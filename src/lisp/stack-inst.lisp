;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module STACK-INST

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Chris Morel 



;;;; Stack Evaluator Instructions




;;; This file implements all instructions for the stack evaluator.  These
;;; instructions are used at macro expand time by the function STACK-EVAL, which
;;; must follow this file in the loading sequence.

;; Forward References


;; In GRAMMAR2

(declare-forward-reference write-expression function)


;; In STACK-COMP

(declare-forward-reference emit-operator-of-type function)
(declare-forward-reference compiler-warning-if-superseded-attribute function)

;; In STACK-EVAL1

(declare-forward-reference pprint-infix-evaluator function)

(declare-forward-reference pprint-functional-evaluator function)

;; In STACK-KERN
(declare-forward-reference enable-running-compiled-code-p variable)
(declare-forward-reference execution-time-stack variable)
(declare-forward-reference procedure-start-time variable)
(declare-forward-reference procedure-end-time variable)
(declare-forward-reference procedure-current-time variable)

;; In PROC-INST

(declare-forward-reference twrite-reference-point-details function)

;; In G2-GSI

(declare-forward-reference gsi-interface-p-function function)

;; In G2DS

(declare-forward-reference g2-to-g2-data-interface-p-function function)

;; In FOREIGN

(declare-forward-reference new-call-foreign-function function)

;; In CONTROLS

(declare-forward-reference show-or-hide function)

;; In G2-BPEL

(declare-forward-reference g2gl-call-invocation-p-function function)






;;;; Stack Evaluator Instruction Format




;;; An instruction in stack eval consists of a byte followed by zero or more
;;; bytes of code constant arguments stored in the instruction vector.
;;; Instructions which take code constant arguments are responsible for
;;; performing a branch past their arguments to the next instruction byte.
;;; Forms are available within the bodies of instructions to perform branches
;;; and to refer to the instruction word.  Constant datum within a compiled form
;;; (which can be any kind of G2 datum, integer, float, string, or truth value,
;;; where truth values are integers between -1000 and 1000) can either be stored
;;; directly in the bytes following the instruction if they are small integers,
;;; or else are stored in a separate constant vector.  The bytes following a
;;; push constant instruction form an index into the constant vector.

;;; The choice of a byte representation for instructions and constants in the
;;; instruction stream lead us to some choices about the maximum sizes of
;;; instruction vectors, maximum count of local variables in a stack frame, and
;;; maximum sizes of instruction vectors themselves, in that natural maximum
;;; sizes for these structures are either 256 or 65536.

;;; Given this suggestion, the following maximum sizes are imposed.  Instruction
;;; vectors are limited to 64K.  Local var vectors and constant vectors are
;;; limited to 2048.  The number of arguments to a function or procedure is
;;; limited to 256.  The maximum number of local variables in a stack frame is
;;; 256.  We may have to consider upping the local variables limit for large
;;; procedures.

;;; An instruction should be added to help alleviate the restriction to 256
;;; instructions.  This instruction will execute out-of-line instructions.  It
;;; should take a one byte argumnent identifying which out-of-line function to
;;; funcall.  There will be a simple vector containing pointers to the compiled
;;; functions for each of these out-of-line instructions and another vector
;;; identifying which type of dispatching code to use.  The dispatching code is
;;; responsible for extracting arguments to the instruction from the stack and
;;; passing them as arguments to the out-of-line instruction.  Some instructions
;;; may also be passed the stack, base-of-stack-frame, and top-of-stack
;;; pointers, and may return either a new program-counter or a new top-of-stack
;;; pointer.  This is a hook to avoid a complex dispatching code, but this hook
;;; should be avoided since future machine code compiled versions of the system
;;; may end up calling these out-of-line instructions directly from Lisp code.






;;;; Instruction Printers and Pprinters




;;; All stack instruction printers and pprinters are grouped here to ensure that
;;; they precede the stack instruction definitions which use them, and to
;;; facilitate reuse.  Note that for the printers, the name of the stack
;;; instruction will already have been written and these functions should print
;;; the extra information for that instruction.  This is not true for the
;;; pprinter which print the name and arguments in a format that is "pretty"
;;; (understandable) to the end-user.

(defun-void print-op-and-code-constant (pc instructions constants environment)
  (declare (ignore constants environment))
  (twrite-character #.%space)
  (twrite-positive-fixnum (byte-vector-aref instructions (+f pc 1))))

(defmacro defun-printer-with-typecode (name base-printer offset)
  `(defun-void ,name (pc instructions constants environment)
     (,base-printer pc instructions constants environment)
     (twrite ", ")
     (twrite-typecode (byte-vector-aref instructions (+f pc ,offset)))))


(defun-printer-with-typecode print-op-and-code-constant-and-typecode
    print-op-and-code-constant
  2)

(defun-void print-op-and-long-code-constant
       (pc instructions constants environment)
  (declare (ignore constants environment))
  (twrite-character #.%space)
  (twrite-positive-fixnum
    (long-code-constant-in-byte-vector instructions (+f pc 1))))

(defun-void print-op-and-relative-code-constant
       (pc instructions constants environment)
  (declare (ignore constants environment))
  (twrite-character #.%space)
  (twrite-fixnum
    (relative-code-constant-in-byte-vector instructions (+f pc 1))))

(defun-void print-op-and-relative-code-constant-address
       (pc instructions constants environment)
  (declare (ignore constants environment))
  (let ((relative-constant
	  (relative-code-constant-in-byte-vector instructions (+f pc 1))))
    (tformat " by ~a to ~a"
	     relative-constant (+f pc relative-constant))))

(defun-void print-op-and-constant (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index (byte-vector-aref instructions (+f pc 1)))
	 (constant (svref constants constant-index)))
    (tformat " #~a (" constant-index)
    (cond ((evaluation-value-p constant)
	   (write-evaluation-value constant))
	  (t
	   (twrite constant)))
    (twrite-string ")")))

(defun-void print-op-and-constant-long (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 1)))
	 (constant (svref constants constant-index)))
    (tformat " #~a (" constant-index)
    (cond ((evaluation-value-p constant)
	   (write-evaluation-value constant))
	  (t
	   (twrite constant)))
    (twrite-string ")")))

(defun-void print-op-constant-long-and-code-constant
       (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 1)))
	 (constant (svref constants constant-index))
	 (code-constant (byte-vector-aref instructions (+f pc 3))))
    (tformat " #~a (" constant-index)
    (cond ((null constant)
	   (twrite-string "no value"))
	  ((evaluation-value-p constant)
	   (write-evaluation-value constant))
	  ((framep constant)
	   (tformat "~NF" constant))
	  (t
	   (twrite constant)))
    (twrite-string ")")
    (tformat ", ~a" code-constant)))

(defun-void print-op-and-role-no-domain-long
       (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 1)))
	 (role (svref constants constant-index))
	 (code-constant (byte-vector-aref instructions (+f pc 3))))
    (tformat " #~a, " constant-index)
    (cond ((symbolp role)
	   (twrite-symbol role))
	  (t
	   (print-role role)))
    (tformat ", ~a" code-constant)))

(defun-void print-op-and-role-long
       (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 1)))
	 (role (svref constants constant-index)))
    (tformat " #~a, the " constant-index)
    (print-role role)))

(defun-void print-op-role-long-and-arg-count
       (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 1)))
	 (role (svref constants constant-index))
	 (arg-count (byte-vector-aref instructions (+f pc 3))))
    (tformat " #~a, the " constant-index)
    (print-role role)
    (tformat ", ~a arguments" arg-count)))

(defun-void print-funcall-evaluator
       (pc instructions constants environment)
  (declare (ignore constants environment))
  (let* ((function-description?
	  (svref funcalled-evaluator-array
		 (byte-vector-aref instructions (+f pc 1))))
	 (instruction-name (if function-description?
			      (instruction-name function-description?)
			      'error-unused-index)))
    (twrite-character #.%space)
    (twrite-symbol instruction-name)))

(defun-void pprint-funcall-evaluator
       (pc byte-code-body constant-vector stack top-of-stack)
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (evaluator-number (byte-vector-aref instructions (+f pc 1)))
	 (description?
	  (svref funcalled-evaluator-array evaluator-number))
	 (pprinter?
	   (when description? (evaluator-pprinter-function description?)))
	 (argument-count
	   (when description? (length (evaluator-arguments description?)))))
    (cond ((null description?)
	   (tformat "internal out-of-line evaluator ~a" evaluator-number))
	  (pprinter?
	   (funcall-simple-compiled-function
	     pprinter? description? pc byte-code-body constant-vector stack
	     top-of-stack))
	  ((=f argument-count 2)
	   (pprint-infix-evaluator
	     description? pc byte-code-body constant-vector stack
	     top-of-stack))
	  (t
	   (pprint-functional-evaluator
	     description? pc byte-code-body constant-vector stack
	     top-of-stack)))))




;;; The function `print-funcalled-instruction' is used to print a
;;; funcalled-instruction which is being executed by the funcall-instruction.
;;; Funcall-instruction is defined in STACK-INST.

(defun-void print-funcalled-instruction
       (pc instructions constants environment)
  (declare (ignore constants environment))
  (let* ((funcalled-instruction-number
	   (byte-vector-aref instructions (+f pc 1)))
	 (funcalled-instruction-description?
	   (svref funcalled-instructions funcalled-instruction-number))
	 (printer? (and funcalled-instruction-description?
			(funcalled-instruction-printer-function
			  funcalled-instruction-description?)))
	 (instruction-name 
	   (if funcalled-instruction-description?
	       (funcalled-instruction-name funcalled-instruction-description?)
	       'error-unused-index)))
    (twrite-character #.%space)
    (if printer?
	(funcall-symbol printer?)	
	(twrite-symbol instruction-name))))

(defun-void pprint-funcalled-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (funcalled-instruction-number
	   (byte-vector-aref instructions (+f pc 1)))
	 (funcalled-instruction-description?
	   (svref funcalled-instructions funcalled-instruction-number))
	 (pprinter? (and funcalled-instruction-description?
			(funcalled-instruction-pprinter-function
			  funcalled-instruction-description?))))
    (if pprinter?
	(funcall-simple-compiled-function
	  pprinter? funcalled-instruction-description? pc byte-code-body
	  constant-vector stack top-of-stack)
	(tformat "internal out-of-line instruction ~a"
		 funcalled-instruction-number))))

(defun-void print-funcalled-instruction-n
       (pc instructions constants environment)
  (declare (ignore constants environment))
  (let* ((funcalled-instruction-number
	   (byte-vector-aref instructions (+f pc 1)))
	 (funcalled-instruction-description?
	   (svref funcalled-instructions funcalled-instruction-number))
	 (printer? (and funcalled-instruction-description?
			(funcalled-instruction-printer-function
			  funcalled-instruction-description?)))
	 (instruction-name 
	   (if funcalled-instruction-description?
	       (funcalled-instruction-name funcalled-instruction-description?)
	       'error-unused-index))
	 (arg-count
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 3)))
	 (result-count
	   (byte-vector-aref instructions (+f pc 2))))
    (twrite-character #.%space)
    (if printer?
	(funcall-symbol printer?)	
	(twrite-symbol instruction-name))
    (tformat " (~D arguments, ~D results)" arg-count result-count)))

(defun-void pprint-funcalled-instruction-n
       (pc byte-code-body constant-vector stack top-of-stack)
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (funcalled-instruction-number
	   (byte-vector-aref instructions (+f pc 1)))
	 (funcalled-instruction-description?
	   (svref funcalled-instructions funcalled-instruction-number))
	 (pprinter? (and funcalled-instruction-description?
			(funcalled-instruction-pprinter-function
			  funcalled-instruction-description?)))
	 (arg-count
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 3)))
	 (result-count
	   (byte-vector-aref instructions (+f pc 2))))
    (if pprinter?
	(funcall-simple-compiled-function
	  pprinter? funcalled-instruction-description? pc byte-code-body
	  constant-vector stack top-of-stack arg-count result-count)
	(tformat "internal out-of-line instruction ~a"
		 funcalled-instruction-number))))

(defun-void print-op-and-surrounding-local-var
       (pc instructions constants environment)
  (declare (ignore constants))
  (let* ((var-spot-index
	   (long-code-constant-in-byte-vector instructions (+f pc 1)))
	 (var-spot (gensym-list 'var-spot var-spot-index)))
    (twrite-character #.%space)
    (print-var-spot-for-stack var-spot environment)
    (reclaim-gensym-list var-spot)))

(defun-printer-with-typecode print-op-and-surrounding-local-var-and-typecode
    print-op-and-surrounding-local-var
  3)

(defun-void print-op-and-local-var (pc instructions constants environment)
  (declare (ignore constants))
  (let ((var-spot (gensym-list 'var-spot 0)))
    (twrite-character #.%space)
    (setf (second var-spot) (byte-vector-aref instructions (+f pc 1)))
    (print-var-spot-for-stack var-spot environment)
    (reclaim-gensym-list var-spot)))

(defun-printer-with-typecode print-op-and-local-var-and-typecode
    print-op-and-local-var
  2)

(defun-void print-case-dispatch (pc instructions constants environment)
  (declare (ignore constants environment))
  (let ((table-base (long-code-constant-in-byte-vector
		      instructions (+f pc 1)))
	(table-length (long-code-constant-in-byte-vector
			instructions (+f pc 3)))
	(else-address (long-code-constant-in-byte-vector
			instructions (+f pc 5))))
    (tformat ", base = ~a, highest = ~a, index->address = "
	     table-base
	     (-f (+f table-base table-length) 1))
    (loop with address-table-pc = (+f pc 7)
	  for index from table-base
	  repeat table-length
	  do
      (tformat "~a->~a, "
	       index
	       (long-code-constant-in-byte-vector
		 instructions
		 (+f address-table-pc (*f (-f index table-base) 2)))))
    (tformat "else->~a" else-address)))

(defun-void print-call-stack-instruction (pc instructions constants environment)
  (declare (ignore constants environment))
  (tformat ", argument-count = ~a, values-count = ~a"
	   (byte-vector-aref instructions (+f pc 1))
	   (byte-vector-aref instructions (+f pc 2))))

(defun-void print-call-function-stack-instruction (pc instructions constants environment)
  (declare (ignore constants environment))
  (tformat ", argument-count = ~a"
	   (byte-vector-aref instructions (+f pc 1))))

(defun-void print-stack-jump (pc instructions constants environment)
  (declare (ignore constants environment))
  (tformat " out ~a code bodies to entry point #~a"
	   (long-code-constant-in-byte-vector instructions (+f pc 1))
	   (long-code-constant-in-byte-vector instructions (+f pc 3))))

(defun-void print-open-role-no-domain-iteration
       (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index (long-code-constant-in-byte-vector
			   instructions (+f pc 1)))
	 (role (svref constants constant-index)))
    (twrite-string " for each")
    (cond ((symbolp role)
	   (twrite-character #.%space)
	   (twrite-symbol role))
	  (t
	   (print-role role)))
    (tformat ", branch to ~a if no values"
	     (long-code-constant-in-byte-vector
	       instructions (+f pc 3)))))

(defun-void print-open-role-iteration (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index (long-code-constant-in-byte-vector
			   instructions (+f pc 1)))
	 (role (svref constants constant-index))
	 (domain-count (byte-vector-aref instructions (+f pc 5))))
    (twrite-string " for each ")
    (print-role role)
    (tformat ", branch to ~a if no values"
	     (long-code-constant-in-byte-vector
	       instructions (+f pc 3)))
    (when (=f domain-count 0)
      (tformat ", for there exists"))))

(defun-void print-serve-next-iteration-value (pc instructions constants environment)
  (declare (ignore constants environment))
  (tformat ", branch to ~a if no values"
	   (long-code-constant-in-byte-vector instructions (+f pc 1))))

(defun-void print-stack-call-code-body (pc instructions constants environment)
  (declare (ignore constants environment))
  (tformat " #~a, argument-count = ~a"
	   (byte-vector-aref instructions (+f pc 1))
	   (byte-vector-aref instructions (+f pc 2))))

(defun-void print-op-and-type-long (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((index (long-code-constant-in-byte-vector instructions (+f pc 1)))
	 (type (svref constants index)))
    (tformat " #~a, ~NT" index type)))

(defun-void print-block-copy (pc instructions constants environment)
  (declare (ignore constants))
  (let ((var-spot
	  (gensym-list 'var-spot
		       (long-code-constant-in-byte-vector
			 instructions (+f pc 1))))
	(count (byte-vector-aref instructions (+f pc 3))))
    (twrite-string " starting at ")
    (print-var-spot-for-stack var-spot environment)
    (tformat ", ~a elements" count)))

(defun-void print-action-cache-and-indices (pc instructions constants environment)
  (declare (ignore constants))
  (let* ((cache (long-code-constant-in-byte-vector instructions (+f pc 1)))
	 (count (long-code-constant-in-byte-vector instructions (+f pc 3)))
	 (target (long-code-constant-in-byte-vector instructions (+f pc 5)))
	 (var-spot (gensym-list 'var-spot cache)))
    (twrite-string " ")
    (print-var-spot-for-stack var-spot environment)
    (tformat ", ~a elements" count)
    (when (>f count 0)
      (tformat " starting at ")
      (setf (second var-spot) target)
      (print-var-spot-for-stack var-spot environment))
    (reclaim-gensym-list var-spot)))

(defun-void print-action-cache-indices-and-address
       (pc instructions constants environment)
  (declare (ignore constants))
  (let* ((cache (long-code-constant-in-byte-vector instructions (+f pc 1)))
	 (count (long-code-constant-in-byte-vector instructions (+f pc 3)))
	 (target (long-code-constant-in-byte-vector instructions (+f pc 5)))
	 (address (long-code-constant-in-byte-vector instructions (+f pc 7)))
	 (var-spot (gensym-list 'var-spot cache)))
    (twrite-string " ")
    (print-var-spot-for-stack var-spot environment)
    (tformat ", ~a elements" count)
    (when (>f count 0)
      (tformat " starting at ")
      (setf (second var-spot) target)
      (print-var-spot-for-stack var-spot environment))
    (tformat ", branch to ~a if empty" address)
    (reclaim-gensym-list var-spot)))

(defun-void print-cached-item
       (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 1)))
	 (constant (svref constants constant-index))
	 (code-constant (byte-vector-aref instructions (+f pc 3))))
    (tformat " #~a (" constant-index)
    (cond ((null constant)
	   (twrite-string "no value"))
	  ((evaluation-value-p constant)
	   (write-evaluation-value constant))
	  ((consp constant)
	   (twrite (car-of-cons constant)))
	  ((framep constant)
	   (tformat "~NF" constant))
	  (t
	   (twrite constant)))
    (twrite-string ")")
    (tformat ", ~a" code-constant)))

(defun-void print-cached-attribute (pc instructions constants environment)
  (declare (ignore environment))
  (let* ((constant-index
	   (long-code-constant-in-byte-vector
	     instructions (+f pc 1)))
	 (constant (svref constants constant-index)))
    (tformat " #~a (" constant-index)
    (cond ((evaluation-value-p constant)
	   (write-evaluation-value constant))
	  ((consp constant)
	   (twrite (car-of-cons constant)))
	  (t
	   (twrite constant)))
    (twrite-string ")")))



;;; Pprinters for stack-instructions.

(defun-void pprint-branch-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (twrite-string "branch to ")
    (write-evaluation-value (code-constant 0) t)))

(defun-void pprint-branch-long-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (twrite-string "branch to ")
    (write-evaluation-value (long-code-constant 0) t)))

(defun-void pprint-branch-relative-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (twrite-string "branch to ")
    (write-evaluation-value
      (+f pc (relative-code-constant 0))
      t)))

(defun-void pprint-branch-if-not-true-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (twrite-string "branch to ")
    (write-evaluation-value (code-constant 0) t)
    (twrite-string " if not true (")
    (write-stack-argument 1 1 stack top-of-stack)
    (twrite-string ")")))

(defun-void pprint-branch-long-if-not-true-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (twrite-string "branch to ")
    (write-evaluation-value (long-code-constant 0) t)
    (twrite-string " if not true (")
    (write-stack-argument 1 1 stack top-of-stack)
    (twrite-string ")")))

(defun-void pprint-branch-relative-if-not-true-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (twrite-string "branch to ")
    (write-evaluation-value
      (+f pc (relative-code-constant 0))
      t)
    (twrite-string " if not true (")
    (write-stack-argument 1 1 stack top-of-stack)
    (twrite-string ")")))

(defun-void pprint-branch-if-known-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (tformat "branch if known (~a) to ~a"
	     (if stack-expiration "known" "unknown")
	     (code-constant 0))))

(defun-void pprint-branch-long-if-known-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (tformat "branch if known (~a) to ~a"
	     (if stack-expiration "known" "unknown")
	     (long-code-constant 0))))

(defun-void pprint-branch-relative-if-known-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (tformat "branch if known (~a) to ~a"
	     (if stack-expiration "known" "unknown")
	     (+f pc (relative-code-constant 0)))))

(defun-void pprint-push-from-stack-arg-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (twrite-string "fetch function argument #")
    (write-evaluation-value (code-constant 0) t)
    (twrite-string ", ")
    (twrite-typecode (byte-vector-aref instruction-vector (+f pc 2)))))


(defun-void pprint-case-dispatch-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (table-base (long-code-constant-in-byte-vector
		       instructions (+f pc 1)))
	 (table-length (long-code-constant-in-byte-vector
			 instructions (+f pc 3)))
	 (else-address (long-code-constant-in-byte-vector
			 instructions (+f pc 5))))
    (twrite-string "case (")
    (write-stack-argument 1 1 stack top-of-stack)
    (twrite-string ") of branches: ")
    (loop with address-table-pc = (+f pc 7)
	  for index from table-base
	  repeat table-length
	  do
      (tformat "~a->~a, "
	       index
	       (long-code-constant-in-byte-vector
		 instructions
		 (+f address-table-pc (*f (-f index table-base) 2)))))
    (tformat "else->~a" else-address)))

(defun-void pprint-type-check (type-spec stack top-of-stack)
  (twrite-string "check that ")
  (write-stack-argument 1 1 stack top-of-stack)
  (tformat " is a ~NT" type-spec))

(defun-void pprint-type-check-truth-value-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (pprint-type-check 'truth-value stack top-of-stack))

(defun-void pprint-type-check-symbol-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (pprint-type-check 'symbol stack top-of-stack))

(defun-void pprint-type-check-text-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (pprint-type-check 'text stack top-of-stack))

(defun-void pprint-type-check-quantity-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (pprint-type-check 'number stack top-of-stack))

(defun-void pprint-type-check-integer-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (pprint-type-check 'integer stack top-of-stack))

(defun-void pprint-type-check-float-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (pprint-type-check 'float stack top-of-stack))

(defun-void pprint-type-check-class-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    ;; Not calling pprint-type-check because the class constant is not a
    ;; type-spec format.
    (twrite-string "check that ")
    (write-stack-argument 1 1 stack top-of-stack)
    (tformat " is a ~a" (svref constant-vector (code-constant 0)))))

(defun-void pprint-type-check-class-long-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    ;; Not calling pprint-type-check because the class constant is not a
    ;; type-spec format.
    (twrite-string "check that ")
    (write-stack-argument 1 1 stack top-of-stack)
    (tformat " is a ~a" (svref constant-vector (long-code-constant 0)))))

(defun-void pprint-type-check-item-or-datum-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (pprint-type-check 'item-or-datum stack top-of-stack))

(defun-void pprint-pop-into-surrounding-local-var-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (environment (byte-code-body-environment-description byte-code-body))
	 (var-spot-index
	   (long-code-constant-in-byte-vector instructions (+f pc 1)))
	 (var-spot (gensym-list 'var-spot var-spot-index)))
    (twrite-string "assign ")
    (print-var-spot-for-stack var-spot environment)
    (twrite-string ", ")
    (twrite-typecode (byte-vector-aref instructions (+f pc 3)))
    (twrite-string " = ")
    (write-stack-argument 1 1 stack top-of-stack)
    (reclaim-gensym-list var-spot)))

(defun-void pprint-pop-into-local-var-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (environment (byte-code-body-environment-description byte-code-body))
	 (var-spot (gensym-list 'var-spot 0)))
    (setf (second var-spot) (byte-vector-aref instructions (+f pc 1)))
    (twrite-string "assign ")
    (print-var-spot-for-stack var-spot environment)
    (twrite-string ", ")
    (twrite-typecode (byte-vector-aref instructions (+f pc 2)))
    (twrite-string " = ")
    (write-stack-argument 1 1 stack top-of-stack)
    (reclaim-gensym-list var-spot)))

(defun-void pprint-push-from-surrounding-local-var-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (environment (byte-code-body-environment-description byte-code-body))
	 (var-spot-index
	   (long-code-constant-in-byte-vector instructions (+f pc 1)))
	 (var-spot (gensym-list 'var-spot var-spot-index)))
    (twrite-string "fetch ")
    (print-var-spot-for-stack var-spot environment)
    (twrite-string ", ")
    (twrite-typecode (byte-vector-aref instructions (+f pc 3)))
    (reclaim-gensym-list var-spot)))

(defun-void pprint-move-from-surrounding-local-var-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (environment (byte-code-body-environment-description byte-code-body))
	 (var-spot-index
	   (long-code-constant-in-byte-vector instructions (+f pc 1)))
	 (var-spot (gensym-list 'var-spot var-spot-index)))
    (twrite-string "fetch and clear ")
    (print-var-spot-for-stack var-spot environment)
    (reclaim-gensym-list var-spot)))

(defun-void pprint-push-from-local-var-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack constant-vector))
  (let* ((instructions (byte-code-body-byte-vector byte-code-body))
	 (environment (byte-code-body-environment-description byte-code-body))
	 (var-spot (gensym-list 'var-spot 0)))
    (setf (second var-spot) (byte-vector-aref instructions (+f pc 1)))
    (twrite-string "fetch ")
    (print-var-spot-for-stack var-spot environment)
    (twrite-string ", ")
    (twrite-typecode (byte-vector-aref instructions (+f pc 2)))
    (reclaim-gensym-list var-spot)))

(defun-void pprint-name-reference-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack))
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (twrite-string "fetch ")
    (tformat "~a" 
	     (evaluation-symbol-symbol
	       (svref constant-vector (long-code-constant 0))))))

(defun-void pprint-evaluate-role-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (role-index (long-code-constant 0))
	 (arg-count (code-constant 2))		; currently 1 or 2 domains
	 (role (svref constant-vector role-index)))
    (twrite-string "fetch the ")
    (print-role role)
    (twrite-character #.%space)
    (loop for index = 1 then (+f index 1)
	  with first-arg? = t
	  until (>f index arg-count)
	  do
      (cond (first-arg?
	     (setq first-arg? nil))
	    (t
	     (twrite-string ", ")))
      (write-stack-argument index arg-count stack top-of-stack))))

(defun-void pprint-evaluate-role-with-no-domain-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack))
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (role-index (long-code-constant 0))
	 (role (svref constant-vector role-index)))
    (twrite-string "fetch the ")
    (print-role role)))

(defun-void pprint-parameter-value-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "fetch the value of ")
  (write-stack-argument 1 1 stack top-of-stack))

(defun-void pprint-coerce-integer-to-float-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "coerce integer to float ")
  (write-stack-argument 1 1 stack top-of-stack))

(defun-void pprint-coerce-quantity-to-float-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "coerce quantity to float ")
  (write-stack-argument 1 1 stack top-of-stack))

(defun-void pprint-not-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "not (")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string ")"))

(defun-void pprint-attribute-frame-or-place-reference-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "fetch the ")
  (write-stack-argument 2 2 stack top-of-stack)
  (twrite-string " of ")
  (write-stack-argument 1 2 stack top-of-stack))

(defun-void pprint-attribute-value-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (let ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	(stack-program-counter (+f pc 1)))
    (tformat "fetch the ~a of " 
	     (evaluation-symbol-symbol
	       (svref constant-vector (long-code-constant 0))))
    (write-stack-argument 1 1 stack top-of-stack)))

(defun-void pprint-cached-attribute-value-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (attribute-index-or-cons
	   (svref constant-vector (long-code-constant 0))))
    (cond
      ((consp attribute-index-or-cons)
       (tformat "fetch the ~a of " 
		(car-of-cons attribute-index-or-cons))
       (write-stack-argument 1 1 stack top-of-stack))
      (t
       (twrite-string "fetch the attribute of ")
       (write-stack-argument 1 1 stack top-of-stack)
       (tformat " at location ~a" attribute-index-or-cons)))))

(defun-void pprint-return-values-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (arg-count (code-constant 0)))
    (twrite-string "return ")
    (loop for index = 1 then (+f index 1)
	  with first-arg? = t
	  until (>f index arg-count)
	  do
      (cond (first-arg?
	     (setq first-arg? nil))
	    (t
	     (twrite-string ", ")))
      (write-stack-argument index arg-count stack top-of-stack))))

(defun-void pprint-signal-error-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "signal ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string ", ")
  (write-stack-argument 2 2 stack top-of-stack))

;; Pprinter for single argument version of the signal instruction
;; See instruction number 137 below.
;; ajs (5/29/96)

(defun-void pprint-signal-error-new-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "signal ")
  (write-stack-argument 1 1 stack top-of-stack))

(defun-void pprint-call-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (proc-arg-count (code-constant 0))
	 (stack-arg-count (+f proc-arg-count 1)))
    (twrite-string "call ")
    (write-stack-argument 1 stack-arg-count stack top-of-stack)
    (twrite-string " (")
    (loop for index = 2 then (+f index 1)
	  with first-arg? = t
	  until (>f index stack-arg-count)
	  do
      (cond (first-arg?
	     (setq first-arg? nil))
	    (t
	     (twrite-string ", ")))
      (write-stack-argument index stack-arg-count stack top-of-stack))
    (twrite-string ") ")))

(defun-void pprint-call-rpc-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (proc-arg-count (code-constant 0))
	 (stack-arg-count (+f proc-arg-count 2)))
    (twrite-string "call ")
    (write-stack-argument 1 stack-arg-count stack top-of-stack)
    (twrite-string " (")
    (loop for index = 3 then (+f index 1)
	  with first-arg? = t
	  until (>f index stack-arg-count)
	  do
      (cond (first-arg?
	     (setq first-arg? nil))
	    (t
	     (twrite-string ", ")))
      (write-stack-argument index stack-arg-count stack top-of-stack))
    (twrite-string ") across ")
    (write-stack-argument 2 stack-arg-count stack top-of-stack)))

(defun-void pprint-allow-other-processing-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body stack top-of-stack constant-vector))
  (twrite-string "allow other processing"))

(defun-void pprint-open-role-iteration-no-domain-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack))
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (role-index (long-code-constant 0))
	 (role (svref constant-vector role-index))
	 (branch-address (long-code-constant 1)))
    (twrite-string "fetch first iteration of each ")
    (cond ((symbolp role)
	   (twrite-symbol role))
	  (t
	   (print-role role)))
    (tformat ", branch to ~a if none" branch-address)))

;; Note that the pprint-open-role-iteration-instruction function should be fixed
;; when the ignored-domain-count code-constant to the open-role-iteration
;; instruction is not ignored.  - cpm, 6/4/92




(defun-void pprint-open-role-iteration-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (role-index (long-code-constant 0))
	 (role (svref constant-vector role-index))
	 (branch-address (long-code-constant 1))
	 (domain-count (code-constant 4)))
    (twrite-string "fetch first iteration of each ")
    (print-role role)
    (twrite-character #.%space)
    (write-stack-argument 1 1 stack top-of-stack)
    (tformat ", branch to ~a if none" branch-address)
    (when (=f domain-count 0)
      (tformat ", for there exists"))))

(defun-void pprint-serve-next-iteration-value-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (branch-address (long-code-constant 0)))
    (twrite-string "fetch next iteration of ")
    (write-stack-argument 1 1 stack top-of-stack)
    (tformat ", branch to ~a if none" branch-address)))

(defun-void pprint-type-check-item-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "check that ")
  (write-stack-argument 1 1 stack top-of-stack)
  (tformat " is an item"))

(defun-void pprint-fetch-value-of
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "fetch the value of ")
  (write-stack-argument 1 1 stack top-of-stack))

(defun-void pprint-and-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " and ")
  (write-stack-argument 2 2 stack top-of-stack))

(defun-void pprint-or-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " or ")
  (write-stack-argument 2 2 stack top-of-stack))

(defun-void pprint-wait-for-interval-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (wait-interval? (and stack-args-ok? (svref stack top-of-stack))))
    (twrite-string "wait for ")
    (if (and wait-interval? (evaluation-quantity-p wait-interval?))
	(print-constant
	  (evaluation-quantity-value wait-interval?) 'seconds)
	(write-stack-argument 1 1 stack top-of-stack))))

(defun-void pprint-type-check-instruction (pc byte-code-body constant-vector stack top-of-stack)
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (type-spec-index (long-code-constant 0))
	 (type-spec (svref constant-vector type-spec-index)))
    (twrite-string "check that ")
    (write-stack-argument 1 1 stack top-of-stack)
    (tformat " is a ~NT" type-spec)))

(defun-void pprint-call-function-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((stack-frame-base
	   (+f top-of-stack number-of-extra-stack-frame-values 2))
	 (instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (nargs (code-constant 0))
	 (function (svref stack top-of-stack)))
    (write-called-function-and-arguments stack stack-frame-base nargs function)))

(defun-void pprint-return-from-function-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "return from function (")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string ")"))

(defun-void pprint-system-procedure-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body stack top-of-stack constant-vector))
  (twrite-string "system procedure internals"))




;; Create-Connection

;; This instruction takes 14 arguments from the stack.  These are a class; 5
;; values for the first end specifier; 5 values for the second end specifer; and
;; 3 connection details.

;; The end specifier values consist of a designation, make-new-stub flag, side,
;; position, and portname.

;; All of these values may be nil, except for the designation for the first end
;; specifier.

;; The connection details value consists of a style, direction, and vertices.
;; Each of these connection details may be nil.  The vertices value may be nil,
;; an index into a list of numbers in the constant vector, or a g2-list item.

;; Note that a separate instruction is emitted when the result of the action
;; should be popped into a local variable.  Therefore, this create-connection
;; instruction does not take a var-spot argument.

;; Stack-arguments:
;; 1 class 
;; 2 end-1-item
;; 3 make-new-stub-1?
;; 4 side-1?
;; 5 position-1?
;; 6 portname-1?
;; 7 end-2-item?
;; 8 make-new-stub-2?
;; 9 side-2?
;; 10 position-2?
;; 11 portname-2?
;; 12 style?
;; 13 direction?
;; 14 vertices

(defun-void pprint-create-connection-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body))
  (let* ((class (evaluation-symbol-symbol
		  (svref stack (-f top-of-stack 13))))	;1
	 (end-1-item (svref stack (-f top-of-stack 12)))	;2
	 (make-new-stub-1? (evaluation-symbol-symbol
			     (svref stack (-f top-of-stack 11))))	;3
	 (side-1? (evaluation-symbol-symbol
		    (svref stack (-f top-of-stack 10))))	;4
	 (position-1? (evaluation-value-value
			(svref stack (-f top-of-stack 9))))	;5
	 (portname-1? (evaluation-symbol-symbol
			(svref stack (-f top-of-stack 8))))	;6
	 (end-2-item? (if (evaluation-symbol-p
			    (svref stack (-f top-of-stack 7)))	;7
			  (evaluation-symbol-symbol
			    (svref stack (-f top-of-stack 7)))
			  (svref stack (-f top-of-stack 7))))
	 (make-new-stub-2? (evaluation-symbol-symbol
			     (svref stack (-f top-of-stack 6))))	;8
	 (side-2? (evaluation-symbol-symbol
		    (svref stack (-f top-of-stack 5))))	;9
	 (position-2? (evaluation-value-value 
			(svref stack (-f top-of-stack 4))))	;10
	 (portname-2? (evaluation-symbol-symbol
			(svref stack (-f top-of-stack 3))))	;11
	 (style? (evaluation-symbol-symbol
		   (svref stack (-f top-of-stack 2))))	;12
	 (direction? (evaluation-symbol-symbol
		       (svref stack (-f top-of-stack 1))))	;13
	 (vertices-list-or-constant-index? (svref stack top-of-stack)))	;14

    (when position-1? (setq position-1? (round position-1?)))
    (when position-2? (setq position-2? (round position-2?)))

    (cond
      ((evaluation-symbol-p vertices-list-or-constant-index?)
       (setq vertices-list-or-constant-index? 
	     (evaluation-symbol-symbol vertices-list-or-constant-index?)))
      ((evaluation-integer-p vertices-list-or-constant-index?)
       (setq vertices-list-or-constant-index?
	     (svref constant-vector
		    (evaluation-integer-value
		      vertices-list-or-constant-index?)))))

    ;; Direction? determines which is the input and
    ;; which is the output end object.
    (when (eq direction? 'input)
      (psetq end-1-item end-2-item?
	     end-2-item? end-1-item
	     make-new-stub-1? make-new-stub-2?
	     make-new-stub-2? make-new-stub-1?
	     side-1? side-2?
	     side-2? side-1?
	     position-1? position-2?
	     position-2? position-1?
	     portname-1? portname-2?
	     portname-2? portname-1?))

    ;; Write the pretty-print of the instruction.

    (twrite-string "create a connection ")
    (when (not (eq class 'connection))
      (tformat "of class ~a " class))

    (if end-2-item?
	(twrite-string "connected between ")
	(twrite-string "connected to "))
    (write-stored-value end-1-item)
    (cond
      (make-new-stub-1?
       (twrite-string " newly locating it at the position ")
       (write-stored-value side-1?)
       (twrite-character #.%space)
       (write-stored-value position-1?)
       (twrite-string " at the port ")
       (write-stored-value portname-1?))
      (t
       (twrite-string " at the port ")
       (write-stored-value portname-1?)
       (twrite-string " locating it at the position ")
       (write-stored-value side-1?)
       (twrite-character #.%space)
       (write-stored-value position-1?)))

    (when end-2-item?
      (twrite-string " and ")
      (write-stored-value end-2-item?)
      (cond
	(make-new-stub-2?
	 (twrite-string " newly locating it at the position ")
	 (write-stored-value side-2?)
	 (twrite-character #.%space)
	 (write-stored-value position-2?)
	 (twrite-string " at the port ")
	 (write-stored-value portname-2?))
	(t
	 (twrite-string " at the port ")
	 (write-stored-value portname-2?)
	 (twrite-string " locating it at the position ")
	 (write-stored-value side-2?)
	 (twrite-character #.%space)
	 (write-stored-value position-2?))))

    (twrite-string " with style ")
    (write-stored-value style?)
    (twrite-string ", with vertices ")
    (cond ((and vertices-list-or-constant-index?
		(listp vertices-list-or-constant-index?))
	   (loop for index in vertices-list-or-constant-index?
		 do
	     (tformat "~a " index)))
	  (t
	   (write-stored-value vertices-list-or-constant-index?)))
    (twrite-string ", with direction ")
    (write-stored-value direction?)))

(defun-void pprint-halt-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "halt with ")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string "if breakpoints are enabled"))

;;   SHOW (item window? show-details?)

(defun-void pprint-show-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (window? (and stack-args-ok? (svref stack (-f top-of-stack 1))))
	 (show-details-constant-index?
	   (if stack-args-ok? (svref stack top-of-stack) nil))
	 (show-details?
	   (if show-details-constant-index?
	       (svref constant-vector
		      (evaluation-integer-value show-details-constant-index?))
	       nil)))
    (twrite-string "show ")
    (write-stack-argument 1 3 stack top-of-stack)
    (when window?
      (twrite-string " on ")
      (write-stack-argument 2 3 stack top-of-stack))
    (loop for show-detail = (first show-details?) then (first show-details?)
	  while show-details?
	  do
      (setq show-details? (cdr show-details?))
      (case (car show-detail)
	(scale
	 (twrite-string " at ")
	 (twrite (second show-detail))
	 (twrite-string " scale"))
	(workspace-position
	 (twrite-string " with its ")
	 (twrite-reference-point-details (cdr show-detail))
	 (twrite-string " ")
	 (twrite-reference-point-details (cdr (first show-details?)))
	 (twrite-string " of the screen")
	 (setq show-details? (cdr show-details?)))
	(screen-position
	 (twrite-string " ")
	 (twrite-reference-point-details (cdr show-detail))
	 (twrite-string " of the screen"))
	;; No longer in the show details, see the stack instruction.
;	(in
;	 ;; "in" grammar is seen as "on" by the user.
;	 (twrite-string " on ")
;	 (print-designation (second show-detail)))
	))))

;;   INVOKE (query-restriction focal-entity?)

(defun-void pprint-invoke-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (query-restriction-constant-index?
	   (and stack-args-ok? (svref stack (-f top-of-stack 1))))
	 (query-restriction?
	   (and query-restriction-constant-index?
		(svref constant-vector
		       (evaluation-integer-value
			 query-restriction-constant-index?))))
	 (focal-entity? (and stack-args-ok? (svref stack top-of-stack))))
    (twrite-string "invoke ")
    (if stack-args-ok?
	(loop for category in (cdr query-restriction?)
	      with first-arg? = t
	      do
	  (if first-arg?
	      (setq first-arg? nil)
	      (twrite-string ", "))
	  (tformat "~a" category))
	(twrite-string "<unavailable argument>"))
    (twrite-string " rules")
    (when focal-entity?
      (twrite-string " for ")
      (write-stack-argument 2 2 stack top-of-stack))))
	

;; INVOKE-WITH-WAIT (query-restriction focal-entity?)

;; This will be going away and folded into pprint-invoke-instruction at the
;; next KB recompile, so not bothering to abstract (famous last
;; words). -dkuznick, 6/13/05 

(defun-void pprint-invoke-with-wait-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (query-restriction-constant-index?
	   (and stack-args-ok? (svref stack (-f top-of-stack 1))))
	 (query-restriction?
	   (and query-restriction-constant-index?
		(svref constant-vector
		       (evaluation-integer-value
			 query-restriction-constant-index?))))
	 (focal-entity? (and stack-args-ok? (svref stack top-of-stack))))
    (twrite-string "invoke ")
    (if stack-args-ok?
	(loop for category in (cdr query-restriction?)
	      with first-arg? = t
	      do
	  (if first-arg?
	      (setq first-arg? nil)
	      (twrite-string ", "))
	  (tformat "~a" category))
	(twrite-string "<unavailable argument>"))
    (twrite-string " rules")
    (when focal-entity?
      (twrite-string " for ")
      (write-stack-argument 2 2 stack top-of-stack))
    (twrite-string ", awaiting completion")))


(defun-void pprint-coerce-matching-element-type-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "check that ")
  (write-stack-argument 2 2 stack top-of-stack)	; item or value
  (twrite-string " can be stored in ")
  (write-stack-argument 1 2 stack top-of-stack))	; array or list

(defun-void pprint-pause-kb-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body stack top-of-stack constant-vector))
  (twrite-string "pause knowledge-base"))

(defun-void pprint-reset-kb-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body stack top-of-stack constant-vector))
  (twrite-string "reset knowledge-base"))

;;   NUPEC-SYNCHRONIZE (g2-to-g2-object {item} class-list arg-count)

(defun-void pprint-nupec-synchronize-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (stack-arg-count-minus-one
	   (code-constant 0))
	 (synch-item-arg-count?
	   (if stack-args-ok? (-f stack-arg-count-minus-one 2) nil))
	 (stack-arg-count?
	   (if stack-args-ok? stack-arg-count-minus-one nil))
	 (class-arg-count 0))
    (twrite-string "nupec synchronze ")
    (cond
      ((null stack-args-ok?)
       (twrite-string "<unavailable argument>"))
      (t
       ;; Write the classes (every <class>) to synchronize.
       (loop with class-constant-index = (svref stack top-of-stack)
	     with classes =
	       (svref constant-vector
		      (evaluation-integer-value class-constant-index))
	     with first-class? = t
	     for class in classes
	     do
	 (cond (first-class?
		(setq first-class? nil))
	       (t
		(twrite-string ", ")))
	 (tformat "every ~a" class)
	     finally
	       (setq class-arg-count (length classes)))
       ;; Write the items to synchronize.
       (loop for index = 2 then (+f index 1)
	     with last-synch-item-arg-index = (+f synch-item-arg-count? 1)
	     with first-item? = t
	     until (>f index last-synch-item-arg-index)
	     do
	 (cond (first-item?
		(setq first-item? nil)
		(unless (=f class-arg-count 0)
		  (twrite-string ", ")))
	       (t
		(twrite-string ", ")))
	 (write-stack-argument index stack-arg-count? stack top-of-stack))))
    (twrite-string " across ")
    (if (null stack-args-ok?)
	(twrite-string "<unavailable argument>")
	(write-stack-argument 1 stack-arg-count? stack top-of-stack))))

(defun-void pprint-nth-element-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "fetch ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string "[")
  (write-stack-argument 2 2 stack top-of-stack)
  (twrite-string "]"))


;; Note that the function pprint-type-check-class-inline-instruction is defined
;; in this module after the constant classes-type-checked-inline.


(defun-void pprint-complete-generic-formula-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "complete generic formula (")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string ")"))

(defun-void pprint-complete-cell-expression-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "complete embedded expression (")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string ")"))

(defun-void pprint-push-cached-item-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore stack top-of-stack))
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (item-or-cons? (svref constant-vector (long-code-constant 0))))
    (twrite-string "fetch ")
    (cond ((null item-or-cons?)
	   (twrite-string "<unavailable argument>"))
	  ((framep item-or-cons?)
	   (tformat "~NF" item-or-cons?))
	  ((consp item-or-cons?)
	   ;; print the item name
	   (tformat "~a" (car-of-cons item-or-cons?)))
	  (t
	   (twrite-string "<unavailable argument>")))))






;;;; Instructions




;;; The following is a list of instructions we'll need to implement control
;;; structures and expiration computations.

;;; Instruction 0, the `BAD-INSTRUCTION stack instruction' is used to detect
;;; stack instruction programs falling off the end of the instruction stream.
;;; If any stack instructions fall off the end of valid instructions and into
;;; extra space in the byte vector of instructions, they will execute this
;;; instruction, which signals an error.

;;; BAD-INSTRUCTION

;;; Since the otherwise clause for the case statement which dispatches to
;;; instructions bodies ends up calling the bad-instruction-error function, we
;;; do not need to actually implement this instruction.  A small (tiny, teeny,
;;; not worth mentioning) code size improvement is realized by not doing this.

(defun-void bad-instruction-error (instruction top-of-stack)
  (stack-error top-of-stack
    "Attempted to execute ~a, which does not name a valid instruction.  ~
     Execution has proceeded past the end of valid instructions or is ~
     executing data.  Please report this G2 byte code executor bug to Gensym ~
     software support."
    instruction))




;;; Instruction 1, the `BRANCH instruction' takes one argument, the new program
;;; counter to branch to.

;;; Note that a second code constant byte will be in the instruction stream
;;; which will be ignored.  This padding byte is there so that BRANCH will be
;;; the same length and BRANCH-LONG, simplifying the optimizer which chooses
;;; BRANCH over BRANCH-LONG.

;;; BRANCH (new-pc, unused-byte)

(def-stack-instruction (branch 1 3 nil print-op-and-code-constant
			       pprint-branch-instruction)
  (setq stack-program-counter (code-constant 0)))




;;; Instruction 2, the `BRANCH-LONG instructions' takes two arguments, the low
;;; byte and the high byte of the new program counter.

;;; BRANCH-LONG (high-byte-new-pc, low-byte-new-pc)

(def-stack-instruction (branch-long 2 3 nil print-op-and-long-code-constant
				    pprint-branch-long-instruction)
  (setq stack-program-counter (long-code-constant 0)))




;;; Instruction 3, the `BRANCH-RELATIVE stack instruction' takes a single code
;;; constant argument, the relative branch count offset by 128.  The number is a
;;; relative branch instruction count, offset by 128 to which the program
;;; counter should branch.  Note that this offset is actually from the
;;; instruction following the BRANCH-RELATIVE instruction, since the program
;;; counter is incremented before the execution of an instruction body.  The new
;;; PC will be (+ current-pc (- relative 128)).  For example a BRANCH-RELATIVE
;;; -1 is a branch back to self.  Note that the -1 would actually be coded as
;;; 127.

;;; Also note the second code constant byte included as padding to make this
;;; instruction the same size as BRANCH-LONG.

;;; BRANCH-RELATIVE (relative-pc-plus-128, unused-byte)

(def-stack-instruction (branch-relative 3 3 nil
			 print-op-and-relative-code-constant-address
			 pprint-branch-relative-instruction)
  (setq fixnum-register-1 (relative-code-constant 0))
  (setq stack-program-counter
	(+f (-f stack-program-counter 1)
	    fixnum-register-1)))




;;; The stack-instruction-emitter `branch-long' for branch emits the branch
;;; op-code and two zero bytes.  The byte-code address resolver can then rewrite
;;; the op-code to use branch-relative or branch when the true address is known.

(def-stack-instruction-emitter branch-long (byte-code-stream target-tag-marker)
  (register-byte-code-tag-resolution-point
    byte-code-stream target-tag-marker)
  (emit-instruction-byte-code byte-code-stream 'branch-long)
  (write-byte-code-to-stream byte-code-stream 0)
  (write-byte-code-to-stream byte-code-stream 0))

(def-byte-code-resolver branch-long (byte-code-stream byte-vector address tag)
  (declare (ignore byte-code-stream))
  (let* ((tag-address (instruction-address-for-tag tag nil))
	 (relative-offset (-f tag-address address)))
    (cond ((<f tag-address 256)
	   (setf (byte-vector-aref byte-vector address)
		 (op-code-for-stack-instruction 'branch))
	   (setf (byte-vector-aref byte-vector (+f address 1))
		 tag-address))
	  ((relative-code-constant-p relative-offset)
	   (setf (byte-vector-aref byte-vector address)
		 (op-code-for-stack-instruction 'branch-relative))
	   (setf (relative-code-constant-in-byte-vector
		   byte-vector (+f address 1))
		 relative-offset))
	  (t
	   (setf (long-code-constant-in-byte-vector byte-vector (+f address 1))
		 tag-address)))))




;;; Instruction 4, the `BRANCH-IF-NOT-TRUE stack instruction' takes one byte
;;; worth of code constant argument from the instruction stream and one argument
;;; from the top of the stack.  The value on the stack should be an integer
;;; representing a logical value.  If the logical value is less than the truth
;;; threshold in the inference-engine-parameters system table (i.e.  is not
;;; true), then a branch will be executed to the program counter in the
;;; instruction stream code constant.  If the value is true (i.e.  greater than
;;; or equal to the truth threshold), then execution will continue at the
;;; instruction following the branch.  Note that a mini-branch is needed to
;;; continue, since this instruction must branch past the code constant if
;;; continuing.  Also note that the truth threshold is cached into a local
;;; variable of the stack-eval function, since this is likely the most often
;;; executed instruction.

;;; Also, there is an extra unused code constant byte here, so that this is the
;;; same length as the BRANCH-LONG-IF-NOT-TRUE instruction.

;;; BRANCH-IF-NOT-TRUE (program-counter, unused-byte)

(def-stack-instruction (branch-if-not-true 4 3 1
			 print-op-and-code-constant
			 pprint-branch-if-not-true-instruction)
  (setq register-1 (arg 0))
  (setq fixnum-register-1 (evaluation-truth-value-value register-1))
  (reclaim-evaluation-truth-value register-1)
  (decff top-of-stack)
  (if (<f fixnum-register-1 local-truth-threshold)
      (setq stack-program-counter (code-constant 0))
      (incff stack-program-counter 2)))




;;; Instruction 5, the `BRANCH-LONG-IF-NOT-TRUE stack instruction' takes two
;;; bytes of instruction address.  It pops a logical value off the top of the
;;; stack, and branches to the address in the code constants if the value is not
;;; true.  This is the long instruction address version of BRANCH-IF-NOT-TRUE.

;;; BRANCH-LONG-IF-NOT-TRUE (high-byte-pc, low-byte-pc)

(def-stack-instruction (branch-long-if-not-true 5 3 1
			 print-op-and-long-code-constant
			 pprint-branch-long-if-not-true-instruction)
  (setq register-1 (arg 0))
  (setq fixnum-register-1 (evaluation-truth-value-value register-1))
  (reclaim-evaluation-truth-value register-1)
  (decff top-of-stack)
  (if (<f fixnum-register-1 local-truth-threshold)
      (setq stack-program-counter (long-code-constant 0))
      (incff stack-program-counter 2)))




;;; Instruction 6, the `BRANCH-RELATIVE-IF-NOT-TRUE stack instruction' takes one
;;; byte of instruction address.  It pops a logical value off the top of the
;;; stack, and performs a relative branch by the given instruction count minus
;;; 128 if if the value is not true.  This is the relative branch version of
;;; BRANCH-IF-NOT-TRUE.  An unused-byte pads the length of this instruction to
;;; match BRANCH-LONG-IF-NOT-TRUE.

;;; BRANCH-RELATIVE-IF-NOT-TRUE (relative-pc-plus-128, unused-byte)

(def-stack-instruction (branch-relative-if-not-true 6 3 1
			 print-op-and-relative-code-constant-address
			 pprint-branch-relative-if-not-true-instruction)
  (setq register-1 (arg 0))
  (setq fixnum-register-1 (evaluation-truth-value-value register-1))
  (reclaim-evaluation-truth-value register-1)
  (decff top-of-stack)
  (cond ((<f fixnum-register-1 local-truth-threshold)
	 (setq stack-program-counter
	       (+f (-f stack-program-counter 1)
		   (relative-code-constant 0))))
	(t
	 (incff stack-program-counter 2))))




;;; The stack-instruction-emitter `branch-long-if-not-true' takes a
;;; byte-code-stream and an address and emits byte codes and address
;;; registrations.

(def-stack-instruction-emitter branch-long-if-not-true
       (byte-code-stream target-tag-statement)
  (register-byte-code-tag-resolution-point
    byte-code-stream target-tag-statement)
  (emit-instruction-byte-code byte-code-stream 'branch-long-if-not-true)
  (write-byte-code-to-stream byte-code-stream 0)
  (write-byte-code-to-stream byte-code-stream 0))

(def-byte-code-resolver branch-long-if-not-true
			(byte-code-stream byte-vector address tag)
  (declare (ignore byte-code-stream))
  (let* ((tag-address (instruction-address-for-tag tag nil))
	 (relative-offset (-f tag-address address)))
    (cond ((<f tag-address 256)
	   (setf (byte-vector-aref byte-vector address)
		 (op-code-for-stack-instruction 'branch-if-not-true))
	   (setf (byte-vector-aref byte-vector (+f address 1))
		 tag-address))
	  ((relative-code-constant-p relative-offset)
	   (setf (byte-vector-aref byte-vector address)
		 (op-code-for-stack-instruction 'branch-relative-if-not-true))
	   (setf (relative-code-constant-in-byte-vector
		   byte-vector (+f address 1))
		 relative-offset))
	  (t
	   (setf (long-code-constant-in-byte-vector byte-vector (+f address 1))
		 tag-address)))))




;;; The functions `call-stack-instruction-emitter branch-long-if-not-false' and
;;; `call-stack-instruction-emitter branch-long-if-false' take a byte-code-stream and an address
;;; and emits byte codes and address registrations.

;; Note that this is WRONG!!!  -jra

(def-stack-instruction-emitter branch-long-if-not-false
			       (byte-code-stream target-tag)
  (emit-instruction-byte-code byte-code-stream 'not)
  (call-stack-instruction-emitter branch-long-if-not-true byte-code-stream target-tag))

(def-stack-instruction-emitter branch-long-if-false (byte-code-stream target-tag)
  (emit-instruction-byte-code byte-code-stream 'not)
  (call-stack-instruction-emitter branch-long-if-true byte-code-stream target-tag))




;;; The stack-instruction-emitter `branch-long-if-true' takes a byte-code-stream
;;; and an address and emits bytes codes to branch to that tag if the value on the
;;; top of the stack is true.

;; Note that for the moment, this emits several instructions.  We should implement
;; a real branch if true instruction.  -jra 5/29/91

(def-stack-instruction-emitter branch-long-if-true (byte-code-stream target-tag)
  (let ((new-tag (generate-new-goto-tag)))
    (call-stack-instruction-emitter branch-long-if-not-true byte-code-stream new-tag)
    (call-stack-instruction-emitter branch-long byte-code-stream target-tag)
    (register-tag-in-byte-code-stream byte-code-stream new-tag)))



;;; Instruction 7, the `PUSH-CONSTANT stack instruction' takes a one byte index
;;; into the constant vector, identifying the constant to be pushed onto the top
;;; of the stack.  The constant vector will contain an evaluation-value.

;;; PUSH-CONSTANT (constant-index)

(def-stack-instruction (push-constant 7 2 nil print-op-and-constant)
  (setq fixnum-register-1 (code-constant 0))
  (incff top-of-stack)
  (setq register-1 (svref constant-vector fixnum-register-1))
  (setq register-1 (copy-evaluation-value register-1))
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter))




;;; Instruction 8, the `PUSH-CONSTANT-LONG stack instruction' takes two
;;; arguments, the high byte and the low byte of an index into the constant
;;; vector.  This identifies a constant to push onto the top of the stack.  The
;;; constant vector will contain an evaluation-value.

;;; PUSH-CONSTANT-LONG (high-byte-constant-index, low-byte-constant-index)

(def-stack-instruction (push-constant-long 8 3 nil
			 print-op-and-constant-long)
  (setq fixnum-register-1 (long-code-constant 0))
  (incff top-of-stack)
  (setq register-1 (svref constant-vector fixnum-register-1))
  (setq register-1 (copy-evaluation-value register-1))
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 2))




;;; Instruction 9, the `PUSH-SMALL-INTEGER stack instruction' takes one
;;; argument, which is an integer to push onto the stack, offset by 128.

;;; PUSH-SMALL-INTEGER (integer-plus-128)

(def-stack-instruction (push-small-integer 9 2 nil
			print-op-and-relative-code-constant)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(make-evaluation-integer (relative-code-constant 0)))
  (incff stack-program-counter))




;;; Instruction 10, the `PUSH-TRUE stack instruction' pushes true onto
;;; the top of the stack.

;;; Instruction 11, the `PUSH-FALSE stack instruction' pushes falsity
;;; onto the top of the stack.

;;; Instruction 12, the `PUSH-ZERO stack instruction' pushes an integer
;;; zero onto the stack.

;;; Instruction 13, the `PUSH-ONE stack instruction' pushes the integer
;;; 1 onto the top of the stack.

;;; Instruction 14, the `PUSH-NONE stack instruction' pushes the symbol
;;; NIL onto the top of the stack.

;;;   PUSH-TRUE ()
;;;   PUSH-FALSE ()
;;;   PUSH-ZERO ()
;;;   PUSH-ONE ()
;;;   PUSH-NONE ()

(def-stack-instruction (push-true 10 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(make-evaluation-truth-value truth)))

(def-stack-instruction (push-false 11 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(make-evaluation-truth-value falsity)))

(def-stack-instruction (push-zero 12 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(make-evaluation-integer 0)))

(def-stack-instruction (push-one 13 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(make-evaluation-integer 1)))

(def-stack-instruction (push-none 14 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(make-evaluation-symbol nil)))




;;; The stack-instruction-emitter `push-constant' takes a byte-code-stream and an
;;; evaluation-value which needs to be pushed onto the stack.

;; The instructions "push-none" and "push-t" should be removed or renamed.  T and
;; NIL are Lisp terms, not G2 terms, and so there should not be instructions
;; which name these things.  Remember that our users will read disassembled
;; code.  A "push-none" instruction might be better for the NIL case, but I
;; can't think of why T would get pushed.  Maybe we need another instruction,
;; push-internal-constant, which takes Lisp forms.  So far, each instruction
;; which needs a Lisp constant pushed does it itself.  -jra 4/1/91

;; "Push-nil" is now "push-none".  "Push-t" has been removed and will be
;; replaced by calls to push-constant.  cpm, 4/9/91

(def-stack-instruction-emitter push-constant (byte-code-stream evaluation-value)
  (cond ((and (evaluation-integer-p evaluation-value)
	      (relative-code-constant-p
		(evaluation-integer-value evaluation-value)))
	 (case (evaluation-integer-value evaluation-value)
	   ((0)
	    (emit-instruction-byte-code byte-code-stream 'push-zero))
	   ((1)
	    (emit-instruction-byte-code byte-code-stream 'push-one))
	   (t
	    (emit-instruction-byte-code byte-code-stream 'push-small-integer)
	    (emit-relative-code-constant-to-stream
	      byte-code-stream (evaluation-integer-value evaluation-value)))))
	((and (evaluation-truth-value-p evaluation-value)
	      (=f (evaluation-truth-value-value evaluation-value) truth))
	 (emit-instruction-byte-code byte-code-stream 'push-true))
	((and (evaluation-truth-value-p evaluation-value)
	      (=f (evaluation-truth-value-value evaluation-value) falsity))
	 (emit-instruction-byte-code byte-code-stream 'push-false))
	((null evaluation-value)
	 (emit-instruction-byte-code byte-code-stream 'push-none))
	(t
	 (let ((index (register-constant-in-byte-code-stream
			byte-code-stream evaluation-value)))
	   (cond ((<f index 255)
		  (emit-instruction-byte-code byte-code-stream 'push-constant)
		  (write-byte-code-to-stream byte-code-stream index))
		 (t
		  (emit-instruction-byte-code
		    byte-code-stream 'push-constant-long)
		  (emit-long-code-constant-to-stream byte-code-stream index)))))))




;;; Instruction 15, the `PUSH-INTERNAL-CONSTANT stack instruction' takes a one
;;; byte index into the constant vector, identifying the internal constant to be
;;; pushed onto the top of the stack.  This constant vector value is a lisp
;;; form, not an evaluation value.  Note that this constant value is not copied
;;; as it is put onto the stack.

;;; PUSH-INTERNAL-CONSTANT (constant-index)

;; This instruction should be removed if no longer used!! cpm, 6/18/91

(def-stack-instruction (push-internal-constant 15 2 nil print-op-and-constant)
  (setq fixnum-register-1 (code-constant 0))
  (incff top-of-stack)
  (setq register-1 (svref constant-vector fixnum-register-1))
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter))



;;; Instruction 16, the `PUSH-INTERNAL-CONSTANT-LONG stack instruction' takes
;;; two arguments, the high byte and the low byte of an index into the constant
;;; vector.  This identifies a constant to push onto the top of the stack.  This
;;; constant vector value is a lisp form, not an evaluation value.  Note that
;;; this constant value is not copied as it is put onto the stack.

;;; PUSH-INTERNAL-CONSTANT-LONG (high-byte-constant-index,
;;; low-byte-constant-index)

;; This instruction should be removed if no longer used!! cpm, 6/18/91

(def-stack-instruction (push-internal-constant-long 16 3 nil
			print-op-and-constant-long)
  (setq fixnum-register-1 (long-code-constant 0))
  (incff top-of-stack)
  (setq register-1 (svref constant-vector fixnum-register-1))
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 2))



;;; The stack-instruction-emitter `push-internal-constant' takes a
;;; byte-code-stream and an internal-constant (i.e., a lisp-form, not an
;;; evaluation-value) which needs to be pushed onto the stack.

(def-stack-instruction-emitter push-internal-constant 
			       (byte-code-stream slot-value)
  (let ((index (register-internal-constant-in-byte-code-stream
		 byte-code-stream slot-value)))
    (cond ((<f index 255)
	   (emit-instruction-byte-code byte-code-stream 'push-internal-constant)
	   (write-byte-code-to-stream byte-code-stream index))
	  (t
	   (emit-instruction-byte-code
	     byte-code-stream 'push-internal-constant-long)
	   (emit-long-code-constant-to-stream byte-code-stream index)))))




;;; Instruction 17, the `RESET-EXPIRATION stack instruction' resets the global
;;; expiration variable to NEVER.

;;; RESET-EXPIRATION ()

(def-stack-instruction (reset-expiration 17 1)
  (setq stack-expiration 'never))




;;; Instruction 18, the `BRANCH-IF-KNOWN stack instruction' takes one byte of
;;; instruction address to branch to if the global expiration is known.  Note
;;; that there is one byte of padding in this instruction to make it the same
;;; length as BRANCH-LONG-IF-KNOWN.

;;; BRANCH-IF-KNOWN (program-counter, unused-byte)

(def-stack-instruction (branch-if-known 18 3 nil
			 print-op-and-code-constant
			 pprint-branch-if-known-instruction)
  (if stack-expiration
      (setq stack-program-counter (code-constant 0))
      (incff stack-program-counter 2)))




;;; Instruction 19, the `BRANCH-LONG-IF-KNOWN stack instruction' takes two
;;; bytes of code constant which combine to make a long instruction address, and
;;; will branch to that address if the global expiration is known.

;;; BRANCH-LONG-IF-KNOWN (high-byte-pc, low-byte-pc)

(def-stack-instruction (branch-long-if-known 19 3 nil
			 print-op-and-long-code-constant
			 pprint-branch-long-if-known-instruction)
  (if stack-expiration
      (setq stack-program-counter (long-code-constant 0))
      (incff stack-program-counter 2)))




;;; Instruction 20, the `BRANCH-RELATIVE-IF-KNOWN stack instruction' takes a one
;;; byte relative address, which has been offset by 128.  This instruction will
;;; branch relative to the current instruction by the given argument minus 128
;;; if the global expiration is known.  Note that this is one byte of padding to
;;; the end of the instruction to make it the same length as
;;; BRANCH-LONG-IF-KNOWN.

;;; BRANCH-RELATIVE-IF-KNOWN (relative-pc-plus-128, unused-byte)

(def-stack-instruction (branch-relative-if-known 20 3 nil
			 print-op-and-relative-code-constant-address
			 pprint-branch-relative-if-known-instruction)
  (cond (stack-expiration
	 (setq fixnum-register-1 (relative-code-constant 0))
	 (setq stack-program-counter
	       (+f (-f stack-program-counter 1)
		   fixnum-register-1)))
	(t
	 (incff stack-program-counter 2))))




;;; The stack-instruction-emitter `branch-long-if-known' takes a byte-code-stream
;;; and an address and emits byte codes and address registrations.

(def-stack-instruction-emitter branch-long-if-known
			       (byte-code-stream target-tag)
  (register-byte-code-tag-resolution-point
    byte-code-stream target-tag)
  (emit-instruction-byte-code byte-code-stream 'branch-long-if-known)
  (write-byte-code-to-stream byte-code-stream 0)
  (write-byte-code-to-stream byte-code-stream 0))

(def-byte-code-resolver branch-long-if-known
			(byte-code-stream byte-vector address tag)
  (declare (ignore byte-code-stream))
  (let* ((tag-address (instruction-address-for-tag tag nil))
	 (relative-offset (-f tag-address address)))
    (cond ((<f tag-address 256)
	   (setf (byte-vector-aref byte-vector address)
		 (op-code-for-stack-instruction 'branch-if-known))
	   (setf (byte-vector-aref byte-vector (+f address 1))
		 tag-address))
	  ((relative-code-constant-p relative-offset)
	   (setf (byte-vector-aref byte-vector address)
		 (op-code-for-stack-instruction 'branch-relative-if-known))
	   (setf (relative-code-constant-in-byte-vector
		   byte-vector (+f address 1))
		 relative-offset))
	  (t
	   (setf (long-code-constant-in-byte-vector byte-vector (+f address 1))
		 tag-address)))))




;;; Instruction 21, the `PUSH-EXPIRATION stack instruction' pushes the global
;;; expiration onto the top of the stack.

;; The following will have to be rewritten when evaluation-integers become
;; managed values, or when expirations become floats.  -jra 4/29/91

;;;   PUSH-EXPIRATION ()

(def-stack-instruction (push-expiration 21 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) stack-expiration))




;;; Instruction 22, the `POP-EXPIRATION stack instruction' pops a value off the
;;; top of the stack into the global expiration.

;; The following will have to be rewritten when evaluation-integers become
;; managed values, or when expirations become floats.  -jra 4/29/91

;;;   POP-EXPIRATION ()

(def-stack-instruction (pop-expiration 22 1 1)
  (setq stack-expiration (arg 0))
  (decff top-of-stack))




;;; Instruction 23, the `MINIMIZE-EXPIRATION stack instruction', pops a value
;;; off the top of the stack, minimizes it with the expiration stored in the
;;; global expiration variable, and returns the minimum to the global expiration
;;; variable.

;;;   MINIMIZE-EXPIRATION ()

(def-stack-instruction (minimize-expiration 23 1 1)
  (setq register-1 (arg 0))
  (setq stack-expiration (minimum-expiration stack-expiration register-1))
  (decff top-of-stack))




;;; Instruction 24, the `POP stack instruction' pops one value off the stack and
;;; discards it.  Note that if the value is a string it must be recycled.  Since
;;; the stack location could point to a temporary float, it should be reset to
;;; NIL.

;;; POP ()

(def-stack-instruction (pop 24 1)
  (setq register-1 (svref local-stack top-of-stack))
  (reclaim-if-evaluation-value register-1)
  (decff top-of-stack))


(def-stack-instruction-emitter pop-stack (byte-code-stream)
  (emit-instruction-byte-code byte-code-stream 'pop))



;;; Instruction 25, the `POP-VALUES stack instruction' takes one code constant
;;; argument and pops that many values off the stack.  If any of the values are
;;; evaluation values, then they should be reclaimed.  Note that if any compiled
;;; code needs to pop more than 255 values (a very unlikely condition), then it
;;; must emit multiple calls to POP-VALUES.

;;; POP-VALUES (number-of-values-to-pop)

(def-stack-instruction (pop-values 25 2 nil print-op-and-code-constant)
  (setq fixnum-register-1 (code-constant 0))
  (loop while (>f fixnum-register-1 0)
	do
    (setq register-1 (svref local-stack top-of-stack))
    (reclaim-if-evaluation-value register-1)
    (decff fixnum-register-1)
    (decff top-of-stack))
  (incff stack-program-counter))




;;; The stack-instruction-emitter `pop-values' takes a byte code stream and a
;;; number of values to pop off the stack.  This function will emit as many
;;; calls to pop-values as it needs to get them all.

(def-stack-instruction-emitter pop-values (byte-code-stream values-to-pop)
  (when (<f values-to-pop 0)
    (compiler-bug
      "pop-values stack instruction emitter"
      "Trying to pop ~a values, can't pop less than zero." values-to-pop)
    (setq values-to-pop 0))
  (multiple-value-bind (overflows remainder)
      (floorf-positive-2 values-to-pop 255)
    (loop repeat overflows do
      (emit-instruction-byte-code byte-code-stream 'pop-values)
      (write-byte-code-to-stream byte-code-stream 255))
    (cond ((=f remainder 1)
	   (emit-instruction-byte-code byte-code-stream 'pop))
	  ((>f remainder 0)
	   (emit-instruction-byte-code byte-code-stream 'pop-values)
	   (write-byte-code-to-stream byte-code-stream remainder)))))




;;; Instruction 26, the `POP-INTO-STACK-FRAME-VAR stack instruction' takes a one
;;; byte index into the stack frame and pops the value off the top of the stack
;;; into that location.  The old value in the location should be reclaimed if it
;;; was an evaluation value.

;;;   POP-INTO-STACK-FRAME-VAR (stack-frame-var-index)

(def-stack-instruction (pop-into-stack-frame-var 26 2 1
			print-op-and-code-constant)
  (setq fixnum-register-1 (code-constant 0))
  (setq fixnum-register-2 (stack-frame-local-var-stack-index fixnum-register-1))
  (setq register-1 (svref local-stack fixnum-register-2))
  (setf (svref local-stack fixnum-register-2) (arg 0))
  (reclaim-if-evaluation-value register-1)
  (decff top-of-stack)
  (incff stack-program-counter))

(defun-simple emit-typecode-to-stream
    (byte-code-stream var-spot)
  (let ((typecode (gensym-type-to-typecode
		    (var-spot-type var-spot lexically-visible-code-bodies))))
    (write-byte-code-to-stream byte-code-stream typecode)))

;;; We want to do a case on the type, rather than a typep, so that
;;; we don't slow down Interpreted byte-code too much. So instead of
;;; an arbitrary type, we translate into a typecode. Put specific types
;;; before general ones on this list, since it returns the first supertype
;;; of the input type that it finds.

;;; In the bytecode-to-C compiler, types are encoded as single
;;; bytes, so that they can be immediate data on the instruction stack,
;;; rather than pointers into the constant vector.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant nil-typecode 0)
(defconstant integer-typecode 1)
(defconstant float-typecode 2)
(defconstant symbol-typecode 3)
(defconstant truth-value-typecode 4)
(defconstant text-typecode 5)
(defconstant item-typecode 6)
(defconstant iteration-state-typecode 7)
(defconstant defined-evaluation-type-typecode 8)
(defconstant evaluation-type-typecode 9)
(defconstant item-or-datum-typecode 10)
(defconstant anything-typecode 11)
(defconstant sequence-typecode 12)
(defconstant structure-typecode 13)
(defconstant long-typecode 14)
(defconstant or-nil-typecode-modifier 32)
)
;;; What about no-value?

(defun-simple simple-typecode-to-text (typecode)
  (fixnum-case typecode
    (0 "null")
    (1 "integer")
    (2 "float")
    (3 "symbol")
    (4 "truth-value")
    (5 "text")
    (6 "item")
    (7 "iteration state")
    (8 "defined valuation type")
    (9 "evaluation type")
    (10 "item or datum")
    (11 "object of unknown type")
    (12 "sequence type")
    (13 "structure type")
    (14 "long")
    (otherwise "unrecognized typecode")))

(defun-void twrite-typecode (typecode)
  (if (<f typecode or-nil-typecode-modifier)
      (let ((s (simple-typecode-to-text typecode)))
	(twrite (supply-a-or-an s))
	(twrite s))
      (progn
	(twrite "either null or ")
	(twrite (-f typecode or-nil-typecode-modifier)))))

;;; It's important that this list contain subtypes before their supertypes,
;;; since the function that uses it returns the first match.

(defparameter types-and-typecodes
  '(((no-item) #.nil-typecode)
    (integer #.integer-typecode)
    (long #.long-typecode)
    (float #.float-typecode)
    (symbol #.symbol-typecode)
    (truth-value #.truth-value-typecode)
    (text #.text-typecode)
    ((class item) #.item-typecode)
    ((iteration-state) #.iteration-state-typecode)
    ((sequence) #.sequence-typecode)
    ((structure) #.structure-typecode)
    ((and evaluation-value;below added by SoftServe
      (not (or integer long float symbol truth-value text (iteration-state))))
     #.defined-evaluation-type-typecode)
    (evaluation-value #.evaluation-type-typecode)
    (item-or-datum #.item-or-datum-typecode)))

(defparameter no-information-typecode (+ #.item-or-datum-typecode
					 #.or-nil-typecode-modifier))

(defvar use-type-info t)
    
(defun-simple gensym-type-to-typecode (type)
  (if use-type-info
      (progn
	(dolist (pair types-and-typecodes)
	  (when (type-specification-subtype-p type (first pair))
	    (return-from gensym-type-to-typecode (second pair))))
	(dolist (pair types-and-typecodes)
	  (when (type-specification-subtype-p
		  type
		  (make-type-specification-union (first pair) '(no-item)))
	    (return-from gensym-type-to-typecode
	      (+f or-nil-typecode-modifier (second pair)))))
	anything-typecode)
      anything-typecode))


;;; Even if the type returned by var-spot-type says that the value can't
;;; be nil, Rick suspects that the value at runtime still can be nil.
;;; So don't elide the nil checks.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar always-make-runtime-nil-checks t))

(defun-for-macro copy-if-evaluation-value-given-typecode-case-clauses
    (var typecodes nil-forms &rest non-nil-forms)
  (if always-make-runtime-nil-checks
      `(((,@(if (atom typecodes)
		(list (+f or-nil-typecode-modifier typecodes))
		(loop for typecode in typecodes collecting
		      (+f or-nil-typecode-modifier typecode)))
	    ,@(if (atom typecodes) (list typecodes) typecodes))
	 ;; don't test for nil if you are doing the same thing in either case.
	 ,(if (and (or (null nil-forms)
		       (and (null (cdr nil-forms))
			    (null (car nil-forms))))
		   (or (null non-nil-forms)
		       (and (null (cdr nil-forms))
			    (null (car non-nil-forms)))))
	      nil
	      `(if (null ,var)
		   (progn ,@nil-forms)
		   (progn ,@non-nil-forms)))))
      `((,(if (atom typecodes)
	      (+f or-nil-typecode-modifier typecodes)
	      (loop for typecode in typecodes collecting
		    (+ or-nil-typecode-modifier typecode)))
	  ;; don't test for nil if you are doing the same thing in either case.
	  ,(if (and (or (null nil-forms)
			(and (null (cdr nil-forms))
			     (null (car nil-forms))))
		    (or (null non-nil-forms)
			(and (null (cdr nil-forms))
			     (null (car non-nil-forms)))))
	       nil
	       `(if (null ,var)
		    (progn ,@nil-forms)
		    (progn ,@non-nil-forms))))
	(,typecodes
	   (progn ,@non-nil-forms)))))

(defmacro copy-if-evaluation-value-given-typecode-err-on-nil
    (var typecode &rest nil-forms)
  `(case (the (signed-byte 8) ,typecode)
     (#.nil-typecode ,@nil-forms)
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var `(,integer-typecode ,symbol-typecode ,item-typecode) nil-forms nil)
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var truth-value-typecode nil-forms
	`(setq ,var (copy-evaluation-truth-value ,var)))
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var iteration-state-typecode nil-forms
	`(setq ,var (copy-evaluation-iteration-state ,var)))
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var sequence-typecode nil-forms
	`(setq ,var (copy-evaluation-sequence ,var)))
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var structure-typecode nil-forms
	`(setq ,var (copy-evaluation-structure ,var)))
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var defined-evaluation-type-typecode nil-forms
	`(setq ,var (funcall-simple-compiled-function
		      (defined-evaluation-type-copier (cdr ,var))
		      ,var)))
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var float-typecode nil-forms
	`(setq ,var (copy-evaluation-float ,var)))
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var long-typecode nil-forms
	`(setq ,var (copy-evaluation-long ,var)))
    ,@(copy-if-evaluation-value-given-typecode-case-clauses
	var text-typecode nil-forms
	`(setq ,var (copy-evaluation-text ,var)))
    (t (if (null ,var)
	   (progn ,@nil-forms)
	   (setq ,var (copy-if-evaluation-value ,var))))))

(defun-for-macro reclaim-if-evaluation-value-given-typecode-case-clauses
    (var typecodes &rest reclaim-forms)
  (if always-make-runtime-nil-checks
      `(((,@(if (atom typecodes)
		(list (+f or-nil-typecode-modifier typecodes))
		(loop for typecode in typecodes collecting
		      (+f or-nil-typecode-modifier typecode)))
	    ,@(if (atom typecodes) (list typecodes) typecodes))
	 ;; don't test for nil if you are doing the same thing in either case.
	 ,(if (or (null reclaim-forms)
		  (and (null (car reclaim-forms))
		       (null (cdr reclaim-forms))))
	      nil
	      `(unless (null ,var)
		 ,@reclaim-forms))))
      `((,(if (atom typecodes)
	      (+f or-nil-typecode-modifier typecodes)
	      (loop for typecode in typecodes collecting
		    (+ or-nil-typecode-modifier typecode)))
	  ;; don't test for nil if you are doing the same thing in either case.
	  ,(if (or (null reclaim-forms)
		   (and (null (car reclaim-forms))
			(null (cdr reclaim-forms))))
	       nil
	       `(unless (null ,var)
		  ,@reclaim-forms)))
	(,typecodes
	 (progn ,@reclaim-forms)))))
      
(defmacro reclaim-if-evaluation-value-given-typecode (var typecode)
  `(case (the (signed-byte 8) ,typecode)
     (#.nil-typecode nil)
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 `(,integer-typecode ,symbol-typecode ,item-typecode)
	 nil)
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 float-typecode
	 `(reclaim-evaluation-float ,var))
     ;added by SoftServe
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 long-typecode
	 `(reclaim-evaluation-long ,var))                
     ;end of SoftServe changes                      
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 truth-value-typecode
	 `(reclaim-evaluation-truth-value ,var))
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 text-typecode
	 `(reclaim-evaluation-text ,var))
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 iteration-state-typecode
	 `(reclaim-evaluation-iteration-state ,var))
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 sequence-typecode
	 `(reclaim-evaluation-sequence ,var))
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 structure-typecode
	 `(reclaim-evaluation-structure ,var))
     ,@(reclaim-if-evaluation-value-given-typecode-case-clauses
	 var
	 defined-evaluation-type-typecode
	 `(funcall-simple-compiled-function
	   (defined-evaluation-type-reclaimer (cdr ,var))
	   ,var))
     (t (reclaim-if-evaluation-value ,var))))

;;; Instruction 27, the `PUSH-FROM-STACK-FRAME-VAR stack instruction' takes a
;;; one byte index into the stack frame and pushes the value stored in the that
;;; stack frame variable onto the top of the stack.
;;; The one-byte index
;;; is followed by a 1-byte immediate value, giving a typecode indicating
;;; the type of the object to be pushed.

;;;   PUSH-FROM-STACK-FRAME-VAR (stack-frame-var-index)

(def-stack-instruction-emitter push-from-stack-frame-var
			       (byte-code-stream var-spot)
  (emit-instruction-byte-code byte-code-stream
			      'push-from-stack-frame-var)
  (write-byte-code-to-stream byte-code-stream (second var-spot))
  (emit-typecode-to-stream byte-code-stream var-spot))

(defun signal-stack-type-check-error-message (value type top-of-stack)
  (twith-output-to-error-text top-of-stack
    (cond ((null value)
	   (tformat
	     "Nothing was returned from an expression which should have ~
              returned a value of the type ~NT."
	     type))
	  (t
	   (cond ((and (not (evaluation-long-p value)) (framep value))
		  (tformat "~NF" value))
		 ((evaluation-value-p value)
		  (write-evaluation-value value))
		 (t
		  (twrite-string "<internal data>")))
	   (tformat
	     " is being given to an operation which requires values of the ~
              type ~NT."
	     type)))))

(defmacro signal-stack-type-check-error (value type top-of-stack)
  `(raw-stack-error-named-error
     ,top-of-stack
     (signal-stack-type-check-error-message ,value ,type ,top-of-stack)))

(def-stack-instruction (push-from-stack-frame-var 27 3 nil
			print-op-and-code-constant-and-typecode)
  (setq fixnum-register-1 (code-constant 0))
  (setq register-1 (stack-frame-local-var fixnum-register-1))
  (setq fixnum-register-1 (code-constant 1))
  (copy-if-evaluation-value-given-typecode-err-on-nil
    register-1 fixnum-register-1
    (signal-stack-type-check-error register-1 'item-or-value top-of-stack))
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 2))

;;; Instruction 121, the `PUSH-VALUE-OR-NONE-FROM-STACK-FRAME-VAR stack
;;; instruction' takes a one byte index into the stack frame and pushes the
;;; value stored in the that stack frame variable onto the top of the stack,
;;; even if the stored value is NIL.

;;;   PUSH-VALUE-OR-NONE-FROM-STACK-FRAME-VAR (stack-frame-var-index)

(def-stack-instruction (push-value-or-none-from-stack-frame-var 121 3 nil
			print-op-and-code-constant-and-typecode)
  (incff top-of-stack)
  (setq fixnum-register-1 (code-constant 0))
  (setq register-1 (stack-frame-local-var fixnum-register-1))
  (setq fixnum-register-1 (code-constant 1))
  (copy-if-evaluation-value-given-typecode-err-on-nil
    register-1 fixnum-register-1 nil)
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 2))

(def-stack-instruction-emitter push-value-or-none-from-stack-frame-var
			       (byte-code-stream var-spot)
  (emit-instruction-byte-code
    byte-code-stream 'push-value-or-none-from-stack-frame-var)
  (write-byte-code-to-stream byte-code-stream (second var-spot))
  (emit-typecode-to-stream byte-code-stream var-spot))




;;; Instruction 28, the `POP-INTO-STACK-ARG stack instruction' takes a one byte
;;; index into the argument list for a stack frame and pops the value on the top
;;; of the stack off into the argument's location on the stack.  Note that
;;; operation is necessary since we allow mutation of argument variables in
;;; procedures.

;;; Note further that this instruction will only be needed when we have
;;; implemented calls to wait-state-free procedures on the stack.  -jra 3/2/91

;;; POP-INTO-STACK-ARG (argument-index)

(def-stack-instruction (pop-into-stack-arg 28 2 1
			print-op-and-code-constant)
  (setq fixnum-register-1 (code-constant 0))
  (setq fixnum-register-2 (stack-frame-arg-stack-index fixnum-register-1))
  (setq register-1 (svref local-stack fixnum-register-2))
  (setf (svref local-stack fixnum-register-2) (arg 0))
  (reclaim-if-evaluation-value register-1)
  (decff top-of-stack)
  (incff stack-program-counter))

(def-stack-instruction-emitter pop-into-stack-arg (byte-code-stream index)
  (emit-instruction-byte-code byte-code-stream 'pop-into-stack-arg)
  (write-byte-code-to-stream byte-code-stream index))




;;; Instruction 29, the `PUSH-FROM-STACK-ARG stack instruction' takes a one byte
;;; index into the argument list for a stack frame and pushes the value stored
;;; in that location onto the top of the stack.

;;; PUSH-FROM-STACK-ARG (argument-index)

(def-stack-instruction (push-from-stack-arg 29 3 nil
			 print-op-and-code-constant-and-typecode
			 pprint-push-from-stack-arg-instruction)
  (setq register-1 (stack-frame-arg (code-constant 0)))
  (setq fixnum-register-1 (code-constant 1))
  (copy-if-evaluation-value-given-typecode-err-on-nil
    register-1 fixnum-register-1
    (signal-stack-type-check-error register-1 'item-or-value top-of-stack))
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 2))

(def-stack-instruction-emitter push-from-stack-arg (byte-code-stream var-spot)
  (emit-instruction-byte-code byte-code-stream 'push-from-stack-arg)
  (write-byte-code-to-stream byte-code-stream (second var-spot))
  (emit-typecode-to-stream byte-code-stream var-spot))




;;; Instruction 122, the `PUSH-VALUE-OR-NONE-FROM-STACK-ARG stack instruction'
;;; takes a one byte index into the argument list for a stack frame and pushes
;;; the value stored in that location onto the top of the stack, even if the
;;; stored value is NIL.

;;; PUSH-VALUE-OR-NONE-FROM-STACK-ARG (argument-index)

(def-stack-instruction (push-value-or-none-from-stack-arg 122 3 nil
			 print-op-and-code-constant-and-typecode
			 pprint-push-from-stack-arg-instruction)
  (incff top-of-stack)
  (setq register-1 (stack-frame-arg (code-constant 0)))
  (setq fixnum-register-1 (code-constant 1))
  (copy-if-evaluation-value-given-typecode-err-on-nil
    register-1 fixnum-register-1 nil)
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 2))

(def-stack-instruction-emitter push-value-or-none-from-stack-arg
			       (byte-code-stream var-spot)
  (emit-instruction-byte-code
    byte-code-stream 'push-value-or-none-from-stack-arg)
  (write-byte-code-to-stream byte-code-stream (second var-spot))
  (emit-typecode-to-stream byte-code-stream var-spot))

;;; The function `case-dispatch-byte-count' computes the number of bytes that a
;;; CASE-DISPATCH instruction occupies.

(defun case-dispatch-byte-count (address raw-byte-vector constant-vector)
  (declare (ignore constant-vector))
  (+f 7 (*f 2 (long-code-constant-in-byte-vector
		raw-byte-vector
		(+f address 3)))))




;;; Instruction 30, the `CASE-DISPATCH stack instruction' performs multi-way
;;; branches based on an integer popped off the stack.  This instruction takes
;;; at least three long code constants, and then a table of long code constants
;;; which are a table of addresses.  The first long code constant is an integer
;;; which is the number of the lowest entry in the address table.  The second
;;; long code constant is the length of that table.  The third long code
;;; constant is an address to branch to if the integer popped off the stack is
;;; out of range of the given table base and length.  After the else address is
;;; a set of long code constants, table-length long, which is the table of
;;; addresses.

;; Note that this instruction will have to be editted if evaluation-integers
;; need reclaimation.  -jra 4/4/91

;;; CASE-DISPATCH (high-table-base, low-table-base,
;;;                high-table-length, low-table-length,
;;;                high-else-address, low-else-address,
;;;                <table-length * 2 bytes of target addresses>)

(def-stack-instruction (case-dispatch 30 case-dispatch-byte-count 1
			print-case-dispatch
			pprint-case-dispatch-instruction)
  (setq fixnum-register-1 (evaluation-integer-value (arg 0)))
  (decff top-of-stack)
  (setq fixnum-register-2 (long-code-constant 0))	; table base
  (setq register-1 (long-code-constant 1))		; table length
  (cond ((or (<f fixnum-register-1 fixnum-register-2)
	     (>=f fixnum-register-1 (+f fixnum-register-2 register-1)))
	 (setq stack-program-counter (long-code-constant 2)))
	(t
	 (setq fixnum-register-2
	       (+f (-f fixnum-register-1 fixnum-register-2)
		   3))
	 (if-emitting-c-code
	   (compiled-case-dispatch fixnum-register-2 3 (+f 3 register-1))
	   (setq stack-program-counter (long-code-constant fixnum-register-2))))))




;;; The emitter for case-dispatch instructions takes the byte code stream, the
;;; table base and length, a tag for the else instruction, and a list of tags
;;; (table-length long) which will form the table of addresses.  This emitter
;;; should write the table base and table length constants, and enough empty
;;; bytes to hold the else and table addresses at address resolution time.

;;; Note that if the table base is outside the range of long code constants,
;;; then this emitter will also emit an integer-plus instruction to offset the
;;; given integer back into a range that the table-base can handle, i.e.  0.

(def-stack-instruction-emitter case-dispatch
    (byte-code-stream table-base table-length else-tag tag-table)
  (unless (and (>=f table-base 0) (<=f table-base 65535))
    (call-stack-instruction-emitter push-constant byte-code-stream (-f table-base))
    (emit-operator-of-type byte-code-stream '+ 'integer)
    (setq table-base 0))
  (register-byte-code-tag-resolution-point
    byte-code-stream
    (compiler-cons
      else-tag
      (copy-list-using-compiler-conses tag-table)))
  (emit-instruction-byte-code byte-code-stream 'case-dispatch)
  (emit-long-code-constant-to-stream byte-code-stream table-base)
  (emit-long-code-constant-to-stream byte-code-stream table-length)
  (loop repeat (+f table-length 1) do
    (emit-long-code-constant-to-stream byte-code-stream 0)))




;;; The address resolver for the case dispatch instruction takes a list whose
;;; first element is the else tag and the rest of whose elements are the tag
;;; table.  This function looks up addresses for those tags and writes the
;;; addresses into the else-address and address-table in the constant vector.

(def-byte-code-resolver
  case-dispatch (byte-code-stream byte-vector address else-tag-and-table)
  (declare (ignore byte-code-stream))
  (loop for byte-address from (+f address 5) by 2
	for tag in else-tag-and-table
	do
    (setf (long-code-constant-in-byte-vector byte-vector byte-address)
	  (instruction-address-for-tag tag nil))))




;;; Instruction 31, the `TYPE-CHECK-TRUTH-VALUE stack instruction' tests the
;;; value at the top of the stack to ensure that it is a truth value.  If it is
;;; not, this instruction signals an error.  The instruction leaves the value on
;;; the top of the stack.

;;; TYPE-CHECK-TRUTH-VALUE ()

(def-stack-instruction (type-check-truth-value 31 1 1
			nil pprint-type-check-truth-value-instruction)
  (setq register-1 (arg 0))
  (unless (evaluation-truth-value-p register-1)
    (signal-stack-type-check-error register-1 'truth-value top-of-stack)))




;;; Instruction 32, the `TYPE-CHECK-SYMBOL stack instruction' tests the value at
;;; the top of the stack to ensure that it is a symbol.  If it is not, this
;;; instruction signals an error.  The instruction leaves the value on the top
;;; of the stack.

;;; TYPE-CHECK-SYMBOL ()

(def-stack-instruction (type-check-symbol 32 1 1
			nil pprint-type-check-symbol-instruction)
  (setq register-1 (arg 0))
  (unless (evaluation-symbol-p register-1)
    (signal-stack-type-check-error register-1 'symbol top-of-stack)))




;;; Instruction 33, the `TYPE-CHECK-TEXT stack instruction' tests the value at
;;; the top of the stack to ensure that it is a string.  If it is not, this
;;; instruction signals an error.  The instruction leaves the value on the top
;;; of the stack.

;;; TYPE-CHECK-TEXT ()

(def-stack-instruction (type-check-text 33 1 1
			nil pprint-type-check-text-instruction)
  (setq register-1 (arg 0))
  (unless (evaluation-text-p register-1)
    (signal-stack-type-check-error register-1 'text top-of-stack)))




;;; Instruction 34, the `TYPE-CHECK-QUANTITY stack instruction' tests the value
;;; at the top of the stack to ensure that it is a number.  If it is not, this
;;; instruction signals an error.  The instruction leaves the value on the top
;;; of the stack.

;;; TYPE-CHECK-QUANTITY ()

(def-stack-instruction (type-check-quantity 34 1 1
			nil pprint-type-check-quantity-instruction)
  (setq register-1 (arg 0))
  (unless (evaluation-quantity-p register-1)
    (signal-stack-type-check-error register-1 'number top-of-stack)))




;;; Instruction 35, the `TYPE-CHECK-INTEGER stack instruction' tests the value
;;; at the top of the stack to ensure that it is a integer.  If it is not, this
;;; instruction signals an error.  The instruction leaves the value on the top
;;; of the stack.

;;; TYPE-CHECK-INTEGER ()

(def-stack-instruction (type-check-integer 35 1 1
			nil pprint-type-check-integer-instruction)
  (setq register-1 (arg 0))
  (unless (evaluation-integer-p register-1)
    (signal-stack-type-check-error register-1 'integer top-of-stack)))




;;; Instruction 36, the `TYPE-CHECK-FLOAT stack instruction' tests the value at
;;; the top of the stack to ensure that it is a float.  If it is not, this
;;; instruction will attempt to coerce it to a float if it is an integer.  If
;;; not, it signals an error.  The instruction leaves the value on the top of
;;; the stack.

;;; TYPE-CHECK-FLOAT ()

(defun-simple attempt-to-coerce-to-gensym-float (thing)
  (cond ((evaluation-integer-p thing)
	 (make-evaluation-float
	   (coerce-fixnum-to-gensym-float
	     (the fixnum (evaluation-integer-value thing)))))
	((of-class-p thing 'parameter)
	 (let ((value (extract-number-or-value
			(current-value-of-variable-or-parameter thing)))
	       (type (type-specification-of-variable-or-parameter-value thing)))
	   (cond ((eq type 'truth-value)
		  (make-evaluation-float
		    (/e (coerce-fixnum-to-gensym-float (the fixnum value))
			#.(coerce-to-gensym-float truth))))
		 ((gensym-float-p value)
		  (make-evaluation-float value))
		 ((fixnump value)
		  (make-evaluation-float
		    (coerce-fixnum-to-gensym-float (the fixnum value))))
		 (t nil))))
	(t nil)))

(def-stack-instruction (type-check-float 36 1 1
			nil pprint-type-check-float-instruction)
  (setq register-1 (arg 0))
  (unless (evaluation-float-p register-1)
    (setq register-2 (attempt-to-coerce-to-gensym-float register-1))
    (cond (register-2
	   (reclaim-if-evaluation-value register-1)
	   (setf (arg 0) register-2))
	  (t
	   (signal-stack-type-check-error register-1 'float top-of-stack)))))




;;; The constant `classes-type-checked-inline' is used by the emitter and
;;; compiler for type type-check-class-inline instruction.  IF ANY CHANGE IS
;;; MADE TO THIS LIST OTHER THAN ADDING CLASSES AT THE END, THEN A RECOMPILE OF
;;; ALL USER KBS WILL BE NEEDED.  -jra 1/28/92

;; IMPORTANT NOTE ABOVE!! - cpm, 12/14/93

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant
  classes-type-checked-inline
  '(kb-frame
     temporary-workspace invisible-entity message-definition format-frame
     menu language-translation user-menu-choice generic-formula logical-variable
     float-variable integer-variable symbolic-variable text-variable
     logical-parameter quantitative-parameter integer-parameter float-parameter
     symbolic-parameter text-parameter forward-chaining-link
     true-value-update-recipient backward-chaining-link function-definition
     units-of-measure-declaration tabular-function-of-1-arg g2-cell-array
     g2-cell-array-cell g2-query-cell g2-designation-cell g2-expression-cell
     remote-procedure-declaration dial meter digital-clock graph-grid plot
     model-definition foreign-function-declaration external-simulation-definition
     authorized-user statement edit-box procedure-invocation
     logbook-page page menu-workspace category-instance-menu-workspace
     inspect-command icon-cell explanation-table text-box g2-login name-box
     category-menu scrap text-region kfep-conversion-choice-menu
     subordinate-text-box dialog-button connection-definition workspace-name-box
     definition dependent-frame non-kb-workspace connection-post message-board
     action-button chart default-junction ruling-for-dial pointer-for-dial
     ruling-for-meter marker-for-meter readout-table graph ok
     generic-simulation-formula object   
     procedure block variable-or-parameter relation simulation-subtable item
     kb-workspace table message loose-end parameter variable quantitative-variable
     slider-minimum-value-label rule question-mark-box slider-readout button-label
     slider-needle type-in-text-box button generic-action-button type-in-box
     arrow-button g2-window connection entity workspace icon-editor-workspace
     object-definition icon-editor-table-info-frame bounding-box tabular-function
     g2-list item-list integer-list float-list quantity-list symbol-list text-list
     truth-value-list
     g2-array item-array integer-array float-array quantity-array symbol-array
     text-array truth-value-array
     value-list
     value-array)))


;;; Instruction 37, the `TYPE-CHECK-CLASS stack instruction' tests the value at
;;; the top of the stack to ensure that it is an instance of a class.  This
;;; instruction takes a code constant argument which indexes to a location in
;;; the constant vector which holds the symbol naming the class.

;;; TYPE-CHECK-CLASS (class-name-constant-index)

(def-stack-error signal-stack-class-type-check-error (thing class top-of-stack)
  (cond ((null thing)
	 "~A ~A ~A.")
	((framep thing)
	 "~NF ~A ~A.")
	((evaluation-symbol-p thing)
	 "The symbol ~NV ~A ~A.")
	((evaluation-value-p thing)
	 "~NV ~A ~A."))
  (if thing thing "None")
  "should have been an instance of the class"
  (if (fixnump class)
      (nth class classes-type-checked-inline)
      class))

(def-stack-instruction (type-check-class 37 2 1 print-op-and-constant
					 pprint-type-check-class-instruction)
  (setq register-1 (arg 0))
  (setq register-2 (svref constant-vector (code-constant 0)))
  (setq register-4 (of-class-p-function register-1 register-2))
  (unless register-4
    (signal-stack-class-type-check-error register-1 register-2 top-of-stack))
  (incff stack-program-counter))




(def-stack-instruction-emitter type-check-class (byte-code-stream class-name)
  (cond ((eq class-name 'item)
	 (emit-instruction-byte-code byte-code-stream 'type-check-item))
	((memq class-name classes-type-checked-inline)
	 (call-stack-instruction-emitter type-check-class-inline byte-code-stream class-name))
	(t
	 (let ((index (register-constant-in-byte-code-stream
			byte-code-stream class-name)))
	   (cond ((<f index 256)
		  (emit-instruction-byte-code
		    byte-code-stream 'type-check-class)
		  (write-byte-code-to-stream byte-code-stream index))
		 (t
		  (emit-instruction-byte-code
		    byte-code-stream 'type-check-class-long)
		  (emit-long-code-constant-to-stream
		    byte-code-stream index)))))))




;;; Instruction 38, the `TYPE-CHECK-CLASS-LONG stack instruction' tests the
;;; value at the top of the stack to ensure that it is an instance of the class
;;; name stored in the constant vector.  The index to the constant vector is
;;; given as a two byte entity.

;;; TYPE-CHECK-CLASS-LONG (hi-byte-constant-index, low-byte-constant-index)

(def-stack-instruction (type-check-class-long 38 3 1
			 print-op-and-constant-long
			 pprint-type-check-class-long-instruction)
  (setq register-1 (arg 0))
  (setq fixnum-register-1 (long-code-constant 0))
  (setq register-2 (svref constant-vector fixnum-register-1))
  (setq register-4 (of-class-p-function register-1 register-2))
  (unless register-4
    (signal-stack-class-type-check-error register-1 register-2 top-of-stack))
  (incff stack-program-counter 2))




;;; Instruction 39, the `TYPE-CHECK-ITEM-OR-DATUM stack instruction' tests that
;;; the value at the top of the stack is either an evaluation value, or an item.
;;; This is usually emitted after things like attribute fetches.

;;; TYPE-CHECK-ITEM-OR-DATUM ()

(def-stack-instruction (type-check-item-or-datum 39 1 1
			nil pprint-type-check-item-or-datum-instruction)
  (setq register-1 (arg 0))
  (unless (and register-1
	       (or (evaluation-datum-p-given-register register-1 register-3)
		   (thing-is-item-p register-1)))	       
    (signal-stack-type-check-error register-1 'item-or-datum top-of-stack)))




;;; The emitter for the pseudo-instruction `type-check' determines at compile
;;; time which type checking instruction to actually emit.

(def-stack-instruction-emitter type-check (byte-code-stream type)
  (cond ((not (valid-type-specification-p type))
	 (compiler-bug
	   "type check emitter"
	   "Invalid type ~a given to instruction emitter." type))
	((class-type-specification-p type)
	 (call-stack-instruction-emitter type-check-class
	   byte-code-stream
	   (type-specification-class type)))
	((memq type
	       '(item-or-datum truth-value symbol text number integer float))
	 (emit-instruction-byte-code
	   byte-code-stream
	   (case type
	     ((item-or-datum) 'type-check-item-or-datum)
	     ((truth-value) 'type-check-truth-value)
	     ((symbol) 'type-check-symbol)
	     ((text) 'type-check-text)
	     ((number) 'type-check-quantity)
	     ((integer) 'type-check-integer)
	     ((float) 'type-check-float))))
	((intersection-type-specification-p type)
	 (loop for subtype in (cdr type)
	       do
	   (call-stack-instruction-emitter type-check byte-code-stream subtype)))
	(t
	 (let ((constant-index
		 (register-internal-constant-in-byte-code-stream
		   byte-code-stream type)))
	   (emit-instruction-byte-code byte-code-stream 'type-check)
	   (emit-long-code-constant-to-stream
	     byte-code-stream constant-index)))))



(def-stack-error signal-nested-code-bodies-out-of-procedures (top-of-stack local-var-index)
  "An attempt was made to reference surrounding local var ~a.  This kind of ~
   reference should only happen within procedures."
  local-var-index)

;;; Instruction 40, the `POP-INTO-SURROUNDING-LOCAL-VAR stack instruction' takes
;;; a two byte index into the constant vector.  There it will find a var-spot
;;; which references a local-var, possibly in an environment of a surrounding
;;; code-body-invocation.  (Note that this instruction is also used for
;;; local-vars in the local environment when the index is longer than 255).
;;; This instruction will pop a value off the top of the stack and put it into
;;; the denoted local-var, reclaiming the old value in that local var if it is
;;; an evaluation value.

;;; POP-INTO-SURROUNDING-LOCAL-VAR (index-high-byte, index-low-byte)

(def-stack-instruction (pop-into-surrounding-local-var
			 40 4 1 print-op-and-surrounding-local-var-and-typecode
			 pprint-pop-into-surrounding-local-var-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  (setq fixnum-register-2 fixnum-register-1)
  (setq register-2 current-computation-instance)
  (setq fixnum-register-1 (var-spot-index-nesting fixnum-register-2))
  (cond ((pluspf fixnum-register-1)
	 (unless (code-body-invocation-p current-computation-instance)
	   (signal-nested-code-bodies-out-of-procedures
	     top-of-stack fixnum-register-2))
	 (loop while (pluspf fixnum-register-1) do
	   (setq register-2 (code-body-caller register-2))
	   (decff fixnum-register-1))
	 (setq register-2 (invocation-local-var-vector register-2))
	 (setq fixnum-register-1 (var-spot-local-index fixnum-register-2))
	 (setq register-3 (svref register-2 fixnum-register-1))
	 (setf (svref register-2 fixnum-register-1) (arg 0)))
	(t
	 (setq register-3 (svref local-var-vector fixnum-register-2))
	 (setf (svref local-var-vector fixnum-register-2) (arg 0))))
  (setf fixnum-register-1 (code-constant 2))
  (reclaim-if-evaluation-value-given-typecode register-3 fixnum-register-1)
  (incff stack-program-counter 3)
  (decff top-of-stack))

(def-stack-instruction-emitter pop-into-surrounding-local-var
			       (byte-code-stream var-spot)
  (unless (valid-var-spot-p var-spot)
    (compiler-bug
      "pop-into-local-var emitter"
      "An invalid var spot, ~a, was given."
      var-spot)
    (setq var-spot '(var-spot 0)))
  (cond ((eq (car var-spot) 'stack-frame-var)
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-stack-frame-var)
	 (write-byte-code-to-stream byte-code-stream (second var-spot)))
	((eq (car var-spot) 'stack-arg)
	 (call-stack-instruction-emitter pop-into-stack-arg
	   byte-code-stream (second var-spot)))
	(t
	 (let ((first-index (second var-spot)))
	   (cond ((and (fixnump first-index)
		       (<f first-index 256))
		  (emit-instruction-byte-code
		    byte-code-stream 'pop-into-local-var)
		  (write-byte-code-to-stream byte-code-stream first-index)
		  (emit-typecode-to-stream byte-code-stream var-spot))
		 (t
		  (emit-instruction-byte-code
		    byte-code-stream 'pop-into-surrounding-local-var)
		  (emit-long-code-constant-to-stream
		    byte-code-stream
		    first-index)
		  (emit-typecode-to-stream byte-code-stream var-spot)))))))




;;; Instruction 41, the `POP-INTO-LOCAL-VAR stack instruction' takes a one byte
;;; index into the local-var-vector, pops a value off the stack, and puts it
;;; into the vector at that location.  If the old value in the spot was an
;;; evaluation value, it should be reclaimed.  Note that this instruction is an
;;; optimization of the POP-INTO-SURROUNDING-LOCAL-VAR instruction, which can
;;; iterate its way out to environments of surrounding code-bodies or handle
;;; local-var indices over 255.

;;; POP-INTO-LOCAL-VAR (local-var-vector-index)

(def-stack-instruction (pop-into-local-var 41 3 1
			 print-op-and-local-var-and-typecode
			 pprint-pop-into-local-var-instruction)
  (setq fixnum-register-1 (code-constant 0))
  (setq register-1 (svref local-var-vector fixnum-register-1))
  (setq fixnum-register-2 (code-constant 1))
  ;added by SoftServe
  (if (and (rule-instance-p current-computation-instance) 
           (return-value-position-after-lhs-call current-computation-instance))
   (progn 
     (setf (svref local-var-vector fixnum-register-1) 
            (svref local-stack (return-value-position-after-lhs-call current-computation-instance)))
     (setq top-of-stack (return-value-position-after-lhs-call current-computation-instance))
     (setq stack-frame-base (+f top-of-stack 30)) ;recommended distance 
     (setf (return-value-position-after-lhs-call current-computation-instance) nil)
     )    
   (setf (svref local-var-vector fixnum-register-1)
	(arg 0))
  )
  ;end of changes
  (reclaim-if-evaluation-value-given-typecode register-1 fixnum-register-2)
  (incff stack-program-counter 2)
  (decff top-of-stack)
 )




(defun signal-no-value-in-local-var-error-1
       (var-spot-or-index compiled-item compiled-item-component-particulars?)
  (let* ((byte-code-body?
	   (get-byte-code-body-if-any
	     compiled-item compiled-item-component-particulars?))
	 (consed-var-spot?
	   (if (valid-var-spot-index-p var-spot-or-index)
	       (gensym-list 'var-spot var-spot-or-index)
	       nil)))
    (when consed-var-spot?
      (setq var-spot-or-index consed-var-spot?))
    (twith-output-to-error-text
      (twrite-string "The local name ")
      (print-var-spot-for-stack
	var-spot-or-index
	(byte-code-body-environment-description byte-code-body?)
	t)
      (reclaim-gensym-list consed-var-spot?)
      (twrite-string " was referenced when it had no value."))))

(def-substitution-macro signal-no-value-in-local-var-error
       (var-spot-or-index compiled-item compiled-item-component-particulars?
			  top-of-stack)
  (raw-stack-error-named-error
    top-of-stack
    (signal-no-value-in-local-var-error-1
      var-spot-or-index compiled-item compiled-item-component-particulars?)))

;;; Instruction 42, the `PUSH-FROM-SURROUNDING-LOCAL-VAR stack instruction'
;;; retrieves values from local variables which may or may not be local to this
;;; environment.  It takes a high byte and low byte of an index into the
;;; constant vector which should contain a var-spot naming the local variable.
;;; If the value in the local-var is an evaluation value, it pushes a copy on to
;;; the stack, else it just pushes the value itself.

;;; PUSH-FROM-SURROUNDING-LOCAL-VAR (index-high-byte, index-low-byte)

(def-stack-instruction (push-from-surrounding-local-var 42 4 nil
			 print-op-and-surrounding-local-var-and-typecode
			 pprint-push-from-surrounding-local-var-instruction)
  (setq fixnum-register-2 (long-code-constant 0))
  (setq fixnum-register-1 (var-spot-index-nesting fixnum-register-2))
  (cond ((pluspf fixnum-register-1)
	 (setq register-2 current-computation-instance)
	 (unless (code-body-invocation-p register-2)
	   (signal-nested-code-bodies-out-of-procedures
	     top-of-stack fixnum-register-2))
	 (loop while (pluspf fixnum-register-1) do
	   (setq register-2 (code-body-caller register-2))
	   (decff fixnum-register-1))
	 (setq register-3
	       (svref (invocation-local-var-vector register-2)
		      (var-spot-local-index fixnum-register-2))))
	(t
	 (setq register-3
	       (svref local-var-vector fixnum-register-2))))
  (setq fixnum-register-1 (code-constant 2))
  (copy-if-evaluation-value-given-typecode-err-on-nil
    register-3 fixnum-register-1
    (signal-no-value-in-local-var-error
      fixnum-register-2 *current-computation-frame*
      current-computation-component-particulars top-of-stack))
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-3)
  (incff stack-program-counter 3))





;;; Instruction 43, the `PUSH-FROM-LOCAL-VAR stack instruction' takes a one byte
;;; index into the local-var-vector, and pushes the value from that location
;;; onto the top of the stack.  If the value is an evaluation-value, it is
;;; copied before being pushed.
;;; The one-byte index
;;; is followed by a 1-byte immediate value, giving a typecode indicating
;;; the type of the object to be pushed.

;;; PUSH-FROM-LOCAL-VAR (index-into-local-var)

(defun typecode-mismatch-for-place-reference(value value-typecode)
  (and (evaluation-place-reference-p value)
       (eq value-typecode item-typecode)))

(def-stack-instruction (push-from-local-var 43 3 nil
			 print-op-and-local-var-and-typecode
			 pprint-push-from-local-var-instruction)
  (setq fixnum-register-1 (code-constant 0))
  (setq register-1 (svref local-var-vector fixnum-register-1))
  (setq fixnum-register-2 (code-constant 1))
  (copy-if-evaluation-value-given-typecode-err-on-nil
    register-1 fixnum-register-2
    (signal-no-value-in-local-var-error
      fixnum-register-1 *current-computation-frame* 
      current-computation-component-particulars top-of-stack))
  (when (typecode-mismatch-for-place-reference register-1 fixnum-register-2)
    (setq register-1 (copy-if-evaluation-value register-1)))
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 2))

(def-stack-instruction-emitter push-from-surrounding-local-var
			       (byte-code-stream var-spot)
  (unless (valid-var-spot-p var-spot)
    (compiler-bug
      "push-from-local-var emitter"
      "An invalid var spot, ~a, was given."
      var-spot)
    (setq var-spot '(var-spot 0)))
  (cond ((eq (car var-spot) 'stack-frame-var)
	 (call-stack-instruction-emitter push-from-stack-frame-var
	   byte-code-stream var-spot))
	((eq (car var-spot) 'stack-arg)
	 (call-stack-instruction-emitter push-from-stack-arg
	   byte-code-stream var-spot))
	(t
	 (let ((first-index (second var-spot)))
	   (cond ((and (fixnump first-index)
		       (<f first-index 256))
		  (emit-instruction-byte-code
		    byte-code-stream 'push-from-local-var)
		  (write-byte-code-to-stream byte-code-stream first-index)
		  (emit-typecode-to-stream byte-code-stream var-spot))
		 (t
		  (emit-instruction-byte-code
		    byte-code-stream 'push-from-surrounding-local-var)
		  (emit-long-code-constant-to-stream
		    byte-code-stream first-index)
		  (emit-typecode-to-stream byte-code-stream var-spot)))))))


;;; Instruction 44, the `NAME-REFERENCE stack instruction' finds an item with
;;; the given name, if any.  If no such item exits, this instruction will leave
;;; a NIL on the top of the stack when the allow-no-item byte is anything but
;;; zero, otherwise it will signal a stack error.

;;;   NAME-REFERENCE (high-byte-name-constant-index, low-byte, allow-no-item)

(def-stack-error name-reference-error (name top-of-stack)
  (let ((frame-with-name? (get-instance-with-name-if-any 'item name)))
    (if frame-with-name?
	(if (and (not (active-p frame-with-name?))
		 (not (role-serve-inactive-objects?)))
	    "The item named ~a cannot be referred to because it is disabled or inactive."
	    "The item named ~a cannot be referred to because it belongs to another faction.")
	"No item named ~a exists."))
  name)

(def-stack-instruction (name-reference 44 4 nil
			 print-op-constant-long-and-code-constant
			 pprint-name-reference-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  (setq register-2
	(evaluation-symbol-symbol
	  (svref constant-vector fixnum-register-1)))
  (setq register-1 (lookup-name-reference register-2))
  (when (and (null register-1)
	     (=f (code-constant 2) 0))
    (name-reference-error register-2 top-of-stack))
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 3))

#+mtg2
(progn
  (defun-simple check-faction (faction item)
    (or (procedure-p item) ; at this time we allow cross-faction calls
	(of-class-p item 'remote-procedure-declaration)
	(class-definition-p item)
	(eq (or faction :main-faction)
	    (or (faction? item) :main-faction))))
  
  (defun-simple check-faction-at-runtime (item)
    (check-faction (car-of-cons current-faction-global) item)))

(defun-simple lookup-name-reference (name)
  (let ((frame?
	 #-mtg2
	 (get-instance-with-name-if-any 'item name)
	 #+mtg2
	 (get-faction-instance-with-name-if-any
	  (car-of-cons current-faction-global) 'item name)))
    (if (and frame? (serve-item-p frame?)) frame? nil)))

(def-stack-instruction-emitter name-reference
    (byte-code-stream name-constant no-item-ok?)
  (emit-instruction-byte-code byte-code-stream 'name-reference)
  (let ((index (register-constant-in-byte-code-stream
		 byte-code-stream
		 (make-evaluation-symbol name-constant))))
    (emit-long-code-constant-to-stream byte-code-stream index)
    (write-byte-code-to-stream
      byte-code-stream (if no-item-ok? 1 0))))




;;; Instruction 45, the `EVALUATE-ROLE' stack instruction' finds an item or
;;; datum using the role in the constant vector and domains on the stack.  If
;;; any of the domains are NIL, or if no item is served by this role, then a NIL
;;; is left on the top of the stack.  This is done for benifit of the "exists"
;;; predicate cases.

;;; The third byte code constant following the instruction is the argument
;;; count.  At the present time, this will always be either a 1 or a 2.

;;; The fourth byte code constant contains a 1 when no-item is an allowable
;;; return type, and 0 when this instruction must return a role served value or
;;; signal an error.

;;; For roles that do not require domains, use the Evaluate-Role-With-No-Domain
;;; stack instruction.  There should also stack instructions for specific roles,
;;; as optimizations.  The Name-Reference instruction is used to locate an item
;;; by name.

;;;   EVALUATE-ROLE (high-byte-role-constant, low-byte-role-constant, arg-count
;;;                  no-item-allowed)

(defmacro role-server-case (arg &body clauses)
  (if (and (null (cdr clauses))
	   (eq 't (car clauses)))
      `(progn ,@(cdar clauses))
      `(case ,arg
	 ,@clauses)))

(defmacro inlined-role-server-case (arg &body clauses)
  `(case ,arg
     ,@(loop for role in unique-value-roles
	     for domain-count = (unique-value-of-role-server-domain-count role)
	     for macro = (unique-value-of-role-server-macro role)
	     unless (memq role '(named-by-symbol related-to-item)) ; too complicated
	       collect `(,role (,macro top-of-stack
				       register-1
				       (/=f (code-constant 3) 0)
				       ,@(case domain-count
					   (1 `(register-4))
					   (2 `(register-4 register-5))))))
     ,@clauses))

(def-stack-instruction (evaluate-role 45 5 nil print-op-role-long-and-arg-count
				      pprint-evaluate-role-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  (setq fixnum-register-2 (code-constant 2))	; arg count
  (setq register-1 (svref constant-vector fixnum-register-1)) ; role
  (cond ((=f fixnum-register-2 1)
	 (setq register-4 (svref local-stack top-of-stack))
	 (setq register-5 nil))
	(t
	 (setq register-4 (svref local-stack (-f top-of-stack 1)))
	 (setq register-5 (svref local-stack top-of-stack))
	 (decff top-of-stack 1)))
  (setq register-2
	(cond ((atom register-1)
	       (fetch-unique-value-of-role-for-stack
		 register-1 fixnum-register-2 register-4 register-5
		 top-of-stack (/=f (code-constant 3) 0)))
	      (t
	       (setq register-2 (role-name-of-non-atomic-role register-1))
	       (role-server-case register-2
                 (t
		   (fetch-unique-value-of-role-for-stack
		     register-1 fixnum-register-2 register-4 register-5
		     top-of-stack
		     (/=f (code-constant 3) 0)))))))
  (setf (svref local-stack top-of-stack) register-2)
  (incff stack-program-counter 4))




;;; The function `fetch-unique-value-of-role' performs the work of role service
;;; for the stack evaluator.  It takes a role, a count of the number of domains
;;; for this role, the stack, and the top-of-stack index.  This function fetches
;;; the domains from the stack, serves the new role value (if any), and reclaims
;;; the domains if they are evaluation values.

(defun-simple fetch-unique-value-of-role-for-stack
    (role domain-count domain-1 domain-2? top-of-stack no-item-allowed?)
  (let* ((two-arg? (=f domain-count 2))
	 (value nil)
	 (expiration nil)
	 (too-many-values? nil))
    ;; Note that in this case no-item-allowed?  must be T, since the arguments
    ;; to this would have signalled an error if they weren't able to serve
    ;; values.  -jra 10/10/91
    (when (or (null domain-1)
	      (and two-arg? (null domain-2?)))
      (reclaim-if-evaluation-value domain-1)
      (reclaim-if-evaluation-value domain-2?)
      (return-from fetch-unique-value-of-role-for-stack nil))
    (when (consp role)
      (let* ((role-name (role-name-of-non-atomic-role role))
	     (unique-value-function (unique-value-of-role-server-function-macro role-name)))
	(when unique-value-function
	  (return-from fetch-unique-value-of-role-for-stack
	    (if two-arg?
		(funcall-simple-compiled-function ; two domain case
		  (compiled-function-in-place unique-value-function)
		  top-of-stack
		  role
		  no-item-allowed?
		  domain-1 domain-2?)
		(funcall-simple-compiled-function ; one domain case
		  (compiled-function-in-place unique-value-function)
		  top-of-stack
		  role
		  no-item-allowed?
		  domain-1))))))
    ;; Fetch the value, expiration, and too-many values flag.
    (multiple-value-setq (value expiration too-many-values?)
      (serve-unique-item-or-evaluation-value-of-role role domain-1 domain-2? nil))

    (when (null expiration)
      (setq value nil)
      (when (and (not two-arg?) (symbolp role))
	(let ((virtual-attribute? (virtual-attribute role)))
	  (when (and virtual-attribute?
		     (type-specification-type-p
		       domain-1
		       (virtual-attribute-arg-type virtual-attribute?)))
	    (let ((virtual-value (get-virtual-attribute
				   domain-1 virtual-attribute?)))
	      (unless (eq virtual-value no-component-value)
		(setq value virtual-value))))))
      (unless (or value no-item-allowed?)
	(role-returned-no-values-error
	  top-of-stack role domain-1 domain-2?))
      (when (and (null value)
		 too-many-values?
		 (detail-trace-message-will-be-written-p))
	(trace-too-many-objects-role-error role)))
    (reclaim-if-evaluation-value domain-1)
    (reclaim-if-evaluation-value domain-2?)
    value))

(defun attribute-returned-no-values-error-1
    (attribute item-or-structure class-specific-attribute-class?)
  (twith-output-to-error-text
    (write-attribute-returned-no-values-error-message
      attribute item-or-structure class-specific-attribute-class?)))

(def-substitution-macro attribute-returned-no-values-error
    (top-of-stack attribute item-or-structure class-specific-attribute-class?)
  (raw-stack-error-named-error
    top-of-stack
    (attribute-returned-no-values-error-1
      attribute item-or-structure class-specific-attribute-class?)))

(defun role-returned-no-values-error-1 (role domain-1? domain-2?)
  (cond
    ((and (symbolp role) (framep domain-1?))
     (attribute-returned-no-values-error-1 role domain-1? nil))
    ((and (consp role) (eq (car-of-cons role) 'class-qualified-name))
     (attribute-returned-no-values-error-1 (third role) domain-1? (second role)))
    ((and (consp role) (eq (car-of-cons role) 'attribute-value))
     (attribute-returned-no-values-error-1 domain-2? domain-1? nil))
    (t
     (twith-output-to-error-text
       (twrite-string "An attempt was made to reference the ")
       (print-role role)
       (when domain-1?
	 (twrite-char #.%space)
	 (write-stored-value domain-1?))
       (when domain-2?
	 (twrite-string " and ")
	 (write-stored-value domain-2?))
       (twrite-string ", but nothing matches that reference.")))))




;;; The function `attribute-returned-no-values-error' is used to signal a
;;; stack-error when the attribute of an item cannot be referenced or when it
;;; contains no value.  The class-specific-attribute-class? specifies that the
;;; attribute must be defined for a given superior-class.

(defun-void write-attribute-returned-no-values-error-message
    (attribute item-or-structure class-specific-attribute-class?)
  (cond
    ((framep item-or-structure)
     (let* ((slot-description?
	      (get-slot-description-of-frame
		attribute item-or-structure class-specific-attribute-class?))
	    (slot-value?
	      (when slot-description?
		(get-slot-description-value item-or-structure slot-description?))))
       (cond
	 ((null slot-description?)
	  (let* ((class (class item-or-structure))
		 (actual-name?
		   (unalias-slot-name-if-necessary attribute class))
		 (actual-slot-description?
		   (get-slot-description-of-frame
		     actual-name? item-or-structure
		     class-specific-attribute-class?))
		 (slot-type?
		   (and actual-slot-description?
			(feature-assq
			  'type
			  (slot-features
			    actual-slot-description?)))))
	    (cond
	      ((and slot-type?
		    (not (do-not-put-slot-in-attribute-tables-p
			     actual-slot-description? nil)))
	       (let ((evaluator-slot-info?
		       (get-slot-description-evaluator-info actual-slot-description?)))
		 (cond ((and evaluator-slot-info?
			     (null (evaluator-slot-info-category-setter evaluator-slot-info?)))
			(tformat
			  "The attribute ~A of ~NF is read-only."
			   attribute item-or-structure))
		       ((and evaluator-slot-info?
			     (null slot-value?)
			     (evaluator-slot-info-category-getter evaluator-slot-info?))
			(tformat
			  "The attribute ~A exists in ~NF, but the attribute contained ~
                           nothing, causing this reference to fail."
			   attribute item-or-structure))
		       (t
			(tformat
			  "The system defined attribute ~a of ~NF cannot be ~
                           referenced directly, causing this reference to fail.  ~
                           However, you can reference the text of this attribute."
			  attribute item-or-structure)))))
	      ((and class-specific-attribute-class?
		    (not (classp class-specific-attribute-class?)))
	       (tformat
		 "The attribute ~a::~a does not exist in ~NF, since ~a is not ~
                 a defined class."
		 class-specific-attribute-class? attribute item-or-structure
		 class-specific-attribute-class?))
	      ((and class-specific-attribute-class?
		    (not (frame-of-class-p item-or-structure class-specific-attribute-class?)))
	       (tformat
		 "The attribute ~a::~a does not exist in ~NF, since ~NF is not ~
                 an instance of the class ~a."
		 class-specific-attribute-class? attribute item-or-structure item-or-structure
		 class-specific-attribute-class?))
	      ((and class-specific-attribute-class?
		    (get-slot-description-of-frame attribute item-or-structure nil))
	       (tformat
		 "The attribute ~a exists in ~NF, but is not defined for ~
                 the superior-class ~a."
		 attribute item-or-structure class-specific-attribute-class?))
	      (t
	       (tformat
		 "The attribute ~a does not exist in ~NF~a."
		 attribute item-or-structure
		 (if (attribute-p attribute)
		     ", though this attribute is defined for other classes"
		     ""))))))
	 ((null slot-value?)
	  (tformat
	    "The attribute ~NS exists in ~NF, but the attribute contained ~
               nothing, causing this reference to fail."
	    slot-description? (class-description-slot item-or-structure) item-or-structure))
	 ((and (framep slot-value?) (not (active-p slot-value?))
	       (not (role-serve-inactive-objects?)))
	  (tformat
	    "The attribute ~NS of ~NF contained an item which was "
	    slot-description? (class-description-slot item-or-structure) item-or-structure)
	  (if (not (frame-ok-p slot-value?))
	      (tformat "~a." (frame-status slot-value?))
	      (tformat "inactive or disabled.")))
	 ;; The following clause shouldn't happen.
	 (class-specific-attribute-class?
	  (tformat
	    "An attempt to reference the ~A::~A of ~NF failed to return a value."
	    class-specific-attribute-class? attribute item-or-structure))
	 (t
	  (tformat
	    "An attempt to reference the ~A of ~NF failed to return a value."
	    attribute item-or-structure)))))
    ((evaluation-structure-p item-or-structure)
     ;; Limit the structure expand size to limit the error memory use
     (let ((evaluation-value-writing-target-length?
	    maximum-length-for-writing-evaluation-values))
       (tformat "The attribute ~(~a~) was not found in ~NV."
		attribute item-or-structure)))
    (t
     (tformat "The attribute ~NV was not found." attribute))))

(defun-void trace-too-many-objects-role-error (role)
  (write-detail-trace-message
    (twrite-string "Attempted to find an item using ")
    (print-role role)
    (twrite-string ", but more than one item was found.")))

(defvar allow-inline-evaluate-role-instructions-p nil)

(def-stack-instruction-emitter evaluate-role
    (byte-code-stream role-constant domain-count no-item-allowed?
		      domain-1-item-name? domain-1-type-spec
		      optimized-role-info)
  (cond
    ((and (consp role-constant)
	  (eq (car-of-cons role-constant) 'attribute-frame-or-place-reference))
     (call-stack-instruction-emitter attribute-frame-or-place-reference
       byte-code-stream (second role-constant)))
    ((and (consp role-constant)
	  (eq (car-of-cons role-constant) 'class-qualified-name-frame-or-place-reference))
     (call-stack-instruction-emitter push-constant
       byte-code-stream (second-of-long-enough-list role-constant))
     (call-stack-instruction-emitter push-constant
       byte-code-stream (third-of-long-enough-list role-constant))
     (call-stack-instruction-emitter funcall-instruction
       byte-code-stream 'class-qualified-name-frame-or-place-reference))
    ((and (consp role-constant)
	  (eq (car-of-cons role-constant) 'element-frame-or-place-reference))
     (call-stack-instruction-emitter element-frame-or-place-reference byte-code-stream))
;    ((and (symbolp role-constant)
;          (=f domain-count 1)
;          (not no-item-allowed?))
;     (emit-instruction-byte-code byte-code-stream 'attribute-value)
;     (emit-long-code-constant-to-stream
;       byte-code-stream
;       (register-internal-constant-in-byte-code-stream
;         byte-code-stream role-constant)))
    ;; Replaces the above code which emits to the attribute-value instruction.
    ((and (symbolp role-constant)
	  (=f domain-count 1)
	  (not no-item-allowed?))
     (let ((class?
	     (cond ((class-type-specification-p domain-1-type-spec)
		    (type-specification-class-function domain-1-type-spec))
		   ((type-specifications-could-intersect-p
		      domain-1-type-spec '(structure))
		    nil)
		   (t 'item))))
       (call-stack-instruction-emitter cached-attribute-value
	 byte-code-stream role-constant domain-1-item-name? class? nil)))
    ((and (listp role-constant)
	  (eq (first role-constant) 'class-qualified-name)
	  (=f domain-count 1)
	  (not no-item-allowed?))
     (let ((class?
	     (cond ((class-type-specification-p domain-1-type-spec)
		    (type-specification-class-function domain-1-type-spec))
		   ((type-specifications-could-intersect-p
		      domain-1-type-spec '(structure))
		    nil)
		   (t 'item)))
	   (class-specific-attribute-class? (second role-constant))
	   (attribute-name (third role-constant)))
       (call-stack-instruction-emitter cached-attribute-value
	 byte-code-stream attribute-name domain-1-item-name? class?
	 class-specific-attribute-class?)))
    ((and (consp role-constant)
	  (eq (car-of-cons role-constant) 'nth-element)
	  (not no-item-allowed?)
	  (not optimized-role-info)) ; block nth-element if more specific
                                     ; role was seen in pref-inst-chooser
     (emit-instruction-byte-code byte-code-stream 'nth-element))
    (t
     (when optimized-role-info
       (cond ((consp role-constant)
	      (cond ((and (symbolp (car role-constant))
			  (eq (car role-constant) 'role-server))
		     (setf (cadr role-constant)
			   (car optimized-role-info)))
		    ((symbolp (car role-constant))
		     (setf (car role-constant)
			   (car optimized-role-info)))))
	     (t
	      (setf role-constant (car optimized-role-info)))))
     (let ((instruction-name
	     (if (and optimized-role-info
		      (cadr optimized-role-info)
		      allow-inline-evaluate-role-instructions-p)
		 (cadr optimized-role-info)
		 'evaluate-role)))
       (emit-instruction-byte-code byte-code-stream instruction-name))
     (let ((index (register-internal-constant-in-byte-code-stream
		    byte-code-stream role-constant)))
       (emit-long-code-constant-to-stream byte-code-stream index)
       (write-byte-code-to-stream byte-code-stream domain-count)
       (write-byte-code-to-stream byte-code-stream
				  (if no-item-allowed? 1 0))))))




;;; Instruction 46, the `EVALUATE-ROLE-WITH-NO-DOMAIN' stack instruction' finds
;;; an item or datum using the role in the constant vector and no domain.  If no
;;; item or datum is served and the third code constant argument is 1, this
;;; instruction will still push a NIL on the top of the stack.  Otherwise, it
;;; signals an error.

;;; For roles that require domains, use the Evaluate-Role stack instruction.
;;; There are also stack instructions for specific roles.  The Name-Reference
;;; instruction is used to locate an item by name.

;;; EVALUATE-ROLE-WITH-NO-DOMAIN
;;;   (high-byte-role-constant-index, low-byte, no-item-allowed)

(def-stack-instruction (evaluate-role-with-no-domain 46 4 1
			 print-op-and-role-no-domain-long
			 pprint-evaluate-role-with-no-domain-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  (setq register-1 (svref constant-vector fixnum-register-1))  ; role
  ;; Fetch the value, expiration, and too-many values flag.
  (multiple-value-setq (register-3 register-4 register-5)
    (serve-unique-item-or-evaluation-value-of-role register-1 nil nil t))
  (when (null register-4)
    (setq register-3 nil)
    (setq fixnum-register-2 (code-constant 2))
    (when (=f fixnum-register-2 0)
      (role-returned-no-values-error
	top-of-stack register-1 nil nil))
    (when (and register-5 detailed-tracing?)
      (trace-too-many-objects-role-error register-1)))
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-3)
  (incff stack-program-counter 3))

(def-stack-instruction-emitter evaluate-role-with-no-domain 
			       (byte-code-stream role-constant no-item-allowed)
  (emit-instruction-byte-code byte-code-stream 'evaluate-role-with-no-domain)
  (let ((index (register-internal-constant-in-byte-code-stream
		 byte-code-stream role-constant)))
    (emit-long-code-constant-to-stream byte-code-stream index)
    (write-byte-code-to-stream byte-code-stream (if no-item-allowed 1 0))))






;;;; Getting Current Value in Instructions




;;; The function get-current-value-based-on-current-environment is used to fetch
;;; values from variables and parameters from within the stack evaluator.  This
;;; function takes a variable or parameter, returns its value as an
;;; evaluation value or NIL if it has no current value, and side-effects the
;;; stack-expiration global variable to minimize it with the expiration of the
;;; value being returned.

(def-substitution-macro get-current-value-from-simulation-environment
			(variable-or-parameter)
  (let ((simulated-evaluation-value
	  (sim-eval-variable-or-constant-evaluation-value
	    variable-or-parameter)))
    (cond ((no-simulation-value-p simulated-evaluation-value)
	   (setq stack-expiration nil)
	   nil)
	  (t
	   simulated-evaluation-value))))

(def-substitution-macro get-current-value-based-on-current-environment
			(variable-or-parameter top-of-stack)
  ;; Need to make sure cached-top-of-stack is set in case stack-error gets
  ;; called (which relies on it for cleanup).  The simulate case was dying
  ;; downstream from here if a stack-error was thrown because of double-reclaim
  ;; problems.  Don't try to change this to a function!  The variable
  ;; top-of-stack is a local, non-special variable that is bound by every caller of
  ;; this macro.  -dkuznick, 11/10/98 
  (setq cached-top-of-stack top-of-stack)
  (if (or (eq current-environment 'inference-engine)
	  (eq current-environment 'procedure))
      (get-current-evaluation-value variable-or-parameter nil)
      (get-current-evaluation-value-from-simulation-environment
	variable-or-parameter)))

(defun-simple get-current-evaluation-value-from-simulation-environment
    (variable-or-parameter)
  (cond ((eq current-environment 'simulator)
	 (with-current-model-for-variable-if-necessary variable-or-parameter
	   (get-current-value-from-simulation-environment 
	     variable-or-parameter)))
	((eq current-environment 'simulated-value)
	 ;; The simulated-value environment can access a simulated value when
	 ;; not in the simulator environment.
	 (with-current-model-for-variable-if-necessary variable-or-parameter
	   (let ((do-not-update-simulated-value? t))
	     (get-current-value-from-simulation-environment 
	       variable-or-parameter))))))

;; When current environment is 'simulator or 'simulated-value, the call
;; may be made as a result of evaluating a simulation formula, or a
;; simulation procedure.  In the case of a simulation formula,
;; current-model-runtime-info?  will be bound, whereas in the case of a
;; simulation procedure, it will not be.  Therefore,
;; with-current-model-for-variable-if-necessary is used.




;;; Instruction 47, the `PARAMETER-VALUE stack instruction' pops a parameter off
;;; the top of the stack and replaces that parameter with its value.

;;; PARAMETER-VALUE ()

(def-stack-instruction (parameter-value 47 1 1
			nil pprint-parameter-value-instruction)
  (setq register-1 (arg 0))
  (setq register-1 (get-current-value-based-on-current-environment register-1 top-of-stack))
  (setf (arg 0) register-1))




;;; Instruction 48, the `COERCE-INTEGER-TO-FLOAT stack instruction' pops an
;;; integer off the top of the stack, coerces it to a gensym-float, and pushes
;;; it back onto the stack.

;;; COERCE-INTEGER-TO-FLOAT ()

(def-stack-instruction (coerce-integer-to-float 48 1 1
			nil pprint-coerce-integer-to-float-instruction)
  (setq register-1 (arg 0))
  (setq register-2
	(make-evaluation-float-from-evaluation-integer register-1))
  (setf (arg 0) register-2))




;;; Instruction 49, the `COERCE-QUANTITY-TO-FLOAT stack instruction' pops a
;;; quantity off the top of the stack, coerces it to a gensym-float, and pushes
;;; it back onto the stack.

;;; COERCE-QUANTITY-TO-FLOAT ()

(def-stack-instruction (coerce-quantity-to-float 49 1 1
			nil pprint-coerce-quantity-to-float-instruction)
  (setq register-1 (arg 0))
  (cond ((evaluation-long-p register-1)
	 (setf (arg 0) (make-evaluation-float-from-evaluation-long register-1)))
	(t
	 (unless (evaluation-float-p register-1)
	   (setf (arg 0) (make-evaluation-float-from-evaluation-integer register-1))))))


;;; Instruction 50, the `NOT stack instruction' pops a truth-value off the top
;;; of the stack and replaces that with the inversion of the logical-value.

;;; NOT ()

(def-stack-instruction (not 50 1 1 nil pprint-not-instruction)
  (setq register-1 (arg 0))
  (setq register-1 (evaluation-truth-value-not register-1))
  (setf (arg 0) register-1))




;;; Instruction 51, the `FUNCALL-EVALUATOR' stack instruction' funcalls the
;;; stack-evaluators which are not inlined and are not implementations of
;;; special forms.  It accepts one code-constant argument which is an index that
;;; specifies the evaluator function.

;;; The dispatch-type of the function determines the method of function calling.
;;; For each dispatch-type, the function is passed the correct number of
;;; arguments popped from the stack, the top-of-stack is increased or decreased
;;; depending on the number of arguments on the stack, the return value of the
;;; function is put on the stack, and the program-counter is incremented passed
;;; the code-constant.

;;; Note that this instruction only calls functions of up to 6 arguments.  This
;;; should be modified as needed.

;;; FUNCALL-EVALUATOR (function-index)

(def-stack-error funcalled-evaluator-error (evaluator-number top-of-stack)
  "Error in evaluator.  The out of line evaluator #~a did not exist.  Please ~
   report this G2 internal software error to Gensym Software Support."
  evaluator-number)

(defmacro call-funcall-evaluator-function (register-1 nargs)
  `(funcall-simple-compiled-function
     (if-emitting-c-code
       (evaluator-function-name ,register-1)
       (evaluator-function-or-macro-name ,register-1))
     ,@(loop for i from 0 below nargs
	     collect `(stack-arg-macro ,i ,(1- nargs)))))

(def-stack-instruction (funcall-evaluator 51 2 nil
			 print-funcall-evaluator
			 pprint-funcall-evaluator)
  ;; Funcalled evaluator number.
  (setq fixnum-register-1 (code-constant 0))
  ;; Dispatch type
  (setq fixnum-register-2
	(svref funcalled-evaluator-dispatch-type fixnum-register-1))
  (setq register-1
	(svref funcalled-evaluator-array fixnum-register-1))

  (setq cached-top-of-stack top-of-stack)
  (setq cached-stack-program-counter (1-f stack-program-counter))
  
  (fixnum-case fixnum-register-2
    ;; Dispatch types based on number of arguments.  These evaluators are passed
    ;; and return evaluation-values.  They are responsible for reclaiming
    ;; evaluation-value arguments as necessary.
    (#.funcall-eval-type-0-arg
       (setq register-1 (call-funcall-evaluator-function register-1 0)))
    (#.funcall-eval-type-1-arg
       (setq register-1 (call-funcall-evaluator-function register-1 1))
       (decff top-of-stack))
    (#.funcall-eval-type-2-arg
       (setq register-1 (call-funcall-evaluator-function register-1 2))
       (decff top-of-stack 2))
    (#.funcall-eval-type-3-arg
       (setq register-1 (call-funcall-evaluator-function register-1 3))
       (decff top-of-stack 3))
    (#.funcall-eval-type-4-arg
       (setq register-1 (call-funcall-evaluator-function register-1 4))
       (decff top-of-stack 4))
    (#.funcall-eval-type-5-arg
       (setq register-1 (call-funcall-evaluator-function register-1 5))
       (decff top-of-stack 5))
    (#.funcall-eval-type-6-arg
       (setq register-1 (call-funcall-evaluator-function register-1 6))
       (decff top-of-stack 6))
    ;[tam.srogatch][2010-11-23]: We need a KB-level function with 8 arguments
    (#.funcall-eval-type-7-arg
       (setq register-1 (call-funcall-evaluator-function register-1 7))
       (decff top-of-stack 7))
    (#.funcall-eval-type-8-arg
       (setq register-1 (call-funcall-evaluator-function register-1 8))
       (decff top-of-stack 8))
    (t
      (if-emitting-c-code
	nil
	(funcalled-evaluator-error fixnum-register-1 top-of-stack))))
  (incff-top-of-stack-with-caching 1)
  (setq cached-stack-program-counter nil)

  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter))

(def-stack-instruction-emitter funcall-evaluator
			       (byte-code-stream evaluator-number)
  (emit-instruction-byte-code byte-code-stream 'funcall-evaluator)
  (write-byte-code-to-stream byte-code-stream evaluator-number))






;;;; Funcall-Instruction




;;; Instruction 52, the `FUNCALL-INSTRUCTION' stack instruction' executes
;;; funcalled-instructions.  It is similar to the funcall-evaluator instruction,
;;; but executes funcalled-instructions, such as actions, and uses a single type
;;; of function dispatch.  It accepts one code-constant argument which is an
;;; index that specifies the funcalled-instruction.

;;; This instruction calls the funcalled-instruction-function with the arguments
;;; top-of-stack and local-stack.  After executing the funcalled-instruction, the
;;; top-of-stack is updated from the return value of the
;;; funcalled-instruction-function and the program-counter is incremented passed
;;; the code-constant.

;;; Funcalled-instructions are stack-instructions which are not executed in-line
;;; or as special forms.  These instructions access arguments from the local-stack
;;; and leave return values on the local-stack.  Each funcalled-instruction should
;;; reclaim and clear stack-args as needed.

;;; [old] The new top-of-stack must be returned
;;; from the body of the funcalled-instruction.

;;; [new] The number of arguments and return values of the funcalled
;;; instruction are obtained from the arg-count and result-count arguments
;;; to def-funcalled-instruction. Funcalled instructions that take a variable
;;; number of arguments and/or return values
;;; can no longer be called with funcall-instruction;
;;; they must instead be called using funcall-instruction-n, which is similar,
;;; except that it takes the number of arguments and return values as inline
;;; arguments in the code vector. The emitter for funcall-instruction takes
;;; care of this, using additional optional arguments that give the number
;;; of arguments and returned values. -alatto, 8/13/98

;;; Instructions that experience errors will leave this function non-locally
;;; calling write-eval-error or eval-error.

;; Add environment or constant-vector args if necessary!!

;;; FUNCALL-INSTRUCTION (function-index)

(def-stack-instruction (funcall-instruction 52 2 nil
			print-funcalled-instruction
			pprint-funcalled-instruction)
  ;; The funcalled-instruction number is the next byte in the instruction
  ;; stream.
  (setq fixnum-register-1 (code-constant 0))
  (assert-for-development
    (svref funcalled-instructions fixnum-register-1)
    "Missing funcalled-instruction description!")
  (setq register-2 (svref funcalled-instructions fixnum-register-1))
  (setq cached-top-of-stack top-of-stack)
  (setq cached-stack-program-counter (1-f stack-program-counter))
  (if-emitting-c-code
    (decache-for-funcall-instruction
      (funcalled-instruction-function-name register-2)
      (funcalled-instruction-argument-count register-2))
    nil)
  (setq register-1 (funcall-simple-compiled-function-without-decaching
		     (if-emitting-c-code
		       (funcalled-instruction-function-name register-2)
		       (funcalled-instruction-function register-2))
		     top-of-stack local-stack))
  (unless (null register-1)
    (raw-stack-error-named-error top-of-stack register-1))
  (decff top-of-stack
	 (funcalled-instruction-argument-count register-2))
  (incff-top-of-stack-with-caching
    (funcalled-instruction-result-count register-2))
  (setq cached-stack-program-counter nil)

  (if (null current-computation-instance)
      (inner-context-switch-to-next-computation-instance :none nil t)
      (incff stack-program-counter)))

(def-stack-instruction (funcall-instruction-n 139 5 nil
			 print-funcalled-instruction-n
			 pprint-funcalled-instruction-n)
  ;; The funcalled-instruction number is the next byte in the instruction
  ;; stream.
  (setq fixnum-register-1 (code-constant 0))
  (assert-for-development
    (svref funcalled-instructions fixnum-register-1)
    "Missing funcalled-instruction description!")
  (setq register-2 (svref funcalled-instructions fixnum-register-1))
  (setq fixnum-register-1 (long-code-constant 1))
  (setq fixnum-register-2 (code-constant 1))

  (setq cached-top-of-stack top-of-stack)
  (setq cached-stack-program-counter (1-f stack-program-counter))
  (incff top-of-stack)	 
  (setf (svref local-stack top-of-stack) fixnum-register-1)
  (if-emitting-c-code
    (decache-for-funcall-instruction
      (funcalled-instruction-function-name register-2)
      (+f fixnum-register-1 1))
    nil)
  (setq register-1 (funcall-simple-compiled-function-without-decaching
		     (if-emitting-c-code
		       (funcalled-instruction-function-name register-2)
		       (funcalled-instruction-function register-2))
		     top-of-stack local-stack))
  
  (unless (null register-1)
    (raw-stack-error-named-error top-of-stack register-1))
  (decff top-of-stack (+f fixnum-register-1 1))
  (incff-top-of-stack-with-caching fixnum-register-2)
  (setq cached-stack-program-counter nil)

  (if (null current-computation-instance)
      (inner-context-switch-to-next-computation-instance :none nil t)
      (incff stack-program-counter 4)))

(def-stack-instruction-emitter funcall-instruction
    (byte-code-stream funcalled-instruction-name &optional nargs nresults)
  (let* ((description
	   (funcalled-instruction-description funcalled-instruction-name))
	 (funcalled-instruction-number
	   (if description
	       (funcalled-instruction-number description)
	       nil)))
    (cond (funcalled-instruction-number
	   (if nargs
	       (emit-instruction-byte-code byte-code-stream 'funcall-instruction-n)
	       (emit-instruction-byte-code byte-code-stream 'funcall-instruction))
	   (write-byte-code-to-stream byte-code-stream funcalled-instruction-number)
	   (when nargs
	     (write-byte-code-to-stream byte-code-stream nresults)
	     (emit-long-code-constant-to-stream byte-code-stream nargs)))
	  (t
	   (compiler-bug
	     "funcall-instruction emitter"
	     "No instruction description for funcalled-instruction ~a."
	     funcalled-instruction-name)))))

#+development
(defun cerror-if-missing-funcalled-instruction-description
       (funcalled-instruction-number)
  (let ((description? 
	  (svref funcalled-instructions funcalled-instruction-number)))
    (unless description?
      (cerror "continue"
	      "Missing funcalled-instruction description!"))))






;;;; Instructions for Attribute Fetching




;;; Instruction 53, the `ATTRIBUTE-FRAME-OR-PLACE-REFERENCE stack instruction'
;;; receives an item as its first stack argument, and a symbol naming an
;;; attribute as its second stack argument, and returns on the stack one of the
;;; following values: an item if the item argument was present and if the named
;;; attribute of the item held an item; or an evaluation place reference if the
;;; item argument was supplied, but there was anything but an item in the
;;; attribute.  Note that the place reference could contain either an attribute
;;; component particular, or an aliased-attribute component particular.  If the
;;; attribute does not exist or contains an unservable item, then a stack error
;;; is signalled.

;;; This instruction is used for the place argument of conclude and change
;;; actions, when the argument is an attribute reference.  The place reference
;;; value is for the case where we are concluding a value into a constant
;;; attribute or changing a constant attribute.  We can implement this operation
;;; in this style (where either a frame or a place reference is returned, rather
;;; than always a place reference) because we know that conclude and change can
;;; currently never replace a frame in a location.  Great hack, eh?  -jra
;;; 8/23/91

;; Modified the emitter to test if an attribute name stack argument should be
;; emitted.  If emitting for an indirect-attribute reference, the attribute-name
;; is the second domain to the role and is not emitted.  It will already be on the
;; stack when the instruction is called.  -cpm, 12/12/91

;; Fixed the problem of returning a globally aliased slot that was not an
;; attribute of the item.  This was causing an action to try to change an
;; aliased global which was not available.  The slot could have been tested in
;; the action, but it seemed better to have this instruction always return a
;; valid attribute.  - cpm, 1/25/92.

;; Also, added tests that the slot or the aliased slot is accessible to the
;; user, i.e., visible to the user.  This was necessary since there is at lease
;; one case of an internal system slot having the same name as an alias of a
;; slot which is visible to the user.  In this case, the internal system slot
;; was incorrectly being returned.  The slot was icon-description and
;; icon-description-of-class?  and the item was an object-definition.  In
;; implementing this, I needed to find the slot information in the
;; class-description slot-descriptions instead of the lookup-structure of the
;; item.  The lookup-structure can contain an entry for an attribute's
;; new-value, which then does not contain the slot-type information.  - cpm,
;; 1/25/92.

(def-stack-instruction (attribute-frame-or-place-reference 53 1 2
			 nil
			 pprint-attribute-frame-or-place-reference-instruction)
  (setq register-1 (arg 1))
  (setf (arg 0)
	(fetch-attribute-frame-or-place-reference
	  (arg 0) register-1 nil top-of-stack))
  (reclaim-evaluation-symbol register-1)
  (decff top-of-stack))

(defun-simple fetch-attribute-frame-or-place-reference
    (item-or-place pretty-slot-name class-qualifier? top-of-stack)
  (cond
    ((evaluation-place-reference-p item-or-place)
     (redirect-place-reference
       item-or-place
       (make-attribute-component-particulars
         pretty-slot-name class-qualifier?
         (evaluation-place-reference-component-particulars item-or-place)))
     item-or-place)
    ((and (evaluation-structure-p item-or-place)
          (evaluation-structure-slot item-or-place pretty-slot-name))
     (make-evaluation-place-reference-to-place
       (make-attribute-component-particulars pretty-slot-name class-qualifier? '*current-computation-frame*)
       item-or-place))
    ((framep item-or-place)
     (let* ((class-description (class-description-slot item-or-place))
            (slot-description?
              (get-slot-description-of-class-description
                pretty-slot-name class-description class-qualifier?))
            (visible-slot?
              (and slot-description?
                   (feature-assq-macro 'type (slot-features slot-description?))
                   (not (do-not-put-slot-in-attribute-tables-p slot-description? t))))
            (slot-value?
              (and visible-slot?
                   (get-slot-description-value item-or-place slot-description?)))
            (frame-value?
              (and (framep slot-value?) slot-value?)))
       (cond
         ((null frame-value?)
          (cond
            ((null visible-slot?)
             (let ((place-reference?
                     (place-reference-of-virtual-attribute?
                       item-or-place pretty-slot-name)))
              (if place-reference?
                  place-reference?
                  (let* ((actual-name?
                           (get-slot-name-for-alias-if-any
                             pretty-slot-name item-or-place))
                         (actual-slot-description?
                           (and actual-name?
                                (get-slot-description-of-class-description
                                  actual-name? class-description class-qualifier?))))
                    (if (and actual-name?
                             actual-slot-description?
                             (feature-assq
                               'type
                                (slot-features actual-slot-description?))
                             (not (do-not-put-slot-in-attribute-tables-p
                                    actual-slot-description? t)))
                        (make-evaluation-place-reference-to-place
                          (make-aliased-attribute-component-particulars
                            pretty-slot-name actual-name?
                            (defining-class actual-slot-description?)
                            '*current-computation-frame*)
                          item-or-place)
                        (attribute-returned-no-values-error
                          top-of-stack pretty-slot-name item-or-place
                          class-qualifier?))))))
            (t
             (make-evaluation-place-reference-to-place
               (make-attribute-component-particulars
                 pretty-slot-name (defining-class slot-description?)
                 '*current-computation-frame*)
               item-or-place))))
         ((serve-item-p frame-value?)
          frame-value?)
         (t
          (attribute-returned-no-values-error
            top-of-stack pretty-slot-name item-or-place class-qualifier?)))))
    (t
     (attribute-returned-no-values-error
       top-of-stack pretty-slot-name item-or-place class-qualifier?))))

(def-stack-instruction-emitter attribute-frame-or-place-reference
			       (byte-code-stream attribute-name?)
  ;; If this is emitting for an indirect-attribute reference, the attribute-name
  ;; is the second domain to the role.  It will already be on the stack.  -cpm,
  ;; 12/13/91
  (when attribute-name?
    (call-stack-instruction-emitter push-constant
      byte-code-stream (make-evaluation-symbol attribute-name?)))
  (emit-instruction-byte-code
    byte-code-stream 'attribute-frame-or-place-reference))




;;; Instruction 54, the `ATTRIBUTE-VALUE stack instruction' is used to fetch
;;; values from user-defined and system-defined pseudo-attributes of frames.  It
;;; is only used in situations where the reference is required to return some
;;; kind of item-or-datum (i.e.  no item is not allowed).  It takes a long code
;;; constant from the instruction stream which is a constant index to the symbol
;;; which names the attribute, and it takes an item off the stack which should
;;; contain the attribute.

;;; ATTRIBUTE-VALUE (high-byte-constant-index, low-byte)

(def-stack-instruction (attribute-value 54 3 1 print-op-and-constant-long
					pprint-attribute-value-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  (setq register-1 (svref constant-vector fixnum-register-1))	; attribute
  (setq register-2 (arg 0))					; item
  (setq register-3
	(frame-or-evaluation-value-user-attribute-value
	  register-2 register-1 nil))
  (when (null register-3)
    (role-returned-no-values-error top-of-stack register-1 register-2 nil))
  (setf (arg 0) register-3)
  (incff stack-program-counter 2))






;;;; Instructions for Procedures Support




;;; Instruction 55, the `RETURN-VALUES stack instruction' executes a return from
;;; the currently executing procedure invocation to the caller of this
;;; procedure.  It takes one code constant argument, which is the number of
;;; values to pop off the stack and return.

;;; This instruction caches into registers the number of values to return, the
;;; currently executing code-body-invocation (from the current-computation-
;;; instance), and the code-body-invocation of the caller.  If there is no
;;; calling code-body-invocation, then this is the base procedure-invocation of
;;; a process and the values on the stack should just be reclaimed.  If the
;;; caller is a code-body-invocation, the values are copied into the callers
;;; environment and the caller is enqueued for immediate execution.  If the
;;; calling code body is not a code-body-invocation, then it is a
;;; remote-procedure-call, and the values should be copied back to the caller
;;; across the network.

;;; In all cases, close this code-body-invocation, set the
;;; current-computation-instance to the procedure (in *current-computation-frame*)
;;; and exit stack-eval.

;; The above comment is wrong!  In many cases (when return-values-body returns
;; NIL) , stack-eval is NOT exited, but instead various variables are modified
;; (stack-program-counter, etc) and the next instruction in the new
;; current-computation-instance is executed. -dkuznick, 7/25/03

;;;   RETURN-VALUES (values-to-return)

(defmacro local-invocation-p (item)
  `(or (code-body-invocation-p ,item)
       (rule-instance-p ,item)))

(defun-simple return-values-body (nargs local-stack top-of-stack)
  (declare (type fixnum nargs))
  (let ((register-1 (code-body-caller current-computation-instance)))
    (cond
      ;; If no code body caller, or the caller is a G2GL call invocation, then
      ;; this is the top of the stack, and the return values will be ignored (or
      ;; copied by finish-g2gl-call, which is called via the completion form
      ;; during return-from-top-level-procedure-invocation).  Let the exit
      ;; routines for stack-eval pop them off the stack.
      ((or (null register-1)
	   (g2gl-call-invocation-p-function register-1))
       (return-from-top-level-procedure-invocation)
       (setq cached-top-of-stack top-of-stack)
       (reclaim-top-of-stack)
       (setq current-computation-instance nil)
       (setq cached-fixnum-time-limit?
	     (fetch-and-enter-next-current-computation-instance
	       priority-of-current-task))
       (null current-computation-instance))

      ;; 1. special rule instances (SoftServe added)
      ((and (rule-instance-p register-1)
	    (in-lhs-call? register-1))
       (let ((register-2 current-computation-instance))
	 (exit-computation-context-for-code-body-invocation register-2 0 t)
	 (close-code-body-invocation register-2))
       (setq current-computation-activity 0)
       (setq current-computation-component-particulars nil)
       (setq *current-computation-frame* (ri-rule register-1))
       (setq current-computation-instance register-1)
       (setq current-computation-style nil)
       (setq current-environment 'inference-engine)
       (setf (return-value-position-after-lhs-call register-1) top-of-stack) 
       (setf (in-lhs-call? register-1) nil)
       (setq cached-fixnum-time-limit? nil))

      ;; 2. code body invocations and general rule instances
      ((local-invocation-p register-1) ; old: t (otherwise)
       (return-stack-values-to-caller
	 register-1 local-stack top-of-stack nargs
	 current-computation-instance)
       
       (decff top-of-stack nargs)

       ;; The following code is the inline return.
       (let ((register-2 current-computation-instance))
	 (exit-computation-context-for-code-body-invocation register-2 0 t)
	 (close-code-body-invocation register-2))

       ;; We already validated the environment before returning values into the
       ;; caller, so suppress the validation while entering again.
       (setq cached-fixnum-time-limit?
	     (cond ((code-body-invocation-p register-1)
		    (enter-computation-context-for-invocation
		      register-1 t))
		   ((rule-instance-p register-1)
		    (enter-or-reclaim-rule-instance-context register-1 t))
		   (t
		    (return-values-bad-caller register-1))))

       ;; Execute the remainder of the context switch, which mutates variables
       ;; local to stack-eval.
       nil)

      ;; 3. remote callers
      ((remote-procedure-call-p register-1) ; old: (not (local-invocation-p register-1))
       ;; Remote return.
       (return-stack-values-to-remote-caller
	 register-1 local-stack top-of-stack nargs
	 current-computation-instance)
       (decff top-of-stack nargs)
       (close-code-body-invocation current-computation-instance)
       ;;(inner-context-switch-to-next-computation-instance :none)
       (setq cached-top-of-stack top-of-stack)
       (reclaim-top-of-stack)
       (setq current-computation-instance nil)
       (setq cached-fixnum-time-limit?
	     (fetch-and-enter-next-current-computation-instance
	       priority-of-current-task))
       (null current-computation-instance))

      ;; 4. other cases.
      (t
       #+development
       (cerror "Continue" "Reclaimed code body invocations.")
       (decff top-of-stack nargs)
       (setq cached-top-of-stack top-of-stack)
       (reclaim-top-of-stack)
       (setq current-computation-instance nil)
       (setq cached-fixnum-time-limit?
	     (fetch-and-enter-next-current-computation-instance
	       priority-of-current-task))
       (null current-computation-instance)))))

(defun-simple handle-stack-for-call-from-rule-antecedent
    (stack top-of-stack values-count returning-code-body-invocation)
  (declare (ignore stack top-of-stack values-count returning-code-body-invocation)))

(def-stack-instruction (return-values 55 2 nil print-op-and-code-constant
				      pprint-return-values-instruction)
  (if-emitting-c-code
    (decache-local-var-vector)
    nil)

  (handle-procedure-time-return-values fixnum-time-limit?)

  #+mtg2
  (pop-faction)
  
  (setq register-1 (return-values-body (code-constant 0) local-stack top-of-stack))
  ;; After return-values-body, current-computation-instance and friends are the
  ;; caller, not the thing doing the return.
  (setq top-of-stack -1)
  (setq fixnum-time-limit? cached-fixnum-time-limit?)
  (cond (register-1
	 (go exit-stack-eval))
	(t
	 (modify-major-stack-eval-locals nil t)
	 (modify-minor-stack-eval-locals))))

(defun-simple handle-procedure-time-return-values (fixnum-time-limit?)
  (unless (calculate-time-of-called-procedures miscellaneous-parameters)
    (let* ((current-time (get-fixnum-time))
	   (start-time procedure-start-time)
	   (difference (fixnum-time-difference current-time start-time)))
      (setq procedure-end-time current-time)
      (incff procedure-current-time difference)
      (when (>=f difference fixnum-time-limit?)
	(signal-procedure-time-error procedure-current-time cached-top-of-stack))
      (setq procedure-start-time current-time)
      (setq procedure-current-time (gensym-pop execution-time-stack)))))

(defun-simple return-values-bad-caller (caller)
  (error "Return-values has caller ~a that is not a code-body-invocation or rule-instance."
	 caller)
  nil)

(def-stack-instruction-emitter return-values (byte-code-stream values-to-return)
  (emit-instruction-byte-code byte-code-stream 'return-values)
  (if (>f values-to-return 255)
      (compiler-error
	"At most 255 values can be returned, ~a in this statement."
	values-to-return)
      (write-byte-code-to-stream byte-code-stream values-to-return)))

(def-stack-error not-enough-values-error
    (caller requested returning-code-body-invocation supplied top-of-stack)
  "Procedure ~NF is requesting ~a values and ~NF can return only ~a."
  (procedure-of-invocation (procedure-invocation-of-code-body caller))
  requested
  (procedure-of-invocation
    (procedure-invocation-of-code-body returning-code-body-invocation))
  supplied)

(defun-void return-from-top-level-procedure-invocation ()
  (exit-tracing-and-breakpoint-context
    *current-computation-frame*
    (return-from-top-level-procedure-invocation-exit-message))
  (close-code-body-invocation current-computation-instance))

(defun-simple return-from-top-level-procedure-invocation-exit-message ()
  (twith-output-to-text-string
    (let ((procedure-invocation
	    (procedure-invocation-of-code-body current-computation-instance)))
      (twrite-string "Returning from ")
      (write-procedure-invocation-instance-from-slot
	procedure-invocation nil)
      (twrite-string ", a top level procedure invocation."))))

(defun-simple return-stack-values-to-caller
	      (caller stack top-of-stack values-count
		      returning-code-body-invocation)
  (let* ((returning-procedure-invocation
	   (procedure-invocation-of-code-body returning-code-body-invocation))
	 (returning-procedure
	   (procedure-of-invocation returning-procedure-invocation))
	 (calling-environment
	   (invocation-local-var-vector caller))
	 (target-position (invocation-return-value-position caller))
	 (target-count (invocation-return-value-count caller))
	 (exit-message?
	   (exit-trace-messages-will-be-written-p returning-procedure))
	 (argument-strings-for-trace nil))
    (when (>f target-count values-count)
      (not-enough-values-error
	caller target-count returning-code-body-invocation values-count
	top-of-stack))
    (unless (procedure-environment-always-valid-p returning-procedure)
      (validate-computation-instance-environment caller nil nil))
    (update-code-body-invocation-frame-serial-number caller)
    (if exit-message?
	(loop with new-value
	      for stack-index fixnum from (+f (-f top-of-stack values-count) 1)
	      for target-index fixnum from target-position
			       below (+f target-position target-count)
	      do
	  (setq new-value (svref stack stack-index))
	  (setf (svref calling-environment target-index) new-value)
	  (setq argument-strings-for-trace
		(proc-cons
		  (if (framep new-value)
		      (tformat-text-string "~NF" new-value)
		      (write-evaluation-value-to-text-string new-value))
		  argument-strings-for-trace))
	      finally
		(loop until (>f stack-index top-of-stack)
		      do
		  (setq new-value (svref stack stack-index))
		  (reclaim-if-evaluation-value new-value)
		  (incff stack-index)))
	(loop with new-value
	      for stack-index fixnum from (+f (-f top-of-stack values-count) 1)
	      for target-index fixnum from target-position
			       below (+f target-position target-count)
	      do
	  (setf (svref calling-environment target-index)
		(svref stack stack-index))
	      finally
		(loop until (>f stack-index top-of-stack)
		      do
		  (setq new-value (svref stack stack-index))
		  (reclaim-if-evaluation-value new-value)
		  (incff stack-index))))
    (if exit-message?
	(exit-tracing-and-breakpoint-context
	  returning-procedure
	  (return-to-procedure-caller-exit-message
	    returning-procedure-invocation
	    (nreverse argument-strings-for-trace)
	    caller))
	(exit-tracing-and-breakpoint-context returning-procedure nil))
    nil))

(defun-simple return-to-procedure-caller-exit-message
	      (procedure-invocation return-value-strings caller)
  (twith-output-to-text-string
    (setq forgive-long-procedure-instruction? t)
    (twrite-string "Returning values (")
    (loop for string in return-value-strings
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (twrite-string string)
      (reclaim-text-string string))
    (reclaim-proc-list return-value-strings)
    (twrite-string ") from ")
    (write-procedure-invocation-instance-from-slot
      procedure-invocation nil)
    (twrite-string " to ")
    (write-procedure-invocation-instance-from-slot
      (procedure-invocation-of-code-body caller) nil)
    (twrite-character #.%\.)))





;;; Instruction 56, the `SIGNAL-ERROR stack instruction', takes a symbol and a
;;; text off the stack and signals an error with that name and description.
;;; This instruction implements user written error signalling and error signals
;;; emitted into procedures by the system for stuff like unmatched case values
;;; and the like.  It is also used as the implementation of the SIGNAL statement
;;; within procedures.

;;;   SIGNAL-ERROR ()

(def-stack-instruction (signal-error 56 1 2 nil pprint-signal-error-instruction)
  (setq register-1 (arg 0))
  (setq register-2 (arg 1))
  (decff top-of-stack 2)
  (raw-stack-error-1 top-of-stack register-1 register-2))




;;; Instruction 57, the `CALL stack instruction' takes two one byte code
;;; constants in the instruction stream, the number of arguments to send the
;;; called procedure, and the number of values expected back.  This instruction
;;; should take the argument values off the stack and make a procedure argument
;;; list with them.  It should then set the return values count in the current
;;; code body invocation.  Next it creates the code-body-invocation to call and
;;; enqueues it on the immediate stack.

;;;   CALL (argument-count, return-values-count)

#+mtg2
(defun push-faction (procedure)
  (let ((next-fac (faction? procedure)))
    (when (not (memq next-fac current-faction-global))
      (add-faction-to-executing-list next-fac))
    (factions-push next-fac current-faction-global)))
    
#+mtg2
(defun pop-faction ()
  (unless (null (cdr-of-cons current-faction-global))
    (let ((cur-fac (factions-pop current-faction-global)))
      (when (not (memq cur-fac current-faction-global))
	(remove-faction-from-executing-list cur-fac)
	))))

(def-stack-instruction (call 57 3 nil print-call-stack-instruction
			     pprint-call-instruction)
  ;; Fetch arg count.
  (setq fixnum-register-1 (code-constant 0))
  ;; Fetch return value count.
  (setq register-3 (code-constant 1))
  ;; (-f top-of-stack fixnum-register-1)) is index to procedure on the stack.
  ;; Fetch the procedure to call.
  (setq register-1 (svref local-stack (-f top-of-stack fixnum-register-1)))

  ;; Call the function which will perform most of the context switching.
  (multiple-value-setq (register-4 register-5)
    (switch-context-for-procedure-call
      register-1 fixnum-register-1 register-3 local-stack top-of-stack
      (+f stack-program-counter 2) nil))

  (handle-procedure-time-call)

  #+mtg2
  (push-faction register-1)

  (case register-4
    (:error
     (raw-stack-error-named-error top-of-stack register-5))
    (:awaiting-lock
     (incff stack-program-counter 2)
     (inner-context-switch-to-next-computation-instance :unknown))
    (t
     (setq fixnum-time-limit? register-5)
     ;; Pop the arguments off the stack (they were reclaimed by the argument list
     ;; generator).
     (decff top-of-stack)
     (decff top-of-stack fixnum-register-1)
     ;; Execute the remainder of the context switch, which mutates variables local
     ;; to stack-eval.
     (modify-major-stack-eval-locals t) ; Branch to the beginning of the new procedure.
     (modify-minor-stack-eval-locals))))

(defun-simple handle-procedure-time-call ()
  (unless (calculate-time-of-called-procedures miscellaneous-parameters)
    (let* ((current-time (get-fixnum-time))
	   (start-time procedure-start-time)
	   (difference (fixnum-time-difference current-time start-time)))
      (setq procedure-end-time current-time)
      (incff procedure-current-time difference)
      (gensym-push procedure-current-time execution-time-stack)
      (setq procedure-start-time current-time)
      (setq procedure-current-time 0))))

;;; The function `switch-context-for-procedure-call' Returns two values.
;;; If the first value is t, the context switch was successful,
;;; and the returned value is the fixnum-time-limit for the called procedure.
;;; If the first value is :error, an error has occured, and the second value
;;; is the error text. If the first value is :awaiting-lock, the procedure
;;; cannot be called right now, because it is waiting for a lock to be
;;; released, and the caller should do an allow-other-processing. In
;;; this case, the second value is nil.

(defun switch-context-for-procedure-call
    (procedure arg-count return-count local-stack top-of-stack
	       return-program-counter arguments-known-to-be-correct-p?)
  (let ((new-code-body-invocation
 	  (generate-procedure-and-code-body-invocation-in-place
 	    procedure current-computation-instance
 	    local-stack top-of-stack arg-count
 	    evaluating-simulator-procedure? nil top-of-stack
	    arguments-known-to-be-correct-p? 'call
	    (code-body-invocation-thread current-computation-instance))))
    (unless (code-body-invocation-p new-code-body-invocation)
      (return-from switch-context-for-procedure-call (values :error new-code-body-invocation)))
    ;; Set the return value count.
    (setf (invocation-return-value-count current-computation-instance) return-count)
    ;; Store the program counter to return to, and update the frame serial
    ;; number of the current invocation.
    (exit-computation-context-for-code-body-invocation
      current-computation-instance return-program-counter t)
    ;; Silently exit the current tracing context and verbosely enter the new one.
    (exit-tracing-and-breakpoint-context *current-computation-frame* nil)
    (let ((ready-to-execute? (queue-invocation-for-lock-if-necessary
			       new-code-body-invocation)))
      (if ready-to-execute?
	  ;; Switch contexts to the new invocation.
	  (values t (enter-computation-context-for-invocation new-code-body-invocation t))
	  (values :awaiting-lock nil)))))

(defun call-procedure-enter-tracing-context-message (new-procedure-invocation)
  (setq forgive-long-procedure-instruction? t)
  (twith-output-to-text-string
    (twrite-string "Calling procedure ")
    (write-procedure-invocation-instance-from-slot new-procedure-invocation nil)
    (twrite-string ".")))




;;; Instruction 81 `DEPENDENT-CALL stack instruction' takes the same arguments
;;; and performs the same as the CALL stack instruction except for one thing.
;;; Dependent-call is an optimization instruction that does not need to test the
;;; count or type of its arguments.

;;; This instructiontakes two one byte code constants in the instruction stream,
;;; the number of arguments to send the called procedure, and the number of
;;; values expected back.  This instruction should take the argument values off
;;; the stack and make a procedure argument list with them.  It should then set
;;; the return values count in the current code body invocation.  Next it
;;; creates the code-body-invocation to call and enqueues it on the immediate
;;; stack.

;;;   DEPENDENT-CALL (argument-count, return-values-count)

(def-stack-instruction (dependent-call 81 3 nil print-call-stack-instruction
			     pprint-call-instruction)
  ;; Fetch arg count.
  (setq fixnum-register-1 (code-constant 0))
  ;; Fetch return value count.
  (setq register-3 (code-constant 1))
  ;; (-f top-of-stack fixnum-register-1) is index to procedure on the stack.
  ;; Fetch the procedure to call.
  (setq register-1 (svref local-stack (-f top-of-stack fixnum-register-1)))
  ;; Check if the procedure has empty body
  (if (has-empty-code-body-p register-1)
      (progn (incff stack-program-counter 2)
             (decff top-of-stack)
             (decff top-of-stack fixnum-register-1))
  ;; Call the function which will perform most of the context switching.
      (progn (multiple-value-setq (register-4 register-5)
    (switch-context-for-procedure-call
      register-1 fixnum-register-1 register-3 local-stack top-of-stack
      (+f stack-program-counter 2) t))
  (case register-4
    (:error
     (raw-stack-error-named-error top-of-stack register-5))
    (:awaiting-lock
     (incff stack-program-counter 2)
     (inner-context-switch-to-next-computation-instance :unknown))
    (t
     (setq fixnum-time-limit? register-5)
     ;; Pop the arguments off the stack (they were reclaimed by the argument list
     ;; generator).
     (decff top-of-stack)
     (decff top-of-stack fixnum-register-1)
     ;; Execute the remainder of the context switch, which mutates variables local
     ;; to stack-eval.
     (modify-major-stack-eval-locals t) ; Branch to the beginning of the new procedure.
         (modify-minor-stack-eval-locals))))))




(def-stack-error rpc-not-an-interface-error (non-icp-interface top-of-stack)
  "Attempted to call a remote procedure across ~NF, but could not because ~
   it does not have either the G2-TO-G2-DATA-INTERFACE nor the ~
   GSI-INTERFACE capability, and so cannot be a pathway for ~
   a remote procedure call."
  non-icp-interface)

;;; Instruction 58, the `CALL-RPC stack instruction' takes two code constants in
;;; the instruction stream, the number of arguments to send to the called remote
;;; procedure, and the number of values expected back.  This instruction
;;; receives a remote-procedure-declaration, an icp-interface, and the argument
;;; values as arguments (pushed in that order) on the stack.

;;;   CALL-RPC (argument-count, desired-values-count)

(def-stack-instruction (call-rpc 58 3 nil nil pprint-call-rpc-instruction)
  ;; Fetch arg count.
  (setq fixnum-register-1 (code-constant 0))
  ;; Compute index to procedure on the stack.
  (setq fixnum-register-2 (-f top-of-stack fixnum-register-1))
  ;; Fetch the remote procedure to call.
  (setq register-1 (svref local-stack (-f fixnum-register-2 1)))
  ;; Fetch the ICP interface object.
  (setq register-2 (svref local-stack fixnum-register-2))
  ;; Check that it is an ICP interface (no type spec for this yet).
  (unless (or (g2-to-g2-data-interface-p-function register-2)
	      (gsi-interface-p-function register-2))
    (rpc-not-an-interface-error register-2 top-of-stack))
  ;; Make the argument list.
  (setq register-3
	(prepare-procedure-argument-list-for-stack-procedure
	  register-1 local-stack top-of-stack fixnum-register-1 nil))
  ;; Maybe write a major trace message.
  (when major-tracing?
    (write-major-trace-of-rpc-call register-1 register-3 register-2))
  ;; Pop the arguments off the stack (they were reclaimed by the argument list
  ;; generator).
  (decff top-of-stack (+f fixnum-register-1 2))
  ;; Send the call.
  (setq register-5 (call-remote-procedure
		     register-1 register-2 register-3 current-computation-instance))
  (when register-5
    (raw-stack-error-named-error top-of-stack register-5))
  ;; Set the return value count.
  (setf (invocation-return-value-count current-computation-instance)
	(code-constant 1))
  ;; Branch around the code constants.
  (incff stack-program-counter 2)
  ;; Exit evaluations for this code body invocation.
  (inner-context-switch-to-next-computation-instance :unknown))

(defun write-major-trace-of-rpc-call
       (remote-procedure argument-list icp-interface)
  (write-major-trace-message
    (setq forgive-long-procedure-instruction? t)
    (tformat "Calling remote procedure ~NF(" remote-procedure)
    (write-procedure-argument-list argument-list)
    (tformat ") across ~NF." icp-interface)))






;;; Instruction 59, the `PUSH-RETURNED-VALUES stack instruction' is used to push
;;; values just received as a result of a call onto the stack.  The number of
;;; values to push, and their location, are arguments to the instruction.  Note
;;; that this instruction pushes them onto the stack in reverse order, so that
;;; they can be popped off in in forward order.

;;;   PUSH-RETURNED-VALUES ()

(def-stack-instruction (push-returned-values 59 3)
  ;; First returned values index in local-var-vector.
  (setq fixnum-register-1
	(code-constant 1))
  ;; Number of values to push
  (setq fixnum-register-2
	(code-constant 0))
  ;; Last value index.
  (setq fixnum-register-1
	(-f (+f fixnum-register-1
		fixnum-register-2)
	    1))
  (loop while (>f fixnum-register-2 0)
	do
    (incff top-of-stack)
    (setf (svref local-stack top-of-stack)
	  (svref local-var-vector fixnum-register-1))
    (setf (svref local-var-vector fixnum-register-1) nil)
    
    (decff fixnum-register-1)
    (decff fixnum-register-2))
  (incff stack-program-counter 2))


;;; Instruction 141, the `PUSH-RETURNED-VALUES-LONG stack instruction' is used to push
;;; values just received as a result of a call onto the stack when the position
;;; of the return-values placeholders are in the >255th spot in the environment.
;;; The number of values to push, and their location (both longs) are arguments
;;; to the instruction.  Note that this instruction pushes them onto the stack
;;; in reverse order, so that they can be popped off in in forward order.  

;;;   PUSH-RETURNED-VALUES-LONG ()

(def-stack-instruction (push-returned-values-long 141 5)
  ;; First returned values index in local-var-vector.
  (setq fixnum-register-1
	(long-code-constant 1))
  ;; Number of values to push
  (setq fixnum-register-2
	(long-code-constant 0))
  ;; Last value index.
  (setq fixnum-register-1
	(-f (+f fixnum-register-1
		fixnum-register-2)
	    1))
  (loop while (>f fixnum-register-2 0)
	do
    (incff top-of-stack)
    (setf (svref local-stack top-of-stack)
	  (svref local-var-vector fixnum-register-1))
    (setf (svref local-var-vector fixnum-register-1) nil)
    
    (decff fixnum-register-1)
    (decff fixnum-register-2))
  (incff stack-program-counter 4))





;;; Instruction 60, the `JUMP stack instruction' is used to jump from one code
;;; body invocation out to a surrounding code body invocation.  There are two
;;; long code constant arguments, one for the number of code bodies to exit, the
;;; second for the address of the target instruction.

;;; address is now an index into the array of entry-points for the code body
;;; being jumped to. -alatto, 12/15/98

;;; Note that this instruction can currently only be called from procedures,
;;; since they are the only computations that have multiple code bodies.

;;;   JUMP (high-code-body-byte, low-code-body-byte,
;;;         high-address-byte, low-address-byte)

(def-stack-instruction (jump 60 5 nil print-stack-jump)
  (setq register-1 current-computation-instance)
  (setq fixnum-register-1 (long-code-constant 0))
  (loop while (pluspf fixnum-register-1) do
    (setq register-1 (code-body-caller register-1))
    (decff fixnum-register-1))
  #|
  (setf (invocation-stack-program-counter register-1)
	(managed-svref (code-body-entry-points
			 (code-body-of-invocation register-1))
		       (long-code-constant 1)))
  |#
  ;; same thing as above but with more registers used (better for debugging)
  (setq fixnum-register-2 (long-code-constant 1))
  (setq register-2 (code-body-of-invocation register-1))
  (setq register-3 (code-body-entry-points register-2))
  (setq register-4 (managed-svref register-3 fixnum-register-2))
  (setf (invocation-stack-program-counter register-1) register-4)
  (filo-enqueue-immediate-code-body-invocation register-1)
  (inner-context-switch-to-next-computation-instance :code-body-invocation nil t))

(def-stack-instruction-emitter jump (byte-code-stream code-bodies target-tag)
  (register-byte-code-tag-resolution-point byte-code-stream target-tag)
  (emit-instruction-byte-code byte-code-stream 'jump)
  (emit-long-code-constant-to-stream byte-code-stream code-bodies)
  (emit-long-code-constant-to-stream byte-code-stream 0))

(def-byte-code-resolver jump (byte-code-stream byte-vector pc tag)
  (declare (ignore byte-code-stream))
  (let ((code-body-entry current-code-body-entry))
    (dotimes (count (long-code-constant-in-byte-vector byte-vector (+f pc 1)))
      count
      (setf code-body-entry
	    (nth (compiler-code-body-surrounding-body-number? code-body-entry)
		 code-body-entries-in-compilation)))
    (setf (long-code-constant-in-byte-vector byte-vector (+f pc 3))
	  (entry-point-number
	    (instruction-address-for-tag tag t)
	    code-body-entry))))




;;; Instruction 61, the `ABORT-CALLED-CODE-BODIES stack instruction' is used to
;;; abort all code bodies which have been called by this code body.  This
;;; instruction is typically emitted to clean up other code bodies after a
;;; non-local exit from a parallel body, or to stop other executing code bodies
;;; after a do in parallel until one completes.

(def-stack-instruction (abort-called-code-bodies 61 1)
  (setq register-1 (called-code-bodies current-computation-instance))
  (when register-1
    (setq register-2 (copy-list-using-eval-conses register-1))
    (setq register-3 register-2)
    (loop while register-3 do
      (abort-code-body-invocation (car-of-cons register-3))
      (setq register-4 register-3)
      (setq register-3 (cdr-of-cons register-3)))
    (reclaim-eval-list-given-tail register-2 register-4)))

(defun abort-called-code-bodies-function ()
  (let ((called-code-bodies (called-code-bodies current-computation-instance)))
    (when called-code-bodies
      (loop with called-code-bodies-copy
	      = (copy-list-using-eval-conses called-code-bodies)
	    for code-bodies-tail = called-code-bodies-copy
				 then code-bodies-next-tail
	    for code-body = (car-of-cons code-bodies-tail)
	    for code-bodies-next-tail = (cdr-of-cons code-bodies-tail)
	    do (abort-code-body-invocation code-body)
	    while code-bodies-next-tail
	    finally (reclaim-eval-list-given-tail
		      called-code-bodies-copy code-bodies-tail)))))


;;; Instruction 62, the `ALLOW-OTHER-PROCESSING stack instruction' will
;;; deschedule this code-body-invocation if the time slice is expired.  Note
;;; that this instruction can only be called from procedures and rules that have
;;; inlined portions of procedures.

;;;   ALLOW-OTHER-PROCESSING ()

(def-stack-instruction (allow-other-processing 62 1 nil
			nil pprint-allow-other-processing-instruction)
  (when (time-slice-expired-p)
    (schedule-computation-instance-execution
      current-computation-instance priority-of-current-task
      (if (code-body-invocation-p current-computation-instance)
	  (procedure-of-invocation
	    (procedure-invocation-of-code-body current-computation-instance))
	  (ri-rule current-computation-instance)))
    (inner-context-switch-to-next-computation-instance :unknown)))




;;; Instruction 63, the `OPEN-ROLE-ITERATION-NO-DOMAIN stack instruction' takes
;;; two long code constants.  The first is an index into the constant vector
;;; location which contains the role to open.  The second contains an address to
;;; branch to if there are no values in the role.  If there are values in the
;;; role, then this instruction should push the first value and then the
;;; continuation (which may be NIL) onto the stack and continue with the
;;; instruction following this one.

;;;   OPEN-ROLE-ITERATION-NO-DOMAIN (high-role-byte, low-role-byte,
;;;                                  high-no-value-byte, low-no-value-byte)

(def-stack-instruction (open-role-iteration-no-domain 63 5 nil
			 print-open-role-no-domain-iteration
			 pprint-open-role-iteration-no-domain-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  ;; Fetch the value, continuation?, and expiration?.
  (multiple-value-setq (register-1 register-2 register-3)
    (serve-first-item-or-evaluation-value-of-role
      (svref constant-vector fixnum-register-1) nil nil t))
  (cond (register-3
	 (incff top-of-stack 2)
	 (setf (svref local-stack (-f top-of-stack 1)) register-1)
	 (setf (svref local-stack top-of-stack)
	       (make-evaluation-iteration-state register-2))
	 (incff stack-program-counter 4))
	(t
	 (setq stack-program-counter (long-code-constant 1)))))

(def-stack-instruction-emitter open-role-iteration-no-domain
			       (byte-code-stream role no-values-tag)
  (register-byte-code-tag-resolution-point byte-code-stream no-values-tag)
  (emit-instruction-byte-code byte-code-stream 'open-role-iteration-no-domain)
  (emit-long-code-constant-to-stream
    byte-code-stream
    (register-internal-constant-in-byte-code-stream byte-code-stream role))
  (emit-long-code-constant-to-stream byte-code-stream 0))

(def-byte-code-resolver open-role-iteration-no-domain
			(byte-code-stream byte-vector pc tag)
  (declare (ignore byte-code-stream))
  (setf (long-code-constant-in-byte-vector byte-vector (+f pc 3))
	(instruction-address-for-tag tag nil)))




;;; Instruction 64, the `OPEN-ROLE-ITERATION stack instruction' does exactly the
;;; same operation as open-role-iteration-with-no-domain, except that this
;;; instruction additionally takes a domain argument off the top of the stack.
;;; Note that this instruction takes an extra, ignored domain-count argument.
;;; This argument anticipates iterations over roles which take more than one
;;; domain, though this is not currently implemented.

;;;   OPEN-ROLE-ITERATION (high-role-byte, low-role-byte,
;;;                        high-no-value-byte, low-no-value-byte
;;;                        domain-count)

;; Note that now the domain-count is no longer ignored, if the value is zero,
;; then `serve-first-item-or-evaluation-value-of-role' will do a partial search
;; instead. This will NOT break exist compiled KB at all.
;; -- Chun Tian (binghe), 2012/09/16

(def-stack-instruction (open-role-iteration 64 6 1
			 print-open-role-iteration
			 pprint-open-role-iteration-instruction)
  ;; Fetch the value, continuation?, and expiration?.
  (setq register-4 (arg 0))
  (setq fixnum-register-1 (code-constant 4)) ; domain-count
  (setq fixnum-register-2 (long-code-constant 0))
  (multiple-value-setq (register-1 register-2 register-3)
    (serve-first-item-or-evaluation-value-of-role
      (svref constant-vector fixnum-register-2) register-4 nil t
      (=f fixnum-register-1 0))) ; check if the domain-count is zero (0).
  (reclaim-if-evaluation-value register-4)
  (cond (register-3
	 (incff top-of-stack 1)
	 (setf (svref local-stack (-f top-of-stack 1)) register-1)
	 (setf (svref local-stack top-of-stack)
	       (make-evaluation-iteration-state register-2))
	 (incff stack-program-counter 5))
	(t
	 (decff top-of-stack)
	 (setq stack-program-counter (long-code-constant 1)))))

(def-stack-instruction-emitter open-role-iteration
    (byte-code-stream role no-values-tag domain-count)
  (when (and (/=f domain-count 0) (/=f domain-count 1))
    (compiler-bug
      "open role iteration emitter"
      "Iterations can only handle zero or one domain roles, not ~a domains."
      domain-count))
  (register-byte-code-tag-resolution-point byte-code-stream no-values-tag)
  (emit-instruction-byte-code byte-code-stream 'open-role-iteration)
  (emit-long-code-constant-to-stream
    byte-code-stream
    (register-internal-constant-in-byte-code-stream byte-code-stream role))
  (emit-long-code-constant-to-stream byte-code-stream 0)
  (write-byte-code-to-stream byte-code-stream domain-count))

(def-byte-code-resolver open-role-iteration
			(byte-code-stream byte-vector pc tag)
  (declare (ignore byte-code-stream))
  (setf (long-code-constant-in-byte-vector byte-vector (+f pc 3))
	(instruction-address-for-tag tag nil)))




;;; Instruction 65, the `SERVE-NEXT-ITERATION-VALUE stack instruction' is used
;;; to fetch the next value from an iteration state in the local var vector.  It
;;; takes an iterations state evaluation value from the stack and a long code
;;; constant that is the address to branch to if no values are available.  If
;;; there is a value, the iteration-state should be mutated to hold the new
;;; continuation of the role, or reclaimed if there is no continuation left.
;;; The new value should be left on the stack.

;;;   SERVE-NEXT-ITERATION-VALUE (high-no-value-byte, low-no-value-byte)

(def-stack-instruction (serve-next-iteration-value 65 3 1
			 print-serve-next-iteration-value
			 pprint-serve-next-iteration-value-instruction)
  ;; Fetch the iteration state.
  (setq register-1 (arg 0))
  ;; If there is an iteration state, get the continuation.
  (when register-1
    (setq register-2 (evaluation-iteration-state-continuation register-1)))
  (cond (register-2
	 ;; Fetch the value, continuation?, and expiration?.  Always put the
	 ;; returned continuation back into the iteration state.
	 (multiple-value-setq (register-3 register-2 register-4)
	   (serve-next-item-or-evaluation-value-of-role register-2))
	 (setf (evaluation-iteration-state-continuation register-1)
	       register-2))
	(t
	 ;; Else set the expiration to NIL.
	 (setq register-4 nil)))
  ;; Reclaim this reference to the iteration state.  Note that there is still a
  ;; reference to this iteration state in the var-spot which holds it, so the
  ;; continuation will not be closed by this reclamation.
  (reclaim-evaluation-iteration-state register-1)
  ;; If there is an expiration then push the value on the stack and branch
  ;; around the code constants.  Else branch to the no value spot.
  (cond (register-4
	 (setf (svref local-stack top-of-stack) register-3)
	 (incff stack-program-counter 2))
	(t
	 (decff top-of-stack)
	 (setq stack-program-counter (long-code-constant 0)))))

(def-stack-instruction-emitter serve-next-iteration-value
			       (byte-code-stream var-spot no-values-tag)
  (call-stack-instruction-emitter push-from-surrounding-local-var byte-code-stream var-spot)
  (register-byte-code-tag-resolution-point byte-code-stream no-values-tag)
  (emit-instruction-byte-code byte-code-stream 'serve-next-iteration-value)
  (emit-long-code-constant-to-stream byte-code-stream 0))

(def-byte-code-resolver serve-next-iteration-value
			(byte-code-stream byte-vector pc tag)
  (declare (ignore byte-code-stream))
  (setf (long-code-constant-in-byte-vector byte-vector (+f pc 1))
	(instruction-address-for-tag tag nil)))




;;; Instruction 66, the `CLOSE-ITERATION stack instruction' closes and reclaims
;;; the iteration-state on the stack.  Note that if there is a NIL on the stack,
;;; this instruction should not complain.

;;; Also note that the iteration state came from some var-spot, but this is left
;;; where it is.  Iteration states are reclaimed based on reference counts,
;;; though it is okay to close the held continuation within the iteration state.
;;; This instruction will close the continuation held in the iteration state,
;;; but it is only when the iteration-state value in the var-spot is overwritten
;;; or reclaimed that the iteration state itself will be reclaimed.

;;;   CLOSE-ITERATION ()

(def-stack-instruction (close-iteration 66 1 1)
  ;; Fetch the local var index.
  (setq register-1 (arg 0))
  (decff top-of-stack)
  (when register-1
    (close-evaluation-iteration-state-continuation register-1)
    (reclaim-evaluation-iteration-state register-1)))

(def-stack-instruction-emitter close-iteration (byte-code-stream var-spot)
  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
    byte-code-stream var-spot)
  (emit-instruction-byte-code byte-code-stream 'close-iteration))




;;; Instruction 67, the `CLOSE-CODE-BODY stack instruction' closes the current
;;; code body and reschedules the caller of this code body.

;;;   CLOSE-CODE-BODY ()

(def-stack-instruction (close-code-body 67 1)
  (setq register-1 (code-body-caller current-computation-instance))
  (when register-1
    (filo-enqueue-immediate-code-body-invocation register-1))
  (close-code-body-invocation current-computation-instance)
  (inner-context-switch-to-next-computation-instance :none nil t))




;;; Instruction 68, the `CALL-CODE-BODY stack instruction' creates and schedules
;;; for immediate execution a new code-body-invocation, called from the current
;;; code body invocation.  This instruction takes two code constants, the code
;;; body number for the code body to be launched (basically a count into the
;;; list of code bodies in a procedure), and a count of the number of arguments
;;; to pop off the stack and place into the new code body as arguments.  The
;;; arguments to a code body are always the first N values in its environment
;;; vector.

;;;   CALL-CODE-BODY (code-body-number, argument-count)

(def-stack-instruction (call-code-body 68 3 nil print-stack-call-code-body)
  ;; New code body number.
  (setq fixnum-register-1 (code-constant 0))
  ;; Number of arguments on stack minus one.  Note that the top of stack
  ;; contains the last argument.
  (setq fixnum-register-2 (code-constant 1))
  (decff fixnum-register-2)
  ;; Code body to call.
  (setq register-1
	(procedure-code-body-given-number
	  (procedure-of-invocation
	    (procedure-invocation-of-code-body current-computation-instance))
	  fixnum-register-1))
  ;; New code body invocation.
  (setq register-2 (generate-code-body-invocation
		     register-1 current-computation-instance
		     ;; If this is an on error block it's in the same thread;
		     ;; if it's a do-in-parallel, it's a new thread.
		     (when
		       (code-body-error-handler-spec? register-1)
		       (code-body-invocation-thread current-computation-instance))))
  ;; New environment.
  (setq register-3 (invocation-local-var-vector register-2))
  ;; Use fixnum-register-2 as the index into the new environment, and keep
  ;; popping values off the stack into the new environment until the index goes
  ;; negative.
  (loop while (>=f fixnum-register-2 0) do
    (setf (svref register-3 fixnum-register-2)
	  (svref local-stack top-of-stack))
    (decff fixnum-register-2)
    (decff top-of-stack))
  ;; Fifo schedule the new invocation on the immediate queue, and branch around
  ;; the code constants.
  (enqueue-immediate-code-body-invocation register-2)
  (incff stack-program-counter 2))

(def-stack-instruction-emitter call-code-body
    (byte-code-stream code-body-number argument-count)
  (emit-instruction-byte-code byte-code-stream 'call-code-body)
  (write-byte-code-to-stream byte-code-stream code-body-number)
  (write-byte-code-to-stream byte-code-stream argument-count))




;;; Instruction 69, the `CALL-SCHEDULED-CODE-BODY stack instruction' creates and
;;; schedules for current execution a new code-body-invocation, called from the
;;; current code body invocation.  Note that this instruction is just like
;;; call-code-body, except that there is an implicit allow other processing
;;; between the launch of this code body and its execution.  This is used when
;;; launching parallel looping code bodies, to allow arbitrary numbers of them
;;; to be launched without exceeding the limits for uninterrupted procedure
;;; execution.  This instruction takes two code constants, the code body number
;;; for the code body to be launched (basically a count into the list of code
;;; bodies in a procedure), and a count of the number of arguments to pop off
;;; the stack and place into the new code body as arguments.  The arguments to a
;;; code body are always the first N values in its environment vector.

;;;   CALL-SCHEDULED-CODE-BODY (code-body-number, argument-count)

(def-stack-instruction (call-scheduled-code-body 69 3 nil
			print-stack-call-code-body)
  ;; New code body number.
  (setq fixnum-register-1 (code-constant 0))
  ;; Number of arguments on stack minus one.  Note that the top of stack
  ;; contains the last argument.
  (setq fixnum-register-2 (code-constant 1))
  ;; The procedure.
  (setq register-4
	(procedure-of-invocation
	  (procedure-invocation-of-code-body current-computation-instance)))
  ;; Code body to call.
  (setq register-1
	(procedure-code-body-given-number
	  register-4
	  fixnum-register-1))
  ;; New code body invocation.
  (setq register-2 (generate-code-body-invocation
		     register-1 current-computation-instance nil))
  ;; New environment.
  (setq register-3 (invocation-local-var-vector register-2))
  ;; Use fixnum-register-2 as the index into the new environment, and keep
  ;; popping values off the stack into the new environment until the index goes
  ;; negative.
  (loop while (>f fixnum-register-2 0) do
    (decff fixnum-register-2)
    (setf (svref register-3 fixnum-register-2)
	  (svref local-stack top-of-stack))
    (decff top-of-stack))
  ;; Fifo Schedule the new invocation on the immediate queue, and branch around
  ;; the code constants
  (schedule-computation-instance-execution
    register-2 priority-of-current-task register-4)
  (incff stack-program-counter 2))

(def-stack-instruction-emitter call-scheduled-code-body
    (byte-code-stream code-body-number argument-count)
  (emit-instruction-byte-code byte-code-stream 'call-scheduled-code-body)
  (write-byte-code-to-stream byte-code-stream code-body-number)
  (write-byte-code-to-stream byte-code-stream argument-count))




;;; Instruction 70, the `WAIT-FOR-CALLED-CODE-BODIES stack instruction' will
;;; enter a wait state if there are ongoing called code bodies from the current
;;; code body invocation.  If there are, this instruction decrements the program
;;; counter to restart at this instruction again, and exits the instruction
;;; interpreter.  The called bodies will schedule this code body invocation to
;;; run again when they return.  Note that this instruction can only be called
;;; from procedures.

;;;   WAIT-FOR-CALLED-CODE-BODIES ()

(def-stack-instruction (wait-for-called-code-bodies 70 1)
  (when (called-code-bodies current-computation-instance)
    (decff stack-program-counter)
    (inner-context-switch-to-next-computation-instance :code-body-invocation)))




;;; Instruction 71 is available.

;;; Instruction 71, the `TYPE-CHECK-ITEM stack instruction' checks if the thing
;;; on the top of the stack is an item, and signals an error if it is not.  This
;;; instruction is an optimization of the type-check-class instruction, which
;;; itself is an optimization of type-check.

;;;   TYPE-CHECK-ITEM ()

(def-stack-instruction (type-check-item 71 1 1
			nil pprint-type-check-item-instruction)
  (setq register-1 (arg 0))
  (unless (thing-is-item-p register-1)
    (signal-stack-class-type-check-error register-1 'item top-of-stack)))




;;; Instruction 72, the `PAUSE stack instruction' causes the current code body
;;; invocation to enter a wait state.  It will have to be woken up by something
;;; else to continue running.  When this procedure is worken up, execution
;;; continues at the following instruction.  Note that this instruction can be
;;; called from procedures or simulation-formulas.

;;;   PAUSE ()

(def-stack-instruction (pause 72 1)
  (inner-context-switch-to-next-computation-instance :unknown))




;;; Instruction 73, the `PAUSE-IF-CALLED-CODE-BODIES stack instruction' is like
;;; pause, in that it causes this code body invocation to enter a wait state
;;; from which it is only woken up by something else, but this instruction will
;;; only enter that state if there are called code bodies of this code body
;;; which actaully could wake it up.  Note that this can only be called from
;;; procedures.

;;;   PAUSE-IF-CALLED-CODE-BODIES ()

(def-stack-instruction (pause-if-called-code-bodies 73 1)
  (when (called-code-bodies current-computation-instance)
    (inner-context-switch-to-next-computation-instance :code-body-invocation)))






;;;; Stack Instructions to Splice Back In




;;; The following stack instructions should be grouped up with the other coerce
;;; and parameter-value instructions above, and their instruction numbers
;;; changed to fit in the "natural order of things".

;;; Instruction 74, the `VARIABLE-VALUE-OR-UNKNOWN stack instruction' pops a
;;; variable off the top of the stack and replaces that variable with its
;;; value.  This instruction will also minimize the expiration of the variable
;;; with the global stack-expiration.  If the variable has no value, then the
;;; global expiration becomes never, and NIL is pushed onto the stack.

;; Note that this instruction can only be executed from within instructions
;; implementing a wake-up-management environment, whatever the hell that is.
;; After having just looking at proc-utils and the old collect data statement, I
;; realize I'm in some trouble over this, since wake up management macros all
;; depend upon a recursive descent evaluation approach.  Oh well, I'll have to
;; rewrite them all.  -jra 4/24/91

;;; VARIABLE-VALUE-OR-UNKNOWN ()

(def-stack-instruction (variable-value-or-unknown 74 1 1
			nil pprint-fetch-value-of)
  (setq register-1 (arg 0))
  (setq register-2 (get-current-value-based-on-current-environment register-1 top-of-stack))
  (setf (arg 0) register-2))




;;; Instruction 75, the `COERCE-TO-DATUM-OR-UNKNOWN stack instruction' takes one
;;; argument off the stack and coerces it to a datum or unknown, or else signals
;;; an error.  The argument could already be a datum or it could be any kind of
;;; item, but it must be either a datum or a variable-or-parameter.

;;; This instruction has been modified to also allow NO-ITEM as an argument in
;;; some circumstances.  When the code constant argument is non-zero, then NIL
;;; stack arguments (i.e. a value of type (NO-ITEM)) gets coerced to UNKNOWN.
;;; If the code constant argument is zero, then it behaves as before, and
;;; requires arguments of type (or datum (class variable-or-parameter)), and
;;; signals errors otherwise.

;;;   COERCE-TO-DATUM-OR-UNKNOWN (allow-no-item)

(def-stack-error signal-coerce-to-datum-error (thing class top-of-stack)
  (if (framep thing)
      "Attempted to get a value from ~NF, but it was not a ~a."
      "Expected some kind of value, but received ~NV.")
  thing class)

(def-stack-instruction (coerce-to-datum-or-unknown 75 2 1
			 print-op-and-code-constant
			 pprint-fetch-value-of)
  (setq register-1 (arg 0))
  (cond ((evaluation-datum-p-given-register register-1 register-2)
	 ;; This will be a noop.
	 nil)
	((thing-is-variable-or-parameter-p register-1)
	 (setq register-1
	       (get-current-value-based-on-current-environment register-1 top-of-stack)))
	((and (null register-1)
	      (/=f (code-constant 0) 0))
	 (setq stack-expiration nil))
	(t
	 (signal-coerce-to-datum-error
	   register-1 'variable-or-parameter top-of-stack)))
  (setf (arg 0) register-1)
  (incff stack-program-counter))

(declare-side-effect-free-function thing-is-variable-or-parameter-p)

(defun-simple thing-is-variable-or-parameter-p (thing)
  (of-class-p thing 'variable-or-parameter))

(def-stack-instruction-emitter coerce-to-datum-or-unknown
			       (byte-code-stream allow-no-item?)
  (emit-instruction-byte-code byte-code-stream 'coerce-to-datum-or-unknown)
  (write-byte-code-to-stream
    byte-code-stream
    (if allow-no-item? 1 0)))



;;; Instruction 76, the `COERCE-TO-DATUM stack instruction' takes one argument
;;; off the stack and coerces it to a datum.  The argument could be an evaluation
;;; value or any item, but this instruction signals an error when it is a
;;; non-parameter item.

;;; This instruction has been modified to take a code constant argument which
;;; controls whether or not this instruction allows no-item values to pass
;;; through unchanged.  If the code constant is 0, no-item is not allowed, but
;;; if the code constant is anything but zero, then this instruction accepts
;;; no-item (i.e.  NIL at runtime) as a valid argument and leaves it on the
;;; stack.  -jra & cpm 11/19/91

;;;   COERCE-TO-DATUM (no-item-allowed)

(def-stack-instruction (coerce-to-datum 76 2 1 print-op-and-code-constant
					pprint-fetch-value-of)
  (setq register-1 (arg 0))
  (cond ((evaluation-datum-p-given-register register-1 register-3)
	 ;; This will be a noop.
	 nil)
	((thing-is-parameter-p register-1)
	 (setq register-1
	       (get-current-value-based-on-current-environment register-1 top-of-stack)))
	((and (null register-1)
	      (/=f (code-constant 0) 0))
	 nil)
	(t
	 (signal-coerce-to-datum-error
	   register-1 'parameter top-of-stack)))
  (setf (arg 0) register-1)
  (incff stack-program-counter))

(declare-side-effect-free-function thing-is-parameter-p)

(defun thing-is-parameter-p (thing)
  (of-class-p thing 'parameter))

(def-stack-instruction-emitter coerce-to-datum
			       (byte-code-stream no-item-allowed?)
  (emit-instruction-byte-code byte-code-stream 'coerce-to-datum)
  (write-byte-code-to-stream
    byte-code-stream
    (if no-item-allowed? 1 0)))




;;; Instruction 77, the `PUSH-COPY-OF-TOP-OF-STACK stack instruction' looks at
;;; the value on the top of the stack, and pushes a copy of it onto the stack.

;;;   PUSH-COPY-OF-TOP-OF-STACK ()

(def-stack-instruction (push-copy-of-top-of-stack 77 1 1)
  (setq register-1 (arg 0))
  (incff top-of-stack)
  (setf register-1 (copy-if-evaluation-value register-1))
  (setf (svref local-stack top-of-stack) register-1))




;;; Instruction 78, the `POP-COPY-DOWN-THE-STACK stack instruction' reclaims
;;; values that are down from the top of the stack, and copies the value on the
;;; top of the stack down into the stack, and decrements top-of-stack by the
;;; number of values that have been reclaimed off the stack.  The number of
;;; stack slots to pop the top value down is held in a single code constant
;;; argument.  This instruction is used to discard values lower in the stack
;;; when the value currently on the top of the stack is the one which we wish to
;;; use as the result of a computation, typically popping past variables local
;;; to stack frames.

;;;   POP-COPY-DOWN-THE-STACK (values-to-pop)

(def-stack-instruction (pop-copy-down-the-stack 78 2 1
			print-op-and-code-constant)
  (setq fixnum-register-1 (code-constant 0))	; Values to pop
  (setq register-1 (arg 0))			; Cached top value
  (loop while (>f fixnum-register-1 0)
	do
    (decff fixnum-register-1)
    (decff top-of-stack)
    (setq register-2 (svref local-stack top-of-stack))
    (reclaim-if-evaluation-value register-2))
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter))

(def-stack-instruction-emitter pop-copy-down-the-stack (byte-code-stream count)
  (multiple-value-bind (overflows remainder)
      (floorf-positive-2 count 255)
    (loop repeat overflows do
      (emit-instruction-byte-code byte-code-stream 'pop-copy-down-the-stack)
      (write-byte-code-to-stream byte-code-stream 255))
    (when (>f remainder 0)
      (emit-instruction-byte-code byte-code-stream 'pop-copy-down-the-stack)
      (write-byte-code-to-stream byte-code-stream remainder))))



;;; Abstractions For Logical Types
;;;
;;; The truth-value types are represented to the user as "true", "false" and "n
;;; true" where n is a number from -.999 to .999. Internally, truth values are
;;; represented as parameters, embedded constants, or multiple values where the
;;; type is 'truth-value, and the value is an integer within [-1000,
;;; 1000]. (This is to avoid floating point internally for G.C. reasons.)

(defmacro fuzzy-and (&body body)
  `(minf ,@body))

(defmacro fuzzy-or (&body body)
  `(maxf ,@body))

(defmacro fuzzy-not (expression)
  `(-f ,expression))

(defmacro as-true-as (x y)
  `(>=f ,x ,y))

(defmacro as-false-as (x y)
  `(<=f ,x ,y))



;;; Instruction 79, the `FUZZY-AND stack instruction' takes two truth-value
;;; arguments off the stack, performs a fuzzy and on them, and pushes the result
;;; back onto the stack.

;;;   FUZZY-AND ()

(def-stack-instruction (fuzzy-and 79 1 2 nil pprint-and-instruction)
  (setq register-1 (arg 0))
  (setq register-2 (arg 1))
  (setq fixnum-register-1 (evaluation-truth-value-value register-1))
  (setq fixnum-register-2 (evaluation-truth-value-value register-2))
  (setq fixnum-register-1 (fuzzy-and fixnum-register-1 fixnum-register-2))
  (reclaim-evaluation-truth-value register-1)
  (reclaim-evaluation-truth-value register-2)
  (decff top-of-stack)
  (setq register-1 (make-evaluation-truth-value fixnum-register-1))
  (setf (svref local-stack top-of-stack) register-1))




;;; Instruction 80, the `FUZZY-OR stack instruction' takes two truth-value
;;; arguments off the stack, performs a fuzzy or on them, and pushes the result
;;; back onto the stack.

;;;   FUZZY-OR ()

(def-stack-instruction (fuzzy-or 80 1 2 nil pprint-or-instruction)
  (setq register-1 (arg 0))
  (setq register-2 (arg 1))
  (setq fixnum-register-1 (evaluation-truth-value-value register-1))
  (setq fixnum-register-2 (evaluation-truth-value-value register-2))
  (setq fixnum-register-1 (fuzzy-or fixnum-register-1 fixnum-register-2))
  (reclaim-evaluation-truth-value register-1)
  (reclaim-evaluation-truth-value register-2)
  (decff top-of-stack)
  (setq register-1 (make-evaluation-truth-value fixnum-register-1))
  (setf (svref local-stack top-of-stack) register-1))




;;; Instruction 81, is used by the DEPENDENT-CALL stack-instruction.




;;; Instruction 82, the `PUSH-FROM-ALLOW-DATA-SEEKING stack instruction' is
;;; used to push an evaluation truth value reflecting the value of the
;;; do-not-compute-new-variable-values special variable.  If new value computing
;;; is allowed, this function pushes true, otherwise it pushes false.

;;;   PUSH-FROM-ALLOW-DATA-SEEKING ()

(def-stack-instruction (push-from-allow-data-seeking 82 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(if (dont-compute-new-variable-values)
	    (make-evaluation-truth-value falsity)
	    (make-evaluation-truth-value truth))))




;;; Instruction 83, the `POP-INTO-ALLOW-DATA-SEEKING stack instruction' is used
;;; to change the value of do-not-compute-new-variable-values.  If a true is on
;;; the stack, the variable should be set to nil, and false is on the stack,
;;; then the variable is set to true.

;;;   POP-INTO-ALLOW-DATA-SEEKING ()

(def-stack-instruction (pop-into-allow-data-seeking 83 1 1)
  (setq register-1 (arg 0))
  (if (>=f (evaluation-truth-value-value register-1) local-truth-threshold)
      (setf (dont-compute-new-variable-values) nil)
      (setf (dont-compute-new-variable-values) t))
  (reclaim-evaluation-truth-value register-1)
  (decff top-of-stack))




;;; Instruction 84, the `OPEN-WAKE-UP-COLLECTION stack instruction' is used to
;;; remove any existing wake ups from the current computation instance before
;;; executing instructions which could fetch the values of variables.  This
;;; corresponds to the pre-body portion of the macro remove-wake-ups-and-clean-
;;; up-after-body.  The postponed wake-ups are cached in the current computation
;;; instance.  If an error occurs during the execution of this
;;; computation-instance, the wake ups which had been collected must be cleared
;;; using set-pending-wakups or clear-pending-wake-ups, and then the postponed
;;; wake ups must be processed with perform-postponed-clean-ups.

;;;   OPEN-WAKE-UP-COLLECTION ()

(def-stack-instruction (open-wake-up-collection 84 1)
  (setq register-1 (open-wake-up-collection-function top-of-stack))
  (when register-1
    (raw-stack-error-named-error top-of-stack register-1)))

(def-stack-error unknown-instance-error (top-of-stack)
  "An unknown type of current computation instance was encountered in ~
   enable-wake-up-collection.  Please report this stack eval bug to ~
   Gensym software support.")

(defun unknown-instance-warning ()
  (warning-message* 1
      "An unknown type of current computation instance was encountered in ~
       enable-wake-up-collection.  Please report this stack eval bug to ~
       Gensym software support."))

(defun open-wake-up-collection-function (top-of-stack?)
  (let ((wake-ups nil)
	(wake-up-holder nil))
    (prog1 (cond ((code-body-invocation-p current-computation-instance)
		  (setq wake-ups (things-this-code-body-invocation-is-interested-in
				   current-computation-instance))
		  (setf (things-this-code-body-invocation-is-interested-in
			  current-computation-instance)
			nil)
		  (setf (code-body-invocation-postponed-clean-ups
			  current-computation-instance)
			wake-ups)
		  (setq wake-up-holder current-computation-instance)
		  nil)
		 ((rule-instance-p current-computation-instance)
		  (setq wake-ups (ri-things-this-rule-instance-is-interested-in
				   current-computation-instance))
		  (setf (ri-things-this-rule-instance-is-interested-in
			  current-computation-instance)
			nil)
		  (setf (ri-postponed-clean-ups current-computation-instance)
			wake-ups)
		  (setq wake-up-holder current-computation-instance)
		  nil)
		 ((formula-invocation-p current-computation-instance)
		  (let ((variable
			  (formula-invocation-variable current-computation-instance)))
		    (setf wake-ups (things-this-variable-is-interested-in variable))
		    (setf (things-this-variable-is-interested-in variable) nil)
		    (setf (formula-invocation-postponed-clean-ups
			    current-computation-instance)
			  wake-ups)
		    (setq wake-up-holder variable))
		  nil)
		 ((inference-background-collection-p current-computation-instance)
		  (setf wake-ups
			(things-this-inference-background-collection-is-interested-in
			  current-computation-instance))
		  (setf (things-this-inference-background-collection-is-interested-in
			  current-computation-instance)
			nil)
		  (setf (inference-background-collection-postponed-clean-ups
			  current-computation-instance)
			wake-ups)
		  (setq wake-up-holder current-computation-instance)
		  nil)
		 ((of-class-p current-computation-instance 'g2-expression-cell)
		  (setq wake-ups (things-this-g2-expression-cell-is-interested-in
				   current-computation-instance))
		  (setf (things-this-g2-expression-cell-is-interested-in
			  current-computation-instance)
			nil)
		  (setf (g2-expression-cell-postponed-clean-ups
			  current-computation-instance)
			wake-ups)
		  (setq wake-up-holder current-computation-instance)
		  nil)
		 (top-of-stack?
		  (unknown-instance-error-message))
		 (t
		  (unknown-instance-warning)))
      (when wake-ups
	(remove-wake-ups-postponing-clean-up wake-up-holder wake-ups)))))




;;; Instruction 85, the `SET-WAKE-UPS stack instruction' is executed to commit
;;; to the request for variable values which have been registered while
;;; executing a computation.

(def-stack-instruction (set-wake-ups 85 1)
  (setq register-1 (set-wake-ups-function top-of-stack))
  (when register-1
    (raw-stack-error-named-error top-of-stack register-1)))

(defun set-wake-ups-function (top-of-stack?)
  (let ((interesting-variables *variables-that-did-not-have-values*)
	(variable? (if (formula-invocation-p current-computation-instance)
		       (formula-invocation-variable current-computation-instance)
		       nil)))
    (when interesting-variables
      (setq *variables-that-did-not-have-values* nil)
      (set-pending-wake-ups
	(if variable? variable? current-computation-instance)
	interesting-variables)
      (cond
	(variable?
	 (let* ((already-interesting-variables
		  (things-this-variable-is-interested-in variable?)))
	   (when already-interesting-variables
	     (setq interesting-variables
		   (nconc interesting-variables already-interesting-variables)))
	   (setf (things-this-variable-is-interested-in variable?)
		 interesting-variables))
	 nil)
	((code-body-invocation-p current-computation-instance)
	 (let ((already-interesting-variables
		 (things-this-code-body-invocation-is-interested-in
		   current-computation-instance)))
	   (when already-interesting-variables
	     (setq interesting-variables
		   (nconc interesting-variables already-interesting-variables)))
	   (setf (things-this-code-body-invocation-is-interested-in
		   current-computation-instance)
		 interesting-variables))
	 nil)
	((rule-instance-p current-computation-instance)
	 (let ((already-interesting-variables
		 (ri-things-this-rule-instance-is-interested-in
		   current-computation-instance)))
	   (when already-interesting-variables
	     (setq interesting-variables
		   (nconc interesting-variables already-interesting-variables)))
	   (setf (ri-things-this-rule-instance-is-interested-in
		   current-computation-instance)
		 interesting-variables))
	 nil)
	((inference-background-collection-p current-computation-instance)
	 (let ((already-interesting-variables
		 (things-this-inference-background-collection-is-interested-in
		   current-computation-instance)))
	   (when already-interesting-variables
	     (setq interesting-variables
		   (nconc interesting-variables already-interesting-variables)))
	   (setf (things-this-inference-background-collection-is-interested-in
		   current-computation-instance)
		 interesting-variables))
	 nil)
	((of-class-p current-computation-instance 'g2-expression-cell)
	 (let ((already-interesting-variables
		 (things-this-g2-expression-cell-is-interested-in
		   current-computation-instance)))
	   (when already-interesting-variables
	     (setq interesting-variables
		   (nconc interesting-variables already-interesting-variables)))
	   (setf (things-this-g2-expression-cell-is-interested-in
		   current-computation-instance)
		 interesting-variables))
	 nil)
	(top-of-stack?
	 (unknown-instance-error-message))
	(t
	 (unknown-instance-error top-of-stack?))))))




;;; Instruction 86, the `CLEAR-WAKE-UPS stack instruction' is executed to clear
;;; any pending requests for the values of variables.

(def-stack-instruction (clear-wake-ups 86 1)
  (clear-pending-wake-ups))




;;; Instruction 87, the `CLOSE-WAKE-UP-COLLECTION stack instruction' is executed
;;; to close out a wake up collecting execution.  This instruction should be
;;; called after wake ups have been cleared or set.  This instruction will
;;; perform any postponed clean ups on the wake ups removed withint the
;;; open-wake-up-collection instruction.  A call to this instruction must be
;;; made to close any wake up collection intervals previously opened.  If an
;;; error occurs in the stream of executing instructions, then the function
;;; clean-up-wake-ups-state-if-any must be called from the error handler.

(def-stack-instruction (close-wake-up-collection 87 1)
  (clean-up-wake-ups-state-if-any))




;;; The function `clean-up-wake-ups-state-if-any' clears any pending requests
;;; for variable values and processes any postponed clean ups.  This function is
;;; called from the error catcher and the close-wake-up-collection instruction.

(defun clean-up-wake-ups-state-if-any ()
  (clear-pending-wake-ups)
  (let ((computation-instance current-computation-instance))
    (when computation-instance
      (cond
	((code-body-invocation-p computation-instance)
	 (perform-postponed-clean-ups
	   computation-instance
	   (code-body-invocation-postponed-clean-ups
	     computation-instance))
	 (setf (code-body-invocation-postponed-clean-ups
		 computation-instance)
	       nil))
	((rule-instance-p computation-instance)
	 (perform-postponed-clean-ups
	   computation-instance
	   (ri-postponed-clean-ups computation-instance))
	 (setf (ri-postponed-clean-ups computation-instance)
	       nil))
	((formula-invocation-p computation-instance)
	 (perform-postponed-clean-ups
	   (formula-invocation-variable computation-instance)
	   (formula-invocation-postponed-clean-ups computation-instance))
	 (setf (formula-invocation-postponed-clean-ups computation-instance)
	       nil))
	((inference-background-collection-p computation-instance)
	 (perform-postponed-clean-ups
	   computation-instance
	   (inference-background-collection-postponed-clean-ups
	     computation-instance))
	 (setf (inference-background-collection-postponed-clean-ups
		 computation-instance)
	       nil))
	((of-class-p computation-instance 'g2-expression-cell)
	 (perform-postponed-clean-ups
	   computation-instance
	   (g2-expression-cell-postponed-clean-ups
	     computation-instance))
	 (setf (g2-expression-cell-postponed-clean-ups
		 computation-instance)
	       nil))
	((error-occurred-in-simulator?))
	(t
	 #+development
	 (cerror "Continue" "Unknown instance in wake ups state.")
	 ;; If control goes here, rather than unknown type of computation instances,
	 ;; it's more likely that a known type of computation instance was wrongly
	 ;; reclaimed before goes here.  -- Chun Tian (binghe), Mar 2015.
	 (warning-message* 1
	   "An unknown type of current computation instance was encountered in ~
            clean-up-wake-ups-state-if-any.  Please report this stack eval ~
            bug to Gensym software support.")))))
  nil)

(defun error-occurred-in-simulator? ()
  within-simulator-for-stack-error?)



;;; Instruction 88, the WAIT-FOR-INTERVAL stack instruction takes a number off
;;; the stack reflecting how many seconds this procedure should wait and
;;; schedules a task to wait for that interval.  Note that it is OK for other
;;; events (such as wake ups) to revive the procedure before the wait interval
;;; has passed.  Note that this instruction can be called from procedures or
;;; from rules that have inlined a procedure.

;;;   WAIT-FOR-INTERVAL ()

(def-stack-instruction (wait-for-interval
			 88 1 1 nil pprint-wait-for-interval-instruction)
  (setq register-1 (arg 0))
  (decff top-of-stack)
  (when (schedule-wait-for-interval-task register-1)
    (inner-context-switch-to-next-computation-instance :unknown)))

(defun-simple schedule-wait-for-interval-task (evaluation-quantity)
  (let ((float-delay (evaluation-quantity-value-as-float evaluation-quantity)))
    (declare (type gensym-float float-delay))
    (reclaim-evaluation-quantity evaluation-quantity)
    (cond ((>e float-delay 0.0)
	   (schedule-delayed-computation-instance-execution
	     current-computation-instance
	     priority-of-current-task
            *current-computation-frame*
	     float-delay)
	   t)
	  (t nil))))
	  




;;; Instruction 89, the `POP-INTO-FINAL-EVALUATION-ATTEMPT stack instruction'
;;; changes the value of the global varaible final-evaluation-attempt? based on
;;; a truth value stack argument.  Collect data uses this to control whether or
;;; not this is the final attempt at evaluation before timeout.

(def-stack-instruction (pop-into-final-evaluation-attempt 89 1 1)
  (setq register-1 (arg 0))
  (decff top-of-stack)
  (if (>=f (evaluation-truth-value-value register-1) local-truth-threshold)
      (setf (final-evaluation-attempt?) t)
      (setf (final-evaluation-attempt?) nil))
  (reclaim-evaluation-truth-value register-1))




;;; Instruction 90, the `PUSH-WAKE-UPS-COUNT stack instruction' pushes onto the
;;; stack the number of variables currently in the variables that did not have
;;; values list.  This is used by has a value to cache the number of already
;;; seeking variables before executing an expression.

(def-stack-instruction (push-wake-ups-count 90 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(make-evaluation-integer
	  (length *variables-that-did-not-have-values*))))




;;; Instruction 91, the `TYPE-CHECK stack instruction' takes a long constant
;;; index to a type.  This instruction checks that the value on the top of the
;;; stack is of that type, or else it signals an error.  Note that this
;;; instruction can take any valid type specification.  Other instructions are
;;; provided as optimized type checkers for specific types.

;;;   TYPE-CHECK (type-high-byte, type-low-byte)

(def-stack-instruction (type-check 91 3 1 print-op-and-type-long
				   pprint-type-check-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  (setq register-1 (arg 0))			; value
  (setq register-2 (svref constant-vector fixnum-register-1))	; type
  (unless (type-specification-type-p register-1 register-2)
    (cond ((and (type-specification-subtype-p 'float register-2)
		(evaluation-integer-p register-1))
	   (setq register-3 (evaluation-integer-value register-1))
	   (reclaim-evaluation-integer register-1)
	   (setf (arg 0)
		 (make-evaluation-float
		   (coerce-fixnum-to-gensym-float register-3))))
	  (t
	   (signal-stack-type-check-error register-1 register-2 top-of-stack))))
  (incff stack-program-counter 2))




;;; Instruction 92, the `PUSH-NONES stack instruction' takes a code constant for
;;; the number of NILS that it should push onto the stack.

;;;   PUSH-NONES (count)

(def-stack-instruction (push-nones 92 2 0 print-op-and-code-constant)
  (setq fixnum-register-1 (code-constant 0))
  (loop while (>f fixnum-register-1 0)
	do
    (decff fixnum-register-1)
    (incff top-of-stack)
    (setf (svref local-stack top-of-stack) nil))
  (incff stack-program-counter))

(def-stack-instruction-emitter push-nones (byte-code-stream count)
  (multiple-value-bind (overflows remainder)
      (floorf-positive-2 count 255)
    (loop repeat overflows
	  do
      (emit-instruction-byte-code byte-code-stream 'push-nones)
      (write-byte-code-to-stream byte-code-stream 255))
    (cond ((=f remainder 1)
	   (emit-instruction-byte-code byte-code-stream 'push-none))
	  ((>f remainder 0)
	   (emit-instruction-byte-code byte-code-stream 'push-nones)
	   (write-byte-code-to-stream byte-code-stream remainder)))))




;;; Instruction 93, the `PUSH-VALUE-OR-NONE-FROM-SURROUNDING-LOCAL-VAR
;;; stack instruction' takes a two byte index into the constant vector,
;;; to a location holding a local var index.  This instructions pushes
;;; the value held in the denoted local var, pushing none (i.e. NIL), if
;;; there is no current binding of that variable.

;;;   PUSH-VALUE-OR-NONE-FROM-SURROUNDING-LOCAL-VAR (high-byte, low-byte)

(def-stack-instruction (push-value-or-none-from-surrounding-local-var
			 93 4 nil print-op-and-surrounding-local-var-and-typecode
			 pprint-push-from-surrounding-local-var-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  (setq fixnum-register-2 (var-spot-index-nesting fixnum-register-1))
  (setq register-2 current-computation-instance)
  (loop while (pluspf fixnum-register-2) do
    (setq register-2 (code-body-caller register-2))
    (decff fixnum-register-2))
  (setq register-2 (invocation-local-var-vector register-2))
  (setq register-3
	(svref register-2 (var-spot-local-index fixnum-register-1)))
  (setq fixnum-register-1 (code-constant 2))
  (copy-if-evaluation-value-given-typecode-err-on-nil
    register-3 fixnum-register-1
    nil)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-3)
  (incff stack-program-counter 3))

(def-stack-instruction-emitter push-value-or-none-from-surrounding-local-var (byte-code-stream var-spot)
  (cond ((eq (car var-spot) 'stack-frame-var)
	 (call-stack-instruction-emitter push-value-or-none-from-stack-frame-var
	   byte-code-stream var-spot))
	((eq (car var-spot) 'stack-arg)
	 (call-stack-instruction-emitter push-value-or-none-from-stack-arg
	   byte-code-stream var-spot))
	(t
	 (let ((first-index (second var-spot)))
	   (cond ((and (fixnump first-index)
		       (<f first-index 256))
		  (call-stack-instruction-emitter push-value-or-none-from-local-var
		    byte-code-stream var-spot))
		 (t
		  (emit-instruction-byte-code
		    byte-code-stream
		    'push-value-or-none-from-surrounding-local-var)
		  (emit-long-code-constant-to-stream
		    byte-code-stream first-index)
		  (emit-typecode-to-stream byte-code-stream var-spot)))))))


(def-stack-error not-a-function (non-function top-of-stack)
  "Attempted to call ~NF as a function, but it is an instance of the class ~(~a~)."
  non-function
  (class non-function))

(defun complete-call-from-rule-antecedent (completion-form)
  (declare (ignore completion-form))
  nil)

;;; Added by SoftServe

;;; Instruction 143, the `CALL-PROCEDURE stack instruction' is used to call
;;; procedure form the rule antecedent.
;;; This instruction performs context switch to the procedure byte code body,
;;; and original antecedent will be resumed after the procedure exit.

  ;note that the stack in our case is as follows:
  ;//////////////
  ;arg N
  ;arg N-1
  ;...
  ;arg 1
  ;procedure-definition
  ;/////////////
(def-stack-instruction (call-procedure 143 2 nil nil nil)
  (setq register-1 (svref local-stack top-of-stack))	; procedure
  (setq fixnum-register-1 (code-constant 0)) ;arguments count

  (when (rule-instance-p current-computation-instance)
    (setf (in-lhs-call? current-computation-instance) t))
  (multiple-value-setq (register-4 register-5)
      (switch-context-for-procedure-call register-1 fixnum-register-1 1 local-stack
                                         (-f top-of-stack 1) (+f stack-program-counter 1) t))
  (setq fixnum-time-limit? register-5)

  (modify-major-stack-eval-locals t)
  (modify-minor-stack-eval-locals))

;;; Instruction 94, the `CALL-FUNCTION stack instruction' is used to call user
;;; defined, tabular, and foreign functions.  See the documentation above
;;; describing how to dispatch to user defined functions.

(def-stack-instruction (call-function 94 2 nil print-call-function-stack-instruction
			pprint-call-function-instruction)
  (setq register-1 (svref local-stack top-of-stack))	; function
  (setq fixnum-register-1 (code-constant 0))	; arg-count
  (incff stack-program-counter)
  ;; For now, we aren't going to change the stack frame format, so we
  ;; put the number of arguments back in the right place.
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(svref local-stack (1-f top-of-stack)))
  (setf (svref local-stack (1-f top-of-stack))
	fixnum-register-1)
  (setq register-3 (class-description-slot register-1))
  (class-description-class-case register-3
    (function-definition
      (incff recursion-depth)
      (setq register-4
	    (begin-call-to-function-definition
	      local-stack top-of-stack register-1 recursion-depth stack-frame-base
	      stack-program-counter byte-code-body constant-vector))
      (when register-4
	(raw-stack-error-named-error top-of-stack register-4))
      (incff-top-of-stack-with-caching number-of-extra-stack-frame-values)
      ;; Install the new stack frame.
      (if-emitting-c-code
	(progn
	  (decache-stack)
	  (set-top-of-stack))
	  nil)
      (setq stack-frame-base (+f top-of-stack 1))
      (setq cached-stack-frame-base stack-frame-base)
      (setq stack-program-counter 0)
      (setq byte-code-body (function-definition-byte-code-body register-1))
      (setq cached-byte-code-body byte-code-body)
      (setq constant-vector (byte-code-body-constant-vector byte-code-body))
      (setq *current-computation-frame* register-1)
      (setq current-computation-component-particulars nil)
      ;; patch profiling info
      (when profiling-enabled?
	(posit-profiling-structure register-1)
	(increment-profiling-calls
	  register-1))
      (if-emitting-c-code
	(set-values-popped-before-resuming
	  (+f fixnum-register-1 (+f number-of-extra-stack-frame-values 3)))
	nil)
      (modify-minor-stack-eval-locals nil t))
    (foreign-function-declaration
      (setq fixnum-register-2
	    (-f (-f top-of-stack 3) fixnum-register-1))	; arg1 index
      (multiple-value-setq (register-2 register-3)
	(coerce-arguments-and-call-foreign-function
	  register-1
	  local-stack
	  fixnum-register-2
	  fixnum-register-1
	  top-of-stack))
      (when register-3
	(raw-stack-error-named-error top-of-stack register-3))
      ;; Skip reclaiming the function and arg count.
      (decff top-of-stack 1)
      (loop while (>f fixnum-register-1 -2) ;; All the arguments,
	                                    ;; unknown-p, and no-item-p
	    do
	(decff fixnum-register-1)
	(decff top-of-stack)
	(setq register-3 (svref local-stack top-of-stack))
	(reclaim-if-evaluation-value register-3))
      (setf (svref local-stack top-of-stack) register-2))
    (tabular-function
      (setq fixnum-register-2
	    (-f (-f top-of-stack 3) fixnum-register-1))	; arg1 index
      (setq register-3
	    (call-tabular-function
	      register-1 local-stack top-of-stack fixnum-register-2 fixnum-register-1))
      (when register-3
	(raw-stack-error-named-error top-of-stack register-3))
      (decff top-of-stack (+f fixnum-register-1 3)))
    (t
      (not-a-function register-1 top-of-stack))))

;;; `ensure-function-ok-or-return-stack-error-string' is used by the functions (no pun
;;; intended) which are called from the call-function stack-instruction to make
;;; sure the function-definition/tabular-function/foreign-function is OK before
;;; actually calling it.  Note the second argument is not evaluated as it is a
;;; target to use return-from with.  The third argument is optional and also not
;;; evaluated. It is a form to wrap around the error-text, such as
;;; (values nil <error-text>).

(defmacro ensure-function-ok-or-return-stack-error-string
    (func-var return-from-target &optional wrapper-for-error-text)
  (let* ((function (gensym))
	 (error-form `(tformat-stack-error-text-string
			"Can't call the function ~NF because its status is not OK."
			,function)))
    `(let ((,function ,func-var))
       (when (not (frame-ok-p ,function))
	 (return-from ,return-from-target
	   ,(if wrapper-for-error-text
		`(,@wrapper-for-error-text ,error-form)
		error-form))))))
	       

;;; The function `coerce-arguments-and-call-foreign-function' coerces all
;;; arguments on the stack to (and datum (not truth-value)) and then calls the
;;; foreign function.  If any of the arguments are unknown or no item, this
;;; function then signals an error or returns no-item or unknown as necessary
;;; without calling the foreign function.  Note that call-function is an
;;; expiration special form, and so is responsible for managing the
;;; stack-expiration variable when unknown is allowed.

(defun coerce-arguments-and-call-foreign-function
       (foreign-function-declaration local-stack stack-location argument-count
	top-of-stack)
  (ensure-function-ok-or-return-stack-error-string
    foreign-function-declaration
    coerce-arguments-and-call-foreign-function
    (values nil))
  (let* ((unknown-allowed?
	   (as-true-as
	     (evaluation-truth-value-value
	       (svref local-stack (-f top-of-stack 3)))
	     (truth-threshold inference-engine-parameters)))
	 (no-item-allowed?
	   (as-true-as
	     (evaluation-truth-value-value
	       (svref local-stack (-f top-of-stack 2)))
	     (truth-threshold inference-engine-parameters)))
	 (first-argument-index stack-location)
	 (last-argument-index+1 (+f stack-location argument-count))
	 (old-stack-expiration stack-expiration)
	 (no-item-seen? nil))
    (when unknown-allowed?
      (setq stack-expiration 'never))
    (loop for index from first-argument-index below last-argument-index+1
	  for argument = (svref local-stack index)
	  do
      (cond
	((evaluation-datum-p argument)
	 nil)
	(unknown-allowed?
	 (cond ((thing-is-variable-or-parameter-p argument)
		(setq argument
		      (get-current-value-based-on-current-environment
			argument top-of-stack)))
	       ((and (null argument)
		     no-item-allowed?)
		(setq stack-expiration nil))
	       (t
		(signal-coerce-to-datum-error
		  argument 'variable-or-parameter top-of-stack))))
	((thing-is-parameter-p argument)
	 (setq argument
	       (get-current-value-based-on-current-environment argument top-of-stack)))
	((and (null argument) no-item-allowed?)
	 (setq no-item-seen? t))
	(t
	 (return-from coerce-arguments-and-call-foreign-function
	   (signal-coerce-to-datum-error-message argument 'parameter))))
      ;; Do nothing to datum arguments, except that we reject
      ;; truth-values.
      (when (evaluation-truth-value-p argument)
	(return-from coerce-arguments-and-call-foreign-function
	  (values
	    nil
	    (tformat-stack-error-text-string
	      "Argument number ~a to the foreign function ~NF was the ~
               value ~NE.  Foreign functions can only accept arguments ~
               of the types quantity, symbol, and text."
	      (1+f (-f index first-argument-index))
	      foreign-function-declaration
	      argument))))
      (setf (svref local-stack index) argument))
    (cond (no-item-seen?
	   nil)
	  ((and unknown-allowed? (null stack-expiration))
	   nil)
	  (t
	   (when unknown-allowed?
	     (setq stack-expiration
		   (minimum-expiration stack-expiration old-stack-expiration)))
	   (new-call-foreign-function
	     foreign-function-declaration
	     local-stack
	     stack-location
	     argument-count
	     top-of-stack)))))

(defun call-tabular-function
    (tabular-function local-stack top-of-stack first-argument-index arg-count)
  (when (/=f arg-count 1)
    (return-from call-tabular-function
      (tformat-stack-error-text-string
	"Calling ~NF with ~a arguments, it requires 1."
	tabular-function
	arg-count)))
  (ensure-function-ok-or-return-stack-error-string tabular-function
						   call-tabular-function)
  (let* ((unknown-truth-value (svref local-stack (-f top-of-stack 3)))
	 (no-item-allowed (svref local-stack (-f top-of-stack 2)))
	 (unknown-ok? (>=f (evaluation-truth-value-value unknown-truth-value)
			   (truth-threshold inference-engine-parameters)))
	 (argument (svref local-stack first-argument-index)))
    (multiple-value-bind (evaluation-value? error?)
	(coerce-tabular-function-argument-to-evaluation-value
	  argument unknown-ok? top-of-stack)
      (when error?
	(return-from call-tabular-function error?))
      (let* ((argument-value
	       (when evaluation-value?
		 (evaluation-value-value evaluation-value?)))
	     (value
	      ;; Added by SoftServe
	       (if (or (evaluation-sequence-p evaluation-value?)
	               (evaluation-structure-p evaluation-value?))
	           (return-from call-tabular-function
		 (stack-error
		   top-of-stack
		   "The tabular function ~NF, can not take the value ~NV."
		   tabular-function
		   evaluation-value?))
       	      ;; End of SoftServe changes
	       (when evaluation-value? 
		 (compute-value-of-tabular-function-if-any
		   tabular-function argument-value)))))
	(cond ((and (null value) unknown-ok?)
	       (setq stack-expiration
		     (minimum-expiration stack-expiration nil)))
	      ((null value)
	       (return-from call-tabular-function
               ;; Added by SoftServe
		 (stack-error
		   top-of-stack
		   "The tabular function ~NF, given the value ~NV, did not return a value."
		   tabular-function
		   evaluation-value?)))
	      ;; End of SoftServe changes	      
	      ((fixnump value)
	       (setq value (make-evaluation-integer value)))
	      ((gensym-long-p value)
	       (setq value (make-evaluation-long value)))
	      ((evaluation-long-p value)
	       (setq value (copy-evaluation-long value)))
	      ((gensym-float-p value)
	       (setq value (make-evaluation-float value)))
	      ((managed-float-p value)
	       (setq value (copy-managed-float-into-evaluation-float value)))
	      ((symbolp value)
	       (setq value
		     (cond ((eq value 'true)
			    (make-evaluation-truth-value truth))
			   ((eq value 'false)
			    (make-evaluation-truth-value falsity))
			   (t
			    (make-evaluation-symbol value)))))
	      ((text-string-p value)
	       (setq value (make-evaluation-text value)))
	      (t
	       (return-from call-tabular-function
		 (tformat-stack-error-text-string
		   "~A ~NF ~A, ~A.  ~A ~A.  ~A"
		   "The tabular function"
		   tabular-function
		   "returned a datum which is not a number"
		   "symbol, truth value, or text"
		   "This is an internal G2 error caused by"
		   "some unusual use of tabular functions"
		   "Please report this bug to Gensym software support."))))
	;; Reclaim the unknown flag.
	(reclaim-evaluation-truth-value unknown-truth-value)
	;; Reclaim the no-item-allowed flag.
	(reclaim-evaluation-truth-value no-item-allowed)
	;; Reclaim the argument.
	(when evaluation-value?
	  (reclaim-evaluation-value evaluation-value?))
	;; Slam the value back into the stack.
	(setf (svref local-stack first-argument-index) value)
	;; return success
	nil))))

;; Note that the (values <foo> NIL) clauses have been added to get around a
;; problem with gensym-return-one with multiple-values: when not returning
;; enough values, sometimes a multiple-value-bind will stick garbage in the
;; extra args where it should be sticking NIL's instead, so we explicitly return
;; the NIL as the second value.  This is really being caused by the DEFUN-SIMPLE
;; of get-current-evaluation-value.  See bug HQ-4276413 -dkuznick, 5/6/02
(defun coerce-tabular-function-argument-to-evaluation-value
    (argument unknown-ok? top-of-stack)
  (cond ((evaluation-datum-p argument)
	 (values argument nil))
	((framep argument)
	 (frame-class-case argument
	   ((parameter)
	    (values (get-current-value-based-on-current-environment argument
								    top-of-stack)
		    nil))
	   ((variable)
	    (if unknown-ok?
		(values (get-current-value-based-on-current-environment argument
									top-of-stack)
			nil)
		(values
		  nil
		  (signal-coerce-to-datum-error-message
		    argument 'parameter))))
	   (t
	     (values
	       nil
	       (signal-coerce-to-datum-error-message
		 argument
		 (if unknown-ok?
		     'variable-or-parameter
		     'parameter))))))
	(t
	 (values
	   nil
	   (tformat-stack-error-text-string
	     "Unknown thing ~a given as argument to tabular function."
	     argument)))))

(defparameter recursion-warning-explanation-1 
  "There may be an infinite recursion involving this function")

(defparameter recursion-warning-explanation-2 
  "or the recursion limit attribute of the inference-engine-parameters system table should be increased for this knowledge base.")

(defun begin-call-to-function-definition
    (local-stack top-of-stack function-definition recursion-depth
     stack-frame-base stack-program-counter byte-code-body
     constant-vector)
  (declare (type fixnum top-of-stack recursion-depth stack-frame-base stack-program-counter))
  (when (>f recursion-depth (recursion-limit inference-engine-parameters))
    (return-from begin-call-to-function-definition
      (tformat-stack-error-text-string
	"The recursion limit ~a has been exceeded while attempting to call ~NF.  ~a, ~a"
	(recursion-limit inference-engine-parameters)
	function-definition
	recursion-warning-explanation-1 
	recursion-warning-explanation-2)))
  (when (>f top-of-stack (-f global-stack-size maximum-stack-frame-size))
    (return-from begin-call-to-function-definition
      (tformat-stack-error-text-string
	"The stack has overflowed while attempting to call the function ~NF.  ~
         There are currently ~a function calls on the stack.  ~a."
	function-definition
	recursion-depth
	recursion-warning-explanation-1)))
  ;; The following test shouldn't be necessary.  However, two things make it so:
  ;; inspect and may-refer-to-inactive-items.  Function-definitions are unique
  ;; in that one of the ways (in fact usually the only way!) they are "referred" to
  ;; is in a context where they are executed immediately.  Now most compilations
  ;; emit a PUSH-CACHED-ITEM instruction prior to a CALL-FUNCTION instruction
  ;; and it's PUSH-CACHED-ITEM's job to ensure that only an active item is put
  ;; on the stack.  However, PUSH-CACHED-ITEM uses SERVE-ITEM-P to see if an
  ;; item is OK.  SERVE-ITEM-P returns T when run during an inspect or when
  ;; may-refer-to-active-items is true of the "caller", so a BAD
  ;; function-definition will get put on the stack, and havoc ensues when it's
  ;; actually called.  This fix will prevent a BAD function-definition from being
  ;; run.  Bug HQ-4349833 "inspect filter with BAD function aborts g2"
  ;; -dkuznick, 7/31/02
  (ensure-function-ok-or-return-stack-error-string
    function-definition
    begin-call-to-function-definition)
  (let ((argument-count (evaluation-integer-value
			  (svref local-stack (-f top-of-stack 1))))
	(parameter-count
	  (length (second (car (box-translation-and-text function-definition)))))
	(new-base (+f top-of-stack (+f number-of-extra-stack-frame-values 1))))
    (declare (type fixnum argument-count parameter-count new-base))
    (when (/=f argument-count parameter-count)
      (return-from begin-call-to-function-definition
	(tformat-stack-error-text-string
	  "The function ~NF received ~a arguments, but it requires ~a."
	  function-definition argument-count parameter-count)))
    ;; Leave the old stack frames tracing and breakpoints context.
    (exit-tracing-and-breakpoint-context *current-computation-frame* nil)
    ;; Push the old stack frame.
    (setf (stack-frame-old-stack-frame-base local-stack new-base)
	  stack-frame-base)
    (setf (stack-frame-stack-program-counter local-stack new-base)
	  stack-program-counter)
    (setf (stack-frame-byte-code-body local-stack new-base) byte-code-body)
    (setf (stack-frame-constant-vector local-stack new-base) constant-vector)
    (setf (stack-frame-computation-frame local-stack new-base)
	  *current-computation-frame*)
    (setf (stack-frame-computation-component-particulars local-stack new-base)
	  current-computation-component-particulars)
    ;; Enter the new stack frame's tracing and breakpoints context.
    (enter-tracing-and-breakpoint-context
      function-definition
      (begin-function-definition-enter-tracing-context-message
	function-definition local-stack top-of-stack argument-count))
    nil))

(defun begin-function-definition-enter-tracing-context-message
       (function-definition local-stack top-of-stack argument-count)
  (twith-output-to-text-string
    (tformat "Calling function ~NF(" function-definition)
    (loop for argument-index from (-f top-of-stack 2 argument-count)
	  for current-argument from 0 below argument-count
	  do
      (unless (=f current-argument 0)
	(twrite-string ", "))
      (write-stored-value (svref local-stack argument-index)))
    (twrite-string ").")))




;;; Instruction 95, the `RETURN-FROM-FUNCTION stack instruction' is used to
;;; return values from user defined functions.  It takes one value off the stack
;;; and returns it.

(def-stack-instruction (return-from-function 95 1 1
			nil pprint-return-from-function-instruction)
  ;; Switch the tracing contexts back, reinstate the computation frame and
  ;; computation component particulars, reclaim the arguments and any values
  ;; left over on the stack, and return the argument count.
  (setq fixnum-register-1 (begin-return-from-function-definition
			    local-stack top-of-stack stack-frame-base))
  ;; Compute the target stack location for the function's value.
  (setq fixnum-register-1
	(stack-frame-first-argument-index stack-frame-base fixnum-register-1))
  (setq stack-program-counter
	(stack-frame-stack-program-counter local-stack stack-frame-base))
  (setq byte-code-body
	(stack-frame-byte-code-body local-stack stack-frame-base))
  (setq cached-byte-code-body byte-code-body)
  (setq constant-vector
	(stack-frame-constant-vector local-stack stack-frame-base))
  ;; There will be loss of profiling data here in all cases.  This
  ;; needs to be reviewed.
  (when profiling-enabled?
	(posit-profiling-structure
	  (stack-frame-computation-frame local-stack stack-frame-base)))
  (setf (svref local-stack fixnum-register-1)
	(svref local-stack top-of-stack))
  (if-emitting-c-code
    (decache-stack)
    nil)
  (setq stack-frame-base
	(stack-frame-old-stack-frame-base local-stack stack-frame-base))
  (setq cached-stack-frame-base stack-frame-base)
  (decff recursion-depth)
  (setq top-of-stack fixnum-register-1)
  (modify-minor-stack-eval-locals t t))

(defun begin-return-from-function-definition
    (local-stack top-of-stack stack-frame-base)
  (declare (type fixnum top-of-stack stack-frame-base))
  ;; Exit the called tracing context.
  (exit-tracing-and-breakpoint-context
    *current-computation-frame*
    (return-from-function-definition-exit-context-message
      local-stack top-of-stack)
    nil)
  ;; Fetch the calling frame and component particulars.
  (setq *current-computation-frame*
	(stack-frame-computation-frame local-stack stack-frame-base))
  (setf current-computation-component-particulars
	(stack-frame-computation-component-particulars
	  local-stack stack-frame-base))
  ;; Reclaim the arguments (up through the argument count) and any leftover
  ;; values on the stack, leaving the value to be returned on the top of the
  ;; stack.
  (loop for index fixnum from stack-frame-base below top-of-stack
	for value = (svref local-stack index)
	do
    (reclaim-if-evaluation-value value))
  ;; Reenter the calling tracing context.
  (enter-tracing-and-breakpoint-context *current-computation-frame* nil)
  (loop with argument-count-index fixnum =
	  (stack-frame-argument-count-index stack-frame-base)
	with argument-count fixnum =
	  (evaluation-integer-value (svref local-stack argument-count-index))
	with first-argument-index fixnum =
	  (stack-frame-first-argument-index stack-frame-base argument-count)
	for index fixnum from first-argument-index
		  below (+f first-argument-index argument-count)
	for value = (svref local-stack index)
	do
    (reclaim-if-evaluation-value value)
	finally
	  (return argument-count)))

(defun return-from-function-definition-exit-context-message
       (local-stack top-of-stack)
  (twith-output-to-text-string
    (twrite-string "Returning ")
    (if stack-expiration
	(write-stored-value (svref local-stack top-of-stack))
	(twrite-string "unknown"))
    (tformat " from function ~NF." *current-computation-frame*)))




;;; Instruction 96, the `NONE-TEST stack instruction' takes a value off the top
;;; of the stack, and push TRUE in its places if the value on the stack was NIL,
;;; or pushes FALSE on the stack if the value was not NIL.

(def-stack-instruction (none-test 96 1 1)
  (setq register-1 (arg 0))
  (cond (register-1
	 (reclaim-if-evaluation-value register-1)
	 (setq register-1 (make-evaluation-truth-value falsity)))
	(t
	 (setq register-1 (make-evaluation-truth-value truth))))
  (setf (arg 0) register-1))




;;; Instruction 97, the `SYSTEM-CALL stack instruction' calls a lisp function
;;; with the specified arguments and leaves any expected return values on the
;;; stack.  When this instruction is executed, the calling procedure does not
;;; enter a "wait" state.  The lisp function is funcalled directly and is not
;;; scheduled.  (Note, that is instruction was previously called lisp-call, but
;;; has been changed in case the user ever comes in contact with this
;;; instruction and the corresponding procedure-instruction.  cpm, 6/30/91)

;;; This instruction takes two one byte code constants from the instruction
;;; stream that specify the number of arguments to the lisp function and the
;;; number of expected return values.  The lisp function arguments are on the
;;; top of the stack and the lisp function name is below these.

;;; Note that the arguments to the Lisp function are evaluation-values.  If the
;;; incorrect number of arguments is passed to the lisp function, a Lisp error
;;; occurs.  The return values from the Lisp funcion must also be
;;; evaluation-values.

;;; The return values that are left on the stack are later popped into local
;;; variables by the instructions that follow this one.  If the type of any
;;; return values is not compatible with the corresponding local name, a level 1
;;; procedure error is signaled.

;;; Any extra arguments returned by the Lisp function are ignored.  Any missing
;;; return values produce a level 1 error.  The maximum number of arguments and
;;; return values are restricted by the constants
;;; maximum-number-of-lisp-call-arguments and
;;; maximum-number-of-lisp-call-return-values.

;;; This instruction can only be compiled in DEVELOPMENT, since they should only
;;; be used in system-procedures.  It can, of course, be executed in development
;;; and non-development.

;;; IMPORTANT NOTES:
;;; 1. ARGUMENTS AND RETURN VALUES:
;;;    The funcalled Lisp function must use the evaluation-value abstraction in
;;;    SETS to handle arguments and return values.
;;; 2. DECLARE-SYSTEM-PROCEDURE-FUNCTION:
;;;    When defining a system-procedure, use declare-system-procedure-function
;;;    which declares the specified Lisp as funcallable and indicates if the
;;;    function can make use of the following optimization.  This declaration
;;;    must be in the code before defining the system procedure in a KB!
;;; 3. OPTIMIZATION:
;;;    The system-procedure will get an efficiency improvement if it can
;;;    guarantee that the funcalled Lisp function never invalidates the
;;;    environment of the system-procedure or caller to the system-procedure.
;;;    In this case, the system-call instruction does not need to validate the
;;;    calling procedure environment.
;;;    The environment may be invalidated if the funcalled function can cause
;;;    the deletion or deactivation of an item.  This can happen through the
;;;    deletion, deactivation, or transfer of an item; by calling another
;;;    procedure, which may then invalidate the environment; or by allowing a
;;;    "wait state", which could then allow another procedure to execute.  See
;;;    the definition of the property for more information.
;;;    If the optimization applies to the Lisp function then indicate this in
;;;    DECLARE-SYSTEM-PROCEDURE-FUNCTION (pass a second argument of T).

;;;   SYSTEM-CALL (argument-count, return-values-count)

(def-stack-instruction (system-call 97 3 nil print-call-stack-instruction
				    pprint-system-procedure-instruction)
  (setq fixnum-register-1 (code-constant 0))	       ;arg-count
  (setq fixnum-register-2 (code-constant 1))	       ;return value count
  (execute-lisp-call-stack-instruction
    local-stack top-of-stack fixnum-register-1 fixnum-register-2)
  (decff top-of-stack
	 (+f fixnum-register-1 1))
  (incff-top-of-stack-with-caching
    fixnum-register-2)
  (cond ((and current-computation-instance
	      (or system-is-running
		  (runs-while-inactive-p *current-computation-frame*)))
	 (incff stack-program-counter 2))
	(t
	 ;; This case occurs in system calls where KBs are going to be reset, etc.
	 (inner-context-switch-to-next-computation-instance :unknown :none))))



;;; The function `execute-lisp-call-stack-instruction' is the main function for
;;; the lisp-call and lisp-call-assignment stack instructions.

;;; It is passed the local stack, top of stack, lisp function argument count,
;;; and a expected lisp function return value count.  It takes its arguments and
;;; lisp function name off the stack and calls that function.  Any return
;;; evaluation values are pushed onto the stack.  The new top-of-stack is
;;; returned.

;;; The Lisp function is passed evaluation-value or item arguments.  These
;;; evaluation values should be reclaimed by the called Lisp function if
;;; necessary.  The return values from the Lisp function, like the arguments,
;;; must be evaluation-values, that are reclaimable by the recipient, or items.
;;; The Lisp function can delete an item argument passed to it, but that deleted
;;; item should not then be a return value.

;;; Note that when modifying the maximum number of arguments to and return
;;; values from the lisp function, the constants
;;; maximum-number-of-lisp-call-return-values and
;;; maximum-number-of-lisp-call-arguments should also be modified.

;; Modified to validate the calling environment after the Lisp call.  This is
;; necessary since the Lisp function can delete items.  For example, file i/o
;; operations can delete stream items.  This is impemented by setting the
;; current frame serial number before the Lisp call and validating the caller's
;; environment after the Lisp call.  This is similar to what happens in other
;; cases, such as the delete action.  - cpm, 2/14/92

;; Now only validating the calling procedure environment if the Lisp function
;; can invalidate the environment.  This change is to make system-procedures
;; more efficient.  - cpm, 8/3/93

(defvar trace-system-calls-p nil)

(defun twrite-item-or-evaluation-value (argument)
  (if (framep argument)
      (tformat " ~NF" argument)
      (tformat " ~NV" argument)))

(defun-void trace-enter-system-call (function-name arguments)
  (let ((message
	  (twith-output-to-text-string
	    (tformat "calling ~(~a~):" function-name)
	    (loop for argument in arguments
		  do (twrite-item-or-evaluation-value argument)))))
    (notify-user-at-console message)
    (reclaim-text-string message)))

(defun-void trace-exit-system-call
    (argument-count return-value1? return-value2? return-value3? return-value4?
		    return-value5? return-value6? return-value7? return-value8?)
  (let ((message
	  (twith-output-to-text-string
	    (tformat "returning:")
	    (when (<f 0 argument-count)
	      (twrite-item-or-evaluation-value return-value1?))
	    (when (<f 1 argument-count)
	      (twrite-item-or-evaluation-value return-value2?))
	    (when (<f 2 argument-count)
	      (twrite-item-or-evaluation-value return-value3?))
	    (when (<f 3 argument-count)
	      (twrite-item-or-evaluation-value return-value4?))
	    (when (<f 4 argument-count)
	      (twrite-item-or-evaluation-value return-value5?))
	    (when (<f 5 argument-count)
	      (twrite-item-or-evaluation-value return-value6?))
	    (when (<f 6 argument-count)
	      (twrite-item-or-evaluation-value return-value7?))
	    (when (<f 7 argument-count)
	      (twrite-item-or-evaluation-value return-value8?)))))
    (notify-user-at-console message)
    (reclaim-text-string message)))

(defun execute-lisp-call-stack-instruction
       (local-stack top-of-stack argument-count expected-return-value-count)
  (let* ((first-stack-value-index (-f top-of-stack argument-count))
	 (lisp-function-name (svref local-stack first-stack-value-index))
	 (valid-environment?
	   (function-keeps-procedure-environment-valid? lisp-function-name))
	 (argument-list
	   (loop for stack-index from (+f first-stack-value-index 1)
				 to top-of-stack
		 for stack-value = (svref local-stack stack-index)
		 collect stack-value using stack-cons)))
    #+development
    (write-major-trace-message
      (setq forgive-long-procedure-instruction? t)
      (twrite-string "Calling Lisp function ")
      (twrite lisp-function-name)
      (twrite-string "."))

    (when (null valid-environment?)
      ;; Update the frame serial number before making the call.  This is needed
      ;; later to validate the caller's environment.
      (cond ((code-body-invocation-p current-computation-instance)
	     (update-code-body-invocation-frame-serial-number
	       current-computation-instance))
	    ((rule-instance-p current-computation-instance)
	     (frame-serial-number-setf (ri-frame-serial-number current-computation-instance)
		   (current-frame-serial-number)))))

    ;; Cache the top of stack so that it can be used in the system-calls (i.e.,
    ;; funcalled lisp-functions) when signaling a stack error.  Subtract the
    ;; number of arguments to the lisp function before caching this value.  The
    ;; lisp function owns its arguments and should reclaim them when necessary,
    ;; even before signaling a stack-error.
    (setq cached-top-of-stack (-f top-of-stack argument-count))

    (when (or (>f argument-count 10)
	      (not (fboundp lisp-function-name)))
      (loop for arg in argument-list do
	(reclaim-if-evaluation-value arg))
      (reclaim-stack-list argument-list)
      (if (>f argument-count 10)
	  (stack-error
	    cached-top-of-stack
	    "The number of arguments to the System Procedure ~a is ~
             beyond the maximum allowed.  Please report this error to ~
             Gensym Software Support."
	    lisp-function-name)
	  (stack-error
	    cached-top-of-stack
	    "Attempting to make a system call to ~A, which is not defined.  ~
             Please report this G2 internal error to Gensym software support."
	    lisp-function-name)))

    (when trace-system-calls-p
      (trace-enter-system-call lisp-function-name argument-list))

    ;; Keep the number of arguments consistent with
    ;; maximum-number-of-lisp-call-arguments.
    (gensym-dstruct-bind ((arg1? arg2? arg3? arg4? arg5? arg6? arg7? arg8?
				arg9? arg10?)
			 argument-list)
      (reclaim-stack-list argument-list)
      (multiple-value-bind
	;; The constant maximum-number-of-lisp-call-return-values should be kept
	;; up to date with the following dispatch types.  Any extra values are
	;; ignored!  A warning is given in development if extra-return-value?
	;; gets bound.
	(return-value1? return-value2? return-value3? return-value4?
			return-value5? return-value6? return-value7? return-value8?
			#+development extra-return-value?)
	  (case argument-count
	    (0 (funcall-symbol lisp-function-name))
	    (1 (funcall-symbol lisp-function-name arg1?))
	    (2 (funcall-symbol lisp-function-name arg1? arg2?))
	    (3 (funcall-symbol lisp-function-name arg1? arg2? arg3?))
	    (4 (funcall-symbol lisp-function-name arg1? arg2? arg3? arg4?))
	    (5 (funcall-symbol lisp-function-name arg1? arg2? arg3? arg4?
			       arg5?))
	    (6 (funcall-symbol lisp-function-name arg1? arg2? arg3? arg4?
			       arg5? arg6?))
	    (7 (funcall-symbol lisp-function-name arg1? arg2? arg3? arg4?
			       arg5? arg6? arg7?))
	    (8 (funcall-symbol lisp-function-name arg1? arg2? arg3? arg4?
			       arg5? arg6? arg7? arg8?))
	    (9 (funcall-symbol lisp-function-name arg1? arg2? arg3? arg4?
			       arg5? arg6? arg7? arg8? arg9?))
	    (10 (funcall-symbol lisp-function-name arg1? arg2? arg3? arg4?
				arg5? arg6? arg7? arg8? arg9? arg10?)))
	#+development
	(when extra-return-value?
	  (cerror "Continue, ignoring extra return values!"
		  "Too many return values from in a System-Call instruction."))

	(when trace-system-calls-p
	  (trace-exit-system-call
	    expected-return-value-count
	    return-value1? return-value2? return-value3? return-value4?
	    return-value5? return-value6? return-value7? return-value8?)
	  (when (fixnump trace-system-calls-p)
	    (decff trace-system-calls-p)
	    (when (=f 0 trace-system-calls-p)
	      (notify-user-at-console "System call tracing limit reached.")
	      (setq trace-system-calls-p nil))))

	;; Reclaim the following here in case any other errors are signaled.
	(reclaim-evaluation-symbol lisp-function-name)

	(when (null valid-environment?)
	  ;; Validate the caller's environment.  The Lisp call may have deleted
	  ;; or deactivated some items.
	  (validate-computation-instance-environment
	    current-computation-instance
	    nil nil))

	;; Push the expected number of return values onto the stack.  In
	;; development, reclaim and warn of extra return values.  In
	;; non-development, ignore (i.e., reclaim) extra return values.
	(loop with return-values =
		(stack-list return-value1? return-value2? return-value3?
			    return-value4? return-value5? return-value6?
			    return-value7? return-value8?)
	      for return-value-cons on return-values
	      for return-value? = (car-of-cons return-value-cons)
	      for return-value-count from 1
	      for return-value-expected? = 
		  (<=f return-value-count expected-return-value-count)
	      with reversed-return-value-list? = nil
	      while (or return-value? return-value-expected?)
	      do
	  (cond ((null return-value?)
		 (stack-error
		   cached-top-of-stack
		   "Missing return value ~a in System Procedure.  Please ~
                    call Gensym Software Support!"
		   (-f (length return-values) (length return-value-cons) -1))
		 (reclaim-stack-list-macro return-values))
		((null return-value-expected?)
		 ;; Warn in development of extra (reclaimable) return values.
		 ;; This could be the source of corruption, if a data-structure
		 ;; in the sys-proc still refers to it.
					; Add the following #+development guard
					; to test for extra return values.  I'm
					; delaying this for now because are we
					; too close to the final release.
					; - cpm, 6/13/95
;		 #+development
;		 (when (evaluation-value-p return-value?)
;		   (cerror
;		     "Continue, ignoring and RECLAIMING extra sys-proc return ~
;                      value."
;		     "Receiving return value number ~a from the ~
;                      system-~%~a, but it is only defined to return ~a values.~
;                      ~%Review and correct the return values or definition of ~
;                      this system-procedure."
;		     (-f (length return-values) (length return-value-cons) -1)
;		     lisp-function-name
;		     expected-return-value-count))

		 ;; Reclaim, but don't warn (in non-development), of extra
		 ;; return-value.
		 (reclaim-if-evaluation-value return-value?))
		(t
		 (setq reversed-return-value-list? 
		       (stack-cons return-value? reversed-return-value-list?))))
	      finally
		;; Push the values on the stack in reverse order.
		(loop for return-value-stack-index from first-stack-value-index
		      for return-value? in reversed-return-value-list?
		      do
		  ;; Don't need to reclaim the previous values on the stack.
		  ;; The lisp function name was already reclaimed and the lisp
		  ;; function arguments should be managed by the called lisp
		  ;; function.
		 (setf (svref local-stack return-value-stack-index)
		       return-value?))
		(reclaim-stack-list return-values)
		(reclaim-stack-list reversed-return-value-list?)
		;; Return the new top-of-stack.
		(return
		  (+f first-stack-value-index -1
		      expected-return-value-count)))))))





;;; Instruction 98, the `CREATE-CONNECTION stack instruction' executes the
;;; create-connection action.  This action is a separate instruction and is not
;;; implemented as a funcalled instruction since it may need to access the
;;; vertices argument from the constant-vector.  If the value is a constant, it
;;; can not be put on the stack since it is a lisp form (i.e., a list of
;;; numbers).

;;; This instruction takes 14 arguments from the stack.  These are a class; 5
;;; values for the first end specifier; 5 values for the second end specifer;
;;; and 3 connection details.  The end specifier values consist of a
;;; designation, make-new-stub flag, side, position, and portname.  All of these
;;; values may be nil, except for the designation for the first end specifier.
;;; The connection details value consists of a style, direction, and vertices.
;;; Each of these connection details may be nil.  The vertices value may be nil,
;;; an index into a list of numbers in the constant vector, or a g2-list item.
;;; Note that a separate instruction is emitted when the result of the action
;;; should be popped into a local variable.  Therefore, this create-connection
;;; instruction does not take a var-spot argument.  It does leave the new
;;; connection on the stack.

;; Was procedure-instruction 63.

;;;   CREATE-CONNECTION ()

(def-stack-instruction (create-connection 98 1 14
			nil pprint-create-connection-instruction)
  (execute-create-connection-stack-instruction
    local-stack top-of-stack constant-vector)
  (decff top-of-stack 13))

(defparameter valid-styles '(diagonal orthogonal))

(defparameter valid-directions '(input output))

(defparameter valid-sides '(left top right bottom))

(defun execute-create-connection-stack-instruction
       (local-stack top-of-stack constant-vector)
  (let* ((class (evaluation-symbol-symbol
		  (svref local-stack (-f top-of-stack 13))))
	 (class-description? (class-description class))
	 (end-1-item (svref local-stack (-f top-of-stack 12)))
	 (make-new-stub-1? (evaluation-symbol-symbol
			     (svref local-stack (-f top-of-stack 11))))
	 (side-1? (evaluation-symbol-symbol
		    (svref local-stack (-f top-of-stack 10))))
	 (position-1? (evaluation-value-value
			(svref local-stack (-f top-of-stack 9))))
	 (portname-1? (evaluation-symbol-symbol
			(svref local-stack (-f top-of-stack 8))))
	 (end-2-item? (if (evaluation-symbol-p
			    (svref local-stack (-f top-of-stack 7)))
			  (evaluation-symbol-symbol
			    (svref local-stack (-f top-of-stack 7)))
			  (svref local-stack (-f top-of-stack 7))))
	 (make-new-stub-2? (evaluation-symbol-symbol
			     (svref local-stack (-f top-of-stack 6))))
	 (side-2? (evaluation-symbol-symbol
		    (svref local-stack (-f top-of-stack 5))))
	 (position-2? (evaluation-value-value 
			(svref local-stack (-f top-of-stack 4))))
	 (portname-2? (evaluation-symbol-symbol
			(svref local-stack (-f top-of-stack 3))))
	 (style? (evaluation-symbol-symbol
		   (svref local-stack (-f top-of-stack 2))))
	 (direction? (evaluation-symbol-symbol
		       (svref local-stack (-f top-of-stack 1))))
	 (vertices-list-or-constant-index? (svref local-stack top-of-stack))
	 new-transient-connection?)
      
    ;; Update the cached frame serial number so that we can validate the
    ;; environment below after the connection is actually created.  This has to
    ;; be done since creating a new connection may actually delete a previous
    ;; connection at the same port.
    (cond ((code-body-invocation-p current-computation-instance)
	   (update-code-body-invocation-frame-serial-number
	     current-computation-instance))
	  ((rule-instance-p current-computation-instance)
	   (frame-serial-number-setf (ri-frame-serial-number current-computation-instance)
		 (current-frame-serial-number))))
    
    (setf new-transient-connection?
	  (execute-create-connection-stack-instruction-internal
	    class class-description?
	    end-1-item make-new-stub-1? side-1? position-1? portname-1?
	    end-2-item? make-new-stub-2? side-2? position-2? portname-2?
	    style? direction? 
	    (cond
	      ((evaluation-symbol-p vertices-list-or-constant-index?)
	       (setq vertices-list-or-constant-index? 
		     (evaluation-symbol-symbol vertices-list-or-constant-index?)))
	      ((evaluation-integer-p vertices-list-or-constant-index?)
	       (svref constant-vector
		      (evaluation-integer-value
			vertices-list-or-constant-index?)))
	      (t
	       vertices-list-or-constant-index?))
	    top-of-stack))
    
    (reclaim-evaluation-symbol
      (svref local-stack (-f top-of-stack 13)))      ;class
    ;; end-1-item stack arg 1 is not reclaimed since it can not be nil.
    (reclaim-if-evaluation-symbol
      (svref local-stack (-f top-of-stack 11)))      ;make-new-stub-1?
    (reclaim-if-evaluation-symbol
      (svref local-stack (-f top-of-stack 10)))      ;side-1?
    
    (reclaim-if-evaluation-value
      (svref local-stack (-f top-of-stack 9)))       ;position-1?
    (reclaim-if-evaluation-symbol
      (svref local-stack (-f top-of-stack 8)))       ;portname-1?
    
    (reclaim-if-evaluation-value
      (svref local-stack (-f top-of-stack 7)))       ;end-2-item?
    (reclaim-if-evaluation-symbol
      (svref local-stack (-f top-of-stack 6)))       ;make-new-stub-2?
    (reclaim-if-evaluation-symbol
      (svref local-stack (-f top-of-stack 5)))       ;side-2?
    (reclaim-if-evaluation-value
      (svref local-stack (-f top-of-stack 4)))       ;position-2?
    (reclaim-if-evaluation-symbol
      (svref local-stack (-f top-of-stack 3)))       ;portname-2?
    
    (reclaim-if-evaluation-symbol
      (svref local-stack (-f top-of-stack 2)))       ;style?
    (reclaim-if-evaluation-symbol
      (svref local-stack (-f top-of-stack 1)))       ;direction?
    (reclaim-if-evaluation-value
      (svref local-stack top-of-stack))	       ;vertices-list-or-constant-index?
    
    ;; Validate all environments to make sure there are no bindings to any
    ;; deleted connections.
    (validate-computation-instance-environment current-computation-instance
					       nil  nil)
    
    ;; Update the frame serial-number a second time.  This is needed so that
    ;; the number is up to date with the newly created frame.  (Note that the
    ;; first update of the serial-number was needed for the validation above,
    ;; in case any frames were deleted while the new connection was made.)
    (cond ((code-body-invocation-p current-computation-instance)
	   (update-code-body-invocation-frame-serial-number
	     current-computation-instance))
	  ((rule-instance-p current-computation-instance)
	   (frame-serial-number-setf (ri-frame-serial-number current-computation-instance)
		 (current-frame-serial-number))))
    
    ;; Push the new connection and return the new top of stack.
    (setq top-of-stack (-f top-of-stack 13))	       ;arg-count - 1
    (setf (svref local-stack top-of-stack) new-transient-connection?)
    top-of-stack))

(defvar disable-stack-error nil)
(defvar permit-transfer-of-permanent-items-p nil)

(defun execute-create-connection-stack-instruction-internal
    (class class-description?
	   end-1-item make-new-stub-1? side-1? position-1? portname-1?
	   end-2-item? make-new-stub-2? side-2? position-2? portname-2?
	   style? direction? vertices-list-or-constant-vertex-list?
	   top-of-stack)

  (macrolet ((create-connection-error (format &rest args)
	       `(if disable-stack-error
		    (return-from execute-create-connection-stack-instruction-internal
		      (tformat-text-string ,format ,@args))
		    (stack-error top-of-stack ,format ,@args))))

  (let 	(delta-list?)
    
    (when position-1? (setq position-1? (round position-1?)))
    (when position-2? (setq position-2? (round position-2?)))
    
    (when (null class-description?)
      (create-connection-error "~a is not a defined class." class))
    (when (and (not called-within-clear-text-loading)
	       (get-class-feature-in-class-description-if-any
		 class-description? 'not-user-instantiable))
      (create-connection-error
	"In a CREATE statement, attempted to make an instance of ~a, ~
         but you cannot instantiate a class which is not a final ~
         menu choice."
	class))
    (when (not (subclassp class 'connection))
      (create-connection-error
	"When creating transient instances of the class ~a, you should not ~
         use the additional CONNECTED grammar."
	class))
    (when (and style? (not (memq style? valid-styles)))
      (create-connection-error
	"The connection style specifier ~
         in a CREATE action evaluated to ~s ~
         which is not one of the valid styles diagonal, or orthogonal."
	style?))
    (when (and direction? (not (memq direction? valid-directions)))
      (create-connection-error
	"The connection direction specifier in a CREATE action evaluated to ~s ~
         which is not one of the valid directions input, or output"
	direction?))
    (let ((error-string?
	    (or (check-for-illegal-side-error side-1? top-of-stack)
		(check-for-illegal-side-error side-2? top-of-stack)
		(check-for-illegal-position-error position-1? top-of-stack)
		(check-for-illegal-position-error position-2? top-of-stack))))
      (when error-string?
	(return-from execute-create-connection-stack-instruction-internal
	  error-string?)))
    
    (cond ((evaluation-sequence-p vertices-list-or-constant-vertex-list?)
	   (setq delta-list?
		 (loop for element being each evaluation-sequence-element
		       of vertices-list-or-constant-vertex-list?
		       collect element using eval-cons)))
	  ((consp vertices-list-or-constant-vertex-list?)
	   (when (numberp (car vertices-list-or-constant-vertex-list?))
	     (setq delta-list?
		   (copy-list-using-eval-conses
		     vertices-list-or-constant-vertex-list?))))
	  ((of-class-p vertices-list-or-constant-vertex-list? 'quantity-list)
	   (let ((delta-tail? nil))
	     (do-g2-list-elements (element vertices-list-or-constant-vertex-list? nil)
	       (cond
		 ((null delta-tail?)
		  (setq delta-list?
			(eval-list
			  (g2-round (evaluation-quantity-value element))))
		  (setq delta-tail? delta-list?))
		 (t
		  (setf (cdr delta-tail?)
			(eval-list
			  (g2-round (evaluation-quantity-value element))))
		  (setq delta-tail? (cdr delta-tail?))))))))
    
    ;; Direction? determines which is the input and
    ;; which is the output end object.
    (when (eq direction? 'input)
      (psetq end-1-item end-2-item?
	     end-2-item? end-1-item
	     make-new-stub-1? make-new-stub-2?
	     make-new-stub-2? make-new-stub-1?
	     side-1? side-2?
	     side-2? side-1?
	     position-1? position-2?
	     position-2? position-1?
	     portname-1? portname-2?
	     portname-2? portname-1?))
    
    (let* ((transient-connection-error? nil)
	   (new-transient-connection?
	     (make-transient-connection
	       class end-1-item make-new-stub-1?
	       side-1? position-1? portname-1?
	       end-2-item? make-new-stub-2?
	       side-2? position-2? portname-2?
	       direction? style? delta-list? t)))
      (cond
	((null new-transient-connection?)
	 (reclaim-eval-list delta-list?)
	 (stack-eval-handle-transient-connection-error?
	   transient-connection-error?
	   top-of-stack))
	(t
	 (invoke-rules-for-direct-connection-chaining
	   (connection-for-this-connection-frame new-transient-connection?) nil)
	 (invoke-rules-for-indirect-connection-chaining
	   (connection-for-this-connection-frame new-transient-connection?) nil)))
      new-transient-connection?))))


(defun check-for-no-manual-connections-error (end-item? top-of-stack)
  (when (and end-item? (no-manual-connections-p end-item?))
    (if disable-stack-error
	(tformat-text-string
	  "A CREATE action could not make a connection to the ~
       object ~NF because this object has no-manual-connections capability"
	  end-item?)
	(stack-error
	  top-of-stack
	  "A CREATE action could not make a connection to the ~
       object ~NF because this object has no-manual-connections capability"
	  end-item?))))

(defun check-for-illegal-side-error (side? top-of-stack)
  (when (and side? (not (memq side? valid-sides)))
    (if disable-stack-error
	(tformat-text-string
	  "A connection side specifier in a CREATE action evaluated to ~s ~
      which is not one of the valid sides left, right, top, or bottom"
	  side?)
	(stack-error
	  top-of-stack
	  "A connection side specifier in a CREATE action evaluated to ~s ~
      which is not one of the valid sides left, right, top, or bottom"
	  side?))))

(defun check-for-illegal-position-error (position? top-of-stack)
  (when (and position? (not (>=f position? 0)))
    (if disable-stack-error
	(tformat-text-string
	  "A connection end position specifier in a CREATE action evaluated to ~s ~
       which is not a non-negative integer."
	  position?)
	(stack-error
	  top-of-stack
	  "A connection end position specifier in a CREATE action evaluated to ~s ~
       which is not a non-negative integer."
	  position?))))


(defun stack-eval-handle-transient-connection-error? (error? top-of-stack)
  (when error?
    (gensym-dstruct-bind ((kind-of-error second third) error?)
      (reclaim-gensym-list error?)
      (let ((format-string
	      (case kind-of-error
		(not-same-workspace
		 "In a CREATE action, attempt to make a connection between ~NF and ~NF ~
                  was unsuccessful because the objects are not on the same workspace.")
		(not-on-workspace
		 "In a CREATE action, attempt to make a connection to ~NF was ~
                  unsuccessful because the object is not on a workspace.")
		(not-transient
		 "In a CREATE action, attempt to make a connection to ~NF was ~
                  unsuccessful because the connection to connect to is not transient.")
		(bad-designation
		 "In a CREATE action, attempt to make a connection to ~NF was ~
                  unsuccessful because the designated stub was not found."))))
	(if disable-stack-error
	    (tformat-text-string
	      format-string
	      second third)
	    (stack-error
	      top-of-stack
	      format-string
	      second third))))))

;; Get rid of handle-transient-connection-error?  when switching permanently to
;; stack evaluator!

;; Stack-eval-handle-transient-connection-error?  is here (rather than in
;; CONNECTIONS5) because it uses the macro stack-error.




;;; Instruction 99, the `HALT stack instruction' is used to implement the halt
;;; action.  This is not a funcalled-instruction because it needs to access the
;;; local-var-stack.

;; Was procedure-instruction 46.

;;; FUNCTIONALITY CHANGE: The rule action previously gave a level 3 warning when
;;; the debugging-parameters message-and-breakpoint-overrides was not set.  The
;;; procedure non-stack action did not display a message in this case.

;;;   HALT (text-message?)

(def-stack-instruction (halt 99 1 1 nil pprint-halt-instruction)
  (setq register-1 (arg 0))			       ;Text message or nil.
  (when (message-and-breakpoint-overrides debugging-parameters)
    (if-emitting-c-code
      (decache-local-var-vector)
      nil)
    (setq register-2
	  (capture-halt-information
	    'halt-instruction
	    (evaluation-value-value register-1)
	    cached-stack-program-counter top-of-stack local-stack local-var-vector
	    byte-code-body))
    (pause-during-debug
      register-2))
  (reclaim-if-evaluation-value register-1)
  (decff top-of-stack))


;;; The function `capture-halt-information' returns a newly-consed HALT-INFO
;;; structure, which contains interesting information about the halt, as well as
;;; a formatted message to optionally show the user.  We do all this outside of
;;; the halt in-line stack-instruction to keep that instruction small.

;; This function is based on code in STACK-KERN that writes trace messages.
;; This code should be abstracted.  cpm, 6/12/91

;; If there are more than 6 or so local variables, the full dialog-box for the
;; halt message may not be visible on the screen!!  Discuss this with mhd.  cpm,
;; 6/12/91

(defun capture-halt-information (halt-reason halt-message? current-program-counter
					     top-of-stack local-stack local-var-vector
					     byte-code-body)
  (let* ((procedure-invocation-to-print
	   ;; This is WRONG!  You can't assume you have a procedure-invocation
	   ;; here.  See Bug HQ-4576977 "breakpoint dialog for rule mentions
	   ;; procedure-invocation"  -dkuznick, 6/3/03
	   (procedure-invocation-of-code-body current-computation-instance))
	 ;; Likewise, only code-body-invocations (used for procedure-invocs and
	 ;; rpc's have a slot called code-body-of-invocation.  Wow, are these
	 ;; structures named poorly! 
	 (code-body (code-body-of-invocation current-computation-instance))
	 (procedure-and-arguments-as-text
	   ;; Nope, again you can't assume you have a procedure-invocation here.  At
	   ;; minimum it could be a rule-instance in current-computation-instance,
	   ;; though theoretically, it may be a formula-invocation or
	   ;; remote-procedure-call too.
	   (twith-output-to-text-string
	     (write-procedure-invocation-instance-from-slot
	       procedure-invocation-to-print nil)))
	 (stack?
	   (when (>=f top-of-stack 0)
	     (twith-output-to-text-string
	       (loop for index from 0 to top-of-stack
		     do
		 (tformat "  ~a = " index)
		 (write-stored-value (svref local-stack index))
		 (tformat "~%")))))
	 (env
	   (twith-output-to-text-string
	     (write-code-body-environment
	       (byte-code-body-environment-description byte-code-body)
	       local-var-vector)))
	 (line-index? nil)		; Source code line for unwrapped text.
	 (source-code?
	   ;; Maybe also disallow for proprietary items?
	   (multiple-value-bind (source-line? source-character-index?)
	       (if (code-body-invocation-p ; guard against rules
		     current-computation-instance)
		   (get-annotation-for-address-if-any
		     current-program-counter code-body)
		   nil)
	     (when source-line?
	       ;; Note the following is hard-coded for procedures currently.
	       (twith-output-to-text-string
		 (let ((procedure-text
			 (cdr		; cdr of (translation . text)
			   (procedure-definition
			     (procedure-of-invocation
			       procedure-invocation-to-print)))))
		   (multiple-value-bind (non-word-wrapped-text new-line-index
							       new-char-index)
		       (convert-to-non-word-wrapped-text
			 procedure-text
			 source-line?
			 source-character-index?)
		     
		     ;; If the position corresponds to the end of a line,
		     ;; ignoring white space, then use the line index for the
		     ;; next line down, as long as there is one, since we can't
		     ;; otherwise indicate we're at the end of the line -- see
		     ;; note below for additional details! (MHD 6/23/05)
		     (setq line-index?
			   (if (let* ((text-tail
					(find-text-tail-for-line
					  non-word-wrapped-text new-line-index))
				      (index-at-end
					(find-end-of-line-of-text
					  text-tail t))) ; OK if in lost spaces
				 (and (>=f new-char-index index-at-end)
				      (advance-text-tail text-tail 1)))
			       (1+f new-line-index)
			       new-line-index))
		     
		     (tformat-surrounding-source-code-at-halt
		       non-word-wrapped-text line-index?)
		     (reclaim-text non-word-wrapped-text)))))))
	 (message			; Entire message, as returned previously.
	   (twith-output-to-text-string
	     (tformat "In ~a" procedure-and-arguments-as-text)
	     (tformat " {about to execute instruction ~a}." current-program-counter)
	     (when source-code?
	       (tformat "~%~%At source code line #~d." line-index?)
	       (twrite-string source-code?))
	     (when halt-message?
	       (tformat "~%~%~a" halt-message?))
	     (tformat "~%~%Stack:~%")
	     (if stack?
		 (twrite-string stack?)
		 (tformat "  Empty stack~%"))
	     (tformat "~%Environment:~%~a" env)))
	 (hi (make-halt-info)))
    ;; Now bundle it up and send it off to our dear callers.
    (setf (halt-info-type hi) halt-reason
	  (halt-info-message hi) message
	  (halt-info-user-message? hi) (copy-if-text-string halt-message?)
	  (halt-info-procedure hi) procedure-and-arguments-as-text
	  (halt-info-instruction hi) current-program-counter
	  (halt-info-stack? hi) stack?
	  (halt-info-environment hi) env
	  (halt-info-line? hi) line-index?)
    hi))

;; Note: fix for HQ-4984323 "annotation-information is getting misinterpreted".
;; This is somewhat heuristic, but the model case where this wins is with a loop
;; do-end block, where the end position may be on the line of the last token
;; before the end.  When the stepper is executing the end test, we'd prefer to
;; indicate that the line we're on is the line with the end, not the line above
;; it with the last statement in the do-end block. Related Note: our parsing and
;; related tools sometimes mix up the position at the very end of a line as the
;; position at the beginning of the next line, and vice versa.  See, e.g., bug
;; HQ-5064967 "editor records token positions inconstently based on interaction
;; order".  Fortunately, this solution does not rely on either approach to do
;; what it wants to do.) (MHD 6/20/05)



(defun-void tformat-surrounding-source-code-at-halt (non-word-wrapped-text line-index)
  (loop with n-before = 1		; parameterize later!
	with n-after = 1
	with text-line
	with line-length
	with lost-space-at-end-of-line
	with 1st-line-no = (maxf 1 (-f line-index n-before))
	with text-tail?
	  = (find-text-tail-for-line non-word-wrapped-text 1st-line-no)
	for line-no from (maxf 1 (-f line-index n-before))
		    to (+f line-index n-after)
	while text-tail?
	do (tformat "~%[ ~a~d ~a~a] "
		    (if (<f line-no 10) " #" "#") ; pad a space for 1-9
		    line-no
		    (if (=f line-no line-index) "=>" "  ")
		    #.(string #\tab))	; real tab for perfect alignment of ]'s
	   (multiple-value-setq
	       (text-line line-length lost-space-at-end-of-line text-tail?)
	     (get-next-text-line text-tail?))
	   (twrite-portion-of-wide-string-unparsably-to-current-wide-string
	     text-line
	     (get-character-index-past-separator text-tail?)
	     nil)))



;;; Instruction 100, the `SHOW stack instruction' executes the show action.
;;; This action is a separate instruction and is not implemented as a funcalled
;;; instruction since it may need to access the show-details argument from the
;;; constant-vector.  If the value is a constant, it can not be put on the stack
;;; since it is a lisp form.

;;; This instruction takes 3 arguments from the stack.  These are an item, an
;;; window or nil, and nil or an index to show-deatils contained in the
;;; constant-vector.  In this stack instruction, the block, window?, and
;;; show-details are required, though the last two may be nil.  In the non-stack
;;; version of the action, the window was contained in the show-details
;;; argument.  The show-details?  argument is an internal-constant, not an
;;; evaluation-value.

;; Was procedure-instruction 42.

;;;   SHOW (item window? show-details?)

(def-stack-instruction (show 100 1 3 nil pprint-show-instruction)
  (execute-show-stack-instruction
    local-stack top-of-stack constant-vector)
  (decff top-of-stack 3))


(defun execute-show-stack-instruction (local-stack top-of-stack constant-vector)
  (let* ((item (svref local-stack (-f top-of-stack 2)))
	 (window-arg (svref local-stack (-f top-of-stack 1)))
	 (designated-window-g2-extension?
	   (if (evaluation-symbol-p window-arg)
	       ;; Nil argument.
	       (evaluation-symbol-symbol window-arg)
	       window-arg))
	 (show-details-arg? (svref local-stack top-of-stack))
	 (show-details
	   (if (evaluation-integer-p show-details-arg?)
	       (svref constant-vector
		      (evaluation-integer-value show-details-arg?))
	       ;; Nil argument.
	       nil))
	 (ok-to-show?
	   (cond ((kb-workspace-p item)
		  (frame-system-operation-is-allowed-p 'show-workspace item))
		 (t
		  (let ((workspace? (get-workspace-if-any item)))
		    (and workspace?
			 (frame-system-operation-is-allowed-p 'show-workspace workspace?)))))))
    (if ok-to-show?
	(show-or-hide item t show-details designated-window-g2-extension?)
	(stack-error
	  top-of-stack
	  "Cannot show ~NF.  The show action has been restricted for this item."
	  item))
    
    ;; Reclaim window argument if there is a designated window g2 extension.
    (unless designated-window-g2-extension?
      (reclaim-evaluation-symbol window-arg))
    ;; Reclaim show details argument - either a constant index or nil.
    (when (evaluation-integer-p show-details-arg?)
      (reclaim-evaluation-integer show-details-arg?))
    ;; Return the new top of stack.
    (setq top-of-stack (-f top-of-stack 3))	       ;arg-count
    top-of-stack))



 
;;; Instruction 101, the `INVOKE stack instruction' executes the invoke action.
;;; This action is a separate instruction and is not implemented as a funcalled
;;; instruction since it may need to access the query-restriction argument from
;;; the constant-vector.  If the value is a constant, it can not be put on the
;;; stack since it is a lisp form.

;;; If the focal-entity?  arg is non-NIL, invoke will behave the same as "focus"
;;; with the exception that invoke will invoke-rules only if the
;;; query-restriction applies to the relationship between the rule and the
;;; entity.  If the focal-entity?  arg is NIL then things are quite different.
;;; All rules satisfying the query-restriction will be invoked with null focal
;;; entities and null focal roles.

;;; This instruction takes 2 arguments from the stack.  These are an index to
;;; the query-restriction constant and a focal entity or nil.

;;; This is a special form action.  The query-restriction argument was not
;;; evaluated and is in the constant-vector as an internal-constant.

;; Was procedure-instruction 39.

;;;   INVOKE (query-restriction focal-entity?)

(def-stack-instruction (invoke 101 1 2 nil pprint-invoke-instruction)
  (execute-invoke-stack-instruction
    local-stack top-of-stack constant-vector)
  (decff top-of-stack 2))

;;; Instruction 142, is exactly like invoke, except it will cause the
;;; procedure-invocation to wait until the generated rule-instances
;;; finish.
;;;
;;; Note the next time we force a KB recompile invoke and invoke-with-wait
;;; should be combined into one instruction, both for consistency and to free
;;; up the extra instruction. -dkuznick, 6/13/05

;;; INVOKE-WITH-WAIT (query-restriction focal-entity?)

(def-stack-instruction (invoke-with-wait 142 1 2 nil pprint-invoke-with-wait-instruction)
  (execute-invoke-stack-instruction
    local-stack top-of-stack constant-vector t)
  (decff top-of-stack 2)
  ;; Now we do what would happen if the compiler emitted a pause/wait
  ;; instruction {after checking it's ok to actually wait).  But note that if
  ;; this is running from a rule, the following is not valid.  The grammar
  ;; prevents this from happening.  -dkuznick, 5/5/06
  (when (need-to-wait-after-attempting-rule-scheduling
	  current-computation-instance)
    (inner-context-switch-to-next-computation-instance :code-body-invocation)))

(defun execute-invoke-stack-instruction
       (local-stack top-of-stack constant-vector &optional wait-p)
  (let* ((query-restriction-index-arg
	   (svref local-stack (-f top-of-stack 1)))
	 (query-restriction
	   (svref constant-vector
		  (evaluation-integer-value query-restriction-index-arg)))
	 (focal-entity-arg (svref local-stack top-of-stack))
	 (focal-entity? focal-entity-arg)
	 ;; The following is a special. -dkuznick, 6/13/05
	 (current-ri-completion-notification-collection?
	   (when wait-p
	     ;; Set up back-pointer.  current-computation-instance is usually
	     ;; a procedure-invocation, but can be a vanila
	     ;; code-body-invocation in the case of an invoke inside a "do in
	     ;; parallel". -dkuznick, 8/15/05
	     (set-up-completion-notification-collection
	       current-computation-instance))))
    (if focal-entity?
	(progn
	  (loop for class in (class-inheritance-path 
			       (class-description-slot focal-entity?))
		doing
	    (loop for rule-of-this-role-name in
		      (rules-of-this-class-or-object-name class)
		  doing
	      ;; Currently, it is assumed that all query restrictions are
	      ;; restrictions of the form (category ...)!
	      (when (loop with categories-of-rule-of-this-role-name
			    = (rule-categories rule-of-this-role-name)
			  for category in (cdr query-restriction)
			  thereis
			    (memq category
				  categories-of-rule-of-this-role-name))
		;; The condition of this when clause tests whether the
		;; intersection of the rule categories of rule-of-this-role-
		;; name and the categories of the query restriction is
		;; non-nil.
		(schedule-rule-instances-if-rule-is-not-embedded
		  rule-of-this-role-name
		  class nil focal-entity? 'invoking)))
		until (eq class 'item))
	  
	  (let ((name-of-object (name-or-names-for-frame focal-entity?)))
	    (cond
	      ((and name-of-object (symbolp name-of-object))
	       (loop for rule-of-this-object-name
			 in (rules-of-this-class-or-object-name
			      name-of-object)
		     doing
		 (when (loop with categories-of-rule-of-this-object-name
			       = (rule-categories rule-of-this-object-name)
			     for category in (cdr query-restriction)
			     thereis
			       (memq category
				     categories-of-rule-of-this-object-name))
		   (schedule-rule-instances-if-rule-is-not-embedded
		     rule-of-this-object-name nil nil nil 'invoking))))
	      ((consp name-of-object)
	       (loop for name in name-of-object do
		 (loop for rule-of-this-object-name
			   in (rules-of-this-class-or-object-name name)
		       doing
		   (when (loop with categories-of-rule-of-this-object-name
				 = (rule-categories rule-of-this-object-name)
			       for category in (cdr query-restriction)
			       thereis
				 (memq category
				       categories-of-rule-of-this-object-name))
		     (schedule-rule-instances-if-rule-is-not-embedded
		       rule-of-this-object-name
		       nil nil nil 'invoking))))))))
	
	;; else - no focal entity given
	(loop for category in (cdr query-restriction)
	      doing	  
	  (loop for rule-of-this-category in (rules-of-this-category category)
		doing
	    (schedule-rule-instances-if-rule-is-not-embedded
	      rule-of-this-category nil nil nil 'invoking))))
    
    ;; For the purposes of waiting, need to see if any rule-instances actually
    ;; got scheduled. If not, we need to make sure we don't wait.  The
    ;; invoke-with-wait stack-instruction will check to see if it's ok to wait.
    (when wait-p
      (remove-completion-notification-collection-if-empty
	current-computation-instance))

    ;; Reclaim stack arguments and return the new top of stack.
    (reclaim-evaluation-integer query-restriction-index-arg)
    (unless focal-entity?
      (reclaim-evaluation-symbol focal-entity-arg))
    (setq top-of-stack (-f top-of-stack 2))	       ;arg-count
    top-of-stack))


;;; The following function will invoke the rule only if it is not embedded
;;; within action-buttons and user-menu-choices.  Other ways of embedding rules
;;; should be represented here as well, I assume.  -jra 1/30/91

(defun schedule-rule-instances-if-rule-is-not-embedded
       (rule focal-role? local-name? focal-object? purpose)
  (let ((parent-frame? (parent-frame rule)))
    (unless (and parent-frame?
		 (or (frame-of-class-p parent-frame? 'action-button)
		     (frame-of-class-p parent-frame? 'user-menu-choice)))
      (generate-and-schedule-rule-instances
	rule focal-role? local-name? focal-object? purpose nil nil nil))))



;;; Instruction 102, the `PUSH-VALUE-OR-NONE-FROM-LOCAL-VAR stack instruction'
;;; takes a one byte index into the local-var-vector, and pushes the value from
;;; that location onto the top of the stack.  If the value is an
;;; evaluation-value, it is copied before being pushed.  If there is no value in
;;; that local var, then it pushes NIL.

;;;   PUSH-VALUE-OR-NONE-FROM-LOCAL-VAR (index-into-local-var)

(def-stack-instruction (push-value-or-none-from-local-var 102 3 nil
			 print-op-and-local-var-and-typecode
			 pprint-push-from-local-var-instruction)
  (setq fixnum-register-1 (code-constant 0))
  (setq register-1 (svref local-var-vector fixnum-register-1))
  (setq fixnum-register-1 (code-constant 1))
  (copy-if-evaluation-value-given-typecode-err-on-nil
    register-1 fixnum-register-1 nil)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 2))

(def-stack-instruction-emitter push-value-or-none-from-local-var
			       (byte-code-stream var-spot)
  (emit-instruction-byte-code
    byte-code-stream 'push-value-or-none-from-local-var)
  (write-byte-code-to-stream byte-code-stream (second var-spot))
  (emit-typecode-to-stream byte-code-stream var-spot))




;;; Instruction 103, the `CHECK-STACK stack instruction' is used as a debugging
;;; tool.  This instruction checks that the stack is currently empty (i.e.
;;; top-of-stack = -1) else it signals an error.

(def-stack-error check-stack-error (top-of-stack)
  "Top-of-stack was not -1.")

(def-stack-instruction (check-stack 103 1)
  (unless (=f top-of-stack -1)
    (check-stack-error top-of-stack)))




;;; Instruction 104, the `PUSH-CURRENT-ENVIRONMENT stack instruction' pushes the
;;; current environment (i.e., inference, simulator, procedure) onto the top of
;;; the stack.

;;;   PUSH-CURRENT-ENVIRONMENT ()

(def-stack-instruction (push-current-environment 104 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(make-evaluation-symbol current-environment)))




;;; Instruction 105, the `POP-CURRENT-ENVIRONMENT stack instruction' pops a
;;; value off the top of the stack into the current environment.

;;;   POP-CURRENT-ENVIRONMENT ()

(def-stack-instruction (pop-current-environment 105 1 1)
  (setq register-1 (arg 0))
  (setq current-environment (evaluation-symbol-symbol register-1))
  (reclaim-evaluation-symbol register-1)
  (decff top-of-stack))




;;; The function `coerce-matching-element-type-or-unknown' is used by several
;;; instructions to type test and/or coerce a potential g2-list or g2-array
;;; element before adding it to the array or list.

;;; First, if the list or array cannot contain items, the function tries to
;;; fetch the value of the element argument when it is either a variable (and
;;; unknown is allowed) or is a parameter.  This value, if any, is then used in
;;; the tests and possible coercion.

;;; Then, if the element value matches the element-type of the array or list, it
;;; is returned. Otherwise, if it can be coerced, that coerced value is
;;; returned.

;;; Note that an error is signaled if the element does not match and cannot be
;;; coerced to the correct element type.

;;; Note that if the unknown-allowed argument is non-NIL, this function can
;;; reference the value of a variable element argument and can, therefore,
;;; return an unknown (NIL) value.

;;; Note that if a no-value (NIL) is being placed into an item or item-or-datum
;;; array or list this function can return NIL.

(defun signal-coerce-matching-element-type-error-1
    (g2-array-or-list bad-item-or-datum)
  (twith-output-to-error-text
    (twrite-string "The value ")
    (cond ((of-class-p bad-item-or-datum 'item)
	   (tformat " ~NF" bad-item-or-datum))
	  ((evaluation-value-p bad-item-or-datum)
	   (write-evaluation-value bad-item-or-datum))
	  ((null bad-item-or-datum)
	   (twrite-string "none"))
	  ((temporary-constant-p bad-item-or-datum)
	   (print-constant 
	     (cached-constant-value bad-item-or-datum)
	     (constant-type bad-item-or-datum)))
	  (t (twrite bad-item-or-datum)))
    (tformat " is not a valid element for the ~A ~NF."
	     (if (g2-array-p g2-array-or-list) "G2-array" "G2-list")
	     g2-array-or-list)))

(def-substitution-macro signal-coerce-matching-element-type-error
    (g2-array-or-list element-of-wrong-type top-of-stack)
  (raw-stack-error-named-error
    top-of-stack
    (signal-coerce-matching-element-type-error-1
      g2-array-or-list element-of-wrong-type)))

(defun coerce-matching-element-type-or-unknown
    (g2-array-or-list item-or-evaluation-value-element top-of-stack unknown-allowed?)
  (let* ((g2-array-p? (g2-array-p g2-array-or-list))
	 (element-type
	   (if g2-array-p?
	       (g2-array-element-type g2-array-or-list)
	       (list-type g2-array-or-list)))
	 (possible-item-element-p?
	   (g2-list-or-array-element-type-may-contain-item-p element-type))
	 (element? (copy-if-evaluation-value item-or-evaluation-value-element)))
    ;; If the element type is datum, coerce any variable or parameter.
    (when (and (null possible-item-element-p?)
	       (framep element?)
	       (or (and unknown-allowed? (variable-p element?))
		   (parameter-p element?)))
      (setq element? (get-current-value-based-on-current-environment element? top-of-stack)))
    (cond ((and (null element?)
		possible-item-element-p?)
	   ;; Placing a no-value into an item, or item-or-value array
	   nil)
	  ((and (null element?)
		unknown-allowed?
		item-or-evaluation-value-element)
	   ;; Unknown value.
	   nil)
	  ((and (evaluation-integer-p element?)
		(eq element-type 'float))
	   ;; Coerce integer to float for g2-array or g2-list.
	   (let ((new-result
		   (make-evaluation-float
		     (coerce-fixnum-to-gensym-float
		       (the fixnum
			    (evaluation-integer-value element?))))))
	     (reclaim-evaluation-integer element?)
	     new-result))
	  (t
	   (if (g2-list-or-array-element-ok-p element? element-type)
	       element?
	       (values
		 nil
		 (prog1 (signal-coerce-matching-element-type-error-1
			  g2-array-or-list element?)
		   (reclaim-if-evaluation-value element?))))))))



;;; Instruction 106, the `COERCE-MATCHING-ELEMENT-TYPE-OR-UNKNOWN stack
;;; instruction' takes two arguments off the stack, an item, which is a g2-array
;;; or g2-list, and a new element value.  For g2-arrays or g2-lists of datum
;;; element-type, the value is coerced to a datum.  If the value can not be
;;; coerced or is not already a datum an error is signaled.  In all cases, the
;;; datum or item element must match that of the g2-array or g2-list.  If
;;; necessary, an integer datum is coerced to float.  Otherwise, an error is
;;; signaled.

;;; The instruction leaves the item (g2-array or g2-list) argument on the stack.
;;; It replaces the new element value with the coerced, matching value, or nil
;;; if there is no current value.

;;;   COERCE-MATCHING-ELEMENT-TYPE-OR-UNKNOWN ()

(def-stack-instruction (coerce-matching-element-type-or-unknown 106 1 2
			nil
			pprint-coerce-matching-element-type-instruction)
  (multiple-value-setq (register-1 register-2)
    (coerce-matching-element-type-or-unknown
      (arg 0) (arg 1) top-of-stack t))
  (when register-2
    (raw-stack-error-named-error top-of-stack register-2))
  (reclaim-if-evaluation-value (arg 1))
  (setf (arg 1) register-1))





;;; Instruction 107, the `COERCE-MATCHING-ELEMENT-TYPE stack instruction'
;;; instruction' takes two arguments off the stack, an item, which is a g2-array
;;; or g2-list, and a new element value.

;;; For g2-arrays or g2-lists of datum element-type, the new element value is
;;; coerced to a datum.  If the value can not be coerced or is not already a
;;; datum an error is signaled.  In all cases, the datum or item element must
;;; match that of the g2-array or g2-list.  If necessary, an integer datum is
;;; coerced to float.  Otherwise, an error is signaled.

;;; The argument new element could be an evaluation value or any item, but this
;;; instruction signals an error when it is a non-parameter item.

;;; The instruction leaves the item argument on the stack.  It replaces the new
;;; element value with the coerced, matching value.

;;;   COERCE-MATCHING-ELEMENT-TYPE ()

(def-stack-instruction (coerce-matching-element-type 107 1 2 nil
			 pprint-coerce-matching-element-type-instruction)
  (setq register-1 (arg 0))			       ;g2-array or g2-list
  (setq register-2 (arg 1))			       ;new element
  (multiple-value-setq (register-1 register-2)
    (coerce-matching-element-type-or-unknown
      register-1 register-2 top-of-stack nil))
  (when register-2
    (raw-stack-error-named-error top-of-stack register-2))
  (reclaim-if-evaluation-value (arg 1))
  (setf (arg 1) register-1))



;;; The function `emit-coerce-matching-element-type-or-unknown-if-necessary' is
;;; used by instructions that reference g2-arrays and g2-lists when a possible
;;; element item-or-value may need to be coerced to match the element type.

;;; The coerce instruction is only emitted when the element type does not match
;;; the type of the system-defined g2-array or g2-list.

;;; Note that the item (g2-array or g2-list) and item-or-datum element must have
;;; already been emmitted (in that order) immediately before calling this
;;; function.

(defun emit-coerce-matching-element-type-or-unknown-if-necessary
    (byte-code-stream g2-array-or-list-stack-node element-stack-node
		      unknown-allowed?)
  ;; Optimize when possible by leaving out the element test and coercion.  This
  ;; is possible when there can be no subtype to the sequence type and the value
  ;; type is equal to this type.
  (unless (stack-node-matches-element-type-p
	    g2-array-or-list-stack-node element-stack-node)
    (if unknown-allowed?
	(emit-instruction-byte-code
	  byte-code-stream 'coerce-matching-element-type-or-unknown)
	(emit-instruction-byte-code
	  byte-code-stream 'coerce-matching-element-type))))



;;; The function `stack-node-matches-element-type-p' determines if an element
;;; stack-node is guaranteed to be of the correct element type for the given
;;; g2-array or g2-list.  This is possible when there can be no subtype to the
;;; list or array type and the value type is equal to this type.

;;; This function is useful when determining whether the element needs to be
;;; tested and coerced.

(defun stack-node-matches-element-type-p
    (g2-array-or-list-stack-node element-stack-node)
  (let* ((sequence-type
	   (type-specification-minus-type
	     (stack-node-value-type g2-array-or-list-stack-node)
	     '(unknown-datum)))
	 (sequence-class?
	   (and (class-type-specification-p sequence-type)
		(type-specification-class sequence-type)))
	 (contained-type?
	   (and sequence-class?
		(g2-list-or-array-class-element-type sequence-class? t)))
	 (value-type
	   (type-specification-minus-type
	     (stack-node-value-type element-stack-node) '(unknown-datum))))
    (and contained-type?
	 (case contained-type?
	   (integer (eq value-type 'integer))
	   (float (eq value-type 'float))
	   (truth-value (eq value-type 'truth-value))
	   (symbol (eq value-type 'symbol))
	   (text (eq value-type 'text))
	   (t nil)))))



;;; Instruction 108, the `COMPLETE-RULE-INSTANCE stack instruction' closes
;;; execution of the current rule instance execution and possibly switches
;;; context to the next.  This instruction takes one argument which controls
;;; whether the current invocation is closed or allowed to continue execution.

;;;   COMPLETE-RULE-INSTANCE ()

(def-stack-instruction (complete-rule-instance 108 2)
  (setq fixnum-register-1 (code-constant 0))
  (when (=f fixnum-register-1 1)
    (setf (ri-state current-computation-instance) :completed))
  (incff stack-program-counter)
  (inner-context-switch-to-next-computation-instance
    :rule-instance nil (=f fixnum-register-1 1)))  




;;; Instruction 109, the `POP-INTO-BLOCK-OF-LOCAL-VARS stack instruction' is
;;; used to cache several values off of the stack and into a contiguous block of
;;; local vars.  It takes one long code constant which is the index to the first
;;; local var in the block, and a single code constant byte which is the count
;;; of values to cache.

;;;   POP-INTO-BLOCK-OF-LOCAL-VARS
;;;     (high-local-var-byte, low-local-var-byte, count)

(def-stack-instruction (pop-into-block-of-local-vars 109 4 nil print-block-copy)
  (setq fixnum-register-1 (long-code-constant 0))	; Index of first local var
  (setq fixnum-register-2			; Index of last local var
	(-f (+f fixnum-register-1 (code-constant 2)) 1))
  (loop until (<f fixnum-register-2 fixnum-register-1) do
    (setq register-1 (svref local-var-vector fixnum-register-2))
    (reclaim-if-evaluation-value register-1)
    (setf (svref local-var-vector fixnum-register-2)
	  (svref local-stack top-of-stack))
    (decff top-of-stack)
    (decff fixnum-register-2))
  (incff stack-program-counter 3))

(def-stack-instruction-emitter pop-into-block-of-local-vars
			       (byte-code-stream first-var-spot count)
  (unless (valid-var-spot-p first-var-spot)
    (compiler-bug
      "pop-into-block-of-local-vars emitter"
      "An invalid variable location, ~a, was given."
      first-var-spot)
    (setq first-var-spot '(var-spot 0)))
  (multiple-value-bind (overflows remainder)
      (floorf-positive-2 count 255)
    (let ((first-index (second first-var-spot)))
      (loop repeat overflows do
	(emit-instruction-byte-code
	  byte-code-stream 'pop-into-block-of-local-vars)
	(emit-long-code-constant-to-stream byte-code-stream first-index)
	(write-byte-code-to-stream byte-code-stream 255)
	(incff first-index 255))
      (when (>f remainder 0)
	(emit-instruction-byte-code
	  byte-code-stream 'pop-into-block-of-local-vars)
	(emit-long-code-constant-to-stream byte-code-stream first-index)
	(write-byte-code-to-stream byte-code-stream remainder)))))




;;; Instruction 110, the `PUSH-FROM-BLOCK-OF-LOCAL-VARS stack instruction' is
;;; used to push a set of values from a contiguous block of local vars onto the
;;; stack.  Note that this instruction also clears the values which were in
;;; those local vars as part of the copying operation.  It takes one long code
;;; constant which is the index to the first local var in the block, and a
;;; single code constant byte which is the count of values to push.

;;; Note that this instruction DOES NOT check that any frames stored in the
;;; local vars are still there and have not been deleted!  In that sense this
;;; instruction is like push-value-or-none-from-surrounding-local-var.  You must
;;; still use push-from-surrounding-local-var to restore frames onto the stack.

;;;   PUSH-FROM-BLOCK-OF-LOCAL-VARS
;;;     (high-local-var-byte, low-local-var-byte, count)

(def-stack-instruction (push-from-block-of-local-vars 110 4 nil print-block-copy)
  (setq fixnum-register-1 (long-code-constant 0))	; Index of first local var
  (setq fixnum-register-2			; Index of last local var + 1
	(+f fixnum-register-1 (code-constant 2)))
  (loop until (>=f fixnum-register-1 fixnum-register-2) do
    (incff top-of-stack)
    (setf (svref local-stack top-of-stack)
	  (svref local-var-vector fixnum-register-1))
    (setf (svref local-var-vector fixnum-register-1) nil)
    (incff fixnum-register-1))
  (incff stack-program-counter 3))

(def-stack-instruction-emitter push-from-block-of-local-vars
			       (byte-code-stream first-var-spot count)
  (multiple-value-bind (overflows remainder)
      (floorf-positive-2 count 255)
    (let ((first-index (second first-var-spot)))
      (loop repeat overflows do
	(emit-instruction-byte-code
	  byte-code-stream 'push-from-block-of-local-vars)
	(emit-long-code-constant-to-stream byte-code-stream first-index)
	(write-byte-code-to-stream byte-code-stream 255)
	(incff first-index 255))
      (when (>f remainder 0)
	(emit-instruction-byte-code
	  byte-code-stream 'push-from-block-of-local-vars)
	(emit-long-code-constant-to-stream byte-code-stream first-index)
	(write-byte-code-to-stream byte-code-stream remainder)))))




;;; Instruction 111, the `BEGIN-RULE-ACTIONS stack instruction' is used to set
;;; the state of a rule instance when the rule begins to execute actions.  This
;;; affects the process of invoking new instances which would merge with this
;;; one.  After this instruction sets the state of the rule instance, any
;;; invokes which match the context of this invocation must launch a new
;;; invocation, instead of merging with this one, since the affects of the
;;; transactions carried out in this rule have already begun.

;;;   BEGIN-RULE-ACTIONS ()

(def-stack-instruction (begin-rule-actions 111 1)
  (setf (ri-state current-computation-instance) 1)
  (clear-pending-wake-ups))




;;; Instruction 112, the `ADD-TO-ACTION-CACHE stack instruction' is used to
;;; cache a block of variables into an action cache.  This instruction takes
;;; three long code constants.  The first is the local var index of the action
;;; cache, the second is the number of variable values to cache, and the third
;;; is the local var index of the first variable being cached.  Note that if the
;;; count is zero, an entry is still entered into the cache containing no
;;; elements, and the local var index of the first value to cache should be
;;; ignored.

;;;   ADD-TO-ACTION-CACHE
;;;     (cache-high-byte, cache-low-byte, count-high-byte, count-low-byte,
;;;      target-high-byte, target-low-byte)

(def-stack-instruction (add-to-action-cache 112 7 nil
			print-action-cache-and-indices)
  (setq register-1 (long-code-constant 0))
  (setq fixnum-register-1 (long-code-constant 1))
  (setq fixnum-register-2 (long-code-constant 2))
  (if-emitting-c-code
    (decache-local-var-vector)
    nil)
  (execute-add-to-action-cache
    local-var-vector register-1 fixnum-register-1 fixnum-register-2)
  (if-emitting-c-code
    (cache-local-var-vector)
    nil)
  (incff stack-program-counter 6))

(defun execute-add-to-action-cache
       (local-vars cache-index value-count target-index)
  (let ((action-cache (svref local-vars cache-index))
	(new-element
	  (eval-cons
	    value-count
	    (when (/=f value-count 0)
	      (let ((vector (allocate-environment-vector value-count t)))
		(loop for index from 0 below value-count
		      for target from target-index
		      do
		  (setf (svref vector index) (svref local-vars target))
		  (setf (svref local-vars target) nil))
		(loop for index from value-count
				below (length-of-simple-vector vector)
		      do
		  (setf (svref vector index) nil))
		vector)))))
    (cond ((null action-cache)
	   (setq action-cache (make-evaluation-action-cache
				(eval-list new-element)))
	   (setf (svref local-vars cache-index) action-cache))
	  (t
	   (setf (evaluation-action-cache-value action-cache)
		 (eval-cons new-element
			    (evaluation-action-cache-value action-cache)))))))

(def-stack-instruction-emitter add-to-action-cache
    (byte-code-stream action-cache-var-spot var-spot-block)
  (when (action-cache-and-var-spot-block-ok-p
	  action-cache-var-spot var-spot-block
	  "add to action cache byte code emitter")
    (emit-instruction-byte-code byte-code-stream 'add-to-action-cache)
    (emit-long-code-constant-to-stream
      byte-code-stream (second action-cache-var-spot))
    (emit-long-code-constant-to-stream byte-code-stream (length var-spot-block))
    (emit-long-code-constant-to-stream
      byte-code-stream
      (if var-spot-block
	  (second (car var-spot-block))
	  0))))

(defun action-cache-and-var-spot-block-ok-p
       (action-cache-var-spot var-spot-block location-string)
  (let* ((initial-spot (car var-spot-block))
	 (initial-index (second initial-spot)))
    (block action-cache-emitter
      (unless (=f (var-spot-index-nesting
		    (var-spot-index-of-var-spot
		      action-cache-var-spot))
		  0)
	(compiler-bug
	  location-string
	  "The action cache location ~a wasn't local."
	  action-cache-var-spot)
	(return-from action-cache-emitter nil))
      (when var-spot-block
	(when (not (fixnump initial-index))
	  (compiler-bug
	    location-string
	    "The initial spot ~a wasn't local."
	    initial-spot)
	  (return-from action-cache-emitter nil))
	(loop for expected-index from (+f initial-index 1)
	      for var-spot in (cdr var-spot-block)
	      for index = (second var-spot) do
	  (when (or (not (fixnump index))
		    (/=f index expected-index))
	    (compiler-bug
	      location-string
	      "An element of the variable block was out of order or not local.  ~
               Expected index was ~a, actual was ~a."
	      expected-index index)
	    (return-from action-cache-emitter nil))))
      t)))




;;; Instruction 113, the `RESTORE-FROM-ACTION-CACHE-OR-BRANCH stack instruction'
;;; is used to restore values cached into an action cache back into the local
;;; variables from which they came.  If the named action cache is empty, then a
;;; branch is executed to the given address.

;;; This instruction takes 4 long code constant arguments.  The first is the
;;; local var index of the action cache.  The second is the count of the number
;;; of values to decache into local variables.  The third is the local var index
;;; to the first variable to restore values into.  The fourth long code constant
;;; is the address to branch to if the action cache is empty.

;;; Note that it is valid to have decachings occur when the count of values to
;;; copy is zero.  In this case, the number of entries in the action cache
;;; controls how many times an action is executed, without controlling its
;;; arguments.  In this case the index of the first target local var should be
;;; ignored.

;;;   RESTORE-FROM-ACTION-CACHE-OR-BRANCH
;;;     (cache-high-byte, cache-low-byte, count-high-byte, count-low-byte,
;;;      target-high-byte, target-low-byte, empty-high-byte, empty-low-byte)

(def-stack-instruction (restore-from-action-cache-or-branch
			 113 9 nil print-action-cache-indices-and-address)
  (setq register-1 (long-code-constant 0))
  (setq fixnum-register-1 (long-code-constant 1))
  (setq fixnum-register-2 (long-code-constant 2))
  (if-emitting-c-code
    (decache-local-var-vector)
    nil)
  (setq register-2
	(restore-from-action-cache
	  local-var-vector register-1 fixnum-register-1 fixnum-register-2
	  top-of-stack))
  (if-emitting-c-code
    (cache-local-var-vector)
    nil)
  (if register-2
      (incff stack-program-counter 8)
      (setq stack-program-counter (long-code-constant 3))))




;;; The function `restore-from-action-cache' executes the body of a restore, and
;;; returns T if there was something to restore, or else NIL if the action cache
;;; was empty.

(defun restore-from-action-cache
       (local-vars cache-index value-count target-index top-of-stack)
  (let ((action-cache (svref local-vars cache-index)))
    (when action-cache
      (let ((cache-list (evaluation-action-cache-value action-cache)))
	(cond
	  (cache-list
	   (let* ((cache-to-restore (car-of-cons cache-list))
		  (rest-of-cache-list (cdr-of-cons cache-list))
		  (count (car-of-cons cache-to-restore))
		  (vector (cdr-of-cons cache-to-restore)))
	     (when (/=f count value-count)
	       (stack-error
		 top-of-stack
		 "An internal G2 error has occurred restoring action-cache ~
                  values.  Attempt to restore ~a elements from a ~a element
                  cache."
		 value-count count))
	     (when (/=f value-count 0)
	       (loop for index from 0 below value-count
		     for local-var-index from target-index
		     for old-value = (svref local-vars local-var-index)
		     do
		 (reclaim-if-evaluation-value old-value)
		 (setf (svref local-vars local-var-index)
		       (svref vector index)))
	       (reclaim-managed-simple-vector vector))
	     (reclaim-eval-cons-macro cache-to-restore)
	     (reclaim-eval-cons-macro cache-list)
	     (setq cache-list rest-of-cache-list)
	     (setf (evaluation-action-cache-value action-cache) cache-list)
	     (when (null cache-list)
	       (reclaim-evaluation-action-cache action-cache)
	       (setf (svref local-vars cache-index) nil))
	     t))
	  (t
	   (reclaim-evaluation-action-cache action-cache)
	   (setf (svref local-vars cache-index) nil)
	   nil))))))

(def-stack-instruction-emitter restore-from-action-cache-or-branch
    (byte-code-stream action-cache-var-spot var-spot-block empty-tag)
  (when (action-cache-and-var-spot-block-ok-p
	  action-cache-var-spot var-spot-block
	  "restore from action cache byte code emitter")
    (register-byte-code-tag-resolution-point byte-code-stream empty-tag)
    (emit-instruction-byte-code byte-code-stream 'restore-from-action-cache-or-branch)
    (emit-long-code-constant-to-stream
      byte-code-stream (second action-cache-var-spot))
    (emit-long-code-constant-to-stream byte-code-stream (length var-spot-block))
    (emit-long-code-constant-to-stream
      byte-code-stream
      (if var-spot-block
	  (second (car var-spot-block))
	  0))
    ;; Emit dummy address.
    (emit-long-code-constant-to-stream byte-code-stream 0)))

(def-byte-code-resolver restore-from-action-cache-or-branch
			(byte-code-stream byte-vector address tag)
  (declare (ignore byte-code-stream))
  (setf (long-code-constant-in-byte-vector byte-vector (+f address 7))
	(instruction-address-for-tag tag nil)))




;;; Instruction 114, the `COMPLETE-SIMULATION-VARIABLE-EVALUATION stack
;;; instruction' closes execution of the current simulation variable and
;;; possibly switches context to the next.  This instruction takes one argument
;;; which controls whether the current invocation is closed or allowed to
;;; continue execution; the argument indicates whether evaluation of the
;;; simulation formula was successful or not.

(def-stack-instruction (complete-simulation-variable-evaluation 114 1)
  (setq register-1 (svref local-stack top-of-stack))
  (setq register-2
	(>f (evaluation-truth-value-value register-1) local-truth-threshold))
  (if-emitting-c-code
    (decache-local-var-vector)
    nil)
  (exit-last-simulation-variable-context 
    register-2
    local-var-vector)
  (reclaim-evaluation-truth-value register-1)
  (decff top-of-stack)
  (cond
    ((or dont-backward-chain-in-sim-eval? dont-proceed-to-next-variable?)
     (setq current-computation-instance nil)
     (go exit-stack-eval))
    ((and (when (>=f number-of-simulated-variables-processed
		     number-of-variables-to-process-at-a-time)
	    (setq number-of-simulated-variables-processed 0)
	    t)
	  (time-slice-expired-p)
	  (not initializing-simulator?))	       ; don't suspend if initializing
     (setq ran-out-of-time? t)
     (setq current-computation-instance nil)
     (go exit-stack-eval))
    (t
     (enter-next-simulation-variable-context)
     (cond
       (current-computation-instance
	(setf fixnum-register-1 top-of-stack)
	(loop until (<f fixnum-register-1 0) do
	  (setq register-1 (svref local-stack fixnum-register-1))
	  (reclaim-if-evaluation-value register-1)
	  (decff fixnum-register-1))
	(setf top-of-stack -1)
	(setq byte-code-body (runtime-formula current-simulation-runtime-structure)
	      cached-byte-code-body byte-code-body
	      local-var-vector (runtime-cache? current-simulation-runtime-structure)
	      constant-vector (byte-code-body-constant-vector byte-code-body)
	      stack-program-counter 0)
	(modify-minor-stack-eval-locals t))
       (t
	(go exit-stack-eval))))))



;;; Instruction 115, the `PAUSE-KB stack instruction' is used to pause a KB from
;;; the action of a rule or procedure.  It reschedules the code-body-invocation
;;; after pausing the kb.

;;; The pause action can be anywhere in a procedure or an in-order rule.  It can
;;; only be given as the last action of a simultaneous rule.  After the kb is
;;; resumed, the procedure or in-order rule continues execution at the next
;;; statement or action.

;; The restriction on the location of the action in simultaneous rules needs to
;; be implemented!!  cpm, 7/23/91.

;; Since this is a new action in G2 version 3.0, there is no corresponding
;; procedure-instruction.

;;;   PAUSE-KB ()

(def-stack-instruction (pause-kb 115 1 nil nil pprint-pause-kb-instruction)
  (system-pause)
  ;; I'm not certain that this restriction on only resuming
  ;; code-body-invocations is appropriate, please review.  FIND ME, JRA -jra
  ;; 10/27/96
  (when (code-body-invocation-p current-computation-instance)
    (schedule-computation-instance-execution
      current-computation-instance priority-of-current-task
      (if (code-body-invocation-p current-computation-instance)
	  (procedure-of-invocation
	    (procedure-invocation-of-code-body current-computation-instance))
	  (ri-rule current-computation-instance))))
  (inner-context-switch-to-next-computation-instance :unknown :none))




;;; Instruction 116, the `RESET-KB stack instruction' is used to reset G2 from
;;; within a rule or procedure.  The reset action can be anywhere in a procedure
;;; or rule.

;; Since this is a new action in G2 version 3.0, there is no corresponding
;; procedure-instruction.

;;; RESET-KB ()

(def-stack-instruction (reset-kb 116 1 nil nil pprint-reset-kb-instruction)
  (system-reset)
  (unless (runs-while-reset-procedure-p)
    (inner-context-switch-to-next-computation-instance :none :none t)))

(defun-simple runs-while-reset-procedure-p ()
  (when (code-body-invocation-p current-computation-instance)
    (let ((invocation?
	    (procedure-invocation-of-code-body current-computation-instance)))
      (when invocation?
	(runs-while-inactive-p
	  (procedure-of-invocation invocation?))))))

;;; System Procedure Functions used by g2-reset in g2root.kb

;;; The system procedure function `g2-get-blocks-needing-status-refreshed'
;;; is called from within g2-reset in g2root.kb.
;;; This function returns a sequence of blocks which will need to be
;;; refreshed at the end of g2-reset.

(declare-system-procedure-function g2-get-blocks-needing-status-refreshed t)

(defun g2-get-blocks-needing-status-refreshed ()
  (let ((pre-sequence nil))
    (loop for block being each class-instance of 'block
	  when (and (frame-representations block)
		    (frame-status-and-notes-reflects-flags-of-frame-p block))
	       do (eval-push block
			     pre-sequence))
  (allocate-evaluation-sequence
    (nreverse pre-sequence))))

;;; The system procedure function `g2-get-top-level-transient-workspaces'
;;; is called from within g2-reset in g2root.kb.
;;; This function returns a sequence of transient kb-workspaces which will
;;; need to be deleted in g2-reset.

(declare-system-procedure-function g2-get-top-level-transient-workspaces t)

(defun g2-get-top-level-transient-workspaces ()
  (let ((pre-sequence nil))
    (loop for item being each class-instance of 'kb-workspace do
      (if (and (transient-p item)
	       (null (parent-of-subworkspace? item)))
	  (eval-push item pre-sequence)))
    (allocate-evaluation-sequence
      (nreverse pre-sequence))))

;;; The system procedure function
;;; `g2-get-top-level-transient-items-and-connections'
;;; is called from within g2-reset in g2root.kb.
;;; This function returns two sequences:
;;; i) A sequence of transient items which will need to be deleted in g2-reset
;;; ii) A sequence of transient connections which will need to be deleted in
;;; g2-reset.

(declare-system-procedure-function g2-get-top-level-transient-items-and-connections t)

(defun g2-get-top-level-transient-items-and-connections ()
  (let ((pre-item-sequence nil)
	(pre-connection-sequence nil))
    (loop for block being each class-instance of 'block
	  for superior? = (superior-frame block) do
      (when (frame-of-class-p block 'item)
	(if (and (transient-p block)
		 (or (null superior?)
		     (not (transient-p superior?)))
		 )
	    (eval-push block pre-item-sequence))
	(remove-transient-relation-instances block t))
      (when (not (eq (car pre-item-sequence) block))  
	;; When block isn't being deleted, check connections
	(loop for connection being each output-connection of block do
	  (when (and (transient-connection-p connection)
		     (symbolp (connection-frame-or-class connection)))
	    (eval-push connection pre-connection-sequence)))))
    (values
      (allocate-evaluation-sequence
	(nreverse pre-item-sequence))
      (allocate-evaluation-sequence
        (nreverse pre-connection-sequence)))))


;;; The system procedure function `g2-complete-reset-kb' is called from the
;;; procedure g2-reset in g2root.kb.
;;; This function completes reseting G2. This function guaruntees that
;;; all items be deactivated and that all transient items will
;;; be deleted by the time G2 is reset.  Ensuring these two things is
;;; costly but it may be the only way to ensure that all items have
;;; been deactivated and that there are no transient items remaining.
;;; G2 is not completely reset until this system procedure function has
;;; completed.

(declare-system-procedure-function g2-complete-reset-kb t)

(defun g2-complete-reset-kb
    (evaluation-sequence)
  ;; This should not clear g2-reset itself or any procedures which
  ;; can run while inactive.
  (clear-procedure-invocations)

  ;; Deleting any remaining transient items.  It is possible that the
  ;; user created transient items during method calls to g2-delete
  ;; or g2-deactivate
  (let ((items-to-delete nil)
	(delete-connections-without-leaving-stubs? t)
	(connections-to-delete nil))
    (loop for item being each class-instance of 'kb-workspace do
      (if (and (transient-p item)
	       (null (parent-of-subworkspace? item)))
	  (setq items-to-delete (gensym-cons item items-to-delete))))
    (with-module-related-frame-note-updates-supressed
      (loop with serial-number = (copy-frame-serial-number (current-frame-serial-number))
	    for item in items-to-delete
	    when (frame-has-not-been-reprocessed-p item serial-number)
	      do (delete-frame item)
	      finally (reclaim-frame-serial-number serial-number)))
    (reclaim-gensym-list items-to-delete)
    (setq items-to-delete nil)
    (loop for block being each class-instance of 'block
	  for superior? = (superior-frame block) do
      (when (frame-of-class-p block 'item)
	(if (and (transient-p block)
		 (or (null superior?)
		     (not (transient-p superior?))))
	    (setq items-to-delete (gensym-cons block items-to-delete)))
	(remove-transient-relation-instances block t))
      (when (not (eq (car items-to-delete) block))  
	;; When block isn't being deleted, check connections
	(loop for connection being each output-connection of block do
	  (when (and (transient-connection-p connection)
		     (symbolp (connection-frame-or-class connection)))
	    (setq connections-to-delete 
		  (gensym-cons connection connections-to-delete))))))
    
    ;; Deactivating g2-extensions. These may already have been deactivated
    ;; by the user but we have to be sure.
    (loop for g2-extension being each class-instance of 'g2-extension do
      (unless (and (superblock? g2-extension)
		   (null (frame-status g2-extension)))
	(funcall-method 'deactivate-and-propagate g2-extension nil)))

    ;; Deactivating top level workspaces. These may already have been
    ;; deactivated by the user but we have to be sure.
    (loop for block being class-instances of 'kb-workspace do
      (when (and (null (superblock? block))
		 (null (parent-of-subworkspace? block)))
	(funcall-method 'deactivate-and-propagate block nil)))
    
    (let ((message-board?
	    (get-instance-with-name-if-any 'message-board 'message-board)))
      (if message-board?
	  (funcall-method 'deactivate-and-propagate message-board? nil)))
    (clear-g2-schedule)
    (undo-kb-state-changes)
    (clear-inform-messages)
    (loop for server in list-of-all-data-servers
	  for shut-down-function? = (function-to-shut-down-data-server? server)
	  doing
      (if shut-down-function? (funcall-symbol shut-down-function?)))
    (cancel-data-server-accept-data-calls)
    (loop for block
	      being each evaluation-sequence-element of evaluation-sequence
	  do
      (update-representations-of-slot-value block 'frame-status-and-notes))
    (setf (clock-get gensym-time-at-start) (clock-get gensym-time))
					; do? just for hygiene.
					; (preset-gensym-time-for-initialization)
					; ; this isn't really appropriate!  But
					; it was performed here at least in 3.0
					; until Rev. 3.  (MHD 11/10/93)
    
    ;; A G2 authorized as development or restricted-use may be made runtime
    ;; only if runtime data saved from a runtime system was loaded into it.
    ;; If this is the case, it gets reverted upon reset.
    #+pre-g2-v5-licensing
    (restore-authorization-if-temporary)))


;;; Instruction 117, the `NUPEC-SYNCHRONIZE stack instruction' is used to
;;; execute a synchronization operation in the NUPEC specific enhancements to
;;; G2.  Note that this needs to subvert the stuff which checks for a procedure
;;; hogging the processor, since the system will be within this instruction for
;;; quite some time.  Also, if this instruction is executed in a non-NUPEC
;;; version of G2, then a procedure error should be given.

;; Was procedure-instruction 60.

;;; This is a special-form action since it takes a variable number of arguments.
;;; Arg-count is the first stack argument and is the count of additional stack
;;; arguments, not including the first (which is the arg-count).

;;;   NUPEC-SYNCHRONIZE (g2-to-g2-object {item} class-list arg-count)

(declare-forward-reference nupec-synchronize function) ; in G2DS

;;; Since this is currently broken, and I don't want to spend a lot of time
;;; on it, I've arbitrarily decided to assume that this will never take more
;;; than 255 arguments. Easy enough to fix if this turns out to be wrong
;;; -alatto, 8/14/98
(def-stack-instruction (nupec-synchronize 117 2 nil nil
					  pprint-nupec-synchronize-instruction)
  (incff stack-program-counter)
  (setf fixnum-register-1 (code-constant 0))
  (execute-nupec-synchronize-stack-instruction
    local-stack top-of-stack constant-vector fixnum-register-1)
  (decff top-of-stack fixnum-register-1))

(defun execute-nupec-synchronize-stack-instruction
       (local-stack top-of-stack constant-vector arg-count)
  (error-if-simulation-procedure "NUPEC-SYNCHRONIZE" top-of-stack)
  (unless (nupec-authorized-p)
    (stack-error
      top-of-stack
      "This knowledge base was written in a NUPEC enhanced ~
       version of G2, but this version of G2 is not enhanced ~
       for NUPEC.  The NUPEC SYNCHRONIZE instruction cannot ~
       be executed."))
  (let* ((class-list-stack-index top-of-stack)
	 (class-list-constant-index
	   (svref local-stack
		  (evaluation-integer-value class-list-stack-index)))
	 (class-list (svref constant-vector class-list-constant-index))
	 (stack-index (1+f (-f top-of-stack arg-count)))
	 (g2-to-g2-object (svref local-stack stack-index))
	 (items-to-synchronize nil))
    (unless (g2-to-g2-data-interface-p-function g2-to-g2-object)
      (stack-error
	top-of-stack
	"In the NUPEC synchronize action, ~NF is not an instance of a class ~
         containing the G2-to-G2-data-inferface capability."
	g2-to-g2-object))
    (unless (<=f arg-count 2)
      (incff stack-index)
      (loop while (< stack-index class-list-stack-index)
	    for item = (svref local-stack stack-index)
	    do
	(setq items-to-synchronize (eval-cons item items-to-synchronize))
	(incff stack-index)))
    (loop for class in class-list
	  do
      (cond ((subclassp class 'item)
	     (loop for item being each class-instance of class do
	       (when (serve-item-p item)
		 (setq items-to-synchronize
		       (eval-cons item items-to-synchronize)))))
	    (t
	     (reclaim-eval-list items-to-synchronize)
	     (stack-error
	       top-of-stack
	       "In the NUPEC synchronize action, ~a is not a defined class."
	       class))))
    (nupec-synchronize
      (variables-and-parameters-in-items items-to-synchronize)
      g2-to-g2-object)
    (setq forgive-long-procedure-instruction? t)

    (reclaim-eval-list items-to-synchronize)
    (reclaim-evaluation-integer class-list-stack-index)))

;;; The function `variables-and-parameters-in-items' returns an eval cons list
;;; derived from the list of items given it.  The returned list contains all
;;; variables and parameters within the object hierarchies of the items in the
;;; given list.  This means that the any variables or parameters in the list,
;;; any attributes of the items in the list which are variables or parameters,
;;; or any variables or parameters in further traversals of the subworkspaces of
;;; these items and attributes will be in the resulting list.

;; Used in NUPEC.

(defvar items-to-traverse nil)
;; This variable was declared special within variables-and-parameters-in-items
;; and add-to-items-to-traverse.  Added this defvar to prevent C translator from
;; having problems.  3/17/91, cpm

(defun-simple add-to-items-to-traverse (item)
  ; (declare (special items-to-traverse)) - removed 3/17/91, cpm
  (when (serve-item-p item)
    (setq items-to-traverse (eval-cons item items-to-traverse))))

(defun variables-and-parameters-in-items (item-list)
  (let ((items-to-traverse (copy-list-using-eval-conses item-list))
	(items-to-return nil))
    ;(declare (special items-to-traverse)) - removed 3/17/91, cpm
    (loop while items-to-traverse
	  for item-cons = items-to-traverse
	  for item = (car item-cons)
	  do
      (setq items-to-traverse (cdr item-cons))
      (reclaim-eval-cons-macro item-cons)
      (cond ((frame-of-class-p item 'entity)
	     (when (variable-or-parameter-p item)
	       (setq items-to-return (eval-cons item items-to-return)))
	     (funcall-simple-compiled-function-on-attributes
	       item #'add-to-items-to-traverse))
	    ((frame-of-class-p item 'kb-workspace)
	     (loop for subblock being each subblock of item
		   do
	       (when (and (frame-of-class-p subblock 'item)
			  (or (entity-p subblock)
			      (frame-of-class-p subblock 'message))
			  (serve-item-p subblock))
		 (setq items-to-traverse
		       (eval-cons subblock items-to-traverse))
		 (loop for connection being the
			   output-connections of subblock
		       as connection-frame-or-class
			  = (connection-frame-or-class connection)
		       do
		   (when (and (framep connection-frame-or-class)
			      (frame-of-class-p
				connection-frame-or-class 'item)
			      (serve-item-p connection-frame-or-class))
		     (setq items-to-traverse
			   (eval-cons connection-frame-or-class
				      items-to-traverse)))))))
	    ((frame-of-class-p item 'message)
	     (funcall-simple-compiled-function-on-attributes
	       item #'add-to-items-to-traverse))))
    items-to-return))



;;; Instruction 118, the `PUSH-FROM-DEFAULT-ALLOW-DATA-SEEKING stack
;;; instruction' is used to push an evaluation truth value reflecting the value
;;; of the default-dont-compute-new-variable-values special variable.  If by
;;; default new value computing is allowed, this function pushes true, otherwise
;;; it pushes false.

;;; The default applies to the item currently executing.  For example, a
;;; procedure within a Collect Data statement has a default of true, while
;;; procedure statements outside of the Collect Data have a default of false.
;;; The default for a rule varies at run-time depending on whether the rule can
;;; cause data-seeking.

;;;   PUSH-FROM-DEFAULT-ALLOW-DATA-SEEKING ()

(def-stack-instruction (push-from-default-allow-data-seeking 118 1)
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack)
	(if (default-dont-compute-new-variable-values)
	    (make-evaluation-truth-value falsity)
	    (make-evaluation-truth-value truth))))



;;; Instruction 119, the `POP-INTO-DEFAULT-ALLOW-DATA-SEEKING stack instruction'
;;; is used to change the value of default-dont-compute-new-variable-values.  If
;;; a true is on the stack, the variable should be set to nil, and false is on
;;; the stack, then the variable is set to true.

;;;   POP-INTO-DEFAULT-ALLOW-DATA-SEEKING ()

;;this optimized version takes advantages of the two sequential calls
(def-stack-instruction (pop-into-default-allow-data-seeking 119 1 1)
  (setq register-1 (arg 0))
  (if (>=f (evaluation-truth-value-value register-1) local-truth-threshold)
      (progn 
      (setf (default-dont-compute-new-variable-values) nil)
	   (setf (dont-compute-new-variable-values) nil))
	  (progn  
      (setf (default-dont-compute-new-variable-values) t)
	  (setf (dont-compute-new-variable-values) t)))
    
  (reclaim-evaluation-truth-value register-1)
  (decff top-of-stack))




;;; Instruction 120, the `ELEMENT-FRAME-OR-PLACE-REFERENCE stack instruction'
;;; receives an item or place-reference as its first stack argument, and an
;;; index indicating an element postion as its second stack argument, and
;;; returns on the stack one of the following values: an item if the item
;;; argument was present and if the element of the item held an item; an
;;; evaluation place reference if the item argument was supplied, but there was
;;; anything but an item in the element; or an evaluation place reference to the
;;; nth-element if the first argument was itself already a place reference.

;;; This instruction is used for the place argument of the conclude action, when
;;; the argument is a g2-array or g2-list element reference.  The place
;;; reference value is for the case where we are concluding a value into a
;;; datum-array or datum-list.  This works since conclude can not put a frame
;;; into a location, but change nth-element of a g2-array or g2-list can.

(def-stack-instruction (element-frame-or-place-reference 120 1 2
			nil pprint-nth-element-instruction)
  (setq register-1 (arg 1))			       ;index
  (setf (arg 0)
	(fetch-element-frame-or-place-reference
	  (arg 0) register-1 top-of-stack))
  (reclaim-evaluation-integer register-1)
  (decff top-of-stack))




;;; The function `fetch-element-frame-or-place-reference' takes an item, an
;;; index into the item, and the top of the stack, and returns an item if one is
;;; stored at the given index, or else it returns a place reference evaluation
;;; value to that location.  This function implements the logic for conclude
;;; into arrays, where conclude on an item array places the value into the
;;; stored item, and conclude into a datum array changes the element at the
;;; given index.

;;; Note that in cases where it is an item array and no element, an error is
;;; signalled here to that effect.

(defun-simple fetch-element-frame-or-place-reference
    (item-or-place-reference index top-of-stack)
  (let* ((place-reference?
	   (evaluation-place-reference-p item-or-place-reference))
	 (class-description? (and (not place-reference?)
				  (framep item-or-place-reference)))
	 (g2-array-p? (and (not place-reference?)
			   class-description?
			   (class-description-of-class-p
			     class-description? 'g2-array)))
	 (g2-list-p? (and (not place-reference?)
			   class-description?
			   (class-description-of-class-p
			     class-description? 'g2-list)))
	 (servable-item-element? nil))
    (unless (or g2-array-p? g2-list-p? place-reference?)
      (stack-error
	top-of-stack
	"Cannot modify the element at index ~a in ~NA.  This item is not ~
         a g2-list, g2-array, or sequence in an attribute of an item."
	index item-or-place-reference))
    (when (and g2-array-p? (not (g2-array-index-ok-p item-or-place-reference index)))
      (stack-error
	top-of-stack
	"An attempt was made to refer to element ~a of ~NF, but it is ~
         only ~a elements long."
	index item-or-place-reference (g2-array-length item-or-place-reference)))
    (when (and (not place-reference?)
	       (g2-list-or-array-element-type-may-contain-item-p
		 (list-type item-or-place-reference)))
      ;; If a g2-list is empty don't signal an error here.  Let the surrounding
      ;; expression, e.g., action, catch the error and give a better error
      ;; message.
      (let ((stored-item-or-value?
	      (if g2-array-p?
		  ;; This is the actual array element value or unboxed float.
		  (g2-array-aref item-or-place-reference index)
		  ;; This is the actual value from the list.
		  (nth-g2-list-item-or-evaluation-value
		    index item-or-place-reference nil))))
	(cond ((and stored-item-or-value?
		    (evaluation-value-p stored-item-or-value?))
	       ;; Datum value.  Will return the place reference.
	       nil)
	      ((and stored-item-or-value?
		    (serve-item-p stored-item-or-value?))
	       (setq servable-item-element?
		     stored-item-or-value?))
	      (t
	       ;; NIL (no value) or un-serveable value.
	       (role-returned-no-values-error
		 top-of-stack '(nth-element item-or-datum)
		 item-or-place-reference index)))))
    ;; Item or place-reference return value.
    (cond (servable-item-element?
	   servable-item-element?)
	  (place-reference?
	   (redirect-place-reference
	     item-or-place-reference
	     (make-element-component-particulars
	       index (evaluation-place-reference-component-particulars
		       item-or-place-reference)))
	   item-or-place-reference)
	  (t (make-evaluation-place-reference-to-place
	       (make-element-component-particulars
		 index '*current-computation-frame*)
	       item-or-place-reference)))))

(def-stack-instruction-emitter element-frame-or-place-reference
			       (byte-code-stream)
  ;; The index and g2-array or g2-list are the domains for the corresponding
  ;; role and will be on the stack.
  (emit-instruction-byte-code
    byte-code-stream 'element-frame-or-place-reference))




;;; Instruction 121, PUSH-VALUE-OR-NONE-FROM-STACK-FRAME-VAR, is defined above.

;;; Instruction 122, PUSH-VALUE-OR-NONE-FROM-STACK-ARG, is defined above.




;;; Instruction 123, the `NTH-ELEMENT stack instruction' is an optimized version
;;; of the role server for the nth-element of an array, list, sequence, or text.
;;; It takes two arguments off the stack, the item-or-value and the index, and
;;; leaves the item or evaluation value in that index on the stack.

(def-stack-instruction (nth-element 123 1 2 nil pprint-nth-element-instruction)
  (setq register-1 (arg 0))
  (setq register-2 (arg 1))
  (setf (arg 0)
	(fetch-nth-element register-1 register-2 top-of-stack t))
  (reclaim-if-evaluation-value register-1)
  (reclaim-evaluation-integer register-2)
  (decff top-of-stack))




;;; Instruction 124, the `TYPE-CHECK-CLASS-INLINE stack instruction' is an
;;; optimized version of type-check for some system-defined classes.  It takes
;;; one code constant argument, the index into the list of
;;; classes-type-checked-inline.  A fast dispatch is made into this function
;;; which further uses the class-description-of-class-p optimizations to speed
;;; its computation.

;;;   TYPE-CHECK-CLASS-INLINE (class-number)

(defun print-type-check-class-inline (pc instructions constants environment)
  (declare (ignore constants environment))
  (let ((class (nth (byte-vector-aref instructions (+f pc 1))
		    classes-type-checked-inline)))
    (tformat " ~(~a~)" class)))

(defun pprint-type-check-class-inline-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore constant-vector))
  (let* ((instruction-vector (byte-code-body-byte-vector byte-code-body))
	 (stack-program-counter (+f pc 1))
	 (inline-class-index (code-constant 0))
	 (class-name 'unknown-class))
    ;; Not calling pprint-type-check because the class constant is not a
    ;; type-spec format.
    (twrite-string "check that ")
    (write-stack-argument 1 1 stack top-of-stack)
    (loop for class in classes-type-checked-inline
	  for count from 0
	  do
      (when (=f count inline-class-index)
	(setq class-name class)))
    (tformat " is a ~a" class-name)))

(defmacro inline-class-test?
	  (class-number class-description top-of-stack success-form functionp)
  `(fixnum-case ,class-number
     ,@(loop for class in classes-type-checked-inline
	     for count from 0
	     collect
	     `(,count
	       (when (class-description-of-class-p
		       ,class-description
		       ',class)
		 ,success-form)))
     ,@(when functionp
	 `((t (stack-error
		,top-of-stack
		"An internal error has just occured in the type-check-class-inline ~
                 instruction.  The index ~a was out of range."
		,class-number))))))

(defmacro inline-type-check-class-macro (thing class-number top-of-stack &optional functionp)
  `(let* ((class-description? (framep ,thing))
	  (not-error-p (and class-description?
			    (inline-class-test?
			      ,class-number class-description? ,top-of-stack
			      t ,functionp))))
     (unless not-error-p
       (signal-stack-class-type-check-error
	 ,thing ,class-number ,top-of-stack))
     nil))

(defun inline-type-check-class (thing class-number top-of-stack)
  (inline-type-check-class-macro thing class-number top-of-stack t))

(def-stack-instruction (type-check-class-inline 124 2 1
			print-type-check-class-inline
			pprint-type-check-class-inline-instruction)
  (inline-type-check-class (arg 0) (code-constant 0) top-of-stack)
  (incff stack-program-counter))

(def-stack-instruction-emitter type-check-class-inline
			       (byte-code-stream class-name)
  (emit-instruction-byte-code byte-code-stream 'type-check-class-inline)
  (write-byte-code-to-stream
    byte-code-stream
    (position class-name classes-type-checked-inline)))




(defun signal-error-concluding-formula-result (problem-description)
  (twith-output-to-error-text
    (tformat "An error occured while concluding a formula result.  ~a"
	     problem-description)
    (reclaim-text-string problem-description)))

(defun complete-formula-function (computed-value? top-of-stack)
  (let ((variable (formula-invocation-variable current-computation-instance)))
    (cond
      ((and computed-value? stack-expiration)
       (clean-up-wake-ups-state-if-any)
       (let ((problem-description?
	      (put-current-evaluation-value
		variable computed-value? stack-expiration nil nil)))
	 (when problem-description?
	   (signal-error-concluding-formula-result problem-description?))))
      (t
       (let ((variable-had-interests-before-this-attempt?
	       (formula-invocation-postponed-clean-ups
		 current-computation-instance)))
	 (reclaim-if-evaluation-value computed-value?)
	 (let ((circular-path?
		 (and variable-had-interests-before-this-attempt?
		      (circular-variable-interests-p variable))))
	   (if circular-path?
	       (write-circular-path-warning variable circular-path?)
	       (set-wake-ups-function top-of-stack)))
	 (clean-up-wake-ups-state-if-any))
       nil))))

;;; Instruction 125, the `Complete-generic-formula stack instruction' takes the
;;; result of a formula evaluation on the stack and is used to context switch
;;; out of the currently executing formula and into the next scheduled
;;; computation.

(def-stack-instruction (complete-generic-formula 125 1 1 nil
			 pprint-complete-generic-formula-instruction)
  (setq register-1 (complete-formula-function (arg 0) top-of-stack))
  (when register-1
    (raw-stack-error-named-error top-of-stack register-1))
  (decff top-of-stack)
  (inner-context-switch-to-next-computation-instance :formula-invocation nil t))




;;; Instruction 126, the `Complete-cell-expression stack instruction' takes the
;;; result of a cell expression evaluation on the stack and is used to context
;;; switch out of the expression cell and into the next computation.

(def-stack-instruction (complete-cell-expression 126 1 1 nil
			 pprint-complete-cell-expression-instruction)
  (setq register-1 (arg 0))
  (cond ((formula-invocation-p current-computation-instance)
	 (setq register-2 (complete-formula-function register-1 top-of-stack))
	 (when register-2
	   (raw-stack-error-named-error top-of-stack register-2))
	 (decff top-of-stack)
	 (inner-context-switch-to-next-computation-instance
	   :formula-invocation nil t))
	(t
	 (reclaim-if-evaluation-value register-1)
	 (decff top-of-stack)
	 ;; (inner-context-switch-to-next-computation-instance) in my dreams
	 (go exit-stack-eval))))




;;; Instruction 127, the `Begin-activity stack instruction' takes one byte of
;;; code-constant.  The low 7 bits in this byte name the activity just being
;;; begun.  This is stored in current-computation-activity for printing if there
;;; is an error.  The uppermost bit is 1 if this switch of activity should never
;;; be profiled, and 0 if profiling should occur.

;;;   BEGIN-ACTIVITY (activity-number)

(defun print-begin-activity (pc instructions constants environment)
  (declare (ignore constants environment))
  (let* ((arg (byte-vector-aref instructions (+f pc 1)))
	 (suppress-profile? (>f arg 127)))
    (twrite-character #.%space)
    (write-activity-given-index nil nil (logandf arg 127))
    (when suppress-profile?
      (twrite-string " without profiling"))
    (tformat " (~a)" arg)))


(def-stack-instruction (begin-activity 127 2 nil print-begin-activity)
  (setq fixnum-register-1 (code-constant 0))
  (cond
    ((>f fixnum-register-1 127)
     (setq fixnum-register-1 (-f fixnum-register-1 128)))
    (current-profile-structure?
     ;; Add profiling code here!  -jra 5/30/92
     (incff (svref (profiling-activity-count-array current-profile-structure?)
		   fixnum-register-1))))
  (setq current-computation-activity fixnum-register-1)
  (incff stack-program-counter)
  (setq cached-stack-program-counter stack-program-counter)
  (when major-tracing?
    (write-major-trace-of-activity local-stack top-of-stack)))

(defun write-major-trace-of-activity (local-stack top-of-stack)
  (when (or (=f tracing-message-level 2) (=f breakpoint-level 2))
    (write-major-trace-message
      (setq forgive-long-procedure-instruction? t)
      (tformat "About to execute the activity: ")
      (write-activity-given-index
	*current-computation-frame* current-computation-component-particulars
	current-computation-activity)
      (tformat "~%Within: ")
      (write-stack-evaluator-backtrace
	*current-computation-frame* current-computation-component-particulars
	current-computation-instance local-stack top-of-stack cached-stack-frame-base))))

(defparameter insert-begin-activity-instruction-into-byte-code-stream? t)

	    
(def-stack-instruction-emitter begin-activity
    (byte-code-stream activity suppress-profile?)
  (cond ((or insert-begin-activity-instruction-into-byte-code-stream?
	     ;; this is so the user can tell if a rule has fired when using the profiling
	     ;; facility
	     (=f activity (activity-index "begin rule actions")))
	 (emit-instruction-byte-code byte-code-stream 'begin-activity)
	 (when (or (minuspf activity)
		   (>f activity (length registered-activities-array))
		   (>f activity 127))
	   (compiler-bug
	     "begin activity byte code emitter"
	     "The given activity number, ~a, was out of range."
	     activity)
	   (setq activity 0))
	 (when suppress-profile?
	   (incff activity 128))
	 (write-byte-code-to-stream byte-code-stream activity))
	;; don't insert instruction, generate map
	(t
;	 (break "emitter")
	 (add-activity-translation-to-code-stream
	   byte-code-stream
	   (byte-code-stream-address byte-code-stream)
	   activity)

	 ()
	 ))
)


;;; Instruction 128, the `PUSH-CACHED-ITEM stack instruction' locates the given
;;; item, if any, that is cached in the procedure constant vector.  This
;;; instruction is used as an optimization to replace the name-reference
;;; stack-instruction.

;;; If the item does not exist, for example, if it was deleted, or if the item
;;; is not active, this instruction will leave a NIL on the top of the stack
;;; when the allow-no-item byte is anything but zero, otherwise it will signal a
;;; stack error.

;;;   PUSH-CACHED-ITEM (high-byte-name-constant-index, low-byte, allow-no-item)

(def-stack-error cached-item-error (item-or-item-name? top-of-stack)
  (cond ((null item-or-item-name?)
	 "The designated item does not exist.")
	((symbolp item-or-item-name?)
	 "No item named ~a exists." )
	((and (frame-of-class-p item-or-item-name? 'item)
	      (not (active-p item-or-item-name?))
	      (not (role-serve-inactive-objects?)))
	 "~NF cannot be referenced because it is disabled or inactive.")
	#+mtg2
	((null (check-faction-at-runtime item-or-item-name?))
	 "~NF cannot be referenced because it belongs to another faction.")
	(t
	 "The designated item does not exist."))
  item-or-item-name?)

(defun get-cur-faction-item (item)
  (let* ((name-or-names (name-or-names-for-frame item))
	 (name
	  (when name-or-names
	    (if (symbolp name-or-names) name-or-names
		(car-of-cons name-or-names)))))
    (get-faction-instance-with-name-if-any
     (car-of-cons current-faction-global) 'item name)))

(def-stack-instruction (push-cached-item 128 4 nil
			print-cached-item
			pprint-push-cached-item-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  ;; Item or (<item-name> . <cached-name-cons-marker>)
  (setq register-2 (svref-without-inlining constant-vector fixnum-register-1))
  (setq register-1 (and (not (consp register-2))
			(serve-item-p register-2)
			register-2))
  #+mtg2
  (when (and register-1 (null (check-faction-at-runtime register-2)))
    (let ((it (get-cur-faction-item register-1)))
      (if it (setq register-2 it) (setq register-1 nil))))
  (when (and (null register-1) (=f (code-constant 2) 0))
    (cached-item-error (if (consp register-2)
			   (car-of-cons register-2)	;item name
			   register-2)		;item
		       top-of-stack))
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-1)
  (incff stack-program-counter 3))

(def-stack-instruction-emitter push-cached-item
			       (byte-code-stream name-constant no-item-ok?)
  (emit-instruction-byte-code byte-code-stream 'push-cached-item)
  (let* ((name-constant-cons
	   ;; The item name will be cached, but in a form that will not
	   ;; collide (i.e., be constant folded) with other, non-cached-item,
	   ;; constant references to the same symbol.
	   (slot-value-cons name-constant cached-name-cons-marker))
	 (constant-index
	   ;; Always register the item name, as a cons.  The consistency
	   ;; analysis for the free-reference will handle replacing the cached
	   ;; name with the item, if the named item exists.

	   ;; This is done for design reasons, so that the name index is
	   ;; maintained in one part of the code.  But, more importantly, it is
	   ;; done so that different name references do not use the same
	   ;; constant vector location.  For example, if the index was
	   ;; registered first, this code be constant-folded with another
	   ;; constant (the same number), but from a different expression.  This
	   ;; could then cause problems, if a free-reference updates the
	   ;; constant for one expression, while the other expression still
	   ;; refers to it and expects the old value.
	   (register-internal-constant-in-byte-code-stream
	     byte-code-stream name-constant-cons)))
    (reclaim-slot-value-cons name-constant-cons)
    (emit-long-code-constant-to-stream byte-code-stream constant-index)
    (write-byte-code-to-stream byte-code-stream (if no-item-ok? 1 0))

    ;; Note that the free reference is recorded here instead of the
    ;; preferred-instruction-chooser for push-cached-item because the
    ;; free-reference needs the constant index.
    (record-free-reference
      'cached-name (phrase-cons name-constant constant-index))))



;;; Instruction 132, the `CACHED-ATTRIBUTE-VALUE stack instruction' locates the
;;; value of an item's attribute.  The item is taken from the stack.  The
;;; attribute is specified by an index to the constant-vector which holds either
;;; an attribute vector-index or a list which contains the attribute name.  The
;;; attribute name is needed when the index cannot be determined.  This
;;; instruction is used as an optimization to replace the attribute-value
;;; instruction.

;;; Note that this instruction handles only the named attribute of a named item,
;;; where the item must exist (i.e., no item is not allowed).  Note that, in
;;; several cases, the attribute can be system defined.  See authorized-system-
;;; slots.
;;; It does not handle the following cases:
;;; - attributes of an item, where "no item" is allowed in the expressions
;;; (handled by serve-first-value-of-role);
;;; - indirectly named attributes (see the attribute-value role);
;;; - attributes that are a frame or place reference (see the attribute-frame-
;;; or-place-reference stack-instruction;
;;; - system slots that are unauthorized-system-slot-p.

;;; Note that this instruction does not require stability or dependency.

;;;   CACHED-ATTRIBUTE-VALUE (high-byte-name-constant-index, low-byte)

(def-substitution-macro cached-attribute-value-no-value-error
    (top-of-stack compiled-item compiled-item-component-particulars?
		  constant-vector-index constant-vector-attribute-cache item)
  (raw-stack-error-named-error
    top-of-stack
    (cached-attribute-value-no-value-error-1
      compiled-item compiled-item-component-particulars?
      constant-vector-index constant-vector-attribute-cache item)))

(def-stack-instruction (cached-attribute-value 132 3 1
			 print-cached-attribute
			 pprint-cached-attribute-value-instruction)
  (setq fixnum-register-1 (long-code-constant 0))
  (setq register-1 (svref-without-inlining constant-vector fixnum-register-1)) ; index or cons
  (setq register-2 (arg 0))		; item
  (setq register-3
	(frame-or-evaluation-value-given-user-vector-index
	  register-2 register-1))
  (when (null register-3)
    (cached-attribute-value-no-value-error
      top-of-stack *current-computation-frame*
      current-computation-component-particulars fixnum-register-1 register-1
      register-2))
  (when (consp register-2) ; this means it's a structure
    (assert-for-development
      (evaluation-structure-p register-2)
      "Tell Joe that he's wrong")
    (reclaim-evaluation-structure register-2))
  (setf (arg 0) register-3)
  (incff stack-program-counter 2))



;;; The function `cached-attribute-value-no-value-error' is used to signal a
;;; stack-error when the attribute does contain a value.  The constant-vector
;;; index is the index to the attribute-cache information in the compiled-item.
;;; The if non-nil, apply to the compiled item.  The item argument is the item
;;; that should contain the attribute.

(defun cached-attribute-value-no-value-error-1
    (compiled-item compiled-item-component-particulars?
     constant-vector-index constant-vector-attribute-cache item)
  (let ((attribute-name? nil)
	(class-specific-attribute-class? nil)
	(slot-description? nil))
    (cond ((consp constant-vector-attribute-cache)
	   (setq attribute-name? (car constant-vector-attribute-cache))
	   (setq class-specific-attribute-class?
		 (fourth constant-vector-attribute-cache)))
	  ((integerp constant-vector-attribute-cache)
	   (let ((cached-attribute-free-reference?
		   (find-cached-attribute-free-reference
		     constant-vector-index compiled-item
		     compiled-item-component-particulars?)))
	     (when cached-attribute-free-reference?
	       ;; The attribute being referenced is defined in another class.
	       (setq class-specific-attribute-class?
		     (fifth cached-attribute-free-reference?)))
	     (setq slot-description?
		   (get-slot-description-with-user-vector-slot-index
		     constant-vector-attribute-cache item))
	     (when slot-description?
	       (setq attribute-name? (pretty-slot-name slot-description?)))))
	  (t nil))
    (cond (attribute-name?
	   (attribute-returned-no-values-error-1 attribute-name? item class-specific-attribute-class?))
	  (t
	   ;; This is here in the unlikely event that the name of the attribute
	   ;; cannot be located based on the user-vector-index.
	   (tformat-stack-error-text-string
	     "An attribute of ~NF contained nothing, causing this reference to fail."
	     item)))))




;;; The function `find-cached-attribute-free-reference' is given a
;;; constant-vector index and the compiled item containing the cached-attribute
;;; free-reference.  It returns, if possible, the corresponding free-reference.

;;; Note that this function returns nil for items that have multiple
;;; free-reference vector (e.g., cells).  It cannot determine the correct
;;; free-reference vector.

;;; The form of the cached-attribute free-reference is:
;;; (attribute item-name? class? constant-vector-index
;;;  class-specific-attribute-class cached-attribute-cons-marker)

(defun find-cached-attribute-free-reference
    (constant-vector-index compiled-item compiled-item-component-particulars?)
  (let* ((byte-code-body?
	   (get-byte-code-body-if-any
	     compiled-item compiled-item-component-particulars?))
	 (free-references?
	   (and byte-code-body?
		(byte-code-body-free-references byte-code-body?)))
	 (cached-attribute-free-reference? nil))
    (when free-references?
      (loop with vector-length = (length free-references?)
	    for index from 0 below vector-length
	    for free-ref = (svref free-references? index)
	    until cached-attribute-free-reference?
	    do
	(when (and (consp free-ref)
		   #+(and development lispworks (not chestnut-3))
		   (not (lw:dotted-list-p free-ref)) ; TODO: GENSYMCID-847 involved
		   (eq (length free-ref) 6)
		   (eq (sixth free-ref) cached-attribute-cons-marker)
		   (eq (fourth free-ref) constant-vector-index))
	  (setq cached-attribute-free-reference? free-ref))))
    cached-attribute-free-reference?))



;;; The `stack-instruction emitter for cached-attribute-value' registers the
;;; attribute name as a constant, emits the byte codes for the instruction, and
;;; records the cached-attribute free-reference.

;;; Note that the attribute name is register as a constant, but in a format that
;;; will not collide (constant-fold) with other values in the constant vector.
;;; In particular, this prevents constant-folding with non-attribute references
;;; to the same symbol and with other references to the same attribute that
;;; refer to a different class or instance of a different class.
;;; The form of cached attribute information in the constant-vector is:
;;;   (attribute-name item-name? class-name? class-specific-attribute-class?
;;;    <cached-attribute-cons-marker>)
;;; or
;;;   <attribute-vector-index>

;;; Also, note that the attribute name and not the index is cached from this
;;; emitter.  The consistency analysis for the cached-attribute free-reference
;;; will handle replacing the cached attribute name with the attribute index
;;; location, if possible.

;; The index is not cached here for two reasons.  First, it's better to have the
;; attribute index maintained in one place of the code.  But, more importantly,
;; it is done so that different attribute references do not use the same
;; constant vector location.  For example, if the index was registered first,
;; this code be constant-folded with another constant (the same number), but
;; from a different expression.  This could then cause problems, if a
;; free-reference updates the constant for one expression, while the other
;; expression still refers to it and expects the old value.

(def-stack-instruction-emitter cached-attribute-value
    (byte-code-stream attribute-name item-name? class-name?
		      class-specific-attribute-class?)
  (emit-instruction-byte-code byte-code-stream 'cached-attribute-value)
  (let* ((attribute-constant-list
	     (slot-value-list
	       attribute-name item-name? class-name?
	       class-specific-attribute-class?
	       cached-attribute-cons-marker))
	 (constant-index
	   ;; Always register the attribute name, as a list.  The consistency
	   ;; analysis for the free-reference will handle replacing the cached
	   ;; attribute name with the attribute index location, if possible.
	       (register-internal-constant-in-byte-code-stream
		 byte-code-stream attribute-constant-list)))
    (reclaim-slot-value-list attribute-constant-list)
    (emit-long-code-constant-to-stream byte-code-stream constant-index)
    ;; Note that the free reference is recorded here instead of the
    ;; preferred-instruction-chooser for cached-attribute-value because the
    ;; free-reference needs the constant index.
    (record-free-reference
      'cached-attribute
      (phrase-list attribute-name item-name? class-name? constant-index
		   class-specific-attribute-class?
		   cached-attribute-cons-marker))
    (compiler-warning-if-superseded-attribute attribute-name)))






;;;;  Boolean Branch Instructions




;;; The following boolean branch statements are modelled after the non-boolean
;;; conditional branch statements.  These new instructions should behave the
;;; same except that the branching is based on true or false (boolean)
;;; truth-value arguments.

;; Do we need to implement corresponding boolean-branch instructions for the
;; following: branch-long-if-not-false, branch-long-if-false,
;; branch-long-if-true??  I don't see that they are used yet.  - cpm, 4/27/93




;;; Instruction 129, the `BOOLEAN-BRANCH-IF-NOT-TRUE stack instruction' takes
;;; one byte worth of code constant argument from the instruction stream and one
;;; argument from the top of the stack.  The value on the stack should be either
;;; the evaluation-value for truth or falsity.

;;; If the logical value is not true, then a branch will be executed to the
;;; program counter in the instruction stream code constant.  If the value is
;;; true, then execution will continue at the instruction following the branch.
;;; Note that a mini-branch is needed to continue, since this instruction must
;;; branch past the code constant if continuing.

;;; Also, there is an extra unused code constant byte here, so that this is the
;;; same length as the BOOLEAN-BRANCH-LONG-IF-NOT-TRUE instruction.

;;; BOOLEAN-BRANCH-IF-NOT-TRUE (program-counter, unused-byte)

(def-stack-instruction (boolean-branch-if-not-true 129 3 1
			 print-op-and-code-constant
			 pprint-branch-if-not-true-instruction)
  (setq register-1 (arg 0))
  (decff top-of-stack)
  (cond ((evaluation-boolean-is-true-p register-1)
	 (reclaim-evaluation-boolean register-1)
	 (incff stack-program-counter 2))
	(t
	 (reclaim-evaluation-boolean register-1)
	 (setq stack-program-counter (code-constant 0)))))




;;; Instruction 130, the `BOOLEAN-BRANCH-LONG-IF-NOT-TRUE stack instruction'
;;; takes two bytes of instruction address.  It pops a boolean value off the top
;;; of the stack, and branches to the address in the code constants if the value
;;; is not true.  This is the long instruction address version of
;;; BOOLEAN-BRANCH-IF-NOT-TRUE.

;;; BOOLEAN-BRANCH-LONG-IF-NOT-TRUE (high-byte-pc, low-byte-pc)

(def-stack-instruction (boolean-branch-long-if-not-true 130 3 1
			 print-op-and-long-code-constant
			 pprint-branch-long-if-not-true-instruction)
  (setq register-1 (arg 0))
  (decff top-of-stack)
  (cond ((evaluation-boolean-is-true-p register-1)
	 (reclaim-evaluation-truth-value register-1)
	 (incff stack-program-counter 2))
	(t
	 (reclaim-evaluation-truth-value register-1)
	 (setq stack-program-counter (long-code-constant 0)))))




;;; Instruction 131, the `BOOLEAN-BRANCH-RELATIVE-IF-NOT-TRUE stack instruction'
;;; takes one byte of instruction address.  It pops a boolean value off the top
;;; of the stack, and performs a relative branch by the given instruction count
;;; minus 128 if if the value is not true.  This is the relative branch version
;;; of BOOLEAN-BRANCH-IF-NOT-TRUE.  An unused-byte pads the length of this
;;; instruction to match BOOLEAN-BRANCH-LONG-IF-NOT-TRUE.

;;; BOOLEAN-BRANCH-RELATIVE-IF-NOT-TRUE (relative-pc-plus-128, unused-byte)

(def-stack-instruction (boolean-branch-relative-if-not-true 131 3 1
			 print-op-and-relative-code-constant-address
			 pprint-branch-relative-if-not-true-instruction)
  (setq register-1 (arg 0))
  (decff top-of-stack)
  (cond ((evaluation-boolean-is-true-p register-1)
	 (reclaim-evaluation-truth-value register-1)
	 (incff stack-program-counter 2))
	(t
	 (reclaim-evaluation-truth-value register-1)
	 (setq stack-program-counter
	       (+f (-f stack-program-counter 1)
		   (relative-code-constant 0))))))



;; The following emitters for boolean-branch instructions should be removed if
;; they are not used!!  These instructions may be emitted elsewhere, for
;; example, through the regular branch emitters, as an optmization.  - cpm,
;; 4/28/93

;;; The stack-instruction-emitter `boolean-branch-long-if-not-true' takes a
;;; byte-code-stream and an address and emits byte codes and address
;;; registrations.

;(def-stack-instruction-emitter boolean-branch-long-if-not-true
;       (byte-code-stream target-tag-statement)
;  (register-byte-code-tag-resolution-point
;    byte-code-stream target-tag-statement)
;  (emit-instruction-byte-code byte-code-stream 'boolean-branch-long-if-not-true)
;  (write-byte-code-to-stream byte-code-stream 0)
;  (write-byte-code-to-stream byte-code-stream 0))

;(def-byte-code-resolver boolean-branch-long-if-not-true
;			(byte-code-stream byte-vector address tag)
;  (declare (ignore byte-code-stream))
;  (let* ((tag-address (instruction-address-for-tag tag nil))
;	 (relative-offset (-f tag-address address)))
;    (cond ((<f tag-address 256)
;	   (setf (byte-vector-aref byte-vector address)
;		 (op-code-for-stack-instruction 'boolean-branch-if-not-true))
;	   (setf (byte-vector-aref byte-vector (+f address 1))
;		 tag-address))
;	  ((relative-code-constant-p relative-offset)
;	   (setf (byte-vector-aref byte-vector address)
;		 (op-code-for-stack-instruction
;		   'boolean-branch-relative-if-not-true))
;	   (setf (relative-code-constant-in-byte-vector
;		   byte-vector (+f address 1))
;		 relative-offset))
;	  (t
;	   (setf (long-code-constant-in-byte-vector byte-vector (+f address 1))
;		 tag-address)))))


(defun-void pprint-nth-array-element-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "fetch ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string "[")
  (write-stack-argument 2 2 stack top-of-stack)
  (twrite-string "]"))

;; ion (evaluate-role 

;; stack args 2 array and index
;; constants 2-bytes constant-vector index domain-count no-item-allowed

(def-stack-error no-element-for-array-index-error (top-of-stack item index-value)
  "The g2-array ~NF contains no element at index ~a."
  item index-value)

(def-stack-instruction (nth-integer-array-element 133 5 2
			 nil ; print-op-role-long-and-arg-count
			 pprint-nth-array-element-instruction)
  (setq register-1 (arg 0)) ; the g2-array object
  (setq register-2 (arg 1)) ; the eval-integer holding index
  (setq fixnum-register-1 (evaluation-integer-value register-2))
  (reclaim-evaluation-integer register-1)
  (setq fixnum-register-2 (g2-array-length register-1)) 
  (cond
    ((or (>=f fixnum-register-1 fixnum-register-2) ; out-of-bounds high
	 (<f fixnum-register-1 0))
     (bad-g2-array-index-error register-1
			       fixnum-register-1
			       top-of-stack)
     (setq register-3 nil)) 
    (t
     (setq register-3
	   (copy-evaluation-integer
	     (managed-svref (managed-g2-array register-1)
			    fixnum-register-1)))
     (unless register-3
       (no-element-for-array-index-error top-of-stack register-1
				   fixnum-register-1))))
  (setf (arg 0) register-3)
  (incff stack-program-counter 4)
  (decff top-of-stack))

(def-stack-instruction (nth-float-array-element 134 5 2
			 nil ; print-op-role-long-and-arg-count
			 pprint-nth-array-element-instruction)
  (setq register-1 (arg 0)) ; the g2-array object
  (setq register-2 (arg 1)) ; the eval-integer holding index
  (setq fixnum-register-1 (evaluation-integer-value register-2))
  (reclaim-evaluation-integer register-1)
  (setq fixnum-register-2 (g2-array-length register-1)) 
  (cond
    ((or (>=f fixnum-register-1 fixnum-register-2) ; out-of-bounds high
	 (<f fixnum-register-1 0))
     (bad-g2-array-index-error register-1
			       fixnum-register-1
			       top-of-stack)
     (setq register-3 nil)) 
    (t
     (setq register-3
	   (make-evaluation-float
	     (managed-float-aref (managed-g2-array register-1)
				fixnum-register-1)))))
  (setf (arg 0) register-3)
  (incff stack-program-counter 4)
  (decff top-of-stack))

(defun-void pprint-change-nth-array-element-instruction
       (pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (twrite-string "change ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-string "[")
  (write-stack-argument 3 3 stack top-of-stack)
  (twrite-string "] = ")
  (write-stack-argument 2 3 stack top-of-stack))


(def-stack-instruction (change-nth-integer-array-element 135 1 3
			 nil ; print-op-role-long-and-arg-count
			 pprint-nth-array-element-instruction)
  (setq register-1 (arg 0)) ; the g2-array object
  (setq register-2 (arg 2)) ; the eval-integer holding index
  (setq fixnum-register-1 (evaluation-integer-value register-2))
  (reclaim-evaluation-integer register-1)
  (setq fixnum-register-2 (g2-array-length register-1))
  (setq register-3 (arg 1)) ; the properly-coerced new value
  (cond
    ((or (>=f fixnum-register-1 fixnum-register-2) ; out-of-bounds high
	 (<f fixnum-register-1 0))
     (bad-g2-array-index-error register-1
			       fixnum-register-1
			       top-of-stack)
     (setq register-3 nil)) 
    (t
     (note-change-to-runtime-data-for-block register-1)
     (setf (managed-svref (managed-g2-array register-1) fixnum-register-1)
	   (evaluation-integer-value register-3))
     (reclaim-evaluation-integer register-3)))
  (decff top-of-stack 3))

(def-stack-instruction (change-nth-float-array-element 136 1 3
			 nil ; print-op-role-long-and-arg-count
			 pprint-nth-array-element-instruction)
  (setq register-1 (arg 0)) ; the g2-array object
  (setq register-2 (arg 2)) ; the eval-integer holding index
  (setq fixnum-register-1 (evaluation-integer-value register-2))
  (reclaim-evaluation-integer register-1)
  (setq fixnum-register-2 (g2-array-length register-1))
  (setq register-3 (arg 1)) ; the properly-coerced new value
  (cond
    ((or (>=f fixnum-register-1 fixnum-register-2) ; out-of-bounds high
	 (<f fixnum-register-1 0))
     (bad-g2-array-index-error register-1
			       fixnum-register-1
			       top-of-stack)
     (setq register-3 nil)) 
    (t
     (note-change-to-runtime-data-for-block register-1)
     (mutate-managed-float-array
       (managed-g2-array register-1) fixnum-register-1
       (evaluation-float-value register-3))
     (reclaim-evaluation-float register-3)))
  (decff top-of-stack 3))


;;; Instruction 137, the `SIGNAL-ERROR-NEW stack instruction', takes an
;;; error-object off the stack and signals an error with that object.
;;; ajs (5/29/96)

(def-stack-instruction (signal-error-new 137 1 1 nil pprint-signal-error-new-instruction)
  (setq register-1 (arg 0))
  (decff top-of-stack 1)
  (raw-stack-error-throw-object top-of-stack register-1))




;;; Instruction 138, the `MOVE-FROM-SURROUNDING-LOCAL-VAR stack instruction'
;;; retrieves values from local variables which may or may not be local to this
;;; environment, clearing the local variable in the process.  It takes a high
;;; byte and low byte of an index into the constant vector which should contain
;;; a var-spot naming the local variable.  Whatever the type of value in the
;;; local-var, it is pushed onto the stack and NIL is put into its former place.

;;; MOVE-FROM-SURROUNDING-LOCAL-VAR (index-high-byte, index-low-byte)

(def-stack-instruction (move-from-surrounding-local-var 138 3 nil
			 print-op-and-surrounding-local-var
			 pprint-move-from-surrounding-local-var-instruction)
  (setq fixnum-register-2 (long-code-constant 0))
  (setq fixnum-register-1 (var-spot-index-nesting fixnum-register-2))
  (cond ((pluspf fixnum-register-1)
	 (setq register-2 current-computation-instance)
	 (unless (code-body-invocation-p register-2)
	   (signal-nested-code-bodies-out-of-procedures
	     top-of-stack fixnum-register-2))
	 (loop while (pluspf fixnum-register-1) do
	   (setq register-2 (code-body-caller register-2))
	   (decff fixnum-register-1))
	 (setq fixnum-register-1
	       (var-spot-local-index fixnum-register-2))
	 (setq register-4 (invocation-local-var-vector register-2))
	 (setq register-3
	       (svref register-4 fixnum-register-1))
	 (setf (svref register-4 fixnum-register-1) nil))
	(t
	 (setq register-3
	       (svref local-var-vector fixnum-register-2))
	 (setf (svref local-var-vector fixnum-register-2) nil)))
  (when (null register-3)
    (signal-no-value-in-local-var-error
      fixnum-register-2 *current-computation-frame*
      current-computation-component-particulars top-of-stack))
  (incff top-of-stack)
  (setf (svref local-stack top-of-stack) register-3)
  (incff stack-program-counter 2))

(def-stack-instruction-emitter move-from-surrounding-local-var
    (byte-code-stream var-spot)
  (unless (and (valid-var-spot-p var-spot)
	       (not (memq (car var-spot) '(stack-frame-var stack-arg))))
    (compiler-bug
      "move-from-local-var emitter"
      "An invalid var spot, ~a, was given."
      var-spot)
    (setq var-spot '(var-spot 0)))
  (emit-instruction-byte-code
    byte-code-stream 'move-from-surrounding-local-var)
  (emit-long-code-constant-to-stream
    byte-code-stream (second var-spot)))

;;; Instruction 139, FUNCALL-INSTRUCTION-N can be found earlier in this file,
;;; after instruction 52, FUNCALL-INSTRUCTION.

;;; Instruction 140, the `ALLOW-NO-ITEM-FOR-EVALUATOR stack
;;; instruction, should be used immediately before any inlined evaluator
;;; if it is being called within the context of the "there exists" operator.
;;; It takes two one-byte fixnum arguments in the instruction stream. The
;;; first instruction-stream argument, N, is the number of arguments to the
;;; inlined evaluator. It checks that none
;;; of the top N elements on the stack are no-item. If any one of them is
;;; no-item, it pops them all from the stack, pushes a no-item on the stack,
;;; and branches around the following evaluator. The second instruction
;;; stream argument gives the distance to branch. (currently 1 for
;;; inlined evaluators, 2 for funcalled evaluators), plus 2 to skip
;;; over the rest of the allow-no-item-for-evaluator instruction itself.
;;; This essentially transforms the following
;;; in-line evaluator into a new evaluator that can handle no-item (by
;;; returning no-item if any of its arguments are no-item), while only
;;; using one extra byte-code for all of these extra evaluators.
;;; -alatto, 11/17/98

(def-stack-instruction-emitter allow-no-item-for-evaluator
    (byte-code-stream nargs tag)
  (register-byte-code-tag-resolution-point byte-code-stream tag)
  (emit-instruction-byte-code byte-code-stream 'allow-no-item-for-evaluator)
  (write-byte-code-to-stream byte-code-stream nargs)
  (write-byte-code-to-stream byte-code-stream 0))

;;; One less than the difference, since we've already incremented the
;;; program counter to skip over the allow-no-item-for-evaluator bytecode
;;; itself
(def-byte-code-resolver allow-no-item-for-evaluator
    (byte-code-stream byte-vector address tag)
  (declare (ignore byte-code-stream))
  (setf (byte-vector-aref byte-vector (+f address 2))
	(1-f (-f (instruction-address-for-tag tag nil) address))))

(def-stack-instruction (allow-no-item-for-evaluator 140 3)
  (setf fixnum-register-1 (code-constant 0))
  (setf register-1 nil)
  (decff fixnum-register-1)
  (loop while (>=f fixnum-register-1 0) do
    (when (null (svref local-stack (-f top-of-stack fixnum-register-1)))
      (setf register-1 t))
    (decff fixnum-register-1))
  (if register-1
      (progn
	(setf fixnum-register-1 (code-constant 0))
	(loop while (pluspf fixnum-register-1) do
	  (setf register-1 (svref local-stack top-of-stack))
	  (reclaim-if-evaluation-value register-1)
	  (decff top-of-stack)
	  (decff fixnum-register-1))
	(incff top-of-stack)
	(setf (svref local-stack top-of-stack) nil)
	(setf fixnum-register-2 (code-constant 1))
      	(incff stack-program-counter fixnum-register-2))
      (incff stack-program-counter 2)))

;;; Instruction 141, PUSH-RETURNED-VALUES-LONG can be found earlier in this file,
;;; after instruction 59, PUSH-RETURNED-VALUES.

(def-stack-instruction (coerce-integer-to-long 144 1 1
			nil nil)
  (setq register-1 (arg 0))
  (setq register-2
	(make-evaluation-long register-1))
  (setf (arg 0) register-2))

;;;; In-Line Stack Evalutors




;;; In-line stack-evaluators also use stack-instruction numbers.  The
;;; instruction numbers for these begin at base-in-line-evaluator-number, which
;;; is currently 150.  There are no more than
;;; maximum-number-of-in-line-evaluators evaluators, which is currently 100.


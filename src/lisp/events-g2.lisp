; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")
 
;;;; Module EVENTS-G2 (NTW Compiler)

;;; Joe Devlin 1995-1996

;;; This module defines:
;;;   1. The NTW compiler. ( upto an intermediate format)
;;;   2. The deinition classes that are visible to G2 (tw-procedure) etc.
;;;   3. Some icp-message handling routines to inform NTW of
;;;      about the definitions it should have about the above classes.

;;;; Forward References

#+java-export-facilities
(declare-forward-reference add-class-export-info-attributes function)

#+gesture-definition-facilities
(progn
;;;; TW-Procedure (aka Gesture) Compilation

;;; The following grammar rules implement the parser for tw-procedures and
;;; tw-methods.  The grammar for statements here is distinct from G2's,
;;; but implements a strict subset of G2's statements.  The expressions
;;; embedded within these statements is borrowed from the unique-expression
;;; and logical-expression categories defined in G2.  Not every G2 expression
;;; is supported; unsupported constructs are filtered by the slot-value-compiler.

(add-grammar-rules
  '((gesture-definition
     (gesture-name gesture-prototype
      gesture-locals-spec gesture-body)
     (1 2 3 4))
    (gesture-definition
     (gesture-name gesture-prototype
      gesture-body)
     (1 2 nil 3))
    (gesture-name unreserved-symbol)
    (gesture-prototype
     ('\( gesture-argument-list '\) '\= gesture-return-spec)
     (2 5))
    (gesture-prototype
     ('\( '\))
     (nil nil))
    (gesture-prototype
     ('\( '\) '\= gesture-return-spec)
     (nil 4))
    (gesture-prototype
     ('\( gesture-argument-list '\))
     (2 nil))))

;    (gesture-prototype
;     (gesture-argument-spec '\= gesture-return-spec)
;     (1 3))
;    (gesture-prototype
;     ('\( '\))
;     (foo bar))
;    (gesture-prototype
;     gesture-argument-spec
;     (1 nil))
;    (gesture-argument-spec
;     ('\( gesture-argument-list '\))
;     2)
;    (gesture-argument-spec
;     ('\( '\))
;     nil)
;    ))

(add-grammar-rules-for-list 'gesture-argument-list 'gesture-var-spec)

(add-grammar-rules
  '((gesture-var-spec
     (local-name '\: gesture-value-type)
     (1 3))
    (gesture-value-type 'truth-value)
    (gesture-value-type 'integer)
    (gesture-value-type 'quantity number)
    (gesture-value-type 'value datum)
    (gesture-value-type 'text)
    (gesture-value-type 'symbol)
    (gesture-value-type 'float)
    (gesture-value-type 'sequence (sequence))
    (gesture-value-type 'structure (structure))
    (gesture-value-type ('class class))
    (gesture-value-type 'item-or-value item-or-datum)
    (gesture-return-spec
     ('\( gesture-return-type-list '\))
     2)
    (gesture-return-type-list gesture-value-type (1))
    (gesture-return-type-list 
     (gesture-value-type '\, gesture-return-type-list)
     (1 . 3))
    (gesture-locals-spec
     (gesture-locals-list '\;)
     1)))

(add-grammar-rules-for-list 'gesture-locals-list 'gesture-local-spec '\;)
     
(add-grammar-rules
  '((gesture-local-spec
     gesture-var-spec
     (1 nil))
    (gesture-local-spec
     (gesture-local-list '\: gesture-value-type) 
     (multiple-gesture-locals 1 3))
    (gesture-local-list
     (local-name '\, local-name) (1 3))
    (gesture-local-list
     (local-name '\, gesture-local-list)
     (1 . 3))
    (gesture-local-spec
     (gesture-var-spec '\= gesture-expression)
     (1 3))
    (gesture-expression unique-expression
     (unique-expression 1))
    (gesture-expression 'false
     (unique-expression 1))
    (gesture-expression 'true
     (unique-expression 1))
    (gesture-logical-expression logical-expression
     (logical-expression 1))
    (gesture-call-expression
     (unreserved-symbol '\( '\))
     (1 nil))
    (gesture-call-expression
     (unreserved-symbol gesture-argument-list)
     (1 2))
    (gesture-constant number)
    (gesture-constant ('the 'symbol symbol) 3)

    (gesture-constant 'true)
    (gesture-constant 'false)
    ;; ?? (gesture-constant 'none)
    (gesture-constant whole-string)
     
    (gesture-argument-list
     ( '\( gesture-expression '\) )
     (2))
    (gesture-argument-list
     ( '\( gesture-expression '\, gesture-argument-list-tail)
     (2 . 4))
  
    (gesture-argument-list-tail
     (gesture-expression '\) )
     (1))
    (gesture-argument-list-tail
     (gesture-expression '\, gesture-argument-list-tail)
     (1 . 3))))

(add-grammar-rules
  '((gesture-expression-list gesture-expression (1))
    (gesture-expression-list
     (gesture-expression '\, gesture-expression-list)
     (1 . 3))))

;(add-grammar-rules-for-list 'gesture-expression-list 'gesture-expression)

(add-grammar-rules
  '((gesture-body
     ('begin gesture-compound-statement-tail)
     (compound-statement 2 nil))
    (gesture-body
     ('begin gesture-compound-statement-tail
      gesture-error-or-exit-statement)
     (compound-statement 2 3))
    (gesture-compound-statement
     ('begin gesture-compound-statement-tail)
     (compound-statement 2 nil))
    (gesture-compound-statement
     ('begin gesture-compound-statement-tail
      gesture-error-or-exit-statement)
     (compound-statement 2 3))
    (gesture-compound-statement-tail 'end nil)
    (gesture-compound-statement-tail
     (gesture-compound-statement-list 'end)
     1)
    (gesture-compound-statement-tail
     (gesture-compound-statement-list '\; 'end)
     1)

    (gesture-error-or-exit-statement
     ('on 'error '\( local-name '\) gesture-compound-statement-tail)
     (on-error 4 6))
    (gesture-error-or-exit-statement 
     ('on 'exit  gesture-compound-statement-tail)
     (on-exit nil 3))
    ))

(add-grammar-rules-for-list
  'gesture-compound-statement-list 'gesture-statement '\;)

(add-grammar-rules
  '((gesture-statement gesture-compound-statement)
    (gesture-statement gesture-if-statement)
    (gesture-statement gesture-for-statement)
    (gesture-statement gesture-assignment-statement)
    (gesture-statement gesture-call-gesture-statement)
    (gesture-statement gesture-call-g2-statement)
    (gesture-statement gesture-call-next-method-statement)
    (gesture-statement gesture-return-statement)
    (gesture-statement gesture-change-slot-statement)
    (gesture-statement gesture-change-array-length-statement)
    (gesture-statement gesture-repeat-statement)
    (gesture-statement gesture-exit-if-statement)
    (gesture-statement gesture-case-statement)
    (gesture-statement gesture-create-statement)
    (gesture-create-statement
     ('create 'a class local-name)
     (create 3 4))
    (gesture-create-statement
     ('create 'an class local-name)
     (create 3 4))
    (gesture-change-array-length-statement
     ('change 'the 'array-length 'of gesture-expression
      'to gesture-expression)
     (change-array-length 5 7))
    (gesture-change-slot-statement
     ('change 'the unreserved-symbol 'of gesture-expression
      '\= gesture-expression)
     (change-slot 3 5 7))
    (gesture-repeat-statement
     ('repeat gesture-compound-statement-tail)
     (repeat (compound-statement 2)))
    (gesture-exit-if-statement
     ('exit 'if gesture-logical-expression)
     (exit-if 3))
    (gesture-if-statement
     ('if gesture-logical-expression 'then gesture-statement)
     (if 2 4 nil))
    (gesture-if-statement
     ('if gesture-logical-expression
	  'then gesture-statement
	  'else gesture-statement)
     (if 2 4 6))
    (gesture-for-statement
     ('for local-name '\= gesture-expression 'to gesture-expression 'do
      gesture-compound-statement-tail)
     (for (integer-iteration 2 4 6) (begin 8)))
    (gesture-assignment-statement
     (local-name '\= gesture-expression)
     (assignment 1 3))
    (gesture-call-next-method-statement
     ('call 'next 'method)
     (call-next-method nil nil))
    (gesture-call-next-method-statement
     (gesture-call-assignment-target '\=
      'call 'next 'method)
     (call-next-method 1 nil))
    (gesture-call-gesture-statement
     ('call gesture-call-expression)
      ;gesture-name gesture-expression-list-with-parens)
     (call-gesture nil . 2)) ; 2 3))
    (gesture-call-gesture-statement
     (gesture-call-assignment-target '\=
      'call gesture-call-expression)
      ; gesture-name gesture-expression-list-with-parens)
     (call-gesture 1 . 4)) ; 4 5))
    (gesture-call-g2-statement
     ('call gesture-call-expression 'in 'g2)
      ;gesture-name gesture-expression-list-with-parens)
     (call-g2 nil . 2)) ; 2 3))
    (gesture-call-g2-statement
     (gesture-call-assignment-target '\=
      'call gesture-call-expression 'in 'g2)
      ; gesture-name gesture-expression-list-with-parens)
     (call-g2 1 . 4)) ; 4 5))
    (gesture-return-statement
     ('return gesture-expression-list)
     (return 2))
    (gesture-return-statement
     'return
     (return nil))
    (gesture-null-statement '\; (null))))


(add-grammar-rules
  '((gesture-case-statement
     ('case '\( gesture-expression '\) 'of gesture-case-clauses '\; 'end)
     (case-statement 3 . 6))
    
    (gesture-case-clauses
     gesture-case-clause
     (1))
    (gesture-case-clauses
     (gesture-case-clause '\; gesture-case-clauses)
     (1 . 3))
    
    (gesture-case-clause
     (gesture-case-tag-list '\: gesture-statement)
     (1 3)) 

    (gesture-case-tag-list
     gesture-case-tag
     (1))
    (gesture-case-tag-list
     (gesture-case-tag '\, gesture-case-tag-list)
     (1 . 3))
    
    (gesture-case-tag 'otherwise)
    (gesture-case-tag number)
    (gesture-case-tag unreserved-symbol)
    (gesture-case-tag whole-string)
    ))

(add-grammar-rules-for-list 'gesture-call-assignment-target 'local-name)


;;; The slot-value-compiler for gesture-definitions has two passes The first
;;; pass normalizes the parse so that there are not any thing or ('\; thing
;;; thing thing ....) abominations in the compiler's input.  This pass also
;;; performs some conversion of the syntax of expressions generated by G2's
;;; logical-expression and unique-expression types into something that is in
;;; common with the expressions that are not generated by these categories and
;;; is in general more tagged and normalized than what G2 rules give.  This
;;; allows the compiler to have very boring and uniform parse trees to traverse.

(def-slot-value-compiler gesture-definition (parse-result tw-procedure)
  (declare (ignore gesture))
  (pprint-when-tracing-in-events-modules parse-result)
  (let ((simplified-parse (simplify-gesture-parse parse-result)))
    (pprint-when-tracing-in-events-modules simplified-parse)
    (multiple-value-bind (compiled-gesture error?)
	(compile-gesture-definition
	  simplified-parse (frame-of-class-p tw-procedure 'tw-method))
      (cond
	(error?
	 (values bad-phrase error?))
	(t
	 compiled-gesture)))))

;;; gesture-parses do not produce dotted list structure and can do the
;;; following simple recursion to get rid of the crap that list parsing
;;; generates


(defparameter restore-true-and-false-in-simplify-gesture-parse-p t)
  
(defun simplify-gesture-parse-rec (exp)
  (cond
    ;; translate g2-speak to gesture-speak
    ((and (consp exp)
	  (or (eq (car exp) 'unique-expression)
	      (eq (car exp) 'logical-expression)))

     ;; jh, 9/30/97.  The following transform is necessary pending a review of
     ;; the 5/9/97 edit to the add-parallel-grammar-rules form for "unique-" in
     ;; GRAMMAR2.  That edit replaces the symbols TRUE and FALSE with a
     ;; phrase-consed duplicate of evaluation-true-value or
     ;; evaluation-false-value, respectively, via the transformer function
     ;; check-and-scale-certainty-factor.  Doing so appears to violate an
     ;; assumption by simplify-gesture-parse that exp is never a dotted pair.
     (when restore-true-and-false-in-simplify-gesture-parse-p
       (let ((exp-value (cadr exp)))
	 (when (and (consp exp-value)
		    (eq (cdr-of-cons exp-value) 'truth-value))
	   (let* ((truth-level (car-of-cons exp-value))
		  (reverted-value 
		    (cond
		      ((not (fixnump truth-level)) 'false)
		      ((<f truth-level 0) 'false)
		      (t 'true))))
	     (setf (cadr exp) reverted-value)))))
     
     (simplify-gesture-parse-rec
       (unique-expression-to-gesture-expression
	 (cadr exp))))
    ((consp exp)
     ;; jh, 11/10/97.  Following loop takes into account the fact that parsed
     ;; statements need not contain proper lists.
     (loop with maybe-sub-exp-cons? =
	   (cond
	     ;; some hackery to get around add-grammar-rules-for-lists.
	     ((or (eq (car exp) '\,) (eq (car exp) '\;))
	      (cdr exp))
	     (t exp))
	   for sub-exp = (car maybe-sub-exp-cons?)
	   with parsed-exp? = nil
	   with parsed-exp-tail
	   do
       (let* ((parsed-sub-exp (simplify-gesture-parse-rec sub-exp))
	      (parsed-sub-exp-cons (phrase-list parsed-sub-exp)))
	 (cond
	   (parsed-exp?
	    (setf (cdr parsed-exp-tail) parsed-sub-exp-cons)
	    (setq parsed-exp-tail parsed-sub-exp-cons))
	   (t (setq parsed-exp? parsed-sub-exp-cons)
	      (setq parsed-exp-tail parsed-sub-exp-cons)))
	 (setq maybe-sub-exp-cons? (cdr maybe-sub-exp-cons?))
	 (unless (consp maybe-sub-exp-cons?)
	   (setf (cdr parsed-exp-tail)
		 (simplify-gesture-parse-rec maybe-sub-exp-cons?))
	   (loop-finish)))
	   finally (return parsed-exp?)))
    (t
     exp)))

(defun simplify-gesture-parse (exp)
  (let ((locals (caddr exp)))
    (when (and (consp locals) ; locals exist
	       (consp (car locals))
	       (not (consp (caar locals)))) ; bogus singleton case
      (setf (caddr exp) (phrase-list (caddr exp))))
    (simplify-gesture-parse-rec exp)))

;;; The following globals implement the gesture compiling context.

(defvar current-gesture-locals nil)
(defvar current-generated-locals nil)
(defvar current-gesture-returns nil)
(defvar current-gesture-local-initializers nil)
(defvar current-unique-gesture-local-index 0)
(defvar current-compilation-args nil)
(defvar current-compilation-name nil)
(defvar currently-compiling-exists-p nil)
(defvar currently-compiling-method-p nil)
(defvar currently-compiling-local-variables-p nil)
(defvar unique-gesture-local-names nil)
(defvar current-gesture-lexical-block-end nil)
(defvar current-gesture-lexical-block-count 0)
(defvar gesture-lexical-block-labels
  '(block-1 block-2 block-3 block-4
    block-5 block-6 block-7 block-8
    block-9 block-10 block-11 block-12
    block-13 block-14 block-15 block-16
    block-17 block-18 block-19 block-20
    block-21 block-22 block-23 block-24))

(defun gesture-compile-error (text-string)
  (format-when-tracing-in-events-modules "locals: ~s~%" current-gesture-locals)
  #+development
  (loop for b in (verbose-backtrace)
	do
    (format-when-tracing-in-events-modules "~a~%" b))
  (throw :compile-gesture-error text-string))

(defun gesture-value-subtype-p (type potential-subtype)
  (type-specification-subtype-p potential-subtype type))

(defun gesture-local-type-or-error (name)
  (or (cadr (assq name current-gesture-locals))
      (gesture-compile-error
	(tformat-text-string "~a is not defined" name))))

(defun add-gesture-local-or-error (name type arg-or-local)
  (cond
    ((cadr (assq name current-gesture-locals))
     (gesture-compile-error
       (tformat-text-string "~a is defined-twice" name)))
    (t
     (phrase-push (phrase-list name type arg-or-local)
		  current-gesture-locals))))

(defun get-unique-gesture-local-name ()
  (let ((name? (nth (incff current-unique-gesture-local-index)
                    unique-gesture-local-names)))
    (cond (name?
	   name?)
	  (t
	   (setf unique-gesture-local-names
		 (nconc unique-gesture-local-names
			(loop with old-base
				= (length unique-gesture-local-names)
			      for i from 0 below 10
			      collect
			      ;; this does free consing
			      ;; but it is cached and high water marked
			      (intern (format nil "UNIQUE-LOCAL-~s"
					      (+f i old-base))
				      (find-package "AB"))
				using gensym-cons)))
	   (nth current-unique-gesture-local-index
		unique-gesture-local-names)))))

(defun add-generated-local (name type arg-or-local)
  (add-gesture-local-or-error name type arg-or-local)
  (phrase-push (phrase-list name type) current-generated-locals))

(defun-allowing-unwind compile-gesture-definition (parse compiling-for-method-p)
  ;; build up local and type info
  ;;   error if name occurs twice
  (let* ((compile-error? nil)
	 (gesture-name (car parse))
	 (gesture-prototype (cadr parse))
	 (gesture-args (car gesture-prototype))
	 (gesture-returns (cadr gesture-prototype))
	 (gesture-locals
	   (expand-multiple-gesture-locals (caddr parse)))
	 (gesture-body (cadddr parse))
	 (current-gesture-locals nil)
	 (current-generated-locals nil)
	 (current-gesture-returns nil)
	 (current-unique-gesture-local-index -1)
	 (current-gesture-lexical-block-count 0)
	 (currently-compiling-exists-p nil)
	 (currently-compiling-method-p compiling-for-method-p)
	 (current-compilation-args nil)
	 (current-compilation-name nil)
	 compile-result compiled-args
	 compiled-locals compiled-returns compiled-body)
    (with-catch-handlers
	(((:compile-gesture-error) (error-text-string)
	  (setf compile-error? error-text-string)))
      (setf compiled-args (compile-gesture-args gesture-args))
      (setf current-compilation-args gesture-args)
      (setf current-compilation-name gesture-name)
      (setf compiled-returns (compile-gesture-returns gesture-returns))
      (setf compiled-locals (compile-gesture-locals gesture-locals))
      (setf compiled-body
	    (compile-gesture-compound-statement
	      (phrase-list 'compound-statement
			   (nconc
			     current-gesture-local-initializers
			     (cadr gesture-body)
			     (generate-return-statement-if-applicable
			       gesture-returns)))))
      (setf compile-result
	    (phrase-list
	      gesture-name
	      compiled-args
	      compiled-returns
	      (nconc compiled-locals current-generated-locals)
	      compiled-body)))
    (cond
      (compile-error?
       (values nil compile-error?))
      (t
       ;; test the emitter here
       compile-result))))

(defun compile-gesture-args (args)
  (when currently-compiling-method-p
    (unless args
      (gesture-compile-error
	(tformat-text-string "Methods must have at least one argument")))
    (let ((type-of-first-arg (cadr (first args))))
      (unless (class-type-specification-p type-of-first-arg)
	(gesture-compile-error
	  (tformat-text-string
	    "Methods must take an item class for the first argument")))))
  (loop for (name type) in args
	do
    (add-gesture-local-or-error name type 'argument))
  args)

(defun compile-gesture-returns (returns)
  (setf current-gesture-returns returns)
  returns)

(defun expand-multiple-gesture-locals (locals)
  (loop with res = '()
	for local-var-line in locals
	do
    (cond ((eq (car local-var-line) 'multiple-gesture-locals)
	   (loop with type = (caddr local-var-line)
		 for name in (cadr local-var-line)
		 do
	     (phrase-push (phrase-list (phrase-list name type) nil)
			  res)))
	  (t
	   (phrase-push local-var-line res)))
	finally
	  (return (nreverse res))))

(defun compile-gesture-locals (locals)
  (loop with res = '()
	with initializers = '()
	for ((name type) initializer-expression?) in locals
	do
    (format-when-tracing-in-events-modules
      "compile-glocals name=~s type=~s ie?=~s~%"
      name type initializer-expression?)
    (add-gesture-local-or-error name type 'local)
    (phrase-push (phrase-list name type) res)
    (when initializer-expression?
      (phrase-push (phrase-list
		     'assignment name
		     (phrase-list 'initializer-wrapper
				  (phrase-list initializer-expression?)))
		   initializers))
	finally
	  (setf current-gesture-local-initializers
		(nreverse initializers))
	  (return (nreverse res))))

(defvar gesture-fall-through '(fall-through))

(defun generate-return-statement-if-applicable (gesture-returns)
  (declare (ignore gesture-returns))
  (phrase-list (phrase-list 'return (phrase-list gesture-fall-through))))

(defun compile-gesture-compound-statement (compound-statement)
  (let ((protecting-form? (caddr compound-statement)))
    (phrase-list
      (if protecting-form?
	  (if (eq (car protecting-form?) 'on-error)
	      'compound-statement-with-error-handling
	      'compound-statement-with-unwind-protection)
	  'compound-statement)
      (loop for statement in (cadr compound-statement)
	    collect
	    (prog1 
		(compile-gesture-statement statement)
	      (format-when-tracing-in-events-modules
		"just compiled ~s~%" statement))
	      using phrase-cons)
      (and protecting-form?
	   (compile-gesture-statement protecting-form?)))))


(defun cast-compiled-expression (compiled-exp type)
  (multiple-value-bind (type-operator? additional-arg?)
      (get-cast-operator
	(gesture-value-node-type compiled-exp) type)
    (cond ((and additional-arg?
		(eq type-operator? 'value2frame))
	   (make-gesture-value-node
	     '(class item)
	     'value2frame
	     (phrase-list
	       compiled-exp
	       additional-arg?)))
	  (t
	   (make-gesture-value-node
	     type
	     ;; can ignore 2nd ret val here cuz exprs don't return frames
	     (or type-operator?
		 'value2type)
	     (if type-operator?
		 (phrase-list compiled-exp)
		 (phrase-list compiled-exp type)))))))

;; add-to-front
;; add-to-end
;; append-sequences
;; pop-front
;; pop-back
;; subseq
;; change-size ( )


(defun compile-gesture-statement (statement)
  (let ((statement-type (car statement))
	(statement-subforms (cdr statement)))
    (case statement-type
      (assignment
       (let* ((value
		(compile-gesture-expression (second statement-subforms)))
	      (var-name (first statement-subforms))
	      (var-type (gesture-local-type-or-error var-name)))
	 (cond
	   ;; already a good type
	   ((gesture-value-subtype-p
	      var-type (gesture-value-node-type value))
	    (phrase-list 'local-assignment
			 var-name var-type
			 value))
	   ;; a potential type
	   ((gesture-value-subtype-p
	      (gesture-value-node-type value) var-type)
	    (phrase-list 'local-assignment
			 var-name var-type
			 (cast-compiled-expression
			   value var-type)))
	   ;; not a chance to be a compatible type
	   (t
	    (gesture-compile-error
	      (tformat-text-string
		"~a of type ~a is being assigned a value of type ~a"
		var-name var-type (gesture-value-node-type value)))))))
      (change-slot
       (let ((slot-name (first statement-subforms))
	     (structure
	       (compile-gesture-expression (second statement-subforms)))
	     (value
	       (compile-gesture-expression (third statement-subforms))))
;	 (unless (gesture-value-subtype-p
;		   '(class tw-item)
;		   (gesture-value-node-type structure))
;	   (gesture-compile-error
;	     (tformat-text-string
;	       "changing member of something that is not a tw-item")))
	 (phrase-list 'change-slot
		      slot-name
		      (cast-compiled-expression structure '(class item))
		      value)))
      (change-array-length
       (let ((array-exp
	       (compile-gesture-expression (first statement-subforms)))
	     (size-exp
	       (compile-gesture-expression (second statement-subforms))))
	 (unless (eq (gesture-value-node-type size-exp) 'integer)
	   (gesture-compile-error
	     (tformat-text-string "array-length-change must take integer")))		     
	 (phrase-list
	   'change-array-length
	   array-exp
	   size-exp)))
      (if
	(let ((test-value
		 (compile-gesture-expression (first statement-subforms)))
	      (else-clause? (third statement-subforms)))
	  (unless (type-specifications-could-intersect-p
		    'truth-value (gesture-value-node-type test-value))
	    (gesture-compile-error
	      (tformat-text-string "non-truth-value given to if")))
	  (phrase-list 'if
		       (if (eq (gesture-value-node-type test-value) 'truth-value)
			   test-value
			   (cast-compiled-expression test-value 'truth-value))
		       (compile-gesture-statement (second statement-subforms))
		       (and else-clause?
			    (compile-gesture-statement else-clause?)))))
      (for
       (let* ((iteration-spec (first statement-subforms))
	      (for-loop-body (second statement-subforms))
	      (limit-var-name (get-unique-gesture-local-name)))
	 (add-generated-local limit-var-name 'integer 'local)
	 (case (car iteration-spec)
	   (integer-iteration
	    (let* ((var-name (second iteration-spec))
		   (var-type (gesture-local-type-or-error var-name))
		   (initial-value-expression
		     (compile-gesture-expression (third iteration-spec)))
		   (limit-value-expression
		     (compile-gesture-expression (fourth iteration-spec))))
	      (unless (eq var-type 'integer)
		(gesture-compile-error
		  (tformat-text-string
		    "for loop variable ~a must be an integer"
		    var-name)))
	      (unless (gesture-value-subtype-p
			'integer
			(gesture-value-node-type initial-value-expression))
		(gesture-compile-error
		  (tformat-text-string
		    "for loop start value must be an integer")))
	      (unless (gesture-value-subtype-p
			'integer
			(gesture-value-node-type limit-value-expression))
		(pprint-when-tracing-in-events-modules limit-value-expression)
		(gesture-compile-error
		  (tformat-text-string
		    "for loop limit value must be an integer")))
	      (phrase-list 'for-loop-integer
			   var-name
			   limit-var-name
			   initial-value-expression
			   limit-value-expression
			   1 ; increment
			   t ; loop is upward
			   (compile-gesture-statement for-loop-body)))))))
      ((call-gesture call-next-method)
       (let* ((assignment-variable-list (first statement-subforms))
	      (gesture-name (if (eq statement-type 'call-next-method)
				current-compilation-name
				(second statement-subforms)))
	      (gesture-args (if (eq statement-type 'call-next-method)
				(loop for (arg-name nil) in current-compilation-args
				      collect (phrase-list 'local arg-name)
					using phrase-cons)
				(third statement-subforms))))
	 (when (and (eq statement-type 'call-next-method)
		    (not currently-compiling-method-p))
	   (gesture-compile-error
	     (tformat-text-string
	       "Call next method can only be used in methods")))
	 (phrase-list (if (eq statement-type 'call-next-method)
			  'gesture-call-next-method
			  'gesture-call)
		      gesture-name ; this is nil for call next method
		      assignment-variable-list
		      (loop for var in assignment-variable-list
			    collect
			    (gesture-local-type-or-error var)
			      using phrase-cons)
		      (loop for arg in gesture-args
			    collect
			    (compile-gesture-expression arg)
			      using phrase-cons))))
      (call-g2
       (let ((assignment-variable-list (first statement-subforms))
	     (gesture-name (second statement-subforms))
	     (gesture-args (third statement-subforms)))
	 (phrase-list 'call-g2
		      gesture-name
		      assignment-variable-list
		      (loop for var in assignment-variable-list
			    collect
			    (gesture-local-type-or-error var)
			      using phrase-cons)
		      (loop for arg in gesture-args
			    collect
			    (compile-gesture-expression arg)
			      using phrase-cons))))
      (return
	(let ((return-exp-list (first statement-subforms)))
	  (cond
	    ((and (=f (length return-exp-list) 1)
		  (eq (car return-exp-list) gesture-fall-through))
	     (phrase-list 'return nil t))
	    (t
	     (unless (=f (length (first statement-subforms))
			 (length current-gesture-returns))
	       (gesture-compile-error
		 (tformat-text-string
		   "wrong-number of return arguments specified")))
	     (loop with res = '()
		   for exp in (first statement-subforms)
		   for type in current-gesture-returns
		   as value = (compile-gesture-expression exp)
		   do
	       (cond ((gesture-value-subtype-p
			 type (gesture-value-node-type value))
		      ;; do nothing
		      )
		     ((type-specifications-could-intersect-p
			type (gesture-value-node-type value))
		      (setq value (cast-compiled-expression value type)))
		     (t
		      (gesture-compile-error
			(tformat-text-string
			  "returning ~a where expecting ~a in return statement"
			  (gesture-value-node-type value) type))))
	       (phrase-push value res)
		   finally
		     (return (phrase-list 'return
					  (nreverse res)
					  nil)))))))
      (repeat
       (let ((current-gesture-lexical-block-end
	       (nth current-gesture-lexical-block-count
		    gesture-lexical-block-labels)))
	 (incff current-gesture-lexical-block-count)
	 (unless current-gesture-lexical-block-end
	   (error "internal error in compile repeat statement"))
	 (phrase-list 'repeat
		      (compile-gesture-statement (first statement-subforms))
		      current-gesture-lexical-block-end)))
      (case-statement
;       (gesture-compile-error
;	 (tformat-text-string "joe didn't get the case statement right"))
       (let ((case-clauses (cdr statement-subforms))
	     (selector-var-name (get-unique-gesture-local-name)))
	 (loop for clause-tail on case-clauses
	       as (tag-list statement) = (car clause-tail)
	       as otherwise-in-tags-p = (memq 'otherwise tag-list)
	       as len = (length tag-list)
	       do
	   (when (and otherwise-in-tags-p
		      (cdr clause-tail))
	     (gesture-compile-error
		(tformat-text-string
		  "otherwsise can only be used in final case clause")))
	   (when (and otherwise-in-tags-p
		      (>f len 1))
	     (gesture-compile-error
	       (tformat-text-string
		 "otherwise can not be one of a list of case tags"))))
	 (add-generated-local selector-var-name 'datum 'local)
	 (compile-gesture-statement
	   (phrase-list
	    'compound-statement
	    (phrase-list
	      (phrase-list
		'assignment selector-var-name (car statement-subforms))
	      (let ((res 
		      (transform-case-to-if-statements
			selector-var-name case-clauses)))
;		(pprint-when-tracing-in-events-modules res)
		res))))))
      (exit-if
       (unless current-gesture-lexical-block-end
	 (gesture-compile-error
	   (tformat-text-string "no block (e.g. repeat, for, etc) for exit if")))
       (let ((test (compile-gesture-expression (first statement-subforms))))
	 (phrase-list 'exit-if
		      test
		      current-gesture-lexical-block-end)))
      ((on-error on-exit)
       ;; check whether var could intersect with (class tw-error), or item for the while
       (let* ((error-var? (first statement-subforms))
	      (error-var-type (gesture-local-type-or-error error-var?)))
	 (when error-var?
	   (unless (type-specification-subtype-p
		     error-var-type '(class item))
	     (gesture-compile-error
	       (tformat-text-string
		 "on error variable type must be an item class"))))
	 (phrase-list
	   statement-type
	   (and error-var?
		(phrase-list error-var?
			     (gesture-local-type-or-error error-var?)))
		;; here friday , emitting runtime
	                       ; foundation methods and connect/clear/reset
	   (compile-gesture-compound-statement
	     (phrase-list
	       'begin
	       (second statement-subforms))))))
      (create
       (compile-gesture-statement
	 (phrase-list 'assignment
		      (second statement-subforms)
		      (phrase-list
			'new-class-instance
			(phrase-list
			  (phrase-list 'constant (first statement-subforms)))))))
      ((compound-statement begin)
       (compile-gesture-compound-statement statement)))))

(defun transform-case-to-if-statements (selector-var-name case-clauses)
  (let* ((clause (car case-clauses))
	 (clause-tail (cdr case-clauses))
	 (tag-list (car clause))
	 (statement (cadr clause)))
    (cond
      (clause-tail
       (phrase-list
	 'if (make-case-test-expression
	       selector-var-name tag-list)
	 statement
	 (transform-case-to-if-statements selector-var-name clause-tail)))
      ((and (eq (car tag-list) 'otherwise)
	    (null clause-tail))
       statement)
      ((eq (car tag-list) 'otherwise)
       (error "multiple tag otherwise fell through"))
      (t
       (phrase-list
	 'if (make-case-test-expression
	       selector-var-name tag-list)
	 statement
	 nil))))) ; eventually make this a case fall-through error

;; do if-expression AND,OR,>,<,<=,>=, and case

(defun make-case-test-expression (selector-var-name tag-list)
  (phrase-list
    'or
    (loop for tag in tag-list
	  collect (phrase-list
		    '=
		    (phrase-list (phrase-list 'local selector-var-name)
				 (phrase-list 'constant tag)))
	    using phrase-cons)))
		   

(defparameter gesture-expression-compile-table
  (optimize-constant
    '((add
       ((integer integer) -> (integer add-fixnum (arg 1) (arg 2)))
       ((integer float) -> (float add-float (float int2float (arg 1)) (arg 2)))
       ((float integer) -> (float add-float (arg 1) (float int2float (arg 2))))
       ((float float) -> (float add-float (arg 1) (arg 2)))
       ((number number) -> (number add-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (number add-quantity
						 (number value2quantity (arg 1))
						 (number value2quantity (arg 2)))))   
      (subtract
       ((integer integer) -> (integer subtract-fixnum (arg 2) (arg 1)))
       ((integer float) -> (float subtract-float (float int2float (arg 2)) (arg 1)))
       ((float integer) -> (float subtract-float (arg 2) (float int2float (arg 1))))
       ((float float) -> (float subtract-float (arg 2) (arg 1)))
       ((number number) -> (number subtract-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (number subtract-quantity
						 (number value2quantity (arg 1))
						 (number value2quantity (arg 2)))))   
      
      (multiply
       ((integer integer) -> (integer multiply-fixnum (arg 1) (arg 2)))
       ((integer float) -> (float multiply-float (float int2float (arg 1)) (arg 2)))
       ((float integer) -> (float multiply-float (arg 1) (float int2float (arg 2))))
       ((float float) -> (float multiply-float (arg 1) (arg 2)))
       ((number number) -> (number multiply-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (number multiply-quantity
						 (number value2quantity (arg 1))
						 (number value2quantity (arg 2)))))

      (divide
       ((integer integer) -> (integer divide-fixnum (arg 1) (arg 2)))
       ((integer float) -> (float divide-float (float int2float (arg 1)) (arg 2)))
       ((float integer) -> (float divide-float (arg 1) (float int2float (arg 2))))
       ((float float) -> (float divide-float (arg 1) (arg 2)))
       ((number number) -> (number divide-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (number divide-quantity
						 (number value2quantity (arg 1))
						 (number value2quantity (arg 2)))))
      (negate
       ((integer) -> (integer negate-fixnum (arg 1))))
      
      (quotient
       ((integer integer) -> (integer quotient-fixnum (arg 1) (arg 2)))
       ((float integer) -> (float quotient-float (arg 1) (float int2float (arg 2))))
       ((integer float) -> (float quotient-float (float int2float (arg 1)) (arg 2)))
       ((float float) -> (float quotient-float (arg 1) (arg 2)))
       ((number number) -> (number quotient-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (number quotient-quantity
						 (number value2quantity (arg 1))
						 (number value2quantity (arg 2)))))
      (remainder
       ((integer integer) -> (integer remainder-fixnum (arg 1) (arg 2)))
       ((float integer) -> (float remainder-float (arg 1) (float int2float (arg 2))))
       ((integer float) -> (float remainder-float (float int2float (arg 1)) (arg 2)))
       ((float float) -> (float remainder-float (arg 1) (arg 2)))
       ((number number) -> (number remainder-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (number remainder-quantity
						 (number value2quantity (arg 1))
						 (number value2quantity (arg 2)))))
      (bitwise-or
       ((integer integer) -> (integer bitwise-or (arg 1) (arg 2)))
       ((integer item-or-datum) -> (integer bitwise-or
					    (arg 1)
					    (integer value2integer (arg 2))))
       ((item-or-datum integer) -> (integer bitwise-or
					    (integer value2integer (arg 1))
					    (arg 2)))
       ((item-or-datum item-or-datum) -> (integer bitwise-or
						  (integer value2integer (arg 1))
						  (integer value2integer (arg 2)))))
      (bitwise-and
       ((integer integer) -> (integer bitwise-and (arg 1) (arg 2)))
       ((integer item-or-datum) -> (integer bitwise-and
					    (arg 1)
					    (integer value2integer (arg 2))))
       ((item-or-datum integer) -> (integer bitwise-and
					    (integer value2integer (arg 1))
					    (arg 2)))
       ((item-or-datum item-or-datum) -> (integer bitwise-and
						  (integer value2integer (arg 1))
						  (integer value2integer (arg 2)))))
      
      (>
       ((integer integer) -> (truth-value greater-than-fixnum (arg 1) (arg 2)))
       ((integer float) -> (truth-value greater-than-float (float int2float (arg 1)) (arg 2)))
       ((float integer) -> (truth-value greater-than-float (arg 1) (float int2float (arg 2))))
       ((float float) -> (truth-value greater-than-float (arg 1) (arg 2)))
       ((number number) -> (truth-value greater-than-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (truth-value greater-than-quantity
						      (number value2quantity (arg 1))
						      (number value2quantity (arg 2)))))
      (>=
       ((integer integer) -> (truth-value greater-than-equal-fixnum (arg 1) (arg 2)))
       ((integer float) ->
	(truth-value greater-than-equal-float (float int2float (arg 1)) (arg 2)))
       ((float integer) ->
	(truth-value greater-than-equal-float (arg 1) (float int2float (arg 2))))
       ((float float) -> (truth-value greater-than-equal-float (arg 1) (arg 2)))
       ((number number) -> (truth-value greater-than-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (truth-value greater-than-equal-quantity
						      (number value2quantity (arg 1))
						      (number value2quantity (arg 2)))))
      (<
       ((integer integer) -> (truth-value less-than-fixnum (arg 1) (arg 2)))
       ((integer float) -> (truth-value less-than-float (float int2float (arg 1)) (arg 2)))
       ((float integer) -> (truth-value less-than-float (arg 1) (float int2float (arg 2))))
       ((float float) -> (truth-value less-than-float (arg 1) (arg 2)))
       ((number number) -> (truth-value less-than-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (truth-value less-than-quantity
						      (number value2quantity (arg 1))
						      (number value2quantity (arg 2)))))
      (<=
       ((integer integer) -> (truth-value less-than-equal-fixnum (arg 1) (arg 2)))
       ((integer float) -> (truth-value less-than-equal-float (float int2float (arg 1))
					(arg 2)))
       ((float integer) -> (truth-value less-than-equal-float (arg 1)
					(float int2float (arg 2))))
       ((float float) -> (truth-value less-than-equal-float (arg 1) (arg 2)))
       ((number number) -> (truth-value less-than-equal-quantity (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) -> (truth-value less-than-equal-quantity
						      (number value2quantity (arg 1))
						      (number value2quantity (arg 2)))))
      (equal
       ((text text) -> (truth-value equal-text (arg 1) (arg 2)))
       ((integer integer) -> (truth-value equal-fixnum (arg 1) (arg 2)))
       ((integer float) ->
	(truth-value equal-float (float int2float (arg 1)) (arg 2)))
       ((float integer) ->
	(truth-value equal-float (arg 1) (float int2float (arg 2))))
       ((float float) -> (truth-value equal-float (arg 1) (arg 2)))
       ((number number) -> (truth-value equal-quantity (arg 1) (arg 2)))
       ((symbol symbol) -> (truth-value equal-symbol (arg 1) (arg 2)))
       ;; datum poisons efficiency because eval. cannot error if wrong type
       ;; need float and quantity cases here
       ((item-or-datum item-or-datum) -> (truth-value equal-datum
						      (datum value2datum (arg 1))
						      (datum value2datum (arg 2)))))
      (sequence-length
       (((sequence)) -> (integer sequence-length (arg 1)))
       ((item-or-datum) -> (integer sequence-length
				    ((sequence) value2sequence (arg 1)))))
      (nth-element
       (((sequence) integer) -> (datum nth-sequence-element (arg 1) (arg 2)))
       ((item-or-datum integer) -> (datum nth-sequence-element
					  ((sequence) value2sequence (arg 1)) (arg 2)))
       (((sequence) item-or-datum) -> (datum nth-sequence-element (arg 1)
					     (integer value2integer (arg 2))))
       ((item-or-datum item-or-datum) -> (datum nth-sequence-element
						((sequence) value2sequence (arg 1))
						(integer value2integer (arg 2)))))
      (set-nth-sequence-element
       (((sequence) integer item-or-datum) ->
	((sequence) set-nth-sequence-element (arg 1) (arg 2) (arg 3)))
       ((item-or-datum integer item-or-datum) ->
	((sequence) set-nth-sequence-element
	 ((sequence) value2sequence (arg 1)) (arg 2) (arg 3)))
       ((item-or-datum item-or-datum item-or-datum) ->
	((sequence) value2sequence (arg 1)) (integer value2integer (arg 2)) (arg 3)))

      (sequence-push
       (((sequence) item-or-datum) -> ((sequence) sequence-push (arg 1) (arg 2) (arg 3)))
       ((item-or-datum item-or-datum) ->
	((sequence) sequence-push ((sequence) value2sequence (arg 1)) (arg 2) (arg 3))))

      (sequence-remove-element
       (((sequence) item-or-datum) -> ((sequence) sequence-remove-element (arg 1) (arg 2)))
       ((item-or-datum item-or-datum) ->
	((sequence) sequence-remove-element ((sequence) value2sequence (arg 1)) (arg 2))))
      
      (set-structure-slot
       (((structure) symbol item-or-datum) ->
	((structure) set-structure-slot (arg 1) (arg 2) (arg 3)))
       (((structure) item-or-datum item-or-datum) ->
	((structure) set-structure-slot (arg 1) (symbol value2symbol (arg 2)) (arg 3)))
       ((item-or-datum item-or-datum item-or-datum) ->
	((structure) set-structure-slot
	 ((structure) value2struct (arg 1))
	 (symbol value2symbol (arg 2))
	 (arg 3))))
      
      )))

(defun compile-gesture-expression-by-table (operator operands)
  
  (let ((table-for-op (cdr (assq operator gesture-expression-compile-table)))
	(compiled-operands
	  (loop for operand in operands
		collect
		(compile-gesture-expression operand)
		using phrase-cons)))
;    (format-when-tracing-in-events-modules
;      "op=~s rands=~s ~%table-for-op =~s~%"
;      operator operands table-for-op)
    (unless (=f (length operands)
		(length (cddr (caddar table-for-op)))) ; god save me!
;      (format-when-tracing-in-events-modules "the cddr of ~s~%"
;	(caddar table-for-op))
      (gesture-compile-error
	 (tformat-text-string "wrong number of args to ~a" operator)))
    (loop for (type-pattern ignore replacement) in table-for-op
	  when (gesture-expression-operands-match-pattern-p
		 compiled-operands type-pattern)
	    do
	      (return (make-replacement-gesture-expression
			compiled-operands replacement))
	  finally
	    (gesture-compile-error
	      (tformat-text-string "bad argument types for ~a" operator)))))

(defun gesture-expression-operands-match-pattern-p (operands pattern)
  (loop for pattern-element-type in pattern
	as operand in operands
	as operand-type = (gesture-value-node-type operand)
	do
    (unless (or (eq (car operand) 'unevaluated-constant)
		(gesture-value-subtype-p pattern-element-type operand-type))
      (return nil))
	finally
	  (return t)))

(defun make-replacement-gesture-expression (operands template)
  (let ((type (gesture-value-node-type template))
	(operation (gesture-value-node-operation template))
	(template-args (gesture-value-node-args template))
	replacement-args)
    (loop for template-arg in template-args
	  do
      (phrase-push
	(cond ((and (consp template-arg)
		    (eq (car template-arg) 'arg))
	       (nth (1-f (cadr template-arg)) operands))
	      (t
	       (make-replacement-gesture-expression operands template-arg)))
	replacement-args))
    (make-gesture-value-node
      type operation (nreverse replacement-args))))

(defun combine-types-for-gesture-if-expression (then-type else-type)
  (case then-type
    (integer
     (case else-type
       (integer 'integer)
       ((float quantity) 'quantity)
       (otherwise 'datum)))
    (float
     (case else-type
       (float 'float)
       ((integer quantity) 'quantity)
       (otherwise 'datum)))
    (quantity
     (case else-type
       ((integer float quantity) 'quantity)
       (otherwise 'datum)))
    (otherwise
     (if (eq then-type else-type)
	 then-type
	'datum))))

;;; `compile-gesture-expression' is the main routine for compiling gesture/NTW
;;; expressions within tw-procedures.  It is responible for filtering expression
;;; constructs that are supported in G2 but not in NTW.  It will generate
;;; compile-time (under the red line in classic G2 UI) errors if it sees anything
;;; NTW cannot handle.  It supports logical expressions based on an if-expression
;;; and macros (AND , OR) that expand into it. Aside from that it is pretty straight
;;; forward.  It produces a phrase-cons tree of "gesture-value-nodes" which
;;; are structure conses that represent a completely type-checked computation.
;;; The necessary casts are added or an error is signalled at compile time
;;; if no cast could possibly allow the expression to run.  (the latter is not
;;; yet completely implemented.  The unwinding of the expression tree into
;;; a linear instruction stream is left for the code emitter.  All cleverness
;;; is implemented here regarding type-specific optimizations.  The emitter
;;; just does grunt work.

(defun compile-gesture-expression (exp)
  (let ((operator (car exp))
	(operands (cadr exp)))
    (case operator
      (unevaluated-constant
       exp)
      ((add +)
       (compile-gesture-expression-by-table 'add operands))
      ((subtract -)
       (compile-gesture-expression-by-table 'subtract operands))
      ((multiply *)
       (compile-gesture-expression-by-table 'multiply operands))
      (negate
       (compile-gesture-expression-by-table 'negate operands))
      (quotient
       (compile-gesture-expression-by-table 'quotient operands))
      (remainder
       (compile-gesture-expression-by-table 'remainder operands))
      ((divide /)
       (compile-gesture-expression-by-table 'divide operands))
      ((> >= < <=)
       (compile-gesture-expression-by-table operator operands))
      ((equal =)
       (compile-gesture-expression-by-table 'equal operands))
      ((bitwise-or bitwise-and)
       (compile-gesture-expression-by-table operator operands))
      ((g2-list-or-sequence-length)
       (compile-gesture-expression-by-table 'sequence-length operands))
      ((nth-element)
       (compile-gesture-expression-by-table 'nth-element operands))
      (set-sequence-element
       (compile-gesture-expression-by-table 'set-nth-sequence-element operands))
      ((set-structure-attribute set-struct-attribute)
       (compile-gesture-expression-by-table 'set-structure-slot operands))
      (sequence-remove-element
       (compile-gesture-expression-by-table 'sequence-remove-element operands))
      (sequence-add-first  
       (compile-gesture-expression-by-table
	 'sequence-push
	 (nconc (copy-for-phrase operands)
		(phrase-list '(unevaluated-constant first)))))
      (sequence-add-last
       (compile-gesture-expression-by-table
	 'sequence-push
	 (nconc (copy-for-phrase operands)
		(phrase-list '(unevaluated-constant last)))))
      (if-expression
       (let* ((compiled-condition
		(compile-gesture-expression (car operands)))
	      (then-expression (cadr operands))
	      (compiled-then-expression
		(compile-gesture-expression then-expression))
	      (else-expression? (caddr operands))
	      (compiled-else-expression
		(and else-expression?
		     (compile-gesture-expression else-expression?))))
	 (unless (type-specifications-could-intersect-p
		   'truth-value (gesture-value-node-type compiled-condition))
	   (gesture-compile-error
	     (tformat-text-string "non-truth-value given to if")))
	 (cond
	   (else-expression?
	    (make-gesture-value-node
	      (combine-types-for-gesture-if-expression 
		(gesture-value-node-type compiled-then-expression)
		(gesture-value-node-type compiled-else-expression))
	      'if-expression
	      (phrase-list
		(if (eq (gesture-value-node-type compiled-condition) 'truth-value)
		    compiled-condition
		    (cast-compiled-expression compiled-condition 'truth-value))
		compiled-then-expression
		compiled-else-expression)))
	   (t
	    (gesture-compile-error
	      (tformat-text-string "(if ...) expressions must have an else clause"))))))
;	    (make-gesture-value-node
;	      'datum
;	      'if-expression
;	      (phrase-list
;		compiled-condition
;		compiled-then-expression
;		(make-gesture-value-node 'value 'push-unknown nil)))
      (get-slot
       (let* ((slot-name (compile-gesture-expression (car operands)))
	      (structure (compile-gesture-expression (cadr operands)))
	      (structure-type (gesture-value-node-type structure)))
	 (unless (or (type-specifications-could-intersect-p
		       structure-type '(structure))
		     (type-specifications-could-intersect-p
		       structure-type '(class item)))
	   (gesture-compile-error
	     (tformat-text-string
	       "Attribute access to non-(tw)item")))
	 (unless (and (eq (gesture-value-node-type slot-name) 'symbol)
		      (eq (gesture-value-node-operation slot-name)
			  'symbol-constant))
	    (gesture-compile-error
	     (tformat-text-string
	       "evaluated slot names not yet supported")))
	 (cond
	   ((and (constant-symbol-value-node-of-symbol-p slot-name 'array-length)
		 t)
	    ;; this is a hack until we do v-a's for real...
	    (make-gesture-value-node
	      'integer
	      'array-length
	      (phrase-list
		(if (or (type-specification-subtype-p structure-type '(structure))
			(type-specification-subtype-p structure-type '(class item)))
		    structure
		    (cast-compiled-expression structure 
					      '(or (structure) (class item)))))))
	   (t
	    (make-gesture-value-node
	      'item-or-datum
	      (if currently-compiling-exists-p
		  'get-slot-or-no-item
		  'get-slot)
	      (phrase-list
		(if (or (type-specification-subtype-p structure-type '(structure))
			(type-specification-subtype-p structure-type '(class item)))
		    structure
		    (cast-compiled-expression structure 
					      '(or (structure) (class item))))
		slot-name))))))
      (constant
       (let ((value-exp operands))
	 (cond
	   ((fixnump value-exp)
	    (make-gesture-value-node
	      'integer 'integer-constant (phrase-list value-exp)))
	   ((phrase-float-p value-exp)
	    (make-gesture-value-node
	      'float 'float-constant (phrase-list value-exp)))
	   ((phrase-long-p value-exp)
	    (make-gesture-value-node
	      'long 'long-constant (phrase-list value-exp)))
	   ((or (eq value-exp 'true)
		(eq value-exp 'false))
	    (make-gesture-value-node
	      'truth-value 'truth-value-constant (phrase-list value-exp)))
	   ((symbolp value-exp)
	    (make-gesture-value-node
	      'symbol 'symbol-constant (phrase-list value-exp)))
	   ((text-string-p value-exp)
	    (make-gesture-value-node
	      'text 'text-constant (phrase-list value-exp)))
	   (t
	    (gesture-compile-error
	      (tformat-text-string "unrecognized gesture-constant ~a"
				   value-exp))))))
      (local
       (let ((local-name operands))
	 (make-gesture-value-node
	   (gesture-local-type-or-error local-name)
	   (if currently-compiling-exists-p
	       'fetch-local-or-no-item
	       'fetch-local)
	   (phrase-list local-name))))
      (format-form
       (make-gesture-value-node
	 'text
	 'tw-format-form
	 (loop with compiled-operands =
	       (phrase-list (compile-gesture-expression
			      (phrase-list 'constant (length operands))))
	       for operand in operands
	       do
		(phrase-push (compile-gesture-expression operand)
			     compiled-operands)
	       finally
		 (return compiled-operands))))
      (sequence
       (make-gesture-value-node
	 '(sequence)
	 'make-sequence
	 (nconc
	   (loop for operand in operands
		 collect (compile-gesture-expression operand)
		   using phrase-cons)
	   (phrase-list
	     (make-gesture-value-node
	       'integer 'integer-constant (phrase-list (length operands)))))))
      ((structure evaluated-structure)
       (when (oddp (length operands))
	 (gesture-compile-error
	   (tformat-text-string
	     "structure must have even number of args")))
       (make-gesture-value-node 
	 '(structure)
	 'make-structure
	 (nconc
	   (loop for operand in operands
		 collect (compile-gesture-expression operand)
		   using phrase-cons)
	   (phrase-list
	     (make-gesture-value-node
	       'integer 'integer-constant (phrase-list (length operands)))))))
      (exists
       (let ((currently-compiling-exists-p t))
	 (make-gesture-value-node
	   'truth-value
	   'exists
	   (phrase-list
	     (compile-gesture-expression (car operands))))))
      (is
       (let ((thing (car operands))
	     (constant-thing? (cadr operands)))
	 (cond ((eq (car constant-thing?) 'constant)
		(compile-gesture-expression
		  (phrase-list '=
			       (phrase-list thing constant-thing?))))
	       (t
		(gesture-compile-error
		  (tformat-text-string "illegal is expression"))))))
      (is-of-class
       (let ((thing-expression (car operands))
	     (type-specification-expression (cadr operands)))
	 (cond
	   ((and (consp type-specification-expression)
		 (eq (car type-specification-expression) 'constant))
	    (let* ((type-or-class (cadr type-specification-expression))
		   (internal-type-specification?
		     (type-specification-for-user-type type-or-class)))
	      (cond (internal-type-specification? 
		     (make-gesture-value-node
		       'truth-value
		       'type-test
		       (phrase-list
			 (compile-gesture-expression thing-expression)
			 internal-type-specification?)))
		    (t
		     (make-gesture-value-node
		       'truth-value
		       'class-test
		       (phrase-list
			 (compile-gesture-expression thing-expression)
			 (make-gesture-value-node
			   'symbol
			   'symbol-constant 
			   (phrase-list type-or-class))))))))
	   (t
	    (make-gesture-value-node
	      'truth-value
	      'class-test
	      (phrase-list
		(compile-gesture-expression thing-expression)
		(compile-gesture-expression type-specification-expression)))))))
      (and
       (compile-gesture-expression
	 (transform-and-to-if-expression operands)))
      (or
      (compile-gesture-expression
	 (let ((res
		 (transform-or-to-if-expression operands)))
;	   (pprint-when-tracing-in-events-modules res)
	   res)))
      (not
       (make-gesture-value-node
	 'truth-value
	 'invert-truth-value
	 (phrase-list (compile-gesture-expression (car operands)))))
      (initializer-wrapper
       (let ((currently-compiling-local-variables-p t))
	 (compile-gesture-expression (car operands))))
      ((class find-java-class)
       (unless currently-compiling-local-variables-p
	 (gesture-compile-error
	   (tformat-text-string
	     "class(<class-name>) only allowed at top level of variable initializer")))
       (when (cdr operands)
	 (gesture-compile-error
	   "class(<class-name>) takes one arg"))
       (let* ((name-expression (car operands))
	      (currently-compiling-local-variables-p nil)
	      (compiled-name-expression
		(compile-gesture-expression name-expression)))
	 (unless (eq (gesture-value-node-operation
		       compiled-name-expression)
		     (if (eq operator 'class)
			 'symbol-constant
			 'text-constant))
	   (gesture-compile-error 
	     (tformat-text-string
	       "class(<class-name>) must take a constant class name")))
	 (make-gesture-value-node
	   (phrase-list 'class 'class-definition)
	   'get-class
	   (phrase-list compiled-name-expression))))
      (new-class-instance
       (let* ((arg (car operands))
	      (compiled-arg (compile-gesture-expression arg)))
	 (unless (eq (gesture-value-node-operation compiled-arg)
		     'symbol-constant)
	   (error "internal screw-up"))
      	 (make-gesture-value-node
	   (phrase-list 'class (car (gesture-value-node-args compiled-arg)))
	   'new-class-instance
	   (phrase-list compiled-arg))))
      (array-length
       (make-gesture-value-node
	 'integer
	 'array-length
	 (phrase-list
	   (compile-gesture-expression (car operands)))))
      (otherwise
       (gesture-compile-error
	 (tformat-text-string
	   "unrecognized gesture-expression ~a" exp))))))

(defun transform-and-to-if-expression (conjuncts)
  (cond ((cdr conjuncts)
	 (phrase-list
	   'if-expression
	   (phrase-list
	     (car conjuncts)
	     (transform-and-to-if-expression (cdr conjuncts))
	     (phrase-list 'constant 'false))))
	(t
	 (phrase-list
	   'if-expression
	   (phrase-list
	     (car conjuncts)
	     (phrase-list 'constant 'true)
	     (phrase-list 'constant 'false))))))

(defun transform-or-to-if-expression (disjuncts)
  (cond ((cdr disjuncts)
	 (phrase-list
	   'if-expression
	   (phrase-list
	     (car disjuncts)
	     (phrase-list 'constant 'true)
	     (transform-or-to-if-expression (cdr disjuncts)))))
	(t
	 (phrase-list
	   'if-expression
	   (phrase-list
	     (car disjuncts)
	     (phrase-list 'constant 'true)
	     (phrase-list 'constant 'false))))))

;;; `unique-expression-to-gesture-expression' takes an s-expression produced by
;;; the parse of the category unique-expression (or logical-expression) and
;;; turns it into something that is syntactically acceptable to the gesture
;;; (NTW) compiler.  This function does not have the responsibility of filtering
;;; expressions that can be handled by G2 but not by NTW.  This is performed
;;; implicitly by the fall-through case in compile-gesture-expression.

(defun unique-expression-to-gesture-expression (exp)
  (cond
    ((or (eq exp 'true)
	 (eq exp 'false)
	 (text-string-p exp)
	 (managed-float-p exp)
	 (fixnump exp))
     (phrase-list 'constant exp))
    ((symbolp exp)
     (phrase-list 'local exp))
    ((atom exp)
     (phrase-list 'error "unsupported gesture expression"))
    (t
     (case (car exp)
       (quote
	(cond ((symbolp (cadr exp))
	       (phrase-list 'constant (cadr exp)))
	      ((valid-type-specification-p (cadr exp))
	       (phrase-list 'constant (cadr exp)))
	      (t
	       (phrase-list 'error "strange quoted thing"))))
       (the
	(cond ((and (symbolp (cadr exp))
		    (caddr exp)
		    (null (cdddr exp)))
	       (phrase-list
		 'get-slot
		 (phrase-list
		   (phrase-list 'constant (cadr exp))
		   (unique-expression-to-gesture-expression (caddr exp)))))
	      ((equal (cadr exp)
		      '(system-attribute array-length integer))
	       (phrase-list
		 'array-length
		 (phrase-list
		   (unique-expression-to-gesture-expression (caddr exp)))))
	      ((and (consp (cadr exp))
		    (eq (caadr exp) 'nth-element))
	       (let ((nth-element-role (cadr exp)))
		 (cond ((eq (cadr nth-element-role) 'item-or-datum)
			(phrase-list
			  'nth-element
			  (phrase-list
			    (unique-expression-to-gesture-expression (third exp))
			    (unique-expression-to-gesture-expression (fourth exp)))))
		       (t
			(error "Unknown nth-element role variation")))))
	      (t
	       (phrase-list 'error "unsupported gesture expression"))))
       (call-function
	(phrase-list
	  (cadr exp)
	  (loop for arg in (cddr exp)
		collect (unique-expression-to-gesture-expression arg)
		using phrase-cons)))
       (otherwise
	(phrase-list
	  (car exp)
	  (loop for arg in (cdr exp)
		collect (unique-expression-to-gesture-expression arg)
		  using phrase-cons)))))))


(defun make-attribute-entry-pairs-from-managed-array (managed-array)
  (loop with result = nil
	with length = (+f 1 (aref managed-array 1))
	for i from 2 to length 
	as attribute-value-or-name = (aref managed-array i)
	do
    (cond ((evenp i)
	   (gensym-push (gensym-list
			  attribute-value-or-name)
			result))
	  (t
	   (gensym-push attribute-value-or-name
			(cdar result))))
	finally
	  (return (nreverse result))))


(defun make-attribute-precedence-list-from-managed-array
    (managed-array)
  (loop with result = nil
	with length = (+f  1 (aref managed-array 1))
	for i from 2 to  length  
	as attribute-name = (aref managed-array i)
	do
    (gensym-push attribute-name result)
	finally
	  (return (nreverse result))))




;;;; Dispatch Tables

(add-grammar-rules
  '((tw-dispatch-spec tw-dispatch-spec-entry (1))
    (tw-dispatch-spec
     (tw-dispatch-spec-entry '\; tw-dispatch-spec)
     (1 . 3))
    
    (tw-dispatch-spec-entry
      ('when 'in tw-dispatch-user-mode-list 'mode '\:
	     tw-dispatch-message-entry-list)
     (1 3 6))
    (tw-dispatch-spec-entry
     ('unless 'in tw-dispatch-user-mode-list 'mode '\:
	      tw-dispatch-message-entry-list)
     (1 3 6))
    (tw-dispatch-user-mode-list
     unreserved-symbol (1))
    (tw-dispatch-user-mode-list
     (unreserved-symbol 'or unreserved-symbol)
     (1 3))
    (tw-dispatch-user-mode-list
     tw-dispatch-user-mode-series)
    (tw-dispatch-user-mode-series
     (unreserved-symbol '\, unreserved-symbol '\, 'or unreserved-symbol)
     (1 3 6))
    (tw-dispatch-user-mode-series
     (unreserved-symbol '\, tw-dispatch-user-mode-series)
     (1 . 3))

    (tw-dispatch-message-entry-list
     tw-dispatch-message-entry (1))
    (tw-dispatch-message-entry-list
     (tw-dispatch-message-entry '\; tw-dispatch-message-entry-list)
     (1 . 3))
    
    (tw-dispatch-message-entry
     ('whenever 'the 'item 'receives
      a-or-an unreserved-symbol
      'then tw-dispatch-action)
     (6 nil 8))
    (tw-dispatch-message-entry
     ('whenever 'the 'item 'receives
      a-or-an unreserved-symbol 'in 
      'which tw-dispatch-attribute-spec
      'then tw-dispatch-action)
     (6 9 11)) 

    (tw-dispatch-attribute-spec
     tw-dispatch-attribute-entry (1))
    (tw-dispatch-attribute-spec
     (tw-dispatch-attribute-entry 'and tw-dispatch-attribute-spec)
     (1 . 3))
    (tw-dispatch-attribute-entry
     ('the unreserved-symbol 'is tw-attribute-value-constant)
     (attribute-equality 2 4))
    (tw-attribute-value-constant integer)
    (tw-attribute-value-constant
     ('the 'symbol unreserved-symbol)
     3)
    (tw-attribute-value-constant
     whole-string 1)
    (tw-dispatch-action
     ('call unreserved-symbol '\( tw-dispatch-action-arg-list '\) 'in 'tw)
     (call-in-tw 2 4))
    (tw-dispatch-action-arg-list
     tw-dispatch-action-arg (1))
    (tw-dispatch-action-arg-list
     (tw-dispatch-action-arg '\, tw-dispatch-action-arg-list)
     (1 . 3))
    (tw-dispatch-action-arg
     ('the 'symbol unreserved-symbol) 3)
    (tw-dispatch-action-arg
     'message )
    (tw-dispatch-action-arg
     'recipient )
    (tw-dispatch-action-arg
     whole-string)
    (tw-dispatch-action-arg
     number)))


(add-grammar-rules
  '((tw-attribute-name-list unreserved-symbol (1))
    (tw-attribute-name-list 'none)
    (tw-attribute-name-list
     (unreserved-symbol '\, tw-attribute-name-list)
     (1 . 3))))

(def-slot-value-compiler tw-attribute-name-list (parse-result tw-dispatch-table)
  (declare (ignore tw-dispatch-table))
  (cond
    ((eq parse-result 'none)
     nil)
    ((loop for tail on parse-result
	   thereis (memq (car tail) (cdr tail)))
     (values bad-phrase
	     (copy-constant-wide-string #w"Duplicate attributes not permitted")))
    (t
     parse-result)))

(def-slot-value-writer tw-attribute-name-list (slot-value)
  (cond
    (slot-value
     (loop for tail on slot-value
	   as name = (car tail)
	   do
       (twrite name)
       (when (cdr tail)
	 (twrite-string ", "))))
    (t
     (twrite-string "none"))))


) ; end of #+gesture-definition-facilities


;;;; API Stuff


#+development
(defun-system-rpc (g2-api-bogus-1 (integer integer))
    ((rpc-instance system-rpc-instance)
     (a1 integer)
     (a2 integer)
     (a3 integer))
  (format-when-tracing-in-events-modules "g2-api-bogus-1 ~s ~s ~s~%" a1 a2 a3)
  (return-from-system-defined-rpc rpc-instance (eval-list 5 6)))

#+development
(defun-system-rpc (g2-api-bogus-2 (datum datum))
    ((rpc-instance system-rpc-instance)
     (a1 integer)
     (a2 integer)
     (a3 integer))
  (format-when-tracing-in-events-modules "g2-api-bogus-1 ~s ~s ~s~%" a1 a2 a3)
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list
      (allocate-evaluation-structure (eval-list 'X 21 'Y 23))
      (allocate-evaluation-structure (eval-list 'HEIGHT 90 'WIDTH 60)))))

#+development
(defun-system-rpc (g2-api-bogus-3 (datum datum))
    ((rpc-instance system-rpc-instance)
     (a1 integer)
     (a2 integer)
     (a3 integer))
  (format-when-tracing-in-events-modules "g2-api-bogus-1 ~s ~s ~s~%" a1 a2 a3)
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list
      (allocate-evaluation-sequence (copy-list-using-eval-conses '(X 21 Y 23)))
      (allocate-evaluation-sequence (copy-list-using-eval-conses '(HEIGHT 90 WIDTH 60))))))

#+development
(defun-system-rpc (g2-describe-item (integer))
    ((rpc-instance system-rpc-instance)
     (frame? (class item)))
  frame?
  #+development
  (format-when-tracing-in-events-modules "g2-describe-item ~s~%"
    (describe frame?))
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list 221)))


(defun get-text-of-attribute (item pretty-slot-name class-if-specific)
  (unless (symbolp class-if-specific)
    (setf class-if-specific nil))
  (let* ((real-slot-name
	   (or (get-slot-name-for-alias-if-any pretty-slot-name item)
	       pretty-slot-name))
	 (slot-description?
	   (get-slot-description-of-frame
	     real-slot-name item class-if-specific)))
    (cond
      (slot-description?
       (make-text-string-representation-for-slot-value-itself
	 item
	 (get-slot-description-value item slot-description?)
	 (get-type-of-slot-if-any
	   item real-slot-name class-if-specific)))
      (t 'no-slot-description-error))))
      
(defun-system-rpc (g2-get-text-of-attribute (datum))
    ((rpc-instance system-rpc-instance)
     (item (class item)) 
     (pretty-slot-name symbol)
     (class-if-specific datum))
  (let ((text-or-error
	  (get-text-of-attribute item pretty-slot-name class-if-specific)))
    (cond ((eq text-or-error 'no-slot-description-error)
	   (system-rpc-error
	     rpc-instance
	     'undefined-attribute-for-class
	     (tformat-text-string "attribute not defined ~NQ"
				  pretty-slot-name class-if-specific)))
	  (t
	   (return-from-system-defined-rpc rpc-instance
					   (eval-list text-or-error))))))

;; here symbol -> attribute-denotation
;; get-from-item internals in conclude.lisp

(defun system-rpc-access-error (rpc-instance access-error)
  (system-rpc-error
    rpc-instance
    (access-error-name access-error)
    (make-default-text-string-for-access-error
      access-error)))

(defun jv-get-icon-description-defined-by-class (class-description)
  (call-category-getter-fn
    (slot-value-to-evaluation-value-function
      'icon-description?)
    (let ((slot-init-form
	    (and class-description
		 (or (memq 'icon-description (slots-local-to-class class-description))
		     (memq 'icon-description (inherited-slots-this-class-overrides
					       class-description)))
		 (let ((slot-description		       
			 (get-slot-description-of-class-description
			   'icon-description class-description)))
		   (and slot-description
			(slot-init-form slot-description))))))
      (and slot-init-form
	   (let ((line-drawing-description
		   (copy-tree-using-gensym-conses  ; BUG need including-leaves
		     (icon-line-drawing-description slot-init-form))))
	     (setf line-drawing-description
		   (gensym-push
		     (height-of-icon slot-init-form)
		     line-drawing-description))
	     (gensym-push (width-of-icon slot-init-form)
			  line-drawing-description))))
    nil nil))


#+development
(defun jv-get-cross-section-pattern-defined-by-class (class-description)
  (call-category-getter-fn
    (slot-value-to-evaluation-value-function
      'cross-section-pattern)
    (let ((slot-init-form
	    (and class-description
		 (or (memq 'cross-section-pattern (slots-local-to-class class-description))
		     (memq 'cross-section-pattern (inherited-slots-this-class-overrides
						    class-description)))
		 (let ((slot-description		       
			 (get-slot-description-of-class-description
			   'cross-section-pattern class-description)))
		   (and slot-description
			(slot-init-form slot-description))))))
      (and slot-init-form
	   (copy-tree-using-gensym-conses slot-init-form)))
    nil nil))







(def-structure (pseudo-attribute
		 (:constructor make-pseudo-attribute
			       (pseudo-attribute-name)))
  (pseudo-attribute-name nil)
  (pseudo-attribute-type-description nil)
  (pseudo-attribute-defining-class nil)
  (pseudo-attribute-getter nil))

(def-global-property-name pseudo-attribute)

(defvar static-attributes nil)
(defvar class-info-attributes nil)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant class-info-key 'PART-OF-CLASS-INFO))

(defmacro no-such-class-error () ''NO-SUCH-CLASS-ERROR)
(defmacro pseudo-attribute-special-key-p (symbol)
  `(memq ,symbol '(,class-info-key)))

;;; `def-pseudo-attribute'
(defmacro def-pseudo-attribute (attribute-name (defining-class category-name-or-type-description)
					       &body body)
  (let ((getter-name (build-ab-symbol attribute-name 'pseudo-attribute-getter)))
    `(progn
       (declare-funcallable-symbol ,getter-name)
       (defun ,getter-name (class-name) ,@body)
       (add-pseudo-attribute
	 ',attribute-name
	 ',defining-class
	 ',getter-name
	 ',category-name-or-type-description))))

(defun add-pseudo-attribute (attribute-name defining-class getter-name category-name-or-type-description)
  (let ((pseudo-attribute-structure (make-pseudo-attribute attribute-name)))
    (cond ((and (pseudo-attribute-special-key-p defining-class)
		(eq defining-class class-info-key))
	   (gensym-pushnew attribute-name class-info-attributes))
	  (t
	   (gensym-pushnew attribute-name static-attributes)))
    (setf (pseudo-attribute-getter pseudo-attribute-structure) getter-name)
    (cond ((symbolp category-name-or-type-description)
	   (setf (pseudo-attribute-type-description pseudo-attribute-structure)
		 (type-specification-explicit-complex-type
		   category-name-or-type-description)))
	  (t
	   (setf (pseudo-attribute-type-description pseudo-attribute-structure)
		 category-name-or-type-description)))
    (setf (pseudo-attribute-defining-class pseudo-attribute-structure) defining-class)
    (setf (pseudo-attribute attribute-name) pseudo-attribute-structure)))

(def-pseudo-attribute class-name (PART-OF-CLASS-INFO symbol)
    class-name)

(def-pseudo-attribute is-system-defined (PART-OF-CLASS-INFO symbol)
  (copy-evaluation-truth-value
    (if (system-defined-class-p class-name)
	evaluation-true-value
	evaluation-false-value)))

(def-pseudo-attribute direct-superior-classes 
    (PART-OF-CLASS-INFO (sequence (symbol) 0))
  (allocate-evaluation-sequence
    (loop for class in (direct-superior-classes class-name)
	  collect (if reference-class-info-p
		      (class-description class)
		      class)
	    using eval-cons)))

(def-pseudo-attribute class-inheritance-path ;CLASS-INFO-KEY
    (PART-OF-CLASS-INFO (sequence (symbol) 0))
  (allocate-evaluation-sequence
    (loop for class in (class-inheritance-path (class-description class-name))
	  collect (if reference-class-info-p
		      (class-description class)
		      class)
	    using eval-cons)))

(def-pseudo-attribute instantiate (block truth-value);CLASS-INFO-KEY
    (let ((class-features
	    (class-features (class-description class-name))))
      (cond ((and (class-description-of-class-p (class-description class-name) 'item)
		  (null (feature-assq-macro 'not-user-instantiable class-features))
		  (null (feature-assq-macro 'not-solely-instantiable class-features)))
	     (copy-evaluation-truth-value evaluation-true-value))
	    (t
	     (copy-evaluation-truth-value evaluation-false-value)))))

(def-pseudo-attribute include-in-menus (block truth-value);CLASS-INFO-KEY
    (let ((class-features
	    (class-features (class-description class-name))))
      (cond ((and (class-description-of-class-p (class-description class-name) 'item)
		  (null (feature-assq-macro 'not-user-instantiable class-features)))
	     (copy-evaluation-truth-value evaluation-true-value))
	    (t
	     (copy-evaluation-truth-value evaluation-false-value)))))

(def-pseudo-attribute icon-description
    (entity icon-description?)
    (let* ((evaluation-value-function
	     (slot-value-to-evaluation-value-function 'icon-description?))
	   (slot-description?
	     (slot-description-from-class class-name 'icon-description))
	   (slot-init-form?
	     (when slot-description?
	       (slot-init-form slot-description?))))
      (cond (slot-init-form?
	     (let ((line-drawing-description
		     (icon-line-drawing-description slot-init-form?)))
	       (setf line-drawing-description
		     (gensym-push
		       (height-of-icon slot-init-form?)
		       line-drawing-description))
	       (setf line-drawing-description
		     (gensym-push (width-of-icon slot-init-form?)
				  line-drawing-description))
	       (prog1
		   (call-category-getter-fn
		     evaluation-value-function
		     line-drawing-description 
		     nil nil)
		 (reclaim-gensym-cons (cdr line-drawing-description))
		 (reclaim-gensym-cons line-drawing-description))))
	    (t 'nil))))

(def-pseudo-attribute cross-section-pattern
    (connection cross-section-pattern)
  (let* ((evaluation-value-function
	     (slot-value-to-evaluation-value-function 'cross-section-pattern))
	   (slot-description?
	     (slot-description-from-class class-name 'cross-section-pattern))
	   (slot-init-form?
	     (when slot-description?
	       (slot-init-form slot-description?))))
      (cond (slot-init-form?
	     (let ((cross-section-pattern slot-init-form?))
	       (call-category-getter-fn
		 evaluation-value-function
		 cross-section-pattern ;BUG need to reclaim
		 nil nil)))
	    (t nil))))

(def-pseudo-attribute stub-length
    (connection stub-length)
     (let* ((evaluation-value-function
	     (slot-value-to-evaluation-value-function 'stub-length))
	    (slot-description?
	      (slot-description-from-class class-name 'stub-length))
	    (slot-init-form?
	      (when slot-description?
		(slot-init-form slot-description?))))
       (cond (slot-init-form?
	      (call-category-getter-fn
		evaluation-value-function
	      slot-init-form?
	      nil nil))
	     (t nil))))

(def-pseudo-attribute junction-block-class
    (connection junction-class)
     (let* ((evaluation-value-function
	      (slot-value-to-evaluation-value-function 'junction-class))
	    (slot-description?
	      (slot-description-from-class class-name 'junction-block-class))
	    (slot-init-form?
	      (when slot-description?
		(slot-init-form slot-description?))))
       (cond (slot-init-form?
	      (call-category-getter-fn
		evaluation-value-function
		slot-init-form?
		nil nil))
	     (t nil))))

(def-pseudo-attribute default-message-properties
    (message message-properties)
    (let* ((evaluation-value-function
	     (slot-value-to-evaluation-value-function 'message-properties))
	   (slot-description?
	     (slot-description-from-class class-name
					  'default-message-properties-for-class))
	   (slot-init-form?
	     (when slot-description?
	       (slot-init-form slot-description?))))
      (cond (slot-init-form?
	     (call-category-getter-fn
	       evaluation-value-function
	       slot-init-form?
	       nil nil))
	    (t nil))))

(def-pseudo-attribute kb-workspace-initial-width
    (kb-workspace positive-integer)
    (let* ((evaluation-value-function
	     (slot-value-to-evaluation-value-function 'positive-integer))
	   (slot-description?
	     (slot-description-from-class class-name
					  'kb-workspace-initial-width))
	   (slot-init-form?
	     (when slot-description?
	       (slot-init-form slot-description?))))
      (cond (slot-init-form?
	     (call-category-getter-fn
	       evaluation-value-function
	       slot-init-form?
	       nil nil))
	    (t nil))))

(def-pseudo-attribute kb-workspace-initial-height
    (kb-workspace positive-integer)
    (let* ((evaluation-value-function
	     (slot-value-to-evaluation-value-function 'positive-integer))
	   (slot-description?
	     (slot-description-from-class class-name
					  'kb-workspace-initial-height))
	   (slot-init-form?
	     (when slot-description?
	       (slot-init-form slot-description?))))
      (cond (slot-init-form?
	     (call-category-getter-fn
	       evaluation-value-function
	       slot-init-form?
	       nil nil))
	    (t nil))))

(def-pseudo-attribute default-text-box-format-name
   (text-box  ;free-text, name-box, statement, message
     symbol)
    (let* ((evaluation-value-function
	     (slot-value-to-evaluation-value-function 'symbol))
	   (slot-description?
	     (slot-description-from-class class-name
					  'default-text-box-format-name))
	   (slot-init-form?
	     (when slot-description?
	       (slot-init-form slot-description?))))
      (cond (slot-init-form?
	     (call-category-getter-fn
	       evaluation-value-function
	       slot-init-form?
	       nil nil))
	    (t nil))))

(def-pseudo-attribute default-readout-table-format-name
    (readout-table symbol)
    (let* ((evaluation-value-function
	     (slot-value-to-evaluation-value-function 'symbol))
	   (slot-description?
	     (slot-description-from-class class-name
					  'default-readout-table-format-name))
	   (slot-init-form?
	     (when slot-description?
	       (slot-init-form slot-description?))))
      (cond (slot-init-form?
	     (call-category-getter-fn
	       evaluation-value-function
	       slot-init-form?
	       nil nil))
	    (t nil))))

(def-pseudo-attribute system-menu-choices (block (or (sequence (symbol) 0)
						     no-item))
  (system-menu-choices-for-class class-name))

(defmacro pseudo-attribute-name-defining-class (attribute-name)
  `(let ((pseudo-attribute (pseudo-attribute ,attribute-name)))
     (when pseudo-attribute
       (pseudo-attribute-defining-class pseudo-attribute))))

(defun class-defines-pseudo-attribute-p (class-name attribute-name)
  (when (pseudo-attribute attribute-name)
    (eq (pseudo-attribute-name-defining-class attribute-name)
	class-name)))

;; do we need editor-grammar?
;; icon-description,junction-block-class, cross-section-pattern
;; slot-type bugs
(defun generate-description-of-pseudo-attribute (attribute-name
						 initial-value-for-specific-class)
  (allocate-evaluation-structure-inline
    'ATTRIBUTE-NAME (copy-evaluation-value attribute-name)
    'TEXT-READABLE (copy-evaluation-truth-value evaluation-false-value)
    'TEXT-WRITABLE (copy-evaluation-truth-value evaluation-false-value)
    'VALUE-READABLE (copy-evaluation-truth-value evaluation-false-value)
    'VALUE-WRITABLE (copy-evaluation-truth-value evaluation-false-value)
    'IS-SYSTEM-DEFINED (copy-evaluation-truth-value evaluation-true-value)
    'DEFINING-CLASS (copy-if-evaluation-value
		      (pseudo-attribute-name-defining-class attribute-name))
    'INITIAL-VALUE initial-value-for-specific-class
    ;;'EDITOR-GRAMMAR nil
    'TYPE (generate-type-description-of-attribute
	    (pseudo-attribute-type-description
	      (pseudo-attribute attribute-name)))
    ;;'SUPERSEDED (copy-evaluation-value '(-1000 . TRUTH-VALUE))
    ))

(defun-simple filtered-virtual-attributes-local-to-class (class-name)
  (loop with virtual-attributes = (virtual-attributes-local-to-class class-name)
	for attribute in virtual-attributes
	as valid-attribute
	   = (if (consp attribute)
		 (if (eq 'deprecated (cadr attribute))
		     nil
		     (car-of-cons attribute))
		 attribute)
	when valid-attribute
	  collect valid-attribute using eval-cons))

(defun classes-of-class-p (classes class)
  (loop for each-class in classes
	as class-description = (class-description each-class)
	thereis
	(and class-description
	     (class-description-of-class-p class-description class))))

(defun-simple get-list-of-instance-attributes
    (class-description include-inherited-attributes-p stop-classes)
  (let* ((class-name (class-name-of-class-description class-description))
	 (virtual-attr-list
	   ;; Potential bug:  users can define attributes with the same
	   ;; name as virtual attributes.  We can't check for that yet.
	   (loop with virtual-attributes
		   = (if include-inherited-attributes-p
			 (all-virtual-attributes-for-class class-description nil)
			 (filtered-virtual-attributes-local-to-class
			   class-name))
		 for attr-name in virtual-attributes
		 as attribute-structure = (virtual-attribute attr-name)
		 as defining-class = (virtual-attribute-defined-for-class?
				       attribute-structure
				       class-name)
		 as include-attribute-p
		    = (not (classes-of-class-p stop-classes defining-class))
		 when include-attribute-p
		   collect (eval-cons attr-name attribute-structure)
		     using eval-cons
		 finally (reclaim-eval-list virtual-attributes)))
	 (slot-desc-list
	   (loop for slot-description in (slot-descriptions class-description)
		 for defining-class-name = (defining-class slot-description)
		 for aliased-slot-name = (if (slot-name-needs-qualification-p
					       slot-description
					       class-description)
					     (unique-slot-name slot-description)
					     (alias-slot-name-if-necessary
					       (pretty-slot-name slot-description)
					       defining-class-name))
		 if (and (or include-inherited-attributes-p
			     (eq defining-class-name class-name))
			 (not (classes-of-class-p stop-classes defining-class-name))
			 (user-visible-slot-p slot-description)
			 (not (assq aliased-slot-name virtual-attr-list)))
		   collect (eval-cons aliased-slot-name slot-description)
		     using eval-cons))
	 (virtual-attr-list-non-local
	   (when virtual-attributes-not-local-to-a-class
	     (loop for non-local-attr in virtual-attributes-not-local-to-a-class
		   as attribute-structure = (virtual-attribute non-local-attr)
		   as defining-class = (virtual-attribute-defined-for-class?
					 attribute-structure
					 class-name)
		   when (cond (include-inherited-attributes-p
			       (and (not (classes-of-class-p stop-classes defining-class))
				    (applicable-and-not-deprecated-virtual-attribute-p
				      class-description attribute-structure
				      nil)))
			      (t
			       (eq defining-class class-name)))
		     collect (eval-cons non-local-attr attribute-structure)
		       using eval-cons))))
    (sort-pairs-according-to-defining-class
      class-name
      (nconc slot-desc-list
	     virtual-attr-list
	     virtual-attr-list-non-local))))

(defun get-static-attribute-descriptions-of-class (class-name
						    &optional include-inherited-attributes-p)
  (cond ((system-defined-class-p class-name)
	 (loop with result = nil
	       for attribute-name in static-attributes
	       as class-defines-attribute-p
		  = (class-defines-pseudo-attribute-p class-name attribute-name)
	       do
	   (when (or class-defines-attribute-p
		     (and include-inherited-attributes-p
			  (class-description-of-class-p
			    (class-description class-name)
			    (pseudo-attribute-name-defining-class attribute-name))))
	     (eval-push (generate-description-of-pseudo-attribute
			  attribute-name
			  (get-attribute-from-class class-name attribute-name))
			result))
	       finally
		 (return (allocate-evaluation-sequence result))))
	((user-defined-class-p class-name)
	 (get-instance-attribute-descriptions-of-class
	   (class (class-definition class-name))
	  t ; include-inherited-attributes-p
	   '(item entity)))
	(t (no-such-class-error))))

(defun get-instance-attribute-descriptions-of-class (class-name
						      &optional
						      include-inherited-attributes-p
						      stop-classes)
  (cond ((class-description class-name)
	 (loop with name-and-description-alist
		 = (get-list-of-instance-attributes (class-description class-name)
						    include-inherited-attributes-p
						    stop-classes)
	       for (name . slot) in name-and-description-alist
	       collect (generate-description-of-attribute
			 class-name
			 name slot (class-description class-name) nil 'administrator t)
		 into struct-list using eval-cons
	       finally
		 (reclaim-eval-alist name-and-description-alist)
		 (return (allocate-evaluation-sequence struct-list))))
	(t
	 (no-such-class-error))))

(defun get-global-class-info-attribute-names-and-values (class-name)
  (loop with result = nil
	for attribute-name in class-info-attributes
	as attribute-value
	   = (get-attribute-from-class class-name attribute-name)
	do
    (eval-push attribute-value result)
    (eval-push attribute-name result)
	finally
	  (return result)))

(defun get-attribute-from-class (classname attribute)
   (cond
     ((or (system-defined-class-p classname)
	  (and (class-description classname)
	       (pseudo-attribute attribute)))
      (let* ((pseudo-attribute (pseudo-attribute attribute))
	     (pseudo-attribute-getter
	       (and pseudo-attribute
		    (pseudo-attribute-getter pseudo-attribute))))
	(and pseudo-attribute-getter (funcall pseudo-attribute-getter classname))))
     ((user-defined-class-p classname)
      (let ((item (class-definition classname))
	    (denotation
	      (make-attribute-denotation
		(evaluation-symbol-symbol attribute)
		nil
		t))
	    (evaluation-value-or-error nil))
	(when (and (framep item)
		   (evaluation-symbol-p attribute))
	  (setq evaluation-value-or-error
		(get-denoted-evaluation-value item denotation)))))
     (t (no-such-class-error))))
    
(defun get-class-info (class-name include-inherited-attributes-p structure-p)
  (cond ((class-description class-name)
	 (let ((class-info-attributes
		 (nreverse (get-global-class-info-attribute-names-and-values class-name)))
	       (class-attributes
		 (get-static-attribute-descriptions-of-class
		   class-name
		   include-inherited-attributes-p))
	       (instance-attributes
		 (get-instance-attribute-descriptions-of-class
		   class-name
		   include-inherited-attributes-p)))
	   (eval-push 'class-attributes class-info-attributes)
	   (eval-push class-attributes class-info-attributes)
	   (eval-push 'instance-attributes class-info-attributes)
	   (eval-push instance-attributes class-info-attributes)
	   #+java-export-facilities
	   (setq class-info-attributes
		 (add-class-export-info-attributes
		   class-name
		   class-info-attributes))
	   (setq class-info-attributes (nreverse class-info-attributes))
	   (if structure-p
	       (allocate-evaluation-structure class-info-attributes)
	       class-info-attributes)))
	(t (no-such-class-error))))
    
(defun-system-rpc (g2-get-class-info (datum))
    ((rpc-instance system-rpc-instance)
     (class-name symbol)
     (include-inherited-attributes-p truth-value))
  (let* ((current-system-rpc-icp-socket?	          ; This is not bound in defun-system-rpc but
	   (system-rpc-instance-icp-socket rpc-instance)) ; we need the interface of the call later
	 (info-or-error (get-class-info
			  class-name
			  (evaluation-truth-value-is-true-p
			    include-inherited-attributes-p)
			  t)))
    (cond ((eq info-or-error (no-such-class-error))
	   ;;((access-error-p evaluation-value-or-error)
	   (system-rpc-access-error rpc-instance
				    (make-no-such-class-error-message
				      class-name)))
	  (t
	   (return-from-system-defined-rpc
	     rpc-instance
	     (eval-list info-or-error))))))


(defun-void g2-include-method-text-in-export (include-method-text)
  (let ((include-text-p (evaluation-truth-value-is-true-p include-method-text))
	(enclosing-gsi-interface-frame?
	  (when current-system-rpc-icp-socket?
	    (enclosing-interface-frame?
	      current-system-rpc-icp-socket?))))
    (when (and (framep enclosing-gsi-interface-frame?)
	       (frame-has-not-been-reprocessed-p
		 enclosing-gsi-interface-frame?
		 (enclosing-interface-frame-serial-number current-system-rpc-icp-socket?)))
      (setf (include-method-text-in-class-export enclosing-gsi-interface-frame?)
	    include-text-p))))

(define-system-rpc-access (g2-include-method-text-in-export ())
    ((include-method-text truth-value))
  (g2-include-method-text-in-export include-method-text)
  nil)


(defun-simple get-class-inheritance-path (class-name)
  (let ((class-description (class-description class-name)))
    (cond (class-description
	   (allocate-evaluation-sequence
	     (loop for class-in-hierarchy in (class-inheritance-path class-description)
		   collect class-in-hierarchy using eval-cons)))
	  (t
	   (no-such-class-error)))))

(defun-system-rpc (g2-get-class-inheritance-path ((sequence)))
    ((rpc-instance system-rpc-instance)
     (class-name symbol))
  (let ((info-or-error
	  (get-class-inheritance-path
	    class-name)))
    (cond ((eq info-or-error (no-such-class-error))
	   (system-rpc-access-error rpc-instance
				    (make-no-such-class-error-message
				      class-name)))
	  (t
	   (return-from-system-defined-rpc
	     rpc-instance
	     (eval-list info-or-error))))))

(defun-simple g2-get-short-class-info (class-name)
  (let ((class-description (class-description class-name)))
    (cond (class-description
	   (let ((definition (get-instance-with-name-if-any 'definition class-name))
		 (class-inheritance-path
		   (allocate-evaluation-sequence
		     (loop for class-in-hierarchy in (class-inheritance-path class-description)
			   collect class-in-hierarchy using eval-cons))))

	     (if definition		; user-defined-class
		 (allocate-evaluation-sequence
		   (eval-list
		     class-inheritance-path
		     definition
		     (make-evaluation-symbol (get-module-block-is-in definition))))
		 class-inheritance-path)))
	  (t
	   (no-such-class-error)))))
  
(defun-system-rpc (g2-get-short-class-info ((sequence)))
    ((rpc-instance system-rpc-instance)
     (class-name symbol))
  (let ((info-or-error
	  (g2-get-short-class-info
	    class-name)))
    (cond ((eq info-or-error (no-such-class-error))
	   (system-rpc-access-error rpc-instance
				    (make-no-such-class-error-message
				      class-name)))
	  (t
	   (return-from-system-defined-rpc
	     rpc-instance
	     (eval-list info-or-error))))))

(defun-system-rpc (g2-get-attribute-from-class ((or (no-item) datum)))
    ((rpc-instance system-rpc-instance)
     (classname symbol)
     (attribute symbol))
  (let ((evaluation-value-or-error
	 (get-attribute-from-class classname attribute)))
    (cond
      ((access-error-p evaluation-value-or-error)
       (system-rpc-access-error rpc-instance evaluation-value-or-error))
      (t
       (return-from-system-defined-rpc
	 rpc-instance
	 (eval-list evaluation-value-or-error))))))

(defun-system-rpc (g2-get-attributes-from-class ((or (no-item) datum)))
    ((rpc-instance system-rpc-instance)
     (classname symbol)
     (attributes (sequence)))
  (let ((evaluation-value-or-error
	  (loop
	    with attribute-values = '()
	    for attribute-name being each evaluation-sequence-element of attributes
	    as attribute-value-or-error = (get-attribute-from-class classname attribute-name)
		do
	    (cond ((access-error-p attribute-value-or-error)
		   (loop for value in attribute-values
			 do
		     (reclaim-if-evaluation-value value))
		   (reclaim-eval-list attribute-values)
		   (return attribute-value-or-error))
		  (t
		   (eval-push attribute-value-or-error attribute-values)
		   (eval-push attribute-name attribute-values)))
	    finally
	      (return (allocate-evaluation-structure
			attribute-values)))))
    (cond
      ((access-error-p evaluation-value-or-error)
       (system-rpc-access-error rpc-instance evaluation-value-or-error))
      (t
       (return-from-system-defined-rpc
	 rpc-instance
	 (eval-list evaluation-value-or-error))))))

(defun-system-rpc (g2-get-multiple-class-attribute-values ((structure)))
    ((rpc-instance system-rpc-instance)
     (class-names (sequence)))
  (return-from-system-defined-rpc
	 rpc-instance
	 (eval-list (g2-get-multiple-class-attribute-values class-names))))

(defun-simple g2-get-multiple-class-attribute-values (class-names)
  (let ((classes-to-collect ())
	(class-attribute-values-list ()))
    (loop for class-name being each evaluation-sequence-element of class-names
	  when (class-description class-name)
	    do
      (let ((class-inheritance-path (class-inheritance-path (class-description class-name))))
	(loop for class-in-path in class-inheritance-path
	      do
	  (gensym-pushnew class-in-path classes-to-collect))))
    (loop for class-to-collect in classes-to-collect
	  do
      (eval-push
	(get-class-attribute-values-or-definition class-to-collect)
	class-attribute-values-list)
      (eval-push
	class-to-collect
	class-attribute-values-list))
    (reclaim-gensym-list classes-to-collect)
    (allocate-evaluation-structure class-attribute-values-list)))

(defun-simple get-class-attribute-values-or-definition (class-name)
  (cond ((system-class-p class-name)
	 (get-system-class-attribute-values class-name))
	(t
	 (get-instance-with-name-if-any 'definition class-name))))

(defun-simple get-system-class-attribute-values (class-name)
  (let ((class-attribute-values ()))
    (loop for pseudo-attribute-name in static-attributes
	  as pseudo-attribute = (pseudo-attribute pseudo-attribute-name)
	  as defining-class = (pseudo-attribute-defining-class pseudo-attribute)
	  when
	    (subclassp class-name defining-class)
	    do
	      (eval-push
		(get-attribute-from-class class-name pseudo-attribute-name)
		class-attribute-values)
	      (eval-push
		pseudo-attribute-name
		class-attribute-values))
    (allocate-evaluation-structure class-attribute-values)))
						    
(defun-system-rpc (g2-get-format-info (datum))
    ((rpc-instance system-rpc-instance)
     (format-name symbol))
  (let ((format-description? (format-description format-name)))
    (cond
      (format-description?
       (return-from-system-defined-rpc
	 rpc-instance
	 (eval-list
	   (export-format-description format-description?))))
      (t
       (system-rpc-access-error
	 rpc-instance
	 (access-error
	   'no-such-format-error
	   'format-name format-name))))))

(defun export-format-description (format-description)
  (loop with name-value-plist = nil
	with class-name = (car format-description)
	with overrides-plist = (cdr format-description)
	with name-and-description-alist
	  = (get-list-of-instance-attributes (class-description class-name)
					     t
					     '(item entity))
	for (name . slot) in name-and-description-alist
	as slot-type = (feature-assq
			 'type
			 (slot-features slot))
	as slot-init-form? = (slot-init-form slot)
	as override? = (getfq overrides-plist name)
	as value? = (or override? slot-init-form?)
	as exported-value? = (and value?
				 (export-format-value value? slot-type))
	do
    (when exported-value?
      (eval-push name name-value-plist)
      (eval-push exported-value? name-value-plist))
	finally
	  (reclaim-eval-alist name-and-description-alist)
	  (when name-value-plist
	    (return (allocate-evaluation-structure (nreverse name-value-plist))))))

(defun export-format-value (value slot-type)
  (let* ((category-symbol?
	   (if slot-type
	       (category-symbol-given-slot-type slot-type)))
	 (category-getter?
	   (if category-symbol?
	       (slot-value-to-evaluation-value-function
		 category-symbol?))))
    category-getter?
    ;;need cat eval getters for the following types:
    ;;WIDTH QUADDING BOOLEAN WORD-SPACING COLOR
    ;;FONT-MAP MAGNIFICATION-OR-FACTOR?
    (cond ((consp value)
	   (let ((font-name? (car-of-cons value)))
	     (cond ((and (or (ab-font font-name?)
			     (eq font-name? 'fixed14))
			 (null (cdr value)))
		    font-name?)
		   (t
		    #+development
		    (cerror "continue"
			    "Unknown format-value. Please inform pbk ~s."
			    value)
		    nil))))
	  (t
	   (make-evaluation-value-based-on-type value)))))

(defun-for-system-procedure g2-get-class-hash (class-name)
  (let ((class-description? (class-description class-name)))
    (cond
      (class-description?
       (setf leave-text-representation-as-a-single-line? t)
       (let* ((indent-sequences-and-structures-p nil)
	      (class-info
		(get-class-info class-name nil t)))
	 (prog1 (evaluation-value-hash class-info)
	   (reclaim-evaluation-value class-info))))
      (t
       (stack-error cached-top-of-stack
		    "~A does not name a class" class-name)))))

(define-system-rpc-access (g2-get-class-hash ((unsigned-vector-16)))
    ((class-name symbol))
  (let ((result
	  (g2-get-class-hash class-name)))
    (cond ((wide-string-p result)
	   (maybe-make-evaluation-unsigned-vector-16 result))
	  (t
	   #+development
	   (error "this can't happen")
	   result))))


#+development
(defun test-export-format-description-1 ()
  (let ((i 0))
   (do-symbols (sym)
    (when (format-description sym)
      (incff i)
      (format t "~s)~s: ~s ~%" i sym (d (car (export-format-description (format-description sym)))))))))


#+development
(defun all-the-children-of (class-list?)
  (loop with all-children-list = '()
	with was-given-a-list = (listp class-list?)
	with class-list = (if (listp class-list?) class-list?
			      (gensym-list class-list?))
	for class-name in class-list
	do
    (loop for subclass being each subclass of class-name
	  do
      (unless (eq subclass class-name)
	(gensym-push subclass all-children-list)))
	finally
	  (unless was-given-a-list
	    (reclaim-gensym-list class-list))
	  (return all-children-list)))

#+development
(defun export-built-in-classes (root-class)
  (loop with classes = (nreverse (all-the-children-of root-class))
	with export-data = nil
	for class in classes
	as class-data
	   = (get-class-info class nil t)
	do
    (eval-push class-data export-data)
	finally
	  (reclaim-gensym-list classes)
	  (return (allocate-evaluation-sequence export-data))))

#+development
(defun-system-rpc (g2-export-built-in-classes (datum))
    ((rpc-instance system-rpc-instance)
     (rootclass symbol))
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list (export-built-in-classes rootclass))))

;;; Tools for dumping the G2 class hierarchy into a structure/sequence
;;; tree. It is specially designed to pick up only those classes
;;; that are either a subclass of ITEM, or have a subclass of ITEM
;;; among its subclasses.

#+development
(def-hash-table class-heirarchy-dump
    :constructor make-class-heirarchy-dump
    :entry-reclaimer identity
    :accessor get-hierarchy-dump-internal
    :key-deleter delete-class-heirarchy-dump
    :size 109
    :use-binary-tree t)

#+development
(defvar the-class-heirarchy-dump-table
  (make-class-heirarchy-dump))

#+development
(defun class-heirarchy-dump-gethash (class-name)
  (get-hierarchy-dump-internal class-name the-class-heirarchy-dump-table))

#+development
(defun class-heirarchy-dump-puthash (class-name struct)
  (setf (get-hierarchy-dump-internal class-name the-class-heirarchy-dump-table)
	struct))

#+development
(defun dump-class-hierarchy (class-name)
  (or (class-heirarchy-dump-gethash class-name)
      (loop with struct = (allocate-evaluation-structure-inline
			    'class-name
			    class-name)
	    with subclasses = '()
	    for subclass being each subclass of class-name
	    as subclass-struct = (and subclass
				      (not (eq subclass class-name))
				      (dump-class-hierarchy subclass))
	    do
	(and subclass-struct
	     (eval-push subclass-struct subclasses))
	    finally
	      (and subclasses
		   (setf subclasses (nreverse subclasses))
		   (setf (evaluation-structure-slot struct 'subclass-structures)
			 (allocate-evaluation-sequence subclasses)))
	    (class-heirarchy-dump-puthash class-name struct)
	    (fill-in-superclasses-for-dump class-name struct)
	    (return struct))))

#+development
(defun fill-in-superclasses-for-dump (class-name struct)
  (loop for parent in (direct-superior-classes class-name)
	do
    (fill-in-superclass-for-dump parent struct)))

#+development
(defun is-in-sequence-p (thing sequence &optional (test #'eq))
  (loop for elt being each evaluation-sequence-element
	of sequence
	thereis (funcall test elt thing)))

#+development
(defun fill-in-superclass-for-dump (class-name child-class-struct)
  (or
    ;; will find all its children filled in by a visit from the descendents of ITEM
    (class-description-of-class-p (class-description class-name) 'item)
    (let* ((already-installed-struct (class-heirarchy-dump-gethash class-name))
	   (struct (or already-installed-struct
		       (allocate-evaluation-structure-inline
			 'class-name
			 class-name)))
	   (seq (or (evaluation-structure-slot struct 'subclass-structures)
		    (setf (evaluation-structure-slot struct 'subclass-structures)
			  (allocate-evaluation-sequence nil)))))
      (unless (is-in-sequence-p child-class-struct seq)
	(evaluation-sequence-insert-at-end seq child-class-struct)
	(unless already-installed-struct
	  (class-heirarchy-dump-puthash class-name struct)
	  (fill-in-superclasses-for-dump class-name struct))))))

#+development
(defun-system-rpc (g2-dump-tw2-class-hierarchy (datum))
    ((rpc-instance system-rpc-instance)
     (rootclass symbol))
  (dump-class-hierarchy rootclass)
  (return-from-system-defined-rpc
    rpc-instance
    (prog1
	(eval-list (class-heirarchy-dump-gethash 'root))
      ;; every entry in the hashtable just got reclaimed by being
      ;; passed as a return value to an rpc call. I don't know
      ;; if the following will also reclaim the keys (it's a
      ;; development-time only tool right now...)
      (clear-class-heirarchy-dump the-class-heirarchy-dump-table))))
      

#+development
(defun pprint-ma (ma)
  (loop for i from 4 to (+f (managed-array-length ma) 1)
	as elt = (svref ma i)
	as elt-name = (evaluation-structure-slot elt 'attribute-name)
	as defining-class = (evaluation-structure-slot elt 'defining-class)
	do (format t "name: ~s defining-class: ~s~% it: ~s~%~%"
		   elt-name
		   defining-class
		   elt)))

#+development
(defun test-get-attribute-from-class-internal (class-name class-attribute-descriptions-sequence)
  (loop for attribute-description being each evaluation-sequence-element of class-attribute-descriptions-sequence
	as attribute-name = (evaluation-structure-slot attribute-description 'attribute-name)
	as attribute-type = (evaluation-structure-slot attribute-description 'type)
	as defining-class = (evaluation-structure-slot attribute-description 'defining-class)
	do (format t "name: ~s type: ~s defining-class ~s value: ~s~%~%"
		 attribute-name
		 attribute-type
		 defining-class
		 (get-attribute-from-class class-name attribute-name))))

#+development
(defun test-get-attribute-from-class-2 (class-name)
  (loop for class in (class-inheritance-path-internal
			    (class-description class-name))
	as attribute-descriptions = (get-static-attribute-descriptions-of-class class)
	do
    (format t "~%Testing class: ~s with attribute defined by ~s~%-------------------------------------------------------~%"
	    class-name class)
    (test-get-attribute-from-class-internal class-name attribute-descriptions)))

;;; `test-get-attribute-from-class-3'
;;; loops over inheritance path of class-name and gets static attributes for each
;;; class for the attributes defined at that class
#+development
(defun test-get-attribute-from-class-3 (class-name)
  (loop for class in (class-inheritance-path-internal
			    (class-description class-name))
	as attribute-descriptions = (get-static-attribute-descriptions-of-class class)
	do
    (format t "~%Testing class: ~s~%-------------------------------------------------~%" class)
    (test-get-attribute-from-class-internal class attribute-descriptions)))

;;; `test-get-attribute-from-class-4'
;;; loops over inheritance path of class-name and gets static attributes for each
;;; class for all attributes, whether defined at that class or inherited. 
#+development
(defun test-get-attribute-from-class-4 (class-name)
  (loop for class in (class-inheritance-path-internal
			    (class-description class-name))
	as attribute-descriptions = (get-static-attribute-descriptions-of-class class t)
	do
    (format t "~%Testing class: ~s~%-------------------------------------------------~%" class)
    (test-get-attribute-from-class-internal class attribute-descriptions)))
    
	
#+vkp-development
(defun test-get-attribute-from-class (classname attribute
			    &optional (default-value 'default-value))
  (let* ((item? (get-instance-with-name-if-any 'class-definition classname))
	 (denotation (make-attribute-denotation
		       (evaluation-symbol-symbol attribute)
		       nil
		       t))
	 (answer (and item?
		      (get-denoted-evaluation-value item? denotation))))
    (or answer default-value)))

#+development
(defparameter valid-slotname-for-classes
  '(class-name direct-superior-classes instantiate include-in-menus
    icon-description))



  




;;;; NEW RPCs


(defun-system-rpc (g2-get-list-of-workspaces (datum))
    ((rpc-instance system-rpc-instance))
  (loop with ws-info = nil
	with ws-info-list = ()
	for ws being each class-instance of 'kb-workspace
	as name? = (get-primary-name-for-frame-if-any ws)
	do
    (unless (or (superblock? ws) (null name?))
      ;;(format-when-tracing-in-events-modules "~s exists~%" ws)
      (eval-push name? ws-info-list))
	finally
	  (setq ws-info (allocate-evaluation-sequence ws-info-list))
	  (return-from-system-defined-rpc
	    rpc-instance
	    (eval-list ws-info))))


(defun create-bounds-structure-from-block-edges (block)
  (allocate-evaluation-structure-inline
    'left (left-edge-of-block block)
    'top (top-edge-of-block block)
    'right (right-edge-of-block block)
    'bottom (bottom-edge-of-block block)))



(defun get-gensym-window-from-system-rpc-instance-icp-socket
    (system-rpc-instance-icp-socket)
  (loop for workstation in workstations-in-service
	as window
	   = (window-for-workstation workstation)
	as icp-output-port
	   = (icp-output-port-for-window? window)
	as parent-icp-socket
	   = (and icp-output-port
		  (parent-icp-socket icp-output-port))
	thereis
	(when (eq system-rpc-instance-icp-socket
		  parent-icp-socket)
	  window)))

(defun-system-rpc (g2-set-v5-mode (truth-value))
    ((rpc-instance system-rpc-instance)
     (state truth-value))
  (set-v5-mode-state (evaluation-truth-value-true-p state))
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list
      (if g2-has-v5-mode-windows-p
	  evaluation-true-value
	  evaluation-false-value))))

;;; These next two s-expressions are part of a
;;; temporary hack to deal with the lack of updates
;;; for item-configurations and connection-style in the
;;; workspace protocol and the fact that changing
;;; the connection style does not send an update
;;; for the connection-position-sequence.

(defvar ws-representation-slots-to-update
  '(item-configuration))

(defun-system-rpc (g2-get-updated-workspace-information (datum))
    ((rpc-instance system-rpc-instance)
     (session (class ui-client-session))
     (workspace (class kb-workspace))
     (attributes (or (no-item) (sequence))))
  (when (ui-client-session-ok-for-defun-system-rpc?
		session rpc-instance 'g2-get-updated-workspace-information)
    (let* ((interim-attr-list
	     (and attributes
		  (loop for attr being each evaluation-sequence-element of attributes
			collect attr using eval-cons)))
	   (attr-list (or interim-attr-list
			  ws-representation-slots-to-update))
	   (result (eval-list
		     (create-ws-representation-updated-state
		       workspace
		       attr-list))))
      (and interim-attr-list
	   (reclaim-eval-list interim-attr-list))
      (and attributes
	   (reclaim-evaluation-sequence attributes))
      (return-from-system-defined-rpc
	rpc-instance
	result))))

(defun-system-rpc (g2-represent-workspace (datum))
    ((rpc-instance system-rpc-instance)
     (session (class ui-client-session))
     (workspace (class kb-workspace))
     (callback-procedure symbol))
  (when (ui-client-session-ok-for-defun-system-rpc?
		session rpc-instance 'g2-represent-workspace)
    (let ((existing-representation-for-session? ; a representation across the same interface
	    (find-frame-representation-for-this-session session workspace 'ws-representation)))
      (cond (existing-representation-for-session?
	     (if (associate-workspace-with-ui-session session workspace)
		 (return-from-system-defined-rpc
		   rpc-instance
		   (eval-list (allocate-evaluation-structure-inline
				'return-type
				'session-association-confirmation
				'subscription-handle
				(callback-representation-callback-subscription-handle
				  existing-representation-for-session?))))
		 (system-rpc-error
		   rpc-instance
		   'session-already-associated
		   (tformat-text-string "session already associated with workspace"))))
	    (t
	     (let* ((icp-socket (system-rpc-instance-icp-socket rpc-instance))
		    (ws-initial-data
		      (create-ws-representation-initial-state workspace))
		    (representation
		      (represent-ws workspace icp-socket callback-procedure))
		    (subscription-handle
		      (callback-representation-callback-subscription-handle
			representation)))
	       (associate-workspace-with-ui-session session workspace)
	       (return-from-system-defined-rpc
		 rpc-instance
		 (eval-list
		   (allocate-evaluation-structure-inline
		     'return-type 'initial-subscription-data
		     'workspace-initial-data ws-initial-data
		     'subscription-handle subscription-handle)))))))))



;; based on g2-represent-ws

(defun-system-rpc (g2-represent-trend-chart (datum))
    ((rpc-instance system-rpc-instance)
     (item (class item))
     (callback-procedure symbol))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-represent-trend-chart 'ui-client-interface)
    (let* ((icp-socket (system-rpc-instance-icp-socket rpc-instance))
	   ;; must collect the data before the representation is created
	   ;; so that we can tell if this is the first time while we are collecting
	   (item-initial-data (trend-chart-property-getter item))
	   (representation
	     (represent-trend-chart item icp-socket callback-procedure))
	   (subscription-handle
	     (callback-representation-callback-subscription-handle
	       representation)))
      ;;  (format-when-tracing-in-events-modules
      ;;    "in g2-represent-trend-chart~%")
      (return-from-system-defined-rpc
	rpc-instance
	(eval-list
	  (allocate-evaluation-structure-inline
	    'item-initial-data
	    item-initial-data
	    'subscription-handle subscription-handle))))))

(defun-system-rpc (g2-unrepresent-workspace (truth-value))
    ((rpc-instance system-rpc-instance)
     (session (class ui-client-session))
     (subscription-handle integer))
  (let ((representation? (representation-handle-gethash
			     (evaluation-integer-value subscription-handle)))
	(session-ok? (ui-client-session-ok-for-defun-system-rpc?
		       session rpc-instance 'g2-represent-workspace)))
    (cond ((not session-ok?))
	  ((null representation?)
	   (return-from-system-defined-rpc rpc-instance
					   (eval-list evaluation-false-value)))
	  (t (let ((frame (represented-frame representation?)))
	       (cond ((disassociate-workspace-from-ui-session session frame)
		      (unless (any-session-ws-associations-remaining-p
				frame (ui-client-session-parent-interface session))
			(delete-representation representation?))
		      (return-from-system-defined-rpc rpc-instance
						      (eval-list evaluation-true-value)))
		     (t (system-rpc-error
			  rpc-instance
			  'session-and-workspace-not-associated
			  (tformat-text-string "session and workspace not associated")))))))))

(defun-system-rpc (g2-move-ws-item (truth-value))
    ((rpc-instance system-rpc-instance)
     (item (class item))
     (xpos integer)
     (ypos integer)
     (enlarge-workspace-if-necessary-p-ev truth-value)
     (transient-change-p-ev truth-value))
  (let ((enlarge-workspace-if-necessary-p
	  (prog1 (evaluation-truth-value-is-true-p
		   enlarge-workspace-if-necessary-p-ev)
	    (reclaim-evaluation-truth-value
	      enlarge-workspace-if-necessary-p-ev)))
	(transient-change-p
	  (prog1 (evaluation-truth-value-is-true-p
		   transient-change-p-ev)
	    (reclaim-evaluation-truth-value
	      transient-change-p-ev))))
    (when item ; this seems like total paranoia
      (let ((deltax (-w xpos (item-x-position item)))
	    (deltay (-w ypos (item-y-position item))))
	(when enlarge-workspace-if-necessary-p
	  (enlarge-workspace-if-necessary
	    (get-workspace-if-any item)
	    (+f (left-edge-of-block item) deltax)
	    (+f (top-edge-of-block item) (-w deltay))
	    (+f (right-edge-of-block item) deltax)
	    (+f (bottom-edge-of-block item) (-w deltay))))
	(move-item-by item deltax deltay transient-change-p)
	(invoke-rules-for-movement-chaining item 'is-moved-by-the-user)))
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list (if item evaluation-true-value
		     evaluation-false-value)))))

(define-system-rpc-access (g2-shutdown-g2-process())
    ((status symbol));'requested
  (shut-down-ab-process status)
  nil)


(define-system-rpc-access (g2-clear-kb())
    ()
  (when (and (or (not system-is-running) system-has-paused)
	     (not inside-breakpoint-p))  
    (clear-kb))
  nil)

(defun-system-rpc (g2-set-package-preparation-mode (truth-value))
    ((rpc-instance system-rpc-instance)
     (new-state truth-value))
  (set-package-preparation-mode (evaluation-truth-value-is-true-p new-state))
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list (if package-preparation-mode evaluation-true-value
		   evaluation-false-value))))

(defun-system-rpc (g2-get-package-preparation-mode (truth-value))
    ((rpc-instance system-rpc-instance))
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list (if package-preparation-mode evaluation-true-value
		   evaluation-false-value))))

(defun-system-rpc (g2-set-simulate-proprietary-mode (truth-value))
    ((rpc-instance system-rpc-instance)
     (new-state truth-value))
  (set-simulate-proprietary-mode (evaluation-truth-value-is-true-p new-state))
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list (if simulate-proprietary? evaluation-true-value
		   evaluation-false-value))))

(defun-system-rpc (g2-get-simulate-proprietary-mode (truth-value))
    ((rpc-instance system-rpc-instance))
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list (if simulate-proprietary? evaluation-true-value
		   evaluation-false-value))))

(defun-system-rpc (g2-strip-all-texts (truth-value))
    ((rpc-instance system-rpc-instance))
  (strip-all-texts)
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list evaluation-true-value)))

(defun-system-rpc (g2-make-kb-proprietary (truth-value))
    ((rpc-instance system-rpc-instance))
  (make-proprietary-now)
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list evaluation-true-value)))

(defun-system-rpc (g2-flush-all-change-logs (truth-value))
    ((rpc-instance system-rpc-instance))
  (flush-change-log-for-entire-kb-now)
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list evaluation-true-value)))

(defun-system-rpc (g2-enable-all-items (truth-value))
    ((rpc-instance system-rpc-instance))
  (loop for frame being class-instances of 'block doing
    (when (manually-disabled-p frame)
      (funcall-method 'manually-enable frame)))
  (return-from-system-defined-rpc
    rpc-instance
    (eval-list evaluation-true-value)))
  
(defun-system-rpc (g2-move-ws-item-by (truth-value))
    ((rpc-instance system-rpc-instance)
     (item (class item))
     (deltax integer)
     (deltay integer)
     (enlarge-workspace-if-necessary-p-ev truth-value)
     (transient-change-p-ev truth-value))
  (let ((enlarge-workspace-if-necessary-p
	  (prog1 (evaluation-truth-value-is-true-p
		   enlarge-workspace-if-necessary-p-ev)
	    (reclaim-evaluation-truth-value
	      enlarge-workspace-if-necessary-p-ev)))
	(transient-change-p
	  (prog1 (evaluation-truth-value-is-true-p
		   transient-change-p-ev)
	    (reclaim-evaluation-truth-value
	      transient-change-p-ev))))
    (when item ; this seems like total paranoia
      (let ((workspace? (get-workspace-if-any item)))
	(when (and workspace? enlarge-workspace-if-necessary-p)
	  (multiple-value-bind
	      (extreme-left-edge extreme-top-edge extreme-right-edge
				 extreme-bottom-edge)
	      (determine-extreme-edges-for-item-being-moved item)
	    (enlarge-workspace-if-necessary
	      workspace?
	      (+f extreme-left-edge deltax)
	      (+f extreme-top-edge deltay)
	      (+f extreme-right-edge deltax)
	      (+f extreme-bottom-edge deltay)))))
      (move-item-by item deltax (-f deltay) transient-change-p)
      (invoke-rules-for-movement-chaining item 'is-moved-by-the-user))
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list (if item evaluation-true-value
		     evaluation-false-value)))))

(defun-for-system-procedure g2-move-items-along-paths
    (items paths interval return-rpc-name id)
  (loop with sessions = '()
	with enlarge-workspace-if-necessary-p = t
	with transient-change-p = nil
	for item being each evaluation-sequence-element of items
	for path being each evaluation-sequence-element of paths
	as length = (evaluation-sequence-length path)
	as xpos = (evaluation-sequence-aref path (-f length 2))
	as ypos = (evaluation-sequence-aref path (-f length 1))	
	as deltax = (-w xpos (item-x-position item))
	as deltay = (-w ypos (item-y-position item))
	as workspace? = (get-workspace-if-any item)
	do
  (when (and workspace? enlarge-workspace-if-necessary-p)
    (multiple-value-bind
	(extreme-left-edge extreme-top-edge extreme-right-edge
			   extreme-bottom-edge)
	(determine-extreme-edges-for-item-being-moved item)
      (enlarge-workspace-if-necessary
	workspace?
	(+f extreme-left-edge deltax)
	(+f extreme-top-edge deltay)
	(+f extreme-right-edge deltax)
	(+f extreme-bottom-edge deltay))))
  (move-item-by item deltax deltay transient-change-p)
  (invoke-rules-for-movement-chaining item 'is-moved-by-g2 t)
  (when (and g2-has-v5-mode-windows-p workspace?)
    (do-javalink-notification (workspace? 'ws-representation)
      (send-ws-representations-item-moved-aux
	item path 0 0 interval return-rpc-name id))
    (loop with reps = (frame-representations workspace?)
	  with current-frame-serial-number-on-entry
	    = (copy-frame-serial-number (current-frame-serial-number))      
	  for rep in reps
	  do
      (when (and (frame-of-class-p rep 'ws-representation)
		 (not (frame-has-been-reprocessed-p rep current-frame-serial-number-on-entry))
		 (representation-address-valid-p rep))
	(loop for session in (ui-client-interface-sessions
			       (get-interface-from-representation rep))
	      do
	  (when (workspace-is-showing-in-ui-client-item workspace? session)
	    (eval-push session sessions))))
	  finally
	    (reclaim-frame-serial-number current-frame-serial-number-on-entry)))
	finally
	  (reclaim-evaluation-sequence items)
	  (reclaim-evaluation-sequence paths)
	  (return (allocate-evaluation-sequence sessions))))


(defun-for-system-procedure g2-create-item (class-name)
  (create-action-internal class-name cached-top-of-stack))

(define-system-rpc-access (g2-create-item ((class item)))
    ((class-name symbol))
  (g2-create-item class-name))

(defun-for-system-procedure g2-clone-item (item)
  (create-by-cloning-action-internal
    (class item) item cached-top-of-stack nil))

(define-system-rpc-access (g2-clone-item ((class item)))
    ((item (class item)))
  (g2-clone-item item))

(defun-for-system-procedure g2-transfer-item
    (item target-item ypos xpos
	  attribute-name-or-false class-qualifier-or-false)
  (cond
    ((and item target-item)
     (cond
       ((and (framep target-item)
	     (frame-of-class-p target-item 'kb-workspace)
	     (not (symbolp attribute-name-or-false)))
	(transfer-action-internal item target-item xpos ypos
				  cached-top-of-stack nil)
	evaluation-true-value)
       ((and (framep target-item)
	     (symbolp attribute-name-or-false))
	(let ((place-reference
		(make-evaluation-place-reference-to-place 
		  (make-attribute-component-particulars
		    attribute-name-or-false
		    (and (symbolp class-qualifier-or-false)
			 class-qualifier-or-false)
		    '*current-computation-frame*)
		  target-item)))
	  ;; place-ref is consumed by following call
	  (transfer-action-internal
	    item place-reference xpos ypos cached-top-of-stack nil))
	evaluation-true-value)
       ;; transfer off
       ((not (framep target-item))
	(transfer-action-internal item nil xpos ypos
 				  cached-top-of-stack nil)
 	evaluation-true-value)
       (t
	evaluation-false-value)))
    (t
     evaluation-false-value)))

(define-system-rpc-access (g2-transfer-item (truth-value))
    ((item (class item))
     (target-item item-or-datum)
     (xpos integer)
     (ypos integer)
     (attribute-name-or-false datum)
     (class-qualifier-or-false datum))
  (let ((*current-computation-frame*
	  (enclosing-interface-frame? current-system-rpc-icp-socket?))
	(current-computation-instance nil))
    (g2-transfer-item
      item target-item ypos xpos
      attribute-name-or-false class-qualifier-or-false)))

(defun-for-system-procedure g2-delete-item (item without-permanence-checks-p
						 without-leaving-stubs-p)
  (delete-action-internal
    item
    (prog1 (evaluation-truth-value-is-true-p without-permanence-checks-p)
      (reclaim-evaluation-truth-value without-permanence-checks-p))
    (prog1 (evaluation-truth-value-is-true-p without-leaving-stubs-p)
      (reclaim-evaluation-truth-value without-leaving-stubs-p))
    cached-top-of-stack
    nil)
  nil) ; means no values

(define-system-rpc-access (g2-delete-item ())
    ((item (class item))
     (without-permanence-checks-p truth-value)
     (without-leaving-stubs-p truth-value))
  (let ((*current-computation-frame*
	  (enclosing-interface-frame? current-system-rpc-icp-socket?))
	(current-computation-instance nil))
    (g2-delete-item item without-permanence-checks-p without-leaving-stubs-p)))

(def-virtual-attribute permanent
    ((class item)
     truth-value
     ())
  ;;subscription?
  :event-updates nil
  :initial  ((class) (declare (ignore class)) nil)
  :getter  ((item)
	    (make-evaluation-boolean-value (permanent-block-p item))))


(def-virtual-attribute manually-disabled?
    ((class item)
     truth-value
     ())
  :event-updates nil
  :initial  ((class) (declare (ignore class)) nil)
  :getter  ((item)
	    (make-evaluation-boolean-value (manually-disabled-p item)))
  :setter  ((item new-value)
	    (cond ((not (frame-may-be-enabled-or-disabled-p item))
		   (tformat-text-string "~NF may not be enabled or disabled" item))
		  ((and (evaluation-truth-value-true-p new-value)
			*current-computation-frame* current-computation-instance
			(existence-depends-on-p *current-computation-frame* item))
		   (tformat-text-string "~NF can not be disabled because it is currently running"
					item))
		  (t
		   (if (evaluation-truth-value-true-p new-value)
		       (unless (manually-disabled-p item)
			 (funcall-method 'manually-disable item))
		       (when (manually-disabled-p item)
			 (funcall-method 'manually-enable item)))
		   nil))))

(defun-for-system-procedure g2-make-permanent (item)
  (make-permanent-action-internal item cached-top-of-stack))

(define-system-rpc-access (g2-make-permanent ())
    ((item (class item)))
  (g2-make-permanent item)
  nil)

(def-virtual-attribute transient
    ((class item)
     truth-value
     ())
  ;;subscription?
  :event-updates nil
  :initial  ((class) (declare (ignore class)) nil)
  :getter  ((item)
	    (make-evaluation-boolean-value (transient-p item))))

(defun-for-system-procedure g2-make-transient (item)
  (make-transient-action-internal item cached-top-of-stack))

(define-system-rpc-access (g2-make-transient ())
    ((item (class item)))
  (g2-make-transient item))

(defun-for-system-procedure g2-get-subworkspace (item)
  (car (subworkspaces item)))

(define-system-rpc-access (g2-get-subworkspace ((or (no-item) (class item))))
    ((item (class item)))
  (g2-get-subworkspace item))

(defun-for-system-procedure g2-get-referenced-items (message)
  (let ((snapshots
	  (snapshots-of-valid-blocks-related-to-message message)))
    (loop for snapshot in snapshots
	  as block = (block-of-snapshot snapshot)
	  when (allow-go-to-referenced-item-p block)
	    collect block into lst using eval-cons 
	  finally
	    (return (if lst
			(allocate-evaluation-sequence lst))))))

(define-system-rpc-access (g2-get-referenced-items ((or (no-item) (sequence))))
    ((message (class message)))
  (g2-get-referenced-items message))

(define-system-rpc-access (g2-name-for-item ((or text symbol)))
    ((frame (class block)))
  (g2-user-name-for-frame frame))

   
(defun-for-system-procedure g2-get-origin-of-message (text-box)
  (let ((originating-frame? (get-origin-of-message-if-appropriate text-box)))
    (or originating-frame? evaluation-false-value)))

(define-system-rpc-access (g2-get-origin-of-message ((or (no-item) (class item))))
    ((text-box (class text-box)))
    (let ((origin-or-falsity (g2-get-origin-of-message text-box)))
      (if (framep origin-or-falsity)
	  origin-or-falsity
	  nil)))

(defun-for-system-procedure g2-make-subworkspace (kb-workspace target-item)
  (make-subworkspace-action-internal
    kb-workspace target-item cached-top-of-stack)
  nil)

(define-system-rpc-access (g2-make-subworkspace ())
    ((kb-workspace (class kb-workspace))
     (target-item (class item)))
  (g2-make-subworkspace kb-workspace target-item))


(defun-for-system-procedure g2-get-containment-hierarchy (item)
  (loop with containment-list = nil
	as current-item
	   = item
	   then superior-frame
	as superior-frame = (superior-frame current-item)
	while superior-frame
	do
    (eval-push superior-frame containment-list)
	finally
	  (return (allocate-evaluation-sequence
		    (nreverse containment-list)))))

(define-system-rpc-access (g2-get-containment-hierarchy ((sequence))
							ui-client-interface)
    ((item (class item)))
  (g2-get-containment-hierarchy item))


(defun-simple exported-user-menu-choice-p (user-menu-choice frame restrictions permitted?)
  (let ((choice-name (user-menu-choice-symbol? user-menu-choice)))
    (and choice-name
	 (not (built-in-menu-choice-p choice-name))
	 (action-for-user-menu-choice? user-menu-choice)
	 (evaluate-user-menu-choice-condition user-menu-choice frame)
	 (if (memq choice-name restrictions)
	     permitted? (not permitted?)))))

;; New callers should pass a g2-window as the second argument. A user-mode
;; symbol is accepted only for backwards compatibility.
(defun-for-system-procedure g2-get-current-user-menu-choices (item user-mode-or-g2-window)
  (check-type-or-stack-error user-mode-or-g2-window '(or symbol (class g2-window)))
  (cond ((symbolp user-mode-or-g2-window)
	 (g2-get-current-user-menu-choices-internal item user-mode-or-g2-window))

	((of-class-p user-mode-or-g2-window 'g2-window)
	 (let ((gensym-window (map-to-gensym-window-or-stack-error user-mode-or-g2-window)))
	   (for-workstation ((workstation-this-is-on gensym-window))
	     (g2-get-current-user-menu-choices-internal
	       item (g2-user-mode user-mode-or-g2-window)))))))

(defun g2-get-current-user-menu-choices-internal (item user-mode)
  (loop with class = (class item)
	with exported-user-menu-choices = nil
	with current-g2-user-mode? = user-mode
	with restrictions = nil
	with permitted = nil
	initially
	  (multiple-value-setq (restrictions permitted)
	    (compute-menu-restrictions-for-workspace item))
	for superior-class in (class-inheritance-path (class-description class))
	do
    (loop for current-user-menu-choice
	      in (user-menu-choices-for-this-class superior-class)
	  when (and (exported-user-menu-choice-p
		      current-user-menu-choice item
		      restrictions permitted)
		    (loop for exported-user-menu-choice
			      in exported-user-menu-choices
			  never (eq (user-menu-choice-symbol?
				      current-user-menu-choice)
				    (user-menu-choice-symbol?
				      exported-user-menu-choice))))
	    do
	      (eval-push current-user-menu-choice exported-user-menu-choices))
	finally
	  (return (allocate-evaluation-sequence exported-user-menu-choices))))

(define-system-rpc-access (g2-get-current-user-menu-choices ((sequence))
							    ui-client-interface)
    ((item (class item))
     (user-mode symbol))
  (g2-get-current-user-menu-choices-internal item user-mode))

(define-system-rpc-access (g2-get-current-user-menu-choices-for-session ((sequence))
							    ui-client-interface)
    ((item (class item))
     (session (class ui-client-session)))
  (let ((user-mode (ui-client-session-user-mode session))
	(current-ui-client-session session))
    (g2-get-current-user-menu-choices-internal item user-mode)))

(defun-for-system-procedure g2-get-user-menu-choice
    (label applicable-class)
  (let ((class-description (class-description applicable-class)))
    (when class-description
      (loop for superior-class in (class-inheritance-path class-description)
	    thereis
	    (loop for umc in (user-menu-choices-for-this-class superior-class)
		  thereis
		  (when (eq (user-menu-choice-symbol? umc) label)
		    umc))))))

(define-system-rpc-access (g2-get-user-menu-choice
			    ((or (no-item) (class item)))
			    ui-client-interface)
    ((label symbol)
     (applicable-class? symbol))
  (g2-get-user-menu-choice label applicable-class?))

(defun-for-system-procedure g2-get-strict-instances-of-class (class-name)
  (cond ((class-description class-name)
	 (loop for sci being each strict-class-instance of class-name
	       collect sci into scis using eval-cons
	       finally
		 (return (allocate-evaluation-sequence scis))))
	(t
	 (stack-error cached-top-of-stack
		      "~A does not name a class"
		      class-name))))

(define-system-rpc-access (g2-get-strict-instances-of-class ((sequence)))
    ((class-name symbol))
  (g2-get-strict-instances-of-class class-name))

(defun-for-system-procedure g2-get-direct-subclasses (class-name)
  (cond ((class-description class-name)
	 (allocate-evaluation-sequence
	   (copy-list-using-eval-conses
	     (inferior-classes class-name))))
	(t
	 (stack-error cached-top-of-stack
		      "~A does not name a class"
		      class-name))))

(define-system-rpc-access (g2-get-direct-subclasses ((sequence)))
    ((class-name symbol))
  (g2-get-direct-subclasses class-name))


(defun-system-rpc (g2-enable-item (truth-value))
    ((rpc-instance system-rpc-instance)
     (item (class item)))
  (let* ((ok? (and item
		   (manually-disabled-p item)
		   (frame-may-be-enabled-or-disabled-p item))))
    (when ok?
      (funcall-method 'manually-enable item))
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list (if ok?
		     evaluation-true-value
		     evaluation-false-value)))))


(defun-system-rpc (g2-disable-item (truth-value))
    ((rpc-instance system-rpc-instance)
     (item (class item)))
  (let ((ok? (and item
		  (not (manually-disabled-p item))
		  (frame-may-be-enabled-or-disabled-p item))))
    (when ok?
      (funcall-method 'manually-disable item))
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list (if ok?
		     evaluation-true-value
		     evaluation-false-value)))))


(defun-system-rpc (g2-item-is-disabled (truth-value))
    ((rpc-instance system-rpc-instance)
     (item (class item)))
  (let* ((disabled? (manually-disabled-p item)))
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list (if disabled?
		     evaluation-true-value
		     evaluation-false-value)))))

(defun-for-system-procedure g2-change-mode-for-window (client-item new-mode)
  (multiple-value-bind (result error-string?)
      (check-and-install-new-g2-user-mode-for-login new-mode client-item)
    (declare (ignore result)) ; it's just 'new-mode' unchanged
    (cond
      ((null error-string?)
       evaluation-true-value)
      (t
       (reclaim-text-string error-string?)
       evaluation-false-value))))

(define-system-rpc-access (g2-change-mode-for-window (truth-value)
						     ui-client-interface)
    ((client-item (class ui-client-item))
     (new-mode symbol))
  (g2-change-mode-for-window client-item new-mode))


(defun-for-system-procedure g2-get-list-memberships (item)
  (loop with lists = nil
	for element in (list-elements-for-item item)
	do
    (eval-push (list-frame element) lists)
	finally
	  (return (allocate-evaluation-sequence lists))))

(define-system-rpc-access (g2-get-list-memberships ((sequence)))
    ((item (class item)))
  (g2-get-list-memberships item))

(defun-for-system-procedure g2-get-methods-defined-for-class (class-name)
  (loop with methods = nil
	for method-information in (procedure-methods-of-class class-name)
	do
    (loop for method in (cdr method-information)
	  do
      (eval-push method methods))
	finally
	  (return (allocate-evaluation-sequence (nreverse methods)))))

(define-system-rpc-access (g2-get-methods-defined-for-class ((sequence)))
    ((class-name symbol))
  (g2-get-methods-defined-for-class class-name))

(defun-for-system-procedure g2-get-methods-of-name (method-name)
  (loop with methods-found = nil
	with classes-of-procedure-method? = (and (symbolp method-name)
						 (classes-of-procedure-method method-name))
	for (class . nil) in classes-of-procedure-method?
	for class-methods? =
	(get-named-procedure-methods-for-class method-name class)
	do
    (when class-methods?
      (loop for specific-method in (cdr class-methods?)
	    do
	(eval-push specific-method methods-found)))
	finally
	  (return (allocate-evaluation-sequence (nreverse methods-found)))))
  
(define-system-rpc-access (g2-get-methods-of-name ((sequence)))
    ((method-name symbol))
  (g2-get-methods-of-name method-name))

(defun-system-rpc (g2-set-g2-state (symbol))
    ((rpc-instance system-rpc-instance)
     (desired-state symbol))
  (case desired-state
    (reset
     (when (and (or system-has-paused system-is-running)
		(not inside-breakpoint-p))
       (system-reset)))
    (paused
     (when system-is-running
       (system-pause)))
    (running
     (cond (inside-breakpoint-p
	    (return-from-breakpoint
	      (eval-cons 'g2-set-g2-state
			 rpc-instance)))		
	   (system-has-paused
	    (system-resume))
	   ((not system-is-running)
	    (system-start)))))
  (unless (and (eq desired-state 'running)
	       inside-breakpoint-p)
    (return-from-g2-set-g2-state rpc-instance)))

(defun-void return-from-g2-set-g2-state (rpc-instance)
  (let ((new-state (cond (system-is-running 'running)
			 (system-has-paused 'paused)
			 (t 'reset))))
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list new-state))))

(defun-system-rpc (g2-get-g2-state (symbol))
    ((rpc-instance system-rpc-instance))
  (let ((new-state (cond (system-is-running 'running)
			 (system-has-paused 'paused)
			 (t 'reset))))
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list new-state))))

(defun-simple normalize-specific-client (item)
  (cond ((frame-of-class-p item 'g2-window)
	 (let* ((workstation-for-g2-window?
		  (workstation-for-g2-window? item))
		(gensym-window?
		  (and workstation-for-g2-window?
		       (window-for-workstation
			 workstation-for-g2-window?))))
	   (or gensym-window?
	       (stack-error cached-top-of-stack "Invalid G2-Window ~NF"
			    item))))
	((frame-of-class-p item 'ui-client-session)
	 (and (ui-client-session-valid-p item)
	      item))
	(item
	 (stack-error cached-top-of-stack "G2-FIRE-ACTION-BUTTON called with invalid client ~NF" item))
	(t
	 (stack-error cached-top-of-stack "G2-FIRE-ACTION-BUTTON called with no client" nil))))

(defun-for-system-procedure g2-fire-action-button
    (item specific-client)
  (let* ((client-item
	   (normalize-specific-client
	     specific-client))
	 ;; NOTE: prior to providing a cap, this binding may need to be
	 ;; reviewed.
	 (current-workstation-window system-window)
	 (click-result?
	   (and (runnable-p item)
		(frame-of-class-p item 'action-button)
		system-is-running
		(fire-action-button
		  item
		  client-item))))
    (cond ((and (fixnump click-result?)
		(>=f click-result? 1)) ; number of rules scheduled
	   evaluation-true-value)
	  (t
	   evaluation-false-value))))

(define-system-rpc-access (g2-fire-action-button (truth-value) ui-client-interface)
    ((action-button (class action-button))
     (specific-client (class ui-client-session)))
  (check-ui-client-session-for-rpc-access specific-client)
  (g2-fire-action-button action-button specific-client))

(defun-for-system-procedure g2-fire-user-menu-choice
    (user-menu-choice item specific-client)
  (let ((client-item
	  (normalize-specific-client
	    specific-client)))
    (cond
      ((and (frame-of-class-p user-menu-choice 'user-menu-choice)
	    system-is-running
	    (runnable-p user-menu-choice))
       (let ((rules-scheduled?
	       (execute-user-menu-choice
		 user-menu-choice
		 item
		 (or client-item
		     system-window))))
	 (cond ((and (fixnump rules-scheduled?)
		     (>=f rules-scheduled? 1))
		evaluation-true-value)
	       (t
		evaluation-false-value))))
      (t
       evaluation-false-value))))

(define-system-rpc-access (g2-fire-user-menu-choice (truth-value)
						    ui-client-interface)
    ((user-menu-choice (class user-menu-choice))
     (item (class item))
     (specific-client (class ui-client-session)))
  (check-ui-client-session-for-rpc-access specific-client)
  (g2-fire-user-menu-choice user-menu-choice item specific-client))


(define-system-rpc-access (g2-show-workspace
			    ()
			    ui-client-interface)
    ((workspace (class kb-workspace))
     (show-details? (structure))
     (specific-client (class ui-client-session)))
  (show-workspace
    (or (evaluation-structure-slot show-details? 'item) workspace)
    specific-client
    (evaluation-structure-slot show-details? 'go-to-item)
    (evaluation-structure-slot show-details? 'symbolic-x-scale)
    (evaluation-structure-slot show-details? 'symbolic-y-scale)
    (evaluation-structure-slot show-details? 'symbolic-x-in-workspace)
    (evaluation-structure-slot show-details? 'symbolic-y-in-workspace)
    (evaluation-structure-slot show-details? 'symbolic-x-in-window)
    (evaluation-structure-slot show-details? 'symbolic-y-in-window)
    (evaluation-structure-slot show-details? 'x-offset-units)
    (evaluation-structure-slot show-details? 'symbolic-x-offset-direction)
    (evaluation-structure-slot show-details? 'y-offset-units)
    (evaluation-structure-slot show-details? 'symbolic-y-offset-direction)
    (evaluation-structure-slot show-details? 'x-magnification)
    (evaluation-structure-slot show-details? 'y-magnification)
    (evaluation-structure-slot show-details? 'x-in-workspace)
    (evaluation-structure-slot show-details? 'y-in-workspace)
    (evaluation-structure-slot show-details? 'x-in-window)
    (evaluation-structure-slot show-details? 'y-in-window)
    t;(evaluation-structure-slot show-details? 'above-or-below-or-t-for-same)
    t;(evaluation-structure-slot show-details? 'specific-workspace-or-t-for-group?)
    )
  nil)

(define-system-rpc-access (g2-hide-workspace
			    ()
			    ui-client-interface)
    ((workspace (class kb-workspace))
     (specific-client (class ui-client-session)))
  (show-or-hide workspace
		nil
		nil
		specific-client
		nil)
  nil)       


(defun-simple loose-end-connection-frame-p (connection-frame)
  (loose-end-connection-p
    (connection-for-this-connection-frame connection-frame)))

(defun-simple get-loose-end-for-loose-end-connection-frame (connection-frame)
   (let* ((connection (connection-for-this-connection-frame
		       connection-frame))
	  (connection-input (input-end-object connection))
	  (connection-output (output-end-object connection)))
     (if (loose-end-p connection-input)
	 connection-input
	 connection-output)))


;;; `move-loose-end-and-set-connection-vertices' takes a vertex list that
;;; includes the starting and ending point on the block and loose-end. This
;;; argument is compatible with the value produced from the virtual-attribute,
;;; connection-position-sequence, except that it always goes from block to loose
;;; end.  It consumes the gensym-list of gensym-consed dotted pairs of vertices
;;; it receives.

(defun move-loose-end-and-set-connection-vertices (loose-end connection
						   vertex-list-arg
						   connection-mode)
  (let* ((input (input-end-object connection))
	 (output (output-end-object connection))
	 (block (if (eq input loose-end) output input))
	 (input-end-position (input-end-position connection))
	 (output-end-position (output-end-position connection))
	 vertex-list)
    (cond
      ((eq connection-mode 'orthogonal)
       (multiple-value-bind (block-x block-y)
	   (determine-connection-terminal-coordinate
	     block (if (eq block input)
		       input-end-position
		       output-end-position))
	 (let ((vertex-list-start-x (caar vertex-list-arg))
	       (vertex-list-start-y (cdar vertex-list-arg)))
	   (unless (and (=f block-x vertex-list-start-x)
			(=f block-y vertex-list-start-y))
	     (reclaim-gensym-tree vertex-list-arg)
	     (stack-error cached-top-of-stack
			  "vertex (~NV, ~NV) does not match connection origin"
			  vertex-list-start-x
			  vertex-list-start-y))))
       (cond
	 ((eq block output)
	  (setf vertex-list (nreverse vertex-list-arg)))
	 (t
	  (setf vertex-list vertex-list-arg)))
       (let ((start-x (caar vertex-list))
	     (start-y (cdar vertex-list)))
	 (loop with deltas = '()
	       with initial-horizontal-p
		 = (if (eq block input)
		       (horizontal-end-position-p input-end-position)
		       ;; are the first two y's equal -> first segment is horiz.
		       (=f start-y (cdadr vertex-list)))
	       for prev-x = start-x then x
	       for prev-y = start-y then y
	       for (x . y) in (cdr vertex-list)
	       as horizontal-p
		  = initial-horizontal-p
		  then (not horizontal-p)
	       do
	   ;;(format t "px ~s py ~s  x ~s y ~s  h ~s ~%"
	   ;;     prev-x prev-y x  y horizontal-p)
	   ;; check orthogonality of next segment
	   (unless (if horizontal-p
		       (=f prev-y y)
		       (=f prev-x x))
	     (reclaim-gensym-tree vertex-list)
	     (reclaim-slot-value-list deltas)
	     (stack-error cached-top-of-stack
			  "non-orthogonal vertices specified"))
	   (slot-value-push (if horizontal-p
				(-f x prev-x)
				(-f y prev-y))
			    deltas)
	       finally
		 (reclaim-gensym-tree vertex-list)
		 (setf deltas (nreverse deltas))
		 (let ((workspace? (superblock? loose-end)))
		   (update-connection-images t workspace? connection)
		   (update-images-of-block loose-end t nil)
		   (cond
		     ((eq input loose-end)
		      (shift-block loose-end
				   (-w start-x (left-edge-of-block loose-end))
				   (-w start-y (top-edge-of-block loose-end)))
		      (setf (input-end-position connection)
			    (if initial-horizontal-p 1 0)))
		     (t
		      (shift-block loose-end
				   (-w x (left-edge-of-block loose-end))
				   (-w y (top-edge-of-block loose-end)))
		      (setf (output-end-position connection)
			    (if horizontal-p 1 0))))
		   (setf (delta-or-deltas connection) deltas)
		   (remove-redundant-deltas-from-connection connection)
		   (update-images-of-block loose-end nil nil)
		   (update-connection-images nil workspace? connection)
		   (return t)))))
      (t;(eq connection-mode 'diagonal)
       (multiple-value-bind (block-x block-y)
	   (determine-connection-terminal-coordinate
	     block (if (eq block input)
		       input-end-position
		       output-end-position))
	 (let ((vertex-list-start-x (caar vertex-list-arg))
	       (vertex-list-start-y (cdar vertex-list-arg)))
	   (unless (and (=f block-x vertex-list-start-x)
			(=f block-y vertex-list-start-y))
	     (reclaim-gensym-tree vertex-list-arg)
	     (stack-error cached-top-of-stack
			  "vertex (~NV, ~NV) does not match connection origin"
			  vertex-list-start-x
			  vertex-list-start-y))))
       (cond
	 ((eq block output)
	  (setf vertex-list (nreverse vertex-list-arg)))
	 (t
	  (setf vertex-list vertex-list-arg)))
       (let ((start-x (caar vertex-list))
	     (start-y (cdar vertex-list)))
	 (loop with deltas = '()
	       with initial-horizontal-p
		 = (if (eq block input)
		       (horizontal-end-position-p input-end-position)
		       (horizontal-end-position-p output-end-position))
	       for prev-x = start-x then x
	       for prev-y = start-y then y
	       for (x . y) in (cdr vertex-list)
	       as horizontal-p
		  = initial-horizontal-p
		  then (not horizontal-p)	       
	       do
	   (slot-value-push (if initial-horizontal-p
				(-f x prev-x)
				(-f y prev-y))
			    deltas)
	   (slot-value-push (if (not initial-horizontal-p)
				(-f x prev-x)
				(-f y prev-y))
			    deltas)
	       finally
		 (reclaim-gensym-tree vertex-list)
		 (setf deltas (nreverse deltas))
		 (let ((workspace? (superblock? loose-end)))
		   (update-connection-images t workspace? connection)
		   (update-images-of-block loose-end t nil)
		   (cond
		     ((eq input loose-end)
		      (shift-block loose-end
				   (-w start-x (left-edge-of-block loose-end))
				   (-w start-y (top-edge-of-block loose-end)))
		      (setf (input-end-position connection)
			    (if initial-horizontal-p 1 0)))
		     (t
		      (shift-block loose-end
				   (-w x (left-edge-of-block loose-end))
				   (-w y (top-edge-of-block loose-end)))
		      (setf (output-end-position connection)
			    (if horizontal-p 1 0))))
		   (setf (delta-or-deltas connection) deltas)
		   (remove-redundant-deltas-from-connection connection)
		   (update-images-of-block loose-end nil nil)
		   (update-connection-images nil workspace? connection)
		   (return t))))))))

(defun-simple decode-connection-position-sequence (sequence)
  (loop with x = 0
	with res = '()
        for coordinate being each evaluation-sequence-element of sequence
	as horizontal-p = t then (not horizontal-p)
	do
    (cond (horizontal-p
	   (setf x coordinate))
	  (t
	   (gensym-push (gensym-cons x (-f coordinate))
			res)))
	finally
	  (return (nreverse res))))

(defun-for-system-procedure g2-make-connection-for-user
    (loose-end-connection other-item mode-ev
			  connection-position-sequence
			  specific-client-or-false)
  (let* ((connection (connection-for-this-connection-frame
		       loose-end-connection))
	 (specific-client?
	   (cond
	     ((of-class-p specific-client-or-false 'g2-window)
	      specific-client-or-false)
	     (current-system-rpc-icp-socket?
	      (enclosing-interface-frame?
		current-system-rpc-icp-socket?))
	     (t
	      (stack-error cached-top-of-stack
			   "must supply window/ui-client-interface"))))
	 (connection-style (connection-style loose-end-connection))
	 (mode (prog1 (evaluation-symbol-symbol mode-ev)
		 (reclaim-evaluation-symbol mode-ev)))
	 loose-end vertex-list
	 end-dragging-p connection-type connection-was-not-made-p
	 joined-connection original-x-position original-y-position)
    
    (cond
     ((and (not (eq mode 'moving-loose-end))
	   (not (framep other-item)))
      (stack-error cached-top-of-stack
		   "~NV must be an item"))
     ((loose-end-connection-frame-p loose-end-connection)
      (setf loose-end
	    (get-loose-end-for-loose-end-connection-frame
	      loose-end-connection))
      (setf vertex-list
	    (decode-connection-position-sequence connection-position-sequence))
      (setf original-x-position (item-x-position loose-end))
      (setf original-y-position (item-y-position loose-end)))
     (t
      (stack-error cached-top-of-stack
		   "~NF is not a loose-end connection"
		   loose-end-connection)))
    
    (case mode
      (joining-loose-ends
       (setq connection-type 'joined-connections)
       (unless (loose-end-connection-frame-p other-item)
	 (stack-error cached-top-of-stack
		      "other item ~NF must be a loose end for ~A"
		      other-item
		      mode))
       (move-loose-end-and-set-connection-vertices
	 loose-end
	 connection
	 vertex-list
	 connection-style)
       (let ((other-loose-end
	       (get-loose-end-for-loose-end-connection-frame other-item)))
	 (multiple-value-setq (end-dragging-p joined-connection)
	   ;; (values t connection)
	   (join-two-connections loose-end other-loose-end))
	 (unless end-dragging-p
	   (stack-error cached-top-of-stack
			"Incompatible directions or cross-sections joining ~NF to ~NF"
			loose-end-connection other-item))))
      
      (dragging-loose-end-into-item
       (setq connection-type 'added-connection-to-block)
       (when (or (loose-end-p other-item)
		 (connection-frame-p other-item)
		 (no-manual-connections-p other-item)) ; new, missing before! (MHD 5/14/02)
	 (stack-error cached-top-of-stack
		      "~NF is not an item that accepts connections"
		      other-item))
       (move-loose-end-and-set-connection-vertices
	 loose-end
	 connection
	 vertex-list
	 connection-style)
       (multiple-value-setq (end-dragging-p connection-was-not-made-p)
	 (add-new-connection-to-block loose-end other-item))
       (when (and g2-has-v5-mode-windows-p
		  (not connection-was-not-made-p))
	 (send-ws-representations-connection-moved connection)))

      (making-new-junction-block
       (setq connection-type 'made-junction)
       (unless (connection-frame-p other-item)
	 (stack-error cached-top-of-stack
		      "~NF is not a connection"
		      other-item))
       (move-loose-end-and-set-connection-vertices
	 loose-end
	 connection
	 vertex-list
	 connection-style)
       (let ((other-connection
	       (connection-for-this-connection-frame other-item)))
	 ;; where to move.
	 (setq end-dragging-p
	       (make-junction other-connection loose-end))
	 (when (and g2-has-v5-mode-windows-p)
	   (send-ws-representations-connection-moved connection)
	   (send-ws-representations-connection-moved other-connection))))

      (moving-loose-end
       (setq connection-was-not-made-p t)
       (move-loose-end-and-set-connection-vertices
	 loose-end
	 connection
	 vertex-list
	 connection-style)
       (when (and g2-has-v5-mode-windows-p)
	   (send-ws-representations-connection-moved connection)))

      (t
       (reclaim-gensym-tree vertex-list)
       (stack-error cached-top-of-stack
		    "unknown mode ~A"
		    mode)))

    (when connection-was-not-made-p
      (setf connection-type
	    (if (eq mode 'moving-loose-end)
		'moved-loose-end
		'deleted-stub)))

    (when end-dragging-p
      #+ignore
      (trigger-user-icon-movement-rules-for-blocks connection-frame?)
      
      ;; G2 4.0 (secret for GDA) connection-handling protocol
      (invoke-connection-handler-if-any
	(if connection-was-not-made-p other-item connection)
	specific-client?
	connection-type
	(and (not connection-was-not-made-p)
	     (eq connection-type 'added-connection-to-block)
	     other-item))

      ;; G2 5.0 standard connection chaining.
      (unless connection-was-not-made-p
	(case connection-type
	  (added-connection-to-block
	   (invoke-rules-for-direct-connection-chaining connection nil)
	   (invoke-rules-for-indirect-connection-chaining connection nil))
	  (joined-connections
	   (invoke-rules-for-direct-connection-chaining joined-connection nil)
	   (invoke-rules-for-indirect-connection-chaining joined-connection nil))
	  (made-junction
	   (invoke-rules-for-indirect-connection-chaining connection nil)))))))

(define-system-rpc-access (g2-make-connection-for-user ())
    ((loose-end-connection (class connection))
     (other-item item-or-datum)
     (mode symbol)
     (position-sequence (sequence));(sequence integer))
     (specific-client-or-false item-or-datum))
  (g2-make-connection-for-user
    loose-end-connection other-item mode position-sequence
    specific-client-or-false))
       
(define-system-rpc-access (g2-get-connection-input-and-output ((sequence)))
    ((connection (class connection)))
  (multiple-value-bind (input output)
      (g2-get-connection-input-and-output connection)
    (allocate-evaluation-sequence (eval-list input output))))


;;; This rpc is part of the security code. The X-authorized-p forms
;;; are macros that return integers or nil. Calls to it should be
;;; buried in the C code of the module involved, in a way that
;;; makes it look innocent (thence obscure) and several steps removed
;;; from the code that acts on the yes-or-no authorization information
;;; this provides.

(defun-system-rpc (g2-confirm-available-handles-by-type (integer))
    ((rpc-instance system-rpc-instance)
     (type symbol))
  (let ((value
	  (case type
	    (window (jl-authorized-p))
	    (popup (jp-authorized-p))
	    (radio (al-authorized-p))
	    (otherwise nil))))
    (unless value
      (setq value 0)) ;; conversion to convenient C value
    (return-from-system-defined-rpc
      rpc-instance (eval-list value))))




;;;; AB-->NTW notification senders


;; based on with-ws-notification
;;; sends the result of body as the third argument to the remote
;;; tc-representation-callback-procedure.
;;; NOTE: (Recursively) reclaims the *result* of body iff the body was evaluated.
;;; Only evaluates the body if there is at least one 'tc-representation in the
;;; frame-representations of item. Any allocations made in the body will only be
;;; reclaimed if those allocations are incorporated into the body result value.
;;; RETURNS: T is the body is evaluated, NIL otherwise.

(defmacro with-trend-chart-notification
    ((item notification-type)
     &body body)
  (avoiding-variable-capture (&aux representation representations address argument-list
				   current-frame-serial-number-on-entry subscription-handle socket
				   body-evaluated-p
				   notification-body)
    `(let ((,body-evaluated-p nil)
	   (,notification-body nil))
       (loop with ,representations = (collect-frames-of-class (frame-representations ,item)
							      'tc-representation)
	     with ,current-frame-serial-number-on-entry = (copy-frame-serial-number (current-frame-serial-number))
	     for ,representation in ,representations
	     do
	 (when (and (not (frame-has-been-reprocessed-p ,representation
						       ,current-frame-serial-number-on-entry))
		    (representation-address-valid-p ,representation))
	   (unless ,body-evaluated-p
	     (setf ,notification-body (progn ,@body))
	     (setf ,body-evaluated-p t))
	   (let* ((,address (representation-address ,representation))
		  (,subscription-handle
		     (callback-representation-callback-subscription-handle
		       ,representation))
		  (,socket (getf ,address 'socket))
		  (,argument-list
		     (eval-list
		       ,subscription-handle
		       ,item
		       (make-evaluation-symbol ,notification-type)
		       (copy-if-evaluation-value ,notification-body))))
	     (callback-representation-fire-callback ,representation ,socket ,argument-list)))
	     finally
	       (reclaim-frame-serial-number ,current-frame-serial-number-on-entry)
	       (reclaim-gensym-list ,representations)
	       (when ,body-evaluated-p
		 (reclaim-if-evaluation-value ,notification-body))
	       (return ,body-evaluated-p)))))

;;; returns the first valid representation of ITEM of class
;;; REPRESENTATION-CLASS-NAME, or NIL if there are none.
(defun-simple item-has-remote-representation-p (item representation-class-name)
  (loop for representation in (frame-representations item)
    if (and (frame-of-class-p representation representation-class-name)
	    (representation-address-valid-p representation))
      return representation))

;;; This would like to be more general: It should use copy-evaluation-value,
;;; and will in the next release. Is designed to build a tree of
;;; evaluation-sequences from a tree of lists. Does not consume its arguments.
(defun-simple make-nested-evaluation-value-based-on-type (tree)
  (cond ((not (listp tree)) (make-evaluation-value-based-on-type tree))
	(t (let ((list-of-sequences
		   (loop for element in tree
			 collect (make-nested-evaluation-value-based-on-type element)
			 using eval-cons)))
	     (allocate-evaluation-sequence list-of-sequences)))))

;;; This includes plot data, and changes to time bounds and value axes.

(defun-allowing-unwind send-new-trend-chart-data (trend-chart trend-chart-data)
  (with-trend-chart-notification (trend-chart 'general-update)
    trend-chart-data))
      
(defun-allowing-unwind send-trend-chart-activation-deactivation
    (trend-chart is-activation)
  (with-trend-chart-notification (trend-chart 'activation)
    (allocate-evaluation-structure-inline
      'activation-value
      (make-evaluation-boolean-value is-activation))))

(defun-allowing-unwind send-trend-chart-update-for-clock-discontinuity (trend-chart delta)
  (with-trend-chart-notification (trend-chart 'clock-discontinuity)
    (allocate-evaluation-structure-inline
      'timespan-info (collect-time-bounds trend-chart nil t)
      'initial-plot-data (get-current-plot-data trend-chart nil t)
      'time-delta (make-evaluation-value-based-on-type delta))))


;;; MOVED `with-workspace-notification' to TABLES.lisp

(defun-allowing-unwind send-ws-representations-item-icon-variables-change
    (item new-variables)
  (do-javalink-notification ((get-workspace-if-any-for-block-or-connection item)
			     'ws-representation)
    (send-versioned-ws-notification-internal 'item-icon-variables-change
				    item
				    (copy-if-evaluation-value new-variables))))

;;; Definition of `send-ws-representations-item-moved'
;;; Used by 'change-edges-of-block

(defun-simple send-ws-representations-item-moved-internal
    (item path? x-offset y-offset interval? return-rpc-name? id?)
  (send-versioned-ws-notification-internal
    'item-move
    item
    (let ((bounds
	    (or (get-bounds-of-thing item)
		(allocate-evaluation-structure-inline))))
      (when path?
	(set-evaluation-structure-slot-macro bounds 'path (copy-if-evaluation-value path?))
	(set-evaluation-structure-slot-macro bounds 'x-offset (copy-if-evaluation-value x-offset))
	(set-evaluation-structure-slot-macro bounds 'y-offset (copy-if-evaluation-value y-offset))
	(set-evaluation-structure-slot-macro bounds 'interval (copy-if-evaluation-value interval?))
	(set-evaluation-structure-slot-macro bounds 'id (copy-if-evaluation-value id?))	
	(set-evaluation-structure-slot-macro bounds 'return-rpc-name return-rpc-name?))
      
      bounds)))
					     
(defun-allowing-unwind send-ws-representations-item-moved-aux
    (item path? x-offset y-offset interval? return-rpc-name? id?)
  (send-ws-representations-item-moved-internal
    item path? x-offset y-offset interval? return-rpc-name? id?)
    (loop with connections
	    = (connections-moved-for-blocks-moved item)
	  for connection in connections
	  do
      (unless (symbolp connection)
	(send-ws-representations-connection-moved-internal
	  connection nil nil nil nil))
	  finally
	    (reclaim-gensym-list connections))
    (when (not ws-protocol-handle-moves-from-edge-change-p)
      (loop for subblock being each subblock of item
	    as x-offset-sub = (if path? (-w (vertical-midline-of-block subblock)
					    (vertical-midline-of-block item))
			      0)
	    as y-offset-sub = (if path? (-w (horizontal-midline-of-block item)
					    (horizontal-midline-of-block subblock))
			      0)
	    do
	(when (or (frame-of-class-p subblock 'name-box)
		  (frame-of-class-p subblock 'table))
	  (send-ws-representations-item-moved-aux
	    subblock path? (+f x-offset x-offset-sub) (+f y-offset y-offset-sub) interval? nil nil)))))

(defun-allowing-unwind send-ws-representations-item-moved (item delta-x delta-y)
  (declare (ignore delta-x delta-y))
  (do-javalink-notification ((get-workspace-if-any-for-block-or-connection item)
			     'ws-representation)
    (send-ws-representations-item-moved-aux item nil 0 0 nil nil nil)))
	      
(defun-simple send-ws-representations-connection-moved-internal
    (connection path? interval? return-rpc-name? id?)
  ;;(format-when-tracing-in-events-modules "MOVING A CONNECTION~s~%" connection)
  (send-versioned-ws-notification-internal
    'item-move
    (if (connectionp connection)
	(get-or-make-connection-frame-and-activate-if-appropriate connection)
	connection)
    (if path?
	(allocate-evaluation-structure-inline
	  'tw-workspace-item-position
	  (get-position-of-thing connection)
	  'path (copy-if-evaluation-value path?)
	  'interval (copy-if-evaluation-value interval?)
	  'id id?
	  'return-rpc-name return-rpc-name?)
	(allocate-evaluation-structure-inline
	  'tw-workspace-item-position
	  (get-position-of-thing connection)))))

(defun-allowing-unwind send-ws-representations-connection-moved (connection)
  (do-javalink-notification ((get-workspace-if-any-for-block-or-connection connection)
			     'ws-representation)
    (send-ws-representations-connection-moved-internal connection nil nil nil nil)))

;;; Definition of `send-ws-representations-item-resized'
;;; Used by 'change-edges-of-block

(defun-allowing-unwind send-ws-representations-item-resized
    (item new-left new-top new-right new-bottom)
  (do-javalink-notification ((get-workspace-if-any-for-block-or-connection item)
			     'ws-representation)
    (send-versioned-ws-notification-internal
      'item-resize
      item
      (allocate-evaluation-structure-inline
	'left new-left
	'top (-f new-top)
	'right new-right
	'bottom (-f new-bottom)))))

;;; Definition of `send-ws-representations-item-rotated'

(defun-allowing-unwind send-ws-representations-item-rotated
    (item new-rotation)
  (unless (workspace-p item) ;paranoid aren't we
    (do-javalink-notification ((get-workspace-if-any-for-block-or-connection item)
			       'ws-representation)
      (send-versioned-ws-notification-internal
	'item-rotate
	item
	(allocate-evaluation-structure-inline
	  'new-rotation
	  (or new-rotation 'normal))))))

;;; Definition of `send-ws-representations-item-rotated'

(defun-allowing-unwind send-ws-representations-item-color-pattern-change
    (item specific-region? color-or-pattern)
  (do-javalink-notification ((get-workspace-if-any-for-block-or-connection item)
			     'ws-representation)
    (send-versioned-ws-notification-internal
      'item-color-pattern-change
      item
      (allocate-evaluation-structure-inline
	'color-pattern-changes
	(if (symbolp color-or-pattern)
	    (allocate-evaluation-structure-inline
	      specific-region?
	      color-or-pattern)
	    (export-color-pattern color-or-pattern))))))

(defun-simple item-or-connection-being-deleted-p (thing)
  (cond ((framep thing)
	 (or (frame-being-deleted-p thing)
	     (and (connection-frame-p thing)
		  (connection-being-deleted-p
		    (connection-for-this-connection-frame thing)))))
	((connectionp thing)
	 (connection-being-deleted-p thing))))



(defun-allowing-unwind send-ws-representations-item-layer-change
    (thing parent-of-thing? position-or-next-lower-thing)
  (let* ((should-be-wksp-thing (or (get-workspace-if-any-for-block-or-connection thing)
				   parent-of-thing?))
	 (useable-position-or-next-lower-thing
	   (find-non-loose-end-below-thing
	     thing should-be-wksp-thing position-or-next-lower-thing)))
    (do-javalink-notification (should-be-wksp-thing
				'ws-representation)
      (javalink-version-case
	(t2-supports-item-layer-change
	  (send-ws-representations-item-insert-or-change-layer-aux
	    thing useable-position-or-next-lower-thing nil))
	(t
	  (send-ws-representations-item-remove-as-subblock-aux thing)
	  (send-ws-representations-item-insert-or-change-layer-aux
	    thing useable-position-or-next-lower-thing t))))))

(defun-simple find-non-loose-end-below-thing
    (thing parent-of-thing? position-or-next-lower-thing)
  (when (and (framep position-or-next-lower-thing)
	     (loose-end-p position-or-next-lower-thing))
    (let ((subblocks (nreverse (copy-subblocks-using-slot-value-conses
				 (subblocks (or (get-workspace-if-any-for-block-or-connection thing)
						parent-of-thing?))))))
      (setf position-or-next-lower-thing
	    (find-next-non-loose-end (memq position-or-next-lower-thing
					   subblocks)))
      (reclaim-slot-value-list subblocks)))
  position-or-next-lower-thing)

(defun-simple send-item-remove-as-subblock-internal (thing)
  (send-versioned-ws-notification-internal 'item-remove thing nil))

(defun-simple send-layer-change-for-item-internal
    (thing position-or-next-lower-thing)
  (send-versioned-ws-notification-internal 'item-layer-change
				  thing
				  (allocate-evaluation-structure-inline
				    'position-or-next-lower-item
				    position-or-next-lower-thing)))

(defun-simple send-insert-for-item-internal
    (thing position-or-next-lower-thing)
  (let ((info (get-thing-initial-info thing)))
    (setf (evaluation-structure-slot
	    info 'position-or-next-lower-item)
	  position-or-next-lower-thing)
    (send-versioned-ws-notification-internal 'item-insert thing info)))  

(defun-allowing-unwind send-ws-representations-item-insert-or-change-layer-aux
    (thing position-or-next-lower-thing for-insert-p)
  (if for-insert-p
      (send-insert-for-item-internal thing position-or-next-lower-thing)
      (send-layer-change-for-item-internal thing position-or-next-lower-thing))
  (let* ((children (children-of-thing thing t))
	 (item-like-children
	   (item-like-children children))
	 (first-child (car item-like-children))
	 (first-lower-item-or-position
	   (if (and (framep thing)
		    (loose-end-p thing))
	       position-or-next-lower-thing
	       thing)))
    (when first-child
      (send-ws-representations-item-insert-or-change-layer-aux first-child first-lower-item-or-position for-insert-p))
    (loop with last-non-loose-end = first-lower-item-or-position
	  for (child1 child2) on item-like-children
	  do
      (when (not (and (framep child1)
		      (loose-end-p child1)))
	(setf last-non-loose-end child1))
      (when child2
	(send-ws-representations-item-insert-or-change-layer-aux child2 last-non-loose-end for-insert-p)))
    (reclaim-gensym-list children)
    (reclaim-gensym-list item-like-children)))

;;; Definition of `send-ws-representations-item-insert-as-subblock'
;;; If the item has subblocks then each subblock is recursively inserted
;;; as a subblock, in a way that preserves z-positions.  Valid for any depth
;;; of subblock containment.
;;; Reclaims its local variable 'item-initial-info.
;;; Uses new auxiliary functions 'get-item-initial-info and
;;; 'get-all-rows-of-table-as-text
;;; Used by 'add-subblock and 'primitive-insert-as-subblock

(defun-allowing-unwind send-ws-representations-item-insert-as-subblock
    (thing parent-of-thing? position-or-next-lower-thing)
  (if transfer-in-progress
      (setf saved-position-or-next-lower-thing position-or-next-lower-thing)
      (let* ((should-be-wksp-thing (or (get-workspace-if-any-for-block-or-connection thing)
				       parent-of-thing?))
	     (useable-position-or-next-lower-thing
	       (find-non-loose-end-below-thing
		 thing should-be-wksp-thing position-or-next-lower-thing)))
	(do-javalink-notification (should-be-wksp-thing
				    'ws-representation)
	  (send-ws-representations-item-insert-or-change-layer-aux
	    thing useable-position-or-next-lower-thing t)))))


;; Not sure if 'item-specific-info is being reclaimed (if it was a list)
;; through the reclamation  of item-initial-info.
;; Should check that next-lower-item is on the same workspace, as a precaution.

(defun send-ws-representations-remove-connections-of-block (block)
  (loop for connection being each connection of block do
    (send-ws-representations-item-remove-as-subblock
      connection block)))
      
(defun-allowing-unwind send-ws-representations-item-remove-as-subblock-aux
    (thing)
  (send-versioned-ws-notification-internal 'item-remove thing nil)
  (loop with children = (children-of-thing thing t)
	with item-like-children = (item-like-children children)
	for child in item-like-children
	do
    (send-ws-representations-item-remove-as-subblock-aux child)
	  finally
	    (reclaim-gensym-list children)
	    (reclaim-gensym-list item-like-children)))

;;; Definition of `send-ws-representations-item-remove-as-subblock'
;;; Used by 'remove-as-subblock  and 'primitive-remove-as-subblock

(defun-allowing-unwind send-ws-representations-item-remove-as-subblock
    (thing parent-of-thing?)
  (do-javalink-notification ((or parent-of-thing?
				 (get-workspace-if-any-for-block-or-connection thing))
			     'ws-representation)
    (send-ws-representations-item-remove-as-subblock-aux thing)))

(defun-allowing-unwind send-ws-representations-item-virtual-attribute-change
    (item virtual-attribute sub-denotation?)
  (declare (ignore sub-denotation?))
  (do-javalink-notification ((get-workspace-if-any-for-block-or-connection item)
			     'ws-representation)
    (send-versioned-ws-notification-internal
      'item-change
      item
      (let* ((new-value
	       (get-virtual-attribute item virtual-attribute))
	     (attribute-name (virtual-attribute-name virtual-attribute))
	     (update-info
	       (allocate-evaluation-structure-inline
		 'attribute-name
		 attribute-name
		 'new-value
		 new-value)))
	update-info))))
	    



#+gesture-definition-facilities
(progn
;;;; HAX

(add-grammar-rules
  '((new-gesture-expression
     ('experiment unique-expression)
     (unique-expression 2))
    (new-gesture-expression
     ('logical logical-expression)
     (logical-expression 2))
    (new-gesture-expression
     ('prototype-1 gesture-prototype-1))
    (new-gesture-expression
     ('prototype-2 gesture-prototype-2))))

(def-slot-value-compiler new-gesture-expression (parse-result gesture)
  (declare (ignore gesture))
  (pprint-when-tracing-in-events-modules parse-result)
  (let ((simplified-parse (simplify-gesture-parse parse-result)))
    (pprint-when-tracing-in-events-modules simplified-parse)
    simplified-parse))

)  ; end #+gesture-definition-facilities






;;;; RPC based API for parsing

;;; These RPCs are basically just packaging shells around calls to the
;;; workhorse functions in the corresponding section of EDIT2.  The
;;; one exception is `g2-update-parsing-context', the primary entry point
;;; once the parsing has started, which has to do a fair amount of
;;; calculation in order to set up its calls and also does some work
;;; to determine which token to use when returning prompt information.


(defvar highest-parsing-context-handle 0)
(defvar current-parsing-contexts nil)

(defun get-parsing-context (handle)
  (cond ((fixnump handle)
	 (cdr (assq handle current-parsing-contexts)))
	((parsing-context-p handle)
	 handle)
	(t nil)))
  

(defun remove-parsing-context (handle-or-pc)
  (cond ((fixnump handle-or-pc)
	 (let ((parsing-context-pair? (assq handle-or-pc current-parsing-contexts)))
	   (when parsing-context-pair?
	     (let ((pc (cdr parsing-context-pair?)))
	       (setf current-parsing-contexts
		     (delete-gensym-element parsing-context-pair? current-parsing-contexts))
	       (reclaim-gensym-cons parsing-context-pair?)
	       (reclaim-parsing-context pc)))))
	(t (reclaim-parsing-context handle-or-pc))))


;;; This provides a means of determining whether we are in the scope
;;; of the editor-less parsing interface as entered from the rpcs
;;; in this section. It is bound in every rpc that uses the interface.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar current-parsing-context? nil))


(defvar testing-parsing-context-locally-p nil)

(defun maybe-return-from-system-defined-rpc (rpc-instance eval-list)
  (cond
    (testing-parsing-context-locally-p
     (format-when-tracing-in-events-modules "ret=~s ~%" eval-list))
    (t
     (return-from-system-defined-rpc
       rpc-instance eval-list))))


(defmacro invalid-parsing-context-handle (parsing-context-handle)
  `(stack-error cached-top-of-stack
		"There is no parsing-context for handle ~d."
		,parsing-context-handle))

(defmacro return-error-values (message &rest args)
  (let ((error-message (gensym)))
    `(let ((,error-message (tformat-text-string ,message ,@args)))
       (values nil ;ok
	       nil ;endable-p
	       nil ;longest-common-completion
	       nil ;category-choices
	       nil ;completion-choices
	       nil ;token-complete-p
	       nil ;null token-data means we are so hosed.
	       ,error-message))))



;;; `G2-create-parsing-context' is the entry point for creating
;;; a parsing context. The minimum requirement is the name of the category
;;; to be parsed against. If that is supplied, it will be preferred over
;;; the combination of a class, slot (attribute), and (if needed) a qualifying
;;; class from which the category will otherwise be derived. 
;;;
;;; It has a parsing context set up, cranks it over once to get some state
;;; from which to generate initial prompts, and then packages the handle to
;;; the parsing context and the prompt and status information up and passes
;;; it back. No status information about a possible bad parse is included
;;; on the assumption that that could never happen.  If it doesn't get a
;;; slot description (in the class + slot case) or the slot cannot be edited
;;; in the current configuration it returns false.


;; To Do: supply symbols that distinguish the various error conditions
;; once there is a 'note to the user' element in the text-editor UI.

(defun-system-rpc (g2-create-parsing-context (datum))
    ((rpc-instance system-rpc-instance)
     (grammar-category? datum)
     (class-name? datum)
     (attribute-name? datum)
     (slot-component-name? datum)
     (slot-component-indicator? datum))

  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-create-parsing-context 'ui-client-interface)
    ;; Clean up unused arguments
    (unless (symbolp grammar-category?)
      (reclaim-evaluation-value grammar-category?)
      (setf grammar-category? nil))
    (unless (symbolp class-name?)
      (reclaim-evaluation-value class-name?)
      (setf class-name? nil))
    (unless (symbolp attribute-name?)
      (reclaim-evaluation-value attribute-name?)
      (setf attribute-name? nil))
    (unless (symbolp slot-component-name?)
      (reclaim-evaluation-value slot-component-name?)
      (setf slot-component-name? nil))
    (unless (symbolp slot-component-indicator?)
      (reclaim-evaluation-value slot-component-indicator?)
      (setf slot-component-indicator? nil))
    
    (let* ((pretty-slot-name?
	     (when (and attribute-name? class-name?)
	       (unalias-slot-name-if-necessary attribute-name? class-name?)))
	   (slot-description?
	     (when (and attribute-name? class-name?)
	       (get-slot-description-of-class-description
		 pretty-slot-name? (class-description class-name?))))
	   (type-when-editable?
	     (when slot-description?
	       (type-slot-feature-assq-if-editable
		 (slot-features slot-description?)))))
      
      (cond
	((not (or grammar-category?
		  (and class-name? attribute-name?)))
	 #+development
	 (when trace-parsing-context-p
	   (format t "~3%==============================================~
                    ~%==============================================~
                    ~%Attempted to create a parsing context~
                    ~%   But no class/slot combination or category ~
                    was passed in -- bad call."))
	 (maybe-return-from-system-defined-rpc
	   rpc-instance (eval-list evaluation-false-value)))
	
	((and (null grammar-category?)
	      (null slot-description?))
	 #+development (when trace-parsing-context-p
			 (format t "~3%==============================================~
                    ~%==============================================~
                    ~%Attempted to create a parsing context~
                    ~%   for the ~a of a ~a class
                    ~%   But there is no such slot on that class~%~%"
				 attribute-name? class-name?))
	 (maybe-return-from-system-defined-rpc
	   rpc-instance (eval-list evaluation-false-value)))
	
	((and (null grammar-category?)
	      slot-description?
	      (null type-when-editable?))
	 #+development (when trace-parsing-context-p
			 (format t "~3%==============================================~
                    ~%==============================================~
                    ~%Attempted to create a parsing context~
                    ~%   for the ~a of a ~a class
                    ~%   But the slot ~a is not editable~%~%"
				 attribute-name? class-name? pretty-slot-name?))
	 (maybe-return-from-system-defined-rpc
	   rpc-instance (eval-list evaluation-false-value)))
	
	(t
	 (let ((pc nil) (type-to-use nil) (construct-the-type? nil)
	       (index (incff highest-parsing-context-handle)))
	   
	   #+development (when trace-parsing-context-p
			   (format t "~3%==============================================~
                      ~%==============================================~
                      ~%Created parsing context #~a" index))
	   
	   (cond
	     ((and grammar-category?   ;; just the category
		   (not class-name?))
	      #+development (when trace-parsing-context-p
			      (format t "~%   for the category ~a" grammar-category?))
	      (setq construct-the-type? t)
	      (setq type-to-use (gensym-list 'type grammar-category?)) ; Leaks
	      (setq pc (create-parsing-context
			 nil nil
			 type-to-use
			 nil nil)))
	     
	     (t
	      (when (and grammar-category?   ;; prefer the category?
			 type-when-editable?)
		(setq construct-the-type?
		      (eq grammar-category?
			  (category-symbol-given-slot-type type-when-editable?)))
		(setq type-to-use
		      (if construct-the-type?
			  type-when-editable?
			  (gensym-list 'type grammar-category?))))
	      
	      #+development (when trace-parsing-context-p
			      (format t "~%  for the ~a of a ~a~3%"
				      pretty-slot-name? class-name?)
			      (when construct-the-type?
				(format t "    but using the grammar of ~a~%"
					grammar-category?)))
	      
	      (setq pc (create-parsing-context
			 class-name? pretty-slot-name?
			 type-to-use
			 slot-component-name? slot-component-indicator?))))
	   
	   (gensym-push (gensym-cons index pc)
			current-parsing-contexts)
	   
	   (return-from-parsing-context-creation
	     pc index rpc-instance)))))))


;; This (below) is broken out just to avoid yet more right-margin creep

(defun return-from-parsing-context-creation
      (current-parsing-context? index rpc-instance)  ; using "?" form as per global variable above
  (cond
    ((not (free-text-slot-being-edited? current-parsing-context?))
     
     (let ((start-token (parsing-context-start-token current-parsing-context?)))
       (within-parsing-context (current-parsing-context?)
	 (update-parsing-context-completions-as-appropriate start-token nil nil))

       #+development (when trace-parsing-context-p
	 (format t "~%   start-token: ~a~%"
		 start-token))
       
       (multiple-value-bind (category-choices completion-choices
					      longest-common-completion? can-end?)
	   (compute-parsing-context-prompts start-token)
	 
	 (maybe-return-from-system-defined-rpc
	   rpc-instance
	   (eval-list
	     (allocate-evaluation-structure-inline
	       'parsing-context-handle
	       index
	       'endable-p
	       (make-evaluation-boolean-value can-end?)
	       'longest-common-completion
	       (or longest-common-completion? evaluation-false-value)
	       'completion-choices
	       (allocate-evaluation-sequence
		 (copy-list-using-eval-conses completion-choices))
	       'category-choices
	       (allocate-evaluation-sequence
		 (copy-list-using-eval-conses category-choices))))))))

    ;; free text case (item and also individual fields)
    (t
     (maybe-return-from-system-defined-rpc
       rpc-instance
       (eval-list
	 (allocate-evaluation-structure-inline
	   'parsing-context-handle
	      index
	   'endable-p
	      evaluation-true-value
	   'longest-common-completion
	      evaluation-false-value
	   'completion-choices
	      (allocate-evaluation-sequence nil)
	   'category-choices
	      (allocate-evaluation-sequence nil)))))))

(defun-system-rpc (g2-simple-create-parsing-context (datum))
    ((rpc-instance system-rpc-instance)
     (item (class item))
     (attribute-name datum))
  (maybe-return-from-system-defined-rpc
    rpc-instance
    (eval-list (g2-simple-create-parsing-context item attribute-name))))


(defun-for-system-procedure g2-simple-create-parsing-context ((item item) (attribute-name symbol))
  (declare (values integer)
	   (keeps-g2-local-variables-valid t))
  (let ((pc (simple-create-parsing-context item attribute-name))
	(index (incff highest-parsing-context-handle)))
    (gensym-push (gensym-cons index pc)
		 current-parsing-contexts)
    index))


(defun simple-create-parsing-context (item attribute-name)
  (let* ((class-name (class item))
	 (pretty-slot-name
	   (unalias-slot-name-if-necessary attribute-name class-name))
	 (slot-description?
	   (get-slot-description-of-class-description
	     pretty-slot-name (class-description class-name)))
	 (type-when-editable
	   (when slot-description?
	     (type-slot-feature-assq-if-editable
	       (slot-features slot-description?))))
	 pc)

    (unless slot-description?
      (stack-error cached-top-of-stack
		   "Cannot create parsing context for item ~NF, attribute ~a"
		   item attribute-name))

    (setq pc (create-parsing-context
	       class-name pretty-slot-name
	       type-when-editable
	       nil nil))

    (set-frame-being-edited pc item)
    
    ;;jv says get-text-of-attribute may not be the best solution.

    (setf (parsing-context-text-string pc)
	  (get-text-of-attribute item pretty-slot-name class-name))

    pc))


(defun-for-system-procedure g2-validate-parsing-text ((class-name symbol) (attribute-name symbol) (the-text text))
  (declare (values structure))
  (let* ((pretty-slot-name
	   (unalias-slot-name-if-necessary attribute-name class-name))
	 (class-description? (class-description class-name))
	 (slot-description?
	   (and class-description?
		(get-slot-description-of-class-description
		  pretty-slot-name class-description?)))
	 (type-when-editable
	   (when slot-description?
	     (type-slot-feature-assq-if-editable
	       (slot-features slot-description?)))))
    (unless class-description?
      (stack-error cached-top-of-stack
		   "Class name ~a not valid for g2-validate-parsing-text" class-name))
    (unless type-when-editable
      (stack-error cached-top-of-stack
		   "Class name ~a or attribute name ~a not valid for g2-validate-parsing-text"
		   class-name attribute-name))

    (let ((current-parsing-context?
	    (create-parsing-context
	      class-name pretty-slot-name
	      type-when-editable
	      nil nil)))

      ;;Make sure this is nil; we have no item.
      (setf (frame-being-edited? current-parsing-context?) nil)

      (setf (parsing-context-text-string current-parsing-context?) (copy-wide-string the-text))
      (multiple-value-bind
	  (ok endable-p longest-common-completion?
	      category-choices completion-choices
	      token-complete-p token-data copy-of-gripe) 
	  (parsing-context-adjust-cursor-position
	    current-parsing-context?
	    (lengthw (parsing-context-text-string current-parsing-context?)))
	(prog1
	    (package-return-values-from-parsing-rpc
	      ok endable-p longest-common-completion?
	      category-choices completion-choices
	      token-complete-p token-data copy-of-gripe)
	  ;; GENSYMCID-1543: Suspected memory leak in system procedure g2-validate-parsing-text
	  (clear-parsing-context current-parsing-context?)
	  (remove-parsing-context current-parsing-context?))))))

(define-system-rpc-access (g2-parsing-context-get-text (text) ui-client-interface)
    ((parsing-context-handle integer))
  (g2-parsing-context-get-text parsing-context-handle))

(defun-for-system-procedure g2-parsing-context-get-text ((parsing-context-handle integer))
  (declare (values text))
  (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
    (cond ((null current-parsing-context?)
	   (invalid-parsing-context-handle parsing-context-handle))
	  (t
	   (parsing-context-text-string current-parsing-context?)))))

;;legacy for tw2
(defun-system-rpc (g2-set-editing-context-item (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer)
     (item (class item)))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-clear-parsing-context 'ui-client-interface)
    (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
      (when (null current-parsing-context?)
	#+development
	(when trace-parsing-context-p
	  (format t "No parsing context defined for handle ~a" parsing-context-handle))
	(return-from-system-defined-rpc
	  rpc-instance (eval-list evaluation-false-value)))
      #+development
      (when trace-parsing-context-p
	(format t "~%The item of ~a was set to ~a"
		current-parsing-context? item))
      (set-frame-being-edited current-parsing-context? item)

      (return-from-system-defined-rpc
	rpc-instance (eval-list evaluation-true-value)))))


(defun-system-rpc (g2-clear-parsing-context (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-clear-parsing-context 'ui-client-interface)
    (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
      (cond
	(current-parsing-context?
	 #+development (when trace-parsing-context-p
			 (format t "~%~%~%+++++++++++++++++++++++++++++++++++++~
                    ~%clearing parsing context: ~a~%"
				 current-parsing-context?))
	 (clear-parsing-context current-parsing-context?)
	 (return-from-system-defined-rpc
	   rpc-instance (eval-list evaluation-true-value)))
	(t
	 (return-from-system-defined-rpc
	   rpc-instance (eval-list evaluation-false-value)))))))

(defun-for-system-procedure g2-clear-parsing-context ((parsing-context-handle integer))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid t))
  (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
    (cond
      (current-parsing-context?
       #+development (when trace-parsing-context-p
		       (format t "~%~%~%+++++++++++++++++++++++++++++++++++++~
                    ~%clearing parsing context: ~a~%"
			       current-parsing-context?))
       (clear-parsing-context current-parsing-context?)
       truth)
	(t falsity))))


(defun-system-rpc (g2-delete-parsing-context (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-delete-parsing-context 'ui-client-interface)
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list (g2-delete-parsing-context parsing-context-handle)))))


(defun-for-system-procedure g2-delete-parsing-context ((parsing-context-handle integer))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid t))
  (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
    (cond
      (current-parsing-context?
       #+development (when trace-parsing-context-p
		       (format t "~%~%~%+++++++++++++++++++++++++++++++++++++~
                    ~%deleting parsing context: ~a~%"
			       current-parsing-context?))
       (remove-parsing-context parsing-context-handle)
       truth)
      (t falsity))))



;;;Note: for legacy with TW2, this system RPC takes the ITEM, although it should
;;;already be set.  The system procedure does not take the item, and is named
;;;g2-compile-parse-result.
(defun-system-rpc (g2-commit-parse-result (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer)
     (item (class item))
     (editing-for-runtime-change-p truth-value))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-commit-parse-result 'ui-client-interface)
    (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
      (cond (current-parsing-context?
	     (set-frame-being-edited current-parsing-context? item)
	     (let ((structure-to-return (g2-compile-parse-result parsing-context-handle editing-for-runtime-change-p)))
	       (return-from-system-defined-rpc
		 rpc-instance
		 (eval-list
		   structure-to-return))))
	    (t (invalid-parsing-context-handle parsing-context-handle))))))

;;;We also have the RPC for the signature without the item
(defun-system-rpc (g2-compile-parse-result (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer)
     (editing-for-runtime-change-p truth-value))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-compile-parse-result 'ui-client-interface)
    (let ((structure-to-return (g2-compile-parse-result parsing-context-handle editing-for-runtime-change-p)))
      (return-from-system-defined-rpc
	rpc-instance
	(eval-list
	  structure-to-return)))))

;;;The system procedure called by the above two RPC's
(defun-for-system-procedure g2-compile-parse-result
    ((parsing-context-handle integer) (editing-for-runtime-change-p truth-value))
  (declare (values structure))
  (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
    (cond (current-parsing-context?
	   (cond ((eq editing-for-runtime-change-p truth)
		  (setq editing-for-runtime-change-p t))
		 ((eq editing-for-runtime-change-p falsity)
		  (setq editing-for-runtime-change-p nil))
		 #+development
		 (t (cerror "Continue, using raw value"
			    "editing-for-runtime-change-p (~a) is neither truth nor falsity!"
			    editing-for-runtime-change-p)))
	   (multiple-value-bind (ok error-text error-index)
	       (commit-parse-result current-parsing-context? editing-for-runtime-change-p)
	     (allocate-evaluation-structure-inline
	       'ok (if ok evaluation-true-value evaluation-false-value)
	       'description (make-evaluation-text-reclaiming-argument error-text)
	       'error-index (if error-index
				(make-evaluation-integer error-index)
				evaluation-false-value))))
	  (t (invalid-parsing-context-handle parsing-context-handle)))))

;;Lisp function called by both commit and compile parse result
(defun commit-parse-result (current-parsing-context? editing-for-runtime-change-p)
  (let (item flag-or-error-text-or-nil)
    (if (null current-parsing-context?)
	(setq flag-or-error-text-or-nil 'frame-is-null-or-reprocessed)
	(progn
	  (setq item (frame-being-edited? current-parsing-context?))
	  (if (or (null item)
		  (frame-has-been-reprocessed-p
		    item
		    (serial-number-of-frame-being-edited? current-parsing-context?)))
	      (setq flag-or-error-text-or-nil 'frame-is-null-or-reprocessed)
	      (progn
		;;Finally done with error checking:  Do the work!
		(complete-and-extend-final-token-if-necessary current-parsing-context?)
		(setq flag-or-error-text-or-nil
		      (end-editorless-parsing
			current-parsing-context? item editing-for-runtime-change-p))))))
    (cond
      (flag-or-error-text-or-nil
       (cond
	 ((symbolp flag-or-error-text-or-nil) ; flag case
	  (let ((error-text
		  (case flag-or-error-text-or-nil
		    (frame-is-null-or-reprocessed
		     #w"frame is null or reprocessed")
		    (parse-is-bad        #w"bad parse")
		    (parse-is-incomplete #w"this is incomplete")
		    (parse-is-ambiguous  #w"this is ambiguous"))))
	    #+development
	    (when trace-parsing-context-p
	      (format t "~%~%Flag return from Commit:~%   \"~a\"" error-text))
	    (values nil
		    (copy-text-string error-text)
		    (parsing-context-error-index current-parsing-context?))))
	 (t  ; error text from the compiler
	  #+development
	  (when trace-parsing-context-p
	    (format t "~%~%Compiler complaint:~%  ~a" flag-or-error-text-or-nil))
	  (values nil			;ok
		  (copy-text-string flag-or-error-text-or-nil) ;error-text
		  (parsing-context-error-index current-parsing-context?))))) ;error-index
      (t
       #+development
       (when trace-parsing-context-p
	 (format t "~%~%Commit went through without complaint"))
	 (values t nil nil)))))


;;; `G2-update-parsing-context' has become the standard way to translate
;;; any change in the text to an impact on the edit-state that's embedded
;;; in the parsing-context structure. Now that it's being driven from Nevada,
;;; I'm giving its indicies a strict interpretation that empirically I've
;;; determined is different from what they originally had.  (ddm 11/4/97)
;;;
;;; When the advance-index? has a value, there has been a character or
;;; characters added to the text. If they have been added to the end of the
;;; text this will be manifest by the advance index having a larger value
;;; than the start index. If the cursor was moved and the additions are
;;; somewhere in the middle, then the advance index will be the
;;; between-characters position just to the right of the last character
;;; that was added. (We're only going to get additions of contiguous
;;; strings of charaters.)

;;; It is the responsibility of the caller to only supply either an
;;; advance index or a retreat (backup) index. Should they happen to
;;; supply both the retreat will win. 

;;; Note: This is in the TW2 legacy API and not published as a sysproc.
(defun-system-rpc (g2-update-parsing-context (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer)
     (backup-index? datum)
     (advance-index? datum)
     (the-text text))
  
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-update-parsing-context 'ui-client-interface)
    (unless (fixnump backup-index?)
      (setf backup-index? nil))
    (unless (fixnump advance-index?)
      (setf advance-index? nil))
    
    (let ((current-parsing-context? (get-parsing-context parsing-context-handle))
	  copy-of-gripe parse-status)
      
      (parsing-context-setf-reclaiming-old-text-string current-parsing-context? the-text)
      
      (when (and advance-index?
		 (>f advance-index? (lengthw the-text)))
	;; bug trap. This can happen if the indicies get out of sync
	;; between the client's impression of where we are and the
	;; impression here. It will blow up the copy operation that
	;; starts the advance operation if we don't trap it.
	;; Obviously we should prove that this can't happen, but
	;; better safe than sorry since if the error happens the
	;; server goes down.
	#+development
	(when nil ;trace-parsing-context-p
	  (cerror "Truncate the advance to just the length of the string"
		  "indicies out of sync: text length = ~a, advance = ~a"
		  (lengthw the-text) advance-index?))
	;; ?? feedback to the client?  We could declare this a sort
	;; of reset and pass back the text we're actually working on.
	(setq advance-index? (lengthw the-text)))
          
      #+development (when trace-parsing-context-p
	(format t "~4%>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>~
               ~%Update: full text passed in = \"~a\"" the-text)
	(if advance-index?
	    (format t "~%   advancing to ~a" advance-index?)
	    (format t "~%   retreating to ~a" backup-index?))
	(cond
	  ((and advance-index? (=f advance-index? (lengthw the-text)))
	   (format t ", which is the end of the text~%"))
	  (t (let ((net-text (copy-text-string-portion
			       the-text 0 (or advance-index? backup-index?))))
	       (format t "~%   The net text =\"~a\"~%" net-text)
	       (reclaim-text-string net-text)))))

      (cond
	(current-parsing-context?
	 (cond
	   ((free-text-slot-being-edited? current-parsing-context?)
	    ;; Don't do anything. This change is not monitored by
	    ;; the grammar since no grammar applies to these slots.
	    (return-from-parsing-rpc-with-cursor-relative-prompt-and-status-data
	      rpc-instance current-parsing-context? nil nil))
	   (t
	    (within-parsing-context (current-parsing-context?)
	      (let ((start-index (parsing-context-text-length current-parsing-context?)))
		(cond
		  (backup-index?
		   ;;it's highly unlikely that we will actually get a problem
		   ;;string with a retreat, but we should handle it in the same
		   ;;way we handle advance strings
		   (multiple-value-setq (parse-status copy-of-gripe)
		     (retreat-parsing-context current-parsing-context? backup-index?))
		   (when copy-of-gripe
		     (setf copy-of-gripe (copy-text-string copy-of-gripe)))
		   #+development
		   (when trace-parsing-context-p
		     (format t "Retreated to ~a.  Text length now is ~a~%"
			     backup-index? (parsing-context-text-length current-parsing-context?))))
		  (advance-index?
		   (cond
		     ((>f advance-index? start-index) ; the intended case
		      (let ((advance-string
			      (copy-text-string-portion
				the-text start-index advance-index?)))
			(multiple-value-setq (parse-status copy-of-gripe)
			  (advance-parsing-context current-parsing-context? advance-string))
			(when copy-of-gripe
			  (setf copy-of-gripe (copy-text-string copy-of-gripe)))))
		     
		     ((=f advance-index? start-index)
		      ;; We can get here if the user types a non-inserting
		      ;; character. That case should be trapped as a non-event
		      ;; by the caller, but we want cover the possibility
		      ;; in case they miss it.
		      )
		     
		     
		     ((<f advance-index? start-index)   
		      ;; This is a case of adding characters behind the right fringe
		      ;; of the text. This would not normally happen because the
		      ;; only reasonable way to move to the left of the fringe
		      ;; is by deleting characters or moving the cursor, both of
		      ;; which should have triggered 'retreat' events that
		      ;; would have moved the start-index.
		      ;;   But we still need to behave correctly even if the
		      ;; caller does not follow the intended protocol, so we
		      ;; have to first get everything into a state that we know
		      ;; is valid. The simplest way to do this is to retreat
		      ;; all the way back to the start-token via clear-parsing-
		      ;; context and then treat this as an advance that starts
		      ;; from position zero.
		      #+development
		      (cerror "Retreat to 0"
			      "~%!! the advance index(~a) is <= the ~
                            start index(~a)~%"
			      advance-index? start-index)
		      (setf (parsing-context-text-string current-parsing-context?) #w"")
		      (clear-parsing-context current-parsing-context?)
		      (let ((advance-string
			      (copy-text-string-portion
				the-text 0 advance-index?)))
			(multiple-value-setq (parse-status copy-of-gripe)
			  (advance-parsing-context current-parsing-context? advance-string))
			(when copy-of-gripe
			  (setf copy-of-gripe (copy-text-string copy-of-gripe))))))
		   
		   ;; We get here with any advance
		   #+development
		   (when trace-parsing-context-p
		     (format t "parse-status = ~s~%" parse-status)
		     (when (not  ; copied from advance-parsing-context
			     (or (eq parse-status 'parsing-context-complete-status)
				 (eq parse-status 'so-far-so-good-2)
				 (eq parse-status 'so-far-so-good-3)))
		       (format t "gripe = ~s~%" copy-of-gripe)
		       (print-token-list current-parsing-context?)))))
		
		;; common return path for advance or retreat if there was a parsing context
		(return-from-parsing-rpc-with-cursor-relative-prompt-and-status-data
		  rpc-instance current-parsing-context? parse-status copy-of-gripe))))))
	
	(t  ; what we do if there isn't a parsing context
	 (maybe-return-from-system-defined-rpc
	   rpc-instance (eval-list evaluation-false-value)))))))





;;; `Return-from-parsing-rpc-with-cursor-relative-prompt-and-status-data'
;;; was broken out from update-parsing-context so that it could be
;;; shared with cursor-movement and potentially other operations.

;;; It was further refined to have just the return values split out, so that
;;; lisp functions could interact with it directly rather than through RPC
;;; (function return-values-with-cursor-relative-prompt-and-status-data).

;;; Now we have a packaging issue, because we didn't update
;;; g2-update-parsing-context to use the new return values function, as it was
;;; not intended to be exported with the new API, but we don't want to end up
;;; calling return-values-with-cursor-relative-prompt-and-status-data multiple
;;; times.  So, a new function package-return-values-from-parsing-rpc takes all
;;; the possible arguments you could imagine (all returns from
;;; return-values-with-cursor-relative-prompt-and-status-data and then some) in
;;; order to package up and return it as an RPC return value structure.  the new
;;; text update API functions will call both
;;; return-values-with-cursor-relative-prompt-and-status-data and
;;; package-return-values-from-parsing-rpc.  yduJ, 12/05

(defun return-values-with-cursor-relative-prompt-and-status-data 
    (current-parsing-context? &optional copy-of-gripe)
  #+development (when trace-parsing-context-p
    (format-when-tracing-in-events-modules
      " pc-error-index=~s pc-text-length=~s~%"
      (parsing-context-error-index current-parsing-context?) (parsing-context-text-length current-parsing-context?))
    (print current-parsing-context?))

  (cond ((free-text-slot-being-edited? current-parsing-context?)
	 (values
	   t ;ok
	   t ;endable-p
	   nil ;longest-common-completion
	   nil ;category-choices
	   nil ;completion-choices
	   nil ;token-complete-p
	   '(0 0 0) ;token-data
	 ))
	(t
	 (let* ((cursor-token (parsing-context-cursor-token current-parsing-context?))
		(token-data (phrase-list
			      (parsing-token-ordinal-index cursor-token)
			      (parsing-token-start-index cursor-token)
			      (parsing-token-end-index cursor-token)))
		got-prompts-from-prior-token? )
	   
	   (multiple-value-bind (category-choices completion-choices
						  longest-common-completion? can-end?)
	       (when (not (parsing-context-error-index current-parsing-context?))
		 (compute-parsing-context-prompts
		   (cond
		     ;;Check for whitespace or comment, and use prior token for
		     ;;prompts in this case.
		     ((and (or (null (parsing-token-type-or-prefix-string cursor-token))
			       (comment-token-p cursor-token))
			   (parsing-token-previous cursor-token))
		      (setq got-prompts-from-prior-token? t)
		      (maybe-skip-comment-tokens (parsing-token-previous cursor-token)))
		     (t
		      cursor-token))))
	     
	     #+development (when trace-parsing-context-p
			     (format t "~%~%Cursor token: ~a~%" cursor-token)
			     (if got-prompts-from-prior-token?
				 (format t "Getting the prompts from the Prior token:~
                            ~%   ~a~%" (parsing-token-previous cursor-token))
				 (format t "It is providing the prompts.~%")))
	     
	     ;; send the information back
	     (values 
	       (not (parsing-context-error-index current-parsing-context?)) ;ok
	       can-end?
	       longest-common-completion?
	       category-choices
	       completion-choices
	       (not (parsing-token-incomplete-p cursor-token)) ;token-complete=p
	       token-data
	       copy-of-gripe))))))



(defun return-from-parsing-rpc-with-cursor-relative-prompt-and-status-data
    (rpc-instance current-parsing-context? parse-status copy-of-gripe)
  (declare (ignore parse-status))

  (multiple-value-bind
      (ok endable-p longest-common-completion?
	  category-choices completion-choices
	  token-complete-p token-data) 
      (return-values-with-cursor-relative-prompt-and-status-data
	current-parsing-context?)
    (maybe-return-from-system-defined-rpc
      rpc-instance
      (eval-list
	(package-return-values-from-parsing-rpc
	  ok endable-p longest-common-completion?
	  category-choices completion-choices
	  token-complete-p token-data copy-of-gripe)))))


(defun package-return-values-from-parsing-rpc
    (ok endable-p longest-common-completion?
	category-choices completion-choices
	token-complete-p token-data copy-of-gripe)
  (allocate-evaluation-structure-inline
    'ok (make-evaluation-boolean-value ok)
    'endable-p (make-evaluation-boolean-value endable-p)
    'description (if copy-of-gripe
		     (make-evaluation-text-reclaiming-argument copy-of-gripe)
		     evaluation-false-value)
    'error-index
    (if (parsing-context-error-index current-parsing-context?)
	(make-evaluation-integer (parsing-context-error-index current-parsing-context?))
	evaluation-false-value)

    'longest-common-completion
    (or longest-common-completion? evaluation-false-value)

    'category-choices
    (allocate-evaluation-sequence
      (copy-list-using-eval-conses category-choices))
    'completion-choices
    (allocate-evaluation-sequence
      (copy-list-using-eval-conses completion-choices))
    'token-complete-p (make-evaluation-boolean-value token-complete-p)
    'token-data
    (allocate-evaluation-sequence
      (copy-list-using-eval-conses token-data))))



;;; `G2-shift-cursor-position' should be used when only the cursor has
;;; changed, e.g. when the mouse was clicked at some position other than
;;; the insertion point or when the arrow keys are used. 
;;; This is zero based and takes the text for T2.
(defun-system-rpc (g2-shift-cursor-position (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer)
     (new-position integer)
     (the-text text))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-shift-cursor-position 'ui-client-interface)
    (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
      (cond
	(current-parsing-context?
	 (when (wide-string-p the-text)
	   (parsing-context-setf-reclaiming-old-text-string current-parsing-context? the-text))
	 (maybe-return-from-system-defined-rpc
	   rpc-instance
	   (eval-list
	     (g2-adjust-cursor-position parsing-context-handle (1+f new-position)))))
	(t (return-from-system-defined-rpc rpc-instance (eval-list evaluation-false-value)))))))


;;One based.
(defun-system-rpc (g2-adjust-cursor-position (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer)
     (new-position integer))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-adjust-cursor-position 'ui-client-interface)
    (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
      (cond
	(current-parsing-context?
	 (maybe-return-from-system-defined-rpc
	   rpc-instance
	   (eval-list
	     (g2-adjust-cursor-position parsing-context-handle new-position))))
	 (t (return-from-system-defined-rpc rpc-instance (eval-list evaluation-false-value)))))))

;;One based.
(defun-for-system-procedure g2-adjust-cursor-position ((parsing-context-handle integer) (new-position integer))
  (declare (values structure))
  (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
    (cond
      (current-parsing-context?
       (if (> new-position (1+ (lengthw (parsing-context-text-string current-parsing-context?))))
	   (stack-error cached-top-of-stack
			"Position ~a invalid for g2-adjust-cursor-position" new-position))
       (multiple-value-bind
	   (ok endable-p longest-common-completion?
	       category-choices completion-choices
	       token-complete-p token-data copy-of-gripe) 
	   (parsing-context-adjust-cursor-position current-parsing-context?
						   (1-f new-position))
	 (package-return-values-from-parsing-rpc
	   ok endable-p longest-common-completion?
	   category-choices completion-choices
	   token-complete-p token-data copy-of-gripe)))
      (t (invalid-parsing-context-handle parsing-context-handle)))))

;;zero based.
(defun parsing-context-adjust-cursor-position (current-parsing-context? new-position)
  (cond
    ((free-text-slot-being-edited? current-parsing-context?)
     ;; Don't do anything. This change is not monitored by
     ;; the grammar since no grammar applies to these slots.
     (return-values-with-cursor-relative-prompt-and-status-data current-parsing-context?))
    (t
     (if (<f new-position 0)
	 (setq new-position (lengthw (parsing-context-text-string current-parsing-context?))))
     #+development (when trace-parsing-context-p
		     (format t "~%~%~%>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>~
                    ~%Shifting the cursor position to ~a~
                    ~%   The full text is \"~a\"~%" new-position (parsing-context-text-string current-parsing-context?))
		     (let ((net-text (copy-text-string-portion
				       (parsing-context-text-string current-parsing-context?) 0 new-position)))
		       (format t "~%The net text is \"~a\"~%" net-text)
		       (reclaim-text-string net-text)))
     
     (within-parsing-context (current-parsing-context?)
			     (multiple-value-bind (parse-status copy-of-gripe)
				 (shift-cursor-token current-parsing-context? new-position)
			       (declare (ignore parse-status))
			       (return-values-with-cursor-relative-prompt-and-status-data
				 current-parsing-context? copy-of-gripe))))))



(defun parsing-context-set-text (current-parsing-context? the-text new-position)
  (when (wide-string-p the-text)
    (let* ((new-text (copy-wide-string the-text))
	   (common-position (mismatch new-text (parsing-context-text-string current-parsing-context?)
				      :end2 (parsing-context-text-length current-parsing-context?))))
      (parsing-context-setf-reclaiming-old-text-string current-parsing-context? new-text)
	;;This is too funky for words.  However, we may not be using this
	;;function much at all.  It's possible the right thing is to clear
	;;parsing context upon set text instead of trying to diff it and stuff.
	;;But for testing we need it this way.
      (when (parsing-context-error-index current-parsing-context?)
	(setf (parsing-context-error-index current-parsing-context?) nil))
      (if (and (null (parsing-context-error-index current-parsing-context?))
		     (or (null common-position)
			 (=f common-position (parsing-context-text-length current-parsing-context?))))
	       ;;If same, just return values from adjust position.
	  (parsing-context-adjust-cursor-position current-parsing-context? new-position)

	  ;;Otherwise, must back up to common position to throw away parsing tokens.
	  (multiple-value-bind
	      (ok endable-p longest-common-completion?
		  category-choices completion-choices
		  token-complete-p token-data copy-of-gripe) 
	      (parsing-context-adjust-cursor-position current-parsing-context? common-position)
	    ;;If it's OK at this point (should be, because have only popped stack,
	    ;;could be incomplete though, but that's ok) we advance to new
	    ;;position.  Otherwise, we punt back to the value we get here.
	    (if (or ok (not token-complete-p))
		(parsing-context-adjust-cursor-position current-parsing-context? new-position)
		(values ok endable-p longest-common-completion?
			category-choices completion-choices
			token-complete-p token-data copy-of-gripe)))))))



;;one based
(defun-system-rpc (g2-parsing-context-delete-characters (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer)
     (position integer)
     (number-of-chars integer))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-parsing-context-delete-characters 'ui-client-interface)
    (maybe-return-from-system-defined-rpc
      rpc-instance
      (eval-list
	(g2-parsing-context-delete-characters parsing-context-handle position number-of-chars)))))


;;one based
(defun-for-system-procedure g2-parsing-context-delete-characters ((parsing-context-handle integer)
								  (position integer)
								  (number-of-chars integer))
  (declare (values structure))
  (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
    (cond
      (current-parsing-context?
       (multiple-value-bind
	   (ok endable-p longest-common-completion?
	       category-choices completion-choices
	       token-complete-p token-data copy-of-gripe) 
	   (parsing-context-delete-characters current-parsing-context? (1-f position) number-of-chars)
	 (when (and (null token-data) copy-of-gripe)
	   (reclaim-text-string copy-of-gripe)
	   (stack-error
	     cached-top-of-stack
	     "Error while deleting ~a characters from position ~a:  Bad string index?"
	     number-of-chars position))
	 (package-return-values-from-parsing-rpc
	   ok endable-p longest-common-completion?
	   category-choices completion-choices
	   token-complete-p token-data copy-of-gripe)))
      (t (invalid-parsing-context-handle parsing-context-handle)))))

;;zero based
(defun parsing-context-delete-characters (current-parsing-context? position number-of-chars)
  ;;Back up current parse, we're invalidating our cached information.
  (if (< position (parsing-context-text-length current-parsing-context?))
      (retreat-parsing-context current-parsing-context? position))
  ;;omit-from-g2-text takes 1 based positions.  We take 0-based for
  ;;compatibility with T2 fns and for ease of use directly from lisp.  Silly to
  ;;have to adjust twice, but we do.
  (let*	((g2-position (1+f position))
	 (new-string? (omit-from-g2-text (parsing-context-text-string current-parsing-context?)
				       g2-position (+ g2-position (1-f number-of-chars)))))
    (cond (new-string? ;;no errors
	   (parsing-context-setf-reclaiming-old-text-string current-parsing-context? new-string?)
	   (adjust-after-insert/delete current-parsing-context? position))
	  (t (return-error-values
	       "Error while deleting ~a characters from position ~a:  Bad string index?"
	       number-of-chars position)))))



;;one based
(defun-system-rpc (g2-parsing-context-insert-characters (datum))
    ((rpc-instance system-rpc-instance)
     (parsing-context-handle integer)
     (position integer)
     (addition text))
  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-parsing-context-insert-characters 'ui-client-interface)
    (return-from-system-defined-rpc
      rpc-instance
      (eval-list (g2-parsing-context-insert-characters parsing-context-handle position addition)))))


;;one based
(defun-for-system-procedure g2-parsing-context-insert-characters ((parsing-context-handle integer)
								  (position integer)
								  (addition text))
  (declare (values structure))
  (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
    (cond
      (current-parsing-context?
       (multiple-value-bind
	   (ok endable-p longest-common-completion?
	       category-choices completion-choices
	       token-complete-p token-data copy-of-gripe) 
	   (parsing-context-insert-characters current-parsing-context? (1-f position) addition)
	 (when (and (null token-data) copy-of-gripe)
	   (reclaim-text-string copy-of-gripe)
	   (stack-error
	     cached-top-of-stack
	     "Error while inserting characters:  Bad string index ~a or invalid string."
	     position))
	 (package-return-values-from-parsing-rpc
	   ok endable-p longest-common-completion?
	   category-choices completion-choices
	   token-complete-p token-data copy-of-gripe)))
      (t (invalid-parsing-context-handle parsing-context-handle)))))

;;zero based
(defun parsing-context-insert-characters (current-parsing-context? position addition)
  ;;issue: insert-in-g2-text takes 1 based positions.
  ;;Back up current parse, we're invalidating our cached information.
  (if (< position (parsing-context-text-length current-parsing-context?))
      (retreat-parsing-context current-parsing-context? position))
  ;;insert-in-g2-text takes 1 based positions.  See delete.
  (let*	((g2-position (1+f position))
	 (new-string? (insert-in-g2-text addition
					 (parsing-context-text-string current-parsing-context?)
					 g2-position)))
    (cond (new-string? ;;no errors
	   (parsing-context-setf-reclaiming-old-text-string current-parsing-context? new-string?)
	   (adjust-after-insert/delete current-parsing-context? (+ position (lengthw addition))))
	  (t (return-error-values "Error while inserting characters:  Bad string index ~a or invalid string." position)))))

(defun adjust-after-insert/delete (current-parsing-context? position)
  (cond ((free-text-slot-being-edited? current-parsing-context?)
	 (return-values-with-cursor-relative-prompt-and-status-data current-parsing-context?))
	(t (within-parsing-context (current-parsing-context?)
				   (multiple-value-bind (parse-status copy-of-gripe)
				       (shift-cursor-token current-parsing-context? position)
				     (declare (ignore parse-status))
				     (return-values-with-cursor-relative-prompt-and-status-data
				       current-parsing-context? copy-of-gripe))))))  




;;; `g2-menu-of-names-for-category' does what it says. Its purpose
;;; within the Nevada Text Editor is to provide the response when
;;; the user clicks on a category prompt.

(defun-system-rpc (g2-menu-of-names-for-category (datum))
    ((rpc-instance system-rpc-instance)
     (category-symbol symbol)
     (parsing-context-handle integer))

  (when (rpc-interface-class-ok?
	  rpc-instance 'g2-menu-of-names-for-category 'ui-client-interface)
    (macrolet ((string-of-incomplete-cursor-token (current-parsing-context?)
		 `(let ((cursor-token (parsing-context-cursor-token ,current-parsing-context?)))
		    (when (parsing-token-incomplete-p cursor-token)
		      (parsing-token-incomplete-text cursor-token)))))
      
      (let ((current-parsing-context? (get-parsing-context parsing-context-handle)))
	(cond
	  (current-parsing-context?
	   (let* ((prefix-string? (string-of-incomplete-cursor-token current-parsing-context?))
		  (list
		    ;; This list is not freshly cons'd modulo a comment about a
		    ;; possible leak in the 'flattening' phase that is mentioned
		    ;; in a note about four functions down from this one which I
		    ;; haven't independently checked out. -ddm
		    (make-menu-of-names-from-directory
		      category-symbol prefix-string?)))
	     
	     (when trace-parsing-context-p
	       (format t "~%~%~%>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>~
                 ~%Menu of names for ~a with prefix \"~a\" =~%~a"
		       category-symbol prefix-string? list))
	     (cond
	       (list
		(return-from-system-defined-rpc
		  rpc-instance
		  (eval-list
		    (allocate-evaluation-structure-inline
		      'token-prompts-for-category
		      (allocate-evaluation-sequence
			(copy-list-using-eval-conses list))))))
	       (t
		(return-from-system-defined-rpc
		  rpc-instance (eval-list evaluation-false-value))))))
	  (t
	   (return-from-system-defined-rpc
	     rpc-instance (eval-list evaluation-false-value))))))))





(defun blank-text-string-p (text-string)
  (loop for i from 0 below (text-string-length text-string)
	always (char=w (charw text-string i)  #.%\Space)))







;;;; Other Stuff

(defun-simple convert-internal-slot-value (category? category-function? slot-features frame value)
  (let* ((converted-value? (when category-function?
			     (call-category-getter-fn category-function?
						      value frame nil))))
    (cond (converted-value?
	   converted-value?)
	  ((eq category? 'name-or-names)
	   (cond ((null value) nil)
		 ((listp value)
		  (allocate-evaluation-sequence
		    (copy-list-using-eval-conses value)))
		 ((symbolp value)
		  (make-evaluation-symbol value))
		 (t
		  #+development
		  (cerror "returned nil" "got a wierd name-or-names in convert-internal-slot-value ~S"
			  value))))
	  ((and category-function?
		(null converted-value?))
	   nil)
	  (t
	   (let* ((type-of-slot-component (feature-assq 'type slot-features)))
	     (cond ((text-slot-type-p type-of-slot-component)
		    (text-slot-value-to-evaluation-text
		      frame value type-of-slot-component))
		   (t
		    #+development
		    (cerror "returned nil" "got a wierd value in convert-internal-slot-value ~S" value)
		    nil)))))))

(defun-allowing-unwind send-trend-chart-slot-change (trend-chart slot-name
								 slot-component-name
								 new-value
								 old-value
								 slot-component-indicator?)
;  (format t "slot-name ~s; name-if-any ~s alias-if-any ~s~%" slot-name
;	  (get-slot-name-for-alias-if-any slot-name trend-chart)
;	  (get-alias-for-slot-name-if-any slot-name trend-chart))
  ;; fix this: will one ever want to send if the old and new values are equal?
  (unless (equal new-value old-value)
    (with-trend-chart-notification (trend-chart 'slot-change)
      (let* ((slot-features (get-slot-component-features
			      slot-name
			      (class-description 'trend-chart)
			      slot-component-name))
	     (category-spec? (feature-assq 'type slot-features))
	     (category? (and category-spec? (cadr category-spec?)))
	     (category-function? (slot-value-to-evaluation-value-function category?))
	     (exported-new-value (convert-internal-slot-value category? category-function?
							      slot-features
							      trend-chart new-value)))
	(allocate-evaluation-structure-inline
	  'slot-name
	  (or (get-alias-for-slot-name-if-any slot-name trend-chart)
	      slot-name)
	  'slot-component-name
	  (or (slot-component-alias slot-component-name)
	      slot-component-name)
	  'chart-element-uid
	  (make-evaluation-value-based-on-type slot-component-indicator?)
	  'new-value
	  exported-new-value)))))


;;;; System RPC access to group transfer, move and clone operations

;;; These have been added here since the system-procedures are defined
;;; in lists, which precedes g2-rpc1, where the define-system-rpc-access
;;; macro is defined. Maybe we can find a better place for them later.

(define-system-rpc-access (g2-transfer-items ())
    ((sequence-of-items (sequence))
     (kb-workspace (class kb-workspace))
     (delta-x integer)
     (delta-y integer))
  (g2-transfer-list-contents sequence-of-items kb-workspace delta-x delta-y evaluation-true-value)
  nil)

;;; This rpc was written for use by Telewindows2 Toolkit (T2)
;;; NOTE: contrary to other similar T2 procedures, delta-y is in fact
;;; passed in in user co-ordinates (delta-y positive means moving
;;; towards the top of the screen).
;;; The purpose of this rpc is to allow the moving of
;;; multiple items to maintain the correct relationships of their connections.
;;; It was not possible to use the existing g2-move-items (or the
;;; corresponding g2-move-list-contents) because neither of them
;;; allowed the restriction on expanding the workspace to be specified

(define-system-rpc-access (g2-move-items-enlarging-workspace-if-necessary ())
    ((sequence-of-items (sequence))
     (delta-x integer)
     (delta-y integer)
     (enlarge-workspace-if-necessary truth-value))
  (setf delta-y (-f delta-y))
  ;;(format t "moving ~S ~s ~s~%" delta-x delta-y enlarge-workspace-if-necessary)
  (multiple-value-bind (objects-being-moved from-workspace)
      (get-blocks-valid-for-group-operation sequence-of-items)
    ;; move-blocks-with-their-external-connections
    ;; enlarges the workspace, so limit the delta to
    ;; prevent that
    (unless (evaluation-truth-value-is-true-p
	      enlarge-workspace-if-necessary)
      (multiple-value-bind (left top right bottom)
	  (determine-extreme-edges-of-group objects-being-moved)
	(let ((margin (workspace-margin from-workspace)))
	  (if (<f delta-x 0)
	      ;; limit moving left
	      (let* ((leftmost-point
		       (+f (left-edge-of-block from-workspace) margin))
		     (biggest-move (-f leftmost-point left)))
		(when (<f delta-x biggest-move)
		  (setf delta-x biggest-move)))
	      ;; limit moving right
	      (let* ((rightmost-point (-f (right-edge-of-block from-workspace) margin))
		     (biggest-move (-f rightmost-point right)))
		(when (>f delta-x biggest-move)
		  (setf delta-x biggest-move))))
	  (if (<f delta-y 0)
	      ;; limit moving top
	      (let* ((topmost-point
		       (+f (top-edge-of-block from-workspace) margin))
		     (biggest-move (-f topmost-point top)))
		(when (<f delta-y biggest-move)
		  (setf delta-y biggest-move)))
	      ;; limit moving bottom
	      (let* ((bottommost-point (-f (bottom-edge-of-block from-workspace) margin))
		     (biggest-move (-f bottommost-point bottom)))
		;;(format t "dy ~s move ~s bmp ~s beb ~s~%"
		;;delta-y biggest-move bottommost-point bottom)
		(when (>f delta-y biggest-move)
		  (setf delta-y biggest-move)))))))
    (move-blocks-with-their-external-connections
      objects-being-moved  from-workspace delta-x delta-y)
    (when g2-has-v5-mode-windows-p
      (loop for block in objects-being-moved
	    do
	(send-ws-representations-item-moved block delta-x delta-y)))
    (reclaim-dragging-list objects-being-moved)
    (reclaim-evaluation-truth-value enlarge-workspace-if-necessary))
  nil)

(defun determine-extreme-edges-of-group (group-of-blocks)
  (loop with current-leftmost = most-positive-fixnum
	with current-rightmost = most-negative-fixnum
	with current-topmost = most-positive-fixnum
	with current-bottommost = most-negative-fixnum
	for block in group-of-blocks
	do
    (multiple-value-bind
	(left top right bottom)
	(determine-extreme-edges-of-block block)
      ;;(format t "block: ~s ~s ~s ~s~%" left top right bottom)
      (when (<f left current-leftmost)
	(setf current-leftmost left))
      (when (>f right current-rightmost)
	(setf current-rightmost right))
      (when (<f top current-topmost)
	(setf current-topmost top))
      (when (>f bottom current-bottommost)
	(setf current-bottommost bottom))
      ;;(format t "current: ~s ~s ~s ~s~%" current-leftmost current-topmost current-rightmost current-bottommost)
      )
	finally
	  (return (values current-leftmost current-topmost current-rightmost current-bottommost))))

  

(define-system-rpc-access (g2-move-items ())
    ((sequence-of-items (sequence))
     (delta-x integer)
     (delta-y integer))
  (g2-move-list-contents sequence-of-items delta-x delta-y)
  nil)



(define-system-rpc-access (g2-clone-and-transfer-items ((sequence)))
    ((sequence-of-items (sequence))
     (kb-workspace (class kb-workspace))
     (delta-x integer)
     (delta-y integer))
  (let ((item-list
	  (g2-clone-list-contents sequence-of-items kb-workspace delta-x delta-y)))
    (prog1
	(get-list-contents-as-sequence item-list)
      (delete-frame item-list))))



;;;; System rpc for generic event chaining



(define-system-rpc-access (g2-invoke-generic-event-rules ())
    ((event-name symbol)
     (item (class item))
     (event-object (class item)))
  (g2-invoke-generic-event-rules event-name item event-object))




;;;; System rpc and system procedure for describing an item


(defun-for-system-procedure g2-get-description-of-item (item)
  (let* ((*current-computation-frame* item)	; needed for calling role servers
	 (display-description (funcall-method 'describe-frame item))
	 (main-header (tformat-text-string "Description of ~(~NF.~)" item)))
    (loop with descriptions = '()
	  for display-statement in display-description
	  as description = nil
	  do
      (setq description
	    (typecase display-statement
	      (atom
	       (cond
		 ((null display-statement)
		  nil)
		 ((text-string-p display-statement)
		  display-statement)
		 ((consp display-statement) ; "text-p"!!! - abstract further1
		  (prog1
		      (convert-text-to-text-string display-statement)
		    (reclaim-text display-statement)))
		 ((framep display-statement)
		  (prog1
		      (frame-class-case display-statement
			(text-box
			  (convert-text-to-text-string
			    (box-translation-and-text display-statement)))
			(table-item
			  (get-represented-item display-statement)))
		    (delete-frame display-statement)))
		 (t 
		  #+development
		  (cerror "Continue" "Unexcepted type in g2-get-description-of-item")
		  nil)))
	      #+development	      
	      (t
	       (cerror "Ignore" "No nested forms yet in describe display descriptions"))))
      (when description
	(eval-push description descriptions))
	  finally
	    (reclaim-eval-list display-description)
	    (eval-push main-header descriptions)
	    (return
	      (allocate-evaluation-sequence descriptions)))))

(define-system-rpc-access (g2-get-description-of-item ((sequence)))
    ((item (class item)))
  (g2-get-description-of-item item))





;;;; Exporting Inspect Command Graphs system procedures and system rpcs

;;; Returns a sequence of node structures of the following format:
;;;
;;; structure(item-or-name: <item-or-name>, <--either an item or a string
;;;           children: sequence(<node-structure>, <node-structure>...))
;;;
;;; The following four macros determine the slot-names of the exported node-structure:
;;; NOTE: These macros do not bind their args; ie will eval their args
;;;       each time they are called.


(defmacro create-item-node (item)
  `(allocate-evaluation-structure-inline 'item-or-name ,item))

(defmacro get-item-or-name-of-node (node-structure)
  `(evaluation-structure-slot ,node-structure 'item-or-name))

(defmacro set-item-or-name-of-node (node-structure new-item-or-name)
  `(set-evaluation-structure-slot ,node-structure 'item-or-name ,new-item-or-name))

(defmacro set-children-of-node (node-structure children)
  `(set-evaluation-structure-slot
     ,node-structure
     'children
     ,children))

(defun-simple get-item-name-of-node (node)
  (let ((item-or-name (get-item-or-name-of-node node)))
    (cond ((wide-string-p item-or-name)
           item-or-name)
          (t
            (let* ((item (get-item-if-item-reference item-or-name))
                   (item-name (when (framep item)
                                (name-or-names-for-frame item))))
              (cond ((symbolp item-name) (symbol-namew item-name))
                    (t
                      #+development
                      (cerror "Continue" "Name of item should be symbol")
                      #w"")))))))

(defun-simple item-or-name-lessp (node1 node2)
  (string-lesspw (get-item-name-of-node node1) (get-item-name-of-node node2)))

(defun-simple export-node (node)
  (let ((node-item (get-item-or-name-of-node node))
	exported-item)
    (setq exported-item
	  (frame-class-case node-item
	    ((table-item)
	     (get-represented-item node-item))
	    ((text-box)
	     (convert-text-to-text-string
	       (box-translation-and-text node-item)))))
    (set-item-or-name-of-node node exported-item)))

(defun-simple sibling-nodes (default-junction excluded-node)
  (loop with siblings = '()
	for connection being each connection of default-junction
	as sibling-node = (get-block-at-other-end-of-connection
			    connection
			    default-junction)
	do
    (unless (eq sibling-node excluded-node)    
      (cond ((default-junction-p sibling-node)
	     (setf siblings (nconc siblings (sibling-nodes sibling-node default-junction))))
	    (t
	     (eval-push (create-item-node sibling-node) siblings))))
	finally
	  (return siblings)))
     
(defun-simple gather-children-nodes (item-node)
  (let* ((item (get-item-or-name-of-node item-node))
	 (child-connection? (sub-nodes-connection item))
	 (child-block? (and child-connection?
			    (get-block-at-other-end-of-connection
			      child-connection?
			      item)))
	 (child-nodes nil))
    (when child-block?
      (cond ((default-junction-p child-block?)
	     (setq child-nodes (sibling-nodes child-block? item)))
	    (t
	     (setq child-nodes (eval-list (create-item-node child-block?)))))
      (loop for node in child-nodes
	    do
	(gather-children-nodes node)
	(export-node node))
      (when child-nodes
	(set-children-of-node item-node (allocate-evaluation-sequence (sort-list child-nodes #'item-or-name-lessp nil)))))))

(defun get-tree-structure-for-inspect-command (inspect-command-string
						&optional 
						(force-workspace-creation-p nil)
						(root-node-index 2))
  (let ((inspect-command
	  (make-inspect-command-or-signal-error inspect-command-string)))
    (for-dummy-workstation
      (when force-workspace-creation-p
	(make-inspect-workspace inspect-command))
      (execute-inspect-command inspect-command))
    (let* ((workspace? (superblock? inspect-command))
	   (subblocks (and workspace? (subblocks workspace?)))
	   (block-count
	     #-subblocks-v2
	     (length subblocks)
	     #+subblocks-v2
	     (constant-queue-length subblocks))
	   (root (and (>f block-count (-f root-node-index 1))
		      #-subblocks-v2
		      (nth (-f block-count root-node-index) subblocks)
		      #+subblocks-v2
		      (when subblocks
			(constant-queue-nth (-f block-count root-node-index) subblocks))))
	   (root-node (and root (create-item-node root))))
      (when root-node
	(gather-children-nodes root-node)
	(export-node root-node))
      (cond (workspace?
	     (delete-frame workspace?))
	    (t
	     (delete-frame inspect-command)))
      root-node)))

(defun-for-system-procedure g2-get-method-inheritance-path (class-name method-name?)
  (get-tree-structure-for-inspect-command
    (if method-name?
	(tformat-text-string "show on a workspace the method inheritance path for ~s and the method ~s"
			     class-name method-name?)
	(tformat-text-string "show on a workspace the method inheritance path for ~s" class-name))))

(define-system-rpc-access (g2-get-method-inheritance-path ((or (no-item) (structure))))
    ((class-name symbol)
     (method-name?  (or (no-item) symbol)))
  (g2-get-method-inheritance-path class-name method-name?))

(defun-for-system-procedure g2-get-method-hierarchy (method-name)
  (get-tree-structure-for-inspect-command
    (tformat-text-string "show on a workspace the method hierarchy of ~s" method-name)))

(define-system-rpc-access (g2-get-method-hierarchy ((or (no-item) (structure))))
    ((method-name symbol))
  (g2-get-method-hierarchy method-name))

(defun-for-system-procedure g2-get-procedure-invocation-hierarchy ()
  (get-tree-structure-for-inspect-command
    (tformat-text-string "show on a workspace the procedure invocation hierarchy")
    t))

(define-system-rpc-access (g2-get-procedure-invocation-hierarchy ((or (no-item) (structure))))
    ()
  (g2-get-procedure-invocation-hierarchy))

(defun-for-system-procedure g2-get-procedure-calling-hierarchy (procedure-name?)
  (get-tree-structure-for-inspect-command
    (tformat-text-string "show on a workspace the procedure calling hierarchy of ~s"
			 (or procedure-name? 'item))))

(define-system-rpc-access (g2-get-procedure-calling-hierarchy ((or (no-item) (structure))))
    ((procedure-name?  (or (no-item) symbol)))
  (g2-get-procedure-calling-hierarchy procedure-name?))

(defun-for-system-procedure g2-get-procedure-caller-hierarchy (procedure-name?)
  (get-tree-structure-for-inspect-command
    (tformat-text-string "show on a workspace the procedure caller hierarchy of ~s"
			 (or procedure-name? 'item))))

(define-system-rpc-access (g2-get-procedure-caller-hierarchy ((or (no-item) (structure))))
    ((procedure-name? (or (no-item) symbol)))
  (g2-get-procedure-caller-hierarchy procedure-name?))

(defun-for-system-procedure g2-get-class-hierarchy (class-name?)
  (get-tree-structure-for-inspect-command
    (if class-name?
	(tformat-text-string "show on a workspace the class hierarchy of ~s"
			     class-name?)
	(tformat-text-string "show on a workspace the class hierarchy"))))

(define-system-rpc-access (g2-get-class-hierarchy ((or (no-item) (structure))))
    ((class-name? (or (no-item) symbol)))
  (g2-get-class-hierarchy class-name?))

(defun-for-system-procedure g2-get-workspace-hierarchy (workspace-name?)
  (get-tree-structure-for-inspect-command
    (if workspace-name?
	(tformat-text-string "show on a workspace the workspace hierarchy of ~s"
			     workspace-name?)
	(tformat-text-string "show on a workspace the workspace hierarchy"))))

(define-system-rpc-access (g2-get-workspace-hierarchy ((or (no-item) (structure))))
    ((workspace-name? (or (no-item) symbol)))
  (g2-get-workspace-hierarchy workspace-name?))


(defun-for-system-procedure g2-get-module-hierarchy (module-name?)
  (export-module-hierarchy module-name?))

(define-system-rpc-access (g2-get-module-hierarchy ((or (no-item) (structure))))
    ((module-name? (or (no-item) symbol)))
  (g2-get-module-hierarchy module-name?))

(defun export-graph-node (graph-node
			   &optional item-node-creation-function?
			   add-children-to-all-nodes-p)
  (let ((root-node (if item-node-creation-function?
		       (funcall item-node-creation-function?
				(graph-node-item graph-node))
		       (create-item-node (graph-node-item graph-node))))
	(children? (graph-node-children graph-node)))
    (cond ((null children?)
	   (when add-children-to-all-nodes-p
	     (set-children-of-node root-node
				   (allocate-evaluation-sequence nil))))
	  ((consp children?)
	   (loop with child-nodes? = '()
		 for child in children?
		 do
	     (eval-push (export-graph-node child
					   item-node-creation-function?
					   add-children-to-all-nodes-p)
			child-nodes?)
		 finally
		   (when child-nodes?
		     (set-children-of-node
		       root-node
		       (allocate-evaluation-sequence (nreverse child-nodes?))))))
	  (t
	   (set-children-of-node
	     root-node
	     (allocate-evaluation-sequence
	       (eval-list (export-graph-node children?
					     item-node-creation-function?
					     add-children-to-all-nodes-p))))))
    root-node))

(defun export-module-hierarchy (module-to-start-with?)
  (for-dummy-workstation
   (let*((required-modules-node nil)
	 (unrequired-modules-node? nil)
	 (ultimate-top-level-module?	; nil if no real top-level module
	   (top-level-kb-module? module-information))
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
		  ;orientationp
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
		  nil
		  ;left-edge-for-graph?
		  0
		  ;top-edge-for-graph?
		  0)))
	  (setq required-modules-node
		(create-item-node
		  (copy-constant-wide-string #w"Modules required by the KB:")))
	  (set-children-of-node required-modules-node
				(allocate-evaluation-sequence
				  (eval-list (export-graph-node (graph-display-root graph)))))
	  
	  (reclaim-graph-display graph))
	(progn 
	  (setq required-modules-node
		(create-item-node
		  (tformat-text-string
		    "No module hierarchy ~a~a"
		    (if module-to-start-with? "can be shown for " "exists, because the top-level module is unnamed.")
		    (or module-to-start-with? ""))))
	  (when (null module-to-start-with?)		  
	    (set-children-of-node required-modules-node
				  (allocate-evaluation-sequence
				    (eval-list (create-item-node module-information)))))))

    (loop with unrequired-modules? = '()
	  for module-information-instance being each class-instance of 'module-information
	  as parent-module? = (top-level-kb-module? module-information-instance)
	  initially (propagate-kb-requires-module-p-to-all-modules)
	  when (and (not (eq module-information-instance module-information))
		    (or (null parent-module?)
			(null ultimate-top-level-module?)
			(not (efficient-kb-requires-module-p parent-module?))))
	    do
	      (eval-push (create-item-node module-information-instance) unrequired-modules?)
	  finally
	    (when unrequired-modules?
	      (setq unrequired-modules-node?
		    (create-item-node
		      (copy-constant-wide-string #w"Modules not required by the KB:")))
	      (setq unrequired-modules? (nreverse unrequired-modules?))
	      (set-children-of-node unrequired-modules-node?
				    (allocate-evaluation-sequence unrequired-modules?))))
    
    (if unrequired-modules-node?
	(let ((root-node
	       (create-item-node (copy-constant-wide-string #w"KNOWLEDGE-BASE"))))	  
	  (set-children-of-node
	    root-node
	    (allocate-evaluation-sequence (eval-list required-modules-node
						     unrequired-modules-node?)))
	  root-node)
	required-modules-node))))
    


;;DO NOT MAKE THIS PUBLIC(IT SHOULD ONLY BE CALLED WITH VIABLE COMMAND STRINGS)
(defun-for-system-procedure g2-get-inspect-graph (inspect-command-string)
  (get-tree-structure-for-inspect-command inspect-command-string))

;;DO NOT MAKE THIS PUBLIC(IT SHOULD ONLY BE CALLED WITH VIABLE COMMAND STRINGS)
(define-system-rpc-access (g2-get-inspect-graph ((or (no-item) (structure))))
    ((inspect-command-string text))
  (g2-get-inspect-graph inspect-command-string))




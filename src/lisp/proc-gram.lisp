;; -*- Mode:Lisp; Package: AB; Base: 10; Syntax: Common-lisp -*-
(in-package "AB")

;;;; Module PROC-GRAM

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Michael Levin







;;;; Procedures Overview





;;; The procedures facility in G2 provides a concurrent and sequential program
;;; execution facility.  It may be used to implement process monitoring and
;;; control systems, as well as numeric and symbolic computations.  Procedures
;;; have a complete, explicit interface with inferencing and data service,
;;; making them a powerful tool for the implementation of control over
;;; real-world systems as well as inferencing.

;;; Procedures provide a new data environment in G2 distinct from inferencing
;;; evaluation, in which expressions may reference only local or so-called
;;; program variables.  This guarantees that expression evaluation values will
;;; never be UNKNOWN, and possible wait states in procedures are fully
;;; controlled by the user.

;;; Functions in G2 are being compatibly enhanced to include sequential,
;;; structured programming features.  They otherwise keep their current place in
;;; the G2 environment as implementations of value returning expression
;;; components (as opposed to side-effect causing procedures with possible wait
;;; states).  Note that they still may be called from both inference and
;;; simulation expressions, exhibiting the proper execution behavior for each
;;; environment, and now may also be called from procedure expressions, adopting
;;; the correct behavior when called from that environment.





;;;; Features of Statements Common to Procedures and Functions

;;; The following features and language facilities are common to both procedures
;;; and functions:

;;; *  Allow local variable declaration with optional type specifiers

;;; *  Use Pascal-like structured language constructs:
;;; BEGIN END compound statements
;;; IF THEN ELSE conditionals
;;; CASE selection
;;; FOR X = EACH generic iteration
;;; FOR X = expression TO, DOWN TO, BY numeric iteration
;;; REPEAT iteration

;;; *  Provide arbitrary exit points to iterations with EXIT IF statement

;;; *  Support compilation to machine code in future releases





;;;; Features of Procedures




;;; Procedures provide for implementation of complex control algorithms,
;;; side-effect causing computations, scheduled events, and concurrent
;;; processes.  Procedures have the following features:

;;; *  Execute as concurrent processes from rule consequents or procedure bodies
;;; via:
;;; START statement

;;; *  Execute as sub-procedures from procedure bodies via:
;;; START action

;;; *  Interface explicitly to inferencing via:
;;; INFER statement

;;; *  Allow all rule actions to be used as procedure statements:
;;; CONCLUDE THAT
;;; FOCUS ON
;;; INVOKE
;;; HALT
;;; INFORM
;;; SET
;;; ACTIVATE
;;; DEACTIVATE
;;; SHOW
;;; HIDE
;;; MOVE
;;; ROTATE
;;; CHANGE

;;; *  May cause side-effects

;;; *  May return multiple values

;;; *  May be suspended through timed WAIT statements or condition controlled
;;; WAIT statements

;;; *  May be declared as object-oriented methods of classes through the METHOD
;;; attribute

;;; *  Allow methods to be combined with the CALL MORE GENERAL METHOD statement,
;;; BEFORE, AFTER, and AROUND method combination

;;; *  Provide CALL ABORT and START ABORT commands for cancelling execution of
;;; procedures

;;; *  Provide an ON ABORT feature that declares clean-up code for aborted
;;; procedures

;;; * Provide CALL SUSPEND, START SUSPEND, CALL RESUME, and START RESUME
;;; commands for causing temporary cecession and restart of currently executing
;;; procedures.

;;; *  Provide ON SUSPEND and ON RESUME feature that specifies code to execute
;;; when a procedure is suspended, or resumed.

;;; *  Provide a SIGNAL command to invoke errors

;;; *  Provide ON ERROR code which can handle signalled errors, including system
;;; errors catchable by G2

;;; *  Support parallel execution of sub-statements in synchrony or as a race
;;; condition via:
;;; DO IN PARALLEL
;;; DO IN PARALLEL UNTIL ONE COMPLETES

;;; *  Exist as object instances that may have attributes and may be reasoned
;;; about

;;; *  Create transient object instances to represent invocations of procedures
;;; which may have attributes and be reasoned about





;;;; Features of Functions

;;; The current capabilities of functions are extended to permit value returning
;;; algorithms that use looping, conditional statements, local variables, and
;;; recursion.  Functions have the following features:

;;; *  Return values within expressions

;;; *  Interface implicitly to the inference engine when executed from rule
;;; expressions

;;; *  Interface implicitly to the simulator when executed from simulation
;;; expressions

;;; *  Provide implicit procedure evaluation restrictions when executed from
;;; procedure expressions, i.e. no references allowed to inferred or data served
;;; variables, and so no backward chaining

;;; *  Do not allow side-effects from within functions, i.e. no rule actions are
;;; available as statements

;;; *  Defined either with simple expressions or sets of sequential statements

;;; *  Include RETURN command for returning values from function statements





;;;; Examples

;;; These are examples of function and procedure definitions.  Note that all
;;; procedure and function specific words have been capitalized within this
;;; example, but that the language itself is case-insensitive.

;;; Procedure Definition:

;;; run-intersection-lights
;;;   (intersection : CLASS intersection,
;;;     cycle-time : QUANTITY, yellow-time : QUANTITY)
;;;   east-west : signal = the east-west-signals of intersection;
;;;   north-south : signal = the north-south-signals of intersection;
;;;   current-signal : signal = east-west;
;;;   BEGIN
;;;    REPEAT
;;;     WAIT UNTIL
;;;         not (the status of intersection is required-by-emergency-vehicle)
;;;       CHECKING EVERY 1 second;
;;;     DO IN PARALLEL UNTIL ONE COMPLETES
;;;       CALL cycle-signal (current-signal, cycle-time, yellow-time);
;;;       WAIT UNTIL the status of intersection is required-by-emergency-vehicle
;;;         CHECKING EVERY 1 second
;;;     END;
;;;     IF current-signal is the same object as east-west
;;;       THEN current-signal = north-south
;;;       ELSE current-signal = east-west
;;;    END
;;;   END

;;; cycle-signal (signal : signal,  cycle-time : INTEGER,  yellow-time : INTEGER)
;;;   BEGIN
;;;     SET the red-light of signal TO off;
;;;     SET the green-light of signal TO on;
;;;     WAIT FOR (cycle-time - yellow-time);
;;;     SET the green-light of signal TO off;
;;;     SET the yellow-light of signal TO on;
;;;     WAIT FOR yellow-time;
;;;     SET the yellow-light of signal TO off;
;;;     SET the red-light of signal TO on
;;;   END
;;;   ON ABORT
;;;     IF the green-light of signal is on
;;;       BEGIN
;;;         SET the green-light of signal TO off;
;;;         SET the yellow-light of signal TO on;
;;;         WAIT FOR yellow-time;
;;;         SET the yellow-light of signal TO off;
;;;         SET the red-light of signal TO on
;;;       END
;;;       ELSE
;;;         IF the yellow-light of signal is on
;;;           BEGIN
;;;             WAIT FOR yellow-time;
;;;             SET the yellow-light of signal TO off;
;;;             SET the red-light of signal TO on
;;;           END



;;; Function Definition

;;; fibonacci (x : integer)
;;;  fib : INTEGER = 1;
;;;  fib-trailer : INTEGER = 0;
;;;  fib-temp : INTEGER;
;;;  fib-so-far : INTEGER = 1;
;;;  BEGIN
;;;   IF x < 2
;;;     THEN RETURN x
;;;     ELSE
;;;       BEGIN
;;;         REPEAT
;;;           fib-temp = fib-so-far;
;;;           fib-so-far = fib-so-far + fib-trailer;
;;;           EXIT IF fib = x;
;;;           fib-trailer = fib-temp;
;;;           fib = fib + 1
;;;         END;
;;;         RETURN fib-so-far
;;;       END
;;;  END





;;;; Differences Between Procedures and Functions




;;; There are two requirements for the embedding of sequential statements in our
;;; system;  control and algorithm.  There are two facilities to address these
;;; needs, with differing compilation and execution approaches.

;;; The first facility, procedures, is new in Release 2.0.  Procedures are for
;;; the implementation of control, scheduled events, other side effect causing
;;; sequential code, and interruptible numeric algorithms.  Like functions,
;;; procedure definitions will contain a body of statements which are
;;; sequentially executed.  Unlike functions, procedures may have side-effect
;;; causing actions (e.g. CONCLUDE THAT, MOVE, SET, etc.)  as statements within
;;; the body.  They have WAIT statements.  They have an ALLOW OTHER PROCESSING
;;; statement to break up execution of large computations.  They are able to
;;; invoke other procedures through CALL (start and wait for completion of the
;;; procedure) and START (start and continue processing immediately) statements.
;;; They will only be able to reference the values of inferred or data served
;;; values by binding them to program variables using the INFER statement.  If a
;;; procedure needs a set of inferred results and needs to be sure they came
;;; from a consistent data set environment, many local variables can be bound
;;; within the same INFER statement, and it will only complete when all local
;;; variables have been able to receive values at the same time.  Procedures may
;;; be invoked from the consequents of rules with the START action, or from the
;;; bodies of procedures with START or CALL statements.

;;; The second facility is an extension to current functions for the
;;; representation of complex, side-effect free, value returning algorithms.
;;; Functions should be extended so that sequential statements, local variables,
;;; and looping statements may be embedded within function definitions.
;;; However, no action statements (CONCLUDE THAT, SET, etc.) are available in
;;; the body of a function, and the form may only be called for value.
;;; Functions may assign and mutate the values of locally defined variables.  A
;;; function returns values via the RETURN statement.

;;; Functions will execute is a manner which is consistent with the environment
;;; from which they are called.  When called from inference engine expressions,
;;; if a statement within a function does not complete for lack of a variable
;;; value, then the execution of the function as a whole will terminate
;;; returning UNKNOWN.  When called from simulations, references to variables in
;;; function expressions will use values from the simulator.  When called from
;;; procedure expressions they may not reference inferred variables.  The two
;;; exceptions to this rule are when a call is made from within the inference
;;; expression portion of an INFER statement, or when it is made from the
;;; condition portion of a WAIT statement.

;;; These definitions of how and when things may be interrupted allow for a more
;;; efficient compilation, give users a clear framework within which waiting for
;;; variable values may be managed, and determine the points at which execution
;;; may be interrupted.  It is important for users to know exactly when the
;;; execution of a procedure or function may be interrupted, since values which
;;; that execution depends upon may change during the interruption.  With the
;;; restrictions given above, procedures may only be interrupted at ALLOW OTHER
;;; PROCESSING, WAIT, CALL (if the called procedure interrupts), CALL ABORT (if
;;; the ON ABORT code interrupts), and INFER statements.






;;;; Procedure Invocation Class




;;; Within a procedure, one can optionally include a class name for a procedure
;;; invocation instance which will be created when a procedure is called.  When
;;; we can make subclasses of any class, then the grammar for this slot should
;;; be extended to allow any subclass of procedure invocation.  Until then, the
;;; only available values should be none or procedure-invocation.

(add-grammar-rules
  '((class-of-procedure-invocation? 'none)
    (class-of-procedure-invocation? 'procedure-invocation)
    (class-of-procedure-invocation? class)))

(def-slot-value-compiler class-of-procedure-invocation? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(define-category-evaluator-interface (class-of-procedure-invocation?
				       :access read-write)
    (or (no-item)
	(member procedure-invocation)
	(named unreserved-symbol))
  
  ((set-form (evaluation-value))
   (if evaluation-value
       (call-category-setter 'unreserved-symbol evaluation-value nil nil nil)
       'none))
  ((get-form (slot-value))
   slot-value))

(def-slot-value-writer class-of-procedure-invocation? (class?)
  (if class?
      (twrite-symbol class?)
      (twrite-string "none")))






;;;; Grammar for Function and Procedure Statements




;;; The following grammar code implements grammar for procedure expressions, and
;;; some of the rewrite rules for that grammar.



(add-grammar-rules
  '((procedure-expression unique-expression)
    (procedure-logical-expression unique-logical-expression)

    (procedure-untyped-expression procedure-expression)
    (procedure-untyped-expression procedure-logical-expression)

    (procedure-untyped-expression-list procedure-untyped-expression-list-1 1 cdr)
    
    (procedure-untyped-expression-list-1
      (procedure-untyped-expression '\, procedure-untyped-expression)
				 (2 1 3))
    (procedure-untyped-expression-list-1
      (procedure-untyped-expression '\, procedure-untyped-expression-list-1)
				 (2 1 3) simplify-associative-operation)

;    (proc-simple-statement proc-inform-simple-statement)
;
;    (proc-inform-simple-statement
;      (`inform-simple procedure-expression
;       'for 'the 'next procedure-expression)
;      (inform-simple-statement 2 6))

    ))


;;; There are three categories of statements:  common statements, function
;;; statements, and procedure statements.  Common statements are available in
;;; both function and procedure bodies.  Function statements are only available
;;; in function bodies, and procedure statements are only available in procedure
;;; bodies.

;;; The following conventions are used in presenting this grammar.  Items
;;; enclosed in curly brackets can be repeated an arbitrary number of times
;;; (including zero).  Items in square brackets are optional, i.e. they may be
;;; omitted or included.  Items in all capital letters are literals.  Items
;;; seperated by double vertical bars are alternative items for the given
;;; grammar item.





;;;; Common Statements

;;; Common statements may be used in either functions or procedures.  All of the
;;; statements in this section are common statements.  Note that common
;;; statements are used in either procedure or function bodies.  Within the
;;; definition of common statements, the term "statement" is used to mean any
;;; common statement, or any function statement when in a function, or any
;;; procedure statement when in a procedure.




;;; `Compound Statement', `BEGIN Statement', and `END Statement'

;;; At any point where a common statement may be entered, a compound statment
;;; may be entered.  A compound statement consists of the literals BEGIN and END
;;; enclosing a (possibly empty) set of statements separated by semicolons.  The
;;; last statement may optionally be followed by a semicolon.

;;; BEGIN END

;;; BEGIN
;;;   statement {; statement} [;]
;;; END

;;; Compound statement grammar is implemented below in the section for procedure
;;; compound statements.



;;; `Assignment Statement'

;;; Assignment of local variables is an implied command.  We can do this without
;;; syntactic confusion between the equal sign as a statement and the equal sign
;;; as a predicate since we do not allow expressions as statements.

;;; variable-name = expression

(add-grammar-rules
  '((proc-simple-statement proc-assignment-statement)
    (proc-assignment-statement (local-name '= procedure-untyped-expression)
			       (assignment-statement 1 3))
    ))




;;; `Conditional Statement' or `IF Statement', `ELSE Clause to IF'

;;; Conditional statements are IF THEN statements with optional ELSE clauses,
;;; and CASE statements.  The syntax for IF statements is as follows.

;;; IF expression THEN statement [ELSE statement]

;;; It is possible to write a nested set of IF statements such that there is an
;;; ambiguity about the particular IF statement to which an ELSE may apply.  The
;;; following is an example of such a form.

;;; IF x = y THEN IF x = z THEN RETURN 10 ELSE RETURN 12

;;; In one interpretation x would have to be equal to y for this statement to
;;; execute RETURN 12, and in the other interpretation x would have to be not
;;; equal to y for this statement to execute RETURN 12.  We will follow the
;;; convention of Pascal, where ELSE clauses bind to the deepest nested
;;; available IF, and give the above form the first interpretation, so that the
;;; above form will have the same meaning as the following form.

;;; IF x = y THEN
;;;   BEGIN
;;;     IF x = z
;;;       THEN RETURN 10
;;;       ELSE RETURN 12
;;;   END

(add-grammar-rules
  '((proc-statement proc-if-then-statement)
    (proc-statement proc-if-then-else-statement)
    (proc-if-then-statement
      ('if procedure-logical-expression
       'then proc-simple-statement)
      (if-then-statement 2 4))

    (proc-if-then-else-statement
      ('if procedure-logical-expression
       'then proc-simple-statement 'else proc-statement)
      (if-then-else-statement 2 4 6))))




;;; `Selection Statement' or `CASE Statement'

;;; The other conditionalizing form is the CASE statement.  CASE performs
;;; dispatch to code based on a selection amongst a set of mutually exclusive
;;; and collectively exhaustive values.  Its format is as follows

;;; CASE ( expression ) OF
;;;   case-choice {; case-choice} [;]
;;;   END

;;; Each CASE-CHOICE takes the following format.  If the OTHERWISE clause is
;;; included, it must be the last case-choice of the statement.

;;; constant {, constant}: statement
;;; OTHERWISE : statement

;;; The CASE statement will cause the given expression to be evaluated, and then
;;; will execute the statement whose constant value matches the value returned
;;; by the expression.  The comparison will be performed as if by the =
;;; operator.  An optional OTHERWISE case choice may be included as the last
;;; choice in a CASE statement.  If the value of the expression matches none of
;;; the given constants, then the statement for the OTHERWISE choice will be
;;; executed.  If the value returned by the expression matches none of the given
;;; constants and no OTHERWISE choice is specified, then a level 1 error will be
;;; signalled.

;;; Still needs to be implemented.  -jra 6/13/89


;; Modified the following grammar so that the "otherwise" choice is only allowed
;; when there is another (non-otherwise) case choice preceeding it.  (It also
;; must be the last case choice.) This prevents a procedure-compiler crash when
;; only the "otherwise" choice was present.  This fix adds a new grammar
;; category called final-case-otherwise-choice.  This causes the
;; rest-of-case-statement category not to end in an "otherwise" choice, but
;; reset-of-case-statement-1 can.  The function, reason-for-bad-parse-as-string,
;; in grammar1 was modified to reflect the fix.  -cpm 28jun90.


(add-grammar-rules
  '((proc-simple-statement proc-case-statement)

    (proc-case-statement ('case '\( expression '\) 'of rest-of-case-statement)
			 (case-statement 3 . 6))

    (rest-of-case-statement (final-case-choice 'end) (1))
    (rest-of-case-statement (final-case-choice '\; 'end) (1))

    (rest-of-case-statement (case-choice '\; rest-of-case-statement-1 'end)
			    (2 1 3) simplify-associative-operation cdr)

    (rest-of-case-statement-1 (case-choice '\; rest-of-case-statement-1)
			      (2 1 3) simplify-associative-operation)
    (rest-of-case-statement-1 final-case-choice)
    (rest-of-case-statement-1 (final-case-choice '\;) 1)

    ;; Added rule for new grammar category. -28jun90, cpm.
    (rest-of-case-statement-1 final-case-otherwise-choice)

    ;; Added rule for new grammar category. -28jun90, cpm.
    (rest-of-case-statement-1 (final-case-otherwise-choice '\;) 1)

    (case-choice (case-tag-list '\: proc-statement)
		 (1 3) fix-case-choice)

    (final-case-choice case-choice)

    ;; Changed from final-case-choice to final-case-otherwise-choice. -28jun90,
    ;; cpm.
    (final-case-otherwise-choice ('otherwise '\: proc-statement) (1 3))

    (case-tag-list case-tag)
    (case-tag-list (case-tag '\, case-tag-list)
		   (2 1 3) simplify-associative-operation)

    (case-tag number)
    (case-tag unreserved-symbol)
    (case-tag whole-string)
    ))




(defun fix-case-choice (form)
  (let ((label (first form)))
    (cond
      ((or (eq label 'otherwise)
	   (and (consp label)
		(memq 'otherwise label)))
       (values bad-phrase
	       'otherwise))

      ((or (atom label)
	   (phrase-float-p label))
       (phrase-cons (phrase-list label) (cdr form)))

      (t (phrase-cons (cdr label) (cdr form))))))

(declare-grammar-transform-can-return-bad-phrase fix-case-choice)





;; Michael, could you fix the grammar for CASE such that the word "otherwise" is
;; not available as a symbol value within the CASE?  I've added code to the
;; fix-case-choice function so that it is rejected now, but the rejection
;; happens at the case-choice level, not the case-tag-list level, and so the
;; parsing elipsis appears after the case choice, not immediately after the
;; illegal reference to otherwise.  Also, it seems that it is not possible to
;; include a semicolon after the last case choice where there is more than
;; choice.  -jra 6/18/89




;;; `Iteration Statement' or `REPEAT Statement', and `EXIT IF Statement'

;;; Iteration constructs with embedded termination conditions are provided
;;; through the REPEAT, FOR, and EXIT IF statements.  The REPEAT statement is
;;; given a set of statements possibly containing EXIT IF statements.  The set
;;; of statements will be repeatedly executed until an EXIT IF statement is
;;; executed whose expression returns TRUE.  Note that EXIT IF statements may be
;;; further nested within IFs and other structured statements, but will still
;;; affect the iteration statement surrounding the EXIT IF.  EXIT IF statements
;;; nested within a futher call to REPEAT or FOR will only affect the innermost
;;; iteration statement.  It is a language error to use a EXIT IF statement
;;; outside of the body of some enclosing iteration statement.

;;; REPEAT
;;;   statement {; statement} [;]
;;; END

;;; EXIT IF logical-expression

(add-grammar-rules
  '((proc-simple-statement proc-repeat-statement)
    (proc-simple-statement proc-exit-if-statement)
    (proc-repeat-statement ('repeat proc-compound-1)
			   (repeat-statement . 2))
    (proc-exit-if-statement ('exit 'if procedure-logical-expression)
			    (exit-if-statement 3))))




;;; `Generic Iteration' or `FOR EACH Iteration Statement'

;;; Iterations over generic designations are performed using a "FOR var = EACH"
;;; iterator.  The body will be executed once for each item that the generic
;;; reference denotes, with that item bound to the given variable..  If the
;;; generic designation refers to no objects, the body will not be executed.
;;; EXIT IF statements are legal within the body of the iteration statement, and
;;; may terminate the iteration, leaving the variable bound as it was at the
;;; time the EXIT IF was executed.

;;; FOR variable-name = EACH generic-designation
;;;   DO
;;;     statement {; statement} [;]
;;;   END

(add-grammar-rules
  '((proc-simple-statement proc-for-each-statement)
    (proc-for-each-statement
     ('for local-name '= 'each proc-iterator proc-compound-1)
     (for-each-statement (2 5) . 6))

    (proc-iterator (class 'do) (any 1))
    (proc-iterator (procedure-class-phrase-role unique-designation 'do) (any 1 2))

    ;; Why are the following two cases here?  I would have thought that the
    ;; proc-iterator clause above, by including procedure-class-phrase-role, and
    ;; the defining of user-attribute-names below would have covered it, but no,
    ;; there are these two defintions within spitting distance of each other.
    ;; Someone who understands the parser might want to tackle this conundrum,
    ;; but not me man!  Copying it for attribute-names.  -jra 9/23/96
    (proc-iterator ('symbol 'that 'is a-or-an 'user-defined 'attribute 'name 'of
		    designation 'do)
     (any (user-attribute-names 1) 9))
    (proc-iterator ('symbol 'that 'is a-or-an 'attribute 'name 'of designation 'do)
     (any (attribute-names 1) 8))

    (procedure-class-phrase-role (class preposition) (1 2) translate-role-and-preposition)
    (procedure-class-phrase-role (element-type 'in) (element-iterator 1))
    (procedure-class-phrase-role ('name 'of) (role-server name))
    (procedure-class-phrase-role
     ('symbol 'that 'is a-or-an 'user-defined 'attribute 'name 'of)
     (user-attribute-names 1))
    (procedure-class-phrase-role
     ('symbol 'that 'is a-or-an 'attribute 'name 'of)
     (attribute-names 1))
    (procedure-class-phrase-role ('symbol 'that 'is 'an 'inferior-class 'of)
     (inferior-class 1))
    (procedure-class-phrase-role ('symbol 'that 'is 'a 'superior-class 'of)
     (superior-class 1))
    (procedure-class-phrase-role (class 'that 'contains)
     (member-iterator 1))))






;;; `Numeric Iteration' or `FOR Iteration Statement'


;;; A simple numeric iterator statement is also supplied.  The body will be
;;; executed with the given variable containing the value of the initial
;;; expression, and then values either increasing by one up to and possibly
;;; including the final value, or down to and possibly including the final
;;; value.  Note that the given variable must be declared at the top of this
;;; procedure definition.  On entrance to this form, the initial expression will
;;; be evaluated and the value stored in the given variable.  Then the given TO
;;; or DOWN TO expression will be evaluated and its value stored in an internal
;;; variable.  Next, any BY expression will be evaluated and its value stored in
;;; an internal variable as the step size.  If no step size is given and the
;;; termination value is given with TO, then the stepping value defaults to 1.
;;; If the termination value is given with DOWN TO, then the stepping value
;;; defaults to -1.  The internal variables will take on the same type as the
;;; iteration variable.  If TO is specified and if the initial value is less
;;; than or equal to the termination value, the statement will be executed, the
;;; stepping value will be added to the variable value, and then the termination
;;; condition tested again.  If DOWN TO is specified, then the body will be
;;; executed when the value is greater than or equal to the termination value,
;;; with the bound variable decremented by one each iteration.  EXIT IF
;;; statements are allowed within the body of the iteration, and may cause the
;;; iteration to terminate, leaving the iteration variable bound to whatever
;;; value it had at the time the EXIT IF was executed.

;;; FOR variable-name = expression
;;;     TO || DOWN TO expression
;;;    [BY expression]
;;;   DO
;;;     statement {; statement} [;]
;;;   END

(add-grammar-rules
  '((proc-simple-statement proc-for-numeric-statement)
    (proc-for-numeric-statement
      ('for local-name '= proc-numeric-iterator proc-numeric-do
       proc-compound-1)
      (for-numeric-statement (2 . 4) 5 . 6))

    (proc-numeric-iterator
      (procedure-expression to-phrase procedure-expression)
      (2 1 3))
    (proc-numeric-iterator
      (procedure-expression to-phrase procedure-expression
			    'by procedure-expression)
      (2 1 3 5))
    
    (to-phrase 'to)
    (to-phrase ('down 'to) down-to)

    (proc-numeric-do 'do)
    (proc-numeric-do ('do 'in 'parallel) do-in-parallel)
    (proc-numeric-do ('do 'in 'parallel 'until 'one 'completes)
		     do-in-parallel-until-one-completes)))




;;; `GOTO Statement' and `Tag Statements'

;;; In keeping with the tradition of structured programming languages allowing
;;; unstructured programming, G2 procedures will include a GOTO statement.  It
;;; takes a tag which is either a symbol or a constant integer, and causes
;;; processing to continue at the statement immediately following the named tag
;;; within the current procedure.

;;; GOTO symbol || constant-integer

;;; GOTO statements may be executed from within ON RESUME and ON ERROR bodies
;;; back to tags in the main code body of a procedure, and from the bodies of
;;; IN-PARALLEL statements back into the context surrounding the IN-PARALLEL
;;; statement.  However, GOTO statments may not transfer control to tags within
;;; parallel code bodies, into event handlers, or out of an ON SUSPEND or ON
;;; ABORT body back into the main code body.

;;; Note that in cases where a GOTO statement is being executed from within a
;;; parallel statement to a tag which is outside of the parallel statement,
;;; first all parallel bodies to the code executing the GOTO statement will be
;;; CALL ABORTed, and only then will control actually transfer to the statement
;;; after the named tag.  This is also true when executing GOTO statments out of
;;; RESUME or ERROR bodies back into the main body of a procedure.  In this
;;; situation any CALLs from the existing main body are CALL ABORTed, and
;;; execution then continues at the statement following the named tag.

;;; Tags for GOTO statements are statements, declaring either a symbol or a
;;; constant integer as the tag.  The symbol or integer is followed by a colon.

;;; symbol :

;;; constant-integer :

(add-grammar-rules
  '((proc-simple-statement proc-go-to-statement)
    (proc-go-to-statement ('go 'to label) (go-to-statement 3))
    (label positive-integer)
    (label unreserved-symbol)))






;;;; Procedure Definitions



;;; Procedure definitions contain a procedure compound statement as their
;;; definition, and may optionally contain declarations for argument types,
;;; declarations for local variables, and clean-up forms to execute in case of
;;; suspends, resumes, errors, or aborts.  Procedures are created by choosing
;;; the new definition option on the workspace menu, and then picking the
;;; procedure definition option.  It is allowable to define new classes of
;;; procedures using the class definition facilities, and to assign attributes
;;; to instances of these newly defined procedure classes.  The procedure class
;;; is a subclass of item, and so may be reasoned about.  Run-time evaluation
;;; may be performed to determine the procedure which will be invoked in a given
;;; statement.  Procedures can be declared to have identity arguments to
;;; restrict concurrent executions of the same operation on an object.
;;; Procedures may also be declared as methods of classes, providing run-time
;;; selection of the correct procedure to execute an operation, based on the
;;; class of the first argument to the procedure.






;;; `Object-Oriented Methods'




;;; Procedures may be declared as object-oriented methods by setting the METHOD
;;; attribute of a procedure definition to the class with which this procedure
;;; should be associated.  Methods of a class are invoked on instances via CALL
;;; and START commands to the method name, in the same way that normal
;;; procedures are invoked.  (Note:  We should also define functions as
;;; methods.)  When a method style procedure is invoked, the class of the first
;;; argument will be used to find the method for this procedure name, and that
;;; method will be invoked on the given argument list.  Users can combine
;;; procedure methods defined at different levels of the class hierarchy to
;;; produce methods for classes which perform a composite behavior specified by
;;; the collection of combined methods.

;;; Within methods it is possible to then invoke the next most specific method,
;;; allowing combination of methods defined at different levels of the class
;;; hierarchy.

;;; Invocations of procedures may also be given "identity".  The identity of a
;;; procedure invocation is determined by its name and a set of arguments which
;;; may be specified in the IDENTITY ARGUMENTS attribute of the procedure
;;; definition.  Identity for a procedure invocation means that only one
;;; invocation with a given identity may be under way at the same time, that
;;; further CALLS and STARTS of that invocation must wait until completion of
;;; the first one, and that these invocations may be aborted with the CALL ABORT
;;; or START ABORT statements.  Procedure invocation identity is defined in
;;; section below.

;;; (Note:  We should allow designation of methods with "the <method-name>
;;; method of <class>" designations.  Further define what an individual method
;;; definition is, and what an abstract method which combines them is.)

;;; (Note:  This section on object oriented methods needs lots of expansion.  It
;;; needs to talk about before, after, around, and base methods, as well as the
;;; actual method of a procedure, which may be an internally generated procedure
;;; which performs the correct combination of the different types of methods for
;;; an operation.)





;;; `Procedure Definitions'

;;; Procedure definitions and type declarations for arguments and return values
;;; take the following format.

;;; procedure-name typed-argument-list [= return-types]
;;;   {local-variable-declaration ;}
;;;   procedure-compound-statement
;;;   [{ON ERROR error-type-var procedure-compound-statement}
;;;     [[ON SUSPEND suspend-reason-var procedure-compound-statement]
;;;       [[ON RESUME resume-reason-var procedure-compound-statement]
;;;         [[ON ABORT abort-reason-var procedure-compound-statement]]]]]

;;; The typed-argment-list is a list of arguments, separated by commas, with
;;; optional type declarations.  Its format is as follows.

;;; ()

;;; (argument-name [: argument-type] {, argument-name [: argument-type]})

;;; Return-types declares the types of the returned values of this procedure,
;;; and is a list of types enclosed in parentheses, separated by commas.  To
;;; declare that a procedure returns no values, use an empty list.

;;; ()

;;; (value-type {, value-type})

;;; (To be addressed:  Must procedures declare the values they return?)

;;; Note that all event handlers (i.e. ON ERROR, ON SUSPEND, ON RESUME, and ON
;;; ABORT) must be entered in the order shown.  Each declares a variable to be
;;; bound to any supplied reason for the event, and a statement to be executed
;;; when the event occurs.


(defun nil-function (x)
  (declare (ignore x))
  nil)

(add-grammar-rules
  '((procedure-definition
      (procedure-name proc-parameter-list procedure-definition-1)
      (1 2 . 3) fix-procedure-definition)

    (procedure-definition-1
      (proc-return-type-list procedure-definition-2) (1 . 2))
    (procedure-definition-1 procedure-definition-2)
    ;; See note in fix-procedure-definition concerning the lack of
    ;; a transform to (nil . 1) in the immediate preceeding rule.

    (procedure-definition-2
      (proc-local-name-declr proc-compound-statement) (1 2))
    (procedure-definition-2 proc-compound-statement (nil 1))

    (procedure-name? procedure-name)
    (procedure-name? 'none)
 
    (proc-parameter-list ( '\( '\) ) nil nil-function)
    (proc-parameter-list ( '\( proc-parameter-list-1 '\) ) 2 cdr)

    ))


(def-slot-value-compiler procedure-name? (parse-result)
  (if (eq parse-result 'none) nil parse-result))

(def-slot-value-writer procedure-name? (procedure-name?)
  (if (null procedure-name?) 
      (twrite-symbol 'none)
      (twrite procedure-name?)))

(def-slot-value-writer read-only-procedure-name? (procedure-name?)
  (if (null procedure-name?) 
      (twrite-symbol 'none)
      (twrite procedure-name?)))

(define-category-evaluator-interface (procedure-name?
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (call-category-setter 'standard-or-class-qualified-symbol?
			 evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter 'standard-or-class-qualified-symbol?
			 slot-value nil nil)))

(define-category-evaluator-interface (read-only-procedure-name?
				       :access read)
    (or (no-item) symbol)
  ((get-form (slot-value))
   (call-category-getter 'standard-or-class-qualified-symbol?
			 slot-value nil nil)))


(add-grammar-rules-for-list 'proc-parameter-list-1 'proc-parameter)

(add-grammar-rules
  '((proc-parameter (local-name '\: proc-type) (1 3))

    (proc-type ('class class))
    
    (proc-logical-type 'truth-value)
    (proc-non-logical-type ('class class))
    
    ))



;;; The function `fix-procedure-definition' does a modifying replacement of the
;;; local names declaration which is the fourth of the definition.  Any subform
;;; ((|,| x y z ...) type) is replaced by ... (x type) (y type) (z type) ...

(defun fix-procedure-definition (form)
  ;; If form is of length four, this is because there was no way
  ;; to put a nil in place of an absent proc-return-type-list given
  ;; the quirks of the parser when a -> b -> c.
  (if (=f (length form) 4)
      (setq form
	    (phrase-list (first form) (second form) nil
			 (third form) (fourth form))))

  (setf (fourth form)
	(loop for item in (fourth form) nconcing
	      (if (symbolp (car item))
		  (phrase-list item)
		  (loop with type = (second item)
			for local-name in (cdar item) nconcing
			(phrase-list
			  (phrase-list local-name type))))))
;  (nsubst 'number 'quantity form)
  form)




;;; `Local Variables'



;;; Local variables with types may be declare for the body of a function or
;;; procedure.  They may optionally have initializations.  A local variable is
;;; like a local name within a rule, in that an item or a datum may be bound to
;;; the local variable symbol, and thereafter used in expressions to refer to
;;; that value.  The value of local variables within functions and procedures
;;; may be changed using an assignment statement.  The compiler should provide
;;; an error warning when a local variable has been referenced before its value
;;; has been set with either an initialization or an assignment within the body
;;; of the function.  The format for local-variable-declarations is as follows.

;;; local-variable-name [: type] [= expression]

;;; local-variable-name [, local-variable-name] [: type]

;;; The following symbols are available as type specifiers.  As we add new data
;;; structures, they will become available as type specifiers.

;;; QUANTITY || TRUTH-VALUE || SYMBOL || TEXT || CLASS class

;;; Note that we have removed the type ANY TYPE.  We needed to know whether a
;;; form was an expression for datum or was a designation in order to compile
;;; it.  We still could have a non-specific datum type, but there seemed to be
;;; no desire for such a type.  -jra 6/13/89

;;; The types integer and float have been removed from the list.  Until we have
;;; a compiler which can note inconsistent uses of float and integer we should
;;; not allow these types at all.  The current plan is to include integer and
;;; float, plus a type checking compiler for expressions, in Release 2.1.  -jra
;;; 6/13/89

;;; The type checking compiler is going into Version 3.0, and so integer and
;;; float are now being added.  -jra 11/24/90

;;; The types value and item-or-value are now being added.  -jra 8/21/91

(add-words-as-instances-of-category
  proc-type
  (truth-value symbol text time-stamp integer float long))

(add-grammar-rules
  '((proc-type 'quantity number)
    (proc-type 'value datum)
    (proc-type 'item-or-value item-or-datum)
    (proc-type 'sequence (sequence))
    (proc-type 'structure (structure))))

(add-words-as-instances-of-category
  proc-non-logical-type
  (symbol text time-stamp integer float long))

(add-grammar-rules
  '((proc-non-logical-type 'sequence (sequence))
    (proc-non-logical-type 'structure (structure))
    (proc-non-logical-type 'quantity number)
    (proc-logical-or-non-logical-type 'value datum)
    (proc-logical-or-non-logical-type 'item-or-value item-or-datum)
    (proc-return-type-list ('= '\( '\) ) 1 nil-function)
    (proc-return-type-list ('= '\( proc-type '\) ) (3))
    (proc-return-type-list ('= '\( proc-return-type-list-1 '\) ) 3 cdr)

    (proc-return-type-list-1 (proc-type '\, proc-type) (2 1 3))
    (proc-return-type-list-1 (proc-type '\, proc-return-type-list-1)
			     (2 1 3) simplify-associative-operation)

    (proc-local-name-declr (proc-local-name-declr-1 '\; ) 1 cdr)

    ))

(add-grammar-rules-for-list 'proc-local-name-declr-1 '
			    proc-local-name-element '\;)


(add-grammar-rules
  '((proc-local-name-element (local-name '\: proc-type) (1 3))
    (proc-local-name-element (local-name-list-1 '\: proc-type) (1 3))
    (proc-local-name-element
      (local-name '\: proc-logical-type '= procedure-logical-expression)
      (1 3 5))
    (proc-local-name-element
      (local-name '\: proc-non-logical-type '= procedure-expression)
      (1 3 5))
    (proc-local-name-element
     (local-name '\: proc-logical-or-non-logical-type '= procedure-expression)
     (1 3 5))
    (proc-local-name-element
     (local-name '\: proc-logical-or-non-logical-type '=
      procedure-logical-expression)
     (1 3 5))))




;;;; Procedure Statements




;;; Procedure compound statements are compound statements, delimited by BEGIN
;;; and END, which contain common and procedure statements.  The specific
;;; procedure statements are detailed below.

;(add-grammar-rules
;  '((proc-compound-statement ('begin 'end) (begin-statement))
;    (proc-compound-statement ('begin proc-statement 'end) (begin-statement 2))
;    (proc-compound-statement
;      ('begin statement-or-tag-with-punctuation 'end) (begin-statement 2))
;;    (proc-compound-statement ('begin label '\: 'end)
;;			     (begin-statement (tag-statement 2)))
;    (proc-compound-statement ('begin proc-statements 'end) (begin-statement . 2))

;    (proc-statements proc-statements-1 1 cdr)
;    (proc-statements (proc-statements-1 '\;) 1 cdr)

;    (proc-statements-1 (statement-or-tag-with-punctuation proc-statement) (\; 1 2))
;    (proc-statements-1 (statement-or-tag-with-punctuation label '\:)
;		       (\; 1 (tag-statement 2)))

;    (proc-statements-1 (statement-or-tag-with-punctuation proc-statements-1) (\; 1 2)
;		     simplify-associative-operation)

;    (statement-or-tag-with-punctuation (proc-statement '\;) 1)
;    (statement-or-tag-with-punctuation (label '\:) (tag-statement 1))
;    ))

(add-grammar-rules
  '((proc-statement proc-simple-statement)
    (proc-simple-statement proc-compound-statement)
    ))

(add-grammar-rules
  '((proc-compound-statement ('begin proc-compound-1) (begin-statement . 2))

    (proc-compound-1 (label '\: proc-compound-1)
		     ((tag-statement 1) . 3) convert-to-true-list)
    (proc-compound-1 (proc-statement proc-compound-2) (1 . 2) convert-to-true-list)
    (proc-compound-1 'end nil nil-function)

    (proc-compound-2 'end nil nil-function)
    (proc-compound-2 ('\; proc-compound-1) 2)
    ))

(add-grammar-rules
  '((proc-compound-statement
      ('begin proc-compound-1
       'on 'error '\( local-name '\, local-name '\)
       proc-compound-1)
      (on-error-statement
	(begin-statement . 2)
	6 8
	(begin-statement . 10)))

    ;; Single argument version of on error
    ;; ajs (5/25/96)
    (proc-compound-statement
      ('begin proc-compound-1
       'on 'error '\( local-name '\)
       proc-compound-1)
      (on-error-statement-new
	(begin-statement . 2)
	6 
	(begin-statement . 8)))
    
    (proc-simple-statement proc-signal-statement)
    (proc-signal-statement
      ('signal procedure-expression '\, procedure-expression)
      (signal-statement 2 4))

    ;; Single argument version of signal
    (proc-signal-statement
      ('signal procedure-expression)
      (signal-statement-new 2))

    ))

;; convert-to-true-list is needed only because of a bug in the parser!!!
;; The rule (proc-compound-2 'end nil nil-function) was not applying a transform.
;; For some unknown reason, it would apply the transform if the following
;; spurious rule is added: (proc-compound-2 nonsense-category nil nil-function)!!

;; Converts a list* to a true list by stuffing nil into cdr of last.
;; The value is eq the argument in all cases.

(defun convert-to-true-list (x)
  (loop for y = x then (cdr y)
	while (consp y)
	do
    (when (and (atom (cdr y)) (cdr y))
      (setf (cdr y) nil)))
  x)


;;; `Procedure Value Return' or `Return Statement'

;;; The RETURN statement for procedures causes this procedure to complete
;;; normally, returning an arbitrary number of values to the caller.  Execution
;;; of a procedure can be normally completed with this command or by completing
;;; execution of the last statement in a procedure body, i.e. falling off the
;;; end of the procedure statement.  If a procedure completes by falling off the
;;; end, no values will be returned.  This statement will evaluate all value
;;; expressions, then CALL ABORT any other parallel procedure bodies of this
;;; procedure, and finally it will continue execution of the procedure
;;; invocation which called this procedure.

;;; RETURN

;;; RETURN expression {, expression}

;;; A calling procedure may choose to receive as many of the returned values as
;;; desired, discarding any extras.  It is an error for a procedure to attempt
;;; to receive more values than a called procedure supplies.

(add-grammar-rules
  '((proc-simple-statement proc-return-statement)
    (proc-return-statement 'return (return-statement)) 
    (proc-return-statement ('return procedure-untyped-expression)
			   (return-statement 2))
    (proc-return-statement ('return procedure-untyped-expression-list)
			   (return-statement . 2))))




;;; `Procedure Assignment Statement' or `Assignment Statement'

;;; Within procedures the assignment statement may be used in its common
;;; statement form, or it may be used to receive multiple values from a CALLed
;;; procedure, assigning those values to local variables.  The user is not
;;; required to receive all values that the called procedure produces.  However,
;;; it is an error to attempt to receive more values than a procedure supplies.
;;; The ACROSS grammar can be used to execute a call statement on another
;;; system.

;;; var-name {, var-name} =
;;;   CALL procedure-designation ([expression] {, expression})
;;;     [ACROSS interface-designation]

;;; The system-call (originally lisp-call) statement is used to call out to Lisp
;;; from procedures.  It is only available in development G2 and should only be
;;; used in system-procedures.  The name of the lisp-function is not evaluated.
;;; The name of this statement has been changed to system-call since the
;;; statement should only be used in system procedures and the term "lisp"
;;; should not be used in G2 KB's.  We do not intend to make system procedures
;;; visible to the user, but the "lisp" term is being removed in case users have
;;; access to the system procedure in the future.

;;; var-name {, var-name} =
;;;   SYSTEM CALL symbol ([expression] {, expression})

(add-grammar-rules
  '((proc-simple-statement proc-call-assignment-statement)
    (proc-simple-statement proc-call-next-method-assignment-statement)

    (proc-call-assignment-statement
      (local-name-list '= 'call procedure-designation procedure-arguments)
      (call-assignment-statement 1 4 5 nil))
    (proc-call-assignment-statement
      (local-name-list '= 'call procedure-designation procedure-arguments
		       'across unique-designation)
      (call-assignment-statement 1 4 5 7))

    ;; Call next method is only available in procedure methods.  Test this in
    ;; the transforming function.
    (proc-call-next-method-assignment-statement
      (local-name-list '= 'call 'next 'method )
      (call-next-method-assignment-statement 1)
      test-call-next-method-parse)

    (local-name-list local-name (1))
    (local-name-list local-name-list-1 1 cdr)

    ;; local-name-list-1 referenced by proc-local-name-declr.
    (local-name-list-1 (local-name '\, local-name) (2 1 3))
    (local-name-list-1 (local-name '\, local-name-list-1)
		       (2 1 3) simplify-associative-operation)
    (procedure-arguments ( '\( '\) ) nil nil-function)
    (procedure-arguments ( '\( procedure-argument '\) ) (2))
    (procedure-arguments ( '\( procedure-arguments-1 '\) ) 2 cdr)

    (procedure-argument procedure-untyped-expression)

    (procedure-arguments-1 (procedure-argument '\, procedure-argument) (2 1 3))
    (procedure-arguments-1 (procedure-argument '\, procedure-arguments-1)
			 (2 1 3) simplify-associative-operation)
    #+(or development g2-lisp-unit)
    (proc-call-assignment-statement
      (local-name-list '= 'system 'call symbol procedure-arguments)
      (system-call-assignment-statement 1 5 6))
    #+(or development g2-lisp-unit)
    (proc-call-assignment-statement
      (local-name-list '= 'system 'action symbol procedure-arguments)
      (system-action-assignment-statement 1 5 6))
    ))

	
;;; The function `test-call-next-method-parse' is used to verify that the "call
;;; next method" statement should be a valid parse.  It is only available in
;;; method procedures and not in non-methods.

(defun test-call-next-method-parse (next-method-parse)
  (let ((frame? (frame-being-edited? current-edit-state)))
    (if (and frame? (of-class-p frame? 'method))
	next-method-parse
	(values
	  bad-phrase
	  "CALL NEXT METHOD is only available within a method"))))

(declare-grammar-transform-can-return-bad-phrase test-call-next-method-parse)




;;; `Inference Interface' or `INFER Statement'

;;; The INFER statement allows access to inferred variables from within
;;; procedures.  If a call to this statement contains multiple pairs of local
;;; variables and inferred expressions, then this statement will not complete
;;; until all variables have received values.  If a second variable name is
;;; included before the equal sign for an assignment, then this second variable
;;; will receive the expiration timestamp of the given inferred value, or one of
;;; the symbols UNKNOWN or NEVER.  If an expiration variable has been supplied,
;;; then an UNKNOWN OK option may be also specified.  An attempt to evaluate
;;; UNKNOWN OK expressions will be made, but if these expressions do not have
;;; values, then the symbol UNKNOWN will be placed in the expiration variable,
;;; the value variable value will not be changed, and the INFER statement will
;;; complete.  However, if any expressions within the INFER command without an
;;; UNKNOWN OK do not have values, then the INFER will be placed on wake-up, and
;;; will wait until all these expressions have values.  Note that an INFER
;;; command with all expressions declared UNKNOWN OK cannot cause a wait state.
;;; When the INFER statement can complete, the variable will be set to the value
;;; of the expression, and the expiration variable set to the expiration time of
;;; the value.  If the value is indefinite, the expiration variable will be set
;;; to the symbol NEVER.

;;; (Discussion:  The format of the INFER statement obviously needs improvement.
;;; One comment has been made that this statement is not explicitly calling for
;;; inferencing, but instead is requesting all forms of data service.  So, a
;;; name other than INFER which implies data seeking or data service would be
;;; appropriate.  Also, a better way is needed to specify the expiration
;;; variables and whether or not this statement may complete with UNKNOWN in one
;;; of the expiration variables.  I need more input on this issue.  -jra 4/7/89)

;;; (Update on the discussion!  The INFER statement has been replaced with the
;;; COLLECT DATA statement.  -jra 9/1/89

;;; INFER
;;;    variable-name [expiration-variable [UNKNOWN OK]] = expression
;;;    {, variable-name [expiration-variable [UNKNOWN OK]] = expression}

;(add-grammar-rules
;  '((proc-simple-statement proc-infer-statement)
;
;    (proc-infer-statement
;      ('infer infer-element) (infer-statement 2))
;
;    (proc-infer-statement 
;      ('infer infer-element-list) (infer-statement . 2))
;
;    (infer-element (local-name '= unique-expression) (1 nil 3))
;    (infer-element (local-name '\( 'unknown 'ok '\)
;			       '= unique-expression) (1 t 7))
;
;    (infer-element-list infer-element-list-1 1 cdr)
;
;    (infer-element-list-1
;      (infer-element '\, infer-element) (2 1 3))
;    (infer-element-list-1
;      (infer-element '\, infer-element-list-1)
;      (2 1 3) simplify-asociative-operation)))




;;; `Data Service Interface' or `COLLECT DATA statement'

;;; Within procedures there is a need to collect values of variables, where
;;; asynchronous data service may be required to get the data.  The COLLECT DATA
;;; statement is provided to supply an interface to variable values from data
;;; servers, and from the inference engine.  The statement includes facilities
;;; for scheduling timeouts on data requests, for making a set of data requests
;;; which should be sought in parallel and returned from a consistent data set
;;; environment, and for determining which individual variables did or did not
;;; receive data in a COLLECT DATA statement which failed.  Each execution of a
;;; COLLECT DATA statement will set flags on the local names being assigned
;;; reflecting whether or not the local names did or did not receive values.
;;; This flag is accessed through the expression "local-name FAILED TO RECEIVE A
;;; VALUE".  At procedure start this flag will always be false.

;;; COLLECT DATA [(TIMING OUT AFTER interval-expression)]
;;;   local-name = inferred-expression {; local-name = inferred-expression}
;;;   [; IF TIMEOUT THEN statement] [;]
;;; END

;;; On execution of this statement an attempt will be made to evaluate all
;;; inferred expressions.  If all return values, then these values will be
;;; assigned to their local names, the failed to receive a value flags will be
;;; set to false, and execution will continue to the following statement.  If
;;; any of the expressions do not return values, then if there no timeout, this
;;; procedure invocation will put itself on wake up for the values which did not
;;; return, and will wait.  On wake up it will attempt to evaluate all inferred
;;; expressions again, and proceed only if all evaluate.  Note that a COLLECT
;;; DATA statement without a timeout could wait indefinitely if one of its
;;; expressions did not return a value.

;;; If the COLLECT DATA statement has been given a timeout and the interval has
;;; not expired (i.e. there is a positive interval for the first attempt), then
;;; if any of the inferred expressions do not receive values the procedure
;;; invocation will put itself on wake up, schedule a task at the wake up
;;; interval, and enter a wait state.  The expressions will be attempted again
;;; on wake up, or when the timeout time arrives.  If all return values, then
;;; the values will be assigned to their local names, the failed to receive a
;;; value flags will be set to false, and execution will continue at the next
;;; statement.  If the timeout has arrived and some of the expressions did not
;;; receive values then values will be assigned to those local names whose
;;; expressions did receive values, their flags will be set to false, the local
;;; names whose expressions did not receive values will not have their values
;;; changed, but their failed to receive a value flags will be set to true.  If
;;; a timeout statement has been given, then this statement will be executed,
;;; and execution will be proceed at the following statement when the timeout is
;;; done.  If there is no timeout statement then execution proceeds directly to
;;; the statement following the COLLECT DATA.

;(add-grammar-rules
;  '((proc-simple-statement proc-collect-data-statement)
;
;    (proc-collect-data-statement
;      ('collect 'data collect-data-element 'end)
;      (infer-statement 3)
;      uffda-thing)
;
;    (proc-collect-data-statement 
;      ('collect 'data collect-data-element-list 'end)
;      (infer-statement . 3)
;      uffda-thing)
;
;    (collect-data-element (local-name '= unique-expression) (1 nil 3)
;			  uffda-thing)
;
;    (collect-data-element-list collect-data-element-list-1 1 cdr uffda-thing)
;
;    (collect-data-element-list-1
;      (collect-data--element '\; collect-data-element) (2 1 3) uffda-thing)
;    (collect-data-element-list-1
;      (collect-data-element '\; collect-data-element-list-1)
;      (2 1 3) simplify-asociative-operation uffda-thing)))

(add-grammar-rules
  '((proc-simple-statement proc-collect-data-statement)

    (end-with-optional-semicolon 'end)
    (end-with-optional-semicolon ('\; 'end) end)

    (proc-collect-data-statement
      ('collect 'data proc-data-element-list end-with-optional-semicolon)
      (collect-data-statement 3))

    (proc-collect-data-statement
      ('collect 'data '\( 'timing 'out 'after procedure-expression '\)
       proc-data-element-list end-with-optional-semicolon)
      (collect-data-statement 9 7))

    (proc-collect-data-statement
      ('collect 'data '\( 'timing 'out 'after procedure-expression '\)
       proc-data-element-list
       '\; 'if 'timeout 'then proc-statement
       end-with-optional-semicolon)
      (collect-data-statement 9 7 14))

    

    (proc-data-element-list proc-data-element (1))

    (proc-data-element-list (proc-data-element '\; proc-data-element-list)
			    (1 . 3))

    (proc-data-element (local-name '= procedure-untyped-expression) (1 3))))
    
;;;




;;; `Actions as Procedure Statements' or `Action Statements'

;;; All rule actions are available as statements in procedures.  The actions
;;; FOCUS, INVOKE, HALT, INFORM, SET, ACTIVATE, DEACTIVATE, MOVE, ROTATE, and
;;; CHANGE have the same format as statements that they have as actions.

(add-grammar-rules
  '((proc-simple-statement action)))


;; There is also some special action grammar that is currently only available
;; for procedures.  -dkuznick, 7/29/05

(add-grammar-rules
  '((proc-simple-statement proc-specific-action)))

;;; An extension to the usual CONCLUDE THAT action is available in procedures so
;;; that an explicit expiration or collection time may be given to a value being
;;; placed in an inferred variable.  Within procedures we do not want to carry
;;; along the extra processing of maintaining expirations on every local
;;; variable, but we have given users a facility for receiving expirations of
;;; inferred values.  We will also provide the capability to take the minimum of
;;; the expirations and send it out with a computed value.  If no explicit
;;; expiration is given, an expiration of NEVER is supplied.  Optionally, a
;;; collection time may be given for the value being concluded.  If the
;;; collection time is previous to the time of the most recent value concluded
;;; for that variable, then this value will be inserted into the variable's
;;; history.  If this is the most recent value for the variable, then it will be
;;; made the current value of the variable, with its expiration determined by
;;; the collection time and the validity interval of the variable.  The
;;; collection time must be equal to or less than THE CURRENT TIME.

;;; CONCLUDE THAT designation = expression
;;;   [WITH EXPIRATION expression] [WITH COLLECTION TIME expression]

;; The modification to the "conclude" grammar to support expiration and
;; collection times is in the grammar module.  Both procedure and rule actions
;; support this change.  7/14/89 cpm.

;(add-grammar-rules
;  '((proc-simple-statement proc-conclude-that-statement)

;    (proc-conclude-that-statement
;      ('conclude 'that unique-designation '= unique-expression)
;      (conclude-that-statement 3 5))
;    (proc-conclude-that-statement
;      ('conclude 'that unique-designation '= unique-expression
;       'with 'expiration unique-expression)
;      (conclude-that-statement 3 5 8))
;    (proc-conclude-that-statement
;      ('conclude 'that unique-designation '= unique-expression
;       'with 'collection 'time unique-expression)
;      (conclude-that-statement 3 5 nil 9))
;    (proc-conclude-that-statement
;      ('conclude 'that unique-designation '= unique-expression
;       'with 'expiration unique-expression
;       'with 'collection 'time unique-expression)
;      (conclude-that-statement 3 5 8 12))
;    (proc-conclude-that-statement
;      ('conclude 'that unique-designation '= unique-expression
;       'with 'collection 'time unique-expression
;       'with 'expiration unique-expression)
;      (conclude-that-statement 3 5 12 9))))



;;; `Calling or Starting Procedures', `Call Statement', or `Start Statement'

;;; START schedules execution of a procedure as a new concurrent process, then
;;; continues execution of this procedure.  The optional AFTER syntax allows the
;;; user to schedule this procedure to be run at some interval into the future,
;;; and the optional AT PRIORITY syntax allows the user to control the priority
;;; level at which this new process is executed.  The priority defaults to the
;;; the priority of the task executing the START.  Both AFTER and AT PRIORITY
;;; allow expressions in their argument positions.

;;; START procedure-name ([expression] {, expression} )
;;;   [ AFTER interval ] [ AT PRIORITY expression ]

;;; The CALL statement executes a procedure, waiting for completion of the
;;; called procedure before returning.

;;; CALL procedure-name ([expression] {, expression} )

;;; Note also that CALL and START may be passed a reference instead of a
;;; procedure name, and this reference will be evaluated to produce the
;;; procedure which will be invoked on the given arguments.  For example the
;;; statement

;;; CALL THE PROCEDURE NAMED BY THE SYMBOL OPEN (THE TANK)

;;; is equivalent to the statement the following statement.

;;; CALL OPEN (THE TANK)

;;; A more realistic example is where an attribute of an object contains the
;;; name of a procedure.

;;; CALL THE PROCEDURE NAMED BY THE OPENER-PROCEDURE OF TANK-42 (TANK-42)

;;; (Note:  We have received requests from customers that a form of
;;; "indirection" be made available for calling functions.  I see no reason we
;;; couldn't do this, besides the inconvenience of our figuring out how to
;;; supply the grammar.  Further, when defining the methods facility, we should
;;; make it possible to make functions into methods of procedures.  The syntax
;;; "EXECUTE function-designation ( expressions )" would work.)

;;; `Remote Procedure Calls', `START ACROSS', or `CALL ACROSS'

;;; The following documentation relates to the new START ACROSS and CALL ACROSS
;;; facilities for remote procedure calls.  -jra 3/4/90

;;; The remote procedure call facility is implemented to allow call-in and
;;; call-out between procedures in G2 and foreign processes in GSI.  The calls
;;; between two G2s and between a G2 and a GSI extension use the same ICP
;;; messages and formats.  This module is part of the procedures code, but uses
;;; lots of ICP facilities (in the INT module).

;;; The user accesses remote procedure calls within G2 using the following
;;; grammar.  This action is available within rules and procedures, and should
;;; appear to users as a simple extension to the START action.

;;;   START <remote procedure declaration designation>
;;;         ([<datum arg> {, <datum arg>}])
;;;     [AT PRIORITY <expression>]
;;;     [AFTER <expression>]
;;;     [ACROSS <g2-to-g2 or gsi interface designation>]

;;; The AFTER and AT PRIORITY clauses are still available.  The AFTER clause
;;; will locally delay the initiation of the remote call.  The given priority
;;; will only affect local processing (it takes some processing to initiate the
;;; call) and will not affect the processing which occurs on the remote system.
;;; Within remote G2s, the execution of a remote procedure call begins at
;;; the default priority of the remote procedure.

;;; There must be a declaration for any procedure which will be invoked
;;; remotely.  The remote declaration names the argument and return types of the
;;; remote procedure, as well as the name which will be used for the procedure
;;; in the remote system.  The remote name defaults to the same name as the
;;; local definition.

;;; The argument to the ACROSS grammar is a designation of an active and
;;; connected interface object.  This object can be connected with either
;;; another G2, or with a GSI extension process.  If the designated interface is
;;; not connected, then an error will occur which posts a message on the
;;; logbook.  The rule or procedure which executed the start will be allowed to
;;; continue.  If the procedure does not exist within the remote procedure, or
;;; some other error occurs in the process of starting the remote execution,
;;; then an error will be posted on the logbook of the G2 which started the
;;; remote procedure.  If an error occurs during the execution of the started
;;; remote procedure, then the source G2 will not be notified, and the remote
;;; system will handle the error in its own local style.

;;; The remote extensions to the CALL facility have the following grammar.

;;;   [<local name> {, <local name} = ]
;;;     CALL <remote procedure declaration designation>
;;;          ([<datum arg> {, <datum arg>}])
;;;       [ACROSS <g2-to-g2 or gsi interface designation>]

;;; Note that this grammar is the same as a local procedure call, but containing
;;; the additional ACROSS grammar.  The local processing to initiate the call
;;; occurs at the same priority as the priority of the procedure invocation
;;; making the call.  This priority does not affect the priority of the call on
;;; the remote system.  Within remote G2s, the execution of the remote procedure
;;; call begins at the default priority of the remote procedure.

;;; If the designated interface object is not connected, then an error is
;;; signalled within the procedure invocation which executed the CALL ACROSS.
;;; Also, if an error occurs within the called remote procedure, then an error
;;; will be signalled within the remote system, and and the error will also be
;;; propagated back to the local procedure which initiated the CALL ACROSS.
;;; This error will locally cause an error message to be posted on the logbook
;;; and will cause the procedure stack to be aborted.  Within future systems,
;;; these errors will be able to be handled with ON ERROR like any other error,
;;; even if they must be propagated across machine boundaries before they are
;;; handled (whoa Nelly, but that's wild).

;;; Note that the grammar for START is defined in GRAMMAR1.  -jra 3/4/90

;;; The system-call (originally lisp-call) statement is used to call out to Lisp
;;; from procedures.  It is only available in development G2 and should only be
;;; used in system-procedures.  The name of the lisp-function is not evaluated.
;;; The name of this statement has been changed to system-call since the
;;; statement should only be used in system procedures and the term "lisp"
;;; should not be used in G2 KB's.  We do not intend to make system procedures
;;; visible to the user, but the "lisp" term is being removed in case users have
;;; access to the system procedure in the future.

;;; SYSTEM CALL symbol ([expression] {, expression})


(add-grammar-rules
  '((proc-simple-statement proc-call-statement)
    (proc-simple-statement proc-call-next-method-statement)
    (proc-call-statement
      ('call procedure-designation procedure-arguments)
      (call-assignment-statement nil 2 3 nil))
    
    (proc-call-statement
      ('call procedure-designation procedure-arguments 'across
       unique-designation)
      (call-assignment-statement nil 2 3 5))
    ;; Call next method is only available in procedure methods.  Test this in
    ;; the transforming function.
    (proc-call-next-method-statement
      ('call 'next 'method )
      (call-next-method-statement)
      test-call-next-method-parse)
    #+(or development g2-lisp-unit)
    (proc-call-statement
      ('system 'call symbol procedure-arguments)
      (system-call-statement 3 4))
    ))

(defun-for-system-procedure extend-procedure-grammar ()
  (with-permanent-gensym-float-creation
    (add-grammar-rules
      '((proc-call-assignment-statement
	 (local-name-list '= 'system 'call symbol procedure-arguments)
	 (system-call-assignment-statement 1 5 6))
	(proc-call-statement
	 ('system 'call symbol procedure-arguments)
	 (system-call-statement 3 4))
	(proc-simple-statement proc-system-wait-statement)
	(proc-system-wait-statement
	 ('system 'wait)
	 (system-wait-statement)))))
  (copy-evaluation-truth-value evaluation-true-value))




;;; `Procedure Invocations' or `Referring to Procedure Invocations'



;;; Each CALL or START of a procedure creates a procedure invocation instance.
;;; These invocations instances are instances of the class PROCEDURE-INVOCATION.
;;; These invocations have some system supplied attributes and roles, and may be
;;; given further attributes by the user.

;;; The IDENTITY ARGUMENTS attribute of a procedure definition is used to
;;; restrict the set of concurrently existing procedure invocation instances.
;;; If a procedure has a declared set of procedure instance identity arguments,
;;; then only one invocation with a given set of identity arguments may exist at
;;; one time.

;;; If a procedure invocation with a particular set of identity arguments
;;; currently exists and a second call is made to that procedure with the same
;;; set of arguments, then the second call will wait until the first is
;;; completed before it is allowed to begin.  If several calls are waiting, they
;;; will execute in the order that the calls were queued.  This provides a
;;; simple interlocking facility for a particular operation on a given object or
;;; set of objects.

;;; For example, suppose there is a procedure named OPEN which has been given
;;; identity on its first argument.  It is CALLed by some procedure we'll name
;;; PROCEDURE-1 with a first argument of some valve named VALVE-1.  If a second
;;; procedure we'll name PROCEDURE-2 executes a CALL on OPEN with a first
;;; argument of VALVE-1, then this will start a new invocation of OPEN on
;;; VALVE-1 only after the existing call is completed.  When PROCEDURE-1's CALL
;;; to OPEN of VALVE-1 completes, then PROCEDURE-1 will continue its execution,
;;; and PROCEDURE-2's CALL to OPEN of VALVE-1 will begin.

;;; Similarly, if an invocation of OPEN on VALVE-1 had been launched with a
;;; START, the CALL in PROCEDURE-2 would wait until the existing OPEN of VALVE-1
;;; completes before begining a new invocation.




;;; `Attributes of Procedures' and `Roles of Procedures'

;;; From an invocation instance you can reference the CALLING-PROCEDURE, which
;;; returns the procedure instance which has called the given instance.  Note
;;; that the CALLING-PROCEDURE of a STARTed procedure invocation does not exist.
;;; An invocation instance also has a set of CALLED-PROCEDURES, which are the
;;; set of procedure instances which this instance is currently calling.  (There
;;; may be a set of procedure instances when using the IN-PARALLEL statement.)
;;; Procedure invocations have a system supplied attribute PROCEDURE-STATUS.  It
;;; has four possible values: NORMAL, SUSPENDED, RESUMING, and ABORTING.
;;; Procedure invocations also have a system supplied attribute
;;; PROCEDURE-RUN-STATUS which has the values WAITING and RUNNING.  A procedure
;;; invocation is RUNNING if it is either currently executing or if it is on the
;;; queue of tasks currently seeking processing time.  A procedure invocation is
;;; WAITING if it is currently executing a WAIT statement and the condition is
;;; not yet met, if it is executing an INFER statement for which not all
;;; expressions have values, or if it is executing a CALL statement and the
;;; called invocation has not yet completed.  Note that since an
;;; ALLOW-OTHER-PROCESSING statement just places the given procedure invocation
;;; back onto the queue of tasks seeking processing, it does not affect the
;;; PROCEDURE-RUN-STATUS attribute.




;;;; Procedure Suspending




;;; The SUSPEND and RESUME statements allow procedures or rules to temporarily
;;; halt and then restart currently executing procedures.  The ON SUSPEND and ON
;;; RESUME statements can be used to declare code for a procedure which will be
;;; executed when the procedure is suspended or resumed.  Note that a procedure
;;; can only be suspended or resumed at one of the statements which allows a
;;; wait state.

;;; When a procedure is suspended it takes the following actions:

;;; 1.  If the procedure has already been suspended, the procedure is handling
;;; an error, or if it is handling an abort, then this call to suspend has no
;;; action.

;;; 2.  If the procedure is currently executing any ON RESUME code, that is
;;; aborted via a CALL ABORT, and suspension continues.

;;; 3.  The current position within this procedure is noted and retained.

;;; 4.  Any procedures which are being called from this procedure will be
;;; suspended.  This step is complete as soon as the suspend code for each of
;;; the sub-procedures (and the sub-procedures of these procedures) has entered
;;; a wait state.

;;; 5.  Begin execution of the suspend code for this procedure, if any.  If a
;;; reason was given in the SUSPEND statement, the suspend-reason-var is bound
;;; to this value.  If no reason was given, this variable is bound to NULL.
;;; This code may enter wait states, call other procedures, and perform GOTO
;;; statements within its own body.  It may not perform a GOTO back to the main
;;; body of the procedure, nor may it execute RETURN statements.

;;; 6.  If there is no suspend code, or if execution of the suspend code
;;; completes by "falling off the end" of the suspend code body, then the
;;; procedure waits until it is resumed.

;;; If a WAIT statement which polls for a condition is being executed at the
;;; time that a procedure is suspended, then this polling will be stopped.  If a
;;; WAIT statement is waiting for a specified interval of time, or if a WAIT
;;; statement is waiting for an event, then these will remain in effect.  If the
;;; timer does time out or the event occurs during the suspension, then this
;;; will be noted, and on resumption, execution will immediately proceed past
;;; the wait statement.  On resumption of a WAIT statement which polls a
;;; condition, the polling will be restarted.

;;; When a procedure is RESUMED it takes the following actions:

;;; 1.  If the procedure is not currently suspended, or if it is handling an
;;; error or abort, it takes no action.

;;; 2.  Resume any called procedures which had been suspended.

;;; 3.  If this procedure is currently executing any ON SUSPEND code, abort it
;;; via a CALL ABORT (START ABORT?).

;;; 4.  Begin execution of ON RESUME code for this procedure, if any.  If a
;;; reason was given in the RESUME statement, the resume-reason-var is bound to
;;; this value.  If no reason was given, the variable is bound to NULL.  This
;;; code may enter wait states and call other procedures.  It may also execute
;;; GOTO statements within its own body or to tags within the main body of the
;;; procedure.  It may not execute any RETURN commands.  If a GOTO is executed
;;; back into the main body of the procedure, then the procedure has finished
;;; its resumption, and no further actions are taken.

;;; 5.  If there is no ON RESUME code, or if the ON RESUME code completes by
;;; "falling off the end" of the resume code body, then execution will resume in
;;; the main body at the statement which was being executed when this procedure
;;; was suspended.  If the suspended statement was a WAIT with a timed or
;;; event-based condition, and the timer completed, or the event occurred which
;;; suspended, then execution resumes at the statement immediately following the
;;; WAIT.  If the suspended statement was a WAIT which was checking a polled
;;; condition, then execution resumes at the WAIT, and polling continues.  The
;;; condition will be checked again immediately upon resumption.

;;; The formats of SUSPEND and RESUME statements are as follows.

;;; SUSPEND procedure-invocation-designation [WITH REASON expression]

;;; RESUME procedure-invocation-designation [WITH REASON expression]






;;;; Procedure Error Handling




;;; (G2 needs an error handling facility.  ON ERROR event handlers provide the
;;; means for users to declare their own handlers for errors on procedures.
;;; Handlers are declared for classes of errors and will be invoked if an error
;;; of the given class occurs within the scope of the procedure.  Since this
;;; facility is being newly defined here, there is no current hierarchy of error
;;; types, and little support will exist for the error facility within the first
;;; release.)

;;; The optional ON ERROR statement allows procedures to catch and handle errors
;;; which happen within them or within called procedures.  When an error occurs
;;; a search is begun to find a handler for the error.  The search begins with
;;; any ON ERROR handlers declared for the procedure body within which the error
;;; occurred.  If none is found, then the search continues back to the caller of
;;; this procedure.  If an error is not handled, then a default handler is
;;; invoked, which will issue an error message, afford developers a chance to
;;; view the state of the procedure stack ala the Lisp stack debugger, and then
;;; will abort the procedure invocation at the base of the stack.  An error
;;; handler is applicable if the error which occurred is a sub-class of the
;;; specified error for the handler.  Within an error handler the user may take
;;; one of several actions.

;;; If the error is continuable, then the user may call CONTINUE FROM ERROR.
;;; Execution will proceed at the statement following the statement which
;;; received the error.  Note that the handler which executes the continue
;;; statement need not be within the procedure which actually experienced the
;;; error, but that a call to continue will continue execution at the point
;;; where the error did actually occur.

;;; If a RETURN statement is executed within the error handler, then all CALLs
;;; from the procedure containing this error handler body will be aborted, and
;;; this procedure will be returned from, returning the given values.

;;; If a GOTO statement is executed which transfers control to a tag within the
;;; main body of the procedure, then all calls from the procedure will be
;;; aborted, and control will continue at the given tag.

;;; If all of an error handler is executed without executing either a CONTINUE
;;; FROM ERROR, RETURN, or GOTO statement, then this handler has declined to
;;; handle the error, and the search will continue further up the stack to the
;;; callers of this procedure invocation.

;;; The syntax of the ON ERROR statement is as follows.  The error-var should be
;;; a symbol which names a class of errors.  This symbol names a variable bound
;;; for the body of the error statement which contains an instance of the class
;;; ERROR.  The error instance has a ERROR-REASON attribute that will either
;;; have no value or will contain the datum given as the reason for the error in
;;; the ERROR statement.  The error instance also has an ERROR-DESCRIPTION
;;; attribute which contains a text describing the error, suitable for display
;;; to a knowledge-base developer.  (Note that ERROR-DESCRIPTIONS may be
;;; presented as extra information to end user's of knowledge bases, but that
;;; they may not be meaningful to this level of user.)

;;; ON ERROR error-var statement

;;; The statement for continuing from an error has the following format.

;;; CONTINUE FROM ERROR

;;; Errors are signalled with the ERROR statement.  It takes an optional procedure
;;; expression which specifies a reason for this error.

;;; ERROR

;;; ERROR expression






;;;; Procedure Aborting




;;; The optional ON ABORT statement will be executed if a procedure has been
;;; started (through CALL or START) and is then aborted by some other procedure
;;; or by a rule before it voluntarily completes by itself.  Note that there are
;;; two ways of aborting procedures, corresponding to whether the aborting
;;; procedure should wait for completion of the ON ABORT code before completing
;;; its call to abort, or whether it should cause the abort code to be started,
;;; and then continue itself immediately.  Note that the aborting of procedure
;;; execution can only take place at points in the procedure body where wait
;;; states could be encountered, that is at ALLOW OTHER PROCESSING, WAIT, CALL,
;;; CALL ABORT, and INFER statements.  Also note that the ON ABORT code will
;;; never be executed without the variable intializations having executed and
;;; the execution of statements in the procedure body begun.  If a procedure is
;;; scheduled for execution with the START statement, but is aborted before it
;;; has had a chance to begin execution, then the procedure invocation will be
;;; de-scheduled and discarded without running the ON ABORT statements.

;;; When a procedure invocation is aborted, all outstanding calls to other
;;; procedures are aborted by this procedure.  After all calls to other
;;; procedures have been successfully aborted (CALL ABORT style), then the ON
;;; ABORT code for this procedure (if any) is executed.  Within the ON ABORT
;;; code, the user may call RETURN, and this procedure will return values to its
;;; caller.  If the ON ABORT code does not call RETURN, then any callers of the
;;; aborted procedure will have the error CALL-ABORTED signalled within them.

;;; CALL ABORT will abort a given procedure, named through the identity feature.
;;; This procedure will continue executing after the named procedure has been
;;; successfully aborted, and any ON ABORT statements for it have been run.

;;; CALL ABORT procedure-invocation-designation [WITH REASON expression]

;;; START ABORT will abort a given procedure, named through the identity
;;; feature, continuing on immediately in this procedure regardless of whether
;;; any ON ABORT statements for the given procedure have been completed.

;;; START ABORT procedure-invocation-designation [WITH REASON expression]






;;;; Scoping of Event Handlers




;;; The ON SUSPEND, ON RESUME, ON ERROR, and ON ABORT facilities are all event
;;; handlers.  When a procedure is invoked, the body of that procedure is said
;;; to be "within the scope" of all event handlers for that procedure.  Being
;;; within the scope of an event handler means that if a handlable event occurs,
;;; then the handler will "see" the event and be given a chance to handle it.
;;; Some of the event handlers are scoped over the others.  The scoping of event
;;; handlers is as follows.

;;; ON ERROR handlers have scope only over the body of procedures.  There can be
;;; many ON ERROR handlers, but they do not have scope over each other.

;;; ON SUSPEND and ON RESUME handlers are scoped over the body of a procedure,
;;; over any executing error handlers, and over each other.  However, because
;;; suspending a procedure which has already been suspended has no effect and
;;; because resuming an already resumed procedure has no effect, neither of
;;; these event handlers have scope over their own bodies.

;;; (Discussion: What should happen if a procedure is suspended or resumed while
;;; it is handling an error?  It seems obvious that no action should occur in
;;; the case of an ABORT, in that we are already on the way out of the given
;;; procedure.  However, with an error handler, we may either continue at the
;;; point of the error (in the case of a continuable error), or a GOTO statement
;;; may be performed out of the error body back into the main procedure body.
;;; In these situations, we must handle the resume or suspend in some way, or
;;; else it is lost.  If suspend and resume do not have scope over errors, then
;;; the only way to proceed is to allow a suspend or resume to be postponed
;;; until the error is continued from in some way, and then let the suspension
;;; or resumption continue.  Because GOTO statements are not allowed to
;;; relinquish control of the processor, the suspend or resume would have to
;;; wait until the resumed processed entered a wait state.  On the other hand,
;;; if we allow suspend and resume statements to have scope over error handlers,
;;; there is a straightforward process through which suspensions and resumptions
;;; could be handled, and they would not be lost.  When a suspend occurs, the
;;; current position within the error body is saved, and processing continues at
;;; that point on resumption, much as would have happened if we were just
;;; executing the main body of the procedure.  With the main body and each event
;;; handler executed as its own code body, then there is no problem saving the
;;; program counter for each body separately.  However, this means that there
;;; will be no error handling around suspend and resume statements.  Can error,
;;; suspend, and resume handlers all have scope over each other?  For the moment
;;; I'll go with suspend and resume being around errors, but errors not being
;;; around suspend and resume.)

;;; ON ABORT handlers have scope over error, suspend, and resumption handlers.
;;; Therefore, if a procedure is aborted, no matter what the current state, you
;;; can be sure that the ON ABORT handler will be executed in the event of an
;;; abnormal exit.






;;;; Parallel Statement Execution




;;; The `DO IN PARALLEL statement' executes a set of statements in parallel and
;;; in synchrony.  It executes all of the statements in its body concurrently,
;;; with the DO IN PARALLEL statement completing after all statements in its
;;; body have successfully completed.  All local procedure variables are shared
;;; by statements.

;;; DO IN PARALLEL
;;;   statement {; statement} [;]
;;;   END

(add-grammar-rules
  '((proc-simple-statement proc-do-in-parallel-statement)
    (proc-do-in-parallel-statement
      ('do 'in 'parallel proc-compound-1)
      (do-in-parallel-statement . 4))))






;;; The `DO IN PARALLEL UNTIL ONE COMPLETES statement' executes a set of
;;; statements, continuing execution of this procedure after at least one of
;;; them completes, and CALL ABORTing those which lost the race and did not
;;; complete.  After one of the statements has completed and the rest have
;;; completed being aborted, then execution continues at the statment following
;;; the DO IN PARALLEL UNTIL ONE COMPLETES.

;;; DO IN PARALLEL UNTIL ONE COMPLETES
;;;   statement {; statement} [;]
;;;   END

;;; Note that the bodies of the parallel statements are allowed to perform GOTO
;;; statments to tags within their own scope, but they are not allowed to
;;; perform GOTO statements to tags within another of the parallel bodies.  If a
;;; GOTO statement is performed to a tag outside of the IN PARALLEL statement,
;;; then the other parallel statements will be aborted, and execution will
;;; continue at the specified GOTO tag.  Similarly, if an EXIT IF statement is
;;; executed which terminates an iteration that contains the entire IN PARALLEL
;;; form, then all other bodies in the IN PARALLEL are call aborted, and
;;; execution continues at the statement following the terminated iteration
;;; statement.  Finally, if a RETURN statement is executed from within one of
;;; the parallel statements, then the others will be call aborted, and the
;;; values given in the RETURN statement will be returned from the procedure.

(add-grammar-rules
  '((proc-simple-statement proc-do-in-parallel-until-one-completes-statement)
    (proc-do-in-parallel-until-one-completes-statement
      ('do 'in 'parallel 'until 'one 'completes proc-compound-1)
      (do-in-parallel-until-one-completes-statement . 7))))




;;; `Parallel Iteration'




;;; The parallel iteration statements provide execution of an iteration
;;; statement with all executions of the parallel bodies running in parallel
;;; with either other.  Both generic and numeric iteration are supported, in
;;; both the DO IN PARALLEL and DO IN PARALLEL UNTIL ONE COMPLETES styles of
;;; iteration.  Note that the body of the iteration constitutes a sequential set
;;; of statements.  During the execution of the body each parallel execution of
;;; the body will have its own private binding of the variable, and there will
;;; be as many parallel executions as the given iterator calls for.  This form
;;; will not affect the value of the binding for the named variable in the main
;;; body of the procedure.  All other local variables of the procedure are
;;; shared.

;;; FOR variable-name = EACH generic-designation
;;;   DO IN PARALLEL [UNTIL ONE COMPLETES]
;;;     statement {; statement} [;]
;;;   END

;;; FOR variable-name = expression
;;;     TO || DOWN TO expression
;;;    [BY expression]
;;;   DO IN PARALLEL [UNTIL ONE COMPLETES]
;;;     statement {; statement} [;]
;;;   END

;;; Note that G2 is a sequential program, and does not currently run on any
;;; parallel processing machines.  If an iteration being performed has no wait
;;; states in its body, then it should be executed with a sequential iteration
;;; statement.  This avoids the extra overhead of launching and resynchronizing
;;; the parallel code bodies.  The parallel forms in G2 are useful in cases
;;; where each code body experiences a latency external to processing within the
;;; computer running G2.

(add-grammar-rules
  '((proc-simple-statement proc-for-each-in-parallel-statement)
    (proc-for-each-in-parallel-statement
      ('for local-name '= 'each proc-in-parallel-iterator proc-compound-1)
      (for-each-in-parallel-statement (2  5) . 6))

    (proc-in-parallel-iterator
      (class 'do 'in 'parallel) (any 1))
    (proc-in-parallel-iterator
      (procedure-class-phrase-role unique-designation 'do 'in 'parallel) (any 1 2))
    (proc-in-parallel-iterator
      (element-type 'in unique-designation 'do 'in 'parallel)
      (any (element-iterator 1) 3))

    ))

(add-grammar-rules
  '((proc-simple-statement proc-for-each-in-parallel-race-statement)
    (proc-for-each-in-parallel-race-statement
      ('for local-name '= 'each proc-in-parallel-race-iterator
       proc-compound-1)
      (for-each-in-parallel-race-statement (2  5) . 6))

    (proc-in-parallel-race-iterator
      (class 'do 'in 'parallel 'until 'one 'completes) (any 1))
    (proc-in-parallel-race-iterator
      (procedure-class-phrase-role unique-designation
		  'do 'in 'parallel 'until 'one 'completes)
      (any 1 2))
    (proc-in-parallel-race-iterator
      (element-type 'in unique-designation 'do
			    'in 'parallel 'until 'one 'completes)
      (any (element-iterator 1) 3))))






;;;; Procedure Wait States




;;; The `ALLOW OTHER PROCESSING statement' gives users the ability to break up
;;; large computational procedures, allowing the scheduler to service networks,
;;; the user interface, the clock, and other processes currently executing at
;;; the same priority.  Note that G2 will not preempt execution of large
;;; procedures on its own, but will only do so at at the commands which can
;;; cause wait states.  This statement gives users to ability to explicitly tell
;;; G2 that this is an appropriate place at which a procedure may be
;;; interrupted.

;;; ALLOW OTHER PROCESSING

(add-grammar-rules
  '((proc-simple-statement proc-allow-other-processing-statement)
    (proc-allow-other-processing-statement ('allow 'other 'processing)
      (allow-other-processing-statement))))




;;; The `WAIT statement' allows users to temporarily halt the execution of a
;;; procedure to wait for some period of time or for some condition to become
;;; true.

;;; There are three different styles of WAIT supported for users, and an
;;; additional one for system procedures.  One is an event-based wait statement.
;;; It sets up monitors on variables and on the clock such that when a specified
;;; event occurs, this procedure will begin execution again.  The event-based
;;; style of execution does not "poll" on its conditions, and therefore uses no
;;; CPU time while waiting.  The event-based wait statement is of the same form
;;; as the antecedent of a WHENEVER rule, but does not allow an AND WHEN clause,
;;; and there is an additional "interval ELAPSES" event predicate clause
;;; available which is not available in WHENEVER rules.

;;; The second style of waiting allows any kind of logical, inferred expression
;;; as its condition, and it specifies an interval which should be used to
;;; schedule polling for this condition.  The condition will be checked
;;; immediately on execution of the WAIT statement, and then checked again at
;;; the specified interval.  When the condition becomes true, execution will
;;; continue in the procedure.

;;; The third style of wait allows the procedure to be paused for a specified
;;; amount of time, after which the execution will continue.

;;; The fourth style of wait is system wait, which enters a wait state but does
;;; not schedule any wake ups from that wait state.  It is intended to be used
;;; within system procedures where some other event within G2 will trigger the
;;; wait to be returned from.

;;; WAIT UNTIL event-logical-expression

;;; WAIT UNTIL inferred-logical-expression CHECKING EVERY interval

;;; WAIT FOR interval-expression

;;; SYSTEM WAIT

(add-grammar-rules
  '((proc-simple-statement proc-wait-for-statement)
    (proc-simple-statement proc-wait-until-statement)
;    (proc-simple-statement proc-wait-statement)
    (proc-simple-statement proc-wait-until-event-statement)

    #+development
    (proc-simple-statement proc-system-wait-statement)

    (proc-wait-for-statement
      ('wait 'for procedure-expression) (wait-for-statement 3))

    (proc-wait-until-statement
      ('wait 'until procedure-logical-expression
       'checking 'every procedure-expression) (wait-until-statement 3 6))

;    (proc-wait-statement ('wait) (wait-statement))

    (procedure-event-antecedent proc-event-logical-expression)
    (proc-event-logical-expression proc-event-disjunct)
    (proc-event-logical-expression
      (proc-event-disjunct 'or proc-event-logical-expression)
      (or 1 3) simplify-associative-operation)

    (proc-event-disjunct proc-event-literal)

    (proc-event-literal (procedure-designation 'receives 'a 'value)
			(receives-a-value 1))

    (proc-wait-until-event-statement
      ('wait 'until procedure-event-antecedent)
      (wait-until-event-statement 3))

    #+(or development g2-lisp-unit)
    (proc-system-wait-statement ('system 'wait) (system-wait-statement))
    ))






;;;; Procedures as Class Methods




;;; Procedures can be written as methods of classes.  This is done by setting
;;; the METHOD attribute of a procedure definition to the type of method this
;;; should be, and the name of the class with which the method should be
;;; associated.  Note that it is an error to have method definitions and a
;;; non-method procedure definition for the same name co-existing in a knowledge
;;; base.  When a CALL or START is executed on a name, if that names a set of
;;; methods, then the method which is bound to the class most specific to the
;;; first argument will be executed.  Within a method the statement CALL MORE
;;; GENERAL METHOD may be executed to further invoke the next most specific
;;; method.  This will cause the next most specific method to be CALLed on the
;;; same arguments that were passed to this method.

;;; CALL MORE GENERAL METHOD

;;; The logical expression MORE GENERAL METHOD EXISTS can be used within a
;;; method to determine if there is a more specific method for this name.

;;; (This section needs to be merged with the other fragmentary sections dealing
;;; with procedures as methods.  It needs to address BEFORE, AFTER, AROUND,
;;; PRIMARY, and EFFECTIVE methods.  This discussion needs to stress that
;;; methods are merely a way of performing run-time determination of code to
;;; perform specific operations, and that all other rules of procedure
;;; invocation execution still apply.)






;;;; Procedure Expressions




;;; The expressions allowed in procedures are those allowed in inference engine
;;; expressions, with the following exceptions and restrictions. 

;;; If expressions are required to include an else clause.

;;; The "has a value" and "has no value" logical expressions are not allowed.

;;; The "has a current value" and "has no current value" logical expressions are
;;; allowed, however their argument must be a designation which references a
;;; variable.  The syntax which allows a parenthesized expression instead of a
;;; designation in inference engine expressions is not allowed.

;;; The expression "the current value of" is not allowed.

;;; The expression "the value of" is allowed, but it may only be applied to
;;; parameters.  Note that this expression is unneccessary in procedures, except
;;; to emphasize that the value of a parameter is being referenced, instead of
;;; the parameter frame itself.

;;; The expressions "the first of the following expressions that has a value"
;;; and "the first of the following expressions that has a current value" are
;;; not allowed.

;;; The use of "every" in action designations is not allowed in procedures.  Use
;;; the "FOR local-name = EACH..." iteration instead.

;;; The expression "<local-name> failed to receive a value" is allowed only to
;;; accept local names as its argument, and is available only in procedures.

;;; The special variable `procedure-function-template-alist' is used to hold a
;;; list of procedure function templates.

(defvar procedure-function-template-alist nil)




;;; The macro `procedure-function-template' implements a facility used to
;;; provide overriding function templates for use by the procedure compiler.  By
;;; default the normal function templates are used in the procedure compiler,
;;; however an overriding template may be defined here.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun def-procedure-function-template (template)
    (def-template template procedure-function-template-alist)))

#+unused
(defun lookup-procedure-function-template (function-name)
  (assq function-name procedure-function-template-alist))




;;; The functions `has-a-current-value for procedures' and `has-no-current-value
;;; for procedures' are restricted to take only designations as arguments.

(def-procedure-function-template '(has-a-current-value designation))
(def-procedure-function-template '(has-no-current-value designation))




;;; The procedure evaluator expression `failed-to-receive-a-value'
;;; receives a local name as its argument.  This local name must be compiled
;;; into a var spot.  It returns a logical value.

(def-procedure-function-template '(failed-to-receive-a-value local-name-var-spot))




;;; The function `there-exists-literal' needs a special compilation for its
;;; scope, since the local name referenced here should be able to use normally
;;; declared procedure local variables.

(def-procedure-function-template
  '(there-exists-literal there-exists-scope expression))




;;; The generated operator `var-spot' should be passed on with no compilation.

(def-procedure-function-template
  '(var-spot other))






;;;; Function Definitions




;;; The following two formats are available for function definitions.  A
;;; function definition can be either an expression or a set of declarations and
;;; a compound function statement.

;;; function-name ( argument-list ) = expression

;;; function-name ( argument-list ) [= (return-type)]
;;;   {local-variable-declaration ;}
;;;   function-compound-statement

;;; The format of an argument list for functions is the same as an argument list
;;; for procedures.  It is a list of variable names seperated by commas, with
;;; possible variable types seperated from their variable names by a colon.  A
;;; function compound statement is a compound statement (i.e.  delimited by
;;; BEGIN and END which contains function statements.  The return type may be
;;; specified in the same as for procedures, as a type within parentheses
;;; following an equal sign after the argument list.  Local variables are also
;;; declared for functions the same way as they are for procedures.






;;;; Function Statements

;;; A function compund statement is a compound statement, delimited by BEGIN and
;;; END, which contains common statements and function statements.  Presently
;;; there is only one explicit function statement.






;;; `Function Value Return'

;;; RETURN statements cause a function to return the value of the given
;;; expression.  As opposed to RETURN statments in procedures, only one value
;;; may be returned from a function.

;;; RETURN expression







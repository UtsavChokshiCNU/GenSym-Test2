;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module STACK-EVAL1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Chris Morel






;; In GRAMMAR4
(declare-forward-reference decode-format function)

;; In STACK-EVAL2
(declare-forward-reference eval-bitwise-test-funcalled function)

;;;; New Evaluator Definitions 




;;; The STACK-EVAL module contains a reimplementation of all the G2 expression
;;; evaluators.  There is one evaluator definition for all applicable
;;; environments: inference, simulator, or procedure.

;;; The evaluators specify the expected argument types, return values, and valid
;;; environments.  The arguments are evaluated before the evalutor is called.
;;; If an argument is not of the correct type, an error is signalled without
;;; calling the evaluator.  There are two types of evaluators: in-line and
;;; funcalled.  The in-line evaluators access there arguments from the stack
;;; with a call to (stack-arg <n>).  The funcalled evaluators are passed there
;;; evaluated arguments.

;;; IMPORTANT NOTE: The types of the arguments and return values of in-line and
;;; funcalled evaluators differ.  In-line evaluators access arguments and leave
;;; a return value on the stack.  These are evaluation values.  Funcalled
;;; evaluators are passed and return evaluation-value values.

;;; Some operations or functions have several evaluators which correspond to the
;;; different numbers and types of arguments required.  Some arithmetic
;;; evaluators have different names depending on the type of quantity arguments
;;; accepted.  For example, = has =-float and =-integer version for integer and
;;; float arguments respectively.  Other evaluators, such as arctan, and
;;; integral, have versions which accept different numbers of arguments.

;;; Some evaluators are implemented as special forms and implemented as separate
;;; instructions.  See the section on special forms.

;;; Some expressions receive there values from role-servers which are not in
;;; this module.

;;; Each evaluator must return the value that it specifies in its definition or
;;; it should signal an error.  An evaluator that is in the current-environment
;;; of INFERENCE, can return an "unknown" value by setting stack-expiration to
;;; nil and leaving a value on the stack.

;;; Normally, evaluators will not modify the expression expiration,
;;; stack-expiration.  The expression expiration is usually based on the minimum
;;; expiration value of the "leaves", i.e., constant values, of the expression.
;;; The cases where the expiration would be modified is when "unknown" is
;;; returned or when the evaluator is a special form, such as "or".

;;; Evaluators can behave differently depending on the current-environment.  For
;;; example, history evaluators test if current-environment is SIMULATOR.  Also,
;;; if "unknown" is returned by an evaluator in the INFERENCE environment, an
;;; error is signalled in the PROCEDURE environment.  In the simulator
;;; environment, non-current real-time expressions use
;;; (get-current-time-in-simulation-environment).

;;; The documentation for each stack-evaluator describes the behavior for each
;;; evaluator, the difference, if any, in each environment, and the difference,
;;; if any, from the old evaluators.  The order of the evaluators is based on
;;; the G2 2.0 User Manual, except for those evaluators not in the
;;; documentation.






;;; Compiler Notes

;;; Some n-ary evaluators are compiled into other evaluators.  For example,
;;; average can be compiled into calls to + and /.

;;; Other n-ary evaluators, such as +, *, min, and max, compile multiple calls
;;; to the binary evaluators.




;;; To Do

;; STACK-EVAL:

;; History and some Time Evaluators - rewrite suppport functions to not write
;; error messages.

;; Lisp Arithmetic Functions - Review evaluators that call lisp arithmetic
;; functions for error cases!  For example, arctan (0,0), which calls (atan 0
;; 0), is an error.

;; Existence Expression - review expiration time computation.

;; Expt and ^ evaluators - can we have one evaluator?  Have the grammar parse to
;; one evaluator?

;; Error messages:
;; 1. Don't use print-designation or "~ND" format string on
;; get-or-make-up-designation-for-block.  Use either "~NF" on the frame or "~A" on
;; the possibly generated designation, which could be a designation or string.
;; 2. Use STACK-ERROR instead of WRITE-STACK-ERROR since it is smaller and does
;; not bind special variables.

;; ENVIRONMENTS:

;; Review which evaluators should be in inference, simulator, and procedure. 

;; Simulation error messages - Check simulation code to see if there are changes
;; in when error messages are produced!  See the following comment in simulate3.
;; "The operators defined below do some type checking.  For instance, if numeric
;; operators get nil as an argument, the evaluation will not be successful.
;; Consider also posting a simulation error message in this case.  This would be
;; similar to the other simulation error messages; it only goes up when the
;; simulator is initialized."

;; Simulation - History evaluators need to be written to access simulation
;; histories.




;; QUESTIONS

;; Should index arguments be restricted to integer instead of quantity, which
;; could be of the form n.0?

;; Some evaluators, such as fails-to-receive-a-value, expect an arg that is an
;; item OR temporary constant.  Should we still handle these cases?

;; Change calls of round to g2-round.

;; The user may be relying on some evaluators returning unknown when giving an
;; invalid value.  An example is passing a negative value to log.  In the stack
;; evaluator version of log, an error is signaled.  It is difficult for the user
;; to test for values such as this in rules or formulas.  Should evaluators like
;; this return unknown when not in procedures? No.  We should note a
;; functionality change when we now signal an error.






;;;; Special Forms




;; Quote, Format-Form, Is, Is-Not, And, Or, If-Expression, Has-A-Current-Value,
;; Has-No-Current-Value, Has-A-Value, Has-No-Value, Current-Value-Of, Value-Of,
;; First-That-Has-A-Current-Value, First-That-Has-A-Value, SImulated-Value-Of,
;; There-Exists-Literal, For-Every-Literal, Exists, Containing, Containing-Word,
;; etc.

;; Aggregators: Sum, Product, Aggregated-Average, Maximum, Minimum, Count.











;;;; Evaluator Pretty Printers




;;; This section should contain all the pretty printers for evaluators.  A
;;; pretty printer for an evaluator the thing that prints an evaluator
;;; instruction and its arguments.  It takes as arguments the evaluator
;;; description, the program counter, the current byte-code-body, the current
;;; stack, and the given top of stack.

;;; The function `pprint-infix-evaluator' is used to print two argument
;;; evaluators.  This is the default printer for all two argument evaluators.

(defun pprint-infix-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (pprint-infix-evaluator-using-name
    (evaluator-name description) pc byte-code-body constant-vector stack
    top-of-stack))


;;; The function `pprint-infix-evaluator-using-name' is used to print infix
;;; evaluators when the name is different from the internal name.

(defun pprint-infix-evaluator-using-name
       (name pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-character #.%space)
  (twrite-symbol name)
  (twrite-character #.%space)
  (write-stack-argument 2 2 stack top-of-stack))



;;; The function `pprint-functional-evaluator' is used to print arbitrary
;;; argument count evaluators in a functional style, e.g. max(22, 34).  This is
;;; the default printer for evaluators with argument counts other than two.

(defun pprint-functional-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore pc byte-code-body constant-vector))
  (let ((argument-count (length (evaluator-arguments description))))
    (twrite-symbol (evaluator-name description))
    (twrite-character #.%\()
    (loop for index from 1 to argument-count do
      (when (/=f index 1) (twrite-string ", "))
      (write-stack-argument index argument-count stack top-of-stack))
    (twrite-character #.%\))))



;;; The function `pprint-prefix-evaluator' is used to print evaluators that take
;;; one argument and pprint as "some string" <argument>".  This function is
;;; needed if the evaluator name is not printed as its internal name.

;;; "operator-string <argument>"

(defun pprint-prefix-evaluator (operator-string stack top-of-stack)
  (twrite-string operator-string)
  (twrite-character #.%space)
  (write-stack-argument 1 1 stack top-of-stack))



;;; The function `pprint-negation-evaluator' is used to print the negate
;;; evaluator.

(defun pprint-negate-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-prefix-evaluator "negate" stack top-of-stack))



;;; The function `pprint-format-form-instruction' is used to print the form-form
;;; funcalled instruction.  This instruction takes a variable number of
;;; arguments.  Therefore, the argument count in the instruction description,
;;; which is not correct, is not referenced.

(defun pprint-format-form-instruction
    (description pc byte-code-body constant-vector stack top-of-stack arg-count result-count)
  (declare (ignore description pc byte-code-body constant-vector result-count))
  (twrite-character #.%\")
  (loop for index from 1 to arg-count
	do
    (twrite-character #.%\[)
    (write-stack-argument index arg-count stack top-of-stack)
    (twrite-character #.%\]))
  (twrite-character #.%\"))



;;; The function `pprint-format-evaluator' is used to print the format funcalled
;;; evaluator.

(defun pprint-format-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (cond ((=f top-of-stack cached-top-of-stack)
	 (let* ((value-arg (svref stack (-f top-of-stack 1)))
		(format-arg (svref stack top-of-stack))
		(format (evaluation-symbol-symbol format-arg)))
	   (write-stored-value value-arg)
	   (cond ((eq format 'seconds)
		  (twrite-string " as an interval"))
		 ((eq format 'time-stamp)
		  (twrite-string " as a time stamp"))
		 (t
		  (twrite-string " as a <unknown format>")))))
	(t
	 ;; write "format as an interval or time stamp <argument unavailable>".
	 (twrite-string "format as an interval or time stamp ")
	 (write-stack-argument 1 1 stack top-of-stack))))



;;; The function `pprint-fixed-format-evaluator' is used to print the fixed-
;;; format funcalled evaluator.  This evaluator prints a number in a format such
;;; as dd.ddd.

(defun pprint-fixed-format-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (cond ((=f top-of-stack cached-top-of-stack)
	 (let* ((value-arg (svref stack (-f top-of-stack 2)))
		(integral-size-arg (svref stack (-f top-of-stack 1))) 
		(integral-size (evaluation-integer-value integral-size-arg))
		(fraction-size-arg (svref stack top-of-stack))
		(fraction-size (evaluation-integer-value fraction-size-arg)))
	   (write-stored-value value-arg)
	   (twrite-string " as ")
	   (loop for x from 1 to integral-size do
		 (twrite-character #.%\d))
	   (twrite-character #.%\.)
	   (loop for x from 1 to fraction-size do
		     (twrite-character #.%\d))))
	(t
	 ;; write "format as an interval or time stamp <argument unavailable>".
	 (twrite-string "format as some dd.ddd ")
	 (write-stack-argument 1 1 stack top-of-stack))))



;;; The function `pprint-is-and-possibly-unknown-instruction' is used to print
;;; the is-and-possibly-unknown funcalled-instruction.  This instruction needs a
;;; printer to translate the name to IS.

(defun pprint-is-and-possibly-unknown-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (pprint-is-instruction
    description pc byte-code-body constant-vector stack top-of-stack))

(defun pprint-is-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description))
  (pprint-infix-evaluator-using-name
    'is pc byte-code-body constant-vector stack top-of-stack))



;;; The function `pprint-fuzzy-evaluator' is used to write all of the fuzzy
;;; comparison evaluators, except those that compare two fuzzy value
;;; expressions.  The expression is written as "X OP Y (+- .N)".

(defun pprint-fuzzy-evaluator (operator stack top-of-stack)
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-character #.%space)
  (twrite-symbol operator)
  (twrite-character #.%space)
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-string " (+- ")
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-character #.%\)))



;;; The following functions print the fuzzy operator evaluators.  These are
;;; `pprint-fuzzy-<', `pprint-fuzzy->', `pprint-fuzzy-=', and
;;; `pprint-fuzzy-not-='.

(defun pprint-fuzzy-<-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-fuzzy-evaluator '< stack top-of-stack))

(defun pprint-fuzzy->-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-fuzzy-evaluator '> stack top-of-stack))

(defun pprint-fuzzy-=-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-fuzzy-evaluator '= stack top-of-stack))

(defun pprint-fuzzy-not-=-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-fuzzy-evaluator '/= stack top-of-stack))




;;; The function `pprint-history-evaluator-during-time-interval' is used to
;;; write the history evaluators that compute a value "during the last
;;; <interval>".

(defun pprint-history-evaluator-during-time-interval
       (description-string stack top-of-stack argument-count)
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (interval
	   (and stack-args-ok?
		(svref stack (-f top-of-stack (-f argument-count 2))))))
    (twrite-string description-string)
    (twrite-character #.%space)
    (write-stack-argument 1 argument-count stack top-of-stack)
    (twrite-string " during the last ")
    (if stack-args-ok?
	(print-constant interval 'seconds)
	(write-stack-argument 2 argument-count stack top-of-stack))))

(defun pprint-average-value-1-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-during-time-interval
    "the average value of" stack top-of-stack 4))

(defun pprint-sum-of-values-1-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-during-time-interval
    "the sum of the values of" stack top-of-stack 4))

(defun pprint-minimum-value-1-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-during-time-interval
    "the minimum value of" stack top-of-stack 4))

(defun pprint-maximum-value-1-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-during-time-interval
    "the maximum value of" stack top-of-stack 4))

(defun pprint-standard-deviation-1-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-during-time-interval
    "the standard deviation of" stack top-of-stack 4))

(defun pprint-number-of-datapoints-1-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-during-time-interval
    "the number of history datapoints in" stack top-of-stack 4))



;;; The function `pprint-history-evaluator-between-time-interval' is used to
;;; write the history evaluators that compute a value "between <time interval>
;;; and <time interval> ago" and "during the <interval> ending with the
;;; collection time".

(defun pprint-history-evaluator-between-time-intervals
       (description-string stack top-of-stack argument-count)
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (interval-1
	   (and stack-args-ok?
		(svref stack (-f top-of-stack (-f argument-count 2)))))
	 (interval-2
	   (and stack-args-ok?
		(svref stack (-f top-of-stack (-f argument-count 3))))))
    (twrite-string description-string)
    (twrite-character #.%space)
    (write-stack-argument 1 argument-count stack top-of-stack)

    (cond ((evaluation-truth-value-p interval-2)
	   (twrite-string " during the ")
	   (if stack-args-ok?
	       (print-constant interval-1 'seconds)
	       (write-stack-argument 2 argument-count stack top-of-stack))
	   (twrite-string " ending with the collection time"))
	  (t (twrite-string " between ")
	     (if stack-args-ok?
		 (print-constant interval-1 'seconds)
		 (write-stack-argument 2 argument-count stack top-of-stack))
	     (twrite-string " ago")
	     (twrite-string " and ")
	     (if stack-args-ok?
		 (print-constant interval-2 'seconds)
		 (write-stack-argument 3 argument-count stack top-of-stack))
	     (twrite-string " ago")))))

(defun pprint-average-value-2-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-between-time-intervals
    "the average value of" stack top-of-stack 5))

(defun pprint-sum-of-values-2-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-between-time-intervals
    "the sum of the values of" stack top-of-stack 5))

(defun pprint-minimum-value-2-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-between-time-intervals
    "the minimum value of" stack top-of-stack 5))

(defun pprint-maximum-value-2-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-between-time-intervals
    "the maximum value of" stack top-of-stack 5))

(defun pprint-standard-deviation-2-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-between-time-intervals
    "the standard deviation of" stack top-of-stack 5))

(defun pprint-number-of-datapoints-2-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-between-time-intervals
    "the number of history datapoints in" stack top-of-stack 5))



;;; The function `pprint-history-evaluator-with-time-units-during-time-interval'
;;; is used to write the history evaluators that compute a value "in <time
;;; units> of <item> during the last <interval>".

(defun pprint-history-evaluator-with-time-units-during-time-interval
       (description-string stack top-of-stack argument-count)
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (interval?
	   (and stack-args-ok?
		(svref stack (-f top-of-stack (-f argument-count 3))))))
    (twrite-string description-string)
    (twrite-character #.%space)
    (write-stack-argument 2 argument-count stack top-of-stack)
    (twrite-string " of ")
    (write-stack-argument 1 argument-count stack top-of-stack)
    (twrite-string " during the last ")
    (if interval?
	(print-constant interval? 'seconds)
	(write-stack-argument 3 argument-count stack top-of-stack))))


(defun pprint-rate-of-change-1-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-with-time-units-during-time-interval
    "the rate of change per" stack top-of-stack 5))

(defun pprint-integral-1-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-with-time-units-during-time-interval
    "the integral in" stack top-of-stack 5))



;;; The `pprint-history-evaluator-with-time-units-between-time-interval'
;;; function is used to write the history evaluators that compute a value "in
;;; <time units> of <item> between <time interval> and <time interval> ago" 
;;; and "during the <interval> ending with the collection time".

(defun pprint-history-evaluator-with-time-units-between-time-intervals
       (description-string stack top-of-stack argument-count)
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (interval-1?
	   (and stack-args-ok?
		(svref stack (-f top-of-stack (-f argument-count 3)))))
	 (interval-2?
	   (and stack-args-ok?
		(svref stack (-f top-of-stack (-f argument-count 4))))))
    
    (twrite-string description-string)
    (twrite-character #.%space)
    (write-stack-argument 2 argument-count stack top-of-stack)
    (twrite-string " of ")
    (write-stack-argument 1 argument-count stack top-of-stack)

    (cond ((evaluation-truth-value-p interval-2?)
	   (twrite-string " during the ")
	   (if stack-args-ok?
	       (print-constant interval-1? 'seconds)
	       (write-stack-argument 3 argument-count stack top-of-stack))
	   (twrite-string " ending with the collection time"))
	  (t (twrite-string " between ")
	     (if stack-args-ok?
		 (print-constant interval-1? 'seconds)
		 (write-stack-argument 3 argument-count stack top-of-stack))
	     (twrite-string " ago")
	     (twrite-string " and ")
	     (if stack-args-ok?
		 (print-constant interval-2? 'seconds)
		 (write-stack-argument 4 argument-count stack top-of-stack))
	     (twrite-string " ago")))))


(defun pprint-rate-of-change-2-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-with-time-units-between-time-intervals
    "the rate of change per" stack top-of-stack 6))

(defun pprint-integral-2-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-history-evaluator-with-time-units-between-time-intervals
    "the integral in" stack top-of-stack 6))



;; "the number of history datapoints in <v-or-p>"

(defun pprint-number-of-datapoints-0-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (pprint-prefix-evaluator
    "the number of history datapoints in" stack top-of-stack))


;; "the value of <v-or-p> as of <interval> ago".

;(defun pprint-historic-value-instruction-instruction
;; Fix by ML, 6/4/92

(defun pprint-historic-value-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (interval?
	   (and stack-args-ok?
		(svref stack (-f top-of-stack 2)))))
    (twrite-string "the value of ")
    (write-stack-argument 1 4 stack top-of-stack)
    (twrite-string " as of ")
    (if interval?
	(print-constant interval? 'seconds)
	(write-stack-argument 2 4 stack top-of-stack))
    (twrite-string " ago")))


;;; "the value of <v-or-p> as of <integer> datapoints ago".

(defun pprint-value-of-previous-datapoint-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "the value of ")
  (write-stack-argument 1 4 stack top-of-stack)
  (twrite-string " as of ")
  (write-stack-argument 2 4 stack top-of-stack)
  (twrite-string " datapoints ago"))


;; "the interpolated value of <v-or-p> as of <interval> ago".

(defun pprint-interpolated-value-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (interval?
	   (and stack-args-ok?
		(svref stack (-f top-of-stack 2)))))
  (twrite-string "the interpolated value of ")
  (write-stack-argument 1 4 stack top-of-stack)
  (twrite-string " as of ")
  (if interval?
      (print-constant interval? 'seconds)
      (write-stack-argument 2 4 stack top-of-stack))
  (twrite-string " ago")))


;; "the distance between <item> and <item>"

(defun pprint-distance-between-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "the distance between ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " and ")
  (write-stack-argument 2 2 stack top-of-stack))


;; "the distance between <item> and the nearest <class>"

(defun pprint-distance-between-and-the-nearest-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "the distance between ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " and the nearest ")
  (write-stack-argument 2 2 stack top-of-stack))


;; "<item> has a value"

(defun pprint-has-a-value-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (write-stack-argument 2 2 stack top-of-stack)
  (twrite-string " has a value"))


;;; The function `pprint-first-that-has-a-value-instruction' prints the
;;; first-that-has-a-value special-form evaluator.  Note that it can only print
;;; one of the expressions that is being evaluated.  This is because the
;;; evaluator is implemented as a special form that passes one value a time to
;;; this instruction.

;; "first that has a value <value>"

;; REVIEW THIS!!

(defun pprint-first-that-has-a-value-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "first that has a value ")
  (write-stack-argument 3 3 stack top-of-stack))


;; "<item> exists"

(defun pprint-exists-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string " exists"))


;; "the current time"

(defun pprint-current-time-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body stack top-of-stack
		   constant-vector))
  (twrite-string "the current time"))


;; "the current real time"

(defun pprint-current-real-time-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body stack top-of-stack
		   constant-vector))
  (twrite-string "the current real time"))


;; "the collection time of <v-or-p>"

(defun pprint-collection-time-of-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "the collection time of ")
  (write-stack-argument 1 2 stack top-of-stack))


;; "the collection time of <v-or-p> as of <integer> datapoints ago"

(defun pprint-collection-time-of-previous-datapoint-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "the collection time of ")
  (write-stack-argument 1 4 stack top-of-stack)
  (twrite-string " as of ")
  (write-stack-argument 2 4 stack top-of-stack)
  (twrite-string " datapoints ago"))


;; "the expiration time of <v-or-p>"

(defun pprint-expiration-time-of-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "the expiration time of ")
  (write-stack-argument 1 2 stack top-of-stack))




;; "<item-or-value> is a member of <list>"

(defun pprint-g2-list-or-sequence-member-p-instruction
    (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (write-stack-argument 2 2 stack top-of-stack)
  (twrite-string " is a member of ")
  (write-stack-argument 1 2 stack top-of-stack))


;; "the number of elements in <list>"

(defun pprint-g2-list-or-sequence-length-evaluator
    (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "the number of elements in ")
  (write-stack-argument 1 1 stack top-of-stack))


;; "the attribute name of <item>"

(defun pprint-attribute-name-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "the attribute name of ")
  (write-stack-argument 1 1 stack top-of-stack))


;; "<item> is <relation> <item>"

(defun pprint-is-related-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-string " is ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-character #.%space)
  (write-stack-argument 2 3 stack top-of-stack))


;; "<item> is not <relation> <item>"

(defun pprint-is-not-related-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-string " is not ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-character #.%space)
  (write-stack-argument 2 3 stack top-of-stack))


;; The false stack-evaluator is identical to "not" operationally, but may be
;; passed through a quantifier by the compiler.

;; Print the false evaluator as not??

;; "not <expression"

(defun pprint-false-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "not ")
  (write-stack-argument 1 1 stack top-of-stack))


;; "<item-or-value> is a(n) <class-or-type>"

(defun pprint-is-of-class-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " is a(n) ")
  (write-stack-argument 2 2 stack top-of-stack))


;; "<workspace> has been activated"

(defun pprint-is-active-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string " has been activated"))


;; "<item> has a name"

(defun pprint-has-a-name-evaluator
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string " has a name"))


;;;






;;;; Arithmetic Expression Evaluators




;;; The `+ stack evaluator' accepts two quantity arguments and returns the
;;; result of adding the two values.  This stack-evaluator differs from the old
;;; one by not not accepting any number of arguments.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;;; EVAL: accepted any number of arguments.
;;; STACK-EVAL: accepts only two arguments.

;;; + (number, number)

(def-float-contagion-stack-operator +)

(def-in-line-evaluator (+ +-quantity 4) (0 all (number number) number t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1
	(add-evaluation-quantities (stack-arg 0) (stack-arg 1))))

(defun-simple add-evaluation-quantities (x y)
  (cond 
    ((fixnump x)
     (cond
       ((fixnump y) (+f x y))
       ((evaluation-long-p y)
	(mutate-evaluation-long-value y
	  (+l x (evaluation-long-value y)))
	y)
       (t
	(mutate-evaluation-float-value y
	  (+e (coerce-fixnum-to-gensym-float x)
	      (evaluation-float-value y)))
	y)))
    ((evaluation-long-p x)
     (cond  
       ((fixnump y)
	(mutate-evaluation-long-value x
	  (+l (evaluation-long-value x) y))
	x)
       ((evaluation-long-p y)
	(mutate-evaluation-long-value y
	  (+l (evaluation-long-value x) (evaluation-long-value y)))
	(reclaim-evaluation-long x)
	y)
       (t
	(mutate-evaluation-float-value y
	  (+e (normalize-to-gensym-float x)
	      (evaluation-float-value y)))
	(reclaim-evaluation-long x)
	y)))
    ((fixnump y) ; x = float
     (mutate-evaluation-float-value x
       (+e (evaluation-float-value x)
	   (coerce-fixnum-to-gensym-float y)))
     x)
    ((evaluation-long-p y) ; x = float
     (mutate-evaluation-float-value x
       (+e (evaluation-float-value x)
	   (normalize-to-gensym-float y)))
     (reclaim-evaluation-long y)
     x)
    (t ; x = float, y = float
     (mutate-evaluation-float-value x
       (+e (evaluation-float-value x) (evaluation-float-value y)))
     (reclaim-evaluation-float y)
     x)))

;; This is an example of how to implement a + evaluator when evaluation-integers
;; are completed! cpm, 3/1/91.
;(def-in-line-evaluator (+ +-integer 1) (1 all (integer integer) integer t)
;  (setq register-1 (stack-arg 0))
;  (setq register-2 (stack-arg 1))
;  (setf (evaluation-integer-value register-1)
;	(+f (evaluation-integer-value register-1)
;	    (evaluation-integer-value register-2)))
;  (reclaim-evaluation-integer register-2))

(def-in-line-evaluator (+ +-integer 1) (1 all (integer integer) integer)
  (+f (stack-arg 0) (stack-arg 1)))

(def-in-line-evaluator (+ +-float 2) (2 all (float float) float t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-float-value
    register-1
    (+e (evaluation-float-value register-1)
	(evaluation-float-value register-2)))
  (reclaim-evaluation-float register-2))

(def-in-line-evaluator (+ +-long 3) (100 all (long long) long t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-long-value
    register-1
    (+l (evaluation-long-value register-1)
	(evaluation-long-value register-2)))
  (reclaim-evaluation-long register-2))

;;; The `- binary stack evaluator' accepts two quantity arguments and returns
;;; the result of subtracting the second from the first.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;;; - (number, number)


(def-float-contagion-stack-operator -)

(def-in-line-evaluator (- subtract-quantity 4) (3 all (number number) number t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1
	(subtract-evaluation-quantities (stack-arg 0) (stack-arg 1))))

(defun-simple subtract-evaluation-quantities (x y) ; like add-evaluation-quantities
  (cond
    ((fixnump x)
     (cond
       ((fixnump y) (-f x y))
       ((evaluation-long-p y)
	(-l x (evaluation-long-value y)))
       (t
	(mutate-evaluation-float-value y
	  (-e (coerce-fixnum-to-gensym-float x)
	      (evaluation-float-value y)))
	y)))
    ((evaluation-long-p x)
     (cond  
       ((fixnump y)
	(-l (evaluation-long-value x) y))
       ((evaluation-long-p y)
	(-l (evaluation-long-value x) (evaluation-long-value y)))
       (t
	(mutate-evaluation-float-value y
	  (-e (normalize-to-gensym-float x)
	      (evaluation-float-value y)))
	y)))
    ((fixnump y) ; x = float
     (mutate-evaluation-float-value x
       (-e (evaluation-float-value x)
	   (coerce-fixnum-to-gensym-float y)))
     x)
    ((evaluation-long-p y) ; x = float
     (mutate-evaluation-float-value x
       (-e (evaluation-float-value x)
	   (normalize-to-gensym-float y)))
     x)
    (t ; x = float, y = float
     (mutate-evaluation-float-value x
       (-e (evaluation-float-value x) (evaluation-float-value y)))
     (reclaim-evaluation-float y)
     x)))

;(def-in-line-evaluator (- subtract-integer 1) 
;		       (54 all (integer integer) integer t)
;  (setq register-1 (stack-arg 0))
;  (setq register-2 (stack-arg 1))
;  (setf (evaluation-integer-value register-1)
;	(-f (evaluation-integer-value register-1)
;	    (evaluation-integer-value register-2)))
;  (reclaim-evaluation-integer register-2))

;; Rewrite the following evaluator when evaluation-integers are implemented!!
;; cpm, 3/1/91.
(def-in-line-evaluator (- subtract-integer 1) (4 all (integer integer) integer)
  (-f (stack-arg 0) (stack-arg 1)))

(def-in-line-evaluator (- subtract-float 2) (5 all (float float) float t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-float-value
    register-1
    (-e (evaluation-float-value register-1)
	(evaluation-float-value register-2)))
  (reclaim-evaluation-float register-2))

(def-in-line-evaluator (- subtract-long 3) (102 all (long long) long t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-long-value
    register-1
    (-l (evaluation-long-value register-1)
	(evaluation-long-value register-2)))
  (reclaim-evaluation-long register-2))

;;; The `- unary stack evaluator' accepts one quantity argument and returns the
;;; negation of the argument.  This evaluator is available in the inference
;;; engine, procedures, and the simulator.

;;; - (number)

(def-in-line-evaluator (- negate 3)
		       (6 all (number) number t pprint-negate-evaluator)
  (setq register-1 (stack-arg 0))
  (cond ((fixnump register-1)
	 (setq register-1 (-f register-1)))
	((evaluation-long-p register-1)
	 (mutate-evaluation-long-value
	   register-1
	   (-l (evaluation-long-value register-1))))
	(t
	 (mutate-evaluation-float-value
	   register-1
	   (-e (evaluation-float-value register-1))))))

;(def-in-line-evaluator (- negate-integer 1) (7 all (integer) integer t)
;  (setq register-1 (stack-arg 0))
;  (setf (evaluation-quantity-value register-1)
;	(-f (evaluation-quantity-value register-1))))

;; Rewrite the following when evaluation-integers are implemented!!  cpm,
;; 3/1/91.

(def-in-line-evaluator (- negate-integer 1)
		       (7 all (integer) integer nil pprint-negate-evaluator)
  (-f (stack-arg 0)))

(def-in-line-evaluator (- negate-float 2)
		       (8 all (float) float t pprint-negate-evaluator)
  (setq register-1 (stack-arg 0))
  (mutate-evaluation-float-value
    register-1
    (-e (evaluation-float-value register-1))))

(def-in-line-evaluator (- negate-long 2) (104 all (long) long t pprint-negate-evaluator)
  (setq register-1 (stack-arg 0))
  (mutate-evaluation-long-value
    register-1
    (-l (evaluation-long-value register-1))))

;;; The `* stack evaluator' accepts two quantity arguments and returns the
;;; result of multiplying the two values.  The new form of this evaluator
;;; differs from the earlier one by not accepting any number of arguments.  This
;;; evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; EVAL: accepted any number of arguments.
;;; STACK-EVAL: accepts only two arguments.

;;; * (number, number)

(def-float-contagion-stack-operator *)

(def-in-line-evaluator (* *-quantity 4) (9 all (number number) number t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1
	(multiply-evaluation-quantities (stack-arg 0) (stack-arg 1))))

(defun-simple multiply-evaluation-quantities (x y)
  (cond
    ((fixnump x)
     (cond
       ((fixnump y) (*f x y))
       ((evaluation-long-p y)
	(mutate-evaluation-long-value y
	  (*l x (evaluation-long-value y)))
	y)
       (t
	(mutate-evaluation-float-value y
	  (*e (coerce-fixnum-to-gensym-float x)
	      (evaluation-float-value y)))
	y)))
    ((evaluation-long-p x)
     (cond  
       ((fixnump y)
	(mutate-evaluation-long-value x
	  (*l (evaluation-long-value x) y))
	x)
       ((evaluation-long-p y)
	(mutate-evaluation-long-value x
	  (*l (evaluation-long-value x)
	      (evaluation-long-value y)))
	(reclaim-evaluation-long y)
	x)
       (t ; float
	(mutate-evaluation-float-value y
	  (*e (normalize-to-gensym-float x)
	      (evaluation-float-value y)))
	(reclaim-evaluation-float y)
	y)))
    ((fixnump y) ; x = float
     (mutate-evaluation-float-value x
       (*e (evaluation-float-value x)
	   (coerce-fixnum-to-gensym-float y)))
     x)
    ((evaluation-long-p y) ; x = float
     (mutate-evaluation-float-value x
       (*e (evaluation-float-value x)
	   (normalize-to-gensym-float y)))
     (reclaim-evaluation-long y)
     x)
    (t ; x = float, y = float
     (mutate-evaluation-float-value x
       (*e (evaluation-float-value x) (evaluation-float-value y)))
     (reclaim-evaluation-float y)
     x)))

;(def-in-line-evaluator (* *-integer 1) (10 all (integer integer) integer t)
;  (setq register-1 (stack-arg 0))
;  (setq register-2 (stack-arg 1))
;  (setf (evaluation-integer-value register-1)
;	(*f (evaluation-integer-value register-1)
;	    (evaluation-integer-value register-2)))
;  (reclaim-evaluation-integer register-2))

;; Rewrite the following when evaluation-integers are implemented!!  cpm,
;; 3/1/91.

(def-in-line-evaluator (* *-integer 1) (10 all (integer integer) integer)
  (*f (stack-arg 0) (stack-arg 1)))

(def-in-line-evaluator (* *-float 2) (11 all (float float) float t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-float-value
    register-1
    (*e (evaluation-float-value register-1)
	(evaluation-float-value register-2)))
  (reclaim-evaluation-float register-2))

(def-in-line-evaluator (* *-long 2) (101 all (long long) long t)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-long-value
    register-1
    (*l (evaluation-long-value register-1)
	(evaluation-long-value register-2)))
  (reclaim-evaluation-long register-2))


;;; The `/ stack evaluator' accepts two quantity arguments and returns the
;;; result of dividing the first by the second.  If the second argument is not
;;; greater than the smallest-divisor, an error is signalled.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;;; There is only a float version of the / in-line-evaluator because the
;;; evaluator requires floats in its computation.  (Dividing two integers in
;;; Common Lisp can result in a ratio.) The compiler will coerce any integer and
;;; quantity args to type float.

;;; / (dividend, divisor)

(def-float-contagion-stack-operator /)

;; Removed the code that prevents division by a number less than smallest-divisor.
;; This should now be caught by the signal handlers.  - cpm, 1/3/92.  

;; jh, 1/27/92.  This is NOT caught by signal handlers on some machines (notably
;; the Sparcs).  They simply produce a NaN float (not a number).  I hesitate to
;; re-introduce the *smallest-divisor* check, however, since it was probably
;; removed for performance reasons.

;; It was removed for performance and correctness reasons.  We we unneccessarily
;; limiting the division arithmatic with this test, in that many divisions would
;; be ok which would have been disallowed by the given test.  If we are to add
;; checking back in for underflow, it should be by checking the result of the
;; division to see if it is an exceptional float (Nan, plus-infinity,
;; minus-infinity) rather than reintroducing the previous check.  Also note that
;; we would have to introduce the test into all operations on floats and
;; quantities, since any of these can over or underflow.  For the time being, we
;; will allow exceptional floats to be propagated through G2 on those machines
;; which support them.  -jra 1/28/92

(def-in-line-evaluator (/ /-float 2) (12 all (float float) float t)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (setq cached-top-of-stack top-of-stack)
;  (cond ((>e (abs float-register-1)  *smallest-divisor*)
;	 (setf (evaluation-float-value register-1)
;	       (/e (evaluation-float-value register-1) float-register-1))
;	 (reclaim-evaluation-float register-2))
;	(t
;	 (reclaim-evaluation-float register-1)
;	 ;; The following reclaims its arg.
;	 (division-by-zero-eval-error register-2 top-of-stack)))
  (mutate-evaluation-float-value
    register-1
    (/e (evaluation-float-value register-1)
	(evaluation-float-value register-2)))
  (reclaim-evaluation-float register-2))




;;; The `^ stack evaluator' and `EXPT stack evaluator' return the value of the
;;; first argument raised to the power of the second argument.

;;; These evaluators call g2-exponent instead of calling the Common Lisp expt
;;; function directly.  G2-exponent catches and prevents certain errors.  Since
;;; G2 does not have complex or ratio numeric datum, an error is signalled when
;;; a result would be a complex number and ratio results are prevented by
;;; coercing the base to a float when necessary.  Several other errors involving
;;; a base of 0 or 0.0 are signalled or prevented.

;;; The two arguments to the evaluators are either float or integer quantities.
;;; The return value is of type integer if both arguments are integer.  If
;;; either argument is a float or when an argument must be coerced to a float
;;; (as described above to prevent errors or ratio values), the result is a
;;; float.  These evaluator are available in the inference engine, procedures,
;;; and the simulator.

;; Note that there is no difference between the implementations of any of these
;; power evaluators, since g2-exponent is a function.  The integer version
;; should therefore be eliminated.  The float version should be retained since
;; it propagates a float data type as result.  In the future we may further
;; optimize the float version.  -jra 11/20/90

;; The integer version has been removed.  Also, the integer version could not
;; guarantee that the result is always an integer.  For example, when the power is
;; an integer less than 0, the base is coerced to a float to prevent a ratio
;; result.  4dec90, cpm.

;;; ^ (base, exponent)

(def-float-contagion-stack-operator ^)

(def-in-line-evaluator (^ ^-quantity 3) (13 all (number number) number)
  (setq cached-top-of-stack top-of-stack)
  (expt-evaluation-quantities (stack-arg 0) (stack-arg 1) top-of-stack))


(def-in-line-evaluator (^ ^-float 2) (14 all (float float) float)
  (setq cached-top-of-stack top-of-stack)
  (g2-exponent-evaluation-float (stack-arg 0) (stack-arg 1) top-of-stack))

;; The evaluator above could be optimized by making a version of
;; g2-exponent-float which took and mutated evaluation-floats.  This
;; would stop unneccessary consing of intermediate double-floats.  -jra
;; 1/25/92 - Done.  - cpm, 1/30/92



;;; The function 'expt-evaluation-quantities' is called by the ^ and
;;; expt quantity exponent stack evaluators.

(defun expt-evaluation-quantities (base-number power-number top-of-stack)
  (let ((e-float-base (if (evaluation-float-p base-number)
                          base-number
                          (prog1
                              (make-evaluation-float (evaluation-quantity-value-as-float base-number))
                              (reclaim-evaluation-quantity base-number))))
        (e-float-power (if (evaluation-float-p power-number)
                           power-number
                           (prog1
                               (make-evaluation-float (evaluation-quantity-value-as-float power-number))
                               (reclaim-evaluation-quantity power-number)))))
    (g2-exponent-evaluation-float e-float-base e-float-power top-of-stack)))



;;; The function 'g2-exponent-evaluation-float' is an evaluation-float
;;; version of g2-exponent.  It accepts two evaluation-float arguments,
;;; mutates and returns one float with the result, and reclaims the
;;; other float.  This function may signal an error and not return.
;;; This function signals several errors in expt that would cause an
;;; error in Common Lisp.

(defun g2-exponent-evaluation-float
       (evaluation-float-base evaluation-float-power top-of-stack)
  (cond ((>e (evaluation-float-value evaluation-float-base) 0.0)
	 ;; Positive Base ok.  Don't need to test for a ratio result
	 ;; since we have float arguments.
	 (mutate-evaluation-float-value
	   evaluation-float-base
	   (expte
	     (evaluation-float-value evaluation-float-base)
	     (evaluation-float-value evaluation-float-power)))
	 (reclaim-evaluation-float evaluation-float-power)
	 evaluation-float-base)
	((=e (evaluation-float-value evaluation-float-base) 0.0)
	 ;; Base is 0.0
	 (cond
	   ((=e (evaluation-float-value evaluation-float-power) 0.0)
	    ;; (expt 0.0 0.0) would cause a Common Lisp error.
	    (mutate-evaluation-float-value evaluation-float-base 1.0)
	    (reclaim-evaluation-float evaluation-float-power)
	    evaluation-float-base)
	   ((>e (evaluation-float-value evaluation-float-power) 0.0)
	    ;; (expt 0.0 +power-float) is 0.0
	    (mutate-evaluation-float-value evaluation-float-base 0.0)
	    (reclaim-evaluation-float evaluation-float-power)
	    evaluation-float-base)
	   (t
	    ;; (expt 0.0 -power-float) is undefined.
	    (stack-error
	      top-of-stack
	      "The arguments to the exponent operator were a base ~NV and a ~
               negative power ~NV.  These values produce an undefined result."
	      evaluation-float-base evaluation-float-power))))
	(t
	 ;; Negative base.  (expt -base-float +power-float) produces a
	 ;; complex numeric result which is not allowed in G2.
	 (let ((truncated-power
                 (truncate (evaluation-float-value evaluation-float-power))))
	   (cond
	     ;; Test for a power of the form n.0 and avoid a complex result.
	     ((= (evaluation-float-value evaluation-float-power)
		 truncated-power)
	      (mutate-evaluation-float-value
		evaluation-float-base
		(expt
		  (evaluation-float-value evaluation-float-base)
		  truncated-power))
	      (reclaim-evaluation-float evaluation-float-power)
	      evaluation-float-base)
	     (t
	      (stack-error
		top-of-stack
		"The arguments to the exponent operator were a negative ~
                base ~NV and a floating point power ~NV.  These values ~
                produce a complex number, which is not supported in G2."
		evaluation-float-base evaluation-float-power)))))))






;;;; Symbolic Expression Evaluators




;;; The `QUOTE stack evaluator' is a special form that accepts one symbol argument
;;; and returns it unevaluated.  This evaluator is available in the inference
;;; engine and procedures.

(def-special-form-converter quote (expression)
  (make-stack-node-instruction
    'push-constant
    (make-evaluation-symbol (second expression))))




;;; The `LET stack evaluator' is a special form which binds values into local
;;; names and then evaluates and returns the result of a single bound expression
;;; form.  The bindings are only available for the surrounded expressions, and
;;; so are expression bound local names.  Note that it is OK for the bound
;;; expressions to return NO-ITEM, since the excapsulated expression may
;;; perform an exists test on the arguments to determine its value.  The types
;;; of the expressions can only be determined by the chooser after looking to
;;; the types of the expressions being evaluated.

;;; Note that the initial value expression of LET may be NIL.  This occurs in
;;; cases where the evaluation of a form within the LET will set a value into
;;; the variable, as happens in there-exists-literal.  In this case the variable
;;; should be generated and made available, but no attempt should be made to set
;;; an initial value into it.  Also, note that the expression should be
;;; converted before the new binding for the value is made available in the
;;; expression bound local names list.

(def-expiration-special-form let)

(def-special-form-converter let (expression)
  (gensym-dstruct-bind ((nil bindings sub-expression) expression)
    (loop for (binding-name binding-expression?) in bindings
	  for var-spot = (generate-new-stack-frame-var-spot
			   'item-or-datum)
	  when binding-expression?
	    collect
	      (convert-expression-to-stack-node-tree binding-expression?)
	      into expression-list using stack-cons
	  when binding-expression?
	    collect
	      var-spot into var-spot-list using phrase-cons
	  do
      (phrase-push (phrase-cons binding-name var-spot)
		   expression-bound-local-names)
	  finally
	    (let ((new-node (make-stack-node-instruction 'let var-spot-list)))
	      (setf (stack-node-argument-nodes new-node)
		    (nconc expression-list
			   (stack-list (convert-expression-to-stack-node-tree
					 sub-expression))))
	      (return new-node)))))




;;; The types of the generated stack frame vars for the LET is determined by the
;;; types of expressions whose value is being bound.

(def-preferred-instruction-chooser let
  (declare (ignore extra-info))
  (let* ((unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	 (unknown-arguments? nil)
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (binding-expressions argument-nodes)
	 (binding-type
	   (maybe-add-no-item-implies-unknown
	     (maybe-add-unknown '(or item-or-datum (no-item)) unknown-allowed?)
	     no-item-implies-unknown-allowed?))
	 (result-expression (car (last argument-nodes))))
    (loop for cons on binding-expressions
	  until (null (cdr-of-cons cons))
	  do
      (setf (car cons)
	    (choose-stack-node-instructions-and-types (car cons) binding-type))
      (when (and (null unknown-arguments?)
		 (type-specification-subtype-p
		   '(unknown-datum)
		   (stack-node-value-type (car cons))))
	(setq unknown-arguments? t)))
    (setf result-expression
	  (choose-stack-node-instructions-and-types
	    result-expression required-type))
    (setf (car (last argument-nodes)) result-expression)
    (let ((result-type (stack-node-value-type result-expression)))
      (when (and (not (type-specification-subtype-p
			'(unknown-datum) result-type))
		 unknown-arguments?)
	(setq result-type
	      (make-type-specification-union result-type '(unknown-datum))))
      (setf (stack-node-value-type stack-node-instruction)
	    result-type))
    stack-node-instruction))



(declare-instruction-for-optimizer
  'let
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor get-stack-node-extra-info
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles))

;;; The emitter for LET should set the local variables, then evaluate the result
;;; expression.

(def-stack-node-instruction-emitter let
  (let* ((var-spots extra-info)
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (binding-expressions argument-nodes))
    (loop for var-spot in var-spots
	  for binding-expression in binding-expressions
	  do
      (emit-stack-node-tree byte-code-stream binding-expression)
      (call-stack-instruction-emitter pop-into-surrounding-local-var byte-code-stream
						      var-spot))
    (emit-stack-node-tree byte-code-stream (car (last argument-nodes)))))

;;; The `NAME stack evaluator' returns the name of the item that is referred to.
;;; If the item has more than one name, the first name in the item's attribute
;;; slot is returned.  This evaluator is only available in the inference engine.

;;; NAME (item)

;; The NAME evaluator is obsolete.  I can only find one reference to this
;; evalutaor in Grammar3.  The parse from message-expression to name is commented
;; out.  "The name of" expression parses into the Name role-server.  cpm, 6/21/91

;; Number 15 is now used by another evaluator!

;(def-in-line-evaluator name (15 (inference) ((class item)) truth-value t)
;  (setq register-1 (name-or-names-for-frame (stack-arg 0)))
;  (when (consp register-1)
;    (setq register-1 (car register-1)))
;  (if register-1
;      (setq register-1 (make-evaluation-symbol register-1))
;      ;; Unknown value.
;      (setq stack-expiration nil)))






;;;; Text Expression Evaluators




;;; The `FORMAT-FORM stack evaluator' is a special form that takes multiple
;;; format-components and formats a text-string.  The format-components can
;;; contain expressions, text-strings, and format or fixed-format expressions.
;;; The special-form converter returns an instruction-node tree that contains
;;; argument nodes that are the format-form arguments and a count of all
;;; arguments including the argument count.

;;; In version 3.0, the Inform action will compile to "format-form" instead of
;;; "and" as needed insteaded of duplicating the format-form evaluator within
;;; Inform.  Also, format and fixed-format have their own evaluators instead of
;;; being handled specially in format-form.

;;; The Format and Fixed-Format format-components correspond to the phrases "as
;;; <format>", "as a time stamp", and "as an interval".

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.

;;; This evaluator is available in the inference engine and procedures.

(declare-optimizer-stack-instruction format-form)



(def-special-form-converter format-form (expression)
  (let ((format-form-node (make-stack-node-instruction 'format-form nil)))
    (setf (stack-node-argument-nodes format-form-node)
	  (loop for argument in (cdr expression)
	  ;; Unless the argument is a zero length string (which has no
	  ;; effect on the result of this function), add the argument to the
	  ;; list and increment the count.  -jra 11/6/91
	  unless (and (text-string-p argument)
		      (=f (text-string-length argument) 0))
	    collect (convert-expression-to-stack-node-tree argument)
	    using stack-cons))
    format-form-node))




;;; The preferred instruction chooser for FORMAT-FORM chooses instructions and
;;; types on its arguments, and then sets its own return value, depending on
;;; whether any of its arguments can return unknown.  It expects the last
;;; argument to be an integer count of all the arguments, including this count
;;; argument.

(def-preferred-instruction-chooser format-form
  (declare (ignore extra-info))
  (let ((unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(unknown-argument? nil))
    (loop for argument-node-cons on argument-nodes
	  do
      (setf (car argument-node-cons)
	    (choose-stack-node-instructions-and-types
	      (car argument-node-cons)
	      (if unknown-allowed?
		  '(or datum (unknown-datum))
		  'datum)))
      (when (type-specification-subtype-p
	      '(unknown-datum)
	      (stack-node-value-type (car argument-node-cons)))
	(setq unknown-argument? t)))
    (setf (stack-node-value-type stack-node-instruction)
	  (if unknown-argument?
	      '(or text (unknown-datum))
	      'text))))



;;; The stack node instruction emitter for FORMAT-FORM emits to a
;;; funcalled-instruction.

(def-stack-node-instruction-emitter format-form
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    (loop for node in argument-nodes
	  do
      (emit-stack-node-tree byte-code-stream node))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'format-form
				    (length argument-nodes) 1)))



;;; Instruction 32, the `FORMAT-FORM funcalled stack-instruction' is used to
;;; implement the evaluator for format-form.  This evaluator takes any number of
;;; format-component stack-arguments.  The format-components can be the value of
;;; any expression including a format expression or a fixed-format expression.
;;; These arguments are written to a text string and the text string is
;;; returned.

;;; The arguments are [AS OF 5/26/92] printed beautifully (non-parsably); e.g.,
;;; strings are not quoted; special characters in symbols are not quoted; etc.]
;;; [Prior to 5/26/92, only strings were printed beautifully; symbols were not,
;;; except in Version 3.0 Beta Rev. 5, not generally released. (MHD 5/26/92)]

;;; Note, that for the special-form evaluators that take a variable number of
;;; arguments, the arg-count argument in the funcalled-instruction definition is
;;; not correct.  The actual argument count is left on the top of the stack and
;;; is the count of additional stack arguments and this argument (i.e., the
;;; argument count itself).

;;; Modified this instruction to attempt an optimization of the expression
;;; "[<text-value>] <any-other-values>", where text-value is allocated as an
;;; adjustable-text-string, with a fill-pointer.  This expression is recognized
;;; by this instruction when the first format arg (the second stack arg) is an
;;; adjustable-text-string.  In this case, the instruction will write the second
;;; through N format arguments into a string and attempt to fit the string at
;;; the end of the adjustable-text-string, after the fill-pointer.  This is a
;;; useful optimization when the G2 user is contatenating values to the end of a
;;; long text string.  This change is for G2 version 4.0.  [NOTE: in G2 version
;;; 5.0 it became the case that evaluation texts (wide strings) _always_ have
;;; fill pointers.]

;;; The current implementation was done by MHD, 5/25/00.  It makes a few
;;; assumptions:
;;;
;;;  (a) wide string is the implementation type of evaluation-text;
;;;  (b) evaluation integers can be written using twrite-fixnum
;;;        just as they would be if written using twrite-evaluation-value;
;;;  (c) evaluation symbols can be written by writing their symbol
;;;        name text string, resulting in output equivalent to that
;;;        of write-evaluation-value

(def-funcalled-instruction format-form (32 (inference procedure) (0) 1 nil pprint-format-form-instruction)
  (let* ((arg-count (evaluation-integer-value (svref local-stack top-of-stack)))
	 (first-index (-f top-of-stack arg-count))
	 (last-index (-f top-of-stack 1))
	 (index first-index)
	 (total-length 0)
	 (string-1? nil)
	 (length-1 0)
	 (general-cases '()))
    (declare (type fixnum arg-count first-index last-index total-length length-1))
    (macrolet ((process ()
		 `(let ((arg (svref local-stack index)))
		    (cond
		      ((wide-string-p arg)
		       (incff total-length (wide-string-length arg))
		       (when (=f index 0)
			 (setq string-1? arg)
			 (setq length-1 (wide-string-length arg))))
		      ((evaluation-integer-p arg)
		       (incff total-length (fixnum-twrite-length arg)))
		      ((evaluation-symbol-p arg)
		       (incff total-length
			      (wide-string-length
				(get-or-make-symbol-name-wide-string-macro arg))))
		      (t
		       (multiple-value-bind (wide-string-list length)
			   (write-evaluation-value-to-wide-string-list arg)
			 (incff total-length length)
			 (setq general-cases
			       (nconc general-cases (gensym-list wide-string-list))))))
		    (incff index)))
	       (process-2 (destination-string fill)
		 `(let* ((source-arg (svref local-stack index))
			 (length 0))
		    (declare (type fixnum length))
		    (cond
		      ((evaluation-integer-p source-arg)
		       (setq length
			     (twrite-fixnum-into-wide-string
			       source-arg ,destination-string ,fill)))
		      ((evaluation-symbol-p source-arg)
		       (let ((source-string (symbol-name-wide-string source-arg)))
			 (setq length (wide-string-length source-string))
			 (memcpy-portion-of-wide-string-into-wide-string
			   source-string 0 length ,destination-string ,fill))
		       (reclaim-evaluation-symbol source-arg))
		      ((wide-string-p source-arg)
		       (setq length (wide-string-length source-arg))
		       (memcpy-portion-of-wide-string-into-wide-string
			 source-arg 0 length ,destination-string ,fill)
		       (reclaim-wide-string source-arg))
		      (t
		       ;; general case
		       (setq length
			     (copy-wide-string-list-text-to-wide-string-and-reclaim
			       (gensym-pop general-cases)
			       ,destination-string ,fill))
		       (reclaim-evaluation-value source-arg)))
		    (incff ,fill length)
		    (incff index)))
	       (pass-2 (destination-string fill-start index-offset)
		 `(let ((result ,destination-string)
			(fill ,fill-start))
		    (declare (type fixnum fill))
		    (setq index (+f first-index ,index-offset))
		    (loop until (>f index last-index) do (process-2 result fill))
		    (when general-cases (reclaim-gensym-list general-cases))
		    (setf (wide-string-length result) total-length)
		    (setf (svref local-stack first-index) result)
		    nil)))
      (loop until (>f index last-index) do (process))
      (cond
	((>f total-length maximum-length-for-user-text-strings)
	 (format-form-too-long
	  local-stack top-of-stack arg-count total-length general-cases))
	((and string-1?			; optimization: reuse string 1
	      (<=f total-length (wide-string-total-length string-1?)))
	 (pass-2 string-1? length-1 1))
	(t
	 (pass-2 (make-wide-string total-length) 0 0))))))


;;; Subfunctions of the above format-form instruction.
;;;
;;; Write-evaluation-value-to-wide-string-list is called with an evaluation
;;; value, and returns a wide string list (a gensym list as created by
;;; twith-output-to-wide-string-list) containing the text representing
;;; evaluation-value, as printed by write-evaluation-value.
;;;
;;; Copy-wide-string-list-text-to-wide-string-and-reclaim takes a wide string
;;; list and copies its text to destination-string, which must be a wide string
;;; known to have enough room left to write all of the text from destination
;;; start until the end of the total length.  It reclaims its wide-string-list
;;; argument strings and conses.  It returns the length of the text it has
;;; written as its value.
;;;
;;; Format-form-too-long is called when the resulting text would be longer than
;;; maximum length permitted for user text strings.  It creates a stack-error
;;; message text string using tformat-stack-error-text-string, and returns that
;;; string as its value. Before returning, it reclaims general-case-list, which
;;; must be a gensym list of wide string lists, which may have been created as
;;; part of the initial pass to determine the total length of the text.

(defun write-evaluation-value-to-wide-string-list (evaluation-value)
  (let* ((evaluation-value-writing-target-length?
	   maximum-length-for-user-text-strings)
	 (wide-string-list
	   (twith-output-to-wide-string-list
	     (write-evaluation-value evaluation-value))))
    (values
      wide-string-list
      (loop for string in wide-string-list
	    sum (wide-string-length string)))))


(defun-simple copy-wide-string-list-text-to-wide-string-and-reclaim
    (wide-string-list destination-string destination-start)
  (prog1 (loop for string in wide-string-list
	       as dest-start = destination-start
			     then (+f dest-start length)
	       as length = (wide-string-length string)
	       do (copy-portion-of-wide-string-into-wide-string
		    string 0 length
		    destination-string dest-start)
		  (reclaim-wide-string string)
	       summing length)
    (reclaim-gensym-list wide-string-list)))


(defun-simple format-form-too-long
    (local-stack top-of-stack arg-count result-text-length general-case-list)
  (let* ((small-formatted-string 
	   (twith-output-to-wide-string
	     (loop with n = 20
		   as i from (-f top-of-stack arg-count)
		   as arg = (svref local-stack i)
		   repeat arg-count
		   do (let* ((string
			       (if (wide-string-p arg)
				   (copy-wide-string arg)
				   (let ((evaluation-value-writing-target-length?
					   20))
				     (twith-output-to-wide-string
				       (write-evaluation-value arg)))))
			     (length (wide-string-length string)))
			(twrite-beginning-of-wide-string string (minf n length))
			(reclaim-wide-string string)
			(decff n length))
		   while (>f n 0))))
	 (error-string
	   (tformat-stack-error-text-string
	     "A text value cannot contain more than ~a characters.  The text ~
                  begins with \"~a...\" and contains ~a characters."
	     maximum-length-for-user-text-strings
	     small-formatted-string
	     result-text-length)))
    (reclaim-wide-string small-formatted-string)
    ;; This is where we reclaim the list of wide-string lists.  (It's simpler
    ;; not to use them, though they may have some of the text we need.)
    (loop for wsl in general-case-list
	  do (loop for ws in wsl do (reclaim-wide-string ws))
	     (reclaim-gensym-list wsl)
	  finally
	    (reclaim-gensym-list general-case-list))
    error-string))





;;; The `FORMAT stack evaluator' is a special form that formats an expression
;;; which can be used in FORMAT-FORM.  The expression accepts two arguments, the
;;; expression and the formatting information.

;;; The expression is of the form: (format <expression> time-stamp), (format
;;; <expression> seconds), or (format <expression> <format-string>).

;;; The special-form converter returns an instruction-node tree that contains
;;; argument nodes of the expression and the quoted formatting argument.

;;; This evaluator is new to version 3.0.  The evaluation of this expression was
;;; previously handled inside of the evaluator for INFORM and FORMAT-FORM.

;;; See also the FIXED-FORMAT evaluator.

;;; This evaluator is available in the inference engine and procedures.

;; FUNCTIONALITY CHANGE!!  Previously evaluation of this expression in Inform
;; and Format-Form allowed the value to be of any data type.  It would print
;; numeric values in the way expected for Format.  Non-numeric values would be
;; printed as constants.  Now a non-numeric value argument is an error.

;; The parse of Format has been changed to quote its time-stamp or seconds
;; argument.  This eliminates the need for a special form converter.

;; Does anything else depend on this grammar, such as readouts?

;; What is an example use of a <format-string> argument?  cpm, 5/17/91

(def-funcalled-evaluator format (value format-string-or-unit)
			 (0 (inference procedure)
			    (number datum) text
			     funcall-eval-type-2-arg
			     nil pprint-format-evaluator)
  (let ((quantity-value (evaluation-quantity-value value))
	(format-value (evaluation-value-value format-string-or-unit))
	(text-value nil))
    (setq text-value
	  (twith-output-to-text-string
	    (case format-value
	      (time-stamp (print-constant quantity-value 'time-stamp))
	      (seconds (print-constant quantity-value 'seconds))
	      (t (stack-error
		   cached-top-of-stack
		   "Unrecognized format control argument ~a"
		   format-value))
						; The following case is from the
						; old evaluators.  I don't see
						; how it can be executed!!
						; Check the parse.  cpm, 5/17/91
	      ; (t (tformat format-value quantity-value))
	      )))
	(reclaim-evaluation-quantity value)
	(reclaim-evaluation-value format-string-or-unit)
	(make-evaluation-text-reclaiming-argument text-value)))





;;; The `FIXED-FORMAT stack evaluator' is a special form that formats an
;;; expression which can be used in FORMAT-FORM.  The expression accepts three
;;; arguments, the number, the integral size, and the fraction size.

;;; The expression is of the form: (fixed-format <expression> <integral-size>
;;; <fraction-size>).

;;; This evaluator is new to version 3.0.  The evaluation of this expression was
;;; previously handled inside of the evaluator for INFORM and FORMAT-FORM.

;;; See also the FORMAT evaluator.

;;; This evaluator is available in the inference engine and procedures.

;; FUNCTIONALITY CHANGE!!
;; 1. In pre-3.0, the evaluation of this form in Inform and Format-Form
;; restricted the precision to 6 digits.  Now the precision is 16.  See the
;; precision argument to write-floating-point-number.
;; 2.  Previously evaluation of this expression in Inform and Format-Form
;; allowed value to be of any data type.  It would print numeric values in the
;; way expected for Fixed-Format.  Non-numeric values would be printed as
;; constants.  Now a non-numeric value argument is an error.

(def-funcalled-evaluator fixed-format (number integral-size fraction-size)
			 (1 (inference procedure)
			    (number integer integer) text
			    funcall-eval-type-3-arg
			    nil pprint-fixed-format-evaluator)
  (let ((number-value (evaluation-quantity-value number))
	(integral-size-value (evaluation-integer-value integral-size))
	(fraction-size-value (evaluation-integer-value fraction-size))
	(text-value nil))
    (setq text-value
	  (twith-output-to-text-string
	    (write-floating-point-number
	      number-value integral-size-value fraction-size-value 16 
	      nil nil nil)))			;suppress-trailing-zeros-p
    (reclaim-evaluation-quantity number)
    (reclaim-evaluation-integer integral-size)
    (reclaim-evaluation-integer fraction-size)
    (make-evaluation-text-reclaiming-argument text-value)))




;;; `format-numeric-text' takes two arguments: a text whose leftmost part is a
;;; quantity {leading spaces are ok, as is anything following the quantity, but
;;; see below for special treatment of a trailing "*"} and a second argument
;;; which will be a text containing a dd.ddd format.  The result will be a text
;;; which will be the result of applying the format to the numeric text.

;;; In order to assist with formatting variable values, the first argument can
;;; also be one of the following:
;;; "****" which will always return "****", regardless of the format argument
;;; (though one still needs to supply one) OR 
;;; a text with a quantity, with a trailing "*".  This will result in a text 
;;; which has the number formatted according to the dd.ddd directive, with a
;;; trailing "*".  So for example:  format-numeric-text("35.3*", "dd.ddd")  ==>
;;; "35.300*"

(def-funcalled-evaluator format-numeric-text (number-as-text format-text)
    (121 (inference procedure)
	 (text text) text
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (multiple-value-bind (format-left? format-right)
      (decode-format (intern-text-string-no-reclaim
		       (evaluation-text-value format-text)))
    (unless format-left?
      (stack-error cached-top-of-stack
		   "~NV is not a ddd.dddd format."
		   format-text))
    (let ((text-value nil)
	  (expired-p nil))
      (setq text-value
	    (if (text-string= (evaluation-text-value number-as-text)
			      #w"****")		;sad this isn't abstracted
		(copy-constant-wide-string #w"****")
		(multiple-value-bind (number-value? type start end)
		    (read-number-from-text-string
		      (evaluation-text-value number-as-text))
		  (declare (ignore type start))
		  (cond ((or (eq number-value? 'overflow)
			     (eq number-value? 'underflow))
			 (stack-error cached-top-of-stack
				      "~NV causes ~NV when formatted as a number."
				      number-as-text
				      number-value?))
			((null number-value?)
			 (stack-error cached-top-of-stack
				      "~NV could not be formatted as a number."
				      number-as-text))
			((=f (1+f end)
			     (text-string-length
			       (evaluation-text-value number-as-text)))
			 ;; There is one character to the right of the number.
			 ;; If it's "*", treat this specially, else error
			 (if (char=w (charw number-as-text end)
				     #.%*)
			     (setq expired-p t)
			     (stack-error cached-top-of-stack
					  "~NV is not the text of a number, ~
                                           an expired number, nor ****"
					  number-as-text))))
		  (twith-output-to-text-string
		    (write-floating-point-number
		      number-value? format-left? format-right 16
		      nil nil nil)
		    ;; kludge to show expired value.  Can we use the
		    ;; obsolete-datum evaluation-writer somehow? -dkuznick,
		    ;; 2/18/05
		    (when expired-p
		      (twrite #w"*"))))))
      (reclaim-evaluation-text number-as-text)
      (reclaim-evaluation-text format-text)
      (make-evaluation-text-reclaiming-argument text-value))))



;;;; Logical Expression Evaluators




;; A FUNCTIONALITY CHANGE!!  For comparison evaluators: =, /=, >, >=, <, <=.  If
;; there is an arg type mismatch, the old evaluators:

;; EVAL & PROC-EVAL - returned falsity (a recent change) for = and /=;  For
;; other evaluators EVAL gave a warning and return unknown, PROC-EVAL signaled
;; an error.

;; SIMULATOR - if both args were not numeric, gave a warning and
;; simulation-no-value was returned.

;; STACK-EVAL - now signals an error within the "datum" type evaluator.  I.e.
;; the types gotta match.  Two exceptions are = evaluator which returns falsity
;; and /= evaluator which returns truth for mixed datum types.



;;; The `= stack evaluator' accept two arguments and returns a truth-value.  If
;;; the two arguments are equal, truth is returned.  Otherwise, falsity is
;;; returned.  It is an error if the arguments are not of the same type.

;;; There are versions of this evaluator which apply to different argument types
;;; and environments.
;;;    Number, Integer, Float:  Inference, Procedure, Simulator.
;;;    Text, Symbol, Datum (except truth-value):  Inference, Procedure.

;; Note that you can use an OR combined type as the argument or return type.  At
;; least, give it a try and let's see if it breaks.  -jra 6/3/91

;; Should we warn the user in the documentation that comparing floats for
;; equality is risky??  cpm, 4dec90.

;;; = (datum, datum)

(def-in-line-evaluator (= =-quantity 3) (16 all (number number) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (evaluation-quantity-= register-2 register-3)
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

;; Should we write and use a make-evaluation-boolean instead make-evaluation-
;; truth-value??  - cpm, 4/27/93


;; Rewrite the following evaluator when evaluation-integers are implemented!!
;; cpm, 3/1/91.

(def-in-line-evaluator (= =-integer 1) (17 all (integer integer) boolean)
  (if (=f (stack-arg 0) (stack-arg 1))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(def-in-line-evaluator (= =-float 2) (18 all (float float) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (=e (evaluation-float-value register-2)
			   (evaluation-float-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-float register-2)
  (reclaim-evaluation-float register-3))


;; Rewrite the following when evaluation-symbols are implemented!!  cpm, 3/1/91.

(def-in-line-evaluator (= =-symbol) (19 (inference procedure) (symbol symbol)
					boolean)
  (if (eq (the symbol (stack-arg 0)) (the symbol (stack-arg 1)))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))


(def-in-line-evaluator (= =-text) (20 (inference procedure) (text text)
				      boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (g2-text-equal (evaluation-text-value register-2)
				      (evaluation-text-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-text register-2)
  (reclaim-evaluation-text register-3))


(def-in-line-evaluator (= =-truth-value) 
		       (21 (inference procedure) (truth-value truth-value)
			   boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (=f (evaluation-truth-value-value register-2)
			   (evaluation-truth-value-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-truth-value register-2)
  (reclaim-evaluation-truth-value register-3))


;; Maybe, instead of returning falsity, an error should be signaled when there
;; are incompatible data types!!  This would be a change in functionality.  cpm,
;; 6/24/91

(def-in-line-evaluator (= =-datum 4) 
		       (22 (inference procedure) (datum datum) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (make-evaluation-boolean-value
		     (evaluation-value-= register-2 register-3)))
  (reclaim-evaluation-value register-2)
  (reclaim-evaluation-value register-3))



;;; The `/= stack evaluator' accept two arguments and returns a truth-value.  If
;;; the two arguments are not-equal, truth is returned.  Otherwise, falsity is
;;; returned.  It is an error if the arguments are not of the same type.

;;; There are versions of this evaluator which apply to different argument types
;;; and environments.
;;;    Number, Integer, Float:  Inference, Procedure, Simulator.
;;;    Text, Symbol, Datum (except truth-value):  Inference, Procedure.

;;; /= (datum, datum)

(def-in-line-evaluator (/= /=-quantity 3) (23 all (number number) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (evaluation-quantity-/= register-2 register-3)
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

;; Should we warn the user (in the doc) that comparing floats for inequality is
;; risky??  cpm, 4dec90.


;; Rewrite the following when evaluation-integers are implemented!!  cpm,
;; 3/1/91.

(def-in-line-evaluator (/= /=-integer 1) (24 all (integer integer) boolean)
  (if (/=f (stack-arg 0) (stack-arg 1))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(def-in-line-evaluator (/= /=-float 2) (25 all (float float) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (/=e (evaluation-float-value register-2)
			    (evaluation-float-value register-3))
			 (make-evaluation-truth-value truth)
			 (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-float register-2)
  (reclaim-evaluation-float register-3))


;; Rewrite the following when evaluation-symbols are implemented!!  cpm, 3/3/91.

(def-in-line-evaluator (/= /=-symbol) (26 (inference procedure) (symbol symbol)
					  boolean)
  (if (neq (the symbol (stack-arg 0)) (the symbol (stack-arg 1)))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))


(def-in-line-evaluator (/= /=-text) (27 (inference procedure) (text text)
					boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (not (g2-text-equal (evaluation-text-value register-2)
					   (evaluation-text-value register-3)))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-text register-2)
  (reclaim-evaluation-text register-3))


(def-in-line-evaluator (/= /=-truth-value) 
		       (28 (inference procedure) (truth-value truth-value)
			   boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (/=f (evaluation-truth-value-value register-2)
			    (evaluation-truth-value-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-truth-value register-2)
  (reclaim-evaluation-truth-value register-3))


;; Maybe, instead of returning falsity, an error should be signaled when there
;; are incompatible data types!!  This would be a change in functionality.  cpm,
;; 6/24/91

(def-in-line-evaluator (/= /=-datum 4)
		       (29 (inference procedure) (datum datum)
			   boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (make-evaluation-boolean-value
		     (not (evaluation-value-= register-2 register-3))))
  (reclaim-evaluation-value register-2)
  (reclaim-evaluation-value register-3))



;;; The `> stack evaluator' accept two arguments and returns a boolean.  If the
;;; first argument is strictly greater than the second argument, truth is
;;; returned.  Otherwise, falsity is returned.  It is an error if the arguments
;;; are not of the same type.

;;; There are versions of this evaluator which apply to different argument types
;;; and environments.
;;;    Number, Integer, Float:         Inference, Procedure, Simulator.
;;;    Text, Datum (text, number): Inference, Procedure.

;;; > (datum, datum)

(def-float-contagion-stack-operator >)

(def-in-line-evaluator (> >-quantity 3) (30 all (number number) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (evaluation-quantity-> register-2 register-3)
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

;; Rewrite the following when evaluation-integers are implemented!!  cpm, 3/3/91.

(def-in-line-evaluator (> >-integer 1) (31 all (integer integer) boolean)
  (if (>f (stack-arg 0) (stack-arg 1))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(def-in-line-evaluator (> >-float 2) (32 all (float float) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (>e (evaluation-float-value register-2)
			   (evaluation-float-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-float register-2)
  (reclaim-evaluation-float register-3))

(def-in-line-evaluator (> >-text) (33 all (text text) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (g2-text-greater-than
			 (evaluation-text-value register-2)
			 (evaluation-text-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-text register-2)
  (reclaim-evaluation-text register-3))


(def-in-line-evaluator (> >-datum 4) 
		       (34 (inference procedure) (datum datum) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (stack-eval>function register-2 register-3 top-of-stack))
  (reclaim-evaluation-value register-2)
  (reclaim-evaluation-value register-3))


(def-stack-error invalid-argument-type-eval-error
       (stack-arg evaluator-name top-of-stack)
  (if (evaluation-value-p stack-arg)
      "The ~a operator received the invalid argument ~NV."
      "The ~a operator received the invalid argument ~A.")
  evaluator-name stack-arg)

;; The evaluation value arguments should be on the stack and will be reclaimed
;; within the call to stack error.

(def-stack-error argument-mismatch-eval-error
       (stack-arg-1 stack-arg-2 evaluator-name top-of-stack)
  "In a ~a expression, the values ~NE and ~NE are not of the same type."
  evaluator-name stack-arg-1 stack-arg-2)

;;; The function `STACK-EVAL>FUNCTION' is used in the definition of the >
;;; in-line evaluator.  This function accepts two evaluation-value stack
;;; arguments and returns an evaluation boolean.  The stack arguments are
;;; only reclaimed if there is a stack error.

;; This function could to be rewritten for the SETS module to be an
;; evaluation-value operation.  It should then optionally (?) not signal a
;; stack-error for mismatched or incorrect data types.  cpm, 6/24/91

(defun stack-eval>function (stack-arg-1 stack-arg-2 top-of-stack)
  (cond ((evaluation-quantity-p stack-arg-1)
	 (if (evaluation-quantity-p stack-arg-2)
	     (if (evaluation-quantity-> stack-arg-1 stack-arg-2)
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '> top-of-stack)))
	((text-string-p stack-arg-1)
	 ;; Text strings are compared as g2-text since they may contain complex
	 ;; G2 characters, e.g., international characters.
	 (if (text-string-p stack-arg-2)
	     (if (g2-text-greater-than
		   (evaluation-text-value stack-arg-1)
		   (evaluation-text-value stack-arg-2))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '> top-of-stack)))
	((evaluation-truth-value-p stack-arg-1)
	 (if (evaluation-truth-value-p stack-arg-2)
	     (if (> (evaluation-truth-value-value stack-arg-1)
		    (evaluation-truth-value-value stack-arg-2))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '> top-of-stack)))
	(t (invalid-argument-type-eval-error stack-arg-1 '> top-of-stack))))



;;; The `>= stack evaluator' accept two arguments and returns a boolean.  If the
;;; first argument is greater than or equal to the second argument, truth is
;;; returned.  Otherwise, falsity is returned.  It is an error if the arguments
;;; are not of the same type.

;;; There are versions of this evaluator which apply to different argument types
;;; and environments.
;;;    Number, Integer, Float:         Inference, Procedure, Simulator.
;;;    Text, Datum (text, number): Inference, Procedure.

;;; >= (datum, datum)

(def-float-contagion-stack-operator >=)

(def-in-line-evaluator (>= >=-quantity 3) (35 all (number number) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (evaluation-quantity->= register-2 register-3)
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

;; Rewrite the following when evaluation-integers are implemented!!  cpm, 3/3/91

(def-in-line-evaluator (>= >=-integer 1) (36 all (integer integer) boolean)
  (if (>=f (stack-arg 0) (stack-arg 1))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(def-in-line-evaluator (>= >=-float 2) (37 all (float float) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (>=e (evaluation-float-value register-2)
			    (evaluation-float-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

(def-in-line-evaluator (>= >=-text) (38 all (text text) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (g2-text-not-less-than
			 (evaluation-text-value register-2)
			 (evaluation-text-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-text register-2)
  (reclaim-evaluation-text register-3))


(def-in-line-evaluator (>= >=-datum 4)
		       (39 (inference procedure) (datum datum) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (stack-eval>=function register-2 register-3 top-of-stack))
  (reclaim-evaluation-value register-2)
  (reclaim-evaluation-value register-3))


;;; The function `STACK-EVAL>=FUNCTION' is used in the definition of the >=
;;; in-line evaluator.  This function accepts two evaluation-value stack
;;; arguments and returns an evaluation boolean.  The stack arguments are only
;;; reclaimed if there is a stack error.

;; This function could to be rewritten for the SETS module to be an
;; evaluation-value operation.  It should then optionally (?) not signal a
;; stack-error for mismatched or incorrect data types.  cpm, 6/24/91

(defun stack-eval>=function (stack-arg-1 stack-arg-2 top-of-stack)
  (cond ((evaluation-quantity-p stack-arg-1)
	 (if (evaluation-quantity-p stack-arg-2)
	     (if (evaluation-quantity->= stack-arg-1 stack-arg-2)
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '>= top-of-stack)))
	((text-string-p stack-arg-1)
	 ;; Text strings are compared as g2-text, since they may contain complex
	 ;; G2 characters, e.g., international characters.
	 (if (text-string-p stack-arg-2)
	     (if (g2-text-not-less-than
		   (evaluation-text-value stack-arg-1)
		   (evaluation-text-value stack-arg-2))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '>= top-of-stack)))
	((evaluation-truth-value-p stack-arg-1)
	 (if (evaluation-truth-value-p stack-arg-2)
	     (if (>= (evaluation-truth-value-value stack-arg-1)
		     (evaluation-truth-value-value stack-arg-2))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '>= top-of-stack)))
	(t (invalid-argument-type-eval-error stack-arg-1 '>= top-of-stack))))



;;; The `< stack evaluator' accept two arguments and returns a boolean.  If the
;;; first argument is strictly less than the second argument, truth is returned.
;;; Otherwise, falsity is returned.  It is an error if the arguments are not of
;;; the same type.

;;; There are versions of this evaluator which apply to different argument types
;;; and environments.
;;;    Number, Integer, Float:         Inference, Procedure, Simulator.
;;;    Text, Datum (text, number): Inference, Procedure.

;;; < (datum, datum)

(def-float-contagion-stack-operator <)

(def-in-line-evaluator (< <-quantity 3) (40 all (number number) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (evaluation-quantity-< register-2 register-3)
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

;; Rewrite the following when evaluation-integers are implemented!!  cpm, 3/3/91.

(def-in-line-evaluator (< <-integer 1) (41 all (integer integer) boolean)
  (if (<f (stack-arg 0) (stack-arg 1))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(def-in-line-evaluator (< <-float 2) (42 all (float float) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (<e (evaluation-float-value register-2)
			   (evaluation-float-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-float register-2)
  (reclaim-evaluation-float register-3))

(def-in-line-evaluator (< <-text) 
		       (43 (inference procedure) (text text) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (g2-text-less-than
			 (evaluation-text-value register-2)
			 (evaluation-text-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-text register-2)
  (reclaim-evaluation-text register-3))


(def-in-line-evaluator (< <-datum 4)
		       (44 (inference procedure) (datum datum) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (stack-eval<function register-2 register-3 top-of-stack))
  (reclaim-evaluation-value register-2)
  (reclaim-evaluation-value register-3))


;;; The function `STACK-EVAL<FUNCTION' is used in the definition of the <
;;; in-line evaluator.  This function accepts two evaluation-value stack
;;; arguments and returns an evaluation boolean.  The stack arguments are only
;;; reclaimed if there is a stack error.

;; This function could to be rewritten for the SETS module to be an
;; evaluation-value operation.  It should then optionally (?) not signal a
;; stack-error for mismatched or incorrect data types.  cpm, 6/24/91

(defun stack-eval<function (stack-arg-1 stack-arg-2 top-of-stack)
  (cond ((evaluation-quantity-p stack-arg-1)
	 (if (evaluation-quantity-p stack-arg-2)
	     (if (evaluation-quantity-< stack-arg-1 stack-arg-2)
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '< top-of-stack)))
	((text-string-p stack-arg-1)
	 ;; Text strings are compared as g2-text, since they may contain complex
	 ;; G2 characters, e.g., international characters.
	 (if (text-string-p stack-arg-2)
	     (if (g2-text-less-than
		   (evaluation-text-value stack-arg-1)
		   (evaluation-text-value stack-arg-2))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '< top-of-stack)))
	((evaluation-truth-value-p stack-arg-1)
	 (if (evaluation-truth-value-p stack-arg-2)
	     (if (< (evaluation-truth-value-value stack-arg-1)
		    (evaluation-truth-value-value stack-arg-2))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '< top-of-stack)))
	(t (invalid-argument-type-eval-error stack-arg-1 '< top-of-stack))))



;;; The `<= stack evaluator' accept two arguments and returns a boolean.  If
;;; the first argument is less than or equal to the second argument, truth is
;;; returned.  Otherwise, falsity is returned.  It is an error if the arguments
;;; are not of the same type.

;;; There are versions of this evaluator which apply to different argument types
;;; and environments.
;;;    Number, Integer, Float:         Inference, Procedure, Simulator.
;;;    Text, Datum (text, number): Inference, Procedure.

;;; <= (datum, datum)

(def-float-contagion-stack-operator <=)

(def-in-line-evaluator (<= <=-quantity 3) (45 all (number number) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (evaluation-quantity-<= register-2 register-3)
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

;; Rewrite the following when evaluation-integers are implemented!!  cpm, 3/3/91.

(def-in-line-evaluator (<= <=-integer 1) (46 all (integer integer) boolean)
  (if (<=f (stack-arg 0) (stack-arg 1))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(def-in-line-evaluator (<= <=-float 2) (47 all (float float) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (<=e (evaluation-float-value register-2)
			    (evaluation-float-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-float register-2)
  (reclaim-evaluation-float register-3))


(def-in-line-evaluator (<= <=-text) (48 all (text text) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (if (g2-text-not-greater-than
			 (evaluation-text-value register-2)
			 (evaluation-text-value register-3))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-text register-2)
  (reclaim-evaluation-text register-3))


(def-in-line-evaluator (<= <=-datum 4)
		       (49 (inference procedure) (datum datum) boolean t)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1 (stack-eval<=function  register-2 register-3 top-of-stack))
  (reclaim-evaluation-value register-2)
  (reclaim-evaluation-value register-3))


;;; The function `STACK-EVAL<=FUNCTION' is used in the definition of the <=
;;; in-line evaluator.  This function accepts two evaluation-value stack
;;; arguments and returns an evaluation boolean.  The stack arguments are only
;;; reclaimed if there is a stack error.

;; This function could to be rewritten for the SETS module to be an
;; evaluation-value operation.  It should then optionally (?) not signal a
;; stack-error for mismatched or incorrect data types.  cpm, 6/24/91

(defun stack-eval<=function (stack-arg-1 stack-arg-2 top-of-stack)
  (cond ((evaluation-quantity-p stack-arg-1)
	 (if (evaluation-quantity-p stack-arg-2)
	     (if (evaluation-quantity-<= stack-arg-1 stack-arg-2)
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '<= top-of-stack)))
	((text-string-p stack-arg-1)
	 ;; Text strings are compared as g2-text, since they may contain complex
	 ;; G2 characters, e.g., international characters.
	 (if (text-string-p stack-arg-2)
	     (if (g2-text-not-greater-than
		   (evaluation-text-value stack-arg-1)
		   (evaluation-text-value stack-arg-2))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '<= top-of-stack)))
	((evaluation-truth-value-p stack-arg-1)
	 (if (evaluation-truth-value-p stack-arg-2)
	     (if (<= (evaluation-truth-value-value stack-arg-1)
		     (evaluation-truth-value-value stack-arg-2))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))
	     (argument-mismatch-eval-error
	       stack-arg-1 stack-arg-2 '<= top-of-stack)))
	(t (invalid-argument-type-eval-error stack-arg-1 '<= top-of-stack))))


(declare-optimizer-stack-instruction is)

;;; The `IS stack evaluator' is a predicate that compares a symbolic-expression
;;; and a symbol for equality.  This operator compares symbolic constants,
;;; variable or parameter values, or implied attributes to a symbolic value.
;;; The first argument is a designation and the second argument is a quoted
;;; symbol.  The values returned are truth or falsity.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.

;;; This evaluator is available in the inference engine and procedures.

(def-special-form-converter is (expression)
  (let ((symbol-expression
	  (convert-expression-to-stack-node-tree (second expression)))
	(symbol-value
	  (convert-expression-to-stack-node-tree (third expression)))
	(is-node (make-stack-node-instruction 'is nil)))
    (setf (stack-node-argument-nodes is-node)
	  (stack-list symbol-expression symbol-value))
    is-node))



;;; The preferred instruction chooser for IS chooses instructions and types on
;;; its arguments, and then sets its own return value.

(def-preferred-instruction-chooser is
  (declare (ignore extra-info))
  (let ((unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(no-item-implies-unknown-allowed?
	  (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	(argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(value-type 'boolean))
    (setf (first argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (first argument-nodes)
	    'item-or-datum))

    (setf (second argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (second argument-nodes) 'symbol))

    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-unknown
	     value-type (or unknown-allowed? no-item-implies-unknown-allowed?)))))



;;; IS is an expiration source node.  It can return unknown if given a variable
;;; that does not have a value or if the designation argument did not return an
;;; item or datum.

(def-expiration-source-operator is)

;;; The stack node instruction emitter for IS emits different
;;; funcalled-instructions depending on whether the stack node can return
;;; unknown.

(def-stack-node-instruction-emitter is
  (declare (ignore extra-info))
  (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (unknown-is-allowed?
	   (type-specification-subtype-p
	     '(unknown-datum) (stack-node-value-type stack-node-instruction))))    
    (emit-stack-node-tree byte-code-stream (first argument-nodes))
    (emit-stack-node-tree byte-code-stream (second argument-nodes))
    (if unknown-is-allowed?
	(call-stack-instruction-emitter funcall-instruction
	  byte-code-stream 'is-and-possibly-unknown)
	(call-stack-instruction-emitter funcall-instruction byte-code-stream 'is))))



;;; Instruction 33, the `IS funcalled stack-instruction' is one of the two
;;; instructions used to implement the evaluator for IS.  The instruction
;;; accepts two arguments, an item or datum and a symbol.  The instruction
;;; compares for equality the value or the value of the implied attribute of the
;;; first argument and the second argument.

;;; There are two versions of this operator.  This version does not return a
;;; value of unknown.  The second version, is-and-possibly-unknown, can return
;;; unknown.

;;; Since this version does not return unknown, the first argument must be a
;;; parameter, symbol, or an implied attribute parameter or symbol.

;;; added support for attribute-class? (multiple-inheritance) -rdf, 2/17/94

(def-funcalled-instruction is (33 (inference procedure) 2 1 nil pprint-is-instruction)
  (let* ((item-or-datum-arg (stack-arg 0))
	 (datum-arg? (when (evaluation-datum-p item-or-datum-arg)
		       item-or-datum-arg))
	 (symbolic-value-arg (stack-arg 1))
	 (symbolic-value (evaluation-symbol-symbol symbolic-value-arg))
	 (attribute-class? nil)
	 (implied-attribute-name? nil)
	 (implied-attribute-role? nil)
	 
	 result?)
    

    (cond
      (datum-arg?
       (cond ((evaluation-symbol-p datum-arg?)
	      ;; Don't need to test the type of the symbolic-value-arg.
	      (cond ((eq (evaluation-symbol-symbol datum-arg?)
			 symbolic-value)
		     (setq result? t))
		    (t (setq result? nil))))
	     (t (stack-error
		  top-of-stack
		  "The first value, ~NV, in the IS expression is not a symbol."
		  datum-arg?))))
      (t
       (when (not datum-arg?)
	 (multiple-value-setq
	     (implied-attribute-name? attribute-class?)
	   (implied-attribute-of-class-throwing-errors
	     (class item-or-datum-arg) symbolic-value top-of-stack)))
       (cond
	 (implied-attribute-name?
	  (cond (attribute-class?

		 ;; need to reclaim this now
		 (setq implied-attribute-role?
		       (eval-list 'class-qualified-name
				  attribute-class?
				  implied-attribute-name?)))
		(t
		 (setq implied-attribute-role? implied-attribute-name?)))

	  (multiple-value-bind (attribute-value role-expiration? extra-objects?)
	      (serve-unique-item-or-evaluation-value-of-role
		implied-attribute-role? item-or-datum-arg nil t)
	    (cond
	      ((null role-expiration?)
					; Are there other error
					; cases to warn about??
					; cpm, 5/6/91
	       (if extra-objects?
		   (stack-error
		     top-of-stack
		     "The first argument to IS, the ~a of ~NF, denoted ~
                          more than one value.  IS requires one value only."
		     implied-attribute-name? item-or-datum-arg)
		   (stack-error
		     top-of-stack
		     "The first argument to IS, the ~a of ~NF, held no value."
		     implied-attribute-name? item-or-datum-arg)))

	      ((evaluation-symbol-p attribute-value)
	       (if (eq (evaluation-symbol-symbol attribute-value)
		       symbolic-value)
		   (setq result? t)
		   (setq result? nil))
	       (reclaim-evaluation-symbol attribute-value))

	      ((evaluation-value-p attribute-value)
	       (write-stack-error
		   top-of-stack
		 (tformat
		   "The first argument to IS, ~NA, which was the ~a ~
                       of ~NF, was not a symbol."
		   attribute-value
		   implied-attribute-name? item-or-datum-arg)
		 (reclaim-evaluation-value attribute-value)))
	      ((parameter-p attribute-value)
	       (if (eq (type-specification-of-variable-or-parameter-value
			 attribute-value)
		       'symbol)
		   (let* ((managed-current-value
			    (current-value-of-variable-or-parameter
			      attribute-value))
			  (current-value
			    (extract-cached-number-or-value
			      managed-current-value)))
		     (if (eq current-value symbolic-value)
			 (setq result? t)
			 (setq result? nil)))
		   (stack-error
		     top-of-stack
		     "The first argument to IS, ~NF, is not a symbol."
		     item-or-datum-arg)))
	      (t
	       (stack-error
		 top-of-stack
		 "The first argument to IS, ~NF, is not a parameter."
		 attribute-value))))
	  (when (consp implied-attribute-role?)
	    (reclaim-eval-list implied-attribute-role?)
	    (setq implied-attribute-role? nil))
	  )
	 ((parameter-p item-or-datum-arg)
	  (if (eq (type-specification-of-variable-or-parameter-value item-or-datum-arg)
		  'symbol)
	      (let* ((managed-current-value
		       (current-value-of-variable-or-parameter item-or-datum-arg))
		     (current-value
		       (extract-cached-number-or-value managed-current-value)))
		(if (eq current-value symbolic-value)
		    (setq result? t)
		    (setq result? nil)))
	      (stack-error
		top-of-stack
		"The first argument to IS, ~NF, is not a symbol."
		item-or-datum-arg)))
	 (t
	  (stack-error
	    top-of-stack
	    "The first argument to IS, ~NF, is an item which is neither a ~
          parameter or an attribute with a possible symbolic value of ~a."
	    item-or-datum-arg symbolic-value)))))

    (reclaim-if-evaluation-value item-or-datum-arg)
    (reclaim-evaluation-value symbolic-value-arg)
    (decff top-of-stack 1)
    (setf (svref local-stack top-of-stack)
	  (if result?
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity)))
    nil))



;;; Instruction 34, the `IS-AND-POSSIBLY-UNKNOWN' funcalled stack-instruction'
;;; is one of the two instructions used to implement the evaluator for IS.  The
;;; instruction accepts two arguments, an item or datum and a symbol.  The
;;; instruction compares for equality the value or the value of the implied
;;; attribute of the first argument and the second argument.

;;; There are two versions of this operator.  The first version, IS, does not
;;; return a value of unknown.  This version, IS-AND-POSSIBLY-UNKNOWN, can
;;; return unknown.

;; We should do the following optimization??  This is a functionality change
;; from G2 version 2.
;;
;; The EVAL version of IS would call get-current-value before knowing if the
;; variable or parameter could return a symbol.  In the IS
;; funcalled-instruction, get-current-value is not called if a symbol can not be
;; returned.

;;; added support for attribute-class? (multiple-inheritance) -rdf, 2/17/94

(def-funcalled-instruction is-and-possibly-unknown (34 (inference procedure) 2 1 nil
						       pprint-is-and-possibly-unknown-instruction)
  (let* ((item-or-datum-arg (stack-arg 0))
	 (datum-arg? (when (evaluation-value-p item-or-datum-arg)
		     item-or-datum-arg))
	 (symbolic-value-arg (stack-arg 1))
	 (symbolic-value (evaluation-value-value symbolic-value-arg))
	 (attribute-class? nil)
	 (implied-attribute-name? nil)
	 (implied-attribute-role? nil)
	 result?)
     (cond
       ((and datum-arg?
	     (null (evaluation-value-value datum-arg?)))
	;; Unknown value.
	(setq result? nil)
	(setq stack-expiration nil))

       (datum-arg?
	(cond ((evaluation-symbol-p datum-arg?)
	       ;; Don't need to test the type of the symbolic-value-arg since it
	       ;; is a quoted constant.
	       (cond ((eq (evaluation-symbol-symbol datum-arg?) symbolic-value)
		      (setq result? t))
		     (t (setq result? nil))))
	      (t
	       (stack-error
		 top-of-stack
		 "The first value passed to IS, ~NV, was not a symbol."
		 datum-arg?))))

       (t
	(when (not datum-arg?)
	  (multiple-value-setq
	      (implied-attribute-name? attribute-class?)
	    (implied-attribute-of-class-throwing-errors
	      (class item-or-datum-arg) symbolic-value top-of-stack)))
	(cond
	  (implied-attribute-name?
	   (cond (attribute-class?

		  ;; need to reclaim this now
		  (setq implied-attribute-role?
			(eval-list 'class-qualified-name
				   attribute-class?
				   implied-attribute-name?)))
		 (t
		  (setq implied-attribute-role? implied-attribute-name?)))
	   (multiple-value-bind (attribute-value role-expiration? extra-objects?)
	       
	       (serve-unique-item-or-evaluation-value-of-role
		 implied-attribute-role? item-or-datum-arg nil t)
	     (cond
	       ((null role-expiration?)
		(if extra-objects?
		    (stack-error
		      top-of-stack
		      "The first argument to IS, the ~a of ~NF, denoted ~
                           more than one value.  IS requires one value only."
		      implied-attribute-name? item-or-datum-arg)
		    (stack-error
		      top-of-stack
		      "The first argument to IS, the ~a of ~NF, held no value."
		      implied-attribute-name? item-or-datum-arg)))
	       ((evaluation-symbol-p attribute-value)
		(if (eq (evaluation-symbol-symbol attribute-value)
			symbolic-value)
		    (setq result? t)
		    (setq result? nil))
		(reclaim-evaluation-symbol attribute-value))
	       ((evaluation-value-p attribute-value)
		(write-stack-error
		    top-of-stack
		  (tformat
		    "The first argument to IS, ~NA, which was the ~a ~
                        of ~NF, was not a symbol."
		    attribute-value
		    implied-attribute-name? item-or-datum-arg)
		  (reclaim-evaluation-value attribute-value)))
	       ((variable-or-parameter-p attribute-value)
		(let ((value? (get-current-evaluation-value attribute-value nil)))
		  (cond
		    ((null value?)
		     (setq result? nil))
		    ((not (evaluation-symbol-p value?))
		     (stack-error
		       top-of-stack
		       "The first argument to IS, ~NV, which was the value ~
                    of ~NF, was not a symbol."
		       value? item-or-datum-arg))
		    ((not (eq (evaluation-symbol-symbol value?)
			      symbolic-value))
		     (setq result? nil))
		    (t
		     (setq result? t)))
		  (reclaim-if-evaluation-value value?)))
	       (t
		(stack-error
		  top-of-stack
		  "The first argument to IS, ~NF, was not a variable or a parameter."
		  attribute-value))))
	   (when (consp implied-attribute-role?)
	     (reclaim-eval-list implied-attribute-role?)
	     (setq implied-attribute-role? nil)))
	  ((variable-or-parameter-p item-or-datum-arg)
	   (let ((value? (get-current-evaluation-value item-or-datum-arg nil)))
	     (cond
	       ((null value?)
		(setq result? nil))
	       ((not (evaluation-symbol-p value?))
		(stack-error
		  top-of-stack
		  "The first argument to IS, ~NV, which was the value ~
               of ~NF, was not a symbol."
		  value? item-or-datum-arg))
	       ((not (eq (evaluation-symbol-symbol value?)
			 symbolic-value))
		(setq result? nil))
	       (t
		(setq result? t)))
	     (reclaim-if-evaluation-value value?)))
	  (t
	   (stack-error
	     top-of-stack
	     "The first argument to IS, ~NF, was an item which was not a variable ~
          or parameter nor did it have an attribute with a possible symbolic ~
          value of ~a."
	     item-or-datum-arg symbolic-value)))))

     (reclaim-if-evaluation-value item-or-datum-arg)
     (reclaim-evaluation-value symbolic-value-arg)
     (decff top-of-stack 1)
     (setf (svref local-stack top-of-stack)
	   (if result?
	       (make-evaluation-truth-value truth)
	       (make-evaluation-truth-value falsity)))
     nil))




;;; The `IS-NOT stack-evaluator' is a predicate that compares that a
;;; symbolic-expression and a symbol are not equal.  This operator compares
;;; symbolic constants, variable or parameter values, or implied attributes to a
;;; symbolic value.  The first argument is a designation and the second argument
;;; is a quoted symbol.  The values returned are truth or falsity.

;;; This evaluator is available in the inference engine and procedures.

(def-special-form-converter is-not (expression)
  (convert-expression-to-stack-node-tree
    (phrase-list 'not (phrase-cons 'is (cdr expression)))))




;;; The `SAME-AS stack evaluator' and `NOT-SAME-AS stack evaluator' compare two
;;; object references to determine if they refer to the same item.  The
;;; evaluators returns truth or falsity.  These evaluators are available in the
;;; inference engine, procedures, and the simulator.

;; A FUNCTIONALITY CHANGE!!
;; If either item is a temporary-constant:
;; PROC-EVAL, EVAL - returned FALSITY.
;; SIMULATOR - returned nil (which is false to the simulator).
;; STACK-EVAL - signals an error before the evaluator is called.

;;; SAME-AS (item, item)

(def-in-line-evaluator same-as (50 all ((class item) (class item)) boolean t)
  (setq register-1 (if (eq (stack-arg 0) (stack-arg 1))
		       (make-evaluation-truth-value truth)
		       (make-evaluation-truth-value falsity))))


;; A FUNCTIONALITY CHANGE!!
;; If either item is a temporary-constant:
;; PROC-EVAL, EVAL - returned TRUTH.
;; SIMULATOR - returned t (which is true to the simulator).
;; STACK-EVAL - signals an error before the evaluator is called.

;;; NOT-SAME-AS (item, item)

;; Not-same-as now parses to "not same-as".

;; Number 51 is now used by another in-line evaluator.

;(def-in-line-evaluator not-same-as (51 all ((class item) (class item))
;				       truth-value)
;  (setq register-1 (if (neq (stack-arg 0) (stack-arg 1))
;		       (make-evaluation-truth-value truth)
;		       (make-evaluation-truth-value falsity))))




;;; The `AND stack-evaluator' is a special form that takes multiple truth value
;;; arguments and returns a truth-value or boolean.  The result is computed by
;;; returning the minimum value of its arguments.  This evaluator will be
;;; implemented as a stack-node-instruction which emits its own instructions
;;; specifically.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

(def-special-form-converter and (expression)
  (let ((arguments
	  (loop for argument in (cdr expression)
		collect (convert-expression-to-stack-node-tree argument)
		using stack-cons))
	(and-node (make-stack-node-instruction 'and nil)))
    (setf (stack-node-argument-nodes and-node) arguments)
    and-node))


(declare-optimizer-stack-instruction and)

;;; The preferred instruction chooser for AND chooses instructions and types on
;;; its arguments, and then sets its own return value, depending on whether any
;;; of its arguments can return unknown and whether all the arguments are
;;; boolean values.

(def-preferred-instruction-chooser and
  (declare (ignore extra-info))
  (let ((unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(no-item-implies-unknown-allowed?
	  (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	(argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(unknown-argument? nil)
	(all-boolean-arguments? t)
	(type-spec 'truth-value))
    (setq type-spec
	  (maybe-add-no-item-implies-unknown
	    (maybe-add-unknown
	      type-spec unknown-allowed?)
	    no-item-implies-unknown-allowed?))
    (loop for argument-node-cons on argument-nodes
	  do
      (setf (car argument-node-cons)
	    (choose-stack-node-instructions-and-types
	      (car argument-node-cons)
	      type-spec))
      (when (type-specification-subtype-p
	      '(unknown-datum)
	      (stack-node-value-type (car argument-node-cons)))
	(setq unknown-argument? t))
      (unless (and (type-specification-subtype-p
		     'boolean
		     (stack-node-value-type (car argument-node-cons)))
		   (not (type-specification-subtype-p
			  'truth-value
			  (stack-node-value-type (car argument-node-cons)))))
	(setq all-boolean-arguments? nil)))
    (cond (unknown-argument?
	   (setf (stack-node-value-type stack-node-instruction)
		 (if all-boolean-arguments?
		     '(or boolean (unknown-datum))
		     '(or truth-value (unknown-datum))))
	   (unless (stack-node-instruction-extra-info stack-node-instruction)
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   (phrase-list (generate-new-stack-frame-var-spot 'datum)
				(generate-new-stack-frame-var-spot 'datum)))))
	  (t
	   (setf (stack-node-value-type stack-node-instruction)
		 (if all-boolean-arguments?
		     'boolean
		     'truth-value))
	   (setf (stack-node-instruction-extra-info stack-node-instruction)
		 nil)))))



;;; The stack node instruction emitter for AND emits in one of two ways,
;;; depending upon whether or not any of its argument nodes can return unknown.
;;; If the arguments cannot, then this instruction need not collect expirations
;;; from its arguments, or check at all whether or not they are known.

(def-expiration-special-form and)

(def-stack-node-instruction-emitter and
  (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (expiration-var? (first extra-info))
	 (cached-global-expiration-var? (second extra-info))
	 (end-of-and-tag (generate-new-goto-tag)))
    (cond
      ((not expiration-var?)
       (emit-stack-node-tree byte-code-stream (car argument-nodes))
       (loop for node in (cdr argument-nodes)
	     do
	 (emit-instruction-byte-code
	   byte-code-stream 'push-copy-of-top-of-stack)
	 (call-stack-instruction-emitter branch-long-if-false
	   byte-code-stream end-of-and-tag)
	 (emit-stack-node-tree byte-code-stream node)
	 (emit-instruction-byte-code byte-code-stream 'fuzzy-and))
       (register-tag-in-byte-code-stream
	 byte-code-stream end-of-and-tag))
      (t
       (let ((false-tag (generate-new-goto-tag))
	     (first-known-tag (generate-new-goto-tag)))
	 ;; Cache the global expiration, and reset it to never.
	 (emit-instruction-byte-code byte-code-stream 'push-expiration)
	 (call-stack-instruction-emitter pop-into-surrounding-local-var
	   byte-code-stream cached-global-expiration-var?)
	 (emit-instruction-byte-code byte-code-stream 'reset-expiration)
	 ;; Push the value of the first argument onto the stack.
	 (emit-stack-node-tree byte-code-stream (car argument-nodes))
	 (call-stack-instruction-emitter branch-long-if-known byte-code-stream first-known-tag)
	 (emit-instruction-byte-code byte-code-stream 'pop)
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value truth))
	 (register-tag-in-byte-code-stream
	   byte-code-stream first-known-tag)
	 (emit-instruction-byte-code
	   byte-code-stream 'push-copy-of-top-of-stack)
	 (call-stack-instruction-emitter branch-long-if-false
	   byte-code-stream false-tag)
	 (loop for argument-node in (cdr argument-nodes)
	       for argument-known-tag = (generate-new-goto-tag)
	       do
	   (emit-instruction-byte-code byte-code-stream 'push-expiration)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream expiration-var?)
	   (emit-instruction-byte-code byte-code-stream 'reset-expiration)

	   (emit-stack-node-tree byte-code-stream argument-node)

	   (call-stack-instruction-emitter branch-long-if-known
	     byte-code-stream argument-known-tag)
	   (emit-instruction-byte-code byte-code-stream 'pop)
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value truth))
	   (register-tag-in-byte-code-stream
	     byte-code-stream argument-known-tag)
	   (emit-instruction-byte-code byte-code-stream 'fuzzy-and)
	   (emit-instruction-byte-code
	     byte-code-stream 'push-copy-of-top-of-stack)
	   (call-stack-instruction-emitter branch-long-if-false
	     byte-code-stream false-tag)

	   (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	     byte-code-stream expiration-var?)
	   (emit-instruction-byte-code byte-code-stream 'minimize-expiration))
	   
	 (register-tag-in-byte-code-stream
	   byte-code-stream false-tag)
	 (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	   byte-code-stream cached-global-expiration-var?)
	 (emit-instruction-byte-code byte-code-stream 'minimize-expiration))))))




;;; The `OR stack-evaluator' is a special form that takes multiple truth value
;;; arguments and returns a truth-value or boolean.  The result is computed by
;;; returning the maximum truth value of its arguments.  This evaluator will be
;;; implemented as a stack-node-instruction which emits its own instructions
;;; specifically.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

(def-special-form-converter or (expression)
  (let ((arguments
	  (loop for argument in (cdr expression)
		collect (convert-expression-to-stack-node-tree argument)
		using stack-cons))
	(or-node (make-stack-node-instruction 'or nil)))
    (setf (stack-node-argument-nodes or-node) arguments)
    or-node))



;;; The preferred instruction chooser for OR chooses instructions and types on
;;; its arguments, and then sets its own return value, depending on whether any
;;; of its arguments can return unknown or whether they all return boolean.

(def-preferred-instruction-chooser or
  (declare (ignore extra-info))
  (let ((unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	(unknown-argument? nil)
	(all-boolean-arguments? t)
	(type-spec 'truth-value))
        (setq type-spec
	  (maybe-add-no-item-implies-unknown
	    (maybe-add-unknown
	      type-spec unknown-allowed?)
	    no-item-implies-unknown-allowed?))
    (loop for argument-node-cons on argument-nodes
	  do
      (setf (car argument-node-cons)
	    (choose-stack-node-instructions-and-types
	      (car argument-node-cons)
	      type-spec))
      (when (type-specification-subtype-p
	      '(unknown-datum)
	      (stack-node-value-type (car argument-node-cons)))
	(setq unknown-argument? t))
      (unless (and (type-specification-subtype-p
		     'boolean
		     (stack-node-value-type (car argument-node-cons)))
		   (not (type-specification-subtype-p
			  'truth-value
			  (stack-node-value-type (car argument-node-cons)))))
	(setq all-boolean-arguments? nil)))
    (cond (unknown-argument?
	   (setf (stack-node-value-type stack-node-instruction)
		 (if all-boolean-arguments?
		     '(or boolean (unknown-datum))
		     '(or truth-value (unknown-datum))))
	   (unless (stack-node-instruction-extra-info stack-node-instruction)
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   (phrase-list (generate-new-stack-frame-var-spot 'datum)
				(generate-new-stack-frame-var-spot 'datum)))))
	  (t
	   (setf (stack-node-value-type stack-node-instruction)
		 (if all-boolean-arguments?
		     'boolean
		     'truth-value))
	   (setf (stack-node-instruction-extra-info stack-node-instruction)
		 nil)))))



;;; The stack node instruction emitter for OR emits in one of two ways,
;;; depending upon whether or not any of its argument nodes can return unknown.
;;; If the arguments cannot, then this instruction need not collect expirations
;;; from its arguments, or check at all whether or not they are known.

;; Is this correct way to handle expiration for OR??  cpm, 4/30/91

(def-expiration-special-form or)

(declare-instruction-for-optimizer
  'or
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    or-like-flow))

(def-stack-node-instruction-emitter or
  (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (expiration-var? (first extra-info))
	 (cached-global-expiration-var? (second extra-info))
	 (end-of-or-tag (generate-new-goto-tag)))
    (cond
      ((not expiration-var?)
       (emit-stack-node-tree byte-code-stream (car argument-nodes))
       (loop for node in (cdr argument-nodes)
	     do
	 (emit-instruction-byte-code
	   byte-code-stream 'push-copy-of-top-of-stack)
	 (call-stack-instruction-emitter branch-long-if-true byte-code-stream end-of-or-tag)
	 (emit-stack-node-tree byte-code-stream node)
	 (emit-instruction-byte-code byte-code-stream 'fuzzy-or))
       (register-tag-in-byte-code-stream byte-code-stream end-of-or-tag))
      (t
       (let ((true-tag (generate-new-goto-tag))
	     (first-known-tag (generate-new-goto-tag)))
	 ;; Cache the global expiration, and reset it to never.
	 (emit-instruction-byte-code byte-code-stream 'push-expiration)
	 (call-stack-instruction-emitter pop-into-surrounding-local-var
	   byte-code-stream cached-global-expiration-var?)
	 (emit-instruction-byte-code byte-code-stream 'reset-expiration)
	 ;; Push the value of the first argument onto the stack.
	 (emit-stack-node-tree byte-code-stream (car argument-nodes))
	 (call-stack-instruction-emitter branch-long-if-known byte-code-stream first-known-tag)
	 (emit-instruction-byte-code byte-code-stream 'pop)
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value falsity))
	 (register-tag-in-byte-code-stream byte-code-stream first-known-tag)
	 (emit-instruction-byte-code
           byte-code-stream 'push-copy-of-top-of-stack)
         (call-stack-instruction-emitter branch-long-if-true byte-code-stream true-tag)
	 (loop for argument-node in (cdr argument-nodes)
	       for argument-known-tag = (generate-new-goto-tag)
	       do
	   (emit-instruction-byte-code byte-code-stream 'push-expiration)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream expiration-var?)
	   (emit-instruction-byte-code byte-code-stream 'reset-expiration)

	   (emit-stack-node-tree byte-code-stream argument-node)

	   (call-stack-instruction-emitter branch-long-if-known
	     byte-code-stream argument-known-tag)
	   (emit-instruction-byte-code byte-code-stream 'pop)
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value falsity))
	   (register-tag-in-byte-code-stream
	     byte-code-stream argument-known-tag)
	   (emit-instruction-byte-code byte-code-stream 'fuzzy-or)

	   (emit-instruction-byte-code
	     byte-code-stream 'push-copy-of-top-of-stack)
	   (call-stack-instruction-emitter branch-long-if-true byte-code-stream true-tag)

	   (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	     byte-code-stream expiration-var?)
	   (emit-instruction-byte-code byte-code-stream 'minimize-expiration))
	   
	 (register-tag-in-byte-code-stream byte-code-stream true-tag)
	 (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	   byte-code-stream cached-global-expiration-var?)
	 (emit-instruction-byte-code byte-code-stream 'minimize-expiration))))))




;;; The `NOT stack-evaluator' accepts one truth-value argument and returns the
;;; truth-value result of "fuzzy not" of the argument.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;; "Not" for the SIMULATOR was implemented as "(not arg)", where arg is a
;; simulator logical value of t or nil!!

;;; NOT (truth-value)

;(def-in-line-evaluator not (52 all (truth-value) truth-value t)
;  (setq register-2 (stack-arg 0))
;  (setq register-1 (evaluation-truth-value-not register-2)))

;; Note that the evaluator has been replaced with a stack-node-instruction.
;; This is because other emitter facilities need access to a NOT instruction,
;; and evaluators do not have emitters other than those in the expression
;; compiler itself.  So, even though NOT doesn't have to be handled as an
;; instruction, it is so that we don't duplicate an instruction with an
;; evaluator.  -jra & cpm 5/2/91

(def-special-form-converter not (expression)
  (let ((new-node (make-stack-node-instruction 'not nil)))
    (setf (stack-node-argument-nodes new-node)
	  (stack-list (convert-expression-to-stack-node-tree
			(second expression))))
    new-node))

(declare-instruction-for-optimizer
  'not
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles))

(def-preferred-instruction-chooser not
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(no-item-implies-unknown-allowed?
	  (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	(unknown-allowed? (type-specification-subtype-p
			    '(unknown-datum) required-type))
	(type-spec 'truth-value))
    (setq type-spec
	  (maybe-add-no-item-implies-unknown
	    (maybe-add-unknown
	      type-spec unknown-allowed?)
	    no-item-implies-unknown-allowed?))
    (setf (car argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (car argument-nodes)
	    (if unknown-allowed?
		'(or truth-value (unknown-datum))
		'truth-value)))
    (setf (stack-node-value-type stack-node-instruction)
	  (stack-node-value-type (car argument-nodes)))))

(def-stack-node-instruction-emitter not
  (declare (ignore extra-info))
  (emit-stack-node-tree
    byte-code-stream
    (first (stack-node-argument-nodes stack-node-instruction)))
  (emit-instruction-byte-code byte-code-stream 'not))






;;;; Logical Expression, Fuzzy Truth Value Evaluators



(def-stack-error negative-fuzzy-band-eval-error (band-value top-of-stack)
  ;; Fuzzy band arg is < 0 error.
  "The fuzzy comparator band value ~a is less than zero."
  (if (evaluation-value-p band-value)
      (evaluation-value-value band-value)
      band-value))

;;; Fuzzy truth values indicate a degree of certainty in the truth of something.
;;; Truth values can range from -1 to +1, where -1 indicates complete certainty
;;; that something is false and +1 indicates complete certainty that something
;;; is true.  Examples of fuzzy truth values are .7 true, .3 true, and -.2 true.
;;; Fuzzy truth values are assigned to expressions with a fuzzy truth band, for
;;; example, "if flow-20 > 50 gpm (+-5 gpm) then ...".  Here, (+-5 gpm)
;;; describes a band of fuzzy truth values that range from-1 to +1 as the value
;;; of flow-20 ranges from 50 - 5 gpm to 50 + 5 gpm.

;; Do we need number, float, and integer versions of the fuzzy operators??  Is
;; the band-value a float, integer, or number??

;(def-substitution-macro stack-eval-fuzzy-<-macro 
;			(value1 value2 band-value top-of-stack)
;  (cond ((> band-value *smallest-divisor*)
;	 (let ((low-band (- value2 band-value))
;	       (high-band (+ value2 band-value)))
;	   (cond ((<= value1 low-band)
;		  truth)
;		 ((>= value1 high-band)
;		  falsity)
;		 (t (-f (round (/ (* (- high-band value1) truth) band-value))
;			truth)))))
;	((< band-value 0)
;	 (negative-fuzzy-band-eval-error band-value top-of-stack))
;	((< value1 value2) truth)
;	(t falsity)))

(defmacro stack-eval-fuzzy-<-macro 
	  (value1 value2 band-value top-of-stack)
  (let ((value1-arg (gensym))
	(value2-arg (gensym))
	(band-value-arg (gensym))
	(value1-float (gensym))
	(value2-float (gensym))
	(band-value-float (gensym)))
    `(let* ((,value1-arg ,value1)
	    (,value2-arg ,value2)
	    (,band-value-arg ,band-value)
	    (,value1-float
	     (if (fixnump ,value1-arg)
		 (coerce-fixnum-to-gensym-float ,value1-arg)
		 ,value1-arg))
	    (,value2-float
	     (if (fixnump ,value2-arg)
		 (coerce-fixnum-to-gensym-float ,value2-arg)
		 ,value2-arg))
	    (,band-value-float
	     (if (fixnump ,band-value-arg)
		 (coerce-fixnum-to-gensym-float ,band-value-arg)
		 ,band-value-arg)))
       (declare (type gensym-float ,value1-float ,value2-float ,band-value-float))
       (cond ((>e ,band-value-float 0.0)
	      (let ((low-band-float (-e ,value2-float ,band-value-float))
		    (high-band-float (+e ,value2-float ,band-value-float)))
		(declare (type gensym-float low-band-float high-band-float))
		(cond ((<=e ,value1-float low-band-float)
		       truth)
		      ((<e ,value1-float high-band-float)
		       (-f (round
			     (/e (*e (-e high-band-float ,value1-float)
				     (coerce-fixnum-to-gensym-float truth))
				 ,band-value-float))
			   truth))
		      (t falsity))))
	     ((<e ,band-value-float 0.0)
	      (negative-fuzzy-band-eval-error band-value ,top-of-stack))
	     ((<e ,value1-float ,value2-float) truth)
	     (t falsity)))))



;;; The `FUZZY-< stack-evaluator' is a "less than" fuzzy comparitor of numeric
;;; values.  It accepts three arguments: two quantities and a band value.  It
;;; returns a fuzzy truth value.  This evaluator is available in the inference
;;; engine and procedures.

(def-funcalled-evaluator fuzzy-< (value1 value2 band-value)
			 (2 (inference procedure)
			    (number number number) truth-value
			    funcall-eval-type-3-arg
			    nil pprint-fuzzy-<-evaluator)
  (let ((quantity-value1 (evaluation-quantity-value value1))
	(quantity-value2 (evaluation-quantity-value value2))
	(band-value-value (evaluation-quantity-value band-value))
	(result-value nil))
    (setq result-value
	  (stack-eval-fuzzy-<-macro
	    quantity-value1 quantity-value2 band-value-value
	    cached-top-of-stack))
    (reclaim-evaluation-quantity value1)
    (reclaim-evaluation-quantity value2)
    (reclaim-evaluation-quantity band-value)
    (make-evaluation-truth-value result-value)))


;;; The `FUZZY-> stack-evaluator' is a "greater than" fuzzy comparitor of
;;; numeric values.  It accepts three arguments: two quantities and a band
;;; value.  It returns a fuzzy truth value.  This evaluator is only available in
;;; the inference engine and procedures.

(def-funcalled-evaluator fuzzy-> (value1 value2 band-value)
			 (3 (inference procedure)
			    (number number number) truth-value
			    funcall-eval-type-3-arg
			    nil pprint-fuzzy->-evaluator)
  (let ((quantity-value1 (evaluation-quantity-value value1))
	(quantity-value2 (evaluation-quantity-value value2))
	(band-value-value (evaluation-quantity-value band-value))
	(result-value nil))
    (setq result-value
	  (-f (stack-eval-fuzzy-<-macro
		quantity-value1 quantity-value2 band-value-value
		cached-top-of-stack)))
    (reclaim-evaluation-quantity value1)
    (reclaim-evaluation-quantity value2)
    (reclaim-evaluation-quantity band-value)
    (make-evaluation-truth-value result-value)))


;(def-substitution-macro stack-eval-fuzzy-=-macro 
;			(value1 value2 band-value top-of-stack)
;  (cond ((> band-value *smallest-divisor*)
;	 (let ((difference (abs (- value1 value2))))
;	   (cond ((>= difference band-value)
;		  falsity)
;		 (t (-f truth (round (* 2 truth difference) band-value))))))
;	((< band-value 0)
;	 (negative-fuzzy-band-eval-error band-value top-of-stack))
;	((= value1 value2) truth)
;	(t falsity)))


(defmacro stack-eval-fuzzy-=-macro
	  (value1 value2 band-value top-of-stack)
  (let ((value1-arg (gensym))
	(value2-arg (gensym))
	(band-value-arg (gensym))
	(value1-float (gensym))
	(value2-float (gensym))
	(band-value-float (gensym)))
    `(let* ((,value1-arg ,value1)
	    (,value2-arg ,value2)
	    (,band-value-arg ,band-value)
	    (,value1-float
	    (if (fixnump ,value1-arg)
		(coerce-fixnum-to-gensym-float ,value1-arg)
		,value1-arg))
	   (,value2-float
	    (if (fixnump ,value2-arg)
		(coerce-fixnum-to-gensym-float ,value2-arg)
		,value2-arg))
	   (,band-value-float
	    (if (fixnump ,band-value-arg)
		(coerce-fixnum-to-gensym-float ,band-value-arg)
		,band-value-arg)))
       (declare (type gensym-float ,value1-float ,value2-float ,band-value-float))
       (cond ((>e ,band-value-float 0.0)
	      (let ((difference-float (abse (-e ,value1-float ,value2-float))))
		(declare (type gensym-float difference-float))
		(cond ((<e difference-float ,band-value-float)
		       (-f truth
			   (round
			     (/e (*e 2.0 (coerce-fixnum-to-gensym-float truth)
				     difference-float)
				 ,band-value-float))))
		      (t falsity))))
	     ((<e ,band-value-float 0.0)
	      (negative-fuzzy-band-eval-error band-value ,top-of-stack))
	     ((=e ,value1-float ,value2-float) truth)
	     (t falsity)))))



;;; The `FUZZY-= stack-evaluator' is an "equal" fuzzy comparitor of numeric
;;; values.  It accepts three arguments: two quantities and a band value.  It
;;; returns a fuzzy truth value.  This evaluator is only available in the
;;; inference engine and procedures.

(def-funcalled-evaluator fuzzy-= (value1 value2 band-value)
			 (4 (inference procedure)
			    (number number number) truth-value
			    funcall-eval-type-3-arg
			    nil pprint-fuzzy-=-evaluator)
  (let ((quantity-value1 (evaluation-quantity-value value1))
	(quantity-value2 (evaluation-quantity-value value2))
	(band-value-value (evaluation-quantity-value band-value))
	(result-value nil))
    (setq result-value
	  (stack-eval-fuzzy-=-macro
	    quantity-value1 quantity-value2 band-value-value
	    cached-top-of-stack))
    (reclaim-evaluation-quantity value1)
    (reclaim-evaluation-quantity value2)
    (reclaim-evaluation-quantity band-value)
    (make-evaluation-truth-value result-value)))



;;; The `FUZZY-not-= stack-evaluator' is a "not equal" fuzzy comparitor of
;;; numeric values.  It accepts three arguments: two quantities and a band
;;; value.  It returns a fuzzy truth value.  This evaluator is available in the
;;; inference engine and procedures.

(def-funcalled-evaluator fuzzy-not-= (value1 value2 band-value)
			 (5 (inference procedure)
			    (number number number) truth-value
			    funcall-eval-type-3-arg
			    nil pprint-fuzzy-not-=-evaluator)
  (let ((quantity-value1 (evaluation-quantity-value value1))
	(quantity-value2 (evaluation-quantity-value value2))
	(band-value-value (evaluation-quantity-value band-value))
	(result-value nil))
    (setq result-value
	  (if (< band-value-value 0)
	      (negative-fuzzy-band-eval-error band-value cached-top-of-stack)
	      (fuzzy-not
		(stack-eval-fuzzy-=-macro
		  quantity-value1 quantity-value2 band-value-value
		  cached-top-of-stack))))
    (reclaim-evaluation-quantity value1)
    (reclaim-evaluation-quantity value2)
    (reclaim-evaluation-quantity band-value)
    (make-evaluation-truth-value result-value)))



;;; The `IS-MORE-TRUE-THAN stack-evaluator' takes two logical expressions, and
;;; compares the relative truth of their fuzzy truth expressions using greater
;;; than.  Note that this evaluator does not return fuzzy values itself, but
;;; returns true or false strictly.  This evaluator is available in the
;;; inference engine and procedures.

(def-funcalled-evaluator is-more-true-than (truth-value-1 truth-value-2)
			 (6 (inference procedure)
			    (truth-value truth-value) boolean
			    funcall-eval-type-2-arg)
  (let ((truth-value-value-1 (evaluation-truth-value-value truth-value-1))
	(truth-value-value-2 (evaluation-truth-value-value truth-value-2))
	(result-value nil))
    (setq result-value
	  (if (>f truth-value-value-1 truth-value-value-2)
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity)))
    (reclaim-evaluation-truth-value truth-value-1)
    (reclaim-evaluation-truth-value truth-value-2)
    result-value))



;;; The `IS-NOT-MORE-TRUE-THAN stack-evaluator' takes two logical expressions,
;;; and compares the relative truth of their fuzzy truth expressions using "not
;;; greater than".  Note that this evaluator does not return fuzzy values
;;; itself, but returns true or false.  This evaluator is only available in the
;;; inference engine and procedures.

(def-funcalled-evaluator is-not-more-true-than (truth-value-1 truth-value-2)
			 (7 (inference procedure)
			    (truth-value truth-value) boolean
			    funcall-eval-type-2-arg)
  (let ((truth-value-value-1 (evaluation-truth-value-value truth-value-1))
	(truth-value-value-2 (evaluation-truth-value-value truth-value-2))
	(result-value nil))
    (setq result-value
	  (if (>f truth-value-value-1 truth-value-value-2)
	      (make-evaluation-truth-value falsity)
	      (make-evaluation-truth-value truth)))
    (reclaim-evaluation-truth-value truth-value-1)
    (reclaim-evaluation-truth-value truth-value-2)
    result-value))



;;; The `IS-LESS-TRUE-THAN stack-evaluator' takes two logical expressions, and
;;; compares the relative truth of their fuzzy truth expressions using less
;;; than.  Note that this evaluator does not return fuzzy values itself, but
;;; returns true or false.  This evaluator is available in the inference engine
;;; and procedures.

(def-funcalled-evaluator is-less-true-than (truth-value-1 truth-value-2)
			 (8 (inference procedure)
			    (truth-value truth-value) boolean
			    funcall-eval-type-2-arg)
  (let ((truth-value-value-1 (evaluation-truth-value-value truth-value-1))
	(truth-value-value-2 (evaluation-truth-value-value truth-value-2))
	(result-value nil))
    (setq result-value
	  (if (<f truth-value-value-1 truth-value-value-2)
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity)))
    (reclaim-evaluation-truth-value truth-value-1)
    (reclaim-evaluation-truth-value truth-value-2)
    result-value))



;;; The `IS-NOT-LESS-TRUE-THAN stack-evaluator' takes two logical expressions,
;;; and compares the relative truth of their fuzzy truth expressions using "not
;;; less than".  Note that this evaluator does not return fuzzy values itself,
;;; but returns true or false.  This evaluator is available in the inference
;;; engine and procedures.

(def-funcalled-evaluator is-not-less-true-than (truth-value-1 truth-value-2) 
			 (9 (inference procedure)
			    (truth-value truth-value) boolean
			    funcall-eval-type-2-arg)
  (let ((truth-value-value-1 (evaluation-truth-value-value truth-value-1))
	(truth-value-value-2 (evaluation-truth-value-value truth-value-2))
	(result-value nil))
    (setq result-value
	  (if (<f truth-value-value-1 truth-value-value-2)
	      (make-evaluation-truth-value falsity)
	      (make-evaluation-truth-value truth)))
    (reclaim-evaluation-truth-value truth-value-1)
    (reclaim-evaluation-truth-value truth-value-2)
    result-value))






;;;; Conditional Expression Evaluators




;;; The `IF-EXPRESSION stack-evaluator' is a special form that accepts three
;;; arguments.  The first is a truth-value and the second and third can be any
;;; datum type.  If the truth-value is true the value of the second argument is
;;; returned.  Otherwise, if the truth-value is false the value of the third
;;; argument is returned.  Otherwise, if the truth-value is false and there is
;;; no third argument, the value is unknown.  If the condition was true or
;;; false, the expiration is set to be the minimum of the condition expiration
;;; and the "then" or "else" expiration depending on which value is being
;;; returned.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.

;; The G2 user manual mentions that the "else" clause is optional.  If the
;; "else" is not provided then the return value can be "unknown".  Note that the
;; parser currently prohibits if-expressions with no else when parsing
;; procedures.

(def-special-form-converter if-expression (expression)
  (let ((arguments
	  (loop for argument in (cdr expression)
		collect (convert-expression-to-stack-node-tree argument)
		using stack-cons))
	(if-node (make-stack-node-instruction 'if-expression nil)))
    (setf (stack-node-argument-nodes if-node) arguments)
    if-node))



(declare-instruction-for-optimizer
  'if-expression
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    if-like-flow))

;;; The preferred instruction chooser for IF-EXPRESSION chooses instructions and
;;; types on its arguments, and then sets its own return value, depending on
;;; whether any of its arguments can return unknown.

(def-preferred-instruction-chooser if-expression
  (declare (ignore extra-info))
  (let ((unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	(unknown-argument? nil)
	(then-and-else-types-without-unknown nil)
	(no-else? nil)
	(type-spec 'truth-value))
    (setq type-spec
	  (maybe-add-no-item-implies-unknown
	    (maybe-add-unknown
	      type-spec unknown-allowed?)
	    no-item-implies-unknown-allowed?))
    (setf (car argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (car argument-nodes)
	type-spec))
    (when (type-specification-subtype-p
	      '(unknown-datum)
	      (stack-node-value-type (car argument-nodes)))
	(setq unknown-argument? t))
    (loop for argument-node-cons on (cdr argument-nodes)
	  for argument-type = nil
	  for argument-type-without-unknown = nil
	  do
      (setf (car argument-node-cons)
	    (choose-stack-node-instructions-and-types
	      (car argument-node-cons)
	      required-type))
      (setq argument-type (stack-node-value-type (car argument-node-cons)))
      (cond ((type-specification-subtype-p '(unknown-datum) argument-type)
	     (setq unknown-argument? t)
	     (cond ((union-type-specification-p argument-type)
		    (setq argument-type-without-unknown
			  (type-specification-union-minus-type
			    argument-type '(unknown-datum))))
		   (t
		    ;; This cryptic message catches the case where the type
		    ;; model starts to break down.  Hopefully it won't ever
		    ;; happen.  If it does, see JRA.  -jra 5/1/91
		    (compiler-bug
		      "if-expression emitter"
		      "Non-union unknown type returned from then or else clause.")
		    (setq argument-type-without-unknown 'item-or-datum)))
	     )
	    (t
	     (setq argument-type-without-unknown argument-type)
	     ))
      (if (null then-and-else-types-without-unknown)
	  (setq then-and-else-types-without-unknown
		argument-type-without-unknown)
	  (setq then-and-else-types-without-unknown
		(make-type-specification-union
		  then-and-else-types-without-unknown
		  argument-type-without-unknown))))
    (when (=f (length argument-nodes) 2)
      (setq no-else? t)
      (when (not unknown-allowed?)
	(compiler-error
	  "~a ~a ~a"
	  "An IF with no ELSE clause cannot be used in procedures (except within "
	  "a COLLECT DATA or WAIT statement), since a missing ELSE can produce "
	  "the value unknown.")))
    (cond ((or unknown-argument? no-else?)
	   (setf (stack-node-value-type stack-node-instruction)
		 (make-type-specification-union
		   then-and-else-types-without-unknown
		   '(unknown-datum))))
	  (t
	   (setf (stack-node-value-type stack-node-instruction)
		 then-and-else-types-without-unknown)))))



;;; The stack node instruction emitter for IF-EXPRESSION emits in several ways,
;;; depending upon whether or not any of its argument nodes can return unknown
;;; and if an "else" is part of the expression.

;;; If the condition was true or false, the expiration is set to be the minimum
;;; of the condition expiration and the "then" or "else" expiration depending on
;;; which value is being returned.

(def-expiration-special-form if-expression)


;; A FUNCTIONALITY CHANGE!!
;; In version 2, the EVAL version of if-expression would only executed the
;; "else" of the if-expression if the condition was less than the falsity
;; threshold.  Otherwise unknown was returned.  In the STACK-EVAL version, as
;; well as the PROC-EVAL 2.0 version, this test is not done.  cpm, 5/2/91

(def-stack-node-instruction-emitter if-expression
  (declare (ignore extra-info))
  (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (end-of-if-expression-tag (generate-new-goto-tag))
	 (could-be-unknown?
	   (type-specification-subtype-p
	     '(unknown-datum)
	     (stack-node-value-type stack-node-instruction)))
	 (else-or-end-tag (if (or (third argument-nodes) could-be-unknown?)
			      (generate-new-goto-tag)
			      end-of-if-expression-tag))
	 (truth-value-could-be-unknown?
	   (type-specification-subtype-p
	     '(unknown-datum)
	     (stack-node-value-type (car argument-nodes))))
	 (known-truth-value-tag (when truth-value-could-be-unknown?
				  (generate-new-goto-tag))))
    ;; Evaluate the logical expression, and possibly branch.
    (emit-stack-node-tree byte-code-stream (first argument-nodes))
    (when truth-value-could-be-unknown?
      (call-stack-instruction-emitter branch-long-if-known
	byte-code-stream known-truth-value-tag)
      ;; Since we are about to branch to the end of the expression, we have to
      ;; pop the stack and push a NIL (unknown) on to the top.
      (call-stack-instruction-emitter pop-values byte-code-stream 1)
      (call-stack-instruction-emitter push-nones byte-code-stream 1)
      (call-stack-instruction-emitter branch-long byte-code-stream end-of-if-expression-tag)
      (register-tag-in-byte-code-stream
	byte-code-stream known-truth-value-tag))
    (call-stack-instruction-emitter branch-long-if-not-true byte-code-stream else-or-end-tag)
    ;; The "then" clause.
    (emit-stack-node-tree byte-code-stream (second argument-nodes))
    ;; The "else" clause.
    (cond 
      ((third argument-nodes)
       (call-stack-instruction-emitter branch-long byte-code-stream end-of-if-expression-tag)
       (register-tag-in-byte-code-stream
	 byte-code-stream else-or-end-tag)
       (emit-stack-node-tree byte-code-stream (third argument-nodes)))
      (could-be-unknown?
       (call-stack-instruction-emitter branch-long byte-code-stream end-of-if-expression-tag)
       (register-tag-in-byte-code-stream byte-code-stream else-or-end-tag)
       (call-stack-instruction-emitter push-nones byte-code-stream 2)
       (emit-instruction-byte-code byte-code-stream 'minimize-expiration))
      (t
       (compiler-bug
	 "if expression emitter"
	 "There is no else clause and unknown is not allowed.")))
    (register-tag-in-byte-code-stream
      byte-code-stream end-of-if-expression-tag)))






;;;; History Expression Evaluators






;;; History expressions return values and signal errors in the following way.

;;; If the history-related can be computed, it is returned. 

;;; If the object has no history or is not collecting histories, a level 3
;;; warning is given and one of the following is done.  If unknown-datum is an
;;; allowed type, unknown is returned (by setting the stack-expiration).
;;; Otherwise, if no-item (i.e., no value) is an allowed type, no value is
;;; returned.  Otherwise, if neither unknown-datum or no-item is an allowed
;;; type, then an error is signaled.

;;; If unexpected non-numeric values are encountered in the interval or if the
;;; beginning time interval is greater than the end interval, a level 1 stack
;;; error is given.




;;; The macros `stack-eval-invoke-historic-interval-function' and
;;; `stack-eval-invoke-historic-interval-function-with-time-units' are used to
;;; abstact the invocation of history interval functions.  (This is a
;;; replacement for invoke-historic-interval-function which also did its own
;;; evaluation of arguments, issued error messages, and funcalled the
;;; history-function.) The interval arguments are computed differently depending
;;; on the number of arguments and the current environment.

;;; This macro takes raw values (i.e., evaluation-value values) or nil for the
;;; beginning and end intervals and returns a raw value.  It is up to the
;;; calling evaluator to reclaim the arguments and box the return value.  This
;;; is normally done in the dispatch to the funcalled evaluator.

;;; This is a non-standard macro.  Note that the name-of-history-function
;;; argument is not evaluated.  This macro could be optimized to check for nil
;;; interval arguments at macro-expansion time.

;;; Note that an in-simulator argument is passed to the history function.  This
;;; determines whether simulated history values are used.

;; Why does the SIMULATOR not use the start-time in its computations of the
;; following evaluators? -cpm.
;;
;; When a value is stored in a simulation history, the history time stored 
;; is the seconds portion of simulation-time.  When a value is stored in an 
;; inference engine history, the history time stored is gensym-time - 
;; gensym-time-at-start.  Thus, history times, whether for simulated or
;; inference engine histories, always begin at 0 at start.
;;
;;  - Comment from agh in Histories module, -cpm, 11/20/91.

;;; Note that this macro returns a history-related value or nil if no value can
;;; be computed.  It is up to the caller to return unknown by setting the
;;; stack-expiration or to return no value.  Note that the history function
;;; signals an error in some cases, and when returning nil, may issue a level 3
;;; warning to the user.

(defmacro stack-eval-invoke-historic-interval-function
	  (name-of-history-function variable-or-parameter current-environment
	   beginning-of-interval? end-of-interval?)
  (let ((v-or-p variable-or-parameter)
	(environment current-environment))
    `(let* ((in-simulator? (or (eq ,environment 'simulator)
			       (eq ,environment 'simulated-value)))
	    (begin? ,beginning-of-interval?)
	    (end? ,end-of-interval?)
	    (beginning-of-interval-for-environment? nil)
	    (end-of-interval-for-environment? nil)
	    (collection-time? nil)
	    (result? nil))
       (cond (in-simulator?
	      (let ((simulation-time
		      (managed-float-value
			(extract-number-from-compound-fixnum-simulation-time
			  (get-current-time-in-simulation-environment)))))
		(setq beginning-of-interval-for-environment?
		      (if begin?
			  (- simulation-time begin?)
			  nil))
		(setq end-of-interval-for-environment?
		      (cond (end? (- simulation-time end?))
			    (begin? simulation-time)
			    (t nil)))))
	     (t
	      (when (eq end? 'ending-with)
		(setq collection-time?
		      (extract-number-or-value 
			(time-of-most-recent-value ,v-or-p))))
	      (setq beginning-of-interval-for-environment?
		    (if begin?
			(- (if (eq end? 'ending-with)
			       collection-time? 
			       (managed-float-value (clock-get current-g2-time)))
			   begin?
			   (managed-float-value (clock-get g2-time-at-start)))
			nil))
	      (setq end-of-interval-for-environment?
		    (cond (end?
			   (if (eq end? 'ending-with)
			       (- collection-time? 
				  (managed-float-value (clock-get g2-time-at-start)))
			       (- (managed-float-value (clock-get current-g2-time))
				  end?
				  (managed-float-value (clock-get g2-time-at-start)))))
			  (begin?
			   (- (managed-float-value (clock-get current-g2-time))
			      (managed-float-value (clock-get g2-time-at-start))))
			  (t nil)))))
       (setq result? (,name-of-history-function
		      ,v-or-p
		      in-simulator?
		      beginning-of-interval-for-environment?
		      end-of-interval-for-environment?))
       ;; The history function returns either a history-related value or nil,
       ;; or signals a stack error.  Note that in some cases when returning
       ;; nil, a level 3 warning is issued to the user.  This macro does not
       ;; set the stack-expiration.
       result?)))







;; Modify this macro, callers, and the called history functions, to expect an
;; error-string argument!!  This will improve the error message in the history
;; functions.  Currently, the error-string argument is only used in the
;; time-unit error.  Note that def-history-funcalled-instruction takes a similar
;; error string argument.  - cpm, 11/21/91

(defmacro stack-eval-invoke-historic-interval-function-with-time-units
	  (name-of-history-function variable-or-parameter current-environment
	   beginning-of-interval? end-of-interval? time-units? error-string?)
  (let ((units? time-units?)
	(v-or-p variable-or-parameter)
	(environment current-environment))
    `(let* ((in-simulator? (or (eq ,environment 'simulator)
			       (eq ,environment 'simulated-value)))
	    (begin? ,beginning-of-interval?)
	    (end? ,end-of-interval?)
	    (beginning-of-interval-for-environment? nil)
	    (end-of-interval-for-environment? nil)
	    (converted-units? (and ,units? (units-to-integer ,units?)))
	    (collection-time? nil)
	    (result? nil))
       (when (and ,units? (null converted-units?))
;	 (write-stack-error
;	   top-of-stack
;	   (tformat "Cannot compute the ~a of ~NF.  " ,error-string? ,v-or-p)
;	   (if (evaluation-value-p ,units?)
;	       (write-evaluation-value ,units?)
;	       (twrite ,units?))
;	   (twrite-string " is an invalid time unit."))
	 (if (evaluation-value-p ,units?)
	     (stack-error
	       top-of-stack
	       "Cannot compute the ~a of ~NF.  ~NV is an invalid time-unit."
	       ,error-string? ,v-or-p ,units?)
	     (stack-error
	       top-of-stack
	       "Cannot compute the ~a of ~NF.  ~a is an invalid time unit."
	       ,error-string? ,v-or-p ,units?)))
       (cond (in-simulator?
	      (let ((simulation-time
		      (managed-float-value
			(extract-number-from-compound-fixnum-simulation-time
			  (get-current-time-in-simulation-environment)))))
		(setq beginning-of-interval-for-environment?
		      (if begin?
			  (- simulation-time begin?)
			  nil))
		(setq end-of-interval-for-environment?
		      (cond (end? (- simulation-time end?))
			    (begin? simulation-time)
			    (t nil)))))
	     (t
	      (when (eq end? 'ending-with)
		(setq collection-time?
		      (extract-number-or-value 
			(time-of-most-recent-value ,v-or-p))))
	      (setq beginning-of-interval-for-environment?
		    (if begin?
			(- (if (eq end? 'ending-with)
			       collection-time? 
			       (managed-float-value (clock-get current-g2-time)))
			   begin?
			   (managed-float-value (clock-get g2-time-at-start)))
			nil))
	      (setq end-of-interval-for-environment?
		    (cond (end?
			   (if (eq end? 'ending-with)
			       (- collection-time? 
				  (managed-float-value (clock-get g2-time-at-start)))
			       (- (managed-float-value (clock-get current-g2-time))
				  end?
				  (managed-float-value (clock-get g2-time-at-start)))))
			  (begin?
			   (- (managed-float-value (clock-get current-g2-time))
			      (managed-float-value (clock-get g2-time-at-start))))
			  (t nil)))))
       (setq result? (,name-of-history-function
		      ,v-or-p
		      in-simulator?
		      converted-units?
		      beginning-of-interval-for-environment?
		      end-of-interval-for-environment?))
	 ;; The history function returns either a history-related value or nil,
	 ;; or signals a stack error.  Note that in some cases when returning
	 ;; nil, a level 3 warning is issued to the user.  This macro does not
	 ;; set the stack-expiration.
	 result?)))



;;; The macro `def-history-special-form-converter' is used to define special
;;; form converters for many history operations.  A stack-node instruction is
;;; created for the instruction, the arguments are converted into stack-node
;;; trees, and these argument trees are added the argument slot of the
;;; stack-node instruction.  The specialty of this converter is to choose the
;;; instruction name based on the number of arguments.  If an instruction-name
;;; argument is nil and the argument length corresponds to this missing
;;; argument, the stack-node will be given the converter instruction-name.

;;; Note that this macro does not evaluate its arguments.

(defmacro def-history-special-form-converter
	  (instruction-name &optional (instruction-name-for-0-arg? nil)
	   (instruction-name-for-1-arg? nil) (instruction-name-for-2-arg? nil)
	   (instruction-name-for-3-arg? nil)
	   (instruction-name-for-4-arg? nil))
  `(def-special-form-converter ,instruction-name (expression)
     (let* ((argument-count (length (cdr expression)))
	    (instruction-node
	      (make-stack-node-instruction
		(case argument-count
		  (4 (or ',instruction-name-for-4-arg?
			 ',instruction-name))
		  (3 (or ',instruction-name-for-3-arg?
			 ',instruction-name))
		  (2 (or ',instruction-name-for-2-arg?
			 ',instruction-name))
		  (1 (or ',instruction-name-for-1-arg?
			 ',instruction-name))
		  (0 (or ',instruction-name-for-0-arg?
			 ',instruction-name))
		  (t ',instruction-name))
		nil)))
       (loop for argument in (cdr expression)
	     collect
	       (convert-expression-to-stack-node-tree argument)
	       into converted-argument-list using stack-cons
	     finally
	       (setf (stack-node-argument-nodes instruction-node)
		     converted-argument-list))
       instruction-node)))



;;; The macro `def-history-preferred-instruction-chooser' defines instruction
;;; choosers for some history instructions.  The instructions arguments can be a
;;; variable-or-parameter and 0, 1, or 2 numeric arguments.  If the
;;; per-time-unit?  flag is non-nil, the second argument type is symbol, and
;;; there may be 0, 1, or 2 numeric arguments.  The return type is quantity.

;; CHECK THE USE OF NO-ITEM AND UNKNOWN-DATUM IN THE ARGUMENT AND VALUE TYPES!!!
;; - cpm, 11/20/91

;;; Note that this macro does not evaluate its argument.

(defmacro def-history-preferred-instruction-chooser
    (instruction-name &optional (time-unit-p? nil) (return-type 'number))
  `(def-preferred-instruction-chooser ,instruction-name
     (declare (ignore extra-info))
     (let* ((unknown-allowed?
	      (type-specification-subtype-p '(unknown-datum) required-type))
	    (no-item-implies-unknown-allowed?
	      (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	    (no-item-allowed?
	      (type-specification-subtype-p '(no-item) required-type))
	    (argument-nodes (stack-node-argument-nodes stack-node-instruction)))
       ;; variable or parameter
       (when argument-nodes
	 (setf (first argument-nodes)
	       (choose-stack-node-instructions-and-types
		 (first argument-nodes)
		 (maybe-add-no-item-implies-unknown
		   (maybe-add-no-item
		     (maybe-add-unknown
		       '(class variable-or-parameter) unknown-allowed?)
		     no-item-allowed?)
		   no-item-implies-unknown-allowed?))))
       ;; optional first interval/datapoint or time-unit
       (when (cdr argument-nodes)
	 (setf (second argument-nodes)
	       (choose-stack-node-instructions-and-types
		 (second argument-nodes) 
		 (maybe-add-no-item
		   (maybe-add-unknown
		     (if ',time-unit-p? 'symbol 'number)
		     unknown-allowed?)
		   no-item-allowed?))))
       (when (cddr argument-nodes)
	 ;; optional second interval (third argument)
	 (setf (third argument-nodes)
	       (choose-stack-node-instructions-and-types
		 (third argument-nodes)
		 (make-type-specification-union
		   (maybe-add-no-item-implies-unknown
		     (maybe-add-no-item
		       (maybe-add-unknown 'number unknown-allowed?)
		       no-item-allowed?)
		     no-item-implies-unknown-allowed?)
		   'truth-value))))
       (when (cdddr argument-nodes)
	 ;; optional second interval (fourth argument)
	 (setf (fourth argument-nodes)
	       (choose-stack-node-instructions-and-types
		 (fourth argument-nodes)
		 (make-type-specification-union
		   (maybe-add-no-item-implies-unknown
		     (maybe-add-no-item
		       (maybe-add-unknown 'number unknown-allowed?)
		       no-item-allowed?)
		     no-item-implies-unknown-allowed?)
		   'truth-value))))
       (setf (stack-node-value-type stack-node-instruction)
	     (maybe-add-no-item
	       (maybe-add-unknown ',return-type (or unknown-allowed?
						    no-item-implies-unknown-allowed?))
	       no-item-allowed?)))))




;;; The macro `def-history-stack-node-instruction-emitter' is the emitter for
;;; most history instructions.  After emitting the instruction arguments, two
;;; new stack arguments, an unknown-datum flag and a no-item flag, are also
;;; emitted.

;;; Note that this macro does not evaluate its argument.

(defmacro def-history-stack-node-instruction-emitter (instruction-name)
  `(progn
     (declare-optimizer-stack-instruction ,instruction-name)
     (def-stack-node-instruction-emitter ,instruction-name
       (declare (ignore extra-info))
       (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	     (unknown-allowed?
	       (type-specification-subtype-p
		 '(unknown-datum) (stack-node-value-type stack-node-instruction)))
	     (no-item-allowed?
	       (type-specification-subtype-p
		 '(no-item) (stack-node-value-type stack-node-instruction))))
	 (loop for argument in argument-nodes
	       do
	   (emit-stack-node-tree byte-code-stream argument))
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream
	   (make-evaluation-truth-value (if unknown-allowed? truth falsity)))
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream
	   (make-evaluation-truth-value (if no-item-allowed? truth falsity)))
	 (call-stack-instruction-emitter funcall-instruction
	   byte-code-stream ',instruction-name)))))



;;; The macro `def-history-funcalled-instruction' is used to abstract the
;;; definition of some of the history funcalled instructions.  These
;;; instructions take 3 to 5 arguments, a variable-or-parameter, an optional
;;; start interval, an optional end interval, an unknown allowed flag, and a
;;; no-item allowed flag.  This macro is useful for average-value,
;;; minimum-value, etc.  It currently does not work for history instructions
;;; that use a per-time-unit argument.

(defmacro def-history-funcalled-instruction
	  (instruction-name instruction-number history-function-name arg-count 
	   error-string &optional (error-if-empty-history? t) (pprinter? nil))
  `(def-funcalled-instruction ,instruction-name (,instruction-number all ,arg-count 1 nil ,pprinter?)
     (let* ((stack-arg-count ,arg-count)
	    (stack-error-string ,error-string)
	    (stack-error-if-empty-history? ,error-if-empty-history?)
	    (variable-or-parameter? (stack-arg 0))
	    (start-interval-p  (>f stack-arg-count 3))
	    (end-interval-p (>f stack-arg-count 4))
	    (start-of-interval? (if start-interval-p
				    (evaluation-quantity-value (stack-arg 1))
				    nil))
	    ;; evaluation-truth-value supports "during the <interval> ending
	    ;; with the collection time" where the second interval is "true".
	    ;; - jpg 2/1/07
	    (end-of-interval?
	      (if end-interval-p
		  (if (evaluation-truth-value-p (stack-arg 2))
		      (if (evaluation-boolean-is-true-p (stack-arg 2))
			  'ending-with
			  (stack-error
			    top-of-stack
			    "Illegal use of a truth-value in computing a history."))
		      (evaluation-quantity-value (stack-arg 2)))
		  nil))
	    (unknown-allowed (evaluation-truth-value-value
			       (stack-arg-of-stack-count
				 (-f stack-arg-count 2) stack-arg-count)))
	    (no-item-allowed (evaluation-truth-value-value
			       (stack-arg-of-stack-count
				 (-f stack-arg-count 1) stack-arg-count)))
	    (result? (if variable-or-parameter?
			 (stack-eval-invoke-historic-interval-function
			   ,history-function-name variable-or-parameter?
			   current-environment start-of-interval?
			   end-of-interval?)
			 nil))
	    return-value?)
       (cond (result?
	      (setq return-value? (make-evaluation-quantity result?)))
	     ((null variable-or-parameter?)
	      ;; No-item must be allowed.  Or, this would not be possible.
	      (setq return-value? nil))
	     ((=f unknown-allowed truth)
	      (setq stack-expiration nil)
	      (setq return-value? nil))
	     ((=f no-item-allowed truth)
	      (setq return-value? nil))
	     ((and end-of-interval? start-of-interval?)
	      (if (eq end-of-interval? 'ending-with)
		  (if stack-error-if-empty-history?
		      (stack-error
			top-of-stack
			"Cannot compute the ~a of ~NF during the ~NC ~
                         ending with the collection time. ~
                         There are no values in the history for the interval specified."
			stack-error-string variable-or-parameter? start-of-interval?
			'seconds)
		      (stack-error
			top-of-stack
			"Cannot compute the ~a of ~NF during the ~NC ~
                         ending with the collection time. ~
                         This object is not keeping history values."
			stack-error-string variable-or-parameter? start-of-interval?
			'seconds))
		  (if stack-error-if-empty-history?
		      (stack-error
			top-of-stack
			"Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~
                         There are no values in the history for the interval specified."
			stack-error-string variable-or-parameter? start-of-interval?
			'seconds end-of-interval? 'seconds)
		      (stack-error
			top-of-stack
			"Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~
                         This object is not keeping history values."
			stack-error-string variable-or-parameter? start-of-interval?
			'seconds end-of-interval? 'seconds))))
	     (start-of-interval?
	      (if stack-error-if-empty-history?
		  (stack-error
		    top-of-stack
		    "Cannot compute the ~a of ~NF during the last ~NC. ~
                    There are no values in the history for the interval specified."
		    stack-error-string variable-or-parameter? start-of-interval?
		    'seconds)
		  (stack-error
		    top-of-stack
		    "Cannot compute the ~a of ~NF during the last ~NC. ~
                    This object is not keeping history values."
		    stack-error-string variable-or-parameter? start-of-interval?
		    'seconds)))
	     (stack-error-if-empty-history?
	      (stack-error
		top-of-stack
		"Cannot compute the ~a of ~NF.  There are no values in its history."
		stack-error-string variable-or-parameter? start-of-interval?
		'seconds))
	     (t
	      (stack-error
		top-of-stack
		"Cannot compute the ~a of ~NF.  This object is not keeping ~
                 history values."
		stack-error-string variable-or-parameter? start-of-interval?
		'seconds)))
       (loop for i from 1 below stack-arg-count
	     for stack-arg = (stack-arg-of-stack-count i stack-arg-count)
	     do
	 (when stack-arg
	   (reclaim-evaluation-value stack-arg)))
       (decff top-of-stack (-f stack-arg-count 1))
       (setf (svref local-stack top-of-stack) return-value?)
       nil)))


(defmacro def-history-with-time-units-funcalled-instruction
	  (instruction-name instruction-number history-function-name arg-count
	   error-string pprinter?)
  `(def-funcalled-instruction ,instruction-name (,instruction-number all ,arg-count 1 nil ,pprinter?)
     (let* ((stack-arg-count ,arg-count)
	    (stack-error-string ,error-string)
	    (variable-or-parameter? (stack-arg 0))
	    (time-units? (evaluation-symbol-symbol (stack-arg 1)))
	    (start-interval-p (>f stack-arg-count 4))
	    (end-interval-p (>f stack-arg-count 5))
	    (start-of-interval? (if start-interval-p
				    (evaluation-quantity-value (stack-arg 2))
				    nil))
	    ;; evaluation-truth-value supports "during the <interval> ending
	    ;; with the collection time" where the second interval is "true".
	    ;; - jpg 2/1/07
	    (end-of-interval?
	      (if end-interval-p
		  (if (evaluation-truth-value-p (stack-arg 3))
		      (if (evaluation-boolean-is-true-p (stack-arg 3))
			  'ending-with
			  (stack-error
			    top-of-stack
			    "Illegal use of a truth-value in computing a history."))
		      (evaluation-quantity-value (stack-arg 3)))
		  nil))
	    (unknown-allowed (evaluation-truth-value-value
			       (stack-arg-of-stack-count
				 (-f stack-arg-count 2) stack-arg-count)))
	    (no-item-allowed (evaluation-truth-value-value
			       (stack-arg-of-stack-count
				 (-f stack-arg-count 1) stack-arg-count)))
	    (result?
	      (if variable-or-parameter?
		  (stack-eval-invoke-historic-interval-function-with-time-units
		    ,history-function-name variable-or-parameter?
		    current-environment start-of-interval? end-of-interval?
		    time-units? stack-error-string)
		  nil))
	    return-value?)
       (cond (result?
	      (setq return-value? (make-evaluation-quantity result?)))
	     ((null variable-or-parameter?)
	      ;; No-item must be allowed.  Or, this would not be possible.
	      (setq return-value? nil))	      
	     ((=f unknown-allowed truth)
	      (setq stack-expiration nil)
	      (setq return-value? nil))
	     ((=f no-item-allowed truth)
	      (setq return-value? nil))
	     ((and end-of-interval? start-of-interval?)
	      (if (eq end-of-interval? 'ending-with)
		  (stack-error
		    top-of-stack
		    "Cannot compute the ~a of ~NF during the ~NC ~
                     ending with the collection time. ~
                     There are no values in the history for the interval specified."
		    stack-error-string variable-or-parameter? start-of-interval?
		    'seconds)
		  (stack-error
		    top-of-stack
		    "Cannot compute the ~a of ~NF between ~NC ago and ~NC ago. ~
                     There are no values in the history for the interval specified."
		    stack-error-string variable-or-parameter? start-of-interval?
		    'seconds end-of-interval? 'seconds)))
	     (start-of-interval?
	      (stack-error
		top-of-stack
		"Cannot compute the ~a of ~NF during the last ~NC. ~
                 There are no values in the history for the interval specified."
		stack-error-string variable-or-parameter? start-of-interval?
		'seconds))
	     (t
	      (stack-error
		top-of-stack
		"Cannot compute the ~a of ~NF.  There are no values in its ~
                 history."
		stack-error-string variable-or-parameter? start-of-interval?
		'seconds)))
       (loop for i from 1 below stack-arg-count
	     for stack-arg = (stack-arg-of-stack-count i stack-arg-count)
	     do
	 (when stack-arg
	   (reclaim-evaluation-value stack-arg)))
       (decff top-of-stack (-f stack-arg-count 1))
       (setf (svref local-stack top-of-stack) return-value?)
       nil)))



;;; The `AVERAGE-VALUE stack-evaluator' returns the average value collected in
;;; the interval for a variable or parameter.  This is a simple average of all
;;; the values received during the time period.  Therefore, if values are
;;; received at irregular intervals, this will be different from the time
;;; average.  The evaluator accepts a variable or parameter designation argument
;;; and 1 or 2 time interval arguments.

;;; This instruction returns unknown-datum, no value, or signals an error if a
;;; variable or parameter does not keep histories or does not have history
;;; values for the given interval.  This behavior depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine and procedures.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.


(def-expiration-source-operator average-value-1)
(def-expiration-source-operator average-value-2)

(def-history-special-form-converter
  average-value nil nil average-value-1 average-value-2)

(def-history-preferred-instruction-chooser average-value-1)
(def-history-preferred-instruction-chooser average-value-2)

(def-history-stack-node-instruction-emitter average-value-1)
(def-history-stack-node-instruction-emitter average-value-2)



;;; Instructions 49 and 50, the `AVERAGE-VALUE-1 and AVERAGE-VALUE-2 funcalled
;;; stack-instructionS' are the two instructions used to implement the evaluator
;;; for AVERAGE-VALUE.  Both accept a variable-or-parameter, an interval,
;;; unknown-datum allowed flag, and an no-item allowed flag.  Average-value-2
;;; also takes a second interval argument.  The return value and error handling
;;; depends on the value of the unknown-datum and no-item flags.

(def-history-funcalled-instruction
  average-value-1 49 get-averaged-value 4 "average value" t
  pprint-average-value-1-instruction)

(def-history-funcalled-instruction
  average-value-2 50 get-averaged-value 5 "average value" t
  pprint-average-value-2-instruction)

;;; The `SUM-OF-VALUES stack-evaluator' returns the sum of all values collected in
;;; the interval for a variable or parameter.  The evaluator accepts a variable or parameter designation argument
;;; and 1 or 2 time interval arguments.

;;; This instruction returns unknown-datum, no value, or signals an error if a
;;; variable or parameter does not keep histories or does not have history
;;; values for the given interval.  This behavior depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine and procedures.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.


(def-expiration-source-operator sum-of-values-1)
(def-expiration-source-operator sum-of-values-2)

(def-history-special-form-converter
  sum-of-values nil nil sum-of-values-1 sum-of-values-2)

(def-history-preferred-instruction-chooser sum-of-values-1)
(def-history-preferred-instruction-chooser sum-of-values-2)

(def-history-stack-node-instruction-emitter sum-of-values-1)
(def-history-stack-node-instruction-emitter sum-of-values-2)



;;; Instructions 85 and 86, the `SUM-OF-VALUES-1 and SUM-OF-VALUES-2 funcalled
;;; stack-instructionS' are the two instructions used to implement the evaluator
;;; for SUM-OF-VALUES.  Both accept a variable-or-parameter, an interval,
;;; unknown-datum allowed flag, and an no-item allowed flag.  sum-of-values-2
;;; also takes a second interval argument.  The return value and error handling
;;; depends on the value of the unknown-datum and no-item flags.

(def-history-funcalled-instruction
  sum-of-values-1 85 get-sum-of-values 4 "sum of values" nil
  pprint-sum-of-values-1-instruction)

(def-history-funcalled-instruction
  sum-of-values-2 86 get-sum-of-values 5 "sum of value" nil
  pprint-sum-of-values-2-instruction)

;;; The `MINIMUM-VALUE stack-evaluator' returns the minimum value collected in
;;; the interval for a variable or parameter.  The evaluator accepts a variable
;;; or parameter designation argument and one or two time interval arguments.

;;; This instruction returns unknown-datum, no value, or signals an error if a
;;; variable or parameter does not keep histories or does not have history
;;; values for the given interval.  This behavior depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

(def-expiration-source-operator minimum-value-1)
(def-expiration-source-operator minimum-value-2)

(def-history-special-form-converter
  minimum-value nil nil minimum-value-1 minimum-value-2)

(def-history-preferred-instruction-chooser minimum-value-1)
(def-history-preferred-instruction-chooser minimum-value-2)

(def-history-stack-node-instruction-emitter minimum-value-1)
(def-history-stack-node-instruction-emitter minimum-value-2)



;;; Instructions 51 and 52, the `MINIMUM-VALUE-1 and MINIMUM-VALUE-2 funcalled
;;; stack-instructions' are the two instructions used to implement the evaluator
;;; for MINIMUM-VALUE.  Both accept a variable-or-parameter, an interval,
;;; unknown-datum allowed flag, and an no-item allowed flag.  Minimum-value-2
;;; also takes a second interval argument.  The return value and error handling
;;; depends on the value of the unknown-datum and no-item flags.

(def-history-funcalled-instruction
  minimum-value-1 51 get-minimum-value 4 "minimum value" t
  pprint-minimum-value-1-instruction)

(def-history-funcalled-instruction
  minimum-value-2 52 get-minimum-value 5 "minimum value" t
  pprint-minimum-value-2-instruction)



;;; The `MAXIMUM-VALUE stack-evaluator' returns the maximum value collected in
;;; the interval for a variable or parameter.  The evaluator accepts a variable
;;; or parameter designation argument and one or two time interval arguments.

;;; This instruction returns unknown-datum, no value, or signals an error if a
;;; variable or parameter does not keep histories or does not have history
;;; values for the given interval.  This behavior depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

(def-expiration-source-operator maximum-value-1)
(def-expiration-source-operator maximum-value-2)

(def-history-special-form-converter
  maximum-value nil nil maximum-value-1 maximum-value-2)

(def-history-preferred-instruction-chooser maximum-value-1)
(def-history-preferred-instruction-chooser maximum-value-2)

(def-history-stack-node-instruction-emitter maximum-value-1)
(def-history-stack-node-instruction-emitter maximum-value-2)



;;; Instructions 53 and 54, the `MAXIMUM-VALUE-1 and MAXIMUM-VALUE-2 funcalled
;;; stack-instructions' are the two instructions used to implement the evaluator
;;; for MAXIMUM-VALUE.  Both accept a variable-or-parameter, an interval,
;;; unknown-datum allowed flag, and an no-item allowed flag.  Maximum-value-2
;;; also takes a second interval argument.  The return value and error handling
;;; depends on the value of the unknown-datum and no-item flags.

(def-history-funcalled-instruction
  maximum-value-1 53 get-maximum-value 4 "maximum value" t
  pprint-maximum-value-1-instruction)

(def-history-funcalled-instruction
  maximum-value-2 54 get-maximum-value 5 "maximum value" t
  pprint-maximum-value-2-instruction)



;;; The `STANDARD-DEVIATION stack-evaluator' returns the standard deviation
;;; collected in the interval for a variable or parameter.  The evaluator
;;; accepts a variable or parameter designation argument and one or two time
;;; interval arguments.

;;; This instruction returns unknown-datum, no value, or signals an error if a
;;; variable or parameter does not keep histories or does not have history
;;; values for the given interval.  This behavior depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

(def-expiration-source-operator standard-deviation-1)
(def-expiration-source-operator standard-deviation-2)

(def-history-special-form-converter
  standard-deviation nil nil standard-deviation-1 standard-deviation-2)

(def-history-preferred-instruction-chooser standard-deviation-1)
(def-history-preferred-instruction-chooser standard-deviation-2)

(def-history-stack-node-instruction-emitter standard-deviation-1)
(def-history-stack-node-instruction-emitter standard-deviation-2)



;;; Instructions 55 and 56, the `STANDARD-DEVIATION-1 and STANDARD-DEVIATION-2
;;; funcalled stack-instructions' are the two instructions used to implement the
;;; evaluator for STANDARD-DEVIATION.  Both accept a variable-or-parameter, an
;;; interval, unknown-datum allowed flag, and an no-item allowed flag.
;;; Standard-deviation-2 also takes a second interval argument.  The return
;;; value and error handling depends on the value of the unknown-datum and
;;; no-item flags.

(def-history-funcalled-instruction
  standard-deviation-1 55 get-standard-deviation-of-value 4
  "standard deviation" t pprint-standard-deviation-1-instruction)

(def-history-funcalled-instruction
  standard-deviation-2 56 get-standard-deviation-of-value 5
  "standard deviation" t pprint-standard-deviation-2-instruction)



;;; The `NUMBER-OF-DATAPOINTS stack-evaluator' returns the number of values
;;; collected for a variable or parameter in either its entire history or in the
;;; specified interval.  The evaluator accepts a variable or parameter
;;; designation argument and zero, one, or two time interval arguments.

;;; This instruction returns unknown-datum, no value, or signals an error if a
;;; variable or parameter does not keep histories or does not have history
;;; values for the given interval.  This behavior depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

(def-expiration-source-operator number-of-datapoints-0)
(def-expiration-source-operator number-of-datapoints-1)
(def-expiration-source-operator number-of-datapoints-2)

(def-history-special-form-converter
  number-of-datapoints nil number-of-datapoints-0 number-of-datapoints-1
  number-of-datapoints-2)

(declare-optimizer-stack-instruction number-of-datapoints-0)
(declare-optimizer-stack-instruction number-of-datapoints-1)
(declare-optimizer-stack-instruction number-of-datapoints-2)

(def-history-preferred-instruction-chooser number-of-datapoints-0)
(def-history-preferred-instruction-chooser number-of-datapoints-1)
(def-history-preferred-instruction-chooser number-of-datapoints-2)

(def-history-stack-node-instruction-emitter number-of-datapoints-0)
(def-history-stack-node-instruction-emitter number-of-datapoints-1)
(def-history-stack-node-instruction-emitter number-of-datapoints-2)



;;; Instructions 57, 58, and 59, the `NUMBER-OF-DATAPOINTS-0,
;;; NUMBER-OF-DATAPOINTS-1, and NUMBER-OF-DATAPOINTS-2 funcalled
;;; stack-instructions' are the instructions used to implement the evaluator for
;;; NUMBER-OF-DATAPOINTS.  All accept a variable-or-parameter, unknown-datum
;;; allowed flag, and an no-item allowed flag.  Number-of-datapoints-1 also
;;; takes a start interval argument.  Number-of-datapoints-2 also takes start
;;; and end interval arguments.  The return value and error handling depends on
;;; the value of the unknown-datum and no-item flags.

(def-history-funcalled-instruction
  number-of-datapoints-0 57 number-of-datapoints 3
  "number of history datapoints" nil pprint-number-of-datapoints-0-instruction)

(def-history-funcalled-instruction
  number-of-datapoints-1 58 number-of-datapoints 4
  "number of history datapoints" nil pprint-number-of-datapoints-1-instruction)

(def-history-funcalled-instruction
  number-of-datapoints-2 59 number-of-datapoints 5
  "number of history datapoints" nil pprint-number-of-datapoints-2-instruction)



;;; The `RATE-OF-CHANGE stack-evaluator' returns the rate of change per second,
;;; minute, hour, day, or week of a variable or parameter over a selected period
;;; of time.  The rate of change is computed by dividing the total accumulated
;;; change during the time period by the length of the time period.  The
;;; evaluator accepts a variable or parameter designation argument, a units
;;; arguments (e.g., seconds, minutes, etc.), and one or two time interval
;;; arguments.

;;; This instruction returns unknown-datum, no value, or signals an error if a
;;; variable or parameter does not keep histories or does not have history
;;; values for the given interval.  This behavior depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

;;; Rate-of-Change <variable-or-parameter> <units> <interval> [<interval>]

;; EVAL: an error message was not displayed for invalid time units arg.

(def-expiration-source-operator rate-of-change-1)
(def-expiration-source-operator rate-of-change-2)

(def-history-special-form-converter
  rate-of-change nil nil nil rate-of-change-1 rate-of-change-2)

(def-history-preferred-instruction-chooser rate-of-change-1 t)
(def-history-preferred-instruction-chooser rate-of-change-2 t)

(def-history-stack-node-instruction-emitter rate-of-change-1)
(def-history-stack-node-instruction-emitter rate-of-change-2)



;;; Instructions 60 and 61, the `RATE-OF-CHANGE-1 and RATE-OF-CHANGE-2 funcalled
;;; stack-instructions' are the instructions used to implement the evaluator for
;;; RATE-OF-CHANGE.  All accept a variable-or-parameter, a time unit, start
;;; interval, unknown-datum allowed flag, and an no-item allowed flag.
;;; Rate-of-change-2 also takes an end interval argument.  The return value and
;;; error handling depends on the value of the unknown-datum and no-item flags.

(def-history-with-time-units-funcalled-instruction
  rate-of-change-1 60 get-rate-of-change-of-value 5 "rate of change"
  pprint-rate-of-change-1-instruction)

(def-history-with-time-units-funcalled-instruction
  rate-of-change-2 61 get-rate-of-change-of-value 6 "rate of change"
  pprint-rate-of-change-2-instruction)



;;; The `INTEGRAL stack-evaluator' returns the integral, over time measured in
;;; seconds, minutes, hours, days or weeks, of the value of a variable or
;;; parameter.  The integral is calculated by performing a true integration over
;;; time of the most recently received value for the variable or parameter at
;;; each instant of the time period.  The evaluator accepts a variable or
;;; parameter designation argument, a units arguments (e.g., seconds, minutes,
;;; etc.), and one or two time interval arguments.

;;; This instruction returns unknown-datum, no value, or signals an error if a
;;; variable or parameter does not keep histories or does not have history
;;; values for the given interval.  This behavior depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

;;; Integral <variable-or-parameter> <units> <interval> [<interval>]

(def-expiration-source-operator integral-1)
(def-expiration-source-operator integral-2)

(def-history-special-form-converter integral nil nil nil integral-1 integral-2)

(def-history-preferred-instruction-chooser integral-1 t)
(def-history-preferred-instruction-chooser integral-2 t)

(def-history-stack-node-instruction-emitter integral-1)
(def-history-stack-node-instruction-emitter integral-2)



;;; Instructions 62 and 63, the `INTEGRAL-1 and INTEGRAL-2 funcalled
;;; stack-instructions' are the instructions used to implement the evaluator for
;;; INTEGRAL.  All accept a variable-or-parameter, a time unit, start interval,
;;; unknown-datum allowed flag, and an no-item allowed flag.  Integral-2 also
;;; takes an end interval argument.  The return value and error handling depends
;;; on the value of the unknown-datum and no-item flags.

(def-history-with-time-units-funcalled-instruction
  integral-1 62 get-integral-of-value-over-interval 5 "integral"
  pprint-integral-1-instruction)

(def-history-with-time-units-funcalled-instruction
  integral-2 63 get-integral-of-value-over-interval 6 "integral"
  pprint-integral-2-instruction)



;;; The `HISTORIC-VALUE stack-evaluator' returns the value of a variable or
;;; parameter as of a given time interval ago.  If a value was collected at the
;;; indicated time, it is returned.  Otherwise, the next previous value that it
;;; collected, if one exists, is returned.  If none is found, this instruction
;;; returns unknown-datum, no value, or signals an error.  This behavior depends
;;; on whether the instruction allows unknown-datum and/or no-item.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

;;; HISTORIC-VALUE (variable-or-parameter, time-interval)

(def-expiration-source-operator historic-value)

(def-default-special-form-converter historic-value)

(def-history-preferred-instruction-chooser historic-value nil datum)

(def-history-stack-node-instruction-emitter historic-value)



;;; Instruction 64, the `HISTORIC-VALUE funcalled stack-instruction' is the
;;; instruction used to implement the evaluator for Historic-Value.  It accepts
;;; a variable-or-parameter, a time interval, unknown-datum allowed flag, and an
;;; no-item allowed flag.  The return value and error handling depends on the
;;; value of the unknown-datum and no-item flags.

(def-funcalled-instruction historic-value (64 all 4 1 nil pprint-historic-value-instruction)
  (let* ((variable-or-parameter? (stack-arg 0))
	 (interval (evaluation-quantity-value (stack-arg 1)))
	 (unknown-allowed (evaluation-truth-value-value (stack-arg 2)))
	 (no-item-allowed (evaluation-truth-value-value (stack-arg 3)))
	 (result?
	   (if variable-or-parameter?
	       (if (or (eq current-environment 'simulator)
		       (eq current-environment 'simulated-value))
		   (get-historical-delayed-value
		     variable-or-parameter? t 
		     (- (managed-float-value
			  (extract-number-from-compound-fixnum-simulation-time
			    (get-current-time-in-simulation-environment)))
			interval))
		   (get-historical-delayed-value
		     variable-or-parameter? nil
		     (- (managed-float-value (clock-get current-g2-time))
			interval
			(managed-float-value (clock-get g2-time-at-start)))))
	       nil))
	 return-value?)
    (cond (result?
	   ;; The following reclaims the result argument, when necessary.  This
	   ;; is needed because the history value reference copies any managed
	   ;; values (i.e., text).
	   (setq return-value?
		 (make-evaluation-value-reclaiming-argument
		   result?
		   (type-specification-of-variable-or-parameter-value
		     variable-or-parameter?)))
	   (setq result? nil))
	  ((null variable-or-parameter?)
	   ;; No-item must be allowed.  Or, this would not be possible.
	   (setq return-value? nil))
	  ((=f unknown-allowed truth)
	   (setq stack-expiration nil)
	   (setq return-value? nil))
	  ((=f no-item-allowed truth)
	   (setq return-value? nil))
	  (t
	   (stack-error
	     top-of-stack
	     "Cannot reference the value of ~NF as of ~NC ago.  ~
              There was no value at that time."
	     variable-or-parameter? interval 'seconds)))
    (reclaim-evaluation-quantity (stack-arg 1))
    (reclaim-evaluation-truth-value (stack-arg 2))
    (reclaim-evaluation-truth-value (stack-arg 3))
    (decff top-of-stack 3)
    (setf (svref local-stack top-of-stack) return-value?)
    nil))

;;; The `VALUE-OF-PREVIOUS-DATAPOINT stack-evaluator' returns the value of a
;;; variable or parameter at a given number of datapoints ago.  If the value is
;;; not present at that time, a level 3 warning is given and either unknown
;;; returns unknown-datum, returns no value, or signals an error.  This depends
;;; on whether the instruction allows unknown-datum and/or no-item.

;;; The evaluator accepts a variable or parameter and datapoint index (integer)
;;; arguments.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

;;; VALUE-OF-PREVIOUS-DATAPOINT
;;;    (variable-or-parameter, number-of-data-points-ago)

(declare-optimizer-stack-instruction value-of-previous-datapoint)
    
(def-expiration-source-operator value-of-previous-datapoint)

(def-default-special-form-converter value-of-previous-datapoint)

(def-history-preferred-instruction-chooser
  value-of-previous-datapoint nil datum)

(def-history-stack-node-instruction-emitter value-of-previous-datapoint)



;;; Instruction 65, the `VALUE-OF-PREVIOUS-DATAPOINT funcalled
;;; stack-instruction' is the instruction used to implement the evaluator for
;;; Value-Of-Previous-Datapoint.  It accepts a variable-or-parameter and a
;;; number-of-datapoints-ago argument.  The return value and error handling
;;; depends on the value of the unknown-datum and no-item flags.

(def-funcalled-instruction value-of-previous-datapoint (65 all 4 1 nil
							   pprint-value-of-previous-datapoint-instruction)
  (let* ((variable-or-parameter? (stack-arg 0))
	 (number-of-datapoints-ago (evaluation-quantity-value (stack-arg 1)))
	 (unknown-allowed (evaluation-truth-value-value (stack-arg 2)))
	 (no-item-allowed (evaluation-truth-value-value (stack-arg 3)))
	 result?
	 return-value?)
  (when (<f number-of-datapoints-ago 0)
    (stack-error
      top-of-stack
      "Cannot reference the value of ~NF as of ~d datapoints ago.  A ~
      history datapoint must be referenced by a non-negative integer."
    variable-or-parameter? number-of-datapoints-ago))
  (setq result?
	(if variable-or-parameter?
	    (if (or (eq current-environment 'simulator)
		    (eq current-environment 'simulated-value))
		(get-value-of-previous-datapoint
		  variable-or-parameter? t number-of-datapoints-ago)
		(get-value-of-previous-datapoint
		  variable-or-parameter? nil number-of-datapoints-ago))
	    nil))
  (cond (result?
	 ;; The following reclaims the result argument, when necessary.  This is
	 ;; needed because the history value reference copies any managed values
	 ;; (i.e., text).
	 (setq return-value?
	       (make-evaluation-value-reclaiming-argument
		 result?
		 (type-specification-of-variable-or-parameter-value
		   variable-or-parameter?)))
	 (setq result? nil))
	((null variable-or-parameter?)
	 ;; No-item must be allowed.  Or, this would not be possible.
	 (setq return-value? nil))
	((=f unknown-allowed truth)
	 (setq stack-expiration nil)
	 (setq return-value? nil))
	((=f no-item-allowed truth)
	 (setq return-value? nil))
	(t
	 (stack-error
	   top-of-stack
	   "Cannot reference the value of ~NF as of ~d datapoints ago.  ~
            There was no value at that time."
	   variable-or-parameter? number-of-datapoints-ago)))
    (reclaim-evaluation-quantity (stack-arg 1))
    (reclaim-evaluation-truth-value (stack-arg 2))
    (reclaim-evaluation-truth-value (stack-arg 3))
    (decff top-of-stack 3)
    (setf (svref local-stack top-of-stack) return-value?)
    nil))


;; Obsolete
;(def-in-line-evaluator value-of-previous-datapoint
;		   (54 all ((class variable-or-parameter) integer)
;		       (or datum (no-item)) t)
;  (setq register-2 (stack-arg 0))		       ; variable or parameter
;  (setq register-3 (stack-arg 1))		       ; number of data points
;  (cond ((<f register-3 0)
;	 (stack-error
;	   top-of-stack
;	   "Cannot reference the value of ~NF as of ~d datapoints ago.  A ~
;            history datapoint should be referenced by a non-negative integer."
;	   register-2 register-3))
;	(t
;	 (setq register-1 
;	       (if (eq current-environment 'simulator)
;		   (get-value-of-previous-datapoint register-2 t register-3)
;		   (get-value-of-previous-datapoint register-2 nil register-3)))
;	 (setq register-1
;	       (if register-1
;		   (make-evaluation-value 
;		     register-1
;		     (type-specification-of-variable-or-parameter-value
;		       register-2))
;		   (make-evaluation-symbol nil)))
;	 (reclaim-evaluation-quantity register-3))))

(def-in-line-evaluator is-nan
		       (54 all (float) boolean t pprint-functional-evaluator)
  (setq register-2 (stack-arg 0))
  (setq register-1 
    (if (nanp (evaluation-float-value register-2))
        (make-evaluation-truth-value truth)
        (make-evaluation-truth-value falsity)))
  (reclaim-evaluation-float register-2))

(setf (argument-range 'is-nan) 1)

;;; The `INTERPOLATED-VALUE stack-evaluator' returns the value of a variable or
;;; parameter as of a given time interval ago.  If a value was collected at that
;;; time, it is returned.  If no value was collected at that time, it returns
;;; the straight line interpolation of the values collected before and after
;;; that time.  If a value can not be computed, either unknown is returned, no
;;; value is returned, or an error is signaled.  This depends on whether the
;;; instruction allows unknown-datum and/or no-item.

;;; This evaluator accepts a variable or parameter designation argument and a
;;; time interval argument.  This evaluator is available in the inference
;;; engine, procedures, and the simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

;;; INTERPOLATED-VALUE (variable-or-parameter, interval)

(def-expiration-source-operator interpolated-value)

(def-default-special-form-converter interpolated-value)

(def-history-preferred-instruction-chooser interpolated-value)

(def-history-stack-node-instruction-emitter interpolated-value)



;;; Instruction 66, the `INTERPOLATED-VALUE funcalled stack-instruction' is the
;;; instruction used to implement the evaluator for Interpolated-value.  It
;;; accepts a variable-or-parameter and an interval argument.  The return value
;;; and error handling depends on the value of the unknown-datum and no-item
;;; flags.

;;; This instruction always returns a number, unknown, no value, or signals an
;;; error.

(def-funcalled-instruction interpolated-value (66 all 4 1 nil pprint-interpolated-value-instruction)
  (let* ((variable-or-parameter? (stack-arg 0))
	 (interval-ago (evaluation-quantity-value (stack-arg 1)))
	 (unknown-allowed (evaluation-truth-value-value (stack-arg 2)))
	 (no-item-allowed (evaluation-truth-value-value (stack-arg 3)))
	 (result?
	   (if variable-or-parameter?
	       (if (or (eq current-environment 'simulator)
		       (eq current-environment 'simulated-value))
		   (get-interpolated-delayed-value
		     variable-or-parameter? t 
		     (- (managed-float-value
			  (extract-number-from-compound-fixnum-simulation-time
			    (get-current-time-in-simulation-environment)))
			interval-ago))
		   (get-interpolated-delayed-value
		     variable-or-parameter? nil 
		     (- (managed-float-value (clock-get current-g2-time))
			interval-ago
			(managed-float-value (clock-get g2-time-at-start)))))
	       nil))
	 return-value?)
  (cond (result?
	 (setq return-value? (make-evaluation-quantity result?)))
	((null variable-or-parameter?)
	 ;; No-item must be allowed.  Or, this would not be possible.
	 (setq return-value? nil))
	((=f unknown-allowed truth)
	 (setq stack-expiration nil)
	 (setq return-value? nil))
	((=f no-item-allowed truth)
	 (setq return-value? nil))
	(t
	 (stack-error
	   top-of-stack
	   "Cannot reference the value of ~NF as of ~NC ago.  ~
           There was no value at that time."
	   variable-or-parameter? interval-ago 'seconds)))
    (reclaim-evaluation-quantity (stack-arg 1))
    (reclaim-evaluation-truth-value (stack-arg 2))
    (reclaim-evaluation-truth-value (stack-arg 3))
    (decff top-of-stack 3)
    (setf (svref local-stack top-of-stack) return-value?)
    nil))






;;;; Animation Expression Evaluators



;; Where are the following evaluated?  Are they system attributes??
;;
;; item-x-position
;; item-y-position
;; item-height
;; item-width
;; item-heading



(def-stack-error item-distance-eval-error (item1 item2 top-of-stack)
  "The distance between ~NF and ~NF could not be computed, ~
   since they were not on the same workspace."
  item1
  item2)

;;; The `DISTANCE-BETWEEN stack-evaluator' returns the distance in workspace
;;; units between the centers of two items on the same workspace.  This
;;; evaluator is only available in the inference engine and procedures.

;;; DISTANCE-BETWEEN (item, item)

(def-in-line-evaluator distance-between
		       (55 (inference procedure) ((class item) (class item))
			   float nil pprint-distance-between-evaluator)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1
	(distance-between-icons-if-in-same-workspace register-2 register-3))
  (unless register-1
    (item-distance-eval-error register-2 register-3 top-of-stack))
  (make-evaluation-float register-1))


;;; The `DISTANCE-BETWEEN-AND-THE-NEAREST stack-evaluator' returns the distance
;;; in workspace units between the center of an item and the center of the
;;; nearest item of a given class on the same workspace.  This evaluator is only
;;; available in the inference engine and procedures.

;;; INFERENCE: returns unknown if not item is found.
;;; PROCEDURE: signals an error if no item is found.

;; Why does distance-between-and-the-nearest test whether an object is being
;; moved and distance-between does not!!

;; This operator is a source node since it can return unknown.

(def-expiration-source-operator distance-between-and-the-nearest)

(def-stack-error no-item-of-class-eval-error (class top-of-stack)
  "Could not locate a non-active item of type ~a." class)

(def-funcalled-evaluator distance-between-and-the-nearest
			 (item class)
			 (26 (inference procedure)
			     ((class item) symbol) float
			     funcall-eval-type-2-arg
			     nil
			     pprint-distance-between-and-the-nearest-evaluator)
  (let* ((class-name (evaluation-symbol-symbol class))
	 (class-description? (class-description class-name))
	 (result-float nil))
    (setq result-float
	  (let ((closest-instance?
		  (if (and class-description?
			   (class-description-of-class-p
			     class-description? 'item))
		      (find-nearest-active-instance-of-class-to-entity
			class-description? item))))
	    (cond
	      (closest-instance?
	       (distance-between-icons-if-in-same-workspace
		 closest-instance? item))
	      ((eq current-environment 'inference-engine)
	       ;; If in the inference environment, return "unknown".
	       (setq stack-expiration nil)
	       1.0)
	      (t
	       ;; Else, in the procedure environment.
	       (no-item-of-class-eval-error
		 class-name cached-top-of-stack)))))
  (reclaim-evaluation-symbol class)
  (make-evaluation-float result-float)))



;;; The function `distance-between-icons-if-in-same-workspace' returns the
;;; distance, in workspace units, between entity1 and entity2, provided they are
;;; located on the same workspace.  This assumes that it can do gensym
;;; arithmetic.

(defun distance-between-icons-if-in-same-workspace (entity1 entity2)
  (let ((workspace? (get-workspace-if-any entity1)))
    (if (and workspace?
	     (eq workspace? (get-workspace-if-any entity2)))
	(let ((delta-x
		(coerce-to-gensym-float
		  (-w (item-x-position entity1) (item-x-position entity2))))
	      (delta-y
		(coerce-to-gensym-float
		  (-w (item-y-position entity1) (item-y-position entity2)))))
	  (sqrte (+e (*e delta-x delta-x) (*e delta-y delta-y)))))))

;; THERE SHOULD BE A SYSTEM TABLE VALIDITY INTERVAL PARAMETER FOR SUCH
;; DISTANCES, SINCE THE ENTITIES MAY MOVE!!!

;; Consider using, for speed:
;;    (defun integer-approximation-to-distance-in-workspace (delta-x delta-y)
;;      (isqrt (+ (* delta-x delta-x) (* delta-y delta-y)))).

;; Consider the following, which is almost as fast as the integer approximation.
;; -jra 4/6/92
;;(let ((fixnum-delta-x
;;	(-w (icon-x-position entity1) (icon-x-position entity2)))
;;      (fixnum-delta-y
;;	(-w (icon-y-position entity1) (icon-y-position entity2))))
;;  (make-evaluation-float 
;;    (sqrte (+e (*e (coerce-fixnum-to-gensym-float fixnum-delta-x)
;;		   (coerce-fixnum-to-gensym-float fixnum-delta-x))
;;	       (*e (coerce-fixnum-to-gensym-float fixnum-delta-y)
;;		   (coerce-fixnum-to-gensym-float fixnum-delta-y))))))






;;;; Color Expression Evaluators




;;; Icon color has become a role in 2.0.






;;;; Value and Current Value Expression Evaluators




;;; The `HAS-A-CURRENT-VALUE stack-evaluator' checks if an expression or
;;; variable has a current value, without attempting to compute any new values
;;; for variables which do not have current values.  The evaluator accepts one
;;; argument.  If there is a current value, truth is returned.  Otherwise,
;;; falsity is returned.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.  This evaluator is available in the
;;; inference engine and procedures.

(def-special-form-converter has-a-current-value (expression)
  (let ((arguments (stack-cons (convert-expression-to-stack-node-tree
				 (second expression))
			       nil))
	(stack-node-instruction
	  (make-stack-node-instruction 'has-a-current-value nil)))
    (setf (stack-node-argument-nodes stack-node-instruction) arguments)
    stack-node-instruction))



;;; The preferred instruction chooser for HAS-A-CURRENT-VALUE chooses
;;; instructions and types on its arguments, and then sets its own return value,
;;; depending on whether any of its arguments can return unknown.

;;; FUNCTIONALITY CHANGE!!
;;;
;;; In Version 2, the expiration of Has A Current Value (and Has No Current
;;; Value) was always indefinite.
;;;
;;; In 3.0, if the argument does have a current value and its expiration is not
;;; indefinite, then the expiration of the Has A Current Value result is the
;;; same as the expiration of the argument.  If the argument does not have a
;;; current value, then the expiration of this expression is indefinite, just as
;;; in 2.0.  -jra & cpm 5/2/91

(declare-optimizer-stack-instruction has-a-current-value)

(def-preferred-instruction-chooser has-a-current-value
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type)))
    (setf (car argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (car argument-nodes)
	    '(or datum (unknown-datum) (no-item) (no-item-implies-unknown))))
    (setf (stack-node-value-type stack-node-instruction) 'boolean)
    ;; If the expression can return unknown, cache the data-seeking flag
    ;; regardless of whether the return type allows unknown.
    (when (type-specification-subtype-p
	    '(unknown-datum)
	    (stack-node-value-type (car argument-nodes)))
      (unless (stack-node-instruction-extra-info stack-node-instruction)
	(setf (stack-node-instruction-extra-info stack-node-instruction)
	      (phrase-list (generate-new-stack-frame-var-spot 'truth-value)
			   (if unknown-allowed?
			       (generate-new-stack-frame-var-spot 'datum)
			       nil)))))))

(def-expiration-special-form has-a-current-value)

(def-stack-node-instruction-emitter has-a-current-value
  (let* ((surrounding-data-seeking-cache-var? (car extra-info))
	 (previous-expiration-cache? (second extra-info))
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (value-could-be-unknown?
	   (type-specification-subtype-p
	     '(unknown-datum) (stack-node-value-type (car argument-nodes))))
	 (known-value-tag?
	   (and value-could-be-unknown? (generate-new-goto-tag)))
	 (has-a-value-tag (generate-new-goto-tag))
	 (end-of-expression-tag (generate-new-goto-tag)))

    (cond (value-could-be-unknown?
	   ;; The expression can return unknown regardless of whether the required
	   ;; type allows unknown.  This means that this expression can be inside
	   ;; or outside of a Collect Data statement.  When in a Collect Data, the
	   ;; previous expiration is being cached and minimized with the result of
	   ;; this expresssion, which is NEVER.  In both cases, the data-seeking
	   ;; flag is cached, data seeking is turned off during the evaluation of
	   ;; this expression, and the cached data-seeking flag is restored.

	   ;; Cache the old data seeking flag, and turn data seeking off.
	   (emit-instruction-byte-code
	     byte-code-stream 'push-from-allow-data-seeking)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream surrounding-data-seeking-cache-var?)
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value falsity))
	   (emit-instruction-byte-code
	     byte-code-stream 'pop-into-allow-data-seeking)

	   ;; Cache the previous expiration and reset the global.
	   (when previous-expiration-cache?
	     (emit-instruction-byte-code byte-code-stream 'push-expiration)
	     (call-stack-instruction-emitter pop-into-surrounding-local-var
	       byte-code-stream previous-expiration-cache?)
	     (emit-instruction-byte-code byte-code-stream 'reset-expiration))

	   ;; Evaluate the argument, pop the discarded value, and branch if
	   ;; known.
	   (emit-stack-node-tree byte-code-stream (first argument-nodes))
	   (call-stack-instruction-emitter branch-long-if-known
	     byte-code-stream known-value-tag?)

	   ;; Unknown value.
	   (emit-instruction-byte-code byte-code-stream 'pop)
	   (emit-instruction-byte-code byte-code-stream 'reset-expiration)
	   ;; When caching, minimize NEVER with the previous expiration.
	   (when previous-expiration-cache?
	     (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	       byte-code-stream previous-expiration-cache?)
	     (emit-instruction-byte-code byte-code-stream 'minimize-expiration))
	   ;; Return value
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value falsity))
	   (call-stack-instruction-emitter branch-long byte-code-stream end-of-expression-tag)
	   
	   ;; Known value.
	   (register-tag-in-byte-code-stream byte-code-stream known-value-tag?)
	   ;; When caching, minimize the expiration of this expression with the
	   ;; previous expiration.
	   (when previous-expiration-cache?
	     (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	       byte-code-stream previous-expiration-cache?)
	     (emit-instruction-byte-code byte-code-stream 'minimize-expiration))
	   (emit-instruction-byte-code byte-code-stream 'none-test)
	   (call-stack-instruction-emitter branch-long-if-not-true
	       byte-code-stream has-a-value-tag)

	   ;; No Value.
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value falsity))
	   (call-stack-instruction-emitter branch-long byte-code-stream end-of-expression-tag)
	   
	   ;; Has A Value.
	   (register-tag-in-byte-code-stream byte-code-stream has-a-value-tag)
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value truth))
	   
	   ;; Reinstate the previous data seeking flag.
	   (register-tag-in-byte-code-stream
	     byte-code-stream end-of-expression-tag)
	   (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream surrounding-data-seeking-cache-var?)
	   (emit-instruction-byte-code
	     byte-code-stream 'pop-into-allow-data-seeking))

	  (t
	   ;; The expression is always evaluated, even though it can not return
	   ;; unknown.  The expression may contain a reference to an unbound
	   ;; local variable.  Evaluating this type of expression signals an
	   ;; error.
						       ; This needs to be
						       ; reviewed.  In version
						       ; 2.1, reference of an
						       ; unbound local variable
						       ; was an error.  A fix
						       ; was added in the 3.0
						       ; code because an
						       ; expression that is
						       ; expected to have a
						       ; value was not being
						       ; evaluated.  Therefore,
						       ; an unbound local
						       ; variable was thought to
						       ; have a value.  - cpm,
						       ; 11/22/91
	   ;; Evaluate the argument and test for no value.
	   (emit-stack-node-tree byte-code-stream (first argument-nodes))
	   (emit-instruction-byte-code byte-code-stream 'none-test)
	   (call-stack-instruction-emitter branch-long-if-not-true
	     byte-code-stream has-a-value-tag)
	   
	   ;; No Value.
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value falsity))
	   (call-stack-instruction-emitter branch-long byte-code-stream end-of-expression-tag)
	   
	   ;; Has A Value.
	   (register-tag-in-byte-code-stream byte-code-stream has-a-value-tag)
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value truth))
	   
	   (register-tag-in-byte-code-stream
	     byte-code-stream end-of-expression-tag)))))



;;; The `HAS-NO-CURRENT-VALUE stack-evaluator' checks if an expression or
;;; variable has no current value, without attempting to compute any new values
;;; for variables which do not have current values.  The evaluator accepts one
;;; argument.  If there is a current value, falsity is returned.  Otherwise,
;;; truth is returned.

;;; FUNCTIONALITY CHANGE!!!  Similar to Has A Current Value, this operation can
;;; now return expirations that are not indefinite.  See has a current value for
;;; a full description.  -jra & cpm 5/2/91

(def-special-form-converter has-no-current-value (expression)
  (convert-expression-to-stack-node-tree
    (phrase-list 'not (phrase-cons 'has-a-current-value (cdr expression)))))



;;; The `HAS-A-VALUE stack-evaluator' checks if an expression or variable has a
;;; value and attempts to compute the value for a variable that does not
;;; currently have a value.  It accepts an expression argument and returns
;;; truth, falsity or unknown.  If either a current value or a computed value is
;;; available, then truth is returned.  If no value is found and either the rule
;;; has timed out, a variable referenced in the expression has failed, or all
;;; the variables referenced in the expression either returned values or did not
;;; exists, then falsity is returned.  Otherwise, unknown is returned.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.  This instruction does not
;;; test the environment at run-time.

;; FUNCTIONALITY CHANGE!!  This expression can be executed within procedures in
;; G2 version 3.0, but not in 2.1.

(def-special-form-converter has-a-value (expression)
  (let ((arguments (stack-cons (convert-expression-to-stack-node-tree
				 (second expression))
			       nil))
	(stack-node-instruction
	  (make-stack-node-instruction 'has-a-value nil)))
    (setf (stack-node-argument-nodes stack-node-instruction) arguments)
    stack-node-instruction))



;;; The preferred instruction chooser for HAS-A-VALUE chooses instructions and
;;; types on its arguments, and then sets its own return value, depending on
;;; whether any of its arguments can return unknown.

;;; FUNCTIONALITY CHANGE!!
;;;
;;; 1. In Version 2, the expiration of has-a-value (and has-no-value) was
;;; always indefinite.  In 3.0, if the argument does have a value, but its
;;; expiration is not indefinite, then the expiration of the result of has a
;;; value is the same as the expiration of the argument.  If the result is
;;; false, then the expiration of this expression is indefinite, just as in 2.0.
;;; -jra & cpm 5/2/91 (This comment was from has-a-current-value, but also
;;; applies here.  -cpm)
;;;
;;; 2. In Version 2, this instruction was not available in procedures, but in
;;; 3.0 can be in procedure statements that allow unknown.


(declare-optimizer-stack-instruction has-a-value)

(def-preferred-instruction-chooser has-a-value
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    (unless (type-specification-subtype-p '(unknown-datum) required-type)
      ;; Previously tested the value type in
      ;; rewrite-stack-node-trees-for-unknown.
      (compiler-error
	"The HAS A VALUE expression can only be executed in contexts where ~
         unknown can be returned, such as within a rule or a COLLECT DATA ~
         statement in procedures.  The HAS A CURRENT VALUE expression does not ~
	 have this restriction and could be used here."))
    (setf (car argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (car argument-nodes)
	    '(or datum (unknown-datum) (no-item) (no-item-implies-unknown))))
    (let ((no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	  (argument-could-be-unknown?
	    (type-specification-subtype-p
	      '(unknown-datum)
	      (stack-node-value-type (car argument-nodes)))))
      (setf (stack-node-value-type stack-node-instruction)
	      (maybe-add-unknown 'boolean (or argument-could-be-unknown? no-item-implies-unknown-allowed?)))
      (when argument-could-be-unknown?
	(unless (stack-node-instruction-extra-info stack-node-instruction)
	  (setf (stack-node-instruction-extra-info stack-node-instruction)
		(phrase-list (generate-new-stack-frame-var-spot 'truth-value)
			     (generate-new-stack-frame-var-spot 'datum))))))))

(def-expiration-special-form has-a-value)

(def-stack-node-instruction-emitter has-a-value
  (let* ((surrounding-data-seeking-cache-var? (car extra-info))
	 (previous-expiration-cache? (second extra-info))
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    (cond (surrounding-data-seeking-cache-var?
	   ;; Cache the old data seeking flag, and set to the default.
	   (emit-instruction-byte-code
	     byte-code-stream 'push-from-allow-data-seeking)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream surrounding-data-seeking-cache-var?)
	   (emit-instruction-byte-code
	     byte-code-stream 'push-from-default-allow-data-seeking)
	   (emit-instruction-byte-code
	     byte-code-stream 'pop-into-allow-data-seeking)
	   
	   ;; Cache the previous expiration and reset the global.
	   (emit-instruction-byte-code byte-code-stream 'push-expiration)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream previous-expiration-cache?)
	   (emit-instruction-byte-code byte-code-stream 'reset-expiration)
	   
	   (emit-instruction-byte-code byte-code-stream 'push-wake-ups-count)
	   
	   ;; Evaluate the argument.  The value is popped by has-a-value.
	   (emit-stack-node-tree byte-code-stream (first argument-nodes))
	   (call-stack-instruction-emitter funcall-instruction byte-code-stream 'has-a-value)
	   
	   (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	     byte-code-stream previous-expiration-cache?)
	   (emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	   
	   ;; Reinstate the previous data seeking flag.
	   (call-stack-instruction-emitter push-from-surrounding-local-var
	     byte-code-stream surrounding-data-seeking-cache-var?)
	   (emit-instruction-byte-code
	     byte-code-stream 'pop-into-allow-data-seeking))
	  (t
	   ;; The expression is always evaluated, even though it can not return
	   ;; unknown.  The expression may contain a reference to an unbound
	   ;; local variable.  Evaluating this type of expression signals an
	   ;; error.
						       ; This needs to be
						       ; reviewed.  In version
						       ; 2.1, reference of an
						       ; unbound local variable
						       ; was an error.  A fix
						       ; was added in the 3.0
						       ; code because an
						       ; expression that is
						       ; expected to have a
						       ; value was not being
						       ; evaluated.  Therefore,
						       ; an unbound local
						       ; variable was thought to
						       ; have a value.  - cpm,
						       ; 11/22/91
	   (let ((has-a-value-tag (generate-new-goto-tag))
		 (end-of-expression-tag (generate-new-goto-tag)))

	     ;; Evaluate the argument and test for no value.
	     (emit-stack-node-tree byte-code-stream (first argument-nodes))
	     (emit-instruction-byte-code byte-code-stream 'none-test)
	     (call-stack-instruction-emitter branch-long-if-not-true
	       byte-code-stream has-a-value-tag)
	     
	     ;; No Value.
	     (call-stack-instruction-emitter push-constant
	       byte-code-stream (make-evaluation-truth-value falsity))
	     (call-stack-instruction-emitter branch-long byte-code-stream end-of-expression-tag)
	     
	     ;; Has A Value.
	     (register-tag-in-byte-code-stream byte-code-stream has-a-value-tag)
	     (call-stack-instruction-emitter push-constant
	       byte-code-stream (make-evaluation-truth-value truth))
	     
	     (register-tag-in-byte-code-stream
	       byte-code-stream end-of-expression-tag))))))



;;; Instruction 35, the `HAS-A-VALUE funcalled stack-instruction' is used to
;;; implement the evaluator for has-a-value.  This instruction takes a wake-up
;;; count and a value stack arguments.  This count was pushed onto the stack
;;; before the value expression was evaluated.  The stack-expiration should
;;; contain the expiration that results from evaluating the value expression.

;;; Before this instruction is called the previous expiration and data-seeking
;;; flags are cached, the data-seeking is turned on, the value argument has
;;; already been evaluated, the expiration of the value is still in the
;;; expiration variable.

(def-funcalled-instruction has-a-value (35 (inference procedure) 2 1 nil
					   pprint-has-a-value-instruction)
  (let* ((wake-ups-count (evaluation-integer-value (stack-arg 0)))
	 (new-wake-ups-count (length *variables-that-did-not-have-values*))
	 (value? (stack-arg 1))
	 (result
	   (cond
	     (stack-expiration
	      (if (and value? (evaluation-value-value value?)) truth falsity))
	     ((or (final-evaluation-attempt?)
		  (<=f new-wake-ups-count wake-ups-count)
		  (loop for variable-cons = *variables-that-did-not-have-values*
					  then (cdr variable-cons)
			for count = 1 then (incff count)
			with end-count = (-f new-wake-ups-count wake-ups-count)
			until (>f count end-count)
			thereis (failed-p (car variable-cons))))
	      (setq stack-expiration 'never)
	      falsity)
	     ;; Unknown.
	     (t (setq stack-expiration nil)
		falsity))))
    (reclaim-evaluation-integer (stack-arg 0))
    (reclaim-if-evaluation-value (stack-arg 1))

    ;; Push the return value and return the new top-of-stack.
    (decff top-of-stack 1)
    (setf (svref local-stack top-of-stack)
	  (make-evaluation-truth-value result))
    nil))




;;; The `HAS-NO-VALUE stack-evaluator' checks if an expression or variable has
;;; no value and attempts to compute the value for a variable that does not
;;; currently have a value.  It accepts an expression argument and returns truth
;;; or falsity.  If a value is found, falsity is returned.  If no value is found
;;; and either the rule has timed out, a variable referenced in the expression
;;; has failed, or all the variables referenced in the expression either
;;; returned values or did not exists, then truth is returned.  Otherwise,
;;; unknown is returned.  This evaluator is available in the inference engine,
;;; procedures, and the simulator.

;;; FUNCTIONALITY CHANGE!!
;;;
;;; Similar to has a value, this operation can now return expirations that are
;;; not indefinite.  See has a current value for a full description.
;;;
;; This expression can be executed within procedures in G2 version 3.0, but not
;; in 2.1.

(def-special-form-converter has-no-value (expression)
  (convert-expression-to-stack-node-tree
    (phrase-list 'not (phrase-cons 'has-a-value (cdr expression)))))



(declare-instruction-for-optimizer
  'current-value-of
  '(no-wait-states
    cannot-read-local-variables
    cannot-write-local-variables
    cannot-read-roles
    cannot-write-roles))

;;; The `CURRENT-VALUE-OF stack-evaluator' is used to force an evaluation for an
;;; expression, with variables using only their current values, and not
;;; attempting to compute any new values through data serving, backward chaining
;;; or formula evaluation.  The evaluator accepts one argument.  If the
;;; expression has a current value, then the value is returned.  If the
;;; expression refers to an item that does not exist or if the item does not
;;; currently have a value, then unknown is returned.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.  This evaluator is only available in the
;;; inference engine and procedures.

;; FUNCTIONALITY CHANGE!!  This expression can be executed within procedures in
;; G2 version 3.0, but not in 2.1.

(def-special-form-converter current-value-of (expression)
  (let ((arguments (stack-cons (convert-expression-to-stack-node-tree
				 (second expression))
			       nil))
	(stack-node-instruction
	  (make-stack-node-instruction 'current-value-of nil)))
    (setf (stack-node-argument-nodes stack-node-instruction) arguments)
    stack-node-instruction))

(def-preferred-instruction-chooser current-value-of
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(no-item-allowed?
	  (type-specification-subtype-p '(no-item) required-type))
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type)))
    (setf (car argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (car argument-nodes)
	    (if (type-specification-subtype-p
		  required-type
		  '(or datum (unknown-datum) (no-item)))
		required-type
		(maybe-add-unknown
		  (maybe-add-no-item 'datum no-item-allowed?)
		  unknown-allowed?))))
    (setf (stack-node-value-type stack-node-instruction)
	  (stack-node-value-type (car argument-nodes)))

    ;; changed from a "when unknown to a cond which sets extra info to nil if
    ;; not unknown  
    (cond ((and (type-specification-subtype-p
		  '(unknown-datum)
		  (stack-node-value-type (car argument-nodes)))
		unknown-allowed?)
	   (unless (stack-node-instruction-extra-info stack-node-instruction)
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   (phrase-list (generate-new-stack-frame-var-spot 'truth-value)))))
	  (t
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   nil))
	     )))

(def-expiration-special-form current-value-of)

(def-stack-node-instruction-emitter current-value-of
  (let* ((surrounding-data-seeking-cache-var? (car extra-info))
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    (cond (surrounding-data-seeking-cache-var?
	   ;; Cache the old data seeking flag, and turn data seeking off.
	   (emit-instruction-byte-code
	     byte-code-stream 'push-from-allow-data-seeking)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream surrounding-data-seeking-cache-var?)
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-truth-value falsity))
	   (emit-instruction-byte-code
	     byte-code-stream 'pop-into-allow-data-seeking)
	   
	   ;; Evaluate the expression.
	   (emit-stack-node-tree byte-code-stream (first argument-nodes))
	   
	   ;; Reinstate the previous data seeking flag.
	   (call-stack-instruction-emitter push-from-surrounding-local-var
	     byte-code-stream surrounding-data-seeking-cache-var?)
	   (emit-instruction-byte-code
	     byte-code-stream 'pop-into-allow-data-seeking))
	  (t
	   ;; Since the expression can not be unknown (i.e., does not affect the
	   ;; expiration), data seeking does not need to be turned off.  Just
	   ;; leave the value on the stack.
	   (emit-stack-node-tree byte-code-stream (first argument-nodes))))))




;;; The `VALUE-OF stack-evaluator' is used to force an evaluation of an
;;; expression, with variables attempting to obtain new values if they do not
;;; have a current value.  The evaluator accepts one argument.  This evaluator
;;; is available in the inference engine, procedures, and the simulator.  When
;;; the type of this expression includes unknown, a current value or computed
;;; value is returned.  Otherwise, the current value, if any, is returned.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.

;;; Note that to keep G2 version 2.1 compatible with 3.0, Value Of is being
;;; allowed even if the required type does not allow unknown.  In this case, no
;;; new value is computed.  A current value, if any, is returned.

(def-special-form-converter value-of (expression)
  (let ((arguments (stack-cons (convert-expression-to-stack-node-tree
				 (second expression))
			       nil))
	(stack-node-instruction (make-stack-node-instruction 'value-of nil)))
    (setf (stack-node-argument-nodes stack-node-instruction) arguments)
    stack-node-instruction))


(declare-instruction-for-optimizer
  'value-of
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))

(def-preferred-instruction-chooser value-of
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(no-item-allowed?
	  (type-specification-subtype-p '(no-item) required-type)))
    (setf (car argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (car argument-nodes)
	    (if (type-specification-subtype-p
		  required-type
		  '(or datum (unknown-datum) (no-item)))
		required-type
		(maybe-add-unknown
		  (maybe-add-no-item 'datum no-item-allowed?)
		  unknown-allowed?))))
    (setf (stack-node-value-type stack-node-instruction)
	  (stack-node-value-type (car argument-nodes)))
    (cond ((and (type-specification-subtype-p
		  '(unknown-datum)
		  (stack-node-value-type (car argument-nodes)))
		unknown-allowed?)
	   (unless (stack-node-instruction-extra-info stack-node-instruction)
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   (phrase-list (generate-new-stack-frame-var-spot 'truth-value)))))
	  (t
	   (setf (stack-node-instruction-extra-info stack-node-instruction)
		 nil)))
    ))

(def-expiration-special-form value-of)

(def-stack-node-instruction-emitter value-of
  (let* ((surrounding-data-seeking-cache-var? (car extra-info))
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    (cond (surrounding-data-seeking-cache-var?
	   ;; Cache the old data seeking flag and set the flag to the default.
	   (emit-instruction-byte-code
	     byte-code-stream 'push-from-allow-data-seeking)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream surrounding-data-seeking-cache-var?)
	   (emit-instruction-byte-code
	     byte-code-stream 'push-from-default-allow-data-seeking)
	   (emit-instruction-byte-code
	     byte-code-stream 'pop-into-allow-data-seeking)
	   
	   ;; Evaluate the expression.
	   (emit-stack-node-tree byte-code-stream (first argument-nodes))
	   
	   ;; Reinstate the previous data seeking flag.
	   (call-stack-instruction-emitter push-from-surrounding-local-var
	     byte-code-stream surrounding-data-seeking-cache-var?)
	   (emit-instruction-byte-code
	     byte-code-stream 'pop-into-allow-data-seeking))
	  (t
	   ;; Since the expression can not be unknown (i.e., does not affect the
	   ;; expiration), data seeking does not need to be turned off.  Just
	   ;; leave the value on the stack.
	   (emit-stack-node-tree byte-code-stream (first argument-nodes))))))




(declare-instruction-for-optimizer
 'first-that-has-a-current-value
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    or-like-flow))

;;; The `FIRST-THAT-HAS-A-CURRENT-VALUE stack-evaluator' is implemented as a
;;; special form.  It evaluates its arguments in turn, stopping evaluation and
;;; returning the value of the first which returns a value.  There is no
;;; backward chaining, data serving, or formula evaluation to get a current
;;; value for any of the expressions.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.  This evaluator is available in the
;;; inference engine and in procedures.

;; FUNCTIONALITY CHANGE!!  In version 2.1, the expression was not allowed in
;; procedures.

(def-special-form-converter first-that-has-a-current-value (expression)
  (let ((arguments
	  (loop for argument in (cdr expression)
		collect (convert-expression-to-stack-node-tree argument)
		using stack-cons))
	(instruction-node
	  (make-stack-node-instruction 'first-that-has-a-current-value nil)))
    (setf (stack-node-argument-nodes instruction-node) arguments)
    instruction-node))


;;; The preferred instruction chooser for FIRST-THAT-HAS-A-CURRENT-VALUE chooses
;;; instructions and types on its arguments, and then sets its own return value,
;;; depending on whether any of its arguments can return unknown.

;;; If unknown is not a subtype of the required type, the type of the last
;;; expression must not include unknown.

(def-preferred-instruction-chooser first-that-has-a-current-value
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(primary-argument-required-type
	  (primary-type-of-type-specification required-type))
	(primary-value-type nil)
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
;	(no-item-allowed?
;	  (type-specification-subtype-p '(no-item) required-type))
	(unknown-argument? nil)
	(unknown-last-argument? nil))
    (unless (type-specification-subtype-p primary-argument-required-type 'datum)
      (setq primary-argument-required-type 'datum))
    (loop with but-last-argument-type =
	  (make-type-specification-union
	    primary-argument-required-type '(or (no-item) (unknown-datum)
					     (no-item-implies-unknown)))
	  with last-argument-type =
	  (make-type-specification-union
	    primary-argument-required-type '(or (no-item) (unknown-datum)
					     (no-item-implies-unknown)))
					; Passing no-item and
					; unknown-datum.  This
					; allows the last arg
					; type to include
					; unknown, which can then
					; give a compiler error.
					; Otherwise, 2 warnings are
					; produced about the last
					; arg not being a
					; parameter, and it is
					; still ok!!  - cpm, 11/15/91
;	    (maybe-add-unknown
;	      (maybe-add-no-item
;		primary-argument-required-type no-item-allowed?)
;	      unknown-allowed?)
	  with argument-type = nil
	  for argument-node-cons on argument-nodes
	  do
      (setf (car argument-node-cons)
	    (choose-stack-node-instructions-and-types
	      (car argument-node-cons)
	      (if (cdr argument-node-cons)
		  but-last-argument-type
		  last-argument-type)))
      (setq argument-type (stack-node-value-type (car argument-node-cons)))
      ;; If no primary type or existing primary value type is a subtype of this
      ;; argument type, then replace the primary type with this argument type.
      (setq primary-value-type
	    (most-general-primary-type argument-type primary-value-type))
      (when (type-specification-subtype-p '(unknown-datum) argument-type)
	(setq unknown-argument? t)
	(when (null (cdr argument-node-cons))
	  (setq unknown-last-argument? t)))
	  finally
	    (when (and unknown-last-argument? (not unknown-allowed?))
	      (compiler-error
		"~a ~a"
		"The last expression within the FIRST OF THE FOLLOWING EXPRESSIONS "
		"THAT HAS A CURRENT VALUE must not produce an unknown value.")))
    (cond (unknown-argument?
	   (setf (stack-node-value-type stack-node-instruction)
		 (make-type-specification-union
		   primary-value-type '(unknown-datum)))
	   (unless (stack-node-instruction-extra-info stack-node-instruction)
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   (phrase-list (generate-new-stack-frame-var-spot 'datum)
				(generate-new-stack-frame-var-spot 'datum)))))
	  (t
	   (setf (stack-node-value-type stack-node-instruction)
		 primary-value-type)
	   ;; Changed to always create 2 var-spots.  See the emitter.  - cpm,
	   ;; 12/9/91
;	   (setf (stack-node-instruction-extra-info stack-node-instruction)
;		 nil)
	   (unless (stack-node-instruction-extra-info stack-node-instruction)
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   (phrase-list (generate-new-stack-frame-var-spot 'datum)
				(generate-new-stack-frame-var-spot 'datum))))))))


;;; The function `most-general-primary-type' takes a type specification and a
;;; type specification or nil.  It returns the most general primary type of the
;;; two.

(defun most-general-primary-type (argument-type type?)
  (let ((primary-argument-type
	  (primary-type-of-type-specification argument-type))
	(primary-value-type
	  (and type? (primary-type-of-type-specification type?))))
    ;; If no primary type or existing primary value type is a subtype of this
    ;; argument type, then replace the primary type with this argument type.
    (cond ((or (null primary-value-type)
	       (type-specification-subtype-p
		 primary-value-type primary-argument-type))
	   (setq primary-value-type primary-argument-type))
	  ;; If this argument type is a subtype of the existing primary value
	  ;; type, then do nothing.
	  ((type-specification-subtype-p
	     primary-argument-type primary-value-type)
	   nil)
	  ;; Otherwise, this argument type is disjoint of the primary value
	  ;; type, set the primary type to datum.  (Note, that we could make
	  ;; unions, but we don't believe that unions are perfect within the
	  ;; subtypep tests.
	  (t
	   (setq primary-value-type 'datum)))
    primary-value-type))



;;; The stack node instruction emitter for FIRST-THAT-HAS-A-CURRENT-VALUE emits
;;; in one of two ways, depending upon whether or not any of its argument nodes
;;; can return unknown.  If the arguments cannot, then this instruction need not
;;; collect expirations from its arguments, or check at all whether or not they
;;; are known.  It only needs to return the first value.

(def-expiration-special-form first-that-has-a-current-value)

(def-stack-node-instruction-emitter first-that-has-a-current-value
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(surrounding-data-seeking-cache-var? (car extra-info))
	(global-expiration-cache-var? (second extra-info)))
    (cond
      ;; The first expression may not have a value, if it is a reference to a
      ;; local variable.  So, loop over each expression.  - cpm, 12/9/91
						       ; If this is changed, see
						       ; the converter also.
;      ((not surrounding-data-seeking-cache-var?)
;       ;; Emit the first expression since it always has a value.
;       (emit-stack-node-tree byte-code-stream (car argument-nodes)))
      (t
       (let ((end-of-instruction-tag (generate-new-goto-tag)))
	 ;; Cache the old data seeking flag, and turn data seeking off.
	 (emit-instruction-byte-code
	   byte-code-stream 'push-from-allow-data-seeking)
	 (call-stack-instruction-emitter pop-into-surrounding-local-var
	   byte-code-stream surrounding-data-seeking-cache-var?)
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value falsity))
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-allow-data-seeking)

	 ;; Cache the global expiration, and reset it to never.
	 (emit-instruction-byte-code byte-code-stream 'push-expiration)
	 (call-stack-instruction-emitter pop-into-surrounding-local-var
	   byte-code-stream global-expiration-cache-var?)
	 (emit-instruction-byte-code byte-code-stream 'reset-expiration)

	 ;; Evaluate the expressions until one has a value.
	 (loop for argument-node-cons on argument-nodes
	       for argument-node = (first argument-node-cons)
	       for known-value-tag = (generate-new-goto-tag)
	       for next-value-tag = (generate-new-goto-tag)
	       do
	   (emit-stack-node-tree byte-code-stream argument-node)
	   (call-stack-instruction-emitter branch-long-if-known
	     byte-code-stream known-value-tag)
	   (call-stack-instruction-emitter branch-long byte-code-stream next-value-tag)

	   ;; Test for a known value of none.  Make a copy of the value first,
	   ;; since the none test pops the value.
	   (register-tag-in-byte-code-stream byte-code-stream known-value-tag)
	   (emit-instruction-byte-code
	      byte-code-stream 'push-copy-of-top-of-stack)
	   (emit-instruction-byte-code byte-code-stream 'none-test)
	   (call-stack-instruction-emitter branch-long-if-not-true
	       byte-code-stream end-of-instruction-tag)

	   ;; If this unknown or no-item value is not the last expression, pop
	   ;; the value and reset the expiration.
	   (register-tag-in-byte-code-stream byte-code-stream next-value-tag)
	   (when (cdr argument-node-cons)
	     (emit-instruction-byte-code byte-code-stream 'pop)
	     (emit-instruction-byte-code byte-code-stream 'reset-expiration)))
	 
	 (register-tag-in-byte-code-stream
	   byte-code-stream end-of-instruction-tag)
	 
	 (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	   byte-code-stream global-expiration-cache-var?)
	 (emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	 
	 ;; Reinstate the previous data seeking flag.
	 (call-stack-instruction-emitter push-from-surrounding-local-var
	   byte-code-stream surrounding-data-seeking-cache-var?)
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-allow-data-seeking))))))





;;; The `FIRST-THAT-HAS-A-VALUE stack-evaluator' will evaluate its arguments in
;;; turn, stopping evaluation and returning the value of the first which returns
;;; a value.  There are three ways that this expression can evaluate.

;;; 1. If the first expression has a value, it is returned.
;;; 2. If the first expression in the list does not have a value, then G2
;;; attempts to evaluate the next expression in the list.
;;; 3. If the first expression in the list has not returned a value, and the rule
;;; or formula has not timed out, and no variable in the expression has failed,
;;; then while that expression is waiting for a value, G2 attempts to evaluate the
;;; rest of the expressions in the list, but does not return their values yet.  If
;;; the first expression finally does not have a value, then G2 uses the first
;;; expression in the rest of the list that does have a value.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.

;;; This evaluator is available in the inference engine, procedure, and the
;;; simulator.

;; FUNCTIONALITY CHANGE!!  In version 2.1, the expression was not allowed in
;; procedures.

(declare-instruction-for-optimizer
  'first-that-has-a-value
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    or-like-flow))

(def-special-form-converter first-that-has-a-value (expression)
  (let ((arguments
	  (loop for argument in (cdr expression)
		collect (convert-expression-to-stack-node-tree argument)
		using stack-cons))
	(instruction-node
	  (make-stack-node-instruction 'first-that-has-a-value nil)))
    (setf (stack-node-argument-nodes instruction-node) arguments)
    instruction-node))



;;; The preferred instruction chooser for FIRST-THAT-HAS-A-VALUE chooses
;;; instructions and types on its arguments, and then sets its own return value,
;;; depending on whether any of its arguments can return unknown.



(def-preferred-instruction-chooser first-that-has-a-value
  (declare (ignore extra-info))
  (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (primary-argument-required-type
	   (primary-type-of-type-specification required-type))
	 (primary-value-type nil)
	 (unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-implies-unknown-allowed? unknown-allowed?)
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (unknown-argument? nil))
    (unless (type-specification-subtype-p '(unknown-datum) required-type)
      ;; Previously tested the value type in
      ;; rewrite-stack-node-trees-for-unknown.
      (compiler-error
	"The FIRST OF THE FOLLOWING EXPRESSIONS THAT HAS A VALUE expression ~
         can only be executed in contexts where ~
         unknown can be returned, such as within a rule or a COLLECT DATA ~
         statement in procedures.  The HAS A CURRENT VALUE form of this ~
         expression does not have this restriction and could be used here."))
    (unless (type-specification-subtype-p primary-argument-required-type 'datum)
      (setq primary-argument-required-type 'datum))
    (loop with but-last-argument-type =
	  (make-type-specification-union
	    primary-argument-required-type '(or (unknown-datum) (no-item) (no-item-implies-unknown)))
	  with last-argument-type =
	  (maybe-add-unknown
	    (maybe-add-no-item-implies-unknown
	      (maybe-add-no-item
		primary-argument-required-type no-item-allowed?)
	      unknown-allowed?)
	    no-item-implies-unknown-allowed?)
	  with argument-type = nil
	  for argument-node-cons on argument-nodes
	  do
      (setf (car argument-node-cons)
	    (choose-stack-node-instructions-and-types
	      (car argument-node-cons)
	      (if (cdr argument-node-cons)
		  but-last-argument-type
		  last-argument-type)))
      (setq argument-type (stack-node-value-type (car argument-node-cons)))
      ;; If no primary type or existing primary value type is a subtype of this
      ;; argument type, then replace the primary type with this argument type.
      (setq primary-value-type
	    (most-general-primary-type argument-type primary-value-type))
      (when (type-specification-subtype-p '(unknown-datum) argument-type)
	(setq unknown-argument? t)))
    (cond (unknown-argument?
	   (setf (stack-node-value-type stack-node-instruction)
		 (make-type-specification-union
		   primary-value-type '(unknown-datum)))
	   (unless (stack-node-instruction-extra-info stack-node-instruction)
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   (phrase-list (generate-new-stack-frame-var-spot 'datum)
				(generate-new-stack-frame-var-spot 'datum)
				(generate-new-stack-frame-var-spot 'datum)))))
	  (t
	   (setf (stack-node-value-type stack-node-instruction)
		 primary-value-type)
	   ;; Changed to always create 3 var-spots.  See the emitter.  - cpm,
	   ;; 12/9/91
;	   (setf (stack-node-instruction-extra-info stack-node-instruction)
;		 nil)
	   (unless (stack-node-instruction-extra-info stack-node-instruction)
	     (setf (stack-node-instruction-extra-info stack-node-instruction)
		   (phrase-list (generate-new-stack-frame-var-spot 'datum)
				(generate-new-stack-frame-var-spot 'datum)
				(generate-new-stack-frame-var-spot 'datum))))))
    ))



;;; The stack node instruction emitter for FIRST-THAT-HAS-A-VALUE emits in one
;;; of two ways, depending upon whether or not any of its argument nodes can
;;; return unknown.  If the arguments cannot, then this instruction need not
;;; collect expirations from its arguments, or check at all whether or not they
;;; are known.  It only needs to return the first value.

;;; There are three local variables that may be used from within the emitted
;;; instruction: the data seeking cache, the global expiration cache, and the
;;; previous expression could supply a value variable.

(def-expiration-special-form first-that-has-a-value)

(def-stack-node-instruction-emitter first-that-has-a-value
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(surrounding-data-seeking-cache-var? (car extra-info))
	(global-expiration-cache-var? (second extra-info))
	(previous-expression-could-supply-value-var? (third extra-info)))
    (cond
      ;; The first expression may not have a value, if it is a reference to a
      ;; local variable.  So, loop over each expression.  - cpm, 12/9/91
						       ; If this is changed, see
						       ; the converter also.
;      ((null surrounding-data-seeking-cache-var?)
;	;; Emit the first expression since it always has a value.
;	(emit-stack-node-tree byte-code-stream (car argument-nodes)))
      (t
	(let ((end-of-instruction-tag (generate-new-goto-tag)))
	  ;; Cache the old data seeking flag, and set the flag to the default.
	  (emit-instruction-byte-code
	    byte-code-stream 'push-from-allow-data-seeking)
	  (call-stack-instruction-emitter pop-into-surrounding-local-var
	    byte-code-stream surrounding-data-seeking-cache-var?)
	   (emit-instruction-byte-code
	     byte-code-stream 'push-from-default-allow-data-seeking)
	  (emit-instruction-byte-code
	    byte-code-stream 'pop-into-allow-data-seeking)

	  ;; Initialize the previous expression variable.
	  (call-stack-instruction-emitter push-constant
	    byte-code-stream (make-evaluation-truth-value falsity))
	  (call-stack-instruction-emitter pop-into-surrounding-local-var
	    byte-code-stream previous-expression-could-supply-value-var?)

	  ;; Cache the global expiration.
	  (emit-instruction-byte-code byte-code-stream 'push-expiration)
	  (call-stack-instruction-emitter pop-into-surrounding-local-var
	    byte-code-stream global-expiration-cache-var?)

	  ;; Evaluate the expressions until one has a value.
	  (loop for argument-node-cons on argument-nodes
		for argument-node = (first argument-node-cons)
		for test-if-known-tag = (generate-new-goto-tag)
		for known-value-tag = (generate-new-goto-tag)
		for next-argument-tag = (generate-new-goto-tag)
		do
	    (emit-instruction-byte-code byte-code-stream 'reset-expiration)
	    (emit-instruction-byte-code byte-code-stream 'push-wake-ups-count)
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream previous-expression-could-supply-value-var?)
	    (emit-stack-node-tree byte-code-stream argument-node)
	    (call-stack-instruction-emitter funcall-instruction
	      byte-code-stream 'first-that-has-a-value)

	    (emit-instruction-byte-code
	      byte-code-stream 'push-copy-of-top-of-stack)
	    (call-stack-instruction-emitter pop-into-surrounding-local-var
	      byte-code-stream previous-expression-could-supply-value-var?)
	    ;; If no previous expression could still return a value, branch to
	    ;; the value test.
	    (call-stack-instruction-emitter branch-long-if-not-true
	      byte-code-stream test-if-known-tag)

	    ;; A previous expression could have returned a value.
	    (cond
	      ((cdr argument-node-cons)
	       ;; There are still other expressions to evaluate.
	       (call-stack-instruction-emitter branch-long byte-code-stream next-argument-tag))
	      (t
	       ;; This is the last value.  Since a previous expression could have
	       ;; returned a value, always return unknown.
	       (call-stack-instruction-emitter push-constant
		 byte-code-stream (make-evaluation-symbol nil))
	       (emit-instruction-byte-code byte-code-stream 'pop-expiration)
	       (call-stack-instruction-emitter branch-long
		 byte-code-stream end-of-instruction-tag)))

	    ;; A previous expression could not have returned a value.
	    (register-tag-in-byte-code-stream
	      byte-code-stream test-if-known-tag)

	   (call-stack-instruction-emitter branch-long-if-known
	     byte-code-stream known-value-tag)
	   (call-stack-instruction-emitter branch-long byte-code-stream next-argument-tag)

	   ;; Test for a known value of none.  Make a copy of the value first,
	   ;; since the none test pops the value.
	   (register-tag-in-byte-code-stream byte-code-stream known-value-tag)
	   (emit-instruction-byte-code
	      byte-code-stream 'push-copy-of-top-of-stack)
	   (emit-instruction-byte-code byte-code-stream 'none-test)
	   (call-stack-instruction-emitter branch-long-if-not-true
	       byte-code-stream end-of-instruction-tag)

	   ;; Next argument
	   (register-tag-in-byte-code-stream
	     byte-code-stream next-argument-tag)
	   (when (cdr argument-node-cons)
	     (emit-instruction-byte-code byte-code-stream 'pop)))

	  ;; End-Of-Instruction Tag
	  (register-tag-in-byte-code-stream
	    byte-code-stream end-of-instruction-tag)

	  ;; Minimize global expiration var.
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream global-expiration-cache-var?)
	  (emit-instruction-byte-code byte-code-stream 'minimize-expiration)

	  ;; Reinstate the previous data seeking flag.
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream surrounding-data-seeking-cache-var?)
	  (emit-instruction-byte-code
	    byte-code-stream 'pop-into-allow-data-seeking))))))



;;; Instruction 36, the `FIRST-THAT-HAS-A-VALUE funcalled stack-instruction' is
;;; used to implement the evaluator for first-that-has-a-value.  This
;;; instruction takes a wake-up count, a "previous expression could not supply
;;; value", and an expression value stack arguments.  The wake-up count is the
;;; count before the value expression is evaluated.  The expression value is
;;; left on the stack.  Its expiration is also referenced.

;;; This instruction leaves two values on the stack.  The first (i.e., top of
;;; stack) is the "new" previous expression flag (for this expression).  This
;;; value is passed into this instruction if it is called again.  The second
;;; return value is the value of the expression.  This value is considered unknown
;;; if the stack-expiration is nil.

;;; Before this instruction is called the previous expiration and data-seeking
;;; flags are cached, the data-seeking is turned on, the value argument has been
;;; evaluated, and the expiration of the value is in stack-expiration variable.

(def-funcalled-instruction first-that-has-a-value (36 (inference procedure) 3 2 nil
						      pprint-first-that-has-a-value-instruction)
  (let* ((wake-ups-count (evaluation-integer-value (stack-arg 0)))
	 (stack-arg-1 (stack-arg 1))
	 (previous-expression-could-supply-value
	   (evaluation-truth-value-value stack-arg-1))
	 (value? (stack-arg 2))
	 (new-wake-ups-count (length *variables-that-did-not-have-values*)))

    (when (and (null stack-expiration)
	       (not (or (=f previous-expression-could-supply-value truth)
			(final-evaluation-attempt?)
			(<=f new-wake-ups-count wake-ups-count)
			(loop for variable-cons
				  = *variables-that-did-not-have-values*
				  then (cdr variable-cons)
			      for count = 1 then (+f count 1)
			      with end-count = (-f new-wake-ups-count wake-ups-count)
			      until (>f count end-count)
			      thereis (failed-p (car variable-cons))))))
      (setq previous-expression-could-supply-value truth))

    (reclaim-evaluation-integer (stack-arg 0))	       ;wake-ups-count
    (reclaim-evaluation-truth-value stack-arg-1)       ;prev. expr. flag

    (setf (stack-arg 0) value?)			       ;expression value.
    (setf (stack-arg 1)				       ;new prev. expr. flag
	  (make-evaluation-truth-value previous-expression-could-supply-value))
    nil))




;;; The `SIMULATED-VALUE-OF stack-evaluator' is used to directly access a
;;; simulated value without going through data service.  The evaluator accepts
;;; one designation (expression?) argument.  If the variable has a simulated
;;; value, it is returned.  Otherwise, the value is unknown.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.  The instructions cache and set the
;;; current environment to the simulator, get the simulated value, and reset the
;;; current environment to the original value.  This evaluator is available in
;;; the inference engine and procedures.



(declare-optimizer-stack-instruction simulated-value-of)


(def-expiration-special-form simulated-value-of)

(def-special-form-converter simulated-value-of (expression)
  (let ((arguments (stack-cons (convert-expression-to-stack-node-tree
				 (second expression))
			       nil))
	(stack-node-instruction
	  (make-stack-node-instruction 'simulated-value-of nil)))
    (setf (stack-node-argument-nodes stack-node-instruction) arguments)
    stack-node-instruction))


(def-preferred-instruction-chooser simulated-value-of
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(primary-argument-required-type
	  (primary-type-of-type-specification required-type))
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(no-item-allowed?
	  (type-specification-subtype-p '(no-item) required-type)))
    (unless (type-specification-subtype-p primary-argument-required-type 'datum)
      (setq primary-argument-required-type 'datum))
    (setf (car argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (car argument-nodes) 
	    (maybe-add-unknown
	      (maybe-add-no-item
		primary-argument-required-type no-item-allowed?)
	      unknown-allowed?)))
    (setf (stack-node-value-type stack-node-instruction)
	  (stack-node-value-type (car argument-nodes)))
    ;; Generate a place to the cache the current environment.
    ;; but don't do it twice
    (unless (stack-node-instruction-extra-info stack-node-instruction)
      (setf (stack-node-instruction-extra-info stack-node-instruction)
	    (phrase-list (generate-new-stack-frame-var-spot 'symbol))))))

(def-stack-node-instruction-emitter simulated-value-of
  ;; Cache the current environment and set to environment. 
  (emit-instruction-byte-code byte-code-stream 'push-current-environment)
  (call-stack-instruction-emitter pop-into-surrounding-local-var
    byte-code-stream (first extra-info))
  ;; Simulated-value is the environment that can access a simulated value when
  ;; not in the simulator environment.
  (call-stack-instruction-emitter push-constant
    byte-code-stream (make-evaluation-symbol 'simulated-value))
  (emit-instruction-byte-code byte-code-stream 'pop-current-environment)

  (emit-stack-node-tree
    byte-code-stream
    (first (stack-node-argument-nodes stack-node-instruction)))

  ;; Restore the cached current environment.
  (call-stack-instruction-emitter push-from-surrounding-local-var
    byte-code-stream (first extra-info))
  (emit-instruction-byte-code byte-code-stream 'pop-current-environment))

;(Param: class quantitative-parameter,  0
; N: integer {WindowSize},              1
; NStart: integer {WindowStart},        2
; Val: value,                           3
; RequiredGoodSize: integer,            4
; CompareOperator: integer) =           5
; result (value)

(def-in-line-evaluator count-datapoints-that-evaluate-true
    (99 all ((class quantitative-parameter) integer integer number integer integer) float nil 
        pprint-functional-evaluator)
  (let ((good-data-count 0)
        (matched-data-count 0)
        v)
    (setq register-2 (stack-arg 2))
    (setq register-3 (stack-arg 3))
    (setq register-4 (stack-arg 0))
    (loop for i from register-2 to 
          (-f (minf (+f (stack-arg 1) register-2) (number-of-datapoints register-4 nil nil nil)) 1) do
      (setq v (get-value-of-previous-datapoint register-4 nil i))
      (when (and (evaluation-quantity-p v)
                 (not (nanp v)))
        (incff good-data-count)
        (case (stack-arg 5)
          (1 (when (evaluation-quantity->= v register-3) (incff matched-data-count)))
          (2 (when (evaluation-quantity-> v register-3) (incff matched-data-count)))
          (3 (when (evaluation-quantity-<= v register-3) (incff matched-data-count)))
          (4 (when (evaluation-quantity-< v register-3) (incff matched-data-count)))
          (5 (when (evaluation-quantity-= v register-3) (incff matched-data-count)))
          (6 (when (evaluation-quantity-/= v register-3) (incff matched-data-count))))))
    (when (evaluation-float-p register-3)
      (reclaim-evaluation-float register-3))
    (make-evaluation-float
      (if (and (>=f good-data-count (stack-arg 4)) (>f good-data-count 0))
          (/e (coerce-fixnum-to-gensym-float matched-data-count)
              (coerce-fixnum-to-gensym-float good-data-count))
        0.0))))

(setf (argument-range 'count-datapoints-that-evaluate-true) 6)            

;Param: class quantitative-parameter,       0
;N: integer {WindowSize},                   1
;NStart: integer {WindowStart},             2
;Val: value,                                3
;EventFlag: class quantitative-parameter,   4
;EventBit: integer,                         5
;RequiredGoodSize: integer,                 6
;CompareOperator: integer)                  7
;(value)
            
(def-in-line-evaluator count-datapoints-that-evaluate-true-with-eventflag
    (103 all ((class quantitative-parameter) integer integer number (class quantitative-parameter) integer integer integer) float nil 
        pprint-functional-evaluator)
  (let ((good-data-count 0)
        (matched-data-count 0)
        mend
        sum-value
        truth-value-value
        truth-value-truth
        v)
    (setq register-1 (stack-arg 1))  
    (setq register-2 (stack-arg 2))
    (setq register-3 (stack-arg 3))
    (setq register-4 (stack-arg 0)) ;Param
    (setq register-5 (stack-arg 4)) ;EventFlag
    (setf sum-value (+f register-1 register-2))
    (setf mend (-f (minf sum-value (number-of-datapoints register-5 nil nil nil)) 1))
    (loop for i from register-2 to (-f (minf sum-value (number-of-datapoints register-4 nil nil nil)) 1) do
      (setq v (get-value-of-previous-datapoint register-4 nil i))
      (when (and (evaluation-quantity-p v)
                 (not (nanp v))
                 (<f i mend)
                 (progn
                   (setq truth-value-value
                         (eval-bitwise-test-funcalled (get-value-of-previous-datapoint register-5 nil i) (stack-arg 5)))
                   (setq truth-value-truth
                         (evaluation-truth-value-value truth-value-value))
                   (reclaim-evaluation-truth-value truth-value-value)
                   truth-value-truth))
        (incff good-data-count)
        (case (stack-arg 7)
          (1 (when (evaluation-quantity->= v register-3) (incff matched-data-count)))
          (2 (when (evaluation-quantity-> v register-3) (incff matched-data-count)))
          (3 (when (evaluation-quantity-<= v register-3) (incff matched-data-count)))
          (4 (when (evaluation-quantity-< v register-3) (incff matched-data-count)))
          (5 (when (evaluation-quantity-= v register-3) (incff matched-data-count)))
          (6 (when (evaluation-quantity-/= v register-3) (incff matched-data-count))))))
    (when (evaluation-float-p register-3) (reclaim-evaluation-float register-3))
    (make-evaluation-float
      (if (and (>=f good-data-count (stack-arg 6)) (>f good-data-count 0))
          (/e (coerce-fixnum-to-gensym-float matched-data-count)
              (coerce-fixnum-to-gensym-float good-data-count))
        0.0))))

(setf (argument-range 'count-datapoints-that-evaluate-true-with-eventflag) 8)              

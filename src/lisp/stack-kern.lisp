;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module STACK-KERN

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Chris Morel



;; In G2-GSI

(declare-forward-reference gsi-interface-p-function function)

;; In G2DS

(declare-forward-reference g2-to-g2-data-interface-p-function function)

(declare-forward-reference ensure-expanded-instruction-macros function)

;; In COVERAGE

(declare-forward-reference collect-coverage-information function)





;;;; The Stack Expression Evaluator




;;; This file implements the kernel for a stack machine-like evaluator for
;;; expressions and procedures in G2.  This evaluator is the replacement for the
;;; previously seperate simulator, procedure, and inference engine evaluators
;;; for G2.  The instructions for this evaluator are implemented in the file
;;; STACK-INST, which must preceed this file in load order.






;;;; Stack Evaluator Run-Time Environment




;;; The stack evaluator consists of a top-level evaluation function called
;;; Stack-eval.  This function will implement all instructions needed to carry
;;; out the primitives required to execute user specified code.  It will be
;;; efficient and compact, both in implementation and in storage of compiled
;;; user code.

;;; Stack-eval and its subfunctions will contain some inlined, and some out of
;;; line instructions.  This function will execute given a stack vector,
;;; instruction vector, local var vector, and code constant vector.  The stack
;;; vector will be our implementation of a stack, onto and off of which all
;;; values for instructions will flow.  The instruction vector will contain
;;; fixnums which are instructions, as well as other Lisp data structures which
;;; are code constant arguments to instructions.  The local var vector will be
;;; used differently by the differing users of the stack evaluator.  In
;;; procedures, this vector is the local var vector of a code body invocation.
;;; In rules it will be the context and non-context bindings of the rule.  For
;;; the simulator it will contain the items and cached run-time structures to be
;;; accessed by a compiled simulation expression.  The code constant vector for
;;; an instruction vector will contain the quoted code constants for that
;;; compiled p-code vector.  As an implementation issue, data values stored in
;;; the local var vector and constant vector will be boxed as evaluation values.
;;; Those stored in the stack will also be boxed as evaluation values, since we
;;; will have to exit temporary areas more often than we might have to actually
;;; exit execution of a piece of code.  All of these vectors will be implemented
;;; as simple vectors, and therefore will require us to maintain maximum size
;;; restrictions on their size.

;;; The stack-eval function will maintain several fixnum indices into these
;;; vectors.  These indices are required to implement a stack discipline and
;;; function call frames for executing user defined functions.  The indices will
;;; be TOP-OF-STACK, STACK-FRAME-BASE, CURRENT-PROGRAM-COUNTER, PREVIOUS-
;;; PROGRAM-COUNTER (for error reporting purposes), and CURRENT-INSTRUCTION.
;;; All of these variables should be local lexical variables of stack-eval (i.e.
;;; not global) for speed.






;;;; STACK-EVAL Function Implementation




;;; The function `stack-eval' takes an instruction vector and a local var vector
;;; as its arguments, and exits by either throwing to :STACK-EVAL-ERROR or
;;; returns as its value a G2 datum (string, symbol, integer, or gensym-float),
;;; an item instance, or NIL.  It will throw whenever it cannot carry out the
;;; evaluation which was requested because of some error.  It may have a side
;;; effect on the global variable stack-eval-expiration, which is used to report
;;; expirations on those computations which require it.

(defmacro define-stack-eval (name establish-catch-handler-p)
  `(,(if establish-catch-handler-p
         'defun-allowing-unwind
         'defun-void)
        ,name (byte-code-body constant-vector local-var-vector
                              fixnum-start-time fixnum-time-limit?
                              initial-program-counter)
     (setq saved-local-var-vector local-var-vector)
     (with-backtrace-for-internal-error
         (execute-byte-codes nil twrite-stack-eval-activity-after-internal-error)
       (with-catch-handlers-for-stack-eval (,establish-catch-handler-p nil)
         (with-icp-buffer-coelescing-scope
           (stack-eval-1
             byte-code-body constant-vector local-var-vector fixnum-start-time
             fixnum-time-limit? initial-program-counter)
           (when (>f cached-top-of-stack -1)
             (reclaim-top-of-stack)))))))

(defmacro with-catch-handlers-for-stack-eval ((establish-catch-handler-p
                                                execute-computation-instance-cleanup-p)
                                               &body forms)
  (if establish-catch-handler-p
      `(with-catch-handlers
           (((:stack-error) (passed-top-of-stack error error-text-string
                                                 supress-debugging-info?)
             (clean-up-wake-ups-state-if-any)
             (let ((breakpoints-enabled-p nil))
               (signal-error-to-computation-instance
                 current-computation-instance cached-byte-code-body error 1
                 error-text-string cached-stack-program-counter global-stack
                 ;; I don't understand why saved-local-var-vector can ever be
                 ;; right. It's only set in one place, upon entry to stack-eval.
                 ;; What happens when you abort a code body (from a do in
                 ;; parallel)?
                 ;; This is probably another thing to add to
                 ;; modify-major-stack-eval-locals -dkuznick, 8/14/03
                 passed-top-of-stack saved-local-var-vector supress-debugging-info?))
             (setq cached-top-of-stack passed-top-of-stack)
             (when (>f cached-top-of-stack -1)
               (reclaim-top-of-stack))
             (when icp-output-ports-to-flush
               (flush-icp-output-ports))
             ,@(when execute-computation-instance-cleanup-p
                 `(;;execute-computation-instance cleanup
                   (clear-computation-context-variables)
                   ;;dequeue-and-execute-next-task cleanup
                   ;;  >> cleanup is at the top of dequeue-and-execute-next-task
                   ;;run-one-scheduler-cycle cleanup
                   (when profiling-enabled?
                     (let ((current-time (allocate-managed-float (gensym-get-unix-time))))
                       (exit-current-profiling-context current-time)
                       (reclaim-managed-float current-time)))
                   (register-profiling-activity clock-tick)))))
         ,@forms)
      `(progn ,@forms)))

(defvar saved-local-var-vector nil)

(define-stack-eval stack-eval t)

(define-stack-eval stack-eval-for-execute-computation-instance nil)

(defun-allowing-unwind g2-event-loop ()
  (g2-event-loop-macro))

(declare-forward-references
  (last-source-line	variable)
  (current-source-line	variable))

#+SymScale
(defun-allowing-unwind g2-worker-loop ()
  (with-safe-stack-eval-reentrancy
    (g2-worker-loop-macro)))

;;; `Run-scheduler-for-breakpoint' runs a scheduling loop,
;;; until return-from-breakpoint is called.

(defun-allowing-unwind run-scheduler-for-breakpoint ()
  (flush-icp-output-ports)
  (let ((with-icp-buffer-coelescing-scope? nil)
        (current-schedule-task nil)
        (priority-of-current-task -1)
        (inside-breakpoint-p t))
    (with-global-stack
      (with-three-thousand-variables-bound
        (catch 'return-from-breakpoint
          (with-inhibited-icp-socket-reclamation
            (ne-enqueue-scheduler-event)
            (maybe-schedule-service-workstations t)
            (g2-event-loop)))))))





;;; The function `twrite-stack-eval-activity-after-internal-error' is called
;;; only after an unhandled signal or call to error has occurred.  This function
;;; should succintly write the current computation frame,
;;; current-computation-component-particulars, and the current-activity in a
;;; user readable format, while attempting to be as wary of data corruption as
;;; possible.

(defun twrite-stack-eval-activity-after-internal-error ()
  (twrite-string "  within ")
  (cond
    ((and (framep *current-computation-frame*)
          (framep current-computation-instance)
          (framep (invocation-byte-code-body current-computation-instance)))
     (write-activity-given-pc-and-byte-code-body
       (invocation-byte-code-body current-computation-instance)
       (invocation-stack-program-counter current-computation-instance)))
    ((and (framep *current-computation-frame*)
              (fixnump current-computation-activity))
         (write-activity-given-index
           *current-computation-frame* current-computation-component-particulars
           current-computation-activity)
         (twrite-string " in ")
         (denote-component-of-block t))
        ((framep *current-computation-frame*)
         (denote-component-of-block t))
        (t
         (twrite-string "context switching code"))))



(defvar enable-running-compiled-code-p t)

;;; The function stack-eval-1 is used as the round-robin loop that sets up and
;;; clears out the temporary-area context for stack-eval-inner.

(def-inlined-pseudo-function-with-side-effects inline-c-call-8 (fn arg1 arg2 arg3 arg4
                                                                   arg5 arg6 arg7 arg8)
  (funcall-simple-compiled-function fn arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8))

(defvar c-byte-code-body-result-1 nil)
(defvar c-byte-code-body-result-2 nil)
(defvar c-byte-code-body-result-3 nil)
(defvar c-byte-code-body-result-4 nil)
(defvar c-byte-code-body-result-5 nil)
(defvar c-byte-code-body-result-6 nil)
(defvar c-byte-code-body-result-7 nil)
(defvar c-byte-code-body-result-8 nil)

(defmacro funcall-byte-code-body-function (fn arg1 arg2 arg3 arg4
                                              arg5 arg6 arg7 arg8)
  `(progn
     (inline-c-call-8 ,fn ,arg1 ,arg2 ,arg3 ,arg4 ,arg5 ,arg6 ,arg7 ,arg8)
     (values c-byte-code-body-result-1 c-byte-code-body-result-2 c-byte-code-body-result-3
             c-byte-code-body-result-4 c-byte-code-body-result-5 c-byte-code-body-result-6
             c-byte-code-body-result-7)))

(defvar trace-compiled-function-execution nil)
(defvar trace-instruction-execution nil)


(defmacro debug-interpreter-print (stack-program-counter top-of-stack local-stack)
  (declare (ignore stack-program-counter top-of-stack local-stack))
  nil)

(defvar debug-print-byte-code-pc-p nil)

#|
;;; debugging version

(defvar print-interpreter-debug-info nil)

(defvar verbose-interpreter-debug-info nil)

(defmacro debug-interpreter-print
    (stack-program-counter top-of-stack local-stack)
  `(when print-interpreter-debug-info
       (format t "pc=~d, tos=~d~%" ,stack-program-counter ,top-of-stack)
       (when verbose-interpreter-debug-info
           (format t "~%")
           (dotimes (i (1+f ,top-of-stack))
             (format t "~D:  ~S~%" i (aref ,local-stack i))))))

|#

(defvar execution-time-stack nil)
(defvar procedure-start-time 0)
(defvar procedure-end-time 0)
(defvar procedure-current-time 0)

(defun-void stack-eval-1
    (byte-code-body constant-vector local-var-vector fixnum-start-time
                    fixnum-time-limit? initial-program-counter)
  (setq stack-expiration 'never)
  (setq cached-fixnum-start-time fixnum-start-time)
  (setq arithmetic-errors-are-stack-errors-p t)
  (setq cached-top-of-stack -1)
  (setq cached-stack-program-counter initial-program-counter)
  (setq cached-stack-frame-base 0)
  (setq cached-byte-code-body byte-code-body)
  (setq procedure-start-time fixnum-start-time)

  (unless (calculate-time-of-called-procedures miscellaneous-parameters) 
    (gensym-push 0 execution-time-stack))

  ;; This loop tests if any execution time limit has been exceeded, and it
  ;; enters and exits a temporary context for the call to stack-eval-inner.
  (loop with next-program-counter = initial-program-counter
        with stack-frame-base = 0
        with recursion-depth = 0
        do
    (when fixnum-time-limit?
      (let ((current-fixnum-time (get-fixnum-time)))
        (declare (type fixnum current-fixnum-time))
        (cond (forgive-long-procedure-instruction?
               (setq forgive-long-procedure-instruction? nil)
               (setq cached-fixnum-start-time current-fixnum-time))
              ((not (calculate-time-of-called-procedures miscellaneous-parameters))
               (let ((procedure-execution-time
		      (fixnum-time-difference current-fixnum-time procedure-start-time)))
                 (when (>=f procedure-execution-time fixnum-time-limit?)
                   (signal-procedure-time-error procedure-execution-time cached-top-of-stack))))
              (t
               (let ((time-elapsed
                       (fixnum-time-difference
                         current-fixnum-time cached-fixnum-start-time)))
                 (declare (type fixnum time-elapsed))
                 (when (>=f time-elapsed fixnum-time-limit?)
                   (setq cached-fixnum-start-time current-fixnum-time)
                   (signal-procedure-time-error
                     time-elapsed cached-top-of-stack)))))))
    (with-temporary-gensym-float-creation stack-eval
      (multiple-value-setq
          (byte-code-body constant-vector local-var-vector fixnum-time-limit?
                          next-program-counter stack-frame-base recursion-depth)
        (if (message-and-breakpoint-overrides debugging-parameters)
            (stack-eval-inner-debuggable
              byte-code-body constant-vector local-var-vector fixnum-time-limit?
              next-program-counter cached-top-of-stack stack-frame-base
              recursion-depth)
            #+development
            (let ((compiled-function
                    (byte-cody-body-compiled-function byte-code-body)))

              (if (and compiled-function enable-running-compiled-code-p)
                  (progn
                    (when trace-compiled-function-execution
                      (write-computation-context-to-console
                        *current-computation-frame* current-computation-component-particulars
                        current-computation-instance byte-code-body constant-vector
                        next-program-counter global-stack cached-top-of-stack))
                    (funcall-byte-code-body-function
                      compiled-function
                      byte-code-body constant-vector local-var-vector fixnum-time-limit?
                      next-program-counter cached-top-of-stack stack-frame-base
                      recursion-depth))
                  (stack-eval-inner
                    byte-code-body constant-vector local-var-vector fixnum-time-limit?
                    next-program-counter cached-top-of-stack stack-frame-base
                    recursion-depth)))
            #-development
            (stack-eval-inner
              byte-code-body constant-vector local-var-vector fixnum-time-limit?
              next-program-counter cached-top-of-stack stack-frame-base
              recursion-depth))))
    #+development
    (when debug-print-byte-code-pc-p
      (format t "~%~%~%*** Stack-eval-1 outer loop; stack follows ***~%")
      (debug-interpreter-print next-program-counter cached-top-of-stack global-stack)
      (format t "~%~%~%*** Stack-eval-1 outer loop; end of stack ***~%"))

        until (<f next-program-counter 0))
  (setq arithmetic-errors-are-stack-errors-p nil))

;; These may get moved into stack-eval-locals later, or at least a debuggable?
;; version, or with-three-thousand-variables-bound.  Or might want to be saved
;; and restored ala saved-source-stepping-level. At the very least, they should
;; be kb-specific-variables.  Note there's a slight bug currently, as when
;; stepping into a procedure from another stepped procedure, last-source-line
;; may still be set relative to the caller, thus causing us to stop on the way
;; into the new procedure (though it doesn't seem all that unusual to users -
;; it seems like we just broke upon entrance to the procedure on purpse).
;; Likewise when we return to a caller, we may not stop when we are supposed to
;; (if say we were just on line 4 of the callee, and happen to now be on line 4
;; of the caller).  This will be dealt with in a future commit. -dkuznick,
;; 10/20/04
(defvar last-source-line 0)
(defvar current-source-line 0)

;;; `items-with-dynamic-breakpoints' is simply a list of all items (stored as
;;; item-references) which currently have at least one dynamic breakpoint set
;;; on them.  This is not likely to ever get very big.  We could switch to a
;;; hash-table as access time gets to be an issue.
;; Will be used in a future commit.
#+:GLOBAL-FOR-ITEMS-WITH-DYNAMIC-BREAKPOINTS
(def-kb-specific-variable items-with-dynamic-breakpoints stack-kern
  nil t items-with-dynamic-breakpoint-reclaimer)

;; Will be used in a future commit.
#+:GLOBAL-FOR-ITEMS-WITH-DYNAMIC-BREAKPOINTS
(defun items-with-dynamic-breakpoint-reclaimer (table)
  ;; Can't use reclaim-gensym-tree because the item-references would get
  ;; reclaimed as conses!
  (loop for item-reference in table
        do
    (reclaim-evaluation-item-reference item-reference))
  (reclaim-gensym-list table))

;;; `at-dynamic-breakpoint-p' returns T when the given pc is at a breakpoint
;;; which is set.  Otherwise it returns NIL.  Note this implies if you are at a
;;; dynamic-breakpoint which is unset, this returns NIL.
;;;
;;; This will be the "slow" check.  A quick check and implementation (see
;;; projects/core-0041-debugging.html for details) may come later.  As a
;;; reminder from alatto, we may have to deal with address ranges no matter
;;; what, because a single line might have multiple statements on it.  Say
;;; there's a label in the middle of two statements on one line, and somewhere
;;; you want to go to the label.  If you have a breakpoint set at the line, you
;;; probably want to break.  The current scheme won't do this because it only
;;; checks the address for the first statement on a line.
(defun at-dynamic-breakpoint-p (item pc code-body)
  (when (procedure-p item)
    (loop with code-body-n = (code-body-number-of-code-body code-body)
          for dynamic-breakpoint in (dynamic-breakpoint-settings item)
          for address = (dynamic-breakpoint-address dynamic-breakpoint)
          if (and (eql address pc)
                  (eql (dynamic-breakpoint-nth-code-body dynamic-breakpoint)
                       code-body-n))
            return (and (dynamic-breakpoint-valid-p dynamic-breakpoint)
                        (dynamic-breakpoint-enabled-p dynamic-breakpoint)))))


;;; `get-dynamic-breakpoints-internal' returns a fresh eval-list {but the
;;; contents should not be reclaimed, only the spine} of breakpoints for the
;;; specified item, or NIL if there are none.  By default only valid
;;; breakpoints are returned.  If you want all breakpoints, specify a second
;;; argument of nil.
(defun get-dynamic-breakpoints-internal (item &optional (only-valid-p t))
  (when (procedure-p item)
    (loop for dynamic-breakpoint in (dynamic-breakpoint-settings item)
          nconcing (if only-valid-p
                       (and (dynamic-breakpoint-valid-p dynamic-breakpoint)
                            (eval-list dynamic-breakpoint))
                       (eval-list dynamic-breakpoint)))))

;;; `set-dynamic-breakpoint-internal' is the main entry point, and is what
;;; other internal code should call.  It returns NIL if the breakpoint placed
;;; was invalid, or in the case when valid-only-p was specified and a
;;; breakpoint was not able to be placed or non-NIL to indicate success.  If
;;; there already is a breakpoint at the specified line, it gets its status set
;;; apropriately based on the status argument, otherwise a new one gets
;;; added {with the apropriate status}.
(defun set-dynamic-breakpoint-internal
    (procedure line
               &optional (status dynamic-breakpoint-enabled) (valid-only-p t))
  ;; This will only work for setting a breakpoint at a real line of code, as
  ;; opposed to a begin, where it should probably set it at the next real line,
  ;; and inform the caller that it did something different.  That's a
  ;; suggestion for the future.  For now it simply sets an invalid
  ;; breakpoint. -dkuznick, 3/11/05
  (or (if (eq status dynamic-breakpoint-enabled)
          (turn-on-dynamic-breakpoint procedure line)
          (turn-off-dynamic-breakpoint procedure line))
      (multiple-value-bind (address? nth-code-body?)
          (get-address-for-line-from-annotation-if-any line procedure)
        (if (and valid-only-p (not address?))
            nil
            (multiple-value-bind (valid? first-one?)
                (add-dynamic-breakpoint procedure
                                        address?
                                        line
                                        status
                                        nth-code-body?)
              (declare (ignore first-one?))
              #+:GLOBAL-FOR-ITEMS-WITH-DYNAMIC-BREAKPOINTS
              (when first-one?
                (gensym-push (get-reference-to-item procedure)
                             items-with-dynamic-breakpoints))
              valid?)))))




;;; The function `stack-eval-inner' is the one that interprets instructions for
;;; the stack evaluator.  All stack instructions and in-lined evaluators are
;;; included within the body of this function.

;;; So recompilation is necessary if more inline evaluators are added --rdf
;;; Or any of the profiling macros are changed

(defmacro stack-eval-inner-body (debuggable?)
  `(stack-eval-locals
     (setq instruction-count 500)
     (setq detailed-tracing?
           ,(if debuggable?
                `(detail-trace-message-will-be-written-p)
                nil))
     (setq major-tracing?
           ,(if debuggable?
                `(major-trace-message-will-be-written-p)
                nil))

     ;; The following may get removed if we move the setting of the variables
     ;; to modify-tracing-and-breakpoints-context-on-entry and friends.
     ,@(when debuggable?                ;may become "stepping?"
         `((setq last-source-line 0)
           (setq current-source-line 0)))

     (tagbody
      execute-next-stack-instruction
        (if (>f instruction-count 0)
            (decff instruction-count)
            (go exit-stack-eval-inner))
        (debug-interpreter-print stack-program-counter top-of-stack local-stack)
        (setq cached-stack-program-counter stack-program-counter)
        ,@(when debuggable?
            `((setq cached-top-of-stack top-of-stack)
              (when (and detailed-tracing?
                         (or disassemble-enabled?
                             (pprinter-for-stack-instruction-p
                               stack-program-counter byte-code-body)))
                (write-detailed-stack-eval-trace
                  stack-program-counter top-of-stack local-stack
                  local-var-vector byte-code-body constant-vector))))

        ;; Now handle source stepping.  We only pause if we have changed lines.
        ,@(when debuggable?                ;may become "stepping?"
            ;; This test needs to be smarter since they might be the same first
            ;; time through.  True?  Also, add check for non-zero
            ;; current-source-line?
            `((when (and (message-and-breakpoint-overrides debugging-parameters)
                         (>f source-stepping-level 0)
                         ;; not for rules yet

                         ;; The reason we can't just test the
                         ;; current-computation-instance is that for
                         ;; function-definitions, the instance stays a
                         ;; procedure-invocation, but the frame is the
                         ;; function-definition.  -dkuznick, 1/28/05
                         (procedure-p *current-computation-frame*)
                         (code-body-invocation-p current-computation-instance))
                (setq last-source-line current-source-line)
                (setq current-source-line
                      (let ((code-body? (code-body-of-invocation
                                          current-computation-instance)))
                        ;; When can this be nil? -dkuznick, 1/14/05
                        (if code-body?
                            ;; Make this faster?  We can probably be smarter
                            ;; than calling this every time.  I think we can
                            ;; figure out what the program-counter range is
                            ;; when we change lines, and so we should be able
                            ;; to do a simple range compare, rather than the
                            ;; whole lookup each time.
                            (or (nth-value
                                  2        ; use the non-wrapped line index
                                  (get-annotation-for-address-if-any
                                    stack-program-counter
                                    code-body?)) ;can't get it from byte-code-body
                                0)
                            0)))        ;or -1?
                (unless (eql current-source-line last-source-line)
                  (pause-during-debug
                    (capture-halt-information
                      'source-stepping
                      #w"****SOURCE STEPPING****"
                      stack-program-counter
                      top-of-stack
                      local-stack
                      local-var-vector
                      byte-code-body))))))

        ;; Check for dynamic breakpoints.
        ,@(when debuggable?
            ;; We will make a much more optimal check later.  Also, not for
            ;; rules yet.

            ;; See same procedure-p test above for explanation. -dkuznick,
            ;; 1/28/05
            `((when (and (message-and-breakpoint-overrides debugging-parameters)
                         (procedure-p *current-computation-frame*)
                         (code-body-invocation-p current-computation-instance)
                         (at-dynamic-breakpoint-p
                           *current-computation-frame*
                           stack-program-counter
                           ;; Hmm... Why the existence check above?  Necessary
                           ;; here?  -dkuznick, 1/14/05
                           (code-body-of-invocation
                             current-computation-instance)))
                (pause-during-debug
                  (capture-halt-information
                    'dynamic-breakpoint
                    #w"****DYNAMIC BREAKPOINT****"
                    stack-program-counter
                    top-of-stack
                    local-stack
                    local-var-vector
                    byte-code-body)))))
      
        (when trace-instruction-execution
          (write-computation-context-to-console
            *current-computation-frame* current-computation-component-particulars
            current-computation-instance byte-code-body constant-vector
            stack-program-counter local-stack top-of-stack))

        (setq byte-instruction
              (byte-vector-aref instruction-vector stack-program-counter))

        (incff stack-program-counter)            
        (execute-stack-instruction
          byte-instruction execute-next-stack-instruction debuggable?) ;added by SoftServe

      exit-stack-eval-inner
        (setq cached-top-of-stack top-of-stack)
        (setq cached-stack-program-counter stack-program-counter)
        (return-from stack-eval-inner
          (values byte-code-body constant-vector local-var-vector
                  fixnum-time-limit? stack-program-counter stack-frame-base
                  recursion-depth))

      exit-stack-eval
        ;; Finally, store the program counter and current frame serial number,
        ;; and reclaim the remainder of the stack.

        (cond ((code-body-invocation-p current-computation-instance)
               (exit-computation-context-for-code-body-invocation
                 current-computation-instance stack-program-counter nil))
              ((rule-instance-p current-computation-instance)
               (setf (invocation-stack-program-counter
                       current-computation-instance)
                     stack-program-counter)))

        (setq cached-top-of-stack top-of-stack)
        (return-from stack-eval-inner
          (values byte-code-body constant-vector local-var-vector
                  fixnum-time-limit? -1 stack-frame-base recursion-depth)))))

(defun stack-eval-inner
    (byte-code-body constant-vector local-var-vector fixnum-time-limit?
     initial-program-counter initial-top-of-stack initial-stack-frame-base
     initial-recursion-depth)
  (stack-eval-inner-body nil))

(defun stack-eval-inner-debuggable
    (byte-code-body constant-vector local-var-vector fixnum-time-limit?
     initial-program-counter initial-top-of-stack initial-stack-frame-base
     initial-recursion-depth)
  (block stack-eval-inner
    (stack-eval-inner-body t)))




;;; The function `check-current-computation-instance-ok' gets called
;;; between every instruction when trying to catch corruptions of the
;;; currently running thing.

#+development
(defun check-current-computation-instance-ok ()
  (cond ((code-body-invocation-p current-computation-instance)
         nil)
        ((rule-instance-p current-computation-instance)
         nil)
        ((formula-invocation-p current-computation-instance)
         nil)
        ((and (framep current-computation-instance)
              (or (variable-p current-computation-instance)
                  (g2-expression-cell-p current-computation-instance)))
         nil)
        ((error-occurred-in-simulator?)
         nil)
        (t
         #+development
         (cerror
           "Continue"
           "Unknown instance ~a check-current-computation-instance-ok."
           current-computation-instance))))



;;; The function `write-detailed-stack-eval-trace' is called from the inner loop
;;; of the stack evaluator when writing detailed tracing messages.  This
;;; function should write the message and return.

;;; Note that there is currently a crappy interface to users for tracing.  Every
;;; time a tracing message comes up, a new window is made, all the stuff is
;;; drawn, and then the whole thing is reclaimed after the user acknowledges it.
;;; This causes a redraw of everything below the window.  If the user is
;;; breakpointing on minor traces, then EVERY INSTRUCTION gets this treatment,
;;; with no way for the user to step forward N instructions, or anything.  This
;;; makes tracing virtually useless.  -jra 4/9/91

(defun write-detailed-stack-eval-trace
    (current-program-counter top-of-stack local-stack
                             local-var-vector byte-code-body constant-vector)
  (write-detail-trace-message
    (tformat "About to execute the following operation.~%")

    (write-computation-context
      *current-computation-frame* current-computation-component-particulars
      current-computation-instance byte-code-body constant-vector
      current-program-counter local-stack top-of-stack local-var-vector)

;    (twrite-string "In ")
;    (denote-component-of-block t)
;    (tformat ", about to execute instruction ~a." current-program-counter)
;    (when (or (eval-feature :development)
;              disassemble-enabled?)
;      (tformat "~%~%<The following is development or disassemble-enabled? only.>")
;      (cond
;        ((code-body-invocation-p current-computation-instance)
;         (tformat "~%~%Code Body ~a~%"
;                  (code-body-number-of-code-body
;                    (code-body-of-invocation current-computation-instance))))
;        (t
;         (tformat "~%~%")))
;      (write-stack-instruction
;        current-program-counter
;        byte-code-body))
;    (write-stack-contents local-stack top-of-stack)
;    (tformat "~%~%Environment:~%")
;    (write-code-body-environment
;      (byte-code-body-environment-description byte-code-body)
;      local-var-vector)
      ))




;;; The function `signal-error-to-computation-instance' is used to signal errors
;;; to things which are in the current-computaion-intance variable.  This
;;; function should dispatch to the different error handlers for the differing
;;; types of current-computation-instance.

;;; The argument error can now be either a symbol or an error object.
;;; In the case that it is an error object the error-text-string argument
;;; will be a copy of the text string in the error-description of the
;;; error object.


(defun signal-error-to-computation-instance
    (computation-instance byte-code-body error error-level
                          error-text-string current-program-counter local-stack top-of-stack
                          local-var-vector suppress-debugging-info?)
  (cond ((code-body-invocation-p computation-instance)
         (exit-tracing-and-breakpoint-context
           *current-computation-frame*
           (tformat-text-string
             "Exiting ~NF due to the following error:  ~NW"
             *current-computation-frame*
             error-text-string))
         (exit-computation-context-for-code-body-invocation
           computation-instance current-program-counter t)
         (signal-code-body-invocation-error
           computation-instance
           error
           error-level
           error-text-string
           byte-code-body
           current-program-counter
           local-stack
           top-of-stack
           suppress-debugging-info?
           *current-computation-frame*
           current-computation-component-particulars))
        ((rule-instance-p computation-instance)
         (handle-rule-instance-error
           computation-instance error error-level error-text-string
           current-program-counter local-stack top-of-stack
           *current-computation-frame* current-computation-component-particulars
           byte-code-body local-var-vector))
        ((formula-invocation-p computation-instance)
         (handle-formula-invocation-error
           computation-instance error error-level error-text-string
           current-program-counter local-stack top-of-stack
           *current-computation-frame* current-computation-component-particulars
           byte-code-body
           (byte-code-body-constant-vector byte-code-body)
           local-var-vector))
        ((error-occurred-in-simulator?)
         (handle-simulator-stack-error
           computation-instance *current-computation-frame*
           current-computation-component-particulars error error-level
           error-text-string current-program-counter local-stack top-of-stack
           byte-code-body local-var-vector))
        ((and (framep computation-instance)
              (or (variable-p computation-instance)
                  (g2-expression-cell-p computation-instance)))
         (let ((expanded-error-message
                 (generate-standard-error-message
                   error error-text-string *current-computation-frame*
                   current-computation-component-particulars computation-instance
                   byte-code-body (byte-code-body-constant-vector byte-code-body)
                   current-program-counter local-stack top-of-stack
                   local-var-vector)))
           ;; Invoke default error handler if registered and active
           (cond
             ((and (registered-and-active-default-error-handler-p)
                   (invoke-user-defined-default-error-handler
                     error expanded-error-message)))
             (t
              (warning-message 1 "~NW" expanded-error-message)
              (reclaim-error-text expanded-error-message)))
           (reclaim-error-text error-text-string)))
        ((null computation-instance) ; from a breakpoint, when it can't continue
         (notify-user "Error: ~NW" error-text-string)
         (reclaim-error-text error-text-string))
        (t
         (notify-user "Don't know how to handle errors in ~NF.  Error: ~NW"
                      computation-instance
                      error-text-string)
         (reclaim-error-text error-text-string))))




;;; The function `handle-rule-instance-error' will be called if there is an
;;; error while executing the rule.  This function should issue an error message
;;; on the logbook and set the ri-state of the rule instance such that it will
;;; be reclaimed when control returns to validate-and-execute-rule-
;;; continuation-new.

(defun handle-rule-instance-error
    (rule-instance error error-level error-text-string
                   current-program-counter local-stack? top-of-stack?
                   computation-frame computation-component-particulars byte-code-body
                   local-var-vector)
  (let ((standard-message
          (generate-standard-error-message
            error error-text-string computation-frame
            computation-component-particulars rule-instance byte-code-body
            (byte-code-body-constant-vector byte-code-body)
            current-program-counter local-stack? top-of-stack?
            local-var-vector)))
    ;; Invoke default error handler if registered and active
    (cond
      ((and (registered-and-active-default-error-handler-p)
            (invoke-user-defined-default-error-handler error
                                                       standard-message)))
      (t
       (warning-message error-level "~NW" standard-message)
       (reclaim-error-text standard-message)))
    (reclaim-error-text error-text-string)
    (setf (ri-state rule-instance) :error)
    (exit-last-rule-instance-context current-program-counter)))



;;; Default G2 Error Handler

;;; G2 system procedures to allow the user to define a default error handler.

;;; The variable 'user-defined-default-error-handling-procedure? stores the
;;; current registered default error handler for the KB.

(def-kb-specific-variable user-defined-default-error-handling-procedure?
 stack-kern nil nil nil)


(def-kb-specific-variable user-defined-default-error-handling-procedure-fsn
 stack-kern nil nil reclaim-frame-serial-number)





;;; `valid-new-style-error-handler-p'

(defun-simple valid-new-style-error-handler-p (error-handler)
  (or (of-class-p error-handler 'method-declaration)
      (and (= (argument-count error-handler) 1)
           (equal (var-type-from-index
                    (argument-list-description error-handler) 0)
                  '(class error)))))


;;; `valid-old-style-error-handler-p'

(defun-simple valid-old-style-error-handler-p (error-handler)
  #+development
  (unless (of-class-p error-handler 'procedure)
    (cerror "Continue (this will abort in distribution)"
            "valid-old-style-error-handler-p must be given a procedure"))
  (let ((argument-descriptions (argument-list-description error-handler))
        (argument-count (argument-count error-handler)))
    (and (fixnump argument-count)
         (=f argument-count 2)
         (eq (var-type-from-index argument-descriptions 0) 'symbol)
         (eq (var-type-from-index argument-descriptions 1) 'text))))



;;; `valid-user-defined-message-handler-p'

(defun-simple valid-user-defined-message-handler-p (message-handler)
  (let ((arg-count
          (argument-count message-handler)))
    (and (fixnump arg-count)
         (=f arg-count 1)
         (eq 'text
             (var-type-from-index
               (argument-list-description message-handler) 0)))))






;;; The system procedure `g2-register-default-error-handler' alows the user to
;;; register a local procedure as a default error handler.   The procedure
;;; must be an active local procedure with two arguments, a symbol and a
;;; text value, or with one argument: an error-object.  The argument checking
;;; is done by `check-default-error-handler-arguments'.

(defun-for-system-procedure g2-register-default-error-handler
    (procedure)
  (cond  ((not (of-class-p procedure 'procedure))
          (stack-error
            cached-top-of-stack
            "Attempt to register ~NF failed, the default error handler must be a procedure."
            procedure))
         ((or (of-class-p procedure 'method-declaration)
              (check-default-error-handler-arguments procedure))
          (setq user-defined-default-error-handling-procedure? procedure)
          (frame-serial-number-setf user-defined-default-error-handling-procedure-fsn
                                    (frame-serial-number procedure)))))


;;; Check that the procedure being registered has allowable argument list
;;; Allowable:
;;; (symbol, text)
;;; (class error)

(defun-simple check-default-error-handler-arguments (procedure)
  (or (valid-new-style-error-handler-p procedure)
      (valid-old-style-error-handler-p procedure)
      (stack-error cached-top-of-stack
                   "Attempt to register ~NF failed. ~
                    Default error handler must either: (a) take one argument: an ~
                    error object; or (b) take two arguments: first argument must ~
                    be a symbol, and second argument must be a text."
                   procedure)))


;;; The system procedure `g2-deregister-default-error-handler' is used to
;;; deregister the user defined default error handler.

(defun-for-system-procedure g2-deregister-default-error-handler
    ()
  (setq user-defined-default-error-handling-procedure? nil)
  (frame-serial-number-setf user-defined-default-error-handling-procedure-fsn nil))


;;; The system procedure `g2-get-default-error-handler' returns the
;;; currently registered default error handler procedure. If there is
;;; none then it returns the truth-value false.

(defun-for-system-procedure g2-get-default-error-handler
    ()
  (cond ((and user-defined-default-error-handling-procedure?
              (framep user-defined-default-error-handling-procedure?)
              (procedure-p user-defined-default-error-handling-procedure?)
              (not (frame-has-been-reprocessed-p
                     user-defined-default-error-handling-procedure?
                     user-defined-default-error-handling-procedure-fsn)))
           user-defined-default-error-handling-procedure?)
        (t (make-evaluation-truth-value-function falsity)))
  )

;;; The function `registered-and-active-default-error-handler-p'
;;; is used to determine if a default-error handler is currently
;;; registered and is active.

(defun registered-and-active-default-error-handler-p
    ()
  (and user-defined-default-error-handling-procedure?
       (framep user-defined-default-error-handling-procedure?)
       (procedure-p user-defined-default-error-handling-procedure?)
       (active-p user-defined-default-error-handling-procedure?)
       (not (frame-has-been-reprocessed-p
              user-defined-default-error-handling-procedure?
              user-defined-default-error-handling-procedure-fsn)))
  )

;;; The function `pass-loop-check-for-user-defined-default-error-handler-p'
;;; takes a code-body-invocation as an argument.  It checks to see if the
;;; user defined default error handler is the procedure for the
;;; code-body-invocation or is a caller of the code-body-invocation.

(defun pass-loop-check-for-user-defined-default-error-handler-p
    (code-body-invocation)
  (and
    (not
      (called-by-default-handler-p
        code-body-invocation
        user-defined-default-error-handling-procedure?))
    (pass-loop-check-to-write-error-to-logbook-p code-body-invocation)))


;;; Invoking a user defined default error handler

;;; `invoke-user-defined-default-error-handler'
;;;
;;; There are two kinds of errors to consider:
;;;   (i) Symbol, Text (old-style-error)
;;;   (ii) Error Object (new-style-error)
;;;
;;; There are two kinds of error handlers to consider:
;;;  (i)  Symbol, text  (old-style-handler)
;;;  (ii) Error Object  (new-style-handler)
;;;
;;; This function must map between the error style passed to it and the
;;; error style expected by the currently registered handler.
;;;
;;; In the case that the currently registered handler is a method-declaration
;;; this function must perform method dispatching
;;;
;;; This function must cause the default error handler to be performed
;;; immediately.
;;;
;;; This function assumes that the default handler has already been checked
;;; to be registered correctly and active  by a call to the predicate
;;; `registered-and-active-default-error-handler-p'.
;;;
;;; This function returns t if the default error handler is successfully
;;; dispatched, nil if it is not.

(defun invoke-user-defined-default-error-handler
    (error error-text)
  (let* ((handler user-defined-default-error-handling-procedure?)
         (new-style-error? (framep error))
         (new-style-handler? (valid-new-style-error-handler-p handler))
         (old-style-handler? (and (not new-style-handler?)
                                  (valid-old-style-error-handler-p handler))))
    (cond
      (new-style-handler?
       (cond
         (new-style-error?
          (let ((handler-success?
                  (invoke-new-style-user-defined-default-error-handler
                    error)))
            (when handler-success?
              (reclaim-error-text error-text))
            handler-success?))
         (t
          (let* ((converted-error
                   (convert-symbol-text-to-error-object
                     error
                     (copy-text-string
                       (error-text-string error-text))))
                 (handler-success?
                   (invoke-new-style-user-defined-default-error-handler
                     converted-error)))
            (cond
              (handler-success?
               (reclaim-error-text error-text)
               t)
              (t
               (delete-frame converted-error)
               nil))))))
      (old-style-handler?
       (cond
         (new-style-error?
          (multiple-value-bind (e-symbol e-text)
              (convert-error-object-to-symbol-text error)
            (invoke-old-style-user-defined-default-error-handler
              e-symbol e-text))
          (when (transient-p error)
            (delete-frame error))
          (reclaim-error-text error-text)
          t)
         (t
          (invoke-old-style-user-defined-default-error-handler
            error error-text)
          (reclaim-error-text-but-not-string error-text)
          t)))
      (t
       (notify-user "The currently registered default error handler ~NF no ~
                     longer conforms to the necessary specification.  ~
                     Default error handler must either: (a) take one ~
                     argument: an error object; or (b) take two arguments: ~
                     first argument must be a symbol, and second argument ~
                     must be a text." handler)
       nil))))


(defun invoke-old-style-user-defined-default-error-handler
    (error error-text)
  (let ((local-stack (allocate-managed-simple-vector 2))
        (just-error-text (error-text-string error-text)))
    (setf (svref local-stack 0) error)
    (setf (svref local-stack 1) just-error-text)

    (with-three-thousand-variables-bound
        (start-procedure-invocation-in-place-immediately
          user-defined-default-error-handling-procedure?
          local-stack
          1
          2
          nil
          nil
          nil)
      (reclaim-managed-simple-vector local-stack))
    ))

(defun invoke-new-style-user-defined-default-error-handler
    (error)
  (let ((local-stack (allocate-managed-simple-vector 1))
        (method-declaration?
          (of-class-p user-defined-default-error-handling-procedure?
                      'method-declaration))
        (handler? user-defined-default-error-handling-procedure?))
    (setf (svref local-stack 0) error)

    ;; Dispatching for the case that the default-error handler is
    ;; a method-declaration.
    (when method-declaration?
      (let ((method-or-error-string?
              (get-specific-method-for-stack
                handler?
                local-stack
                0
                1)))
        (cond
          ((framep method-or-error-string?)
           (setq handler? method-or-error-string?))
          ;; Do not signal an error when the method handler is incorrect
          ;; because this could produce looping involving the default error
          ;; handler
          (t (setq handler? nil)))))

    (cond (handler?
           (let ((invocation?
                   (with-three-thousand-variables-bound
                       (start-procedure-invocation-in-place-immediately
                         handler?
                         local-stack
                         0
                         1
                         nil
                         nil
                         nil))))
             (reclaim-managed-simple-vector local-stack)
             (if invocation? t nil)))
          (t (reclaim-managed-simple-vector local-stack)
             nil))))

;;; The function `called-by-default-handler-p'  is used to determine
;;; if a given code body invocation is down the call tree from a
;;; particular procedure.  It is used for the purposes of preventing
;;; infinite loops involving user defined logbook or default error
;;; handlers.

(defun called-by-default-handler-p
    (code-body-invocation default-handler)
  (let ((method-declaration? (frame-of-class-p default-handler 'method-declaration)))
    (loop
      for caller? = code-body-invocation
                  then (code-body-caller caller?)
      for procedure-invocation? =
      (if caller?
          (procedure-invocation-of-code-body caller?))
      for procedure-to-compare =
      (if procedure-invocation?
          (procedure-of-invocation procedure-invocation?))
      for counter fixnum = 0
                  then (incf counter)

      while (and (code-body-invocation-p caller?)
                 (< counter 50))
      do

      (when (or (eq default-handler procedure-to-compare)
                (and method-declaration?
                     (frame-of-class-p procedure-to-compare 'method)
                     (eq (name-or-names-for-frame default-handler)
                         (procedure-method-name procedure-to-compare))))
        (return t)))
    ))


;;; Logbook and Message Board Handlers cont..

;;; This section contains facilities used in BOOKS for user defined
;;; message board and logbook handling.  These facilities have been
;;; moved here to avoid excessive numbers of forward references in
;;; BOOKS.

;;; The function  `user-defined-message-handler-arguments-p' determines
;;; whether a given procedure has the correct argument list to be
;;; registered as a message handler.
;;; This is used in BOOKS and is included here to avoid forward references
;;; to argument-list-description, argument-count, and var-type-from-index.

(defun-simple check-user-defined-message-handler-arguments (procedure)
  (or (valid-user-defined-message-handler-p procedure)
      (stack-error cached-top-of-stack
                   "Attempt to register ~NF failed. Message handler ~
                    must take one argument of type text." procedure)))

;;; The function `invoke-user-defined-message-handler' is used to start a
;;; default message handler procedure, with a given text argument.  This
;;; function is used is BOOKS.

(defun invoke-user-defined-message-handler
    (text procedure)
  (cond
    ((valid-user-defined-message-handler-p procedure)
     (let ((arg-vector (allocate-managed-simple-vector 1)))
       (setf (svref arg-vector 0) text)
       (with-three-thousand-variables-bound
           (start-procedure-invocation-in-place
             procedure
             nil nil
             arg-vector
             0
             1
             nil nil nil nil nil)
         (reclaim-managed-simple-vector arg-vector)))
     t)
    (t
     (let ((allow-user-defined-logbook-handlers-p
             (not currently-posting-message-on-logbook-p)))
       (notify-user "The currently registered message handler ~NF no ~
                     longer conforms to the necessary specification.  ~
                       Message handler must take one argument of type text."
                    procedure))
     nil)))


;;; The function `pass-loop-check-for-user-defined-message-handler-p'
;;; does some primitive checking to see whether invoking a given
;;; user defined message handler at this point could cause an infinite loop.
;;; This procedure performs two checks.
;;; 1. Is the *current-computation-frame* eq to the handler
;;; 2. If the current-computation-instance is defined and is a
;;;    code-body-invocation then search the callers to find if
;;;    the handler is a caller of the current invocation

(defun pass-loop-check-for-user-defined-message-handler-p
    (procedure)
    (not (or (and (boundp '*current-computation-frame*)
                (eq *current-computation-frame* procedure))
           (and (boundp 'current-computation-instance)
                current-computation-instance
                (code-body-invocation-p current-computation-instance)
                (called-by-default-handler-p current-computation-instance
                                             procedure)))))

;;; This check is necessary because logbook message handlers could contain
;;; errors, and thus could by default be posted to the logbook.

(defun pass-loop-check-to-write-error-to-logbook-p
    (code-body-invocation)
  (and (if user-defined-logbook-handling-procedure?
             (not
               (called-by-default-handler-p code-body-invocation
                                            user-defined-logbook-handling-procedure?))
           t)
       (if user-defined-message-board-handling-procedure?
             (not
               (called-by-default-handler-p code-body-invocation
                                            user-defined-message-board-handling-procedure?))
           t)))


(eval-when (#-translating :compile-toplevel :load-toplevel :execute)

(defparameter c-byte-code-lisp-macros
  '())

(defparameter ab-pkg (find-package "AB"))
(defparameter lisp-pkg
  #+ansi-cl (find-package "COMMON-LISP")
  #-ansi-cl (find-package "LISP"))


(defun fixnump-function (thing)
  (fixnump thing))

(defun development-only-function-called-from-compiled-kb (name)
  (cerror "Continue"
          "The undefined function ~S was called from a compiled kb." name))

(defun inlined-function-data (fn)
  (loop for data in c-byte-code-inlined-functions
        do
    (when (eq (car-of-cons data) fn)
      (return data))))

(defun inlined-function-data-given-arg-count (fn argcount)
  (loop for data in c-byte-code-inlined-functions
        do
    (when (and (eq (car-of-cons data) fn)
               (let ((count (inlined-function-arity data)))
                 (or (null count)
                     (eq count :n-ary)
                     (=f count argcount))))
      (return data))))

(defun inlined-function-c-name (data)
  (second data))

(defun inlined-function-argument-type (data)
  (third data))

(defun inlined-function-return-type (data)
  (fourth data))

;;; This can be nil, a number or the symbol :n-ary. This is currently unused,
;;; but could be used, say, to have - expand into "negate" or "minus", depending on the
;;; number of arguments.

(defun inlined-function-arity (data)
  (fifth data))

;;; For n-ary-functions, this parameter represents the number of "non-arguments" in
;;; the list -
;;; in other words, FUNCALL_3 actually takes four arguments - three
;;; function arguments, plus the function itself.  VALUES_3 really does
;;; take three arguments.  (However, VALUES is no longer used.)
;;; For functions that take a fixed number of args, this is not used, and should be nil.

(defun inlined-function-numbered (data)
  (sixth data))


;;; Really should make a hash-table here, and fix the above accessors.

(defun make-inlined-function-table (data) data)

(defparameter c-byte-code-inlined-functions ; 83
  (make-inlined-function-table
    '((*e "DOUBLE_TIMES" :double :double 2)
      (*l "LONG_TIMES" :long :long 2)
      (*f "FIXNUM_TIMES" :object :object 2)
      (+e "DOUBLE_ADD" :double :double 2)
      (+l "LONG_ADD" :long :long 2)
      (+f "FIXNUM_ADD" :object :object 2)
      ; +  untyped + was used in the in-line-evaluator random-quantity-2
      (-e "DOUBLE_NEGATE" :double :double 1)
      (-l "LONG_NEGATE" :long :long 1)
      (-e "DOUBLE_MINUS" :double :double 2)
      (-l "LONG_MINUS" :long :long 2)
      (-f "FIXNUM_NEGATE" :object :object 1)
      (-f "FIXNUM_MINUS" :object :object 2)
      ; -  untyped - was used in the in-line-evaluator random-quantity-2
      (/e "DOUBLE_DIVIDE" :double :double 2)
      (/l "LONG_DIVIDE" :long :long 2)
      (/f "FIXNUM_DIVIDE" :object :object 2)
      (inline-ceiling-1 "CEILING" :double :object 1)
      (inline-floor-1 "FLOOR" :double :object 1)
      (1-e "DOUBLE_SUB1" :double :double 1)
      (1-f  "FIXNUM_SUB1" :object :object 1)
      (/=e "DOUBLE_NE" :double :boolean 2)
      (/=l "LONG_NE" :long :long 2)
      (/=f "FIXNUM_NE" :object :boolean 2)
      (<e "DOUBLE_LT" :double :boolean 2)
      (<l "LONG_LT" :long :boolean 2)
      (<f "FIXNUM_LT" :object :boolean 2)
      (<=e "DOUBLE_LE" :double :boolean 2)
      (<=l "LONG_LE" :long :boolean 2)
      (<=f "FIXNUM_LE" :object :boolean 2)
      ; <= untyped <= was used in the in-line-evaluator random-quantity
      (=e "DOUBLE_EQ" :double :boolean 2)
      (=l "LONG_EQ" :long :boolean 2)
      (=f "FIXNUM_EQ" :object :boolean 2)
      (>e "DOUBLE_GT" :double :boolean 2)
      (>l "LONG_GT" :long :boolean 2)
      (>f "FIXNUM_GT" :object :boolean 2)
      (>=e "DOUBLE_GE" :double :boolean 2)
      (>=l "LONG_GE" :long :boolean 2)
      (>=f "FIXNUM_GE" :object :boolean 2)
      ; >=  untyped <= was used in the in-line-evaluator random-quantity-2
      (pluspe "DOUBLE_PLUSP" :double :boolean 1)
      (pluspf "FIXNUM_PLUSP" :object :boolean 1)
      (maxe "DOUBLE_MAX" :double :double 2)
      (maxf "FIXNUM_MAX" :object :object 2)
      ; max untyped max was used in the in-line-evaluator max-quantity
      (mine "DOUBLE_MIN" :double :double 2)
      (minf "FIXNUM_MIN" :object :object 2)
      ; min  untyped min was used in the in-line-evaluator min-quantity
      (logiorf "FIXNUM_LOGIOR" :object :object 2)
      (logandf "FIXNUM_LOGAND" :object :object 2)
      (logandc2f "FIXNUM_LOGANDC2" :object :object 2)
      ;; Don't inline ashf; macroexpand it into right-shiftf or
      ;; left-shiftf, and inline those instead. -alatto, 8/18/98
      ;;ashf
      (right-shiftf "FIXNUM_RSH" :object :object 2)
      (left-shiftf "FIXNUM_LSH" :object :object 2)
      (float "FLOAT" (:object :double) :double 2)
      (abse "DOUBLE_ABS" :double :double 1)
      (absf "FIXNUM_ABS" :object :object 1)
      (atane "atan" :double :double 1)
      (atane "atan2" :double :double 2)
      (cose "cos" :double :double 1)
      (expe "exp" :double :double 1)
      (sine "sin" :double :double 1)
      (sqrte "sqrt" :double :double 1)
      (tane "tan" :double :double 1)
      (loge "log" :double :double 1)
      (fixnump "FIXNUMP" :object :boolean 1)
      (eq "EQ" :object :boolean 2)
      (not "!" :boolean :boolean 1)
      (null "ISNULL" :object :boolean 1)
      (symbolp "SYMBOLP" :object :boolean 1)
      (atom "ATOM" :object :boolean 1)
      (consp "CONSP" :object :boolean 1)
      (simple-vector-p "SIMPLE_VECTOR_P" :object :boolean 1)
      (double-float-vector-p "DOUBLE_FLOAT_VECTOR_P" :object :boolean 1)
      (long-vector-p "LONG_VECTOR_P" :object :boolean 1)
      (inline-unsigned-byte-16-vector-p "INLINE_UNSIGNED_BYTE_16_VECTOR_P" :object :boolean 1)
      (svref "SVREF" :object :object 2)
      (byte-vector-aref "BYTE_VECTOR_AREF" :object :object 2)
      (float-vector-aref "FLOAT_VECTOR_AREF" :object :double 2)
      (long-vector-aref "LONG_VECTOR_AREF" :object :long 2)
      (car "M_CAR" :object :object 1)
      (car-of-cons "M_CAR" :object :object 1)
      (cdr "M_CDR" :object :object 1)
      (cdr-of-cons "M_CDR" :object :object 1)
      (length "rtl_length" :object :object 1)
      (float-vector-length "SIMPLE_ARRAY_ANY_1_LENGTH" :object :object 1)
      (long-vector-length "SIMPLE_ARRAY_ANY_1_LENGTH" :object :object 1)
      (compiled-function-p "COMPILED_FUNCTION_P" :object :boolean 1)
      (compiled-function-in-place) ; omitted in emitted code, since it's the identity in C
      (symbol-plist-for-lookup "INLINE_SYMBOL_PLIST" :object :object 1)
      (funcall-compiled-function "funcall_compiled_function_" :object :object :n-ary 1)
      (funcall-simple-compiled-function "inline_funcall_" :object :object :n-ary 1)
      ;; used to pass through to phase 2, where it gets transformed to
      ;; funcall-simple-compiled-function.
      (funcall-simple-compiled-function-without-decaching "inline_funcall_" :object :object :n-ary 1)
      (funcall-simple-multi-valued-compiled-function "inline_funcall_" :object :object :n-ary 1)
      ;; These aren't really functions, but they work enough like functions
      ;; for the emitter to get away with treating them like functions:
      (incff "INCFF" :object :object 2)
      (decff "DECFF" :object :object 2)
      (call-function "call_function_" :object :object :n-ary 1)
      (call-simple-function "call_simple_function_" :object :object :n-ary 1)
      (call-simple-function-without-decaching "call_simple_function_" :object :object :n-ary 1)
      (debug-print-byte-code-pc-and-tos "debug_print_byte_code_pc_and_tos" :object :int 2)
      (debug-print-byte-code-pc-stack-base-and-offset
       "debug_print_byte_code_pc_stack_base_and_offset" :object :int 3)

      ;; Argument type for the next two is irrelevant; special-cased in emitter.
      (get-variable "get_variable" :int :object 1)
      (get-constant "get_constant" :int :object 1)
      (svref-without-inlining) ; gets converted to svref in lisp-for-stack-instruction-form
      (svref-with-inlining) ; gets converted to svref in lisp-for-stack-instruction-form
      (decache-local-var-vector) ; expanded by constant-folder, when we
      (cache-local-var-vector)   ; know how many local vars there are.
      (decache-stack)            ; expanded by constant-folder, when we
                                 ; know how many live stack vars there are.
      (incff-top-of-stack-with-caching) ; expanded in constant-folder.
      (decache-for-funcall-instruction) ; expanded in constant-folder.
      #+development (break) ; For emit-lisp-p only
      #+development (print) ; for emit-lisp-p only
      )))

(defparameter c-byte-code-local-arguments
  '(byte-code-body
    constant-vector
    local-var-vector
    fixnum-time-limit?
    initial-program-counter
    initial-top-of-stack
    initial-stack-frame-base
    initial-recursion-depth))

;;; The single interpreter variable top-of-stack gets replaced
;;; by the sum of stack-frame-base and a new variable, stack-offset.
;;; Stack-offset should always be constant-folded out of existence, and
;;; never appears in compiled code.

;;; top-of-stack is only set immediately before branching to the epilog.

(defmacro set-top-of-stack ()
  '(setq top-of-stack (+f stack-frame-base stack-offset)))

(defparameter c-byte-code-local-variables
  '#.(loop for binding in stack-eval-locals-bindings
           for var = (if (consp binding) (car binding) binding)
           collect (case var
                     (instruction-count 'instruction-count-plus-pc)
                     (top-of-stack 'stack-offset)
                     (t var))))

(defparameter c-byte-code-function-alist nil)
(defparameter c-byte-code-constant-alist nil)
(defparameter c-byte-code-variable-alist nil)
(defparameter c-byte-code-foldable-variable-alist nil)

(defun add-index-to-alist (name index alist-symbol &optional properties)
  (let ((assoc-for-index (loop for assoc in (symbol-value alist-symbol)
                               when (eql (cadr assoc) index)
                                 return assoc)))
    (cond ((null assoc-for-index)
           (push (list name index properties)
                 (symbol-value alist-symbol)))
          ((not (equal (car assoc-for-index) name))
           (error "An item with index ~s already exists in alist ~s"
                  index alist-symbol))
          (t
           (setf (cddr assoc-for-index) (list properties))))))

(def-structure (function-info
                 (:constructor
                   make-function-info-internal
                   (function-name function-index
                     throws-stack-error
                     stack-reads
                     stack-writes))
                 #+development
                 (:print-function print-function-info))
  function-name
  function-index
  ;; value is :always, :never, :sometimes, :float, :breakpoint, or :unknown
  throws-stack-error
  ;; value is one of:
  ;; nil (does not read the stack)
  ;; t (reads the stack in arbitrary ways)
  ;; n, a fixnum (reads the top n entries on the stack,
  ;;      from top-of-stack to top-of-stack - n + 1, inclusive.
  stack-reads
  ;; value is one of:
  ;; nil (does not write the stack)
  ;; t (writes the stack in arbitrary ways)
  ;; :reclaim (reclaims the entire stack, but doesn't otherwise
  ;;           use it)
  ;; (m n), a list of two fixnums (writes entries on the
  ;; stack from location m to location n, inclusive;
  ;; for example, (0 0) means rewrites the top of the stack,
  ;; (1 1) means it pushes a new element on the stack,
  ;; and a function that pops three arguments off the stack,
  ;; then pushes two return values would have a stack-writes
  ;; of (-2 -1).
  ;; A function that throws a stack error will then reclaim the entire stack,
  ;; but this should not be indicated by stack-writes; It's the
  ;; responsibility of the users of function-info to be aware of this,
  ;; and use the stack-writes slot in conjuction with the throws-stack-error
  ;; slot.
  stack-writes)

#+development
(defun print-function-info (function-info stream depth)
  (declare (ignore depth))
  (printing-random-object (function-info stream)
    (format stream "FUNCTION-INFO ~A"
            (function-name function-info))))

(defun make-function-info (name index &optional (returns :unknown) (stack-reads t) (stack-writes t))
  (make-function-info-internal name index returns stack-reads stack-writes))

(defmacro declare-c-byte-code-function (name index &rest options)
  `(add-index-to-alist
     ',name ',index 'c-byte-code-function-alist
     (make-function-info ',name ,index
                         ,@(loop for option in options
                                 collect `',option))))

(defmacro declare-environment-dependent-c-byte-code-function
    (development-name distribution-name index &rest options)
  (declare (ignore #+development distribution-name
                   #-development development-name))
  (let ((name #+development development-name #-development distribution-name))
    `(add-index-to-alist
       ',name ',index 'c-byte-code-function-alist
       (make-function-info ',name
                           ,index
                           ,@(loop for option in options
                                   collect `',option)))))

(defmacro declare-c-byte-code-constant (name index &rest options)
  `(add-index-to-alist ',name ',index 'c-byte-code-constant-alist ',options))

(defmacro declare-c-byte-code-variable (name index &rest options)
  `(add-index-to-alist ',name ',index 'c-byte-code-variable-alist ',options))

(defmacro declare-c-byte-code-foldable-variable (name index &rest options)
  `(progn (add-index-to-alist 't ',index 'c-byte-code-foldable-variable-alist ',options)
          (add-index-to-alist ',name ',index 'c-byte-code-variable-alist ',options)))

(defmacro declare-class-description-variables
    ((min-variable-index max-variable-index) (min-list-position max-list-position))
  `(progn
     ,@(loop for list-position from min-list-position to max-list-position
             for variable-index from min-variable-index to max-variable-index
             for class in (nthcdr min-list-position classes-type-checked-inline)
             for class-description-variable
                 = (intern (format nil "~A-~A" class 'class-description))
             collect `(declare-c-byte-code-variable ,class-description-variable ,variable-index))))

;;; funcalled evaluators and instructions are coded in the database as not
;;; reading or writing the stack, since their stack usage is handled differently
(defmacro declare-c-byte-code-funcalled-instruction (name &rest args)
  (let ((function-name (intern (format nil "FUNCALL-~A-INST" name))))
    `(declare-c-byte-code-function ,function-name ,@args nil nil)))

(defmacro declare-c-byte-code-funcalled-evaluator (name &rest args)
  (let ((function-name (intern (format nil "EVAL-~A-FUNCALLED" name))))
    `(declare-c-byte-code-function ,function-name ,@args nil nil)))

(defparameter oldest-compatible-byte-code-version 1)
(defparameter current-compiled-byte-code-version 2)

(defun-simple check-compiled-code-version (loaded-version)
  (and (fixnump loaded-version)
       (<=f oldest-compatible-byte-code-version loaded-version)))

(declare-c-byte-code-constant :completed 0)
(declare-c-byte-code-constant *current-computation-frame* 1)
(declare-c-byte-code-constant error 2)
(declare-c-byte-code-constant eval 3)
(declare-c-byte-code-constant float 4)
(declare-c-byte-code-constant g2-defstruct-structure-name::code-body-invocation-g2-struct 5)
(declare-c-byte-code-constant g2-defstruct-structure-name::formula-invocation-g2-struct 6)
(declare-c-byte-code-constant g2-defstruct-structure-name::rule-instance-g2-struct 7)
(declare-c-byte-code-constant gensym 8)
(declare-c-byte-code-constant inference-engine 9)
(declare-c-byte-code-constant integer 10)
(declare-c-byte-code-constant item 11)
(declare-c-byte-code-constant item-or-datum 12)
(declare-c-byte-code-constant item-or-value 13)
(declare-c-byte-code-constant iteration-state 14)
(declare-c-byte-code-constant kb-workspace 15)
(declare-c-byte-code-constant ln 16)
(declare-c-byte-code-constant log 17)
(declare-c-byte-code-constant message-and-breakpoint-overrides 18)
(declare-c-byte-code-constant name-or-names-for-frame 19)
(declare-c-byte-code-constant never 20)
(declare-c-byte-code-constant number 21)
(declare-c-byte-code-constant parameter 22)
(declare-c-byte-code-constant parent-attribute-name 23)
(declare-c-byte-code-constant procedure 24)
(declare-c-byte-code-constant quotient 25)
(declare-c-byte-code-constant random 26)
(declare-c-byte-code-constant sequence 27)
(declare-c-byte-code-constant simulated-value 28)
(declare-c-byte-code-constant simulator 29)
(declare-c-byte-code-constant sqrt 30)
(declare-c-byte-code-constant structure 31)
(declare-c-byte-code-constant symbol 32)
(declare-c-byte-code-constant t 33)
(declare-c-byte-code-constant text 34)
(declare-c-byte-code-constant truncate 35)
(declare-c-byte-code-constant truth-value 36)
(declare-c-byte-code-constant variable-or-parameter 37)
(declare-c-byte-code-constant "The stack should have been -1, was ~a." 38)
(declare-c-byte-code-constant "Tell Joe that he's wrong" 39)
(declare-c-byte-code-constant "integer array" 40)
(declare-c-byte-code-constant "value array" 41)
(declare-c-byte-code-constant role-server 42)
(declare-c-byte-code-constant unique-value-of-role-server-function 43)
(declare-c-byte-code-constant available-frame-vector 44)
(declare-c-byte-code-constant g2-defstruct-structure-name::class-description-g2-struct 45)
(declare-c-byte-code-constant nth-element-of-float-array 46)
(declare-c-byte-code-constant nth-element-of-integer-array 47)
(declare-c-byte-code-constant nth-element-of-value-array 48)
(declare-c-byte-code-constant name-of-item 49)
(declare-c-byte-code-constant g2-defstruct-structure-name::procedure-invocation-g2-struct 50)
;;; These can get deleted once I code types as immediates on stack,
;;; instead of as constants                            -alatto, 7/6/98
(declare-c-byte-code-constant frame 51)
(declare-c-byte-code-constant no-item 53)
(declare-c-byte-code-constant unknown 54)
(declare-c-byte-code-constant defined-evaluation-type-copier 55)
(declare-c-byte-code-constant :none 56)
(declare-c-byte-code-constant :formula-invocation 57)
(declare-c-byte-code-constant :unknown 58)
(declare-c-byte-code-constant :code-body-invocation 59)
(declare-c-byte-code-constant :rule-instance 60)
(declare-c-byte-code-constant defined-evaluation-type-reclaimer 61)
(declare-c-byte-code-constant round 62)
(declare-c-byte-code-constant g2-defstruct-structure-name::longstruct-g2-struct 63)
(declare-c-byte-code-constant g2-defstruct-structure-name::g2longint-g2-struct 64)
(declare-c-byte-code-constant :error 65)
(declare-c-byte-code-constant :awaiting-lock 66)

(declare-c-byte-code-variable *variables-that-did-not-have-values* 0)
(declare-c-byte-code-variable available-eval-conses 1)
(declare-c-byte-code-variable available-gensym-conses 2)
(declare-c-byte-code-variable breakpoint-level 3)
(declare-c-byte-code-variable cached-byte-code-body 4)
(declare-c-byte-code-variable cached-stack-frame-base 5)
(declare-c-byte-code-variable cached-stack-program-counter 6)
(declare-c-byte-code-variable cached-top-of-stack 7)
(declare-c-byte-code-variable current-computation-activity 8)
(declare-c-byte-code-variable current-computation-component-particulars 9)
(declare-c-byte-code-variable current-computation-flags 10)
(declare-c-byte-code-variable *current-computation-frame* 11)
(declare-c-byte-code-variable current-computation-instance 12)
(declare-c-byte-code-variable current-environment 13)
(declare-c-byte-code-variable current-profile-structure? 14)
(declare-c-byte-code-variable current-simulation-runtime-structure 15)
(declare-c-byte-code-variable debugging-parameters 16)
(declare-c-byte-code-variable debugging-reset 17)
(declare-c-byte-code-variable defined-evaluation-datum-types 18)
(declare-c-byte-code-variable dont-backward-chain-in-sim-eval? 19)
(declare-c-byte-code-variable dont-proceed-to-next-variable? 20)
(declare-c-byte-code-variable eval-car-marker 21)
(declare-c-byte-code-variable evaluation-false-value 22)
(declare-c-byte-code-variable evaluation-true-value 23)
(declare-c-byte-code-variable exit-stack-eval 24)
(declare-c-byte-code-variable falsity 25)
(declare-c-byte-code-variable foreign-function-declaration-class-description 26)
(declare-c-byte-code-foldable-variable funcalled-evaluator-dispatch-type 27)
(declare-c-byte-code-variable funcalled-evaluator-functions 28)
(declare-c-byte-code-variable funcalled-instruction-functions 29)
(declare-c-byte-code-variable function-definition-class-description 30)
(declare-c-byte-code-variable gensym-time 31)
(declare-c-byte-code-variable gensym-time-at-start 32)
(declare-c-byte-code-variable inference-engine-parameters 33)
(declare-c-byte-code-variable initializing-simulator? 34)
(declare-c-byte-code-variable most-negative-fixnum 35)
(declare-c-byte-code-variable most-positive-fixnum 36)
(declare-c-byte-code-variable noting-changes-to-kb-p 37)
(declare-c-byte-code-variable number-of-extra-stack-frame-values 38)
(declare-c-byte-code-variable number-of-simulated-variables-processed 39)
(declare-c-byte-code-variable number-of-variables-to-process-at-a-time 40)
(declare-c-byte-code-variable priority-of-current-task 41)
(declare-c-byte-code-variable profiling-enabled? 42)
(declare-c-byte-code-variable ran-out-of-time? 43)
(declare-c-byte-code-variable stack-expiration 44)
(declare-c-byte-code-variable system-is-running 45)
(declare-c-byte-code-variable tabular-function-class-description 46)
(declare-c-byte-code-variable tracing-message-level 47)
(declare-c-byte-code-variable truth 48)
(declare-c-byte-code-variable kb-workspace-class-description 49)
(declare-c-byte-code-variable global-stack 50)
(declare-c-byte-code-variable c-byte-code-body-result-1 51)
(declare-c-byte-code-variable c-byte-code-body-result-2 52)
(declare-c-byte-code-variable c-byte-code-body-result-3 53)
(declare-c-byte-code-variable c-byte-code-body-result-4 54)
(declare-c-byte-code-variable c-byte-code-body-result-5 55)
(declare-c-byte-code-variable c-byte-code-body-result-6 56)
(declare-c-byte-code-variable c-byte-code-body-result-7 57)
(declare-c-byte-code-variable c-byte-code-body-result-8 58)
(declare-c-byte-code-variable cached-fixnum-time-limit? 59)
(declare-c-byte-code-variable forgive-long-procedure-instruction? 60)
(declare-c-byte-code-variable cached-fixnum-start-time 61)
(declare-c-byte-code-foldable-variable funcalled-instructions 62)
(declare-c-byte-code-foldable-variable funcalled-evaluator-array 63)
;; (length classes-type-checked-inline) = 130
(declare-class-description-variables (64 193) (0 129))
(declare-c-byte-code-variable MOST-POSITIVE-FIXNUM-AS-FLOAT 194)
(declare-c-byte-code-variable MOST-NEGATIVE-FIXNUM-AS-FLOAT 195)
;; next: (declare-class-description-variables (196 197) (130 131))

(declare-environment-dependent-c-byte-code-function eval-cons-1 gensym-cons-1 0 :never nil nil) ; (expr)
(declare-environment-dependent-c-byte-code-function reclaim-eval-cons-1 reclaim-gensym-cons-1 1 :never nil nil)
(declare-c-byte-code-function abort-called-code-bodies-function 2 :never nil nil)
(declare-c-byte-code-function abs-fixnum-overflow-error-message 3 :never nil nil)
(declare-c-byte-code-function add-evaluation-quantities 4 :float nil nil)
(declare-c-byte-code-function allocate-managed-simple-float-array 5 :never nil nil) ;(expr)
;;; The corresponding function to the following is no longer called. - jpg 4/23/02
;(declare-c-byte-code-function arg-to-random-operator-is-most-positive-fixnum-message 6 :never nil nil)
(declare-c-byte-code-function arg1-not-less-than-arg2-eval-error-message 7 :never nil nil)
(declare-c-byte-code-function attempt-to-coerce-to-gensym-float 8 :never nil nil)
(declare-c-byte-code-function attribute-item-eval-error-message 9 :never nil nil)
(declare-c-byte-code-function bad-g2-array-index-error-1 10 :never nil nil)
(declare-c-byte-code-function begin-call-to-function-definition 11 :never t t) ;
(declare-c-byte-code-function begin-return-from-function-definition 12 :breakpoint t t)
(declare-c-byte-code-function c-native-clock-ticks-or-cache 13 :never nil nil) ;(expr)
(declare-c-byte-code-function cached-attribute-value-no-value-error-1 14 :never nil nil)
(declare-c-byte-code-function cached-item-error-message 15 :never nil nil)
(declare-c-byte-code-function call-remote-procedure 16 :never t nil) ; *** Does this really read the stack? -alatto, 2/12/99
(declare-c-byte-code-function call-tabular-function 17 :never t nil) ; ** check this
(declare-c-byte-code-function ceiling-float-error-message 18 :never nil nil)
(declare-c-byte-code-function check-stack-error-message 19 :never nil nil)
(declare-c-byte-code-function class-description-subclass-of-class-description-p-function 20 :never nil nil) ; (expr)
(declare-c-byte-code-function clean-up-wake-ups-state-if-any 21 :never nil nil)
(declare-c-byte-code-function clear-pending-wake-ups 22 :never nil nil)
(declare-c-byte-code-function close-code-body-invocation 23 :never nil nil)
(declare-c-byte-code-function close-evaluation-iteration-state-continuation 24 :never nil nil)
(declare-c-byte-code-function coerce-arguments-and-call-foreign-function 25 :never t nil) ; ** check this
(declare-c-byte-code-function coerce-evaluation-value-to-quantity 26 :never nil nil)
(declare-c-byte-code-function coerce-matching-element-type-or-unknown 27 :never nil nil)
(declare-c-byte-code-function complete-formula-function 28 :never nil nil)
(declare-c-byte-code-function compute-remainder-float 29 :float nil nil)
(declare-c-byte-code-function compute-remainder-quantity 30 :float nil nil)
(declare-c-byte-code-function copy-evaluation-value-1 31 :never nil nil)
(declare-c-byte-code-function copy-if-evaluation-value-1 32 :never nil nil)
(declare-c-byte-code-function copy-managed-float 33 :never nil nil)
;; note: copy-wide-string replaced
;; copy-text-string-into-simple-or-adjustable-text-string. (MHD 9/10/04)
(declare-c-byte-code-function copy-wide-string 34 :never nil nil)
(declare-c-byte-code-function distance-between-icons-if-in-same-workspace 35 :never nil nil)
(declare-c-byte-code-function enqueue-immediate-code-body-invocation 36 :never nil nil)
(declare-c-byte-code-function enter-next-simulation-variable-context 37 :breakpoint nil nil)
(declare-c-byte-code-function evaluation-quantity-/= 38 :never nil nil) ; (expr)
(declare-c-byte-code-function evaluation-quantity-< 39 :never nil nil) ; (expr)
(declare-c-byte-code-function evaluation-quantity-<= 40 :never nil nil) ; (expr)
(declare-c-byte-code-function evaluation-quantity-= 41 :never nil nil) ; (expr)
(declare-c-byte-code-function evaluation-quantity-> 42 :never nil nil) ; (expr)
(declare-c-byte-code-function evaluation-quantity->= 43 :never nil nil) ; (expr)
(declare-c-byte-code-function evaluation-value-= 44 :never nil nil) ; (expr)
(declare-c-byte-code-function execute-create-connection-stack-instruction 45 :sometimes 14 (-13 -13))
(declare-c-byte-code-function execute-invoke-stack-instruction 46 :sometimes 2 nil)
(declare-c-byte-code-function execute-show-stack-instruction 47 :sometimes 3 nil)
(declare-c-byte-code-function exit-computation-context-for-code-body-invocation 48 :breakpoint nil nil)
(declare-c-byte-code-function exit-computation-context-for-variable-formula 49 :breakpoint nil nil)
(declare-c-byte-code-function exit-last-rule-instance-context 50 :breakpoint nil nil)
(declare-c-byte-code-function exit-last-simulation-variable-context 51 :breakpoint nil nil)
(declare-c-byte-code-function expt-evaluation-quantities 52 :float nil nil)
(declare-c-byte-code-function fetch-and-enter-next-current-computation-instance 53 :never nil nil) ; ** check this
(declare-c-byte-code-function fetch-attribute-frame-or-place-reference 54 :sometimes nil nil)
(declare-c-byte-code-function fetch-element-frame-or-place-reference 55 :sometimes nil nil)
(declare-c-byte-code-function fetch-nth-element 56 :sometimes nil nil)
(declare-c-byte-code-function fetch-unique-value-of-role-for-stack 57 :sometimes nil nil)
(declare-c-byte-code-function filo-enqueue-immediate-code-body-invocation 58 :never nil nil)
(declare-c-byte-code-function floor-evaluation-error-message 59 :never nil nil)
(declare-c-byte-code-function frame-or-evaluation-value-given-user-vector-index 60 :never nil nil)
(declare-c-byte-code-function frame-or-evaluation-value-user-attribute-value 61 :never nil nil) ; ** check this
(declare-c-byte-code-function g2-exponent-evaluation-float 62 :float nil nil)
(declare-c-byte-code-function g2-list-length 63 :never nil nil)
(declare-c-byte-code-function g2-random 64 :never nil nil) ; (expr)
;(declare-c-byte-code-function g2-round-evaluation-float 65 :float nil nil)
(declare-c-byte-code-function g2-to-g2-data-interface-p-function 66 :never nil nil) ; (expr)
(declare-c-byte-code-function generate-code-body-invocation 67 :never nil nil)
(declare-c-byte-code-function get-current-evaluation-value 68 :never nil nil) ; ** check this
(declare-c-byte-code-function get-current-evaluation-value-from-simulation-environment 69 :never nil nil) ; (expr)
(declare-c-byte-code-function get-current-time-in-simulation-environment 70 :never nil nil)
(declare-c-byte-code-function get-lookup-slot-value-given-default 71 :never nil nil) ; (expr)
(declare-c-byte-code-function get-real-gensym-time 72 :never nil nil)
(declare-c-byte-code-function getfq-function-no-default 73 :never nil nil)
(declare-c-byte-code-function gsi-interface-p-function 74 :never nil nil) ; (expr)
(declare-c-byte-code-function increment-profiling-calls 75 :never nil nil)
(declare-c-byte-code-function item-distance-eval-error-message 76 :never nil nil)
(declare-c-byte-code-function log-10 77 :float nil nil)
(declare-c-byte-code-function lookup-name-reference 78 :never nil nil)
(declare-c-byte-code-function make-evaluation-float-from-evaluation-integer 79 :never nil nil)
(declare-c-byte-code-function make-evaluation-quantity 80 :never nil nil)
(declare-c-byte-code-function memq-function 81 :never nil nil) ; (expr)
(declare-c-byte-code-function multiply-evaluation-quantities 82 :float nil nil)
(declare-c-byte-code-function name-of-item-invalid-reference-message 83 :never nil nil)
(declare-c-byte-code-function name-reference-error-message 84 :never nil nil)
(declare-c-byte-code-function negative-arg-eval-error-message 85 :never nil nil)
(declare-c-byte-code-function no-element-for-array-index-error-message 86 :never nil nil)
(declare-c-byte-code-function no-element-for-array-role-index-error-message 87 :never nil nil)
(declare-c-byte-code-function non-positive-arg-eval-error-message 88 :never nil nil)
(declare-c-byte-code-function not-a-function-message 89 :never nil nil)
(declare-c-byte-code-function note-change-to-runtime-data-for-block-1 90 :never nil nil)
(declare-c-byte-code-function of-class-p-function 91 :never nil nil)
(declare-c-byte-code-function open-wake-up-collection-function 92 :never nil nil)
(declare-c-byte-code-function posit-profiling-structure 93 :never nil nil)
(declare-c-byte-code-function prepare-procedure-argument-list-for-stack-procedure 94 :sometimes t t) ; ## fix this
(declare-c-byte-code-function procedure-code-body-given-number 95 :never nil nil)
(declare-c-byte-code-function random-real-0 96 :never nil nil)
(declare-c-byte-code-function raw-stack-error-1 97 :always nil nil)
(declare-c-byte-code-function raw-stack-error-named-error 98 :always nil nil)
(declare-c-byte-code-function raw-stack-error-throw-object-function 99 :always nil nil)
(declare-c-byte-code-function reclaim-evaluation-iteration-state 100 :never nil nil)
(declare-c-byte-code-function reclaim-evaluation-quantity 101 :never nil nil)
(declare-c-byte-code-function reclaim-evaluation-sequence 102 :never nil nil)
(declare-c-byte-code-function reclaim-evaluation-structure 103 :never nil nil)
(declare-c-byte-code-function reclaim-evaluation-value 104 :never nil nil)
(declare-c-byte-code-function reclaim-if-evaluation-value-1 105 :never nil nil)
(declare-c-byte-code-function reclaim-managed-simple-float-array 106 :never nil nil)
(declare-c-byte-code-function reclaim-text-string 107 :never nil nil)
(declare-c-byte-code-function reclaim-top-of-stack 108 :never :reclaim)
(declare-c-byte-code-function rem-fixnums 109 :never nil nil)
(declare-c-byte-code-function return-values-body 110 :never t t) ; ## fix this
(declare-c-byte-code-function role-returned-no-values-error-1 111 :never nil nil)
(declare-c-byte-code-function rpc-not-an-interface-error-message 112 :never nil nil)
(declare-c-byte-code-function schedule-computation-instance-execution 113 :never nil nil)
(declare-c-byte-code-function schedule-wait-for-interval-task 114 :never nil nil) ; (expr)
(declare-c-byte-code-function serve-first-item-or-evaluation-value-of-role 115 :never nil nil) ; ** check this
(declare-c-byte-code-function serve-item-p 116 :never nil nil) ; (expr)
(declare-c-byte-code-function serve-unique-item-or-evaluation-value-of-role 117 :sometimes nil nil)
(declare-c-byte-code-function set-wake-ups-function 118 :never nil nil)
(declare-c-byte-code-function signal-coerce-to-datum-error-message 119 :never nil nil)
(declare-c-byte-code-function signal-nested-code-bodies-out-of-procedures-message 120 :never nil nil)
(declare-c-byte-code-function signal-no-value-in-local-var-error-message 121 :never nil nil)
(declare-c-byte-code-function signal-stack-class-type-check-error-message 122 :never nil nil)
(declare-c-byte-code-function signal-stack-type-check-error-message 123 :never nil nil)
(declare-c-byte-code-function stack-eval<=function 124 :never nil nil)
(declare-c-byte-code-function stack-eval<function 125 :never nil nil)
(declare-c-byte-code-function stack-eval>=function 126 :never nil nil)
(declare-c-byte-code-function stack-eval>function 127 :never nil nil)
(declare-c-byte-code-function string-equalw 128 :never nil nil) ; (expr)
(declare-c-byte-code-function string-greaterpw 129 :never nil nil) ; (expr)
(declare-c-byte-code-function string-lesspw 130 :never nil nil) ; (expr)
(declare-c-byte-code-function string-not-greaterpw 131 :never nil nil) ; (expr)
(declare-c-byte-code-function string-not-lesspw 132 :never nil nil) ; (expr)
(declare-c-byte-code-function subtract-evaluation-quantities 133 :float nil nil)
(declare-c-byte-code-function switch-context-for-procedure-call 134 :never t nil) ; ## fix this
(declare-c-byte-code-function system-pause 135 :never nil nil)
(declare-c-byte-code-function text-string-p 136 :never nil nil) ; (expr)
(declare-c-byte-code-function thing-is-item-p 137 :never nil nil) ; (expr)
(declare-c-byte-code-function thing-is-parameter-p 138 :never nil nil) ; (expr)
(declare-c-byte-code-function thing-is-variable-or-parameter-p 139 :never nil nil) ; (expr)
(declare-c-byte-code-function time-slice-expired-p 140 :never nil nil) ; (expr)
(declare-c-byte-code-function trace-too-many-objects-role-error 141 :never nil nil)
(declare-c-byte-code-function truncate-evaluation-error-message 142 :never nil nil)
(declare-c-byte-code-function truncatef-first 143 :never nil nil)
(declare-c-byte-code-function truth-value-evaluation-number 144 :never nil nil)
(declare-c-byte-code-function type-specification-subtype-p 145 :never nil nil) ; (expr)
(declare-c-byte-code-function type-specification-type-p 146 :never nil nil) ; (expr)
(declare-c-byte-code-function unknown-entry-point-error 147 :never nil nil)
(declare-c-byte-code-function write-major-trace-of-rpc-call 148 :never nil nil)
(declare-c-byte-code-function signal-no-value-in-local-var-error-1 149 :never nil nil)

(declare-c-byte-code-funcalled-instruction conclude 150 :sometimes)
(declare-c-byte-code-funcalled-instruction move 151 :sometimes)
(declare-c-byte-code-funcalled-instruction set-position 152 :sometimes)
(declare-c-byte-code-funcalled-instruction rotate 153 :sometimes)
(declare-c-byte-code-funcalled-instruction set-heading 154 :sometimes)
(declare-c-byte-code-funcalled-instruction conclude-has-no-current-value 155 :sometimes)
(declare-c-byte-code-funcalled-instruction conclude-has-no-value 156 :sometimes)
(declare-c-byte-code-funcalled-instruction focus 157 :sometimes)
(declare-c-byte-code-funcalled-instruction change-item-color 158 :sometimes)
(declare-c-byte-code-funcalled-instruction change-item-color-pattern 159 :sometimes)
(declare-c-byte-code-funcalled-instruction hide 160 :sometimes)
(declare-c-byte-code-funcalled-instruction activate 161 :sometimes)
(declare-c-byte-code-funcalled-instruction deactivate 162 :sometimes)
(declare-c-byte-code-funcalled-instruction set 163 :sometimes)
(declare-c-byte-code-funcalled-instruction inform 164 :sometimes)
(declare-c-byte-code-funcalled-instruction add-relation 165 :sometimes)
(declare-c-byte-code-funcalled-instruction remove-relation 166 :sometimes)
(declare-c-byte-code-funcalled-instruction create 167 :sometimes)
(declare-c-byte-code-funcalled-instruction delete 168 :sometimes)
(declare-c-byte-code-funcalled-instruction transfer 169 :sometimes)
(declare-c-byte-code-funcalled-instruction change-system-attribute 170 :sometimes)
(declare-c-byte-code-funcalled-instruction change-the-text-of-attribute 171 :sometimes)
(declare-c-byte-code-funcalled-instruction change-nth-element 172 :sometimes)
(declare-c-byte-code-funcalled-instruction g2-list-insert-expression 173 :sometimes)
(declare-c-byte-code-funcalled-instruction g2-list-insert-designation 174 :sometimes)
(declare-c-byte-code-funcalled-instruction g2-list-remove-expression 175 :sometimes)
(declare-c-byte-code-funcalled-instruction g2-list-remove-designation 176 :sometimes)
(declare-c-byte-code-funcalled-instruction show-new 177 :sometimes)
(declare-c-byte-code-funcalled-instruction create-explanation 178 :sometimes)
(declare-c-byte-code-funcalled-instruction update 179 :sometimes)
(declare-c-byte-code-funcalled-instruction start 180 :sometimes)
(declare-c-byte-code-funcalled-instruction start-rpc 181 :sometimes)
(declare-c-byte-code-funcalled-instruction format-form 182 :never) ;;; False! For testing.
(declare-c-byte-code-funcalled-instruction is 183 :sometimes)
(declare-c-byte-code-funcalled-instruction is-and-possibly-unknown 184 :sometimes)
(declare-c-byte-code-funcalled-instruction has-a-value 185 :sometimes)
(declare-c-byte-code-funcalled-instruction first-that-has-a-value 186 :sometimes)
(declare-c-byte-code-funcalled-instruction exists 187 :sometimes)
(declare-c-byte-code-funcalled-instruction abort 188 :sometimes)
(declare-c-byte-code-funcalled-instruction shut-down-g2 189 :sometimes)
(declare-c-byte-code-funcalled-instruction create-by-cloning 190 :sometimes)
(declare-c-byte-code-funcalled-instruction make-permanent 191 :sometimes)
(declare-c-byte-code-funcalled-instruction make-subworkspace 192 :sometimes)
(declare-c-byte-code-funcalled-instruction print 193 :sometimes)
(declare-c-byte-code-funcalled-instruction make-transient 194 :sometimes)
(declare-c-byte-code-funcalled-instruction install-event-detector 195 :sometimes)
(declare-c-byte-code-funcalled-instruction clear-event-detectors 196 :sometimes)
(declare-c-byte-code-funcalled-instruction prepare-procedure-arguments 197 :sometimes)
(declare-c-byte-code-funcalled-instruction prepare-possibly-unknown-procedure-arguments 198 :sometimes)
(declare-c-byte-code-funcalled-instruction average-value-1 199 :sometimes)
(declare-c-byte-code-funcalled-instruction average-value-2 200 :sometimes)
(declare-c-byte-code-funcalled-instruction minimum-value-1 201 :sometimes)
(declare-c-byte-code-funcalled-instruction minimum-value-2 202 :sometimes)
(declare-c-byte-code-funcalled-instruction maximum-value-1 203 :sometimes)
(declare-c-byte-code-funcalled-instruction maximum-value-2 204 :sometimes)
(declare-c-byte-code-funcalled-instruction standard-deviation-1 205 :sometimes)
(declare-c-byte-code-funcalled-instruction standard-deviation-2 206 :sometimes)
(declare-c-byte-code-funcalled-instruction number-of-datapoints-0 207 :sometimes)
(declare-c-byte-code-funcalled-instruction number-of-datapoints-1 208 :sometimes)
(declare-c-byte-code-funcalled-instruction number-of-datapoints-2 209 :sometimes)
(declare-c-byte-code-funcalled-instruction rate-of-change-1 210 :sometimes)
(declare-c-byte-code-funcalled-instruction rate-of-change-2 211 :sometimes)
(declare-c-byte-code-funcalled-instruction integral-1 212 :sometimes)
(declare-c-byte-code-funcalled-instruction integral-2 213 :sometimes)
(declare-c-byte-code-funcalled-instruction historic-value 214 :sometimes)
(declare-c-byte-code-funcalled-instruction value-of-previous-datapoint 215 :sometimes)
(declare-c-byte-code-funcalled-instruction interpolated-value 216 :sometimes)
(declare-c-byte-code-funcalled-instruction collection-time-of-previous-datapoint 217 :sometimes)
(declare-c-byte-code-funcalled-instruction coerce-no-item-to-unknown 218 :sometimes)
(declare-c-byte-code-funcalled-instruction collection-time-of 219 :sometimes)
(declare-c-byte-code-funcalled-instruction expiration-time-of 220 :sometimes)
(declare-c-byte-code-funcalled-instruction g2-list-insert 221 :sometimes)
(declare-c-byte-code-funcalled-instruction g2-list-remove 222 :sometimes)
(declare-c-byte-code-funcalled-instruction coerce-item-or-values-to-matching-element-type 223 :sometimes)
(declare-c-byte-code-funcalled-instruction coerce-item-or-values-to-matching-element-type-or-unknown 224 :sometimes)
(declare-c-byte-code-funcalled-instruction g2-list-or-sequence-member-p 225 :sometimes)
(declare-c-byte-code-funcalled-instruction class-qualified-name-frame-or-place-reference 226 :sometimes)
(declare-c-byte-code-funcalled-instruction conclude-attribute 227 :sometimes)
(declare-c-byte-code-funcalled-instruction make-evaluation-sequence 228 :sometimes)
(declare-c-byte-code-funcalled-instruction make-evaluated-structure 229 :sometimes)
(declare-c-byte-code-funcalled-instruction start-kb 230 :sometimes)
(declare-c-byte-code-funcalled-instruction resume-kb 231 :sometimes)
(declare-c-byte-code-funcalled-instruction focus-with-wait 232 :sometimes)
(declare-c-byte-code-funcalled-instruction compare-and-swap 233 :sometimes) ; 83
(declare-c-byte-code-funcalled-instruction concatenate 234 :sometimes)

(declare-c-byte-code-funcalled-evaluator format 235 :sometimes)
(declare-c-byte-code-funcalled-evaluator fixed-format 236 :sometimes)
(declare-c-byte-code-funcalled-evaluator fuzzy-< 237 :sometimes)
(declare-c-byte-code-funcalled-evaluator fuzzy-> 238 :sometimes)
(declare-c-byte-code-funcalled-evaluator fuzzy-= 239 :sometimes)
(declare-c-byte-code-funcalled-evaluator fuzzy-not-= 240 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-more-true-than 241 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-not-more-true-than 242 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-less-true-than 243 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-not-less-true-than 244 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-activated 245 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-deactivated 246 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-enabled 247 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-disabled 248 :sometimes)
(declare-c-byte-code-funcalled-evaluator loses-its-value 249 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-created 250 :sometimes)
(declare-c-byte-code-funcalled-evaluator generic-event 251 :sometimes)
(declare-c-byte-code-funcalled-evaluator generic-becomes-related 252 :sometimes)
(declare-c-byte-code-funcalled-evaluator generic-ceases-to-be-related 253 :sometimes)
(declare-c-byte-code-funcalled-evaluator generic-directly-connected-to 254 :sometimes)
(declare-c-byte-code-funcalled-evaluator generic-directly-disconnected-from 255 :sometimes)
(declare-c-byte-code-funcalled-evaluator directly-connected-to 256 :sometimes)
(declare-c-byte-code-funcalled-evaluator directly-disconnected-from 257 :sometimes)
(declare-c-byte-code-funcalled-evaluator indirectly-connected-to 258 :sometimes)
(declare-c-byte-code-funcalled-evaluator indirectly-disconnected-from 259 :sometimes)
(declare-c-byte-code-funcalled-evaluator get-next-token-3 260 :sometimes)
(declare-c-byte-code-funcalled-evaluator distance-between-and-the-nearest 261 :sometimes)
(declare-c-byte-code-funcalled-evaluator find-next-pattern-3 262 :sometimes)
(declare-c-byte-code-funcalled-evaluator find-next-substring-matching-pattern-3 263 :sometimes)
(declare-c-byte-code-funcalled-evaluator find-and-replace-pattern-5 264 :sometimes)
(declare-c-byte-code-funcalled-evaluator symbol-datum 265 :sometimes)
(declare-c-byte-code-funcalled-evaluator symbol-text 266 :sometimes)
(declare-c-byte-code-funcalled-evaluator get-next-token-4 267 :sometimes)
(declare-c-byte-code-funcalled-evaluator find-next-pattern-4 268 :sometimes)
(declare-c-byte-code-funcalled-evaluator truth-value-of-truth-value 269 :sometimes)
(declare-c-byte-code-funcalled-evaluator truth-value-quantity 270 :sometimes)
(declare-c-byte-code-funcalled-evaluator truth-value-integer 271 :sometimes)
(declare-c-byte-code-funcalled-evaluator truth-value-float 272 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-contained-in-text 273 :sometimes)
(declare-c-byte-code-funcalled-evaluator length-of-text 274 :sometimes)
(declare-c-byte-code-funcalled-evaluator position-of-text 275 :sometimes)
(declare-c-byte-code-funcalled-evaluator text-begins-with-quantity 276 :sometimes)
(declare-c-byte-code-funcalled-evaluator upper-case-text 277 :sometimes)
(declare-c-byte-code-funcalled-evaluator lower-case-text 278 :sometimes)
(declare-c-byte-code-funcalled-evaluator capitalize-words 279 :sometimes)
(declare-c-byte-code-funcalled-evaluator insert-in-text 280 :sometimes)
(declare-c-byte-code-funcalled-evaluator omit-from-text 281 :sometimes)
(declare-c-byte-code-funcalled-evaluator get-from-text 282 :sometimes)
(declare-c-byte-code-funcalled-evaluator quantity-truth-value 283 :sometimes)
(declare-c-byte-code-funcalled-evaluator quantity-quantity 284 :sometimes)
(declare-c-byte-code-funcalled-evaluator quantity-text 285 :sometimes)
(declare-c-byte-code-funcalled-evaluator year 286 :sometimes)
(declare-c-byte-code-funcalled-evaluator month 287 :sometimes)
(declare-c-byte-code-funcalled-evaluator day-of-the-month 288 :sometimes)
(declare-c-byte-code-funcalled-evaluator day-of-the-week 289 :sometimes)
(declare-c-byte-code-funcalled-evaluator hour 290 :sometimes)
(declare-c-byte-code-funcalled-evaluator minute 291 :sometimes)
(declare-c-byte-code-funcalled-evaluator second 292 :sometimes)
(declare-c-byte-code-funcalled-evaluator time 293 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-related 294 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-not-related 295 :sometimes)
(declare-c-byte-code-funcalled-evaluator false 296 :sometimes)
(declare-c-byte-code-funcalled-evaluator receives-a-value 297 :sometimes)
(declare-c-byte-code-funcalled-evaluator fails-to-receive-a-value 298 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-moved 299 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-moved-by-the-user 300 :sometimes)
(declare-c-byte-code-funcalled-evaluator replace-in-text 301 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-moved-by-g2 302 :sometimes)
(declare-c-byte-code-funcalled-evaluator becomes-related 303 :sometimes)
(declare-c-byte-code-funcalled-evaluator ceases-to-be-related 304 :sometimes)
(declare-c-byte-code-funcalled-evaluator nupec-synchronization-occurs 305 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-of-class 306 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-active 307 :sometimes)
(declare-c-byte-code-funcalled-evaluator has-a-name 308 :sometimes)
(declare-c-byte-code-funcalled-evaluator connection-portname 309 :sometimes)
(declare-c-byte-code-funcalled-evaluator connection-side 310 :sometimes)
(declare-c-byte-code-funcalled-evaluator connection-position 311 :sometimes)
(declare-c-byte-code-funcalled-evaluator connection-direction 312 :sometimes)
(declare-c-byte-code-funcalled-evaluator connection-style 313 :sometimes)
(declare-c-byte-code-funcalled-evaluator find-next-substring-matching-pattern-4 314 :sometimes)
(declare-c-byte-code-funcalled-evaluator which-has-the-focal-object 315 :sometimes)
(declare-c-byte-code-funcalled-evaluator which-has-the-focal-class 316 :sometimes)
(declare-c-byte-code-funcalled-evaluator in-the-category 317 :sometimes)
(declare-c-byte-code-funcalled-evaluator with-status 318 :sometimes)
(declare-c-byte-code-funcalled-evaluator with-notes 319 :sometimes)
(declare-c-byte-code-funcalled-evaluator containing 320 :sometimes)
(declare-c-byte-code-funcalled-evaluator containing-word 321 :sometimes)
(declare-c-byte-code-funcalled-evaluator g2-inspect-internal-name-for-debugging-p 322 :sometimes)
(declare-c-byte-code-funcalled-evaluator assigned-to-module 323 :sometimes)
(declare-c-byte-code-funcalled-evaluator bitwise-not 324 :sometimes)
(declare-c-byte-code-funcalled-evaluator bitwise-xor 325 :sometimes)
(declare-c-byte-code-funcalled-evaluator bitwise-right-shift 326 :sometimes)
(declare-c-byte-code-funcalled-evaluator bitwise-left-shift 327 :sometimes)
(declare-c-byte-code-funcalled-evaluator bitwise-test 328 :sometimes)
(declare-c-byte-code-funcalled-evaluator bitwise-set 329 :sometimes)
(declare-c-byte-code-funcalled-evaluator current-subsecond-time 330 :sometimes)
(declare-c-byte-code-funcalled-evaluator current-subsecond-real-time 331 :sometimes)
(declare-c-byte-code-funcalled-evaluator containing-symbol 332 :sometimes)
(declare-c-byte-code-funcalled-evaluator find-and-replace-pattern-6 333 :sometimes)
(declare-c-byte-code-funcalled-evaluator lexeme 334 :sometimes)
(declare-c-byte-code-funcalled-evaluator character-codes-to-text 335 :sometimes)
(declare-c-byte-code-funcalled-evaluator text-to-character-codes 336 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-uppercase 337 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-titlecase 338 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-lowercase 339 :sometimes)
(declare-c-byte-code-funcalled-evaluator to-uppercase 340 :sometimes)
(declare-c-byte-code-funcalled-evaluator to-titlecase 341 :sometimes)
(declare-c-byte-code-funcalled-evaluator to-lowercase 342 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-digit 343 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-readable-digit 344 :sometimes)
(declare-c-byte-code-funcalled-evaluator is-readable-digit-in-radix 345 :sometimes)
(declare-c-byte-code-funcalled-evaluator readable-text-for-value 346 :sometimes)
(declare-c-byte-code-funcalled-evaluator readable-text 347 :sometimes)
(declare-c-byte-code-funcalled-evaluator readable-symbol-text 348 :sometimes)
(declare-c-byte-code-funcalled-evaluator text-to-symbol 349 :sometimes)
(declare-c-byte-code-funcalled-evaluator compare-text 350 :sometimes)
(declare-c-byte-code-funcalled-evaluator import-text 351 :sometimes)
(declare-c-byte-code-funcalled-evaluator export-text 352 :sometimes)
(declare-c-byte-code-funcalled-evaluator transform-text-for-unicode-comparison 353 :sometimes)
(declare-c-byte-code-funcalled-evaluator transform-text-for-g2-4.0-comparison 354 :sometimes)
(declare-c-byte-code-funcalled-evaluator great-circle-distance 355 :sometimes)
(declare-c-byte-code-funcalled-evaluator format-numeric-text #|121|# 356 :sometimes)
(declare-c-byte-code-funcalled-evaluator rgb-symbol 357 :sometimes)
(declare-c-byte-code-funcalled-evaluator remove 358 :sometimes)
(declare-c-byte-code-funcalled-evaluator insert-at-beginning 359 :sometimes)
(declare-c-byte-code-funcalled-evaluator insert-at-end 360 :sometimes)
(declare-c-byte-code-funcalled-evaluator insert-before 361 :sometimes)
(declare-c-byte-code-funcalled-evaluator insert-after 362 :sometimes)
(declare-c-byte-code-funcalled-evaluator insert-before-element 363 :sometimes)
(declare-c-byte-code-funcalled-evaluator insert-after-element 364 :sometimes)
(declare-c-byte-code-funcalled-evaluator change-element 365 :sometimes)
(declare-c-byte-code-funcalled-evaluator portion 366 :sometimes)
(declare-c-byte-code-funcalled-evaluator change-evaluated-attribute 367 :sometimes)
(declare-c-byte-code-funcalled-evaluator remove-evaluated-attribute 368 :sometimes)
(declare-c-byte-code-funcalled-evaluator items-are-connected 369 :sometimes)
(declare-c-byte-code-funcalled-evaluator items-are-connected-with-direction 370 :sometimes)
(declare-c-byte-code-funcalled-evaluator items-are-connected-at-ports 371 :sometimes)
(declare-c-byte-code-funcalled-evaluator find-java-class 372 :sometimes)
(declare-c-byte-code-funcalled-evaluator network-interface-for 373 :sometimes)
(declare-c-byte-code-funcalled-evaluator in-the-tracked-item-set #|139|# 374 :sometimes)
(declare-c-byte-code-funcalled-evaluator with-unsaved-changes #|140|# 375 :sometimes)
(declare-c-byte-code-funcalled-evaluator current-system-time #|141|# 376 :sometimes)
(declare-c-byte-code-funcalled-evaluator current-system-real-time #|142|# 377 :sometimes)
(declare-c-byte-code-funcalled-evaluator div-long #|143|# 378 :sometimes)
(declare-c-byte-code-funcalled-evaluator kbf-g2nke-count-history-matching-op #|144|# 379 :sometimes)
(declare-c-byte-code-funcalled-evaluator kbf-g2nke-count-history-matching-op-and-eventflag #|145|# 380 :sometimes)
(declare-c-byte-code-funcalled-evaluator vector-add #|146|# 381 :sometimes)
(declare-c-byte-code-funcalled-evaluator vector-multiply #|147|# 382 :sometimes)
(declare-c-byte-code-funcalled-evaluator vector-scalar-multiply #|148|# 383 :sometimes)
(declare-c-byte-code-funcalled-evaluator with-changes-logged-2 384 :sometimes)

(declare-c-byte-code-function copy-evaluation-sequence 385 :never nil nil)
(declare-c-byte-code-function copy-evaluation-structure 386 :never nil nil)
(declare-c-byte-code-function unexpected-stack-top-error 387 :always nil nil)
(declare-c-byte-code-function with-unsaved-changes 388 :sometimes nil nil)
(declare-c-byte-code-function get-parent-attribute-name-as-symbol 389 :never nil nil)
(declare-c-byte-code-function runs-while-reset-procedure-p 390 :never nil nil)

(declare-c-byte-code-funcalled-evaluator is-resized-by-the-user 391 :sometimes)

(declare-c-byte-code-function copy-managed-long 392 :never nil nil)
(declare-c-byte-code-function wide-string-p 393 :never nil nil)
(declare-c-byte-code-function make-evaluation-float 394 :never nil nil)
(declare-c-byte-code-function MAKE-EVALUATION-FLOAT-FROM-EVALUATION-LONG 395 :never nil nil)
(declare-c-byte-code-function MAKE-EVALUATION-LONG 396 :never nil nil)
(declare-c-byte-code-function NANP 397 :never nil nil)
(declare-c-byte-code-function HAS-EMPTY-CODE-BODY-P 398 :never nil nil)
(declare-c-byte-code-function DIV-LONG 399 :never nil nil)
(declare-c-byte-code-function HANDLE-PROCEDURE-TIME-CALL 400 :never nil nil)
(declare-c-byte-code-function CONVERT-G2LONGINT-TO-DOUBLE 401 :never nil nil)
(declare-c-byte-code-function need-to-wait-after-attempting-rule-scheduling 402 :never nil nil)
(declare-c-byte-code-function NUMBER-OF-DATAPOINTS 403 :never nil nil)
(declare-c-byte-code-function GET-VALUE-OF-PREVIOUS-DATAPOINT 404 :never nil nil)
(declare-c-byte-code-function HANDLE-PROCEDURE-TIME-RETURN-VALUES 405 :never nil nil)
(declare-c-byte-code-function TRUNCATE-EVALUATION-QUANTITIES 406 :never nil nil)

(declare-c-byte-code-funcalled-evaluator number-of-arguments-for-procedure 407 :sometimes)

;Use (:never nil nil) for the functions called indirectly from the instruction
; serve-next-iteration-value.  (look for "#'" in roles.lisp)
;    serve-next-evaluation-value serve-next-unreprocessed-frame serve-next-item-or-value
;    serve-next-unreprocessed-cached-frame serve-next-name-of-entity serve-remaining-list-elements
;    serve-remaining-g2-array-elements serve-next-evaluation-sequence-value

)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro c-byte-code-array (alist-symbol &optional (length-alist-symbol alist-symbol))
  (let* ((largest-index (loop for (name value) in (symbol-value length-alist-symbol)
                              maximize value))
         (array (make-array (1+f largest-index))))
    (loop for (name value) in (symbol-value alist-symbol)
          do (setf (svref array value) name))
    `(optimize-constant ',array)))

(defmacro c-byte-code-properties-array (alist-symbol &optional (length-alist-symbol alist-symbol))
  (let* ((largest-index (loop for (name value) in (symbol-value length-alist-symbol)
                              maximize value))
         (array (make-array (1+f largest-index))))
    (loop for (name value properties) in (symbol-value alist-symbol)
          do (setf (svref array value) properties))
    `(optimize-constant ',array)))

(defparameter c-byte-code-constants
  (c-byte-code-array c-byte-code-constant-alist))
(defparameter c-byte-code-variables
  (c-byte-code-array c-byte-code-variable-alist))
(defparameter c-byte-code-foldable-variables
  (c-byte-code-array c-byte-code-foldable-variable-alist c-byte-code-variable-alist))
(defparameter c-byte-code-functions
  (c-byte-code-properties-array c-byte-code-function-alist))

(defparameter-for-macro c-byte-code-function-table
  (loop with table = (make-hash-table)
        for (name value properties) in c-byte-code-function-alist
        do (setf (gethash name table) properties)
        finally (return table)))

)

#+development
(progn
(defun call-function (index &rest args)
  (apply (function-name (svref c-byte-code-functions index)) args))

(defun call-simple-function (index &rest args)
  (apply (function-name (svref c-byte-code-functions index)) args))

(defun call-simple-function-without-decaching (index &rest args)
  (apply (function-name (svref c-byte-code-functions index)) args))

(defun get-variable (index)
  (symbol-value (svref c-byte-code-variables index)))

(defun set-variable (index new-value)
  (setf (symbol-value (svref c-byte-code-variables index)) new-value))

(defsetf get-variable set-variable)
)

(defun-simple get-constant (index)
  (svref c-byte-code-constants index))


;#+development
;(trace call-function call-simple-function get-variable set-variable get-constant)

;c-byte-code-inlined-functions
;c-byte-code-constants
;c-byte-code-local-variables
;c-byte-code-variables
;c-byte-code-functions

(defun-for-macro byte-code-constant-index (constant)
  (position constant c-byte-code-constants :test #'equalw))

(defmacro byte-code-constant-index-macro (constant)
  (byte-code-constant-index constant))

(defun-for-macro byte-code-variable-index (symbol)
  (position symbol c-byte-code-variables))

(defun-for-macro foldable-byte-code-variable-p (index)
  (svref c-byte-code-foldable-variables index))

(defun-for-macro byte-code-function-index (symbol)
  (let ((function-info (gethash symbol c-byte-code-function-table)))
    (when function-info
      (function-index function-info))))

(defun byte-code-function-index-for-phase-2 (symbol)
  (loop for index from 0 below (length c-byte-code-functions)
        for info = (aref c-byte-code-functions index)
        when (and info (eq (function-name info) symbol))
          return index))

(defun-for-macro ab-or-lisp-package-p (pkg)
  (or (eq pkg ab-pkg)
      (eq pkg lisp-pkg)))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar catch-for-let-in-expression-context nil)

(defvar failure-marker '(make-symbol "FAILURE"))
)

;;; When using this form, it is key that a subforms S is evaluated
;;; within this form only if the failure to expand S as an expression
;;; necessarily results in the failure of all superforms of S to be
;;; expanded as expressions. Otherwise, an infinite loop will result.

;;; Uses of this macro should be added to the clauses for
;;; setq, loop, incff, and case in expand-stack-instruction,
;;; as well as the functions
;;;        expand-call-in-stack-instruction
;;;        expand-and-stack-instruction
;;;        expand-or-stack-instruction
;;;        expand-case-stack-instruction  -alatto, 7/9/98

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro maybe-catch-for-expression-context (&body forms)
  `(let ((catch-for-let-in-expression-context
           (if catch-for-let-in-expression-context
               'catch-for-let-in-expression-context-ignore
               'catch-for-let-in-expression-context)))
     (catch catch-for-let-in-expression-context ,@forms)))
)

(defun-for-macro not-an-expression (expressionp)
  (when expressionp
    (if catch-for-let-in-expression-context
        (throw 'catch-for-let-in-expression-context failure-marker)
        #+development
        (cerror "Continue anyway"
                "Impossible to expand in expression context, and no catch ~
                 tag available"))))

(defvar-for-macro functions-expanded-in-expression-context nil)
(defvar-for-macro all-functions-expanded nil)

(defun-for-macro expand-call-in-stack-instruction (form context expressionp env)
  (let ((expansion
          (maybe-catch-for-expression-context
            (let ((index (byte-code-function-index (car form))))
              `(,@(if index
                      `(,(if (and (fixnump context) (<f 1 context))
                             'call-function
                             'call-simple-function)
                         ,index)
                      `(,(car form)))
                  ,@(loop for arg-form in (cdr form)
                          collect (expand-stack-instruction
                                    arg-form
                                    (if (eq (car form) 'not) ':boolean 1)
                                    t
                                    env)))))))
    (if (eq expansion failure-marker)
        (let ((argvars
                (loop for arg in (cdr form) collect (make-symbol "ARG"))))
          (expand-stack-instruction
            `(let ,(loop for argvar in argvars
                         for argval in (cdr form)
                         collect `(,argvar ,argval))
               (,(car form) ,@argvars))
            context expressionp env))
        (progn
          (when (and expressionp (byte-code-function-index (car form)))
            (pushnew (car form) functions-expanded-in-expression-context))
          (when (byte-code-function-index (car form))
            (pushnew (car form) all-functions-expanded))
          (handle-lvalue-context expansion context)))))

(defun-for-macro expand-stack-instruction-list (form-list context expressionp env)
  (loop for tail on form-list
        for form = (car tail)
        for expanded-form = (expand-stack-instruction
                              form
                              (if (cdr tail) ':ignore context)
                              expressionp
                              env)
        for form-list = (if (and (consp expanded-form)
                                 (eq (car expanded-form) 'progn))
                            (cdr expanded-form)
                            (list expanded-form))
        append (if (cdr tail)
                   (remove nil form-list)
                   form-list)))

(defun-for-macro macroexpand-cond-for-expansion (clauses context expressionp env)
  (declare (ignore context env))
  (cond ((null clauses)
         nil)
        ((eq (caar clauses) 't)
         `(progn ,@(cdar clauses)))
        ((and (null (cdar clauses)) (not expressionp))
         (let ((temp (make-symbol "TEMP")))
           `(let ((,temp ,(caar clauses)))
              (if ,temp
                  ,temp
                  (cond ,@(cdr clauses))))))
        (t
         `(,(if expressionp 'ife 'if) ,(caar clauses)
              (progn ,@(cdar clauses))
              (cond ,@(cdr clauses))))))

(defun-for-macro lookup-local-variable (form env)
  (loop for local-var-list in env
        when (loop for s in local-var-list
                   when (eq form (if (consp s) (car s) s))
                     return (if (consp s) (cdr s) s)
                   finally (return nil))
          return it
        finally (return nil)))

(defun-for-macro some-variable-expands-to (form env)
  (loop for local-var-list in env
        when (loop for s in local-var-list
                   when (eq form (if (consp s) (cdr s) s))
                     return t
                   finally (return nil))
          return t
        finally (return nil)))

(defun-for-macro esi-normalize-local-variable (var env)
  (loop with count = 0
        for postfix = "" then (format nil "~D" (incff count))
        for sym = (intern (format nil "~A~A" var postfix))
        while (some-variable-expands-to sym env)
        finally (return sym)))

(defun-for-macro expand-and-stack-instruction (form-list context expressionp env)
  (cond ((null form-list)
         (expand-stack-instruction t context expressionp env))
        ((null (cdr form-list))
         (expand-stack-instruction (car form-list) context expressionp env))
        ((cddr form-list)
         (expand-and-stack-instruction
           `(,(car form-list) (and ,@(cdr form-list)))
           context
           expressionp
           env))
        ((eq context ':boolean)
         `(and ,(expand-stack-instruction (car form-list) context t env)
               ,(expand-stack-instruction (cadr form-list) context t env)))
        (t
         (let ((first-expansion
                 (expand-stack-instruction (car form-list) ':boolean t env)))
           (cond
             ((null first-expansion) nil)
             ((equal first-expansion '(get-constant 33))
              (expand-stack-instruction (cadr form-list) context expressionp env))
             (t
              `(,(if expressionp 'ife 'if)
                 ,first-expansion
                 ,(expand-stack-instruction (cadr form-list) context expressionp env)
                 ,(expand-stack-instruction nil context expressionp env))))))))

(defun-for-macro expand-or-stack-instruction (form-list context expressionp env)
  (cond ((null form-list)
         (expand-stack-instruction nil context expressionp env))
        ((null (cdr form-list))
         (expand-stack-instruction (car form-list) context expressionp env))
        ((cddr form-list)
         (expand-or-stack-instruction
           `(,(car form-list) (or ,@(cdr form-list)))
           context
           expressionp
           env))
        ((eq context ':boolean)
         `(or ,(expand-stack-instruction (car form-list) context expressionp env)
              ,(expand-stack-instruction (cadr form-list) context expressionp env)))
        (t
         (expand-stack-instruction
           `(cond (,(car form-list)) (t ,(cadr form-list)))
           context expressionp env))))

(defun-for-macro expand-case-stack-instruction (key-form clause-list context expressionp env)
  (cond ((null clause-list)
         (expand-stack-instruction nil context expressionp env))
        (t
         (let ((key-or-keys (caar clause-list)))
           (if (memq key-or-keys '(t otherwise))
               (expand-stack-instruction `(progn ,@(cdar clause-list)) context expressionp env)
               `(,(if expressionp 'ife 'if)
                  ,(if (atom key-or-keys)
                       `(eq ,key-form ,(expand-stack-instruction `',key-or-keys 1 t env))
                       (expand-stack-instruction
                         `(or
                           ,@(loop for key in key-or-keys
                                   for form = `(eq ,key-form ,(expand-stack-instruction `',key 1 t env))
                                   collect form))
                         1 t env))

                  ,(expand-stack-instruction `(progn ,@(cdar clause-list)) context expressionp env)
                  ,(expand-case-stack-instruction
                     key-form
                     (cdr clause-list) context expressionp env)))))))

(defmacro lisp-eval (&rest args)
  `(ab-lisp::eval ,@args))

(defun-for-macro expand-stack-instruction-constant (constant context)
  (let ((value (unless (eq context ':ignore)
                 (lisp-eval constant))))
    (if (or (fixnump value) (floatp value) (null value))
        value
        `(get-constant
           ,(or (byte-code-constant-index value)
                (error "~S was not found in c-byte-code-constants" value))))))

(defun-for-macro expand-stack-instruction-variable (variable)
  (let ((index (byte-code-variable-index variable)))
    (unless index
      (error "~S is not a local variable or in c-byte-code-variables" variable))
    (if (foldable-byte-code-variable-p index)
        `(get-foldable-variable ,index ,variable)
        `(get-variable ,index))))

(defun-for-macro handle-lvalue-context (form context)
  (cond ((not (and (consp context) (eq (car context) ':lvalue)))
         form)
        ((and (symbolp form) (eq form (cadr context)))
         nil)
        (t
         `(setf ,(cadr context) ,form))))

(defmacro ife (form1 form2 &optional form3)
  `(if ,form1 ,form2 ,form3))

;;; This is used to inform the constant-folder that the top-of-stack
;;; will be modified by this amount before the next instruction will be
;;; executed, so that it can get the stack-offset right for the next
;;; instruction. Since it sets stack-offset, it should only be used at the
;;; end of an instruction, at a point where stack-offset is otherwise dead,
;;; because subsequent references to top-of-stack in the same instruction
;;; would otherwise use the wrong value of stack-offset, and reference the
;;; wrong stack location.
(defmacro set-values-popped-before-resuming (count)
  `(decff stack-offset ,count))

(defun-for-macro expand-stack-instruction (form context expressionp env)
  (if (atom form)
      (handle-lvalue-context
        (if (and (symbolp form)
                 (not (constantp form)))
            (if (eq form 'top-of-stack)
                (if (eq context :location)
                    'top-of-stack
                    '(+f stack-frame-base stack-offset))
                (let ((emit-var (lookup-local-variable form env)))
                  (or emit-var (expand-stack-instruction-variable form))))
            (expand-stack-instruction-constant form context))
        context)
      (cond
        ((not (symbolp (car form)))
         (error "bad form: car must be symbol ~S" form))
        ((or (equal form '(go exit-stack-eval))
             (equal form '(go exit-stack-eval-inner))
             (equal form '(go label-dispatch))
             (equal form '(go check-timeout)))
         form)
        (t
         (case (car form)
           ((go)
            (error "bad form: go not allowed ~S" form))
           ((modify-major-stack-eval-locals)
            `(go ,(if (second form)
                      'exit-stack-eval-major-t
                      'exit-stack-eval-major-nil)
                 ,@(if (third form)
                       (list (third form))
                       nil)))
           ((modify-minor-stack-eval-locals)
            `(go exit-stack-eval-minor ,@(cdr form)))
           ((if-emitting-c-code)
            (expand-stack-instruction (second form) context expressionp env))
           ((exit-compiled-stack-eval)
            `(go exit-stack-eval-inner))
           ((quote)
            (handle-lvalue-context
              (expand-stack-instruction-constant form context)
              context))
           ((assert-for-development eval-cons-checker progn-for-development
             write-major-trace-of-activity)
            nil)
           ((check-type-for-development)
            (expand-stack-instruction
              (cadr form)
              context
              expressionp
              env))
           ((note-allocate-cons note-reclaim-cons debugging-consing-p)
            nil)
           ((integerp)
            (expand-stack-instruction
              `(fixnump ,@(cdr form))
              context
              expressionp
              env))
           ((reclaim-managed-float reclaim-evaluation-float
             reclaim-managed-long reclaim-evaluation-long)
            (expand-stack-instruction
              `(reclaim-managed-simple-float-array ,@(cdr form))
              context
              expressionp
              env))
           ((raw-stack-error-throw-object)
            (expand-stack-instruction
              `(raw-stack-error-throw-object-function ,@(cdr form))
              context
              expressionp
              env))
           ((inline-type-check-class)
            (expand-stack-instruction
              `(inline-type-check-class-macro ,@(cdr form))
              context
              expressionp
              env))
           ((class-description-subclass-of-class-description-p)
            (expand-stack-instruction
              `(class-description-subclass-of-class-description-p-function ,@(cdr form))
              context
              expressionp
              env))
           ((stack-abort-called-code-bodies-body)
            (expand-stack-instruction
              `(abort-called-code-bodies-function)
              context
              expressionp
              env))
           ((progn)
            (let ((forms (expand-stack-instruction-list (cdr form) context expressionp env)))
              (if (null (cdr forms))
                  (car forms)
                  `(progn ,@forms))))
           ((prog1)
            (error "bad form: prog1 is not supported ~S" form))
           ((or ab-lisp::or)
            (expand-or-stack-instruction (cdr form) context expressionp env))
           ((and ab-lisp::and)
            (expand-and-stack-instruction (cdr form) context expressionp env))
           ;; This assumes that no specials get bound; should be checked at
           ;; compile time -alatto, 8/18/98
           ((let ab-lisp::let)
            (unless (cadr form)
              (return-from expand-stack-instruction
                (expand-stack-instruction `(progn ,@(cddr form)) context expressionp env)))
            (not-an-expression expressionp)
            (let* ((original-bindings
                     (loop for binding in (cadr form)
                           for variable = (if (consp binding) (car binding) binding)
                           for value = (if (consp binding) (cadr binding) nil)
                           unless (eq variable value)
                             collect binding))
                   (new-env (cons nil env))
                   (bindings
                     (maybe-catch-for-expression-context
                       (loop for binding in original-bindings
                             for var = (if (consp binding) (car binding) binding)
                             for init-form = (if (consp binding) (cadr binding) nil)
                             for emit-var = (esi-normalize-local-variable var new-env)
                             do (rplaca new-env
                                        (cons
                                          (if (eq emit-var var) var (cons var emit-var))
                                          (car new-env)))
                             collect `(,emit-var
                                         ,(expand-stack-instruction init-form 1 t env))))))
              (if (eq bindings failure-marker)
                  (let ((new-env (cons nil env)))
                    (loop for binding in original-bindings
                          for var = (if (consp binding) (car binding) binding)
                          for init-form = (if (consp binding) (cadr binding) nil)
                          for emit-var = (esi-normalize-local-variable var new-env)
                          do (rplaca new-env
                                     (cons
                                       (if (eq emit-var var) var (cons var emit-var))
                                       (car new-env)))
                          collect `(,emit-var ,(when (lfsi-constant-p init-form) init-form))
                            into bindings
                          unless (lfsi-constant-p init-form)
                            collect
                            (expand-stack-instruction
                              init-form
                              `(:lvalue
                                 ,(expand-stack-instruction var ':location t new-env))
                              expressionp
                              env)
                              into setqs
                          finally (return `(,(if expressionp 'lete 'let) ,bindings
                                             ,@setqs
                                             ,@(expand-stack-instruction-list
                                                 (cddr form)
                                                 context
                                                 expressionp
                                                 new-env)))))
                  `(,(if expressionp 'lete 'let) ,bindings
                     ,@(expand-stack-instruction-list
                         (cddr form)
                         context
                         expressionp
                         new-env)))))
           ((let* ab-lisp::let*)
            (unless (cadr form)
              (return-from expand-stack-instruction
                (expand-stack-instruction `(progn ,@(cddr form)) context expressionp env)))
            (not-an-expression expressionp)
            (multiple-value-bind (bindings new-env)
                (maybe-catch-for-expression-context
                  (loop for env = env then (cons (list venv) env)
                        for binding in (cadr form)
                        for var = (if (consp binding) (car binding) binding)
                        for init-form = (if (consp binding) (cadr binding) nil)
                        for emit-var = (esi-normalize-local-variable var env)
                        for venv = (if (eq emit-var var) var (cons var emit-var))
                        collect `(,emit-var
                                    ,(expand-stack-instruction init-form 1 t env))
                          into bindings
                        finally (return (values bindings env))))
              (if (eq bindings failure-marker)
                  (loop for env = env then new-env
                        for binding in (cadr form)
                        for var = (if (consp binding) (car binding) binding)
                        for init-form = (if (consp binding) (cadr binding) nil)
                        for emit-var = (esi-normalize-local-variable var env)
                        for venv = (if (eq emit-var var) var (cons var emit-var))
                        for new-env = (cons (list venv) env)
                        collect `(,emit-var ,(when (lfsi-constant-p init-form) init-form))
                          into bindings
                        unless (lfsi-constant-p init-form)
                          collect
                          (expand-stack-instruction
                            init-form
                            `(:lvalue
                               ,(expand-stack-instruction var ':location t new-env))
                            expressionp
                            env)
                            into setqs
                        finally (return
                                  `(,(if expressionp 'let*e 'let*) ,bindings
                                     ,@setqs
                                     ,@(expand-stack-instruction-list
                                         (cddr form)
                                         context
                                         expressionp
                                         new-env))))
                  `(,(if expressionp 'let*e 'let*) ,bindings
                     ,@(expand-stack-instruction-list
                         (cddr form)
                         context
                         expressionp
                         new-env)))))
           ((setq setf)
            (when (and (consp context) (eq (car context) ':lvalue))
              (error "setf problem"))
            (cond
              ((and (eq (car form) 'setf)
                    (consp (cadr form))
                    ;; what we really want here is
                    ;; "...and the setf method for (caadr form) was
                    ;; defined by an explicit defsetf" but there's no easy
                    ;; way to say this, so we'll just special-case them
                    ;; by hand.
                    (or (special-setf-method (caadr form))
                        (eq (caadr form) 'managed-svref)))
               (expand-stack-instruction
                 (macroexpand-1 form)
                 context
                 expressionp
                 env))
              (t
               (let ((forms (loop for (lform form) on (cdr form) by 'cddr
                                  for expanded-lform
                                      = (expand-stack-instruction lform ':location t env)
                                  for expanded-lform-1
                                      = (if (and (consp expanded-lform)
                                                 (memq (car expanded-lform) '(car cdr)))
                                            `(,(case (car expanded-lform)
                                                 (car 'car-of-cons)
                                                 (cdr 'cdr-of-cons))
                                               ,@(cdr expanded-lform))
                                            expanded-lform)
                                  collect
                                  (expand-stack-instruction
                                    form
                                    `(:lvalue ,expanded-lform-1)
                                    nil
                                    env))))
                 (cond ((null forms)
                        nil)
                       ((null (cdr forms))
                        (car forms))
                       (t
                        `(progn ,@forms)))))))
           ((if ab-lisp::if ife)
            (cond
              ((equal (cadr form) '(get-constant 33))
               (expand-stack-instruction (caddr form) context expressionp env))
              ((null (cadr form))
               (expand-stack-instruction (cadddr form) context expressionp env))
              (t
               (let ((test-expansion
                       (maybe-catch-for-expression-context
                         (expand-stack-instruction (cadr form) ':boolean t env))))
                 (if (eq test-expansion failure-marker)
                     (let ((test (make-symbol "TEST")))
                       (expand-stack-instruction
                         `(let ((,test ,(cadr form)))
                            (,(if expressionp 'ife 'if) ,test ,@(cddr form)))
                         context expressionp env))
                     `(,(if expressionp 'ife 'if)
                        ,test-expansion
                        ,(expand-stack-instruction (caddr form) context expressionp env)
                        ,(expand-stack-instruction (cadddr form) context expressionp env)))))))
           ((when)
            (expand-stack-instruction
              `(if ,(cadr form) (progn ,@(cddr form)) nil)
              context expressionp env))
           ((unless)
            (expand-stack-instruction
              `(if (not ,(cadr form)) (progn ,@(cddr form)) nil)
              context expressionp env))
           ((cond)
            (expand-stack-instruction
              (macroexpand-cond-for-expansion (cdr form) context expressionp env) context expressionp env))
           ((loop)
            (when expressionp (error "loop in expression context"))
            (cond ((and (or (eq (second form) 'while)
                            (eq (second form) 'until))
                        (eq (fourth form) 'do)
                        (every #'consp (nthcdr 4 form)))
                   `(loop while ,(expand-stack-instruction
                                   (if (eq (second form) 'until)
                                       `(not ,(third form))
                                       (third form))
                                   ':boolean t env)
                          do ,(expand-stack-instruction
                                `(progn ,@(nthcdr 4 form))
                                ':ignore
                                expressionp
                                env)))
                  ;; expand FOR loop into WHILE loop to support some evaluators
                  ((and (eq (second form) 'for)
                        (eq (fourth form) 'from)
                        (eq (sixth form) 'to)
                        (eq (eighth form) 'do)
                        (every #'consp (nthcdr 8 form)))
                   (let ((loop-var (third form))
                         (end-value (make-symbol "END-VALUE"))
                         (new-env (cons nil env)))
                     (maybe-catch-for-expression-context
                       (loop for var in (list loop-var end-value)
                             for emit-var = (esi-normalize-local-variable var new-env)
                             do (rplaca new-env
                                        (cons
                                          (if (eq emit-var var) var (cons var emit-var))
                                          (car new-env)))))
                     `(let ((,loop-var ,(fifth form))
                            (,end-value ,(seventh form)))
                        (loop while ,(expand-stack-instruction
                                       `(<f ,loop-var ,end-value)
                                       ':boolean t new-env)
                              do ,(expand-stack-instruction
                                    `(progn ,@(nthcdr 8 form) (incff ,loop-var))
                                    ':ignore
                                    expressionp
                                    new-env)))))
                  (t
                   (error "bad form: only a very small subset of loop is supported ~S" form))))
           (the
            (expand-stack-instruction (caddr form) context expressionp env))
           ((incff decff)
            (if (eq (cadr form) 'top-of-stack)
                (expand-stack-instruction
                  `(,(car form) stack-offset ,@(cddr form))
                  context expressionp env)
                (handle-lvalue-context
                  `(,(first form) ,(expand-stack-instruction (second form) ':location t env)
                     ,(expand-stack-instruction (or (third form) 1) 1 t env))
                  context)))
           ((macrolet)
            (error "bad form: macrolet is not supported ~S" form))
           ((potentially-rigorous-operation)
            (expand-stack-instruction (cadr form) context expressionp env))
           ((role-server-case)
            (expand-stack-instruction `(inlined-role-server-case ,@(cdr form)) context expressionp env))
           ((fixnum-case)
            (when expressionp (error "fixnum-case in expression context"))
            `(,(car form) ,(expand-stack-instruction (cadr form) 1 t env)
               ,@(loop for clause in (cddr form)
                       collect `(,(car clause)
                                  ,@(expand-stack-instruction-list (cdr clause) context nil env)))))
           ((case)
            (let ((key (expand-stack-instruction (cadr form) 1 expressionp env)))
              (if (or (atom key)
                      (eq (car key) 'get-constant))
                  (expand-case-stack-instruction key (cddr form) context expressionp env)
                  (let ((key-var (make-symbol "KEY")))
                    (expand-stack-instruction `(let ((,key-var ,(cadr form)))
                                                 (case ,key-var ,@(cddr form)))
                                              context expressionp env)))))
           ((multiple-value-setq)
            (when expressionp (error "multiple-value-setq in expression context"))
            `(multiple-value-setq ,(second form)
               ,(expand-stack-instruction (third form) (length (second form)) nil env)))
           ((multiple-value-bind)
            (error "bad form: multiple-value-bind is not supported ~S" form))
           ((compiled-case-dispatch)
            (handle-lvalue-context
              `(compiled-case-dispatch
                 ,(expand-stack-instruction (second form) 1 t env)
                 ,(expand-stack-instruction (third form) 1 expressionp env)
                 ,(expand-stack-instruction (fourth form) 1 expressionp env))
              context))
           (t
            (let ((data (inlined-function-data (car form))))
              (cond
                (data
                 (if (null (inlined-function-data-given-arg-count (car form) (1-f (length form))))
                     (error "bad form: arity mismatch for ~S.  ~S" (car form) form)
                     (expand-call-in-stack-instruction form context expressionp env)))
                ((byte-code-function-index (car form))
                 (expand-call-in-stack-instruction form context expressionp env))
                ((eq (car form) 'declare)
                 nil)
                ((and (eq lisp-pkg (symbol-package (car form)))
                      (not (memq (car form) c-byte-code-lisp-macros)))
                 (error "bad form: ~S is not a c-byte-code-lisp-macro. ~
                         Perhaps you should use assert-for-development, progn-for-development, ~
                         or check-type-for-development.  ~
                         The whole form was: ~S" (car form) form))
                (t
                 (multiple-value-bind (new-form exp-p)
                     (let ((macroexpanding-for-instruction-expander t))
                       (macroexpand-1 form))
                   (cond ((not exp-p)
                          (warn "~S was not found in c-byte-code-functions" (car form))
                          (expand-call-in-stack-instruction form context expressionp env))
                         ((and (consp new-form)
                               (not (ab-or-lisp-package-p (symbol-package (car new-form)))))
                          (error "bad form from macroexpansion: ~S" form))
                         (t
                          (expand-stack-instruction new-form context expressionp env)))))))))))))

(defmacro stack-instruction-prologue ()
  `(incff stack-program-counter))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter expand-instruction-toplevel-environment
  (list c-byte-code-local-variables c-byte-code-local-arguments))
)

(defvar expanded-bindings-forms)
(defvar expanded-exit-form)
(defvar expanded-return-values-form)
(defvar expanded-exit-stack-eval-major-form)
(defvar expanded-exit-stack-eval-minor-form)
(defvar expanded-check-timeout-form)
(defvar expanded-default-clause-form)

(defmacro generate-expanded-instruction-macros (optimize-p)
  (setq functions-expanded-in-expression-context nil)
  `(progn
     (setq expanded-bindings-forms
           (,(if optimize-p 'optimize-constant 'progn)
             ',(loop for (var form) in stack-eval-locals-bindings
                     collect
                     (list
                       'setf
                       (if (eq var 'instruction-count)
                           'instruction-count-plus-pc
                           var)
                       (expand-stack-instruction
                         (case var
                           (instruction-count
                            `(+f ,form initial-program-counter))
                           (stack-frame-base
                            `initial-stack-frame-base)
                           (t form))
                         1
                         t
                         expand-instruction-toplevel-environment)))))
     (setq expanded-exit-form
           (,(if optimize-p 'optimize-constant 'progn)
             ',(expand-stack-instruction
                 `(cond ((code-body-invocation-p current-computation-instance)
                         (exit-computation-context-for-code-body-invocation
                           current-computation-instance stack-program-counter nil))
                        ((rule-instance-p current-computation-instance)
                         (setf (invocation-stack-program-counter
                                 current-computation-instance)
                               stack-program-counter)))
                 ':ignore
                 nil
                 expand-instruction-toplevel-environment)))
     (setq expanded-return-values-form
           (,(if optimize-p 'optimize-constant 'progn)
             ',(expand-stack-instruction
                 `(progn
                    (setf c-byte-code-body-result-1 byte-code-body)
                    (setf c-byte-code-body-result-2 constant-vector)
                    (setf c-byte-code-body-result-3 local-var-vector)
                    (setf c-byte-code-body-result-4 fixnum-time-limit?)
                    (setf c-byte-code-body-result-5 stack-program-counter)
                    (setf c-byte-code-body-result-6 stack-frame-base)
                    (setf c-byte-code-body-result-7 recursion-depth)
                    nil)
                 ':ignore
                 nil
                 expand-instruction-toplevel-environment)))
     (setq expanded-exit-stack-eval-major-form
           (,(if optimize-p 'optimize-constant 'progn)
             ',(expand-stack-instruction
                 (let ((macroexpanding-for-instruction-expander t))
                   (macroexpand-1 `(modify-major-stack-eval-locals (/=f 0 fixnum-register-1))))
                 ':ignore
                 nil
                 expand-instruction-toplevel-environment)))
     (setq expanded-exit-stack-eval-minor-form
           (,(if optimize-p 'optimize-constant 'progn)
             ',(expand-stack-instruction
                 (let ((macroexpanding-for-instruction-expander t))
                   (macroexpand-1 `(modify-minor-stack-eval-locals)))
                 ':ignore
                 nil
                 expand-instruction-toplevel-environment)))
     (setq expanded-check-timeout-form
           (,(if optimize-p 'optimize-constant 'progn)
             ',(expand-stack-instruction
                 `(when fixnum-time-limit?
                    (let* ((current-fixnum-time (get-fixnum-time))
                           (time-elapsed
                             (fixnum-time-difference
                               current-fixnum-time cached-fixnum-start-time)))
                        (declare (type fixnum current-fixnum-time time-elapsed))
                        (unless (>=f time-elapsed fixnum-time-limit?)
                          (progn
                            (setf instruction-count-plus-pc
                                  (+f instruction-count-plus-pc 500))
                            (go label-dispatch)))))
                 ':ignore
                 nil
                 expand-instruction-toplevel-environment)))
     (setq expanded-default-clause-form
           (,(if optimize-p 'optimize-constant 'progn)
             '(t ,(expand-stack-instruction
                   '(progn (unknown-entry-point-error)
                      (go exit-stack-eval))
                   :ignore nil
                   expand-instruction-toplevel-environment))))
     ,@(loop for op-code from 0 below 256
             for description? = (svref stack-instructions op-code)
             for instruction
                 = (when (and description?
                              (not (instruction-should-not-be-compiled op-code)))
                     `(progn
                        (stack-instruction-prologue)
                        (,(stack-instruction-macro-name description?))))
             when instruction
               collect `(setf (stack-instruction-expanded-body
                                (svref stack-instructions ,op-code))
                              (,(if optimize-p 'optimize-constant 'progn)
                                ',(expand-stack-instruction
                                    instruction
                                    ':ignore
                                    nil
                                    expand-instruction-toplevel-environment))))
     ,@(loop for normalized-in-line-index
             from 0 below maximum-number-of-in-line-evaluators
             for description? = (svref in-line-evaluator-array normalized-in-line-index)
             for op-code = (when description? (evaluator-number description?))
             for instruction
              = (when (and op-code (not (instruction-should-not-be-compiled op-code)))
                  (let ((values-to-pop
                          (-f (length (evaluator-arguments description?)) 1))
                        (macro-name (evaluator-function-or-macro-name
                                      description?))
                        (value-left-in-register-1?
                          (evaluator-result-in-register-1? description?)))
                    (if (and (=f values-to-pop 0)
                             (null value-left-in-register-1?))
                        `(progn
                           (stack-instruction-prologue)
                           (setf (svref local-stack top-of-stack)
                                 (,macro-name)))
                        `(progn
                           (stack-instruction-prologue)
                           ,(if value-left-in-register-1?
                                `(,macro-name)
                                `(setq register-1 (,macro-name)))
                           ,@(case values-to-pop
                               ((-1) `((incff top-of-stack)))
                               ((0)  `())
                               ((1)  `((decff top-of-stack)))
                               (t `((decff top-of-stack ,values-to-pop))))
                           (setf (svref local-stack top-of-stack) register-1)))))
             when instruction
               collect `(setf (evaluator-expanded-body
                                (svref in-line-evaluator-array ,normalized-in-line-index))
                              (,(if optimize-p 'optimize-constant 'progn)
                                ',(expand-stack-instruction
                                    instruction
                                    ':ignore
                                    nil
                                    expand-instruction-toplevel-environment))))
     nil))


#-translating
(progn
(defun value<-type (v)
  (typecase v
    (keyword 1)
    (symbol (if (find-symbol (symbol-name v))
                3 2))
    (string 4)
    (t 5)))

(defun value< (v1 v2)
  (let ((e1 (value<-type v1))
        (e2 (value<-type v2)))
    (or (< e1 e2)
        (and (= e1 e2)
             (case e1
               ((1 2 3 4) (string< v1 v2)))))))

(defun show-use-list (name value)
  (format t "~&(defparameter ~s~%  '(" name)
  (when value
    (let ((value (sort (copy-list value) #'value<)))
      (format t "~s" (car value))
      (loop for v in (cdr value)
            do (format t "~%    ~s" v))))
  (format t "))~%~%"))

(defun-simple make-identification-string (form)
  (let* ((*print-case* :downcase)
         (identification (cadr form))
         (reference
           (if (consp identification)
               (cadr identification)
               nil))
         (stack-instruction-p
           (and reference (eq (cadr reference) 'stack-instructions)))
         (in-line-evaluator-p
           (and reference (eq (cadr reference) 'in-line-evaluator-array))))
    (cond
      (stack-instruction-p
       (format nil "~%~%;; Instruction #~s: ~s"
               (caddr reference)
               (stack-instruction-name (lisp-eval reference))))
      (in-line-evaluator-p
       (format nil "~%~%;; In-line evaluator #~s: ~s (~s)"
               (caddr reference)
               (evaluator-name (lisp-eval reference))
               (instruction-name (lisp-eval reference))))
      (reference
       (format nil "~%~%;; ~s" (cdr reference)))
      (t
       (format nil "~%~%;; ~s" identification)))))

(defun show-expanded-instruction-macros ()
  (loop for form in (cdr (macroexpand-1 '(generate-expanded-instruction-macros nil)))
        do
    (format *standard-output* "~A" (make-identification-string form))
    (pprint (cadr (cadr (caddr form)))))
  (terpri) (terpri))

(defun write-expanded-instruction-macros ()
  (with-open-file (*standard-output*
                    #+development "expanded-instructions-development.lisp"
                    #-development "expanded-instructions-delivery.lisp"
                    :direction :output)
    (let ((*print-case* :downcase)
          (*print-length* nil)
          (*print-level* nil)
          (*features* #+development *features*
                      #-development (append '(:translating :vanilla-numbers :translator
                                              :chestnut-trans :no-macros :do-not-load-bootstrap)
                                            *features*)))
      (show-expanded-instruction-macros))))

)


;;;; LFSI - Lisp for Stack Instruction

(defvar lfsi-unbound-marker '(unbound))
(defvar lfsi-bound-marker '(bound))

(defmacro lfsi-push (thing place) `(phrase-push ,thing ,place))

(defmacro lfsi-cons (a b) `(phrase-cons ,a ,b))

(defun-simple lfsi-copy-tree (x)
  (cond ((atom x) x)
        ((eq x lfsi-unbound-marker)
         x)
        (t
         (lfsi-cons (lfsi-copy-tree (car-of-cons x))
                    (lfsi-copy-tree (cdr-of-cons x))))))

(defmacro lfsi-list (&body args) `(phrase-list ,@args))

(defmacro expand-stack-instruction-variable-macro (name)
  `',(expand-stack-instruction-variable name))

(defvar cached-stack-program-counter-form
  (expand-stack-instruction-variable-macro cached-stack-program-counter))

(defvar cached-top-of-stack-form
  (expand-stack-instruction-variable-macro cached-top-of-stack))

(defun unknown-entry-point-error ()
  #+development
  (cerror "Give up permanently on compiled code"
          "Entry into compiled code at unexpected point")
  (setq enable-running-compiled-code-p nil)
  (if-emitting-c-code (modify-minor-stack-eval-locals) nil))



;;; For dispatch-case

(defvar cached-long-code-constant-form
  `(setf stack-program-counter
         (+f (left-shiftf (byte-vector-aref
                     instruction-vector
                     (+f stack-program-counter (*f 2 index-marker)))
                   8)
             (byte-vector-aref
               instruction-vector
               (+f stack-program-counter (+f (*f 2 index-marker) 1))))))

(defun lfsi-subst (new old form)
  (cond ((eq old form) new)
        ((consp form) (lfsi-cons (lfsi-subst new old (car form))
                                 (lfsi-subst new old (cdr form))))
        (t form)))


(defun make-long-code-constant-stack-program-counter-assignment-form (index)
  (lfsi-subst index 'index-marker cached-long-code-constant-form))

;; (c-set-include-directory (format nil "~A/rtl/c" source-directory-name))

(def-side-effect-free-inlined-pseudo-function inline-get-run-time-function ((index :fixnum-long))
  index)

(def-side-effect-free-inlined-pseudo-function (inline-get-run-time-function-array-size :fixnum-long) ()
  0)

(def-side-effect-free-inlined-pseudo-function inline-symbol-value-location (symbol)
  symbol)

(def-side-effect-free-inlined-pseudo-function inline-symbol-function-location (symbol)
  symbol)

(defun-simple make-compiled-kb-initialization-array ()
  (let ((array (make-array 6)))
    (setf (svref array 0)
          (inline-extract-c-array (make-array #.(length c-byte-code-constants)) 0))
    (setf (svref array 1)
          (inline-extract-c-array (make-array #.(length c-byte-code-variables)) 0))
    (setf (svref array 2)
          (inline-extract-c-array (make-array #.(length c-byte-code-functions)) 0))
    (setf (svref array 3)
          (inline-extract-c-array (make-array (inline-get-run-time-function-array-size)) 0))
    (setf (svref array 4)
          (inline-symbol-function-location 'check-compiled-code-version))
    (setf (svref array 5)
          (inline-symbol-function-location 'add-new-compiled-byte-code-body))
    array))

(defparameter compiled-kb-initialization-array
  (make-compiled-kb-initialization-array))

(defvar compiled-kb-initialization-array-initialized-p nil)

(defun-simple compiled-kb-initialization-argument ()
  (unless compiled-kb-initialization-array-initialized-p
    (loop with array = (inline-get-array-from-c
                         (svref compiled-kb-initialization-array 0) 0)
          for i from 0 below #.(length c-byte-code-constants)
          do (setf (svref array i)
                   (svref c-byte-code-constants i)))
    (loop with array = (inline-get-array-from-c
                         (svref compiled-kb-initialization-array 1) 0)
          for i from 0 below #.(length c-byte-code-variables)
          for variable = (svref c-byte-code-variables i)
          do (setf (svref array i)
                   (when variable
                     (inline-symbol-value-location variable))))
    (loop with array = (inline-get-array-from-c
                         (svref compiled-kb-initialization-array 2) 0)
          for i from 0 below #.(length c-byte-code-functions)
          for function = (svref c-byte-code-functions i)
          for function-name = (when function (function-name function))
          do (setf (svref array i)
                   (when function-name
                     (inline-symbol-function-location function-name))))
    (loop with array = (inline-get-array-from-c
                         (svref compiled-kb-initialization-array 3) 0)
          for i from 0 below (inline-get-run-time-function-array-size)
          do (setf (svref array i)
                   (inline-get-run-time-function i))))
  (inline-extract-c-array compiled-kb-initialization-array 0))

#+development
(defun compile-byte-code-body (byte-code-body constant-vector entry-points)
  (with-phrase-conses
    (multiple-value-bind (lambda-form new-constant-vector)
        (lisp-for-byte-code-body byte-code-body constant-vector entry-points)
      (unless (eq constant-vector new-constant-vector)
        (setf (byte-code-body-constant-vector byte-code-body)
              new-constant-vector))
      (install-compiled-byte-code-body
        byte-code-body
        (ab-lisp::compile nil lambda-form)))))

(defun-void install-compiled-byte-code-body (byte-code-body compiled-function)
  (setf (byte-cody-body-compiled-function byte-code-body) compiled-function)
  ;; maybe update the constant-vector (load time)
  byte-code-body)

(defvar use-interpreter-debug-format nil)

(defun-simple debug-print-byte-code-pc-and-tos (pc top-of-stack)
  (when debug-print-byte-code-pc-p
    (format t "~&pc=~D, top-of-stack=~D~%" pc top-of-stack)))

(defun-simple debug-print-byte-code-pc-stack-base-and-offset (pc stack-frame-base stack-offset)
  (when debug-print-byte-code-pc-p
    (if use-interpreter-debug-format
        (debug-interpreter-print pc (+f stack-frame-base stack-offset) global-stack)
        (format t "~&pc=~D, base=~D, offset=~D~%" pc stack-frame-base stack-offset))))

(defvar lfsi-label-index-space nil)

(defun-simple lfsi-label (index)
  (unless lfsi-label-index-space
    (setq lfsi-label-index-space (make-index-space 'lfsi-label-index-space nil)))
  (or (get-object-from-index-space-if-any lfsi-label-index-space index)
      (setf (get-object-from-index-space lfsi-label-index-space index)
            (intern-text-string (tformat-text-string "L~D" index)))))

(defvar max-var-index nil)

(defvar lfsi-local-var-index-space nil)

(defun-simple local-var (index)
  (setf max-var-index (maxf max-var-index index))
  (unless lfsi-local-var-index-space
    (setq lfsi-local-var-index-space (make-index-space 'lfsi-local-var-index-space nil)))
  (or (get-object-from-index-space-if-any lfsi-local-var-index-space index)
      (setf (get-object-from-index-space lfsi-local-var-index-space index)
            (intern-text-string (tformat-text-string "LOCAL-VAR~D" index)))))

(defun local-var-expression (index-expression)
  (lfsi-list 'svref 'local-var-vector index-expression))

(defvar var-vector-decaching-backpatch-locations)
(defvar var-vector-caching-backpatch-locations)

(defvar cache-stack-and-locals t)

;;; If we don't know the number of vars yet, backpatch it later.
(defun decache-local-vars-form (&optional number-of-vars)
  (if number-of-vars
      (lfsi-list
        'if
        'locals-already-decached
        nil
        (lfsi-cons
          'progn
          (loop for i from 0 to number-of-vars
                collect (lfsi-list 'setf (local-var-expression i) (local-var i))
                  using lfsi-cons)))
      (let ((placeholder (lfsi-list 'insert-var-decaching-forms-here)))
        (lfsi-push placeholder var-vector-decaching-backpatch-locations)
        placeholder)))

(defun cache-local-vars-form (&optional number-of-vars)
  (if number-of-vars
      (lfsi-cons
        'progn
        (loop for i from 0 to number-of-vars
              collect (lfsi-list 'setf (local-var i) (local-var-expression i))
                using lfsi-cons))
      (let ((placeholder (lfsi-list 'insert-var-caching-forms-here)))
        (lfsi-push placeholder var-vector-caching-backpatch-locations)
        placeholder)))

(defvar max-stack-index nil)

(defvar lfsi-stack-var-index-space nil)

(defun-simple stack-var (index)
  (setf max-stack-index (maxf max-stack-index index))
  (unless lfsi-stack-var-index-space
    (setq lfsi-stack-var-index-space (make-index-space 'lfsi-stack-var-index-space nil)))
  (or (get-object-from-index-space-if-any lfsi-stack-var-index-space index)
      (setf (get-object-from-index-space lfsi-stack-var-index-space index)
            (intern-text-string (tformat-text-string "STACK-~D" index)))))

(defun stack-var-expression (index)
  (lfsi-list 'svref 'local-stack (lfsi-list '+f 'stack-frame-base index)))

(defun cache-stack-var-form (index)
  (lfsi-list 'setf (stack-var index) (stack-var-expression index)))

(defun decache-stack-var-form (index)
  (lfsi-list 'setf (stack-var-expression index) (stack-var index)))

(defun cache-stack-vars-form (number-of-stack-vars)
  (lfsi-cons 'progn
             (loop for i from 0 to number-of-stack-vars
                   collect (lfsi-list 'setf (stack-var i) (stack-var-expression i))
                     using lfsi-cons)))

(defun decache-stack-vars-form (number-of-stack-vars)
  (lfsi-cons
    'progn
    (loop for i from 0 to number-of-stack-vars
          collect (lfsi-list 'setf (stack-var-expression i) (stack-var i))
            using lfsi-cons)))

;;; This only accepts a single key in each clause, since its only current use
;;; uses only that case. It does allow a t or otherwise clause.
(defmacro fixnum-case-with-fallthrough (key-expression &rest clauses)
  (let ((key-var (gensym))
        (falling-through (gensym)))
    `(let ((,key-var ,key-expression)
           (,falling-through nil))
       ,@(loop for clause in clauses
               collect
               (if (or (eq (car clause) t)
                       (eq (car clause) 'otherwise))
                   `(progn ,@(cdr clause))
                   `(when (or ,falling-through (eql ,key-var ,(car clause)))
                      (setq ,falling-through t)
                      ,@(cdr clause)))))))

;;;
(defun decache-entire-stack-form (stack-max destination-label)
  (nconc
    (lfsi-list
      'fixnum-case-with-fallthrough
      (lfsi-list
        '-f 'top-of-stack 'stack-frame-base))
    (loop for i from stack-max downto 0
      collect
          (lfsi-list
            i
            (decache-stack-var-form i))
        using lfsi-cons)
    (lfsi-list
      (lfsi-list
        -1
        (lfsi-list 'go destination-label))
      (lfsi-list
        t
        (lfsi-list
          'call-simple-function 387 'top-of-stack 'stack-frame-base)))))

(defun cache-entire-stack-form (stack-max destination-label)
  (nconc
    (lfsi-list
      'fixnum-case-with-fallthrough
      (lfsi-list
        '-f 'top-of-stack 'stack-frame-base))
    (loop for i from stack-max downto 0
      collect
          (lfsi-list
            i
            (cache-stack-var-form i))
        using lfsi-cons)
    (lfsi-list
      (lfsi-list
        -1
        (lfsi-list 'go destination-label))
      (lfsi-list
        t
        (lfsi-list
          'call-simple-function 387 'top-of-stack 'stack-frame-base)))))

(defun unexpected-stack-top-error (top-of-stack stack-frame-base)
  (stack-error top-of-stack
               "stack-frame-base was ~D, top of stack was ~D, an unexpected value"
               stack-frame-base top-of-stack))

(defvar initial-stack-offsets)
(defvar unused-known-offsets)
(defvar possible-label-dispatch-destination)
(defvar explicit-branch-destination)
(defvar all-branch-destinations-possible)

#+development
(defvar do-consistency-checks nil)
#+development
(defun check-consistency (unused-known-offsets form-array initial-stack-offsets
                                               byte-code-body bytes index)
  (format t "~%~D" index)
  (let ((unused-offsets 0))
    (loop with index fixnum = 0
          with length
          while (<f index bytes)
          do
      (setq length
            (length-of-stack-instruction index byte-code-body :unused-constant-vector))
      (when (and (null (managed-svref form-array index))
               (managed-svref initial-stack-offsets index))
        (incff unused-offsets))
      (incff index length))
    (if (eql unused-offsets unused-known-offsets)
        (format t ":  OK")
        (progn (format t ":   Inconsistency detected!~% unused-known-offsets is ~D: should be ~D at index ~D~%" unused-known-offsets unused-offsets index)
               (break)))))

(defvar remove-unused-labels t)
(defvar inline-timeout-checks t)

(defvar do-backpatching t)

(defmacro with-backpatched-var-vector-decaching (&body body)
  `(let* ((max-var-index -1)
          (var-vector-decaching-backpatch-locations nil)
          (var-vector-caching-backpatch-locations nil))
     (multiple-value-prog1
         (progn ,@body)
       (when do-backpatching
         (backpatch-var-vector-decaches)))))

(defun ensure-backpatching (form)
  (cond
    ((atom form) nil)
    ((eq (car form) 'insert-var-decaching-forms-here)
     (if cache-stack-and-locals
         (lfsi-push form var-vector-decaching-backpatch-locations)
         (rplaca form 'progn)))
    ((eq (car form) 'insert-var-caching-forms-here)
     (if cache-stack-and-locals
         (lfsi-push form var-vector-caching-backpatch-locations)
         (rplaca form 'progn)))
    ((eq (car form) 'decache-local-var-vector)
     (if cache-stack-and-locals
         (progn
           (rplaca form 'insert-var-decaching-forms-here)
           (lfsi-push form var-vector-decaching-backpatch-locations))
         (rplaca form 'progn)))
    ((eq (car form) 'cache-local-var-vector)
     (if cache-stack-and-locals
         (progn
           (rplaca form 'insert-var-caching-forms-here)
           (lfsi-push form var-vector-caching-backpatch-locations))
         (rplaca form 'progn)))
    (t
     (ensure-backpatching (car form))
     (ensure-backpatching (cdr form))))
  form)

(defun backpatch-var-vector-decaches ()
  (loop for location in var-vector-decaching-backpatch-locations
        do
    (let ((form (decache-local-vars-form max-var-index)))
      (rplaca location (car form))
      (rplacd location (cdr form))))
  (loop for location in var-vector-caching-backpatch-locations
        do
    (let ((form (cache-local-vars-form max-var-index)))
      (rplaca location (car form))
      (rplacd location (cdr form)))))

;returns two values: a lambda form, and a new constant-vector, which should
;  include the original constant vector as a prefix.
(defun lisp-for-byte-code-body (byte-code-body constant-vector entry-points)
  (ensure-expanded-instruction-macros)
  (let* ((max-stack-index -1)
         (bytes (byte-code-body-length byte-code-body))
         (form-array (allocate-managed-array bytes))
         (initial-stack-offsets (allocate-managed-array bytes))
         ;; Obsolete comment: delete if there's no 1+f in either of
         ;; the two following instructions.
         ;; The extra location is a kludge, so that lfsi-form-1 can record
         ;; a possible branch on return after execution of the final
         ;; instruction. The Right Thing is to be smart about branches to
         ;; the end, distinguishing those that might resume with the next
         ;; instruction later (like function calls, or allow-other-processing)
         ;; from those that will never resume (like timeouts, or the final
         ;; instruction) -alatto, 9/29/98
         (possible-label-dispatch-destination (allocate-managed-array bytes))
         (explicit-branch-destination (allocate-managed-array bytes))
         (all-branch-destinations-possible nil)
         (unused-known-offsets 1)
         (compiled-code nil))
    (with-backpatched-var-vector-decaching

    (setf (managed-svref possible-label-dispatch-destination 0) t)
    (setf (managed-svref initial-stack-offsets 0) -1)
    (when entry-points
      (loop for i from 0 below (managed-array-length entry-points)
            do
        (let ((entry-point (managed-svref entry-points i)))
          (setf (managed-svref possible-label-dispatch-destination entry-point) t)
          (setf (managed-svref initial-stack-offsets entry-point) -1)))
      (incff unused-known-offsets (managed-array-length entry-points)))
    (loop with first-unexpanded-opcode = 0
          while first-unexpanded-opcode do
      (loop with index fixnum = first-unexpanded-opcode
            with form with length
            while (<f index bytes)
            do
        #+development
        (when do-consistency-checks (check-consistency unused-known-offsets
                                                       form-array
                                                       initial-stack-offsets
                                                       byte-code-body
                                                       bytes
                                                       index))
        (setq length
              (length-of-stack-instruction index byte-code-body constant-vector))
        (when (null (managed-svref form-array index))
          (when (and (zerop unused-known-offsets)
                     (null (managed-svref initial-stack-offsets index)))
            ;; ## the locations that appear to be unreachable may actually  be reachable
            ;; ## through the function handle-error-in-code-body-invocation or a jump instruction,
            ;; ## which could be in a in a sibling code body.  See on-error-statement-new.
            #+development
            (cerror "Set an offset to -1 and continue"
                    "unknown stack offset at instruction ~D" index)
            (setf (managed-svref initial-stack-offsets index) -1)
            (incff unused-known-offsets))
          (if (managed-svref initial-stack-offsets index)
              (progn
                (decff unused-known-offsets)
                (setf form
                      (lisp-for-stack-instruction
                        index byte-code-body constant-vector length))
                (setf (managed-svref form-array index)
                      (lfsi-cons
                        'progn
                        (lfsi-cons
                          (lfsi-list
                            'debug-print-byte-code-pc-stack-base-and-offset index
                            'stack-frame-base (managed-svref initial-stack-offsets index))
                          (if (and (consp form) (eq (car form) 'progn))
                              (cdr form)
                              (lfsi-list form)))))
                (when (eql first-unexpanded-opcode index)
                  (setf first-unexpanded-opcode nil)))
              (if (or (null first-unexpanded-opcode)
                      (>f first-unexpanded-opcode index))
                  (setf first-unexpanded-opcode index))))
        (incff index length)))
    ;; Now we've translated everything, so stitch it together in order
    (multiple-value-bind (label-clause-list form-list)
        (loop with index fixnum = 0
              with length
              while (<f index bytes)
              for label = (lfsi-label index)
              for form = (managed-svref form-array index)
              when (or all-branch-destinations-possible
                       (not remove-unused-labels)
                       (managed-svref possible-label-dispatch-destination index))
                collect
                (lfsi-list
                  index
                  (lfsi-list 'go label))
                  into label-clause-list using lfsi-cons
              when (or all-branch-destinations-possible
                       (not remove-unused-labels)
                       (managed-svref possible-label-dispatch-destination index)
                       (managed-svref explicit-branch-destination index))
                collect label into form-list using lfsi-cons
              collect form into form-list using lfsi-cons
              do
          (setq length
                (length-of-stack-instruction index byte-code-body constant-vector))
          (incff index length)

              finally (return (values label-clause-list form-list)))
      (setq compiled-code
          (lfsi-list
            'lambda
            (copy-list-using-phrase-conses
              '(byte-code-body constant-vector local-var-vector fixnum-time-limit?
                initial-program-counter initial-top-of-stack initial-stack-frame-base
                initial-recursion-depth))
            (lfsi-list
              'let*
              (nconc
                (loop for (setf var form) in expanded-bindings-forms
                      collect (lfsi-list var (copy-tree-using-phrase-conses form))
                        using lfsi-cons)
                (loop for i from 0 to max-var-index
                      collect (lfsi-list (local-var i) (local-var-expression i))
                        using lfsi-cons)
                (loop for i from 0 to max-stack-index
                      collect (lfsi-list (stack-var i) nil)
                        using lfsi-cons)
                (when cache-stack-and-locals
                  (lfsi-list
                    (lfsi-list
                      'stack-already-decached nil)
                    (lfsi-list
                      'locals-already-decached nil))))
                (lfsi-list 'setf 'instruction-count-plus-pc (lfsi-list '+f 500 'initial-program-counter))
              (lfsi-list 'setf 'detailed-tracing? nil)
              (lfsi-list 'setf 'major-tracing? nil)
              (lfsi-list 'setf (copy-tree-using-phrase-conses cached-stack-program-counter-form) nil)
              (nconc
                (lfsi-list
                  'tagbody)
                (if cache-stack-and-locals
                    (lfsi-list
                      (cache-entire-stack-form max-stack-index 'label-dispatch))
                    nil)
                (lfsi-list
                  'label-dispatch
                  (nconc
                    (lfsi-list
                      'fixnum-case
                      'stack-program-counter)
                    label-clause-list
                    (lfsi-list
                      (copy-tree-using-phrase-conses expanded-default-clause-form))))
                form-list
                (lfsi-list
                  'check-timeout)
                (when inline-timeout-checks
                    (lfsi-list
                      (copy-tree-using-phrase-conses expanded-check-timeout-form)))
                (when cache-stack-and-locals (lfsi-list
                                               (decache-local-vars-form)))
                (lfsi-list
                  'exit-stack-eval-inner
                  (lfsi-list 'setf (copy-tree-using-phrase-conses cached-stack-program-counter-form)
                             'stack-program-counter)
                  (lfsi-list 'go 'end)
                  'exit-stack-eval-major-t
                  (lfsi-list 'setf 'fixnum-register-1 1)
                  (lfsi-list 'go 'exit-stack-eval-major)
                  'exit-stack-eval-major-nil
                  (lfsi-list 'setf 'fixnum-register-1 0)
                  'exit-stack-eval-major
                  (ensure-backpatching
                    (copy-tree-using-phrase-conses expanded-exit-stack-eval-major-form))
                  'exit-stack-eval-minor
                  (copy-tree-using-phrase-conses expanded-exit-stack-eval-minor-form)
                  'exit-stack-eval
                  (copy-tree-using-phrase-conses expanded-exit-form)
                  (lfsi-list 'setf 'stack-program-counter -1)
                  'end
                  (lfsi-list 'setf (copy-tree-using-phrase-conses cached-top-of-stack-form)
                             'top-of-stack))
                  (when cache-stack-and-locals
                    (lfsi-list
                      (lfsi-list
                        'if
                        'stack-already-decached
                        nil
                        (decache-entire-stack-form max-stack-index 'end2))))
                  (lfsi-list 'end2))
              expanded-return-values-form)))
      (reclaim-managed-array form-array)
      (reclaim-managed-array initial-stack-offsets)
      (reclaim-managed-array possible-label-dispatch-destination)
      (reclaim-managed-array explicit-branch-destination)))
    (values (remove-unused-local-variables compiled-code :all)
            constant-vector)))


(defun lisp-for-stack-instruction (op-code-address byte-code-body constant-vector length)
  (let* ((raw-byte-vector (byte-code-body-byte-vector byte-code-body))
         (op-code (byte-vector-aref raw-byte-vector op-code-address))
         (in-line-evaluator-p (in-line-evaluator-op-code-p op-code))
         (unexpanded-body
           (if in-line-evaluator-p
            (in-line-evaluator-description-for-op-code op-code)
            (instruction-description-for-op-code op-code)))
         (expanded-body
           (if in-line-evaluator-p
               (evaluator-expanded-body unexpanded-body)
               (stack-instruction-expanded-body unexpanded-body))))
    (lisp-for-stack-instruction-form
      op-code-address
      (+f length op-code-address)
      expanded-body
      byte-code-body
      constant-vector)))

(defun length-of-stack-instruction (op-code-address byte-code-body constant-vector)
  (let* ((raw-byte-vector (byte-code-body-byte-vector byte-code-body))
         (op-code (byte-vector-aref raw-byte-vector op-code-address)))
    (if (in-line-evaluator-op-code-p op-code)
        1
        (let* ((description?
                 (instruction-description-for-op-code op-code))
               (byte-length-or-function?
                 (when description?
                   (stack-instruction-byte-length description?))))
          (cond ((fixnump byte-length-or-function?)
                 byte-length-or-function?)
                ((compiled-function-p byte-length-or-function?)
                 (funcall-compiled-function
                   byte-length-or-function?
                   op-code-address raw-byte-vector constant-vector))
                (t 1))))))

;;; top-of-stack must be set before branching to epilog code.
;;; Some stack instructions that branch to epilog do this; others don't.
;;; So we keep track of this in the environment by setting the value for
;;; top-of-stack to the special value 'lfsi-bound-marker


(defun make-initial-lfsi-environment (initial-pc initial-offset constant-vector)
  (lfsi-list
    (nconc
      (lfsi-list
        (lfsi-list 'stack-program-counter initial-pc)
        (lfsi-list 'stack-offset initial-offset)
        (lfsi-list 'stack-frame-base lfsi-unbound-marker)
        (lfsi-list 'top-of-stack lfsi-unbound-marker)
        (lfsi-list 'register-1 lfsi-unbound-marker)
        (lfsi-list 'register-2 lfsi-unbound-marker)
        (lfsi-list 'register-3 lfsi-unbound-marker)
        (lfsi-list 'register-4 lfsi-unbound-marker)
        (lfsi-list 'register-5 lfsi-unbound-marker)
        (lfsi-list 'fixnum-register-1 lfsi-unbound-marker)
        (lfsi-list 'fixnum-register-2 lfsi-unbound-marker)
        (lfsi-list 'float-register-1 lfsi-unbound-marker)
        (lfsi-list 'float-register-2 lfsi-unbound-marker)
              (lfsi-list 'constant-vector constant-vector)))))

(defun lfsi-local-p (env variable-name)
  (loop for contour in env
        do
    (loop for (name value?) in contour
          when (eq name variable-name)
            do (return-from lfsi-local-p t))))

(defun get-lfsi-constant-value? (env variable-name)
  (loop for contour in env
        do
    (loop for (name value?) in contour
          when (eq name variable-name)
            do (return-from get-lfsi-constant-value? value?))))

(defun set-lfsi-constant-value (env variable-name new-value)
  (loop for contour in env
        do
    (loop for name+value in contour
          as (name value) = name+value
          when (eq name variable-name)
            do (setf (cadr name+value) new-value)
               (return-from set-lfsi-constant-value nil))))

(defun maybe-add-top-of-stack-setq (form env)
  (if (eq (get-lfsi-constant-value? env 'top-of-stack) 'lfsi-unbound-marker)
      (let ((offset (get-lfsi-constant-value? env 'stack-offset)))
        (lfsi-list 'progn
                   (lfsi-list
                     'setf 'top-of-stack
                     (cond
                       #+development
                       ((eq offset 'lfsi-unbound-marker)
                        (cerror "continue"
                                "unknown stack-offset when binding top-of-stack"))
                       ((=f offset 0)
                        'stack-frame-base)
                       (t
                        (lfsi-list
                          '+f 'stack-frame-base offset))))
                   form))
      form))

(defun-simple prune-lfsi-environment (main-env other-env)
  ;; this needs to be re-thought for "let/let*"
  (let ((main-env-changed nil))
    (loop for contour in main-env
          do
      (loop for name+value in contour
            as (name value) = name+value
            as value-in-other-env = (get-lfsi-constant-value? other-env name)
            do
        (unless (or (eq (cadr name+value) lfsi-unbound-marker)
                    (lfsi-constant-= value value-in-other-env))
          (setf (cadr name+value) lfsi-unbound-marker)
          (setf main-env-changed t))))
    main-env-changed))

(defun-void merge-lfsi-environments (main-env if-env else-env)
  (loop for contour in main-env
        do
    (loop for name+value in contour
          as (name value) = name+value
          as value-in-if-env = (get-lfsi-constant-value? if-env name)
          as value-in-else-env = (get-lfsi-constant-value? else-env name)
          do
      (if (lfsi-constant-= value-in-else-env value-in-if-env)
          (setf (cadr name+value) value-in-if-env)
          (setf (cadr name+value) lfsi-unbound-marker)))))


(defun-simple lfsi-constant-= (a b)
  (or (eql a b)
      (cond ((text-string-p a)
             (and (text-string-p b)
                  (text-string-equal+ a b)))
            ((consp a)
             (equal a b))
            (t
             nil))))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun lfsi-constant-p (expression)
  (or (fixnump expression)
      (gensym-float-p expression)
      (gensym-string-p expression)
      (text-string-p expression)
      (eq expression t)
      (eq expression nil)
      (keywordp expression)
      (and (consp expression)
           (eq (car expression) 'quote))))
)

;;; this is conservative, and could be improved.
(defun lfsi-side-effect-free-p (expression)
  (or (lfsi-constant-p expression)
      (and (consp expression)
           (inlined-function-data (car expression))
           (every #'lfsi-side-effect-free-p (cdr expression)))))

(defun-simple lfsi-form-list-to-form (forms)
  (cond ((eql (length forms) 1) (car forms))
        (t (lfsi-cons 'progn forms))))

(defun lisp-for-stack-instruction-form
    (op-code-address next-op-code-address form byte-code-body constant-vector)
  (let ((env (make-initial-lfsi-environment
               op-code-address
               (managed-svref initial-stack-offsets op-code-address)
               constant-vector)))
    (multiple-value-bind (form value does-not-return)
        (lisp-for-stack-instruction-form-1
          op-code-address next-op-code-address
          form byte-code-body constant-vector env t)
      (setq form (maybe-generate-go-after-form form value does-not-return
                                               env next-op-code-address t))
      (if (and (consp form) (eq (car form) 'progn))
          (lfsi-cons 'progn (remove-unused-register-sets (cdr form)))
          form))))

(defconstant names-of-vectors-to-always-inline
  `(constant-vector
    funcalled-instructions
    funcalled-evaluator-array
    funcalled-evaluator-dispatch-type))

(defun-simple make-vectors-to-always-inline ()
  (loop for name in names-of-vectors-to-always-inline
        when (not (eq name 'constant-vector)) collect (symbol-value name)))

(defparameter vectors-to-always-inline
  (make-vectors-to-always-inline))

(defun function-does-not-return (index)
  (eq (throws-stack-error (aref c-byte-code-functions index)) :always))

(defun record-possible-next-op-code (env pc)
  (let ((current-offset (get-lfsi-constant-value? env 'stack-offset))
        (new-offset (managed-svref initial-stack-offsets pc)))
    (unless new-offset
      (incff unused-known-offsets)
      (setf new-offset (if (eq current-offset lfsi-unbound-marker)
                           (progn
                             #+development
                             (cerror "continue anyway"
                                     "Unknown stack-offset at end of non-terminal instruction proceeding to address ~d" pc)
                             0)
                           current-offset))
      (setf (managed-svref initial-stack-offsets pc) new-offset))
    #+development
    (unless (=f new-offset current-offset)
      (cerror "continue anyway"
              "Execution-path dependent stack offset at address ~d"
              pc))))


(defvar enclosing-form-will-wrap nil)

(defun maybe-wrap-for-decaching (form stack-offset)
  (if enclosing-form-will-wrap
      form
      (multiple-value-bind (pre-forms post-forms)
          (decaching-wrappers form stack-offset)
        (if (or pre-forms post-forms)
            (nconc
              (lfsi-list 'progn)
              pre-forms
              (if (eq (car form) 'progn)
                  (cdr form)
                  (lfsi-list form))
              post-forms)
            form))))

;;; Floating point error only causes throws on certain platforms.
(defvar float-errors-are-possible nil)

(defvar throws-from-breakpoints-are-possible t)

(defvar wrap-conservatively nil)

(defun decaching-wrappers (form stack-offset)
  (cond
    ((not cache-stack-and-locals) (values nil nil))
    ((atom form) (values nil nil))
    ((or (eq (car form) 'setf) (eq (car form) 'multiple-value-setq))
     (decaching-wrappers (third form) stack-offset))
    ((eq (car form) 'call-simple-function-without-decaching) (values nil nil))
    ((or (eq (car form) 'call-function) (eq (car form) 'call-simple-function))
     (let* ((function-data (aref c-byte-code-functions (second form)))
            (throws-stack-error (if wrap-conservatively
                                    :sometimes
                                    (throws-stack-error function-data)))
            (reads (if wrap-conservatively (stack-reads function-data) t))
            (writes (if wrap-conservatively (stack-writes function-data) t)))
       (values
         (cond
           ((or (eq throws-stack-error :always)
                (eq throws-stack-error :sometimes)
                (and (eq throws-stack-error :float) float-errors-are-possible)
                (and (eq throws-stack-error :breakpoint) throws-from-breakpoints-are-possible)
                (eq throws-stack-error :unknown))
            (lfsi-cons (decache-local-vars-form)
                       (loop for i from 0 to stack-offset
                             collect (decache-stack-var-form i)
                               using lfsi-cons)))
           ((eq reads t)
            (loop for i from 0 to stack-offset
                  collect (decache-stack-var-form i)
                    using lfsi-cons))
           ((null reads) nil)
           (t
            (loop for i from (+f (-f stack-offset reads) 1) to stack-offset
                  collect (decache-stack-var-form (-f stack-offset i))
                    using lfsi-cons)))
         (unless (eq throws-stack-error :always)
           (cond
             ((or (eq writes t) (eq writes :reclaim))
              (loop for i from 0 to stack-offset
                    collect (cache-stack-var-form i)
                      using lfsi-cons))
             ((null writes) nil)
             (t
              (loop for i from (+f stack-offset (car writes))
                    to (+f stack-offset (cdr writes))
                  collect (decache-stack-var-form (-f stack-offset i))
                    using lfsi-cons)))))))
    (t (values nil nil))))

(defun stack-frame-base-relative-index (form)
  (if (consp form)
      (cond ((eq (car form) '+f)
             (let ((offset (third form)))
               (when (fixnump offset)
                 (let ((inner (stack-frame-base-relative-index
                                (second form))))
                   (when (and inner offset)
                     (+f inner offset))))))
            ((eq (car form) '-f)
             (let ((offset (third form)))
               (when (fixnump offset)
                 (let ((inner (stack-frame-base-relative-index
                                (second form))))
                   (when (and inner offset)
                     (-f inner offset))))))
            (t nil))
      (if (eq form 'stack-frame-base) 0 nil)))

(defun lisp-for-stack-instruction-form-1
    (op-code-address next-op-code-address
                     form byte-code-body constant-vector env last-form-p)
  (macrolet
      ((walk (sub &optional last-form-p)
         `(lisp-for-stack-instruction-form-1
            op-code-address next-op-code-address
            ,sub byte-code-body constant-vector env ,last-form-p))
       (walk-for-branch (sub new-env &optional last-form-p)
         `(lisp-for-stack-instruction-form-1
            op-code-address next-op-code-address
            ,sub byte-code-body constant-vector ,new-env ,last-form-p)))
    (typecase form
      (symbol (cond ((null form)
                     (values nil nil))
                    ((lfsi-local-p env form)
                     (let ((value (get-lfsi-constant-value? env form)))
                       (values
                         (if (or (fixnump value)
                                 (floatp value)
                                 (null value))
                             value
                             form)
                         value)))
                    ;; Not sure what this clause is doing here;
                    ;; Never used, I think -alatto, 12/2/98
                    ((member form '(c-byte-code-variables
                                    c-byte-code-constants
                                    c-byte-code-functions))
                     (values form lfsi-unbound-marker))
                    (t
                     (values form lfsi-unbound-marker))))
      (fixnum (values form form))
      (float  (values form form))
      (atom (error "bad constant ~S" form))
      (cons
       (cond
         ((not (symbolp (car form)))
          (error "bad form: car must be symbol: ~S" form))
         (t
          (case (car form)
            ((go)
             (cond
               ((memq (cadr form) '(check-timeout label-dispatch))
                ;; execution might resume later at the current value of
                ;; stack-program-counter.
                (let ((next
                        (get-lfsi-constant-value? env 'stack-program-counter)))
                  (if (eq next lfsi-unbound-marker)
                      (progn
                        (setq all-branch-destinations-possible t)
                        #+development
                        (warn "Unknown stack-program-counter at instruction  ~D"
                              op-code-address))
                      (setf (managed-svref possible-label-dispatch-destination next)
                            t))))
               ((memq (cadr form) '(exit-stack-eval-major-nil
                                    exit-stack-eval-major-t
                                    exit-stack-eval-minor
                                    exit-stack-eval-inner))
                ;; execution might resume later at the next instruction,
                ;; a value of stack-program-counter that has been
                ;; stored away in the computation instance.
                (unless (third form)
                  (setf (managed-svref possible-label-dispatch-destination
                                       next-op-code-address)
                        t)
                  (record-possible-next-op-code env next-op-code-address)))
               ((eq (cadr form) 'exit-stack-eval))
               ;; execution will not resume.
               ;; the branch to exit-stack-eval-minor in return-from-function
               ;; and complete-simulation-variable-evaluation should
               ;; also be covered by this exception. Not sure the
               ;; cleanest way to handle this.
               (t (error "bad form: go ~S" form)))
             (values
               (nconc
                 (lfsi-list
                   'progn
                   ;; probably don't need the local-var-vector at exit-stack
                   ;; eval, but the things in it need to get reclaimed,
                   ;; and this is the easiest way to accomplish that
                   (when (and
                           (eq (cadr form) 'exit-stack-eval)
                           cache-stack-and-locals)
                     (decache-local-vars-form)))
                 (when (and cache-stack-and-locals (not (fourth form)))
                   (loop for i from 0 to
                         (get-lfsi-constant-value? env 'stack-offset)
                         collect (decache-stack-var-form i)
                           using lfsi-cons))
                 (lfsi-list
                   (maybe-add-top-of-stack-setq
                     (if (cddr form)
                         (lfsi-list 'go (second form))
                         form)
                     env)))
               lfsi-unbound-marker t))
            ((decache-local-var-vector)
             (values (if cache-stack-and-locals
                         (lfsi-list
                           'progn
                           (lfsi-list
                             'setf 'locals-already-decached 1)
                           (decache-local-vars-form))
                         nil)
                     lfsi-unbound-marker))
            ((cache-local-var-vector)
             (values
               (if cache-stack-and-locals
                   (cache-local-vars-form)
                   nil)
               lfsi-unbound-marker))
            ((decache-stack)
             (values
               (when cache-stack-and-locals
                 (nconc
                   (lfsi-list
                     'progn
                     (lfsi-list
                       'setf 'stack-already-decached 1))
                   (loop for i from 0 to (get-lfsi-constant-value?
                                           env 'stack-offset)
                         collect (decache-stack-var-form i)
                           using lfsi-cons)))
               lfsi-unbound-marker))
            ((incff-top-of-stack-with-caching)
             (multiple-value-bind (inc-exp inc-value)
                 (walk (second form))
               (declare (ignore inc-exp))
               #+development
               (unless (fixnump inc-value)
                 (error "argument to incff-top-of-stack-with-caching not known at compile time"))
             (values
               (nconc
                 (lfsi-list
                   'progn
                   (walk (lfsi-list 'incff 'stack-offset (second form))))
                 (when cache-stack-and-locals
                   (loop with offset = (get-lfsi-constant-value?
                                         env 'stack-offset)
                         for i from (-f (1+f offset) inc-value) to offset
                         collect (cache-stack-var-form i)
                           using lfsi-cons)))
               lfsi-unbound-marker)))
            ((decache-for-funcall-instruction)
             (multiple-value-bind (function-form function-value)
                 (walk (cadr form))
               (declare (ignore function-form))
               (multiple-value-bind (nargs-form nargs-value)
                   (walk (caddr form))
                 (declare (ignore nargs-form))
                 #+development
                 (unless (and (fixnump nargs-value)
                              function-value
                              (not (eq function-value 'lfsi-unbound-marker)))
                   (cerror "Continue"
                           "Bad decache-for-funcall-instruction form ~S"
                           form))
                 (let*
                     ((function-index (byte-code-function-index-for-phase-2 function-value))
                      (function-data (aref c-byte-code-functions function-index))
                      (throws-stack-error (if wrap-conservatively
                                              :sometimes
                                              (throws-stack-error function-data)))
                      (stack-offset
                        (get-lfsi-constant-value? env 'stack-offset)))
                   (values
         (cond
            ((or (eq throws-stack-error :always)
                 (eq throws-stack-error :sometimes)
                 (and (eq throws-stack-error :float) float-errors-are-possible)
                 (and (eq throws-stack-error :breakpoint) throws-from-breakpoints-are-possible)
                 (eq throws-stack-error :unknown))
             (lfsi-cons 'progn
                        (lfsi-cons (decache-local-vars-form)
                                   (loop for i from 0 to stack-offset
                                         collect (decache-stack-var-form i)
                                           using lfsi-cons))))
           (t
            (lfsi-cons 'progn
                       (loop for i from (+f (-f stack-offset nargs-value) 1) to stack-offset
                  collect (decache-stack-var-form (-f stack-offset i))
                    using lfsi-cons))))
         nil)))))
               ((quote)
             (error "bad form: quote ~S" form))
            ((get-constant)
             (values form (get-constant (cadr form))))
            ((get-foldable-variable)
             (values (lfsi-list 'get-variable (second form))
                     (symbol-value (third form))))
            ((progn)
             (loop with expanded-form and value and does-not-return
                   for form-tail on (cdr form)
                   for sub-form = (car form-tail)
                   for last-p = (null (cdr form-tail))
                   do (multiple-value-setq (expanded-form value does-not-return)
                        (walk sub-form (and last-p last-form-p)))
                   unless (null expanded-form)
                     collect expanded-form
                       into sub-forms
                       using lfsi-cons
                   when (or last-p does-not-return)
                     return (values (lfsi-cons 'progn sub-forms)
                                    value
                                    does-not-return)))
            ((or)
             (loop with expanded-sub-form and expanded-sub-form-value
                   with all-constants-p = t
                   with value = nil
                   for sub-form in (cdr form)
                   do (multiple-value-setq
                          (expanded-sub-form expanded-sub-form-value)
                        (walk sub-form))
                      (if (eq expanded-sub-form-value lfsi-unbound-marker)
                          (setq all-constants-p nil)
                          (setq value (or value expanded-sub-form-value)))
                   until (and expanded-sub-form-value
                              (not (eq expanded-sub-form-value lfsi-unbound-marker)))
                   unless (null expanded-sub-form-value)
                     collect expanded-sub-form
                       into sub-expressions
                       using lfsi-cons
                   finally (return
                             (cond (all-constants-p
                                    (values value value)) ;only appears in a :predicate context
                                   ((null sub-expressions)
                                    (values nil nil))
                                   ((null (cdr sub-expressions))
                                    (values (car sub-expressions) lfsi-unbound-marker))
                                   (t
                                    (values (lfsi-cons 'or sub-expressions)
                                            lfsi-unbound-marker))))))
            ((and)
             (loop with expanded-sub-form and expanded-sub-form-value
                   with all-constants-p = t
                   with value = t
                   for sub-form-tail on (cdr form)
                   for sub-form = (car-of-cons sub-form-tail)
                   do (multiple-value-setq
                          (expanded-sub-form expanded-sub-form-value)
                        (walk sub-form))
                      (if (eq expanded-sub-form-value lfsi-unbound-marker)
                          (setq all-constants-p nil)
                          (setq value (and value expanded-sub-form-value)))
                   until (null expanded-sub-form-value)
                   when (eq expanded-sub-form-value lfsi-unbound-marker)
                     collect expanded-sub-form
                       into sub-expressions
                       using lfsi-cons
                   finally (return
                             (cond (all-constants-p
                                    (values value value)) ;only appears in a :predicate context
                                   ((null sub-expressions)
                                    (values (lfsi-list 'get-constant (byte-code-constant-index-macro t)) t))
                                   ((null (cdr sub-expressions))
                                    (values (car sub-expressions) lfsi-unbound-marker))
                                   (t
                                    (values (lfsi-cons 'and sub-expressions)
                                            lfsi-unbound-marker))))))
            ((setf)
             (cond
               ((and (symbolp (cadr form))
                     (lfsi-local-p env (cadr form)))
                (multiple-value-bind (expanded-value-form expanded-value-form-value)
                    (let ((enclosing-form-will-wrap t))
                      (walk (caddr form)))
                  (set-lfsi-constant-value env (cadr form) expanded-value-form-value)
                  (values (maybe-wrap-for-decaching
                            (cond
                            ((not (eq (cadr form) 'stack-program-counter))
                             (unless (arrayp expanded-value-form)
                               (lfsi-list 'setf (cadr form) expanded-value-form)))
                            ((or (not (fixnump expanded-value-form))
                                 (<=f expanded-value-form op-code-address)
                                 (<f next-op-code-address expanded-value-form))
                             (lfsi-list
                               'progn
                               (lfsi-list 'setf 'stack-program-counter expanded-value-form)
                               (lfsi-list 'setf 'instruction-count-plus-pc
                                          (lfsi-list
                                            '+f
                                            'instruction-count-plus-pc
                                            (if (fixnump expanded-value-form)
                                                (-f expanded-value-form next-op-code-address)
                                                (lfsi-list '-f 'stack-program-counter
                                                           next-op-code-address))))))
                            ((=f next-op-code-address expanded-value-form)
                             (lfsi-list 'setf (cadr form) expanded-value-form))
                            (t
                             nil))
                            (get-lfsi-constant-value? env 'stack-offset))
                          expanded-value-form-value)))
               (t
                (multiple-value-bind (expanded-value-form expanded-value-form-value)
                    (walk (caddr form))
                  (values (lfsi-list 'setf (walk (cadr form)) expanded-value-form)
                          expanded-value-form-value)))))
            ((let)
             (loop with expanded-value-form and expanded-value-form-value
                   for (var value) in (cadr form)
                   do (multiple-value-setq (expanded-value-form expanded-value-form-value)
                        (walk value))
                   collect (lfsi-list var expanded-value-form-value)
                     into new-contour
                     using lfsi-cons
                   collect (lfsi-list var expanded-value-form)
                     into new-bindings
                     using lfsi-cons
                   finally
                     (return
                       (multiple-value-bind (expanded-body-form expanded-body-value)
                           (walk-for-branch (lfsi-cons 'progn (cddr form))
                                            (lfsi-cons new-contour env)
                                            last-form-p)
                         (values
                           (if (and (consp expanded-body-form)
                                    (eq (car expanded-body-form) 'progn))
                               (lfsi-cons 'let (lfsi-cons new-bindings (cdr expanded-body-form)))
                               (lfsi-list 'let new-bindings expanded-body-form))
                           expanded-body-value)))))
            ((let*)
             (let ((let*env env))
               (loop with expanded-value-form and expanded-value-form-value
                     for (var value) in (cadr form)
                     do (multiple-value-setq (expanded-value-form expanded-value-form-value)
                          (walk-for-branch value let*env))
                        (setq let*env
                              (lfsi-cons (lfsi-list
                                           (lfsi-list var expanded-value-form-value))
                                         let*env))
                     collect (lfsi-list var expanded-value-form)
                       into new-bindings
                       using lfsi-cons
                     finally
                       (return
                         (multiple-value-bind (expanded-body-form expanded-body-value)
                             (walk-for-branch (lfsi-cons 'progn (cddr form))
                                              let*env
                                              last-form-p)
                           (values
                             (if (and (consp expanded-body-form)
                                      (eq (car expanded-body-form) 'progn))
                                 (lfsi-cons 'let* (lfsi-cons new-bindings (cdr expanded-body-form)))
                                 (lfsi-list 'let* new-bindings expanded-body-form))
                             expanded-body-value))))))
            ((byte-vector-aref)
             (let* ((index-expression (walk (caddr form)))
                    (byte (and (eq (cadr form) 'instruction-vector)
                               (fixnump index-expression)
                               (byte-vector-aref
                                 (byte-code-body-byte-vector byte-code-body)
                                 index-expression))))
               (if byte
                   (values byte byte)
                   (values (lfsi-list 'byte-vector-aref (cadr form) index-expression)
                           lfsi-unbound-marker))))
            ((svref svref-without-inlining svref-with-inlining)
             (multiple-value-bind (vector-expression vector-value)
                 (walk (cadr form))
               (let* ((index-expression (walk (caddr form)))
                      (vector-form (cadr form))
                      (name (if (and (consp vector-form)
                                     (eq (car vector-form) 'get-foldable-variable))
                                (caddr vector-form)
                                vector-form))
                      (constantp
                        (and vector-value
                             (not (eq vector-value lfsi-unbound-marker))
                             (fixnump index-expression)
                             (not (eq (car form) 'svref-without-inlining))
                             (or (eq (car form) 'svref-with-inlining)
                                 (memq name
                                       names-of-vectors-to-always-inline)
                                 (memq vector-value
                                       vectors-to-always-inline))))
                      (constant (if constantp
                                    (svref vector-value index-expression)
                                    lfsi-unbound-marker)))
                 (cond ((and (eq name 'local-var-vector)
                             cache-stack-and-locals)
                        (if (fixnump index-expression)
                            (walk (local-var index-expression))
                            #+development
                            ;; Really we should insert decaching and recaching
                            ;; code here
                            (progn
                              (cerror
                                "Continue"
                                "unknown index ~A into variable vector"
                                index-expression)
                              (values
                                (lfsi-list 'svref vector-expression index-expression)
                                lfsi-unbound-marker))))
                       ((and (eq name 'local-stack) cache-stack-and-locals)
                        (let ((relative-index
                                (stack-frame-base-relative-index
                                  index-expression)))
                          (if relative-index
                              (walk (stack-var relative-index))
                              #+development
                              (progn
                                (cerror
                                  "Continue"
                                  "unknown index ~A into stack"
                                  index-expression)
                                ;; Really we should insert decaching and
                                ;; recachine code here
                                (values
                                  (lfsi-list 'svref vector-expression index-expression)
                                  lfsi-unbound-marker)))))
                       (t
                        (values (if (or (fixnump constant)
                                        (floatp constant)
                                        (null constant)
                                        (eq (car form) 'svref-with-inlining)
                                        (eq name 'funcalled-instructions)
                                        (eq name 'funcalled-evaluator-array))
                                    constant
                                    (lfsi-list 'svref vector-expression index-expression))
                                constant))))))
            ((funcall-simple-compiled-function funcall-simple-multi-valued-compiled-function funcall-simple-compiled-function-without-decaching)
             (multiple-value-bind (walked-function-form walked-function-value)
                 (let ((enclosing-form-will-wrap t))
                   (walk (cadr form)))
               (let* ((name (and (not (eq lfsi-unbound-marker walked-function-value))
                                 (symbolp walked-function-value)
                                 walked-function-value))
                      (index (when name
                               (byte-code-function-index-for-phase-2 name)))
                      (walked-arguments (loop for sub-form in (cddr form)
                                              collect
                                              (let ((enclosing-form-will-wrap t))
                                                (walk sub-form))
                                                using lfsi-cons)))
                 (when (and name (null index))
                   (notify-user-at-console "Need to add a declaration for ~S" name))
                 (if (or index name)
                     (values
                       (maybe-wrap-for-decaching
                         (lfsi-cons
                           (case (car form)
                             (funcall-simple-compiled-function 'call-function)
                             (funcall-simple-multi-valued-compiled-function 'call-simple-function)
                             (funcall-simple-compiled-function-without-decaching 'call-simple-function-without-decaching))
                           (lfsi-cons (or index -1) walked-arguments))
                         (get-lfsi-constant-value? env 'stack-offset))
                       lfsi-unbound-marker
                       (when index (function-does-not-return index)))
                     (values
                       (lfsi-cons (car form) (lfsi-cons walked-function-form walked-arguments))
                       lfsi-unbound-marker
                       nil))))) ;(function-does-not-return (cadr form))
            ((if ife)
             (multiple-value-bind (condition-expression condition-value)
                 (walk (cadr form))
               (cond
                 ((not (eq condition-value lfsi-unbound-marker))
                  (if condition-value
                      (walk (caddr form) last-form-p)
                      (walk (cadddr form) last-form-p)))
                 ((cdddr form)
                  (let ((then-env (lfsi-copy-tree env))
                        (else-env (lfsi-copy-tree env)))
                    (multiple-value-bind (true-expression true-value true-does-not-return)
                        (walk-for-branch (caddr form) then-env last-form-p)
                      (multiple-value-setq (true-expression true-value true-does-not-return)
                        (maybe-generate-go-after-form true-expression true-value true-does-not-return
                                                      then-env next-op-code-address last-form-p))
                      (multiple-value-bind (false-expression false-value false-does-not-return)
                          (walk-for-branch (cadddr form) else-env last-form-p)
                        (multiple-value-setq (false-expression false-value false-does-not-return)
                          (maybe-generate-go-after-form false-expression false-value false-does-not-return
                                                        else-env next-op-code-address last-form-p))
                        (values
                          (prog1 (lfsi-list
                                   (car form) condition-expression
                                   true-expression
                                   false-expression)
                            (if true-does-not-return
                                (if false-does-not-return
                                    nil
                                    (prune-lfsi-environment env else-env))
                                (if false-does-not-return
                                    (prune-lfsi-environment env then-env)
                                    (merge-lfsi-environments
                                      env then-env else-env))))
                          (cond (true-does-not-return false-value)
                                (false-does-not-return true-value)
                                (t lfsi-unbound-marker))
                          (and true-does-not-return false-does-not-return))))))
                 (t
                  (let ((then-env (lfsi-copy-tree env)))
                    (multiple-value-bind (expression value does-not-return)
                        (walk-for-branch (caddr form) then-env last-form-p)
                      (multiple-value-setq (expression value does-not-return)
                        (maybe-generate-go-after-form expression value does-not-return
                                                      then-env next-op-code-address last-form-p))
                      (values
                        (prog1
                            (lfsi-list
                              (car form) condition-expression
                              expression)
                          (unless does-not-return
                            (prune-lfsi-environment env then-env)))
                        (if does-not-return nil value))))))))
            ((loop)
             (cond ((and (eq (second form) 'while)
                         (eq (fourth form) 'do)
                         (every #'consp (nthcdr 4 form)))
                    (multiple-value-bind (test-expression test-value)
                        (walk (third form))
                      (declare (ignore test-expression))
                      (cond ((eq test-value lfsi-unbound-marker)
                             (let ((looping-env (lfsi-copy-tree env))
                                   (main-env-changed t))
                               (loop while main-env-changed
                                     do
                                 (loop for sub-form in (nthcdr 4 form) do
                                   (walk-for-branch sub-form looping-env))
                                 (walk-for-branch (third form) looping-env)
                                 (setf main-env-changed
                                       (prune-lfsi-environment env looping-env))))
                             (values form lfsi-unbound-marker))
                            ((not test-value)
                             (values nil nil))
                            (t
                             (walk
                               (lfsi-cons
                                 'progn
                                 (nconc
                                   (loop for sub-form in (nthcdr 4 form)
                                         collect sub-form using lfsi-cons)
                                   (lfsi-list form))))))))
                   (t
                    (warn "bad form: loop ~S" form))))
            ((fixnum-case-with-branches)
             (multiple-value-bind (key-expression key-value)
                 (walk (cadr form))
               (cond ((not (eq key-value lfsi-unbound-marker))
                      (walk (lfsi-cons 'fixnum-case (cdr form)) last-form-p))
                     (t
                      (let ((no-branch-returns t))
                        #+development
                        (unless (lfsi-local-p env key-expression)
                          (cerror "Proceed anyway"
                                  "Key expression ~S in ~
                              fixnum-case-with-branches is not a local variable"
                                  key-expression))
                        (values
                          (nconc
                            (lfsi-list
                              'fixnum-case
                              key-expression)
                            (loop for branch in (cddr form)
                                  collect
                                  (let ((branch-env
                                          (lfsi-cons
                                            (lfsi-list
                                              (lfsi-list key-expression
                                                         (car branch)))
                                            (lfsi-copy-tree env))))
                                    (multiple-value-bind
                                        (exp value does-not-return)
                                        (walk-for-branch
                                          (cadr branch)
                                          branch-env
                                          last-form-p)
                                      (multiple-value-bind
                                          (exp inner-value does-not-return)
                                          (maybe-generate-go-after-form
                                            exp value does-not-return branch-env
                                            next-op-code-address last-form-p)
                                        (declare (ignore inner-value))
                                        (unless does-not-return
                                          (setf no-branch-returns nil)
                                          (prune-lfsi-environment env branch-env))
                                        (lfsi-list (car branch) exp))))
                                    using lfsi-cons))
                          lfsi-unbound-marker
                          no-branch-returns))))))
            ((fixnum-case case)
             (multiple-value-bind (key-expression key-value)
                 (walk (cadr form))
               (cond ((eq key-value lfsi-unbound-marker)
                      ;; This isn't right.
                      (values (lfsi-cons
                                (car form)
                                (lfsi-cons key-expression (cddr form)))
                              lfsi-unbound-marker))
                     (t
                      (walk (lfsi-cons
                              'progn
                              (loop for clause in (cddr form)
                                    for key-or-keys = (car clause)
                                    when (or (eq key-or-keys 't)
                                             (eq key-or-keys 'otherwise)
                                             (if (atom key-or-keys)
                                                 (eql key-value key-or-keys)
                                                 (member  key-value key-or-keys)))
                                      return (cdr clause)))
                            last-form-p)))))
            ((multiple-value-setq)
             (multiple-value-bind (expression value)
                 (let ((enclosing-form-will-wrap t))
                   (walk (caddr form)))
               (declare (ignore value))
               (dolist (var (cadr form))
                 (set-lfsi-constant-value env var lfsi-unbound-marker))
               (values (maybe-wrap-for-decaching
                         (lfsi-list (car form) (cadr form) expression)
                         (get-lfsi-constant-value? env 'stack-offset))
                       lfsi-unbound-marker)))
            ((incff decff)
             (cond ((symbolp (cadr form))
                    (let ((expansion
                            (lfsi-list 'setf
                                       (cadr form)
                                       (lfsi-list (if (eq (car form) 'incff) '+f '-f)
                                                  (cadr form)
                                                  (caddr form)))))
                      (walk expansion last-form-p)))
                   (t
                    (values (lfsi-list (car form) (walk (cadr form)) (walk (caddr form)))
                            lfsi-unbound-marker))))
            ((not null atom consp fixnump symbolp car cdr car-of-cons cdr-of-cons pluspe pluspf)
             (multiple-value-bind (expanded-sub-form expanded-sub-form-value)
                 (walk (cadr form))
               (if (eq expanded-sub-form-value lfsi-unbound-marker)
                   (values (lfsi-list (car form) expanded-sub-form) lfsi-unbound-marker)
                   (let ((value (case (car form)
                                  ((not null) (not expanded-sub-form-value))
                                  (atom (atom expanded-sub-form-value))
                                  (consp (consp expanded-sub-form-value))
                                  (fixnump (fixnump expanded-sub-form-value))
                                  (symbolp (symbolp expanded-sub-form-value))
                                  ((car car-of-cons) (car expanded-sub-form-value))
                                  ((cdr cdr-of-cons) (cdr expanded-sub-form-value))
                                  ((pluspe pluspf) (plusp expanded-sub-form-value)))))
                     (cond ((null value)
                            (values nil nil))
                           ((eq value 't)
                            (values (lfsi-list 'get-constant (byte-code-constant-index-macro t))
                                    t))
                           (t
                            (values (lfsi-list (car form) expanded-sub-form)
                                    value)))))))
            ((eq <f >f =f <=f >=f /=f)
             (multiple-value-bind (form1 value1)
                 (walk (cadr form))
               (multiple-value-bind (form2 value2)
                   (walk (caddr form))
                 (cond ((or (eq value1 lfsi-unbound-marker)
                            (eq value2 lfsi-unbound-marker))
                        (values (lfsi-list (car form) form1 form2) lfsi-unbound-marker))
                       ((case (car form)
                          (eq (eq value1 value2))
                          (<f (<f value1 value2))
                          (>f (>f value1 value2))
                          (=f (=f value1 value2))
                          (<=f (<=f value1 value2))
                          (>=f (>=f value1 value2))
                          (/=f (/=f value1 value2)))
                        (values (lfsi-list 'get-constant (byte-code-constant-index-macro t))
                                t))
                       (t
                        (values nil nil))))))
            ((1-f)
             (walk (lfsi-list '-f (cadr form) 1)))
            ((+f -f *f right-shiftf left-shiftf logandf logiorf)
             (if (and (eq (car form) '-f)
                      (null (cddr form)))
                 (let* ((sub-form (cadr form))
                        (sub-expression (walk sub-form)))
                   (if (fixnump sub-expression)
                       (let ((value (-f sub-expression)))
                         (values value value))
                       (values (lfsi-list (car form) sub-expression)
                               lfsi-unbound-marker)))
                 (let* ((op (car form))
                        (sub-form1 (cadr form))
                        (sub-form2 (caddr form))
                        (sub-expression1 (walk sub-form1))
                        (sub-expression2 (walk sub-form2)))
                   (cond
                     ((and (fixnump sub-expression1)
                           (fixnump sub-expression2))
                      (let ((value
                              (case op
                                (+f (+f sub-expression1 sub-expression2))
                                (-f (-f sub-expression1 sub-expression2))
                                (*f (*f sub-expression1 sub-expression2))
                                (right-shiftf (right-shiftf sub-expression1 sub-expression2))
                                (left-shiftf (left-shiftf sub-expression1 sub-expression2))
                                (logandf (logandf sub-expression1 sub-expression2))
                                (logiorf (logiorf sub-expression1 sub-expression2)))))
                        (values value value)))
                     ((and (or (eq op '+f) (eq op '-f))
                           (fixnump sub-expression2)
                           (consp sub-expression1)
                           (let ((op1 (car sub-expression1)))
                             (and (or (eq op1 '+f) (eq op1 '-f))
                                  (fixnump (caddr sub-expression1)))))
                      (let* ((v1 (caddr sub-expression1))
                             (v2 sub-expression2)
                             (delta (+f (if (eq (car sub-expression1) '-f)
                                            (-f v1)
                                            v1)
                                        (if (eq op '-f)
                                            (-f v2)
                                            v2))))
                        (values (lfsi-list '+f (cadr sub-expression1) delta)
                                lfsi-unbound-marker)))
                     (t
                      (values (lfsi-list op sub-expression1 sub-expression2)
                              lfsi-unbound-marker))))))
            ((compiled-case-dispatch)
             (let ((switch-expression (walk (cadr form))))
               (multiple-value-bind (ignore base-value)
                   (walk (third form))
                 (declare (ignore ignore))
                 (multiple-value-bind (ignore final-value)
                     (walk (fourth form))
                   (declare (ignore ignore))
                   #+development
                   (unless (and (fixnump base-value) (fixnump final-value))
                     (error "Unknown base or final case-dispatch value in form ~S" form))
                   (walk
                     (nconc
                       (lfsi-list
                         'fixnum-case-with-branches
                         switch-expression)
                       (loop for index from base-value below final-value
                             collect
                             (lfsi-list
                               index
                               (make-long-code-constant-stack-program-counter-assignment-form index))
                               using lfsi-cons))
                     last-form-p)))))
            (t
             (values
               (cond ((inlined-function-data (car form))
                      (lfsi-cons
                        (car form)
                        (loop for sub-form in (cdr form)
                              collect (walk sub-form)
                                using lfsi-cons)))
                     (t
                      (maybe-wrap-for-decaching
                        form
                        (get-lfsi-constant-value? env 'stack-offset))))
               lfsi-unbound-marker
               (if (memq (car form) '(call-function call-simple-function))
                   (function-does-not-return (cadr form))
                   nil))))))))))

(defun maybe-generate-go-after-form (expression value does-not-return env next-op-code-address last-form-p)
  (if (or (not last-form-p) does-not-return)
      (values expression value does-not-return)
      (let* ((pc (get-lfsi-constant-value? env 'stack-program-counter))
             (go-label (cond ((eq pc lfsi-unbound-marker)
                              #+development
                              (cerror "Branch to label-dispatch"
                                      "Unknown branch destination just before address ~d"
                                      next-op-code-address)
                              'label-dispatch)
                             ((not (=f pc next-op-code-address))
                              (lfsi-label pc))
                             (t
                              nil)))
             (forwards-branch (and (fixnump pc)
                                   (>f pc next-op-code-address))))
        (unless (eq go-label 'label-dispatch)
          (record-possible-next-op-code env pc))
        (cond
          ((eq go-label 'label-dispatch)
           (setf all-branch-destinations-possible t))
          (go-label
           (setf (managed-svref explicit-branch-destination pc) t)
           (unless forwards-branch
             (setf (managed-svref possible-label-dispatch-destination pc) t))))
        (let* ((forms
                 (if (and (consp expression) (eq (car expression) 'progn))
                     (cdr expression)
                     (lfsi-list expression)))
               (go-form
                 (cond
                   (forwards-branch
                    (lfsi-list 'go go-label))
                   (go-label
                    (lfsi-list
                      'if
                      (lfsi-list '>f 'instruction-count-plus-pc
                                 (cond ((eq pc lfsi-unbound-marker)
                                        'stack-program-counter)
                                       (t
                                        pc)))
                      (lfsi-list 'go go-label)
                      (maybe-add-top-of-stack-setq
                        (lfsi-list 'go 'check-timeout) env)))
                   (t nil))))
          (values (if go-form
                      (lfsi-cons 'progn
                                 (nconc forms (lfsi-list go-form)))
                      expression)
                  value
                  t)))))

;;; In the case where there is no go added, returning a does-not-return value
;;; of t is a white lie, because since last-form-p is t, the only use
;;; that will be made of the returned does-not-return value is in deciding
;;; whether to add a go after the form. Since we have already decided not to,
;;; there's no need to decide again.


(defmacro lfsi-pushnew (item list)
  `(progn
     (unless (memq ,item ,list)
       (lfsi-push ,item ,list))
     ,list))

(defmacro lfsi-pushnew-list (newlist list)
  `(dolist (item ,newlist ,list)
     (unless (memq item ,list)
       (lfsi-push item ,list))))



(defun remove-vars (expression unused-vars)
  (if (consp expression)
      (if (memq (car expression) '(let let*))
          (remove-vars-let expression unused-vars)
          (rplacd expression (remove-vars-list (cdr expression) unused-vars)))
      expression))

(defun remove-vars-let (expression unused-vars)
  (let ((bindings nil)
        (last-binding nil)
        (previous-binding-deleted nil))
    (loop for binding-cons on (second expression) do
      (let ((binding (car binding-cons)))
        (if (or (memq binding unused-vars)
                (and (consp binding)
                     (memq (first binding) unused-vars)))
            (when bindings (setf previous-binding-deleted t))
            (progn
              (if bindings
                  (when previous-binding-deleted
                    (rplacd last-binding binding-cons))
                  (setf bindings binding-cons))
              (setf previous-binding-deleted nil)
              (setf last-binding binding-cons)))))
    (when previous-binding-deleted
      (rplacd last-binding nil))
    (if bindings
        (progn
          (rplaca (cdr expression) bindings)
          (rplacd (cdr expression)
                  (remove-vars-list (cddr expression) unused-vars))
          expression)
        (lfsi-cons 'progn (remove-vars-list (cddr expression) unused-vars)))))

(defun remove-vars-list (expressions unused-vars)
  (let ((result nil)
        (last-cons nil)
        (previous-element-deleted nil))
    (loop for expression-cons on expressions do
      (let ((expression (remove-vars (car expression-cons) unused-vars)))
        (rplaca expression-cons expression)
        (if (and (consp expression)
                 (memq (car expression) '(incff decff setf))
                 (memq (second expression) unused-vars)
                 (lfsi-constant-p (third expression)))
            (when result (setf previous-element-deleted t))
            (progn
              (if result
                  (when previous-element-deleted
                    (rplacd last-cons expression-cons))
                  (setf result expression-cons))
              (setf previous-element-deleted nil)
              (setf last-cons expression-cons)
              (when (and (consp expression)
                         (memq (car expression) '(setf incff decff))
                         (memq (second expression) unused-vars))
                (rplaca expression-cons (third expression)))))))
    (when previous-element-deleted
      (rplacd last-cons nil))
    result))

(defmacro merge-into-walk-lists (variables used-variables form-to-walk)
  `(multiple-value-bind (sub-variables sub-used-variables)
       (walk-for-unused-locals ,form-to-walk)
     (setf ,variables (nconc sub-variables ,variables))
     (setf ,used-variables
           (lfsi-pushnew-list sub-used-variables ,used-variables))))

(defun walk-for-unused-locals-list (expressions)
  (let ((variables nil) (used-variables nil))
    (dolist (subexpression expressions)
      (merge-into-walk-lists variables used-variables subexpression))
    (values variables used-variables)))


;;; (probably silent) bug: If the initial binding of an unused variable
;;; has a side-effect, we remove the binding clause, omitting the
;;; side-effect. -alatto, 9/4/98

(defun walk-for-unused-locals (expression)
  (typecase expression
    (symbol (values nil (lfsi-list expression)))
    (cons
     (case (car expression)
       ((setf incff decff)
        (if (and (=f (length expression) 3)
                 (atom (second expression)))
            (walk-for-unused-locals (third expression))
            (walk-for-unused-locals-list (cdr expression))))
       ((let let*)
        (multiple-value-bind (body-variables body-used-variables)
            (walk-for-unused-locals-list (cddr expression))
          (dolist (binding (cadr expression))
            (lfsi-push (if (consp binding) (car binding) binding)
                       body-variables)
            (when (consp binding)
              (merge-into-walk-lists body-variables body-used-variables
                                     (cadr binding))))
          (values body-variables body-used-variables)))
       (t (walk-for-unused-locals-list (cdr expression)))))
    (t (values nil nil))))

(defun remove-unused-local-variables (expression &optional
                                                 (vars-to-eliminate :all))
  (let ((unused-vars nil))
    (multiple-value-bind (variables used-variables)
        (walk-for-unused-locals expression)
      (dolist (var (lfsi-cons 'stack-offset variables))
        (when (and (or (eq vars-to-eliminate :all)
                       (memq var vars-to-eliminate))
                   (not (memq var used-variables)))
          (lfsi-push var unused-vars)))
      (when (consp vars-to-eliminate)
        (dolist (var vars-to-eliminate)
          (when (not (memq var used-variables))
            (lfsi-pushnew var unused-vars))))
      (if unused-vars
          (remove-vars expression unused-vars)
          expression))))

(defun remove-unused-register-sets (expressions)
  (loop with constant-register-setfs = '()
        with setf-registers = '()
        for expression in expressions
        when (and (consp expression)
                  (=f (length expression) 3)
                  (eq (car expression) 'setf)
                  (memq (cadr expression)
                        '(fixnum-register-1 fixnum-register-2
                          float-register-1 float-register-2
                          register-1 register-2 register-3
                          register-4 register-5))
                  (lfsi-side-effect-free-p (caddr expression)))
          do
            (lfsi-push expression constant-register-setfs)
            (unless (memq (cadr expression) setf-registers)
              (lfsi-push (cadr expression) setf-registers))
        finally
          (return
            (loop with unused-registers = '()
                  for register in setf-registers
                  unless (register-is-used-in-expressions
                           register expressions constant-register-setfs)
                    do
                      (lfsi-push register unused-registers)
                  finally
                    (return
                      (loop for expression in expressions
                            when (or (not (consp expression))
                                     (not (eq (car expression) 'setf))
                                     (not (memq (cadr expression)
                                                unused-registers)))
                              collect expression
                                using lfsi-cons))))))

(defun register-is-used-in-expressions (register expressions excluded-expressions)
  (loop for expression in expressions
        thereis (and (not (memq expression excluded-expressions))
                     (find-in-tree-eq expression register))))

(defun-simple find-in-tree-eq (tree thing)
  (cond ((consp tree)
         (or (find-in-tree-eq (car-of-cons tree) thing)
             (find-in-tree-eq (cdr-of-cons tree) thing)))
        (t
         (eq tree thing))))


;;; for debugging only

;;; If a var is mentioned in a quoted context, Chestnut builds a symbol
;;; structure for it. This then guarantees that set will work on it at
;;; runtime.

(defvar vars-settable-at-runtime
  '(always-recompile-on-load recompile-on-next-load
    use-type-info remove-unused-labels inline-timeout-checks
    enable-running-compiled-code-p write-all-byte-code-bodies-for-kb-p
    emit-lisp-p
    cache-stack-and-locals wrap-conservatively))

(defun-for-system-procedure set-var ((what symbol))
  (case what
    (always-recompile-on-load (setq always-recompile-on-load t))
    (recompile-on-next-load (setq recompile-on-next-load t))
    (use-type-info (setq use-type-info t))
    (remove-unused-labels (setq remove-unused-labels t))
    (inline-timeout-checks (setq inline-timeout-checks t))
    (enable-running-compiled-code-p (setq enable-running-compiled-code-p t))
    (write-all-byte-code-bodies-for-kb-p (setq write-all-byte-code-bodies-for-kb-p t))
    #+development(emit-lisp-p (setq emit-lisp-p t))
    (t (set what t)))
  nil)

(defun-for-system-procedure unset-var ((what symbol))
  (case what
    (always-recompile-on-load (setq always-recompile-on-load nil))
    (recompile-on-next-load (setq recompile-on-next-load nil))
    (use-type-info (setq use-type-info nil))
    (remove-unused-labels (setq remove-unused-labels nil))
    (inline-timeout-checks (setq inline-timeout-checks nil))
    (enable-running-compiled-code-p (setq enable-running-compiled-code-p nil))
    (write-all-byte-code-bodies-for-kb-p (setq write-all-byte-code-bodies-for-kb-p nil))
    #+development(emit-lisp-p (setq emit-lisp-p nil))
    (t (set what nil)))
  nil)

;;; This is just here so that if you change stack-kern, you don't need to
;;; remember to recompile g2-final. The real expansions are generated by a
;;; similar call in g2-final, so that all classes are visible at macroexpansion
;;; time, guaranteeing that expand-lookup-slot-reference will do the right
;;; thing.

#+compiled-code-saving-is-initially-enabled
(generate-expanded-instruction-macros t)

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module EVENTS

;;;  Joe Devlin

;;; This module defines common definitions for NTW compiler and
;;; run-time to be used in G2 and NTW.   

(in-package "AB")

;;; The following four parameters should eventually become
;;; constants

(defparameter frame-type-offset 0)
(defparameter frame-previous-offset 1)
(defparameter frame-gesture-offset 2)
(defparameter frame-pc-offset 3)
; (defparameter frame-frame-serial-number 4)
(defparameter frame-header-size 4)

(defparameter normal-frame 0)
(defparameter catch-frame 1)
(defparameter protected-frame 2)

(defparameter no-previous-frame 0)

(defparameter per-call-stack-slop 300)

#+vkp-development
(defvar current-gesture-error-info nil)

(defun gesture-value-runtime-subtype-p (type potential-subtype)
  (type-specification-subtype-in-kb-p potential-subtype type))

(def-structure gesture-thread
  (gesture-thread-stack 0)
  (gesture-thread-sp 0) ; stack-pointer
  (gesture-thread-fp 0) ; frame-pointer
  (gesture-thread-pc 0) ; program-counter
  (gesture-thread-frame-serial-number nil :reclaimer reclaim-frame-serial-number)
  (gesture-thread-function 0) ; routine pointer
  (gesture-thread-environment nil) ; yeah, right
  (gesture-thread-wakeup-function nil) ; name of function to call on thread
  (gesture-thread-wakeup-data nil) ; data for the above
  )

(def-global-property-name gesture-function)

(def-system-variable gesture-source-recording-p EVENTS t)

(def-structure (gesture-function
		 (:reclaimer reclaim-gesture-function-internal))
  (gesture-function-argument-count nil)
  (gesture-function-argument-specs nil)
  (gesture-function-locals-count nil)
  (gesture-function-locals-specs nil)
  (gesture-function-return-count nil)
  (gesture-function-return-specs nil)
  (gesture-function-primitive-p nil)
  (gesture-function-instructions nil)
  (gesture-function-can-wait-p nil)
  (gesture-function-source nil)
  (gesture-function-source-index nil)
  (gesture-function-method-p nil)
  (gesture-function-method-declared-p nil)
  (gesture-function-name nil))


(defmacro gesture-function-primitive-function (x)
  `(gesture-function-instructions ,x))

(defmacro gesture-function-method-table (x)
  `(gesture-function-instructions ,x))

(def-structure (gesture-local
		 (:constructor make-gesture-local
			       (gesture-local-name 
				 gesture-local-index
				 gesture-local-type)))
  (gesture-local-name nil)
  (gesture-local-index nil)
  (gesture-local-type nil))

(defun-simple copy-gesture-local (gesture-local)
  (make-gesture-local
    (gesture-local-name gesture-local)
    (gesture-local-index gesture-local)
    (gesture-local-type gesture-local)))

(defun tw-method-is-congruent-to-declaration-p (method-declaration specific-method)
  (and (=f (gesture-function-argument-count method-declaration)
	   (gesture-function-argument-count specific-method))
       (gesture-locals-match-p
	 (cdr (gesture-function-argument-specs method-declaration))
	 (cdr (gesture-function-argument-specs specific-method)))
       (=f (gesture-function-locals-count method-declaration)
	   (gesture-function-locals-count specific-method))
       (gesture-locals-match-p
	 (cdr (gesture-function-locals-specs method-declaration))
	 (cdr (gesture-function-locals-specs specific-method)))
       (=f (gesture-function-return-count method-declaration)
	   (gesture-function-return-count specific-method))
       (gesture-locals-match-p
	 (cdr (gesture-function-return-specs method-declaration))
	 (cdr (gesture-function-return-specs specific-method)))
       (or (gesture-function-can-wait-p method-declaration)
	   (not (gesture-function-can-wait-p specific-method)))))

(defun gesture-locals-match-p (local-list-1 local-list-2)
  (and (eq (length local-list-1) (length local-list-2))
       (loop for local-1 in local-list-1
	     for local-2 in local-list-2
	     always
	     (and (equal (gesture-local-type local-1)
			 (gesture-local-type local-2))
		  (=f (gesture-local-index local-1)
		      (gesture-local-index local-2))))))

(defun reclaim-gesture-function (gesture-function)
  (loop for local-spec
	    in (gesture-function-argument-specs gesture-function)
	do
    (reclaim-gesture-local local-spec))
  (loop for local-spec
	    in (gesture-function-locals-specs gesture-function)
	do
    (reclaim-gesture-local local-spec))
  (loop for local-spec
	    in (gesture-function-return-specs gesture-function)
	do
    (reclaim-gesture-local local-spec))
  (when (gesture-function-method-p gesture-function)
    (loop for (name gesture-method)
	  on (gesture-function-method-table gesture-function)
	      by 'cddr
	  do
      (reclaim-gesture-function gesture-method))
    (reclaim-gensym-list (gesture-function-method-table gesture-function)))
  (reclaim-managed-simple-vector
    (gesture-function-instructions gesture-function))
  (reclaim-gesture-function-internal gesture-function))

#+development
(defun make-gesture-variable-spec (spec-list)
  (loop with res = '()
	for (name index type) in spec-list
	as local = (make-gesture-local name index type)
	do
    (gensym-push local res)
	finally
	  (return (nreverse res))))
		  

;;;; Gesture Debugging

(defvar-for-development tracing-in-events-modules-p nil)

(defmacro print-when-tracing-in-events-modules (&rest args)
  (if (eval-feature :development)
      `(when tracing-in-events-modules-p (print ,@args))
      nil))

(defmacro pprint-when-tracing-in-events-modules (&rest args)
  (if (eval-feature :development)
      `(when tracing-in-events-modules-p (pprint ,@args))
      nil))
  
(defmacro format-when-tracing-in-events-modules (&rest args)
  (if (eval-feature :development)
      `(when tracing-in-events-modules-p (format t ,@args))
      nil))

;;;; Gesture Run-Time

(defvar tw-evaluate-trace-level 0)
(defvar tw-source-debug-p t)

(defvar gesture-unbound-value '(unbound))

(def-global-property-name gesture-instruction)
(defvar all-gesture-instruction-names nil)

(defun-for-macro register-usage-spec-p (register-usage-spec)
  (declare (ignore register-usage-spec))
  t) ; eventually get real on this

(defmacro define-gesture-instruction
    ((name number) register-usage-spec &body body)
  (unless (register-usage-spec-p register-usage-spec)
    (error "bad register spec"))
  `(progn (setf (gesture-instruction ',name)
		(list ',register-usage-spec ,number ',body))
	  (pushnew ',name all-gesture-instruction-names)))


;;; Abstraction of register and stack access

(defmacro gesture-pc ()
  `gesture-pc)

(defmacro gesture-constant (n)
  `(nth ,n (cdr-of-cons gesture-instruction)))

(defmacro gesture-fp ()
  `gesture-fp)

(defmacro gesture-sp ()
  `gesture-sp)

(defmacro gesture-func ()
  `gesture-function)

(defmacro gesture-instruction-vector ()
  `gesture-instruction-vector)

(defmacro gesture-stack-size ()
  `gesture-stack-size)

(defmacro gesture-thread ()
  `gesture-thread)

(defmacro gesture-error-name ()
  `gesture-error-name)

(defmacro gesture-error-information ()
  `gesture-error-information)

(defmacro gesture-stack-ref (index)
  `(svref gesture-stack ,index))

(defmacro gesture-pop ()
  `(svref gesture-stack (decff gesture-sp)))

(defmacro gesture-push (thing)
  `(let ((thing-value ,thing))
     (setf (svref gesture-stack gesture-sp)
	   thing-value)
     (incff gesture-sp)))

;;; The following globals contain enough state
;;; to make error printing and thread verification possible

(defvar current-gesture-stack-pointer nil)
(defvar current-gesture-frame-pointer nil)


(defmacro gesture-evaluation-error (name &body error-keys-and-values)
  `(progn
     (format t "Gesture Evaluation Error: ~s~%" ,name)
     (let ((thread (gesture-thread)))
       (setf (gesture-thread-fp thread) (gesture-fp))
       (setf (gesture-thread-sp thread) (gesture-sp))
       (setf (gesture-thread-function thread) (gesture-func))
       (setf (gesture-thread-pc thread) (gesture-pc))
       (pprint-gesture-thread thread))
     (setf (gesture-error-name) ,name)
     (setf (gesture-error-information)
	   (gensym-list ,@error-keys-and-values))
     (go gesture-thread-error)))

(define-gesture-instruction (branch-if-false 0)
    ()
  (when (eq (gesture-pop) evaluation-false-value)
    (incff (gesture-pc) (gesture-constant 0))))

(define-gesture-instruction (branch-always 1)
    ()
  (incff (gesture-pc) (gesture-constant 0)))
 
(define-gesture-instruction (branch-if-true 2)
    ()
  (unless (eq (gesture-pop) evaluation-false-value)
    (incff (gesture-pc) (gesture-constant 0))))

(define-gesture-instruction (set-local 3)
    ((value register-1))
  (setq value (gesture-pop))
  (setf (gesture-stack-ref (+f (gesture-fp)
			       (gesture-constant 0)))
	value))

(define-gesture-instruction (get-local 4)
    ((value register-1))
;  (let ((index (+f (gesture-fp)
;		   (gesture-constant 0))))
 ;   (format t "I'm going for stack val at ~s~%" index))
  (setq value (gesture-stack-ref (+f (gesture-fp)
				     (gesture-constant 0))))
  (when (eq value gesture-unbound-value)
    (gesture-evaluation-error
      'unbound-local-variable
      'local-variable (get-gesture-local-by-index
			(gesture-func) (gesture-constant 0))))
  (unless value
    (gesture-evaluation-error
      'does-not-exist
      'local-variable (get-gesture-local-by-index
			(gesture-func) (gesture-constant 0))))
  (gesture-push (copy-if-evaluation-value value)))

(defun get-gesture-local-by-index (gesture-function index)
  (or (loop for local in (gesture-function-locals-specs gesture-function)
	    do
	(when (=f (gesture-local-index local) index)
	  (return local)))
      (loop for local in (gesture-function-argument-specs gesture-function)
	    do
	(when (=f (gesture-local-index local) index)
	  (return local)))))
      
;;; The Following is the structure of gesture evaluation
;;; stack frames:
;;;
;;; CALL_PROC
;;; CALL_NARGS
;;; CALL_ARGk
;;; CALL_ARG0
;;; <stack-frame-stuff, incl. prev-frame, prev-pc, function-ptr, frame-header
;;;  LOCAL_M
;;;  LOCAL_0
;;; FRAME
;;; ARG_N
;;; ARG_OFFSET
;;; ...<frames of calling procedures>


;; todo
;; 3. tw invert sense of system attribute access, i.e. open unless banned.


(defmacro check-gesture-argument (argument-spec argument-value)
  `(type-specification-type-p
     ,argument-value
     (gesture-local-type ,argument-spec)))

(define-gesture-instruction (check-args 5)
    ((routine register-1)
     (argument-count register-2))
  ;; crawl the args checking against
  ;; gesture-function's type spec
  (setf routine (gesture-stack-ref (-f (gesture-sp) 1)))
  (setf argument-count (gesture-stack-ref (-f (gesture-sp) 2)))
  (when (gesture-function-method-p routine)
    (setf routine
	  (compute-effective-gesture-method
	    routine
	    (gesture-stack-ref (-f (gesture-sp)
				   (+f 2 argument-count)))
	    nil))
    (unless routine (gesture-evaluation-error 'no-effective-method)))
;  (format t "check-args passed-argcount=~s req=~s~%"
;	  argument-count
;	  (gesture-function-argument-count routine))
  (unless (=f argument-count
	      (gesture-function-argument-count routine))
    (gesture-evaluation-error
      'argument-count-mismatch
      'expected-number-of-args (gesture-function-argument-count routine)))
  (loop for arg-index from (-f (gesture-sp) (+f argument-count 2))
		      to (-f (gesture-sp) 3)
	as argument-value = (gesture-stack-ref arg-index)
	as arg-spec in (gesture-function-argument-specs routine)
	as argument-index from 0
	do
    (tw-trace 2 "arg-type =~s value=~s~%"
	      (gesture-local-type arg-spec) argument-value)
    (unless (check-gesture-argument arg-spec argument-value)
      #+vkp-development
      (setf current-gesture-error-info
	    (tformat-text-string "Arg#~d (~a) was passed a value ~a, which does not conform to the type specification ~a."
				 argument-index
				 (gesture-local-name arg-spec)
				 argument-value
				 (gesture-local-type arg-spec)))
      (gesture-evaluation-error
	'argument-type-mismatch
	'argument-name (gesture-local-name arg-spec)
	'argument-type (tformat-text-string "~NT"
					    (gesture-local-type arg-spec))))))

(define-gesture-instruction (procedure-call 6)
    ((procedure register-1)
     (new-stack-ptr register-2)
     (arg-count register-3))
  ;; this is the statement call that returns mult values
  ;; into an assignment
  (setf procedure (gesture-pop))
  (setf arg-count (gesture-pop)) ; the arg-count
  (when (gesture-function-method-p procedure)
    (setf procedure
	  (compute-effective-gesture-method
	    procedure
	    (gesture-stack-ref (-f (gesture-sp) arg-count))
	    nil))
    (unless procedure
      (gesture-evaluation-error
	'no-effective-method
	'method-name (gesture-function-name procedure)
	'item-class (class (gesture-stack-ref (-f (gesture-sp) arg-count))))))
  (cond
    ((gesture-function-primitive-p procedure)
     (setf current-gesture-stack-pointer (gesture-sp))
     (setf current-gesture-frame-pointer (gesture-fp))
     (frame-serial-number-setf (gesture-thread-frame-serial-number (gesture-thread))
	   (current-frame-serial-number))
     (let* ((current-gesture-thread (gesture-thread))
	    (return-list (call-primitive-gesture
			   (gesture-function-primitive-function procedure)
			   arg-count
			   (nreverse
			     (loop for i from 0 below arg-count
				   collect (gesture-pop)
				     using gensym-cons)))))
       (cond
	 ((gesture-function-can-wait-p procedure)
	  (setf (gesture-thread-sp (gesture-thread)) (gesture-sp))
	  (setf (gesture-thread-fp (gesture-thread)) (gesture-fp))
	  (setf (gesture-thread-pc (gesture-thread))
		(1+f (gesture-pc)))
	  (setf (gesture-thread-function (gesture-thread)) (gesture-func))
	  (go gesture-thread-pause))
 	 (t
	  (loop for return-value in return-list
		do
	    (gesture-push return-value))
	  (gesture-push (length return-list))))))
    ((remote-procedure-definition-p
       (gesture-function-primitive-function procedure))
     (gesture-evaluation-error 'procedure-is-remote
			       'procedure-name (gesture-function-name procedure)))
    (t
     (setf new-stack-ptr (+f (gesture-sp)
			     (gesture-function-locals-count procedure)
			     frame-header-size))
     (when (>f (+f new-stack-ptr per-call-stack-slop)
	       (gesture-stack-size))
       (gesture-evaluation-error 'stack-overflow))
     
     ;; set the pc into the current frame
     (setf (gesture-stack-ref (+f (gesture-fp) frame-pc-offset)) (gesture-pc))
     ;; build the frame
     
     (setf (gesture-stack-ref (+f (gesture-sp) frame-type-offset)) normal-frame)
     (setf (gesture-stack-ref (+f (gesture-sp) frame-previous-offset)) (gesture-fp))
     (setf (gesture-stack-ref (+f (gesture-sp) frame-gesture-offset)) procedure)
     (setf (gesture-stack-ref (+f (gesture-sp) frame-pc-offset)) 1234567)
     ;; push all locals with unbound-marker
     (loop with start = (+f (gesture-sp) frame-header-size)
	   for i from start below (+f start
				      (gesture-function-locals-count procedure))
	   do
       (setf (gesture-stack-ref i) gesture-unbound-value))
     (setf (gesture-fp) (gesture-sp))
     (setf (gesture-func) procedure)
     (setf (gesture-instruction-vector) (gesture-function-instructions procedure))
     (setf (gesture-sp) new-stack-ptr)
     (setf (gesture-pc) -1))))

(defvar secret-return-value '(secret-return-value))

(defmacro argument-count-based-funcall-dispatch
    (function arg-list arg-count max-args)
  (let ((returned-value (gensym)))
    `(let ((argument-list ,arg-list)
	   (,returned-value secret-return-value))
       (fixnum-case ,arg-count
	 ,@(loop for i from 0 below (eval max-args)
		 collect
		 `(,i (setq ,returned-value
			    (funcall
			      ,function
			      ,@(loop for arg-number from 0 below i
				      collect
				      `(prog1 (car-of-cons argument-list)
					 (setf argument-list
					       (cdr-of-cons argument-list)))))))))
       (when (eq ,returned-value secret-return-value)
	 (error "too many args to call-primitive-gesture"))
       ,returned-value)))

(defun call-primitive-gesture (gesture-function arg-count arg-list)
  (when (>f tw-evaluate-trace-level 1)
    (format t "in call prim argc =~s argl=~s ~%"
	    arg-count arg-list)
    (force-output t))
  (prog1 (let ((ret-val-list
		 (argument-count-based-funcall-dispatch 
		   gesture-function arg-list arg-count 18)))
	   (when (>f tw-evaluate-trace-level 2)
	     (format t "call prim gesture ret=~s~%" ret-val-list)
	     (force-output t))
	   (nreverse ret-val-list))
    (reclaim-gensym-list arg-list)))

(define-gesture-instruction (function-call 7)
    ()
  ;; this is the statement call that returns mult values
  ;; into an assignment
  )

(define-gesture-instruction (procedure-start 8)
    ((routine register-1)
     (argument-count register-2)
     (argument-list register-3))
  ;; crawl the args checking against
  ;; gesture-function's type spec
  (setf routine (gesture-stack-ref (-f (gesture-sp) 1)))
  (setf argument-count (gesture-stack-ref (-f (gesture-sp) 2)))
  ;; pop values into arglist
  ;; post-some event to resume the stack
  )

(define-gesture-instruction (call-in-g2 9)
    ((procedure register-1)
     (arg-count register-2))
  ;; this is the statement call that returns mult values
  ;; into an assignment
  (setf procedure (gesture-pop))
  (setf arg-count (gesture-pop)) 
  (format t "in call in g2 before much of anything~%")
  (force-output t)
  (let* ((current-gesture-thread (gesture-thread))
	 (arglist
	   (nreverse
	     (loop for i from 0 below arg-count
		   collect (gesture-pop)
		     using gensym-cons))))
    (format t "in call in g2 before prim call~%")
    (force-output t)
    (cond ((gesture-function-primitive-p procedure)
	   (call-primitive-gesture
	     (tw-rpc-call-name
	       (gesture-function-primitive-function procedure))
	     (1+f arg-count)
	     (gensym-cons (gesture-thread) arglist)))
	  ((not (remote-procedure-definition-p
		  (gesture-function-primitive-function procedure)))
	   (gesture-evaluation-error
	     'not-an-rpc
	     'procedure-name (gesture-function-name procedure)))
	  (t
	   (tw-call-rpc
	     (gesture-function-primitive-function procedure)
	     (gesture-thread)
	     arglist)))
    (setf (gesture-thread-sp (gesture-thread)) (gesture-sp))
    (setf (gesture-thread-fp (gesture-thread)) (gesture-fp))
    (setf (gesture-thread-pc (gesture-thread))
	  (1+f (gesture-pc)))
    (setf (gesture-thread-function (gesture-thread)) (gesture-func))
    (go gesture-thread-pause)))

(define-gesture-instruction (start-in-g2 10)
    ((procedure register-1)
     (arg-count register-2))
  ;; this is the statement call that returns mult values
  ;; into an assignment
  (setf procedure (gesture-pop))
  (setf arg-count (gesture-pop)) 
  (format t "in start in g2 before much of anything~%")
  (force-output t)
  (let* ((current-gesture-thread (gesture-thread))
	 (arglist
	   (nreverse
	     (loop for i from 0 below arg-count
		   collect (gesture-pop)
		     using gensym-cons))))
    (format t "in start in g2 before prim call~%")
    (force-output t)
    (cond ((gesture-function-primitive-p procedure)
	   #+development
	   (cerror "go on"
		   "I have no idea about starting primitive procs")
	   (call-primitive-gesture
	     (tw-rpc-start-name
	       (gesture-function-primitive-function procedure))
	     arg-count
	     arglist))
	  (t
	   (tw-start-rpc
	     (gesture-function-primitive-function procedure)
	     arglist)))
    (setf (gesture-thread-sp (gesture-thread)) (gesture-sp))
    (setf (gesture-thread-fp (gesture-thread)) (gesture-fp))
    (setf (gesture-thread-pc (gesture-thread))
	  (1+f (gesture-pc)))
    (setf (gesture-thread-function (gesture-thread)) (gesture-func))
    (go gesture-thread-pause)))

(define-gesture-instruction (procedure-return 11)
    ((previous-frame register-1)
     (return-count register-2)
     (routine register-3))
  (setf previous-frame
	(gesture-stack-ref (+f (gesture-fp) frame-previous-offset)))
  (setf return-count (gesture-pop))
  (setf routine
	(gesture-stack-ref (+f (gesture-fp) frame-gesture-offset)))
  (loop for i from (-f (gesture-fp)
		       (gesture-function-argument-count routine))
	      below (-f (gesture-sp) return-count)
	do
    (unless (gesture-function-p (gesture-stack-ref i))
      (reclaim-if-evaluation-value (gesture-stack-ref i))))
  (loop with target-start = (-f (gesture-fp)
				(gesture-function-argument-count routine))
        for source-index from (-f (gesture-sp) return-count)
			 below (gesture-sp)
	for target-index from target-start 
			 below (+f target-start return-count)
	do
    (setf (gesture-stack-ref target-index)
	  (gesture-stack-ref source-index))
	finally
	  (setf (gesture-sp) (+f target-start return-count)))
  (gesture-push return-count)
  ;; resume lower frame or got to thread end
  (cond
    ((eq previous-frame no-previous-frame)
     ;; uh, um, do something
     (go gesture-thread-done))
    (t
     ;; resume lower frame
     (setf (gesture-fp) previous-frame)
     (setf (gesture-func)
	   (gesture-stack-ref (+f previous-frame frame-gesture-offset)))
     (setf (gesture-instruction-vector)
	   (gesture-function-instructions (gesture-func)))
     (setf (gesture-pc)
	   (gesture-stack-ref (+f previous-frame frame-pc-offset)))
     ))
  )

(define-gesture-instruction (set-local-from-return 17)
    ((value register-1))
  (setq value (gesture-pop))
  ;; doesn't set use of return value in this case --
  ;; it's use-count is already at n+1 from procedure returning mechanism
  (setf (gesture-stack-ref (+f (gesture-fp)
			       (gesture-constant 0)))
	value))

(define-gesture-instruction (return-check 18)
    ((return-count register-1)
     (desired-return-count register-2)
     (temp register-3))
  (setf return-count (gesture-pop))
  (setf desired-return-count (gesture-constant 0))
  (cond
    ((<f return-count desired-return-count)
     (gesture-evaluation-error
       'unsufficient-number-of-return-values
       'number-desired desired-return-count
       'number-received return-count))
    ((>f return-count desired-return-count)
     ;; this little bit reclaims unused return values
     ;; and attempts to leave the stack in a nice state
     (setf temp nil)
     (loop for i from 0 below return-count
	   do
       (cond
	 ((<f i desired-return-count)
	  (gensym-push (gesture-pop) temp))
	 (t
	  (reclaim-if-evaluation-value (gesture-pop)))))
     (loop for i from 0 below desired-return-count
	   do
       (gesture-push (gensym-pop temp))))))

(define-gesture-instruction (function-return 12)
    ()
  ;; just put some value on the stack
  ;; don't worry about cleanup (maybe)
  ;; or thread exit (definitely)
  )

(define-gesture-instruction (push-next-method 13)
    ((method register-1)
     (next-method register-2))
  (setf method (gesture-function (gesture-constant 0)))
  (when (or (null method)
	    (and (gesture-function-method-p method)
		 (not (gesture-function-method-p method))))
    #+development
    (cerror "go on" "Call next method should have a valid method-decl")
    (gesture-evaluation-error
      'undefined-method
      'method-name (gesture-function-name method)))
  (setf next-method
	(compute-effective-gesture-method
	  method
	  (gesture-stack-ref (-f (gesture-fp)
				 (gesture-function-argument-count
				   (gesture-func))))
	  t))
  (unless next-method
    (gesture-evaluation-error
      'no-next-method
      'method-name (gesture-function-name method)))
  (gesture-push next-method))

(defun-simple compute-effective-gesture-method
    (gesture-method-declaration frame next-p)
  (compute-effective-gesture-method-of-class-description
    gesture-method-declaration
    (class-description-slot frame)
    next-p))

(defun-simple compute-effective-gesture-method-of-class-description
    (gesture-method-declaration class-description next-p)
  (let ((inheritance-path (class-inheritance-path class-description)))
    (when next-p
      (setf inheritance-path (cdr inheritance-path)))
    (loop with method-table
	    = (gesture-function-method-table gesture-method-declaration)
          for class in inheritance-path
	  as method? = (getf method-table class)
	  when method?
	    return method?)))

(define-gesture-instruction (exists 14)
    ()
  (if (gesture-pop)
      (gesture-push evaluation-true-value)
      (gesture-push evaluation-false-value)))

(define-gesture-instruction (push-gesture-def 15)
    ((routine register-1))
  (setf routine (gesture-function (gesture-constant 0)))
  (when (or (null routine)
	    (and (gesture-function-method-p routine)
		 (not (gesture-function-method-p routine))))
    (gesture-evaluation-error
      'undefined-procedure-or-method
      'name (gesture-constant 0)))
  (gesture-push routine))

(define-gesture-instruction (samep 16)
    ()
  (gesture-push
    (if (eq (gesture-pop)
	    (gesture-pop))
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (get-local-or-no-item 19)
    ((value register-1))
  (setq value (gesture-stack-ref (+f (gesture-fp)
				     (gesture-constant 0))))
  (when (eq value gesture-unbound-value)
    (setq value nil))
  (gesture-push value))


(define-gesture-instruction (add-fixnum 20)
    ()
  (gesture-push
    (+f (gesture-pop) (gesture-pop))))

(define-gesture-instruction (subtract-fixnum 21)
    ()
  (gesture-push
    (-f (gesture-pop) (gesture-pop))))

(define-gesture-instruction (multiply-fixnum 22)
    ()
  (gesture-push
    (*f (gesture-pop) (gesture-pop))))

(define-gesture-instruction (equal-fixnum 23)
    ()
  (gesture-push
    (if (=f (gesture-pop) (gesture-pop))
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (push-fixnum 24)
    ()
;  (format t "pre pushfix sp=~s~%" (gesture-sp))
  (gesture-push
    (gesture-constant 0)))
;  (format t "pre pushfix sp=~s~%" (gesture-sp)))


(define-gesture-instruction (increment 25)
    ()
  (gesture-push
    (incff (gesture-pop))))

(define-gesture-instruction (decrement 26)
    ()
  (gesture-push
    (decff (gesture-pop))))

(define-gesture-instruction (negate-fixnum 27)
    ()
  (gesture-push
    (-f (gesture-pop))))

(define-gesture-instruction (greater-than-fixnum 28)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (>f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))


(define-gesture-instruction (less-than-fixnum 29)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (<f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))


(define-gesture-instruction (greater-than-equal-fixnum 30)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (>=f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))


(define-gesture-instruction (less-than-equal-fixnum 31)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (<=f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (quotient-fixnum 32)
    ((dividend register-1)
     (divisor register-2))
  (setf divisor (gesture-pop))
  (setf dividend (gesture-pop))
  (gesture-push
    (truncatef-first dividend divisor)))


(define-gesture-instruction (remainder-fixnum 33)
    ((dividend register-1)
     (divisor register-2))
  (setf divisor (gesture-pop))
  (setf dividend (gesture-pop))
  (gesture-push
    (rem-fixnums dividend divisor)))

(define-gesture-instruction (divide-fixnum 34)
    ((dividend register-1)
     (divisor register-2))
  (setf divisor (gesture-pop))
  (setf dividend (gesture-pop))
  (gesture-push
    (rem-fixnums dividend divisor)))



(define-gesture-instruction (add-quantity 40)
    ()
  (gesture-push
    (+f (gesture-pop) (gesture-pop))))

(define-gesture-instruction (subtract-quantity 41)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (-f first-arg second-arg)))

(define-gesture-instruction (multiply-quantity 42)
    ()
  (gesture-push
    (*f (gesture-pop) (gesture-pop))))

(define-gesture-instruction (equal-quantity 43)
    ()
  (gesture-push
    (if (=f (gesture-pop) (gesture-pop))
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (push-quantity 44)
    ()
  (format t "pre pushfix sp=~s~%" (gesture-sp))
  (gesture-push
    (gesture-constant 0))
  (format t "pre pushfix sp=~s~%" (gesture-sp)))

(define-gesture-instruction (negate-quantity 47)
    ()
  (gesture-push
    (-f (gesture-pop))))

(define-gesture-instruction (greater-than-quantity 48)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (>f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))


(define-gesture-instruction (less-than-quantity 49)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (<f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (greater-than-equal-quantity 50)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (>=f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (less-than-equal-quantity 51)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (<=f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (quotient-quantity 52)
    ((dividend register-1)
     (divisor register-2))
  (setf divisor (gesture-pop))
  (setf dividend (gesture-pop))
  (gesture-push
    (truncatef-first dividend divisor)))


(define-gesture-instruction (remainder-quantity 53)
    ((dividend register-1)
     (divisor register-2))
  (setf divisor (gesture-pop))
  (setf dividend (gesture-pop))
  (gesture-push
    (rem-fixnums dividend divisor)))


(def-substitution-macro tw-serve-item-p (item)
  (and (frame-of-class-p item 'item)
       t))
;       (or (active-p item)
;	   role-serve-inactive-objects?
;	   (frame-of-class-p item 'kb-workspace)

(defun-simple tw-put-attribute-description-value
    (frame slot-description new-attribute-value initializing?)
  (let* ((old-attribute-value
	   (get-slot-description-value frame slot-description))
	 (new-value-is-frame-p (framep new-attribute-value)))
    (unless initializing?
      (when (framep old-attribute-value)
	(error "we should not be in the sub-frame case")))

    (set-slot-description-value frame slot-description new-attribute-value)

    (when new-value-is-frame-p
      (set-parent-information
	new-attribute-value
	frame
	(pretty-slot-name slot-description)
	(if (slot-name-needs-qualification-p
	      slot-description (class-description-slot frame))
	    (defining-class slot-description))))
    
    ;; the sub-frame case is being disallowed currently
;    (when new-value-is-frame-p
;      (cerror "go on"
;	      "sub frame error should have been caught by outer check"))
    (when (and (not initializing?) old-attribute-value)
      (unless (eq old-attribute-value (slot-init-form slot-description))
	(reclaim-slot-value old-attribute-value)))
    
    new-attribute-value))


(defun tw-change-slot-description-value
    (frame slot-description new-value
	   pretty-slot-name defining-class)
  (declare (ignore pretty-slot-name defining-class))
  (let* (old-value
	 (do-not-reclaim-old-value? nil)
	 (slot-putter?
	   (get-slot-description-putter-if-any slot-description))
	 (return-value
	   (cond
	     ((eq slot-putter? 'put-attribute-value)
	      ;; Put-attribute-value reclaims slot values, so we always
	      ;; set do-not-reclaim-old-value? to true, and we don't need
	      ;; to set old-value, since it won't be looked at.
	      (setq do-not-reclaim-old-value? t)
	      (tw-put-attribute-description-value
		frame slot-description new-value nil))
	     (t
	      (setq old-value
		    (get-slot-description-value-macro frame slot-description))
	      (cond
		(slot-putter?
		 
		 (multiple-value-setq-some (nil do-not-reclaim-old-value?)
		     (funcall-simple-multi-valued-compiled-function 
		       slot-putter? frame new-value nil)))
		(t
		 (set-slot-description-value
		   frame slot-description new-value)))))))
    (when (and (not do-not-reclaim-old-value?)
	       old-value
	       (not (eq new-value old-value))
	       (not (fixnump old-value))
	       (not (eq old-value
			(slot-init-form slot-description))))
      (reclaim-slot-value old-value))
    return-value)) 

(defparameter tw-predefined-user-attributes nil)

(define-gesture-instruction (set-slot 60)
    ((frame register-1)
     (new-value register-2)
     (attribute-name register-3))
  (setf frame (gesture-pop))
  (setf new-value (gesture-pop))
  (setf attribute-name (gesture-constant 0))
  (let* ((class-qualifier? nil) ; eventually add something to instr args
	 (class-description (class-description-slot frame))
	 (slot-description?
	   (get-slot-description-of-class-description
	     attribute-name class-description class-qualifier?))
	 (visible-slot?
	   (and slot-description?
		(feature-assq-macro 'type (slot-features slot-description?))
		(not (do-not-put-slot-in-attribute-tables-p
			 slot-description? t))))
	 (slot-value?
	   (if visible-slot?
	       (get-slot-description-value frame slot-description?)
	       nil))
	 (slot-value-class-description? (framep slot-value?)))
    (cond
      ((framep new-value)
       (gesture-evaluation-error
	 'sub-items-not-yet-supported))
      (slot-value-class-description?
       (gesture-evaluation-error
	 'illegal-conclude-for-tw))
      ;; Need non-frame slot value case.
      ((null visible-slot?)
       (gesture-evaluation-error
	 'unknown-attribute-reference))
      ((or (not (user-defined-slot-description-p slot-description?))
	   (assq-macro attribute-name tw-predefined-user-attributes))
       ;; Added a test to disallow concluding of predefined user attributes.
       ;; These are really system slots which are visible from expressions.

       ;; We should review the various abstractions related to system and user
       ;; attributes.  For example, should the predefined attributes be in the
       ;; authorized-system-slots list also?  - cpm, 4/24/92
       (gesture-evaluation-error
	 'attempt-to-conclude-to-inaccessibe-system-slot
	 ;; attribute-name class-qualifer frame
	 ))
      (t
       (let ((slot-type-specification
	       (slot-type-specification slot-description?)))
	 (cond
	   ((type-specification-type-p new-value slot-type-specification)
	    (cond ((evaluation-truth-value-p new-value)
		   (tw-change-slot-description-value
		     frame slot-description?
		     (slot-value-list
		       (evaluation-truth-value-value new-value)
		       'truth-value)
		     attribute-name class-qualifier?)
		   (reclaim-evaluation-truth-value new-value))
		  (t
		   (tw-change-slot-description-value
		     frame slot-description? new-value
		     attribute-name class-qualifier?))))
	   ((and (evaluation-integer-p new-value)
		 (eq slot-type-specification 'float))
	    (let ((float-value (make-evaluation-float
				 (coerce-fixnum-to-gensym-float
				   (evaluation-integer-value new-value)))))
	      (reclaim-evaluation-integer new-value)
	      (tw-change-slot-description-value
		frame slot-description? float-value
		attribute-name class-qualifier?)))
	   (t
	    (gesture-evaluation-error
	      'attribute-type-mismatch
	      ;; new-value
	      ;; slot-description? (class-description-slot item)
	      ;; item
	      ;; slot-type-specification))))))
	      ))))))))


(define-gesture-instruction (get-slot 61)
    ((frame-or-structure register-1)
     (attribute-name register-2)
     (allow-no-item-p register-3))
  (setf frame-or-structure (gesture-pop))
  (setf attribute-name (gesture-constant 0))
  (setf allow-no-item-p (gesture-constant 0))
  (cond
    ((and (null frame-or-structure)
	  allow-no-item-p)
     (gesture-push nil))
    ((evaluation-structure-p frame-or-structure)
     (let* ((structure frame-or-structure) ; just for readability
	    (value
	      (evaluation-structure-slot structure attribute-name)))
       (cond
	 (value
	  (gesture-push (copy-if-evaluation-value value)))
	 (allow-no-item-p
	  (gesture-push nil))
	 (t
	  (gesture-evaluation-error
	    'unknown-structure-attribute-reference)))))
    (t
     (let* ((frame frame-or-structure) ; just for readability
	    (class-qualifier? nil) ; eventually add something to instr args
	    (class-description (class-description-slot frame))
	    (slot-description?
	      (get-slot-description-of-class-description
		attribute-name class-description class-qualifier?))
	    (visible-slot?
	      (and slot-description?
		   (feature-assq-macro 'type (slot-features slot-description?))
		   (not (do-not-put-slot-in-attribute-tables-p
			    slot-description? t))))
	    (slot-value?
	      (if visible-slot?
		  (get-slot-description-value frame slot-description?)
		  nil)))
;	    (slot-value-class-description?
;	      (framep slot-value?)))
       (cond
;	 (slot-value-class-description?
;	  (gesture-evaluation-error
;	    'illegal-conclude-for-tw))
	 ;; Need non-frame slot value case.
	 ((and (null visible-slot?)
	       (not allow-no-item-p)) ; implements allow no-item
	  (gesture-evaluation-error
	    'unknown-attribute-reference))
	 ((slot-constantp slot-value?)
	  (gesture-push
	    (cast-slot-constant-into-evaluation-value slot-value?)))
	 (t
	  (gesture-push
	    (copy-if-evaluation-value slot-value?))))))))


(define-gesture-instruction (value2symbol 62)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((and value (symbolp value))
	 (gesture-push value))
	(t
	 (gesture-evaluation-error
	   'value-not-of-type-symbol
	   'the-value value))))

(define-gesture-instruction (value2float 63)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((managed-float-p value)
	 (gesture-push value))
	(t
	 (gesture-evaluation-error
	   'value-not-of-type-float
	   'the-value value))))

(define-gesture-instruction (value2quantity 64)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((or (managed-float-p value)
	     (fixnump value))
	 (gesture-push value))
	(t
	 (gesture-evaluation-error
	   'value-not-of-type-quantity
	   'the-value value))))

(define-gesture-instruction (value2integer 65)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((fixnump value)
	 (gesture-push value))
	(t
	 (gesture-evaluation-error
	   'value-not-of-type-integer
	   'the-value value))))

(define-gesture-instruction (value2text 66)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((text-string-p value)
	 (gesture-push value))
	(t
	 (gesture-evaluation-error
	   'value-not-of-type-text
	   'the-value value))))

(define-gesture-instruction (value2truth-value 67)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((or (eq value evaluation-true-value)
	     (eq value evaluation-false-value))
	 (gesture-push value))
	(t
	 (gesture-evaluation-error
	   'value-not-of-type-truth-value
	   'the-value value))))

(define-gesture-instruction (value2frame 68)
    ((value register-1)
     (target-class register-2))
  (setf value (gesture-pop))
  (setf target-class (gesture-constant 0))
  (cond ((framep value)
	 (cond ((frame-of-class-p value target-class)
		(gesture-push value))
	       (t
		(gesture-evaluation-error
		  'not-an-instance-of-class
		  'item-class (class value)
		  'desired-class (gesture-constant 0)))))
	(t
	 (gesture-evaluation-error
	   'not-tw-item
	   'the-value value))))

(define-gesture-instruction (value2datum 69)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((framep value)
	 (gesture-evaluation-error
	   'not-a-value
	   'thing-that-is-not-a-value value))
	(value
	 (gesture-push value))
	(t
	 (gesture-evaluation-error 'value-does-not-exist))))

(define-gesture-instruction (push-truth-value 70)
    ()
  (gesture-push
    (cond
      ((eq (gesture-constant 0) 'true)
       evaluation-true-value)
      (t
       evaluation-false-value))))

(define-gesture-instruction (invert-truth-value 71)
    ()
  (gesture-push
    (cond ((eq evaluation-true-value (gesture-pop))
	   evaluation-false-value)
	  (t
	   evaluation-true-value))))

(define-gesture-instruction (push-symbol 80)
    ()
  (gesture-push (gesture-constant 0)))

(define-gesture-instruction (equal-symbol 81)
    ()
  (gesture-push
    (if (eq (gesture-pop) (gesture-pop))
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (push-text 90)
    ()
  (gesture-push
    (copy-evaluation-text (gesture-constant 0))))

(define-gesture-instruction (equal-text 91)
    ()
  (gesture-push
    (if (string-equalw (gesture-pop) (gesture-pop))
	evaluation-true-value
	evaluation-false-value)))

;;; Decade 100 Random Expressions



(define-gesture-instruction (tw-format-form 100)
    ((arg-count register-1)
     (new-text-string register-2))
  (setf arg-count (gesture-pop)) ; the arg-count
  (setf new-text-string
	(twith-output-to-text-string
	  (loop for i from 0 below arg-count
		as thing = (gesture-pop)
		do
	    (when (framep thing)
	      (gesture-evaluation-error
		'cannot-get-text-of-item
		'item-class (class thing)))			
	    (write-evaluation-value thing t))))
  (gesture-push new-text-string))

(define-gesture-instruction (equal-datum 101)
    ()
  (gesture-push
    (make-evaluation-boolean-value
      (evaluation-value-= (gesture-pop) (gesture-pop)))))

(define-gesture-instruction (push-thread-state 102)
    ((new-pc register-1))
  ;; here Sunday 6/2
  )

(define-gesture-instruction (type-test 103)
    ((thing register-1)
     (type-specification register-2))
  (setf thing (gesture-pop))
  (setf type-specification (gesture-constant 0))
  (cond ((type-specification-type-p thing type-specification)
	 (gesture-push evaluation-true-value))
	(t
	 (gesture-push evaluation-false-value))))

(define-gesture-instruction (class-test 104)
    ((thing register-1)
     (class register-2))
  (setf class (gesture-pop))
  (setf thing (gesture-pop))
  (cond ((and (framep thing)
	      (frame-of-class-p thing class))
	 (gesture-push evaluation-true-value))
	(t
	 (gesture-push evaluation-false-value))))

(define-gesture-instruction (value2type 105)
    ((thing register-1)
     (type-specification register-2))
  (setf thing (gesture-pop))
  (setf type-specification (gesture-constant 0))
  (cond
    ((type-specification-type-p thing type-specification)
     (gesture-push thing))
    (t
     (gesture-evaluation-error
       'type-mismatch
       'thing thing
       'desired-type (tformat-text-string "~NT" type-specification)))))

(define-gesture-instruction (bitwise-or 106)
    ()
  (gesture-push
    (logiorf (gesture-pop) (gesture-pop))))

(define-gesture-instruction (bitwise-and 107)
    ()
  (gesture-push
    (logandf (gesture-pop) (gesture-pop))))

(define-gesture-instruction (get-class 108)
    ()
  (gesture-evaluation-error
    'class-operator-is-not-yet-implemented))

(define-gesture-instruction (new-class-instance 109)
    ()
  (gesture-evaluation-error
    'new-class-instance-is-not-yet-implemented))

;;; Decades 110 and 120 Components/Parts

(define-gesture-instruction (sequence-length 110)
    ((sequence register-1))
  (setf sequence (gesture-pop))
  (gesture-push
    (evaluation-sequence-length sequence)))

(define-gesture-instruction (nth-sequence-element 111)
    ((sequence register-1)
     (length register-2)
     (index register-3))
  (setf index (gesture-pop))
  (setf sequence (gesture-pop))
  (setf length (evaluation-sequence-length sequence))
  (cond ((<f -1 index length)
	 (gesture-push
	   (copy-if-evaluation-value
	     (evaluation-sequence-aref sequence index))))
	(t
	 (gesture-evaluation-error
	   'sequence-index-out-of-range
	   'length-of-sequence length
	   'index index))))

;; Sat goals
;; make and test all creators acessors (and length) in NTW
;; think about concludes
;; do commit
;; initialize method
;; fake up parts of the semantic channel
;; make new evaluation error that works on
;;    name (key val key val)
;; hack up a debugger
;; worry about on-error and signal
;; we should only support the new variant

(define-gesture-instruction (set-nth-sequence-element 112)
    ((sequence register-1)
     (index register-2)
     (new-value register-3)
     (length register-4))
  (setf new-value (gesture-pop))
  (setf index (gesture-pop))
  (setf sequence (gesture-pop))
  (setf length (evaluation-sequence-length sequence))
  (cond ((<f -1 index length)
	 (setf sequence
	       (allocate-new-evaluation-sequence-copy sequence))
	 ;; I think we need to do this
	 (loop with held-vector = (evaluation-sequence-value sequence)
	       with new-element-index =  (+f index
					     (evaluation-sequence-first-element-index))
	       for i from (evaluation-sequence-first-element-index)
		     below (managed-array-length held-vector)
	       do
	   (setf (managed-svref held-vector i)
		 (if (=f i new-element-index)
		     (copy-if-evaluation-value new-value)
		     (copy-if-evaluation-value (managed-svref held-vector i)))))
	 (gesture-push sequence))
	(t
	 (gesture-evaluation-error
	   'sequence-index-out-of-range
	   'length-of-sequence length
	   'index index))))

(define-gesture-instruction (sequence-push 113)
    ((sequence register-1)
     (new-value register-2))
  (setf new-value (gesture-pop))
  (setf sequence (gesture-pop))
  (gesture-push
    (if (eq (gesture-constant 0) 'first)
	(evaluation-sequence-insert-at-beginning sequence new-value)
	(evaluation-sequence-insert-at-end sequence new-value))))

(define-gesture-instruction (sequence-remove 114)
    ((sequence register-1)
     (index register-2)
     (new-sequence register-3))
  ;; I'm presuming that the first argument is deepest in the stack.  -jra 8/15/96
  (setf index (gesture-pop))
  (setf sequence (gesture-pop))
  (setf new-sequence (evaluation-sequence-remove-element-at-index
		       sequence index))
  (if new-sequence
      (gesture-push new-sequence)
      ;; Is this how errors get signalled?  -jra 8/15/96
      (gesture-evaluation-error
	'sequence-remove-index-out-of-range
	'sequence sequence
	'index index)))

(defun evaluation-sequence-without-elements (sequence evaluation-value first-only-p)
  (allocate-evaluation-sequence
    (nreverse
      (loop with remove-p = t
	    with eval-list = '()
	    for element being each evaluation-sequence-element of sequence
	    do
	(cond
	  ((and remove-p
		(evaluation-value-= element evaluation-value))
	   (when first-only-p
	     (setf remove-p nil)))
	  (t
	   (eval-push (copy-if-evaluation-value element) eval-list)))
	    finally
	      (return eval-list)))))
	   
(define-gesture-instruction (sequence-remove-element 120)
    ((sequence register-1)
     (value-to-match register-2)
     (new-sequence register-3))
  (setf value-to-match (gesture-pop))
  (setf sequence (gesture-pop))
  (setf new-sequence (evaluation-sequence-without-elements sequence value-to-match t))
  (gesture-push new-sequence))

(define-gesture-instruction (set-structure-slot 115)
    ((structure register-1)
     (attribute-name register-2)
     (new-value register-3))
  (setf new-value (gesture-pop))
  (setf attribute-name (gesture-pop))
  (setf structure (gesture-pop))
  (setf structure (obtain-mutable-evaluation-structure-copy structure))
  (setf (evaluation-structure-slot structure attribute-name) new-value)
  (gesture-push structure))

(define-gesture-instruction (make-structure 116)
    ((struct-length register-1)
     (eval-list register-2))
  (setf struct-length (gesture-pop))
  ;; use headed list to avoid conditional in loop
  (setf eval-list nil)
  (loop for i from 0 below struct-length
	as value = (gesture-pop)
	do
    (tw-trace 2 "structure-val i=~s value=~s~%" i value)
    (when (and (/=f (logandf i 1) 0)
	       (not (symbolp value))) ; should check for dupes?
      (gesture-evaluation-error
	'structure-attribute-name-not-symbol
	'would-be-attribute-name value))
    (eval-push value eval-list))
  (tw-trace 2 "structure-args =~s~%" eval-list)
  (gesture-push (allocate-evaluation-structure eval-list)))
    

(define-gesture-instruction (make-sequence 117)
    ((sequence-length register-1)
     (eval-list register-2))
  (setf sequence-length (gesture-pop))
  ;; use headed list to avoid conditional in loop
  (setf eval-list nil)
  (loop for i from 0 below sequence-length
	as value = (gesture-pop)
	do
    (eval-push value eval-list))
  (tw-trace 2 "seq-args=~s~%" eval-list)
  (gesture-push (allocate-evaluation-sequence eval-list)))



(define-gesture-instruction (value2sequence 118)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((evaluation-sequence-p value)
	 (gesture-push value))
	(t
	 (gesture-evaluation-error
	   'value-is-not-a-sequence
	   'the-value value))))

(define-gesture-instruction (value2struct 119)
    ((value register-1))
  (setf value (gesture-pop))
  (cond ((evaluation-structure-p value)
	 (gesture-push value))
	(t
	 (gesture-evaluation-error
	   'value-is-not-a-structure
	   'the-value value))))

;;;; Decade 130-140 floats

(define-gesture-instruction (add-float 130)
    ()
  (gesture-push
    (+f (gesture-pop) (gesture-pop))))

(define-gesture-instruction (subtract-float 131)
    ()
  (gesture-push
    (-f (gesture-pop) (gesture-pop))))

(define-gesture-instruction (multiply-float 132)
    ()
  (gesture-push
    (*f (gesture-pop) (gesture-pop))))

(define-gesture-instruction (equal-float 133)
    ()
  (gesture-push
    (if (=f (gesture-pop) (gesture-pop))
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (push-float 134)
    ()
;  (format t "pre pushfix sp=~s~%" (gesture-sp))
  (gesture-push
    (gesture-constant 0)))
;  (format t "pre pushfix sp=~s~%" (gesture-sp)))

(define-gesture-instruction (int2float 135)
    ()
  (gesture-push
    (gesture-pop)))

(define-gesture-instruction (negate-float 137)
    ()
  (gesture-push
    (-f (gesture-pop))))

(define-gesture-instruction (greater-than-float 138)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (>f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))


(define-gesture-instruction (less-than-float 139)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (<f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))


(define-gesture-instruction (greater-than-equal-float 140)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (>=f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))


(define-gesture-instruction (less-than-equal-float 141)
    ((first-arg register-1)
     (second-arg register-2))
  (setf second-arg (gesture-pop)) ; because of left to right eval
  (setf first-arg (gesture-pop))
  (gesture-push
    (if (<=f first-arg second-arg)
	evaluation-true-value
	evaluation-false-value)))

(define-gesture-instruction (quotient-float 142)
    ((dividend register-1)
     (divisor register-2))
  (setf divisor (gesture-pop))
  (setf dividend (gesture-pop))
  (gesture-push
    (truncatef-first dividend divisor)))


(define-gesture-instruction (remainder-float 143)
    ((dividend register-1)
     (divisor register-2))
  (setf divisor (gesture-pop))
  (setf dividend (gesture-pop))
  (gesture-push
    (rem-fixnums dividend divisor)))

(define-gesture-instruction (divide-float 144)
    ((dividend register-1)
     (divisor register-2))
  (setf divisor (gesture-pop))
  (setf dividend (gesture-pop))
  (gesture-push
    (rem-fixnums dividend divisor)))

(define-gesture-instruction (push-long 135)
    ()
  (gesture-push
    (gesture-constant 0)))

#+vkp-development
(defvar gesture-instructions-array nil)

#+vkp-development
(defun gesture-instruction-name-from-index (code)
  (unless gesture-instructions-array
    (let ((gesture-max-instruction-code 150))
;	    (cadr (gesture-instruction (car all-gesture-instruction-names)))))
      (setf gesture-instructions-array
	    (allocate-managed-simple-vector (+f gesture-max-instruction-code 1)))
      (loop as instruction-name in all-gesture-instruction-names
	    as instruction-code = (cadr (gesture-instruction instruction-name))
	    do
	(setf (svref gesture-instructions-array instruction-code)
	      instruction-name))))
  (svref gesture-instructions-array code))

(defun-for-macro gesture-instruction< (gi1 gi2)
  (<f (cadr gi1) (cadr gi2)))

(defun-for-macro make-instruction-clause (code substitution-list)
  (labels ((z (x)
	     (cond
	       ((atom x)
		(cond ((symbolp x)
		       (let ((subst? (assq x substitution-list)))
			 (if subst? (cadr subst?) x)))
		      (t
		       x)))
	       (t
		(cons (z (car x))
		      (z (cdr x)))))))
    (z code)))

(defmacro evaluate-gesture-instruction (instruction-number-var)
  (let ((instruction-definitions
	  (loop for instruction-name in all-gesture-instruction-names
		collect
		(gesture-instruction instruction-name))))
    (setf instruction-definitions
	  (sort-list instruction-definitions #'gesture-instruction< nil))
    (loop with case-clauses = '()
          for instruction in instruction-definitions
	  do
      (push
	`(,(cadr instruction)
	   ,@(make-instruction-clause (caddr instruction)
				      (car instruction)))
	case-clauses)
	  finally
	    (return
	      `(fixnum-case ,instruction-number-var
		 ,@(nreverse case-clauses))))))






;;;; Gesture Emitter/Compiler Shared Definitions



(defmacro gesture-value-node-type (x) `(car ,x))
(defmacro gesture-value-node-operation (x) `(cadr ,x))
(defmacro gesture-value-node-args (x) `(cddr ,x))

(defun make-gesture-value-node (type op args)
  (phrase-cons type (phrase-cons op args)))

(defun-simple constant-symbol-value-node-of-symbol-p (node symbol)
  (and (eq (gesture-value-node-type node) 'symbol)
       (eq (gesture-value-node-operation node) 'symbol-constant)
       (eq (car (gesture-value-node-args node)) symbol)))

(defun get-cast-operator (source-type target-type)
  (declare (ignore source-type))
  (cond
    ((consp target-type)
     (case (car target-type)
       (class 
	(values 'value2frame (cadr target-type)))
       ((structure struct)
	'value2struct)
       (sequence
	'value2sequence)))
    (t
     (case target-type
       (datum       'value2datum)
       (symbol      'value2symbol)
       (float       'value2float)
       (number      'value2quantity)
       (integer     'value2integer)
       (text        'value2text)
       (truth-value 'value2truth-value)))))
  





;;;; The Gesture Code Emitter




(defvar current-gesture-code-sequences nil)
(defvar current-gesture-code-sequence nil)
(defvar current-gesture-sequence-index 0)
(defvar current-gesture-label-index 0)

(defvar gesture-source-stack nil) ; always points to statement or value node

(defmacro with-gesture-source ((source-expression) &body body)
  `(progn
     (when tw-source-debug-p
       (gensym-push ,source-expression gesture-source-stack))
     ,@body
     (when tw-source-debug-p
       (gensym-pop gesture-source-stack))))

(defmacro gesture-code-sequence-index (x) `(car ,x))
(defmacro gesture-code-sequence-instructions (x) `(cadr ,x))
(defmacro gesture-code-sequence-sources (x) `(caddr ,x))

(defun new-gesture-code-sequence ()
  (let ((new-gcs (gensym-list (incff current-gesture-sequence-index) nil nil)))
    (gensym-push new-gcs current-gesture-code-sequences)
    new-gcs))

(defun write-gesture-code-instruction (gcs instruction)
  (gensym-push instruction 
	       (gesture-code-sequence-instructions gcs))
  (gensym-push (car gesture-source-stack)
	       (gesture-code-sequence-sources gcs)))

(defmacro emit-gesture-instruction (instruction &body args)
  `(write-gesture-code-instruction
     current-gesture-code-sequence
       (gensym-list ,instruction ,@args)))

(defun emit-gesture-instruction-with-constants (instruction constants)
  (write-gesture-code-instruction
    current-gesture-code-sequence
    (gensym-cons instruction constants)))

(defun new-gesture-local (name index type)
  (let ((local (make-gesture-local name index type)))
    local))

(defun add-variable-data-to-gesture (gesture args locals returns)
  (loop with count = (length args)
	with res = '()
	for (name type) in args
	as i from 0 by 1
	do
    (gensym-push (new-gesture-local name (-f i count) type) res)
	finally
	  (setf (gesture-function-argument-count gesture) count)
	  (setf (gesture-function-argument-specs gesture) (nreverse res)))
  (loop with count = (length locals)
	with res = '()
	for (name type) in locals
	as i from 0 by 1
	do
    (gensym-push (new-gesture-local name (+f i frame-header-size) type) res)
	finally
	  (setf (gesture-function-locals-count gesture) count)
	  (setf (gesture-function-locals-specs gesture) (nreverse res)))
  (loop with count = (length returns)
	with res = '()
	with name = nil
	for type in returns
	as i from 0 by 1
	do
    (gensym-push (new-gesture-local name i type) res)
	finally
	  (setf (gesture-function-return-count gesture) count)
	  (setf (gesture-function-return-specs gesture) (nreverse res))))

(defmacro compiled-gesture-name (x) `(car ,x))
(defmacro compiled-gesture-args (x) `(cadr ,x))
(defmacro compiled-gesture-returns (x) `(caddr ,x))
(defmacro compiled-gesture-locals (x) `(cadddr ,x))
(defmacro compiled-gesture-body (x) `(fifth ,x))
(defmacro compiled-gesture-g2-call-references (x) `(sixth ,x))
(defmacro compiled-gesture-tw-call-references (x) `(seventh ,x))
(defmacro compiled-gesture-variable-type (x) `(cadr ,x))

(defun emit-compiled-gesture (compiled-gesture)
  (let* ((args (compiled-gesture-args compiled-gesture))
	 (returns (compiled-gesture-returns compiled-gesture))
	 (locals (compiled-gesture-locals compiled-gesture))
	 (body (compiled-gesture-body compiled-gesture))
	 (gesture (make-gesture-function))
	 (current-gesture-code-sequences nil)
	 (current-gesture-sequence-index -1) ; first one will be zero
	 (current-gesture-label-index 0)
	 (outer-code-sequence (new-gesture-code-sequence)))
    (setf gesture-source-stack nil)
    (add-variable-data-to-gesture gesture args locals returns)
    (emit-compiled-gesture-statement body outer-code-sequence)
    (setf (gesture-function-instructions gesture) nil)
    (setf (gesture-code-sequence-instructions outer-code-sequence)
	  (nreverse
	    (gesture-code-sequence-instructions outer-code-sequence)))
    (setf (gesture-code-sequence-sources outer-code-sequence)
	  (nreverse
	    (gesture-code-sequence-sources outer-code-sequence)))
    (multiple-value-bind (instruction-vector source-vector?)
	(assemble-gesture-code-sequence outer-code-sequence gesture)
      (setf (gesture-function-instructions gesture) instruction-vector)
      (setf (gesture-function-source-index gesture) source-vector?))
    #+development
    (print-when-tracing-in-events-modules gesture)
    gesture))

;;; `assemble-gesture-code-sequence' consumes the code-sequence argument

(defparameter obsolete-gesture-instruction-map
  '((make-struct . make-structure)
    (set-struct-slot . set-structure-slot)))

(defun assemble-gesture-code-sequence (code-sequence gesture)
  (let* ((number-of-real-instructions
	   (loop for (instruction-name . ignore)
		     in (gesture-code-sequence-instructions code-sequence)
		 count (not (eq instruction-name 'label))))
	 (code-vector (allocate-managed-simple-vector number-of-real-instructions))
	 (source-vector
	   (and tw-source-debug-p
		(allocate-managed-simple-vector number-of-real-instructions)))
	 (label-table nil))
    (loop with instruction-index = 0
	  with instruction-sources = (gesture-code-sequence-sources code-sequence)
	  with instruction-source = nil
	  for instruction
	      in (gesture-code-sequence-instructions code-sequence)
	  as replacement-instruction-name?
	     = (cdr (assq (car instruction) obsolete-gesture-instruction-map))
	  do
      (when replacement-instruction-name?
	(setf (car instruction) replacement-instruction-name?))
      (when tw-source-debug-p
	(setf instruction-source (gensym-pop instruction-sources)))
      (cond
	((eq (car instruction) 'label)
	 (gensym-push (gensym-cons (cadr instruction) instruction-index)
		      label-table))
	(t
	 (setf (svref code-vector instruction-index) instruction)
	 (when tw-source-debug-p
	   (setf (svref source-vector instruction-index) instruction-source))
	 (incff instruction-index))))
    ;; resolve branch targets
    ;; and local variables into frame offsets
    ;; and mnemonics into opcodes
    ;; (pprint label-table)
    (loop for i from 0 below number-of-real-instructions
	  as instruction = (svref code-vector i)
	  as mnemonic = (car instruction)
	  do
      (case mnemonic
	((branch-always branch-if-true branch-if-false push-thread-state)
	 (setf (cadr instruction)
	       (1-f (-f (cdr (assq (cadr instruction) label-table)) i))))
	((get-local get-local-or-no-item
		    set-local set-local-from-return)
	 (setf (cadr instruction)
	       (resolve-gesture-local-variable gesture (cadr instruction)))))
      (setf (car instruction)
	    (cadr (or (gesture-instruction (car instruction))
		      (error "Unknown instruction mnemonic ~s~%"
			     (car instruction))))))
    (reclaim-gensym-tree label-table)
    (values code-vector source-vector)))

(defun resolve-gesture-local-variable (gesture var-name)
  (or
    (loop for local in (gesture-function-argument-specs gesture)
	  as name = (gesture-local-name local)
	  when (eq name var-name)
	    return (gesture-local-index local))
    (loop for local in (gesture-function-locals-specs gesture)
	  as name = (gesture-local-name local)
	  when (eq name var-name)
	    return (gesture-local-index local))))

(defun emit-compiled-gesture-statement (statement code-sequence)
  (with-gesture-source (statement)
    (let ((statement-type (car statement))
	  (statement-subforms (cdr statement))
	  (current-gesture-code-sequence code-sequence))
      (case statement-type
	(local-assignment
	 (emit-compiled-gesture-expression (third statement-subforms))
	 (emit-gesture-instruction 'set-local (first statement-subforms)))
	(change-slot
	 (emit-compiled-gesture-expression (third statement-subforms))
	 (emit-compiled-gesture-expression (second statement-subforms))
	 (emit-gesture-instruction 'set-slot (first statement-subforms)))
	(change-array-length
	 nil)
	(if
	  (let ((test-expression (first statement-subforms))
		(then-clause (second statement-subforms))
		(else-clause? (third statement-subforms))
		(end-label (incff current-gesture-label-index)))
	    (cond
	      (else-clause?
	       (let ((else-label (incff current-gesture-label-index)))
		 (emit-compiled-gesture-expression test-expression)
		 (emit-gesture-instruction 'branch-if-false else-label)
		 (emit-compiled-gesture-statement then-clause code-sequence)
		 (emit-gesture-instruction 'branch-always end-label)
		 (emit-gesture-instruction 'label else-label)
		 (emit-compiled-gesture-statement else-clause? code-sequence)
		 (emit-gesture-instruction 'label end-label)))
	      (t
	       (emit-compiled-gesture-expression test-expression)
	       (emit-gesture-instruction 'branch-if-false end-label)
	       (emit-compiled-gesture-statement then-clause code-sequence)
	       (emit-gesture-instruction 'label end-label)))))
	(for-loop-integer
	 ;; must gensym a variable 
	 (let ((iteration-var-name (first statement-subforms))
	       (limit-var-name (second statement-subforms))
	       (initial-value-expression (third statement-subforms))
	       (limit-value-expression (fourth statement-subforms))
	       (increment (fifth statement-subforms))
	       (increasing-p (sixth statement-subforms))
	       (loop-body (seventh statement-subforms))
	       (loop-top (incff current-gesture-label-index))
	       (loop-exit (incff current-gesture-label-index)))
	   (emit-compiled-gesture-expression initial-value-expression)
	   (emit-gesture-instruction 'set-local iteration-var-name)
	   (emit-compiled-gesture-expression limit-value-expression)
	   (emit-gesture-instruction 'set-local limit-var-name)
	   (emit-gesture-instruction 'label loop-top)
	   (emit-gesture-instruction 'get-local iteration-var-name)
	   (emit-gesture-instruction 'get-local limit-var-name)
	   (cond (increasing-p
		  (emit-gesture-instruction 'greater-than-fixnum))
		 (t
		  (emit-gesture-instruction 'less-than-fixnum)))
	   (emit-gesture-instruction 'branch-if-true loop-exit)
	   (emit-compiled-gesture-statement loop-body code-sequence)
	   (emit-gesture-instruction 'push-fixnum increment)
	   (emit-gesture-instruction 'get-local iteration-var-name)
	   (emit-gesture-instruction 'add-fixnum)
	   (emit-gesture-instruction 'set-local iteration-var-name)
	   (emit-gesture-instruction 'branch-always loop-top)
	   (emit-gesture-instruction 'label loop-exit)))
	((gesture-call gesture-call-next-method call-g2)
	 ;; form is (gname lname-list type-list arg-list)
	 (let* ((assignment-variable-list (second statement-subforms))
		(assignment-type-list (third statement-subforms))
		(compiled-arg-list (fourth statement-subforms))
		(assignment-count (length assignment-variable-list)))
	   
	   ;; 1 emit the args
	   (loop for compiled-arg in compiled-arg-list 
		 do
	     (emit-compiled-gesture-expression compiled-arg))
	   
	   ;; 2 emit the arg-count
	   (emit-gesture-instruction 'push-fixnum (length compiled-arg-list))
	   
	   ;; 3 emit something that will push the definition on the stack
	   (ecase statement-type
	     ((gesture-call call-g2)
	      (emit-gesture-instruction
		'push-gesture-def (first statement-subforms)))
	     (gesture-call-next-method
	      (emit-gesture-instruction
		'push-next-method (first statement-subforms))))
	   
	   ;; 4 emit arg type check
	   (emit-gesture-instruction 'check-args)
	   
	   ;; 5 emit control transfer statement
	   (ecase statement-type
	     ((gesture-call gesture-call-next-method)
	      (emit-gesture-instruction 'procedure-call))
;	   (gesture-call-next-method
;	    (emit-gesture-instruction 'call-next-method))
	     (call-g2
	      (emit-gesture-instruction 'call-in-g2)))
	   
	   ;; 6 emit return value handling
	   (emit-gesture-instruction 'return-check assignment-count)
	   (loop for assignment-var-name in assignment-variable-list
		 for assignment-var-type in assignment-type-list
		 do
	     (multiple-value-bind (cast-operator additional-arg?)
		 (get-cast-operator 'item-or-datum assignment-var-type)
	       (cond ((eq assignment-var-type 'item-or-datum)
		      ;; no cast needed , I think
		      nil)
		     (additional-arg?
		      (emit-gesture-instruction cast-operator additional-arg?))
		     (t
		      (emit-gesture-instruction cast-operator))))
	     (emit-gesture-instruction 'set-local-from-return
				       assignment-var-name))
	   ;; pop remaining stack values
	   ;; return-count - assignment-count
	   ;; after the return-check instruction is softened to >=
	   ))
	(return
	  (let ((compiled-value-list (first statement-subforms)))
	    (loop for compiled-value in compiled-value-list 
		  do
	      (emit-compiled-gesture-expression compiled-value))
	    (emit-gesture-instruction 'push-fixnum (length compiled-value-list))
	    (emit-gesture-instruction 'procedure-return)))
	(repeat
	 (let ((repeat-top (incff current-gesture-label-index)))
	   (emit-gesture-instruction 'label repeat-top)
	   (emit-compiled-gesture-statement (first statement-subforms) code-sequence)
	   (emit-gesture-instruction 'branch-always repeat-top)
	   (emit-gesture-instruction 'label (second statement-subforms))))
	(exit-if
	 (emit-compiled-gesture-expression (first statement-subforms))
	 (emit-gesture-instruction 'branch-if-true (second statement-subforms)))
	((compound-statement begin
			     compound-statement-with-error-handling
			     compound-statement-with-unwind-protection)
	 (let* ((statement-list (first statement-subforms))
		(protecting-statement? (second statement-subforms))
		(on-error-var-and-type?
		  (and protecting-statement? (cadr protecting-statement?)))
		(after-protect (incff current-gesture-label-index))
		(cleanup-start (incff current-gesture-label-index)))
	   (when protecting-statement?
	     (emit-gesture-instruction
	       'push-thread-state
	       cleanup-start
	       (and (eq statement-type 'compound-statement-with-error-handling)
		    (type-specification-class (cadr on-error-var-and-type?)))))
	   (loop for statement in statement-list
		 do
	     (emit-compiled-gesture-statement statement code-sequence))
	   (when protecting-statement?
	     (emit-gesture-instruction 'branch-always after-protect)
	     (emit-gesture-instruction 'label cleanup-start)
	     (case (car protecting-statement?)
	       (on-error
		(let ((var-and-type (second protecting-statement?)))
		  (emit-gesture-instruction 'set-local (car var-and-type))
		  (emit-compiled-gesture-statement
		    (third protecting-statement?) code-sequence)))
	       (on-exit
		(emit-compiled-gesture-statement
		  (third protecting-statement?) code-sequence)))
	     (emit-gesture-instruction 'label after-protect))))))))

(defun emit-compiled-gesture-expression (node)
  (with-gesture-source (node)
    (cond
      ((primitive-gesture-value-node-p node)
       (emit-primitive-gesture-value-node node))
      (t
       (let ((instruction-name
	       (get-instruction-for-gesture-value-node node))
	     (args (gesture-value-node-args node)))
	 (cond
	   ((or (eq instruction-name 'get-slot)
		(eq instruction-name 'get-slot-or-no-item))
	    (emit-compiled-gesture-expression
	      (first (gesture-value-node-args node)))
	    (emit-gesture-instruction
	      'get-slot
	      (first
		(gesture-value-node-args
		  (second (gesture-value-node-args node))))
	      (eq instruction-name 'get-slot-or-no-item))) ; controls no-item allowed
	   ((eq instruction-name 'array-length)
;	    #+development
;	    (cerror "go on" "don't do this")
	    )
	   ((eq instruction-name 'if-expression)
	    (gensym-dstruct-bind ((condition then else) args)
	      (let ((else-label (incff current-gesture-label-index))
		    (end-label (incff current-gesture-label-index)))
		(emit-compiled-gesture-expression condition)
		(emit-gesture-instruction 'branch-if-false else-label)
		(emit-compiled-gesture-expression then)
		(emit-gesture-instruction 'branch-always end-label)
		(emit-gesture-instruction 'label else-label)
		(emit-compiled-gesture-expression else)
		(emit-gesture-instruction 'label end-label))))
	   ((or (eq instruction-name 'type-test)
		(eq instruction-name 'value2type)
		(eq instruction-name 'value2frame))
	    (emit-compiled-gesture-expression (car args))
	    (emit-gesture-instruction
	      instruction-name
	      (copy-tree-using-gensym-conses (cadr args))))
	   (t
	    (loop with constants = nil
		  for arg in args
		  do
	      (cond ((eq (car arg) 'unevaluated-constant)
		     (gensym-push (cadr arg) constants))
		    (t
		     (emit-compiled-gesture-expression arg)))
		  finally
		    (setf constants (nreverse constants))
		  ;; the following call absorbs constants
		    (emit-gesture-instruction-with-constants
		      instruction-name constants)))))))))

(defun primitive-gesture-value-node-p (node)
  (memq (gesture-value-node-operation node)
	'(fetch-local fetch-local-or-no-item
	  integer-constant truth-value-constant
	  symbol-constant text-constant float-constant
	  long-constant)))

(defun emit-primitive-gesture-value-node (node)
  (let ((args (gesture-value-node-args node)))
    (ecase (gesture-value-node-operation node)
      (fetch-local
       (emit-gesture-instruction 'get-local (car args)))
      (fetch-local-or-no-item
       (emit-gesture-instruction 'get-local-or-no-item (car args)))
      (integer-constant
       (emit-gesture-instruction 'push-fixnum (car args)))
      (float-constant
       (emit-gesture-instruction 'push-float (car args)))
      (long-constant
       (emit-gesture-instruction 'push-long (car args)))
      (symbol-constant
       (emit-gesture-instruction 'push-symbol (car args)))
      (text-constant
       (emit-gesture-instruction 'push-text (car args)))
      (truth-value-constant
       (emit-gesture-instruction 'push-truth-value (car args))))))

(defun get-instruction-for-gesture-value-node (node)
  (let ((operation (gesture-value-node-operation node)))
    ;; someday this will do something more complex
    operation))



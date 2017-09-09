(in-package "AB")

;;;; Module GTHREAD

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde

;;; Note: the name of this module has been changed from THREAD to GTHREAD,
;;; the reason is that we already have thread.[ch] in RTL source code, which
;;; seriously confused C compiler when doing #includes.
;;;
;;; As a result, three DEF-SYSTEM-VARIABLE definitions has to be changed
;;; correspondly, or they will record into non-exist module.
;;;
;;; -- Chun Tian (binghe) / Glority , 2011/10/11

;;;; Introduction

;;; Tools to manage a tree of threads, much like a unix tree
;;; of processes, a display postscript set of contexts, or
;;; a Java set of threads.

;;; Thread are always in one of four states :new, :runnable,
;;; :not-runable, or :dead.


;;;; Forward References

#+development
(declare-forward-reference rpc-in-progress? function)






;;;; Slow Methods

;;; These have the advantage that we don't need to modify any tables
;;; in the GSI substrate.

(defun slowly-lookup-next-method (name path)
  (loop for type = (pop path) while type
	as method? = (get name type)
	when method? do (return (values method? path))))

(defmacro def-generic-slow-method (name (structure-type &rest args) &body body)
  (declare (ignore body))
  `(defun ,name (,structure-type ,@args)
     (let ((inheritance-path
	     (inheritance-path-of-type-description
       (type-description-of-structure ,structure-type))))
       (funcall-next-slow-method-1 inheritance-path ',name ,structure-type ,args))))

(defmacro def-slow-method (name (type &rest args) &body body)
  (multiple-value-bind (decl stmts)
      (split-declarations-and-documentation-from-statements body)
    (let ((method-function (intern (format nil "M-~S-~S-1" name type))))
      `(progn
	 (defun-allowing-unwind ,method-function (#1=#:path ,type ,@args)
	   ,@decl
	   (macrolet ((funcall-superior-method (frame &rest args) 
			(list 'funcall-next-slow-method-1 #1# ',name frame args)))
	     ,@stmts))
	 (setf (get ',name ',type) ',method-function)))))

(defmacro funcall-next-slow-method-1 (inheritance-path name instance args)
  `(multiple-value-bind (method next-path)
       (slowly-lookup-next-method ,name ,inheritance-path)
     (funcall method next-path ,instance ,@args)))







;;;; Threads

;;; All activities in the bridge take place under the umbrella of a thread.
;;; The current-thread is a structure refined from the structure thread.
;;; It is useful to think of it as containing the thread's global bindings.

;;; The set of all threads is a tree with root-thread at its base.  The root
;;; thread is the only thread with no parent, and we contrive to never give
;;; cycles to the root thread, or to ever delete it.

;;; A `thread' structure has:
;;;    - a symbolic name, and serial number,
;;;    - a parent and children,
;;;    - a state, e.g. :not-runable, and an optional reason for the state
;;;    - a priority, 
;;;    - a list of pending events,
;;;    - a list of i/o sockets it owns, and
;;;    - state to implement microtasking (including a stack).

;;; The parent and children link the thread into the tree of all threads.
;;; When a thread is created is becomes a child of the current-thread.
;;; When a thread is reclaimed it children are reclaimed, and it is removed
;;; from the parent.  The thread tree consists entirely of thread
;;; structures, NIL, and gensym lists.  The parent of the root thread is
;;; NIL.

;;; A slot, cleaned?, is used to mark the thread when all the frames
;;; have been unwound and cleaned up.  This avoid having them fire
;;; twice, as might happen when debugging, or if they killing becomes
;;; recursive.


;;;; Bug HQ-4192692, "Weblink memory increase"

;;; There was a bug fix put in to GW 1.0r4, by hand-editing the translated C
;;; code, in gw/c/thread.c.  In order to start translating again, we need to
;;; put the fix into the Lisp code.  Here is the log from the commit:

;;; revision 1.12.2.1; date: 2002/02/28 20:57:04;  author: cshapiro

;;;  In order to give the illusion of multiplexing various units of computation,
;;;  Weblink has its own ersatz task switching mechanism which it calls threads.
;;;  Weblink threads are cooperatively scheduled through state machines.  The
;;;  current state of computation in a Weblink thread is kept inside of a
;;;  structure associated through a many-to-one mapping, called a frame.  Frames
;;;  are supposed to be conceptually equivalent to stack frames in your average
;;;  programming language.  Both threads and frames are created and disposed of
;;;  as part of the life cycle of a client query.

;;;  However, while threads are resourced through Gensym's pooling mechanism,
;;;  frames aren't.  This discrepancy is the source of a horrible memory leak in
;;;  the current (1.0r3) and prior (1.0r2, etc.) Weblink releases.

;;;  In order to fix this I have hacked the translated Lisp code and introduced
;;;  a simple resourcing mechanism at the C level to resource frames.

;;;  Frames become garbage whenever the thread they are associated with is
;;;  returned to a pool through a reclaimer.  The normal life cycle of a thread
;;;  has the the thread allocated in THREAD-INITIALIZE and disposed of in
;;;  THREAD-FINALIZE.  A frame is first associated with a thread through
;;;  PROLOG-THREAD-FUNCTION which is called by THREAD-INITIALIZE.  The storage
;;;  for a frame is carved straight out of the heap.

;;;  In order to curb the leak, frames are now no longer always freshly
;;;  allocated.  Before allocating a fresh frame in PROLOG-THREAD-FUNCTION we
;;;  now first check a queue of frames for an available unused frame.  Since
;;;  frames vary between 6 and 11 words in length, we force all threads to be 11
;;;  words long to avoid any corruption.  Just be safe (mostly for development's
;;;  sake), I added an assertion to the frame allocation code which checks to
;;;  make sure a frame of no more than 11 words was requested.  We also retire
;;;  frames to a queue when a thread is terminated during the call to
;;;  THREAD-FINALIZE.  Unfortunately only one frame is associated with a thread
;;;  during the so-called finalization while during the servicing of clients up
;;;  to two frames can be associated with a thread.  A frame from the client
;;;  servicing thread will break its relation to one extra frame earlier than
;;;  finalization so we have to complement CLEANUP-AND-UNWIND-ONE-THREAD (which
;;;  explicitly breaks frame thread relations) with frame reclamation machinery
;;;  for the case when it gets called from GIVE-THREAD-QUANTUM.  Research has
;;;  shown that this is probably the only situation other than finalization when
;;;  thread to frame relations are broken.  A global variable signals a call
;;;  from GIVE-THREAD-QUANTUM to CLEANUP-AND-UNWIND-ONE-THREAD and
;;;  CLEANUP-AND-UNWIND-ONE-THREAD (which breaks relations between threads and
;;;  frames) will accordingly reclaim the frame passed to it.

;;; Difficulty of change: moderate - tracking down the leak site consumed
;;;  the better part of five days.

;;; Number of edit sites: 7
;;; Number of lines changed: +100

;;; Fanin and fanout of change: Everytime a client connection is serviced or
;;;  other "thread creating" operations are performed, new code to resource
;;;  frames is called.  Whenever "threads" are terminated suchas when a client
;;;  connection is completed (by a page being sent to a browser, etc.), the
;;;  new reclaiming code is called.

;;; Example: /gensym/issuekbs/g2weblink-10r2/HQ-3935847GWEX-FULVIO.KB
;;; How this has been tested: Pounded weblink with 15 web browsers for several
;;;  hours on my PC and noticed no changes in the memory footprint.


(def-structure (thread
		 (:constructor 
		   make-thread-1
		   (parent-of-thread
		     name-of-thread))
		 #+development
		 (:print-function print-thread))

  ;; Thread ID.
  (number-of-thread (generate-thread-number)) ;; Globally uniq.
  name-of-thread ;; Mnemonic value only.

  ;; Memory with Extent Over thread. (analagous to phrase cons pool.
  (string-pool-of-thread nil)
  (cons-pool-of-thread nil)

  ;; Thread Hierarchy.
  parent-of-thread
  (children-of-thread nil) ;; reclaimed in destroy-thread

  ;; Scheduling state
  (state-of-thread :new)
  (reason-for-state-of-thread :allocated)
  (cleaned? nil)
  (priority-of-thread 100)

  ;; I/O state
  (sockets-of-thread nil :reclaimer reclaim-sockets)
  (pending-events-of-thread nil :reclaimer reclaim-event-tree)

  ;; Microtasking state.
  (stack-of-thread nil)          ;; A thread of simple vectors.
  (contour-wrapper-of-thread #'null-thread-contour-wrapper)
  (microtask-of-thread nil)    ;; A simple-compiled-function defined by defun-for-thread
  (program-counter-of-thread nil)) ;; An atom, often a keyword.




#+development
(defun print-thread (thread stream depth)
  (declare (ignore depth))
  (printing-random-object (thread stream)
    (format stream "~a ~a#~d"
	    (name-of-type-description
	      (type-description-of-structure thread))
	    (name-of-thread thread)
	    (number-of-thread thread))))

(defvar the-last-thread-number 1000)

(defun generate-thread-number () ;; lame
  (incf the-last-thread-number))

(defun reclaim-event-tree (event-tree)
  (reclaim-plist-tree-of-resource-buffer event-tree))

;;; `Root-thread' is the root of a the tree of threads.
;;; Its thread-pool is managed in a unique manner.

(def-system-variable root-thread gthread
  (:funcall make-root-thread))

(defun make-root-thread () (make-thread-1 nil 'root))

(def-system-variable current-thread gthread
  (:symbol-value root-thread))

(defmacro with-thread ((p) &body body)
    `(let ((current-thread ,p)) ,@body))

(defmacro set-state-of-thread (thread state reason)
  `(progn
     (setf (state-of-thread ,thread) ,state)
     (setf (reason-for-state-of-thread ,thread) ,reason)))



;;; Calls on `thread-child-created' and `thread-child-destroyed' are called
;;; to bracket the life of a child thread.  These are called after the child
;;; is born, and before the child has actually died.  

;;; `Thread-child-created' refinements should be after methods.

;;; `Thread-child-destroyed' refinements should be before methods.

(def-generic-slow-method thread-child-created (thread child-thread))

(def-generic-slow-method thread-child-destroyed (thread child-thread))

(def-slow-method thread-child-created (thread child-thread)
  (declare (ignore thread child-thread))
  ;; Do nothing.
  )

(def-slow-method thread-child-destroyed (thread child-thread)
  (declare (ignore thread child-thread))
  ;; Do nothing.
  )


;;; Calls on `thread-initialize' and `thread-finalize' bracket the life cycle
;;; of a thread.

;;; Refinements to thread-initilize should be after methods, and they should
;;; take care to return the thread.

;;; Refinements to thread-finalize should be before methods.

(def-generic-slow-method thread-initialize (thread))

(def-generic-slow-method thread-finalize (thread))

(def-slow-method thread-initialize (thread)
  (gensym-push thread (children-of-thread current-thread))
  (setf (parent-of-thread thread) current-thread)
  (thread-child-created current-thread thread)
  thread)


;;; The implementation of `thread-finalize' defined upon
;;; `thread' does the tear down required.  It finalizes the
;;; the children, unwinds the stack, removes it from the
;;; thread hierarchy, and reclaims the thread and its
;;; pool.

(def-slow-method thread-finalize (thread)
  ;; Tear down the children.
  (loop for child = (first (children-of-thread thread))
	while child
	do (thread-finalize child))
  ;; Unwind this thread.
  (cleanup-thread-if-necessary thread)
  ;; Unlink from the thread tree.
  (let ((parent-of-thread (parent-of-thread thread)))
    (with-thread (parent-of-thread)
      (thread-child-destroyed parent-of-thread thread))
    (setf (children-of-thread parent-of-thread)
	  (delete-gensym-element thread
				 (children-of-thread parent-of-thread)))
    (when (eq current-thread thread)
      (setf current-thread parent-of-thread))
    (set-state-of-thread thread :dead :finalized))
  ;; Reclaim this thread's pool
  (clear-thread-pool thread)
  ;; Reclaim this thread
  (reclaim-structure thread))


;;; `ps' displays an outline of the tread tree.

(defun do-print-thread (thread)
  (format t "~a ~a#~d [~a, ~a] [~a ~a] (~s)"
	  (name-of-type-description
	    (type-description-of-structure thread))
	  (name-of-thread thread)
	  (number-of-thread thread)
	  (state-of-thread thread)
	  (program-counter-of-thread thread)
	  (sockets-of-thread thread)
	  (pending-events-of-thread thread)
	  (microtask-of-thread thread)))

(defun ps-1 (depth thread)
  (terpri)
  (loop repeat depth doing (write-char #\space))
  (do-print-thread thread)
  (loop for child in (children-of-thread thread)
	doing (ps-1 (1+ depth) child)))

(defun ps ()
  (ps-1 0 root-thread)
  (terpri))





;;;; Thread Ephemeral Data

;;; Each thread has a `thread-pool', a body of data said to have
;;; thread extent, i.e. it is reclaimed automaticly when the thread
;;; is finalized.

;;; This is analagous to the parser's pool of phrase conses, in G2.  The data
;;; structures in this pool are limited to strings at present.  The thread
;;; implmentor may create these data structures with copy-for-thread-tree, or
;;; thread-format.  No folding of common substructures is attempted, he may
;;; mutate the data structures as he chooses.

;;; Thread-format is analagous to tformat but the result has thread
;;; extent.

;;; Bridge RPC calls that are not implemented as threads run in the root-thread.
;;; Def-rpc-exported-to-g2 implemented them to clear its thread-pool when they
;;; return.  That has the side effect of making other uses of the root-thread's
;;; pool risky.

(def-concept thread-pool)

;; Currently thread trees contain only strings, not even conses, since
;; I haven't gotten around to conses yet.



;;; The cons pool `thread-pool' is used to implement the backbone, but
;;; NEVER the content of the thread pool.  The thread-pool family of
;;; functions should be used ONLY in this section.

(defconser thread-pool thread)


;;; `Clear-thread-pool' reclaims all memory stored in the
;;; thread-pool.  In the typical case it is only called
;;; when the thread is exited.  It is also called, for the
;;; root thread, when RPC functions return.

(defun clear-thread-pool (thread)
  (loop for string in (string-pool-of-thread thread)
	do (reclaim-gensym-string string))
  (reclaim-thread-pool-list (string-pool-of-thread thread))
  (setf (string-pool-of-thread thread) nil)
  (reclaim-thread-pool-tree (cons-pool-of-thread thread)))


(defmacro note-string-into-thread-pool (string)
  `(let ((x ,string))
     #+development
     (when (and (not (rpc-in-progress?))
		(eq root-thread current-thread))
       (cerror "go" "Dangerous allocation in root thread."))
     (thread-pool-push
       x
       (string-pool-of-thread current-thread))
     x))


;;; `Copy-for-thread-tree' copy the data structure into the
;;; the thread's pool.

(defun copy-for-thread-tree (tree)
  (cond
    ((stringp tree)
     (note-string-into-thread-pool (copy-gensym-string tree)))
    #+development
    (t
     (error "This data type may not be placed a thread's memory."))))



;;; `Thread-format' is like tformat, but places the string in
;;; the thread's memory pool.

(defun thread-format (control-string
		       &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)
  (note-string-into-thread-pool
    (tformat-gensym-string
	    control-string
	    arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)))



;;; `Thread-string-substring' Extracts a substring from a text returning it.
;;; This string is added to the current thread's pool.  Either start or end
;;; maybe nil.

(defun thread-string-substring (text start? end?)
  (note-string-into-thread-pool
    (gensym-string-substring text start? end?)))




;;;; Thread Functions and Microtasking







;;; `Prolog-thread-function' is internal to this section, it places a new
;;; function frame into the thread stack.  The program counter is set to
;;; :initialize.  The epilog is found in give-thread-quantum's handling of the
;;; :return continuation.

(defun prolog-thread-function (return-continuation microtask-function frame-size)
  (let ((frame (allocate-managed-simple-vector frame-size)))
    (setf (svref frame 0) (stack-of-thread current-thread))
    (setf (svref frame 1) (microtask-of-thread current-thread))
    (setf (svref frame 2) return-continuation) ;; (program-counter-of-thread current-thread)
    (setf (stack-of-thread current-thread) frame)
    (setf (microtask-of-thread current-thread) microtask-function)
    (setf (program-counter-of-thread current-thread) :initialize)
    frame))


(defvar trace-quantum nil)

;;; `Give-thread-quantum' feeds some cycles to the current-thread,
;;; if the thread's program counter becomes :return it then calls
;;; the thread cleanup function, and finally it unwinds the thread
;;; stack.  This is the inverse of prolog-thread-function.

(defun give-thread-quantum ()

  ;; Tracing
  (when trace-quantum
    (format t "~%~S:~D ~S"
	    (name-of-thread current-thread)
	    (number-of-thread current-thread)
	    (program-counter-of-thread current-thread)))
  
  ;; Feed the current thread
  (funcall (contour-wrapper-of-thread current-thread))

  ;; Return? -- implies two more quantums
  (when (eq :return (program-counter-of-thread current-thread))
    (cleanup-and-unwind-one-thread-frame-with-needed-contour current-thread)
    (cond
      ((microtask-of-thread current-thread)
       (give-thread-quantum))
      ;; The Thread just exited.
      (t
       (thread-finalize current-thread)))))

(defun null-thread-contour-wrapper ()
  (funcall (microtask-of-thread current-thread)))


;;; `cleanup-and-unwind-one-thread-frame-with-needed-contour' runs the cleanup
;;; continuation of the current stack frame.  This happens in two situations:
;;; when the frame returns; and when the thread is finalized.

(defun cleanup-and-unwind-one-thread-frame-with-needed-contour (thread)
  ;; Let the function cleanup.
  (with-thread (thread)
    (setf (program-counter-of-thread current-thread) :cleanup)
    (funcall (contour-wrapper-of-thread current-thread))
    ;; Unwind the stack.
    (let ((old-frame (stack-of-thread current-thread)))
      (setf (stack-of-thread current-thread) (svref old-frame 0))
      (setf (microtask-of-thread current-thread) (svref old-frame 1))
      (setf (program-counter-of-thread current-thread) (svref old-frame 2))
      (reclaim-managed-simple-vector old-frame))))

;;; `cleanup-thread-if-necessary' is responsible for unwinding
;;; the entire stack of a thread when it is finalized.  THis
;;; is called by the thread-finalize method defined on thread.

(defun cleanup-thread-if-necessary (thread)
  (unless (cleaned? thread)
    (setf (cleaned? thread) t) ;; don't try the following twice.
    (loop while (stack-of-thread thread)
	  doing
      (cleanup-and-unwind-one-thread-frame-with-needed-contour thread))))


;;; `Thread-exit-1' is called when a thread function yields
;;; to exit.

(defun thread-exit-1 ()
  (set-state-of-thread current-thread
		       (state-of-thread current-thread)
		       :thread-exiting)
  (thread-finalize current-thread))

(defun thread-kill (thread)
  (unless (or (eq (state-of-thread thread) :dead)
	      (memq (reason-for-state-of-thread thread)
		   '(:thread-exiting)))
    (setf (state-of-thread thread) :murdered))
  (unless (eq (reason-for-state-of-thread thread) :finalized)
    (thread-finalize thread)))


(defun thread-suspend (thread)
  #+development
  (unless (eq (state-of-thread thread) :runnable)
    (cerror "Go" "Can't suspend thread that isn't runnable."))
  (set-state-of-thread thread :not-runnable :suspended))

(defun thread-resume (thread)
  #+development
  (unless (and (eq (reason-for-state-of-thread thread) :suspended)
	       (eq (state-of-thread thread) :not-runnable))
    (cerror "Go" "Can't resume thread that isn't suspended."))
  (set-state-of-thread thread :runnable :resumed))

(defun thread-resume-if-necessary (thread)
  (when (and (eq (reason-for-state-of-thread thread) :suspended)
	       (eq (state-of-thread thread) :not-runnable))
    (thread-resume thread)))






;;; A `defun-for-thread' is analagous to defun.  The lambda list must be
;;; simple.  The first and only statement must be the with-thread macro which
;;; appears only in this position.

;;; `With thread' takes arguments and a set of case clauses.  The arguments are
;;; in the form of an alist.  Elements include: `:locals'.  The :locals form is
;;; (:locals <let-bindings>), these are evaluated when the function is invoked.

;;; These functions implement the microtasking in a thread.  The control stack
;;; of the thread holds invokations of these functions.  The microtasking
;;; provides cycles to these functions in quantums.  Executing the case branches
;;; of the with-thread macro consume these quantums.

;;; The case branches are evaluated in a lexical contour including the arguments
;;; and the locals.  These maybe fetched or set.  The microtasking mechinism
;;; will pack and unpack these from the function's invocation frame.  State
;;; stored in the thread structure is accessible via the special
;;; current-thread.

;;; The execution of case branch must include an invokation of the lexical macro
;;; (`yield' <case-label>) to control which branch gets the
;;; continuation of control when the next quantum becomes available.

;;; The required case branch label `:initialize' gets the first quantum.  The
;;; optional case branch label `:cleanup' is executed no matter what before the
;;; function invocation is removed from the thread stack.  The case branch
;;; label `:return' signals that the function should exit.

;;; The lexical macro (`call' <thread-function> <continuation-label> &rest
;;; <args>) is used to invoke another thread function, when it returns control
;;; will return to the continuation with the label given.

;;; The lexical macro (`return-values' &rest <values>) stores the values given
;;; into a temporary array, while the lexical macro (`with-values' <vars> &body
;;; <body>) allows the the continuation to access those values.  The length of
;;; values is limited to 10.

(defmacro defun-for-thread (name args &body body)
  (gensym-dstruct-bind (((with-thread alist  . case-branches)) body)
    (unless (eql with-thread 'with-thread)
      (warn "Defun-for-thread of ~S is missing its with-thread form." name))
    (setf case-branches (validate-and-refine-thread-case-branches name case-branches))
    (let* ((locals (rest (assq :locals alist)))
	   (special-contour
	     (rest (assq :special-contour alist)))
	   (microtask-function (intern (format nil "~@:(MT-~S~)" name)))
	   (call-site-size (+ call-site-minimum-size (length args)))
	   (frame-size (+ call-site-size (length locals)))
	   (local-bindings? (not (= call-site-minimum-size frame-size))))
      `(progn

	 ;; The function is feed microtask cycles by calling this.
	 (defun-allowing-unwind ,microtask-function ()
	   (with-permanent-allocation ;; Motivation? sloth

	     (let* ((program-counter
		      (program-counter-of-thread current-thread))
		    (pending-continuation nil)
		    ,@special-contour
		    ,@(when local-bindings?
			`((#1=#:frame (stack-of-thread current-thread))))
		    ,@(loop for arg in args as i from call-site-minimum-size
			    collect `(,arg (svref #1# ,i)))
		    ,@(loop for local in locals as i from call-site-size
			    as local-name = (if (symbolp local) local (first local))
			    collect `(,local-name (svref #1# ,i))))
	       (setf (program-counter-of-thread current-thread) :quantum-in-progress)
	       (macrolet
		   ((yield (continuation)
		      (list 'setf 'pending-continuation continuation))
		    (return-values (&rest values)
		      (list* 'return-values-for-thread-1 values))
		    (call (thread-function continuation-label &rest args)
		      (list* `call-thread-function-1
			     thread-function continuation-label args))
		    (with-values (bind &body body)
		      (list* 'with-thread-values-1 bind body))
		    (io-wait (continuation)
		      (subst
			continuation :x
			'(progn
			  (set-state-of-thread
			   current-thread :not-runnable :io-wait)
			  (yield :x))))
		    (thread-exit ()
		      '(progn
			(yield :continuation-taken-care-of) 
			;; This changes current-thread
			(thread-exit-1))))
		 (case program-counter
		   ,@case-branches
		   #+development
		   (:quantum-in-progress
		    (error "Thread function exited abnormally?"))
		   (otherwise
		    (error "No handler for this continuation."))))
	       ,@(loop for arg in args as i from call-site-minimum-size
		       collect `(setf (svref #1# ,i) ,arg))
	       ,@(loop for local in locals as i from call-site-size
		       as local-name = (if (symbolp local) local (first local))
		       collect `(setf (svref #1# ,i) ,local-name))
	       (when (and (not pending-continuation)
			  (not (eq :cleanup program-counter)))
		 (error "No continuation."))
	       (unless (eq :continuation-taken-care-of pending-continuation)
		 (setf (program-counter-of-thread current-thread) pending-continuation)))))

	 ;; The function is invoked by this.
	 (defun ,name (return-continuation ,@args)
	   (progn

	     (let ((#2=#:frame
		      (prolog-thread-function
			return-continuation #',microtask-function ,frame-size)))
	       ,@(loop
		   for arg in args as i from call-site-minimum-size
		   collect `(setf (svref #2# ,i) ,arg))
	       (let* ,(loop
			for local in locals
			as local-var = (if (symbolp local) local (first local))
			as local-init = (if (symbolp local) nil (second local))
			collect
			`(,local-var ,local-init))
		 ,@(loop  for local in locals
			  as i from call-site-size
			  as local-var = (if (symbolp local) local (first local))
			  collect `(setf (svref #2# ,i) ,local-var))))))
	 
	 ))))


;;; `Call-thread-function-1' implements the lexical macro call of
;;; defun-for-thread.

(defmacro call-thread-function-1 (thread-function continuation &rest args)
  `(progn
     (,thread-function ,continuation ,@args)
     (yield :continuation-taken-care-of)))

;;; `Return-values-for-thread-1' implements the lexical macro return-values of
;;; defun-for-thread.

(defmacro return-values-for-thread-1 (&rest results)
  `(progn
     ,@(loop for expr in results as i from 0
	     collect `(setf (svref thread-return-value-pad ,i) ,expr))))

;;; `With-thread-values-1' implements the lexical macro with-values of
;;; defun-for-thread

(defmacro with-thread-values-1 (bind &body body)
  `(let ,(loop for var in bind as i from 0 collect `(,var (svref thread-return-value-pad ,i)))
     ,@body))

;;; `Thread-return-value-pad' is internal to this section.  We store the return
;;; values of for thread functions in it.

(defvar thread-return-value-pad (make-array 10))




;;; `Validate-and-refine-thread-case-branches' is internal to the macro defun-for-thread,
;;; it adds a :cleanup clause if necessary and complains if the thread lackes an :initialize
;;; clause.

(defun-for-macro validate-and-refine-thread-case-branches (name case-branches)

  ;; Check for the required entry point.
  (unless (assq :initialize case-branches)
    (warn "The thread function ~S is missing an initialize case." name))

  ;; Add a cleanup branch if user didn't need one.
  (unless (assq :cleanup case-branches)
    (setf case-branches
	  `(,@case-branches (:cleanup (yield :thats-all-folks)))))

  ;; Return the refined case-branches
  case-branches)


;;; `Do-start-thread' is used to start a fresh child thread of the
;;; current-thread.  It takes a thread structure, presumably with some slots
;;; filled in, and a call upon a thread function.

(defmacro do-start-thread ((thread) (thread-function &rest args))
  `(let ((thread ,thread))
     (thread-initialize thread)
     (with-thread (thread)
       (,thread-function
	  nil ;; Null continuation
	  ,@args)
       (set-state-of-thread thread :runnable :initializing)
       (give-thread-quantum) ;; Run :initialize clause!
       (when (eq (state-of-thread thread) :runnable)
	 #+development
	 (when (eq root-thread current-thread)
	   (error "Huh"))
	 (set-state-of-thread thread :runnable :started)))
     thread))


;; Should check that each branch has a relinquish clause in it, and
;; should check that each relinquish has a branch to go to.  Need
;; a list of external entry points.

(defun thread-backtrace ()
  (format t "~%Current thread: ~S ~S" current-thread
	  (state-of-thread current-thread))
  (format t "~%~S in ~S"
    (program-counter-of-thread current-thread)
    (microtask-of-thread current-thread))
  (loop for frame = (stack-of-thread current-thread)
	then (svref frame 0)
	while frame
	do
    (cond
      ((null (svref frame 2))
       (format t "~% ~S - Root -" frame))
      (t
       (format t "~%~S ~S in ~S"
	       frame
	       (svref frame 2)
	       (svref frame 1))))))


  
#+nil
(defun fork-new-thread (new-thread-instance thread-function arg1 arg2 arg3 arg4)
  (thread-initialize new-thread-instance)
  (with-thread (new-thread-instance)
    (funcall thread-function  nil arg1 arg2 arg3 arg4))
  new-thread-instance)


#+nil ;; example thread
(defun-for-thread test-thread (low high c d)
  (with-thread ((:locals (counter low)
			  (max high)))
    (:initialize
      (print :initialize)
      (yield :cycle))
    (:cycle
      (print (incf counter))
      (cond
	((= counter 4)
	 (call test-thread2 :cycle counter))
	((<= max counter)
	  (yield :return))
	(t
	 (yield :cycle))))
    (:cleanup
      (print :cleanup)
      (yield :thats-all-folks))))

#+nil
(defun-for-thread test-thread2 (number)
  (with-thread ()
    (:initialize
      (print (* number number))
      (return-values (* number))
      (yield :return))))

#+nil
(defun foo () 
  (let ((p (fork-new-thread
	     (make-thread-1 current-thread 'test-thread)
	     'test-thread 0 10 nil nil)))
    (with-thread (p)
      (loop while (eq p current-thread) do (give-thread-quantum)))))



;;;; Thread Event Q

;;; The thread event Q is a gensym cons tree, possibly with test-strings.
;;; The backbone is a list, new events are placed at the end of the list.
;;; When events are enqueued the thread is resumed, if it is currently
;;; suspended.  Any thread may enqueue events into any other thread.
;;; If the thread is killed, the events are discarded.  Presumably the
;;; thread will pop events from its queue from time to time.  The
;;; form of the individual events is unspecified, beyond thier reclaiming
;;; model.

;;; `Thread-enqueue-event' takes ownership of the event passed to it,
;;; placing it in the pending event Q of the thread given.

(defun thread-enqueue-event (thread event)
  (let ((event-queue (pending-events-of-thread thread))
	(listed-event (gensym-list event)))
    (cond
      (event-queue
       (setf (cdr (last event-queue)) listed-event))
      (t
       (setf (pending-events-of-thread thread) listed-event))))
  (thread-resume-if-necessary thread))


;;; `Thread-dequeue-event' returns an event, if any, from
;;; the head of the event q for this thread.  The caller
;;; takes ownership of the event at that point.

(defun thread-dequeue-event (thread)
  (let ((result (gensym-pop (pending-events-of-thread thread))))
    result))






;;;; Thread Feeding

#+development
(def-generic-slow-method thread-feed-trace (thread))

#+development
(def-slow-method thread-feed-trace (thread)
  (format t "~&Feeding ~S" thread))

(defvar sum-of-running-threads 0)

(defvar number-of-running-threads 0)

(defun-void feed-running-threads ()
  (setf sum-of-running-threads 0)
  (feed-thread-tree root-thread)
  (setf number-of-running-threads sum-of-running-threads))

#+development
(defun compare-memory-allocation-with-label (label object)
  (when (and t ;; Used to enable/disable
	     (compare-memory-allocation))
    (format t "~%noticed at ~S on ~S" label object)))

(defun-void feed-thread-tree (p)
;  #+development
;  (compare-memory-allocation-with-label 'feed-thread-tree-1 p)
  (loop for child in (children-of-thread p)
	do (feed-thread-tree child))
;  #+development
;  (compare-memory-allocation-with-label 'feed-thread-tree-2 p)
  (when (eq :runnable (state-of-thread p))
    (incf sum-of-running-threads)
    (with-thread (p)
;      #+development
;      (thread-feed-trace p)
      (give-thread-quantum)))
;  #+development
;  (compare-memory-allocation-with-label 'feed-thread-tree-3 p)
  )





(defun end-io-wait ()
  (end-io-wait-1 root-thread))

(defun end-io-wait-1 (p)
  (loop for child in (children-of-thread p)
	do (end-io-wait-1 child)
	when (eq (reason-for-state-of-thread child) :io-wait)
	  do
	    #+development
	    (when (eq root-thread child)
	      (error "Never make the root thread run!"))
	    (set-state-of-thread child :runnable :end-io-wait)))

(defun shutdown-thread-tree ()
  (loop for child = (first (children-of-thread root-thread))
	while child
	do (shutdown-thread-tree-1 child)))

(defun shutdown-thread-tree-1 (thread)
  (loop for child = (first (children-of-thread thread))
	while child
	do (shutdown-thread-tree-1 child))
  (thread-kill thread))











;;;; C Interface for Sockets.





#| ;; done now with  def-direct-c-function, which itself has to die, but.
(lcl:def-foreign-function (g2ext-tcpip-connect (:return-type :signed-32bit))
    (host :string)
    (port :signed-32bit))

(lcl:def-foreign-function (g2ext-tcpip-close (:return-type :signed-32bit))
    (socket :signed-32bit))

(lcl:def-foreign-function (gw-tcpip-connection-check
			    (:return-type :signed-32bit))
    (socket :signed-32bit))

(lcl:def-foreign-function (gw-socket-data-available-p
			    (:return-type :signed-32bit))
    (socket :signed-32bit))

(lcl:def-foreign-function (gw-socket-write (:return-type :signed-32bit))

    (socket-number :signed-32bit)
    (buffer :string)
    (start :signed-32bit)
    (end :signed-32bit))

;; Note you must take great care to avoid passing this a fill-pointer
;; string.

(lcl:def-foreign-function (gw-socket-poll-status
			    (:return-type :signed-32bit))
    (socket-number :signed-32bit))

(lcl:def-foreign-function (gw-socket-read (:return-type :signed-32bit))
    (socket-number :signed-32bit)
    (buffer :string)
    (max :signed-32bit))

(lcl:def-foreign-function (gw-get-peer-name (:return-type :signed-32bit))
    (socket-number :signed-32bit)
    (buffer :string)
    (max :signed-32bit))

(lcl:def-foreign-function (gw-get-peer-address-string (:return-type :signed-32bit))
    (socket-number :signed-32bit)
    (buffer :string)
    (max :signed-32bit))
|#





;;;; Sockets


;;; Sockets usually sockets in the O/S communications layer.  They are
;;; parts of threads.  We register them with GSI as things we want to
;;; watch when it sleeps so it will awaken if something happens upon one
;;; of them.  When GSI returns control to our top level loop we call
;;; the socket-poll method on each socket, and that can then choose to
;;; reschedule the thread.

;;; `Issue-with-socket?' is nil indicating the socket is entirely
;;; wonderful.  Symbols appear in this slot to indicate an enumerated
;;; set of known states.  Integers appear to indicate an unknown issue
;;; has occured.  The integer being the platform specific error code.
;;; The integer -1 may occur.

;;; `retry-counter-of-socket' is proably not accurate yet, but it
;;; attempts to count how many times we have attempted I/O and told
;;; to backoff.

;;; The enumerated symbolic values are:
;;;   :born
;;;   :uninstalled
;;;   nil -- i.e. open and presumed functional
;;;   :closed
;;;   ...

(def-structure (weblink-socket)
  (thread-of-socket current-thread)
  (number-of-socket nil)
  (issue-with-socket? :born)
  (retry-counter-of-socket 0))

(defun reclaim-sockets (list-of-sockets)
  (loop for s = (gensym-pop list-of-sockets)
	while s
	do (reclaim-structure s)))

;;; `All-sockets' is the master list of all sockets. These
;;; are polled.

(def-system-variable all-sockets gthread nil)

;; `note-issue-with-socket' see slot documentation

(defun note-issue-with-socket (socket issue)
  ;; Record only the first issue noticed.
  (unless (issue-with-socket? socket)
    (cond
      ;; Don't store -1 if we can avoid it, try errno.
      ((and (eq -1 issue)
	    (number-of-socket socket))
       (socket-poll-status socket)
       ;; That might set the issue.
       (unless (issue-with-socket? socket)
	 (setf (issue-with-socket? socket) -1)))
      
      ;; Just count issues that imply blocking.
      ((or (eq errno-would-block issue)
	   (eq errno-again issue))
       (incff (retry-counter-of-socket socket))
       #+development
       (bridge-log "Retry scheduled ~D" (retry-counter-of-socket socket)))

      ;; Record it, it's new.
      (t
       (setf (issue-with-socket? socket) issue)))
    (when (issue-with-socket? socket)
      (thread-enqueue-event current-thread :socket-issue))))

(defun peer-name-of-socket (socket)
  (c-get-peer-hostname (number-of-socket socket)
		    current-foreign-string-pad
		    10000)
  (make-text-string-from-c-string-in-foreign-string-pad))

(defun peer-address-string-of-socket (socket)
  (c-get-peer-address-string
    (number-of-socket socket)
    current-foreign-string-pad
    10000)
  (make-text-string-from-c-string-in-foreign-string-pad))

(defun socket-poll-status (socket)
  (let ((result (gw-socket-poll-status (number-of-socket socket))))
    (cond
      ((=f 0 result) nil)
      (t
       (note-issue-with-socket socket result)
       result
	 ))))


;;; `Socket-install' is called from the socket create methods. It stores the
;;; socket number, pushes the socket into the current-thread, and pushs the
;;; socket into the set of all sockets..  Finally it returns the socket.

(defun socket-install (socket socket-number)
  (setf (issue-with-socket? socket) nil)
  (setf (number-of-socket socket) socket-number)
  (gsi-watch-fd (number-of-socket socket))
  (g2ext-tcpip-set-nodelay (number-of-socket socket))
  (gensym-push socket (sockets-of-thread current-thread))
  (gensym-push socket all-sockets)
  socket)

(defun socket-deinstall (socket)
  (let ((thread (thread-of-socket socket)))
    (setf (sockets-of-thread thread)
	  (delete-gensym-element socket (sockets-of-thread thread)))
    (setf all-sockets
	  (delete-gensym-element socket all-sockets))
    (gsi-unwatch-fd (number-of-socket socket))
    (setf (issue-with-socket? socket) :uninstalled)
    socket))


(def-generic-slow-method socket-close-it (weblink-socket))

(def-slow-method socket-close-it (weblink-socket)
  (socket-deinstall weblink-socket)
  (let ((errcode (g2ext-tcpip-close (number-of-socket weblink-socket))))
    (unless (=f 0 errcode)
      (note-issue-with-socket weblink-socket errcode))))

#+development
(def-gtrace socket-traffic "Trace what's happening at the socket level.")
    
;;; `Socket-write-region' attempts to move the found between two marks out on a
;;; given socket.  It moves the from-mark forward as it succeeds.  If the socket
;;; is dead, this is a noop.  If the socket blocks, this will return at that
;;; point.  This has no useful return value.

(defun socket-write-region (socket from-mark to-mark)
  (let ((from-pos (position-of-mark from-mark))
	(to-pos (position-of-mark to-mark))
	text-of-chunk?
	(number-of-socket (number-of-socket socket)))
    (with-mark (chunk-left-mark from-mark)
      (with-mark (chunk-right-mark chunk-left-mark)
	(loop for chunk-left = from-pos then chunk-right
	      as chunk-right = (minf to-pos (+f chunk-left 5000))
	      as chunk-size = (-f chunk-right chunk-left)
	      while (<f 0 chunk-size) ;; Or we get frustrated...
	      do
	  (mark-move chunk-right-mark chunk-size)
	  (when text-of-chunk? (reclaim-gensym-string text-of-chunk?))
	  (setf text-of-chunk?
		(copy-text-between-marks chunk-left-mark chunk-right-mark))
	  ;; 1. Preflight the socket.
	  (socket-poll-status socket)
	  (when (eq errno-would-block (issue-with-socket? socket))
	    (setf (issue-with-socket? socket) nil)
	    (return nil))
	  (when (issue-with-socket? socket)
	    (return nil))
	  ;; 2. Write.
	  #+development
	  (with-tracing (socket-traffic)
	    (dmesg "~&Socket writing ~S" text-of-chunk?))
	  (let*
	      ((c-safe-text (make-text-safe-for-c text-of-chunk?))
	       (result
		 (gw-socket-write
		   number-of-socket
		   c-safe-text
		   0 chunk-size)))
;	    (print (list result chunk-size (subseq c-safe-text 0 chunk-size)))
	    ;; If we wrote some bytes, advance the from-mark
	    (when (<=f 0 result)
	      (mark-move from-mark result))
	    
	    ;; 3. "Post flight" the socket
	    (cond
	      ;; Did we get an error?
	      ((<f result 0)
	       (let ((errno (gw-fetch-errno)))
		 (when (or (=f errno-would-block errno)
			   (=f errno-again errno))
		   (return nil))
	       (note-issue-with-socket socket errno)))
	      (t
	       (socket-poll-status socket)
	       (when (issue-with-socket? socket)
		 (return nil))))

	    ;; Bail out at the first sign of blocking.
	    (unless (=f result chunk-size)
	      (return nil))
	    (mark-set chunk-left-mark chunk-right-mark)
	    ))))
    (when text-of-chunk? (reclaim-gensym-string text-of-chunk?))))

;; This should see straight to the fragments strings, and it should compute
;; offsets right into them.  A macro churning <string> <from> <to> exported
;; by buffer.lisp would be just the ticket.




;;;; Development only Process Cleanup

;;; In development we (launch-gsi) to start da thing, and
;;; we - usually - use :A in the debugger to stop da thing.
;;; Most data structures are discarded into garbage at that
;;; point because the process bindings are lost.  But, things
;;; that are O/S data structures are left hanging.  Of course,
;;; in a real process we would let those cleanup by exiting
;;; the process.  Inside of Lisp - on the other hand - we
;;; have to clean things up ourself.  So we have a development
;;; only hook setup here.

;; See also shutdown-system-for-exit in G2.

;;; `lisp-process-cleanups' holds a list of functions to fire
;;; we run-system-process unwinds out of a system process.

(defvar lisp-process-cleanups nil)

;;; `Cleanup-gw-lisp-process' is invoked from run-system-process as it unwinds
;;; out of a running "system process".

;;; `Defun-for-lisp-process-cleanup'

#+development
(defmacro defun-for-lisp-process-cleanup (name () &body body)
  `(progn
     (pushnew ',name lisp-process-cleanups)
     (defun ,name ()
       ,@body)))


;;; `icp-lisp-process-cleanup'

#+development
(defun-for-lisp-process-cleanup lisp-process-cleanup-for-icp ()
  (loop for icp-socket in active-icp-sockets
	do (close-network-handle-in-icp-socket icp-socket)))

;;; `thread-lisp-process-cleanup'

#+development
(defun-for-lisp-process-cleanup lisp-process-cleanup-for-all-sockets ()
  (loop while all-sockets
	repeat 30 ;; Unwinding, so no telling how weird things are.
	doing
    (socket-close-it (first all-sockets)))
  (when all-sockets
    (format t "~&Unable to force all sockets to close.")))






;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PLAYER

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author: Ben Hyde



;;;; Introduction to Testing Player's Evaluator.

;;; The code in this file exists to allow hand written scripts to simulate user
;;; interaction with G2.  These are used for testing.  There is no suport for
;;; recording these scripts automaticly say by monitoring an actual user's
;;; interaction.

;;; If all you want to do is write test scripts and then run them you should
;;; read the section "Player's External Interface," which providse the routines
;;; used to start and stop the player.  Then read the file
;;; MA:>player-tests>examples.lisp which contains a series of simple example
;;; test scripts.

;;; How this interpreter works.

;;; The player is an odd kind of interpreter.  It is used to feed events into
;;; the event stream of an application.  This is done by having poll-workstation
;;; call poll-player when ever it needs fresh events.  Poll player then
;;; interprets the current player script until it generates an event and
;;; suspends.  The player then suspends execution (packing its bags) and returns
;;; to whom ever polled it.  The next time it is polled it will pick up where it
;;; left off.

;;; Enabling this requires that the interpreter maintain all of its state in
;;; stacks outside those of the application that polls it.  The language this
;;; evaluator handles is a tiny subset of common lisp; i.e. function
;;; calling, if, progn, defun, and tagbody are supported.

;;; This evaluator has two stacks, one is the usual value stack.  The other is
;;; known as the control stack.  The control stack is used in place of a program
;;; counter.  Analagous to a real computer's fetching an instruction from the
;;; program counter, the player fetchs by poping the top off the control stack.
;;; The control stack implements all special forms, i.e. it maintains the
;;; lexical and dynamic contours of the evaluated program.  For example to
;;; implement a tagbody an entry is placed in the control stack that points to
;;; the tagbody and the current statement in that tagbody.  A go is implement by
;;; searching the control stack for a tag body containing that label.

;;; This is all very similar to the way a postscript interpreter works.

;;; Like a lisp evalutor much or most of the dispatching to discover how to
;;; handle individual forms encountered during evaluation is stored in the
;;; symbol-function of various symbols.  The place player-symbol-function is
;;; used to play this role.

;;; The player is contrived to avoid leaking.  All cones are stored in the
;;; PLAYER cons pool.  Some forms that appear on the control stack are reclaimed
;;; by the code that executes them, these are known as player instructions.
;;; while other forms are not reclaimed by executing them, presumable because
;;; they are part of the program's source. 

;;; For example if a progn appears in the user's program it will be placed on
;;; the control stack when the time comes to execute it.  The handler for a
;;; progn then pushs a player instruction into the stack to actually step thru
;;; the execution of the progn.  In a sense this instruction becomes the program
;;; counter that knows how to sweep over the progn.  Each time the instruction
;;; is executed, i.e.  popped off the control stack, and its handler will be
;;; called and that handler will then either push the instruction back into the
;;; stack, or reclaim the instruction.  Of course, the instruction will push the
;;; next statement in the progn into the control stack.

;;; The contours that a Lisp evaluator requires are implemented using the
;;; control stack as well.  Tagbodies, for example, create an entry in the
;;; control stack that the (go <label>) can search for to find the label to go
;;; to.  Such constructs can, of course, create oportunities for nonlocal exits
;;; (see bugs below).

;;; Lexical variable contours are marked in the control stack with an
;;; instruction to unbind the variables created in that contour.  A separate
;;; alist is maintained that contains the current lexical bindings.  Currently
;;; only let* and simple lambda lists are supported.  The lambda lists do not
;;; support any lambda list keywords.  (see bugs below).

;;; Current Bugs of the Implementation.

;;; While this yearns to be common lisp, it is very limited in scope.  Script
;;; writers will find these limits are surprisingly easy to live with.

;;; Block, and unwind contours are not currently supported.  None local exits in
;;; tagbodies will leak.  All lexical variables are implicitly declared special.

;;; No macros are supported.  Some "instructions" don't match the definition
;;; above, i.e.  that they always reclaim thier own storage.  For example PROGN
;;; is implemented as an instruction, to allow the handler to get the entire
;;; form, but it never reclaims its storage.

;;;; The Player Evaluator's Dynamic Global State



(defconser player)



;;; `Reclaim-tree-and-atoms' does just that.  Someday it will handle floats.

(defun reclaim-player-tree-and-atoms (tree)
  (reclaim-atoms-in-tree tree)
  (reclaim-player-tree tree))


(defun reclaim-atoms-in-tree (tree)
  (cond
    ((consp tree)
     (reclaim-atoms-in-tree (car tree))
     (reclaim-atoms-in-tree (cdr tree)))
    ((text-string-p tree)
     (reclaim-text-string tree))))



;;; `Copy-tree-and-atoms-using-player-conses' does just that.  It is used
;;; to assure that a tree passed over ICP is moved out of ICP owned pools
;;; and into PLAYER owned pools.  This will someday do floats too.

(defun copy-tree-and-atoms-using-player-conses (tree)
  (cond
    ((consp tree)
     (player-cons (copy-tree-and-atoms-using-player-conses (car tree))
		  (copy-tree-and-atoms-using-player-conses (cdr tree))))
    ((text-string-p tree)
     (copy-text-string tree))
    (t tree)))


;;; The global state of the player consists of these system variables.
;;;    player-state player         -- one of paused, running.
;;;    player-control-stack        -- the subprogram stack.
;;;    player-value-stack          -- the register stack.
;;;    player-current-instruction  -- the program counter.
;;;    player-lexical-binding-stack
;;;    player-definition-stack     -- global definitions
;;;    player-location-stack       -- screen locations, a list of (# . #) pairs
;;;    player-named-locations      -- an alist of named locations (name . ( # . #))
;;; All data structures in these variables are constructed from player conses.

(def-system-variable player-state player 'paused)
(def-system-variable player-control-stack player ())
(def-system-variable player-value-stack player ())
(def-system-variable player-current-instruction player)
(def-system-variable player-lexical-binding-stack player ())
(def-system-variable player-definition-stack player ())
(def-system-variable player-location-stack player ())
(def-system-variable player-named-locations player ())

(defmacro with-player-executing (&body body)
  `(catch 'suspend-player
     ,@body))

(defun-void suspend-player ()
  (throw 'suspend-player nil))

(defun player-symbol-value (symbol)
  (let ((lexical-binding (assq symbol player-lexical-binding-stack)))
    (if lexical-binding 
	(cdr lexical-binding)
	(symbol-value symbol))))






;;;; The Player's Linkage into G2's Event Stream



(def-system-variable player-target-gensym-window-g2-struct? player nil)
(def-system-variable best-text-matched-by-player player nil)
(def-system-variable player-mouse-x player 0)
(def-system-variable player-mouse-y player 0)
(def-system-variable last-player-mouse-x player 0)
(def-system-variable last-player-mouse-y player 0)
(def-system-variable last-player-event-time player 0)
(def-system-variable player-pace player 2)  ; in 60 sec ticks on lispm?

(defun set-best-text-matched-by-player (text)
  (when best-text-matched-by-player
    (reclaim-text-string best-text-matched-by-player))
  (setq best-text-matched-by-player text))

(defun current-player-event-time ()
  (c-x11-last-event-time
   (native-window?
    player-target-gensym-window-g2-struct?)))

(defun player-generate-event (event-type)
  (when (or (not (= last-player-mouse-x player-mouse-x))
	    (not (= last-player-mouse-y player-mouse-y)))
    (setf last-player-mouse-x player-mouse-x)
    (setf last-player-mouse-y player-mouse-y)
    (let* ((type-of-current-workstation-window
	     (type-of-gensym-window player-target-gensym-window-g2-struct?))
	   (current-workstation-native-window?
	     (native-window?
	       player-target-gensym-window-g2-struct?)))

      ;; Must call the low-level position setter, which does not require a
      ;; current-workstation. -fmw, 7/1/94
      (set-position-of-mouse-1 player-mouse-x player-mouse-y)))

  (with-drawing-trace (player)
    (format t "Player: ~a at ~d,~d~%" (key-name event-type) player-mouse-x player-mouse-y))

  (enqueue-local-event 
    (native-window? player-target-gensym-window-g2-struct?)
    event-type
    player-mouse-x player-mouse-y
    (setf last-player-event-time (current-player-event-time)))
  (maybe-schedule-service-workstation nil t)
  (suspend-player))

(defun player-generate-event-and-suspend (event-type)
  (player-generate-event event-type)
  (suspend-player))

(defun player-error (error-string &optional arg)
  (progn ;; Note A
    #+(and development (not SymScale))
    (cerror "Pause Player" error-string arg)
    #-(and development (not SymScale))
    (let ((error-string (tformat-text-string error-string arg)))
      (notify-user-at-console "~&Player Error: ~A~%" error-string)
      (reclaim-text-string error-string)))
  (pause-player)
  (suspend-player))

;; Note A: cerror isn't supported by some Lisp->C translators.





;;;; The Player Evaluator's Static State: Symbol-function, Macro-function, etc.



;;; `Player-symbol-function' is the place where we store the definitions of
;;; functions that are evaluated using by the player evaluator.  Player-symbol-function
;;; is to symbol-function as player-eval is to eval.

(defmacro player-symbol-function (name)
  `(get ,name 'player-symbol-function))


;;; 'Set-player-symbol-function' provides a nonmacro way to set the player
;;; symbol function place of a symbol so this can be done via ICP.

(defun set-player-symbol-function (name new-value)
  (with-permanent-cons-creation
    (setf (player-symbol-function name) 
	  (if *there-is-a-current-kb?*
	      (copy-tree-and-atoms-using-player-conses new-value)
	      new-value))))

;;; `Player-macro-function' is to macro-function as player-eval is to eval, i.e.
;;; it is the place where the function that implements a macro or special form
;;; is stored for the player evaluator.

(defmacro player-macro-function (name)
  `(get ,name 'player-macro-function))



;;; `Player-mark-definitions' pushs a new entry into the player defintion
;;; stack.  This entry will then accumulate all functions defined subsequently
;;; defined.  This enables the space used by these definitions to be reclaimed.

(defun player-mark-definitions (name)
  (player-push (player-cons name ()) player-definition-stack))



;;; `Player-release-definition-stack' pops off a named entry on the player definition
;;; stack and proceeds to undefine all the definitions made in since that entry
;;; was inserted.  If name is T then all definitions are released.

(defun player-release-definitions (name)
  (unless (or (eq name T)
	      (assq name player-definition-stack))
    (error "Player-release-definitions is able to find matching mark."))
  (loop as (entry-name . definition-records) = (player-pop player-definition-stack)
	while entry-name
	do
    (loop for (definition-kind . definition-name) in definition-records
	  do
      (case definition-kind
	(defun
	 (undefine-player-symbol-function definition-name))))
    (unless (eq T name)
      (when (eq entry-name name)
	(return nil)))))



;;; `player-record-definition' will record into the player-definition-stack
;;; a record of the definition of a name.  This allows the space allocated
;;; by that definition to be reclaimed.  This mechinism only works inside
;;; of a G2 process.  All definitions made outside the g2 process will
;;; not be reclaimed by a player-release-defintions.

(defun player-record-definition (kind name)
  (when (and (boundp 'player-definition-stack)
	     player-definition-stack)
    (player-push (player-cons kind name) (cdr (first player-definition-stack)))))



;;; 'Def-player-instruction' is used to define the most primitive handlers for forms
;;; that appear on the control stack.  When these forms are encountered on the control
;;; stack the player evaluator will call these handlers, passing responsiblity for
;;; the conses in thier top level forms off to the handler.

;;; These handlers often modify the form, insert themselfs back into the control stack and
;;; then place some number of additional forms into the control stack.

(defmacro def-player-instruction (name args &body body)
  (let ((instruction-function (intern (format nil "~:@(PLAYER-INSTRUCTION-~S~)" name))))
    `(progn
       (defun ,instruction-function ,args ,@body)
       (setf (player-macro-function ',name)
             ',instruction-function)
       ',name)))



;;; 'Def-player-lisp-function' imports a lisp function into the name space of the
;;; player evaluator.  It sometimes useful to change the name of the function, for example
;;;   (def-player-lisp-function text-visible-p player-find-graphic-element-containing-text)

(defmacro def-player-lisp-function (name &optional (real-name name))
  `(setf (player-symbol-function ',name) ',real-name))



;;; `Defun-for-player' is the principle means of defining testing scripts.  The argument
;;; lists to these functions may contain no lambda list keywords.  The only special forms
;;; currently supported are: QUOTE, PROGN, TAGBODY, IF, and LET*.

;;; The body of these functions are moved into copied into space owned by the player evaluator.
;;; This space maybe reclaimed using the routines mark-player-definitions, and 
;;; release-player-definitions.

(defmacro defun-for-player (name args &body body)
  (assert (null (intersection args  '(&optional &rest &key &aux 
						&allow-other-keys
						&body &whole
						&environment))) () 
	  "Lambda list keywords are not supported in player functions.")
    `(progn
       (undefine-player-symbol-function ',name)
       (player-record-definition 'defun ',name)
       (set-player-symbol-function
	 ',name
	 '(player-function
	    ,args
	    (progn ,@body)))
       ',name))

;; Doesn't support the implicit block yet.

(declare-funcallable-symbol undefine-player-symbol-function)
(declare-funcallable-symbol player-record-definition)
(declare-funcallable-symbol set-player-symbol-function)
(declare-funcallable-symbol player-function)

;;; `Undefine-player-symbol-function' removes a symbol's definition from
;;; the player's name space.  This almost reclaims all the space allocated
;;; for the definition, but it can't reclaim the space used for the 
;;; property list backbone.

(defun undefine-player-symbol-function (name)
  (let ((definition (player-symbol-function name)))
    (when (and definition
	       *there-is-a-current-kb?*)
      (reclaim-player-tree-and-atoms definition))
                                        ;(remprop name 'player-symbol-function)))
    (setf (getf (symbol-plist name) 'player-symbol-function) nil)))

;; Oviously we should move the player-symbol-function place off
;; the symbol property list so we can reclaim that space.

;; Remprop will not be supported in GLT -- instead we null the value.
;; (ghw 2/23/95)




;;;; The Player Evaluator 



;;; `Poll-player' is called by poll-workstation to see if the player 
;;; can generate any events for it.

(defun-allowing-unwind poll-player ()
  (when player-target-gensym-window-g2-struct?
    (when (and (eq player-state 'running)
	       (<=f 
		 (+f last-player-event-time player-pace)
		 (current-player-event-time)))
      (with-player-executing
	;; let it do two dozen instructions attempting 
	;; to create an instruction and suspend.
	(loop for i from 0 upto 20
	      do
	  (unless player-control-stack (return nil))
	  (execute-player))))))



(defun execute-player ()
  (let ((player-current-instruction (player-pop player-control-stack)))
    (typecase player-current-instruction
      (null
       (player-push player-current-instruction player-value-stack))
      (symbol
       (player-push (player-symbol-value player-current-instruction) player-value-stack))
      (atom
       (player-push player-current-instruction player-value-stack))
      (list
       (let ((head (first player-current-instruction))
             handler)
         (cond
           ((setq handler (player-macro-function head))
            (funcall handler player-current-instruction))
           ((setq handler (player-symbol-function head))
	    (do-player-funcall handler))
           (T
            (player-error "undefined player function ~S" player-current-instruction)))))))
  ;(format t "~%<execute-player:~%  ~S~%  ~S" player-control-stack player-value-stack)
  )



(defun do-player-funcall (handler)
  (cond
    ;; Very simple call sites.
    ((loop for arg-form in (rest player-current-instruction)
	   do (unless (atom arg-form) (return nil))
	   finally (return t))
     (loop
       with call-site = ()
       for arg-form in (rest player-current-instruction)
       do (player-push (if (symbolp arg-form)
			   (player-symbol-value arg-form)
			   arg-form) call-site)
       finally 
	 (setf call-site (nreverse call-site))
	 (return (player-do-call-finally handler call-site))))
    ;; Real call sites, i.e. where one of the args' computations might suspend.
    (T
     (player-push
       (player-list 'do-call player-current-instruction 1 (length player-current-instruction))
       player-control-stack))))



(def-player-instruction do-call (form)  ; the ultimate special form
  (let ((call (second form))
        (args-so-far (third form))
        (total-args  (fourth form))
        (call-site ()))
    (cond
      ((= args-so-far total-args)
       (loop for i from 1 below total-args
             do (player-push (player-pop player-value-stack) call-site))
       (player-do-call-finally (player-symbol-function (first call)) call-site)
       (reclaim-player-list form))
      (T
       (setf (third form) (+ 1 args-so-far))
       (player-push form player-control-stack)
       (player-push (nth args-so-far call) player-control-stack)))))


(defun player-do-call-finally (handler call-site)
  (when call-site
    (player-push 
      (player-list 'reclaim-player-tree call-site)
      player-control-stack))
  (typecase handler
    (list 
     (player-parse-arguments (second handler) call-site)
     (player-push (third handler) player-control-stack))
    (symbol 
     (player-push (apply handler call-site) player-value-stack))))



;;; `player-parse-arguments' creates the lexical contour for containing
;;; the function's parameters.  It places an unbind instruction on the
;;; stack to clear this contour, and it pushs into the lexical binding
;;; stack bindings for each of the parameters.

;;; Currently no lambda list keywords are supported.

(defun player-parse-arguments (lambda-list actuals)
  (cond ((and (null lambda-list)
	      (null actuals))
	 ;; All done.
	 )
	((not (= (length actuals) (length lambda-list)))
	 (player-error "Player call failed since actual parameters don't match lambda list"))
	(T
	 (player-push 
	   (player-list 'unbind player-lexical-binding-stack)
	   player-control-stack)
	 (loop for parameter-name in lambda-list
	       for actual in actuals
	       do (player-push 
		    (player-cons parameter-name actual)
		    player-lexical-binding-stack)))))






;;;; Player Special Form Handlers



(def-player-instruction quote (form)
  (player-push (second form) player-value-stack))



(def-player-instruction progn (form)
  (player-push (player-list 'progn-1 1 (- (length form) 1) form) player-control-stack))

(def-player-instruction progn-1 (form)
  (let* ((index (second form))
         (max (third form))
         (statements (fourth form))
         (statement (nth index statements)))
    (cond
      ((= index max)
       (reclaim-player-list player-current-instruction))
      (t
       (player-pop player-value-stack)
       (setf (second form) (1+ index))
       (player-push form player-control-stack)))
    (player-push statement player-control-stack)))




(def-player-instruction if (form)
  (let ((test-form (second form))
	(then-form (third form))
	(else-form (fourth form)))
    (player-push else-form player-control-stack)
    (player-push then-form player-control-stack)
    (player-push '(if-1) player-control-stack)
    (player-push test-form player-control-stack)))

(def-player-instruction if-1 (form)
  (declare (ignore form))
  (let ((then-form (player-pop player-control-stack))
        (else-form (player-pop player-control-stack)))
    (if (pop player-value-stack)
      (player-push then-form player-control-stack)
      (player-push else-form player-control-stack))))
    



(def-player-instruction tagbody (form) ; untested
  (player-push 
    (player-list 'player-tagbody-1 1 (length form) form)
    player-control-stack))

(def-player-instruction player-tagbody-1 (form) ; untested
  (let* ((index (second form))
         (max (third form))
         (statements (fourth form))
         (statement-or-tag (nth index statements)))
    (cond
      ((= index max)
       (reclaim-player-list player-current-instruction))
      (t
       (player-pop player-value-stack)
       (setf (second form) (1+ index))
       (player-push form player-control-stack)))
    (unless (symbolp statement-or-tag)
      (player-push statement-or-tag player-control-stack))))

(def-player-instruction go (form)
  (loop 
    with label = (second form)
    for new-player-control-stack on player-control-stack
    as control-form = (first new-player-control-stack)
    as head = (first control-form)
    when (eq head 'player-tagbody-1)
    do
    (let* ((statements (rest (fourth control-form)))
           (position (position label statements)))
      (when position
        (setf (second control-form) (+f position 1))
        (setf player-control-stack new-player-control-stack) ; LEAK! ?? ... arch. flaw.
        (return nil)))
    finally
    (player-error "Player found no label ~S to go to in enclosing tagbodies." label)))

;; This is a real problem.  The entire control stack must have a simple reclaimation
;; stratagy.  The other lexical contours and macro expand are in this nest of worms too.


;;; `let*-bind, a player-instruction', is does the actual work of binding
;;; each variable as we enter a lexical scope.  It takes one argument, a
;;; list of lexical bindings that are waiting to be bound.  The first in
;;; this list is always having its init form evaluated.  These pending
;;; bindings are of the form ( <lexical-variable> . <init-form> )  When
;;; ever this instruction is executed it will find the result of the
;;; top most form on the value stack.  It then creates the new binding
;;; in the lexical bindings stack and starts evaluating the next
;;; of the pending bindings.  When it has done all the pending bindings
;;; it stops inserting itself into the control stack.

(def-player-instruction let*-bind (form)
  (let ((binding-in-progress (first (second form))))
    ;; Set the binding of the current binding in progress.
    (setf 
      (cdr binding-in-progress)
      (player-pop player-value-stack)))
  ;; Make this binding visible.
  ;; Lucid isn't dependable
  ;;(rotatef
  ;;  (cdr (second form))
  ;;  player-lexical-binding-stack
  ;;  (second form))
  (let ((temp1 (cdr (second form)))
	(temp2 player-lexical-binding-stack)
	(temp3 (second form)))
    (setf (cdr (second form)) temp2)
    (setf player-lexical-binding-stack temp3)
    (setf (second form) temp1)
    nil)
  ;; Either
  ;; 1. Eval the next binding's initial value.
  ;; 2. or exit finish let*-binding.
  (cond
    ((second form)
     (player-push form player-control-stack)
     (player-push 
       (cdr (first (second form)))
       player-control-stack))
    (T
     (reclaim-player-list form))))



;;; `unbind, a player instruction', unwinds the lexical binding
;;; stack back to its argument, reclaiming the player conses
;;; containing the bindings, as well as the backbone of the
;;; stack.

(def-player-instruction unbind (form)
  (let ((desired-player-lexical-binding-stack (second form)))
    (loop until (eq desired-player-lexical-binding-stack
		    player-lexical-binding-stack)
	  do
      (reclaim-player-cons (first player-lexical-binding-stack))
      (player-pop player-lexical-binding-stack)))
  (reclaim-player-list form))




;;; `let*, a player instruction' packs into the controls stack
;;; these forms.
;;;    (unbind C)
;;;    (progn-1 2 (let* ...))
;;;    (let*-bind D)
;;;    <first-init-form>
;;; Where C is the current top of the lexical binding stack
;;; Where D is a normalized version of the binding spec.

(def-player-instruction let* (form)
  (let ((binding-specs (second form)))
    (player-push 
      (player-list 'unbind player-lexical-binding-stack)
      player-control-stack)
    (player-push
      (player-list 'progn-1 2 (length form) form)
      player-control-stack)
    (player-push
      (player-list 
	'let*-bind
	(loop for binding-spec in binding-specs
	      as lexical-variable-name 
		 = (if (symbolp binding-spec)
		       binding-spec
		       (car binding-spec))
	      as lexical-variable-init-form
		 = (if (symbolp binding-spec)
		       nil
		       (second binding-spec))
	      collect (player-cons
			lexical-variable-name
			lexical-variable-init-form)))
      player-control-stack)
    (player-push
      (cdr (first (second (first player-control-stack))))
      player-control-stack)))


(def-player-lisp-function wait player-wait)

(defun player-wait (how-many-ticks)
  (player-push 
    (player-list 'wait-until (+f how-many-ticks (get-fixnum-time)))
    player-control-stack)
  nil)

(def-player-instruction wait-until (form)
  (let ((wake-up-time (second form)))
    (cond
      ((<= wake-up-time (get-fixnum-time))
       (reclaim-player-list form))
      (T
       (player-push form player-control-stack)
       (suspend-player)))))




(def-player-instruction reclaim-player-tree (form)
  (reclaim-player-tree-function form))

(defun reclaim-player-tree-function (tree)
  (reclaim-player-tree tree))







;;;; Player's Interface into G2's State to it Can "See" the Screen



;;; There are two ways of "seeing" the cool way, and the not so cool way.
;;; The cool way is to divert the drawing ICP messages, while refreshing
;;; the screen, and to note the appearance of drawing that matches what
;;; we are looking for.

;;; The not so cool way is to walk the workstation/pane/image-plane/workspace/block
;;; tree and find the thing we are looking for.  This second technique is
;;; much more invasive, but dependable.  If, when drawing, G2 bound sufficent
;;; semantic information into the dynamic state then we could use the cool way
;;; more often.  For example to find a menu item with a given text we need
;;; to use the uncool way since we can't tell a menu item from other text when
;;; using the cool technique.

;;; Conflict resolution is a general hard problem in this kind of stuff.  When
;;; looking for the text "ok" on the screen is "logbook" a good awnser?  The
;;; code the follows is too stupid about this stuff.  It prefers short text
;;; that matches to long text that matches.  It prefers text near the front
;;; of the screen to test toward the back.

;;; The cool way of drawing has trouble with those rules.  Drawing order is a
;;; little volitile in G2 today.  Right now we draw the image-planes from front
;;; to back and the blocks in them from front to back.  Soon we will draw the
;;; the blocks back to front.  As which point... more work.

(defun player-center-of-rectangle (left top right bottom)
  (values
    (halff (+f left right))
    (halff (+f top bottom))))


;;; `Icp-player-message-handler-array' is bound into icp-printing-message-handler-array
;;; when we are looking at the screen the cool way.  It contains a NOP handler
;;; `default-player-handler-for-icp-messages' except for those drawing messages that
;;; might be of interests to our eyes.

(defvar icp-player-message-handler-array
	(let ((result 
		(make-array #.(icp-message-handler-array-size) 
		    :initial-element 'default-player-handler-for-icp-messages)))
	  (setf (svref result (icp-message-type-code 'add-from-line-of-text-to-current-window))
		'player-handler-for-add-from-line-of-text-to-current-window)
	  result))

(defun default-player-handler-for-icp-messages (&optional a b c d e f g h i j k l m n o p)
  (declare (ignore  a b c d e f g h i j k l m n o p)))


;;; When we are looking for a particular fragment of text we use these specials
;;; to communicate between the top level search and the low level bottleneck
;;; routine.  We look for the text bound in `current-text-focus-for-eyes?,'
;;; using `current-score-of-best-match-for-eyes' so we find the shortest text
;;; that matches, the center of the text found is reported in
;;; `current-{x,y}-for-eyes?.

(defvar current-score-of-best-match-for-eyes)
(defvar current-best-match-for-eyes nil)
(defvar current-text-focus-for-eyes? nil)
(defvar current-x-for-eyes? nil)
(defvar current-y-for-eyes? nil)


;;; The special variable `lower-match-rank-for-player-eyes-p' is globally bound
;;; to nil, but can be specially bound in certain cases where it's desireable
;;; that the bottleneck rank text matches lower.  The only use found for this so
;;; far is, when we draw the title bar text (see module DRAW).  The text is by
;;; default (as of 6.0b1, sources pending 3/30/01) the class name printed the
;;; same way as a menu header.  It's desireable that the text match, but that be
;;; given lower ranking than other text, mostly for compatibility with past
;;; player/QA tests.

;;; When lower-match-rank-for-player-eyes-p is true, and a match occurs, the
;;; ranking is lowered by increasing the "score" that is the value of
;;; current-score-of-best-match-for-eyes.

(defvar lower-match-rank-for-player-eyes-p nil)


;;; `Player-handler-for-add-from-line-of-text-to-current-window' implements the
;;; bottleneck routine to catch and see text.  It implements the conflict
;;; resolution stratagy outlined above.  This also contains code to support
;;; the development only function show-all-text-on-screen.

(defun player-handler-for-add-from-line-of-text-to-current-window (subtract-instead?	; i.e. a subtract-instead?
								   clipped-left-edge	; i.e. a coordinate
								   clipped-top-edge	; i.e. a coordinate
								   clipped-right-edge	; i.e. a coordinate
								   clipped-bottom-edge	; i.e. a coordinate
								   text-line	; i.e. a text-line
								   word-spacing	; i.e. a word-spacing
								   font-map	; i.e. a font-map
								   color-difference	; i.e. a color-difference
								   x-scale	; i.e. a x-scale
								   y-scale	; i.e. a y-scale
								   left-edge-of-line-of-text-in-window	; i.e. a coordinate
								   baseline-in-window	; i.e. a coordinate
								   )
  (declare (ignore subtract-instead?
	     word-spacing font-map
	     color-difference x-scale y-scale
	     left-edge-of-line-of-text-in-window baseline-in-window
	     ))
  (when current-text-focus-for-eyes?
    (cond
      #+development
      ((eql :show current-text-focus-for-eyes?)
       (print text-line))
      ((and (text-string-search+
	      current-text-focus-for-eyes?
	      text-line	; need case-insensitive test
	      :test #'char-equalw-function)
	    (<f (lengthw text-line) current-score-of-best-match-for-eyes))
       (when current-best-match-for-eyes
	 (reclaim-text-string current-best-match-for-eyes))
       (setf current-best-match-for-eyes
	     (copy-text-string text-line))
       (setf current-score-of-best-match-for-eyes (lengthw text-line))
       (when lower-match-rank-for-player-eyes-p
	 (incff current-score-of-best-match-for-eyes))
       (setf current-x-for-eyes?
	     (halff (+f clipped-left-edge clipped-right-edge)))
       (setf current-y-for-eyes?
	     (halff (+f clipped-top-edge clipped-bottom-edge)))
       (when trace-system-calls-p
	 (notify-user-at-console "found: ~s ~s ~s" current-x-for-eyes? current-y-for-eyes?
				 current-best-match-for-eyes))))))



;;; `Player-look-for-text-on-screen' implments the top level of the cool way of
;;; seing text on the screen.

;;; This works by taking the window the player is running in, since it has the
;;; layout we need, and slamming it to be of type "printer."  That will cause
;;; the ICP bottleneck to dispatch thru the the vector of printing routines.
;;; We then rebind that vector to a set of routines that look for the text
;;; we wish to find.

;;; This will not find text in rasters, since they are bitmaps by now.  It is
;;; frighting to worry about the consistency of the raster caches.  This is
;;; why we have a drawing-for-eyes-of-player-p predicate.

(defun-allowing-unwind player-look-for-text-on-screen (current-text-focus-for-eyes?)
  (let ((gensym-window player-target-gensym-window-g2-struct?))

    ;; First, let the REAL drawing get to the REAL screen.
    (force-window-drawing gensym-window)
    
    (with-drawing-trace (player)
      (format t "Player: Looking for ~s~%" current-text-focus-for-eyes?))

    (let ((current-x-for-eyes? nil)
	  (current-y-for-eyes? nil)
	  (current-best-match-for-eyes nil)
	  (current-score-of-best-match-for-eyes most-positive-fixnum))
      (let ((stored-raster-type-for-window (stored-raster-type-for-window gensym-window))
	    (scratchpad-raster-type-for-window (scratchpad-raster-type-for-window gensym-window))
	    (type-of-gensym-window (type-of-gensym-window gensym-window)))
	(setf (stored-raster-type-for-window gensym-window) 'printer)
	(setf (scratchpad-raster-type-for-window gensym-window) 'printer)
	(setf (type-of-gensym-window gensym-window) 'printer)
	(unwind-protect
	  (let ((icp-printing-message-handler-array icp-player-message-handler-array))
	    (let ((current-drawing-priority :draw-as-soon-as-possible))
	      (with-unlimited-time-slice
		(let ((allow-invalidate-on-printing-window-p t))
		  (refresh-window gensym-window)))))
	  (setf (stored-raster-type-for-window gensym-window) stored-raster-type-for-window)
	  (setf (scratchpad-raster-type-for-window gensym-window) scratchpad-raster-type-for-window)
	  (setf (type-of-gensym-window gensym-window) type-of-gensym-window)))
      (set-best-text-matched-by-player current-best-match-for-eyes)
      (values current-x-for-eyes? current-y-for-eyes?))))


;;; `Drawing-for-eyes-of-player-p' must be used in all draw methods that
;;; stand on some raster caches.  The rasters currently displayed to the
;;; user, and stored in the cache, may not be in synch with the underlying
;;; KB state.  On one hand it might be lagging behind the KB state.  In which
;;; case we want to supress bringing it uptodate so that the player sees what
;;; is currently showing.  On the other hand it might be entirely useless,
;;; i.e. the cache was flushed, in which case we wish we could simulate what
;;; the user currently sees.

;;; All of these cases are sort of pointless since the player can't see
;;; anything useful in bitmap anyway.  So the draw method, if designed to
;;; bring it the cache into synch behavior should just supressed that when
;;; this predicate is true.  (This means trend charts).

;;; It must be supressed for one other reason. The cache update process can
;;; meltdown if it notices that the window is hacked up to look a little bit
;;; like a printer window.

(defun drawing-for-eyes-of-player-p ()
  (and player-target-gensym-window-g2-struct?
       (printing-window-p player-target-gensym-window-g2-struct?)
       (not (printing-p))))

;; Isn't this totally Zen dude?



;;; `Show-all-text-on-screen', a development only function, can be used to print all
;;; the text that drawing currently has on any given screen.

#+development
(defun-allowing-unwind show-all-text-on-screen (gensym-window)
  (let ((current-text-focus-for-eyes? :show)
	(current-x-for-eyes? nil)
	(current-y-for-eyes? nil))

    ;; First, let the REAL drawing get to the REAL screen.
    (force-window-drawing gensym-window)

    (let ((stored-raster-type-for-window (stored-raster-type-for-window gensym-window))
	  (scratchpad-raster-type-for-window (scratchpad-raster-type-for-window gensym-window))
	  (type-of-gensym-window (type-of-gensym-window gensym-window)))
      (setf (stored-raster-type-for-window gensym-window) 'printer)
      (setf (scratchpad-raster-type-for-window gensym-window) 'printer)
      (setf (type-of-gensym-window gensym-window) 'printer)
      (unwind-protect
	(let ((icp-printing-message-handler-array icp-player-message-handler-array))
	  (with-unlimited-time-slice
	    (let ((current-drawing-priority :draw-as-soon-as-possible))
	      (let ((allow-invalidate-on-printing-window-p t))
		(refresh-window gensym-window)))))
	(setf (stored-raster-type-for-window gensym-window) stored-raster-type-for-window)
	(setf (scratchpad-raster-type-for-window gensym-window) scratchpad-raster-type-for-window)
	(setf (type-of-gensym-window gensym-window) type-of-gensym-window)))
    (values current-x-for-eyes? current-y-for-eyes?)))




;;; `Do-image-planes' is an extremely minor abstraction in support of walking the
;;; workstation -> pane -> image-plane -> workspace -> block hierarchy when we
;;; are eying the screen an un-cool manner.

(defmacro do-image-planes ((image-plane gensym-window-g2-struct) &body body)
  (let ((pane (gensym-make-symbol 'pane)))
    `(loop for ,pane in (panes-in-window ,gensym-window-g2-struct)
	   do
       (loop
	for ,image-plane in (stack-of-image-planes ,pane)
	do ,@body))))


;;; `Do-table-iteration' will sweep over all the cells in a given
;;; table executing a body of code.  Some number of bindings are
;;; made available to that body of code.  These may include:
;;;
;;;    table       -- has the table being iterated over.
;;;    table-format  
;;;    bottom-edge-of-cells
;;;    right-edge-of-cells 
;;;    row         -- the current row
;;;    first-cell-of-row 
;;;    text-cell   -- the cell's contents
;;;    row-number  -- the row and column number of the cell (zero based).
;;;    column-number
;;;    top         -- the bounds of the cell on screen.
;;;    bottom 
;;;    left 
;;;    right 
;;;    text        -- the text of the cell
;;;    remaining-row-edges
;;;    remaining-column-edges

;; Desired...
;;    supertable?
;;    format-of-superblock-if-a-table?

(defmacro do-table-iteration ((desired-bindings table) &body body)
  
  ;; Compute a fix point from the desired bindings into
  ;; the set of bindings we will actually make to do this.
  ;; Complain if this isn't possible.
  (let (normalized-desired-bindings
	;; normalized-desired-bindings will contain, by example,
	;;     ((table t) (row-index row-index) (bottom #:bottom1) ...)
	;; i.e. what they bind and the name to bind it to.

	(binding-requirements
	  '((table)
	    (table-format)
	    (bottom-edge-of-table-interior table-format)
	    (right-edge-of-table-interior table-format)
	    (row)
	    (remaining-row-edges)
	    (row-index)
	    (first-cell-of-row row)
	    (text-cell row)
	    (remaining-column-edges)
	    (column-index)
	    (top-edge-of-cell bottom-edge-of-cell)
	    (bottom-edge-of-cell remaining-row-edges bottom-edge-of-table-interior)
	    (left-edge-of-cell right-edge-of-cell)
	    (right-edge-of-cell remaining-column-edges right-edge-of-table-interior)
	    (text text-cell))))

    (unless (memq 'row desired-bindings)
      (push 'row desired-bindings))

    (unless (memq 'text-cell desired-bindings)
      (push 'text-cell desired-bindings))

    (setq normalized-desired-bindings
	  (loop for desired-binding in desired-bindings
		collect (if (symbolp desired-binding)
			    (list desired-binding desired-binding)
			    (list (second desired-binding) (first desired-binding)))))

    (loop as changed-flag = nil then nil
	  do
      (loop for (desired-variable . required-variables) 
		in binding-requirements
	    do
	(when (assq desired-variable normalized-desired-bindings)
	  (loop for required-variable in required-variables
		when (not (assq required-variable normalized-desired-bindings))
		  do
		    (setf changed-flag t)
		    (push 
		      (list required-variable (gensym-make-symbol required-variable)) 
		      normalized-desired-bindings))))
      (unless changed-flag (return nil)))

    (let ((trouble
	    (loop for (desired-variable nil) in normalized-desired-bindings
		  when (not (assq desired-variable binding-requirements))
		    collect desired-variable)))
      (when trouble
	(error "do-table-iteration doesn't know how to bind ~S" trouble)))
    
    ;; Now build the resulting iteration.
    (let (var)
      (macrolet ((spell (symbol)
			`(second (assq ',symbol normalized-desired-bindings)))
		 (desired-p (symbol)
			    `(setq var (second (assq ,symbol normalized-desired-bindings)))))
	`(loop ,@(when (desired-p 'table) 
		   `(with ,var = ,table))
	       ,@(when (desired-p 'table-format) 
		   `(with ,var = (table-format ,table)))
	       ,@(when (desired-p 'right-edge-of-table-interior)
		   `(with ,var =
			  (-r (right-edge-of-block ,table)
			      (table-right-border-width ,(spell table-format)))))
	       ,@(when (desired-p 'bottom-edge-of-table-interior)
		   `(with ,var = 
			  (-r (bottom-edge-of-block ,table)
			      (table-bottom-border-width ,(spell table-format)))))
	       ,@(when (desired-p 'row) 
		   `(for ,var in (table-rows ,table)))
	       ,@(when (desired-p 'row-index) 
		   `(as ,var from 0))
	       ,@(when (desired-p 'first-cell-of-row) 
		   `(as ,var = (first ,(spell row))))
	       ,@(when (desired-p 'remaining-row-edges)
		   `(for ,var = (row-edges ,table) then (rest ,(spell remaining-row-edges))))
	       ,@(when (desired-p 'top-edge-of-cell)
		   `(as ,var = (top-edge-of-block ,table) then ,(spell bottom-edge-of-cell)))
	       ,@(when (desired-p 'bottom-edge-of-cell)
		   `(as ,var = (if ,(spell remaining-row-edges)
						(first ,(spell remaining-row-edges))
						,(spell bottom-edge-of-table-interior))))
	       do
	   (loop ,@(when (desired-p 'text-cell) 
		     `(for ,var in ,(spell row)))
		 ,@(when (desired-p 'column-index)
		     `(as ,var from 0))
		 ,@(when (desired-p 'remaining-column-edges)
		     `(as ,var = (column-edges ,table) then (rest ,(spell remaining-column-edges))))
		 ,@(when (desired-p 'left-edge-of-cell) 
		     `(as ,var = (left-edge-of-block ,table) then ,(spell right-edge-of-cell)))
		 ,@(when (desired-p 'right-edge-of-cell)
		     `(as ,var = (if ,(spell remaining-column-edges)
						  (first ,(spell remaining-column-edges))
						  ,(spell right-edge-of-table-interior))))
		 ,@(when (desired-p 'text) `(as ,var = (text? ,(spell text-cell))))
		 do
	     ,@body))))))


(defun bounds-and-component-in-window
    (left-in-workspace
      top-in-workspace
      right-in-workspace
      bottom-in-workspace
      component
      image-plane)
  (with-image-plane-transform (image-plane)
    (values
      (x-in-window left-in-workspace)
      (y-in-window top-in-workspace)
      (x-in-window right-in-workspace)
      (y-in-window bottom-in-workspace)
      component)))


(defun player-find-menu-item-containing-string (string-to-look-for)
  (let ((match-left nil)
	(match-top nil)
	(match-right nil)
	(match-bottom nil)
	(match-text-cell nil)
	(match-text-string nil)
	(match-text-length nil)
	(match-image-plane nil))
    (do-image-planes (image-plane player-target-gensym-window-g2-struct?)
      (let ((workspace? (workspace-on-image-plane? image-plane)))

	(with-drawing-trace (player)
	  (when (and workspace? (frame-of-class-p workspace? 'menu-workspace))
	    (format t "Player: ~s ~s~%" workspace? (class workspace?))))
	
	(when (and workspace?
		   (eq 'menu-workspace (class workspace?)))
	  (loop with table = (first-subblock workspace?)
		for row in (table-rows table)
		do (loop for cell? in row
			 when (and cell?
				   (not (cell-is-block-p cell?))
				   (not (menu-heading-text-cell-p cell?))
				   (find-string-in-text string-to-look-for (text? cell?)))
			   do (let* ((text-string (convert-text-to-text-string (text? cell?)))
				     (text-length (lengthw text-string)))
				(when (or (null match-text-length)
					  (<f text-length match-text-length))
				  (setq match-text-string
					(prog1 text-string
					  (when match-text-string
					    (reclaim-text-string match-text-string))))
				  (setq match-text-length text-length)
				  (multiple-value-bind (left top right bottom)
				      (get-table-cell-edges table cell?)
				    (setq match-left left)
				    (setq match-top top)
				    (setq match-right right)
				    (setq match-bottom bottom)
				    (setq match-text-cell cell?)
				    (setq match-image-plane image-plane)))))))))
    (set-best-text-matched-by-player match-text-string)
    (when match-text-cell
      (bounds-and-component-in-window
	match-left
	match-top
	match-right
	match-bottom
	match-text-cell
	match-image-plane))))



;;; The function `player-find-attribute-table-value-cell' finds an attribute
;;; table in the player window with an attribute description matching
;;; string-to-look-for.  At the end best-text-matched-by-player is set to the
;;; closest matching text, or nil if none was found.  [Note: prior to the
;;; release pending today the value was left as is, i.e., random, when no match
;;; at all was found.  (MHD 6/8/00)] In addition, if a match is not found, nil
;;; is returned; otherwise, the following six values are returned:
;;;
;;; 	match-left match-top match-right match-bottom
;;; 	match-text-cell
;;; 	match-image-plane
;;;
;;; The edge values give the rectangle around the _value cell_ (i.e., the cell
;;; to the right of the attribute description cell showing the attribute value).
;;; The match-text-cell value is the value cell itself.  The image plane value is
;;; the image plane where the match occurred.

(defun player-find-attribute-table-value-cell (string-to-look-for)
  (let ((match-left nil)
	(match-top nil)
	(match-right nil)
	(match-bottom nil)
	(match-text-string nil)
	(match-text-length nil)
	(match-text-cell nil)
	(match-image-plane nil))
    (do-image-planes (image-plane player-target-gensym-window-g2-struct?)
      (let ((workspace? (workspace-on-image-plane? image-plane)))
	(when workspace?
	  (loop for subblock being each subblock of workspace?
		when (attribute-table-p subblock)
		  do (loop with table = subblock
			   for row in (table-rows table)
			   as description-cell? = (if (cdr row) (car row))
			   when (and description-cell?
				     (not (cell-is-block-p description-cell?))
				     (find-string-in-text
				       string-to-look-for
				       (text? description-cell?)))
			     do (let* ((text (text? description-cell?))
				       (text-string (convert-text-to-text-string text))
				       (text-length (lengthw text-string))
				       (value-cell (second row)))
				  (when (or (null match-text-length)
					    (<f text-length match-text-length))
				    (setq match-text-string
					  (prog1 text-string
					    (when match-text-string
					      (reclaim-text-string match-text-string))))
				    (setq match-text-length text-length)
				    (multiple-value-bind (left top right bottom)
					(get-table-cell-edges table value-cell)
				      (setq match-left left)
				      (setq match-top top)
				      (setq match-right right)
				      (setq match-bottom bottom)
				      (setq match-text-cell value-cell)
				      (setq match-image-plane image-plane)))))))))
    (set-best-text-matched-by-player match-text-string)
    (when match-text-cell
      (bounds-and-component-in-window
	match-left
	match-top
	match-right
	match-bottom
	match-text-cell
	match-image-plane))))

(defun player-find-action-button (string-to-look-for)
  (let ((match-subblock nil)
	(match-image-plane nil)
	(match-label nil)
	(match-label-length nil))
    (do-image-planes (image-plane player-target-gensym-window-g2-struct?)
      (let ((workspace? (workspace-on-image-plane? image-plane)))
	(when workspace?
	  (loop for subblock being each subblock of workspace?
		for label = (and (eq 'action-button (class subblock))
				 (label-for-button subblock))
		when (and label
			  (text-string-search+ string-to-look-for label)
			  (or (null match-subblock)
			      (<f (lengthw label)
				  match-label-length)))
		  do (setq match-subblock subblock)
		     (setq match-image-plane image-plane)
		     (setq match-label (label-for-button subblock))
		     (setq match-label-length (lengthw match-label))))))
    (when match-subblock
      (set-best-text-matched-by-player (copy-text-string match-label))
      (bounds-and-component-in-window
	(left-edge-of-block match-subblock)
	(top-edge-of-block match-subblock)
	(right-edge-of-block match-subblock)
	(bottom-edge-of-block match-subblock)
	match-subblock
	match-image-plane))))



(defun player-find-instance (class-name)
  (do-image-planes (image-plane player-target-gensym-window-g2-struct?)
    (let ((workspace? (workspace-on-image-plane? image-plane)))
      (when workspace?
	(loop for subblock being each subblock of workspace?
	      when (eq class-name (class subblock))
		do (return-from player-find-instance
		     (multiple-value-bind (left top right bottom)
			 (bounds-and-component-in-window
			   (left-edge-of-block subblock)
			   (top-edge-of-block subblock)
			   (right-edge-of-block subblock)
			   (bottom-edge-of-block subblock)
			   subblock
			   image-plane)
		       (values
			 (halfr (+r left right))
			 (halfr (+r top bottom))))))))))







;;;; Player Functions for The Generation of Events



;;; `generate-event, a player function' ...

(def-player-lisp-function generate-event-and-suspend player-generate-event-and-suspend)

(def-player-lisp-function generate-event player-generate-event)



;;; `move-to, a player function' ...

(def-player-lisp-function move-to player-move-to)

(defun player-move-to (x y)
  (setf player-mouse-x x)
  (setf player-mouse-y y)
  (player-generate-event-and-suspend #.(key-code 'mouse-motion)))



;;; `move, a player function' ...

(def-player-lisp-function move player-move)

(defun player-move (delta-x delta-y)
  (incf player-mouse-x delta-x)
  (incf player-mouse-y delta-y)
  (player-generate-event-and-suspend #.(key-code 'mouse-motion)))



;;; `push-location, a player function' ...

(def-player-lisp-function push-location player-push-location)

(defun player-push-location ()
  (player-push (player-cons player-mouse-x player-mouse-y) player-location-stack))




;;; `pop-location, a player function' ...

(def-player-lisp-function pop-location player-pop-location)

(defun player-pop-location ()
  (let* ((location-record (player-pop player-location-stack))
	 (x (car location-record))
	 (y (cdr location-record)))
    (reclaim-player-cons location-record)
    (player-move-to x y)))



;;; `name-location, a player function' ...

(def-player-lisp-function name-location player-name-location)

(defun player-name-location (name)
  (let* ((alist-entry (or (assq name player-named-locations)
			 (let ((new-entry 
				 (player-cons name
					      (player-cons nil nil))))
			   (player-push new-entry player-named-locations)
			   new-entry)))
	 (location-record (cdr alist-entry)))
    (setf (car location-record) player-mouse-x)
    (setf (cdr location-record) player-mouse-y)))


;;; `move-to-location, a player function' ...

(def-player-lisp-function move-to-location player-move-to-location)

(defun player-move-to-location (name)
  (let* ((alist-entry (assq name player-named-locations))
	 (location-record (cdr alist-entry)))
    (unless location-record 
      (player-error "Unknown location passed to move-to-location."))
    (player-move-to (car location-record) (cdr location-record))))




;;; `type-character, a player function' ...

(defun player-translate-character-code-to-event-code (wide-character)
  (key-code-from-character		; accepts only CL characters for now!
    (code-char (wide-character-code wide-character))))

(def-player-lisp-function type-character player-type-character)

(defun player-type-character (wide-character)
  (player-generate-event
     (player-translate-character-code-to-event-code wide-character)))



;;; `type, a player function' ...

(def-player-lisp-function type player-type)

(defun player-type (string)
  (player-push 
    (player-list 'type-1 string (lengthw string) 0)
    player-control-stack)
  nil)

(def-player-instruction type-1 (form)
  (let ((string (second form))
        (max (third form))
        (index (fourth form)))
   (cond
     ((>= index max) 
      (reclaim-player-list form))
     (T
      (setf (fourth form) (+ index 1))
      (player-push form player-control-stack)
      (player-generate-event 
	(player-translate-character-code-to-event-code 
	  (charw string index)))))))




;;; `text-visible-p, a player function' ...

(def-player-lisp-function text-visible-p player-text-visible-p)

(defun player-text-visible-p (text)
  (cond ((player-look-for-text-on-screen (evaluation-text-value text))
	 (when trace-system-calls-p
	   (notify-user-at-console "player-text-visible-p: ~s" best-text-matched-by-player))
	 t)
	(t
	 nil)))

;;; `menu-item-visible-p, a player function' ...

(def-player-lisp-function menu-item-visible-p player-find-menu-item-containing-string)



;;; `attribute-table-slot-visible-p, a player-function' ...

(def-player-lisp-function attribute-table-slot-visible-p player-find-attribute-table-value-cell)


;;; `action-button-visible-p, a player-function' ...

(def-player-lisp-function action-button-visible-p player-find-action-button)

;;; `instance-visible-p, a player-function' ...

(def-player-lisp-function instance-visible-p player-find-instance)



;;; `move-to-text' ...

(def-player-lisp-function move-to-text player-move-to-text)

(defun player-move-to-text (text)
  (multiple-value-bind (x? y?)
      (player-look-for-text-on-screen text)
    (when (and x? trace-system-calls-p)
      (notify-user-at-console "player-move-to-text: ~s ~s ~s" x? y? best-text-matched-by-player))
    (cond (x?
	   (player-move-to x? y?))
	  (t
	   (player-error "Player couldn't find text.")))))



;;; `move-to-menu-item, a player function' ...

(def-player-lisp-function move-to-menu-item player-move-to-menu-item)

(defun player-move-to-menu-item (text)
  (multiple-value-bind (left top right bottom)
      (player-find-menu-item-containing-string text)
    (cond
      (left
       (when trace-system-calls-p
	 (notify-user-at-console "player-move-to-menu-item: ~s" best-text-matched-by-player))
       (multiple-value-bind (x y) (player-center-of-rectangle left top right bottom)
	 (player-move-to x y)))
      (T (player-error "Player couldn't find menu item.")))))



;;; `move-to-attribute-table-slot, a player function' either finds and moves to
;;; the attribute description cell of a table, if it can be found and is
;;; visible, or calls player-error.

(def-player-lisp-function move-to-attribute-table-slot player-move-to-attribute-table-slot)

(defun player-move-to-attribute-table-slot (string-to-look-for)
  (multiple-value-bind (left top right bottom)
      (player-find-attribute-table-value-cell string-to-look-for)
    (declare (ignore right))
    (cond
      (left
       (when trace-system-calls-p
	 (notify-user-at-console "player-move-to-attribute-table-slot: ~s" best-text-matched-by-player))
       (player-move-to (+r left 1) (truncatef (+r top bottom) 2)))
      (T (player-error "Player couldn't find attribute table slot.")))))



;;; `move-to-action-button, a player function' ...

(def-player-lisp-function move-to-action-button player-move-to-action-button)

(defun player-move-to-action-button (string-to-look-for)
  (multiple-value-bind (left top right bottom)
      (player-find-action-button string-to-look-for)
    (cond
      (left
       (when trace-system-calls-p
	 (notify-user-at-console "player-move-to-action-button: ~s" best-text-matched-by-player))
       (player-move-to (truncatef (+r left right) 2) (truncatef (+r top bottom) 2)))
      (T (player-error "Player couldn't find attribute table slot.")))))



;;; `move-to-instance, a player function' ...

(def-player-lisp-function move-to-instance player-move-to-instance)

(defun player-move-to-instance (class-name)
  (multiple-value-bind (x y)
      (player-find-instance class-name)
    (cond
      (x (player-move-to x y))
      (T (player-error "Player couldn't find attribute table slot.")))))






;;;; Player Functions Imported Out of The Lisp Environment



(def-player-lisp-function print)

(defun-for-player type-control-return ()
  (type-character #.char-return))

(defun-for-player type-entry (string)
  (type string)
  (type-control-return))

;; move this to utilities after type-control-return has moved into 2.1

(defun-for-player type-control-j ()
  (type-character #.char-control-j))

(defun-for-player type-control-s ()
  (type-character #.char-control-s))

(defun-for-player type-control-b ()
  (type-character #.char-control-b))

(defun-for-player type-control-x ()
  (type-character #.char-control-x))

(defun-for-player type-control-y ()
  (type-character #.char-control-y))

(defun-for-player type-control-t ()
  (type-character #.char-control-t))

(defun-for-player type-control-v ()
  (type-character #.char-control-v))







;;;; Player's External Interface



;;; The routines in this section together provide the "front console" of the
;;; player.  These routines include:

;;;    clear-player       -- Resets all internal state in the player
;;;    pause-player       -- Pauses the player.
;;;    resume-player      -- Resumes the player.
;;;    player-eval        -- Player equivalent of eval.
;;;    player-eval-server -- Just like player-eval, but it copies 
;;;                          the form given, and latter reclaims it.
;;;                          This is necessary when sending a form via ICP.
;;;    backtrace-player   -- Prints a debuggin backtrace of the play's stacks.

;;; Additionally the player will pause if you depress the mode lock key.  To
;;; resume the player depress the key again.  The state of the light on the mode 
;;; lock key is ignored.  You may have to keep the key depressed for a moment
;;; before the player will poll its state again.

(defun clear-player ()
  (setf player-value-stack ())
  (setf player-control-stack ())
  (reclaim-player-tree player-location-stack)
  (setf player-location-stack ())
  (reclaim-player-tree player-named-locations)
  (setf player-named-locations ())
  (setf player-state 'paused)
  (let* ((g2-window?
	   (loop for w being class-instances of 'g2-window
		 when (eq 'local (g2-window-management-type w))
		   do (return w)))
	 (workstation?
	   (if g2-window?
	       (workstation-for-g2-window? g2-window?)
	       nil))
	 (window-struct
	   (if workstation?
	       (window-for-workstation workstation?)
	       system-window)))
    (assert window-struct () "Player-eval couldn't find a window to play into.")
    (setf player-target-gensym-window-g2-struct? window-struct))
  (player-release-definitions T))

(defun pause-player ()
  (setf player-state 'paused))

(defun resume-player ()
  (setf last-player-event-time 0)
  (setf player-state 'running))

(defun player-eval (form)
  (clear-player)
  (player-push form player-control-stack)
  (resume-player))

(defun player-eval-server (form)
  (clear-player)
  (let ((copy-of-form 
	  (copy-tree-and-atoms-using-player-conses form)))
    (player-push 
      (player-list 'reclaim-player-tree copy-of-form)
      player-control-stack)
    (player-push
      copy-of-form
      player-control-stack))
  (resume-player))



;;; `Backtrace-player' creates output that looks like this example
;;; (except for the comments).

;;;    state: RUNNING, current-instruction: UNBOUND
;;;    value stack: NIL
;;;    control stack:
;;;      (progn-1 2 2...           ; this was probably the body of (click)
;;;           progn
;;;           (mouse-down)
;;;          ^(mouse-up))
;;;      (unbind <(y . 0) (x . 0) >)  ; the parameters to (click-at 0 0)
;;;      (progn-1 4 8...   
;;;           (click-at 0 0)
;;;           (if (menu-item-visible-p "reset") (progn (click-menu-item "reset") (click-at 0 0)))
;;;          ^(click-menu-item "misc")
;;;           (click-menu-item "clear kb") ...)
;;;      (progn-1 2 4...
;;;           progn
;;;           (clear-kb)            ; The caret shows what we are going to do next.
;;;          ^(main-menu "load kb") ; so the last thing this did was (clear-kb)
;;;           (type-entry kb-name) ...)
;;;      (unbind <(kb-name . "critical.kb") >)
;;;      (progn-1 2 3...
;;;           progn
;;;           (load-kb name)
;;;          ^(main-menu "start")
;;;           (wait 240))
;;;      (unbind <(name . "critical.kb") >)
;;;      (progn-1 30 33...
;;;           (load-kb-and-start "mapi.kb")
;;;           (load-kb-and-start "critical.kb")
;;;          ^(load-kb-and-start "paper.kb")
;;;           (load-kb-and-start "petro.kb") ...)
;;;      (progn-1 3 13...
;;;           (login)
;;;           (try-load-all-example-kb)
;;;          ^(clear-kb)
;;;           (click-at 500 500) ...)
;;;      (player-release-definitions (quote remote-test))  ; will reclaim the space
;;;                                                        ; taken by these tests.

;;; Not all frames found on the control stack are shown, unless the optional 
;;; parameter is bound to T.  The caret is used to mark where execution will
;;; proceed from when that control stack entry is invoked again.

#+development
(defun backtrace-player (&optional show-minor-frames)
  (format t "~%state: ~S ~A, current-instruction: ~S, ~A" 
	  player-state
	  (if nil
	      ",but paused via MODE LOCK key"
	      "")
	  (if (boundp 'player-current-instruction) 
	      player-current-instruction
	      'unbound)
	  (if (<=f 
		(+f last-player-event-time player-pace)
		(current-player-event-time))
	      "awake"
	      "sleeping"))
  (let ((*print-length* (if (fixnump show-minor-frames) nil 4))
	(*print-level* (if (fixnump show-minor-frames) nil 3)))
    (format t "~%value stack: ~S" player-value-stack))
  (when (eq t show-minor-frames)
    (format t "~%definition stack: ~(~S~)" player-definition-stack))
  (format t "~%control stack:")
  (loop with latest-lexical-contour = player-lexical-binding-stack
	for control-form in player-control-stack
	as control-form-index from 0
	do
    (typecase control-form
      (cons
       (when (or (eq t show-minor-frames)
		 (eql show-minor-frames control-form-index)
		 (and
		   (not (fixnump show-minor-frames))
		   (not
			(memq (first control-form)
			      '(reclaim-player-tree)))))
	 (case (first control-form)
	   ((progn-1 player-tagbody-1)
	    (let ((instruction-opcode (first control-form))
		  (next-statement (second control-form))
		  (length (third control-form))
		  (statements (fourth control-form)))
	      (format t "~%~2D  (~(~S ~S ~S~)"
		      control-form-index
		      instruction-opcode
		      next-statement
		      length)
	      (loop with low = (- next-statement 2)
		    with high = (+ next-statement 1)
		    initially (unless (< low 0)
				(format t "..."))
		    for statement in statements
		    as cnt from 0
		    when (or (fixnump show-minor-frames)
			     (<= low cnt high))
		      do
			(format t "~%        ~A~(~S~)" (if (= cnt next-statement) "^" " ") statement)
		    finally
		      (format t (cond
				  ((< high length) " ...)")
				  ((< length next-statement) "^)")
				  (T ")"))))))
	   (unbind
	    (format t "~%~2D  (unbind <" control-form-index)
	    (loop with next-lexical-contour = (second control-form)
		  for p on latest-lexical-contour
		  as binding = (first p)
		  until (eq p next-lexical-contour)
		  do (format t "~(~S~) " binding)
		  finally 
		    (format t ">)")
		    (setf latest-lexical-contour next-lexical-contour)))
	   (T
	    (let ((*print-length* 3)
		  (*print-level* 3))
	      (format t "~%~2D  ~(~S~)" control-form-index control-form))))))
      (T (format t "~%  ~S" control-form)))))







;;;; Player ICP driver


;;; `Player-icp-connection, a system variable', is dynamically bound to the connection
;;; overwhich a test is sent to a testing slave.  Most of the routines in this section
;;; depend upon this being bound.  Play-test binds it.

(def-system-variable player-icp-connection player nil)



;;; `Open-icp-connection-for-player' and 'close-icp-connection-for-player' bracket
;;; the lifecycle of the open connection to the testing slave.  

(defun open-icp-connection-for-player (machine address protocol)
  (when player-icp-connection
    (close-icp-connection-for-player))
  (setf 
    player-icp-connection
    (setup-network-connection-for-connect
      (make-icp-connection (list protocol machine address)))))

(defun close-icp-connection-for-player ()
  (flush-and-shutdown-icp-socket
    ;; (shiftf player-icp-connection nil) Lucid!
    (prog1
      player-icp-connection
      (setf player-icp-connection nil))
    ))



;;; `With-open-icp-connection-for-player' is used in the sources to lexically bracket
;;; the open connection to the slave and to dynamically assure that it is reclaimed
;;; after a test has been sent.

(defmacro with-open-icp-connection-for-player ((machine address protocol) &body body)
  `(progn
     (open-icp-connection-for-player ,machine ,address ,protocol)
     (unwind-protect
	 (progn ,@body)
       nil ; (close-icp-connection-for-player)
       )))



;;; `Remote-eval' builds on the ICP message icp-remote-eval.  To send over a single
;;; form to the current testing slave.

(defun-allowing-unwind remote-eval (form)
  (writing-icp-message-group ((icp-output-port player-icp-connection))
    (send-icp-remote-eval form)))



(defun-allowing-unwind remote-eval-once
		       (form target-machine target-address target-protocol)
  #+development
  (assert (and (eq target-protocol 'tcp-ip)
	       (fixnump target-address)))
  (with-open-icp-connection-for-player (target-machine target-address target-protocol)
    (remote-eval form)))

(declare-funcallable-symbol remote-eval-once)


#+development
(defvar last-remote-eval-host)
#+development
(defvar last-remote-eval-port)
#+development
(defvar last-remote-eval-protocol)
#+development
(defvar remote-read-eval-status :idle)
#+development
(defvar remote-read-eval-return-value)

#+development
(defun-allowing-unwind remote-read-eval
    (form &optional
	  (host last-remote-eval-host)
	  (port last-remote-eval-port)
	  (protocol last-remote-eval-protocol))
  (unless (and (boundp 'current-system-name)
	       (eq current-system-name 'ab))
    (format t "~&Remote-read-eval can only be used within a running G2")
    (return-from remote-read-eval nil))
  (setf last-remote-eval-host host)
  (setf last-remote-eval-port port)
  (setf last-remote-eval-protocol protocol)
  (let* ((my-host-name (get-unix-host-name))
	 (my-port-number (read-from-string (second (first (get-local-host-addresses)))))
	 (form-to-send
	   `(remote-eval-once
	      (list 'handle-return-from-remote-eval (list 'quote ,form))
	      ,my-host-name ,my-port-number 'tcp-ip)))
	 (loop with remote-read-eval-status = :waiting
	       initially
		 (remote-eval-once form-to-send host port protocol)
	       do (with-scheduler-disabled
		    (g2-event-cycle-handling-windows-quit))
	       until (eq remote-read-eval-status :done))
	remote-read-eval-return-value))

#+development
(defun handle-return-from-remote-eval (value)
  (when (eq remote-read-eval-return-value :idle)
    (format t "~&An unexpected remote eval returned: ~S" value))
  (setf remote-read-eval-return-value :value)
  (setf remote-read-eval-status :done))




;;; 'Player-server-push-control-stack' provides to the evaluator that implements
;;; remote evaluation a way to push forms into the control stack, since
;;; that evaluator doesn't support macro expansion.

(defun player-server-push-control-stack (form)
  (player-push 
    (copy-tree-and-atoms-using-player-conses form)
    player-control-stack))



(defvar player-require-modules-already-sent)

;;; `Send-player-test' will send a test to the current testing ICP connection.
;;; It reads the forms out of the test script file, checking that only legal
;;; forms appear.  It does some macro expansion and sends the result over the
;;; wire.

#+development
(defun send-player-test (test-name)
  (let ((pathname
	  (gensym-merge-pathnames
	    (string test-name)
	    "ma:>player-tests>*.lisp"))
	(form-counter 0))
    (format t "~%sending ~A" pathname)
    (with-open-file (f pathname)
      (loop for form = (read f nil :eof)
	    as head = (if (consp form) (first form) nil)
	    until (eq form :eof)
	    do
	(let* ((form-to-send
		 (cond
		   ((or (not head)
			(not (memq head '(require-for-player
					   in-package
					   defun-for-player))))
		    (let ((*print-level* 2)
			  ;; jh, 6/8/93.  *Print-length* is not implemented in
			  ;; Chestnut 3.1, ;; though it is part of CLtL/2e (and
			  ;; presumably ANSI CL as well).
			  #-chestnut-3 (*print-length* 3))
		      (error "Player testing script files may only ~
                          have IN-PACKAGE, REQUIRE-FOR-PLAYER and DEFUN-FOR-PLAYER ~
                          as thier top level forms, saw ~S instead" form)))
		   (T
		    (case head
		      (in-package
		       ;; Ignore this.
		       )
		      (require-for-player
		       (loop with (nil requested-module) = form
			     with required-module = (if (symbolp requested-module)
							(symbol-name requested-module)
							requested-module)
			     for previously-send-module in player-require-modules-already-sent
			     when (string=w previously-send-module required-module)
			       do (return nil)
			     finally
			       (player-push required-module player-require-modules-already-sent)
			       #+development 
			       (send-player-test required-module)))
		      (defun-for-player
		       (macroexpand form)))))))
	  (remote-eval form-to-send)
	  (incf form-counter))))
    (format t "~%sent ~D forms from ~A" form-counter test-name)))



;;; 'Play-test' is the principle interface for invoking a test.  It sends the test
;;; named over ICP to the testing slave. After sending the test over it invokes the
;;; function main, which presumable then proceeds to do the testing.  When main exits
;;; the space used to store the test in the testing slave will be reclaimed.

;;; The testing slave is specified using the optional parameters.  If you do not provide
;;; any optional parameters the test will be sent to the last slave we sent test too.
;;; Intiallly this defaults to the local host you are on, the address 1111, using 
;;; tcp as the protocol.

(defun-allowing-unwind play-test (test-name
				   &optional
				   target-machine
				   target-address
				   target-protocol)
  (unless target-machine
    (setf target-machine (get-local-host-name)))
  (unless target-address 
    (setf target-address (get-current-icp-contact-port-number-or-name-if-any)))
  (unless target-protocol
    (setf target-protocol 'tcp-ip))
  (format t "~%Sending ~A to ~A at ~D via ~A." test-name target-machine target-address target-protocol)
  (let ((player-require-modules-already-sent ()))
    (unwind-protect
      (with-open-icp-connection-for-player (target-machine target-address target-protocol)
	(remote-eval '(clear-player))
	(remote-eval '(player-mark-definitions 'remote-test))
	#+development
	(send-player-test test-name)
	(remote-eval '(player-server-push-control-stack '(player-release-definitions t)))
	(remote-eval '(player-server-push-control-stack '(main)))
	(remote-eval '(resume-player)))
      (reclaim-player-list player-require-modules-already-sent))))

;; a bug in the ab-2-1 version requires having the done via t, rather than remote-test


;;; Player

#+development
(defun player (&optional command arg1 arg2 arg3 arg4)
  (let* ((command-table
	   '(
	     (nil nil nil "~%Type (player 'help) for help")
	     (help nil nil 
		   "~%These commands are available~
	          ~%   'help           -- shows this output~
	          ~%   'backtrace      -- shows a backtrace of the player's stack.~
	          ~%   'guardian       -- submits the guardian test to this g2 process.~
                  ~%   'clear          -- clears the player completely
                  ~%   'pause          -- pauses the player
                  ~%   'resume         -- resumes the player
	          ~%   'submit <test>  -- submits named test to this g2 process.~
	          ~%   'help <command> -- provides additional help for a given command.~
	          ")
	     (backtrace backtrace-player 1
			"~%Backtrace takes one optional argument, if T it shows more information,~
	                 ~%if an integer it shows that frame of the backtrace in more detail.")
	     (guardian guardian 0
		       "~%Guardian is equivalent to (player 'submit 'guardian)")
	     (clear clear-player 0   "~%Clears the player's control stacks.")
	     (pause pause-player 0   "~%Pauses the player.")
	     (resume resume-player 0 "~%Resumes the player.")
	     (submit play-test 4
		     "~%play-test <test> <machine> <process-id> <protocol>~
	            ~%  The last three arguments default to the current process.~
	            ~%  This opens an ICP link to another G2 process and streams,~
	            ~%  the named test to that process.  The tests are, by default~
	            ~%  found in MA:>player-tests>*.lisp")
	     ))
	 (command-record (or (assq command command-table)
			     (assq nil command-table)))
	 (command-function
	   (second command-record))
	 (command-argument-count
	   (third command-record))
	 (command-help-text
	   (fourth command-record)))
    (cond
      (command-function
       (case command-argument-count
	 (0 (funcall command-function))
	 (1 (funcall command-function arg1))
	 (2 (funcall command-function arg1 arg2))
	 (3 (funcall command-function arg1 arg2 arg3))
	 (4 (funcall command-function arg1 arg2 arg3 arg4))))
      (t
       (when (and (eq 'help command) arg1)
	 (setf command-help-text
	       (fourth
		 (assq arg1 command-table))))
       (format t command-help-text)))))


;;; `Guardian' provides a simple test that this G2 is working.

(defun guardian ()
  (play-test 'guardian))



(def-player-lisp-function player-release-definitions)
(def-player-lisp-function random)

;(def-player-instruction player-reclaim-definitions-1 (form)
;  (let ((mark (second form)))
;    (player-release-definitions mark)
;    (reclaim-player-list form)))






;;;; Interface For A Remote Testing Master

;;; These routines provide an interface into the player for a remote G2.
;;; One G2 (known as the master) manipulates another G2 (known as the slave).
;;; The master, using remote-eval ICP messages, invokes the routines defined
;;; below.  The master will recieve a reply to with each call.

;;; All routines used by the master are named <function>-for-player-master.
;;; Where <function> is one of:
;;;
;;;     generate-event
;;;
;;;     text-visible-p
;;;     move-to-text
;;;
;;;     menu-item-visible-p
;;;     move-to-menu-item
;;;
;;;     attribute-table-slot-visible-p
;;;     move-to-attribute-table-slot
;;;

;;; The routines for the player master must be invoked in the dynamic extent
;;; provided by process-next-icp-message-group-if-ready since they all send
;;; a reply back to the master once they have done their work.  This reply 
;;; is send, via player-reply-to-master, by sending a remote-eval message
;;; to the master via the current-icp-socket that the master's request
;;; came in on.



;; These routines depend upon the global state and dynamic extents of the 
;; player evaluator.  When writting new ones you will have to consider
;; carefully how that state is used in the low level event generation 
;; functions.

;; TBD???  -- figure out where this section got implemented...







;;;; System Procedure Interface to the Player




;;; This section implements the lisp back end of a set of system
;;; procedures.  The G2 side of these are found in player.kb. Care
;;; must be taken to keep these two in synch.  These system
;;; procedures are intended for use only in testing G2 internally
;;; at Gensym.

;;; System procedures recieve (and consume) must evaluation values.
;;; They return evaluation values, and must return enough values
;;; to satisfy thier callers.  It is extremely bad if you return
;;; other than an evaluation value, for example a frame pointer.

(defmacro coerce-lisp-boolean-to-c-integer (lisp-value)
  `(if ,lisp-value 1 0))



;;; In the simple cases the two parameters `slave-player-{un,}happy'
;;; provide a mnemonic for zero and one respectively.

(defparameter c-boolean-false 0)
(defparameter c-boolean-true  1)




(defun-for-system-procedure+ pm-push-location () ((result integer c-boolean-true)) nil
  (player-push
    (player-cons player-mouse-x player-mouse-y)
    player-location-stack))

(defun-allowing-unwind-for-system-procedure+ pm-pop-location () ((result integer c-boolean-true)) nil
  (when player-location-stack
    (let* ((location-record (player-pop player-location-stack))
	   (x (car location-record))
	   (y (cdr location-record)))
      (reclaim-player-cons location-record)
      (with-player-executing
	(player-move-to x y)))))

(defun-allowing-unwind-for-system-procedure+ pm-move ((mouse-x integer) (mouse-y integer))
  ((result integer c-boolean-true)) nil
  (with-player-executing
    (player-move-to (+f player-mouse-x mouse-x) (+f player-mouse-y mouse-y))))

(defun-for-system-procedure+ pm-reset () ((result integer c-boolean-true)) nil
  (when trace-system-calls-p
    (trace-events)
    #+development ; make development do the same as delivery
    (setq trace-workstation-events 'simple))
  (clear-player))

(defun-allowing-unwind-for-system-procedure+ pm-type-control-x () ((result integer c-boolean-true)) nil
  (with-player-executing
    (player-generate-event
      (player-translate-character-code-to-event-code
	(code-wide-character (char-code #.char-control-x))))))

(defun-allowing-unwind-for-system-procedure+ pm-generate-event ((simple-event-type symbol)
			     (character-as-integer integer)
			     (mouse-x integer)
			     (mouse-y integer))
  ((result integer c-boolean-true)) nil
  (let ((real-event-type
	  (case simple-event-type
	    (mouse-down    (key-code 'mouse-left-down))
	    (mouse-up      (key-code 'mouse-left-up))
	    (mouse-motion  (key-code 'mouse-motion))
	    ;; TODO: player will need to be able to generate middle & right
	    ;; mouse clicks in order to test parts of the new UI.
	    (keystroke     character-as-integer)
	    (kludge        character-as-integer))))
    (with-player-executing
      (when (> character-as-integer 0)
	(setf player-mouse-x mouse-x)
	(setf player-mouse-y mouse-y))
      (player-generate-event real-event-type))))



;;; `PM-get-current-location' gives the current player location of the mouse, as
;;; well as the current actual location of the mouse. It returns four integers,
;;; player-mouse-x and player-mouse-y as its first and second value, respectively, and
;;; the actual mouse x and y, respectively, as its third and fourth value.

(defun-allowing-unwind-for-system-procedure+ pm-get-current-location ()
  ((player-x integer)
   (player-y integer)
   (real-x integer)
   (real-y integer)) nil
   (setq player-x player-mouse-x)
   (setq player-y player-mouse-y)
   (let* ((type-of-current-workstation-window
	    (type-of-gensym-window player-target-gensym-window-g2-struct?))
	  (current-workstation-native-window?
	    (native-window? player-target-gensym-window-g2-struct?)))
     (multiple-value-setq (real-x real-y)
       (get-position-of-mouse))))



;;; `Pm-text-visible-p' Returns Zero if the text is visible and one
;;; otherwise.  These odd behavor maintains is what was originally
;;; implemented and a lot of code upstream depends upon it.

(defun-for-system-procedure+ pm-text-visible-p ((text text))
  ((result integer (coerce-lisp-boolean-to-c-integer (player-text-visible-p text))))
  nil)

(defun-allowing-unwind-for-system-procedure+ pm-move-to-text ((text text))
                          ((result integer c-boolean-true)) nil
  (with-player-executing
    (player-move-to-text text)))

(defun-for-system-procedure+ pm-menu-item-visible-p ((text text))
  ((result integer
	   (coerce-lisp-boolean-to-c-integer
	     (player-find-menu-item-containing-string text))))
  nil)

(defun-for-system-procedure+ pm-action-button-visible-p ((text text))
  ((result integer
	   (coerce-lisp-boolean-to-c-integer
	     (player-find-action-button text))))
  nil)

(defun-allowing-unwind-for-system-procedure+  pm-move-to-action-button ((string-to-look-for text))
  ((result integer c-boolean-true)) ;; rebound
  nil
  (with-player-executing
    (multiple-value-bind (left? top right bottom)
	(player-find-action-button string-to-look-for)
      (if left?
	  (player-move-to (truncatef (+r left? right) 2) (truncatef (+r top bottom) 2))
	  (setf result c-boolean-false)))))

(defun-allowing-unwind-for-system-procedure+  pm-move-to-menu-item ((text text))
  ((result integer c-boolean-true)) nil
  (with-player-executing
    (player-move-to-menu-item text)))

(defun-for-system-procedure+ pm-table-slot-visible-p ((text text))
  ((result integer
	  (coerce-lisp-boolean-to-c-integer
	    (player-find-attribute-table-value-cell text))))
  nil)

(defun-allowing-unwind-for-system-procedure+ pm-move-to-table-slot ((text text))
  ((result integer c-boolean-true)) nil
  (with-player-executing
    (player-move-to-attribute-table-slot text)))

(defun-for-system-procedure+ pm-translate-character-code-to-event-code
    ((text text) (offset integer))
  ((result integer
	  (player-translate-character-code-to-event-code ; input is a CL character
	    (charw text offset))))
  nil)

(defun-for-system-procedure+ pm-key-code-from-symbol
    ((symbol symbol))
  ((result integer
	   (key-code-from-symbol symbol)))
  nil)

(defun-for-system-procedure+ pm-best-text ()
  ((result datum best-text-matched-by-player))
  nil)








;;;; To Do List for the Player

;; - no macros can go over the remote eval, 
;;   - defun-for-player, player cons pool ops,
;; - All the "seeing" operations, menu, table, text. doen't check visiblity well enough.
;; - get-position-of-the-mouse needs to be patched too.
;; - hit menu item
;; - hit-menu-text ".." , close-menu ".." ...
;; - edit-slot-erasing-value ...
;; - wait-until-redraw-finished
;; - burst rate in typing.
;; - player eval
;;   - fix the contour leakage problem
;;   + player defun should be used for some low level things now.
;;   + player defun arguments
;;     - lambda-list-keywords
;;   + lexical symbol contours
;;     - let binding
;;     - don't implicitly declare all lexical variables special.
;; - backtrace to supress uninteresting frames.
;; - if the time gets really wedged the it is hard to get it started again.
;;   I think this can happen in both pacing, and in waiting.
;; - reconsider reclaim-player-tree-function
;; - wait is currently in units of machine clock ticks, but it should be in
;;   some machine independent units.
;; - The example section is going to have to go, those tests don't belong
;;   in the shipped sources.
;; - player-symbol-function shouldn't use the symbol's plist.
;;   rather it should search there after an alist of player conses.
;;   but that requires teasing the KB spec from global defintiton
;;   state apart.
;; - Use fixnum-time-interval

;; + consider using with-make-symbols-for-args or what ever
;; + leak?
;; + process independent?
;; + move into ab
;;  + move the gem hackery stuff we need into here.
;;  + make it be development only
;; + Change remote-play-test to be play-test.





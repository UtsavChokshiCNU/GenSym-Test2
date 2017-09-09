;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module NEW-MENUS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Fred White




;;;; Forward References in NEW-MENUS

(declare-forward-references
  (describe-keymap-into-table-rows function run)
  (compute-main-menu-restrictions function filters)
  (compute-menu-restrictions-for-workspace function filters)
  (compute-menu-restrictions-for-click-on-table function filters)
  (reclaim-filter-list-function function filters)
  (reclaim-filter-tree-function function filters)
  (command-is-excluded-absolutely-p function filters)
  (handle-spaces-intelligently-p function edit1)
  
  ;; The following are used by the selection state.
  (editor-parameters variable)
  (find-position-in-text-given-image-plane function)
  (change-edit-box-cursor-position function)
  (enter-editing-context function)
  (non-menu-choice-permitted-p function)
  (handle-inspect-command function)
  (do-kfep-conversion-edit-from-outside function)
  (insert-text-string-at-cursor-from-outside function)
  (editable-virtual-attribute-p function)
  (current-selection function))


(declare-forward-references
  (execute-menu-choice-1 function commands0)
  (menu-cell-menu-choice function commands0)
  (selected-workspace function commands0)
  (editable-text-cell-p function commands0)
  (selectable-table-cell-p function commands0)
  (command-runs-on-multi-selection-p function commands0)
  (selected-native-window? function commands0))

;;;; Utilities



(defun-for-macro quote-function (function-name)
  (when function-name `#',function-name))
	  


;;; Some missing predicates.
(defmacro object-p (frame)
  `(frame-of-class-p ,frame 'object))

(defmacro item-p (frame)
  `(frame-of-class-p ,frame 'item))



;;; Some functions to prettify macro expansions.

(defun-for-macro optimized-when-and (conditions body)
  (cond ((null conditions)
	 body)
	((singleton? conditions)
	 `((when ,(first conditions) ,@body)))
	(t
	 `((when (and ,@conditions) ,@body)))))

(defun-for-macro optimized-and (conditions)
  (let ((conditions (remove t conditions)))
    (cond ((null conditions)
	   t)
	  ((singleton? conditions)
	   (first conditions))
	  (t
	   `(and ,@conditions)))))


;;; The defun-for-macro `optimized-progn' is a function which takes a list
;;; of forms and wraps them in a PROGN, deleting any unneeded progns and
;;; also removing any NIL forms.

(defun-for-macro optimized-progn (&rest forms)
  (optimize-progn `(progn ,@forms)))


;;; The defun-for-macro `optimize-progn' removes any unneeded PROGNS in
;;; the given form.

(defun-for-macro optimize-progn (form)
  (cond ((atom form)
	 form)
	((neq (car form) 'progn)
	 form)
	(t
	 (cond ((= (length form) 2)
		(optimize-progn (second form)))
	       (t
		(let ((new-forms (loop for subform in (cdr form)
				       for subform* = (optimize-progn subform)
				       if (and (consp subform*)
					       (eq (car subform*) 'progn))
					 append (cdr subform*)
				       else if subform*
					      collect subform*)))
		  (if (= (length new-forms) 1)
		      (first new-forms)
		      `(progn ,@new-forms))))))))




;;; The function `massage-function-spec' converts a function spec into
;;; something which, when evaled, can call be funcalled with `funcall-ui.'  In
;;; development, we turn it into a symbol.  In production, we turn it into a
;;; compiled function.

(defun-for-macro massage-function-spec (function?)
  (when (and (consp function?)				    ; Unquote.
	     (eq (first function?) 'quote)
	     (symbolp (second function?)))
    (setq function? (second function?)))
  (cond ((null function?)
	 nil)
	((symbolp function?)
	 #+development `#',function?
	 #-development `',function?)
	(t
	 function?)))



;;; The macro `funcall-ui' deals with functions which may be either symbols or
;;; compiled function objects. We are paranoid, and check for each case, rather
;;; than assume that functions are symbols in development and compiled function
;;; objects otherwise.

(defmacro funcall-ui (place &rest args)
  (let ((function (gensym)))
    `(let ((,function ,place))
       (funcall-compiled-function
	 (cond ((symbolp ,function)
		(symbol-function ,function))
	       (t
		,function))
	 ,@args))))



;;;; Presentation Types




(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name presentation-type-named)

(define-structure presentation-type ()
  (:constructor make-presentation-type-1)
  (:conc-name t)
  name
  menu				; Name of a menu which gets a value for one of these.
  dialog			; Name of a dialog (ws context) to do the same.
  available-p			; Predicate on the ptype arguments, returns T if any object of this type available. - What does 'available' mean here?  -pga, 3/7/96
  predicate			; Predicate to test whether any object satifies this type.
				; (Since we get back objects from spot, not ptypes).
  function-on-mouse-pointer     ; If non-NIL, we may be found in the "blackboard".
  lambda-list                    ; Lambda list of presentation type parameters.
  immediate-value-function)

(defun make-presentation-type (name menu dialog available-p predicate blackboard immediate-value parameters)
  (let ((ptype (make-presentation-type-1)))
    (setf (presentation-type-name ptype) name
	  (presentation-type-menu ptype) menu
	  (presentation-type-dialog ptype) dialog
	  (presentation-type-available-p ptype) available-p
	  (presentation-type-predicate ptype) predicate
	  (presentation-type-function-on-mouse-pointer ptype) blackboard
	  (presentation-type-immediate-value-function ptype) immediate-value
	  (presentation-type-lambda-list ptype) parameters)

    (setf (presentation-type-named name) ptype)
    ptype))
)

#+development
(defmacro trace-presentation-type (name)
  (let* ((ptype? (find-presentation-type name))
	 (functions-to-trace? (and ptype?
				   (list (presentation-type-available-p ptype?)
					 (presentation-type-predicate ptype?)
					 (presentation-type-function-on-mouse-pointer
					   ptype?)
					 (presentation-type-immediate-value-function
					   ptype?)))))
    (when functions-to-trace?
      ;; delete-if-not is not available
      `(trace ,.(remove-if-not #'identity functions-to-trace?)))))

(defun find-presentation-type (presentation-type-or-name &optional warn-p)
  (cond ((presentation-type-p presentation-type-or-name)
	 presentation-type-or-name)
	((symbolp presentation-type-or-name)
	 (presentation-type-named presentation-type-or-name))
	((consp presentation-type-or-name)		    ; Could be (type . parms)  or ((type .parms) . options)
	 (if (consp (car presentation-type-or-name))
	     (presentation-type-named (caar presentation-type-or-name))
	     (presentation-type-named (car presentation-type-or-name))))
	(warn-p
	 (dwarn "Unknown presentation type: ~s" presentation-type-or-name))))


(defun presentation-type-parameters (presentation-type-or-name)
  (cond ((atom presentation-type-or-name)
	 nil)
	((atom (car presentation-type-or-name))
	 (cdr presentation-type-or-name))
	(t
	 (cdr (car presentation-type-or-name)))))


(defun presentation-type-options (presentation-type-or-name)
  (cond ((atom presentation-type-or-name)
	 nil)
	((atom (car presentation-type-or-name))
	 nil)
	(t
	 (cdr presentation-type-or-name))))



;;; The function `parse-presentation-type' returns three values: the
;;; presentation-type instance, the parameters, and the options. This is where
;;; we could handle type abbreviations.

(defun parse-presentation-type (presentation-type-or-name)
  (let ((ptype? (find-presentation-type presentation-type-or-name t))
	(parameters (presentation-type-parameters presentation-type-or-name))
	(options (presentation-type-options presentation-type-or-name)))
    (values ptype? parameters options)))


	    
;;; The function `presentation-type-admits-menu-p' is true is an object of this
;;; presentation type can be selected by a choice from some menu.

(defun presentation-type-admits-menu-p (ptype)
  (let ((ptype? (find-presentation-type ptype)))
    (when ptype?
      (presentation-type-menu ptype?))))

(defun presentation-type-admits-dialog-p (ptype)
  (let ((ptype? (find-presentation-type ptype)))
    (when ptype?
      (presentation-type-dialog ptype?))))


(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name magic-argument-fetcher)
)

;;; The macro `define-presentation-type' defines a presentation type, which in its
;;; current implementation is another name for a parameter menu.  Each option may
;;; be either the name of a function, or an inline function, in the form of the cdr
;;; of the lambda expression, eg, ((mouse-pointer) . body). Except, CHOICES is either
;;; a quoted list of choices, or, a form to eval in the body of a defmenu.
;;; Each option can reference the presentation type parameters

(defmacro define-presentation-type (name parameters &key
					 menu choices submenu-choices choice-transformer
					 menu-options immediate-value
					 tester dialog available-p blackboard)
  (macrolet ((emit-code (code)
	       `(push ,code code))
	     (emit-function-for (option)
	       `(when (consp ,option)
		  (let ((function-name (build-ab-symbol name ',option 'function)))
		    (emit-code `(defun ,function-name ,(car ,option) ,@(cdr ,option)))
		    (setq ,option function-name)))))
    (let ((code ()))
      (emit-function-for tester)
      (emit-function-for available-p)
      (emit-function-for blackboard)
      (emit-function-for immediate-value)
      (when blackboard
	(emit-code `(setf (magic-argument-fetcher ',name) ',blackboard)))
      (emit-function-for choice-transformer)
      (when choices
	(setq menu (build-ab-symbol name 'menu))
	(emit-code `(defmenu (,menu :type parameter-menu
				    :parameters ,parameters
				    ,@menu-options
				    ,@(when submenu-choices
					`(:submenu-choices ,submenu-choices))
				    ,@(when choice-transformer
					`(:choice-transformer ,choice-transformer))) ()
			,@(if (quoted-form-p choices)
			      (unquote choices)
			      `(,choices)))))
      ;; Why am I storing symbols here instead of compiled function objects?
      (emit-code
	`(make-presentation-type ',name ',menu ',dialog ',available-p ',tester ',blackboard
				 ',immediate-value
				 ',parameters))
      `(eval-when (:compile-toplevel :load-toplevel :execute)
	 ,@(nreverse code)))))

;; Ought to use defun-into-place here.



;;;; Magic arguments



;;; Magic arguments are special presentation types, values for which can be pulled
;;; directly out of mouse-pointers and workstations.  This is mediated by the macro
;;; `with-magic-arguments'.

(def-concept magic-argument)

;;; Any subclass of frame or any presentation type with the "blackboard" option set
;;; is considered a magic argument.


(defmacro define-magic-argument (name (mouse-pointer) &body body)
  `(define-presentation-type ,name () :blackboard ((,mouse-pointer) ,@body)))


;;; `Magic-argument-of-latest-event' is called by get-outline-node (aka @, aka gon).

#+development
(defun magic-argument-of-latest-event (magic-argument-name)
  (blackboard-argument-of-mouse-pointer
    (mouse-pointer-of-latest-event (workstation-this-is-on system-window))
    magic-argument-name))

#+development
(defun show-recent-events (&key (count 5)
				(magic-args '(frame-being-represented
					      slot-name
					      defining-class)))
  (loop initially (format t "~&               age ")
	for arg in magic-args do (format t " ~S" arg))
  (loop
    with workstation = (workstation-this-is-on system-window)
    with mps = (sort (nconc
			   (copy-list
			     (recent-mouse-pointers-1 workstation))
			   (copy-list
			     (recent-mouse-pointers-2 workstation)))
			 #'> :key #'(lambda (mp)
				      (fixnum-time-of-mouse-pointer mp)))
	with basetime = (fixnum-time-of-mouse-pointer (first mps))
	for mp in mps
	repeat count
    collect mp
    do
    (format t "~&~12a ~5D"
	    (key-name (key-code-of-mouse-pointer mp))
	    (- basetime (fixnum-time-of-mouse-pointer mp)))
  (loop for arg in magic-args
	do
    (format t " ~S" (blackboard-argument-of-mouse-pointer mp arg)))
  (terpri)
  (values)))




;;; `Blackboard-argument-of-mouse-pointer' is useful in code that
;;; forward references blackboard arguments.

(defun blackboard-argument-of-mouse-pointer (mouse-pointer magic-argument-name)
  (when (magic-argument-fetcher magic-argument-name)
    (funcall (magic-argument-fetcher magic-argument-name)
	     mouse-pointer)))

;; Can I use something lighter weight than funcall?


;;; Operationally speaking, magic arguments are completely defined by the
;;; next two routines.

;;; The function `blackboard-argument-type-p' is true for types of values which can
;;; be dug out of mouse pointers.  These types include all magic arguments and
;;; all subclasses of object (?).

(defun blackboard-argument-type-p (type)
  (let ((ptype? (find-presentation-type type)))
    (cond (ptype?
	   (presentation-type-function-on-mouse-pointer ptype?))
	  ((symbolp type)
	   (class-description type)))))


;;; The function `magic-argument-fetcher-form' returns a form on mouse-pointer which
;;; digs out a value of the given type.  Here is where we handle the search for
;;; any class name.

(defun-for-macro magic-argument-fetcher-form (mouse-pointer type)
  (let ((fetcher? (magic-argument-fetcher type)))
    (cond (fetcher?
	   `(,fetcher? ,mouse-pointer))
	  ((class-description type)
	   `(find-frame-of-class-in-mouse-pointer ,mouse-pointer ',type)))))


;;; The function `get-magic-argument' is a runtime functional version of the
;;; preceding macro.

(defun get-magic-argument (type mouse-pointer)
  (let ((fetcher? (magic-argument-fetcher type)))
    (cond (fetcher?
	   (funcall-ui fetcher? mouse-pointer))
	  ((class-description type)
	   (find-frame-of-class-in-mouse-pointer mouse-pointer type)))))


;;; The macro `with-mouse-pointer-bindings' pulls the named values out of the
;;; mouse-pointer and binds them.  Each element of bindings is either
;;; argument-type or (argument-name argument-type), or, in the case of
;;; &optional arguments, (argument-name argument-type default-value).
;;; All bindings which are not declared &optional are required to be found
;;; in the mouse-pointer, else the body is not run.

(defmacro with-mouse-pointer-bindings (bindings mouse-pointer &body body)
  (avoiding-variable-capture (mouse-pointer)
    (expand-with-mouse-pointer-bindings bindings mouse-pointer body :warn-p t :test-p t)))

(defmacro with-mouse-pointer-bindings-no-warn (bindings mouse-pointer &body body)
  (avoiding-variable-capture (mouse-pointer)
    (expand-with-mouse-pointer-bindings bindings mouse-pointer body :warn-p nil :test-p t)))


;;; The function `expand-with-mouse-pointer-bindings' runs the body only if all required
;;; arguments are found, if test-p is T.   If warn-p is also T, it will print a warning
;;; if they are not found (in development).

(defun-for-macro expand-with-mouse-pointer-bindings (bindings mouse-pointer body &key warn-p test-p)
  (multiple-value-bind (declarations body)
      (parse-body-declarations body)
    (let ((clauses ())
	  (conditions ())
	  (required-argument-names ()))
      (loop with optional-p = nil
	    for binding in bindings
	    as name = (if (consp binding)
			  (first binding)
			  binding)
	    as type = (if (consp binding)
			  (second binding)
			  binding)
	    as default-value? = (if (consp binding)
				   (third binding)
				   nil)
	    as fetcher-form = (magic-argument-fetcher-form mouse-pointer type)
	    doing
	(when (and (not optional-p)
		   (not (memq binding lambda-list-keywords)))
	  (push name required-argument-names))
	(cond ((eq binding '&optional)
	       (setq optional-p t))
	      ((memq binding lambda-list-keywords)
	       (warn "Lambda-list keywords other than &optional are not allowed here."))
	      ((null fetcher-form)
	       (warn "The magic argument type ~s is unknown." type))
	      ((null optional-p)
	       (push `(,name ,fetcher-form) clauses)
	       ;; Optimization here: some args (like mouse-pointer or spot) need no conditions.
	       ;; In other cases, being non-NIL may not be the correct condition.
	       (push name conditions))
	      (default-value?
	       (push `(,name (or ,fetcher-form ,default-value?)) clauses))
	      (t
	       (push `(,name ,fetcher-form) clauses))))

      required-argument-names
      ;; Optionally conditionalize on the required arguments.
      ;; Optionally warn when any are not found (development only).
      (when (and test-p conditions)
	(setq body
	      `((cond ((and ,@(nreverse conditions))
		       ,@body)
		      ,@(when (and warn-p (eval-feature :development))
			  `((t
			      (warn "In ~s:~%No bindings in ~s for ~{~a~^, ~}."
				    ',most-recent-defun-name
				    ,mouse-pointer
				    (append
				      ,@(loop for name in required-argument-names
					      collect `(unless ,name (list ',name))))))))))))


      `(let* ,(nreverse clauses)
	 ,@declarations
	 ,mouse-pointer
	 ,@body))))

;; This can be made more efficient later, by binding more arg simultaneously, etc.
;; Fetcher forms ought not to always be function calls.




;;; The macro `find-spot-of-type-and-return-value-of-slot' finds the innermost
;;; spot on the mouse-pointer bound to the variable MOUSE-POINTER [gross! -mhd]
;;; of the given slot-type, and returns the value of the slot denoted by
;;; slot-name and defining-class.  SPOT-TYPE can also be a list of types.  If
;;; the desired spot cannot be found, this returns nil.

(defmacro find-spot-of-type-and-return-value-of-slot
    (spot-type-or-types structure-slot-name)
  (let* ((spot-types (if (atom spot-type-or-types) (list spot-type-or-types) spot-type-or-types))
	 (bindings (loop for spot-type in spot-types
			 unless (type-description-of-type spot-type)
			   do (warn "The spot-type ~s is unknown." spot-type)
			 collect `(,spot-type (type-description-of-type ',spot-type))))
	 (conditions (loop for spot-type in spot-types
			   collect `(subtype-p-using-type-descriptions (type-description-of spot) ,spot-type))))
    `(let ,bindings
       (loop for spot = (stack-of-spots mouse-pointer)
		      then (enclosing-spot? spot)
	     while spot
	     when (or ,@conditions)
	       do (return (,structure-slot-name spot))))))


;;; The macro `find-spot-of-type' scans the spot stack seeking a
;;; spot of the desired type, returning NIL if none found.

(defmacro find-spot-of-type (mouse-pointer spot-type)
  `(loop
     with type-description-of-desired-type
       = (type-description-of-type ,spot-type)
     for spot = (stack-of-spots ,mouse-pointer) then (enclosing-spot? spot)
     while spot
     when (subtype-p-using-type-descriptions (type-description-of spot)
					     type-description-of-desired-type)
       do (return spot)))


;;; The macro `find-frame-in-spot-stack' finds the innermost frame
;;; represented by a spot in the stack which satifies the given predicate.
;;; Except, do not find the g2-window unless that is precisely what we are
;;; looking for.

(defmacro find-frame-in-mouse-pointer (mouse-pointer &optional predicate)
  `(loop for spot = (stack-of-spots ,mouse-pointer) then (enclosing-spot? spot)
	 while spot
	 until (entire-g2-window-spot-p spot)	    ; Do not find the frame-represented here.
	 for frame = (frame-represented? spot)
	 when (and frame ,(if predicate `(,predicate frame)))
	   return frame))


(defun find-frame-of-class-in-mouse-pointer (mouse-pointer class)
  (loop for spot = (stack-of-spots mouse-pointer) then (enclosing-spot? spot)
	while spot
	until (entire-g2-window-spot-p spot)	    ; Do not find the frame-represented here.
	for frame = (frame-represented? spot)
	when (and frame (frame-of-class-p frame class))
	  return frame))



;;;; Event handlers



;;; An `event-handler' is a function which can be bound to UI events.  They
;;; always receive exactly one argument, mouse-pointer.  There is a convenience
;;; macro which makes easy to reference anything which can be dug out of a
;;; mouse pointer.

(def-global-property-name new-style-event-handler)


;;; The global-property-name `event-handler-pretty-name?' records the name to
;;; place into the backtrace presented on a G2 abort.

(def-global-property-name event-handler-pretty-name?)

(defun event-handler-pretty-name (event-handler-name)
  (or (event-handler-pretty-name? event-handler-name)
      event-handler-name))

;;; An `event-handler-condition' is either NIL, meaning no condition, or the
;;; name of a boolean function of no arguments.  Event handler conditions are
;;; called during key lookup.  If it returns NIL, then the search is continued
;;; for the next applicable handler.

(def-global-property-name event-handler-condition)


;;; The macro `define-event-handler' defines a function of the same name as the
;;; event handler.  The lambda-list may include the name of any desired
;;; blackboard argument available in a mouse-pointer.  See
;;; with-mouse-pointer-bindings for more info. Options are :pretty-name and
;;; :condition. The condition must be a symbol naming a function of no
;;; arguments.

(defmacro define-event-handler (name-and-options lambda-list &body body)
  (let* ((name (car-or-atom name-and-options))
	 (options (cdr-or-atom name-and-options))
	 (mouse-pointer (make-symbol "MOUSE-POINTER"))
	 (pretty-name (getf options :pretty-name))
	 (condition (getf options :condition)))
    (multiple-value-bind (declarations inner-body documentation)
	(parse-body-declarations body)
      `(progn
	 (setf (new-style-event-handler ',name) ',name)
	 ,@(when pretty-name
	     `((setf (event-handler-pretty-name? ',name) ',pretty-name)))
	 ,@(when condition
	     `((setf (event-handler-condition ',name) ',condition)))
	 (defun ,name (,mouse-pointer)
	   ,@(when documentation `(,documentation))
	   ,mouse-pointer
	   (with-mouse-pointer-bindings ,lambda-list
	       ,mouse-pointer
	     ,@declarations
	     ,@inner-body))
	 ',name))))



;;;; Keymaps




;;; A `keymap' is an association of key-patterns and spot classes to commands.
;;; A workstation context specifies a list of keymaps to search in order for a
;;; handler for an event.  Each keymap gets its own paragraph in the HELP
;;; workspace, unless is declared private.  Keymaps stand by themselves.  One
;;; keymap can be shared by any number of workstation contexts.

;;; The buckets slot is a list of buckets, one per key-pattern represented.
;;; Each bucket is a list of the form (key-pattern type-1 handler-1 ... type-n
;;; handler-n).  The entries in the list have been sorted by the type from
;;; specific to general.  Note that "t" is the most general type.

;;; Event lookup proceeds as follows.  We find the first bucket which matches
;;; the key code, searching them in the order they were specified in
;;; define-keymap.  A type in the bucket matches if it is a supertype of either
;;; the event's spot, of any enclosing-spot of the event's spot, or of the
;;; event's object.  If no type matches, we then search the bucket, if any, for
;;; the wild event.  If nothing matches there, we then repeat the entire lookup
;;; on the keymaps in our parent context.

(def-global-property-name keymap-named)

(define-structure keymap ()
  (:conc-name t)
  (:constructor make-keymap-1)
  name
  pretty-name				; Name for the help workspace. If NIL, we are private.
  buckets				; Alist of key bindings
  namespace				; Of the bindings. This is INTERNAL for all but item configs.
  condition				; No-argument function. If returns NIL, keymap is invisible.
  filter				; Function on (keymap binding).  Defaults to (lambda (..) t).
  lookup-method				; Custom lookup function on (keymap keycode spot)
  describe-method)			; Custom describe function on (keymap frame?) -> table rows.


(defun make-keymap (name pretty-name bindings namespace condition
			 filter lookup-method describe-method)
  (let ((keymap (make-keymap-1)))
    (setf (keymap-name keymap) name
	  (keymap-pretty-name keymap) pretty-name
	  (keymap-namespace keymap) (or namespace 'internal)
	  (keymap-condition keymap) condition
	  (keymap-filter keymap) filter
	  (keymap-lookup-method keymap) lookup-method
	  (keymap-describe-method keymap) describe-method)

    (loop for (key-pattern class handler . options) in bindings doing
      (bind-key-in-keymap keymap key-pattern class handler options))

    (setf (keymap-named name) keymap)

    keymap))


(defmacro find-keymap-named (name &optional (warn-p t))
  `(or (keymap-named ,name)
       (and ,warn-p
	    (dwarn "Unknown keymap ~S" ,name))))

(defun keymap-enabled-p (keymap)
  (or (null (keymap-condition keymap))
      (funcall-ui (keymap-condition keymap))))

(defun keymap-private-p (keymap)
  (null (keymap-pretty-name keymap)))


;;; A `keymap-bucket' is a list of (key-pattern . handlers), which each handler
;;; is a list (spot-class handler-name . options).  Key-pattern is either a
;;; fixnum for simple key codes, or a symbol.

(defmacro keymap-bucket-key-pattern (bucket)
  `(first ,bucket))

(defmacro keymap-bucket-handlers (bucket)
  `(cdr ,bucket))

(defmacro make-keymap-bucket (conser key-pattern class handler options)
  `(,conser ,key-pattern
	    (,conser
	       (,conser ,class (,conser ,handler ,options))
	       nil)))

(defmacro keymap-bucket-empty-p (bucket)
  `(or (null ,bucket) (null (cdr ,bucket))))



;;; The macro `do-matching-keymap-buckets' runs body for each bucket whose key-pattern
;;; matches the given key-code.  This is used at run-time to lookup event
;;; handlers.

(defmacro do-matching-keymap-buckets ((bucket keymap keycode) &body body)
  (avoiding-variable-capture (&aux key-pattern)
    `(loop for ,bucket in (keymap-buckets ,keymap)
	   for ,key-pattern = (keymap-bucket-key-pattern ,bucket)
	   doing
       (when (key-code-matches-key-pattern-p ,keycode ,key-pattern) 
	 ,@body))))


;;; The substitution-macro `find-keymap-bucket-for-key-pattern' returns
;;; the bucket which handles the given key-pattern.  Note that this is
;;; NOT the same as find the bucket which matches a elemental key-code.

(def-substitution-macro find-keymap-bucket-for-key-pattern (key-pattern keymap)
  (assoc-equal key-pattern (keymap-buckets keymap)))



;;; The function `bind-key-in-keymap' binds the handler to the given key-pattern
;;; in the given keymap.  If the handler is NIL, then any extant binding is
;;; removed.

(defun bind-key-in-keymap (keymap key-pattern class handler? options)
  (let* ((buckets (keymap-buckets keymap))
	 (bucket? (find-keymap-bucket-for-key-pattern key-pattern keymap))
	 (place? (when bucket?
		   (loop for sublist on (keymap-bucket-handlers bucket?)
			 as (class-1 handler . options) = (car sublist)
			 when (eq class class-1)
			   return sublist)))
	 (old-entry? (car place?)))
    (cond ((null handler?)				    ; Remove old binding.
	   (when old-entry?
	     ;; Replacing destructive function remf with setf of nil.  (ghw 2/15/96)
	     (setf (second old-entry?) nil)))
					; (remf (keymap-bucket-handlers bucket?) class)))
	  (old-entry?					    ; Update old binding.
	   (setf (second old-entry?) handler?
		 (cddr old-entry?) options))
	  
	  (bucket?					    ; Add to old bucket in right spot.
	   (let ((new-entry (list* class handler? options)))
	     (loop as previous-cons = bucket? then (cdr sublist)
		   for sublist on (cdr bucket?)               ; Loss of abstraction here.
		   as (class-1 handler . options) = (car sublist)
		   when (ab-subtypep class class-1)	    ; Insert before sublist.
		     do (setf (cdr previous-cons) (cons new-entry sublist))
			(return)
		   finally
		     (setq bucket? (nconc bucket? (list new-entry))))))
	  (t						    ; Create a new bucket.
	   (setq bucket? (make-keymap-bucket cons key-pattern class handler? options))
	   (setf (keymap-buckets keymap) (nconc buckets (list bucket?)))))

    ;; Delete newly empty bucket.
    (when (keymap-bucket-empty-p bucket?)
      (setf (keymap-buckets keymap) (remove bucket? (keymap-buckets keymap))))
    
    keymap))

;; Must only be called at load time!



;;; The function `clear-keymap' removes all the bindings from a keymap.

#+development
(defun clear-keymap (keymap)
  (setf (keymap-buckets keymap) nil))



(defun structure-class (structure)
  (name-of-type-description (type-description-of structure)))


;;; The macro `def-spot-class-set' is a trivial macro used to define a
;;; abbreviation for a list of spot classes.  This is needed because there is no
;;; common superclass for all of the sets of spot classes we need.

(def-global-property-name spot-class-set)

(defmacro def-spot-class-set (name options &rest spot-class-names)
  options
  `(progn (setf (spot-class-set ',name) ',spot-class-names)
	  ',name))


(defun find-frame-in-spot (leaf-spot)
  (loop for spot = leaf-spot then (enclosing-spot? spot)
	while spot
	until (entire-g2-window-spot-p spot)
	thereis (frame-represented? spot)))


;;; The def-substitution-macro `lookup-key-in-bucket' supports
;;; `lookup-key-in-keymap.'  Here is where we implement the semantics of the
;;; CLASS part of an event binding.  The class is either:
;;;  (1) T, meaning this handler always applies (but is searched-for last),
;;;  (2) The name of a spot class, which matches the given spot or any enclosing spot.
;;;  (3) The name of a frame class, which matches the frame-represented? of spot or any enclosing spot.
;;;  (4) The name of a list of spot classes, as defined by def-spot-class-set

;;; The list of bindings in the bucket is sorted from most-specific to
;;; most-general by the class, so that we tend to find the most specific
;;; handler possible.

(defun lookup-key-in-bucket (bucket spot)
  (loop for (class handler . options) in (keymap-bucket-handlers bucket) doing
    (when (cond ((eq class t) t)
		((memq 'exact options) ; Means exact match to class of innermost spot,
					; or class of represented frame.
		 (let ((frame? (find-frame-in-spot spot)))
		   (or (eq class (structure-class spot))
		       (and frame? (eq class (class frame?))))))
		(t
		 (loop for spot = spot then (enclosing-spot? spot)
		       while spot
		       as spot-class = (structure-class spot)
		       as frame = (frame-represented? spot)
		       as spot-class-set = (spot-class-set class)
		       thereis (or (memq spot-class spot-class-set)
				   (ab-typep spot class)
				   (and frame (ab-typep frame class))))))
      (with-drawing-trace (keymap-1)
	(format t " MATCH: ~s matches class:~s options:~s handler:~s~%"
		spot class options handler))
      (return handler))))



;;; The defun `lookup-key-in-keymap' returns an event-interpretation associated
;;; with the given key-code and spot, or NIL.

(defun lookup-key-in-keymap (keymap keycode spot)
  (cond ((keymap-lookup-method keymap)
	 (funcall-ui (keymap-lookup-method keymap) keymap keycode spot))
	(t
	 (block search
	   (do-matching-keymap-buckets (bucket keymap keycode)
	     (let ((handler?
		     (lookup-key-in-bucket bucket spot))
		   (filter?
		     (keymap-filter keymap)))
	       (when (and handler? (or (null filter?)
				       (funcall-ui filter? keymap handler?)))
		 ;; Make an event interp in desired namespace, with no arguments.
		 (return-from search
		   (make-event-interpretation
		     (keymap-namespace keymap)
		     handler?
		     nil)))))))))

;; Notice how the lookup method doesn't use the filter or the namespace.



;;; The function `lookup-command-in-keymap' returns the keycode bound to the
;;; given command, if any.  Only simple, bindable keys are returned, not key
;;; patterns nor mouse gestures.

(defun lookup-command-in-keymap (keymap command-name)
  (block command-found
    (loop for bucket in (keymap-buckets keymap)
	  as key-pattern = (keymap-bucket-key-pattern bucket)
	  as abbrev? = (and (symbolp key-pattern)
			    (key-pattern-abbreviation key-pattern))
	  as alternate-key? = (and abbrev? (consp abbrev?)
				   (eq (car abbrev?) 'or)
				   (cadr abbrev?)) ; Multiple keys bound, arbitrarily pick first.
	  as key-code = (or alternate-key? key-pattern)
	  doing

      (when (and (fixnump key-code)	; Simple key
		 (not (mouse-key-code-p key-code)))
	(loop for (class handler) in (keymap-bucket-handlers bucket)
	      when (eq handler command-name)
		do (return-from command-found key-code))))))

;; TODO: return a list of all keys bound to command.


;;; The function `describe-keymap' returns a list of table rows which describe
;;; the given keymap.  The frame? argument is the interesting frame under the
;;; mouse, used in lieu of spot matching.  For the HELP command.

(defun describe-keymap (keymap frame?)
  (cond ((keymap-describe-method keymap)
	 (funcall-ui (keymap-describe-method keymap) keymap frame?))
	(t
	 (describe-keymap-into-table-rows
	   (tformat-text-string "~a" (keymap-pretty-name keymap))
	   (keymap-buckets keymap)))))




;;; The macro `define-keymap' creates a named keymap and adds it to a
;;; workstation context.  The bindings are in the form of a plist of
;;; alternating complex-event's and event handlers.  A complex event, you will
;;; recall, is either the name of a key-code, the list (key-name spot-class), or
;;; the list (OR complex-event ... complex-event).

;;; PRETTY-NAME is the label which appears in the HELP workspace.  If PRIVATE
;;; is true, then these bindings are not listed in the HELP workspace.

;;; Custom handlers may be supplied for filtering, lookup, and describe.  The
;;; filter method gets (keymap handler-name), and should return T or NIL.  The
;;; lookup method gets the arguments (keymap keycode spot) and should return an
;;; event-interpretation or NIL.  The describe method gets (keymap frame?) and
;;; should return a list of table rows.

(defmacro define-keymap (name (&key context (pretty-name name)
				    private
				    (namespace 'internal)
				    condition ; No-argument function enables entire keymap.
				    filter
				    lookup-method
				    describe-method)
			      &body key-bindings)
  (when (and lookup-method key-bindings)
    (warn "Key bindings ignored for keymap ~s with a lookup method." name))
  (multiple-value-bind (parsed-bindings inline-handlers)
      (parse-key-bindings name key-bindings)
    (when private
      (setq pretty-name nil))
    `(progn
       ,@inline-handlers
       (make-keymap ',name ',pretty-name
		    (optimize-constant ',parsed-bindings)
		    ',namespace
		    ',condition
		    ',filter
		    ',lookup-method
		    ',describe-method)
       ,@(when context
	   `((add-keymap-to-workstation-context ',name ',context)))
       #+development (keymap-named ',name))))



#+development
(defun show-keymap (keymap)
  (when (symbolp keymap)
    (setq keymap (keymap-named keymap)))
  (when keymap
    (format t "Keymap: ~s (~s)~%" (keymap-name keymap) (keymap-pretty-name keymap))
    (loop for bucket in (keymap-buckets keymap)
	  as key-pattern = (keymap-bucket-key-pattern bucket)
	  as key-pattern-name = (unparse-key-pattern key-pattern)
	  doing
      (loop for (class handler . options) in (keymap-bucket-handlers bucket)
	    doing
	(format t "~25a ~20a  ~20a ~a options:~a~%"
		(or key-pattern-name "")
		key-pattern
		class
		handler options)
	(setq key-pattern-name nil)))
    keymap))



;;;; User Interface Commands



;;; A `UI command' is basically a triple of functions: the command function
;;; itself, the translator from mouse-pointers to partial commands, and the
;;; command pursuer, which collects additional command arguments from menus.
;;; The translator function is also used for testing a command's applicability.

;;; They are statically allocated structures.

(define-structure ui-command ()
  (:constructor make-ui-command-1)
  ui-command-name		; The unique command name.
  ui-command-menu-name		; The name for restrictions and menus.  Might not be unique.
  ui-command-category		; The restrictions and grammar category: main-menu, item-menu, table-menu,
				; non-menu, keyboard.  If NIL, then this is an internal command.
  ui-command-function		; The function which implements the command.
  ui-command-translator		; The function on mouse-pointer which creates a partial command.
  ui-command-pursuer		; The function which fills in the next missing argument.
  ui-command-documentation	; A string
  ui-command-lambda-list	; Used only for its length, by make-empty-partial-command.
  ui-command-id			; Command ID, for stock commands.
  ui-command-labeler?)		; Function to compute menu label from partial command

(def-global-property-name ui-command-named)

(def-global-property-name ui-commands-with-menu-name)

(def-global-property-name ui-command-command-posts-dialog-p)

;;; The defparameter `+missing-argument+' is a special value of a command
;;; argument which implies that the argument still needs a value.

(defvar-of-special-global +missing-argument+ (make-symbol "MISSING-ARGUMENT"))
(defvar-of-special-global +abort-menu-choice+ (make-symbol "ABORT-MENU-CHOICE"))

;; It is actually important that these markers are symbols and not unique cons
;; cells: cons cells will be reclaimed!!



;; This will be used (someday) by an excel-like command key bindery.
(defvar-of-special-global list-of-all-ui-commands ())


#+development
(defun undefine-all-ui-commands ()
  (loop for cmd in list-of-all-ui-commands doing
    (undefine-ui-command (ui-command-name cmd)))
  (setq list-of-all-ui-commands nil))


#+development
(defun undefine-ui-command (name)
  (let ((cmd (ui-command-named name)))
    (when cmd
      (remprop name 'ui-command-named)
      (setf (ui-commands-with-menu-name (ui-command-menu-name cmd))
	    (remove cmd (ui-commands-with-menu-name (ui-command-menu-name cmd))))
      (setq list-of-all-ui-commands (remove cmd list-of-all-ui-commands))
      cmd)))


  
;;; The substitution-macro `missing-argument-p' is true if the argument is
;;; the magic value which represents MISSING.

(def-substitution-macro missing-argument-p (value)
  (eq value +missing-argument+))
  
  
;;; The function `find-ui-command' returns the UI command object
;;; given its unique name.

(defun find-ui-command (command-or-name &optional warn-p)
  (or (when (ui-command-p command-or-name)
	command-or-name)
      (ui-command-named command-or-name)
      (when warn-p
	(dwarn "Unknown UI command: ~s" command-or-name))))


(defun generic-name-of-exported-ui-command? (name)
  (built-in-menu-choice-p name))

;; (loop for command in (ui-commands-with-menu-name name) thereis <exported-p>)




(defun make-ui-command (name lambda-list &optional documentation (menu-name name) id)
  (let ((cmd (make-ui-command-1)))
    (setf (ui-command-name cmd) name
	  (ui-command-lambda-list cmd) lambda-list

	  (ui-command-documentation cmd) documentation

	  ;; The menu name MUST be a symbol, which is then translated.
	  (ui-command-menu-name cmd) (or menu-name name)
	  (ui-command-id cmd) id)

    (push-update cmd list-of-all-ui-commands :key ui-command-name)
    (push-update cmd (ui-commands-with-menu-name menu-name) :key ui-command-name)
    (setf (ui-command-named name) cmd)
    cmd))

;; This guy is run only at G2 startup (load) time.



;;; The defun-for-macro `availability-form-for-type' returns a form which
;;; tests for the "availabilty" of an object of the given presentation type.
;;; A presentation type if available if any object of that type has any hope
;;; of being found.  UI commands which require a presentation type which is
;;; not available are automatically disabled and removed from their menu.

(defun-for-macro availability-form-for-type (type)
  (multiple-value-bind (ptype? arguments options)
      (parse-presentation-type type)
    (declare (ignore options))
    (when ptype?
      (let ((tester? (and ptype? (presentation-type-available-p ptype?))))
	(when tester?
	  `(,tester? ,@arguments))))))



;;; The function `tester-form-for-type' returns a form which tests that thing
;;; is valid object of the given presentation type.  It is used to build the
;;; command condition which is tested just before the command is run, ie,
;;; within the com-xxx function.

(defun-for-macro tester-form-for-type (thing type)
  (let* ((ptype? (find-presentation-type type))
	 (predicate? (and ptype? (presentation-type-predicate ptype?))))
    (cond (predicate?
	   `(,predicate? ,thing))

	  ((eq type 'window)
	   `(gensym-window-p ,thing))

	  ;; This test is really just a hack.  The image-plane might still
	  ;; exist, but represent a different workspace than we thought.
	  ;; We should give image-planes a serial number, and snapshot them
	  ;; in the same way as blocks.
	  ((eq type 'image-plane)
	   `(valid-image-plane-p ,thing))

	  ((and (symbolp type) (class-description type))
	   `(of-class-p-function ,thing ',type)) ; of-class-p has a BIG macroexpansion.

	  ((blackboard-argument-type-p type)
	   ;; Any other blackboard arg: just check for non-NIL.
	   thing)
	  
	  (t
	   nil))))

;; This would be a good thing for ptypes to inherit.


(defun empty-command-pursuer (partial-command)
  (declare (ignore partial-command))
  nil)



;;; These four setf methods are defined for use by defun-in-place only.  They assume
;;; that the command exists.  The SET methods are defined separately functions in order
;;; to reduce te size of the macroexpansion of define-ui-command for a wimpy
;;; C compiler.

(defun get-ui-command-function (command-name)
  (ui-command-function (ui-command-named command-name)))

(defun get-ui-command-labeler (command-name)
  (ui-command-labeler? (ui-command-named command-name)))

(defun get-ui-command-translator (command-name)
  (ui-command-translator (ui-command-named command-name)))

(defun get-ui-command-pursuer (command-name)
  (ui-command-pursuer (ui-command-named command-name)))


(defun set-ui-command-function (command-name function)
  (setf (ui-command-function (ui-command-named command-name)) function))

(defun set-ui-command-labeler (command-name function)
  (setf (ui-command-labeler? (ui-command-named command-name)) function))

(defun set-ui-command-translator (command-name function)
  (setf (ui-command-translator (ui-command-named command-name)) function))

(defun set-ui-command-pursuer (command-name function)
  (setf (ui-command-pursuer (ui-command-named command-name)) function))


(defsetf get-ui-command-function set-ui-command-function)
(defsetf get-ui-command-labeler set-ui-command-labeler)
(defsetf get-ui-command-translator set-ui-command-translator)
(defsetf get-ui-command-pursuer set-ui-command-pursuer)



(defun lambda-list-of-ui-command-named (user-menu-choice-symbol? &optional default)
  (let ((command? (ui-command-named user-menu-choice-symbol?)))
    (if command?
	(ui-command-lambda-list command?)
	default)))


;;; The macro `define-ui-command' defines a lisp function which is invokable by the
;;; user from a menu choice or a keystroke.  It's name is user-visible and it's doc
;;; string may someday be user-visible.

;;; This defines a function with the given lambda-list, a mouse-pointer to partial-command
;;; translator, and a command pursuer.

;;; The command pursuer is a custom defun here so that we can easily allow presentation
;;; types which depend on previous arguments in the lambda-list.  Otherwise, we could
;;; have implemented a single "universal" command pursuer, and did.

;; The pursuer does not account for optional arguments.
;; As far as argument collection goes, optional args should be ignored?

;; define-ui-command is sensitive to a body which begins
;; with "unless" or "when". It peels off the condition and
;; uses it in both the partial-command-translator and the
;; command pursuer. The partial-command-translator is used,
;; for example, to determine whether the command appears in
;; menus. The command pursuer is used when the option is
;; actually selected. Using any other type of conditional
;; statement, such as "if", means that the
;; partial-command-translator will not contain that
;; condition. See comments on "command condition"
;; below. lgibson 7/16/99

;; May do the wrong thing if there are two BB arguments of the same type.  For example,
;; ((ws1 workspace) (ws2 workspace)) will bind ws1 and ws2 to the same workspace.  Probably
;; not what was intended.

;; Does not allow (name type) syntax for BB arguments!

(defmacro define-ui-command (name-and-options lambda-list &body body)
  "Allowed options are &key name pretty-name category label"
  (destructuring-lambda-list (command-name &key
					   (name command-name) ; The menu name and restrictions name.
					   pretty-name	    ; English translation string.
					   labeler          ; Function to compute label
					   category	    ; Grammar category.
					   dialog           ; Body posts a dialog
					   id)              ; For stock commands
      (if (atom name-and-options) (list name-and-options) name-and-options)

    (when (and name (not (symbolp name)))
      (warn "The name option ~s must be a symbol. It is used in user restrictions." name))
    (when (and pretty-name
	       (not (or (text-string-p pretty-name)
			(gensym-string-p pretty-name))))
      (warn "The pretty-name option ~s must be a string." pretty-name))
    
    (let ((translator-name (build-ab-symbol command-name 'command 'translator))
	  (pursuer-name (build-ab-symbol command-name 'command 'pursuer))
	  (function-name (build-ab-symbol 'com command-name))
	  (labeler-name (build-ab-symbol command-name 'command 'labeler))
	  argument-names argument-types cl-lambda-list
	  required-argument-names required-argument-types
	  blackboard-arguments required-blackboard-arguments
	  blackboard-arguments-lambda-list
	  availability-testers-for-other-arguments
	  condition
	  (mouse-pointer (make-symbol "MOUSE-POINTER")))
      
      ;; Parse the lambda-list
      (loop with optional-p
	    for argument in lambda-list
	    for lambda-keyword-p = (memq argument lambda-list-keywords)
	    for argument-name = (car-or-atom argument)
	    for argument-type = (if (consp argument) (second argument) argument)
	    doing
	(push argument-name cl-lambda-list)
	(cond ((eq argument '&optional)
	       (push '&optional blackboard-arguments-lambda-list)
	       (setq optional-p t))
	      ((not lambda-keyword-p)
	       (push argument-name argument-names)
	       (push argument-type argument-types)
	       (unless optional-p
		 (push argument-name required-argument-names)
		 (push argument-type required-argument-types))
	       (cond ((blackboard-argument-type-p argument-type)
		      ;; A list of blackboard args and types, with &optional where needed.
		      (push argument blackboard-arguments-lambda-list)
		      
		      (push argument-name blackboard-arguments)
		      (unless optional-p
			(push argument-name required-blackboard-arguments)))
		     ((find-presentation-type argument-type)
		      (let ((tester? (availability-form-for-type argument-type)))
			(when tester?
			  (push tester? availability-testers-for-other-arguments))))
		     (t
		      (warn "For command ~s: unknown presentation-type ~s" command-name argument-type))))))
      (setq argument-names (nreverse argument-names)
	    argument-types (nreverse argument-types)
	    required-argument-names (nreverse required-argument-names)
	    required-argument-types (nreverse required-argument-types)
	    cl-lambda-list (nreverse cl-lambda-list)
	    blackboard-arguments-lambda-list (nreverse blackboard-arguments-lambda-list)
	    blackboard-arguments (nreverse blackboard-arguments)
	    required-blackboard-arguments (nreverse required-blackboard-arguments)
	    availability-testers-for-other-arguments (nreverse availability-testers-for-other-arguments))
      
      ;; If there are no non-blackboard arguments, then we can optimize away the pursuer.
      (when (null lambda-list)
	(setq pursuer-name 'empty-command-pursuer))
      
      ;; Parse the body.
      (multiple-value-bind (declarations bare-body documentation)
	  (parse-body-declarations body)

	;; Scarf the command condition out of the body.
	(cond ((and (consp (car bare-body))
		    (memq (caar bare-body) '(when unless)))
	       (let ((which (caar bare-body)))
		 (unless (= (length bare-body) 1)
		   (warn "~s is discarding forms after the initial ~a" 'define-ui-command which))
		 (setq condition (case which
				   (when (cadr (car bare-body)))
				   (unless `(not ,(cadr (car bare-body)))))
		       bare-body (cddr (car bare-body)))))
	      (t
	       (setq condition t)))

	;; Disgorge.
	`(progn
	   (make-ui-command ',command-name ',lambda-list ',documentation ',name ',id)
	   ,@(when dialog
	       `((setf (ui-command-command-posts-dialog-p ',command-name) ',dialog)))
	   (defun-into-place (,function-name (get-ui-command-function ',command-name))
	       ,cl-lambda-list
	     ,@declarations
	     ,@(optimized-when-and
		 (append (loop for name in required-argument-names
			       for type in required-argument-types
			       for form = (tester-form-for-type name type)
			       when form collect it)
			 (and (neq condition t) (list condition)))
		 bare-body))

	   ;; Hmm. The body of the pursuer should not care about optional arguments?
	   ,@(if (eq pursuer-name 'empty-command-pursuer)
		 `((setf (get-ui-command-pursuer ',command-name) ',pursuer-name))
		 `((defun-into-place (,pursuer-name (get-ui-command-pursuer ',command-name))
		       (partial-command)
		     ;; (declare (values argument-name argument-type argument-place))
		     (gensym-dstruct-bind (,argument-names (partial-command-arguments partial-command))
		       ;; In order to pass onto pres types, we need the actual argument values here,
		       ;; not the snapshots. !!
		       ,@(loop for name in argument-names
			       collect `(setq ,name (command-argument-value ,name)))
		       (cond ,@(loop for name in argument-names
				     for type in argument-types
				     for position from 0
				     for evaluated-type
					 = (cond ((atom type) ; Handle ptype parameters & options.
						  `',type)
						 ((atom (car type))
						  `(slot-value-list ',(car type) ,@(cdr type)))
						 (t
						  `(slot-value-list (slot-value-list ',(caar type)
										     ,@(cdar type))
								    ,@(cdr type))))

				     ;; unless (blackboard-argument-type-p type)  ; An optimization.
				     collect `((missing-argument-p ,name)
					       (values ',name ,evaluated-type ,position))))))))
	   
	   (defun-into-place (,translator-name (get-ui-command-translator ',command-name))
	       (,mouse-pointer)
	     (with-mouse-pointer-bindings-no-warn ,blackboard-arguments-lambda-list
	       ,mouse-pointer
	       ,@declarations
	       (when ,(optimized-and (append availability-testers-for-other-arguments
					     (list condition)))
		 (make-partial-command
		   ',command-name
		   (slot-value-list ,@(loop for name in argument-names
					    collect
					    ;; If a blackboard argument is required, then if not found
					    ;; now, it is missing.
					    `(snapshot-command-argument
					       ,(cond ((memq name required-blackboard-arguments)
						       `(or ,name +missing-argument+))
						      ((memq name blackboard-arguments)
						       name)
						      (t
						       '+missing-argument+)))))))))
	   ,@(when labeler
	       `((defun-into-place (,labeler-name (get-ui-command-labeler ',command-name))
		     (partial-command pretty-name)
		   pretty-name
		   (gensym-dstruct-bind (,argument-names (partial-command-arguments partial-command))
		     ,@(loop for name in argument-names
			       collect `(setq ,name (command-argument-value ,name)))
		     (twith-output-to-wide-string
		       (tformat ,@labeler))))))

	   ,@(when category
	       `((add-words-as-instances-of-category ,category (,command-name))))

;	   ,@(when (and gesture context)
;	       (let ((key-pattern (parse-key-pattern gesture)))
;		 (when key-pattern
;		   `(define-key ',context ',key-pattern ',class ',command-name))))
	   
	   ,@(when (or (gensym-string-p pretty-name)
		       (text-string-p pretty-name))
	       `((def-menu-string ,name ,pretty-name)))

	   #+development (find-ui-command ',command-name))))))




;;;; Partial Commands (command instances)



(define-structure partial-command ()
  (:constructor make-partial-command-1)
  (:reclaimer reclaim-partial-command-1)
  (:managed t)
  (:conc-name t)
  name					; Get arg types from here (a command name).
  arguments)				; Either values, block snapshots, or +missing-argument+

(defun partial-command-p-function (thing)
  (partial-command-p thing))

(defun make-partial-command (command-name command-arguments)
  (let ((pc (make-partial-command-1)))
    (setf (partial-command-name pc) command-name
	  (partial-command-arguments pc) command-arguments)
    pc))

(defun reclaim-partial-command (partial-command)
  (let ((arguments (partial-command-arguments partial-command)))
    (loop for argument in arguments doing
      (reclaim-partial-command-argument argument))
    (reclaim-slot-value-list arguments)
    (reclaim-partial-command-1 partial-command)))

(defun copy-partial-command (partial-command)
  (let* ((name (partial-command-name partial-command))
	 (arguments (copy-list-using-slot-value-conses
		      (partial-command-arguments partial-command))))
    (loop for sublist on arguments
	  as argument = (first sublist)
	  doing
      (when (snapshot-of-block-p argument)
	(setf (first sublist) (copy-snapshot-of-block argument))))
    (make-partial-command name arguments)))


;; Nomenclature: a "Value" is a real lisp value to be passed to a command.
;;  an "argument" either a value, a snapshoted block, or a special missing marker,
;;   and is what is actually stored in partial-command-arguments.

(defun snapshot-command-argument (value)
  (cond ((and (framep value) (block-p value))
	 (make-snapshot-of-block value))
	(t
	 value)))
;; What about image-planes? mouse-pointers? Other structures?


(defun command-argument-value (argument)
  (cond ((snapshot-of-block-p argument)
	 (unless (snapshot-of-block-valid-p argument)
	   (dwarn "Deleted block in partial-command argument ~s" argument))
	 (block-of-snapshot argument))
	(t
	 argument)))

(defun command-argument-valid-p (argument)
  (if (snapshot-of-block-p argument)
      (snapshot-of-block-valid-p argument)
      t))


(defun reclaim-partial-command-argument (argument)
  (when (snapshot-of-block-p argument)
    (reclaim-snapshot-of-block argument)))

(defun partial-command-valid-p (partial-command)
  (loop for argument in (partial-command-arguments partial-command)
	always (command-argument-valid-p argument)))



;;; The function `make-initial-partial-command' is responsible for creating
;;; partial command instances given a command name and a mouse-pointer.  This
;;; is where we call the command translator on the mouse-pointer, which both
;;; creates the partial command instance, and fills in all the arguments which
;;; can be filled directly from the mouse pointer (it returns NIL if the
;;; command is unavailable on the given mouse-pointer).  We then fill in even
;;; more arguments whose presentation types specify an immediate value.
;;; Finally, we return the partial-command instance.  Note that the command may
;;; be complete and ready to run at this point.

(defun make-initial-partial-command (command-or-partial-command mouse-pointer)
  (cond ((null command-or-partial-command)
	 nil)
	((partial-command-p command-or-partial-command)
	 (copy-partial-command command-or-partial-command))
	(t
	 (let* ((command? (find-ui-command command-or-partial-command t))
		(partial-command? (when command?
				    (funcall-ui (ui-command-translator command?) mouse-pointer))))
	   (when partial-command?
	     (fill-in-immediate-arguments partial-command?)
	     partial-command?)))))



;;; The function `fill-in-mouse-pointer-arguments' fills in missing arguments
;;; whose values can be obtained from a mouse-pointer.  Normally, this is done
;;; by the UI command translator when the partial-command is first created.  It
;;; is not done, however, when creating commands for the menu bar (since no
;;; mouse-pointer is available at the time the menu bar is created).

(defun fill-in-mouse-pointer-arguments (partial-command mouse-pointer)
  (loop while (fill-in-next-mouse-pointer-argument partial-command mouse-pointer)))


(defun fill-in-next-mouse-pointer-argument (partial-command mouse-pointer)
  (multiple-value-bind (name type? place)
      (partial-command-next-argument partial-command)
    (declare (ignore name))
    (when (blackboard-argument-type-p type?)
      (let ((value? (get-magic-argument type? mouse-pointer)))
	(when value?
	  (bind-partial-command-argument partial-command
					 place
					 (snapshot-command-argument value?))
	  t)))))



;;; The function `fill-in-immediate-arguments' supplies any missing arguments
;;; whose presentation type has defined an "immediate-value".  This in done in
;;; order, from left to right in the arglist, until we run into an argument
;;; without an immediate value.

(defun fill-in-immediate-arguments (partial-command)
  (loop while (fill-in-next-immediate-argument partial-command)))



;;; The function `fill-in-next-immediate-argument' fills in an immediate value
;;; for the next missing argument, if any.  If returns the value, which must
;;; be non-NIL.

(defun fill-in-next-immediate-argument (partial-command)
  (multiple-value-bind (name type? place)
      (partial-command-next-argument partial-command)
    (declare (ignore name))
    (when type?
      (multiple-value-bind (ptype parameters options)
	  (parse-presentation-type type?)
	(declare (ignore options))
	(when ptype
	  (prog1
	      (when (presentation-type-immediate-value-function ptype)
		(let ((value? (apply (presentation-type-immediate-value-function ptype)
				     parameters)))
		  (when value?
		    (bind-partial-command-argument partial-command place value?)
		    value?)))
	    (reclaim-presentation-type type?)))))))



;; Soon, store this in place of the NAME slot.
(defun partial-command-command (partial-command)
  (find-ui-command (partial-command-name partial-command)))



;;; The function `partial-command-next-argument' find the first missing argument and returns
;;; its name, type, and place.  The type, if it is a cons, is a newly consed slot-value cons.

(defun partial-command-next-argument (partial-command)
; (declare (values argument-name argument-type argument-place))
  (let ((command (partial-command-command partial-command)))
    (funcall-ui (ui-command-pursuer command) partial-command)))


;;; The function `make-empty-partial-command' creates a partial-command for
;;; given command name with ALL arguments missing.

(defun make-empty-partial-command (command-or-command-name)
  (let ((command? (find-ui-command command-or-command-name)))
    (when command?
      (let* ((number-of-arguments (loop for argument in (ui-command-lambda-list command?)
					count (not (memq argument lambda-list-keywords))))
	     (arguments (make-slot-value-list number-of-arguments)))
	(loop for place on arguments
	      do (setf (car place) +missing-argument+))
	(make-partial-command (ui-command-name command?) arguments)))))



;; Yuck.
(defun command-or-partial-command-next-argument-type (command-or-partial-command)
  (let ((partial-command? (if (symbolp command-or-partial-command)
			      (make-empty-partial-command command-or-partial-command)
			      command-or-partial-command)))
    (when partial-command?
      (multiple-value-bind (argument-name argument-type argument-place)
	  (partial-command-next-argument partial-command?)
	(declare (ignore argument-name argument-place))

	(when (symbolp command-or-partial-command)
	  (reclaim-partial-command partial-command?))
	argument-type))))



;;; The function `reclaim-presentation-type' tries to tip-toe around the parts
;;; of a presentation-type which are statically consed, Pretty bogus, and
;;; should be fixed.

(defun reclaim-presentation-type (presentation-type)
  (when (consp presentation-type)
    (when (consp (car presentation-type))
      (reclaim-slot-value-list (car presentation-type)))
    (reclaim-slot-value-list presentation-type)))

      
  
;;; The function `presentation-type-wants-menu' returns T if this presentation
;;; type would like to post a menu to choose an object of that type.

(defun presentation-type-wants-menu (ptype?)
  (when ptype?
    (multiple-value-bind (ptype arguments options)
	(parse-presentation-type ptype?)
      (declare (ignore options))
      (presentation-type-admits-menu-p ptype)
      ;; Hmm. Shouldn't use APPLY here.
      (if (presentation-type-available-p ptype)
	  (apply (presentation-type-available-p ptype) arguments)
	  t))))


(defun partial-command-next-argument-wants-menu (command-or-partial-command)
  (let* ((ptype (command-or-partial-command-next-argument-type command-or-partial-command))
	 (wants-menu? (presentation-type-wants-menu ptype)))
    (reclaim-presentation-type ptype)
    wants-menu?))
    


(defun partial-command-next-argument-wants-dialog (command-or-partial-command)
  (let* ((command-name? (cond ((symbolp command-or-partial-command)
			       command-or-partial-command)
			      ((partial-command-p command-or-partial-command)
			       (partial-command-name command-or-partial-command))))
	 (ptype (command-or-partial-command-next-argument-type command-or-partial-command))
	 (wants-dialog? (or (ui-command-command-posts-dialog-p command-name?)
			    (presentation-type-admits-dialog-p ptype))))
    (reclaim-presentation-type ptype)
    wants-dialog?))


;; There are commands which collect further arguments in their bodies.
;; They must be declared by hand.



;; But, allow missing &optional arguments.
(defun partial-command-is-complete-p (partial-command)
  (loop for argument in (partial-command-arguments partial-command)
	never (missing-argument-p argument)))




;;;; Command journaling


;; This is a development-only utility which lives completely in
;; permanent cons space.


#+development
(def-system-variable command-journal new-menus ())


#+development
(defun make-journal-entry (command-name command-arguments)
  (list* 'journal-entry
	 (get-universal-time)
	 command-name
	 (loop for arg in command-arguments
	       collect (make-up-name-for-journal arg))))


#+development
(defun print-journal-entry (journal-entry &optional (stream *standard-output*))
  (gensym-dstruct-bind ((time command-name . args) (cdr journal-entry))
    (print-universal-time time stream)
    (format stream "  ~a ~{~a~^, ~}~%" command-name args)))


(defmacro lisp-princ-to-string (thing)
  #-ansi-cl
  `(lisp:princ-to-string ,thing)
  #+ansi-cl
  `(common-lisp:princ-to-string ,thing))

#+development
(defun make-up-name-for-journal (anything)
  (cond ((or (numberp anything)
	     (symbolp anything))
	 anything)
	((workstation-event-p anything)
	 (key-name (workstation-event-code anything)))
	(t
	 (lisp-princ-to-string anything))))



#+development
(defun print-universal-time (universal-time &optional (stream *standard-output*))
  (multiple-value-bind (sec min hour day month year)
      (decode-universal-time universal-time)
    (format stream "~d/~d/~d ~d:~2,'0d:~2,'0d~a"
	    month
	    day
	    (mod year 100)
	    (1+ (mod (1- hour) 12))
	    min
	    sec
	    (if (>= hour 12) "pm" "am"))
    universal-time))


#+development
(defun print-unix-time (unix-time &optional stream?)
  (let ((universal-time
	 (round
	   (unix-time-to-universal-time
	     (managed-float-value unix-time)))))
    (if stream?
	(print-universal-time universal-time stream?)
	(print-universal-time universal-time))))


#+development
(defun show-command-journal ()
  (loop for journal-entry in (reverse command-journal) doing
    (print-journal-entry journal-entry))
  (values))


  
(defun record-command-in-journal (command-name command-arguments)
  #-development (declare (ignore command-name command-arguments))
  #+development
  (let ((journal-entry (make-journal-entry command-name command-arguments)))
    (push journal-entry command-journal)
    journal-entry))





;;;; How to run a command



;;; The system-variable `ui-command-context' is bound occasionally to a symbol
;;; indicating the context in which a UI command function is being called.
;;; Currently, the only possible values are NIL and START-GENERIC, which means
;;; it is being checked/invoked via start-generic-command. UI commands are
;;; allowed to reference this variable. This a bit of a kludge.

(def-system-variable ui-command-context new-menus nil)

(def-substitution-macro ui-command-start-generic-context-p ()
  (eq ui-command-context 'start-generic))


;;; `Command-available-p' returns a boolean if the command can be started with
;;; the given mouse-pointer.

;;; A command is available if it's condition is met, and it's arguments
;;; are available.  Command arguments are available if either they
;;; can be obtained from the mouse-pointer, or if their presentation
;;; type provides a scheme for obtaining them from the user once the
;;; command is started.

;;; A command that is available-p may not necessarily be appropriate in the
;;; current configuration.

(defun command-available-p (command mouse-pointer)
  ;; command is a user menu choice, a command name, or a command instance.
  (cond ((and (mouse-pointer-is-multi-p mouse-pointer)
	      (not (command-runs-on-multi-selection-p command)))
	 nil)
	((consp command)		; (user-menu-choice choice-symbol)
	 (let ((frame? (compute-frame-for-selection mouse-pointer)))
	   (and frame?
		(not (null (get-user-menu-choice-or-choice-symbols
			     frame?
			     (second command)))))))
	(t
	 (let* ((command? (find-ui-command command t))
		(partial-command?
		  (when command?
		    (funcall-ui (ui-command-translator command?) mouse-pointer))))
	   (when partial-command?
	     (reclaim-partial-command partial-command?)
	     t)))))


;;; The function `start-ui-command' "starts" a UI command in response to an
;;; event, captured in the given mouse-pointer. We fill in all of the arguments
;;; we can from the mouse pointer.  This is done for us by the command
;;; translator which "translates" a command name and mouse-pointer in a partial
;;; command instance.  We then puruse the command, which will execute the
;;; command now if it has all of its arguments, or will post a menu if it needs
;;; more.

;;; If the command cannot bind all of its required mouse-pointer arguments
;;; (arguments which can ONLY be bound via a mouse-pointer), then nothing
;;; happens, except that a warning is optionally printed in development.

(defun start-ui-command (command-or-name mouse-pointer &optional warn-p)
  (let ((command? (find-ui-command command-or-name t)))
    (when command?
      (let ((partial-command? (funcall-ui (ui-command-translator command?) mouse-pointer)))
	(cond (partial-command?
	       (pursue-partial-command partial-command? mouse-pointer))
	      (warn-p
	       (dwarn "The command ~s could not find all of its required mouse-pointer arguments."
		      (ui-command-name command?))))))))



;;; The macro `funcall-ui-command' runs a named UI command on the given arguments.
;;; It bypasses all of the parsing of arguments out of mouse-pointers, etc, and
;;; simply takes the command arguments directly.  If the named command is unknown,
;;; it simply does nothing and returns NIL.  It does NOT enter the command into
;;; the journal.  This is the interface to use if you simply want to call the command
;;; as if it were an ordinary defun.

(defmacro funcall-ui-command (command-name &rest args)
  (let ((ui-command (make-symbol "UI-COMMAND")))
    `(let ((,ui-command (ui-command-named ,command-name)))
       (cond (,ui-command
	      (funcall-ui (ui-command-function ,ui-command) ,@args))
	     (t
	      (dwarn "UI command ~s not found" ,command-name)
	      nil)))))




;;; The function `execute-ui-command' is the bottleneck though which all command
;;; executions finally happen, except for those called directly with funcall-ui-command.
;;; This is where we record commands into the journal.  This would also be a good
;;; place for pushing a backtrace token.

(defun execute-ui-command (command-name command-arguments)
  (let ((ui-command? (ui-command-named command-name)))
    (cond (ui-command?
	   ;; Must record command first since its execution may reclaim some of
	   ;; the command arguments!
	   (record-command-in-journal command-name command-arguments)
	   (apply (ui-command-function ui-command?) command-arguments))
	  (t
	   (dwarn "UI command ~s not found" command-name)
	   nil))))


  
;;; `invoke-ui-command' is a convenience macro for the user to call a UI command
;;; from code just as if it was called from the user interface.  The command
;;; will be recorded into the journal.

(defmacro invoke-ui-command (command-name &rest args)
  (let ((command-arguments '#:command-arguments))
    `(let ((,command-arguments (gensym-list ,@args)))
       (prog1 (execute-ui-command ',command-name ,command-arguments)
	 (reclaim-gensym-list ,command-arguments)))))



;;; The function `execute-partial-command' executes a partial command once all of
;;; its arguments have been collected.  If any arguments have become invalid,
;;; we abort the command.  The partial command is reclaimed.

(defun execute-partial-command (partial-command)
  (cond ((not (partial-command-p partial-command))
	 (dwarn "Partial-command reclaimation error in invoke-partial-command"))	 

	((not (partial-command-valid-p partial-command))
	 (dwarn "Partial command ~s aborted. Some argument is invalid." partial-command))

	(t
	 (let ((command-name (partial-command-name partial-command))
	       (command-arguments
		 (loop for argument in (partial-command-arguments partial-command)
		       collect (command-argument-value argument)
			 using slot-value-cons)))
	   (prog1
	       (execute-ui-command  command-name command-arguments)
	     (reclaim-slot-value-list command-arguments)
	     (reclaim-partial-command partial-command))))))





;;; The function `pursue-partial-command' either runs the command function, if
;;; all of the arguments are present, or enters some new ws context, posts a
;;; menu, etc, to collect the missing arguments.  It takes ownership of the
;;; partial-command, either running it and reclaiming it, or reusing it for
;;; another menu.  At this point, the partial-command should live no where else
;;; in the system, especially not in some menu we are about to delete.

(defun pursue-partial-command (partial-command mouse-pointer &optional mode)
  (let* ((command (partial-command-command partial-command))
	 (pursuer (ui-command-pursuer command)))
    (fill-in-mouse-pointer-arguments partial-command mouse-pointer)
    (fill-in-immediate-arguments partial-command)
    (multiple-value-bind (argument-name argument-type argument-place)
	(funcall-ui pursuer partial-command)
      (declare (ignore argument-name argument-place))

      ;; If no next argument, then we're ready to play.
      (cond ((null argument-type)
	     (execute-partial-command partial-command))
	    (t
	     (collect-next-argument-for-partial-command
	       partial-command argument-type mouse-pointer mode))))))

;; mouse-pointer is where to post the menu.

;; MODE was supposed to control the manner in which the arguments are
;; collected: via menus, dialogs, typein, etc.

;; This is only used after the final menu choice is made.  It would be called,
;; eg, if the user selects the REGION in the item->region->color menu string,
;; then here we popup the standalone menu of colors for that region.  This is
;; NOT where submenus get posted while walking menus.  That is done by
;; track-mouse-in-walking-menus-context. IS THIS TRUE??? -fmw, 1/14/02


;;;; Collecting arguments



;;; The defvar `presentation-mode' describes alternative ways of collecting
;;; arguments for commands.  Presentation types can reference this special
;;; variable to modify their behavior.  If NIL, then the default behavior is
;;; assumed.

(defvar presentation-mode nil)

;; The presentation-mode is effectively an additional ptype argument which
;; controls some details about how the ptype collects its argument.  It
;; presently has only one use: to switch the color argument for some commands
;; from the first-level color menu to the second-level menu.  This is how we
;; can force a different menu even though the same command and argument is
;; being pursued in each case.

;; Ideally, this would be a presentation argument, not a special variable.




;;; The function `collect-next-argument-for-partial-command' posts
;;; a parameter menu which collects the next missing argument for the
;;; command.

(defun collect-next-argument-for-partial-command
    (partial-command argument-type mouse-pointer mode)
  (let ((ptype? (find-presentation-type argument-type t))
	(presentation-mode mode))
    (when ptype?
      (prog1
	  (let ((menu? (make-parameter-submenu-for-partial-command
			 partial-command mouse-pointer)))
	    (when menu?
	      (expose-menu menu?
			   (x-of-mouse-pointer mouse-pointer)
			   (y-of-mouse-pointer mouse-pointer))))

	(reclaim-presentation-type argument-type)))))

;; What is THING and MP here??  They have to be passed down from the original
;; menu posting.  For command menus, What-this-is-a-menu-for?  could be,
;; actually, every block which appears in any partial command's arglist.
;; what-this-is-menu-for is really just a form of validation for menus.



;;; The function `more-missing-arguments-p' is true if the command has
;;; additional arguments missing after the one pointed to by argument-place.
;;; This is used to decide whether to make each menu-item for this argument
;;; have a submenu for the next argument.  KLudgey.  Used as a wuick test.

(defun more-missing-arguments-p (partial-command argument-place)
  (loop for argument in (cdr (nthcdr argument-place (partial-command-arguments partial-command)))
	thereis (missing-argument-p argument)))




;;; The function `partial-command-requires-submenu-after-this-choice' performs
;;; this boolean test: if VALUE is substituted for the WHICH-ARGUMENT argument
;;; in the partial-command (we assume that that argument is now missing), then
;;; does the partial-command require any menus to collect any further argument
;;; values.  This is one place where immediate values for presentation types
;;; can prevent submenus from appearing.

;;; This returns a newly consed partial-command, with the choice filled-in,
;;; if a submenu is required!

(defun partial-command-requires-submenu-after-this-choice
    (partial-command which-argument value)
  (let ((new-partial-command (copy-partial-command partial-command)))
    (bind-partial-command-argument new-partial-command which-argument value)
    (fill-in-immediate-arguments new-partial-command)
    (cond ((not (partial-command-is-complete-p new-partial-command))
	   new-partial-command)
	  (t
	   (reclaim-partial-command new-partial-command)
	   nil))))



;;; The function `parameter-menu-item-submenu-p' returns T if the given
;;; menu-item has a submenu, hence needs one of those hinky-binkies after it.

(defun parameter-menu-item-submenu-p
    (menu-description menu-item partial-command argument-place arg-3)
  (declare (ignore arg-3))
  (or (menu-item-submenu-p menu-description menu-item)
      (and (more-missing-arguments-p partial-command argument-place)
	   (let ((new-partial-command?
		   (partial-command-requires-submenu-after-this-choice
		     partial-command
		     argument-place
		     (transform-menu-item-after-choice menu-description menu-item))))
	     (when new-partial-command?
	       (reclaim-partial-command new-partial-command?)
	       t)))))



;;; The function `make-parameter-submenu-for-partial-command' makes the menu
;;; needed to collect the next missing argument of the given partial-command.
;;; If the command needs no more arguments, we return NIL.  The partial command
;;; is NOT copied, it becomes owned by the menu.

(defun make-parameter-submenu-for-partial-command (partial-command mouse-pointer &optional adjustment)
  (let* ((command (partial-command-command partial-command))
	 (pursuer (ui-command-pursuer command)))
    (multiple-value-bind (argument-name argument-type argument-place)
	(funcall-ui pursuer partial-command)
      (declare (ignore argument-name))
      (multiple-value-bind (ptype? parameters options)
	  (parse-presentation-type argument-type)
	(when ptype?
	  (prog1
	      (let* ((menu-name? (presentation-type-menu ptype?))
		     (menu-description? (and menu-name? (menu-description-named menu-name?))))
		(when menu-description?
		  (make-parameter-menu menu-name?
				       partial-command
				       argument-place mouse-pointer adjustment parameters options
				       nil nil
				       #'parameter-menu-item-submenu-p
				       partial-command argument-place)))
	    (reclaim-presentation-type argument-type)))))))





;;; The function `bind-partial-command-argument' binds the WHICH-ARGUMENT-th
;;; argument of the partial-command to the given value.  The value is
;;; snapshotted as needed.

(defun bind-partial-command-argument (partial-command which-argument value)
  #+development (assert (missing-argument-p (nth which-argument
						 (partial-command-arguments partial-command))))
  (setf (nth which-argument (partial-command-arguments partial-command))
	(snapshot-command-argument value)))


;;; The function `unbind-partial-command-argument' sets the WHICH-ARGUMENT-th
;;; argument back to MISSING.

(defun unbind-partial-command-argument (partial-command which-argument)
  (let* ((arguments (partial-command-arguments partial-command))
	 (old-argument (nth which-argument arguments)))
    (reclaim-partial-command-argument old-argument)
    (setf (nth which-argument arguments)
	  +missing-argument+)))




;;;; Menu descriptions


;;; Menu descriptions are simply registered lists of commands and submenus.
;;; These descriptions have to be able to describe all classes of menus:
;;; command, parameter, subcommand, etc.  So, they need the union of their
;;; slots.

;; Return a menu description given its name.
(def-global-property-name find-menu-description)

(defun menu-description-named (name?)
  (when name?
    (find-menu-description name?)))


;; Return a list of menus defined on a given class.
(def-global-property-name menu-descriptions-for-class)


(define-structure menu-description ()
  (:constructor make-menu-description-1)
  (:conc-name t)
  name				; Name for indexing
  title				; String, symbol to translate, or (:funcall function). Gets menu params.
  documentation
  classes			; The spot-types to which we apply.
  choice-function	        ; Default choice handler. gets (menu menu-item choice . args)
  no-choice-function		; Function to call when no choice made. Same args, but item & choice are NIL.

  restriction-type		; What type of restrictions (main-menu, table-menu) affects us, if any.
  condition			; Predicate which determines our applicability. Gets (mouse-pointer)
  choice-transformer		; Function to xform menu-item-values before handing them to the choice function.
  submenu-choices		; Function on an explicit submenu item to return a list of items (optional).
  make-text-cell		; Function to create text cell from a choice.
  single-lines?			; Some default formatting options.
  capitalize?
  strip-hyphens?
  menu-type			; command-menu or parameter-menu
  choice-list-internal)		; A constant list of choices, or, a function to compute a slot-value list.




(defun make-menu-description
    (name doc classes title condition make-text-cell
	  single-lines capitalize strip-hyphens
	  choice-function no-choice-function 
	  restriction-type choice-transformer submenu-choices menu-type
	  choices)
  (let ((menu (make-menu-description-1)))
    (setf (menu-description-name menu) name
	  (menu-description-documentation menu) doc
	  (menu-description-title menu) (or title name)
	  (menu-description-classes menu) classes
	  (menu-description-make-text-cell menu) make-text-cell
	  (menu-description-condition menu) condition
	  (menu-description-restriction-type menu) restriction-type
	  (menu-description-choice-transformer menu) choice-transformer
	  (menu-description-submenu-choices menu) submenu-choices
	  (menu-description-menu-type menu) menu-type

	  (menu-description-single-lines? menu) single-lines
	  (menu-description-capitalize? menu) capitalize
	  (menu-description-strip-hyphens? menu) strip-hyphens

	  (menu-description-no-choice-function menu) no-choice-function
	  ;; Wrong place for this decision.
	  (menu-description-choice-function menu)
	  (or choice-function
	      (case menu-type
		(parameter-menu #'parameter-menu-choice-function)
		(command-menu #'command-menu-choice-function)))
	  (menu-description-choice-list-internal menu) choices)

    ;; Keep this sorted such that menus with conditions are first.
    (loop for class in classes doing
      (push-update menu (menu-descriptions-for-class class) :key menu-description-name))
    (setf (find-menu-description name) menu)))


;;; The function `menu-available-p' checks the menu's supplied condition,
;;; but NOT its spot attachment!

(defun menu-available-p (menu-description mouse-pointer)
  (let ((condition (menu-description-condition menu-description)))
    (or (null condition)
	(funcall condition mouse-pointer))))


;;; The function `menu-obtains-p' is true iff the menu which
;;; would have popped up for mouse-pointer is the given named
;;; menu.

(defun menu-obtains-p (name-of-menu mouse-pointer)
  (let ((menu-description? (find-menu-description name-of-menu)))
    (and menu-description?
	 (eq menu-description?
	     (find-menu-for-spot (stack-of-spots mouse-pointer))))))



  
;;; The function `find-menu-for-spot' returns the description of the popup menu
;;; appropriate for the given mouse spot.  It performs the "Sawtooth" search:
;;; first, we look for a menu defined on any superclass of the innermost spot.
;;; Failing there, we then move to the enclosing spot and search again.  This
;;; is where we diverge from CLIM's semantics: the operations available in CLIM
;;; are determined entirely by "what you clicked on", which is defined to be
;;; the innermost spot.

;; Compare this search with that for event handlers.  Maybe they can be merged.

(defun find-menu-for-spot (spot)
  (block found
    (let ((mouse-pointer (mouse-pointer-of-spot spot)))
      (loop for class-name in (inheritance-path-of-type-description (type-description-of spot))
	    until (eq class-name 'NAMED-GENSYM-STRUCTURE)   ; KLudge.
	    for menu-descriptions = (menu-descriptions-for-class class-name)
	    doing
	(loop for desc in menu-descriptions
	      when (menu-available-p desc mouse-pointer)
		do (return-from found desc))))))

;; What if more than one menu applies?
;; Maybe the menu should depend on the mouse gesture, too?  Store menus as in keymaps?


;;; The function `within-spot-of-type-p' is used by menu conditions to implement the "within"
;;; keyword.

(defun within-spot-of-type-p (mouse-pointer spot-type-or-frame-class)
  (loop for spot = (stack-of-spots mouse-pointer) then (enclosing-spot? spot)
	while spot
	for frame = (frame-represented? spot)
	thereis (or (ab-typep spot spot-type-or-frame-class)
		    (and frame (ab-typep frame spot-type-or-frame-class)))))



#+development
(defun describe-find-menu-for-spot (spot)
  (let ((mouse-pointer (mouse-pointer-of-spot spot)))
    (loop for class-name in (inheritance-path-of-type-description (type-description-of spot))
	  until (eq class-name 'NAMED-GENSYM-STRUCTURE)   ; KLudge.
	  for menu-descriptions = (menu-descriptions-for-class class-name)
	  appending
      (loop for desc in menu-descriptions
	    when (menu-available-p desc mouse-pointer)
	      collect desc and
	      do (format t "~a: ~s~%" class-name desc)))))



;; I suppose I ought to put this in a ptype slot!
(defun presentation-type-choice-transformer (presentation-type-or-name)
  (let ((ptype? (find-presentation-type presentation-type-or-name)))
    (when ptype?
      (let ((menu-name? (presentation-type-menu ptype?)))
	(when menu-name?
	  (let ((menu-descriiption? (menu-description-named menu-name?)))
	    (when menu-descriiption?
	      (menu-description-choice-transformer menu-descriiption?))))))))


;;; The macro `defmenu' defines the list of possible choices in a menu for the
;;; given class of object. CLASS is the type of spot to which we apply, if any.
;;; If the innermost spot of a mouse click is of class CLASS, or any subclass
;;; of CLASS and there is no defmenu defined on the any of those subclasses,
;;; then this will be that click's menu.

;;; The body should be either a list of items, or a form which computes the
;;; list of items.  Computed item lists must be newly consed slot-values, and
;;; are reclaimed by the menu system with reclaim-slot-value. See
;;; `map-over-menu-items'.

(def-global-property-name exported-menu-description-for-class)

(defmacro defmenu (name-and-options classes &body items)
  (macrolet ((emit-code (code)
	       `(push ,code code))
	     (emit-function-for (option)
	       `(when (consp ,option)
		  (let ((function-name (build-ab-symbol menu-name ',option 'function)))
		    (emit-code `(defun ,function-name ,(car ,option) ,@(cdr ,option)))
		    (setq ,option (list ':funcall function-name))))))
    (let ((code ())
	  (within? (memq :within classes)))
      (destructuring-lambda-list
	  (menu-name &key
		(type 'command-menu) ; command-menu, parameter-menu. Should default to NIL.
		name		     ; Name used to lookup translations
		title		     ; String, symbol, or ((parameters) . body)
		choice-function	     ; Function to call if choice made.
		no-choice-function   ; Function to call if deleted with no choice.
		make-text-cell
		documentation
		restriction-type
		parameters
		choice-transformer
		submenu-choices
		(class-name-or-names-for-export nil)
		(condition t)
		(capitalize nil)	    ; Only main-menu.
		(strip-hyphens t)
		(single-lines t))
	  (if (atom name-and-options) (list name-and-options) name-and-options)

	;; Maybe dig a condition out of the classes spec.
	(when within?
	  (setq classes (ldiff classes within?)
		condition `(within-spot-of-type-p mouse-pointer ',(cadr within?))))

	(let ((condition-name (when (neq condition t)
				(build-ab-symbol menu-name 'menu 'condition)))
	      (choice-computer-name nil)
	      (choice-computer-body nil)
	      (name-for-translations (or name menu-name)))

	  ;; Allow the body to be the body of a choice computer.
	  (when (and (singleton? items)
		     (consp (first items))
		     (not (menu-item-special-p (first items))))
	    (setq choice-computer-name (build-ab-symbol menu-name 'compute 'choices)
		  choice-computer-body items
		  items choice-computer-name))

	  (when condition-name
	    (emit-code `(defun ,condition-name (mouse-pointer)
			  mouse-pointer
			  ,condition)))
	  (when choice-computer-name
	    (emit-code `(defun ,choice-computer-name (mouse-pointer ,@parameters)
			  mouse-pointer
			  ,@choice-computer-body)))

	  (emit-function-for title)
	  
	  ;; A title string is just a translation for the menu name.
	  (when (or (gensym-string-p title)
		    (text-string-p title))
	    (emit-code `(def-menu-string ,name-for-translations ,title)))

	  (emit-code
	    `(make-menu-description
	       ',menu-name ',documentation ',classes
	       ',(if (or (gensym-string-p title)
			 (text-string-p title))
		     name-for-translations
		     title)
	       ',condition-name ',make-text-cell
	       ',single-lines ',capitalize ',strip-hyphens
	       ,(massage-function-spec choice-function)
	       ,(massage-function-spec no-choice-function)
	       ',restriction-type ',choice-transformer
	       ',submenu-choices
	       ',type
	       (optimize-constant ',items)))
	  (cond ((and class-name-or-names-for-export
		      (consp class-name-or-names-for-export))
		 (loop for class-name in class-name-or-names-for-export
		       do
		    (emit-code
		      `(setf (exported-menu-description-for-class
			       ',class-name)
			       ',menu-name))))
		(class-name-or-names-for-export
		 (emit-code
		   `(setf (exported-menu-description-for-class
			    ',class-name-or-names-for-export)
			  ',menu-name))))
	  (optimize-progn
	    `(progn ,@(nreverse code))))))))

;; Allow the lambda-less notation for inline functions here.


;;; SYSTEM MENU CHOICE EXPORT
;;;

(defun system-menu-choices-for-class (class-name)
  (let ((menu-description
	  (menu-description-for-class class-name))) 
    (when menu-description
      (allocate-evaluation-sequence
	(menu-description-choice-names menu-description)))))

(defun menu-description-for-class (class-name)
  (loop with class-description = (class-description class-name)
	with class-inheritance-path = (class-inheritance-path class-description)
	for super-class in class-inheritance-path
	thereis
	(menu-description-local-to-class-if-any super-class)))

(defun menu-description-local-to-class-if-any (class-name)
  (let ((menu-description-name?
	  (exported-menu-description-for-class class-name)))
    (when menu-description-name?
      (menu-description-named menu-description-name?))))


;;; The function `menu-description-choice-names' returns a newly consed
;;; eval-list of the top-level menu items for the given menu, ignoring
;;; dynamically computed menu item lists.

(defun menu-description-choice-names (menu-description)
  (let ((result nil)
	(list-or-function
	  (menu-description-choice-list-internal menu-description)))
    (cond ((atom list-or-function)
	   ;(eval-push list-or-function result))
	   )
	  (t
	   (loop for symbol-or-list in list-or-function
		 do
	     (cond ((atom symbol-or-list)
		    (let ((command-structure?
			    (ui-command-named symbol-or-list)))
		      (eval-pushnew (if command-structure?
					 (ui-command-menu-name command-structure?)
					 symbol-or-list)
				     result)))
		   (t ;(include <included-menu-name>)
		    (let* ((included-menu-name
			     (cadr symbol-or-list))
			   (included-menu-description?
			     (menu-description-named included-menu-name)))
		      (when included-menu-description?
			(setf result (nconc
				       (menu-description-choice-names included-menu-description?)
				       result)))))))))
    (nreverse result)))



;;;; Menu Items



;;; A `menu item' is an entry in a menu.  They have a simple list structure so
;;; that they can be listed explicitly in the body of defmenu.

(def-concept menu-item)

;;; Possible menu-item formats (lists are slot-value lists):

;;;   A symbol
;;;   The symbol -|spacer|-
;;;   A partial-command instance.
;;;   (CHOICE <label> <value> . plist)
;;;   (COMMAND <label> <command-name-or-partial-command>)
;;;   (USER-MENU-CHOICE <name>)
;;;   (INCLUDE menu-name &optional <label>)
;;;   (SUBMENU menu-name &optional <label>)
;;;   (DIALOG <label> <function>)
;;;   (ROW . menu-items)



;;; The macro `make-menu-choice' creates a "choice" menu item with the given
;;; value.  Optionally, a different label to display in the menu.  If a label
;;; is given, it must be a symbol or a text-string and it is CONSUMED by this
;;; macro.

(defmacro make-menu-choice (value &optional label)
  (avoiding-variable-capture (value label)
    `(slot-value-cons
       'choice
       (slot-value-cons
	 ,value
	 (if ,label
	     (slot-value-cons ,label nil))))))


(defun copy-menu-item (menu-item)
  (copy-for-slot-value menu-item))



;;; The function `reclaim-menu-item' reclaim a menu-item, which is either a
;;; partial-command, or a slot-value. It also reclaims frames, which are never
;;; menu items (so far), but are pushed onto the other-things-to-reclaim list.

(defun reclaim-menu-item (menu-item)
  (cond ((snapshot-of-block-p menu-item) ; Added for native menus -fmw, 1/17/02
	 (if (snapshot-of-block-valid-p menu-item)
	     (delete-menu (block-of-snapshot menu-item)))
	 (reclaim-snapshot-of-block menu-item))
	((partial-command-p menu-item)
	 (reclaim-partial-command menu-item))
	((consp menu-item)
	 (reclaim-slot-value menu-item))))

;; Careful!!
;; ensure-that-menu-item-will-be-reclaimed is taking care of the reclaiming
;; of partial commands?



;;; The def-substitution-macro `menu-item-is-spacer-p' defines spacers as symbols
;;; consisting only hyphens or -spacer- (lowercase).

(def-substitution-macro menu-item-is-spacer-p (menu-item)
  (and (symbolp menu-item)
       (or (eq menu-item '-|spacer|-)
	   (loop with name = (symbol-name-text-string menu-item)
		 for i below (text-string-length name)
		 as char = (charw name i)
		 always (char=w char #.%\-)))))


(def-substitution-macro menu-item-is-row-p (menu-item)
  (and (consp menu-item)
       (eq (car menu-item) 'row)))


(defun menu-item-ncolumns (menu-item)
  (cond ((menu-item-is-row-p menu-item)
	 (length (cdr menu-item)))
	(t
	 1)))


(defun menu-item-plist (menu-item)
  (and (consp menu-item)
       (eq (car menu-item) 'choice)
       (cdddr menu-item)))


(defun menu-item-special-p (menu-item)
  (and (consp menu-item)
       (memq (car menu-item) '(include submenu choice command user-menu-choice row))))


(defun menu-item-explicit-submenu (menu-description menu-item)
  (declare (ignore menu-description))
  (when (and (consp menu-item)		; (submenu <menu-name> &optional <label>)
	     (eq (car menu-item) 'submenu))
    (cadr menu-item)))

;; Maybe allow the submenu's item list to be inlined here.
;; Or, a function to return the items.  The class menu hierarchy might need this feature.



;;; The function `menu-item-dialog' returns the function which runs the dialog.

(defun menu-item-dialog (menu-item)
  (when (and (consp menu-item)		; (dialog <label> <function>)
	     (eq (car menu-item) 'dialog))
    (third menu-item)))



;; (command <label> <command-name-or-partial-command>)

(defun menu-item-is-command-p (menu-item)
  (or (symbolp menu-item)
      (and (consp menu-item)
	   (eq (car menu-item) 'command))
      (partial-command-p menu-item)))


(defun menu-item-command-name (menu-item)
  (cond ((symbolp menu-item)
	 menu-item)
	((and (consp menu-item)
	      (eq (car menu-item) 'command))
	 (third menu-item))))

(defun menu-item-command (menu-item)
  (or (menu-item-command-name menu-item)
      (and (partial-command-p menu-item)
	   menu-item)))



;;; The function `menu-item-submenu-p' returns non-NIL if this menu-item has a
;;; submenu.

(defun menu-item-submenu-p (menu-description menu-item)
  (or (menu-item-explicit-submenu menu-description menu-item)
      (cond ((menu-item-is-spacer-p menu-item)
	     nil)

	    ((eq (menu-description-menu-type menu-description)
		 'parameter-menu)
	     nil)

	    ((menu-item-is-command-p menu-item)
	     (partial-command-next-argument-wants-menu (menu-item-command menu-item))))))

;; This is an older piece of code, now somewhat questionable.
;; Note that parameter menus override this function.  See `parameter-menu-item-submenu-p'.



;;; The function `menu-item-name' returns the name to compare against
;;; user restrictions.

(defun menu-item-name (menu-item)
  (cond ((partial-command-p menu-item)
	 (ui-command-menu-name (partial-command-command menu-item)))
	((and (consp menu-item)		      ; (command <label> <command-name-or-pc>)
	      (eq (first menu-item) 'command))
	 (second menu-item))
	(t
	 (menu-item-value menu-item))))



;;; The function `menu-item-value' returns the "value" of the menu-item,
;;; meaning the token returned to the client of the menu.

(defun menu-item-value (menu-item)
  (cond ((consp menu-item)		; (choice <label> <value> . plist)
					; (command <label> <command-name-or-pc>)
					; (user-menu-choice <name>)
					; (submenu menu-name &optional <label>)
	 (case (car menu-item)
	   ((choice command)
	    (third menu-item))		; command name or partial command.
	   (user-menu-choice
	    (second menu-item))
	   (submenu
	    (or (third menu-item)
		(second menu-item)))
	   (t
	    menu-item)))
	((menu-item-is-spacer-p menu-item)
	 nil)
	(t
	 menu-item)))



;;; The function `translated-string-for-symbol' returns an appropriately
;;; translated and capitalized string to display for a menu item symbol or
;;; string.
;;;
;;; When there is a translation, the treatment of its capitalization will
;;; depend on whether the translation was given as a symbol or as a string.
;;; If it is a symbol, then we let the default capitalization policy apply
;;; as dictated by the menu it is to be part of, which is signaled here by
;;; the value of capitalize?. If it is a string, then we presume that any
;;; capitalization that the string has is intended to apply regardless of
;;; the menu's policy. The is particularly germane for German, where terms
;;; like 'cut' are capitalized even though the menu where it would appear,
;;; edit-operations, would otherwise want to produce lower case menu items.
;;; ddm 7/27/99

;;; Menu item symbols can already have strings associated with them even if
;;; they are not translated in the current-language. The function
;;; `def-menu-string' and the pretty-name option to `define-ui-command'
;;; both introduce strings for menu symbols that are accessed here with
;;; `menu-string'.
;;;
;;; I have observed that there appears to be a tacit convention that the
;;; only reason strings are explicitly associated with menu symbols is to
;;; handle the capitalization issues in multi-word menu strings when the
;;; default policy (capitalizing just the first letter of every
;;; hyphen-delimited term within the symbol) would be inadequate,
;;; e.g. "Drop to Bottom", "Load KB".  ddm 8/5/99

(defun translated-string-for-symbol (symbol &optional capitalize? strip-hyphens?)
  (let* ((translation? (and (symbolp symbol)
			    (translation-for-symbol? symbol)))
	 (default (or (menu-string symbol)
		      symbol))
	 (menu-name (or translation?
			default)))

    (cond ((symbolp menu-name)
	   (copy-symbol-name menu-name
			     (if (eq capitalize? t)
				 :first-of-each-word
				 capitalize?)
			     strip-hyphens?
			     nil
			     known-gensym-acronyms))
	  
	  ((text-string-p menu-name)
	   (if (or translation? capitalize?)
	       (copy-text-string menu-name) ; Ignoring capitalize?
	       (copy-text-string-with-case-conversion menu-name :none)))
	  
	  #+development
	  (t (error "Bogus data structure for menu item: ~s" menu-name)))))


;;; The function `compute-modified-menu-item-string' removes "&"s from string if
;;; we are not using native menus, and appends "..." if we are and the item
;;; posts a dialog.

(defun compute-modified-menu-item-string (menu-item string)
  (let ((native? (and (current-window) (native-pop-up-menus-p (current-window)))))
    (unless native?
      (setq string (prog1 (remove-character-from-wide-string  #.%& string)
		     (reclaim-text-string string))))
    (when (and native?
	       (partial-command-next-argument-wants-dialog menu-item))
      (setq string (prog1 (tformat-text-string "~a..." string)
		     (reclaim-text-string string))))
    string))


;;; The function `menu-item-string' returns the label for a menu item, as a
;;; newly consed text string.  The parameters are those given to any possible
;;; submenu item, which acquires the title of its submenu.  Language
;;; translations are performed on symbols. This is where we append "..." to
;;; commands which post dialogs, and remove "&" from command strings if not
;;; using native menus.

(defun menu-item-string
    (menu-description menu-item &optional capitalize? strip-hyphens? parameters)
  (with-localization-purpose 'menu-item
    (cond ((null menu-item)
	   nil)
	  ((menu-item-is-spacer-p menu-item)
	   nil)

	  ((or (gensym-string-p menu-item) ; allow both string types for now! (MHD 2/7/96)
	       (text-string-p menu-item))
	   ;; This used to downcase string when capitalize? was NIL, which
	   ;; downcased the menu of workspace names for get-workspace, which
	   ;; was an undesirable difference from 3.0.
	   (copy-text-string menu-item))

	  ((symbolp menu-item)
	   (let ((string (translated-string-for-symbol menu-item capitalize? strip-hyphens?)))
	     (compute-modified-menu-item-string menu-item string)))

	  ;; Partial commands.
	  ((partial-command-p menu-item)
	   (let* ((command (partial-command-command menu-item))
		  (string (translated-string-for-symbol
			    (ui-command-menu-name command)
			    capitalize? strip-hyphens?)))
	     ;; Complete commands may have a label computer, which can
	     ;; incorporate command argument values into the string.
	     (when (and (ui-command-labeler? command)
			(partial-command-is-complete-p menu-item))
	       (setq string (prog1 (funcall-ui (ui-command-labeler? command) menu-item string)
			      (reclaim-wide-string string))))
	     (compute-modified-menu-item-string menu-item string)))

	  ((ui-command-p menu-item)
	   (let ((string (translated-string-for-symbol
			   (ui-command-menu-name menu-item)
			   capitalize? strip-hyphens?)))
	     (compute-modified-menu-item-string (ui-command-name menu-item) string)))

	  ((consp menu-item)
	   (case (car menu-item)
	     (submenu
	      (let* ((submenu-name (second menu-item)) ; (submenu <name> &optional <label>)
		     (submenu-title (third menu-item))
		     (submenu-desc (find-menu-description submenu-name)))
		(cond ((menu-description-submenu-choices menu-description)
		       ;; We control the submenu.
		       (menu-item-string menu-description
					 (or submenu-title submenu-name)
					 capitalize? strip-hyphens? parameters))
		      (submenu-desc		    ; The submenu controls its label.
		       (menu-item-string submenu-desc
					 (or submenu-title
					     (menu-description-title submenu-desc))
					 capitalize? strip-hyphens? parameters))
		      (t
		       ;; Missing submenu.
		       (tformat-text-string "<<Missing submenu ~s>>" submenu-name)))))

	     ((choice			; (choice <label> <thing> . plist)
		command			; (command <label> <command>)
		dialog			; (dialog <label> <function>)
		user-menu-choice)		; (user-menu-choice <name>)
	      (menu-item-string menu-description (second menu-item)
				capitalize? strip-hyphens? parameters))

	     (t
	      (dwarn "Unknown menu item ~s" menu-item)
	      nil)))
	  (t
	   (dwarn "Unknown menu item ~s" menu-item)
	   nil))))

;; TODO: strip &'s from string if not native menu.




;; Really a command property, like, refreshes-image-plane-p.
;; Allow for other menu-item formats.
(defun menu-item-causes-movement-p (choice)
  (memq choice '(transfer move move-workspace)))


(def-global-property-name refreshes-image-plane-p)


;;; The function `event-handler-refreshes-image-plane-p' returns true if
;;; the given handler has been declared to refresh image planes.

(defun event-handler-refreshes-image-plane-p (event-handler?)
  (and event-handler? (symbolp event-handler?)		    ; Paranoia.
       (refreshes-image-plane-p event-handler?)))



(def-substitution-macro aborted-menu-choice? (choice)
  (eq choice +abort-menu-choice+))


;;; The function `transform-menu-item' transforms a menu item before
;;; placing it into a menu.  It is used, for example, to turn command names
;;; into partial commands.  If it returns nil, then the menu item is
;;; removed.  If it returns non-NIL, then the value is NEWLY consed,
;;; whether it is a partial-command instance or a slot value.

(defun transform-menu-item (menu-description menu-item mouse-pointer
					     &optional recyclable-lists?)
  (cond ((menu-item-is-spacer-p menu-item)
	 menu-item)

	((menu-item-explicit-submenu menu-description menu-item)
	 ;; If menu has own way of getting submenu choices, then do not look
	 ;; for a named menu.
	 (when (or (menu-description-submenu-choices menu-description)
		   (let* ((submenu-name (menu-item-explicit-submenu
					  menu-description menu-item))
			  (desc (find-menu-description submenu-name)))
		     #+development (unless desc
				     (dwarn "Submenu named ~s not found." submenu-name))
		     (and desc (menu-available-p desc mouse-pointer))))
	   (copy-for-slot-value menu-item)))

	((and (menu-item-command-name menu-item)
	      (eq (menu-description-menu-type menu-description) 'command-menu))
	 (let* ((command-name (menu-item-command-name menu-item))
		(command? (find-ui-command command-name t))
		(partial-command? (make-initial-partial-command command? mouse-pointer)))

	   (with-drawing-trace (menu)
	     (format t "  ~s: ~s~a~%"
		     (menu-description-name menu-description) command-name
		     (if partial-command? "" " failed its predicate")))

	   (cond ((null partial-command?)
		  nil)
		 ((symbolp menu-item)
		  partial-command?)
		 ((consp menu-item)
		  ;; Have to preserve the special label in (command <label> <command>).
		  (let ((new-menu-item (copy-list-using-slot-value-conses menu-item)))
		    (setf (third new-menu-item) partial-command?)
		    (when recyclable-lists?
		      (reclaim-slot-value-list menu-item))
		    new-menu-item)))))

	(t						    ; User-menu-choices pass thru here.
	 (with-drawing-trace (menu)
	   (format t "  ~s: ~s"
		   (menu-description-name menu-description) menu-item))
	 (copy-for-slot-value menu-item))))

;; The menu-item might be, say, (CHOICE "pump::temperature"
;; (CLASS-QUALIFIED-NAME PUMP TEMPERATURE)) which must be copied (as a slot
;; value).  Added needed copy. (MHD 4/2/94)




;;; The function `filter-choices-by-restrictions' returns a newly consed slot-value
;;; list of those choices which satified the given restrictions.  Both CHOICES and
;;; RESTRICTIONS are reclaimed.

(defun filter-choices-by-restrictions (choices restrictions permitted?)
  (let ((restricted-choices
	  (loop for choice in choices
		as choice-name = (menu-item-name choice)
		as allowed-p = (if (memq choice-name restrictions)
				   permitted? (not permitted?))
		if allowed-p
		  collect choice using slot-value-cons
		else
		  do (with-drawing-trace (menu)
		       (format t " ~a: restricted away~%" choice-name))
		     (cond ((partial-command-p choice)
			    (reclaim-partial-command choice))
			   ((consp choice)
			    (reclaim-slot-value choice))))))

    (reclaim-slot-value-list choices)
    (reclaim-filter-list-function restrictions)

    restricted-choices))

;; Note that it is crucial that we compare against the correct names here.
;; For example, EDIT-ATTRIBUTE is known by  restrictions simply as "EDIT".

;; Each choice is either a symbol naming a command, or, a partial-command instance.
;; Hmm.  Could they be a list (choice <label> <name>) ?

;; It also reclaims the choices which are filtered out -rdf, 11/22/94



;;; The function `map-over-menu-items' applies the given function to each
;;; menu-item in the menu.  Each menu-item is NEWLY consed, and must be
;;; reclaimed with reclaim-menu-item.

;;; We handle both statically defined menus and menus whose choice list is
;;; computed at run time.  In the later case, we take care of reclaiming the
;;; item list. We handle included menus here.  If the mapping function returns
;;; non-NIL, then we exit the loop and return that value.

(defun map-over-menu-items (menu-description function mouse-pointer parameters
					     &optional descend-into-submenus?)
  (let* ((choice-list (menu-description-choice-list-internal menu-description))
	 (choice-list-is-computed-p (and choice-list (atom choice-list)))
	 (choices (if choice-list-is-computed-p
		      (apply choice-list mouse-pointer parameters) ; Pass down any menu parameters.
		      choice-list))
	 (transformed-menu-item nil)
	 (return-value nil))

    (block SEARCH
      (loop for choice in choices doing
	(cond ((and (consp choice)			    ; (include <menu> . parms)
		    (or (eq (car choice) 'include)
			(and descend-into-submenus?	    ; (submenu <menu>)
			     (eq (car choice) 'submenu))))
	       (let* ((menu-type
			(first choice))
		      (included-menu?
			(find-menu-description (second choice)))
		      (parameters-for-submenu
			(case menu-type
			  (include (if (>=f (length choice) 3) ; If parms given, use them.
				       (third choice)
				       parameters))
			  (t
			   parameters)))
		      (available?
			(and included-menu?
			     (menu-available-p included-menu? mouse-pointer))))
		 #+development
		 (when (and included-menu? (not available?))
		   (with-drawing-trace (menus)
		     (format t "Menu ~s unavailable." included-menu?)))

		 (when available?
		   (setq return-value
			 (map-over-menu-items included-menu?
					      function mouse-pointer
					      parameters-for-submenu)))))

	      ((setq transformed-menu-item (transform-menu-item
					     menu-description choice mouse-pointer
					     choice-list-is-computed-p))
	       ;; The transformed item is always a NEW copy.
	       (setq return-value (funcall function menu-description
					   transformed-menu-item mouse-pointer))))
	(when return-value
	  (return-from search))))

    ;; A computed choice-list is a newly consed slot-value.  Actually, that is
    ;; not quite true.  All of its reclaimable structure is a slot-value, but
    ;; it is allowed to contain opaque non-reclaimable structures, such as
    ;; snapshot-of-block instances.
    (when choice-list-is-computed-p
      (reclaim-slot-value choices))

    return-value))





;;;; New menus, the movie.




(def-class (new-menu menu define-predicate)
  (menu-description-of-menu nil lookup-slot system)
  (menu-choice-transformer nil lookup-slot system)

  ;; A slot-value list of structures and sometimes blocks.
  (new-menu-other-things-to-reclaim nil lookup-slot system)

  ;; Function to call if menu is deleted without making any choice.
  ;; Whenever we make a choice from this menu, we clobber this slot to NIL
  ;; so that it will not be called when the menu is deleted.
  ;;  This must be a simple function of two arguments: (menu mouse-pointer).
  (menu-no-choice-function nil lookup-slot system))


(defun old-style-menu-p (menu)
  (and (framep menu)
       (eq (class menu) 'menu)))


(defun new-style-menu-p (menu)
  (and (framep menu)
       (of-class-p menu 'new-menu)))


(def-slot-value-reclaimer new-menu-other-things-to-reclaim (things)
  (reclaim-menu-items things))


(def-class-method cleanup (new-menu)
  (funcall-superior-method new-menu)
  (let ((no-choice-function? (menu-no-choice-function new-menu)))
    (when no-choice-function?
      ;; Give it exactly the same arguments as the choice function.
      ;; See execute-menu-choice
      (apply no-choice-function? new-menu nil nil
	     (menu-choice-arglist new-menu)))))


(defun notice-choice-made-on-menu (menu choice)
  (declare (ignore choice))
  (when (new-style-menu-p menu)
    (setf (menu-no-choice-function menu) nil)))




;;; The function `ensure-that-menu-item-will-be-reclaimed' pushes partial
;;; commands onto another list, since the old menu code merely calls
;;; reclaim-slot-value on the list of menu items, which won't reclaim partial
;;; commands.

(defun ensure-that-menu-item-will-be-reclaimed (menu menu-item)
  (cond ((framep menu-item)
	 (slot-value-push (make-snapshot-of-block menu-item)
			  (new-menu-other-things-to-reclaim menu)))
	((partial-command-p menu-item)
	 (slot-value-push menu-item
			  (new-menu-other-things-to-reclaim menu)))
	((and (menu-item-is-command-p menu-item)
	      (partial-command-p (menu-item-command menu-item)))
	 (slot-value-push (menu-item-command menu-item)
			  (new-menu-other-things-to-reclaim menu)))))

;; It'd be better to update the old menu code to call reclaim-menu-items.

	      


;;; The function `transform-menu-item-after-choice' transforms a menu item
;;; after choosing from a menu given by menu-description, and before supplying
;;; to the choice function.  It can return +abort-menu-choice+ to abort the
;;; entire menu choose.

(defun transform-menu-item-after-choice (menu-description? menu-item)
  (let ((value (menu-item-value menu-item))
	(transformer? nil))
    (cond ((or (null menu-description?)
	       (null (setq transformer? (menu-description-choice-transformer
					  menu-description?))))
	   value)
	  (t
	   (funcall transformer? value)))))



;;; The function `compute-menu-title' returns the menu title given
;;; a menu description and menu parameters.

(defun compute-menu-title (menu-description parameters)
  (let ((title-spec (menu-description-title menu-description)))
    (cond ((atom title-spec)
	   title-spec)
	  ((eq (first title-spec) ':funcall)
	   (apply (second title-spec) parameters)))))

;; Allow for translations!



;;; The function `make-menu-from-description' is the principal function for
;;; making a new style menu.  It makes a menu (table) instance from a menu
;;; description.  This needs to know the actual, final list of menu choices,
;;; and so needs the mouse-pointer, in order to be able to test all of the item
;;; predicates and restrictions.  If the resulting menu would have no choices,
;;; NIL is returned.

;;; The choice-function gets (menu menu-item menu-item-value . args).  ARGS
;;; should be a slot-value list. The spine of that list is reclaimed
;;; automatically by menus.

(defun make-menu-from-description
    (menu-description
      mouse-pointer
      &optional
      adjustment
      menu-class parameters options
      the-menu-items
      the-title
      item-submenu-function? ; NIL, or a function on (menu-desc menu-item arg-1 arg-2)
      arg-1 arg-2 arg-3)
  (macrolet ((menu-item-has-submenu-p (menu-item)
	       `(cond (item-submenu-function?
		       (funcall-simple-compiled-function
			 item-submenu-function? menu-description ,menu-item arg-1 arg-2 arg-3))
		      (t
		       (menu-item-submenu-p menu-description ,menu-item)))))
    (with-drawing-trace (menu)
      (format t "Building ~a for ~s:~%" menu-description mouse-pointer))

    (with-localization-domain 'menu   ; any specialization goes here

      (let ((menu-items (or the-menu-items
			    (compute-menu-items menu-description mouse-pointer parameters))))
	(when menu-items
	  (let* ((title? (or the-title
			     (getf options :title)
			     (compute-menu-title menu-description parameters)))
		 (single-lines? (menu-description-single-lines? menu-description))
		 (capitalize? (menu-description-capitalize? menu-description))
		 (strip-hyphens? (menu-description-strip-hyphens? menu-description))
		 (menu-class (or menu-class
				 (menu-description-menu-type menu-description)
				 'new-menu))
		 (markers-exist? (loop for menu-item in menu-items
				       thereis (menu-item-has-submenu-p menu-item)))
		 (number-of-columns
		   (loop for menu-item in menu-items
			 maximize (menu-item-ncolumns menu-item) using maxf))
		 (cascade-format
		   (get-or-make-format-frame
		     (if new-g2-classic-ui-p
			 (get-ui-parameter 'cascade-menu-item-format adjustment)
			 (choose-cascade-menu-item-format-per-menu-parameters))))
		 (default-format
		     (get-or-make-format-frame
		       (if new-g2-classic-ui-p
			   (get-ui-parameter 'menu-item-format adjustment)
			   (choose-menu-item-format-per-menu-parameters markers-exist?))))

		 (title-cells
		   (when title?
		     (slot-value-list
		       (make-table-spanning-row
			 (make-text-cell
			   (slot-value-list
			     (menu-item-string menu-description
					       title? capitalize? strip-hyphens?
					       parameters))
			   (choose-menu-heading-format-per-menu-parameters markers-exist?))
			 number-of-columns))))

		 (item-cells
		   (loop for menu-item in menu-items
			 as format = (if (menu-item-has-submenu-p menu-item)
					 cascade-format
					 default-format)
			 nconc (make-table-rows-for-menu-item menu-description menu-item
							      format number-of-columns parameters)))

		 (menu
		   (make-or-reformat-table (nconc title-cells item-cells)
					   (if new-g2-classic-ui-p
					       (if (memq
						     (menu-description-name menu-description)
						     '(full-color-menu color-menu))
						   'menu-table-format
						   'menu-table-format-for-new-g2-classic-ui)
					       'menu-table-format)
					   nil menu-class single-lines?)))

	    ;; If the menu-item is not reclaimable by virtue of being part of the
	    ;; text-cell-plist, which means anything which reclaim-slot-value
	    ;; will miss, then ensure that it happens some other way.
	    (loop for menu-item in menu-items doing
	      (ensure-that-menu-item-will-be-reclaimed menu menu-item))

	    (setf (menu-description-of-menu menu) menu-description
		  (menu-choice-function menu) (menu-description-choice-function menu-description)
		  (menu-no-choice-function menu) (menu-description-no-choice-function menu-description)
		  (menu-choice-arglist menu) nil
		  (menu-choice-transformer menu) (menu-description-choice-transformer menu-description)
		  ;; Each menu remembers the mouse-pointer which caused it to be posted.
		  (menu-mouse-pointer menu) (reference-mouse-pointer mouse-pointer))

	    (unless the-menu-items
	      (reclaim-slot-value menu-items))
	    
	    menu))))))

(defun-void change-adjustment-of-menu (menu adjustment)
  (declare (ignore adjustment))
  (update-images-of-block menu t t)
  (loop for row in (table-rows menu) do
    (loop for cell in row
	  for format-name = (when (and (consp cell) (framep (car cell)))
			       (name-or-names-for-frame (car cell)))
	  for new-format-name
	      = (case format-name
		  (left-aligned-cascade-menu-item-format-new-large
		   'left-arrow-left-aligned-cascade-menu-item-format-new-large)
		  (left-aligned-cascade-menu-item-format-new-small
		   'left-arrow-left-aligned-cascade-menu-item-format-new-small)
		  (left-arrow-left-aligned-cascade-menu-item-format-new-large
		   'left-aligned-cascade-menu-item-format-new-large)
		  (left-arrow-left-aligned-cascade-menu-item-format-new-small
		   'left-aligned-cascade-menu-item-format-new-small)
		  (left-arrow-left-aligned-cascade-menu-item-format
		   'left-aligned-cascade-menu-item-format)
		  (left-aligned-cascade-menu-item-format
		   ;;'left-arrow-left-aligned-cascade-menu-item-format
		   'left-aligned-cascade-menu-item-format)
		  
		  (left-aligned-menu-item-format-new-large
		   'left-arrow-left-aligned-menu-item-format-new-large)
		  (left-aligned-menu-item-format-new-small
		   'left-arrow-left-aligned-menu-item-format-new-small)
		  (left-arrow-left-aligned-menu-item-format-new-large
		   'left-aligned-menu-item-format-new-large)
		  (left-arrow-left-aligned-menu-item-format-new-small
		   'left-aligned-menu-item-format-new-small)
		  (left-arrow-left-aligned-menu-item-format
		   'left-aligned-menu-item-format)
		  (left-aligned-menu-item-format
		   ;;'left-arrow-left-aligned-menu-item-format
		   'left-aligned-menu-item-format))
	  for new-format = (when new-format-name
			     (get-or-make-format-frame new-format-name))
	  when new-format
	    do (setf (car cell) new-format)))
  (reformat-table-in-place
   menu t
   (- (right-edge-of-block menu) (left-edge-of-block menu)))
  (update-images-of-block menu nil t)
  menu)



;;; The function `make-table-rows-for-menu-item' returns a newly consed
;;; slot-value-list of table rows for a menu-item.  Only spacer items return
;;; more than one row.

(defun make-table-rows-for-menu-item
    (menu-description menu-item format number-of-columns &optional parameters)
  (cond ((menu-item-is-row-p menu-item)
	 ;; Notice that we do not recurse here, as you might expect.
	 (slot-value-list
	   (loop for item in (cdr menu-item)
		 as text-cell? = (menu-item-make-text-cell
				   menu-description item format parameters)
		 if (or text-cell? (null item))		    ; Let thru explicits NILs
		   collect text-cell?
		     using slot-value-cons)))
	(t
	 (let ((text-cell? (menu-item-make-text-cell
			     menu-description menu-item format parameters)))
	   (if text-cell?
	       (slot-value-list (make-table-spanning-row text-cell? number-of-columns))
	       (make-table-spacer-cells 3 number-of-columns))))))



;;; The function `menu-item-make-text-cell' returns a text-cell for a menu
;;; item.  Usually, this is derived from prettifying the menu-item-string, but
;;; CHOICE menu items also include a text-cell-plist.  The syntax is: (choice
;;; <label> <value> . plist).  Optionally, a user-supplied function can take
;;; care of the entire job.  This is used by the color menus, for example, to
;;; get different background colors for each text cell.

;;; The text-cell is newly consed, and shares no slot-value structure with the
;;; menu-item.  It may share structures (such as partial-command instances)
;;; which are not reclaimed by reclaim-slot-value (nor copied by
;;; copy-for-slot-value).

(defun menu-item-make-text-cell (menu-description menu-item format parameters)
  (let* ((capitalize? (menu-description-capitalize? menu-description))
	 (strip-hyphens? (menu-description-strip-hyphens? menu-description))
	 (function? (menu-description-make-text-cell menu-description))
	 (string? nil))
    (cond ((null menu-item)
	   nil)
	  (function?
	   (apply function? menu-description menu-item format parameters))
	  ((setq string? (menu-item-string
			   menu-description
			   menu-item capitalize? strip-hyphens? parameters))
	   ;; string? is newly consed.
	   (let ((text-cell (make-text-cell (slot-value-list string?) format))
		 (plist (menu-item-plist menu-item)))

	     (change-text-cell-property
	       text-cell 'choice
	       (copy-menu-item menu-item))		    ; added needed copy. (MHD 3/30/94))
	     (loop for (property value) in plist by 'cddr doing
	       (change-text-cell-property
		 text-cell property
		 (copy-for-slot-value value)))		    ; added needed copy. (MHD 3/30/94)
	     text-cell)))))




(defun finalize-menu (menu &optional thing)
  (setf (x-in-window-prior-to-posting-menu menu) (x-of-mouse-pointer
						   (menu-mouse-pointer menu))
	(y-in-window-prior-to-posting-menu menu) (y-of-mouse-pointer
						   (menu-mouse-pointer menu)))
  (when (is-block-p thing)
    (slot-value-push menu (menus-for-this thing))
    (setf (what-this-is-a-menu-for? menu) thing))
  menu)




;;; The function `make-menu-named' creates a menu given its name or
;;; description.  It does filtering of menu-items using command testers, which
;;; may depend on the mouse-pointer.  If there if no menu of the given name,
;;; then nothing happens.  If there is a menu of that name, but it would have
;;; no choices, then nothing is posted, but we will call the no-choice-function
;;; for the menu, if any.  The multifarious optional arguments are passed
;;; directly onto `make-menu-from-description', and are documented there.

;;; The item-submenu-function?, if non-NIL, should be a function on (menu-desc
;;; menu-item arg-1 arg-2 arg-3), which returns the submenu to post when the
;;; given item is selected.

(defun-allowing-keywords make-menu-named
    (menu-name-or-description
      &key
      mouse-pointer
      adjustment			; nil, left, or right.  for walking menus
      class				; Of menu
      parameters			; Args to the menu builder
      options				; Options to the menu builder
      items				; Overriding list of menu items
      title				; A string
      item-submenu-function? arg-1 arg-2 arg-3)
  (let ((mouse-pointer (or mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
	(desc? (if (symbolp menu-name-or-description)
		   (find-menu-description menu-name-or-description)
		   menu-name-or-description)))
    (when desc?
      (make-menu-from-description
	desc? mouse-pointer adjustment class
	parameters options items title
	item-submenu-function? arg-1 arg-2 arg-3))))




;;; The function `post-menu' posts a menu table, installing the given choice
;;; function.  The choice function gets the arguments (menu menu-item choice
;;; . arguments).  Arguments must be a slot-value-list, whose spine is
;;; reclaimed automatically.

(defun-allowing-keywords post-menu
    (menu &key
	  choice-function
	  choice-function-arguments
	  no-choice-function
	  what-this-is-a-menu-for
	  x-in-window y-in-window)
  (when choice-function
    (setf (menu-choice-function menu) choice-function)
    (setf (menu-choice-arglist menu) choice-function-arguments))

  (when no-choice-function
    (setf (menu-no-choice-function menu) no-choice-function))
  
  (finalize-menu menu what-this-is-a-menu-for)

  (multiple-value-bind (x-in-window y-in-window)
      ;; Maybe this wants menu-mouse-pointer?
      (let ((mouse-pointer
	      (mouse-pointer-of-latest-event current-workstation)))
	(values (or x-in-window (x-of-mouse-pointer mouse-pointer))
		(or y-in-window (y-of-mouse-pointer mouse-pointer))))

    (expose-menu menu x-in-window y-in-window)))




;;; The function `post-menu-named' posts (actually exposes) the named menu,
;;; at the given x, y position, and optionally on behalf of the given object.
;;; The menu's choice-function is taken from the menu description.  If a menu
;;; is indeed posted, then the menu workspace is returned.

(defun-allowing-keywords post-menu-named
    (menu-name &key
	       mouse-pointer
	       x-in-window
	       y-in-window
	       what-this-is-a-menu-for
	       title
	       choice-function
	       choice-function-arguments)
  (let ((menu? (make-menu-named menu-name :mouse-pointer mouse-pointer
				:title title)))
    (when menu?
      (post-menu menu?
		 :choice-function choice-function
		 :choice-function-arguments choice-function-arguments
		 :what-this-is-a-menu-for what-this-is-a-menu-for
		 :x-in-window x-in-window
		 :y-in-window y-in-window))))

;; The choice-function gets (menu choice menu-item . arglist).  See
;; execute-menu-choice.



;;;; Command menu



;;; The class `command-menu' defines a menu which calls a choice-function when
;;; a choice is made.  The choice function gets three arguments, (menu
;;; menu-item choice).  If the menu is dismissed without making any choice,
;;; then the no-choice-function (defined in the new-menu class) is called.

(def-class (command-menu new-menu define-predicate)
  (menu-choice-function command-menu-choice-function vector-slot system))



(defun make-command-menu
    (menu-name mouse-pointer &optional parameters options menu-items title)
  (let ((menu? (make-menu-named menu-name
				:mouse-pointer mouse-pointer
				:class 'command-menu
				:parameters parameters
				:options options
				:items menu-items
				:title title)))
    (when menu?
      (setf (menu-choice-function menu?) 'command-menu-choice-function)
      menu?)))


;;; The function `post-command-menu' posts the named menu of commands, at x,y,
;;; using the given mouse-pointer to initially fill in magic command arguments.
;;; If a menu is indeed posted, then we return the menu-workspace.

(defun post-command-menu (menu-name-or-description
			   &optional mouse-pointer x y thing parameters options title)
  (unless mouse-pointer
    (setq mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
  (unless x
    (setq x (x-of-mouse-pointer mouse-pointer)))
  (unless y
    (setq y (y-of-mouse-pointer mouse-pointer)))

  (let* ((desc? (if (symbolp menu-name-or-description)
		    (find-menu-description menu-name-or-description)
		    menu-name-or-description)))
    (when desc?
      (let ((menu? (make-command-menu desc? mouse-pointer parameters options nil title)))
	(when menu?
	  (finalize-menu menu? thing)
	  (expose-menu menu? x y))))))



;;; The function `command-menu-choice-function' executes a choice off of a
;;; command menu.  Each choice in a command menu is either a symbol, a command,
;;; or a partial-command.  Submenus are taken care of by execute-menu-choice.

(defun command-menu-choice-function (menu menu-item choice)
  (cond ((null choice))

	((symbolp choice)
	 (let ((command? (find-ui-command choice))
	       (user-menu-choice? (and (consp menu-item)
				       (eq (car menu-item) 'user-menu-choice))))
	   ;; If it's a floor wax and a dessert topping we don't want the floor
	   ;; wax. -rdf, 1/17/95
	   (cond (user-menu-choice?
		  (execute-user-menu-choice-if-possible
		    choice (what-this-is-a-menu-for? menu)))
		 (command?
		  (start-ui-command command? (menu-mouse-pointer menu))))))
	
	((ui-command-p choice)
	 (start-ui-command choice (menu-mouse-pointer menu)))
	
	((partial-command-p choice)
	 ;; The menu still owns this partial-command, so we must make a copy
	 ;; for the pursuer.
	 (cond ((partial-command-valid-p choice)
		(pursue-partial-command (copy-partial-command choice)
					(menu-mouse-pointer menu)
					'menu))
	       (t
		(dwarn "Partial command ~s aborted because some argument is invalid."
		       choice))))
	(t
	 (dwarn "Unknown command menu choice: ~s." choice))))

;; This function should be combined with run-event-handler, except that here we
;; don't want to check restrictions -- that was done when the menu was popped
;; up.


;;;; Parameter menu



;;; A menu of values for some argument of a command.

(def-class (parameter-menu new-menu define-predicate)
  (menu-choice-function parameter-menu-choice-function vector-slot system)
  (parameter-menu-partial-command nil lookup-slot system)   ; Owned by this menu.
  (parameter-menu-which-argument nil lookup-slot system))   ; An integer.

(def-slot-value-reclaimer parameter-menu-partial-command (partial-command?)
  (when partial-command?
    (reclaim-partial-command partial-command?)))



;;; The function `make-parameter-menu' creates a parameter menu to retrieve a
;;; value for the given argument of the partial command, then pursues the
;;; command further.  The partial command instance is OWNED by this routine.

(defun make-parameter-menu (menu-name partial-command which-argument mouse-pointer
				      &optional adjustment parameters options
				      menu-items title item-submenu-function? arg-1 arg-2 arg-3)
  (let ((menu? (make-menu-named menu-name
				:mouse-pointer mouse-pointer
				:adjustment adjustment
				:class 'parameter-menu
				:parameters parameters
				:options options
				:items menu-items
				:title title
				:item-submenu-function? item-submenu-function?
				:arg-1 arg-1
				:arg-2 arg-2
				:arg-3 arg-3)))
    (when menu?
      (setf (menu-choice-function menu?) 'parameter-menu-choice-function
	    (parameter-menu-partial-command menu?) partial-command
	    (parameter-menu-which-argument menu?) which-argument)
      menu?)))




;;; The function `parameter-menu-choice-function' is the menu choice function
;;; for parameter menus.  If the parameter menu item request a dialog, we
;;; invoke that here with funcall (eg, for `choose-more-colors').  Otherwise,
;;; we bind that argument in the partial command and pursue if further.

(defun parameter-menu-choice-function (menu menu-item value)
  (parameter-menu-choice-function-1
    ;; In general, a choice from a menu should not side-effect the menu.
    ;; So, we have to copy out the partial command instance.
    (copy-partial-command (parameter-menu-partial-command menu))
    (menu-item-dialog menu-item)
    (parameter-menu-which-argument menu)
    value
    (menu-mouse-pointer menu)))


;;; The function `parameter-menu-choice-function-1' is a helper function used by
;;; both classic G2 parameter menus and NMS parameter menus.

(defun parameter-menu-choice-function-1
    (partial-command dialog? which-argument value mouse-pointer)
  (cond (dialog?
	 (funcall dialog? partial-command which-argument value mouse-pointer)
	 (reclaim-partial-command partial-command))
	(t
	 (bind-partial-command-argument partial-command which-argument value)
	 (pursue-partial-command partial-command mouse-pointer 'menu))))



;;; The function `create-submenu' returns the menu which should be posted as
;;; the submenu for the given parent menu and menu-item.  This is the only
;;; interface function which the walking-menus context needs in order to do its
;;; thing.

;; I think that we do not need the mouse-pointer here, but check. -fmw, 1/15/02
(defun create-submenu (parent-menu menu-item mouse-pointer &optional adjustment)
  (unless (old-style-menu-p parent-menu)
    (let* ((menu-description (menu-description-of-menu parent-menu))
	   (value (menu-item-value menu-item))
	   (explicit-submenu?
	     (menu-item-explicit-submenu menu-description menu-item))
	   (implicit-submenu?
	     (menu-item-submenu-p menu-description menu-item))
	   ;; *** implicit-submenu? is NIL for parameter-menus at the moment!!
	   (submenu-choices
	     ;; Yuck. Overrides menu item list.
	     (menu-description-submenu-choices menu-description))
	   (original-mouse-pointer
	     (menu-mouse-pointer parent-menu))
	   (submenu-choice-list nil)
	   
	   (submenu-name
	     ;; Not exactly a "name".
	     (if submenu-choices menu-description explicit-submenu?))
	   
	   (menu?
	     (frame-class-case parent-menu
	       (command-menu
		 (setq submenu-choice-list
		      (when submenu-choices
				(funcall submenu-choices menu-description explicit-submenu?
					 original-mouse-pointer)))
		 (cond (explicit-submenu?
			;; More, unrelated commands.
			(make-command-menu
			  submenu-name original-mouse-pointer
			  nil submenu-choice-list))
		       (implicit-submenu?
			;; First argument of a command. Fills in mouse-pointer
			;; and immediate args.

			;; Shouldn't this be using the original mouse pointer? -fmw, 1/15/02
			(let ((pc (make-initial-partial-command value mouse-pointer)))
			  (make-parameter-submenu-for-partial-command pc mouse-pointer adjustment)))))

	       (parameter-menu
		 (cond (explicit-submenu?
			;; Work on the same argument.
			(setq submenu-choice-list
			      (when submenu-choices
				(funcall submenu-choices menu-description explicit-submenu?
					 original-mouse-pointer)))
			(make-parameter-menu
			  submenu-name
			  (copy-partial-command (parameter-menu-partial-command parent-menu))
			  (parameter-menu-which-argument parent-menu)
			  original-mouse-pointer
			  adjustment nil nil
			  submenu-choice-list))
		       
		       (t
			;; Look ahead to the next argument, and see if it wants a submenu.
			(let* ((this-partial-command (parameter-menu-partial-command parent-menu))
			       (this-argument (parameter-menu-which-argument parent-menu))
			       (this-value (transform-menu-item-after-choice menu-description menu-item))
			       (next-partial-command?
				 (partial-command-requires-submenu-after-this-choice
				   this-partial-command this-argument this-value)))
			  (when next-partial-command?
			    (make-parameter-submenu-for-partial-command
			      next-partial-command?
			      original-mouse-pointer
			      adjustment)))))))))
      (when submenu-choice-list
	(reclaim-slot-value-list submenu-choice-list))
      (when menu?
	(finalize-menu menu? (what-this-is-a-menu-for? parent-menu))
	menu?))))


;;; The function `expose-menu' posts a menu and returns the menu workspace.
;;; Used by walking-menus.  Normally the top-center of the menu is positioned
;;; on the given x,y.  However, if left-adjusted? if non-NIL, then the top-left
;;; is placed there

(defun expose-menu
    (menu x-in-window? y-in-window &optional default-x-scale? default-y-scale?
	  x-for-left-adjusting? x-for-right-adjusting? walking-submenu-p)
  (let ((window (window-for-workstation current-workstation)))
    (cond ((and (native-pop-up-menus-p window)
		(menu-works-natively-p menu))

	   (with-icp-window (window)
	     (expose-menu-remotely
	       window
	       menu
	       ;; walking-menus-post-submenu calls expose-menu with NIL for x !!!!
	       (or x-in-window? x-for-left-adjusting? x-for-right-adjusting? 100)  ; hack
	       y-in-window)))
	  (t
	   (expose-menu-locally
	     menu x-in-window? y-in-window default-x-scale? default-y-scale?
	     x-for-left-adjusting? x-for-right-adjusting? walking-submenu-p)))))


;;; The function `menu-works-natively-p' returns T for menus which currently
;;; work natively.

(defun menu-works-natively-p (menu)
  (let ((desc (menu-description-of-menu menu)))
    (not (memq (menu-description-name desc) '(EDITOR-TEXT-MARKING-MENU)))))


;;; The function `make-menu-workspace' must be used to create all menu
;;; workspaces.

(defun make-menu-workspace (menu)
  (let ((workspace (make-workspace 'menu-workspace nil menu 0)))
    (make-workspace-unselectable workspace)
    workspace))


;; "Locally" really means "classically".
(defun expose-menu-locally
    (menu x-in-window? y-in-window default-x-scale? default-y-scale?
	  x-for-left-adjusting? x-for-right-adjusting? walking-submenu-p)
  (let ((menu-workspace (make-menu-workspace menu)))
    (when walking-submenu-p
      (setf (menu-workspace-for-is-for-walking-submenu-p menu-workspace) t))
    ;; New style: move title text to menu workspace
    (cond
      (new-g2-classic-ui-p
       (change-slot-value
	 menu-workspace 'workspace-background-color?
	 (get-ui-parameter 'system-workspace-background-color))
       (let* ((first-row (first (table-rows menu)))
	      (title-text?
		(loop for cell? in first-row
		      when (and cell? (not (cell-is-block-p cell?)))
			do (return (copy-text (text? cell?))))))
	 (cond
	   ((and title-text?
		 ;; can't handle case of degenerate menu with just one row:
		 (cdr (table-rows menu))
		 ;; can't handle blocks in cells (rare):
		 (not (loop for cell? in first-row
			    thereis (and cell? (cell-is-block-p cell?)))))
	    (slot-value-pop (table-rows menu))
	    (reclaim-slot-value first-row)
	    (reformat-table-in-place
	      menu t
	      (+w (get-total-title-bar-text-width title-text?)
		  ;; Disclosure: hand-tweaked to account for:   (MHD 10/5/99)
		  ;;  + extra padding around title bar
		  ;;  + extra padding around title bar text
		  ;;  + extra padding around close box
		  ;;  + width of close box
		  ;;  - menu (i.e., table) border width
		  33))
	    (change-slot-value
	      menu-workspace 'title-bar-caption-text
	      title-text?)
	    (shrink-wrap-workspace menu-workspace))
	   (title-text?
	    (reclaim-text title-text?))))
       (post-menu-workspace
	 menu-workspace
	 (if (or x-for-left-adjusting? x-for-right-adjusting?)
	     x-in-window?
	     (+r x-in-window? (get-ui-parameter 'close-box-x-offset)))
	 (if (or x-for-left-adjusting? x-for-right-adjusting?)
	     y-in-window
	     (+r y-in-window (get-ui-parameter 'close-box-y-offset)))
	 nil
	 default-x-scale? default-y-scale?
	 x-for-left-adjusting?  ; presumably for walking menus
	 x-for-right-adjusting? ; right adjust normally in the new UI 
	 walking-submenu-p))		
      (t
       (post-menu-workspace menu-workspace x-in-window? y-in-window
			    nil
			    default-x-scale? default-y-scale?
			    x-for-left-adjusting?
			    x-for-right-adjusting?
			    walking-submenu-p)))))





;;;; Workstation Context Descriptions




;; Enough info to default all of the arguments to `enter-context-in-current-workstation'

;; The specific-structures and type-of-workstation-context should be replaced by
;; simply subclassing workstation-context for ech new context.  It would have one slot
;; which points to its description, which contains the more static info like the keymap.


(defvar-of-special-global list-of-all-workstation-contexts ())
(def-global-property-name context-description-named)

;; Should define the constructor for us. Keyword-based.
(define-structure context-description ()
  (:constructor make-context-description-1)
  (:conc-name t)
  name
  parent				; Context to which we default unhandled events.
  modal					; this-is-a-modal-context?
  keymaps)				; A list of NAMES of keymaps to search, in order.


(defun make-context-description (name parent modal keymaps)
  (let* ((old-context (find-workstation-context name))
	 (context (make-context-description-1)))
    old-context
    (setf (context-description-name context) name
	  (context-description-parent context) parent
	  (context-description-modal context) modal
	  (context-description-keymaps context) keymaps)
    (push-update context list-of-all-workstation-contexts :key context-description-name)
    (setf (context-description-named name) context)))



;;; The function `add-keymap-to-workstation-context' adds the keymap name
;;; to the end of the list of keymaps searched by the context, unless it
;;; is already there.  This is called only at load-time, so it conses in the
;;; permanent area.

(defun add-keymap-to-workstation-context (keymap-name context-name)
  (let ((context? (find-workstation-context context-name t)))
    (when context?
      (pushnew-onto-end keymap-name (context-description-keymaps context?)))
    context?))


(defun delete-keymap-from-workstation-context (keymap-name context-name)
  (let ((context? (find-workstation-context context-name t)))
    (when context?
      (setf (context-description-keymaps context?)
	    (delete keymap-name (context-description-keymaps context?))))
    context?))


#+development
(defun undefine-workstation-context (&optional name?)
  (cond (name?
	 (remprop name? 'context-description-named))
	 (t
	  (loop for context in list-of-all-workstation-contexts doing
	    (undefine-workstation-context (context-description-name context)))
	  (setq list-of-all-workstation-contexts nil))))


(defun find-workstation-context (context-or-name &optional warn-p)
  (or
    (unless (symbolp context-or-name)
      context-or-name)
    (context-description-named context-or-name)
    (when warn-p
      (dwarn "Unknown workstation context: ~s" context-or-name))))


(defun context-description-parent-context (context)
  (find-workstation-context (context-description-parent context)))
    


(def-concept complex-event)

;;; The function `parse-complex-event-specifier' returns a list of parsed events
;;; given a complex event.  A complex event, for now, is either a key-code, a
;;; list of (key-code spot-class . options), or the list (OR complex-event*).  A
;;; parsed complex event is always a list (key-pattern spot-class . options),
;;; where a spot class of T is the default.

(defun-for-macro parse-complex-event-specifier (specifier)
  (cond ((atom specifier)
	 (list (list (parse-key-pattern specifier)
		     t)))
	((eq (car specifier) 'or)
	 (loop for disjunct in (cdr specifier)
	       append (parse-complex-event-specifier disjunct)))
	(t
	 ;; Warn about unknown spot classes?
	 (list (list* (parse-key-pattern (first specifier))
		      (second specifier)
		      (cddr specifier))))))



;;; The function `lookup-key-in-context' returns an event-interpretation for
;;; keycode over spot in the given context.  The context's keymaps are searched in
;;; order, and the first handler found wins.
 
(defun lookup-key-in-context (context keycode spot)
  (loop for keymap-name in (context-description-keymaps context)
	as keymap? = (find-keymap-named keymap-name)
	as handler? = (and keymap?
			   (keymap-enabled-p keymap?)
			   (lookup-key-in-keymap keymap? keycode spot))
	do (with-drawing-trace (keymap)
	     (format t " ~a Keymap: ~30a ~a -> ~s"
		     (context-description-name context)
		     (if keymap? (keymap-name keymap?) "none")
		     (key-name keycode)
		     handler?))
	thereis handler?))


;;; The function `lookup-key-in-context-stack' returns a newly consed
;;; event-interpretation for keycode over spot in the current context or any
;;; above it in the stack.

(defun lookup-key-in-context-stack (workstation key-code spot)
  (with-backtrace-for-internal-error 'find-event-interpretation
    (let* ((context-name (type-of-workstation-context
			   (first (workstation-context-stack workstation))))
	   (new-style-context? (find-workstation-context context-name))
	   (handler? nil))

      (cond (new-style-context?
	     (loop for context = new-style-context? then (context-description-parent-context context)
		   while context
		   for handler = (lookup-key-in-context context key-code spot)
		   if handler
		     return (values handler (context-description-name context))))

	    ((setq handler?
		   (lookup-key-in-context
		     (find-workstation-context 'top-level)
		     key-code spot))
	     (values handler? 'top-level))))))

	  

;;; The function `lookup-command-in-context' returns the key-pattern, if any,
;;; to which a given command is bound in the given context.

(defun lookup-command-in-context (context command-name)
  (loop for keymap-name in (context-description-keymaps context)
	as keymap? = (keymap-named keymap-name)
	thereis (and keymap? (keymap-enabled-p keymap?)
		     (lookup-command-in-keymap keymap? command-name))))

	

;;; The function `lookup-command-in-context-stack' returns the key code to which
;;; the given command is bound, if any.

(defun lookup-command-in-context-stack (command-name)
  (let* ((context-name (type-of-workstation-context
			 (first (workstation-context-stack
				  current-workstation))))
	 (context? (find-workstation-context context-name)))
    (when context?
      (loop for context = context? then (context-description-parent-context context)
	    while context
	    as key-pattern? = (lookup-command-in-context context command-name)
	    if key-pattern? return it))))

;; Used only for the development command show-all-ui-commands




;;; The function `find-event-interpretation' returns an event interpretation
;;; for the given workstation event in the current workstation context.  The
;;; interpretation is newly consed, and should be reclaimed by the caller.
;;; ajs (4/17/96)  Added with-backtrace-for-internal-error.

(defun find-event-interpretation (event workstation)
  (let ((mouse-pointer (mouse-pointer-of-latest-event workstation)))
    (unless (eql (key-code-of-mouse-pointer mouse-pointer) (workstation-event-code event))
      (dwarn "Keycodes do not match in ~s and ~s" event mouse-pointer))
    (lookup-key-in-context-stack workstation
				 (key-code-of-mouse-pointer mouse-pointer)
				 (stack-of-spots mouse-pointer))))

;; This really wants to take a mouse-pointer, not an event.


;;; The function `define-key' defines a new event binding within a workstation
;;; context, using the first keymap in the context.  To remove a binding,
;;; supply a function of NIL.

(defun define-key (context-name parsed-key-pattern object-class handler)
  (let* ((context? (find-workstation-context context-name t))
	 (keymap? (keymap-named (first (context-description-keymaps context?)))))
    (when keymap?
      (bind-key-in-keymap keymap? parsed-key-pattern object-class handler nil))))

;; This conses!  Meant to be used only at load-time!



#+development
(defun undefine-key (key-pattern &key (class t) (context 'top-level))
  (let ((key-pattern? (parse-key-pattern key-pattern)))
    (when key-pattern?
      (define-key context key-pattern? class nil))))


					
;;; The defun-for-macro `parse-key-bindings' returns (values new-keymap
;;; new-handlers).  Makes mini-handlers for commands inlined in the keymap.
;;; keymap-name is simply used as a component in the name of the event handler
;;; functions.

(defun-for-macro parse-key-bindings (keymap-name key-bindings)
  (let ((new-bindings ())
	(mini-handlers ()))
    
    ;; If the "body" is the not the name of a handler function,
    ;; then it should be (lambda-list . handler-body)

    (loop for (complex-event . handler-body) in key-bindings
	  as handler-name = (car handler-body)
	  doing
      (loop for (key-pattern class . options) in (parse-complex-event-specifier complex-event)
	    as key-pattern-name = (lisp-princ-to-string key-pattern)
	    doing
	(when (or (cdr handler-body)
		  (not (symbolp handler-name)))

	  (setq handler-name
		(if (neq class t)
		    (build-ab-symbol "handle" key-pattern "on" class "in" keymap-name)
		    (build-ab-symbol "handle" key-pattern "in" keymap-name)))
	  
	  (push `(define-event-handler ,handler-name ,(car handler-body)
		   ,@(cdr handler-body)) mini-handlers))
	(push (list* key-pattern class handler-name options) new-bindings)))
    (values (nreverse new-bindings) (nreverse mini-handlers))))



;;; The macro `define-workstation-context' defines a new workstation context,
;;; which is the same as a mode in the user interface.  The mode contains
;;; hidden state, and can install a totally new event handler.

;;; The enter context function, if defined, takes each of the state variables
;;; as a keyword argument, and returns the state.

(defmacro define-workstation-context
    (name includes &key
	  (parent 'top-level) ; Parent context. Where unhandled events are sent.
	  structure-name      ; Name of structure. Defaults to <name>-STATE
	  constructor	      ; Constructor option, a la def-structure.
	  conc-name	      ; Name to prepend to state var names to get the slot names.
	  state-variables     ; Context state variables.
	  define-enter-context-function	; Make one for me.
	  dont-define-structure		; A KLudge.
	  (selection-style 'top-level-is-selection-style)
	  modal		      ; Whether context grabs all events.
	  keymaps	      ; List of names of keymaps to search, in order.
	  initial-keymap      ; Body of a define-keymap form.
	  keymap)             ; Synonym for initial-keymap
  (when (search "-STATE" (symbol-name name))
    (warn
      "You proabably didn't want to include \"-STATE\" in the name ~S"
      name))
  (let* ((structure-name (or structure-name
			     (build-ab-symbol name "state")))
	 (constructor-name (or (first constructor)
			       (build-ab-symbol "make" structure-name)))
	 (state-variable-names (mapcar #'car-or-atom state-variables))
	 (enter-name (build-ab-symbol "enter" name "context"))
	 (includes (or includes '(workstation-context-frame)))
	 (conc-name (if (eq conc-name t) structure-name conc-name))
	 (initial-keymap (or initial-keymap keymap))
	 (definer (if state-variable-names 'defun-allowing-keywords 'defun))
	 (lambda-list (if state-variable-names `(&key ,@state-variable-names) nil)))

    (optimized-progn
      (unless dont-define-structure
	`(define-structure ,structure-name (,@includes)
	   (:managed t)
	   (:conc-name ,conc-name)
	   ,@(when constructor `((:constructor ,@constructor)))
	   ,@state-variables))

      `(def-selection-style-of-workstaton-context
	   ,structure-name ,selection-style)

      ;; A simple enter-context function.
      (when define-enter-context-function
	`(,definer ,enter-name ,lambda-list
	   (let ((state (,constructor-name)))
	     (setf ,@(loop for structure-slot-name in state-variable-names
			   for accessor = (if conc-name
					      (build-ab-symbol conc-name structure-slot-name)
					      structure-slot-name)
			   collect `(,accessor state)
			   collect structure-slot-name))
	     (enter-context-in-current-workstation ',name state ',modal)
	     state)))

      `(make-context-description ',name ',parent ',modal ',keymaps)

      (when initial-keymap
	`(define-keymap ,name (:context ,name) ,@initial-keymap))

      #+development `(find-workstation-context ',name))))




#+development
(defun show-keymaps (&optional (context-or-name 'top-level))
  (let ((context (find-workstation-context context-or-name)))
    (loop for keymap in (context-description-keymaps context) doing
      (show-keymap keymap))
    context))




;;;; Magic argument definitions



(define-magic-argument event (mouse-pointer)
  (declare (ignore mouse-pointer))
  (when (boundp 'current-workstation-event)
    current-workstation-event))

;; Ack! Ignores the mouse-pointer!!  Pretty racey!!


(define-magic-argument event-plist (mouse-pointer)
  (declare (ignore mouse-pointer))
  (when (boundp 'current-workstation-event)
    (workstation-event-detail current-workstation-event)))

(define-magic-argument key-code (mouse-pointer)
  (key-code-of-mouse-pointer mouse-pointer))


;; In milliseconds.

(define-magic-argument timestamp (mouse-pointer)
  (fixnum-time-of-mouse-pointer mouse-pointer))


(define-magic-argument mouse-pointer (mouse-pointer)
  mouse-pointer)

(define-magic-argument mouse-down-pointer (mouse-pointer)
  (declare (ignore mouse-pointer))
  (mouse-pointer-of-last-down current-workstation))


(define-magic-argument workstation (mouse-pointer)
  (declare (ignore mouse-pointer))
  current-workstation)

(define-magic-argument window (mouse-pointer)
  (declare (ignore mouse-pointer))
  (window-for-workstation current-workstation))

(define-magic-argument g2-window (mouse-pointer)
  (declare (ignore mouse-pointer))
  (g2-window-for-this-workstation? current-workstation))

(define-magic-argument workstation-context (mouse-pointer)
  (first (workstation-context-stack (workstation-for-mouse-pointer mouse-pointer))))


(define-magic-argument workstation-context-specifics (mouse-pointer)
  (let ((ws (first (workstation-context-stack (workstation-for-mouse-pointer mouse-pointer)))))
     (specific-structure-for-workstation-context ws)))


(define-magic-argument spot (mouse-pointer)
  (stack-of-spots mouse-pointer))

(define-magic-argument innermost-spot (mouse-pointer)	    ; Synonym.
  (stack-of-spots mouse-pointer))

(define-magic-argument pane (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot pane-spot pane-of-spot))



;;; The magic argument `detail-pane' are is to the pane in the current window,
;;; if any, with the corresponding name.  Note that detail-pane should never be
;;; nil, and the others may generally be nil or non-nil depending on the
;;; situation.

(define-magic-argument detail-pane (mouse-pointer)
  (declare (ignore mouse-pointer))
  (detail-pane (window-for-workstation current-workstation)))



;; Is this ever different from the image-plane in the event?
(define-magic-argument image-plane (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot image-plane-spot image-plane-of-spot))

;; Is this ever different?
(define-magic-argument image-plane-showing-block (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot image-plane-spot image-plane-of-spot))

(define-magic-argument native-window (mouse-pointer)
  (let* ((event-plist (get-magic-argument 'event-plist mouse-pointer))
	 (handle? (getf event-plist 'window)))
    (when handle?
      (find-native-window (window-for-workstation current-workstation) handle?))))

(define-magic-argument native-image-plane (mouse-pointer)
  (let* ((event-plist (get-magic-argument 'event-plist mouse-pointer))
	 (handle? (getf event-plist 'window)))
    (when handle?
      (find-native-image-plane (window-for-workstation current-workstation) handle?))))


(define-magic-argument current-selection (mouse-pointer)
  (declare (ignore mouse-pointer))
  (current-selection))


(define-magic-argument x-in-window (mouse-pointer)
  (x-of-mouse-pointer mouse-pointer))

(define-magic-argument y-in-window (mouse-pointer)
  (y-of-mouse-pointer mouse-pointer))


(define-magic-argument x-in-workspace (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot image-plane-spot x-in-workspace-of-spot))

(define-magic-argument y-in-workspace (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot image-plane-spot y-in-workspace-of-spot))


;;; `x-in-workspace-of-selection-focus' and `y-in-workspace-of-selection-focus'
;;; returns the workspace coordinate of of the mouse when the current
;;; selection-style's causes an image-plane and object to be focused on.  For
;;; example when moving a block in a workspace even if the mouse moves outside
;;; the image-plane, and over another image-plane we want to have x/y relative
;;; to the home workspace.  Another example is in marking-state we want to focus
;;; on the block containing the text, even if we drag outside that block.

(define-magic-argument x-in-workspace-of-selection-focus (mouse-pointer)
  (x-in-workspace-of-selection-focus? mouse-pointer))

(define-magic-argument y-in-workspace-of-selection-focus (mouse-pointer)
  (y-in-workspace-of-selection-focus? mouse-pointer))

(define-magic-argument image-plane-of-selection-focus (mouse-pointer)
  (image-plane-with-selection-focus-of-workstation?
	   (workstation-for-mouse-pointer mouse-pointer)))


;;; `Block-of-selection-focus' returns just that, since the mouse-pointer can
;;; persist longer than the focus it's use to have moved into the mouse-pointer.

(define-magic-argument block-of-selection-focus (mouse-pointer)
  (block-of-selection-focus? mouse-pointer))

;;  (block-with-selection-focus-of-workstation
;;    (workstation-for-mouse-pointer mouse-pointer))


(define-magic-argument workspace-of-selection-focus (mouse-pointer)
  (let ((image-plane?
	 (image-plane-with-selection-focus-of-workstation?
	   (workstation-for-mouse-pointer mouse-pointer))))
    (if image-plane?
	(workspace-on-image-plane? image-plane?))))


;; These are defined to be the most recent x,y we can find.
;; And, they will never work, because magic arguments are filled at the time
;; the menu is put-up, before the menu item is selected!
(define-magic-argument latest-x-in-window (mouse-pointer)
  (x-of-mouse-pointer
    (mouse-pointer-of-latest-event
      (workstation-for-mouse-pointer mouse-pointer))))

(define-magic-argument latest-y-in-window (mouse-pointer)
  (y-of-mouse-pointer
    (mouse-pointer-of-latest-event
      (workstation-for-mouse-pointer mouse-pointer))))


;; Only differ if we were invoked via a menu.

(define-magic-argument original-mouse-pointer (mouse-pointer)
  (let ((menu? (find-frame-in-mouse-pointer mouse-pointer menu-p)))
    (if menu?
	(menu-mouse-pointer menu?)
	mouse-pointer)))

(define-magic-argument original-x-in-window (mouse-pointer)
  (let ((menu? (find-frame-in-mouse-pointer mouse-pointer menu-p)))
    (if menu?
	(x-in-window-prior-to-posting-menu menu?)
	(x-of-mouse-pointer mouse-pointer))))

(define-magic-argument original-y-in-window (mouse-pointer)
  (let ((menu? (find-frame-in-mouse-pointer mouse-pointer menu-p)))
    (if menu?
	(y-in-window-prior-to-posting-menu menu?)
	(y-of-mouse-pointer mouse-pointer))))


;; Note that given a click on an attributes-table, FRAME gets the frame represented,
;; and not the table itself.

(define-magic-argument frame (mouse-pointer)
  (find-frame-in-mouse-pointer mouse-pointer framep))



(defun get-subframe (frame slot-name defining-class?)
  (let ((slot-value (get-slot-value-if-any frame slot-name defining-class?)))
    (when (and slot-value (framep slot-value))
      slot-value)))



;;; The magic-argument `frame-or-subframe' returns the frame, if we are not
;;; over an attribute table, or the subframe of the slot, if any, if we are.
;;; It is used as the argument to enable, disable, describe, and
;;; describe-restrictions commands which normally operate on the frame under
;;; the mouse but switch to the subframe if the mouse is over an attribute
;;; table.  Readout-tables are a special case.  They look like ordinary tables
;;; to spot generation, but behave completely differently.

(define-magic-argument frame-or-subframe (mouse-pointer)
  (let ((spot
	  (stack-of-spots mouse-pointer))
	(readout-table?
	  (find-spot-of-type-and-return-value-of-slot
	    readout-table-spot frame-represented?)))
    (cond (readout-table?
	   readout-table?)
	  ((or (ab-typep spot 'attribute-name-represented-by-table-spot)
	       (ab-typep spot 'attribute-value-represented-by-table-spot))
	   (let ((slot-name (slot-name-of-spot spot))
		 (defining-class (defining-class-of-spot spot))
		 (frame (frame-represented? (enclosing-spot? spot))))
	     (get-subframe frame slot-name defining-class)))
	  (t
	   (find-frame-in-mouse-pointer mouse-pointer framep)))))




;;; The magic-argument `subframe' returns the subframe of a table slot, if any.

(define-magic-argument subframe (mouse-pointer)
  (let ((spot (stack-of-spots mouse-pointer)))
    (ab-typecase spot
      ((attribute-name-represented-by-table-spot attribute-value-represented-by-table-spot)
       (let ((slot-name (slot-name-of-spot spot))
	     (defining-class (defining-class-of-spot spot))
	     (frame (frame-represented? (enclosing-spot? spot))))
	 (get-subframe frame slot-name defining-class))))))



;;; The TABLE magic argument is defined to return and table it can find, including, eg, readout-tables.
;;; The ATTRIBUTE-TABLE magic argument returns an attribute-table, if any, which is a representation
;;; of some frame.  The mere fact that the frame you clicked on is a table (for example, a readout-table),
;;; is NOT enough to bind this magic argument.

;;; Clicks on an attribute-table always generate these three spots:
;;;  #<ATTRIBUTE-NAME-REPRESENTED-BY-TABLE-SPOT NIL @1295>                    -- attribute-name
;;;    #<ATTRIBUTE-VALUE-REPRESENTED-BY-TABLE-SPOT NIL @1301>                   -- One or the other of these.
;;;  #<ITEM-REPRESENTED-BY-TABLE-SPOT #<FLOAT-ARRAY @1296> @1233>             -- frame
;;;  #<ATTRIBUTE-TABLE-SPOT #<TABLE ATTRIBUTES-TABLE-FORMAT @1294> @1344>     -- text-cell, row, column
;;;     #<ATTRIBUTE-DISPLAY-SPOT #<TABLE ATTRIBUTE-DISPLAY-TABLE-FORMAT @1299> @1336>  -- ditto.
;;; The table itself, in the third spot, may be an attribute-table or an attribute-display.


(define-magic-argument table (mouse-pointer)
  (find-frame-in-mouse-pointer mouse-pointer table-p))


;;; The TABLE-BUT-NOT-KB-ITEM magic argument is similar, but will not get, e.g.,
;;; readout tables (at least if they're transient or permanent items, i.e., part
;;; of the user's KB).

(define-magic-argument table-but-not-kb-item (mouse-pointer)
  (find-frame-in-mouse-pointer mouse-pointer table-but-not-kb-item-p))


;;; The function `table-but-not-kb-item-p' is true if block is a table but is
;;; not a "KB item', meaning it is neither permanent nor transient.

(defun table-but-not-kb-item-p (block)
  (and (table-p block)
       ;; neither-permanent-nor-transient-p ? kb-item-p?
       (not (or (transient-p block) (permanent-block-p block)))))

;; For finding a table, but not a readout table, which is a different thing, as
;; has been noted elsewhere, but also anything that's a table that is part of
;; the user's KB, including table-item and graph instances. So we check for the
;; item being either permanent or transient, which is about the most
;; reliable test.  The main goal is to not return inspect tables (tabular
;; displays, short representations tables, etc.)  (MHD 1/17/01)



;;; The magic-argument `attribute-table' matches either an ordinary attribute table or
;;; an attribute display.

(define-magic-argument attribute-table (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot (attribute-table-spot attribute-display-spot
						table-header-spot
						search-state-table-spot
						graph-table-spot)
					      frame-represented?))


;;; The magic-argument `short-representation-table' includes multiframe tables, too.

(define-magic-argument short-representation-table (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot (short-representation-table-spot
						multiframe-table-spot)
					      frame-represented?))


;;; The magic-argument `text-cell-of-table' returns the text-cell of a table.

(define-magic-argument text-cell-of-table (mouse-pointer)
  (let ((table-cell (find-spot-of-type-and-return-value-of-slot
		      table-spot
		      table-cell-of-spot?)))
    (when (cell-is-text-cell-p table-cell)
      table-cell)))

(define-magic-argument cell-of-table (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot table-spot table-cell-of-spot?))

(define-magic-argument slot-name (mouse-pointer)
  (or (find-spot-of-type-and-return-value-of-slot
	(attribute-represented-by-table-spot)
	slot-name-of-spot)
      (let ((text-box-spot? (find-spot-of-type-and-return-value-of-slot
			      (text-box-spot) progn)))
	(when text-box-spot?
	  (let ((text-box (frame-represented? text-box-spot?)))
	    (frame-class-case text-box
	      (name-box 'name-or-names-for-frame)
	      (edit-box nil)
	      (t 'box-translation-and-text)))))))


(define-magic-argument defining-class (mouse-pointer)
  (or (find-spot-of-type-and-return-value-of-slot
	(attribute-represented-by-table-spot)
	defining-class-of-spot)
      (let ((text-box-spot? (find-spot-of-type-and-return-value-of-slot
			      (text-box-spot) progn)))
	(when text-box-spot?
	  (let ((text-box (frame-represented? text-box-spot?)))
	    (frame-class-case text-box
	      (name-box 'block)
	      (edit-box nil)
	      (t 'text-box)))))))

(define-magic-argument slot-component-name? (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot
    (attribute-represented-by-table-spot)
    slot-component-name-of-spot?))

(define-magic-argument slot-component-indicator? (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot
    (attribute-represented-by-table-spot)
    slot-component-indicator-of-spot?))

;; I think that this always gets the same value that the FRAME magic arg does.
(define-magic-argument frame-represented-by-table (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot
    item-represented-by-table-spot
    frame-represented?))


;;; `Block-showing-representation' returns the block whose draw method rendered
;;; the spot in question.  Currently this only works for tables and text-boxes.

(define-magic-argument block-showing-representation (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot text-spot frame-represented?)
  ;; icon, chart, graph, workspace... 
  )


;;; `block-being-represented' returns the frame that is being shown as opposed
;;; to the frame that is doing the showing.  For example a table usually is
;;; displaying the attributes of some other frame, a name box is showing the
;;; name of a frame.  Ths currently only works for text-box and table.

(define-magic-argument block-being-represented (mouse-pointer)
  (or
    ;; Table
    (find-spot-of-type-and-return-value-of-slot
      item-represented-by-table-spot
      frame-represented?)
    ;; Text-box
    (let ((text-box-spot? (find-spot-of-type mouse-pointer 'text-box-spot)))
      (when text-box-spot?
	(let ((frame-represented? (frame-represented? text-box-spot?)))
	  (frame-class-case frame-represented?
	    (name-box
	      (superblock? frame-represented?))
	    ;; Not edit box, since it is representing a proxy of the frame.
	    (text-box frame-represented?)))))))

;; Should this work for icons and workspaces as well?
;; Multiframe-table-spot are thought provoking?
;; Network info table?



;;; `Frame-transform-block' is the block within who's coordinate
;;; system is used by block drawn under the mouse pointer.

#+development
(define-magic-argument frame-transform-block (mouse-pointer)
  (let* ((image-plane?
	   (blackboard-argument-of-mouse-pointer
	    mouse-pointer
	    'image-plane))
	 (block-showing-representation?
	   (if image-plane?
	       (blackboard-argument-of-mouse-pointer
		 mouse-pointer
		 'block-showing-representation)))
	 (frame-transform?
	   (if block-showing-representation?
	       (find-frame-transform-if-any
		 (blackboard-argument-of-mouse-pointer
		   mouse-pointer
		   'block-showing-representation)
		 image-plane?))))
    (if frame-transform?
	(block-of-frame-transform frame-transform?))))





;; A table which is an attribute-display.
(define-magic-argument attribute-display (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot attribute-display-spot frame-represented?))

(define-magic-argument attribute-display-text-cell (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot
    attribute-display-spot table-cell-of-spot?))


;; A table which is a graph.
(define-magic-argument graph-table (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot graph-table-spot frame-represented?))

(define-magic-argument line-index (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot
    text-spot line-index-of-text-spot))

(define-magic-argument character-index (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot
    text-spot character-index-of-text-spot))

(define-magic-argument text-plist (mouse-pointer)
  (find-spot-of-type-and-return-value-of-slot
    text-spot format-plist-of-text-spot))




;;; `Editable-text-spot-p' returns the text-spot of the mouse-pointer if
;;; that text spot denotes an editable fragment of text.  A text-spot
;;; has a slot to record if editing is allowed, this routine maintains
;;; that slot and the slot is useless until this is called once.

(define-magic-argument editable-text-spot-p (mouse-pointer)
  (let (text-spot)
    (when (setf text-spot (find-spot-of-type mouse-pointer 'text-spot))
      ;; Late binding for (editable-text-spot-p text-spot).
      (when (eq :unknown (editable-text-spot-p text-spot))
	(setf (editable-text-spot-p text-spot) nil) ;; Default awnser.
	(when (or (find-spot-of-type mouse-pointer
				     'attribute-value-represented-by-table-spot)
		  (find-spot-of-type mouse-pointer 'text-box-spot))
	  (when (with-mouse-pointer-bindings (image-plane
					       block-being-represented
					       block-showing-representation
					       slot-name
					       &optional defining-class)
		    mouse-pointer
		  (and
		    (or (slot-editable-p
			  block-being-represented slot-name defining-class)
			(editable-virtual-attribute-p
			  block-being-represented slot-name defining-class))
		    (text-visible-p
		      (format-frame-of-text-spot text-spot)
		      (format-plist-of-text-spot text-spot)
		      (image-x-scale image-plane)
		      (image-y-scale image-plane))))
	    (setf (editable-text-spot-p text-spot) text-spot))))
      (editable-text-spot-p text-spot))))

;; See the Note on the click-to-edit command.



;;; `Image-plane-of-mouse-pointer' finds the image-plane for the given
;;; mouse-pointer.

(defun image-plane-of-mouse-pointer (mouse-pointer)
  (with-mouse-pointer-bindings (&optional (image-plane? image-plane))
      mouse-pointer
    (or image-plane?
	#+development (error "No image-plane in mouse-pointer ~s" mouse-pointer))))





;;; The magic-argument `frame-for-selection' is the frame which the old
;;; selection context operated upon (hopefully).

(define-magic-argument frame-for-selection (mouse-pointer)
  (compute-frame-for-selection mouse-pointer))

(defun compute-frame-for-selection (mouse-pointer)
  (with-mouse-pointer-bindings
      (&optional (graph-table? graph-table)
		 (short-representation-table? short-representation-table)
		 (attribute-display? attribute-display)
		 (attribute-table? attribute-table)
		 (frame? frame)
		 (workspace? workspace))
      mouse-pointer
    
    (or graph-table?
	short-representation-table?
	attribute-display?
	attribute-table?

	;; Clicks in the editor which make it to here, meaning that they were
	;; not handled by the editor context, should refer to the editor
	;; workspace.  Although since the innermost spot may still not be a
	;; workspace-background-spot, the menu found will be wrong.
	(if (and workspace?
		 (frame-of-class-p workspace? 'edit-workspace))
	    workspace?
	    frame?))))

;; It is a question what to "select" here.  Selecting simply on frame
;; unfortunately gets us, when over tables, the underlying frame the table is
;; representing.

;; This might be identical to most-interesting-frame. It's hard to prove.



(define-magic-argument most-interesting-frame (mouse-pointer)
  (most-interesting-frame mouse-pointer))


;;; The function `most-interesting-frame-in-spot' searches for the
;;; "interesting" frame represented by the spot.  It is the frame used for
;;; searching the object configurations path.  Here we try to return the
;;; table, for example, rather than the item represented by the table.

(defun most-interesting-frame-in-spot (spot)
  (loop with frame*
	for spot = spot then (enclosing-spot? spot)
	while spot
	;; Comment-out this line to allow clicks on the background pane to have
	;; a frame.  This is one step towards allowing user-menu-choices to run
	;; anywhere.
	until (entire-g2-window-spot-p spot)
	for frame = (frame-represented? spot)
	finally (return frame*)
	doing
    (ab-typecase spot
      ((short-representation-table-spot
	 multiframe-table-spot
	 attribute-display-spot attribute-table-spot)
       (return frame))
      (t
	(setq frame* (or frame* frame))))))

;; I added the condition on ENTIRE-G2-WINDOW-SPOT so that object
;; configurations, such as selecting any object, will not match the G2 window,
;; which is an object.  This might not be exactly the right test.  Do object
;; configs ever want to affect clicks on the pane background? -fmw, 1/10/94


(defun most-interesting-frame (mouse-pointer)
  (most-interesting-frame-in-spot (stack-of-spots mouse-pointer)))


#+unused
(defun mouse-pointer-same-objects-p (mouse-pointer-1 mouse-pointer-2)
  (and (not (contains-invalid-spots mouse-pointer-1))
       (not (contains-invalid-spots mouse-pointer-2))
       (stack-of-spots mouse-pointer-1)
       (stack-of-spots mouse-pointer-2)
       (eq (type-name-of (stack-of-spots mouse-pointer-1))
	   (type-name-of (stack-of-spots mouse-pointer-2)))
       (eq (most-interesting-frame mouse-pointer-1)
	   (most-interesting-frame mouse-pointer-2))))


;;;; Magic arguments for selection


;;; The magic-argument `thing-to-select' returns the thing to be selected given
;;; a mouse-pointer. As a side-effect, it adds the PARENT property to a
;;; text-cell, in anticipation of selecting it. This is where we make clicks on
;;; non-selectable table cells select the entire table.

(define-magic-argument thing-to-select (mouse-pointer)
  (with-mouse-pointer-bindings
      (spot block &optional
	    (attribute-table? attribute-table)
	    (table? table)
	    (cell-of-table? cell-of-table)
	    (short-representation-table? short-representation-table))
      mouse-pointer
    ;; Make sure that short-representations get priority. Also, attribute-table
    ;; differs from from table in the case where it is the attribute-table of a
    ;; table object, such as a readout table. In that case we want the
    ;; attribute-table, not the underlying object.
    (let ((the-table? (or short-representation-table?
			  attribute-table?
			  table?)))
      (cond ((and (eq (structure-class spot) 'attribute-name-represented-by-table-spot)
		  the-table?)
	     the-table?)
	    ((eq (structure-class spot) 'attribute-value-represented-by-table-spot)
	     (if (selectable-table-cell-p the-table? cell-of-table?)
		 (prepare-table-cell cell-of-table? the-table?)
		 the-table?))
	    ((and (framep block) (frame-of-class-p block 'connection))
	     (connection-for-this-connection-frame block))
	    (t
	     (or the-table? block))))))


;;; The function `prepare-table-cell' "prepares" a table cell to be selected and
;;; returns the cell. For a text cell to be selected, it must know the table in
;;; which it resides.

(defun prepare-table-cell (cell? table)
  (when cell?
    (assert-for-development (cell-in-table-p cell? table) "~s not in ~s!" cell? table)
    table
;    (when (cell-is-text-cell-p cell?)
;      (change-text-cell-property cell? 'parent table))
    cell?))

;;; The function `get-table-for-cell' is the inverse of prepare-text-cell. It
;;; returns the table for a text-cell.

(defun get-table-for-cell (cell)
  (cond ((cell-is-text-cell-p cell)
;	 (getf (text-cell-plist cell) 'parent)
	 (let ((frame? (get-slot-represented-by-text-cell-if-any cell)))
	   (when frame?
	     (loop for representation in (frame-representations frame?)
		   thereis (and (table-p representation)
				(loop for row in (table-rows representation)
				      thereis (memq cell row))
				representation)))))
	(t
	 (superblock? cell))))

;; Adding a property to the text-cell-plist caused problems because the entire
;; plist is copied when an item is cloned (and saved when an item is KB-saved),
;; leading to some shared structure. At the cost of some performance, we can dig
;; out the table for a text-cell by scanning the representations of the frame it
;; represents. This is the fix for HQ-4480612 "deleting a workspace makes kb
;; unsavable".  -fmw, 1/21/03



(defun cell-in-table-p (cell table)
  (loop for row in (table-rows table)
	thereis (loop for element in row
		      thereis (eq cell element))))


(define-magic-argument selected-image-plane (mouse-pointer)
  (with-mouse-pointer-bindings (workstation) mouse-pointer
    (selected-image-plane workstation)))

(define-magic-argument selected-workspace (mouse-pointer)
  (with-mouse-pointer-bindings (workstation) mouse-pointer
    (selected-workspace workstation)))

(define-magic-argument selected-native-window (mouse-pointer)
  (with-mouse-pointer-bindings (workstation) mouse-pointer
    (selected-native-window? workstation)))



;;;; Things needing magic arguments.


(defvar compute-menu-items-list)

(defun collect-menu-item (menu-description menu-item mouse-pointer)
  (declare (ignore menu-description mouse-pointer))
  ;; The menu-item is already newly consed here.
  (slot-value-push menu-item compute-menu-items-list)
  nil)


;;; The function `compute-menu-items' returns the final list of menu
;;; choices, and so needs the mouse-pointer, in order to be able to call
;;; all the predicates, restrictions, etc. The list is newly consed, and
;;; should be reclaimed with reclaim-menu-items.

(defun compute-menu-items (menu-description mouse-pointer parameters)
  ;; Filter first by command-availability, and copy the list.
  (let ((compute-menu-items-list ()))
    (map-over-menu-items menu-description #'collect-menu-item mouse-pointer parameters)
    (let ((available-choices (nreverse compute-menu-items-list)))

      ;; Then by restrictions.
      (let ((restriction-type (menu-description-restriction-type menu-description)))

	;; *** Probably not getting the correct slot name here... ***

	(multiple-value-bind (choice-restrictions permitted?)
	    (compute-restrictions restriction-type mouse-pointer)

	  ;; This guy reclaims available-choices and choice-restrictions.
	  (filter-choices-by-restrictions available-choices
					  choice-restrictions
					  permitted?))))))


;;; The variable `cached-restrictions-alist' is bound to an alist of (type
;;; permitted? . choices) for all types of KB-level restrictions.

(defvar cached-restrictions-alist)

;; Restrictions are somewhat expensive to compute, so we compute all four types
;; once, and use the appropriate one for each menu we encounter in the recursive
;; decent of get-menu-choice-list.



;;; The function `restriction-type-for-command' is a hack to get around the
;;; problem that new-workspace and get-workspace are in the Workspace menu in
;;; the menu bar, but obey main-menu restrictions, and Print is in the file menu
;;; in the menu bar but obeys workspace-menu-restrictions. We could move the
;;; commands, or we can do this.

(defparameter main-menu-restriction-type-exceptions '(new-workspace get-workspace statusbar))
(defparameter workspace-menu-restriction-type-exceptions '(print-to-server print-to-client))

(defun-substitution-macro restriction-type-for-command (cmd? default-restriction-type?)
  (let ((command? (cond ((null cmd?)
			 nil)
			((partial-command-p cmd?)
			 (find-ui-command (partial-command-name cmd?)))
			((symbolp cmd?)
			 (find-ui-command cmd?))
			((ui-command-p cmd?)
			 cmd?))))
    (cond ((and command?
		(memq (ui-command-name command?) main-menu-restriction-type-exceptions))
	   'main-menu)
 	  ((and command?
 		(memq (ui-command-name command?)
		      workspace-menu-restriction-type-exceptions))
 	   'workspace-menu)
	  (t
	   default-restriction-type?))))


;;; The recursive function `get-menu-choice-list' returns a newly consed list
;;; of the top-level items in the given menu.  Unlike compute-menu-items, we
;;; don't remove commands which are not available-p, we let them through and
;;; they will later be grayed.  Although it takes a mouse-pointer argument, only
;;; the window-level information in it should be used, since the menu bar
;;; contents must necessarily be independent of the current selection.

;;; The convention here is that we only remove commands which have been
;;; restricted-away at the KB level (in kb-configuration). Gray/ungraying (see
;;; `update-native-menu') takes care of the other current-selection-dependent
;;; restrictions.

;;; The list should be reclaimed with reclaim-menu-items.

(defun get-menu-choice-list (menu-description)
  (let* ((choice-list
	   (menu-description-choice-list-internal menu-description))
	 (choices
	   (cond ((atom choice-list)
		  (dwarn "You will indubitably lose: ~s" choice-list))
		 (t
		  (loop for choice in choice-list
			as include-clause? = (and (consp choice)
						  (eq (first choice) 'include))
			as included-choices = (when (and include-clause?
							 (menu-description-named (second choice)))
						(get-menu-choice-list
						  (menu-description-named (second choice))))
			if include-clause?
			  nconc included-choices
			else
			  collect (copy-menu-item choice) using slot-value-cons)))))
    ;; Now choices is a list of full command names, or (COMMAND ...) or (SUBMENU
    ;; ...)  clauses. Filter it by the restrictions appropriate for this menu.
    ;; See also filter-choices-by-restrictions
    (prog1
	(loop with default-restriction-type? = (menu-description-restriction-type menu-description)
	      for choice in choices
	      as cmd? = (and (atom choice) (ui-command-named choice))
	      as restriction-type = (restriction-type-for-command
				      cmd? default-restriction-type?)
	      as restrictions = (cdr (assq restriction-type cached-restrictions-alist))
	      as choice-name = (if cmd? (ui-command-menu-name cmd?) (menu-item-name choice))
	      as allowed-p = (if (memq choice-name (cdr restrictions))
				 (car restrictions) (not (car restrictions)))
	      if allowed-p
		collect (copy-menu-item choice) using slot-value-cons)
      (reclaim-menu-items choices))))

;; compute-menu-items does the same thing, but returns a list of partial
;; commands, and simply omits commands which don't apply, rather than leaving
;; them in for us to gray out later.  However, it does filter on restrictions,
;; which we aren't doing here.



;;; The defvar `name-for-find-menu-item' is bound to the menu-name we are
;;; looking for.  If should be the name for restrictions.

(defvar name-for-find-menu-item)

(defun find-menu-item-internal (menu-description menu-item mouse-pointer)
  (declare (ignore menu-description mouse-pointer))
  (cond ((eq name-for-find-menu-item (menu-item-name menu-item))
	 menu-item)
	(t
	 (reclaim-menu-item menu-item)
	 nil)))
    
						 
;;; The function `find-menu-item' returns the menu-item whose label is
;;; MENU-NAME, for the given menu or one of its explicit menus.  The menu-item
;;; is newly consed, and should be reclaimed with reclaim-menu-item. (It may be
;;; a partial-command instance, for example).

(defun find-menu-item (menu-name menu-description mouse-pointer parameters)
  (let ((name-for-find-menu-item menu-name))
    (map-over-menu-items menu-description #'find-menu-item-internal
			 mouse-pointer parameters t)))





;;; The function `command-permitted-p' returns T iff the given UI command has
;;; not been completely disabled by "exclude absolutely" configurations
;;; clauses.  The configuration clauses which merely "exclude" or "include" are
;;; not checked here since those do not disable the commands themselves, but
;;; merely remove them from the default menus.

(defun command-permitted-p (command-name frame?)
  (not (command-is-excluded-absolutely-p command-name frame?)))

;; There are two kinds of permission: A command in a menu is permitted if it
;; appears in the menu after summing the contributions of all of the
;; include/exclude restrictions.  A command as the target of "selecting",
;; "clicking", or "pressing" is permitted if it does not appear in an "exclude
;; absolutely" clause -- ordinary nonabsolute clauses don't apply.  -fmw,
;; 3/15/95

;; The frame? argument should be the most-interesting-frame in a mouse-pointer.

  

;;; The function `compute-restrictions' determines the set of allowed menu
;;; choices for item at the given mouse-pointer.  The restriction-type argument
;;; determines which sets of restrictions are scanned, since they're spread
;;; over several different system table slots.  It returns the standard FILTERS
;;; representation of the set, via two values, choice-restrictions and
;;; permitted?.

;;; Choice-restrictions is a newly consed filter-list of names of commands to
;;; permit or to forbid.

(defun compute-restrictions (restriction-type mouse-pointer)
  (with-mouse-pointer-bindings (&optional (frame? frame) (slot-name? slot-name))
      mouse-pointer
    (case restriction-type
      (main-menu
       (compute-main-menu-restrictions))
      ((workspace-menu item-menu)
       ;; Maybe get rid of workspace-menu here!
       (compute-menu-restrictions-for-workspace frame?))
      (table-menu
       (cond ((display-table-p frame?)
	      (compute-menu-restrictions-for-workspace frame?))
	     (frame?
	      (compute-menu-restrictions-for-click-on-table ; Click-on?
		frame?
		(alias-slot-name-if-necessary slot-name? frame?)
		nil))))					    ; Defining class ???
      (t
       nil))))

;; Parameter menus, eg, should have a restriction type of NIL.




;;; The function `reclaim-menu-items' reclaims a slot-value list of menu-items.

(defun reclaim-menu-items (menu-items)
  (loop for menu-item in menu-items doing
    (reclaim-menu-item menu-item))
  (reclaim-slot-value-list menu-items))

  

;;; The function `name-of-user-menu-choice?' returns T if NAME is the name of
;;; some user-menu-choice applicable to FRAME.  It may or may not actually be
;;; runnable at the moment.

(defun name-of-user-menu-choice? (name frame)
  (when (frame-of-class-p frame 'item)
    (loop for superior-class in (class-inheritance-path (class-description (class frame)))
	  thereis (loop for user-menu-choice in (user-menu-choices-for-this-class superior-class)
			as symbol? = (user-menu-choice-symbol? user-menu-choice)
			thereis (eq symbol? name)))))



;;; The function `user-menu-choice-potentially-runnable-p' returns true if there
;;; is a user-menu-choice named NAME applicable to the given frame, and it is
;;; potentially runnable.

(defun user-menu-choice-potentially-runnable-p (name frame)
  (let ((user-menu-choice? (get-user-menu-choice-or-choice-symbols frame name)))
    (and user-menu-choice?
	 (embedded-rule-in-user-menu-choice? user-menu-choice?))))

;; Only used in development, currently.






;;;; Workstation Context for Hot Spot Tracking

;;; `Hot-spot-tracking' is a workstation context used to track the depressed
;;; mouse over some hot spot on the screen.  It is invoked with a rectangle,
;;; image-plane, block, function and time constant.  The function is called as
;;; the mouse is dragged or, if possible, as often as the time constant
;;; suggests.

;;; The function's arguments are:
;;;   - a "method name",
;;;   - mouse pointer of current event.
;;;   - a boolean indicating if we are inside or outside the block,
;;;   - the block,
;;;   - the "info"
;;; The method is one of these symbols:
;;;   - :mouse-down      -- Called only once, as the first call.
;;; The following are invoked as needed to indicate the state of things.
;;;   - :enter-hot-spot  -- Called at least once.
;;;   - :exit-hot-spot   -- Called zero or more times
;;;   - :idle            -- Called zero or more,  whenevever the heart beat demands it.
;;; Finally to wrap things up these are called.
;;;   - :mouse-up   -- Called zero or more times. 
;;;   - :abort      -- A final call.
;;; Lastly this is called once to allow you to cleanup the info highlighting, etc.
;;; Note you may have aborted at this point, inwhich case the info will be :aborted.
;;;   - :unwind

;;; This doesn't behave well if the image-plane is scaled or moved.

;; It might be possible to do that with a mess of mechinism and passing the
;; frame-transform enclosing the hot spot?

;;; The context can be aborted by a few things.  The block might be reclaimed,
;;; the block might be transfered off the workspace in question and finally the
;;; user might abort the context.

(define-workstation-context hot-spot (workstation-context-with-selection-focus)
  :selection-style top-level-with-selection-focus-is-selection-style
  :parent nil
  :modal t
  :constructor (make-hot-spot-state
		 (block-with-selection-focus-of-workstation-context
		   image-plane-with-selection-focus-of-workstation-context
		   reference-number-of-image-plane
		   method-function-of-hot-spot
		   info-of-hot-spot
		   left-edge-in-focus-of-hot-spot
		   top-edge-in-focus-of-hot-spot
		   right-edge-in-focus-of-hot-spot
		   bottom-edge-in-focus-of-hot-spot))
  :state-variables (method-function-of-hot-spot
		    info-of-hot-spot
		    left-edge-in-focus-of-hot-spot
		    top-edge-in-focus-of-hot-spot
		    right-edge-in-focus-of-hot-spot
		    bottom-edge-in-focus-of-hot-spot
		    (consider-autorepeat-of-hot-spot nil)
		    (drawing-activity-of-hot-spot-state?
		      nil :reclaimer cancel-identified-drawing-activity-if-any)
		    (frame-reference-of-hot-spot-tracking
		      (copy-of-current-frame-serial-number-function))
		    (recently-inside-of-hot-spot-p t)
		    (workspace-of-hot-spot
		      (workspace-on-image-plane?
			image-plane-with-selection-focus-of-workstation-context))
		    (recent-event-time-of-hot-spot-state
		      (fixnum-time-of-mouse-pointer
			(mouse-pointer-of-latest-event current-workstation)))
		    )
  :keymaps (global-development ;; mostly to get debugging support.
	     hot-spot-gestures))

(define-keymap hot-spot-gestures ()
  (<mouse-up> mouse-up-in-hot-spot)
  (<mouse-motion> mouse-motion-in-hot-spot)
  (<standard-abort-keys> abort-hot-spot))



;;; `Call-hot-spot-method' is useful for tracing.  It also
;;; bottlenecks the maintainance of the hot-spot-state.

(defun call-hot-spot-method (method-name inside-p)
  #+development
  (unless (member method-name '(;; First you get one of these
				:mouse-down
				;; Then you get an assortment of these,
				;; the enter/exit pairs are well behaved.
				:idle :enter-hot-spot :exit-hot-spot
				;; Then ou get one of these.
				:mouse-up :abort
				;; Finally you get one of these.
				:unwind))
    (error "Unexpected hot spot method-name"))
  (let ((hot-spot-state specific-structure-for-current-workstation-context))
    (funcall-symbol
      (method-function-of-hot-spot hot-spot-state)
      method-name
      inside-p)
    (setf (recently-inside-of-hot-spot-p hot-spot-state) (if inside-p t nil))))







;;; `Mouse-motion-in-hot-spot' hangs off the mouse motion event in the
;;; keymap of the hot-spot-state.  It is also called by mouse up, and
;;; mouse down.

(define-event-handler mouse-motion-in-hot-spot ((hot-spot-state
						  workstation-context-specifics)
						mouse-pointer
						x-in-workspace-of-selection-focus
						y-in-workspace-of-selection-focus)
  (let ((recently-inside-of-hot-spot-p
	  (recently-inside-of-hot-spot-p hot-spot-state))
	(now-inside-hot-spot-p
	  (point-inside-rectangle-p 
	    x-in-workspace-of-selection-focus
	    y-in-workspace-of-selection-focus
	    (left-edge-in-focus-of-hot-spot hot-spot-state)
	    (top-edge-in-focus-of-hot-spot hot-spot-state)
	    (right-edge-in-focus-of-hot-spot hot-spot-state)
	    (bottom-edge-in-focus-of-hot-spot hot-spot-state))))
    (macrolet ((call-hot-spot-method-1 (method)
		 `(call-hot-spot-method ,method now-inside-hot-spot-p)))
      (cond
	;; Exit?
	((and recently-inside-of-hot-spot-p
	      (not now-inside-hot-spot-p))
	 (call-hot-spot-method-1 :exit-hot-spot))
	;; Enter?
	((and (not recently-inside-of-hot-spot-p)
	      now-inside-hot-spot-p)
	 (call-hot-spot-method-1 :enter-hot-spot))
	(T
	 (call-hot-spot-method-1 :idle)
	 )))))


;;; `Mouse-up-in-hot-spot' simulates a mouse motion, then sends
;;; mouse-up and an unwind to the method function.

(define-event-handler mouse-up-in-hot-spot (mouse-pointer
					     (hot-spot-state
					       workstation-context-specifics))
  (mouse-motion-in-hot-spot mouse-pointer)
  (call-hot-spot-method :mouse-up (recently-inside-of-hot-spot-p hot-spot-state))
  (call-hot-spot-method :unwind (recently-inside-of-hot-spot-p hot-spot-state))
  (return-from-current-workstation-context 'hot-spot))



;;; `Abort-hot-spot' hangs off the abort key in the hot-spot keymap.
;;; it generates an abort and then an unwind event.  Finally it
;;; aborts this workstation context

(define-event-handler abort-hot-spot (mouse-pointer
				       (hot-spot-state workstation-context-specifics))
  (call-hot-spot-method :abort (recently-inside-of-hot-spot-p hot-spot-state))
  (setf (info-of-hot-spot hot-spot-state) :aborted)
  (call-hot-spot-method :unwind (recently-inside-of-hot-spot-p hot-spot-state))
  (abort-current-workstation-context 'hot-spot))







;;;; Simple Push Buttons for Scrolling


;;; When the user presses on a frame component that does scrolling we enter a
;;; hot-spot state.  The mouse pointer of the mouse down that created the state
;;; provides most of the parameterization of behavior.

;;; The method function (aka call back) of the hot spot state implements the
;;; actual scrolling etc.

;;; We create a heartbeat task to assure that we can do continous scrolling
;;; while the mouse is depressed, but not moving.  The heartbeat task sets a
;;; flag in the hotspot state's info.  When ever we actually scroll we clear the
;;; flag.  If the heartbeat notices the flag hasn't been cleared it scrolls, by
;;; invoking the idle method of the hot spot state's method function.


;;; The parameter `scrolling-autorepeat-interval' is the period of scrolling bar
;;; autorepeat in seconds.

(defparameter scrolling-autorepeat-interval 0.3)

;; I tried to change this to a 21st century value of 0.1 seconds. Unfortunately,
;; the value is used for both the autorepeat interval and the autorepeat delay,
;; and a delay of 0.1 seconds is too short (you get double scrolls all the time,
;; see HQ-4579778). And making the interval and delay different is a project.
;; So, back to a lethargic 0.3 seconds for both. -fmw, 8/19/03


;;; `Scrolling-heartbeat' is the function installed in a scheduled task.
;;; It's job is to kick the scrolling along if the event stream is idle.
;;; first it polls the event stream to check for events, if none are found
;;; it calls the hot spot method to do a quantum of scrolling.

(defun scrolling-heartbeat (workstation)
  (for-workstation (workstation)
    (with-mouse-pointer-bindings
	((hot-spot-state workstation-context-specifics))
	(mouse-pointer-of-last-down current-workstation)
      (setf (consider-autorepeat-of-hot-spot hot-spot-state) t)
      (unless (drawing-activity-of-hot-spot-state? hot-spot-state)
	(push-back-mouse-motion-event)))))


;;; `Start-or-restart-scrolling-heartbeat' is called after any scrolling
;;; occurs so that we will wait a moment and then do some more scrolling.

(defun start-or-restart-scrolling-heartbeat ()
  (cancel-task (heartbeat-task-of-workstation? current-workstation))
  (with-mouse-pointer-bindings ((hot-spot-state workstation-context-specifics))
      (mouse-pointer-of-last-down current-workstation)
    (setf (consider-autorepeat-of-hot-spot hot-spot-state) nil))
  (with-temporary-gensym-float-creation starting-scrolling-heartbeat
    (let ((realtime-interval-of-heartbeat scrolling-autorepeat-interval))
      (declare (type gensym-float realtime-interval-of-heartbeat))
      (with-future-scheduling
	  ((heartbeat-task-of-workstation? current-workstation)
	   ;; priority
	   0
	   ;; Delay prior to running.
	   (+e (gensym-get-unix-time) realtime-interval-of-heartbeat)
	   ;; Scan interval, ensure anniversaries and real time!
	   nil nil t)
	(scrolling-heartbeat current-workstation)))))

;; Currently this isn't called unless we are running.



;;; `Scroll-bar-hot-spot-method' is the callback function of the
;;; hot-spot workstation context when we are working tracking a mouse.
;;; It is called for each event handled. It is also called by the
;;; heartbeat task, a fact which makes it hard to use the state in the
;;; current event.

(defun scroll-bar-hot-spot-method (method inside?)
  (with-mouse-pointer-bindings ((hot-spot-state workstation-context-specifics)
				spot
				block
				workspace
				(gensym-window window)
				image-plane)
      (mouse-pointer-of-last-down current-workstation)
    (case method

      ;; Backing out
      (:UNWIND
       ;; Discard the heartbeat task.
       (cancel-task (heartbeat-task-of-workstation? current-workstation)))

      ((:MOUSE-DOWN :ENTER-HOT-SPOT)
       (when inside?
	 (highlight-color-of-frame-spot spot image-plane t)
	 (when (stepper-of-scroll-bar-spot-p spot)
	   (funcall-ui-command 'do-scrolling
			       spot block image-plane)
	   (suppress-autorepeat-until-drawing-is-done
	     gensym-window workspace hot-spot-state)
	   (setf (recent-event-time-of-hot-spot-state hot-spot-state)
		 ;; Assure we actually move ahead a few milliseconds?
		 (fixnum-time-of-mouse-pointer
		   (mouse-pointer-of-latest-event current-workstation)))
	   (start-or-restart-scrolling-heartbeat))))

      (:IDLE
       (when (and (consider-autorepeat-of-hot-spot hot-spot-state)
		  (mouse-still-down-p))
	 (unless (drawing-activity-of-hot-spot-state? hot-spot-state)
	   (funcall-ui-command 'do-scrolling spot block image-plane)
	   (suppress-autorepeat-until-drawing-is-done
	     gensym-window workspace hot-spot-state)
	   (start-or-restart-scrolling-heartbeat))))
      
      ((:ABORT :MOUSE-UP :EXIT-HOT-SPOT)
       ;; Scrolling on mouse up would be very annoying.
       (when (or (eq method :exit-hot-spot)
		 inside?)
	 (highlight-color-of-frame-spot spot image-plane nil)))
      #+development
      (t
       (error "Unexpected call")))))


;; Does the test on inside? ever fail?  Yes since we don't cancel the heartbeat
;; when we exit the hot-spot.

;; 1) The initial heart beat should be delayed, i.e. 1 second before auto
;; repeat!  2) Rumors that click on the elevator scrolls one line.

;;; `Enable-autorepeat-after-drawing' is the continuation for the
;;; identified drawing activity created by supress-autorepeat-until-drawing-is-done.

(defun enable-autorepeat-after-drawing
    (identified-drawing-activity kind-of-continuation)
  (case kind-of-continuation
    (:finished
     (let ((hot-spot-state
	    (arg-of-identified-drawing-activity identified-drawing-activity)))
       (setf (drawing-activity-of-hot-spot-state? hot-spot-state) nil)
       (when (consider-autorepeat-of-hot-spot hot-spot-state)
	 (for-workstation ((workstation-this-is-on
			     (gensym-window-of-identified-drawing-activity
			       identified-drawing-activity)))
	   (push-back-mouse-motion-event)))))
    (:canceled
     ))
  (remove-identified-drawing-activity
    identified-drawing-activity kind-of-continuation))



;;; `Suppress-autorepeat-until-drawing-is-done' is marks the hot-spot-state to
;;; disable autorepeating, and then enqueues a ping for the workspace's drawing
;;; that will clear it when the drawing is finished.

(defun suppress-autorepeat-until-drawing-is-done
    (gensym-window workspace hot-spot-state)
  (setf (drawing-activity-of-hot-spot-state? hot-spot-state)
	(start-identified-drawing-activity gensym-window
					   nil ;; parent
					   #'enable-autorepeat-after-drawing
					   hot-spot-state))
  (ping-workspace-drawing
    workspace
    (drawing-activity-of-hot-spot-state? hot-spot-state)))


  


(defun highlight-color-of-frame-spot (spot image-plane highlight-on?)
  (when (or (elevator-of-scroll-bar-spot-p spot)
	    (and ;; stepper
	      (eq 'line (amount-of-step spot))))
    (let* ((orientation nil)
	   (frame-widget-name
	     (if (elevator-of-scroll-bar-spot-p spot)
		 'gensym-scroll-bar-elevator-frame-component
		 (case (direction-of-step spot)
		   (left 'gensym-left-scroll-arrow-frame-component)
		   (up 'gensym-up-scroll-arrow-frame-component)
		   (right 'gensym-right-scroll-arrow-frame-component)
		   (down 'gensym-down-scroll-arrow-frame-component))))
	   (entity-used-for-rubber-stamp
	     (or
	       (getf (lookup-rubber-stamp-set-of-frame-widget frame-widget-name)
		     orientation)
	       (second resize-box-rubber-stamp-widget))))
      (let ((from-color 'dark-grey)
	    (to-color 'light-grey))
	(when highlight-on?
	  (setf from-color 'light-grey)
	  (setf to-color 'dark-grey))
	(change-color-in-rubber-stamp
	  (workspace-on-image-plane? image-plane)
	  entity-used-for-rubber-stamp
	  (left-edge-of-scroll-bar-spot spot)
	  (top-edge-of-scroll-bar-spot spot)
	  (right-edge-of-scroll-bar-spot spot)
	  (bottom-edge-of-scroll-bar-spot spot)
	  'face-color from-color to-color)))))


;;; `Enter-hot-spot-state-upon-frame-component' is an event handler which should
;;; be bound to mouse down upon those spots which do scrolling.

(define-event-handler enter-hot-spot-state-upon-frame-component
    (mouse-pointer
      (frame-component-spot innermost-spot)
      block
      image-plane)
  (let ((hot-spot-state
	  (make-hot-spot-state
	    block
	    image-plane
	    (serial-number-of-image-plane image-plane)
	    'scroll-bar-hot-spot-method
	    nil ; info-of-hot-spot
	    (left-edge-of-scroll-bar-spot frame-component-spot)
	    (top-edge-of-scroll-bar-spot frame-component-spot)
	    (right-edge-of-scroll-bar-spot frame-component-spot)
	    (bottom-edge-of-scroll-bar-spot frame-component-spot))))
    (enter-context-in-current-workstation 'hot-spot hot-spot-state t)
    (call-hot-spot-method :mouse-down t)
    hot-spot-state))



;;;; Elevator for Scrolling

(define-workstation-context elevator (workstation-context-with-selection-focus)
  :selection-style top-level-with-selection-focus-is-selection-style
  :parent nil
  :modal t
  :constructor (make-elevator-state
		 (block-with-selection-focus-of-workstation-context
		   image-plane-with-selection-focus-of-workstation-context
		   reference-number-of-image-plane))
  :state-variables (;; These are the delta from the upper left
		    ;; corner of the elevator to the mouse doen
		    ;; location
		    (x-offset-of-mouse-in-elevator-state 0)
		    (y-offset-of-mouse-in-elevator-state 0)
		    ;; This is the scale value for the elevator
		    ;; of the most recent mouse position. It
		    ;; is the pending value to commit.
		    (elevator-position-of-elevator-state 0)

		    (initial-left-edge-of-dragged-elevator 0)
		    (initial-top-edge-of-dragged-elevator 0)

		    ;; Edges of dragged elevator.
		    (left-edge-of-dragged-elevator 0)
		    (top-edge-of-dragged-elevator 0)
		    (right-edge-of-dragged-elevator 0)
		    (bottom-edge-of-dragged-elevator 0))
  :keymap ((<mouse-up> mouse-up-in-elevator-state)
	   (<mouse-motion> mouse-motion-in-elevator-state)
	   (<standard-abort-keys> abort-elevator-state)))

(define-event-handler enter-elevator-state
    ((elevator-spot innermost-spot)
     block image-plane
	  x-in-workspace
	  y-in-workspace)
  (let ((elevator-state (make-elevator-state
			  block image-plane
			  (serial-number-of-image-plane image-plane))))
    (setf (x-offset-of-mouse-in-elevator-state elevator-state)
	  (-f x-in-workspace
	      (left-edge-of-scroll-bar-spot elevator-spot)))
    (setf (y-offset-of-mouse-in-elevator-state elevator-state)
	  (-f y-in-workspace
	      (top-edge-of-scroll-bar-spot elevator-spot)))
    (enter-context-in-current-workstation 'elevator elevator-state t)
    (highlight-color-of-frame-spot elevator-spot image-plane t)
    (revisit-traveling-elevator t nil x-in-workspace y-in-workspace)
    (setf (initial-left-edge-of-dragged-elevator elevator-state)
	  (left-edge-of-dragged-elevator elevator-state))
    (setf (initial-top-edge-of-dragged-elevator elevator-state)
	  (top-edge-of-dragged-elevator elevator-state))
    elevator-state))

(define-event-handler abort-elevator-state
    ((x-in-workspace x-in-workspace-of-selection-focus)
     (y-in-workspace y-in-workspace-of-selection-focus))
  (revisit-traveling-elevator nil t x-in-workspace y-in-workspace)
  (with-mouse-pointer-bindings (spot image-plane)
      (mouse-pointer-of-last-down current-workstation)
    (highlight-color-of-frame-spot spot image-plane nil))
  (abort-current-workstation-context 'elevator))

(define-event-handler mouse-up-in-elevator-state
    ((x-in-workspace x-in-workspace-of-selection-focus)
     (y-in-workspace y-in-workspace-of-selection-focus))
  (with-mouse-pointer-bindings ((elevator-state workstation-context-specifics)
				(elevator-spot spot)
				block
				image-plane
				workspace)
      (mouse-pointer-of-last-down current-workstation)
    (with-deferred-drawing-in-process ()
      ;; Remove the ghost the user is dragging.
      (revisit-traveling-elevator nil t x-in-workspace y-in-workspace)
      ;; Unhighlight the real elevator, at it's old position
      (highlight-color-of-frame-spot elevator-spot image-plane nil)
      ;; Move the elevator, and scroll the contents.
      (let* ((elevator-shaft-spot (enclosing-spot? elevator-spot))
	     (vertical? (eq 'vertical (orientation-of-shaft elevator-shaft-spot)))
	     (old-horizontal-position-of-block (position-of-horizontal-elevator block))
	     (old-vertical-position-of-block (position-of-vertical-elevator block))
	     (new-horizontal-position-of-block
	       (if vertical?
		   old-horizontal-position-of-block
		   (elevator-position-of-elevator-state elevator-state)))
	     (new-vertical-position-of-block
	       (if vertical?
		   (elevator-position-of-elevator-state elevator-state)
		   old-vertical-position-of-block)))
	(unless (or
		  ;; The user thinks the elevator didn't move.
		  (and (=f (initial-left-edge-of-dragged-elevator
			     elevator-state)
			   (left-edge-of-dragged-elevator elevator-state))
		       (=f (initial-top-edge-of-dragged-elevator
			     elevator-state)
			   (top-edge-of-dragged-elevator elevator-state)))
		  ;; We don't think the elevator moved.
		  (and (=f new-horizontal-position-of-block
			   old-horizontal-position-of-block)
		       (=f new-vertical-position-of-block
			   old-vertical-position-of-block)))
	  (move-elevator
	    block
	    new-horizontal-position-of-block
	    new-vertical-position-of-block)
	  (delta-position-of-block-scroll
	    block
	    image-plane
	    (-f new-horizontal-position-of-block
		old-horizontal-position-of-block)
	    (-f new-vertical-position-of-block
		old-vertical-position-of-block)))))
    (return-from-current-workstation-context 'elevator)))


(define-event-handler mouse-motion-in-elevator-state
    ((x-in-workspace x-in-workspace-of-selection-focus)
     (y-in-workspace y-in-workspace-of-selection-focus))
  (revisit-traveling-elevator nil nil x-in-workspace y-in-workspace))



;;; `Revisit-traveling-elevator' updates the elevator state and screen to
;;; to maintain the elevator as we are dragging it.  The flavors of call
;;; are supported: start dragging, move, end dragging are denoted by two
;;; booleans first-call? and last-call?.  The position of the mouse in the
;;; workspace is passed in, and then updated in the elevator state.

;;; The on screen ghost is maintained, either drawing it, erasing it, or both,
;;; via update-ghost.

(defun revisit-traveling-elevator (first-call?
				    last-call?
				    new-x-in-workspace
				    new-y-in-workspace)
  (with-mouse-pointer-bindings ((elevator-state workstation-context-specifics)
				(elevator-spot innermost-spot)
				image-plane)
      (mouse-pointer-of-last-down current-workstation)
    (let* ((last-elevator-position
	     (elevator-position-of-elevator-state elevator-state))
	   (new-elevator-position
	     (elevator-position-given-workspace-point
	       new-x-in-workspace
	       new-y-in-workspace))
	   (move-it?
	     (or (not (=f last-elevator-position new-elevator-position))
		 first-call?
		 last-call?))
	   (erase-it? (cond
			(first-call? nil)
			(last-call? t)
			(t move-it?)))
	   (draw-it? (if last-call? nil move-it?)))
      (when erase-it?
	;; XOR it off the screen
	(update-ghost-elevator 'black 'light-gray))
      (when move-it?
	(setf (elevator-position-of-elevator-state elevator-state)
	      new-elevator-position)
	(multiple-value-bind
	    (left-edge-of-ghost
	      top-edge-of-ghost
	      right-edge-of-ghost
	      bottom-edge-of-ghost) (edges-of-dragged-elevator)
	  (setf
	    (left-edge-of-dragged-elevator elevator-state) left-edge-of-ghost
	    (top-edge-of-dragged-elevator elevator-state) top-edge-of-ghost
	    (right-edge-of-dragged-elevator elevator-state) right-edge-of-ghost
	    (bottom-edge-of-dragged-elevator elevator-state)
	    bottom-edge-of-ghost)))
      (when draw-it?
	;; XOR it onto the screen
	(update-ghost-elevator 'light-gray 'black)))))


;;; `Update-ghost-elevator' changes the color of the ghost elevator.  It
;;; presumes that now current elevator state records where the elevator is.
;;; This is called to erase the elevator and to draw it.  I.e. two calls are
;;; done for each mouse motion with the elevator state being updated between
;;; them.

(defun update-ghost-elevator (from-color to-color)
  (with-mouse-pointer-bindings (image-plane
				 (elevator-state workstation-context-specifics))
      (mouse-pointer-of-last-down current-workstation)
    ;; Draw the ghost
    (change-color-in-rubber-stamp
      (workspace-on-image-plane? image-plane)
	(second (lookup-rubber-stamp-set-of-frame-widget
		  'gensym-scroll-bar-elevator-frame-component))
	(left-edge-of-dragged-elevator elevator-state)
	(top-edge-of-dragged-elevator elevator-state)
	(right-edge-of-dragged-elevator elevator-state)
	(bottom-edge-of-dragged-elevator elevator-state)
	'face-color from-color to-color)))



;;; `Edges-of-dragged-elevator' computes where current elevator state implies
;;; the elevator is being dragged to.  It presumes the edit state already has
;;; recorded the lastes mouse position (in workspace cooridinates) and it
;;; then maps that into a elevator postions (as a scale) and computes the
;;; edges using the same routine the scroll bar projection does.

(defun edges-of-dragged-elevator ()
  (with-mouse-pointer-bindings ((elevator-state workstation-context-specifics)
				(elevator-spot innermost-spot))
      (mouse-pointer-of-last-down current-workstation)
    (let* ((elevator-shaft-spot (enclosing-spot? elevator-spot)))
      (edges-of-elevator
	(orientation-of-shaft elevator-shaft-spot)
	(left-edge-of-scroll-bar-spot elevator-shaft-spot)
	(top-edge-of-scroll-bar-spot elevator-shaft-spot)
	(right-edge-of-scroll-bar-spot elevator-shaft-spot)
	(bottom-edge-of-scroll-bar-spot elevator-shaft-spot)
	(elevator-position-of-elevator-state elevator-state)))))



;;; `Elevator-position-given-workspace-point' returns just that (as a scale)
;;; relative to the shaft of the current elevator state given a point in the
;;; workspace containing it.

(defun elevator-position-given-workspace-point (x-in-workspace y-in-workspace)
  (with-mouse-pointer-bindings ((elevator-state workstation-context-specifics)
				(elevator-spot innermost-spot))
      (mouse-pointer-of-last-down current-workstation)
    (let* ((elevator-shaft-spot (enclosing-spot? elevator-spot))
	   (vertical?
	     (eq 'vertical
		 (orientation-of-shaft elevator-shaft-spot)))
	   (height (-f (bottom-edge-of-scroll-bar-spot elevator-shaft-spot)
		       (top-edge-of-scroll-bar-spot elevator-shaft-spot)
		       2))
	   (width (-f (right-edge-of-scroll-bar-spot elevator-shaft-spot)
		      (left-edge-of-scroll-bar-spot elevator-shaft-spot)
		      2))
	   (shaft-width (if vertical? width height))
	   (shaft-height (if vertical? height width))
	   ;; The current mouse, adjusted by some initial offset.
	   (x-in-workspace
	     (-f x-in-workspace
		 (x-offset-of-mouse-in-elevator-state elevator-state)))
	   (y-in-workspace
	     (-f y-in-workspace
		 (y-offset-of-mouse-in-elevator-state elevator-state)))
	   (pinned-offset
	     (cond
	       (vertical?
		(let* ((pin-y (pin-in-rangef
				(top-edge-of-scroll-bar-spot elevator-shaft-spot)
				y-in-workspace
				(-f (bottom-edge-of-scroll-bar-spot
				      elevator-shaft-spot)
				    shaft-width))))
		  (-f pin-y (top-edge-of-scroll-bar-spot elevator-shaft-spot))))
	       (t ;; horizontal
		(let* ((pin-x (pin-in-rangef
				(left-edge-of-scroll-bar-spot elevator-shaft-spot)
				x-in-workspace
				(-f (right-edge-of-scroll-bar-spot elevator-shaft-spot)
				    shaft-width))))
		  (-f pin-x (left-edge-of-scroll-bar-spot elevator-shaft-spot)))))))
      (position-of-elevator-as-scale-given-offset
	pinned-offset shaft-width shaft-height))))






#+TBD
(defun move-elevator-of-block (block orientation elevator-position)
  (multiple-value-bind (left-edge-of-new-elevator
			 top-edge-of-new-elevator
			 right-edge-of-new-elevator
			 bottom-edge-of-new-elevator)
      (edges-of-elevator block orientation elevator-position)
    (let ((workspace? (workspace-of-block? block)))
      (macrolet ((update-elevator-areas (erase?)
		   `(progn
		      ;; Update the area with the old elevator position
		      (when workspace?
			(update-images
			  ,erase? block workspace?
			  (left-edge-of-scroll-bar-spot elevator-spot)
			  (top-edge-of-scroll-bar-spot elevator-spot)
			  (+f (right-edge-of-scroll-bar-spot elevator-spot) 1)
			  (+f (bottom-edge-of-scroll-bar-spot elevator-spot) 1)
			  :no-bleeding
			  'draw-block
			  block)
			;; Update the area with the new elevator position
			(update-images
			  ,erase? block workspace?
			  left-edge-of-new-elevator
			  top-edge-of-new-elevator
			  (+f right-edge-of-new-elevator 1)
			  (+f bottom-edge-of-new-elevator 1)
			  :no-bleeding
			  'draw-block
			  block)))))
	(update-elevator-areas t)
	;; Revise the document state for the elevator.
	(setf (position-of-vertical-elevator block)
	      elevator-position)
	(update-elevator-areas nil)))))

;; Where is this getting the shaft shape? Just Trouble!
;; It wants an elevator shaft spot!

;; But I need this to keep the elevator in synch when the editor
;; scrolls for other reasons...



;;;; Selection State


;; Somebody should break up this party!
;; Party's over, man.


;;; The function `distance-from-point-to-table' returns the distance from the
;;; given point (in window coordinates) to the interior of the table on the
;;; given image-plane.  The distance is based on a rectangular metric, and is 0
;;; anywhere strictly within the table.  It is non-zero inside the borders of
;;; the table.

(defun distance-from-point-to-table (x y table image-plane)
  (maxr 0
	(- (x-in-frame-transform
	     (+w (left-edge-of-block table)
		 (table-left-border-width (table-format table)))
	     (workspace-on-image-plane? image-plane)
	     image-plane)
	   x)
	(- (y-in-frame-transform
	     (+w (top-edge-of-block table)
		 (table-top-border-width (table-format table)))
	     (workspace-on-image-plane? image-plane)
	     image-plane)
	   y)
	(- x
	   (x-in-frame-transform
	     (+w (right-edge-of-block table)
			    (table-right-border-width (table-format table)))
	     (workspace-on-image-plane? image-plane)
	     image-plane))
	(- y
	   (y-in-frame-transform
	     (+w (bottom-edge-of-block table)
			    (table-bottom-border-width (table-format table)))
	     (workspace-on-image-plane? image-plane)
	     image-plane))))





;;; The function `mouse-was-dragged-p', given a mouse-motion event, returns T
;;; if we've moved far enough from the original position to call it a drag.
;;; This behavior maybe tuned with these compile time parameters:

;;;   `minimum-distance-to-move-mouse-to-be-dragging',
;;;   `overshoot-distance-around-menus-before-beginning-dragging' and
;;;   `minimum-time-that-must-pass-to-be-dragging'.

;;; At present, this is true if all of the following are true:
;;;
;;;  (1) n microseconds have elapsed between the time of the selection and
;;;      this selection event, where n is given by the parameter minimum-
;;;      time-that-must-pass-to-be-dragging OR the mouse position recorded
;;;      in the current workstation differs in X or Y from the original X or
;;;      Y position at the time the selection was selected by more than an
;;;      "epsilon" (in pixels), where epsilon is givent by the parameter
;;;      minimum-distance-to-move-mouse-to-be-dragging; and
;;;
;;;  (2) the current-selection-can-move? slot of the current selection state
;;;      variable is true;
;;;
;;;  (3) if the selection is a menu, the mouse has moved out of the menu table
;;;      by overshoot-distance-around-menus-before-beginning-dragging window
;;;      units; if the selection is not a menu, this condition does not apply.

;;; Condition (1) helps to ensure that what the user intended to be a click does
;;; not get interpreted as a press-drag-release, which could easily happen, for
;;; example, if the user were to start moving down to the some anticipated position
;;; of a desired menu item before releasing.  It just has to a short enough time
;;; so that the click case is not confused with (very quickly) pressing, dragging,
;;; and releasing.  A good default for this seems to be 100.

;;; To do the test for condition 1, the timestamp of the selection event is compared
;;; to the value of the special variable time-of-current-selection.

(defparameter minimum-distance-to-move-mouse-to-be-dragging 3)

;; Experiment with this!  Zero was especially poor in the editor, where it went into
;; a marking context without giving any feed back of that.  Then it would would look
;; like it had just missed a click.  (Was 10 in 1.11.) (MHD 6/21/89) -- 3, what's
;; currently used, is very poor for dragging, especially for find positioning.  It
;; makes dragging look sluggish also, for quick drags, since it appears that it
;; delays for time it takes to drag 3 pixels whereas it really is just trying to be
;; "helpful".  The Mac seems to use 0.  The Sparc (with Open Look) seems to use 3.
;; Probably, the editor marking vs.  cursor movement decision parameter should be
;; separated out from the dragging object vs.  putting up menu decision if that's
;; what's keeping the latter unreasonable.  Note that the Mac doesn't have this
;; problem in the editing case, since it moves the cursor to the mouse down point
;; immediately, whereas we only do so if there is to be a cut or delete.  Another
;; important flaw with this with the editor is that if you start off, say, on the
;; right edge of a one pixel wide charater, and want to just mark that character, you
;; still have to drag left 3 pixels just to get the marked region to show up over
;; your character.  At that point, in fact, it might have gone over to the next
;; character over even, which is more than you wanted.  It's also then inconsistent
;; with what happens if you go back to your mouse-down point and drag again: in that
;; case, you only need to drag 1 pixel to get the mark to show up.  (MHD 5/7/92)


(defparameter minimum-time-that-must-pass-to-be-dragging 1000)	; a fixnum, milliseconds

(defparameter overshoot-distance-around-menus-before-beginning-dragging 50)
						; in window units

(defun mouse-was-dragged-p (spot motion-event original-x original-y original-timestamp)
  (let ((cursor-x (workstation-event-cursor-x motion-event))
	(cursor-y (workstation-event-cursor-y motion-event))
	(timestamp (workstation-event-timestamp motion-event))
	(minimum-distance (if (loose-end-spot-p spot)
			      0				    ; Make loose-ends easy to pick up.
			      minimum-distance-to-move-mouse-to-be-dragging)))
    (or (>f (event-time-difference timestamp original-timestamp)
	    minimum-time-that-must-pass-to-be-dragging)
	(>r (absr (-r cursor-x original-x))
	    minimum-distance)
	(>r (absr (-r cursor-y original-y))
	    minimum-distance))))

;; The time difference test are wrong for telewindows connections.  Event timestamps
;; are in the units of the remote telewindows, and we are comparing them as if
;; they are in local time units.  -fmw, 9/13/94

;; That is now fixed. Event times are always in milliseconds. -fmw, 10/12/94


;; When the selection is a pop-up menu, this should return non-nil (but does not at
;; present!) only once the mouse is dragged off of the menu, and furthermore not until
;; dragged off by the same perhaps by the same epsilon.

;; See if the 100 millisecond default for minimum-time-that-must-pass-to-be-dragging
;; is good in all implementations!!

;; Currently, time is taken into account only in distinguising a "rolling click" (with
;; the mouse moving in between the down and upstroke) and a very quick press-drag-release
;; action.  However, this can result in it getting wedged if the mouse suddenly stops
;; after having been moved during the minimum time period.  At this point, a mouse-still-
;; down event is needed to wake it up! Notice that moving it a little (causing a mouse-
;; motion event) unwedges it also.  THIS MUST BE FIXED!

;; The decision should also be able to take into account the passage of time.  I.e.
;; It should be possible to have the decision to move be made because the mouse was
;; held down for a long time, meaning that there was no "click", so consider it instead
;; a "drag", even though we haven't moved (enough) yet.  Note, however, that this
;; involves coding in another place, namely service workstations, since this test is
;; only performed whenever a workstation event happens.  OR: there may want to be a MOUSE-
;; STILL-DOWN selection event; then this test could be done here (using the timestamps
;; that come with the events).




;;; The function `menu-choice-cell-p' is true if the cell is a choice cell of a menu,
;;; as opposed to the title cell.

(defun menu-choice-cell-p (cell?)
  (and cell?
       (cell-is-text-cell-p cell?)
       (getf (text-cell-plist cell?) 'choice)))




;;; The function `auto-insert-text-from-block' inserts TEXT into the current
;;; editor, where the text originally came from BLOCK.  It sometimes flashes the
;;; source block, by way of feedback.

(defun auto-insert-text-from-block (text block)
  (let* (;; Flash name boxes or scraps (not if already highlighted; reverse
	 ;; highlight in this case?)
	 (flash?
	   (and (frame-of-class-p block 'name-box)
		(null (getf (text-cell-plist-for-text-box block) 'highlight-color))))
	 ;; the following 2 do not apply in kfep-conversion-choice-menu
	 ;; The following 2 should also be GF's on the block, or, stored on all objects
	 ;; in a lookup-slot or in the object-configuration.
	 (replace-fragments-on-sides?
	   (frame-class-case block
	     ((scrap token-menu)	; generic slot
	      (get-slot-value block 'replace-fragments-on-sides?))
	     (name-box
	       t)
	     (table
	       ;; For attribute descripton as text inserter in
	       ;; attribute table case.  (MHD 12/18/91)
	       t)))
	 (handle-spaces-intelligently?
	   (handle-spaces-intelligently-p block))
	 (replace-entire-text?
	   (frame-class-case block
	     ((token-menu scrap)	; generic slot
	      (get-slot-value block 'replace-entire-text?))))
	 (block-reference-serial-number
	   (copy-frame-serial-number (frame-serial-number block))))

    (when flash?
      (highlight-or-unhighlight-text-box block nil nil))
    
; Never in editing, only invoked from selection state.
;    (when (and (eq type-of-current-workstation-context 'editing)
;               (eq (workstation-context-return-information current-workstation-context)
;                   image-plane-for-current-selection?))
;      (exit-current-workstation-context))

    ;; Insert the string.
    (frame-class-case block
      (kfep-conversion-choice-menu
	(do-kfep-conversion-edit-from-outside text))
      (pathname-component-token-menu
	(insert-text-string-at-cursor-from-outside	; (may delete token menu)
	  text
	  replace-fragments-on-sides?
	  handle-spaces-intelligently?
	  replace-entire-text?
	  'pathname-component-conversion))
      (t
	(insert-text-string-at-cursor-from-outside	; (may delete token menu)
	  text
	  replace-fragments-on-sides?
	  handle-spaces-intelligently?
	  replace-entire-text?)))
    (reclaim-text-string text)
    (unless (frame-has-been-reprocessed-p
	      block block-reference-serial-number)
      (when (and (frame-of-class-p block 'token-menu)
		 ;; in token menu case, deletes category instance menu
		 ;;   workspace holding the menu when the menu is all
		 ;;   alone thereon.  Thus, users can name the workspace
		 ;;   to cause it to stick around (a documented feature).
		 ;;   But note that the following test also distinguishes
		 ;;   it from a menu on the edit workspace.
		 (has-only-one-subblock-p (superblock? block)))
	(setq flash? nil)
	(delete-frame (superblock? block)))
      (when flash?
	(highlight-or-unhighlight-text-box block nil t)))
    (reclaim-frame-serial-number block-reference-serial-number)))


;;;; Native Menus


;;; A native menu is a native menu on telewindows only, for now.  Soon this will
;;; have to be generalized to any native control/widget/whatever, and for local
;;; windows, too.


;;; The function `allocate-menu-handle' allocates a menu handle, which is a
;;; small integer that we can fit into a key-code, for the given menu, and
;;; records the associated top-level menu handle.

(defun allocate-menu-handle (gensym-window menu top-level-menu-handle?)
  (let ((native-menu-table (native-menu-table gensym-window)))
    (loop for i from 1 below (managed-array-length native-menu-table)
	  as entry? = (managed-svref native-menu-table i)
	  doing
      (when (null entry?)
	(let* ((menu-snap (make-snapshot-of-block menu))
	       (top-handle (or top-level-menu-handle? i))
	       (entry (slot-value-list menu-snap top-handle)))
	  (setf (managed-svref native-menu-table i) entry)
	  (return i))))))

;; We skip the zero handle here.  Maybe it will indicate the main menu.


;;; The function `set-menu-handle-info' is used to add the total tree of menus
;;; items to the top-level menu's entry.  We keep it around mostly so that we
;;; can reclaim it (in execute-native-menu-choice).

(defun set-menu-handle-info (gensym-window handle info)
  (let* ((native-menu-table (native-menu-table gensym-window))
	 (entry? (managed-svref native-menu-table handle)))
    (when entry?
      (nconc entry? (slot-value-list info)))
    entry?))


;;; The function `lookup-menu-handle' returns the top-level-menu-handle and the
;;; submenu object associated with the handle, and the top-level item list, when
;;; the handle is for the top-level menu, as three values.

(defun lookup-menu-handle (gensym-window handle)
  (let* ((native-menu-table (native-menu-table gensym-window))
	 (entry? (managed-svref native-menu-table handle)))
    (when entry?
      (let ((menu-snap (first entry?))
	    (top-handle (second entry?))
	    (items (third entry?)))
	(values (and (snapshot-of-block-valid-p menu-snap)
		     (block-of-snapshot menu-snap))
		top-handle
		items)))))


;;; The function `reclaim-menu-handle' reclaims the table entry, the menu
;;; instance, and the items tree if this was the top-level menu.

(defun reclaim-menu-handle (gensym-window handle)
  (reclaim-menu-handle-1 (native-menu-table gensym-window) handle))

(defun reclaim-menu-handle-1 (native-menu-table handle)
  (let ((entry? (managed-svref native-menu-table handle)))
    (when entry?
      (let ((menu-snap (first entry?))
	    (top-handle (second entry?))
	    (items (third entry?)))

	(when (snapshot-of-block-valid-p menu-snap)
	  (delete-menu (block-of-snapshot menu-snap)))
	
	(reclaim-snapshot-of-block menu-snap)
	(reclaim-slot-value-list entry?) ; Just the spine, not the items tree.
	(when (eql handle top-handle)	; Reclaim item tree if we're the top menu.
	  (reclaim-gensym-tree items))
	(setf (managed-svref native-menu-table handle) nil)))))


;;; The function `reclaim-contents-of-native-menu-table' completely reclaims the
;;; contents of the native-menu-table.  This is used only when the corresponding
;;; gensym-window is being reclaimed.

(defun reclaim-contents-of-native-menu-table (native-menu-table)
  (loop for i from 1 below (managed-array-length native-menu-table) doing
    (reclaim-menu-handle-1 native-menu-table i)))


;;; The parameter `standard-remote-submenu-depth' defines the maximum depth of a
;;; tree of native menus.  Since the G2 class menu can be arbitrarily deep, and
;;; we must pass the entire menu tree over the wire in advance for Win32, we
;;; must limit the depth to a reasonable number.

(defparameter standard-remote-submenu-depth 5)

;; This may be worth putting into the menu-parameters system table.
;; It could apply to classic G2 menus, also.


;;; The function `expose-menu-remotely' is called from expose-menu when we want to
;;; post a native menu on a remote telewindow.

(defun expose-menu-remotely (gensym-window menu x y)
  (gensym-assert (and x y))
  (let* ((handle (allocate-menu-handle gensym-window menu nil))
	 (items (extract-menu-item-list-from-menu
		  gensym-window handle menu standard-remote-submenu-depth)))
    (set-menu-handle-info gensym-window handle items)
    (send-icp-post-native-menu current-workstation-window handle x y items)))

;; All this stuff is finally reclaimed in execute-native-menu-choice, or
;; when the gensym-window is reclaimed.
;; Should be called expose-menu-natively


(defun length-of-longest-row (table)
  (loop for row in (table-rows table)
	maximize (length row)))


;;; The recursive function `extract-menu-item-list-from-menu' returns a newly
;;; consed gensym tree of the items in the menu, in the format that remote
;;; native menus wants.  It may create submenu frames during recursion.

;;; The returned item list is a tree of gensyms conses, symbols, and strings.
;;; The strings are shared with the menu instance and should not be reclaimed
;;; with the tree!

;; The order must match that in menu-choice-text-cell-for-item-number.

(defun extract-menu-item-list-from-menu (gensym-window top-level-menu-handle
						       menu &optional (max-depth 0))
  ;; We return items in column-major order, since that's what Win32 wants.
  (loop for column from 0 below (length-of-longest-row menu)
	as column-items =
	(loop for row in (table-rows menu)
	      as cell? = (nth column row)
	      as string? = (and (cell-is-text-cell-p cell?)
				;; FIXME We should be calling convert-text-to-text-string here.
				;; Note that that function conses a new string.
				(loop for piece in (text? cell?)
				      when (text-string-p piece)
					return piece))
	      as item? = 
	      (when (and string? (menu-choice-cell-p cell?))
		(let* ((fmt (text-cell-format cell?))
		       (plist (text-cell-plist cell?))
		       (fg (getf plist 'line-color))
		       (bg (getf plist 'background-color))
		       (submenu? nil)
		       ;; choice is a partial command or an argument value.
		       (choice (menu-cell-menu-choice cell?)))
		  (cond ((menu-item-format-is-cascade-p fmt)
			 (cond ((<=f max-depth 0)
				(gensym-list 'submenu string?))
			       ((null (setq submenu? (create-submenu menu choice
								     ;; Possibly not the right
								     ;; mouse pointer here.
								     (menu-mouse-pointer menu))))
				;; We MUST return a menu item here; otherwise,
				;; item offsets will be out of sync.
				(gensym-list 'submenu string?))
			       (t
				(let ((submenu-handle (allocate-menu-handle
							gensym-window
							submenu? top-level-menu-handle)))
				  ;; Ensure that the submenu frame gets reclaimed
				  ;; when the top-level menu is.  Need since TW
				  ;; sends back just the handle to the top-level
				  ;; menu, the submenus would otherwise be hard to
				  ;; find. -fmw, 1/17/02
				  (ensure-that-menu-item-will-be-reclaimed menu submenu?)
				  (nconc
				    (gensym-list 'submenu string? submenu-handle)
				    (extract-menu-item-list-from-menu
				      gensym-window
				      top-level-menu-handle
				      submenu? (1-f max-depth)))))))
			((or fg bg)
			 (gensym-list 'color string? fg bg))
			(t
			 string?))))
	      when item? collect it using gensym-cons)
	when (and items column-items)
	  collect menu-break-marker into items using gensym-cons
	nconc column-items into items
	finally
	  (return items)))


;;; The function `reclaim-menu-handles-item-tree' reclaims all of the submenu
;;; handles found in the tree of items.  A side-effect of reclaiming a handle is
;;; to reclaim the menu, too.

(defun reclaim-menu-handles-in-item-tree (gensym-window items)
  (loop for item in items
	as submenu-handle? = (and (consp item)
				  (eq (first item) 'submenu)
				  (third item))
	doing
    (when submenu-handle?
      (reclaim-menu-handle gensym-window submenu-handle?)
      (reclaim-menu-handles-in-item-tree gensym-window (cdddr item)))))


;;; The function `menu-item-format-is-cascade-p' returns T if the given
;;; menu-item-format draws the little triangle.

(defun menu-item-format-is-cascade-p (menu-item-format)
  (let ((name (car-or-atom (name-or-names-for-frame menu-item-format))))
    (memq name '(left-aligned-cascade-menu-item-format
		 center-aligned-cascade-menu-item-format
		 right-aligned-cascade-menu-item-format
		 left-aligned-cascade-menu-item-format-new-large
		 center-aligned-cascade-menu-item-format-new-large
		 right-aligned-cascade-menu-item-format-new-large
		 left-aligned-cascade-menu-item-format-new-small
		 center-aligned-cascade-menu-item-format-new-small
		 right-aligned-cascade-menu-item-format-new-small))))
;; A hack.  Could grovel in post-draw-methods-for-text-box-formats instead.


;;; The event-handler `execute-native-menu-choice' executes a menu choice made
;;; on a remote TW.  TW sends a special menu-choice key-code to us containing
;;; the handle of the menu in which the choice was made, and the item-number in
;;; that menu.

(define-event-handler execute-native-menu-choice ((gensym-window window)
						  key-code x-in-window y-in-window
						  &optional event-plist)
  (let* ((menu-handle (or (getf event-plist 'menu-handle)
			  (key-code-menu-number key-code))) ; Remove after 7.0 alpha
	 (item-number (or (getf event-plist 'item-number)
			  (key-code-item-number key-code)))) ; Remove after 7.0 alpha

    (multiple-value-bind (menu? top-level-menu-handle)
	(lookup-menu-handle gensym-window menu-handle)
      
      (when menu?
	(when (>f item-number 0)	; item-number 0 means user made no choice.
	  (let ((cell? (menu-choice-text-cell-for-item-number menu? item-number)))
	    (when cell?
	      (execute-menu-choice-1 menu? cell? x-in-window y-in-window t))))

	;; Now reclaim everything associated with the menu tree of which menu is
	;; part.  We do this by looking up the top-level menu to get the
	;; complete item tree, reclaiming all the submenus found in that tree,
	;; and finally reclaiming the top-level menu.
	(multiple-value-bind (top-menu top-handle top-level-items)
	    (lookup-menu-handle gensym-window top-level-menu-handle)
	  (declare (ignore top-menu top-handle))

	  ;; This all the submenus.
	  (reclaim-menu-handles-in-item-tree gensym-window top-level-items)

	  ;; This gets the top-level menu and the items.
	  (reclaim-menu-handle gensym-window top-level-menu-handle))))))


;; item-number is 1-origin and counts from top-to-bottom and then left-to-right
;; in the menu table (column-major order).  The order must match that in
;; extract-menu-item-list-from-menu.

(defun menu-choice-text-cell-for-item-number (menu item-number)
  (let ((index 1))
    (block search
      (loop for column from 0 below (length-of-longest-row menu) doing
	(loop for row in (table-rows menu)
	      as cell? = (nth column row)
	      doing
	  (when (menu-choice-cell-p cell?)
	    (when (=f item-number index)
	      (return-from search cell?))
	    (incff index)))))))
		     

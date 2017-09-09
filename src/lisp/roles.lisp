;;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ROLES  

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin, Jim Allard




;;; In CONTROLS

(declare-forward-reference get-block-on-workspace-for-frame function)

;;; In PROC-UTILS

(declare-forward-reference get-specific-methods-for-class-or-superior-class
			   function)

;;; In EVAL

(declare-forward-reference evaluate-designation function)
(declare-forward-reference print-role function)
(declare-forward-reference print-designation function)

;;; in FILTERS

(declare-forward-reference attribute-is-visible-via-the-text-of-p function)

;;; In INSTALL
(declare-forward-reference focal-entity-for-simulation-formula variable)
(declare-forward-reference get-focal-entity-for-simulation-formula? variable)

;;; In PROC-UTILS

(declare-forward-reference
  get-current-procedure-invocation-frame-if-any function)
(declare-forward-reference
  write-stored-value function)

;; In STACK-INST

(declare-forward-reference get-next-specific-method function)

(declare-forward-reference role-returned-no-values-error-1 function)

;; In GRAMMAR6

(declare-forward-reference write-expression function)

;; In GRAMMAR7

(declare-forward-reference first-value-ok-for-the-named-by-grammar-p function)

;;; In CONTROLS

(declare-forward-reference serve-this-window function)
(declare-forward-reference rule-is-embedded-p function)

;;; In ATTR-EXPORT

(declare-forward-reference
  get-list-of-all-user-visible-attributes function)

;; To Do

;; Make some of the role server functions for connections be macros
;; (see notes in role servers for connections section).  - agh

;; Currently, "at the output end of" rather than "connected at the output
;; end of" is used.  Allow both?






;;;; Definitions for roles




;;; A role is a name representing a unary, binary, or ternary relation. 
;;; Role grammar in G2 uses phrases such as:

;;; 	[the] temperature of [the furnace]    TEMPERATURE    	    attribute
;;; 	[any] valve connected to [furnace-1]  (CONNECTED-TO VALVE)  connected
;;;	      object of class
;;; etc.

;;; The role itself never has anything in it that requires evaluation. It may
;;; contain attribute names, class names, port names, etc.

;;; The treatment of roles is abstract because the variety of them is
;;; open-ended.  The method of dealing with a role is determined at the time
;;; that it is evaluated because no assumption can be made that the definition
;;; is available at compile time, that the definition might not change, or that
;;; the instances of relatedness might not change.  This does not preclude
;;; certain amounts of compilation with built in assumptions being made at some
;;; time for some applications for reasons of efficiency.

;;; The function `serve-first-value-of-role' is used to request the first (and
;;; sometimes the only) value of the role.  Currently roles can take zero, one,
;;; or two arguments, called domains.

;;; Role serving requires three values be returned.

;;; (1) The value if any or nil if there is none. But nil is also a possible
;;; value of a role server. (2) A continuation if there is a possibility of
;;; obtaining further values, and nil if there is not. (3) An expiration if a
;;; value is supplied, otherwise nil. The default expiration is 'never. Nil as a
;;; third value means that no value is being served. and is the proper test for
;;; this.

;;; When the last value is served, the continuation will be NIL. It is possible
;;; to have a non-null continuation, but when more values are asked for, there
;;; are not any.  This could happen, for example, if a frame that was going to
;;; be served has been deleted. However, it is not permitted for a role server
;;; to return a continuation and not to provide a value at the same time.

;;; The (first) value of a role server must be a frame, evaluation-value or nil.
;;; If it is an evaluation-value, then it is the responsibility of the caller to
;;; reclaim it.

;;; To get successive values of the role after the first, the requestor of
;;; service calls the function `serve-next-item-or-evaluation-value-of-role'. The values will be
;;; the same as for serve-first-value-of-role.

;;; In case the requestor chooses not to accept further values when a
;;; continuation has been supplied, it is required to execute
;;; `close-role-value-server'. This may be needed by the role server to reclaim
;;; data structures. When the role server has not supplied a continuation, then
;;; it must not be closed because it has closed itself already.

;;; The method of dispatching role service is limited by the fact that
;;; no assumption can be made at compile time concerning a role.

;;; Service is initialized by serve-first-value-of-role which must examine the
;;; role as follows: (1) Determine whether the role is the name of an attribute,
;;; and if the given entity has that attribute. If so get the value. If the
;;; attribute is multivalued, a continuation is required. (2) Determine whether
;;; the role is the name of a class, and if so enumerate the entities of that
;;; class that are "connected" to the given entity, or if the domain is nil then
;;; enumerate the class instances, (3) look for a global property
;;; role-server of the role which will be a function that takes the same two
;;; arguments as serve-first-value-of-role. (It needs the role-name because the
;;; function is not necessarily specific to that role, but may serve a
;;; collection of roles.) The property role-server will belong to the role if
;;; a symbol, and to car of the role if a cons.

;;; A continuation will always be a cons whose car is the name of a function and
;;; whose cdr is data for the function. The function should take two arguments.
;;; The first is t if this is a request to continue and nil if it is a request
;;; to close.  The second argument is the continuation itself.  Note that this
;;; function is never invoked to start service, but only to continue or close
;;; it. It is not the same as the function which is the property role-server.

;;; The function `serve-first-value-of-role-inverse' is used to compute
;;; backwards from a value returned from a role to the arguments of that role
;;; that might have produced the given result.

;;; It is a requirement of both forward and backward chaining to compute the
;;; inverse of the function indicated by a role, given an object which was
;;; returned by a service of that role.  For this purpose, we specify
;;; serve-first-value-of-role-inverse.  There are many cases where this is not
;;; possible.  But it is important to be able to compute the entity of which
;;; this entity is a slot value, and the entity of which this entity (of given
;;; type) is "connected".  This function will serve entities which could have
;;; served the given entity using the given role.  These served entities are
;;; filtered as much as is possible using the role of the given domain
;;; designation, however some entities may be served which would not have been
;;; in the forward service of this total designation.  This may occur since the
;;; domain of the passed domain designation may denote no objects which serve
;;; some of the objects accessible through reverse service.  The users of this
;;; facility should take care to serve a total chain of the inverse of any given
;;; designation before using any incremental results of an inverse chain.

;;; The continuation and closing work the same way as for forward role serving.
;;; Inverse role servers are defined with def-role-inverse .

;;; The function `value-of-role-p' is used to validate that a given value is a
;;; possible value of the given quantifier, role, and domain value.  By default
;;; this function will iterate over the role values, checking if the given value
;;; is one of the served values.  However, if a predicate function has been
;;; declared for the role with `def-role-predicate', this function will be
;;; called with the same arguments as were passed to this function, and its
;;; value will be returned.

;;; Roles are defined with `def-role', `def-role-printer', `def-role-inverse',
;;; `def-unique-value-of-role-server', and `def-role-predicate'.  See each of
;;; these functions for specific documentation.  Def-role defines the default
;;; function that produces values given invocations of this rule.
;;; Def-role-printer defines how print-role will print it.  Def-role-inverse
;;; defines how to traverse this role in the opposite direction, getting the
;;; possible arguments for a role given the values produced by it.  These
;;; so-called `inverse role servers' are used when pattern matching in rules.
;;; Def-unique-value-of-role-server is an optimization of the def-role form for
;;; the common case where a role is being evaluated for one and only one value.
;;; Def-role-predicate is an optimization of the def-role form for use in
;;; value-of-role-p.



;; The following documentation should be moved down near the defining functions.
;; -jra 8/5/96


;;; When accessing a slot value which is a parameter, its value and type must be
;;; copied into a temporary-constant. Note that this is true for numbers and
;;; truth-values. The value of an attribute may also be a symbol (which stands
;;; for itself) a number or a frame.



;;; The following roles are defined (see also the Summary Of Roles section):

;;; Name, named-by, nearest, icon-color, item-color, icon-x-position,
;;; icon-y-position, icon-heading, icon-width, icon-height, system-attribute,
;;; system-attribute-as-text, connected-to, at-port, at-an-input, at-an-output,
;;; at-input-end, at-output-end, at-either-end, subworkspace, superior-item,
;;; attribute-of-class, workspace, upon, named, this-workspace, this-window,
;;; this-rule, this-procedure, this-procedure-invocation, related,
;;; first-of-list, second-of-list, next-to-last-of-list, last-of-list,
;;; list-iterator, nth-element, var-spot, attribute-value.

;;; Cases where the role is an attribute name or class name are handled
;;; specially by serve-first-value-of-role.

;;; The following roles are not included in the simulation grammar:

;;; name named-by icon-color item-color
;;; icon-x-position icon-y-position icon-heading icon-width icon-height
;;; etc... need to update.  cpm, 4/24/91.






;;;; Role Conses




;;; At the current time the eval cons pool is used for role service.  Since this
;;; pool is already overused, we are introducing a new pool, role-cons.  This
;;; will be first used for the conses in the containing structure for role
;;; caching, though not for the actual cached list of frames.  Currently all
;;; lists of role values are made of eval conses, and this is built into the
;;; functions which produce these lists of role values.  When we can get to it
;;; this should be changed such that all conses will be role conses in this
;;; facility.  -jra 8/31/88


(defconser role roles)






;;;; Role Interfaces




;;; The following properties and macros are used for containing role server
;;; mappings and for calling role service.


(def-global-property-name role-server)

(def-global-property-name defined-type-of-role)

(def-global-property-name inverse-role-server)

(def-global-property-name role-server-printer)

(def-global-property-name role-and-designation-printer)

(defmacro role-server-exists-p (symbol)
  `(role-server ,symbol))

(def-substitution-macro serve-next-item-or-evaluation-value-of-role (continuation)
  (assert-for-development
    (framep *current-computation-frame*)
    "Serve-next-item-or-evaluation-value-of-role called without ~
     *current-computation-frame* bound to a frame.")
  (assert-for-development
    (or (compiled-function-p (car continuation))
	;; when set a breakpoint in a compiled function,following form is necessary.
	#+(and lispworks (not chestnut3))
	(system:interpreted-function-p (car continuation)))
    "Continuation didn't contain a compiled function, ~a."
    continuation)
  (funcall-simple-multi-valued-compiled-function
    (car-of-cons continuation) t continuation))

(defun serve-next-item-or-temporary-constant-of-role (continuation)
  (multiple-value-bind (value? next-continuation expiration?)
      (serve-next-item-or-evaluation-value-of-role continuation)
    (when (and expiration?
	       (evaluation-value-p value?))
      (setq value? (transform-evaluation-value-into-temporary-constant value?)))
    (values value? next-continuation expiration?)))

(def-substitution-macro close-role-value-server (continuation)
  (assert-for-development
    (or (compiled-function-p (car continuation))
	;; when set a breakpoint in a compiled function,following form is necessary.
	#+(and lispworks (not chestnut3))
	(system:interpreted-function-p (car continuation)))
    "Continuation didn't contain a compiled function, ~a."
    continuation)
  (funcall-simple-multi-valued-compiled-function
    (car-of-cons continuation) nil continuation))




;;; The function reclaim-evaluation-iteration-state has been moved here from
;;; SETS to pick up the close-role-value-server macro.  -jra 4/13/91

(defun reclaim-evaluation-iteration-state (evaluation-iteration-state)
  (let* ((reference-cons (car-of-cons evaluation-iteration-state))
	 (reference-count (car-of-cons reference-cons)))
    (declare (type fixnum reference-count))
    (if (=f reference-count 1)
	(let ((continuation? (cdr-of-cons reference-cons)))
	  (when continuation?
	    (close-role-value-server continuation?))
	  (reclaim-eval-cons-macro reference-cons)
	  (reclaim-eval-cons-macro evaluation-iteration-state))
	(setf (car-of-cons reference-cons) (-f reference-count 1)))
    nil))

(defun close-evaluation-iteration-state-continuation
       (evaluation-iteration-state)
  (let* ((reference-cons (car-of-cons evaluation-iteration-state))
	 (continuation? (cdr-of-cons reference-cons)))
    (when continuation?
      (close-role-value-server continuation?)
      (setf (cdr-of-cons reference-cons) nil))
    nil))




;;; The macro `def-role' defines the functions that provide values for
;;; executions of a role.  It's argument syntax is like defun, except that
;;; instead of just the name, you may optionally provide a form that describes
;;; that argument and return value types.  The first argument to def-role is the
;;; role name or specification.  The second argument of def-role is the argument
;;; list of the role server function, and the remainder is the body of the role
;;; server function.  The role spec is either the role-name symbol, or a list of
;;; the role-name symbol, the result type-specification, and a list of argument
;;; type-specifications.  The following is an example of a role definition.

;;;   (def-role (item-height integer ((class item))) (role domain)
;;;     (declare (ignore role))
;;;     (values (make-evaluation-integer (item-height domain)) nil 'never))

;;; The parser produces role forms that are passed through to the compiler, for
;;; example:

;;;   (THE <attr-name> <item>)
;;;   (THE (CONNECTED-TO <class>) <item>)

;;; There is a special case for determining the result types of many roles.  If
;;; the role is a list (such as the CONNECTED-TO example) and the result-type in
;;; the role-spec is NIL, then the car of the last of the role list will be used
;;; as a user-type type-specification for the values produced by the role (see
;;; user-type-to-type-specification to understand what user-type means).  In
;;; these cases, the body of the def-role needs to ensure that it only returns
;;; values of the given type, and the compiler may compile-in assumptions that
;;; only values of that type will be returned.  The default result type is
;;; item-or-datum.  The default required type list for domains of roles is the
;;; list ((class item))

(defmacro def-role (name-or-role-specification argument-list &body forms)
  (let* ((role-specification (if (symbolp name-or-role-specification)
				 (list name-or-role-specification)
				 name-or-role-specification))
	 (role-name (first role-specification))
	 (type-of-role? (second role-specification))
	 (domain-types (if (cddr role-specification)
			   (third role-specification)
			   '((class item))))
	 (domain-count (length domain-types))
	 (argument-count (length argument-list))
	 (server-name (intern (format nil "SERVE-FIRST-~a" role-name))))
    (unless (= (+ (max domain-count 1) 1) argument-count)
      (warn "Domain types for role ~a don't match argument list length."
	    role-name))
    `(progn
       (defun-into-place (,server-name (role-server ',role-name))
	   ,argument-list
	 ,@forms)
       ,@(when type-of-role?
	   `((setf (defined-type-of-role ',role-name) ',type-of-role?)))
       (setf (required-domain-types-of-role ',role-name) ',domain-types)
       ;; The following line may seem stupid, but it keeps the role
       ;; server property on the front of the property list, instead of
       ;; being buried by the inverse role server.  -jra 5/8/91
       (when (null (inverse-role-server ',role-name))
	 (setf (inverse-role-server ',role-name) nil))
       ',role-name)))



;;; The macro `def-role-inverse' defines inverse servers for roles.  The first
;;; argument to def-role-inverse is the name of the role to invert, the second
;;; is the argument list of the role inverter function, and the remainder of the
;;; arguments are the body of the inverse role server function.

;; See an example of an inverse role server for the appropriate number and order
;; of elements of the inverse server argument list.  -jra 8/5/96

(defmacro def-role-inverse (name argument-list &body forms)
  (let ((inverse-name (intern (format nil "SERVE-FIRST-~a-INVERSE" name))))
    `(progn
       (defun-into-place (,inverse-name (inverse-role-server ',name))
	   ,argument-list
	 ,@forms)
       'name)))

(defmacro def-role-printer (role-name &body forms)
  (let ((printer-name (intern (format nil "ROLE-PRINT-~a" role-name))))
    `(progn
       (defun-simple-into-place
	   (,printer-name (role-server-printer ',role-name))
	   (role local-variable?)
	 ,@forms)
       ',printer-name)))

(defun print-role-whose-car-is-role-server (role local-variable?)
  (princ-lowercase (second role))
  (when local-variable?
    (twrite-string " ")
    (tprinc local-variable?))
  (twrite-string " of"))

(defun print-standard-two-element-role (role local-variable? role-string)
  (print-user-or-datum-type (second role))
  (when local-variable? (tprinc " ") (tprinc local-variable?))
  (twrite-string role-string))

(defmacro def-role-and-designation-printer (role-name &body forms)
  (let ((printer-name 
	  (intern (format nil "ROLE-AND-DESIGNATION-PRINT-~a" role-name))))
    `(progn
       (defun ,printer-name
	      (role &optional (domain-1? nil) (domain-2? nil))
	 ,@forms)
       (setf (role-and-designation-printer ',role-name) #',printer-name)
       ',printer-name)))

#+development
(defun non-invertible-roles ()
  (do-symbols (symbol (find-package "AB"))
    (when (and (role-server-exists-p symbol)
	       (not (inverse-role-server symbol)))
      (format t "~a~%" symbol))))




;;; The predicate `invertible-designation-p' returns whether or not a given
;;; designation can possibly be inverted by inverse role service.  Invertible
;;; designations are names and complex designation (i.e. quantifier, role, and
;;; domain) whose roles are either atomic or have inverse servers and which have
;;; invertible domains.  There is a further restriction that there is a symbolic
;;; atomic-naming-element of the role.  In cases where the role refers to
;;; structures or sequences, we will not be able to invert the role.

(defun-simple invertible-designation-p (designation)
  (or (symbolp designation)
      (let ((role (simple-role-of-role (role-of-designation designation))))
	(and (invertible-role-p role)
	     (invertible-designation-p (domain-of-designation designation))))))

(defun-simple invertible-role-p (role)
  (or (symbolp role)
      (and (consp role)
	   (inverse-role-server
	     (role-name-of-non-atomic-role role))
	   (symbolp (atomic-naming-element-of-role role)))))



;;; The function `type-of-designation' takes a designation and returns a symbol,
;;; which either names a data type (e.g. number or symbol) or names a class.  If
;;; no type can be determined from the designation, this function returns nil.

(defun-simple type-of-designation (designation)
  (when (consp designation)
    (let ((role (simple-role-of-role (role-of-designation designation))))
      ;; If it is an attribute, there is currently no type information that can
      ;; be returned.
      (if (symbolp role)
	  (if (third designation)
	      nil
	      ;; If the role is a symbol and there is no domain, then this is an
	      ;; iteration over instances of the class, and the role name symbol
	      ;; is the class.
	      role)
	  (let* ((role-name
		   (role-name-of-non-atomic-role role))
		 (role-type? (defined-type-of-role role-name)))
	    (or role-type?
		(car (last role))))))))




;;; The function `type-of-role' takes a non-symbol role and returns a symbol
;;; which either names a data type or names a class.  If no type can be
;;; determined, then this function returns NIL.

(defun-simple type-of-role (non-atomic-role)
  (let* ((role (simple-role-of-role non-atomic-role))
	 (role-name (role-name-of-non-atomic-role role))
	 (role-type? (defined-type-of-role role-name)))
    (or role-type?
	(car (last role)))))




;;; The functions `type-specification-of-role' and `type-specification-of-
;;; designation' should be called to fetch the type specifications of the values
;;; produced by roles and designations.  These functions are replacements for
;;; type-of-role and type-of-designation.  -jra 4/13/91

;;; The function `type-specification-of-role' takes a non-symbol role and
;;; returns nil or a type specification for the values returned by this role.
;;; This function cannot take symbol roles because a symbol role can be either a
;;; class iteration or a attribute fetch of a designation.

(defun type-specification-of-role (non-atomic-role)
  (let* ((role (simple-role-of-role non-atomic-role))
	 (role-name (if (consp role)
			(role-name-of-non-atomic-role role)
			role))
	 (defined-role-type? (defined-type-of-role role-name)))
    (or defined-role-type?
	(let ((type-in-role-spec? (if (consp role) (car (last role)))))
	  (and type-in-role-spec?
	       (or (type-specification-for-user-or-datum-type
		     type-in-role-spec?)
		   (and (symbolp type-in-role-spec?)
			(make-class-type-specification type-in-role-spec?))))))))




;;; The function `type-specification-of-designation' takes a designation and
;;; returns nil or a type specification for the values returned by this
;;; designation.

;;; This function will not be able to determine type specifications for
;;; designations when they are symbols, or when they are attribute fetches.
;;; Note that we could return types for these if we were to depend on existing
;;; user class definitions (with the restriction that all instances must conform
;;; to the definition), or if we were able to depend on names.  -jra 4/13/91

(defun type-specification-of-designation (designation)
  (when (consp designation)
    (let ((role (simple-role-of-role (role-of-designation designation))))
      ;; If it is an attribute, there is currently no type information that can
      ;; be returned.
      (if (symbolp role)
	  (if (third designation)
	      nil
	      ;; If the role is a symbol and there is no domain, then this is an
	      ;; iteration over instances of the class, and the role name symbol
	      ;; is the class.
	      (make-class-type-specification role))
	  (type-specification-of-role role)))))




;;; The function `datum-type-p' takes a symbol which is a type of a designation,
;;; and returns non-null if the symbol names a datum type.  If it does not, it
;;; returns NIL, and then this type must be assumed to be a class.

#+obsolete
(defun datum-type-p (type)
  (valid-datum-type-specification-p type))

;; The function above is obsolete and should be replaced by calls to
;; valid-datum-type-specification-p.  -jra 3/29/91




;;; The function `unique-designation-p' tests to see if the designation it is given
;;; is an unique designation.  Nil is return if not, t is returned otherwise.

(defun unique-designation-p (designation)
  (or (symbolp designation)
      (and (eq (car designation) 'the)
	   (unique-designation-p (domain-of-designation designation)))))






;;; The function `generate-designation-for-block' takes a block frame
;;; and returns a designation the block made out of eval conses.  The
;;; caller is responsible for reclaiming the designation.  If a
;;; designation cannot be made for this block, then this function
;;; returns NIL.  The designation will be constructed by returning the
;;; name of this block if it has one, and if not a search is begun
;;; through the parent-frames of this block until a block with a name is
;;; found.  This function will not be able to generate a designation and
;;; will return NIL if there is no name on this block or on any of its
;;; parents.

;;; modified for multiple inheritance -rdf, 2/17/94

(defun generate-designation-for-block (block)
  (let ((name-or-names? (name-or-names-for-frame block)))
    (cond ((and name-or-names? (symbolp name-or-names?))
	   name-or-names?)
	  ((consp name-or-names?)
	   (car name-or-names?))
	  (t
	   (let* ((parent-frame? (parent-frame block))
		  (parent-attribute? (parent-attribute-name block))
		  (parent? (parent block))
		  (parent-description?
		    (if parent?
			(class-description (class parent?))))
		  (parent-designation?
		    (if parent-frame?
			(generate-designation-for-block parent-frame?)
			nil))
		  (slot-description?
		    (and parent-attribute? parent-description?
			 (get-slot-description-of-class-description
			   parent-attribute? parent-description?))))
	     (cond
	       ((and
		  slot-description? parent-description?
		  (slot-name-needs-qualification-p
		    slot-description? parent-description?))
		(eval-list 'the
			   (eval-list 'class-qualified-name
				      (defining-class slot-description?) 
				      (pretty-slot-name slot-description?))
			   parent-designation?))
	       (parent-designation?
		(eval-list 'the
			   (pretty-slot-name slot-description?)
			   parent-designation?))))))))





;;; Note-things-encountered-during-role-service?  is a special variable flag which
;;; is rebound to t by generate-runtime-formula.  This flag indicates to
;;; search-for-directly-connected-entities-for-connection,
;;; serve-first-value-of-role, and other role service functions to add entities
;;; and connections encountered to things-that-affect-this-formula.  Note that
;;; things-that-affect-this-formula is not bound at top level.  Note also that an
;;; alternative to using this special variable would be to note things directly
;;; within role service.  However, it is generally more efficient to use
;;; things-that-affect-this-formula since things are often encountered more than
;;; once and adding them to things-that-affect-this-formula is a little more
;;; efficient than noting them each time they are encountered (see also
;;; note-runtime-structure-in-things-that-affect-it).

(def-system-variable note-things-encountered-during-role-service?
		     roles nil)

(def-system-variable things-that-affect-this-formula ROLES nil)

;; Things-that-affect-this-formula was formerly declared using defvar
;; and was not bound globally.  This has been changed due to the
;; Chestnut problem with binding special variables.  Revert 
;; when Chestnut problem is fixed!  - agh, 6/1/92



(defmacro add-to-things-that-affect-if-appropriate (thing)
  `(when note-things-encountered-during-role-service?
     (add-to-set things-that-affect-this-formula ,thing)))

(defmacro add-frame-to-things-that-affect-if-appropriate (frame)
  `(when (not (frame-being-deleted-p ,frame))
     (when note-things-encountered-during-role-service?
       (add-to-set things-that-affect-this-formula ,frame))
     t))

;; The frame-being-deleted-p check is necessary for cases when role service is
;; being done for installation (update-runtime-structures-according-to-edit, which
;; can call update-generic-simulation-formula-for-variable-or-parameter, is called
;; from some cleanup methods and slot reclaimers).

;; Frame is always assumed to be a symbol.






;;;; Role Predicates




;;; The `value-of-role-p' function provides a predicate facility that checks if
;;; the given range is a possible value of the quantifier, role, and domain
;;; value.

;;; The global property `role-predicate-function' is used to stored defined role
;;; predicate functions for a role.

(def-global-property-name role-predicate-function)




;;; The macro `def-role-predicate' is used to define a predicate function for a
;;; given role.  It takes unquoted symbols and defines the global property value
;;; to be used by value-of-role-p.

(defmacro def-role-predicate (role-name predicate-function-name)
  `(setf (role-predicate-function ',role-name) ',predicate-function-name))




;;; The function `value-of-role-p' takes a value, a quantifier (any or the), a
;;; role, and a domain value, and returns whether or not the role holds between
;;; the given value and domain.  If there is a specific role predicate for the
;;; given role, that function is called.  Otherwise, if the quantifier is the,
;;; serve-unique-value-of-role is called and the result is checked against the
;;; given value.  If the quantifier is any, then all values of this role are
;;; served in turn and checked against the given value.  If the value is the
;;; same as any of the given role values, then the result of this function is
;;; true.

;;; Note that the given role must be a simple role (i.e. any local names already
;;; stripped away), and that evaluation-values are generally not equal to other
;;; served values.  If the value-to-check is an evaluation-value, the caller is
;;; responsible for reclaiming it.

(defun value-of-role-p (value-to-check quantifier role domain)
  (if (not (framep value-to-check))
      nil
      (let* ((role-name? (if (consp role)
			     (role-name-of-non-atomic-role role)
			     nil))
	     (predicate-function?
	       (if role-name? (role-predicate-function role-name?) nil)))
	(cond (predicate-function?
	       (funcall-symbol
		 predicate-function?
		 value-to-check quantifier role domain))
	      ((eq quantifier 'the)
	       ;; There are no uniquely valued class iterations allowed,
	       ;; so a symbol role and null domain (class iteration
	       ;; case) is rejected out of hand.
	       (cond
		 ((and (symbolp role) (null domain))
		  nil)
		 ;; Attributes are checked through the vector slots
		 ;; of the sub-object.
		 ((symbolp role)
		  (and (eq (parent-attribute-name value-to-check) role)
		       (eq (parent-frame value-to-check) domain)))
		 ;; All other roles are attempted to be served uniquely.
		 (t
		  (let ((value? (serve-unique-item-or-evaluation-value-of-role
				  role domain nil nil)))
		    (cond ((evaluation-value-p value?)
			   (reclaim-evaluation-value value?)
			   nil)
			  (t
			   (eq value? value-to-check)))))))
	      ;; Generic class iteration is checked directly via a
	      ;; frame-of-class-p call.
	      ((and (symbolp role) (null domain))
	       (frame-of-class-p value-to-check role))
	      ;; All other roles must be iterated the value checked to
	      ;; see if it is one of the served role values.
	      (t
	       (loop with role-value? and continuation? and expiration?
		     initially
		       (multiple-value-setq
			 (role-value? continuation? expiration?)
			 (serve-first-item-or-evaluation-value-of-role
			   role domain nil nil))
		     until (null expiration?)
		     do
		 (cond ((eq role-value? value-to-check)
			(when continuation?
			  (close-role-value-server continuation?))
			(return t))
		       (t
			(reclaim-if-evaluation-value role-value?)))
		 (if (null continuation?)
		     (setq expiration? nil)
		     (multiple-value-setq
		       (role-value? continuation? expiration?)
		       (serve-next-item-or-evaluation-value-of-role
			 continuation?)))))))))






;;;; Serving Unique Values from Roles




;;; The macro `serve-unique-value-of-role' takes as arguments a role and a
;;; domain and will serve either one or no values for that role.  It returns a
;;; value, an expiration, and an extra objects flag.  If the role serves a
;;; continuation with its first value, this macro will do one of two things.  If
;;; the role has the first-value-ok-for-the property, it will simply close the
;;; continuation and return the first value and its expiration.  If the role
;;; does not have this property, then it will try to serve the next value for
;;; the continuation.  If it receives a value, then this function will close the
;;; continuation and return no value, since a unique value was called for.  In
;;; this case it also returns T as the third value, since no objects were served
;;; because there were too many.  This function will retry the continuation once
;;; in the case of role service returning a continuation and no value.

;;; This functionality was required for role service of object names.  In cases
;;; where an object has more than one name, the first name should be returned
;;; when an object is asked for its name.  However, it should also be possible
;;; to write rules which reference any or every of its names.  This facility
;;; provides that ability in role service, while keeping the ability to not
;;; serve anything when asked for a unique value, but several are being served.

;;; The property `first-value-ok-for-the' may be declared for roles using the
;;; macro `def-first-value-ok-for-the'.  It is checked for via the macro
;;; `first-value-ok-for-the-p'.  It is used to allow a value to be served in
;;; cases where a unique value of a role is called for, but where there are
;;; several values served by a role.


(def-global-property-name first-value-ok-for-the)

(defmacro def-first-value-ok-for-the (role-name)
  `(setf (first-value-ok-for-the ',role-name) t))

(def-substitution-macro first-value-ok-for-the-p (role)
  (let ((name-of-the-role (if (consp role)
			      (role-name-of-non-atomic-role role)
			    role)))
    ;; GENSYMCID-1638: Inconsistency in item existence checking syntax
    (cond ((eq name-of-the-role 'named-by)
	   ;; GENSYMCID-1783: "Configure" window header overlaps window controls
	   ;; GENSYMCID-1784: Edit box behavior changed: additional dialog "Cancel - Undo - End" appeared
	   ;;
	   ;; When (first-value-ok-for-the-named-by-grammar-p) is NIL (by default, when
	   ;; backward compatibility feature is NOT enabled. This new feature will broken
	   ;; G2 system KBs and have caused about two regressions.  As a workaround, we
	   ;; completely disabled GENSYMCID-1638.  Long term solution is to find out the
	   ;; relationship between this feature and the exact affected KB code in G2 system
	   ;; KB (and all layered products) and change the KB instead.
	   ;; -- Chun Tian (binghe), Jun 22, 2016.
	   (and #+ignore (first-value-ok-for-the-named-by-grammar-p)
		(first-value-ok-for-the name-of-the-role)))
	  (t
	   (first-value-ok-for-the name-of-the-role)))))

(defun serve-unique-item-or-evaluation-value-of-role
    (role domain domain-2? domains-already-type-checked?)
  (progn-for-development
    (unless (framep *current-computation-frame*)
      (error "Serve-unique-value-of-role called without ~
            *current-computation-frame* bound to a frame.")))
  (multiple-value-bind (first-value continuation first-expiration)
      (serve-first-item-or-evaluation-value-of-role
	role domain domain-2? domains-already-type-checked?)
    (cond
      (first-expiration
       (cond
	 ((null continuation)
	  (values first-value first-expiration nil))
	 ((first-value-ok-for-the-p role)
	  (close-role-value-server continuation)
	  (values first-value first-expiration nil))
	 (t
	  (multiple-value-bind
	      (second-value continuation second-expiration)
	      (serve-next-item-or-evaluation-value-of-role continuation)
	    (cond
	      (second-expiration
	       (if continuation
		   (close-role-value-server continuation))
	       (reclaim-if-evaluation-value second-value)
	       (values nil nil t))
	      ;; This next one is a judgement call.  If there is a continuation,
	      ;; there may or may not be further values.  Arbitrarily, I'm going
	      ;; to take the loose interpretation here and assume that no more
	      ;; are arriving.  -jra 10/28/87 I don't believe that this case
	      ;; occurs, but it is only a null check to leave it in.  -jra
	      ;; 8/5/96
	      (continuation
	       (close-role-value-server continuation)
	       (values first-value first-expiration nil))
	      (t
	       (values first-value first-expiration nil)))))))
      ;; If there is a continuation but no first value was served, try
      ;; service again.  I don't believe that this case ever occurs.  -jra
      ;; 8/5/96
      (continuation
       (multiple-value-setq (first-value continuation first-expiration)
	 (serve-next-item-or-evaluation-value-of-role continuation))
       (cond
	 (first-expiration
	  (cond
	    ((null continuation)
	     (values first-value first-expiration nil))
	    ((first-value-ok-for-the-p role)
	     (close-role-value-server continuation)
	     (values first-value first-expiration nil))
	    (t
	     (multiple-value-bind
		 (second-value continuation second-expiration)
		 (serve-next-item-or-evaluation-value-of-role continuation)
	       (cond
		 (second-expiration
		  (reclaim-if-evaluation-value second-value)
		  (if continuation
		      (close-role-value-server continuation))
		  (values nil nil t))
		 ;; This is also a judgement call.  If there was no value served
		 ;; on the first call for service, but there was a value and a
		 ;; continuation on the second call, there may still be values
		 ;; waiting.  Again, I'll be loose and just close the
		 ;; continuation, returning the value served.  -jra 12/18/87
		 ;; Again, I don't think this ever occurs.  -jra 8/5/96
		 (continuation
		  (close-role-value-server continuation)
		  (values first-value first-expiration nil))
		 (t
		  (values first-value
			  first-expiration nil)))))))
	 (continuation
	  (close-role-value-server continuation)
	  (values nil nil nil))
	 (t
	  (values nil nil nil))))
      (t
       (values nil nil nil)))))

(defun serve-unique-value-of-role (role domain &optional domain-2?)
  (multiple-value-bind (value? expiration? too-many-values?)
      (serve-unique-item-or-evaluation-value-of-role
	role domain domain-2? nil)
    (when (and expiration?
	       (evaluation-value-p value?))
      (setq value? (transform-evaluation-value-into-temporary-constant value?)))
    (values value? expiration? too-many-values?)))



;;; The function `serve-eval-list-of-role-values' returns an eval cons list of
;;; objects served by the passed role and domain.  It will keep calling service
;;; on the passed role until either the continuation is nil or the continuation
;;; has been tried twice consequtively and returned no new value.

(defun serve-eval-list-of-role-values (role domain)
  (multiple-value-bind (value continuation expiration)
      (serve-first-item-or-temporary-constant-of-role role domain nil)
    (loop with barren-continuation = nil
	  with values-so-far = nil
	  with last-cons-so-far = nil
	  do
      (cond (expiration
	     (if (consp last-cons-so-far)
		 (progn (setf (cdr last-cons-so-far)
			      (eval-cons value nil))
			(setf last-cons-so-far (cdr last-cons-so-far)))
		 (progn (setq values-so-far (eval-cons value nil))
			(setq last-cons-so-far values-so-far)))
	     (setq barren-continuation nil))
	    (barren-continuation
	     (close-role-value-server continuation)
	     (return values-so-far))
	    (t
	     (setq barren-continuation t)))
      (if (null continuation)
	  (return values-so-far))
      (multiple-value-setq (value continuation expiration)
	(serve-next-item-or-temporary-constant-of-role continuation)))))




;;; The function `serve-eval-list-of-designation-values' takes a designation,
;;; and returns an eval cons list of the values of all role service, generic or
;;; unique, for all levels of role in that designation.  This is an analog to
;;; evaluate-designation, but for generic designations.  Note that the variable
;;; *current-computation-frame* must be bound to a frame when this function is
;;; called.

(defun serve-eval-list-of-designation-values (designation)
  #+development
  (when (not (and (boundp '*current-computation-frame*)
		  (framep *current-computation-frame*)))
    (error
      "Serve-eval-list-of-designation-values was called without ~
       *current-computation-frame* bound to a frame."))
  (cond ((symbolp designation)
	 (let ((value? (evaluate-designation designation nil)))
	   (if value?
	       (eval-list value?)
	       nil)))
	((=f (length designation) 2)
	 (if (eq (car designation) 'the)
	     (let ((value? (serve-unique-value-of-role
			     (role-of-designation designation) nil)))
	       (if value?
		   (eval-list value?)
		   nil))
	     (serve-eval-list-of-role-values
	       (role-of-designation designation) nil)))
	(t
	 (loop with result-list = nil
	       with domain-values = (serve-eval-list-of-designation-values
				      (domain-of-designation designation))
	       for domain in domain-values
	       do
	   (if (eq (car designation) 'the)
	       (let ((value? (serve-unique-value-of-role
			       (role-of-designation designation) domain)))
		 (when value?
		   (setq result-list (eval-cons value? result-list))))
	       (multiple-value-bind (role-value? continuation? expiration?)
		   (serve-first-item-or-temporary-constant-of-role
		     (role-of-designation designation) domain nil)
		 (loop while expiration? do
		   (setq result-list (eval-cons role-value? result-list))
		       while continuation? do
		   (multiple-value-setq
		     (role-value? continuation? expiration?)
		     (serve-next-item-or-temporary-constant-of-role continuation?)))))
	   (reclaim-if-temporary-constant domain)
	       finally
		 (reclaim-eval-list domain-values)
		 (return (nreverse result-list))))))




;;; The macro `serve-first-instance-of-class' sets up a list of all of the
;;; instances of a class in eval conses.  If there is only one object, it serves
;;; the object and gives a null continuation.  If there are more than one, it
;;; serves the first with a continuation made of eval conses.

(defmacro serve-first-instance-of-class (class-name)
  `(serve-all-unreprocessed-frames
     (collect-instances-of-class-for-role-service ,class-name)))

(defun-simple collect-instances-of-class-for-role-service (class)
  (let ((instance-list nil))
    (cond
      ((subclassp class 'connection)
       (loop
	   for object-to-try being each class-instance of 'block 
	   when (not (frame-of-class-p object-to-try 'connection))
	     do
	       (loop
		for connection being each output-connection of object-to-try
		    of-type class
		as connection-frame
		   = (get-or-make-connection-frame-and-activate-if-appropriate
		       connection)
		do
		 (setq instance-list
		       (eval-cons connection-frame instance-list)))))
      ((subclassp class 'rule)
       (loop for instance being each class-instance of class
	     unless (rule-is-embedded-p instance)
	       do (setq instance-list (eval-cons instance instance-list))))
      ((subclassp 'rule class)       
       (loop for instance being each class-instance of class
	     unless (embedded-rule-p instance)
	     do
	 (setq instance-list (eval-cons instance instance-list))))
      (t
       (loop for instance being each class-instance of class
	     do
	 (setq instance-list (eval-cons instance instance-list)))))
    instance-list))

;; Similarly to INSPECT, we need to hack the results to not serve up embedded
;; rules which we use to implement action-buttons and user-menu-items.  The code
;; is a little uglier than it could be for efficiency  since we're in an inner
;; loop. -dkuznick, 2/28/00


;;; The system variable `there-exists-p' is used by function
;;; `serve-first-item-or-evaluation-value-of-role' when handling existential
;;; quantifications like `there-exists-literal' (without a `such that' part).
;;; If the variable is set to T, then the underlying role server like
;;; `connected-to' won't need to find out all matched nodes, just the first one
;;; will be enough. This can bring essential performance improvements in linear
;;; searching algorithms for connections. --Chun Tian (binghe), 2012/9/16

(def-system-variable there-exists-p roles nil)

;;; The function `serve-first-item-or-evaluation-value-of-role' is the
;;; replacement for the old serve-first-value-of-role.  It takes a role 
;;; and two domains as arguments to the role, and a flag indicating
;;; whether or not the domains have already been checked as valid argument 
;;; type values for the role.

;;; Three values are returned.  The first value is an item or evaluation-value
;;; returned by the role server.  The second value is a continuation, which may
;;; produce more values from this invocation of role service.  The third value
;;; is an expiration for the item or evaluation-value returned as the first
;;; value.  If the third value is NIL, then no values were returned from this
;;; execution of the role server.

;;; The new optional `existence?' argument is for partial search support, now
;;; it's used by stack instruction `open-role-iteration'.
;;; -- Chun Tian (binghe), 2012/9/16

(defun serve-first-item-or-evaluation-value-of-role
    (role-arg domain domain-2? domain-types-already-checked? &optional existence?)
  #+development
  (unless (framep *current-computation-frame*)
    (error "*current-computation-frame* isn't a frame."))
  (let* ((role (simple-role-of-role role-arg))
	 (role-name (if (consp role)
		       (role-name-of-non-atomic-role role)
		       role)))
    (unless domain-types-already-checked?
      (if (symbolp role)
	  (when (not (and (null domain-2?)
			  (or (null domain)
			      (framep domain)
			      (evaluation-structure-p domain))))
	    (write-wrong-arguments-for-role-warning
	      role domain)
	    (return-from serve-first-item-or-evaluation-value-of-role
	      (values nil nil nil)))
	  (let ((domain-types? (required-domain-types-of-role role-name)))
	    (cond ((null domain-types?)
		   (when domain
		     (write-wrong-arguments-for-role-warning role domain)
		     (return-from serve-first-item-or-evaluation-value-of-role
		       (values nil nil nil))))
		  ((null (cdr-of-cons domain-types?))
		   (unless (and (type-specification-type-p
				  domain (car-of-cons domain-types?))
				(null domain-2?))
		     (let ((coerced-value?
			     (coerce-to-type-for-role-service
			       domain (car-of-cons domain-types?))))
		       (cond
			 (coerced-value?
			  (setq domain coerced-value?))
			 ((not (and (temporary-constant-p domain)
				    (eq role-name 'named-by)))
			  ;; For a non-atomic role, except for the role named-by, the
			  ;; domain, if it exists, must be an item or nil.  Otherwise
			  ;; there is a level 1 warning.  We test for temporary-constants
			  ;; here, for the role named-by.  This code was merged back in 
			  ;; from 1996 code since it is needed by the Graphs capability.
			  ;; - jpg 8/10/00
			  (write-wrong-arguments-for-role-warning role domain)
			  (return-from serve-first-item-or-evaluation-value-of-role
			    (values nil nil nil)))))))
		  (t
		   (unless (and (type-specification-type-p
				  domain (car-of-cons domain-types?))
				(type-specification-type-p
				  domain-2? (cadr-of-conses domain-types?)))
		     ;; Need to print the second domain.  This current printout
		     ;; here is a bug.  -jra 8/4/96
		     (write-wrong-arguments-for-role-warning role domain)
		     (return-from serve-first-item-or-evaluation-value-of-role
		       (values nil nil nil))))))))
  (cond
    ;; Where the role is non-atomic, the name of it is used to dispatch.
    ((consp role)
     (let ((function (role-server-macro role-name))
	   ;; bind system variable for role servers (enterprise only)
	   (there-exists-p (if *is-g2-enterprise?* existence?)))
       (cond (function
	      (if domain-2?
		  (funcall-simple-multi-valued-compiled-function
		    (compiled-function-in-place function)
		    role domain domain-2?)
		  (funcall-simple-multi-valued-compiled-function
		    (compiled-function-in-place function) role domain)))
	     (t
	      (values nil nil nil)))))
    
    ;; If the domain is null, then the role is a class name, and iteration over
    ;; all the objects of that class is required.
    ((null domain)
     (if (subclassp role 'item)
	 (serve-first-instance-of-class role)
	 (values nil nil nil)))
    ;; If the domain exists, it is an item or structure, and we are fetching the
    ;; value of the attribute named by the role.
    (t
     (let ((slot-value?
	     (frame-or-evaluation-value-user-attribute-value
	       domain role nil)))
       (if slot-value?
	   (values slot-value? nil 'never)
	   (values nil nil nil)))))))



;;; If the computation-flag `no-wake-ups-during-role-serving' is true, then no
;;; wake-ups will be set during coercion to appropriate types in role service.
;;; This flag is defined in the call to def-computation-flags in TYPES.

(def-concept no-wake-ups-during-role-serving)




;;; The function `coerce-to-type-for-role-service' is used in the named-by and
;;; instances-named-by roles.  It data-seeks when necessary.  The argument is
;;; not reclaimed, and this function may create a new evaluation value result
;;; which would need to be reclaimed by the caller.

(defun-allowing-unwind coerce-to-type-for-role-service (item-or-value type)
  (let ((coerced-value? nil))
    (when (and (type-specification-subtype-in-kb-p type 'datum)
	       (of-class-p item-or-value 'variable-or-parameter))
      (if (no-wake-ups-during-role-serving)
	  (with-wake-up-management
	      (none (coerced-value?) nil)
	    (get-current-evaluation-value item-or-value nil))
	  (setq coerced-value?
		(get-current-evaluation-value item-or-value nil))))
    (unless coerced-value?
      (setq coerced-value? item-or-value))
    (cond ((type-specification-type-p coerced-value? type)
	   coerced-value?)
	  ((and (type-specification-type-p coerced-value? 'integer)
		(type-specification-subtype-in-kb-p type 'float))
	   (let ((result 
		   (make-evaluation-float
		     (coerce-fixnum-to-gensym-float
		       (evaluation-integer-value coerced-value?)))))
	     (unless (eq item-or-value coerced-value?)
	       (reclaim-evaluation-integer coerced-value?))
	     result))
	  (t
	   (unless (eq item-or-value coerced-value?)
	     (reclaim-if-evaluation-value coerced-value?))
	   nil))))

(defun write-wrong-arguments-for-role-warning (role domain)
  (write-warning-message* 1
    (twrite-string "Cannot evaluate \'")
    (print-role role)
    (tformat "\', the argument ~NA was the wrong type of value." domain)))




;;; The function `serve-first-item-or-temporary-constant-of-role' is an old
;;; version of serve-first-value-of-role which returns temporary-constants
;;; instead of evaluation-values.  It is still in use in a few places in G2,
;;; primarily in serve-eval-list-of-designation-values and its subfunctions.  As
;;; we attempt to remove the remaining uses of temporary-constants, this should
;;; eventually go away as well.  -jra 8/6/96

(defun serve-first-item-or-temporary-constant-of-role (role domain domain-2?)
  (let* ((copied-domain
	   (if (temporary-constant-p domain)
	       (make-evaluation-value-from-temporary-constant domain)
	       domain))
	 (copied-domain-2?
	   (if (temporary-constant-p domain-2?)
	       (make-evaluation-value-from-temporary-constant domain-2?)
	       domain-2?)))
    (multiple-value-bind
	(value continuation? expiration?)
	(serve-first-item-or-evaluation-value-of-role
	  role copied-domain copied-domain-2? nil)
      (when (and expiration?
		 (evaluation-value-p value))
	(setq value (transform-evaluation-value-into-temporary-constant value)))
      (reclaim-if-evaluation-value copied-domain)
      (reclaim-if-evaluation-value copied-domain-2?)
      (values value continuation? expiration?))))




;;; The function `frame-or-temporary-constant-user-attribute-value' takes an
;;; item and a pretty-slot-name symbol possibly naming a user defined attribute.
;;; This function role serves the value of that attribute if any.  If there is
;;; no attribute, or the value of the attribute is NIL, this returns triple
;;; NILs.  If the value of the attribute is a slot constant, it is cast into a
;;; temporary constant and returned.  If the value is a frame, that frame is
;;; returned.

;;; The function `frame-or-evaluation-value-user-attribute-value' performs a
;;; similar operation as the one returning temporary constants, but instead it
;;; returns evaluation values.  This is the optimized version called from the
;;; stack evaluator.

;;; This function has also been modified to take an argument,
;;; class-specific-attribute- class?, that is used to determine which definition
;;; of the named attribute should be referenced.  This is necessary because the
;;; an object may have several versions of the attribute defined by superior
;;; classes or the object-definition.  If the given class is not a superior
;;; class of the given item, then this function returns NIL.

;;; The function `frame-or-evaluation-value-given-user-vector-index' performs
;;; the same operation as the function above, except that it accepts a user
;;; vector attribute index.  This allows a faster access to the attribute value.

;; Note the use of `slot-init-form' below.  This is used because of the
;; coincidence that the init form and non-defaulted values are both stored in
;; the second of the slot description.  -jra 8/27/91

;; Note that I believe the callers of this function assume that only user
;; defined slots will return anything other than triple NILs from this function.
;; This was assured previously, since user defined slots were only implemented
;; as lookup slots, and this function only manipulated the lookup-structure,
;; thus violating the abstractions but serving its own purpose.  This assumption
;; needs to be reverified before changing this function as part of the
;; vectorized user slots project.  -jra & ghw 1/5/93

;; Since the tail of the old lookup-structure contains the class slot-
;; descriptions, and the slot-value is derived from the slot-init-form, it
;; seems to me that this function might possibly return values from
;; non-user-defined slots, unless the slot-init-forms are not constants,
;; frames, or floats.  Check this out further for project vectorized
;; user-slots.  (2/22/93 ghw)

(defun-simple frame-or-evaluation-value-user-attribute-value
    (item-or-structure attribute class-specific-attribute-class?)
  (cond
    ((evaluation-structure-p item-or-structure)
     ;; JED 8/28/96 -- seemed like the structure case should copy
     ;; the slot value (if its a non-nil value)
     (let ((structure-slot-value?
	     (evaluation-structure-slot-macro item-or-structure attribute nil)))
       (cond
	 ((null structure-slot-value?)
	  nil)
	 ((framep structure-slot-value?)
	  (if (serve-item-p structure-slot-value?)
	      structure-slot-value?
	      nil))
	 ((evaluation-truth-value-p structure-slot-value?)
	  (copy-evaluation-truth-value structure-slot-value?))
	 (t
	  (copy-evaluation-non-logical-datum-macro structure-slot-value?)))))
    ((and class-specific-attribute-class?
	  (not (frame-of-class-p item-or-structure
				 class-specific-attribute-class?)))
     nil)
    (t
     (let* ((slot-description?
	      (get-slot-description-of-frame
		attribute item-or-structure class-specific-attribute-class?))
	    (user-slot?
	      (and slot-description?
		   (user-defined-slot-description-p slot-description?)))
	    (unaliased-name?
	      (if (not user-slot?)
		  (get-slot-name-for-alias-if-any
		    attribute item-or-structure))))
       (cond
	 (user-slot?
	  (let ((slot-value? (get-slot-description-value
			       item-or-structure slot-description?)))
	    (when (add-frame-to-things-that-affect-if-appropriate
		    item-or-structure)
	      (cond ((null slot-value?)
		     nil)
		    ((slot-constantp slot-value?)
		     (cast-slot-constant-into-evaluation-value slot-value?))
		    ((framep slot-value?)
		     (if (serve-item-p slot-value?)
			 slot-value?
			 nil))
		    (t
		     (copy-evaluation-non-logical-datum-macro slot-value?))))))
	 
	 (t
	  (cond
	    (unaliased-name?
	     (setq slot-description? (get-slot-description-of-frame
				       unaliased-name? item-or-structure
				       class-specific-attribute-class?)))
	    ;; If we have stumbled across a slot-description of a slot which has
	    ;; an alias, reject this access.  -jallard 5/10/97
	    ((get-alias-for-slot-name-if-any attribute item-or-structure)
	     (setq slot-description? nil)))
	  (let* ((evaluator-info
		   (when slot-description?
		     (get-slot-description-evaluator-info slot-description?)))
		 (getter?
		   (when evaluator-info
		     (evaluator-slot-info-category-getter evaluator-info)))
		 (virtual-attribute? nil))
	    (cond
	      (getter?
	       (multiple-value-bind (extracted-value reclaim-p)
		   (funcall-simple-multi-valued-compiled-function
		     (evaluator-slot-info-category-extracter evaluator-info)
		     (get-slot-description-value
		       item-or-structure slot-description?)
		     evaluator-info)
		 (prog1 (call-category-getter-fn
			  getter?
			  extracted-value
			  item-or-structure slot-description?)
		   (when reclaim-p
		     (reclaim-slot-value extracted-value)))))
	      ((and (setq virtual-attribute? (virtual-attribute attribute))
		    (type-specification-type-p
		      item-or-structure
		      (virtual-attribute-arg-type virtual-attribute?)))
	       (let ((value (get-virtual-attribute
			      item-or-structure virtual-attribute?)))
		 (if (eq value no-component-value)
		     nil
		     value)))
	      ;; The following is a workaround for accessing the old
	      ;; authorized-system-slots and predefined-user-attributes.
	      ;; These should be removed once virtual attributes have been
	      ;; put into place for each of these.  FIND ME, JRA| -jra
	      ;; 6/10/96
	      ;; We have attempted to dump this special case. 10/29/96
	      (slot-description?
	       (let ((category?
		       (evaluator-slot-info-category evaluator-info)))
		 (when (or (eq category? 'attribute)
			   (memq attribute authorized-system-slots)
			   (assq attribute predefined-user-attributes))
		   #+development
		   (cerror "go on"
			   "tell joe that a category-evalator-interface is missing for ~a"
			   category?))))))))))))

(defun-simple frame-or-evaluation-value-given-user-vector-index
    (item user-attribute-index)
  (if (fixnump user-attribute-index)
      (when (add-frame-to-things-that-affect-if-appropriate item)
	(let ((slot-value? (get-user-vector-slot-index-value-macro
			     item user-attribute-index)))
	  (cond ((null slot-value?)
		 nil)
		((slot-constantp slot-value?)
		 (cast-slot-constant-into-evaluation-value slot-value?))
		((framep slot-value?)
		 (if (serve-item-p slot-value?)
		     slot-value?
		     nil))
		(t
		 (copy-evaluation-non-logical-datum-macro slot-value?)))))
      (frame-or-evaluation-value-user-attribute-value
	item
	(first user-attribute-index)
	(fourth user-attribute-index))))




;;; A `constant attribute value' is an attribute known not to be a frame.

;;; `Convert-constant-attribute-value-to-cached-value' given the value of an
;;; attribute known not to be a frame, returns a triple of values as for
;;; datum-or-string-evaluate. 

;;; HOWEVER, if a text-string is returned, it is owned by the slot it came from,
;;; and is not to be disposed of without copying if appropriate. Since the value
;;; may also be a non-immediate number, one must be in a temporary flonum
;;; context.  If other types of numbers are introduced which require a copy
;;; logic like text-strings, then these must be handled appropriately also.

(defun convert-constant-attribute-value-to-cached-value (constant-attribute-value)
  (cond
    ((null constant-attribute-value) (values nil nil nil))
    ((slot-value-float-p constant-attribute-value)
     (values
       (slot-value-float-value constant-attribute-value)
       'never 'number))
    ((slot-constantp constant-attribute-value)
     (values (get-slot-value-number-value-or-string-from-slot-constant
	       constant-attribute-value)
	     'never
	     (get-unit-from-slot-constant constant-attribute-value)))
    ((numberp constant-attribute-value)
     (values constant-attribute-value 'never 'number))
    ((symbolp constant-attribute-value)
     (values constant-attribute-value 'never 'symbol))
    ((text-string-p constant-attribute-value)
     (values constant-attribute-value 'never 'text))))

;; At present, this function is only used in module CONTROLS.  (MHD 2/28/91)




;;; The macro `serve-all-evaluation-values' takes an eval-cons list (possibly
;;; null) of evaluation values and role serves them.

(defun serve-next-evaluation-value (continue? continuation)
  (if (null continue?)
      (loop for evaluation-value in (cdr-of-cons continuation) do
	(reclaim-evaluation-value evaluation-value)
	    finally (reclaim-eval-list continuation))
      (let ((list? (cdr-of-cons continuation)))
	(cond ((null list?)
	       (reclaim-eval-cons-macro continuation)
	       (values nil nil nil))
	      (t
	       (let ((constant-to-serve (car-of-cons list?))
		     (rest? (cdr-of-cons list?)))
		 (cond ((null rest?)
			(reclaim-eval-list-given-tail continuation list?)
			(values constant-to-serve nil 'never))
		       (t
			(setf (cdr continuation) rest?)
			(reclaim-eval-cons-macro list?)
			(values constant-to-serve continuation 'never)))))))))

(defmacro serve-all-evaluation-values (eval-cons-list-of-evaluation-values?)
  (let ((vals (gensym)))
    `(let ((,vals ,eval-cons-list-of-evaluation-values?))
       (if (null ,vals)
	   (values nil nil nil)
	   (let ((val-to-serve (car-of-cons ,vals))
		 (rest? (cdr-of-cons ,vals)))
	     (cond (rest?
		    (setf (car ,vals) #'serve-next-evaluation-value)
		    (values val-to-serve ,vals 'never))
		   (t
		    (reclaim-eval-cons-macro ,vals)
		    (values val-to-serve nil 'never))))))))




;;; The function `serve-next-unreprocessed-frame' is a continuation role server
;;; for serve-all-unreprocessed-frames.  It serves frames from continuation
;;; passed it, reclaiming the eval conses it is made from as the frames get
;;; served.

(defun serve-next-unreprocessed-frame (continue? continuation)
  (if (not continue?)
      (progn
	(reclaim-frame-serial-number (second continuation))
	(reclaim-eval-list-macro continuation))
      (loop for frame-reference-cons = (cdr-of-cons continuation)
	    for frame-reference-number = (car-of-cons frame-reference-cons)
	    for instance-cons = (cdr-of-cons frame-reference-cons)
	    for rest-of-instances = (cdr instance-cons)
	    for instance = (car instance-cons)
	    do
	(cond (rest-of-instances
	       (setf (cdr frame-reference-cons) rest-of-instances)
	       (reclaim-eval-cons-macro instance-cons)
	       (if (and (frame-has-not-been-reprocessed-p
			  instance frame-reference-number)
			(serve-item-p instance))
		   (return (values instance continuation 'never))
		   nil))
	      (instance-cons
	       (reclaim-eval-list-given-tail continuation instance-cons)
	       (if (and (frame-has-not-been-reprocessed-p
			  instance frame-reference-number)
			(serve-item-p instance))
		   (progn
		     (reclaim-frame-serial-number frame-reference-number)
		     (return (values instance nil 'never)))
		   (progn
		     (reclaim-frame-serial-number frame-reference-number)
		     (return (values nil nil nil)))))
	      (t
	       (reclaim-frame-serial-number frame-reference-number)
	       (reclaim-eval-list-macro continuation)
	       (return (values nil nil nil)))))))




;;; The function `serve-all-unreprocessed-frames' should be called with a
;;; possibly null eval list of frames to be served.  As the frames are served,
;;; the list will be reclaimed.  This function also ensures that if a frame has
;;; been reprocessed, it will not be served.

(defun serve-all-unreprocessed-frames (frame-list)
  (let (instance-to-serve)
    (cond ((null frame-list)
	   (values nil nil nil))
	  ((null (cdr-of-cons frame-list))
	   (setq instance-to-serve (car-of-cons frame-list))
	   (reclaim-eval-cons-macro frame-list)
	   (if (serve-item-p instance-to-serve)
	       (values instance-to-serve nil 'never)
	       (values nil nil nil)))
	  (t
	   (setq instance-to-serve (car-of-cons frame-list))
	   (setf (car frame-list) (copy-frame-serial-number (current-frame-serial-number)))
	   (let ((continuation (eval-cons-macro
				 #'serve-next-unreprocessed-frame
				 frame-list)))
	     (if (serve-item-p instance-to-serve)
		 (values instance-to-serve continuation 'never)
		 (serve-next-unreprocessed-frame t continuation)))))))




;;; The function `serve-next-item-or-value' is a continuation role server for
;;; serve-all-items-and-values.  It serves an item-or-value from the
;;; continuation passed it, reclaiming the eval conses it is made from as the
;;; values get served.  If the continuation is closed prematurely, reclaim the
;;; evaluation-values in the continuation.  In normal service, the consumer of
;;; the values is responsible for reclaiming any served evaluation-values.

(defun serve-next-item-or-value (continue? continuation)
  (if (not continue?)
      (loop for item-or-value in (cddr-of-conses continuation)
	    do
	(unless (frame-or-deleted-frame-p item-or-value)
	  (reclaim-evaluation-value item-or-value))
	    finally
	      (progn
		(reclaim-frame-serial-number (cadr continuation))
		(reclaim-eval-list continuation)))
      (let* ((serial-number-cons (cdr-of-cons continuation))
	     (frame-serial-number (car-of-cons serial-number-cons))
	     (value-cons (cdr-of-cons serial-number-cons))
	     (rest-of-values (cdr value-cons))
	     (item-or-value (car value-cons)))
	(cond (rest-of-values
	       (setf (cdr serial-number-cons) rest-of-values)
	       (reclaim-eval-cons-macro value-cons)
	       (if (and (not (deleted-frame-p item-or-value))
			(or (not (framep item-or-value))
			    (and (frame-has-not-been-reprocessed-p
				   item-or-value frame-serial-number)
				 (serve-item-p item-or-value))))
		   (values item-or-value continuation 'never)
		   (serve-next-item-or-value continue? continuation)))
	      (value-cons
	       (reclaim-eval-list-given-tail continuation value-cons)
	       (if (and (not (deleted-frame-p item-or-value))
			(or (not (framep item-or-value))
			    (and (frame-has-not-been-reprocessed-p
				   item-or-value frame-serial-number)
				 (serve-item-p item-or-value))))
		   (progn
		     (reclaim-frame-serial-number frame-serial-number)
		     (values item-or-value nil 'never))
		   (progn
		     (reclaim-frame-serial-number frame-serial-number)
		     (values nil nil nil))))
	      (t
	       (reclaim-eval-list-macro continuation)
	       (reclaim-frame-serial-number frame-serial-number)
	       (values nil nil nil))))))



;;; The function `serve-all-items-and-values' is given an eval list containing
;;; items-or-values, and it returns values that serve up the first of the given
;;; values for role service, ala serve-all-unreprocessed-frames and
;;; serve-all-evaluation-values.

(defun serve-all-items-and-values (item-or-value-list)
  (let (value-to-serve)
    (cond ((null item-or-value-list)
	   (values nil nil nil))
	  ((null (cdr-of-cons item-or-value-list))
	   (setq value-to-serve (car-of-cons item-or-value-list))
	   (if (or (not (framep value-to-serve))
		   (serve-item-p value-to-serve))
	       (values value-to-serve nil 'never)
	       (values nil nil nil)))
	  (t
	   (setq value-to-serve (car-of-cons item-or-value-list))
	   (setf (car item-or-value-list) (copy-frame-serial-number (current-frame-serial-number)))
	   (let ((continuation (eval-cons-macro #'serve-next-item-or-value
						item-or-value-list)))
	     (if (or (not (framep value-to-serve))
		     (serve-item-p value-to-serve))
		 (values value-to-serve continuation 'never)
		 (serve-next-item-or-value t continuation)))))))
		 




;;;; Role Caching




;;; Lists of frames to be served by roles of frames are cached in a structure
;;; inside of the role-cache slot of entity instances.  This structure is an
;;; alist of the role names which have been cached.  The structure of the values
;;; of the alist entry are specific to each role.  The alist values will either
;;; be a cache list for that role, or they will be some other type of lookup
;;; structure if that role takes arguments, typically another alist.  The result
;;; of these cache lookups will in all cases be a cache list.

;;; Cache lists are eval cons lists whose first element is frame serial number,
;;; whose second element is a reference count, and the rest of whose elements
;;; are frames.  When these cache lists are served from, they should be handed
;;; to serve-all-unreprocessed-cached-frames.  This macro will cause each of the
;;; role values to be served without having to copy the list of frames.  The
;;; reason for the reference count has to do with decaching.  When a cache list
;;; is let go of by either the continuation server or the frame which held the
;;; cache, it calls drop-reference-to-cache-list.  This will decrement the
;;; reference count, and if it has reached zero, it will reclaim the entire
;;; cache list.  Since we expect that decaching will happen very seldom, the
;;; efficiency of serving roles without copying the cached frame list should
;;; make up for the overhead of maintaining the reference count.




;; The following is a definition of the syntax of role caches
;; used in the role-cache slot in entities:
;;
;; <role-cache-entries>  == (role-cache <entity>)
;;			 == list of <role-cache-entry>'s
;; (role-cache <entity>) == list of <role-cache-entry>'s
;; <role-cache-entry>    == (<role-name> . <specific-cache-list>)
;; <role-name>           == <symbol>
;; <specific-cache-list> == list of <specific-cache>'s
;; <specific-cache>      == (<role-argument> . <cache-list>)
;; <role-argument> 	 == <symbol> | ( <quantifier> . <designation> )
;; <quantifier>		 == <symbol>
;; <designation>	 == <symbol-tree>
;; <cache-list>          == (<serial#> <reference-count> . <frame-list>)
;;
;; Definitions of macros for extracting various parts of the above
;; syntax is given as follows:


(defmacro role-name-of-role-cache-entry (role-cache-entry)
  `(car ,role-cache-entry))

(defmacro specific-cache-list-of-role-cache-entry (role-cache-entry)
  `(cdr ,role-cache-entry))



(defmacro role-argument-of-specific-cache (specific-cache)
  `(car ,specific-cache))

(defmacro cache-list-of-specific-cache (specific-cache)
  `(cdr ,specific-cache))



(defmacro serial-number-of-cache-list (cache-list)
  `(car ,cache-list))

(defmacro reference-count-of-cache-list (cache-list)
  `(second ,cache-list))

(defmacro frame-list-of-cache-list (cache-list)
  `(cddr ,cache-list))



(defmacro serial-number-of-specific-cache (specific-cache)
  `(serial-number-of-cache-list
    (cache-list-of-specific-cache ,specific-cache)))

(defmacro reference-count-of-specific-cache (specific-cache)
  `(reference-count-of-cache-list
    (cache-list-of-specific-cache ,specific-cache)))

(defmacro frame-list-of-specific-cache (specific-cache)
  `(frame-list-of-cache-list
    (cache-list-of-specific-cache ,specific-cache)))





;;; The macro `make-cache-list' takes an eval cons list of frames, and returns a
;;; newly created cache list with one recorded reference to it.


(defun make-cache-list (eval-cons-list-of-frames)
;  (dformat t "MAKE-CACHE-LIST ~a" eval-cons-list-of-frames)
  (eval-cons (copy-frame-serial-number (current-frame-serial-number))
	     (eval-cons 1 eval-cons-list-of-frames)))


;;; The macro `add-reference-to-cache-list' takes a cache list as its argument
;;; and modifies that cache list to include another reference to it.


(defmacro add-reference-to-cache-list (cache-list)
  `(incff (reference-count-of-cache-list ,cache-list)))




;;; The macro `drop-reference-to-cache-list' will decrement the reference count
;;; at the head of the list, and if this is zero, it will then reclaim the eval
;;; conses which make up this list.  This macro has an undefined return value.


(def-substitution-macro drop-reference-to-cache-list (cache-list)
  (when (=f (decff (reference-count-of-cache-list cache-list)) 0)
    (reclaim-frame-serial-number (car cache-list))
    (reclaim-eval-list-macro cache-list)))




;;; The function `serve-all-unreprocessed-cached-frames' takes a cache list as
;;; its argument and will serve all of the frames in it, as long as they have
;;; not been reprocessed.  Cached role lists are lists made of eval conses whose
;;; first element contains a frame serial number, whose second element contains
;;; a reference count, and the rest of whose elements are frames to be served.
;;; This function will increment the reference count to this cache list and serve
;;; the first frame along with a continuation for the rest of them.  When all
;;; frames have been served, decrement the reference number and then check if it
;;; is zero.  If so, eval list reclaim the cache list, it has been dropped, and
;;; this was the last reference to it.


(defun serve-all-unreprocessed-cached-frames (cache-list)
  (loop with frame-serial-number = (serial-number-of-cache-list cache-list)
	for current-position on (frame-list-of-cache-list cache-list)
	for current-frame = (car-of-cons current-position)
	do
    (if (and (serve-item-p current-frame)
	     (not (frame-has-been-reprocessed-p
		    current-frame frame-serial-number)))
	(return (values current-frame
			(if (setq current-position (cdr-of-cons current-position))
			    (progn
			      (add-reference-to-cache-list cache-list)
			      (eval-cons-macro
				#'serve-next-unreprocessed-cached-frame
				(eval-cons-macro
				  current-position
				  cache-list)))
			    nil)
			'never)))
	finally
	  (values nil nil nil)))




;;; The function `serve-next-unreprocessed-cached-frame' is the continuation
;;; server for cached-frame lists.  It takes a continue? flag and a
;;; continuation.  If the continue? flag is NIL, it will close and reclaim the
;;; passed continuation.  If the flag is non-NIL, it will serve the next
;;; unreprocessed frame in the continuation, reclaiming it if there are no more
;;; left to be served.

(defun serve-next-unreprocessed-cached-frame (continue? continuation)
  (let* ((current-position-cons (cdr-of-cons continuation))
	 (cache-list (cdr-of-cons current-position-cons)))
    (if continue?
	(loop for current-spot on (car-of-cons current-position-cons)
	      for current-frame = (car-of-cons current-spot)
	      do
	  (if (and (serve-item-p current-frame)
		   (not (frame-has-been-reprocessed-p
			  current-frame
			  (serial-number-of-cache-list cache-list))))
	      (let ((next-spot (cdr current-spot)))
		(cond (next-spot
		       (setf (car current-position-cons) next-spot)
		       (return (values current-frame continuation 'never)))
		      (t
		       (drop-reference-to-cache-list cache-list)
		       (reclaim-eval-list-given-tail
			 continuation current-position-cons)
		       (return (values current-frame nil 'never))))))
	      finally
		(drop-reference-to-cache-list cache-list)
		(reclaim-eval-list-given-tail
		  continuation current-position-cons)
		(return (values nil nil nil)))
	(progn
	  (drop-reference-to-cache-list cache-list)
	  (reclaim-eval-list-given-tail continuation current-position-cons)))))




;;; The function `equal-assoc' works just like assoc with :test #'equal.

(defun-simple equal-assoc (key alist)
  (if (atom key)
      (loop for entry in alist
	    when (eq (car entry) key)
	      do (return entry))
      (let ((key-car (car key))
	    (key-cdr (cdr key)))
	(if (and (atom key-car)
		 (consp key-cdr)
		 (null (cdr key-cdr))
		 (atom (car key-cdr)))
	    (loop with key-cadr = (car key-cdr)
		  for entry in alist
		  for entry-key = (car entry)
		  when (and (consp entry-key)
			    (eq (car entry-key) key-car)
			    (let ((entry-key-cdr (cdr entry-key)))
			      (and (consp entry-key-cdr)
				   (null (cdr entry-key-cdr))
				   (eq (car entry-key-cdr) key-cadr))))
		    do (return entry))
	    (loop for entry in alist
		  when (equal (car entry) key)
		    do (return entry))))))


(def-system-variable role-caching-enabled? ROLES nil)

(defun use-role-caching (enabled-p)
  (when (and (not enabled-p)
	     role-caching-enabled?)
    (decache-roles-for-all-items))
  (setq role-caching-enabled? enabled-p))

;;; The macro `serve-cached-role' is used inside of role server functions
;;; to cause collection, caching, and role service of roles which get
;;; cached as nested association lists.  The arguments to this macro are
;;; as follows:  entity is the domain of this role, role-name is the
;;; symbol which names this role and which will be used as the key for an
;;; assq search of the entity's role-cache slot, argument is a symbol or
;;; a symbol tree argument to the given role which is used as a key into
;;; the association list stored under the role name, and finally
;;; collection-form is a form which should be evaluated to return an eval
;;; list of the frames to be served for this role when there is no cache.

;;; This form attempts to find a cached value for this role and argument pair
;;; in the role-cache slot of the given entity.  If found, this cache is
;;; served.  If not found, the collection form will be evaluated to return an
;;; eval list of frames, this list will be cached on the given entity, and
;;; then it will be served.

(defmacro serve-cached-role
    ((entity role-name argument) &body collection-form)
  (let ((entity-variable (gensym))
	(role-name-variable (gensym))
	(argument-variable (gensym))
	(eval-list-of-role-values (gensym))
	(use-role-caching-p (gensym)))
    `(let* ((,entity-variable ,entity)
	    (,role-name-variable ,role-name)
	    (,argument-variable ,argument)
	    (,use-role-caching-p (and role-caching-enabled?
				      (not (role-serve-inactive-objects?))))
	    domain-cache? role-cache? specific-cache?)
       (if (and ,use-role-caching-p
		(progn
		  (setq domain-cache? (role-cache ,entity-variable))
		  (setq role-cache? (assq ,role-name-variable domain-cache?))
		  (setq specific-cache?
			(equal-assoc ,argument-variable (cdr role-cache?)))))
	   (serve-all-unreprocessed-cached-frames (cdr specific-cache?))
	   (let ((,eval-list-of-role-values (progn ,@collection-form)))
	     (if ,use-role-caching-p
		 ;; Note that the domain-cache? (role-cache) value, from above,
		 ;; is not passed to the following function.  (The cache may
		 ;; have been reclaimed or modified in the "collection-format".)
		 ;; The following looks up the role-cache.  - cpm, 6/9/95
		 (add-to-cache-and-serve
		   ,entity-variable ,role-name-variable
		   (copy-tree-using-eval-conses ,argument-variable)
		   ,eval-list-of-role-values)
		 (serve-all-unreprocessed-frames ,eval-list-of-role-values)))))))




;;; The function `add-to-cache-and-serve' is used to cache an eval cons list of
;;; frames, and begin role service of them.

;;; The arguments are as follows:
;;; - entity is the frame on which the role is to be cached,
;;; - role-name is a symbol which should be used as the association list key at
;;;   the top level of the domain's role cache,
;;; - role-argument is a tree of eval conses and symbols which should be used
;;;   as a secondary lookup key within the cache for this role name,
;;; - eval-cons-list-of-frames is a list of the frames which are to
;;;   be served for this role.

(defun add-to-cache-and-serve
       (entity role-name role-argument eval-cons-list-of-frames)
;  (dformat t "ADD-TO-CACHE-AND-SERVE: ~A, ~A, ~A, ~A, ~A, ~a" ENTITY ROLE-NAME ROLE-ARGUMENT DOMAIN-CACHE? ROLE-CACHE? eval-cons-list-of-frames)

  (let* ((cache-list (make-cache-list eval-cons-list-of-frames))
	 (specific-cache-entry (eval-cons role-argument cache-list))
	 (domain-cache? (role-cache entity))
	 (role-cache? (assq role-name domain-cache?)))
    (if role-cache?
	(setf (cdr role-cache?)
	      (eval-cons specific-cache-entry (cdr role-cache?)))
	(setf (role-cache entity)
	      (eval-cons
		(eval-list role-name specific-cache-entry)
		domain-cache?)))
    (serve-all-unreprocessed-cached-frames cache-list)))




(def-substitution-macro make-inverse-role-argument
			(role-argument quantifier designation)
  (eval-cons role-argument
	     (eval-cons quantifier designation)))

(def-substitution-macro reclaim-inverse-role-argument (role-argument)
    (reclaim-eval-cons (cdr role-argument))
    (reclaim-eval-cons role-argument))




;;; The macro `serve-cached-inverse-roles' creates the role argument to
;;; be used by serve-cached-role for service, calls serve-cached-role,
;;; and reclaims the cons cells used after the role has been served.
;;; The appropriate values are returned.

; (serve-cached-inverse-roles (obj quant role dd) '(b1) '(b2 x))

(defmacro serve-cached-inverse-roles
    ((object quantifier role domain-designation) &body collection-form)
  (let ((object-variable (gensym))
	(quantifier-variable (gensym))
	(role-variable (gensym))
	(domain-designation-variable (gensym))
	(value-to-be-returned (gensym))
	(continuation-to-be-returned (gensym))
	(expiration-to-be-returned (gensym))
	(role-argument (gensym))
	(use-role-caching-p (gensym)))
    `(let* ((,object-variable ,object)
	    (,quantifier-variable ,quantifier)
	    (,role-variable ,role)
	    (,domain-designation-variable ,domain-designation)
	    (,use-role-caching-p (and role-caching-enabled?
				      (not (role-serve-inactive-objects?))))
	    (,role-argument
	       (when ,use-role-caching-p
		 (make-inverse-role-argument
		   (cdr ,role-variable)
		   ,quantifier-variable
		   ,domain-designation-variable))))
       (multiple-value-bind (,value-to-be-returned
			       ,continuation-to-be-returned
			       ,expiration-to-be-returned)
	   (serve-cached-role
	       (,object-variable (car ,role-variable) ,role-argument)
	     ,@collection-form)
	 (when ,role-argument
	   (reclaim-inverse-role-argument ,role-argument))
	 (values ,value-to-be-returned
		 ,continuation-to-be-returned
		 ,expiration-to-be-returned)))))




;;; The predicate function `designation-could-denote-item-p' is called when
;;; deciding whether or not to perform inverse service with the passed item as a
;;; result.  It should return whether or not this designation or the role of the
;;; desination could refer to the passed item.

(defun designation-could-denote-item-p (designation item)
  (let ((role nil)
	(attribute? (parent-attribute-name item)))
    (cond ((symbolp designation)
	   (let ((name-or-names (name-or-names-for-frame item)))
	     (if (consp name-or-names)
		 (memq designation name-or-names)
		 (eq designation name-or-names))))
	  ((symbolp (setq role (role-of-designation designation)))
	   (if (or (eq role attribute?)
		   (and (consp attribute?)
			(eq role (car-of-cons attribute?))))
	       t
	       (frame-of-class-p item role)))
	  ((name-denotation-p role)
	   (and (consp role)
		(consp attribute?)
		(member (cdr attribute?)
			(class-inheritance-path
			  (class-description
			    (class-qualifier role))))))
	  ((inline-tree-eq role (role-server this-workspace kb-workspace))
	   (and (framep *current-computation-frame*)
		(eq item
		    (nth-value 1 (get-block-on-workspace-for-frame
				   *current-computation-frame*)))))
	  ;; GENSYMCID-1303: Syntax problem 1
	  ((inline-tree-eq role (role-server this-rule rule))
	   (eq item *current-computation-frame*))
	  (t
	   (let ((class? (atomic-class-element-of-role role)))
	     (if class?
		 (frame-of-class-p item class?)
		 nil))))    
    ))




;;; The function `designation-denotes-item-p' determines conclusively whether
;;; or not the given designation denotes the given entity.  Note that the
;;; designation must be invertible, and is allowed to be a generic designation.
;;; If the designation is generic or has some role within it which is not
;;; strictly a one to one relation, then this predicate returns non-nil if the
;;; given entity is one of the set of entities denoted.  Note that this
;;; predicate will only work while the system is running and that
;;; *current-computation-frame* must be bound.

(defun designation-denotes-item-p (designation entity)
  (when designation
    (loop do
      (cond
	((symbolp designation)
	 (let ((name-or-names (name-or-names-for-frame entity)))
	   (return (if (consp name-or-names)
		       (memq designation name-or-names)
		       (eq designation name-or-names)))))
	((=f (length designation) 2)
	 (let ((role (second-of-long-enough-list designation)))
	   (return
	     (if (symbolp role)
		 (if get-focal-entity-for-simulation-formula?
		     (let ((frame-of-class-p
			     (frame-of-class-p entity role)))
		       (when frame-of-class-p
			 (setq focal-entity-for-simulation-formula entity))
		       frame-of-class-p)
		     (frame-of-class-p entity (second designation)))
		 (and (inline-tree-eq
			role (role-server this-workspace kb-workspace))
		      (framep *current-computation-frame*)
		      (eq (nth-value 1 (get-block-on-workspace-for-frame
					 *current-computation-frame*))
			  entity))))))
	((=f (length designation) 3)
	 (let* ((quantifier (car-of-cons designation))
		(role-cons (cdr-of-cons designation))
		(role (car-of-cons role-cons))
		(domain (car-of-cons (cdr-of-cons role-cons))))
	   (multiple-value-bind (value continuation expiration)
	       (serve-first-value-of-role-inverse
		 entity quantifier role domain)
	     (cond ((null expiration)
		    (if continuation
			(close-role-value-server continuation))
		    (return nil))
		   ((null continuation)
		    (setq entity value)
		    (setq designation domain))
		   (t
		    (loop do
		      (if (designation-denotes-item-p
			    domain value)
			  (progn
			    (if continuation
				(close-role-value-server continuation))
			    (return-from designation-denotes-item-p t))
			  (multiple-value-setq
			    (value continuation expiration)
			    (if continuation
				(serve-next-item-or-evaluation-value-of-role
				  continuation)
				(values nil nil nil))))
			  while expiration
			  finally
			    (if continuation
				(close-role-value-server continuation))
			    (return-from designation-denotes-item-p nil)))))))))))



(defun serve-first-value-of-role-inverse
       (object quantifier role domain-designation)
  ;; If the given role is non-atomic, dispatch on the car of the role to the
  ;; appropriate inverse role server.  If no server exists, this role is not
  ;; invertible and return triple nils.
  (cond ((consp role)
	 (let ((inverse-server-function
		 (inverse-role-server
		   (role-name-of-non-atomic-role role))))
	   (cond (inverse-server-function
		  (funcall-simple-multi-valued-compiled-function
		    (compiled-function-in-place inverse-server-function)
		    object quantifier role domain-designation))
		 (t
		  (values nil nil nil)))))
	;; Atomic roles are served through attributes.  Check for the attribute
	;; by seeing if this object has a parent and checking if the given
	;; symbol matches the attribute name of the parent information.  Note
	;; that it is not necessary to check if this atomic role really could be
	;; an attribute, that is accounted for by just checking if the parent of
	;; this variable has the given symbol as its attribute name.
	((and role domain-designation)
	 (multiple-value-bind (parent? attribute? class?)
	     (get-kb-parent-information object)
	   (if (and (eq attribute? role)
		    (if class?
			(eq class? (if (consp domain-designation)
				       (second domain-designation)
				       domain-designation))
			t)
		    (add-frame-to-things-that-affect-if-appropriate parent?)
		    (designation-could-denote-item-p domain-designation parent?)
		    (serve-item-p parent?))
	       (values parent? nil 'never)
	       (values nil nil nil))))
	;; We get here if either the role or the domain-designation were NIL.
	(t
	 (values nil nil nil))))




;;; When performing inverse role service of a designation which has "the" as its
;;; quantifier, it must be guaranteed that there is only one object which
;;; serves the given role of the thing to be inverse served, and that the
;;; object started with is the object that serves that role.  The function
;;; `unique-value-of-role-p' performs that operation.

(defun unique-value-of-role-p (object-serving-role role object)
  (multiple-value-bind (served-object expiration)
      (serve-unique-item-or-evaluation-value-of-role role object nil nil)
    (prog1
	(and expiration (eq object-serving-role served-object))
      (when expiration
	(reclaim-if-evaluation-value served-object)))))


;; The following 2 functions are for testing purposes.
;
;(defun list-served-items (role domain)
;  (loop with value
;	with expiration
;	with continuation
;	with values-served
;	initially (multiple-value-setq (value continuation expiration)
;		    (serve-first-item-or-temporary-constant-of-role role domain))
;	do
;    (if expiration
;	(push value values-served))
;    (if continuation
;	(multiple-value-setq (value continuation expiration)
;	  (serve-next-item-or-temporary-constant-of-role continuation))
;	(return (nreverse values-served)))))
;
;(defun list-served-inverse-items (object quantifier role domain)
;  (loop with value
;	with expiration
;	with continuation
;	with values-served
;	initially (multiple-value-setq (value continuation expiration)
;		    (serve-first-value-of-role-inverse object quantifier
;						       role domain))
;	do
;    (if expiration
;	(push value values-served))
;    (if continuation
;	(multiple-value-setq (value continuation expiration)
;	  (serve-next-value-of-role continuation))
;	(return (nreverse values-served)))))






;;;; Slot Value Reclaimer for role-cache




;; <specific-cache> == (<role-argument> . <cache-list>)
;; <cache-list> == (<serial#> <reference-count> . <frame-list>)
;; <role-argument> == <symbol> | ( <quantifier> . <designation> )

(def-substitution-macro reclaim-one-specific-cache (specific-cache)
  (drop-reference-to-cache-list (cdr specific-cache))
  (reclaim-eval-tree (car specific-cache))	; reclaims role argument
  (reclaim-eval-cons-macro specific-cache))


;; <list-of-specific-caches> == list of <specific-cache>'s

(def-substitution-macro reclaim-one-list-of-specific-caches 
			(list-of-specific-caches)
  (loop for specific-cache in list-of-specific-caches
	do
     (reclaim-one-specific-cache specific-cache))
  (reclaim-eval-list-macro list-of-specific-caches))


;; <role-cache-entry> == (<role-name> . <list-of-specific-caches>)

(def-substitution-macro reclaim-one-role-cache-entry (role-cache-entry)
  (reclaim-one-list-of-specific-caches (cdr role-cache-entry))
  (reclaim-eval-cons-macro role-cache-entry))


;; <role-cache-entries> == (role-cache <entity>)
;; (role-cache <entity>) == list of <role-cache-entry>'s

(def-slot-value-reclaimer role-cache (role-cache-entries)
    (loop for role-cache-entry in role-cache-entries
	  do
       (reclaim-one-role-cache-entry role-cache-entry))
    (reclaim-eval-list-macro role-cache-entries))






;;;; Decaching




;;; The function `decache-roles-for-all-items' is used to remove the role-cache
;;; from all items.

(defun decache-roles-for-all-items ()
  (when role-caching-enabled?
    (decache-roles-for-all-items-1)))

(defun decache-roles-for-all-items-1 ()
  (loop for item being each class-instance of 'item
	for role-cache? = (role-cache item)
	do
    (when role-cache?
      (reclaim-role-cache-value role-cache? nil)
      (setf (role-cache item) nil))))



;;; The variable `list-of-connection-roles' contains the list of
;;; connection role names which can exist.  This list should be updated
;;; if and when new connection roles are added.

(defvar list-of-connection-roles '(connected-to
				    at-an-input
				    at-an-output
				    at-port
				    at-input-end
				    at-output-end
				    at-either-end))


;;; The function `decache-connection-roles' takes an entity and decaches it.


(defun decache-connection-roles (entity)
  (when role-caching-enabled?
    (decache-connection-roles-1 entity)))

(defun decache-connection-roles-1 (entity)
  ;; Could be made more efficient if a list of roles to be deleted were
  ;; not generated using new conses.  (Each role to be decached can be
  ;; spliced out and linked to form a list of roles-entires-to-be-removed.)
  (loop with role-entries-to-remove = nil
	for role-cache-entry in (role-cache entity)
	do
    (if (memq (car role-cache-entry) list-of-connection-roles)
	(setq role-entries-to-remove
	      (eval-cons role-cache-entry
			 role-entries-to-remove)))
	finally
	  (loop for entry in role-entries-to-remove
		do
	    (setf (role-cache entity)
		  (delete-eval-element entry (role-cache entity)))
	    (reclaim-one-role-cache-entry entry))
	  (reclaim-eval-list-macro role-entries-to-remove)))




;;; Decache-roles-for-entities-related-to-this-connection calls
;;; search-for-directly-connected-entities-for-connection to collect entities in
;;; the special variable things-that-affect-this-formula.  Note that nothing is
;;; done if the system is not running which means that decaching must also
;;; happen upon deactivation (system reset).  Decaching should happen just prior
;;; to the action which changes the connection.  Thus,
;;; decache-roles-for-entities-related-to-this-connection is called at the
;;; beginning of add-connection-in-block, delete-connection-in-block, and
;;; replace-connection-in-block in the same place where
;;; update-runtime-structures-according-to-edit (the decaching function for the
;;; simulator) is called.  It is also called in insert-junction.  Note also that
;;; the requirement that decaching happen just prior to the change of the
;;; connection is in contrast to calls to
;;; update-runtime-structures-according-to-edit (decaching for simulator) which
;;; can be called just about any time, both before and after the change.  This
;;; is because update-runtime-structures-according-to-edit simply notes
;;; variables which must be derived.  The decaching and recaching is done later
;;; at the beginning of simulate-one-cycle (by
;;; handle-editing-changes-effecting-simulation), and thus after the connection
;;; has been changed.

(defvar connections-to-be-excluded?)

(defvar entities-to-be-excluded?)

(defvar entities-or-triples-found-in-search)



;;; The macro `searching-connections' manages the search state information
;;; around calls to connection searching function.

;;; This binds connections-to-be-excluded?, entities-to-be-excluded?, and
;;; entities-or-triples-found-in-search, all to nil, around body.  After
;;; evaluating body, connections-to-be-excluded? and entities-to-be-excluded?
;;; are reclaimed, as well as each element having its search mark bit cleared.
;;; Note, however, that entities-or-triples-found-in-search is not reclaimed.
;;;
;;; This returns the result of evaluating body.
;;;
;;; Note that it is not allowed to be called recursively or reentrantly, and in
;;; development it checks for recursive or reentrant calls.  It is also not
;;; allowed to be exited nonlocally (no calls to stack-error, and, of course, no
;;; internal errors allowed).  If it is exited nonlocally, it will not corrupt
;;; the KB permanently, but will make connection searching invalid during the
;;; current session for the current KB only (reloading a new KB, or reloading
;;; the same KB from a save, will solve any resulting problems).  In development
;;; only there are checks to signal an error when there's a recursive or
;;; reentrant call, or a nonlocal exit.

(defmacro searching-connections ((&rest options) &body body)
  (declare (ignore options))		; none for now, maybe later
  `(progn
     #+development
     (when (or (boundp 'connections-to-be-excluded?)
	       (boundp 'entities-to-be-excluded?))
       (cerror "Continue anyway"
	       "Searching-connections macro invoked recursively or reentrantly, which is not allowed."))
     (let ((connections-to-be-excluded? nil)
	   (entities-to-be-excluded? nil)
	   (entities-or-triples-found-in-search nil))
       (unwind-protect-for-development
	   searching-connections	; checks/tags nonlocal exit in development
	   (progn . ,body)
	 (clear-connections-to-be-excluded connections-to-be-excluded?)
	 (clear-entities-to-be-excluded entities-to-be-excluded?)))))

(defun decache-roles-for-entities-related-to-this-connection (connection)
  (when (and (or system-is-running
		 system-has-paused)
	     role-caching-enabled?)
    (decache-roles-for-entities-related-to-this-connection-1 connection)))

(defun decache-roles-for-entities-related-to-this-connection-1 (connection)
  (loop with things-that-affect-this-formula = nil
	with note-things-encountered-during-role-service? = t
	as direction-to-try = 'input then 'output
	as block
	   = (case direction-to-try
	       (input (output-end-object connection))
	       (t				; output
		(input-end-object connection)))
	when (of-class-p block 'item)
	  do (searching-connections ()
	       (search-for-directly-connected-entities-for-connection
		 block 'object connection nil nil nil nil t)
	       (reclaim-eval-list entities-or-triples-found-in-search))
	    
	until (eq direction-to-try 'output)
	finally
	  (progn
	    (loop for entity-or-connection in things-that-affect-this-formula
		  do
	      (cond
		((framep entity-or-connection)
		 (decache-connection-roles entity-or-connection))
		(t				; if connection
		 (let ((connection-frame?
			 (connection-frame-or-class entity-or-connection)))
		   (when (framep connection-frame?)
		     (decache-connection-roles connection-frame?))))))
	    (reclaim-eval-list things-that-affect-this-formula))))




;;; warning-for-null-domain 

(defun warning-for-null-domain (role)
  (write-warning-message* 1
    (tprinc "Cannot evaluate \`")
    (print-role role)
    (tprinc "\' of something which cannot be found."))
  (values nil nil nil))








;;;; Role Server for Names and Named By




;;; The following role is used to get the name of an object.  The name is
;;; returned as a symbolic temporary constant.  If there is no name, no value is
;;; served.  If there is a list of names for this object, then the first one is
;;; served and the rest are bundled into a continuation which is also served.
;;; Note that this role has the property `first-value-ok-for-the', so that if
;;; there is more than one name for an object, the first will be used in cases
;;; where only one is required.  Note that at this time only entities have
;;; names, but that soon everything from block on down will have them.

(def-first-value-ok-for-the name)

(def-role-printer name 
  (print-role-whose-car-is-role-server role local-variable?))

(def-role (name symbol ((class item))) (role domain)
  (declare (ignore role))
  (let ((name-or-names (name-or-names-for-frame domain)))
    (cond
      ((null name-or-names)
       (values nil nil nil))
      ((consp name-or-names)
       (values (make-evaluation-symbol (car-of-cons name-or-names))
	       (if (cdr-of-cons name-or-names)
		   (eval-cons
		     #'serve-next-name-of-entity
		     (copy-list-using-eval-conses
		       (cdr-of-cons name-or-names)))
		   nil)
	       'never))
      (t
       (values (make-evaluation-symbol name-or-names)
	       nil
	       'never)))))

(defun serve-next-name-of-entity (continue? continuation)
  (if (not continue?)
      (reclaim-eval-list continuation)
      (let ((instance-cons (cdr-of-cons continuation)))
	(cond ((null instance-cons)
	       (reclaim-eval-cons-macro continuation)
	       (values nil nil nil))
	      ((null (cdr-of-cons instance-cons))
	       (values (make-evaluation-symbol
			 (prog1 (car-of-cons instance-cons)
			   (reclaim-eval-list-given-tail
			     continuation instance-cons)))
		       nil
		       'never))
	      (t
	       (values (make-evaluation-symbol
			 (prog1 (car instance-cons)
			   (setf (cdr continuation) (cdr-of-cons instance-cons))
			   (reclaim-eval-cons-macro instance-cons)))
		       continuation
		       'never))))))




;;; The `named-by' role is served by the function serve-first-entity-named-by.

;;; Note that this is the first role server that can call for current value
;;; evaluation. Hence it can get into datum-evaluation.

(def-first-value-ok-for-the named-by)

(def-role-printer named-by 
  (print-standard-two-element-role role local-variable? " named by"))

;;; Some code in the following was merged back in from 1996 code
;;; since it is needed by the Graphs capability. - jpg 8/10/00

(def-role (named-by nil (symbol)) (role domain)
  (let* ((class (car-of-cons (cdr-of-cons role)))
	 (class-description (class-description class))
	 (symbol-name?
	   (coerce-to-symbol-for-named-by-role role domain class))
	 (frame-or-frames?
	   (and symbol-name?
		(frame-or-frames-with-this-name symbol-name?))))
    (cond ((null symbol-name?)
	   (values nil nil nil))
	  ((or (null class-description)
	       (not (class-description-of-class-p class-description 'item))
	       (null frame-or-frames?))
	   (values nil nil nil))
	  ((consp frame-or-frames?)
	   (serve-all-unreprocessed-frames
	     (loop for frame in frame-or-frames?
		   if (frame-of-class-description-p
			frame class-description)
		     collect frame using eval-cons)))
	  ((and (frame-of-class-description-p
		  frame-or-frames? class-description)
		(serve-item-p frame-or-frames?))
	   (values frame-or-frames? nil 'never))
	  (t
	   (values nil nil nil)))))


;;; The function `coerce-to-symbol-for-named-by-role' is used in the 
;;; named-by role.  It data-seeks when necessary.  This code was brought
;;; back from 1996 code and then updated as needed since it is needed
;;; by the Graphs capability. - jpg 8/10/00

(defun coerce-to-symbol-for-named-by-role (role domain class-name)
  (let ((symbol-name? nil) value (expiration? nil) type)
    (cond ((null domain) (warning-for-null-domain role))
	  ((symbolp domain)
	   (return-from coerce-to-symbol-for-named-by-role domain))
	  ((temporary-constant-p domain)
	   (if (eq (constant-type domain) 'symbol)
	       (setq symbol-name? (cached-constant-value domain))
	       (warning-message*
		 1
		 "Attempting to get the ~a named by ~NC, which is not a symbol."
		 class-name (cached-constant-value domain)
		 (constant-type domain))))
	  ((variable-or-parameter-p domain)
	   (multiple-value-setq (value expiration? type)
	     (if (no-wake-ups-during-role-serving)
		 (get-current-value-for-named-by-without-wake-ups domain)
		 (get-current-value domain nil)))
	   (cond ((null expiration?) nil)
		 ((eq type 'symbol) (setq symbol-name? value))
		 (t
		  (reclaim-if-text-string value)
		  (warning-message*
		    1
		    "Attempting to get the ~a named by ~a, which is ~
		     not a symbolic variable or parameter."
		    class-name domain))))
	  (t
	   (warning-message*
	     1
	     "Attempting to get the ~a named by ~a, which is not a ~
              variable or parameter."
	     class-name domain)))
    symbol-name?))

;;; The following definition was brought back from 1996 code and then updated
;;; as needed since it is needed by the Graphs capability. - jpg 8/10/00

(defun-allowing-unwind get-current-value-for-named-by-without-wake-ups
		       (variable-or-parameter)
  (let (value expiration? type)
    (with-wake-up-management
      (none (value expiration? type) nil)
      (get-current-value variable-or-parameter nil))
    (values value expiration? type)))


;;; The role server `named-by-debugging-name' is used only by inspect.  It
;;; is not designed to be called from generalized callers

(def-role-printer named-by-debugging-name
  (print-standard-two-element-role
    role local-variable? " named by debugging name "))

(def-role (named-by-debugging-name nil ((or symbol text)))
    (role domain)
  (let* ((class (second role))
	 (name-as-string
	   (cond ((evaluation-text-p domain)
		  (evaluation-text-value domain))
		 ((symbolp domain)
		  (symbol-name-text-string domain))
		 (t
		  (error "Named-by for inspect received a value that was not a symbol or text:  ~a."
			 domain))))
	 (frame-to-serve?
	   (loop for frame in all-frames-with-simple-debugging-names
		 when (string-equalw
			name-as-string
			(get-cached-debugging-name frame))
		   do (return frame))))
    (if (and frame-to-serve?
	     (frame-of-class-p frame-to-serve? class)
	     (serve-item-p frame-to-serve?))
	(values frame-to-serve? nil 'never)
	(values nil nil nil))))







;;;; Role Servers for Animation




;;; The role server `nearest' returns the entity of the given class which is
;;; nearest to the domain of the role.  Note that find-nearest-instance-of-
;;; class-to-entity only returns active frames, and so we need not check if it's
;;; active here.

(def-role-printer nearest
  (print-standard-two-element-role role local-variable? " nearest to"))

(def-role nearest (role domain)
  (let* ((class (second role))
	 (class-description? (class-description class))
	 (found-object
	   (if (and class-description?
		    (class-description-of-class-p class-description? 'item))
	       (find-nearest-active-instance-of-class-to-entity
		 class-description? domain)
	       nil)))
    (if found-object
	(values found-object nil 'never)
	(values nil nil nil))))





;;; Find-nearest-active-instance-of-class-to-entity examines all the active,
;;; instances of class class on the same workspace as entity, and returns the
;;; one that is nearest to entity (if there are any), or else nil.

(defun find-nearest-active-instance-of-class-to-entity
    (class-description entity)
  (let ((icon-x (item-x-position entity))
	(icon-y (item-y-position entity))
	(workspace? (get-workspace-if-any entity)))
    (when workspace?
      (loop with nearest-of-class-so-far? = nil
	    with nearest-distance-squared-so-far? = nil
	    as subblock being each subblock of workspace?
	    as x-distance fixnum = (absw (-w icon-x (item-x-position subblock)))
	    as y-distance fixnum = (absw (-w icon-y (item-y-position subblock)))
	    as distance-squared?
	    = (if (and (not (eq subblock entity))
		       (serve-item-p subblock)
		       (frame-of-class-description-p subblock class-description)
		       (or (null nearest-distance-squared-so-far?)
			   (and (<w x-distance
				    nearest-distance-squared-so-far?)
				(<w y-distance
				    nearest-distance-squared-so-far?))))
		  (vector-distance-in-workspace x-distance y-distance))
	    do
	(when (and distance-squared?
		   (or (null nearest-distance-squared-so-far?)
		       (<f distance-squared? nearest-distance-squared-so-far?)))
	  (setq nearest-of-class-so-far? subblock)
	  (setq nearest-distance-squared-so-far? distance-squared?))
	    finally
	      (return nearest-of-class-so-far?)))))




;;; The role `icon-color' returns a temporary constant containing the
;;; color of the object.

(def-role (icon-color symbol) (role domain)
  (declare (ignore role))
  (values (make-evaluation-symbol (icon-color domain))
	  nil
	  'never))




;;; (item-color <color-keyword or region> symbol)

(def-role-printer item-color
  (princ-lowercase (second role))
  (when local-variable? (tprinc " ") (tprinc local-variable?))
  (if (memq (second role)
	    '(icon-color stripe-color text-color
			 background-color foreground-color
			 border-color))
      (tprinc " of")
      ;; This might have been "stripe-color." No way to tell.
      (tprinc " icon-color of")))

(def-role (item-color symbol) (role domain)
  (let ((value (item-color domain (second role))))
    (if value
	(values (make-evaluation-symbol value) nil 'never)
	(values nil nil nil))))




;;; The role `item-x-position' returns a temporary constant which contains the x
;;; position of the item on its workspace.

;; Note that this used to be name with "icon" instead of "item".  The old form
;; is supported for users by parsing it into this role.  -jra 5/30/91

(def-role-printer item-x-position
  (print-role-whose-car-is-role-server role local-variable?))

(def-role (item-x-position integer) (role domain)
  (declare (ignore role))
  (values (make-evaluation-integer (item-x-position domain))
	  nil
	  'never))



;; Note that this used to be name with "icon" instead of "item".  The old form
;; is supported for users by parsing it into this role.  -jra 5/30/91

(def-role-printer item-y-position
  (print-role-whose-car-is-role-server role local-variable?))

(def-role (item-y-position integer) (role domain)
  (declare (ignore role))
  (values (make-evaluation-integer (item-y-position domain))
	  nil
	  'never))




(def-role-printer icon-heading
  (print-role-whose-car-is-role-server role local-variable?))

(def-role (icon-heading number) (role domain)
  (declare (ignore role))
  (cond
    ((not (entity-p domain))
     (values nil nil nil))
    (t
     (values (make-evaluation-quantity (icon-heading domain))
	     nil
	     'never))))




;; Note that this used to be name with "icon" instead of "item".  The old form
;; is supported for users by parsing it into this role.  -jra 5/30/91

(def-role-printer item-width
  (print-role-whose-car-is-role-server role local-variable?))

(def-role (item-width integer) (role domain)
  (declare (ignore role))
  (values (make-evaluation-integer (item-width domain))
	  nil
	  'never))




;; Note that this used to be name with "icon" instead of "item".  The old form
;; is supported for users by parsing it into this role.  -jra

(def-role-printer item-height
  (print-role-whose-car-is-role-server role local-variable?))

(def-role (item-height integer) (role domain)
  (declare (ignore role))
  (values (make-evaluation-integer (item-height domain))
	  nil
	  'never))






;;;; Role server for system attributes




;;; The `serve-system-attribute' role-server returns the value of a system
;;; attribute that is accessible to the user.

;;; System-attribute does not have an inverse role-server.

;; Note that the "text" system attribute of messages was previously handled
;; here.  Now, the "text" attribute is handled in "text-of-attribute" role for
;; message and several other classes.  This solves a grammar conflict between
;; the two roles.  -- I got rid of the old code in comments, since it can be
;; found in the 2.1 sources, and I was getting rid of certain functions it
;; referred to.  (MHD 10/31/91)

;; If the domain is not a g2-array and the user attribute is named length, this
;; role now returns the value of that attribute.  cpm, 8/28/91

;; This role is obsoleted by virtual attributes and category-evaluator
;; interfaces.  FIND ME, JRA!  -jra 8/4/96

(def-role-printer system-attribute
  (declare (ignore local-variable?))
  (tformat "~(~a of~)" (second role)))


;; NOTE: If modifying this code, see the semi-open category system-attribute and
;; the parameter system-attribute-types in GRAMMAR1!!

(def-role (system-attribute item-or-datum ((class item))) (role domain)
  (let ((attribute-name (second role)))
    (case attribute-name
      
      ;; For this to be valid, the slot must be present. This test
      ;; will be used, rather than a capability test.
      ;; jh, 4/25/91.  Added gsi-interface-status and interface-status.
      ((gsi-interface-name gsi-interface-status interface-status)
       (let ((slot-value 
	       (get-slot-value-or-no-slot domain attribute-name)))
	 (cond
	   ((eq slot-value no-slot)
	    (values nil nil nil))
	   ((null slot-value)
	    (values nil nil nil))
	   (t (values
		(cond ((fixnump slot-value) ; gsi-interface-status
		       (make-evaluation-integer slot-value))
		      (t		; symbol, for interface-status and interface-status
		       (make-evaluation-symbol slot-value)))
		nil
		'never)))))
      
      (array-length
       ;; G2-array length or array-length user attribute (?).
       
       ;; Array-length should probably be a reserved-word and not available
       ;; as a user-attribute!!  cpm, 10/1/91
       
       (cond ((g2-array-p domain)
	      (values (make-evaluation-integer (g2-array-length domain))
		      nil 'never))
	     (t
	      (let ((slot-value?
		      (frame-or-evaluation-value-user-attribute-value
			domain attribute-name nil)))
		(if slot-value?
		    (values slot-value? nil 'never)
		    (values nil nil nil)))))))))




;;; The `text-of-attribute role-server' endeavors to return the value of user
;;; attributes and most system-attributes as a temporary constant with constant-
;;; type = TEXT.  (This value could be given to the change-the-text-of-attribute
;;; which will parse the text and change the attribute value.) This role can
;;; access more attributes then change-the-text-of-attribute can modify.  The
;;; role can access system attributes that are normally visible, but not
;;; editable by the user.  These slots accessible in this role include those
;;; that are restricted in run-time G2 or hidden with user-restrictions.

;; NOTES:

;; This role does not have an inverse role-server.

;; Note that we do not need to test for stripped text, since the attribute will
;; have a text of "...".

;; In some cases the parse is not available, for example, in rules and
;; procedures.  In this cases, the text is copied instead of being written from
;; the parse.

;; If an object has a system attribute or system attribute alias whose name is
;; the same as an user attribute, the user attribute value is returned.

;; If there is no system slot or alias system slot for the domain, the slot may
;; be a user attribute, even if this is a system slot for another item class.

;; Some slots are only visible, and so can only be referenced, when NUPEC is
;; authorized and others when NUPEC is not authorized.


;; OPEN ISSUES:

;; Check that the gsi-connection-configuration slot is accessible and changeable
;; in the 3.0!!  This slot was added by JH and AC to
;; changeable-system-attribute-of-frame-p.  cpm, 8/16/91

;; User attributes that contain frames return the printed representation seen in
;; tables.  ??

;; System-attribute-as-text is the old name in pre-3.0.

;; As far as I can tell, there is no grammar in G2 currently to produce the
;; system-attribute-as-text role.  However, we do not currently know that there
;; are not old compilations with this role in them, so runtime support for it
;; remains.  -jra 2/16/94

(def-role-printer system-attribute-as-text
  (declare (ignore local-variable?))
  (tformat "text of the ~(~a of~)" (second role)))

(def-role (system-attribute-as-text text) (role domain)
  (serve-text-of-attribute
    domain (second role)
    nil))				; handle class-qualifier later!
					; (MHD/JRA 2/15/94)

;; Text-of-attribute is the new name in 3.0.  The role now handles both user and
;; system attributes.

(def-role-printer text-of-attribute
  (declare (ignore local-variable?))
  (if (eq (second role) 'text)
      (twrite-string "text of")
      (tformat "text of the ~(~a of~)" (second role))))

(def-role (text-of-attribute text) (role domain)
  (let ((slot-denotation (second-of-long-enough-list role)))
    (if (symbolp slot-denotation)
	(serve-text-of-attribute
	  domain slot-denotation nil)
	(serve-text-of-attribute
	  domain
	  (unqualified-name slot-denotation)
	  (class-qualifier slot-denotation)))))

;;; The function `serve-text-of-attribute' is described in the documentation for
;;; text-of-attribute role-server.

;; Removed level 1 warnings.  Role stack errors are signaled in role-returned-
;; no-values-error.  - cpm, 12/4/92

(defun serve-text-of-attribute (frame attribute-name class-qualifier?)
  ;; Test for a system or user attribute.  Unalias the slot, if necessary.
  (let* ((real-slot-name
	   (unalias-slot-name-if-necessary attribute-name frame))
	 (slot-description
	   ;; can be nil despite name; fix later! (MHD 4/14/04)
	   (get-slot-description-of-frame
	     real-slot-name frame class-qualifier?))
	 (slot-features (if slot-description (slot-features slot-description)))
	 (type-of-slot? (feature-assq 'type slot-features))
	 (unnamed-text-attribute? nil))

    ;; Treat  (TYPE NIL ...) the same as having no type feature:
    (when (and (consp type-of-slot?)
	       (eq (car-of-cons type-of-slot?) 'type)
	       (consp (cdr-of-cons type-of-slot?))
	       (null (car-of-cons (cdr-of-cons type-of-slot?))))
      (setq type-of-slot? nil))

    ;; If no visible slot was found and if the slot was an alias, test for a
    ;; user-attribute with the original name.
    (when (and (null type-of-slot?) (not (eq attribute-name real-slot-name)))
      (setq real-slot-name attribute-name)
      (setq type-of-slot?
	    (get-type-of-slot-if-any
	      frame real-slot-name class-qualifier?)))

    (when (and (eq attribute-name 'text) (not (eq real-slot-name 'text)))
      (setq unnamed-text-attribute? t))

    (cond ((or (null type-of-slot?)
	       ;; If the attribute name is not displayed in the table,
	       ;; it is only ok to access it here if the attribute is
	       ;; referred to as an unnamed text attribute.  That is,
	       ;; the expression is of the form "the text of <item>" and
	       ;; not "the text of the <attribute> of <item>".
	       (and
		 (not unnamed-text-attribute?)
		 (do-not-put-slot-in-attribute-tables-p slot-description t)))
	   (values nil nil nil))
	  
	  ((not (attribute-is-visible-via-the-text-of-p
		  frame attribute-name class-qualifier?))
	   (values nil nil nil))
	  
	  (t
	   (let* ((evaluation-value-writing-target-length?
		    maximum-length-for-user-text-strings)
		  (format-override?
		    (feature-assq 'format-overrride slot-features))
		  (current-ddd.dddd-format? ; special var.
		    (if (and format-override?
			     (eq (second format-override?) 'ddd.dddd-format))
			(third format-override?)))
		  (text-string
		   (make-text-string-representation-for-slot-value-itself
		     frame
		     (get-slot-description-value frame slot-description)
		     type-of-slot?)))
	     ;; nec. due to module ordering issues:
	     (declare (special current-ddd.dddd-format?))
	     (cond ((>f (wide-string-length text-string)
			maximum-length-for-user-text-strings)
		    (warning-message*
		      1
		      "Cannot reference the text of the ~a of ~NF.  The text ~
                       contains ~a characters.  The maximum number of ~
                       characters allowed in text is ~a."
		      attribute-name frame (wide-string-length text-string)
		      maximum-length-for-user-text-strings)
		    (reclaim-text-string text-string)
		    (values nil nil nil))
		   (t
		    (values
		      (make-evaluation-text-reclaiming-argument text-string)
		      nil 'never))))))))






;;;; Role Servers for Connections




;;; The various role servers using connections are defined here.  In general,
;;; this amounts to a search of the schematic via connections.  Although
;;; complicated searches will be possible, the most commonly used role servers
;;; will do very localized searches, usually limited to directly connected
;;; objects.  This brings up the issue of what a directly connected object is.
;;; In the strictest sense, it is the block at the other end of a connection
;;; from the block that is the start of the search.  However, it is desireable
;;; in most cases to bypass certain blocks such as junctions.  These should be
;;; transparent to the search.  As this idea develops, role servers specifying
;;; exactly what classes are transparent will be implemented.  For now, the
;;; default is that junctions are transparent.

;;; Connection frames are not instantiated due to role service.  

;; Currently, the search for entities in the schematic is separated from the
;; serving.  Essentially all the search is performed before serving the first
;; instance.  If this becomes a problem, a more combined technique will have to
;; be used, possibly involving putting some sort of continuation mechanism into
;; the loop paths for connections.

;; Consider implementing some of these as macros.
;; Search-for-directly-connected-entities-for-connection should definitely be
;; a macro.


(defparameter transparent-classes-for-schematic-search
	      '(default-junction invisible-entity connection-post))

(defparameter classes-to-ignore-for-schematic-search
	      '(loose-end))




;;; Search-for-directly-connected-entities takes as arguments an entity and a
;;; class and returns a list (made up of eval conses) of entities of type
;;; class directly connected to entity.  Transparent entities are bypassed.
;;; Connections-to-be-excluded? and entities-to-be-excluded?  (both made up of
;;; eval conses) are used for loop avoidance in the search.  The elements of
;;; each list are marked with connection-found-in-search and
;;; block-found-in-search flags, respectively, to make membership testing
;;; extremely efficient, even with long lists, although these will typically not
;;; grow to be very large.  The current implementation allows for the top-level
;;; entity to be connected to itself and will return the entity on the list in
;;; this case.

;;; IMPORTANT: search-for-directly-connected-entities and other similar "outer"
;;; search functions, namely those that bind connections-to-be-excluded? and
;;; entities-to-be-excluded?, must never be aborted, interrupted, or called from
;;; within any of the "inner" search subfunctions, since they expect all blocks
;;; and connections they encounter to have clear mark bits on entry, and they
;;; must clear any marked bits used during the search on exit.

;;; Junction blocks are transparent except when class is a sub-class of 
;;; 'default-junction and the entity being considered is an instance of 
;;; class.  This allows for designations such as
;;;         "the pipe-junction at the output of valve1"
;;; See also design book notes for 2/29/88. 

;;; Connection frames will be returned if they are of type class.  If a 
;;; connection frame is encountered along a path of the search and is returned,
;;; then search along that path is stopped.  Thus, connection frames are not 
;;; "transparent".  The reason for this is to prevent multiple connection frames
;;; being found if the source expression is, for example
;;; " the flow-rate of the pipe at port1 of tank1 "
;;; and the connection at port1 branches into multiple connections, each of 
;;; which could have connection frames.  There is usually no loss of
;;; information with returning just the first one since typically, connection
;;; frames for connections joined by a junction will all have the same values.
;; See also design book notes for 2/15/88.

;;; The directionality? argument can be 'input, 'output, or nil.  If it is
;;; non-nil, the search will stop only at directed connections which don't 
;;; satisfy this directionality? argument;  it will not stop at non-directed
;;; connections.  As mentioned, transparent entities such as junctions are 
;;; bypassed.  In this case, search-for-directly-connected-entities-rec calls
;;; itself recursively, resulting in a depth-first exhaustive search.
;;; If the directionality? argument is nil and a directed connection is
;;; encountered during the search, then all recursive calls to
;;; search-for-directly-connected-entities-rec from that connection will have
;;; a non-nil directionality? argument so that the search proceeds along
;;; connections which conform to the directed connection.

;;; If also-get-port-and-direction-info? is non-nil,
;;; then triples of entity, port-names, and direction will be returned.
;;; This is used by inverse role servers to make sure that the entity satisfies
;;; the pattern specified by the role.  
;;; Port-names are the port names corresponding to the connection for the
;;; entity.  Direction is non-nil only if the connection is directed. 
;;; If this is the case, it is the direction with respect to the entity being
;;; returned.  Also-get-port-and-direction-info? can have four values:
;;; nil, 'port-names, 'directionality, or 'both.  If the value is 'port-name,
;;; then the inverse role server only cares about the port name, not the 
;;; directionality, and search-for-directly-connected-entities must be 
;;; sure not to return more than one triple with the same entity and port names.
;;; Similarly, if the value is 'directionality,
;;; search-for-directly-connected-entities
;;; must not to return more than one triple with the same entity and
;;; directionality.  Finally, if the value is 'both, 
;;; search-for-directly-connected-entities must not return more than one triple
;;; with the same entity, port names, and directionality.  The value of
;;; also-get-port-and-direction-info? will never change during the search.
;; See also design book notes for 2/15/88.

;;; The argument required-connection-directionality-for-inverse-role-service? is
;;; used by inverse role servers for at-input-end, at-output-end, and
;;; at-either-end to ensure that the connection of the connection-frame meets
;;; the directional requirements specified in the role. 

;;; Note that search-for-directly-connected-entities checks whether the entity
;;; is an object or a connection frame and handles each appropriately.  
;;; If it is a connection frame, the original-port-name? and
;;; original-port-directionality? arguments are meaningless.
;;; Search will proceed from either or both ends of 
;;; the connection for the connection frame depending on the directionality? 
;;; argument.  The case of the entity being a connection frame can be quite
;;; common in some applications.  It occurs for forward role service for roles
;;; at-input-end, at-output-end, and at-either-end, and can occur for inverse
;;; role service for any of the connection roles (connected-to, at-an-input,
;;; at-an-output, at-port, at-input-end, at-output-end, and at-either-end).
;;; For example, in the rule
;;;   "if the flow-rate of any pipe at an input to tank-1 ..."
;;; if focus is on pipe, then inverse role service begins with a pipe connection
;;; frame.  See also test cases 6 and 7 in agh>connection-frames-test.kb. 

;;; Connections-in-connection-paths contains a list of connection frame paths.
;;; Each connection frame path is a list of connection frames corresponding to the
;;; search path used to find the corresponding entity in
;;; entities-or-triples-found-in-search.  Connections-in-connection-paths is set
;;; by search-for-directly-connected-entities-for-connection if
;;; do-not-stop-search-at-connections?  is 'save-path.  This feature is currently
;;; used only by GSPAN (see get-info-for-connection-and-entity).



(def-system-variable connections-in-connection-paths ROLES nil)

(def-system-variable current-connection-path ROLES nil)



(def-substitution-macro class-transparent-p (class)
  (loop for transparent-class 
	    in transparent-classes-for-schematic-search
	thereis (subclassp class transparent-class)))

(defun-substitution-macro note-entity-to-be-excluded (entity)
  #+development
  (when (block-found-in-search-p entity)
    (cerror "continue anyway"
	    "Bad: a block (~s) is being doubly marked during connection search!"
	    entity))
  (set-block-found-in-search entity)
  (eval-push entity entities-to-be-excluded?))

(defun-substitution-macro note-connection-to-be-excluded (connection)
  #+development
  (when (connection-found-in-search-p connection)
    (cond
      ((memq connection connections-to-be-excluded?) ; see note! (MHD 3/24/04)
;       (dwarn "A connection (~s) is being multiply marked, but ~
;               this appears to be at worst an inefficiency, not a corruption."
;	      connection)
       )
      (t
       (cerror "continue anyway"
	       "Bad: a connection (~s) is being doubly marked during connection search!"
	       connection))))
  (set-connection-found-in-search connection)
  (eval-push connection connections-to-be-excluded?))

;; Note: we allow multiple marking for connections just in the case where the
;; connection is in the current list connections-to-be-excluded? we're
;; maintaining in the searching-connections dynamic scope. That seems to have
;; always have happened, i.e., prior to the implementation change to use mark
;; checking rather than list membership (in 8.0).  The connection may be pushed
;; n times into the list connections-to-be-excluded?, but all conses will be
;; reclaimed at the end. Note that the complimentary case for blocks is not
;; known to exist, so there's no similar case in
;; note-block-to-be-excluded. HQ-4741703 "NOTE-CONNECTION-TO-BE-EXCLUDED trapped
;; in development (internals)" (MHD 3/24/04)


(defun clear-entities-to-be-excluded (entities)
  #+development
  (loop for entity in entities
	unless (block-found-in-search-p entity)
	  do (cerror "continue anyway"
		     "Bad: a block (~s) is being doubly cleared after connection search!"
		     entity))
  (clear-blocks-found-in-search entities)
  (reclaim-eval-list entities))

(defun clear-connections-to-be-excluded (connections)
  #+development
  (loop for connection in connections
	unless (connection-found-in-search-p connection)
	  do (cerror "continue anyway"
		     "Bad: a connection (~s) is being doubly cleared after connection search!"
		     connection))
  (clear-connections-found-in-search connections)
  (reclaim-eval-list connections))





(defun-substitution-macro note-entity-and-connection-to-be-excluded
    (entity connection)
  (note-entity-to-be-excluded entity)
  (note-connection-to-be-excluded connection))

(defun-substitution-macro search-excluding-entity-and-connection
			(entity connection class
			 directionality? directionality
			 also-get-port-and-direction-info?
			 required-connection-directionality-for-inverse-role-service?
			 do-not-stop-search-at-connections?)
  (note-entity-and-connection-to-be-excluded entity connection)
  (search-for-directly-connected-entities-rec
    entity class
    (or directionality? directionality)
    also-get-port-and-direction-info?
    required-connection-directionality-for-inverse-role-service?
    do-not-stop-search-at-connections?))

;; The substitution macros search-excluding-entity-and-connection, and
;; search-from-connection-post are called with many arguments that could
;; theoretically be omitted since these macros are all called from within
;; search-for-directly-connected-entities-for-connection.  While this would reduce
;; some clutter, it does not conform to strict function syntax.





(defun search-from-origin-entity
    (entity class 
	    directionality? also-get-port-and-direction-info?
	    required-connection-directionality-for-inverse-role-service?
	    do-not-stop-search-at-connections?
	    original-port-name? original-port-directionality?)
  (cond
    (original-port-name?
     (loop for connection being each connection of entity
	   at-port original-port-name?
	   for connection-frame = (connection-frame-or-class connection)
	   do
       (when (or (null (and (framep connection-frame)
			    (frame-of-class-p connection-frame 'item)))
		 (serve-item-p connection-frame))
	 (search-for-directly-connected-entities-for-connection
	   entity class connection
	   directionality? also-get-port-and-direction-info? nil
	   required-connection-directionality-for-inverse-role-service?
	   do-not-stop-search-at-connections?))))
    ((eq original-port-directionality? 'input)
     (loop for connection being each input-connection of entity
	   for connection-frame = (connection-frame-or-class connection)
	   do
       (when (or (null (and (framep connection-frame)
			    (frame-of-class-p connection-frame 'item)))
		 (serve-item-p connection-frame))
	 (if (connection-directed? connection)
	     (search-for-directly-connected-entities-for-connection
	       entity class connection
	       'input also-get-port-and-direction-info? nil
	       required-connection-directionality-for-inverse-role-service?
	       do-not-stop-search-at-connections?)))))
    ((eq original-port-directionality? 'output)
     (loop for connection being each output-connection of entity
	   for connection-frame =(connection-frame-or-class connection)
	   do
       (when (or (null (and (framep connection-frame)
			    (frame-of-class-p connection-frame 'item)))
		 (serve-item-p connection-frame))
	 (if (connection-directed? connection)
	     (search-for-directly-connected-entities-for-connection
	       entity class connection
	       'output also-get-port-and-direction-info? nil
	       required-connection-directionality-for-inverse-role-service?
	       do-not-stop-search-at-connections?)))))
    (t
     (search-for-directly-connected-entities-rec
       entity class 
       directionality? also-get-port-and-direction-info?
       required-connection-directionality-for-inverse-role-service?
       do-not-stop-search-at-connections?))))



(defmacro search-from-entity-1
	  (entity class
	   directionality? also-get-port-and-direction-info?
	   required-connection-directionality-for-inverse-role-service?
	   do-not-stop-search-at-connections?
	   original-port-name? original-port-directionality?)
  (if (or original-port-name? original-port-directionality?)
      `(search-from-origin-entity
	 ,entity ,class
	 ,directionality? ,also-get-port-and-direction-info?
	 ,required-connection-directionality-for-inverse-role-service?
	 ,do-not-stop-search-at-connections?
	 ,original-port-name? ,original-port-directionality?)
      `(search-for-directly-connected-entities-rec
	 ,entity ,class 
	 ,directionality? ,also-get-port-and-direction-info?
	 ,required-connection-directionality-for-inverse-role-service?
	 ,do-not-stop-search-at-connections?)))



(defmacro connection-post-search-2
	  (connection-post class
	   directionality? also-get-port-and-direction-info?
	   required-connection-directionality-for-inverse-role-service?
	   do-not-stop-search-at-connections?
	   original-port-name? original-port-directionality?)
  `(let ((superior-connection-and-end 
	   (superior-connection-cache ,connection-post)))
     (search-from-entity-1
       ,connection-post ,class
       ,directionality? ,also-get-port-and-direction-info?
       ,required-connection-directionality-for-inverse-role-service?
       ,do-not-stop-search-at-connections?
       ,original-port-name? ,original-port-directionality?)
     (when (and superior-connection-and-end
		(not ,original-port-name?))
       (loop with superior-connection = (cdr superior-connection-and-end)
	     for superior-connection-frame = (connection-frame-or-class superior-connection)
	     with connection-end = (car superior-connection-and-end)
	     with required-direction? = (or ,original-port-directionality?
					    ,directionality?)
	     as direction-to-try = 'input then 'output
	     do
	 (when
	   (and
	     (or
	       (and (null ,original-port-directionality?)
		    (or (connection-not-directed? superior-connection)
			(null required-direction?)))
	       (and (or (null ,original-port-directionality?)
			(connection-directed? superior-connection))
		    (eq required-direction? direction-to-try)
		    (if (eq direction-to-try 'input)
			(eq connection-end 'output)
			(eq connection-end 'input))))
	     (or (null (and (framep superior-connection-frame)
			    (frame-of-class-p superior-connection-frame 'item)))
		 (serve-item-p superior-connection-frame)))

	   (search-for-directly-connected-entities-for-connection
	     (case direction-to-try
	       (input (output-end-object superior-connection))
	       (t				; output
		(input-end-object superior-connection)))
	     ,class superior-connection
	     required-direction? 
	     ,also-get-port-and-direction-info?
	     nil
	     ,required-connection-directionality-for-inverse-role-service?
	     ,do-not-stop-search-at-connections?))
	     until (eq direction-to-try 'output)))))

;; Args are assumed to always be symbols.



;;; The macro `connection-post-search' applies search-operator, a function or
;;; macro, to connection-post and its "namesakes" (other connection posts with
;;; one or more names in common with it) also passing along to the function the
;;; arguments in search-args, an implicitly quoted list of arguments.  If
;;; connection-post has no name, the operator is only applied connection-post
;;; itself name in common with it.  Otherwise, search-operator is only applied
;;; to the argument connection post.
;;;
;;; Note that this is a nonstandard macro in that the elements of search-args
;;; are evaluated for each connection post visited.
;;;
;;; Each connection post will be visited at most one time.
;;;
;;; [Note: previously, the operator may have been applied more than one time to
;;; each connection post, i.e., if the connection post had more than one name.
;;; That behavior was reviewed, and found to be at best unhelpful and
;;; inefficient! (MHD 6/5/02)]

(defmacro connection-post-search (connection-post search-operator search-args)
  (avoiding-variable-capture (connection-post &aux name name-or-names frame
					      cp-list cp-list-tail cp)
    `(let ((,name-or-names (name-or-names-for-frame ,connection-post))
	   (,cp-list nil)		; keep a list, no duplicates, reclaim at end 
	   (,cp-list-tail nil))
       (if ,name-or-names
	   (do-name-or-names (,name ,name-or-names)
	     (do-frame-or-frames (,frame (frame-or-frames-with-this-name ,name))
	       (when (and (frame-of-class-p ,frame 'connection-post)
			  (not (memq ,frame ,cp-list)))
		 ;; We enqueue in this order to keep the search order compatible
		 ;; with that used in past releases. (MHD 6/5/02)
		 (enqueue-1 ,frame ,cp-list ,cp-list-tail gensym-cons))))
	   (setq ,cp-list (gensym-list ,connection-post)))
       (loop for ,cp in ,cp-list
	     do (,search-operator ,cp ,@search-args))
       (reclaim-gensym-list ,cp-list))))


(defmacro search-from-connection-post
	  (connection-post connection? class
	   directionality? directionality
	   also-get-port-and-direction-info?
	   required-connection-directionality-for-inverse-role-service?
	   do-not-stop-search-at-connections?
	   original-port-name? original-port-directionality?)
  `(progn
     (when ,connection?
       (note-entity-and-connection-to-be-excluded ,connection-post ,connection?))
     (connection-post-search 
       ,connection-post connection-post-search-2
       (,class
	(or ,directionality? ,directionality)
	,also-get-port-and-direction-info?
	,required-connection-directionality-for-inverse-role-service?
	,do-not-stop-search-at-connections?
	,original-port-name? ,original-port-directionality?))))

;; Note that as with entities, a connection post can be given more than one name.
;; Also, more than one connection post can have the same name (this is how they
;; work).





;;; `decache-roles-for-connection-post-and-namesakes' decaches the roles cached
;;; for the argument connection-post and its "namesakes", i.e., other instances
;;; of class CONNECTION-POST that have the same name(s) as the argument.  The
;;; names argument is a name-or-names-for-frame slot value, i.e., a name symbol,
;;; which cannot be nil, or a list (possibly nil, i.e., empty) of name symbols.

(defun decache-roles-for-connection-post-and-namesakes (connection-post names)
  (when role-caching-enabled?
    (decache-connection-roles-1 connection-post)
    
    (let ((namesakes-done-so-far '()))
      (do-name-or-names (name names)
	(do-frame-or-frames (frame (frame-or-frames-with-this-name name))
	  (when (and (frame-of-class-p frame 'connection-post)
		     (not (memq frame namesakes-done-so-far)))
	    (decache-roles-for-connection-post-search frame)
	    (gensym-push frame namesakes-done-so-far))))
      (reclaim-gensym-list namesakes-done-so-far))))

;; The means to avoid multiple calls on the connection post or its namesakes
;; could be much more efficient if necessary, but the total number of namesakes
;; we ever deal with is practically always quite small, typically 2 or 3.  It is
;; not realistically ever going to be a high number, above 50 or so.  So the
;; above test, building a list, and using the memq test, then reclaiming the
;; list, should be quite adequate.  Note, too, that previously there was no test
;; done, so the decache would be performed multiple times on the same
;; frame. (MHD 6/4/02)




(defun decache-roles-for-connection-post (connection-post)
  (when role-caching-enabled?
    (decache-roles-for-connection-post-1 connection-post)))

(defun decache-roles-for-connection-post-1 (connection-post)
  (decache-connection-roles connection-post)
  (connection-post-search 
    connection-post decache-roles-for-connection-post-search nil))

(defun decache-roles-for-connection-post-search (connection-post)
  (loop for connection being each connection of connection-post
	do (decache-roles-for-entities-related-to-this-connection connection))
  (let ((superior-connection-and-end 
	  (superior-connection-cache connection-post)))
    (when superior-connection-and-end
      (decache-roles-for-entities-related-to-this-connection 
	(cdr superior-connection-and-end)))))



(defun search-for-directly-connected-entities
       (entity class original-port-name? original-port-directionality?
	directionality? also-get-port-and-direction-info?
	required-connection-directionality-for-inverse-role-service?
	do-not-stop-search-at-connections?)
  (cond 
    ((frame-of-class-p entity 'connection)
     ;; if entity is a connection frame
     (let ((connection?  ; may be nil if instantiating
	     (connection-for-this-connection-frame entity)))
       (when connection?
	 (loop with entities-or-triples-found-in-both-searches = nil
	       with self-connected? = (eq
					(output-end-object connection?)
					(input-end-object connection?))
	       as direction-to-try = 'input then 'output	       
	       do (searching-connections ()
		    (when (and (or (not directionality?)
				   (eq directionality? direction-to-try))
			       ;;active?
			       (or (null (and (framep entity)
					      (frame-of-class-p entity 'item)))
				   (serve-item-p entity)))

		      (search-for-directly-connected-entities-for-connection
			(case direction-to-try
			  (input
			   (when (and directionality?
				      (not self-connected?))
			     (note-entity-to-be-excluded
			       (output-end-object connection?)))
			   (output-end-object connection?))
			  ;; if it's not an input it's an output
			  (t				    
			   (when (and directionality?
				      (not self-connected?))
			     (note-entity-to-be-excluded
			       (input-end-object connection?)))
			   (input-end-object connection?)))
			class connection?
			directionality? 
			also-get-port-and-direction-info?
			entity
			required-connection-directionality-for-inverse-role-service?
			do-not-stop-search-at-connections?))
		    (setq entities-or-triples-found-in-both-searches
			  (nconc entities-or-triples-found-in-both-searches
				 entities-or-triples-found-in-search)))
	       until (eq direction-to-try 'output)
	       finally (return entities-or-triples-found-in-both-searches)))))
    (t
     (searching-connections ()
       (cond
	 ((frame-of-class-p entity 'connection-post)
	  (search-from-connection-post
	    entity nil class directionality? nil 
	    also-get-port-and-direction-info? 
	    required-connection-directionality-for-inverse-role-service?
	    do-not-stop-search-at-connections?
	    original-port-name? original-port-directionality?))
	 (t
	  (search-from-origin-entity
	    entity class 
	    directionality? also-get-port-and-direction-info?
	    required-connection-directionality-for-inverse-role-service?
	    do-not-stop-search-at-connections?
	    original-port-name? original-port-directionality?)))
       (setq entities-or-triples-found-in-search
	     (delete-item-from-list-and-reclaim-cons-cells
	       entities-or-triples-found-in-search entity 'reclaim-eval-cons-function t))
       entities-or-triples-found-in-search))))

;;; This special variable was used by `search-for-directly-connected-entities-rec'
;;; to stop the loop in the middle, when the first node was found. But this functionality
;;; was controlled by another system variable `there-exists-p' in function
;;; `note-entity-found-in-directly-connected-search' when recording search results.
;;; -- Chun Tian (binghe), 2012/09/16

(defvar do-not-stop-search-once-found? t)

;; Note that if original-port-directionality? is non-nil, search will proceed
;; along a connection only if it is directed.

(defun search-for-directly-connected-entities-rec
       (entity class 
	directionality? also-get-port-and-direction-info?
	required-connection-directionality-for-inverse-role-service?
	do-not-stop-search-at-connections?)
  (loop for connection being each connection of entity
	for connection-frame = (connection-frame-or-class connection)
	do
       (when (or (null (and (framep connection-frame)
			    (frame-of-class-p connection-frame 'item)))
		 (serve-item-p connection-frame))
	 (let ((do-not-stop-search-once-found? t))
	   (search-for-directly-connected-entities-for-connection
	     entity class connection
	     directionality? also-get-port-and-direction-info? nil
	     required-connection-directionality-for-inverse-role-service?
	     do-not-stop-search-at-connections?)
	   (unless do-not-stop-search-once-found? (loop-finish))))))

(defun search-for-directly-connected-entities-for-connection
       (entity class connection
	directionality? also-get-port-and-direction-info?
	connection-frame-to-ignore?
	required-connection-directionality-for-inverse-role-service?
	do-not-stop-search-at-connections?)
  (cond
    ((eq do-not-stop-search-at-connections? 'save-path)
     (eval-push 
       (get-or-make-connection-frame-and-activate-if-appropriate
	 connection)
       current-connection-path)
     (search-for-directly-connected-entities-for-connection-1
       entity class connection
       directionality? also-get-port-and-direction-info?
       connection-frame-to-ignore?
       required-connection-directionality-for-inverse-role-service?
       do-not-stop-search-at-connections?)
     (eval-pop current-connection-path))
    (t
     (search-for-directly-connected-entities-for-connection-1
       entity class connection
       directionality? also-get-port-and-direction-info?
       connection-frame-to-ignore?
       required-connection-directionality-for-inverse-role-service?
       do-not-stop-search-at-connections?))))



(defmacro bypass-connection-post-in-search (class connection-post-class)
  `(or (not (subclassp ,class 'connection-post))
       (not (subclassp ,connection-post-class ,class))))

(defmacro bypass-junction-in-search (class junction-class)
  `(or (not (subclassp ,class 'default-junction))
       (not (subclassp ,junction-class ,class))))

;; Class is always assumed to be a symbol.




(defun search-for-directly-connected-entities-for-connection-1
    (entity class connection
	    directionality? also-get-port-and-direction-info?
	    connection-frame-to-ignore?
	    required-connection-directionality-for-inverse-role-service?
	    do-not-stop-search-at-connections?)
  (when (add-frame-to-things-that-affect-if-appropriate entity)
    (add-to-things-that-affect-if-appropriate connection)
    (when (and (not (connection-found-in-search-p connection))
	       (framep
		 (get-block-at-other-end-of-connection
		   connection entity)))
      (let* ((entity-at-other-end
	       (get-block-at-other-end-of-connection
		 connection entity))
	     (class-of-entity-at-other-end
	       (class entity-at-other-end))
	     (connection-frame-or-class	       ;
	       (connection-frame-or-class connection))
	     (connection-class
	       (if (framep connection-frame-or-class)
		   (class connection-frame-or-class)
		   connection-frame-or-class))
	     (directionality nil))
	(when (not (block-found-in-search-p entity-at-other-end))
	  (when (or (connection-not-directed? connection)
		    (if directionality?
			(if (eq directionality? 'input)
			    (eq (output-end-object connection) entity)
			    (eq (input-end-object connection) entity))
			(progn
			  ;; If connection is directed and no directionality
			  ;; is specified, set directionality so that all
			  ;; recursive search from this connection corresponds
			  ;; to the connection.  Note that both directionality?
			  ;; and directionality can be nil if the connection is
			  ;; not directed.
			  
			  (setq directionality
				(if (eq (output-end-object connection) entity)
				    'input
				    'output))
			  t)))
	    ;; If connection-class is subclass of class name, return
	    ;; connection frame for connection.  If the connection frame
	    ;; doesn't exist, instantiate it.  Note that this stops the
	    ;; search along this path and no further entities (either
	    ;; objects or connection frames) are returned unless
	    ;; do-not-stop-search-at-connections? is non-nil.  If it is
	    ;; non-nil, search will continue.
	    (progn
	      ;; prior to today a recursive search was not guaranteed to start up
	      ;; if connection was to junction blocks -rdf, 7/20/94
	      (when (and (subclassp (class entity) 'default-junction)
			 (bypass-junction-in-search
			   class (class entity)))
		(unless (block-found-in-search-p entity)
		  (search-excluding-entity-and-connection
		    entity connection class
		    directionality? directionality
		    also-get-port-and-direction-info?
		    required-connection-directionality-for-inverse-role-service?
		    do-not-stop-search-at-connections?)))
	      (cond
		((and
		   ;; The check for the class not being item was added because
		   ;; connection-class is a subclass of item (although before
		   ;; item extensibility that test was designed to catch only
		   ;; connection classes) and serve up only the connection and
		   ;; none of the non-connection connected items.  (ghw 8/27/96)
					;(not (eq class 'item))
		   (subclassp connection-class class)
		   (not (eq (connection-frame-or-class connection)
			    connection-frame-to-ignore?))
		   (case
		       required-connection-directionality-for-inverse-role-service?
		     (output (eq (input-end-object connection) entity))
		     (input (eq (output-end-object connection) entity))
		     (t t)))
		 (let ((connection-frame
			 (get-or-make-connection-frame-and-activate-if-appropriate
			   connection)))
		   (when (add-frame-to-things-that-affect-if-appropriate
			   connection-frame)
		     (eval-push 
		       (if also-get-port-and-direction-info?
			   (eval-list connection-frame nil nil)
			   connection-frame)
		       entities-or-triples-found-in-search)
		     (note-connection-to-be-excluded connection)
		     (if do-not-stop-search-at-connections?
			 ;; search for more connection frames?
			 ;; Note that since class is a connection
			 ;; class, don't have to check if class is a
			 ;; default-junction as is done below.
			 (when (class-transparent-p
				 class-of-entity-at-other-end)
			   (search-excluding-entity-and-connection
			     entity-at-other-end connection class
			     directionality? directionality
			     also-get-port-and-direction-info?
			     required-connection-directionality-for-inverse-role-service?
			     do-not-stop-search-at-connections?))
			 (return-from search-for-directly-connected-entities-for-connection-1)
			 ))))
		((memq class-of-entity-at-other-end
		       classes-to-ignore-for-schematic-search)
		 ;; Search along this path stops.  An explicit test here is
		 ;; actually unnecessary but improves efficiency in certain
		 ;; cases.
		 )
		
		((and (subclassp class-of-entity-at-other-end 'connection-post)
		      (bypass-connection-post-in-search 
			class class-of-entity-at-other-end)
		      ;; Don't go into connections which are not subclass of current connection class
		      (or (not (subclassp class 'connection))
			  (subclassp connection-class class)))
		 (search-from-connection-post
		   entity-at-other-end connection class
		   directionality? directionality
		   also-get-port-and-direction-info?
		   required-connection-directionality-for-inverse-role-service?
		   do-not-stop-search-at-connections? nil nil))
		
		((and (subclassp class-of-entity-at-other-end 'default-junction)
		      (bypass-junction-in-search
			class class-of-entity-at-other-end))
		 (search-excluding-entity-and-connection
		   entity-at-other-end connection class
		   directionality? directionality
		   also-get-port-and-direction-info?
		   required-connection-directionality-for-inverse-role-service?
		   do-not-stop-search-at-connections?))
		
		((and (subclassp class-of-entity-at-other-end
				 class)
		      (not (block-found-in-search-p entity-at-other-end)))
		 (note-entity-found-in-directly-connected-search
		   entity-at-other-end connection 
		   also-get-port-and-direction-info?))))))
	;; Don't go into connections which are not subclass of current connection class
	(when (or (not (subclassp class 'connection))
		  (subclassp connection-class class))
	  (search-for-subworkspace-connection-posts
	    class connection
	    (or directionality? directionality)
	    also-get-port-and-direction-info?
	    required-connection-directionality-for-inverse-role-service?
	    do-not-stop-search-at-connections?))))))

;; The connection-frame-to-ignore? argument is used only by the at-input-end,
;; at-output-end, and at-either-end role servers so that the original connection
;; frame is not returned.

;; Consider making this a macro even though it is lengthy and used in two
;; places.  It is time critical!!

;; Note that loop path for connections is not used here.  It is not appropriate
;; for such a complicated search.

;; When note-things-encountered-during-role-service?  is non-nil, the argument
;; entity and connection are always added to the set
;; things-that-affect-this-formula.  If a connection frame is encountered, that
;; too is added to this set.  Note however that connection frames for
;; connections that have been added to this set are not necessarily added to the
;; set themselves.  This is logically correct since in such cases, editing the
;; connection frame in no way changes the role.  Note that this simple mechanism
;; takes care of noting all entities and connections encountered during role
;; service for any of the connection related roles.  This is because they all
;; use search-for-directly-connected-entities which uses
;; search-for-directly-connected-entities-for-connection.  Thus, noting the
;; argument entity and connection, connection frames encountered, and
;; entity-at-other-end if not continuing search ensures that all entities and
;; connections for the role are noted.  Note also that it is possible for
;; connections that aren't part of the legitimate role service search path to be
;; added to the set anyway.  This can happen, for example, in certain cases when
;; there is directionality.  This is because the connection is added at the
;; beginning of the function before any directionality checks are made.  This is
;; not a big problem; it means a few extra conses of runtime memory and it may
;; result in some runtime formulas being re-derived when they don't have to be.
;; Consider modifying this brute force approach at some point however.

;; Consider marking entities and connections traversed rather than collecting
;; them in entities-to-be-excluded? and connections-to-be-excluded?.  The only
;; drawbacks to this is that it would require adding new slots to entities and
;; connections, and would require some sort of collection anyway in order to
;; reset the markings.  Also, the speed improvement will typically not be 
;; great since the lists entities-to-be-excluded? and connections-to-be-excluded?
;; are typically short.
;;
;; -- UPDATE: done for entities-to-be-excluded? and connections-to-be-excluded?
;; -- very easily for the entity case by using the BLOCK-FOUND-IN-SEARCH frame
;; flag and related facilities; almost as simple for connections by defining
;; CONNECTION-FOUND-IN-SEARCH as the connection-flag analog of
;; BLOCK-FOUND-IN-SEARCH. (MHD 1/28/04)



(defun note-entity-found-in-directly-connected-search 
       (entity-found connection also-get-port-and-direction-info?)
  (when (add-frame-to-things-that-affect-if-appropriate
	  entity-found)
    (when current-connection-path
      (eval-push
	(copy-list-using-eval-conses current-connection-path)
	connections-in-connection-paths))
    (cond
      (also-get-port-and-direction-info?
       (add-port-and-direction-info-triple
	 entity-found
	 connection
	 also-get-port-and-direction-info?))
      ;; Note that in this case, the entity is not added to
      ;; entities-to-be-excluded since there may be other ports
      ;; (other triples) for this entity.
      (t
       (note-entity-to-be-excluded entity-found)
       (eval-push 
	 entity-found
	 entities-or-triples-found-in-search)))
    ;; When doing the searching under `there-exists-literal', we only need the
    ;; first found entity, set the variable for return in the middle.
    ;; -- Chun Tian (binghe), 2012/09/16
    (when there-exists-p
      (setq do-not-stop-search-once-found? nil))))

;; Also-get-port-and-direction-info? should be a special var.



(defun search-for-subworkspace-connection-posts
       (class connection
	directionality? also-get-port-and-direction-info?
	required-connection-directionality-for-inverse-role-service?
	do-not-stop-search-at-connections?)
  (let ((input-end-subworkspace-connection-posts
	  (getfq (connection-attributes-plist connection) 
		 'input-end-subworkspace-connection-posts))
	(output-end-subworkspace-connection-posts
	  (getfq (connection-attributes-plist connection) 
		 'output-end-subworkspace-connection-posts)))
    (search-for-subworkspace-connection-posts-1 
      input-end-subworkspace-connection-posts class connection
      directionality? also-get-port-and-direction-info?
      required-connection-directionality-for-inverse-role-service?
      do-not-stop-search-at-connections? 'input)
    (search-for-subworkspace-connection-posts-1 
      output-end-subworkspace-connection-posts class connection
      directionality? also-get-port-and-direction-info?
      required-connection-directionality-for-inverse-role-service?
      do-not-stop-search-at-connections? 'output)))

(defun search-for-subworkspace-connection-posts-1 
       (connection-posts class connection
	directionality? also-get-port-and-direction-info?
	required-connection-directionality-for-inverse-role-service?
	do-not-stop-search-at-connections? required-direction)
  (when (or (connection-not-directed? connection)
	    (null directionality?)
	    (eq directionality? required-direction))
    (loop for connection-post in connection-posts
	  do 
      (when (not (block-found-in-search-p connection-post))
	(cond
	  ((bypass-connection-post-in-search 
	     class (class connection-post))
	   (note-entity-to-be-excluded connection-post)
	   (search-from-connection-post
	     connection-post nil class
	     directionality? nil
	     also-get-port-and-direction-info?
	     required-connection-directionality-for-inverse-role-service?
	     do-not-stop-search-at-connections? nil nil))
	  (t
	   (note-entity-found-in-directly-connected-search
	     connection-post connection 
	     also-get-port-and-direction-info?)))))))



(defun add-port-and-direction-info-triple 
    (entity connection port-and-direction-info?)
  (let* ((port-names
	   (get-port-names-for-connection
	     entity connection))
	 (direction-of-connection-for-entity
	   (if (connection-directed? connection)
	       (if (eq (output-end-object connection)
		       entity)
		   'input
		   'output)))
	 (triple-to-add
	   (eval-list entity port-names direction-of-connection-for-entity)))
    (case port-and-direction-info?
      (both
       ;; There is no chance of duplication of all three elements
       ;; so the triple can just be added.
       (eval-push triple-to-add entities-or-triples-found-in-search))
      (t
       (loop for triple in entities-or-triples-found-in-search
	     do
	 (when (eq entity (car triple)) 
	   (if (eq port-and-direction-info? 'port-names)
	       (when (equal port-names (second triple))
		 (reclaim-eval-tree triple-to-add)
		 (return (values)))
	       ;; if port-and-direction-info? is 'directionality
	       (when (eq direction-of-connection-for-entity
			 (third triple))
		 (reclaim-eval-tree triple-to-add)
		 (return (values)))))
	     finally
	       (eval-push triple-to-add entities-or-triples-found-in-search))))))



;; Get-port-names-for-connection returns a list of eval-conses of
;; the port names for a connection.

(defun-simple get-port-names-for-connection (block connection)
  #-connections-v2
  (let ((connections-sublist
	  (get-connections-sublist-for-connection
	    block connection))
	(port-name-list nil))
    (loop for port-name? in connections-sublist
	  while (not (connection-p port-name?))
	  do
      (setq port-name-list
	    (nconc port-name-list
		   (eval-cons port-name? nil))))
    port-name-list)
  ;; GENSYMCID-1834: G2 2015 Aborts when loading some of our applications
  ;;
  ;; In connection-v1, if `block' and `connection' are not connected, this function returns
  ;; NIL. But in connection-v2, the function will crash, now we've fixed it to return NIL.
  #+connections-v2
  (when-let (connection-item
	     (get-connection-item connection (connections block)))
    (copy-list-using-eval-conses
      (case (get-direction-of-connection connection block)
	(input
	 (connection-item-input-names connection-item))
	(t ; output or undirected
	 (connection-item-output-names connection-item))))))

;;; The role server `serve-first-entity-connected-to-domain' performs service
;;; for the non-atomic role `connected-to'.  This role replaces an implied
;;; meaning of the preposition "of" within our grammar.

(def-role-printer connected-to
  (print-standard-two-element-role role local-variable? " connected to"))


(def-role connected-to (role domain)
  (let* ((class (car-of-cons (cdr-of-cons role)))
	 (class-description (class-description class)))
    (cond 
      ((and class-description
	    (class-description-of-class-p class-description 'item))

       (serve-cached-role (domain 'connected-to class)
	 (search-for-directly-connected-entities 
	   domain class nil nil nil nil nil nil)))
      (t
       (warn-of-bad-connected-to-class class domain)
       (values nil nil nil)))))

(defun warn-of-bad-connected-to-class (class domain)
  (warning-message* 1
    "In a reference to a ~a connected to ~nf, ~nf is not a ~a, so no connection ~
     search could be performed."
    class
    domain
    domain
    (if (subclassp class 'item)
	"class that can have connections"
	"defined class")))

(def-role-inverse connected-to
		  (object quantifier role domain-designation)
  (serve-cached-inverse-roles (object quantifier role domain-designation)
    (if (symbolp domain-designation)
	(let* ((frame-or-frames (frame-or-frames-with-this-name
				  domain-designation))
	       (connected-entities
		 (if (listp frame-or-frames)
		     (loop for frame in frame-or-frames
			   nconc (search-for-directly-connected-entities
				   object (class frame) nil nil nil nil nil nil))
		     (search-for-directly-connected-entities
		       object (class frame-or-frames) nil nil nil nil nil nil)))
	       (entities-to-serve nil))
	  (loop for entity in connected-entities
		for name-or-names = (name-or-names-for-frame entity)
		do
	    (when (and (if (consp name-or-names)
			   (memq domain-designation name-or-names)
			   (eq domain-designation name-or-names))
		       (or (neq quantifier 'the)
			   (unique-value-of-role-p object role entity)))
	      (setq entities-to-serve
		    (eval-cons entity entities-to-serve))))
	  (reclaim-eval-list-macro connected-entities)
	  entities-to-serve)
	;; If this is a role named domain, then the only filter available is a
	;; class mentioned in the role of the domain.  Apply this filter while
	;; collecting the set of connected entities.
	(let* ((class? (atomic-class-element-of-designation
			 domain-designation))
	       (connected-entities
		 (if (and class? (subclassp class? 'item))
		     (search-for-directly-connected-entities
		       object class? nil nil nil nil nil nil))))
	  (if (neq quantifier 'the)
	      connected-entities
	      (let ((entities-to-serve nil))
		(loop for entity in connected-entities
		      do
		  (if (unique-value-of-role-p object role entity)
		      (setq entities-to-serve
			    (eval-cons entity entities-to-serve))))
		(reclaim-eval-list-macro connected-entities)
		entities-to-serve))))))

;; Make this more like other inverse role servers?!
;; (use designation-could-denote-item-p?)


;;; The following is a server for 'at-port.  The role is a cons of form
;;; ('at-port port-name class).  All instances of entities of that class
;;; class directly connected to the domain at the port-name will be served.
;;; This role server would be used in evaluating expressions like "any valve
;;; connected at the water-inlet of the pump" which compiles to (any (at-port
;;; water-inlet valve) (the pump)).

(def-role-printer at-port
  (princ-lowercase (third role))
  (when local-variable? (tprinc " ") (tprinc local-variable?))
  (twrite-string " connected at the ")
  (princ-lowercase (second role))
  (twrite-string " of"))

(def-role at-port (role domain)
  (let* ((class (third role))
	 (class-description (class-description class)))
    (cond 
      ((and class-description
	    (class-description-of-class-p class-description 'item))
       (serve-cached-role (domain (first role) (cdr role))
	 (search-for-directly-connected-entities
	   domain class (second role) nil nil nil nil nil)))
      (t
       (warn-of-bad-connected-to-class class domain)
       (values nil nil nil)))))



;;; The following definition and the function
;;; `serve-first-inverse-from-named-port' define the `at-port inverse
;;; role server'.   This role searches the list of all connected
;;; entities of the given object for those which connected to this one
;;; via a port with the name given in the passed role and which could be
;;; denoted by the passed designation.

(def-role-inverse at-port (object quantifier role domain-designation)
  (serve-cached-inverse-roles (object quantifier role domain-designation)
    (let* ((classes? (get-classes-given-designation domain-designation))
	   (port-name (second role))
	   (connected-entities
	     (loop for class in classes?
		   nconc (search-for-directly-connected-entities
			   object class
			   nil nil nil 'port-names nil nil)))
	   (entities-to-serve nil))
      (loop with entity
	    for entity-entry in connected-entities
	    do
	(when (memq port-name (second entity-entry))
	  (setq entity (first entity-entry))
	  (when (and (designation-could-denote-item-p domain-designation entity)
		     (or (neq quantifier 'the)
			 (unique-value-of-role-p object role entity)))
	    (setq entities-to-serve
		  (eval-cons entity entities-to-serve)))))
      (reclaim-eval-list-macro classes?)
      (reclaim-eval-tree connected-entities)
      entities-to-serve)))



;;; The following is a server for 'at-an-input which serves all instances of
;;; entities directly connected to the domain (a entity) at an input port.  The
;;; role is a cons of form ('at-an-input class).  This role server would be
;;; used in evaluating expressions like "any valve at any input of the pump"
;;; which compiles to (any (at-an-input valve) (the pump)).

(def-role-printer at-an-input
  (print-standard-two-element-role 
    role local-variable? " connected at an input of"))

(def-role at-an-input (role domain)
  (let* ((class (second role))
	 (class-description (class-description class)))
    (cond 
      ((and class-description
	    (class-description-of-class-p class-description 'item))
       (serve-cached-role (domain (first role) class)
	 (search-for-directly-connected-entities
	   domain class nil 'input 'input nil nil nil)))
      (t
       (warn-of-bad-connected-to-class class domain)
       (values nil nil nil)))))



;;; The following definition and the function
;;; `serve-first-inverse-from-input-connection' define the `at-an-input
;;; inverse role server'.   This role searches the list of all connected
;;; entities of the given object for those which connected to this one
;;; via an output port and which could be denoted by the passed
;;; designation.

(def-role-inverse at-an-input (object quantifier role domain-designation)
  (serve-cached-inverse-roles (object quantifier role domain-designation)
    (let* ((classes? (get-classes-given-designation domain-designation))
	   (connected-entities
	     (loop for class in classes?
		   nconc (search-for-directly-connected-entities
			   object class nil nil 'output 'directionality
			   nil nil)))
	   (entities-to-serve nil))
      (loop with entity
	    for entity-entry in connected-entities
	    do
	(when (eq (third entity-entry) 'input)
	  (setq entity (first entity-entry))
	  (when (and (designation-could-denote-item-p domain-designation entity)
		     (or (neq quantifier 'the)
			 (unique-value-of-role-p object role entity)))
	    (setq entities-to-serve
		  (eval-cons entity entities-to-serve)))))
      (reclaim-eval-list-macro classes?)
      (reclaim-eval-tree connected-entities)
      entities-to-serve)))



;;; The role server for 'at-an-output is similar to the one for
;;; 'at-an-input.

(def-role-printer at-an-output
  (print-standard-two-element-role 
    role local-variable? " connected at an output of"))

(def-role at-an-output (role domain)
  (let* ((class (second role))
	 (class-description (class-description class)))
    (cond 
      ((and class-description
	    (class-description-of-class-p class-description 'item))
       (serve-cached-role (domain (first role) class)
	 (search-for-directly-connected-entities
	   domain class nil 'output 'output nil nil nil)))
      (t
       (warn-of-bad-connected-to-class class domain)
       (values nil nil nil)))))




;;; The following definition and the function `serve-first-inverse-from-output-
;;; connection' define the `at-an-output inverse role server'.  This role
;;; searches the list of all connected entities of the given object for those
;;; which connected to this one via an output port and which could be denoted by
;;; the passed designation.

(def-role-inverse at-an-output (object quantifier role domain-designation)
  (serve-cached-inverse-roles (object quantifier role domain-designation)
    (let* ((classes? (get-classes-given-designation domain-designation))
	   (connected-entities
	     (loop for class in classes?
		   nconc (search-for-directly-connected-entities
			   object class nil nil 'input 'directionality
			   nil nil)))
	   (entities-to-serve nil))
      (loop with entity
	    for entity-entry in connected-entities
	    do
	(when (eq (third entity-entry) 'output)
	  (setq entity (first entity-entry))
	  (when (and (designation-could-denote-item-p domain-designation entity)
		     (or (neq quantifier 'the)
			 (unique-value-of-role-p object role entity)))
	    (setq entities-to-serve (eval-cons entity entities-to-serve)))))
      (reclaim-eval-list-macro classes?)
      (reclaim-eval-tree connected-entities)
      entities-to-serve)))


(defun get-classes-given-designation (domain-designation)
  (if (symbolp domain-designation)
      (let ((frame-or-frames
	      (frame-or-frames-with-this-name domain-designation)))
	(cond ((listp frame-or-frames)
	       (loop for frame in frame-or-frames
		     when (frame-of-class-p frame 'item)
		       collect (class frame) using eval-cons))
	      ((frame-of-class-p frame-or-frames 'item)
	       (eval-list (class frame-or-frames)))
	      (t
	       nil)))
      (let ((class? (atomic-class-element-of-designation domain-designation)))
	(if (and class? (subclassp class? 'item))
	    (eval-list class?)
	    nil))))



;;; The role server for at-input-end will serve entities of the class specified
;;; in the role at the input end of the connection corresponding to the domain.
;;; Nothing will be served if the connection is not directional, or if the 
;;; domain is not a connection frame (of class connection).

(def-role-printer at-input-end
  (print-standard-two-element-role 
    role local-variable? " at the input end of"))

(def-role at-input-end (role domain)
  (let* ((class (second role))
	 (class-description (class-description class)))
    (cond 
      ((and class-description
	    (class-description-of-class-p class-description 'item))
       (serve-cached-role (domain (first role) class)
	 (search-for-entities-at-input-end domain class t)))
      (t
       (warn-of-bad-connected-to-class class domain)
       (values nil nil nil)))))

;; Domain is a connection frame here.


(defun search-for-entities-at-input-end
       (connection-frame class enforce-directionality?)
  (when (frame-of-class-p connection-frame 'connection)
    (let ((connection
	    (connection-for-this-connection-frame 
	      connection-frame)))
      (when (or (not enforce-directionality?)
		(connection-directed? connection))
	(search-for-directly-connected-entities
	  connection-frame class nil nil 'input nil nil nil)))))

(def-role-printer at-output-end
  (print-standard-two-element-role 
    role local-variable? " at the output end of"))

(def-role at-output-end (role domain)
  (let* ((class (second role))
	 (class-description (class-description class)))
    (cond 
      ((and class-description
	    (class-description-of-class-p class-description 'item))
       (serve-cached-role (domain (first role) class)
	 (search-for-entities-at-output-end domain class t)))
      (t
       (warn-of-bad-connected-to-class class domain)
       (values nil nil nil)))))

(defun search-for-entities-at-output-end
       (connection-frame class enforce-directionality?)
  (when (frame-of-class-p connection-frame 'connection)
    (let ((connection
	    (connection-for-this-connection-frame 
	      connection-frame)))
      (when (or (not enforce-directionality?)
		(connection-directed? connection))
	(search-for-directly-connected-entities
	  connection-frame class nil nil 'output nil nil nil)))))

(def-role-printer at-either-end
  (print-standard-two-element-role 
    role local-variable? " at either end of"))

(def-role at-either-end (role domain)
  (let* ((class (second role))
	 (class-description (class-description class)))
    (cond 
      ((and class-description
	    (class-description-of-class-p class-description 'item))
       (serve-cached-role (domain (first role) class)
	 (search-for-entities-at-either-end domain class)))
      (t
       (warn-of-bad-connected-to-class class domain)
       (values nil nil nil)))))

(defun search-for-entities-at-either-end
       (connection-frame class)
  (nconc (search-for-entities-at-input-end
	   connection-frame class nil)
	 (search-for-entities-at-output-end
	   connection-frame class nil)))
                                                                                
(def-role-inverse at-input-end (object quantifier role domain-designation)
  (serve-cached-inverse-roles (object quantifier role domain-designation)
    (let* ((classes? (get-classes-given-designation domain-designation))
	   (connected-entities
	     (loop for class in classes?
		   nconc (search-for-directly-connected-entities
			   object class nil nil nil nil 'output t)))
	   (entities-to-serve nil))
      (loop for entity in connected-entities
	    do
	(when (and (frame-of-class-p entity 'connection)	; if connection frame
		   (designation-could-denote-item-p domain-designation entity)
		   (or (neq quantifier 'the)
		       (unique-value-of-role-p object role entity)))
	  (setq entities-to-serve (eval-cons entity entities-to-serve))))
      (reclaim-eval-list-macro classes?)
      (reclaim-eval-tree connected-entities)
      entities-to-serve)))

(def-role-inverse at-output-end (object quantifier role domain-designation)
  (serve-cached-inverse-roles (object quantifier role domain-designation)
    (let* ((classes? (get-classes-given-designation domain-designation))
	   (connected-entities
	     (loop for class in classes?
		   nconc (search-for-directly-connected-entities
			   object class nil nil nil nil 'input t)))
	   (entities-to-serve nil))
      (loop for entity in connected-entities
	    do
	(when (and (frame-of-class-p entity 'connection)	; if connection frame
		   (designation-could-denote-item-p domain-designation entity)
		   (or (neq quantifier 'the)
		       (unique-value-of-role-p object role entity)))
	  (setq entities-to-serve (eval-cons entity entities-to-serve))))
      (reclaim-eval-list-macro classes?)
      (reclaim-eval-tree connected-entities)
      entities-to-serve)))

(def-role-inverse at-either-end (object quantifier role domain-designation)
  (serve-cached-inverse-roles (object quantifier role domain-designation)
    (let* ((classes? (get-classes-given-designation domain-designation))
	   (connected-entities
	     (loop for class in classes?
		       nconc (search-for-directly-connected-entities
			       object class nil nil nil nil nil t)))
	   (entities-to-serve nil))
     (loop for entity in connected-entities
	   do
       (when (and (frame-of-class-p entity 'connection)  ; if connection frame
		  (designation-could-denote-item-p domain-designation entity)
		  (or (neq quantifier 'the)
		      (unique-value-of-role-p object role entity)))
	 (setq entities-to-serve (eval-cons entity entities-to-serve))))
     (reclaim-eval-list-macro classes?)
     (reclaim-eval-tree connected-entities)
     entities-to-serve)))




(defun get-output-connections-for-class (block connection-class)
  (loop for connection being each output-connection of block
	as connection-frame-or-class
	   = (connection-frame-or-class connection)
	as connection-frame?
	   = (cond
	       ((symbolp connection-frame-or-class)
		(when (subclassp connection-frame-or-class connection-class)
		  (make-and-install-new-connection-frame
		    connection connection-class)))
	       (t
		(when (frame-of-class-p 
			connection-frame-or-class connection-class)
		  connection-frame-or-class)))
	if connection-frame?
	  collect connection-frame? using eval-cons))

;; A better place for this would be in CONNECTIONS1 or 2.  It is here because it
;; uses eval-cons, which is not defined when CONNECTIONS1 or 2 are loaded.





;;;; Notes on role service for connections

;;; General assumptions: The ports of an entity can be enumerated. They
;;; may have names.  There may be a connection at the port. The
;;; connection may have a direction. The connection may have a
;;; connection class which is hierarchically under `connection'. The
;;; connection may have an entity at the other end. If so, it is
;;; possible to find the port by which the entity was reached.

;;; It seems necessary to expand the notion of role so as not neccessarily to be
;;; atomic. Consider the following pairs of source language and translations:

;;;    1a. the pipe at the inlet of the tank
;;;    1b. (the (at-port inlet pipe) tank)

;;;    2a. every valve at the inlet of the tank
;;;    2b. (every (at-port inlet valve) tank)

;;; The semantics are as follows. When PIPE designates a connection subtype, 
;;; and INLET is a port name of a tank, then if there is a connection at the
;;; inlet, and its a PIPE or subtype thereof, the pipe itself is designated.

;;; When VALVE is a class name of an entity which is not a connection,
;;; and if if there are valves directly connected to the tank at the
;;; inlet, these are designated. (Note that if the quantifier were THE,
;;; there would have to be a uniqure valve.

;;; `Directly connected' means that the valve is reachable from the inlet
;;; without going through objects other than t-connectors or +-connectors, and
;;; without reversing direction.

;;; Thus role-serving needs to recognize these cases, as does FOR.






;;;; Roles For Workspaces And Attributes




;;; (SUBWORKSPACE KB-WORKSPACE)
;;; Finds the unique subworkspace if any of the given item.
;;; Inverse: Finds the item superior to the given kb-workspace if any.

;;; "the subworkspace of "

(def-role-printer subworkspace
  (print-role-whose-car-is-role-server role local-variable?))

(def-role subworkspace (role domain)
  (declare (ignore role))
  (cond
    ((frame-of-class-p domain 'entity)
     (let ((sws (car (subworkspaces domain))))
       (if (and sws (serve-item-p sws))
	   (values sws nil 'never)
	   (values nil nil nil))))
    (t
     (values nil nil nil))))

(def-role-inverse subworkspace (kb-workspace quantifier role domain-designation)
  (declare (ignore role quantifier))
  (if (frame-of-class-p kb-workspace 'kb-workspace)
      (let ((superior-item (parent-of-subworkspace? kb-workspace)))
	(if (and superior-item
		 (designation-could-denote-item-p domain-designation superior-item))
	    (values superior-item nil 'never)
	    (values nil nil nil)))
      (progn (warning-message* 1 "~a is not a kb-workspace." kb-workspace)
	     (values nil nil nil))))




;;; (SUPERIOR-ITEM <class>)
;;; Finds the item superior to the given kb-workspace if any. 
;;; Inverse: Find the unique if any subworkspace of the given item.

;;; "the <class> superior to   "

(def-role-printer superior-item
  (print-standard-two-element-role 
    role local-variable? " superior to"))

(def-role superior-item (role domain)
  (let* ((superior-class (second role))
	 (superior-class-description (class-description superior-class)))
    (cond ((and superior-class-description
		(class-description-of-class-p superior-class-description 'item))
	   (let ((superior-item? (if (kb-workspace-p domain)
				     (parent-of-subworkspace? domain)
				     (parent-frame domain))))
	     (if superior-item?
		 (if (frame-of-class-description-p
		       superior-item? superior-class-description)
		     (if (serve-item-p superior-item?)
			 (values superior-item? nil 'never)
			 (values nil nil nil))
		     (values nil nil nil))
		 (values nil nil nil))))
	  (t
	   (values nil nil nil)))))





;;; The function `item-attributes-of-kb-frame' takes a kb-frame and a
;;; class-description, and returns an eval cons list of the items which are
;;; values of user defined attributes of the given frame.  Note that the list is
;;; in slot-description order (and therefore in attribute table order).  A
;;; faster version of this function which returns an unordered list is given
;;; below.

(defun-simple item-attributes-of-kb-frame (kb-frame class-description)
  (loop for slot-description in
	    (slot-descriptions (class-description-slot kb-frame))
	for attribute-value?
	    = (if (user-defined-slot-description-p slot-description)
		  (get-slot-description-value kb-frame slot-description)
		  nil)
	for attribute-class-description? = (framep attribute-value?)
	when (and attribute-class-description?
		  (class-description-subclass-of-class-description-p
		    attribute-class-description? class-description))
	  collect attribute-value? using eval-cons))




;;; The function `unordered-item-attributes-of-kb-frame' given a kb-frame, will
;;; return a newly consed eval cons list of the items which are attributes of
;;; the given frame, but in no particular order.

(def-system-variable attribute-items roles nil)

(defun-simple add-to-attribute-items (item)
  (setq attribute-items (eval-cons-macro item attribute-items))
  nil)

(defun unordered-item-attributes-of-kb-frame (kb-frame)
  (setq attribute-items nil)
  (funcall-simple-compiled-function-on-attributes kb-frame #'add-to-attribute-items)
  (let ((items-to-return attribute-items))
    (setq attribute-items nil)
    items-to-return))

(def-role-inverse superior-item (item quantifier role domain-designation)
  (declare (ignore role quantifier))
  (let ((frames-to-serve nil)
	(attributes (nconc
		      ;; GENSYMCID-1546: Whenever names receives a value
		      (when (entity-p item) ; only entities have subworkspaces
			(copy-list-using-eval-conses (subworkspaces item)))
		      (unordered-item-attributes-of-kb-frame item))))
    (loop for current-attribute-cons = attributes then next-attribute-cons
	  while current-attribute-cons
	  for attribute = (car current-attribute-cons)
	  for next-attribute-cons = (cdr current-attribute-cons)
	  do
      (cond ((designation-could-denote-item-p domain-designation attribute)
	     (setf (cdr current-attribute-cons) frames-to-serve)
	     (setq frames-to-serve current-attribute-cons))
	    (t
	     (reclaim-eval-cons-macro current-attribute-cons))))
    (serve-all-unreprocessed-frames frames-to-serve)))




;;; The role ATTRIBUTE-OF-CLASS is used to select the frames which are
;;; attributes of another item, filtered by class.

;;; (ATTRIBUTE-OF-CLASS <class>)

(def-role-printer attribute-of-class
  (print-standard-two-element-role 
    role local-variable? " that is an attribute of"))

(def-role (attribute-of-class nil ((or (structure) (class item)))) (role domain)
  (let* ((given-type-symbol (cadr-of-conses role))
	 (type-spec? (type-specification-for-user-or-datum-type
		       given-type-symbol))
	 (class-description?
	   (if (null type-spec?) (class-description given-type-symbol))))
    (cond
      ((and (null type-spec?)
	    (or (null class-description?)
		(not (class-description-of-class-p class-description? 'item))))
       (values nil nil nil))
      ((evaluation-structure-p domain)
       (serve-all-items-and-values 
	 (loop for (nil . value) being each evaluation-structure-pair of domain
	       when (if type-spec?
			(type-specification-type-p value type-spec?)
			(let ((value-class-desc? (framep value)))
			  (and value-class-desc?
			       (class-description-subclass-of-class-description-p
				 value-class-desc? class-description?))))
		 collect (copy-if-evaluation-value value)
		   using eval-cons)))
      (type-spec?
       (let ((slots (get-list-of-all-user-visible-attributes
		      (class-description-slot domain))))
	 (serve-all-items-and-values
	   
	   (loop for slot-name-and-value in slots
		 for slot-name = (car-of-cons slot-name-and-value)
		 for value? = (frame-or-evaluation-value-user-attribute-value
				domain slot-name nil)
		 do
	     (reclaim-eval-cons slot-name-and-value)
		 when (and value?
			   (type-specification-type-p value? type-spec?))
		   collect (prog1 value?
			     (setq value? nil))
		     using eval-cons
		 do
	     (when value?
	       (reclaim-if-evaluation-value value?))
		 finally (reclaim-eval-list slots)))))
      (t
       (serve-all-unreprocessed-frames
	 (item-attributes-of-kb-frame domain class-description?))))))
	       
(def-role-inverse attribute-of-class (item quantifier role domain-designation)
  (declare (ignore quantifier role))
  (let ((parent-frame? (parent-frame item)))
    (if (and parent-frame?
	     (designation-could-denote-item-p
	       domain-designation parent-frame?)
	     (serve-item-p parent-frame?))
	(values parent-frame? nil 'never)
	(values nil nil nil))))




;;; The `USER-ATTRIBUTE-NAMES role server' serves the names of all user-defined
;;; attributes of an item.

;;; Role: (user-attribute-names symbol), Domain: <designation>
;;;
;;; for any symbol [local-name] that is a user-defined attribute name 
;;;    of <designation>
;;;
;;; for <local-variable> = each symbol that is a user-defined attribute name
;;;    of <designation>

(def-role-printer user-attribute-names
  (print-standard-two-element-role
    role local-variable? " that is a user-defined attribute name of"))

(def-role (user-attribute-names symbol ((or (structure) (class item)))) (role domain)
  (declare (ignore role))
  (cond
    ((evaluation-structure-p domain)
     (let ((structure domain))
       (serve-all-evaluation-values
	 (loop for (name . nil) being each evaluation-structure-pair of structure 
	       collect (make-evaluation-symbol name)
	       using eval-cons))))
    ((of-class-p domain 'item)
     (serve-all-evaluation-values
       (loop for x being each attribute of domain
	     collect (make-evaluation-symbol x) using eval-cons)))
    (t
     ;; This case can't happen, but I'm too paranoid to remove it -jra 8/5/96
     (values nil nil nil))))




;;; The `ATTRIBUTE-NAMES role server' serves the names of all exported
;;; attributes of an item, including both user-defined and system-defined
;;; attribute names.  This role can also accept structure arguments, in which
;;; case it returns all structure attributes of the given argument.

;;; Role: (attribute-names symbol), Domain: <designation>
;;;
;;; for any symbol [local-name] that is an attribute name of <designation>
;;;
;;; for <local-var> = each symbol that is an attribute name of <designation>

(def-role-printer attribute-names
  (print-standard-two-element-role
    role local-variable? " that is an attribute name of"))

(def-role (attribute-names symbol ((or (structure) (class item)))) (role domain)
  (declare (ignore role))
  (cond
    ((evaluation-structure-p domain)
     (let ((structure domain))
       (serve-all-evaluation-values
	 (loop for (name . nil) being each evaluation-structure-pair of structure 
	       collect (make-evaluation-symbol name)
	       using eval-cons))))
    (t
     (let ((name-to-slot-description-alist
	     (get-list-of-all-user-visible-attributes
	       (class-description-slot domain))))
       (loop for entry-cons on name-to-slot-description-alist
	     for alist-entry = (car-of-cons entry-cons)
	     for name = (car-of-cons alist-entry)
	     do
	 (reclaim-eval-cons alist-entry)
	 (setf (car entry-cons) (make-evaluation-symbol name)))
       (serve-all-evaluation-values name-to-slot-description-alist)))))




;;; The role ATTRIBUTE-VALUE is used to return the item or constant contained
;;; within an attribute.  Normally, attribute values are served in
;;; serve-first-value-of-role.  This role allows the user to refer to an
;;; attribute indirectly using a symbolic expression.  For attributes containg
;;; items, including variables and parameters, this function returns the item
;;; and not the current value of an item.  It is up to the compiler to emit an
;;; instruction that coerces this value to the correct type, if necessary.

;;;   Role: (attribute-value item-or-datum)
;;;   Domains: designation symbolic-expression
;;;
;;;   "the <type-or-class> that is an attribute of <designation>
;;;    named by <designation>"

(def-role-printer attribute-value
  (print-standard-two-element-role
    role 
    local-variable?
      " that is an attribute of the item"))

;; printer for: ((attribute-value <class>) . <local-name>) (<domain-1> <domain-2>)
;; and          (attribute-value <class>) (<domain-1> <domain-2>)

(def-role-and-designation-printer attribute-value
  (let* ((local-name? (if (and (consp role)
			       (consp (first role)))
			  (cdr role)
			  nil))
	 (role-with-no-local-name (if local-name?
				      (first role)
				      role))
	 (type (if (listp role-with-no-local-name)
		   (second role-with-no-local-name))))
    (print-user-or-datum-type type)
    (when local-name?
      (twrite-string " ")
      (princ-lowercase local-name?))
    (tformat " that is an attribute of ~ND named by ~ND" domain-1? domain-2?)))


;; change function for project vectorized user slots (jra/ghw 1/4/93)
;; Changed.  (2/22/93 ghw)

(def-role (attribute-value nil ((or (class item) (structure)) symbol))
    (role item attribute-name)
  (let ((attribute (evaluation-symbol-symbol attribute-name)))
    (if (unauthorized-system-slot-p attribute)
	(values nil nil nil)
	(let* ((class? (if (consp role)
			   (second role)))
	       (class-type-spec (eval-list 'class class?))
	       (type-spec
		 (or (type-specification-for-user-or-datum-type class?)
		     class-type-spec))
	       (attribute-value?
		 (frame-or-evaluation-value-user-attribute-value
		   item attribute nil)))
	  (when (and attribute-value?
		     (not (type-specification-type-p
			    attribute-value?
			    type-spec)))
	    (let ((coerced-value? (coerce-to-type-for-role-service
				    attribute-value? type-spec)))
	      (cond (coerced-value?
		     (reclaim-if-evaluation-value attribute-value?)
		     (setq attribute-value? coerced-value?))
		    (t
		     (reclaim-if-evaluation-value attribute-value?)
		     (setq attribute-value? nil)))))
	  (reclaim-eval-list-given-tail
	    class-type-spec (cdr-of-cons class-type-spec))
	  (if attribute-value?
	      (values attribute-value? nil 'never)
	      (values nil nil nil))))))




(def-role-printer class-qualified-name 
  (princ-lowercase (second role))
  (twrite-string "::")
  (princ-lowercase (third role))
  (when local-variable?
    (twrite-string " ")
    (tprinc local-variable?))
  (twrite-string " of"))


;;; The role `class-qualified-name' implements fetching attribute values when
;;; the user has given a class to use as the class from whose perspective the
;;; attribute search should proceed.  The semantics of this qualification are
;;; that the default version of this attribute from the perspective of the given
;;; class should be chosen.  The given class must be a superior class of the
;;; class of the domain.

;;; Note that this code is closely related to that in serve-first-value-of-role,
;;; which processes unqualified attribute references.

;;;   (CLASS-QUALIFIED-NAME class attribute-name)

(def-role (class-qualified-name item-or-datum ((class item)))
    (role domain)
  (let* ((class-cons (cdr-of-cons role))
	 (class (car-of-cons class-cons))
	 (attribute-name (second-of-long-enough-list class-cons))
	 (attribute-value?
	   (frame-or-evaluation-value-user-attribute-value
	     domain attribute-name class)))
    (if attribute-value?
	(values attribute-value? nil 'never)
	(values nil nil nil))))


(def-role-inverse class-qualified-name (item quantifier role domain-designation)
  (declare (ignore quantifier))
  (let* ((parent-frame? (parent-frame item))
	 (pretty-name (unqualified-name role))
	 (qualifier (class-qualifier role)))
    (if (and parent-frame?
	     (eq
	       item
	       (get-slot-value parent-frame? pretty-name qualifier)) 
	     (designation-could-denote-item-p
	       domain-designation parent-frame?)
	     (serve-item-p parent-frame?))
	(values parent-frame? nil 'never)
	(values nil nil nil))))


;;; (WORKSPACE KB-WORKSPACE)
;;; Finds the unique workspace if any upon which the given item is mounted.

;;; Needs an inverse server which finds all items of the given class which
;;; are "on" the workspace directly or indirectly, e.g. embedded rules.!!!
 
(def-role-printer workspace
  (print-role-whose-car-is-role-server role local-variable?))

(def-role workspace (role domain)
  (declare (ignore role))
  (let ((ws (superblock? domain)))
    (if (and ws (serve-item-p ws))
	(values (superblock? domain) nil 'never)
	(values nil nil nil))))

(def-role-inverse workspace (workspace quantifier role domain-designation)
  (declare (ignore quantifier role))
  (cond
    ((not (of-class-p workspace 'kb-workspace))
     (values nil nil nil))

    (t (loop for frame being each subblock of workspace
	     when (and (frame-of-class-p frame 'item)
		       (serve-item-p frame)
		       (designation-could-denote-item-p domain-designation frame))
	       collect frame into item-list using eval-cons
	     finally (return (serve-all-unreprocessed-frames item-list))))))





;;; (UPON <class>)
;;; Finds all items upon the given kb-workspace.
;;; Inverse: Finds the kb-workspace this item is upon.

;;; "the|any <class> upon   "

(def-role-printer upon
  (print-standard-two-element-role 
    role local-variable? " upon"))

(def-role (upon nil ((class kb-workspace))) (role domain)
  (let* ((class (second role))
	 (class-description (class-description class)))
    (cond
      ((or (null class-description)
	   (not (class-description-of-class-p class-description 'item)))
       (values nil nil nil))
      
      (t
       (serve-all-unreprocessed-frames
	 (loop for frame being each subblock of domain
	       if (frame-of-class-description-p frame class-description)
		 collect frame using eval-cons
	       and
		 count frame into counts
	       ;; GENSYMCID-854 & GENSYMCID-903: terminate search process for "there exists" on first found node.
	       ;; -- Chun Tian (binghe), 2012/11/24
	       until (and there-exists-p (pluspf counts))))))))

(def-role-inverse upon (item quantifier role domain-designation)
  (let ((kb-workspace? (superblock? item)))
    (if (and kb-workspace?
	     (designation-could-denote-item-p domain-designation kb-workspace?)
	     (or (neq quantifier 'the)
		 ;; If quantifier is 'the, then there must be only one
		 ;; item of given class on workspace.
		 (=f 1 (loop for frame being each subblock of kb-workspace?
			     counting (frame-of-class-p frame (second role))))))		 

	(values kb-workspace? nil 'never)
	(values nil nil nil))))




;;; (NAMED <name> WORKSPACE)
;;; If there is a kb-workspace of this name, it finds it, otherwise
;;; it finds the subworkspace of an object of that name.

;; The following role was last used in version 1.11B, and the parser will no
;; longer produce it.  Since it's been six years and two recompiles of all user
;; code since it was last used, I think I can safely comment it out, but will
;; leave this note and the comment below for the humorous perusal of any future
;; passerby.  -jra 8/5/96

;(def-role-printer named
;  (declare (ignore local-variable?))
;  (tformat "workspace named ~(~d~)" (second role)))

;(def-role named (role domain)
;  (declare (ignore domain))
;  (let ((ws (or (get-instance-with-name-if-any 'kb-workspace (second role))
;                (get-instance-with-name-if-any 'message-board (second role))))
;        entity)
;    (cond
;      (ws
;       (if (or (serve-item-p ws) (frame-of-class-p ws 'message-board))
;           (values ws nil 'never)
;           (values nil nil nil)))
;      (t
;       (setq entity (get-instance-with-name-if-any 'entity (second role)))
;       (when (and entity (frame-of-class-p entity 'item))
;         (setq ws (car (subworkspaces entity))))
;       (if (and ws (serve-item-p ws))
;           (values ws nil 'never)
;           (values nil nil nil))))))




;;; (THIS-WORKSPACE KB-WORKSPACE) finds the workspace of 
;;; *current-computation-frame*.

;; Inverse role server!!!
						       ;Is an inverse needed??
						       ;cpm, 4/19/91

;; Inverse role servers serve items which are domains a role given a value of
;; the role.  This role has no explicit domain, though in a sense it has an
;; implicit domain.  This workspace is really "the kb-workspace that is superior
;; to the currently executing item".  The "currently executing item" is not a
;; role that we currently have, but we need.  It could be implemented using the
;; *current-computation-frame* (which identifies the lexical scope of the current
;; execution, to use Ben's words).  So, we should implement a "this item"
;; reference for the currently executing thing, and we should parse
;; this-workspace into a role of the "this item" phrase.  Then we could
;; reasonable supply an inverse server for this role.  -jra 6/4/91

;; An inverse is being made through designation-denotes-item-p.  This will be
;; necessary for all roles with no domains that still need inverters.  -jra
;; 1/25/95

(def-role-printer this-workspace
  (declare (ignore role local-variable?))
  (tprinc "this workspace"))

(def-role (this-workspace nil nil) (role domain)
  (declare (ignore role domain))
  (let ((workspace?
	  (nth-value
	    1 (get-block-on-workspace-for-frame *current-computation-frame*))))
    (if (and workspace? (serve-item-p workspace?))
	(values workspace? nil 'never)
	(values nil nil nil))))

(def-role-inverse this-workspace (kb-workspace quantifier role domain-designation)
  (declare (ignore kb-workspace quantifier role domain-designation))
  (values nil nil nil))


;;; The role server for this-window finds the window of 
;;; *current-computation-frame*.  This assumes that failure to find
;;; the window implies that `this window' is not being called from
;;; from an embedded rule (i.e. either an action button or a user
;;; menu choice), which is a KB error.

;;; Inverse role server!!! 
						       ;Is an inverse needed??
						       ;cpm, 4/19/21
;; Serve-this-window has been moved to CONTROLS due to a reference to the
;; slot ri-window-for-rule?.

(def-role-printer this-window
  (declare (ignore role local-variable?))
  (tprinc "this window"))

(def-role (this-window nil nil) (role domain)
  (let ((g2-window-or-client-interface? (serve-this-window role domain)))
    (if (and g2-window-or-client-interface?
	     (serve-item-p g2-window-or-client-interface?))
	(values g2-window-or-client-interface? nil 'never)
	(values nil nil nil))))






;;;; Class Hierarchy Role Servers




;;; The `Superior-class role server' returns the class superior to the given
;;; class.  Both the domain and the value served are the names of classes, not the
;;; class definitions.  Note that the superior of item and the superior of any
;;; system class that is not a subclass of item, e.g., entity, return no value.

;;; Role: (SUPERIOR-CLASS SYMBOL), Domain: CLASS-NAME

;;; added support for multiple direct superior classes -rdf, 2/22/94

(def-first-value-ok-for-the superior-class)

(def-role-printer superior-class
  (print-standard-two-element-role
    role local-variable? " that is a superior-class of"))

(def-role (superior-class symbol (symbol)) (role domain)
  (declare (ignore role))
  (let* ((class-name domain)
	 (system-class-p? (system-defined-class-p class-name))
	 (superior-classes? 
	   (cond (system-class-p?
		  (cond ((eq class-name 'item) nil)
			((subclassp class-name 'item)
			 (direct-superior-classes class-name))
			(t nil)))
		 (t
		  (direct-superior-classes class-name)))))
    (serve-all-evaluation-values
      (loop for class in superior-classes?
	    when (or (null system-class-p?) (subclassp class 'item))
	      collect (make-evaluation-symbol class)
		using eval-cons))))



;;; The `Inferior-class role server' returns the class inferior to the given
;;; class.  Both the domain and the value served are the names of classes, not
;;; class definitions.  Note that the inferior of a class with no subclasses and
;;; the inferior of a system-defined class which is not a subclass of item
;;; return no value.

;;; Role: (INFERIOR-CLASS SYMBOL), Domain: CLASS-NAME

(def-role-printer inferior-class
  (print-standard-two-element-role
    role local-variable? " that is an inferior-class of"))

(def-role (inferior-class symbol (symbol)) (role domain)
  (declare (ignore role))
  (let* ((class-name domain)
	 (inferior-classes? (inferior-classes class-name)))
    (serve-all-evaluation-values
      (loop for class in inferior-classes?
	    collect (make-evaluation-symbol class) using eval-cons))))






;;;; Serve for Various Items




;;; Role: (CLASS-INSTANCES-NAMED-BY <CLASS>)
;;;
;;; (any (class-instances-named-by <class>) symbol-expression)
;;;
;;; for any <class-name> [local-name] that is of the class 
;;;    named by <designation>
;;;
;;; for <local-variable> = <class-name> that is of the class 
;;;    named by <designation>


;;; The `CLASS-INSTANCES-NAMED-BY role server' serves all instances of a class
;;; that is named by a designation.  The domain of the role should contain a
;;; symbolic value of the designation.  If the domain class name is a superior or
;;; an inferior class of the role class, the more restrictive of the two are
;;; served.  If the two classes are disjoint, no values are served.

;;; Note that instances of classes, e.g., "for any foo x if ...", are normally
;;; served in serve-first-value-of-role.

;;; This role server, similar to named-by, does have an inverse role server.

(def-role-printer class-instances-named-by
  (print-standard-two-element-role 
    role local-variable? " that is of the class named by"))

;; Note that the data seeking for named-by was abstracted in
;; coerce-to-symbol-for-named-by-role.  This wil not be necessary when generic
;; references in rules coerce the domain to the defined domain type!!  cpm,
;; 8/12/91

(def-role (class-instances-named-by nil (symbol)) (role domain)
  (let* ((role-class (second role))
	 (named-by-class domain)
	 (role-class-description (class-description role-class))
	 (named-by-class-description (class-description named-by-class)))
    (cond
      ((or (null role-class-description)
	   (null named-by-class-description)
	   (not (class-description-of-class-p
		  rule-class-description 'item))
	   (not (class-description-of-class-p
		  named-by-class-description 'item)))
       (values nil nil nil))
      ((class-description-subclass-of-class-description-p
	 named-by-class-description
	 role-class-description)
       (serve-first-instance-of-class named-by-class))
      ((class-description-subclass-of-class-description-p
	 role-class-description
	 named-by-class-description)
       (serve-first-instance-of-class role-class))
      ;; In this case both classes are items, but neither is a direct
      ;; subclass of the other.  However, there may be (possibly multiple)
      ;; intersections in the subclass hierarchies of these two classes.  In
      ;; this case, collect the named-by class and filter out everything
      ;; that is not of the role class.  -jra 8/5/96
      (t
       (let ((named-instances
	       (collect-instances-of-class-for-role-service named-by-class)))
	 (serve-all-unreprocessed-frames
	   (loop for instance in named-instances
		 when (frame-of-class-description-p
			instance role-class-description)
		   collect instance using eval-cons
		 finally (reclaim-eval-list named-instances))))))))


;;; "This-rule" role server serves the *current-computation-frame* which should be
;;; a rule.  There is no inverse role-server.  The grammar restricts this
;;; role from being called from other than rules.

;;; The role is: (THIS-RULE RULE)

(def-role-printer this-rule
  (declare (ignore role local-variable?))
  (tprinc "this rule"))

(def-role (this-rule nil nil) (role domain)
  (declare (ignore role domain))
  (let ((this-frame *current-computation-frame*))
    (if (frame-of-class-p this-frame 'rule)
	(values this-frame nil 'never)
	(values nil nil nil))))

(def-role-inverse this-rule (rule quantifier role domain-designation)
  (declare (ignore rule quantifier role domain-designation))
  (values nil nil nil))


;;; "This-procedure" role server serves the *current-computation-frame* which
;;; should be a procedure.  There is no inverse role-server.  The grammar
;;; restricts this role from being called from other than procedures.

;;; The role is: (THIS-PROCEDURE PROCEDURE)

(def-role-printer this-procedure
  (declare (ignore role local-variable?))
  (tprinc "this procedure"))

(def-role (this-procedure nil nil) (role domain)
  (declare (ignore role domain))
  (let ((this-frame *current-computation-frame*))
    (if (frame-of-class-p this-frame 'procedure)
	(values this-frame nil 'never)
	(values nil nil nil))))



;;; "This-procedure-invocation" role server serves a procedure-invocation frame
;;; if the current-computation-instance is a code-body invocation.  This value
;;; is only served if there is a frame contained within the procedure-invocation
;;; structure.  There is no inverse role-server.  The grammar restricts this
;;; role from being called from other than procedures.

;;; The role is: (THIS-PROCEDURE-INVOCATION PROCEDURE-INVOCATION)

(def-role-printer this-procedure-invocation
  (declare (ignore role local-variable?))
  (tprinc "this procedure-invocation"))

(def-role (this-procedure-invocation nil nil) (role domain)
  (declare (ignore role domain))
  (let ((this-procedure-invocation-frame?
	  (get-current-procedure-invocation-frame-if-any)))
    (if this-procedure-invocation-frame?
	;; Procedure invocations are structures which may have a
	;; procedure-invocation frame.
	(values this-procedure-invocation-frame? nil 'never)
	(values nil nil nil))))






;;;; Role server for relations.




(def-role-printer related
  (print-user-or-datum-type (third role))
  (when local-variable?
    (twrite-character #.%space)
    (twrite-symbol local-variable?))
  (twrite-string " that is ")
  (twrite-symbol (second role)))

(def-role related (role domain)
  (let* ((class (third role))
	 (class-description (class-description class)))
    (cond
      ((or (null class-description)
	   (not (class-description-of-class-p class-description 'item)))
       (values nil nil nil))
      (t
       (let* ((given-name (second role))
	      (unfiltered-related-items (related-items domain given-name)))
	 (if unfiltered-related-items
	     (loop for item being each related-item of unfiltered-related-items
		   when (and item
			     (serve-item-p item)
			     (frame-of-class-description-p item class-description))
		   collect item into result using eval-cons
		   finally (return (serve-all-unreprocessed-frames result)))
	   (serve-all-unreprocessed-frames nil)))))))

;; Issue a warning where there is no such relation.  -jra 6/4/91

(def-role-inverse related (item quantifier role domain-designation)
  (block serve-inverse-related-items
    (let* ((relation
	     (get-instance-with-name-if-any 'relation (second role)))
	   (given-name (second role))
	   (other-name
	     (cond ((null relation) nil)	       ; warn of no such relation?
		   ((relation-is-symmetric relation) given-name)
		   ((eq given-name (relation-name relation))
		    (or (inverse-of-relation relation)
			(secret-inverse-name relation)))
		   (t (relation-name relation))))
	   (class (third role))
	   (subject-unfiltered-list
	     (if other-name (related-items item other-name))))

      (when (related-items-is-empty-p subject-unfiltered-list)
	(return-from serve-inverse-related-items
	  (values nil nil nil)))
      
      (if (neq quantifier 'the)
	  (loop for item-2 being each related-item of subject-unfiltered-list
		when (and (serve-item-p item-2)
			  (designation-could-denote-item-p domain-designation item-2))
		  collect item-2 into result using eval-cons
		finally
		  (return (serve-all-unreprocessed-frames result)))
	  ;; else, need to test for uniqueness of item.
	  (loop for item-2 being each related-item of subject-unfiltered-list
		when (and (serve-item-p item-2)
			  (designation-could-denote-item-p domain-designation item-2)
			  ;; Test if item is the only instance of class
			  ;; that is related to item-2 by this relation.
			  (when-let* ((relation-instances (relation-instances item-2))
				      (relation-instance
				       (get-relation-instance given-name relation-instances))
				      (forward-instances
				       (relation-instance-items relation-instance)))
			    ;; NOTE: when-let* otherwise returns NIL, this is acceptable.
			    (loop for possible-unique-item being each related-item of forward-instances
				initially
				  (if (and (only-one-related-item-p forward-instances)
					   (let ((the-only-item
						  (first-related-item forward-instances)))
					     (and (frame-of-class-p the-only-item class)
						  (serve-item-p the-only-item))))
				      (return t))
				until (cdr item-list)
				when (and (frame-of-class-p
					    possible-unique-item class)
					  (serve-item-p possible-unique-item))
				  collect possible-unique-item into item-list 
							 using eval-cons
				  ;; Stop after the second relation-instance
				  ;; is found. 
				finally
				  ;; Test for uniqueness.
				  (return
				    (prog1
				      (=f (length item-list) 1)
				      (reclaim-eval-list item-list))))))
		  collect item-2 into result using eval-cons
		finally
		  (return (serve-all-unreprocessed-frames result)))))))

;; Fixed the above serve-inverse-related-items to test for uniqueness
;; using the class contained in the role.   cpm/ml , 8apr90.




(def-role-predicate related related-role-predicate)

(defun related-role-predicate (value-to-check quantifier role domain)
  (let* ((relation-name (second role))
	 (class (third role))
	 (class-description (class-description class))
	 (related-items (related-items domain relation-name)))
    (and (class-description-of-class-p class-description 'item)
	 (frame-of-class-description-p value-to-check class-description)
	 (or (and (eq quantifier 'the)
		  (and related-items
		       (eq (first-related-item related-items) value-to-check)
		       (only-one-related-item-p related-items)))
	     (and (neq quantifier 'the)
		  (relation-exist-p value-to-check related-items))))))






;;;; Role Servers for G2-Lists




;;; Role:  (<element-position> <list-type>), or
;;; Role:  ((<element-position> <list-type>) . <local-name>)


;;; `First-of-list' role server and inverse role server.

(def-role-printer first-of-list
  (print-ordinal-list-role "first" role local-variable?))

(defun-void print-ordinal-list-role (ordinal-name role local-variable?)
  (twrite-string ordinal-name)
  (twrite-character #.%space)
  (print-user-or-datum-type (second role))
  (when local-variable?
    (tformat " ~(~a~)" local-variable?))
  (twrite-string " in"))

(def-role (first-of-list nil ((or (class g2-list) (sequence)))) (role domain)
  (serve-element-of-list role domain))

(def-role-inverse first-of-list (item quantifier role domain-designation)
  (serve-element-of-list-inverse item quantifier role domain-designation))

;;; `Second-of-list' role server and inverse role server.

(def-role-printer second-of-list
  (print-ordinal-list-role "second" role local-variable?))

(def-role (second-of-list nil ((or (class g2-list) (sequence)))) (role domain)
  (serve-element-of-list role domain))

(def-role-inverse second-of-list (item quantifier role domain-designation)
  (serve-element-of-list-inverse item quantifier role domain-designation))


;;; `Next-to-last-of-list' role server and inverse role server.

(def-role-printer next-to-last-of-list
  (print-ordinal-list-role "next to last" role local-variable?))

(def-role (next-to-last-of-list nil ((or (class g2-list) (sequence))))
    (role domain)
  (serve-element-of-list role domain))

(def-role-inverse next-to-last-of-list (item quantifier role domain-designation)
  (serve-element-of-list-inverse item quantifier role domain-designation))


;;; `Last-of-list' role server and inverse role server.

(def-role-printer last-of-list
  (print-ordinal-list-role "last" role local-variable?))

(def-role (last-of-list nil ((or (class g2-list) (sequence)))) (role domain)
  (serve-element-of-list role domain))

(def-role-inverse last-of-list (item quantifier role domain-designation)
  (serve-element-of-list-inverse item quantifier role domain-designation))



;;; The role serice `serve-element-of-list' finds a particular list element as
;;; indicated by the role's element-position.  These can be: first-of-list,
;;; second-of-list , next-to-last-of-list, last-of-list.

(defun serve-element-of-list (role g2-list-or-sequence?)
  (let ((element-position (if (consp (first role))
			      (first (first role))
			      (first role)))
	(desired-list-type? (if (consp (first role))
				(second (first role))
				(second role)))
	(list-type? nil))
    ;; local name, if present in the role, is ignored.
    (cond
      ((evaluation-sequence-p g2-list-or-sequence?)
       (let* ((class-type-spec nil)
	      (type-spec?
		(if desired-list-type?
		    (or (type-specification-for-user-or-datum-type
			  desired-list-type?)
			(progn
			  (setq class-type-spec (eval-list 'class nil))
			  (setf (second class-type-spec)
				desired-list-type?)
			  class-type-spec))))
	      (result
		(case element-position
		  ((first-of-list second-of-list)
		   (loop for value being each
			 evaluation-sequence-element of g2-list-or-sequence?
			 do
		     (when (or (null type-spec?)
			       (type-specification-type-p value type-spec?))
		       (if (eq element-position 'first-of-list)
			   (return value)
			   (setq element-position 'first-of-list)))))
		  ((next-to-last-of-list)
		   (search-for-sequence-element-from-back
		     g2-list-or-sequence? type-spec? 1))
		  ((last-of-list)
		   (search-for-sequence-element-from-back
		     g2-list-or-sequence? type-spec? 0))
		  #+development
		  (t
		   (error "Bad sequence element-position ~a."
			  element-position)))))
	 (reclaim-eval-list class-type-spec)
	 (if result
	     (values (copy-if-evaluation-value result) nil 'never)
	     (values nil nil nil))))
      ((not (g2-list-p g2-list-or-sequence?))
       (values nil nil nil))
      ((null (setq list-type? (list-type g2-list-or-sequence?)))
       (warning-message*
	   1
	   "The element type ~NT is incorrect for the g2-list ~NF ~
              which is missing a type."
	 desired-list-type? g2-list-or-sequence?)
       (values nil nil nil))
      ((not (g2-list-or-array-type-ok-p desired-list-type? list-type? t))
       (warning-message*
	   1
	   "The element type ~NT is incorrect for the g2-list ~NF ~
              which is of type ~NT."
	 desired-list-type? g2-list-or-sequence? list-type?)
       (values nil nil nil))
      (t
       (when (g2-list-or-array-datum-subtype-p
	       list-type? desired-list-type?)
	 ;; Optimization.  Locate an element by position only.
	 (setq desired-list-type? nil))
       (let ((element?
	       (case element-position
		 (first-of-list
		  (g2-list-first g2-list-or-sequence? desired-list-type? nil))
		 (second-of-list
		  (g2-list-second g2-list-or-sequence? desired-list-type? nil))
		 (next-to-last-of-list
		  (g2-list-next-to-last g2-list-or-sequence? desired-list-type? nil))
		 (last-of-list
		  (g2-list-last g2-list-or-sequence? desired-list-type? nil))
		 #+development
		 (t
		  (cerror
		    "error"
		    "unknown element position in serve-element-of-list")))))
	 (cond ((null element?)
		(values nil nil nil))
	       (t (values element? nil 'never))))))))

;; Removed the warning for the g2-list-p check in serve-element-of-list.  The
;; roles that call this function now specify that their domain is a g2-list.
;; This type-test is emitted into the expressions that use these roles.  This
;; allows us to signal a stack-error instead of a giving a warning message.  -
;; cpm, 12/4/92



;;; The inverse role service `serve-element-of-list-inverse' finds the g2-lists
;;; that an item belongs to.

(defun serve-element-of-list-inverse
       (item quantifier role domain-designation)
  (let ((element-position (if (consp (first role))
			      (first (first role))
			      (first role)))
	(desired-list-type (if (consp (first role))
			       (second (first role))
			       (second role))))
    (cond
      ((null (framep item))
       ;; Can only locate the g2-lists containing items.  Don't give a warning.
       (values nil nil nil))
      (t
       (loop for g2-list-element-structure in (list-elements-for-item item)
	     for g2-list = (list-frame g2-list-element-structure)
	     for g2-list-type = (list-type g2-list)
	     for check-domain-role-and-type?
	     = (and (designation-could-denote-item-p domain-designation g2-list)
		    (or (neq quantifier 'the)
			;; The item is the only thing in the list, this check
			;; could be made faster if you want.
			(unique-value-of-role-p item role g2-list))
		    ;; Check the type of role.
		    (g2-list-or-array-type-ok-p
		      desired-list-type g2-list-type t))
	     for element? = (if check-domain-role-and-type?
				(case element-position
				  (first-of-list
				   (g2-list-first
				     g2-list desired-list-type nil))
				  (second-of-list
				   (g2-list-second 
				     g2-list desired-list-type nil))
				  (next-to-last-of-list
				   (g2-list-next-to-last 
				     g2-list desired-list-type nil))
				  (last-of-list
				   (g2-list-last
				     g2-list desired-list-type nil))
				  #+development
				  (t (cerror 
				       "Error" 
				       "Unknown list element position in ~
                                           serve-element-of-list")))
				nil)
	     when (and element?
		       (eq item element?) ; only care if items are equal
		       (not (memq g2-list result)))
	       collect g2-list into result using eval-cons
	       do
	 (when element?
	   (reclaim-if-evaluation-value element?))
	     finally
	       (return
		 (serve-all-unreprocessed-frames result)))))))

;; This should be made more efficient.  Have separate inverse role servers,
;; instead of checking the element-position at run-time in each loop iteration!!
;; cpm, 3-2-90



;;; The `list-iterator role service' returns all the elements of a list.  Note,
;;; that this role-server is obsolete.  It has been replaced by element-iterator
;;; which serves the elements of both g2-lists and g2-arrays.




;; NEXT-LIST-ELEMENT Designation and Role:
;;    (the (NEXT-LIST-ELEMENT item-or-datum) designation element-expression)

;; NEXT-LIST-ELEMENT (<list>, <list-element-designation>) - G2 function.

;; Currently, there is no G2 grammar that parses into this role.
;; Next-list-element is implemented as a G2 function and compiled with a
;; special-form converter into this role and the coerce-matching-element-type
;; instruction.  The coerce instruction coerces and data-seeks, if necessary,
;; based on the list element type.

;; The role service `serve-next-list-element' returns the next element in the
;; list after the given element.  For example, the function call
;; "next-list-element (tank-list, tank-1)", returns the element in tank-list
;; after tank-1, if any.

;; It is an error if the list does not contain the indicated element or
;; contains no elements.  If there is no element after the specified element,
;; which is in the list, no value is returned.  It is an error for this
;; expression to operate on lists that allow duplicate elements.  If a
;; duplicate element was being referenced in this expression, it is not
;; possible to determine which element the user inteded to reference.  Also,
;; with duplicates, the same series of "next elements" could possibly be served
;; repeatedly.

;; This expression is more efficient for item lists.  Since an item contains
;; pointers to every g2-list that it belongs to (in fact it points to its
;; actual position in the list), the speed of the operation depends on the
;; number of times an item is in any g2-lists.  Therefore, if the item is
;; contained in one list, the operation is executed in a constant time.

;; This expression is less efficient for datum lists.  In this case, the list
;; is searched from the start of the list for the next element, which is an
;; O(n) operation, where n is the length of the list.

;; This evaluator is available in the inference engine and procedures.

;; Possible errors:
;; 1. The element is not found in the list.
;; 2. The g2-list allows duplicate elements.  If there are duplicate elements,
;; it could be ambiguous which element the expression is referencing.  Another
;; problem is that the same series of elements could be served repeatedly.

;; Currently, there is no inverse role-server.

;; NEXT-LIST-ELEMENT was planned to be used in 3.0 as a G2 function.  There is
;; an implementation problem with this.  G2 functions currently can't return
;; items and, therefore, can't be used as designations.  Since this function is
;; not an important feature, it is not being put into G2 at this time.  As
;; described above, this function would have only been useful in lists that
;; don't allow duplicates and would have only been efficient for item-lists.
;; cpm, 8/20/91.

;(def-role-printer next-list-element
;  (declare (ignore role local-variable?))
;  (tformat "next-list-element"))

;(def-role-and-designation-printer next-list-element
;  (declare (ignore role))
;  (twrite-string "next-list-element (")
;  (print-designation (first domain-args))
;  (twrite-string ", ")
;  (write-expression (second domain-args))
;  (twrite-string ")"))

;(def-role (next-list-element item-or-datum ((class g2-list) item-or-datum))
; 	  (role g2-list? previous-element?)
;  (let ((previous-element-structure? nil))
;    (cond ((null g2-list?)
;	   (warning-for-null-domain role))
;	  ((null previous-element?)
;	   (write-warning-message* 1
;	     (tformat "While referencing the next element in the g2-list ~
;                      ~NF, the element was not provided."
;		      g2-list?)))
;	  ((insert-duplicate-elements? g2-list?)
;	   (write-warning-message* 1
;	     (tformat "Cannot reference the next element in ~NF ~
;                       because this g2-list allows duplicate elements."
;		      g2-list?)
;	     (tformat
;	       "~A ~A ~A"
;	       "  There is an attribute that can be modified in the g2-list"
;	       "table or in the default settings of a g2-list object"
;	       "definition to not allow duplicates.")
;	     (values nil nil nil)))
;	  ((g2-list-empty-p g2-list?)
;	   (write-warning-message* 1
;	     (tformat "Cannot reference the next element in the g2-list ~NF.  ~
;                       The list is empty."
;		      g2-list?))
;	   (values nil nil nil))
;	  ;; Locate the previous element in the g2-list.
;	  ((null (setq previous-element-structure?
;		       (find-g2-list-element-structure
;			 previous-element? g2-list? t)))
;	   (if (framep previous-element?)
;	       (write-warning-message* 1
;		 (tformat "Cannot reference the next element from ~NF.  The ~
;                          g2-list ~NF does not contain that element."
;			  previous-element? g2-list?))
;	       (write-warning-message* 1
;		 (tformat "Cannot reference the next element from ~NC.  The ~
;                          g2-list ~NF does not contain that element."
;			  (cached-constant-value previous-element?)
;			  (constant-type previous-element?)
;			  g2-list?)))
;	   (values nil nil nil))
;	  (t
;	   (let* ((g2-list-structure (list-structure g2-list?))
;		  (next-element-structure
;		    (list-next-element previous-element-structure?))
;		  (next-element
;		    (list-element-value next-element-structure)))
;	     (cond ((eq next-element-structure g2-list-structure)
;		    ;; Previous-element is the last element in the list.
;		    (values nil nil nil))
;		   ((not (framep next-element))
;		    (values (copy-temporary-constant next-element) nil 'never))
;		   ((serve-item-p next-element)
;		    (values next-element nil 'never))
;		   (t (values nil nil nil))))))))






;;;; Role Server for both G2-Arrays and G2-lists




;;; Nth-Element Designation and Role:
;;;    (the (nth-element item-or-datum) designation index-expression)
;;;
;;;    (the ((nth-element item-or-datum) . local-name) 
;;;         designation index-expression)
;;;    Note that nth-element currently does not parse with local-names.  cpm,
;;;    5/7/91


;;; The `nth-element' role-server serves a g2-array or g2-list element given by
;;; the index location.  There is no inverse role-server from an item element to
;;; the g2-array or g2-list.

;;; The `serve-nth-element' role-server serves an element of either a g2-array,
;;; g2-list, or sequence based on an index location.  The type of the object
;;; (i.e., list or array) is determined within the role-server.

;;; The value is served as either an item or an evaluation-value. The
;;; role-server can return "unknown" for item-arrays if there is either no item
;;; or an inactive or deleted item at that element location.  An error is
;;; signaled and unknown is returned when the index references outside of the
;;; array or list.

;; Role service for array and list element(s) required a change to the design
;; of role-service.  The role-servers require multiple-domain arguments, an
;; index expression and an array or list designation.

;; Local name, if present in the role, is ignored.

(def-role-printer nth-element
  (declare (ignore role local-variable?))
  (tformat "nth element of g2-array, g2-list, or sequence"))

(defmacro generic-nth-element-role-and-designation-printer (domain1 domain2)
  `(progn
     (cond
       ((consp ,domain1)
	(twrite-wide-character #.%\()
	(print-designation ,domain1)
	(twrite-wide-character #.%\)))
       (t
	(print-designation ,domain1)))
     (twrite-wide-character #.%\[)
     (write-expression ,domain2)
     (twrite-wide-character #.%\])))


(def-role-and-designation-printer nth-element
  (declare (ignore role))
  (generic-nth-element-role-and-designation-printer
    domain-1? domain-2?))

(def-role (nth-element
	    item-or-value
	    ((or (class g2-array) (class g2-list) (sequence) text) integer))
    (role item-or-value index)
  (declare (ignore role))
  (let* ((index-value (evaluation-integer-value index))
	 (fetched-item-or-evaluation-value?
	   (fetch-nth-element item-or-value index-value nil nil)))
    (cond ((null fetched-item-or-evaluation-value?)
	   (values nil nil nil))
	  (t
	   (values fetched-item-or-evaluation-value? nil 'never)))))

(defun bad-g2-array-index-warning (g2-array bad-index)
  (write-warning-message* 1
    (write-bad-g2-array-index-message g2-array bad-index)))

(defun bad-g2-array-index-error-1 (g2-array bad-index)
  (twith-output-to-error-text
    (write-bad-g2-array-index-message g2-array bad-index)))

(def-substitution-macro bad-g2-array-index-error (g2-array bad-index top-of-stack)
  (raw-stack-error-named-error
    top-of-stack
    (bad-g2-array-index-error-1 g2-array bad-index)))

(defun write-bad-g2-array-index-message (g2-array bad-index)
  (let* ((length (g2-array-length g2-array))
	 (end-index (-f length 1)))
    (if (=f length 0)
	(tformat "The array index ~a is not correct for ~NF.  This array is of length 0."
		 bad-index g2-array)
	(tformat "The array index ~a is not in the range 0 to ~a for ~NF."
		 bad-index end-index g2-array))))

(defun-simple fetch-nth-element
    (item-or-value index-value top-of-stack signal-errors?)
  (let ((element? nil))
    (cond
      ((evaluation-sequence-p item-or-value)
       (let ((sequence-element?
	       (evaluation-sequence-aref item-or-value index-value)))
	 (cond (sequence-element?
		(copy-if-evaluation-value sequence-element?))
	       (signal-errors?
		(cond ((<f -1 index-value
			   (evaluation-sequence-length item-or-value))
		       (if (evaluation-sequence-ref item-or-value index-value)
			   (stack-error
			     top-of-stack
			     "A deleted item was found at index ~a within ~NE."
			     index-value item-or-value)
			   (stack-error
			     top-of-stack
			     "No item-or-value exists at index ~a within ~NE."
			     index-value item-or-value)))
		      ((=f 0 (evaluation-sequence-length item-or-value))
		       (stack-error
			 top-of-stack
			 "The index ~a is not correct for ~NE. This sequence is of length 0."
			 index-value item-or-value))
		      (t
		       (stack-error
			 top-of-stack
			 "The index ~a into the sequence ~NE was out of the ~
                       bounds 0 through ~a."
			 index-value item-or-value
			 (1-f (evaluation-sequence-length item-or-value))))))
	       (t
		nil))))
      ((evaluation-text-p item-or-value)
       (let ((wide-string (evaluation-text-value item-or-value)))
	 (cond ((<=f 0 index-value (1-f (wide-string-length wide-string)))
		(make-evaluation-integer
		 (char-codew (charw wide-string index-value))))
	       (signal-errors?
		(stack-error
		  top-of-stack
		  "The index ~a into the text ~NE was out of the bounds 0 ~
                   through ~a."
		  index-value item-or-value
		  (1-f (wide-string-length item-or-value))))
	       (t
		nil))))
      ((not (framep item-or-value))
       (if signal-errors?
	   (stack-error
	     top-of-stack
	     "Cannot reference element ~a of ~NF.  It is neither a g2-list, ~
              g2-array, sequence, or text."
	     index-value item-or-value)
	   nil))
      ((g2-array-p item-or-value)
       (cond 
	 ((not (g2-array-index-ok-p item-or-value index-value))
	  ;; Issue a stack-error when errors are being signalled, e.g., when "no
	  ;; value" is not allowed.  Otherwise, do not give a warning.
	  (when signal-errors?
	    (bad-g2-array-index-error item-or-value index-value top-of-stack))
	  nil)
	 ((eq (g2-array-element-type item-or-value) 'float)
	  ;; Note that the call to managed-g2-array should not be within the
	  ;; call to managed-float-aref, it affects the ability to optimize the
	  ;; float handling.  -jra 1/29/92
	  (let ((managed-float-array
		 (access-once (managed-g2-array item-or-value))))
	    (make-evaluation-float
	      (managed-float-aref managed-float-array index-value))))
	 ((null (setq element?
		      (g2-array-aref-item-or-evaluation-value item-or-value index-value)))
	  ;; This is not a level 1 warning, since it could be expected to
	  ;; have no value or an inactive item at an array position.
	  (when signal-errors?
	    (stack-error
	      top-of-stack
	      "The g2-array ~NF contains no element at index ~a."
	      item-or-value index-value))
	  nil)
	 ((or (not (framep element?)) (serve-item-p element?))
	  element?)
	 (signal-errors?
	  (stack-error
	    top-of-stack
	    "A reference to element ~a of ~NF failed because the item at ~
             that location, ~NF, was disabled or inactive."
	    index-value item-or-value element?))
	 (t nil)))
      ((g2-list-p item-or-value)
       (cond
	 ((g2-list-empty-p item-or-value)
	  (when signal-errors?
	    (stack-error
	      top-of-stack
	      "Cannot access element ~a of ~NF.  This g2-list contains no ~
               elements."
	      index-value item-or-value))
	  nil)
	 ((null (setq element?
		      (nth-g2-list-item-or-evaluation-value index-value item-or-value t)))
	  ;; The nth element was not found.  The index is outside of the bounds
	  ;; of the list.
	  (when signal-errors?
	    (stack-error
	      top-of-stack
	      "Cannot reference an element at index ~a in the ~
               g2-list ~NF.  The index must be in the range from 0 ~
               to below the number of list elements, which is ~a."
	      index-value item-or-value (g2-list-length item-or-value)))
	  nil)
	 ((or (not (framep element?)) (serve-item-p element?))
	  element?)
	 (signal-errors?
	  (stack-error
	    top-of-stack
	    "Unable to reference element ~a of ~NF."
	    index-value item-or-value))
	 (t
	  nil)))
      (signal-errors?
       (stack-error
	 top-of-stack
         "Cannot reference element ~a of ~NF.  It is neither a g2-list ~
          nor a g2-array."
	 index-value item-or-value))
      (t
       (warning-message*
	 1
	 "Cannot reference element ~a of ~NF.  It is neither a g2-list ~
          nor g2-array."
	 index-value item-or-value)
       nil))))



;;; The `element-iterator role server' serves elements of both g2-lists and
;;; g2-arrays.  The elements of both of these can be filtered by the element
;;; type specified in the grammar.  If any element contains no value, e.g., an
;;; item array element, that element is not served and the remaining elements
;;; with values are served.

;;; Note that the inverse of this role-server only serves item-lists since items
;;; maintain a back pointer from the item element to the list that contains that
;;; element.

;;; In pre-3.0, this role server was called list-iterator and only served list
;;; elements.  Since 3.0 requires a reparse of expressions, we were able to
;;; change the name.

;; The element-iterator role-server has been rewritten below to use
;; continuations for g2-arrays.  cpm, 11/6/91.

(def-role-printer element-iterator
  (print-user-or-datum-type (second role))
  (when local-variable?
    (tformat " ~(~a~)" local-variable?))
  (twrite-string " in"))

(def-role (element-iterator nil ((or (class g2-list) (class g2-array)
				     (sequence))))
	  (role domain)
  (let ((desired-element-type (second role))
	(element-type nil))
    ;; Note that the desired and actual element types are not actual
    ;; type-specifications.  These are either datum types, such as symbol, or a
    ;; class name, such as water-tank.
    (cond
      ((evaluation-sequence-p domain)
       (serve-evaluation-sequence-values domain desired-element-type))
      ((g2-list-p domain)
       (setq element-type (list-type domain))
	(cond
	  ((not (g2-list-or-array-type-ok-p desired-element-type element-type t))
	   (if (or (classp desired-element-type)
		   (valid-type-specification-p desired-element-type))
               (warning-message*
                 1
                 "~NT is an element-type that is not correct for ~NF.  ~
                  ~NF is a g2-list that has an element-type of ~NT."
                 desired-element-type domain domain element-type)
	       (warning-message*
		 1
		 "~a is not a correct element-type for the g2-list ~NF. ~
                  ~a is not a defined class or type."
		 desired-element-type domain desired-element-type))
	   (values nil nil nil))
	  ((g2-list-empty-p domain)
	   (values nil nil nil))
	  (t
	   ;; List of items or evaluation-values.
	   (let* ((g2-list-structure? (list-structure domain))
		  (structure-head #-Lockfree-List
				  (g2-list-structure-head g2-list-structure?)
				  #+Lockfree-List
				  (g2-list-structure-next
				    (g2-list-structure-head g2-list-structure?)
				    g2-list-structure?))
		  (next-element (g2-list-structure-next structure-head g2-list-structure?))
		  (skip-element-test?
		    ;; Test if all elements are a subtype or subclass of the
		    ;; desired type.
		    (g2-list-or-array-type-ok-p
		      desired-element-type element-type nil)))
	     (if #-Lockfree-List (eq next-element g2-list-structure?)
		 #+Lockfree-List (null next-element)
		 ;; Only 1 possible element to serve.
		 (let ((item-or-value-to-serve
			 (list-element-value structure-head)))
		   (cond ((framep item-or-value-to-serve)
			  (if (and (or skip-element-test?
				       (item-ok-for-g2-list-or-array-p
					 item-or-value-to-serve
					 desired-element-type))
				   (serve-item-p item-or-value-to-serve))
			      (values item-or-value-to-serve nil 'never)
			      (values nil nil nil)))
			 ((and item-or-value-to-serve
			       (or skip-element-test?
				   (datum-ok-for-g2-list-or-array-p
				     item-or-value-to-serve desired-element-type)))
			  (values (copy-evaluation-value item-or-value-to-serve) nil 'never))
			 (t
			  (values nil nil nil))))
		 ;; More than 1 possible element to serve.
		 (let ((continuation
			 (eval-cons
			   #'serve-remaining-list-elements
			   (eval-cons
			     structure-head
			     (if skip-element-test?
				 nil
				 desired-element-type)))))
		   (setf (list-open-continuations domain)
			 (eval-cons continuation
				    (list-open-continuations domain)))
		   (serve-remaining-list-elements t continuation)))))))
      ((g2-array-p domain)
       (setq element-type
	     (if (eq (g2-array-element-type domain) 'quantity)
		 'number
		 (g2-array-element-type domain)))
       (cond
	 ((not (g2-list-or-array-type-ok-p desired-element-type element-type t))
	  ;; The elements cannot be of the correct type.
	   (if (or (classp desired-element-type)
		   (valid-type-specification-p desired-element-type))
	       (warning-message*
		 1
		 "The element type ~a is not valid for the g2-array ~a."
		 desired-element-type
		 (get-or-make-up-designation-for-block domain))
	       (warning-message*
		 1
		 "~a is not a correct element-type for the g2-array ~NF. ~
                  ~a is not a defined class or type."
		 desired-element-type domain desired-element-type))
	  (values nil nil nil))
	 (t
	  (let* ((possible-item-element-p?
		  (g2-list-or-array-element-type-may-contain-item-p
		    element-type))
		 (array-length (g2-array-length domain))
		 (skip-element-test?
		    ;; Test if all the elements are a subtype or subclass of the
		    ;; desired type.
		   (g2-list-or-array-type-ok-p
		     desired-element-type element-type nil)))
	    (fixnum-case array-length
	      (0 (values nil nil nil))
	      (1 (let ((item-or-evaluation-value-element?
			 (g2-array-aref-item-or-evaluation-value domain 0)))
		   (cond
		     ;; No value or one value that's the wrong type or class.
		     ((or (null item-or-evaluation-value-element?)
			  (and (not skip-element-test?)
			       (not (g2-list-or-array-element-ok-p
				      item-or-evaluation-value-element?
				      desired-element-type))))
		      (values nil nil nil))
		     ;; Non-frame (evaluation-value).
		     ((or (null possible-item-element-p?)
			  (not (framep item-or-evaluation-value-element?)))
		      (values item-or-evaluation-value-element? nil 'never))
		     ;; Frame
		     ((serve-item-p item-or-evaluation-value-element?)
		      (values item-or-evaluation-value-element? nil 'never))
		     ;; Non-servable frame.
		     (t
		      (values nil nil nil)))))
	      (t
	       (let ((continuation
			(eval-cons
			  #'serve-remaining-g2-array-elements
			  (eval-cons
			    domain
			    (eval-cons
			      0		;next array index
			      (if skip-element-test?
				  nil
				  desired-element-type))))))
		  (serve-remaining-g2-array-elements t continuation))))))))
      (t
       (warning-message*
	 1
	 "Cannot iterate over the elements in ~NF.  It is not a g2-list, ~
          g2-array, or sequence."
	 domain)
       (values nil nil nil)))))



;;; First pass functions for serving sequences.  These should do something
;;; better than copying all elements of the given sequence, perhaps something
;;; like holding onto a current iteration index.  FIND ME, JRA!  -jra 6/16/96

(defun serve-next-evaluation-sequence-value (continue? continuation)
  (cond
    ((null continue?)
     (loop for elt in (cddr-of-conses continuation) do
       (reclaim-if-evaluation-value elt)
	   finally (progn
		     (reclaim-frame-serial-number (cadr-of-conses continuation))
		     (reclaim-eval-list continuation))))
    ((null continuation)
     (values nil nil nil))
    (t
     (let ((list? (cddr-of-conses continuation)))
       (if list?
	   (let* ((elt-to-serve (car-of-cons list?))
		  (frame-serial-number (cadr-of-conses continuation))
		  (rest? (cdr-of-cons list?))
		  (next-continuation?
		    (cond ((null rest?)
			   (reclaim-eval-list continuation)
			   nil)
			  (t
			   (setf (cddr continuation) rest?)
			   (reclaim-eval-cons list?)
			   continuation))))
	     (if (and (frame-or-deleted-frame-p elt-to-serve)
		      (frame-has-been-reprocessed-p
			elt-to-serve frame-serial-number))
		 (if next-continuation?
		     (serve-next-evaluation-sequence-value
		       t next-continuation?)
		     (progn
		       (reclaim-frame-serial-number frame-serial-number)
		       (values nil nil nil)))
		 (progn
		   (unless next-continuation?
		     (reclaim-frame-serial-number frame-serial-number))
		   (values elt-to-serve next-continuation? 'never))))
	   (progn
	     (reclaim-frame-serial-number (cadr-of-conses continuation))
	     (reclaim-eval-list continuation)
	     (values nil nil nil)))))))


(defun serve-evaluation-sequence-values (sequence desired-element-type)
  (serve-next-evaluation-sequence-value
    t
    (eval-cons
      #'serve-next-evaluation-sequence-value
      (eval-cons
	(copy-frame-serial-number (current-frame-serial-number))
	(loop with class-spec = (eval-list 'class desired-element-type)
	      with type-spec = (or (type-specification-for-user-or-datum-type
				     desired-element-type)
				   class-spec)
	      for elt being each evaluation-sequence-element of sequence
	      when (type-specification-type-p elt type-spec)
		collect (copy-if-evaluation-value elt) using eval-cons
	      finally (reclaim-eval-list-given-tail
			class-spec (cdr-of-cons class-spec)))))))




;;; The "element-iterator inverse role server' only serves the inverse for
;;; item-lists since items maintain a pointer to the lists that they belong to.
;;; It serves the lists that an item is an element of.

(def-role-inverse element-iterator (item quantifier role domain-designation)
  (let ((desired-list-type (second role)))
    (cond ((null (framep item))
	   ;; No warning message, since g2-list elements can be non-items.
	   (values nil nil nil))
	  (t
	   (loop for g2-list-element-structure in (list-elements-for-item item)
		 for g2-list = (list-frame g2-list-element-structure)
		 for g2-list-type = (list-type g2-list)
		 when (and (designation-could-denote-item-p
			     domain-designation g2-list)
			   (or (neq quantifier 'the)
			       ;; The item is the only thing in the list, this
			       ;; check could be made faster if you want.
			       (unique-value-of-role-p item role g2-list))
			   ;; check the type of role.
			   (g2-list-or-array-type-ok-p
			     desired-list-type g2-list-type t)
			   ;; check the item for the desired type.
			   (g2-list-or-array-element-ok-p
			     item desired-list-type))
		   collect g2-list into result using eval-cons
		 finally
		   (return
		     (serve-all-unreprocessed-frames result)))))))


;;; the `member-iterator' role is designed to allow the user to iterate over the
;;; the lists that contain the item

(def-role-printer member-iterator
  (tformat "~(~a~)~a~a that contains"	; class lowercase, local uppercase
	   (second role)		; class
	   (if local-variable? " " "")
	   (or local-variable? "")))

(def-role (member-iterator  (class g2-list)) (role item)
  (serve-all-unreprocessed-frames
    (let* ((desired-list-type (second role))
	   (class-description (class-description desired-list-type)))
      (when class-description
	(loop with list-of-g2-lists-to-return = nil
	      for g2-list-element-structure in (list-elements-for-item item)		 
	      for g2-list = (list-frame g2-list-element-structure)
	      when (and (frame-of-class-description-p g2-list class-description)
			(not (memq g2-list list-of-g2-lists-to-return)))
		do (eval-push g2-list list-of-g2-lists-to-return)
	      finally (return list-of-g2-lists-to-return))))))

(def-role-inverse member-iterator (item quantifier role domain-designation)
  (declare (ignore quantifier role))
  (let (frame-or-frames)
    (cond ((symbolp domain-designation)
	   (setq frame-or-frames
		 (frame-or-frames-with-this-name domain-designation))
	   (cond ((null (framep item))
		  ;; No warning message, since g2-list elements can be non-items.
		  (values nil nil nil))
		 (t
		  (when (loop for element in (list-elements-for-item frame-or-frames)
			      for comparison-list = (list-frame element)
			      do
			  (when (eq comparison-list item)
			    (return t)))
		    (values item nil 'never)))))
	  ;; need to do the fole service
	  (t
	   (let ((class? (atomic-class-element-of-designation
			 domain-designation))
		 (is-list (and (framep item) ;; SoftServe added.
			       (class-description-of-class-p 
				 (class-description-slot item) 'g2-list))))
	     (unless is-list (notify-user-at-console-and-on-logbook "~%~S~%" 
			      (twith-output-to-text-string
			       (twrite-string "Error: Supplied for rule class ")
			       (when (framep item) 
				 (twrite-string (string (class item))))
			       (twrite-string " is not a g2-list instance and can not be used with \'that contains\' expression"))))

	     (when (and class? is-list
			(loop for element being each g2-list-element in item
			      do
			  (when (and (framep element)
				     (subclassp (class element) class?))
			    (return t)))
			(serve-item-p item))
	       (values item nil 'never)))))))


(defun serve-remaining-list-elements (continue? continuation)
  (let* ((second-cons (cdr continuation))
	 (element-structure-or-list-cons (car second-cons))
	 (desired-element-type? (cdr second-cons)))
    (cond ((or (null continue?) (consp element-structure-or-list-cons))
	   ;; Don't serve a next value.  A second continuation element of
	   ;; (<g2-list>) indicates the continuation should be ended.
	   ;; Previously, this element was nil, but this did not provide a way
	   ;; of dropping the g2-list's pointer to the continuation before
	   ;; reclaiming it.  cpm, 9/24/91
	   (let* ((frame?
		    (cond ((null element-structure-or-list-cons) nil)
			  ((consp element-structure-or-list-cons)
			   (car element-structure-or-list-cons))
			  (t (list-frame element-structure-or-list-cons))))
		  (g2-list-frame-p? (and frame? (g2-list-p frame?))))

	     (when g2-list-frame-p?
	       (setf (list-open-continuations frame?)
		     (delete-eval-element
		       continuation
		       (list-open-continuations frame?)))))
	   (when (consp element-structure-or-list-cons)
	     (reclaim-eval-list element-structure-or-list-cons))
	   (reclaim-eval-list-given-tail continuation second-cons)
	   (values nil nil nil))
	  (element-structure-or-list-cons
	   (loop with g2-list-frame = (list-frame element-structure-or-list-cons)
		 with list-structure = (list-structure g2-list-frame)
		 with list-type = (list-type g2-list-frame)
		 with possible-item-element-p? =
		 (g2-list-or-array-element-type-may-contain-item-p
		   list-type)
		 with item-element-p? =
		 (and possible-item-element-p?
		      (not (eq list-type 'item-or-datum)))
		 for item-or-value-to-serve = (list-element-value element-structure-or-list-cons)
					 then (list-element-value next-element-structure)
		 for next-element-structure = (g2-list-structure-next element-structure-or-list-cons
								      list-structure)
					 then (g2-list-structure-next next-element-structure
								      list-structure)
		 for serve-item-or-value-p? =
		 (and (or (null desired-element-type?)
			  (cond
			    ((and item-element-p? (framep item-or-value-to-serve))
			     (item-ok-for-item-list-or-item-array-p
			       item-or-value-to-serve
			       desired-element-type?))
			    ((not item-element-p?)
			     (g2-list-or-array-element-ok-p
			       item-or-value-to-serve
			       desired-element-type?))))
;			    (datum-ok-for-g2-list-or-array-p t nil)))
;			  (if item-element-p?
;			      (item-ok-for-item-list-or-item-array-p
;				item-or-value-to-serve
;				desired-element-type?)
;			      (g2-list-or-array-element-ok-p
;				item-or-value-to-serve
;				desired-element-type?)))
		      (or (null possible-item-element-p?)
			  (null (framep item-or-value-to-serve))
			  (serve-item-p item-or-value-to-serve)))
		 until #-Lockfree-List (eq next-element-structure list-structure)
		       #+Lockfree-List (null next-element-structure)
		 do
	     (when serve-item-or-value-p?
	       (setf (second continuation) next-element-structure)
	       (return-from serve-remaining-list-elements
		 (values (if (and possible-item-element-p?
				  ;; Check for frames, only when necessary.
				  (framep item-or-value-to-serve))
			     item-or-value-to-serve
			     (if item-or-value-to-serve
				 (copy-evaluation-value item-or-value-to-serve) nil))
			 continuation 'never)))

		 finally
		   (setf (list-open-continuations g2-list-frame)
			 (delete-eval-element
			   continuation
			   (list-open-continuations g2-list-frame)))
		   (reclaim-eval-list-given-tail continuation second-cons)
		   (return-from serve-remaining-list-elements
		     (if serve-item-or-value-p?
			 (values
;			   (cond ((and possible-item-element-p?
;				     (framep item-or-value-to-serve))
;				item-or-value-to-serve)
;			       ((not (null item-or-value-to-serve))
;				(copy-evaluation-value item-or-value-to-serve))
;			       (t nil))
			   (if (and possible-item-element-p?
				    (framep item-or-value-to-serve))
			       item-or-value-to-serve
			       (if item-or-value-to-serve
				   (copy-evaluation-value item-or-value-to-serve) nil))
			   nil 'never)
			 (values nil nil nil)))))
	  (t
	   (reclaim-eval-list-given-tail continuation second-cons)
	   (values nil nil nil)))))



;;; The function `serve-remaining-g2-array-elements' is used as a continuation
;;; function to serve g2-array elements.  This is more efficient than consing up
;;; a list of the elements and serving that list.  Also, this function serves
;;; the current array elements instead of the elements that were present when
;;; the role-service began.  Changing the length of the array during
;;; role-service can affect the values served by this function.  This function
;;; may be serving elements based on the element-type-filter value in the
;;; continuation.

;;; The continuation checks if the array length shrunk so that the index is now
;;; out-of-bounds

;;; The continuation is of the form:
;;;   (CONTINUATION-FUNCTION G2-ARRAY NEXT-ELEMENT-INDEX . ELEMENT-TYPE-FILTER?)

(defun serve-remaining-g2-array-elements (continue? continuation)
  (gensym-dstruct-bind
    ((nil g2-array starting-index . element-type-filter?) continuation)
    (let* ((g2-array-length (g2-array-length g2-array))
	   (element-type (g2-array-element-type g2-array))
	   (possible-item-element-p?
	     (g2-list-or-array-element-type-may-contain-item-p element-type)))
      (cond ((null continue?)
	     (reclaim-eval-list-given-tail continuation (cddr continuation))
	     (values nil nil nil))
	    ((>=f starting-index g2-array-length)
	     (reclaim-eval-list-given-tail continuation (cddr continuation))
	     (values nil nil nil))
	    ;; There is a least one possibly servable element.
	    (t
	     (loop for current-index = starting-index then (+f current-index 1)
		   for following-index = (+f current-index 1)
		   for item-or-evaluation-value-element?
		       = (g2-array-aref-item-or-evaluation-value
			   g2-array current-index)
		   with serve-element? = nil
		   with serve-continuation? = nil
		   with serve-expiration? = nil
		   do
	       ;; There is possibly a servable element.  Note that currently, we
	       ;; do not serve elements with no value.  See the documentation at
	       ;; the bottom of this function.  - cpm, 11/26/91
	       (when (and item-or-evaluation-value-element?
			  ;; Check the element type if necessary.
			  (or (null element-type-filter?)
			      (g2-list-or-array-element-ok-p
				item-or-evaluation-value-element?
				element-type-filter?)))
		 (setq serve-element? 
		       (cond
			 ((or (null possible-item-element-p?)
			      (not (framep item-or-evaluation-value-element?))
			      (serve-item-p item-or-evaluation-value-element?))
			  item-or-evaluation-value-element?)
			 ;; Non-servable frame.
			 (t nil)))
		 (when serve-element?
		   ;; There may be another possible element after this one.
		   (when (<f following-index g2-array-length)
		     (setq serve-continuation? continuation))
		   (setq serve-expiration? 'never)
		   (setf (third continuation) following-index)))
		  ;; GENSYMCID-977: memory leak by using "there exist a quantity in [value-array]"
		  (when (and item-or-evaluation-value-element?
			     (null serve-element?))
		    (reclaim-if-evaluation-value item-or-evaluation-value-element?))
		   until (or (>=f following-index g2-array-length)
			     serve-element?)
		   finally
		     (unless serve-continuation?
		       (reclaim-eval-list-given-tail
			 continuation (cddr continuation)))
		     (return-from serve-remaining-g2-array-elements
		       (values serve-element? serve-continuation?
			       serve-expiration?))))))))

;; Note that, unlike g2-lists, g2-arrays do not keep a list of open
;; continuations on the g2-array frame.  G2-lists need to update the
;; element-structure in the continuation if an item element is removed.  - cpm,
;; 11/25/91.

;; NOTE: Is it ok for this continuation function to return a continuation and no
;; value (i.e., expiration of nil).  This may be useful for item-arrays since
;; they can contain elements with no value.  Check if returning a NIL expiration
;; and value with a continuation causes a problem in SERVE-UNIQUE-VALUE-OF-ROLE
;; or other role service!!  For now, elements with no value will not be served!!
;; - cpm, 11/26/91.






;;;; Roles Server for Possibly Indexed Attributes




;;; The `indexed-attribute' role-server serves instances of a class that contain
;;; a particular attribute value.  It is given a role that may contain an
;;; indexed attribute and tests that the attribute is indexed for the class and
;;; that the attribute value can be indexed.  If this is true, the items that
;;; index this attribute value are served, filtering for the given class.
;;; Otherwise, in the non-indexed case, all instances of the class are returned
;;; and it is up the receiver of the served values to search for items that
;;; contain the given attribute value.  For example, the "there-exists"
;;; iteration expression will still test all items for the correct attribute
;;; value.

;;; This role is used when compiling an expression, such as "there exists" or
;;; "count", that are of the format that can contain an indexed attribute.  The
;;; original class-name role within the expression is replaced by this role to
;;; get the indexed attribute optimization.

;;; As of version 4.0, attributes specified with a class-qualified-name role
;;; can be also indexed.

;; Prints as: "<class> [<local-name>], using the <attribute> of the <class> if
;; indexed with the value [<attribute-value>]" 

(def-role-printer indexed-attribute
  (let* ((attribute-name-or-role (second role))
	 (class (third role))
	 (class-qualifier?
	   (when (class-qualified-name-list-p attribute-name-or-role)
	     (car-of-cons (cdr-of-cons attribute-name-or-role))))
	 (attribute-name
	   (if (symbolp attribute-name-or-role)
	       attribute-name-or-role
	       (third attribute-name-or-role))))
    (tformat "~a" class)
    (when local-variable?
      (tformat " ~a" local-variable?))
    (twrite-string ", using the ")
    (if class-qualifier?
	(tformat "~NQ " attribute-name class-qualifier?)
	(tformat "~a" attribute-name))
    (tformat " of the ~a if indexed with the value" class)))

(def-role (indexed-attribute nil (datum)) (role attribute-value)
  (gensym-dstruct-bind ((nil attribute-role class) role)
    (let* ((class-qualified-name-p?
	     (class-qualified-name-list-p attribute-role))
	   (class-qualifier?
	       (when class-qualified-name-p?
		 (car-of-cons (cdr-of-cons attribute-role))))
	   (attribute
	       (if class-qualified-name-p?
		   (third attribute-role)
		   attribute-role))	;the attribute name
	   (unpacked-value (evaluation-value-value attribute-value))
	   (indexed-attribute-value?
	     (and (indexed-attribute-or-inherited-attribute-for-class-p
		    attribute class)
		  (valid-indexed-attribute-value-p unpacked-value)
		  unpacked-value))
	   (indexed-attribute-table?
	     (indexed-attribute-hash-table attribute))
	   (class-description? (class-description class)))
      (cond
	((and indexed-attribute-value? indexed-attribute-table?
	      class-description?)
	 (let ((parent-and-class-tree?
		 (get-indexed-attribute-parent-objects
		   indexed-attribute-value? indexed-attribute-table?)))
	   (serve-all-unreprocessed-frames
	     (when parent-and-class-tree?
	       (loop for (hashed-item . defining-classes) being each
		     binary-tree-entry-cons of parent-and-class-tree?
		     for slot-description?
			 = (get-slot-description-of-frame
			     attribute hashed-item class-qualifier?)
		     for defining-class-of-attribute?
			 = (when slot-description?
			     (defining-class slot-description?))
		     when (and (frame-of-class-description-p
				 hashed-item class-description?)
			       (memq defining-class-of-attribute?
				     defining-classes))
		       collect hashed-item using eval-cons)))))
	((and (eq attribute 'uuid) (null class-qualifier?)
	      class-description?
	      t ; (class-description-of-class-p class-description? 'unique-identification)
	      (text-string-p attribute-value))
	 (let ((item-or-item-list (get-item-or-item-list-for-uuid attribute-value)))
	   (serve-all-unreprocessed-frames
	     (cond ((null item-or-item-list)
		    nil)
		   ((atom item-or-item-list)
		    (when (frame-of-class-description-p
			    item-or-item-list
			    class-description?)
		      (eval-list item-or-item-list)))
		   (t
		    (loop for item in item-or-item-list
			  when (frame-of-class-description-p
				 item
				 class-description?)
			    collect item using eval-cons))))))
	((and class-description?
	      (class-description-of-class-p class-description? 'item))
	 ;; Serve all instances of the class.  The caller of the role will need
	 ;; to filter the items based on the attribute value.
	 (serve-first-instance-of-class class))
	(t
	 (values nil nil nil))))))






;;;; Frame or Place Reference Roles




;;; The roles `attribute-frame-or-place-reference' and
;;; `element-frame-or-place-reference' are used as an implementation of setters
;;; for attribute locations and g2-array and g2-list element locations
;;; respectively.

;;; These are implemented through a stack instruction, and so these roles should
;;; only exist temporarily during the compilation of a designation.  However, if
;;; there is a bug where a designation with one of these lands in
;;; evaluate-designation, then it will arrive at this role server, and it should
;;; quietly return nil.

(def-role (attribute-frame-or-place-reference
	    (or (class item) (place-reference))
	    ((or (class item) (place-reference)) symbol))
	  (role parent-frame attribute-name)
  (declare (ignore role parent-frame attribute-name))
  (values nil nil nil))

(def-role (element-frame-or-place-reference
	    (or (class item) (place-reference))
	    ((or (class g2-array) (class g2-list) (place-reference)) integer))
	  (role list-or-array index)
  (declare (ignore role list-or-array index))
  (values nil nil nil))

(def-role (class-qualified-name-frame-or-place-reference
	    (or (class item) (place-reference))
	    ((or (class item) (place-reference))))
    (role parent-frame)
  (declare (ignore role parent-frame))
  (values nil nil nil))
	    






;;;; Class Qualified Name Roles




;;; The role `class-qualified-method' implements fetching of the specific method
;;; with a given name that is most specific to a given class.  Users can access
;;; this role with the "<class>::<name>" grammar.

;;; Note that this role is handled specially in print-designation to suppress
;;; the printing of "the".

(def-role-printer class-qualified-method
  (declare (ignore local-variable?))
  (princ-lowercase (second role))
  (twrite-string "::")
  (princ-lowercase (third role)))


(def-role (class-qualified-method (class method) nil)
    (role domain)
  (declare (ignore domain))
  (let* ((class-cons (cdr-of-cons role))
	 (class (car-of-cons class-cons))
	 (method-name (car-of-cons (cdr-of-cons class-cons)))
	 (method-list?
	   (get-specific-methods-for-class-or-superior-class
	     method-name class)))
    (if method-list?
	;; Note the following does the serve-item-p tests.
	(serve-all-unreprocessed-frames
	  (loop for frame in method-list? collect frame using eval-cons))
	(values nil nil nil))))






;;; Method Roles




;;; The role `next-procedure-method' is used to fetch the next method while
;;; executing a method.  It takes the first argument to the method as its
;;; domain, and takes the class-name for the currently executing method as the
;;; second element of the role and the number of arguments as the third element
;;; of the role.

(def-role (next-procedure-method (class method) ((class item)))
    (role domain)
  (gensym-dstruct-bind ((nil name class arg-count) role)
    (let ((next-method-or-string
	    (get-next-specific-method
	      name class arg-count (class-description-slot domain))))
      (if (text-string-p next-method-or-string)
	  (values nil nil nil)
	  (values next-method-or-string nil 'never)))))

    
  





;;;; Validating Roles




;;; When there are KB changes at runtime (i.e., when G2 is paused or running)
;;; that can affect roles, currently executing roles need to be validated.  Most
;;; roles are either served immediately or collect a list of item-or-values that
;;; will be served.  In these cases, it's too late to do a validation because
;;; the role information is not retained.  What can be validated is role-caches.
;;; So far, these caches are used in connection roles.




;;; The function `validate-role-service' is used to validate currently executing
;;; roles, when there has been a runtime change to the KB.  Note that only
;;; role-caches are validated, not roles that are being served.  This means that
;;; if there was a change to the KB that would have affected role-service, any
;;; roles that are currently being served will continue to serve the values
;;; collected before the change.  This behavior applies also to cached-roles
;;; that are currently being served.  Only the cache is validated and not any
;;; values currently being served.

(defun validate-role-service ()
  (decache-roles-for-all-items))

;; Note that for version 4.0, this function takes a simple approach and removes
;; all cached-roles.  This could be optimized to decache only those roles that
;; relate to the part of the KB that needs validation, for example, because of a
;; modification to an object-definition.  In this case, this function would only
;; need to decache those roles related to the changed class.  - cpm, 3/16/94





;;;; Optimized Service of Unique Values

(defvar unique-value-roles nil)
(def-global-property-name unique-value-of-role-server-macro)
(def-global-property-name unique-value-of-role-server-function)
(def-global-property-name unique-value-of-role-next-role)
(def-global-property-name unique-value-of-role-server-domain-count)

;;; The macro `def-unique-value-of-role-server' defines a substitution macro
;;; that can be used for a more efficient fetch of unique values for roles.
;;; This was designed primarily for use by the code generator of the G2 compiler
;;; so that it would have a more fine-grained target language for role
;;; evaluation.  Unique-value-of-role-servers are allowed to signal
;;; stack-errors.  This macro defines both a substitution macro
;;; and a simple-function that implement the role fetch.  This will
;;; enable the construction of inline (stack) instructions for the
;;; most time-critical roles (e.g. integer and float arrays) and let
;;; others be done by function dispatch.  Note that unique-value-of-role-servers
;;; DO NOT use temporary constants in any way.

(defmacro def-unique-value-of-role-server
    ((role-name more-general-role-name domain-count)
	       (top-of-stack-arg
		 role-arg no-item-arg
		 domain-1-arg . listed-domain-2-arg)
	       &body body)
  (unless (and (fixnump domain-count) (<= 1 domain-count 2))
    (error "roles have either 1 or 2 domains"))
  (unless (if (= domain-count 1)
	      (null listed-domain-2-arg)
	      (and (consp listed-domain-2-arg)
		   (null (cdr listed-domain-2-arg))))
    (error "the number of domain args does not match the domain-count"))
  (let ((unique-value-macro-name
	  (intern (format nil "SERVE-UNIQUE-~a-VALUE-MACRO" role-name)))
	(unique-value-function-name
	  (intern (format nil "SERVE-UNIQUE-~a-VALUE" role-name))))
    `(progn
       (setf (unique-value-of-role-server-domain-count ',role-name)
	     ,domain-count)
       (setf (unique-value-of-role-next-role ',role-name)
	     ',more-general-role-name)
       (pushnew ',role-name unique-value-roles)
       (def-substitution-macro ,unique-value-macro-name
	   (,top-of-stack-arg ,role-arg
			      ,no-item-arg ,domain-1-arg ,@listed-domain-2-arg)
	 ,@body)
       (defun-simple-into-place
	   (,unique-value-function-name
	      (unique-value-of-role-server-function ',role-name))
	   (,top-of-stack-arg ,role-arg
			      ,no-item-arg ,domain-1-arg ,@listed-domain-2-arg)
	 (,unique-value-macro-name
	    ,top-of-stack-arg ,role-arg
	    ,no-item-arg ,domain-1-arg ,@listed-domain-2-arg))
       (setf (unique-value-of-role-server-macro ',role-name)
	     ',unique-value-macro-name))))

  
(defmacro fetch-unique-value-of-role (role-name &rest args)
  (unless (and (symbolp role-name)
	       (unique-value-of-role-server-macro role-name))
    (error "no unique-value-of-role server defined for ~s" role-name))
  `(,(unique-value-of-role-server-macro role-name)
     ,@args))
  
;;; The most important difference between the optimized unique-value-of role
;;; server and the general one is that the domain type has been limited to the
;;; type symbol.  The proof of constraint of domain type is the responsibility
;;; of the caller.


(def-role-printer named-by-symbol
  (print-standard-two-element-role role local-variable? " named by"))

(def-unique-value-of-role-server (named-by-symbol named-by 1)
    (top-of-stack role-constant no-item-allowed-p name) 
  (let* ((class (car-of-cons (cdr-of-cons role-constant)))
	 (class-description? (class-description class))
	 frame-or-frames? unique-item?)
    (cond
      ((null name)
       (setq unique-item? nil))
      ((or (null class-description?)
	   (not (class-description-of-class-p
		  class-description? 'item)))
       (setq unique-item? nil))
      ((consp (setq frame-or-frames?
		    (frame-or-frames-with-this-name name)))
       (setq
	 unique-item?
	 (loop for frame in frame-or-frames?
	       when (and (frame-of-class-description-p
			   frame class-description?)
			 (serve-item-p frame))
		 return frame)))
      ((and frame-or-frames?
	    (frame-of-class-description-p
	      frame-or-frames? class-description?)
	    (serve-item-p frame-or-frames?))
       (setq unique-item? frame-or-frames?))
      (t
       (setq unique-item? nil)))
    (unless (or unique-item? no-item-allowed-p)
      (write-stack-error top-of-stack
       (twrite-string "An attempt was made to reference the ")
       (print-role role-constant)
       (twrite-char #.%space)
       (write-stored-value name)))
    unique-item?))

(def-role-printer name-of-item
  (print-role-whose-car-is-role-server role local-variable?))

(defun name-of-item-invalid-reference-message (role-constant item?)
  (twith-output-to-error-text
    (twrite-string "An attempt was made to reference the ")
    (print-role role-constant)
    (twrite-char #.%space)
    (write-stored-value item?)))

(def-substitution-macro name-of-item-invalid-reference (top-of-stack role-constant item?)
  (raw-stack-error-named-error
    top-of-stack
    (name-of-item-invalid-reference-message role-constant item?)))

(def-unique-value-of-role-server (name-of-item name 1)
    (top-of-stack role-constant no-name-allowed-p item?)
  (let ((name?
	  (cond
	    (item?
	     (let ((name-or-names (name-or-names-for-frame item?)))
	       (cond ((consp name-or-names)
		      (car-of-cons name-or-names))
		     (t
		      name-or-names))))
	    (t
	     nil))))
    (unless (or name? no-name-allowed-p)
      (name-of-item-invalid-reference top-of-stack role-constant item?))
    name?))


(def-role-printer related-to-item
  (print-user-or-datum-type (third role))
  (when local-variable?
    (tformat " ~(~a~)" local-variable?))
  (tformat " that is ~(~a~)" (second role)))


(def-substitution-macro role-returned-no-values-error (top-of-stack role domain-1? domain-2?)
  (raw-stack-error-named-error
    top-of-stack
    (role-returned-no-values-error-1 role domain-1? domain-2?)))

(def-unique-value-of-role-server (related-to-item related 1)
    (top-of-stack role-constant no-item-allowed-p item?)
  (let* ((relation-name (car-of-cons (cdr-of-cons role-constant)))
	 (relation? (get-instance-with-name-if-any 'relation relation-name))
	 (class-name (car-of-cons (cdr-of-cons (cdr-of-cons role-constant))))
	 (class-description? (class-description class-name))
	 (unique-test-not-needed?
	   (when relation?
	     (unique-reverse-relation relation?)))
	 (filter-of-items-not-needed? (eq class-name 'item))
	 related-item?)
    (cond
      ((null item?)
       (setq related-item? nil))
      ;; maybe the following case is paranoid bogosity
      ((or (null class-description?)
	   (not (class-description-of-class-p class-description? 'item)))
       (setq related-item? nil))
      (unique-test-not-needed?
       (when-let (unfiltered-related-items (related-items item? relation-name))
	 (loop for item-2 being each related-item of unfiltered-related-items
	       when (and item-2
			 (serve-item-p item-2)
			 (or filter-of-items-not-needed?
			     (frame-of-class-description-p item-2 class-description?)))
	       do
		 (setq related-item? item-2)
		 (return))))
      (t
       (when-let (unfiltered-related-items (related-items item? relation-name))
	 (loop for item-2 being each related-item of unfiltered-related-items
	       when (and (serve-item-p item-2)
			 (or filter-of-items-not-needed?
			     (frame-of-class-description-p item-2 class-description?)))
	       do
		 (cond
		   ((null related-item?)
		    (setq related-item? item-2))
		   (no-item-allowed-p
		    ;; A second item was found.  Return "no item".
		    (setq related-item? nil)
		    (return))
		   (t
		    ;; In this case, a second related item is an error.
		    (write-stack-error top-of-stack
		      (twrite-string "An attempt was made to reference the ")
		      (print-role role-constant)
		      (tformat
			" ~NF.  Note that this relation exists between ~NF and ~
                         more than one other item."
			item? item?))))))))
    (unless (or related-item? no-item-allowed-p)
      (role-returned-no-values-error
	(-f top-of-stack 1)
	role-constant
	item? nil))
    related-item?))


(def-stack-error no-element-for-array-role-index-error
    (top-of-stack array-type-string array index)
  "The ~a ~NF contains no element at index ~a."
  array-type-string array index)


(def-role-printer nth-element-of-integer-array
  (declare (ignore role local-variable?))
  (tformat "nth element of integer-array"))

(def-role-and-designation-printer nth-element-of-integer-array
  (declare (ignore role))
  (generic-nth-element-role-and-designation-printer
    domain-1? domain-2?))

(def-unique-value-of-role-server (nth-element-of-integer-array
				   nth-element 2)
    (top-of-stack role-constant no-item-allowed-p array index)
  role-constant no-item-allowed-p
  (let ((length (g2-array-length array))
	integer-value?)
    (cond ((or (<f index 0)
	       (>=f index length))
	   (bad-g2-array-index-error array
				     index
				     top-of-stack)
	   (setq integer-value? nil))
	  (t
	   (let ((managed-array (managed-g2-array array)))
	     (setq integer-value?
		   (copy-evaluation-integer
		     (managed-svref managed-array index))))))
    (unless integer-value?
      (no-element-for-array-role-index-error
	top-of-stack "integer array" array index))
    integer-value?))

(def-role-printer nth-element-of-float-array
  (declare (ignore role local-variable?))
  (tformat "nth element of float-array"))

(def-role-and-designation-printer nth-element-of-float-array
  (declare (ignore role))
  (generic-nth-element-role-and-designation-printer
    domain-1? domain-2?))

;; fetch-nth-ele

(def-unique-value-of-role-server (nth-element-of-float-array
				   nth-element 2)
    (top-of-stack role-constant no-item-allowed-p array index)
  role-constant no-item-allowed-p
  (let ((length (g2-array-length array))
	float-value?)
    (cond ((or (<f index 0)
	       (>=f index length))
	   (bad-g2-array-index-error array
				     index
				     top-of-stack)
	   (setq float-value? nil))
	  (t
	   (setq float-value?
		 (make-evaluation-float
		   (managed-float-aref
		     (managed-g2-array array) index)))))
    ;; the no value case is not possible because
    ;; the storage object MUST contain floats
    float-value?))

(def-role-printer nth-element-of-value-array
  (declare (ignore role local-variable?))
  (tformat "nth element of value-array"))

(def-role-and-designation-printer nth-element-of-value-array
  (declare (ignore role))
  (generic-nth-element-role-and-designation-printer
    domain-1? domain-2?))

(def-unique-value-of-role-server (nth-element-of-value-array
				   nth-element 2)
    (top-of-stack role-constant no-item-allowed-p array index)
  role-constant no-item-allowed-p
  (cond
    ((null (managed-g2-array array))
     nil)
    (t
  (let ((length (g2-array-length array))
	(float-array? (eq (g2-array-element-type array) 'float))
	value?)
    (cond ((or (<f index 0)
	       (>=f index length))
	   (bad-g2-array-index-error array
				     index
				     top-of-stack)
	   (setq value? nil))
	  (float-array?
	   (setq value?
		 (make-evaluation-float
		   (managed-float-aref
		     (managed-g2-array array) index))))
	  (t
	   (setq value?
		 (managed-svref (managed-g2-array array) index))
	   (when value?
	     (setq value?
		   (if (eq (g2-array-element-type array) 'truth-value)
		       (make-evaluation-truth-value value?)
		       (copy-evaluation-value value?))))))
    (unless value?
      (no-element-for-array-role-index-error
	top-of-stack "value array" array index))
    value?))))

;;; `faction' role

#+mtg2
(progn
  (def-role-printer faction
      (print-role-whose-car-is-role-server role local-variable?))

  (def-role faction (role domain)
    (declare (ignore role))
    (let ((fc (faction? domain)))
      (if (and fc (serve-item-p fc))
	  (values fc nil 'never)
	  (values nil nil nil))))
  
  (def-role-inverse faction (faction quantifier role domain-designation)
    (declare (ignore quantifier role))
    (cond
      ((not (of-class-p faction 'faction))
       (values nil nil nil))
      
      (t (loop for frame being each faction-member of faction
	    when (and (frame-of-class-p frame 'item)
		      (serve-item-p frame)
		      (designation-could-denote-item-p domain-designation frame))
	    collect frame into item-list using eval-cons
	    finally (return (serve-all-unreprocessed-frames item-list)))))))
  
;;; `this-faction' role

#+mtg2
(progn
  (def-role-printer this-faction
      (declare (ignore role local-variable?))
    (tprinc "this faction"))

  (defun get-this-faction ()
    (when *current-computation-frame*
      (let ((workspace?
	     (nth-value
	      1 (get-block-on-workspace-for-frame
		 *current-computation-frame*))))
	(when workspace? (faction? workspace?)))))
  
  (def-role (this-faction nil nil) (role domain)
    (declare (ignore role domain))
    (let ((faction? (get-this-faction)))
      (if (and faction? (serve-item-p faction?))
	  (values faction? nil 'never)
	  (values nil nil nil))))
  
  (def-role-inverse this-faction (faction quantifier role domain-designation)
    (declare (ignore faction quantifier role domain-designation))
    (values nil nil nil)))

;;;; Summary of roles




;;; This summary contains all the roles currently in G2. The left column
;;; contains a designation with the article "the" if the role is single valued,
;;; and "any" if the role is multi-valued. The right column contains the
;;; translation of the role only. If there is a local name, it is consed with
;;; the role. The general form for a designation with a role is (Q R D) where Q
;;; is a quantifier ("the" or "any"), R is the role with or without local name,
;;; and D is a designation. In the following, D is a designation, A is an
;;; attribute name, C is a class name, and N is an object name.

;; The ? means that I am not sure of the form.

;;; the A of D				A
;;; any name of D			(ROLE-SERVER NAME)
;;; any C named by D			(NAMED-by C)
;;;
;;; the C nearest to D			(NEAREST C)
;;;
;;; the icon-color of D, etc.		(ITEM-COLOR keyword SYMBOL)
;;; the icon-x-position of D		(ROLE-SERVER ITEM-X-POSITION)
;;;	similarly icon-y-position, icon-width, icon-height, icon-heading,
;;;	item-x-position, item-y-position, item-width, item-height
;;;
;;; any C connected to D		(CONNECTED-TO C)
;;; any C connected at an/the input of/to D
;;; 					(AT-AN-INPUT C)
;;; any C connected at an/the output of D
;;; 					(AT-AN-OUTPUT C)
;;; any C at an/the input end of D	(AT-INPUT-END C)
;;; any C at an/the output end of D	(AT-OUTPUT-END C)
;;; any C at either end of D		(AT-EITHER-END)
;;;
;;; the subworkspace of D		(ROLE-SERVER SUBWORKSPACE KB-WORKSPACE)
;;; the workspace of D			(ROLE-SERVER WORKSPACE KB-WORKSPACE)
;;; the faction of D			(ROLE-SERVER FACTION FACTION) ; mtg2
;;; the C superior to D			(SUPERIOR-ITEM C)
;;; any C upon D			(UPON C)
;;;
;;; the symbol that is a superior-class of
;;;                                     (SUPERIOR-CLASS SYMBOL)
;;; the symbol that is an inferior-class of
;;;                                     (INFERIOR-CLASS SYMBOL)
;;;
;;; this workspace			(ROLE-SERVER THIS-WORKSPACE KB-WORKSPACE)
;;; this faction			(ROLE-SERVER THIS-FACTION FACTION) ; mtg2
;;; this window				(ROLE-SERVER THIS-WINDOW G2-WINDOW)
;;; this rule			        (ROLE-SERVER THIS-RULE RULE)
;;; this procedure			(ROLE-SERVER THIS-PROCEDURE PROCEDURE)
;;; this procedure-invocation		(ROLE-SERVER THIS-PROCEDURE-INVOCATION 
;;;                                                  PROCEDURE-INVOCATION)
;;;
;;; the workspace named N		(NAMED N KB-WORKSPACE)
;;;
;;; any C that is R D			(RELATED R C) 

;;; G2-LISTS:
;;;
;;; the first <g2-list-element-type> in <g2-list>         
;;;                                     (FIRST-OF-LIST <g2-list-element-type>)
;;; the second <g2-list-element-type> in <g2-list>
;;;                                     (SECOND-OF-LIST <g2-list-element-type>)
;;; the next to last <g2-list-element-type> in <g2-list>
;;;                                     (NEXT-TO-LAST-OF-LIST <g2-list-element-type>)
;;; the last <g2-list-element-type> in <g2-list>
;;;                                     (LAST-OF-LIST <g2-list-element-type>)
;;;
;;; any <g2-list-element-type> in <g2-list>
;;;                                     (LIST-ITERATOR <g2-list-element-type>)

;;; Source language and keywords for icon-color: (R is a region name.)

;;; the icon-color of D			icon-color
;;; the R icon-color of D		R
;;; the stripe-color of D		stripe-color
;;; the R stripe-color of D		R
;;; the text-color of D			text-color
;;; the background-color of D		background-color
;;; the foreground-color of D		foreground-color
;;; the border-color of D		border-color

;;; attribute-value (item, attribute)   (ATTRIBUTE-VALUE ITEM-OR-DATUM)

;;; <g2-array-or-list> [<index>]        (NTH-ELEMENT ITEM-OR-DATUM)

;;; <class>::<name>                     (CLASS-QUALIFIED-METHOD class name)

;;; the <class>::<attribute-name> of D  (CLASS-QUALIFIED-NAME class attribute-name)

;;; (subpart of the next method exists and call next method, in procedure
;;; methods only)
;;;                                     (NEXT-PROCEDURE-METHOD name class arg-count)


;;; SEE PRINT-ROLE IN FILE EVAL!

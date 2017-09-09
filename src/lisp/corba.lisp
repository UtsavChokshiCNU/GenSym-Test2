;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module CORBA

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; John Hodgkinson

;; jh, 11/19/95.  Takes the output of the IDL parser and creates items in G2 and
;; GSI that enable CORBA integration.

;;;; In Progress

;;; G2 as client
;;;   G2 item specs from parse
;;;     x coded
;;;     x initial tests
;;;     commented
;;;   G2 items from item specs
;;;     evaluator for constants
;;;     transient object-definitions
;;;     transient method-definitions
;;;     transient remote-procedure-declarations
;;;     commented
;;;   GSI bridge from parse
;;;     x storing case-sensitive names
;;;     marshalling from G2 to GSI
;;;     marshalling from GSI to G2
;;;     commented
;;;   compiling the GSI bridge
;;;   launching the GSI bridge
;;;   initial test of G2 as client
;;; G2 as legacy server
;;; G2 as stubs server

;;;; Overview

;;; Helpful Acronyms
;;; ----------------
;;; CORBA Common Object Request Broker Architecture
;;; ORB   Object Request Broker
;;; IDL   Interface Description Language
;;; OMG   Object Management Group

;;; This module offers three sorts of CORBA integration with G2: `CORBA client',
;;; `CORBA legacy server', and `CORBA stubs server'.  In all three sorts of
;;; integration, a knowledge base is populated with G2 items that provide
;;; visibility to an ORB.  These items are typically object-definitions,
;;; method-definitions, and remote-procedure declarations.  The general term
;;; `CORBA integration item' denotes any such item.

;;; Since there is no IDL mapping that lets the "G2 language" communicate
;;; directly with an ORB, G2 codes and spawns a GSI bridge written in a language
;;; that does have a mapping, namely C++.  G2 then communicates with the bridge
;;; via remote procedure invocation, and the bridge in turn communicates with
;;; the ORB.

;;; To turn G2 into a CORBA client, a KB is populated with object-definitions
;;; (representing IDL interfaces and compound data types) and methods
;;; (representing IDL operations).  Once this is done, G2 uses these items as it
;;; would local items: it creates instances from object-definitions and invokes
;;; methods on those instances.  But these methods are implemented elsewhere and
;;; are accessed through an ORB.  The remote procedures in this case go from G2
;;; to GSI.

;;; To turn G2 into a CORBA legacy server, items in an existing KB are marked
;;; for export.  How this marking will be done is a UI issue.  For now (jh,
;;; 12/5/95), we will assume the items are in a g2-list handed to a system
;;; procedure.  Once the CORBA bridge is running, other processes have access to
;;; these items through an ORB.  The remote procedures in this case go from GSI
;;; to G2.  We need to decide what to do with G2 items that have no mapping into
;;; IDL (e.g. "you have marked an instance for CORBA export; perhaps you want to
;;; export the corresponding object-definition?")

;;; To turn G2 into a CORBA stubs server, G2 items are generated from an IDL
;;; source file.  These items represent the IDL interface with the ORB.  Once
;;; the KB developer provides an implementation of the items (makes the methods
;;; do something, and so forth), other process can access them through an ORB.
;;; The remote procedures in this case go from GSI to G2.

;;; When G2 acts as server, it binds new instances via `shared activation'.
;;; This is an OMG term meaning that a single G2 process creates many instances
;;; of the same IDL interface.  Other types of activation, which we may
;;; implement in the future, include `unshared activation', where a new process
;;; is spawned for each new instance of an IDL interface, and `per-method
;;; activation', where each operation spawns a new process.

;;; As with any CORBA client, it is transparent to a G2 CORBA client what sort
;;; of activation ahppens to implement the interface it is using.

;;;; Specs for CORBA Integration Items

;;; The policy is: one def-structure per G2 item or module. (Modules should be a
;;; first-class item in G2, but are not yet.)  The :include hierarchy of the
;;; structure definitions mirrors IDL rather than G2.

(def-structure g2-corba-definition-mixin
  idl-definition-name-as-symbol       ;symbol
  (idl-definition-name-as-text        ;reclaimable text-string
    nil           
   :reclaimer reclaim-if-text-string)
  idl-source-filename                 ;shared text-string
  g2-to-corba-relationship            ;symbol: CLIENT, STUB-SERVER, or LEGACY-SERVER
  (nearest-enclosing-idl-spec? nil)   ;shared g2-corba-definition-mixin or nil
  )

(def-hash-table idl-namespace-hash-table
    :constructor      make-idl-namespace-hash-table
    :accessor         look-up-in-idl-namespace
    :entry-reclaimer  reclaim-if-idl-list
    :clearer          clear-idl-namspace-hash-table
    :key-comparitor   eq
    :size             67 ; use a prime number
    )

(defvar idl-top-level-namespace (make-idl-namespace-hash-table))

(def-structure (g2-corba-containing-definition-mixin
		 (:include g2-corba-definition-mixin))
  (idl-namespace                        ;an idl-namespace-hash-table
    (make-idl-namespace-hash-table)
    :reclaimer reclaim-idl-namespace-hash-table))

(def-structure (g2-corba-module-spec
		(:include g2-corba-containing-definition-mixin)
		(:constructor
		   make-g2-corba-module-spec
		   (idl-definition-name-as-symbol
		     idl-definition-name-as-text
		     nearest-enclosing-idl-spec?)))
  )

;;; An IDL interface is represented by a G2 object-definition, getter and
;;; possibly setter method definitions, and method definitions for each IDL
;;; operation.

(def-structure (g2-corba-interface-definition-spec
		 (:include g2-corba-containing-definition-mixin)
		 (:constructor
		   make-g2-corba-interface-definition-spec
		   (idl-definition-name-as-symbol
		     idl-definition-name-as-text
		     idl-interface-direct-superiors
		     nearest-enclosing-idl-spec?)))
  (idl-interface-direct-superiors nil    ;idl-list of symbols
   :reclaimer reclaim-idl-list)
  (idl-interface-attribute-specs? nil    ;idl-alist: 
   :reclaimer                            ; (name-symbol name-text idl-type readonly-p)
   reclaim-idl-tree-with-some-text-string-leaves)
  idl-interface-attribute-specs-tail     ;shared cons
  )

(defun-void reclaim-if-idl-list (maybe-idl-list)
  (when (consp maybe-idl-list)
    (reclaim-idl-list maybe-idl-list)))

(def-structure (g2-corba-array-definition-spec
		 (:include g2-corba-containing-definition-mixin)
		 (:constructor
		   make-g2-corba-array-definition-spec
		   (idl-definition-name-as-symbol
		     idl-definition-name-as-text
		     idl-array-element-type
		     idl-array-dimension-list
		     nearest-enclosing-idl-spec?)))
  (idl-array-element-type nil     ;symbol or idl-list
  :reclaimer reclaim-if-idl-list)
  (idl-array-dimension-list nil   ;idl-tree (may need eval'ing)
   :reclaimer reclaim-idl-tree)
  )

;;; The IDL struct type is relatively straightforward to represent in G2.  It is
;;; simply an object-definition, possibly specifying some nested sub-objects.
;;; The g2-corba-containing-definition-mixin structures corresponding to the
;;; each sub-object may be reached by looking in enclosing namespaces for the
;;; symbol that names the sub-object's type.

(def-structure (g2-corba-struct-definition-spec
		 (:include g2-corba-containing-definition-mixin)
		 (:constructor
		   make-g2-corba-struct-definition-spec
		   (idl-definition-name-as-symbol
		     idl-definition-name-as-text
		     idl-struct-type
		     nearest-enclosing-idl-spec?)))
  idl-struct-type               ;symbol: STRUCT or EXCEPTION
  (idl-struct-member-specs nil  ;idl-alist: (name-symbol name-text idl-type)
   :reclaimer
   reclaim-idl-tree-with-some-text-string-leaves)
  )

;;; Since G2 lacks a memory layout model, the IDL discriminated union presents
;;; an especial problem.  The tentative design is to represent the union type as
;;; a G2 object with three attributes: a discriminator slot, a readonly slot
;;; containing the discriminator value that points to the "largest" field, and a
;;; slot containing that field.  When two or more fields are equally large in
;;; C++, the "simplest" of the two is chosen (e.g., a float over a two-element
;;; long array).  We may have to determine the longest field at run-time, as
;;; with the IDL string or sequence type.  The intent of this design is to
;;; provide G2 with enough information to reconstruct the union when returning
;;; it to CORBA, without encouraging G2 users to probe a memory layout model
;;; that does not exist.  For example, the following IDL fragment
;;;
;;;   union a_numeric_union
;;;         switch(long) {
;;;            case 1:  long    long_view[2];
;;;            case 2 : float   float_view;
;;;            case 3:  char    char_view;
;;;         };
;;;
;;; will produce in G2 an object-definition that specifies three attributes:
;;; DISCRIMIATOR (containing an integer), LARGEST-FIELD-DISCRIMINATOR
;;; (containing the integer 2), and FLOAT_VIEW (containing a float).  In
;;; instances of this class, the LARGEST-FIELD-DISCRIMINATOR attribute will be
;;; rendered readonly somehow, possibly via whenever rules (similar to the
;;; measures taken to warn G2 users who mutate parameters that represent IDL
;;; constants).

(def-structure (g2-corba-union-definition-spec
		 (:include g2-corba-containing-definition-mixin)
		 (:constructor
		   make-g2-corba-union-definition-spec
		   (idl-definition-name-as-symbol
		     idl-definition-name-as-text
		     idl-union-switch-type-spec
		     nearest-enclosing-idl-spec?)))
  (idl-union-switch-type-spec nil    ;symbol or idl-list
   :reclaimer reclaim-if-idl-list)
  (idl-union-member-specs nil        ;idl-tree [case-expression may need eval'ing]:
   :reclaimer                        ; (name-symbol name-text idl-type case-expression)
   reclaim-idl-tree-with-some-text-string-leaves)      
  )

;;; The IDL enum type captures two notions: that of symbolic names, and that of
;;; an ordered set of names.  Each enum type is represented in G2 as an object
;;; (as opposed to an object-definition).  This `G2 enum object' has one
;;; attribute per ordered name (where the value of that attribute is an integer
;;; that preserves the same ordering as that in the original IDL), plus a
;;; INVERSE-ENUMERATION attribute, containing a G2 symbol-array that maps from
;;; integer back to the corresponding ordered name.  At run time, a CORBA enum
;;; reaches G2 as as a symbol, but G2 converts that symbol to its corresponding
;;; integer before it is used as the argument to a CORBA method.  Contrariwise,
;;; a CORBA method in G2 returns an enum value as a symbol, by using the
;;; INVERSE-ENUMERATION array to locate the symbol.that corresponds to an
;;; integer.  Depending on the outcome of the 5.0 Components Project, more
;;; efficient representations may be possible.

(defun-void reclaim-idl-list-of-text-strings (idl-list)
  (loop for text-string in idl-list
	when (text-string-p text-string) ;defensive
	  do (reclaim-text-string text-string)
    finally (reclaim-idl-list idl-list)))

(def-structure (g2-corba-enum-definition-spec
		 (:include g2-corba-definition-mixin)
		 (:constructor
		   make-g2-corba-enum-definition-spec
		   (idl-definition-name-as-symbol
		     idl-definition-name-as-text
		     idl-enum-member-name-symbols
		     idl-enum-member-name-texts
		     nearest-enclosing-idl-spec?)))
  (idl-enum-member-name-symbols nil   ;idl-list of symbols
   :reclaimer reclaim-idl-list)
  (idl-enum-member-name-texts nil     ;idl-list of text-strings
   :reclaimer
   reclaim-idl-list-of-text-strings)
  )

;;; The IDL const declaration is represented in G2 as a parameter.  A whenever
;;; rule warns the user is the value of the parameter is changed, and thus makes
;;; the parameter more or less read-only.

(def-structure (g2-corba-const-definition-spec
		 (:include g2-corba-definition-mixin)
		 (:constructor
		   make-g2-corba-const-definition-spec
		   (idl-definition-name-as-symbol
		     idl-definition-name-as-text
		     idl-const-type-spec
		     idl-const-expression-spec
		     nearest-enclosing-idl-spec?)))
  (idl-const-type-spec nil         ;symbol or idl-list
   :reclaimer reclaim-if-idl-list)
  (idl-const-expression-spec nil   ;idl-tree (may need eval'ing)
   :reclaimer reclaim-idl-tree)
  (idl-evaluated-exprsssion? nil   ;evaluation-value or nil
   :reclaimer reclaim-if-evaluation-value)
  )

;;; A `CORBA method' is an ordinary G2 method that implements an description
;;; from IDL and is thereby able to integraate with CORBA.

(def-structure (g2-corba-method-definition-spec
		 (:include g2-corba-definition-mixin))
  (g2-corba-method-arglist nil      ;idl-alist: (name-symbol name-text idl-type)
   :reclaimer reclaim-idl-tree-with-some-text-string-leaves)
  (g2-corba-method-return-list nil  ;idl-alist: (name-symbol name-text idl-type)
   :reclaimer reclaim-idl-tree-with-some-text-string-leaves)
  g2-corba-method-oneway-p          ;t or nil
  (g2-corba-method-raises nil       ;idl-list of symbols
   :reclaimer reclaim-idl-list)
  (g2-corba-method-context nil      ;idl-list of text-strings
   :reclaimer reclaim-idl-list-of-text-strings)
  )

(def-structure (g2-corba-client-method-definition-spec
		 (:include g2-corba-method-definition-spec)
		 (:constructor
		   make-g2-corba-client-method-definition-struct
		   (idl-definition-name-as-symbol
		     idl-definition-name-as-text
		     g2-corba-method-arglist
		     g2-corba-method-return-list
		     g2-corba-client-remote-procedure-name?
		     g2-corba-method-oneway-p
		     g2-corba-method-raises
		     g2-corba-method-context
		     nearest-enclosing-idl-spec?)))
  g2-corba-client-remote-procedure-name?  ;symbol or nil

  ;; The following slots go somewhere else, possibly in a private G2 class that
  ;; describes how to code the CORBA bridge, returned by the system procedure
  ;; along with the user-visible classes and methods.
  ;;rpc-arglist-for-gsi-corba        ;idl-list of text-strings: (name C++type)
  ;;idl-function-name-for-gsi-corba  ;text-string
  )

(def-structure (g2-corba-legacy-server-method-definition-spec
		 (:include g2-corba-method-definition-spec))
  g2-corba-legacy-server-method-comments ;text-string
  )

(def-structure (g2-corba-stub-server-method-definition-spec
		 (:include g2-corba-method-definition-spec))
  g2-corba-stub-server-method-comments ;text-string
  )

(def-structure (g2-corba-client-remote-declaration-spec
		 (:include g2-corba-definition-mixin)
		 (:constructor
		   make-g2-corba-client-remote-declaration-spec
		   (governing-g2-method-declaration-spec)))
  governing-g2-method-declaration-spec
  )

;;; The intent of the g2-corba-client-whenever-rule-spec is to complain whenever
;;; someone tries to alter an IDL constant, since other IDL semantics (array
;;; dimensions, union switches, and the like) may depend on it.

(def-structure (g2-corba-client-whenever-rule-spec
		 (:include g2-corba-definition-mixin)
		 (:constructor
		   make-g2-corba-client-whenever-rule-spec
		   (governing-g2-const-spec)))
  governing-g2-const-spec
  )

;;; The simple function `g2-idl-object-reference-p' is necessary because
;;; def-structure does not arrange for the predicate from a parent structure
;;; definition to return true on instance of an :included definition.

(defun-simple g2-idl-object-reference-p (thing)
  (or (g2-corba-module-spec-p thing)
      (g2-corba-interface-definition-spec-p thing)
      (g2-corba-array-definition-spec-p thing)
      (g2-corba-struct-definition-spec-p thing)
      (g2-corba-union-definition-spec-p thing)
      (g2-corba-enum-definition-spec-p thing)
      (g2-corba-const-definition-spec-p thing)
      (g2-corba-client-method-definition-spec-p thing)
      (g2-corba-legacy-server-method-definition-spec-p thing)
      (g2-corba-stub-server-method-definition-spec-p thing)))

;;;; Built-in Classes for CORBA Integration

;; These fall into at least two categories: objects representing CORBA errors
;; and object mimicking CORBA compound types.

;; object
;;   => corba-error
;;     => idl-client-error
;;       => no-idl-file (continue by prompting for new name & allowing navigation)
;;     => idl-server-error
;;     => corba-runtime-error (including those pre-defined in CORBA spec)
;;   => corba-warning
;;     => idl-client-warning
;;       => extant non-corba module,  making up new corba module name
;;          (other option for UI: use extant module)
;;       => extant non-corba object-definition, making up new name
;;          (other options for UI: use extant definition)
;;       => unfulfilled inheritance, adding dummy ancestors, renaming when necessary
;;     => idl-server-warning
;;     => corba-struct
;;     => corba-union
;;     => corba-enumeration
;;     => corba-exception

(def-structure (idl-to-g2-error
		 (:constructor
		   make-idl-to-g2-error
		   (idl-to-g2-error-type idl-to-g2-error-spec)))
  idl-to-g2-error-type ;symbol
  idl-to-g2-error-spec ;shared data: g2-corba-definition-mixin, idl-list, etc.
  )

(defun-void signal-idl-to-g2-error (idl-to-g2-error-type idl-to-g2-error-spec)
  (throw 'idl-to-g2-error-catcher
    (make-idl-to-g2-error idl-to-g2-error-type idl-to-g2-error-spec)))

;;;; Transforming IDL Parser Output into Raw CORBA Integration Specs

;; First we get all the information we can from the parse into integration
;; structures.  Then we transform various IDL names as necessary to prevent
;; collisions.

;;;; Checking G2 for Namespace Conflicts

;;;; Evaluating IDL Constants

;;; The simple function `eval-idl-constant' must be called within a
;;; with-temporary-gensym-float-creation scope.

(defparameter integer-only-idl-ops
  '( \| ^ & >> << ))

(defun-void reclaim-idl-list-of-evaluation-values (idl-list)
  (loop for value in idl-list
	do (reclaim-evaluation-value value)
    finally (reclaim-idl-list idl-list)))

#+not-yet
(defun-simple eval-idl-constant-op (op-expression op namespace-holder)
  (let* ((arglist
	   (loop with integer-only-p = (memq op integer-only-idl-ops)
		 for subexpression in (rest op-expression)
		 for subvalue
		     = (eval-idl-constant subexpression namespace-holder)
		 for arg-count from 1
		 when (and integer-only-p
			   (not (evaluation-integer-p subvalue)))
		   do (progn
			(reclaim-idl-list-of-evaluation-values arguments)
			(signal-idl-to-g2-error
			  'idl-op-only-accepts-integers
			  op-expression))
		 collect subvalue into arguments using idl-cons
		 finally (return arguments)))
	 (argcount (length arguments)))
    (case car-of-expression
      (\| ...)
      (^ ...)
      (& ...)
      (>> ...)
      (<< ...)
      (+ ...)
      (- ...)
      (~ ...)
      (* ...)
      (/ ...)
      (% ...)
      (otherwise
       (signal-idl-to-g2-error 'unknown-idl-constant-op op-expression)))))
    
#+not-yet
(defun-simple eval-idl-constant (constant-expression namespace-holder)
  (cond
    ((fixnump constant-expression)
     (make-evaluation-integer constant-expression))
    ((typep constant-expression 'double-float)
     (make-evaluation-float constant-expression))
    ((text-string-p constant-expression) (make-evaluation-text constant-expression))
    ((symbolp constant-expression)
     (case constant-expression
       (true (copy-evaluation-truth-value evaluation-true-value))
       (false (copy-evaluation-truth-value evaluation-false-value))
       (otherwise
	(signal-idl-to-g2-error 'bad-idl-constant-symbol constant-expression))))
    ((idl-scoped-name-p constant-expression)
     (let ((const-spec (chase-idl-constant constant-expression)))
       (unless (g2-corba-const-definition-spec-p const-spec)
	 (signal-idl-to-g2-error 'bad-idl-scoped-constant constant-expression))
       (let ((value-already? (idl-evaluated-exprsssion? const-spec)))
	 (copy-evaluation-value
	   (or value-already?
	       (setf (idl-evaluated-exprsssion? const-spec)
		     (eval-idl-constant
		       (idl-const-expression-spec const-spec)
		       namespace-holder)))))))
    ((not (consp constant-expression))
     (signal-idl-to-g2-error 'unknown-idl-constant-form constant-expression))
    (t (loop for op-expression = constant-expression then first-of-expression
	     for first-of-expression = (first op-expression)
	     while (consp first-of-expression)
	     finally
	       (eval-idl-constant-op
		 op-expression
		 first-of-expression
		 namespace-holder)))))

;;;; Determining the Largest Union Member

;;; Determining the largest union member may not always be possible at run time.
;;; If a union contains a member that is an IDL unbounded sequence type, the
;;; actual size of the sequence depends on its _max_size field.

;;;; Generating or Checking IDL Operation Names

;;;; System Procedures for G2 as CORBA Client

;; get-corba-client-proxy-list-from-idl(idl-filename: text)
;;   => class corba-client-proxy-list or class idl-client-error,
;;      idl-client-warning or nil
;;   {items include module name somehow}

;; delete-corba-client-proxy-list-and-elements(class corba-client-proxy-list)
;;   => true or class idl-client-error

;; possible UI stuff

;; populate-workspace-from-corba-client-proxy-list(class corba-client-proxy-list)
;;   {new workspace?}
;;   {deletes list afterward?}
;;   {can group by item class, alphabetically, etc}
;;   {grouping by ws, sections of same ws, etc}

;;;; Helpers for Accessing IDL Parse Result

;;; Need to doc that IDL names in the G2 mapping are not case sensitive by
;;; default.

(defun-simple intern-upcase (text)
  (intern-text-string
    (copy-text-string-with-case-conversion text :all)))

(defun-simple intern-upcase-idl-leaves (idl-tree)
  (cond
    ((text-string-p idl-tree)
     (intern-upcase idl-tree))
    ((consp idl-tree)
     (idl-cons (intern-upcase-idl-leaves (car idl-tree))
	       (intern-upcase-idl-leaves (cdr idl-tree))))
    (t idl-tree)))

(defun-simple intern-upcase-idl-list (idl-list)
  (loop for list-element in idl-list
	collect
	(if (text-string-p list-element)
	    (intern-upcase list-element)
	    list-element)
	using idl-cons))

;;; The function `copy-idl-leaf-type-spec' must be run in a context wherein a
;;; catcher exists for the symbol idl-to-g2-error-catcher.

(defun-simple copy-idl-leaf-type-spec (param-type-spec)
  (cond
    ;; Declares a string, sequence, or scoped user-defined name.
    ((consp param-type-spec) (intern-upcase-idl-leaves param-type-spec))
    ;; Declares a user-defined name.
    ((text-string-p param-type-spec) (intern-upcase param-type-spec))
    ;; A symbol declaring a built-in IDL type.
    ((symbolp param-type-spec) param-type-spec)
    (t (signal-idl-to-g2-error 'bad-param-type-spec param-type-spec))))

(defun-simple copy-idl-tree-with-some-text-string-leaves (idl-tree)
  (cond
    ((text-string-p idl-tree) (copy-text-string idl-tree))
    ((consp idl-tree)
     (idl-cons (copy-idl-tree-with-some-text-string-leaves (car idl-tree))
	       (copy-idl-tree-with-some-text-string-leaves (cdr idl-tree))))
    (t idl-tree)))

(defun-simple copy-idl-list-of-text-strings (idl-list)
  (loop for list-element in idl-list
	collect
	(if (text-string-p list-element)
	    (copy-text-string list-element)
	    list-element)
	using idl-cons))

;;;; Accessors on IDL Parse Result

;;; In general, when the accessor has -FROM-PARSE post-pended, it copies or
;;; interns some component of the original IDL parse.  For example, such a
;;; function might return an interned symbol instead of the original
;;; text-string, or generate a tree of fresh idl-conses, or both.

;;; In general, when an accessor has G2-CORBA- prepended, it generates something
;;; not present in the original parse, such as a symbol naming a getter method
;;; for an interface attribute.

(defun-simple idl-enclosed-definitions (idl-module)
  (nthcdr 2 idl-module))

(defun-simple idl-interface-specs (idl-interface)
  (nthcdr 2 idl-interface))

(defun-simple idl-array-dimensions (array-declarator)
  (nthcdr 2 array-declarator))

(defun-simple idl-typedef-declarators (idl-typedef)
  (nthcdr 2 idl-typedef))

(defun-simple idl-struct-members (idl-struct)
  (nthcdr 2 idl-struct))

(defun-simple idl-union-members (idl-union)
  (nthcdr 3 idl-union))

(defun-simple idl-enum-members (idl-enum)
  (nthcdr 2 idl-enum))

(defun-simple idl-module-name (idl-module)
  (second idl-module))

(defun-simple idl-interface-name (idl-interface)
  (second idl-interface))

(defun-simple idl-array-declarator-name (array-declarator)
  (second array-declarator))

(defun-simple idl-compound-type-name-from-parse (compound-type-declarator)
  (intern-upcase (second compound-type-declarator)))

(defun-simple idl-struct-name (idl-struct)
  (second idl-struct))

(defun-simple idl-union-name (idl-union)
  (second idl-union))

(defun-simple idl-enum-name (idl-enum)
  (second idl-enum))

(defun-simple idl-const-name (idl-const)
  (second idl-const))

(defun-simple idl-typedef-spec (idl-typedef)
  (second idl-typedef))

(defun-simple idl-operation-return-type (operation-spec)
  (second operation-spec))

(defun-simple idl-attribute-type (idl-attribute)
  (second idl-attribute))

(defun-simple idl-sequence-element-type (idl-sequence)
  (second idl-sequence))

(defun-simple idl-union-switch-type (idl-union)
  (second (third idl-union)))

(defun-simple idl-interface-inheritance-from-parse (idl-interface)
  (let ((possible-inheritance (third idl-interface)))
    (and (consp possible-inheritance)
	 (eq (car possible-inheritance) 'inheritance)
	 (intern-upcase-idl-leaves (rest possible-inheritance)))))

;; Need to worry about 32-character limit of VMS linker!  Do this when we check
;; for name collisions?

(defun-simple g2-corba-getter-method-symbol (attribute-name)
  (intern-text-string (tformat "GET-CORBA-~s" attribute-name)))

(defun-simple g2-corba-getter-remote-procedure-name (attribute-name)
  (intern-text-string (tformat "GET-CORBA-~s-REMOTELY" attribute-name)))

(defun-simple g2-corba-setter-method-symbol (attribute-name)
  (intern-text-string (tformat "SET-CORBA-~s" attribute-name)))

(defun-simple g2-corba-setter-remote-procedure-name (attribute-name)
  (intern-text-string (tformat "SET-CORBA-~s-REMOTELY" attribute-name)))

(defun-simple g2-corba-remote-procedure-name (operation-name)
  (intern-text-string (tformat-text-string "REMOTE-CORBA-~s" operation-name)))

(defun-simple idl-operation-name (operation-spec)
  (third operation-spec))

(defun-simple idl-operation-parameters (operation-spec)
  (fourth operation-spec))

(defun-simple idl-operation-raises-list-from-parse (operation-spec)
  (loop for exception in (sixth operation-spec)
	collect (intern-upcase exception) using idl-cons))

(defun-simple idl-operation-context-from-parse (operation-spec)
  (loop for context-item in (seventh operation-spec)
	collect (copy-text-string context-item) using idl-cons))

(defun-simple idl-attribute-name-list (idl-attribute)
  (third idl-attribute))

(defun-simple idl-definition-type-if-any (idl-definition)
  (and (consp idl-definition) (car idl-definition)))

(defun-simple idl-const-type (idl-const)
  (third idl-const))

(defun-simple idl-const-expression (idl-const)
  (fourth idl-const))

;;;; Predicates on IDL Parse Result

(defun-simple idl-array-declarator-p (declarator)
  (and (consp declarator) (eq (first declarator) 'array)))

(defun-simple idl-string-declarator-p (declarator)
  (and (consp declarator) (eq (first declarator) 'string)))

(defun-simple idl-sequence-declarator-p (declarator)
  (and (consp declarator) (eq (first declarator) 'sequence)))

(defun-simple idl-scoped-name-p (idl-entity)
  (or (text-string-p idl-entity)
      (and (consp idl-entity)
	   (memq (first idl-entity) '(scoped-name global-scoped-name)))))

(defun-simple idl-scoped-name-components (idl-entity)
  (rest idl-entity))

(defun-simple idl-identifier-p (idl-entity?)
  (and idl-entity? (symbolp idl-entity?)))

;;; The "leaf" in `idl-leaf-type-p' means we needn't go any further in gathering
;;; g2-corba-definition-mixin structs from the IDL parse.  The term "leaf"
;;; should not be confused with the term "built-in" in idl-built-in-type-p.  An
;;; `IDL leaf type' can denote a complex user-defined type.  Such a user-defined
;;; type is a "leaf" despite its substructure, because its own
;;; g2-corba-definition-mixin resides in an idl-namespace somewhere, so all we
;;; need is a symbol or list of symbols to look it up.  In constrast, an `IDL
;;; built-in type' only maps onto a pre-exsiting IDL type (i.e., boolean, char,
;;; short, int, float, double, or string), or an IDL type that can be
;;; represented by a built-in G2 object (i.e., sequence as item-array).

(defun-simple idl-leaf-type-p (idl-type)
  (or (symbolp idl-type)
      (idl-scoped-name-p idl-type)
      (idl-string-declarator-p idl-type)
      (idl-sequence-declarator-p idl-type)))

(defun-simple idl-oneway-operation-p (operation-spec)
  (eq (fifth operation-spec) 'oneway))

(defun-simple idl-readonly-attribute-p (idl-attribute)
  (eq (fourth idl-attribute) 'readonly))

;;;; IDL Namespaces

(defun-void add-to-idl-namespace-if-possible
    (name referent enclosing-object-definition?)
  (let* ((idl-namespace
	   (if enclosing-object-definition?
	       (idl-namespace enclosing-object-definition?)
	       idl-top-level-namespace))
	 (extant-name-p (look-up-in-idl-namespace name idl-namespace)))
    (when extant-name-p
      ;; Actually, this should not throw.  Rather, it should do the best it can,
      ;; then record for later frame notes or somesuch.  Note that this sort of
      ;; error is distinct from a conflict with G2 namespaces, as doing "the
      ;; best you can" with an IDL namespace conflict entails the additional
      ;; hair of revising some IDL namespaces, whereas no such change is
      ;; necessary in a G2 namespace conflict (all the revision happens within
      ;; the g2-corba-definition structure pointed to by the namespace).  In
      ;; both cases, however, we try to proceed as far as possible without
      ;; involving the end user.
      (signal-idl-to-g2-error 'namespace-collision referent))
    (setf (look-up-in-idl-namespace name idl-namespace) referent)))

;;;; Method Specs from IDL Parse

(defun-simple make-g2-corba-client-method-definition-spec
    (operation-spec object-definition-spec)
  (let* ((operation-name (idl-operation-name operation-spec))
	 (operation-symbol (intern-upcase operation-name))
	 (in-parameters nil)
	 (return-type
	   (idl-list
	     'corba-return-value
	     (copy-idl-leaf-type-spec
	       (idl-operation-return-type operation-spec))))
	 (out-parameters (idl-list return-type)))
    (loop for (parameter-mode parameter-type parameter-name)
	      in (idl-operation-parameters operation-spec)
	  do
      (let* ((copy-of-type (copy-idl-leaf-type-spec parameter-type))
	     (new-spec (idl-list (intern-upcase parameter-name)
				 (copy-text-string parameter-name)
				 copy-of-type)))
	(case parameter-mode
	  (in (idl-push new-spec in-parameters))
	  (out (idl-push new-spec out-parameters))
	  (inout (idl-push new-spec in-parameters)
		 (idl-push
		   (copy-idl-tree-with-some-text-string-leaves new-spec)
		   out-parameters))))
	  finally
	    (nreversef in-parameters)
	    (nreversef out-parameters))
    (make-g2-corba-client-method-definition-struct
      operation-symbol
      (copy-text-string operation-name)
      in-parameters
      out-parameters
      (g2-corba-remote-procedure-name operation-symbol)
      (idl-oneway-operation-p operation-spec) ;warn if return-type is not void!
      (idl-operation-raises-list-from-parse operation-spec)
      (idl-operation-context-from-parse operation-spec)      
      object-definition-spec)))
  
(defun make-g2-corba-client-getter-method-definition
    (attribute-name object-definition-spec?)
  (let* ((method-symbol (g2-corba-getter-method-symbol attribute-name))
	 (method-definition-spec
	   (make-g2-corba-client-method-definition-struct
	     method-symbol
	     (copy-symbol-name method-symbol nil)
	     nil
	     nil
	     (g2-corba-getter-remote-procedure-name attribute-name)
	     nil
	     nil
	     nil
	     object-definition-spec?)))
    (add-to-idl-namespace-if-possible
      method-symbol
      method-definition-spec
      object-definition-spec?)
    method-definition-spec))

(defun make-g2-corba-client-setter-method-definition
    (attribute-name idl-type object-definition-spec?)
  (let* ((method-symbol
	   (g2-corba-setter-method-symbol attribute-name))
	 (method-definition-spec
	   (make-g2-corba-client-method-definition-struct
	     method-symbol
	     (copy-symbol-name method-symbol nil)
	     (idl-list 'new-value (intern-upcase idl-type))
	     nil
	     (g2-corba-setter-remote-procedure-name attribute-name)
	     nil
	     nil
	     nil
	     object-definition-spec?)))
    (add-to-idl-namespace-if-possible
      method-symbol
      method-definition-spec
      object-definition-spec?)
    method-definition-spec))

;;;; Module Specs from IDL Parse

;;; The function `get-corba-client-module-specs' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition.  This list contains one or
;;; more instances of any of the subtypes of the g2-corba-definition-mixin
;;; structure.  In addition, this function may modify either
;;; idl-top-level-namespace or the idl-namespace of its enclosing-idl-entity?
;;; argument.

(defun-simple get-corba-client-module-specs (idl-module enclosing-idl-entity?)
  (let* ((module-name (idl-module-name idl-module))
	 (module-symbol (intern-upcase module-name))
	 (idl-module-spec
	   (make-g2-corba-module-spec
	     module-symbol
	     (copy-text-string module-name)
	     enclosing-idl-entity?)))
    (add-to-idl-namespace-if-possible
      module-symbol
      idl-module-spec
      enclosing-idl-entity?)
    (idl-cons
      idl-module-spec
      (loop for sub-definition in (idl-enclosed-definitions idl-module)
	    nconc
	    (get-corba-client-item-specs-from-idl-definition
	      sub-definition
	      idl-module-spec)))))

;;;; Interface Specs from IDL Parse

;;; The function `get-corba-client-interface-specs' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition.  This list contains one or
;;; more instances of any of the subtypes of the g2-corba-definition-mixin
;;; structure.  In addition, this function may modify either
;;; idl-top-level-namespace or the idl-namespace of its enclosing-idl-entity?
;;; argument.

(defun get-corba-client-interface-specs (idl-interface enclosing-idl-entity?)
  (let* ((interface-name (idl-interface-name idl-interface))
	 (interface-symbol (intern-upcase interface-name))
	 (object-definition-spec
	   (make-g2-corba-interface-definition-spec
	     interface-symbol
	     (copy-text-string interface-name)
	     (idl-interface-inheritance-from-parse idl-interface)
	     enclosing-idl-entity?)))
    (add-to-idl-namespace-if-possible
      interface-symbol
      object-definition-spec
      enclosing-idl-entity?)
    (idl-cons
      object-definition-spec
      (loop for sub-definition in (idl-interface-specs idl-interface)
	    nconc
	    (get-corba-client-item-specs-from-idl-definition
	      sub-definition
	      object-definition-spec)))))

;;;; Attribute Specs from IDL Parse

;;; The function `get-corba-client-attribute-specs' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition.  This list contains one or
;;; more instances of the g2-corba-client-method-definition-spec structure.
;;; These instances represent the getter and possible setter operations on the
;;; attributes of the enclosing IDL interface.  In addition, this function may
;;; modify either idl-top-level-namespace or the idl-namespace of its
;;; enclosing-idl-object? argument, as well as the
;;; idl-interface-attribute-specs? field of a non-nil
;;; enclosing-object-definition? argument.

(defun-simple get-corba-client-attribute-specs
    (idl-attribute enclosing-object-definition?)
  (let ((attribute-specs
	  (loop for attribute-name in (idl-attribute-name-list idl-attribute)
		with attribute-type
		  = (copy-idl-leaf-type-spec
		      (idl-attribute-type idl-attribute))
		with readonly-p = (idl-readonly-attribute-p idl-attribute)
		collect (idl-list (intern-upcase attribute-name)
				  (copy-text-string attribute-name)
				  attribute-type
				  readonly-p)
		  using idl-cons)))
    (when enclosing-object-definition?
      (if (idl-interface-attribute-specs? enclosing-object-definition?)
	  (setf (cdr (idl-interface-attribute-specs-tail
		       enclosing-object-definition?))
		attribute-specs)
	  (setf (idl-interface-attribute-specs? enclosing-object-definition?)
		attribute-specs))
      (setf (idl-interface-attribute-specs-tail enclosing-object-definition?)
	    (last attribute-specs)))
    (loop for (attribute-name idl-type readonly-p) in attribute-specs
	  collect
	  (make-g2-corba-client-getter-method-definition
	    attribute-name
	    enclosing-object-definition?)
	    using idl-cons
	  unless readonly-p
	    collect
	    (make-g2-corba-client-setter-method-definition
	      attribute-name
	      idl-type
	      enclosing-object-definition?)
	      using idl-cons)))

;;;; Operation Specs from IDL Parse

;;; The function `get-corba-client-operation-specs' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition..  This list contains one or
;;; more instances of the g2-corba-client-method-definition-spec structure.

(defun-simple get-corba-client-operation-specs
    (idl-operation enclosing-object-definition?)
  (let ((method-definition-spec
	   (make-g2-corba-client-method-definition-spec
	     idl-operation
	     enclosing-object-definition?)))
    (add-to-idl-namespace-if-possible
      (idl-definition-name-as-symbol method-definition-spec)
      method-definition-spec
      enclosing-object-definition?)
    (idl-list
      method-definition-spec
      (make-g2-corba-client-remote-declaration-spec method-definition-spec))))

;;;; Typedef Specs from IDL Parse

;;; The function `get-corba-client-typedef-specs' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition.  This list contains zero or
;;; more instances of g2-corba-array-definition-spec,
;;; g2-corba-struct-definition-spec, g2-corba-union-definition-spec, or
;;; g2-corba-enum-definition-spec structures.  In addition, this function may
;;; modify either idl-top-level-namespace or the idl-namespace of its
;;; enclosing-idl-entity? argument.

(defun-simple get-corba-client-typedef-specs
    (idl-typedef enclosing-idl-entity?)
  (let* ((typedef-spec (idl-typedef-spec idl-typedef))
	 (simple-spec-p (idl-leaf-type-p typedef-spec))
	 (typedef-declarators (idl-typedef-declarators idl-typedef)))
    (loop for typedef-declarator in typedef-declarators
	  nconc
	  (let ((typespec-referent
		  (if simple-spec-p
		      (copy-idl-leaf-type-spec typedef-spec)
		      (idl-compound-type-name-from-parse typedef-spec))))
	    (if (idl-array-declarator-p typedef-declarator)
		(let* ((array-declarator-name
			 (idl-array-declarator-name typedef-declarator))
		       (array-declarator-symbol
			 (intern-upcase array-declarator-name))
		       (array-declarator-definition-spec
			 (make-g2-corba-array-definition-spec
			   array-declarator-symbol
			   (copy-text-string array-declarator-name)
			   typespec-referent
			   (intern-upcase-idl-leaves
			     (idl-array-dimensions typedef-declarator))
			   enclosing-idl-entity?)))
		  (add-to-idl-namespace-if-possible
		    array-declarator-symbol
		    array-declarator-definition-spec
		    enclosing-idl-entity?)
		  (idl-cons
		    array-declarator-definition-spec
		    (if simple-spec-p
			nil
			(get-corba-client-item-specs-from-idl-definition
			  typedef-spec
			  enclosing-idl-entity?))))
		(let ((scalar-declarator-name
			(intern-upcase typedef-declarator)))
		  (add-to-idl-namespace-if-possible
		    scalar-declarator-name
		    typespec-referent
		    enclosing-idl-entity?)
		  (if simple-spec-p
		      nil
		      (get-corba-client-item-specs-from-idl-definition
			typedef-spec
			enclosing-idl-entity?))))))))

;;;; Struct Specs from IDL Parse

(defun-simple collect-idl-struct-member-specs
    (member-specs struct-spec enclosing-idl-entity?)
  (loop for (member-type . member-declarators) in member-specs
	nconc
    (let ((simple-spec-p (idl-leaf-type-p member-type)))
      (loop for member-declarator in member-declarators
	    nconc
	(let ((member-type-to-store
		(if simple-spec-p
		    (copy-idl-leaf-type-spec member-type)
		    (idl-compound-type-name-from-parse member-type))))
	  (if (idl-array-declarator-p member-declarator)
	      (let* ((array-declarator-name
		       (idl-array-declarator-name member-declarator))
		     (array-declarator-symbol
		       (intern-upcase array-declarator-name))
		     (array-declarator-definition-spec
		       (make-g2-corba-array-definition-spec
			 array-declarator-symbol
			 (copy-text-string array-declarator-name)
			 member-type-to-store
			 (intern-upcase-idl-leaves
			   (idl-array-dimensions member-declarator))
			 enclosing-idl-entity?)))
		(add-to-idl-namespace-if-possible
		  array-declarator-symbol
		  array-declarator-definition-spec
		  struct-spec)
		(idl-push
		  (idl-list array-declarator-symbol
			    (copy-text-string array-declarator-name)
			    array-declarator-symbol)
		  (idl-struct-member-specs struct-spec))
		(idl-cons
		  array-declarator-definition-spec
		  (if simple-spec-p
		      nil
		      (get-corba-client-item-specs-from-idl-definition
			member-type
			struct-spec))))
	      (let ((scalar-declarator-symbol
		      (intern-upcase member-declarator)))
		(idl-push
		  (idl-list scalar-declarator-symbol
			    (copy-text-string member-declarator)
			    member-type-to-store)
		  (idl-struct-member-specs struct-spec))
		(add-to-idl-namespace-if-possible
		  scalar-declarator-symbol
		  member-type-to-store
		  struct-spec)
		(if simple-spec-p
		    nil
		    (get-corba-client-item-specs-from-idl-definition
		      member-type
		      struct-spec)))))))
	finally (nreversef (idl-struct-member-specs struct-spec))))

;;; The function `get-corba-client-struct-specs' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition.  This list contains one or
;;; more instances of g2-corba-array-definition-spec,
;;; g2-corba-struct-definition-spec, g2-corba-union-definition-spec, or
;;; g2-corba-enum-definition-spec structures.  In addition, this function may
;;; modify either idl-top-level-namespace or the idl-namespace of its
;;; enclosing-idl-entity? argument.

(defun-simple get-corba-client-struct-specs
    (idl-struct enclosing-idl-entity? struct-type)
  (let* ((struct-name (idl-struct-name idl-struct))
	 (struct-symbol (intern-upcase struct-name))
	 (struct-spec
	   (make-g2-corba-struct-definition-spec
	     struct-symbol
	     (copy-text-string struct-name)
	     struct-type
	     enclosing-idl-entity?)))
    (add-to-idl-namespace-if-possible
      struct-symbol
      struct-spec
      enclosing-idl-entity?)
    (idl-cons
      struct-spec
      (collect-idl-struct-member-specs
	(idl-struct-members idl-struct)
	struct-spec
	enclosing-idl-entity?))))

;;;; Union Specs from IDL Parse

(defun-simple collect-idl-union-member-specs
    (member-specs union-spec enclosing-idl-entity?)
  (loop for ((nil case-expression) member-type . member-declarators)
	    in member-specs
	nconc
    (let ((simple-spec-p (idl-leaf-type-p member-type)))
      (loop for member-declarator in member-declarators
	    nconc
	(let ((member-type-to-store
		(if simple-spec-p
		    (copy-idl-leaf-type-spec member-type)
		    (idl-compound-type-name-from-parse member-type)))
	      (case-expression-to-store
		(intern-upcase-idl-leaves case-expression)))
	  (if (idl-array-declarator-p member-declarator)
	      (let* ((array-declarator-name
		       (idl-array-declarator-name member-declarator))
		     (array-declarator-symbol
		       (intern-upcase array-declarator-name))
		     (array-declarator-definition-spec
		       (make-g2-corba-array-definition-spec
			 array-declarator-symbol
			 (copy-text-string array-declarator-name)
			 member-type-to-store
			 (intern-upcase-idl-leaves
			   (idl-array-dimensions member-declarator))
			 enclosing-idl-entity?)))
		(add-to-idl-namespace-if-possible
		  array-declarator-symbol
		  array-declarator-definition-spec
		  union-spec)
		(idl-push
		  (idl-list
		    array-declarator-symbol
		    (copy-text-string array-declarator-name)
		    array-declarator-symbol
		    case-expression-to-store)
		  (idl-union-member-specs union-spec))
		(idl-cons
		  array-declarator-definition-spec
		  (if simple-spec-p
		      nil
		      (get-corba-client-item-specs-from-idl-definition
			member-type
			union-spec))))
	      (let ((scalar-declarator-symbol
		      (intern-upcase member-declarator)))
		(idl-push
		  (idl-list
		    scalar-declarator-symbol
		    (copy-text-string member-declarator)
		    member-type-to-store
		    case-expression-to-store)
		  (idl-union-member-specs union-spec))
		(add-to-idl-namespace-if-possible
		  scalar-declarator-symbol
		  member-type-to-store
		  union-spec)
		(if simple-spec-p
		    nil
		    (get-corba-client-item-specs-from-idl-definition
		      member-type
		      union-spec)))))))
	finally (nreversef (idl-union-member-specs union-spec))))

;;; The function `get-corba-client-union-specs' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition.  This list contains one or
;;; more instances of g2-corba-array-definition-spec,
;;; g2-corba-struct-definition-spec, g2-corba-union-definition-spec, or
;;; g2-corba-enum-definition-spec structures.  In addition, this function may
;;; modify either idl-top-level-namespace or the idl-namespace of its
;;; enclosing-idl-entity? argument.

(defun-simple get-corba-client-union-specs (idl-union enclosing-idl-entity?)
  (let* ((union-name (idl-union-name idl-union))
	 (union-symbol (intern-upcase union-name))
	 (switch-type (idl-union-switch-type idl-union))
	 (simple-switch-type-p (idl-leaf-type-p switch-type))
	 (switch-definitions
	   (if simple-switch-type-p
	       nil
	       (get-corba-client-item-specs-from-idl-definition
		 switch-type
		 enclosing-idl-entity?)))
	 (union-spec
	   (make-g2-corba-union-definition-spec
	     union-symbol
	     (copy-text-string union-name)
	     (idl-list
	       union-name
	       (if simple-switch-type-p
		   (copy-idl-leaf-type-spec switch-type)
		   (idl-compound-type-name-from-parse switch-type)))
	     enclosing-idl-entity?)))
    (add-to-idl-namespace-if-possible
      union-symbol
      union-spec
      enclosing-idl-entity?)
    (nconc
      (idl-list union-spec)
      switch-definitions
      (collect-idl-union-member-specs
	(idl-union-members idl-union)
	union-spec
	enclosing-idl-entity?))))

;;;; Enum Spec from IDL Parse

;;; The function `get-corba-client-enum-spec' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition.  This list contains exactly
;;; one instance of the g2-corba-enum-definition-spec structure.  In addition,
;;; this function may modify either idl-top-level-namespace or the idl-namespace
;;; of its enclosing-idl-entity? argument.

(defun-simple get-corba-client-enum-spec (idl-enum enclosing-idl-entity?)
  (let* ((enum-name (idl-enum-name idl-enum))
	 (enum-symbol (intern-upcase enum-name))
	 (enum-members (idl-enum-members idl-enum))
	 (enum-spec
	   (make-g2-corba-enum-definition-spec
	     enum-symbol
	     (copy-text-string enum-name)
	     (intern-upcase-idl-list enum-members)
	     (copy-idl-list-of-text-strings enum-members)
	     enclosing-idl-entity?)))
    (add-to-idl-namespace-if-possible
      enum-symbol
      enum-spec
      enclosing-idl-entity?)
    (idl-list enum-spec)))

;;;; Constant Specs from IDL Parse

;;; The function `get-corba-client-const-specs' splices an idl-list into the
;;; result of the governing call to
;;; get-corba-client-item-specs-from-idl-definition.  This list contains exactly
;;; one instance of the g2-corba-const-definition-spec structure.  In addition,
;;; this function may modify either idl-top-level-namespace or the idl-namespace
;;; of its enclosing-idl-entity? argument.

(defun-simple get-corba-client-const-specs (idl-const enclosing-idl-entity?)
  (let* ((const-name (idl-const-name idl-const))
	 (const-symbol (intern-upcase const-name))
	 (const-spec
	   (make-g2-corba-const-definition-spec
	     const-symbol
	     (copy-text-string const-name)
	     (copy-idl-leaf-type-spec (idl-const-type idl-const))
	     (intern-upcase-idl-leaves (idl-const-expression idl-const))
	     enclosing-idl-entity?)))
    (add-to-idl-namespace-if-possible
      const-symbol
      const-spec
      enclosing-idl-entity?)
    (idl-list
      const-spec
      (make-g2-corba-client-whenever-rule-spec const-spec))))

;;;; Top-level Collector of Specs from IDL Parse

;;; The function `get-corba-client-item-specs-from-idl-definition' is the
;;; top-level function for deriving a list of g2-corba-definition-mixin
;;; structures to implement a setup for G2 as CORBA client.  This function must
;;; be called in a context wherein a catcher exists for the symbol
;;; idl-to-g2-error-catcher.

(defun-simple get-corba-client-item-specs-from-idl-definition
    (idl-definition enclosing-idl-entity?)
  (let ((definition-type (idl-definition-type-if-any idl-definition)))
    (case definition-type
      (module
       (get-corba-client-module-specs idl-definition enclosing-idl-entity?))
      (interface
       (get-corba-client-interface-specs idl-definition enclosing-idl-entity?))
      (attribute
       (get-corba-client-attribute-specs idl-definition enclosing-idl-entity?))
      (operation
       (get-corba-client-operation-specs idl-definition enclosing-idl-entity?))
      (typedef
       (get-corba-client-typedef-specs idl-definition enclosing-idl-entity?))
      (union
       (get-corba-client-union-specs idl-definition enclosing-idl-entity?))
      ((struct exception)
       (get-corba-client-struct-specs
	 idl-definition
	 enclosing-idl-entity?
	 definition-type))
      (enum
       (get-corba-client-enum-spec idl-definition enclosing-idl-entity?))
      (const
       (get-corba-client-const-specs idl-definition enclosing-idl-entity?))
      (t (signal-idl-to-g2-error 'unknown-definition-type definition-type)))))

;; How to allow for forward class references, i.e., parent interface declared,
;; child defined, parent defined?  Maybe do what G2 does, i.e.,
;; object-definition accepts it but is "not OK" until all ancestors are defined?

;; See "else" clause of locate-or-create-junction-block-definition in
;; DEFINITIONS for precedent in how to generate class definitions
;; programatically (this particular precedent may go away soon, but users are
;; surely allowed to create transient object-definitions from somewhere).

;; After adjustment for name collision, need to modify entries in
;; compound-idl-type-hashtable (and all that implies, even unto scoped names
;; mentioned in constant expressions).

;;;; GSI Side of G2 as Client

;; Worry about Vax/VMS 32-char linker limit for emit-inward- and
;; -outward-corba-marshalling-function!

;; Need to worry about copy semantics and memory management of "inout"
;; parameters, as they occur both in the arglist and the return-values list.

;;;; Marshalling "In" Parameters

(defmacro with-emit-bindings ((stream-var) &body body)
  `(macrolet ((emit (depth format-string &rest args?)
		`(progn
		   (loop repeat ,depth
			 do (g2-stream-write-char #\Space ,',stream-var))
		   ,(if args?
			`(let ((formatted-text
				 (tformat-text-string ,format-string ,@args?)))
			   (g2-stream-write-line formatted-text ,',stream-var)
			   (reclaim-text-string formatted-text))
			`(g2-stream-write-line ,format-string ,',stream-var)))))
     ,@body))

(eval-when (compile load eval)
(defparameter built-in-idl-type-symbols
  '(boolean char octet short unsigned-short
    long unsigned-long float double any))
)

(defun-simple built-in-idl-type-p (idl-type)
  (cond
    ((null idl-type) nil)
    ((symbolp idl-type) (memq idl-type built-in-idl-type-symbols))
    (t (or (idl-string-declarator-p idl-type)
	   (idl-sequence-declarator-p idl-type)))))

;;; The simple function `chase-idl-type' returns either a symbol naming a
;;; built-in IDL type (i.e., one that is a member of the parameter
;;; built-in-idl-type-symbols), a shared list naming an idl "template" type
;;; (that is, either a string or a sequence), or a g2-corba-definition-mixin
;;; structure describing a user-defined object.  This function must be run in a
;;; context wherein a catcher exists for the symbol idl-to-g2-error-catcher.

;;; Tentatively, a CORBA object reference on the GSI side is a g2pointer to the
;;; C++ object created by Orbix (this object is an instance of the C++ class
;;; that implements the IDL interface).  The corresponding CORBA object in G2
;;; has a corba-object-handle attribute.  When G2 binds (i.e., creates) a CORBA
;;; object, the GSI returns the g2pointer to G2 for storage inside that
;;; attribute (either as a return value from the bind() RPC, or, if necessary,
;;; in a more devious manner).  Thus a CORBA method in G2 actually sends an
;;; integer g2pointer, which the GSI side looks up.  There is no need to use the
;;; "as handle" object-passing facility.

(defun-simple chase-idl-type (idl-type governing-idl-definition?)
  (cond
    ((or (built-in-idl-type-p idl-type) (g2-idl-object-reference-p idl-type))
     idl-type)
    ((idl-identifier-p idl-type)
     (loop with scope? = governing-idl-definition?
           with namespace = (if governing-idl-definition?
				(idl-namespace governing-idl-definition?)
				idl-top-level-namespace)
	   for referent? = idl-type
	       then (or (look-up-in-idl-namespace referent? namespace)
			(cond
			  ((eq namespace idl-top-level-namespace) nil)
			  (t (setq scope? (nearest-enclosing-idl-spec? scope?))
			     (setq namespace
				   (if scope?
				       (idl-namespace scope?)
				       idl-top-level-namespace))
			     referent?)))
	   while referent?
	   when (or (built-in-idl-type-p referent?)
		    (g2-idl-object-reference-p referent?))
	     do (return referent?)
	   finally (signal-idl-to-g2-error
		     'idl-type-chase-failed-from-identifier
		     idl-type)))
    ((idl-scoped-name-p idl-type)
     (loop with components = (idl-scoped-name-components idl-type)
	   for component in components
	   for component-cons on components
	   for last-component-p = (null (cdr component-cons))
	   for namespace = idl-top-level-namespace
			 then (idl-namespace referent?)
	   for referent? = (look-up-in-idl-namespace component namespace)
	   for enclosing-referent = nil then referent?
	   unless (or last-component-p (g2-idl-object-reference-p referent?))
	     do (signal-idl-to-g2-error
		  'idl-type-chase-failed-from-scoped-name
		  idl-type)
	       finally (return (chase-idl-type referent? enclosing-referent))))
    (t (signal-idl-to-g2-error 'unexpected-idl-type-to-chase idl-type))))

(defun-simple chase-idl-constant (idl-type governing-idl-definition?)
  (chase-idl-type idl-type governing-idl-definition?))

;;; The function `idl-sequence-element-type-as-text' returns a new text-string,
;;; which it is the caller's responsibility to reclaim.  The element-type
;;; argument to this function is not a typedef or scoped name.  Another way of
;;; putting this is that element-type is the result of a call to chase-idl-type.
;;; This function must be run in a context wherein a catcher exists for the
;;; symbol idl-to-g2-error-catcher.

(defun-simple idl-sequence-element-type-as-text
    (element-type governing-idl-definition)
  (case element-type
    (boolean        (copy-text-string "unsigned char"))
    (char           (copy-text-string "char"))
    (octet          (copy-text-string "unsigned char"))
    (short          (copy-text-string "short"))
    (unsigned-short (copy-text-string "unsigned short"))
    (long           (copy-text-string "long"))
    (unsigned-long  (copy-text-string "unsigned long"))
    (float          (copy-text-string "float"))
    (double         (copy-text-string "double"))
    (any            (copy-text-string "struct any"))
    (otherwise
     (cond
       ((idl-string-declarator-p element-type) (copy-text-string "char *"))
       ((idl-sequence-declarator-p element-type)
	(twith-output-to-text-string
	  (twrite-string "_IDL_SEQUENCE_")
	  (loop for sub-element-type = element-type
		    then (chase-idl-type
			   (idl-sequence-element-type sub-element-type)
			   governing-idl-definition)
		while (idl-sequence-declarator-p sub-element-type)
		do (twrite-string "sequence_")
	    finally
		  (let ((leaf-type
			  (idl-sequence-element-type-as-text
			    sub-element-type
			    governing-idl-definition)))
		    (twrite-string leaf-type)
		    (reclaim-text-string leaf-type)))))
       ((g2-idl-object-reference-p element-type)
	(twith-output-to-text-string
	  (let ((scoped-name
		  (get-scoped-idl-definition-name
		    (idl-definition-name-as-text element-type))))
	    (twrite-string scoped-name)
	    (twrite-string " *")
	    (reclaim-text-string scoped-name))))
       (t (signal-idl-to-g2-error
	    'bad-idl-sequence-element-type
	    element-type))))))

(defun-void emit-inward-idl-sequence-marshalling
    (idl-sequence-type c++var gsi-item nearest-namespace g2-output-stream i)
  (with-emit-bindings (g2-output-stream)
    (let* ((element-type (idl-sequence-element-type idl-sequence-type))
	   (element-text
	     (idl-sequence-element-type-as-text
	       element-type
	       nearest-namespace))
	   (c++subvar
	     (tformat-text-string "~A[i]" c++var)))
      (emit i "{ long i;"                                               )
      (emit i "  gsi_item *gsi_subitems = gsi_elements_of(~A);" gsi-item)
      (emit i "  ~A._length = gsi_element_count_of(~A);" c++var gsi-item)
      (emit i "  for (i = 0; i < ~A._length; i++)"                c++var)
      (emit i "   {"                                                    )
      (emit i "    gsi_item *gsi_subitem = gsi_subitems[i];"            )
      (emit i "    ~A idl_subitem = ~A[i];"       element-text c++subvar)
      (emit-inward-idl-built-in-marshalling
	element-type
	c++subvar
	"gsi_subitem"
	nearest-namespace
	g2-output-stream
	(1+f i))
      (emit i "   }" )
      (emit i "}"    )
      (reclaim-text-string element-text)
      (reclaim-text-string c++subvar))))

(defun-void emit-inward-idl-compound-marshalling
    (idl-built-in-type c++var gsi-item nearest-namespace g2-output-stream i)
  (with-emit-bindings (g2-output-stream)
    (cond
      ((eq idl-built-in-type 'any)
       (emit i "~A._type = idl_any_item_type_tag(~A);" c++var gsi-item)
       ;; Note the following emitted statement is atypical in that it makes the
       ;; C++ variable (an Orbix "any" struct) point to a value inside the
       ;; gsi_item, rather than copying the value.  The gsi_item should
       ;; therefore not be reclaimed until after the CORBA operation is invoked.
       (emit i "~A._value = idl_any_item_value(~A);" c++var gsi-item))
      ;; Again, note the following emitted statement is atypical in that it
      ;; makes the C++ variable point to a value inside the gsi_item, rather
      ;; than copying the value.  This is another reason not to reclaim the
      ;; gsi_item until after the CORBA operation is invoked.
      ((idl-string-declarator-p idl-built-in-type)
       (emit i "~A = (char *) gsi_str_of(~A);" c++var gsi-item))
      ((idl-sequence-declarator-p idl-built-in-type)
       (emit-inward-idl-sequence-marshalling
	 idl-built-in-type
	 c++var
	 gsi-item
	 nearest-namespace
	 g2-output-stream
	 i))
      ((idl-scoped-name-p idl-built-in-type)
       (emit-inward-idl-built-in-marshalling
	 (chase-idl-type idl-built-in-type nil)
	 c++var
	 gsi-item
	 nearest-namespace
	 g2-output-stream
	 i))
      ((g2-idl-object-reference-p idl-built-in-type)
       (let ((scoped-name
	       (get-scoped-idl-definition-name
		 (idl-definition-name-as-text idl-built-in-type))))
	 (emit i "~A = (~A *) map_g2pointer_to_cpointer(gsi_int_of(~A));"
	       c++var
	       scoped-name
	       gsi-item
	       g2-output-stream
	       i)))
      (t (signal-idl-to-g2-error 'bad-idl-built-in-type idl-built-in-type)))))
    
;;; The void function `emit-inward-idl-built-in-marshalling' takes five
;;; arguments: a symbol or idl-list specifying an IDL built-in-type, a shared
;;; text-string naming a C++ variable, a shared text string naming a gsi_item, a
;;; g2-corba-definition-spec-mixin that contains the nearest enclosing namespace
;;; a g2-stream that outputs to a GSI source file, and a fixnum indentation
;;; depth.  This function emits code that causes the C++ variable to have the
;;; value stored inside the gsi_item.  The emitted code makes type and other
;;; conversions as appropriate, based on the semantics of the Orbix IDL
;;; compiler.  Unlike emit-inward-idl-user-marshalling,
;;; emit-inward-idl-built-in-marshalling does not emit a complete C++ function.

;;; The code emitted by `emit-inward-idl-built-in-marshalling' expects to link
;;; with the following utility functions in /bt/ab/ext/c/corba.c:
;;; idl_item_any_type_tag() and idl_item_any_value().  See that file for
;;; details.

;;; If the first argument specifies an IDL scoped name, that name must denote a
;;; built-in type (either directly or through a series of typedefs).  This is a
;;; semantic, not a syntactic, constraint on the IDL that describes a built-in
;;; type.

(defun-void emit-inward-idl-built-in-marshalling
    (idl-built-in-type c++var gsi-item nearest-namespace g2-output-stream i)
  (with-emit-bindings (g2-output-stream)
    (case idl-built-in-type
      (boolean
       (emit i "~A = (unsigned char) gsi_log_of(~A);" c++var gsi-item))
      (char
       (emit i "~A = (char) gsi_int_of(~A);" c++var gsi-item))
      (octet
       (emit i "~A = (unsigned char) gsi_int_of(~A);" c++var gsi-item))
      (short
       (emit i "~A = (short) gsi_int_of(~A);" c++var gsi-item))
      (unsigned-short
       (emit i "~A = (unsigned short) gsi_int_of(~A);" c++var gsi-item))
      (long
       (emit i "~A = (long) gsi_flt_of(~A);" c++var gsi-item))
      (unsigned-long
       (emit i "~A = (unsigned long) gsi_flt_of(~A);" c++var gsi-item))
      (float
       (emit i "~A = (float) gsi_flt_of(~A);" c++var gsi-item))
      (double
       (emit i "~A = (double) gsi_flt_of(~A);" c++var gsi-item))
      (otherwise
       (emit-inward-idl-compound-marshalling
	 idl-built-in-type
	 c++var
	 gsi-item
	 nearest-namespace
	 g2-output-stream
	 i)))))

;;; According to the Orbix Programmer's Guide pp 20 ff, we have to parameterize
;;; `get-scoped-idl-definition-name' according to whether or not the C++
;;; compiler can handle nested classes.

(defun get-scoped-idl-definition-name
    (idl-definition &optional (nested-classes-p t))
  (let ((delimitor (if nested-classes-p "::" "_"))
	(components
	  (nreverse
	    (loop for definition?
		      = idl-definition
		      then (nearest-enclosing-idl-spec? definition?)
		  while definition?
		  collect (idl-definition-name-as-text definition?)
		    using idl-cons))))
    (prog1
	(twith-output-to-text-string
	  (loop for component in components
		for component-cons on components
		for last-component-p = (null (cdr component-cons))
		do (twrite-string component)
		unless last-component-p do (twrite-string delimitor)))
      (reclaim-idl-list components))))

(defmacro idl-typecase (idl-struct &body clauses)
  (avoiding-variable-capture (idl-struct)
    `(cond 
       ,@(loop for (type . actions) in clauses
	       do
	   (unless (memq type '(array struct union enum))
	     (error "IDL-TYPECASE: unknown type ~s" type))
	       collect
	       (if (memq type '(t otherwise))
		   `(t ,@actions)
		   `((,(case type
			 (array  'g2-corba-array-definition-spec-p)
			 (struct 'g2-corba-struct-definition-spec-p)
			 (union  'g2-corba-union-definition-spec-p)
			 (enum   'g2-corba-enum-definition-spec-p))
		       ,idl-struct)
		     ,@actions)))
       ,@(if (eval-feature :development)
	     `((t (cerror "Continue, taking no action.  ~
                           (This behavior is what the user would get)"
			  "~s is of unknown IDL type"
			  ,idl-struct)))
	     nil))))

(defun-void emit-inward-idl-user-marshalling-body
    (idl-definition g2-output-stream depth)
  (declare (ignore idl-definition g2-output-stream depth))
  #+not-yet
  (with-emit-bindings (g2-output-straeam)
    (idl-typecase idl-definition
      (array ...)
      (struct ...)
      (union ...)
      (enum ...))))

;;; The void function `emit-inward-idl-user-marshalling' takes two arguments: a
;;; g2-corba-definition-mixin structure representing a user-defined IDL type and
;;; a g2-stream that outputs to a GSI source file.  This function emits code for
;;; a C++ function that uses a gsi_item to assign values to the fields in a
;;; CORBA class instance.  This instance will subsequently be used as an
;;; argument to a CORBA operation.  The emitted C++ function takes two
;;; arguments, a pointer to a gsi_item and a C++ reference to an instance of a
;;; class generated by the Orbix IDL compiler.  The name of the emitted C++
;;; function is of the form marshall_<type>_into_corba().  It is a top-level
;;; function (as opposed to a member function of some class).  Since we (will)
;;; check for case-insensitive name collisions in G2 before emitting this
;;; function, we are guaranteed that there will be no case-sensitive collisions
;;; in C++.

(defun-void emit-inward-idl-user-marshalling
    (idl-definition g2-output-stream)
  (with-emit-bindings (g2-output-stream)
    (let* ((definition-name (idl-definition-name-as-text idl-definition))
	   (scoped-definition-name
	     (get-scoped-idl-definition-name idl-definition)))
      (emit 0 "marshall_~A_into_corba" definition-name)
      (emit 0 "  (gsi_item *idl_source,")
      (emit 0 "   ~A &      idl_sink)" scoped-definition-name)
      (emit 0 "{")
      (emit-inward-idl-user-marshalling-body
	idl-definition
	g2-output-stream
	1)
      (emit 0 "}")
      (emit 0 "")
      (emit 0 "")
      (reclaim-text-string scoped-definition-name))))

;;;; Marshalling "Out" Parameters

#+not-yet
(defun-void emit-outward-corba-marshalling
    (idl-definition g2-output-stream)
  ...
  )

;;; The GSI side needs code to convert back and forth between gsi_item and the
;;; C++ type created by the IDL compiler.  Policy: each
;;; g2-corba-definition-mixin stores enough information to generate this code.

;; For "in" parameters, have to send from G2 to GSI, then marshall from gsi_item
;; into C++ on the bridge side.  Have to do something reasonable with legacy G2
;; items, maybe turn them into IDL structs.

;; For "out" parameters, have to marshal from C++ into gsi_item type on the
;; bridge side, then send to G2.




;;;; System Procedures for G2 Legacy KB as CORBA Server

;; create-corba-server-item-list() => corba-server-item-list
;;   {items include module name somehow}

;; delete-corba-server-item-list(class corba-server-item-list) => true

;; add-to-corba-server-item-list(class item, class corba-server-item-list)
;;   => true or class corba-server-error
;;   {uses define-analyze-for-consistency to notify if someone
;;    changes network restrictions to make unreadable}
;;   {error trying to something other than:
;;      a G2 object representing a CORBA datatype
;;      an object-definition
;;      a method definition}
;;   {how to designate attributes?! use include/exclude grammar from object-passing?!}

;; remove-from-corba-server-item-list(class item, class corba-server-item-list)
;;   => true or class corba-server-error
;;   {undoes the define-analyze-for-consistency}

;; emit-idl-for-corba-server-list(idl-filename: text, class corba-server-item-list)
;;   => true or class corba-server-error or class corba-server-warning

;; possible UI stuff

;; mark-item-for-corba-service()
;;   {does it more visibly, somehow}
;;   {perhaps sets up a "combobox" of marked objects}
;;   {options for module name?  use existing one, make one up, ask the user}

;;;; System Procedures for CORBA Server Stubs in G2

;; Similar algorithm to "System Procedures for G2 as CORBA Client", but instead
;; of calling a remote-procedure, each method body has a "work in process"
;; comment.

;; get-corba-server-stub-list-from-idl(idl-filename: text)
;;   => class corba-server-stub-list, idl-server-warning or false
;;   {items include module name somehow}

;; delete-corba-client-stub-list-and-elements(class corba-client-stub-list)
;;   => true or class idl-server-error

;; possible UI stuff

;; populate-workspace-from-corba-server-stub-list(class corba-server-stub-list)
;;   {similar to populate-workspace-from-corba-client-proxy-list()}


(defun emit-g2-server-idl-from-marked-items ()

  ;; probably want to check network restrictions to be sure that items are
  ;; remotely visible

  )

;;;; Error Handling

;; possible UI stuff

;; idl-error-to-text(class idl-error)

;; concoct-idl-error-continuation-options(class idl-error)
;;   {rename class,
;;    edit class definition,
;;    reread IDL after editing,
;;    etc}
;;   {probably need sticky permission to overwrite from the same IDL}

;;;; Coding the GSI CORBA Integration Bridge

;;;; Launching the CORBA Integration Bridge 

;;;; Stopping the CORBA Integration Bridge


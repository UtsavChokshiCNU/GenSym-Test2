; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module UTILITIES2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David, Lowell Hawkinson, Michael Levin, Stephen DeVoy, Jim Allard,
;;; and Ben Hyde




(declare-forward-reference equal-rule-context function)        ; in RULES
#+development(declare-forward-reference eval-cons-1 function) ; in TYPES
(declare-forward-reference signal-gsi-index-space-full-error
                          function) ;in GSI

(declare-forward-reference g2-random function) ; in UTILITIES3
#+Lockfree-Deque
(declare-forward-reference merge-constant-queues function) ; in SCHEDULE



;;;; Gensym Structure Descriptions



;;; The descriptive knowledge about gensym structures is stored
;;; on the plists of the two symbols that define that name the structure.
;;; These two symbols (for example gensym-window and
;;; g2-defstruct-structure-name::gensym-window-g2-struct) are known
;;; as the ab type name and the unique type name.

;;; The properties include:
;;;                                                         Available
;;;        Property                       Where             at Runtime?
;;;   ab-name-of-unique-structure-type <unique-type-name>     Yes
;;;   unique-structure-type-of-ab-name?<ab-type-name>         No
;;;   slot-names-in-gensym-structure   <unique-type-name>     No
;;;   gensym-structure-printer?        <unique-type-name>     No
;;;   def-structure-slot-descriptions  <ab-type-name>         No?

;; The "Available at Runtime?" entries are not accurate, mostly due to flaws in
;; the implementation that follows.  They are "what ought to be true."



;;; The global property `slot-names-in-gensym-structure' is a development only
;;; global property which contains an ordered list of the slot names for a given
;;; structure type.  It is used by describe-structure.

#+development
(def-global-property-name slot-names-in-gensym-structure)



;;; The macro time, global property `def-structure-slot-descriptions' is used to
;;; associate structure names with the list of slots for that structure.  This
;;; data is required to implement the :include option for def-structure.  It
;;; will not be available in release compiles of the software.

(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name def-structure-slot-descriptions)
)


;;; The development only global property `gensym-structure-printer?'  is used on
;;; gensym structure unique type names to specify a printer for the structure in
;;; development Lispm implementations.  This is directly analagous to the
;;; defstruct's print-function.

#+development
(def-global-property-name gensym-structure-printer?)



;;; `Ab-name-of-unique-structure-type' and `unique-structure-type-of-ab-name?'
;;; implement the relation ship between the ab type name and the actual name used
;;; for named structures.  These are global properties. Unnamed structures
;;; types return nil for unique-structure-type-of-ab-name?.

;;; In named structures the zeroth element is the unique type name. For example:
;;;   (g2-type-name-of-named-simple-vector current-workstation)
;;;     -> (svref current-workstation 0)
;;;       -> g2-defstruct-structure-name::workstation-g2-struct
;;;   (ab-name-of-unique-structure-type *) -> workstation

(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name ab-name-of-unique-structure-type)
(def-global-property-name unique-structure-type-of-ab-name?)
)

(defmacro lookup-structure-method-function (structure method-id)
  `(svref (method-table-of-type-description
            (type-description-of-structure ,structure)) ,method-id))


(defun find-structure-method (method-name structure)
  (let ((method-id? (map-structure-method-name-to-id? method-name)))
    (when method-id?
      (lookup-structure-method-function structure method-id?))))


;;; The global property `direct-methods-defined' is found on the ab-type-names
;;; of structures.  It records those methods defined directly on that type name,
;;; i.e. for which a (def-structure-method <method-name> (<ab-type-name>...)...)
;;; occurs.  It is used at load time to construct the method dispatch tables.



#+development
(defun describe-gensym-structure-type (structure-ab-type)
  (let* ((unique-structure-type-of-ab-name?
           (unique-structure-type-of-ab-name? structure-ab-type))
;         (slot-names-in-gensym-structure
;           unique-structure-type-of-ab-name?))
         (gensym-structure-printer?
           (gensym-structure-printer?
             unique-structure-type-of-ab-name?))
         (type-description
           (type-description-of-unique-type-name-of-gensym-structure
             unique-structure-type-of-ab-name?))
         (def-structure-slot-descriptions
             (def-structure-slot-descriptions structure-ab-type))
         (methods-table
           (method-table-of-type-description type-description))
         (direct-methods
           (direct-methods-of-type-description
             (type-description-of-type structure-ab-type)))
         (*print-pretty* t))
    (cond
      (unique-structure-type-of-ab-name?
       (format t "~&~S is named and has unique type name ~S"
               structure-ab-type unique-structure-type-of-ab-name?))
      (t
       (format t "~&S is an unnamed structure type.")))
    (format t "~&~S has these slot-descriptions ~(~{~&  ~S~}~)"
            structure-ab-type def-structure-slot-descriptions)
    (format t "~& it has this type description: ~S"
            type-description)
    (format t "~& it is printed by ~A"
            (if gensym-structure-printer? gensym-structure-printer? "<the default printer>"))
    (format t "~& it has this method behavor:")
    (loop for method-id from 0 below (length methods-table)
          as method-name = (map-structure-id-to-method-name? method-id)
          as directly-defined? = (assq method-name direct-methods)
          do (format t "~&  ~A ~D  ~S is handled by ~S"
                     (if directly-defined? "*" " ")
                     method-id
                     method-name
                     (svref methods-table method-id)))))







;;;; Substrate for Methods on Gensym Structures



;;; Methods on ab structures are dispatched thru a vector associated with each
;;; named structure.  The method-name is mapped to a method id, aka a small
;;; fixnum, to do this indexing.  See the section "Structure Method Dispatch
;;; Tables" in UTILITIES1 for implementation details.




;;; The method dispatch tables are filled out from the information recorded in
;;; the `direct-methods-of-type-description.'  This happens at load time. There
;;; is a risk that a method might be used prior to the dispatch table being
;;; setup.  When ever this property is updated a call on
;;; propogate-structure-method brings the dispatch tables into synch.

(defun record-direct-structure-method (method-name structure-ab-type method-function)
  (let* ((type-description (type-description-of-type structure-ab-type))
         (direct-methods ;; rebound, and stored.
           (direct-methods-of-type-description type-description))
         (existing-entry? (assq method-name direct-methods)))
    (cond
      (existing-entry?
       (setf (second existing-entry?) method-function))
      (t
       (push
         (list method-name method-function)
         direct-methods)))
    (setf (direct-methods-of-type-description type-description)
          direct-methods))
  (set-structure-method-and-propogate
    structure-ab-type
    method-name
    (map-structure-method-name-to-id? method-name)
    method-function))

(defun direct-structure-method (method-name structure-ab-type)
  (let* ((type-description (type-description-of-type structure-ab-type))
         (direct-methods ;; rebound, and stored.
           (direct-methods-of-type-description type-description)))
    (second (assq method-name direct-methods))))

(defsetf direct-structure-method record-direct-structure-method)




;;; `Set-structure-method-and-propogate' recursively propogates a
;;; method-implementation into the method dispatch tables of the given type and
;;; those time that refine it which do not, them selves, define this method.

(defun set-structure-method-and-propogate (structure-ab-type method-name method-id method-function)
  (let* ((type-description (type-description-of-type structure-ab-type))
         (dispatch-table-of-this-structure-type
           (method-table-of-type-description type-description)))
    (setf (svref dispatch-table-of-this-structure-type method-id)
          method-function)
    ;;; Propogate too
    (loop for subtype in (direct-inferiors-of-type-description type-description)
          unless (or (not (type? subtype))
                     (assq method-name
                           (direct-methods-of-type-description
                             (type-description-of-type subtype))))
            do (set-structure-method-and-propogate
                 subtype method-name method-id method-function))))



;;; The global property `structure-method-arglist' records the arglist used on
;;; structure methods, so congruence can be checked when individual methods are
;;; defined.  This is available only at compile time.

(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name structure-method-arglist)
)



;;; `Def-generic-structure-method' creates a generic function to dispatch
;;; to the actual method for a given instance.  It records the lambda
;;; list given so each individual def-structure-method's arg list can be
;;; checked for congruence.

;;; Three symbols are defined by (def-generic-structure-method <method-name> ...).
;;;   <method-name>           -- a macro (aka the generic function).
;;;   <method-name>-macro     -- a macro
;;;   <method-name>-function  -- an actual function.

;;; A corresponding def-generic-structure-method-id must have been previously
;;; established.

(defmacro def-generic-structure-method
    (method-name (structure-name &rest remainder-of-simple-lambda-list) &body body)
  (unless (null body)
    (warn "Def-generic-structure-method currently takes no body."))
  (let ((method-id? (map-structure-method-name-to-id? method-name))
        (method-function (build-ab-symbol method-name "FUNCTION"))
        (method-macro (build-ab-symbol method-name "MACRO"))
        (get-method-macro (build-ab-symbol "GET-FUNCTION-FOR" method-name))
        (generic-function method-name)
        )
    (unless method-id?
      (warn
        "Def-generic-structure-method attempted on unknown method name ~S, ~
         see def-generic-structure-method-id in UTILITIES1"
        method-name))
    `(progn
       ,(unless (eval-feature :no-macros)
          `(eval-when (:compile-toplevel :load-toplevel :execute)
             (setf (structure-method-arglist ',method-name)
                   '(,structure-name ,@remainder-of-simple-lambda-list))))
      (defmacro ,method-macro (,structure-name ,@remainder-of-simple-lambda-list)
        (expand-structure-method-macro ,method-id? ,structure-name
                                       (list ,@remainder-of-simple-lambda-list)))
      (defmacro ,get-method-macro (,structure-name)
        (expand-structure-get-method-macro ,method-id? ,structure-name))
      (defun ,method-function (,structure-name ,@remainder-of-simple-lambda-list)
        (,method-macro ,structure-name ,@remainder-of-simple-lambda-list))
      (defmacro ,generic-function (,structure-name ,@remainder-of-simple-lambda-list)
        (list ',method-macro ,structure-name ,@remainder-of-simple-lambda-list))
        )))

(defun-for-macro expand-structure-method-macro
    (method-id structure rest-of-lambda-list)
  (if (symbolp structure)
      `(funcall-simple-compiled-function
        (compiled-function-in-place
          (lookup-structure-method-function ,structure ,method-id))
        ,structure
        ,@rest-of-lambda-list)
      `(let ((#1=#:structure ,structure))
         ,(expand-structure-method-macro method-id '#1# rest-of-lambda-list))))

(defun-for-macro expand-structure-get-method-macro
    (method-id structure)
  (if (symbolp structure)
      `(compiled-function-in-place
         (lookup-structure-method-function ,structure ,method-id))
      `(let ((#1=#:structure ,structure))
         ,(expand-structure-get-method-macro method-id '#1#))))




;;; `Def-structure-method' is used to define individual methods on structures.
;;; It will check for argument list congruence with a previously encountered
;;; generic structure method.  Within the body you may use
;;; funcall-superior-method.

#+(and lispworks (not chestnut-3))
(dspec:define-form-parser def-structure-method (operation type-and-args)
    `(,def-structure-method ,operation ,(car type-and-args)))

(defmacro def-structure-method (method-name (structure-type &rest remaining-lambda-list) &body body)
  (let* ((method-function
          (build-ab-symbol method-name "for" structure-type))
         (generic-lambda-list (structure-method-arglist method-name))
         (method-id (map-structure-method-name-to-id? method-name)))
    (unless generic-lambda-list
      (warn "The ~S structure method on ~S is not congruent with its generic definition, i.e. ~S"
            method-name structure-type `(,structure-type ,@remaining-lambda-list)))
    (multiple-value-bind (declarations-and-documentation rest-of-body)
        (split-declarations-and-documentation-from-statements body)
      `(progn
         (defun-into-place
             (,method-function
                (direct-structure-method ',method-name ',structure-type))
             (,structure-type ,@remaining-lambda-list)
          ,@declarations-and-documentation
          (macrolet
              ((funcall-superior-method
                   (frame &rest args)
                 (list 'funcall-superior-structure-method-1
                       ',structure-type
                       ,method-id
                       frame
                       args)))
            (block ,method-name
              ,@rest-of-body)))
        ',method-function))))

(defmacro funcall-superior-structure-method-1
    (type-with-the-direct-method method-id instance args)
  (let ((type-description-var
         (build-type-description-var-of-type-name type-with-the-direct-method)))
  `(funcall-simple-compiled-function
     (compiled-function-in-place
       (svref (superior-dispatch-table
                (method-table-of-type-description ,type-description-var))
              ,method-id))
     ,instance
     ,@args)))




;;;; Type-checked accessors.



;;; The macro `typecheck' is a crufty type checker which assumes that
;;; there is a predicate named <type>-p.

(defmacro typecheck (argument-name &optional (type argument-name))
  #+development
  (let ((predicate (build-ab-symbol type "P")))
    `(assert (,predicate ,argument-name) () ,(format nil "~~s is not a ~s" type) ,argument-name))
  #-development
  (declare (ignore type)))



;;; The macro `def-accessor' defines a macro accessor form which
;;; typechecks its first argument in development.

(defmacro def-accessor (name (structure &rest args) &body body)
  #+development
  (let ((setter (build-ab-symbol 'set name)))
    `(progn
       (defmacro ,name (,structure ,@args)
         `(progn
            (typecheck ,,structure ,',structure)
            ,,@body))
       (defmacro ,setter (,structure ,@args new-value)
         `(progn
            (typecheck ,,structure ,',structure)
            (setf ,,@body ,new-value)))))

  #-development
  `(defmacro ,name (,structure ,@args)
     ,@body))




;;;; Structures: Defstruct for G2


;;; The macro `defstruct-g2' has been written as an internal tool for the
;;; def-structure macro, defined below.  It mimics the Common Lisp definition of
;;; defstruct.  It was written because of differences in the implementations of
;;; defstruct in the different vendor's Lisps which were hindering our attempts
;;; to implement a reclaiming scheme within the type specifier of a structure,
;;; because of our desire to have these elements print nicely in our development
;;; environment, and because of our desire to have accessors defined as macros
;;; instead of functions.  Specifically there were several bugs (or non-standard
;;; implementation decisions, if you prefer) in the Texas Instruments
;;; implementation which were forcing us to declare default values for slots
;;; whether we wanted them or not, and an unusual implementation of the naming
;;; structure which hindered our data corruption detection mechanism, as well as
;;; the printing facility.

;;; This implementation offers a limited set of the options available in CLtL
;;; defstruct, and defines accessors as macros instead of functions declared
;;; inline.  This is to force inline coding of these accessors, and also allows
;;; us to compile out the macro definitions when compiling a version for
;;; release.  The defstruct options that defstruct-g2 supports are as follows:

;;;   :constructor can be used to explicitly name the macro which will be
;;;   defined for creating new structure instances.  This option is limited from
;;;   the defstruct definition in that it requires a null argument list to be
;;;   passed.  See def-structure for a :constructor option which allows
;;;   arguments.

;;;   :predicate can be used to explicitly name the macro which will be defined
;;;   as a predicate for instances of this structure.  By default a predicate is
;;;   defined whose name is generated by concatenating "-p" onto the end of the
;;;   name of the structure.  If this option is given with a null argument, no
;;;   predicate is defined.

;;;   :print-function can be used to declare a function which will be called as
;;;   the printer for instances of this structure.  This option has an effect
;;;   only in Lisp machine development implementations.

;;;   :type can be used to explicitly control the type of the underlying
;;;   structure which is created for instances.  By default, structures are
;;;   defined as type vector.  The other allowable type is list.  Note that if
;;;   this option is specified, by default the created structure will not be
;;;   named, and so no predicate can be defined for this structure.  If the
;;;   :named option is also given when giving an explicit type, then a predicate
;;;   may be defined.

;;;   :named can be used to cause a named structure to be created when giving
;;;   the type option.  By default structures are of type vector and are named,
;;;   but if the :type option is given, then :named must also be given for this
;;;   to be a named structure.  Names are stored in the zeroth element of the
;;;   created structure, (aref structure 0) if this is of type vector, and (car
;;;   structure) if it is of type list.  The stored name is a symbol in the
;;;   g2-defstruct-structure-name package which has a similar symbol name as the
;;;   symbol which was given as the name of this structure.  (These symbols are
;;;   created with the macro intern-unique-def-structure-symbol-name.  These
;;;   symbols are placed in a different package so that there will be no
;;;   collisions between names of structures and names of classes.  The
;;;   predicates for both of these systems use the same naming scheme, and so
;;;   would not be able to distinguish between instances of these different
;;;   systems which had the same symbol name.

;;; :slot-offset takes a list of arguments, each argument either a symbol,
;;; slot-name, or a list (slot-name variable-name). Variable-name defaults to
;;; slot-name-OFFSET. The variable holds a small integer which is the offset of the
;;; respective slot from the begining of the structure. The right thing happens for
;;; named structures. Conceptually you do (elt structure slot-offset) to get the
;;; contents of the slot. Usually svref if used for speed. See the structure
;;; schedule-task for an example usage.

;;; The :conc-name option is not supported, but defstruct-g2 behaves like the
;;; normal defstruct would with :conc-name nil specified.  The :copier,
;;; :include, and :initial-offset options are not supported.  The :include
;;; option is supported at the level of def-structure.

;;; Defstruct-g2 takes the :type slot option, as per CLtL defstruct.  It causes
;;; the accessors to be defined with explicit type declarations on the value
;;; being returned.  The slot option `:no-accessor' t is also accepted.  It is
;;; used by the :include option of def-structure when slots have been included
;;; from a previous structure.  It directs that no accessor (or setf mutator)
;;; should be defined, though an spot should be left in the structure for the
;;; slot.  The slot has already been defined the by included structure.

;;; The macro `defstruct-g2' defines a structure, a creator function, possibly a
;;; predicate, and accessors for the slots of the structure.


(defmacro defstruct-g2 (type-with-options &body slot-descriptions)
  (if (atom type-with-options)
      (setq type-with-options (list type-with-options)))
  (let* ((type-name (first type-with-options))
         (options (cdr type-with-options))
         (constructor-name (build-ab-symbol "MAKE" type-name))
         (type? nil)
         (force-named? nil)
         (predicate-name? nil)
         (predicate-option-given? nil)
         (print-function? nil)
         (slot-initializations nil)
         (structure-arg type-name)
         (structure-var (build-ab-symbol "DEFSTRUCT-G2" type-name "VARIABLE"))
         structure-length
         (unique-type-name
           (if (symbolp type-name)
               (intern-unique-def-structure-symbol-name type-name)
               (error "Defstruct-g2 needs a symbol for a structure name, it was ~S."
                      type-name)))
         (slot-offset nil))

    ;; Collect the option information for the structure.

    (loop for option in options
          do
      (cond ((consp option)
             (case (car option)
               ((:constructor)
                (setq constructor-name (second option))
                (if (not (null (third option)))
                    (error "Defstruct-g2 only takes null argument lists~%~
                            in its constructor option, in structure ~A."
                           type-name)))
               ((:predicate)
                (setq predicate-name? (second option))
                (setq predicate-option-given? t))
               ((:print-function)
                (setq print-function? (second option))
                (when (not (symbolp print-function?))
                  (warn "The :PRINT-FUNCTION option to DEF-STRUCTURE ~A did~@
                         not have a symbol as its argument, and so will be ignored.~@
                         The argument was:~%~a"
                        type-name print-function?)
                  (setq print-function? nil)))
               ((:type)
                (setq type? (second option))
                (if (and (neq type? 'list) (neq type? 'vector))
                    (error "Defstruct-g2 only allows type vector or list.~%~
                            Offending type: ~A"
                           option)))
               ((:eliminate-for-products) nil)
               ((:slot-offset)
                (setf slot-offset (cdr option)))
               (t
                 (error "Unknown option to defstruct-g2: ~A" option))))
            ((eq option :named)
             (setq force-named? t))
            (t
             (error "Unknown option to defstruct-g2: ~A" option))))

    ;; Set what the type and named flags should really be, and from that decide how
    ;; many slots we'll need in the structure, and if we can have a predicate.

    (when (and (not force-named?) (null type?))
      (setq force-named? t))
    (unless type?
      (setq type? 'vector))
    (setq structure-length (+ (length slot-descriptions) (if force-named? 1 0)))
    (cond
      (predicate-option-given?
        (when (and predicate-name? (null force-named?))
          (error "Can't have a defstruct-g2 predicate in an unnamed structure.~%~
                       Name of offending structure: ~A"
                 type-name)))
      (force-named?
       (setq predicate-name? (build-ab-symbol type-name "P"))))

    ;; Collect the initializations for slots.

    (loop for slot in slot-descriptions
          do
      (cond ((consp slot)
             (if (not (consp (cdr slot)))
                 (error "No initialization for listed slot in defstruct-g2~%~
                         Offending slot: ~A"
                        slot))

             ;; While we're here, check that only allowable slot options are
             ;; listed.
             (loop with type = t
                   for option on (cddr slot) by 'cddr
                   do
               (if (null (cdr option))
                   (error "Defstruct-g2 slot options must be given in option and value~%~
                           pairs.  Offending slot: ~A"
                          slot))
               (case (car option)
                 ((:type) (setq type (cadr option)) nil)
                 ((:no-accessor) nil)
                 (t
                   (error "~A is not a supported defstruct-g2 slot option.~%~
                           Offending slot: ~A"
                          (car option)
                          slot)))
                   finally
                     (when (or (eq type 't)
                               (typep (second slot) type))
                       (push (list (first slot) (second slot)) slot-initializations)))))
          finally
            (setq slot-initializations (nreverse slot-initializations)))

    ;; Generate code.

    `(progn

       ;; Insert the code defining the slot accessor macros.

       ,@(let (res)
           (loop named top
                 for x in slot-offset do
             (gensym-dstruct-bind ((s v) (if (listp x) x (list x (intern (format nil "~S-OFFSET" x)))))
               (loop for slot in slot-descriptions
                     for slot-index from (if force-named? 1 0)
                     do
                 (if (listp slot)
                     (setf slot (car slot)))
                 (when (eq slot s)
                   (push `(defconstant ,v ,slot-index ,(format nil "slot offset for ~S in structure ~S" s type-name)) res)
                   (return-from top t)))
               (warn "unknown slot offset entry ~S" x)))
           (reverse res))

       ,@(loop for slot in slot-descriptions
               for position = (if force-named? 1 0)
                            then (+ position 1)
               for slot-type? = (if (and (consp slot) (> (length slot) 2))
                                    (memq :type (cddr slot))
                                    nil)
               for no-accessor? = (if (and (consp slot) (> (length slot) 2))
                                      (memq :no-accessor (cddr slot))
                                      nil)
               unless (and no-accessor? (second no-accessor?))
                 collect
                   (if slot-type?
                       `(defmacro ,(first slot) (,structure-arg)
                          ,(if (eq type? 'vector)
                               ``(the ,',(second slot-type?)
                                      (svref ,,structure-arg ,',position))
                               ``(the ,',(second slot-type?)
                                      (car (nthcdr-macro
                                             ,',position
                                             ,,structure-arg)))))
                       `(defmacro ,(if (consp slot) (first slot) slot)
                                  (,structure-arg)
                          ,(if (eq type? 'vector)
                               ``(svref ,,structure-arg ,',position)
                               ``(car (nthcdr-macro
                                        ,',position
                                        ,,structure-arg))))))

       ,@(unless (eval-feature :no-macros)
           `((note-non-resumable-function-call-macro
               ',constructor-name
               ,@(when predicate-name?
                   `(',predicate-name?)))
             (note-function-call-accessor-macro
               ,@(loop for slot in slot-descriptions
                       for slot-type? = (if (and (consp slot) (> (length slot) 2))
                                            (memq :type (cddr slot))
                                            nil)
                       for no-accessor? = (if (and (consp slot) (> (length slot) 2))
                                              (memq :no-accessor (cddr slot))
                                              nil)
                       unless (and no-accessor? (second no-accessor?))
                         collect `',(if slot-type?
                                        (first slot)
                                        (if (consp slot) (first slot) slot))))))


       ;; Insert code for the predicate, if one is defined.  Note that the
       ;; predicate will not be checking the length of vector before it performs
       ;; the call to svref.  We assume that there will be no zero length
       ;; vectors passed in to this code.

       ,@(if predicate-name?
             `((def-substitution-macro ,predicate-name? (thing)
                 ,(if (eq type? 'vector)
                      `(and (simple-vector-p thing)
                            (eq (g2-type-name-of-named-simple-vector thing) ',unique-type-name))
                      `(and (consp thing)
                            (eq (car-of-cons thing) ',unique-type-name)))))
             nil)

       ;; Define the constructor.  In the odd case that there are no
       ;; initializations and the structure is unnamed, don't bother with the
       ;; let, just return the created structure.

       (defmacro ,constructor-name ()
         ,(if (or force-named? slot-initializations)
              `'(let ((,structure-var nil))
                  ,(if (eq type? 'vector)
                       `(setq ,structure-var
                                (make-array-with-nils ,structure-length))
                       `(setq ,structure-var
                              (make-mutable-list ,structure-length)))
                  ,@(if force-named?
                        (if (eq type? 'vector)
                            `((setf (g2-type-name-of-named-simple-vector ,structure-var) ',unique-type-name))
                            `((setf (car ,structure-var) ',unique-type-name)))
                        nil)
                  ,@(loop for init-spec in slot-initializations
                          collect
                            `(setf (,(first init-spec) ,structure-var)
                                   ,(second init-spec)))
                  ,structure-var)
              (if (eq type? 'vector)
                  `'(let ((,structure-var
                           (make-array-with-nils ,structure-length)))
                      ,structure-var)
                  `'(make-mutable-list ,structure-length))))

       ,@(when force-named?
           `((eval-when (:compile-toplevel :load-toplevel :execute)
               (setf (ab-name-of-unique-structure-type ',unique-type-name)
                   ',type-name)
               (setf (unique-structure-type-of-ab-name? ',type-name)
                  ',unique-type-name))))

       #+development
       (register-definition ',type-name 'gensym-structure)

       #+development
       (setf (slot-names-in-gensym-structure ',unique-type-name)
             ',(loop for slot-description in slot-descriptions
                     collect (if (atom slot-description)
                                 slot-description
                                 (car slot-description))))
       ,@(when print-function?
           #+development
           `((setf (gensym-structure-printer? ',unique-type-name)
                   ',print-function?))
           #-development
           nil)

       ;; Finally, return the name of the structure being defined.
       ',type-name)))

(def-system-variable structure-being-reclaimed utilities2
  nil nil
  ;; now bound globally to allow use at load time (MHD 2/21/96)
  t)

(defun reset-structure-being-reclaimed-after-bombout ()
  (setq structure-being-reclaimed nil))

;; jh, 12/12/91.  Moved the following form to OS-ERROR because
;; def-bombout-cleanup-function is defined there.  It is not clear that this
;; gensym-structure belongs in a UTILITIES module, so this might not be the final
;; fix.
;(def-bombout-clean-up-function 'reset-structure-being-reclaimed-after-bombout)














;;; The function `type-of-named-structure' takes an instance of a named
;;; structure created with def-structure and returns the structure type.  Note
;;; that the symbol stored in the zeroth element of the structure is not the
;;; name, but is instead of unique name in a different package.  The name
;;; returned here is actually on a property of that symbol.

(defun-simple type-of-named-structure (named-structure-instance)
  (ab-name-of-unique-structure-type
    (if (simple-vector-p named-structure-instance)
        (g2-type-name-of-named-simple-vector named-structure-instance)
        (car named-structure-instance))))




;;; The macro `def-structure' is a more specialized version of defstruct, to be
;;; used in all Gensym software.  Its arguments are identical to those of
;;; defstruct, except for the :constructor option.  It differs from defstruct in
;;; that it automatically specifies (:conc-name nil) and (:copier nil),
;;; correctly manages the areas in which a structure is created, defines a
;;; reclaimer function, has appropriate declarations for compilation, and tries
;;; to make its way around known bugs in various Common Lisp implementations.

;;; The following defstruct options, as described in the Common Lisp manual, may
;;; be specified in the first def-structure argument:  `:constructor', `:predicate',
;;; `:print-function', `:type', `:named', `:include', and `:initial-offset'.

;;; Additional features of def-structure which are not part of defstruct are the
;;; `:creations-at-a-time' options for structures, `:reclaimer' option for
;;; structures and slots, and the `:initialize-on-recycle' option for slots.

;;; Note that def-structure will only define by-order-of-argument constructor
;;; functions.  So, if the constructor option is not given, a MAKE-type
;;; constructor of no arguments will be generated.  If the argument list part of
;;; the constructor option is used, you may not use &optional, &rest, or &aux
;;; arguments.  Def-structure will also create a macro version of the
;;; constructor whose name is the name of the constructor function, with "-MACRO
;;; concatenated onto the end.  (Note that this constructor function does not
;;; always create new structures, but will allocate structures from an available
;;; pool if possible.  If the pool is empty, it will then actually create a new
;;; structure.  Be sure to give back structures you are done with via the
;;; RECLAIM-type function.)

;;; SymScale notes by Chun Tian (binghe): A new thread-specific available pool
;;; design was added into the original work of DEF-STRUCTURE. (GENSYM-47006)

;;; The `:creations-at-a-time' option allows you to specify a positive integer
;;; number of structure instances to be created when the structure pool runs out
;;; of objects.  The default is 1.  A larger number gets better locality of
;;; reference between similar structure instances, and avoids costly multiple
;;; entrance and exits from a permanent consing construct when many instances
;;; need to be created.

;;; The `:reclaimer' option allows you to specify an unquoted symbol which will be
;;; used as the name of the generated reclaimer function.  If this option is
;;; specified with an argument of NIL, no reclaimer or reclaiming mechanisms
;;; will be created.

;;; The `:include' option can be used to cause the slots from a previously defined
;;; structure to also be defined for this structure.  The accessors from the
;;; previously defined structure can then be used on this structure.  The :type
;;; and :named options of the two structure must agree, though a mismatch error
;;; is not necessarily detected by this software.  This option takes an unquoted
;;; symbol naming the other structure as its required argument.  Optionally,
;;; more arguments may be given to this option which are overriding slot
;;; descriptions for slots included from the named structure.  This feature can
;;; be used to redefine default values.  The slots from the included structure
;;; will defined as the first slots of this structure.

;;; By default the slots of a structure are not reclaimed when the structure is
;;; reclaimed.  Using the `:reclaimer' option (e.g.  (my-widget :reclaimer
;;; reclaim-widget)) request that the slots are reclaimed A special variable
;;; named `structure-being-reclaimed' is bound to the containing structure
;;; around the call to the reclaimer.  On return from the reclaimer the slot
;;; value is set to NIL.  Note that the structure reclaimer will not modify any
;;; slots that do not have explicit :reclaimer options, at least until all of
;;; those slot reclaimers have been executed.

;;; By giving the option ":initialize-on-recycle nil" to a slot, you can cause
;;; the initialization of that slot to only occur when a new structure object is
;;; created.  Normally, the initialization form will be evaluated and a new
;;; value put into the slot every time a structure is given out, whether the
;;; structure is newly created or is a recycled structure.  With this option
;;; specified on a slot, that slot will only be initialized on creation.  Note
;;; that this does not always guarantee that a slot will not be modified when a
;;; structure is recycled.  If you have also specified a reclaimer for this slot
;;; the reclaimer will be called and the slot set to NIL on recycle.  Also, if
;;; the structure is of an explicitly declared type and is not named, the first
;;; slot will be modified on recycle.  This second case is described in detail
;;; below.

;;; The option :print-function is directly analagous to the Common Lisp's
;;; defstruct option.  The print function should only be defined in
;;; #+development.

;;; Users who try to keep stuff in structures through the recycling process
;;; (with :initialize-on-recycle nil) should be aware that the zeroth element of
;;; a structure is used by this code to chain together reclaimed structure
;;; objects.  This element is normally used internally by defstruct for the name
;;; of the structure, so if you are using a named structure (which you get if
;;; you don't declare a type, or if you declare a type and the option :named)
;;; you don't need to worry about this.  However, if you have an unnamed, typed
;;; structure, your first slot will contain the symbol naming this structure
;;; when it is returned to you, rather than whatever was in it when it was
;;; reclaimed.  On recycle I use that slot to chain together reclaimed
;;; structures, and on allocation I set it back to the name of the structure
;;; type, whether or not this structure was supposed to be named.

;;; The user should also beware when using typed slots.  This code takes any
;;; initialization forms out of the slot descriptors passed to defstruct and
;;; instead splices then into the managed allocator form.  If there are slot
;;; options that need to be passed on to defstruct, this form will send them
;;; along, and will send NIL as the initial value (CLtL requires an initial
;;; value when giving options to a slot).  If the type given to a slot does not
;;; accept NIL as a value (for example, if the type is gensym-float), this may
;;; cause problems when trying to instantiate the structure.  I don't expect
;;; this to ever come up, but let the buyer beware of declaring types to slots.

;;; Def-structure also defines object-pool-meters under the name of the
;;; structure.  It will also declare a `<type-name>-reclaimed-p' function in the
;;; development system.  It can be used in development to determine in an object
;;; is in the list of reclaimed structures for this type.

;;; Temporary memory meters for constant memory allocation in def-structure
;;; expansions.

#+meter-init-memory
(defparameter structure-memory 0)

#+meter-init-memory
(defparameter before-structure-init 0)

(defmacro def-structure (type-or-type-with-options &body slot-descriptions)
  (when (symbolp type-or-type-with-options)
    (setf type-or-type-with-options
          (list type-or-type-with-options)))
  (unless (eval-feature :development)
    (let ((forbidden-products?
            (cdr (assoc :eliminate-for-products
                        (cdr type-or-type-with-options)))))
      (when forbidden-products?
        (when (member current-system-being-loaded forbidden-products?)
            (return-from def-structure nil)))))
  (let* ((type-name (first type-or-type-with-options))
         (type-description-var-name
          (build-type-description-var-of-type-name type-name))
         (unique-type-name
           (if (symbolp type-name)
               (intern-unique-def-structure-symbol-name type-name)
               (error "Def-structure requires a symbol as a structure name, it was ~s"
                      type-name)))
         (chain-of-available-objects
           (intern (format nil "CHAIN-OF-AVAILABLE-~aS" type-name)))
         #+SymScale
         (chain-of-available-objects-vector
           (intern (format nil "CHAIN-OF-AVAILABLE-~aS-VECTOR" type-name)))
         (chain-slot (intern (format nil "~a-CHAIN-SLOT-INTERNAL" type-name)))
         (created-object-count (intern (format nil "~a-COUNT" type-name)))
         (outstanding-object-function
           (intern (format nil "OUTSTANDING-~a-COUNT" type-name)))
         (object-memory-usage
           (intern (format nil "~a-STRUCTURE-MEMORY-USAGE" type-name)))
         (options (cdr type-or-type-with-options))
         (constructor-name
           (intern (format nil "MAKE-~a-STRUCTURE-INTERNAL" type-name)))
         (permanent-name
           (intern (format nil "MAKE-PERMANENT-~a-STRUCTURE-INTERNAL" type-name)))
         (constructor-spec
           (or (cdr (car (member :constructor options :test 'option-equal)))
               (list (intern (format nil "MAKE-~a" type-name)) nil)) )
         (creation-count
           (or (second (car (member :creations-at-a-time options
                                    :test 'option-equal)))
               1))
         (constructor-count-var (gensym))
         (user-constructor-name (first constructor-spec))
         (user-constructor-actual-name
           (intern (format nil "~a-1" user-constructor-name)))
         (user-constructor-macro
           (intern (format nil "~a-MACRO" user-constructor-name)))
         (user-argument-list (second constructor-spec))
         (structure-arg type-name)
         (structure-var (intern (format nil "DEF-STRUCTURE-~a-VARIABLE" type-name)))
         (user-reclaimer-name?
           (let ((reclaim-option?
                   (car (member :reclaimer options :test 'option-equal))))
             (if reclaim-option?
                 (second reclaim-option?)
                 (build-ab-symbol "RECLAIM" type-name))))
         (user-reclaimer-actual-name?
           (if user-reclaimer-name?
               (intern (format nil "~a-1" user-reclaimer-name?))))
         (user-reclaimer-macro?
           (if user-reclaimer-name?
               (intern (format nil "~a-MACRO" user-reclaimer-name?))))
         (type? (second (car (member :type options :test 'option-equal))))
         (named? (or (not type?)
                     (member :named options)))
         (include-option? (or (car (member :include options :test 'option-equal))
                              (if named? '(:include named-gensym-structure))))
         (included-structure? (second include-option?))
         (superior-type
           (if (null included-structure?) t included-structure?))
         (overriding-include-slot-descriptions (cddr include-option?))
         (slot-initializations nil)
         (initializations-on-creation-only nil)
         (slot-reclaimers nil)
         (defstruct-slot-descriptors nil)
         #+development
         (structure-reclaimed-p
           (intern (format nil "~a-RECLAIMED-P" type-name)))

         ;; Optional :copier
         #+ignore
         (user-copier-name
           (cdr (car (member :copier options :test 'option-equal))))

         #+development
         (old-type-description?
           (type-description-of-type type-name))
         #+development
         (raw-defining-form
           (list 'raw-defining-form type-or-type-with-options slot-descriptions)))

    ;; If there happens to be an old type description, we
    ;; can check to see if something is changing about this
    ;; and if so, we can warn the user that dependent things
    ;; should be recompiled.
    #+development
    (when (and old-type-description?
               (not (equal raw-defining-form
                           (assq 'raw-defining-form
                                 (alist-of-type-description
                                   old-type-description?)))))
      (warn "Recompiling and changing gensym structure ~S, ~
              recompilation of methods, subtypes, etc. is recommended."
            type-name))

    ;; First signal any errors and give warnings for unsupported options.
    (when (member :initial-offset options :test 'option-equal)
      (error "~&Def-structure doesn't support the :initial-offset option."))

    ;; Add slots from an included structure to the beginning of the slot
    ;; descriptions list.

    (when included-structure?
      (let ((included-slots
              (def-structure-slot-descriptions included-structure?)))
        (unless (unique-structure-type-of-ab-name? included-structure?)
          (error "Structure ~a included in ~a is not defined!"
                 included-structure? type-name))
        (loop with included-descriptions-to-use = nil
              for slot-description in included-slots
              for slot-name = (if (consp slot-description)
                                  (car slot-description)
                                  slot-description)
              for description-to-use
              = (loop for override in overriding-include-slot-descriptions
                      do
                  (when (or (eq slot-name override)
                            (and (consp override)
                                 (eq slot-name (car override))))
                    (return override))
                      finally (return slot-description))
              do
          (push (cond ((symbolp description-to-use)
                       `(,description-to-use nil
                                             :no-accessor t :initialize-on-recycle nil))
                      ((second (memq :no-accessor (cddr description-to-use)))
                       description-to-use)
                      (t
                       (append description-to-use (list :no-accessor t))))
                included-descriptions-to-use)
              finally
                (setq slot-descriptions
                      (append (nreverse included-descriptions-to-use)
                              slot-descriptions)))))

    ;; Collect the lists associated with slots in the structure.

    (loop for slot-description in slot-descriptions
          for defstruct-options = nil
          do
      (cond ((symbolp slot-description)
             (push slot-description
                   defstruct-slot-descriptors))
            ((consp slot-description)
             (if (not (consp (cdr slot-description)))
                 (error "~&Def-structure slot descriptor should be a symbol, or~%~
                         have an initialization if it is a list.~%~
                         Bad descriptor: ~A"
                        slot-description))
             (if (memq (first slot-description) user-argument-list)
                 (if (not (null (second slot-description)))
                     (warn "~&Def-structure ~A slot initialization for ~A~%~
                            will not ever be performed, since this slot is in the~%~
                            argument list for the constructor."
                           type-name (first slot-description)))
                 (push (list (first slot-description) (second slot-description))
                       slot-initializations))
             (loop for option = (cddr slot-description) then (cddr option)
                   until (endp option)
                   do
               (if (not (consp (cdr option)))
                   (error
                     "~&Def-structure ~A had a slot description with an odd number of ~
                      arguments.~%~
                      Offending description: ~A"
                     type-name slot-description))
               (case (first option)
                 ;; Reclaimer gives the symbol name for the reclaimer macro.
                 ((:reclaimer)
                  (If (not (symbolp (second option)))
                      (error "~&In def-structure for ~A, :reclaimer slot option requires an ~
                              unquoted symbol.~%~
                              Offending slot description: ~A"
                             type-name slot-description))
                  (push (list (first slot-description) (second option))
                        slot-reclaimers))
                 ;; Initialize-on-recycle, when null, means only eval this form
                 ;; when creating a new structure, but don't touch the slot
                 ;; when recycling.
                 ((:initialize-on-recycle)
                  (cond ((and (null (second option))
                              (eq (first slot-description)
                                  (first (first slot-initializations))))
                         (push (first slot-initializations)
                               initializations-on-creation-only)
                         (setq slot-initializations (cdr slot-initializations)))))
                 ;; The following are the CLtL slot options supported by
                 ;; def-structure (this happens to be the whole list of slot
                 ;; options for defstruct).  We also support our own option,
                 ;; called :no-accessor.
                 ((:read-only :type :no-accessor)
                  (setq defstruct-options
                        (append defstruct-options
                                (list (first option) (second option)))))
                 (t
                  (error "~&In def-structure ~A, slot option ~A is not defined.~%~
                          Slot description: ~A"
                         type-name (first slot-description) slot-description))))
             (if (null defstruct-options)
                 (push (first slot-description)
                       defstruct-slot-descriptors)
                 (push (cons (first slot-description)
                             (cons nil defstruct-options))
                       defstruct-slot-descriptors)))
            (t
             (error "~&Weird def-structure slot description in ~A, it's not a symbol ~
                     or a list.~%~
                     Slot description: ~A"
                    type-name slot-description))))

    ;; Reverse what was gathered above so that it is back in forward order.

    (setq defstruct-slot-descriptors (nreverse defstruct-slot-descriptors)
          slot-initializations (nreverse slot-initializations)
          initializations-on-creation-only (nreverse initializations-on-creation-only)
          slot-reclaimers (nreverse slot-reclaimers))

    (let ((compile-time-type-description (build-type-description)))
      ;; This type description has only knowledge lexically apparent
      ;; from the def-structure in it.  See Load-and-initialize-type-description
      ;; for critcal other done at load time to stitch this into the
      ;; existing type system.
      (setf (name-of-type-description compile-time-type-description)
            type-name)
      (setf (inheritance-path-of-type-description compile-time-type-description)
            (list* type-name
                   (if (null included-structure?)
                       (list superior-type)
                       (copy-list
                         (inheritance-path-of-type-description
                           (type-description-of-type included-structure?))))))
      (setf (direct-superiors-of-type-description compile-time-type-description)
            (list superior-type))
      (setf (direct-inferiors-of-type-description compile-time-type-description)
            nil) ;; Maybe reset at load time from existing value.
      #+development
      (setf (slot-descriptions-of-type-description compile-time-type-description)
            slot-descriptions) ;; Different from class slot descriptions!
      ;; direct-slots-of-type-description -- TBD
      (setf (method-table-of-type-description compile-time-type-description)
            nil) ;; Reset at load time, maybe from existing value.
      (setf (alist-of-type-description compile-time-type-description)
            (list*
              #+development raw-defining-form
              (loop for option in options
                    collect (if (consp option) option (list option)))))
      ;; flags-of-type-description -- default is all false.
      (setf (instance-length-of-type-description compile-time-type-description)
            ;; Is this perfectly in synch with "force-named?"
            (+ (length slot-descriptions) (if named? 1 0)))
      ;; serial-number-of-type-description -- TBD
      ;; subtype-p-bit-vector-of-type-description -- TBD!


    `(progn
       #+meter-init-memory
       (setq before-structure-init (g2-memory-usage))

       ;; Inline the more primitive defstruct
       (defstruct-g2
           (,@(remove-entry-given-car
                :constructor
                (remove-entry-given-car
                  :reclaimer
                  (remove-entry-given-car
                    :include
                    (remove-entry-given-car
                      :creations-at-a-time
                      (remove-entry-given-car
                        :copier
                        type-or-type-with-options)))))
              (:constructor ,constructor-name nil))
         ,@defstruct-slot-descriptors)

       ;; Create the type description, hang off the three places we keep it.
       (eval-when (:compile-toplevel :load-toplevel :execute)
         (defvar-of-special-global ,type-description-var-name nil)
         (setf ,type-description-var-name
           (load-and-initialize-type-description
             ,type-description-var-name
             (copy-optimized-constant ',compile-time-type-description)))
         (setf (type-description-of-unique-type-name-of-gensym-structure
                 ',unique-type-name)
               ,type-description-var-name)
         (setf (type-description-of-type ',type-name)
               ,type-description-var-name))

       ;; Tell the development environment about us.
       #+development
       (register-definition ',type-name 'def-structure)

       ;;  Setup the pool.
       ,@(when user-reclaimer-name?
           `((def-system-object-pool ,type-name structure
               ,created-object-count nil ,outstanding-object-function
               ,object-memory-usage)

             (def-system-variable ,chain-of-available-objects utilities2 nil nil t)
             (def-system-variable ,created-object-count utilities2 0 nil t)

             #+SymScale
             (defvar-of-special-global ,chain-of-available-objects-vector
               (make-thread-array nil))

             (defun-simple ,object-memory-usage ()
               (declare (eliminate-for-gsi))
               (*f ,created-object-count
                   ,(if (eq type? 'list)
                        `(*f (bytes-per-cons)
                             ,(+f (length slot-descriptions)
                                  (if named? 1 0)))
                        `(bytes-per-simple-vector
                           ,(+f (length slot-descriptions)
                                (if named? 1 0))))))

             ;; Make an accessor that will be used to chain structures together, and a
             ;; function for creation of the structures in a permanent context.

             (defmacro ,chain-slot (,structure-arg)
               ,(if (eq type? 'list)
                    `(list 'car ,structure-arg)
                    `(list 'svref ,structure-arg 0)))

             ;; Make an outstanding object count function.
             ;; TODO: count on the per-thread pools. --binghe
             (defun-simple ,outstanding-object-function ()
               (declare (eliminate-for-gsi))
               (-f ,created-object-count
                   (loop for ,structure-var
                             = ,chain-of-available-objects
                             then (,chain-slot ,structure-var)
                         for count = 0 then (+f count 1)
                         until (null ,structure-var)
                         finally (return count))))

             ;; Make the reclaimer substitution macro.  If this is a named
             ;; structure, put in a data corruption check by making sure the chain
             ;; slot of the thing being given back still contains the name of this
             ;; structure type.  If it does not, this thing has been given back
             ;; already or munged in some other way not given the def-structure
             ;; stamp of approval.

             (def-substitution-macro ,user-reclaimer-macro? (,structure-arg)
               ,@(if named?
                     #+development
                     `((if (neq (,chain-slot ,structure-arg) ',unique-type-name)
                           (error
                             "Structure reclaimed is not of expected type ~A"
                             ',type-name)))
                     #-development
                     nil
                     nil)
               (note-reclaim-cons ,structure-arg nil)
               ,@(when slot-reclaimers
                   ;; SymScale notes: here we made a big change. Old code:
                   ;; 
                   ;; (let ((old-structure-being-reclaimed structure-being-reclaimed))
                   ;;   (setq structure-being-reclaimed ,structure-arg)
                   ;;   ...
                   ;;   (setq structure-being-reclaimed old-structure-being-reclaimed))
                   ;;
                   ;; New code:
                   ;;
                   ;; (let ((structure-being-reclaimed ,structure-arg))
                   ;;   ...)
                   ;;
                   ;; This is because in multi-threading environment, there're multiple reclaimers
                   ;; being called at the same time but for different structures. A single global
                   ;; variable (structure-being-reclaimed) is not enough. Instead, we must specially
                   ;; bind it to make it into a thread-specific (TLS) variable.
                   ;;
                   ;;                                             -- Chun Tian (binghe), 2009/10/15
                   `((let (#+SymScale (structure-being-reclaimed ,structure-arg)
                           #-SymScale (old-structure-being-reclaimed structure-being-reclaimed))
                       #-SymScale
                       (setq structure-being-reclaimed ,structure-arg)
                       ,@(loop for slot-reclaimer in slot-reclaimers
                               nconcing
                               `((,(second slot-reclaimer)
                                   (,(first slot-reclaimer) ,structure-arg))
                                 (setf (,(first slot-reclaimer)
                                         ,structure-arg)
                                       nil)))
                       #-SymScale
                       (setq structure-being-reclaimed old-structure-being-reclaimed))))
                 (setf (,chain-slot ,structure-arg)
                       #-SymScale ,chain-of-available-objects
                       #+SymScale (svref ,chain-of-available-objects-vector current-thread-index))
                 (setf #-SymScale ,chain-of-available-objects
                       #+SymScale (svref ,chain-of-available-objects-vector current-thread-index)
                       ,structure-arg)
               nil)

             (defun-simple ,user-reclaimer-actual-name? (,structure-arg)
               (,user-reclaimer-macro? ,structure-arg))

             (defmacro ,user-reclaimer-name? (,structure-arg)
               `(,',user-reclaimer-actual-name? ,,structure-arg))

             ,@(unless (eval-feature :no-macros)
                 `((note-non-resumable-function-call-macro ',user-reclaimer-name?)))

             (def-structure-method reclaim-structure (,type-name)
                   (,user-reclaimer-name? ,type-name))

       )) ; ,@(when user-reclaimer-name? ...)

       ;; Make the constructor for the creation of a new, permanently allocated
       ;; structure.  Note that as long as the memory meter functions are not
       ;; declared side-effect free, this function may be declared to be
       ;; side-effect free.

       (declare-side-effect-free-function ,permanent-name)

       (defun-simple ,permanent-name ()
         (let (,structure-var)
           ,@(when user-reclaimer-name?
                   `((atomic-incff
                      ,created-object-count ,creation-count)))
           (,(if (eq type? 'list)
                 'with-permanent-cons-creation
                 'with-permanent-array-creation)
             ,(if (and (null initializations-on-creation-only)
                       (=f creation-count 1))
                  `(setq ,structure-var (,constructor-name))
                  `(loop for ,constructor-count-var from 1 do
                         (setq ,structure-var (,constructor-name))
                         ,@(loop for slot-init in initializations-on-creation-only
                                 collect
                                 `(setf (,(first slot-init) ,structure-var)
                                        ,(second slot-init)))
                         (when (>=f ,constructor-count-var ,creation-count)
                           (loop-finish))
                         (setf (,chain-slot ,structure-var)
                               #-SymScale ,chain-of-available-objects
                               #+SymScale (svref ,chain-of-available-objects-vector current-thread-index))
                         (setf #-SymScale ,chain-of-available-objects
                               #+SymScale (svref ,chain-of-available-objects-vector current-thread-index)
                               ,structure-var))))
                  ;;                 `(let ((,structure-var (,constructor-name)))
                  ;;                    ,@(loop for slot-init in initializations-on-creation-only
                  ;;                            collect
                  ;;                              `(setf (,(first slot-init) ,structure-var)
                  ;;                                     ,(second slot-init)))
                  ;;                    ,structure-var)
           ,structure-var))

       #+in-progress
       (when user-copier-name
         `(defun ,user-copier-name (,type-name)
            (let ((,new-type-name ))
              (setf ,@(loop for slot-description in slot-descriptions
                            as slot-name = (car-or-atom slot-description)
                            collect `(slot-name ,type-name)
                            collect `(slot-name ,type-name))))))


       ;; Make the constructor macro for the user.
       ;; SymScale notes: use of this macro must be protected by current structure lock --binghe
       (defmacro ,user-constructor-macro ,user-argument-list
         `(let ((,',structure-var
                     ,',(if user-reclaimer-name?
                            #-SymScale chain-of-available-objects
                            #+SymScale `(svref ,chain-of-available-objects-vector current-thread-index)
                            `(,permanent-name))))
            ,',(when user-reclaimer-name?
                     `(cond (,structure-var
                             (setf #-SymScale ,chain-of-available-objects
                                   #+SymScale (svref ,chain-of-available-objects-vector current-thread-index)
                                   (,chain-slot ,structure-var))
                             ,@(when named?
                                     `((setf (,chain-slot ,structure-var)
                                             ',unique-type-name))))
                            (t
                             (setq ,structure-var (,permanent-name)))))
            (note-allocate-cons ,',structure-var nil)
            ;; Set the slots initialized by macro arguments.
            ,,@(loop for argument in user-argument-list
                     collect
                     ``(setf (,',argument ,',structure-var)
                             ,,argument))
            ;; Set the remaining slots to their slot initializations.
;            ,',@(loop for slot-init in slot-initializations
;                      collect
;                      `(setf (,(first slot-init) ,structure-var)
;                             ,(second slot-init)))
            ,,@(loop for slot-init in slot-initializations
                     collect
                     ``(setf (,',(first slot-init) ,',structure-var)
                             ,',(second slot-init))) ;make sure same semantics!!
                                        ; Not evalling initform at compile time  -dkuznick, 8/19/99
            ;; Return the initialized object.
            ,',structure-var))

       ,@(unless (eval-feature :no-macros)
           `((note-non-resumable-function-call-macro
               ',user-constructor-macro
               ',user-constructor-name)))

       ;; Define the constructor function for the user.  As long as the memory
       ;; metering functions are not declared to be side-effect free, then the
       ;; constructor can be side-effect-free.

       (declare-side-effect-free-function ,user-constructor-actual-name)

       (defun-simple ,user-constructor-actual-name ,user-argument-list
         (,user-constructor-macro ,@user-argument-list))

       (defmacro ,user-constructor-name ,user-argument-list
         (list ',user-constructor-actual-name ,@user-argument-list))

       ;; If we are in a macro compile, emit the slot-descriptions for this
       ;; structure, and the included structure info.
       ,@(unless (eval-feature :no-macros)
                 `((eval-when (:compile-toplevel :load-toplevel :execute)
                     (setf (def-structure-slot-descriptions ',type-name)
                           ',slot-descriptions))))


       ;; Structure-reclaimed-p is a development only predicate that tells you
       ;; if the given thing is in the list of reclaimed structures for that
       ;; type.

       #+development
       ,@(if user-reclaimer-name?
             `((defun-simple ,structure-reclaimed-p (thing)
                 (loop for reclaimed-structure
                       = ,chain-of-available-objects
                       then (,chain-slot reclaimed-structure)
                       until (null reclaimed-structure)
                       do
                   (if (eq thing reclaimed-structure)
                       (return t))
                       finally
                         (return nil))))
             nil)
       #+meter-init-memory
       (setq structure-memory
             (+f structure-memory (-f (g2-memory-usage) before-structure-init)))

       ;; Finally, return the name of the structure.
       ',type-name))))

#+(and lispworks development)
(lw:defadvice (def-structure def-structure-record-definition :around)
    (call environment)
  (let ((structure-name (car-or-atom (second call))))
    (cond
      (structure-name
       `(dspec:def (def-structure ,structure-name)
            (progn
              (dspec::record-definition `(def-structure ,',structure-name)
                                        (dspec:location))
              ,(lw:call-next-advice call environment))))
      (t     
       (lw:call-next-advice call environment)))))


;;; `Load-and-initialize-type-description' is called at compile and load time to
;;; create a type description.  It takes two parameters:
;;; old-type-description? and new-type-description.

;;; The type-description-being-loaded is a precursor of the type description
;;; desired.  It contains only that information that is lexically apparent from
;;; the def-structure.  It contains symbols rather than pointers in a number of
;;; it's fields.  It is missing some fields that this routine will fill in
;;; for it.

;;; If old-type-description? is NIL then we are doing a load or
;;; compile from scratch.  Otherwise we are doing a reload, in which
;;; case we want to keep a lot of info taken from old-type-description?

;;; First we clean up the loaded-type-description.  For example we take the
;;; list of superior type names, and replace them with pointers to the
;;; superior type descriptions.

;;; We initialize a number of other fields, defaulting them from the old
;;; type description if possible.

;;; Finally, if we have an old type description, we copy the slots from
;;; the new to the old, so that pointer to the old will remain useful.

;;; We then return the type description so it can be assigned to the
;;; various places that "own" it.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defun load-and-initialize-type-description (old-type-description?
                                                new-type-description)
    ;; Bind things in the new-type-description.
    ;; Nothing to bind at this time

    ;; Initialize things in the new-type-description.

    (let* ((new-superior-type (second
                                 (inheritance-path-of-type-description
                                   new-type-description)))
           (new-superior-type? (if (eq t new-superior-type)
                                   nil
                                   new-superior-type))
           (new-superior-type-description?
             (if new-superior-type?
                 (type-description-of-type new-superior-type))))

      ;; The Method table is taken from the old one if possible, and otherwise from
      ;; the superior type's, and if all else fails we just make an empty one.
      (let ((new-dispatch-table
              (cond
                ((and old-type-description?
                      (eq new-superior-type?
                          (second
                            (inheritance-path-of-type-description
                              old-type-description?))))
                 (method-table-of-type-description old-type-description?))
                (new-superior-type?
                 (make-structure-method-table
                   (method-table-of-type-description
                     new-superior-type-description?)))
                (t
                 (make-structure-method-table nil)))))
        (setf (superior-dispatch-table new-dispatch-table)
              (method-table-of-type-description
                     (type-description-of-type new-superior-type)))
        (setf (method-table-of-type-description new-type-description)
              new-dispatch-table))

      ;; Hang us off our superior.
      (when new-superior-type-description?
        (pushnew
          (name-of-type-description new-type-description)
          (direct-inferiors-of-type-description new-superior-type-description?)))

      ;; Maintain our inferiors, if possible.
      (when old-type-description?
        (setf (direct-inferiors-of-type-description new-type-description)
              (direct-inferiors-of-type-description old-type-description?))))

    (cond
      ;; We really want to return the old type description,
      ;; so copy over our new and improved type description
      ;; and do so.
      (old-type-description?
       (loop for i from 1 below (length-of-simple-vector old-type-description?)
             do (setf (svref old-type-description? i)
                      (svref new-type-description i)))
       old-type-description?)
      ;; Return the new one.
      (t
         new-type-description)))

)



;;; The `reclaim-structure' method will reclaim an instance of any structure.
;;; The methods for this are automaticly generated by def-structure.

(def-generic-structure-method reclaim-structure (named-gensym-structure))




;;; `Reclaim-structure-if-any' takes nil or a structure instance.  Given a
;;; structure instance it reclaims it as if by reclaim-structure.

(defun-void reclaim-structure-if-any (structure?)
  (when structure?
    (reclaim-structure structure?)))


;;; The function `reclaim-if-structure' reclaims thing if it is a named gensym
;;; structure.

(defun-void reclaim-if-structure (thing?)
  (when (allocated-named-gensym-structure-p thing?)
    (reclaim-structure thing?)))



;;; The `clean-up-structure' does any cleanups needed prior to reclaiming the
;;; structure itself.

(def-generic-structure-method clean-up-structure (named-gensym-structure))


(defun-void clean-up-and-reclaim-structure (structure)
  (clean-up-structure structure)
  (reclaim-structure structure))



;;; `named-gensym-structure' is the superior gensym structure type of all structures types
;;; in G2.

(def-structure (named-gensym-structure (:include nil))
;  (unique-type-name-of-gensym-structure)
  ;; Not possible due to entangle ments with Lispm named structures
  )


(defmacro unique-type-name-of-gensym-structure (named-gensym-structure)
  `(g2-type-name-of-named-simple-vector ,named-gensym-structure))


;;; `Type-description' the actual structure defintition for type description
;;; may be defined at this point.

(def-structure (type-description
                 (:print-function print-type-description)
                 (:creations-at-a-time 20)
                 (:eliminate-for-products gsi))
  (name-of-type-description nil :no-accessor t)

  ;; Subtype Lattice.
  ;; These are all lists of type names
  (inheritance-path-of-type-description nil :no-accessor t)
  (direct-superiors-of-type-description nil :no-accessor t)
  (direct-inferiors-of-type-description nil :no-accessor t)

  ;; Slots.
  (slot-descriptions-of-type-description nil :no-accessor t)
  (direct-slots-of-type-description nil :no-accessor t) ;; a list of slot names
  (performance-hack-for-slot-of-type-description-tbd nil :no-accessor t)  ;; Unused.

  ;; Methods.
  (direct-methods-of-type-description nil :no-accessor t)
  (method-table-of-type-description (make-array 10) :no-accessor t)

  ;; Other.
  (alist-of-type-description nil :no-accessor t)
  (flags-of-type-description nil :no-accessor t)
  (instance-length-of-type-description 0 :no-accessor t)
  (user-vector-length-of-type-description 0 :no-accessor t)
  (subclass-of-item-for-type-description 0 :no-accessor t)

  ;; Subtypep implementation
  (serial-number-of-type-description 0 :no-accessor t)
  (subtype-p-bit-vector-of-type-description nil :no-accessor t))

(defun print-type-description (type-description stream depth)
  (declare (ignore depth) (eliminate-for-gsi))
  (printing-random-object (type-description stream)
    (format stream "~a ~a"
            (name-of-type-description (type-description-of type-description))
            (name-of-type-description type-description))))


(defun type-name-of (thing)
  (let ((description? (type-description-of thing)))
    (when description?
      (name-of-type-description
        description?))))



;;; `Outline-type-descriptions' shows an outline of the type description
;;; instances that are inferiors of the the type or type description given
;;; as it's arguement.

#+development
(defun outline-type-description (type-or-type-description
                                  &key
                                  ((:print-length *print-length*) 10)
                                  ((:print-level *print-level*) 4))
  (when (symbolp type-or-type-description)
    (setf type-or-type-description
          (type-description-of-type type-or-type-description)))
  (unless (type-description-p type-or-type-description)
    (error "Huh?"))
    (outline-tree-of-nodes
      #'(lambda (type-or-type-description)
          (if (symbolp type-or-type-description)
              nil
              (loop for type in (direct-inferiors-of-type-description type-or-type-description)
                    collect (or (type-description-of-type type)
                                type))))
      type-or-type-description
      0
      (cons nil nil)
      #'(lambda (node) (declare (ignore node)) t) ;; visible-p
      ))



;;; `Structure-type-p' takes an instance and a structure's ab type name and
;;; returns t or nil to indicate if the structure is an instance of that type.
;;; Note that this provides a work around for the bug that
;;; <structure-type>-p only checks that the instance is exactly that type.

(defun-simple structure-type-p (named-gensym-structure type)
  (let ((type-description-of-type (type-description-of-type type))
        (type-description-of-instance (type-description-of named-gensym-structure)))
    (or (eql type-description-of-instance type-description-of-type)
        (subtype-p-using-type-descriptions
          type-description-of-instance
          type-description-of-type))))




;;; The macro `define-structure' allows conc-name and constructs printers for you.
;;; It can define either static or managed structures.  The allowed options are:
;;;      (:conc-name value)   -- defaults to NIL.
;;;      (:managed value)     -- defaults to T if there are superclasses (?)
;;;      (:constructor name args) -- defines the constructor, as in def-structure.
;;;      (:constructor t)         -- defines a constructor which takes all of the
;;;                                  slots as positionl arguments.
;;;   Other def-structure otpions.

(defmacro define-structure (class-name superclasses &body slots)
  (let ((options (loop while (and (consp (car slots))
                                  (keywordp (caar slots)))
                       collect (pop slots))))
    (flet ((getopt (option-name)
             (loop for option in options
                   when (eq (car option) option-name)
                     do (return option))))

      (let ((conc-name (if (eq (cadr (getopt :conc-name)) t)
                           class-name
                           (cadr (getopt :conc-name)))))
        (flet ((conc-name (original-name)
                 (if conc-name
                     (build-ab-symbol conc-name original-name)
                     original-name)))

          (let* ((printer-name (cadr (getopt :print-function)))
                 (managed (if superclasses t (getopt :managed))) ; Always managed if has superclass.

                 (the-name-slot nil)
                 (new-slots (loop for slot in slots
                                  for slot-name = (if (atom slot) slot (car slot))
                                  for conced-name = (conc-name slot-name)
                                  if (or (eq slot-name 'name)
                                         (and (eq slot (car slots))
                                              (>= (length (string slot-name)) 5)
                                              (string-equal (string slot-name) "-NAME"
                                                            :start1 (- (length (string slot-name)) 5))))
                                         do (setq the-name-slot conced-name)
                                  collect (if (consp slot) (cons conced-name (cdr slot)) conced-name)))

                 (constructor-option (cdr (getopt :constructor)))
                 (constructor (cond ((null constructor-option)
                                     (list (build-ab-symbol "make" class-name)))
                                    ((and managed
                                          (eq (first constructor-option) t))
                                     (list (build-ab-symbol "make" class-name)
                                           (mapcar #'car-or-atom new-slots)))
                                    (t
                                     (list (first constructor-option)
                                           (mapcar #'conc-name (second constructor-option))))))

                 (printer (when (and (eval-feature :development)
                                     the-name-slot
                                     (null printer-name))
                            (setq printer-name (build-ab-symbol "print" class-name))
                            `(defun ,printer-name (,class-name stream depth)
                               (declare (ignore depth))
                               (printing-random-object (,class-name stream)
                                 (format stream "~s ~s" ',class-name (,the-name-slot ,class-name))))))
                 (remaining-options
                   (loop for option in options
                         unless (memq (first option) '(:conc-name :print-function :constructor :managed))
                           collect option)))

            `(progn
               (,(if managed 'def-structure 'defstruct-g2)
                 (,class-name
                    ,@(when constructor `((:constructor ,@constructor)))
                    ,@(when superclasses `((:include ,@superclasses)))
                    ,@(when printer-name `((:print-function ,printer-name)))
                    ,@remaining-options)
                 ,@new-slots)
               ,@(when printer `(,printer))
               ',class-name)))))))



;;;; Describing and Printing Gensym Structures




;;; The function `print-gensym-structure' prints a gensym named structure.

#+development
(def-development-printer print-gensym-structure (gensym-structure stream)
  (when (allocated-named-gensym-structure-p gensym-structure)
    (let* ((type (g2-type-name-of-named-simple-vector gensym-structure))
           (printer? (gensym-structure-printer? type))
           (friendly-type-name (if (eql (symbol-package type)
                                        the-g2-defstruct-package)
                                   (ab-name-of-unique-structure-type type)
                                   type)))
      (if printer?
          (funcall printer? gensym-structure stream 0)
          (printing-random-object (gensym-structure stream)
            (format stream "~a" friendly-type-name)))
      gensym-structure)))


#+development
(def-development-describer describe-gensym-structure (structure)
  (when (allocated-named-gensym-structure-p structure)
    (describe-structure structure)
    structure))



;;; The function `describe-structure' is a development only printer which shows
;;; the contents of Gensym structure instances along with their slot names.

#+development
(defun describe-structure (named-gensym-structure)
  (cond
    ((allocated-named-gensym-structure-p named-gensym-structure)
     ;; There might not be a type-description (for raw defstruct-g2 thingies).
     (let* ((raw-name (g2-type-name-of-named-simple-vector named-gensym-structure))
            (type-description? (type-description-of-unique-type-name-of-gensym-structure raw-name))
            (type-name (if type-description?
                           (name-of-type-description type-description?)
                           raw-name))
            (slots (if type-description?
                       (slot-descriptions-of-type-description type-description?)
                       (slot-names-in-gensym-structure raw-name))))

       (loop for slot-name-or-description in slots
             as slot-name = (if (symbolp slot-name-or-description)
                                slot-name-or-description
                                (car slot-name-or-description))
             as i from 1
             initially
               (format t "~&~a is a Gensym structure of type ~a"
                       named-gensym-structure
                       (symbol-name type-name))
             do (cond
                  ((and (eq type-name 'icp-buffer)
                        (eq slot-name 'icp-buffer-vector))
                   (format t "~& [~a] ~vT~(~a~)" i 7 slot-name)
                   (funcall 'print-icp-buffer-contents named-gensym-structure))
                  ((and (eq type-name 'category-set)
                        (eq slot-name 'category-vector))
                   (describe-slot-in-frame-or-structure
                     i nil slot-name (svref named-gensym-structure i)
                     :printer 'print-indices-of-bits-in-category-vector))
                  (t
                   (describe-slot-in-frame-or-structure
                     i nil slot-name (svref named-gensym-structure i)))))))

    ((simple-vector-p named-gensym-structure)
     (format
       t "~&~a is an unallocated or unnamed Gensym structure ~a elements long."
       named-gensym-structure (length named-gensym-structure))
     (loop for i from 0 below (length named-gensym-structure)
           do
       (format
         t "~% [~d] ~v,,,'.a.. ~s"
         i (max 0 (- 15 (floor (log (max 1 i) 10)))) ""
         (svref named-gensym-structure i))))
    (t
     (format t "~&~a is not a Gensym structure." named-gensym-structure)))
  named-gensym-structure)

#+development
(defun describe-type-description (desc)
  (format t "~a is a Gensym structure of type ~a~%" desc 'type-description)
  (format t "Name:             ~:s~%" (name-of-type-description desc))
  (format t "Inheritance Path: ~:s~%" (inheritance-path-of-type-description desc))
  (format t "Direct Superiors: ~:s~%" (direct-superiors-of-type-description desc))
  (format t "Direct Inferiors: ~:s~%" (direct-inferiors-of-type-description desc))
  (format t "Slots:           ~{~<~%                 ~:; ~A~>~^,~}~%"
          (mapcar 'car-or-atom (slot-descriptions-of-type-description desc)))
  desc)



;; This should be made available for all situations in which Gensym personnel may
;; be performing on-line debugging!!!  Mark David worries about having too much
;; stuff be in delivery code, so maybe another feature is necessary which is
;; used to compile code to be used here at Gensym, or at least for Pre-release
;; compiles.  -jra 1/16/89






;;;; Array Pools




;;; The macro `def-vector-pool' defines a pool of simple vectors of a given
;;; size.  Its options are :element-type, :initial-element, and
;;; :initialize-on-recycle, and :unmoveable.  The :element-type option specifies
;;; an unquoted type for the elements of the vector.  The :initial-element
;;; option specifies a value that elements of the vector will be initialized to.
;;; If no :initial-element option is specified, the array elements are not
;;; initialized and the contents are undefined.  The :initialize-on-recycle
;;; option controls whether the elements of a vector are re-initialized when a
;;; vector is recycled, and it defaults to T.  The :unmoveable option controls
;;; whether the vector is allocated such that its address remains constant, or
;;; whether it may be moved by a garbage collector.  Data structures handed over
;;; to the operating system may need this property, particularly in the
;;; networking code on VAXes and other conventional architectures.  By default
;;; this option is NIL.

;;; This macro defines three macros for the user.  The first, called MAKE-name,
;;; takes no arguments and allocates an instance of the described vector.  The
;;; second, called RECLAIM-name, takes a vector as its argument and returns that
;;; vector back to the pool.  The third, called AREF-name, takes a vector from
;;; this pool and a fixnum index and accesses that element in the most efficient
;;; manner possible, i.e., the reference is wrapped with the appropriate type
;;; declarations for the type of array and element.  SETF on the AREF-name
;;; accessor mutates vector elements.  Meters are defined for this pool and
;;; entered into the system object pool metering facility as
;;; name-length-VECTORS.

;;; This facility uses vector pool conses to string together lists of available
;;; vectors.

;;; Note that on the Texas Instruments 2.1 release machines, there is a bug in
;;; the creation of arrays element-typed as short-floats.  If an array is given
;;; this element type, it will instead create an array of type float.  Any short
;;; floats stored into this array will then be coerced into type float, and on
;;; removal from the array will be boxed as floats.  This is unacceptable, since
;;; the new float conses and will cause other arithmetic performed with it to
;;; modify all short floats into floats through type contagion.  Therefor, on
;;; the TI, any arrays typed as short-float will instead be made type T.  Note
;;; that if you want to store short floats, you really should be using managed
;;; numbers anyway.  See store-managed-number.  -jra 12/8/87

;; This could really be defined with a simple conser facility, since I'm only
;; using vector-pool-cons-macro and reclaim-vector-pool-cons-macro from
;; everything defined in this conser.  -jra 12/2/87

(defconser vector-pool utilities2)



;;; The macro `initialize-vector-pool-vector' takes as arguments forms that give
;;; a vector, the length of the vector, an initial element to store into all
;;; elements of the vector, and the prefered accessor name for the vector.  It
;;; will do its best to produce code that optimally initializes all elements of
;;; the vector to the given value.  For some implementations the speedup over a
;;; simple loop is substantial.

;;; On the Symbolics, this expands into a loop using the sys:array-register
;;; declaration.  On the TI we will use a supplied function called
;;; array-initialize.  On the Lucid system, we will be forced into a
;;; loop, using the given accessor to speed the individual references.  This has
;;; been tested in Lucid 2.1.3, and the loop below is 5 times faster than
;;; calling the FILL Common Lisp function.  -jra 3/23/89

(defmacro initialize-vector-pool-vector
          (vector-form length-form initial-element-form accessor-name)
  (let ((vector (gensym))
        (length (gensym))
        (initial-element (gensym)))
    `(let ((,vector ,vector-form)
           (,length ,length-form)
           (,initial-element ,initial-element-form))
       (declare (type fixnum ,length))
       (loop for index from 0 below ,length
             do
         (setf (,accessor-name ,vector index) ,initial-element))
       ,vector)))




(defmacro def-vector-pool (name length &rest options)
  (if (not (symbolp name))
      (error "Def-vector-pool must have a symbol as its pool name.  Bad name: ~A"
             name))
  (if (not (and (integerp length) (>= length 0)))
      (error "Def-vector-pool ~a must have an positive, integer length.  Bad length: ~a."
             name length))
  (let* ((pool-name
           (intern (format nil "~a-~a-VECTORS" name length)))
         (available-vectors
           (intern (format nil "AVAILABLE-~a-~a-VECTORS" name length)))
         #+SymScale
         (available-vectors-vector
           (intern (format nil "AVAILABLE-~a-~a-VECTORS-VECTOR" name length)))
         (vector-count
           (intern (format nil "COUNT-OF-~a-~a-VECTORS" name length)))
         (outstanding-vector-count
           (intern (format nil "OUT-~a-~a-VECTORS" name length)))
         (vector-memory-usage
           (intern (format nil "~a-~a-VECTOR-MEMORY-USAGE" name length)))
         (vector-accessor
           (intern (format nil "AREF-~a" name)))
         (permanent-constructor-name
           (intern (format nil "MAKE-PERMANENT-~a-~a-VECTOR-INTERNAL" name length)))
         (constructor-name
           (intern (format nil "MAKE-~a" name)))
         (constructor-macro
           (intern (format nil "~a-MACRO" constructor-name)))
         (reclaimer-name
           (intern (format nil "RECLAIM-~a" name)))
         (reclaimer-macro
           (intern (format nil "~a-MACRO" reclaimer-name)))
         (vector-variable
           (intern (format nil "~a-~a-VECTOR" name length)))
         (element-type t)
         (no-value (gensym))
         (initial-element no-value)
         (initialize-on-recycle t)
         (unmoveable? nil))

    ;; Process the options.

    (loop for option-list on options by 'cddr
          do
      (if (not (consp (cdr option-list)))
          (error "Def-vector-pool options must be in option/value pairs.~%~
                  Bad option list: ~a"
                 options))
      (case (car option-list)
        ((:element-type)
         (setq element-type (second option-list)))
        ((:initial-element)
         (setq initial-element (second option-list)))
        ((:initialize-on-recycle)
         (setq initialize-on-recycle (second option-list)))
        ((:unmoveable)
         (setq unmoveable? (second option-list)))
        (t
          (error "Unknown option to def-vector-pool: ~a in options list ~a"
                 (first option-list)
                 options))))

    ;; Produce code.

    `(progn

       ;; Define system variables for holding the list of available vectors,
       ;; define the variables for memory pool metering, and define the pool.

       (def-system-variable ,available-vectors utilities2 nil nil t)
       (def-system-variable ,vector-count utilities2 0 nil t)

       #+SymScale ; per-thread pool
       (defvar-of-special-global ,available-vectors-vector
         (make-thread-array nil))

       (def-system-object-pool
         ,pool-name
         ,(if (eq element-type t)
              'simple-vector
              `(simple-array ,element-type (,length)))
         ,vector-count nil ,outstanding-vector-count ,vector-memory-usage)

       ;; Define the memory usage and outstanding vector count functions.
       (defun-simple ,vector-memory-usage ()
         (*f ,vector-count
             (bytes-per-typed-simple-array ,(if (eq element-type t)
						t
					      `',element-type)
					   ,length)))

       ;; TODO: count on the per-thread pools. --binghe
       (defun-simple ,outstanding-vector-count ()
         (-f ,vector-count (length (the list ,available-vectors))))

       ;; Define a function for creating a new instance of the vector pool.  The
       ;; contructor will be declared side-effect free, so the memory meters
       ;; must not be declared side-effect free.

       (declare-side-effect-free-function ,permanent-constructor-name)

       (defun-simple ,permanent-constructor-name ()
         (atomic-incff ,vector-count)
         (,(if unmoveable?
               'with-unmoveable-object-creation
               'with-permanent-array-creation)
           (make-static-array
             ,length
             ,@(if (not (eq element-type t))
                   `(:element-type ',element-type)
                   nil)
             ,@(if (not (eq initial-element no-value))
                   `(:initial-element ,initial-element)
                   nil))))

       ;; Define an accessor macro.

       (defmacro ,vector-accessor (vector index)
         ,(if (eq element-type t)
              ``(svref (the simple-vector ,vector)
                       (the fixnum ,index))
              ``(the ,',element-type
                     (aref (the (simple-array ,',element-type (,',length))
                                ,vector)
                           (the fixnum ,index)))))

       ;; Define the user creation macro.

       (defmacro ,constructor-macro ()
         `(progn
            (if #-SymScale ,',available-vectors
                #+SymScale (svref ,',available-vectors-vector current-thread-index)
                ,',(if (or (eq initial-element no-value)
                           (null initialize-on-recycle))
                       `(prog1
                          (car-of-cons #-SymScale ,available-vectors
                                       #+SymScale (svref ,available-vectors-vector
                                                         current-thread-index))
                          (setf #-SymScale ,available-vectors
                                #+SymScale (svref ,available-vectors-vector
                                                  current-thread-index)
                                (prog1
                                  (cdr-of-cons #-SymScale ,available-vectors
                                               #+SymScale (svref ,available-vectors-vector
                                                                 current-thread-index))
                                  (reclaim-vector-pool-cons-macro
                                    #-SymScale ,available-vectors
                                    #+SymScale
                                    (svref ,available-vectors-vector current-thread-index)))))
                       `(initialize-vector-pool-vector
                          (prog1
                            ;; this looks like a POP operation --binghe
                            (car-of-cons #-SymScale ,available-vectors
                                         #+SymScale (svref ,available-vectors-vector
                                                           current-thread-index))
                            (setf #-SymScale ,available-vectors
                                  #+SymScale (svref ,available-vectors-vector
                                                    current-thread-index)
                                  (prog1
                                    (cdr-of-cons #-SymScale ,available-vectors
                                                 #+SymScale (svref ,available-vectors-vector
                                                                   current-thread-index))
                                    (reclaim-vector-pool-cons-macro
                                      #-SymScale ,available-vectors
                                      #+SymScale
                                      (svref ,available-vectors-vector current-thread-index)))))
                          ,length
                          ,initial-element
                          ,vector-accessor))
                (,',permanent-constructor-name))))

       (declare-side-effect-free-function ,constructor-name)

       (defun-simple ,constructor-name ()
         (,constructor-macro))

       ;; Define the reclaimer macro.

       (defmacro ,reclaimer-macro (,vector-variable)
         `(progn
            ;; this looks like a PUSH operation --binghe
            (setf #-SymScale ,',available-vectors
                  #+SymScale (svref ,',available-vectors-vector current-thread-index)
                  (vector-pool-cons-macro
                    ,,vector-variable
                    #-SymScale ,',available-vectors
                    #+SymScale (svref ,',available-vectors-vector current-thread-index)))
            nil))

       (defun-simple ,reclaimer-name (,vector-variable)
         (,reclaimer-macro ,vector-variable))

       ;; Return the vector name from this defining form.

       ',name)))






;;;; Hash Numbers for Symbols




;;; The macro `sxhash-symbol' should be used for computing hash numbers of
;;; symbols.  This macro will be tuned to provide optimal performance an each
;;; implementation.  The macro `sxhash-compiled-function' is similar, but for
;;; compiled function objects.

#+translator
(tx::def-foreign-function (sxhash-symbol-1
                            (:name "SXHASH_SYMBOL_1")
                            (:return-type :fixnum-long))
    (symbol :object))

#-translator
(defun sxhash-symbol-1 (symbol)
  (sxhash symbol))

(defmacro sxhash-symbol (symbol)
  (if (and (eval-feature :chestnut-3)
           (eval-feature :chestnut-trans))
      `(logandf (sxhash-symbol-1 ,symbol) most-positive-fixnum)
      `(sxhash ,symbol)))

;;; Lisp objects passing into `sxhash-lisp-object' should be allocated under
;;; `with-unmoveable-object-creation' (or `with-permanent-allocation').

#-translator
(defun sxhash-lisp-object-1 (object)
  #+(and development lispworks)
  (unless (sys:staticp object)
    (cerror "Continue"
	    "Lisp object ~A is not in static area, pointer address may have changed."
	    object))
  (logandf (%pointer object) most-positive-fixnum))

;;; `sxhash-lisp-object' is used in various hash-tables in which the key is a normal
;;; lisp object (mostly KB frames).

(defmacro sxhash-lisp-object (object)
  (if (and (eval-feature :chestnut-3)
           (eval-feature :chestnut-trans))
      `(logandf (sxhash-symbol-1 ,object) most-positive-fixnum)
    `(sxhash-lisp-object-1 ,object)))

(defmacro sxhash-compiled-function (compiled-function)
  (if (and (eval-feature :chestnut-3)
           (eval-feature :chestnut-trans))
      ;; The symbol stuff works on compiled-functions too within Chestnut.  -jra
      ;; 10/17/96
      `(sxhash-symbol ,compiled-function)
      `(sxhash ,compiled-function)))


;; In Chestnut the pointer to the symbol can be used as a hashing function,
;; since we do not perform garbage collections and relocate symbols.  Note that
;; the implementation of the operation actually shifts the pointer right by 3
;; bits, since Chestnut pointers are always multiples of 8.  However, since
;; fixnums have a shorter range than longs (especially on 64 bit machines) we
;; must mask the result with most-positive-fixnum to ensure that we have
;; received a positive fixnum result.  -jra 11/4/93






;;;; Binary Trees




;;; Hash table and binary tree lookup structures are provided through the
;;; def-binary-tree and def-hash-table mechanisms.  Both of these mechanisms
;;; allow users to specify their own hashing function, reclaimers for keys
;;; and/or value entries, key comparitor functions, and hash table sizes.  These
;;; mechanisms are intended to be general enough to handle any fast lookup
;;; situations where a repeatable hash can be computed from a key.  The binary
;;; trees use the computed hash to generate branches and nodes, and then use a
;;; supplied key comparitor to assoc down the list of keys which collided at a
;;; particular hash number.  The insertion and deletion functions for binary
;;; trees always maintain balanced binary trees.  The hash table uses the
;;; computed hash mod its size to index to a bucket, and it uses binary trees in
;;; each bucket to arbitrate bucket collisions.  This should make hash tables
;;; very tolerant of overfilling.

;;; The `lookup' cons pool and the `binary-tree-element' structure pool are used
;;; by all hash tables and binary trees.

(defconser lookup)

(def-structure (binary-tree-element
                 (:type vector)
                 (:creations-at-a-time 100)
                 (:constructor
                   make-binary-tree-element
                   (binary-element-hash-number
                     less-than-branch
                     greater-than-branch
                     binary-element-alist
                     balance-factor)))
  binary-element-hash-number
  less-than-branch
  greater-than-branch
  binary-element-alist
  balance-factor)




;;; The macro `def-binary-tree' defines constructor, reclaimer, clear, and
;;; accessor macros for a named binary tree type.  The constructor is named
;;; MAKE-name-TREE (where "name" is the passed name of the tree) which takes no
;;; arguments, and returns a new empty tree.  The reclaimer is
;;; RECLAIM-name-TREE, and takes a tree to be reclaimed as its argument.  The
;;; clearing macro is CLEAR-name-TREE, which takes a tree and will clear out and
;;; reclaim all entries currently in the tree.  The accessor is GET-name which
;;; takes the key to be looked up and a tree to look it up in.  It returns the
;;; value found, or NIL if no entry exists for the key.  SETF should be used
;;; with the accessor macro to modify a value.  Note that the tree will store
;;; references to both a key and its value on tree modification, and will
;;; reclaim both the key and the value as necessary.  Rotations are performed to
;;; keep the tree balanced as entries are added.  The key deleter is
;;; DELETE-name, which takes a key and deletes the entry and value for that key
;;; from the tree.  Any tree nodes which are emptied by this deletion are pruned
;;; from the tree, and rebalancing performed on the remaining nodes.  Each of
;;; these name choices may be overridden through optional arguments to
;;; def-binary-tree.  A further set of accessor, deleter, and mutator macros
;;; which take an already computed hash will be defined when called for by the
;;; x-given-hash options.  These facilities are used by hash tables.  The one
;;; required argument is the tree name, and the rest of the optional arguments
;;; are provided as keywords, taking unquoted symbols.

;;; The options are as follows:
;;;
;;;   :constructor takes an unquoted symbol to use as the name of the
;;;   constructor macro instead of MAKE-name-TREE.
;;;
;;;   :reclaimer takes an unquoted symbol to use as the name of the reclaimer
;;;   macro instead of RECLAIM-name-TREE.
;;;
;;;   :clearer takes an unquoted symbol to use as the name of the clearing macro
;;;   instead of CLEAR-name-TREE.
;;;
;;;   :accessor takes an unquoted symbol to use as the name of the accessor
;;;   macro instead of GET-name.
;;;
;;;   :accessor-given-hash takes an unquoted symbol, and will cause an accessor
;;;   to be defined which takes as an additional argument the already computed
;;;   hash number of the key being looked up.  SETF may be used with this
;;;   accessor form.  This is used by the hash table mechanism.
;;;
;;;   :key-deleter takes an unquoted symbol to use as the name of macro for
;;;   deleting key entries from the tree instead of DELETE-name.
;;;
;;;   :key-deleter-given-hash takes an unquoted symbol, and will cause a macro to
;;;   be defined which takes a key and the hash for that key, and will delete
;;;   the entry for that key from the table.
;;;
;;;   :set-if-no-entry-given-hash takes an unquoted symbol, and will cause a
;;;   macro to be defined which takes a key, the hash for that key, and a new
;;;   entry.  The macro will add the given new entry to the tree if no entry
;;;   already exists for the given key.  The value which holds for the given key
;;;   at the end of the operation is the returned value.  So, if an entry
;;;   already existed for this key, then the old entry will be returned.  If
;;;   there was no old entry and the new one has now been entered as the value
;;;   of this key, then the new entry will be returned.  Note that if the new
;;;   entry is accepted, then both the key and the new entry will be "owned" by
;;;   tree, and will be reclaimed as instructed by the key-reclaimer and
;;;   entry-reclaimer arguments.
;;;
;;;   :hash-function takes as an unquoted symbol the name of the function or
;;;   macro to use to compute the hash of a passed key.  It defaults to SXHASH,
;;;   which will almost never be the hashing function we will want to use.
;;;
;;;   :key-comparitor takes as an unquoted symbol the name of the FUNCTION which
;;;   is used to compare two keys to determine if they are equal.  This argument
;;;   may not name a macro, as it is passed as the :test argument to ASSOC.  It
;;;   defaults to EQ.  Note that because of an internal optimization, this
;;;   key-comparitor function may not perform mutations on binary trees.  This
;;;   is because of the use of a global data structure during the mutation
;;;   operation, which would corrupt if another tree mutation operation was
;;;   entered recursively.  The only place that can happen is through this
;;;   function, so don't be tempted into any weird hacks which mutate structure
;;;   during a comparison.
;;;
;;;   :key-reclaimer takes as an unquoted symbol the name of a function or macro
;;;   which should be used to reclaim keys when the tree is being reclaimed or
;;;   to reclaim a new key when a value is being modified for which an equal key
;;;   already exists in the tree structure.  It defaults to NIL; no reclamation.
;;;
;;;   :entry-reclaimer takes as an unquoted symbol the name of a function or
;;;   macro which should be used to reclaim entry keys when the tree is being
;;;   reclaimed, or to reclaim an old entry value when the tree is being modifed
;;;   and the old entry is being replaced with a new entry.  It defaults to NIL;
;;;   no reclamation.

;;;   :flattener returns an eval-list containing alternating
;;;   keys and values, giving all the keys and values in the tree
;;;   in arbitrary order.
;;;

(defmacro def-binary-tree (name &key
                                (constructor nil)
                                (reclaimer nil)
                                (clearer nil)
                                (accessor nil)
                                (accessor-given-hash nil)
                                (key-deleter nil)
                                (key-deleter-given-hash nil)
                                (set-if-no-entry-given-hash nil)
                                (hash-function 'sxhashw)
                                (key-comparitor 'eq)
                                (key-reclaimer nil)
                                (entry-reclaimer nil)
                                (flattener nil))
  (if (not (symbolp name))
      (error "The name argument, ~s, to def-binary-tree was not a symbol."
             name))
  (let* ((constructor-name
           (or constructor
               (intern (format nil "MAKE-~a-TREE" name))))
         (reclaimer-name
           (or reclaimer
               (intern (format nil "RECLAIM-~a-TREE" name))))
         (clear-name
           (or clearer
               (intern (format nil "CLEAR-~a-TREE" name))))
         (element-reclaimer-name (intern (format nil "RECLAIM-~a-LEAVES" name)))
         (accessor-name (or accessor (intern (format nil "GET-~a" name))))
         (mutator-name (intern (format nil "SET-~a-TREE-VALUE" name)))
         (mutator-given-hash
           (if accessor-given-hash
               (intern (format nil "SET-~a" accessor-given-hash))))
         (deleter-name (or key-deleter (intern (format nil "DELETE-~a" name))))
         (flattener-name (or flattener (intern (format nil "FLATTEN-~a" name))))
         (entry-mutator?
           (if (or key-reclaimer entry-reclaimer)
               (intern (format nil "MUTATE-~a-TREE-ENTRY" name))
               nil))
         (entry-mutator-var?
           (if entry-mutator?
               (intern (format nil "FP-~a" entry-mutator?))
               nil))
         (tree-variable (intern (format nil "~a-BINARY-TREE" name))))
  `(progn

     (defmacro ,constructor-name ()
       `(lookup-cons-macro ',',name nil))

     ,@(when entry-mutator?
         `((defun-void ,entry-mutator? (entry-cons new-key new-entry)
             ,@(if key-reclaimer
                   `((,key-reclaimer (car-of-cons entry-cons)))
                   nil)
             ,@(if entry-reclaimer
                   `((,entry-reclaimer (cdr-of-cons entry-cons)))
                   nil)
             (setf (car entry-cons) new-key)
             (setf (cdr entry-cons) new-entry))
           (defparameter ,entry-mutator-var? #',entry-mutator?)))

     ,@(when accessor-given-hash
         `((defmacro ,accessor-given-hash
                     (key ,tree-variable hash)
             (if (or (constantp key) (symbolp key))
                 `(lookup-binary-tree-entry-macro
                    (cdr ,,tree-variable)
                    ,',key-comparitor
                    ,key
                    ,hash)
                 (let ((key-var (gensym)))
                   `(let ((,key-var ,key))
                      (lookup-binary-tree-entry-macro
                        (cdr ,,tree-variable)
                        ,',key-comparitor
                        ,key-var
                        ,hash)))))

           (defmacro ,mutator-given-hash
                     (key ,tree-variable hash entry)
             (if (or (constantp key) (symbolp key))
                 `(set-balanced-binary-tree-entry
                    ,,tree-variable
                    ',',key-comparitor
                    ,',entry-mutator-var?
                    t
                    ,key
                    ,hash
                    ,entry)
                 (let ((key-var (gensym)))
                   `(let ((,key-var ,key))
                      (set-balanced-binary-tree-entry
                        ,,tree-variable
                        ',',key-comparitor
                        ,',entry-mutator-var?
                        t
                        ,key-var
                        ,hash
                        ,entry)))))

           (defsetf ,accessor-given-hash ,mutator-given-hash)))

     ,@(when set-if-no-entry-given-hash
         `((defmacro ,set-if-no-entry-given-hash (key ,tree-variable hash entry)
             (if (or (constantp key) (symbolp key))
                 `(set-balanced-binary-tree-entry
                    ,,tree-variable
                    ',',key-comparitor
                    nil
                    nil
                    ,key
                    ,hash
                    ,entry)
                 (let ((key-var (gensym)))
                   `(let ((,key-var ,key))
                      (set-balanced-binary-tree-entry
                        ,,tree-variable
                        ',',key-comparitor
                        nil
                        nil
                        ,key-var
                        ,hash
                        ,entry)))))))

     (defmacro ,accessor-name (key ,tree-variable)
       (if (or (constantp key) (symbolp key))
           `(lookup-binary-tree-entry-macro
              (cdr ,,tree-variable)
              ,',key-comparitor
              ,key
              (,',hash-function ,key))
           (let ((key-evaled (gensym)))
             `(let ((,key-evaled ,key))
                (lookup-binary-tree-entry-macro
                  (cdr ,,tree-variable)
                  ,',key-comparitor
                  ,key-evaled
                  (,',hash-function ,key-evaled))))))

     (defmacro ,mutator-name (key ,tree-variable entry)
       (let ((key-evaled (gensym)))
         `(let ((,key-evaled ,key))
            (set-balanced-binary-tree-entry
              ,,tree-variable
              ',',key-comparitor
              ,',entry-mutator-var?
              t
              ,key-evaled
              (,',hash-function ,key-evaled)
              ,entry))))

     (defsetf ,accessor-name ,mutator-name)

     (defmacro ,deleter-name (key ,tree-variable)
       ,(if (and (null key-reclaimer) (null entry-reclaimer))
            `(if (or (symbolp key) (constantp key))
                 `(progn
                    (delete-balanced-binary-tree-entry
                      #',',key-comparitor
                      ,key
                      ,,tree-variable
                      (,',hash-function ,key))
                    nil)
                 (let ((key-evaled (gensym)))
                   `(let ((,key-evaled ,key))
                      (delete-balanced-binary-tree-entry
                        #',',key-comparitor
                        ,key-evaled
                        ,,tree-variable
                        (,',hash-function ,key-evaled))
                      nil)))
            ``(multiple-value-bind (old-key old-entry)
                  ,(if (or (symbolp key) (constantp key))
                       `(delete-balanced-binary-tree-entry
                          #',',key-comparitor
                          ,key
                          ,,tree-variable
                          (,',hash-function ,key))
                       (let ((key-evaled (gensym)))
                         `(let ((,key-evaled ,key))
                            (delete-balanced-binary-tree-entry
                              #',',key-comparitor
                              ,key-evaled
                              ,,tree-variable
                              (,',hash-function ,key-evaled)))))
                ,@',(cond ((null key-reclaimer)
                           `((declare (ignore old-key))
                             (,entry-reclaimer old-entry)))
                          ((null entry-reclaimer)
                           `((declare (ignore old-entry))
                             (,key-reclaimer old-key)))
                          (t
                           `((,key-reclaimer old-key)
                             (,entry-reclaimer old-entry))))
                nil)))
     ,@(if key-deleter-given-hash
           `((defmacro ,key-deleter-given-hash
                        (key ,tree-variable key-hash)
               ,(if (and (null key-reclaimer) (null entry-reclaimer))
                    ``(progn
                        (delete-balanced-binary-tree-entry
                          #',',key-comparitor
                          ,key
                          ,,tree-variable
                          ,key-hash)
                        nil)
                    ``(multiple-value-bind (old-key old-entry)
                          (delete-balanced-binary-tree-entry
                            #',',key-comparitor
                            ,key
                            ,,tree-variable
                            ,key-hash)
                        ,@',(cond ((null key-reclaimer)
                                   `((declare (ignore old-key))
                                     (,entry-reclaimer old-entry)))
                                  ((null entry-reclaimer)
                                   `((declare (ignore old-entry))
                                     (,key-reclaimer old-key)))
                                  (t
                                   `((,key-reclaimer old-key)
                                     (,entry-reclaimer old-entry))))
                        nil)))))

     ,@(unless (or key-reclaimer entry-reclaimer)
         `((defun-simple ,element-reclaimer-name (,tree-variable)
             (loop until (null ,tree-variable)
                   for less-than-branch? = (less-than-branch ,tree-variable)
                   for greater-than-branch? = (greater-than-branch
                                                ,tree-variable)
                   for alist = (binary-element-alist ,tree-variable)
                   do
               (reclaim-binary-tree-element ,tree-variable)
               (loop for alist-entry in alist
                     do
                 ,@(if key-reclaimer
                       `((,key-reclaimer (car alist-entry)))
                       nil)
                 ,@(if entry-reclaimer
                       `((,entry-reclaimer (cdr alist-entry)))
                       nil)
                 (reclaim-lookup-cons-macro alist-entry))
               (reclaim-lookup-list-macro alist)
               (cond ((and less-than-branch? greater-than-branch?)
                      (,element-reclaimer-name less-than-branch?)
                      (setq ,tree-variable greater-than-branch?))
                     (t
                      (setq ,tree-variable
                            (or less-than-branch? greater-than-branch?))))))))

     ;; Note that the reclaimer and clearing functions delete a tree by
     ;; repeatedly deleting the first key in the root element of the tree when
     ;; there are reclaimers for either the key or the entry.  This is done
     ;; since the reclaimers for the keys or entries may further mutate this
     ;; binary tree, rebalancing it in the process.  The old reclaimers
     ;; experienced bugs in rules because of this.

     (def-substitution-macro ,reclaimer-name (,tree-variable)
       ,(if (or key-reclaimer entry-reclaimer)
            `(loop for element? = (cdr-of-cons ,tree-variable)
                   while element?
                   do
               (,deleter-name
                (car-of-cons (car-of-cons (binary-element-alist element?)))
                ,tree-variable)
                   finally
                     (reclaim-lookup-cons-macro ,tree-variable))
            `(let ((element? (cdr-of-cons ,tree-variable)))
               (if element?
                   (,element-reclaimer-name element?))
               (reclaim-lookup-cons-macro ,tree-variable))))

     (defun-simple ,clear-name (,tree-variable)
       ,(if (or key-reclaimer entry-reclaimer)
            `(loop for element? = (cdr ,tree-variable)
                   while element?
                   do
               (,deleter-name
                (caar (binary-element-alist element?))
                ,tree-variable))
            `(let ((element? (cdr ,tree-variable)))
               (when element?
                 (,element-reclaimer-name element?)
                 (setf (cdr ,tree-variable) nil))))
       ,tree-variable)

     (defmacro ,flattener-name (,tree-variable)
       `(flatten-binary-tree (cdr ,,tree-variable)))

     ',name)))


;;; This returns the result in arbitrary order. We could also do an
;;; ordered one, but we're not bothering for now, since the intended
;;; client is def-hash-table, which doesn't care about the order.
(defun flatten-binary-tree (tree)
  (when tree
    (flatten-binary-tree-1 tree nil)))

;;; flatten-binary-tree-1 takes a list of key-value pairs and a binary
;;; tree, and adds the pairs on the list to the existing list of pairs.

;;; Maybe this should get rewritten iteratively, to avoid any risk
;;; of blowing the stack. It may be that this is doing no more
;;; to the stack than other functions that access the same binary
;;; tree, though, in which case there's no gain my changing
;;; it in this way.

(defmacro early-eval-cons (car cdr)
  #+development`(eval-cons-1 ,car ,cdr)
  #-development`(gensym-cons-1 ,car ,cdr))

(defun flatten-binary-tree-1 (tree pairs)
  (loop for pair in (binary-element-alist tree)
    do
    ;; we can't use eval-push, or even eval-cons,
    ;; because that would be forward-referencing
    ;; a macro. Sigh.
    (setq pairs (early-eval-cons (car pair)
                                 (early-eval-cons
                                   (cdr pair) pairs))))
  (let ((subtree1 (less-than-branch tree))
        (subtree2 (greater-than-branch tree)))
    (when subtree1
      (setq pairs (flatten-binary-tree-1 subtree1 pairs)))
    (when subtree2
      (setq pairs (flatten-binary-tree-1 subtree2 pairs)))
    pairs))

;;; The macro `lookup-binary-tree-entry' is used by binary trees as their lookup
;;; function.  It takes a binary tree element structure, a key comparitor
;;; function, a key, and a fixnum key-hash as arguments and either returns the
;;; value stored under that key in the tree, or NIL if there was no entry for
;;; that key.

(declare-side-effect-free-function lookup-binary-tree-entry)

(defun-simple lookup-binary-tree-entry (tree-element key-comparitor key key-hash)
  (declare (type fixnum key-hash))
  (loop with key-hash-local fixnum = key-hash
        until (null tree-element)
        for element-hash fixnum = (binary-element-hash-number tree-element)
        do
    (cond ((<f key-hash-local element-hash)
           (setq tree-element (less-than-branch tree-element)))
          ((>f key-hash-local element-hash)
           (setq tree-element (greater-than-branch tree-element)))
          (t
           (return
             (loop for entry-cons on (binary-element-alist tree-element)
                   for entry-key = (car-of-cons (car-of-cons entry-cons))
                   do
               ;; Oddly enough, the bizarre cond clause below is faster
               ;; than just calling funcall in the current Chestnut.
               ;; -jra 3/31/94
               (when (cond ((eq key-comparitor 'equal)
                            (equal key entry-key))
                           ((eq key-comparitor 'string=)
                            (string= key entry-key))
                           ((eq key-comparitor 'equal-rule-context)
                            (equal-rule-context key entry-key))
                           (t
                            (funcall key-comparitor key entry-key)))
                 (return (cdr-of-cons (car-of-cons entry-cons))))))))))

;;; The macro `lookup-binary-tree-entry' is used by binary trees as their lookup
;;; function.  It takes a binary tree element structure, a key comparitor
;;; function, a key, and a fixnum key-hash as arguments and either returns the
;;; value stored under that key in the tree, or NIL if there was no entry for
;;; that key.  Note that this is a standard macro, except that the
;;; key-comparitor argument should be an unquoted symbol giving a two argument
;;; comparitor operation called by the expansion of this macro.

(defmacro lookup-binary-tree-entry-macro (tree-element key-comparitor key key-hash)
  (let ((tree (gensym))
        (key-value (gensym))
        (key-hash-value (gensym))
        (element-hash (gensym))
        (entry-cons (gensym))
        (entry-key (gensym)))
    `(let ((,tree ,tree-element)
           (,key-value ,key)
           (,key-hash-value ,key-hash))
       (declare (type fixnum ,key-hash-value))
       (loop until (null ,tree)
             for ,element-hash fixnum = (binary-element-hash-number ,tree)
             do
         (cond ((<f ,key-hash-value ,element-hash)
                (setq ,tree (less-than-branch ,tree)))
               ((>f ,key-hash-value ,element-hash)
                (setq ,tree (greater-than-branch ,tree)))
               (t
                (return
                  (loop for ,entry-cons on (binary-element-alist ,tree)
                        for ,entry-key = (car-of-cons (car-of-cons ,entry-cons))
                        do
                    (when (,key-comparitor ,key-value ,entry-key)
                      (return (cdr-of-cons (car-of-cons ,entry-cons))))))))))))




;;; The function `lookup-eq-binary-tree-entry' is a version of
;;; lookup-binary-tree-entry which uses EQ as its comparitor.

(declare-side-effect-free-function lookup-eq-binary-tree-entry)

(defun-simple lookup-eq-binary-tree-entry (tree-element key key-hash)
  (declare (type fixnum key-hash))
  (loop with key-hash-local fixnum = key-hash
        until (null tree-element)
        for element-hash fixnum = (binary-element-hash-number tree-element)
        do
    (cond ((<f key-hash-local element-hash)
           (setq tree-element (less-than-branch tree-element)))
          ((>f key-hash-local element-hash)
           (setq tree-element (greater-than-branch tree-element)))
          (t
           (return
             (loop for entry-cons on (binary-element-alist tree-element)
                   do
               (when (eq key (car-of-cons (car-of-cons entry-cons)))
                 (return (cdr-of-cons (car-of-cons entry-cons))))))))))




;;; The system variables `binary-tree-ancestor' and `binary-tree-branch' hold 50
;;; element arrays used as temporary storage for the balanced binary tree set
;;; and delete functions.  The following demonstration that this is an adequate
;;; size to handle the deepest of binary trees has been graciously provided by
;;; Michael.
;;;
;;; (avl-min-size n) for n > 0 is the minimum size (number of nodes) of an avl
;;; tree of depth n.  The second value, for n > 1 is avl-min-size(n - 1).  This
;;; is used as a computational efficiency.
;;;
;;; Avl-min-size is given by the inductive formula:
;;;
;;;          avl-min-size(n+2) = avl-min-size(n) + avl-min-size(n+1) + 1
;;;
;;; The justification for the formula is that the smallest tree of depth
;;; n+2 must have a non-zero balance, and have minimally sized subtrees
;;; of depth n and n+1.

;;; (defun avl-min-size (n)
;;;   (cond
;;;     ((= n 1) 1)
;;;     ((= n 2) (values 2 1))
;;;     (t (multiple-value-bind (x y)
;;;                (avl-min-size (1- n))
;;;             (values (+ x y 1) x)))))

;;; Note avl-min-size(50) = 32,951,280,098.  This would seem to be a sufficient
;;; table size for the present.  Therefore, you can safely use a fixed list or
;;; array, rather than dynamically allocated storage for insertion/deletion
;;; operators.

(declare-special-global binary-tree-ancestor
                        binary-tree-branch)

(def-system-variable binary-tree-ancestor utilities2 (:funcall make-array 50)
                     nil t)

(def-system-variable binary-tree-branch utilities2 (:funcall make-array 50)
                     nil t)




;;; The function `set-balanced-binary-tree-entry' will add a new element to the
;;; given tree, maintaining tree balance.  When given a mutate-entry? flag of
;;; NIL this function will then refuse to mutate any existing entries of the
;;; tree, returning the existing value for the given tree instead of the new
;;; value passed as an argument.  If the mutate-entry? flag is non-nil, then the
;;; given value will always become the entry for the given key, and will always
;;; be the returned value.  Also note that the key-comparitor is always a symbol
;;; naming a function, and the mutator-function is always a
;;; compiled-simple-function or NIL.

;;; Note that the use of the special variables binary-tree-ancestor and
;;; binary-tree-branch require that this function never be called recursively.
;;; The only place this could arise is the key-comparitor.

(defun-simple set-balanced-binary-tree-entry
       (binary-tree key-comparitor mutator-function? mutate-old-entry?
        key key-hash entry)
  (declare (type fixnum key-hash))
  ;; Special case where tree is empty.
  (when (null (cdr binary-tree))
    (setf (cdr binary-tree)
          (make-binary-tree-element
            key-hash nil nil
            (lookup-cons-macro (lookup-cons-macro key entry) nil)
            0))
    (return-from set-balanced-binary-tree-entry entry))

  ;; Initialize search variables.
  (let* ((insertion-point (cdr binary-tree))
         (insertion-depth 0)
         (heavy-ancestor-depth 0))
    (declare (type fixnum insertion-depth heavy-ancestor-depth))
    ;; Search for the insertion point.  If the key-hash collides with an
    ;; existing key in the tree, insert the new value in the alist and exit
    ;; since no rebalancing will be necessary.
    (loop while insertion-point
          for insertion-point-hash fixnum
              = (binary-element-hash-number insertion-point)
          do
      (when (/=f (balance-factor insertion-point) 0)
        (setq heavy-ancestor-depth insertion-depth))
      (cond ((<f key-hash insertion-point-hash)        ; Less than branch
             (setf (svref binary-tree-ancestor insertion-depth) insertion-point)
             (setf (svref binary-tree-branch insertion-depth) :less-than)
             (incff insertion-depth)
             (setq insertion-point (less-than-branch insertion-point)))
            ((>f key-hash insertion-point-hash) ; Greater than branch
             (setf (svref binary-tree-ancestor insertion-depth) insertion-point)
             (setf (svref binary-tree-branch insertion-depth) :greater-than)
             (incff insertion-depth)
             (setq insertion-point (greater-than-branch insertion-point)))
            ;; Collision of key hashes case.  Insert the element in the alist
            ;; and exit, no rebalancing will be necessary.
            (t
             (let* ((alist (binary-element-alist insertion-point))
                    (alist-entry?
                      (loop for entry-cons on alist
                            for entry-key
                            = (car-of-cons (car-of-cons entry-cons))
                            do
                        ;; Oddly enough, the bizarre cond clause below is faster
                        ;; than just calling funcall in the current Chestnut.
                        ;; -jra 3/31/94
                        (when (cond ((eq key-comparitor 'equal-rule-context)
                                     (equal-rule-context key entry-key))
									((eq key-comparitor 'eq)
                                     (eq key entry-key))
                                    ((eq key-comparitor 'equal)
                                     (equal key entry-key))
                                    ((eq key-comparitor 'string=)
                                     (string= key entry-key))
                                    (t
                                     (funcall key-comparitor key entry-key)))
                          (return (car-of-cons entry-cons))))))
               (if alist-entry?
                   (if mutate-old-entry?
                       (if mutator-function?
                           (funcall-simple-compiled-function
                             mutator-function? alist-entry? key entry)
                           (setf (cdr alist-entry?) entry))
                       (setq entry (cdr-of-cons alist-entry?)))        ; Return old value.
                   (setf (binary-element-alist insertion-point)
                         (lookup-cons-macro
                           (lookup-cons-macro key entry)
                           alist)))
               (return-from set-balanced-binary-tree-entry entry)))))

    ;; Insert a new node at the indicated point and rebalance.
    (let* ((new-node
             (make-binary-tree-element
               key-hash nil nil
               (lookup-cons-macro (lookup-cons-macro key entry) nil)
               0))
           (depth-of-insertion-parent (-f insertion-depth 1))
           (heavy-ancestor (svref binary-tree-ancestor heavy-ancestor-depth)))
      (declare (type fixnum depth-of-insertion-parent))
      (if (eq (svref binary-tree-branch depth-of-insertion-parent) :less-than)
          (setf (less-than-branch
                  (svref binary-tree-ancestor depth-of-insertion-parent))
                new-node)
          (setf (greater-than-branch
                  (svref binary-tree-ancestor depth-of-insertion-parent))
                new-node))

      ;; Adjust the balance factors of the nodes from the heavy ancestor to the
      ;; parent of the insertion-point.  Note that the definition of the heavy
      ;; ancestor implies that all nodes along the path now have a balance factor
      ;; of zero, and so will be changed to +-1.  A +1 balance means the child
      ;; went into the less than branch, -1 means the greater than branch.

      (loop for adjust-point from (+f heavy-ancestor-depth 1)
                             to depth-of-insertion-parent
            initially
              (if (eq (svref binary-tree-branch heavy-ancestor-depth)
                      :less-than)
                  (incff (balance-factor heavy-ancestor))
                  (decff (balance-factor heavy-ancestor)))
            do
        (setf (balance-factor (svref binary-tree-ancestor adjust-point))
              (if (eq (svref binary-tree-branch adjust-point) :less-than)
                  1
                  -1)))

      ;; Rebalance the tree if necessary.

      (let ((balance (balance-factor heavy-ancestor)))
        (when (or (>f balance 1) (<f balance -1))
          (rebalance-tree
            binary-tree
            (if (=f heavy-ancestor-depth 0)
                nil
                (svref binary-tree-ancestor (-f heavy-ancestor-depth 1)))
            heavy-ancestor)))

      entry)))




;;; The function `rebalance-tree' takes a binary tree, a parent node of an
;;; unbalanced node, and an unbalanced node.  This function will mutate the
;;; given tree such that the unbalanced node is now balanced, and will return
;;; the difference in height of the new balanced tree.  The branches of the
;;; unbalanced node must themselves be balanced trees which differ in depth by
;;; the amount given in the balance-factor slot of the unbalanced node.  Note
;;; that this function only works on the given node of the tree, and that any
;;; node which is not a descendent of the given node may itself be unbalanced
;;; and waiting for a balance operation.  This case does occur when deleting
;;; elements from balanced trees.

;;; Note that in all cases where the imbalance of this tree was generated by an
;;; insertion of a new node, the rebalance will reduce the size of the given
;;; tree by one.  There is one case of rebalancing which can arise while
;;; deleting nodes which would leave the resulting tree at the same overall
;;; height as that at which it started.  In this case this function will return
;;; 0 instead of -1.

(defun-simple rebalance-tree (binary-tree heavy-parent heavy-ancestor)
  (let* ((imbalance-direction (balance-factor heavy-ancestor))
         (heavy-child (if (=f imbalance-direction 2)
                          (less-than-branch heavy-ancestor)
                          (greater-than-branch heavy-ancestor)))
         (heavy-child-balance-factor (balance-factor heavy-child))
         (depth-change 0))
    (declare (type fixnum
		   imbalance-direction heavy-child-balance-factor depth-change))
    ;; Determine the appropriate rotation to rebalance the tree and execute it.
    (cond ((=f imbalance-direction 2)                ; Left imbalance.
           (cond ((=f heavy-child-balance-factor 1)        ; LL
                  (setf (less-than-branch heavy-ancestor)
                        (greater-than-branch heavy-child))
                  (setf (greater-than-branch heavy-child)
                        heavy-ancestor)
                  (setf (balance-factor heavy-ancestor) 0)
                  (setf (balance-factor heavy-child) 0)
                  (setq depth-change -1))
                 ((=f heavy-child-balance-factor 0)        ; LL(b)
                  (setf (less-than-branch heavy-ancestor)
                        (greater-than-branch heavy-child))
                  (setf (greater-than-branch heavy-child)
                        heavy-ancestor)
                  (setf (balance-factor heavy-ancestor) 1)
                  (setf (balance-factor heavy-child) -1)
                  (setq depth-change 0))
                 (t                                ; Rotation type LR
                  (let* ((heavy-grandchild
                           (greater-than-branch heavy-child))
                         (greater-than-heavy-great-grandchild
                           (greater-than-branch heavy-grandchild))
                         (less-than-heavy-great-grandchild
                           (less-than-branch heavy-grandchild)))
                    (setf (greater-than-branch heavy-child)
                          less-than-heavy-great-grandchild)
                    (setf (less-than-branch heavy-ancestor)
                          greater-than-heavy-great-grandchild)
                    (setf (less-than-branch heavy-grandchild)
                          heavy-child)
                    (setf (greater-than-branch heavy-grandchild)
                          heavy-ancestor)
                    (cond ((=f (balance-factor heavy-grandchild) 1)        ; LR(b)
                           (setf (balance-factor heavy-ancestor) -1)
                           (setf (balance-factor heavy-child) 0))
                          ((=f (balance-factor heavy-grandchild) -1)        ; LR(c)
                           (setf (balance-factor heavy-ancestor) 0)
                           (setf (balance-factor heavy-child) 1))
                          (t                        ; LR (a)
                           (setf (balance-factor heavy-ancestor) 0)
                           (setf (balance-factor heavy-child) 0)))
                    (setf (balance-factor heavy-grandchild) 0)
                    (setq depth-change -1)
                    ;; The child of the heavy ancestor is changed, since the
                    ;; heavy grandchild is now the new root of this subtree.
                    (setq heavy-child heavy-grandchild)))))
          ((=f imbalance-direction -2)                ; Right imbalance.
           (cond ((=f heavy-child-balance-factor -1)        ; RR
                  (setf (greater-than-branch heavy-ancestor)
                        (less-than-branch heavy-child))
                  (setf (less-than-branch heavy-child)
                        heavy-ancestor)
                  (setf (balance-factor heavy-ancestor) 0)
                  (setf (balance-factor heavy-child) 0)
                  (setq depth-change -1))
                 ((=f heavy-child-balance-factor 0)        ; RR (b)
                  (setf (greater-than-branch heavy-ancestor)
                        (less-than-branch heavy-child))
                  (setf (less-than-branch heavy-child) heavy-ancestor)
                  (setf (balance-factor heavy-ancestor) -1)
                  (setf (balance-factor heavy-child) 1)
                  (setq depth-change 0))
                 (t                                ; Rotation type RL
                  (let* ((heavy-grandchild
                           (less-than-branch heavy-child))
                         (less-than-heavy-great-grandchild
                           (less-than-branch heavy-grandchild))
                         (greater-than-heavy-great-grandchild
                           (greater-than-branch heavy-grandchild)))
                    (setf (less-than-branch heavy-child)
                          greater-than-heavy-great-grandchild)
                    (setf (greater-than-branch heavy-ancestor)
                          less-than-heavy-great-grandchild)
                    (setf (greater-than-branch heavy-grandchild)
                          heavy-child)
                    (setf (less-than-branch heavy-grandchild)
                          heavy-ancestor)
                    (cond ((=f (balance-factor heavy-grandchild) -1)        ; RL(b)
                           (setf (balance-factor heavy-ancestor) 1)
                           (setf (balance-factor heavy-child) 0))
                          ((=f (balance-factor heavy-grandchild) 1)        ; RL(c)
                           (setf (balance-factor heavy-ancestor) 0)
                           (setf (balance-factor heavy-child) -1))
                          (t                        ; RL (a)
                           (setf (balance-factor heavy-ancestor) 0)
                           (setf (balance-factor heavy-child) 0)))
                    (setf (balance-factor heavy-grandchild) 0)
                    (setq depth-change -1)
                    ;; The child of the heavy ancestor is changed, since the
                    ;; heavy grandchild is now the new root of this subtree.
                    (setq heavy-child heavy-grandchild)))))
          (t                                        ; No imbalance, get outa here!
           (return-from rebalance-tree 0)))

    ;; The subtree with root heavy-child has been rebalanced and is
    ;; the new subtree of the heavy-parent.
    (cond ((null heavy-parent)
           (setf (cdr binary-tree) heavy-child))
          ((eq (less-than-branch heavy-parent) heavy-ancestor)
           (setf (less-than-branch heavy-parent)
                 heavy-child))
          (t
           (setf (greater-than-branch heavy-parent)
                 heavy-child)))
    depth-change))




;;; The macro `find-alist-entry-and-previous-cons' takes an alist, a key, and a
;;; comparitor function.  It finds the position in the list of the entry for
;;; this key (if any) and returns the cons of the alist where it is stored and
;;; returns the cons previous to this one.


(def-substitution-macro find-alist-entry-and-previous-cons
                        (alist key comparitor)
  (if (or (null alist)
          (funcall-compiled-function comparitor key (caar alist)))
      (values alist nil)
      (loop for parent-cons = alist then entry-cons
            for entry-cons = (cdr alist) then (cdr entry-cons)
            while entry-cons
            do
        (if (funcall-compiled-function comparitor key (caar entry-cons))
            (return (values entry-cons parent-cons)))
            finally
              (return (values nil nil)))))




;;; The function `delete-balanced-binary-tree-entry' takes a balanced binary
;;; tree and deletes the indicated entry from that tree, performing an necessary
;;; rebalancing on the tree.  This function returns two values, the stored key
;;; and entry which have been removed from the tree.  If there was no entry for
;;; the given key, then the values NIL NIL are returned.

(defun delete-balanced-binary-tree-entry (comparitor key binary-tree key-hash)
  (declare (type fixnum key-hash))
  ;; Initialize searching variables.
  (let* ((deletion-point (cdr binary-tree))
         (deletion-depth 0)
         (old-key nil)
         (old-entry nil))
    (declare (type fixnum deletion-depth))

    ;; Handle the NULL tree case.
    (when (null deletion-point)
      (return-from delete-balanced-binary-tree-entry (values nil nil)))

    ;; Search for the deletion point.  If the hash does not collide with an
    ;; existing node that means that this key is not entered in the table, and
    ;; we should exit.  If the node with the appropriate hash has more than just
    ;; this entry in its alist, then we will not need to delete the node and we
    ;; may exit without any further balance factor adjustment or rebalancing.
    ;; Also, keep the ancestor path in a list with the following format
    ;; ((<ancestor> . <sub-branch-direction>) ... ).
    (loop while deletion-point
          for deletion-point-hash fixnum
              = (binary-element-hash-number deletion-point)
          do
      (cond ((<f key-hash deletion-point-hash)        ; Less than branch
             (setf (svref binary-tree-ancestor deletion-depth) deletion-point)
             (setf (svref binary-tree-branch deletion-depth) :less-than)
             (incff deletion-depth)
             (setq deletion-point (less-than-branch deletion-point)))
            ((>f key-hash deletion-point-hash) ; Greater than branch
             (setf (svref binary-tree-ancestor deletion-depth) deletion-point)
             (setf (svref binary-tree-branch deletion-depth) :greater-than)
             (incff deletion-depth)
             (setq deletion-point (greater-than-branch deletion-point)))
            ;; If hashes are equal, then we've found the node.
            (t
             (multiple-value-bind (entry-cons? parent-cons?)
                 (find-alist-entry-and-previous-cons
                   (binary-element-alist deletion-point) key comparitor)
               ;; If no entry is returned, then the key was not in the table.
               ;; If there is no entry or if there are other elements in the
               ;; alist, then we will not be deleting any nodes, and should set
               ;; the deletion-point to NIL.
               (if (null entry-cons?)
                   (setq deletion-point nil)
                   (let ((old-alist-cons (car-of-cons entry-cons?)))
                     (setq old-key (car-of-cons old-alist-cons))
                     (setq old-entry (cdr-of-cons old-alist-cons))
                     (cond (parent-cons?
                            (setf (cdr parent-cons?) (cdr-of-cons entry-cons?))
                            (setq deletion-point nil))
                           ((cdr-of-cons entry-cons?)
                            (setf (binary-element-alist deletion-point)
                                  (cdr-of-cons entry-cons?))
                            (setq deletion-point nil)))
                     (reclaim-lookup-cons-macro old-alist-cons)
                     (reclaim-lookup-cons-macro entry-cons?))))
             (return nil))))

    ;; If the deletion-point is null, then we are done.  Reclaim the ancestor
    ;; path, then return the old-key and old-entry values.

    (when (null deletion-point)
      (return-from delete-balanced-binary-tree-entry
        (values old-key old-entry)))

    ;; Delete the node in the deletion-point variable and note the branch to add
    ;; to the parent of the node being deleted.  If there are two subbranches to
    ;; this node then delete the inorder successor to the deletion-point node,
    ;; updating the ancestor-path so that it points down to the removal point
    ;; for the successor node.

    (let* ((less-branch (less-than-branch deletion-point))
           (greater-branch (greater-than-branch deletion-point))
           (rebalance-depth deletion-depth)
           (deletion-parent-depth (-f deletion-depth 1))
           (branch-to-promote
             (cond
               ((null less-branch)
                greater-branch)
               ((null greater-branch)
                less-branch)
               ((null (less-than-branch greater-branch))
                (setf (less-than-branch greater-branch) less-branch)
                (setf (balance-factor greater-branch)
                      (balance-factor deletion-point))
                (setf (svref binary-tree-ancestor rebalance-depth)
                      greater-branch)
                (setf (svref binary-tree-branch rebalance-depth)
                      :greater-than)
                (incff rebalance-depth)
                greater-branch)
               (t
                (loop for successor-parent = greater-branch
                                           then successor-node
                      for successor-node = (less-than-branch greater-branch)
                                         then successor-less-branch
                      for successor-less-branch
                          = (less-than-branch successor-node)
                      do
                  (incff rebalance-depth)
                  (setf (svref binary-tree-ancestor rebalance-depth)
                        successor-parent)
                  (setf (svref binary-tree-branch rebalance-depth)
                        :less-than)
                      until (null successor-less-branch)
                      finally
                        (setf (less-than-branch successor-parent)
                              (greater-than-branch successor-node))
                        (setf (less-than-branch successor-node) less-branch)
                        (setf (greater-than-branch successor-node) greater-branch)
                        (setf (balance-factor successor-node)
                              (balance-factor deletion-point))
                        (setf (svref binary-tree-ancestor deletion-depth)
                              successor-node)
                        (setf (svref binary-tree-branch deletion-depth)
                              :greater-than)
                        (incff rebalance-depth)
                        (return successor-node))))))
      (declare (type fixnum rebalance-depth deletion-parent-depth))

      ;; Reclaim the deleted node and insert the node to promote into the parent
      ;; pointer to this subtree.

      (reclaim-binary-tree-element deletion-point)
      (cond ((=f deletion-parent-depth -1)
             (setf (cdr binary-tree) branch-to-promote))
            ((eq (svref binary-tree-branch deletion-parent-depth) :less-than)
             (setf (less-than-branch
                     (svref binary-tree-ancestor deletion-parent-depth))
                   branch-to-promote))
            (t
             (setf (greater-than-branch
                     (svref binary-tree-ancestor deletion-parent-depth))
                   branch-to-promote)))

      ;; The deletion point node has now been removed and reclaimed, and the
      ;; tree is back into a correct ordered state.  However, it may now be
      ;; unbalanced.  The binary-tree-ancestor vector holds the ancestors to the
      ;; point of shortening of the tree in the elements numbered from 0 to
      ;; rebalance-depth - 1.  These elements must be traversed back toward the
      ;; root, rebalancing the tree and adjusting balance factors until we hit
      ;; the root or a node whose maximum depth has not been reduced by the
      ;; deletion.
      ;;
      ;; If a node was heavy towards the branch which has been shortened, then
      ;; it is now level, but its overall depth has been reduced by one and the
      ;; iteration must continue to its parent.  If this node was balanced, now
      ;; the opposite branch of the removal spot is heavy, but this node's
      ;; overall depth has remained constant and the iteration towards the root
      ;; should be terminated.  If this branch was heavy towards the opposite
      ;; branch from which the removal was made, then this node is now
      ;; unbalanced and must be rebalanced.  Its overall depth will have been
      ;; reduced by one, and the iteration must proceed to its ancestors.

      (loop with depth-reduced? = t
            with balance fixnum = 0
            for rebalance-point from (-f rebalance-depth 1) downto 0
            while depth-reduced?
            for ancestor = (svref binary-tree-ancestor rebalance-point)
            do
        (case (svref binary-tree-branch rebalance-point)
          ((:less-than)
           (setq balance
                 (decff (balance-factor ancestor)))
           (cond ((=f balance -1)
                  (setq depth-reduced? nil))
                 ((=f balance -2)
                  (if (=f (rebalance-tree
                            binary-tree
                            (if (/=f rebalance-point 0)
                                (svref binary-tree-ancestor
                                       (-f rebalance-point 1))
                                nil)
                            ancestor)
                          0)
                      (setq depth-reduced? nil)))))
          ((:greater-than)
           (setq balance
                 (incff (balance-factor ancestor)))
           (cond ((=f balance 1)
                  (setq depth-reduced? nil))
                 ((=f balance 2)
                  (if (=f (rebalance-tree
                            binary-tree
                            (if (/=f rebalance-point 0)
                                (svref binary-tree-ancestor
                                       (-f rebalance-point 1))
                                nil)
                            ancestor)
                          0)
                      (setq depth-reduced? nil)))))))

      ;; The tree is now rebalanced.  Return the old key and old entry.
      (values old-key old-entry))))




;;; The predicate `binary-tree-empty-p' can be used to efficiently determine if
;;; a binary tree has no entries in it.

(defmacro binary-tree-empty-p (binary-tree)
  `(null (cdr-of-cons ,binary-tree)))




;;; The `binary-tree-value loop path' allows users to loop over the values
;;; within binary trees.

(define-loop-path binary-tree-value
  #-skip-list expand-binary-tree-value-loop-iterator
  #+skip-list expand-skip-list-or-binary-tree-value-loop-iterator
  (of))

(defun-for-macro expand-binary-tree-value-loop-iterator
                 (method-name
                   iter-var iter-var-data-type prep-phrases inclusive?
                   allowed-preps method-specific-data)
  (declare (ignore method-name allowed-preps method-specific-data))
  (when inclusive?
    (error "The binary-tree-value iteration path does not support inclusive iterations."))
  (let* ((binary-tree-form-entry (assq 'of prep-phrases))
         (binary-tree-form (second binary-tree-form-entry))
         (node-stack (loop-gentemp 'node-stack-))
         (current-node (loop-gentemp 'current-node-))
         (next-node? (loop-gentemp 'next-node?-))
         (current-alist (loop-gentemp 'current-alist-))
         (entry-cons (loop-gentemp 'entry-cons-))
         (less-than-branch? (loop-gentemp 'less-than-branch?-))
         init-bindings
         prologue-forms
         (pre-step-tests nil)
         (steppings nil)
         post-step-tests
         post-step-settings)
    (when (null binary-tree-form-entry)
      (error "The binary-tree-value iteration path requires an \"OF binary-tree-form\"."))
    (when (or (not (symbolp iter-var)) (eq iter-var-data-type t))
      (setq iter-var-data-type nil))
    ;; The following variables need to be bound in the loop expansion.
    (setq init-bindings
          `((scope-conses scope-conses)
            (,node-stack nil)
            (,current-node nil)
            (,next-node? ,binary-tree-form)
            (,current-alist nil)
            (,entry-cons nil)
            ,(if iter-var-data-type
                 `(,iter-var nil ,iter-var-data-type)
                 `(,iter-var))))

    ;; NOTE: CDR-OF-CONS cannot accept NIL as arguments, but as a prologue form of
    ;; LOOP, if we have following LOOP use:
    ;; (loop with tree = ...
    ;;       while tree
    ;;       for value being each binary-tree-value of tree
    ;;  ...)
    ;; The expansion of LOOP will always call CDR-OF-CONS on tree even if it's NIL.
    ;; This has caused problems when we're using the LOOP on procedure-invocations.
    (setq prologue-forms
          `((setq ,next-node? (cdr-of-cons ,next-node?))))

    (setq post-step-tests
          `(progn
             (cond
               (,current-alist
                (setq ,entry-cons (car-of-cons ,current-alist))
                (setq ,current-alist (cdr-of-cons ,current-alist)))
               (t
                (cond
                  (,next-node?
                   (setq ,current-node ,next-node?)
                   (loop for ,less-than-branch? = (less-than-branch
                                                    ,current-node)
                         while ,less-than-branch?
                         do
                     (setq ,node-stack (scope-cons ,current-node ,node-stack))
                     (setq ,current-node ,less-than-branch?)))
                  (,node-stack
                   ;; Hold the cons in next-node? for a moment.
                   (setq ,next-node? ,node-stack)
                   (setq ,current-node (car-of-cons ,node-stack))
                   (setq ,node-stack (cdr-of-cons ,node-stack)))
                  (t
                   (setq ,current-node nil)))
                (when ,current-node
                  (setq ,next-node? (greater-than-branch ,current-node))
                  (setq ,current-alist (binary-element-alist ,current-node))
                  (setq ,entry-cons (car-of-cons ,current-alist))
                  (setq ,current-alist (cdr-of-cons ,current-alist)))))
             (null ,current-node)))

    ;; Use the type declaration only if it is something other than T and if the
    ;; iter-var is a symbol and not a destructuring list.
    (if (and (symbolp iter-var)
             iter-var-data-type
             (neq iter-var-data-type t))
        (setq post-step-settings
              `(,iter-var (the ,iter-var-data-type (cdr-of-cons ,entry-cons))))
        (setq post-step-settings
              `(,iter-var (cdr-of-cons ,entry-cons))))

    ;; Return a list of the six path elements.
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))




;;; The `binary-tree-entry-cons loop path' allows users to loop over the conses
;;; of keys and entrys within binary trees.

(define-loop-path binary-tree-entry-cons
  #-skip-list expand-binary-tree-entry-cons-loop-iterator
  #+skip-list expand-skip-list-or-binary-tree-entry-cons-loop-iterator
  (of))

(defun-for-macro expand-binary-tree-entry-cons-loop-iterator
                 (method-name
                   iter-var iter-var-data-type prep-phrases inclusive?
                   allowed-preps method-specific-data)
  (declare (ignore method-name allowed-preps iter-var-data-type method-specific-data))
  (when inclusive?
    (error "The binary-tree-entry-cons iteration path does not support inclusive iterations."))
  (let* ((binary-tree-form-entry (assq 'of prep-phrases))
         (binary-tree-form (second binary-tree-form-entry))
         (node-stack (loop-gentemp 'node-stack-))
         (current-node (loop-gentemp 'current-node-))
         (next-node? (loop-gentemp 'next-node?-))
         (current-alist (loop-gentemp 'current-alist-))
         (entry-cons (loop-gentemp 'entry-cons-))
         (less-than-branch? (loop-gentemp 'less-than-branch?-))
         init-bindings
         prologue-forms
         (pre-step-tests nil)
         (steppings nil)
         post-step-tests
         post-step-settings)
    (when (null binary-tree-form-entry)
      (error "The binary-tree-value iteration path requires an \"OF binary-tree-form\"."))
    ;; The following variables need to be bound in the loop expansion.
    (setq init-bindings
          `((scope-conses scope-conses)
            (,node-stack nil)
            (,current-node nil)
            (,next-node? ,binary-tree-form)
            (,current-alist nil)
            (,entry-cons nil)
            (,iter-var)))

    (setq prologue-forms
          `((setq ,next-node? (cdr-of-cons ,next-node?))))

    (setq post-step-tests
          `(progn
             (cond
               (,current-alist
                (setq ,entry-cons (car-of-cons ,current-alist))
                (setq ,current-alist (cdr-of-cons ,current-alist)))
               (t
                (cond
                  (,next-node?
                   (setq ,current-node ,next-node?)
                   (loop for ,less-than-branch? = (less-than-branch
                                                    ,current-node)
                         while ,less-than-branch?
                         do
                     (setq ,node-stack (scope-cons ,current-node ,node-stack))
                     (setq ,current-node ,less-than-branch?)))
                  (,node-stack
                   ;; Hold the cons in next-node? for a moment.
                   (setq ,next-node? ,node-stack)
                   (setq ,current-node (car-of-cons ,node-stack))
                   (setq ,node-stack (cdr-of-cons ,node-stack)))
                  (t
                   (setq ,current-node nil)))
                (when ,current-node
                  (setq ,next-node? (greater-than-branch ,current-node))
                  (setq ,current-alist (binary-element-alist ,current-node))
                  (setq ,entry-cons (car-of-cons ,current-alist))
                  (setq ,current-alist (cdr-of-cons ,current-alist)))))
             (null ,current-node)))

    (setq post-step-settings
          `(,iter-var ,entry-cons))

    ;; Return a list of the six path elements.
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

;;; The function `describe-tree' takes a binary tree as its argument and will
;;; print out a description of the tree and its current contents.

#+development
(progn
  (defvar binary-tree-count 0)
  (defvar binary-tree-node-count 0)
  (defvar binary-tree-collision-count 0)
  (defvar binary-tree-max-depth 0)

  (defun describe-tree (binary-tree)
    (cond ((or (not (consp binary-tree))
               (not (symbolp (car binary-tree)))
               (and (cdr binary-tree)
                    (not (simple-vector-p (cdr binary-tree)))))
           (format t "~%~S is not a binary-tree." binary-tree))
          ((null (cdr binary-tree))
           (format t "~%This is an empty ~a tree." (car binary-tree)))
          (t
           (format t "~%This is a ~a tree with the following nodes and contents:"
                   (car binary-tree))
           (let ((binary-tree-count 0)
                 (binary-tree-max-depth 0))
             (describe-tree-nodes (cdr binary-tree) 0)
             (format t "~%~a total entries in tree with a maximum depth of ~a."
                     binary-tree-count
                     (+f binary-tree-max-depth 1)))))
    binary-tree)

  (defun tree-indent-to-depth (depth)
    (loop repeat depth do (format t "|  ")))

  (defun describe-tree-nodes (node depth)
    (setq binary-tree-max-depth (maxf depth binary-tree-max-depth))
    (incff binary-tree-count (length (binary-element-alist node)))
    (terpri)
    (tree-indent-to-depth depth)
    (format t "Node Hash  = ~a" (binary-element-hash-number node))
    (terpri)
    (tree-indent-to-depth depth)
    (format t "Balance factor = ~a" (balance-factor node))
    (terpri)
    (tree-indent-to-depth depth)
    (format t "Node Alist = ~s" (binary-element-alist node))
    (terpri)
    (tree-indent-to-depth depth)
    (if (less-than-branch node)
        (progn
          (format t "Less Than Branch:")
          (describe-tree-nodes (less-than-branch node) (+f depth 1))
          (terpri)
          (tree-indent-to-depth depth)
          (format t "End Less Than Branch"))
        (format t "No Less Than Branch"))
    (terpri)
    (tree-indent-to-depth depth)
    (if (greater-than-branch node)
        (progn
          (format t "Greater Than Branch:")
          (describe-tree-nodes (greater-than-branch node) (+f depth 1))
          (terpri)
          (tree-indent-to-depth depth)
          (format t "End Greater Than Branch"))
        (format t "No Greater Than Branch")))




  ;;; The function `print-tree' takes a binary tree and prints out a list of the
  ;;; elements of that tree, showing the hash numbers for each element set.


  (defun print-tree (tree)
    (cond ((null (cdr tree))
           (format t "~%No elements in ~a tree." (car tree)))
          (t
           (format t "~%Elements in ~a tree:" (car tree))
           (print-elements (cdr tree)))))

  (defun print-elements (element?)
    (when element?
      (print-elements (less-than-branch element?))
      (format t "~%Elements at hash ~a" (binary-element-hash-number element?))
      (loop for entry in (binary-element-alist element?)
            do
        (format t "~%  ~S => ~S" (car entry) (cdr entry)))
      (print-elements (greater-than-branch element?))))

  (defun collect-tree-statistics (tree?)
    (if (null tree?)
        (values 0 0 0 0)
        (let ((binary-tree-count 0)
              (binary-tree-node-count 0)
              (binary-tree-collision-count 0)
              (binary-tree-max-depth 0))
          (collect-statistics-from-node (cdr tree?) 0)
          (values binary-tree-count binary-tree-node-count
                  binary-tree-collision-count binary-tree-max-depth))))

  (defun collect-statistics-from-node (node? depth)
    (when node?
      (incff depth)
      (incff binary-tree-count (length (binary-element-alist node?)))
      (if (>f (length (binary-element-alist node?)) 1)
          (incff binary-tree-collision-count))
      (incff binary-tree-node-count)
      (setq binary-tree-max-depth (maxf depth binary-tree-max-depth))
      (collect-statistics-from-node (less-than-branch node?) depth)
      (collect-statistics-from-node (greater-than-branch node?) depth)))

  (defun validate-tree-balance (tree-node spot-tag)
    (when tree-node
      (let* ((less-branch (less-than-branch tree-node))
             (less-than-weight (tree-depth-count less-branch))
             (greater-branch (greater-than-branch tree-node))
             (greater-than-weight (tree-depth-count greater-branch)))
        (if (or (/=f (balance-factor tree-node)
                     (-f less-than-weight greater-than-weight))
                (>f (absf (balance-factor tree-node)) 1))
            (cerror "Continue."
                    "Node ~a out sync with its balance.  Bal Fact = ~a, Left = ~a, Right = ~a"
                    tree-node
                    less-than-weight
                    greater-than-weight)
            (progn
              (when less-branch
                (validate-tree-balance less-branch spot-tag))
              (when greater-branch
                (validate-tree-balance greater-branch spot-tag)))))))

  (defun tree-depth-count (tree-node?)
    (if (null tree-node?)
        0
        (+f (maxf (tree-depth-count (less-than-branch tree-node?))
                  (tree-depth-count (greater-than-branch tree-node?)))
            1)))

  (defun tree-node-count (tree-node?)
    (if tree-node?
        (+f 1
            (tree-node-count (less-than-branch tree-node?))
            (tree-node-count (greater-than-branch tree-node?)))
        0))

  )




;;;; Skip List




;;; Many popular sequential search structures, such as red-black trees or AVL-
;;; trees, require periodic rebalancing to maintain the structure's logarithmic
;;; depth. Rebalancing works well for sequential tree-based search structures,
;;; but for concurrent structures, rebalancing may cause bottlenecks and
;;; contention. `SKIP LIST' is a proven data structure that provides expected
;;; logarithmic time search without the need to rebalance.

;;; The SkipList is a probabilistic data structure. (No one knows how to provide
;;; this kind of performance without randomization.) Each node is created with a
;;; random top level (topLevel), and belongs to all lists up to that level. Top
;;; levels are chosen so that the expected number of nodes in each level's list
;;; decreases exponentially. Let 0 < p < 1 be the conditional probability that a
;;; node at level i also appears at level i + 1. All nodes appear at level 0.
;;; The probability that a node at level 0 also appears at level i > 0 is p_i.
;;; For example, with p = 1/2, 1/2 of the nodes are expected to appear at level
;;; 1, 1/4 at level 2 and so on, providing a balancing property like the
;;; classical sequential tree-based search structures, except without the need
;;; for complex global restructuring.

;;; Here's a picture of some of the basics for a possible list with 2 levels of
;;; index:

;;;  Head nodes          Index nodes
;;;  +-+    next         +-+                      +-+
;;;  |2|---------------->| |--------------------->| |->null
;;;  +-+                 +-+                      +-+
;;;   |                   |                        |
;;;  +-+    next    +-+  +-+       +-+            +-+       +-+
;;;  |1|----------->| |->| |------>| |----------->| |------>| |->null
;;;  +-+            +-+  +-+       +-+            +-+       +-+
;;;   |              |    |         |              |         |
;;;  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+
;;;  | |->|A|->|B|->|C|->|D|->|E|->|F|->|G|->|H|->|I|->|J|->|K|->null
;;;  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-+

;;; We've implemented the Lock-Free Skip List to replace all BINARY-TREEs used
;;; in SymScale G2.                            -- Chun Tian (binghe), May 2014.

(def-structure (skip-list-element
		 (:type vector)
		 (:creations-at-a-time 100)
		 (:constructor
		   make-skip-list-element
		   (skip-list-element-hash-number
		    skip-list-element-key
		    skip-list-element-entry
		    skip-list-element-top-level))
		 (:reclaimer reclaim-skip-list-element-internal))
  skip-list-element-next ; (simple-vector atomic-reference *)
  skip-list-element-hash-number ; fixnum
  skip-list-element-key
  skip-list-element-entry
  skip-list-element-top-level)

(defun-simple reclaim-skip-list-element (element)
  (reclaim-managed-simple-vector-for-skip-list
    (skip-list-element-next element))
  (setf (skip-list-element-next element) nil)
  #+development
  (progn
    (setf (skip-list-element-hash-number element) 0)
    (setf (skip-list-element-key element) nil)
    (setf (skip-list-element-entry element) nil)
    (setf (skip-list-element-top-level element) 0))
  (reclaim-skip-list-element-internal element))

;;; The macro `def-skip-list' defines constructor, reclaimer, clear, and
;;; accessor macros for a named skip list type.

(defmacro skip-list-head (skip-list)
  `(car-of-cons (cdr-of-cons ,skip-list)))

(defmacro skip-list-tail (skip-list)
  `(cdr-of-cons (cdr-of-cons ,skip-list)))

(defmacro skip-list-element-next-0 (skip-list-element)
  `(atomic-reference-object
     (svref (skip-list-element-next ,skip-list-element) 0)))

(defmacro skip-list-element-next-n (skip-list-element level)
  `(atomic-reference-object
     (svref (skip-list-element-next ,skip-list-element) ,level)))

(defmacro def-skip-list (name &key
                              (constructor nil)
                              (reclaimer nil)
                              (clearer nil)
                              (accessor nil)
                              (accessor-given-hash nil)
                              (key-deleter nil)
                              (key-deleter-given-hash nil)
                              (set-if-no-entry-given-hash nil)
                              (hash-function 'sxhashw)
                              (key-comparitor 'eq)
                              (key-reclaimer nil)
                              (entry-reclaimer nil)
                              (flattener nil)
                              (max-level 31))
  (if (not (symbolp name))
      (error "The name argument, ~s, to def-skip-list was not a symbol."
             name))
  (let* ((constructor-name
           (or constructor
               (intern (format nil "MAKE-~a-SKIP-LIST" name))))
         (sentinel-constructor (intern (format nil "MAKE-~a-SKIP-LIST-SENTINEL" name)))
         (reclaimer-name
           (or reclaimer
               (intern (format nil "RECLAIM-~a-SKIP-LIST" name))))
         (clear-name
           (or clearer
               (intern (format nil "CLEAR-~a-SKIP-LIST" name))))
         (element-reclaimer-name (intern (format nil "RECLAIM-~a-NODES" name)))
         (accessor-name (or accessor (intern (format nil "GET-~a" name))))
         (mutator-name (intern (format nil "SET-~a-SKIP-LIST-VALUE" name)))
         (mutator-given-hash
           (if accessor-given-hash
               (intern (format nil "SET-~a" accessor-given-hash))))
         (deleter-name (or key-deleter (intern (format nil "DELETE-~a" name))))
         (flattener-name (or flattener (intern (format nil "FLATTEN-~a" name))))
         (entry-mutator?
           (if (or key-reclaimer entry-reclaimer)
               (intern (format nil "MUTATE-~a-SKIP-LIST-ENTRY" name))
               nil))
         (entry-mutator-var?
           (if entry-mutator?
               (intern (format nil "FP-~a" entry-mutator?))
               nil))
         (skip-list-variable (intern (format nil "~a-SKIP-LIST" name))))
  `(progn

     (defmacro ,constructor-name ()
       (let ((head (make-symbol "HEAD"))
             (tail (make-symbol "TAIL")))
         `(let* ((,tail (,',sentinel-constructor most-positive-fixnum nil))
                 (,head (,',sentinel-constructor most-negative-fixnum ,tail)))
            ;; see macros SKIP-LIST-HEAD & SKIP-LIST-TAIL
            (lookup-cons-macro ',',name (lookup-cons-macro ,head ,tail)))))

     (defun-simple ,sentinel-constructor (hash tail)
       (let ((node (make-skip-list-element hash
					   'sentinel-node
					   (if tail 'head 'tail)
					   ,max-level))
             (next (allocate-managed-simple-vector-for-skip-list ,(1+f max-level))))
         (loop for i from 0 to ,max-level do
           (setf (svref next i) (make-atomic-reference tail)))
         (setf (skip-list-element-next node) next)
         node))

     ,@(when entry-mutator?
         `((defun-void ,entry-mutator? (node new-key new-entry)
             ,@(if key-reclaimer
                   `((,key-reclaimer (skip-list-element-key node)))
                   nil)
             ,@(if entry-reclaimer
                   `((,entry-reclaimer (skip-list-element-entry node)))
                   nil)
             (setf (skip-list-element-key node) new-key)
             (setf (skip-list-element-entry node) new-entry))
           (defparameter ,entry-mutator-var? #',entry-mutator?)))

     ,@(when accessor-given-hash
         `((defmacro ,accessor-given-hash
                     (key ,skip-list-variable hash)
             (if (or (constantp key) (symbolp key))
                 #-development
                 `(lookup-skip-list-entry-macro
                    (cdr ,,skip-list-variable)
                    ,,max-level
                    ,',key-comparitor
                    ,key
                    ,hash)
                 #+development
                 `(lookup-skip-list-entry
                    (cdr ,,skip-list-variable)
                    ,,max-level
                    ',',key-comparitor
                    ,key
                    ,hash)
                 (let ((key-var (gensym)))
                   `(let ((,key-var ,key))
                      #-development
                      (lookup-skip-list-entry-macro
                        (cdr ,,skip-list-variable)
                        ,,max-level
                        ,',key-comparitor
                        ,key-var
                        ,hash)
                      #+development
                      (lookup-skip-list-entry
                        (cdr ,,skip-list-variable)
                        ,,max-level
                        ',',key-comparitor
                        ,key-var
                        ,hash)))))

           (defmacro ,mutator-given-hash
                     (key ,skip-list-variable hash entry)
             (if (or (constantp key) (symbolp key))
                 `(set-skip-list-entry
                    ,,skip-list-variable
                    ,,max-level
                    ',',key-comparitor
                    ,',entry-mutator-var?
                    t ; mutate-old-entry?
                    ,key
                    ,hash
                    ,entry)
                 (let ((key-var (gensym)))
                   `(let ((,key-var ,key))
                      (set-skip-list-entry
                        ,,skip-list-variable
                        ,,max-level
                        ',',key-comparitor
                        ,',entry-mutator-var?
                        t ; mutate-old-entry?
                        ,key-var
                        ,hash
                        ,entry)))))

           (defsetf ,accessor-given-hash ,mutator-given-hash)))

     ,@(when set-if-no-entry-given-hash
         `((defmacro ,set-if-no-entry-given-hash (key ,skip-list-variable hash entry)
             (if (or (constantp key) (symbolp key))
                 `(set-skip-list-entry
                    ,,skip-list-variable
                    ,,max-level
                    ',',key-comparitor
                    nil ; mutator-function?
                    nil ; mutate-old-entry?
                    ,key
                    ,hash
                    ,entry)
                 (let ((key-var (gensym)))
                   `(let ((,key-var ,key))
                      (set-skip-list-entry
                        ,,skip-list-variable
                        ,,max-level
                        ',',key-comparitor
                        nil ; mutator-function?
                        nil ; mutate-old-entry?
                        ,key-var
                        ,hash
                        ,entry)))))))

     (defmacro ,accessor-name (key ,skip-list-variable)
       (if (or (constantp key) (symbolp key))
           #-development
           `(lookup-skip-list-entry-macro
              (cdr ,,skip-list-variable)
              ,,max-level
              ,',key-comparitor
              ,key
              (,',hash-function ,key))
           #+development
           `(lookup-skip-list-entry
              (cdr ,,skip-list-variable)
              ,,max-level
              ',',key-comparitor
              ,key
              (,',hash-function ,key))
           (let ((key-evaled (gensym)))
             `(let ((,key-evaled ,key))
                #-development
                (lookup-skip-list-entry-macro
                  (cdr ,,skip-list-variable)
                  ,,max-level
                  ,',key-comparitor
                  ,key-evaled
                  (,',hash-function ,key-evaled))
                #+development
                (lookup-skip-list-entry
                  (cdr ,,skip-list-variable)
                  ,,max-level
                  ',',key-comparitor
                  ,key-evaled
                  (,',hash-function ,key-evaled))))))

     (defmacro ,mutator-name (key ,skip-list-variable entry)
       (let ((key-evaled (gensym)))
         `(let ((,key-evaled ,key))
            (set-skip-list-entry
              ,,skip-list-variable
              ,,max-level
              ',',key-comparitor
              ,',entry-mutator-var?
              t ; mutate-old-entry?
              ,key-evaled
              (,',hash-function ,key-evaled)
              ,entry))))

     (defsetf ,accessor-name ,mutator-name)

     (defmacro ,deleter-name (key ,skip-list-variable)
       ,(if (and (null key-reclaimer) (null entry-reclaimer))
            `(if (or (symbolp key) (constantp key))
                 `(progn
                    (delete-skip-list-entry
                      #',',key-comparitor
                      ,key
                      ,,skip-list-variable
                      ,,max-level
                      (,',hash-function ,key))
                    nil)
                 (let ((key-evaled (gensym)))
                   `(let ((,key-evaled ,key))
                      (delete-skip-list-entry
                        #',',key-comparitor
                        ,key-evaled
                        ,,skip-list-variable
                        ,,max-level
                        (,',hash-function ,key-evaled))
                      nil)))
            ``(multiple-value-bind (old-key old-entry)
                  ,(if (or (symbolp key) (constantp key))
                       `(delete-skip-list-entry
                          #',',key-comparitor
                          ,key
                          ,,skip-list-variable
                          ,,max-level
                          (,',hash-function ,key))
                       (let ((key-evaled (gensym)))
                         `(let ((,key-evaled ,key))
                            (delete-skip-list-entry
                              #',',key-comparitor
                              ,key-evaled
                              ,,skip-list-variable
                              ,,max-level
                              (,',hash-function ,key-evaled)))))
                ,@',(cond ((null key-reclaimer)
                           `((declare (ignore old-key))
                             (when old-entry (,entry-reclaimer old-entry))))
                          ((null entry-reclaimer)
                           `((declare (ignore old-entry))
                             (when old-key (,key-reclaimer old-key))))
                          (t
                           `((when old-key (,key-reclaimer old-key))
                             (when old-entry (,entry-reclaimer old-entry)))))
                nil)))

     ,@(if key-deleter-given-hash
           `((defmacro ,key-deleter-given-hash
                        (key ,skip-list-variable key-hash)
               ,(if (and (null key-reclaimer) (null entry-reclaimer))
                    ``(progn
                        (delete-skip-list-entry
                          #',',key-comparitor
                          ,key
                          ,,skip-list-variable
                          ,,max-level
                          ,key-hash)
                        nil)
                    ``(multiple-value-bind (old-key old-entry)
                          (delete-skip-list-entry
                            #',',key-comparitor
                            ,key
                            ,,skip-list-variable
                            ,,max-level
                            ,key-hash)
                        ,@',(cond ((null key-reclaimer)
                                   `((declare (ignore old-key))
                                     (when old-entry (,entry-reclaimer old-entry))))
                                  ((null entry-reclaimer)
                                   `((declare (ignore old-entry))
                                     (when old-key (,key-reclaimer old-key))))
                                  (t
                                   `((when old-key (,key-reclaimer old-key))
                                     (when old-entry (,entry-reclaimer old-entry)))))
                        nil)))))

     ,@(unless (or key-reclaimer entry-reclaimer)
	 `((defun-simple ,element-reclaimer-name (,skip-list-variable tail)
	     (loop until (eq ,skip-list-variable tail)
		   for next-element = (skip-list-element-next-0 ,skip-list-variable)
		   for key = (skip-list-element-key ,skip-list-variable)
		   for entry = (skip-list-element-entry ,skip-list-variable)
		   do
	       (reclaim-skip-list-element ,skip-list-variable)
	       ,@(when key-reclaimer
		   `((,key-reclaimer key)))
	       ,@(when entry-reclaimer
		   `((,entry-reclaimer entry)))
               (setq ,skip-list-variable next-element)))))

     ;; Note that the reclaimer and clearing functions delete a tree by
     ;; repeatedly deleting the first key in the root element of the tree when
     ;; there are reclaimers for either the key or the entry.  This is done
     ;; since the reclaimers for the keys or entries may further mutate this
     ;; binary tree, rebalancing it in the process.  The old reclaimers
     ;; experienced bugs in rules because of this.

     (def-substitution-macro ,reclaimer-name (,skip-list-variable)
       (progn
         ,(if (or key-reclaimer entry-reclaimer)
            `(loop with head = (skip-list-head ,skip-list-variable)
                   with tail = (skip-list-tail ,skip-list-variable)
                   for element? = (skip-list-element-next-0 head)
                   for key? = (skip-list-element-key element?)
                   while (neq element? tail)
                   do
               (,deleter-name key? ,skip-list-variable)
                   finally
                     (reclaim-skip-list-element head)
                     (reclaim-skip-list-element tail)
                     (setf (cddr ,skip-list-variable) nil)
                     (setf (cadr ,skip-list-variable) nil)
                     (setf (car ,skip-list-variable) nil)
                     (reclaim-lookup-list-macro ,skip-list-variable))
            `(let* ((head (skip-list-head ,skip-list-variable))
                    (tail (skip-list-tail ,skip-list-variable))
                    (element? (skip-list-element-next-0 head)))
               (when (neq element? tail)
                 (,element-reclaimer-name element? tail))
               (reclaim-skip-list-element head)
               (reclaim-skip-list-element tail)
               (setf (cddr ,skip-list-variable) nil)
               (setf (cadr ,skip-list-variable) nil)
               (setf (car ,skip-list-variable) nil)
               (reclaim-lookup-list-macro ,skip-list-variable)))))

     (defun-simple ,clear-name (,skip-list-variable)
       ,(if (or key-reclaimer entry-reclaimer)
            `(loop with head = (skip-list-head ,skip-list-variable)
                   with tail = (skip-list-tail ,skip-list-variable)
                   for element? = (skip-list-element-next-0 head)
                   for key? = (skip-list-element-key element?)
                   while (neq element? tail)
                   do
               (,deleter-name key? ,skip-list-variable))
            `(let* ((head (skip-list-head ,skip-list-variable))
                    (tail (skip-list-tail ,skip-list-variable))
                    (element? (skip-list-element-next-0 head)))
               (when (neq element? tail)
                 (,element-reclaimer-name element? tail))))
       ,skip-list-variable)

     (defmacro ,flattener-name (,skip-list-variable)
       `(flatten-skip-list (cdr ,,skip-list-variable)))

     ',name)))

(defun flatten-skip-list (skip-list)
  (gensym-dstruct-bind ((head . tail) skip-list)
    (loop for node = (skip-list-element-next-0 head)
                   then (skip-list-element-next-0 node)
          until (eq node tail)
          collect (early-eval-cons
                    (skip-list-element-key node)
                    (skip-list-element-entry node))
          using early-eval-cons)))

(declare-side-effect-free-function lookup-skip-list-entry)

#+SymScale
(defun-simple lookup-skip-list-entry (skip-list-element max-level key-comparitor key key-hash)
  (declare (type fixnum key-hash max-level))
  (let ((bottom-level 0)
        (marked nil)
        (pred (car-of-cons skip-list-element)) ; head
        (curr nil)
        (succ nil))
    (loop for level from max-level downto bottom-level do
      (setq curr (skip-list-element-next-n pred level))
      (loop
        (multiple-value-setq (succ marked)
            (get-atomic-reference (svref (skip-list-element-next curr) level)))
        (loop while marked do
          (setq curr (skip-list-element-next-n pred level))
          (multiple-value-setq (succ marked)
              (get-atomic-reference (svref (skip-list-element-next curr) level))))
	(let ((entry-hash (skip-list-element-hash-number curr)))
	  (if (or (<f entry-hash key-hash)
		  (and (=f entry-hash key-hash)
		       (not
			 (let ((entry-key (skip-list-element-key curr)))
			   (cond ((eq key-comparitor 'equal)
				  (equal key entry-key))
				 ((eq key-comparitor 'string=)
				  (string= key entry-key))
				 ((eq key-comparitor 'equal-rule-context)
				  (equal-rule-context key entry-key))
				 (t
				  (funcall key-comparitor key entry-key)))))))
	      (setq pred curr
		    curr succ)
	    (return)))))
    (when (=f (skip-list-element-hash-number curr) key-hash)
      (let ((entry-key (skip-list-element-key curr)))
        (when (cond ((eq key-comparitor 'equal)
                     (equal key entry-key))
                    ((eq key-comparitor 'string=)
                     (string= key entry-key))
                    ((eq key-comparitor 'equal-rule-context)
                     (equal-rule-context key entry-key))
                    (t
                     (funcall key-comparitor key entry-key)))
          (skip-list-element-entry curr))))))

#-SymScale
(defun-simple lookup-skip-list-entry (skip-list-element max-level key-comparitor key key-hash)
  (declare (type fixnum key-hash max-level))
  (let ((bottom-level 0)
        (pred (car-of-cons skip-list-element)) ; head
        (curr nil))
    (loop for level from max-level downto bottom-level do
      (setq curr (skip-list-element-next-n pred level))
      (loop as entry-hash = (skip-list-element-hash-number curr)
	    do
	(if (or (<f entry-hash key-hash)
		(and (=f entry-hash key-hash)
		     (not
		       (let ((entry-key (skip-list-element-key curr)))
			 (cond ((eq key-comparitor 'equal)
				(equal key entry-key))
			       ((eq key-comparitor 'string=)
				(string= key entry-key))
			       ((eq key-comparitor 'equal-rule-context)
				(equal-rule-context key entry-key))
			       (t
				(funcall key-comparitor key entry-key)))))))
	    (setq pred curr
		  curr (skip-list-element-next-n curr level))
	  (return))))
    (when (=f (skip-list-element-hash-number curr) key-hash)
      (let ((entry-key (skip-list-element-key curr)))
        (when (cond ((eq key-comparitor 'equal)
                     (equal key entry-key))
                    ((eq key-comparitor 'string=)
                     (string= key entry-key))
                    ((eq key-comparitor 'equal-rule-context)
                     (equal-rule-context key entry-key))
                    (t
                     (funcall key-comparitor key entry-key)))
          (skip-list-element-entry curr))))))

#+SymScale
(defmacro lookup-skip-list-entry-macro (skip-list-element max-level key-comparitor key key-hash)
  (let ((skip-list (make-symbol "SKIP-LIST"))
        (key-value (make-symbol "KEY-VALUE"))
        (key-hash-value (make-symbol "KEY-HASH-VALUE"))
        (entry-hash (make-symbol "ENTRY-HASH"))
        (bottom-level (make-symbol "BOTTOM-LEVEL"))
        (level (make-symbol "LEVEL"))
        (marked (make-symbol "MARKED"))
        (pred (make-symbol "PRED"))
        (curr (make-symbol "CURR"))
        (succ (make-symbol "SUCC")))
    `(let* ((,skip-list ,skip-list-element)
            (,key-value ,key)
            (,key-hash-value ,key-hash)
            (,bottom-level 0)
            (,marked nil)
            (,pred (car-of-cons ,skip-list))
            (,curr nil)
            (,succ nil))
       (declare (type fixnum ,key-hash-value))
       (loop for ,level from ,max-level downto ,bottom-level do
         (setq ,curr (skip-list-element-next-n ,pred ,level))
         (loop
           (multiple-value-setq (,succ ,marked)
             (get-atomic-reference (svref (skip-list-element-next ,curr) ,level)))
           (loop while ,marked do
             (setq ,curr (skip-list-element-next-n ,pred ,level))
             (multiple-value-setq (,succ ,marked)
               (get-atomic-reference (svref (skip-list-element-next ,curr) ,level))))
	   (let ((,entry-hash (skip-list-element-hash-number ,curr)))
	     (if (or (<f ,entry-hash ,key-hash-value)
		     (and (=f ,entry-hash ,key-hash-value)
			  (not (,key-comparitor ,key-value (skip-list-element-key ,curr)))))
		 (setq ,pred ,curr
		       ,curr ,succ)
	       (return)))))
       (when (=f (skip-list-element-hash-number ,curr) ,key-hash-value)
	 (when (,key-comparitor ,key-value (skip-list-element-key ,curr))
	   (skip-list-element-entry ,curr))))))

#-SymScale
(defmacro lookup-skip-list-entry-macro (skip-list-element max-level key-comparitor key key-hash)
  (let ((skip-list (make-symbol "SKIP-LIST"))
        (key-value (make-symbol "KEY-VALUE"))
        (key-hash-value (make-symbol "KEY-HASH-VALUE"))
        (entry-hash (make-symbol "ENTRY-HASH"))
        (bottom-level (make-symbol "BOTTOM-LEVEL"))
        (level (make-symbol "LEVEL"))
        (pred (make-symbol "PRED"))
        (curr (make-symbol "CURR")))
    `(let* ((,skip-list ,skip-list-element)
            (,key-value ,key)
            (,key-hash-value ,key-hash)
            (,bottom-level 0)
            (,pred (car-of-cons ,skip-list))
            (,curr nil))
       (declare (type fixnum ,key-hash-value))
       (loop for ,level from ,max-level downto ,bottom-level do
         (setq ,curr (skip-list-element-next-n ,pred ,level))
         (loop as ,entry-hash = (skip-list-element-hash-number ,curr)
	       do
	   (if (or (<f ,entry-hash ,key-hash-value)
		   (and (=f ,entry-hash ,key-hash-value)
			(not (,key-comparitor ,key-value (skip-list-element-key ,curr)))))
	       (setq ,pred ,curr
		     ,curr (skip-list-element-next-n ,curr ,level))
	     (return))))
       (when (=f (skip-list-element-hash-number ,curr) ,key-hash-value)
	 (when (,key-comparitor ,key-value (skip-list-element-key ,curr))
	   (skip-list-element-entry ,curr))))))

(defmacro make-skip-list-node (hash key entry height)
  (let ((node (make-symbol "NODE"))
        (next (make-symbol "NEXT")))
    `(let* ((,node (make-skip-list-element ,hash ,key ,entry ,height))
            (,next (allocate-managed-simple-vector-for-skip-list (1+f ,height))))
       (setf (skip-list-element-next ,node) ,next)
       ,node)))

(defconstant half-of-most-positive-fixnum (floorf most-positive-fixnum 2))

(defun-simple random-level (max-level)
  (declare (type fixnum max-level))
  (loop with level = 0
        while (and (<f (*f 2 (current-system-case
                               (ab #+development (random half-of-most-positive-fixnum)
                                   #-development (g2-random half-of-most-positive-fixnum))
                               (t (random half-of-most-positive-fixnum))))
                       half-of-most-positive-fixnum)
                   (<f level max-level))
        do (incff level)
        finally (return level)))

(defconstant skip-list-global-max-level 32)
(defvar skip-list-find-preds (make-array skip-list-global-max-level))
(defvar skip-list-find-succs (make-array skip-list-global-max-level))

#+SymScale
(defun-simple skip-list-find (skip-list max-level key-comparitor key hash preds succs)
  (let ((bottom-level 0)
        marked snip
        pred curr succ)
    (tagbody retry
      (loop
        (setq pred skip-list)
        (loop for level from max-level downto bottom-level do
          (setq curr (skip-list-element-next-n pred level))
          (loop for next = (skip-list-element-next curr)
		do
            (multiple-value-setq (succ marked)
              (get-atomic-reference (svref next level)))
            (loop while marked do
              (setq snip (compare-and-swap (svref (skip-list-element-next pred) level)
                                           (make-atomic-reference curr)
                                           (make-atomic-reference succ)))
              (unless snip (go retry))
              (setq curr (skip-list-element-next-n pred level))
              (multiple-value-setq (succ marked)
                (get-atomic-reference (svref (skip-list-element-next curr) level))))
	    (let ((entry-hash (skip-list-element-hash-number curr)))
	      (if (or (<f entry-hash hash)
		      ;; this only happens at bottom level
		      (and (=f entry-hash hash)
			   (not
			     (let ((entry-key (skip-list-element-key curr)))
			       (cond ((eq key-comparitor 'equal)
				      (equal key entry-key))
				     ((eq key-comparitor 'string=)
				      (string= key entry-key))
				     ((eq key-comparitor 'equal-rule-context)
				      (equal-rule-context key entry-key))
				     (t
				      (funcall key-comparitor key entry-key)))))))
		  (setq pred curr
			curr succ)
		(return))))
          (setf (svref preds level) pred
                (svref succs level) curr))
        (return-from skip-list-find
          (when (and (=f (skip-list-element-hash-number curr) hash)
		     (let ((entry-key (skip-list-element-key curr)))
		       (cond ((eq key-comparitor 'equal)
			      (equal key entry-key))
			     ((eq key-comparitor 'string=)
			      (string= key entry-key))
			     ((eq key-comparitor 'equal-rule-context)
			      (equal-rule-context key entry-key))
			     (t
			      (funcall key-comparitor key entry-key)))))
            curr)))))) ; return current node

#-SymScale
(defun-simple skip-list-find (skip-list max-level key-comparitor key hash preds succs)
  (let ((bottom-level 0)
	(pred skip-list)
	curr)
    (loop for level from max-level downto bottom-level do
      (setq curr (skip-list-element-next-n pred level))
      (loop as entry-hash = (skip-list-element-hash-number curr)
	    do
	(if (or (<f entry-hash hash)
		;; this only happens at bottom level
		(and (=f entry-hash hash)
		     (not
		       (let ((entry-key (skip-list-element-key curr)))
			 (cond ((eq key-comparitor 'equal)
				(equal key entry-key))
			       ((eq key-comparitor 'string=)
				(string= key entry-key))
			       ((eq key-comparitor 'equal-rule-context)
				(equal-rule-context key entry-key))
			       (t
				(funcall key-comparitor key entry-key)))))))
	    (setq pred curr
		  curr (skip-list-element-next-n curr level))
	  (return)))
      (setf (svref preds level) pred
	    (svref succs level) curr))
    (when (and (=f (skip-list-element-hash-number curr) hash)
	       (let ((entry-key (skip-list-element-key curr)))
		       (cond ((eq key-comparitor 'equal)
			      (equal key entry-key))
			     ((eq key-comparitor 'string=)
			      (string= key entry-key))
			     ((eq key-comparitor 'equal-rule-context)
			      (equal-rule-context key entry-key))
			     (t
			      (funcall key-comparitor key entry-key)))))
      curr)))

#+SymScale
(defun-simple set-skip-list-entry
       (skip-list max-level key-comparitor mutator-function? mutate-old-entry?
	key key-hash entry)
  (declare (type fixnum key-hash max-level))
  (let* ((bottom-level 0)
	 (head (skip-list-head skip-list))
	 (preds skip-list-find-preds)
	 (succs skip-list-find-succs))
    (loop as insertion-point
	     = (skip-list-find head max-level key-comparitor key key-hash preds succs)
	  do
      (when insertion-point
	(if mutate-old-entry?
	    (if mutator-function?
		(funcall-simple-compiled-function
		  mutator-function? insertion-point key entry)
	      (progn
		(setf (skip-list-element-key insertion-point) key)
		(setf (skip-list-element-entry insertion-point) entry)))
	  (setq entry (skip-list-element-entry insertion-point)))
	(return-from set-skip-list-entry entry))
      (let* ((pred (svref preds bottom-level))
	     (top-level (if (=f (skip-list-element-hash-number pred) key-hash)
			    ;; if the hash is duplicated with previous node, the level is:
			    (skip-list-element-top-level pred)
			  (random-level max-level)))
	     (new-node (make-skip-list-node key-hash key entry top-level)))
	(loop for level from bottom-level to top-level do
	  (setf (svref (skip-list-element-next new-node) level)
		(make-atomic-reference (svref succs level))))
	(let ((succ (svref succs bottom-level)))
	  (if (compare-and-swap (svref (skip-list-element-next pred) bottom-level)
				(make-atomic-reference succ)
				(make-atomic-reference new-node))
	      (progn
		(loop for level from (1+f bottom-level) to top-level do
		  (loop
		    (setq pred (svref preds level)
			  succ (svref succs level))
		    (when (compare-and-swap (svref (skip-list-element-next pred) level)
					    (make-atomic-reference succ)
					    (make-atomic-reference new-node))
		      (return nil))
		    (skip-list-find head max-level key-comparitor key key-hash preds succs)))
		(return-from set-skip-list-entry entry))
	    ;; Failed CAS means previous node is not pred any more, need to reclaim
	    ;; the new node and go over the whole process again.
	    (progn
	      (reclaim-skip-list-element new-node))))))))

#-SymScale
(defun-simple set-skip-list-entry
       (skip-list max-level key-comparitor mutator-function? mutate-old-entry?
	key key-hash entry)
  (declare (type fixnum key-hash max-level))
  (let* ((bottom-level 0)
	 (head (skip-list-head skip-list))
	 (preds skip-list-find-preds)
	 (succs skip-list-find-succs)
	 (insertion-point
	  (skip-list-find head max-level key-comparitor key key-hash preds succs)))
    (if insertion-point
	(if mutate-old-entry?
	    (if mutator-function?
		(funcall-simple-compiled-function
		  mutator-function? insertion-point key entry)
	      (progn
		(setf (skip-list-element-key insertion-point) key)
		(setf (skip-list-element-entry insertion-point) entry)))
	  (setq entry (skip-list-element-entry insertion-point)))
      (let* ((pred-0 (svref preds bottom-level))
	     (top-level (if (=f (skip-list-element-hash-number pred-0) key-hash)
			    ;; if the hash is duplicated with previous node
			    (skip-list-element-top-level pred-0)
			  (random-level max-level)))
	     (new-node (make-skip-list-node key-hash key entry top-level)))
	(loop for level from bottom-level to top-level
	      for succ = (svref succs level)
	      for pred = (svref preds level)
	      do
	  (setf (svref (skip-list-element-next new-node) level) succ)
	  (setf (svref (skip-list-element-next pred) level) new-node))))
    entry))

;; TODO: there must be bugs in this function. --binghe
#+SymScale
(defun delete-skip-list-entry (comparitor key skip-list max-level key-hash)
  (declare (type fixnum max-level key-hash))
  (let* ((bottom-level 0)
	 (head (skip-list-head skip-list))
	 (preds skip-list-find-preds)
	 (succs skip-list-find-succs))
    ;; note: there's no LOOP in single-thread version
    (loop as deletion-point
	     = (skip-list-find head max-level comparitor key key-hash preds succs)
	  doing
      (when (null deletion-point)
	(return-from delete-skip-list-entry (values nil nil)))

      (let ((node-to-remove (svref succs bottom-level))
	    (old-key (skip-list-element-key deletion-point))
	    (old-entry (skip-list-element-entry deletion-point))
            succ marked)
	#+development
	(unless (eq node-to-remove deletion-point)
	  (error "node-to-remove <> deletion-point ?!"))
        (loop for level from (skip-list-element-top-level node-to-remove)
                        downto (1+f bottom-level)
              do
          (multiple-value-setq (succ marked)
            (get-atomic-reference (svref (skip-list-element-next node-to-remove) level)))
          (loop while (not marked) do
            (compare-and-swap (svref (skip-list-element-next node-to-remove) level)
                              (make-atomic-reference succ nil)
                              (make-atomic-reference succ t))
            (multiple-value-setq (succ marked)
              (get-atomic-reference
                (svref (skip-list-element-next node-to-remove) level)))))
        (multiple-value-setq (succ marked)
          (get-atomic-reference
            (svref (skip-list-element-next node-to-remove) bottom-level)))
        (loop as i-marked-it =
              (compare-and-swap (svref (skip-list-element-next node-to-remove) bottom-level)
                                (make-atomic-reference succ nil)
                                (make-atomic-reference succ t))
              do
           (multiple-value-setq (succ marked)
             (get-atomic-reference (svref (skip-list-element-next (svref succs bottom-level))
                                          bottom-level)))
           (cond (i-marked-it
                  (skip-list-find head max-level comparitor key key-hash preds succs)
                  (return-from delete-skip-list-entry
                    (values old-key old-entry)))
                 (marked
                  ;; other threads has removed it first
                  (return-from delete-skip-list-entry
                    (values old-key old-entry)))))))))

#-SymScale
(defun delete-skip-list-entry (comparitor key skip-list max-level key-hash)
  (declare (type fixnum max-level key-hash))
  (let* ((bottom-level 0)
	 (head (skip-list-head skip-list))
	 (preds skip-list-find-preds)
	 (succs skip-list-find-succs)
	 (deletion-point
	   (skip-list-find head max-level comparitor key key-hash preds succs)))
    ;; return directly if didn't found the node.
    (when (null deletion-point)
      (return-from delete-skip-list-entry (values nil nil)))

    (let ((node-to-remove deletion-point)
	  (old-key (skip-list-element-key deletion-point))
	  (old-entry (skip-list-element-entry deletion-point)))
      ;; delete the node in the deletion-point variable.
      (loop for level from (skip-list-element-top-level node-to-remove)
		      downto bottom-level
	    for pred = (svref preds level)
	    doing
	(when (eq (skip-list-element-next-n pred level) node-to-remove)
	  (setf (svref (skip-list-element-next pred) level)
		(skip-list-element-next-n node-to-remove level))))

      ;; reclaim node element.
      (reclaim-skip-list-element node-to-remove)
      (values old-key old-entry))))

(defmacro skip-list-empty-p (skip-list)
  (let ((temp (gensym)))
    `(let ((,temp (cdr-of-cons ,skip-list)))
       (eq (skip-list-element-next-0 (car-of-cons ,temp))
           (cdr-of-cons ,temp)))))

(defmacro skip-list-p (thing)
  (let ((temp (gensym)))
    `(let ((,temp (cdr ,thing))) ; using CDR to allow thing to be NIL
       (and (consp ,temp)
            (simple-vector-p (car-of-cons ,temp))
            (simple-vector-p (cdr-of-cons ,temp))))))

(def-substitution-macro skip-list-or-binary-tree-empty-p (thing)
  (if (skip-list-p thing)
      (skip-list-empty-p thing)
    (binary-tree-empty-p thing)))

(define-loop-path skip-list-value
  expand-skip-list-or-binary-tree-value-loop-iterator (of))

(defun-for-macro expand-skip-list-or-binary-tree-value-loop-iterator
                 (method-name
                   iter-var iter-var-data-type prep-phrases inclusive?
                   allowed-preps method-specific-data)
  (declare (ignore method-name allowed-preps method-specific-data))
  (when inclusive?
    (error "The skip-list-or-binary-tree-value iteration path does not support ~
inclusive iterations."))
  (let* ((skip-list-or-binary-tree-form-entry (assq 'of prep-phrases))
         (skip-list-or-binary-tree-form (second skip-list-or-binary-tree-form-entry))
         (skip-list-form (loop-gentemp 'skip-list-form-))
         (binary-tree-form (loop-gentemp 'binary-tree-form-))
         (skip-list-p (loop-gentemp 'skip-list-p-))
         (node-stack (loop-gentemp 'node-stack-))
         (current-node (loop-gentemp 'current-node-))
         (next-node? (loop-gentemp 'next-node-))
         (tail-node (loop-gentemp 'tail-node-))
         (current-alist (loop-gentemp 'current-alist-))
         (entry-cons (loop-gentemp 'entry-cons-))
         (less-than-branch? (loop-gentemp 'less-than-branch?-))
         init-bindings
         prologue-forms
         (pre-step-tests nil)
         (steppings nil)
         post-step-tests
         post-step-settings)
    (when (null skip-list-or-binary-tree-form-entry)
      (error "The skip-list-or-binary-tree-value iteration path requires an ~
\"OF skip-list-or-binary-tree-form\"."))
    (when (or (not (symbolp iter-var)) (eq iter-var-data-type t))
      (setq iter-var-data-type nil))

    (setq init-bindings
          `((scope-conses scope-conses)
            (,node-stack nil)
            (,current-node nil)
            (,skip-list-form ,skip-list-or-binary-tree-form)
            (,binary-tree-form ,skip-list-or-binary-tree-form)
            (,skip-list-p (skip-list-p ,skip-list-or-binary-tree-form))
            (,next-node? nil)
            (,tail-node nil) 
            (,current-alist nil)
            (,entry-cons nil)
            ,(if iter-var-data-type
                 `(,iter-var nil ,iter-var-data-type)
                 `(,iter-var))))

    (setq prologue-forms
          `((cond (,skip-list-p
		   (setq ,next-node?
			 (skip-list-element-next-0 (skip-list-head ,skip-list-form))
			 ,tail-node
			 (skip-list-tail ,skip-list-form))
		   (when (eq ,next-node? ,tail-node)
		     (setq ,next-node? nil)))
		  (t ; binary-tree
		   (setq ,next-node? (cdr-of-cons ,binary-tree-form))))))

    (setq post-step-tests
          `(progn
             (cond
               (,current-alist
                (setq ,entry-cons (car-of-cons ,current-alist))
                (setq ,current-alist (cdr-of-cons ,current-alist)))
               (,skip-list-p
		(cond (,next-node?
		       (setq ,current-node ,next-node?)
		       (setq ,next-node? (skip-list-element-next-0 ,current-node))
		       (when (eq ,next-node? ,tail-node)
			 (setq ,next-node? nil))
		       (setq ,entry-cons
			     (scope-cons (skip-list-element-key ,current-node)
					 (skip-list-element-entry ,current-node))))
		      (t
		       (setq ,current-node nil))))
               (t
                (cond
                  (,next-node?
                   (setq ,current-node ,next-node?)
                   (loop for ,less-than-branch? = (less-than-branch
                                                    ,current-node)
                         while ,less-than-branch?
                         do
                     (setq ,node-stack (scope-cons ,current-node ,node-stack))
                     (setq ,current-node ,less-than-branch?)))
                  (,node-stack
                   (setq ,next-node? ,node-stack)
                   (setq ,current-node (car-of-cons ,node-stack))
                   (setq ,node-stack (cdr-of-cons ,node-stack)))
                  (t
                   (setq ,current-node nil)))
                (when ,current-node
                  (setq ,next-node? (greater-than-branch ,current-node))
                  (setq ,current-alist (binary-element-alist ,current-node))
                  (setq ,entry-cons (car-of-cons ,current-alist))
                  (setq ,current-alist (cdr-of-cons ,current-alist)))))
	     (null ,current-node)))

    ;; skip-list-entry-cons is different only in this part.
    (if (and (symbolp iter-var)
             iter-var-data-type
             (neq iter-var-data-type t))
        (setq post-step-settings
              `(,iter-var (the ,iter-var-data-type (cdr-of-cons ,entry-cons))))
        (setq post-step-settings
              `(,iter-var (cdr-of-cons ,entry-cons))))

    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

(define-loop-path skip-list-entry-cons
  expand-skip-list-or-binary-tree-entry-cons-loop-iterator (of))

(defun-for-macro expand-skip-list-or-binary-tree-entry-cons-loop-iterator
                 (method-name
                   iter-var iter-var-data-type prep-phrases inclusive?
                   allowed-preps method-specific-data)
  (declare (ignorable method-name allowed-preps iter-var-data-type method-specific-data))
  (when inclusive?
    (error "The skip-list-or-binary-tree-value iteration path does not support ~
inclusive iterations."))
  (let* ((skip-list-or-binary-tree-form-entry (assq 'of prep-phrases))
         (skip-list-or-binary-tree-form (second skip-list-or-binary-tree-form-entry))
         (skip-list-form (loop-gentemp 'skip-list-form-))
         (binary-tree-form (loop-gentemp 'binary-tree-form-))
         (skip-list-p (loop-gentemp 'skip-list-p-))
         (node-stack (loop-gentemp 'node-stack-))
         (current-node (loop-gentemp 'current-node-))
         (next-node? (loop-gentemp 'next-node-))
         (tail-node (loop-gentemp 'tail-node-))
         (current-alist (loop-gentemp 'current-alist-))
         (entry-cons (loop-gentemp 'entry-cons-))
         (less-than-branch? (loop-gentemp 'less-than-branch?-))
         init-bindings
         prologue-forms
         (pre-step-tests nil)
         (steppings nil)
         post-step-tests
         post-step-settings)
    (when (null skip-list-or-binary-tree-form-entry)
      (error "The skip-list-or-binary-tree-value iteration path requires an ~
\"OF skip-list-or-binary-tree-form\"."))

    (setq init-bindings
          `((scope-conses scope-conses)
            (,node-stack nil)
            (,current-node nil)
            (,skip-list-form ,skip-list-or-binary-tree-form)
            (,binary-tree-form ,skip-list-or-binary-tree-form)
            (,skip-list-p (skip-list-p ,skip-list-or-binary-tree-form))
            (,next-node? nil)
            (,tail-node nil) 
            (,current-alist nil)
            (,entry-cons nil)
            (,iter-var)))

    (setq prologue-forms
          `((cond (,skip-list-p
		   (setq ,next-node?
			 (skip-list-element-next-0 (skip-list-head ,skip-list-form))
			 ,tail-node
			 (skip-list-tail ,skip-list-form))
		   (when (eq ,next-node? ,tail-node)
		     (setq ,next-node? nil)))
		  (t ; binary-tree
		   (setq ,next-node? (cdr-of-cons ,binary-tree-form))))))

    (setq post-step-tests
          `(progn
             (cond
               (,current-alist
                (setq ,entry-cons (car-of-cons ,current-alist))
                (setq ,current-alist (cdr-of-cons ,current-alist)))
               (,skip-list-p
		(cond (,next-node?
		       (setq ,current-node ,next-node?)
		       (setq ,next-node? (skip-list-element-next-0 ,current-node))
		       (when (eq ,next-node? ,tail-node)
			 (setq ,next-node? nil))
		       (setq ,entry-cons
			     (scope-cons (skip-list-element-key ,current-node)
					 (skip-list-element-entry ,current-node))))
		      (t
		       (setq ,current-node nil))))
               (t
                (cond
                  (,next-node?
                   (setq ,current-node ,next-node?)
                   (loop for ,less-than-branch? = (less-than-branch
                                                    ,current-node)
                         while ,less-than-branch?
                         do
                     (setq ,node-stack (scope-cons ,current-node ,node-stack))
                     (setq ,current-node ,less-than-branch?)))
                  (,node-stack
                   (setq ,next-node? ,node-stack)
                   (setq ,current-node (car-of-cons ,node-stack))
                   (setq ,node-stack (cdr-of-cons ,node-stack)))
                  (t
                   (setq ,current-node nil)))
                (when ,current-node
                  (setq ,next-node? (greater-than-branch ,current-node))
                  (setq ,current-alist (binary-element-alist ,current-node))
                  (setq ,entry-cons (car-of-cons ,current-alist))
                  (setq ,current-alist (cdr-of-cons ,current-alist)))))
	     (null ,current-node)))

    (setq post-step-settings
          `(,iter-var ,entry-cons))

    ;; Return a list of the six path elements.
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

;; Skip list pretty printer, it assumes single char keys for showing up pretty.
#+development
(defun describe-skip-list (skip-list)
  (let ((head (skip-list-head skip-list))
        (tail (skip-list-tail skip-list))
        (level-list nil)
        (max-level 0)
        (element-list nil)
        (n-element 0)
        (print-limit 26))
    ;; get level 0 element first
    (loop for node = (skip-list-element-next-0 head)
                then (skip-list-element-next-0 node)
          until (eq node tail)
          maximize (skip-list-element-top-level node) into m
          finally (setq max-level m)
          do
      (push (skip-list-element-top-level node) level-list)
      (push (skip-list-element-key node) element-list)
      (incf n-element))
    (setq level-list (nreverse level-list))
    (setq element-list (nreverse element-list))
    (unless level-list
      (format t ";;;  Skip-list is empty.~%")
      (return-from describe-skip-list))
    ;; title
    (format t ";;;  Head nodes")
    (loop with node = head
          with done = nil
          for j on level-list
          for n = 1 then (1+ n)
          until (or (eq node tail) (> n print-limit))
          finally (unless done (terpri))
          do
      (cond ((=f n 1)
             nil)      ; "nodes", no spaces
            ((=f n 2)
             (format t "     ")) ; no spaces
            ((=f (car j) max-level)
             (format t "Index nodes~%")
             (setq done t)
             (return))
            (t (format t "     "))))
    ;; body
    (loop for i from max-level downto 0 do
      ;; 1st round:
      (if (<f i 10)
          (format t ";;;  +-+  ")
          (format t ";;;  +--+ "))
      (loop with node = head
            with nex-p = nil
            for j on level-list
            for n = 1 then (1+f n)
            until (or (eq node tail) (>f n print-limit))
            do
        (if (>=f (car j) i)
            (progn
              (setq node (skip-list-element-next-n node i))
              (format t "+-+  "))
          (cond ((and (=f n 1) (<f (or (cadr j) most-positive-fixnum) i))
                 (format t "  nex")
                 (setq nex-p t))
                ((and (=f n 2) nex-p)
                 (format t "t    "))
                (t
                 (format t "     ")))))
      (terpri)
      ;; 2nd round:
      (if (<f i 10)
          (format t ";;;  |~D|-" i)
          (format t ";;;  |~D|" i))
      (princ (if (>= (car level-list) i) ">" "-"))
      (loop with node = head
            for j on level-list
            for n = 1 then (1+ n)
            until (or (eq node tail) (> n print-limit))
            do
        (if (>=f (car j) i)
            (progn
              (setq node (skip-list-element-next-n node i))
              (if (=f i 0)
		  (format t "|~A|-" (skip-list-element-key node))
		(format t "|~A|-" (skip-list-element-entry node))))
          (format t "----"))
        (princ (if (>= (or (cadr j) most-positive-fixnum) i) ">" "-")))
      (if (>f n-element print-limit)
          (format t "...~%")
        (format t "null~%"))
      ;; 3rd round
      (if (<f i 10)
          (format t ";;;  +-+  ")
          (format t ";;;  +--+ "))
      (loop with node = head
            for j on level-list
            for n = 1 then (1+ n)
            until (or (eq node tail) (> n print-limit))
            do
        (if (>=f (car j) i)
            (progn
              (setq node (skip-list-element-next-n node i))
              (format t "+-+  "))
          (format t "     ")))
      (terpri)
      ;; 4th round (i /= 0)
      (when (=f i 0) (return))
      (format t ";;;   |   ")
      (loop with node = head
            for j on level-list
            for n = 1 then (1+ n)
            until (or (eq node tail) (>f n print-limit))
            do
        (if (>=f (car j) i)
            (progn
              (setq node (skip-list-element-next-n node i))
              (format t " |   "))
          (format t "     ")))
      (terpri))
    (terpri)
    element-list))

#+development
(defun describe-large-skip-list (skip-list)
  (let ((head (skip-list-head skip-list))
        (tail (skip-list-tail skip-list))
        (level-list nil)
        (max-level 0)
        (element-list nil)
        (n-element 0))
    ;; get level 0 element first
    (loop for node = (skip-list-element-next-0 head)
                then (skip-list-element-next-0 node)
          until (eq node tail)
          maximize (skip-list-element-top-level node) into m
          finally (setq max-level m)
          do
      (push (skip-list-element-top-level node) level-list)
      (push (skip-list-element-key node) element-list)
      (incf n-element))
    (setq level-list (nreverse level-list))
    (setq element-list (nreverse element-list))
    ;; print the table
    (unless level-list
      (format t "Skip-list is empty.~%")
      (return-from describe-large-skip-list))
    (loop for i from max-level downto 0 do
      (format t "Level ~2D: " i)
      (loop with node = head
            for j in level-list
            for n = 1 then (1+ n)
            until (eq node tail)
            do
        (if (>= j i)
            (format t "#")
            (format t " ")))
      (terpri))
    (terpri)
    element-list))

;; A compatibility layer for exist binary trees.
(defmacro def-skip-list-or-binary-tree
    (name &key (constructor nil)
               (reclaimer nil)
               (clearer nil)
               (accessor nil)
               (accessor-given-hash nil)
               (key-deleter nil)
               (key-deleter-given-hash nil)
               (set-if-no-entry-given-hash nil)
               (hash-function 'sxhashw)
               (key-comparitor 'eq)
               (key-reclaimer nil)
               (entry-reclaimer nil)
               (flattener nil)
               (max-level 31)
               (use-binary-tree nil))
  (declare (ignorable max-level use-binary-tree))
  (let ((use-skip-list
         (current-system-case
           (ab #+skip-list (not use-binary-tree)
               #-skip-list nil)
           (t nil))))
    `(,(if use-skip-list
           'def-skip-list
           'def-binary-tree)
      ,name
      :constructor ,constructor
      :reclaimer ,reclaimer
      :clearer ,clearer
      :accessor ,accessor
      :accessor-given-hash ,accessor-given-hash
      :key-deleter ,key-deleter
      :key-deleter-given-hash ,key-deleter-given-hash
      :set-if-no-entry-given-hash ,set-if-no-entry-given-hash
      :hash-function ,hash-function
      :key-comparitor ,key-comparitor
      :key-reclaimer ,key-reclaimer
      :entry-reclaimer ,entry-reclaimer
      :flattener ,flattener
      ,@(when use-skip-list
          `(:max-level ,max-level)))))


;;;; Sets and Bags



;;; Note! These sets are different from the list-like implementation described
;;; in file SETS. That file is a mixed collection of code that should be edited
;;; soon. To avoid name collision, do not use the following facility with the
;;; argument name being '||.

;;; Def-set defines a `set' in the mathematical sense.
;;; Any thing, x, is either a member of the set or it is not.

;;; To make x a member of a foo set s: (add-to-foo-set x s).
;;; This can be done any number of times without further effect.

;;; To make x cease to be a member: (remove-from-set x s).

;;; To test if x is a member of s: (foo-set-member-p x s).
;;; The value is t or nil.

;;; The keyword arguments constructor, reclaimer, clearer, hash-function,
;;; and key-comparitor are documented under binary trees. The corresponding
;;; functions are also used in the same way.

;;; The default names of the adder, remover and member-tester are given above.
;;; Other names can be obtained by using the keyword arguments.

;;; The implementation that follows uses the def-binary-tree facility with
;;; the set being a tree, the set members being keys and the values being
;;; t always.

;; Consider an implementation that did not have values. It would save
;; one cons per entry.

;; Unused.

(defmacro def-set (name &key
                         (constructor nil)
                         (reclaimer nil)
                         (clearer nil)
                         (adder nil)
                         (remover nil)
                         (member-tester nil)
                         (hash-function 'sxhashw)
                         (key-comparitor 'eq))

  (let* ((constructor-name
           (or constructor
               (intern (format nil "MAKE-~a-SET" name))))
         (reclaimer-name
           (or reclaimer
               (intern (format nil "RECLAIM-~a-SET" name))))
         (clearer-name
           (or clearer
               (intern (format nil "CLEAR-~a-SET" name))))
         (accessor-name
           (intern (format nil "GET-~a-MEMBER" name)))
         (key-deleter-name
               (intern (format nil "DELETE-~a" name)))
         (adder-name
           (or adder
               (intern (format nil "ADD-TO-~a-SET" name))))
         (remover-name
           (or remover
               (intern (format nil "REMOVE-FROM-~a-SET" name))))
         (member-tester-name
           (or member-tester
               (intern (format nil "~a-SET-MEMBER-P" name))))
         (set-variable
           (intern (format nil "~a-SET" name))))

    `(progn
       (def-skip-list-or-binary-tree ,name
         :constructor ,constructor-name
         :reclaimer ,reclaimer-name
         :clearer ,clearer-name
         :accessor ,accessor-name
         :key-deleter ,key-deleter-name
         :key-comparitor ,key-comparitor
         :hash-function ,hash-function)

       (defmacro ,adder-name (member ,set-variable)
         `(setf (,',accessor-name ,member ,,set-variable) t))

       (defmacro ,remover-name (member ,set-variable)
         `(,',key-deleter-name ,member ,,set-variable))

       (defmacro ,member-tester-name (member ,set-variable)
          `(,',accessor-name ,member ,,set-variable))

       ',name)))






;;; A `bag' differs from a set in that an element can be a member
;;; any number of times. Thus the bag of the salaries of all employees
;;; contains more information than the set of salaries of all employees.
;;; In particular, the sum, average, and distribution can be inferred
;;; from the bag.

;;; Def-bag is similar to def-set except for the following:

;;; (1) The default function names have BAG instead of SET, except that
;;;       the tester is foo-bag-member-count.
;;; (2) (add-to-foo-bag member bag) increments the number of times that
;;;       the member is in the bag.
;;; (3) (remove-from-foo-bag member set) decrements the number of times
;;;       that the member is in the bag, except that it does not become
;;; negative.
;;; (4) (foo-bag-member-count member bag) always has a non-negative fixnum
;;;      as value.

;;; The implementation that follows uses the def-binary-tree facility with
;;; the bag being a binary-tree, the bag members being keys and the
;;; values being positive fixnums that specify the number of times the member
;;; is in the bag. (0 times is represented by no entry.)

;; Unused.

(defmacro def-bag (name &key
                         (constructor nil)
                         (reclaimer nil)
                         (clearer nil)
                         (adder nil)
                         (remover nil)
                         (member-tester nil)
                         (hash-function 'sxhashw)
                         (key-comparitor 'eql))

  (let* ((constructor-name
           (or constructor
               (intern (format nil "MAKE-~a-BAG" name))))
         (reclaimer-name
           (or reclaimer
               (intern (format nil "RECLAIM-~a-BAG" name))))
         (clearer-name
           (or clearer
               (intern (format nil "CLEAR-~a-BAG" name))))
         (accessor-name
           (intern (format nil "GET-~a-MEMBER" name)))
         (key-deleter-name
               (intern (format nil "DELETE-~a" name)))
         (adder-name
           (or adder
               (intern (format nil "ADD-TO-~a-BAG" name))))
         (remover-name
           (or remover
               (intern (format nil "REMOVE-FROM-~a-BAG" name))))
         (member-tester-name
           (or member-tester
               (intern (format nil "~a-BAG-MEMBER-COUNT" name))))
         (bag-variable
           (intern (format nil "~a-BAG" name))))

    `(progn
       (def-skip-list-or-binary-tree ,name
         :constructor ,constructor-name
         :reclaimer ,reclaimer-name
         :clearer ,clearer-name
         :accessor ,accessor-name
         :key-deleter ,key-deleter-name
         :key-comparitor ,key-comparitor
         :hash-function ,hash-function)

       (defmacro ,adder-name (member ,bag-variable)
         (let ((member-value (gensym))
               (bag-value (gensym))
               (previous-value (gensym)))
           `(let* ((,member-value ,member)
                   (,bag-value ,,bag-variable)
                   (,previous-value
                    (,',accessor-name ,member-value ,bag-value)))
              (setf (,',accessor-name ,member-value ,bag-value)
                    (if (null ,previous-value)
                        1
                        (+f 1 ,previous-value))))))



       (defmacro ,remover-name (member ,bag-variable)
         (let ((member-value (gensym))
               (bag-value (gensym))
               (previous-value (gensym)))
           `(let* ((,member-value ,member)
                   (,bag-value ,,bag-variable)
                   (,previous-value
                    (,',accessor-name ,member-value ,bag-value)))
              (if ,previous-value
                  (if (>f ,previous-value 1)
                      (setf (,',accessor-name ,member-value ,bag-value)
                            (-f ,previous-value 1))
                      (,',key-deleter-name ,member-value ,bag-value))))))


       (defmacro ,member-tester-name (member ,bag-variable)
         `(let ((value
                  (,',accessor-name ,member ,,bag-variable)))
            (if value value 0)))

       ',name)))






;;;; Hash Tables




;; This general facility is rather inefficient for many important cases.  It
;; should do optimizations based on the key comparitor and on declarations.  For
;; example, either common comparitor cases should be handled by open code in
;; lookup-binary-tree-entry, or there should be variants of
;; lookup-binary-tree-entry for common comparitors.  It should be possible to
;; declare that one does not want binary trees, but just alists, in which case
;; accesses should expand in-line if the comparitor is trivial.  There should be
;; a standard way of specifying a simple fixnum identity function for
;; :hash-function-or-macro.  If these optimations are done, then I will enjoy
;; using this facility to map Kanji character codes into character information
;; structures, knowing that the overhead of the mapping is minimal.  (LH,
;; 3/20/89.)

;;; The macro `def-hash-table' is used to define constructor, reclaimer,
;;; clearing, accessor, and mutator macros for a hash table which provides fast
;;; lookups from a key to an entry.  Def-hash-table allows users to specify
;;; their own hashing, key equality predicates, sizes, and key and entry
;;; reclaimers.

;;; The constructor is MAKE-name (where "name" is the given name for the hash
;;; table).  It takes no arguments and returns an empty hash-table.  The
;;; reclaimer RECLAIM-name takes a hash table as its argument and will reclaim
;;; the table and any keys and values entered into it as instructed by the
;;; :KEY-RECLAIMER and :ENTRY-RECLAIMER arguments.  The clearer CLEAR-name takes
;;; a hash table as its argument and will delete and reclaim all keys and
;;; entries from the table.  The accessor GET-name takes a key and a hash-table
;;; as its arguments and will return any value entered under that key, or NIL if
;;; there is no entry for that key.  Entries may be entered into the hash table
;;; via SETF on the accessor.  Individual entries may be deleted from the hash
;;; table via the DELETE-name macro, which takes a key as its argument.

;;; Note that references to both a key and an entry into a hash table are stored
;;; within that structure, and the hash table then takes responsibility for
;;; reclaiming any keys and entries used in a SETF if a reclaimer has been
;;; declared.  That is, if there is a reclaimer for keys, and you pass a key to
;;; a SETF form, that key is now "owned" by the hash table, and it will take
;;; care of reclaiming it.  Note that in SETFs to keys which already exist
;;; within a hash table, the new copy of the key is immediately reclaimed, since
;;; a copy of it already exists within the table.  When there is a reclaimer for
;;; entries, if a value for a key is being replaced by a new value, the old
;;; value will be reclaimed.

;;; Hash tables are implemented with vector pools and binary trees.  The created
;;; vector pool is named name-HASH-VECTOR.

;;; The first argument to def-hash-table is an unquoted symbol which will be
;;; used as the table name.  The following optional keyword arguments also take
;;; unquoted symbols or constant numbers as their values:

;;;   :constructor takes an unquoted symbol which will be used as the name of
;;;   the constructor macro instead of MAKE-name.
;;;
;;;   :reclaimer takes an unquoted symbol which will be used as the name of the
;;;   reclaimer function instead of RECLAIM-name.
;;;
;;;   :clearer takes an unquoted symbol which will be used as the name of the
;;;   function which clears all entries from a hash table, replacing the default
;;;   CLEAR-name.
;;;
;;;   :accessor takes an unquoted symbol which will be used as the name of the
;;;   accessor macro instead of GET-name.
;;;
;;;   :key-deleter takes an unquoted symbol which will be used as the name of
;;;   the function which deletes an entry for a key from the hash table, instead
;;;   of the default DELETE-name.
;;;
;;;   :set-if-no-entry takes an unquoted symbol which will be used as the name
;;;   of a function which will either enter a new entry into the hash table for a
;;;   given key if no previous value existed, returning the new entry.  If a
;;;   value did exist for this key, then the new value will not be entered, and
;;;   the old value will be returned.  The default name for this macro is
;;;   SET-name-IF-NO-ENTRY.  Note that if no old entry existed, then the given
;;;   key and entry will become "owned" by the hash table and will be managed as
;;;   specified by the key-reclaimer and entry-reclaimer for the table.  If an
;;;   old value existed, neither the given key nor the new value will be
;;;   acquired by the hash table and it is up to the caller to reclaim them as
;;;   appropriate.
;;;
;;;   :hash-function-or-macro takes an unquoted symbol which names the function
;;;   or macro to be called with a key to compute a non-negative fixnum hash of
;;;   that key.  The default is SXHASH.
;;;
;;;   :key-comparitor takes an unquoted symbol which names the FUNCTION which
;;;   will be used to test equality of lookup keys.  This must be a function
;;;   since it is passed as the :TEST argument to ASSOC.  It defaults to EQ.
;;;
;;;   :size takes a constant integer to be used as the size of the hash table.
;;;   It defaults to 43.  Note that typically hash tables are given prime
;;;   numbers as their hashing size, so that when performing a MOD on the hash
;;;   it will provide an even distribution of objects to buckets within the
;;;   table.  However, in our system we occasionally have hashing numbers which
;;;   are monotonically increasing, so a MOD of any number will give a nice
;;;   distribution.  Because of this, if the size given a hash table is a power
;;;   of two, a LOGANDF is used to perform the MOD, which is a bit faster.
;;;   Users should take some care in choosing their size numbers.
;;;
;;;   :key-reclaimer takes an unquoted symbol which names the function or macro
;;;   used to reclaim keys from the table.  Note that when given this option,
;;;   the key will be reclaimed on entry deletion, table clear, table reclaim,
;;;   and also on entry mutation.  On mutation, it is not defined whether this
;;;   will reclaim the old key stored in the table or the new key just given.
;;;   References should not be maintained to keys which have been given to the
;;;   table mutation functions, since they may have been reclaimed.
;;;
;;;   :entry-reclaimer takes an unquoted symbol which names the function or
;;;   macro used to reclaim entry values from the table.  This reclaimer will be
;;;   called on values within the table when they are replaced with new values
;;;   via a mutation, when the table is cleared, when the entry is deleted, or
;;;   when the table is being reclaimed.

(defmacro def-hash-table (name &key
                               (constructor nil)
                               (reclaimer nil)
                               (clearer nil)
                               (accessor nil)
                               (key-deleter nil)
                               (set-if-no-entry nil)
                               (hash-function-or-macro 'sxhashw)
                               (key-comparitor 'eq)
                               (size 43)
                               (max-skip-list-level 31)
                               (key-reclaimer nil)
                               (entry-reclaimer nil)
                               (flattener nil)
                               (use-binary-tree nil))
  (if (not (symbolp name))
      (error "Def-hash-table needs a symbol as a name, it got ~s." name))
  (let* ((vector-name (intern (format nil "~a-HASH-VECTOR" name)))
         (vector-maker (intern (format nil "MAKE-~a" vector-name)))
         (vector-reclaimer (intern (format nil "RECLAIM-~a" vector-name)))
         (vector-aref (intern (format nil "AREF-~a" vector-name)))
         (tree-name (intern (format nil "~a-TREE-FOR-HASH" name)))
         (tree-constructor
           (intern (format nil "MAKE-~a-TREE" name)))
         (tree-reclaimer
           (intern (format nil "RECLAIM-~a-TREE" name)))
         (tree-clearer
           (intern (format nil "CLEAR-~a-TREE" name)))
         (tree-accessor-given-hash
           (intern (format nil "GET-~a-FROM-TREE-GIVEN-HASH" name)))
         (tree-deleter-given-hash
           (intern (format nil "DELETE-~a-FROM-TREE-GIVEN-HASH" name)))
         (tree-set-if-no-entry-given-hash
           (intern (format nil "SET-~a-IN-TREE-IF-NO-ENTRY-GIVEN-HASH" name)))
         (accessor-name
           (or accessor (intern (format nil "GET-~a" name))))
         (deleter-name
           (or key-deleter (intern (format nil "DELETE-~a" name))))
         (flattener-name (or flattener (intern (format nil "FLATTEN-~a" name))))
         (tree-flattener-name  (intern (format nil "FLATTEN-~a-TREE" name)))
         (set-if-no-entry-name
           (or set-if-no-entry (intern (format nil "SET-~a-IF-NO-ENTRY" name))))
         (mutator-name (intern (format nil "SET-~a-HASH-VALUE" name)))
         (constructor-name
           (or constructor (intern (format nil "MAKE-~a" name))))
         (reclaimer-name
           (or reclaimer (intern (format nil "RECLAIM-~a" name))))
         (clear-name
           (or clearer (intern (format nil "CLEAR-~a" name))))
         (hash-table-var (intern (format nil "~a-HASH-TABLE" name)))
         (hash-mod-macro (intern (format nil "~a-HASH-MOD" name))))

  `(progn
     (def-vector-pool ,vector-name ,size
       :initial-element nil :initialize-on-recycle nil)

     (def-skip-list-or-binary-tree ,tree-name
       :constructor ,tree-constructor
       :reclaimer ,tree-reclaimer
       :clearer ,tree-clearer
       :accessor-given-hash ,tree-accessor-given-hash
       :key-deleter-given-hash ,tree-deleter-given-hash
       :set-if-no-entry-given-hash ,tree-set-if-no-entry-given-hash
       :hash-function ,hash-function-or-macro
       :key-comparitor ,key-comparitor
       :key-reclaimer ,key-reclaimer
       :entry-reclaimer ,entry-reclaimer
       :flattener ,tree-flattener-name
       :use-binary-tree ,use-binary-tree
       :max-level ,max-skip-list-level)

     (defmacro ,hash-mod-macro (hash)
       ,(if (=f (logcount size) 1)                ; size is base two
            ``(logandf ,hash ,',(-f size 1))
            ``(modf-positive ,hash ,',size)))

     (defmacro ,accessor-name (key ,hash-table-var)
       (let ((key-evaled (gensym))
             (key-hash (gensym)))
         (if (or (constantp key) (symbolp key))
             `(let ((,key-hash (,',hash-function-or-macro ,key)))
                (declare (type fixnum ,key-hash))
                (,',tree-accessor-given-hash
                 ,key
                 (,',vector-aref ,,hash-table-var (,',hash-mod-macro ,key-hash))
                 ,key-hash))
             `(let* ((,key-evaled ,key)
                     (,key-hash (,',hash-function-or-macro ,key-evaled)))
                (declare (type fixnum ,key-hash))
                (,',tree-accessor-given-hash
                 ,key-evaled
                 (,',vector-aref ,,hash-table-var (,',hash-mod-macro ,key-hash))
                 ,key-hash)))))

     (defmacro ,mutator-name (key ,hash-table-var entry)
       (let ((key-evaled (gensym))
             (key-hash (gensym)))
         (if (or (constantp key) (symbolp key))
             `(let ((,key-hash (,',hash-function-or-macro ,key)))
                (declare (type fixnum ,key-hash))
                (setf (,',tree-accessor-given-hash
                       ,key
                       (,',vector-aref
                        ,,hash-table-var
                        (,',hash-mod-macro ,key-hash))
                       ,key-hash)
                      ,entry))
             `(let* ((,key-evaled ,key)
                     (,key-hash (,',hash-function-or-macro ,key-evaled)))
                (declare (type fixnum ,key-hash))
                (setf (,',tree-accessor-given-hash
                       ,key-evaled
                       (,',vector-aref
                        ,,hash-table-var
                        (,',hash-mod-macro ,key-hash))
                       ,key-hash)
                      ,entry)))))

     (defsetf ,accessor-name ,mutator-name)

     (defmacro ,deleter-name (key ,hash-table-var)
       (let ((key-evaled (gensym))
             (key-hash (gensym)))
         (if (or (constantp key) (symbolp key))
             `(let ((,key-hash (,',hash-function-or-macro ,key)))
                (declare (type fixnum ,key-hash))
                (,',tree-deleter-given-hash
                 ,key
                 (,',vector-aref ,,hash-table-var (,',hash-mod-macro ,key-hash))
                 ,key-hash))
             `(let* ((,key-evaled ,key)
                     (,key-hash (,',hash-function-or-macro ,key-evaled)))
                (declare (type fixnum ,key-hash))
                (,',tree-deleter-given-hash
                 ,key-evaled
                 (,',vector-aref ,,hash-table-var (,',hash-mod-macro ,key-hash))
                 ,key-hash)))))

     (defmacro ,set-if-no-entry-name (key ,hash-table-var entry)
       (let ((key-evaled (gensym))
             (key-hash (gensym)))
         (if (or (constantp key) (symbolp key))
             `(let ((,key-hash (,',hash-function-or-macro ,key)))
                (declare (type fixnum ,key-hash))
                (,',tree-set-if-no-entry-given-hash
                 ,key
                 (,',vector-aref ,,hash-table-var (,',hash-mod-macro ,key-hash))
                 ,key-hash
                 ,entry))
             `(let* ((,key-evaled ,key)
                     (,key-hash (,',hash-function-or-macro ,key-evaled)))
                (declare (type fixnum ,key-hash))
                (,',tree-set-if-no-entry-given-hash
                 ,key-evaled
                 (,',vector-aref ,,hash-table-var (,',hash-mod-macro ,key-hash))
                 ,key-hash
                 ,entry)))))

     (defun-simple ,constructor-name ()
       (loop with new-vector = (,vector-maker)
             for index from 0 below ,size
             do
         (setf (,vector-aref new-vector index) (,tree-constructor))
              finally
                (return new-vector)))

     (defun-simple ,flattener-name (,hash-table-var)
       (let ((result))
         (loop for index from 0 below ,size
               do
           (let ((subtree (,vector-aref ,hash-table-var index)))
             (when subtree
               (setf result
                     (nconc
                       (,tree-flattener-name subtree)
                       result)))))
         result))

     (defun-simple ,clear-name (,hash-table-var)
       (loop for index from 0 below ,size
             do
         (,tree-clearer (,vector-aref ,hash-table-var index))))

     (defun-simple ,reclaimer-name (,hash-table-var)
       (loop for index from 0 below ,size
             do
         (,tree-reclaimer (,vector-aref ,hash-table-var index))
         (setf (,vector-aref ,hash-table-var index) nil))
       (,vector-reclaimer ,hash-table-var))

     ',name)))




;;; The `hash-value loop path' allows users to loop over the values within hash
;;; tables.

(define-loop-path hash-value expand-hash-value-loop-iterator (of))

(defun-for-macro expand-hash-value-loop-iterator
                 (method-name
                   iter-var iter-var-data-type prep-phrases inclusive?
                   allowed-preps method-specific-data)
  (declare (ignore method-name allowed-preps method-specific-data))
  (when inclusive?
    (error "The hash-value iteration path does not support inclusive iterations."))
  (let* ((hash-table-form-entry (assq 'of prep-phrases))
         (hash-table-form (second hash-table-form-entry))
         (table (loop-gentemp 'hash-table-))
         (table-length (loop-gentemp 'table-length-))
         (index (loop-gentemp 'index-))
         (tree-form (loop-gentemp 'tree-form-))
         #+skip-list
         (skip-list-p (loop-gentemp 'skip-list-p-))
         (node-stack (loop-gentemp 'node-stack-))
         (current-node (loop-gentemp 'current-node-))
         #+skip-list
         (tail-node (loop-gentemp 'tail-node-))
         (current-alist (loop-gentemp 'current-alist-))
         (entry-cons (loop-gentemp 'entry-cons-))
         (less-than-branch? (loop-gentemp 'less-than-branch?-))
         init-bindings
         prologue-forms
         (pre-step-tests nil)
         (steppings nil)
         post-step-tests
         post-step-settings)
    (when (null hash-table-form-entry)
      (error "The hash-value iteration path requires an \"OF hash-table-form\"."))
    (when (or (not (symbolp iter-var)) (eq iter-var-data-type t))
      (setq iter-var-data-type nil))
    ;; The following variables need to be bound in the loop expansion.
    (setq init-bindings
          `((scope-conses scope-conses)
            (,table ,hash-table-form simple-vector)
            (,table-length 0 fixnum)
            (,index 0 fixnum)
            (,tree-form nil)
            (,node-stack nil)
            (,current-node nil)
            (,current-alist nil)
            (,entry-cons nil)
            #+skip-list (,skip-list-p nil)
            #+skip-list (,tail-node nil)
            ,(if iter-var-data-type
                 `(,iter-var nil ,iter-var-data-type)
                 `(,iter-var))))

    (setq prologue-forms
          `((setq ,table-length (length-of-simple-vector ,table))))

    (setq post-step-tests
          `(progn
             (cond
               (,current-alist
                (setq ,entry-cons (car-of-cons ,current-alist))
                (setq ,current-alist (cdr-of-cons ,current-alist)))
               #+skip-list
               ((and ,current-node ,skip-list-p)
                (setq ,current-node (skip-list-element-next-0 ,current-node))
                (if (eq ,current-node ,tail-node)
                    (setq ,current-node nil)
                  (progn
		    (setq ,entry-cons
			  (scope-cons (skip-list-element-key ,current-node)
				      (skip-list-element-entry ,current-node))))))
               (,current-node
                (setq ,current-node (greater-than-branch ,current-node))
                (cond
                  (,current-node
                   (loop for ,less-than-branch? = (less-than-branch ,current-node)
                         while ,less-than-branch?
                         do
                     (setq ,node-stack
                           (scope-cons ,current-node ,node-stack))
                     (setq ,current-node ,less-than-branch?)))
                  (,node-stack
                   (setq ,current-node (car-of-cons ,node-stack))
                   (setq ,node-stack (cdr-of-cons ,node-stack))))
                (when ,current-node
                  (setq ,current-alist (binary-element-alist ,current-node))
                  (setq ,entry-cons (car-of-cons ,current-alist))
                  (setq ,current-alist (cdr-of-cons ,current-alist)))))
             (unless ,current-node
               (loop while (<f ,index ,table-length) do
                 (setq ,tree-form (svref ,table ,index))
                 #+skip-list
                 (when (=f ,index 0)
                   (setq ,skip-list-p (skip-list-p ,tree-form)))
                 (incff ,index)
                 (cond
                   #+skip-list
                   (,skip-list-p
                    (setq ,current-node
                          (skip-list-element-next-0 (skip-list-head ,tree-form)))
                    (setq ,tail-node (skip-list-tail ,tree-form))
                    (if (eq ,current-node ,tail-node)
                        (setq ,current-node nil)
                      (progn
			(setq ,entry-cons
			      (scope-cons (skip-list-element-key ,current-node)
					  (skip-list-element-entry ,current-node)))
                        (loop-finish))))
                   (t
                    (setq ,current-node (cdr ,tree-form))
                    (when ,current-node
                      (loop for ,less-than-branch? = (less-than-branch ,current-node)
                            while ,less-than-branch?
                            do
                        (setq ,node-stack (scope-cons ,current-node ,node-stack))
                        (setq ,current-node ,less-than-branch?))
                      (setq ,current-alist (binary-element-alist ,current-node))
                      (setq ,entry-cons (car-of-cons ,current-alist))
                      (setq ,current-alist (cdr-of-cons ,current-alist))
                      (loop-finish))))))
             (null ,current-node)))

    ;; Use the type declaration only if it is something other than T and if the
    ;; iter-var is a symbol and not a destructuring list.
    (if (and (symbolp iter-var)
             iter-var-data-type
             (neq iter-var-data-type t))
        (setq post-step-settings
              `(,iter-var (the ,iter-var-data-type (cdr-of-cons ,entry-cons))))
        (setq post-step-settings
              `(,iter-var (cdr-of-cons ,entry-cons))))

    ;; Return a list of the six path elements.
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

;;; The function `describe-hash-table' prints out the contents of a given hash
;;; table.

#+development
(defun describe-hash-table (hash-table)
  (if (simple-vector-p hash-table)
      (print-hash-table hash-table)
      (format t "~s is not a hash table." hash-table)))

#+development
(defun print-hash-table (hash-table)
  (loop with table-size = (length hash-table)
        for index from 0 below table-size
        for bucket? = (aref hash-table index)
        initially
          (format t "~%Contents of hash table with ~a buckets." table-size)
        do
    (if (null bucket?)
        (format t "~%Bucket ~a is empty" index)
        (progn
          (format t "~%Bucket ~a contains:" index)
          (describe-tree bucket?)))))


#+development
(defun print-hash-table-histogram (hash-table)
  (loop with table-size = (length hash-table)
        with total-elements = 0
        with total-nodes = 0
        with max-level = 0
        with total-collisions = 0
        for index from 0 below table-size
        for bucket? = (aref hash-table index)
        initially
          (format t "~%Histogram of hash table with ~a buckets." table-size)
          do
    (multiple-value-bind (element-count node-count collisions depth)
        (collect-tree-statistics bucket?)
      (incff total-elements element-count)
      (incff total-nodes node-count)
      (incff total-collisions collisions)
      (setq max-level (maxf depth max-level))
      (format
        t
        "~%Bucket ~a contains ~a elements, ~a nodes, ~a collisions, and is ~a levels deep"
        index element-count node-count collisions depth))
        finally
          (format
            t
            "~%Totals ~a elements, ~a nodes, ~a collisions, ~a maximum depth."
            total-elements total-nodes total-collisions max-level)))






;;;; Sparse Arrays




;;; A `sparse array' is a managed data structure which can efficiently hold and
;;; retrieve large numbers of values at indexed locations without having to
;;; allocate full arrays for entire range of index values.  The interfaces to
;;; this facility are as follows.  The macro `allocate-sparse-array' which
;;; allocates a new, empty sparse array and `reclaim-sparse-array' reclaims it.
;;; The function `aref-sparse-array' takes a sparse array and an index and
;;; returns the value at that index or NIL if there is none.  It is setfable to
;;; put new values into the sparse array.

;;; About the memory use of this facility.  It allocates a hierarchy of buffers
;;; broad enough to span the range of values inserted into the array.  It is not
;;; biased towards a lowest index value of 0 as are most sparse array
;;; implementations, but will instead adjust its base value to fit the indices
;;; inserted.  Clumpiness in the set of indices helps, with the lowest level
;;; buffers allocated being 32 elements long.  Lookups are require 1 function
;;; call, some inline fixnum arithmetic, and at most 6 SVREFs.





;;; The structure `sparse-array' is the base of any sparse array instance.

(def-structure (sparse-array (:constructor allocate-sparse-array ())
                             (:reclaimer reclaim-sparse-array-1)
                             (:eliminate-for-products gsi))
  (sparse-array-lowest-index 0)
  (sparse-array-hierarchy-depth -1)
  (sparse-array-vector nil))

(defun-void reclaim-sparse-array (sparse-array)
  (declare (eliminate-for-gsi))
  (let ((depth (sparse-array-hierarchy-depth sparse-array)))
    (when (>=f depth 0)
      (reclaim-sparse-array-vectors (sparse-array-vector sparse-array) depth))
    (reclaim-sparse-array-1 sparse-array)))

(defun-void reclaim-sparse-array-vectors (vector depth)
  (declare (eliminate-for-gsi))
  (when (>f depth 0)
    (loop with subdepth = (-f depth 1)
          for index from 0 below (left-shiftf 1 sparse-array-layer-order)
          for subvector? = (svref vector index)
          do
      (when subvector? (reclaim-sparse-array-vectors subvector? subdepth))))
  (reclaim-managed-simple-vector vector))

(defun-simple aref-sparse-array (sparse-array index)
  (declare (type fixnum index)
	   (eliminate-for-gsi))
  (let* ((base (-f index (sparse-array-lowest-index sparse-array)))
         (depth (sparse-array-hierarchy-depth sparse-array))
         (shift-amount (*f depth sparse-array-layer-order)))
    (declare (type fixnum base depth shift-amount))
    (when (and (>=f depth 0)
               (>=f base 0)
               (or (=f depth sparse-array-max-depth)
                   (<f base
                       (left-shiftf 1 (+f shift-amount sparse-array-layer-order)))))
      (loop with buffer = (sparse-array-vector sparse-array)
            while buffer do
        (cond ((=f shift-amount 0)
               (return (svref buffer base)))
              (t
               (setq buffer (svref buffer (right-shiftf base shift-amount)))
               (setq base (logandf base (-f (left-shiftf 1 shift-amount) 1)))
               (decff shift-amount sparse-array-layer-order)))))))




;;; The function `aset-sparse-array' takes a sparse array, and index, and a new
;;; value to be placed at that index.  It adds whatever extra layers of
;;; buffer hierarchy that are necessary to span an index range that includes the
;;; given index, and then it traverses into the buffer heirarchy adding whatever
;;; intermediate buffers are needed to get to the actual buffer containing the
;;; element to set.  It returns the given new value for the index.

(defun-simple aset-sparse-array (sparse-array index value)
  (declare (type fixnum index)
	   (eliminate-for-gsi))
  (let* ((lowest-index (sparse-array-lowest-index sparse-array))
         (current-depth (sparse-array-hierarchy-depth sparse-array))
         (shift-amount (*f current-depth sparse-array-layer-order))
         (buffer-length (left-shiftf 1 sparse-array-layer-order))
         (buffer-mask (-f buffer-length 1)))
    (declare (type fixnum
		   lowest-index current-depth shift-amount buffer-length
		   buffer-mask))
    ;; Add layers of buffer hierarchy until the given index is inside the range
    ;; encompassed by the current lowest-index and current-depth.
    (loop while (or (<f index lowest-index)
                    (and (<f current-depth sparse-array-max-depth)
                         (>=f index
                              (+f lowest-index
                                  (left-shiftf
                                    1 (+f shift-amount sparse-array-layer-order))))))
          for new-buffer = (allocate-managed-simple-vector buffer-length)
          do
      (loop for init-index from 0 below buffer-length do
        (setf (svref new-buffer init-index) nil))
      (cond ((=f current-depth -1)
             (setq current-depth 0)
             (setq shift-amount 0)
             (setq lowest-index (logandf index (-f buffer-length))))
            (t
             (incff current-depth)
             (incff shift-amount sparse-array-layer-order)
             (setf (svref new-buffer
                          (logandf (right-shiftf lowest-index shift-amount)
                                   buffer-mask))
                   (sparse-array-vector sparse-array))
             (setf lowest-index
                   (logandf
                     lowest-index
                     (if (=f current-depth sparse-array-max-depth)
                         -1
                         (-f (left-shiftf
                               1 (+f shift-amount sparse-array-layer-order))))))))
      (setf (sparse-array-lowest-index sparse-array) lowest-index)
      (setf (sparse-array-hierarchy-depth sparse-array) current-depth)
      (setf (sparse-array-vector sparse-array) new-buffer))
    ;; Now there is enough hiearchy to span the index we are aiming for, so
    ;; descend into the sparse array vector, filling in buffers as necessary.
    (loop for buffer = (sparse-array-vector sparse-array)
                     then next-buffer?
          for buffer-index fixnum = (logandf
                                      (right-shiftf index shift-amount)
                                      buffer-mask)
          until (=f shift-amount 0)
          for next-buffer? = (svref buffer buffer-index)
          do
      (when (null next-buffer?)
        (setq next-buffer? (allocate-managed-simple-vector buffer-length))
        (loop for init-index from 0 below buffer-length do
          (setf (svref next-buffer? init-index) nil))
        (setf (svref buffer buffer-index) next-buffer?))
      (decff shift-amount sparse-array-layer-order)
          finally
            (setf (svref buffer buffer-index) value))
    value))

(defmacro defsetf-of-aref-sparse-array ()
  (if (gsi-eliminable-p)
      nil
      `(defsetf aref-sparse-array aset-sparse-array)))

(defsetf-of-aref-sparse-array)





;;; The loop path `sparse-array-value' can be used to iterate over all non-null
;;; values within a sparse array.

(define-loop-path sparse-array-value expand-sparse-array-value-loop-iterator (of))

(defun-for-macro expand-sparse-array-value-loop-iterator
                 (method-name
                   iter-var iter-var-data-type prep-phrases inclusive?
                   allowed-preps method-specific-data)
  (declare (ignore method-name allowed-preps method-specific-data))
  (when inclusive?
    (error "The sparse-array-value iteration path does not support inclusive iterations."))
  (let* ((sparse-array-form-entry (assq 'of prep-phrases))
         (sparse-array-form (second sparse-array-form-entry))
         (sparse-array (loop-gentemp 'sparse-array-))
         (vector-stack (loop-gentemp 'vector-stack-))
         (next-value? (loop-gentemp 'next-value?-))
         (next-vector-index (loop-gentemp 'next-vector-index-))
         (pre-step-tests nil)
         (steppings nil)
         init-bindings prologue-forms post-step-tests post-step-settings)
    (when (null sparse-array-form-entry)
      (error "The sparse-array-value iteration path requires an \"OF sparse-array-form\"."))
    (when (or (not (symbolp iter-var)) (eq iter-var-data-type t))
      (setq iter-var-data-type nil))
    ;; The following variables need to be bound in the loop expansion.
    (setq init-bindings
          `((scope-conses scope-conses)
            (,sparse-array ,sparse-array-form)
            (,vector-stack nil)
            (,next-vector-index 0 fixnum)
            (,next-value? nil)
            ,(if iter-var-data-type
                 `(,iter-var nil ,iter-var-data-type)
                 `(,iter-var))))

    (setq prologue-forms
          `((setq ,vector-stack
                  (collect-leaf-vectors
                    (sparse-array-vector ,sparse-array)
                    (sparse-array-hierarchy-depth ,sparse-array)))))

    (setq post-step-tests
          `(progn
             (setq ,next-value? nil)
             (loop named find-value
                   while ,vector-stack
                   for vector = (car-of-cons ,vector-stack)
                   for vector-length fixnum = (length-of-simple-vector vector)
                   do
               (loop while (<f ,next-vector-index vector-length) do
                 (setq ,next-value? (svref vector ,next-vector-index))
                 (incff ,next-vector-index)
                 (when ,next-value?
                   (return-from find-value nil)))
               (setq ,next-vector-index 0)
               (setq ,vector-stack (cdr-of-cons ,vector-stack)))
             (null ,next-value?)))

    (setq post-step-settings `(,iter-var ,next-value?))

    ;; Return a list of the six path elements.
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

(defun-simple collect-leaf-vectors (vector depth)
  (declare (eliminate-for-gsi))
  (cond ((<f depth 0)
         nil)
        ((=f depth 0)
         (scope-cons vector nil))
        ((=f depth 1)
         (loop for index from 0 below (length-of-simple-vector vector)
               for element? = (svref vector index)
               when element?
                 collect element? using scope-cons))
        (t
         (loop for index from 0 below (length-of-simple-vector vector)
               for subvector? = (svref vector index)
               when subvector?
                 nconc (collect-leaf-vectors subvector? (1-f depth))))))




;;; The development-only function `describe-sparse-array' takes a sparse array
;;; and writes to standard-output a description of the values currently within
;;; the sparse array.

#+development
(defun describe-sparse-array (sparse-array)
  (with-faster-standard-output
    (let ((depth (sparse-array-hierarchy-depth sparse-array))
          (lowest-index (sparse-array-lowest-index sparse-array)))
      (cond ((<f depth 0)
             (format t "~a is an empty sparse array.~%" sparse-array))
            (t
             (format t "~a has ~a levels, with a lowest index of ~a.~%"
                     sparse-array (+f depth 1) lowest-index)
             (format t "~a vectors total.~%"
                     (describe-sparse-array-1
                       (sparse-array-vector sparse-array)
                       lowest-index
                       depth))))
      sparse-array)))

#+development
(defun describe-sparse-array-1 (vector lowest-index depth)
  (let ((length (left-shiftf 1 sparse-array-layer-order)))
    (unless (=f (length-of-simple-vector vector) length)
      (error "~a is the wrong length." vector))
    (if (=f depth 0)
        (loop for index from 0 below length
              for value? = (svref vector index)
              do
          (when value?
            (format t "~6d : ~a~%" (+f lowest-index index) value?))
              finally (return 1))
        (loop with subvector-count = 0
              for index from 0 below length
              for subvector? = (svref vector index)
              do
          (when subvector?
            (incff subvector-count
                   (describe-sparse-array-1
                     subvector?
                     (+f lowest-index
                         (*f index
                             (left-shiftf
                               1 (*f depth sparse-array-layer-order))))
                     (-f depth 1))))
              finally (return subvector-count)))))






;;;; Index Spaces




;;; An `index space' is a data-abstracted structure that maps from a contiguous
;;; set of non-negative integers (starting with 0) to arbitrary objects.

;;; At present, an index space has a maximum capacity of 1,048,576 objects.

;; Index spaces were originally defined in INT.  I've moved them here to
;; utilities2 and made them use managed simple vectors as their vector source.
;; If and when we can get around to it, we should consider using managed-vectors
;; as the implementation of index-space vectors.  That would give us better
;; usage of memory buffers, though the unused buffer characteristics of the
;; current growth scheme here are better.  -jra 3/23/89

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defmacro index-space-vector-length () #.(expt 2 10)))        ; must be a power of two

(defun make-index-space-vector ()
  (let ((new-vector (allocate-managed-simple-vector
                      (index-space-vector-length))))
    (initialize-vector-pool-vector
      new-vector (index-space-vector-length) nil svref)
    new-vector))

;; Make-index-space-vector initializes the elements of the vector to nil.





(def-structure (index-space
                 (:constructor
                   make-index-space (index-space-name index-space-object-reclaimer?)))

  index-space-name

  (vector-of-index-subspace-vectors
    (make-index-space-vector)
    :reclaimer reclaim-vector-of-index-subspace-vectors)

  (last-assigned-index -1)
  (current-index-limit-plus-one 0)

  (list-of-reassignable-indices                        ; a gensym list
    nil
    :reclaimer reclaim-gensym-list)
  index-space-object-reclaimer?)

(defun-void reclaim-if-index-space (index-space?)
  (when index-space? (reclaim-index-space index-space?)))

;; Consider using a gensym list of index subspace vectors, in lieu of an index
;; space vector, for better memory management (but loss of speed).

;; Consider using a managed-array as the vector and subspace vector
;; implementation, giving you both speed and better memory management.  -jra
;; 3/23/89

(defun reclaim-vector-of-index-subspace-vectors
    (vector-of-index-subspace-vectors)
  (loop with index-space-name = (index-space-name structure-being-reclaimed)
        with index-space-object-reclaimer?
          = (index-space-object-reclaimer? structure-being-reclaimed)
        with nil-unreclaimed-as-yet-p = t
        as i from 0 below (length vector-of-index-subspace-vectors)
        as index-subspace-vector? = (svref vector-of-index-subspace-vectors i)
        while index-subspace-vector?

        when index-space-object-reclaimer?
          do (loop with fn = (symbol-function index-space-object-reclaimer?)
                   for j from 0 below #.(index-space-vector-length)
                   as object? = (svref index-subspace-vector? j)
                   ;; On a simple TW connection, would call the reclaimer 1000 times on NIL.
                   do
               (when (or object? nil-unreclaimed-as-yet-p)
                 (funcall-simple-compiled-function fn object? index-space-name t)
                 (unless object?
                   (setq nil-unreclaimed-as-yet-p nil))))

        do (reclaim-managed-simple-vector index-subspace-vector?))
  (reclaim-managed-simple-vector vector-of-index-subspace-vectors))




;;; Get-object-from-index-space ...

;; GENSYMCID-1054: Gigasoft Charts Issue causes TWNG to crash and exit without
;;                 warning when using TWNG 2011 with 8.3r1
;;
;; `get-object-from-index-space-if-valid' is a safer version to handle null
;; indexes, which could happen when handling ICP messages sent from old G2.
;; it's used only in `get-icp-arg-reader-for-corresponding-object'.
;;
;; also see (def-icp-message-type manage-chart-view) in NATIVE-TW and `body-
;; of-read-icp-unsigned-integer' in INT3A for backgrounds.
;;
;;  -- Chun Tian (binghe), 2013/06/19

(def-substitution-macro get-object-from-index-space-if-valid (index-space index)
  (when (fixnump index)
    (get-object-from-index-space index-space index)))

(def-substitution-macro get-object-from-index-space (index-space index)
  (when (>=f index (current-index-limit-plus-one index-space))
    (enlarge-index-space index-space index))
  (svref
    (svref
      (vector-of-index-subspace-vectors index-space)
      (ashf index #.(- (integer-length (1- (index-space-vector-length))))))
    (logandf index #.(1- (index-space-vector-length)))))

(def-substitution-macro svref-checking-vector-and-index (vector index)
  (and vector
       (<f index (length (the simple-vector vector)))
       (svref vector index)))

(def-substitution-macro get-object-from-index-space-if-any (index-space index)
  (svref-checking-vector-and-index
    (svref-checking-vector-and-index
      (vector-of-index-subspace-vectors index-space)
      (ashf index #.(- (integer-length (1- (index-space-vector-length))))))
    (logandf index #.(1- (index-space-vector-length)))))



;;; Store-object-in-index-space ... returns object.

(def-substitution-macro store-object-in-index-space (index-space index object)
  (when (>=f index (current-index-limit-plus-one index-space))
    (enlarge-index-space index-space index))
  (setf (svref
          (svref
            (vector-of-index-subspace-vectors index-space)
            (ashf index #.(- (integer-length (1- (index-space-vector-length))))))
          (logandf index #.(1- (index-space-vector-length))))
        object))

(defsetf get-object-from-index-space store-object-in-index-space)


;;; Assign-index-in-index-space ... returns the index and either nil or, if
;;; index-space was enlarged, the new index limit plus one.

(defun assign-index-in-index-space (index-space)
  (if (list-of-reassignable-indices index-space)
      (gensym-pop (list-of-reassignable-indices index-space))
      (let ((index (incff (last-assigned-index index-space))))
        (cond
          ((=f index (current-index-limit-plus-one index-space))
           (enlarge-index-space index-space nil)
           (values index (current-index-limit-plus-one index-space)))
          (t index)))))



;;; Deassign-index-in-index-space ...

(defun deassign-index-in-index-space (index index-space)
  (gensym-push index (list-of-reassignable-indices index-space)))





;;; Enlarge-index-space ...
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant enlarge-index-space-error-message "Index space full!"))

(defmacro signal-index-space-full-error () ; never called, anymore
  `(current-system-case
     ((ab telewindows) (error #.enlarge-index-space-error-message))
     (gsi (signal-gsi-index-space-full-error))))

(defun enlarge-index-space (index-space minimum-new-index-limit?)
  (if minimum-new-index-limit?
      (when (>f (current-index-limit-plus-one index-space)
                minimum-new-index-limit?)
        (return-from enlarge-index-space nil))
      (setq minimum-new-index-limit?
            (current-index-limit-plus-one index-space)))
  (loop with spine-vector = (vector-of-index-subspace-vectors index-space)
        with spine-vector-length = (length spine-vector)
        as new-index-subspace-index
           = (ashf (current-index-limit-plus-one index-space)
                   #.(- (integer-length (- (index-space-vector-length) 1))))
        do (when (=f new-index-subspace-index spine-vector-length)
             (let* ((new-spine-vector-length (ashf spine-vector-length 1))
                    (new-spine-vector (allocate-managed-simple-vector new-spine-vector-length)))
               (loop for i fixnum from 0 below spine-vector-length
                     do (setf (svref new-spine-vector i) (svref spine-vector i)))
               (loop for i fixnum from spine-vector-length below new-spine-vector-length
                     do (setf (svref new-spine-vector i) nil))
               (reclaim-managed-simple-vector spine-vector)
               (setf (vector-of-index-subspace-vectors index-space) new-spine-vector)
               (setq spine-vector new-spine-vector)
               (setq spine-vector-length new-spine-vector-length)))
           (setf (svref (vector-of-index-subspace-vectors index-space)
                        new-index-subspace-index)
                 (make-index-space-vector))
           (incff (current-index-limit-plus-one index-space) #.(index-space-vector-length))
        until (>f (current-index-limit-plus-one index-space) minimum-new-index-limit?)))

;See lookup-index-in-index-space

#+development
(defun describe-index-space (index-space)
  (loop for i from 0 to (last-assigned-index index-space)
        as object = (get-object-from-index-space-if-any index-space i)
        do (format t "[~d] ~s~%" i object))
  index-space)



;;;; Queues With Constant Insert, Dequeue, and Delete Operations




;;; The following forms implement a type of queue which has constant time
;;; insert, dequeue, and delete operations.

;;; The lock-free verion is based on algorithms from following papers:
;;;
;;; Sundell, Hakan. Efficient and practical non-blocking data structures.
;;; Department of Computer Engineering, Chalmers University of Technology, 2004.

;;; The structure `queue-element' is used to represent the elements of constant
;;; queues.  They have next-element, previous-element, and datum slots.  Note
;;; that these structures are declared to explicitly be of type vector, so as to
;;; eliminate the name and save a word of memory per instance.  Note that this
;;; means there is no predicate for this structure.

(def-structure (queue-element
                 (:type vector)
                 (:constructor make-queue-element
                  (queue-next-element queue-previous-element queue-datum))
                 ;; (:eliminate-for-products gsi)
                 )
  #+Lockfree-Deque
  (reserved-slot-for-chaining nil)
  #+Lockfree-Deque		    ; this cannot be the first slot which is also
  (reference-count-and-claim-bit 1) ; used for chaining
  ;; fix the literal number in `constant-queue-p' if more slots were added
  queue-next-element		; also head
  queue-previous-element	; also tail
  queue-datum)			; also mark

(defmacro reference-count (queue-element)
  `(ash (reference-count-and-claim-bit ,queue-element) -1))

(defmacro claim-bit (queue-element)
  `(ldb (byte 1 0) (reference-count-and-claim-bit ,queue-element)))

(defconstant constant-queue-marker :constant-queue-marker)

(def-substitution-macro constant-queue-p (thing)
  (and (simple-vector-p thing)
       (=f (length (the simple-vector thing))
	   #-Lockfree-Deque 3
	   #+Lockfree-Deque 5)
       (eq (queue-datum thing) constant-queue-marker)))

#+Lockfree-Deque
(defmacro safe-queue-read (place)
  (let ((q (gensym)))
    `(loop for ,q = ,place do
       (unless ,q (return nil))
       (atomic-incf (reference-count-and-claim-bit ,place) 2)
       (if (eq ,q ,place)
	   (return ,q)
	 (release-queue-node ,q)))))

#+Lockfree-Deque
(defmacro copy-queue-node (node-or-place) ; COPY_NODE
  `(safe-queue-read ,node-or-place))

#+Lockfree-Deque
(defun-simple read-queue-node (reference) ; READ_NODE
  (multiple-value-bind (node mark)
      (get-atomic-reference reference)
    (unless mark
      (safe-queue-read node))))

#+Lockfree-Deque ; READ_DEL_NODE
(defun-substitution-macro read-deleted-queue-node (reference)
  (let ((node (get-atomic-reference reference)))
    (safe-queue-read node)
    node))

#+Lockfree-Deque
(defun-simple create-queue-element (thing)
  (let ((node (make-queue-element-macro nil nil nil)))			  ; C1
    (setq node (safe-queue-read node))
    (clear-lowest-bit (reference-count-and-claim-bit node))
    (setf (queue-datum node) thing)					  ; C2
    node))								  ; C3

(defun release-queue-node (node)
  (when (null node)
    (return-from release-queue-node))
  #+Lockfree-Deque
  (when (=f 0 (decrement-and-test-and-set (reference-count-and-claim-bit node)))
    (return-from release-queue-node))
  #+Lockfree-Deque
  (release-reference node)
  (reclaim-queue-element-macro node))

;;; The function `make-empty-constant-queue' returns a new, empty constant
;;; queue.  Constant queues are represented with a queue-element, where the head
;;; of the queue is stored in the next-element slot, the tail of the queue is
;;; stored in the previous-element slot, and the datum slot contains the
;;; constant-queue-head marker.  Empty constant queues contain pointers back to
;;; the queue element in the head and tail slots.

#+Lockfree-Deque
(defconstant constant-queue-head-marker '(constant-queue-head-marker))
#+Lockfree-Deque
(defconstant constant-queue-tail-marker '(constant-queue-tail-marker))

(defmacro queue-next-element-real (queue-element)
  `(atomic-reference-object
     (queue-next-element ,queue-element)))

(defmacro queue-previous-element-real (queue-element)
  `(atomic-reference-object
     (queue-previous-element ,queue-element)))

#+Lockfree-Deque
(defun release-reference (node)
  (release-queue-node (queue-previous-element-real node))		  ; RR1
  (release-queue-node (queue-next-element-real node)))			  ; RR2

(defmacro constant-queue-head (constant-queue)
  `(queue-next-element ,constant-queue))

(defmacro constant-queue-tail (constant-queue)
  `(queue-previous-element ,constant-queue))

(def-substitution-macro constant-queue-head-if (constant-queue)
  (when constant-queue
    (constant-queue-head constant-queue)))

(def-substitution-macro constant-queue-tail-if (constant-queue)
  (when constant-queue
    (constant-queue-tail constant-queue)))

#-Lockfree-Deque
(defun-simple make-empty-constant-queue ()
  (let ((new-queue (make-queue-element-macro
                     nil nil constant-queue-marker)))
    (setf (constant-queue-head new-queue) new-queue)
    (setf (constant-queue-tail new-queue) new-queue)
    new-queue))

#+Lockfree-Deque
(defun-simple make-empty-constant-queue ()
  (let ((new-queue (make-queue-element-macro
		     nil nil constant-queue-marker))
	(head (make-queue-element-macro
		nil (make-atomic-reference nil) constant-queue-head-marker))
	(tail (make-queue-element-macro
		(make-atomic-reference nil) nil constant-queue-tail-marker)))
    (setq head (safe-queue-read head)
	  tail (safe-queue-read tail))
    (clear-lowest-bit (reference-count-and-claim-bit head))
    (clear-lowest-bit (reference-count-and-claim-bit tail))
    (setf (queue-next-element head) (make-atomic-reference tail))
    (setf (queue-previous-element tail) (make-atomic-reference head))
    (setf (constant-queue-head new-queue) head)
    (setf (constant-queue-tail new-queue) tail)
    new-queue))

;;; The `Next' function tries to change the cursor to the next position
;;; relative to the current position, and returns the status of success. The
;;; algorithm repeatedly in line NT2-NT11 checks the next node for possible
;;; traversal until the found node is present and is not the tail dummy node.
;;; If the current node is the tail dummy node, false is returned in line NT2.
;;; In line NT3 the next pointer of the current node is de-referenced and in
;;; line NT4 the deletion state of the found node is read. If the found node
;;; is deleted and the current node was deleted when directly next of the
;;; found node, this is detected in line NT5 and then the position is updated
;;; according to [Def 1]* in line NT10. If the found node was detected as
;;; present in line NT5, the cursor is set to the found node in line NT10 and
;;; true is returned (unless the found node is the tail dummy node when
;;; instead false is returned) in line NT11. Otherwise it's checked if the
;;; found node is not already fully deleted in line NT6 and then fulfils the
;;; deletion by calling the HelpDelete procedure after which the algorithm
;;; retries at line NT2. The linearizability point of a Next function that
;;; succeeds is the read sub-operation of the next pointer in line NT3. The
;;; linearizability point of cursor was the tail dummy node, and the read sub-
;;; operation of the next pointer in line NT3 otherwise.

;;; [Def 1] The position of a cursor that references a node that is present in
;;; the list is the referenced node. The position of a cursor that references
;;; a deleted node, is represented by the node that was logically next of the
;;; deleted node at the very moment of the deletion (i.e. the setting of the
;;; deletion mark). If that node is deleted as well, the position is equal to
;;; the position of a cursor referencing that node, and so on recursively. The
;;; actual position is then interpreted to be at an imaginary node directly
;;; previous of the representing node.

#-Lockfree-Deque
(defmacro constant-queue-next (cursor constant-queue)
  (declare (ignore constant-queue))
  `(queue-next-element ,cursor))

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-*-next ((cursor container)
			   tail-element
			   next-element
			   read-deleted-node
			   release-node
			   help-delete)
  `(progn
     (loop with tail = (,tail-element ,container)			  ; NT1
	   do
       (when (eq ,cursor tail) (return nil))				  ; NT2
       (let* ((next (,read-deleted-node (,next-element ,cursor)))	  ; NT3
	      (d (atomic-reference-mark (,next-element next))))		  ; NT4
	 (cond ((and d
		     (atomic-reference-neq
		       (,next-element ,cursor)
		       (make-atomic-reference next t)))			  ; NT5
		(when (eq next (atomic-reference-object
				 (,next-element ,cursor)))
		  (,help-delete next))					  ; NT6
		(,release-node next))					  ; NT7
	       (t
		(,release-node next) ; old: cursor			  ; NT9
		(setq ,cursor next)					  ; NT10
		(when (and (not d)
			   (neq next tail))
		  (return ,cursor))))))))				  ; NT11

#+Lockfree-Deque
(defun-simple constant-queue-next (cursor constant-queue)
  (generate-*-next (cursor constant-queue)
    constant-queue-tail
    queue-next-element
    read-deleted-queue-node
    release-queue-node
    help-delete-queue-node))

;;; The `Prev' function tries to change the cursor to the previous position
;;; relative to the current position, and returns the status of success. The
;;; algorithm repeatedly in line PV2-PV11 checks the next node for possible
;;; traversal until the found node is present and is not the head dummy node.
;;; If the current node is the head dummy node, false is returned in line PV2.
;;; In line PV3 the prev pointer of the current node is de-referenced. If the
;;; found node is directly previous of the current node and the current node
;;; is present, this is detected in line PV4 and then the cursor is set to the
;;; found node in line PV6 and true is returned (unless the found node is the
;;; head dummy node when instead false is returned) in line PV7. If the current
;;; node is deleted then the cursor position is updated according to [Def 1]*
;;; by calling the `Next' function in line PV8. Otherwise the prev pointer of
;;; the current node is updated by calling the `HelpInsert' function in line
;;; PV10 after which the algorithm retries at line PV2. The linearizability
;;; point of a Prev function that succeeds is the read sub-operation of the prev
;;; pointer in line PV13. The linearizability point of a Prev function that
;;; fails is line PV2 if the node positioned by the original cursor was the head
;;; dummy node, and the read sub-operation of the prev pointer in line PV3
;;; otherwise.

#-Lockfree-Deque
(defmacro constant-queue-previous (cursor constant-queue)
  (declare (ignore constant-queue))
  `(queue-previous-element ,cursor))

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-*-previous ((cursor structure)
			       head-element
			       next-element
			       previous-element
			       read-deleted-node
			       release-node
			       help-insert
			       structure-next)
  `(progn
     (loop with head = (,head-element ,structure)			  ; PV1
	   do
       (when (eq ,cursor head) (return nil))				  ; PV2
       (let ((prev (,read-deleted-node
		     (,previous-element ,cursor))))			  ; PV3
	 (cond ((and (atomic-reference-equal
		       (,next-element prev)
		       (make-atomic-reference ,cursor nil))
		     (not (atomic-reference-mark
			    (,next-element ,cursor))))			  ; PV4
		(,release-node prev) ; old: cursor			  ; PV5
		(setq ,cursor prev)					  ; PV6
		(when (neq prev head) (return ,cursor)))		  ; PV7
	       ((atomic-reference-mark (,next-element ,cursor))
		(setq ,cursor
		      (,structure-next ,cursor ,structure)))		  ; PV8
	       (t							  ; PV9
		(setq prev (,help-insert prev ,cursor))			  ; PV10
		(,release-node prev)))))))				  ; PV11

#+Lockfree-Deque
(defun constant-queue-previous (cursor constant-queue)
  (generate-*-previous (cursor constant-queue)
    constant-queue-head
    queue-next-element
    queue-previous-element
    read-deleted-queue-node
    release-queue-node
    help-insert-queue-node
    constant-queue-next))

;;; The `Read' function returns the current value of the node referenced by
;;; the cursor, unless this node is deleted or the node is equal to any of
;;; the dummy nodes when the function instead returns a non-value. In line
;;; RD1 the algorithm checks if the node referenced by the cursor is either
;;; the head or tail dummy node, and then returns a non-value. The value of
;;; the node is read in line RD2, and in line RD3 it is checked if the node
;;; is deleted and then returns a non-value, otherwise the value is returned
;;; in line RD4. The linearizability point of a Read function that returns
;;; a value is the read sub-operation of the next pointer in line RD3. The
;;; linearizability point of a Read function that returns a non-value is the
;;; read sub-operation of the next pointer in line RD3, unless the node
;;; positioned by the cursor was the head or tail dummy node when the
;;; linearizability point is line RD1.

#+Lockfree-Deque
(defun constant-queue-read (cursor &optional constant-queue)
  (if (or (eq cursor (constant-queue-head-if constant-queue))		  ; RD1
	  (eq cursor (constant-queue-tail-if constant-queue)))
      nil
    (let ((value (queue-datum cursor)))					  ; RD2
      (if (atomic-reference-mark (queue-next-element cursor))		  ; RD3
	  nil
	value))))							  ; RD4

#-Lockfree-Deque
(defun constant-queue-read (cursor &optional constant-queue)
  (declare (ignore constant-queue))
  (let ((value (queue-datum cursor)))
    value))

#-Lockfree-Deque
(defun-simple clear-constant-queue (constant-queue)
  (declare (eliminate-for-gsi))
  (loop for element = (constant-queue-head constant-queue)
                    then (prog1 (queue-next-element element)
                                (reclaim-queue-element-macro element))
        until (eq element constant-queue))
  (setf (constant-queue-head constant-queue) constant-queue)
  (setf (constant-queue-tail constant-queue) constant-queue)
  constant-queue)

#+Lockfree-Deque
(defun-simple clear-constant-queue (constant-queue)
  (declare (eliminate-for-gsi))
  (let ((head (constant-queue-head constant-queue))
        (tail (constant-queue-tail constant-queue)))
    (loop with next-element-structure = nil
	  for element-structure = (queue-next-element-real head)
	                        then next-element-structure
	  until (eq element-structure tail)
	  do
      (setf next-element-structure (queue-next-element-real element-structure))
      (reclaim-queue-element-macro element-structure))
    (setf (queue-next-element head)
          (make-atomic-reference tail))
    (setf (queue-previous-element tail)
          (make-atomic-reference head))
    constant-queue))

#-Lockfree-Deque
(defun-simple reclaim-constant-queue (constant-queue)
  (loop for element = (constant-queue-head constant-queue)
                    then (prog1 (queue-next-element element)
                                #+development
                                (setf (queue-next-element element) nil)
                                (reclaim-queue-element-macro element))
        until (eq element constant-queue))
  (setf (queue-datum constant-queue) nil)
  (reclaim-queue-element-macro constant-queue)
  nil)

#+Lockfree-Deque
(defun-simple reclaim-constant-queue (constant-queue)
  (let ((head (constant-queue-head constant-queue))
        (tail (constant-queue-tail constant-queue)))
    (loop for element = head
                   then (prog1 (queue-next-element-real element)
                          (reclaim-queue-element-macro element))
          until (eq element tail)
          finally (reclaim-queue-element-macro element)))
  (setf (queue-datum constant-queue) nil)
  (reclaim-queue-element-macro constant-queue)
  nil)

#+development
(def-development-printer print-constant-queue (queue stream)
  (when (constant-queue-p queue)
    (printing-random-object (queue stream)
      (format stream "CONSTANT-QUEUE"))
    queue))

;;; The macro `constant-queue-peek' takes a constant queue and returns the
;;; next item to be dequeued.

#-Lockfree-Deque
(defmacro constant-queue-peek (constant-queue &optional (default-value nil))
  (let ((queue-var (if (symbolp constant-queue) constant-queue (gensym)))
        (first-entry (gensym)))
    `(let* (,@(if (neq queue-var constant-queue)
                  `((,queue-var ,constant-queue)))
            (,first-entry (constant-queue-head ,queue-var)))
       (if (neq ,first-entry ,queue-var)
           (queue-datum ,first-entry)
         ,default-value))))

#+Lockfree-Deque
(defmacro constant-queue-peek (constant-queue &optional (default-value nil))
  (let ((queue-var (if (symbolp constant-queue)
		       constant-queue
		     (make-symbol "QUEUE")))
	(head (make-symbol "HEAD"))
	(first (make-symbol "FIRST")))
    `(let* (,@(if (neq queue-var constant-queue)
		  `((,queue-var ,constant-queue)))
	    (,head (constant-queue-head ,queue-var))
	    (,first (constant-queue-next ,head ,queue-var)))
       (if ,first
	   (constant-queue-read ,first ,queue-var)
	 ,default-value))))

;;; The substitution macro `constant-queue-empty-p' returns whether or not the
;;; queue is empty.  If you want the datum of the first queue entry, call
;;; constant-queue-peek.

(def-substitution-macro constant-queue-empty-p (constant-queue)
  #-Lockfree-Deque
  (eq (constant-queue-head constant-queue) constant-queue)
  #+Lockfree-Deque
  (null (constant-queue-next
	  (constant-queue-head constant-queue) constant-queue)))

(def-substitution-macro constant-queue-non-empty-p (constant-queue)
  (not (constant-queue-empty-p constant-queue)))

;;; The macro `constant-queue-enqueue' takes a constant queue and a thing to
;;; be enqueued, and enqueues that item in the queue for FIFO dequeuing.  This
;;; function returns the new entry for the given thing in the queue.

;;; Since the head and tail pointers of an empty queue point back to the queue
;;; itself, we do not need to check for the empty queue in this enqueuing
;;; operation.  This is true since setting the "next-element" of the "tail"
;;; actually sets the head pointer of the queue in the empty queue case.

#-Lockfree-Deque
(defmacro constant-queue-enqueue (constant-queue thing)
  (let* ((queue-var (if (symbolp constant-queue)
                        constant-queue
                        (gensym)))
         (tail (gensym))
         (new-element (gensym)))
    `(let* (,@(if (neq queue-var constant-queue)
                  `((,queue-var ,constant-queue)))
            (,tail (constant-queue-tail ,queue-var))
            (,new-element (make-queue-element-macro ,queue-var ,tail ,thing)))
       (setf (queue-next-element ,tail) ,new-element)
       (setf (constant-queue-tail ,queue-var) ,new-element)
       ,new-element)))

;;; The PushRight operation inserts a new node at the rightmost position in the
;;; deque. The algorithm first repeatedly tries in lines R4-R13 to insert the
;;; new node (node) between the rightmost node (prev) and the tail node (next),
;;; by atomically changing the next pointer of the prev node. Before trying to
;;; update the next pointer, it assures in line R5 that the next node is still
;;; the very next node of prev, otherwise prev is updated by calling the Help-
;;; Insert function in R6, which updates the prev pointer of the next node.
;;; After the new node has been successfully inserted, it tries in lines P1-P13
;;; to update the prev pointer of the next node, following the same scheme as
;;; for the PushLeft operation.

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-*-push-common ((node next)
				  previous-element
				  next-element
				  copy-node
				  release-node
				  help-insert)
  `(progn
     (let ((backoff-limit backoff-min-delay))
       (loop as link1 = (,previous-element ,next)			  ; P1+P2
	     do
	 (when (or (atomic-reference-mark link1)			  ; P3
		   (atomic-reference-neq (,next-element ,node)
					 (make-atomic-reference ,next nil)))
	   (loop-finish))						  ; P4
	 (when (compare-and-swap (,previous-element ,next)
				 link1
				 (make-atomic-reference ,node nil))	  ; P5
	   (,copy-node ,node)						  ; P6
	   (,release-node (atomic-reference-object link1))		  ; P7
	   (when (atomic-reference-mark (,previous-element ,node))	  ; P8
	     (let ((prev2 (,copy-node ,node)))				  ; P9
	       (setq prev2 (,help-insert prev2 ,next))			  ; P10
	       (,release-node prev2)))					  ; P11
	   (loop-finish))						  ; P12
	 (back-off)))							  ; P13
     (,release-node ,next)						  ; P14
     (,release-node ,node)))						  ; P15

#+Lockfree-Deque
(defun-void constant-queue-push-common (node next)
  (generate-*-push-common (node next)
    queue-previous-element
    queue-next-element
    copy-queue-node
    release-queue-node
    help-insert-queue-node))

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-*-push-right ((structure
				  tail-element
				  previous-element
				  next-element
				  copy-node
				  read-node
				  help-insert
				  push-common)
				 create-action)
  `(progn
     (let* ((node ,create-action)					  ; R1
	    (next (,copy-node (,tail-element ,structure)))		  ; R2
	    (prev (,read-node (,previous-element next)))		  ; R3
	    (backoff-limit backoff-min-delay))
       (loop								  ; R4
	 (cond
	   ((atomic-reference-neq (,next-element prev)
				  (make-atomic-reference next nil))	  ; R5
	    (setq prev (,help-insert prev next)))			  ; R6
	   (t								  ; R7
	    (setf (,previous-element node)
		  (make-atomic-reference prev nil))			  ; R8
	    (setf (,next-element node)
		  (make-atomic-reference next nil))			  ; R9
	    (when (compare-and-swap (,next-element prev)
				    (make-atomic-reference next nil)
				    (make-atomic-reference node nil))	  ; R10
	      (,copy-node node)						  ; R11
	      (loop-finish))						  ; R12
	    (back-off))))						  ; R13
       (,push-common node next)						  ; R14
       node)))

#+Lockfree-Deque
(defun-simple constant-queue-push-right (constant-queue thing)
  (generate-*-push-right (constant-queue
			  constant-queue-tail
			  queue-previous-element
			  queue-next-element
			  copy-queue-node
			  read-queue-node
			  help-insert-queue-node
			  constant-queue-push-common)
    (create-queue-element thing)))

#+Lockfree-Deque
(defmacro constant-queue-enqueue (constant-queue thing)
  `(constant-queue-push-right ,constant-queue ,thing))

;;; The function `constant-queue-filo-enqueue' takes a constant queue and a
;;; thing to be enqueued, and enqueues that item in the queue for FILO
;;; dequeueing.  This function returns the new entry for the given thing in the
;;; queue.

#-Lockfree-Deque
(defmacro constant-queue-filo-enqueue (constant-queue thing)
  (let* ((queue-var (if (symbolp constant-queue) constant-queue (gensym)))
         (head (gensym))
         (new-element (gensym)))
    `(let* (,@(if (neq queue-var constant-queue)
                  `((,queue-var ,constant-queue)))
            (,head (constant-queue-head ,queue-var))
            (,new-element (make-queue-element-macro ,head ,queue-var ,thing)))
       (setf (constant-queue-head ,queue-var) ,new-element)
       (setf (queue-previous-element ,head) ,new-element)
       ,new-element)))

;;; The PushLeft operation inserts a new node at the leftmost position in the
;;; deque. The algorithm first repeatedly tries in lines L4-L14 to insert the
;;; new node (node) between the head node (prev) and the leftmost node (next),
;;; by atomically changing the next pointer of the head node. Before trying to
;;; update the next pointer, it assures in line L5 that the next node is still
;;; the very next node of head, otherwise next is updated in L6-L7. After the
;;; new node has been successfully inserted, it tries in lines P1-P13 to update
;;; the prev pointer of the next node. It retries until either i) it succeeds
;;; with the update, ii) it detects that either the next or new node is deleted,
;;; or iii) the next node is no longer directly next of the new node. In any of
;;; the two latter, the changes are due to concurrent Pop or Push operations,
;;; and the responsibility to update the prev pointer is then left to those. If
;;; the update succeeds, there is though the possibility that the new node was
;;; detected (and thus the prev pointer of the next node was possibly already
;;; updated by the concurrent Pop operation) directly before the CAS in line P5,
;;; and then the prev pointer is updated by calling the HelpInsert function in
;;; line P10.

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-*-push-left ((structure
				 head-element
				 previous-element
				 next-element
				 copy-node
				 read-node
				 release-node
				 push-common)
				create-action)
  `(progn
     (let* ((node ,create-action)					  ; L1
	    (prev (,copy-node (,head-element ,structure)))		  ; L2
	    (next (read-queue-node (queue-next-element prev)))		  ; L3
	    (backoff-limit backoff-min-delay))
       (loop								  ; L4
	 (cond
	   ((atomic-reference-neq (,next-element prev)
				  (make-atomic-reference next nil))	  ; L5
	    (,release-node next)					  ; L6
	    (setq next (,read-node (,next-element prev))))		  ; L7
	   (t								  ; L8
	    (setf (,previous-element node)
		  (make-atomic-reference prev nil))			  ; L9
	    (setf (,next-element node)
		  (make-atomic-reference next nil))			  ; L10
	    (when (compare-and-swap (,next-element prev)
				    (make-atomic-reference next nil)
				    (make-atomic-reference node nil))	  ; L11
	      (,copy-node node)						  ; L12
	      (loop-finish))						  ; L13
	    (back-off))))						  ; L14
       (,push-common node next)						  ; L15
       node)))

#+Lockfree-Deque
(defun-simple constant-queue-push-left (constant-queue thing)
  (generate-*-push-left (constant-queue
			 constant-queue-head
			 queue-previous-element
			 queue-next-element
			 copy-queue-node
			 read-queue-node
			 release-queue-node
			 constant-queue-push-common)
    (create-queue-element thing)))

#+Lockfree-Deque
(defmacro constant-queue-filo-enqueue (constant-queue thing)
  `(constant-queue-push-left ,constant-queue ,thing))

;;; The macro `constant-queue-dequeue' takes a constant queue and an optional
;;; value to return if the queue is empty.  It dequeues and returns the first
;;; element of the queue, or returns the given value if the queue is empty.
;;; Note that this is a NON-STANDARD MACRO in that the default value will only
;;; be evaluated if the queue is empty.

#-Lockfree-Deque
(defmacro constant-queue-dequeue (constant-queue &optional (default-value nil))
  (let ((queue-var (if (symbolp constant-queue)
                       constant-queue
                       (gensym)))
        (head (gensym))
        (datum (gensym))
        (new-head (gensym)))
    `(let* (,@(if (neq queue-var constant-queue)
                  `((,queue-var ,constant-queue)))
            (,head (constant-queue-head ,queue-var)))
       (if (eq ,head ,queue-var)
           (values ,default-value nil)
           (let ((,datum (queue-datum ,head))
                 (,new-head (queue-next-element ,head)))
             (setf (constant-queue-head ,queue-var) ,new-head)
             (setf (queue-previous-element ,new-head) ,queue-var)
             (reclaim-queue-element-macro ,head)
             (values ,datum t))))))

;;; The PopLeft operation tries to delete and return the value of the leftmost
;;; node in the deque. The algorithm first repeatedly tries in lines PL2-PL22 to
;;; mark the leftmost node (node) as deleted. Before trying to update the next
;;; pointer, it first assures in line PL4 that the deque is not empty, and secondly
;;; in line PL9 that the node is not already marked for deletion. If the deque
;;; was detected to be empty, the function returns. If node was marked for detection,
;;; it tries to update the next pointer of the prev node by calling the HelpDelete
;;; function, and then node is updated to be the leftmost node. If the prev pointer
;;; of node was incorrect, it tries to update it by calling the HelpInsert function.
;;; After the node has been successfully marked by the successful CAS operation in
;;; line PL13, it tries in line PL14 to update the next pointer of the prev node by
;;; calling the HelpDelete function, and in line PL16 to update the prev pointer of
;;; the next node by calling the HelpInsert function. After this, it tries in line
;;; PL23 to break possible cyclic references that includes node by calling the
;;; RemoveCrossReference function.

#+Lockfree-Deque
(defun constant-queue-pop-left (constant-queue &optional default-value)
  (let ((prev (copy-queue-node (constant-queue-head constant-queue)))	  ; PL1
	(tail (constant-queue-tail constant-queue))
	(node nil)
	(return-value default-value)
	(backoff-limit backoff-min-delay))
    (loop								  ; PL2
      (setq node (read-queue-node (queue-next-element prev)))		  ; PL3
      (when (eq node tail)						  ; PL4
	(release-queue-node node)					  ; PL5
	(release-queue-node prev)					  ; PL6
	(return-from constant-queue-pop-left
	  (values default-value nil)))					  ; PL7
      (let ((link1 (queue-next-element node)))				  ; PL8
	(cond
	  ((atomic-reference-mark link1)				  ; PL9
	   (help-delete-queue-node node)				  ; PL10
	   (release-queue-node node))					  ; PL11
	  (t
	   (when (compare-and-swap (queue-next-element node)
				   link1
				   (make-atomic-reference
				     (atomic-reference-object link1) t))  ; PL13
	     (help-delete-queue-node node)				  ; PL14
	     (let* ((next
		     (read-deleted-queue-node
		       (queue-next-element node)))			  ; PL15
		    (prev2 (help-insert-queue-node prev next)))		  ; PL16
	       (release-queue-node prev2)				  ; PL17
	       (release-queue-node next)				  ; PL18
	       (setq return-value (queue-datum node))			  ; PL19
	       (loop-finish)))						  ; PL20
	   (release-queue-node node)					  ; PL21
	   (back-off)))))						  ; PL22
    (remove-queue-cross-reference node)					  ; PL23
    (release-queue-node node)						  ; PL24
    (values return-value t)))						  ; PL25

#+Lockfree-Deque
(defmacro constant-queue-dequeue (constant-queue &optional (default-value nil))
  `(constant-queue-pop-left ,constant-queue ,default-value))

;;; The PopRight operation tries to delete and return the value of the rightmost
;;; node in the deque. The algorithm first repeatedly tries in lines PR2-PR19 to
;;; mark the rightmost node (node) as deleted. Before trying to update the next
;;; pointer, it assures i) in line PR4 that the node is not already marked for
;;; deletion, ii) in the same line that the prev pointer of the tail (next) node
;;; is correct, and iii) in line PR7 that the deque is not empty. If the deque
;;; was detected to be empty, the function returns. If node was marked for deletion
;;; or the prev pointer of the next node was incorrect, it tries to update the
;;; prev pointer of the next node by calling the HelpInsert function, and then
;;; node is updated to be the rightmost node. After the node has been successfully
;;; marked it follows the same scheme as the PopLeft operation.

#+Lockfree-Deque
(defun constant-queue-pop-right (constant-queue &optional default-value)
  (let* ((next (copy-queue-node (constant-queue-tail constant-queue)))	  ; PR1
	 (node (read-queue-node (queue-previous-element next)))		  ; PR2
	 (return-value default-value)
	 (backoff-limit backoff-min-delay))
    (loop								  ; PR3
      (cond
        ((atomic-reference-neq (queue-next-element node)
			       (make-atomic-reference next nil))	  ; PR4
	 (setq node (help-insert-queue-node node next)))		  ; PR5
	(t								  ; PR6
	 (when (eq node (constant-queue-head constant-queue))		  ; PR7
	   (release-queue-node node)					  ; PR8
	   (release-queue-node next)					  ; PR9
	   (return-from constant-queue-pop-right
	     (values default-value nil)))				  ; PR10
	 (when (compare-and-swap (queue-next-element node)
				 (make-atomic-reference next nil)
				 (make-atomic-reference next t))	  ; PR11
	   (help-delete-queue-node node)				  ; PR12
	   (let* ((prev
		   (read-deleted-queue-node
		     (queue-previous-element node)))			  ; PR13
		  (prev2 (help-insert-queue-node prev next)))		  ; PR14
	     (release-queue-node prev2)					  ; PR15
	     (release-queue-node next)					  ; PR16
	     (setq return-value (queue-datum node))			  ; PR17
	     (loop-finish)))						  ; PR18
	 (back-off))))							  ; PR19
    (remove-queue-cross-reference node)					  ; PR20
    (release-queue-node node)						  ; PR21
    (values return-value t)))						  ; PR22

#+Lockfree-Deque
(defmacro constant-queue-filo-dequeue (constant-queue &optional (default-value nil))
  `(constant-queue-pop-right ,constant-queue ,default-value))

;;; Helping and Back-Off

;;; The HelpDelete sub-procedure tries to set the deletion mark of the prev
;;; pointer and then atomically update the next pointer of the previous node
;;; of the to-be-deleted node, thus fulfilling step 2 and 3 of the overall
;;; node deletion scheme. The algorithm first ensures in line HD1-HD4 that
;;; the deletion mark on the prev pointer of the given node is set. It then
;;; repeatedly tries in lines HD8-HD34 to delete (in the sense of a chain of
;;; next pointers starting from the head node) the given marked node (node)
;;; by changing the next pointer from the previous non-marked node. First, we
;;; can safely assume that the next pointer of the marked node is always
;;; referring to a node (next) to the right and the prev pointer is always
;;; referring to a node (prev) to the left (not necessarily the first). Before
;;; trying to update the next pointer with the CAS operation in line HD30, it
;;; assumes in line HD9 that node is not already deleted, in line HD10 that
;;; the next node is not marked, in line HD16 that the prev node is not marked,
;;; and in HD24 that prev is the previous node of node. If next is marked, it
;;; is updated to be the next node. If prev is marked we might need to delete
;;; it before we can update prev to one of its previous nodes and proceed with
;;; the current deletion, but in order to avoid unnecessary and even possibly
;;; infinite recursion, HelpDelete is only called if a next pointer from a non-
;;; marked node to prev has been observed (i.e. lastlink.d is false). Otherwise
;;; if prev is not the previous node of node it is updated to be the next node.

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-help-delete ((node)
				previous-element
				next-element
				read-node
				read-deleted-node
				copy-node
				release-node
				help-delete)
  `(progn
     (loop as link1 = (,previous-element ,node) do			  ; HD1+HD2
       (when (or (atomic-reference-mark link1)				  ; HD3
		 (compare-and-swap (,previous-element ,node)		  ; HD4
				   link1
				   (make-atomic-reference
				     (atomic-reference-object link1) t)))
	 (loop-finish)))
     (let ((lastlink-deleted? t)					  ; HD5
	   (prev (,read-deleted-node (,previous-element ,node)))	  ; HD6
	   (next (,read-deleted-node (,next-element ,node)))		  ; HD7
	   (backoff-limit backoff-min-delay))
       (loop								  ; HD8
	 (when (eq prev next) (loop-finish))				  ; HD9
	 (cond
	   ((atomic-reference-mark (,next-element next))		  ; HD10
	    (let ((next2
		   (,read-deleted-node (,next-element next))))		  ; HD11
	      (,release-node next)					  ; HD12
	      (setq next next2)))					  ; HD13
	   (t
	    (let ((prev2 (,read-node (,next-element prev))))		  ; HD15
	      (cond
	        ((null prev2)						  ; HD16
		 (when (not lastlink-deleted?)				  ; HD17
		   (,help-delete prev) ; recursive call		  ; HD18
		   (setq lastlink-deleted? t))				  ; HD19
		 (setq prev2
		       (,read-deleted-node (,previous-element prev)))	  ; HD20
		 (,release-node prev)					  ; HD21
		 (setq prev prev2))					  ; HD22
		((neq prev2 ,node)					  ; HD24
		 (setq lastlink-deleted? nil)				  ; HD25
		 (,release-node prev)					  ; HD26
		 (setq prev prev2))					  ; HD27
		(t ; (eq prev2 node)
		 (,release-node prev2)					  ; HD29
		 (when (compare-and-swap (,next-element prev)		  ; HD30
					 (make-atomic-reference ,node nil)
					 (make-atomic-reference next nil))
		   (,copy-node next)					  ; HD31
		   (,release-node ,node)				  ; HD32
		   (loop-finish))					  ; HD33
		 (back-off)))))))					  ; HD34
       (,release-node prev)						  ; HD35
       (,release-node next))))						  ; HD36

#+Lockfree-Deque
(defun-void help-delete-queue-node (node)
  (generate-help-delete (node)
    queue-previous-element
    queue-next-element
    read-queue-node
    read-deleted-queue-node
    copy-queue-node
    release-queue-node
    help-delete-queue-node))

;;; The HelpInsert sub-function tries to update the prev pointer of a node and
;;; then return a reference to a possibly direct previous node, thus fulfilling
;;; step 2 of the overall insertion scheme or step 4 of the overall deletion
;;; scheme. The algorithm repeatedly tries in lines HI2-HI27 to correct the prev
;;; pointer of the given node (node), given a suggestion of a previous (not
;;; necessarily the directly previous) node (prev). Before trying to update the
;;; prev pointer with the CAS operation in line HI22, it assures in line HI4 that
;;; the prev node is not marked, in line HI13 that node is not marked, and in
;;; line HI16 that prev is the previous node of node. If prev is marked we might
;;; need to delete it before we can update prev to one of its previous nodes and
;;; proceed with the current insertion, but in order to avoid unnecessary
;;; recursion, HelpDelete is only called if a next pointer from a non-marked node
;;; to prev has been observed (i.e. lastlink.d is false). If node is marked, the
;;; procedure is aborted. Otherwise if prev is not the previous node of node it
;;; is updated to be the next node. If the update in line HI22 succeeds, there is
;;; though the possibility that the prev node was deleted (and thus the prev
;;; pointer of node was possibly already updated by the concurrent Pop operation)
;;; directly before the CAS operation. This is detected in line HI25 and then the
;;; update is possibly retried with a new prev node.

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-help-insert ((prev node)
				previous-element
				next-element
				read-node
				read-deleted-node
				copy-node
				release-node
				help-delete)
  `(progn
     (let ((backoff-limit backoff-min-delay)
	   (lastlink-deleted? t))					  ; HI1
       (loop as prev2 = (,read-node (,next-element ,prev))		  ; HI3+HI3
	     do
	 (cond
	   ((null prev2)						  ; HI4
	    (when (not lastlink-deleted?)				  ; HI5
	      (,help-delete ,prev)					  ; HI6
	      (setq lastlink-deleted? t))				  ; HI7
	    (setq prev2
		  (,read-deleted-node (,previous-element ,prev)))	  ; HI8
	    (,release-node ,prev)					  ; HI9
	    (setq ,prev prev2))						  ; HI10
	   (t
	    (let ((link1 (,previous-element ,node)))			  ; HI12
	      (when (atomic-reference-mark link1)			  ; HI13
		(,release-node prev2)					  ; HI14
		(return ,prev))						  ; HI15
	      (cond
	        ((neq prev2 ,node)					  ; HI16
		 (setq lastlink-deleted? nil)				  ; HI17
		 (,release-node ,prev)					  ; HI18
		 (setq ,prev prev2))					  ; HI19
		(t
		 (,release-node prev2)					  ; HI21
		 (when (compare-and-swap (,previous-element ,node)	  ; HI22
					 link1
					 (make-atomic-reference ,prev nil))
		   (,copy-node ,prev)					  ; HI23
		   (,release-node (atomic-reference-object link1))	  ; HI24
		   (unless (atomic-reference-mark
			     (,previous-element ,prev))			  ; HI25
		     (return ,prev)))					  ; HI26
		 (back-off))))))))))					  ; HI27

#+Lockfree-Deque
(defun-simple help-insert-queue-node (prev node)
  (generate-help-insert (prev node)
    queue-previous-element
    queue-next-element
    read-queue-node
    read-deleted-queue-node
    copy-queue-node
    release-queue-node
    help-delete-queue-node))

;;; The RemoveCrossReference sub-procedure tries to break cross-references
;;; between the given node (node) and any of the nodes that it references, by
;;; repeatedly updating the prev and next pointer as long as they reference a
;;; marked node. First, we can safely assume that the prev or next field of
;;; node is not concurrently updated by any other operation, as this procedure
;;; is only called by the main operation that deleted the node and both the
;;; next and prev pointers are marked and thus any concurrent update using CAS
;;; will fail. Before the procedure is finished, it assures in the next node
;;; (next) is not marked. As long as prev is marked it is traversed to the left,
;;; and as long as next is marked it is traversed to the right, while
;;; continuously updating the prev or next field of node in lines RC5 or RC11.

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-remove-cross-reference ((node)
					   previous-element
					   next-element
					   read-deleted-node
					   release-node)
  `(progn
     (loop as prev = (atomic-reference-object (,previous-element ,node))  ; RC1
	   do								  ; RC2
       (cond
	 ((atomic-reference-mark (,next-element prev))			  ; RC3
	  (let ((prev2 (,read-deleted-node
			 (,previous-element prev))))			  ; RC4
	    (setf (,previous-element ,node)
		  (make-atomic-reference prev2 t))			  ; RC5
	    (,release-node prev)))					  ; RC6
	 (t
	  (let ((next (atomic-reference-object (,next-element ,node))))	  ; RC8
	    (if (atomic-reference-mark (,next-element next))		  ; RC9
		(let ((next2 (,read-deleted-node
			       (,next-element next))))			  ; RC10
		  (setf (,next-element ,node)
			(make-atomic-reference next2 t))		  ; RC11
		  (,release-node next))					  ; RC12
	      (loop-finish))))))))					  ; RC14

#+Lockfree-Deque
(defun-void remove-queue-cross-reference (node)
  (generate-remove-cross-reference (node)
    queue-previous-element
    queue-next-element
    read-deleted-queue-node
    release-queue-node))

;;; The `InsertBefore' operation inserts a new node directly before the node
;;; positioned by the given cursor and later changes the cursor to position
;;; the inserted node. If the node positioned by the cursor is the head
;;; dummy node, the new node will be inserted directly after the head dummy
;;; node. The algorithm checks in line IB1 if the cursor position is equal
;;; to the head dummy node, and consequently then calls the `InsertAfter'
;;; operation to insert the new node directly after the head dummy node.
;;; The algorithm repeatedly tries in lines IB4-IB13 to insert the new node
;;; (node) between the previous node (prev) of the cursor and the cursor
;;; positioned node, by atomically changing the next pointer of the prev node
;;; to instead point to the new node. If the node positioned by the cursor is
;;; deleted this is deleted in line IB4 and the cursor is updated by calling
;;; the `Next' function. If the update of the next pointer of the prev node
;;; by using the CAS operation in line IB8 fails, this is because either the
;;; prev node is no longer the directly previous node of the cursor
;;; positioned node, or that the cursor positioned node is deleted. If the
;;; prev node is no longer the directly previous node this is deleted in
;;; line IB11 and then the `HelpInsert' function is called in order to
;;; update the prev pointer of the cursor positioned node. If the update
;;; using CAS in line IB8 succeeds, the cursor position is set to the new
;;; node in line IB15 and the prev pointer of the previous cursor positioned
;;; node is updated by calling the `HelpInsert' function in line IB16. The
;;; linearizability point of the InsertBefore operation is the successful
;;; CAS operation in line IB8, or equal to the linearizability point of the
;;; InsertBefore operation if that operation was called in line IB1.

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-*-insert-before ((function-name structure cursor
				     structure-head
				     structure-next
				     previous-element next-element
				     read-deleted-node copy-node
				     release-node help-insert)
				    create-action
				    insert-after-action)
  `(progn
     (when (eq ,cursor (,structure-head ,structure))
       (return-from ,function-name ,insert-after-action))		  ; IB1
     (let ((node ,create-action)					  ; IB2
	   (backoff-limit backoff-min-delay))
       (loop doing							  ; IB3
	 (when (atomic-reference-mark (,next-element ,cursor))
	   (setq ,cursor (,structure-next ,cursor ,structure)))		  ; IB4
	 (let ((prev (,read-deleted-node
		       (,previous-element ,cursor))))			  ; IB5
	   (setf (,previous-element node)
		 (make-atomic-reference prev nil))			  ; IB6
	   (setf (,next-element node)
		 (make-atomic-reference ,cursor nil))			  ; IB7
	   (when (compare-and-swap (,next-element prev)
				   (make-atomic-reference ,cursor nil)
				   (make-atomic-reference node nil))	  ; IB8
	     (,copy-node node)						  ; IB9
	     (loop-finish))						  ; IB10
	   (when (atomic-reference-neq (,next-element prev)
				       (make-atomic-reference ,cursor nil))
	     (setq prev (,help-insert prev ,cursor)))			  ; IB11
	   (,release-node prev)						  ; IB12
	   (back-off)))							  ; IB13
       (let ((next ,cursor))						  ; IB14
	 #+ignore
	 (setq cursor (,copy-node node))				  ; IB15
	 (setq node (,help-insert node next))				  ; IB16
	 (,release-node node)						  ; IB17
	 #+ignore
	 (,release-node next))						  ; IB18
       node)))

#+Lockfree-Deque
(defun-simple constant-queue-insert-before (constant-queue cursor thing)
  (generate-*-insert-before (constant-queue-insert-before constant-queue cursor
			     constant-queue-head
			     constant-queue-next
			     queue-previous-element
			     queue-next-element
			     read-deleted-queue-node
			     copy-queue-node
			     release-queue-node
			     help-insert-queue-node)
    (create-queue-element thing)
    (constant-queue-insert-after constant-queue cursor thing)))

#-Lockfree-Deque
(defmacro constant-queue-insert-before (constant-queue cursor thing)
  (let* ((queue-var (if (symbolp constant-queue)
			constant-queue
		        (gensym)))
         (head (gensym))
         (new-element (gensym)))
    `(let* (,@(if (neq queue-var constant-queue)
                  `((,queue-var ,constant-queue))))
       (if (eq ,cursor ,queue-var)
	   (constant-queue-enqueue ,queue-var ,thing)
	 (let* ((,head (queue-previous-element ,cursor))
		(,new-element (make-queue-element-macro ,cursor ,head ,thing)))
	   (setf (queue-previous-element ,cursor) ,new-element)
	   (if (eq ,head ,queue-var) ; cursor is head
	       (setf (constant-queue-head ,queue-var) ,new-element)
	     (setf (queue-next-element ,head) ,new-element))
	   ,new-element)))))

;;; The `InsertAfter' operation inserts a new node directly after the node
;;; positioned by the given cursor and later changes the cursor to position
;;; inserted node. If the node positioned by the cursor is the tail dummy
;;; node, the new node will be inserted directly before the tail dummy node.
;;; The algorithm checks in line IA1 if the cursor position is equal to the
;;; tail dummy node, and consequently then calls the `InsertBefore' operation
;;; to insert the new node directly after the head dummy node. The algorithm
;;; repeatedly tries in lines IA4-IA14 to insert the new node (node) between
;;; the cursor positioned node and the next node (next) of the cursor, by
;;; atomically changing the next pointer of the cursor positioned node to
;;; instead point to the new node. If the update of the next pointer of the
;;; cursor positioned node by using the CAS operation in line IA7 fails, this
;;; is because either the next node is no longer the directly next node of
;;; the cursor positioned node, or that the cursor positioned node is deleted.
;;; If the cursor positioned node is deleted, the operation to insert directly
;;; after the cursor position now becomes the problem of inserting
;;; directly before the node that represents the cursor position according to
;;; [Def 1]*. It is detected in line IA11 if the cursor positioned node is
;;; deleted and then it calls the `InsertBefore' operation in line IA13. If
;;; the update using CAS in line IA7 succeeds, the cursor position is set to
;;; the new node in line IA15 and the prev pointer of the previous cursor
;;; positioned node is updated by calling the `HelpInsert' function in line
;;; IA16. The linearizability point of the InsertAfter operation is the
;;; successful CAS operation in line IA7, or equal to the linearizability
;;; point of the InsertAfter operation if that operation was called in line
;;; IA1 or IA13.

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-*-insert-after ((function-name structure cursor
				    structure-tail
				    previous-element
				    next-element
				    read-deleted-node copy-node
				    release-node help-insert)
				   create-action
				   insert-before-action)
  `(progn
     (when (eq ,cursor (,structure-tail ,structure))
       (return-from ,function-name ,insert-before-action))		  ; IA1
     (let ((node ,create-action)					  ; IA2
	   (next nil)
	   (backoff-limit backoff-min-delay))
       (loop doing							  ; IA3
	 (setq next (,read-deleted-node (,next-element ,cursor)))	  ; IA4
	 (setf (,previous-element node)
	       (make-atomic-reference ,cursor nil))			  ; IA5
	 (setf (,next-element node)
	       (make-atomic-reference next nil))			  ; IA6
	 (when (compare-and-swap (,next-element ,cursor)
				 (make-atomic-reference next nil)
				 (make-atomic-reference node nil))	  ; IA7
	   (,copy-node node)						  ; IA8
	   (loop-finish))						  ; IA9
	 (,release-node next)						  ; IA10
	 (when (atomic-reference-mark (,next-element ,cursor))		  ; IA11
	   (,release-node node)						  ; IA12
	   (return-from ,function-name ,insert-before-action))		  ; IA13
	 (back-off))							  ; IA14
       (,copy-node cursor) ; old: node					  ; IA15
       (setq node (,help-insert node next))				  ; IA16
       (,release-node node)						  ; IA17
       (,release-node next)						  ; IA18
       node)))


#+Lockfree-Deque
(defun-simple constant-queue-insert-after (constant-queue cursor thing)
  (generate-*-insert-after (constant-queue-insert-after constant-queue cursor
			    constant-queue-tail
			    queue-previous-element
			    queue-next-element
			    read-deleted-queue-node
			    copy-queue-node
			    release-queue-node
			    help-insert-queue-node)
    (create-queue-element thing)
    (constant-queue-insert-before constant-queue cursor thing)))

#-Lockfree-Deque
(defmacro constant-queue-insert-after (constant-queue cursor thing)
  (let* ((queue-var (if (symbolp constant-queue)
                        constant-queue
                        (gensym)))
	 (tail (gensym))
         (new-element (gensym)))
    `(let* (,@(if (neq queue-var constant-queue)
                  `((,queue-var ,constant-queue))))
       (if (eq ,cursor ,queue-var)
	   (constant-queue-filo-enqueue ,queue-var ,thing)
	 (let* ((,tail (queue-next-element ,cursor))
		(,new-element (make-queue-element-macro ,tail ,cursor ,thing)))
	   (setf (queue-next-element ,cursor) ,new-element)
	   (if (eq ,tail ,queue-var) ; cursor is tail
	       (setf (constant-queue-tail ,queue-var) ,new-element)
	     (setf (queue-previous-element ,tail) ,new-element))
	   ,new-element)))))

;;; The substitution macro `requeue-queue-element' takes a constant-queue and a
;;; queue-element.  The queue-element is removed from its current constant-queue
;;; and enqueued onto the end of the given constant-queue.  Note that the given
;;; constant-queue can either be the current queue for this queue-element, or it
;;; can be an entirely different constant queue.

#-Lockfree-Deque
(def-substitution-macro requeue-queue-element (constant-queue queue-element)
  (let ((old-next-element (queue-next-element queue-element))
        (old-previous-element (queue-previous-element queue-element)))
    (setf (queue-previous-element old-next-element) old-previous-element)
    (setf (queue-next-element old-previous-element) old-next-element))
  (let ((old-tail (constant-queue-tail constant-queue)))
    (setf (queue-next-element queue-element) constant-queue)
    (setf (queue-previous-element queue-element) old-tail)
    (setf (queue-next-element old-tail) queue-element)
    (setf (constant-queue-tail constant-queue) queue-element))
  nil)

;;; The substitution macro `merge-constant-queues' takes two constants queues,
;;; and appends the tasks from the second constant queue onto the end of the
;;; queue of tasks stored in the first constant queue.  After this macro, the
;;; second constant queue will always be empty.

#-Lockfree-Deque
(def-substitution-macro merge-constant-queues (queue-to-fill queue-to-empty)
  (unless (constant-queue-empty-p queue-to-empty)
    (let ((head (constant-queue-head queue-to-empty))
          (tail (constant-queue-tail queue-to-empty)))
      (setf (constant-queue-head queue-to-empty) queue-to-empty)
      (setf (constant-queue-tail queue-to-empty) queue-to-empty)
      (cond ((constant-queue-empty-p queue-to-fill)
             (setf (constant-queue-head queue-to-fill) head)
             (setf (constant-queue-tail queue-to-fill) tail)
             (setf (queue-previous-element head) queue-to-fill)
             (setf (queue-next-element tail) queue-to-fill))
            (t
             (let ((old-tail (constant-queue-tail queue-to-fill)))
               (setf (queue-next-element old-tail) head)
               (setf (queue-previous-element head) old-tail)
               (setf (constant-queue-tail queue-to-fill) tail)
               (setf (queue-next-element tail) queue-to-fill))))))
  #+development
  (unless (constant-queue-empty-p queue-to-empty)
    (error "constant queue not empty?!"))
  nil)

;;; The macro `delete-queue-element' takes a constant queue element and deletes
;;; it from its constant queue.  It also reclaims the given element.

#-Lockfree-Deque
(defmacro delete-queue-element (constant-queue-element)
  (let* ((element-var (if (symbolp constant-queue-element)
                          constant-queue-element
                          (gensym)))
         (next (gensym))
         (previous (gensym)))
    `(let* (,@(if (neq element-var constant-queue-element)
                  `((,element-var ,constant-queue-element)))
            (,next (queue-next-element ,element-var))
            (,previous (queue-previous-element ,element-var)))
       (setf (queue-next-element ,previous) ,next)
       (setf (queue-previous-element ,next) ,previous)
       (prog1 (queue-datum ,element-var)
	 (reclaim-queue-element-macro ,element-var)))))

#-Lockfree-Deque
(defmacro constant-queue-delete (queue-element constant-queue)
  (declare (ignore constant-queue))
  `(delete-queue-element ,queue-element))

;;; The `Delete' operation tries to delete the non-dummy node referenced by
;;; the given cursor and returns the value if successful, otherwise a non-
;;; value is returned. If the cursor positioned node is equal to any of the
;;; dummy nodes this is detected in line D1 and a non-value is returned. The
;;; algorithm repeatedly tries in line D3-D5 to set the deletion mark of the
;;; next pointer of the cursor positioned node. If the deletion mark is
;;; already set, this is detected in line D4 and a non-value is returned. If
;;; the CAS operation in line D5 succeeds, the deletion process is completed
;;; by calling the HelpDelete procedure in line D6 and the HelpInsert function
;;; in line D8. In order to avoid possible problems with cyclic garbage the
;;; RemoveCrossReference procedure in called in line D11. The value of the
;;; deleted node is read in line D10 and the value returned in line D12. The
;;; linearizability point of a Delete function that returns a value is the
;;; successful CAS operation in line D5. The linearizability point of a Delete
;;; function that returns a non-value is the read sub-operation of the next
;;; pointer in line D3, unless the node positioned by the cursor was the head
;;; or tail dummy node when the linearizability point instead is line D1.

#+(or Lockfree-Deque Lockfree-List)
(defmacro generate-*-delete ((cursor structure)
			     head-element
			     tail-element
			     next-element
			     previous-element
			     copy-node
			     release-node
			     help-delete
			     help-insert
			     structure-datum
			     remove-cross-reference
			     structure-delete)
  `(progn
     (when (and ,structure
		(or (eq ,cursor (,head-element ,structure))
		    (eq ,cursor (,tail-element ,structure))))
       (return-from ,structure-delete (values nil nil)))		  ; D1
     (loop as link1 = (,next-element ,cursor)				  ; D3
	   do
       (when (atomic-reference-mark link1)				  ; D4
	 (return (values nil nil)))
       (when (compare-and-swap (,next-element ,cursor)
			       link1
			       (make-atomic-reference
				 (atomic-reference-object link1) t))	  ; D5
	 (,help-delete ,cursor)						  ; D6
	 (let ((prev
		(,copy-node (atomic-reference-object
			      (,previous-element ,cursor)))))		  ; D7
	   (setq prev
		 (,help-insert prev
			       (atomic-reference-object link1)))	  ; D8
	   (,release-node prev)						  ; D9
	   (let ((value (,structure-datum ,cursor)))			  ; D10
	     (,remove-cross-reference ,cursor)				  ; D11
	     (return (values value t))))))))				  ; D12

#+Lockfree-Deque
(defun constant-queue-delete (cursor &optional constant-queue)
  (generate-*-delete (cursor constant-queue)
		     constant-queue-head
		     constant-queue-tail
		     queue-next-element
		     queue-previous-element
		     copy-queue-node
		     release-queue-node
		     help-delete-queue-node
		     help-insert-queue-node
		     queue-datum
		     remove-queue-cross-reference
		     constant-queue-delete))

#+Lockfree-Deque
(defmacro delete-queue-element (constant-queue-element)
  `(constant-queue-delete ,constant-queue-element))

;; find the first matched datum and delete it from constant-queue
(defun-void constant-queue-search-and-delete (constant-queue datum)
  (loop with head = (constant-queue-head constant-queue)
	for queue-element = #-Lockfree-Deque head
			    #+Lockfree-Deque (constant-queue-next head constant-queue)
		       then (constant-queue-next queue-element constant-queue)
	until #-Lockfree-Deque (eq queue-element constant-queue)
	      #+Lockfree-Deque (null queue-element)
	when (eq datum (queue-datum queue-element))
	  do (constant-queue-delete queue-element constant-queue)
	     (loop-finish)))

;; find all matched data and delete them from constant queue
(defun-void constant-queue-search-and-delete-all (constant-queue datum)
  (loop with head = (constant-queue-head constant-queue)
	for queue-element = #-Lockfree-Deque head
			    #+Lockfree-Deque (constant-queue-next head constant-queue)
		       then next-queue-element
	until #-Lockfree-Deque (eq queue-element constant-queue)
	      #+Lockfree-Deque (null queue-element)
	for next-queue-element = (constant-queue-next queue-element constant-queue)
	when (eq datum (queue-datum queue-element))
	  do (constant-queue-delete queue-element constant-queue)))

#+Lockfree-Deque
(defun requeue-queue-element (constant-queue queue-element element-queue)
  (let ((value (queue-datum queue-element)))
    (constant-queue-delete queue-element element-queue)
    (constant-queue-enqueue constant-queue value))
  nil)

;;; The development function `check-constant-queue-ok' takes a constant queue
;;; and checks that it's elements are in a circular list and that they become
;;; circular within fewer than `constant-queue-check-limit' elements.

#+development
(defconstant constant-queue-check-limit 131072) ; increased for HTWOS

;;; The loop path `constant-queue-element' is used to iterate over all
;;; constant-queue-elements within a constant queue.  During this iteration it
;;; is OK to call delete-queue-element on the current queue element given by the
;;; iteration, but any other modifications to the constant-queue being iterated
;;; have undefined effect.

(define-loop-path (constant-queue-element) constant-queue-elements-of (of))

(defun-for-macro constant-queue-elements-of
    (path-name variable data-type prep-phrases inclusive?
               allowed-preposistions data)
  (declare (ignore data-type data allowed-preposistions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S."
           path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~s path of ~s ~
            (prep-phrase = ~s)"
           path-name variable prep-phrases))
  (let* ((queue (make-symbol "QUEUE"))
         (next-queue-element (make-symbol "NEXT-QUEUE-ELEMENT"))
         (init-bindings
           `((,queue ,(second (car prep-phrases)))
             (,next-queue-element nil)
             (,variable nil)))
         (prologue-forms
           `((setq ,next-queue-element
                   #-Lockfree-Deque (constant-queue-head ,queue)
                   #+Lockfree-Deque (constant-queue-next
                                      (constant-queue-head ,queue) ,queue))))
         (pre-step-tests
	   #-Lockfree-Deque
	   `(eq ,next-queue-element ,queue)
	   #+Lockfree-Deque
           `(null ,next-queue-element))
         (steppings nil)
         (post-step-tests nil)
         (post-step-settings
           `(,variable (queue-datum ,next-queue-element)
             ,next-queue-element
             (constant-queue-next ,next-queue-element ,queue))))
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))


;;; The development function `constant-queue-elements' returns a list of
;;; the values queued in the given constant queue.

#+development
(defun constant-queue-elements (constant-queue)
  (loop for element being each constant-queue-element of constant-queue
        collect element))

(defun constant-queue-length (constant-queue)
  (if (null constant-queue)
      0
    (loop for element being each constant-queue-element of constant-queue
	  count element)))

#+development
(defun describe-constant-queue (constant-queue)
  "Display all queue elements in a constant queue (with head and tail), then ~
return the number of elements (not include head and tail)."
  (flet ((print-one (element)
	   #-Lockfree-Deque
	   (format t "~A: next: ~A, prev: ~A, data: ~A~%"
		   (%pointer element)
		   (queue-next-element element)
		   (queue-previous-element element)
		   (queue-datum element))
	   #+Lockfree-Deque
	   (format t "~A: next: ~A, prev: ~A, data: ~A, ref-count: ~D (claim-bit: ~D)~%"
		   (%pointer element)
		   (queue-next-element element)
		   (queue-previous-element element)
		   (queue-datum element)
		   (reference-count element)
		   (claim-bit element))))
    (let ((element-list nil)
	  (head (constant-queue-head constant-queue))
	  #+Lockfree-Deque
	  (tail (constant-queue-tail constant-queue)))
      (loop for element = #-Lockfree-Deque head
			  #+Lockfree-Deque (queue-next-element-real head)
			then (queue-next-element-real element)
			until #-Lockfree-Deque (eq element constant-queue)
			      #+Lockfree-Deque (eq element tail)
	    initially
	      #-Lockfree-Deque ()
	      #+Lockfree-Deque (print-one head)
	    do
	(print-one element)
	(push element element-list)
	    finally
	      #+Lockfree-Deque (print-one tail)
	      (return (nreverse element-list))))))

;; reverse the elements and reclaim the argument
(defun-simple constant-queue-nreverse (constant-queue)
  (let ((new-constant-queue
	 (make-empty-constant-queue)))
    (loop for block being each constant-queue-element of constant-queue
	  do
      (constant-queue-filo-enqueue new-constant-queue block) ; push-left
          finally
	    (reclaim-constant-queue constant-queue)
	    (return new-constant-queue))))

(defun-simple constant-queue-nth (n constant-queue)
  (loop for count fixnum = 0 then (+f count 1)
	for block being each constant-queue-element of constant-queue
	when (=f count n)
	do (return block)))

;;;; Least Recently Used Management Facilities




;;; Within several facilities in G2 there is a need for management of resources
;;; using a "least recently used" reclamation heuristic.  To support management
;;; of objects in this style, an inclusion def-structure and a set of functions
;;; have been written which implement efficient least recently used object
;;; tracking for structures.

;;; You can use this facility by including the structure `lru-element' into a
;;; structure, defining a variable which holds an `lru-queue', calling the macro
;;; `install-lru-element-in-queue' with the new structure and the LRU queue as
;;; arguments within an allocator function for the structure, and calling
;;; `record-lru-element-usage' on the structure and queue whenever the structure
;;; is used.  The function `least-recently-used-lru-element' then can be called
;;; on the LRU queue to return the structure of this type which has not been
;;; used for the longest time.  If there are no elements in the given queue, it
;;; will return NIL.

;;; The structure `lru-element' defines the slots needed for LRU management.
;;; Direct instances of this structure are used as LRU queue heads.

(def-structure (lru-element (:eliminate-for-products gsi))
  (lru-element-next-element nil :reclaimer remove-lru-element
                            :initialize-on-recycle nil)
  lru-element-previous-element)




;;; The macro `splice-out-lru-element' is called on an lru element to remove it
;;; from the LRU queue in which it is located.  Note that corruption will ensue
;;; if this element is not currently within a LRU queue.

(def-substitution-macro splice-out-lru-element (element)
  (let ((next-element (lru-element-next-element element))
        (previous-element (lru-element-previous-element element)))
    (setf (lru-element-next-element previous-element) next-element)
    (setf (lru-element-previous-element next-element) previous-element)
    nil))




;;; The function `remove-lru-element' is the reclaimer for the
;;; lru-element-next-element slot of lru-element structures.  If the structure
;;; being reclaimed is not an lru-element (i.e., it is something that
;;; lru-element has been included within, then remove this element from its
;;; queue.

(defun remove-lru-element (next-element)
  (declare (ignore next-element) (eliminate-for-gsi))
  (when (not (lru-element-p structure-being-reclaimed))
    (splice-out-lru-element structure-being-reclaimed))
  nil)




;;; The function `make-lru-queue' takes no arguments and returns a new, empty
;;; LRU queue.

(defun make-lru-queue ()
  (declare (eliminate-for-gsi))
  (let ((new-queue (make-lru-element)))
    (setf (lru-element-next-element new-queue) new-queue)
    (setf (lru-element-previous-element new-queue) new-queue)
    new-queue))




;;; The macro `lru-queue-p' returns whether or not the passed thing is an LRU
;;; queue.

(defmacro lru-queue-p (thing)
  `(lru-element-p ,thing))




;;; The function `install-lru-element-in-queue' is called with a structure into
;;; which the LRU-element structure has been included, and with an LRU-queue.
;;; It installs the structure into the most recently used position of the queue.
;;; It returns the LRU-element which has just been installed.

(defun install-lru-element-in-queue (lru-element lru-queue)
  (declare (eliminate-for-gsi))
  (let ((previous-tail (lru-element-previous-element lru-queue)))
    (setf (lru-element-next-element previous-tail) lru-element)
    (setf (lru-element-previous-element lru-queue) lru-element)
    (setf (lru-element-next-element lru-element) lru-queue)
    (setf (lru-element-previous-element lru-element) previous-tail)
    lru-element))




;;; The macro `record-lru-element-usage' takes an lru-element structure
;;; and an LRU-queue, and makes the element the most recently used element of
;;; the queue.  It returns the lru-element.

(def-substitution-macro record-lru-element-usage (lru-element lru-queue)
  (let ((previous-tail (lru-element-previous-element lru-queue)))
    (when (not (eq lru-element previous-tail))
      (splice-out-lru-element lru-element)
      (setf (lru-element-next-element previous-tail) lru-element)
      (setf (lru-element-previous-element lru-element) previous-tail)
      (setf (lru-element-next-element lru-element) lru-queue)
      (setf (lru-element-previous-element lru-queue) lru-element))
    lru-element))




;;; The macro `least-recently-used-lru-element' takes an lru-queue, and returns
;;; the least recently used element of the queue, or nil if the queue is empty.
;;; Note that this macro does not modify the queue, it only returns the element.

(def-substitution-macro least-recently-used-lru-element (lru-queue)
  (let ((queue-head (lru-element-next-element lru-queue)))
    (if (neq queue-head lru-queue)
        queue-head
        nil)))


;;; The macro `do-lru-queue' iterates over the elements of the given lru-element,
;;; in order from least-recently-used to most.

(defmacro do-lru-queue ((element lru-queue) &body body)
  (avoiding-variable-capture (lru-queue &aux next)
    `(loop for ,element = (or (least-recently-used-lru-element ,lru-queue)
                              ,lru-queue)
                        then ,next
           as ,next = (lru-element-next-element ,element)
           until (eq ,element ,lru-queue)
           doing
       (progn ,@body))))






;;;; Structure Decaching



;;; In G2, it is necessary to limit the total amount of memory allocated so that
;;; the system will not crash.  This is especially important for structures like
;;; icon and graph renderings which can consume a lot of memory (due to the
;;; rasters which these structures contain).  Enforcing limits on numbers of
;;; structures allocated means that it will, at times, be necessary to
;;; de-allocate such structures.  This imposes a speed penalty since the
;;; de-allocation results in a decaching of information that typically has to be
;;; recached at some point in the future.  Thus, it is important to choose the
;;; limits for each type of structure carefully.

;;; Since the optimal settings for the limits can vary with the platform, the
;;; knowlege base, and even with time for a particular knowledge base, it is
;;; best for the system to tune these settings automatically.  This is
;;; accomplished by the following decaching algorithm.

;;; 1.  Memory limit check when allocating -
;;; Whenever a structure of a certain type is allocated, check whether the limit
;;; for that type has been exceeded.  If so, rather than allocating a new one,
;;; decache an existing one.

;;; 2.  Decaching -
;;; The least recently used (LRU) structure of the required type is chosen for
;;; decaching.  Any corresponding ICP objects must also be decached.

;;; 3.  Recaching cost calculation -
;;; The cost of recaching the decached structure is computed by the following
;;; formula:
;;;      cost = f(complexity of structure, empirical constant)

;;; 4.  Thrashing percentage calculation -
;;; Thrashing percentage is calculated at certain, not necessarily regular
;;; intervals according to the following formula:
;;;      thrashing percentage = total decaching cost for interval / interval.

;;; 5.  Adjustment of limit -
;;; After the thrashing percentage is calculated, it is compared with the
;;; global, user specified, thrashing percentage setpoint.  If the
;;; thrashing percentage is too high, the limit is expanded, provided that
;;; this doesn't violate the global memory limit.  If the thrashing
;;; percentage is too low, the memory limit is decreased.




;;; Define-decacheable-structure is used to set up a decaching mechanism for a
;;; type of structure.  It is assumed that the structure type given by
;;; structure-name has lru-element included in the def-structure (see above
;;; documentation on LRU).

;;; Define-decacheable-structure defines the following:
;;; 1.  a decache function,
;;; 2.  a make-decacheable function,
;;; 3.  an lru-queue,
;;; 4.  a memory-limit-info variable,
;;; 5.  a record-usage function,
;;; 6.  a note-increase-in-size function.
;;; The make-decacheable function should be used whenever creating an instance
;;; that may be decached.  The decache function may be called automatically by the
;;; make-decacheable function in order to decache before allocating a new
;;; structure.  It should also be used when explicitly deleting the structure.
;;; The record-usage function should be called whenever the structure is used for
;;; some purpose (such as drawing for example).  Use of the note-increase-in-size
;;; function is explained below.

;;; Meters are set up automatically if G2-METERS is loaded (see
;;; define-g2-meters-for-decacheable-structures).

;;; Along with the define-decacheable-structure form, it is necessary to define a
;;; cost-function, which computes cost of decaching.  This function takes an
;;; instance of the structure type as its argument and must return an integer.  If
;;; the cache is obsolete, the cost should be 0.  An example of this is when the
;;; graph corresponding to a graph-rendering being decached has already been
;;; deleted (see compute-cost-of-decaching-graph-rendering, cleanup method for
;;; graph-grid).

;;; The decaching-body argument must contain a call to the reclaim function for
;;; the structure, which in turn calls remove-lru-element so that the structure
;;; is removed from the LRU queue.  Decaching typically requires removal of the
;;; structure from some list or parent frame or structure.  Thus, a backpointer
;;; slot is necessary in the structure which must be set when the structure is
;;; cached, and which is used by the decaching-body to decache.

;;; Size-computation-function-name must be the name of a function which takes an
;;; instance of the structure type as its argument and computes the size of the
;;; structure.  The size argument passed to the make-decacheable function should
;;; be the same as the size that would be computed using the size computation
;;; function after the structure is allocated.

;;; Two types of behavior are possible regarding sizes.  If the sizes?  argument
;;; to define-decacheable-structure is nil, the decaching mechanism will, when the
;;; make-decacheable function is called, decache structures until the accumulated
;;; sizes of the decached structures is greater than or equal to the size
;;; specified by the size argument to the make-decacheable function, or until
;;; there is nothing left to decache.

;;; If the sizes?  argument to define-decacheable-structure is non-nil, the
;;; caching pools for that type of structure are subdivided by size according to
;;; the sizes?  argument.  In this case, sizes?  must be a short list (10 elements
;;; or less) of monotonically increasing integers.  When the make-decacheable
;;; function is called to make a structure of a certain size, the decaching
;;; mechanism will decache only from the pool corresponding to that size.

;;; The note-increase-in-size function is provided to allow for structures to
;;; change (usually increase) size after they are cached.  This function is only
;;; defined if the sizes?  argument is nil.  This function simply takes a
;;; delta-size argument and uses it to adjust the
;;; decacheable-structures-allocated-memory slot of the memory-limit-info
;;; structure for a particular type of decacheable structure.  This function is
;;; used, for example, for scaled fonts to allow for adding character images as
;;; needed rather than allocating all character images for the scaled font when
;;; the scaled font is cached.  Note that the method used to compute the
;;; delta-size argument must be consistent with the method used in the size
;;; computation function so that the size computed using the size computation
;;; function before the size change + delta size = the size that would be computed
;;; after the size change using the size computation function.

;;; In some cases, (icon-renderings, graph-renderings, and other graphic
;;; structures), the structure is window specific and should only be decached if
;;; it corresponds to the current window.  For this reason, the
;;; corresponding-window-slot-name? arg is provided in
;;; define-decacheable-structure.  If non-nil, this must be the name of the slot
;;; in the structure which contains the window associated with the structure.
;;; This slot will then be checked to make sure that it contains the current
;;; window before the structure is decached.

;;; In certain cases, the structure may be cached in two places and may exist
;;; multiple times in one of the caches.  It may be too computationally
;;; expensive to decache it explicitly from such a cache.  In such cases, it is
;;; better to wait for the structure to be decached from the large cache as part
;;; of normal operation, before decaching it explicitly.  An example of this is
;;; icon-renderings which are cached in the icon-description for an entity and
;;; also, possibly multiple times, in graphic-element-memory.  Since decaching
;;; icon-renderings explicitly from graphic-element-memory is very
;;; computationally expensive, it is better to wait for the icon-rendering to be
;;; decached from graphic element memory due to erasing, before decaching it
;;; from the icon-description.  In other words, an icon rendering should not
;;; be decached if it is currently showing on some workspace.

;;; For such cases, the track-number-of-times-used-in-cache? argument to
;;; define-decacheable-structure should be t.  A number-of-times-used-in-cache?
;;; slot must exist in the structure.  Finally, the record-usage function
;;; must be passed an additional argument indicating whether to increment or
;;; decrement the number-of-times-used-in-cache slot.  When this is done,
;;; the structure will not be decached unless the value of the
;;; number-of-times-used-in-cache slot is 0.



;;; Update-memory-limits computes thrashing percentage from the accumulated
;;; decaching costs.  The thrashing percentage is then used to modify the memory
;;; limit.  The thrashing percentage is actually filtered by a ring buffer which
;;; keeps the last 10 values and weights them exponentially (see
;;; compute-newest-thrashing-ratio).  This introduces a first order lag and is
;;; thus a low pass filter for the memory limit computation control system.
;;; Update-memory-limits (or its macro alternative,
;;; update-memory-limits-if-time-to-check) can be called at regular intervals,
;;; or simply along with the record-usage function when the structure is used
;;; (it is typically difficult to schedule regular intervals since currently,
;;; the G2 scheduler only works when the system is running).




;;; Memory-limit-variable-names-for-decacheable-structures is a list of names
;;; for variables which hold the memory limit information.  This list is not
;;; process specific (since it is set at compile time) so defvar, rather than
;;; def-system-variable, is used.  However, the values for the variables
;;; contained in this list are process specific.  Thus, update-memory-limits
;;; (see below) loops through the variable names on the list, and then accesses
;;; the values using symbol-value.

(defvar memory-limit-variable-names-for-decacheable-structures nil)

;; An alternative to the above approach would be to make
;; memory-limit-variable-names-for-decacheable-structures process specific.
;; This is unattractive however in that it would make it impossible to set this
;; variable at compile time and would thus require calling some sort of
;; initialization function to set the value.



;;; Names-and-sizes-for-decacheable-structures is a global list for
;;; decacheable structures.  Each element is of the form
;;; (structure-type memory-limit-variable-name corresponding-window-slot-name?
;;;  lru-queue-name decaching-function-name
;;;  . (sizes?))
;;; It is used by define-g2-meters-for-decacheable-structures (for development
;;; case only, and by reclaim-cached-structures-for-window.

(defvar names-and-sizes-for-decacheable-structures nil)

;; Consider combining with
;; memory-limit-variable-names-for-decacheable-structures.



(defparameter default-decacheable-structure-allocation-limit 5)        ; was 1 before today (MHD/agh 2/7/91)

(defparameter minimum-decacheable-structure-allocation-limit 1)


;;; A memory-limit-info structure contains the following information for
;;; a decacheable structure pool:
;;; - number of structures allocated
;;; - memory limit
;;; - accumulated thrashing cost for time interval
;;; - newest thrashing ratio
;;; - filtered thrashing ratio
;;; - thrashing ratio ring buffer.
;;; A size slot is also included for size-specific pools.

(def-structure (memory-limit-info (:eliminate-for-products gsi))
  (decacheable-structures-allocated-memory 0)
  (allocation-limit default-decacheable-structure-allocation-limit)
  (accumulated-thrashing-cost 0)
  (newest-thrashing-ratio 0)
  (filtered-thrashing-ratio 0)
  (thrashing-ratio-ring-buffer nil)
  (decacheable-structure-size nil)
  (name-of-memory-limited-structure nil) ;jh, 4/14/93.
  )




;;; If sizes?  is non-nil initial-memory-limit-info returns a list of
;;; memory-limit-info structures (one for each size), otherwise, it returns a
;;; single memory-limit-info structure.  It is assumed that if sizes?  is
;;; non-nil, it is a short list (10 elements or less) of monotonically
;;; increasing integers.

(defun initialize-memory-limit-info (sizes? name)
  (declare (eliminate-for-gsi))
  (if sizes?
      (loop for size in sizes?
            as memory-limit-info = (make-memory-limit-info)
            do (setf (decacheable-structure-size memory-limit-info) size)
               (setf (name-of-memory-limited-structure memory-limit-info)
                     name) ;jh, 4/14/93.
            collect memory-limit-info)
      (make-memory-limit-info)))



(defun get-memory-limit-info-given-size (memory-limit-variable size)
  (declare (eliminate-for-gsi))
  (loop        for limit-info in memory-limit-variable
        as decacheable-structure-size
           = (decacheable-structure-size limit-info)
        do (when (<=f size decacheable-structure-size)
             (return limit-info))))


(defun get-bracketing-sizes (size sizes)
  (declare (eliminate-for-gsi))
  (loop as min-size = 0 then max-size
        for max-size in sizes
        do (if (and (>f size min-size)
                    (<=f size max-size))
               (return (values min-size max-size)))))

;; Get-bracketing-sizes returns nil if size can not be bracketed
;; by sizes.





(defmacro allocate-decacheable-structure
          (limit-info allocation-form size-computation-function-name)
  (let ((value-of-limit-info (gensym)))
    `(let* ((,value-of-limit-info ,limit-info)
            (new-structure ,allocation-form)
            (size-of-new-structure
              (,size-computation-function-name new-structure)))
       (when ,value-of-limit-info
         (setf (decacheable-structures-allocated-memory ,value-of-limit-info)
               (+f (decacheable-structures-allocated-memory ,value-of-limit-info)
                   size-of-new-structure)))
       new-structure)))





(defmacro get-structure-of-correct-size-to-decache
          (minimum-size maximum-size
           lru-queue-name size-computation-function
           track-number-of-times-used-in-cache? corresponding-window-slot-name?)
  #+development
  (when (or (not (or (symbolp minimum-size) (constantp minimum-size)))
            (not (or (symbolp maximum-size) (constantp maximum-size)))
            (not (symbolp lru-queue-name))
            (not (symbolp size-computation-function)))
    (error "Incorrect arg types for get-structure-of-correct-size-to-decache"))

;  `(when (not (eq ,lru-queue-name icon-rendering-lru-queue))
  ;; To disable decaching of icon renderings.

  `(loop as lru-element?
            = (least-recently-used-lru-element ,lru-queue-name)
            then (lru-element-next-element lru-element?)
         while lru-element?
         as count = 0 then (+f count 1)
         until (eq lru-element? ,lru-queue-name)
         as size = (,size-computation-function lru-element?)
         do (when (and (>f size ,minimum-size)
                       (<=f size ,maximum-size)
                       ,@(if track-number-of-times-used-in-cache?
                             `((=f (number-of-times-used-in-cache? lru-element?) 0)))
                       ,@(if corresponding-window-slot-name?
                             `((let ((window-for-structure
                                      (,corresponding-window-slot-name? lru-element?)))
                                 (and (not (printing-window-p window-for-structure))
                                      (eq window-for-structure current-window))))))
              (return lru-element?))))

;; A note on LRU queues -
;; The LRU queue name points to the head lru-element.  This lru-element actually
;; indicates the "dateline" of the queue rather than the head since the
;; queue is a ring.  The lru-element-next-element slot of the head lru-element
;; points to the least recently used lru element and the
;; lru-element-previous-element slot points to the most recently used element.
;; Note that only the head element is actually an lru-element;  all the
;; other elements are structures which include lru-element.


(defmacro get-structure-to-decache
          (lru-queue-name track-number-of-times-used-in-cache?
           corresponding-window-slot-name?)
  (if (or track-number-of-times-used-in-cache?
          corresponding-window-slot-name?)
      `(loop as lru-element?
                = (least-recently-used-lru-element ,lru-queue-name)
                then (lru-element-next-element lru-element?)
             while lru-element?
             until (eq lru-element? ,lru-queue-name)
             do (when
                  ,(cond
                     ((and track-number-of-times-used-in-cache?
                           corresponding-window-slot-name?)
                      `(and (=f (number-of-times-used-in-cache? lru-element?) 0)
                            (eq (,corresponding-window-slot-name? lru-element?)
                                current-window)))
                     (track-number-of-times-used-in-cache?
                      `(=f (number-of-times-used-in-cache? lru-element?) 0))
                     (t  ; if corresponding-window-slot-name?
                      `(eq (,corresponding-window-slot-name? lru-element?)
                           current-window)))
                  (return lru-element?)))
      `(least-recently-used-lru-element ,lru-queue-name)))



;;; Decache-occurred-since-last-update? is always set when decaching a structure.
;;; It is always reset by update-memory-limits.  It is used to adjust the
;;; frequency with which update-memory-limits is called (it does not have to
;;; be called so often if no decaching has occurred).

(def-system-variable decache-occurred-since-last-update? UTILITIES2 nil)



(defmacro define-decacheable-structure
          (structure-name allocation-form cost-function-name
           sizes? size-computation-function-name
           track-number-of-times-used-in-cache?
           corresponding-window-slot-name? &body decaching-body)
  (let* ((decacheable-allocation-function-name
           (intern (format nil "MAKE-DECACHEABLE-~a" structure-name)))
         (decaching-function-name
           (intern (format nil "DECACHE-~a" structure-name)))
         (allocation-primitive
           (intern (format nil "MAKE-~a" structure-name)))
         (record-usage-function-name
           (intern (format nil "RECORD-USAGE-OF-~a" structure-name)))
         (note-increase-in-size-function-name
           (intern (format nil "NOTE-INCREASE-IN-SIZE-OF-~a" structure-name)))
         (memory-limit-variable-name
           (intern (format nil "~a-MEMORY-LIMIT-INFO" structure-name)))
         (lru-queue-name
           (intern (format nil "~a-LRU-QUEUE" structure-name)))
         (allocation-form-using-primitive
           (cons allocation-primitive
                 (cdr allocation-form))))

    `(progn
       (declare-special-global ,memory-limit-variable-name)
       (def-system-variable ,memory-limit-variable-name UTILITIES2
         (:funcall initialize-memory-limit-info
                   ,sizes?
                   ,structure-name)) ;jh, 4/14/93.  Added structure-name.

       (when (not (memq ',memory-limit-variable-name
                        memory-limit-variable-names-for-decacheable-structures))
         (setq memory-limit-variable-names-for-decacheable-structures
               (nconc memory-limit-variable-names-for-decacheable-structures
                      ',(list memory-limit-variable-name))))

       (loop with new-entry
               = ,(if sizes?
                      `(nconc (list ',structure-name
                                    ',memory-limit-variable-name
                                    ',corresponding-window-slot-name?
                                    ',lru-queue-name
                                    ',decaching-function-name)
                              (copy-list ',sizes?))
                      `(list ',structure-name
                             ',memory-limit-variable-name
                             ',corresponding-window-slot-name?
                             ',lru-queue-name
                             ',decaching-function-name))
             for entry-cons on names-and-sizes-for-decacheable-structures
             do
         (cond ((eq (caar entry-cons) (car new-entry))
                (if (not (equal (car entry-cons) new-entry))
                    (setf (car entry-cons) new-entry))
                (return (values))))
             finally                                ; no entry yet
               (setq names-and-sizes-for-decacheable-structures
                     (nconc names-and-sizes-for-decacheable-structures
                            (list new-entry))))

       (declare-special-global ,lru-queue-name)
       (def-system-variable ,lru-queue-name UTILITIES2
         (:funcall make-lru-queue))

       (defun ,decaching-function-name (,structure-name)
         (let* ((size-of-structure
                  (,size-computation-function-name ,structure-name))
                (limit-info
                  ,(if sizes?
                       `(get-memory-limit-info-given-size
                          ,memory-limit-variable-name size-of-structure)
                       memory-limit-variable-name)))
           (when limit-info
             (setf (decacheable-structures-allocated-memory limit-info)
                   (-f (decacheable-structures-allocated-memory limit-info)
                       size-of-structure))))
         (setq decache-occurred-since-last-update? t)
         ,@decaching-body)
       ;; Note that the decaching-body must contain a call to
       ;; the reclaim function for the structure, which in turn
       ;; calls remove-lru-element so that the structure is
       ;; removed from the LRU queue.

       (defun ,allocation-primitive
              ,(cdr allocation-form)
         (install-lru-element-in-queue
           ,allocation-form
           ,lru-queue-name))

       (defun ,decacheable-allocation-function-name
              ,(nconc (copy-tree (cdr allocation-form))
                      `(size &optional dont-decache?))
         (let ((limit-info
                 ,(if sizes?
                      `(get-memory-limit-info-given-size
                         ,memory-limit-variable-name size)
                      memory-limit-variable-name)))
           (cond
             ((or dont-decache?
                  (null limit-info)
                  (<f (decacheable-structures-allocated-memory limit-info)
                      (allocation-limit limit-info)))

              ;; If size is greater than any size in sizes?,
              ;; there is no pool for that size and
              ;; get-memory-limit-info-given-size returns nil.
              ;; In this case, a structure is allocated but
              ;; it will not, currently, be reclaimed.

              (allocate-decacheable-structure
                limit-info ,allocation-form-using-primitive
                ,size-computation-function-name))

             (t
              ;; decache

              ,(if sizes?
                   `(let ((structure-to-decache?
                            (multiple-value-bind
                              (minimum-size maximum-size)
                                (get-bracketing-sizes size ',sizes?)
                              (when minimum-size
                                (get-structure-of-correct-size-to-decache
                                  minimum-size maximum-size
                                  ,lru-queue-name ,size-computation-function-name
                                  ,track-number-of-times-used-in-cache?
                                  ,corresponding-window-slot-name?)))))
                      (when structure-to-decache?
                        (accumulate-thrashing-cost-and-decache
                          structure-to-decache? limit-info
                          ',cost-function-name ',decaching-function-name)))
                   `(loop with accumulated-size = 0
                          while (<f accumulated-size size)
                          as structure-to-decache?
                             = (get-structure-to-decache
                                 ,lru-queue-name
                                 ,track-number-of-times-used-in-cache?
                                 ,corresponding-window-slot-name?)
                          while structure-to-decache?
                          do
                      ;; accumulate size
                      (setq accumulated-size
                            (+f accumulated-size
                                (,size-computation-function-name
                                 structure-to-decache?)))
                      (accumulate-thrashing-cost-and-decache
                        structure-to-decache? limit-info
                        ',cost-function-name ',decaching-function-name)))

              ;; allocate
              (allocate-decacheable-structure
                limit-info ,allocation-form-using-primitive
                ,size-computation-function-name)))))

       (def-substitution-macro ,record-usage-function-name
                               ,(if track-number-of-times-used-in-cache?
                                    `(,structure-name decrement-usage-instead?)
                                    `(,structure-name))
         ,@ (when track-number-of-times-used-in-cache?
              `((setf (number-of-times-used-in-cache? ,structure-name)
                      (if decrement-usage-instead?
                          (-f (number-of-times-used-in-cache?
                                ,structure-name) 1)
                          (+f (number-of-times-used-in-cache?
                                ,structure-name) 1)))
                #+development
                (if (<f (number-of-times-used-in-cache? ,structure-name) 0)
                    (error "Number-of-times-used-in-cache? slot of a
~a is less than 0" ,structure-name))))
         ,(if track-number-of-times-used-in-cache?
              `(when (not decrement-usage-instead?)
                 (record-lru-element-usage ,structure-name ,lru-queue-name))
              `(record-lru-element-usage ,structure-name ,lru-queue-name)))

       ,(if (not sizes?)
            `(defun ,note-increase-in-size-function-name (delta-size)
               (let* ((limit-info ,memory-limit-variable-name))
                 (when limit-info
                   (setf (decacheable-structures-allocated-memory limit-info)
                         (+f (decacheable-structures-allocated-memory limit-info)
                             delta-size))))))
       )))

;; May eventually want an optional arg form for deciding the structure to
;; decache.

;; The "make" function for the structure is defined here so that it
;; will always call install-lru-element-in-queue.



(defun accumulate-thrashing-cost-and-decache
       (structure-to-decache? limit-info
        cost-function-name decaching-function-name)
  (declare (eliminate-for-gsi))
  ;; compute cost of decaching
  (setf (accumulated-thrashing-cost limit-info)
        (+f (funcall cost-function-name structure-to-decache?)
            (accumulated-thrashing-cost limit-info)))
  ;; decache
  (funcall decaching-function-name structure-to-decache?))




(def-system-variable global-desired-thrashing-setpoint UTILITIES2 50)

;; Consider making this a user settable parameter.  This should always be
;; some number >> 1 because the thrashing ratios are rounded when kept
;; in the thrashing ratio ring buffer (see compute-newest-thrashing-ratio).
;; In other words, thrashing ratios should always be of a magnitude that
;; rounding them doesn't greatly reduce their accuracy.


(def-system-variable time-of-last-thrashing-cost-update UTILITIES2
  (:funcall get-fixnum-time-function))

;; Consider having some sort of mechanism which resets this if idle for too long
;; (to avoid wrap around problem).  Actually, probably relatively imune to
;; wraparound problem.
;; -- CHANGED: the default value is now initialized to the fixnum time
;; at the start of the process, rather than to nil, thus avoiding the need
;; for the nil check in update-memory-limits.



(def-system-variable thrashing-cost-update-interval UTILITIES2
  (:funcall fixnum-time-interval 1000))

;; Initialized to 1 second.


(def-system-variable long-thrashing-cost-update-interval UTILITIES2
  (:funcall fixnum-time-interval 5000))

;; Initialized to 5 seconds.

;; Changed the above two variables to get initialized by fixnum-time-interval,
;; rather than by the custom initialization function that called
;; fixnum-time-interval, which custom initialization function has been removed.
;; (MHD 7/20/93)




;;; `Update-memory-limits-now' changes the limits based on thrashing.  This must
;;; be called at regular intervals from the system's top level scheduler.
;;; However, it should only be called indirectly by calling
;;; `Update-memory-limits-if-time-to-check', a macro, which does a quick, inline
;;; check to see if it is time to check, and, if so, calls the function
;;; update-memory-limits-now.  `Update-memory-limits' does it all, at the cost
;;; of some extra function calling if done at more frequent intervals than
;;; needed.

(def-substitution-macro update-memory-limits-if-time-to-check (fixnum-time-now)
  (when (>f (fixnum-time-difference
              fixnum-time-now
              time-of-last-thrashing-cost-update)
            (if decache-occurred-since-last-update?
                thrashing-cost-update-interval
                long-thrashing-cost-update-interval))
    (update-memory-limits-now fixnum-time-now)))

(defun-void update-memory-limits-now (fixnum-time-now)
  (declare (eliminate-for-gsi))
  (let* ((time-since-last-update
          (fixnum-time-difference
           fixnum-time-now time-of-last-thrashing-cost-update)))
    ;; Update memory limits for all pools.
    (loop for memory-limit-variable-name
            in memory-limit-variable-names-for-decacheable-structures
          as memory-limit-info
            = (symbol-value memory-limit-variable-name)
          do (if (not (consp memory-limit-info))
                 ;; if pool is not subdivided based on size
                 (apply-memory-limit-control-law
                  memory-limit-info time-since-last-update)
                 (loop for limit-info-for-size in memory-limit-info
                       do (apply-memory-limit-control-law
                           limit-info-for-size time-since-last-update))))
    (setq time-of-last-thrashing-cost-update fixnum-time-now
          decache-occurred-since-last-update? nil))

  ;; Change update interval based on thrashing?
  )


(defun update-memory-limits (fixnum-time-now)
  (declare (eliminate-for-gsi))
  (update-memory-limits-if-time-to-check fixnum-time-now))

;; This is called from run-scheduler-1 at regular intervals.  It uses
;; decache-occurred-since-last-update?  to decide whether to use the long or
;; short thrashing-cost-update-interval.
;; -- UPDATE: This is now also called from run-telewindows-top-level-2, which
;; is that system's scheduler body, at regular intervals.  It had been a bug
;; in all version of Telewindows, from 2.0 to present 3.0 (rev. 3 is the
;; current rev) that this was not called, and therefore memory limits were
;; never upped in Telewindows, leaving TW to thrash forever. (MHD 7/19/93)

;; I divided update-memory-limits into a macro, to do the time-to-check test,
;; and a function, actually a defun-void, to do the actual updating, for a bit
;; of efficiency gain.  I also took out the nil test for
;; time-of-last-thrashing-cost-update, which can now not ever by nil.
;; Update-memory-limits was then rewritten in terms of the new macro/function
;; team.  (MHD 7/20/93)

;; Consider having the interval be adjusted continuously by update-memory-limits,
;; perhaps based on thrashing cost.  Note however that this technique would have
;; a lag since thrashing cost isn't computed until update-memory-limits is
;; called.  Thus, using decache-occurred-since-last-update? is still necessary
;; to ensure quick response.



(defparameter positive-thrashing-error-gain 1)

(defparameter negative-thrashing-error-gain 1)



(declare-forward-reference compute-newest-thrashing-ratio function)


;;; Apply-memory-limit-control-law adjusts the memory limit based on the
;;; thrashing error by applying a feedback control law.  Five parameters
;;; can be used to tune response:
;;; - global-desired-thrashing-setpoint
;;; - positive-thrashing-error-gain
;;; - negative-thrashing-error-gain
;;; - base-for-exponential-weighting
;;; - thrashing-cost-update-interval.
;;; Also, the function for computing thrashing cost when decaching (see
;;; define-decacheable-structure) can be used to tune response.  Only
;;; global-desired-thrashing-setpoint should be made a user settable
;;; parameter.

(defun apply-memory-limit-control-law
       (memory-limit-info time-since-last-update)
  (declare (eliminate-for-gsi))
  (with-temporary-gensym-float-creation apply-memory-limit-control-law
    (multiple-value-bind
      (newest-thrashing-ratio filtered-thrashing-ratio)
        (compute-newest-thrashing-ratio
          memory-limit-info time-since-last-update)
      newest-thrashing-ratio
      (let* ((limit (allocation-limit memory-limit-info))
             (thrashing-error
               (- filtered-thrashing-ratio
                  global-desired-thrashing-setpoint)))

        (if (> thrashing-error 0)
            (setf (allocation-limit memory-limit-info)
                  (+f limit
                      (round (* thrashing-error
                                positive-thrashing-error-gain)))))
        ;; Clamp with some maximum?!
        ;; Note that the round provides some hysteresis.

        (if (< thrashing-error 0)
            (setf (allocation-limit memory-limit-info)
                  (maxf minimum-decacheable-structure-allocation-limit
                        (+f limit
                            (round (* thrashing-error
                                      negative-thrashing-error-gain))))))
        ))))

;; If time-since-last-update is nil, then the thrashing-cost is not divided.  May
;; want to divide by some constant amount.  In any case, there is no information
;; about the time period in which the thrashing took place.  Thus, it is assumed
;; that the time period is short (a worst case thrashing assumption) and the
;; thrashing cost is not divided.  A better approach might be to not do anything
;; if the time-since-last-update is nil and let the next call to
;; update-memory-limits update things.

;; Could use some combination of newest and filtered thrashing ratios (see also
;; notes under compute-weighting-factors-for-thrashing-filter for ideas on other
;; control schemes).

;; Note that memory limit can (and typically will) decrease since typically, no
;; thrashing is occuring.  This means that the limit will typically be less than
;; the number allocated.  This is OK since it will cause decaching when new ones
;; are needed.  If thrashing continues over some time, the memory limit will be
;; increased above the number allocated which will allow new ones to be allocated
;; to stop the thrashing.  Thus, the memory limit itself is something of a low
;; pass filtering mechanism for the thrashing cost.

;; Consider varying thrashing-cost-update-interval, making it shorter when there
;; is a lot of thrashing. - already done -
;; Also, consider having global-desired-thrashing-setpoint
;; be based on how much available memory is left.  Thus, if the system gets close
;; to running out of memory, the thrashing setpoint could be increased causing
;; more decaching rather than allocation.

;; Note that there is no reason to vary desired thrashing ratio for each
;; pool.  The cost function provides all the individualization needed.





;;;; No Simulation Value

(def-system-variable simulation-no-value UTILITIES2
  (:funcall gentemp "simulation-no-value-"))

;; Gentemp is used here so that a reserved word is not necessary.
;; Gentemp, rather than gensym is used so that the string
;; "simulation-no-value" is not used by default for subsequent calls
;; to gensym.



(def-substitution-macro no-simulation-value-p (value)
  (eq value simulation-no-value))





;; jh & mhd, 6/3/92.  Moved avoiding-variable-capture to UTILITIES0.



;;;; Ordering Subforms in a Macroexpansion

;; (jh, 8/19/91, from an idea of BAH)

;;; with-ordered-macroexpansion (tags-in-desired-order form-containing-tags)

;;; With-ordered-macroexpansion ensures that subforms of a macro will be expanded
;;; in a desired order.  Given an unevaluated list tags-in-desired-order, this
;;; macro walks down form-containing-tags, gathering those subforms whose car is
;;; eql to a tag.  It then macroexpands the tagged forms in the order they appear
;;; in tags-in-desired-order, and incorporates these macroexpansions into
;;; form-containing-tags.

;;; Although CLtL/2e says (p 91) that top-level forms must be compiled in the same
;;; order they appear in the source file, there is no guarantee that subforms of a
;;; top-level form are processed in any particular order, hence the need for the
;;; with-ordered-macroexpansion wrapper in some complicated macros.

;;; For example,
;;;
;;;(defmacro register-font-resource (font-id)
;;;  (with-ordered-macroexpansion (-1- -2-)
;;;    `(progn
;;;       (-2- create-resource-file ,font-id)
;;;       (-1- note-resource-file-name))))
;;;
;;; is equivalent to
;;;
;;;(defmacro register-font-resource (font-id)
;;;  (let* ((#:macroexpansion-2
;;;            (macroexpand
;;;                 `(create-resource-file ,font-id)))
;;;            (#:macroexpansion-1
;;;               (macroexpand
;;;                 `(note-resource-file-name))))
;;;     `(progn ,#:macroexpansion-2
;;;                ,#:macroexpansion-1)))
;;;
;;; Actually, because of the implementation-specificity of backquote,
;;; with-ordered-macroexpansion expands to something more opaque, but the behavior
;;; is identical.

;;; Note that it is an error to place a tag in front of a subform that will not be
;;; macroexpanded in the usual manner.  That is, this won't work:
;;;   (let ((-1- greetings (translate-into-current-language "hello"))) ...)
;;; and neither will this:
;;;   (setf (-5- svref my-array 2) (register-array-element))
;;; but this will work:
;;;   (let ((greetings (-1- translate-into-current-language "hello"))) ...)
;;; as will this:
;;;   (setf (svref my-array 2) (-5- register-array-element))

;;; Almost needless to say, with-ordered-macroexpansion cannot control the order
;;; of expansion of symbols given a macroexpansion by symbol-macrolet.

(defun-for-macro walk-form-for-ordered-macroexpansion
                 (form tags-in-desired-order)
  (let ((macroexpansion-ordering-specs nil)
        (tags-in-reversed-order (reverse tags-in-desired-order)))
    (labels ((walk-form (form superior-tags locative)
               (if (and (consp form)
                        (not (eq (car form) 'quote)))
                   (let* ((tag (car form))
                          (previous-tags?
                            (memq tag tags-in-reversed-order)))
                     (cond
                       (previous-tags?
                        (when (intersection previous-tags? superior-tags)
                          (error "WITH-ORDERED-MACROEXPANSION: ~
                                  Circularity detected around tag ~a"
                                 tag))
                        (let ((augmented-superior-tags
                                (cons tag superior-tags))
                              (spine-of-subform
                                (copy-list (cdr form))))
                          (push (list tag locative (cdr form))
                                macroexpansion-ordering-specs)
                          (loop for subform in spine-of-subform
                                for sub-locative on spine-of-subform
                                do
                                (setf (car sub-locative)
                                      (walk-form
                                        subform
                                        augmented-superior-tags
                                        sub-locative))
                                while ;list might be dotted
                                (consp (cdr sub-locative)))
                          spine-of-subform))
                       (t (let ((spine-of-subform (copy-list form)))
                            (loop for subform in spine-of-subform
                                  for sub-locative on spine-of-subform
                                  do
                                  (setf (car sub-locative)
                                        (walk-form
                                          subform
                                          superior-tags
                                          sub-locative))
                                  while ;list might be dotted
                                  (consp (cdr sub-locative)))
                            spine-of-subform))))
                   form)))
      (let* ((outer-locative (cons form nil))
             (walked-form (walk-form form nil outer-locative)))
        (setf (car outer-locative) walked-form)
        (values (loop for tag in tags-in-desired-order
                      for spec = (assoc tag macroexpansion-ordering-specs)
                      when spec
                        collect (rest spec))
                outer-locative)))))

(defmacro with-ordered-macroexpansion
          (tags-in-desired-order &body list-of-form-not-implicit-progn)
  (let ((form (car list-of-form-not-implicit-progn)))
    `(multiple-value-bind (ordering-specs cons-containing-form)
         (walk-form-for-ordered-macroexpansion
           ,form
           ',tags-in-desired-order)
       (loop for (locative subform)
                 in ordering-specs
             do
             (setf (car locative)
                   (macroexpand subform)))
       (car cons-containing-form))))



;; Testing with-ordered-macroexpansion

;;(defvar current-font-resource-file-name nil)

;;(defmacro create-resource-file (font-id)
;;  (format t "~&creating resource file for ~a~%" font-id)
;;  (setq current-font-resource-file-name
;;        (format nil "FONT-~a" font-id))
;;  `(create-resource-file-1 ,font-id))

;;(defmacro note-resource-file-name ()
;;  (format t "~&current font resource file is ~s~%"
;;          current-font-resource-file-name)
;;  `(note-resource-file-name-1 current-font-resource-file-name))

;;(defmacro reclaim-resource-file-name ()
;;  (format t "~&reclaiming resource file name~%")
;;  (setq current-font-resource-file-name nil)
;;  nil)

;;(defmacro create-font-resource (font-id)
;;  (with-ordered-macroexpansion (-1- -2- -3-)
;;    `(progn
;;       (-1- create-resource-file ,font-id)
;;       (-3- reclaim-resource-file-name)
;;       (-2- note-resource-file-name))))

;;(create-font-resource 123)





;;;; Incremental Subfunction Definition

;; jh, 9/12/91.

;;; defun-incremental <generic-name> <method-name> <combiner> <lambda-list> &body <body>
;;; undefun-incremental <generic-name> <method-name>

;;; commit-incremental-defun <generic-name>
;;; release-incremental-defun <generic-name>

;;; commit-all-incremental-defuns
;;; release-all-incremental-defuns

;;; The idea is to allow incremental definition of subfunctions in development
;;; while avoiding performance penalties in distribution.

;;; Defun-incremental is a function-defining form meant to be used at top-level.
;;; It defines an overlay function named <generic-name> if one is not already
;;; known, and a method function with a unique name which will evaluate the forms
;;; in <body> when the function <generic-name> is called.  Subsequent
;;; defun-incremental forms mentioning the same <generic-name> but a different
;;; <method-name> will cause additional method functions to be executed when
;;; <generic-name> is called.  Currently [9/12/91], each <lambda-list> must not
;;; contain any lambda-list-keywords and must be the same length.

;;; An association is maintained between (generic-name .  method-name) tags and
;;; <body> forms.  When both the <generic-name> and the <method-name> of a new
;;; defun-incremental are eql to a previously-defined association, that association
;;; is overwritten.

;;; When called, the overlay function will evaluate all method bodies that have
;;; been encountered up to that point, as if by evaluating the form
;;;    `(,combiner (progn ,@body1) (progn ,@body2) ...).
;;; The order in which body1, body2, ...  are executed is the order in which their
;;; respective methods were defined (in other words, build order is used).

;;; At first, the overlay function evaluates method bodies by looping through all
;;; known method functions.  Then, when <generic-name> is `committed' via
;;; commit-incremental-defun, all existing method bodies are assembled into a
;;; single defun.  Individual method functions are no longer called, which brings
;;; about a savings in performance.  The trade-off is that subsequent
;;; defun-incrementals of <generic-name> will not take effect until after
;;; <generic-name> is `released' via release-incremental-defun, although this is
;;; something that is only needed in development.

;;; If the overlay function has not yet been committed, and if its <combiner> is a
;;; special form (e.g.  or), the loop through its method functions must contain an
;;; inner form which will simulate the behavior of <combiner>.  The macro
;;; def-incremental-combiner (vide infra) supplies this behavior.

;;; If the overlay function was called before a call to commit-incremental-defun
;;; or commit-all-incremental-defuns, the table defun-incremental-runtime-registry
;;; is used at run time to run the method-functions.  Afterwards, the overlay
;;; function is monolithic, and the effects of executing any subsequent
;;; defun-incrementals with that generic-name do not have any effect on the
;;; behavior of the function.  The intervening defun-incrementals are registered
;;; in the defun-incremental-xxx-registry tables, however, and after a call to
;;; release-incremental-defun or release-all-incremental-defuns, the function will
;;; behave in accordance with these intervening forms.

;;; For example,

;;;(defun-incremental bunch-o-greetings progn 1 () (format t "~&hi~%"))
;;;(defun-incremental bunch-o-greetings progn 2 () (format t "~&hello~%"))
;;;(bunch-o-greetings)
;;;hi
;;;hello
;;;NIL

;;;(defun-incremental bunch-o-greetings progn 2 () (format t "~&how are you~%"))
;;;(bunch-o-greetings)
;;;hi
;;;how are you ;ordering among methods is preserved
;;;NIL

;;;(undefun-incremental bunch-o-greetings 2)
;;;(bunch-o-greetings)
;;;hi
;;;NIL

;;;(defun-incremental bunch-o-greetings progn 2 () (format t "~&wherefore art thou~%"))
;;;(commit-incremental-defun bunch-o-greetings)
;;;(bunch-o-greetings)
;;;hi
;;;wherefore art thou
;;;NIL

;;;(defun-incremental bunch-o-greetings progn 2 () (format t "~&hello~%"))
;;;(bunch-o-greetings)
;;;hi
;;;wherefore art thou ;incremental defun registered, but has no effect
;;;NIL

;;;(release-incremental-defun bunch-o-greetings)
;;;(bunch-o-greetings)
;;;hi
;;;hello ;intervening incremental defun is now noticed
;;;NIL

;;; Note that defun-incremental is a development-only facility, since conses are
;;; dropped at various points in the defun-incremental process.  The tables
;;; defun-incremental-runtime-registry, defun-incremental-compile-time-registry,
;;; and combiners-for-defun-incremental will be empty in a #+no-macros image,
;;; because by that time all incremental defuns should be committed.



;;; def-incremental-combiner ( <var> ) &rest <body>

;;; The macro def-incremental-combiner indicates how an incremental defun method is
;;; to be executed, based on a given combiner.  Until the incremental defun is
;;; committed, each method function is executed inside a loop in which a variable
;;; is setq'd to the result of evaluating the method.  Def-incremental-combiner
;;; registers a unique variable to hold this result, along with an expander
;;; function which returns code which is inserted into the loop at macroexpansion
;;; time, and which will handle the result value at runtime.  If the expander
;;; function returns nil nothing is placed inside the loop, to avoid
;;; mis-identifying nil as a loop keyword.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar combiners-for-defun-incremental nil)
)

(defmacro def-incremental-combiner
          (combiner (var &key ordering) &body body-with-var)
  (declare (ignore ordering)) ;for now [9/12/91]
  (if (eval-feature :no-macros)
      nil
      (let ((unique-var-for-incremental-combiner
              (make-symbol (symbol-name var)))
            (expander-for-incremental-combiner
              (intern (format nil "INCREMENTAL-COMBINER-FOR-~a" combiner))))
        `(eval-when (:compile-toplevel :load-toplevel :execute)
           (defun-for-macro ,expander-for-incremental-combiner (,var)
             ,@body-with-var)
           (let ((old-entry?
                   (loop for entry in combiners-for-defun-incremental
                         thereis (and (eq (first entry) ',combiner)
                                      entry))))
             (cond (old-entry?
                    (setf (second old-entry?)
                          ',unique-var-for-incremental-combiner)
                    (setf (third old-entry?)
                          #',expander-for-incremental-combiner))
                   (t (push (list ',combiner
                                  ',unique-var-for-incremental-combiner
                                  #',expander-for-incremental-combiner)
                            combiners-for-defun-incremental))))))))


(def-incremental-combiner and (result)
  `(unless ,result (loop-finish)))

(def-incremental-combiner or (result)
  `(when ,result (loop-finish)))

(def-incremental-combiner progn (result)
  (declare (ignore result))
  nil)




;; The variable defun-incremental-compile-time-registry is used at compile time to
;; create overlay and method functions.  It is a list of sublists, one per overlay
;; function.  Each sublist is of the form:
;; ( <generic-name> <combiner> <lambda-list> . <methods> )
;; where <methods> is a list which alternates <method-name> with <method-body>.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar defun-incremental-compile-time-registry nil)
)

;; The variable defun-incremental-runtime-registry is used at runtime in
;; development to execute overlay functions which have not yet been committed.  It
;; is a list of sublists, one per overlay function.  The car of each sublist names
;; the overlay function; the cdr is a list which alternates <method-name> with
;; method functions, which are compiled function objects.

(defvar defun-incremental-runtime-registry nil)

(defun-for-macro update-existing-defun-incremental-at-compile-time
                 (entry
                   generic-name
                   method-name
                   combiner
                   lambda-list
                   body)
  (let ((old-combiner (second entry)))
    (unless (eq old-combiner combiner)
      (error "DEFUN-INCREMENTAL: combiner mismatch while defining ~a, ~
              need the combiner ~a; can't use ~a"
             generic-name
             old-combiner
             combiner)))
  (let ((old-lambda-list (third entry)))
    (unless (lambda-lists-conform-p old-lambda-list lambda-list)
      (error "DEFUN-INCREMENTAL: lambda-list mismatch while defining ~a,~%~
              need the lambda-list ~a; can't use ~a"
             generic-name
             old-lambda-list
             lambda-list)))
  (let ((cons-containing-method?
          (loop for cons-possibly-containing-method
                    on (nthcdr 3 entry)
                    by 'cddr
                thereis (and (eq (car cons-possibly-containing-method)
                                 method-name)
                             cons-possibly-containing-method))))
    (if cons-containing-method?
        (setf (second cons-containing-method?)
              body)
        (if entry
            (setf (cdr (last entry))
                  (list method-name
                        body))
            (error "DEFUN-INCREMENTAL: corrupt compile-time registry")))))



(defun-for-macro expander-for-existing-defun-incremental
                 (generic-name
                  method-name
                  combiner
                  lambda-list
                  body)
  (let ((name-for-incremental-method
          (intern
            (format nil
                    "~a-METHOD-FOR-~a-USING-~a"
                    method-name generic-name combiner))))
    `(progn
       (defun ,name-for-incremental-method
              ,lambda-list
         ,@body)
       (let* ((entry
                (assoc ',generic-name defun-incremental-runtime-registry))
              (cons-containing-method?
                (loop for cons-possibly-containing-method
                          on (cdr entry)
                          by 'cddr
                      thereis (and (eq (car cons-possibly-containing-method)
                                       ',method-name)
                                   cons-possibly-containing-method))))
         (if cons-containing-method?
             (setf (second cons-containing-method?)
                   #',name-for-incremental-method)
             (if entry
                 (setf (cdr (last entry))
                       (list ',method-name
                             #',name-for-incremental-method))
                 (error "DEFUN-INCREMENTAL: corrupt runtime registry")))))))



(defun-for-macro expander-for-uncommitted-incremental-defun
                 (generic-name
                   combiner
                   lambda-list)
  (let ((combiner-spec?
          (assoc combiner combiners-for-defun-incremental)))
    (unless combiner-spec?
      (error "DEFUN-INCREMENTAL: unknown combiner ~a while defining ~a"
             combiner
             generic-name))
    (let ((combiner-var (second combiner-spec?))
          (combiner-expander (third combiner-spec?)))
      `(defun ,generic-name
              ,lambda-list
         (let ((,combiner-var nil))
           (loop for (nil method-function-object)
                     on (cdr (assoc ',generic-name
                                    defun-incremental-runtime-registry))
                     by 'cddr
                 do
                 (setq ,combiner-var
                       (funcall method-function-object ,@lambda-list))
                 ,@(let ((combiner-form?
                           (funcall combiner-expander combiner-var)))
                     (if combiner-form?
                         (list combiner-form?)
                         nil))
                 finally
                 (return ,combiner-var)))))))


(defun-for-macro notice-new-defun-incremental-at-compile-time
                 (generic-name
                   method-name
                   combiner
                   lambda-list
                   body)
  (let ((entry (list generic-name combiner lambda-list)))
    (push entry defun-incremental-compile-time-registry)
    (update-existing-defun-incremental-at-compile-time
      entry
      generic-name
      method-name
      combiner
      lambda-list
      body)))



(defun-for-macro expander-for-new-defun-incremental
                 (generic-name
                   method-name
                   combiner
                   lambda-list
                   body)
  `(progn
     ,(expander-for-uncommitted-incremental-defun
        generic-name
        combiner
        lambda-list)
     (push (list ',generic-name) defun-incremental-runtime-registry)
     ,(expander-for-existing-defun-incremental
        generic-name
        method-name
        combiner
        lambda-list
        body)))



(defmacro defun-incremental
          (generic-name combiner method-name lambda-list &body body)
  (if (eval-feature :no-macros)
      nil
      (let ((entry?
              (assoc generic-name defun-incremental-compile-time-registry)))
        (cond (entry?
               (update-existing-defun-incremental-at-compile-time
                 entry?
                 generic-name
                 method-name
                 combiner
                 lambda-list
                 body)
               (expander-for-existing-defun-incremental
                 generic-name
                 method-name
                 combiner
                 lambda-list
                 body))
              (t (notice-new-defun-incremental-at-compile-time
                   generic-name
                   method-name
                   combiner
                   lambda-list
                   body)
                 (expander-for-new-defun-incremental
                   generic-name
                   method-name
                   combiner
                   lambda-list
                   body))))))



(defmacro undefun-incremental (generic-name &optional method-name?)
  (cond (method-name?
         (let ((entry?
                 (assoc generic-name
                        defun-incremental-compile-time-registry)))
           (when entry?
             (let ((locative-of-method?
                     (loop for possible-locative-of-method
                               on entry?
                               by 'cddr
                           thereis
                           (and (eq (cadr possible-locative-of-method)
                                    method-name?)
                                possible-locative-of-method))))
               (when locative-of-method?
                 (setf (cdr locative-of-method?)
                       (cdddr locative-of-method?))))))
         `(let ((entry?
                  (assoc ',generic-name defun-incremental-runtime-registry)))
            (when entry?
              (let ((locative-of-method?
                      (loop for possible-locative-of-method
                                on entry?
                                by 'cddr
                            thereis
                            (and (eq (cadr possible-locative-of-method)
                                     ',method-name?)
                                 possible-locative-of-method))))
                (when locative-of-method?
                  (setf (cdr locative-of-method?)
                        (cdddr locative-of-method?)))))))
        (t (cond ((eq (caar defun-incremental-compile-time-registry)
                       generic-name)
                   (pop defun-incremental-compile-time-registry))
                  (t (let ((locative-of-generic?
                             (loop for possible-locative-of-generic
                                       on defun-incremental-compile-time-registry
                                   thereis
                                   (and (eq (caadr
                                              possible-locative-of-generic)
                                            generic-name)))))
                       (when locative-of-generic?
                         (setf (cdr locative-of-generic?)
                               (cddr locative-of-generic?))))))
           `(cond ((eq (caar defun-incremental-runtime-registry)
                       ',generic-name)
                   (pop defun-incremental-runtime-registry))
                  (t (let ((locative-of-generic?
                             (loop for possible-locative-of-generic
                                       on defun-incremental-runtime-registry
                                   thereis
                                   (and (eq (caadr
                                              possible-locative-of-generic)
                                            ',generic-name)))))
                       (when locative-of-generic?
                         (setf (cdr locative-of-generic?)
                               (cddr locative-of-generic?)))))))))


(defmacro commit-incremental-defun (generic-name)
  (let ((entry?
          (assoc generic-name defun-incremental-compile-time-registry)))
    (unless entry?
      (error "COMMIT-INCRMENTAL-DEFUN: no incremental defun named ~a"
             generic-name))
    (let ((combiner (second entry?))
          (lambda-list (third entry?)))
      `(defun ,generic-name
              ,lambda-list
         (,combiner
              ,@(loop for (nil body)
                        on (nthcdr 3 entry?)
                        by 'cddr
                    collect `(progn ,@body)))))))


(defmacro release-incremental-defun (generic-name)
  (let ((entry?
          (assoc generic-name defun-incremental-compile-time-registry)))
    (unless entry?
      (error "RELEASE-INCRMENTAL-DEFUN: no incremental defun named ~a"
             generic-name))
    (let ((combiner (second entry?))
          (lambda-list (third entry?)))
      (expander-for-uncommitted-incremental-defun
        generic-name
        combiner
        lambda-list))))

(defmacro commit-all-incremental-defuns ()
  `(progn
     ,@(loop for (generic-name combiner lambda-list . methods)
                 in defun-incremental-compile-time-registry
             collect
             `(defun ,generic-name
                     ,lambda-list
                (,combiner
                   ,@(loop for (nil body)
                               on methods
                               by 'cddr
                           collect `(progn ,@body)))))))


(defmacro release-all-incremental-defuns ()
  `(progn
     ,@(loop for (generic-name combiner lambda-list)
                 in defun-incremental-compile-time-registry
             collect
             (expander-for-uncommitted-incremental-defun
               generic-name
               combiner
               lambda-list))))







;;;; Computing Tagbody Labels at Runtime

;; jh, 9/13/91.

;;; dynamic-tagbody <specs> &body <body>

;;; Dynamic-tagbody behaves like a tagbody with its labels found at runtime, as if
;;; by throw instead of go.  The <specs> subform specifies which symbols in <body>
;;; will serve as catchers.  Each <spec> has two elements, a tag-symbol and a
;;; tag-form.  When a dynamic-tagbody is first evaluated, each tag-form is
;;; evaluated in order.  Then the forms in <body> which are not tag-symbols are
;;; evaluated as an implicit progn.  Each tag-symbol in <body> will catch any throw
;;; made to its value during the dynamic extent of the progn, and control will
;;; resume after that tag-symbol.  The thrown value is dropped unless the
;;; symbol-tag the last component of <body>.  If the last component in <body> is a
;;; tag-symbol and is thrown to, dynamic-tagbody will return a single value from
;;; that throw; otherwise, dynamic-tagbody will return a single value from the last
;;; form in the implicit progn when control reaches there.

;;; For example,

;;;(dynamic-tagbody
;;;  ((xxx 1)
;;;   (yyy 2)
;;;   (zzz 3)
;;;   (www 4))
;;;  xxx
;;;  (format t "~&first!~%")
;;;  (throw (+ 1 2) 'pending) ;thrown value ignored
;;;  yyy
;;;  (format t "~&second!~%")
;;;  (throw (+ 2 2) 'my-result)
;;;  zzz
;;;  (format t "~&third!~%")
;;;  (throw (+ 1 1) 'pending) ;thrown value ignored
;;;  www))

;;;first!
;;;third!
;;;second!
;;;MY-RESULT




(defun-for-macro expander-for-dynamic-tagbody-forms
       (result tags-and-flags forms-between-tags)
  `(let ,(loop for (nil . flag) in tags-and-flags
               collect `(,flag t))
     (setq ,result
           ,(labels
              ((make-nested-catch (tags-and-flags)
                 (cond ((null (cdr tags-and-flags))
                        `(catch ,(caar tags-and-flags)
                           (prog1
                             ,(if (cdr forms-between-tags)
                                  `(progn ,@(reverse forms-between-tags))
                                  (car forms-between-tags))
                             (setq ,(cdar tags-and-flags) nil))))
                       (t `(catch ,(caar tags-and-flags)
                             (prog1
                               ,(make-nested-catch (cdr tags-and-flags))
                               (setq ,(cdar tags-and-flags) nil)))))))
              (make-nested-catch tags-and-flags)))
     (cond ,@(loop for (tag . flag) in tags-and-flags
                   collect `(,flag (go ,tag))))))



(defmacro dynamic-tagbody (tag-specs &body tags-and-forms)
  (avoiding-variable-capture (&aux result dynamic-tagbody)
    (let ((tags-and-flags
            (loop for (tag) in tag-specs
                  for index from 1
                  collect
                  (cons tag
                        (make-symbol (format nil "THREW-TO-~a" tag))))))
      `(block ,dynamic-tagbody
         (let* (,result
                ,@tag-specs)
           (tagbody
               ,@(loop for tag-or-form
                           in tags-and-forms
                       with forms-between-tags = nil
                       with expansion = nil
                       do
                       (cond ((member tag-or-form tag-specs :key #'car)
                              (when forms-between-tags
                                (push (expander-for-dynamic-tagbody-forms
                                        result
                                        tags-and-flags
                                        forms-between-tags)
                                      expansion))
                              (setq forms-between-tags nil)
                              (push tag-or-form expansion))
                             (t (push tag-or-form
                                      forms-between-tags)))
                       finally
                       (when forms-between-tags
                         (push (expander-for-dynamic-tagbody-forms
                                 result
                                 tags-and-flags
                                 forms-between-tags)
                               expansion))
                       (return (nreverse expansion)))
               (return-from ,dynamic-tagbody ,result)))))))



;;;; Concise Trees of Managed Conses

;; jh, 9/17/91, from an idea of BAH

;;; managed-backquote <managed-conser> <template>

;;; It would be nice to form arbitrary trees of managed conses in a concise
;;; manner.  We would like <template> to look as much like a backquoted form as
;;; possible, but the challenge is to do this without using a read macro, which is
;;; absolute anathema for G2 building.  We bypass the read macro mechanism
;;; entirely and simply use symbols and printname-decorations which resemble
;;; Common Lisp backquote syntax.  The visual difference is that the initial comma
;;; marker for unquoting and unquote-splicing is preceded by the single-character
;;; escape.

;;; For example,

;;;(let ((people (icp-list 'john)))
;;;  (managed-backquote icp-cons
;;;    (hi (there \,@people))))

;;; is equivalent to

;;;(let ((people (icp-list 'john)))
;;;  (icp-cons 'hi
;;;    (icp-cons
;;;      (icp-cons
;;;        'there
;;;        people)
;;;      nil)))

;;; Some caveats:

;;; Note that \,@ (the analogue of the ,@ reader macro) destructively modifies
;;; lists and so is actually more similar to the ,. reader macro in Common Lisp.
;;; We mimic the ,@ reader macro anyway, since it is more familiar and visually
;;; clearer.

;;; Note that a form like `(a \,@b c) will "lose" the cdr of the last cons in b,
;;; even if that cdr is non-nil.  Such constructs can result in leaks when used
;;; carelessly.  This is true in the Common Lisp backquote as well (CLtL/2e pp
;;; 528-529).  Note that a form like `(a \,@b) will not "lose" the last cdr of b,
;;; since the entire list b is spliced in.  Again, this is in accord with Common
;;; Lisp.

;;; Note that nested unquoting will not work in managed-backquote.  A nested
;;; unquote is two or more \, or \,@ markers in a row, with possibly intervening
;;; quotes.  Managed-backquote forms may be evaluated within other managed
;;; backquote forms, however, as long as the unquotes themselves are not nested.

;;; For now (jh, 9/17/91) there should be no whitespace between the , and the @ of
;;; the unquote-splice marker, and there must be whitespace before the , marker.

(defmacro managed-backquote (managed-conser template)
  (expander-for-managed-backquote managed-conser template))

(defun-for-macro expander-for-managed-backquote (managed-conser template)
  (flet ((solitary-unquote-p (element) (eq '\, element))
         (solitary-unquote-splice-p (element) (eq '\,@ element))
         (unquote-p (element)
           (and (symbolp element)
                (let ((name (symbol-name element)))
                  (and (eql (elt name 0) #\,)
                       (not (eql (elt name 1) #\@))))))
         (unquote-splice-p (element)
           (and (symbolp element)
                (let ((name (symbol-name element)))
                  (and (eql (elt name 0) #\,)
                       (eql (elt name 1) #\@)))))
         (de-unquote (element)
           (let ((name (symbol-name element)))
             (intern (subseq name 1))))
         (de-unquote-splice (element)
           (let ((name (symbol-name element)))
             (intern (subseq name 2)))))
    (let ((index-for-tail-values 0)
          (splice-onto-tail (make-symbol "SPLICE-ONTO-TAIL")))
      (loop with flattened-consing-form = nil
            do
            (gensym-dstruct-bind ((element . next-element) template)
              (cond ;; The element is a subform.
                    ((consp element)
                     (push managed-conser flattened-consing-form)
                     (push (expander-for-managed-backquote
                             managed-conser
                             element)
                           flattened-consing-form))

                    ;; The unquote marker is surrounded by whitespace.
                    ((solitary-unquote-p element)
                     (push managed-conser flattened-consing-form)
                     (push (car next-element) flattened-consing-form)
                     (setq template (cdr template))
                     (setq next-element (cdr next-element)))

                    ;; The unquote marker is part of a symbol, so there is no risk
                    ;; of side effects.
                    ((unquote-p element)
                     (push managed-conser flattened-consing-form)
                     (push (de-unquote element) flattened-consing-form))

                    ;; The unquote-splice marker is surrounded by whitespace.
                    ((solitary-unquote-splice-p element)
                     (cond
                       ;; We are in the middle of a list.
                       ((consp (cdr next-element))
                        (cond
                          ((constantp (car next-element))
                           (let ((runtime-value? (eval (car next-element))))
                             (when runtime-value?
                               (error
                                 "MANAGED BACKQUOTE: ~S is a non-NIL constant ~
                                  -- you don't want to side-effect it"
                                 (car next-element)))))
                          (t (let ((placeholder-for-tail
                                     (make-symbol
                                       (format nil "TAIL-VALUE-~a?"
                                               (incf index-for-tail-values)))))
                               (push 'let flattened-consing-form)
                               (push `((,placeholder-for-tail
                                          ,(car next-element)))
                                     flattened-consing-form)
                               (push splice-onto-tail flattened-consing-form)
                               (push placeholder-for-tail
                                     flattened-consing-form))))

                        ;; Skip the next element of the template.
                        (setq template (cdr template)))
                       ;; We are at the end of a list - throw away the old cdr.
                       (t (push (car next-element) flattened-consing-form)
                          (setq template (cdr template))
                          (loop-finish))))

                    ;; The unquote-splice marker is part of a symbol, so there is
                    ;; no risk of side effects.
                    ((unquote-splice-p element)
                     (let ((real-element (de-unquote-splice element)))
                       (cond

                         ;; We're in the middle of the template list.
                         ((consp next-element)
                          (cond
                            ((constantp real-element)
                             (let ((runtime-value? (eval real-element)))
                               (when runtime-value?
                                 (error
                                   "MANAGED BACKQUOTE: ~
                                    ~S is a non-NIL constant ~
                                    -- you don't want to side-effect it"
                                   real-element))))
                            (t (push splice-onto-tail flattened-consing-form)
                               (push real-element flattened-consing-form))))

                         ;; We're at the end of the template list.
                         (t (push real-element flattened-consing-form)
                            (loop-finish)))))

                    ;; There are no special unquote markers, so quote it.
                    (t (push managed-conser flattened-consing-form)
                       (push `(quote ,element) flattened-consing-form)))

              ;; Check if we're at the end of the list.
              (when (not (consp next-element))
                (cond ((null next-element)
                       (push nil flattened-consing-form))
                      ((unquote-p next-element)
                       (push (de-unquote next-element) flattened-consing-form))
                      ((unquote-splice-p next-element)
                       (push (de-unquote-splice next-element)
                             flattened-consing-form))
                      (t (push `(quote ,next-element) flattened-consing-form)))
                (loop-finish)))

            ;; If not at the end of the list, cdr down the template.
            (setq template (cdr template))

            finally
            (return
              ;; Unflatten the consing form and return it.  The trick is that
              ;; all the subforms in the flattened form take exactly two
              ;; arguments, so we can unflatten it easily.
              (loop with expanded-form
                    = `(,(third flattened-consing-form)
                           ,(second flattened-consing-form)
                           ,(first flattened-consing-form))
                    for (first-argument operator)
                        on (cdddr flattened-consing-form) by 'cddr
                    do
                    (setq expanded-form
                          `(,operator
                               ,first-argument
                               ,expanded-form))
                    finally
                    (return
                      `(macrolet ((,splice-onto-tail (tail? new)
                                    `(cond
                                       (,tail?
                                        (setf (cdr (last ,tail?)) ,new)
                                        ,tail?)
                                       (t ,new))))
                         ,expanded-form))))))))

#+development
(defparameter managed-backquote-validation-suite
  '(
    ((managed-backquote icp-cons (hi \,@nil there))
     (hi there))

    ((managed-backquote icp-cons (hi \,@nil \,@nil there))
     (hi there))

    ((let ((nothing nil))
       (managed-backquote icp-cons (hi \,@nothing \,@nothing there)))
     (hi there))

    ((managed-backquote icp-cons (hi \,@nil \,@(icp-list 'there)))
     (hi there))

    ((managed-backquote icp-cons (hi \,@(icp-list 'there) \,@(icp-list 'jh)))
     (hi there jh))

    ((managed-backquote icp-cons (hi there john))
     (hi there john))

    ((managed-backquote icp-cons (hi there . john))
     (hi there . john))

    ((let ((john 'me))
       (managed-backquote icp-cons (hi there \,john)))
     (hi there me))

    ((let ((john 'me))
       (managed-backquote icp-cons (hi there . \,john)))
     (hi there . me))

    ((let ((john (icp-list 'me)))
       (managed-backquote icp-cons (hi there \,@john)))
     (hi there me))

    ((let ((john (icp-cons 'me 'there)))
       (managed-backquote icp-cons (hi there \,@john my friend)))
     (hi there me my friend))

    ((let ((john (icp-list 'me)))
       (managed-backquote icp-cons
         (hi there (and felicitations \,@john my friend))))
     (hi there (and felicitations me my friend)))

    ((let ((john (icp-cons 'me 'there)))
       (managed-backquote icp-cons
         (hi there (and felicitations \,@john) my friend)))
     (hi there (and felicitations me . there) my friend))

    ;; same as above but with whitespace

    ((let ((john 'me))
       (managed-backquote icp-cons (hi there \, john)))
     (hi there me))

    ((let ((john (icp-list 'me)))
       (managed-backquote icp-cons (hi there \,@ john)))
     (hi there me))

    ((let ((john (icp-cons 'me 'there)))
       (managed-backquote icp-cons (hi there \,@ john my friend)))
     (hi there me my friend))

    ((let ((john (icp-list 'me)))
       (managed-backquote icp-cons
         (hi there (and felicitations \,@ john my friend))))
     (hi there (and felicitations me my friend)))

    ((let ((john (icp-cons 'me 'there)))
       (managed-backquote icp-cons
         (hi there (and felicitations \,@ john) my friend)))
     (hi there (and felicitations me . there) my friend))


    ;; same as above but with subforms, not symbols

    ((flet ((modify-name (name)
              (declare (ignore name))
              'me))
       (managed-backquote icp-cons (hi there \,(modify-name 'john))))
     (hi there me))

    ((flet ((listify-and-modify-name (name)
              (icp-cons 'me name)))
       (managed-backquote icp-cons
         (hi there \,@(listify-and-modify-name 'john) my friend)))
     (hi there me my friend))

    ((flet ((listify-and-modify-name (name)
              (icp-list 'me name)))
       (managed-backquote icp-cons
         (hi there (and felicitations
                        \,@(listify-and-modify-name 'john) my friend))))
     (hi there (and felicitations me john my friend)))

    ((flet ((listify-and-modify-name (name)
              (icp-list 'me name)))
       (managed-backquote icp-cons
         (hi there (and felicitations
                        \,@(listify-and-modify-name 'john)) my friend)))
     (hi there (and felicitations me john) my friend))

    ;; same as above with whitespace

    ((flet ((modify-name (name)
              (declare (ignore name))
              'me))
       (managed-backquote icp-cons (hi there \, (modify-name 'john))))
     (hi there me))

    ((flet ((listify-and-modify-name (name)
              (icp-cons 'me name)))
       (managed-backquote icp-cons
         (hi there \,@ (listify-and-modify-name 'john) my friend)))
     (hi there me my friend))

    ((flet ((listify-and-modify-name (name)
              (icp-list 'me name)))
       (managed-backquote icp-cons
         (hi there (and felicitations
                        \,@ (listify-and-modify-name 'john) my friend))))
     (hi there (and felicitations me john my friend)))

    ((flet ((listify-and-modify-name (name)
              (icp-list 'me name)))
       (managed-backquote icp-cons
         (hi there (and felicitations
                        \,@ (listify-and-modify-name 'john)) my friend)))
     (hi there (and felicitations me john) my friend))
    ))


#+development
(declare-forward-reference validate-gensym-lisp-facility function) ;UTILITIES3

#+development
(defun validate-managed-backquote (&optional verbose-p)
  (validate-gensym-lisp-facility managed-backquote-validation-suite verbose-p))




;;;; Conditional Binding

;; jh, 10/22/91.

;;; let*-while-true ( (<var> <init>) ... ) <body> ...

;;; The macro `let*-while-true' is useful in situations where we want to enter a
;;; binding scope only if all previous bindings are non-nil.  It resembles let* in
;;; that the bindings occur sequentially, but each binding is only made if the
;;; previous binding was to a non-nil form.  Note that this macro disallows the
;;; various degenerate binding forms permitted by let*, such as (let* (a) ...) and
;;; (let* ((a)) ...).

;;; For example,
;;;  (let*-while-true ((x? (get-x))
;;;                       (y? (get-y-assuming-x x?))
;;;                       (z? (get-z-assuming-x-and-y x? y?)))
;;;    (process-z-assuming-not-nil z?))

(defmacro let*-while-true (bindings &body body)
  (loop for (variable initialization) in (reverse bindings)
        with expansion? = nil
        do
    (if expansion?
        (setq expansion?
              `(let ((,variable ,initialization))
                 (when ,variable
                   ,expansion?)))
        (setq expansion?
              `(let ((,variable ,initialization))
                 (when ,variable
                   ,@body))))
        finally (return expansion?)))




;;;; Temping Cond Forms without Losing Readability

;; jh, 11/24/91.

;;; The macro `cond-with-temporaries' behaves exactly like cond, except that it
;;; makes an effort to bind temporary variables to subforms of tests which show up
;;; in later tests.

;;; For example,

;;;(cond-with-temporaries
;;;  ((and (hairy-test x)
;;;           (another-test x))
;;;   (process-x-passing-two-tests x))
;;;  ((hairy-test x)
;;;   (process-x-passing-hairy-test x)))

;;; will expand into

;;;(LET (#:COND-TEMPORARY-1)
;;;  (COND
;;;    ((AND (SETQ #:COND-TEMPORARY-1 (HAIRY-TEST X))
;;;             (ANOTHER-TEST X))
;;;     (PROCESS-X-PASSING-TWO-TESTS X))
;;;    (#:COND-TEMPORARY-1 (PROCESS-X-PASSING-HAIRY-TEST X))))


;;; The advantages of this construct are readability and automation.  Complicated
;;; cond clauses which for reasons of efficiency need to be temped will be more
;;; readable, and hence more maintainable.  And automation of the tedious process
;;; of temping cond clauses by hand should reduce coding errors.

;;; If any subform in any test has lexically apparent side effects, the results
;;; are unpredictable.  If any subform is a macro, it should be standard, that is,
;;; it should evaluate all of its arguments as a function does.

;;; Currently (11/24/91, jh), cond-with-temporaries does not insert temps into
;;; subforms of special forms except the first subforms of "and" and "or".  It
;;; does temp the outer special form itself, though.  As well,
;;; cond-with-temporaries makes no attempt as yet (jh, 11/24/91) to collapse
;;; multiple "and" or "or" subforms that appear in different cond clauses.
;;; Knowing that it does temp the first subform of an "and" or "or", however, often
;;; allows you to give it a hint without compromising readability too much.  For
;;; example, rewriting

;;;(cond-with-temporaries
;;;  ((and (test1 x)
;;;            (test2 x)
;;;           (test3 x))
;;;   ...)
;;;  ((and (test1 x)
;;;           (test2 x))
;;;   ...)
;;;  ((test1 x)
;;;   ...)

;;; as

;;;(cond-with-temporaries
;;;  ((and (and (test1 x)
;;;                (test2 x))
;;;           (test3 x))
;;;   ...)
;;;  ((and (test1 x)
;;;           (test2 x))
;;;   ...)
;;;  ((test1 x)
;;;   ...))

;;; will temp as much as possible, expanding into

;;;(LET (#:COND-TEMPORARY-1 #:COND-TEMPORARY-2)
;;;  (COND
;;;    ((AND (SETQ #:COND-TEMPORARY-1
;;;                   (AND (SETQ #:COND-TEMPORARY-2 (TEST1 X))
;;;                        (TEST2 X)))
;;;          (TEST3 X))
;;;     ...)
;;;    (#:COND-TEMPORARY-1 ...)
;;;    (#:COND-TEMPORARY-2 ...)))

(defun-for-macro get-subforms-and-locatives-from-cond-clause-test
                 (test-form locative)
  (let ((alist-of-subforms-and-locatives-thereto nil))
    (labels ((walk-for-subforms-and-locatives (subform locative)
               (cond
                 ((not (consp subform)) nil)
                 ((notany #'consp subform)
                  (push (list subform locative)
                        alist-of-subforms-and-locatives-thereto))
                 (t (let ((head-of-form (car subform))
                          (rest-of-form (cdr subform)))
                      (cond
                        ;; We know we'll at least evaluate the first subform on an
                        ;; "and" or "or".
                        ((memq head-of-form '(and or))
                         (push (list subform locative)
                               alist-of-subforms-and-locatives-thereto)
                         (walk-for-subforms-and-locatives
                           (cadr subform)
                           (cdr subform)))
                        ;; Stop walking at any other special form.
                        ((special-form-p head-of-form)
                         (push (list subform locative)
                               alist-of-subforms-and-locatives-thereto))
                        (t (push (list subform locative)
                               alist-of-subforms-and-locatives-thereto)
                           (loop for subform in rest-of-form
                                 for locative-of-subform on rest-of-form
                                 do
                             (walk-for-subforms-and-locatives
                               subform
                               locative-of-subform)))))))))
      (walk-for-subforms-and-locatives test-form locative)
      ;; If the list isn't reversed, get-rebuilt-clauses-for-cond-with-temporaries
      ;; ends up uselessly storing the side-effected subform.
      (nreverse alist-of-subforms-and-locatives-thereto))))




(defun-for-macro get-rebuilt-clauses-for-cond-with-temporaries (clauses)
  (loop
    with registry-for-subforms-of-tests = nil
    with uniquifying-tag-for-temporary-variables = 0
    with rebuilt-cond-clauses = nil
    with tail-cons-in-cond-clauses-so-far? = nil
    with test = nil
    for (test-form . actions) in clauses
    do

    ;; Defend against implementations of defmacro which displace.
    (setq test (copy-tree test-form))

    ;; Add cond clauses to the tail of the rebuilt list, while keeping track of
    ;; the head of the rebuilt list.
    (if tail-cons-in-cond-clauses-so-far?
        (let ((new-final-cons
                (list (cons test actions))))
          (setf (cdr tail-cons-in-cond-clauses-so-far?)
                new-final-cons)
          (setq tail-cons-in-cond-clauses-so-far? new-final-cons))
        (let ((first-cons
                (list (cons test actions))))
          (setq rebuilt-cond-clauses first-cons)
          (setq tail-cons-in-cond-clauses-so-far? first-cons)))

    ;; Process all subforms of the cond clause test, temping as necessary.
    (loop
      with clauses-binding-temporary-variables = nil
      for (subform-of-test cons-whose-car-is-subform-of-test)
      in (get-subforms-and-locatives-from-cond-clause-test
           test
           (car tail-cons-in-cond-clauses-so-far?))
      do

      ;; See if we've already encountered this subform in a previous test (or
      ;; previously in this test).
      (let ((entry-in-registry-for-subforms-of-tests?
              (assoc subform-of-test
                     registry-for-subforms-of-tests
                     :test #'tree-equal)))
        (if entry-in-registry-for-subforms-of-tests?

            ;; If we've encountered this subform, do the temping required (either
            ;; by using an extant temporary variable, or by creating a new one).
            (gensym-dstruct-bind
              ((nil
                 cons-whose-car-is-first-occurrence-of-subform
                 cons-whose-car-is-clause
                 temporary-variable?)
               entry-in-registry-for-subforms-of-tests?)

              ;; If we haven't already created a temporary variable for this
              ;; subform, do so now.
              (unless temporary-variable?
                (let ((new-temporary-variable
                        (make-symbol
                          (format nil "COND-TEMPORARY-~a"
                            (incf uniquifying-tag-for-temporary-variables)))))

                  ;; Add to the list of previous clauses around which we need to
                  ;; bind a temporary variable.
                  (let ((clause-already-binding-temporary-variable?
                          (assq cons-whose-car-is-clause
                                clauses-binding-temporary-variables)))
                    (if clause-already-binding-temporary-variable?
                        (setf
                          (cdr (last clause-already-binding-temporary-variable?))
                          (list new-temporary-variable))
                        (push
                          (list cons-whose-car-is-clause new-temporary-variable)
                          clauses-binding-temporary-variables)))

                  ;; In the cond form, set the temporary variable to the value of
                  ;; the subform's first occurrence.
                  (setf (car cons-whose-car-is-first-occurrence-of-subform)
                        `(setq
                           ,new-temporary-variable
                           ,(car cons-whose-car-is-first-occurrence-of-subform)))

                  ;; Record the temporary variable for possible re-use.
                  (setf (fourth entry-in-registry-for-subforms-of-tests?)
                        new-temporary-variable)

                  ;; Pass the temporary variable out of this "unless".
                  (setq temporary-variable? new-temporary-variable)))

              ;; Use the temporary variable instead of the repeated subform in the
              ;; current cond clause's test.
              (setf (car cons-whose-car-is-subform-of-test)
                    temporary-variable?))

            ;; If we haven't encountered this subform, register it so we can temp
            ;; it (if it repeats in this or subsequent cond clause tests).
            (push (list subform-of-test
                        cons-whose-car-is-subform-of-test
                        tail-cons-in-cond-clauses-so-far?
                        nil)
                  registry-for-subforms-of-tests)))
      finally

      ;; Replace every previous cond clause around which we need to bind a
      ;; temporary variable.
      (loop for (cons-whose-car-is-clause . temporary-variables)
            in clauses-binding-temporary-variables
            do
            (let ((remaining-clauses (cdr cons-whose-car-is-clause)))
              (setf (cdr cons-whose-car-is-clause) nil)
              (setf (car cons-whose-car-is-clause)
                    `(t (let ,temporary-variables
                          (cond ,(car cons-whose-car-is-clause)
                                ,@remaining-clauses)))))))

    finally (return rebuilt-cond-clauses)))


(defmacro cond-with-temporaries (&body clauses)
  (let* ((rebuilt-clauses
          (get-rebuilt-clauses-for-cond-with-temporaries clauses))
         (first-rebuilt-clause
           (first rebuilt-clauses)))
    (if (eq (first first-rebuilt-clause) 't)
        (second first-rebuilt-clause)
        `(cond ,@rebuilt-clauses))))



;; jh, 2/11/92.  Moved protected-let and protected-let* to UTILITIES0 so
;; it can be used in UTILITIES1.



;;;; EZ Queues


;;; EZ queues are user-friendly abstractions on top of enqueue and dequeue
;;; (from utilities0).  Now object oriented!


(defconser queue-item)

(def-structure (queue
                 (:print-function print-queue)
                 (:reclaimer reclaim-queue-internal)
                 (:constructor make-queue-internal
                               (queue-head-internal queue-tail-internal))
                 (:eliminate-for-products :gsi))
  queue-head-internal
  queue-tail-internal)

#+development
(defun print-queue (queue stream depth)
  (declare (ignore depth) (eliminate-for-gsi))
  (printing-random-object (queue stream)
    (format stream "~a (~d)"
            (name-of-type-description (type-description-of queue))
            (queue-length queue))))


(defun make-queue ()
  (declare (eliminate-for-gsi))
  (make-queue-internal nil nil))

(defun reclaim-queue (queue)
  (declare (eliminate-for-gsi))
  (clear-queue queue)
  (reclaim-queue-internal queue))


(defun queue-empty-p (queue)
  (declare (eliminate-for-gsi))
  (null (queue-head-internal queue)))

(defmacro queue-non-empty-p-macro (queue)
  `(queue-head-internal ,queue))

(defun queue-non-empty-p (queue)
  (declare (eliminate-for-gsi))
  (queue-non-empty-p-macro queue))





;;; The function `clear-queue' reclaims just the spine of
;;; the queue, not the queue entries.

(defun clear-queue (queue)
  (declare (eliminate-for-gsi))
  (when (queue-head-internal queue)
    (reclaim-queue-item-list (queue-head-internal queue)))
  (setf (queue-head-internal queue) nil
        (queue-tail-internal queue) nil))


;;; The function `queue-insert' inserts the element onto the TAIL of the queue,
;;; and returns the element.  (Ie, this is an ordinary enqueue).

(defun queue-insert (queue element)
  (declare (eliminate-for-gsi))
  #+development (assert (queue-p queue))
  (enqueue element
           (queue-head-internal queue)
           (queue-tail-internal queue)
           queue-item-cons))

;;; The function `queue-push' inserts the element onto the HEAD
;;; of the queue.

(defun queue-push (queue element)
  (declare (eliminate-for-gsi))
  #+development (assert (queue-p queue))
  (cond ((queue-head-internal queue)
         (queue-item-push element (queue-head-internal queue)))
        (t
         (enqueue element
                  (queue-head-internal queue)
                  (queue-tail-internal queue)
                  queue-item-cons)))
  element)

;;; The function `queue-pop' returns NIL if the queue is empty.

(defun queue-pop (queue)
  (declare (eliminate-for-gsi))
  #+development (assert (queue-p queue))
  (dequeue (queue-head-internal queue)
           (queue-tail-internal queue)
           reclaim-queue-item-cons))


(defun queue-peek (queue)
  (declare (eliminate-for-gsi))
  #+development (assert (queue-p queue))
  (car (queue-head-internal queue)))


;;; The macro `queue-delete-macro' deletes all entries in the queue satifying
;;; (test element (key entry)).  Each entry found is reclaimed with the
;;; supplied reclaimer macro.

(defmacro queue-delete-macro (queue element &key
                                    (key 'identity-macro)
                                    (test 'eq)
                                    (reclaimer 'identity-macro))
  (avoiding-variable-capture (queue element)
    `(when (queue-non-empty-p ,queue)
       (macrolet ((reclaim-entry-and-cons (cons)
                    `(progn
                       (,',reclaimer (car-of-cons ,cons))
                       (reclaim-queue-item-cons ,cons))))
         (setf (queue-head-internal ,queue)
               (delete-macro ,element (queue-head-internal ,queue)
                             :key ,key
                             :test ,test
                             :reclaimer reclaim-entry-and-cons))
         (setf (queue-tail-internal ,queue)
               (last (queue-head-internal ,queue)))
         ,queue))))




(defmacro do-queue-elements ((element queue) &body body)
  (avoiding-variable-capture (queue &aux sublist)
    `(loop for ,sublist = (queue-head-internal ,queue)
                        then (cdr-of-cons ,sublist)
           while ,sublist
           as ,element = (car-of-cons ,sublist)
           doing
       (progn ,@body))))


(defun queue-length (queue)
  (declare (eliminate-for-gsi))
  (let ((length 0))
    (do-queue-elements (element queue)
      element
      (incff length))
    length))


;;; The loop-path `queue-element' supplies the datums from the queue, unlike
;;; the constant-queue-elements path, which supplies internal queue element
;;; structures (for a totally different kind of queue).


(define-loop-path (queue-element) queue-elements-path (of))

(defun-for-macro queue-elements-path
    (path-name variable data-type prep-phrases inclusive? allowed-prepositions data)
  (declare (ignore data-type data allowed-prepositions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S" path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
           path-name variable prep-phrases))
  (let* ((queue (cadar prep-phrases))
         (sublist-variable (make-symbol "QUEUE-SUBLIST"))
         (generator-bindings `((,sublist-variable (queue-head-internal ,queue))
                               (,variable nil)))
         (generator-initialize nil)
         (generator-eof-p `(null ,sublist-variable))
         (generator-advance
           `(,variable (car-of-cons ,sublist-variable)
             ,sublist-variable (cdr-of-cons ,sublist-variable))))
    `(,generator-bindings
        ,generator-initialize
        ,generator-eof-p
        nil
        nil
        ,generator-advance)))

;; Usage: (loop for e being each queue-element of queue ...)






;;;; More Loop Paths


;;; As far as I can see, loop paths can be defined anywhere between loop.lisp
;;; and the first use of the iteration path; and if it turns out they never get
;;; used, nobody minds one bit.  I am moving three iteration paths here.  I
;;; chose this file simply because it already had several loop-iteration-paths
;;; in it, and of course it is part of G2, GSI, and TW.
;;;
;;; The functions which do the actual iteration are defined elsewhere (TYPES and
;;; FRAMES2A), and are stubbed out for GSI.  The idea is not to get the
;;; functionality into GSI, but simply to allow GSI to continue successfully
;;; upon encountering the following loop-paths, and in fact to produce a Lisp
;;; binary file which is identical to the one that G2 would produce.
;;; -jv, 12/19/03


(define-loop-path (evaluation-sequence-element)
    evaluation-sequence-elements-of (of))


(define-loop-path (evaluation-structure-pair)
    evaluation-structure-pairs-of (of))


(define-loop-path (class-instances class-instance)
                   class-instances-path (of))







;;;; Stack Evaluator Bit Flags




;;; The stack evaluator needs several flags that control its behavior.  These
;;; are grouped together into a single global variable to reduce the time spent
;;; setting global variables on entry and exit from computation contexts.  These
;;; values are stored in a global variable called `current-computation-flags'.

(def-system-variable current-computation-flags utilities2 0)




;;; The macro `def-computation-flags' defines getter macros and setf methods for
;;; those setter macros which provide access to bit locations with
;;; current-computation-flags.  These accessors return T or NIL values.  This
;;; also defines macro `make-computation-flags' which is a creation function for
;;; a new binding of the computation-flags which efficiently computes a new
;;; value for the entire set of bits.

(def-global-property-name special-setf-method)

(defmacro def-computation-flags (&rest names)
  `(progn
     ,@(loop for name in names
             for local-name = (intern (format nil "~a-LOCAL" name))
             for setter = (intern (format nil "SET-~a" name))
             for bit from 0
             for mask = (ashf 1 bit)
             nconc
             `((defmacro ,name ()
                 `(/=f (logandf current-computation-flags ,',mask) 0))
               (defmacro ,local-name ()
                 `(/=f (logandf local-current-computation-flags ,',mask) 0))
               (defmacro ,setter (t-or-nil)
                 (if (constantp t-or-nil)
                     (if (eval t-or-nil)
                         `(progn
                            (setq current-computation-flags
                                  (logiorf current-computation-flags ,',mask))
                            t)
                         `(progn
                            (setq current-computation-flags
                                  (logandc2f current-computation-flags ,',mask))
                            nil))
                     `(cond (,t-or-nil
                             (setq current-computation-flags
                                  (logiorf current-computation-flags ,',mask))
                             t)
                            (t
                             (setq current-computation-flags
                                  (logandc2f current-computation-flags ,',mask))
                             nil))))
               (setf (special-setf-method ',name) ',setter)
               (defsetf ,name ,setter)))
     (defmacro make-computation-flags ,(cons '&key names)
       (let ((computed-elements nil)
             (collected-constants 0))
         ,@(loop for name in names
                 for bit from 0
                 for mask = (ashf 1 bit)
                 collect
                 `(if (constantp ,name)
                      (when (eval ,name)
                        (incf collected-constants ,mask))
                      (push `(if ,,name ,',mask 0) computed-elements)))
         (cond ((null computed-elements)
                collected-constants)
               ((null (cdr computed-elements))
                (if (zerop collected-constants)
                    (car computed-elements)
                    `(+f ,collected-constants ,(car computed-elements))))
               (t
                `(+f ,@(if (zerop collected-constants)
                           nil
                           (list collected-constants))
                     ,@(reverse computed-elements))))))))

(defmacro with-local-computation-flags (&body body)
  `(let ((local-current-computation-flags current-computation-flags))
     ,@body))

(def-computation-flags
  cache-explanation-variables?
  final-evaluation-attempt?
  force-new-request-for-value
  no-wake-ups-during-role-serving
  role-serve-inactive-objects?
  attempting-network-write-access-p
  attempting-network-read-access-p
  default-dont-compute-new-variable-values
  dont-compute-new-variable-values
  dont-forward-chain-from-rule
  within-dynamic-extent-of-traced-rule-p
  serve-only-permanent-items-p
  serve-loose-ends-p
  )

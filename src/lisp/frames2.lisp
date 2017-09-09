;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FRAMES2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; M. Levin and Gretchen Wang








;;;; Forward References




(declare-forward-references-to-module
  frames2a
  delete-frame
  well-instantiated-or-subclassed-class-p)

(declare-forward-references-to-module
  frames3
  note-change-to-block-1
  note-change-to-dependent-frame-1)

(declare-forward-references-to-module
  install
  put-attribute-description-value)

(declare-forward-references-to-module
  resources
  compiled-resource-p-function reclaim-compiled-resource-function)

(declare-forward-reference validate-item-or-evaluation-value function)

(declare-forward-reference validate-item-or-evaluation-value function)

#+development
(declare-forward-reference legal-non-copied-slot-value-p function)

(declare-forward-reference do-not-note-permanent-changes-p variable)

#+relation-instances-v2
(declare-forward-reference reclaim-relation-instances function)



;;;; Defining a G2 Class




;;; `Def-class' is a macro that defines a G2 class.  User-defined classes are
;;; defined by define-user-class.  See DEFINITIONS for documentation.  A
;;; system class definition takes the following form.

;;; (def-class (<class> [<direct superior classes> {<class feature specifier>}])
;;; {<slot definition>})

;;; (def-class (<class> [<direct superior classes> {<class-feature>}])
;;; (<pretty-slot-name> <slot-init-form> {<slot-feature>}))

;;; <class> may be any symbol except nil or root.

;;; <direct superior classes> can be a single class or a list of classes.  Each
;;; direct superior class symbol cannot be <class>, nil, or any subclass of
;;; <class>.  A set of direct superior classes will be rejected if there are two
;;; or more classes that have a differently-named slot assigned the same vector
;;; slot index.

;;; <class feature specifier> is either of the form <class feature> or (<class
;;; feature> {<class feature argument>}).

;;; <class feature> is a member of the set {define-predicate, never-a-choice,
;;; not-a-final-choice, ...}.

;;; <class feature argument> is a lisp object of some form defined to be an
;;; argument of the class feature.

;;; <slot definition> is of the form (<pretty-slot-name> <slot init form> {<slot
;;; feature specifier>}).

;;; <pretty-slot-name> is any atom.

;;; <slot init form> is one of following: datum (anything that doesn't look like
;;; a slot feature or any of the following) (:FUNCALL function .  args); or
;;; (:FUNCALL-AT-LOAD-TIME function .  args).  (As of 5/12/95, see the section
;;; entitled "Initializations on Frames Being Made" in FRAMES3 for rules about
;;; the evaluation of slot init forms.)

;;; <slot feature specifier> is either of the form <slot feature> or (<slot
;;; feature> {<slot feature argument>}).  <slot feature> is a member of the set
;;; {vector-slot, lookup-slot, ...}.  <slot feature argument> is a lisp object
;;; of some form defined to be an argument of the slot feature.  For example the
;;; slot feature descriptive-phrase has one slot feature argument, which if
;;; present must be a string.

;;; For example,

;;; (def-class (gadget (item block) define-predicate)
;;;   (gadget-renderings-for-chart nil system vector-slot)
;;;   (chart-initial-update-task?  nil system vector-slot do-not-save)
;;;   (computed-annotations nil do-not-save system))

;;; is a class definition for the class chart.  Chart will inherit any
;;; non-shadowed slots defined for its direct superior classes, item and block,
;;; or any non-shadowed slots inherited by item or block from their
;;; superclasses.  When there are two or more same-named slots defined for the
;;; classes on the class inheritance path for a particular class, the slot that
;;; is defined for a class further to the left on the class inheritance path
;;; will have precedence (or overshadow) a slot defined for a class that appears
;;; more to the right on the path.

;;; A set of direct superior classes for a system-defined class will be rejected
;;; by def-class if there are two or more direct superiors that have a slot
;;; assigned the same vector index but with different slot names.  The reason
;;; for this situation is that there is a great deal of code that depends on
;;; same-named vector slots being at the same vector index.  Making one of the
;;; conflicting slots a lookup slot can solve the conflict.

;;; The implementation of the slots defined specifically for chart will be
;;; vector slot for the first slot and lookup for the remaining two slots.
;;; Lookup is the default implementation.

;;; The class feature define predicate will cause the predicate chart-p to be
;;; defined which will return t if the frame given it is an instance of chart.

;;; During execution def-class creates a structure, called a class description,
;;; which encapsulates the information essential to the class defined.  Also
;;; defined at this time are various accessors for the slots.





;;; On the Relevance of Order in the Definition of G2 Classes.

;;; For any symbol X, one and only one of the following three statements is
;;; true.
;;;  (1) X is a class.
;;;  (2) X is a potential class.
;;;  (3) X is neither a class nor a potential class.

;;; X is a class if X is root or X has been defined with def-class and the
;;; parent of X is a class.

;;; X is a potential class if X is not the root and X has been defined by
;;; def-class and the parent of X is not a class.

;;; X is neither a class nor a potential class if X is not the root and X has
;;; not been defined by def-class.

;;; If X is not a class and we define X with def-class such that the direct
;;; superior classes of X are classes, then X will become a class.  X will
;;; inherit from its direct superior classes any slots which X itself does not
;;; possess by virtue of its own slot descriptions.  Furthermore, any potential
;;; classes which existed at the moment of the definition of X which have X as a
;;; direct superior class, and have defined classes for their remaining direct
;;; superior classes, will likewise become classes, inheriting from X and its
;;; other direct superior classes.

;;; If X is a potential class and the direct superior classes of X become
;;; classes then X too will become a class.  X will inherit from its direct
;;; superior classes as in the first example.  In like manner, any potential
;;; classes holding X as a direct superior classes, and having defined classes
;;; for their remaining direct superior classes, will be defined.

;;; If X is a class and we redefine X, then X will inherit from its direct
;;; superior classes just as in the case where X is not a class.  Furthermore,
;;; any classes which hold X as a direct superior class, and have defined
;;; classes for their remaining direct superior classes, will be redefined as
;;; was X.

;;; If X is a class and we define X with def-class such that one of the direct
;;; superior classes of X is not a class, then X will become a potential class.
;;; Futhermore, any classes holding X as a direct superior class will be
;;; redefined and thus too become potential classes.

;;; Only classes are instantiable. Thus applying make-frame to a potential class
;;; is an error.

;;; When the definition state of a class changes, the following statements about
;;; the instances of the class, if there are any, hold.

;;; (1) Any instances specific to the class endure in the same form they were in
;;; when they were instantiated with make-frame.

;;; (2) Any accessors defined for the class are redefined, if necessary, to the
;;; specifications of the new definition.

;;; (3) Accessors definitions are never retracted, only redefined.

;;; If redefinition results in relocation of vector slots, caused by a change in
;;; the length of the vector utilized in their representation, then it is often the
;;; case that the former frames will not be properly accessed by the new accessors.
;;; Adding vector slots to the end of a class with no child classes does not present
;;; this problem but it should be noted that the frames of the original definition
;;; will not have storage for these new slots. Lookup slots are immune from all
;;; of these problems and will therefore not be affected by such redefinitions provided
;;; the corresponding new slots too are lookup slots.



;;; The Effect of Class Redefinition on Frames (Instances)

;;; Redfinition of a class can be disasterrous to frames of the class and frames of
;;; subclasses of the class. If redefinition is done cautiously according to the
;;; following rules, however, its effects will be predictable and useful.

;;; Rules of redefinition for leaf classes (leaf classes are classes with no
;;; subclasses) of which frames exist:

;;; 1. Inherited vector slots must remain vector slots. Inherited lookup slots must
;;; remain lookup slots.

;;; 2. Lookup slots may be redefined and/or defined in any order and in any quantity.

;;; 3. Vector slots must be redefined in the same order in which they appeared in their
;;; original definition. Vector slots may be omitted only if all vector slots which were
;;; originally defined after them are omitted too. The consequence of this will be that
;;; existing frames of the class will be represented by vectors of length greater than
;;; newly created frames of the class but that their accessors will still be applicable.
;;; If it is likely that such redefinition will occur it might be wiser to use lookup
;;; slots.



;;; Rules of redefinition for internal classes (internal classes are not leaf classes and
;;; not the root class).

;;; 1. Same as above.

;;; 2. Same as above.

;;; 3. Addition and deletion of vector slots from internal classes is dangerous. There
;;; are many criteria to consider. If any subclass of the class has vector slots and
;;; there exist frames of the subclass then it is unsafe to change the order or the
;;; quantity of vector slots. If there are no such subclasses then redefinition can
;;; occur as described in 3 above. The only difference is that the considerations for
;;; the differences in the sizes of the vectors of the frames of the class must be
;;; propagated to its subclasses.

;;; 4. Instances of classes with :FUNCALL-AT-LOAD-TIME slot initializations of
;;;    lookup-slots which are redefined will, in certain cases, lose the values of the
;;;    slots which underwent the change because of structural assumptions made about the
;;;    lookup structure of the class.

;;; A quick note on how to do backward compatability -rdf, 2/25/94
;;;
;;; 1. the slot must still exist on the class (make it a lookup slot to save
;;; space). The slot MUST have an editable type or any references in procedures
;;; will fail. adding the feature `formerly-put-in-attribute-tables'
;;; hides the slot from the user but allows procedures to play with it
;;;
;;; 2. define a def-slot-value-writer and def-slot-putter which morph the old
;;; references to the new ones
;;;
;;; 3. Develop a way to read in old kb's which transfer values of the old slot
;;; into the new format
;;;
;;; A working example of 1 and 2 can be found for the superior-class slot of
;;; object-definition found in definitions.lisp and grammar6.lisp








;;;; Class bit numbers and class bit vectors




;;; The class bit number and the class bit vector are components, named class-
;;; bit-number and class-bit-vector, on the class- description structure
;;; of a class.  The class bit numbers start with 0 for the root class and are
;;; incremented by 1.  The system classes are not assigned class bit numbers and
;;; vectors at definition time; instead, assign-bit-numbers-and-vectors-to-
;;; classes is called from run-ab which assigns the class bit numbers and
;;; vectors starting with the root class and visiting the inferior classes of
;;; root breadth-first, visiting each class once.  The class bit vector for a
;;; class has its own bit number turned on as well as the bits corresponding to
;;; the bit numbers of its direct and indirect superior classes, up to root
;;; class.  Class bit numbers will not be reordered when there is a change in
;;; the class hierarchy.  Class bit numbers will be recycled.


(defvar last-system-class-bit-number 0)

(defvar next-class-bit-number 0)

(defun initialize-classes-visited-byte-vector ()
  (allocate-byte-vector (ceilingf-positive next-class-bit-number 8)))

(def-system-variable classes-visited-byte-vector frames2
  (:funcall initialize-classes-visited-byte-vector) nil nil
  reclaim-byte-vector t)




#+development
(defun initialize-class-bit-numbers-and-vectors-to-nil ()
  (loop for class being each unoptimized-subclass of 'root
        for class-description = (class-description class)
        do
    (when class-description
      (setf (class-bit-number class-description) nil)
      (setf (class-bit-vector class-description) nil))))




;;; `Get-next-class-bit-number' returns the next available bit number.

(defun get-next-class-bit-number ()
  (if class-bit-numbers-pool
      (frame-pop class-bit-numbers-pool) ; not thread-safe
      (prog1
        next-class-bit-number
        (atomic-incff next-class-bit-number)
        (let ((needed-length (ceilingf-positive next-class-bit-number 8)))
          (when classes-visited-byte-vector
            (unless (>=f (byte-vector-length classes-visited-byte-vector)
                         needed-length)
              (reclaim-byte-vector classes-visited-byte-vector)
              (setq classes-visited-byte-vector nil)))
          (unless classes-visited-byte-vector
            (setq classes-visited-byte-vector
                  (allocate-byte-vector needed-length)))))))





;;; `Assign-class-bit-numbers-and-vectors-to-system-classes' assigns class bit
;;; numbers and class bit vectors to the G2 classes from run-ab.  It assigns the
;;; class bit numbers breadth-first, incrementing by one, starting with 0 for
;;; root.

(defun assign-class-bit-numbers-and-vectors-to-system-classes ()
  (let ((current-class-bit-number 0))
    (when class-bit-numbers-pool
      (reclaim-frame-list class-bit-numbers-pool)
      (setq class-bit-numbers-pool nil))

    (loop for class being each unoptimized-subclass of 'root
          do
      (setf (class-bit-number (class-description class))
            current-class-bit-number)
      (setq current-class-bit-number (1+f current-class-bit-number)))

    (setq next-class-bit-number current-class-bit-number)
    (setq last-system-class-bit-number (1-f current-class-bit-number))

    (loop for class being each unoptimized-subclass of 'root
          for class-description = (class-description class)
          do
      (setf (class-bit-vector class-description)
            (make-class-bit-vector
              (class-bit-number class-description)
              (class-inheritance-path class-description))))))




;;; `Make-class-bit-vector' allocates a byte vector and turns on the
;;; bits corresponding to the class bit number and the class bit numbers
;;; of all of its superior classes up to root.

(defun make-class-bit-vector (class-bit-number class-inheritance-path)
  (let* ((superior-classes (cdr class-inheritance-path))
         (vector-index-for-class (byte-vector-index class-bit-number))
         (required-bytes-for-vector
           (loop with number-of-bytes = (1+f vector-index-for-class)
                 for superior-class in superior-classes
                 for length-needed-for-superior-bit =
                     (1+f (byte-vector-index
                            (class-bit-number
                              (class-description superior-class))))
                 do
             (setq number-of-bytes
                   (maxf number-of-bytes
                         length-needed-for-superior-bit))
                 finally (return number-of-bytes)))
         (class-bit-vector
           (allocate-byte-vector required-bytes-for-vector)))
    (loop for index from (1-f (byte-vector-length class-bit-vector)) downto 0
          do
      (setf (byte-vector-aref class-bit-vector index) 0))
    (setf (byte-vector-aref class-bit-vector vector-index-for-class)
          (logior
            (byte-vector-aref class-bit-vector vector-index-for-class)
            (byte-mask-for-bit class-bit-number)))
    (loop for superior-class in superior-classes
          for superior-class-bit-number =
                (class-bit-number (class-description superior-class))
          for vector-index-for-superior =
                (byte-vector-index superior-class-bit-number)
          do
      (setf (byte-vector-aref class-bit-vector vector-index-for-superior)
            (logior
              (byte-vector-aref class-bit-vector vector-index-for-superior)
              (byte-mask-for-bit superior-class-bit-number))))
    class-bit-vector))







;;;; Subclasses and superclasses iteration path




;;; The `subclasses interation path', given a class, performs a breadth first
;;; traversal of the class-subclass hierarchy beneath and including the class
;;; itself, visiting each class once.  An example of this iteration path is:

;;; (loop for class being each subclass of 'block doing (print class)).

;;; In this case block will be printed followed by each of its children and then
;;; each of their children and so on.

;;; The `superclasses interation path', given a class, performs a breadth
;;; first traversal of the superclasses of class, visiting each class once.  Class
;;; is not a superclass of class.  Example:

;;; (loop for class being each superclass of 'variable collect class).

(defun-for-macro sub-or-superclasses-path
    (path-name variable data-type prep-phrases
               inclusive? allowed-prepositions data)

  (let ((list-of-classes (loop-gentemp))
        (argument-class (loop-gentemp)))

    ;; unused variables
    data-type data allowed-prepositions

    (unless prep-phrases
      (error "OF is missing in ~S iteration path of ~S" path-name variable))

    (when inclusive?
      (error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
             path-name variable prep-phrases))

    #+development
    (test-assertion
      (member path-name
              '(subclass subclasses superclasses superclass)))

    (list
      ;; bindings
      `((scope-conses scope-conses)
        (,list-of-classes nil)
        (,argument-class ,(second (assq 'of prep-phrases)))
        (,variable nil))
      ;; prologue
      `((setq ,list-of-classes
              ,(case path-name
                 ((subclass subclasses)
                  `(collect-subclasses ,argument-class))
                 ((superclass superclasses)
                  `(collect-superclasses ,argument-class))
                 (t nil))))
      ;; end test
      `(null ,list-of-classes)
      ;; steps
      nil
      ;; post step endtest
      nil
      ;; pseudo steps
      `(,variable
          (prog1 (car-of-cons ,list-of-classes)
            (setq ,list-of-classes (cdr-of-cons ,list-of-classes)))))))




(define-loop-path (subclasses subclass superclasses superclass)
                  sub-or-superclasses-path (of))




(def-substitution-macro class-not-visited-for-loop-path (class)
  (let* ((class-bit-number (class-bit-number (class-description class)))
         (class-byte-vector-index (byte-vector-index class-bit-number))
         (class-visited-byte
           (byte-vector-aref
             classes-visited-byte-vector class-byte-vector-index))
         (class-byte-mask
           (byte-mask-for-bit class-bit-number)))
    (=f (logandf class-visited-byte class-byte-mask) 0)))




;;; The function `collect-subclasses' produces the scope-cons subclass list
;;; for the sub-or-superclasses-path loop.

(defun-simple collect-subclasses (subclasses-path-argument)
  (let ((class-description? (class-description subclasses-path-argument)))
    (when class-description?
      (loop for index from 0
                      below (ceilingf-positive next-class-bit-number 8)
            do
        (setf (byte-vector-aref classes-visited-byte-vector index) 0))
      (let* ((classes (scope-list subclasses-path-argument))
             (classes-tail-pointer classes)
             (class-bit-number (class-bit-number class-description?)))
        (setf (byte-vector-aref
                classes-visited-byte-vector (byte-vector-index class-bit-number))
              (byte-mask-for-bit class-bit-number))
        (loop for subclasses-traversal-pointer
                  = classes
                  then (cdr-of-cons subclasses-traversal-pointer)
              while subclasses-traversal-pointer
              for superior-class = (car-of-cons subclasses-traversal-pointer)
              do
          (loop for class in (inferior-classes superior-class)
                do
            ;; The unless form delays the collection of a class until its
            ;; superiors are collected.
            (unless (loop for superior in (direct-superior-classes class)
                          thereis
                          (and (subclassp superior subclasses-path-argument)
                               (class-not-visited-for-loop-path superior)))
              (let* ((class-bit-number
                       (class-bit-number (class-description class)))
                     (byte-vector-index
                       (byte-vector-index class-bit-number))
                     (visited-byte
                       (byte-vector-aref
                         classes-visited-byte-vector byte-vector-index))
                     (byte-mask (byte-mask-for-bit class-bit-number)))
                (when (=f (logandf visited-byte byte-mask) 0)
                  (setf (byte-vector-aref
                          classes-visited-byte-vector byte-vector-index)
                        (logiorf visited-byte byte-mask))
                  (let ((new-class-cons (scope-list class)))
                    (setf (cdr classes-tail-pointer) new-class-cons)
                    (setq classes-tail-pointer new-class-cons)))))))
        classes))))




;;; The function `collect-superclasses' produces the scope-cons superclass list
;;; for the sub-or-superclasses-path loop.

(defun-simple collect-superclasses (superclasses-path-argument)
  (when (classp superclasses-path-argument)
    (loop for index from 0
                    below (ceilingf-positive next-class-bit-number 8)
          do
      (setf (byte-vector-aref classes-visited-byte-vector index) 0))
    (loop with classes = (frame-list superclasses-path-argument)
          with classes-tail-pointer = classes
          for classes-traversal-pointer
              = classes
              then (cdr-of-cons classes-traversal-pointer)
          while classes-traversal-pointer
          for subclass = (car-of-cons classes-traversal-pointer)
          do
      (loop for superior-class in (direct-superior-classes subclass)
            do
        ;; The unless form delays the collection of a class until its
        ;; inferiors are collected.
        (unless (loop for inferior in (inferior-classes superior-class)
                      thereis
                      (and (neq superclasses-path-argument inferior)
                           (class-not-visited-for-loop-path inferior)))
          (let* ((class-bit-number (class-bit-number (class-description superior-class)))
                 (byte-vector-index (byte-vector-index class-bit-number))
                 (visited-byte
                   (byte-vector-aref classes-visited-byte-vector byte-vector-index))
                 (byte-mask (byte-mask-for-bit class-bit-number)))
            (when (=f (logandf visited-byte byte-mask) 0)
              (setf (byte-vector-aref
                      classes-visited-byte-vector byte-vector-index)
                    (logiorf visited-byte byte-mask))
              (let ((new-class-cons (scope-list superior-class)))
                (setf (cdr classes-tail-pointer) new-class-cons)
                (setq classes-tail-pointer new-class-cons))))))
          finally
            (progn
              (reclaim-frame-cons
                (prog1 classes (setq classes (cdr classes))))
              (return classes)))))




;;; `Make-slot-descriptions-hash-table' returns two values, a hash table and a
;;; class symbol, which become the values of the slot-descriptions-hash-table
;;; and full-hash-table-class components of the class-description for class.

;;; This function returns a full hash table when the class argument is block or
;;; when the class has more than five instances or has more than three inferior
;;; classes and that have class as their sole direct-superior class; otherwise
;;; it returns a parse hash table.  Define-root-class calls
;;; make-full-slot-descriptions-hash-table directly.

;;; In the process of determining the full-hash-table-class for class, a superior
;;; of class may have its hash table changed from sparse to full.  This happens
;;; when the class inheritance path of a superior equals the tail of the
;;; class-inheritance-path for class and one of these conditions holds true: the
;;; superior and the class are separated by more than two classes on the
;;; class inheritance path for class, the superior has more than five
;;; instances, or the superior has more than three inferior-classes that have
;;; the superior as their sole direct-superior class.

;;; When a superior hash table is upgraded, subclasses of the superior are
;;; checked to see if superior is a more specific full-hash-table class than
;;; its current full-hash-table class; if it is, the change is made.

;;; This function is called when a class is being defined or when the inheritance
;;; of a defined class is changing.

(defun make-slot-descriptions-hash-table
    (class class-slot-descriptions class-inheritance-path
           direct-superior-classes user-defined-class?)
  ;; Root, kb-frame, and block are special-cased because their definition
  ;; occurs before the loop paths are defined.
  (let ((class-is-defined? (classp class)))
    (cond ((or (eq class 'root) (eq class 'block))
           (values (make-full-slot-descriptions-hash-table
                     class-slot-descriptions class-inheritance-path)
                   class))
          ((eq class 'kb-frame)
           (values (make-sparse-slot-descriptions-hash-table
                     class class-slot-descriptions class-inheritance-path)
                   'root))
          ((and user-defined-class?
                class-is-defined?
                (well-instantiated-or-subclassed-class-p class))
           (values (make-full-slot-descriptions-hash-table
                     class-slot-descriptions class-inheritance-path)
                   class))
          (t
           (let ((full-hash-table-class nil)
                 (upgraded-superiors-list nil))
             (loop for class-cons on (cdr class-inheritance-path)
                   for superior-class = (car-of-cons class-cons)
                   for superior-class-description = (class-description
                                                      superior-class)
                   for superior-has-full-hash-table? =
                   (class-description-has-full-hash-table-p
                     superior-class-description)
                   do
               ;; Determining whether a direct-superior class should have a full
               ;; hash table is of more benefit when loading a kb or changing
               ;; class inheritance than during class hierarchy development when
               ;; superior classes will probably not yet have their full
               ;; complement of instances and inferior classes.
               (when (and (memq superior-class direct-superior-classes)
                          (not superior-has-full-hash-table?)
                          (well-instantiated-or-subclassed-class-p superior-class))
                 (frame-push superior-class upgraded-superiors-list)
                 (reclaim-slot-hash
                   (slot-descriptions-hash-table superior-class-description))
                 (setf (slot-descriptions-hash-table superior-class-description)
                       (make-full-slot-descriptions-hash-table
                         (slot-descriptions superior-class-description)
                         (class-inheritance-path superior-class-description)))
                 (setf (full-hash-table-class superior-class-description)
                       superior-class))

               (when (equal class-cons
                            (class-inheritance-path superior-class-description))
                 ;; The superior-class is an inheritance merging point for class.
                 (cond (superior-has-full-hash-table?
                        (setq full-hash-table-class superior-class)
                        (loop-finish))
                       ((superior-is-well-spaced-for-full-hash-table-p
                          superior-class class-inheritance-path)
                        (frame-push superior-class upgraded-superiors-list)
                        (reclaim-slot-hash
                          (slot-descriptions-hash-table superior-class-description))
                        (setf (slot-descriptions-hash-table superior-class-description)
                              (make-full-slot-descriptions-hash-table
                                (slot-descriptions superior-class-description)
                                (class-inheritance-path superior-class-description)))
                        (setf (full-hash-table-class superior-class-description)
                              superior-class)
                        (setq full-hash-table-class superior-class)
                        (loop-finish))
                       (t nil))))

             ;; For subclasses of upgraded superiors, set the class full-hash
             ;; table-class to the upgraded superior if the upgraded superior is
             ;; more specific to class than its current full-hash-table-class
             ;; and the upgraded superior is an inheritance merging point.
             (loop for superior in upgraded-superiors-list
                   do
               (if user-defined-class?
                   (loop for subclass being each subclass of superior
                         do
                     (let* ((subclass-class-description
                              (class-description subclass))
                            (subclass-full-hash-table-class
                              (full-hash-table-class subclass-class-description))
                            (subclass-inheritance-path
                              (class-inheritance-path subclass-class-description)))
                       (when (and (equal (memq superior subclass-inheritance-path)
                                         (class-inheritance-path
                                           (class-description superior)))
                                  (<f (position superior subclass-inheritance-path)
                                      (position subclass-full-hash-table-class
                                                subclass-inheritance-path)))
                         (setf (full-hash-table-class subclass-class-description)
                               superior))))
                   (loop for subclass being each unoptimized-subclass of superior
                         do
                     (let* ((subclass-class-description
                              (class-description subclass))
                            (subclass-full-hash-table-class
                              (full-hash-table-class subclass-class-description))
                            (subclass-inheritance-path
                              (class-inheritance-path subclass-class-description)))
                       (when (and (equal (memq superior subclass-inheritance-path)
                                         (class-inheritance-path
                                           (class-description superior)))
                                  (<f (position superior subclass-inheritance-path)
                                      (position subclass-full-hash-table-class
                                                subclass-inheritance-path)))
                         (setf (full-hash-table-class subclass-class-description)
                               superior))))))

             (reclaim-frame-list upgraded-superiors-list)

             (values (make-sparse-slot-descriptions-hash-table
                       class class-slot-descriptions class-inheritance-path)
                     full-hash-table-class))))))




;;; `Make-class-inheritance-path-for-system-defined-class' is the system-class
;;; equivalent of make-class-inheritance-path-for-user-defined-class.  It
;;; does not trouble itself memory reclamation except for the temporary consing
;;; of the list-of-common-ancestors.

(defun make-class-inheritance-path-for-system-defined-class
       (class-being-defined direct-superior-classes)
  (loop with path =
               (copy-list
                 (class-inheritance-path
                   (class-description (car direct-superior-classes))))
        with merging-path = nil
        for superior-class in (cdr direct-superior-classes)
        for superior-path =
              (copy-list
                (class-inheritance-path (class-description superior-class)))
        do
    (loop with list-of-common-ancestors =
                 (loop for class in superior-path
                       when (memq class path)
                         collect class using frame-cons)
          for common-ancestor in list-of-common-ancestors
          do
      (setq merging-path
            (nconc
              merging-path
              (loop for class in path
                    until (eq class common-ancestor)
                    collect class
                    do
                (pop path))
              (loop for class in superior-path
                    until (eq class common-ancestor)
                    collect class
                    do
                (pop superior-path))
              (list common-ancestor)))

      (pop path)
      (pop superior-path)
          finally (reclaim-frame-list list-of-common-ancestors))
    (setq path nil)
    (setq path merging-path)
    (setq merging-path nil)
        finally (return (cons class-being-defined path))))




;;; `Def-class' defines a g2-class.  Documentation for G2-class definition
;;; appears at the beginning of this file.

#+meter-init-memory
(defparameter class-memory 0)

#+meter-init-memory
(defparameter before-class-init 0)

(defmacro def-class
    ((class . parent-class-and-class-features?)        ; changed by LH for GCLISP
     &body slot-definitions)
  (clear-all-evaluator-slot-info)
  (if (eq class 'root)
      (error
        "Def-class is not permitted to redefine the root class.~%~
         See define-root-class.")
      (let ((direct-superior-classes (car parent-class-and-class-features?)))
        `(progn
           #+meter-init-memory
           (setq before-class-init (g2-memory-usage))
           #+development (register-definition ',class 'class)
           ,(expand-class-definition
              class
              (if (atom direct-superior-classes)
                  (list direct-superior-classes)
                  direct-superior-classes)
              (cdr parent-class-and-class-features?)
              slot-definitions
              nil)
           #+meter-init-memory
           (setq class-memory
                 (+f (-f (g2-memory-usage) before-class-init)))))))

#+(and lispworks development)
(lw:defadvice (def-class def-class-record-definition :around)
    (call environment)
  (let ((class-name (car-or-atom (second call))))
    (cond
      (class-name
       `(dspec:def (def-class ,class-name)
            (progn
              (dspec::record-definition `(def-class ,',class-name)
                                        (dspec:location))
              ,(lw:call-next-advice call environment))))
      (t
       (lw:call-next-advice call environment)))))


;;; `Redef-class' is not intended for use outside of expand-class-definition. Save for the
;;; last parameter it hands expand-class-definition, it is exactly the same as def-class.
;;; Redef-class causes expand-class-definition to distinguish between a class defined
;;; explicitly by the user and one defined implicitly by the definition or redefinition
;;; of a class. This distinction is necessary for the avoidance of redundant and
;;; unintentional redefinition of classes in the expansion of def-class while compiling.

(defmacro redef-class
          ((class . parent-class-and-class-features?)        ; changed by LH for GCLISP
           &body slot-definitions)
  (if (eq class 'root)
      (error
        "Def-class is not permitted to redefine the root class.~%~
         See define-root-class.")
      (expand-class-definition
        class
        (car parent-class-and-class-features?)
        (cdr parent-class-and-class-features?)
        slot-definitions
        t)))



#+development
(defun-simple describe-this-class-feature-in-system-defined-classes
    (feature-name)
  (loop for class being each subclass of 'root
        for feature-with-name? =
              (when (system-defined-class-p class)
                (get-class-feature-if-any class feature-name))
        do
    (when feature-with-name?
      (format t "~%~A --> ~a" class feature-with-name?))))





;;; `Slot-description-is-of-savable-slot-p' is true if the slot described by slot-
;;; description is `savable', in that (a) it has a type feature but no
;;; do-not-save feature or (b) it has a save feature.  Note that block edge,
;;; superblock?, subblocks, and class slots are not "savable".

(defmacro slot-description-is-of-savable-slot-p (slot-description)
  `(let ((slot-features (slot-features ,slot-description)))
     (if (feature-assq 'type slot-features)
         (not (feature-assq 'do-not-save slot-features))
         (feature-assq 'save slot-features))))

(def-substitution-macro slot-description-is-noteworthy (slot-description)
  (or (slot-description-is-of-savable-slot-p slot-description)
      (feature-assq 'note-slot-changes (slot-features slot-description))))




;;; `Classes-intersect-p' returns t if the two symbol arguments are defined
;;; classes and have a subclass in common.

(defun classes-intersect-p (symbol-1 symbol-2)
  (and (classp symbol-1) (classp symbol-2)
       (loop for symbol-1-subclasses =
                   (loop for class being each subclass of symbol-1
                         collect class using frame-cons)
             for symbol-2-subclass being each subclass of symbol-2
             do
         (when (memq symbol-2-subclass symbol-1-subclasses)
           (reclaim-frame-list symbol-1-subclasses)
           (return t))
             finally
               (reclaim-frame-list symbol-1-subclasses)
               (return nil))))




;;; `noting-changes-to-kb-p' is the global determinent as to whether changes
;;; have to be noted for backup and journalling. It is a fast test to avoid
;;; penalty when these facilities are not being used. Its value is true if (1)
;;; backup and journalling is enabled, or (2) saving is in progress. However the
;;; value must be nil during read-kb. The value is set to the value of
;;; (enable-journalling journal-and-backup-parameters) whenever this slot is
;;; edited. It is set to nil during switch-to-new-empty-kb. It is set t at the
;;; beginning of a save, backup or journal, and is reset after the completion of
;;; the same to the value of (enable-journalling journal-and-backup-parameters).
;;; After read-kb has completed, it is also set to this value.



(def-system-variable noting-changes-to-kb-p frames2 nil nil t)


;;; `Current-block-of-dependent-frame' is bound dynamically, whenever modifications
;;; to the slots of a dependent frame are in progress, to provide a path from
;;; the frame to its enclosing block for the journalling/backup mechanisms.
;;; The type of this variable is
;;;   (or (member nil dependent-frame-has-no-owner)
;;;       block)
;;; It is an error to modify a slot of a dependent frame when it is bound to NIL.

;;; Access to dependent frames by pointers from blocks other than their owners
;;; must not modify the savable slots of those frames without appropriately
;;; rebinding this variable.

(def-system-variable current-block-of-dependent-frame frames2 nil nil t)

(defun error-message-for-dependent-frame-saving (frame)
  #-development (declare (ignore frame))
  #+development
  (cerror "continue" "Setting a savable slot of dependent frame ~a without a current block."
          frame))


(defmacro note-change-to-block (block pretty-slot-name?)
  `(when noting-changes-to-kb-p
     (note-change-to-block-1 ,block ,pretty-slot-name?)))


(defmacro note-change-to-dependent-frame ()
  '(when noting-changes-to-kb-p (note-change-to-dependent-frame-1)))





;;; `System-vector-slots-in-conflict' determines whether there are at least two
;;; slots in the slot-description pool of a set of direct superior system
;;; classes that have the same vector slot index but have different slot names.
;;; It returns a two-element list of the names of the first conflicting slot
;;; descriptions it finds.  If there are no conflicts, it returns nil.

(defun system-vector-slots-in-conflict (direct-superior-classes)
  (if (=f (length direct-superior-classes) 1)
      nil
      (let ((slot-names-in-conflict? nil)
            (longest-class-vector-length
              (class-vector-length
                (class-description (first direct-superior-classes))))
            (class-with-longest-vector (first direct-superior-classes)))
        (loop for superior in (cdr direct-superior-classes)
              do
          (when (>f (class-vector-length (class-description superior))
                    longest-class-vector-length)
            (setq longest-class-vector-length
                  (class-vector-length (class-description superior)))
            (setq class-with-longest-vector superior)))
        (loop with maximum-slot-descriptions
                = (slot-descriptions
                    (class-description class-with-longest-vector))
              for superior in direct-superior-classes
              until slot-names-in-conflict?
              for comparison-class-description = (class-description superior)
              do
          (unless (eq class-with-longest-vector superior)
            (loop for slot-description in maximum-slot-descriptions
                  for vector-slot-index? =
                      (vector-slot-index? slot-description)
                  for comparison-slot-description? =
                        (if vector-slot-index?
                            (loop for slot-description
                                      in (slot-descriptions
                                           comparison-class-description)
                                  do
                              (when (eq (vector-slot-index? slot-description)
                                        vector-slot-index?)
                                (return slot-description)))
                            nil)
                  do
              (when (and comparison-slot-description?
                         (not (eq (pretty-slot-name slot-description)
                                  (pretty-slot-name comparison-slot-description?))))
                (return (setq slot-names-in-conflict?
                              (list (pretty-slot-name slot-description)
                                    (pretty-slot-name
                                      comparison-slot-description?))))))))
        slot-names-in-conflict?)))




;;; `Expand-class-definition' is the function which computes the expansions of def-class
;;; and redef-class. It is intended for use by these macros alone. Included within the
;;; expansion of any class are the predicate to test an instance for membership in the
;;; class if it was called for, the accessors to any slots of the class which are not
;;; already defined to meet the needs of the class definition if there is not a current
;;; KB, and the redefinitions of any classes which inherit from the class if such classes
;;; exist. The redefinitions are always evaluated while compiling and evaluating the
;;; expansion but are evaluated during loading only when the class is being redefined and
;;; the redefinition was not caused by a redefinition of the parent.

;; Expand-class-definition is not called for user-defined classes.
;; It is not necessary to give a defining class argument to get-slot-value
;; and get-slot-description-of-class-description.
;; Define-user-class calls add-class-to-environment directly.  (4/12/93 ghw)

(defun-for-macro expand-class-definition
    (class direct-superior-classes? class-features slot-definitions redef-class-p)

  (setq direct-superior-classes?
        (if (atom direct-superior-classes?)
            (list direct-superior-classes?)
            direct-superior-classes?))
  ;; Check for errors in class name, features, and direct superior classes.

  (when (or (null class) (not (symbolp class)))
    (error "~S is an invalid class name." class))

  (loop with item-class? = (or (eq class 'item)
                               (loop for superior in direct-superior-classes?
                                  thereis (memq 'item (class-inheritance-path
                                                       (class-description
                                                        superior)))))
     for class-feature in class-features
     do
     (cond ((or (and (atom class-feature)
                     (not (memq class-feature global-class-features)))
                (and (consp class-feature)
                     (not (memq (car class-feature) global-class-features))))
            (error
             "~S, a class-feature of ~A, is not on the global-class-features list."
             (if (consp class-feature) (car class-feature) class-feature) class))
           ((and (not item-class?)
                 (or (case class-feature
                       (not-user-instantiable t)
                       (do-not-put-in-menus t)
                       (not-solely-instantiable t)
                       (t (and (consp class-feature)
                               (case (car class-feature)
                                 (foundation-class t)
                                 (disjoint-from t)
                                 (only-compatible-with t)
                                 (t nil)))))))
            (error
             "~S, a class-feature of ~A, is not appropriate for a non-item class."
             (if (consp class-feature) (car class-feature) class-feature) class))
           ((and (eq class-feature 'not-solely-instantiable)
                 (not (loop for class-feature in class-features
                         thereis (and (consp class-feature)
                                      (eq (car class-feature)
                                          'foundation-class)))))
            (error
             "~A has a not-solely-instantiable class-feature but no foundation-class ~
             class-feature." class))
           ((and (eq class-feature 'not-solely-instantiable)
                 (not (memq 'not-user-instantiable class-features)))
            (error
             "~A has a not-solely-instantiable class-feature but no not-user-instantiable ~
              class-feature." class))
           (t nil)))

  (loop for direct-superior in direct-superior-classes?
     do
     (when (not (symbolp direct-superior))
       (error "~S is an invalid class name." direct-superior))

     (when (eq class direct-superior)
       (error "~S has ~A as a direct superior class." class direct-superior))
     (loop for superior being each unoptimized-superclass of direct-superior
        do
        (when (eq class superior)
          (error "~S has ~A as a indirect superior class." class superior))))

  ;; If a class is qualified for definition, slot definition error checking
  ;; is done as slot definitions are compiled into slot descriptions. If a
  ;; class is to be simply a potential class then its slot definitions are
  ;; checked all at once to prevent erroneous potential classes from bearing
  ;; their ugly heads during run time.

  (with-permanent-allocation
    (let* ((class-definition
            `(redef-class (,class ,direct-superior-classes? ,@class-features)
               ,@slot-definitions))
           (normalized-class-features
            (normalize-features class-features))
           (unchanged-class-definition-p
            (equal class-definition (class-definition class)))
           (previous-direct-superior-classes?
            (direct-superior-classes class))
           (direct-superior-classes
            (or direct-superior-classes? '(root)))
           ;; If redefinitionp, inferior classes are used to redefine the
           ;; classes which inherit from class.
           (a-priori-inferior-classes (inferior-classes class))
           ;; If the class has a definition or children, it is being redefined.
           (redefinitionp
            (or (class-definition class) a-priori-inferior-classes))
           (undefined-direct-superior-classes
            (loop for superior in direct-superior-classes
               when (not (classp superior))
               collect superior)))

      (if undefined-direct-superior-classes
          ;; One or more direct superior classes do not have a class description.
          (if (or (not redef-class-p)
                  (loop for superior in undefined-direct-superior-classes
                     thereis (eq (definition-state superior)
                                 'being-redefined))
                  (not unchanged-class-definition-p))
              ;; Is there need for redefinition?
              (progn
                (unless *there-is-a-current-kb?*
                  ;; Unless there is a current kb, warn that the class
                  ;; exists only potentially.
                  (error "These direct superior classes, ~A, are undefined.~%~
                          Classes defined outside of knowledge bases are expected to be~%~
                          defined only after the definition of their superior classes."
                         undefined-direct-superior-classes))

                ;; Check slot definitions for validity.
                (loop for definition in slot-definitions
                   do (cond
                        ((null definition) (warn-of-invalid-slot-name nil))
                        ((consp definition)
                         (cond
                           ((or (null (slot-name-given-slot-definition definition))
                                (not
                                 (symbolp
                                  (slot-name-given-slot-definition definition))))
                            (warn-of-invalid-slot-name
                             (slot-name-given-slot-definition definition)))
                           ((null (cdr definition)) nil)
                           ((not (consp (cdr definition)))
                            (warn-of-invalid-slot-definition definition))
                           (t (error-check-slot-features
                               (slot-features-given-slot-definition definition)))))
                        ((not (symbolp definition))
                         (warn-of-invalid-slot-definition definition))))
                (unless (equal previous-direct-superior-classes?
                               direct-superior-classes)
                  ;; When there are previous direct superiors that are not on
                  ;; the list of current direct superiors, remove class from the
                  ;; inferior-classes property of the previous direct superior.
                  (loop for previous-superior in previous-direct-superior-classes?
                     do
                     (when (not (memq previous-superior direct-superior-classes))
                       (setf (inferior-classes previous-superior)
                             (delete class (inferior-classes previous-superior)))))
                  ;; Inform the new direct superiors of the class' inferiority.
                  (loop for superior in direct-superior-classes
                     do
                     (when (not (memq superior previous-direct-superior-classes?))
                       (setf (inferior-classes superior)
                             (nconc (inferior-classes superior) (list class))))))
                (setf (class-description class) nil) ; Not a definable class!
                (setf (class-definition class) class-definition)
                (setf (direct-superior-classes class) direct-superior-classes)
                ;; If this point is reached, the following form (upon evaluation),
                ;; is returned as the expansion for def-class. This form is for
                ;; the case that no class could be defined but the information vital
                ;; to a future definition, if ever possible, is hereby arranged to
                ;; make such a definition possible.
                `(eval-when (:compile-toplevel :load-toplevel :execute)
                   ,@(unless (equal previous-direct-superior-classes?
                                    direct-superior-classes)
                             `((loop for previous-superior in ',previous-direct-superior-classes?
                                  do
                                  (when (not (memq previous-superior ',direct-superior-classes))
                                    (setf (inferior-classes previous-superior)
                                          (delete ',class (inferior-classes previous-superior)))))
                               (setf (direct-superior-classes ',class) ',direct-superior-classes)
                               (loop for superior in ',direct-superior-classes
                                  do
                                  (when (not (memq ',class (inferior-classes superior)))
                                    (setf (inferior-classes superior)
                                          (nconc (inferior-classes superior)
                                                 (list ',class)))))))
                   ,@(when redefinitionp
                           (if (not (equal previous-direct-superior-classes?
                                           direct-superior-classes))
                               `((progn
                                   (loop for previous-superior
                                      in ',previous-direct-superior-classes?
                                      do
                                      (when (not (memq previous-superior ',direct-superior-classes))
                                        (unpropagate-methods previous-superior ',class)))
                                   (loop for superior in ',direct-superior-classes?
                                      do
                                      (when (not (memq superior ',previous-direct-superior-classes?))
                                        (propagate-methods superior ',class)))))
                               `((loop for superior in ',direct-superior-classes
                                    do
                                    (copy-methods superior ',class)))))

                   ;; Use new method of method propagation in the
                   ;; immediately preceeding code!
                   ;; On second thought, one cannot. The new method assumes that the
                   ;; children of the class being defined will be redefined. This
                   ;; assumption does not hold when the class being defined has no
                   ;; parent. In such a case a potential class may never become
                   ;; an actual class! SD 4/29/1987
                   (setf (class-description ',class) nil)
                   (setf (class-definition ',class) ',class-definition)
                   ;; Consider checking against wasteful redefinition as below.
                   (setf (definition-state ',class) 'being-redefined)
                   ,@(and redefinitionp
                          (loop for inferior-class in a-priori-inferior-classes
                             collecting (class-definition inferior-class)))
                   (setf (definition-state ',class) 'defined)
                   ',class))
              ;; No need for redefinition.
              class)
          ;; The direct superior classes have been defined
          (if (or (not redef-class-p)
                  (if (not (member :no-macros *features*)) ; seems needed only for Coral?
                      (or (loop for superior in direct-superior-classes
                             thereis
                             (eq (definition-state superior)
                                 'being-redefined))
                          ;; Are any direct superiors being redefined?
                          (not unchanged-class-definition-p)
                          ;; Has the class definition changed?
                          (and (not *there-is-a-current-kb?*)
                               (loop for slot-definition in slot-definitions
                                  thereis (null
                                           (fboundp
                                            (slot-name-given-slot-definition
                                             slot-definition))))))))
              ;; Are any of the slots not defined?

              ;; The above condition is to protect against redundant definition.
              ;; This is important because redefinition under some frequent conditions
              ;; can be combinatorially explosive. Consider the case of recompiling a
              ;; file of class definitions which are defined such that no definition
              ;; preceeds the definition of its parent. In such a case each definition
              ;; would redefine each of its children, who would in turn do the same.
              ;; All this and worse! For the process would begin again with the
              ;; redefinition of each upon evaluation at the top level. The method of
              ;; protecting against such a case is to define a class only when;
              ;; (1) Its definition has changed, or
              ;; (2) Its parent is in the process of being redefined, or
              ;; (3) Some one of its slots needs redefinition.
              ;; The last case may seem unnecessary but consider the consequences
              ;; of macroexpanding a class definition. During the expansion the class's
              ;; definition is stored. If subsequently the definition was evaluated
              ;; instead of macroexpanded, it would appear that the definition was a
              ;; redundant definition it would be avoided.

              ;; There is need for redefinition.
              (let* ((slot-conflict?
                      (system-vector-slots-in-conflict direct-superior-classes)))
                (if slot-conflict?
                    (let ((first-slot-name (first slot-conflict?))
                          (second-slot-name (second slot-conflict?)))
                      (error "At least two inheritable slot descriptions for ~S,~%~
                                 ~A and ~A, share the same slot vector index."
                             class first-slot-name second-slot-name))
                    (let* ((subclass-of-block-p ; system-item, really
                            (or (eq class 'system-item)
                                (loop for superior in direct-superior-classes
                                   thereis (memq 'system-item
                                                 (class-inheritance-path
                                                  (class-description
                                                   superior))))))
                           (dependent-frame-p
                            (or (eq class 'dependent-frame)
                                (loop for superior in direct-superior-classes
                                   thereis (memq 'dependent-frame
                                                 (class-inheritance-path
                                                  (class-description
                                                   superior))))))
                           (local-slot-descriptions
                            (loop for slot-definition in slot-definitions
                               collecting
                               (make-slot-description-with-error-checking
                                class slot-definition nil direct-superior-classes))))
                      (setf (definition-state class) 'being-redefined)
                      (add-class-to-environment
                       class direct-superior-classes nil
                       normalized-class-features nil local-slot-descriptions
                       previous-direct-superior-classes?
                       class-definition nil)

                      ;; Given that expand-class-definition has not yet exited,
                      ;; the following form (upon evaluation), is returned as the
                      ;; expansion for def-class. This case is the normal case,
                      ;; in which it is possible for the class to be defined.

                      `(eval-when (:compile-toplevel :load-toplevel :execute)
                         (check-if-superior-classes-are-defined
                          ',class ',direct-superior-classes)
                         (add-class-to-environment
                          ',class ',direct-superior-classes nil
                          (optimize-constant ',normalized-class-features)
                          nil
                          (optimize-constant ',local-slot-descriptions)
                          ',previous-direct-superior-classes?
                          (optimize-constant ',class-definition)
                          nil)
                         ,@(when (assq class class-description-variable-alist)
                                 `((setq ,(cdr (assq class class-description-variable-alist))
                                         (class-description ',class))))
                         ;; Unless there is a current knowledge base or there is a
                         ;; 'no-accessors' feature present in the class features list,
                         ;; define an accessor for each slot which has no 'no-accessor'
                         ;; feature.
                         ,@(unless *there-is-a-current-kb?*
                                   `((eval-when
                                         ,(if redef-class-p
                                              '(:compile-toplevel :execute)
                                              '(:compile-toplevel :load-toplevel :execute))
                                       ;; If this definition has a 'define-predicate' feature
                                       ;; and there is not a current knowledge base, create
                                       ;; a definition for such a predicate.
                                       ,@(and
                                          (feature-assq 'define-predicate normalized-class-features)
                                          `((defmacro ,(intern (format nil "~A-P" class)) (frame)
                                              (list 'frame-of-class-p frame '',class))))
                                       ,@(loop with class-description = (class-description class)
                                            for unique-slot-name in (slots-local-to-class class-description)
                                            for slot-description =
                                            (get-slot-description-of-class-description
                                             unique-slot-name class-description)
                                            for pretty-slot-name = (pretty-slot-name slot-description)
                                            for vector-slot-index? =
                                            (vector-slot-index? slot-description)
                                            for old-slot-name-assignment? =
                                            (old-slot-name-assignment pretty-slot-name)
                                            when
                                            (and
                                             (not (loop for superior in direct-superior-classes
                                                     thereis
                                                     (get-slot-description-of-class-description
                                                      unique-slot-name (class-description superior))))
                                             (or (not redef-class-p)
                                                 (and (not *there-is-a-current-kb?*)
                                                      (or (null old-slot-name-assignment?)
                                                          (if (eq old-slot-name-assignment?
                                                                  'lookup-slot)
                                                              vector-slot-index?
                                                              (not (eql old-slot-name-assignment?
                                                                        vector-slot-index?))))))
                                             (not (feature-assq
                                                   'no-accessor
                                                   (slot-features slot-description))))
                                            collect
                                            (if vector-slot-index?
                                                (cond
                                                  ((and subclass-of-block-p
                                                        (slot-description-is-noteworthy
                                                         slot-description))
                                                   (let ((setf-name (intern (format nil "SETF-~a" pretty-slot-name))))
                                                     `(progn
                                                        (defmacro ,pretty-slot-name (,class)
                                                          (list 'svref
                                                                (list 'the 'simple-vector ,class)
                                                                (list 'the 'fixnum ,vector-slot-index?)))

                                                        (defmacro ,setf-name (,class value)
                                                          (cond
                                                            ((symbolp ,class)
                                                             `(progn
                                                                (note-change-to-block ,,class ',',pretty-slot-name)
                                                                (setf (svref (the simple-vector ,,class)
                                                                             ,',vector-slot-index?)
                                                                      ,value)))

                                                            (t (let ((class-value (gensym)))
                                                                 `(let ((,class-value ,,class))
                                                                    (note-change-to-block ,class-value ',',pretty-slot-name)
                                                                    (setf (svref (the simple-vector ,class-value)
                                                                                 ,',vector-slot-index?)
                                                                          ,value))))))
                                                        (defsetf ,pretty-slot-name ,setf-name))))
                                                  ((and dependent-frame-p
                                                        (slot-description-is-noteworthy
                                                         slot-description))
                                                   (let ((setf-name (intern (format nil "SETF-~a" pretty-slot-name))))
                                                     `(progn
                                                        (defmacro ,pretty-slot-name (,class)
                                                          (list 'svref
                                                                (list 'the 'simple-vector ,class)
                                                                (list 'the 'fixnum ,vector-slot-index?)))

                                                        (defmacro ,setf-name (,class value)
                                                          (cond
                                                            ((symbolp ,class)
                                                             `(progn
                                                                #+development
                                                                (when (null current-block-of-dependent-frame)
                                                                  (error-message-for-dependent-frame-saving ,,class))
                                                                (note-change-to-dependent-frame)
                                                                (setf (svref (the simple-vector ,,class)
                                                                             ,',vector-slot-index?)
                                                                      ,value)))

                                                            (t (let ((class-value (gensym)))
                                                                 `(let ((,class-value ,,class))
                                                                    #+development
                                                                    (when (null current-block-of-dependent-frame)
                                                                      (error-message-for-dependent-frame-saving
                                                                       ,class-value))
                                                                    (note-change-to-dependent-frame)
                                                                    (setf (svref (the simple-vector ,class-value)
                                                                                 ,',vector-slot-index?)
                                                                          ,value))))))

                                                        (defsetf ,pretty-slot-name ,setf-name))))
                                                  (t
                                                   `(defmacro ,pretty-slot-name (,class)
                                                      (list 'svref
                                                            (list 'the 'simple-vector ,class)
                                                            (list 'the 'fixnum ,vector-slot-index?)))))
                                                ;; The above aref was replaced with an svref
                                                ;; to make it run fast in Lucid.  -jra 11/10/87
                                                ;; If the current slot is a vector slot then
                                                ;; generate an accessor which accesses the proper
                                                ;; place in the vector ...
                                                (let ((setf-name (intern (format nil "SETF-~a" pretty-slot-name))))
                                                  `(progn
                                                     ;; Defmacro is used here instead of
                                                     ;; defmacro-with-setf because the later
                                                     ;; definition is for canonical setf forms only.
                                                     (defmacro ,pretty-slot-name (,class)
                                                       (expand-lookup-slot-reference
                                                        ,class '',pretty-slot-name))
                                                     ;; Modified by ML, 3/24/91 to call either
                                                     ;; set-non-savable-lookup-slot-value,
                                                     ;; set-savable-block-lookup-slot-value, or
                                                     ;; set-savable-dependent-frame-lookup-slot-value.
                                                     (defmacro ,setf-name (,class value)
                                                       (list
                                                        ,(cond
                                                          ((not
                                                            (slot-description-is-noteworthy
                                                             slot-description))
                                                           ''set-non-savable-lookup-slot-value)
                                                          (subclass-of-block-p
                                                           ''set-savable-block-lookup-slot-value)
                                                          (dependent-frame-p
                                                           ''set-savable-dependent-frame-lookup-slot-value)
                                                          (t
                                                           (cerror "continue"
                                                                   "Expanding savable ~
                                                                      slot of kb-frame?!!")))
                                                        ,class '',pretty-slot-name value))

                                                     (defsetf ,pretty-slot-name ,setf-name))))))))
                         ;; If this definition was a redefinition of this class
                         ;; then redefine each of the descendants of the class.
                         ;; During this hackery, make the Lucid redefinition
                         ;; warnings shut up.
                         ,@(if a-priori-inferior-classes
                               `((eval-when
                                     (:compile-toplevel :execute)
                                   (let
                                       #+(and lucid (not translator))
                                       ((lcl:*record-source-files* nil)
                                        (lcl:*redefinition-action* nil))
                                       #-(and lucid (not translator))
                                       ()
                                       ,@(if *there-is-a-current-kb?*
                                             (if (and redefinitionp
                                                      (not unchanged-class-definition-p))
                                                 `((setf (definition-state ',class) 'being-redefined)
                                                   ,@(loop for inferior-class
                                                        in a-priori-inferior-classes
                                                        collecting
                                                        (class-definition inferior-class))
                                                   (setf (definition-state ',class) 'defined))
                                                 `((setf (definition-state ',class) 'being-redefined)
                                                   ,@(loop for inferior-class
                                                        in a-priori-inferior-classes
                                                        when (not (classp inferior-class))
                                                        collect (class-definition inferior-class))
                                                   (setf (definition-state ',class) 'defined)))
                                             `((setf (definition-state ',class) 'being-redefined)
                                               ,@(loop for inferior-class
                                                    in a-priori-inferior-classes
                                                    collecting
                                                    (class-definition inferior-class))
                                               (setf (definition-state ',class) 'defined)))))))
                         ',class))))
              ;; No need for redefinition.
              (progn
                (setf (definition-state class) 'defined)
                `(progn
                   ,@(if (and *there-is-a-current-kb?*
                              a-priori-inferior-classes)
                         `((setf (definition-state ',class) 'being-redefined)
                           ,@(loop for inferior-class
                                in a-priori-inferior-classes
                                when (not (classp inferior-class))
                                collect (class-definition inferior-class))
                           (setf (definition-state ',class) 'defined)))
                   ',class)))))))




;;; The function for macro `expand-loookup-slot-reference' is used to expand
;;; calls to the macros which fetch the values of lookup slots.  This macro
;;; will expand into a call to get-lookup-slot-value-given-default.  During
;;; development and macro pass compiles, the default is determined by looking
;;; up the slot-description with the class-description of the given frame.
;;; However, when in a distribution pass compile, if the slot named has a
;;; uniform default value throughout all slot descriptions for that slot name,
;;; and that default value is a Lisp constant, then expand this call to pass
;;; the default value directly to get-lookup-slot-value-given-default.  This
;;; optimization eliminates the need to find the slot-description at run-time
;;; when executing this fetch, which was identified by profiling as a
;;; performance problem.

;;; We need to emit the optimized call when emitting C code. This is a little
;;; dangerous, since we don't actually know that we have seen all the classes
;;; that define this slot yet. But at the moment, we're lucky; the only time
;;; the slot is redefined in other classes subsequent to stack-kern
;;; is for name-or-names-for-frames, and all the definitions agree
;;; that the init form is nil, so we're OK. So this is fragile, but correct.
;;; Simplest fix is probably to move (generate-expanded-instruction-macros t)
;;; from stack-kern to some very late file.

(defun-for-macro expand-lookup-slot-reference (frame-form slot-name-constant)
  (if (not (or (eval-feature :no-macros)
               macroexpanding-for-instruction-expander))
      `(get-lookup-slot-value ,frame-form ,slot-name-constant)
      (let* ((slot-name (eval slot-name-constant))
             (optimizable-default
               (get slot-name 'lookup-slot-optimizable-default)))
        (unless optimizable-default
          (loop with first? = t
                with default
                for class being each unoptimized-subclass of 'root
                for class-description = (class-description class)
                do
            (when (memq slot-name (slots-local-to-class class-description))
              (let ((init-form (slot-init-form
                                 (get-slot-description-of-class-description
                                   slot-name class-description))))
                (cond (first?
                       (unless (constantp init-form)
                         (setq optimizable-default 'no)
                         (return nil))
                       (setq default init-form)
                       (setq first? nil))
                      ((neq default init-form)
                       (setq optimizable-default 'no)
                       (return nil)))))
                finally
                  (setq optimizable-default (cons 'yes default)))
          (setf (get slot-name 'lookup-slot-optimizable-default)
                optimizable-default))
        (if (eq optimizable-default 'no)
            `(get-lookup-slot-value ,frame-form ,slot-name-constant)
            `(get-lookup-slot-value-given-default
               ,frame-form ,slot-name-constant ,(cdr optimizable-default))))))




;;; `Get-most-specific-direct-superior-for-class' returns the first class
;;; in a set of direct superior classes.

(defun get-most-specific-direct-superior-for-class (direct-superiors-for-class)
  (first direct-superiors-for-class))




;;; `Get-foundation-class-for-class' returns the value of the foundation-class
;;; class feature for class when there is one; otherwise it returns nil.  The
;;; class must be defined.

(defun get-foundation-class-for-class (class)
  (second (get-class-feature-in-class-description-if-any
            (class-description class) 'foundation-class)))




;;; `Most-refined-foundation-class-of-direct-superiors' returns the most
;;; specific system-defined class from the foundation classes for a set of
;;; acceptable direct superior classes.  That foundation-class need not be
;;; instantiable.

;;  The following system classes have foundation classes that are more general
;;  than themselves.  If a slot-name is provided to this function, and the
;;  slot is not found on the superior's foundation class but is found on the
;;  superior, the slot's defining class will be used in place of the foundation class.

;;   foundation-class : classes
;;   item : (g2-foreign-savable g2-foreign-serializable gsi-message-service)
;;   object : (g2-to-g2-data-interface gfi-input-interface gfi-output-interface gsi-interface)
;;   variable : (g2-meter-data-service g2-to-g2-data-service gfi-data-service gsi-data-service)

(defun most-refined-foundation-class-of-direct-superiors
    (direct-superior-classes &optional unaliased-slot-name)
  (let ((most-refined-foundation-class nil))
    (loop for superior in direct-superior-classes
          for slot-description?
              = (when unaliased-slot-name
                  (slot-description-from-class
                   superior unaliased-slot-name))
          for slot-defining-class?
              = (when slot-description?
                  (defining-class slot-description?))
          for superior-is-system-defined-p
              = (system-defined-class-p superior)
          for superior-foundation-class
              = (get-foundation-class-for-class superior)
          for foundation-class-slot-description?
              = (when unaliased-slot-name
                  (slot-description-from-class
                   superior-foundation-class unaliased-slot-name))
          do
      (unless foundation-class-slot-description?
        (when unaliased-slot-name
          (setq superior-foundation-class nil))
        (when slot-defining-class?
          (setq superior-foundation-class slot-defining-class?)))
      (when superior-foundation-class
        (when (or (null most-refined-foundation-class)
                  (subclassp superior-foundation-class
                             most-refined-foundation-class))
          (setq most-refined-foundation-class superior-foundation-class))))
    most-refined-foundation-class))




;;; `System-class-method-tables-processed?' is true after G2-FINAL has
;;; been loaded.  The def-class and def-class-method forms check this variable
;;; before calling fill-in-or-update-method-tables-of-class-descriptions.

(defvar system-class-method-tables-processed? nil)



(defvar decache-attribute-description-lists-of-interned-lists-function nil)

(defvar class-change-timestamp 0)

(defun-void decache-cached-class-data (class)
  (when decache-attribute-description-lists-of-interned-lists-function
    (funcall-simple-compiled-function
      decache-attribute-description-lists-of-interned-lists-function
      class))
  (update-change-timestamps class))

(defun-void update-change-timestamps (class)
  (let ((class-description? (class-description class)))
    (when class-description?
      (let ((new-timestamp (atomic-incff class-change-timestamp)))
        (setf (class-description-change-timestamp class-description?) new-timestamp)
        (loop for superclass-class-description in (class-description-inheritance-path class-description?)
              do (setf (class-description-subclass-change-timestamp superclass-class-description) new-timestamp))))))


;;; `Add-class-to-environment' adds the given system-defined or user-defined
;;; class to the class hierarchy by constructing a class description for the
;;; class that includes the slot descriptions that class inherits from its
;;; superior classes.

(defun add-class-to-environment
    (class direct-superior-classes
           class-inheritance-path
           class-features do-not-propagate-methods?
           slot-descriptions-defined-for-class
           previous-direct-superior-classes?
           class-definition user-defined-class?
           &optional slot-descriptions-for-overridden-slots?)
  (let* ((slot-descriptions-defined-for-class
           (if user-defined-class?
               slot-descriptions-defined-for-class
               (copy-slot-descriptions-evaluating-initialization-if-eval-once
                 slot-descriptions-defined-for-class)))
         (superior-class-class-description
           (class-description (car direct-superior-classes)))
         (class-inheritance-path
           (if user-defined-class?
               class-inheritance-path
               (make-class-inheritance-path-for-system-defined-class
                 class direct-superior-classes)))
         (foundation-class
           (when user-defined-class?
             (most-refined-foundation-class-of-direct-superiors
               direct-superior-classes)))
         (frame-vector-length
           (if user-defined-class?
               (class-vector-length
                 (class-description foundation-class))
               (class-vector-length
                 superior-class-class-description)))
         (class-bit-number
           (if user-defined-class?
               (get-next-class-bit-number)
               nil))
         (class-bit-vector
           (if user-defined-class?
               (make-class-bit-vector
                 class-bit-number class-inheritance-path)
               nil))
         (slots-local-to-class nil)
         (inherited-slots-this-class-overrides nil))

    (cond (user-defined-class?
           (eval-slot-init-forms-of-slot-descriptions-defined-for-class
             class slot-descriptions-defined-for-class)

           (multiple-value-bind
               (all-slot-descriptions-for-class
                 class-user-vector-length)
               (merge-slot-descriptions-for-user-defined-class
                 class class-inheritance-path
                 slot-descriptions-defined-for-class
                 slot-descriptions-for-overridden-slots?)


             (multiple-value-bind
                 (slot-descriptions-hash-table full-hash-table-class)
                 (make-slot-descriptions-hash-table
                   class all-slot-descriptions-for-class class-inheritance-path
                   direct-superior-classes t)


               (setf (class-definition class) class-definition)

               (cond ((and previous-direct-superior-classes?
                           (not (equal previous-direct-superior-classes?
                                       direct-superior-classes)))

                      (loop for previous-superior in previous-direct-superior-classes?
                            do
                        (unless (memq previous-superior direct-superior-classes)
                          (setf (inferior-classes previous-superior)
                                (delete-class-description-element
                                  class (inferior-classes previous-superior)))))

                      (loop for superior in direct-superior-classes
                            do
                        (unless (memq class (inferior-classes superior))
                          (copy-kb-specific-property-from-global-if-necessary
                            superior 'inferior-classes)
                          (setf (inferior-classes superior)
                                (nconc (inferior-classes superior)
                                       (class-description-list class))))))
                     (t
                      (loop for superior in direct-superior-classes
                            for inferior-classes = (inferior-classes superior)
                            do
                        (unless (memq class inferior-classes)
                          (copy-kb-specific-property-from-global-if-necessary
                            superior 'inferior-classes)
                          (setf (inferior-classes superior)
                                (nconc (inferior-classes superior)
                                       (class-description-list class)))))))

               (loop for slot-description in slot-descriptions-defined-for-class
                     for unique-slot-name = (unique-slot-name slot-description)
                     for pretty-slot-name = (pretty-slot-name slot-description)
                     for slot-features = (slot-features slot-description)
                     do
                 (if (user-defined-slot-description-p slot-description)
                     (setf slots-local-to-class
                           (nconc slots-local-to-class
                                  (class-description-list unique-slot-name)))
                     (setf inherited-slots-this-class-overrides
                           (class-description-cons
                             unique-slot-name inherited-slots-this-class-overrides)))

                 ;; Kept for pre-4.0 kbs.  Since then user-defined slots do not have
                 ;; such a slot-feature.
                 (when (feature-assq 'port slot-features)
                   (setf (slot-category pretty-slot-name) 'port)))


               (loop for slot-description in slot-descriptions-for-overridden-slots?
                     do
                 (setf inherited-slots-this-class-overrides
                       (class-description-cons
                         (unique-slot-name slot-description)
                         inherited-slots-this-class-overrides)))

               (reclaim-class-description-list slot-descriptions-defined-for-class)
               (reclaim-class-description-list slot-descriptions-for-overridden-slots?)

               (make-and-change-class-description
                 class
                 class-inheritance-path
                 frame-vector-length
                 class-features
                 all-slot-descriptions-for-class
                 t
                 class-user-vector-length
                 slots-local-to-class
                 inherited-slots-this-class-overrides
                 slot-descriptions-hash-table
                 full-hash-table-class
                 class-bit-number class-bit-vector
                 (initialize-or-update-method-table-for-user-class
                   class class-inheritance-path t)
                 (not user-defined-class?))

               (setf (direct-superior-classes class)
                     (if user-defined-class?
                         (copy-list-using-class-description-conses
                           direct-superior-classes)
                         direct-superior-classes)))))

          ;; The class is system-defined.
          (t
           (multiple-value-bind
               (all-slot-descriptions-for-class
                 class-vector-length local-slots-for-class)
               (merge-slot-descriptions-for-system-defined-class
                 direct-superior-classes class-inheritance-path
                 slot-descriptions-defined-for-class)

             (multiple-value-bind
                 (slot-descriptions-hash-table full-hash-table-class)
                 (make-slot-descriptions-hash-table
                   class all-slot-descriptions-for-class class-inheritance-path
                   direct-superior-classes nil)

               (when
                   (and previous-direct-superior-classes?
                        (not (equal previous-direct-superior-classes?
                                    direct-superior-classes)))
                 (loop for superior in previous-direct-superior-classes?
                       do
                   (unless (memq superior direct-superior-classes)
                     (setf (inferior-classes superior)
                           ;; is it safe to use `delete' here? it may leak memory. --binghe
                           (delete class (inferior-classes superior))))
                   (unpropagate-methods superior class)))

               ;; The parameter do-not-propagate-methods? should be nil if called
               ;; during a def-class, and t if called from a user definition.
               ;; But until there is a complete recompile, expanded def-class macros
               ;; in FASL files will give a value of 'OBSOLETE!!!
               (loop for superior in direct-superior-classes
                     do
                 (when (or (null do-not-propagate-methods?)
                           (eq do-not-propagate-methods? 'obsolete))
                   (propagate-methods superior class))
                 (unless (memq class (inferior-classes superior))
                   (copy-kb-specific-property-from-global-if-necessary
                     superior 'inferior-classes)
                   (setf (inferior-classes superior)
                         (nconc (inferior-classes superior)
                                (class-description-list class)))))

               (setf (class-definition class) class-definition)

               ;; Alter the class description to reflect the new state of the class.
               (make-and-change-class-description
                 class
                 class-inheritance-path
                 class-vector-length
                 class-features
                 all-slot-descriptions-for-class
                 (if (memq 'item class-inheritance-path) t nil)
                 0
                 local-slots-for-class
                 nil
                 slot-descriptions-hash-table
                 full-hash-table-class
                 ;; class-bit-number and class-bit-vector
                 class-bit-number class-bit-vector
                 (make-method-table-for-system-class)
                 (not user-defined-class?))

               (setf (direct-superior-classes class) direct-superior-classes)

               (when system-class-method-tables-processed?
                 (initialize-or-update-method-tables-of-class-descriptions class)))))))
  (decache-cached-class-data class)
  class)




;;; The function `get-appropriate-slot-descriptions-cons' returns a sublist of
;;; the slot descriptions in which the first slot description has a
;;; unique-slot-name EQ to the unique-slot-name argument if there is such a slot
;;; description; otherwise it returns nil.

(defun-simple get-appropriate-slot-descriptions-cons
    (unique-slot-name slot-descriptions)
  (when slot-descriptions
    (loop for sublist on slot-descriptions
          for car-of-slot-descriptions = (car sublist)
          when (eq unique-slot-name (unique-slot-name car-of-slot-descriptions))
            return sublist)))




;;; `Merge-descriptions-for-system-class' is called by add-class-to-
;;; environment.  Using the slot descriptions defined for the classes on the
;;; class inheritance path for new class, it constructs a set of
;;; slot descriptions for the new class that is a union of the uniquely-named
;;; slot descriptions plus the most-specific of the same-named slot
;;; descriptions.  When there is more than one slot description with the same
;;; name, the most-specific slot description is the slot description defined for
;;; the left-most class on the class inheritance path (new class or the class
;;; closest to new class on the class hierarchy).

(defun merge-slot-descriptions-for-system-defined-class
        (direct-superior-classes class-inheritance-path
         slot-descriptions-defined-for-class)
  (let* ((all-slot-descriptions-for-class nil)
         (class-vector-length
           (loop with longest-vector-length =
                        (class-vector-length
                          (class-description (first direct-superior-classes)))
                 for superior in (cdr direct-superior-classes)
                 for superior-vector-length =
                       (class-vector-length (class-description superior))
                 do
             (when (>f superior-vector-length longest-vector-length)
               (setq longest-vector-length superior-vector-length))
                 finally (return longest-vector-length)))
         (slots-local-to-class nil))

    ;; Process the slot descriptions of the superior classes starting with
    ;; the slot descriptions defined for the root class.
    (loop with temp-class-list = (nreverse (copy-list-using-gensym-conses
                                             (cdr class-inheritance-path)))
          ;; for superior in (nreverse (cdr class-inheritance-path))
          for superior in temp-class-list
          for class-description = (class-description superior)
          for slots-local-to-class =
          (slots-local-to-class class-description)
          do
      (loop for local-slot-name in slots-local-to-class
            for slot-description =
            (get-slot-description-of-class-description
              local-slot-name class-description)
            for cons-holding-slot-description? =
            (get-appropriate-slot-descriptions-cons
              local-slot-name all-slot-descriptions-for-class)
            do
        (if cons-holding-slot-description?
            (setf (car cons-holding-slot-description?)
                  slot-description)
            (setq all-slot-descriptions-for-class
                  (nconc
                    all-slot-descriptions-for-class
                    (list slot-description)))))
          finally
            (reclaim-gensym-list temp-class-list))

    ;; Process the slot descriptions specifically defined for the new class.
    (loop for slot-description in slot-descriptions-defined-for-class
          for unique-slot-name = (unique-slot-name slot-description)
          for pretty-slot-name = (pretty-slot-name slot-description)
          for cons-holding-slot-description? =
              (get-appropriate-slot-descriptions-cons
                unique-slot-name all-slot-descriptions-for-class)
          do

      (setq slots-local-to-class (nconc slots-local-to-class (list unique-slot-name)))
      (if cons-holding-slot-description?
          (setf (car cons-holding-slot-description?)
                (add-inherited-features-and-indexes-to-system-slot-description
                  slot-description (car cons-holding-slot-description?) nil))
          (let* ((slot-features (slot-features slot-description))
                 (vector-slot? (vector-slot-from-features-p
                                (slot-features slot-description)))
                 (current-slot-name-assignment?
                  (slot-name-assignment pretty-slot-name))
                 (future-slot-name-assignment nil))

            (cond (vector-slot?
                   (setf (vector-slot-index? slot-description)
                         class-vector-length)
                   (setq future-slot-name-assignment class-vector-length)
                   (setq class-vector-length (1+f class-vector-length)))
                  (t
                   (setq future-slot-name-assignment 'lookup-slot)))

            (when (and current-slot-name-assignment?
                       (or (not (eql current-slot-name-assignment?
                                     future-slot-name-assignment))
                           (old-slot-name-assignment pretty-slot-name)))
              (setf (old-slot-name-assignment pretty-slot-name)
                    current-slot-name-assignment?))
            (setf (slot-name-assignment pretty-slot-name)
                future-slot-name-assignment)

            (cond ((feature-assq 'system slot-features)
                   (setf (slot-category pretty-slot-name) 'system))
                  ((feature-assq 'port slot-features)
                   (setf (slot-category pretty-slot-name) 'port))
                  ((slot-category pretty-slot-name)
                   (setf (slot-category pretty-slot-name) nil))
                  (t nil))
            (setq all-slot-descriptions-for-class
                  (nconc all-slot-descriptions-for-class
                         (list slot-description))))))

    (values all-slot-descriptions-for-class
              class-vector-length slots-local-to-class)))




;; just checks if the slot description defines a system slot

(defmacro system-slot-p (a-slot-description)
  (let ((slot-description (gensym)))
    `(let* ((,slot-description ,a-slot-description)
            (features (slot-features ,slot-description)))
       (feature-assq 'system features))))




;;; `Collect-user-defined-slot-descriptions-for-defining-class' frame-conses the
;;; slot descriptions in slot-descriptions that are user defined specifically
;;; for defining-class.

(defun collect-user-defined-slot-descriptions-for-defining-class
    (defining-class slot-descriptions)
  (loop for slot-description in slot-descriptions
        for slot-description-defining-class = (defining-class slot-description)
        when (and (eq slot-description-defining-class defining-class)
                  (user-defined-slot-description-p slot-description))
          collect slot-description using frame-cons))




;;; `Get-new-defaul-slot-description-with-pretty-name' returns the
;;; slot-description with pretty-slot-name defined by the most-specific superior
;;; on the class- inheritance-path if there is one; otherwise it returns nil.
;;; This function is called by delete-slot-description-from-hash-table code, and
;;; will not choose the slot-description-being-deleted.

(defun get-new-default-slot-description-with-pretty-name
    (slot-description-being-deleted class-description)
  (let ((class-inheritance-path (class-inheritance-path class-description))
        (pretty-slot-name (pretty-slot-name slot-description-being-deleted))
        (qualifying-slot-description? nil))
    (loop for slot-description in (slot-descriptions class-description)
          do
      (when (and (eq (pretty-slot-name slot-description) pretty-slot-name)
                 (not (eq slot-description slot-description-being-deleted))
                 (or (null qualifying-slot-description?)
                     (<f (position
                           (defining-class slot-description)
                           class-inheritance-path)
                         (position
                           (defining-class qualifying-slot-description?)
                           class-inheritance-path))))
        (setq qualifying-slot-description? slot-description))
          finally (return qualifying-slot-description?))))




;;; The function `get-slot-description' takes a unique or pretty slot name, a
;;; list of slot-descriptions and, optionally, a defining-class specifier, and
;;; returns the slot description in that list with that unique slot name or with
;;; that pretty slot name and defining class.

;;; This is an unoptimized version of get-slot-description-of-class-description
;;; and should be used only when there is a change in the class hierarchy that
;;; temporarily makes the slot-description hash tables out of sync.  If at all
;;; possible, unique-or-pretty-slot-name should be the unique slot name if
;;; defining-class? is null; however, if no unique-slot-name is found with
;;; that unique-or-pretty-slot-name, the most specific slot description will be
;;; returned based on that fact that user-defined slot descriptions are
;;; arranged from least specific to most specific.

(defun get-slot-description
    (unique-or-pretty-slot-name slot-descriptions &optional defining-class?)
  (if defining-class?
      (loop for slot-description in slot-descriptions
            when (and (or (eq unique-or-pretty-slot-name
                              (pretty-slot-name slot-description))
                          (eq unique-or-pretty-slot-name
                              (unique-slot-name slot-description)))
                      (eq defining-class? (defining-class slot-description)))
              return slot-description)
      (loop with most-specific-default? = nil
            for slot-description in slot-descriptions
            do
        (when (eq unique-or-pretty-slot-name
                  (unique-slot-name slot-description))
          (return slot-description))
        (when (eq unique-or-pretty-slot-name
                  (pretty-slot-name slot-description))
          (setq most-specific-default? slot-description))
            finally (return most-specific-default?))))




;;; `User-overridable-system-slots' is used for determing what system slots are
;;; user-overridable, both to display them to the user in the system slot of the
;;; same name on class definitions and to use them for determining inheritance.
;;; Every foundation class has an entry which consists of:

;;; (class-name overridable-slots-aliased masked-slots-aliased
;;;             overridable-slots-unaliased masked-slots-unaliased).

;;; Masked slots are those not inherited from a superior class.

(def-system-variable list-of-user-overridable-system-slots frames2
  '(
    (class-definition
     (instantiate include-in-menus)
     nil
     (instantiate? include-in-menus?)
     nil)

    (object
     (attribute-displays stubs)
     nil
     (attribute-displays-for-class stubs-for-class icon-description)
     nil)

    (variable-or-parameter
     (tracing-and-breakpoints history-keeping-spec-for-variable-or-parameter
      initial-value)
     nil
     (tracing-and-breakpoints variable-or-parameter-history-specification?
      initial-value-of-variable-or-parameter)
     nil)

    (variable
     (validity-interval supply-simulation-subtable data-server
      default-update-interval options-for-variable
      history-keeping-spec-for-simulation-subtable)
     nil
     (validity-interval simulation-details data-server-map
      background-collection-interval? frame-flags
      history-keeping-spec-for-simulation-subtables?)
     nil)

    (sensor
     (data-type)
     nil
     (data-type-of-variable-or-parameter)
     nil)

    (quantitative-variable
     (data-type)
     nil
     (data-type-of-variable-or-parameter)
     nil)

    (gsi-message-service
     (gsi-interface-name data-server-for-messages)
     nil
     (gsi-interface-name data-server-for-messages)
     nil)

    (g2-meter-data-service
     (g2-meter-name)
     nil
     (g2-meter-name)
     nil)

    (gfi-data-service
     (gfi-input-interface-object)
     nil
     (gfi-input-interface-object)
     nil)

    (gsi-data-service
     (gsi-interface-name)
     nil
     (gsi-interface-name)
     nil)

    (g2-to-g2-data-service
     (g2-to-g2-interface-name)
     nil
     (g2-to-g2-interface-name)
     nil)

    (gfi-output-interface
     (maximum-number-of-output-lines gfi-output-file-update-frequency
      gfi-output-time-stamp-format gfi-output-file-format
      renamed-gfi-output-file-pathname gfi-output-file-pathname)
     nil
     (maximum-number-of-output-lines gfi-output-file-update-frequency
      gfi-output-time-stamp-format gfi-output-file-format
      renamed-gfi-output-file-pathname? gfi-output-file-pathname)
     nil)

    (gfi-input-interface
     (ignore-gfi-input-base-time gfi-input-variables-update-mode
      gfi-input-time-stamp-format gfi-input-file-format gfi-input-file-pathname)
     nil
     (ignore-gfi-input-base-time? gfi-input-variables-update-mode
      gfi-input-time-stamp-format gfi-input-file-format gfi-input-file-pathname)
     nil)

    (network-interface
     (identifying-attributes interface-warning-message-level
      interface-timeout-period interface-initialization-timeout-period
      disable-interleaving-of-large-messages)
     ;; creation-attributes item-reference-options names-of-remote-interface class-of-remote-interface
     nil
     (identifying-attributes interface-warning-message-level
      interface-timeout-period interface-initialization-timeout-period
      disable-interleaving-of-large-messages)
     nil)

    (gsi-interface
     (external-system-has-a-scheduler poll-external-system-for-data
      grouping-specification remote-process-initialization-string interval-to-poll-external-system)
     nil
     (external-system-has-a-scheduler poll-external-system-for-data
      grouping-specification remote-process-initialization-string interval-to-poll-external-system)
     nil)

    (g2-to-g2-data-interface
     ()
     nil
     ()
     nil)

    (parameter
     (options-for-parameter)
     nil
     (frame-flags)
     nil)

    (quantitative-parameter
     (data-type)
     nil
     (data-type-of-variable-or-parameter)
     nil)

    (g2-array
     (array-length initial-values array-is-permanent)
     nil
     (g2-array-length g2-array-initial-values array-is-permanent)
     nil)

    (item-array
     (element-type)
     nil
     (g2-array-element-type)
     nil)

    (item-list
     (element-type)
     nil
     (list-type)
     nil)

    (g2-list
     (allow-duplicate-elements-for-g2-list list-is-permanent)
     nil
     (insert-duplicate-elements? list-is-permanent)
     nil)

    (connection
     (cross-section-pattern stub-length junction-block)
     nil
     (cross-section-pattern cross-section-pattern-for-class
      stub-length stub-length-for-class junction-block-class
      junction-block-class-for-class)
     nil)

    (message
     (default-message-properties)
     nil
     (default-message-properties-for-class default-text-box-format-name
         text-cell-plist-for-text-box
         minimum-width-of-text-box minimum-height-of-text-box)
     nil)

    (kb-workspace
     (initial-width initial-height foreground-color background-color
      workspace-margin frame-style title-bar-text module-assignment)
     nil
     (kb-workspace-initial-width kb-workspace-initial-height
      workspace-foreground-color? workspace-background-color? workspace-margin
      frame-style title-bar-text module-this-is-part-of?)
     nil)

    (procedure
     (tracing-and-breakpoints class-of-procedure-invocation
      default-procedure-priority uninterrupted-procedure-execution-limit
      attribute-displays stubs)
     nil
     (tracing-and-breakpoints class-of-procedure-invocation
      default-procedure-priority uninterrupted-procedure-execution-limit?
      attribute-displays-for-class stubs-for-class icon-description)
     nil)

    (procedure-invocation
     (attribute-displays stubs)
     nil
     (attribute-displays-for-class stubs-for-class icon-description)
     nil)

    (method-declaration
     nil
     (tracing-and-breakpoints class-of-procedure-invocation
      default-procedure-priority uninterrupted-procedure-execution-limit)
     nil
     (tracing-and-breakpoints class-of-procedure-invocation
      default-procedure-priority uninterrupted-procedure-execution-limit?))

    (dial
     (tracing-and-breakpoints low-value-for-dial-ruling
      increment-per-dial-ruling display-update-interval display-wait-interval
      display-update-priority show-simulated-values
      attribute-displays stubs)
     nil
     (tracing-and-breakpoints low-value-for-dial-ruling
      increment-per-dial-ruling display-update-interval display-wait-interval
      display-update-priority display-evaluation-should-use-simulated-values?
      attribute-displays-for-class stubs-for-class icon-description)
     nil)

    (meter
     (tracing-and-breakpoints low-value-for-meter-ruling
      increment-per-meter-ruling display-update-interval display-wait-interval
      display-update-priority show-simulated-values attribute-displays stubs)
     nil
     (tracing-and-breakpoints low-value-for-meter-ruling
      increment-per-meter-ruling display-update-interval display-wait-interval
      display-update-priority display-evaluation-should-use-simulated-values?
      attribute-displays-for-class stubs-for-class icon-description)
     nil)

    (readout-table
     (tracing-and-breakpoints display-format display-update-interval
      display-wait-interval display-update-priority show-simulated-values)
     nil
     (tracing-and-breakpoints format-for-readout-table display-update-interval
      display-wait-interval display-update-priority
      display-evaluation-should-use-simulated-values?)
     nil)

    (digital-clock
     nil
     (tracing-and-breakpoints display-format show-simulated-values)
     nil
     (tracing-and-breakpoints format-for-readout-table
      display-evaluation-should-use-simulated-values?))

    (graph
     (desired-range-for-horizontal-axis desired-range-for-vertical-axis
      scroll-continuously? percentage-extra-space-to-leave show-grid-lines?
      interval-between-horizontal-grid-lines? extra-grid-lines?
      background-colors display-update-interval
      display-wait-interval display-update-priority
      show-simulated-values)
     nil
     (desired-range-for-horizontal-axis? desired-range-for-vertical-axis?
      scroll-continuously? percentage-extra-space-to-leave show-grid-lines?
      interval-between-horizontal-grid-lines? extra-grid-lines?
      background-colors display-update-interval
      display-wait-interval display-update-priority
      display-evaluation-should-use-simulated-values?)
     nil)

    (chart
     (chart-style data-series annotations)
     nil
     (chart-style data-series annotations)
     nil)

    (freeform-table
     (table-size default-cell-format default-evaluation-setting)
     nil
     (cell-annotations default-cell-format default-evaluation-setting)
     nil)

    (image-definition
     (file-name-of-image save-image-data-with-kb width-of-image
      height-of-image depth-of-image attribute-displays stubs)
     nil
     (file-name-of-image? save-image-data-with-kb width-of-image
      height-of-image depth-of-image attribute-displays-for-class stubs-for-class)
     nil)

    (user-menu-choice
     (applicable-class condition action-priority attribute-displays stubs)
     nil
     (class-for-user-menu-choice? condition-for-using-user-menu-choice?
       user-menu-choice-priority attribute-displays-for-class stubs-for-class
      icon-description)
     nil)

    (tabular-function-of-1-arg
     (keep-sorted interpolate attribute-displays stubs)
     nil
     (keep-tabular-function-sorted? tabular-function-interpolation?
      attribute-displays-for-class stubs-for-class icon-description)
     nil)

    (relation
     (first-class second-class relation-is-permanent attribute-displays stubs)
     nil
     (class-of-subject class-of-object relation-is-permanent
      attribute-displays-for-class stubs-for-class)
     nil)

    (frame-style-definition
     (description-of-frame attribute-displays stubs)
     nil
     (description-of-frame attribute-displays-for-class stubs-for-class
      icon-description)
     nil)

    (rule
     (tracing-and-breakpoints scan-interval focal-classes focal-objects
      categories rule-priority depth-first-backward-chaining-precedence
      timeout-for-rule-completion)
     nil
     (tracing-and-breakpoints rule-scan-interval focal-classes focal-objects
      rule-categories rule-priority backward-chaining-precedence
      timeout-for-rule-completion)
     nil)

    (generic-simulation-formula
     (tracing-and-breakpoints)
     nil
     (tracing-and-breakpoints)
     nil)

    (foreign-function-declaration
     (timeout-interval)
     nil
     (timeout-interval)
     nil)

    (model-definition
     (default-simulation-time-increment
      integration-algorithm
      simulation-procedure send-all-values-at-beginning-of-cycle
      simulation-control-specifications attribute-displays stubs)
     nil
     (default-simulation-time-increment-for-model
      integration-algorithm-for-model
      simulation-procedure-for-model
      send-all-values-at-beginning-of-cycle-for-model?
      simulation-control-specifications attribute-displays-for-class stubs-for-class
      icon-description)
     nil)

    (external-simulation-definition
     (class-of-object-computed-by-this attribute-displays stubs)
     nil
     (class-of-object-computed-by-this attribute-displays-for-class stubs-for-class
      icon-description)
     nil)

    (free-text
     (default-text-box-colors)
     nil
     (text-cell-plist-for-text-box)
     nil)

    (borderless-free-text
     (default-text-box-colors #+text-converted-to-show-encoding text-converted-to-show-encoding?)
     nil
     (text-cell-plist-for-text-box #+text-converted-to-show-encoding text-converted-to-show-encoding?)
     nil)

    (text-inserter
     (default-text-box-colors)
     nil
     (text-cell-plist-for-text-box)
     nil)

    (action-button
     (action-priority attribute-displays stubs)
     nil
     (action-button-priority attribute-displays-for-class stubs-for-class
      icon-description)
     nil)

    (non-action-button
     (value-on-activation variable-or-parameter)
     nil
     (value-on-activation? associated-variable-designation?)
     nil)

    (check-box
     (on-value off-value attribute-displays stubs)
     nil
     (on-value-for-check-box off-value-for-check-box attribute-displays-for-class
      stubs-for-class icon-description)
     nil)

    (radio-button
     (on-value attribute-displays stubs)
     nil
     (value-for-radio-button attribute-displays-for-class stubs-for-class
      icon-description))

    (slider
     (minimum-value maximum-value set-value-while-sliding? when-to-show-value
      attribute-displays stubs)
     nil
     (minimum-value-for-slider maximum-value-for-slider set-value-while-sliding?
      when-to-show-value attribute-displays-for-class stubs-for-class
      icon-description)
     nil)

    (type-in-box
     (format-for-type-in-box blank-for-type-in?
      have-edit-option-buttons-for-type-in?)
     nil
     (format-for-type-in-box blank-for-type-in?
      have-edit-option-buttons-for-type-in?)
     nil)

    (simulation-subtable
     (tracing-and-breakpoints time-increment-for-update)
     nil
     (tracing-and-breakpoints time-increment-for-update?))
    ))

(def-system-variable user-overridable-variable-slots frames2
  '(validity-interval data-server-map background-collection-interval?
    frame-flags variable-or-parameter-history-specification?
    history-specification-for-simulation-subtables?
    data-type-of-variable-or-parameter
    initial-value-of-variable-or-parameter icon-description))

(def-system-variable user-overridable-parameter-slots frames2
  '(variable-or-parameter-history-specification?
    data-type-of-variable-or-parameter
    initial-value-of-variable-or-parameter icon-description))

(def-system-variable user-overridable-g2-array-slots frames2
  '(g2-array-element-type g2-array-length g2-array-initial-values
    icon-description))

(def-system-variable user-overridable-g2-list-slots frames2
  '(list-type insert-duplicate-elements? icon-description))

(def-system-variable user-overridable-object-slots frames2
  '(icon-description))

(def-system-variable user-overridable-message-slots frames2
  '(default-text-box-format-name text-cell-plist-for-text-box
    minimum-width-of-text-box minimum-height-of-text-box))

(def-system-variable user-overridable-connection-slots frames2
  '(cross-section-pattern stub-length junction-block-class))




;;;  The function
;;;  `make-list-of-unaliased-user-overridable-system-slots-for-class'
;;;  frame-lists all of the unaliased system slot names that are
;;;  user-overridable by a class defined with a class-definition.

(defun-simple make-list-of-unaliased-user-overridable-system-slots-for-class
    (class-inheritance-path)
  (let ((list-to-return nil))
    (loop with slots-to-mask? =
          (loop for class in class-inheritance-path
                for masked-slots? =
                (and (system-defined-class-p class)
                     (fifth
                       (car (member class list-of-user-overridable-system-slots
                                    :test 'car-eq))))
                nconc masked-slots?)
          for class in class-inheritance-path
          for overridable-slots-for-class? =
          (and (system-defined-class-p class)
               (fourth
                 (car (member class list-of-user-overridable-system-slots
                              :test 'car-eq))))
          do
      (when overridable-slots-for-class?
        (loop for slot-name in overridable-slots-for-class?
              do
          (unless (memq slot-name slots-to-mask?)
            (frame-push slot-name list-to-return)))))
    list-to-return))

(defun car-eq (x some-cons) (eq x (car some-cons)))
(defun car-equal (x some-cons) (equal x (car some-cons)))



;;; The macro `system-class-overrides-slot-p' returns a non-null value
;;; when the def-class form for system-class has a slot-description
;;; for slot-name.

(defmacro system-class-overrides-slot-p (system-class slot-name)
  `(memq ,slot-name
         (slots-local-to-class (class-description ,system-class))))




;;; `Merge-slot-descriptions-for-user-defined-class' class-description-conses a
;;; list of slot descriptions that will be the value of the slot-descriptions
;;; slot of new-class class description.  It returns the slot descriptions and
;;; the number of slot descriptions that have user-vector slot indices.

;;; The list of slot descriptions has all of the system-defined slot
;;; descriptions at the beginning of the list and all of the user-defined slot
;;; descriptions at the end of the list.  Within each group, the
;;; slot-descriptions for less-specific classes come before those from
;;; more-specific classes.

;;; This separation of system and user-defined slot descriptions is done for
;;; code efficiency and for consistency with user-visible G2 3.0 behavior where
;;; all user-defined slots are found at the bottom of attribute tables;
;;; however, in G2 4.0, this placement may violate the class inheritance path
;;; ordering for some classes.  For example, a system-defined data-service
;;; class can be positioned between two user-defined classes.

;;; Overriding slot descriptions replace the original defining class slot
;;; description.  The slot descriptions for user-defined classes are kept in
;;; the order they appear on the class-definition table.

;;; The final parameter, slot-descriptions-for-overridden-slots?, will only
;;; be used by tw-rpc code.

(defun merge-slot-descriptions-for-user-defined-class
    (new-class new-class-inheritance-path new-class-specific-slot-descriptions
               slot-descriptions-for-overridden-slots?)
          ;; Find the longest tail on the new class inheritance path that equals
          ;; the class inheritance path of an existing class.  The list
          ;; structure of the existing class slot descriptions is copied and
          ;; becomes the start of the slot descriptions list for the new class.
  (let* ((superior-merging-point
           (loop for class-cons on (cdr new-class-inheritance-path)
                 when (equal class-cons
                             (class-inheritance-path
                               (class-description (car class-cons))))
                   return (car class-cons)))
         (merging-point-class-description
           (class-description superior-merging-point))
         (slot-descriptions-working-list
           (copy-list-using-class-description-conses
             (slot-descriptions merging-point-class-description)))
         (superior-classes-below-merging-point-in-reverse-order?
           (nreverse
             (loop for superior in (cdr new-class-inheritance-path)
                   until (eq superior superior-merging-point)
                   collect superior using frame-cons)))
         (user-superior-classes-below-merging-point?
           (loop for superior in (cdr new-class-inheritance-path)
                 until (eq superior superior-merging-point)
                 when (user-defined-class-p superior)
                   collect superior using frame-cons))
         (system-slots-overridden-by-most-refined-version nil)
         (current-user-vector-slot-index
           (class-user-vector-length merging-point-class-description)))

    ;; Replace the user-defined slot descriptions on the slot descriptions
    ;; working list with overrides from user-defined classes below the
    ;; merging point class.
    (unless (and (or (zerop current-user-vector-slot-index)
                     (null user-superior-classes-below-merging-point?))
                 ;; When called from tw-rpc code, deal with class-level
                 ;; overrides on superior user-defined slots here.
                 (null slot-descriptions-for-overridden-slots?))
      (loop with merging-point-class-inheritance-path =
              (class-inheritance-path merging-point-class-description)
            for slot-description in slot-descriptions-working-list
            do
        (when (user-defined-slot-description-p slot-description)
          (let* ((unique-slot-name (unique-slot-name slot-description))
                 (new-class-slot-description?
                   (get-slot-description
                     unique-slot-name slot-descriptions-for-overridden-slots?))
                 (most-specific-overriding-class
                   (if new-class-slot-description?
                       new-class
                       ;; Most-specific-superior-that-refines-slot is
                       ;; defined in frames1.  It gets its information from
                       ;; class-descriptions.
                       (most-specific-superior-that-refines-slot
                         new-class-inheritance-path slot-description))))
            (unless (memq most-specific-overriding-class
                          merging-point-class-inheritance-path)
              (let* ((overriding-class-slot-description
                       (or new-class-slot-description?
                           (slot-description-from-class
                             most-specific-overriding-class unique-slot-name)))
                     (inherited-user-vector-slot-index
                       (user-vector-slot-index? slot-description))
                     (slot-description-to-add
                       (if (eql (user-vector-slot-index?
                                  overriding-class-slot-description)
                                inherited-user-vector-slot-index)
                           overriding-class-slot-description
                           (make-slot-description
                             (pretty-slot-name overriding-class-slot-description)
                             (defining-class overriding-class-slot-description)
                             new-class
                             (slot-type-specification
                               overriding-class-slot-description)
                             (slot-init-form overriding-class-slot-description) nil
                             inherited-user-vector-slot-index
                             (slot-features overriding-class-slot-description))))
                     (cons-holding-slot-description
                       (memq slot-description slot-descriptions-working-list)))
                (setf (car cons-holding-slot-description)
                      slot-description-to-add)))))))

    ;; Now add the slot descriptions for the superior classes below the
    ;; merging point.  The classes are processed from least specific to
    ;; most specific superior which automatically replaces the slot descriptions
    ;; of less specific system-defined classes with those of more-specific
    ;; system-defined classes.
    ;; The slots-local-to-class for a user-defined-class is a list of
    ;; unique-slots-names for the slot-descriptions that correspond to the
    ;; attribute descriptions in the class-specific-attributes for the class.
    ;; The slots-local-to-class list for a system-defined class is generated by
    ;; the slot forms on the def-class form for a class.  This list is used to
    ;; determine what slots a system-defined class overrides.
    (when superior-classes-below-merging-point-in-reverse-order?
      (loop with user-slot-descriptions-to-add = nil
            with last-system-defined-slot-description = nil
            for superior in
                  superior-classes-below-merging-point-in-reverse-order?
            for class-description = (class-description superior)
            do
        (if (class-description-is-user-defined-p class-description)
            ;; Loop over the slot-descriptions that correspond to the local
            ;; attributes of the user-defined classes below the merging point.
            (loop for unique-slot-name in (slots-local-to-class class-description)
                  for local-slot-description =
                  (get-slot-description-of-class-description
                    unique-slot-name class-description)
                  ;; Slot-descriptions-for-overridden-slots? can only have a
                  ;; value when called from tw-rpc code.
                  for most-specific-slot-description =
                  (or (get-slot-description
                        unique-slot-name slot-descriptions-for-overridden-slots?)
                      (slot-description-of-most-specific-superior-refining-slot
                        new-class-inheritance-path local-slot-description))
                  for slot-description-to-add =
                  (if (eql (user-vector-slot-index?
                             most-specific-slot-description)
                           current-user-vector-slot-index)
                      most-specific-slot-description
                      (make-slot-description
                        (pretty-slot-name most-specific-slot-description)
                        (defining-class most-specific-slot-description)
                        new-class
                        (slot-type-specification most-specific-slot-description)
                        (slot-init-form most-specific-slot-description) nil
                        current-user-vector-slot-index
                        (slot-features most-specific-slot-description)))
                  do
              (setq user-slot-descriptions-to-add
                    (class-description-cons
                      slot-description-to-add user-slot-descriptions-to-add))
              (incff current-user-vector-slot-index))
            ;; Loop over the slot-descriptions that correspond to the slots
            ;; in the def-class forms of the system-defined classes below the
            ;; merging point.
            (loop for unique-slot-name in (slots-local-to-class
                                            class-description)
                  for class-level-slot-description =
                        (get-slot-description-of-class-description
                          unique-slot-name class-description)
                  for working-list-slot-description? =
                        (get-slot-description
                          unique-slot-name slot-descriptions-working-list)
                  do
              (if working-list-slot-description?
                  (let ((cons-holding-slot-description
                          (memq working-list-slot-description?
                                slot-descriptions-working-list)))
                    ;; See note below by GHW about the form added here for bug
                    ;; HQ-3307363: (MHD 3/2/00)
                    (when (eq (car cons-holding-slot-description)
                              last-system-defined-slot-description)
                      (setq last-system-defined-slot-description
                            class-level-slot-description))
                    (setf (car cons-holding-slot-description)
                          class-level-slot-description))
                  ;; Note that this code implements the choice that system slots
                  ;; will be grouped before user defined slots.  If we wanted to
                  ;; change this choice, this is where to do it.  -jra 11/2/94
                  (let* ((preceding-slot-description-for-positioning
                           (if last-system-defined-slot-description
                               last-system-defined-slot-description
                               (let ((last-slot-description-in-list
                                       (car
                                         (last slot-descriptions-working-list))))
                                 (if (user-defined-slot-description-p
                                       last-slot-description-in-list)
                                     (loop for sublist on
                                           slot-descriptions-working-list
                                           when (user-defined-slot-description-p
                                                  (second sublist))
                                             return (first sublist))
                                     last-slot-description-in-list))))
                         (slot-descriptions-cons-after-which-to-insert
                           (memq preceding-slot-description-for-positioning
                                 slot-descriptions-working-list)))
                    (setf (cdr slot-descriptions-cons-after-which-to-insert)
                          (class-description-cons
                            class-level-slot-description
                            (cdr slot-descriptions-cons-after-which-to-insert)))
                    (setq last-system-defined-slot-description
                          class-level-slot-description)))))
            finally
              (setq slot-descriptions-working-list
                    (nconc slot-descriptions-working-list
                           (nreverse user-slot-descriptions-to-add)))
              (reclaim-frame-list
                superior-classes-below-merging-point-in-reverse-order?)))

    ;; Add the slot descriptions defined for the new class in the new-class-
    ;; specific-slot-descriptions list.  When called from tw-rpc code, these
    ;; slots will correspond to the class-specific-attributes for new class;
    ;; when called from defined-user-class, the list will also contain
    ;; overridden system slots.
    (loop with user-slot-descriptions-to-add = nil
          for slot-description in new-class-specific-slot-descriptions
          do
      (if (system-defined-slot-description-p slot-description)
          (let* ((unique-slot-name (unique-slot-name slot-description))
                 (cons-holding-slot-description
                   (get-appropriate-slot-descriptions-cons
                     unique-slot-name slot-descriptions-working-list)))
            (setq system-slots-overridden-by-most-refined-version
                  (frame-cons
                    unique-slot-name
                    system-slots-overridden-by-most-refined-version))
            (setf (car cons-holding-slot-description)
                  (add-inherited-features-and-indexes-to-system-slot-description
                    slot-description
                    (slot-description-from-class
                      (defining-class slot-description) unique-slot-name) t)))
          ;; The user-defined slot slot descriptions in the new-class-specific
          ;; slot descriptions are in attribute-description order.
          (let* ((user-vector-slot-index?
                  (user-vector-slot-index? slot-description))
                 (slot-description-to-add
                   (cond
                     ((fixnump user-vector-slot-index?)
                      ;; Numberp will be true when this function is called from
                      ;; alter-inheritance-of-class-without-changing-foundation-
                      ;; class.  The user-vector-slot-index? will be t when
                      ;; called from define-user-class.
                      (if (=f user-vector-slot-index?
                              current-user-vector-slot-index)
                          slot-description
                          (make-slot-description
                            (pretty-slot-name slot-description)
                            new-class new-class
                            (slot-type-specification slot-description)
                            (slot-init-form slot-description) nil
                            current-user-vector-slot-index
                            (slot-features slot-description))))
                     (t (setf (user-vector-slot-index? slot-description)
                              current-user-vector-slot-index)
                            slot-description))))
            (setq user-slot-descriptions-to-add
                  (class-description-cons
                    slot-description-to-add
                    user-slot-descriptions-to-add))
            (incff current-user-vector-slot-index)))
          finally
            (setq slot-descriptions-working-list
                  (nconc slot-descriptions-working-list
                         (nreverse user-slot-descriptions-to-add))))

    ;; Add the system-defined slot-descriptions that are in the slot-
    ;; descriptions-for-overridden-slots? list.
    (loop for slot-description in slot-descriptions-for-overridden-slots?
          do
      (when (system-defined-slot-description-p slot-description)
        (let* ((unique-slot-name (unique-slot-name slot-description))
               (cons-holding-slot-description
                 (get-appropriate-slot-descriptions-cons
                   unique-slot-name slot-descriptions-working-list)))
          (setq system-slots-overridden-by-most-refined-version
                (frame-cons
                  unique-slot-name
                  system-slots-overridden-by-most-refined-version))
          (setf (car cons-holding-slot-description)
                slot-description))))

    ;; replace the system-defined slot descriptions on the working list with
    ;; the override slot descriptions for the user-defined superior classes
    ;; more refined than the superior-merging-point class.  The list is
    ;; arranged from most specific to least specific.
    (when user-superior-classes-below-merging-point?
      (loop for superior in user-superior-classes-below-merging-point?
            for superior-class-description = (class-description superior)
            do
        (loop for unique-slot-name in (inherited-slots-this-class-overrides
                                        superior-class-description)
              for superior-slot-description? = (get-slot-description-of-class-description
                                                 unique-slot-name superior-class-description)
              do
          (when superior-slot-description?
            (unless (memq unique-slot-name
                          system-slots-overridden-by-most-refined-version)
              (let ((working-list-slot-description
                      (get-slot-description
                        unique-slot-name slot-descriptions-working-list)))
                (when (system-defined-slot-description-p
                        working-list-slot-description)
                  (setq system-slots-overridden-by-most-refined-version
                        (frame-cons unique-slot-name
                                    system-slots-overridden-by-most-refined-version))
                  (let ((cons-holding-slot-description
                          (memq working-list-slot-description
                                slot-descriptions-working-list)))
                    (setf (car cons-holding-slot-description)
                          (get-slot-description-of-class-description
                            unique-slot-name superior-class-description))))))))
            finally
              (reclaim-frame-list
                user-superior-classes-below-merging-point?)))
    (when system-slots-overridden-by-most-refined-version
      (reclaim-frame-list
        system-slots-overridden-by-most-refined-version))

    (values slot-descriptions-working-list current-user-vector-slot-index)))

;; Note (by GHW about the form added above and Bug HQ-3307363): The problem is
;; in merge-slot-descriptions-for-user-defined-class.  The user class has
;; digital-clock for a direct-superior, and digital-clock's direct-superior is
;; readout-table. Digital-clock overrides the readout-table-display-value slot
;; it inherits from table.
;;
;; System-defined slot-descriptions are added to the new class from
;; least-specific system-defined superior to most-specific system-defined
;; superior.  So readout-table's readout-table-display-value slot-description is
;; added to the working list of slot descriptions for the new class first, and
;; then it is replaced by digital-clock's overriding slot description.  The
;; problem is that the slot description for readout-table-display-value is the
;; last system-defined slot-description in the working list, but the code fails
;; to update the value of the local variable
;; last-system-defined-slot-description with the slot description from
;; digital-clock.  The value of that variable remains the slot description from
;; readout-table which is no longer in the slot-description list, and this
;; causes the cons error. [By GHW, 3/2/00, from Bug HQ-3307363 (MHD 3/2/00)]




;;; `Add-inherited-features-and-indexes-to-system-slot-description' adds
;;; the necessary slot features to system-defined slot descriptions that
;;; are been refined by a new class.

(defun add-inherited-features-and-indexes-to-system-slot-description
       (slot-description superior-slot-description user-defined-class?)
  (setf (vector-slot-index? slot-description)
        (vector-slot-index? superior-slot-description))
  (loop with slot-features = (slot-features slot-description)
        with superior-slot-features = (slot-features superior-slot-description)
        for superior-feature in superior-slot-features
        when (not (feature-assq (first superior-feature) slot-features))
          do
        (setf (slot-features slot-description)
              (if user-defined-class?
                  (class-description-cons
                    (copy-tree-using-class-description-conses superior-feature)
                    (slot-features slot-description))
                  (nconc (slot-features slot-description)
                         (permanent-list superior-feature)))))
  slot-description)




;;; `Check-if-superior-classes-are-defined' is called to check whether the
;;; direct superior classes of class are defined at load time.  This check
;;; is generated by expand-class-definition to be evaluated at compile,
;;; load, and eval times.  If there is an undefined direct superior class,
;;; this function signals an error.

(defun check-if-superior-classes-are-defined (class direct-superior-classes)
  (loop for direct-superior in direct-superior-classes
        do
   (unless (classp direct-superior)
      (error "The direct superior class, ~A, of class ~A is not defined.~
            ~%It was defined when this class definition was initially ~
            evaluated.~
            ~%The user is advised to recompile/load the definition of ~
            the superior class."
             direct-superior class))))




;;; `System-class-p' is true if its argument is a symbol for which there is
;;; a def-class in the software, and nil for any other symbol.

(defun system-class-p (symbol)
  (consp (class-definition symbol)))








;;;; Aliases for Slot Names



;;; `Def-slot-alias' defines an `alias' for a slot of a frame, a "user" name that
;;; differs from the "internal" slot name.  The form
;;;
;;;   (def-slot-alias pretty-slot-name alias &optional class?)
;;;
;;; creates such a definition globally.  There are no kb-specific aspects of this
;;; feature, and it is not available to other than system programmers.  If class?
;;; is nil, a global correspondence is intended.  Otherwise, the correspondence is
;;; applicable to frames of a particular class.  Since the feature has no warnings,
;;; the following constraints must be maintained by the programmer:
;;;
;;;    (1) Only one alias may be globally associated with a pretty-slot-name;
;;;
;;;    (2) An alias may be globally associated with at most one slot name;
;;;
;;;    (3) Several class-specific aliases may be specified, but they must
;;;        be for classes which are mutually disjoint on the taxonomy
;;;        (i.e., no class is a subclass of any other);
;;;
;;;    (4) An alias may be associated with several pretty-slot-names, provided
;;;        that no pair of these pretty-slot-names are slots of the same class.
;;;        The purpose of these constraints is simply to have mapping
;;;        unambiguous; and
;;;
;;;    (5) A slot must not be user visible in both an aliased and non-aliased
;;;        form.

;;; This macro is for top-level use.  The forms are unevaluated.

(def-global-property-name aliases-for-slot-name)

(def-global-property-name slot-names-for-alias)


;;; The macro `define-slot-alias' puts the arguments in the correct order.
;;; That is, "correct" because the name of the new thing that is being defined
;;; comes first.  This allows m-. to find these things.

(defmacro define-slot-alias (alias pretty-slot-name &optional class?)
  `(alias-slot-name ',pretty-slot-name ',alias ',class?))

#+development
(defvar alias-slot-name-list nil)

(defun alias-slot-name (pretty-slot-name alias &optional class?)
  #+development
  (push (list pretty-slot-name alias class?) alias-slot-name-list)
  (let ((association?
          (assq class? (aliases-for-slot-name pretty-slot-name))))
    (if association?
        (setf (cdr association?) alias)
        (push (cons class? alias)
              (aliases-for-slot-name pretty-slot-name))))
  (let ((association?
          (assq class? (slot-names-for-alias alias))))
    (if association?
        (setf (cdr association?) pretty-slot-name)
        (push (cons class? pretty-slot-name)
              (slot-names-for-alias alias)))))

#+development
(defun show-aliases ()
  (with-open-file (out "aliases.txt" :direction :output)
    (loop for alias in (reverse alias-slot-name-list)
          do (format out "~&~S~%" alias))))




;;; The system programmer who has made a mistake will need to get rid of it.
;;; This can be done by executing the function (with quoted args)
;;; unalias-slot-name.

;;; `Undef-slot-alias' does the same thing, but is a macro with quoted args.
;;; (Undef-slot-alias is an analog of def-slot-alias while unalias-slot-name
;;; is analog of alias-slot-name.)

;;; These are intended for online execution and should not be incorporated
;;; into G2 code.  They are for development environments only.

#+development
(defmacro undef-slot-alias (pretty-slot-name alias &optional class)
  `(unalias-slot-name ',pretty-slot-name ',alias ',class))

#+development
(defun unalias-slot-name (pretty-slot-name alias &optional class)
  (setf (aliases-for-slot-name pretty-slot-name)
        (delete
          (cons class alias) (aliases-for-slot-name pretty-slot-name)
          :test #'equal))
  (setf (slot-names-for-alias alias)
        (delete
          (cons class pretty-slot-name) (slot-names-for-alias alias)
          :test #'equal)))



;;; `Get-alias-for-slot-name-if-any' returns the alias for slot-name in
;;; class-or-frame, if there is one, or else nil.

(defun-simple get-alias-for-slot-name-if-any (pretty-slot-name class-or-frame)
  (let ((alist (aliases-for-slot-name pretty-slot-name)))
    (if alist                                        ; just an optimization
        (if (and (null (car (car-of-cons alist)))
                 (null (cdr alist)))
            (cdr (first alist))                        ; just an optimization
            (loop with class-description
                    = (if (symbolp class-or-frame)
                          (class-description class-or-frame)
                          (class-description-slot class-or-frame))
                  with global-alias? = nil
                  as (class? . alias) in alist
                  do (cond
                       ((null class?)
                        (setq global-alias? alias))
                       ((class-description-of-class-p class-description class?)
                        (return alias)))
                  finally (return global-alias?))))))

;; Note that make-string-that-identifies-attribute in module TABLES assumes that
;; there can be no alias for prettyslot-name if (aliases-for-slot-name
;; pretty-slot-name) is nil.




;;; `Get-slot-name-for-alias-if-any' returns the slot-name for alias in
;;; class-or-frame-or-class-description if the class is defined and there is
;;; such a slot with that alias, or else nil.

(defun-simple get-slot-name-for-alias-if-any (alias class-or-frame-or-class-description)
  (let ((alist? (slot-names-for-alias alias))
        (class-description?
          (cond ((symbolp class-or-frame-or-class-description)
                 (class-description class-or-frame-or-class-description))
                ((class-description-p class-or-frame-or-class-description)
                 class-or-frame-or-class-description)
                (t
                 (class-description-slot class-or-frame-or-class-description)))))
    ;; The check for a class-description (in addition to an alist) has been
    ;; added to deal with references to undefined classes in procedures,
    ;; rules, etc. where the attribute-name has aliases.  (ghw 3/22/94)
    (when (and alist? class-description?)
      (if (and (null (car (first alist?))) (null (cdr alist?)))
          (cdr (first alist?))                        ; just an optimization
          (loop with global-slot-name? = nil
                as (class? . pretty-slot-name) in alist?
                do (cond
                     ((null class?)
                      (setq global-slot-name? pretty-slot-name))
                     ((class-description-of-class-p class-description? class?)
                      (return pretty-slot-name)))
                finally (return global-slot-name?))))))










;;;; Method tables on class descriptions




;;; `Method-table-of-class-description' is a component on the class description
;;; of all classes.  It is an array in which each element maps to a generic
;;; system-defined method name, and the value for each element is either nil or
;;; a sub-vector which contains all the class-specific methods corresponding to
;;; the generic method defined for the classes on the class inheritance path.
;;; Each even-indexed element on a sub-vector contains the name of the class
;;; for which a class-specific method is defined, and each odd-indexed element
;;; of the sub-vector contains the corresponding class-specific methods which
;;; are function-method names in development and function-method pointers in
;;; translated G2 images.

;;; The length of each method table is the number of generic methods defined for
;;; system classes plus 1 more for an owner-class name.  The last vector element
;;; is the class for which the table was made, the most superior class having
;;; that possibly shared table.  Using a table of generic method names, each generic
;;; method name can be mapped to a generic-method id which is an index into the
;;; method table.

;;; This scheme makes it essential that each class-specific method have a
;;; corresponding generic method form, that each new generic method be registered
;;; by adding a new def-generic-method-id form below the existing def-generic
;;; method-id-forms further down in this module, that the maximum-number-of-
;;; generic-methods constant be incremented, and that a full compile is forced.






(defmacro owner-class-of-method-table (method-table)
  `(svref ,method-table maximum-number-of-generic-methods))

(defun set-owner-class-of-method-table (method-table class-name)
  (setf (svref method-table maximum-number-of-generic-methods) class-name))




;;; `Make-method-table-for-system-class' will be called for each system class
;;; from add-class-to-the-environment.  The tables entries will be initialized
;;; at the end of load-time by a top-level call to initialize-or-update-method-
;;; tables-of-class-descriptions in G2-FINAL.

(defun make-method-table-for-system-class ()
  (make-array (1+ maximum-number-of-generic-methods) :initial-element nil))




;;; `Reclaim-method-table-of-class-description' reclaims the sub-vector table
;;; values as well as the vector itself when a user-class is being undefined.

(defun-simple reclaim-method-table-of-class-description (method-table)
  (loop for index from 0 below maximum-number-of-generic-methods
        for method-table-sub-vector? = (svref method-table index)
        do
    (when method-table-sub-vector?
      (reclaim-managed-simple-vector method-table-sub-vector?)))
  (reclaim-managed-simple-vector method-table))




;;; `Table-to-map-generic-method-id-to-generic-method-name' has as its element
;;; values every generic class method name defined by def-generic-method.  The
;;; indices of this mapping table correspond to the indices of the method tables of
;;; class descriptions.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar table-to-map-generic-method-id-to-generic-method-name
  (make-array-with-nils maximum-number-of-generic-methods))

(defmacro map-generic-method-id-to-name (id)
  `(svref table-to-map-generic-method-id-to-generic-method-name ,id))

;;; `map-generic-method-name-to-id' may return NIL, which may crash the product.
;;; We need to return zero instead, and in development mode report the error.
;;; -- Chun Tian (binghe), Jun 2016.

(defmacro map-generic-method-name-to-id (generic-method-name-arg)
  (if (constantp generic-method-name-arg)
      (loop with generic-method-name = (eval generic-method-name-arg)
            for id from 0 below maximum-number-of-generic-methods
            when (eq (map-generic-method-id-to-name id)
                     generic-method-name)
              return id
            finally
              #+development
              (error "map-generic-method-name-to-id returns NIL")
	      (return id))
      `(loop with generic-method-name = ,generic-method-name-arg
             for id from 0 below maximum-number-of-generic-methods
             when (eq (map-generic-method-id-to-name id)
                      generic-method-name)
               return id
             finally
               #+development
               (error "map-generic-method-name-to-id returns NIL")
               (return id))))

(defmacro do-each-class-method-name ((method-name) &body body)
  `(loop for id from 0 below maximum-number-of-generic-methods
        as ,method-name
           = (svref table-to-map-generic-method-id-to-generic-method-name id)
        do
    (progn ,@body)))

) ; eval-when



;;; `Initialize-method-table-of-class-description' allocates the table-element
;;; sub-vectors and initializes them.  No sub-vector reclamation is done here.
;;; Reclamation of method tables for user-defined classes is dealt with in the
;;; calling function for user-defined classes, initialize-or-update-method-
;;; table-for-user-class.  No reclamation is done for system-defined classes
;;; since any system method table updating is done only during development.  See
;;; the beginning of this section for a description of the table elements.

(defun-simple initialize-method-table-of-class-description
    (method-table class-inheritance-path user-defined-class?)
  (loop for generic-method-id from 0 below maximum-number-of-generic-methods
        for generic-method-name = (map-generic-method-id-to-name generic-method-id)
        for class-specific-methods-with-name-on-path? =
              (loop for class in class-inheritance-path
                    for class-specific-method? =
                          (getfq-macro (symbol-plist-for-lookup class)
                                       generic-method-name)
                    when class-specific-method?
                      collect (frame-list class class-specific-method?)
                        using frame-cons)
        for number-of-methods-on-path =
              (length class-specific-methods-with-name-on-path?)
        for sub-vector? =
              (when class-specific-methods-with-name-on-path?
                (if user-defined-class?
                    (allocate-managed-simple-vector
                      (*f number-of-methods-on-path 2))
                    (make-array (*f number-of-methods-on-path 2))))
        do
    (if sub-vector?
        (loop for index fixnum from 0
                        below (1-f (length-of-simple-vector sub-vector?))
                        by 2
              for method-sub-list in class-specific-methods-with-name-on-path?
              do
          (setf (svref sub-vector? index) (car-of-cons method-sub-list))
          (setf (svref sub-vector? (1+f index)) (second method-sub-list))
              finally (progn
                        (reclaim-frame-tree class-specific-methods-with-name-on-path?)
                        (setf (svref method-table generic-method-id) sub-vector?)))
        (setf (svref method-table generic-method-id) nil)))
  (set-owner-class-of-method-table method-table (car class-inheritance-path)))




;;; `Method-tables-are-equivalent-p' returns table2 when the values on the
;;; subvectors of the method tables are EQ; otherwise it returns nil.

(defun method-tables-are-equivalent-p (table1 table2)
  (loop for index from 0
                  below maximum-number-of-generic-methods
        for table1-sub-vector-for-index? = (svref table1 index)
        for table1-sub-vector-length? = (when table1-sub-vector-for-index?
                                          (length-of-simple-vector
                                            table1-sub-vector-for-index?))
        for table2-sub-vector-for-index? = (svref table2 index)
        for table2-sub-vector-length? = (when table2-sub-vector-for-index?
                                          (length-of-simple-vector
                                            table2-sub-vector-for-index?))
        do
    (unless (and (null table1-sub-vector-for-index?)
                 (null table2-sub-vector-for-index?))
      (when (or (and table1-sub-vector-for-index?
                     (null table2-sub-vector-for-index?))
                (and (null table1-sub-vector-for-index?)
                     table2-sub-vector-for-index?)
                (/=f table1-sub-vector-length?
                     table2-sub-vector-length?)
                (loop for index fixnum from 0
                                below table1-sub-vector-length?
                      thereis
                      (not (eq (svref table1-sub-vector-for-index? index)
                               (svref table2-sub-vector-for-index? index)))))
        (return nil)))
        finally (return table2)))




;;; `Equivalent-method-table-on-path-p' returns the method table of the first
;;; user-defined superior class on the class inheritance path that has a method
;;; table equivalent to the table provisionally made for user-class; if
;;; there is no equivalent method table on the path, it returns nil.

(defun-simple equivalent-method-table-on-path-p
    (user-class-method-table class-inheritance-path)
  (loop for superior-class in (cdr-of-cons class-inheritance-path)
        for superior-class-method-table? =
              (when (user-defined-class-p superior-class)
                (method-table-of-class-description
                  (class-description superior-class)))
        for equivalent-method-table? =
              (and superior-class-method-table?
                   (method-tables-are-equivalent-p
                     user-class-method-table superior-class-method-table?))
        when equivalent-method-table?
          return equivalent-method-table?))




;;; `Initialize-or-update-method-table-for-user-class' always allocates and
;;; fills a new method vector for user-class.  If there is a user-defined
;;; superior class on the class inheritance path that has a table that is
;;; equivalent to the new vector, it is used for the class and the new vector
;;; is reclaimed, otherwise the new vector table will be assigned to class.  If
;;; there is a pre-existing vector table for class and that table is unique in
;;; the class hierarchy, it is reclaimed.  This function is called from
;;; add-class-to-the-environment for a new class and from
;;; initialize-or-update-method-tables-of-class-descriptions when there has
;;; been a change in the class hierarchy or class methods.

(defun initialize-or-update-method-table-for-user-class
    (user-class class-inheritance-path new-class?)
  (let* ((user-class-description (class-description user-class))
         (pre-existing-method-table-from-class-hierarchy?
           (unless new-class?
             (let ((existing-user-class-method-table?
                     (method-table-of-class-description
                       user-class-description)))
               (and existing-user-class-method-table?
                    ;; This test is necessary when the direct superiors of
                    ;; of a class are changing.
                    (subclassp
                      user-class
                      (owner-class-of-method-table
                        existing-user-class-method-table?))
                    existing-user-class-method-table?))))
         (new-method-table
           (let ((new-vector
                   (allocate-managed-simple-vector
                     (1+ maximum-number-of-generic-methods))))
             (initialize-method-table-of-class-description
               new-vector class-inheritance-path t)
             new-vector))
         (new-table-equivalent-to-existing-table?
           (and pre-existing-method-table-from-class-hierarchy?
                (method-tables-are-equivalent-p
                  new-method-table
                  pre-existing-method-table-from-class-hierarchy?)))
         (user-class-is-owner-of-pre-existing-obsolete-table?
           (when pre-existing-method-table-from-class-hierarchy?
             (unless new-table-equivalent-to-existing-table?
               (eq (owner-class-of-method-table
                     pre-existing-method-table-from-class-hierarchy?)
                   user-class))))
         (equivalent-method-table-on-path?
           (unless new-table-equivalent-to-existing-table?
             (equivalent-method-table-on-path-p
               new-method-table class-inheritance-path))))

    #+development
    (when debugging-class-description-method-table-leaks?
      (frame-push
        new-method-table unreclaimed-class-description-method-tables))

    (cond (new-class?
           ;; The value returned here for new classes is passed to make-and-change-
           ;; class-description from add-class-to-environment.
           (cond (equivalent-method-table-on-path?
                  #+development
                  (when debugging-class-description-method-table-leaks?
                    (delete-class-description-method-table-from-unreclaimed-list
                      new-method-table))
                  (reclaim-method-table-of-class-description new-method-table)
                  equivalent-method-table-on-path?)
                 (t
                  new-method-table)))
          (t
           ;; There is a change in heritance for an existing class.
           (cond (new-table-equivalent-to-existing-table?
                  #+development
                  (when debugging-class-description-method-table-leaks?
                    (delete-class-description-method-table-from-unreclaimed-list
                      new-method-table))
                  (reclaim-method-table-of-class-description new-method-table))
                 (t
                  (when user-class-is-owner-of-pre-existing-obsolete-table?
                    (let ((usable-method-table
                            (if equivalent-method-table-on-path?
                              equivalent-method-table-on-path?
                              new-method-table)))
                    #+development
                    (when debugging-class-description-method-table-leaks?
                      (delete-class-description-method-table-from-unreclaimed-list
                        pre-existing-method-table-from-class-hierarchy?))
                    (loop for class being each subclass of user-class
                          for subclass-description = (class-description class)
                          for subclass-method-table? =
                          (method-table-of-class-description subclass-description)
                          do
                      (when (and subclass-method-table?
                                 (eq subclass-method-table?
                                     pre-existing-method-table-from-class-hierarchy?))
                        (setf (method-table-of-class-description subclass-description)
                              usable-method-table))))
                    (reclaim-method-table-of-class-description
                      pre-existing-method-table-from-class-hierarchy?))
                  (cond (equivalent-method-table-on-path?
                         #+development
                         (when debugging-class-description-method-table-leaks?
                           (delete-class-description-method-table-from-unreclaimed-list
                             new-method-table))
                         (reclaim-method-table-of-class-description new-method-table)
                         (setf (method-table-of-class-description user-class-description)
                               equivalent-method-table-on-path?))
                        (t
                         (setf (method-table-of-class-description user-class-description)
                               new-method-table)))))))))




;;; `Initialize-or-update-method-tables-of-class-descriptions' is called
;;; towards the end of loading from a top-level form in G2-FINAL, when a
;;; def-class or def-class-method form is recompiled, and when there is a
;;; change in direct superiors that does not involve a foundation class change.
;;; Initialize-or-update-method-table-for-user-class is called directly when
;;; defining a user class.

(defun initialize-or-update-method-tables-of-class-descriptions (node)
  (loop for subclass being each unoptimized-subclass of node
        for subclass-description = (class-description subclass)
        for subclass-inheritance-path =
              (class-inheritance-path subclass-description)
        for subclass-method-table =
              (method-table-of-class-description subclass-description)
        do
    (if (system-defined-class-p subclass)
        (initialize-method-table-of-class-description
          subclass-method-table subclass-inheritance-path nil)
        (initialize-or-update-method-table-for-user-class
          subclass subclass-inheritance-path nil))))




;;; `Def-generic-method-id' must be executed for each generic class method that
;;; is defined by def-generic-method.  See the section below, IDs for ALL generic
;;; system methods, for information.

(defmacro def-generic-method-id (generic-method-name id)
  `(install-generic-method-id ',generic-method-name ,id))

(defun-simple install-generic-method-id (generic-method-name new-id)
  (let ((old-name (map-generic-method-id-to-name new-id)))
    (cond ((or (not (symbolp generic-method-name))
               (not (fixnump new-id))
               (not (<f -1 new-id maximum-number-of-generic-methods)))
           (error "Bad generic-method-name symbol or id: name = ~a, id = ~a."
                  generic-method-name new-id))
          ((and old-name (not (eq old-name generic-method-name)))
           (warn "Changing generic-method id number ~a from ~a to ~a."
                 new-id old-name generic-method-name)))
    (setf (map-generic-method-id-to-name new-id) generic-method-name)
    generic-method-name))






;;; `IDs for ALL generic system methods'

;;; The calls to def-generic-method-id are currently sorted by the number of
;;; specific-class methods defined for that generic method.  Please add new
;;; def-generic-method-id forms to the end, increment the value of the constant
;;; maximum-number-of-generic-methods, and recompile.

(def-generic-method-id generate-spot 0)
(def-generic-method-id cleanup 1)
(def-generic-method-id initialize 2)
(def-generic-method-id analyze-for-consistency 3)
(def-generic-method-id initialize-after-reading 4)
(def-generic-method-id draw 5)
(def-generic-method-id activate 6)
(def-generic-method-id deactivate 7)
(def-generic-method-id install-system-table 8)
(def-generic-method-id deinstall-system-table 9)
(def-generic-method-id note-name-change 10)
(def-generic-method-id denote-cell-array-element 11)
(def-generic-method-id expression-cell-updated 12)
(def-generic-method-id deactivate-subclass-of-entity 13)
(def-generic-method-id activate-subclass-of-entity 14)
(def-generic-method-id describe-frame 15)
(def-generic-method-id put-box-translation-and-text-slot-value 16)
(def-generic-method-id copy-frame 17)
(def-generic-method-id note-runs-while-inactive-change 18)
(def-generic-method-id update-frame-status-and-notes 19)
(def-generic-method-id fix-frame-with-substitute-class 20)
(def-generic-method-id clear-display 21)
(def-generic-method-id update-display 22)
(def-generic-method-id click 23)
(def-generic-method-id scroll-block 24)
(def-generic-method-id compute-minimum-right-edge 25)
(def-generic-method-id compute-minimum-bottom-edge 26)
(def-generic-method-id execute-command 27)
(def-generic-method-id reformat-as-appropriate 28)
(def-generic-method-id update-cell-based-display 29)
(def-generic-method-id activate-if-possible-and-propagate 30)
(def-generic-method-id deactivate-and-propagate 31)
(def-generic-method-id shift 32)
(def-generic-method-id assert-frame-notes 33)
(def-generic-method-id retract-frame-notes 34)
(def-generic-method-id resize 35)
(def-generic-method-id place-reference-of-cell 36)
(def-generic-method-id recompile-expression-at-component-particulars 37)
(def-generic-method-id note-may-refer-to-inactive-items-change 38)
(def-generic-method-id reconsider-formatting 39)
(def-generic-method-id strip-text 40)
(def-generic-method-id handle-end-operation 41)
(def-generic-method-id add-items-to-edit-workspace 42)
(def-generic-method-id query-cell-updated 43)
(def-generic-method-id designation-cell-updated 44)
(def-generic-method-id generate-designation-of-cell 45)
(def-generic-method-id update-part-dependencies 46)
(def-generic-method-id manually-disable 47)
(def-generic-method-id manually-enable 48)
(def-generic-method-id handle-change-or-deletion-fanout 49)
(def-generic-method-id change-size-per-bounding-rectangle 50)
(def-generic-method-id restore-history-buffer 51)
(def-generic-method-id get-workspace-representation-type 52)
(def-generic-method-id note-ancestor-not-activatable 53)
(def-generic-method-id note-ancestor-manually-enabled 54)
(def-generic-method-id prepare-to-saving-frame 55)
(def-generic-method-id on-frame-saved 56)





;;;; Class Methods



;;;  (def-class-method <method-name> (<class> . <args>) &body <body>)
;;;  Defines a <method-name> method for class <class>.

;;;  (forget-class-method <method-name> <class>)
;;;  Undoes def-class-method. Forget the <method> method of class <class>.

;;;  (forget-method <method-name>)
;;;  Completely removes the method from the environment.

;;;  (funcall-method <method-name> <frame> &rest <args>)
;;;  Funcalls the definition of the method applicaple to the frame on the frame and args.
;;;  This is the most common way to invoke methods.

;;;  (funcall-method-macro <method-name> <frame> &rest <args>)
;;;  Expands into a form which behaves as does funcall-method.

;;;  (funcall-method-if-any <method-name> <frame> &rest <args>)
;;;  If the class of <frames> as a <method-name> method, the applicable method is
;;;  funcalled on <frame> and <args>, otherwise no-op and return nil.

;;;  (funcall-method-if-any-macro <method-name> <frame> &rest <args>)
;;;  Expands into a form which behaves as does funcall-method-if-any.

;;;  (apply-method <method-name> <args>)
;;;  Applies the definition of the method applicaple to the frame to the frame and args.

;;;  (apply-method-macro <method-name> <args>)
;;;  Expands into a form which behaves as does apply-method.

;;;  (apply-method-if-any <method-name> <args>)
;;;  If the class of <frames> as a <method-name> method, the applicable method is
;;;  applied to <frame> and <args>, otherwise no-op and return nil.

;;;  (apply-method-if-any-macro <method> <args>)
;;;  Expands into a form which behaves as does apply-method-if-any.

;;;  (trace-methods {<method>})
;;;  Trace methods.

;;;  (untrace-methods {<method>})
;;;  Untrace methods.

;;;  (trace-class-methods <class> &rest <methods>)
;;;  Given a class, trace the methods of <methods> applicable to class <class>.

;;;  (untrace-class-methods <class> &rest <methods>)
;;;  Given a class, untrace the methods of <methods> applicable to class <class>.



;;; A method is a means of performing a general operation on, or with, a frame in a
;;; manner specific to the class of which the frame is an instance. Methods are similar
;;; to functions. They evaluate their actual arguments and bind them to their parameters.
;;; The parameters are lexically bound within the scope of the method within which the
;;; body of the method is evaluated. The value or values of the last evaluated form of
;;; the body are then returned as the value of the application of the method. Unlike
;;; functions, the first argument to an application of a method must be a frame. Methods
;;; must have at least one argument, a frame. It is an error to apply a method to an
;;; instance of a class for which no such method is defined or inherited.

;;; Inheritance of methods is similar to inheritance of slots. When a method is defined
;;; for a class it is inherited by all subclasses of the class which do not have a more
;;; specific method of the same name, defined or inherited. A method is more specific
;;; to a class than another method when the inheritance path between the class for which
;;; the former was defined and the class is shorter than the inheritance path between the
;;; class for which the latter was defined and the class. When a class is defined it
;;; inherits from its parent all methods for which it does not already have a definition.
;;; When a class is redefined all methods defined or inherited by it are uninherited and
;;; undefined and then the methods of its new parent are inherited and its own methods
;;; are redefined. Thus at all times all method inheritance retains its intergrety.

;;; Methods are almost as efficient as are functions. In all cases it takes the same
;;; amount of time to reference the definition of a defined or inherited method. This
;;; is due to the application of the general philosophy behind this frame system. In all
;;; cases as much as possible is done to insure at definition time that as little as
;;; possible will have to be done while manipulating frames, slots and methods. In this
;;; sense the frame system compiles whatever it can.

;; Originally def-class-method allowed accesses to shadowed methods via a local
;; function called shadowed. (shadowed <method>) would return the definition
;; of <method> which was shadowed by some method, including the method being
;; defined, which could then be applied or funcall'ed on the class to which the
;; defined method was to be attached. This was abandoned on advice from Mark David.
;; Mark feels that this implementation of frames should be so restricted to exclude
;; shadowed methods for reasons of efficiency. Also he has brought to my attention
;; that flet, which was used to define shadowed, is difficult to impliment and may
;; be flaky in some implementations of Common LISP. If anyone whould like the
;; shadowed capability, please let me know and we can all discuss the benifits and
;; ills of such an extension. -sd- October 10, 1986.







;;; The function for macro `function-name-for-method' takes a symbol naming a
;;; class and a symbol naming a method, and returns the symbol which names the
;;; function implementing the specific method for the given class.  Note that
;;; this is an internal of the frame system, which currently has to be used by
;;; displays.  Displays should be changed to not use this operation as soon as
;;; possible.  -jra 2/21/91

(defun-for-macro function-name-for-method (class method)
  (intern (format nil "~A-FOR-~A" method class)))




;;; `Generic-method-lambda-list' (a global property name) is discussed below with
;;; `def-generic-method.'

(def-global-property-name generic-method-lambda-list)




;;; `Def-generic-method' is analagous to CLOS's defgeneric.  It is used to provide a
;;; place the common information about a family of methods maybe defined.  It takes a
;;; method-name, a lambda-list, and some number of options.  Def-class-method will
;;; complain if individual methods are not congruent with this lambda list.

;;; A lambda list is congruent if `congruent-lambda-list-p' defined below is true.

;;; The options are specified by lists who's car is a keyword.  Currently there are
;;; no options.

(defmacro def-generic-method (method-name lambda-list &body options)
  (unless (map-generic-method-name-to-id method-name)
    (warn "~S should have a def-generic-method-id form, the ~
             maximum-number-of-generic-methods constant should be
             incremented, and there should be a recompile."
           method-name))
  (loop for option in options
        do
        (cond
          ((or (atom option)
               (not (keywordp (car option))))
           (format t "All def-generic-method options must be of the form (<keyword> ...)"))
          ((not (memq (car option) '()))
           (format t "~S is not a supported option of def-generic-method" (car option)))))
  `(progn
     #+development
     (register-definition ',method-name 'def-generic-method)
     (setf (generic-method-lambda-list ',method-name)
         ',lambda-list)))




;;; `Def-class-method' is used to define a method applicable to instances
;;; of a class.  Methods shadow other methods of the same name in the usual
;;; manner.

(def-concept funcall-superior-method)

;;; The shadowed method may be called via the macro `funcall-superior-method'
;;; passing the frame and any additional arguments.

;;; For example:
;;;   (def-class-method shut-down (widgit operator)
;;;     (power-down-the-grits (grits widget))
;;;     (funcall-superior-method widget operator)
;;;     (disable-the-grits (grits widget)))

#+(and lispworks (not chestnut-3))
(dspec:define-form-parser def-class-method (operation class-and-args)
    `(,def-class-method ,operation ,(car class-and-args)))

(defmacro def-class-method (operation (class &rest args) &body body)
  (let ((function-name (function-name-for-method class operation))
        (generic-lambda-list (generic-method-lambda-list operation)))
    (unless (map-generic-method-name-to-id operation)
      (warn "The ~S method on ~S will not be called because there is no corresponding ~
             generic-method definition." operation class))
    (when (and generic-lambda-list
               (not (congruent-lambda-list-p generic-lambda-list `(class ,@args))))
      (warn "The ~S method on ~S is not congruent with it's generic definition, i.e. ~S"
            operation class generic-lambda-list))
    (multiple-value-bind (declarations-and-documentation rest-of-body)
        (split-declarations-and-documentation-from-statements body)
      `(progn
         (declare-function-type
           ,function-name
           ,(loop repeat (1+ (length args)) collect t)
           *)

        (defun ,function-name (,class ,@args)
          ,@declarations-and-documentation
          (macrolet
              ((funcall-superior-method
                   (frame &rest args)
                 (list 'funcall-superior-method-1
                       '',class
                       '',operation
                       frame
                       args)))
            ,@rest-of-body))

        (setf (get ',class ',operation)
              #+development
              ',function-name
              #-development
              #',function-name)

        #+development
        (pushnew ',class (classes-which-define ',operation))
        #-development
        (push ',class (classes-which-define ',operation))
        #+development
        (when system-class-method-tables-processed?
          (initialize-or-update-method-tables-of-class-descriptions ',class))
        ',operation))))




;;; `Funcall-superior-method-1'  Class-with-specific-method must be a class that
;;; defines its own method for operation.  This is only intended to be called
;;; from funcall-superior-method (local) macros defined within def-class-method.

;;; Note that this is a non-standard macro for the arguments
;;; class-with-specific-method and operation.  It is assumed that these
;;; arguments are always constants and so can be evaluated out of order and
;;; multiple times.

(defmacro funcall-superior-method-1
    (class-with-specific-method operation frame args)
  (when (and (constantp frame) (symbolp (eval frame)))
    (warn "Funcall-superior-method received ~a, not a frame." frame))
  (let ((frame-evaled (gensym-make-symbol "FRAME"))
        (method-function? (gensym-make-symbol "METHOD-FUNCTION?"))
        (sub-vector? (gensym-make-symbol "SUB-VECTOR?")))
    `(let* ((,frame-evaled ,frame)
            (,sub-vector?
               (svref (method-table-of-class-description
                        (class-description-slot ,frame-evaled))
                      (map-generic-method-name-to-id ,operation)))
            (,method-function?
               (loop for index fixnum from 0
                               below (-f (length-of-simple-vector ,sub-vector?) 3)
                               by 2
                     do
                 (when (eq (svref ,sub-vector? index) ,class-with-specific-method)
                   (return (svref ,sub-vector? (+f index 3)))))))
       (when ,method-function?
         (funcall-simple-multi-valued-compiled-function
           ,method-function? ,frame-evaled ,@args)))))




;;; `Forget-class-method' undoes def-class-method.

#+development
(defun forget-class-method (method class)
  (setf (get class method) nil)
  (setf (classes-which-define method)
        (delete class (classes-which-define method)))
  (initialize-or-update-method-tables-of-class-descriptions class)
  nil)




;;; `Forget-method' completely erases method from the environment.

#+development
(defun forget-method (method)
  (cerror "FRAMES2" "It's now necessary to remove the def-generic-method-id ~
                     form for ~A, renumber them, and recompile" method))




;;; `Propagate-method' informs a class of its method and the each inferior class
;;; of the class, and then does the same for each inferior on all paths
;;; descending from the class for which no closer definition exists.  If
;;; this-class-defines-this-method? is non-nil, it will be noted.

;;; Note that this function is obsolete, and is being made into a noop.  If we
;;; wish to reimplement optimizations for method dispatch, then this should be
;;; brought back to life.  -jra & ghw 9/8/93

(defun propagate-method (method method-definition class
                         &optional this-class-defines-this-method?)
  (declare (ignore method method-definition class
                   this-class-defines-this-method?))
  nil)


;;; Given a source class and a target class and optionally a list of methods belonging to
;;; the source class, which default to all the methods of the source class,
;;; `propagate-methods' makes all descendants of, and including, the target class
;;; receive the methods unless the methods are intercepted by definitions closer
;;; to the subordinate classes.

;;; Note that this function is being made a noop.  If we reinstate propagation
;;; optimizations for methods, then revisit this function.  -jra & ghw 9/8/93

(defun propagate-methods (source-class target-class
                          &optional (specific-methods (class-methods source-class)))
  (declare (ignore target-class specific-methods))
  nil)



;;; `Unpropagate-methods' does the exact opposite of propagate-methods.

(defun unpropagate-methods (source-class target-class
                            &optional (specific-methods (class-methods source-class)))
  (declare (ignore target-class specific-methods))
  nil)


;; Note that the call to remove above will need to be removed itself when frames
;; are fixed to not create garbage!!!  -jra 1/20/89




;;; `Copy-methods' copies all methods of the source class to the destination class.
;;; All source methods for which there is a locally defined method in the destination
;;; class are not copied.

(defun copy-methods (source-class target-class)
  (declare (ignore source-class target-class))
  nil)





;;; `Funcall-method' funcalls the definition of the method relative to the class of the
;;; frame on the arguments with frame being the first argument.

;; This should be a macro.  -jra 9/8/93

(defmacro funcall-method (method frame &rest args)
  #+development
  (let ((method-arg (gensym-make-symbol "METHOD"))
        (frame-arg (gensym-make-symbol "FRAME"))
        (method-table-sub-vector? (gensym-make-symbol "SUB-VECTOR?"))
        (function-to-apply? (gensym-make-symbol "FUNCTION?")))
    `(let* ((,method-arg ,method)
            (,frame-arg ,frame)
            (,method-table-sub-vector?
               (svref
                 (method-table-of-class-description
                   (class-description-slot ,frame-arg))
                 (map-generic-method-name-to-id ,method-arg)))
            (,function-to-apply?
               (when ,method-table-sub-vector?
                 (svref ,method-table-sub-vector? 1))))
       (if ,function-to-apply?
           (funcall-simple-multi-valued-compiled-function
             (symbol-function ,function-to-apply?) ,frame-arg ,@args)
           (warn-of-invalid-frame-method-association
             (class ,frame-arg) ,method-arg))))
  #-development
  (if (and (or (constantp method) (symbolp method))
           (or (constantp frame) (symbolp frame)))
      `(funcall-simple-multi-valued-compiled-function
         (svref
           (svref (method-table-of-class-description
                    (class-description-slot ,frame))
                  (map-generic-method-name-to-id ,method))
           1)
         ,frame ,@args)
      (let ((method-arg (gensym-make-symbol "METHOD"))
            (frame-arg (gensym-make-symbol "FRAME")))
        `(let ((,method-arg ,method)
               (,frame-arg ,frame))
           (funcall-simple-multi-valued-compiled-function
             (svref
               (svref (method-table-of-class-description
                        (class-description-slot ,frame-arg))
                      (map-generic-method-name-to-id ,method-arg))
               1)
             ,frame-arg ,@args)))))




;;; `Funcall-method-macro' is a macro-expanded equivalent of funcall-method.

(defmacro funcall-method-macro (method frame &rest args)
  `(funcall-method ,method ,frame ,@args))



;;; `Funcall-simple-method-macro' is a macro-expanded equivalent of
;;; funcall-method, except that the methods must meet the same criteria that
;;; simple functions meet; that they take a fixed number of arguments and return
;;; a single value.

;; This is the most efficient method dispatch mechanism that we currently have.
;; -jra 6/24/92

;; Note that funcall-method is now competative with this.  The only difference
;; is that funcall-method could return multiple values.  -jra & ghw 9/8/93

(defmacro funcall-simple-method-macro (method frame &rest args)
  #+development
  (let ((method-arg (gensym-make-symbol "METHOD"))
        (frame-arg (gensym-make-symbol "FRAME"))
        (method-table-sub-vector? (gensym-make-symbol "SUB-VECTOR?"))
        (function-to-apply? (gensym-make-symbol "FUNCTION?")))
    `(let* ((,method-arg ,method)
            (,frame-arg ,frame)
            (,method-table-sub-vector?
               (svref
                 (method-table-of-class-description
                   (class-description-slot ,frame-arg))
                 (map-generic-method-name-to-id ,method-arg)))
            (,function-to-apply?
               (when ,method-table-sub-vector?
                 (svref ,method-table-sub-vector? 1))))
       (if ,function-to-apply?
           (funcall-simple-compiled-function
             (symbol-function ,function-to-apply?) ,frame-arg ,@args)
           (warn-of-invalid-frame-method-association
             (class ,frame-arg) ,method-arg))))
  #-development
  (if (and (or (constantp method) (symbolp method))
           (or (constantp frame) (symbolp frame)))
      `(funcall-simple-multi-valued-compiled-function
         (svref
           (svref (method-table-of-class-description
                    (class-description-slot ,frame))
                  (map-generic-method-name-to-id ,method))
           1)
         ,frame ,@args)
      (let ((method-arg (gensym-make-symbol "METHOD"))
            (frame-arg (gensym-make-symbol "FRAME")))
        `(let ((,method-arg ,method)
               (,frame-arg ,frame))
           (funcall-simple-multi-valued-compiled-function
             (svref
               (svref (method-table-of-class-description
                        (class-description-slot ,frame-arg))
                      (map-generic-method-name-to-id ,method-arg))
               1)
             ,frame-arg ,@args)))))




;;; `Funcall-method-if-any' behaves as funcall-method behaves except that it handles the
;;; condition of the nondefinition of method by returning nil rather than signaling an
;;; error.

(defmacro funcall-method-if-any (method frame &rest args)
  (let ((method-index (gensym-make-symbol "METHOD-INDEX"))
        (frame-arg (gensym-make-symbol "FRAME"))
        (method-table-sub-vector? (gensym-make-symbol "SUB-VECTOR?"))
        (function-to-apply? (gensym-make-symbol "FUNCTION?")))
    `(let* ((,method-index (map-generic-method-name-to-id ,method))
            (,frame-arg ,frame)
            (,method-table-sub-vector?
               (svref
                 (method-table-of-class-description
                   (class-description-slot ,frame-arg))
                 ,method-index))
            (,function-to-apply?
               (when ,method-table-sub-vector?
                 (svref ,method-table-sub-vector? 1))))
       (declare (type fixnum ,method-index))
       (if ,function-to-apply?
            (funcall-simple-multi-valued-compiled-function
             #+development (symbol-function ,function-to-apply?)
             #-development ,function-to-apply?
             ,frame-arg ,@args)
           nil))))




;;; `Funcall-method-if-any-macro' is a macro-expanded equivalent of
;;; funcall-method-if-any.

(defmacro funcall-method-if-any-macro (method frame &rest args)
  `(funcall-method-if-any ,method ,frame ,@args))




;;; `Funcall-simple-method-if-any-macro' is a macro-expanded equivalent of
;;; funcall-method-if-any that operates on macros which meet the same criteria
;;; for simple that functions meet, i.e. that they take a fixed number of
;;; required arguments.

(defmacro funcall-simple-method-if-any-macro (method frame &rest args)
  (let ((method-index (gensym-make-symbol "METHOD-INDEX"))
        (frame-arg (gensym-make-symbol "FRAME"))
        (method-table-sub-vector? (gensym-make-symbol "SUB-VECTOR?"))
        (function-to-apply? (gensym-make-symbol "FUNCTION?")))
    `(let* ((,method-index (map-generic-method-name-to-id ,method))
            (,frame-arg ,frame)
            (,method-table-sub-vector?
               (svref
                 (method-table-of-class-description
                   (class-description-slot ,frame-arg))
                 ,method-index))
            (,function-to-apply?
               (when ,method-table-sub-vector?
                 (svref ,method-table-sub-vector? 1))))
       (declare (type fixnum ,method-index))
       (if ,function-to-apply?
           (funcall-simple-compiled-function
             #+development (symbol-function ,function-to-apply?)
             #-development ,function-to-apply?
             ,frame-arg ,@args)
           nil))))








;;;; Tracing Methods (for development only)



;;; `Trace-methods' expands into that which trace would have expanded into if given each of
;;; the class defintions of the methods to which it was applied. Thus trace-methods allows
;;; the tracing of methods.

;; Although these definitions are for development only, I have found them quite
;; useful and would suggest that they remain. SD

#+development
(defmacro trace-methods (&rest methods)
  `(trace ,@(loop for method in methods
                  nconcing (loop for class in (classes-which-define method)
                                 collecting (get class method)))))



;;; `Untrace-methods' untraces the methods supplied if they were previously traced using
;;; trace-methods.

#+development
(defmacro untrace-methods (&rest methods)
  `(untrace ,@(loop for method in methods
                    nconcing (loop for class in (classes-which-define method)
                                   collecting (get class method)))))



;;; `Trace-class-methods' traces the methods supplied relative the specified class only.

#+development
(defmacro trace-class-methods (class &rest methods)
  `(trace ,@(loop for method in methods
                  collecting (get class method))))



;;; `Untrace-class-methods' untraces the methods supplied relative to the specified class
;;; only.

#+development
(defmacro untrace-class-methods (class &rest methods)
  `(untrace ,@(loop for method in methods
                    collecting (get class method))))









;;;; Standard Methods



;;; This section specifies certain standard methods.

;; BAH would like to be able to meta-. on, say, SHIFT and go to the spec for
;; the shift method below.  Consider achieving this through some specifying
;; macro, e.g., (def-method-spec shift), which only takes up space in
;; development.  (MHD 4/3/91)



;;; The `shift' method ...



;;; The `draw' method ...



;;; The `initialize' method ....
;;;
;;; Generally, for any class X, body should begin with the expression
;;;
;;;    (funcall-superior-method x)
;;;
;;; This convention ensures that initialization begins with the most general
;;; initializations, defined by the most general classes, and ends with the
;;; most specific.  Any initialize method should expect to be called from
;;; within more specific initialize methods for more specific classes, and
;;; should behave accordingly.






;;;; Slots




;;; The macro `find-slot-index-in-lookup-structure' returns the index for the
;;; value of the slot named slot-name in lookup-structure if there is one.
;;; Otherwise, it returns nil.

(defun-substitution-macro find-slot-index-in-lookup-structure
    (frame lookup-structure slot-name)
  (let ((max-i (length-of-simple-vector lookup-structure)))
    (declare (type fixnum max-i))
    (setq max-i (-f max-i 1))
  (loop for i from (class-user-vector-length (class-description-slot frame))
                below max-i 
              by 2
        when (eq (svref lookup-structure i) slot-name)
          return (+f i 1))))


;;; `Look-up-slot-value-else-compute-default' looks up a value for slot-name in
;;; frame's lookup structure and returns that value provided there is such a
;;; value.  Otherwise, it returns the value of evaluating
;;; form-that-computes-default.  Note that form-that-computes-default is not
;;; evaluated at all if the value can be looked up.

(defmacro look-up-slot-value-else-compute-default
    (frame slot-name form-that-computes-default)
  (avoiding-variable-capture (frame slot-name &aux lookup-structure? slot-index?)
    `(let* ((,lookup-structure? (lookup-structure ,frame)))
       (if ,lookup-structure?
           (let ((,slot-index?
                    (find-slot-index-in-lookup-structure ,frame ,lookup-structure? ,slot-name)))
             (if ,slot-index?
                 (svref ,lookup-structure? ,slot-index?)
                 ,form-that-computes-default))
           ,form-that-computes-default))))



;;; The macro `get-slot-description-value-macro' takes a frame and a slot
;;; description from the class of that frame, and returns the value stored in
;;; that slot for this frame.  Note that this is faster than get-slot-value,
;;; when you already have the slot-description in hand.  The function
;;; `get-slot-description-value' is a functionized version of the same
;;; operation.

(def-substitution-macro get-slot-description-value-macro
                        (frame slot-description)
  (let ((vector-slot-index? (vector-slot-index? slot-description)))
    (if vector-slot-index?
        (svref frame vector-slot-index?)
        (let ((user-vector-slot-index?
                (user-vector-slot-index? slot-description)))
          (if user-vector-slot-index?
              (svref (lookup-structure frame) user-vector-slot-index?)
              (look-up-slot-value-else-compute-default
                frame (unique-slot-name slot-description)
                (slot-init-form slot-description)))))))

(declare-side-effect-free-function get-slot-description-value)

(defun-simple get-slot-description-value (frame slot-description)
  (get-slot-description-value-macro frame slot-description))


;;; `get-user-slot-description-value' is a fast and small
;;; accessor that can be called from code that is already so complex
;;; and powerful that it is absolutely sure the slot-description
;;; describes a user-defined slot.

(defmacro get-user-slot-description-value (frame slot-description)
  `(svref (lookup-structure ,frame) (user-vector-slot-index? ,slot-description)))


;;; The simple function `get-lookup-slot-value-given-default' takes a frame, a
;;; slot-name, and a default-value.  When the frame lookup structure has a
;;; value for the slot name, it is returned; otherwise the default-value
;;; argument is returned.  The simple function `get-lookup-slot-value' takes a
;;; frame and a slot-name, but will find its own default value if there is no
;;; specific value on this frame.  This function is an improvement over
;;; get-slot-value only because it declines to get the slot-description when
;;; there is a specific value on the given frame.

(defun-simple get-lookup-slot-value-given-default (frame slot-name default-value)
  ;; Gensym-122 fix
  (if (null frame) default-value 
      (look-up-slot-value-else-compute-default frame slot-name default-value)))

(defun-simple get-lookup-slot-value (frame slot-name)
  (look-up-slot-value-else-compute-default
    frame slot-name
    (slot-init-form (get-slot-description-of-frame slot-name frame))))




;;; The macro `get-user-vector-slot-index-value-macro' is used to reference a
;;; user attribute value when the vector-index is already known.  This macro
;;; assumes that the lookup structure is present for the item and the index is
;;; valid.

(def-substitution-macro get-user-vector-slot-index-value-macro
                        (frame user-vector-slot-index)
  (svref (lookup-structure frame) user-vector-slot-index))




;;; `Get-slot-value' returns the value stored in the given slot of the frame.
;;; Get-slot-value signals an error if there is no such slot.

(defmacro get-slot-value
    (frame unique-or-pretty-slot-name &optional class-if-specific?)
  `(get-slot-value-function
     ,frame ,unique-or-pretty-slot-name ,class-if-specific?))

(declare-side-effect-free-function get-slot-value-function)

(defun-simple get-slot-value-function
    (frame unique-or-pretty-slot-name class-if-specific?)
  (let* ((slot-description?
           (get-slot-description-of-frame
             unique-or-pretty-slot-name frame class-if-specific?)))
    (if slot-description?
        (get-slot-description-value-macro frame slot-description?)
        (error "Frame ~S has no ~A slot" frame unique-or-pretty-slot-name))))




;;; `Get-slot-value-if-any' returns the value stored in the given slot of the frame.
;;; If there is no such slot, get-slot-value-if-any returns nil.

(defmacro get-slot-value-if-any
    (frame unique-or-pretty-slot-name &optional class-if-specific?)
  `(get-slot-value-if-any-function
     ,frame ,unique-or-pretty-slot-name ,class-if-specific?))

(declare-side-effect-free-function get-slot-value-if-any-function)

(defun-simple get-slot-value-if-any-function
    (frame unique-or-pretty-slot-name class-if-specific?)
  (let ((slot-description?
          (get-slot-description-of-frame
            unique-or-pretty-slot-name frame class-if-specific?)))
    (if slot-description?
        (get-slot-description-value-macro frame slot-description?))))




;;; `get-slot-value-or-no-slot' returns the slot value if any, else
;;; it returns the value of the defconstant no-slot. Use this function
;;; when it is necessary to distinguish no slot from a null slot value.
;;; Obviously, this value must not be mutated.

(defparameter no-slot '(no-slot))

(defmacro get-slot-value-or-no-slot
    (frame unique-or-pretty-slot-name &optional class-if-specific?)
  `(get-slot-value-or-no-slot-function
     ,frame ,unique-or-pretty-slot-name ,class-if-specific?))

(declare-side-effect-free-function get-slot-value-or-no-slot-function)

(defun-simple get-slot-value-or-no-slot-function
    (frame unique-or-pretty-slot-name class-if-specific?)
  (let ((slot-description?
          (get-slot-description-of-frame
            unique-or-pretty-slot-name frame class-if-specific?)))
    (if slot-description?
        (get-slot-description-value-macro frame slot-description?)
        no-slot)))




(defmacro set-savable-block-lookup-slot-value
    (frame pretty-lookup-slot-name value)
  (if (symbolp frame)
      `(progn
         (note-change-to-block ,frame ,pretty-lookup-slot-name)
         (set-lookup-slot-value-1
           ,frame ,pretty-lookup-slot-name ,value))

      (let ((frame-value (gensym)))
        `(let ((,frame-value ,frame))
           (progn
             (note-change-to-block ,frame-value ,pretty-lookup-slot-name)
             (set-lookup-slot-value-1
               ,frame-value ,pretty-lookup-slot-name ,value))))))




(defun-simple set-lookup-slot-value-1 (frame pretty-lookup-slot-name value)
  (let ((slot-description?
          (get-slot-description-of-frame pretty-lookup-slot-name frame)))
    ;; GENSYMCID-608: G2 abort after clearing previous kb and loading new kb
    ;; Protect the slot-description from nil to avoid abort
    (if slot-description?
        (set-slot-description-value-without-noting
          frame slot-description? value)
        #+development
        (warn-of-missing-lookup-slot pretty-lookup-slot-name frame))))




;; Set-savable-dependent-frame-lookup-slot-value is only called by expand-
;; class-definition.

(defmacro set-savable-dependent-frame-lookup-slot-value
          (frame pretty-lookup-slot-name value)
      `(progn
         #+development
         (when noting-changes-to-kb-p
           (when (null current-block-of-dependent-frame)
             (error-message-for-dependent-frame-saving ,frame)))
         (note-change-to-dependent-frame)
         (set-lookup-slot-value-1
           ,frame ,pretty-lookup-slot-name ,value)))

(defun-simple set-non-savable-lookup-slot-value
    (frame pretty-lookup-slot-name value)
  (let ((slot-description?
          (get-slot-description-of-frame pretty-lookup-slot-name frame)))
    #+development
    (when (null slot-description?)
      (warn-of-missing-lookup-slot pretty-lookup-slot-name frame))
    (set-slot-description-value-without-noting frame slot-description? value)))




;;; The function `allocate-frame-lookup-structure-vector' takes a length
;;; required, and will allocate a managed-simple-vector long enough, but
;;; possibly rounded up to a reasonable allocation size.  It also takes a second
;;; argument that can be used to suppress the initialization of the extra
;;; elements of the array to NIL, where extra elements are those above and
;;; beyond the length requested.

;;; This function uses the same allocation scheme for rounding up sizes as is
;;; used by managed-arrays.  This means that we will get good reuse
;;; characteristics between vectors used for frames and for managed-arrays, and
;;; it simplifies this code.  See buffer-size-for-partial-buffer for
;;; documentation and rationalization about the rounding schemes.

(def-memory-allocation-schemes frame-lookup-structure-vector-allocation-schemes
    (16 1 1) (32 4 6))

(defun-simple allocate-frame-lookup-structure-vector (length dont-initialize)
  (declare (type fixnum length))
  (let* ((actual-length (buffer-size-for-partial-buffer
                          length
                          frame-lookup-structure-vector-allocation-schemes))
         (new-vector (allocate-managed-simple-vector actual-length)))
    (declare (type fixnum actual-length))
    (unless dont-initialize
      (loop for index fixnum from 0 below actual-length
            do
        (setf (svref new-vector index) nil)))
    new-vector))




;;; The macro `reclaim-frame-lookup-structure-vector' takes a vector that had
;;; been used as a lookup structure vector, and reclaims it.

(defmacro reclaim-frame-lookup-structure-vector (vector)
  `(reclaim-managed-simple-vector ,vector))




;;; The function `set-slot-description-value-without-noting' takes a frame, a
;;; slot description from the class of that frame, and a value.

;;; When the slot is implemented as a vector-slot or user-vector-slot, it sets
;;; the associated vector location to the value.

;;; For lookup slots, if the value is NEQ to its slot-init-form, it either
;;; sets the value component of an existing name-value pair or adds a new
;;; name-value pair on the lookup-portion of the lookup-structure.  When the
;;; lookup-slot value is EQ to the slot-init-form and there is an existing
;;; name-value pair, both locations are set to nil; otherwise, the
;;; lookup-structure is not altered.

;;; Value is returned.

(defun-simple set-slot-description-value-without-noting
              (frame slot-description value)
  (let ((vector-slot-index? (vector-slot-index? slot-description)))

    ;; vector slot
    (if vector-slot-index?
        (setf (svref frame vector-slot-index?) value)

        (let ((user-vector-slot-index?
                (user-vector-slot-index? slot-description))
              (lookup-structure (lookup-structure frame)))

          ;; user vector slot
          (if user-vector-slot-index?
              (setf (svref lookup-structure user-vector-slot-index?) value)

              ;; lookup slot
              (let* ((lookup-structure-length
                       (if lookup-structure
                           (length-of-simple-vector lookup-structure)
                           0))
                     (unique-slot-name (unique-slot-name slot-description))
                     (class-user-vector-length
                       (class-user-vector-length
                         (class-description-slot frame)))
                     (index class-user-vector-length)
                     (first-available-location? nil)
                     (mission-accomplished? nil))

                (declare (type fixnum
			       lookup-structure-length
			       class-user-vector-length index))

                (if (eq value (slot-init-form slot-description))
                    ;; For default slot values: if there is an existing
                    ;; name-value pair, this loop will null both locations;
                    ;; otherwise, the lookup-structure will remain unaltered.
                    ;; In either case, mission-accomplished? will be set to t.
                    (loop while (<f index lookup-structure-length)
                          for lookup-slot-name = (svref lookup-structure index)
                          do
                      (cond ((eq lookup-slot-name unique-slot-name)
                             (setf (svref lookup-structure index) nil)
                             (setf (svref lookup-structure (1+f index)) nil)
                             (setf mission-accomplished? t)
                             (loop-finish))
                            (t
                             (incff index 2)))
                          finally (setf mission-accomplished? t))
                    ;; For non-default slot values:  if there is an existing
                    ;; name-value pair, this loop will set the value location
                    ;; to value and will set mission-accomplished to t;
                    ;; otherwise, the location for the new name-value pair will
                    ;; be available in either first-available-location? or index.
                    (loop while (<f index lookup-structure-length)
                          for lookup-slot-name = (svref lookup-structure index)
                          do
                      (cond ((eq lookup-slot-name unique-slot-name)
                             (setf (svref lookup-structure (1+f index)) value)
                             (setf mission-accomplished? t)
                             (loop-finish))
                            ((and (null lookup-slot-name)
                                  (null first-available-location?))
                             (setq first-available-location? index)
                             (incff index 2))
                            (t
                             (incff index 2)))))

                ;; A value still remains to be set.  A new lookup structure will
                ;; need to be allocated if there is no first-available-location?
                ;; or if the first-available-location? is the last vector index.
                (unless mission-accomplished?
                    (cond ((and first-available-location?
                                (>f lookup-structure-length
                                    (1+f first-available-location?)))
                           (setf (svref lookup-structure first-available-location?)
                                 unique-slot-name)
                           (setf (svref lookup-structure (1+f first-available-location?))
                                 value))
                          (t
                           (let* ((entry-location (or first-available-location? index))
                                  (new-lookup-structure
                                    (allocate-frame-lookup-structure-vector
                                      (+f entry-location 2) nil)))
                             (when lookup-structure
                               (copy-simple-vector-portion
                                 lookup-structure 0 lookup-structure-length
                                 new-lookup-structure 0)
                               (reclaim-frame-lookup-structure-vector
                                 lookup-structure))
                             (setf (lookup-structure frame) new-lookup-structure)
                             (setf (svref new-lookup-structure entry-location)
                                   unique-slot-name)
                             (setf (svref new-lookup-structure (1+f entry-location))
                                   value))))))))))
  value)




;;; The macro `set-slot-description-value' is just like set-slot-value, except
;;; that it takes a slot-description of the slot to be changed, instead of the
;;; unique or pretty slot name.

(def-substitution-macro set-slot-description-value
    (frame slot-description new-value)
  (when (and noting-changes-to-kb-p
             (slot-description-is-noteworthy slot-description))
    (cond ((frame-of-class-p frame 'block)
           (note-change-to-block-1 frame (pretty-slot-name slot-description)))
          (t
           #+development
           (when (null current-block-of-dependent-frame)
             (error-message-for-dependent-frame-saving frame))
           (note-change-to-dependent-frame-1))))
  (set-slot-description-value-without-noting frame slot-description new-value))




;;; `Set-slot-value' sets the specified slot of the frame to new-value and
;;; returns new-value.  Set-slot-value signals an error if there is no such
;;; slot.  Set-slot-value is the setf method for get-slot-value.

(defmacro set-slot-value
    (frame unique-or-pretty-slot-name new-value &optional class-if-specific?)
  `(set-slot-value-function
     ,frame ,unique-or-pretty-slot-name ,new-value ,class-if-specific?))

(defun-simple set-slot-value-function
    (frame unique-or-pretty-slot-name new-value class-if-specific?)
  (let ((slot-description?
          (get-slot-description-of-frame
            unique-or-pretty-slot-name frame class-if-specific?)))
    (if slot-description?
        (set-slot-description-value frame slot-description? new-value)
        (error "Frame ~S has no ~A slot" frame unique-or-pretty-slot-name))))

(defsetf get-slot-value set-slot-value)




;;; `Initialize-slot-value' initializes the specified slot of the frame to
;;; new-value, or, if there is a slot putter for slot-name, to whatever that
;;; slot putter stores.  The stored value is returned.  It is an error for
;;; unique-or-pretty-slot-name not to designate an actual slot of frame; in
;;; development, initialize-slot-value signals an error if frame has no
;;; such slot.

(defmacro initialize-slot-value
    (frame unique-or-pretty-slot-name new-value &optional class-if-specific?)
  (avoiding-variable-capture
      (frame unique-or-pretty-slot-name new-value class-if-specific?)
    `(initialize-slot-description-value
       ,frame
       (or (get-slot-description-of-frame
             ,unique-or-pretty-slot-name ,frame ,class-if-specific?)
           #+development
           (error "Frame ~S has no ~A slot" ,Frame ,unique-or-pretty-slot-name))
       ,new-value)))

(defun-simple initialize-slot-description-value (frame slot-description new-value)
  (let* ((slot-putter?
           (get-slot-description-putter-if-any slot-description))
         (do-not-note-permanent-changes-p t))
    (cond
      ((null slot-putter?)
       (set-slot-description-value-without-noting
         frame slot-description new-value))
      ((eq slot-putter? 'put-attribute-value)
       (put-attribute-description-value
         frame slot-description new-value t))
      (t
       (funcall-simple-multi-valued-compiled-function
         slot-putter? frame new-value t)))))

#+unused
(defun-simple initialize-slot-value-function
    (frame unique-or-pretty-slot-name new-value class-if-specific?)
  (initialize-slot-value
    frame unique-or-pretty-slot-name new-value class-if-specific?))

;; Consider, For later, doing this plan: Add an arg, initialization-kind, with
;; the following spec, and fix all callers to pass it in.  This might help
;; eliminate a lot of the kludgery and confusion in the slot putters called via
;; this function, e.g., checking of the variable loading-kb-p, and the like.
;;
;; (MHD/GHW 4/28/94)
;;
;; ;;; ... Initialization-kind should be specified according to the follwing table
;; ;;;
;; ;;;    initialization kind        callers
;; ;;;    ----------------------------------------------------
;; ;;;    :creation                make-frame
;; ;;;    :redefinition                fix-icon-description-for-class-slot,
;; ;;;                                      update-slot-description,
;; ;;;                                      add-attribute-or-slot-description-to-class
;; ;;;                                      delete-attribute-from-user-class,
;; ;;;                                      restore-and-fix-class-instances-after-attribute-name-change,
;; ;;;                                      change-superior-of-class
;; ;;;    :duplication                clone-frame
;; ;;;    :recreation                read-frame-for-kb
;; ;;;
;; ;;; This is passed in as the value of the INITIALIZING? variable to the slot
;; ;;; putter.  (NOTE: the slot putters, and documentation for them, should all
;; ;;; ultimately be changed to reflect the fact that they now take an
;; ;;; initialization-kind? argument, which can be nil or any of the above, instead
;; ;;; of an initializing? boolean argument.)

;; These functions are used most heavily during the loading of a KB.

;; Eliminate initialize-slot-value-function?  I changed its one caller to use
;; initialize-slot-description-value, which I added.  I don't know that the
;; function is needed now.  (MHD 4/14/94)

;; Previously, this was documented to signal an error even in non-development,
;; but that surely had no useful function.  Looks like this should be done to
;; set-slot-value, for consistency.  I also converted this to use
;; put-attribute-description-value.  While at it, I reorganized the code
;; slightly for improved readability.  (MHD 4/13/94)




;;; `Get-slot-init-form' returns the slot init form for the slot named
;;; unique-or-pretty-slot-name for instances of class.  That is the same as the default
;;; slot value, unless it is a cons whose car is :funcall or
;;; :funcall-at-load-time.

(defun get-slot-init-form
    (class unique-or-pretty-slot-name &optional class-if-specific?)
  (let ((class-description? (class-description class)))
    (if class-description?
        (slot-init-form
          (get-slot-description-of-class-description
            unique-or-pretty-slot-name class-description? class-if-specific?)))))




;;; The macro `class' obtains the class of a frame.  The class slot has
;;; been removed from the class hierarchy in an attempt to reduce the
;;; memory requirements of G2.

(defmacro class (frame)
  `(class-name-of-class-description (class-description-slot ,frame)))

(defun class-function (frame)
  (class-name-of-class-description (class-description-slot frame)))






;;;; Slot Values



;;; A `slot value' is anything that could be the value of a slot or a "component"
;;; of the value of a slot.  A slot value may be any of the following.
;;;
;;;    slot value cons (the car and cdr of which are component slot values)
;;;
;;;    managed arrays (the elements of which are component slot values)
;;;
;;;    managed float arrays
;;;
;;;    G2 symbol
;;;
;;;    punctuation mark
;;;
;;;    nil
;;;
;;;    fixnum
;;;
;;;    managed float
;;;
;;;    permanent gensym float, for now
;;;
;;;    text string  (NOTE: Distinct from
;;;       a Common Lisp ("gensym") string)
;;;
;;;    string, for now
;;;
;;;    frame
;;;
;;;    connection
;;;
;;;    byte-code-body
;;;
;;;    a slot constant (a cons), for now
;;;
;;;    `no value' (a cons, the value of special variable no-value)
;;;
;;;    eval struct
;;;
;;;    eval sequence
;;;
;;; A `slot value cons' is a kind of cons defined by defconser.

;; Complications Having to Do with Init Forms
;;
;; Add, after "A `slot value' can be ...",
;;
;;    the value of the slot init form, i.e., an arbitrary lisp object
;;      created at read or load time by the def-class form for the
;;      class for which the slot was defined
;;
;; This will somewhat subsume the cases of permanent gensym float and
;; default slot constant.  Also, it will explain the cases like structures,
;; e.g. (icon-description entity) created with (:funcall-at-load-time ...),
;; and list structures used as initial values, e.g., line-drawing-description-
;; for-chart, which is ((graph) (chart-call-back)), or default user
;; restrictions.
;;
;; When this is done, change initializations for the following slots to be
;; constants as follows:
;;
;;     (initial-value-of-variable-or-parameter text-parameter) = ""
;;     (initial-value-of-variable-or-parameter float-parameter) = 0.0
;;     (initial-value-of-variable-or-parameter long-parameter) = 0
;;     (initial-value-of-variable-or-parameter quantity-parameter) = 0.0
;;     (initial-value-of-variable-or-parameter quantity-parameter) = 0.0
;;     (g2-array-initial-values <float, quantity, text, etc.>-array)
;;       = (<0.0, 0.0, "", etc>)
;;     .
;;     .
;;     . [Search/analize for others!]
;;
;;
;; We are giving up on having reclaimable structure inside of every single slot.
;; We are giving up on not having to go through change-slot-value to update
;; (arbitrary) slots, at least those that might have nonimmediate default slot
;; values.  We are not giving up on being able to initialize slots quickly without
;; computation and on being able not save slot values in KBs if they are EQ
;; to their slot initializations.
;;
;; Consider also not saving a slot value if its a float or a managed float,
;; and its default is a float, and it is = to its default, e.g., if they're
;; both 0.0 but not necessarily EQ.  Similarly for strings, e.g., if they're
;; both "" but not necessarily EQ.  Similarly for list structure, at least
;; "simple" list structure.  Note that this would mean that if a user "changed"
;; a value from its default, say 0.0, to the same thing, i.e., by editing the
;; slot and typing in 0.0, then the system would act as though he'd never
;; changed it and save it out as though it had remained a "default" value.
;; The difference typically only would be apparent to the user when the slot
;; is changed by the programmer between releases.  But it would cause savings
;; in space, both in memory and KB file size.  Note that this behavior has
;; always been in effect for immediate data types, i.e. fixnums and symbols.
;; Note that you could do the extended testing at various times, when saving,
;; when changing slots, when reading in a KB; it would do to just do this
;; when saving.
;;
;;
;; Somewhere it also should be noted that you should never have a system-
;; defined slot be a lookup slot that has (:funcall ...) init form.  The
;; only possible reason would be for development, where you do not want to
;; recompile all the code that may be compiled with old vector indices;
;; this would be a temporary situation, lasting a week at most.  (Perhaps
;; this can be true of user-defined slots some day as well.)
;;
;;
;; Along with the above suggestions, it should be documented that gensym
;; floats and strings may appear nonuniquely as slot values only if they
;; come from slot init forms.  When they are encountered by copy-for-slot-
;; value, they are always copied, gensym floats being copied as managed
;; floats.  However, you could imagine not copying gensym floats in copy-
;; for-slot-value -- but my hunch is that this might be problematic.
;;
;;
;; BUG: When a KB is read in and an instance of a system-defined class is
;; created, and that class has a slot with a (:funcall ...) init form, and
;; that slot did did not previously exist, or it did not previously have
;; such an init form, the slot is always initialized to nil.  A fix for this
;; is to mark these slots and flag their existstence in make-frame-without-
;; computing-slot-initializations, and have read-kb evaluate and initialize
;; them if, after reading the slots saved in the KB, it finds that they did
;; not get initialized.
;;
;;
;;
;; (MHD 3/7/91)
;;
;; Review the following comment (by LH) in light of the above!!  Review
;; "slot constants" as well!


;; Both slot constants (sharable conses used as default values for slots) and
;; gensym floats must be eliminated as kinds of slot values to get rid of
;; leakage when values for slots are parsed, compiled, and changed! (LH)




;;; Slot value conses, managed arrays, managed float arrays, managed floats, and
;;; text strings may never be shared, whether in the same or in different slot
;;; values.  Thus when a slot value is copied or reclaimed, all component slot
;;; value conses, managed arrays, managed floats, and text strings are copied or
;;; reclaimed correspondingly.

;;; On the other hand, G2 symbols, punctuation marks, nil, fixnums, frames,
;;; connections, slot constants, and "no value" may be freely shared within the
;;; same or different slot values.  These kinds of values are not copied or
;;; reclaimed when a slot value is copied or reclaimed (except that a
;;; specifically defined slot value reclaimer could, in principle, reclaim these
;;; kinds of values in certain cases).

;;; The standard suite of consing functions, macros, and variables for slot values are:
;;;
;;;    available-slot-value-conses, slot-value-cons-counter, slot-value-cons,
;;;    slot-value-cons-macro, slot-value-list, copy-tree-using-slot-value-conses,
;;;    reclaim-slot-value-cons, reclaim-slot-value-list, reclaim-slot-value-tree,
;;;    delete-slot-value-cons, delete-slot-value-element, and report-outstanding-
;;;    slot-value-conses
;;;
;;; See "Defining Consers" in module UTILITIES0 for a description of these facilities.

;;; the actual (defconser ... appears in icons due to load order chaos


;;; A `slot value float' is the default slot value representation for a
;;; float.  At present, a slot value float is represented as a managed
;;; float.  (Prior to 8/25/91 in 3.0, slot value floats were represented
;;; as gensym floats.)

;; After all code that uses slot values has been revised, as necessary, to use the
;; slot value float abstraction, and after all transformation functions in the
;; grammar and all slot value compilers have been revised, as necessary, to use the
;; phrase float abstraction, the following should be done.
;;
;;    (1) Revise the definition of "slot value float" and switch to the new
;;        definitions that implement this abstraction in terms of managed floats.
;;
;;    (2) Do likewise for "phrase float".
;;
;;    (3) Eliminate with-permanent-gensym-float-creation if no longer needed.
;;
;;    (4) Revise the definition of reclaim-slot-value as indicated therein.
;;
;;    (5) Eliminate copying-compilation-result? in modules FRAMES4 and EDIT.
;;
;; (defvar slot-value-floats-are-managed-floats? t) ; remove after next recompile! (MHD 9/16/91)

;;; `Slot-value-float-p' is true if slot-value is a slot value float.

(defmacro slot-value-float-p (slot-value)
  `(managed-float-p ,slot-value))

;;; `slot-value-long' is for G2 2015 only. -- Chun Tian (binghe), Dec 2015.

(defmacro slot-value-long-p (slot-value)
  `(managed-long-p ,slot-value))

;;; `Slot-value-float-p-function' is a funcallable version of the macro
;;; slot-value-float-p.

(defun slot-value-float-p-function (thing)
  (slot-value-float-p thing))

(defun slot-value-long-p-function (thing)
  (slot-value-long-p thing))

;; It's only now used in simple-typep.

(deftype-simple slot-value-float () '(satisfies slot-value-float-p-function))
(deftype-simple slot-value-long () '(satisfies slot-value-long-p-function))

(deftype-error-printer slot-value-float () "not a number")
(deftype-error-printer slot-value-long () "not a number")

;;; `Make-slot-value-float' makes a slot-value float equivalent in value to
;;; gensym-float.

(defun make-slot-value-float (gensym-float)
  (allocate-managed-float gensym-float))

(defun make-slot-value-long (gensym-long)
  (allocate-managed-long gensym-long))

;; This has to be a function so that it can be funcalled to initialize slot
;; values; consider having a macro version for speed-critical applications.
;; For example, the slot value floats created by reading in KB files might
;; want to use that.  (MHD 3/1/91)

;; Here's the macro.  - cpm, 8/12/94

(defmacro make-slot-value-float-macro (gensym-float)
  `(allocate-managed-float ,gensym-float))

(defmacro make-slot-value-long-macro (gensym-long)
  `(allocate-managed-long ,gensym-long))

;;; `Slot-value-number-p' is true if slot-value represents a slot value number.

(defun slot-value-number-p (slot-value)
  (or (fixnump slot-value)                        ; fixnump -- faster test presumably,
      (slot-value-float-p slot-value)             ;    although redundant with numberp
      (slot-value-long-p slot-value)
      (numberp slot-value)))

;;; `Slot-value-float-value' gets the gensym-float from slot-value-float.
;;; Note that this should only be called in a temporary context, because
;;; otherwise it will create a permanent gensym float, which would represent
;;; a leak.

(defmacro slot-value-float-value (slot-value-float)
  `(managed-float-value ,slot-value-float))

(defmacro slot-value-long-value (slot-value-long)
  `(managed-long-value ,slot-value-long))

;;; `Slot-value-number-value' gets the gensym-float from slot-value-number,
;;; if it is a slot-value-float, and otherwise just returns slot-value-number.
;;; Note that this should only be called in a temporary context, because
;;; otherwise it might create a permanent gensym float, which would represent
;;; a leak.

(def-substitution-macro slot-value-number-value (slot-value-number)
  (cond ((slot-value-float-p slot-value-number)
	 (slot-value-float-value slot-value-number))
	((slot-value-long-p slot-value-number)
	 (slot-value-long-value slot-value-number))
	(t
	 slot-value-number)))

;;; `slot-value-number-value-as-float' ...

(defmacro slot-value-number-value-as-float (slot-value)        ; to reduce retina wear-n-tear
  `(coerce-to-gensym-float (slot-value-number-value ,slot-value)))

;;; Atomic-slot-value-p is true if x is a either an atom, a slot value float,
;;; or no-value.

(defun atomic-slot-value-p (x)
  (or (atom x)
      (slot-value-float-p x)
      (slot-value-long-p x)
      (no-value-p x)))

;; Added for use in FUNCTIONS by the tabular functions facility.  (MHD 9/12/91)


;;; Slot-value-equal-p is true if
;;;
;;;    x and y are eq; or
;;;
;;;    if they are both slot value numbers,
;;;      their values are =; or
;;;
;;;    if they are both text strings,
;;;      their values are string=w; or
;;;
;;;    if at least one of them are atoms,
;;;      they are equal; or
;;;
;;;    if they are both conses,
;;;      their cars and cdrs are slot-value-equal-p
;;;
;;; Note that, in Common Lisp, (equal 1 1.0) is false, but (= 1 1.0) and (equalp
;;; 1 1.0) are both true.  (slot-value-equal-p 1 <slot-value-
;;; float-representing-1.0>) is true, since the value of <slot-value-
;;; float-representing-1.0> is 1.0, and (= 1 1.0) is true.  Thus, this is more
;;; like CL's = or equalp than equal for number comparison purposes.  This does
;;; not compare arrays as equalp does, however.  This also does not compare
;;; strings as equalp does: it uses a string= analog, rather than a string-equal
;;; analog; for example, (slot-value-equal-p "foo" "FOO") is false.

(defun slot-value-equal-p (x y)
  (or (eq x y)                                        ; opt.
      (cond
        ((and (fixnump x) (fixnump y))
         nil) ; known to be not eq
        ((and (slot-value-number-p x) (slot-value-number-p y))
         (let ((float-x
                (cond ((fixnump x)
                       (coerce-to-gensym-float (the fixnum x)))
                      ((slot-value-float-p x)
                       (managed-float-value x))
		      ((slot-value-long-p x)
		       (coerce-to-gensym-float (managed-long-value x)))
                      (t x)))
               (float-y
                (cond ((fixnump y)
                       (coerce-to-gensym-float (the fixnum y)))
                      ((slot-value-float-p y)
                       (managed-float-value y))
		      ((slot-value-long-p y)
		       (coerce-to-gensym-float (managed-long-value y)))
                      (t y))))
           (declare (type gensym-float x y))
           (=e float-x float-y)))
        ((text-string-p x)                ; added. (MHD 2/7/96)
         (and (text-string-p y)
              (string=w x y)))
        ((text-string-p y)
         (and (text-string-p x)
              (string=w x y)))
        ((atom x) ; equal descends into strings, bit-vectors, pathnames, and conses
         (and (not (symbolp x)) ; known not to be eq
              (equal x y)))
        ((atom y)
         nil)
        ((evaluation-sequence-p x)
         (and (evaluation-sequence-p y)
              (=f (evaluation-sequence-length x) (evaluation-sequence-length y))
              (loop for x-value being each evaluation-sequence-element of x
                    for y-value being each evaluation-sequence-element of y
                    always (slot-value-equal-p x-value y-value))))
        ((evaluation-structure-p x)
         (and (evaluation-structure-p y)
              (and (=f (managed-array-length (evaluation-structure-value x))
                       (managed-array-length (evaluation-structure-value y)))
                   (loop for (x-key . x-value) being each evaluation-structure-pair of x
                         for (y-key . y-value) being each evaluation-structure-pair of y
                         always
                         (if (eq x-key y-key)
                             (slot-value-equal-p x-value y-value)
                             ;; Perhaps the keys are in a different order, search the
                             ;; second structure for this key.
                             (loop for (y-key1 . y-value1)
                                       being each evaluation-structure-pair of y
                                   when (eq x-key y-key1)
                                     return (slot-value-equal-p x-value y-value1)))))))
        (t
         (and (slot-value-equal-p (car x) (car y))
              (slot-value-equal-p (cdr x) (cdr y)))))))

;; This has some similarities with tabular-function-datum-equal, in FUNCTIONS.
;; That function, however, is NOT case-sensitive.

;; Note that this function is used by find-differences-in-frames-if-any.








;;; The functions slot-value-cons-function and reclaim-slot-value-cons-function
;;; are needed as early as utilities1.

(defun slot-value-cons-function (car cdr)
  (slot-value-cons car cdr))

(defun reclaim-slot-value-cons-function (cons)
  (reclaim-slot-value-cons cons))

#+unused
(defun copy-tree-using-slot-value-conses-function (tree)
  (copy-tree-using-slot-value-conses tree))

(defun reclaim-slot-value-tree-function (tree)
  (reclaim-slot-value-tree tree))






;;; The macro `change-property-in-slot-value-plist' changes the property named
;;; by indicator to the given value.  PLISt must he a setf-table place
;;; reference to a plist composed of slot-value conses.  Property values must
;;; be slot-values, and are reclaimed by reclaim-slot-value.  The new value is
;;; returned.  If value? is NIL, then the indicator/value pair is removed.

(defmacro change-property-in-slot-value-plist (plist indicator value?)
  (avoiding-variable-capture (indicator value?)
    `(loop as l-trailer? = nil then (cdr l)
           as l = ,plist
                then (cdr l-trailer?)
           while l
           when (eq (car l) ,indicator)
             do (cond
                  (value?
                   (reclaim-slot-value (cadr l))            ; Old value must be a slot-value.
                   (setf (cadr l) ,value?))
                  (t (if l-trailer?
                         (setf (cdr l-trailer?) (cddr l))
                         (setf ,plist (cddr l)))
                     (setf (cddr l) nil)
                     (reclaim-slot-value l)))
                (return ,value?)
           finally
             (if value?
                 (setf ,plist
                       (slot-value-cons
                         indicator
                         (slot-value-cons
                           value?
                           ,plist))))
             (return ,value?))))







;;;; Slot Constants


(def-concept slot-constant)

;;; A `slot constant' is a numeric or text, non-variable attribute slot value.
;;; In addition to a slot-constant's number or text component, there is a `unit'
;;; component, which specifies the `unit of measure' or `dimension', as well as
;;; an indication of whether or not the slot-constant is a sharable default
;;; value (belonging to a class description).
;;;
;;; Slot constants only appear in user-defined attributes or definitions
;;; therefor.  See module DEFINITIONS and various grammar files for their uses.

;;; A slot-constant may be assumed to be implemented as a cons, but no further
;;; assumptions should be made (outside this section).  However, the option
;;; should be kept open to have a slot-constant recognized as a cons with a
;;; number or string as its car, so no other type of attribute value should be
;;; implemented as a cons whose car is a number or string.

;;; The current implementation of a slot constant is a cons of the form
;;;
;;;    (number-or-string unit?  .  DEFAULT-SLOT-CONSTANT), for a (sharable)
;;;    default value, or
;;;
;;;    (number-or-string unit?), for a frame-specific (non-sharable) value,
;;;    made from slot value conses and subject to recycling.

;;; If the frame that owns a non-sharable slot-constant gets deleted or a
;;; non-sharable slot-constant gets replaced, there should be no other
;;; non-transient references to it.

;;; `Make-slot-constant' makes a slot constant with components number and unit?.
;;; Default-value-case?  should be non-nil when the new slot-constant is to be
;;; used as a default value.

(defun make-slot-constant (number-or-string unit? default-value-case?)
  (if default-value-case?
      (slot-value-cons
        number-or-string
        (slot-value-cons unit? 'default-slot-constant))
      (slot-value-list number-or-string unit?)))

(defun reclaim-slot-constant (the-constant)
  (reclaim-slot-value-list* the-constant))


;; Use a different pool of conses for default slot-constants, e.g., frame conses!




;;; `Make-slot-constant-using-phrase-conses' makes a slot-constant with
;;; components number-or-string and unit?, except that it uses phrase conses
;;; instead of slot value conses.  It is needed by the attribute slot value
;;; compiler.

(defun make-slot-constant-using-phrase-conses (number-or-string unit?)
  (phrase-cons number-or-string (phrase-cons unit? nil)))




;;; `Slot-constantp' is true if slot-value is a slot-constant.  This test should
;;; only be used to test slot values that could possible be slot-constants,
;;; i.e., only those found in user-defined attributes or definitions therefor,
;;; etc.

(def-substitution-macro slot-constantp (slot-value)
  (and (consp slot-value)
       (let ((car (car-of-cons slot-value))
             (cdr (cdr-of-cons slot-value)))
         (and (consp cdr)
              (symbolp (car-of-cons cdr))
              (or (slot-value-number-p car)
                  (text-string-p car)
                  (gensym-string-p car))))))




;;; `Default-slot-constant-p' is true if cons is a default slot-constant.

(def-substitution-macro default-slot-constant-p (cons)
  (and (not (slot-value-float-p cons))
       (let ((car (car-of-cons cons))
             (cdr (cdr-of-cons cons)))
         (and (or (slot-value-number-p car)
                  (text-string-p car)
                  (gensym-string-p car))
              (consp cdr)
              (eq (cdr-of-cons cdr) 'default-slot-constant)))))

(def-substitution-macro non-float-default-slot-constant-p (cons)
  (let ((cdr (cdr-of-cons cons)))
    (and (consp cdr)
         (eq (cdr-of-cons cdr) 'default-slot-constant)
         (let ((car (car-of-cons cons)))
           (or (slot-value-number-p car)
               (text-string-p car)
               (gensym-string-p car))))))



;;; `Get-slot-value-number-or-string-from-slot-constant' returns the number
;;; component of slot-constant.

(defmacro get-slot-value-number-or-string-from-slot-constant (slot-constant)
  `(car-of-cons ,slot-constant))




;;; The function `get-slot-value-number-value-or-string-from-slot-constant'
;;; takes a slot constant and returns the string or unboxed slot number value
;;; from the slot constant.

(defun get-slot-value-number-value-or-string-from-slot-constant (slot-constant)
  (let ((value (get-slot-value-number-or-string-from-slot-constant slot-constant)))
    (if (slot-value-float-p value)
        (slot-value-float-value value)
        value)))




;;; `Get-unit-from-slot-constant' returns the unit component of slot-constant,
;;; which may be nil.

(defmacro get-unit-from-slot-constant (slot-constant)
  `(car-of-cons (cdr-of-cons ,slot-constant)))



;; For compatibility only until converting all occurances to the preceeding!!
;(defmacro get-number-from-slot-constant (slot-constant)
;  `(car ,slot-constant))

(def-substitution-macro cast-slot-constant-into-temporary-constant (slot-constant)
  (make-temporary-constant-copying-managed-value-no-expiration
    (get-slot-value-number-or-string-from-slot-constant slot-constant)
    (convert-type-or-unit-of-measure-to-type
      (get-unit-from-slot-constant slot-constant))))





;;;; Reclaiming Slot Values



(def-global-property-name slot-value-reclaimer)



;;; `Def-slot-value-reclaimer' defines a function that `reclaims' (recycles some of the
;;; structure of) the value of a slot named pretty-slot-name.  Body, which will be the function's
;;; body, refers to the value via slot-value-var, and, if listed-frame-var is specified,
;;; body may refer to the frame containing the slot via the listed variable.  A slot value
;;; reclaimer may, but need not, change the value in the slot.

;;; Slot value reclaimers are invoked when a frame is being deleted.  A slot value reclaimer
;;; for a slot is NOT invoked by CHANGE-SLOT-VALUE nor when the value of the slot is nil, a
;;; number, or (eq to) the default value for the slot.

;;; If no slot value reclaimer is defined, then a default reclaimer is used, If
;;; this a user-defined slot, reclaim-attribute-value is used.  Otherwise, i.e.,
;;; when this is a system-defined slot, reclaim-slot-value is used.

(defmacro def-slot-value-reclaimer
          (pretty-slot-name (slot-value-var . listed-frame-var) &body body)
  (let ((name (intern (format nil "RECLAIM-~A-VALUE" pretty-slot-name)))
        (frame-var (if listed-frame-var (car listed-frame-var) (gensym))))
    `(progn
       (defun-void ,name (,slot-value-var ,frame-var)
         ,@(if (null listed-frame-var) `((declare (ignore ,frame-var))))
         ,@body)
       (setf (slot-value-reclaimer ',pretty-slot-name) #',name)
       ',name)))

;; Recalling that change-slot-value does not apply the slot value reclaimer
;; it would seem likely that the slot putters would.  Inspection indicates they don't ever access
;; the slot-value-reclaimer property, so maybe they all know the name this function is
;; placed on.  Therefore it seems unlikely you can change the format these name.




;;; The slots lookup-structure and class-description-slot are reclaimed
;;; explicitly in the later parts of delete-frame, so no-op reclaimers are
;;; defined here to avoid a special case check when iterating over slot names in
;;; delete-frame.

(def-slot-value-reclaimer lookup-structure (vector?)
  vector?)

(def-slot-value-reclaimer class-description-slot (class-description)
  class-description)

(defun reclaim-initial-slot-value (slot-value)
  (cond
    ((or (symbolp slot-value)                ; handles NIL, too.
         (fixnump slot-value)
         (no-value-p slot-value))
     nil)
    ((consp slot-value)
     (let ((slot-value-cdr (cdr-of-cons slot-value)))
       (cond
         ((defined-evaluation-value-type-p slot-value-cdr)
          (funcall-simple-compiled-function
            (defined-evaluation-type-reclaimer slot-value-cdr)
            slot-value))
         (t
          (loop for slot-cons = slot-value then next-cdr
                for car-value = (car slot-cons)
                for next-cdr = (cdr slot-cons)
                do (unless (or (null car-value)
                               (symbolp car-value)
                               (fixnump car-value)
                               (no-value-p car-value))
                     (reclaim-slot-value car-value))
                while (and (consp next-cdr)
                           (neq next-cdr no-value))
                finally
                  (unless (or (symbolp next-cdr) (fixnump next-cdr))
                    (reclaim-slot-value next-cdr))
                  (reclaim-slot-value-list-given-tail
                    slot-value slot-cons))))))
    ((managed-float-p slot-value)
     (reclaim-managed-float slot-value))
    ((text-string-p slot-value)
     (reclaim-text-string slot-value))
    ((gensym-string-p slot-value)
     ;; gensym strings are now only used as constants, ala -- should not come up
     ;; here for reclamation!  (MHD 2/7/96)
     )
    ((managed-array-p slot-value)
     (loop for index from 0 below (managed-array-length slot-value)
           do (reclaim-slot-value (managed-svref slot-value index))
           finally
             (reclaim-managed-array slot-value)))
    ((managed-float-array-p slot-value)
     (reclaim-managed-float-array slot-value))
    ((byte-code-body-p slot-value)
     (reclaim-byte-code-body slot-value))
    ((of-class-p slot-value 'dependent-frame)
     (delete-frame slot-value))))




;;; `Reclaim-slot-value' reclaims slot-value and all of its non-sharable
;;; components to all levels, provided it is non-sharable.  This does not call
;;; the slot value reclaimer, only delete frame calls the slot value reclaimer.

(defun-void reclaim-slot-value (slot-value)
  (cond
    ((or (fixnump slot-value)
         (null slot-value)
         (no-value-p slot-value)
         (symbolp slot-value))
     nil)
    #+subblocks-v2
    ((constant-queue-p slot-value)
     #+development
     (error "reclaim a constant-queue?!")
     nil)
    ((managed-float-p slot-value)
     (reclaim-managed-float slot-value))
    ((text-string-p slot-value)
     (reclaim-text-string slot-value))
    ((gensym-string-p slot-value)
     ;; strings are now only used as constants, ala -- should not come up here
     ;; for reclamation!  (MHD 2/7/96)
     )
    ((managed-array-p slot-value)
     (loop for index from 0 below (managed-array-length slot-value)
           do (reclaim-slot-value (managed-svref slot-value index))
           finally
             (reclaim-managed-array slot-value)))
    ((managed-float-array-p slot-value)
     (reclaim-managed-float-array slot-value))
    ((byte-code-body-p slot-value)
     (reclaim-byte-code-body slot-value))
    ((of-class-p slot-value 'dependent-frame)
     (delete-frame slot-value))
    ((compiled-resource-p-function slot-value)
     (reclaim-compiled-resource-function slot-value))
    ((evaluation-long-p slot-value)
     (reclaim-evaluation-long slot-value))
    #+relation-instances-v2
    ((and (consp slot-value)
	  (eq (car slot-value) 'relation-instance-tree))
     (reclaim-relation-instances slot-value))
    #+connections-v2
    ((and (consp slot-value)
	  (eq (car slot-value) 'connection-item-table))
     #+development
     (error "reclaim a connection-item-table?!")
     nil)
    ;; NOTE: in current Chestnut configuration, there's no header for conses,
    ;; so the type test for conses must be the last test after all others. --binghe
    ((consp slot-value)
     (let ((slot-value-cdr (cdr-of-cons slot-value)))
       (cond ((non-float-default-slot-constant-p slot-value)
              nil)
             ((and (defined-evaluation-value-type-p slot-value-cdr)
                   (or (not (or (eq slot-value-cdr 'sequence)
                                (eq slot-value-cdr 'structure)))
                       (managed-array-p (car-of-cons slot-value))))
              (funcall-simple-compiled-function
                (defined-evaluation-type-reclaimer slot-value-cdr)
                slot-value))
             (t
              (loop with cdr-of-next-cdr = slot-value-cdr
                    for slot-cons = slot-value then next-cdr
                    for car-value = (car-of-cons slot-cons)
                    for next-cdr = cdr-of-next-cdr
                    do
                (unless (or (symbolp car-value)
                            (fixnump car-value)
                            (no-value-p car-value))
                  (reclaim-slot-value car-value))
                    while (and (consp next-cdr)
                               (not (no-value-p next-cdr))
                               (setq cdr-of-next-cdr (cdr-of-cons next-cdr)))
                    finally
                      (unless (or (symbolp next-cdr) (fixnump next-cdr))
                        (reclaim-slot-value next-cdr))
                      (reclaim-slot-value-list-given-tail
                        slot-value slot-cons))))))
    (t
     #+development
     (unless (legal-non-copied-slot-value-p slot-value)
       (cerror "Continue" "Unknown thing for reclaim-slot-value ~S (~S)"
               slot-value (when (vectorp slot-value) (aref slot-value 0))))
     nil)))

;; This will fail if it encounters a simple vector of length zero.

;; Note that text lines and text strings are (indistinguishable from) strings.







;;;; Root Frame Class Definitions




;;; `Define-root-class' redefines the root class.  To see a hierarchical display
;;; of the inheritance tree, use `show-inheritance-tree'.

(defun define-root-class ()

  (setf (slot-name-assignment 'lookup-structure) 0)
  (setf (slot-name-assignment 'class-description-slot) 1)

  (let ((slot-descriptions
          (with-permanent-allocation
            (list
              (make-slot-description
                'lookup-structure 'root 'root nil () 0 nil
                '((vector-slot) (system)) t)
              (make-slot-description
                'class-description-slot 'root 'root nil () 1 nil
                '((vector-slot) (system)) t))))
        (class-inheritance-path (with-permanent-allocation (copy-tree '(root)))))

    (setf (class-description
            'root)
          (make-class-description

            ;; class-name-of-class-description
            'root

            class-inheritance-path

            ;; class-vector-length
            2

            ;; class-features
            nil

            slot-descriptions

            ;; class-is-subclass-of-item?
            nil

            ;; class-user-vector-length
            0

            ;; slots-local-to-class
            '(lookup-structure class-description-slot)

            ;; inherited-slots-this-class-overrides
            nil

            (make-full-slot-descriptions-hash-table
              slot-descriptions class-inheritance-path)

            'root

            ;; class-bit-number and class-bit-vector
            nil nil

            ;; method-table-of-class-description
            (make-method-table-for-system-class)

            ;; class-description-is-system-defined-p
            t)))

  (setf (slot-category 'lookup-structure) 'system)
  (setf (slot-category 'class-description-slot) 'system)
  ;; Class is a "virtual" system-attribute in that the class macro
  ;; expands to (class-name-of-class-description (class-description-slot ,frame)).
  ;; It should not be used as a user-defined slot name.
  (setf (slot-category 'class) 'system)

  (setf (class-definition 'root) '(def-root-class))
  (setf (definition-state 'root) 'defined)

  'root)




(define-root-class)

;; Generally, attribute mimics are defined near the class which they modify.
;; However, attribute mimics for root class are defined in frames2b, as necessary
;; macros are not available here.






;;;; More Random Evaluator Stuff

;;; `clear-all-evaluator-slot-info' is used to clear cached information
;;; that the evaluator uses to access slots and virtual attributes.  This
;;; information is stored on slot-descriptions and cleared whenever a change
;;; is made to system-defined classes, virtual attributes, and category-evaluator
;;; interfaces.

(defun clear-all-evaluator-slot-info ()
  (when any-cached-evaluator-slot-info-p
    (loop for class being each subclass of 'root
          as class-description = (class-description class)
          do
      (loop for slot-description in (slot-descriptions class-description)
            as evaluator-slot-info?
               = (slot-description-evaluator-info? slot-description)
            when evaluator-slot-info?
              do
                ;; leak, rather than reclaim
                ;; which is okay becuase this cannot be called at run time
                ;; (reclaim-evaluator-slot-info evaluator-slot-info?)
                (setf (slot-description-evaluator-info? slot-description) nil)))
    (setq any-cached-evaluator-slot-info-p nil)))






;;;; Optimized Class Description Fetching




;;; Within the class-definition-of-class-p macro, there is an optimization that
;;; can avoid a runtime lookup of a class-description if that class name is
;;; mentioned in this list of classes

(declare-optimized-class-description-lookup
  item system-item

  kb-frame temporary-workspace invisible-entity message-definition format-frame
  menu language-translation user-menu-choice generic-formula logical-variable
  float-variable integer-variable symbolic-variable text-variable
  logical-parameter quantitative-parameter integer-parameter float-parameter
  symbolic-parameter text-parameter forward-chaining-link
  true-value-update-recipient backward-chaining-link function-definition
  units-of-measure-declaration tabular-function-of-1-arg g2-cell-array
  g2-cell-array-cell g2-query-cell g2-designation-cell g2-expression-cell
  remote-procedure-declaration dial meter digital-clock graph-grid plot
  model-definition foreign-function-declaration external-simulation-definition
  authorized-user statement edit-box procedure-invocation
  logbook-page page menu-workspace category-instance-menu-workspace
  inspect-command icon-cell explanation-table text-box g2-login name-box
  category-menu scrap text-region kfep-conversion-choice-menu
  subordinate-text-box dialog-button connection-definition workspace-name-box
  class-definition dependent-frame non-kb-workspace connection-post message-board
  action-button chart default-junction ruling-for-dial pointer-for-dial
  ruling-for-meter marker-for-meter readout-table graph ok
  generic-simulation-formula object method-declaration method
  procedure block variable-or-parameter relation simulation-subtable
  kb-workspace table message loose-end parameter variable quantitative-variable
  slider-minimum-value-label rule question-mark-box slider-readout button-label
  slider-needle type-in-text-box button generic-action-button type-in-box
  arrow-button g2-window connection entity workspace icon-editor-workspace
  object-definition icon-editor-table-info-frame bounding-box tabular-function
  g2-list item-list value-list integer-list float-list quantity-list symbol-list
  text-list truth-value-list
  g2-array item-array
  value-array
  integer-array float-array quantity-array
  symbol-array text-array truth-value-array
  definition
  long-variable #+mtg2 faction)

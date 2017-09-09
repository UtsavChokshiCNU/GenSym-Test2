;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PRIMITIVES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Lowelfl B. Hawkinson, Brian Matthews, and Deborah Young








;;;; Forward References in PRIMITIVES


(declare-forward-references
  (reclaim-gensym-string                                    function UTILITIES1)
  (managed-float-p-function                                 function UTILITIES3)
  (the-g2-defstruct-package                                 variable UTILITIES1)
  (obtain-simple-gensym-string                              variable UTILITIES1)
  (reclaim-text-string                                      function UNICODE)
  (tformat-text-string                                      function UNICODE)
  (copy-null-terminated-string-as-text-string               function UNICODE)
  (text-string-p                                            function UNICODE)
  (lengthw                                                  function UNICODE)
  (newline-p                                                function UNICODE)
  (wide-string-to-gensym-string                             function TRANSCODE)
  (intern-gensym-string                                     function UTILITIES3)
  (gensym-symbol-name                                       function UTILITIES3)
  (g2int-signal-handler                                     function OS-ERROR)
  (g2int-signal-handler-for-launch                          function OS-ERROR)
  (current-system-name                                      variable LAUNCH)
  )

(declare-forward-references (:suppress-module-checks-for ctest)
  (copy-list-using-icp-conses-function                      function INT1)
  (reclaim-icp-list-function                                function INT1)
  (active-icp-sockets                                       variable INT1)
  (handle-event-internal                                    function NETEVENT)
  )

(declare-forward-references (:suppress-module-checks-for gsi gw ctest)
  (g2-stream-all-open-streams                               variable STREAMS)
  (reclaim-streams-list-function                            function STREAMS)
  (copy-list-using-streams-conses-function                  function STREAMS)
  (release-all-kb-write-locks                               function STREAMS)
  (close-and-disconnect-all-sockets                         function INT4)
  (close-native-window                                      function WINDOWS1)
  (noting-changes-to-kb-p                                   variable FRAMES2)
  (make-system-frame                                        function MODULES)
  (install-system-table                                     function MODULES)
  (shift-rule-ordering-heuristics                           function SEQUENCES1)
  (close-log-file                                           function BOOKS)
  (in-clear-kb-p                                            variable KB-SAVE2)
  (kill-possibly-leftover-spawned-process                   function FILE-SYSPROC)
  (reclaim-sysproc-list-function                            function FILE-SYSPROC)
  (kill-foreign-image-unconditionally                       function G2-FOREIGN)
  (get-symbol-properties-function                           function UTILITIES4)
  (get-property-value-function                              function UTILITIES4)
  (set-property-value-function                              function UTILITIES4)
  )

(declare-forward-references (:suppress-module-checks-for ab telewindows ctest gensym-site)
  (call-gsi-open-fd-callback                                function GSI)
  (call-gsi-close-fd-callback                               function GSI)
  (call-gsi-writing-fd-callback                             function GSI)
  (call-gsi-not-writing-fd-callback                         function GSI)
  )



;;;; Storage Allocation Primitives




;;; The following macros are used to control which types of system memory
;;; management are used when creating new Lisp objects.  The expansions of these
;;; macros are highly implementation specific and most have been made for us as
;;; special extensions to vendor's Lisp implementations.

;;; There are three forms of Lisp system memory management used within G2.  They
;;; can be categorized as permanent, dynamic, and temporary.  The kind of memory
;;; management that is used for a particular object is determined by which kind
;;; of area that object was created within.  An object created within a
;;; permanent area of memory will never have garbage collection performed upon
;;; it.  An object created within a dynamic context will have normal garbage
;;; collection performed on it.  Finally, an object created within a temporary
;;; context will be destroyed upon exit from that context.  The default type of
;;; memory management within Common Lisp is dynamic.  Some implementations of
;;; Lisp provide permanent areas of memory.  These are useful for us since we
;;; manage all objects which we create and so should not need garbage collection
;;; carried out on these objects.  However, permanent areas are not required and
;;; in implementations where we do not have them, dynamic
;;; storage will do.  We have requested that our Lisp vendors provide us with a
;;; mechanism for temporary storage so that we may control number consing.

;;; Note:  At the present time we know that there are some objects being created
;;; within the scope of with-permanent-x-creation forms which are becoming
;;; garbage.  For this reason we will be using dynamic storage as the
;;; implementation for both with-dynamic and with-permanent forms.  When we have
;;; things more under control, we will be switching back to permanent
;;; allocation.  -jra 12/16/87

;;; Note on the Note:  Within Lucid, it has become somewhat obvious that it will
;;; not be a good idea to use their static areas ever.  The static (or reserved)
;;; areas of memory in Lucid are typically very small, and every time one of
;;; these areas needs to be expanded, Lucid must perform a garbage collect to
;;; re-organize memory.  So, allocating permanent objects can cause garbage
;;; collects in Lucid.  Given this, it seems a much better idea to just stick
;;; within the dynamic areas of memory for Lucid.  -jra 12/7/88



;;;   with-managed-object-creation {form}*  [macro]

;;; The macro `with-managed-objects' is used in the with-primitive-bindings
;;; macro, which is in turn used in run-system-process, our top level function.
;;; It sets up the environment for managed object creation by initializing all
;;; temporary areas and binding a default area for consing.

;;; We are experiencing problems with consing temporary bignums, and it would
;;; appear that we have clobbered the temporary areas in some way.  It could be
;;; that we are overflowing the size of the temporary areas, so we're increasing
;;; them all.  -jra 8/18/89

(defmacro emit-c-lines (&rest lines) ;Chestnut3.1
  #+chestnut
  `(trans::c-lines ,@lines)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      `(tx:c-lines ,@lines)
      nil)

  #-(or chestnut chestnut-3)
  (declare (ignore lines))
  #-(or chestnut chestnut-3)
  (error "EMIT-C-LINES only implemented in Chestnut")
  )


;; Temporary area initialization has been moved to the with-managed-objects
;; macro.  -jra 10/7/88

;; within-managed-object-scope is defined in GLBASICS.  -pto 03sep90

(defmacro with-managed-objects ((system) &body forms)
  `(let*-or-set-for-system ((within-managed-object-scope t))
      (current-system-case
       (gsi) ; moved to run-gsi-1
       (t (set-up-lisp-memory-management ,system)))
     ,@forms))

;; Changed with-managed-objects to take an additional sublist, as
;; with-primitive-bindings (<system>) ...) The form <system> should evaluate to a
;; system name, a symbol like 'g2 or 'telewindows.  The sublist is passed in by
;; the with-managed-objects macro, whose syntax has also been changed.  This
;; change is necessary in order to insure that memory limits can be tuned to a
;; specific system, though the limits are currently the same for all systems.
;; Note that <system> is evaluated only once, and so does not need to be protected
;; with a gensymed variable.  (jh, 8/2/90)




;;; The following macros are written to explicitly set up an environment for
;;; consing of particular kinds of objects, but there is no guarantee that the
;;; macro will not affect what kind of consing is used for other types of
;;; objects.  That is to say that declaring permanent consing for numbers may
;;; also get you permanent consing for cons cells and structures.  These macros
;;; are written this way since some vendors control object creation per type,
;;; while others manage it per area, and object creation of all types is
;;; affected when changing it for any type.  So, users should only rely on
;;; memory control explicitly described by each function.

;;;   with-permanent-gensym-float-creation {form}*  [macro]

;;; The macro `with-permanent-gensym-float-creation' takes a body of forms as
;;; its arguments, and will cause all gensym-float numbers created within the
;;; dynamic extent of the evaluation of its forms to be consed in a permanent
;;; area of memory.  It returns all values returned by the evaluation of the
;;; last of the forms in its body

;;; On the Lisp machines the area ab-permanent-area will be used for permanent
;;; consing.  Note that for floating point numbers this will really have no
;;; effect.  Short floats on the Lisp machines are immediate datum and don't
;;; ever cons.  This form is being made something other than a noop for testing
;;; purposes.  In Lucid 2.x the macro sys:with-dynamic-area is used to achieve
;;; this effect.  In Lucid 3.0 the macro lucid::with-dynamic-area is used.
;;; -jra 7/6/88

;;; On so-called Vanilla machines with no special facilities yet, this form will
;;; expand into a progn.  -jra 5/27/88

(defmacro with-permanent-gensym-float-creation (&body forms)
  (feature-case
    (:chestnut-trans
      (feature-case
        (:chestnut
          `( ,(intern "WITH-DYNAMIC-AREA" "TRUN")
            ,@forms))
        (:chestnut-3
          `( ,(intern "WITH-DYNAMIC-AREA" "TX")
            ,@forms))))
    (:translator
      (warn "This translator has no WITH-PERMANENT-GENSYM-FLOAT-~
             CREATION code.")
      `(progn ,@forms))
    (:lucid
      `( ,(intern "WITH-DYNAMIC-AREA" "LUCID")
        ,@forms))
    (:lispworks
      `(,(intern "IN-STATIC-AREA" "SYS")
        ,@forms))
    (t `(progn ,@forms))))

;;;   with-temporary-gensym-float-creation spot-tag {form}*  [macro]

;;; The macro `with-temporary-gensym-float-creation' takes a body of forms as its
;;; argument and will cause all gensym-float numbers created within the dynamic
;;; extent of the evaluation of its forms to be consed in a temporary area of
;;; memory.  It also takes as its first argument an unquoted symbol which should
;;; name the spot at which this invocation of the form has been inserted.  This
;;; form returns ONLY THE FIRST VALUE returned by the last form in its body.  On
;;; exit from this form all of the numbers created within it will be garbage
;;; collected and thus will become invalid objects.  Users should take care that
;;; no numbers are returned out of this form, nor should any numbers created
;;; within this form be stored within structures.  See the macros
;;; store-managed-number and extract-number for a way of retaining numeric
;;; results generated within the context of this form.

;; The defvar for minimum-fixnum-interval-between-float-resets is further down
;; in this file, after the definition of fixnum-time-interval.  -jra 8/8/89

(defmacro with-temporary-gensym-float-creation (spot-tag &body forms)
  (unless (symbolp spot-tag)
    (warn "WITH-TEMPORARY-GENSYM-FLOAT-CREATION's spot-tag must be a symbol."))
  (feature-case
    (:chestnut-trans
      (feature-case
        (:chestnut
          `(,(intern "WITH-TEMPORARY-ALLOCATION" "TRUN")
            ,@forms))
        (:chestnut-3
          `(,(intern "WITH-LOCAL-ALLOCATION" "TX")
            ,@forms))))
    (:translator
      `(progn ,@forms))
    (:lucid
      (if (fboundp (intern "%SQ-REF" "LUCID"))
          `(,(intern "WITH-TEMPORARY-AREA" "LUCID")
            ,@forms)
          (progn
            (format t "~&~a is not a function or macro."
                    (intern "%SQ-REF" "LUCID"))
            `(progn ,@forms))))
    (t
     (feature-case
       (:development
         `(let ((within-temporary-float-scope? t))
            ,@forms))
       (t
         `(progn
            ,@forms))))))

;;; `with-temporary-creation' is designed to eventually replace
;;; with-temporary-gensym-float-creation and with-temporary-bignum-creation

(defmacro with-temporary-creation (spot-tag &body forms)
  (unless (symbolp spot-tag)
    (warn "WITH-TEMPORARY-GENSYM-FLOAT-CREATION's spot-tag must be a symbol."))
  (feature-case
    (:chestnut-trans
      (feature-case
        (:chestnut
          `(,(intern "WITH-TEMPORARY-ALLOCATION" "TRUN")
            ,@forms))
        (:chestnut-3
          `(,(intern "WITH-LOCAL-ALLOCATION" "TX")
            ,@forms))))
    (:translator
      `(progn ,@forms))
    (:lucid
      (if (fboundp (intern "%SQ-REF" "LUCID"))
          `(,(intern "WITH-TEMPORARY-AREA" "LUCID")
            ,@forms)
          (progn
            (format t "~&~a is not a function or macro."
                    (intern "%SQ-REF" "LUCID"))
            `(progn ,@forms))))
    (t
     (feature-case
       (:development
         `(let ((within-temporary-float-scope? t))
            ,@forms))
       (t
         `(progn
            ,@forms))))))

;;;   with-temporary-bignum-creation {form}*  [macro]

;;; The macro `with-temporary-bignum-creation' takes a body of forms and will
;;; evaluate them, returning ONLY THE FIRST VALUE returned by the last form in
;;; the body.  Inside of this form, all bignums created will be put into a
;;; temporary area of memory which will be cleared on exit from this form.

;;; Note that on the implementations for Lisp machines, this form bypasses the
;;; consing detection facility.  That is because this mechanism will be
;;; clobbering the temporary area on exit.  The code for the temporary float
;;; wrapper is just checking if any consing is occurring, and errors if any has
;;; happened, since floats on the Lispms are immediate and will not cons.
;;; However, nobody does or can do immediate bignums, so this is a clobbering
;;; macro in all implementations.

;;; In Lispm machines, a temporary area is bound which is cleared on exit from
;;; an outermost invocation of a with-temporary-bignum-creation form.  Before
;;; clearing, if this is a development compilation on a Symbolics, the area is
;;; scanned for objects and if any of the objects in the area are not bignums
;;; and with-consing-errors is non-nil, then an error is signalled.  In Lucid
;;; the body of this form is wrapped with a with-temporary-area form.

;;; Note that the macro avoid-arithmetic-errors will, in the case of an error,
;;; set the variable local-with-consing-errors? to nil.


;;; The macro `objects-in-area' is a Lisp machine only, development only,
;;; debugging form which returns a Gensym cons list of all of the objects in
;;; the passed area.

;;; The function `TAO', which stands for "temporary area objects", is a Lisp
;;; machine only, development only, debugging form which returns the result
;;; of calling objects-in-area with the current value of the special variable
;;; ab-temporary-area.

(defmacro with-temporary-bignum-creation (&body forms)
  (feature-case
    (:chestnut-trans
      (feature-case
        (:chestnut
          `(,(intern "WITH-TEMPORARY-ALLOCATION" "TRUN")
            ,@forms))
        (:chestnut-3
          `(,(intern "WITH-LOCAL-ALLOCATION" "TX")
            ,@forms))))
    (:translator
      `(progn ,@forms))
    (:lucid
      (cond
        ((eval-feature :no-lucid-temporary-areas)
         `(progn
            ,@forms))
        ((fboundp (intern "%SQ-REF" "LUCID"))
         `(,(intern "WITH-TEMPORARY-AREA" "LUCID")
           ,@forms))
        (t
         (progn
           (format t "~&~a is not a function or macro."
                   (intern "%SQ-REF" "LUCID"))
           `(progn ,@forms)))))
    (t `(progn ,@forms))))

;;   with-dynamic-creation {form}*  [macro]
;;
;; Moved to GLBASICS for forward reference.  -pto 03sep90




;;; The macro `with-permanent-non-gensym-float-creation' is used to implement
;;; all of the following permanent cons controllers below.  This is because at
;;; the moment they will all expand to the same thing.  However, this may not be
;;; the case in the future, especially as we add support for different Lisp
;;; implementations, so this macro should never be directly used by anything but
;;; the following few macros.

(defmacro with-permanent-non-gensym-float-creation (&body forms)
  (feature-case
    (:chestnut-trans
      (feature-case
        (:chestnut
          `( ,(intern "WITH-DYNAMIC-AREA" "TRUN")
            ,@forms))
        (:chestnut-3
          `( ,(intern "WITH-DYNAMIC-AREA" "TX")
            ,@forms))))
    (:translator
      (warn "This translator has no WITH-PERMANENT-NON-GENSYM-FLOAT-~
             CREATION code.")
      `(progn ,@forms))
    ((and :lucid :no-lucid-temporary-areas)
     `(,(intern "WITH-NORMAL-CONSING-AREA" "LUCID")
       ,@forms))
    (:lucid
      (cond ((fboundp (intern "%SQ-REF" "LUCID"))
             `(,(intern "WITH-DYNAMIC-AREA" "LUCID")
               ,@forms))
            (t
             (format t "~&~a is not a function or macro."
                     (intern "%SQ-REF" "LUCID"))
             `(progn
                ,@forms))))
    (:lispworks
      `(,(intern "IN-STATIC-AREA" "SYS")
         ,@forms))
    (t `(progn ,@forms))))

;;;   with-permanent-bignum-creation {form}*  [macro]

;;; The macro `with-permanent-bignum-creation' takes a body of forms and will cause
;;; all bignums created within the dynamic extent of the evaluation of these forms to
;;; be placed within a permanent area of memory.  It returns all values returned by
;;; the last form in its body.

(defmacro with-permanent-bignum-creation (&body forms)
  `(with-permanent-non-gensym-float-creation ,@forms))



;;; `Make-permanent-integer' either returns integer unchanged, if it is a fixnum,
;;; or else makes a new permanent bignum equivalent in value to integer.

(defvar one-integer 1)

(defvar minus-one-integer -1)

(defun make-permanent-integer (integer)
  (declare (eliminate-for-gsi))
  (if (typep integer 'fixnum)
      integer
      (let ((one-less (+ integer minus-one-integer)))
        (with-permanent-bignum-creation
          (+ one-less one-integer)))))

;; Consider defining this as macro, with evaluation of the argument outside the
;; with-permanent-bignum-creation context since it may create temporary bignums.

;; The previous implementation of make-permanent-integer only added zero to the
;; given integer, expecting that this would create a new bignum as the result.
;; It turns out that both Lucid and Ibuki [an obsolete platform] optimize the
;; case of adding zero to a bignum and just return the original bignum.  This
;; causes errors, since the bignum given to this function may be temporary, and
;; needs to be copied into a permanently allocated object.  The only
;; implementation that I think of now is to add one and subtract one.  This
;; suffers from an extra allocation of a bignum.  Suggestions for better
;; implementations of this operation are welcome.  -jra & ac 5/29/90




;;;   with-permanent-cons-creation {form}*  [macro]

;;; The macro `with-permanent-cons-creation' takes a body of forms as its
;;; argument and will cause all cons cells created within the dynamic extent of
;;; the evaluation of these forms to be placed within a permanent area of memory.
;;; It returns all values returned by the last form in its body.

(defmacro with-permanent-cons-creation (&body forms)
  `(with-permanent-non-gensym-float-creation
     ,@forms))



;;;   with-permanent-string-creation {form}*  [macro]

;;; The macro `with-permanent-string-creation' takes a body of forms as its
;;; arguments and will cause all strings created within its scope to be placed
;;; into a permanent area of memory.  It returns all values returned by the last
;;; form in its body.

(defmacro with-permanent-string-creation (&body forms)
  `(with-permanent-non-gensym-float-creation
     ,@forms))



;;;   with-permanent-array-creation {form}* [macro]

;;; The macro `with-permanent-array-creation' takes a body of forms as its
;;; arguments and will cause all arrays created within its scope to be placed
;;; into a permanent area of memory.  It returns all values returned by the last
;;; form in its body.

(defmacro with-permanent-array-creation (&body forms)
  `(with-permanent-non-gensym-float-creation
     ,@forms))



;;; `With-permanent-allocation' guarantees that consing done for the duration of
;;; body will be put into non-temporary storage.  If these structures are later
;;; released, they will be eligible for garbage collection.  It is recommended
;;; that this form be placed around the creation of structures during
;;; compilation that have to be used then as well as after the compilation.

(defmacro with-permanent-allocation (&body body)
  (feature-case
    (:chestnut-trans
      (feature-case
        (:chestnut
          `(,(intern "WITH-DYNAMIC-AREA" "TRUN")
            ,@body))
        (:chestnut-3
          `(,(intern "WITH-DYNAMIC-AREA" "TX")
            ,@body))))
    (:translator
      `(progn ,@body))
    ((and :lucid :no-lucid-temporary-areas)
     `(,(intern "WITH-NORMAL-CONSING-AREA" "LUCID")
       ,@body))
    (:lucid
      (cond ((fboundp (intern "%SQ-REF" "LUCID"))
             `(,(intern "WITH-DYNAMIC-AREA" "LUCID")
               ,@body))
            (t
             (format t "~&~a is not a function or macro."
                     (intern "%SQ-REF" "LUCID"))
             `(progn
                ,@body))))
    (:lispworks
      `(,(intern "IN-STATIC-AREA" "SYS")
         ,@body))
    (t`(progn ,@body))))

;;; The macro `with-unmoveable-object-creation' will cause any objects that are
;;; created to be made such that they are permanent and will not be relocated by
;;; garbage collection.  This is necessary on systems where we are passing
;;; pointers to these objects to foreign functions whose pointers will not be
;;; updated by the garbage collector.  Currently this is true only of Lucid.  In
;;; systems where unmoveable objects are not required (e.g. the Lisp machines),
;;; this form will cause objects creation to occur in a permanent area of
;;; memory.

(defmacro with-unmoveable-object-creation (&body forms)
  (feature-case
    (:chestnut-trans
      `(with-permanent-allocation ,@forms))
    (:translator
      `(progn ,@forms))
    (:lucid
     `(,(intern "WITH-STATIC-AREA" "SYS") ,@forms))
    (t
      `(with-permanent-allocation ,@forms))))

;;; The macro `make-mutable-list' takes the place of CLtL make-list in our
;;; system.  Since the lists that we make are always rplacd'ed into pieces after
;;; their creation we want to avoid any cdr-coding of lists.  So,
;;; make-mutable-list will expand into a form which conses up and returns a list
;;; which is guaranteed to be made out of full-fledged cons objects.

(defmacro make-mutable-list (length)
  `(make-list ,length))


;;; The function `make-permanent-list' will create and return a list of conses
;;; created in an appropriate area of memory and guaranteed to not be cdr-coded
;;; (for efficiency when doing rplacd's).

(defun make-permanent-list (length)
  (let ((new-list nil))
    (with-permanent-cons-creation
      (setq new-list (make-mutable-list length)))
    new-list))

(defmacro permanent-list (&rest elements)
  `(set-list-contents (make-permanent-list ,(length elements)) ,@elements))




;;; The macro `make-permanent-list-macro' will create and return a list of
;;; conses created in an appropriate area of memory and guaranteed to not be
;;; cdr-coded (for efficiency when doing rplacd's).

(defmacro make-permanent-list-macro (length)
  (let ((new-list (gensym)))
    `(let ((,new-list nil))
       (with-permanent-cons-creation
         (setq ,new-list (make-mutable-list ,length)))
       ,new-list)))



;;; The function `make-dynamic-list' will create and return a list of conses created
;;; in a garbage-collectable area of memory.  The list is guaranteed to not be
;;; cdr-coded (for efficiency when doing replacd's on Lisp machines).

(defun make-dynamic-list (length)
  (declare (eliminate-for-gsi)
           (ignorable length))
  (with-dynamic-creation (make-mutable-list length)))





;;; The macro `make-dynamic-list-macro' will create and return a list of conses
;;; created in a garbage-collectable area of memory.  The list is guaranteed to
;;; not be cdr-coded (for efficiency when doing replacd's on Lisp machines).

(defmacro make-dynamic-list-macro (length)
  `(with-dynamic-creation (make-mutable-list ,length)))

;; jh, 1/27/93.  Moved the remaining memory-related facilities to OS-MEMORY to
;; make it easier to get an overall picture of G2 memory management.  Will leave
;; the temporary area macros in PRIMITIVES for a while, since that is where
;; everybody is used to looking for them.






;;;; Global Properties




;;; The macro `symbol-plist-for-lookup' abstracts an optimization we are using
;;; for fetching the symbol-plist of symbols in Chestnut.  Normally, fetching a
;;; symbol-plist costs a function call in Chestnut.  This is done so that they
;;; can skip over properties that they "hide" at the front of the symbol-plist.
;;; If these properties are on a symbol (they are for symbol-name and
;;; symbol-function) any modifications made to the user-visible symbol-plist
;;; must happen in the portion of the list behind these properties.  We would
;;; prefer to fetch the symbol-plist without a function call, and we can do so
;;; as long as we do not attempt to do modifications to the symbol-plist by
;;; consing things onto the front of the returned list and setf'ing it back into
;;; the symbol.  So, this macro symbol-plist-for-lookup is to be used when
;;; looking up values within the plist, but not for manipulating the conses of
;;; the list.

;;; Note that when calling INLINE_SYMBOL_PLIST, the argument must able to be
;;; evaluated more than once.

(defmacro symbol-plist-for-lookup (symbol)
  (if (and (eval-feature :chestnut-3)
           (eval-feature :translator))
      (if (or (symbolp symbol) (constantp symbol))
          `(symbol-plist-chestnut-internal ,symbol)
          (let ((arg (gensym)))
            `(let ((,arg ,symbol))
               (symbol-plist-chestnut-internal ,arg))))
      `(symbol-plist ,symbol)))

#+(and chestnut-3 translator)
(tx::def-foreign-function
    (symbol-plist-chestnut-internal (:name "INLINE_SYMBOL_PLIST")
                                    (:return-type :object))
    (symbol :object))

#-(and chestnut-3 translator)
(defun symbol-plist-chestnut-internal (symbol)
  (symbol-plist symbol))




;;; `Def-global-property-name' defines access and update operations for
;;; global-property-name.  The accessor takes a symbol as its argument and
;;; returns any global value for that property on that symbol.  The accessor
;;; works with SETF.

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar-of-special-global global-property-names nil))

(defmacro def-global-property-name (global-property-name &optional use-hash?)
  (let ((set-property-name
         (build-ab-symbol "SET-PROPERTY" global-property-name))
        (get-property-macro
         (build-ab-symbol global-property-name "MACRO"))
        (property-name-var (intern (format nil "~a-PROP" global-property-name))))
    `(progn
       #+development
       (pushnew ',global-property-name global-property-names)

       (eval-when (:compile-toplevel :load-toplevel :execute)
         (defparameter ,property-name-var ',global-property-name))

       (defmacro ,get-property-macro (symbol &optional default)
         (if (and (eval-feature :chestnut-trans) ,use-hash?)
             `(get-property-value-function (get-symbol-properties-function ,symbol)
                                           ',',global-property-name ,default)
           `(getfq-macro (symbol-plist-for-lookup ,symbol)
                         ',',global-property-name ,default)))

       (defmacro ,global-property-name (symbol &optional default)
         (if (and (eval-feature :chestnut-trans) ,use-hash?)
             `(get-property-value-function (get-symbol-properties-function ,symbol)
                                           ',',global-property-name ,default)
           `(getfq (symbol-plist-for-lookup ,symbol)
                   ',',global-property-name ,default)))

       (defmacro ,set-property-name (symbol-form value-form)
         (if (and (eval-feature :chestnut-trans) ,use-hash?)
             `(progn
                (set-property-value-function (get-symbol-properties-function ,symbol-form)
                                             ',',global-property-name ,value-form)
                ,value-form)
           `(mutate-global-property ,symbol-form ,value-form ',',global-property-name)))

       (defsetf ,global-property-name ,set-property-name)

       ,@(unless (eval-feature :no-macros)
           `((note-function-call-accessor-macro ',global-property-name)))
       ',global-property-name)))

;; The property name is stored in a variable to avoid calls to STATIC_SYMBOL in
;; every file that uses the accessor or mutator for this property.  This is an
;; obscurity of Chestnut's implementation of symbol initializations.  The
;; approach of having a parameter that holds a pointer to the symbol works
;; around it without any loss of performance.  We should remove this when we
;; have a better initialization story from Chestnut.  -jra 4/20/94




;;; `Map-over-global-property' is a development only function which
;;; will apply a function of two arguments to all the symbols that
;;; have a particular property.

#+development
(defun map-over-global-property (property function-of-symbol-and-value)
  (unless (memq property global-property-names)
    (cerror "go on." "Unknown global property."))
  (let (value)
    (do-symbols (symbol 'ab)
      (when (neq '#1=#:NOPE (setf value (get symbol property '#1#)))
        (funcall function-of-symbol-and-value symbol value)))
    (do-symbols (symbol the-g2-defstruct-package)
      (when (neq '#2=#:NOPE (setf value (get symbol property '#2#)))
        (funcall function-of-symbol-and-value symbol value)))))




;;; `Mutate-global-property' is used to set values that are stored as
;;; properties.  It takes the symbol containing the property, the value it
;;; should receive, and the symbol naming the property as arguments.  Note that
;;; this form is used as the expansion of defsetfs on global property accessors,
;;; and so must return the value being placed into the property.  The function
;;; has been somewhat optimized for the case where an existing property is
;;; mutated.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar-of-special-global global-property-conses nil))

(defun-simple mutate-global-property (symbol-1 value property)
  (as-atomic-operation
    (let* ((original-plist (symbol-plist symbol-1))
           (property-value-cons
             (loop for property-cons
                       = original-plist
                       then (cdr-of-cons (cdr-of-cons property-cons))
                   while property-cons
                   do
               (when (eq property (car-of-cons property-cons))
                 (setq property-cons (cdr-of-cons property-cons))
                 (return property-cons)))))
      (if property-value-cons
          (setf (car property-value-cons) value)
          (let ((new-property-cons global-property-conses))
            (unless new-property-cons
              (setq new-property-cons (make-permanent-list 200))) ;not sure
            ;; Since even numbers of property-conses are allocated and used
            ;; at every turn, we can assume that the next cons is available.
            (let ((new-value-cons (cdr-of-cons new-property-cons)))
              (setf global-property-conses (cdr-of-cons new-value-cons))
              (setf (car new-property-cons) property)
              (setf (car new-value-cons) value)
              (setf (cdr new-value-cons) original-plist)
              (setf (symbol-plist symbol-1) new-property-cons))))))
    value)






;;;; System Object Pool Metering




;;; The macro `def-system-object-pool' should be called to define meters for any
;;; pool of managed objects in G2.  It takes five unquoted arguments:
;;;
;;;   the name of the pool being created,
;;;
;;;   the type of objects being created (given as a Common Lisp type if
;;;   possible),
;;;
;;;   a symbol which holds as a value a count of how many objects have been
;;;   created for the pool,
;;;
;;;   a symbol which holds as a value a count of how many objects from the pool
;;;   are outstanding (i.e. given out but not yet reclaimed into the pool) or
;;;   else NIL if there is function which returns this value,
;;;
;;;   a symbol which names a function which returns a count of how many objects
;;;   from the pool are outstanding or else NIL if there is a variable which
;;;   holds this value,
;;;
;;;   and a symbol which names a function which returns the number of bytes of
;;;   memory that are used by all objects from this pool
;;;
;;; The counts of objects created and objects outstanding must be kept exact,
;;; and the memory-usage result should be as good as is possible.  (We are trying
;;; to make all memory-usage estimates exact from now on.  -jra 11/25/90)

;;; This macro will cause an entry for the pool to be added to the global
;;; variable `object-pool-meters'.  If an entry already exists it will be
;;; modified only if the new definition is different from the original, but it
;;; will always retain the original order or add a new one to the end of the
;;; list.  This an association list whose keys are the names of the object
;;; pools.

(defvar object-pool-meters nil)

(eval-when (:compile-toplevel :load-toplevel :execute)                        ; this is needed in this file
  (defun update-object-pool-meters-list (new-entry)
    (declare (eliminate-for-gsi))
    (loop for entry-cons on object-pool-meters
          do
            (cond ((eq (caar entry-cons) (car new-entry))
                   (if (not (equal (car entry-cons) new-entry))
                       (setf (car entry-cons) new-entry))
                   (return nil)))
          finally                                ; no entry yet
            (with-permanent-allocation
              (setq object-pool-meters
                    (nconc object-pool-meters (cons new-entry nil)))))
    (car new-entry)))

(defmacro def-system-object-pool
          (name x-data-type x-counter-var
                outstanding-x-counter-var?
                outstanding-x-counter-function?
                memory-use-function)
  (if (eq current-system-being-loaded 'gsi)
      nil
      `(update-object-pool-meters-list
         (optimize-constant
           '(,name ,x-data-type ,x-counter-var
             ,outstanding-x-counter-var? ,outstanding-x-counter-function?
             ,memory-use-function)))))




;;; The functions `pool-entry-name', `pool-entry-data-type',
;;; `pool-entry-object-count', `pool-entry-outstanding-object-count', and
;;; `pool-entry-memory-usage-in-bytes', can be used to retrieve the values
;;; associated with an entry in the object-pool-meters list.  These function are
;;; given an object pool entry as their only argument.  These entries can be
;;; found by doing as assq on the object-pool-meters alist.

;;; Pool-entry-name returns the symbol naming the entry.  Pool-entry-data-type
;;; returns the specifier naming the type of objects in that pool.
;;; Pool-entry-object-count returns the number of objects which have been
;;; created for that pool.  Pool-entry-outstanding-object-count returns the
;;; number of objects in this pool which have been given out, but not returned.
;;; Note that this may value may be computed for paticular entries either by
;;; incff and decffs in the allocators and reclaimers, or it may keep a count of
;;; how many it has created and subtract from that the number currently in the
;;; pool's buffer.  Pool-entry-memory-usage-in-bytes returns the number of bytes
;;; used to create the total number of objects allocated for this pool.

(defun pool-entry-name (pool-entry)
  (declare (eliminate-for-gsi))
  (first pool-entry))

(defun pool-entry-data-type (pool-entry)
  (declare (eliminate-for-gsi))
  (second pool-entry))

#+development
(defvar warn-of-missing-pool-variables-and-functions? t)

#+development
(defun warn-of-missing-pool-variable (variable)
  (when warn-of-missing-pool-variables-and-functions?
    (cerror "Continue, disabling further missing pool variable warnings."
            "~a unbound in request for system object pool meters."
            variable)
    (setq warn-of-missing-pool-variables-and-functions? nil)))

#+development
(defun warn-of-missing-pool-function (function)
  (when warn-of-missing-pool-variables-and-functions?
    (cerror "Continue, disabling further missing pool function warnings."
            "Function ~a not defined in request for system object pool meters."
            function)
    (setq warn-of-missing-pool-variables-and-functions? nil)))

(defmacro pool-entry-object-count-macro (pool-entry)
  (let ((count-variable (gensym)))
    `(let ((,count-variable (third ,pool-entry)))
       (if (boundp ,count-variable)
           (symbol-value ,count-variable)
           (progn
             #+development
             (warn-of-missing-pool-variable ,count-variable)
             0)))))

(defun pool-entry-object-count (pool-entry)
  (declare (eliminate-for-gsi))
  (pool-entry-object-count-macro pool-entry))

(def-substitution-macro pool-entry-outstanding-object-count-macro (pool-entry)
  (let ((outstanding-counter-variable? (fourth pool-entry)))
    (if outstanding-counter-variable?
        (if (boundp outstanding-counter-variable?)
            (symbol-value outstanding-counter-variable?)
            (progn
              #+development
              (warn-of-missing-pool-variable outstanding-counter-variable?)
              0))
        (let ((outstanding-counter-function? (fifth pool-entry)))
          (if outstanding-counter-function?
              (if (fboundp outstanding-counter-function?)
                  (funcall-symbol outstanding-counter-function?)
                  (progn
                    #+development
                    (warn-of-missing-pool-function
                      outstanding-counter-function?)
                    0))
              0)))))

(defun pool-entry-outstanding-object-count (pool-entry)
  (declare (eliminate-for-gsi))
  (pool-entry-outstanding-object-count-macro pool-entry))

(defmacro pool-entry-memory-usage-in-bytes-macro (pool-entry)
  (let ((count-function (gensym)))
    `(let ((,count-function (sixth ,pool-entry)))
       (if (fboundp ,count-function)
           (funcall-symbol ,count-function)
           (progn
             #+development
             (warn-of-missing-pool-function ,count-function)
             0)))))

(defun pool-entry-memory-usage-in-bytes (pool-entry)
  (declare (eliminate-for-gsi))
  (pool-entry-memory-usage-in-bytes-macro pool-entry))




;;; The function `total-pool-outstanding-object-count' returns an integer count
;;; of the total number of object pool objects which have been handed out, but
;;; not yet returned to a system pool.


(defun total-pool-outstanding-object-count ()
  (declare (eliminate-for-gsi))
  (loop with accumulator = 0
        for pool-entry in object-pool-meters
        do
          (setq accumulator
                (+f accumulator
                    (pool-entry-outstanding-object-count-macro pool-entry)))
        finally
          (return accumulator)))

;;; The function `total-pool-object-count' returns an integer count of the total
;;; number of object pool objects that which have been created in all system
;;; object pools.


(defun total-pool-object-count ()
  (declare (eliminate-for-gsi))
  (loop with accumulator = 0
        for pool-entry in object-pool-meters
        do
          (setq accumulator
                (+f accumulator (pool-entry-object-count-macro pool-entry)))
        finally
          (return accumulator)))




;;; The function `total-pool-memory-usage' returns an integer count of the total
;;; number of memory bytes allocated to system object pools.


(defun total-pool-memory-usage ()
  (declare (eliminate-for-gsi))
  (loop with accumulator = 0
        for pool-entry in object-pool-meters
        do
          (setq accumulator
                (+f accumulator (pool-entry-memory-usage-in-bytes-macro pool-entry)))
        finally
          (return accumulator)))




(defparameter-excluding-gsi names-of-interesting-system-object-pools
    '(gensym-conses
      slot-value-conses
      graphics-conses
      token-conses
      byte-vector-16-pool
      frame-vector-pool
      ))

#+development
(defun memory (&optional args)
  "
;;; The function `memory' will print out a table of the size and free space of some
;;; system object pools.  Args can be the names of system object pools or T (listed),
;;; meaning to show all system object pools or unspecified, meaning to show a the default
;;; subset of \"interesting\" object pools -- the variable names-of-interesting-system-object-
;;; pools defines what is printed in the latter case.  This function is an analog of the lisp
;;; function room and is useful and intended for online lisp hacking.
"
  (format
    t "~%~3T~30A~20A~9@A~9@A~9@A~9@A" "Pool Name" "Type"
    "Count" "Out" "%Out" "Memory")
  (loop for meter-entry in object-pool-meters
        as pool-name = (pool-entry-name meter-entry)
        do
          (when (if (eq args nil)
                    (memq pool-name names-of-interesting-system-object-pools)
                    (if (equal args '(t))
                        t
                        (memq pool-name args)))
            (let ((object-count (pool-entry-object-count meter-entry))
                  (outstanding-count
                    (pool-entry-outstanding-object-count meter-entry))
                  (memory-usage (pool-entry-memory-usage-in-bytes meter-entry)))
              (format
                t "~:(~%~3T~30a~20a~9D~9D~9D~9D~)"
                (if (> (length (symbol-name (pool-entry-name meter-entry))) 25)
                    (concatenate
                      'string (subseq (symbol-name (pool-entry-name meter-entry)) 0 25)
                      "...")
                    (symbol-name (pool-entry-name meter-entry)))
                (let ((s (write-to-string (pool-entry-data-type meter-entry))))
                  (if (> (length s) 15)
                      (concatenate 'string (subseq s 0 15) "...")
                      s))
                object-count
                outstanding-count
                (floor (* outstanding-count 100)
                       (maxf object-count 1))
                memory-usage)))))

#+development
(defun memory-sorted (&optional args)
  (format
    t "~%~3T~30A~20A~9@A~9@A~9@A~9@A" "Pool Name" "Type"
    "Count" "Out" "%Out" "Memory")
  (loop with entry-list = nil
        for meter-entry in object-pool-meters
        as pool-name = (pool-entry-name meter-entry)
        do
          (when (if (eq args nil)
                    (memq pool-name names-of-interesting-system-object-pools)
                    (if (equal args '(t))
                        t
                        (memq pool-name args)))
            (let ((object-count (pool-entry-object-count meter-entry))
                  (outstanding-count
                    (pool-entry-outstanding-object-count meter-entry))
                  (memory-usage (pool-entry-memory-usage-in-bytes meter-entry)))
              (push (list
                      (if (> (length (symbol-name (pool-entry-name meter-entry))) 25)
                          (concatenate
                            'string (subseq (symbol-name (pool-entry-name meter-entry)) 0 25)
                            "...")
                          (symbol-name (pool-entry-name meter-entry)))
                      (let ((s (write-to-string (pool-entry-data-type meter-entry))))
                        (if (> (length s) 15)
                            (concatenate 'string (subseq s 0 15) "...")
                            s))
                      object-count
                      outstanding-count
                      (floor (* outstanding-count 100)
                             (maxf object-count 1))
                      memory-usage)
                    entry-list)))
        finally
          (setq entry-list (sort entry-list #'> :key #'(lambda (x) (car (last x)))))
          (dolist (entry entry-list)
            (apply (lisp-format) t "~:(~%~3T~30a~20a~9D~9D~9D~9D~)" entry))))





;;; Compare-memory-allocation will print out a table of object pools that have
;;; changed in size since the last time the function was called.  If the show-all?
;;; argument is non-nil, all pools will be printed.  If the
;;; initialize-memory-comparison-alist? argument is non-nil, the special variable
;;; memory-comparison-alist is initialized.  This special variable is bound to
;;; an alist consisting of gensym conses.  This alist is re-used so
;;; compare-memory-allocation does no consing if it is not initializing.
;;; The elements of the alist are of the form
;;;   (pool-name number-allocated number-outstanding delta-allocated delta-outstanding).
;;; Also, when initializing, results of any previous calls are cleared so no
;;; comparison can be done.

#+(or development under-test)
(eval-when (:compile-toplevel :load-toplevel :execute)
(proclaim '(special memory-comparison-alist))        ; defined below
)

#+(or development under-test)
(defun scope-conses-delta (pool-name)
  ;; Scope conses are gensym conses which are never reclaimed. 
  ;; So we have to subtract their amount from a number of 
  ;; outstanding gensym conses to avoid reporting a false memory leak.
  ;; This will work fine only if there are no outstanding scope-conses.
  ;; If there are outstanding scope-conses, we can not count conses without changing scope-conses implementation
  (if (eq pool-name 'gensym-conses)
      (- (* 
          2 ; each scope-cons requires two gensym-conses, 
            ; see ab::scope-cons
          (length scope-conses))
         1  ; initial conses in scope-conses are allocated from lisp.
         )
    0))

#+(or development under-test)
(defun compare-memory-allocation
       (&optional (show-all? nil) (initialize-memory-comparison-alist? nil))
  (let ((initializing?
          (when (or (null memory-comparison-alist)
                    initialize-memory-comparison-alist?)
            (setq memory-comparison-alist
                  (loop for meter-entry in object-pool-meters
                        as pool-name = (pool-entry-name meter-entry)
                        nconc (with-permanent-allocation
                                (list
                                  (list pool-name nil nil nil nil)))))
            t)))
    (loop with heading-printed? = nil
          for meter-entry in object-pool-meters
          for comparison-entry in memory-comparison-alist
          as pool-name = (pool-entry-name meter-entry)
          as number-allocated
             = (pool-entry-object-count meter-entry)
          as number-outstanding
             = (- (pool-entry-outstanding-object-count meter-entry)
                  (scope-conses-delta pool-name))
          as change-in-number-allocated
             = (if initializing?
                   0
                   (-f number-allocated
                       (second comparison-entry)))
          as change-in-number-outstanding
             = (if initializing?
                   0
                   (-f number-outstanding
                       (third comparison-entry)))
          do
            (when (not (eq pool-name (car comparison-entry)))
              (format t "Memory-comparison-alist must be initialized.")
              (return (values)))
            (setf (second comparison-entry) number-allocated
                  (third comparison-entry) number-outstanding
                  (fourth comparison-entry) change-in-number-allocated
                  (fifth comparison-entry) change-in-number-outstanding)
            (when (or (not (=f change-in-number-allocated 0))
                      (not (=f change-in-number-outstanding 0))
                      show-all?)
              (when (not heading-printed?)
                (format
                  t "~%~3T~30A~20A~9@A~9@A~9@A~9@A"
                  "Pool Name" "Type" "Count" "Out" "D Count" "D Out")
                (setq heading-printed? t))
              (format
                t "~:(~%~3T~30a~20a~9D~9D~9D~9D~)"
                (if (> (length (symbol-name (pool-entry-name meter-entry))) 25)
                    (with-permanent-allocation
                      (concatenate
                        'string (subseq (symbol-name (pool-entry-name meter-entry)) 0 25)
                        "..."))
                    (symbol-name (pool-entry-name meter-entry)))
                (let ((s (write-to-string (pool-entry-data-type meter-entry))))
                  (if (> (length s) 15)
                      (with-permanent-allocation
                        (concatenate 'string (subseq s 0 15) "..."))
                      s))
                number-allocated number-outstanding
                change-in-number-allocated change-in-number-outstanding)))))






;;;; Printing Data Structures in Translated Images



;; The following are some functions that make is possible for remote-eval
;; to poke around inside of the G2 data structures.

;; jh, 7/16/94.  Moved Ben's functions to GLBASICS, where GSI can benefit from
;; them, and added pm-print-structure.  As a historical aside, Ben tells me that
;; "pm" stands for "poor man's".


(defmacro defun-for-remote-eval (name arglist &rest body)
  `(progn
     (declare-funcallable-symbol ,name)
     (defun-allowing-unwind ,name ,arglist ,@body)))

(defun-for-remote-eval pm-elt (object index)
  (cond
    ((consp object)
     (nth index object))
    ((arrayp object)
     (aref object index))
    (t
     -1234567)))

(defun-for-remote-eval pm-nthcdr (object index)
  (cond
    ((consp object)
     (nthcdr index object))
    (t
     -1234567)))

(defun-for-remote-eval pm-type-of (object)
  (cond
    ((null object)
     'null)
    ((or (symbolp object)
         (stringp object)
         (numberp object))
     (list 'member object))
    ((consp object)
     'cons)
    ((arrayp object)
     (list 'array (array-element-type object) (length object)))))


(defun-for-remote-eval pm-composite-type-of (object)
  (cond
    ((or (arrayp object)
         (consp object))
     (list*
       'composite-object
       (pm-type-of object)
       (loop for i from 0 below (length object)
             as element = (elt object i)
             collect (pm-type-of element))))
    (t
     (pm-type-of object))))


(defvar single-element-string (make-string 1))

(defun pm-print-wide-string (thing)
  (princ "#w\"")
  (loop as i from 0
        as elt = (aref thing i)
        until (=f elt 0)
        do
    (cond
      ((newline-p elt)
       (terpri))
      ((=f elt 32)    ;; %space
       (princ " "))
      (t
       (setf (elt single-element-string 0) (code-char elt))
       (princ single-element-string)))
        finally
          (princ "\"")))


(defun-void pm-print-substructure (object max-depth depth)
  (macrolet ((print-type (type)
               (if (eq current-system-being-loaded 'gsi)
                   `(format t "~s:~%" ,type)
                   `(format t "~(~s~):~%" ,type))))
    (cond
      ((and (fixnump max-depth) (>f depth max-depth))
       (format t "~s~%" object))
      ((stringp object) (format t "~s~%" object))
      ((text-string-p object)
       (pm-print-wide-string object)
       (terpri))
      ((or (arrayp object) (consp object))
       (print-type (pm-type-of object))
       (loop for i fixnum from 0 below (length object)
             as element = (elt object i)
             do
         (loop for j fixnum from 0 to (*f depth 2) do (format t " "))
         (format t "[~d] " i)
         (pm-print-substructure element max-depth (1+f depth))))
      (t (format t "~s~%" object)))))

(defun-for-remote-eval pm-print-structure (object max-depth)
  (pm-print-substructure object max-depth 0)
  object)



;;; The function `pm-structure-type' returns the gensym structure type of thing,
;;; if it has one.

(defun pm-structure-type (thing)
  (when (and (simple-vector-p thing)
             (>f (length thing) 1))
    (let ((raw-type-name (aref thing 0)))
      (when (symbolp raw-type-name)
        (let* ((string (symbol-name raw-type-name))
               (suffix "-G2-STRUCT")
               (n (length suffix))
               (tail (-f (length string) n)))

          (when (and (>f tail 0)
                     (string= string suffix :start1 tail))
            (values
              (intern (subseq string 0 tail)
                      ab-package-1))))))))


;;; The function `pm-frame-type' returns the frame type of thing, if it has one.

(defun pm-frame-type (thing)
  (when (and (simple-vector-p thing)
             (>f (length thing) 2))
    (let ((x (svref thing 1)))
      (cond ((simple-vector-p x)
             (svref x 1))
            ((eq x 'available-frame-vector)
             'available-frame-vector)))))

;; Notice the hardwired knowledge of frame formats.


;;; The function `pm-gensym-type-of' returns a more Gensym-oriented type than
;;; pm-type-of, which I am afraid to change since it may be used by remote-eval.

(defun pm-gensym-type-of (thing)
  (or (pm-frame-type thing)
      (pm-structure-type thing)
      (if (managed-float-p-function thing) 'managed-float)
      (type-of thing)))


;;; The function `write-structure-slotnames' is a new slotnames file writer for
;;; use with the Windows debugger extension in util/windbg.

#+development
(defun write-structure-slotnames (&optional (filename "slotnames.txt"))
  (with-open-file (*standard-output* filename :direction :output)
    (format t "# ")
    (write-system-version (system-version 'ab))
    (format t "~%")
    (do-symbols (symbol 'ab)
      (let ((slots (get symbol 'DEF-STRUCTURE-SLOT-DESCRIPTIONS)))
        (when slots
          (format t "~s-G2-STRUCT~%" symbol)
          (format t "~(~s~)~%" 'internal-structure-type-name)
          (loop for slot in slots doing
            (format t "~(~s~)~%" (if (consp slot) (car slot) slot)))
          (format t "~%"))))))


(defparameter pm-file-names '("slotnames.70" "/home/ab/g2/slotnames.70"))

(defvar pm-slot-names nil)

(defun pm-slot-names (vector)
  (declare allow-lisp-pathnames
           #-gsi-web (no-op-for-gsi))
  (unless pm-slot-names
    (let ((filename? (loop for filename in pm-file-names
                           when (funcall 'gensym-probe-file filename)
                             return filename)))
      (when filename?
        (format t "[Reading slotnames from ~s]~%" filename?)
        (with-open-file (stream filename?)
          (setq pm-slot-names (read stream nil))))))
  (cdr (assq (or (pm-structure-type vector)
                 (pm-frame-type vector))
             pm-slot-names)))



(defvar pm-max-length 100)


;;; The function `pm-describe' prints both lists and vectors as structures. It
;;; intended for use by gdb.

(defun pm-describe (thing)
  (with-permanent-allocation ; eliminate warnings by warn_gensym_area_violation
    (macrolet ((P (index object &optional name)
                 `(progn
                    (format t "[~2d] " ,index)
                    (if ,name
                        (format t " ~50a " ,name))
                    (pm-print-object-id ,object)
                    (princ "  ")
                    (pm-print ,object))))

      (let ((max-length pm-max-length))
        (pm-prin1 thing)
        (princ " is a ")
        (prin1 (pm-gensym-type-of thing))
        (princ " aka ")
        (prin1 (type-of thing))
        (terpri)
        (typecase thing
          ((vector (unsigned-byte 16))
           (pm-print-wide-string thing)
           (terpri))
          (vector
           (loop with names = (pm-slot-names thing)
                 for i below (minf (length thing) max-length)
                 as elt = (aref thing i)
                 as name = (pop names)
                 doing (P i elt name)))
          (cons
           (loop for sublist on thing
                 for i below (minf (length thing) max-length)
                 as elt = (car sublist)
                 doing
             (P i elt)
             (when (and (atom (cdr sublist))
                        (cdr sublist))
               (P "CDR" (cdr sublist))))))
        thing))))


(defvar pm-temp-string (make-string 10))

;;; The function `pm-print-object-id' exists because Chestnut cannot handle
;;; (format t "~8,'0x" ...).  It could be rewritten in C w/o consing bignums.

(defun pm-object-id (object)
  (let ((addr (%pointer object)))
    (macrolet ((pm-logand (n1 n2)
                 (feature-case
                   ((and :chestnut-3 :chestnut-trans) `(logandf ,n1 ,n2))
                   (t `(logand ,n1 ,n2))))
               (pm-ash (n1 n2)
                 (feature-case
                   ((and :chestnut-3 :chestnut-trans) `(ashf ,n1 ,n2))
                   (t `(ash ,n1 ,n2)))))
      (loop for i from 9 downto 2
            do (setf (char pm-temp-string i)
                     (char "0123456789abcdef" (pm-logand addr 15)))
               (setq addr (pm-ash addr -4)))
      (setf (char pm-temp-string 0) #\0
            (char pm-temp-string 1) #\x)
      pm-temp-string)))

(defun pm-print-object-id (object)
  (pm-prin1 (pm-object-id object)))

;; jh, 3/30/95.  I don't believe this function conses bignums in Chestnut.  A
;; look at the translation shows that variable addr comes from a foreign
;; function with return type Object, meaning that the translator does not
;; attempt type coercion.  Since Object fits inside an immediate long, and addr
;; is logand'd and ash'd without reference to its type, no bignums are consed.
;; (I need to use fixnum arithmetic in an attempt to eliminate generic
;; arithmetic from GSI, in order to reduce its size.)


;;; The function `pm-print' is also for use by gdb.

(defun pm-print (thing)
  (pm-prin1 thing)
  (terpri)
  thing)

(defun pm-princ (thing)
  (with-permanent-allocation ; eliminate warnings by warn_gensym_area_violation
    (princ thing)))

(defun pm-prin1 (thing)
  (with-permanent-allocation ; eliminate warnings by warn_gensym_area_violation
    (let ((*print-circle* t))
      (cond ((text-string-p thing)
             (pm-print-wide-string thing))
            ((managed-float-p-function thing)
             (let* ((wide-string (tformat-text-string "~A" thing))
                    (gensym-string (wide-string-to-gensym-string wide-string)))
               (princ "#<Managed-Float ")
               (princ gensym-string)
               (princ " ")
               (pm-print-object-id thing)
               (princ ">")
               (reclaim-text-string wide-string)
               (reclaim-gensym-string gensym-string)))
            ((pm-structure-type thing)
             (princ "#<")
             (princ (pm-structure-type thing))
             (princ " ")
             (princ (pm-object-id thing))
             (princ ">"))
            ((pm-frame-type thing)
             (princ "#<")
             (princ (pm-frame-type thing))
             (princ " ")
             (pm-print-object-id thing)
             (princ ">"))
            ((consp thing)
             (princ "(")
             (loop for (car . rest) on thing doing
               (pm-prin1 car)
               (cond ((null rest))
                     ((consp rest)
                      (princ " "))
                     (t
                      (princ " . ")
                      (pm-prin1 rest)
                      (loop-finish))))
             (princ ")"))
            (t
             (prin1 thing)))))
  thing)



;;;; System and KB-Specific Variables

;; These are here only because they are used in module PRIMITIVES rather than
;; because of any implementation dependencies.



(def-global-property-name system-variable-descriptions)         ; of a module name



;;; Def-system-variable defines a `system variable', a special variable which is to
;;; be bound (and maybe initialized) at the top level of a process, or, more
;;; precisely, within each invocation of with-system-variables that specifies a
;;; system having module-name as a component.  (See with-system-variables below for
;;; details and for the significance of re-evaluate-initialization-on-rebinding?.)
;;; If also-bind-globally? is specified, then system-variable-name is also globally
;;; set per initialization, unless it already has a global binding.

;;; If kb-specific? is specified, system-variable-name is (1) bound to nil at the top
;;; level of a process and (2) has its value switched whenever the current kb is switched,
;;; with saving and (re)initialization or restoring as required to keep it kb-specific.
;;; (Normally, def-kb-specific-variable, as defined below, is used for the kb-specific
;;; case.)

;;; Initialization may be:
;;;
;;;    :no-initial-value, when the variable is not to be initialized at all;
;;;
;;;    :system-frame, when the variable is to be set to a "system frame" (q.v.);
;;;
;;;    value, when the variable is to be set to value (which may not be any of the
;;;         other forms);
;;;
;;;    (quote value), when the variable is to be set to value;
;;;
;;;    (:symbol-value special-variable), when the variable is to be set to the value
;;;         of special-variable; or
;;;
;;;    (:funcall function-symbol . arguments), when the variable is to be set to the
;;;         value of function-symbol applied to the arguments (which are not evaluated).

;;; When initialization is specified, it applies each time an initialization is to be
;;; done.  Initializations may be expected to occur in system-loading order, which
;;; allows an initialization to depend on the value of an earlier system variable.
;;; (This initialization-order guarantee is invalidated if regions of modules have been
;;; incrementally compiled.)

;;; Value-reclaimer?, when specified, is applied to the value of the variable when it is
;;; no longer useful.  In the kb-specific case, this is when the kb is released.

;;; A system variable is always proclaimed a special variable.

(defmacro def-system-variable
          (system-variable-name module-name
           &optional (initialization :no-initial-value)
                      re-evaluate-initialization-on-rebinding?
                      also-bind-globally?
                      value-reclaimer?
                      kb-specific?)
  #+development
  (if (not (loop for system-name in all-systems
                 thereis (memq module-name (system-modules system-name))))
      (warn
        "~%The definition of system variable ~A specifies an unknown module name ~A."
        system-variable-name module-name))
  `(progn
     ;; (proclaim '(special ,system-variable-name))  ; Replaced with defvar -pto 10sep90
     (defvar ,system-variable-name
;             ,@(if (eval-feature :development)
;                   (if (or (numberp initialization)
;                           (null initialization)
;                           (eq initialization t))
;                       `(,initialization)))
       )
     (record-system-variable
       ',system-variable-name ',module-name
       ,(if (or (numberp initialization)
                (null initialization)
                (eq initialization t)
                (keyword-symbol-p initialization))
            initialization
            `',initialization)
       ',re-evaluate-initialization-on-rebinding? ',also-bind-globally?
       ',value-reclaimer? ',kb-specific?)
     ',system-variable-name))

;; The re-evaluate-initialization-on-rebinding? is worthless, really, and should be
;; eliminated, after ensuring that it is not in use anywhere!

;; Use value reclaimers in the non-kb-specific case when a process (window) is "killed"!

;; Check for initialization errors, when possible!

;; All-systems and system-modules, defined in module BOOTSTRAP, should really be
;; "names-of-all-systems" and "system-module-names".

;; Consider converting (quote value) to value, where possible.

;; Consider having keyword instead of optional arguments.



;;; Def-kb-specific-variable defines a `kb-specific variable', a special variable that
;;; (1) is bound (to nil) at the top level of each process, and (2) has its value switched
;;; whenever the current kb is switched, with saving and (re)initialization or restoring
;;; as required to keep it kb-specific.  (More precisely, the binding takes place within
;;; each invocation of with-system-variables that specifies a system having module-name as
;;; a component.  See with-system-variables.)  If also-bind-globally? is specified, then
;;; kb-specific-variable-name is also globally set per initialization, unless it already
;;; has a global binding.  See also def-system-variable above, and see switch-values-of-
;;; kb-specific-variables in module UTILITIES.

(defmacro def-kb-specific-variable
          (kb-specific-variable-name module-name
           &optional (initialization :no-initial-value)
                      also-bind-globally? value-reclaimer?)
  `(def-system-variable ,kb-specific-variable-name ,module-name
     ,initialization nil ,also-bind-globally? ,value-reclaimer? t))

;; One major bug here was just uncovered: the value reclaimer was never being
;; called because reclaim-values-of-kb-specific-variables was never being
;; called.  Now, to recover from this gross oversight, the plan is to take
;; the following steps
;;
;;    (1) check syntax for value-reclaimer? in def-kb-specific-variable
;;        (above), since it was not checked syntactically here, and
;;        several callers actually passed in (QUOTE <function-name>);
;;
;;    (2) fix release-kb to call reclaim-values-of-kb-specific-variables,
;;        which we think should happen right after reclaiming the
;;        kb-specific property lists;
;;
;;    (3) visit all callers and review them for obvious problems AND
;;        comment out the above fix until Monday;
;;
;;    (4) on monday enable the above fix for development and
;;        send mail to all developers advising them that it
;;        will be generally enabled one week from monday; and
;;
;;    (5) enable it one week from monday, i.e., on 12/16/91
;;
;;
;; Fortunately, the number of callers is small.  The only kb-specific
;; variables with reclaimers at this time are as follows:
;;
;;    Module                Function
;;    ---------------------------------------------------------------
;;
;;    WINDOWS1                all-colors
;;                      menu-colors
;;                      menu-colors-sorted-alphabetically
;;                      menu-colors-sorted-by-hue
;;                      -- the above are MHD's
;;
;;    TABLES                all-frames-with-simple-debugging-names
;;                      -- the above is BAH's, I think
;;
;;    CELLS                set-of-all-permanent-computation-styles
;;                      -- the above is BAH's
;;
;;    ENTITIES                modules-and-system-tables-a-list
;;                      -- the above is MHD's
;;
;;    KB-LOAD2                saved-detail-pane-description
;;                      -- the above is MHD's
;;
;;    KB-MERGE                record-of-class-name-conflicts
;;                      record-of-definitional-name-conflicts
;;                      -- the above are MHD's
;;
;;    SEQUENCES                archetypal-stripped-text
;;                      -- the above is MHD's
;;
;; (MHD/BAH 12/6/91)




(defun record-system-variable
       (system-variable-name module-name initialization
        re-evaluate-initialization-on-rebinding?
        also-bind-globally? value-reclaimer? kb-specific?)
  #+development
  (when value-reclaimer?
    (cond
      ((not (symbolp value-reclaimer?))
       (warn "~a was given as the value reclaimer for ~a, but it is not a symbol."
             value-reclaimer?
             system-variable-name))
      ((macro-function value-reclaimer?)
       (warn "~a was given as the value reclaimer for ~a, but it seems to be a macro!"
             value-reclaimer?
             system-variable-name))
      ;; let undefined symbols go, and hope they'll be defined later as
      ;; functions, at least for now. Consider final code later! -mhd, 1/9/01
      ))
  #+development
  (unless (member also-bind-globally? '(t nil))
    (warn "Odd spec (not T or NIL) for also-bind-globally? for ~a variable ~a: ~s"
          (if kb-specific? "KB-specific" "system")
          system-variable-name
          also-bind-globally?))
  (let* ((system-variable-descriptions
           (system-variable-descriptions module-name))
         (system-variable-description?
           (assoc system-variable-name system-variable-descriptions)))
    (if system-variable-description?
        (setf (cdr system-variable-description?)
              (list
                initialization
                re-evaluate-initialization-on-rebinding?
                kb-specific?
                value-reclaimer?))
        (setf (system-variable-descriptions module-name)
              (nconc system-variable-descriptions
                     (list (list
                             system-variable-name
                             initialization
                             re-evaluate-initialization-on-rebinding?
                             kb-specific?
                             value-reclaimer?))))))
  (if also-bind-globally?
      (set-system-variable-as-appropriate system-variable-name initialization)))

;; Omit nils at the end of system variable descriptions, to save a bit of space!

;; This is only called at top level, and so the with-permanent-allocation can be
;; removed.  -jra 1/22/92





;;; Declaration:     let*-or-set-for-system (binding-clauses &body body)
;;; Type:            macro
;;; Purpose:         used instead of let* in situations where we want
;;;                  to use setf in translated code and let* in lisp environments.
;;;                     Currently, this means GSI.   --ncc, paf!
;;;
;;; Arguments:       binding-clauses: a list of variable bindings ala let*.
;;;                  body: the body of a progn.
;;;
;;; Return behavior: same as let*
;;;
;;; Users:           run-system-process in launch.lisp
;;;
;;;
;;;
;;; Side effects:    will bind variables globally in translated code.
;;;                  incurs any side effects from execution of body.
;;; Non-local exits: body may exit non-locally.
;;; Memory impact:   code in body may cons.
;;; Notes:           This is intended for limited usage in launch.lisp & friends.
;;;                  Talk to paf!, ncc or jra before using elsewhere.
;;;

(defmacro let*-or-set-for-system (binding-clauses &body body)
  ;; We should always use SETF in SymScale/MTG2, to be visible to all threads.
  (if (or (or (eval-feature :SymScale) (eval-feature :mtg2))
          (and (boundp 'current-system-being-loaded)
               (eq current-system-being-loaded 'gsi) ; for gsi ONLY,
               (eval-feature :translator))) ; in xlation, use setf; in development, use let*
      (loop
        for binding in binding-clauses
        when (atom binding)
          collect `(setf ,binding nil) into list-of-setfs
        else
          collect `(setf ,(car binding) ,@(cdr binding)) into list-of-setfs
        finally (return `(progn ,@list-of-setfs ,@body)))

      `(let* ,binding-clauses
         ,@body)))



;;; A process should execute, except for the most preliminary initializations, entirely
;;; within the dynamic scope of a with-system-variables form, where system-name and
;;; process-handle are associated with the process.  A with-system-variables form binds
;;; and initializes, in order of definition, all system variables belonging to component
;;; modules of the system named system-name, and keeps track of its initializations (in
;;; process-initializations-alist) under process-handle.  Note that with-system-variables
;;; initializes all kb-specific variables to nil.

;;; When a with-system-variables form is executed with the same process-handle as was
;;; used in an earlier execution of this or another with-system-variables form, those
;;; system variables that were earlier bound (perhaps with "no value") and do not have
;;; the re-evaluate-initialization-on-rebinding? feature are rebound to their
;;; saved initial values (or again "no value").  Thus, the effect of setting a system
;;; variable within the scope of an earlier binding is lost if it is rebound.  If this
;;; is a problem, in the case of a particular system variable, replace that system
;;; variable by a slot in a structure kept as a system variable.

(defmacro with-system-variables ((system-name process-handle) &body body)
  (let ((system-name-var (gensym)))
    `(let ((,system-name-var ,system-name)) ; system-name-var isn't a global, must bind it (lexically!) -ncc, 3/10/94
       ,(if (eval-feature '(and development (not (or mtg2 SymScale))))
            ;; there's no way to support this in SymScale. --binghe
            `(progv (compute-system-variables ,system-name-var) nil
                    (initialize-system-variables
                     ,system-name-var ,process-handle)
                    ,@body)
            `(progn
               (initialize-system-variables
                ,system-name-var ,process-handle)
               ,@body)))))



(defun compute-system-variables (system-name)
  (loop for module-name in (system-modules system-name)
        nconc (loop for (system-variable-name
;                          initialization
;                          re-evaluate-initialization-on-rebinding?
;                          kb-specific?
;                          value-reclaimer?
                          )
                        in (system-variable-descriptions module-name)
                    collect system-variable-name)))



;;; Forget-system-variables-for-module causes all recorded information about system
;;; variables for module module-name to be forgotten, so that a recompilation of that
;;; module will rerecord up-to-date information.  This is for development only.

#+development
(defun forget-system-variables-for-module (module-name)
  (setf (system-variable-descriptions module-name) nil))


;;; Undef-system-variable and undef-kb-specific-variable have the same syntax as
;;; their "def" counterparts, except that they tell the system to forget their
;;; variable names instead of defining them.  This is for development only.

#+development
(defmacro undef-kb-specific-variable
          (kb-specific-variable-name module-name
           &optional (initialization :no-initial-value)
                      also-bind-globally? value-reclaimer?)
  `(progn
     (forget-system-variable ',kb-specific-variable-name ',module-name)
     ;; the rest are ignored:
     ',initialization ',also-bind-globally? ',value-reclaimer?))

#+development
(defmacro undef-system-variable
          (system-variable-name module-name
           &optional (initialization :no-initial-value)
                      re-evaluate-initialization-on-rebinding?
                      also-bind-globally?
                      value-reclaimer?
                      kb-specific?)
  `(progn
     (forget-system-variable ',system-variable-name ',module-name)
     ;; the rest are ignored:
     ',initialization
     ',re-evaluate-initialization-on-rebinding?
     ',also-bind-globally? ',value-reclaimer?
     ',kb-specific?))

#+development
(defun forget-system-variable (system-variable-name module-name)
  (let* ((system-variable-descriptions
           (system-variable-descriptions module-name))
         (system-variable-description?
           (assq system-variable-name system-variable-descriptions)))
    (if system-variable-description?
        (setf (system-variable-descriptions module-name)
              (delq system-variable-description?
                    system-variable-descriptions)))))


(defvar process-initializations-alist nil)

;; This is of the form ({(process-handle {system-variable-name saved-initial-value})}).

(defvar no-saved-initial-value (list 'no-saved-initial-value))

(defun initialize-system-variables (system-name process-handle)
  (loop with process-initializations-entry
          = (or (assq process-handle process-initializations-alist)
                (first (push (list process-handle) process-initializations-alist)))
        as module-name in (system-modules system-name)
        do (loop for (system-variable-name
                       initialization
                       re-evaluate-initialization-on-rebinding?
                       kb-specific?
;                       value-reclaimer?
                       )
                     in (system-variable-descriptions module-name)
                 as saved-initial-value-if-any
                    = (getfq (cdr process-initializations-entry)
                             system-variable-name no-saved-initial-value)
                 do (if (or (eq saved-initial-value-if-any no-saved-initial-value)
                            re-evaluate-initialization-on-rebinding?)
                        (let ((new-value
                                (set-system-variable-as-appropriate
                                  system-variable-name
                                  (if (not kb-specific?)        ; optimize the kb-specific case?
                                      initialization))))
                          (setf (getf (cdr process-initializations-entry)
                                      system-variable-name)
                                new-value))
                        (if (not (eq saved-initial-value-if-any no-saved-initial-value))
                            (set system-variable-name saved-initial-value-if-any))))))

;; Get rid of the optional argument!

;; If there were hundreds of system variables, this could get slow.  Consider
;; speeding it up by ordering the property list and checking to see if the next
;; entry is one step ahead.



;;; Set-system-variable-as-appropriate initializes system-variable-name per
;;; initialization.

(defun set-system-variable-as-appropriate (system-variable-name initialization)
  (if (or (eq initialization :no-initial-value)
          (and (consp initialization)
               (eq (car-of-cons initialization) 'no-initial-value)))
      (set system-variable-name no-saved-initial-value)
      (if (eq initialization :system-frame)
          (current-system-case
            (ab
              (install-system-table
                (let ((in-clear-kb-p t))
                  (make-system-frame system-variable-name)))))
          (set system-variable-name
               (if (atom initialization)
                   initialization
                   (case (first initialization)
                     (quote (second initialization))
                     (:symbol-value
                      (symbol-value (second initialization)))
                     (:funcall
                      (apply (second initialization)
                             (cddr initialization)))
                     (t initialization)))))))





;;; Forget-process-initializations ...

#+development
(defun forget-process-initializations (process-handle)
  (setq process-initializations-alist
        (delq (assq process-handle process-initializations-alist)
              process-initializations-alist 1)))









#+(or development under-test)
(def-system-variable memory-comparison-alist primitives nil)

;; only here because it needed to be after def-system-variable!










;;;; Named Dynamic Extents

;; ben 1/23/91

;;; CLTL says "...entities with dynamic extent obey a stack-like discipline,
;;; paralleling the nested executions of their establishing constructs."
;;; Variables declared to be special are, when bound, rebound for the duration
;;; of the dynamic extent established by thier binding form.  In G2 dynamic
;;; extents are used both to create such special binding, for example to bind
;;; the particulars of the workstation currently being serviced into global
;;; variables.

;;; A `named dynamic extent' is a programmer's abstraction that aids writing and
;;; documenting code that uses dynamic extents.  These constructs add no
;;; additional cost to the code that utilizes them (when that code is compiled
;;; outside development).

;; That isn't exactly true anymore.  We do retain some small vistigal list structures on
;; the symbol that names the dynamic extent since I'm lazy and scared of the subtle
;; details around getting they to hang around only at compile time. - ben 10/27/92

;;; A named dynamic extent may have set of special variables which parameterize
;;; the particular instance of a dynamic extent.  For example a dynamic extent
;;; is often constructed around drawing code with variables to obtain
;;; variations on the usual draw behavor (i.e.  low resolution when
;;; dragging, or erasing instead of drawing).

;;; It is extremely useful to name and document these dynamic extents.  It is
;;; valuable to document those routines that assume they will be executed in a
;;; particular kind of dynamic extent.  It is practical when developing to have
;;; standard ways to check that the expected dynamic extents are actually
;;; have been established.

;;; The term "current" is used to refer to a dynamic extent that is currently
;;; active in this process stack.  The term "named" is used to refer to a
;;; dynamic extent that is declared via def-named-dynamic-extent.

;;; Debugging and development support is provided by routines to check what
;;; dynamic extents the code is currently executing within.  For example:
;;; (assert-that-within-named-dynamic-extent 'temporary-gensym-float-creation)
;;; Routines are provide to display the outstanding named dynamic extents.  For
;;; example: (dx) -- will show the stack of current dynamic extents (dx
;;; 'working-on-chart) -- will show the current bindings of dynamic extent
;;; given.  (dx t) -- will show all the bindings for current dynamic extent
;;; variables.

;;; A named dynamic extent must be declared lexically before any variables are
;;; declared for it, or before any code references it.

;;; There are two inheritance hierarchies for dynamic extents.  The first is
;;; lexical, and is directly analagous to the INCLUDES parameter to defstruct.
;;; When A includes B then when A is established B is also established.  The second form
;;; of inheritance is dynamic.  When A dynamically inherits B then it is always
;;; the case that B must already be current when ever A is established.

;;; It is possible for one dynamic extent to shadow another dynamic extent.  For
;;; example in G2 code executes either in a dynamic extent that where
;;; allocations are permanent or where they are temporary.

;;; A named dynamic extent is introduced by the form `def-named-dynamic-extent'.
;;; The module the name is defined in is specified as well as optionally the
;;; name of additional provide information about dynamic or included superiors.
;;; Information about shadowing may also be given.

;;; The form `defvar-of-named-dynamic-extent' is used to introduce the
;;; individual special variables of this dynamic extent.

;;; Functions use the macro with-named-dynamic-extent establish instances of a
;;; dynamic extent.  `With-named-dynamic-extent' takes, in addition to the name
;;; of the extent being created, a binding list which expands into a let.
;;; `With-named-dynamic-extent*' expands into a let*.  It is usually, but not
;;; always, the case that all variables declared for the dynamic extent are
;;; bound in the corresponding with-named-dynamic extent.

;;; This is not required for numerous reasons.  The one reason is that loop is
;;; often used to enclose a dynamic extent.  The another reason is to ease the
;;; transition into using this abstraction in existing code.  Possibly the most
;;; important reason is that experiance illustrates that the patterns of binding
;;; are just not that simple.

;;; Routines that must execute inside of a particular named dynamic extent may
;;; use the macro `within-named-dynamic-scope' to lexically enclose their code.
;;; Once it is possible to supress the global special proclamation for
;;; variables of a dynamic extent this form will provide the local special
;;; declarations.  In development this macro adds an additional call to assert
;;; that we are actually in the expected scope.  Out of development this adds
;;; the additional cost of a progn.

;; Shadowing doesn't work yet.  It should be a separate declaration.
;; i.e.
;; (def-dynamic-extent-shadowing
;;   (extents with-temporary-creation with-permanent-creation)
;;   (kind mutual))

;; A declaration that a context shouldn't be recursive would be nice.
;;   (def-named-dynamic-extent on-window .... (recursive? nil) ... )

;; A separate declaration that dynamic contexts are "antagonistic," i.e.  they
;; should never be simultanously current would be very helpful.
;; (def-antagonistic-dynamic-extents working-on-expression-for-frame rendering)



;;; `Named-dynamic-extent-description', a global property, is used to hold the
;;; declarative information about the named dynamic extent.  This data structure
;;; is available at compile, load and run time.

(def-global-property-name named-dynamic-extent-description)



;;; `Named-dynamic-extent-description', a list structure, is the data structure
;;; used to store knowledge of a dynamic extent.

; The following is a expansion by hand of:
;    (def-list-structure (named-dynamic-extent-description (:constructor make-named-dynamic-extent-description))
;                    ( name-of-dynamic-extent
;                     module-of-dynamic-extent
;                      dynamic-superiors-list-of-dynamic-extent
;                      shadowing-list-of-dynamic-extent
;                      included-list-of-dynamic-extent . named-dynamic-extent-plist))

(progn
  (defmacro name-of-dynamic-extent (named-dynamic-extent-description)
    `(first ,named-dynamic-extent-description))
  (defmacro module-of-dynamic-extent (named-dynamic-extent-description)
    `(second ,named-dynamic-extent-description))
  (defmacro variables-of-dynamic-extent (named-dynamic-extent-description)
    `(third ,named-dynamic-extent-description))
  (defmacro dynamic-superiors-list-of-dynamic-extent (named-dynamic-extent-description)
    `(fourth ,named-dynamic-extent-description))
  (defmacro shadowing-list-of-dynamic-extent (named-dynamic-extent-description)
    `(fifth ,named-dynamic-extent-description))
  (defmacro included-list-of-dynamic-extent (named-dynamic-extent-description)
    `(sixth ,named-dynamic-extent-description))
  (defmacro named-dynamic-extent-plist (named-dynamic-extent-description)
    `(cdddr (cdddr ,named-dynamic-extent-description)))
  (defun make-named-dynamic-extent-description (name
                                                module
                                                variables-of-dynamic-extent
                                                dynamic-superiors-list-of-dynamic-extent
                                                shadowing-list-of-dynamic-extent
                                                included-list-of-dynamic-extent
                                                named-dynamic-extent-plist)
     (list* name
            module
            variables-of-dynamic-extent
            dynamic-superiors-list-of-dynamic-extent
            shadowing-list-of-dynamic-extent
            included-list-of-dynamic-extent
            named-dynamic-extent-plist))
  'named-dynamic-extent-description)



;;; Currently only a few things are stored on the plist of the dynamic extent
;;; description.  These include:
;;;    unwind?
;;;    excluded-dynamic-superiors

(defmacro named-dynamic-extent-unwind? (named-dynamic-extent-description)
  `(getf
     (named-dynamic-extent-plist ,named-dynamic-extent-description)
     'unwind?))

(defmacro excluded-dynamic-superiors-of-named-dynamic-extent
          (named-dynamic-extent-description)
  `(getf (named-dynamic-extent-plist ,named-dynamic-extent-description)
         'excluded-dynamic-superiors))

;;; `Def-named-dynamic-extent', a macro, introduces a named dynamic extent.  It
;;; must appear lexically prior to any other references to the name.  Additional
;;; arguments, in the form of an alist, must include these:
;;;   (module <module-name>)
;;;     This required argument names the module, that in turn controls the
;;;     initialization order for variables upon process initialization.
;;; The arguments may include:
;;;   (include <named-dynamic-extent-b> ...)
;;;     The variables of this other dynamic extent are implicitly included in
;;;     those defined for this one.
;;;   (dynamic-superior <named-dynamic-extent-c> ...)
;;;     Assertions will be automaticly be done, in development, that this
;;;     named-dynamic-extent-c is current when ever this dynamic extent is
;;;     established.
;;;   (shadows <named-dynamic-extent-x> ...)
;;;     Named-dynamic-extent-x will not be asserted as current if this one is
;;;     more current.
;;;   (unwind? <boolean>)
;;;     If this is false (the default) then in development code a warning is
;;;     generated when ever the dynamic extent exited via stack unwinding.

(defmacro def-named-dynamic-extent (name &body other-arguments-alist)
  "alist arguments include: module, include, dynamic-superior, shadows, unwind?, excluded-dynamic-superiors"
  ;; Assert that the arguments are well formed
  (progn
    (unless (symbolp name)
      (warn "The name of a dynamic extent must be a symbol, not: ~S" name))
    (loop for x in other-arguments-alist
          unless (and (consp x)
                      (<= 1 (length x))
                      (memq (first x) '(module unwind?
                                               shadows
                                               dynamic-superior
                                               includes
                                               excluded-dynamic-superiors))
                      (case (first x)
                        (unwind?
                         (and (= 2 (length x))
                              (memq (second x) '(nil t))))
                        (module
                         (= 2 (length x))
                         ;; I'm not clever enough to assert this is a module name.
                         )
                        (otherwise
                         (every #'(lambda (y)
                                    #+development
                                    (or (named-dynamic-extent-description y)
                                        (eql y name))
                                    #-development
                                    (declare (ignore y))
                                    #-development
                                    t)
                                (rest x)))))
            do
              (warn "An argument to the def-named-dynamic-extent ~S was malformed: ~S" name x)))
  (let ((module nil)
        (dynamic-superiors-list-of-dynamic-extent nil)
        (shadowing-list-of-dynamic-extent nil)
        (excluded-dynamic-superiors? nil)
        (included-list-of-dynamic-extent nil)
        (unwind? nil))
    ;; Unpack the arguments
    (loop for argument in other-arguments-alist
          as (argument-name . argument-value) = argument
          do
            (case argument-name
              (module
               (setf module (first argument-value)))
              (dynamic-superior
               (setf dynamic-superiors-list-of-dynamic-extent argument-value))
              (includes
               (setf included-list-of-dynamic-extent argument-value))
              (shadows
               (setf shadowing-list-of-dynamic-extent argument-value))
              (excluded-dynamic-superiors
               (setf excluded-dynamic-superiors? argument-value))
              (unwind?
               (setf unwind? (first argument-value)))))

    (unless module
      (warn "A module is required in the def-named-dynamic-extent for ~S" name))

    `(progn
       #+development
       (register-definition ',name 'named-dynamic-extent)

       #+(or mtg2 SymScale)
       (defvar ,name (tx:make-recursive-lock :name ,(format nil "~S" name)))

       (eval-when (:compile-toplevel :load-toplevel :execute)
         (let ((named-dynamic-extent-description
                 (make-named-dynamic-extent-description
                   ',name
                   ',module
                   nil
                   ',dynamic-superiors-list-of-dynamic-extent
                   ',shadowing-list-of-dynamic-extent
                   ',included-list-of-dynamic-extent
                   nil)))
           ,@(when unwind?
               `((setf (named-dynamic-extent-unwind? named-dynamic-extent-description) t)))
           ,@(when excluded-dynamic-superiors?
               `((setf (excluded-dynamic-superiors-of-named-dynamic-extent named-dynamic-extent-description)
                     ',excluded-dynamic-superiors?)))
           (setf (named-dynamic-extent-description ',name) named-dynamic-extent-description)))
       ',name
       )))

;; It would be nice...
;; There are common situations where a dynamic extent is not fully established
;; until some other things are done.  In these situations it would be nice to
;; have a
;;   <start     <enter   ...   leave>    end>
;; topology to the extent.  Assertions about dynamic superiors might then be
;; checked just after the enter.  This comes up more that I would have expected.



;;; `Defvar-of-named-dynamic-extent' is used to declare a special variable that
;;; is bound and useful when a particular dynamic extent is current.  A name for
;;; the dynamic extent, along with a name for the variable are given.
;;; Additional details about the special variable maybe given by other arguments
;;; in the form of an alist.

;;; The "default" binding(s) maybe specified by zero or more of the following:
;;;  (kb-binding <form>)
;;;  (process-binding <form>)
;;;  (global-binding <form>)
;;; The default is to leave the variable unbound in all three contexts.
;;; If a kb-binding is specified then the process-binding is defaults to nil.
;;; There currently no mechinism to specify a reclaimer for the kb-binding.

;;; You may supress the special proclaimation for the variable by overridding the
;;; default of the proclaim-special-globally argument of T.
;;;     (proclaim-special-globally <boolean>)
;;; That allow you to assure that the variable is only used in contexts that
;;; explicitly declare their intent to use it.

(defmacro defvar-of-named-dynamic-extent
          (variable named-dynamic-extent &rest other-arguments-alist)
  "other arguments include global-binding, process-binding, kb-binding and proclaim-special-globally"

  ;; Check the arguments are well formed
  (progn
    (unless (every
              #'(lambda (x) (and (consp x) (= 2 (length x))))
              other-arguments-alist)
      (warn "defvar-of-named-dynamic-extent for ~S: Expected a list of pairs in other-arguments-alist" variable))
    (unless (named-dynamic-extent-description named-dynamic-extent)
      (warn "defvar-of-named-dynamic-extent for ~S: Expected a known named-dynamic-extent" variable)))

  (let* ((module
           (module-of-dynamic-extent
             (named-dynamic-extent-description
               named-dynamic-extent)))
         (unspecified '#:unspecified)
         (global-binding unspecified)
         (process-binding unspecified)
         (kb-binding unspecified)
         (proclaim-special-globally t)
         (binding-functions? ()))


    ;; Unpack the arguments
    (loop for argument in other-arguments-alist
          as (argument-name argument-value) = argument
          do
      (case argument-name
        (kb-binding
         (setq kb-binding argument-value))
        (process-binding
         (setq process-binding argument-value))
        (global-binding
         (setq global-binding argument-value))
        (proclaim-special-globally
         (setq proclaim-special-globally argument-value))))

    ;; Special handling of kb-binding.
    (unless (eq kb-binding unspecified)
      (when (eq process-binding unspecified)
        (setf process-binding nil))
      (unless (eq process-binding nil)
        (warn "In the defvar-of-named-dynamic-extent of ~S The process binding must be nil when a kb-binding is specified."
              variable)))

    ;; Generate functions to do the binding if necessary.
    (macrolet ((trivial-p (x) `(or (atom ,x)
                                 (eq (car ,x) 'quote))))
      (unless (trivial-p kb-binding)
        (let ((func (intern (concatenate'string "COMPUTE-KB-INITIAL-VALUE-FOR-" (symbol-name variable)))))
          (push `(defun-simple ,func () ,kb-binding) binding-functions?)
          (setf kb-binding `(:funcall ,func))))
      (unless (trivial-p process-binding)
        (let ((func (intern (concatenate'string "COMPUTE-PROCESS-INITIAL-VALUE-FOR-" (symbol-name variable)))))
          (push `(defun-simple ,func () ,process-binding) binding-functions?)
          (setf process-binding `(:funcall ,func)))))

    `(progn
       #+development
       (eval-when (:compile-toplevel :load-toplevel :execute)
         (pushnew ',variable (variables-of-dynamic-extent
                               (named-dynamic-extent-description
                                 ',named-dynamic-extent))))

       ,@binding-functions?

       ,@(cond
           ;; KB Binding
           ((not (eq kb-binding unspecified))
            `((def-system-variable ,variable ,module
                ,kb-binding
                nil
                ,(if (eq global-binding unspecified)
                     nil
                     t)
                nil
                t)))

           ;; Process Binding
           ((not (eq process-binding unspecified))
            `((def-system-variable ,variable ,module
                ,process-binding
                nil
                ,(if (eq global-binding unspecified)
                     nil
                     t)
                nil
                nil)))

           ;; Global Binding
           ((not (eq global-binding unspecified))
            `((defvar ,variable ,global-binding)))

           ;; No Binding
           (t
            (if proclaim-special-globally
                `((defvar ,variable))
                `((defvar ,variable)))))
       #+development
       (register-definition ',variable 'variable-of-named-dynamic-extent)
       ',variable)))

;; Chestnut doesn't support (proclaim '(special ...)), so we have to do a defvar.



;;; `Def-dynamic-extent' expands into a def-named-dynamic-extent and a
;;; def-additional-slots-of-named-dynamic-extent form.  It provides a
;;; defstruct like syntac for defining a dynamic extent.

(defmacro def-dynamic-extent ((name &rest options) &body slots)
  `(progn
    (def-named-dynamic-extent ,name ,@options)
    (def-additional-slots-of-named-dynamic-extent ,name ,@slots)))



;;; `Def-additional-slots-of-named-dynamic-extent' expands into one
;;; defvar-of-named-dynamic-extent for each slot given.  The name of
;;; dynamic extent need be given only in header.

(defmacro def-additional-slots-of-named-dynamic-extent (name &body slots)
  `(progn
    ,@(loop for slot in slots
            collect
            `(defvar-of-named-dynamic-extent ,(car slot) ,name ,@(rest slot)))))



#+development
(def-system-variable pool-of-conses-for-stack-of-current-named-dynamic-extents primitives nil)

#+development
(defmacro dynamic-extent-cons (car cdr)
  `(let ((cons (or pool-of-conses-for-stack-of-current-named-dynamic-extents
                   (cons nil nil))))
     (setf pool-of-conses-for-stack-of-current-named-dynamic-extents (cdr cons))
     (setf (car cons) ,car)
     (setf (cdr cons) ,cdr)
     cons))

#+development
(defmacro reclaim-dynamic-extent-cons (cons)
  `(let ((cons ,cons))
     (setf (cdr cons) pool-of-conses-for-stack-of-current-named-dynamic-extents)
     (setf pool-of-conses-for-stack-of-current-named-dynamic-extents cons)
     nil))

#+development
(def-system-variable stack-of-current-named-dynamic-extents primitives nil)

(defmacro assert-that-within-named-dynamic-extent (named-dynamic-extent
                                                    &optional
                                                    (reason-string? ""))
  #-development
  (declare (ignore named-dynamic-extent reason-string?))
  #-development
  nil

  #+development
  `(let ((named-dynamic-extent ,named-dynamic-extent))
     (unless (current-named-dynamic-extent-p named-dynamic-extent)
       (cerror "Continue ignoring missing dynamic scope"
               "Not currently in the dynamic extent ~S ~A."
               named-dynamic-extent ,reason-string?))))

(defmacro assert-that-not-within-named-dynamic-extent (named-dynamic-extent
                                                       &optional
                                                       (reason "Currently in the unexpected dynamic extent ~S.")
                                                       (format-arg1 named-dynamic-extent)
                                                       format-arg2
                                                       format-arg3)
  #-development
  (declare (ignore reason format-arg1 format-arg2 format-arg3)
           (ignorable named-dynamic-extent))
  #-development
  nil

  #+development
  `(let ((named-dynamic-extent ,named-dynamic-extent))
     (when (current-named-dynamic-extent-p named-dynamic-extent)
       (cerror "Continue, ignoring the problem"
               ,reason
               ,format-arg1
               ,@(when format-arg2 (list format-arg2))
               ,@(when format-arg3 (list format-arg3))))))

#+development
(defun assert-superiors-of-named-dynamic-extent-are-current (named-dynamic-extent)
  ;; See if the dynamic superiors are all current
  (let* ((named-dynamic-extent-description
           (named-dynamic-extent-description named-dynamic-extent)))
    ;; Check for illegal superiors
    (loop for excluded-dynamic-superior
              in (excluded-dynamic-superiors-of-named-dynamic-extent
                   named-dynamic-extent-description)
          when (current-named-dynamic-extent-p named-dynamic-extent)
            do (cerror "Continue"
                       "It is illegal to establish ~S when ~S is already current."
                       named-dynamic-extent
                       excluded-dynamic-superior))
    ;; Check dynamic superiors
    (loop for dynamic-superior
              in (dynamic-superiors-list-of-dynamic-extent named-dynamic-extent-description)
          do
            (assert-that-within-named-dynamic-extent dynamic-superior))
    ;; Check Lexical superiors
    (loop for lexical-superior
              in (included-list-of-dynamic-extent named-dynamic-extent-description)
          do
            (assert-superiors-of-named-dynamic-extent-are-current lexical-superior))))

#+development
(defun enter-named-dynamic-extent (named-dynamic-extent)
  (assert-superiors-of-named-dynamic-extent-are-current named-dynamic-extent)
  (setf stack-of-current-named-dynamic-extents
        (dynamic-extent-cons
          named-dynamic-extent
          stack-of-current-named-dynamic-extents)))

;; the assert could be removed if it is a performance problem.

#+development
(defun exit-named-dynamic-extent ()
  (let ((cons stack-of-current-named-dynamic-extents))
    (when cons
      (setf stack-of-current-named-dynamic-extents (cdr cons))
      (reclaim-dynamic-extent-cons cons))))

#+development
(defun current-named-dynamic-extent-p (named-dynamic-extent)
  (loop for current-dynamic-extent in stack-of-current-named-dynamic-extents
        do
          (if (eq current-dynamic-extent named-dynamic-extent)
              (return t)
              (case (current-named-dynamic-extent-p-1
                     named-dynamic-extent
                     (named-dynamic-extent-description current-dynamic-extent))
                (no-match nil)
                (match          (return t))
                (mismatch (return nil))))
        finally
          (return nil)))

#+development
(defun current-named-dynamic-extent-p-1 (desired-named-dynamic-extent description-of-an-established-dynamic-extent)
  (loop
    with included-extents
      = (included-list-of-dynamic-extent description-of-an-established-dynamic-extent)
    initially
      (when (memq desired-named-dynamic-extent
                  (included-list-of-dynamic-extent description-of-an-established-dynamic-extent))
        (return 'match))
      (when (memq desired-named-dynamic-extent
                  (shadowing-list-of-dynamic-extent
                    description-of-an-established-dynamic-extent))
        (return 'mismatch))
    for included-extent        in included-extents
    as description-of-an-established-dynamic-extent-1
       = (named-dynamic-extent-description included-extent)
    as match =
       (current-named-dynamic-extent-p-1
         desired-named-dynamic-extent
         description-of-an-established-dynamic-extent-1)
    unless (eql match 'no-match) do (return match)
    finally (return 'no-match)))

;;; With-named-dynamic-extent and With-named-dynamic-extent* establish a dynamic
;;; extent and give it a name.  With-named-dynamic-extent handles its bindings like
;;; LET, while with-named-dynamic-extent* handles its bindings like LET*.  The name
;;; must have been declared as a named-dynamic-scope lexically prior to this form.
;;; The name must be a symbol; it is not evaluated.

;;; In development this construct costs one unwind protect, two calls to minor
;;; functions, and one assert-that-within-dynamic-extent for each dynamic superior
;;; of the dynamic extent being established. If control is thrown pass this form
;;; a warning is generated.  That warning is not generated if the extent is declared
;;; as unwindable.

;;; Outside of development this is equivalent to a LET or LET*
;;; Inside of development this returns one, and only one value.

(defmacro with-named-dynamic-extent (name bindings &body body)
  `(with-named-dynamic-extent-1 let ,name ,bindings ,body))

(defmacro with-named-dynamic-extent* (name bindings &body body)
  `(with-named-dynamic-extent-1 let* ,name ,bindings ,body))

(defmacro with-named-dynamic-extent-1 (let-flavor name bindings body)
  #-(or mtg2 development SymScale)
  (declare (ignore name))
  #-(or mtg2 development SymScale)
  `(,let-flavor ,bindings ,@body)

  #+(and (not development) (or mtg2 SymScale))
  `(tx:with-lock-held (,name)
     (within-named-dynamic-extent ,name
       (,let-flavor ,bindings
         (progn ,@body))))

  #+development
  (progn
    (unless (named-dynamic-extent-description name)
      (warn "Unknown named dynamic extent ~S" name))
    (let ((unwind-flavor
          (if (named-dynamic-extent-unwind?
                (named-dynamic-extent-description name))
              'multiple-value-prog1 ;; 'prog1
              'unwind-protect-for-development)))
      (let (; (result (gensym))
            )
        `(#-(or mtg2 SymScale) progn ; let (,result)
          #+(or mtg2 SymScale) tx:with-lock-held #+(or mtg2 SymScale) (,name)
           (enter-named-dynamic-extent ',name)
           (,unwind-flavor
            ,@(when (eq unwind-flavor 'unwind-protect-for-development) `(,name)) ;; '(named-dynamic-extent)
            (within-named-dynamic-extent ,name
              (,let-flavor ,bindings
                (progn ,@body)  ; (setf ,result (progn @body))
               ))
            (exit-named-dynamic-extent))
;           ,result
           )))))

;; It would be nice to have a mode where these noted variables being bound that are not
;; declared as being in the dynamic extent.

;;; `With-named-dynamic-extent-given' is identical to with-named-dynamic-extent with these
;;; exceptions.  The name given is provided by a form, which is evaluated to
;;; obtain the name.  No warnings are provided upon unexpected unwinding. No checking is
;;; done required dynamic superior extents are current.

;;; Outside of development this equivlent to a let or let*, but inside of development
;;; this form does not return any useful value.

(defmacro with-named-dynamic-extent-given (name-form bindings &body body)
  `(with-named-dynamic-extent-given-1 let ,name-form ,bindings ,body))

(defmacro with-named-dynamic-extent-given* (name-form bindings &body body)
  `(with-named-dynamic-extent-given-1 let* ,name-form ,bindings ,body))

(defmacro with-named-dynamic-extent-given-1 (let-flavor name-form bindings body)
  #-development
  `(progn
     ,name-form ; in case it has side effects.
     (,let-flavor ,bindings
      ,@body))

  #+development
  (let ((name (gensym)))
    `(let ((,name ,name-form))
       (enter-named-dynamic-extent ,name)
       (unwind-protect-for-development given-named-dynamic-extent
                                       (,let-flavor ,bindings ,@body)
        (exit-named-dynamic-extent)))))

;; This form is useful when using progv or symbol-value to establish the bindings.
;; It is technically feasible to remove all the exceptions.
;; The bindings seem sort of useless unless you know that the set of possible
;; extents all include some known extent.


(defmacro within-named-dynamic-extent (name &body body)
  #-development
  (declare (ignore name))
  #+development
  (unless (and (symbolp name)
               (named-dynamic-extent-description name))
    (warn
      "In within-named-dynamic-extent: Unknown named-dynamic-extent ~S (or not a symbol)"
      name))
  `(progn
     #+development
     (assert-that-within-named-dynamic-extent ',name)
     ,@body))

#+development
(defun show-current-named-dynamic-extent-1 (named-dynamic-extent
                                            current-named-dynamic-extent
                                            variables-of-dynamic-extent
                                            this-stack)
  (when (or (eq named-dynamic-extent t)
            (eq named-dynamic-extent current-named-dynamic-extent))
    (loop for variable in variables-of-dynamic-extent
          as variable-might-have-been-rebound-p
             = (loop for more-current-stack on stack-of-current-named-dynamic-extents
                     as older-dynamic-extent = (first more-current-stack)
                     until (eq this-stack more-current-stack)
                     when (memq variable
                                (variables-of-dynamic-extent
                                  (named-dynamic-extent-description
                                    older-dynamic-extent)))
                       do
                         (return t)
                     finally
                       (return nil))
          do
            (format t "~(~& ~35A ~S~)"
                    variable
                    (if (boundp variable)
                        (symbol-value variable)
                        '<unbound>))
            (when variable-might-have-been-rebound-p
              (format t "~65T; possibly shadowed")))))

#+development
(defun show-current-named-dynamic-extent (named-dynamic-extent)
  (cond
    ((and (not (member named-dynamic-extent '(nil t)))
          (or (not stack-of-current-named-dynamic-extents)
              (not (member named-dynamic-extent
                           stack-of-current-named-dynamic-extents))))
     (cond
       ((not stack-of-current-named-dynamic-extents)
        (format t "~&No named dynamic extents are apparent."))
       ((not (named-dynamic-extent-description named-dynamic-extent))
        (format t "Unknown dynamic extent ~S." named-dynamic-extent))
       (t
        (format t "~&~S not currently active." named-dynamic-extent)))
     (when (and named-dynamic-extent
                (named-dynamic-extent-description named-dynamic-extent))
       (labels ((show-dx (name)
                  (loop with named-dynamic-extent-description
                        = (named-dynamic-extent-description name)
                        for variable
                            in (variables-of-dynamic-extent
                                 named-dynamic-extent-description)
                        do
                    (format t "~(~& ~35A ~S~)"
                            variable
                            (if (boundp variable)
                                (symbol-value variable)
                                '<unbound>))
                        finally
                          (loop for included
                                    in (included-list-of-dynamic-extent
                                         named-dynamic-extent-description)
                                do
                            (format t "~&Including: ~S" included)
                            (show-dx included)))))
         (show-dx named-dynamic-extent))))
    (t
     (loop with got-one = nil
           for this-stack on stack-of-current-named-dynamic-extents
           as current-named-dynamic-extent = (first this-stack)
           as named-dynamic-extent-description =
           (named-dynamic-extent-description current-named-dynamic-extent)
           do
       (when (or (memq named-dynamic-extent '(t nil))
                 (eq named-dynamic-extent current-named-dynamic-extent))
         (format t "~&; ~A" current-named-dynamic-extent))
       (when (or (eq named-dynamic-extent t)
                 (eq named-dynamic-extent current-named-dynamic-extent))
         (show-current-named-dynamic-extent-1
           named-dynamic-extent
           current-named-dynamic-extent
           (variables-of-dynamic-extent named-dynamic-extent-description)
           this-stack)
         (loop for included-dynamic-extent
                   in (included-list-of-dynamic-extent
                        named-dynamic-extent-description)
               do
           (format t "~& ; including ~(~A~)" included-dynamic-extent)
           (show-current-named-dynamic-extent-1
             named-dynamic-extent
             current-named-dynamic-extent
             (variables-of-dynamic-extent
               (named-dynamic-extent-description
                 included-dynamic-extent))
             this-stack)))
       (when (eq named-dynamic-extent current-named-dynamic-extent)
         (setf got-one t)
         (loop-finish))
           finally
             (unless got-one
               (unless (memq named-dynamic-extent '(nil t))
                 (let ((named-dynamic-extent-description
                         (named-dynamic-extent-description
                           named-dynamic-extent)))
                   (cond
                     ((not named-dynamic-extent-description)
                      (format
                        t
                        "~&~S is not the name of a known named-dynamic-extent."
                        named-dynamic-extent))
                     (t
                      (format t
                              "~&The dynamic extent ~S is not currently active."
                              named-dynamic-extent)
                      (show-current-named-dynamic-extent-1
                        named-dynamic-extent
                        named-dynamic-extent
                        (variables-of-dynamic-extent
                          named-dynamic-extent-description)
                        nil)
                      (loop for included-dynamic-extent
                                in (included-list-of-dynamic-extent
                                     named-dynamic-extent-description)
                            do
                        (format t "~& ; including ~(~A~)"
                                included-dynamic-extent)
                        (show-current-named-dynamic-extent-1
                          included-dynamic-extent
                          included-dynamic-extent
                          (variables-of-dynamic-extent
                            (named-dynamic-extent-description
                              included-dynamic-extent))
                          nil))))))))))
  (values))

;; Computing the "possibly shadowed" output makes this O(N^2) for stack depth.
;; The calls to show-current-named-dynamic-extent-1 in the FINALLY are too wierd!
;; This doesn't work if the extent is active by inclusion.

#+development
(defun dx (&optional named-dynamic-extent)
  (show-current-named-dynamic-extent named-dynamic-extent))


#+development
(defun search-dynamic-extent-for-thing-of-type (ab-type-name)
  (declare (ignore ab-type-name))
  nil)





(eval-when (:compile-toplevel :load-toplevel :execute)
(defun declare-gsi-api-symbol-1 (name)
  (setf (get name 'gsi-api-symbol) t))
)

(defmacro declare-gsi-api-symbol (name)
  (unless (eval-feature ':no-macros)
    `(eval-when (:compile-toplevel :load-toplevel :execute)
       (declare-gsi-api-symbol-1 ',name))))


;;;; Foreign Function Cruft

;; jh, 8/11/97.  The def-debug-api-function for x-error needs to happen before
;; Lucid loads our foreign libraries so it can properly define to foreign symbol
;; "_x_error".

;;; The macro `def-debug-api-function' defines a LISP function which can be
;;; called back from C code.  Intended for debugging utilities only.

(defmacro def-debug-api-function (name-and-options argument-specs &body body)
  (cond ((and (eval-feature :chestnut-3)
              (eval-feature :chestnut-trans))
         (with-package-specific-symbols (tx |::| def-foreign-callable)
           `(def-foreign-callable ,name-and-options ,argument-specs
              ,@body)))
        ((or (eval-feature :lucid) (eval-feature :allegro))
         #+(or lucid allegro)
         `(lcl::def-foreign-callable ,name-and-options ,argument-specs
            ,@body))
        (t
         nil)))

(def-debug-api-function (g2int-x-error (:return-type :signed-32bit))
    ((error-code :signed-32bit))
;     (error-string :object)                                    ; A C string!
  #+development
  (break "Error ~d from X server." error-code)
  error-code)


;Note that the following three forms work in both Lucid and Chestnut, because
; lcl::def-foreign-callable and tx:def-foreign-callable are the same symbol.
 

;;; callback into lisp to handle network and scheduler events. (from netevent.lisp)

(def-concept g2int-network-event-handler)
(declare-gsi-api-symbol g2int-network-event-handler)

(eval-when (:compile-toplevel)
  (defmacro g2int-network-event-handler-macro ()
    `(handle-event-internal event-code event-socket-handle event-status-code)))

#+chestnut-3 ;SS_G2L
(def-lisp-api-function (g2int-network-event-handler (:return-type :fixnum))
    ((event-code :fixnum)
     (event-socket-handle :fixnum)
     (event-status-code :fixnum))
  (g2int-network-event-handler-macro))

#+(and sbcl (not chestnut-3))
(progn
  (sb-alien:define-alien-routine g2int-network-event-handler-init-call-handle
      sb-alien:void
    (ptr (function sb-alien:int sb-alien:int sb-alien:int sb-alien:int)))
  
  (sb-alien::define-alien-callback g2int-network-event-handler
      sb-alien:int
      ((event-code sb-alien:int)
       (event-socket-handle sb-alien:int)
       (event-status-code sb-alien:int))
    (g2int-network-event-handler-macro)))

#+(and lispworks (not chestnut-3))
(progn
  (fli:define-foreign-function (g2int-network-event-handler-init-call-handle
                                "g2int_network_event_handler_init_call_handle")
      ((ptr :pointer))
    :result-type :void)

  (fli:define-foreign-callable ("g2int_network_event_handler" :result-type :long)
      ((event-code :long)
       (event-socket-handle :long)
       (event-status-code :long))
    (g2int-network-event-handler-macro))
		
  (defvar g2int-network-event-handler
    (fli:make-pointer :symbol-name "g2int_network_event_handler")))

#+(and clozure (not chestnut-3))
(progn
  (defun g2int-network-event-handler-init-call-handle (handler)
    (declare (type ccl:macptr handler))
    (ccl:external-call "g2int_network_event_handler_init_call_handle"
                       :address handler
                       :void))

  (ccl:defcallback g2int-network-event-handler (:signed-fullword event-code
                                                :signed-fullword event-socket-handle
                                                :signed-fullword event-status-code
                                                :signed-fullword)
    (g2int-network-event-handler-macro)))

(def-concept g2int-open-fd-callback)
(declare-gsi-api-symbol g2int-open-fd-callback)

(eval-when (:compile-toplevel)
  (defmacro g2int-open-fd-callback-macro ()
    `(current-system-case
       ((gsi #+gsi-in-g2 ab)
        (call-gsi-open-fd-callback fd))
       (t fd))))

#+chestnut-3
(def-lisp-api-function (g2int-open-fd-callback (:return-type :fixnum))
    ((fd :fixnum))
  (g2int-open-fd-callback-macro))

#+(and sbcl (not chestnut-3))
(progn
  (sb-alien:define-alien-routine g2int-open-fd-callback-init-call-handle
      sb-alien:void
    (ptr (function sb-alien:int sb-alien:int)))

  (sb-alien::define-alien-callback g2int-open-fd-callback
      sb-alien:int
      ((fd sb-alien:int))
    (g2int-open-fd-callback-macro)))

#+(and lispworks (not chestnut-3))
(progn
  (fli:define-foreign-function (g2int-open-fd-callback-init-call-handle
                                "g2int_open_fd_callback_init_call_handle")
      ((ptr :pointer))
    :result-type :void)

  (fli:define-foreign-callable ("g2int_open_fd_callback" :result-type :long)
      ((fd :long))
    (g2int-open-fd-callback-macro))

  (defvar g2int-open-fd-callback
    (fli:make-pointer :symbol-name "g2int_open_fd_callback")))

#+(and clozure (not chestnut-3))
(progn
  (defun g2int-open-fd-callback-init-call-handle (handler)
    (declare (type ccl:macptr handler))
    (ccl:external-call "g2int_open_fd_callback_init_call_handle"
                       :address handler
                       :void))

  (ccl:defcallback g2int-open-fd-callback (:signed-fullword fd
                                           :signed-fullword)
    (g2int-open-fd-callback-macro)))

(def-concept g2int-close-fd-callback)
(declare-gsi-api-symbol g2int-close-fd-callback)

(eval-when (:compile-toplevel)
  (defmacro g2int-close-fd-callback-macro ()
    `(current-system-case
       ((gsi #+gsi-in-g2 ab)
        (call-gsi-close-fd-callback fd))
       (t fd))))

#+chestnut-3
(def-lisp-api-function (g2int-close-fd-callback (:return-type :fixnum))
    ((fd :fixnum))
  (g2int-close-fd-callback-macro))

#+(and sbcl (not chestnut-3))
(progn
  (sb-alien:define-alien-routine g2int-close-fd-callback-init-call-handle
      sb-alien:void
    (ptr (function sb-alien:int sb-alien:int)))
  
  (sb-alien::define-alien-callback g2int-close-fd-callback
      sb-alien:int
      ((fd sb-alien:int))
    (g2int-close-fd-callback-macro)))

#+(and lispworks (not chestnut-3))
(progn                                                                   
  (fli:define-foreign-function (g2int-close-fd-callback-init-call-handle
                                "g2int_close_fd_callback_init_call_handle")
      ((ptr :pointer))
    :result-type :void)

  (fli:define-foreign-callable ("g2int_close_fd_callback" :result-type :long)
      ((fd :long))
    (g2int-close-fd-callback-macro))

  (defvar g2int-close-fd-callback
    (fli:make-pointer :symbol-name "g2int_close_fd_callback")))

#+(and clozure (not chestnut-3))
(progn
  (defun g2int-close-fd-callback-init-call-handle (handler)
    (declare (type ccl:macptr handler))
    (ccl:external-call "g2int_close_fd_callback_init_call_handle"
                       :address handler
                       :void))

  (ccl:defcallback g2int-close-fd-callback (:signed-fullword fd
                                            :signed-fullword)
    (g2int-close-fd-callback-macro)))

(def-concept g2int-writing-fd-callback)
(declare-gsi-api-symbol g2int-writing-fd-callback)

(eval-when (:compile-toplevel)
  (defmacro g2int-writing-fd-callback-macro ()
    `(current-system-case
       ((gsi #+gsi-in-g2 ab)
        (call-gsi-writing-fd-callback fd))
       (t fd))))

#+chestnut-3
(def-lisp-api-function (g2int-writing-fd-callback (:return-type :fixnum))
     ((fd :fixnum))
  (g2int-writing-fd-callback-macro))

#+(and sbcl (not chestnut-3))
(progn
  (sb-alien:define-alien-routine g2int-writing-fd-callback-init-call-handle
      sb-alien:void
    (ptr (function sb-alien:int sb-alien:int)))

  (sb-alien::define-alien-callback g2int-writing-fd-callback
      sb-alien:int
      ((fd sb-alien:int))
    (g2int-writing-fd-callback-macro)))

#+(and lispworks (not chestnut-3))
(progn
  (fli:define-foreign-function (g2int-writing-fd-callback-init-call-handle
                                "g2int_writing_fd_callback_init_call_handle")
      ((ptr :pointer))
    :result-type :void)

  (fli:define-foreign-callable ("g2int_writing_fd_callback" :result-type :long)
      ((fd :long))
    (g2int-writing-fd-callback-macro))

  (defvar g2int-writing-fd-callback
    (fli:make-pointer :symbol-name "g2int_writing_fd_callback")))

#+(and clozure (not chestnut-3))
(progn
  (defun g2int-writing-fd-callback-init-call-handle (handler)
    (declare (type ccl:macptr handler))
    (ccl:external-call "g2int_writing_fd_callback_init_call_handle"
                       :address handler
                       :void))

  (ccl:defcallback g2int-writing-fd-callback (:signed-fullword fd
                                              :signed-fullword)
    (g2int-writing-fd-callback-macro)))

(def-concept g2int-not-writing-fd-callback)
(declare-gsi-api-symbol g2int-not-writing-fd-callback)

(eval-when (:compile-toplevel)
  (defmacro g2int-not-writing-fd-callback-macro ()
    `(current-system-case
       ((gsi #+gsi-in-g2 ab)
        (call-gsi-not-writing-fd-callback fd))
       (t fd))))

#+chestnut-3
(def-lisp-api-function (g2int-not-writing-fd-callback (:return-type :fixnum))
    ((fd :fixnum))
  (g2int-not-writing-fd-callback-macro))

#+(and sbcl (not chestnut-3))
(progn
  (sb-alien:define-alien-routine g2int-not-writing-fd-callback-init-call-handle
      sb-alien:void
    (ptr (function sb-alien:int sb-alien:int)))
  
  (sb-alien::define-alien-callback g2int-not-writing-fd-callback
      sb-alien:int
      ((fd sb-alien:int))
    (g2int-not-writing-fd-callback-macro)))

#+(and lispworks (not chestnut-3))
(progn
  (fli:define-foreign-function (g2int-not-writing-fd-callback-init-call-handle
                                "g2int_not_writing_fd_callback_init_call_handle")
      ((ptr :pointer))
    :result-type :void)

  (fli:define-foreign-callable ("g2int_not_writing_fd_callback" :result-type :long)
      ((fd :long))
    (g2int-not-writing-fd-callback-macro))

  (defvar g2int-not-writing-fd-callback
    (fli:make-pointer :symbol-name "g2int_not_writing_fd_callback")))

#+(and clozure (not chestnut-3))
(progn
  (defun g2int-not-writing-fd-callback-init-call-handle (handler)
    (declare (type ccl:macptr handler))
    (ccl:external-call "g2int_not_writing_fd_callback_init_call_handle"
                       :address handler
                       :void))

  (ccl:defcallback g2int-not-writing-fd-callback (:signed-fullword fd
                                                  :signed-fullword)
    (g2int-not-writing-fd-callback-macro)))

;; jh, 7/19/93.  Added def-callables for the functions g2_signal_handler(),
;; g2_signal_handler_for_launch(), and service_sigalrm_signal().
;; In Chestnut, these are the translated names of
;; Lisp functions designed to be called from our handwritten C code in
;; libcprim.a.  In Lucid, these are C functions which end up calling Lisp code
;; through the def-callable facility.  This workaround is necessary because the
;; object files in libcprim.a are compiled using the preprocessor switch
;; CHESTNUT, causing Chestnut constructs to be seen by Lucid when it calls
;; sys::load-foreign-libraries to link dynamically with libcprim.a.

;; jh, 8/16/93.  Changed the compile-switching so that the dummy foreign symbols
;; defined by lucid::def-foreign-callable will get created in every Lucid build
;; environment except :chestnut-trans.  These dummy foreign symbols will thereby
;; suppress "undefined foreign symbol" warnings in both development and
;; translation macro passes, but will allow C code generated by the translation
;; pass to link correctly with the signal handlers in g2signal.c.

;; MHD, 6/12/00. for Allegro, the following three are declared as foreign
;; functions by direct means below.  We had some problems getting the following
;; calls digested by Allegro's LCL compatibility version of
;; def-foreign-callable.

#+(and lucid (not :chestnut-trans))
(lucid::def-foreign-callable (g2-signal-handler-for-lucid
                              (:name #-solaris "_g2int_signal_handler"
                                     #+solaris "g2int_signal_handler")
                              (:return-type :lisp)) ;return value discarded
    ()
    (g2int-signal-handler))

#+(and lucid (not :chestnut-trans))
(lucid::def-foreign-callable (g2-signal-handler-for-launch-for-lucid
                              (:name #-solaris "_g2int_signal_handler_for_launch"
                                     #+solaris "g2int_signal_handler_for_launch")
                              (:return-type :lisp)) ;return value discarded
    ()
    (g2int-signal-handler-for-launch))

#+(and lucid (not :chestnut-trans))
(lucid::def-foreign-callable (service-sigalrm-signal-for-lucid
                              (:name #-solaris "_g2int_service_sigalrm_signal"
                                     #+solaris "g2int_service_sigalrm_signal")
                              (:return-type :lisp)) ;return value discarded
    ()
    (g2int-service-sigalrm-signal))

#+allegro
(progn
(ff:defun-c-callable g2int-service-sigalrm-signal ())
(ff:register-function 'g2int-service-sigalrm-signal)

(ff:defun-c-callable g2int-signal-handler ())
(ff:register-function 'g2int-signal-handler)

(ff:defun-c-callable g2int-signal-handler-for-launch ())
(ff:register-function 'g2int-signal-handler-for-launch)
)






(def-gensym-c-function c-get-name-for-function (:fixnum-int "g2ext_get_name_for_function")
  ((:string-buffer buffer)
   (:fixnum-int addr)))

(def-side-effect-free-inlined-pseudo-function (inline-get-function-address :long) (fn)
  fn)

(defun-simple make-symbol-name-from-c-name (length buffer)
  (loop with string = (obtain-simple-gensym-string length)
        for i from 0 below length
        for buffer-char = (schar buffer i)
        for char = (if (char= buffer-char #\_)
                       #\-
                       (char-upcase buffer-char))
        do (setf (schar string i) char)
        finally (return string)))

(defun get-name-for-function (fn)
  (when (symbolp fn)
    (return-from get-name-for-function (gensym-symbol-name fn)))
  (make-symbol-name-from-c-name
    (c-get-name-for-function
      gensym-environment-variable-buffer
      (inline-get-function-address fn))
    gensym-environment-variable-buffer))




(def-gensym-c-function c-get-trace-function-name (:fixnum-int "g2ext_get_trace_function_name")
  ((:string buffer)))

(defvar-for-macro the-ab-package (find-package "AB"))

(def-global-property-name trace-function-p)
(defmacro declare-trace-function (name)
  `(setf (trace-function-p ',name) t))

(defvar running-trace-function-p nil)

(def-lisp-api-function (g2int-run-trace-function ;was g2int-run-trace-function - changed by SoftServe
                            (:name #-(or solaris translating)
                                   ;"_g2int_run_trace_function" ;commented by SoftServe
                                    "g2int_run_trace_function"
                                   #+(or solaris translating)
                                   "g2int_run_trace_function")
                            (:return-type :fixnum)) ()
  (let* ((length (c-get-trace-function-name gensym-environment-variable-buffer))
         (function-name
           (when (<= 0 length)
             (intern-gensym-string
               (make-symbol-name-from-c-name
                 length
                 gensym-environment-variable-buffer)))))
    (cond ((and (trace-function-p function-name) (fboundp function-name))
           (let ((running-trace-function-p t))
             (funcall function-name))
           1)
          (t
           0))))

;added by SoftServe in order to fix g2int_g2int problem
(setf (get 'g2int-run-trace-function 'gsi-api-symbol) t)
;end of SoftServe addition

(declare-gsi-api-symbol g2int-unix-command-callback)

(defvar unix-command-callback-function nil)

(def-lisp-api-function (g2int-unix-command-callback (:return-type :fixnum))
    ()
  (if unix-command-callback-function
      (funcall unix-command-callback-function)
      0))

;;; Load library containing all C primitive object modules.
;;; This is necessary because these primitive files are
;;; no longer kept on MA, but are kept on BOSTON.  The library
;;; is created separately from the Lucid compile of the Lisp
;;; sources. AC 7-30-91.  This has to be here because
;;; c-native-clock-ticks-per-second is referenced at load time.

;; jh, 8/19/93 per fmw.  The following form is intended to suppress redefinition
;; warnings that happen in the eternal recompile when the Lucid dynamic linker
;; access /lib/libc.a more than once.  Currently, the eternal recompile runs a
;; Lucid 4.0 worldsave containing the old (1.7) Chestnut translator.  I cannot
;; reproduce these warnings manually in this worldsave, nor can I reproduce them
;; in a Lucid 4.1 environment, so this change is in the way of an experiment.
;; According to the Lucid Advanced User's Guide, p 4-16,
;; lcl::unintern-foreign-symbol will prevent the redefinition from taking place.
;; Thus we might get a change in behavior when we do this, but it will be
;; limited to the macro pass of the old translator.  I have featured this to
;; happen only in the old translator because we might get lucky when we switch
;; to the new and in any event we should review this practice at that time.
;; According to the man for "ld.so" on the Sparc, the symbol __DYNAMIC should
;; not be defined by any program.  I believe that uninterning it as a foreign
;; symbol is OK.

#+(and (or lucid allegro) chestnut (not chestnut-trans))
(mapc #'lcl::unintern-foreign-symbol
      '(
        "_localtime"
        "_offtime"
        "_gmtime"
        "_tzset"
        "_tzsetwall"
        "__fp_rightshift"
        "__DYNAMIC"
        ))



#+(and development lucid)
(defun handle-warning-during-reload-foreign-libraries (condition)
  (declare (ignore condition))
  (setq lcl::*redefinition-action* nil)
  (format t "~&-- one warning is enough --~%")
  (let ((restart? (lcl::find-restart 'lcl::continue)))
    (when restart?
      (lcl::invoke-restart restart?))))

#+(and development lucid)
(defun reload-foreign-libraries ()
  (let ((lcl::*redefinition-action* :warn))
    (lcl::handler-bind
      ((lcl::warning #'handle-warning-during-reload-foreign-libraries))
      (load-foreign-libraries-for-ab-when-appropriate ab))))



;;; `load-libfnt' - moved here from FONTS.  Should be fixed up to not be
;;; so hard-coded.  - jv, 8/25/99

#+development
(defun load-libfnt ()
  (load-foreign-libraries
    (list (format nil "~alibfnt.a"
                  (local-fontrip-lib-directory current-system-being-loaded))
          "-lX11" "-lm" "-lc")))

;; (load-libfont) -- to reload the libfnt library, e.g., after changes to
;; fontrip.c.




;;;; Timeout Signal Handling



;;; C-cause_future_alarm_signal takes a single argument, a fixnum indicating the
;;; number of milliseconds that will elapse before G2 receives a SIGALRM signal.
;;; G2 will handle the SIGALRM signal by calling the no-argument void function
;;; service-sigalarm-signal.  C-cause_future_alarm_signal returns 0 if it
;;; succeeds in setting the alarm, and -1 if it fails.

;; jh, 4/26/93.  Currently, c-cause_future_alarm_signal only works on UNIX
;; platforms.

(def-gensym-c-function c-cause_future_alarm_signal
                       (:fixnum-int "g2ext_cause_future_alarm_signal")
  ((:fixnum-int milliseconds)))

;;; C-cancel_future_alarm_signal takes no arguments and cancels any timer that
;;; may be waiting to send this G2 process a SIGALRM signal.  This function
;;; returns 0 if it successfully cancels the SIGALRM signal, and -1 if it fails.

;; jh, 4/26/93.  Currently, c-cancel_future_alarm_signal only works on UNIX
;; platforms.

(def-gensym-c-function c-cancel_future_alarm_signal
                       (:fixnum-int "g2ext_cancel_future_alarm_signal")
  ())







;;;; Fixnum Time Primitives




;;; The macro get-fixnum-time, the constant fixnum-time-units-per-second, and
;;; the function fixnum-time-difference are used by the higher level modules
;;; (particularly in RUN, at present) as efficient means of comparing times
;;; accurately without reference to the real time of day.  Two results of
;;; get-fixnum-time can be validly compared if they are at most one day apart.
;;; The length of time between the times being compared is limited by the size
;;; of fixnums in a given application as well and perhaps also by limits within
;;; the implementation, but in no case can there be any problem comparing times
;;; that are less than 24 hours apart.

;;; The macro `get-fixnum-time' returns as a single value a non-negative fixnum that
;;; increases by 1 every 1/fixnum-time-units-per-second seconds and "wraps
;;; around" less than one time per day, with the wrap-around occuring at
;;; most-positive-fixnum.  In most Lisp implementations this will wrap around
;;; approximately once per week.  Called with no arguments, its accuracy may be
;;; limited to within 50 milliseconds.  When called with a non-null argument, it
;;; will return a value that is as accurate as can be had on the machine.

;;; Get-fixnum-time must be called inside of the system context, since in some
;;; implementations it depends on the temporary bignum areas being defined.  It
;;; does not need to be run as an atomic operation.  However, note that it can
;;; only be called from within the Lisp process for those machines which must use
;;; the with-temporary-bignum-creation form.  That means no interrupt level calls!
;;; This has been fixed on the Lisp machines by providing a global temporary bignum
;;; area.  -jra & MHD 10/7/88

;;; All the platform-and-build-specific conditionalization that used to be
;;; here has been moved inside c-native-clock-ticks-or-cache -alatto, 10/30/98

(defmacro get-fixnum-time (&optional as-accurately-as-possible? disable-caching-fixnum-time?)
  `(c-native-clock-ticks-or-cache ,as-accurately-as-possible? ,disable-caching-fixnum-time?))



;;; The global variable `cached-fixnum-time?' is used to hold a cached value for
;;; the current fixnum time.  This cache is cleared by a interrupt once every 50
;;; milliseconds or so.

(defvar cached-fixnum-time? nil)




;;; The function `fixnum-time-milliseconds-of-graininess' is used to control the
;;; length the interval during which we will hold a cached fixnum-time for reuse
;;; within multiple calls to get-fixnum-time.  If this value is 0, then the time
;;; will never be cached, the alarm will never be set, and the alarm will never
;;; be cleared.  This value should not vary within the lifetime of an
;;; executable.  The zero setting behavior is needed for GSI, since customers
;;; often use this alarm themselves and resent us cancelling their alarm signals
;;; (silly them).  Note that this is a function since current-system-case only
;;; works within already initialized processes.  -jra & ncc 3/22/95

(defmacro fixnum-time-milliseconds-of-graininess ()
  `(current-system-case
     (gsi 0)
     (t 50)))




;;; The simple function c-native-clock-ticks-or-cache is an internal to
;;; get-fixnum-time used to fetch fixnum times in translated code.  If there is
;;; a cached value to be had, and the caller has not requested an extremely
;;; accurate time, then the cache is used, which will not be more than 50
;;; milliseconds out of date.  If there is no cache available, or if a request
;;; has been made to make the results as accurate as possible, and always make
;;; the system call to get a new time.  If a new time is fetched, then it is
;;; placed into the cache and an attempt is made to set an alarm to clear it at
;;; 50 milliseconds from now.  If the attempt to set the alarm failed (some
;;; ports don't implement this alarm yet) then the cache is cleared.  In all
;;; cases, a fixnum time is returned.

;;; This can now be called even in development or other platforms that don't
;;; have the alarm facility. -alatto, 10/30/98

(defun-simple c-native-clock-ticks-or-cache (as-accurately-as-possible? 
                                             disable-caching-fixnum-time?)
  ;; GENSYMCID-1677: Problems with installing G2-2015 on Linux
  ;; Further disable some legacy code under Linux, as they stop G2 when building
  ;; layered products in Linux. -- Chun Tian (binghe), Mar 19, 2016.
  #-(and :unix (not :linux) :translator-is-loaded)
  (declare (ignore as-accurately-as-possible? disable-caching-fixnum-time?))
  #-(and :unix (not :linux) :vanilla-time) ; old: :unix
  (c-native-clock-ticks most-positive-fixnum)
  #+(and :unix (not :linux) :vanilla-time)
  (get-internal-real-time)
  ;; old: (and :unix (not :linux) (not :vanilla-time)), therefore it's disabled now, as
  ;; it sometimes causes G2 abort when building KBs.
  ;; -- Chun Tian (binghe), Feb 13, 2014.
  #+ignore
  (let ((local-cached-fixnum-time? cached-fixnum-time?))
    #-translator-is-loaded
    local-cached-fixnum-time? ;; to avoid unused warning.
    (cond
      #+translator-is-loaded
      ((and local-cached-fixnum-time? (not as-accurately-as-possible?))
       local-cached-fixnum-time?)
      (t
       (let ((new-time (c-native-clock-ticks most-positive-fixnum)))
	 #+translator-is-loaded
	 (when (and (/=f (fixnum-time-milliseconds-of-graininess) 0)
		    (not disable-caching-fixnum-time?))
	   (setq cached-fixnum-time? new-time)
	   (unless (=f (c-cause_future_alarm_signal
                        (fixnum-time-milliseconds-of-graininess))
                       0)               ; 0 means success
	     (setq cached-fixnum-time? nil)))
	 new-time)))))



;;; The function `clear-fixnum-time-alarm' is used to clear the fixnum time
;;; cache and cancel any pending alarms to clear it.  This function must be
;;; called before performing any sleep operations, since it believed that there
;;; is an interaction, at least on the UNIX platforms, between setitimer and
;;; select.  Note that when fixnum-time-milliseconds-of-graininess is 0, then
;;; cached-fixnum-time? will always be NIL, and so this function will not mess
;;; with the alarm.

(defun-void clear-fixnum-time-alarm ()
  (when cached-fixnum-time?
    (when (/=f (c-cancel_future_alarm_signal) 0)
      (format t "~%Failure reported when clearing sigalarm, continuing."))
    (setq cached-fixnum-time? nil)))



(defvar check-time-on-next-uuid #+development t #-development nil)
(defvar time-to-check-network-events #+development t #-development nil)

;;; The function service-sigalrm-signal is called when a sigalarm signal occurs.
;;; This is currently only used for fixnum time cache clearing.  Note that this
;;; function should do very little, but it cannot make any system calls
;;; (including mallocs) or we risk croaking UNIX.

;;; Note that unlike every other use of defun-simple and defun-void
;;; in G2, which are all for efficiency, this one is mandatory! The
;;; values-count is a global variable, and setting it here can screw
;;; up the values-count for whatever function happens to be executuing
;;; when the signal occurs. -alatto, 1/15/03

(defun-void g2int-service-sigalrm-signal ()
  (setq cached-fixnum-time? nil)
  (setq check-time-on-next-uuid t)
  (setq time-to-check-network-events t))

(declare-gsi-api-symbol g2int-service-sigalrm-signal)

(def-substitution-macro maybe-check-network-events ()
  (when time-to-check-network-events
    (or (g2-event-ready-p)
        #-development
        (setq time-to-check-network-events nil))))

(def-substitution-macro maybe-get-network-events ()
  (when (maybe-check-network-events)
    #-development
    (setq time-to-check-network-events nil)
    (get-pending-network-events)))



;;; The function `get-fixnum-time-function' is just a function version of the
;;; macro get-fixnum-time.  It is needed for initialization of some system
;;; variables.

(defun-simple get-fixnum-time-function ()
  (get-fixnum-time))





;;; The special variable `fixnum-time-units-per-second' is the number of clock
;;; ticks per second in the value of get-fixnum-time.  This number is
;;; implementation specific, and is based on, though not necessarily the same
;;; as, the internal-time-units-per-second of a Lisp implementation, or is based
;;; on the clock ticks per second of the subsecond clock functions.  In some
;;; cases (notably Lucid VMS) internal-time-units-per-second had to be drasticly
;;; reduced to insure that this get-fixnum-time would not wrap around more than
;;; once per day.  In all cases fixnum-time-units-per-second is greater than 60
;;; and less then 6213 (i.e. (floor most-positive-fixnum (* 24 60 60))), and is
;;; usually near 1000.

(defparameter fixnum-time-units-per-second
  #+(and :unix (not :linux) :vanilla-time)
  internal-time-units-per-second
  #-(and :unix (not :linux) :vanilla-time)
  (c-native-clock-ticks-per-second))




;;; The macro `fixnum-time-difference' can be called on two fixnums returned as
;;; the values of get-fixnum-time, and it will return a fixnum interval in
;;; fixnum-time-units-per-second that represents the amount of time that passed
;;; between the calls to get-fixnum-time.  This function gives subsecond
;;; accuracy for intervals up to a day long, but possibly will return a nonsense
;;; fixnum for longer times.

;;; Note that the ordering of combination of incremental results in the else
;;; clause of the IF is important.  They have been structured such that none of
;;; the intermediate results can overflow into bignums.

(defmacro fixnum-time-difference (later-fixnum-time earlier-fixnum-time)
  (if (and (symbolp later-fixnum-time)
           (symbolp earlier-fixnum-time))
      (let ((temp (gensym)))
        `(if (>=f ,later-fixnum-time ,earlier-fixnum-time)
             (-f ,later-fixnum-time ,earlier-fixnum-time)
             ;; Note that this computation and the one below have been split
             ;; into multiple lines to ensure that C compiler associativity
             ;; transformations will not change the ordering of these
             ;; operations.  See Harbison & Steele for sections on arithmetic
             ;; for appropriate warnings.  -jra 2/17/94
             (let ((,temp (-f ,later-fixnum-time ,earlier-fixnum-time)))
               (declare (type fixnum ,temp))
               (setq ,temp (+f ,temp most-positive-fixnum))
               (+f ,temp 1))))
      (let ((later (gensym))
            (earlier (gensym)))
        `(let ((,later ,later-fixnum-time)
               (,earlier ,earlier-fixnum-time))
           (declare (type fixnum ,later ,earlier))
           (cond ((>=f ,later ,earlier)
                  (-f ,later ,earlier))
                 (t
                  (setq ,later (-f ,later ,earlier))
                  (setq ,later (+f ,later most-positive-fixnum))
                  (+f ,later 1)))))))

#+unused
(declare-side-effect-free-function fixnum-time-difference-function)

#+unused
(defun-simple fixnum-time-difference-function (later-fixnum-time earlier-fixnum-time)
  (declare (eliminate-for-gsi))
  (declare (type fixnum later-fixnum-time earlier-fixnum-time))
  (fixnum-time-difference later-fixnum-time earlier-fixnum-time))




;;; The function `fixnum-time-sum' takes a fixnum time stamp as its first
;;; argument and a fixnum time interval as the second, adds the interval to the
;;; time stamp, and returns the new time stamp.  Note that the result may have
;;; wrapped around within fixnum time, but will be valid as long as the passed
;;; interval is not longer than 24 hours.  Do not use this function to add two
;;; fixnum time intervals; use +f instead.

;; To clarify the above, fixnum-time-stamp is a non-negative fixnum, and
;; fixnum-time-interval is a fixnum. The value must be a non-negative fixnum
;; which is congruent to the sum of the arguments mod most-positive-fixnum + 1.
;; The following code does not make use of bignums even temporarily.

#+unused
(declare-side-effect-free-function fixnum-time-sum)

#+unused
(defun-simple fixnum-time-sum (fixnum-time-stamp fixnum-time-interval)
  (let ((x fixnum-time-stamp)
        (y fixnum-time-interval)
        (r1 0))
    (declare (type fixnum x y r1))
    (cond ((minuspf y)
           (setq r1 (+f x y))
           (cond ((minuspf r1)
                  (setq r1 (+f r1 most-positive-fixnum))
                  (+f r1 1))
                 (t
                  r1)))
          (t
           (setq x (-f x most-positive-fixnum))
           (setq r1 (+f x y))
           (if (<=f r1 0)
               (+f r1 most-positive-fixnum)
               (-f r1 1))))))




;;; The function `fixnum-time-interval' takes a numeric millisecond argument and
;;; converts it into an interval expressed in fixnum-time-units-per-second.
;;; This function rounds up to the nearest interval to avoid clobbering any
;;; small intervals into 0 amount of time.  This form attempts to preform fixnum
;;; arithmetic if the millisecond count is low enough, otherwise this function
;;; enters a temporary bignum environment in case an intermediate result should
;;; rise above most-positive-fixnum.  The argument should not be more than 24
;;; hours worth of milliseconds.

(declare-side-effect-free-function fixnum-time-interval)

(defparameter fixnum-time-bignum-worries-limit
  (floorf-positive most-positive-fixnum fixnum-time-units-per-second))

(defun-simple fixnum-time-interval-protected (milliseconds)
  (current-system-case
    ((ab telewindows)
     (let (result-fixnum)
       (with-temporary-bignum-creation
         (setq result-fixnum
               (ceiling (* milliseconds fixnum-time-units-per-second) 1000)))
       result-fixnum))
    (gsi
      ;; The following message is analogous to the warning emitted by
      ;; SI_alloc_primitive_vector() in /bt/ab/rtl/c/heap.c about bignum
      ;; allocation outside a temporary context.
      (format t "Memory inconsistency (type 3, case 2) detected.")
      (let ((result-fixnum 0))
        (declare (type fixnum result-fixnum))
        (setq result-fixnum
              (ceilingf-positive
                (*f milliseconds fixnum-time-units-per-second)
                1000))
        result-fixnum))))

(defun-simple fixnum-time-interval (milliseconds)
  (let ((local-time-units-per-second fixnum-time-units-per-second))
    (declare (type fixnum local-time-units-per-second))
    (cond ((=f local-time-units-per-second 1000)
           milliseconds)
          ;; If milliseconds is small enough to not worry about bignums,
          ;; do it all in fixnum arithmetic.
          ((<f milliseconds fixnum-time-bignum-worries-limit)
           (ceilingf-positive (*f milliseconds local-time-units-per-second)
                              1000))
          (t
           (fixnum-time-interval-protected milliseconds)))))

;; jh, 4/8/92.  Added fixnum-time-interval-for-one-second because it no longer
;; suffices to call fixnum-time-interval at read time to get this number, as we
;; used to do in update-file-progress-display (KB-LOAD1) and in
;; search-items-a-little (QUERIES).  Readtime only happens on the Sparc now, and
;; so can produce erroneous code on other platforms, which have a different
;; fixnum-time-units-per-second.

(defvar fixnum-time-interval-for-one-second (fixnum-time-interval 1000))

;;; `Convert-fixnum-time-difference-to-seconds' ... returns
;;; fixnum-time-interval rounded to the nearest equivalent number of seconds
;;; expressed as a fixnum.

(defmacro convert-fixnum-time-difference-to-seconds (fixnum-time-interval)
  `(floorf-positive ,fixnum-time-interval fixnum-time-units-per-second))



;;; The macro `convert-seconds-to-fixnum-time-difference' converts a
;;; second to a fixnum-time-interval.  It assumes that the resulting value
;;; fits into a fixnum.

(defmacro convert-seconds-to-fixnum-time-difference (fixnum-seconds)
  `(*f ,fixnum-seconds fixnum-time-units-per-second))





;;; The function `fixnum-time-difference-in-seconds' returns the number of
;;; seconds between later-fixnum-time and earlier-fixnum-time. Obviously this
;;; will be unsuitable for intervals finer grained than one second.

(defun fixnum-time-difference-in-seconds (later-fixnum-time earlier-fixnum-time)
  (convert-fixnum-time-difference-to-seconds
    (fixnum-time-difference later-fixnum-time earlier-fixnum-time)))





;; This defvar for minimum-fixnum-interval-between-float-resets has been moved
;; here so that it follows the definition of fixnum-time-interval.  This
;; variable is used above in the temporary area section, which must precede the
;; use here in fixnum-time-interval.  -jra 8/8/89


#+development
(defparameter fixnum-time-units-per-second-as-a-float
              (* fixnum-time-units-per-second 1.0))

#+development
(defun test-fixnum-time (&optional (interval-to-sleep-in-seconds 1))
  (loop for previous-time = 0 then this-time
        for this-time = (get-fixnum-time)
        as first-time? = t then nil
        until (read-char-no-hang)
        do (gensym-sleep interval-to-sleep-in-seconds)
           (if first-time?
               (format t "~&Printing all 1.0's means a perfect score.  ~
                          Type any character to quit ... ")
               (format t "~a "
                       (/ (fixnum-time-difference this-time previous-time)
                          fixnum-time-units-per-second-as-a-float)))
           (force-output *standard-output*)))








#+development
(defun long-term-fixnum-time-test ()
  (loop with u-seconds and u-minutes and u-hours and
          f-seconds and f-minutes and f-hours and
          old-fixnum-time and new-fixnum-time and
          elapsed-time-in-seconds and remaining-micro-units = 0
        initially (multiple-value-setq (f-seconds f-minutes f-hours)
                    (get-decoded-time))
                  (setq old-fixnum-time (get-fixnum-time))
        until (read-char-no-hang)
        do
          (gensym-sleep 10)
          (setq new-fixnum-time (get-fixnum-time))
          (multiple-value-setq (elapsed-time-in-seconds remaining-micro-units)
            (floor (+ (fixnum-time-difference
                        new-fixnum-time old-fixnum-time)
                      remaining-micro-units)
                   fixnum-time-units-per-second))
          (setq old-fixnum-time new-fixnum-time)
          (multiple-value-bind (carry wrap-around)
              (floor (+ f-seconds elapsed-time-in-seconds) 60)
            (setq f-seconds wrap-around)
            (setq f-minutes (+ f-minutes carry)))
          (multiple-value-bind (carry wrap-around)
              (floor f-minutes 60)
            (setq f-minutes wrap-around)
            (setq f-hours (+ f-hours carry)))
          (multiple-value-setq (u-seconds u-minutes u-hours)
            (get-decoded-time))
          (format t "The long term creep is ~D seconds~%"
                  (+ (- f-seconds u-seconds)
                     (* 60 (- f-minutes u-minutes))
                     (* 3600 (- f-hours u-hours))))))







;;;; C Pointers


;;; The function `initialize-g2pointers' ...  This function has to be called
;;; before any C function which uses G2pointers is called.  In other words, it
;;; should be called pretty early.  This comment used to say that it had to be
;;; called before any other C function is called, but that's not really true.
;;; In fact, we call some C functions while loading!  We call wide-string-memcmp
;;; many times, and may call partition-float and reconstruct-float while loading
;;; as well.  We also call verify-operating-system before initialize-g2pointers
;;; when we run.  Those are all fine since they don't use G2 pointers or events.
;;; Most C functions do, and are not ready to run until initialize-g2pointers
;;; and ne-initialize-event-handling have been called.  -jv, 7/21/07

(def-gensym-c-function initialize-g2pointers (:void "g2ext_initialize_g2pointers")
  ())

; Added initialize-g2pointers for lucid in VMS for non-consing stream fix
; on that platform.  The shareable file SYS$LIBRARY:CSTREAMS.EXE must exist.
; See the file streams.lisp for details and the rest of the fix.  (jh, 2/15/90)

#+development
(def-gensym-c-function map-g2pointer-to-cpointer
                       (:fixnum-int "g2ext_map_g2pointer_to_cpointer")
   ((:fixnum-int g2pointer)))

;;; The purpose is to set locales to default (C) so that I/O functions on floats
;;; won't turn to use "strange" formats like in Italian or Franch.
;;; -- Chun Tian (binghe), Dec 2015

(def-gensym-c-function initialize-locales (:void "g2ext_initialize_locales")
  ())

#+development ; for some compile-time tests
(initialize-locales)

(def-gensym-c-function c-set-file-operation-timeout
                       (:fixnum-int "g2ext_set_file_operation_retry_timeout")
  ((:string timeout)))




;;;; Functions of CPRIMITIVES.C

;;; The function unix-command-output-as-string returns a text-string containing the
;;; output of a unix command, if successful, truncated to
;;; maximum-gensym-environment-variable-length characters (1023 as of 6/10/99).
;;; If unsuccessful, it returns nil.

(def-gensym-c-function c-unix_command_with_string_output
                       (:fixnum-int "g2ext_unix_cmd_with_string_output_mx")
  ((:string command)
   (:string buff)
   (:fixnum-int max-bytes)))

(defun unix-command-output-as-string (command-string)
  (declare (eliminate-for-gsi))
  (let ((result-code
          (c-unix_command_with_string_output
            command-string
            gensym-environment-variable-buffer
            maximum-gensym-environment-variable-length)))
    (interface-to-foreign-environment-access result-code)))

(def-gensym-c-function c-unix_command_with_string_output_and_timeout
                       (:fixnum-int "g2ext_unix_cmd_with_string_output_and_timeout_mx")
  ((:string command)
   (:string dir)
   (:string buff)
   (:fixnum-int timeout-in-ms)
   (:fixnum-int max-bytes)))

(defun unix-command-output-as-string-with-timeout-callback
    (command-string directory initial-timeout? callback?)
  (declare (eliminate-for-gsi))
  (let* ((unix-command-callback-function callback?)
         (result-code
           (c-unix_command_with_string_output_and_timeout
             command-string
             directory
             gensym-environment-variable-buffer
             (or initial-timeout? most-positive-fixnum)
             maximum-gensym-environment-variable-length)))
    (interface-to-foreign-environment-access result-code)))

(def-gensym-c-function c-run_program_with_string_output_and_timeout
                       (:fixnum-int "g2ext_run_program_with_string_output_and_timeout_mx")
  ((:string command)
   (:string dir)
   (:string buff)
   (:fixnum-int timeout-in-ms)
   (:fixnum-int max-bytes)))


(def-gensym-c-function c-directory_contains_directory
                       (:fixnum-int "g2ext_directory_contains_directory")
  ((:string containing-directory)
   (:string contained-directory)))

(def-substitution-macro directory-contains-directory-p (containing-directory contained-directory)
  (not (=f 0 (c-directory_contains_directory containing-directory contained-directory))))



(def-gensym-c-function c-write-string-to-console
                       (:fixnum-int "g2ext_write_string_to_console_1")
  ((:string string)
   (:fixnum-int write-console-p)))

;;; function nsleep moved to sequences1.lisp -ncc, 3/29/94

;;; `Nsleep-result-ok-p' takes the value returned by nsleep and returns
;;; non-nil if nsleep managed to get the machine id, and nil if not.

(def-substitution-macro nsleep-result-ok-p (result?)
  (or result? t))


(def-gensym-c-function c-pause
                       (:void "g2ext_gensym_pause")
  ((:fixnum-int timeout-in-milliseconds-when-interruptable)
   (:fixnum-int timeout-in-milliseconds-when-polling)))




(def-gensym-c-function c-uninterruptible-sleep
                       (:fixnum-int "g2ext_sys_sleep")
  ((:fixnum-int time-in-milliseconds)))


(def-gensym-c-function c-max-ready
                       (:void "g2ext_max_ready")
  ())


;;; `verify-operating-system'

(def-gensym-c-function verify-operating-system (:void "g2ext_verify_operating_system")
  ((:fixnum-int exit-on-os-conflict-p)))







;;;; Rings



;;; Def-ring defines queuing operations implemented using named rings of linked
;;; "elements".  The operations are:
;;;
;;;    (OBTAIN-name [structure-holding-queue]),
;;;
;;;    (ENQUEUE-name [structure-holding-queue]),
;;;
;;;    (DEQUEUE-name-IF-ANY [structure-holding-queue]), and
;;;
;;;    (PEEK-AT-name-IF-ANY [structure-holding-queue]), and
;;;
;;;    (REQUEUE-name [structure-holding-queue]).

;;; To enqueue, call OBTAIN-name, fill in the element so obtained, and then call
;;; ENQUEUE-name.  It is okay to abort this sequence of actions at any point.  Note
;;; that ENQUEUE-name must not be called without first calling OBTAIN-name.

;;; To dequeue, call DEQUEUE-name-IF-ANY, and if it returns an element (non-nil),
;;; extract the useful information.  Note that all information must be extracted from
;;; a dequeued element before an attempt is made to dequeue the next element.  To
;;; requeue the last dequeued element, call REQUEUE-name, and that element will be
;;; returned by the next call to DEQUEUE-name-IF-ANY.  To peek at the next available
;;; element without dequeueing it, call PEEK-AT-name-IF-ANY, which does not destroy
;;; information in the previously dequeued element.

;;; Available-elements-maker takes no arguments and returns one or more unfilled-in
;;; elements, suitably linked via element-link-accessor links, with nil at the end.
;;; Thus it may make a "batch" of new elements at a time.  Note that element-link-accessor
;;; must be applicable to every element.

;;; If the ring is to be kept in system variables, the optional accessors should not be
;;; specified.  If they are to be kept in structures, on the other hand, all three
;;; accessors (for the head and tail of the queue and requeue flag) must be specified.
;;; In this latter case, the operations defined by def-ring takes an additional structure-
;;; holding-queue final argument, to which the accessors are applied.  (This structure
;;; case may be helpful in ICP, for example, where a queue of listed ICP buffers may have
;;; to be kept in each ICP port.)

;;; The def-ring facility is especially valuable for communication between two asynchronous
;;; processes or between a main process and its (atomic) interrupt handlers.  As long
;;; as a particular queue is used only by the pair of processes (or the main process and
;;; its interrupt handlers) in such a way that one side exclusively enqueues and the other
;;; exclusively dequeues, the enqueuing and dequeuing can be safely done without locks.

;;; A new argument, added 6 April 1988, provide-obtainer-unable-to-extend-ring?, if true,
;;; causes version of the obtainer macro to be defined which returns nil if there are
;;; no available elements (i.e. if the available elements maker would have to be called
;;; in this situation if using the normal obtainer).  Then a form like
;;;   (OBTAIN-name-IF-AVAILABLE [structure-holding-queue])
;;; will return either an available element to be filled in or nil.  When enqueueing items
;;; at interrupt level on most machines, it is a bad idea to allocate storage.  This makes
;;; it impossible for that to happen. When this obtainer used, the queue must be initialized
;;; with all of its elements when it is created (otherwise you never obtain a new element
;;; using this obtainer.  In the case where the ring is to be kept in a system variable,
;;; this initialization is performed automatically.  In the case of structures, a form like
;;; the following should be executed upon creation of the queue: (EXTEND-name-QUEUE
;;; structure-holding-queue). EXTEND-name-QUEUE is a macro defined by def-ring.


(defmacro def-ring
          (name module-name
           available-elements-maker element-link-accessor
           &optional
           accessor-for-head-of-queue? accessor-for-tail-of-queue?
           accessor-for-requeue-flag?
           (provide-obtainer-unable-to-extend-ring? nil))

  (let* ((obtainer (format-symbol "OBTAIN-~A" name))
         (obtainer-unable-to-extend-ring
           (if provide-obtainer-unable-to-extend-ring?
               (format-symbol "OBTAIN-~A-IF-AVAILABLE" name)))
         (enqueuer (format-symbol "ENQUEUE-~A" name))
         (dequeuer (format-symbol "DEQUEUE-~A-IF-ANY" name))
         (peeker (format-symbol "PEEK-AT-~A-IF-ANY" name))
         (requeuer (format-symbol "REQUEUE-~A" name))
         (structure-holds-queue? accessor-for-head-of-queue?)        ; verify all or none!
         (place-for-head-of-queue
           (if structure-holds-queue?
               `(,accessor-for-head-of-queue? structure-holding-queue)
               (format-symbol "HEAD-OF-~A-QUEUE" name)))
         (place-for-tail-of-queue
           (if structure-holds-queue?
               `(,accessor-for-tail-of-queue? structure-holding-queue)
               (format-symbol "TAIL-OF-~A-QUEUE" name)))
         (place-for-requeue-flag
           (if structure-holds-queue?
               `(,accessor-for-requeue-flag? structure-holding-queue)
               (format-symbol "REQUEUE-FLAG-FOR-~A-QUEUE" name)))
         (extra-args
           (if structure-holds-queue? '(structure-holding-queue)))
         (initializer (format-symbol "INITIALIZE-~A-QUEUE" name))
         (extender (format-symbol "EXTEND-~A-QUEUE" name)))

    `(progn

     ,@(if (not structure-holds-queue?)
           `((def-system-variable ,place-for-head-of-queue ,module-name nil)
             (def-system-variable ,place-for-tail-of-queue ,module-name nil)
             (def-system-variable ,place-for-requeue-flag ,module-name
               (:funcall ,initializer))
             (defun ,initializer ()
               (,extender)
               nil)))

     ,(if (not structure-holds-queue?)
          `(defmacro ,obtainer ()
             `(let ((,',name (,',element-link-accessor ,',place-for-tail-of-queue)))
                (if (eq ,',name ,',place-for-head-of-queue)
                    (,',extender)
                    ,',name)))
          `(defmacro ,obtainer ,extra-args        ; could adapt this for both cases!
             `(let* ((structure-holding-queue ,structure-holding-queue)
                     (tail-of-queue ,',place-for-tail-of-queue)
                     (,',name
                      (if tail-of-queue (,',element-link-accessor tail-of-queue))))
                (if (eq ,',name ,',place-for-head-of-queue)
                    (,',extender . ,',extra-args)
                    ,',name))))

     ,@(if provide-obtainer-unable-to-extend-ring?
           `(,(if (not structure-holds-queue?)
                  `(defmacro ,obtainer-unable-to-extend-ring ()
                     `(let ((,',name (,',element-link-accessor ,',place-for-tail-of-queue)))
                        (if (eq ,',name ,',place-for-head-of-queue)
                            nil
                            ,',name)))
                  `(defmacro ,obtainer-unable-to-extend-ring ,extra-args
                                                ; could adapt this for both cases!
                     `(let* ((structure-holding-queue ,structure-holding-queue)
                             (tail-of-queue ,',place-for-tail-of-queue)
                             (,',name
                              (if tail-of-queue (,',element-link-accessor tail-of-queue))))
                        (if (eq ,',name ,',place-for-head-of-queue)
                            (progn (progn . ,',extra-args) nil)
                                                ; arg not used (could be eliminated!)
                            ,',name))))))

     (def-substitution-macro ,enqueuer ,extra-args
       (setf ,place-for-tail-of-queue
             (,element-link-accessor ,place-for-tail-of-queue)))

;;    (ENQUEUING-name [structure-holding-queue] {form-to-fill-in-next-element})
;; ENQUEUING-name is a unified enqueuer.  The body of this environment macro fills
;; in the element to be enqueued, referring to it by the name of the queue used as
;; a variable.
;         (enqueuing (format-symbol "ENQUEUING-~A" name))
;     (defmacro ,enqueuing (,@extra-args &body body-to-fill-in-next-element)
;       `(let ((,',name (,',obtainer . ,',extra-args)))
;          (progn . ,body-to-fill-in-next-element)
;          (,',enqueuer . ,',extra-args)))

     (def-substitution-macro ,dequeuer ,extra-args
       (let ((head-of-queue ,place-for-head-of-queue))
         (cond
           (,place-for-requeue-flag
            (setf ,place-for-requeue-flag nil)
            head-of-queue)
           ((and (not (eq head-of-queue ,place-for-tail-of-queue))
                 ,@(if structure-holds-queue? '(head-of-queue)))        ; see above
            (setf ,place-for-head-of-queue
                  (,element-link-accessor head-of-queue))))))

     (def-substitution-macro ,peeker ,extra-args
       (let ((head-of-queue ,place-for-head-of-queue))
         (cond
           (,place-for-requeue-flag
            head-of-queue)
           ((and (not (eq head-of-queue ,place-for-tail-of-queue))
                 ,@(if structure-holds-queue? '(head-of-queue)))        ; see above
            (,element-link-accessor head-of-queue)))))

     (def-substitution-macro ,requeuer ,extra-args        ; should be a defmacro!
       (setf ,place-for-requeue-flag t))

     (defun ,extender ,extra-args
       (loop with available-elements-for-queue = (,available-elements-maker)
             as l = (if (or (cdr available-elements-for-queue)
                            ,place-for-tail-of-queue)
                        available-elements-for-queue
                        (nconc available-elements-for-queue        ; must initialize to at
                               (,available-elements-maker)))        ;   least two elements
                  then (,element-link-accessor l)
             until (null (,element-link-accessor l))
             finally
               (setf (,element-link-accessor l)
                     (if ,place-for-tail-of-queue
                         (,element-link-accessor ,place-for-tail-of-queue)
                         available-elements-for-queue))
               (if ,place-for-tail-of-queue
                   (setf (,element-link-accessor ,place-for-tail-of-queue)
                         available-elements-for-queue)
                   (setf ,place-for-head-of-queue
                         (setf ,place-for-tail-of-queue
                               available-elements-for-queue)))
               (return (,element-link-accessor ,place-for-tail-of-queue))))

     ',name)))

;; Note that, after initialization, only enqueuers change tail variables and only
;; dequeuers change head variables.  This is essential if enqueueing and dequeuing are
;; to work properly between asynchronous processes without locking.

;; Consider making the requeuing capability optional.

;; Consider initializing queues kept in structures in advance, rather than on the first
;; enqueue.  Alternatively, consider not initializing, in advance, queues kept in system
;; variables.

(defmacro dolist-safely ((variable list &optional value) &body body)
  (let ((list-var (make-symbol "LIST"))
        (next-list-var (make-symbol "NEXT-LIST")))
    `(loop for ,list-var = ,list then ,next-list-var
           for ,variable = (car ,list-var)
           for ,next-list-var = (cdr ,list-var)
           while ,list-var
           do
       ,@body
           finally (return ,value))))









;;;; Primitive Bindings

;;; Catch-system-conditions causes body to be restarted even when an error or
;;; abort condition occurs.  Implementations should allow an interactive
;;; debugging session to be used until the user aborts to end the session.  Body
;;; then should be reexecuted.  If body completes without being aborted due to
;;; an error, the values of evaluating body are returned. Catch-system-conditions
;;; is intended to be used around an interactive command loop at a fairly high
;;; level.  (See run-system-process.)

(defmacro catch-system-conditions (&body body)
  ;; currently, this does not stop M-Aborts.  Deal with this!!!
  `(progn . ,body))



;;; With-break-bindings should be used within with-primitive-bindings (see above) to put
;;; back certain things in the environment the way they were before. (Think of it as
;;; a "break" from the rarified atmosphere of the application for the way things are in
;;; the "outside world" of the host environment.)  With-break-bindings must be called
;;; within a with-primitive-bindings form and should be called at the highest level around
;;; the lisp break loop.  (See Run-Break-Loop in the Run module.)

(defmacro with-break-bindings (&body body)        ;for running (AB's own) break loop
  `(progn . ,body))


;;; With-primitive-bindings runs body with the "right things" from the host
;;; operating system enabled and the "wrong things" disabled.  Two examples are:
;;; giving the application control of the special function keys (e.g. Abort), as
;;; opposed to leaving this up to the operating system; and disabling the lisp
;;; error handler from rebinding the *package* variable to some package other
;;; than AB.  The changes to be included here are intended to be ones that
;;; enable or disable a global feature of the host environment for this
;;; application.  The goal is a change "for the better" in the local context of
;;; this application and no change whatsoever in the global environment.
;;; With-primitive-bindings should be called at the highest level around the
;;; main top-level loop.  (See run-system-process.)

;;; With-primitive-bindings may also be used to bind special variables in higher
;;; level code but before the binding of the system variables (see System Variables
;;; subsection).

;; jh, 12/12/91.  Moved with-standard-error-restart-loop to the new module
;; OS-ERROR, which collects in one place all the machinery for handling internal
;; errors.

;;; The macro `with-protected-streams' ...

(defmacro with-protected-streams (&body body)
  `(let*-or-set-for-system ((g2-stream-all-open-streams nil))
     (unwind-protect
         (progn . ,body)
       (let ((copy-of-g2-stream-all-open-streams
               (copy-list-using-streams-conses-function
                 g2-stream-all-open-streams)))
         (loop for stream? in copy-of-g2-stream-all-open-streams
               when stream?
                 do (g2-stream-close stream?))
         (reclaim-streams-list-function copy-of-g2-stream-all-open-streams)))))



;; Changed with-protected-streams to map down a copy of g2-stream-all-open-streams,
;; instead of the real thing.  This prevents unplanned side effects, since
;; g2-streams-close mutates g2-stream-all-open-streams.  (jh, 7/10/90)



;;; The macro `with-protected-listeners' closes down all open listeners G2 was using.

;; jh, 8/13/91.  Both UNIX and VMS have problems closing down network sockets on
;; exit.  In UNIX, when a parent spawns G2 and then is killed before it can
;; explicitly kill G2, G2's sockets are bequeathed to the UNIX init process, and
;; thus seem to persist even though the G2 is incommunicado.  In VMS, the STOP
;; command can bypass all shutdown handling, including mailbox (a.k.a. socket)
;; shutdown.  With-protected-listeners currently only closes down the listener
;; used by the per-process checker, but for these reasons we should consider
;; closing any ICP socket which managed to remain open.

;; jh, 9/3/91.  Added shutdown of foreign image connections to
;; with-protected-listeners.  If this is not done, the sockets for these images
;; will persist after G2 exits, at least in UNIX and possibly elsewhere.  A
;; symptom of this seems to be that the G2 window will not vanish after a
;; shutdown.

;; jh, 10/23/92.  Added the ability to kill processes spawned by the
;; g2-spawn-process-to-run-command-line system procedure which the end-user may
;; have neglected to kill with the g2-kill-process system procedure.  (These
;; procedures are implemented in the FILE-IO module).

;; paf!, ncc 2/10/94 Moved cleanup code in with-protected-listeners into new function
;; shutdown-system-for-exit, which is called from with-protected-listeners only if
;; current system is *not* GSI.  GSI will call shutdown-system-for-exit explicitly
;; as required.

(def-system-variable known-process-ids? PRIMITIVES nil)

(def-system-variable all-foreign-function-images? PRIMITIVES nil)
(def-system-variable all-external-foreign-function-images? PRIMITIVES nil)

(defmacro with-protected-listeners (&body body)
  `(unwind-protect (progn ,@body)
     (current-system-case
       (gsi) ; entering one cycle mode
       (t (shutdown-system-for-exit)))))

(defun-void kill-foreign-images (list-of-foreign-images?)
  (when list-of-foreign-images?
    (let ((copy-of-list-of-foreign-images
            (copy-list-using-icp-conses-function list-of-foreign-images?)))
      (loop for foreign-image-info in copy-of-list-of-foreign-images
            do
        (kill-foreign-image-unconditionally foreign-image-info)
            finally
              (reclaim-icp-list-function copy-of-list-of-foreign-images)))))

(defun-simple shutdown-system-for-exit ()
  (with-temporary-gensym-float-creation with-protected-listeners
    (kill-foreign-images all-foreign-function-images?)
    (kill-foreign-images all-external-foreign-function-images?)
    (when known-process-ids?
      (loop for process-id in known-process-ids?
            do (kill-possibly-leftover-spawned-process process-id)
            finally (reclaim-sysproc-list-function known-process-ids?))))
  (shift-rule-ordering-heuristics) ; license-close-listener
  (close-and-disconnect-all-sockets)
  (current-system-case
    ((ab telewindows)
     (close-native-window))))



;;; The macro `with-primitive-bindings' ...

(defmacro with-primitive-bindings ((system) &body body)
  `(with-standard-error-restart-loop
     (with-managed-objects (,system)
       #+lucid
       ,@(if (not (eval-feature :translator))
             (if (eval-feature :solaris)
                 nil
                 `((setq lcl::*scheduling-quantum* 1)))
             nil)
       ,@body)))


;; Changed with-primitive bindings to take an additional sublist, as
;; (with-primitive-bindings (<system>) ...) The form <system> should evaluate to a
;; system name, a symbol like 'g2 or 'telewindows.  The sublist is passed to the
;; with-managed-objects macro, whose syntax has also been changed.  This change is
;; necessary in order to insure that memory limits can be tuned to a specific
;; system, though the limits are currently the same for all systems.  (jh, 8/2/90)

;; Removed the with-protected-streams scope from with-primitive-bindings.  This
;; scope more properly belongs inside the with-system-variables scope in
;; run-system-process from PLATFORMS.  This is because text-strings and managed
;; structures are reclaimed upon exit from the with-protected-streams scope, and
;; this requires system variables.  jh, 1/24/91.

;; jh, 12/12/91.  Moved all the error handling machinery that was here to the new
;; module OS-ERROR, which collects all this machinery in one place.

;; Removed a slew of with... forms and the binding of the now-gone in-color?
;; variable all of whose raisons d'etre were tied solely to LISP machines.


;;;; Scales



;;; A `scale' is a multiplicative conversion factor between an x or y
;;; displacement (`delta') in a workspace (or in a graphic object description)
;;; and the corresponding displacement (delta) in some particular image of that
;;; workspace (or of some workspace).  A scale is typically associated with an
;;; "image plane" (see module PANES).  Note that scale increases with increasing
;;; image size.  Note also that scaling, as typically implemented, requires, in
;;; addition to multiplying a scale times a delta, dividing by a "normalized
;;; scale"; see below.

;;; A scale is a positive number that should, except transiently, be within the
;;; limits determined by the minimum-scale and maximum-scale window parameters.
;;; These are bound in make-window-parameters-plist.

;;; Avoiding fixnum overflow is achieved by a careful contract between the
;;; range of values passed to the scaling operators, and the range of
;;; legal scales.  See `workspace-coordinate' for a discussion of who gets
;;; how many bits.

;;; A `default scale' is a scale used by default for a new image plane.
;;; See also `workspace-coordinate.'

(def-concept scale)
(def-concept minimum-scale)
(def-concept maximum-scale)

;; Nobody has yet worried about nested scaling but it's not implemented
;; either.



;;; The `normalized scale' is the scale at which one workspace unit = one raster
;;; unit (i.e., one pixel).  The normalized scale should be a power of two, so
;;; that the most common scaling operations, delta-x-in-window and
;;; delta-y-in-window, can be done without a division operation.

;;; `Normalized-scale' is a macro of no arguments, rather than a special
;;; variable, to emphasize that it is an implementation constant.  Typical uses
;;; in code are #.(normalized-scale), or #.(round (normalized-scale) 4) for
;;; one-quarter normalized scale.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro normalized-scale () #.(expt 2 12))

#+development
(unless (/= (integer-length (normalized-scale))
            (integer-length (- (normalized-scale) 1)))
  (warn "Oh my GOD.  normalized-scale is not power of two!"))
)

;; Consider defining convert-to-scale, a la convert-to-magnification below.


(defconstant isqrt-of-most-positive-fixnum (isqrt most-positive-fixnum))
(defconstant minus-of-isqrt-of-most-positive-fixnum
  (-f isqrt-of-most-positive-fixnum))

(defmacro squareable-fixnum-p (fixnum)
  `(<f minus-of-isqrt-of-most-positive-fixnum
       ,fixnum
       isqrt-of-most-positive-fixnum))

;;; `Scalef' quickly computes:
;;;      (round (* fixnum scale) (normalized-scale))

(defun-substitution-macro scalef (scale value)
  (cond ((=f scale (normalized-scale))
         value)
        ((and (squareable-fixnum-p scale)
              (squareable-fixnum-p value))
         (let ((unshifted-result                ; Chestnut workaround, see below.
                 (+f (*f scale value)
                     #.(floor (normalized-scale) 2))))
           (declare (type fixnum unshifted-result))
           (ashf unshifted-result
                 #.(- (integer-length (- (normalized-scale) 1))))))
        (t
         (scalef-function scale value))))

;; Note for Chestnut workaround: There is an obscure translation bug exposed by
;; this macro that we are trying to work around.  When this form was used as an
;; argument to values, the multiple-values count was being corrupted by a call
;; to ltimes for the multiply in the unshifted-result expression.  I'm guessing
;; that the multiply was not being inlined as it should, and some part of that
;; problem caused the values count to be corrupted.  -jra & rdf 1/20/94

;; The largest scale is 262144, which is 4x for workspaces and 16x for icons on
;; the workspace.


;;; The simple function `scalef-function' handles the overflow case,
;;; where the intermediate product is larger than a fixnum.

(defun-simple scalef-function (scale value)
  (declare (no-op-for-gsi))
  (rounde-first (*e (coerce-fixnum-to-gensym-float scale)
                    (coerce-fixnum-to-gensym-float value))
                (coerce-fixnum-to-gensym-float (normalized-scale))))

;; A custom C function could be much faster here.  We could avoid
;; consing the temporary boxed floats.



;;; The macro `inverse-scalef' quickly computes
;;;   (round (*f fixnum (normalized-scale)) scale)

(defun-substitution-macro inverse-scalef (scale value)
  (cond ((=f scale (normalized-scale))
         value)

        ((not (squareable-fixnum-p value))                    ; Really can-multiply-by-4096-p
         (inverse-scalef-function scale value))

        ((>=f value 0)
         (values
           (floorf-positive
             (+f (ashf value #.(integer-length (- (normalized-scale) 1)))
                 (ashf scale -1))
             scale)))
        (t
         (values
           (-f (floorf-positive
                 (+f (ashf (-f value) #.(integer-length (- (normalized-scale) 1)))
                     (ashf scale -1))
                 scale))))))

;; The bummed code above sometimes differs by one from the formula, due to the
;; fancy behavior of CL round, namely that it breaks ties by rounding to the
;; even integer: (round 0.5) = 0, (round 1.5) = 2.  I don't think we care
;; enough about the result to include that refinement here. The code as it
;; stands always rounds up, which is probably better for our purposes (eg,
;; region computations). -fmw, 1/26/95


;;; The simple function `inverse-scalef-function' handles the overflow case,
;;; where the intermediate product may exceed the size of a fixnum.

(defun-simple inverse-scalef-function (scale value)
  (declare (no-op-for-gsi))
  (rounde-first (*e (coerce-fixnum-to-gensym-float value)
                    (coerce-fixnum-to-gensym-float (normalized-scale)))
                (coerce-fixnum-to-gensym-float scale)))





;;; `Delta-x-in-window' converts an x displacement in a workspace,
;;; delta-x-in-workspace, into the nearest-integer x displacement in an image of
;;; the workspace, where x-scale is the conversion factor.  Delta-y-in-window is
;;; similar for the y dimension.  These macros are designed to be as fast as
;;; possible.

(defmacro delta-x-in-window (delta-x-in-workspace x-scale)
  `(scalef ,x-scale ,delta-x-in-workspace))

(defmacro delta-y-in-window (delta-y-in-workspace y-scale)
  `(scalef ,y-scale ,delta-y-in-workspace))



;;; The simple function `float-delta-x-in-window' returns the floating point
;;; scaled value.

(defun-simple float-delta-x-in-window (delta-x-in-workspace x-scale)
 (/e (*e (coerce-fixnum-to-gensym-float x-scale)
         (coerce-fixnum-to-gensym-float delta-x-in-workspace))
     (coerce-fixnum-to-gensym-float (normalized-scale))))


(defun-simple float-delta-y-in-window (delta-y-in-workspace y-scale)
 (/e (*e (coerce-fixnum-to-gensym-float y-scale)
         (coerce-fixnum-to-gensym-float delta-y-in-workspace))
     (coerce-fixnum-to-gensym-float (normalized-scale))))



;;; `Delta-x-in-workspace' converts an x displacement in an image of a
;;; workspace, delta-x-in-window, into the nearest-integer x displacement in
;;; the workspace, where x-scale is the conversion factor.
;;; `Delta-y-in-workspace' is similar for the y dimension.

;;; These macros are also designed for maximal speed, even though they are used
;;; much less frequently than the macros that convert in the other direction.
;;; In fact, they have just two primary uses: (1) mapping a cursor position to
;;; workspace coordinates and (2) loosely determining where the edges of a pane
;;; fall in a workspace, to allow "quick clipping" while drawing elements of
;;; the workspace.  Note that delta-x-in-workspace and delta-x-in-window cannot
;;; be exact inverses of one another, for a given scale, because of roundoff
;;; error.  (The roundoff error increases, on the average, as the scale get
;;; farther from the normalized scale.)

(defmacro delta-x-in-workspace (delta-x-in-window x-scale)
  `(inverse-scalef ,x-scale ,delta-x-in-window))

(defmacro delta-y-in-workspace (delta-y-in-window y-scale)
  `(inverse-scalef ,y-scale ,delta-y-in-window))




;;; `Scale-scale' scales scale by (numerator / denominator).  All three
;;; arguments and the result are assumed to be fixnums.

(defun scale-scale (scale numerator denominator)
  (declare (eliminate-for-gsi))
  (rounde-first (/e (*e (coerce-fixnum-to-gensym-float scale)
                        (coerce-fixnum-to-gensym-float numerator))
                    (coerce-fixnum-to-gensym-float denominator))))

;; Moved here from PANES. (MHD 6/18/93)


;; Chestnut ROUND is very slow.  ROUNDF is unfortunately the same function.



;;;; Magnifications



;;; A `magnification' is a multiplicative scaling factor to be applied to an x
;;; or y displacement (`delta') in workspace, window, scale, or text-x-component
;;; units.  A magnification is like a scale, but is typically associated with
;;; something to be drawn on an image plane, rather than with the image plane
;;; itself.

;;; A magnification is a positive number.  At present, a magnification must be a
;;; fixnum fixed-point number with 8 fraction bits that should, except
;;; transiently, be between (expt 2 4) = 16 and (expt 2 12) = 4096, which
;;; represent magnification of 1/16 and 16 respectively.  (The constants
;;; `least-magnification' and `greatest-magnification' are bound to these
;;; respective values.) This permits magnify to use fixnum arithmetic in
;;; implementations of Common Lisp that have at least 25-bit fixnums, assuming
;;; that all displacements being magnified are fixnums less than (expt 2 12) =
;;; 4096.

(def-concept magnification)

;; WORRY ABOUT OVERFLOW IN MAGNIFICATION OPERATIONS!


(defconstant least-magnification #.(expt 2 4))
(defconstant greatest-magnification #.(expt 2 12))



;;; `Convert-to-magnification' converts factor to a magnification.  If factor is
;;; less than 1/16, 1/16 is used instead.  If factor is greater than 16, 16 is
;;; used instead.  `Convert-ratio-to-magnification' does the same after deriving
;;; factor from numerator/denominator.
;;;
;;; Both of these functions enter and exit a temporary (gensym float creation)
;;; context.
;;;
;;; `Convert-to-magnification-at-compile-time' is expected to be used primarily
;;; at compile time.  Hence, it does not enter such a temporary context.
;;;
;;; `Convert-magnification-to-factor' converts magnification to a factor in the
;;; form of a gensym float.  This should generally be called in a temporary area
;;; context in order to avoid leaks.

(defun convert-to-magnification (factor)
  (declare (eliminate-for-gsi))
  (with-temporary-gensym-float-creation convert-to-magnification
    (min (max (round (* factor 256)) least-magnification)
         greatest-magnification)))

(def-substitution-macro convert-ratio-to-magnification (numerator denominator)
  ;; (declare (eliminate-for-gsi)) not for macros, only for functions
  (with-temporary-gensym-float-creation convert-ratio-to-magnification
    (convert-to-magnification
      (/e (coerce-to-gensym-float numerator)
          (coerce-to-gensym-float denominator)))))


(defun convert-to-magnification-at-compile-time (factor)
  (declare (eliminate-for-gsi))
  (min (max (round (* factor 256)) least-magnification) greatest-magnification))


(defun convert-magnification-to-factor (magnification)
  (declare (eliminate-for-gsi))
  (/e (coerce-to-gensym-float magnification) 256.0))



;;; Magnify magnifies delta (a displacement in workspace, window, scale, or
;;; text-x- component units) by magnification.

(defmacro magnify (delta magnification)
  `(ashf (+f (*f ,delta ,magnification) 128) -8))

(defmacro magnify-as-float (delta magnification)
  `(allocate-managed-float
     (/e (coerce-to-gensym-float (*f ,delta ,magnification)) 256.0)))

(def-substitution-macro magnify-as-number (delta magnification)
  (if (=f 0 (logandf 255 magnification))
      (magnify delta magnification)
      (magnify-as-float delta magnification)))



;;; Inverse-magnify divides delta-in-workspace by magnification.  See uses in
;;; modules PANES and EDIT.

(defun-simple inverse-magnify (delta-in-workspace magnification)
  (declare (eliminate-for-gsi))
  (with-temporary-gensym-float-creation inverse-magnify
    (values                                ; just return 1 value
      (round (/ (ashf delta-in-workspace 8)
                (coerce-to-gensym-float magnification))))))

;; Consider defining this as a macro.






;;;; Text Xs and Text Widths



;;; A `text x' is a two-variable (text-x-a and text-x-b) representation of a
;;; text line width or position, an "x", in workspace or window units or
;;; coordinates, that includes an appropriate number of fraction bits to avoid
;;; excessive roundoff error.

;;; A `text width' is an increment to a text x.  It is represented as a
;;; fixed-point number with 8 fraction bits, which can be assumed to be a
;;; fixnum.  This representation cannot be changed without converting KBs.
;;; Arithmetic operations on text widths should be done using the fixnum
;;; arithmetic functions (+f, -f, etc.).

;; Consider reimplementing text x representations to not include an "offset".

;; Worry about overflow in text x operations!


;;; For those few applications that need to deal with the representation of text
;;; widths more explicitly, the constants `number-of-fraction-bits-for-text-widths'
;;; and `scaling-factor-for-text-widths' are provided.

(defconstant number-of-fraction-bits-for-text-widths 8)
(defconstant scaling-factor-for-text-widths              ; 256
  (ash 1 number-of-fraction-bits-for-text-widths))

;; One use for these are in printing, where the scaling is to be done in
;; the PostScript interpreter.  Note that there are some unabstracted
;; assumptions about text widths made in the fontrip.c module.  (MHD 6/1/93)

;; Make use of these in the code below, in reader (#.) macros?!





;;; `Set-text-x' initializes the text x variables, text-x-a and text-x-b, to x,
;;; a workspace or window coordinate or width.

(defmacro set-text-x (text-x-a text-x-b x)
  `(progn
     (setf ,text-x-a ,x)
     (setf ,text-x-b 128)))        ; offset of 1/2, for trivial rounding



;;; `Convert-to-text-width' converts x, a workspace or window coordinate or width,
;;; to text width format.

(defmacro convert-to-text-width (x)
  `(ashf ,x 8))




;;; `Convert-any-number-to-text-width-at-compile-time' is the same as
;;; convert-to-text-width, except that it can take floating-point numbers.  It
;;; must be used only at compile time.  `Convert-any-number-to-text-width' may
;;; be used at run time.

(defun convert-any-number-to-text-width-at-compile-time (number)
  (declare (eliminate-for-gsi))
  (round (* number 256)))


;;; `convert-any-number-to-text-width' ... is just like
;;; convert-any-number-to-text-width-at-compile, but it establishes a temporary
;;; float creation context, making it suitable for use at runtime.

(defun convert-any-number-to-text-width (number)
  (declare (eliminate-for-gsi))
  (with-temporary-gensym-float-creation convert-any-number-to-text-width
      (round (* number 256))))



;;; `Text-width-to-x' converts text-width to a workspace or window coordinate or width.

(defmacro text-width-to-x (text-width)
  `(ashf (+f ,text-width 128) -8))

;; This is used in module TABLES.

;; Consider not rounding.



;;; `Text-width-to-float' converts a text width to gensym float.  This does
;;; gensym float operations, and therefore should normally only be called in a
;;; temporary float creation context.

(defmacro text-width-to-float (text-width)
  `(/e (coerce-fixnum-to-gensym-float ,text-width) 256.0))



;;; `Text-x-to-x' converts the text x represented by text-x-a and text-x-b to a
;;; workspace or window coordinate or width.

(def-substitution-macro text-x-to-x (text-x-a text-x-b)
  text-x-b  ; not used, but should be evaluated, because of offset of 1/2
  text-x-a)

;; This is used in modules FONTS and EDIT.



;;; `Text-x-to-text-width' converts the text x represented by text-x-a and text-x-b
;;; to a text width.  The magnitude of the text x must be such that it can be
;;; converted to a text width that is within fixnum range.

(defmacro text-x-to-text-width (text-x-a text-x-b)
  `(+f (ashf ,text-x-a 8) ,text-x-b -128))

;; This is used in module BOXES.

(defmacro set-text-x-from-text-width (text-x-a text-x-b text-width)
  `(progn
     (setf ,text-x-a (ashf ,text-width -8))
     (setf ,text-x-b (+f (logandf ,text-width #xFF) 128))))



;;; `Incf-text-x' increments the text x represented by text-x-a and text-x-b by
;;; text-width.

(defmacro incf-text-x (text-x-a text-x-b text-width)
  (let ((temp (gensym)))
    `(let ((,temp (+f ,text-x-b ,text-width)))
       (incff ,text-x-a (ashf ,temp -8))
       (setf ,text-x-b (logandf ,temp 255)))))



;;; `Add-to-text-x' adds to the text x represented by text-x-a-1 and text-x-b-1 the
;;; the value of the text x represented by text-x-a-2 and text-x-b-2.

(defmacro add-to-text-x
          (text-x-a-1 text-x-b-1 text-x-a-2 text-x-b-2)
  `(progn
     (incff ,text-x-a-1 ,text-x-a-2)
     (cond
       ((<f (incff ,text-x-b-1 (-f ,text-x-b-2 128)) 0)
        (incff ,text-x-b-1 256)
        (decff ,text-x-a-1))
       ((>=f ,text-x-b-1 256)
        (decff ,text-x-b-1 256)
        (incff ,text-x-a-1)))))



;;; `Subtract-from-text-x' subtracts from the text x represented by text-x-a-1 and
;;; text-x-b-1 the the value of the text x represented by text-x-a-2 and text-x-b-2.

(defmacro subtract-from-text-x
          (text-x-a-1 text-x-b-1 text-x-a-2 text-x-b-2)
  `(progn
     (decff ,text-x-a-1 ,text-x-a-2)
     (cond
       ((<f (decff ,text-x-b-1 (-f ,text-x-b-2 128)) 0)
        (incff ,text-x-b-1 256)
        (decff ,text-x-a-1))
       ((>=f ,text-x-b-1 256)
        (decff ,text-x-b-1 256)
        (incff ,text-x-a-1)))))



;;; `Incremented-text-x-as-x' returns a workspace or window coordinate or width
;;; equivalent to the text x represented by text-x-a and text-x-b incremented by
;;; text-width.

(defmacro incremented-text-x-as-x (text-x-a text-x-b text-width)
  `(+f ,text-x-a (ashf (+f ,text-x-b ,text-width) -8)))



;;; `Magnified-text-x-as-x' returns a workspace or window coordinate or width
;;; equivalent to the text x represented by text-x-a and text-x-b magnified by
;;; magnification.

(def-substitution-macro magnified-text-x-as-x
                        (text-x-a text-x-b x-magnification)
  (+f (magnify text-x-a x-magnification)
       (ashf (+f (magnify (-f text-x-b 128) x-magnification) 128) -8)))

;; This is used in module EDIT.





;;;; Raster and Workspace Arithmetic



;;; A `raster coordinate' is an x or y coordinate, or difference of such
;;; coordinates, in or for a raster.  At present, all raster coordinates (and
;;; hence widths and heights) must be fixnums, so that most raster arithmetic
;;; can be fixnum arithmetic.

;;; The functions +r, -r, =r, /=r, <r, >r, <=r, >=r, minr, maxr, and absr are
;;; like +, -, =, /=, <, >, <=, >=, min, max, and abs, except that they take
;;; raster coordinate arguments and, in the case of all but the comparisons,
;;; produce raster coordinate values.  Note that the arguments of +r and -r must
;;; be such as to allow them to have raster coordinate values.  Halfr computes
;;; the floor of half of raster-coordinate.
;;; Note that there are currently no defined bounds on raster arithmetic.
;;; This means that (minr) and (maxr) will expand into (minf) and (maxf),
;;; i.e. the same bounds as for fixnum arithmetic.
;;; Compare this with (minw) and (maxw) below.
;;; Rumor has it that X rasters are limited to 16 bits.

(def-fixnum-arithmetic-system r)

;; Consider changing the "r" to "-for-raster", and "coordinate" to "measure".

;; Consider defining squarer.

;; Put these into use!



;;; A `workspace coordinate' is an x or y coordinate, or difference of
;;; coordinates, in or for a workspace.  All workspace coordinates (and hence
;;; widths and heights) must be fixnums in the range
;;; `most-negative-workspace-coordinate' to
;;; `most-positive-workspace-coordinate', so that workspace arithmetic can be
;;; fixnum arithmetic.

;;; In fact, four times any workspace coordinate never creates a bignum.  So it
;;; is always safe to do (roundw (+w left right) 2) and it is always safe to do
;;; (+w left offset) where offset is twice most-positive-workspace-coordinate.
;;; But note that (+w left offset) may be outside the legal range for a
;;; workspace coordinate.

;;; Historically G2 was very sloppy about checking that values were kept
;;; inside this range.  We are much more careful now.  I have heard rumors
;;; of one or two places where things leak out still, but I am unaware of
;;; any.  Meanwhile there are likely KBs out there that are outside the range.

;;; During release 3.0 the range used 17 bits.  This was a mistake, it should
;;; have been 16.  These days we use 14 bits, since as of release 4.0 the
;;; number of bits used for scales was increased to support magnified as
;;; well as reduced scaling.

;;; In our current Lisp implementations fixnums are represented in 30 bits, one
;;; of which is the sign.  The scale values are 14 bits, leaving 15 bits for the
;;; range of workspace coordinates.  The min and max values are 14 bits.

;;; Note that computing Euclidean distances sqrt(d1^2+d2^2) is implemented
;;; very carefully in `vector-distance-in-workspace.'

;;; See also the concept `scales.'

(def-concept workspace-unit)

(def-concept workspace-coordinate)

(defconstant most-negative-workspace-coordinate #.(- (expt 2 24)))

(defconstant most-positive-workspace-coordinate #.(- (expt 2 24) 1))

;; Want to be able to multiply workspace units by 4, and then add two of those,
;; without overflowing a fixnum.  Positive fixnums are 29 bits, so
;; conservatively allow 24 bits, which is a hell of a lot (1024x) better than
;; the previous value of 14 bits. -fmw, 7/18/95





;;; The functions +w, -w, =w, /=w, <w, >w, <=w, >=w, minw, maxw, absw, incfw,
;;; and decfw are like +, -, =, /=, <, >, <=, >=, min, max, abs, incf, and decf,
;;; except that they take workspace coordinate arguments and, in the case of all
;;; but the comparisons, produce workspace coordinate values.  Note that the
;;; arguments of +w and -w must be such as to allow them to have workspace
;;; coordinate values.  Halfw computes the floor of half of workspace-coordinate.

(def-fixnum-arithmetic-system w
  :lower-bound most-negative-workspace-coordinate
  :upper-bound most-positive-workspace-coordinate)

;;; Due to the :lower-bound and :upper-bound specified above, the nullary
;;; versions of minw and maxw will be defined naturally as follows:
;;;
;;;         (minw) => most-positive-workspace-coordinate
;;;         (maxw) => most-negative-workspace-coordinate
;;;
;;; This is analogous to defining (+) = 0, (*) = 1, (append) = (),
;;; etc. Generally, given a binary operator F with an identity constant I
;;; (i.e. for all x, (F x I) = x ) it is natural to define the nullary version
;;; (F) = I.  This avoids having to introduce and recall a name for the identity
;;; constant.  Furthermore, one can employ the identity constant to simplify
;;; iteration:
;;;
;;; compare
;;;
;;;   (defun map-hairy-and-reduce-by-F (list)
;;;     (loop with result = (F)
;;;           for elt in list
;;;           do (setq result (F (hairy-code elt) result))
;;;           finally (return result)))
;;;
;;;    which unrolls as   (F (hc eltn)       ; here hc = hairy-code
;;;    (ignoring eval        ...
;;;     order)                       (F (hc elt2)
;;;                                  (F (hc elt1)
;;;                                     (F)))
;;; with
;;;
;;;   (defun map-hairy-and-reduce-by-F (list)
;;;     (loop with result = (hairy-code (first list))
;;;              for elt in (rest list)
;;;           do (setq result (F (hairy-code elt) result))
;;;           finally (return result)))
;;;
;;;   which unrolls as   (F (hc eltn)
;;;                            ...
;;;                              (F (hc elt2)
;;;                                 (hc elt1)))
;;;
;;; [ for a concrete example, choose F = maxw and hairy = some hairy
;;;   coordinate transformation. Then the function computes the maximum
;;;   transformed element of the argument list ]
;;;
;;; These two definitions are equivalent on nonempty lists because (F (hc elt1)
;;; (F)) = (hc elt1) due to the fact that (F) is a right identity [ i.e.  for
;;; all x, (F x (F)) = x ].  It is usually much harder to comprehend the latter
;;; definition, especially if "hairy-code" is hairy (not to mention the increase
;;; in code size).  Needless to say, this complexity quickly gets out of hand if
;;; you have more than one instance of this in a more complicated function. In
;;; general, if F does not have a right identity, then one needs to special case
;;; the initial iteration or accumulation value, which usually results in
;;; increased code size and complexity. For example, compare the first version
;;; of function above, which exploits the right identity (F) in order to treat
;;; each element of the list uniformly in the loop, whereas the latter version
;;; needs to special case the first element and duplicate code.  -wgd 5/18/93





;;; `maximum-x-or-y-separation-allowing-fixnum-vector-distance-calculation' is
;;; used only below by vector-distance-in-workspace.  It specifies an upper
;;; bound on axilateral distances d1, d2 such that the calculation
;;; sqrt(d1^2+d2^2) does not produce intermediate fixnum overflow. Thus it must
;;; be a workspace integer M such that:
;;;
;;;        d1 < M  and  d2 < M  =>  d1^2 + d2^2 < most-postive-fixnum.
;;;
;;; Clearly defining M as isqrt(most-positive-fixnum/2) suffices.

(defparameter-excluding-gsi maximum-x-or-y-separation-allowing-fixnum-vector-distance-calculation
    (floor (sqrt (coerce-to-gensym-float (halff most-positive-fixnum)))))


;;; The macro `vector-distance-in-workspace' returns the length of the vector
;;; (d1, d2) as an integer.  D1 and d2 are positive distances in workspace units.
;;; This is usually employed to compute the Euclidean distance between two
;;; points (x1,y1) and (x2,y2) in the rectilinear plane, where
;;;
;;;         d1 = | x1 - x2 |
;;; and
;;;     d2 = | y1 - y2 |

(def-substitution-macro vector-distance-in-workspace (d1 d2)
  (if (and (<w d1 maximum-x-or-y-separation-allowing-fixnum-vector-distance-calculation)
           (<w d2 maximum-x-or-y-separation-allowing-fixnum-vector-distance-calculation))
      (isqrt (+w (*w d1 d1) (*w d2 d2)))
      (with-temporary-gensym-float-creation vector-distance-in-workspace
        (let ((fd1 (coerce-to-gensym-float d1))
              (fd2 (coerce-to-gensym-float d2)))
          (round (sqrte (+e (*e fd1 fd1) (*e fd2 fd2))))))))

;; This used to be just (isqrt (+w (*w d1 d1) (*w d2 d2))).  This had problems,
;; however with large workspaces.  The squares created bignums rather than
;; fixnums in this case.  One possible solution would be to change the functions
;; that use this to do their computation in window coordinates instead.  The
;; maximum distance allowed could be something like the screen width!

;; In particular, note that since workspace fixnums have 17 bits of magnitude
;; (see the definition of most-negative-workspace-coordinate above), d1^2 + d2^2
;; can have 35 bits, which is greater than the 30 bits provided by Chestnut.
;; This is no longer true since we have changed the magnitude to 14 bits. -pga, 5/9/95

;; No sqrt-e yet!




;;; Workspace-distance-less-than-distance-p ...

(def-substitution-macro workspace-distance-less-than-distance-p (d1 d2 distance)
  (and (<=w d1 distance)
       (<=w d2 distance)
       (<=w (vector-distance-in-workspace d1 d2) distance)))

;; D1 and d2 must be scalars.



;;; Workspace-vector-less-than-distance-p ...

(def-substitution-macro workspace-vector-less-than-distance-p
                        (x1 y1 x2 y2 distance)
  (workspace-distance-less-than-distance-p
    (absw (-w x1 x2)) (absw (-w y1 y2)) distance))



;;; Find-workspace-distance-if-in-range ...

(def-substitution-macro find-workspace-distance-if-in-range
                        (x1 y1 x2 y2 maximum-distance)
  (let* ((d1 (absw (-w x1 x2))) (d2 (absw (-w y1 y2))))
    (if (and (<=w d1 maximum-distance) (<=w d2 maximum-distance))
        (isqrt (+w (expt d1 2) (expt d2 2))))))











;;;; Miscellaneous Arithmetic Primitives



;; THESE SHOULD BE ELIMINATED, OR MOVED TO WHERE THEY ARE USED, BECAUSE THEY ARE
;; NOT TYPE-SPECIFIC!!!



;;; Square computes the square of number.

(def-substitution-macro square (number)
  (* number number))



;;; Enforce-minimum computes (max minimum number).

(defmacro enforce-minimum (minimum number)
  `(max ,minimum ,number))



;;; Enforce-maximum computes (min minimum number).

(defmacro enforce-maximum (maximum number)
  `(min ,maximum ,number))



;;; Restrict-to-range computes (max minimum (min maximum number)).

(defmacro restrict-to-range (minimum maximum number)
  `(max ,minimum (min ,maximum ,number)))










;;;; Exiting G2 to the Operating System


(def-gensym-c-function c-exit (:void "g2ext_exit_from_lisp")
  ((:fixnum-int exit-status)))



(defun exit-lisp-process (&optional status?)
  #+(and lucid development)
  (if status?
      (lucid-common-lisp::quit status?)
      (lucid-common-lisp::quit))

  #+development
  (cerror "Don't exit, just continue"
          "exit-lisp-process called with status ~s" status?)

  #-development
  (progn
    #+chestnut-trans
    (let ((status (or status? 0)))
      (c-exit status))
    #+(and translator (not chestnut-trans))
    (signal-missing-translator-facility EXIT-LISP-PROCESS PRIMITIVES)
    status?)
  )



(def-inlined-pseudo-function-with-side-effects inline-g2-print-backtrace ()
  #+development
  (format t "~%Backtrace: ~S~%" (backtrace)))





;;;; System and Process Primitives

;;; Catch-abort is a macro that is intended to be wrapped around a body of code
;;; in which its companion Abort function may be called.  Its arg should be a
;;; list containing an `abort level', a fixnum integer.  Catch-abort is said to
;;; "bind" the abort level.  A maximum of five levels of abort are permitted,
;;; numbered from 0 through 4.

;;; If the abort occurs, catch-abort returns nil.

;;; Abort, with no arguments, throws to the innermost abort level.  Its optional
;;; argument may be an integer, which should correspond to the abort level for a
;;; corresponding catch higher up.  The call to Abort need not be lexically
;;; contained in the catch-abort block; the catch-abort form has dynamic extent.
;;; (In this sense, Abort is just like Throw and different from Return.)
;;;
;;;    Examples.
;;;
;;;    (defun process-chars
;;;       (CATCH-ABORT (0) ; process chars until user types #\ctrl-c
;;;          (do-forever (process-char (read-char)))))
;;;
;;;    ...
;;;
;;;    (defun process-char (char)
;;;       (if (eql char #\ctrl-c)
;;;           (ABORT 0)  ; Exit process-chars if user types #\ctrl-c
;;;           (process-char-1 char)))
;;;
;;;    ...
;;;
;;;    (let ((x 0)) (catch-abort (x) ...))
;;;    Error: Abort-level should be a fixnum.
;;;    (let ((x 0)) (abort x))
;;;    Error: Abort-level should be a fixnum.

(defvar inner-abort-level-tag)

(defmacro catch-image-exit (&body body)
  `(catch 'exit-image ,body))

(defmacro exit-image ()
  `(throw 'exit-image))

;gsi-api-functions currently use three nested catches, where
;only one is needed. - rh, 11/17/95
(defvar abort-level-0-tag nil)

(defmacro catch-abort ((abort-level &optional dont-whine tag) &body body)
  (if (not (typep abort-level 'fixnum))
      (error "Abort-level should be a fixnum."))
  (let ((abort-tag (intern (format nil "ABORT-LEVEL-~d" abort-level))))
    (if (and (zerop abort-level) tag)
        `(let ((abort-level-0-tag ,tag)
               (inner-abort-level-tag ',abort-tag))
           ,@body)
        `(,(if dont-whine 'ab-lisp::catch 'catch) ',abort-tag
           (let ((inner-abort-level-tag ',abort-tag))
             ,@body)))))

(defun abort (&optional abort-level?)                ; macro before 4/3/89
  (let ((tag (if abort-level?
                 (nth abort-level?
                      '(abort-level-0 abort-level-1 abort-level-2
                        abort-level-3 abort-level-4))
                 inner-abort-level-tag)))
    (when (and (eq tag 'abort-level-0) abort-level-0-tag)
      (setq tag abort-level-0-tag))
    (throw tag nil)))




;;; Avoid-errors (body ...) tries to return nil if a system error is
;;; encountered, instead of going into the lisp system error handler.  It tries
;;; not to do this if there is a really dangerous condition (such as virtual
;;; memory overflow) or a debugging condition.  It is able to guarantee that it
;;; can really avoid any errors at all. It is recommended for use around code
;;; that deals with devices that go into hysterics over the slightest upset,
;;; such as file system and network interfaces, when all the user really wants
;;; is the good old college try.
;;;
;;;    Example:
;;;
;;;    (defun try-to-frobnicate-file (file)
;;;       (when (null (avoid-errors (progn (sys::frobnicate-file file) t)))
;;;          (format t "~&Sorry, I cannot frobnicate ~a at this time.~&" file)))

(defmacro avoid-errors (&body body)
  `(progn . ,body))

;; Remember, Common LISP (CLtL) really let us down by leaving error handling,
;; classifying, intercepting, &so on, for "the future", for "research".  We can
;; hope that the Common Lisp error committee will win, and this sort of thing
;; won't be so necessary, but even so, don't expect a really widely implemented
;; error handling standard till about 1990.

;; More standard error handling abstractions should be implemented and added
;; here!  Avoid-errors is not intended for much serious use in "kernel" code.



;;; jh, 12/28/95.  Moved the process-managing foreign functions from
;;; FILE-SYSPROC to where Telewindows can use them.

(def-gensym-c-function c-get-process-identifier (:double-float "g2ext_get_process_identifier")
  ())

(def-gensym-c-function c-spawn_command_line_process
                       (:double-float "g2ext_spawn_command_line_process")
  ((:string command-string)))

(def-gensym-c-function c-spawn_executable_process
                       (:double-float "g2ext_spawn_command_directly")
  ((:string command-string)))

(def-gensym-c-function c-set_inherit_stdio_handles
                       (:fixnum-int "g2ext_set_inherit_stdio_handles")
  ((:fixnum-int new-value)))

(def-gensym-c-function c-kill_spawned_command_line
                       (:fixnum-int "g2ext_kill_spawned_command_line")
  ((:double-float process-id)))

(def-gensym-c-function c-process_exists
                       (:fixnum-int "g2ext_process_exists")
  ((:double-float process-id)))

(def-gensym-c-function c-load_library
                       (:fixnum-int "g2ext_load_library")
  ((:string name)
   (:string init-function-name)
   (:object init-function-arg)))

(def-gensym-c-function c-produce_shared_object
                       (:fixnum-int "g2ext_produce_shared_object")
  ((:string kb_filename)
   (:fixnum-int nfiles)
   (:string obj_suffix)
   (:string dll_name)))

(def-gensym-c-function c-set-include-directory
                       (:fixnum-int "g2ext_set_include_directory")
  ((:string directory)))

#-development
(def-gensym-c-function c-show-function-address
                       (:fixnum-int "g2ext_show_function_address")
  ((:object function)))




#+development
(defvar load-lisp-p t) ; rebound to NIL by load-library-for-gsi

(defun-simple load-library (name init-function-name init-function-arg)
  (cond
    #+development
    (load-lisp-p
     (load name)
     t)
    (t
     (=f 0 (c-load_library name init-function-name init-function-arg)))))

;;; `C-substatus_run_command_line' runs the command string through the operating
;;; system's command interpreter and returns the resulting status of the
;;; subprocess that gets created.  Note: this can hang the system.  It therefore
;;; cannot be used in general when G2 is fully brought up and running.  This is
;;; used now in only one special situations: the check for a useable g2passwd
;;; executable at the startup of a (secure) G2 process.  This returns the result
;;; of calling substatus_run_command_line_for_g2; see its documentation in
;;; cprocess.c.

(def-gensym-c-function c-substatus_run_command_line
                       (:fixnum-int "g2ext_substatus_run_command_line")
  ((:string command-string)))


;;; `c-uuid-create' interfaces to a C function that knows how to call the
;;; platform-specific API function to get a UUID, if any, and stuff the bytes
;;; into the passed in wide-string buffer in the appropriate byte order. If we
;;; have a native implementation, and the call is successful, then this will
;;; return zero. Otherwise, this will return non-zero.
;;;
;;; On Win32 (IntelNT and AlphaNT), this is implemented usefully. The generally
;;; returns zero, but it may return non-zero if there's a problem getting a
;;; unique ID. In this case, the result is either of these special values, as
;;; documented in the Win32 Platform SDK:
;;;
;;;   RPC_S_UUID_LOCAL_ONLY - The UUID is guaranteed to be unique to this
;;;     computer only.
;;;   RPC_S_UUID_NO_ADDRESS - Cannot get Ethernet or token-ring hardware
;;;     address for this computer.
;;;
;;; The constants `rpc_s_uuid_local_only' and `rpc_s_uuid_no_address' are
;;; defined here, and give the values for the corresponding C constants, as
;;; given by the Windows include file <winerror.h>.  The constants
;;; `rpc_s_uuid_local_only-message' and `rpc_s_uuid_no_address-message' are
;;; strings with the text for the corresponding error codes suggested by
;;; comments <winerror.h>.

(def-gensym-c-function c-uuid-create
    (:fixnum-int "g2ext_uuid_create")
  ((:wide-string buffer)))

(defconstant rpc_s_uuid_local_only 1824)
(defconstant rpc_s_uuid_no_address 1739)
(defconstant rpc_s_uuid_local_only-message
  "A UUID that is valid only on this computer has been allocated.")
(defconstant rpc_s_uuid_no_address-message
  "No network address is available to use to construct a universal unique identifier (UUID).")

;; A way to recreate the rpc_s_uuid_local_only condition is to run on any
;; Windows machine, and pull the network card, then reboot. (MHD 1/3/01)

;; With the addition of c-uuid-create at this time, the function
;; c-get-ethernet-address is obsolete and has been removed. (MHD 12/24/01)





;;;; Fixnum CASE Statement




;;; The following is an abstraction for CASE statements which take fixnum
;;; control expression values, and very efficiently dispatch to the clauses.  In
;;; some implementations these case statements turn into IF THEN ELSE style
;;; binaries.  However, Lucid, Chestnut, and GLT can compile these into table
;;; based branch instructions.

;;; This macro has mainly been written for Chestnut, such that this macro will
;;; emit a C "switch" statement to perform the dispatch.  Hopefully C compilers
;;; will then turn this into a table based branch.

;;; Proper optimization of this form depends somewhat on the format of the case
;;; choices, as well as the fact that the dispatching value is a fixnum.  The
;;; values should be fixnums, and there should not be large gaps between the
;;; values being selected between.  In fact, Lucid will not optimize if ten
;;; percent of the possible values within the span between the highest and
;;; lowest value are not selected upon.  Further, the fixnum must be such that
;;; it could fit within a signed 16 bit INT in C (-32768 to 32767).  In
;;; practice, I assume that the optimizations possible within C compilers work
;;; best when the control number is an integer from 0 through 255.

(defmacro fixnum-case (fixnum-keyform &body clauses)
  `(case (the fixnum ,fixnum-keyform) ,@clauses))




;;; The macro `ascii-char-code' returns the ASCII code for char.

(defmacro ascii-char-code (char) `(the fixnum (char-code ,char)))


;;; The macro `ascii-code-char' returns the character for ascii-code.  This is
;;; similar to CL's code-char, except that it cannot accept values outside the
;;; range 0..255.  In addition, it can never return nil.  Note that ASCII is a
;;; 7-bit characters, but despite the name, this really handles 8-bit character
;;; codes.

(defmacro ascii-code-char (ascii-code)
  `(code-char (the fixnum ,ascii-code)))

;; This could be implemented as a vector array reference if speedier and
;; necessary. (MHD 2/22/96)


;;; `Wide-character-code-offset' is an offset added to wide character codes to
;;; turn them into wide characters in development images.  A wide character,
;;; then, is implemented as the integer that is its code plus this offset.  The
;;; offset is currently one million (1000000).  During distribution, wide
;;; characters are fixnums between 0 and #xFFFF.

(defconstant wide-character-code-offset 1000000)




;;; The macro `wide-character-code-is-noop-p' is used to abstract the predicate
;;; about whether or not wide-character-code is currently subtracting off its
;;; offset.  This test is used in several of the primitives of wide-strings.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro wide-character-code-is-noop-p ()
  '(not (eval-feature :development)))
)

#+development
(defun wide-character-code-function (wchar)
  (test-assertion
    (and (fixnump wchar)
         (<=f wide-character-code-offset
              wchar
              (+f wide-character-code-offset #xffff))))
  (-f wchar wide-character-code-offset))

#+development
(defun code-wide-character-function (code)
  (test-assertion (and (fixnump code) (<=f 0 code #xffff)))
  (+f code wide-character-code-offset))




;;; `Wide-character-code' takes a wide character, and returns its corresponding
;;; code.  Note that the logic of this cond clause is somewhat tortured, since
;;; we want to use the wide-character-code-is-noop-p predicate, but must also
;;; have a #+development switch to avoid distribution compile warnings about the
;;; missing wide-character-code-function.

(defmacro wide-character-code (wide-character)
  (cond ((wide-character-code-is-noop-p)
         wide-character)
        #+development
        ((constantp wide-character)
         (wide-character-code-function (eval wide-character)))
        ;; If we are getting the code of a wide character fetched from a wide
        ;; string using charw, skip the encoding and decoding and just fetch the
        ;; code from the underlying byte-vector-16.
        ((and (consp wide-character)
              (eq (car wide-character) 'charw))
         (cons 'charw-bv16 (cdr wide-character)))
        (t
         `(wide-character-code-function ,wide-character))))




;;; `Code-wide-character' should be called with a wide character code.  This
;;; returns the wide character corresponding to that code.

(defmacro code-wide-character (character-code)
  (cond ((wide-character-code-is-noop-p)
         character-code)
        #+development
        ((constantp character-code)
         (code-wide-character-function (eval character-code)))
        (t
         `(code-wide-character-function ,character-code))))




;;; `Coerce-to-wide-character' takes either a wide character (whatever that is),
;;; or a character code (a 16-bit unsigned integer) or a Common Lisp character
;;; object, and always makes it be a wide character (whatever that is).
;;;
;;; It may be assumed that coerce-to-wide-character does not allocate memory.
;;;
;;; It is an error to give this anything that cannot be recognized as either
;;; a character, a wide character, or a (wide) character code.  If that happens,
;;; the results are unspecified.  In development, this signals an error in that
;;; case.

(defmacro coerce-to-wide-character (code-or-character-or-wide-character)
  (let ((thing '#:thing))
    `(let ((,thing ,code-or-character-or-wide-character))
       (if (characterp ,thing)
           (character-to-wide-character ,thing)
           ,(if (wide-character-code-is-noop-p)
                `,thing
                `(if (<=f 0 ,thing #xFFFF)
                     (code-wide-character ,thing)
                     (progn
                       #+development
                       (test-assertion
                         (<=f ,(+f wide-character-code-offset 0) ; assume?
                              ,thing
                              ,(+f wide-character-code-offset #xFFFF)))
                       ,thing)))))))



;;; `Character-to-wide-character' is a macro that performs the common
;;; translation from the Common Lisp character data type to Gensym's
;;; wide-character data type.  Character must be a CL character object.  This
;;; returns the corresponding wide character.

;;; `Wide-character-to-character' performs the reverse translation; however,
;;; note that it is an error to call this with a wide character whose code is
;;; greater than #xFF, since there would be no corresponding Common Lisp
;;; character.  However, ensuring a valid argument is the responsibility of the
;;; caller, and this does no error checking.

(defmacro character-to-wide-character (character)
  #-development
  `(code-wide-character (ascii-char-code ,character))
  #+development
  `(+f (ascii-char-code ,character) wide-character-code-offset))

(defmacro wide-character-to-character (wide-character)
  `(ascii-code-char (wide-character-code ,wide-character)))



;;; `Wide-character-code-high-byte' and `wide-character-code-low-byte' return
;;; the high and low byte, respectively, of a wide character code (a 16-bit
;;; integer).  `Wide-character-high-byte' and `wide-character-low-byte' return
;;; the high and low byte, respectively, of a wide character.

(defmacro wide-character-code-high-byte (wide-character-code)
  `(ashf ,wide-character-code -8))

(defmacro wide-character-high-byte (wide-character)
  `(wide-character-code-high-byte (wide-character-code ,wide-character)))

(defmacro wide-character-code-low-byte (wide-character-code)
  `(logandf #xFF ,wide-character-code))

(defmacro wide-character-low-byte (wide-character)
  `(wide-character-code-low-byte (wide-character-code ,wide-character)))



;;; The macro `character-case' is a variant of case which takes advantage of
;;; fixnum-case to do efficient dispatching on characters.  The semantics are
;;; the same as case except that the keylists or elements thereof are either
;;; characters or the symbols 't or 'otherwise.

(defun-for-macro evaluate-character-keylist (dispatch)
  (cond ((symbolp dispatch) dispatch)
        ((characterp dispatch) (ascii-char-code dispatch))
        (t (loop for char in dispatch collecting (ascii-char-code char)))))

(defmacro character-case (test-character &body clauses)
  `(fixnum-case (ascii-char-code ,test-character)
     ,@(loop for (keylist . consequences) in clauses
             collecting
             `(,(evaluate-character-keylist keylist)
                ,@consequences))))




;;; `Wide-character-case' is like character-case, but for the wide character
;;; abstract datatype.  See those functions for documentation and restrictions.

(defmacro wide-character-case (keyval &rest clauses)
  `(fixnum-case (wide-character-code ,keyval)
     . ,(loop for (test . action) in clauses
              do (cond
                   ((consp test)
                    (setq test
                          (loop for wide-character in test
                                collect
                                  (wide-character-code wide-character))))
                   (t
                    (unless (symbolp test)
                      (setq test (wide-character-code test)))))
              collect (cons test action))))






;;;; Misc Utilities



;;; `No-operation-function' is a function of no arguments returning
;;; no useful value.

(defun-void no-operation-function () )


(defun intel-inside-p ()
  (declare (eliminate-for-gsi))
  (with-temporary-gensym-float-creation intel-inside-p
    (let ((a 4195835.0d0)
          (b 3145727.0d0))
      (> (- a (* b (/ a b))) 100))))




;;; The macro `double-float-vector-p' is an inlined predicate for determining
;;; whether or not a given item is a simple-array of double-floats.  It is
;;; translated into a call to a macro defined in rtl/c/gensym.h,
;;; INLINE_DOUBLE_FLOAT_VECTOR_P.

(defmacro double-float-vector-p (thing)
  (if (and (eval-feature :chestnut-3)
           (eval-feature :translator))
      (if (or (symbolp thing) (constantp thing))
          `(/=f (inline-double-float-vector-p ,thing) 0)
          (let ((arg (gensym)))
            `(let ((,arg ,thing))
               (/=f (inline-double-float-vector-p ,arg) 0))))
      #+(and development lucid)
      `(lucid-float-simple-vector-p ,thing)
      #-(and development lucid)
      `(typep ,thing '(simple-array ,(gensym-float-type) (*)))))

(declare-side-effect-free-function inline-double-float-vector-p)

#+(and chestnut-3 translator)
(tx::def-foreign-function
    (inline-double-float-vector-p (:name "INLINE_DOUBLE_FLOAT_VECTOR_P")
                                  (:return-type :fixnum))
    (symbol :object))

#-(and chestnut-3 translator)
(defun inline-double-float-vector-p (thing)
  (if (typep thing '(simple-array double-float (*)))
      1
      0))

(defmacro long-p (thing)
  (if (and (eval-feature :chestnut-3)
	   (eval-feature :translator))
      (if (or (symbolp thing) (constantp thing))
	  `(/=f (inline-long-p ,thing) 0)
	  (let ((arg (gensym)))
	    `(let ((,arg ,thing))
	       (/=f (inline-long-p ,arg) 0))))
    `(typep ,thing (gensym-long-type))))

(declare-side-effect-free-function inline-long-p)

#+(and chestnut-3 translator)
(tx::def-foreign-function
    (inline-long-p (:name "INLINE_LONG_P")
			  (:return-type :fixnum))
    (symbol :object))

(defmacro gensym-long-p (thing)
  `(long-p ,thing))

(defmacro long-vector-p (thing)
  (cond ((eval-feature :chestnut-trans)
	 (if (or (symbolp thing) (constantp thing))
	     `(/=f (inline-long-vector-p ,thing) 0)
	   (let ((arg (gensym)))
	     `(let ((,arg ,thing))
		(/=f (inline-long-vector-p ,arg) 0)))))
	(t
	 `(typep ,thing '(simple-array ,(gensym-long-type) (*))))))

(declare-side-effect-free-function inline-long-vector-p)

#+(and chestnut-3 translator)
(tx::def-foreign-function
    (inline-long-vector-p (:name "INLINE_LONG_VECTOR_P")
			  (:return-type :fixnum))
    (symbol :object))

;;; The macro `unsigned-byte-16-vector-p' is an inlined predicate for
;;; determining whether or not a given item is a simple-array of unsigned-byte
;;; 16 elements.  It is translated into a call to a macro defined in
;;; rtl/c/gensym.h, INLINE_UNSIGNED_BYTE_16_VECTOR_P.

(defmacro unsigned-byte-16-vector-p (thing)
  (if (eval-feature :translator)
      (if (or (symbolp thing) (constantp thing))
          `(/=f (inline-unsigned-byte-16-vector-p ,thing) 0)
          (let ((arg (gensym)))
            `(let ((,arg ,thing))
               (/=f (inline-unsigned-byte-16-vector-p ,arg) 0))))
      #+(and development lucid)
      `(lucid-unsigned-byte-16-simple-vector-p ,thing)
      #-(and development lucid)
      `(typep ,thing '(simple-array (unsigned-byte 16) (*)))))

(declare-side-effect-free-function inline-unsigned-byte-16-vector-p)

#+translator
(tx::def-foreign-function
    (inline-unsigned-byte-16-vector-p (:name "INLINE_UNSIGNED_BYTE_16_VECTOR_P")
                             (:return-type :fixnum-long))
    (symbol :object))

#-translator
(defun inline-unsigned-byte-16-vector-p (thing)
  (if (typep thing '(simple-array (unsigned-byte 16) (*)))
      1
      0))





#+(and development lucid)
(proclaim '(optimize (compilation-speed 0))) ; cause TYPEP to be inlined

#+(and development lucid)
(eval-when (:compile-toplevel :load-toplevel :execute)
(defun lucid-float-simple-vector-p (thing)
  (typep thing '(simple-array gensym-float (*))))

(defun lucid-unsigned-byte-16-simple-vector-p (thing)
  (typep thing '(simple-array (unsigned-byte 16) (*))))
)


#+(and development lucid)
(proclaim '(optimize (compilation-speed 3)))





(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant g2-stream-open-mode-for-input 0)
(defconstant g2-stream-open-mode-for-output 1)
(defconstant g2-stream-open-mode-for-appending 2)
(defconstant g2-stream-open-mode-for-update 3)
(defconstant g2-stream-open-mode-for-binary-input 4)
(defconstant g2-stream-open-mode-for-binary-output 5)
(defconstant g2-stream-open-mode-for-binary-appending 6)
(defconstant g2-stream-open-mode-for-binary-update 7)
)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant g2-stream-foreign-file-op-success 0)
(defconstant g2-stream-foreign-file-op-failure -1)
)

(def-gensym-c-function c-g2_probe_file (:pointer "g2ext_g2_probe_file")
  ((:string namestring)))

(def-gensym-c-function c-g2_probe_file_wide (:pointer "g2ext_g2_probe_file_s16")
  ((:wide-string namestring)))

(def-gensym-c-function c-g2_stream_open (:pointer "g2ext_g2_stream_open")
  ((:string namestring)
   (:fixnum-int open-mode)))

(def-gensym-c-function c-g2_stream_open_wide (:pointer "g2ext_g2_stream_open_s16")
  ((:wide-string namestring)
   (:fixnum-int open-mode)))

(def-gensym-c-function c-g2_stream_write_string
                       (:fixnum-int "g2ext_str_write_string")
  ((:string output-string)
   (:pointer g2-output-stream)
   (:fixnum-int write-newline-p)))

(def-gensym-c-function c-g2_stream_close
                       (:fixnum-int "g2ext_str_close")
  ((:pointer g2-stream)))

(def-gensym-c-function c-run-trace (:fixnum-int "g2ext_run_trace")
  ((:string command)
   (:fixnum-int length)
   (:fixnum-int wide-p)))

(def-gensym-c-function c-run-trace-wide (:fixnum-int "g2ext_run_trace")
  ((:byte-vector-16 command)
   (:fixnum-int length)
   (:fixnum-int wide-p)))

(defun-simple run-trace (string)
  (/=f 0
       (cond ((text-string-p string)
              (c-run-trace-wide string (lengthw string) 1))
             ((stringp string)
              (c-run-trace string (length string) 0))
             (t
              0))))

(def-gensym-c-function c-visible-window-is-present
                       (:fixnum-int "g2ext_visible_window_is_present")
  ())

(defun-simple visible-window-is-present-p ()
  (/=f 0 (c-visible-window-is-present)))

(def-gensym-c-function c-window-is-present
                       (:fixnum-int "g2ext_window_is_present")
  ())

(defun-simple window-is-present-p ()
  (/=f 0 (c-window-is-present)))

(def-gensym-c-function c-cache-c-pointer
    (:pointer "g2ext_cache_cpointer")
  ((:pointer c-pointer)))

(def-gensym-c-function c-decache-g2-pointer
    (:void "g2ext_decache_g2pointer")
  ((:pointer g2-pointer)))

;;; The macro `units-to-integer' is defined as follows.  (units-to-integer
;;; <unit>) expects <unit> to be one of the symbols: second, minute, hour, day
;;; and week. It expands into a form which returns the following values
;;; respectively: 1, 60, 3600, 86400 and 604800, that is the number of seconds
;;; in the unit. If the unit is number, then it is treated just as are seconds.

(defmacro units-to-integer (unit)
  (let ((unit-evaluated (gensym)))
    `(let ((,unit-evaluated ,unit))
       (case ,unit-evaluated
         (number 1)
         ((second seconds) 1)
         ((minute minutes) 60)
         ((hour hours) 3600)
         ((day days) 86400)
         ((week weeks) 604800)
         (t 1))))) ; make compiler happy

;;; GENSYM-47032 (G2 Thread Service)  -- Chun Tian (binghe)

#+SymScale
(progn

(def-gensym-c-function c-max-threads (:fixnum-int "g2ext_max_threads")
  ())

(def-gensym-c-function c-number-of-cores (:fixnum-int "g2ext_number_of_cores")
  ())


;; G2-MAX-THREADS is a limitation from Chestnut RTL, it equals to the
;; macro definition of VALUE_CELL_SLOTS in common_config.h
(defparameter g2-max-threads (c-max-threads))

(defparameter max-number-of-cores (c-number-of-cores))

;; At runtime, the value of `number-of-all-threads' will be reset to its
;; actual value.
(defparameter number-of-all-threads g2-max-threads)

(defun-simple make-thread-array (object)
  (let ((thread-array (make-static-array number-of-all-threads)))
    (loop for index from 0 below number-of-all-threads
	  doing
      (setf (svref thread-array index) object))
    thread-array))

(defvar current-thread-index 0)

(defmacro t-svref (thing)
  `(svref ,thing current-thread-index))

) ; progn

;;; Exponential backoff algorithm
;;; (it's here bacause the use of with-temporary-gensym-float-creation)

#+SymScale
(progn
  (defparameter backoff-min-delay 0001) ; in 1/1000 seconds
  (defparameter backoff-max-delay 1024) ; in 1/1000 seconds
  (defvar backoff-limit backoff-min-delay)

  ;; NOTE: before calling this function, please locally bind BACKOFF-LIMIT.
  (defun-void back-off ()
    (let ((delay (g2-random backoff-limit)))
      (declare (type fixnum delay))
      (setq backoff-limit
	    (minf backoff-max-delay (*f 2 backoff-limit)))
      #+development
      (when (=f backoff-limit backoff-max-delay)
	(cerror "continue" "Back-off timeout!")
	#+ignore
	(format t "Back-off timeout!~%"))
      (with-temporary-gensym-float-creation back-off
	(gensym-sleep (/e (coerce delay (gensym-float-type)) 1000.0d0))))))

;;; A recursive lock protecting clock globals

;; If this pattern will repeat, we'll make these 5 defs into a macro.

#+mtg2
(defvar clock-lock
  (tx:make-recursive-lock :name #.(symbol-name 'clock-lock)))

(defmacro with-clock-sync (&body body)
  #+mtg2
  `(tx:with-lock-held (clock-lock) ,@body)
  #-mtg2
  `(progn ,@body))

(defmacro clock-get (var)
  `(with-clock-sync ,var))

(defmacro clock-put (var val)
  `(with-clock-sync (setf ,var ,val)))

(defsetf clock-get clock-put)
 

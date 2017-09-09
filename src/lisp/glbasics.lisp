;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GLBASICS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson and Jim Allard




;;;; Basic Facilities for Both G2 and GLT




(declare-forward-reference gsi-magic-number variable)

(declare-forward-reference current-system-name variable) ;LAUNCH
(declare-forward-reference exit-lisp-process function) ;PRIMITIVES
(declare-forward-reference nanp function) ; INT2


;;;; Lucid Fixes


;;; Advise lcl:record-source-file to behave as if functions defined
;;; merely as forward references were not defined at all.
;;; We do this simply by undefining them and then continuing
;;; with what record-source-file normally does. -fmw

#+(and lucid (not translator))
(lcl:defadvice (lcl:record-source-file handle-forward-references)
    (object type &optional (locator lcl:*source-pathname*)
            (load-instance system:*load-instance*) coldload-p)
  ;; Here we rely on the fact that record-source-file is called
  ;; BEFORE the function is redefined.
  (when (and (eq type 'function)
             (symbolp object)
             (fboundp object)
             ;; We compare the procedure names rather than their compiled
             ;; function objects in case the stand-in function was recompiled
             ;; during the build (for example, whenever bootstrap.lisp is compiled,
             ;; CHECK-MEMORY is fbound to a different version of the stand-in
             ;; function than is now installed.) -fmw
             (let ((function (symbol-function object)))
               ;; See also find-dead-forward-references
               (and
                 (typep function 'system:procedure)
                 (let ((name (system:procedure-name function)))
                   ;; In Lucid 4.0, SYSTEM:PROCEDURE-NAME on interpreted
                   ;; functions returns the list (NAMED-LAMBDA FOO ...) instead
                   ;; of the name.  Fix that here. (fmw 5-Aug-93)
                   #-LCL4.1
                   (when (and (consp name)
                              (eq (first name) 'lcl:named-lambda))
                     (setq name (second name)))
                   (eq name 'stand-in-for-forwardly-referenced-function)))))
    (fmakunbound object))

  (lcl:advice-continue object type locator load-instance coldload-p))




;;;; Concepts


;;; The macro `def-concept' expands to nothing in production code.  In
;;; development, it records NAME as a definition and makes it visible to etags
;;; in emacs.  The Body may include a documentation string which is also
;;; recorded.  Name-and-type is either a symbol, or a list of (name type).
;;; The default definition type is Concept.

(defmacro def-concept (name-and-type &body body)
  #-development (declare (ignore name-and-type body))
  #+development (let* ((name (if (atom name-and-type) name-and-type (car name-and-type)))
                        (type (if (atom name-and-type) 'concept (cadr name-and-type)))
                        (doc (if (stringp (car body))
                                 (car body))))
                  #+sbcl (declare (ignore type))
                   `(progn
                     ;; This just annoys you when a concept is defined in several ways.
                     ;;                     (lcl:record-source-file ',name ',type)
                      ,@(when doc
                          ;; It is CL that documentation is setf-able, but our
                          ;; ab:documentation is not defined until SITE.
                          #+(or lucid allegro lispworks)
                          `((setf (lisp:documentation ',name ',type) ',doc)))
                      ',name)))


(def-concept concept
  "What a concept!")




;;; The macro `dwarn' is a development-only call to WARN.

(defmacro dwarn (format &rest args)
  #+development `(warn ,format ,@args)
  #-development (declare (ignore format args)))


;;; The macro `dmesg' is a development-only call to FORMAT.

(defmacro dmesg (format &rest args)
  #+development `(format t ,format ,@args)
  #-development (declare (ignore format args)))


;;; The macro `dmesgln' is a development-only call to FORMAT and FRESH-LINE.

(defmacro dmesgln (format &rest args)
  #+development `(progn (format t ,format ,@args) (fresh-line))
  #-development (declare (ignore format args)))


;;; The macro `with-tracing' is a development-only wrapper for trace print
;;; statements.  The real macro, with-tracing-1, is in GLDEBUG.

(defmacro with-tracing ((kind &key block) &body body)
  #-development (declare (ignore kind block body))
  #+development `(with-tracing-1 (,kind :block ,block) ,@body))



(defmacro assert-for-development (predicate &optional message? &rest args)
  #+development
  (let ((message (or message? (format nil "Assertion failed: ~s" predicate))))
    `(unless ,predicate
       (cerror "Continue" ,message ,@args)))
  #-development
  (declare (ignore predicate message? args))
  #-development
  nil)

(defmacro check-type-for-development (value type)
  #+development
  (let ((result (make-symbol "RESULT")))
    `(let ((,result ,value))
       (unless ,(if (and (constantp type)
                         (eq (eval type) 'fixnum))
                    `(fixnump ,result)
                    `(typep ,result ,type))
         (cerror "Continue"
                 "~S was not of type ~S"
                 ,result ,type))
       ,result))
  #-development
  (declare (ignore type))
  #-development
  value)

(defmacro progn-for-development (&rest forms)
  #+development
  `(progn ,@forms)
  #-development
  (declare (ignore forms))
  #-development
  nil)


#-development
(defmacro formatd (&rest exps)
  (declare (ignore exps))
  (warn "Debugging macro formatd appears in ~s" most-recent-defun-name))


;;;; Variables for Chestnut Debugging

;;; Incremental compiling in Chestnut does not allow the creation of global
;;; variables. Hence some spares for such use.

(defvar debug-1 nil)
(defvar debug-2 nil)
(defvar debug-3 nil)
(defvar debug-4 nil)
(defvar debug-5 nil)
(defvar debug-6 nil)
(defvar debug-7 nil)
(defvar debug-8 nil)
(defvar debug-9 nil)
(defvar debug-10 nil)
(defvar debug-11 nil)
(defvar debug-12 nil)




;;;; Built-In Packages



;;; `Lisp-package-1' is bound to the lisp package.  The lisp package
;;; contains all GL (most Common Lisp) "primitives": user-visible
;;; functions, special forms, macros, and global variables.

(defvar lisp-package-1
  #+ansi-cl (find-package "COMMON-LISP")
  #-ansi-cl (find-package "LISP"))



;;; `Keyword-package-1' is bound to the keyword package, which contains
;;; all `keywords': symbols prefixed by : which evaluate to themselves.

(defvar keyword-package-1 (find-package "KEYWORD"))



;;; `Symbol-is-keyword-p' is true if symbol is a keyword.

(defmacro symbol-is-keyword-p (symbol)
  `(eq (symbol-package ,symbol) keyword-package-1))



;;; `Keyword-symbol-p' returns non-nil if the object it is given is a
;;; symbol and it is in the KEYWORD package and nil otherwise.

(defun-for-macro keyword-symbol-p (object)
  (and (symbolp object)
       (string= "KEYWORD" (package-name (symbol-package object)))))






;;;; Storage Allocation Primitives



;;; `Within-managed-object-scope' indicates if we are in the scope of
;;; the with-managed-objects wrapper.

(defvar within-managed-object-scope nil)

;; With-managed-objects is defined in PRIMITIVES.  -pto 03sep90



(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro in-static-area (&body forms)
  #+(and lispworks (not chestnut-3))
  `(sys:in-static-area ,@forms)
  #-(and lispworks (not chestnut-3))
  `(progn ,@forms))
)



;;;   with-dynamic-creation {form}*  [macro]

;;; The macro `with-dynamic-creation' will cause any consing which occurs within
;;; the dynamic scope of this form to be created within a dynamic area of
;;; memory, i.e.  one that is elegible for garbage collection.  It returns all
;;; values returned for the last form in its body.  This form should be used
;;; around areas of the code which we do not yet have under consing control.

;;; On the Lisp machine this will lambda bind the default consing area to be the
;;; dynamic unmanaged area that is the default consing area for this system.  In
;;; Lucid 2.x, we will be wrapping the body with the lucid::with-dynamic-area
;;; macro.  In Lucid 3.0, we will be wrapping the body with
;;; lucid::with-normal-consing-area.



(defmacro with-dynamic-creation (&rest forms)
  (feature-case
    (:chestnut-trans
      (feature-case
        (:chestnut
          `( ,(intern "WITH-DYNAMIC-AREA" "TRUN")
            ,@forms))
        (:chestnut-3
          `( ,(intern "WITH-DYNAMIC-AREA" "TX")
            ,@forms))))
    (:vanilla-areas
     `(progn
        ,@forms))
    (:translator
      (warn "This translator has no WITH-DYNAMIC-CREATION code.")
      `(progn ,@forms))
    ((and :lucid :no-lucid-temporary-areas)
     `(,(intern "WITH-NORMAL-CONSING-AREA" "LUCID")
       ,@forms))
    (:lucid
     `(,(intern "WITH-NORMAL-CONSING-AREA" "LUCID")
       ,@forms))
    (:lispworks
     `(in-static-area
        ,@forms))))


;;;; Macro Definition Aids


;;; `split-declarations-and-documentation-from-statements' takes a list known
;;; here as a body and returns two lists.  One is the any doc or declarations
;;; found on the front of the list body.  For example
;;;  '("Documentation" (declare foo) "Result") -- becomes -->
;;;  ("Documentation" (DECLARE FOO))
;;;  ("Result")

(defun-for-macro split-declarations-and-documentation-from-statements (body)
  (loop
    for rest-of-body on body
    while
    (or (if (not (atom (car rest-of-body)))
            (eq (caar rest-of-body) 'declare))
        (and (stringp (car rest-of-body))
             (cdr rest-of-body)))
    collect (car rest-of-body) into declarations-and-documentation
    finally (return (values declarations-and-documentation rest-of-body))))





;;;; Atomic Operations



;;; As-atomic-operation guarantees that the body will be executed atomically.
;;; That is, so long as all possibly conflicting code that has side affects
;;; on shared global data structures is performed within an as-atomic-operation
;;; form, there should be no inconsistent results.  As-atomic-operation forms
;;; may be nested.

;;; Any operations that alter plists of symbols (i.e. "setf of get" operations),
;;; or any other global structures for that matter, should be performed as
;;; atomic operations.

;;; For Lisps without multiple processes (the majority), this form does nothing.
;;; On Lisps with multiple processes (within the same address space), this form
;;; should guarantee that no interruption of body will happen once it has
;;; started executing.

(defmacro as-atomic-operation (&body body)
  `(progn ,@body))




;;;; Reusable Gensyms



;;; `Gensym-gensym' is the same as gensym except that, within the
;;; dynamic scope of a using-reusable-gensyms form, it may return
;;; a reusable gensym.

;;; `Using-reusable-gensyms' causes calls to gensym-gensym within the
;;; dynamic scope of body to use reusable gensyms.  After this has
;;; been exited, any reusable gensyms used within it must be free for
;;; use, that is, free to be returned by gensym-gensym.
;;; Using-reusable-gensyms forms can be nested.

;;; `Reusable-gensyms' is a global list of all reusable gensyms.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar reusable-gensyms)

(defun reusable-gensyms ()
  (declare (eliminate-for-no-macros-gsi))
  (if (boundp 'reusable-gensyms)
      reusable-gensyms
      (setq reusable-gensyms (list (gensym)))))

(defvar available-reusable-gensyms nil)

(defmacro using-reusable-gensyms (&body body)
  `(let ((available-reusable-gensyms
           (or available-reusable-gensyms (reusable-gensyms))))
     . ,body))

(defun gensym-gensym ()                                ; Change to use gensym-make-symbol
  (declare (eliminate-for-no-macros-gsi))
  (if (null available-reusable-gensyms)
      (gensym)
      (as-atomic-operation
        (if (null (cdr available-reusable-gensyms))
            (setf (cdr available-reusable-gensyms) (list (gensym))))
        (pop available-reusable-gensyms))))

) ; closes eval-when

;; Note that the list of reusable gensyms could be being used in two
;; processes concurrently.

;; Use gensym-gensym pervasively in place of gensym!?


;;; `Gensym-make-symbol' is a compile time function similar to make-symbol that
;;; returns an uninterned symbol.  It differs in that the print name will be
;;; made unique.  Note that for gensyms produced during translations into C, the
;;; gensym function will not return unique print names.  The translator itself
;;; generates unique print names in a consistent way on translation.

(defun-for-macro gensym-make-symbol (print-name-prefix)
  (let* ((prefix-string
           (cond
             ((stringp print-name-prefix) print-name-prefix)
             ((symbolp print-name-prefix) (symbol-name print-name-prefix))
             (t (cerror "Continue."
                        "gensym-make-symbol should be called with a symbol or string.")
                "G"))))
    (prog1
      (gensym prefix-string)
      (gensym "G"))))




;;; `With-gensyms-for-args' aids in defining macros by wrapping the
;;; "normal expansion" (the result of evaluating body) in a let form
;;; that binds gensym vars to each of the (arg form) values of the
;;; arg vars, where body is evaluated with the arg vars rebound to
;;; their respective gensym vars.  It may use reusable gensyms.

;;; See avoiding-variable-capture (in the module UTILITIES3) which offers this
;;; functionality, as well as the ability to avoid unneeded gensyms in certain
;;; cases.

;;; With-gensyms-for-args simplifies a common pattern of macro
;;; definition.  Thus, instead of the definition
;;;
;;;    (defmacro foo (x y z)
;;;      (let ((x-var (gensym))
;;;               (y-var (gensym)))
;;;           `(let ((,x-var ,x)
;;;                  (,y-var ,y))
;;;              <body in terms of ,x-var ,y-var and ,z)))
;;;
;;; one can write
;;;
;;;    (defmacro foo (x y z)
;;;      (with-gensyms-for-args (x y z)
;;;           <body in terms of ,x ,y and ,z)).

(defmacro with-gensyms-for-args (arg-vars &body body)
  ;; (with-gensyms-for-args (x y z) `(bar ,x ,y ,z))
  ;; (defmacro bar (x y z) (with-gensyms-for-args (x y z) `(list ,x ,y ,z)))
  ;; (bar a b c)
  ;; (bar a (car b) (car c))
  (let ((gensyms
          (loop for l on arg-vars
                collect (gensym-gensym))))        ; Change to use Gensym-make-symbol!
    `(let ,(loop for gensym in gensyms
                 collect `(,gensym (gensym-gensym)))        ; Change to use Gensym-make-symbol!
       (list 'let                                ; use ` for this?
             (list . ,(loop for gensym in gensyms
                            as arg-var in arg-vars
                            collect `(list ,gensym ,arg-var)))
             (let ,(loop for gensym in gensyms
                         as arg-var in arg-vars
                         collect `(,arg-var ,gensym))
               . ,body)))))

;; Note that this uses gensym-gensym, which is defined later in this module.


(defmacro with-make-symbols-for-args (arg-vars &body body)
  ;; (with-make-symbols-for-args (x y z) `(list ,x ,y ,z))
  ;; (defmacro foo (x y z) (with-make-symbols-for-args (x y z) `(list ,x ,y ,z)))
  ;; (foo a b c)
  ;; (foo a (car b) (car c))
  (let ((gensyms
          (loop for l in arg-vars
                collect (gensym-make-symbol l))))
    `(let ,(loop for gensym in gensyms
                 as l in arg-vars
                 collect `(,gensym (gensym-make-symbol ',l)))
       (list 'let                                ; use ` for this?
             (list . ,(loop for gensym in gensyms
                            as arg-var in arg-vars
                            collect `(list ,gensym ,arg-var)))
             (let ,(loop for gensym in gensyms
                         as arg-var in arg-vars
                         collect `(,arg-var ,gensym))
               . ,body)))))



;; See also Build-symbol in "Basic Macros" below



(defun-for-macro note-defun-resumable-icp-function (name &optional (value t))
  (setf (get name 'resumable-icp-form) value))

(defun-for-macro function-call-macro-p (symbol)
  (and (symbolp symbol)
       (or (get symbol 'function-call-macro)
           (get symbol 'function-call-accessor-macro))))

(defun-for-macro function-call-accessor-macro-p (symbol)
  (and (symbolp symbol)
       (get symbol 'function-call-accessor-macro)))

(defun-for-macro note-function-call-macro-1 (&rest macro-names)
  (loop for name in macro-names
        do (setf (get name 'function-call-macro) t))
  macro-names)

(defun-for-macro note-non-resumable-function-call-macro-1 (&rest macro-names)
  (apply #'note-function-call-macro-1 macro-names)
  (loop for name in macro-names
        do (note-defun-resumable-icp-function name nil))
  macro-names)

(defmacro note-function-call-macro (&rest macro-names)
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     ,@(unless (eval-feature ':no-macros)
         `((note-function-call-macro-1 ,@macro-names)))))

(defmacro note-non-resumable-function-call-macro (&rest macro-names)
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     ,@(unless (eval-feature ':no-macros)
         `((note-non-resumable-function-call-macro-1 ,@macro-names)))))

(defun-for-macro note-function-call-accessor-macro-1 (&rest macro-names)
  (loop for name in macro-names
        do (setf (get name 'function-call-accessor-macro) t))
  macro-names)

(defmacro note-function-call-accessor-macro (&rest macro-names)
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     ,@(unless (eval-feature ':no-macros)
         `((note-function-call-accessor-macro-1 ,@macro-names)))))



;;; `Def-substitution-macro' is like defun except that (1) it defines a macro,
;;; (2) the lambda list must be just a list of variables, and (3) it produces
;;; the macro expansion using expand-by-substituting-args-if-all-trivial (see
;;; below).

;;; `Def-substitution-macro-with-computed-body-form' is like
;;; def-substitution-macro except that the "body", after any declarations and
;;; documentation strings, must consist of a single form that will be evaluated
;;; to be the form to substitute into.

;;; `Substitution macros' are macros that work, in the "trivial" case where all
;;; args are atoms or quote forms, by substituting args for corresponding macro
;;; variables wherever they occur in a form, or else by constructing a let form
;;; that binds each of the macro variables to its corresponding arg.
;;; Therefore, for maximal efficiency, substitution macros should be invoked
;;; with only atomic and quoted args.  Substitution macros are typically
;;; defined by means of def-substitution-macro and
;;; def-substitution-macro-with-computed-body-form; see below.

;;; Expand-by-substituting-args-if-all-trivial produces a macro expansion as
;;; follows:  if all the args are trivial, it substitutes args for the
;;; corresponding macro variables wherever they occur in form; otherwise, it
;;; constructs a let form, with form as the body, that binds each of the
;;; macro-variables to its corresponding arg.  Substitution is pervasive in
;;; form except within quote forms.

;;; An argument is trivial if it is either an atom or a quote form.  The macro
;;; variables should not be &rest or &body variables (or the like).  Note that
;;; the macro-variables argument of expand-by-substituting-args-if-all-trivial
;;; is not evaluated.

;;;   `Legal-substitution-macro' is a utility function used by the substitution
;;;   macros.  It checks that the body is absolutly safe given our extremely
;;;   stupid code walker.  For example: (def-substitution-macro listify (list)
;;;   (list list)) will do (listify x) to expand to (x x).  To avoid this we
;;;   preclude any of the arguments appearing as the first symbol in a list.
;;;   That of course causes preempts a lot of useful constructs. "Safety first."

#+safer-substitution-macros
(defun-for-macro legal-substitution-macro-p (variables body)
  (loop for form in body
        always (legal-substitution-macro-p-1 variables form)))

#+safer-substitution-macros
(defun-for-macro legal-substitution-macro-p-1 (variables body)
  (typecase body
    (atom t)
    (cons
     (or (eql (car body) 'quote)
         (if (member (car body) variables)
             nil
             (loop for tail on (rest body)
                   when (atom tail) do (return t)
                   unless (legal-substitution-macro-p-1 variables (car tail))
                     do (return nil)
                   finally (return t)))))))

(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro def-substitution-macro
    (name variables &body body)
  #+safer-substitution-macros
  (unless (legal-substitution-macro-p variables body)
    (warn "Illegal body (see legal-substitution-macro) in def-substitution-macro ~S"
          name))
  (loop for rest-of-body on body
        while
        (or (if (not (atom (car rest-of-body)))
                (eq (caar rest-of-body) 'declare))
            (stringp (car rest-of-body)))
        collect (car rest-of-body) into declarations-and-documentation
        finally
          (return
            `(progn
              #+safer-substitution-macros
              (defun-for-macro
                  ,(intern
                    (format
                     nil
                     "UNUSED-FUNCTION-TO-VALIDATE-SUBSTITUTION-MACRO-IS-FUNCTION-LIKE-FOR-~S"
                     name))
                  (,@variables)
                ,@body)
              ,@(unless (eval-feature :no-macros)
                  `((note-function-call-macro ',name)))
              (defmacro ,name ,variables
                ,@declarations-and-documentation
                (expand-by-substituting-args-if-all-trivial
                 ,variables
                 ',(if (cdr rest-of-body)
                       `(progn . ,rest-of-body)
                       (car rest-of-body))))))))

(defmacro def-substitution-macro-with-computed-body-form
          (name variables &body body)
  (loop for rest-of-body on body
        while
          (or (if (not (atom (car rest-of-body)))
                  (eq (caar rest-of-body) 'declare))
              (stringp (car rest-of-body)))
        collect (car rest-of-body) into declarations-and-documentation
        finally
          (return
            `(defmacro ,name ,variables
               ,@declarations-and-documentation
               (expand-by-substituting-args-if-all-trivial
                 ,variables
                 . ,rest-of-body)))))

(defmacro expand-by-substituting-args-if-all-trivial
          (macro-variables form)
  `(substitute-args-if-all-trivial
     ',macro-variables
     (list . ,macro-variables) ,form))

(defun-for-macro substitute-args-if-all-trivial (variables args form)
  (if (loop for arg in args
            always (or (atom arg) (eq (car arg) 'quote)))
      (substitute-args form variables args nil)
      `(let ,(loop for variable in variables
                   as arg in args
                   collect `(,variable ,arg))
         ,form)))

(defun-for-macro substitute-args (form-or-tail variables args tail-case?)
  (cond
    ((atom form-or-tail)
     (if (or tail-case? (not (symbolp form-or-tail)))
         form-or-tail
         (let ((arg-index? (position form-or-tail variables)))
           (if arg-index?
               (nth arg-index? args)
               form-or-tail))))
    ((and (not tail-case?) (eq (car form-or-tail) 'quote))
     form-or-tail)
    (t (let ((result-for-car
              (substitute-args (car form-or-tail) variables args nil))
             (result-for-cdr
              (substitute-args (cdr form-or-tail) variables args t)))
         (if (and (eq result-for-car (car form-or-tail))
                  (eq result-for-cdr (cdr form-or-tail)))
             form-or-tail
             (cons result-for-car result-for-cdr))))))

)



;;; The macro `defun-keyword-macro' defines a macro which allows constant
;;; keyword arguments, and expands into a call to an internal function which
;;; takes only required arguments.

;;; **Note**: Default values for optional and keyword arguments may not depend
;;; on the values of earlier arguments.  Defaults are evaluated in the CALLER's
;;; not the callee's environment.  Supplied-p and alternate keyword names are
;;; NOT handled.

(defmacro defun-allowing-keywords (name lambda-list &body body)
  (let* ((function-name (intern (format nil "~a-FUNCTION" name)))
         (argument-names (loop for element in lambda-list
                               unless (memq-function element lambda-list-keywords)
                                 collect (if (consp element) (car element) element)))
         (macro-lambda-list (loop for element in lambda-list
                                  if (atom element)
                                    collect element
                                  else
                                    collect (list (car element)
                                                  `',(cadr element)))))
    `(progn
       (defun ,function-name (,@argument-names)
         ,@body)
       (defmacro ,name ,macro-lambda-list
         `(,',function-name ,,@argument-names)))))

;; Chestnut should do (a better version of) this for us.  -fmw, 9/21/93



;;; The macro `defun-substitution-macro' expands to
;;; a defmacro which references a function (which has a different
;;; name) in development and to a def-substitution-macro for non-
;;; development compiles.

(defmacro defun-substitution-macro (name variables &body body)
  "Expands to a defmacro and a defun if :development is in *features*.
The defmacro expands to a function call to the defun, which is named
differently (<name>-FOR-DEVELOPMENT) from the defmacro.  Otherwise it
expands to a def-substitution-macro.  You should ensure that this
macro/function is called only once, and that it is defined before it is
called."
  (cond
    ((eval-feature :development)
     (let* ((development-function-name
              (intern
                (format nil "~a-FOR-DEVELOPMENT" name))))
       `(progn
          ,@(unless (eval-feature :no-macros)
              `((note-function-call-macro ',name)))
          (defmacro ,name ,variables
            (list ',development-function-name ,@variables))
          (defun ,development-function-name ,variables
            ,@body))))
    (t
     `(def-substitution-macro ,name ,variables
        ,@body))))



;;; The macro `defconstant-for-macro' expands to a defparameter in
;;; development compiles, defconstant in macro compiles, and
;;; nil otherwise.

(defmacro defconstant-for-macro (variable initial-value)
  (cond
    ((eval-feature :development)
     `(eval-when (:compile-toplevel :load-toplevel :execute)
        (defparameter ,variable ,initial-value)))
    ((not (eval-feature :no-macros))
     `(defconstant ,variable ,initial-value))
    (t nil)))

;; Changed defconstant-for-macro to place its binding in the compilation
;; environment even when it defines a parameter and not a constant.  jh,
;; 3/29/91.

;; Consider wrapping eval-when (:compile-toplevel :load-toplevel :execute)
;; around the defconstant expansion in the second cond-clause too.  This would
;; enable us to define constants for macros which could be used in #.  contexts
;; without the ubiquitous and annoying eval-when (:compile-toplevel
;; :load-toplevel :execute) wrapper around each group of such constants.  We
;; won't do this now because I seem to recall that Symbolics has a strange model
;; for the defconstant compilation environment which would make this not work.
;; Although Symbolics is not supported anymore, there is a chance that some Lisp
;; will come along with the same strange model, so using an eval-when around the
;; defconstant needs more thought.  jh, 7/30/91.

;;; The macro `defconstant-for-case' always expands into a defconstant, but
;;; wraps the definition in eval-when, just as jh's sixteen-year-old comment
;;; above suggested.  Not sure about the name: the idea is that it can be used
;;; in a case statement in the same file, with "#.".  We could change the name
;;; if someone comes up with a better one.  -jv, 7/30/07

(defmacro defconstant-for-case (variable initial-value)
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     (defconstant ,variable ,initial-value)))


;;; The macro `defmacro-for-constant' defines a defconstant-for-macro
;;; and a macro (both with the same name).  The macro expands to
;;; a reference to the constant/parameter during development and macro
;;; compiles (so its value is not hardwired into compiled code) and
;;; to the eval'ed value of the constant/parameter in distribution
;;; compiles.

(defmacro defmacro-for-constant (variable-and-macro-name initial-value)
  `(progn
     (eval-when (:compile-toplevel :load-toplevel :execute)
       (defconstant-for-macro ,variable-and-macro-name ,initial-value))
     (defmacro ,variable-and-macro-name ()
       (if (eval-feature :no-macros)
           ,(if (consp initial-value)
                `(list 'quote ,variable-and-macro-name)
                `,variable-and-macro-name)
           ',variable-and-macro-name))))




;;; `Temporary-progn' is used to insert temporary code.  The macro's arguments
;;; are:

;;;   (expiration-month expiration-day expiration-year
;;;     &optional message-string)
;;;     &body body

;;; After this date the compiler on all platforms will start complaining that
;;; the form has "expired." The date and message string should be constants.

;; - ben 6/28/91

(defmacro temporary-progn
    ((expiration-month expiration-day expiration-year &optional message-string)
     &body body)
  (when (< (encode-universal-time
             0 0 0 expiration-day expiration-month expiration-year)
           (get-universal-time))
    (if message-string
        (warn "Temporary-progn has expired, please remove. ~%~
               ~2tIt is labeled: ~S"
              message-string)
        (warn "A temporary-progn has expired, please remove")))
  `(progn
     ,@body))



;;; `Expiring-progn' - is like a "timebomb" demo feature.  It checks, at
;;; runtime, the current time and date, and turns off the code inside the body
;;; when it is later than the given time.  Since this runs in distribution
;;; code, we use the gensym version of the time functions.  For similarity
;;; to temporary-progn, I put the month before the day, even though they
;;; are in the opposite order in gensym-encode-unix-time.

(defmacro expiring-progn
    ((expiration-month expiration-day expiration-year)
     &body body)
  `(when (< (gensym-get-unix-time)
            (gensym-encode-unix-time 0 0 0
                                     ,expiration-day
                                     ,expiration-month
                                     ,expiration-year))
      ,@body))



;;; `lambda-lists-conform-p' ...

(defun-for-macro lambda-lists-conform-p
                 (lambda-list-1 lambda-list-2)
  ;; jh, 9/12/91.  Eventually we should do a more elaborate, CLOS-like
  ;; conformity test here.
  (and (not (intersection lambda-list-1 lambda-list-keywords))
       (not (intersection lambda-list-2 lambda-list-keywords))
       (= (length lambda-list-1) (length lambda-list-2))))



;;; `Congruent-lambda-list-p' is used to check if a method's lambda list is well
;;; formed given the lambda list specified in a generic method declaration.
;;; This currently means that the lambda lists are the same length and make no
;;; use of lambda list keywords.  That is a subset of the definition of
;;; congurent used in CLOS.

(defun-for-macro congruent-lambda-list-p
    (specified-lambda-list implementation-lambda-list)
  (block this-predicate

    (unless (= (length specified-lambda-list)
               (length implementation-lambda-list))
      (return-from this-predicate nil))

    (loop for specified-argument in specified-lambda-list
          as implemented-argument in implementation-lambda-list
          do
      (cond
        ((memq-function specified-argument lambda-list-keywords)
         (warn "Congruent-lambda-list-p does not support lambda list keywords other than &optional")
         (return-from this-predicate nil))
        ((member implemented-argument lambda-list-keywords)
         (warn "Congruent-lambda-list-p can not check lambda list keywords other ")
         (return-from this-predicate nil))
        )
          finally (return-from this-predicate t))))

;; The current definition of a congruent lambda list happens to additionally
;; ensure that the functions are "simple," i.e. that in chestnut you can use
;; funcall-simple-compile-function, which is significantly faster than funcall.
;; - ben Aug/25/93







;;;; Format-symbol




;;; Format-symbol takes a format control-string and args and returns the result
;;; as a symbol interned in the current package (the value *package*).  This
;;; function is primarily to be used in the development compile-time
;;; environment, especially for macro expansion.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun format-symbol (control-string &rest args)
    (declare (eliminate-for-no-macros-gsi))
    (intern (apply (lisp-format) nil control-string args))))

;; Fix this to not use &rest, which may cons, by having a limited number
;; of optional args instead!

;; Fix this to not "leak" strings, by reclaiming the generated string when
;; it is not incorporated into the resultant symbol.  See intern-text-string
;; in module UTILITIES3!






;;;; Unboxed Expression Trees




;;; Within the current port to Chestnut's Lisp translator, they do not pay
;;; attention to and optimize type declared arithmatic.  They have plans to do
;;; this under a project they call type heeding.  We are currently implementing
;;; fast arithmatic within G2 by directly calling primitive numeric operations
;;; that they have supplied to us.  There is a set of operations for fixnum
;;; arithmatic, a set for double-float arithmatic, and a set for unboxed double
;;; float arithmatic.  There are some complexities within the attempt to use to
;;; unboxed double float arithmatic, in that the sub-parts of expressions
;;; emitted which use these operators must not be temporarily cached in local
;;; variables.  Chestnut does these cachings to guarantee left to right
;;; evaluation of arguments when there are possible side-effects of the
;;; operations being carried out.  The code here is used to determine when an
;;; expression tree will or will not be emitted with temping of intermediate
;;; results.  This is a conservative implementation which will return false
;;; negatives on some expressions which will not have any temping, but it
;;; returns no false positives on expressions which could do temping.

;;; The allowable subparts of expressions include functions which are
;;; side-effect free, macros which do not emit any LET statements and are
;;; side-effect free, references to variables, and constants.  Since there are
;;; currently no declaration forms which already reflect which macros will not
;;; temp their arguments, I will simply make lists of the operations which are
;;; known to be OK.

;;; Note that there is an additional important special case.  ASHF cannot in
;;; general be trusted to not temp its arguments, but it can be trusted when its
;;; shift argument is a constant.  This test will be inlined directly in this
;;; function.

;;; Another special case is managed-float-aref when the first argument is a
;;; symbol and the second argument is either a symbol or a call to car-of-cons
;;; on some symbol.

;;; The variable for macro `non-temping-side-effect-free-macros' contains a list
;;; of symbols which name macros that can be trusted to not introduce LET
;;; bindings in their expansion and which are side-effect free.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar-for-macro
  non-temping-side-effect-free-macros
  '(+f -f *f halff twicef logandf logandc2f logxorf logiorf modf
       +w -w *w absw
       +r -r *r absr
       +i -i *i absi
       1+e 1-e +e -e *e /e abse loge atane cose expe expte minuspe pluspe sine
       sqrte tane ffloore-first floore-first
       + - * /
       svref car-of-cons cdr-of-cons
       managed-float-array-buffer
       float-vector-aref managed-float-aref managed-float-value
       cached-float-vector-aref cached-managed-float-aref cached-managed-float-value
       if the coerce-to-gensym-float coerce-fixnum-to-gensym-float
       coerce-to-gensym-long coerce-fixnum-to-gensym-long
       evaluation-float-value evaluation-integer-value evaluation-long-value
       phrase-float-value slot-value-float-value)))




;;; The function for macro `non-temping-side-effect-free-expression-p' takes an
;;; expression and returns whether or not it meets the criteria given above for
;;; expressions which do not cause local var temping of their intermediate
;;; values and which are side-effect free.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defun-for-macro simple-argument-p (form)
  (or (symbolp form) (constantp form)
      (and (consp form)
           (eq (car form) 'the)
           (simple-argument-p (caddr form)))))

(defun-for-macro non-temping-side-effect-free-expression-p (expression)
  (or (simple-argument-p expression)
      (and (consp expression)
           (let ((operation (car expression)))
             (when (symbolp operation)
               (cond
                 ((eq operation 'ashf)
                  (and (non-temping-side-effect-free-expression-p
                         (second expression))
                       (constantp (third expression))))
                 ((eq operation 'managed-float-aref)
                  (let ((float-vector (second expression))
                        (index (third expression)))
                    (and (symbolp float-vector)
                         (or (symbolp index)
                             (and (consp index)
                                  (eq (car index) 'car-of-cons)
                                  (consp (cdr index))
                                  (symbolp (second index)))))))
                 (t
                  (when (or (member                ; No memq yet.
                              operation non-temping-side-effect-free-macros
                              :test #'eq)
                            ;; jh, 1/29/93.  Need to ask Chestnut if the
                            ;; following will still work in rev 3.1.
                            #+(or chestnut chestnut-3)        ;Chestnut3.1
                            (get operation 'trans::no-side-effects-p))
                    (loop for argument-cons = (cdr expression)
                                            then (cdr argument-cons)
                          until (null argument-cons)
                          always
                            (and (consp argument-cons)
                                 (non-temping-side-effect-free-expression-p
                                   (car argument-cons)))))))))))))






;;;; Type Declaration Macros




;;; The following macros are used to implement the fixnum arithmetic and
;;; floating point arithmetic type declared operations.

;;; The function `expand-type-preserving-numeric-operation' takes a type, an
;;; operation, and an argument list and will emit code with all arguments to
;;; the form and all intermediate results of the form type declared using the
;;; THE special form.  This macro is for declaring numeric operations like +.
;;; Note that it will not work for operations like =, whose intermediate
;;; results are not of the same type as the arguments.  Also note that this
;;; macro will signal an error if passed a null argument list, since it does
;;; not know what the identities are of the set of operations that may be
;;; passed in.  If there is one argument, it will type declare the argument and
;;; the result.  If there are two arguments, it will type declare those
;;; arguments, combine them with the operator, and declare the result.  With 3
;;; or more arguments, it will expand into a series of type declared calls to
;;; the operator, maintaining left to right argument evaluation and left to
;;; right combination, combining only two values at a time.  These combinations
;;; will not bottom out into any one argument calls to the operation.

;;; In order to use the raw-double operations supplied to us by Chestnut, this
;;; macro has been extended.  When the type of the operation is gensym-float,
;;; there is a raw-double operator for this operation, and at least one of the
;;; arguments to this operation is itself able to return a raw-double, then this
;;; macro wil convert this operation over into a call to the raw-double
;;; operator.  Also, if the type of the operation given is already raw-double,
;;; then this macro will not wrap the arguments with raw-double declarations.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defun-for-macro declare-type-preserving-numeric-operation-1
    (type operation args)
  (declare-result
   type
   (cond
     ((null (cdr args))
      `(,(primitive-numeric-operator operation type)
         ,(declare-result type (first args))))
     ((null (cddr args))
      `(,(primitive-numeric-operator operation type)
         ,(declare-result type (first args))
         ,(declare-result type (second args))))
     (t
      `(,(primitive-numeric-operator operation type)
         ,(declare-type-preserving-numeric-operation-1
           type operation (butlast args))
         ,(declare-result type (car (last args))))))))

(defun-for-macro declare-type-preserving-numeric-operation
                 (type operation args &optional env)
  (when (eq type 'gensym-float)
    (setq type (gensym-float-type)))
  (cond
    ((null args)
     (error "Numeric type wrapper called with no arguments."))
    ;; If the type is T or raw-double, just split it up into binary
    ;; operations.
    ((or (eq type t) (eq type 'raw-double))
     (if (null (cddr args))
         `(,(primitive-numeric-operator operation type)
           ,@args)
         `(,(primitive-numeric-operator operation type)
           ,(declare-type-preserving-numeric-operation
              type operation (butlast args))
           ,(car (last args)))))
    ;; Otherwise, emit type declarations as normal.
    ((and (eval-feature :chestnut-trans)
          (loop for argument in args
                thereis (argument-needs-binding argument env)))
      (loop for arg in args
            for variable = (gensym)
            collect variable into arg-values
            collect `(,variable ,arg) into bindings
            finally
              (return `(let ,bindings
                         (declare (type ,type ,@arg-values))
                         ,(declare-type-preserving-numeric-operation-1
                            type operation arg-values)))))
    (t
     (declare-type-preserving-numeric-operation-1 type operation args))))
)





;;; The functions `declare-argument-types', `declare-argument-and-result-types',
;;; and `declare-result' all takes a type and a form and perform the described
;;; type declarations on the form.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro declare-argument-types-1 (type form)
  (let ((operator (car form)))
    (when (eq type 'gensym-float)
      (setq type (gensym-float-type)))
    (cond
      ((eq type 'raw-double)
       `(,(primitive-numeric-operator operator type)
         ,@(cdr form)))
      (t
       (cons (primitive-numeric-operator (first form) type)
             (loop for argument in (cdr form)
                   collect (declare-result type argument)))))))

(defun-for-macro argument-needs-binding (form env)
  (and (consp form)
       (or (consp (car form))
           (case (car form)
             (the (argument-needs-binding (caddr form) env))
             ((ab-lisp::if ab-lisp::cond ab-lisp::case ab-lisp::let
               ab-lisp::block ab-lisp::tagbody ab-lisp::or)
              t)
             (t (multiple-value-bind (form expandedp)
                    (macroexpand-1 form env)
                  (and expandedp
                       (argument-needs-binding
                         form env))))))))

(defun-for-macro declare-argument-types (type form &optional env)
  (if (and (eval-feature :chestnut-trans)
           (loop for argument in (cdr form)
                 thereis (argument-needs-binding argument env)))
      (loop for arg in (cdr form)
            for variable = (gensym)
            collect variable into arg-values
            collect `(,variable ,arg) into bindings
            finally
              (return `(let ,bindings
                         (declare (type ,type ,@arg-values))
                         ,(declare-argument-types-1
                            type
                            `(,(car form) ,@arg-values)))))
      (declare-argument-types-1 type form)))

)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro declare-argument-and-result-types-1 (type-arg form)
  (let* ((type (if (eq type-arg 'gensym-float)
                   (gensym-float-type)
                   type-arg))
         (operator (car form))
         (args (cdr form)))
    (cond
      ((eq type 'raw-double)
       `(,(primitive-numeric-operator operator type)
         ,@(loop for arg in args
                 collect (declare-result type arg))))
      #+development
      ((not (eq type 't)) ; (eq type 'fixnum)
       `(check-type-for-development
         (,(primitive-numeric-operator operator type)
           ,@(loop for arg in args
                   collect (declare-result type arg)))
         ',type))
      (t `(the ,type
               (,(primitive-numeric-operator operator type)
                ,@(loop for arg in args
                        collect (declare-result type arg))))))))

(defun-for-macro declare-argument-and-result-types (type-arg form &optional env)
  (if (and (eval-feature :chestnut-trans)
           (loop for argument in (cdr form)
                 thereis (argument-needs-binding argument env)))
      (loop for arg in (cdr form)
            for variable = (gensym)
            collect variable into arg-values
            collect `(,variable ,arg) into bindings
            finally
              (return `(let ,bindings
                         (declare (type ,type-arg ,@arg-values))
                         ,(declare-argument-and-result-types-1
                            type-arg
                            `(,(car form) ,@arg-values)))))
      (declare-argument-and-result-types-1 type-arg form)))

)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar-for-macro
  fixnum-returning-operations
  '(+f -f *f minf maxf absf halff twicef logandf logandc2f logxorf
       logiorf ashf modf
       +w -w *w minw maxw absw
       +r -r *r minr maxr absr
       +i -i *i mini maxi absi)))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar-for-macro
  gensym-float-returning-operations
  '(1+e 1-e +e -e *e /e mine maxe abse loge atane cose expe expte sine
        sqrte tane)))




;;; The function for macro `declare-result' wraps a "the type" form around the
;;; given form.  It does one optimization, that if the form is already declared,
;;; or if the form is one of a few known forms which declare the type, it will
;;; decline to wrap its form argument.  This is a compile time optimization to
;;; avoid redundant type wrappers.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro declare-result (type form)
  (when (eq type 'gensym-float)
    (setq type (gensym-float-type)))
  (cond ((eq type 'raw-double)
         form)
        #+development
        ((not (eq type 't)) ;(eq type 'fixnum)
         `(check-type-for-development
           ,form
           ',type))
        ((and (consp form)
              (or (and (eq (car form) 'the)
                       (consp (cdr form))
                       (eq (cadr form) type))
                  (and (eq type 'fixnum)
                       (member (car form) fixnum-returning-operations))
                  (and (eq type (gensym-float-type))
                       (member (car form) gensym-float-returning-operations))))
         form)
        ((and (consp form)
              (eq (car form) 'setq)
              (= (length form) 3))
         `(setq ,(second form) (the ,type ,(third form))))
        (t (list 'the type form)))))

;; jh, 3/12/93.  Due to a bug in Lucid, we must evert the variable from inside a
;; setq form handed to declare-result.  Otherwise, we get a strange warning
;; complaining that the variable FIXNUM is assumed special.  Here is a simple
;; example:
;;(defun unjustifiable-complaint (exponent most-righthand-float-zeros)
;;  (let (cond-temporary-1)
;;    (cond ((> (the fixnum (setq cond-temporary-1 exponent))
;;                most-righthand-float-zeros)
;;             (values 'underflow nil))
;;            ((> cond-temporary-1 12)
;;           (values 'overflow t)))))

;;; The function for macro `fixnum-returning-expression-p' takes an expression
;;; and returns whether or not it can prove that the expression returns fixnums.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro fixnum-returning-expression-p (expression)
  (or (and (constantp expression)
           (typep (eval expression) 'fixnum))
      (and (consp expression)
           (symbolp (car expression))
           (or (member (car expression)
                       fixnum-returning-operations
                       :test #'eq)
               (and (eq (car expression) 'the)
                    (consp (cdr expression))
                    (eq (second expression) 'fixnum)))))))




;;; The constant for macro `chestnut-fixnum-operations' contains an alist of
;;; Lisp numeric operators to primitive implementations of those fixnum
;;; operators.  This list is used in the function primitive-numeric-operator to
;;; find appropriate primitive operations for unoptimized Lisp numerics.

;;; Note that the following operations have been left out of the alist since we
;;; do not have fixnum macros for them (or else I don't know what they are):
;;; %pointer, %sysint, D>%, D>=%, DEF%, EVENP%, FLOOR% (doesn't return two
;;; values), LOGEQV%, and LSH%.

#+chestnut
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter-for-macro chestnut-fixnum-operations
  '((1+ . trans::1+%)
    (1- . trans::1-%)
    (* . trans::*%)
    (+ . trans::+%)
    (- . trans::-%)
    (/= . trans::/=%)
    (< . trans::<%)
    (<= . trans::<=%)
    (= . trans::=%)
    (> . trans::>%)
    (>= . trans::>=%)
    (abs . trans::abs%)
    (ash . trans::ash%)
    (left-shift . trans::lsh%)
    (right-shift . trans::rsh%)
    (floor-positive . trans::/%)
    (mod-positive . trans::rem%)
    (decf . trans::decf%)
    (incf . trans::incf%)
    (logand . trans::logand%)
    (logandc2 . trans::logandc2%)
    (logior . trans::logior%)
    (lognot . trans::lognot%)
    (logxor . trans::logxor%)
    (max . trans::max%)
    (min . trans::min%)
    (minusp . trans::minusp%)
    (mod . trans::mod%)
    (plusp . trans::plusp%)
    (truncate . trans::truncate%)
    (zerop . trans::zerop%))))




;;; `obliterate-function' removes all knowledge of a function definition.
;;; Well, not really.  Maybe it did that in Lucid 4.1.  In Lucid 5.0, as
;;; well as SBCL, Allegro, etc., all it does is fmakunbound.  But that's
;;; something, I guess.  -jv, 12/14/07

(defun-for-macro obliterate-function (name)
  (when (fboundp name)
    (fmakunbound name))
  #+(and lucid (not translator) (not lcl5.0))
  (let* ((list (gethash name LUCID::*SOURCE-FILE-HASHTABLE*))
         (fun (assoc 'function list))
         (mac (assoc 'lcl:macro list)))
    (when (or fun mac)
      (setf (gethash name LUCID::*SOURCE-FILE-HASHTABLE*)
            (remove fun (remove mac list))))
    list))



;;; The following function definitions are temporary bug fixes for Chestnut
;;; translator problems.  The translator should provide defintions (in Lucid)
;;; for all of the % operators listed above.  Those which are not defined by
;;; Chestnut have been defined below to get us past the bug.  -jra & ac 1/16/91

#+(and chestnut (not no-macros))
(progn
(obliterate-function 'trans::abs%)
(defun-for-macro trans::abs% (fixnum)
  (abs fixnum)))

;; In Chestnut 1.7, trans::abs% is incorrectly implemented.  We must make it
;; unbound before defining a new version to avoid redefinition warnings.  -jra
;; 8/5/93




;;; The constant for macro `chestnut-double-float-operations' contains an alist
;;; associating Common Lisp numeric operations with the symbols naming optimized
;;; versions for double-floats in Chestnut's translated Lisp.  Note that these
;;; operations take double float arguments and return double-float values, i.e.
;;; they cons at every intermediate value.

#+chestnut
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter-for-macro chestnut-double-float-operations
  '(
    (1+  . trun:1+%d)
    (1-  . trun:1-%d)
    (+   . trun:+%d)
    (-   . trun:-%d)
    (*   . trun:*%d)
    (/   . trun:/%d)
    (=   . trun:=%d)
    (/=  . trun:/=%d)
    (<   . trun:<%d)
    (>   . trun:>%d)
    (<=  . trun:<=%d)
    (>=  . trun:>=%d)

    (min . trun:min%d)
    (max . trun:max%d)
    (abs . trun:abs%d)
    ;; Can't use floor, ceiling, truncate or round, since we currently need
    ;; multiple values from these operations.  We should consider redefining
    ;; these operations to return only single values.  -jra 2/25/91
;      (floor    . trun:floor%d)
;      (ceiling  . trun:ceiling%d)
;      (truncate . trun:truncate%d)
;      (fround   . trun:fround%d)
    (log    . trun:log%d)
    (atan   . trun:atan%d)
    (cos    . trun:cos%d)
    (exp    . trun:exp%d)
    (expt   . trun:expt%d)
    (minusp . trun:minusp%d)
    (plusp  . trun:plusp%d)
    (sin    . trun:sin%d)
    (sqrt   . trun:sqrt%d)
    (tan    . trun:tan%d)
    )))




;;; The constant for macro `chestnut-raw-double-operations' contains an alist
;;; associating Common Lisp numeric operations with the symbols naming their
;;; optimized versions in Chestnut's translated Lisp which accept and return raw
;;; doubles in C as opposed to Lisp double floats.  Note that because these
;;; operators accept and return raw C doubles they are the best optimized
;;; operators available.  Our +e etc.  operators attempt to convert themselves
;;; over to these raw operations whenever they can.

#+chestnut
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter-for-macro chestnut-raw-double-operations
  '((1+  . trun:1+%rd)
    (1-  . trun:1-%rd)
    (+   . trun:+%rd)
    (-   . trun:-%rd)
    (*   . trun:*%rd)
    (/   . trun:/%rd)
    (=   . trun:=%rd)
    (/=  . trun:/=%rd)
    (<   . trun:<%rd)
    (>   . trun:>%rd)
    (<=  . trun:<=%rd)
    (>=  . trun:>=%rd)
;      (min . trun:min%rd)
;      (max . trun:max%rd)
    (abs           . trun:abs%rd)
    (floor-first   . trun:floor%rd)
    (ceiling-first . trun:ceiling%rd)
;      (truncate . trun:truncate%rd)
;      (fround   . trun:fround%rd)
    (ffloor-first  . inline-double-ffloor-1)
    (log           . trun:log%rd)
    (atan          . trun:atan%rd)
    ;; There is a bug in the translation of cos%rd, replacing it with
    ;; our own macro version of cos, inline-double-cos, defined in
    ;; gensym.h
;      (cos . trun:cos%rd)
    (cos    . inline-double-cos)
    (exp    . trun:exp%rd)
    (expt   . trun:expt%rd)
    (minusp . trun:minusp%rd)
    (plusp  . trun:plusp%rd)
    (sin    . trun:sin%rd)
    (sqrt   . trun:sqrt%rd)
    (tan    . trun:tan%rd) )))

;; We were unable to use the following primitive operations because we do not
;; have our own versions of them: trun:atan%rd, trun:cos%rd, trun:exp%rd,
;; trun:expt%rd, trun:minusp%d, trun:plusp%d, trun:sin%rd, and trun:tan%rd.
;; -jra 2/25/91

;; Can't use floor, ceiling, truncate or round, since we currently need multiple
;; values from these operations.  We should consider redefining these operations
;; to return only single values. -jra 2/25/92

;; Note that we cannot use the raw min and max operations.  Their macro
;; expansions in C use their arguments more than once.  To correctly translate
;; this code, temporary variables must be allocated for thier arguments.
;; However, since all temporaries in Chestnut are of type Object (4 bytes long)
;; instead of double (8 bytes long), temping cannot be done on raw values.  So,
;; we cannot use these operations.  -jra 1/25/92





;;; The function for macro `primitive-numeric-operator' takes a symbol naming an
;;; arithmetic operation and a symbol naming a numeric type (either fixnum,
;;; gensym-float, the gensym-float-type, or raw-double) and returns the symbol
;;; which implements the primitive operation for that numeric operation.  If no
;;; further primitive operation exists, the original symbol is returned.

;;; This abstraction is needed to implement immediate fixnum and double float
;;; operations in Chestnut.  The Chestnut translator currently ignores numeric
;;; type declarations.  The listed operations are primitive accessors to fixnum
;;; implementations of the given operations.  For operations for which there
;;; are not fixnum optimized versions, or for any implementation other than the
;;; translator pass of the Chestnut translator, this function returns the
;;; original symbol.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro primitive-numeric-operator (operation type)
  #+chestnut
  (cond ((not (eval-feature :chestnut-trans))
         operation)
        ((eq type 'fixnum)
         (or (cdr (assoc operation chestnut-fixnum-operations))
             operation))
        ((or (eq type 'gensym-float) (eq type (gensym-float-type)))
         (or (cdr (assoc operation chestnut-double-float-operations))
             operation))
        ((eq type 'raw-double)
         (or (cdr (assoc operation chestnut-raw-double-operations))
             operation))
        (t operation))
  #-chestnut
  (declare (ignore type))
  #-chestnut
  operation))




;;; The function for macro `declare-comparitor' is used to do type declarations
;;; for numeric comparison operations.  The function for macro
;;; `declare-binary-compound-comparitors' is used to transform multi-argument
;;; comparisons into ANDs of sets of binary comparisons.  Common Lisp allows
;;; many comparitors to take more than two arguments, but our primitives for
;;; some systems (i.e.  Chestnut) can only optimize the two argument cases.  So,
;;; this function is used to split up operations into sets of binary
;;; comparisons.

;;; Calls to inline-nanp-for-comparison are now added to all float comparisons,
;;; to solve a problem with the MSDEV C compiler.
;;; See inline_nanp_for_comparison in rtl/c/gensym.h

(eval-when (:compile-toplevel :load-toplevel :execute)

(defun-for-macro declare-comparitor
                 (comparitor type arguments &optional env)
  (when (eq type 'gensym-float)
    (setq type (gensym-float-type)))
  (cond ((< (length arguments) 2)
         (declare-argument-types type `(,comparitor ,@arguments) env))
        ((or (eq type (gensym-float-type))
             (and (< 2 (length arguments))
                  (not (loop for argument in arguments
                             always (simple-argument-p argument)))))
         (loop for arg in arguments
               for variable = (make-symbol "ARG")
               collect variable into arg-values
               collect `(,variable ,arg) into bindings
               finally
                 (return `(let ,bindings
                            (declare (type ,type ,@arg-values))
                            (,(if (eq comparitor '/=) 'not 'progn)
                              (and ,@(declare-binary-compound-comparitors
                                      (if (eq comparitor '/=)
                                          '=
                                          comparitor)
                                      type arg-values)
                                   ,@(when (eq type (gensym-float-type))
                                       (loop for variable in arg-values
                                             collect `(not (inline-nanp-for-comparison ,variable))))))))))
        (t
         `(and ,@(declare-binary-compound-comparitors comparitor type arguments)))))

(defun-for-macro declare-binary-compound-comparitors (comparitor type arguments)
  (loop        for arguments on arguments
        until (null (cdr arguments))
        for arg1 = (first arguments)
        for arg2 = (second arguments)
        collect `(,(primitive-numeric-operator comparitor type)
                   ,(declare-result type arg1)
                   ,(declare-result type arg2))))

)



;;; The function for macro `typed-operator-for-type' takes a symbol naming a
;;; Common Lisp numeric operation and a symbol naming a numeric type.  The
;;; result is a symbol naming a type declared version of that operator for the
;;; given type.  This currently can return optimized operators for fixnums,
;;; gensym-floats, and whatever the specific gensym-float type is for a machine.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro typed-operator-for-type (operator type)
  (cond ((eq type 'fixnum)
         (fixnum-operator-for-operation operator))
        ((or (eq type 'gensym-float) (eq type (gensym-float-type)))
         (gensym-float-operator-for-operation operator))
        (t
         operator))))






;;;; Fixnum Arithmetic




;; Define most-positive-gensym-fixnum (after we abandon Common Lisp
;; implementations with fixnums shorter than 30 bits?), until we implement
;; managed bignums!

;;; The function for macro `fixnum-operator-for-operation' takes a symbol naming
;;; a generic Common Lisp numeric operator and returns a symbol naming a fixnum
;;; optimized version of the same operator.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter-for-macro fixnum-operator-alist
  `((1+ . 1+f)
    (1- . 1-f)
    (+ . +f)
    (- . -f)
    (* . *f)
    (= . =f)
    (/= . /=f)
    (< . <f)
    (> . >f)
    (<= . <=f)
    (>= . >=f)
    (minusp . minuspf)
    (plusp . pluspf)
    (min . minf)
    (max . maxf)
    (abs . absf)
    (floor . floorf)
    (ceiling . ceilingf)
    (truncate . truncatef)
    (round . roundf)
    (half . halff)
    (twice . twicef)
    (logand . logandf)
    (logandc2 . logandc2f)
    (logxor . logxorf)
    (logior . logiorf)
    (logbitp . logbitpf)
    (ash . ashf)
    (mod . modf)
    (incf . incff)
    (decf . decff)))

(defun-for-macro fixnum-operator-for-operation (operator)
  (or (cdr (assoc operator fixnum-operator-alist))
      operator)))




;;; `Fixnump' it true if x is a fixnum.

;; Is this sort of conditionalization really worth it?  A compiler
;; will translate (typep x 'fixnum) into a fast fixnum comparison.  If
;; this isn't happening, we've found a bug!  css - 05/09/01

(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro fixnump (x)
  (if (eval-feature :translator)
      `(typep ,x 'fixnum)
      #+(and allegro development)
      `(excl:fixnump ,x)
      #+(and lispworks development)
      `(lw:fixnump ,x) ; `(common-lisp:integerp ,x)
      #-(and (or allegro lispworks) development)
      `(typep ,x 'fixnum)))

) ; eval-when

(defconstant most-positive-fixnum32 #.(1- (expt 2 29)))
(defconstant most-negative-fixnum32 #.(- (expt 2 29)))

(defparameter most-positive-fixnum32-plus-one
  (1+ most-positive-fixnum32))

(def-substitution-macro 32bit-fixnump (x)
  (and (<= most-negative-fixnum32 x)
       (<= x most-positive-fixnum32)))

#+(and development lucid)
(proclaim '(optimize (compilation-speed 0))) ; cause TYPEP to be inlined

;; Note that fixnump is hacked to return true for any integer that would fit
;; within a signed 30 bit space.  This is true for all Lisp implementations we
;; use now, except for the TI and Symbolics.  The TI has 25 bit fixnums and the
;; Symbolics has 32 bit fixnums.  -jra




;;; A `fixnum arithmetic suite' includes the set of functions 1+f, 1-f, +f, -f,
;;; *f, =f, /=f, <f, >f, <=f, >=f, minuspf, pluspf, minf, maxf, absf, ashf,
;;; modf, logandf, logand2cf, logxorf, logiorf, logbitpf, incff, and decff,
;;; which are like 1+, 1-, +, -, =, /=, <, >, <=, >=, minusp, plusp, min, max,
;;; abs, ash, mod, logand, logand2c, logxor, logior, logbitp, incf, and decf,
;;; except that they take fixnum arguments and, in the case of all but the
;;; comparisons, produce fixnum values.  Note that the arguments of +f and -f
;;; must be such as to allow them to have fixnum values.  Halff computes the
;;; floor of half of fixnum.  Twicef twice the fixnum argument.

;;; Each fixnum arithmetic suite has a "suffix".  The `standard fixnum
;;; arithmetic suite' has the suffix "F".  Def-fixnum-arithmetic-system, below,
;;; takes a suffix and defines the suite for that suffix.

;;; Def-fixnum-arithmetic-system defines the fixnum arithmetic suite with same
;;; given above, exactly as with the normal fixnum arithmetic system, but with a
;;; different suffix than "F".  Suffix-for-arithmetic-system, which is a quoted
;;; arg, should be a symbol or a string.  If a string is provided, the string is
;;; handled case sensitively.  If a symbol is provided, the arg is turned into
;;; the symbol's print name and then handled the same as if it were a string.

;;; Fixnum arithmetic may not be used within forms that are evaluated at read-time.
;;; Instead, use generic arithmetic.  For example, #.(+ x y) should be written
;;; instead of #.(+f x y).

(defmacro def-fixnum-arithmetic-system (suffix-for-arithmetic-system
                                        &key lower-bound upper-bound)
  `(progn
     ,@(loop for (op . fixnum-op) in fixnum-operator-alist
             as rest-arglist-var = (format-symbol "ARGS-FOR-~a" op)
             as system-op = (format-symbol "~a~a" op suffix-for-arithmetic-system)
             as body = `(cons ',fixnum-op ,rest-arglist-var)

             ;; This defines the nullary version of min and max for system. See the
             ;; comment following "(def-fixnum-arithmetic-system w ...)" in primitives
             ;; for motivation as to why this is natural.
             do (cond ((and lower-bound (eq op 'max))
                       (setq body `(if (null ,rest-arglist-var) ',lower-bound ,body)))
                      ((and upper-bound (eq op 'min))
                       (setq body `(if (null ,rest-arglist-var) ',upper-bound ,body))))
             collect
               `(defmacro ,system-op (&rest ,rest-arglist-var)
                  ,body))))

;; Consider having this return something less random than DECFxxx.




(defmacro halff (fixnum)
  `(ashf ,fixnum -1))

(defmacro twicef (fixnum)
  `(ashf ,fixnum 1))

(defmacro 1+f (fixnum &environment env)
  (declare-argument-and-result-types 'fixnum `(1+ ,fixnum) env))

(defmacro 1-f (fixnum &environment env)
  (declare-argument-and-result-types 'fixnum `(1- ,fixnum) env))

;; See the comment above minf for the reason why arguments to +f are sometimes
;; rebound to gensyms.  -jra 5/2/91

(defmacro +f (&rest fixnums &environment env)
  (cond ((null fixnums)
         0)
        ((null (cdr fixnums))
         (declare-result 'fixnum (car fixnums)))
        (t
         (declare-type-preserving-numeric-operation 'fixnum '+ fixnums env))
;        ((loop for argument in fixnums
;               always (or (symbolp argument) (constantp argument)))
;         (declare-type-preserving-numeric-operation 'fixnum '+ fixnums))
;        (t
;         (loop for argument in fixnums
;               for bound-argument = (gensym)
;               collect `(,bound-argument ,argument) into bindings
;               collect bound-argument into new-arguments
;               finally
;                 (return
;                   `(let ,bindings
;                      ,(declare-type-preserving-numeric-operation
;                         'fixnum '+ new-arguments)))))
        ))



;;; The substitution macro `fixnum-vector-distance' takes two fixnums
;;; and returns the square root of the sum of the squares of the
;;; fixnums.

(def-substitution-macro fixnum-vector-distance (d1 d2)
  (the fixnum (isqrt (+f (*f d1 d1) (*f d2 d2)))))

;; See the comment above minf for the reason why arguments to -f are sometimes
;; rebound to gensyms.  -jra 5/2/91

(defmacro -f (fixnum &rest more-fixnums &environment env)
  (let ((fixnums (cons fixnum more-fixnums)))
    (declare-type-preserving-numeric-operation 'fixnum '- fixnums env)))



;; See the comment above minf for the reason why arguments to *f are sometimes
;; rebound to gensyms.  -jra 5/2/91

(defmacro *f (&rest fixnums &environment env)
  (cond ((null fixnums)
         1)
        (t
         (declare-type-preserving-numeric-operation 'fixnum '* fixnums env))
;        ((loop for argument in fixnums
;               always (or (symbolp argument) (constantp argument)))
;         (declare-type-preserving-numeric-operation 'fixnum '* fixnums))
;        (t
;         (loop for argument in fixnums
;               for bound-argument = (gensym)
;               collect `(,bound-argument ,argument) into bindings
;               collect bound-argument into new-arguments
;               finally
;                 (return
;                   `(let ,bindings
;                      ,(declare-type-preserving-numeric-operation
;                         'fixnum '* new-arguments)))))
        ))

(defmacro =f (&rest fixnums &environment env)
  (declare-comparitor '= 'fixnum fixnums env))

(defmacro /=f (&rest fixnums &environment env)
  (declare-comparitor '/= 'fixnum fixnums env))

(defmacro <f (&rest fixnums &environment env)
  (declare-comparitor '< 'fixnum fixnums env))

(defmacro >f (&rest fixnums &environment env)
  (declare-comparitor '> 'fixnum fixnums env))

(defmacro <=f (&rest fixnums &environment env)
  (declare-comparitor '<= 'fixnum fixnums env))

(defmacro >=f (&rest fixnums &environment env)
  (declare-comparitor '>= 'fixnum fixnums env))

(defmacro minuspf (fixnum &environment env)
  (declare-argument-types 'fixnum `(minusp ,fixnum) env))

(defmacro pluspf (fixnum &environment env)
  (declare-argument-types 'fixnum `(plusp ,fixnum) env))

;; Within *f, minf, maxf, and ashf, there have been problems with the VAX and
;; 386 C compilers in situations where the Chestnut translator has cached
;; complex arguments into temporaries before dispatching to the actual in-lined
;; C macro, or where it has wrapped an execution of these with CALL_N.  The
;; technique Chestnut uses is the implicit progn C form

;;   (temp1=<arg1>,temp2=<arg2>,op(temp1,temp2))

;; Though this is perfectly good ANSI C, the VAX can't handle it.  As a
;; temporary solution, we will ensure that *f, minf, maxf, and ashf only take
;; arguments which Chestnut does not cache into temporaries, namely symbols and
;; constants.  Since Chesnut's implementation of LET explodes initializations of
;; variables into seperate statements, the implicit progn stuff won't get
;; emitted, and the VAX might compile.  -jra 5/1/91

;; We believe that Chestnut now handles this stuff correctly, by using explicit
;; temps in C translations instead of trying to finesse the issue with C comma
;; expressions.  The CALL_N form is gone from Chestnut, and we should start to
;; remove the workarounds we needed to avoid it.  -jra & jh 7/21/93

(defmacro minf (&rest fixnums &environment env)

  ;; The first clause defines (minf) => most-positive-fixnum. See the
  ;; comment following "(def-fixnum-arithmetic-system w ...)" in
  ;; primitives.lisp for motivation as to why this is natural.

  (cond ((null fixnums)
         'most-positive-fixnum)
        (t
         (declare-type-preserving-numeric-operation 'fixnum 'min fixnums env))
;        ((cddr fixnums)
;         `(minf (minf ,@(butlast fixnums)) ,(car (last fixnums))))
;        ((loop for argument in fixnums
;               always (or (symbolp argument) (constantp argument)))
;         (declare-type-preserving-numeric-operation 'fixnum 'min fixnums))
;        (t
;         (loop for argument in fixnums
;               for bound-argument = (gensym)
;               collect `(,bound-argument ,argument) into bindings
;               collect bound-argument into new-arguments
;               finally
;                 (return
;                   `(let ,bindings
;                      ,(declare-type-preserving-numeric-operation
;                         'fixnum 'min new-arguments)))))
        ))

;; See the comment near minf to explain the commented out code for gensymming
;; arguments.  -jra 7/21/93

(defmacro maxf (&rest fixnums &environment env)

  ;; The first clause defines (maxf) => most-negative-fixnum. See the
  ;; comment following "(def-fixnum-arithmetic-system w ...)" in
  ;; primitives.lisp for motivation as to why this is natural.

  (cond ((null fixnums)
         'most-negative-fixnum)
        (t
         (declare-type-preserving-numeric-operation 'fixnum 'max fixnums env))
;        ((cddr fixnums)
;         `(maxf (maxf ,@(butlast fixnums)) ,(car (last fixnums))))
;        ((loop for argument in fixnums
;               always (or (symbolp argument) (constantp argument)))
;         (declare-type-preserving-numeric-operation 'fixnum 'max fixnums))
;        (t
;         (loop for argument in fixnums
;               for bound-argument = (gensym)
;               collect `(,bound-argument ,argument) into bindings
;               collect bound-argument into new-arguments
;               finally
;                 (return
;                   `(let ,bindings
;                      ,(declare-type-preserving-numeric-operation
;                         'fixnum 'max new-arguments)))))
        ))

;;; `pin-in-rangef' does just that and is much more readable and dependable
;;; than the little tangle of max and min.

(defmacro pin-in-rangef (lower-bound x upper-bound)
  `(maxf ,lower-bound (minf ,x ,upper-bound)))


(defmacro absf (fixnum &environment env)
  (declare-argument-and-result-types 'fixnum `(abs ,fixnum) env))




;;; The macro `floorf-positive' is a version of floor which takes two positive,
;;; fixnum arguments and returns only the first value of Common Lisp floor.
;;; This can be specially optimized on those systems which translate to C, since
;;; the built-in C floor operations are well defined only for the positive
;;; integer ranges.  -jra 11/9/91

;; jh, 7/20/93.  Added a clause to floorf-positive so that the new Chestnut
;; translator can properly use the native C / operator.  The call to the Lisp
;; values function will not produce an extra function call in this context.

(defmacro floorf-positive (positive-fixnum positive-divisor-fixnum &environment env)
  (cond ((eval-feature :chestnut-trans)
         `(values
            ,(declare-argument-and-result-types
               'fixnum
               `(floor (the (integer 0 *) ,positive-fixnum)
                       (the (integer 1 *) ,positive-divisor-fixnum))
               env)))
        (t
         `(floorf ,positive-fixnum ,positive-divisor-fixnum))))

(defmacro floorf-positive-2 (positive-fixnum positive-divisor-fixnum &environment env)
  (cond ((eval-feature :chestnut-trans)
         `(the (values fixnum fixnum)
               ,(declare-argument-types
                  'fixnum
                  `(floor (the (integer 0 *) ,positive-fixnum)
                          (the (integer 1 *) ,positive-divisor-fixnum))
                  env)))
        (t
         `(floorf ,positive-fixnum ,positive-divisor-fixnum))))

(defmacro floorf (fixnum &optional divisor-fixnum &environment env)
  (cond ((and divisor-fixnum
              (eval-feature :chestnut-trans))
         `(chestnut-floorf-function ,fixnum ,divisor-fixnum))
        (t
         `(the (values fixnum fixnum)
               ,(declare-argument-types
                  'fixnum
                  `(floor ,fixnum
                          ,@(if divisor-fixnum
                                `(,divisor-fixnum)
                                nil))
                  env)))))

(defmacro ceilingf (fixnum &optional divisor-fixnum &environment env)
  `(the (values fixnum fixnum)
        ,(declare-argument-types
           'fixnum
           `(ceiling ,fixnum
                     ,@(if divisor-fixnum
                           `(,divisor-fixnum)
                           nil))
           env)))




;;; The macro `ceilingf-positive' is a version of ceiling that takes two
;;; non-negative fixnums and returns a single fixnum result.  This operation can
;;; be optimized better in C translated versions because the negative range of
;;; integers don't have to be dealt with.

(defmacro ceilingf-positive (fixnum divisor-fixnum)
  (if (simple-argument-p divisor-fixnum)
      `(floorf-positive
         (+f ,fixnum (-f ,divisor-fixnum 1))
         ,divisor-fixnum)
      (let ((numerator (gensym))
            (divisor (gensym)))
        `(let ((,numerator ,fixnum)
               (,divisor ,divisor-fixnum))
           (declare (type fixnum ,numerator ,divisor))
           (floorf-positive
             (+f ,numerator (-f ,divisor 1))
             ,divisor)))))

(defmacro truncatef (fixnum &optional divisor-fixnum &environment env)
  `(the (values fixnum fixnum)
        ,(declare-argument-types
           'fixnum
           `(truncate ,fixnum
                      ,@(if divisor-fixnum
                            `(,divisor-fixnum)
                            nil))
           env)))

(defun truncatef-first (fixnum divisor-fixnum)
  (declare (type fixnum fixnum divisor-fixnum)
	   (eliminate-for-gsi))
  (if (=f 0 divisor-fixnum)
      0
      (if (pluspf fixnum)
          (if (pluspf divisor-fixnum)
              (floorf-positive fixnum divisor-fixnum)
              (-f (floorf-positive fixnum (-f divisor-fixnum))))
          (if (pluspf divisor-fixnum)
              (-f (floorf-positive (-f fixnum) divisor-fixnum))
              (floorf-positive (-f fixnum) (-f divisor-fixnum))))))

(defmacro roundf (fixnum &optional divisor-fixnum &environment env)
  `(the (values fixnum fixnum)
        ,(declare-argument-types
           'fixnum
           `(round ,fixnum
                   ,@(if divisor-fixnum
                         `(,divisor-fixnum)
                         nil))
           env)))


(defmacro logandf (&rest fixnums &environment env)
  (cond ((null fixnums)
         -1)
        ((null (cdr fixnums))
         (declare-result 'fixnum (car fixnums)))
        ;; The following line works around an IntelNT C compiler bug, where
        ;; (IFIX(x) & 128L) > 0L will fail, due to some special handling
        ;; afforded to the value 128.  We suspect that this problem occurs for
        ;; all fixnums from 128 through 255, since the 7th bit is on in all
        ;; these values, under the theory that this has something to do with the
        ;; compiler trying to use a signed char type for the result.  This can
        ;; be worked around shuffling the result of the bitwise and through an
        ;; assignment statement, accomplished in the translator via the LET
        ;; statement.  -jra 9/30/94
        ((loop for fixnum-form in fixnums
               thereis (and (fixnump fixnum-form)
                            (<= 128 fixnum-form 255)))
         (let ((logand-result (gensym)))
           `(let ((,logand-result
                     ,(declare-type-preserving-numeric-operation
                        'fixnum 'logand fixnums env)))
              (declare (type fixnum ,logand-result))
              ,logand-result)))
        (t
         (declare-type-preserving-numeric-operation
           'fixnum 'logand fixnums env))))

(defmacro logandc1f (fixnum1 fixnum2 &environment env)
  (declare-argument-and-result-types 'fixnum `(logandc1 ,fixnum1 ,fixnum2) env))

(defmacro logandc2f (fixnum1 fixnum2 &environment env)
  (declare-argument-and-result-types 'fixnum `(logandc2 ,fixnum1 ,fixnum2) env))

(defmacro logxorf (&rest fixnums &environment env)
  (cond ((null fixnums)
         0)
        ((null (cdr fixnums))
         (declare-result 'fixnum (first fixnums)))
        (t
         (declare-type-preserving-numeric-operation 'fixnum 'logxor fixnums env))))

(defmacro logiorf (&rest fixnums &environment env)
  (cond ((null fixnums)
         0)
        ((null (cdr fixnums))
         (declare-result 'fixnum (first fixnums)))
        (t
         (declare-type-preserving-numeric-operation 'fixnum 'logior fixnums env))))

(defmacro lognotf (fixnum &environment env)
  (declare-argument-and-result-types 'fixnum `(lognot ,fixnum) env))


;; See the comment above minf for the reason why arguments to ashf are sometimes
;; rebound to gensyms.  -jra 5/2/91

#+chestnut-3
(deftype non-negative-fixnum ()
  `(and (integer 0 *) fixnum))

(defmacro ashf (fixnum n &environment env)
  (cond ((and (constantp n) (= (eval n) 0))
         fixnum)
        ((and (constantp fixnum)
              ;; We must disable constant optimization for boundary values, otherwise
              ;; Lisp->C translations from 64-bit translator won't be compiled correctly
              ;; by 32-bit C compilers. -- Chun Tian (binghe), Apr 2016
              (not (= (eval fixnum) most-positive-fixnum))
              (not (= (eval fixnum) most-negative-fixnum))
              (constantp n))
         (ash (eval fixnum) (eval n)))
        ;; jh, 6/29/93.  Declarations per Rick @ Chestnut.  Not sure how to wire
        ;; this into declare-argument-and-result-types.  Also not sure if we can
        ;; guarantee that a negative constant n is always paired with a
        ;; nonnegative fixnum, though the only use of which I am aware (array
        ;; access of managed-floats) can make that guarantee.

        ;; -jra & jh 7/21/93 Note that there are warnings in Harbison and Steele
        ;; "C: A Reference Manual Edition 3", page 191 that say that the C >>
        ;; operator (right shift) may or may not sign extend a negative left
        ;; hand argument.  Chestnut's generic fixnum shifting makes this
        ;; assumption, but their inliner for fixnum arithmetic refuses.  Silly.
        ;; So we are currently lying to it that the first argument is
        ;; non-negative.  The assumption about right shift extending the sign
        ;; bit is validated below in validate-fixnum-assumptions.  Even if we
        ;; can stop lying to the Chestnut compiler, we will still need to
        ;; validate the assumption, since it is a problem with the underlying C.
        ((constantp n)
         (let ((shift (eval n)))
           (declare-argument-and-result-types
             'fixnum
             `(,(if (minusp shift)
                    'right-shiftf
                    'left-shiftf)
               ,fixnum ,(abs shift))
             env)))
        ((and (simple-argument-p fixnum)
              (simple-argument-p n))
         (declare-argument-and-result-types 'fixnum `(ash ,fixnum ,n) env))
        (t
         (let ((fixnum-arg (gensym))
               (n-arg (gensym)))
           `(let ((,fixnum-arg ,fixnum)
                  (,n-arg ,n))
              ,(declare-argument-and-result-types
                 'fixnum `(ash ,fixnum-arg ,n-arg) env))))))

(defmacro right-shiftf (fixnum non-negative-shift-distance)
  `(the fixnum
        (ash (the fixnum ,fixnum)
             (the (integer * 0) (-f ,non-negative-shift-distance)))))

(defmacro left-shiftf (fixnum non-negative-shift-distance)
  `(the fixnum
        (ash (the fixnum ,fixnum)
             (the (integer 0 *) ,non-negative-shift-distance))))

;;; Benchmarks in Lucid and Ibuki [an obsolete platform] on a Sun 3 showed that
;;; the "(/=f (logandf x (ashf 1 y)) 0" approach is 3 times faster than calling
;;; logbitp in Lucid and is very slow in both cases in Ibuki.  So, for the
;;; moment we will implement a logbitpf using logand.

(defmacro logbitpf (fixnum-index fixnum)
  (let ((mask (if (constantp fixnum-index)
                  (ash 1 (eval fixnum-index))
                  `(ashf 1 ,fixnum-index))))
    `(/=f (logandf ,mask ,fixnum) 0)))

;; Note that logbitpf was always broken until now in that it took its arguments
;; in the order opposite that of Common Lisp's logbitp function.  This has now
;; been fixed. (MHD 4/21/92)


(defmacro modf (fixnum fixnum-divisor &environment env)
  (if (eval-feature :chestnut-trans)
      `(chestnut-modf-function ,fixnum ,fixnum-divisor)
      (declare-argument-and-result-types
        'fixnum `(mod ,fixnum ,fixnum-divisor) env)))




;;; The macro `modf-positive' is a version of modf which takes a non-negative
;;; first argument and a positive second argument and produces its single value
;;; result.  Note that this can be optimized more than the normal fixnum version
;;; on systems which translate into C.

;; jh, 7/20/93.  Added a clause to modf-positive so that the new Chestnut
;; translator can properly use the native C % operator.  The call to the Lisp
;; values function will not produce an extra function call in this context.

(defmacro modf-positive (non-negative-fixnum positive-fixnum-divisor &environment env)
  (cond ((and (eval-feature :chestnut-trans)
              (eval-feature :chestnut-3))
         `(the (values (integer 0 ,most-positive-fixnum))
               (values (mod (the (integer 0 ,most-positive-fixnum)
                                 ,non-negative-fixnum)
                             (the (integer 1 ,most-positive-fixnum)
                                 ,positive-fixnum-divisor)))))
        ((eval-feature :chestnut-trans)
         (declare-argument-and-result-types
          'fixnum
          `(mod-positive ,non-negative-fixnum ,positive-fixnum-divisor)
          env))
        ((eval-feature :development)
         (let ((prolog '(progn))
               (arg1 non-negative-fixnum)
               (arg2 positive-fixnum-divisor))

           (when (and (simple-argument-p non-negative-fixnum)
                      (simple-argument-p positive-fixnum-divisor))
             (setq arg1 (gensym))
             (setq arg2 (gensym))
             (setq prolog `(let ((,arg1 ,non-negative-fixnum)
                                 (,arg2 ,positive-fixnum-divisor)))))
           `(,@prolog
               (when (or (<f ,arg1 0) (<f ,arg2 1))
                 (illegal-use-of-mod-positive ,arg1 ,arg2))
               (modf ,arg1 ,arg2))))
        (t
         `(modf ,non-negative-fixnum ,positive-fixnum-divisor))))


;; modf-quick is a hack to calculate mod quickly.
;; It will use C % operator and the result may not like lisp mod / rem.
;; Be careful when use this macro.

(defmacro modf-quick (fixnum fixnum-divisor)
  (cond ((eval-feature :chestnut-trans)
         `(modf-positive ,fixnum ,fixnum-divisor))
        (t
         `(modf ,fixnum ,fixnum-divisor))))


#+development
(defun illegal-use-of-mod-positive (arg1 arg2)
  (cerror "continue, using modf, which won't be available in Chestnut!"
          "illegal to take mod-positive of negative fixnum ~d, ~d"
          arg1 arg2))




;;; The function `rem-fixnums' takes two fixnums and returns the remainder of
;;; the two.  This is a faster interface to the second of truncatef.

(defun rem-fixnums (fixnum fixnum-divisor)
  (declare (type fixnum fixnum fixnum-divisor)
	   (eliminate-for-gsi))
  (if (=f 0 fixnum-divisor)
      fixnum
      (if (minuspf fixnum)
          (if (minuspf fixnum-divisor)
              (-f (modf-positive (-f fixnum) (-f fixnum-divisor)))
              (-f (modf-positive (-f fixnum) fixnum-divisor)))
          (if (minuspf fixnum-divisor)
              (modf-positive fixnum (-f fixnum-divisor))
              (modf-positive fixnum fixnum-divisor)))))

(defmacro incff (place &optional (delta 1))
  (if (and (eval-feature :chestnut-trans)
           (not (eval-feature :chestnut-3))
           (symbolp place))
      `(,(primitive-numeric-operator 'incf 'fixnum) ,place ,delta)
      `(incff-1 ,place ,delta)))

(define-modify-macro incff-1 (&optional (delta 1)) +f)

(defmacro decff (place &optional (delta 1))
  (if (and (eval-feature :chestnut-trans)
           (not (eval-feature :chestnut-3))
           (symbolp place))
      `(,(primitive-numeric-operator 'decf 'fixnum) ,place ,delta)
      `(decff-1 ,place ,delta)))

(define-modify-macro decff-1 (&optional (delta 1)) -f)

;; Note that when we abandon the old translator, we should get rid of the macros
;; for incff and decff, and rename the modify macros above to be incff and
;; decff.  -jra 7/21/93




;;; `Two-arg-lcmf' is LCM for two fixnums, returning one fixnum.

(defun two-arg-lcmf (n m)
  (declare (type fixnum n m)
	   (eliminate-for-gsi))
  (*f (truncatef-first
        (maxf n m)
        (two-arg-gcdf n m))
      (minf n m)))




;;; `Two-arg-gcdf' is GCD of two fixnum arguments returning a fixnum.  With
;;; fixnum arguments, we use the binary GCD algorithm from Knuth's seminumerical
;;; algorithms.

;; Derived from CMU Lisp's code.

(defun two-arg-gcdf (u v)
  (declare (type fixnum u v)
	   (eliminate-for-gsi))
  (cond
    ((=f u 0) v)
    ((=f v 0) u)
    (t
     (loop for k from 0
           for u fixnum = (absf u) then (ashf u -1)
           for v fixnum = (absf v) then (ashf v -1)
           until (oddp (logiorf u v))
           finally
             (loop for temp fixnum = (if (oddp u) (-f v) (ashf u -1))
                            then (ashf temp -1)
                   when (oddp temp)
                     do
                       (if (pluspf temp)
                           (setq u temp)
                           (setq v (-f temp)))
                       (setq temp (-f u v))
                       (when (=f 0 temp)
                         (return-from two-arg-gcdf
                           (left-shiftf u k))))))))

;;; when allocate memory in G2, allocate bytes rounded to 2^n will speed up the reused rate of it when recycled.
;;; `g-logf' is putted into here for such purpose.

(defun g-logf (y)
  (declare (type fixnum y)
	   (eliminate-for-gsi))
  (loop with i fixnum = 0
        for n = (ashf y -1) then (ashf n -1)
        do
    (if (>=f n 1)
        (incff i)
      (loop-finish))
    finally (return i)))




;;;; System-specific Compilation




;;; The macro `current-system-case' is intended to eliminate unnecessary runtime
;;; branches based on the current system, when that system is running in a
;;; distribution image.  Each clause is a list whose head is an unevaluated
;;; symbol naming a system and whose tail is a set of actions to be executed in
;;; an implicit progn if the current-system-case form is evaluated in the given
;;; system.  Currently (jh, 3/18/94), system names are: ab (an old name for g2),
;;; gsi, and telewindows.

;;; In distribution, current-system-case only expands into the actions given by
;;; the clause for the current system and ignores the other clauses.  In
;;; development, this macro expands into a case statement that dispatches at
;;; runtime on current-system-name and uses all clauses.  The fact that the
;;; development expansion uses all clauses means that extra functions must be
;;; stubbed out there.  Worse, in general, any difference between distribution
;;; and development compiles is abhorrent, since it leads to obscure bugs.  But
;;; unless development does a runtime check, there will be problems loading
;;; different systems in the same Lisp.

(defun-for-macro get-appropriate-current-system-case-clause
    (clauses current-system)
  (dolist (system-and-actions clauses nil)
    (let ((system-or-systems (first system-and-actions)))
      (when (or (member system-or-systems '(t otherwise))
                (if (consp system-or-systems)
                    (member current-system system-or-systems)
                    (eq current-system system-or-systems)))
        (return `(progn ,@(rest system-and-actions)))))))

(defmacro current-system-case (&body clauses)
  (let ((systems-mentioned nil))
    (dolist (clause clauses)
      (let ((system-or-systems (first clause)))
        (cond
          ((symbolp system-or-systems)
           (push system-or-systems systems-mentioned))
          (t (setq systems-mentioned
                   (append system-or-systems systems-mentioned))))))
    (let ((errant-systems?
            (set-difference systems-mentioned
                            (append '(t otherwise) all-systems))))
      (when errant-systems?
        (error "CURRENT-SYSTEM-CASE: unknown system~:[~;~s~]: ~s"
               (cdr errant-systems?)
               errant-systems?))))
  (cond
    #+ignore ; cases not for current system may contain undefined macro.
    ((eval-feature :development)
     `(case (distribution-current-system 'current-system-case)
        ,@clauses))
    (t (let ((current-system (distribution-current-system 'current-system-case)))
         (when current-system
           (get-appropriate-current-system-case-clause
             clauses
             current-system))))))

(defmacro runtime-current-system-case (&body clauses)
  #-gsi-in-g2
  `(current-system-case ,@clauses)
  #+gsi-in-g2
  (let ((systems-mentioned nil))
    (dolist (clause clauses)
      (let ((system-or-systems (first clause)))
        (cond
          ((symbolp system-or-systems)
           (push system-or-systems systems-mentioned))
          (t (setq systems-mentioned
                   (append system-or-systems systems-mentioned))))))
    (let ((errant-systems?
            (set-difference systems-mentioned
                            '(t otherwise ab telewindows gsi))))
      (when errant-systems?
        (error "CURRENT-SYSTEM-CASE: unknown system~:[~;~s~]: ~s"
               (cdr errant-systems?)
               errant-systems?)))
    `(current-system-case
       (gsi         ,(get-appropriate-current-system-case-clause clauses 'gsi))
       (telewindows ,(get-appropriate-current-system-case-clause clauses 'telewindows))
       (ab          (case current-system-name ,@clauses)))))

(defun-for-macro distribution-current-system
    (&optional (caller 'distribution-current-system))
  (or (and (boundp 'current-system-being-loaded)
           current-system-being-loaded)
      (and (boundp 'current-system-name)
           current-system-name)
      (progn
        (warn "~S: evaluated in distribution when neither~%~
               current-system-being-loaded nor current-system-name is bound and non-NIL"
              caller)
        nil)))

(defmacro if-chestnut (chestnut-form otherwise-form)
  chestnut-form
  #+development
  otherwise-form
  #-development
  (if (and (eval-feature :chestnut-3)
           (eval-feature :chestnut-trans))
      chestnut-form
      otherwise-form))

(defmacro if-chestnut-gsi (chestnut-gsi-form otherwise-form)
  chestnut-gsi-form
  #+development
  otherwise-form
  #-development
  `(current-system-case
     ((gsi #+gsi-in-g2 ab)
       (if-chestnut
         ,chestnut-gsi-form
         ,otherwise-form))
     (t
       ,otherwise-form)))






;;;; Forward Reference Masking in Scopes




;;; The macro `with-ignored-forward-references' takes a list of function names
;;; that may be called within the body of this macro.  The compilation of this
;;; in development should mask any forward reference warnings by calling the
;;; function in a way that the compiler won't notice it as a source of a
;;; reference that might require warnings.  In translation, this macro is a no-op.

(defmacro with-ignored-forward-references (function-names &body forms)
  (if (eval-feature :development)
      `(macrolet
           ,(loop for name in function-names
                  collect `(,name (&rest args) `(funcall ',',name ,@args)))
         ,@forms)
      `(progn ,@forms)))





;;;; Fixnum Arithmetic Assumptions




;;; The following code is run at launch time for any Gensym product that
;;; includes glbasics.  It runs a function that will call error if any of the
;;; assumptions that we have made about arithmetic do not hold true.  Add more
;;; assumption checking code to the function validate-fixnum-assumptions.

(defmacro bad-assumption (error-string &rest error-format-args)
  (unless (stringp error-string)
    (warn "Cannot compile call to bad-assumption: ~a ~a"
          error-string error-format-args))
  (let ((control-string
          (concatenate
            'string
            "The following problem has been detected:  "
            error-string)))
    `(current-system-case
       ((ab telewindows)
        (error ,control-string ,@error-format-args))
       (gsi (format t ,control-string ,@error-format-args)))))


(defparameter negative-fifty-million -50000000)

;;; NOTE: we don't need this any more, because all "#.most-positive-fixnum" used
;;; in G2 source code has been converted into parameters re-computed at load-time.
;;; That is because we want G2 Enterprise to have the 64-bit most-positive-fixnum.
;;; And the size of compile-time most-positive-fixnum is irrelevant now.
;;;
;;; -- Chun Tian (binghe), Dec 2015.

#|
(defun validate-fixnum-assumptions ()
  (unless (=f most-positive-fixnum #.most-positive-fixnum)
    (bad-assumption
      "Compile time most-positive-fixnum is different from run-time most-positive-fixnum."))
  (unless (=f (ashf negative-fifty-million -8) -195313)
    (bad-assumption
      "Right shift doesn't sign extend.")))

#-harlequin-pc-lisp ; ~= LispWorks
(validate-fixnum-assumptions)
|#



;;;; Floating Point Arithmetic




;;; The function for macro `gensym-float-operator-for-operation' takes a symbol
;;; naming a Common Lisp numeric operation and returns the symbol naming the
;;; type declared equivalent for gensym-floats.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter-for-macro gensym-float-operator-alist
  '((1+ . 1+e)
    (1- . 1-e)
    (+ . +e)
    (- . -e)
    (* . *e)
    (/ . /e)
    (= . =e)
    (/= . /=e)
    (< . <e)
    (> . >e)
    (<= . <=e)
    (>= . >=e)
    (min . mine)
    (max . maxe)
    (abs . abse)
    (ffloor . ffloore)
    (ffloor-first . ffloore-first)
    (floor-first . floore-first)
    (ceiling-first . ceilinge-first)
    (fceiling . fceilinge)
    (ftruncate . ftruncatee)
    (fround . frounde)
    (log . loge)
    (atan . atane)
    (cos . cose)
    (exp . expe)
    (expt . expte)
    (minusp . minuspe)
    (plusp . pluspe)
    (sin . sine)
    (sqrt . sqrte)
    (tan . tane)))


(defun-for-macro gensym-float-operator-for-operation (operator)
  (or (cdr (assoc operator gensym-float-operator-alist))
      operator)))


;;; Invokation of `assert-that-within-temporary-float-scope' provides a
;;; runtime assertion that we are dynamically inside of a temporary float
;;; scope.  This has no effect, or cost, if we are not  #+development.

;; - ben 2/14/91

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar within-temporary-float-scope? nil))

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar perform-float-scope-checking? nil))

(defmacro assert-that-within-temporary-float-scope ()
  #+(and development chestnut-3) ;SS_G2L
  `(unless within-temporary-float-scope?
     (cerror "Continue." "Call this function only inside a temporary-float-scope!"))
  #-development
  `nil)

(defmacro potentially-rigorous-operation (form)
  ;; so much for rigor.
  form)

(defmacro with-floating-point-checking-off (&body forms)
  `(let ((perform-float-scope-checking? nil))
     ,@forms))

;;; Chestnut has supplied us with a set of operations which take and produce raw
;;; double floats as values.  These double floats can only exist on the stack
;;; while being passed from one raw-double operation to another, and the final
;;; result must eventually be coerced back into a double-float.  The macro
;;; `coerce-gensym-float-to-raw-double' takes an argument which should be
;;; coerced into a raw-double.  If the argument to this macro is an expression,
;;; an attempt will be made to find an operator for that expression which
;;; already produces a raw-double as its value.  If one can be found, the
;;; operator of the given expression is replaced, and all of its arguments are
;;; themselves coerced to raw-doubles.  If no such operator can be found, the
;;; Chestnut primitve unboxing operation is emitted.




;;; The floating point arithmetic suite is a set of macros which are defined to
;;; act upon and (with the exception of predicates and the rounding type
;;; functions) return Gensym floating point numbers.  The actual type which
;;; corresponds to gensym-float varies per machine and Lisp vendor.  These
;;; functions include type declarations for the operators and results so that
;;; compilers may optimize calls to these numeric operations into appropriate
;;; floating point machine instructions.  The following macros are defined: 1+e,
;;; 1-e, +e, -e, =e, /=e, <e, >e, <=e, >=e, mine, maxe, *e, /e, rounde, floore,
;;; ceilinge, and truncatee.  Note that it is also useful to declare the types
;;; of local variables to gensym-float.  Both Lucid and Ibuki [an obsolete
;;; platform] use this information to limit the boxing of a raw floating point
;;; number into a Lisp, consed float.

;; See the comment in the section about fixnum arithmetic above which explains
;; why we ARE wrapping numeric type definers around forms for the Lispms.

(defmacro 1+e (gensym-float &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types (gensym-float-type) `(1+ ,gensym-float) env)))

(defmacro 1+e-raw (raw-double &environment env)
  (declare-argument-and-result-types 'raw-double `(1+ ,raw-double) env))

(defmacro 1-e (gensym-float &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types (gensym-float-type) `(1- ,gensym-float) env)))

(defmacro 1-e-raw (raw-double &environment env)
  (declare-argument-and-result-types 'raw-double `(1- ,raw-double) env))

(defmacro +e (&rest gensym-floats &environment env)
  `(potentially-rigorous-operation
    ,(if (null gensym-floats)
        0.0
        (declare-type-preserving-numeric-operation
          (gensym-float-type) '+ gensym-floats env))))

(defmacro +e-raw (&rest raw-doubles &environment env)
  (declare-type-preserving-numeric-operation 'raw-double '+ raw-doubles env))

(defmacro -e (gensym-float &rest gensym-floats &environment env)
  `(potentially-rigorous-operation
    ,(declare-type-preserving-numeric-operation
      (gensym-float-type) '- (cons gensym-float gensym-floats) env)))

(defmacro -e-raw (raw-double &rest raw-doubles &environment env)
  (declare-type-preserving-numeric-operation
    'raw-double '- (cons raw-double raw-doubles) env))

(defmacro *e (&rest gensym-floats &environment env)
  `(potentially-rigorous-operation
    ,(if (null gensym-floats)
        1.0
        (declare-type-preserving-numeric-operation
          (gensym-float-type) '* gensym-floats env))))

(defmacro *e-raw (&rest raw-doubles &environment env)
  (declare-type-preserving-numeric-operation 'raw-double '* raw-doubles env))

#-chestnut-3
(progn
  #+clozure
  (ccl:set-fpu-mode :invalid nil :division-by-zero nil)

  #+sbcl
  (sb-ext::set-floating-point-modes :traps '(:overflow :divide-by-zero))

  #+sbcl
  (defparameter dividend-to-prevent-constant-folding 0d0)

  (defun /e (dividend &optional divisor)
    (if divisor 
	(if (= divisor 0)
	    (cond ((= dividend 0)
		   #-sbcl 1d+-0
		   #+sbcl (/ 0d0 dividend-to-prevent-constant-folding))  ; #<DOUBLE-FLOAT quiet NaN>
		  ((> dividend 0)
		   #-sbcl 1d++0
		   #+sbcl SB-EXT:DOUBLE-FLOAT-POSITIVE-INFINITY)
		  (t ; (< dividend 0)
		   #-sbcl -1d++0
		   #+sbcl SB-EXT:DOUBLE-FLOAT-NEGATIVE-INFINITY))
	  (/ dividend divisor))
      (/e 1d0 dividend))))

#+chestnut-3
(defmacro /e (&rest gensym-floats &environment env)
  `(potentially-rigorous-operation
    ,(declare-type-preserving-numeric-operation (gensym-float-type) '/ gensym-floats env)))

(defmacro /e-raw (&rest raw-doubles &environment env)
  (declare-type-preserving-numeric-operation 'raw-double '/ raw-doubles env))

(defmacro =e (&rest gensym-floats &environment env)
  (declare-comparitor '= (gensym-float-type) gensym-floats env))

(defmacro =e-raw (&rest raw-doubles &environment env)
  (declare-comparitor '= 'raw-double raw-doubles env))

(defmacro /=e (&rest gensym-floats &environment env)
  (declare-comparitor '/= (gensym-float-type) gensym-floats env))

(defmacro /=e-raw (&rest raw-doubles &environment env)
  (declare-comparitor '/= 'raw-double raw-doubles env))

(defmacro <e (&rest gensym-floats &environment env)
  (declare-comparitor '< (gensym-float-type) gensym-floats env))

(defmacro <e-raw (&rest raw-doubles &environment env)
  (declare-comparitor '< 'raw-double raw-doubles env))

(defmacro >e (&rest gensym-floats &environment env)
  (declare-comparitor '> (gensym-float-type) gensym-floats env))

(defmacro >e-raw (&rest raw-doubles &environment env)
  (declare-comparitor '> 'raw-double raw-doubles env))

(defmacro <=e (&rest gensym-floats &environment env)
  (declare-comparitor '<= (gensym-float-type) gensym-floats env))

(defmacro <=e-raw (&rest raw-doubles &environment env)
  (declare-comparitor '<= 'raw-double raw-doubles env))

(defmacro >=e (&rest gensym-floats &environment env)
  (declare-comparitor '>= (gensym-float-type) gensym-floats env))

(defmacro >=e-raw (&rest raw-doubles &environment env)
  (declare-comparitor '>= 'raw-double raw-doubles env))

;; See comment near maxf for reasoning about rebinding arguments.  -jra 1/23/92

(defmacro mine (&rest gensym-floats &environment env)
  `(potentially-rigorous-operation
    ,(cond
      ((loop for argument in gensym-floats
             always (simple-argument-p argument))
       (declare-type-preserving-numeric-operation
         (gensym-float-type) 'min gensym-floats))
      (t
       (loop for argument in gensym-floats
             for bound-argument = (gensym)
             collect `(,bound-argument ,argument) into bindings
             collect bound-argument into new-arguments
             finally
               (return
                 `(let ,bindings
                    ,(declare-type-preserving-numeric-operation
                       (gensym-float-type) 'min new-arguments env))))))))

(defmacro mine-raw (&rest raw-doubles &environment env)
  (declare-type-preserving-numeric-operation
    'raw-double 'min raw-doubles env))

;;; GENSYMCID-978: 'Unexpected NaN behaviour'.
;;;
;;; Chestnut RTL uses expressions like ((a < b) ? a : b) to determine the max/min value
;;; between two floats, this violates IEEE 754 standard and caused wrong results in KB.

;;; http://en.wikipedia.org/wiki/NaN
;;; 
;;; In section 6.2 of the revised IEEE 754-2008 standard there are two anomalous
;;; functions (the maxnum and minnum functions that return the maximum of two
;;; operands that are expected to be numbers) that favor numbers -- if just one
;;; of the operands is a NaN then the value of the other operand is returned.

;;; The original words in IEEE754-2008: "For an operation with quiet NaN inputs,
;;; other than maximum and minimum operations, if a floating-point result is to
;;; be delivered the result shall be a quiet NaN which should be one of the input
;;; NaNs.

;;; -- Chun Tian (binghe), August 12 2013.

(defmacro mine2 (gensym-float-1 gensym-float-2)
  (let ((float-1 (gensym))
        (float-2 (gensym)))
    `(let ((,float-1 ,gensym-float-1)
           (,float-2 ,gensym-float-2))
       (cond ((nanp ,float-1) ,float-2)
             ((nanp ,float-2) ,float-1)
             (t (mine ,float-1 ,float-2))))))

;; See comment near maxf for reasoning about rebinding arguments.  -jra 1/23/92

(defmacro maxe (&rest gensym-floats &environment env)
  `(potentially-rigorous-operation
    ,(cond
      ((loop for argument in gensym-floats
             always (simple-argument-p argument))
       (declare-type-preserving-numeric-operation
         (gensym-float-type) 'max gensym-floats env))
      (t
       (loop for argument in gensym-floats
             for bound-argument = (gensym)
             collect `(,bound-argument ,argument) into bindings
             collect bound-argument into new-arguments
             finally
               (return
                 `(let ,bindings
                    ,(declare-type-preserving-numeric-operation
                       (gensym-float-type) 'max new-arguments env))))))))

(defmacro maxe-raw (&rest raw-doubles &environment env)
  (declare-type-preserving-numeric-operation
    'raw-double 'max raw-doubles env))

;;; GENSYMCID-978: 'Unexpected NaN behaviour'.

(defmacro maxe2 (gensym-float-1 gensym-float-2)
  (let ((float-1 (gensym))
        (float-2 (gensym)))
    `(let ((,float-1 ,gensym-float-1)
           (,float-2 ,gensym-float-2))
       (cond ((nanp ,float-1) ,float-2)
             ((nanp ,float-2) ,float-1)
             (t (maxe ,float-1 ,float-2))))))

(defmacro abse (gensym-float &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
        (gensym-float-type)
        `(abs ,gensym-float)
        env)))

(defmacro abse-raw (raw-double &environment env)
  (declare-argument-and-result-types
    'raw-double
    `(abs ,raw-double)
    env))

(defmacro ffloore (gensym-float &optional gensym-float-divisor &environment env)
  `(potentially-rigorous-operation
     (the (values ,(gensym-float-type) ,(gensym-float-type))
          ,(declare-argument-types
             (gensym-float-type)
             (if gensym-float-divisor
                 `(ffloor ,gensym-float ,gensym-float-divisor)
                 `(ffloor ,gensym-float))
             env))))

(defmacro fceilinge (gensym-float &optional gensym-float-divisor &environment env)
  `(potentially-rigorous-operation
     (the (values ,(gensym-float-type) ,(gensym-float-type))
        ,(declare-argument-types
           (gensym-float-type)
           (if gensym-float-divisor
               `(fceiling ,gensym-float ,gensym-float-divisor)
               `(fceiling ,gensym-float))
           env))))

;;; The macro `ffloore-first' is like Common Lisp ffloor, but only the first
;;; value is returned and only one argument is received.  In C translation
;;; implementations there is a direct translation for this operator into the C
;;; floor function.

(defmacro ffloore-first (gensym-float &optional divisor-gensym-float?)
  `(potentially-rigorous-operation
     ,(if divisor-gensym-float?
          `(inline-ffloor-1 (/e ,gensym-float ,divisor-gensym-float?))
          `(inline-ffloor-1 ,gensym-float))))




;;; The macro `floore-first' is like Common Lisp floor, but it accepts only
;;; gensym-floats, returns only the first value of floor, and the result must be
;;; able to lie within the range of fixnums.  The behavior is undefined if any
;;; of these constraints are not adhered to.

(defmacro floore-first (gensym-float &optional divisor-gensym-float?)
  `(potentially-rigorous-operation
     ,(if divisor-gensym-float?
         `(inline-floor-1 (/e ,gensym-float ,divisor-gensym-float?))
         `(inline-floor-1 ,gensym-float))))


;;; This doesn't work right for negative numbers.
(defmacro rounde-first (gensym-float &optional divisor-gensym-float?)
  `(potentially-rigorous-operation
     ,(if divisor-gensym-float?
         `(inline-floor-1 (+e 0.5 (/e ,gensym-float ,divisor-gensym-float?)))
         `(inline-floor-1 (+e 0.5 ,gensym-float)))))




;;; The macro `ceilinge-first' takes a gensym float and an optional gensym float
;;; divisor, divides the two, takes the ceiling of the result, and returns the
;;; fixnum result.  Note that if the result is not within fixnum bounds, then
;;; the result of this operation is undefined and it may signal an error.  The
;;; macro `fceilinge-first' is the optimized version of fceiling.

(defmacro ceilinge-first (gensym-float &optional divisor-gensym-float?)
  `(potentially-rigorous-operation
     ,(if divisor-gensym-float?
          `(inline-ceiling-1 (/e ,gensym-float ,divisor-gensym-float?))
          `(inline-ceiling-1 ,gensym-float))))

(defmacro fceilinge-first (gensym-float &optional divisor-gensym-float?)
  `(potentially-rigorous-operation
     ,(if divisor-gensym-float?
          `(inline-fceiling-1 (/e ,gensym-float ,divisor-gensym-float?))
          `(inline-fceiling-1 ,gensym-float))))

(defmacro ftruncatee (gensym-float &optional gensym-float-divisor &environment env)
  `(potentially-rigorous-operation
    (the (values ,(gensym-float-type) ,(gensym-float-type))
         ,(declare-argument-types
            (gensym-float-type)
            (if gensym-float-divisor
                `(ftruncate ,gensym-float ,gensym-float-divisor)
                `(ftruncate ,gensym-float))
            env))))



;;; `ftruncatee-up' truncates up away from 0 (i.e. does the opposite of ftruncatee)

(defun ftruncatee-up (float)
  (declare (eliminate-for-gsi))
  (if (>e float 0d0)
      (fceilinge float)
      (ffloore   float)))


(defmacro frounde (gensym-float &optional gensym-float-divisor &environment env)
  `(potentially-rigorous-operation
    (the (values ,(gensym-float-type) ,(gensym-float-type))
         ,(declare-argument-types
            (gensym-float-type)
            (if gensym-float-divisor
                `(fround ,gensym-float ,gensym-float-divisor)
                `(fround ,gensym-float))
            env))))

(defmacro loge (gensym-float &optional gensym-float-base &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
        (gensym-float-type)
        (if gensym-float-base
            `(log ,gensym-float ,gensym-float-base)
            `(log ,gensym-float))
        env)))

(defmacro loge-raw (raw-double &optional raw-double-base &environment env)
  (declare-argument-and-result-types
    'raw-double
    (if raw-double-base
        `(log ,raw-double ,raw-double-base)
        `(log ,raw-double))
    env))

(defmacro atane (gensym-float &optional gensym-float-2 &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
       (gensym-float-type)
       (if gensym-float-2
           `(atan ,gensym-float ,gensym-float-2)
           `(atan ,gensym-float))
       env)))

(defmacro atane-raw (raw-double &optional raw-double-2 &environment env)
  (declare-argument-and-result-types
    'raw-double
    (if raw-double-2
        `(atan ,raw-double ,raw-double-2)
        `(atan ,raw-double))
    env))

(defmacro asine (gensym-float &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
        (gensym-float-type)
        `(asin ,gensym-float)
        env)))

(defmacro asine-raw (raw-double &environment env)
  (declare-argument-and-result-types
    'raw-double
    `(asin ,raw-double)
    env))

(defmacro cose (gensym-float &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
        (gensym-float-type)
        `(cos ,gensym-float)
        env)))

(defmacro cose-raw (raw-double &environment env)
  (declare-argument-and-result-types
    'raw-double
    `(cos ,raw-double)
    env))

(defmacro expe (gensym-float &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
        (gensym-float-type)
        `(exp ,gensym-float)
         env)))

(defmacro expe-raw (raw-double &environment env)
  (declare-argument-and-result-types
    'raw-double
    `(exp ,raw-double)
    env))

(defmacro expte (gensym-float gensym-float-power &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
        (gensym-float-type)
        `(expt ,gensym-float ,gensym-float-power)
        env)))

(defmacro expte-raw (raw-double raw-double-power &environment env)
  (declare-argument-and-result-types
    'raw-double
    `(expt ,raw-double ,raw-double-power)
    env))

(defmacro minuspe (gensym-float &environment env)
  (declare-argument-types
    (gensym-float-type)
    `(minusp ,gensym-float)
    env))

(defmacro minuspe-raw (raw-double &environment env)
  (declare-argument-types
    'raw-double
    `(minusp ,raw-double)
    env))

(defmacro pluspe (gensym-float &environment env)
  (declare-argument-types
    (gensym-float-type)
    `(plusp ,gensym-float)
    env))

(defmacro pluspe-raw (raw-double &environment env)
  (declare-argument-and-result-types
    'raw-double
    `(plusp ,raw-double)
    env))

(defmacro sine (gensym-float &environment env)
  (declare-argument-and-result-types
    (gensym-float-type)
    `(sin ,gensym-float)
    env))

(defmacro sine-raw (raw-double &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
        'raw-double
        `(sin ,raw-double)
        env)))

(defmacro sqrte (gensym-float &environment env)
  `(potentially-rigorous-operation
    ,(declare-argument-and-result-types
      (gensym-float-type)
      `(sqrt ,gensym-float)
      env)))

(defmacro sqrte-raw (raw-double &environment env)
  (declare-argument-and-result-types
    'raw-double
    `(sqrt ,raw-double)
    env))

(defmacro tane (gensym-float &environment env)
  `(potentially-rigorous-operation
     ,(declare-argument-and-result-types
        (gensym-float-type)
        `(tan ,gensym-float)
        env)))

(defmacro tane-raw (raw-double &environment env)
  (declare-argument-and-result-types
    'raw-double
    `(tan ,raw-double)
    env))


;;; The macro `coerce-to-gensym-float' takes a non-complex number and converts
;;; it into a gensym-float.

(defmacro coerce-to-gensym-float (number)
  `(potentially-rigorous-operation
     ,(cond ((constantp number)
             (float (eval number) 0d0))
            (t
             `(float ,number 0d0)))))

(defun coerce-to-gensym-float-function (x)
  (coerce-to-gensym-float x))

;;; The macro `coerce-fixnum-to-gensym-float' takes a fixnum and converts it
;;; into a gensym-float.

(defmacro coerce-fixnum-to-gensym-float (fixnum)
  `(potentially-rigorous-operation
     ,(cond ((constantp fixnum)
             (float (eval fixnum) 0d0))
            (t
             `(float (the fixnum ,fixnum) 0d0)))))

;;; The macro `gensym-float-p' is a predicate which takes a thing and determines
;;; whether it is a gensym-float.

(defmacro gensym-float-p (thing)
  (if (eval-feature :chestnut-trans)
      `(floatp ,thing)
      `(typep ,thing (gensym-float-type))))

(defparameter most-positive-fixnum-as-float
  ;; We need load-time computation of this parameter. Can't use `coerce-to-gensym-float'
  ;; here, because it's optimized for constant arguments. -- Chun Tian (binghe), Mar 2016
  (coerce-to-gensym-float-function most-positive-fixnum))

(defparameter most-negative-fixnum-as-float
  (coerce-to-gensym-float-function most-negative-fixnum))

(defparameter most-positive-fixnum32-as-float
  (coerce-to-gensym-float-function most-positive-fixnum32))

(defparameter most-positive-fixnum32-plus-one-as-float
  (+e most-positive-fixnum32-as-float 1.0))

(defconstant rational-float-epsilon
             (coerce-to-gensym-float 0.000001))

(defmacro >e-most-positive-fixnum (gensym-float)
  `(>e (-e ,gensym-float most-positive-fixnum-as-float)
       rational-float-epsilon))

(defmacro <e-most-negative-fixnum (gensym-float)
  `(>e (-e most-negative-fixnum-as-float ,gensym-float)
       rational-float-epsilon))

;;; The following feature is used by LOOP to determine whether or not it should
;;; attempt to use +F etc. operators.  This is being put in because of a nagging
;;; bug with some of the defun-for-macros (namedly typed-operator-for-type) are
;;; undefined when compiling forms in the bottom of this file.  This is odd,
;;; since all of them are wrapped with eval-when (:compile-toplevel
;;; :load-toplevel :execute)

#-no-macros
(pushnew :gensym-typed-arithmetic *features*)


;;;; Long (i64) Arithmetic

(defmacro coerce-fixnum-to-gensym-long (fixnum)
  (let ((long (make-symbol "LONG"))
	(zero (make-symbol "ZERO")))
    `(potentially-rigorous-operation
       (let ((,long ,fixnum)
	     (,zero 0))
	 (declare (type ,(gensym-long-type) ,long ,zero))
	 (the ,(gensym-long-type) (+ ,long ,zero))))))

(def-substitution-macro coerce-to-gensym-long (integer)
  (coerce-fixnum-to-gensym-long integer))

(defparameter most-positive-int64
  #+chestnut-trans ; to prevent literal bignums
  (coerce-to-gensym-long
    (1- (* #.(expt 2 21) (* #.(expt 2 21) #.(expt 2 21)))))
  #-chestnut-trans
  #.(1- (expt 2 63)))

(defparameter most-negative-int64
  #+chestnut-trans
  (- (- most-positive-int64) 1)
  #-chestnut-trans
  #.(- (expt 2 63)))

#-chestnut-trans
(defun int64-mod (i)
  (let ((j (mod i #.(expt 2 64))))
    (cond ((> j most-positive-int64)
	   (- j #.(expt 2 64)))
	  (t
	   j))))

(defmacro +L (&rest gensym-longs &environment env)
  (if (eval-feature :chestnut-trans)
      `(potentially-rigorous-operation
	 ,(if (null gensym-longs)
	      0
	    (declare-type-preserving-numeric-operation
	      (gensym-long-type) '+ gensym-longs env)))
    `(int64-mod (+ ,@gensym-longs))))

(defmacro -L (gensym-long &rest gensym-longs &environment env)
  (if (eval-feature :chestnut-trans)
      `(potentially-rigorous-operation
	 ,(declare-type-preserving-numeric-operation
	    (gensym-long-type) '- (cons gensym-long gensym-longs) env))
    `(int64-mod (- ,gensym-long ,@gensym-longs))))

(defmacro *L (&rest gensym-longs &environment env)
  (if (eval-feature :chestnut-trans)
      `(potentially-rigorous-operation
	 ,(if (null gensym-longs)
	      1
	    (declare-type-preserving-numeric-operation
	      (gensym-long-type) '* gensym-longs env)))
    `(int64-mod (* ,@gensym-longs))))

;; NOTE: /L-RAW returns LONG, not FLOAT.
(defmacro /L-RAW (&rest gensym-longs &environment env)
  (if (eval-feature :chestnut-trans)
      `(potentially-rigorous-operation
	 ,(declare-type-preserving-numeric-operation
	    (gensym-long-type) '/ gensym-longs env))
    `(truncate (/ ,@gensym-longs))))

(defmacro /L (&rest gensym-longs &environment env)
  `(potentially-rigorous-operation
     ,(declare-type-preserving-numeric-operation
        (gensym-long-type) '/ gensym-longs env)))

(defmacro =L (&rest gensym-longs &environment env)
  (declare-comparitor '= (gensym-long-type) gensym-longs env))

(defmacro /=L (&rest gensym-longs &environment env)
  (declare-comparitor '/= (gensym-long-type) gensym-longs env))

(defmacro <L (&rest gensym-longs &environment env)
  (declare-comparitor '< (gensym-long-type) gensym-longs env))

(defmacro >L (&rest gensym-longs &environment env)
  (declare-comparitor '> (gensym-long-type) gensym-longs env))

(defmacro <=L (&rest gensym-longs &environment env)
  (declare-comparitor '<= (gensym-long-type) gensym-longs env))

(defmacro >=L (&rest gensym-longs &environment env)
  (declare-comparitor '>= (gensym-long-type) gensym-longs env))


;;;; Fast Operations On List Structure


;;; CDR-OF-CONS and CAR-OF-CONS are defined in Bootstrap.

;;; The macro def-accessor-of-long-enough-list creates accessors analogous to
;;; second, third, and the like, except for two optimizations:
;;;   1) the accessors are macros, avoiding the overhead of a function call.
;;;   2) the accessors use car-of-cons and cdr-of-cons, avoiding the overhead of
;;;      a null check per access.

(defmacro def-accessor-of-long-enough-list (root-name index-in-list-1-based)
  (let ((accessor-name
          (intern (format nil "~a-OF-LONG-ENOUGH-LIST" root-name)))
        (list-var 'list))
    `(defmacro ,accessor-name (,list-var)
       ,(loop for index from 0 below index-in-list-1-based
              for form = list-var
                       then ``(cdr-of-cons ,,form)
              finally (return ``(car-of-cons ,,form))))))

(def-accessor-of-long-enough-list first   1)
(def-accessor-of-long-enough-list second  2)
(def-accessor-of-long-enough-list third   3)
(def-accessor-of-long-enough-list fourth  4)
(def-accessor-of-long-enough-list fifth   5)
(def-accessor-of-long-enough-list sixth   6)
(def-accessor-of-long-enough-list seventh 7)
(def-accessor-of-long-enough-list eighth  8)
(def-accessor-of-long-enough-list ninth   9)
(def-accessor-of-long-enough-list tenth  10)

;;; The macro `def-accessor-of-conses' creates accessors analogous to caar,
;;; cadr, and the like, and has the same optimizations as
;;; def-accessor-of-long-enough-list (q.v.)

(defmacro def-accessor-of-conses (depth)
  `(progn
     ,@(loop for designator from 0 below (expt 2 depth)
             with tree-var = 'tree
             collect
             (let ((accessor-name
                     (intern
                       (format nil "C~{~A~}R-OF-CONSES"
                         (reverse
                           (loop for index from 0 below depth
                                 collect
                                 (if (logbitp index designator) #\D #\A)))))))
               `(defmacro ,accessor-name (,tree-var)
                  ,(loop for index from 0 below depth
                         for form
                             = (if (logbitp index designator)
                                   ``(cdr-of-cons ,,tree-var)
                                   ``(car-of-cons ,,tree-var))
                             then (if (logbitp index designator)
                                      ``(cdr-of-cons ,,form)
                                      ``(car-of-cons ,,form))
                         finally (return form)))))
     ,depth))

(def-accessor-of-conses 2)
(def-accessor-of-conses 3)
(def-accessor-of-conses 4)


;;;; Preserve Symbol Function and Symbol Valueza

;;; `Declare-funcallable-symbol' is used to declare that symbol has a
;;; symbol-function that is funcall'ed else where.  This declaration is
;;; necessary to allow translation.

;;; In the Chestnut translator, Lisp symbols which name functions and global
;;; variables are eliminated from the run-time image, and references to the
;;; functions and values represented by this symbols are in-lined at reference
;;; points.  If a Lisp symbol is really needed at run-time, because
;;; symbol-value, symbol-function, or whatever is going to be called on it, and
;;; if this symbol is not already referenced elsewhere in the code as a quoted
;;; constant, the following declarations need to be issued to ensure that the
;;; symbol-value and symbol-function cells of the symbol are preserved into
;;; run-time.

(defvar destination-for-symbol-with-preserved-cells nil)

#+development
(defvar funcallable-symbol-argument-table (make-hash-table :test 'eq))
#+development
(defvar funcallable-symbol-result-table (make-hash-table :test 'eq))

(defmacro declare-funcallable-symbol (unquoted-symbol &optional (arguments 'not-supplied) (results 'not-supplied))
  #-development
  (declare (ignore arguments results))
  #+development
  (unless (eq arguments 'not-supplied)
    (setf (gethash unquoted-symbol funcallable-symbol-argument-table) arguments))
  #+development
  (unless (eq results 'not-supplied)
    (setf (gethash unquoted-symbol funcallable-symbol-result-table) results))

  (assert
    (symbolp unquoted-symbol) nil
    "~a should have been an unquoted symbol" unquoted-symbol)
  #-chestnut nil

  #+(and chestnut (not chestnut-3))
  (if (eval-feature :chestnut-trans)
      `(eval-when (:compile-toplevel)
         (trans:pushnew-function-symbol ',unquoted-symbol))
      nil)

  ;; jh, 1/25/93.  Chesntut no longer allows us to preserve function
  ;; cells piecemeal.  But they do guarantee that if a quoted symbol
  ;; exists at runtime, its function cell will be preserved.  The
  ;; following form assures that this happens.

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      ;;`(setq destination-for-symbol-with-preserved-cells ',unquoted-symbol)
      `(ab-lisp::declaim (tx:include-at-runtime (:symbol ,unquoted-symbol)))
      nil)
  )



;;; `Declare-symbol-value-preservation' is used to declare that symbol will have
;;; its symbol-value accessed via the symbol-value function.  This declaration is
;;; necessary to allow translation.  (Used only by format-structure-description,
;;; in int0.lisp.  rh, 12/4/95)

(defmacro declare-symbol-value-preservation (unquoted-symbol)
  (assert
    (symbolp unquoted-symbol) nil
    "~a should have been an unquoted symbol" unquoted-symbol)

  #-chestnut nil

  #+(and chestnut (not chestnut-3))
  (if (not (eval-feature :chestnut-trans))
      `(trans:pushnew-global-symbol ',unquoted-symbol)
      nil)

  ;; jh, 1/25/93.  Chesntut no longer allows us to preserve symbol cells
  ;; piecemeal.  But they do guarantee that if a quoted symbol exists at
  ;; runtime, its symbol cell will be preserved.  The following form
  ;; assures that this happens.
  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      `(setq destination-for-symbol-with-preserved-cells ',unquoted-symbol)
      nil)
  )


(defvar *list-of-symbols-for-symbol-value* nil)

(defvar *list-of-funcalled-functions* nil)

;; Remove the variable above after the next recompile.  -jra 3/17/91






;;;; Side-Effect Free Functions




;;; The macro `declare-side-effect-free-function' is given an unquoted symbol
;;; which is the name of a function.  This declaration is used to tell the
;;; compiler that this function can't change the behavior or returned values of
;;; any other operation.  This information allows the compiler to relax the
;;; restriction that arguments to functions in Common Lisp are called in left to
;;; right order.  This relaxation can allow for some significant optimizations.
;;; The macro `declare-side-effect-free-functions' takes an &rest list of
;;; unquoted symbols, and does the same thing.

;;; It is obviously true that a function is side-effect free if the function
;;; doesn't do any SETQ, SETF, or other data modifying operation--it only
;;; extracts portions of a given data structure.

;;; This will also be true for any function which doesn't change anything in a
;;; way which could cause another function (or this one for that matter) to
;;; return another value.  For example, if a property list fetching operation
;;; puts a fetched operation at the front of a property list (assuming this
;;; property will be fetched again soon), and no operation in the system could
;;; return a different value given the order of properties in a property list,
;;; then the property list fetching operation can be declared side-effect free.

;;; There is a further, less obvious case, where a function could be considered
;;; side-effect free.  Say that function A causes side-effects, those side
;;; effects cannot affect the behavior of function A, but they can affect the
;;; behavior of other operations in set B.  Function A can be declared
;;; side-effect free if none of the functions in set B are declared side-effect
;;; free.  This can be done since any argument list containing calls to the
;;; operations in set B will be executed left to right, giving correct behaviors
;;; to argument lists containing calls to both function A and calls to
;;; operations in the set B.  However, argument lists containing only calls to
;;; function A and other side-effect free functions can be optimized.  This
;;; special case is very important, since it can justify side-effect free
;;; declarations for structure allocation functions, like gensym-cons, as long
;;; as the memory metering functions are not declared side-effect free.  If
;;; there are more calls that are performance critical to gensym-cons than there
;;; are to the memory metering functions, then this trade-off is a win.

(defmacro declare-side-effect-free-function (function-name)
  #-(or chestnut chestnut-3) ;Chestnut3.1
  (declare (ignore function-name))
  #-(or chestnut chestnut-3) ;Chestnut3.1
  nil

  #+chestnut
  (if (eval-feature :chestnut-trans)
      nil
      `(trans:declare-side-effect-free ',function-name))

  #+chestnut-3 ;Chestnut3.1
  (if (eval-feature :chestnut-trans)
      `(declaim (tx:non-state-changing ,function-name))
      nil)
  )



(defmacro declare-side-effect-free-functions (&rest function-names)
  #-(or chestnut chestnut-3) ;Chestnut3.1
  (declare (ignore function-names))
  #-(or chestnut chestnut-3) ;Chestnut3.1
  nil

  #+chestnut
  (if (eval-feature :chestnut-trans)
      nil
      `(progn
         ,@(loop for function-name in function-names
                 collect
                   `(trans:declare-side-effect-free ',function-name))))

  #+chestnut-3 ;Chestnut3.1
  (if (eval-feature :chestnut-trans)
      `(declaim (tx:non-state-changing ,@function-names))
      nil)
)



#+chestnut
(progn
  (declare-side-effect-free-function trans::rsh%)
  (declare-side-effect-free-function trans::lsh%))

#+chestnut-3
(progn
  (declare-side-effect-free-function trun:rsh%)
  (declare-side-effect-free-function trun:lsh%))

(declare-side-effect-free-function rem-fixnums)






;;;; Shadowed Function Name




;;; Function-name is not a Common Lisp operation, but is available in some Lisp
;;; implementations.  If a name for a given (presumably compiled) function can
;;; be found, gensym-function-name will return it.  If not, it returns the
;;; original object.

#+development
(defmacro gensym-function-name (function)
  (feature-case
    (:lucid `(,(intern "FUNCTION-NAME" "LUCID") ,function))
    (:ti `(function-name ,function))
    (t function)))

#+development
(defvar maintain-list-of-funcalled-functions-p t)







;;;; Shadowed Symbol-function Function




#+(or development shadow-symbol-function)
(defun gensym-symbol-function (symbol)
;  #+development
;  (when (and within-managed-object-scope
;             maintain-list-of-funcalled-functions-p)
;    (with-dynamic-creation
;      (pushnew symbol *list-of-funcalled-functions*)))
  (ab-lisp:symbol-function symbol))

#+(or development shadow-symbol-function)
(defun setf-gensym-symbol-function (symbol new-value)
;  #+development
;  (when (and within-managed-object-scope
;             maintain-list-of-funcalled-functions-p)
;    (with-dynamic-creation
;      (pushnew symbol *list-of-funcalled-functions*)))
  (setf (ab-lisp::symbol-function symbol) new-value))








;;;; Shadowed Symbol-value Function




#+development
(defvar maintain-list-of-symbols-for-symbol-value-p t)

#+(or development shadow-symbol-value)
(defun gensym-symbol-value (symbol)
;  #+development
;  (when (and within-managed-object-scope
;             maintain-list-of-symbols-for-symbol-value-p)
;    (with-dynamic-creation
;      (pushnew symbol *list-of-symbols-for-symbol-value*)))
  (ab-lisp:symbol-value symbol))

#+(or development shadow-symbol-value)
(defun setf-gensym-symbol-value (symbol new-value)
;  #+development
;  (when (and within-managed-object-scope
;             maintain-list-of-symbols-for-symbol-value-p)
;    (with-dynamic-creation
;      (pushnew symbol *list-of-symbols-for-symbol-value*)))
  (setf (ab-lisp:symbol-value symbol) new-value))











;;;; Funcalling




;;; We have shadowed funcall in G2 to be able to expand it into more efficient
;;; machine specific code for some implementations of Lisp.  In particular,
;;; there is a fast C encoded version for Chestnut.  For all other
;;; implementations of Lisp, this macro expands into a normal Lisp funcall.
;;; There are also versions of funcall which are optimized for funcalling
;;; symbols and compiled functions.

;;; The macro `gensym-funcall' is like the Common Lisp version of funcall,
;;; except that it can only accept symbols and compiled function objects as the
;;; function argument.  In some systems (like ohh say Chestnut) it expands into
;;; C code which is much faster than the default Common Lisp implementation.
;;; Note that right now, the symbol funcall is itself shadowed and redefined as
;;; a macro that calls gensym-funcall.

;;; The comments above about faster funcalls no longer apply to the generic
;;; funcall operation.  We are putting in an optimization for funcall-simple-
;;; compiled-function, but the generic funcall still must go through Chestnut's
;;; implementation to handle things like optional and keyword arguments.  So,
;;; the gensym-funcall macro will only expand into ab-lisp::funcall, though we will
;;; retain this macro in case we want to do something interesting with it in the
;;; future.  -jra 4/24/91

;;; When a defun-simple is funcalled, the resulting values-count,
;;; and any values other than the first, are unpredictable, so
;;; this should be done only in a context where the values
;;; count and arguments other than the first are ignored.
;;; To increase the chance that violating this rule produces
;;; an error in development, we introduce bogus multiple values
;;; in this case. -alatto, 1/16/03

#+development
(defvar bogus-value (sqrt -1))

#+development
(defvar make-multi-value-funcalls-of-defun-simple-fail t)

(defmacro gensym-funcall (symbol-or-compiled-function &rest arguments)
  #-development
  `(ab-lisp::funcall ,symbol-or-compiled-function ,@arguments)
  #+development
  (with-gensyms-for-args (symbol-or-compiled-function)
    `(if (and
           make-multi-value-funcalls-of-defun-simple-fail
           (or (gethash ,symbol-or-compiled-function defun-simples)
               (and (symbolp ,symbol-or-compiled-function)
                    (gethash (symbol-function ,symbol-or-compiled-function)
                             defun-simples))))
         (values
           (ab-lisp::funcall ,symbol-or-compiled-function ,@arguments)
           bogus-value
           bogus-value)
         (ab-lisp::funcall ,symbol-or-compiled-function ,@arguments))))

;;; The `funcall-symbol' macro should be used in all cases where a funcall is
;;; performed whose first argument will be a symbol naming a compiled function
;;; (i.e.  the vast majority of our funcall dispatches).  This macro will
;;; produce an inline funcall on those systems which can produce it.  See also
;;; funcall-simple-function-symbol, defined above.

(defmacro funcall-symbol (symbol &rest arguments)
  #+development `(funcall ,symbol ,@arguments)
  #-development `(funcall-compiled-function (symbol-function ,symbol) ,@arguments))



;;; The macro `funcall-compiled-function' should be used in all cases where a
;;; funcall is performed whose first argument will be a compiled function
;;; object.  This macro produces inline dispatching to the funcalled function on
;;; those system which can support it.

;;; in development, by default, we will make it so that we don't really do this
;;; inlining, so that we can trace functions effectively.  To turn back on
;;; inlining, define the compiler option compiled-fun-in-development.  --yduJ, 5/21/01
(defmacro funcall-compiled-function (compiled-function &rest arguments)
  #+(or (not development) compiled-fun-in-development)
  `(funcall ,compiled-function ,@arguments)
  #+(and development (not compiled-fun-in-development))
  `(funcall (gensym-function-name ,compiled-function) ,@arguments))

;; jh per blm, 2/22/91.  changed ab-lisp::funcall to funcall in order to bypass
;; the funcall in Chestnut Lisp, which conses.





;;;; Function Declarations



;;; The macro `declare-function-type' is used to declare the number of arguments
;;; and returned values of performance critical functions within G2.  By
;;; declaring the number of arguments and values compilers are able to produce
;;; more efficient dispatches and return value processing for these functions.
;;; Note that the declaration of a function must preceed both the function
;;; definition and any uses of the function.  Therefore, these declarations
;;; should be positioned as you would position a macro definition before the use
;;; of a function.

;;; At the moment, Ibuki [an obsolete platform] is the only implementation which
;;; can make use of these declarations.  The hope is that other compilers will
;;; also use them soon.  At this time, Ibuki can only optimize functions which
;;; take a fixed number of arguments and return a single value.  These functions
;;; are turned into nearly direct C function calls (two inline array references
;;; and pointer dereference is the difference between the optimization and a
;;; true C call).  For now, this facility is being used on a test basis only,
;;; and will be declared only for the conser functions, assq, memq, and getfq.
;;; -jra 8/4/89

;;; Ibuki performance improved 66% when these declarations for low level
;;; functions were introduced.  This facility should be broadly used in our code
;;; whenever you have a function which is called very often, which receives a
;;; fixed number of arguments (no optional or keywoard arguments), and which
;;; returns a single value.  Work is being done on the multiple value return
;;; declarations by Ibuki, but we should not expect any improvements in multiple
;;; value return performance in the near future and so shouldn't waste time
;;; putting in declarations.  Further, we should attempt to write single value
;;; returning facilities, since these can be optimized better in all standard
;;; architecture Lisp implementations.  -jra 10/10/89

;;; The sfun facility in Ibuki has an upper limit on the number of arguments of
;;; 16.  If a function has more than 16 arguments, the compiler will silently
;;; refuse to make it into an sfun, and the compile will bomb out with the cc
;;; compile returning a value of 1.  So, the declaration facility below is being
;;; tuned to not emit a declaration if the argument list is more than 16
;;; elements long.  -jra 10/13/89



;;; The macro `declare-function-type' takes a function name, a list of the
;;; argument types accepted by a function, and a list of the value types
;;; returned by the function.  If the number of returned values is not known,
;;; then supply an asterisk for the return values list.

;;; It will register the function declaration so that it can be used by the Lisp
;;; compiler to produce more efficient function calls.  In development it also
;;; sets a property on the function name symbol reflecting the declaration.

;;; In Ibuki, this declaration was used to declare that functions were "simple
;;; functions" when they had a fixed number of type T arguments, and when they
;;; had a single type T return value.

;;; In Chestnut, this declaration is useful when there are a fixed number of
;;; type T arguments and any number of type T return values.  In Chestnut we
;;; have implemented our own "inline-funcall" macro in C which provides direct
;;; inline calling for these functions.  Note that no special compiling is
;;; needed for Lisp functions in Chestnut which are going to be called with this
;;; macro, though for documentation purposes we should still require that
;;; functions to be called with funcall-simple-compiled-function be declared
;;; through this macro.  -jra 4/24/91

(defmacro declare-function-type
          (function-name argument-type-list return-type-list-or-asterisk)
  #-(or development chestnut-3-2-7)
  (declare (ignore function-name argument-type-list
                   return-type-list-or-asterisk))
  #-(or development chestnut-3-2-7)
  nil
  #+(and (not development) chestnut-3-2-7)
  (when (eval-feature :chestnut-trans)
    `(declaim (tcl:ftype
                (function ,argument-type-list
                          ,(if (listp return-type-list-or-asterisk)
                               (if (= 1 (length return-type-list-or-asterisk))
                                   (first return-type-list-or-asterisk)
                                   `(values ,@return-type-list-or-asterisk))
                               `(values &rest t)))
                ,function-name)
              ,@(when (and (listp return-type-list-or-asterisk)
                           (= 1 (length return-type-list-or-asterisk)))
                  `((tx:returns-one-value ,function-name)))))
  #+development
  `(setf (get ',function-name 'function-type-declaration)
         '(,argument-type-list ,return-type-list-or-asterisk)))




;;; The macro `declare-simple-functions' produces function-type declarations for
;;; a set of simple functions, i.e. function which take a fixed number of
;;; arguments of type T and return a single value of type T.

(defmacro declare-simple-functions (&rest functions-and-arg-list-lengths)
  `(progn
     ,@(loop for (function arg-list-length) on functions-and-arg-list-lengths
                                            by #'cddr
             for arg-types = (make-list arg-list-length)
             do (fill arg-types t)
             collect
             `(declare-function-type ,function ,arg-types (t)))))


#+development
(defparameter enable-simple-compiled-function-type-checking nil)

#+development
(defparameter simple-compiled-function-blacklist  nil)

#+development
(defun simple-compiled-function-p (thing)
  (and (compiled-function-p thing)
       #+lucid (let* ((name (sys:procedure-ref thing 1))
                      (ftype (if (symbolp name)
                                 (get name 'function-type-declaration))))
                 (and (consp ftype)
                      (consp (first ftype))
                      (every #'(lambda (x) (eq x t)) (first ftype))
                      (or (equal (second ftype) '(t))
                          (equal (second ftype) '*)            ; Methods
                          (equal (second ftype) '(t t))
                          (equal (second ftype) '(t t t))
                          (equal (second ftype) '(t t t t)))))))

#+development
(defun check-type-of-simple-compiled-function (function)
  (unless (simple-compiled-function-p function)
    (pushnew function simple-compiled-function-blacklist)
    (when enable-simple-compiled-function-type-checking
      (cerror "Ignore it" "~s is not a simple-compiled-function" function))))




;;; The macro `funcall-simple-function-symbol' is a special version of funcall
;;; used only for symbols which name functions with a fixed set of arguments,
;;; returning one value, and which have had their types declared with
;;; declare-function-type.

;;; There is currently an optimization in Ibuki which makes these kind of
;;; function dispatches more than twice as fast as undeclared funcalls.  There
;;; are no such optimizations now for other Lisps.  -jra 10/12/89

;;; This is now an optimization for Chestnut which is similar to the Ibuki
;;; optimization, and so funcall-simple is still worthwhile.  Note however that
;;; symbol-function is itself a slow operation in Chestnut, so caching of
;;; compiled-function pointers and use of funcall-simple-compiled-function is
;;; reccommeded, instead of funcall-simple-function-symbol.  -jra 4/24/91

(defmacro funcall-simple-function-symbol (symbol &rest arguments)
  `(funcall-simple-compiled-function (symbol-function ,symbol) ,@arguments))




;;; Implement the following as an optimized Chestnut operation.  Funcall
;;; compiled function can call functions which take optional arguments and
;;; return multiple values.  Simple functions have argument lists with no
;;; optional or rest arguments, and always return one value.

(defun-for-macro inline-funcall-definition (arg-count mv-p)
  `(def-foreign-function
       (,(intern (format nil "INLINE-~aFUNCALL-~a" (if mv-p "MV-" "") arg-count))
         (:name ,(format nil "inline_funcall_~a" arg-count))
         (:return-type :object)
         ,@(when mv-p `((:protocol :foreign-arguments-function))))
       (inline-funcall-function :object)
     ,@(loop for arg-index from 1 to arg-count
             collect
             `(,(intern
                  (format nil "INLINE-FUNCALL-ARG-~a" arg-index))
                :object))))

(defmacro define-inline-funcall-suite (maximum-number-of-args)
  (cond
    ((and (eval-feature :chestnut-3)
          (eval-feature :chestnut-trans))
     (with-package-specific-symbols (tx |::| def-foreign-function)
       `(progn
          ,@(loop for arg-count from 0 to maximum-number-of-args
                  collect
                  `(progn
                     ,(inline-funcall-definition arg-count nil)
                     ,(inline-funcall-definition arg-count t))))))
    ((not (and (eval-feature :chestnut)
               (eval-feature :chestnut-trans)))
     `(progn
        ,@(loop for arg-count from 0 to maximum-number-of-args
                collect
                (let ((name
                       (intern
                        (format nil "INLINE-FUNCALL-~a" arg-count)))
                      (args
                       (loop for arg-index from 0 to arg-count
                             collect
                             (intern
                              (format nil
                                      "INLINE-FUNCALL-ARG-~a" arg-index)))))
                  `(defun ,name ,args
                     (declare (ignore ,@args))
                     (error
                      "Attempt to call ~a in a non-distribution environment"
                      ',name))))))))

(define-inline-funcall-suite 15)

;; jh, 3/22/93.  Added define-inline-funcall-suite to prevent the formerly
;; ubiquitous "undefined function INLINE-FUNCALL-xx" warnings from the Chestnut
;; translator.  The rev 3.1 Chestnut foreign function interface,
;; tx:def-foreign-function, no longer creates a "glue" function between the Lisp
;; and the C sides of a foreign function call, so we can now call C macros like
;; the inline-funcall-xx suite directly.  (These C macros are currently defined
;; in /bt/ab/runtime/c/gensym.h.)
;;
;; We arrange to call these C macros by defining them with
;; tx:def-foreign-function and declaring argument and return types of :object.
;; This permits us us to pass arguments of C type "Object" to our
;; inline_funcall_xx macros without any type coercion being introduced by the
;; translator.  (Furthermore, the translator no longer emits the "undefined
;; function" warnings, since they have been declared as a foreign function.) Our
;; C macros in turn wrap (*SI_FUNCTION_ENTRY) around their first argument and
;; arrange for that argument to call the remaining arguments directly, as an
;; unadorned C function, bypassing the Lisp function cell entirely.
;;
;; This improvement has the added benefit of supplanting our post-processing
;; step where we removed spurious externs that the translator emitted for each
;; inline-funcall-xx call, since the new translator no longer thinks these are
;; forward-referenced functions.  We will have to remember to include the
;; :object type in the def-gensym-c-function abstraction when we clean it up.

;; jh, 3/23/93.  Arranged for define-inline-funcall-suite to create stub
;; functions in non-distribution, to facilitate metadotting.

(defun-for-macro funcall-simple-compiled-function-body (compiled-function arguments mv-p)
  (cond
    ((eval-feature :chestnut-trans)
     (when (> (length arguments) 15)
       (error "Funcall-simple-compiled-function can only handle 15 ~@
                    arguments, given ~a"
              (length arguments)))
     (let ((fn (intern (format nil "INLINE-~AFUNCALL-~s" (if mv-p "MV-" "") (length arguments)))))
       (if (loop for arg in (cons compiled-function arguments)
                 always (simple-argument-p arg))
           `(,fn ,compiled-function ,@arguments)
           (loop for arg in (cons compiled-function arguments)
                 for let-arg-name = (gensym)
                 collect (list let-arg-name arg) into let-arguments
                 collect let-arg-name into arg-names
                 finally
                   (return
                     `(let ,let-arguments
                        (,fn ,@arg-names)))))))
    (t
     (let ((function (make-symbol "COMPILED-FUNCTION")))
       `(let ((,function ,compiled-function))
          #+fmw (check-type-of-simple-compiled-function ,function)
          #+development
          ,@(when mv-p
              `((when (gethash ,function defun-simples)
                  ;; This should probably be a cerror,
                  ;; but this close to the release, we are
                  ;; making it a warning so that it doesn't
                  ;; interfere with debugging other problems
                  (warn
                    "funcall-simple-multi-valued-compiled-function called on ~S, which was defined with defun-simple"
                          ,function))))
          (funcall-compiled-function ,function ,@arguments))))))

(defmacro funcall-simple-compiled-function (compiled-function &rest arguments)
  #+(or (not development) compiled-fun-in-development)
  (funcall-simple-compiled-function-body compiled-function arguments nil)
  #+(and development (not compiled-fun-in-development))
  `(funcall ,compiled-function ,@arguments))





;;; The verbosely named `funcall-simple-multi-valued-compiled-function' is an
;;; optimized version of funcall for functions which have simple argument lists
;;; (as defined for simple functions), but which are allowed to return multiple
;;; values.

;;; Functions which will be given to this macro should have been type declared
;;; using the declare-function-type macro.

;;; Note that we currently do not achieve any optimizations in Chestnut for
;;; functions which receive single values, and so this macro expands into
;;; funcall-simple-compiled-function.  However, there are optimizations to be
;;; made for single values, so this macro has been made to keep seperate those
;;; funcall dispatches which need multiple values.  -jra 4/30/91

(defmacro funcall-simple-multi-valued-compiled-function
          (compiled-function &rest arguments)
  #+(or (not development) compiled-fun-in-development)
  (funcall-simple-compiled-function-body compiled-function arguments t)
  #+(and development (not compiled-fun-in-development))
  `(funcall ,compiled-function ,@arguments))




;;; The macros `def-side-effect-free-inlined-pseudo-function' and
;;; `def-inlined-pseudo-function-with-side-effects' formalize the practice of
;;; translating forms that look like function calls but which are really
;;; destined to become C macro calls.  A typical example is inline-double-aref,
;;; which has an efficient C macro in /bt/ab/runtime/c/gensym.h.  Also removed
;;; the :chestnut feature so we can metadot these on Lispms.

(defun-for-macro expander-for-def-inlined-pseudo-function
    (lisp-name args lisp-body side-effect-free-p)
  (let* ((specs? (and (consp lisp-name) lisp-name))
         (return-type (if specs? (second specs?) :object))
         (lisp-name (if specs? (car specs?) lisp-name))
         (c-name
           (or (and specs? (third specs?))
               (string-downcase (substitute #\_ #\- (symbol-name lisp-name)))))
         (dff-arglist (loop for arg in args
                            collect (if (atom arg) `(,arg :object) arg)))
         (lisp-arglist (loop for arg in args
                             collect (if (atom arg) arg (car arg)))))
    `(progn
       ,@(when side-effect-free-p
           `((declare-side-effect-free-function ,lisp-name)))

       (defun-for-macro ,lisp-name ,lisp-arglist
         ,@lisp-body)

       ,@(when (and (eval-feature :chestnut-3)
                    (eval-feature :chestnut-trans))
           (with-package-specific-symbols (tx |::| def-foreign-function)
             `((def-foreign-function
                   (,lisp-name
                      (:name ,c-name)
                      (:return-type ,return-type))
                   ,@dff-arglist)))))))

(defmacro def-side-effect-free-inlined-pseudo-function (lisp-name args &body lisp-body)
  (expander-for-def-inlined-pseudo-function
    lisp-name
    args
    lisp-body
    t))

(defmacro def-inlined-pseudo-function-with-side-effects
          (lisp-name args &body lisp-body)
  (expander-for-def-inlined-pseudo-function
    lisp-name
    args
    lisp-body
    nil))




;;; The macro `gensym-return-one' is used when implemented simple functions for
;;; Chestnut translations.  It expands into a C macro of the same name that is
;;; defined in gensym.h.  This C macro will return the one value passed to it
;;; immediately without setting the Values_count Chestnut global variable.  Once
;;; Chestnut has supplied us with a means of doing this within their system, we
;;; can then remove this hack.

;(def-inlined-pseudo-function-with-side-effects gensym-return-one (x)
;  x)

#+(and chestnut-3 chestnut-trans (not chestnut-3-2-7))
(tx::def-foreign-function (gensym-return-one
                            (:name "GENSYM_RETURN_ONE")
                            (:return-type :object))
    (x :object))

;make defun-simple functions runnable at "compile" (vs "load" or "eval") time in Chestnut
#-(and chestnut-3 chestnut-trans (not chestnut-3-2-7))
(defun gensym-return-one (x)
  x)

(defvar-for-macro simple-and-void-defun-table (make-hash-table :test 'eq))

(defvar-for-macro potential-troublemakers (make-hash-table :test 'eq))

(defvar-for-macro defun-simples (make-hash-table :test 'eq))

#+development
(defun-for-macro fill-defun-simple-table ()
  (maphash #'(lambda (key value)
               (case value
                 ((simple def-token)
                  (setf (gethash (symbol-function key) defun-simples) t))
                 (void nil)))
           simple-and-void-defun-table))

(defun-for-macro note-defun-simple (name)
  (setf (gethash name simple-and-void-defun-table) 'simple))

(defun-for-macro note-defun-void (name)
    (setf (gethash name simple-and-void-defun-table) 'void))

(defun-for-macro note-def-token (name)
  (setf (gethash name simple-and-void-defun-table) 'def-token))

#+(and chestnut-3 (not chestnut-3-2-7))
(defun-for-macro caller-must-values-wrap (name mv-context-reason)
  (unless (consp mv-context-reason)
    (break "Bad reason ~S for explicit multiple values: old-style-call ~
              was not cut out successfully" mv-context-reason))
  ;; for now; sooon we will get smart, and only
  ;; wrap in values for tail calls if the
  ;; tail caller is an mv-returning function.
  (case (gethash name simple-and-void-defun-table)
    ((simple def-token)
     t)
    (void
     #+ignore
     (unless (member current-function-name
                     (gethash name potential-troublemakers))
       (user::warn "The defun-void function ~S appears in a multiple-values returning ~
                        position in ~S"
                   name mv-context-reason)
       (push current-function-name
             (gethash name potential-troublemakers)))
     nil) ; It doesn't matter whether VALUES_1 is used or not, so don't.
    (t
     nil)))

#+(and chestnut-3 (not chestnut-3-2-7))
(eval-when (:compile-toplevel)
  (setq timpl::needs-values-wrapping-callback
        #'caller-must-values-wrap))

;;; The function `expand-defun-simple' builds the definition of a simple
;;; function, using the given defun type ('defun, etc).

(defun-for-macro expand-defun-simple (defun-type name lambda-list body)
  (if (loop for arg in lambda-list
            thereis (or (not (symbolp arg))
                        (eq '&optional arg)
                        (eq '&key arg)
                        (eq '&rest arg)))
      (error "Argument lists for simple functions cannot contain &optional, ~
              &key, &rest, or non-symbol arguments.")
      (multiple-value-bind (declaration-and-documentation inner-body)
          (split-defun-body body)
        (let ((use-gensym-return-one-p
                (and (eval-feature :chestnut-3)
                     (not (eval-feature :chestnut-3-2-7))
                     (eval-feature :chestnut-trans)
                     (not (eval-feature :sbcl))      ; why?
                     (not (eval-feature :clozure))   ; why?
                     (not (eval-feature :lispworks)) ; why?
                     (loop for arg in lambda-list
                           never (special-variable-p arg)))))
          #+(and chestnut-3 (not chestnut-3-2-7))
          (when use-gensym-return-one-p
            (note-defun-simple name))
          `(progn
             (declare-function-type ,name
                                    ,(fill (copy-list lambda-list) t)
                                    (t))
             ,(if use-gensym-return-one-p
                  `(,defun-type ,name ,lambda-list
                     ,@declaration-and-documentation
                     (gensym-return-one
                       (block ,name ,@inner-body))
                     nil)
                  `(,defun-type ,name ,lambda-list
                     ,@declaration-and-documentation
                     (values (progn ,@inner-body)))))))))


;;; The macro `defun-simple' is used to define functions which are simple
;;; functions.  Simple functions are those which take a fixed
;;; number of arguments and return one value.  These functions can be compiled
;;; directly into C functions which take their arguments and receive their
;;; values on the C stack, which is more efficient than passing them on the Lisp
;;; stack data structure.

(defmacro defun-simple (name arguments &body declarations-and-forms)
  (expand-defun-simple 'defun name arguments declarations-and-forms))


;;; The macro `defun-simple-allowing-unwind' is a variation on a theme.

(defmacro defun-simple-allowing-unwind (name arguments &body declarations-and-forms)
  (expand-defun-simple 'defun-allowing-unwind name arguments declarations-and-forms))




;;; The macro `defun-void' is used to define functions which return
;;; no values.  This is the moral equivalent of the C return type VOID.
;;; Otherwise all the rules about defun-simple apply to this guy.


(defmacro defun-void (name arguments &body declarations-and-forms)
   (if (loop for arg in arguments
            thereis (or (not (symbolp arg))
                        (eq '&optional arg)
                        (eq '&key arg)
                        (eq '&rest arg)))
      (error "Argument lists for simple or void functions cannot contain ~
              &optional, &key, &rest, or non-symbol arguments.")
      (let (declaration-and-documentation inner-body)
        (multiple-value-setq (declaration-and-documentation inner-body)
          (split-defun-body declarations-and-forms))
        (let (#+(or (not development) (and chestnut-3 (not chestnut-3-2-7)))
              (use-gensym-return-one-p
                (and (eval-feature :chestnut-3)
                     (not (eval-feature :chestnut-3-2-7))
                     (eval-feature :chestnut-trans)
                     (not (eval-feature :sbcl))      ; why?
                     (not (eval-feature :clozure))   ; why?
                     (not (eval-feature :lispworks)) ; why?
                     (loop for arg in arguments
                           never (special-variable-p arg)))))
          #+(and chestnut-3 (not chestnut-3-2-7))
          (when use-gensym-return-one-p
            (note-defun-void name))
          `(progn
             (declare-function-type ,name
                                    ,(fill (copy-list arguments) t)
                                    #+development ()
                                    #-development (null))
             (defun ,name ,arguments
               ,@declaration-and-documentation
               #+development
               (macrolet ((return-from-defun-void ()
                            `(return-from defun-void-ok bogus-value)))
                 (block defun-void-ok
                   (block ,name
                     (return-from defun-void-ok
                       (progn ,@inner-body)))
                   (error "Can't return-from defun-void functions."))
                 bogus-value)
               #-development
               (macrolet ((return-from-defun-void ()
                            `(return-from ,',name nil)))
                 ,@(if use-gensym-return-one-p
                       `(,@inner-body
                          (gensym-return-one nil)
                          nil)
                       `(,@inner-body
                          nil)))))))))




;;; The macro `defun-funcallable' is used to define functions which are funcalled
;;; (lisp functions called by system procedures for instance).

(defmacro defun-funcallable (name arguments &body declarations-and-forms)
  `(progn
     (declare-funcallable-symbol ,name ,arguments)
     (defun ,name ,arguments ,@declarations-and-forms)))

(def-side-effect-free-inlined-pseudo-function (inline-ffloor-1 :double-float)
    ((number :double-float))
  (values (ffloor number)))

(def-side-effect-free-inlined-pseudo-function (inline-floor-1 :fixnum-long)
    ((number :double-float))
  (values (floor number)))

(def-side-effect-free-inlined-pseudo-function (inline-fceiling-1 :double-float)
    ((number :double-float))
  (values (fceiling number)))

(def-side-effect-free-inlined-pseudo-function (inline-ceiling-1 :fixnum-long)
    ((number :double-float))
  (values (ceiling number)))

(def-side-effect-free-inlined-pseudo-function inline-double-from-fix (fixnum)
  (float fixnum 0.0))

(def-side-effect-free-inlined-pseudo-function inline-ifix (fixnum)
  fixnum)

;neither used in g2 or gsi nor defined in rtl/gensym.h
(def-side-effect-free-inlined-pseudo-function inline-get-char-ptr (simple-string)
  simple-string)

(def-inlined-pseudo-function-with-side-effects inline-double-partition
                                               (float-array index byte-array)
  (declare (ignore float-array index))
  (setf (aref byte-array 0) 0)
  (setf (aref byte-array 1) 0)
  (setf (aref byte-array 2) 0)
  (setf (aref byte-array 3) 0)
  1)

(def-side-effect-free-inlined-pseudo-function inline-double-reconstruct
                             (byte0 byte1 byte2 byte3)
  (declare (ignore byte0 byte1 byte2 byte3))
  0.0)


(def-side-effect-free-inlined-pseudo-function (inline-nanp-for-comparison :boolean) ((arg :double-float))
  (nanp arg))





;;; The macro `defun-into-place' is for defining anonymous functions that will
;;; have a compiled function object that will be placed into some location.
;;; Though in a distribution compile these functions will not have a Lisp symbol
;;; associated with them, in development they will be defined under the symbol
;;; given in the first argument.

;;; The compiled function objects for these functions should be fetched from the
;;; place using the macro `compiled-function-in-place'.  In development, the
;;; symbol naming the function will be kept in the place so that trace can work,
;;; but in distribution the compiled function will be kept there, and then
;;; compiled-function-in-place will simply return its argument.

;;; The following variants of defun-into-place provide extra functionality
;;; similar to their defun counterparts: `defun-simple-into-place',
;;; `defun-simple-multi-valued-into-place', and `defun-void-into-place'.

;; Note that the first attempt at this utility failed, since our initial use of
;; flet to define the functions did not allow for the tx:nonrelocating
;; declaration to be applied to the function.  Rick@chestnut assures me now that
;; using labels will make this work out.  Here's hoping.  -jra 12/7/93

#+translator-is-loaded
(defun-for-macro defun-into-place-declarations (name)
  (when (eval-feature :chestnut-trans)
    `((declare (tutil:global-function ,name)
               (tx:nonrelocating ,name)))))

(defmacro defun-into-place ((name place) arguments &body body)
  #+chestnut-3
  `(labels ((,name ,arguments ,@body))
     ,@(defun-into-place-declarations name)
     (setf ,place #',name)
     nil)
  #-chestnut-3
  `(progn
    (defun ,name ,arguments ,@body)
     #+development (setf ,place ',name)
     #-development (setf ,place #',name)
    nil))

(defmacro compiled-function-in-place (defun-into-place-location)
  (if (eval-feature '(or :chestnut-3 (not :development)))
      defun-into-place-location
      `(symbol-function ,defun-into-place-location)))

(defmacro defun-simple-into-place ((name place) arguments &body body)
  #+chestnut-3
  (multiple-value-bind (declaration-and-documentation inner-body)
      (split-defun-body body)
    `(labels ((,name ,arguments
                ,@declaration-and-documentation
                ,@(if (and (eval-feature :chestnut-trans)
                           (not (eval-feature :chestnut-3-2-7)))
                      `((gensym-return-one (block ,name ,@inner-body))
                        nil)
                      inner-body)))
       ,@(defun-into-place-declarations name)
       #+chestnut-3-2-7
       ,@(when (eval-feature :chestnut-trans)
           `((declare (tx:returns-one-value ,name))))
       (setf ,place #',name)
       nil))
  #-chestnut-3
  `(progn
    (defun-simple ,name ,arguments ,@body)
     #+development (setf ,place ',name)
     #-development (setf ,place #',name)
    nil))

(defmacro defun-void-into-place ((name place) arguments &body body)
  #+chestnut-3
  (multiple-value-bind (declaration-and-documentation inner-body)
      (split-defun-body body)
    `(labels ((,name ,arguments
                ,@declaration-and-documentation
                ,@inner-body
                ,@(when (and (eval-feature :chestnut-trans)
                             (not (eval-feature :chestnut-3-2-7)))
                    `((gensym-return-one nil)))
                nil))
       ,@(defun-into-place-declarations name)
       #+chestnut-3-2-7
       ,@(when (eval-feature :chestnut-trans)
           `((declare (tx:returns-one-value ,name))))
       (setf ,place #',name)
       nil))
  #-chestnut-3
  `(progn
     (defun-void ,name ,arguments ,@body)
     #+development (setf ,place ',name)
     #-development (setf ,place #',name)
     nil))

(defmacro defun-simple-multi-valued-into-place
    ((name place) arguments &body body)
  #+chestnut-3
  `(labels ((,name ,arguments ,@body))
     ,@(defun-into-place-declarations name)
     (setf ,place #',name)
     nil)
  #-chestnut-3
  `(progn
    (defun ,name ,arguments ,@body)
     #+development (setf ,place ',name)
     #-development (setf ,place #',name)
    nil))

;; Customers:
;;  def-goto-tag-recorder
;;  def-special-form-converter
;;  def-preferred-instruction-chooser
;;

;; Potential customers:
;;  define-chart-data-point-indicator
;;  def-class-method

;;;






;;;; Basic Macros




;;; `Memq', `assq', and `delq' are Lisp classics, but were foolishly omitted
;;; from Common Lisp.  (Delq should be used only where reclaiming is not an
;;; issue.)

;;; `Memq-macro' and `assq-macro' are macro versions of memq and assq.

;;; `Getfq' is an eq version of getf.  It can not be used with setf.

;; Note that within the macros below we used to use the Lisp machine primitives
;; for memq and assq.  However, this could make the disassemblies of some of
;; our facilities be deceiving, in that we would have function calls in some
;; implementations, but machine instructions on the Lisp machine.  Similarly, in
;; macro expansions, we would get a couple of instructions on the Lisp machine,
;; but a big macro expansion in the delivered product.  Now that we are not
;; shipping G2 on Lisp machines, it makes sense to have the Lisp machine do what
;; everything else does, instead of taking pains to make the Lisp machines run
;; as fast as possible.  -jra 5/8/91

(defmacro default-memq-macro (key list)
  (let ((key-var?
          (if (not (or (constantp key) (symbolp key)))
              (gensym)))
        (current-cons (gensym)))
    `(loop ,@(when key-var? `(with ,key-var? = ,key))
           for ,current-cons = ,list then (cdr-of-cons ,current-cons)
           while ,current-cons
           do
             (when (eq (car-of-cons ,current-cons) ,(or key-var? key))
               (return ,current-cons)))))



;;; `memq-p-macro' is similar to memq, except that in certain cases where the
;;; value of memq would be a list, its value is car of that list. Memq-p-macro
;;; optimizes the case where the second argument is a quoted list by converting
;;; the form to a disjunction of eq tests. E.g. (memq-p-macro x '(a b c) becomes
;;; (or (eq x 'a) (eq x 'b) (eq x 'c)).

(defmacro memq-p-macro (key list)
  (let ((key-var?
          (if (not (simple-argument-p key))
              (gensym)))
        (current-cons (gensym)))
    (if (and (consp list) (eq (car list) 'quote))

        (if key-var?
            `(let ((,key-var? ,key))
               (or . ,(loop for elt in (second list) collect `(eq ,key-var? ',elt))))
            `(or . ,(loop for elt in (second list) collect `(eq ,key ',elt))))

        `(loop ,@(when key-var? `(with ,key-var? = ,key))
               for ,current-cons = ,list then (cdr-of-cons ,current-cons)
               while ,current-cons
               do
                 (when (eq (car-of-cons ,current-cons) ,(or key-var? key))
                   (return ,current-cons))))))





(defmacro memq-macro (key list)
  `(default-memq-macro ,key ,list))

;; As a note for possible (though unlikely) future reference, both Lucid and
;; Zetalisp have memq operations, in the symbols lucid::memq and zeta::memq.  We
;; used to use those operations for Lucid and Lispm implementations, but have
;; switched to keep this Lisps, now only used during development, consistent
;; with the delivered software in Chestnut.  -jra 5/30/91

(declare-side-effect-free-function memq-function)

(defun-simple memq-function (key list)
  (memq-macro key list))

(defmacro memq (key list)
  `(memq-function ,key ,list))

(defun eq-or-memq (x y)
  (declare (eliminate-for-gsi))
  (if (atom y) (eq x y) (memq x y)))

(declare-side-effect-free-function member-equal)

(defun member-equal (key list)
  (declare (eliminate-for-gsi))
  (loop for current-cons on list
        do
    (when (equal (car-of-cons current-cons) key)
      (return current-cons))))

;; Member-equal is currently a lot faster than Chestnut's member with the
;; compiled function equal passed to it.  -jra 1/22/92


;; Note that CLtL states that for alist entries which are NIL, assoc should skip
;; over them.  In other words, a NIL key only matches alist entries which are
;; conses whose car is NIL.  -jra 5/24/91

(defmacro default-assq-macro (key a-list)
  (let ((key-var?
          (if (not (simple-argument-p key))
              (gensym)))
        (alist-entry? (gensym)))
    `(loop ,@(if key-var? `(with ,key-var? = ,key))
           for ,alist-entry? in ,a-list
           do
             (when (and ,alist-entry?
                        (eq (car-of-cons ,alist-entry?)
                            ,(or key-var? key)))
               (return ,alist-entry?)))))

(defmacro assq-macro (key a-list)
  `(default-assq-macro ,key ,a-list))

;; Note that lucid::assq and zeta::assq are available, but unused.  We will
;; consistenty use our macro so that development environments are the same as
;; the distribution.  -jra 5/30/91

(declare-side-effect-free-function assq-function)

(defun-simple assq-function (key a-list)
  (assq-macro key a-list))

(defmacro assq (key a-list)
  `(assq-function ,key ,a-list))

(defun assoc-equal (key list)
  (loop for alist-entry in list doing
    (when (equal (car-of-cons alist-entry) key)
      (return alist-entry))))

(defun assoc-eql (key list)
  (declare (eliminate-for-gsi))
  (loop for alist-entry in list doing
    (when (and alist-entry
               (eql (car-of-cons alist-entry) key))
      (return alist-entry))))

(defmacro getfq-macro (plist indicator &optional default)        ; can't be used in setf
  (let ((indicator-var?
          (if (not (simple-argument-p indicator))
              (make-symbol "INDICATOR")))
        (default-var?
          (if (not (simple-argument-p default))
              (make-symbol "DEFAULT")))
        (l (make-symbol "LIST")))
    `(let* ((,l ,plist)
            ,@(when indicator-var? `((,indicator-var? ,indicator)))
            ,@(when default-var? `((,default-var? ,default))))
       (loop until (or (null ,l) (eq (car-of-cons ,l) ,(or indicator-var? indicator)))
             do (setq ,l (cdr-of-cons (cdr-of-cons ,l))))
       (if ,l
           (car-of-cons (cdr-of-cons ,l))
           ,(or default-var? default)))))

(declare-side-effect-free-function getfq-function-no-default)

(defun-simple getfq-function-no-default (plist indicator)
  (getfq-macro plist indicator))

(declare-side-effect-free-function getfq-function)

(defun-simple getfq-function (plist indicator default)
  (getfq-macro plist indicator default))

(defmacro getfq (plist indicator &optional default)
  (if default
      `(getfq-function ,plist ,indicator ,default)
      `(getfq-function-no-default ,plist ,indicator)))




(defmacro delq (item list &optional count?)        ; speed not important for this
  `(delete ,item ,list :test #'eq ,@(if count? (list :count count?))))

;; Note that Zetalisp has a delq operation in zeta::delq, but we don't use it
;; for reasons of staying consistent with the delivered systems in Chestnut.
;; -jra 5/30

;; A hole in Common Lisp is the absence of a pop-like macro that will delete a
;; specific item from anywhere in the list found at place.  But one could
;; probably define it by means of define-modify-macro!




;;; The macro `memberp' is a version of member which returns true (non-nil)
;;; or false (nil), depending on membership.  It takes the same arguments as
;;; CLtL member.  However, it may or may not return the tail of the list
;;; containing the first arg; i.e., it might just return T in the true case.

(defmacro memberp (&rest member-args)
  `(and (member ,@member-args) t))

;; This macro is primarily here to take advantage of an optimization in
;; Chestnut which inlines constant lists in member calls within an "and", when
;; those calls are not the last form of the and.  Also, Chestnut puts out pesky
;; warnings when it thinks the optimization should be used.  -jra 5/30/91

;; That should be done, then, for that implementation -- in other
;; implementations, it would likely just add extra code, since CLtL's AND has
;; to return its last value.  So I took out of the spec that this returns T in
;; the true case; such a spec would almost never be preferred to the new one.
;; (I will leave it to some other industrious sole to decide to actually fork
;; the implementation -- it's nicer in some ways to to have it be the same on
;; all platforms, and the only one that matters for now is Chestnut.)
;; (MHD 5/31/91)




;;; `Neq' is here, too.

(defmacro neq (x y)
  `(not (eq ,x ,y)))



;;; `True-non-empty-list-p' is true if its arg is a non-null list that terminates
;;; with nil.

(def-substitution-macro true-non-empty-list-p (x)
  (and (not (atom x)) (null (cdr (last x)))))



(defun-simple *f-safe (arg1 arg2)
  (let ((float-result (*e (coerce-to-gensym-float arg1)
                          (coerce-to-gensym-float arg2))))
    (if (or (<e float-result most-negative-fixnum-as-float)
	    (>e float-result most-positive-fixnum-as-float))
	nil
      (floore-first float-result))))




;;; `Multiple-values' are used widely in our code, but there are constructs
;;; around which their use is difficult.

;;; In production code we do not use `multiple-value-prog1', `values-list',
;;; `multiple-value-call', setf of values, or `multiple-value-list'

;;; For example `multiple-value-prog1' is not known to work in Chestnut, it was
;;; known to leak in most Lisp implmentations.  It is very difficult to prove
;;; that it works in a given implementation since testing all combinations with
;;; all contour crossing operations is difficult.

;;; Particularly notable are the macros that do unwind-protect in development
;;; only.  They expand to prog1 in production, and hence never return
;;; multiple-values.  Bummer.

;;; Multiple-value-prog1 was trusted on the lispm so there is code, now
;;; obsolete, which uses it.

;; ben 2/16/94

;; Today we are starting an experiment to see if multiple-value-prog1 can be
;; trusted in Chestnut.  In doing so we are converting a very few cases of prog1
;; to this in critical macros where it's absence is deeply felt. - ben 2/17/94

#+forward-reference
(def-concept multiple-values)


;;; `Without-multiple-values' evaluates it's body and returns the
;;; first value of it's last form.  In development it will emit a
;;; warning if the last form had additional values.

(defmacro without-multiple-values (&body body)
  #+development
  (let ((result (gensym))
        (a (gensym))
        (b (gensym))
        (c (gensym))
        (d (gensym))
        (e (gensym))
        (f (gensym)))
    `(multiple-value-bind (,result ,a ,b ,c ,d ,e ,f)
         (progn ,@body)
       (when (or ,a ,b ,c ,d ,e ,f)
         (development-warning-about-multiple-values))
       ,result))
  #-development
  (let ((result (gensym)))
    `(let ((,result (progn ,@body)))
       ,result)))

#+development
(defun development-warning-about-multiple-values ()
  (warn
    "Discarding additional multiple-values within a without-multiple-values form."))


;;; `Nth-value' returns the nth value, counting from 0, of multiple-value-form.
;;; If multiple-value-form has fewer than n values, nil is returned.

;; Note that this macro requires a constant integer as its first argument.

(defmacro nth-value (n multiple-value-form)
  (loop with variable = (gensym)
        as i from 0 below n
        collect (gensym) into other-variables
        finally
          (return
            `(multiple-value-bind (,@other-variables ,variable)
                 ,multiple-value-form
               (declare (ignore . ,other-variables))
               ,variable))))

;; Forgotten in Common Lisp.

;; It's been added in CLtL II, but is not yet available in most Lisps.  -jra
;; 11/26/90



;;; `Multiple-value-setq-some' is just like multiple-value-setq, except that
;;; it accepts nil in place of a var whose value should be ignored.

(defmacro multiple-value-setq-some (variables form)
  (if (loop for variable? in variables
            always variable?)
      ;; then:
      `(multiple-value-setq ,variables ,form)
      ;; else:
      (loop repeat (length variables)
            collect (gensym) into gensyms
            finally
              (return
                `(multiple-value-bind ,gensyms
                     ,form
                   ,@(loop for variable? in variables
                           as gensym in gensyms
                           as first-time? = t then nil
                           when (and (null variable?) (not first-time?))
                             collect gensym into gensyms-to-ignore
                           finally
                             (return
                               (if gensyms-to-ignore
                                   `((declare (ignore . ,gensyms-to-ignore))))))
                   ,@(loop with rest-of-body-so-far = nil
                           for variable? in variables
                           as gensym in gensyms
                           as first-time? = t then nil
                           do (cond
                                (variable?
                                 (setq rest-of-body-so-far
                                       (cons `(setq ,variable? ,gensym)
                                             rest-of-body-so-far)))
                                (first-time?
                                 (setq rest-of-body-so-far
                                       (cons gensym
                                             rest-of-body-so-far))))
                           finally
                             (return rest-of-body-so-far)))))))

;; This spec should have been Common Lisp's spec for multiple-value-setq.
;; In Lisp Machine Lisp, multiple-value-setq-some is called multiple-value.  CLtL
;; falsely claims that multiple-value-setq is called multiple-value.  The differences
;; between multiple-value-setq-some and multiple-value-setq are exactly the same
;; as between Lisp Machine Lisp's multiple-value and multiple-value-setq.
;; (MHD 12/19/90)

;; It's been added in CLtL II, but is not yet available in most Lisps.  -jra
;; 11/26/90



;;; The macro `pretend-to-use-value' simply tells compilers not to give a warning
;;; that "the value of X is not used".  X should be a symbol.  This can be relied
;;; on to be a very efficient method of accomplishing its "trick", and should be
;;; standardly used for such purposes.  See also multiple-value-setq-some, which
;;; can often be useful in eliminating the variables warned about.

(defvar special-variable-for-use-value-macro nil)        ; always nil

(defmacro pretend-to-use-value (x)
  `(if special-variable-for-use-value-macro
       (setq special-variable-for-use-value-macro ,x)))

;; If faster ways to do this in a given implementation are discovered, they should
;; be employed.  The speed of this is that of a nil check on a special variable,
;; which should be quite fast.

;; I originally thought of the name "use-value", but that led me to discover that
;; Lucid already defined a function of the same name, although I am not sure of
;; its function. (MHD 1/9/91)



;;; The macro `nthcdr-macro' is used inside the defmacro for defstruct-g2
;;; accessor forms.  It expands into N calls to cdr on the result of the form
;;; passed in.

(defmacro nthcdr-macro (n form)
  (cond ((and (constantp n)
              (< (eval n) 20))
         (let ((n-evaled (eval n)))
           (loop with result-form = form
                 repeat n-evaled
                 do
                   (setq result-form (list 'cdr result-form))
                 finally
                   (return result-form))))
        (t
         (let ((result (gensym)))
           `(loop repeat ,n
                  with ,result = ,form
                  do
                    (setq ,result (cdr ,result))
                  finally
                    (return ,result))))))



;;; The macro `set-list-contents' will modify a list such that it contains as
;;; elements the new contents passed as the rest argument.  It is more efficient
;;; than calling setf on the first, then second, etc. in that it will not
;;; traverse the conses of a list more than once.  It returns the passed list.

(defmacro set-list-contents (list &rest new-contents)
  (cond ((null new-contents)
         list)
        ((null (cdr new-contents))
         (if (symbolp list)
             `(progn
                (setf (car ,list) ,(car new-contents))
                ,list)
             (let ((list-evaled (gensym)))
               `(let ((,list-evaled ,list))
                  (setf (car ,list-evaled) ,(car new-contents))
                  ,list-evaled))))
        (t
         (let* ((eval-needed? (not (symbolp list)))
                (new-list (if eval-needed? (gensym) list))
                (current-cons (gensym)))
           `(let* (,@(if eval-needed? `((,new-list ,list)))
                   (,current-cons ,new-list))
              (setf (car ,current-cons) ,(car new-contents))
              ,@(loop with lines = nil
                      for element in (cdr new-contents)
                      do
                        (push `(setq ,current-cons (cdr-of-cons ,current-cons))
                              lines)
                        (push `(setf (car ,current-cons) ,element) lines)
                      finally
                        (return (nreverse lines)))
              ,new-list)))))



;;; The macro `gensym-dstruct-bind' takes a (possibly dotted) cons tree of
;;; symbols, a value argument, and a body, and performs an efficient
;;; destructuring bind of the given symbols to the values in the corresponding
;;; positions of the list returned by the value argument.  If any of the symbols
;;; in the binding list are NIL, then that corresponding value will not be bound
;;; to any symbol.  Note that this is more efficient than evaluating setqs of
;;; the first, second, etc. of the value list, in that the spine conses of the
;;; list are only traversed once.

;; Note that at the present time this expands into a set of nested LET forms.
;; This could be improved upon if all bindings could be made in a single LET*.
;; This would allow the first form of the body to be declarations about the
;; generated variable bindings.  -jra 7/27/89

;; destructuring-bind has long since become part of Common Lisp, albeit with a couple of
;; differences from gensym-dstruct-bind: we wrap the lambda-list and expression
;; in an extra set of parentheses, for one.  But there's at least one other
;; difference: we support nil for members of the expression we don't want to
;; bind to anything, as so:
;;   (gensym-dstruct-bind ((a nil c) '(1 2 3)) (format t "c = ~s, a = ~s~%" c a))
;; The Common Lisp version lacks that feature.  That's what happens when you
;; roll your own, sometimes.  And if there's that difference, it tells me that
;; it's not entirely trivial to prove that there aren't any others.  So, this is
;; going to live on, for now.  -jv, 7/26/07

(defmacro gensym-dstruct-bind ((destructure-pattern value) &body forms)
  (if destructure-pattern
      (let ((list-var (gensym)))
        `(let ((,list-var ,value))
           ,@(destructure-expand
               (list list-var) (list destructure-pattern) forms)))
      `(progn ,value ,@forms)))

(defun-for-macro destructure-expand (list-var-stack pattern-stack body-forms)
  (let* ((list-var (car list-var-stack))
         (pattern (car pattern-stack))
         (pattern-element (if (consp pattern) (car pattern))))
    (cond ((null pattern-stack)
           body-forms)
          ((null pattern)
           (destructure-expand
             (cdr list-var-stack) (cdr pattern-stack) body-forms))
          ((symbolp pattern)
           `((let ((,pattern ,list-var))
               ,@(destructure-expand
                   (cdr list-var-stack) (cdr pattern-stack) body-forms))))
          ((null pattern-element)
           (setf (car pattern-stack) (cdr pattern))
           (cons `(setq ,list-var (cdr ,list-var))
                 (destructure-expand
                   list-var-stack pattern-stack body-forms)))
          ((symbolp pattern-element)
           (setf (car pattern-stack) (cdr pattern))
           (if (and (cdr pattern) (symbolp (cdr pattern)))
               `((let ((,pattern-element (car ,list-var))
                       (,(cdr pattern) (cdr ,list-var)))
                   ,@(destructure-expand
                       (cdr list-var-stack) (cdr pattern-stack) body-forms)))
               `((let ((,pattern-element (car ,list-var)))
                   ,@(if (cdr pattern)
                         `((setq ,list-var (cdr ,list-var))))
                   ,@(destructure-expand
                       list-var-stack pattern-stack body-forms)))))
          ((consp pattern-element)
           (let ((sub-list-var (gensym)))
             (setf (car pattern-stack) (cdr pattern))
             `((let ((,sub-list-var (car ,list-var)))
                 ,@(if (cdr pattern)
                       `((setq ,list-var (cdr ,list-var))))
                 ,@(destructure-expand (cons sub-list-var list-var-stack)
                                       (cons pattern-element pattern-stack)
                                       body-forms))))))))


;;; The macro `destructuring-setq' takes a (possibly dotted) cons tree of symbols,
;;; a value argument, and a body, and performs an efficient setq of the given
;;; symbols to the values in the corresponding positions of the list returned by
;;; the value argument.  If any of the symbols in the binding list are NIL, then
;;; that corresponding value will not be setq to any symbol.  Note that this is
;;; more efficient than evaluating setqs of the first, second, etc.  of the value
;;; list, in that the spine conses of the list are only traversed once.  The value
;;; returned by destructuring-setq is undefined.  Note that the syntax is closer
;;; to Common Lisp than gensym-dstruct-bind is to destructuring-bind (cf. CLtL/2e p205).

;; jh per bah, 8/13/91.  Destructuring-setq is an adaptation of Jim's
;; gensym-dstruct-bind.

(defmacro destructuring-setq (destructure-pattern value)
  (if destructure-pattern
      (let ((list-var (gensym)))
        `(let ((,list-var ,value))
           ,@(destructuring-setq-expand
               (list list-var)
               (list destructure-pattern))))
      nil))

(defun-for-macro destructuring-setq-expand (list-var-stack pattern-stack)
  (let* ((list-var (car list-var-stack))
         (pattern (car pattern-stack))
         (pattern-element (if (consp pattern) (car pattern))))
    (cond ((null pattern-stack)
           nil)
          ((null pattern)
           (destructuring-setq-expand
             (cdr list-var-stack) (cdr pattern-stack)))
          ((symbolp pattern)
           `((setq ,pattern ,list-var)
             ,@(destructuring-setq-expand
                 (cdr list-var-stack) (cdr pattern-stack))))
          ((null pattern-element)
           (setf (car pattern-stack) (cdr pattern))
           (cons `(setq ,list-var (cdr ,list-var))
                 (destructuring-setq-expand
                   list-var-stack pattern-stack)))
          ((symbolp pattern-element)
           (setf (car pattern-stack) (cdr pattern))
           (if (and (cdr pattern) (symbolp (cdr pattern)))
               `((setq ,pattern-element (car ,list-var))
                 (setq ,(cdr pattern) (cdr ,list-var))
                 ,@(destructuring-setq-expand
                     (cdr list-var-stack) (cdr pattern-stack)))
               `((setq ,pattern-element (car ,list-var))
                 ,@(if (cdr pattern)
                       `((setq ,list-var (cdr ,list-var))))
                 ,@(destructuring-setq-expand
                     list-var-stack pattern-stack))))
          ((consp pattern-element)
           (let ((sub-list-var (gensym)))
             (setf (car pattern-stack) (cdr pattern))
             `((let ((,sub-list-var (car ,list-var)))
                 ,@(if (cdr pattern)
                       `((setq ,list-var (cdr ,list-var))))
                 ,@(destructuring-setq-expand
                     (cons sub-list-var list-var-stack)
                     (cons pattern-element pattern-stack)))))))))






;;; `Build-ab-symbol' is a defun-for-macro which provides a short building
;;; symbols in macros.  Constructs like (intern (format nil ...)) are replaced
;;; with (build-symbol ...).  For example
;;;   (let ((name 'foo)
;;;         (n 12)))
;;;     (build-symbol "fast-Stuff" name :bar N))
;;;    --> FAST-STUFF-FOO-12
;;; Symbols are interned in package AB, and everything is put in uppercase.

;; This must be defined after funcall is finished.

(defun-for-macro build-ab-symbol (&rest components)
  (declare (eliminate-for-no-macros-gsi))
  (intern
    (ab-lisp::format nil "~@:(~{~A~^-~}~)" components)
    (find-package "AB")))

(defun-for-macro build-ab-symbol-no-hyphens (&rest components)
  (declare (eliminate-for-no-macros-gsi))
  (intern
    (ab-lisp::format nil "~@:(~{~A~^~}~)" components)
    (find-package "AB")))


;;; `inline-tree-eq' is a predicate that encapsulates many varieties
;;; of cons-tree comparison without introducing a function-call and
;;; improving readablility of complex tests.  It also supports
;;; wildcarding through use of the symbol '*.

(defun-for-macro expand-inline-tree-eq (var tree)
  (cond ((consp tree)
         `(and (consp ,var)
               (let ((the-cons ,var))
                 (and
                   (progn
                     (setq ,var (car-of-cons the-cons))
                     ,(expand-inline-tree-eq var (car tree)))
                   (progn
                     (setq ,var (cdr-of-cons the-cons))
                     ,(expand-inline-tree-eq var (cdr tree)))))))
        ((null tree)
         `(null ,var))
        ((eq tree '*)
         t)
        (t                   ; this includes the fixnum case - see JRA
         `(eq ,var ',tree))))

(defmacro inline-tree-eq (thing tree)
  `(let ((thing ,thing))
     ,(expand-inline-tree-eq 'thing tree)))












;;;; Output recording (all #+development).


#+Development
(progn


(defvar output-recording-enabled t)
(defvar output-recording-id-table (make-hash-table) "Table of object->id")
(defvar output-recording-object-table (make-hash-table) "Table of id->object")
(defvar output-recording-next-id 1000)
(defvar output-recording-minimum-id output-recording-next-id)


;;; "Exported" functions.

(defun enable-output-recording ()
  "Remember complex lisp objects whenever they are printed."
  (setq output-recording-enabled t))

(defun disable-output-recording ()
  "Stop remembering lisp objects as they are printed."
  (setq output-recording-enabled nil))

(defun clear-output-history ()
  "Clear all output histories, so that their object may be GCed.  Notice that
 this means that if an object is printed again, it will acquire a new ID."
  ;; We notice invalidated ID's by keeping the counter going over clear's.
  (setf output-recording-minimum-id output-recording-next-id)
  (#-ansi-cl lisp:clrhash #+ansi-cl common-lisp:clrhash output-recording-id-table)
  (#-ansi-cl lisp:clrhash #+ansi-cl common-lisp:clrhash output-recording-object-table))

(defun show-output-history (&optional (how-many 20))
  (loop for id from (- output-recording-next-id 1) by -1
        repeat how-many
        for object = (output-recording-get-object id)
        when object
          do (format t " [~d] ~s~%" id object))
  (values))


;;; "Internal" functions.

(defun output-recording-get-object (id)
  (values (gethash id output-recording-object-table)))

(defun output-recording-get-id (object)
  (or
    (gethash object output-recording-id-table)
    (output-recording-store-object object)))

(defun output-recording-store-object (object)
  (let ((id output-recording-next-id))
    (setf (gethash id output-recording-object-table) object
          (gethash object output-recording-id-table) id)
    (incf output-recording-next-id)
    id))

(defun abbrev-of-internal-number (frame)
  (modf (output-recording-get-id frame) 100))

)




;;;; Printing random objects.



;;; The macro `printing-random-object' ensures that random objects printed
;;; follow the #< ... @id> notation while recording output, and as #< ...
;;; pointer> otherwise.

(defmacro printing-random-object ((object stream) &body body)
  (if (eq current-system-being-loaded 'gsi)
      `(let ((.object. ,object)
             (.stream. ,stream))
         (print-random-object-prefix-for-gsi .object. .stream.)
         ,@body
         (print-random-object-suffix-for-gsi .object. .stream.))
      `(let ((.object. ,object)
             (.stream. ,stream))
         (print-random-object-prefix .object. .stream.)
         ,@body
         (print-random-object-suffix .object. .stream.))))


;;; The tx:def-foreign-function `pointer-chestnut-internal' gives us access to
;;; the Chestnut rtl routine PCTpointer(). PCT_POINTER_1 is actually a macro
;;; defined in rtl/c/gensym.h

#+(and chestnut-3 chestnut-trans)
(tx::def-foreign-function (pointer-chestnut-internal
                            (:name "PCT_POINTER_1")
                            (:return-type :object))
    (thing :object))

;; Look at sxhash-symbol for hints on how to do this, or come by and ask.  -jra
;; 8/18/94


;;; The function `%pointer' returns the address of the header of the given lisp
;;; object, as an integer, possibly a bignum.

(defun %pointer (lisp-object)
  #+(and chestnut-3 chestnut-trans)
  (pointer-chestnut-internal lisp-object)
  #+(and (not (and chestnut-3 chestnut-trans)) lucid)
  (sys:%pointer lisp-object)
  #+(and (not (and chestnut-3 chestnut-trans)) allegro)
  (excl::pointer-to-address lisp-object)
  #+(and (not (and chestnut-3 chestnut-trans)) lispworks)
  (system::object-address lisp-object)
  #+(and (not (and chestnut-3 chestnut-trans)) sbcl)
  (sb-kernel::get-lisp-obj-address lisp-object)
  #+(and (not (and chestnut-3 chestnut-trans)) clozure)
  (ccl::%address-of lisp-object)
  #-(or chestnut-3 chestnut-trans
        lucid allegro lispworks sbcl clozure)
  (progn lisp-object 0))


(defun print-random-object-prefix (object stream)
  (declare (ignore object) (eliminate-for-gsi))
  (format stream "#<"))

(defun print-random-object-suffix (object stream)
  (declare (eliminate-for-gsi))
  #+Development
  (if output-recording-enabled
      (format stream " @~d>" (output-recording-get-id object))
      (format stream " ~x>" (%pointer object)))
  #-Development
  (format stream " ~x>" (%pointer object)))

(defun print-random-object-prefix-for-gsi (object stream)
  (declare (ignore object stream))
  (format t "#<"))

(defun print-random-object-suffix-for-gsi (object stream)
  (declare (ignore stream))
  #+Development
  (if output-recording-enabled
      (format t " @~d>" (output-recording-get-id object))
      (format t " ~x>" (%pointer object)))
  #-Development
  (format t " ~x>" (%pointer object)))



;;;; Optimizing Constant Creation




;;; In our code there are many large constants, mainly cons trees and arrays.
;;; These constants are not always handled efficiently by the underlying Lisp
;;; system.  This code optimizes constant creation by taking a constant and
;;; emitting Lisp code that will recreate that constant when executed.  The
;;; emitted code is smaller than the constant itself.  Note that this macro will
;;; never terminate when given circular data structures.

;;; Note that whenever this code is executed, its CONSES (read newly creates)
;;; the constant.  So this code should not be called from within functions that
;;; need to execute garbage-free.  In current Gensym code, this should only be
;;; used at top level or in initialization functions that are called only once.

;;; The need for this code has arisen because of problems with Chestnut's
;;; constant emitter.  For large trees of conses, it works by emitting code
;;; calling cons for each cons in the tree.  For large arrays, it works by
;;; creating the array and emitting setf svref calls to set each element into
;;; the array.  Both of these techniques drive the C optimizers on many
;;; platforms out of their little minds, sometimes taking as much as 80 hours to
;;; compile one file worth of this code.  This tool will fix this problem, and
;;; give us an asset we can use in the future.

;;; The idea behind this code is to have a string containing characters which
;;; act as byte codes for an interpreter which executes the byte codes to create
;;; constants.  Many kinds of constants will be handled here, but not all of
;;; them.  For those constants which are not handled directly in the byte codes,
;;; there will be a vector in which arbitrary constants can be registered.  Then
;;; there will be a byte code which can fetch a constant from the vector and
;;; insert it into the constant being constructed.  Our goal will be to handle
;;; as many constants in the byte codes as is possible, but to have the fallback
;;; position of using the native Lisp's system where convenient.




;;; The macro `optimize-constant' takes a single constant argument (quoted if
;;; necessary) and expands into code which will return a newly created constant
;;; equal to the argument.

(defvar-for-macro constant-op-chars nil)

(defvar-for-macro constant-vectored-constants nil)

(defmacro optimize-constant (constant-arg &optional force-optimize-constant-p)
  #-chestnut-3-2-7 force-optimize-constant-p
  (cond
    ((not (constantp constant-arg))
     (warn "Optimize-constant received an argument which is not constantp: ~a"
           constant-arg)
     constant-arg)
    ;; Just return trivial cases which should not have been handed in here.
    (#+chestnut-3-2-7
     (not force-optimize-constant-p)
     #-chestnut-3-2-7
     (or (fixnump constant-arg)
         (stringp constant-arg)
         (floatp constant-arg))
     constant-arg)
    (t
     (let ((constant (eval constant-arg))
           (constant-op-chars nil)
           (constant-vectored-constants nil))
       (constant-emit-constant constant)
       (let ((op-codes (collect-constant-op-chars (nreverse constant-op-chars))))
         (if (null constant-vectored-constants)
             `(regenerate-optimized-constant ,op-codes)
             `(progn
                (clear-optimized-constants)
                ,@(loop for vectored-constant in constant-vectored-constants
                        collect
                        `(push-optimized-constant ',vectored-constant))
                (regenerate-optimized-constant ,op-codes))))))))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant optimized-constant-vector-length 1300))

;; Note: I upped the length from 1024 to 1200 today. It's the first time this
;; has been increased since 1995. The addition of 5 new def-structures caused
;; the limit to be reached (loading module G2-METERS). (MHD 11/1/04)

;; Note: I upped the length from 1200 to 1300 today. Because G2 development
;; build report error in g2-meters.lisp when fill data into this vector:
;; 
;; Loading G2-METERS              [248/257] 
;; Error: Error initializing constants, vector overflow at 1200.
;; 
;; This is a potential G2 bug, only development build process could find it!
;; -- Chun Tian (binghe), 2009/10/9

;; `extend-procedure-grammar' uses them at runtime in threads.
(defvar optimized-constant-vector (make-array optimized-constant-vector-length))
(defvar optimized-constant-vector-index 0)

(defvar optimized-constant-pc 0)         ; verified as special
(defvar optimized-constant-op-codes nil) ; verified as special




;;; `Copy-optimized-constant' creates a fresh data structure that is just like
;;; the constant it is passed.  The constant may include simple vectors,
;;; strings, cons cells, numbers and symbols.  Each time this is invoked a fresh
;;; copy is created.  The result may be modified.  These are allocated from the
;;; outermost heap, and may not be reclaimed.

;;; One application for this is to build load time tables, that are then touched up
;;; before they are used.

(defmacro copy-optimized-constant (constant-arg)
  `(optimize-constant ,constant-arg t))




;;; The macro variable `standard-symbol-candidates?' holds either NIL or a
;;; Common Lisp eq hash table to be used in collecting a set of symbols that
;;; should be considered for inclusion in the set of standard symbols.  If you
;;; want to collect a set of potential standard symbols, load LOAD, change the
;;; initialization of standard-symbols-for-optimized-constant to NIL in the
;;; appropriate patches file then execute the following line.

;;; (setq standard-symbol-candidates? (make-hash-table :test #'eq :size 15000))

;;; Perform a full recompile, then call show-standard-symbol-candidates, and
;;; write-standard-symbol-initializations as desired.

(defvar-for-macro standard-symbol-candidates?
  #-development
  (make-hash-table :test #'eq :size 15000)
  #+development
  nil)




;;; The function for macro `collect-standard-symbol-init-string' will iterate
;;; over all symbols in the standard-symbol-candidates? hash table, and will
;;; return code which generates a string to initialize those standard symbols
;;; when given to regenerate-standard-symbols.  This function takes one optional
;;; argument, which is a lower limit on the number of references to a symbol
;;; needed to include it in this set, which defaults to 1.  Note that symbols
;;; with function definitions cannot be optimized in this way, since the
;;; presence of the quoted symbol in the source signals Chestnut to install the
;;; symbol-function slot of that symbol.

(defun-for-macro collect-standard-symbol-init-string
    (&optional (required-references 1))
  (when (null standard-symbol-candidates?)
    (return-from collect-standard-symbol-init-string nil))
  (let ((symbol-occurance-alist nil))
    (maphash #'(lambda (key value)
                 (when (and (>=f value required-references)
                            (not (special-variable-p key))
                            (or (not (fboundp key))
                                (macro-function key)))
                   (push (cons key value) symbol-occurance-alist)))
             standard-symbol-candidates?)
    (setq symbol-occurance-alist
          (sort symbol-occurance-alist
                #'(lambda (entry1 entry2)
                    (or (>f (cdr entry1) (cdr entry2))
                        (and (=f (cdr entry1) (cdr entry2))
                             (string< (symbol-name (car entry1))
                                      (symbol-name (car entry2))))))))
    (loop with last-package = 'none
          with constant-op-chars = nil
          with constant-vectored-constants = nil
          for (symbol) in symbol-occurance-alist
          for package = (symbol-package symbol)
          initially
            (constant-emit-constant (length symbol-occurance-alist))
          do
      (when (neq package last-package)
        (unless (eq last-package 'none)
          (constant-emit-constant 0))
        (constant-emit-constant (package-name package))
        (setq last-package package))
      (constant-emit-constant (symbol-name symbol))
          finally
            (constant-emit-constant 0)
            (constant-emit-constant 0)
            (when constant-vectored-constants
              (warn "Bad standard symbol set. Continuing with no standard symbols.")
              (return nil))
            (return (collect-constant-op-chars
                      (nreverse constant-op-chars))))))




;;; The function `regenerate-standard-symbols' generates a simple vector of
;;; symbols to be used when regenerating constants using the given constant
;;; op-codes.  The format of the value of its argument is a string or list of
;;; strings as would be given to regenerate-optimized-constant.  Several
;;; constants will be held within these strings, in the following order with the
;;; described meaning:

;;;   1.  fixnum => the length of the standard-symbols array
;;;   2.  string or 0 => a package name or zero if no more packages
;;;   3.  string or 0 => a symbol name, or zero if no more symbols in this
;;;          package
;;;   4.  Go to 2.

(defun regenerate-standard-symbols (standard-symbols-input)
  (if standard-symbols-input
      (loop with optimized-constant-pc = 0
            with optimized-constant-op-codes = standard-symbols-input
            with new-array = (make-array (read-optimized-constant))
            with index fixnum = 0
            for package-name = (read-optimized-constant)
            until (fixnump package-name)
            for package = (find-package package-name)
            do
        (loop for symbol-name = (read-optimized-constant)
              until (fixnump symbol-name)
              do
          (setf (svref new-array index) (intern symbol-name package))
          (incff index))
            finally (return new-array))
      nil))




;;; The function for macro `show-standard-symbol-candidates' will print a sorted
;;; list of the symbol candidates, with the most frequently used candidates
;;; printed first.

(defun-for-macro show-standard-symbol-candidates (output-file)
  (when (null standard-symbol-candidates?)
    (write-line "The variable standard-symbol-candidates? contains NIL.")
    (return-from show-standard-symbol-candidates nil))
  (let ((symbol-occurance-alist nil))
    (maphash #'(lambda (key value) (push (cons key value) symbol-occurance-alist))
             standard-symbol-candidates?)
    (setq symbol-occurance-alist
          (sort symbol-occurance-alist
                #'(lambda (entry1 entry2)
                    (or (>f (cdr entry1) (cdr entry2))
                        (and (=f (cdr entry1) (cdr entry2))
                             (string< (symbol-name (car entry1))
                                      (symbol-name (car entry2))))))))
    (with-open-file (output output-file :direction :output)
      (loop for entry in symbol-occurance-alist do
        (format output "~s ~d~%" (car entry) (cdr entry))))))




;;; The macro `generate-standard-symbol-vector-or-nil' is used to emit code that
;;; will initialize the standard-symbols for optimize-constant.

;;; This is a very unusual macro in that it expands differently during
;;; development, the macro pass of distribution compiles, and the translation
;;; pass of distribution compiles.  In the development and macro pass, it
;;; expands to NIL.  In the translation pass, it expands to code that will
;;; generate a set of standard symbols from the standard-symbol-candidates.  By
;;; doing this, we can still share binaries between G2, TW, and GSI in
;;; development, and we can have accurate symbol sets tailored to each during
;;; distribution compilations.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro generate-standard-symbol-vector-or-nil ()
  (if (eval-feature '(or :development (not :no-macros)))
      nil
      `(regenerate-standard-symbols ,(collect-standard-symbol-init-string))))
)




;;; The parameter `standard-symbols-for-optimized-constant?' holds an
;;; unoptimized simple-vector of symbols that are used often enough in our code
;;; to warrant special treatment in the constant emitter.  Including a symbol in
;;; this array ensures that references to them in optimized constants are
;;; handled more efficiently than they would otherwise be handled.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter standard-symbols-for-optimized-constant?
  (generate-standard-symbol-vector-or-nil)))




;;; The macro variable `standard-symbol-indices' is a hash-table for looking up
;;; the index into the standard-symbols for a symbol.  It is mutated only by the
;;; macro initialize-standard-symbol-indices, and then only at macroexpand time.

#-no-macros
(defvar standard-symbol-indices (make-hash-table :test #'eq :size 100))




;;; The macro `initialize-standard-symbol-indices' will modify the value of the
;;; variable standard-symbol-indicies to set up a hash table of standard-symbols
;;; to indices to those symbols within the standard-symbols-for-optimized-
;;; constant? vector.  This is done this way so that an accurate hash table can
;;; be constructed during the second pass of a compile, but still have no code
;;; for this emitted into the final product.  -jra 4/18/94

(defmacro initialize-standard-symbol-indices ()
  (let* ((standard-symbol-count
           (if standard-symbols-for-optimized-constant?
               (length standard-symbols-for-optimized-constant?)
               0))
         (new-hash (make-hash-table
                     :test #'eq
                     :size (max standard-symbol-count 100))))
    (loop for index from 0 below standard-symbol-count do
      (setf (gethash (svref standard-symbols-for-optimized-constant? index)
                     new-hash)
            index))
    (setq standard-symbol-indices new-hash)
    nil))

(initialize-standard-symbol-indices)




;;; The function for macro `collect-constant-op-chars' takes a list of character
;;; op-codes for optimize-constant and returns code which, when evaluated,
;;; produces the opcode string or list of strings for the given op-codes.  This
;;; is an internal to the optimize constant system.

(defun-for-macro collect-constant-op-chars (op-codes-list)
  (let ((length (length op-codes-list)))
    (cond ((<=f length 128)
           (concatenate 'string op-codes-list))
          ((<=f length 6400)
           (cons
             'list
             (loop with index = 0
                   while (<f index length)
                   collect
                   (loop with string = (make-string (min 128 (-f length index)))
                         for minor-index from 0 below 128
                         while op-codes-list
                         do
                     (incff index)
                     (setf (schar string minor-index) (pop op-codes-list))
                         finally (return string)))))
          ;; Calling "list" with more than 50 arguments won't compile on some
          ;; machines.  For really big lists, split them up into sub-calls to
          ;; list, then nconc.
          (t
           (cons
             'nconc
             (loop with index = 0
                   while (<f index length)
                   collect
                   (cons
                     'list
                     (loop while (<f index length)
                           repeat 50
                           collect
                           (loop with string = (make-string (min 128 (-f length index)))
                                 for minor-index from 0 below 128
                                 while op-codes-list
                                 do
                             (incff index)
                             (setf (schar string minor-index) (pop op-codes-list))
                                 finally (return string))))))))))




;;; The function for maction constant-emit-constant is an internal of this
;;; utility.  It takes a constant and emits character op codes into
;;; constant-op-chars which can be used to reconstruct the constant.  The
;;; characters emitted are always printable numeric or alphabetic characters.
;;; The character op-codes are as follows.  Note that only the numeric
;;; characters and upper and lowercase alphabetic characters are used in this
;;; string.

;;;   0 => NIL
;;;   1 => proper list.  The length is the next constant, the elements follow.
;;;   2 => dotted list.  The cons count is next, followed by list elements and
;;;     the final element for the cdr of the last cons
;;;   3 => fixnums, +-*/, 0-9, A-Z, and a-x are base 64 digits, y terminates
;;;     positive fixnums, z terminates negative
;;;   4 => simple-vector, length followed by elements
;;;   + => (simple-array (unsigned-byte 16), length followed by elements
;;;   5 => simple-string, length followed by characters
;;;   6 => character, it follows
;;;   7 => simple-string of non-standard characters, length followed by
;;;     char-codes
;;;   8 => standard-symbol, index into standard-symbols-for-optimized-constant
;;;   9 => arbitrary constant from constant-vector, index into vector
;;;   a-z => small fixnums -10 through 15

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant-for-macro constant-fixnum-digits
      "+-*=0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx"))

(defmacro fixnum-digit-char-from-fixnum (fixnum)
  `(schar constant-fixnum-digits ,fixnum))

(defmacro fixnum-digit-fixnum-from-char (char)
  `(case (the character ,char)
     ,@(loop for index from 0 below (length constant-fixnum-digits)
             collect
             `((,(schar constant-fixnum-digits index)) ,index))
     ;; prevent return NIL
     (otherwise ,(length constant-fixnum-digits))))

(defun-for-macro constant-emit-constant (constant)
  (typecase constant
    (null
     (push #\0 constant-op-chars))
    (cons
     (let ((cons-count (loop for c = constant then (cdr-of-cons c)
                             while (consp c) count t)))
       (push (if (null (cdr-of-cons (last constant))) #\1 #\2) constant-op-chars)
       (constant-emit-constant cons-count)
       (loop for cons = constant then (cdr-of-cons cons)
             while (consp cons)
             do
         (constant-emit-constant (car-of-cons cons))
             finally
               (when (not (null cons))
                 (constant-emit-constant cons)))))
    (fixnum
     (cond
       ((and (>=f constant -10) (<=f constant 15))
        (push (code-char (+f (char-code #\a) (+f constant 10)))
              constant-op-chars))
       ((=f constant most-negative-fixnum)
        (push #\A constant-op-chars))
       (t
        (let ((terminal-char (cond ((>f constant 0)
                                    #\y)
                                   (t
                                    (setq constant (-f constant))
                                    #\z))))
          (push #\3 constant-op-chars)
          (loop with digit-chars = nil
                while (>f constant 0)
                for digit = (logandf constant 63)
                do
            (push (fixnum-digit-char-from-fixnum digit) digit-chars)
            (setq constant (ashf constant -6))
                finally
                  (setq constant-op-chars
                        (nconc (nreverse digit-chars) constant-op-chars)))
          (push terminal-char constant-op-chars)))))
    ((array (unsigned-byte 16))
     (push #\+ constant-op-chars)
     (constant-emit-constant (length constant))
     (loop for index from 0 below (length constant) do
       (constant-emit-constant (aref constant index))))
    (simple-vector
     (push #\4 constant-op-chars)
     (constant-emit-constant (length constant))
     (loop for index from 0 below (length constant) do
       (constant-emit-constant (svref constant index))))
    (simple-string
     (cond ((loop with standard-non-alphabetic-chars = "!\"#%&'()*+,-./:;<=>?@[\\]^_`{|}~
 "
                  for index from 0 below (length constant)
                  for char = (schar constant index)
                  always (or (alphanumericp char)
                             (loop for subindex from 0 below (length standard-non-alphabetic-chars)
                                   thereis (char= char (schar standard-non-alphabetic-chars subindex)))))
            (push #\5 constant-op-chars)
            (constant-emit-constant (length constant))
            (loop for index from 0 below (length constant) do
              (push (schar constant index) constant-op-chars)))
           (t
            (push #\7 constant-op-chars)
            (constant-emit-constant (length constant))
            (loop for index from 0 below (length constant) do
              (constant-emit-constant (char-code (schar constant index)))))))
    (character
     (push #\6 constant-op-chars)
     (push constant constant-op-chars))
    (t
     (let ((standard-symbol-index?
             (if (symbolp constant)
                 (gethash constant standard-symbol-indices))))
       (cond
         (standard-symbol-index?
          (push #\8 constant-op-chars)
          (constant-emit-constant standard-symbol-index?))
         (t
          (push #\9 constant-op-chars)
          (let ((existing-entry? (position constant
                                           constant-vectored-constants
                                           :test #'equal)))
            (cond (existing-entry?
                   (constant-emit-constant existing-entry?))
                  (t
                   (when (and (symbolp constant) standard-symbol-candidates?)
                     (setf (gethash constant standard-symbol-candidates?)
                           (1+ (gethash constant standard-symbol-candidates? 0))))
                   (constant-emit-constant (length constant-vectored-constants))
                   (if constant-vectored-constants
                       (setf (cdr (last constant-vectored-constants))
                             (list constant))
                       (setf constant-vectored-constants (list constant))))))))))))




;;; The following functions implement the runtime portions of the constant
;;; optimizer.  The function `clear-optimized-constants' will clear the global
;;; variable used to store an index into the vector of optimized constants.  The
;;; function `push-optimized-constant' takes a Lisp object, puts it into the
;;; vector of optimized constants, and increments the index.  The function
;;; `regenerate-optimized-constant' takes either a string or a list of strings
;;; and executes the op-codes in them to cons up a new copy of the originally
;;; given constant.

(defun-void clear-optimized-constants ()
  (setq optimized-constant-vector-index 0))

(defmacro optimized-constant-error (&rest args)
  `(current-system-case
     (gsi (format t ,@args)  ; why is this special handling necessary?! (MHD)
          (exit-lisp-process 0)
          nil)
     (t
       ;; note: this case applies for G2, TW, and also any system in development
       ;; at load time (when current-system-name is nil). (MHD 11/1/04)
       (error ,@args))))


(defun-void push-optimized-constant (constant)
  (when (>=f optimized-constant-vector-index
             (length-of-simple-vector optimized-constant-vector))
    (optimized-constant-error
      "Error initializing constants, vector overflow at ~a."
      optimized-constant-vector-index))
  (setf (svref optimized-constant-vector optimized-constant-vector-index)
        constant)
  (incff optimized-constant-vector-index))

(defun-simple regenerate-optimized-constant (op-codes)
  (setq optimized-constant-pc 0)
  (setq optimized-constant-op-codes op-codes)
  (read-optimized-constant))

(defmacro read-next-constant-op-char ()
  `(let* ((op-code-string (if (consp optimized-constant-op-codes)
                              (car-of-cons optimized-constant-op-codes)
                              optimized-constant-op-codes))
          (op-code-char (schar op-code-string optimized-constant-pc)))
     (declare (type character op-code-char))
     (incff optimized-constant-pc)
     (when (>=f optimized-constant-pc (length-of-simple-string op-code-string))
       (setq optimized-constant-pc 0)
       (if (consp optimized-constant-op-codes)
           (setq optimized-constant-op-codes
                 (cdr-of-cons optimized-constant-op-codes))
           (setq optimized-constant-op-codes nil)))
     op-code-char))

(defun-simple read-optimized-constant ()
  (let ((dispatch-char (read-next-constant-op-char)))
    (declare (character dispatch-char))
    (case dispatch-char
      ((#\0)
       nil)
      ((#\1)
       (loop with new-list = (make-list (read-optimized-constant))
             for cons on new-list
             do
         (setf (car cons) (read-optimized-constant))
             finally
               (return new-list)))
      ((#\2)
       (loop with new-list = (make-list (read-optimized-constant))
             for trailer = nil then cons
             for cons on new-list
             do
         (setf (car cons) (read-optimized-constant))
             finally
               (setf (cdr trailer) (read-optimized-constant))
               (return new-list)))
      ((#\3)
       (loop with new-fixnum fixnum = 0
             for digit-char = (read-next-constant-op-char)
             until (or (char= digit-char #\y) (char= digit-char #\z))
             for new-bits fixnum = (fixnum-digit-fixnum-from-char digit-char)
             do
         (setq new-fixnum (+f (ashf new-fixnum 6) new-bits))
             finally
               (return
                 (if (char= digit-char #\y)
                     new-fixnum
                     (-f new-fixnum)))))
      ((#\4)
       (loop with vector-length fixnum = (read-optimized-constant)
             with new-vector = (make-array vector-length)
             for index from 0 below vector-length
             do
         (setf (svref new-vector index) (read-optimized-constant))
             finally (return new-vector)))
      ((#\5)
       (loop with string-length fixnum = (read-optimized-constant)
             with new-string = (make-string string-length)
             for index from 0 below string-length
             do
         (setf (schar new-string index) (read-next-constant-op-char))
             finally (return new-string)))
      ((#\6)
       (read-next-constant-op-char))
      ((#\7)
       (loop with string-length fixnum = (read-optimized-constant)
             with new-string = (make-string string-length)
             for index from 0 below string-length
             do
         (setf (schar new-string index)
               (code-char (read-optimized-constant)))
             finally (return new-string)))
      ((#\8)
       (svref standard-symbols-for-optimized-constant?
              (read-optimized-constant)))
      ((#\9)
       (svref optimized-constant-vector (read-optimized-constant)))
      ((#\+)
       (loop with vector-length fixnum = (read-optimized-constant)
             with new-vector = (make-array vector-length
                                           :element-type '(unsigned-byte 16))
             for index from 0 below vector-length
             do
         (setf (aref (the (simple-array (unsigned-byte 16)) new-vector) index)
               (read-optimized-constant))
             finally (return new-vector)))
      (#\A
       most-negative-fixnum)
      (t
        (if (and (char>= dispatch-char #\a) (char<= dispatch-char #\z))
            (-f (-f (char-code dispatch-char) (char-code #\a)) 10)
            (optimized-constant-error
              "Error reading constant, bad dispatch char = ~s"
              dispatch-char))))))






;;;; Storage Allocation Primitives

;;; The rest of the Storage Allocation Primitives are defined in PRIMITIVES, but
;;; I intend to move them to this file when such reorganization-style commits
;;; are permitted in 8.4r0.  -jv, 7/24/07

(defmacro make-static-array (&rest args)
  `(in-static-area (make-array ,@args)))

(defmacro make-static-string (&rest args)
  `(in-static-area (make-string ,@args)))



;;; `make-array-with-nils' -- it seems our previous Lisps all used nil as the
;;; default value when making an array.  SBCL apparently likes to use zero.
;;; No idea how far-ranging problems caused by this difference will be, but
;;; catch some of the bigger ones and call make-array-with-nils instead of
;;; make-array.  Obviously, this adds overhead, but I really don't see any
;;; other choice aside from visiting every structure and making an explicit
;;; initialization where there was none before.  Maybe not having an explicit
;;; initialization means you're "not allowed" to depend on the value being
;;; anything in particular.  If so, that's a matter of policy, and the fact
;;; remains, that policy has not been followed.
;;;
;;; Note, make-array takes a bunch of optional arguments; make-array-with-nils
;;; does not.  It is only intended to replace the simplest call to make-array.

(defmacro make-array-with-nils (array-dimensions)
  (let ((dimensions (gensym)))
    `(let* ((,dimensions ,array-dimensions)
            (the-array (make-array ,dimensions)))
       (loop for i from 0 below ,dimensions do
         (setf (svref the-array i) nil))
       the-array)))




;;;; Temporary Home of Symbol Macrolet



;;; `Symbol-macrolet' is a really cool special form.  And it comes from CLtL2,
;;; so you know it's good.  This definition exposes it to us humble, explicit-
;;; reclamation-and-lisp-to-C-translation-addled GL hackers.

;; Just like with destructuring-bind, Carl Shapiro didn't buy us implementating
;; symbol-macrolet ourselves, and removed our implementation from his Lispworks
;; branch.  For now, for Lispworks, we'll do the same.  -jv, 5/27/05

(defmacro symbol-macrolet (binding-list &body body)
  (if (eval-feature :chestnut-trans)
     `(,(intern "SYMBOL-MACROLET" (find-package "TCL"))
        ,binding-list
        ,@body)
     `(,(intern "SYMBOL-MACROLET" (find-package "CL"))
        ,binding-list
        ,@body)))

;;; `with-synchronized' is wrapper of tx:with-lock-held

(defmacro with-synchronized (binding-list &body body)
  (declare (ignorable binding-list))
  #+SymScale
  `(,(intern "WITH-LOCK-HELD" (find-package "TX"))
     ,binding-list
     ,@body)
  #-SymScale
  `(progn ,@body))

;;; Portable CAS (compare-and-swap) for Chestnut, LispWorks, SBCL & Clozure CL.
;;;
;;; `compare-and-swap' performs a conditional store, atomically.
;;; It atomically compare a `place' with a given `compare' value,
;;; and set the place with `new-value' if the comparation succeeds,
;;; then return a boolean to indicate the results.

#+(and (or mtg2 SymScale) translator)
(tx::def-foreign-function (compare-and-swap-symbol-value
                            (:name "CAS_SYMBOL")
                            (:return-type :object))
    (symbol :object)
    (compare :object)
    (new-value :object))

#+(and (or mtg2 SymScale) translator)
(tx::def-foreign-function (compare-and-swap-car
                            (:name "CAS_CAR")
                            (:return-type :object))
    (cons :object)
    (compare :object)
    (new-value :object))

#+(and (or mtg2 SymScale) translator)
(tx::def-foreign-function (compare-and-swap-cdr
                            (:name "CAS_CDR")
                            (:return-type :object))
    (cons :object)
    (compare :object)
    (new-value :object))

#+(and (or mtg2 SymScale) translator)
(tx::def-foreign-function (compare-and-swap-simple-vector-slot
                            (:name "CAS_SVREF")
                            (:return-type :object))
    (vector :object)
    (index :fixnum-int)
    (compare :object)
    (new-value :object))

(defmacro compare-and-swap (place compare new-value &environment env)
  (declare (ignorable compare env))
  #+(or mtg2 SymScale)
  (if (eval-feature :chestnut-trans)
      ;; Now we do not use translator macro
      (let ((place (funcall (intern "MACROEXPAND" (or (find-package "TCL")
                                                      (find-package "CL")))
                            place env)))
	(when (and (consp place)
		   (eq (car place) 'the)) ; handle (the fixnum ...) forms
	  (setq place (third place)))
        (cond ((atom place)
               (if (symbolp place)
                   `(compare-and-swap-symbol-value
                     ',place
                     ,compare ,new-value)
                 (error "Invalid place: non-symbol atom (~A)" place)))
              ((eq (car place) 'symbol-value)
               `(compare-and-swap-symbol-value
                 ,(cadr place)
                 ,compare ,new-value))
              ((or (member (car place) '(car first))
                   (eq (car place)
                       (intern "%M-CAR" (find-package "TRUN"))))
               `(compare-and-swap-car
                 ,(cadr place)
                 ,compare ,new-value))
              ((or (member (car place) '(cdr rest))
                   (eq (car place)
                       (intern "%M-CDR" (find-package "TRUN"))))
               `(compare-and-swap-cdr
                 ,(cadr place)
                 ,compare ,new-value))
              ((eq (car place) 'svref)
               `(compare-and-swap-simple-vector-slot
                 ,(second place) ,(third place)
                 ,compare ,new-value))
              (t (error "Setf place (~A) is not supported yet" (car place)))))

    ;; LispWorks 6.1 Release Notes (section 13.2.8):
    ;;
    ;; More places for which low-level atomic operations are defined:
    ;;
    ;; (the type place)
    ;;   For a place which is itself supported
    ;; (symbol-value symbol)
    ;;   This was documented (but not actually implemented) in LispWorks 6.0.
    ;; symbol
    ;;   This was implemented (but not documented) in LispWorks 6.0.
    #+(or SBCL LispWorks)
    (let ((old-value (gensym)))
      (setq place (macroexpand place env))
      (when (and (consp place)
		 (eq (car place) 'the)) ; handle (the fixnum ...) forms
	(setq place (third place)))

      ;; SBCL's CAS doesn't support atom place (global variable), so we must use
      ;; SYMBOL-VALUE explicitly. And it returns the old value, not boolean.
      `(let ((,old-value ,compare))
         #+SBCL
         (eq ,old-value
	     (sb-ext:cas ,(if (atom place) `(symbol-value ',place) place)
			 ,old-value ,new-value))
         #+LispWorks
         (sys:compare-and-swap ,place ,old-value ,new-value)))
    #+Clozure
    (progn
      (setq place (macroexpand place env))
      (when (and (consp place)
		 (eq (car place) 'the)) ; handle (the fixnum ...) forms
	(setq place (third place)))

      ;; CCL's CAS (CONDITIONAL-STORE) doesn't support CAR and CDR places, but
      ;; there're two replacements (%RPLACA/D-CONDITIONAL) to use instead.
      (if (and (consp place)
               (member (car place) '(car cdr first rest)))
          (ecase (car place)
            ((car first)
             `(ccl::%rplaca-conditional ,(cadr place) ,compare ,new-value))
            ((cdr rest)
             `(ccl::%rplacd-conditional ,(cadr place) ,compare ,new-value)))
        `(ccl::conditional-store ,place ,compare ,new-value)))
    #-(or LispWorks SBCL Clozure)
    (error "CAS is not supported in this platform!"))
  ;; For legacy G2, just SETF directly and return T to terminate the outer LOOP.
  #-SymScale
  `(progn
     (setf ,place ,new-value)
     t))

;;; `atomic-exchange' atomically exchange a place value with a new value,
;;; returning the old value.

(defmacro atomic-exchange (place new-value &environment env)
  (declare (ignore env))
  #+(or mtg2 SymScale)
  (let ((old (gensym))
	(new (gensym)))
    `(loop
       (let* ((,old ,place)
	      (,new ,new-value))
	 (when (compare-and-swap ,place ,old ,new)
	   (return ,old)))))
  #-(or mtg2 SymScale)
  `(prog1 ,place
     (setf ,place ,new-value)))

;;; ATOMIC-INCFF and ATOMIC-DECFF

#+(or mtg2 SymScale)
(defmacro atomic-incff-decff (place delta)
  (let ((old (gensym))
	(new (gensym)))
    `(loop
       (let* ((,old ,place)
	      (,new (+f ,old ,delta)))
	 (declare (type fixnum ,old ,new))
	 (when (compare-and-swap ,place ,old ,new)
	   (return ,new))))))

(defmacro atomic-incff (place &optional (delta 1))
  #+(or mtg2 SymScale)
  `(,(intern "ATOMIC-INCF&" (find-package "TX")) ,place ,delta)
  #+ignore
  `(atomic-incff-decff ,place ,delta)
  #-(or mtg2 SymScale)
  `(incff ,place ,delta))

(defmacro atomic-decff (place &optional (delta 1))
  #+(or mtg2 SymScale)
  `(,(intern "ATOMIC-DECF&" (find-package "TX")) ,place ,delta)
  #+ignore
  `(atomic-incff-decff ,place (-f ,delta))
  #-(or mtg2 SymScale)
  `(decff ,place ,delta))

;;; Atomic references (indirect references of lisp objects)

#+SymScale
(progn

#-chestnut-trans
(defvar *all-atomic-references*	; ref->obj
  (make-hash-table :test 'eql))

;; NOTE: we need this because %pointer could return different values for the same object.
#-chestnut-trans
(defvar *all-atomic-objects*	; obj->ref
  (make-hash-table :test 'eq))

#-chestnut-trans
(defvar *atomic-reference-counter*
  (cons #b111100000000000000000000000000000000000000000000 nil)) ; 48 bits, large enough

#-chestnut-trans ; the so-called indirect reference
(defun get-pseudo-pointer ()
  (atomic-incff (car *atomic-reference-counter*) 8))

#+translator
(tx::def-foreign-function (inline-make-atomic-ref-1
                            (:name "MAKE_ATOMIC_REF")
                            (:return-type :object))
  (object :object)
  (stamp :fixnum-int))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter *atomic-stamp* #x163)) ; #b000101100011

)

#|
Most-positive-fixnum (SBCL x64):
4611686018427387903 (#b0011111111111111111111111111111111111111111111111111111111111111)
Most-positive-fixnum (LispWorks & Clozure CL x64, and now Chestnut):
1152921504606846975 (#b0000111111111111111111111111111111111111111111111111111111111111)
Valid x64 pointer   (#b0000000000000000111111111111111111111111111111111111111111111111)
Valid Stamp         (#b0000111111111111000000000000000000000000000000000000000000000000)
Atomic Stamp        (#b0000000101100011000000000000000000000000000000000000000000000000)
|#

#+SymScale
(defmacro make-atomic-reference (object &optional stamp)
  (if (eval-feature :chestnut-trans)
      `(inline-make-atomic-ref-1 ,object
				 ,(if (constantp stamp)
				      (if (eval stamp) #.*atomic-stamp* 0)
				    `(if ,stamp #.*atomic-stamp* 0)))
    (let ((o (make-symbol "OBJECT"))
	  (v (make-symbol "VALUE")))
      `(let* ((,o ,object)
	      (,v (if ,o (gethash ,o *all-atomic-objects*) 0)))
	 (unless ,v
	   (setq ,v (get-pseudo-pointer))
	   (setf (gethash ,o *all-atomic-objects*) ,v)
	   (setf (gethash ,v *all-atomic-references*) ,o))
	 (logiorf ,v (ashf ,(if (constantp stamp)
				(if (eval stamp) #.*atomic-stamp* 0)
			      `(if ,stamp #.*atomic-stamp* 0)) 48))))))

#-SymScale
(defmacro make-atomic-reference (object &optional stamp)
  (declare (ignore stamp))
  object)

#+(and SymScale translator)
(tx::def-foreign-function (inline-atomic-ref-object-1
                            (:name "ATOMIC_REF_OBJECT")
                            (:return-type :object))
  (object :object))

#-SymScale
(defmacro atomic-reference-object (reference)
  reference)

#+SymScale
(defmacro atomic-reference-object (reference)
  (if (eval-feature :chestnut-trans)
      `(inline-atomic-ref-object-1 ,reference)
    (let ((v (make-symbol "VALUE"))
          (r (make-symbol "ATOMIC-REF")))
      `(let* ((,r ,reference)
              (,v (ldb (byte 48 0) ,r)))
         (if (=f ,v 0)
             nil
           (gethash ,v *all-atomic-references*))))))

#+(and SymScale translator)
(tx::def-foreign-function (inline-barrier-1
                            (:name "barrier")
                            (:return-type :void)))

#+SymScale
(defun inline-barrier ()) ; TODO: how to implement this in SBCL?

;; Use BARRIER to flush local cache (to and from memory).
(defmacro barrier ()
  #+SymScale
  (if (eval-feature :chestnut-trans)
      `(inline-barrier-1)
    `(inline-barrier)))

#+(and SymScale translator)
(tx::def-foreign-function (inline-access-once-1
                            (:name "ACCESS_ONCE")
                            (:return-type :object))
  (object :object))

#+SymScale
(defun inline-access-once (object)
  object)

;;; Use ACCESS-ONCE to read a memory location without local cache.
(defmacro access-once (object)
  #+SymScale
  (if (eval-feature :chestnut-trans)
      `(inline-access-once-1 ,object)
    `(inline-access-once ,object))
  #-SymScale
  object)

#+(and SymScale translator)
(tx::def-foreign-function (inline-atomic-ref-stamp-1
                            (:name "ATOMIC_REF_STAMP")
                            (:return-type :fixnum-int))
  (object :object))

#+SymScale ; Now only used by `atomic-reference-mark'
(defmacro atomic-reference-stamp (reference)
  (if (eval-feature :chestnut-trans)
      `(inline-atomic-ref-stamp-1 ,reference)
    (let ((r (make-symbol "ATOMIC-REF")))
      `(let ((,r ,reference))
	 (if (and ,r (fixnump ,r))
	     (ashf ,r -48)
	   0)))))

#+SymScale
(defmacro atomic-reference-mark (reference)
  (if (eval-feature :chestnut-trans)
      `(=f #.*atomic-stamp* (inline-atomic-ref-stamp-1 ,reference))
    `(=f #.*atomic-stamp*
	 (atomic-reference-stamp ,reference))))

#+(and SymScale (not development))
(defmacro get-atomic-reference (reference)
  (let ((r (make-symbol "REFERENCE"))
	(v (make-symbol "VALUE")))
    (if (eval-feature :chestnut-trans)
	`(let ((,r ,reference))
	   (values (inline-atomic-ref-object-1 ,r)
		   (=f #.*atomic-stamp* (inline-atomic-ref-stamp-1 ,r))))
      `(let* ((,r ,reference)
	      (,v (ldb (byte 48 0) ,r)))
	 (values (if (=f ,v 0) nil
		   (gethash ,v *all-atomic-references*))
		 (=f #.*atomic-stamp* (ashf ,r -48)))))))

#+(and SymScale development)
(defun get-atomic-reference (reference)
  #+chestnut-trans
  (values (inline-atomic-ref-object-1 reference)
	  (=f *atomic-stamp*
	      (inline-atomic-ref-stamp-1 reference)))
  #-chestnut-trans
  (let* ((r reference)
	 (v (ldb (byte 48 0) r)))
    (values (if (=f v 0) nil
	      (gethash v *all-atomic-references*))
	    (=f #.*atomic-stamp* (ashf r -48)))))

#+SymScale
(defmacro atomic-reference-equal (r1 r2)
  (if (eval-feature :chestnut-trans)
      `(eq ,r1 ,r2)
    `(=f ,r1 ,r2)))

#+SymScale
(defmacro atomic-reference-neq (r1 r2)
  `(not (atomic-reference-equal ,r1 ,r2)))

#+SymScale
(defmacro atomic-incf-decf (place delta)
  (let ((old (gensym))
	(new (gensym)))
    `(loop
       (let* ((,old ,place)
	      (,new (+ ,old ,delta)))
	 (when (compare-and-swap ,place ,old ,new)
	   (return ,new))))))

;; NOTE: use ATOMIC-INCFF and ATOMIC-DECFF instead, whenever possible.
(defmacro atomic-incf (place &optional (delta 1))
  #+SymScale
  `(atomic-incf-decf ,place ,delta)
  #-SymScale
  `(incf ,place ,delta))

(defmacro atomic-decf (place &optional (delta 1))
  #+SymScale
  `(atomic-incf-decf ,place (- ,delta))
  #-SymScale
  `(decf ,place ,delta))

;;; The following memory management algorithm is from this paper:
;;;
;;; Michael, Maged M., and Michael L. Scott. Correction of a Memory Management Method for
;;; Lock-Free Data Structures. No. TR-599. ROCHESTER UNIV NY DEPT OF COMPUTER SCIENCE, 1995.

#+SymScale
(defmacro decrement-and-test-and-set (place)
  (let ((old (gensym))
	(new (gensym)))
    `(loop as ,old = ,place
	   as ,new = (-f ,old 2)
	   do
       (when (=f 0 ,new)
	 (setq ,new 1))
	   until (compare-and-swap ,place ,old ,new)
	   finally
	     (return (logandf (-f ,old ,new) 1)))))

#+SymScale
(defmacro clear-lowest-bit (place)
  (let ((old (gensym))
	(new (gensym)))
    `(loop as ,old = ,place
	   as ,new = (-f ,old 1)
	   until (compare-and-swap ,place ,old ,new))))

;; LW:WHEN-LET, carefully use it around a LOOP with FINALLY form, because
;; the FINALLY form could still be executed even the LOOP terminated with
;; null variable. -- Chun Tian (binghe).

(defmacro when-let ((var form) &body body)
  `(let ((,var ,form))
     (when ,var ,@body)))

;; LW:WHEN-LET*
(defmacro when-let* (bindings &body forms)
  (let ((binding-list (if (and (consp bindings) (symbolp (car bindings)))
                          (list bindings)
                          bindings)))
    (labels ((bind (bindings forms)
               (if bindings
                   `((let (,(car bindings))
                       (when ,(caar bindings)
                         ,@(bind (cdr bindings) forms))))
                   forms)))
      `(let (,(car binding-list))
         (when ,(caar binding-list)
           ,@(bind (cdr binding-list) forms))))))

;; A LOOP path interator on LISTs, used by Procedure-invocation and Gensym-Pathname.
(defun-for-macro expand-list-loop-iterator
    (path-name variable data-type prep-phrases inclusive? allowed-prepositions data)
  (declare (ignore data-type data allowed-prepositions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S" path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	   path-name variable prep-phrases))
  (let* ((invocations (cadar prep-phrases))
	 (sublist-variable (make-symbol "LOOP-SUBLIST"))
	 (generator-bindings `((,sublist-variable ,invocations)
			       (,variable nil)))
	 (generator-initialize nil)
	 (generator-eof-p `(null ,sublist-variable))
	 (generator-advance
	   `(,variable (car-of-cons ,sublist-variable)
	     ,sublist-variable (cdr-of-cons ,sublist-variable))))
    `(,generator-bindings	; init-bindings
      ,generator-initialize	; prologue-forms
      ,generator-eof-p		; pre-step-tests
      nil			; steppings
      nil			; post-step-tests
      ,generator-advance)))	; post-step-settings

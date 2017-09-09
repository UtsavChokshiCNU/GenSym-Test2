;;; -*- Mode: Lisp; Package: TUTIL; Syntax: Common-Lisp -*-
;;;
;;; env.lsp -- environment handling code
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  14 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software
;;;
;;; This file defines an implementation of the X3J13
;;; SYNTACTIC-ENVIRONMENT-ACCESS proposal, incorporating some
;;; later changes to the basic functionality, except that the names
;;; have been changed to prevent conflicts in case the host Lisp
;;; implementation also implements this stuff.
;;;
;;; If the host Lisp provides both the syntactic-environment-access stuff
;;; and remote environments, the interface defined in this file could
;;; be implemented in terms of the host's primitives.  (The translator 
;;; needs to modify the global environment as well as the lexical 
;;; environment, so the accessors for lexical definitions alone are 
;;; not sufficient.)
;;;

(in-package "TUTIL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/env.lisp,v $"
 "$Revision: 1.15 $"
 "$Date: 2007/11/16 15:39:43 $")


(in-package :timpl)

(define-forward-variable-reference *translated-file-sequence-number*)

(defstruct translated-file
  (sequence-number           (incf *translated-file-sequence-number*))
  (cookie                    nil)
  (init-function-name        nil)
  (init-function-record      nil)
  (init-pathname             nil)          ; only if #included
  (init-function-p           nil)
  (output-pathname	     nil)
  )

;;; *** Maybe *compile-time-too* and *toplevel-p* ought to be encoded in
;;; *** the environment.

(defvar *compile-time-too* nil)
(defvar *toplevel-p* t)
(defvar *compile-time-only* nil)

(in-package :tutil)

(defstruct descriptor
  (file-cookie nil))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Function/variable descriptors
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; These structures are stored under the defined-as-function and
;;; defined-as-variable properties, respectively.


;;; A function descriptor is used to hold all the information about 
;;; the external interface to function definitions that is necessary
;;; to generate correct calls to them.

(defstruct (function-descriptor
	     (:constructor %make-function-descriptor)
	     (:copier nil)
	     (:include descriptor))
  ;; These slots are used by all functions
  (lambda-list           nil)  ; for arg type matching
  (lambda-list-info      nil)  ; parsed info for arg count matching
  (declare               nil)  ; declarations about lambda parameters
  (argument-types        nil)  ; Lisp type specifiers for the arguments
  (return-type           '(values &rest t)) ; Lisp type specifier for result
  (transforms            nil)  ; list of transformations
  (documentation         nil)  ; documentation string

  (flags                 0)    ; see below

  ;; These slots are used only by Lisp-callable functions
  (generic-function-p    nil)  ; gf object, t (gf not installed yet), or nil
  (linked-locally-p      nil)  ; true iff Qfoo <--> Ffoo linked locally
  ;; It is easiest to keep this here.
  (foreign-protocol      nil)  ; specifies foreign call protocol
  )

(defstruct (foreign-function-descriptor
	     (:constructor %make-foreign-function-descriptor)
	     (:copier nil)
	     (:include function-descriptor))
  (foreign-arguments     nil)  ; foreign argument conversion info
  (foreign-return-type   nil)  ; foreign type of return value

  (uses-locals           nil)  ; implicit locals
  (uses-constants        nil)  ; implicit constants
  (lvalue                nil)  ; if foreign-protocol slot is :lvalue-setter 
			       ; then this is the lvalue
  (operator              nil)  ; The operator name (see emit.lisp)
  )

(define-flags function-descriptor- function-descriptor-flags
  (defined-in-rtl-p      nil)  ; true if function is defined in RTL
  (rtl-requires-linking  nil)  ; true if RTL requires
                               ; symbol-to-function link
  (variadic              nil)  ; true if &optional (non-RTL), &rest, or &key
  (nonconsing            nil)  ; true if never allocates heap
  (nonrelocating         nil)  ; true if never calls GC
  (state-using           t)    ; true if behavior depends on external state
  (state-changing        t)    ; true if behavior changes external state
  (requires-return-type-declaration nil)
  (extern-required       nil)  ; An extern declaration for this function
			       ; should be dumped for this function in
                               ; callables.h (for functions created with
                               ; def-foreign-function)
  (funcallable-p         nil)
  (coerce-rationals-to-floats-p nil)
  (coerce-floats-to-rationals-p nil)
  (sets-values-count-p   t)
  (array-setf-function-p nil)
  (alias-p               nil)
  (dllexport-p           nil)
  (dllimport-p           nil))

(defvar *first-free-function-descriptor* nil)
(defvar *first-free-foreign-function-descriptor* nil)

(eval-when (compile load eval)
(defun make-or-reuse-form (args constructor free-var free-slot prefix package)
  (unless (packagep package) (setq package (find-package package)))
  (let ((result-var (make-symbol "RESULT")))
    `(if ,free-var
	 (let ((,result-var (shiftf ,free-var (,free-slot ,free-var))))
	   ,@(let ((rev-args (reverse args))
		   (setqs nil))
	       (loop (when (null rev-args) (return setqs))
		     (let* ((value (pop rev-args))
			    (key (pop rev-args))
			    (accessor (intern (sformat "~A~A" prefix key)
					      package)))
		       (push `(setf (,accessor ,result-var) ,value)
			     setqs))))
	   ,result-var)
	 (with-static-area (,constructor ,@args)))))

(defparameter *descriptor-slot-names*
  '(file-cookie))

(defparameter *function-descriptor-slot-names*
  '(lambda-list lambda-list-info declare argument-types 
    (return-type '(values &rest t))
    transforms documentation generic-function-p linked-locally-p))

(defparameter *foreign-function-descriptor-slot-names*
  '(foreign-protocol
    foreign-arguments foreign-return-type uses-locals uses-constants
    lvalue operator))
)

(defun variadic-function-p (lambda-list &optional 
					generic-function-p defined-in-rtl-p)
  (dolist (x lambda-list nil)
    (if (or (and (eq x '&optional)
		 (not (or generic-function-p defined-in-rtl-p)))
	    (eq x '&rest)
	    (eq x '&key))
	(return t))))

(defmacro make-function-descriptor-internal (&rest args)
  (let ((new-args nil)
	(new-flags nil)
	(defined-in-rtl-p nil)
	(defined-in-rtl-p-var (make-symbol "DEFINED-IN-RTL-P"))
	(generic-function-p nil)
	(generic-function-p-var (make-symbol "GENERIC-FUNCTION-P"))
	(lambda-list nil) (lambda-list-p nil)
	(lambda-list-var (make-symbol "LAMBDA-LIST"))
	(flags-p nil) (flags-form nil)
	(flags-var (make-symbol "FLAGS"))
	(simple-p t))
    (loop (unless args (return nil))
	  (let ((key (pop args))
		(form (pop args)))
	    (cond ((member key *function-descriptor-flags*)
		   (when (eq key ':defined-in-rtl-p)
		     (setq defined-in-rtl-p form)
		     (setq form defined-in-rtl-p-var))
		   (when (eq key ':generic-function-p)
		     (setq generic-function-p form)
		     (setq form generic-function-p-var))
		   (push key new-flags) (push form new-flags))
		  ((eq key ':flags)
		   (setq flags-p t flags-form form))
		  (t
		   (let ((new-form (case key
				     (:foreign-return-type
				      `(timpl::fix-foreign-return-type ,form))
				     (:foreign-arguments
				      `(timpl::fix-foreign-arguments ,form))
				     (:foreign-protocol
				      (setq simple-p (and (constantp form)
							  (null (eval form))))
				      (unless simple-p
					`(timpl::fix-foreign-protocol ,form)))
				     (:operator
				      `(timpl::fix-foreign-operator ,form))
				     (:transforms
				      `(mapcar #'timpl::copy-transform ,form))
				     (:lambda-list
				      (setq lambda-list form)
				      (setq lambda-list-p t)
				      lambda-list-var))))
		     (when new-form (setq form new-form))
		     (push key new-args)  (push form new-args))))))
    (unless lambda-list-p
      (error "The keyword arg ~S must be supplied." ':lambda-list))
    (multiple-value-bind (constructor free-var prefix)
	(if simple-p
	    (values '%make-function-descriptor
		    '*first-free-function-descriptor*
		    'function-descriptor-)
	    (values '%make-foreign-function-descriptor
		    '*first-free-foreign-function-descriptor*
		    'foreign-function-descriptor-))
      (setq new-args `(:flags ,flags-var ,@(nreverse new-args)))
      `(let* ((,lambda-list-var ,lambda-list)
	      ,@(unless flags-p
			`((,defined-in-rtl-p-var ,defined-in-rtl-p)
			  (,generic-function-p-var ,generic-function-p)))
	      (,flags-var
	       ,(if flags-p
		    flags-form
		    `(make-function-descriptor-flags
		      :variadic (variadic-function-p ,lambda-list-var
						     ,generic-function-p-var
						     ,defined-in-rtl-p-var)
		      ,@(nreverse new-flags)))))
	 ;;(setq ,lambda-list-var (copy-list-static ,lambda-list-var))
	 ,(make-or-reuse-form new-args constructor
			      free-var 'descriptor-file-cookie prefix
			      *tutil-package*)))))


#+ignore ; binghe, 2009/04/03: duplicated definition
(defun variadic-function-p (lambda-list &optional 
					generic-function-p defined-in-rtl-p)
  (dolist (x lambda-list nil)
    (if (or (and (eq x '&optional)
		 (not (or generic-function-p defined-in-rtl-p)))
	    (eq x '&rest)
	    (eq x '&key))
	(return t))))

(defmacro define-function-descriptor-constructor (name)
  (let* ((fdsn `(,@*descriptor-slot-names*
		 ,@*function-descriptor-slot-names*
		 ,@*function-descriptor-flags-slot-names*))
	 (ffdsn `(,@fdsn
		  ,@*foreign-function-descriptor-slot-names*)))
    (flet ((make-key-value (sn)
	     (let* ((name (if (consp sn) (car sn) sn))
		    (key (intern (symbol-name name) "KEYWORD")))
	       (list key name))))
      `(defun ,name (&key ,@ffdsn)
	 (if foreign-protocol
	     (make-function-descriptor-internal
	      ,@(mapcan #'make-key-value ffdsn))
	     (make-function-descriptor-internal
	      ,@(mapcan #'make-key-value fdsn)))))))

(define-function-descriptor-constructor make-function-descriptor)

(defun copy-function-descriptor (old)
  (if (function-descriptor-foreign-protocol old)
      (make-function-descriptor-internal
       :file-cookie (descriptor-file-cookie old)
       :lambda-list (function-descriptor-lambda-list old)
       :lambda-list-info (function-descriptor-lambda-list-info old)
       :declare (function-descriptor-declare old)
       :argument-types (function-descriptor-argument-types old)
       :return-type (function-descriptor-return-type old)
       :transforms (function-descriptor-transforms old)
       :documentation (function-descriptor-documentation old)
       :flags (function-descriptor-flags old)
       :generic-function-p (function-descriptor-generic-function-p old)
       :linked-locally-p (function-descriptor-linked-locally-p old)
       :foreign-protocol (function-descriptor-foreign-protocol old)
       :foreign-arguments (foreign-function-descriptor-foreign-arguments old)
       :foreign-return-type (foreign-function-descriptor-foreign-return-type old)
       :uses-locals (foreign-function-descriptor-uses-locals old)
       :uses-constants (foreign-function-descriptor-uses-constants old)
       :lvalue (foreign-function-descriptor-lvalue old)
       :operator (foreign-function-descriptor-operator old))
      (make-function-descriptor-internal
       :file-cookie (descriptor-file-cookie old)
       :lambda-list (function-descriptor-lambda-list old)
       :lambda-list-info (function-descriptor-lambda-list-info old)
       :declare (function-descriptor-declare old)
       :argument-types (function-descriptor-argument-types old)
       :return-type (function-descriptor-return-type old)
       :transforms (function-descriptor-transforms old)
       :documentation (function-descriptor-documentation old)
       :flags (function-descriptor-flags old)
       :generic-function-p (function-descriptor-generic-function-p old)
       :linked-locally-p (function-descriptor-linked-locally-p old)
       :foreign-protocol nil)))

(defun copy-foreign-function-descriptor (old)
  (make-function-descriptor
   :file-cookie (descriptor-file-cookie old)
   :lambda-list (function-descriptor-lambda-list old)
   :lambda-list-info (function-descriptor-lambda-list-info old)
   :declare (function-descriptor-declare old)
   :argument-types (function-descriptor-argument-types old)
   :return-type (function-descriptor-return-type old)
   :transforms (function-descriptor-transforms old)
   :documentation (function-descriptor-documentation old)
   :flags (function-descriptor-flags old)
   :generic-function-p (function-descriptor-generic-function-p old)
   :linked-locally-p (function-descriptor-linked-locally-p old)
   :foreign-protocol (function-descriptor-foreign-protocol old)
   :foreign-arguments (foreign-function-descriptor-foreign-arguments old)
   :foreign-return-type (foreign-function-descriptor-foreign-return-type old)
   :uses-locals (foreign-function-descriptor-uses-locals old)
   :uses-constants (foreign-function-descriptor-uses-constants old)
   :lvalue (foreign-function-descriptor-lvalue old)
   :operator (foreign-function-descriptor-operator old)))

(defun free-function-descriptor (fd)
  ;;(free-list-static (function-descriptor-lambda-list fd))
  (setf (function-descriptor-lambda-list fd) nil)
  (setf (function-descriptor-lambda-list-info fd) nil)
  (setf (function-descriptor-declare fd) nil)
  (setf (function-descriptor-argument-types fd) nil)
  (setf (function-descriptor-return-type fd) '(values &rest t))
  (setf (function-descriptor-transforms fd) nil)
  (setf (function-descriptor-documentation fd) nil)
  (setf (function-descriptor-flags fd) 0)
  (setf (function-descriptor-generic-function-p fd) nil)
  (setf (function-descriptor-linked-locally-p fd) nil)
  (setf (function-descriptor-foreign-protocol fd) nil)
  (if (foreign-function-descriptor-p fd)
      (progn
	(setf (foreign-function-descriptor-foreign-arguments fd) nil)
	(setf (foreign-function-descriptor-foreign-return-type fd) nil)
	(setf (foreign-function-descriptor-uses-locals fd) nil)
	(setf (foreign-function-descriptor-uses-constants fd) nil)
	(setf (foreign-function-descriptor-lvalue fd) nil)
	(setf (foreign-function-descriptor-operator fd) nil)
	(shiftf (descriptor-file-cookie fd)
		*first-free-foreign-function-descriptor* fd))
      (shiftf (descriptor-file-cookie fd)
	      *first-free-function-descriptor* fd))
  nil)

;;; Build a function descriptor from the lambda-list appearing in its
;;; actual definition.

(defun build-argument-descriptor (lambda-list &key (generic-function-p nil)
					      (documentation nil))
  (make-function-descriptor
   :lambda-list lambda-list
   :generic-function-p generic-function-p
   :documentation documentation))

(defun variadic-lambda-list-p (lambda-list)
  (dolist (x lambda-list nil)
    (if (or (eq x '&optional)
	    (eq x '&rest)
	    (eq x '&key))
	(return t))))

(defmacro function-descriptor-explicit-optionals-p (descriptor)
  `(or (function-descriptor-defined-in-rtl-p ,descriptor)
       (function-descriptor-generic-function-p ,descriptor)))

;;; Do rudimentary checks to make sure that calls processed with 
;;; old-descriptor are still valid with new-descriptor.

(defun argument-descriptors-equal-p (old-descriptor new-descriptor)
  (and (eq (function-descriptor-variadic new-descriptor)
	   (function-descriptor-variadic old-descriptor))
       (eql (number-of-required-args new-descriptor)
	    (number-of-required-args old-descriptor))))

(defun number-of-required-args (descriptor)
  (let ((count  0))
    (dolist (x (function-descriptor-lambda-list descriptor))
      (if (lambda-keyword-p x)
	  (return nil)
	  (incf count)))
    count))



;;; A variable descriptor contains information about symbols defined
;;; as special or constant.
;;; The values for the constant-p slot are:
;;; :simple-constant -- a defined constant whose value is immediate;
;;;     the translator will emit a #define to that value.
;;; :complex-constant -- a defined constant whose value is not immediate;
;;;     the translator treats these like DEFVARs.
;;; The dumper needs to know about these keywords.  See also define.lisp.

(defstruct (variable-descriptor
	     (:include descriptor)
	     (:constructor %make-variable-descriptor)
	     (:copier nil))
  (constant-p            nil)  ; true if a constant; value is a keyword
  (documentation         nil)  ; documentation string
  (flags                 0)
  (value                 nil)  ; the constant's value, if known
  (redefinition-record   nil)) ; Determines the file in which
                               ; the definition will be dumped:
                               ; file containing 1st reference

(define-flags variable-descriptor- variable-descriptor-flags
  (global-p              t)    ; true if a defined global
  (value-p               nil)  ; if a constant, do we know its value?
  (foreign-p             nil)  ; false implies symbol-value will "work".
  (dump-definition-p     t)    ; see dump.lisp
  (linked-locally-p      t)    ; True iff Qfoo <--> Foo linked locally
  #+translator-supports-thread
  (special-p             t))   ; True if a special variable. -- binghe, 2009/5/26

(defvar *first-free-variable-descriptor* nil)

(defmacro make-variable-descriptor (&rest args)
  (let ((new-args nil)
	(new-flags nil)
	(flags-p nil) (flags-form nil)
	(flags-var (make-symbol "FLAGS")))
    (loop (unless args (return nil))
	  (let ((key (pop args))
		(form (pop args)))
	    (if (eq key ':flags)
		(setq flags-p t flags-form form)
		(if (member key *variable-descriptor-flags*)
		    (progn (push key new-flags) (push form new-flags))
		    (progn (push key new-args)  (push form new-args))))))
    (setq new-args `(:flags ,flags-var ,@(nreverse new-args)))
    `(let ((,flags-var ,(if flags-p
			    flags-form
			    `(make-variable-descriptor-flags
			      ,@(nreverse new-flags)))))
       ,(make-or-reuse-form new-args
			    '%make-variable-descriptor
			    '*first-free-variable-descriptor*
			    'descriptor-file-cookie 
			    'variable-descriptor-
			    *tutil-package*))))

(defun free-variable-descriptor (vd)
  (setf (variable-descriptor-constant-p vd) nil)
  (setf (variable-descriptor-documentation vd) nil)
  (setf (variable-descriptor-flags vd) 0)
  (setf (variable-descriptor-value vd) nil)
  (setf (variable-descriptor-redefinition-record vd) nil)
  (shiftf (descriptor-file-cookie vd)
	  *first-free-variable-descriptor* vd)
  nil)

(defun copy-variable-descriptor (vd)
  (make-variable-descriptor
   :file-cookie (descriptor-file-cookie vd)
   :constant-p (variable-descriptor-constant-p vd)
   :documentation (variable-descriptor-documentation vd)
   :flags (variable-descriptor-flags vd)
   :value (variable-descriptor-value vd)
   :redefinition-record (variable-descriptor-redefinition-record vd)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Environment representation
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Translator environments are structures with components for local
;;; and global stuff.
;;; The idea is that whenever we add anything to the lexical environment,
;;; we merge the new information with information that already exists in
;;; the environment.  We store the information in the environment in a
;;; format that can be returned directly by the various xxx-INFORMATION
;;; accessors.  (The theory is that lookup happens more often than
;;; binding so it pays to precompute things.)
;;;
;;; The type name and predicate are exported.
;;;
;;; *** We might want to add compile-time-too and top-level-p slots to
;;; ***    the environment.
;;; *** We might want to separate the lexical-part slot into three different
;;; ***    slots so that the lookups on particular kinds of information
;;; ***    are faster.

;;; These variables are used for handling of top-level forms but are
;;; generally ignored elsewhere.

(defvar *print-table* (make-hash-table :test 'eq))
(defvar *print-count* 0)

(defun print-translator-environment (env stream depth)
  (declare (ignore depth))
  (format stream 
	  "#<Translator-environment (~{~S~^ ~}) ~D>"
	  (translator-environment-function-names env)
	  (or (gethash env *print-table*)
	      (setf (gethash env *print-table*)
		    (incf *print-count*)))))

(defstruct (translator-environment
	     (:copier copy-translator-environment-internal)
	     (:print-function print-translator-environment))
  (lexical-part nil)			; a stack of contours
  (global-simple-part nil)
  (global-setf-symbol-part nil)
  (global-other-part nil))


;;; The values stored in the various contours match the return values
;;; from the corresponding accessor functions.

(defstruct variable-information-contour
    name             ; a symbol
    usage            ; one of :special, :lexical, :symbol-macro
    locally-bound-p  ; a boolean; value for symbol-macros is macro-function
    declarations     ; a-list of declaration information
    ) 

(defstruct function-information-contour
    name             ; a function name (symbol or list)
    usage            ; one of :function, :macro
    locally-bound-p  ; a boolean; value for macros is macro-function
    declarations     ; a-list of declaration information
    )

(defstruct set-declaration-information-contour
    name             ; a symbol, names the declaration
    declarations     ; a-list of declaration information
    )

(defstruct declaration-information-contour
    name             ; a symbol, names the declaration
    value            ; the value associated with the name
    )

(defstruct function-name-contour
    name             ; a function name (symbol or list)
    (info nil) 
    )

(defun translator-environment-function-names (env)
  (nreverse (mapcan #'(lambda (contour)
			(when (function-name-contour-p contour)
			  (list (function-name-contour-name contour))))
		    (translator-environment-lexical-part env))))

;;; Most accessors, etc. deal with the "null lexical environment" if
;;; no environment is explicitly specified.  All global definitions
;;; should be made into this environment, in particular.  It might
;;; be useful to copy and/or rebind this once it has been initialized
;;; with all of the "standard" definitions.
;;; The symbol naming the variable is exported.

(defvar *default-global-environment*
  (make-translator-environment
   :global-simple-part (make-hash-table :test #'eq
					:size #+lucid 5250 #-lucid 3000)
   :global-setf-symbol-part (make-hash-table :test #'eq)
   :global-other-part (make-hash-table :test #'equal)))

(defvar *initial-global-environment*)

;;; Global environments are more general than lexical environments because
;;; they know about more namespaces than just function, variable, and
;;; declaration.  They are used for things like type names, package names, 
;;; method combination names, and the like,

;;; Define a copier for environments.

(defun copy-global-environment (old type)
  (fixup-translator-property-functions)
  (let* ((size (ceiling (* 1.75 (max 50 (hash-table-count old)))))
	 (new (make-hash-table :test type :size size)))
    (maphash #'(lambda (key value)
		 (setf (gethash key new) (copy-environment-entry value)))
	     old)
    new))

(defun free-global-environment (old)
  (fixup-translator-property-functions)
  (maphash #'(lambda (key value)
	       (declare (ignore key))
	       (free-environment-entry value))
	     old)
  (clrhash old))

(defvar *free-translator-environments* nil)

(defun copy-translator-environment (old)
  (let* ((*default-global-environment* old)
	 (new (or (pop *free-translator-environments*)
		  (make-translator-environment))))
    (setf (translator-environment-global-simple-part new)
	  (copy-global-environment
	   (translator-environment-global-simple-part old) 'eq))
    (setf (translator-environment-global-setf-symbol-part new)
	  (copy-global-environment
	   (translator-environment-global-setf-symbol-part old) 'eq))
    (setf (translator-environment-global-other-part new)
	  (copy-global-environment
	   (translator-environment-global-other-part old) 'equal))
    new))

(defun free-translator-environment (old)
  (free-global-environment
   (translator-environment-global-simple-part old))
  (free-global-environment
   (translator-environment-global-setf-symbol-part old))
  (free-global-environment
   (translator-environment-global-other-part old))
  (setf (translator-environment-lexical-part old) nil)
  (push old *free-translator-environments*)
  nil)

(defparameter *check-environments-p* nil)

(defmacro environmentify (env)
  `(cond ((null ,env) *default-global-environment*)
	 ((or (null *check-environments-p*)
	      (translator-environment-p ,env))
	  ,env)
	 (t (error "~s is not a valid environment object." ,env))))


;;; Here's a generally useful predicate.
;;; This is exported.

(defun global-translator-environment-p (env)
  (null (translator-environment-lexical-part env)))


;;; Mapping environment name to the translator environment.
;;; This is sort of trivial right now.  A reentrant translator might need
;;; something more than this (there might be more than one named environment
;;; around at any time).

(defvar *translator-environment-name* 'translator-environment)


;;; This is exported.

(defun coerce-to-environment (env)
  (if (eq env *translator-environment-name*)
      *default-global-environment*
      env))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    global environments -- low level
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; All of the functions in this section are exported, with the exception
;;; of the internal SETF helper function.

;;; Get the name of the translator environment.  We (stupidly) assume that
;;; all translator environments have the same name.

(defun translator-environment-name (env)
  (declare (ignore env))
  *translator-environment-name*)

(defmacro translator-environment-global-table (name env)
  `(if (consp ,name)
       (if (and (eq (car ,name) 'setf)
		(consp (cdr ,name))
		(null (cddr ,name))
		(symbolp (cadr ,name)))
	   (progn
	     (setq ,name (cadr ,name))
	     (translator-environment-global-setf-symbol-part ,env))
	   (translator-environment-global-other-part ,env))
       (translator-environment-global-simple-part ,env)))

(defvar *gethash1-last-key* nil)
(defvar *gethash1-last-table* nil)
(defvar *gethash1-last-value* nil)

(defmacro gethash1 (key table)
  `(if (and (eq ,key *gethash1-last-key*)
	    (eq ,table *gethash1-last-table*))
       *gethash1-last-value*
       (setq *gethash1-last-key* ,key
	     *gethash1-last-table* ,table
	     *gethash1-last-value* (gethash ,key ,table))))

(defsetf gethash1 (key table) (value)
  `(setq *gethash1-last-key* ,key
         *gethash1-last-table* ,table
	 *gethash1-last-value* (setf (gethash ,key ,table) ,value)))

(defvar *no-value* (list 'no-value))


(eval-when (compile load eval)

;; It is important that this list be short enough that there can be
;; one bit for each property, and yet still fit in a fixnum.
;; Also, prefer symbol, variable, function, and slot properties over
;; any of the others.
(defparameter *translator-simple-property-list*
  '(plist

    defined-as-symbol defined-as-quoted-symbol name-of-quoted-symbol

    variable-proclamations defined-as-variable name-of-global-variable

    function-proclamations defined-as-function
    defined-as-macro defined-as-special-form defined-as-toplevel-form
    defined-as-compiler-macro
    defined-as-generalized-variable simple-setf-update-function 
    name-of-function-object name-of-function-entry
    walk::walker-function
    timpl::corresponding-foreign-function
    #+translator-supports-clos tclosi::generic-function-record

    #+translator-supports-clos
    tclosi::global-slot-index-index-constant-property))

)

(eval-when (compile load eval)

(defmacro property-index-or-symbol (property-name)
  (if (constantp property-name)
      (let ((property-name (eval property-name)))
	(or (position property-name *translator-simple-property-list*)
	    `',property-name))
      `(let ((property-name ,property-name))
	 (or (position property-name *translator-simple-property-list*)
	     property-name))))

(defvar *property-mask-vector*
  (let ((array (make-array #.(length *translator-simple-property-list*)
			   :element-type 'fixnum)))
    (dotimes (i #.(length *translator-simple-property-list*) array)
      (setf (aref array i) (ash 1 i)))))

(defvar *translator-property-vector*
  (let ((array (make-array 40 :fill-pointer 0 :adjustable t)))
    (dotimes (i #.(length *translator-simple-property-list*) array)
      (vector-push (elt *translator-simple-property-list* i) array))))

(defvar *translator-property-copier-vector*
  (let ((len #.(length *translator-simple-property-list*)))
    (make-array 40 :fill-pointer len :adjustable t :initial-element nil)))

(defvar *translator-property-free-function-vector*
  (let ((len #.(length *translator-simple-property-list*)))
    (make-array 40 :fill-pointer len :adjustable t :initial-element nil)))

(defun add-translator-property (property-name &optional copier free-fn)
  (let ((index (position property-name *translator-property-vector*)))
    (unless index
      (vector-push-extend property-name *translator-property-vector*)
      (vector-push-extend copier *translator-property-copier-vector*)
      (vector-push-extend free-fn *translator-property-free-function-vector*)
      (setq index (position property-name *translator-property-vector*)))
    (setf (aref *translator-property-copier-vector* index) copier)
    (setf (aref *translator-property-free-function-vector* index) free-fn)
    (setf (get property-name 'copier) copier)
    (setf (get property-name 'free-function) free-fn)
    property-name))
)

(defun fixup-translator-property-functions ()
  (macrolet ((fixup (location type)
	       `(let ((fn ,location))
		  (when (and fn (symbolp fn))
		    (setq fn (symbol-function fn)))
		  (when (eq fn #'identity) (setq fn nil))
		  (setf ,location fn)
		  (setf (get property-name ,type) fn))))
    (dotimes (i (fill-pointer *translator-property-copier-vector*))
      (let ((property-name (aref *translator-property-vector* i)))
	(fixup (aref *translator-property-copier-vector* i)
	       'copier)
	(fixup (aref *translator-property-free-function-vector* i)
	       'free-function)))))

(add-translator-property 'plist 'copy-env-plist 'free-env-plist)

(defvar *free-cons-list* nil)

(defmacro pop-and-free (cons)
  `(when (consp ,cons)
     (prog1 (car ,cons)
       (let ((next (cdr ,cons)))
	 (setf (car ,cons) nil)
	 (setf (cdr ,cons) *free-cons-list*)
	 (setq *free-cons-list* ,cons)
	 (setq ,cons next)))))

(defmacro list-new (&rest args)
  (if (null args)
      'nil
      (let ((cons (gensym)))
	`(let ((,cons (or (pop *free-cons-list*)
			  (cons nil nil))))
	   (setf (car ,cons) ,(car args))
	   (setf (cdr ,cons) (list-new ,@(cdr args)))
	   ,cons))))

(defun copy-env-plist (value)
  (let ((value-copy nil) (value-copy-tail nil))
    (loop (when (null value) (return value-copy))
	  (let* ((property (pop value))
		 (pvalue (pop value))
		 (copier (get property 'copier))
		 (pvalue-copy (if (and copier (not (eq pvalue *no-value*)))
				  (funcall copier pvalue)
				  pvalue))
		 (p+v (list property pvalue-copy)))
	    (if value-copy
		(setf (cdr value-copy-tail) p+v)
		(setf value-copy p+v))
	    (setf value-copy-tail (cdr p+v))))))

(defun free-env-plist (value)
  (loop (when (null value) (return nil))
	(let* ((property (pop value))
	       (pvalue (pop value))
	       (free-fn (get property 'free-function)))
	  (when free-fn (funcall free-fn pvalue)))))

(defvar *property-name-set-table* (make-hash-table :test 'eql))

(defstruct (property-name-set
	     (:print-function print-property-name-set)
	     (:constructor make-property-name-set-internal))
  mask ; the key
  property-index-vector ; vv-index -> simple-property-index
  (property-name-set-vector nil)
  value-vector-index ; simple-property-index -> vv-index
  value-vector-size)

(defun print-property-name-set (property-name-set stream depth)
  (declare (ignore depth))
  (format stream "#<Property-Name-Set ~S>"
	  (property-name-set-property-list property-name-set)))

(defun property-name-set-property-list (property-name-set)
  (let* ((mask (property-name-set-mask property-name-set))
	 (pmask 1) (property-index 0)
	 (plist nil))
    (declare (fixnum mask pmask property-index))
    (loop (unless (zerop (logand mask pmask))
	    (setq mask (logandc1 pmask mask))
	    (push (aref *translator-property-vector* property-index) plist))
	  (incf property-index)
	  (setq pmask (ash pmask 1))
	  (when (zerop mask) (return (nreverse plist))))))

(defun make-property-name-set (property-mask)
  (with-static-area
    (multiple-value-bind
	  (value-vector-index value-vector-size property-index-vector)
	(compute-value-vector-index property-mask)
      (make-property-name-set-internal
       :mask property-mask
       :property-index-vector property-index-vector
       :value-vector-index value-vector-index
       :value-vector-size value-vector-size))))

(defun compute-value-vector-index (mask)
  (declare (fixnum mask))
  (let* ((value-vector-index 
	  (make-array #.(length *translator-simple-property-list*)
		      :initial-element nil))
	 (value-vector-size (logcount mask))
	 (property-index-vector (make-array value-vector-size :initial-element nil))
	 (pmask 1) (value-index -1) (property-index -1))
    (declare (fixnum pmask value-index property-index)
	     (simple-vector value-vector-index property-index-vector))
    (loop (incf property-index)
	  (when (zerop mask) (return nil))
	  (unless (zerop (logand mask pmask))
	    (setq mask (logandc1 pmask mask))
	    (incf value-index)
	    (setf (svref property-index-vector value-index) property-index)
	    (setf (svref value-vector-index property-index) value-index))
	  (setq pmask (ash pmask 1)))
    (values value-vector-index value-vector-size property-index-vector)))

(defvar *empty-property-name-set*
  (setf (gethash 0 *property-name-set-table*) (make-property-name-set 0)))

(defstruct (environment-entry
	     (:print-function print-environment-entry)
	     (:copier nil)
	     (:constructor make-environment-entry-internal))
  name ; the first argument to translator-environment-get
  property-name-set
  property-value-vector)

(defun print-environment-entry (ee stream depth)
  (declare (ignore depth))
  (format stream "#<Environment-Entry ~S>" (environment-entry-name ee)))

(defvar *first-free-value-vector*
  (make-array #.(length *translator-simple-property-list*)
	      :initial-element nil))

(defmacro get-value-vector (size)
  `(let ((first (svref *first-free-value-vector* ,size)))
     (if first
	 (progn
	   (shiftf (svref *first-free-value-vector* ,size) (svref first 0) nil)
	   first)
	 (with-static-area (make-array ,size :initial-element nil)))))

(defvar *empty-value-vector* '#())

(defmacro free-value-vector (vector size)
  `(unless (eq ,vector *empty-value-vector*)
     (shiftf (svref ,vector 0) (svref *first-free-value-vector* ,size) ,vector)
     nil))

(defvar *first-free-environment-entry* nil)

(defmacro make-environment-entry (&key name property-name-set
				       property-value-vector)
  `(let ((name ,name)
	 (property-name-set ,property-name-set)
	 (property-value-vector ,property-value-vector))
     (if *first-free-environment-entry*
	 (let ((ee *first-free-environment-entry*))
	   (shiftf *first-free-environment-entry*
		   (environment-entry-name ee) name)
	   (setf (environment-entry-property-name-set ee) property-name-set)
	   (setf (environment-entry-property-value-vector ee)
		 property-value-vector)
	   ee)
	 (with-static-area
	   (make-environment-entry-internal
	    :name name
	    :property-name-set property-name-set
	    :property-value-vector property-value-vector)))))

(defmacro new-environment-entry (name)
  `(make-environment-entry :name ,name
			   :property-name-set *empty-property-name-set*
			   :property-value-vector *empty-value-vector*))

(defvar *empty-environment-entry*
  (new-environment-entry "empty environment entry"))

(defun copy-environment-entry (ee)
  (let* ((name (environment-entry-name ee))
	 (property-name-set (environment-entry-property-name-set ee))
	 (value-vector (environment-entry-property-value-vector ee))
	 (value-vector-size
	  (property-name-set-value-vector-size property-name-set))
	 (new-value-vector (make-array value-vector-size :initial-element nil))
	 (property-index-vector
	  (property-name-set-property-index-vector property-name-set)))
    (declare (fixnum value-vector-size)
	     (simple-vector value-vector new-value-vector))
    (dotimes (vv-index value-vector-size)
      (declare (fixnum vv-index))
      (let* ((property-index (svref property-index-vector vv-index))
	     (copier (aref *translator-property-copier-vector* property-index))
	     (value (svref value-vector vv-index)))
	(declare (fixnum property-index))
	(setf (svref new-value-vector vv-index)
	      (if (and copier (not (eq value *no-value*)))
		  (funcall copier value)
		  value))))
    (make-environment-entry :name name
			    :property-name-set property-name-set
			    :property-value-vector new-value-vector)))

(defun free-environment-entry (ee)
  (unless (eq ee *empty-environment-entry*)
    (let* ((property-name-set (environment-entry-property-name-set ee))
	   (value-vector (environment-entry-property-value-vector ee))
	   (value-vector-size
	    (property-name-set-value-vector-size property-name-set))
	   (property-index-vector
	    (property-name-set-property-index-vector property-name-set)))
      (declare (fixnum value-vector-size)
	       (simple-vector value-vector))
      (dotimes (vv-index value-vector-size)
	(declare (fixnum vv-index))
	(let* ((property-index (svref property-index-vector vv-index))
	       (free-fn (aref *translator-property-free-function-vector*
			      property-index))
	       (value (svref value-vector vv-index)))
	  (declare (fixnum property-index))
	  (setf (svref value-vector vv-index) nil)
	  (when (and free-fn value (not (eq value *no-value*)))
	    (funcall free-fn value))))
      (free-value-vector value-vector value-vector-size)
      (setf (environment-entry-property-name-set ee) nil)
      (setf (environment-entry-property-value-vector ee) nil))
    (shiftf (environment-entry-name ee) *first-free-environment-entry* ee))
  nil)
	
(defun environment-entry-plist (ee) ; for debugging
  (when ee
    (check-type ee environment-entry)
    (let* ((property-name-set (environment-entry-property-name-set ee))
	   (property-value-vector (environment-entry-property-value-vector ee))
	   (mask (property-name-set-mask property-name-set))
	   (pmask 1) (value-index -1) (property-index 0)
	   (plist (when (logand mask pmask)
		    (setq mask (logandc1 pmask mask))
		    (svref property-value-vector (incf value-index)))))
      (declare (fixnum mask pmask value-index property-index)
	       (simple-vector property-value-vector))
      (loop (incf property-index)
	    (setq pmask (ash pmask 1))
	    (when (zerop mask) (return plist))
	    (unless (zerop (logand mask pmask))
	      (setq mask (logandc1 pmask mask))
	      (let ((property
		     (aref *translator-property-vector* property-index))
		    (value (svref property-value-vector (incf value-index))))
		(unless (eq value *no-value*)
		  (push value plist)
		  (push property plist))))))))
				   
(defun get-property-name-set (property-name-set property-index)
  (let ((property-name-set-vector
	 (property-name-set-property-name-set-vector property-name-set)))
    (unless property-name-set-vector
      (setq property-name-set-vector
	    (with-static-area
	      (make-array #.(length *translator-simple-property-list*)
			  :initial-element nil)))
      (setf (property-name-set-property-name-set-vector property-name-set)
	    property-name-set-vector))
    (or (svref property-name-set-vector property-index)
	(let* ((property-mask (aref *property-mask-vector* property-index))
	       (property-set-mask (property-name-set-mask property-name-set))
	       (new-property-mask (logior property-mask property-set-mask)))
	  (declare (fixnum property-mask property-set-mask new-property-mask))
	  (setf (svref property-name-set-vector property-index)
		(or (gethash new-property-mask *property-name-set-table*)
		    (setf (gethash new-property-mask *property-name-set-table*)
			  (make-property-name-set new-property-mask))))))))

;when property-index-or-symbol is a symbol,
;the property is on the plist.
(defun environment-entry-get (entry property-index-or-symbol &optional
				    update-descriptor-p)
  (declare (special timpl::*current-translated-file*))
  (unless entry
    (return-from environment-entry-get (values nil nil)))
  (let* ((symbolp (symbolp property-index-or-symbol))
	 (property-index (if symbolp 0 property-index-or-symbol))
	 (property-name-set (environment-entry-property-name-set entry))
	 (value-vector-index
	  (property-name-set-value-vector-index property-name-set))
	 (entry-index (svref value-vector-index property-index)))
    (declare (fixnum property-index)
	     (simple-vector value-vector-index))
    (unless entry-index
      (return-from environment-entry-get (values nil nil)))
    (let* ((value-vector (environment-entry-property-value-vector entry))
	   (value (svref value-vector (the fixnum entry-index))))
      (declare (simple-vector value-vector))
      (when symbolp
	(setq value (getf value property-index-or-symbol *no-value*)))
      (when (and value update-descriptor-p (not (eq value *no-value*)))
	(setf (descriptor-file-cookie value)
	      (when timpl::*current-translated-file*
		(translated-file-cookie
		 timpl::*current-translated-file*))))
      (if (eq value *no-value*)
	  (values nil nil)
	  (values value t)))))
			   
(defun setf-environment-entry-get (entry property-index-or-symbol value
					 &optional update-descriptor-p)
  (declare (special timpl::*current-translated-file*))
  (when (and value update-descriptor-p (not (eq value *no-value*)))
    (setf (descriptor-file-cookie value)
	  (when timpl::*current-translated-file*
	    (translated-file-cookie timpl::*current-translated-file*))))
  (let* ((symbolp (symbolp property-index-or-symbol))
	 (property-index (if symbolp 0 property-index-or-symbol))
	 (property-name-set (environment-entry-property-name-set entry))
	 (value-vector-index
	  (property-name-set-value-vector-index property-name-set))
	 (entry-index (svref value-vector-index property-index))
	 (value-vector (environment-entry-property-value-vector entry)))
    (declare (fixnum property-index)
	     (simple-vector value-vector-index value-vector))
    (unless entry-index
      (let* ((value-vector-size
	      (property-name-set-value-vector-size property-name-set))
	     (property-index-vector
	      (property-name-set-property-index-vector property-name-set))
	     (new-property-name-set
	      (get-property-name-set property-name-set property-index))
	     (new-value-vector-index
	      (property-name-set-value-vector-index new-property-name-set))
	     (new-value-vector-size
	      (property-name-set-value-vector-size new-property-name-set))
	     (new-value-vector
	      (get-value-vector new-value-vector-size))
	     (new-entry-index (svref new-value-vector-index property-index)))
	(declare (fixnum value-vector-size new-value-vector-size
			 new-entry-index)
		 (simple-vector property-index-vector
				new-value-vector-index new-value-vector))
	(dotimes (vv-index value-vector-size)
	  (declare (fixnum vv-index))
	  (let* ((property-index (svref property-index-vector vv-index))
		 (new-vv-index (svref new-value-vector-index property-index)))
	    (declare (fixnum property-index new-vv-index))
	    (shiftf (svref new-value-vector new-vv-index)
		    (svref value-vector vv-index) nil)))
	(when (zerop property-index)
	  (setf (svref new-value-vector new-entry-index) nil))
	(free-value-vector value-vector value-vector-size)
	(setf (environment-entry-property-name-set entry)
	      new-property-name-set)
	(setf (environment-entry-property-value-vector entry)
	      new-value-vector)
	(setq value-vector new-value-vector
	      entry-index new-entry-index)))
    (let ((free-fn (if symbolp
		       (get property-index-or-symbol 'free-function)
		       (aref *translator-property-free-function-vector*
			     property-index))))
      (when free-fn
	(let ((old (if symbolp
		       (getf (svref value-vector entry-index)
			     property-index-or-symbol)
		       (svref value-vector entry-index))))
	  (when (and old (not (eq old *no-value*)))
	    (funcall free-fn old)))))
    (if symbolp
	(setf (getf (svref value-vector entry-index)
		    property-index-or-symbol)
	      value)
	(setf (svref value-vector entry-index) value))))

(defun environment-entry-internal (name &optional env create-p)
  (setq env (environmentify env))
  (let* ((complete-name name)
	 (table (translator-environment-global-table name env)))
    (or (gethash1 name table)
	(if create-p
	    (setf (gethash1 name table)
		  (new-environment-entry complete-name))
	    *empty-environment-entry*))))

(defmacro environment-entry (name &optional env create-p)
  (once-only (name env)
    `(if (environment-entry-p ,name)
	 ,name
	 (environment-entry-internal ,name ,env ,create-p))))

(defmacro name-and-environment-entry (name &optional env create-p)
  (once-only (name env)
    `(if (environment-entry-p ,name)
	 (values (environment-entry-name ,name) ,name)
	 (values ,name
		 ,(if (and (constantp create-p)
			   (eq :nolookup (eval create-p)))
		      `nil
		      `(environment-entry-internal ,name ,env ,create-p))))))

;;; Get the value associated with the given property.

(defmacro translator-environment-get (name env property)
  (if (constantp property)
      `(environment-entry-get
	(environment-entry ,name ,env)
	(property-index-or-symbol ,property)
	,(let ((property (eval property)))
	   (or (eq property 'defined-as-variable)
	       (eq property 'defined-as-function)
	       (eq property 'defined-as-symbol)
	       (eq property 'defined-as-package))))
      (once-only (env name property)
	`(environment-entry-get
	  (environment-entry ,name ,env)
	  (property-index-or-symbol ,property)
	  (or (eq ,property 'defined-as-variable)
	      (eq ,property 'defined-as-function)
	      (eq ,property 'defined-as-symbol)
	      (eq ,property 'defined-as-package))))))

(defsetf translator-environment-get
    (name env property)
    (value)
  `(setf-translator-environment-get ,name ,env ,property ,value))

(defmacro setf-translator-environment-get (name env property value)
  (if (constantp property)
      `(setf-environment-entry-get
	(environment-entry ,name ,env t)
	(property-index-or-symbol ,property)
	,value
	,(let ((property (eval property)))
	   (or (eq property 'defined-as-variable)
	       (eq property 'defined-as-function)
	       (eq property 'defined-as-symbol)
	       (eq property 'defined-as-package))))
      (once-only (env name property value)
        `(setf-environment-entry-get
	  (environment-entry ,name ,env t)
	  (property-index-or-symbol ,property)
	  ,value
	  (or (eq ,property 'defined-as-variable)
	      (eq ,property 'defined-as-function)
	      (eq ,property 'defined-as-symbol)
	      (eq ,property 'defined-as-package))))))

;;; Remove the property.

(defun translator-environment-remprop (name env property)
  (setf (translator-environment-get name env property) *no-value*))


;;; Map over all properties associated with the given name.  The function
;;; argument is passed the property name and associated value.
;Not currently used
(defun translator-map-environment-properties (function name env)
  (let ((plist (environment-entry-plist (environment-entry env name))))
    (loop (when (null plist) (return nil))
	  (funcall function (pop plist) (pop plist)))))


;;; Map over all names that have a specific property defined.  The function
;;; argument is passed the name and property value.
;Used in several places.  with-sorted-data is the most important use.
(defun translator-map-environment-names (function env property)
  (setq env (environmentify env))
  (let ((property-index-or-symbol (property-index-or-symbol property)))
    (flet ((map-table (name environment-entry)
	     (declare (ignore name))
	     (multiple-value-bind (value there-p)
		 (environment-entry-get environment-entry
					property-index-or-symbol
					nil)
	       (when there-p
		 (funcall function
			  (environment-entry-name environment-entry)
			  value)))))
      (maphash #'map-table (translator-environment-global-simple-part env))
      (maphash #'map-table (translator-environment-global-other-part env))
      (maphash #'map-table
	       (translator-environment-global-setf-symbol-part env)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Global environment -- high level
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Define-translator-property is used to define all the various
;;; namespaces used by the translator.  It defines an accessor macro
;;; (which is setf'able) with the same name as the property.
;;; This is exported.  Properties which define namespaces which are
;;; referenced in more than one place are defined in this file, but
;;; namespaces that are internal to other modules are defined in those
;;; modules.
;;; *** This should also be where the copying protocol needed by 
;;; *** copy-environment is declared.

;;; *** problem; struct must be defined before translator property.
(defmacro define-translator-property (accessor-name
				      &optional copier free-function)
  (let ((property-name accessor-name)
	#||(setf-accessor-name
	    (intern (sformat "~A-~A" 'setf accessor-name)))||#
	(set-accessor-name (intern (sformat "~A-~A" 'set accessor-name))))
    `(progn
       (eval-when (compile)
	 (add-translator-property ',property-name))
       (eval-when (load eval)
	 (add-translator-property ',property-name ,copier ,free-function))
       #||
       (defmacro ,accessor-name (name &optional env)
	 `(translator-environment-get ,name ,env ',',property-name))
       ||#
       (defun ,accessor-name (name &optional env)
	 (translator-environment-get name env ',property-name))
       #||
       (defmacro ,setf-accessor-name (name env &optional (value nil valuep))
	 (if valuep
	     `(setf-translator-environment-get ,name ,env ',',property-name
					       ,value)
	     `(setf-translator-environment-get ,name nil ',',property-name
					       ,env)))
       (defsetf ,accessor-name ,setf-accessor-name)
       (defun ,set-accessor-name (value name &optional env)
	 (setf (,accessor-name name env) value))
       ||#
       (defun ,set-accessor-name (value name &optional env)
	 (setf-translator-environment-get name env ',property-name value))
       (defsetf ,accessor-name (name &optional env) (value)
	 `(,',set-accessor-name ,value ,name ,env))
       ',accessor-name)))
					 
;;; Useful function for creating copiers.
(defmacro define-copier (name &key structure-name
			      (creator
			       (intern
				(concatenate 'string "MAKE-"
					     (symbol-name structure-name))
				(symbol-package structure-name)))
			      (predicate
			       (intern
				(concatenate 'string
					     (symbol-name structure-name)
					     "-P")
				(symbol-package structure-name)))
			      (nil-ok t)
			      (other-values-ok nil)
			      slot-functions)
  (flet ((attach-prefix (symbol)
	   (if structure-name
	       (intern
		(concatenate 'string
			     (symbol-name structure-name) "-"
			     (symbol-name symbol))
		(symbol-package structure-name))
	       symbol)))
    (let ((new (make-symbol "NEW"))
	  (old (make-symbol "OLD")))
      (when structure-name
	(setf slot-functions
	      (mapcar #'(lambda (slot-function)
			  (if (consp slot-function)
			      (cons (attach-prefix (car slot-function))
				    (cdr slot-function))
			      (attach-prefix slot-function)))
		      slot-functions)))
      `(defun ,name (,old)
	 (cond
	   ,@(when nil-ok
	       `(((null ,old) nil)))
	   ((,predicate ,old)
	    (let ((,new (,creator)))
	      ,@(mapcar
		 #'(lambda (slot-function)
		     (if (consp slot-function)
			 `(setf (,(car slot-function) ,new)
				(funcall ,(cadr slot-function)
					 (,(car slot-function) ,old)))
			 `(setf (,slot-function ,new)
				(,slot-function ,old))))
		 slot-functions)
	      ,new))
	   (t ,(if other-values-ok
		   old
		   `(error "Internal error: Object ~A, found while copying ~
                            environment, does not satisfy propery ~A; please ~
                            reload translator and contact Chestnut Technical ~
                            support"
			   ,old
			   ',predicate))))))))

;;; Properties used internally in this file

(define-translator-property variable-proclamations #'copy-list)
(define-translator-property function-proclamations #'copy-list)
(define-translator-property random-set-proclamation #'copy-list)
(define-translator-property random-proclamation #'identity)


;;; Properties used both in this file and elsewhere to represent
;;; global name bindings.  These symbols are exported from the TUTIL
;;; package.

(define-translator-property defined-as-variable
    'copy-variable-descriptor 'free-variable-descriptor)
(define-translator-property defined-as-function
    'copy-function-descriptor 'free-function-descriptor)
(define-translator-property defined-as-macro #'identity)
(define-translator-property defined-as-special-form #'identity)
(define-translator-property defined-as-toplevel-form #'identity)

(define-translator-property defined-as-declaration #'identity)

;;; quoted symbols need to recorded in the environment so that
;;; the fact that function and symbol linking code needs to be generated
;;; with the symbol code can be recorded there.

(define-translator-property defined-as-quoted-symbol
  'timpl::copy-symbol-record)

;;;*** Add accessors for SETF methods, type definitions, etc. here.

;;; setf methods
(define-translator-property defined-as-generalized-variable #'identity)
(define-translator-property simple-setf-update-function #'identity)

(define-translator-property defined-as-deftype #'identity)
(define-translator-property defined-as-compiler-macro #'identity)
(define-translator-property defined-as-optimize-quality #'identity)

;;; accessor for structure information
(defun defined-as-structure-copier (structure-info)
  (ecase (type-of structure-info)
    (timpl::vector-structure-info
     (timpl::copy-vector-structure-info structure-info))
    (timpl::list-structure-info
     (timpl::copy-list-structure-info structure-info))
    (timpl::typed-structure-info
     (timpl::copy-typed-structure-info structure-info))
    (timpl::untyped-structure-info
     (timpl::copy-untyped-structure-info structure-info))
    (timpl::structure-info
     (timpl::copy-structure-info structure-info))
    (timpl::structure-info-root
     (timpl::copy-structure-info-root structure-info))))

(define-translator-property defined-as-structure #'defined-as-structure-copier)


;;; It's important that we not make copies of the classes, since if we have
;;; done a
;;; (setf (find-class 'foo) (find-class 'bar))
;;; It can happen (and be important) that
;;; (eq (defined-as-class 'foo) (defined-as-class 'bar))
;;; The translator doesn't use any of the slots on the class, since it
;;; uses the class record and its slots instead. 
#+translator-supports-clos
(define-translator-property defined-as-class #'identity)





(define-copier copy-defined-as-variable-entry
  :structure-name variable-descriptor
  :slot-functions
  (constant-p
   global-p
   documentation
   value-p
   value 
   foreign-p
   dump-definition-p
   linked-locally-p
   ;;redefinition-record
   ))


(defun variable-redefinition-record (symbol)
  (let ((descriptor (defined-as-variable symbol)))
    (cond
      ((not descriptor)
       (error "Internal error - No descriptor for special variable ~S" symbol))
      ((variable-descriptor-redefinition-record descriptor))
      (t
       (setf (variable-descriptor-redefinition-record descriptor)
	     (compute-redefinition-record))))))


;;; Inherit information from old variable descriptor, rather than
;;; making a new one; this will ensure that redefinition records
;;; are maintained.

;;; This function should always be used in place of (setf defined-as-variable)
;;; if an earlier descriptor may exist.

(defmacro update-variable-descriptor (name env &rest args)
  `(update-variable-descriptor-internal
    ,name ,env (make-variable-descriptor ,@args)))

(defun update-variable-descriptor-internal (name env new-descriptor)
  (let ((old-descriptor (defined-as-variable name env)))
    (when old-descriptor
      (setf (variable-descriptor-redefinition-record new-descriptor)
	    (variable-descriptor-redefinition-record old-descriptor))
      (unless (variable-descriptor-documentation new-descriptor)
	(setf (variable-descriptor-documentation new-descriptor)
	      (variable-descriptor-documentation old-descriptor))))
    (setf (defined-as-variable name env) new-descriptor)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Environment accessors
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Variable information (exported)

(defun translator-variable-information (name &optional env return-contours-p)
  (setq env (environmentify env))
  (multiple-value-bind (name entry)
      (name-and-environment-entry name env :nolookup)
    (let ((contour-list (translator-environment-lexical-part env))
	  (old-contour-list
	   (and (translator-environment-p return-contours-p)
		(translator-environment-lexical-part return-contours-p))))
      (loop
       (unless contour-list
	 (return (global-variable-information (or entry name) env)))
       (when (eq contour-list old-contour-list)
	 (setq return-contours-p nil))
       (let ((contour (car contour-list)))
	 (when (and (variable-information-contour-p contour)
		    (eq name (variable-information-contour-name contour)))
	   (return
	     (values
	      (variable-information-contour-usage contour)
	      (variable-information-contour-locally-bound-p contour)
	      (variable-information-contour-declarations contour)
	      (when return-contours-p contour)))))
       (setq contour-list (cdr contour-list))))))

(defun add-declaration-to-variable-information-contour (declaration contour)
  (let ((name (car declaration)))
    (dolist (name+value (variable-information-contour-declarations contour))
      (when (eq name (car name+value))
	(if (eq (cdr declaration) (cdr name+value))
	    (return-from add-declaration-to-variable-information-contour
	      contour)
	    (return nil)))))
  (push declaration (variable-information-contour-declarations contour))
  contour)
  
(defun global-variable-information (name env)
  (multiple-value-bind (name entry)
      (name-and-environment-entry name env)
    (values (let ((info (defined-as-variable entry)))
	      (cond ((null info)
		     (if (keywordp name) :constant nil))
		    ((variable-descriptor-constant-p info)
		     :constant)
		    ((not (variable-descriptor-global-p info))
		     nil)
		    (t
		     :special)))
	    nil
	    (variable-proclamations entry))))


;;; Function information (exported)

(defun translator-function-information (name &optional env return-contours-p)
  (setq env (environmentify env))
  (multiple-value-bind (name entry)
      (name-and-environment-entry name env :nolookup)
    (let ((contour-list (translator-environment-lexical-part env))
	  (old-contour-list
	   (and (translator-environment-p return-contours-p)
		(translator-environment-lexical-part return-contours-p))))
      (loop
       (unless contour-list
	 (return (global-function-information (or entry name) env)))
       (when (eq contour-list old-contour-list)
	 (setq return-contours-p nil))
       (let ((contour (car contour-list)))
	 (when (and (function-information-contour-p contour)
		    (eq name (function-information-contour-name contour)))
	   (let ((usage (function-information-contour-usage contour))
		 (l-b-p
		  (function-information-contour-locally-bound-p contour)))
	     (return
	       (values
		usage
		(if (and l-b-p (eq usage :macro)) (car l-b-p) l-b-p)
		(function-information-contour-declarations contour)
		(when return-contours-p contour))))))
       (setq contour-list (cdr contour-list))))))

;;; Special Form must remain last because some special forms in
;;; the host enviroment are functions in translation environment.

(defun global-function-information (name env)
  (multiple-value-bind (name entry)
      (name-and-environment-entry name env)
    (values
     (cond ((defined-as-macro entry)
	    :macro)
	   ((defined-as-function entry)
	    :function)
	   ((and (symbolp name)
		 (let ((mf (macro-function name)))
		       (when mf
			 ;;(warn "Using host macro definition for ~S" name)
			 mf)))
	    :macro)
	   ((defined-as-special-form entry)
	    :special-form)
	   (t nil))
     nil
     (function-proclamations entry))))

;;; Declaration information (exported)

(defun translator-set-declaration-information (name &optional env
						    return-contours-p)
  (setq env (environmentify env))
  (multiple-value-bind (name entry)
      (name-and-environment-entry name env :nolookup)
    (let ((contour-list (translator-environment-lexical-part env))
	  (old-contour-list
	   (and (translator-environment-p return-contours-p)
		(translator-environment-lexical-part return-contours-p))))
      (loop
       (unless contour-list
	 (return (global-set-declaration-information (or entry name) env)))
       (when (eq contour-list old-contour-list)
	 (setq return-contours-p nil))
       (let ((contour (pop contour-list)))
	 (when (and (set-declaration-information-contour-p contour)
		    (eq name
			(set-declaration-information-contour-name contour)))
	   (return
	     (values
	      (set-declaration-information-contour-declarations contour)
	      (when return-contours-p contour)))))))))

(defun global-set-declaration-information (name env)
  (random-set-proclamation name env))

(defun translator-declaration-information (name &optional env
						return-contours-p)
  (setq env (environmentify env))
  (multiple-value-bind (name entry)
      (name-and-environment-entry name env :nolookup)
    (let ((contour-list (translator-environment-lexical-part env))
	  (old-contour-list
	   (and (translator-environment-p return-contours-p)
		(translator-environment-lexical-part return-contours-p))))
      (loop
       (unless contour-list
	 (return (global-declaration-information (or entry name) env)))
       (when (eq contour-list old-contour-list)
	 (setq return-contours-p nil))
       (let ((contour (pop contour-list)))
	 (when (and (declaration-information-contour-p contour)
		    (eq name (declaration-information-contour-name contour)))
	   (return
	     (values
	      (declaration-information-contour-value contour)
	      (when return-contours-p contour)))))))))

(defun global-declaration-information (name env)
  (random-proclamation name env))





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Augment-environment and friends
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Augment-environment and parse-declarations do exactly the same thing
;;; but return different values (augment-environment returns a modified
;;; environment and parse-declarations returns a list of parsed declarations).
;;; They both call the same helper function.
;;; These two functions are exported.

(defun translator-augment-environment (env &key variable symbol-macro
					   function macro declare
					   (function-name nil function-name-p)
					   function-info
					   multiple-execution-p
					   conditional-execution-p)
  (augment-environment-aux
   env variable symbol-macro function macro declare nil
   function-name function-name-p function-info
   multiple-execution-p conditional-execution-p))


(defstruct multiple-execution-contour)
(defstruct conditional-execution-contour)

(defun function-or-multiple-execution-contour-list-p 
    (use-contour-list &optional base-contour-list)
  (loop (when (or (null use-contour-list)
		  (eq use-contour-list base-contour-list))
	  (return nil))
	(let ((contour (pop use-contour-list)))
	  (when (or (multiple-execution-contour-p contour)
		    (function-name-contour-p contour))
	    (return t)))))

(defun function-or-multiple-execution-env-p (use-env &optional binding-env)
  (function-or-multiple-execution-contour-list-p
   (translator-environment-lexical-part use-env)
   (when binding-env (translator-environment-lexical-part binding-env))))

(defun translator-parse-declarations (declare env &key variable symbol-macro
					      function macro)
  ;(when t (print "_translator_parse_decl"))
  (augment-environment-aux
   env variable symbol-macro function macro declare t nil nil nil nil nil))


;;; First add the bindings to the environment, then parse declarations.
;;; We make a copy of the environment here so that we can bash it 
;;; destructively in the helper functions.

(defun augment-environment-aux (env variable symbol-macro function macro
				    decl-specs collect-p
				    function-name function-name-p function-info
				    multiple-execution-p
				    conditional-execution-p)
  (setq env (environmentify env))
  (unless (and (listp variable)
	       (every #'symbolp variable))
    (error "Bad :variable argument syntax ~s." variable))
  (unless (and (listp symbol-macro)
	       (every #'(lambda (x)
			  (and (consp x)
			       (symbolp (car x))
			       (eql (length x) 2)))
		      symbol-macro))
    (error "Bad :symbol-macro argument syntax ~s." symbol-macro))
  (unless (and (listp function)
	       (every #'valid-function-name-p function))
    (error "Bad :function argument syntax ~s." function))
  (unless (and (listp macro)
	       (every #'(lambda (x)
			  (and (consp x)
			       (symbolp (car x))
			       (functionp (cadr x))
			       (consp (cddr x))))
		      macro))
    (error "Bad :macro argument syntax ~s." macro))
  (unless (and (listp decl-specs)
	       (every #'consp decl-specs))
    (error "Bad :declare argument syntax ~s." decl-specs))
  (let ((new-env (copy-translator-environment-internal env)))
    (when function-name-p
      (setq new-env (add-function-name-binding new-env function-name
					       function-info)))
    (when multiple-execution-p
      (setq new-env (add-multiple-execution-binding new-env)))
    (when conditional-execution-p
      (setq new-env (add-conditional-execution-binding new-env)))
    (setq new-env
	  (add-variable-bindings new-env variable symbol-macro decl-specs))
    (setq new-env (add-function-bindings new-env function macro))
    (parse-declarations-aux decl-specs new-env collect-p env)))

(defun add-multiple-execution-binding (env)
  (push (make-multiple-execution-contour)
	(translator-environment-lexical-part env))
  env)

(defun add-conditional-execution-binding (env)
  (push (make-conditional-execution-contour)
	(translator-environment-lexical-part env))
  env)

;;; Helper functions for adding the bindings to the environment.  Note
;;; that add-variable-bindings must also look for SPECIAL declarations.
;;; Free SPECIAL declarations are treated like bindings because they
;;; shadow any outer lexical bindings of the variable name.

;;;  Note that this is tutil::add-variable-bindings.
;;; timpl::add-variable-bindings (defined in dump.lisp) is a completely
;;; different function.
(defun add-variable-bindings (env variable symbol-macro decl-specs)
  (let ((specials  (look-for-special-declarations decl-specs)))
    (add-special-variable-descriptors specials)
    (dolist (v symbol-macro)
      (cond ((member (car v) specials :test #'eq)
	     (error "~s cannot be both SPECIAL and a symbol-macro."
		    (car v)))
	    ((member (car v) variable :test #'eq)
	     (error "~s cannot be both a symbol-macro and a variable."
		    (car v)))
	    (t
	     (push (make-variable-information-contour
		    :name (car v)
		    :usage :symbol-macro
		    :locally-bound-p
		    (make-symbol-macro-function (cadr v))
		    :declarations nil)
		   (translator-environment-lexical-part env)))))
    (dolist (v variable)
      (let ((info  (defined-as-variable v env)))
	(cond ((and info (variable-descriptor-constant-p info))
	       (error "The defined constant ~s cannot be rebound."
		      v))
	      ((or (and info (variable-descriptor-global-p info))
		   (member v specials :test #'eq))
	       (push (make-variable-information-contour
		      :name v
		      :usage :special
		      :locally-bound-p t
		      :declarations (variable-proclamations v env))
		     (translator-environment-lexical-part env)))
	      (t
	       (push (make-variable-information-contour
		      :name v
		      :usage :lexical
		      :locally-bound-p t
		      :declarations (list `(tx:binding-environment . ,env)))
		     (translator-environment-lexical-part env))))))
    (dolist (v specials)
      (if (not (member v variable :test #'eq))
	  (let* ((old-contour
		  (find-special-binding v env))
		 (locally-bound-p
		  (if old-contour
		      (variable-information-contour-locally-bound-p
		       old-contour)
		      nil))
		 (declarations
		  (if old-contour
		      (variable-information-contour-declarations
		       old-contour)
		      (variable-proclamations v env))))
	    (push (make-variable-information-contour
		   :name v
		   :usage :special
		   :locally-bound-p locally-bound-p
		   :declarations declarations)
		  (translator-environment-lexical-part env)))))
    env))

;;; The CL spec permits the expansion of symbol macros to be stored either
;;; in the expansion function, or in the environment.  We store it in the
;;; expansion function.

(defun make-symbol-macro-function (expansion)
  #'(lambda (form env)
      (declare (ignore form env))
      expansion))


;;; Find all the special declarations in the list.  Look for both parsed
;;; and unparsed declarations.

(defun look-for-special-declarations (decl-specs)
  (let ((specials  nil))
    (dolist (d decl-specs)
      (cond ((eq (car d) 'special)
	     (dolist (name (cdr d))
	       (push name specials)))
	    ((eq (car d) 'tx:variable-information)
	     (dolist (info (cdr d))
	       (if (eq (second info) 'special)
		   (push (first info) specials))))
	    (t nil)))
    specials))


;;; Make sure that all special variables have variable descriptors.
;;; This ensures that they will be dumped as C globals.

(defun add-special-variable-descriptors (specials)
  (dolist (v specials)
    (let ((descriptor (defined-as-variable v)))
      (if descriptor
	  ;; Update these guys if retranslating
	  (setf (variable-descriptor-linked-locally-p descriptor) t)
	  (progn
	    (setf (defined-as-variable v)
		  (make-variable-descriptor
		   :constant-p nil
		   :global-p nil
		   :documentation nil))
	    (assign-C-names-for-global-variable v))))))


;;; Assign-C-names-for-global-variable
;;;   Helper function for add-special-variable-descriptors
;;;     and for defvar & friends.

(define-forward-variable-reference *special-symbols*)

(defun assign-C-names-for-global-variable (name)
  (c-name-of-global-variable name)
  (c-name-of-quoted-symbol name)
  (when (and *special-symbols* 
	     (forward-defined-as-symbol name))
    (mark-quoted-symbol name)))


;;; If "name" is specially bound in "env", return the contour.  Otherwise
;;; return NIL.

(defun find-special-binding (name env)
  (dolist (contour (translator-environment-lexical-part env))
    (if (and (variable-information-contour-p contour)
	     (eq (variable-information-contour-name contour) name)
	     (eq (variable-information-contour-usage contour) :special))
	(return contour))))


;;; Add function and macro bindings to the environment.

(defun add-function-bindings (env function macro)
  (dolist (f macro)
    (cond ((member (car f) function :test #'eq)
	   (error "~s cannot be both a macro and a function." (car f)))
	  (t
	   (push (make-function-information-contour
		  :name (car f)
		  :usage :macro
		  :locally-bound-p (cdr f)
		  :declarations nil)
		 (translator-environment-lexical-part env)))))
  (dolist (f function)
    (push (make-function-information-contour
	   :name f
	   :usage :function
	   :locally-bound-p t
	   :declarations (list `(tx:binding-environment . ,env)))
	  (translator-environment-lexical-part env)))
  env)

(defun add-function-name-binding (env name &optional info)
  (push (make-function-name-contour :name name :info info)
	(translator-environment-lexical-part env))
  env)


;;; OK, now that all the binding and SPECIAL information is in the
;;;     environment, collect up all the parsed decl-specs.
;;; Recall that each declaration parsing function returns four values:
;;;   (1) a list of (name key value)s for names that refer to variables.
;;;   (2) a list of (name key value)s for names that refer to functions.
;;;   (3) a list of (name key value)s for other names
;;;   (4) a list of (key . value)s for decls that do not apply to
;;;           variable or function names. 
;;; Note that we have *not* implemented either proposal from X3J13 issue
;;; DEFINE-DECLARATION-FORMAT-INCONSISTENT.
;;;
;;; *** There are some general concerns here about making sure that the
;;; *** values returned from a single decl-spec are being added to the 
;;; *** environment in the right order.
;;;
;;; *** We could reduce some of the consing here by merging declarations
;;; *** onto other contours that were added to the environment during
;;; *** the same call to augment-environment-aux.  We'd have to flag
;;; *** contours with a new-p flag and then know enough to reset them all
;;; *** before returning from augment-environment-aux.

(defun parse-declarations-aux (decl-specs env collect-p old-env)
  (let ((var-info  nil)
	(fun-info  nil)
	(set-decl-info nil)
	(decl-info nil))
    (dolist (decl-spec decl-specs)
      (multiple-value-bind (this-var-info this-fun-info
			    this-set-decl-info this-decl-info)
	  (parse-declaration decl-spec env)
	(when collect-p
	  (setq var-info (append this-var-info var-info))
	  (setq fun-info (append this-fun-info fun-info))
	  (setq set-decl-info (append this-set-decl-info set-decl-info))
	  (setq decl-info (append this-decl-info decl-info)))
	(setq env
	      (add-decls-to-env env old-env
				this-var-info this-fun-info
				this-set-decl-info this-decl-info))))
    (if collect-p
	(values var-info fun-info set-decl-info decl-info)
	env)))


;;; SPECIAL is treated specially here because it has such weird semantics
;;; (different rules for proclaim vs. declare).

(defun parse-declaration (decl-spec env)
  (let ((handler nil))
    (cond ((eq (car decl-spec) 'special)
	   (values (mapcar #'(lambda (n) `(,n special t)) (cdr decl-spec))
		   nil nil nil))
	  ((setq handler (defined-as-declaration (car decl-spec)))
	   (funcall handler decl-spec env))
	  (t
	   (if (translator-type-specifier-p (car decl-spec) env)
	       (parse-declaration `(type ,@decl-spec) env)
	       (progn
		 (warn "Ignoring unknown declaration ~s." decl-spec)
		 (values nil nil nil nil)))))))

(defun add-decls-to-env (env old-env var-info fun-info set-decl-info decl-info)
  (dolist (d var-info)
    (multiple-value-bind (usage bound-p decls contour)
	(translator-variable-information (first d) env old-env)
      (let ((value (cons (second d) (third d))))
	(if contour
	    (push value
		  (variable-information-contour-declarations contour))
	    (push (make-variable-information-contour
		   :name (first d)
		   :usage usage
		   :locally-bound-p bound-p
		   :declarations (cons value decls))
		  (translator-environment-lexical-part env))))))
  (dolist (d fun-info)
    (multiple-value-bind (usage bound-p decls contour)
	(translator-function-information (first d) env old-env)
      (let ((value (cons (second d) (third d))))
	(if contour
	    (push value
		  (function-information-contour-declarations contour))
	    (push (make-function-information-contour
		   :name (first d)
		   :usage usage
		   :locally-bound-p bound-p
		   :declarations (cons value decls))
		  (translator-environment-lexical-part env))))))
  (dolist (d set-decl-info)
    (multiple-value-bind (decls contour)
	(translator-set-declaration-information (first d) env old-env)
      (let ((value (cons (second d) (third d))))
	(if contour
	    (push value
		  (set-declaration-information-contour-declarations contour))
	    (push (make-set-declaration-information-contour
		   :name (first d)
		   :declarations (cons value decls))
		  (translator-environment-lexical-part env))))))
  (dolist (d decl-info)
    (push (make-declaration-information-contour
	   :name (car d)
	   :value (cdr d))
	  (translator-environment-lexical-part env)))
  env)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Define declaration handlers
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Here's the defining macro definition.

(defmacro define-translator-declaration (name lambda-list &body body)
  (let ((fname (intern (sformat "~A-DECLARATION-HANDLER" name))))
    (multiple-value-bind (body decls doc) (parse-body body t)
      (declare (ignore doc))		;***
      `(progn
	 (eval-when (#-translating compile)
	   (when (translator-type-specifier-p ',name)
	     (warn "Defining ~S as a declaration, but it's already a type."
		   ',name)))
	 (when (translator-type-specifier-p ',name)
	   (error "Defining ~S as a declaration, but it's already a type."
		  ',name))
	 (pushnew ',name (random-proclamation 'declaration))
	 (defun ,fname ,lambda-list
	   (declare ,@decls)
	   (block ,name ,@body))
	 (setf (defined-as-declaration ',name) #',fname)
	 ',name))))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    PROCLAIM
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun random-declaration-handler (decl-spec env)
  (declare (ignore decl-spec env))
  (values nil nil nil nil))

;;; Again, SPECIAL is special because it has such weird semantics.
;;; *** Watch out for ordering problems again.
;;; This is exported.

(defun translator-proclaim (decl-spec &optional env)
  (let ((handler  nil))
    (cond ((eq (car decl-spec) 'special)
	   (dolist (name (cdr decl-spec))
	     (update-variable-descriptor name env
					 :constant-p nil)))
	  ((setq handler (defined-as-declaration (car decl-spec) env))
	   (multiple-value-bind (var-info fun-info set-decl-info decl-info)
	       (funcall handler decl-spec env)
	     (dolist (d var-info)
	       (push (cons (second d) (third d))
		     (variable-proclamations (first d) env)))
	     (dolist (d fun-info)
	       (push (cons (second d) (third d))
		     (function-proclamations (first d) env)))
	     (dolist (d set-decl-info)
	       (push (cons (second d) (third d))
		     (random-set-proclamation (first d) env)))
	     (dolist (d decl-info)
	       (setf (random-proclamation (car d) env) (cdr d)))))
	  ((eq (car decl-spec) 'declaration)
	   (dolist (name (cdr decl-spec))
	     (let ((handler (defined-as-declaration name env)))
	       (when (and handler
			  (not (eq handler #'random-declaration-handler)))
		 (warn "Redefining the translator declaration ~S" name)))
	     (pushnew name (random-proclamation 'declaration env))
	     (setf (defined-as-declaration name env)
		   #'random-declaration-handler)))
	  ((translator-type-specifier-p (car decl-spec) env)
	   (translator-proclaim `(type ,@decl-spec) env))
	  (t
	   (warn "Ignoring unknown proclamation ~s." decl-spec)))))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Support for macros
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Get "our" macro definition.  Returns macros defined in the host Lisp
;;; sometimes.
;;; This is exported.

(defvar *host-macro-table* (make-hash-table :test 'eq))
(defvar *warn-about-host-macro-expansions* nil)

(defun translator-macro-function (name &optional env)
  (multiple-value-bind (name entry)
      (name-and-environment-entry name env)
    (let ((entry-or-name (if (eq entry *empty-environment-entry*)
			     name
			     entry)))
      (multiple-value-bind (usage bound-p decls)
	  (translator-function-information entry-or-name env)
	(declare (ignore decls))
	(if (not (eq usage :macro))
	    nil
	    (let ((mdef (or bound-p
			    (defined-as-macro entry))))
	      (if mdef
		  (values mdef env)
		  ;; Don't call host's macro-function with non-symbol
		  ;; function name, since it might not handle such a case.
		  ;; Since macros cannot have non-symbolic names (as per
		  ;; X3J13 FUNCTION-NAME proposal), this is ok.  Note that it
		  ;; might instead be an error to call this on a non-symbol.
		  (when (and (symbolp name)
			     ;; If name is treated as a special form by
			     ;; the translator, don't use host's
			     ;; macro definition even if it exists.
			     (not (defined-as-special-form entry))
			     ;; If the Translator has a function or
			     ;; macro definition, use that.
			     (not (defined-as-function entry)))
		    (when (and *warn-about-host-macro-expansions*
			       (not (gethash name *host-macro-table*)))
		      (setf (gethash name *host-macro-table*) t)
		      (warn "Using the host lisp's definition of macro ~S"
			    name))
		    (values (macro-function name) nil)))))))))

(defun set-translator-macro-function (value name &optional env)
  (if value
      (setf (defined-as-macro name env) value)
      (progn
	(translator-environment-remprop name env 'defined-as-macro)
	value)))

(define-setf-method translator-macro-function (name &optional env)
  (make-translator-macro-function-setf-method
   name env
   'translator-macro-function 'set-translator-macro-function))

(defun make-translator-macro-function-setf-method (name env getter setter)
  (let* ((vals (cons name (when env (list env))))
	 (vars (mapcar #'(lambda (val) (declare (ignore val)) (gensym)) vals))
	 (store (gensym)))
    (values vars
	    vals
	    (list store)
	    `(,setter ,store ,@vars)
	    `(,getter ,@vars))))
    


;;; This will break user-defined macros that use &environment and
;;; pass it along to an explicit call to the host Lisp's macroexpand
;;; function.  Should we be concerned?
;;; These two functions are exported.

(defun translator-macroexpand-1 (form &optional env)
  (let ((temp nil)(macro-env nil))
    (cond ((consp form)
	   (if (and (symbolp (setq temp (car form)))
		    (multiple-value-setq (temp macro-env)
		      (translator-macro-function temp env)))
	       (values (call-macro-function temp form macro-env) t)
	       (values form nil)))
	  ((symbolp form)
	   (expand-symbol-macro form env))
	  (t
	   (values form nil)))))

(defun translator-macroexpand (form &optional env)
  (let ((macro-p  nil))
    (loop
     (multiple-value-bind (new-form new-macro-p)
	 (translator-macroexpand-1 form env)
       (if new-macro-p
	   (progn
	     (setq macro-p t)
	     (setq form new-form))
	   (return (values new-form macro-p)))))))


;;; Recall that the expansion of symbol macros is stored in the function
;;; that is returned as the bound-p value from variable-information.

(defun expand-symbol-macro (form env)
  (multiple-value-bind (usage bound-p decls)
      (translator-variable-information form env)
    (declare (ignore decls))
    (if (not (eq usage :symbol-macro))
	(values form nil)
	(values (call-macro-function bound-p form env) t))))

;;; TRANSLATOR-SYMBOL-MACROEXPAND-1
;;;
;;; Expand a symbol, wrapping any appropriate THE declaration around the
;;; expansion if it is a symbol macro.  This function hides any dependence on
;;; the resolution of X3J13 issue SYMBOL-MACROLET-TYPE-DECLARATION.
;;; This function is exported.

(defun translator-symbol-macroexpand-1 (symbol &optional env)
  (multiple-value-bind (usage boundp decls)
      (translator-variable-information symbol env)
    (if (not (eq usage :symbol-macro))
	(values symbol nil)
	(let ((expansion (call-macro-function boundp symbol env))
	      (type (assoc 'type decls)))
	  (if (and (consp type)
		   (not (eq (setf type (cdr type)) T)))
	      (values `(the ,type ,expansion) t)
	      (values expansion t))))))


;;; This should probably coerce *macroexpand-hook* to be a function, but
;;; the host Lisp might not support coercion to functions yet because of
;;; it being a new feature of ANSI CL....
;;; This function is exported (it is also used by the codewalker).

(defun call-macro-function (function form env)
  (funcall *macroexpand-hook* function form env))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Support for compiler macros
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; For compiler macros, we definitely do not want to pick up host expanders.
;;; The host might provide compiler-macro definitions for standard functions
;;; whose expansions are specific to that implementation.  In the case of
;;; ordinary macros, we've been careful to define our own handling of
;;; built-in macros that shadows the host's definitions, but we have not
;;; defined our own compiler macros for every one of the built-in functions
;;; in the language.

;;; This is exported.

(defun translator-compiler-macro-function (name &optional env)
  (let ((entry (environment-entry name env)))
    (when entry
      (let ((expander (defined-as-compiler-macro entry)))
	(when expander
	  (multiple-value-bind (usage boundp info)
	      (translator-function-information entry env)
	    (declare (ignore usage info))
	    (when (not boundp) expander)))))))

(defun set-translator-compiler-macro-function (value name &optional env)
  (if value
      (setf (defined-as-compiler-macro name env) value)
      (progn
	(translator-environment-remprop name env 'defined-as-compiler-macro)
	value)))

(define-setf-method translator-compiler-macro-function (name &optional env)
  (make-translator-macro-function-setf-method
   name env
   'translator-compiler-macro-function
   'set-translator-compiler-macro-function))


;;; This is exported.

(defun translator-compiler-macroexpand-1 (form &optional env)
  (if (not (consp form))
      (values form nil)
      (let ((name (car form)))
	(if (or (not (symbolp name))
		(function-notinline-p name env))
	    (values form nil)
	    (let ((expander (translator-compiler-macro-function name env)))
	      (if (or expander
		      ;; If no expander on name, but name is FUNCALL, then if
		      ;; function argument is of the form (FUNCTION name), use
		      ;; name to look up the compiler macro definition.
		      (and (eq name 'funcall)
			   (setf name (cadr form))
			   (consp name)
			   (eq (car name) 'function)
			   (valid-function-name-p (setf name (cadr name)))
			   (not (function-notinline-p name env))
			   (setf expander
				 (translator-compiler-macro-function name
								     env))))
		  (let ((expansion (call-macro-function expander form env)))
		    (values expansion (not (eq expansion form))))
		  (values form nil)))))))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Higher level accessors
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; VARIABLE-INFORMATION-VALUE
;;;
;;; Returns the value associated with Key in the variable info for Name in Env.
;;; Returns a second value which is true iff a value was actually present.
;;; This is exported.

(defun variable-information-value (name key &optional environment)
  (multiple-value-bind (usage boundp info)
      (translator-variable-information name environment)
    (declare (ignore usage boundp))
    (let ((entry (assoc key info)))
      (values (cdr entry) (consp entry)))))

;;; FUNCTION-INFORMATION-VALUE
;;;
;;; Returns the value associated with Key in the function info for Name in Env.
;;; Returns a second value which is true iff a value was actually present.
;;; This is exported.

(defun function-information-value (name key &optional environment)
  (multiple-value-bind (usage boundp info)
      (translator-function-information name environment)
    (declare (ignore usage boundp))
    (let ((entry (assoc key info)))
      (values (cdr entry) (consp entry)))))


;;; VARIABLE-TYPE
;;;
;;; Returns the type associated with a variable binding in the specified
;;; environment, or T if no explicit type information is available.
;;; This is exported.

(defun variable-type (variable &optional environment)
  (multiple-value-bind (type therep)
      (variable-information-value variable 'type environment)
    (if (not therep) 't type)))



;;; Is the "form" a constant?
;;; This is exported.

(defun translator-constantp (form &optional env)
  (cond ((symbolp form)
	 (eq (translator-variable-information form env) :constant))
	((consp form)
	 (or (eq (car form) 'quote)
	     (and (eq (car form) 'the)
		  (translator-constantp (caddr form) env))))
	(t t)))

;;; Try to get the value of a constant.
;;; This is exported.

(defun translator-constant-value (form &optional env)
  (cond ((not (symbolp form))
	 (cond ((atom form) (values form t t))
	       ((eq (car form) 'quote) (values (cadr form) t t))
	       ((eq (car form) 'the)
		(translator-constant-value (caddr form) env))
	       (t (values nil nil nil))))
	((or (null form) (eql form 'T) (keywordp form))
	 (values form t t))
	(t
	 (let ((info (defined-as-variable form env)))
	   (if (and info (variable-descriptor-constant-p info))
	       (if (variable-descriptor-value-p info)
		   (values (variable-descriptor-value info) t t)
		   (values nil nil t))
	       (values nil nil nil))))))


;;;    High level accessors on function declarations

;;; FUNCTION-NOTINLINE-P
;;;
;;; Returns true if the named function is declaraed or proclaimed to be
;;; NOTINLINE in the specified environment.
;;; This is exported.

(defun function-notinline-p (function-name &optional environment)
  (eq (function-information-value function-name 'inline environment)
      'notinline))


;;;    High level accessors on random declarations

;;; SAFE-CODE-P
;;;
;;; Returns true if the value of the SAFETY optimization is declared or
;;; proclaimed to be at a maximum (the value of the SAFETY optimization quality
;;; is 3) in the specified environment.
;;; This is exported.

(defun safety-level (environment)
  (cadr (assoc 'safety
	       (translator-declaration-information 'optimize environment))))

(defun safe-code-p (&optional environment)
  (eql 3 (safety-level environment)))

(defvar *prepare-stream* nil)

(defun translator-enclose (lambda env)
  (eval (get-bindings-from-environment `(function ,lambda) env)))

(defun eval-in-env (form env)
  (let ((form (get-bindings-from-environment form env)))
    (translator-eval form)
    (write-prepare-form form)
    nil))

(define-translator-parameter *compile-time-compile-defuns-only-p* t)    
(define-translator-parameter *compile-time-forms-compile-p* t)
(define-translator-parameter *compile-time-skip-defuns-after-prepare-file-p* t)
(define-translator-parameter *compile-time-compile-defun-lazy-p* t)

(defun translator-eval (form)
  (if (if (eq *compile-time-forms-compile-p* :default)
	  #+lucid t #-lucid nil
	  *compile-time-forms-compile-p*)
      (if *compile-time-compile-defuns-only-p*
	  (translator-eval-internal
	   form 
	   (and *compile-time-skip-defuns-after-prepare-file-p*
		(not *compile-time-only*)))
	  (funcall
	   (let (#+lucid (lucid:*use-sfc* t))
	     (compile nil `(lambda () ,form)))))
      (eval form)))

(defun translator-eval-internal (form maybe-skip-defuns-p)
  (if (atom form)
      (eval form)
      (case (car form)
	((progn)
	 (dolist (form (cdr form))
	   (translator-eval-internal form maybe-skip-defuns-p)))
	((eval-when)
	 (when (dolist (time (cadr form) nil)
		 (when (or (eq time 'eval) (eq time ':execute))
		   (return t)))
	   (dolist (form (cddr form))
	     (translator-eval-internal form maybe-skip-defuns-p))))
	((defun)
	 (if (symbolp (cadr form))
	     (unless (and maybe-skip-defuns-p
			  (symbol-package (cadr form)))
	       (if *compile-time-compile-defun-lazy-p*		    
		   (lazy-compile-defun form)
		   (compile-defun form)))
	     (eval form)))
	(t
	 (multiple-value-bind (form expanded-p)
	     (macroexpand-1 form)
	   (if expanded-p
	       (translator-eval-internal form maybe-skip-defuns-p)
	       (eval form)))))))

(defun compile-defun (form)
  (eval form)
  (let (#+lucid (lucid:*use-sfc* t))
    (compile (cadr form))))

(defun lazy-compile-defun (form &aux (package *package*))
  (setf (symbol-function (cadr form))
	#'(lambda (&rest args)
	    ;; Make a tail-recursive call to avoid modifying
	    ;; the function on the stack during the call to compile.
	    (lazy-compile-defun-internal form args package))))

(defun lazy-compile-defun-internal (form args package)
  (let ((*package* package))
    (compile-defun form))
  (apply (symbol-function (cadr form)) args))

(defun write-prepare-form (form)
  (when *prepare-stream*
    (let ((*print-circle* t)
	  (*print-level* nil)
	  (*print-length* nil))
      (pprint form *prepare-stream*)))
  nil)

(defun get-bindings-from-environment (form env)
  (get-bindings-from-environment-internal
   form env (translator-environment-lexical-part env)))

(defun get-bindings-from-environment-internal (form env lenv)
  (if (null lenv)
      form
      (get-bindings-from-environment-internal
       (let ((contour (car lenv)))
	 (case (type-of contour)
	   (variable-information-contour
	    (let ((name (variable-information-contour-name contour))
		  (locally-bound-p
		   (variable-information-contour-locally-bound-p contour)))
	      (case (variable-information-contour-usage contour)
		(:symbol-macro
		 (let ((expansion (funcall locally-bound-p nil nil)))
		   (multiple-value-bind (bindings forms)
		       (if (and (consp form)
				(eq (car form) 'symbol-macrolet))
			   (values (cadr form) (cddr form))
			   (values nil (list form)))
		     `(#+lucid lcl:symbol-macrolet #-lucid symbol-macrolet
		        ((,name ,expansion) ,@bindings)
		       ,@forms))))
		(:special
		 `(locally
		   (declare (special ,name))
		   ,@(if (and (consp form)
			      (eq (car form) 'locally))
			 (cdr form)
			 (list form))))
		(t
		 form))))
	   (function-information-contour
	    (let ((name (function-information-contour-name contour))
		  (locally-bound-p
		   (function-information-contour-locally-bound-p contour)))
	      (case (function-information-contour-usage contour)
		(:macro
		 (let ((expansion (cdr locally-bound-p)))
		   (multiple-value-bind (bindings forms)
		       (if (and (consp form)
				(eq (car form) 'macrolet))
			   (values (cadr form) (cddr form))
			   (values nil (list form)))
		     `(macrolet ((,name ,@expansion)
				 ,@bindings)
		       ,@forms))))
		(t
		 form))))
	   (t
	    form)))
       env (cdr lenv))))



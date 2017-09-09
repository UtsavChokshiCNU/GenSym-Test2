;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Accessing method arguments from method frames.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/method-arguments.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:09 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Method arguments
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; This declaration is used to pass the names of the method arguments downward
;;; for use by walker functions and macro expanders that need to include
;;; references to them.

;;; Spec is (method-arguments #:effective-method #:method-index #:frame #:argq)
(define-translator-declaration method-arguments (spec env)
  (declare (ignore env))
  (values () () () (list spec)))

(defun method-arguments (env)
  (or (translator-declaration-information 'method-arguments env)
      (error "Not in a method body context.")))

;;; Define declarations for method argument variables.

(define-translator-type effective-method () 'trun:effective-method)
(define-translator-type method-index () 'fixnum)
(define-translator-type method-frame-type () 'simple-vector)
(define-translator-type method-quantity-type () 'fixnum)

(define-translator-declaration method-argument-frame (decl-spec env)
  (declare (ignore env))
  (destructuring-bind (var) (cdr decl-spec)
    (declare (ignore var))
    ;; There isn't very much that can be done with this declaration any more.
    ;; At one time there was a nonrelocatable declaration here, but that is
    ;; wrong since the frame might have been heap allocated (it might be the
    ;; result of a call to copy-method-frame).  There also used to be a
    ;; dynamic-extent declaration, but that isn't very useful without a
    ;; constructor being visible.
    (values nil nil nil nil)))

;;; Format of entries is (name type)
(defparameter *method-arguments*
  '(("Method" effective-method)
    ("Index" method-index)
    ("Frame" method-frame-type)
    ("Argq" method-quantity-type)))

(defmacro method-arguments-effective-method  (args) `(first ,args))
(defmacro method-arguments-method-index     (args) `(second ,args))
(defmacro method-arguments-frame            (args) `(third ,args))
(defmacro method-arguments-argq             (args) `(fourth ,args))

(defun make-method-arguments-internal ()
  (let ((vars (mapcar #'(lambda (pair) (make-variable (car pair)))
		      *method-arguments*)))
    (values vars
	    `((ignorable ,@vars)
	      ,@(mapcar #'(lambda (var entry)
			    `(type ,(second entry) ,var))
			vars
			*method-arguments*)))))

(defun make-method-arguments ()
  (multiple-value-bind (vars decls)
      (make-method-arguments-internal)
    (let ((frame (method-arguments-frame vars)))
      (values vars
	      `((method-arguments ,@vars)
		(method-argument-frame ,frame)
		,@decls)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Accessing arguments to a method
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; METHOD-ARGUMENT frame index
;;;
;;; Return the value in the index'ed position in the method argument frame
;;; specified by frame.
;;;
;;;  frame	Method argument frame.
;;;
;;;  index	Position of the argument (an unboxed fixnum).
;;;
;;; The code which generates calls to this is responsible for ensuring that the
;;; arguments are valid.  This function does not need to check the validity of
;;; the arguments it receives.

(define-translator-macro method-argument (index &environment env)
  (let ((walked-index (walk:walk-form index :environment env))
	(frame (method-arguments-frame (method-arguments env))))
    (if (typep walked-index '(integer 0))
	`(tclos-run:%method-argument ,frame ,walked-index)
	`(tclos-run:%method-argument\(boxed\) ,frame ,walked-index))))

;;; METHOD-OPTIONAL-ARGUMENT-P argq index
;;;
;;; Predicate which returns true if the index'ed argument was supplied to the
;;; method, false if not.  Index is relative to the method argument frame,
;;; while argq is the actual number of arguments.
;;;
;;;  argq	Number of arguments passed to the method.
;;;
;;;  index	Position of the argument (an unboxed fixnum).
;;;
;;; The code which generates calls to this is responsible for ensuring that the
;;; arguments are valid.  This function does not need to check the validity of
;;; the arguments it receives.

(define-translator-macro method-optional-argument-p (index &environment env)
  (let ((walked-index (walk:walk-form index :environment env))
	(argq (method-arguments-argq (method-arguments env))))
    (list (if (typep walked-index '(integer 0))
	      'tclos-run:%method-optional-argument-p
	      'tclos-run:%method-optional-argument-p\(boxed\))
	  argq
	  walked-index)))

;;; METHOD-REST-LIST frame
;;;
;;; Return the value of the field in frame which holds the &rest list.  If the
;;; list has not yet been computed, collect and record it in the frame before
;;; returning it.
;;;
;;;  method	Effective-method
;;;
;;;  frame	Method argument frame.
;;;
;;;  argq	Number of arguments in the frame.

(define-translator-macro method-rest-list (&environment env)
  (let ((method-args (method-arguments env)))
    `(tclos-run:%method-rest-list
          ,(method-arguments-effective-method method-args)
          ,(method-arguments-frame method-args)
          ,(method-arguments-argq method-args))))

(timpl::define-local-temp-emitter tclos-run:%method-rest-list (key)
  (declare (ignore key))
  (timpl::emit-newline-indent)
  (timpl::emit-string "Declare_method_rest;"))

;;; METHOD-KEY-VALUE frame key-table key-index
;;;
;;; Return the value of a keyword from the method argument frame.  The
;;; key-index is a compile-time constant index into the key-table, which maps
;;; keyword positions in the current method to the canonical positions in the
;;; argument frame for the effective method.
;;;
;;;  frame	Method argument frame.
;;;
;;;  key-table	Permutation vector for the keyword arguments.  It maps
;;;		translation-time constant indices for the keywords used by the
;;;		method into the canonicalized offsets in the method argument
;;;		frame.  It is a Lisp SIMPLE-VECTOR.
;;;
;;;  key-index	Index into the key-table.  It is an unboxed fixnum.
;;;
;;; The code which generates calls to this is responsible for ensuring that the
;;; arguments are valid.  This function does not need to check the validity of
;;; the arguments it receives.
;;;
;;; The handling of keywords by methods is special.  In addition to collecting
;;; the actual arguments supplied in the call in the &REST list of the frame
;;; (see METHOD-REST-LIST), the keywords are parsed and the values are placed
;;; in the frame in an order which is determined by the effective method.  The
;;; idea is that each effective method specifies a canonical index for each
;;; keyword mentioned by any method in the effective method, and associates a
;;; permutation vector with each method which maps from the method's index for
;;; the keyword to the canonical index.  This results in keyword argument
;;; processing by methods not requiring any searching, instead being found
;;; through a couple of array accesses.

(define-translator-macro method-key-value (key-table index &environment env)
  (let ((method-args (method-arguments env)))
    `(tclos-run:%method-key-value ,(method-arguments-frame method-args)
				  ,key-table
				  ,index)))

;;; METHOD-COMBINATION-KEY-VALUE key-table key key-index frame
;;;
;;; Return the value of a keyword within a method combination function.  The
;;; key index is a compile-time constant index into the key-table, as described
;;; for method-key-value.
;;;
;;;  key-table	Either a keyword permutation vector (as specified for
;;;		method-key-value or a list (which may be Nil).
;;;
;;;  key	The keyword specifier to match.
;;;
;;;  key-index	Index into the key-table.  It is an unboxed fixnum.
;;;
;;;  frame	Method argument frame.
;;;
;;; The code which generates calls to this is responsible to ensuring that the
;;; arguments are valid.  This function does not need to check the validity of
;;; the arguments it receives.
;;;
;;; The LOCAL-METHOD macro cannot determine whether the keywords mentioned in
;;; the lambda-list will actually be valid keywords (or even if keywords will
;;; be permitted) for effective-methods it will be used by.  Instead, calls to
;;; this function are generated to perform the keyword lookup.  If the
;;; specified key is a valid argument to the effective method, then the
;;; key-table argument will be a permutation vector (as used by
;;; METHOD-KEY-VALUE).  Otherwise, it will be the &REST list from the call,
;;; and a search for the key is performed.

(define-translator-macro method-combination-key-value
        (key-table key key-index &environment env)
  (let ((method-args (method-arguments env)))
    `(tclos-run:%method-combination-key-value
        ,key-table
	,key
	,key-index
	,(method-arguments-frame method-args))))

;;; METHOD-KEY-P value
;;;
;;;  value	The value of the keyword parameter obtained via a call to
;;;		Method-key-value.
;;;
;;; This function only returns an unboxed boolean.  It is never used in a
;;; context where a boxed boolean value would be needed.

(define-translator-macro method-key-p (value)
  `(tclos-run:%method-key-p ,value))

;;; COPY-METHOD-FRAME frame
;;;
;;; This function is used to get a method argument frame that can be passed
;;; upward.  It is needed because frames normally have dynamic extent.
;;;
;;; This function first examines the COPY entry in the argument frame, returing
;;; the value found there if it is non-Nil.  If it is Nil, then a copy of the
;;; frame is allocated in the heap.  The COPY entry of both the frame and the
;;; copy are set to the copy, and the copy is returned.  Note that making
;;; the copy point to itself avoids the possibility of long chains of copies.
;;;
;;; Note that the above description depends on the implementation of frames
;;; being as vectors.  If they were raw stack pointers then things would be
;;; significantly more complicated.

(define-translator-macro copy-method-frame (&environment env)
  `(tclos-run:%copy-method-frame
        ,(method-arguments-frame (method-arguments env))))

;;; METHOD-ARGUMENT-LIST effective-method frame argq
;;;
;;; This function first examines the LIST entry in the argument frame
;;; specified by frame, returning the value there if it is a cons.  If it is
;;; not a cons, then the effective-method and argq are used to cons up a list
;;; of all of the arguments in the frame argument frame, with the resulting
;;; list stored into the LIST entry in the frame and returned as the result of
;;; the function.
;;;
;;; The code which generates calls to this is responsible for ensuring that the
;;; arguments are valid.  This function does not need to check the validity of
;;; the arguments it receives.

(define-translator-macro method-argument-list (&environment env)
  (let ((method-args (method-arguments env)))
    `(tclos-run:%method-argument-list
        ,(method-arguments-effective-method method-args)
	,(method-arguments-frame method-args)
	,(method-arguments-argq method-args))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Helper functions for constructing initforms and bindings
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; MAKE-METHOD-KEY-BINDINGS
;;;
;;; This function is used to construct binding forms for keyword parameters in
;;; methods.  The arguments are as follows:
;;;
;;;  key-parm	The keyword parameter specifier for which binding forms are
;;;		to be constructed.  This argument is a list of the form
;;;		((key variable) initform [ suppliedp-variable ]).
;;;
;;;  value-var	This is a temporary variable.  It is assumed that the variable
;;;		will have already been bound before the binding forms returned
;;;		by this function are executed, and that the new binding forms
;;;		may freely modify the value of this variable. 
;;;
;;;  value-form	This must be a form that will return the value of the keyword
;;;		for the supplied parameter, or return the special unsupplied
;;;		cookie if the keyword is unsupplied.

;;; This function returns two values.  The first value is a binding form for
;;; the keyword variable, in the form (variable initform).  The second value is
;;; a binding form for the suppliedp-variable, in the form (variable initform).
;;; If no suppliedp variable is present in key-parm, then the second value is
;;; Nil.

(defun make-method-key-bindings (key-parm value-var value-form)
  (let ((test `(method-key-p (setf ,value-var ,value-form))))
    (destructuring-bind ((key var) init &optional (svar nil svar-p))
	                key-parm
      (declare (ignore key))
      (if svar-p
	  (values `(,var (if ,test
			     (prog1 ,value-var (setf ,value-var t))
			     (progn (setf ,value-var nil) ,init)))
		  `(,svar ,value-var))
	  (values `(,var (if ,test
			     ,value-var
			     ,init))
		  ())))))

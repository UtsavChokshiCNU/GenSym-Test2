;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; target-form-types.lisp 
;;;
;;; Copyright (c) 1993, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/target-form-types.lisp,v $"
 "$Revision: 1.8 $"
 "$Date: 2007/07/13 18:16:53 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Helper functions for expression and statement handlers
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defmacro funcall1 (function &rest args)
  (if (and (consp function)
	   (eq (car function) 'function))
      `(,(cadr function) ,@args)
      `(funcall ,function ,@args)))

(defmacro every-subexpression (function subform-function)
  `#'(lambda (expression)
       (every ,function (funcall1 ,subform-function expression))))

(defmacro some-subexpression (function subform-function)
  `#'(lambda (expression)
       (some ,function (funcall1 ,subform-function expression))))

(defmacro one-subexpression (function subform-function)
  `#'(lambda (expression)
       (funcall ,function (funcall1 ,subform-function expression))))


;;; The :state-using and :state-changing slots of a function descriptor
;;; might be a list of lambda parameters that name functional arguments.
;;; For now, treat that like an ordinary value of true, although
;;; obviously we could be smarter about matching up the actual arguments
;;; to the lambda parameters.

(defun state-changing-call-p (expression)
  (or (and (function-descriptor-state-changing
	    (defined-as-function (cadr expression)))
	   (target-info-state-changing (car expression)))
      (some #'state-changing-expression-p (cddr expression))))

(defun state-using-call-p (expression)
  (or (and (function-descriptor-state-using
	    (defined-as-function (cadr expression)))
	   (target-info-state-using (car expression)))
      (some #'state-using-expression-p (cddr expression))))


;;; The :nonconsing slot of a function descriptor might also be a list
;;; of lambda parameters that name functional arguments.  For now, treat
;;; that like :nonconsing NIL, although obviously we could be smarter
;;; about matching up the actual arguments to the lambda parameters.

(defun nonrelocating-call-internal (expression)
  (or (target-info-nonrelocating (car expression))
      (let ((name
	      (case (target-form-type expression)
		(box-value (boxer (cadr expression)))
		(unbox-value (unboxer (cadr expression)))
		(cast :cast)
		(t (cadr expression)))))
	(case name
	  ((:cast :nonstandard :foreign-pointer-address 
	    :unnecessary :unspecified)
	   t)
	  (:make-foreign-pointer nil)
	  (t
	   (not (relocating-function-p name)))))))

(defun nonrelocating-call-expression-p (expression)
  (and (nonrelocating-call-internal expression)
       (every #'nonrelocating-expression-p
	      (cddr expression))))

;;; Note that unlike the functions above, which consider a call as
;;; an expression (including all of its subexpressions),
;;; this function considers a call as a flow-graph node, so it is concerned
;;; only with the call itself, and not with the argument expressions.

(defun relocating-call-statement-p (s)
  (not (nonrelocating-call-internal s)))

(defun state-changing-c-call-p (expression)
  (or (and (target-info-state-changing (car expression))
	   (let ((fne (cadr expression)))
	     (or (not (eq 'function-name (target-form-type fne)))
		 (let ((fn (cadr fne)))
		   (or (stringp fn)
		       (if (or (symbolp fn) (consp fn))
			   (function-descriptor-state-changing
			    (defined-as-function fn))
			   t))))))
      (some #'state-changing-expression-p (cddr expression))))

(defun state-using-c-call-p (expression)
  (or (and (target-info-state-using (car expression))
	   (let ((fne (cadr expression)))
	     (or (not (eq 'function-name (target-form-type fne)))
		 (let ((fn (cadr fne)))
		   (or (stringp fn)
		       (if (or (symbolp fn) (consp fn))
			   (function-descriptor-state-using
			    (defined-as-function fn))
			   t))))))
      (some #'state-using-expression-p (cddr expression))))

(defun nonrelocating-c-call-expression-p (expression)
  (and (or (target-info-nonrelocating (car expression))
	   (let ((fne (cadr expression)))
	     (and (eq 'function-name (target-form-type fne))
		  (let ((fn (cadr fne)))
		    (and (not (stringp fn))
			 (if (or (symbolp fn) (consp fn))
			     (not (relocating-function-p fn))
			     (function-record-nonrelocating-p fn)))))))
       (every #'nonrelocating-expression-p (cddr expression))))

;;; With lexical bindings does very different things depending on
;;; whether any of the bound varibles is closed.

(defun with-lexical-binding-relocates-p (s)
  (some #'variable-record-closed-p (cadr s)))

(defun lexical-bindings-state-changing-p (s)
  (some #'variable-record-closed-p (cadr s)))

(define-forward-variable-reference *environment*)

(defun reset-read-once-setqs-initializer (form)
  (when *environment*
    (reset-read-once-setqs *environment*))
  form)

(defun maybe-reset-read-once-setqs-initializer (form)
  (when (and *environment*
	     (target-info-state-changing (car form))
	     (function-descriptor-state-changing
	      (defined-as-function (cadr form))))
    (reset-read-once-setqs *environment*))
  form)


#|| ; not currently needed.
;;; Would it be OK to replace this expression by an expression that GC'ed,
;;; or would the result be gc-unsafe code?
;;; Note that for efficiency, this does not check whether the enclosing
;;; function is declared nonrelocating; instead, the calling function
;;; is responsible for checking this, so that it need only be checked once.
(defun gc-permitted-location (expression)
  (or (statement-context-p expression)
      (let ((encloser (enclosing-statement expression)))
	(and (funcall (statement-handler-gc-ok-function (handler encloser))
		      encloser
		      expression)
	     (gc-permitted-location encloser)))))
||#

;;; Simplest thing is to prohibit any consing by an argument to
;;; a function with more than one argument. The more sophisticated
;;; thing to do here is to allow one argument to cons if none of the others
;;; are of type object.
(defun call-gc-ok-function (call arg)
  (every #'(lambda (other-arg)
	     (or (eq other-arg arg) (not (relocatable-p other-arg))))
	 (cddr call)))

;;; This should return nil only if it's argument (a target-language expression)
;;; is of type Object, or contains substructure of type Object, which
;;; may be of nonimmediate type. For now we'll just be conservative.
(defun relocatable-p (expression)
  (declare (ignore expression))
  nil)

;;; Consing by the rhs is only ok if the lhs is simple.
;;; consing by the lhs is only ok if the rhs is simple.
(defun setq-gc-ok-function (assignment arg)
  (let* ((lhs (second assignment))
	 (rhs (third assignment))
	 (type (target-form-type (if (eq arg lhs) rhs lhs))))
    (or (eq type 'local-variable) (eq type 'special-variable))))


;This callback will get called when we are about to
;claim that the function does not need values.
;It returns t if it does not need values.
(defvar does-not-need-values-callback nil)

(defun needs-values-call-p (expression)
  (or (not (function-descriptor-sets-values-count-p
	     (defined-as-function (cadr expression))))
      (and does-not-need-values-callback
	   (not (funcall does-not-need-values-callback
			 (environment-entry-name
			   (environment-entry (cadr expression)))
			 (let ((names (tutil::translator-environment-function-names
					*environment*)))
			   (if (null (cdr names))
			       (car names)
			       names)))))))

(defun state-using-local-variable-p (expression)
  (not (variable-record-unwritten-p (cadr expression))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Expression handler definitions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-expression accessor-call
  :needs-values #'trun:constantly-true
  :state-changing (some-subexpression #'state-changing-expression-p #'cddr)
  :state-using #'trun:constantly-true
  :nonrelocating (every-subexpression #'nonrelocating-expression-p #'cddr)
  :nonrelocatable #'trun:constantly-false
  :values-changing (some-subexpression #'values-changing-expression-p #'cddr)
  )

(define-expression and-expression
  :needs-values #'trun:constantly-true    ; never appears in :values context
  :state-changing (some-subexpression #'state-changing-expression-p #'cdr)
  :state-using (some-subexpression #'state-using-expression-p #'cdr)
  :nonrelocating (every-subexpression #'nonrelocating-expression-p #'cdr)
  :nonrelocatable #'trun:constantly-true  ; value is unboxed C int
  :values-changing (some-subexpression #'values-changing-expression-p #'cdr)
  )

(define-expression box-value
  :needs-values #'trun:constantly-true
  :state-changing (one-subexpression #'state-changing-expression-p #'caddr)
  :state-using (one-subexpression #'state-using-expression-p #'caddr)
  :nonrelocating #'nonrelocating-call-expression-p
  :nonrelocatable
  #'(lambda (expression)
      (multiple-value-bind (foreign-type non-relocatable)
	  (lisp-type->foreign-type (lisp-type (cadr expression)))
	(declare (ignore foreign-type))
	non-relocatable))
  :values-changing (one-subexpression #'values-changing-expression-p #'caddr)
  )

(define-expression c-constant
  :needs-values #'trun:constantly-true    ; never appears in :values context
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-true  ; value is untagged
  :values-changing #'trun:constantly-false
  )

(define-expression call
  :needs-values #'needs-values-call-p
  :state-changing #'state-changing-call-p
  :state-using #'state-using-call-p
  :nonrelocating #'nonrelocating-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true
  )

(define-expression call-generic
  :needs-values #'needs-values-call-p
  :state-changing #'state-changing-call-p
  :state-using #'state-using-call-p
  :nonrelocating #'trun:constantly-false    ; method lookup might cons
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true
  )

(define-expression comma-operator
  :needs-values
  #'(lambda (expression)
      (needs-explicit-values (car (last expression))))
  :state-changing (some-subexpression #'state-changing-expression-p #'cdr)
  :state-using (some-subexpression #'state-using-expression-p #'cdr)
  :nonrelocating (every-subexpression #'nonrelocating-expression-p #'cdr)
  :nonrelocatable
  #'(lambda (expression)
      (nonrelocatable-expression-p (car (last expression))))
  :values-changing (some-subexpression #'values-changing-expression-p #'cdr)
  )

(define-expression conditional-operator
  :needs-values #'trun:constantly-true      ; never appears in :values context
  :state-changing (some-subexpression #'state-changing-expression-p #'cdr)
  :state-using (some-subexpression #'state-using-expression-p #'cdr)
  :nonrelocating (every-subexpression #'nonrelocating-expression-p #'cdr)
  :nonrelocatable (every-subexpression #'nonrelocatable-expression-p #'cddr)
  :values-changing (some-subexpression #'values-changing-expression-p #'cddr)
  )

(define-expression constant
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-true  ; value is statically allocated
  :values-changing #'trun:constantly-false
  )

(define-expression constant-label
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-false ; value might not be static
  :values-changing #'trun:constantly-false
  )

(define-expression first-multiple-value
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-true
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-false
  )

(define-expression foreign-call
  :needs-values #'needs-values-call-p
  :state-changing #'state-changing-call-p
  :state-using #'state-using-call-p
  :nonrelocating #'nonrelocating-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true
  )

(define-expression function-object
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'(lambda (s)
		     (let ((c (function-record-classification (cadr s))))
		       (or (eq c ':global) (eq c ':bound-global)
			   (eq c ':global-dllexport))))
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true
  )

(define-expression global-function
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-true    ; value statically allocated
  :values-changing #'trun:constantly-false
  )

(define-expression global-foreign-function
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-true    ; value statically allocated
  :values-changing #'trun:constantly-false
  )

(define-expression initial-symbol
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-true  ; value is statically allocated
  :values-changing #'trun:constantly-false
  )

(define-expression initial-package
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-true  ; value is statically allocated
  :values-changing #'trun:constantly-false
  )

(define-expression load-time-value
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-false ; value might not be static
  :values-changing #'trun:constantly-false
  )

(define-expression local-variable
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'state-using-local-variable-p
  :nonrelocating #'trun:constantly-true
  :nonrelocatable
  #'(lambda (expression)
      (and (not (variable-record-closed-p (cadr expression)))
	   (variable-record-nonrelocatable-type (cadr expression))))
  :values-changing #'trun:constantly-false
  )

(define-expression macro-call
  :needs-values #'trun:constantly-true ; #'needs-values-call-p
  :state-changing #'state-changing-call-p
  :state-using #'state-using-call-p
  :nonrelocating #'nonrelocating-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true ; fix this
  )

(define-expression operator-call 
  :needs-values #'trun:constantly-true
  :state-changing #'state-changing-call-p
  :state-using #'state-using-call-p
  :nonrelocating #'nonrelocating-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing (some-subexpression #'values-changing-expression-p #'cddr)
  )

(define-expression not-operator
  :needs-values #'trun:constantly-true
  :state-changing (one-subexpression #'state-changing-expression-p #'cadr)
  :state-using (one-subexpression #'state-using-expression-p #'cadr)
  :nonrelocating (one-subexpression #'nonrelocating-expression-p #'cadr)
  :nonrelocatable #'trun:constantly-true    ; value is unboxed C int
  :values-changing (one-subexpression #'values-changing-expression-p #'cadr)
  )

(define-expression nth-value
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-true
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-false
  )

(define-expression or-expression
  :needs-values #'trun:constantly-true    ; never appears in :values context
  :state-changing (some-subexpression #'state-changing-expression-p #'cdr)
  :state-using (some-subexpression #'state-using-expression-p #'cdr)
  :nonrelocating (every-subexpression #'nonrelocating-expression-p #'cdr)
  :nonrelocatable #'trun:constantly-true  ; value is unboxed C int
  :values-changing (some-subexpression #'values-changing-expression-p #'cdr)
  )

(define-expression restore-values
  :needs-values #'trun:constantly-false
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true    ; sets values count
  )

(define-expression setq
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-true
  :state-using (some-subexpression #'state-using-expression-p #'cdr)
  :nonrelocating (every-subexpression #'nonrelocating-expression-p #'cdr)
  :nonrelocatable (every-subexpression #'nonrelocatable-expression-p #'cdr)
  :values-changing (some-subexpression #'values-changing-expression-p #'cdr)
  )

(define-expression special-variable
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-true
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-false
  )

(define-expression symbolic-constant
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-true    ; value static or immediate
  :values-changing #'trun:constantly-false
  )

(define-expression unbox-value
  :needs-values #'trun:constantly-true    ; never appears in :values context
  :state-changing (one-subexpression #'state-changing-expression-p #'caddr)
  :state-using (one-subexpression #'state-using-expression-p #'caddr)
  :nonrelocating #'nonrelocating-call-expression-p
  :nonrelocatable
  #'(lambda (exp)  ; other c-types are immediate
      (let ((ftype (translator-foreign-type (cadr exp))))
	(not (or (eq ftype (translator-foreign-type :object))
		 (eq ftype (translator-foreign-type :string))))))
  :values-changing (one-subexpression #'values-changing-expression-p #'caddr)
  )

(define-expression unbound-special-p
  :needs-values #'trun:constantly-true
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-true
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-false
  )

(define-expression values
  :needs-values #'trun:constantly-false
  :state-changing #'trun:constantly-true
  :state-using (some-subexpression #'state-using-expression-p #'cdr)
  :nonrelocating (every-subexpression #'nonrelocating-expression-p #'cdr)
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true
  )

(define-expression variadic-call
  :needs-values #'needs-values-call-p
  :state-changing #'state-changing-call-p
  :state-using #'state-using-call-p
  :nonrelocating #'nonrelocating-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true
  )

(define-expression variadic-call-generic
  :needs-values #'needs-values-call-p
  :state-changing #'state-changing-call-p
  :state-using #'state-using-call-p
  :nonrelocating #'trun:constantly-false    ; method lookup might cons
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true
  )

(define-expression cast
  :needs-values #'trun:constantly-true    ; never appears in :values context
  :state-changing (one-subexpression #'state-changing-expression-p #'caddr)
  :state-using (one-subexpression #'state-using-expression-p #'caddr)
  :nonrelocating #'nonrelocating-call-expression-p
  :nonrelocatable
  #'(lambda (exp)  ; other c-types are immediate
      (eq (translator-foreign-type (cadr exp))
	  (translator-foreign-type :object)))
  :values-changing (one-subexpression #'values-changing-expression-p #'caddr)
  )


(define-expression c-call
  :needs-values #'trun:constantly-true
  :state-changing #'state-changing-c-call-p
  :state-using #'state-using-c-call-p
  :nonrelocating #'nonrelocating-c-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true ; fix this
  )

(define-expression values-c-call
  :needs-values #'trun:constantly-true
  :state-changing #'state-changing-c-call-p
  :state-using #'state-using-c-call-p
  :nonrelocating #'nonrelocating-c-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true ; fix this
  )

(define-expression variadic-values-c-call
  :needs-values #'trun:constantly-true
  :state-changing #'state-changing-c-call-p
  :state-using #'state-using-c-call-p
  :nonrelocating #'nonrelocating-c-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true ; fix this
  )

(define-expression variadic-c-call
  :needs-values #'trun:constantly-true
  :state-changing #'state-changing-c-call-p
  :state-using #'state-using-c-call-p
  :nonrelocating #'nonrelocating-c-call-expression-p
  :nonrelocatable #'trun:constantly-false
  :values-changing #'trun:constantly-true ; fix this
  )

(define-expression function-name
  :needs-values #'trun:constantly-true    ; never appears in :values context
  :state-changing #'trun:constantly-false
  :state-using #'trun:constantly-false
  :nonrelocating #'trun:constantly-true
  :nonrelocatable #'trun:constantly-true  ; value is untagged
  :values-changing #'trun:constantly-false
  )

;;; Non-expression statements

(define-statement null-statement
  :flow-function #'flow-straight-thru
  :value-subforms-function #'constantly-nil
  :substatements-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement save-values
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression nil
  :l-value nil
  :initializer #'reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'trun:constantly-true
  :gc-ok-function #'trun:constantly-true
  )

(define-statement save-more-values
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression nil
  :l-value nil
  :initializer #'reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'trun:constantly-true
  :gc-ok-function #'trun:constantly-true
  )

(define-statement store-value
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression nil
  :l-value nil
  :initializer #'reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'trun:constantly-true
  :gc-ok-function #'trun:constantly-true
  )

(define-statement store-values
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression nil
  :l-value nil
  :initializer #'reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'trun:constantly-true
  :gc-ok-function #'trun:constantly-true
  )

(define-statement return-value
  :flow-function #'substatement-self-and-return
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement return-values
  :flow-function #'substatement-self-and-return
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement return-stored-values
  :flow-function #'substatement-self-and-return
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement values-assign
  :flow-function #'values-assign-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression nil
  :l-value nil
  :initializer #'reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'trun:constantly-true
  :gc-ok-function #'constantly-nil
  )

(define-statement with-lexical-bindings
  :flow-function #'self-then-substatements-flow
  :substatements-function #'cddr
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :initializer #'lexical-bindings-init
  :statement-subforms-function #'cddr
  :relocating-statement-function #'with-lexical-binding-relocates-p
  :state-changing-function #'lexical-bindings-state-changing-p
  :gc-ok-function #'trun:constantly-true
  )

;;;Since we store value cells on the plist, this may cons.
(define-statement with-special-binding
  :flow-function #'special-binding-flow
  :substatements-function #'cdddr
  :value-subforms-function #'(lambda (s) (list (fourth s)))
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddddr
  :relocating-statement-function #'trun:constantly-true
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement labeled-statement
  :flow-function #'labeled-flow
  :substatements-function #'cddr
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :initializer #'labeled-init
  :statement-subforms-function #'cddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement goto
  :flow-function #'goto-flow
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  ;; have to be careful here; this might need revision if we ever start calling
  ;; state-using on statements
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement switch
  :flow-function #'switch-flow
  :substatements-function #'cdr
  :value-subforms-function #'(lambda (s) (list (second s)))
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement compound-statement
  :flow-function #'substatements-flow
  :substatements-function #'cdr
  :value-subforms-function #'last
  :expression nil
  :l-value nil
  :statement-subforms-function #'cdr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement if-statement
  :flow-function #'if-flow
  :substatements-function #'cdr
  :value-subforms-function  #'(lambda (s) (list (second s)))
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement with-catch
  :flow-function #'catch-flow
  :substatements-function #'cddr
  :value-subforms-function #'(lambda (s) (list (third s)))
  :expression nil
  :l-value nil
  :statement-subforms-function #'cdddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement with-unwind-protect
  :flow-function #'unwind-flow
  :substatements-function #'cddr
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

;;;Since we store value cells on the plist, this may cons.
(define-statement with-progv
  :flow-function #'progv-flow
  :substatements-function #'cddr
  :value-subforms-function #'(lambda (s) (list (third s) (fourth s)))
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddddr
  :relocating-statement-function #'trun:constantly-true
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement with-area
  :flow-function #'self-then-substatements-flow
  :substatements-function #'cddddr
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement with-local-allocation
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cddddr
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement forever-statement
  :flow-function #'forever-flow
  :substatements-function #'cdr
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'cdr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement for-statement
  :flow-function #'for-flow
  :substatements-function #'cdr
  :value-subforms-function #'(lambda (s) (list (second s) (third s) (fourth s)))
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement while-statement
  :flow-function #'(lambda (s) (while-flow s t))
  :substatements-function #'cdr
  :value-subforms-function #'(lambda (s) (list (second s)))
  :expression nil
  :l-value nil
  :statement-subforms-function #'cddr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement do-while-statement
  :flow-function #'(lambda (s) (while-flow s nil))
  :substatements-function #'cdr
  :value-subforms-function #'(lambda (s) (list (third s)))
  :expression nil
  :l-value nil
  :statement-subforms-function #'(lambda (s) (list (second s)))
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement break-statement
  :flow-function #'break-flow
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement set-symbol-value-location
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :initializer #'reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'trun:constantly-true
  :state-changing-function #'trun:constantly-true
  )

(define-statement c-lines
  :flow-function #'c-lines-flow
  :substatements-function #'constantly-nil
  :initializer #'reset-read-once-setqs-initializer
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'trun:constantly-true
  :state-changing-function #'trun:constantly-true
  :gc-ok-function #'trun:constantly-true
  )

(define-statement preprocessor-conditional
  :flow-function #'preprocessor-conditional-flow
  :initializer #'reset-read-once-setqs-initializer
  :substatements-function #'(lambda (s)
			      (values (apply #'append (cddr s)) t))
  :value-subforms-function #'constantly-nil
  :replace-function #'preprocessor-conditional-substitute
  :expression nil
  :l-value nil
  :statement-subforms-function #'(lambda (s)
				   (apply #'append (cddr s)))
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement function-definition
  :flow-function #'null-flow
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement variable-definition
  :flow-function #'null-flow
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

;;; Non-lvalue Expressions

(define-statement restore-values
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement values
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression t
  :l-value nil
  :initializer #'reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'(lambda (values-exp subexp) (declare (ignore subexp))
		      (< (length values-exp) 2))
  )

(define-statement nth-value
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'constantly-nil
  )

(define-statement first-multiple-value
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement setq
  :flow-function #'setq-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'setq-gc-ok-function
  )

(define-statement call
  :flow-function #'call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'maybe-reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'call-gc-ok-function
  )

(define-statement variadic-call
  :flow-function #'call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'maybe-reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'call-gc-ok-function
  )

(define-statement call-generic
  :flow-function #'call-generic-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'maybe-reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  ; method lookup might cons
  :relocating-statement-function #'trun:constantly-true
  :gc-ok-function #'call-gc-ok-function
  )

(define-statement variadic-call-generic
  :flow-function #'call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'maybe-reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  ; method lookup might cons
  :relocating-statement-function #'trun:constantly-true
  :gc-ok-function #'call-gc-ok-function
  )

(define-statement macro-call
  :flow-function #'call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'maybe-reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'call-gc-ok-function
  )

(define-statement operator-call
  :flow-function #'call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'call-init
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'call-gc-ok-function
  )

(define-statement foreign-call
  :flow-function #'call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'maybe-reset-read-once-setqs-initializer
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'call-gc-ok-function
  )

(define-statement global-function
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement global-foreign-function
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

;;; MAKE_FUNCTION may gc: STATIC_FUNCTION doesn't, since it conses
;;; only in the static area.
(define-statement function-object
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function
  #'(lambda (s)	(eq (function-record-classification (cadr s)) :local))
  :gc-ok-function #'trun:constantly-true
  )

(define-statement symbolic-constant
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement conditional-operator
  :flow-function #'if-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement not-operator
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement comma-operator
  :flow-function #'substatements-flow
  :substatements-function #'cdr
  :value-subforms-function #'last
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement and-expression
  :flow-function #'and-or-or-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement or-expression
  :flow-function #'and-or-or-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement c-constant
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement box-value
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'trun:constantly-true
  )

(define-statement unbox-value
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'trun:constantly-true
  )

(define-statement unbound-special-p
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cdr
  :value-subforms-function #'cdr
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement constant
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement load-time-value
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement initial-symbol
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement initial-package
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

;;; Lvalues

(define-statement local-variable
  :flow-function #'simple-lvalue-flow
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement special-variable
  :flow-function #'simple-lvalue-flow
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement accessor-call
  :flow-function #'accessor-call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value t
  :initializer #'call-init
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'call-gc-ok-function
  )

(define-statement constant-label
  :flow-function #'simple-lvalue-flow
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

;;; These statements are never generated by the codewalker, only by
;;; the emitter, so the optimizer, and hence the flow-analyzer, should
;;; never see them.

(define-statement set-catch
  :flow-function #'error
  :substatements-function #'(lambda (s) (list (cadr s)))
  :value-subforms-function #'(lambda (s) (list (cadr s)))
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )


(define-statement set-unwind-protect
  :flow-function #'error
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement set-progv
  :flow-function #'error
  :substatements-function #'(lambda (s) (list (second s) (third s)))
  :value-subforms-function #'(lambda (s) (list (second s) (third s)))
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'trun:constantly-true
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement set-local-allocation
  :flow-function #'error
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )


(define-statement set-area
  :flow-function #'error
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement with-protected-variables
  :flow-function #'self-then-substatements-flow
  :substatements-function #'cdr
  :value-subforms-function #'constantly-nil
  :expression nil
  :l-value nil
  :statement-subforms-function #'cdr
  :relocating-statement-function #'constantly-nil
  :state-changing-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

(define-statement cast
  :flow-function #'substatements-then-self-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value t
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'relocating-call-statement-p
  :gc-ok-function #'trun:constantly-true
  )

(define-statement c-call
  :flow-function #'c-call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'c-call-init
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'call-gc-ok-function ; wrong, but not used now
  )

(define-statement values-c-call
  :flow-function #'c-call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'c-call-init
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'call-gc-ok-function ; wrong, but not used define-statement variadic-values-c-call
  :flow-function #'c-call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'c-call-init
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'call-gc-ok-function ; wrong, but not used now
  )

(define-statement variadic-c-call
  :flow-function #'c-call-flow
  :substatements-function #'cddr
  :value-subforms-function #'cddr
  :expression t
  :l-value nil
  :initializer #'c-call-init
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'call-gc-ok-function ; wrong, but not used now
  )

(define-statement function-name
  :flow-function #'flow-straight-thru
  :substatements-function #'constantly-nil
  :value-subforms-function #'constantly-nil
  :expression t
  :l-value nil
  :statement-subforms-function #'constantly-nil
  :relocating-statement-function #'constantly-nil
  :gc-ok-function #'trun:constantly-true
  )

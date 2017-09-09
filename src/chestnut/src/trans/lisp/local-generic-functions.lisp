;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; GENERIC-FLET & friends.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/local-generic-functions.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:08 $")

;;; GENERIC-FUNCTION
;;;
;;; This macro is pretty simple.  It just binds a variable to the result of
;;; calling make-generic-function on the appropriate initargs, initializes the
;;; list of initial methods using the :method specifiers, and returns the
;;; generic-function object.

(define-translator-macro GENERIC-FUNCTION
    (lambda-list &rest options &environment env)
  (multiple-value-bind (initargs methods)
      (parse-generic-function-arguments lambda-list options env t)
    (let ((gf (make-variable "GENERIC-FUNCTION"))
	  (class (find-generic-function-class-from-initargs initargs env)))
      (multiple-value-bind (bindings declspecs add-forms)
	  (collect-initial-methods gf :anonymous methods env)
	`(the ,class
	      (let ((,gf (tclos-run:make-generic-function ,@initargs)))
		(declare (type ,class ,gf))
		(flet ,bindings
		  (declare ,@declspecs)
		  (tclos-run:update-initial-methods ,gf (list ,@add-forms))
		  )))))))

(define-translator-declaration local-generic-function (decl-spec env)
  (declare (ignore env))
  (destructuring-bind (function-name variable-name) (cdr decl-spec)
    (values ()
	    `((,function-name local-generic-function ,variable-name))
	    ()
	    ())))

;;; GENERIC-FLET
;;; GENERIC-LABELS
;;;
;;; These are a bit more complicated than the GENERIC-FUNCTION macro.  For
;;; these macros, variables get bound to the result of calling
;;; make-generic-function with the corresponding initargs for each of the bound
;;; names.  The list of initial methods for each generic-function object is
;;; then initialized using the corresponding :method specifiers.
;;;
;;; The thing that makes this a bit complicated is that the scope of the bound
;;; names must be walked, with references to the bound functions being
;;; transformed into references to the corresponding variable.
;;;
;;; *** Some additional work could be done here to eliminate unreferenced
;;; *** bindings.  Currently that won't happen if there are any methods
;;; *** specified, since the form for setting the initial methods will
;;; *** reference the variable containing the generic-function.
;;;
;;; *** Some additional work should be done to improve this code with respect
;;; *** to dynamic-extent declarations.  Those bindings which are either only
;;; *** referenced downward or have dynamic-extent declarations attached to
;;; *** them should permit dynamic allocation, including of the methods.

(define-translator-macro GENERIC-FLET (bindings &body body &environment env)
  (multiple-value-bind (body declspecs)
      (parse-body body nil)
    (multiple-value-bind (names vars bindings binding-decls methods)
	(collect-generic-flet/labels-info bindings env)
      (multiple-value-bind (bound free)
	  (split-declarations-for-functions names env declspecs)
	(declare (ignore bound))
	`(let ,bindings
	   (declare ,@binding-decls)
	   ,@methods
	   (locally
	     (declare ,@free)
	     ,@(walk:walk-progn
		    body
		    (translator-augment-environment
		         env
			 :function names
			 :variable vars
			 :declare (append declspecs binding-decls))
		    (make-generic-flet/labels-body-walker names))))))))

(define-translator-macro GENERIC-LABELS (bindings &body body &environment env)
  (multiple-value-bind (body declspecs)
      (parse-body body nil)
    (multiple-value-bind (names vars bindings binding-decls methods)
	(collect-generic-flet/labels-info bindings env)
      (multiple-value-bind (bound free)
	  (split-declarations-for-functions names env declspecs)
	(let* ((binding-env
		 (translator-augment-environment
		      env
		      :function names
		      :variable vars
		      :declare (append bound binding-decls)))
	       (body-env
		 (translator-augment-environment
		      binding-env
		      :declare free))
	       (walker (make-generic-flet/labels-body-walker names)))
	  `(let ,bindings
	     (declare ,@binding-decls)
	     ,@(walk:walk-progn methods binding-env walker)
	     (locally
	       (declare ,@free)
	       ,@(walk:walk-progn body body-env walker))))))))

(defun collect-generic-flet/labels-info (bindings env)
  (let ((names ())
	(vars ())
	(var-bindings ())
	(declspecs ())
	(methods ()))
    (dolist (binding bindings)
      (multiple-value-bind (name var var-binding var-decls method)
	  (collect-generic-flet/labels-info-1 binding env)
	(push name names)
	(push var vars)
	(push var-binding var-bindings)
	(setf declspecs (append var-decls declspecs))
	(push method methods)))
    (values (nreverse names)
	    (nreverse vars)
	    (nreverse var-bindings)
	    declspecs
	    (nreverse methods))))

(defun collect-generic-flet/labels-info-1 (binding env)
  (destructuring-bind (name lambda-list &rest options) binding
    (multiple-value-bind (initargs method-specs)
	(parse-generic-function-arguments lambda-list options env t)
      (let ((var (make-name "~A" (principal-name-of-function-name name)))
	    (class (find-generic-function-class-from-initargs initargs env)))
	(values name
		var
		`(,var (tclos-run:make-generic-function
			    :name ',name ,@initargs))
		`((local-generic-function ,name ,var)
		  (type ,class ,var))
		`(make-generic-flet/labels-initial-methods
		      ,var ,name ,@method-specs))))))

(define-translator-macro make-generic-flet/labels-initial-methods
    (gf name &rest method-specs &environment env)
  (multiple-value-bind (bindings declspecs add-forms)
      (collect-initial-methods gf name method-specs env)
    ;; If the generic function is declared to have dynamic extent, pass that
    ;; declaration along to the method functions.
    (when (variable-information-value gf 'dynamic-extent env)
      (push `(dynamic-extent ,@(mapcar #'(lambda (name) `#',name) bindings))
	    declspecs))
    `(flet ,bindings
       (declare ,@declspecs)
       (tclos-run:update-initial-methods ,gf (list ,@add-forms)))))
	    
(defun make-generic-flet/labels-body-walker (names)
  (flet ((walk-generic-flet/labels-body (form env walker &aux temp)
	   (declare (ignore walker))
	   (flet ((find-transform-var (name)
		    (function-information-value name
						'local-generic-function
						env)))
	     (cond ((atom form) (values form nil))
		   ((eq (setf temp (car form)) 'function)
		    (destructuring-bind (name) (cdr form)
		      (if (and (member name names :test #'equal)
			       (setf temp (find-transform-var name)))
			  (values temp nil)
			  (values form nil))))
		   ((and (symbolp temp)
			 (member temp names :test #'eq)
			 (setf temp (find-transform-var temp)))
		    (values `(funcall ,temp ,@(cdr form)) nil))
		   (t
		    (values form nil))))))
    #'walk-generic-flet/labels-body))

(defun find-generic-function-class-from-initargs (initargs env)
  (multiple-value-bind (value therep)
      (cgetf initargs :generic-function-class)
    (when therep
      (multiple-value-setq (value therep)
	(translator-constant-value value env)))
    (if therep
	value
	'generic-function)))

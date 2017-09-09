;;; -*- Mode: Lisp; Package: TUTIL; Syntax: Common-Lisp -*-
;;;
;;; tcldefs.lisp -- definitions for shadowed TCL things
;;;
;;; author :  Sandra Loosemore
;;; date   :  05 Oct 1990
;;;
;;;
;;; This file contains definitions for things in the TCL package that
;;; shadow symbols provided by the host Lisp.
;;;

(in-package "TUTIL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/tcldefs.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:13 $")

(defun tx:augment-environment (env &rest options)
    (if (translator-environment-p (setq env (coerce-to-environment env)))
	(apply #'translator-augment-environment env options)
	(apply #'hostx:augment-environment env options)))

;;; Code that sometimes evaluates at compile time and sometimes at runtime
;;; (such as macroexpansion functions) should be able to use eval-run.

(defun tx:eval-run (form)
  (eval form))

(defun tcl:compiler-macro-function (name &optional (env nil env-p))
  (cond ((not env-p)
	 (compiler-macro-function name))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-compiler-macro-function name env))
	(t
	 (compiler-macro-function name env))))

(defun set-compiler-macro-function (value name &optional (env nil env-p))
  (cond ((not env-p)
	 #+(and lucid (not (and lcl4.0 translator-supports-clos))) 
	 (warn "set-compiler-macro-function ~S" name)
	 #-(and lucid (not (and lcl4.0 translator-supports-clos)))
	 (setf (compiler-macro-function name) value))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (setf (translator-compiler-macro-function name env) value))
	(t
	 #+(and lucid (not (and lcl4.0 translator-supports-clos))) 
	 (warn "set-compiler-macro-function ~S" name)
	 #-(and lucid (not (and lcl4.0 translator-supports-clos)))
	 (setf (compiler-macro-function name env) value))))

(define-setf-method tcl:compiler-macro-function (name &optional env)
  (let* ((vals (cons name (when env (list env))))
	 (vars (mapcar #'(lambda (val) (declare (ignore val)) (gensym)) vals))
	 (store (gensym)))
    (values vars
	    vals
	    (list store)
	    `(set-compiler-macro-function ,store ,@vars)
	    `(tcl:compiler-macro-function ,@vars))))


;;; Return two values, the first being the value of the constant form, and the
;;; second being a boolean which is true if the first value is real, and false
;;; otherwise.  Signals an error if form is not a constant.

(defun tx:constant-value (form &optional environment)
  (setf environment (coerce-to-environment environment))
  (cond ((translator-environment-p environment)
	 (translator-constant-value form environment))
	((constantp form) (values (eval form) t t))
	(t (values nil nil nil))))

(defun tcl:constantp (name &optional (env nil env-p))
  (cond ((not env-p)
	 (constantp name))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-constantp name env))
	(t
	 (constantp name env))))

(defun tx:declaration-information (name &optional (env nil env-p))
  (cond ((not env-p)
	 (hostx:declaration-information name))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-declaration-information name env))
	(t
	 (hostx:declaration-information name env))))

(defun tx:enclose (lambda-expression &optional (env nil env-p))
  (cond ((not env-p)
	 (hostx:enclose lambda-expression))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-enclose lambda-expression env))
	(t
	 (hostx:enclose lambda-expression env))))

#+translator-supports-clos
(defun tcl:ensure-generic-function (function-name &rest stuff
						  &key (environment nil env-p)
						  &allow-other-keys)
  (if (or (not env-p)
	  (not (translator-environment-p
		(setq environment (coerce-to-environment environment)))))
      (apply #'ensure-generic-function function-name stuff)
      (apply #'translator-ensure-generic-function function-name stuff)))

#+translator-supports-clos
(defun tcl:find-class (symbol &optional (errorp t) (env nil env-p))
  (cond ((not env-p)
	 (find-class symbol errorp))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-find-class symbol errorp env))
	(t
	 (find-class symbol errorp env))))

;;; Conditionalized to avoid error in Lucid release 3 when compiling
;;; SETF of FIND-CLASS.
#+translator-supports-clos
(defun set-find-class (value symbol &optional errorp (env nil env-p))
  (cond ((not env-p)
	 (setf (find-class symbol errorp) value))
	((translator-environment-p (setf env (coerce-to-environment env)))
	 (setf (translator-find-class symbol errorp env) value))
	(t
	 (setf (find-class symbol errorp env) value))))

#+translator-supports-clos
(define-setf-method tcl:find-class
        (&rest rest)
  (let ((vars (mapcar #'(lambda (value) (declare (ignore value)) (gensym))
		      rest))
	(store (gensym)))
    (values vars
	    rest
	    (list store)
	    `(set-find-class ,store ,@vars)
	    `(tcl:find-class ,@vars))))

(defun tx:function-information (name &optional (env nil env-p))
  (cond ((not env-p)
	 (hostx:function-information name))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-function-information name env))
	(t
	 (hostx:function-information name env))))


;;; At some point, our SETF implementation ought to be converted to use
;;; the new names internally....

(defun tcl:get-setf-expansion (form &optional (env nil env-p))
  (cond ((not env-p)
	 (hostx:get-setf-method-multiple-value form))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-get-setf-method-multiple-value form env))
	(t
	 (hostx:get-setf-method-multiple-value form env))))

(defun tx:get-setf-method (form &optional (env nil env-p))
  (cond ((not env-p)
	 (hostx:get-setf-method form))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-get-setf-method form env))
	(t
	 (hostx:get-setf-method form env))))
	   
(defun tx:get-setf-method-multiple-value (form &optional (env nil env-p))
  (cond ((not env-p)
	 (hostx:get-setf-method-multiple-value form))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-get-setf-method-multiple-value form env))
	(t
	 (hostx:get-setf-method-multiple-value form env))))


(defun tcl:macro-function (name &optional (env nil env-p))
  (cond ((not env-p)
	 (macro-function name))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-macro-function name env))
	(t
	 (macro-function name env))))

(defun tcl:macroexpand (form &optional (env nil env-p))
  (cond ((not env-p)
	 (macroexpand form))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-macroexpand form env))
	(t
	 (macroexpand form env))))

(defun tcl:macroexpand-1 (form &optional (env nil env-p))
  (cond ((not env-p)
	 (macroexpand-1 form))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-macroexpand-1 form env))
	(t
	 (macroexpand-1 form env))))

(defun tx:parse-declarations (declspecs env &rest keys)
  (if (translator-environment-p (setf env (coerce-to-environment env)))
      (apply #'translator-parse-declarations declspecs env keys)
      (error "No handler for parse-declarations in host environment.")))

(defun tx:parse-macro (name lambda-list body &optional (env nil env-p))
  (cond ((not env-p)
	 (hostx:parse-macro name lambda-list body))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-parse-macro name lambda-list body env))
	(t
	 (hostx:parse-macro name lambda-list body env))))

(defun tcl:proclaim (decl-spec &optional (env nil env-p))
  (cond ((not env-p)
	 (proclaim decl-spec))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-proclaim decl-spec env))
	(t
	 (proclaim decl-spec))))	; not defined to take env argument

(defun tcl:subtypep (type1 type2 &optional (env nil env-p))
  (cond ((not env-p)
	 (subtypep type1 type2))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-subtypep type1 type2 env))
	(t
	 (subtypep type1 type2 env))))

(defun tcl:typep (object type &optional (env nil env-p))
  (cond ((not env-p)
	 (typep object type))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-typep object type env))
	(t
	 (typep object type env))))

(defun tcl:upgraded-array-element-type (type &optional (env nil env-p))
  (cond ((not env-p)
	 (upgraded-array-element-type type))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-upgraded-array-element-type type env))
	(t
	 (upgraded-array-element-type type env))))

(defun tcl:upgraded-complex-part-type (type &optional (env nil env-p))
  (cond ((not env-p)
	 (upgraded-complex-part-type type))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-upgraded-complex-part-type type env))
	(t
	 (upgraded-complex-part-type type env))))

(defun tx:variable-information (name &optional (env nil env-p))
  (cond ((not env-p)
	 (hostx:variable-information name))
	((translator-environment-p (setq env (coerce-to-environment env)))
	 (translator-variable-information name env))
	(t
	 (hostx:variable-information name env))))

	   

	   










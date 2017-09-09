;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Defining constants for global indices.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/global-index.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:06 $")

;;; Provide a mechanism for defining a mapping from Lisp names to C variables
;;; which have values that are fixnum indices that can be computed at
;;; translation time.  The C variables have translation-time Lisp constants
;;; associated with them so that references to the C variables can be
;;; generated.
;;;
;;; Some usages of this facility include
;;; 1. Mapping a slot-name to the corresponding slot index.
;;; 2. Mapping a generic function name to the index into the discriminator
;;; table.

(eval-when (compile load eval)
(defvar *index-property-table* (make-hash-table :test 'eq))
)

(defmacro get-index-constant-property (reader)
  (if (constantp reader)
      (let ((reader (eval reader)))
	(or `',(gethash reader *index-property-table*)
	    (error "~S not defined as a global index accessor." reader)))
      (once-only (reader)
        `(or (gethash ,reader *index-property-table*)
	     (error "~S not defined as a global index accessor." ,reader)))))
      

;called only by defindex, which is called only at (defindex global-slot-index)
(defmacro add-index-constant-property (reader)
  (let ((property (intern (sformat "~A-~A"
				  reader 'index-constant-property))))
    `(progn
       (define-translator-property ,property #'identity)
       (eval-when (compile load eval)
	 (setf (gethash ',reader *index-property-table*) ',property)))))

(defmacro global-index-constant (reader name env)
  `(translator-environment-get ,name ,env
			       (get-index-constant-property ,reader)))

(defvar *index-constant-constructors* (make-hash-table :test #'eq))

(defun make-index-constant (reader name env &optional c-name)
  (funcall (or (gethash reader *index-constant-constructors*)
	       (error "Undefined global index name: ~S." reader))
	   name
	   env
	   c-name))

(defun make-index-constant-constructor (reader name-generator)
  #'(lambda (name env c-name)
      (let ((constant (gensym)))
	(setf (timpl::name-of-global-variable constant)
	      (cond ((null c-name) (funcall name-generator name env))
		    ((not (c-name-conflict-p c-name t)) c-name)
		    (t
		     (error "The global C identifier ~S is already in use."
			    c-name))))
	(setf (defined-as-variable constant)
	      (make-variable-descriptor :constant-p :simple-constant
					:dump-definition-p nil
					:foreign-p t))
	(setf (global-index-constant reader name env) constant))))

;;; DEFINDEX
;;;
;;; Define a new index mapping.
;;;
;;; Name is the name of the mapping.  It is used as the name of the reader
;;; function that looks up the constant associated with an index identifier.
;;;
;;; The mapping function is a function with one required argument (the name)
;;; and two optional arguments; the first is an environment (defaults to
;;; *default-global-environment*), and the second specifies whether a constant
;;; is to be created if one does not already exist (default t)
;;; Lambda-list and Body specify a function of two arguments, the index
;;; identifier and the environment, which computes the C name for the
;;; associated constant.

(defmacro DEFINDEX (name lambda-list &body body)
  (multiple-value-bind (body declspecs) (parse-body body)
    `(progn
       (add-index-constant-property ,name)
       (defun ,name (name &optional env (create-p t))
	 (setf env (coerce-to-environment env))
	 (when (null env) (setf env *default-global-environment*))
	 (or (global-index-constant ',name name env)
	     (when create-p
	       (make-index-constant ',name name env))))
       (setf (gethash ',name *index-constant-constructors*)
	     (make-index-constant-constructor
	          ',name
	          #'(lambda ,lambda-list
		      (declare ,@declspecs)
		      (block ,(body-block-name name) ,@body))))
       ',name)))

;;; CREATE-GLOBAL-INDEX

(defun CREATE-GLOBAL-INDEX (reader name &optional c-name env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (let ((var (global-index-constant reader name env)))
    (cond ((null var) (make-index-constant reader name env c-name))
	  ((or (null c-name)
	       (string= c-name (timpl::name-of-global-variable var)))
	   var)
	  (t
	   (error "~S constant for ~S alread exists with different C name ~S."
		  reader name (timpl::name-of-global-variable var))))))

;;; GLOBAL-INDEX-CONSTANT-VALUE
;;;
;;; Return the value associated with a global index constant.
;;;
;;; Reader is the name of the namespace reader, used to indicate which kind
;;; of global index is to be accessed.
;;;
;;; Name is the index identifier.  An error is signaled if no global index
;;; constant of the specified type has been associated with the name.  An error
;;; is signaled if the constant has been created but has not had a value
;;; associated with it.
;;;
;;; Env is the translation environment in which the lookup is to be performed.

(defun GLOBAL-INDEX-CONSTANT-VALUE (reader name &optional env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (let ((constant (or (global-index-constant reader name env)
		      (error "No ~S constant defined for ~S." reader name))))
    (multiple-value-bind (value therep)
	(translator-constant-value constant env)
      (if therep value
	  (error "No value specified for ~S constant for ~S." reader name)))))

(defun set-global-index-constant-value (reader name value &optional env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  (flet ((missing-constant-error (reader name)
	   (error "No ~S constant defined for ~S." reader name)))
    (let ((constant (or (global-index-constant reader name env)
			(missing-constant-error reader name))))
      (setf constant (or (defined-as-variable constant env)
			 (missing-constant-error reader name)))
      (if (variable-descriptor-constant-p constant)
	  (setf (variable-descriptor-value-p constant) t
		(variable-descriptor-value constant) value)
	  (missing-constant-error reader name)))))

(define-setf-method global-index-constant-value (reader name &optional env)
  (let* ((values (list* reader name (when env (list env))))
	 (temps (mapcar #'(lambda (value)
			    (declare (ignore value))
			    (gensym))
			values))
	 (store (gensym)))
    (values temps
	    values
	    (list store)
	    `(set-global-index-constant-value
	          ,(first temps)
	          ,(second temps)
	          ,store
	          ,@(when env (list (third temps))))
	    `(global-index-constant-value ,@temps))))

;;; MAP-GLOBAL-INDEX-CONSTANTS
;;;
;;; Apply the function to each of the index identifiers and the associated
;;; constants for the the indicated index namespace in the environment.
;;;
;;; Function is a function of two arguments, the index identifier and the
;;; associated constant.
;;;
;;; Reader is the name of the namespace reader, used to indicate which kind
;;; of global index is to be accessed.
;;;
;;; Env is the translation environment in which the lookup is to be performed.

(defmacro MAP-GLOBAL-INDEX-CONSTANTS (function reader &optional env)
  `(translator-map-environment-names
    ,function
    ,env
    (get-index-constant-property ,reader)))

;;; RESET-GLOBAL-INDEX-CONSTANTS
;;;
;;; Remove the values associated with each of the constants associated with
;;; index identifiers for the specified namespace.

(defmacro RESET-GLOBAL-INDEX-CONSTANTS (reader &optional env)
  (once-only (env)
    `(map-global-index-constants
      #'(lambda (name constant)
	  (declare (ignore name))
	  (let ((descriptor (defined-as-variable constant ,env)))
	    (setf (variable-descriptor-value-p descriptor) nil)))
      ,reader
      ,env)))

;;; -*- Mode: Lisp; Package: TUTIL; Syntax: Common-Lisp -*-
;;;
;;; type.lisp -- type system interface
;;;
;;; author  :  Sandra Loosemore
;;; date    :  04 Dec 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TUTIL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/type.lisp,v $"
 "$Revision: 1.6 $"
 "$Date: 2007/07/10 16:57:58 $")

;;; Fixnums on the target machine are 30 bit, two's complement.

(defparameter most-positive-target-fixnum
  most-positive-fixnum)
(defparameter most-negative-target-fixnum
  most-negative-fixnum)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    DEFTYPE, type expander functions, etc.
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Use this macro to make predefined DEFTYPE expanders.
;;; The deftype expansion is normally applied only if there is not specific
;;;     handling for the type specifier as either a symbol or list.

(defmacro define-translator-type (name lambda-list &body body)
  `(progn
     (eval-when (#-translating compile)
       (when (defined-as-declaration ',name)
	 (warn "Defining ~S as a type, but it's already a declaration."
	       ',name)))
     (define-translator-type-internal
       ',name #',(translator-parse-deftype name lambda-list body))))

(defun define-translator-type-internal (name function)
  (when (defined-as-declaration name)
    (error "Defining ~S as a type, but it's already a declaration."
	   name))
  ;; *** There should be something here to prevent collisions with
  ;; *** defstruct, defclass, and friends.  However, we need to be able
  ;; *** to disable such a check while bootstrapping the translator.
  ;; *** The problem is that some names are defined as both types
  ;; *** and classes.
  (setf (defined-as-deftype name) function)
  name)

;;; These properties are used by TYPEP.  

(define-translator-property type-symbol-predicate #'identity)
(define-translator-property type-list-predicate #'identity)
(define-translator-property type-list-typep-optimizer #'identity)


;;; This stuff is used by SUBTYPEP.

(define-translator-property type-symbol-supertypes #'copy-list)

(defmacro type-symbol-p (name env)
  `(type-symbol-predicate ,name ,env))

(defmacro standard-type-list-p (name env)
  `(type-list-predicate ,name ,env))


;;; Use this macro to define stuff for predefined symbol type specifiers.

(defmacro define-type-symbol (name predicate supertypes)
  `(progn
     (setf (type-symbol-predicate ',name) ',predicate)
     (setf (type-symbol-supertypes ',name) ',supertypes)
     ',name))


;;; Use this macro to define stuff for predefined list type specifiers.

(defmacro define-type-list (name lambda-list &body body)
  (let ((function-name  (intern (format nil "~a-TYPEP" name))))
    `(progn
       (setf (type-list-predicate ',name) ',function-name)
       (defun ,function-name ,lambda-list ,@body)
       ',name)))


;;; Common routine for signaling this error.

(defun invalid-type-specifier-error (thing)
  (error "~S is not a valid type specifier." thing))

;;; Helper function for determining whether a type-specifier is a class object.
;;; It is written a little strangly to avoid potential problems with loading
;;; the translator, since classes might not have been defined yet.  It is
;;; essentially a substitute for (translator-typep typespec 'class env),
;;; but won't get an error if class hasn't been defined yet.

(defun type-specifier-class-p
    (type-specifier &optional env (class-type 'class))
  #-translator-supports-clos
  (declare (ignore type-specifier env class-type))
  #+translator-supports-clos
  (unless (and (or (eq class-type 'class)
		   (eq class-type 'structure-class))
	       (or (symbolp type-specifier)
		   (consp type-specifier)))
    (let ((class (translator-find-class class-type nil env)))
      (when class
	(instance-typep type-specifier class env)))))

;;; Determine whether something is a type specifier.
;;; Note that if the type specifier is something defined with DEFTYPE
;;; that expands into an undefined type specifier, this returns NIL.

(defun translator-type-specifier-p (type-specifier &optional env)
  ;(progn (print "translator-type-specifier-p") (print type-specifier))
  (or (cond ((symbolp type-specifier)
	     (or (type-symbol-p type-specifier env)
		 #+translator-supports-clos
		 (translator-find-class type-specifier nil env)))
	    ((consp type-specifier)
	     (standard-type-list-p (car type-specifier) env))
	    ((type-specifier-class-p type-specifier env) t)
	    ;; If none of the above cases, then not a type specifier, and don't
	    ;; need to call expand-type to prove it.
	    (t (return-from translator-type-specifier-p nil)))
      (let ((expansion (expand-type type-specifier env nil)))
	(when (not (eql expansion type-specifier))
	  (translator-type-specifier-p expansion env)))))

;;; Expand a type specifier, returning its expansion.  Signal an
;;; error if the thing hasn't been defined with DEFTYPE and error-p is
;;; true.

(defun expand-type (type-specifier env &optional (errorp t))
  (let* ((function nil)
	 (type (cond ((symbolp type-specifier)
		      (setf function (defined-as-deftype type-specifier env))
		      (when function (list type-specifier)))
		     ((consp type-specifier)
		      (setf function
			    (defined-as-deftype (car type-specifier) env))
		      (when function type-specifier))
		     ((type-specifier-class-p type-specifier env)
		      (return-from expand-type type-specifier))
		     (t nil))))
    (cond ((and type function)
	   (funcall function type env))
	  ((not errorp) type-specifier)
	  (t
	   (invalid-type-specifier-error type-specifier)))))


;;; Fully expand a type specifier.  This is used because some type
;;; specifiers are both treated specially as symbols and have DEFTYPE
;;; expansions.  Ordinarily we look for the symbols as special cases,
;;; but occasionally we might want to expand them fully into a more
;;; canonical form -- see subtypep-aux, for example.

(defun fully-expand-type (type-specifier env)
  (let ((new nil))
    (loop (if (eql (setq new (expand-type type-specifier env nil))
		   type-specifier)
	      (return type-specifier)
	      (setq type-specifier new)))))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Typep
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; This is easy.  For type specifier symbols, call the predicate on
;;; the object.  For a type specifier list, dispatch to a function that
;;; can look at its subfields.

(defun translator-typep (object type &optional env &aux temp)
  (cond ((symbolp type)
	 (cond ((setf temp (type-symbol-predicate type env))
		(when (or (not (symbolp temp))
			  (fboundp temp))
		  (funcall temp object)))
	       #+translator-supports-clos
	       ((setf temp (translator-find-class type nil env))
		(instance-typep object temp env))
	       (t
		(translator-typep object (expand-type type env t) env))))
	((consp type)
	 (if (setf temp (type-list-predicate (car type) env))
	     (funcall temp object type env)
	     (translator-typep object (expand-type type env t) env)))
	#+translator-supports-clos
	((type-specifier-class-p type env)
	 (instance-typep object type env))
	(t
	 (invalid-type-specifier-error type))))


;;; Try to optimize a call to TYPEP where the TYPE argument is a
;;; compile-time constant.  Return either a function call form,
;;; or NIL.
;;; This is pretty stupid in that it only knows about type specifier 
;;; symbols.  I thought about having it dispatch on type specifier lists
;;; to the appropriate type-list-predicate, but these are really internal
;;; functions.
;;; We might want to try to canonicalize list type specifiers into 
;;; equivalent type symbol specifiers, like recognizing that
;;; (simple-array t (*)) == simple-vector.

(defmacro define-typep-optimizer (name lambda-list &body body)
  (multiple-value-bind (body declspecs) (parse-body body)
    `(setf (type-list-typep-optimizer ',name)
           #'(lambda ,lambda-list
	       (declare ,@declspecs)
	       (block ,name ,@body)))))


(defun optimize-typep (object-form typespec env &optional (known-type 't))
  (loop (unless (and (consp object-form)
		     (eq (car object-form) 'the))
	  (return nil))
	(setq known-type (and-types known-type (cadr object-form)))
	(setq object-form (caddr object-form)))
  (when (atom object-form)
    (if (symbolp object-form)
	(setq known-type (and-types known-type
				    (variable-type object-form env)))
	(return-from optimize-typep
	  (translator-typep object-form typespec env))))
  (let ((temp nil))
    (cond ((translator-subtypep known-type typespec env)
	   't)
	  ((symbolp typespec)
	   (cond ((setq temp (type-symbol-predicate typespec env))
		  (unless (eq known-type 't)
		    (setq object-form `(the ,known-type ,object-form)))
		  `(,temp ,object-form))
		 ((setf temp (type-list-typep-optimizer typespec))
		  (funcall temp object-form typespec known-type env))
		 ((not (eql typespec
			    (setf typespec (expand-type typespec env nil))))
		  (optimize-typep object-form typespec env known-type))
		 #+translator-supports-clos
		 ((translator-find-class typespec nil env)
		  `(tclos-run:%class-typep ,object-form ',typespec))
		 (t nil)))
	  ((consp typespec)
	   (if (setq temp (type-list-typep-optimizer (car typespec)))
	       (funcall temp object-form typespec known-type env)
	       (unless (eql typespec
			    (setq typespec (expand-type typespec env nil)))
		 (optimize-typep object-form typespec env known-type))))
	  #+translator-supports-clos
	  ((type-specifier-class-p typespec env)
	   ;; If type specifier is a class object, try to resolve it to a
	   ;; built-in name, which might have a predicate defined for it.
	   (let ((name (resolve-class-to-name typespec env)))
	     (if (not (eq name typespec))
		 (optimize-typep object-form name env known-type)
		 `(tclos-run:%class-typep ,object-form ',typespec))))
	  (t nil))))

(define-typep-optimizer and (object-form typespec known-type env)
  (optimize-and/or-typep object-form typespec known-type env t))

(define-typep-optimizer or (object-form typespec known-type env)
  (optimize-and/or-typep object-form typespec known-type env nil))

(defun optimize-and/or-typep (object-form typespec known-type env empty-value)
  (cond ((null (cdr typespec))
	 ;; Be careful not to inadvertently promote to toplevel.
	 `(let () ,object-form ,empty-value))
	((null (cddr typespec))
	 `(tcl:typep ,object-form ',(cadr typespec)))
	(t
	 (once-only* (object-form) env
	   (unless (eq known-type 't)
	     (setq object-form `(the ,known-type ,object-form)))
	   (cons (car typespec)
		 (mapcar #'(lambda (type)
			     `(tcl:typep ,object-form ',type))
			 (cdr typespec)))))))

(define-typep-optimizer eql (object-form typespec known-type env)
  (declare (ignore env known-type))
  `(eql ,object-form ',(second typespec)))

(define-typep-optimizer member (object-form typespec known-type env)
  (declare (ignore env known-type))
  `(member ,object-form ',(rest typespec)))

(define-typep-optimizer not (object-form typespec known-type env)
  (declare (ignore env))
  (unless (eq known-type 't)
    (setq object-form `(the ,known-type ,object-form)))
  `(not (tcl:typep ,object-form ',(second typespec))))

(define-typep-optimizer satisfies (object-form typespec known-type env)
  (declare (ignore env known-type))
  ;; Must not use #' here, since call must be to global function even if there
  ;; is a local function of the same name visible.  We assume that handling of
  ;; funcall will resolve this if possible.
  `(funcall ',(second typespec) ,object-form))

(defun build-tests (typep type-test &rest tests)
  (unless typep (push type-test tests))
  (cond ((null tests)
	 't)
	((null (cdr tests))
	 (car tests))
	(t
	 `(and ,@tests))))

(define-typep-optimizer integer (object-form typespec known-type env)
  (let* ((min (or (cadr typespec) '*))
	 (max (or (caddr typespec) '*)))
    (once-only* (object-form) env
      (unless (eq known-type 't)
	(setq object-form `(the ,known-type ,object-form)))
      (cond ((and (eq min '*) (eq max '*))
	     (build-tests (translator-subtypep known-type 'integer env)
			  `(integerp ,object-form)))
	    ((eq min '*)
	     (build-tests (translator-subtypep known-type 'integer env)
			  `(integerp ,object-form)
			  `(<= ,object-form ,max)))
	    ((eq max '*)
	     (build-tests (translator-subtypep known-type 'integer env)
			  `(integerp ,object-form)
			  `(<= ,min ,object-form)))
	    ((or (< min most-negative-target-fixnum)
		 (> max most-positive-target-fixnum))
	     (build-tests (translator-subtypep known-type 'integer env)
			  `(integerp ,object-form)
			  `(<= ,min ,object-form ,max)))
	    ((and (eql min most-negative-target-fixnum)
		  (eql max most-positive-target-fixnum))
	     (build-tests (translator-subtypep known-type 'fixnum env)
			  `(trun:fixnump ,object-form)))
	    ((eql min most-negative-target-fixnum)
	     (build-tests (translator-subtypep known-type 'fixnum env)
			  `(trun:fixnump ,object-form)
			  `(<= (the fixnum ,object-form) ,max)))
	    ((eql max most-positive-target-fixnum)
	     (build-tests (translator-subtypep known-type 'fixnum env)
			  `(trun:fixnump ,object-form)
			  `(<= ,min (the fixnum ,object-form))))
	    (t
	     (build-tests (translator-subtypep known-type 'fixnum env)
			  `(trun:fixnump ,object-form)
			  `(<= ,min (the fixnum ,object-form))
			  `(<= (the fixnum ,object-form) ,max)))))))

(define-typep-optimizer array (object-form typespec known-type env)
  (let ((element-type (or (cadr typespec) '*))
	(dimensions (or (caddr typespec) '*)))
    (once-only* (object-form) env
      (unless (eq known-type 't)
	(setq object-form `(the ,known-type ,object-form)))
      (cond ((and (eq element-type '*) (eq dimensions '*))
	     (build-tests (translator-subtypep known-type 'array env)
			  `(arrayp ,object-form)))
	    ((eq dimensions '*)
	     (let* ((eat (fully-expand-type element-type env))
		    (uat (translator-upgraded-array-element-type 
			  element-type env))
		    (euat (fully-expand-type uat env)))
	       (when (equal eat euat)
		 (build-tests (translator-subtypep known-type 'array env)
			      `(arrayp ,object-form)
			      `(,(if (symbolp uat) 'eq 'equal)
				 ',uat
				 (array-element-type ,object-form))))))
	    ((eq element-type '*)
	     (apply #'build-tests 
		    (translator-subtypep known-type 'array env)
		    `(arrayp ,object-form)
		    `(= ,(length dimensions) (array-rank ,object-form))
		    (let ((dim 0))
		      (mapcan #'(lambda (size)
				  (prog1 (unless (eq size '*)
					   `((= ,size 
						(array-dimension 
						 ,object-form ,dim))))
				    (incf dim)))
			      dimensions))))
	    (t
	     (let* ((eat (fully-expand-type element-type env))
		    (uat (translator-upgraded-array-element-type 
			  element-type env))
		    (euat (fully-expand-type uat env)))
	       (when (equal eat euat)
		 (apply #'build-tests
			(translator-subtypep known-type 'array env)
			`(arrayp ,object-form)
			`(,(if (symbolp uat) 'eq 'equal)
			   ',uat
			   (array-element-type ,object-form))
			`(= ,(length dimensions) (array-rank ,object-form))
			(let ((dim 0))
			  (mapcan #'(lambda (size)
				      (prog1 (unless (eq size '*)
					       `((= ,size 
						    (array-dimension 
						     ,object-form ,dim))))
					(incf dim)))
				  dimensions))))))))))

(define-typep-optimizer simple-array (object-form typespec known-type env)
  (let ((element-type (or (cadr typespec) '*))
	(dimensions (or (caddr typespec) '*)))
    (once-only* (object-form) env
      (unless (eq known-type 't)
	(setq object-form `(the ,known-type ,object-form)))
      (cond ((and (eq element-type '*) (eq dimensions '*))
	     (build-tests (translator-subtypep known-type 'simple-array env)
			  `(trun:%simple-array-p ,object-form)))
	    ((eq dimensions '*)
	     (let* ((eat (fully-expand-type element-type env))
		    (uat (translator-upgraded-array-element-type 
			  element-type env))
		    (euat (fully-expand-type uat env)))
	       (when (equal eat euat)
		 (build-tests (translator-subtypep known-type
						   'simple-array env)
			      `(trun:simple-array-p ,object-form)
			      `(,(if (symbolp uat) 'eq 'equal)
				 ',uat
				 (array-element-type ,object-form))))))
	    ((eq element-type '*)
	     (if (= 1 (length dimensions))
		 (apply #'build-tests 
			(translator-subtypep known-type 
					     '(simple-array * (*)) env)
			`(trun:%primitive-vector-p ,object-form)
			(unless (eq (car dimensions) '*)
			  `((= ,(car dimensions)
			       (trun:%primitive-vector-length ,object-form)))))
		 (apply #'build-tests 
			(translator-subtypep known-type 'simple-array env)
			`(trun:simple-array-p ,object-form)
			`(= ,(length dimensions) (array-rank ,object-form))
			(let ((dim 0))
			  (mapcan #'(lambda (size)
				      (prog1 (unless (eq size '*)
					       `((= ,size 
						    (array-dimension
						     ,object-form ,dim))))
					(incf dim)))
				  dimensions)))))
	    (t
	     (let* ((eat (fully-expand-type element-type env))
		    (uat (translator-upgraded-array-element-type 
			  element-type env))
		    (euat (fully-expand-type uat env)))
	       (when (equal eat euat)
		 (if (= 1 (length dimensions))
		     ;; can do better when uat is T, BIT, or string-char
		     (apply #'build-tests 
			    (translator-subtypep known-type 
						 '(simple-array * (*)) env)
			    `(trun:%primitive-vector-p ,object-form)
			    `(,(if (symbolp uat) 'eq 'equal)
			       ',uat
			       (array-element-type ,object-form))
			    (unless (eq (car dimensions) '*)
			      `((= ,(car dimensions)
				   (trun:%primitive-vector-length 
				    ,object-form)))))
		     (apply #'build-tests 
			    (translator-subtypep known-type 'simple-array env)
			    `(trun:simple-array-p ,object-form)
			    `(,(if (symbolp uat) 'eq 'equal)
			       ',uat
			       (array-element-type ,object-form))
			    `(= ,(length dimensions) (array-rank ,object-form))
			    (let ((dim 0))
			      (mapcan #'(lambda (size)
					  (prog1 
					      (unless (eq size '*)
						`((= ,size 
						     (array-dimension 
						      ,object-form ,dim))))
					    (incf dim)))
				      dimensions)))))))))))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Subtypep
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; The approach here is that we first try to resolve the subtype argument
;;; into something we can deal with, and then deal with the supertype
;;; argument.  Then we look at what we've got left.
;;; The resolved arguments can be one of:
;;; * a symbol which has a type-symbol-supertypes property
;;; * a class object for a type that does not have a type-symbol-supertypes
;;;   property on its class name
;;; * one of the standard type specifier lists (excluding AND and OR, which
;;;   are handled specially during the resolving process)
;;; We might also want to try to canonicalize list type specifiers into 
;;; equivalent type symbol specifiers, like recognizing that
;;; (simple-array t (*)) == simple-vector.  Maybe someday.

(defun translator-subtypep (subtype supertype &optional env)
  (resolve-subtype subtype supertype env))


;;; Resolve the subtype into one of the canonical things, leaving the
;;; supertype alone.

(defun resolve-subtype (subtype supertype env &aux temp)
  (cond ((or (eq subtype 'nil)
	     (eq supertype 't)
	     (equal subtype supertype)) 
	 (values t t)) 
	((symbolp subtype)
	 (cond ((type-symbol-p subtype env)
		(resolve-supertype subtype supertype env))
	       #+translator-supports-clos
	       ((setf temp (translator-find-class subtype nil env))
		(resolve-supertype temp supertype env))
	       (t
		(resolve-subtype (expand-type subtype env t) supertype env))))
	((consp subtype)
	 (cond ((eq (setq temp (car subtype)) 'member)
		(resolve-member-subtype subtype supertype env))
	       ((eq temp 'or)
		(resolve-or-subtype subtype supertype env))
	       ((eq temp 'and)
		(resolve-and-subtype subtype supertype env))
	       ((eq temp 'values)
		(resolve-values-subtype subtype supertype env))
	       ((standard-type-list-p temp env)
		(resolve-supertype subtype supertype env))
	       (t
		(resolve-subtype (expand-type subtype env t) supertype env))))
	#+translator-supports-clos
	((type-specifier-class-p subtype env)
	 (resolve-supertype (resolve-class-to-name subtype env) supertype env))
	(t
	 (invalid-type-specifier-error subtype))
	 ))


;;; If each of the component types of an OR subtype is a subtype of the
;;; supertype, their union must also be a subtype of the supertype.
;;; If any of the component types is definitely not a subtype of the 
;;; supertype, then their union is also definitely not a subtype.

(defun resolve-or-subtype (subtype supertype env)
  (let ((default-subtypep   t)
	(default-certainp   t))
    (dolist (type (cdr subtype)
	     (values default-subtypep default-certainp))
      (multiple-value-bind (subtypep certainp)
	  (translator-subtypep type supertype env)
	(if (not subtypep)
	    (if certainp
		(return (values subtypep certainp))
		(progn
		  (setq default-subtypep subtypep)
		  (setq default-certainp certainp))))))))

(defun resolve-member-subtype (subtype supertype env)
  (dolist (value (cdr subtype) (values t t))
    (unless (translator-typep value supertype env)
      (return (values nil t)))))


;;; If any of the component types of an AND subtype is a subtype of the
;;; supertype, then their intersection must also be a subtype of the supertype.
;;; However it is possible for the intersection to be a subtype even if
;;; none of the component types are.  In that case we give up and 
;;; return NIL NIL; it's theoretically possible to come up with a more 
;;; precise answer though.

(defun resolve-and-subtype (subtype supertype &optional env (expand-p t))
  (cond (expand-p
	 (let ((subtype (and-type-list (cdr subtype) env)))
	   (if (and (consp subtype) (eq (car subtype) 'and))
	       (resolve-and-subtype subtype supertype env nil)
	       (resolve-subtype subtype supertype env))))
	((null (cdr subtype))
	 (resolve-subtype t supertype env))
	((null (cddr subtype))
	 (resolve-subtype (cadr subtype) supertype env))
	((some #'(lambda (type) (translator-subtypep type supertype env))
	       (cdr subtype))
	 (values t t))
	(t
	 (values nil nil))))
    
(defun resolve-values-subtype (subtype supertype env)
  (cond ((and (consp supertype) (eq (car supertype) 'values))
	 (let ((subtype-tail (cdr subtype))
	       (supertype-tail (cdr supertype)))
	   (loop (unless subtype-tail
		   (return (if supertype-tail
			       (values nil t)
			       (values t t))))
		 (unless supertype-tail
		   (return (values nil t)))
		 (let ((subtype-arg (pop subtype-tail))
		       (supertype-arg (pop supertype-tail)))
		   (unless (eq subtype-arg supertype-arg)
		     (when (or (member subtype-arg lambda-list-keywords)
			       (member supertype-arg lambda-list-keywords))
		       (return (values nil t)))
		     (multiple-value-bind (subtype-p certain-p)
			 (translator-subtypep subtype-arg supertype-arg env)
		       (unless subtype-p
			 (return (values nil certain-p)))))))))
	((null (cdr subtype))
	 (values nil nil))
	((null (cddr subtype))
	 (resolve-subtype (cadr subtype) supertype env))
	(t
	 (values nil nil))))


;;; Resolve the supertype into one of the canonical things, leaving the
;;; subtype (already resolved) alone.

(defun resolve-supertype (subtype supertype env &aux temp)
  (cond ((eq supertype 't)
	 (values t t))
	((equal subtype supertype)
	 (values t t))
	((symbolp supertype)
	 (cond ((type-symbol-p supertype env)
		(subtypep-aux subtype supertype env))
	       #+translator-supports-clos
	       ((setf temp (translator-find-class supertype nil env))
		(subtypep-aux subtype temp env))
	       (t
		(resolve-supertype subtype
				   (expand-type supertype env t)
				   env))))
	((consp supertype)
	 (cond ((eq (setq temp (car supertype)) 'and)
		(resolve-and-supertype subtype supertype env))
	       ((eq temp 'or)
		(resolve-or-supertype subtype supertype env))
	       ((eq temp 'values)
		(resolve-values-supertype subtype supertype env))
	       ((standard-type-list-p temp env)
		(subtypep-aux subtype supertype env))
	       (t
		(resolve-supertype subtype
				   (expand-type supertype env t)
				   env))))
	#+translator-supports-clos
	((type-specifier-class-p supertype env)
	 (subtypep-aux subtype (resolve-class-to-name supertype env) env))
	(t
	 (invalid-type-specifier-error supertype))))


;;; If each of the component types of an AND supertype is a supertype of
;;; the subtype, their intersection must also be a supertype of the subtype.
;;; If any of the component types is definitely not a supertype of the
;;; subtype, then their intersection is definitely not a supertype.

(defun resolve-and-supertype (subtype supertype env)
  (let ((default-subtypep   t)
	(default-certainp   t))
    (dolist (type (cdr supertype)
	     (values default-subtypep default-certainp))
      (multiple-value-bind (subtypep certainp)
	  (translator-subtypep subtype type env)
	(if (not subtypep)
	    (if certainp
		(return (values subtypep certainp))
		(progn
		  (setq default-subtypep subtypep)
		  (setq default-certainp certainp))))))))


(defun resolve-values-supertype (subtype supertype env)
  (cond ((and (consp subtype) (eq (car subtype) 'values))
	 (error "shouldn't get here")) ; handled by resolve-values-subtype
	((null (cdr supertype))
	 (values nil nil))
	((null (cddr supertype))
	 (translator-subtypep subtype (cadr supertype) env))
	(t
	 (values nil nil))))

;;; If at least one of the component types of an OR supertype is a supertype
;;; of the subtype, then their union must also be a supertype of the subtype.
;;; However it is possible for the union to be a supertype even if none
;;; of the component types are.  In that case we give up and return NIL NIL;
;;; it's theoretically possible to come up with a more precise answer though.

(defun resolve-or-supertype (subtype supertype env)
  (cond ((null (cdr supertype))
	 (resolve-supertype subtype nil env))
	((null (cddr supertype))
	 (resolve-supertype subtype (cadr supertype) env))
	((some #'(lambda (type) (translator-subtypep subtype type env))
	       (cdr supertype))
	 (values t t))
	(t
	 (values nil nil))))


;;; Helper function for resolve-subtype/supertype.
;;; Class must be a class object.  If the name of the class is a built in
;;; type name, return the name.  Otherwise return the class.
#+translator-supports-clos
(defun resolve-class-to-name (class env &aux name)
  (if (and (setf name (tcl:class-name class))
	   (type-symbol-p name env))
      name
      class))


;;; Now both the subtype and supertype have been resolved.  Look for
;;;     all the special cases.  Note that the ordering of the tests is
;;;     important here.
;;; First look for the simple case when both arguments are symbols.
;;; If both arguments are classes, get the subtype/supertype information
;;;     from the class precedence list of the subtype.
;;; Anything that has been resolved into a type specifier that doesn't
;;;     name a class can't possibly inherit from something that has been
;;;     resolved into a class.  This works because built in classes resolve
;;;     to their class name.
;;; If the subtype is a structure-class, it can inherit only from things
;;;     that are a supertype of structure-object, since multiple inheritance
;;;     is not permitted.
;;; If the subtype is a class, it can inherit either from anything
;;;     that is a supertype of standard-object, or from things on its
;;;     class precedence list.  (Some things like generic-function can
;;;     inherit from types other than standard-object.)  This presumes that
;;;     all non-built-in metaclasses other than structure-class will use
;;;     standard-instance as the base representation and ensure the presence
;;;     of standard-object in the cpl of all instance classes.  The idea is
;;;     that built-in classes will be resolved to the class name, structure
;;;     classes are already handled by previous clause, and all other classes
;;;     include standard-object.
;;; If all that fails, fully expand both type specifiers to put them into
;;; a more canonical form, and then go off and look for all the special
;;; cases.

(defun subtypep-aux (subtype supertype env)
  (cond ((and (symbolp subtype) (symbolp supertype))
	 (type-symbols-subtypep subtype supertype env))
	((and (consp subtype)
	      (member (car subtype)
		      '(member not eql satisfies and or values function)))
	 (values nil nil))
	((and (consp supertype)
	      (member (car supertype)
		      '(member not eql satisfies and or values function)))
	 (values nil nil))
	#+translator-supports-clos
	((and (type-specifier-class-p subtype env)
	      (type-specifier-class-p supertype env))
	 (classes-subtypep subtype supertype env))
	#+translator-supports-clos
	((type-specifier-class-p supertype env)
	 (values nil t))
	#+translator-supports-clos
	((type-specifier-class-p subtype env 'structure-class)
	 (subtypep-aux 'structure-object supertype env))
	#+translator-supports-clos
	((type-specifier-class-p subtype env)
	 (if (and (symbolp supertype)
		  (translator-find-class supertype nil env))
	     (classes-subtypep subtype
			       (translator-find-class supertype nil env) env)
	     (subtypep-aux 'standard-object supertype env)))
	(t
	 ;;*** It's assumed that type specifier symbols that are
	 ;;*** expanded further here don't expand into things that
	 ;;*** are in the list of things for which we return NIL NIL.
	 (subtypep-aux-aux
	  (fully-expand-type subtype env)
	  (fully-expand-type supertype env)
	  env))))


;;; Do the easy case where both arguments are type specifier symbols.

(defun type-symbols-subtypep (subtype supertype env)
  (if (or (eq subtype supertype)
	  (eq supertype 't)
	  (eq subtype 'nil)
	  (some #'(lambda (type) (type-symbols-subtypep type supertype env))
		(type-symbol-supertypes subtype env)))
      (values t t)
      (values nil t)))


;;; At this point we know that both type specifiers are real type specifiers
;;; (not classes) and at least one of them is a list.  Also, both type
;;; specifiers have been fully expanded.
;;; Look for various special cases where either the subtype or supertype
;;; is a type specifier symbol that requires some weird handling first.
;;; Then look for explicit matches of general classes between 
;;; the subtype and supertype specifiers.
;;; Again, the ordering of the tests here is important.

(defun subtypep-aux-aux (subtype supertype env)
  (cond ((eq supertype 'number)
	 ;; COMPLEX and REAL are an exhaustive partition of NUMBER.
	 (if (or (complex-type-p subtype)
		 (real-type-p subtype))
	     (values t t)
	     (values nil t)))
	;; The only types that are not subtypes of ATOM are
	;; CONS, SEQUENCE, LIST and T.  CONS is the only one of these
	;; that has a list form; since at least one of the subtype and
	;; supertype must be a list, none of the other cases can apply.
	((eq supertype 'atom)
	 (if (cons-type-p subtype)
	     (values nil t)
	     (values t t)))
	;; The only subtypes of SEQUENCE are CONS, LIST, and VECTOR.
	;; We've already taken care of LIST (which does not have
	;; list form type specifiers), so we need only check for CONS
	;; and VECTOR.  Recall that at this point we've already 
	;; canonicalized all the vector type specifiers into array 
	;; type specifiers though.
	((eq supertype 'sequence)
	 (cond ((array-type-p subtype)
		(array-subtypep subtype '(array * (*)) env))
	       ((cons-type-p subtype)
		(values t t))
	       (t
		(values nil t))))
	;; Now do the list form of the CONS type specifier.
	((cons-type-p supertype)
	 (if (cons-type-p subtype)
	     (cons-subtypep subtype supertype env)
	     (values nil t)))
	;; Test ARRAY subtypes from most specific to most general.
	;; The subtype must be at least as specific as the supertype.
	;; Dispatch to a helper function to match the array element
	;; type and dimensions.
	((simple-array-type-p supertype)
	 (if (simple-array-type-p subtype)
	     (array-subtypep subtype supertype env)
	     (values nil t)))
	((array-type-p supertype)
	 (if (array-type-p subtype)
	     (array-subtypep subtype supertype env)
	     (values nil t)))
	;; BIGNUM and RATIO need weird treatment because they are both
	;; unions of disjoint ranges.
	((eq subtype 'bignum)
	 (bignum-supertype-p supertype env))
	((eq subtype 'ratio)
	 (ratio-supertype-p supertype env))
	((eq supertype 'bignum)
	 (bignum-subtype-p subtype env))
	((eq supertype 'ratio)
	 (ratio-subtype-p subtype env))
	;; Test other REAL subtypes from most specific to most general.
	;; The subtype must be at least as specific as the supertype.
	;; Dispatch to a helper function to match the ranges.
	((float-type-p supertype)
	 (if (float-type-p subtype)
	     (numeric-subtypep subtype supertype env)
	     (values nil t)))
	((integer-type-p supertype)
	 (if (integer-type-p subtype)
	     (numeric-subtypep subtype supertype env)
	     (values nil t)))
	((rational-type-p supertype)
	 (if (rational-type-p subtype)
	     (numeric-subtypep subtype supertype env)
	     (values nil t)))
	((real-type-p supertype)
	 (if (real-type-p subtype)
	     (numeric-subtypep subtype supertype env)
	     (values nil t)))
	;; Test COMPLEX types, dispatching to a helper function to
	;; match the component types.
	((complex-type-p supertype)
	 (if (complex-type-p subtype)
	     (complex-subtypep subtype supertype env)
	     (values nil t)))
	;; Nothing matches.
	(t
	 (values nil t))))



;;; Predicates to test the form of a type specifier.

(defun cons-type-p (type)
  (or (eq type 'cons)
      (and (consp type) (eq (car type) 'cons))))

(defun simple-array-type-p (type)
  (or (eq type 'simple-array)
      (and (consp type) (eq (car type) 'simple-array))))

(defun array-type-p (type)
  (or (eq type 'array)
      (and (consp type) (eq (car type) 'array))
      (simple-array-type-p type)))

(defun complex-type-p (type)
  (or (eq type 'complex)
      (and (consp type) (eq (car type) 'complex))))

(defun float-type-p (type)
  (or (eq type 'float)
      (and (consp type) (eq (car type) 'float))))

(defun integer-type-p (type)
  (or (eq type 'integer)
      (and (consp type) (eq (car type) 'integer))))

(defun rational-type-p (type)
  (or (eq type 'rational)
      (and (consp type) (eq (car type) 'rational))
      (integer-type-p type)))

(defun real-type-p (type)
  (or (eq type 'real)
      (and (consp type) (eq (car type) 'real))
      (rational-type-p type)
      (float-type-p type)))


;;; Compare two cons type specifiers

(defun cons-subtypep (subtype supertype env)
  (multiple-value-bind (subtype-car subtype-cdr)
      (canonicalize-cons-type subtype env)
    (multiple-value-bind (supertype-car supertype-cdr)
	(canonicalize-cons-type supertype env)
      (multiple-value-bind (car-subtypep car-certain)
	  (unspecified-or-subtypep subtype-car supertype-car env)
	(multiple-value-bind (cdr-subtypep cdr-certain)
	    (unspecified-or-subtypep subtype-cdr supertype-cdr env)
	  (cond ((and car-subtypep cdr-subtypep)
		 (values t t))
		(car-subtypep
		 (values nil cdr-certain))
		(cdr-subtypep
		 (values nil car-certain))
		(t
		 (values nil (or car-certain cdr-certain)))))))))

(defun canonicalize-cons-type (type env)
  (declare (ignore env))
  (if (atom type)
      (values '* '*)
      (let ((car-type   (if (cdr type) (cadr type) '*))
	    (cdr-type   (if (cddr type) (caddr type) '*)))
	(values car-type cdr-type))))


;;; Compare two array type specifiers.

(defun array-subtypep (subtype supertype env)
  (multiple-value-bind (subtype-element-type subtype-dimensions)
      (canonicalize-array-type subtype env)
    (multiple-value-bind (supertype-element-type supertype-dimensions)
	(canonicalize-array-type supertype env)
      (if (and (unspecified-or-equal subtype-element-type
				     supertype-element-type)
	       (or (unspecified-or-equal subtype-dimensions
					 supertype-dimensions)
		   (and (consp subtype-dimensions)
			(eql (length subtype-dimensions)
			     (length supertype-dimensions))
			(every #'unspecified-or-equal
			       subtype-dimensions
			       supertype-dimensions))))
	  (values t t)
	  (values nil t)))))

(defun canonicalize-array-type (type env)
  (if (atom type)
      (values '* '*)
      (let ((element-type  (if (cdr type) (cadr type) '*))
	    (dimensions    (if (cddr type) (caddr type) '*)))
	(values
	 (if (not (eq element-type '*))
	     (translator-upgraded-array-element-type element-type env)
	     element-type)
	 (if (numberp dimensions)
	     (make-list dimensions :initial-element '*)
	     dimensions)))))



;;; Similar, for complex numbers.
;;; Since we only have one representation for complex numbers
;;; (translator-upgraded-complex-part-type always returns T), we effectively
;;; ignore the part-type specification.

(defun complex-subtypep (subtype supertype env)
  (declare (ignore subtype supertype env))
  (values t t))


;;; Compare two numeric type specifiers.  We know that the subtype
;;; relationship holds for the base types, now just check the ranges.

(defun numeric-subtypep (subtype supertype env)
  (multiple-value-bind (subtype-min subtype-max)
      (canonicalize-numeric-type subtype env)
    (multiple-value-bind (supertype-min supertype-max)
	(canonicalize-numeric-type supertype env)
      (if (and (or (eq supertype-min '*)
		   (and (not (eq subtype-min '*))
			(endpoint-greaterp subtype-min supertype-min)))
	       (or (eq supertype-max '*)
		   (and (not (eq subtype-max '*))
			(endpoint-lessp subtype-max supertype-max))))
	  (values t t)
	  (values nil t)))))


;;; This is a little strange.  To handle exclusive endpoints for integers,
;;; add or subract one to get an inclusive bound.
;;; We would really like to do something similar for floating point numbers
;;; (find the next biggest or next smallest representable float).  However
;;; in cross-compilation we have the problem that the representations on
;;; the host machine may not match those on the target machine anyway.
;;; So we cheat and treat them like rationals.

(defun canonicalize-numeric-type (type env)
  (multiple-value-bind (min max) (canonicalize-numeric-type-aux type env)
    (if (not (or (eq min '*)
		 (eq max '*)
		 (endpoint-lessp min max)))
	(error "Invalid range supplied in type specifier ~s." type)
	(values min max))))

(defun canonicalize-numeric-type-aux (type env)
  (declare (ignore env))
  (cond ((member type '(integer rational float real))
	 (values '* '*))
	((eq (car type) 'integer)
	 (values
	  (if (cdr type)
	      (if (consp (cadr type))
		  (1+ (car (cadr type)))
		  (cadr type))
	      '*)
	  (if (cddr type)
	      (if (consp (caddr type))
		  (1- (car (caddr type)))
		  (caddr type))
	      '*)))
	(t
	 (values
	  (if (cdr type) (cadr type) '*)
	  (if (cddr type) (caddr type) '*)))))


;;; Compare two endpoints of a range.  Each value may either be a number
;;; (specifying an inclusive endpoint) or a list of a number (specifying
;;; an exclusive endpoint).
;;; *** If the host Lisp implementation hasn't implement the new ANSI
;;; *** rules for contagion in comparison operators, these functions
;;; *** might give erroneous results.  We could get around this by 
;;; *** explicitly converting everything to rationals.

(defun endpoint-lessp (value1 value2)
  (if (numberp value1)
      (if (numberp value2)
	  (<= value1 value2)		; both closed
	  (< value1 (car value2)))	; value2 is open
      (if (numberp value2)
	  (<= (car value1) value2)	; value2 is open
	  (<= (car value1) (car value2))) ; both open
      ))

(defun endpoint-greaterp (value1 value2)
  (if (numberp value1)
      (if (numberp value2)
	  (>= value1 value2)		; both closed
	  (> value1 (car value2)))	; value2 is open
      (if (numberp value2)
	  (>= (car value1) value2)	; value2 is open
	  (>= (car value1) (car value2))) ; both open
      ))


;;; Check to see whether the type specifier is a supertype of BIGNUM.
;;; This includes only INTEGER, RATIONAL, and REAL type specifiers with
;;; both endpoints unspecified.

(defun bignum-supertype-p (type env)
  (if (and (real-type-p type)
	   (not (float-type-p type)))
      (multiple-value-bind (min max) (canonicalize-numeric-type type env)
	(if (and (eq min '*) (eq max '*))
	    (values t t)
	    (values nil t)))
      (values nil t)))


;;; Check to see whether the type specifier is a supertype of RATIO.
;;; This includes only RATIONAL and REAL type specifiers with both endpoints
;;; unspecified.

(defun ratio-supertype-p (type env)
  (if (and (real-type-p type)
	   (not (float-type-p type))
	   (not (integer-type-p type)))
      (multiple-value-bind (min max) (canonicalize-numeric-type type env)
	(if (and (eq min '*) (eq max '*))
	    (values t t)
	    (values nil t)))
      (values nil t)))


;;; Check to see whether the type specifier is a subtype of BIGNUM.  This
;;; includes only INTEGER type specifiers with ranges that are either
;;; entirely greater than or entirely less than the range of FIXNUMs.

(defun bignum-subtype-p (type env)
  (if (integer-type-p type)
      (multiple-value-bind (min max) (canonicalize-numeric-type type env)
	(if (or (and (not (eq max '*))
		     (< max most-negative-target-fixnum))
		(and (not (eq min '*))
		     (> min most-positive-target-fixnum)))
	    (values t t)
	    (values nil t)))
      (values nil t)))
		     

;;; Check to see whether the type specifier is a subtype of RATIO.  This
;;; includes only RATIONAL type specifiers with ranges that do not include
;;; any integers.

(defun ratio-subtype-p (type env)
  (if (and (rational-type-p type) (not (integer-type-p type)))
      (multiple-value-bind (min max) (canonicalize-numeric-type type env)
	(if (and (not (eq min '*))
		 (not (eq max '*))
		 (not (integerp min))
		 (not (integerp max))
		 (<= (if (consp max)
			 (car max)
			 max)
		     (if (consp min)
			 (if (integerp (car min))
			     (1+ (car min))
			     (ceiling (car min)))
			 (ceiling min))))
	    (values t t)
	    (values nil t)))
      (values nil t)))
		     

;;; A couple of helper functions

(defun unspecified-or-equal (object1 object2)
  (or (eq object2 '*)
      (equal object1 object2)))

(defun unspecified-or-subtypep (object1 object2 env)
  (if (eq object2 '*)
      (values t t)
      (subtypep object1 object2 env)))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Define synonym types
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; These type specifiers are all implemented in terms of some other
;;; primitives.


;;; In our implementation, base-char and character are exactly the
;;; same, and extended-character is an empty subset of them both.
;;; Likewise for string/base-string and simple-string/simple-base-string.
;;; *** should extended-character be made equivalent to type NIL?

(define-translator-type tx:string-char () 'character)

(define-translator-type base-char () 'character)

(define-translator-type simple-base-string (&optional size)
  (if (eq size '*)
      'simple-string
      `(simple-string ,size)))

(define-translator-type base-string (&optional size)
  (if (eq size '*)
      'string
      `(string ,size)))



;;; We only support one kind of float.

(defun float-synonym (low high)
  (if (and (eq low '*) (eq high '*))
      'float
      `(float ,low ,high)))

(define-translator-type double-float (&optional low high)
  (float-synonym low high))

(define-translator-type long-float (&optional low high)
  (float-synonym low high))

(define-translator-type short-float (&optional low high)
  (float-synonym low high))

(define-translator-type single-float (&optional low high)
  (float-synonym low high))



;;; Decompose all of the other array guys into array or simple-array.
;;; These are also treated specially as type specifier symbols.

(define-translator-type bit-vector (&optional size)
  `(array bit (,size)))

(define-translator-type simple-bit-vector (&optional size)
  `(simple-array bit (,size)))

(define-translator-type simple-string (&optional size)
  `(simple-array character (,size)))

(define-translator-type simple-vector (&optional size)
  `(simple-array t (,size)))

(define-translator-type string (&optional size)
  `(array character (,size)))

(define-translator-type vector (&optional element-type size)
  `(array ,element-type (,size)))



;;; Likewise for rational subtypes, also treated specially as symbols.

(define-translator-type fixnum (&environment env)
  (declare (ignore env))
  `(integer ,most-negative-target-fixnum
	    ,most-positive-target-fixnum))

(define-translator-type bit ()
  `(integer 0 1))


;;; Some random other guys.  These don't have definitions as symbols.

(define-translator-type signed-byte (&optional nbits)
  (if (eq nbits '*)
      'integer
      (let ((temp (ash 1 (1- nbits))))
	`(integer ,(- temp) ,(- temp 1)))))

(define-translator-type unsigned-byte (&optional nbits)
  (if (eq nbits '*)
      `(integer 0 *)
      `(integer 0 ,(1- (ash 1 nbits)))))

(define-translator-type mod (n)
  (if (eq n '*)
      `(integer 0 *)
      `(integer 0 ,(1- n))))





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Define the standard type symbols
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-type-symbol array arrayp (atom))
(define-type-symbol atom atom (t))
(define-type-symbol bignum trun:bignump (integer))
(define-type-symbol bit trun:bitp (fixnum))
(define-type-symbol bit-vector bit-vector-p (vector))
(define-type-symbol broadcast-stream trun:broadcast-stream-p (stream))
(define-type-symbol character characterp (atom))
#+translator-supports-clos
(define-type-symbol trun:class-wrapper trun:class-wrapper-p (atom))
(define-type-symbol trun:cobject trun:cobjectp (atom))
(define-type-symbol compiled-function compiled-function-p (function))
(define-type-symbol complex complexp (number))
(define-type-symbol concatenated-stream trun:concatenated-stream-p (stream))
(define-type-symbol cons consp (list))
(define-type-symbol echo-stream trun:echo-stream-p (stream))
#+translator-supports-clos
(define-type-symbol trun:effective-method trun:effective-method-p (atom))
(define-type-symbol extended-character trun:constantly-false (character))
(define-type-symbol file-stream trun:file-stream-p (stream))
(define-type-symbol fixnum trun:fixnump (integer))
(define-type-symbol float floatp (real))
(define-type-symbol function functionp (standard-object))
(define-type-symbol hash-table hash-table-p (atom))
(define-type-symbol integer integerp (rational))
(define-type-symbol trun:interaction-stream trun:interaction-stream-p (stream))
(define-type-symbol trun:internal-marker trun:internal-marker-p (atom))
(define-type-symbol keyword keywordp (symbol))
(define-type-symbol list listp (sequence))
(define-type-symbol logical-pathname trun:logical-pathname-p (pathname))
#+translator-supports-clos
(define-type-symbol method-combination trun:method-combination-p (atom))
(define-type-symbol nil trun:constantly-false (t))
(define-type-symbol null null (symbol list))
(define-type-symbol number numberp (atom))
(define-type-symbol package packagep (atom))
(define-type-symbol pathname pathnamep (atom))
(define-type-symbol random-state random-state-p (atom))
(define-type-symbol ratio trun:ratiop (rational))
(define-type-symbol rational rationalp (real))
(define-type-symbol readtable readtablep (atom))
(define-type-symbol real realp (number))
(define-type-symbol sequence trun:sequencep (t))
(define-type-symbol simple-array trun:simple-array-p (array))
(define-type-symbol simple-bit-vector simple-bit-vector-p
    (bit-vector simple-array))
(define-type-symbol simple-string simple-string-p (string simple-array))
(define-type-symbol simple-vector simple-vector-p (vector simple-array))
(define-type-symbol standard-char standard-char-p (character))
(define-type-symbol standard-object trun:standard-object-p (atom))
(define-type-symbol stream streamp (atom))
(define-type-symbol string stringp (vector))
(define-type-symbol trun:string-input-stream trun:string-input-stream-p
  (string-stream))
(define-type-symbol trun:string-output-stream trun:string-output-stream-p
  (string-stream))
(define-type-symbol string-stream trun:string-stream-p (stream))
(define-type-symbol structure-object trun:structure-object-p (atom))
(define-type-symbol synonym-stream trun:synonym-stream-p (stream))
(define-type-symbol symbol symbolp (atom))
(define-type-symbol t trun:constantly-true ())
(define-type-symbol two-way-stream trun:two-way-stream-p (stream))
(define-type-symbol vector vectorp (array sequence))

;;; We assume that the following types are all implemented (elsewhere)
;;; in terms of standard-object or structure-object:
;;; 
;;; Condition types:
;;;    arithmetic-error cell-error condition control-error
;;;    division-by-zero end-of-file error file-error
;;;    floating-point-inexact floating-point-invalid-operation
;;;    floating-point-overflow floating-point-underflow
;;;    package-error parse-error print-not-readable program-error
;;;    reader-error serious-condition simple-condition
;;;    simple-error simple-type-error simple-warning
;;;    storage-condition stream-error style-warning type-error
;;;    unbound-slot unbound-variable undefined-function warning
;;;
;;; CLOS-related stuff:
;;;    built-in-class class generic-function method method-combination
;;;    standard-class standard-generic-function standard-method
;;;    structure-class
;;;
;;; Random stuff:
;;;    restart (probably ought to be a built-in)
;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    List type specifiers
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; This defines behavior of TYPEP on these guys.  SUBTYPEP needs to have
;;; special knowledge about all of them.


;;; The type predicate for AND is fairly straightforward.

(define-type-list and (object type-spec env)
  (dolist (type (cdr type-spec) t)
    (if (not (translator-typep object type env)) (return nil))))


;;; For arrays, call a helper function.  See also simple-array below.

(define-type-list array (object type-spec env)
  (and (arrayp object)
       (array-typep-aux object type-spec env)))

(defun array-typep-aux (object type-spec env)
  (multiple-value-bind (element-type dimensions)
      (canonicalize-array-type type-spec env)
    (and (or (eq element-type '*)
	     (equal (if (stringp object)
			'character
			(translator-upgraded-array-element-type
			 (array-element-type object) env))
		    element-type))
	 (or (eq dimensions '*)
	     (let ((actual-dimensions  (array-dimensions object)))
	       (and (eql (length actual-dimensions) (length dimensions))
		    (every #'unspecified-or-equal
			   actual-dimensions dimensions)))))))



;;; We only support one kind of complex....

(define-type-list complex (object type-spec env)
  (declare (ignore type-spec env))
  (complexp object))


(define-type-list cons (object type-spec env)
  (if (consp object)
      (multiple-value-bind (car-type cdr-type)
	  (canonicalize-cons-type type-spec env)
	(and (or (eq car-type '*)
		 (translator-typep (car object) car-type env))
	     (or (eq cdr-type '*)
		 (translator-typep (cdr object) cdr-type env))))))


(define-type-list eql (object type-spec env)
  (declare (ignore env))
  (eql object (cadr type-spec)))


;;; We only support one type of float....

(define-type-list float (object type-spec env)
  (and (floatp object) (numeric-typep-aux object type-spec env)))

(defun numeric-typep-aux (object type-spec env)
  (multiple-value-bind (min max) (canonicalize-numeric-type type-spec env)
    (and (or (eq min '*)
	     (endpoint-greaterp object min))
	 (or (eq max '*)
	     (endpoint-lessp object max)))))

(define-type-list function (object type-spec env)
  (declare (ignore object env))
  (error "The type specifier ~s is not valid for discrimination." type-spec))


(define-type-list integer (object type-spec env)
  (and (integerp object) (numeric-typep-aux object type-spec env)))


(define-type-list member (object type-spec env)
  (declare (ignore env))
  (member object (cdr type-spec)))


(define-type-list not (object type-spec env)
  (not (translator-typep object (cadr type-spec) env)))


(define-type-list or (object type-spec env)
  (dolist (type (cdr type-spec) nil)
    (if (translator-typep object type env) (return t))))


(define-type-list rational (object type-spec env)
  (and (rationalp object) (numeric-typep-aux object type-spec env)))


(define-type-list real (object type-spec env)
  (and (realp object) (numeric-typep-aux object type-spec env)))


(define-type-list satisfies (object type-spec env)
  (declare (ignore env))
  (funcall (cadr type-spec) object))


(define-type-list simple-array (object type-spec env)
  (and (trun:simple-array-p object)
       (array-typep-aux object type-spec env)))


(define-type-list values (object type-spec env)
  (declare (ignore object env))
  (error "The type specifier ~s is not valid for discrimination." type-spec))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Type upgrading for arrays and complexes
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; We will probably support additional specialized array types at some
;;; point in the future.  This function needs to know about them.

(defmacro translator-subtypecase (type env &rest clauses)
  (let ((type-var (make-symbol "TYPE"))
	(env-var (make-symbol "ENV")))
    `(let ((,type-var ,type)
	   (,env-var ,env))
       (cond ,@(mapcar #'(lambda (clause)
			   (destructuring-bind (typespec &rest forms) clause
			     (let ((test
				    (if (eq typespec 'otherwise)
					't
				      `(translator-subtypep
					 ,type-var ',typespec ,env-var))))
			       `(,test ,@forms))))
		       clauses)))))

;The function TIMPL::DO-TRANSFORM-P calls this a lot, so make it fast.
(defun translator-upgraded-array-element-type (type &optional env)
  ;; Make an exception for SHORT-FLOAT and SINGLE-FLOAT, which should
  ;; be upgraded to SINGLE-FLOAT.
  (cond ((or (eq type 't) (eq type 'bit)
	     (eq type 'single-float) (eq type 'double-float)
	     (eq type 'character))
	 type)
	((eq type 'short-float)
	 'single-float)
	((eq type 'float)
	 'double-float)
	((eq type 'base-char)
	 'character)
	((and (consp type)
	      (eq (car type) 'integer)
	      (integerp (cadr type))
	      (integerp (caddr type)))
	 (let ((min (cadr type))
	       (max (caddr type)))
	   (if (<= 0 min)
	       (cond ((<= max #.(1- (ash 1 1)))
		      'bit)
		     ((<= max #.(1- (ash 1 8)))
		      '(unsigned-byte 8))
		     ((<= max #.(1- (ash 1 16)))
		      '(unsigned-byte 16))
		     ((<= max #.(1- (ash 1 32)))
		      '(unsigned-byte 32))
		     ((<= max #.(1- (ash 1 64)))
		      '(unsigned-byte 64))     
		     (t
		      't))
	       (cond ((and (<= #.(- (ash 1 (1- 8))) min)
			   (<= max #.(1- (ash 1 (1- 8)))))
		      '(signed-byte 8))
		     ((and (<= #.(- (ash 1 (1- 16))) min)
			   (<= max #.(1- (ash 1 (1- 16)))))
		      '(signed-byte 16))
		     ((and (<= #.(- (ash 1 (1- 32))) min)
			   (<= max #.(1- (ash 1 (1- 32)))))
		      '(signed-byte 32))
		     ((and (<= #.(- (ash 1 (1- 64))) min)
			   (<= max #.(1- (ash 1 (1- 64)))))
		      '(signed-byte 64))
		     (t
		      't)))))
	((and (consp type)
	      (eq (car type) 'signed-byte)
	      (integerp (cadr type)))
	 (let ((bits (cadr type)))
	   (cond ((<= bits 8)
		  '(signed-byte 8))
		 ((<= bits 16)
		  '(signed-byte 16))
		 ((<= bits 32)
		  '(signed-byte 32))
	         ((<= bits 64)
		  '(signed-byte 64))  
		 (t
		  't))))
	((and (consp type)
	      (eq (car type) 'unsigned-byte)
	      (integerp (cadr type)))
	 (let ((bits (cadr type)))
	   (cond ((<= bits 1)
		  'bit)
		 ((<= bits 8)
		  '(unsigned-byte 8))
		 ((<= bits 16)
		  '(unsigned-byte 16))
		 ((<= bits 32)
		  '(unsigned-byte 32))
                 ((<= bits 64)
		  '(unsigned-byte 64))  
		 (t
		  't))))
	((single-float-type-specifier-p type env)
	 'single-float)
	(t
	 (translator-subtypecase type env
	   (character 'character)
	   (float 'double-float)
	   (bit 'bit)
	   ((unsigned-byte 8) '(unsigned-byte 8))
	   ((signed-byte 8) '(signed-byte 8))
	   ((unsigned-byte 16) '(unsigned-byte 16))
	   ((signed-byte 16) '(signed-byte 16))
	   ((unsigned-byte 32) '(unsigned-byte 32))
	   ((signed-byte 32) '(signed-byte 32))
	   ((unsigned-byte 64) '(unsigned-byte 64))
	   ((signed-byte 64) '(signed-byte 64))
	   (otherwise t)))))

(defun single-float-type-specifier-p (type-specifier env)
  ;; Return T if should be upgraded, as an array element type, to SINGLE-FLOAT.
  ;; This needs to be an exception because the "normal" type system treats
  ;; all floats as identicial.
  ;; Modeled after TRANSLATOR-TYPE-SPECIFIER-P.
  (or (cond ((symbolp type-specifier)
	     (or (eq type-specifier 'short-float)
		 (eq type-specifier 'single-float)))
	    ((consp type-specifier)
	     (or (eq (car type-specifier) 'short-float)
		 (eq (car type-specifier) 'single-float)))
	    #+translator-supports-clos
	    ((type-specifier-class-p type-specifier env) nil)
	    ;; If none of the above cases, then not a type specifier, and don't
	    ;; need to call expand-type to prove it.
	    (t (return-from single-float-type-specifier-p nil)))
      (let ((expansion (expand-type type-specifier env nil)))
	(when (not (eql expansion type-specifier))
	  (single-float-type-specifier-p expansion env)))))


;;; We only support one representation of complexes.

(defun translator-upgraded-complex-part-type (type &optional env)
  (declare (ignore type env))
  t)






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Type-of
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; For the runtime system, this could be written more efficiently in
;;; C using a dispatch table based on the type tag encoded in the object,
;;; instead of sequentially testing the alternatives.
;;;
;;; The constraints on type-of are essentially that it has to return something
;;; at least as specific as things that have classes, and the result has
;;; to be recognizable by SUBTYPEP and TYPEP.

(defun translator-type-of (object)
  (cond ((trun:fixnump object) 'fixnum)
	((characterp object) 'character)
	((consp object) 'cons)
	((arrayp object)
	 (cond ((stringp object) 'string)
	       ((bit-vector-p object) 'bit-vector)
	       ((vectorp object) 'vector)
	       (t 'array)))
	((timpl::c-string-p object) 'string)
	((timpl::c-float-p object) 'float)
	((timpl::c-array-p object) 'array)
	((timpl::translator-foreign-type-p object) 'tx:foreign-type)
	((symbolp object) (if (null object) 'null 'symbol))
	((trun:bignump object) 'bignum)
	((trun:ratiop object) 'ratio)
	((floatp object) 'float)
	((complexp object) 'complex)
	((packagep object) 'package)
	;; These go near the end so that if the host implements one of the
	;; preceding types using defstruct or defclass, we'll get the type
	;; specifier we want.
	;;***	  ((trun:structure-object-p object)
	;;***	   ...)  ; get the structure type out of the object
	((trun:structure-object-p object)
	 'fixnum)
	#+translator-supports-clos
	((trun:standard-object-p object)
	 ;; *** This should perhaps be using translator-class-of?
	 (tclos:class-name (class-of object)))
	;; Put compiled-function-p after checks for generic-function classes,
	;; since in some implementations compiled-function-p may be true for
	;; at least some generic functions.
	((compiled-function-p object) 'compiled-function)
	(t (type-of object)
	)))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Type merging
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; These functions could be made a lot smarter.  However it's not really
;;; clear that it's worth the trouble.


;;; Intersect two type (or ftype) specifiers.

(defun and-types (type1 type2 &optional env)
  (cond ((or (eq type1 t)
	     (equal type1 '(values &rest t)))
	 type2)
	((or (eq type2 t)
	     (equal type2 '(values &rest t)))
	 type1)
	((equal type1 type2) type1)
	(t (and-type-list (list type1 type2) env))))

(defun and-type-list1 (type-list env)
  (mapcan #'(lambda (type)
	      (unless (eq type t)
		(setq type (and type (fully-expand-type type env)))
		(if (and (consp type) (eq (car type) 'and))
		    (and-type-list1 (cdr type) env)
		    (list type))))
	  type-list))

(defun and-type-list (type-list &optional env)
  (let ((member-p nil)
	(member-list nil)
	(integer-p nil)
	(min '*) (max '*)
	(new-type-list nil))
    (setq type-list (and-type-list1 type-list env))
    (loop (unless type-list (return nil))
	  (let ((type (pop type-list)))
	    (unless type (return-from and-type-list nil))
	    (if (atom type)
		(if (eq type 'integer)
		    (setq integer-p t)
		    (progn
		      (pushnew type new-type-list)))
		(case (car type)
		  (eql
		   (setq member-list
			 (and (or (null member-p)
				  (member (cadr type) member-list))
			      (list (cadr type))))
		   (setq member-p t))
		  (member
		   (let ((values (copy-list (cdr type))))
		     (if member-p
			 (setq member-list (nintersection member-list
							  values))
			 (progn
			   (setq member-p t)
			   (setq member-list values)))))
		  (integer
		   (let ((emin (or (cadr type) '*))
			 (emax (or (caddr type) '*)))
		     (setq integer-p t)
		     (unless (eq emin '*)
		       (setq min (if (eq min '*)
				     emin
				     (max min emin))))
		     (unless (eq emax '*)
		       (setq max (if (eq max '*)
				     emax
				     (min max emax))))))
		  (t
		   (push type new-type-list))))))
    (setq type-list new-type-list)
    (when (and member-p integer-p)
      (setq member-list (delete-if-not #'(lambda (v)
					   (and (integerp v)
						(or (eq min '*) (<= min v))
						(or (eq max '*) (<= v max))))
				   member-list))
      (setq integer-p nil))
    (when member-p
      (when type-list
	(let ((type (if (cdr type-list)
			`(and ,@type-list)
			(car type-list))))
	  (setq member-list (delete-if-not #'(lambda (v)
					       (translator-typep v type env))
					   member-list))))
      (return-from and-type-list (when member-list `(member ,@member-list))))
    (when integer-p
      (push `(integer ,min ,max) type-list))
    (setq type-list
	  (remove-if #'(lambda (type1)
			 (some #'(lambda (type2)
				   (unless (eq type1 type2)
				     (translator-subtypep type2 type1 env)))
			       type-list))
		     type-list))
    (cond ((null type-list)
	   nil)
	  ((null (cdr type-list))
	   (car type-list))
	  (t
	   `(and ,@type-list)))))	

(defun and-ftypes (type1 type2 &optional env)
  (cond ((eq type1 'function) type2)
	((eq type2 'function) type1)
	((and (consp type1) (eq (first type1) 'function)
	      (consp type2) (eq (first type2) 'function))
	 `(function ,(and-argument-types (second type1) (second type2) env)
		    ,(and-value-types (third type1) (third type2) env)))
	(t 'function)))


;;; Still not quite right.

(defun and-argument-types (args1 args2 env &optional optional-p)
  (if (or (null args1) (null args2))
      nil
      (let ((arg1 (car args1))
	    (arg2 (car args2)))
	(if (equal arg1 arg2)
	    (cons arg1
		  (if (eq arg1 '&key)
		      (and-keyword-argument-types
		       (cdr args1) (cdr args2) env)
		      (and-argument-types
		       (cdr args1) (cdr args2) env)))
	    (cond ((eq arg1 '&rest)
		   (if (null (cddr args1))
		       (and-argument-types-with-type args2 (cadr args1) env)
		       (and-argument-types (cddr args1) arg2 env)))
		  ((eq arg2 '&rest)
		   (if (null (cddr args2))
		       (and-argument-types-with-type args1 (cadr args2) env)
		       (and-argument-types arg1 (cddr args2) env)))
		  ((or (eq arg1 '&key) (eq arg2 '&key))
		   nil) ; could fix this sometime
		  ((eq arg1 '&optional)
		   (if optional-p
		       (cons '&optional
			     (and-argument-types1 (cdr args1) args2 env))
		       (and-argument-types1 (cdr args1) args2 env t)))
		  ((eq arg2 '&optional)
		   (if optional-p
		       (cons '&optional
			     (and-argument-types1 args1 (cdr args2) env))
		       (and-argument-types1 args1 (cdr args2) env t)))
		  (t (and-argument-types1 args1 args2 env)))))))

(defun and-argument-types1 (args1 args2 env &optional optional-p)
  (let ((arg1 (car args1))
	(arg2 (car args2)))
    (cons (and-types arg1 arg2 env)
	  (and-argument-types
	   (cdr args1) (cdr args2) env optional-p))))

(defun and-keyword-argument-types (args1 args2 env)
  (let* ((allow-other-keys1 (member '&allow-other-keys args1))
	 (allow-other-keys2 (member '&allow-other-keys args2))
	 (allow-other-keys (and allow-other-keys1 allow-other-keys2)))
    (nconc (mapcan #'(lambda (arg1 &aux assoc name)
		       (when (and (consp arg1)
				  (or (setq assoc
					    (assoc (setq name (car arg1))
						   args2))
				      allow-other-keys2))
			 (list (list name
				     (and-types (cadr arg1)
						(or (cadr assoc) 't)
						env)))))
		   args1)
	   (when allow-other-keys
	     (nconc (mapcan #'(lambda (arg2)
				(when (and (consp arg2)
					   (not (assoc (car arg2) args1)))
				  (list arg2)))
			    args2)
		    '(&allow-other-keys))))))

(defun and-argument-types-with-type (args type env &aux keyp)
  (mapcar #'(lambda (arg)
	      (cond ((eq (car args) '&key)
		     (setq keyp t)
		     arg)
		    ((member (car args) '(&optional &rest &allow-other-keys))
		     arg)
		    (keyp
		     (list (car arg) (and-types (cadr arg) type env)))
		    (t
		     (and-types arg type env))))
	  args))

;;; Like and-types but treat VALUES specially.  Note that we use
;;; and-argument-types instead of and-types-list because the VALUES
;;; type specifier can contain lambda-list-keywords (it basically
;;; specifies the lambda-list of a function that could be given to
;;; MULTIPLE-VALUE-CALL).

(defun and-value-types (type1 type2 env)
  (if (and (consp type1) (eq (car type1) 'values))
      (cond ((and (consp type2) (eq (car type2) 'values))
	     (make-values-type
	      (and-argument-types (cdr type1) (cdr type2) env)))
	    ((and (consp (cdr type1)) (eq (cadr type1) '&rest))
	     (and-types (caddr type1) type2 env))
	    (t
	     (make-values-type
	      (and-argument-types (cdr type1) (list type2) env))))
      (cond ((not (and (consp type2) (eq (car type2) 'values)))
	     (and-types type1 type2 env))
	    ((and (consp (cdr type2)) (eq (cadr type2) '&rest))
	     (and-types type1 (caddr type2) env))
	    (t
	     (make-values-type
	      (and-argument-types (list type1) (cdr type2) env))))))

(defun and-types-list (list1 list2 env)
  (let ((result  nil))
    (loop
     (if (null list1)
	 (return `(,@(nreverse result) ,@list2)))
     (if (null list2)
	 (return `(,@(nreverse result) ,@list1)))
     (push (and-types (pop list1) (pop list2) env) result))))

(defun make-values-type (types)
  (if (and types (null (cdr types)))
      (car types)
      `(values ,@types)))

(defun make-unspecific-number-of-values-type (type)
  (if (and (consp type) (eq (car type) 'values))
      (if (or (memq '&rest (cdr type))
	      (memq '&key (cdr type)))
	  type
	  (append type '(&rest t)))
      `(values ,type &rest t)))

;;; Take the union of two type specifiers.
(defun or-argument-types (args1 args2 env)
  (if (null args1)
      (if (null args2)
	  nil
	  '(&rest t))
      (if (null args2)
	  '(&rest t)
	  (let ((arg1 (car args1))
		(arg2 (car args2)))
	    (if (equal arg1 arg2)
		(cons arg1 (or-argument-types
			    (cdr args1) (cdr args2) env))
		(if (or (member arg1 lambda-list-keywords)
			(member arg2 lambda-list-keywords))
		    '(&rest t)		;??
		    (cons (or-types arg1 arg2 env)
			  (or-argument-types
			   (cdr args1) (cdr args2) env))))))))

(defun or-value-types (type1 type2 &optional env)
  (if (and (consp type1) (eq (car type1) 'values))
      (cond ((and (consp type2) (eq (car type2) 'values))
	     `(values ,@(or-argument-types (cdr type1) (cdr type2) env)))
	    ((and (consp (cdr type1)) (eq (cadr type1) '&rest))
	     (or-types (caddr type1) type2 env))
	    (t
	     `(values ,@(or-argument-types (cdr type1) (list type2) env))))
      (cond ((not (and (consp type2) (eq (car type2) 'values)))
	     (or-types type1 type2 env))
	    ((and (consp (cdr type2)) (eq (cadr type2) '&rest))
	     (or-types type1 (caddr type2) env))
	    (t
	     `(values ,@(or-argument-types (list type1) (cdr type2) env))))))

(defun or-types (type1 type2 &optional env)
  (cond ((eq type1 t) t)
	((eq type2 t) t)
	((translator-subtypep type1 type2 env) type2)
	((translator-subtypep type2 type1 env) type1)
	(t `(or ,type1 ,type2))))


;;; Get rid of VALUES.

(defun single-value-type (type &optional env expanded-p)
  (cond ((and (consp type)
	      (eq (car type) 'values))
	 (if (endp (cdr type))
	     'null
	     (let ((thing (cadr type)))
	       ;; (VALUES <lambda list keyword> ...) => T
	       ;; (VALUES <type specifier> ...) => <type specifier>
	       (if (lambda-keyword-p thing) 't thing))))
	(expanded-p
	 type)
	((and (symbolp type)
	      (memq type '(t fixnum single-float double-float float)))
	 type)
	(t
	 (single-value-type (fully-expand-type type env) env t))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Support for CLOS
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Finding translator classes

#+translator-supports-clos
(progn

(defun ensure-legal-class-name (name)
  (or (and (symbolp name)
	   (not (keywordp name)))
      (error "~S is not a valid class name." name)
      ;;(error 'simple-type-error
      ;;       :datum name
      ;;       :expected-type '(and symbol (not keyword))
      ;;       :format-string "~S is not a valid class name."
      ;;       :format-arguments (list name))
      ))

(defun translator-find-class (name &optional errorp env)
  (ensure-legal-class-name name)
  (when (null env) (setf env *default-global-environment*))
  (or (defined-as-class name env)
      (when errorp (error "~S does not name a class." name))))

(defun set-translator-find-class (value name &optional errorp env)
  (declare (ignore errorp))
  (ensure-legal-class-name name)
  (cond ((null value)
	 (when (null env) (setf env *default-global-environment*))
	 (translator-environment-remprop name env 'defined-as-class)
	 nil)
	((not (type-specifier-class-p value env))
	 (error "~s is not a class object." value))
	(t
	 (setf (defined-as-class name env) value))))

)

;;; Note that this needs to be present even if the reader and writer functions
;;; are not defined (ie. :translator-supports-clos is not a feature), so that
;;; the writer function for tcl:find-class will be compiled properly.

(define-setf-method translator-find-class
        (&rest rest)
  (let ((vars (mapcar #'(lambda (value) (declare (ignore value)) (gensym))
		      rest))
	(store (gensym)))
    (values vars
	    rest
	    (list store)
	    `(set-translator-find-class ,store ,@vars)
	    `(translator-find-class ,@vars))))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Compatibility functions for typep
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun trun:bignump (object)
  (and (integerp object)
       (not (trun:fixnump object))))

(defun trun:bitp (object)
  (or (eql object 0) (eql object 1)))

(defun trun:constantly-true (&rest args)
  (declare (ignore args))
  t)

(defun trun:constantly-false (&rest args)
  (declare (ignore args))
  nil)

(defun trun:fixnump (object)
  (and (integerp object)
       (<= object most-positive-target-fixnum)
       (>= object most-negative-target-fixnum)))

(defun trun:ratiop (object)
  (and (rationalp object) (not (integerp object))))

(defun trun:sequencep (object)
  (or (listp object) (vectorp object)))


;;; When cross-compiling array constants, all arrays are effectively "simple"
;;; since the qualities that make them non-simple are not preserved.

(defun trun:simple-array-p (object)
  (arrayp object))

;;; *** Perhaps these shouldn't be here, instead being defined as part of the
;;; *** CLOS implementation?

;;;*** These two are incomplete -- in the absence of CLOS in the host Lisp,
;;;*** we can't identify objects of these types.

#+translator-supports-clos
(defun trun:standard-object-p (object)
  (or (typep object 'standard-object)
      ;; *** This actually ought to be (typep object 'generic-function), but
      ;; *** some implementations (including Lucid 4.0) don't have that type
      ;; *** specifier yet.
      (typep object 'standard-generic-function)
      ;; *** Other cases may be needed here eventually
      ))

#-translator-supports-clos
(defun trun:standard-object-p (object)
  (declare (ignore object))
  nil)

(defun trun:structure-object-p (object)
  #+translating (declare (ignore object))
  #+translating nil
  #-translating
  (progn
    #+lucid (lucid::structurep object)
    #+allegro (excl::structurep object)
    #+lispworks (lw:structurep object)
    #+(or mcl clozure) (eq 'structure (ccl::%type-of object))
    #+sbcl (eq object 'sb-alien-internals:heap-alien-info) ; what's this?
    #-(or lucid allegro lispworks mcl clozure sbcl) nil))

#+translator-supports-clos
(defun instance-typep (object class &optional env)
  ;; *** This is pretty iffy at translation time.
  ;; *** The problem is that we are using the host's class-of.
  ;; *** Maybe we need translator-class-of too?
  (values (classes-subtypep (class-of object) class env)))

#+translator-supports-clos
(defun classes-subtypep (subclass superclass env)
  (declare (ignore env))
  (let ((cpl (tclos:class-precedence-list subclass)))
    (if (null cpl)
	;; If subclass is forward-referenced-class or has forward-referenced
	;; supers, the class-precedence-list returns Nil.  Handle this as a
	;; special case, returning unknown for it.
	(values nil nil)
	(values (and (member superclass cpl :test #'eq) t)
		t))))

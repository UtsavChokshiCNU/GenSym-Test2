;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; SETF-METHODS : define a setf method for each generalized variable specified
;;;                in CLtL, 2nd ed.
;;;
;;; Author : John Gilson
;;;
;;; Copyright (c) 1990, Chestnut Software, Inc.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/setf-methods.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2006/03/14 22:03:56 $")

;;; make setf method for variables

(defun make-variable-setf-method (variable env)
  (let ((store-var
	  (make-setf-method-temp-var (sformat "~A-NEW-VALUE" variable))))
    ;; make and return setf method for a variable
    (values
      ;; temps
      nil
      ;; value forms
      nil
      ;; store variable
      (list store-var)
      ;; storing form
      `(setq ,variable ,store-var)
      ;; accessing form
      variable
      nil
      (list (variable-type variable env))
      '(t))))

;;; define the setf method for each generalized variable in CL whose update
;;; operation is a store function implemented in the run-time library
;;;
;;; see defsetf.lisp for a description of translator-defsetf

(translator-defsetf char
  :type :store-function-new-value-last
  :update-fn trun:set-char
  :new-value-type character
  :access-fn-arg-count 2
  :doc
  "The setf method for CHAR.
   The update operation is the function set-char.")

(translator-defsetf tcl:compiler-macro-function
  :type :store-function-new-value-last
  :update-fn trun:set-compiler-macro-function
  :access-fn-arg-count 1
  :doc
  "The setf method for COMPILER-MACRO-FUNCTION.
   The update operation is the function set-compiler-macro-function.")

(translator-defsetf elt
  :type :store-function-new-value-last
  :update-fn trun:set-elt
  :access-fn-arg-count 2
  :doc
  "The setf method for ELT.
   The update operation is the function set-elt.")

;;; the following two macros are used to make setf methods for fdefinition,
;;; symbol-function and setf-function

(defmacro runtime-fn-redefinition-apply-setf-method
  (&key place env access-fn update-fn fn-name-predicate place-type
	new-value-type)
  `(let ((args (cddr ,place))
	 temp)
     (setf temp (apply-macros (first args) ,env))
     (when (quote-form-p temp)
       (let* ((quoted-form (second temp))
	      (fn-name (if (,fn-name-predicate quoted-form)
			   quoted-form
			   (first quoted-form))))
	 (if (function-defined&inline-p fn-name ,env)
	     (runtime-fn-redefinition-warning
	      `(apply (function ,',access-fn) ,temp ,@(rest args))
	      fn-name)
	     (note-non-toplevel-function-definition fn-name))))
     (let ((args-temps (make-setf-method-temp-vars
			 (length (the cons args))
			 ,(sformat "APPLY-OF-~A-ARG" access-fn)))
	   (store-var (make-setf-method-temp-var
		        ,(sformat "APPLY-OF-~A-NEW-VALUE" access-fn))))
       (values
	 ;; temps
	 args-temps
	 ;; value forms
	 args
	 ;; store variable
	 (list store-var)
	 ;; storing form
	 ,(ecase place-type
	    (:l-value
	     `(make-l-value-apply-storing-form
	        ',update-fn args-temps store-var ',new-value-type 1))
	    (:store-function-new-value-last
	     `(make-store-function-new-value-last-apply-storing-form
	        ',update-fn args-temps store-var ',new-value-type 1)))
	 ;; accessing form
	 (make-non-apply-accessing-form-from-apply
	   ',access-fn args-temps ',new-value-type 1)))))

(defmacro runtime-fn-redefinition-setf-method
  (&key place env access-fn update-fn place-type new-value-type)
  `(let ((fn-name (second ,place))
	 temp)
     (setf temp (apply-macros fn-name ,env))
     (when (quote-form-p temp)
       (if (function-defined&inline-p (second temp) ,env)
	   (runtime-fn-redefinition-warning
	    `(,',access-fn ,temp)
	    (second temp))
	   (note-non-toplevel-function-definition (second temp))))
     (let ((fn-name-temp
	     (make-setf-method-temp-var ,(sformat "~A-ARG" access-fn)))
	   (store-var
	     (make-setf-method-temp-var
	       ,(sformat "~A-NEW-VALUE" access-fn))))
       (values
	 ;; temps
	 (list fn-name-temp)
	 ;; value forms
	 (list fn-name)
	 ;; store variable
	 (list store-var)
	 ;; storing form
	 ,(ecase place-type
	    (:l-value
	     `(make-l-value-storing-form
	        ',update-fn (list fn-name-temp) store-var nil nil
		',new-value-type))
	    (:store-function-new-value-last
	     `(make-store-function-new-value-last-storing-form
	        ',update-fn (list fn-name-temp) store-var nil nil
		',new-value-type)))
	 ;; accessing form
	 (make-aug-simple-defsetf-accessing-form
	   ',access-fn (list fn-name-temp) ',new-value-type)))))

;;; define the setf method for fdefinition (and apply of fdefinition)
;;;
;;; :type is :store-function-new-value-last
;;; :update-fn is trun:set-fdefinition
;;; :access-fn-arg-count is 1

(define-translator-setf-method fdefinition (accessing-form env)
  "The setf method for FDEFINITION.
   The update operation is the function set-fdefinition."
  (if (eq (first accessing-form) 'apply)
      ;; make setf method for apply of fdefinition
      (runtime-fn-redefinition-apply-setf-method
        :place accessing-form
	:env env
	:access-fn fdefinition
	:update-fn trun:set-fdefinition
	:fn-name-predicate valid-function-name-p
	:place-type :store-function-new-value-last
	:new-value-type function)
      ;; make setf method for fdefinition
      (runtime-fn-redefinition-setf-method
        :place accessing-form
	:env env
	:access-fn fdefinition
	:update-fn trun:set-fdefinition
	:place-type :store-function-new-value-last
	:new-value-type function)))

(defun quote-form-p (form)
  (and (consp form) (eq (first form) 'quote)))

(defun function-defined&inline-p (name &optional env)
  (multiple-value-bind (type localp decl-info)
      (translator-function-information name env)
    (declare (ignore localp))
    (and type (not (eq (rest (assoc 'inline decl-info)) 'notinline)))))

(defun runtime-fn-redefinition-warning (place fn-name)
  (warn
    "SETF of ~S~@
     encountered.~@
     The function ~S has not been declared NOTINLINE and~@
     calls to the function ~:*~S may have been generated inline."
    place
    fn-name))

(translator-defsetf fill-pointer
  :type :store-function-new-value-last
  :update-fn trun:set-fill-pointer
  :new-value-type fixnum
  :access-fn-arg-count 1
  :doc
  "The setf method for FILL-POINTER.
   The update operation is the function set-fill-pointer.")

(translator-defsetf get
  :type :store-function-new-value-last
  :update-fn trun:set-get
  :access-fn-arg-count 3
  :ignore-place-default-value-p t
  :doc
  "The setf method for GET.
   The update operation is the function set-get.")

(translator-defsetf gethash
  :type :store-function-new-value-last
  :update-fn trun:set-gethash
  :access-fn-arg-count 3
  :ignore-place-default-value-p t
  :doc
  "The setf method for GETHASH.
   The update operation is the function set-gethash.")

(translator-defsetf logical-pathname-translations
  :type :store-function-new-value-last
  :update-fn trun:set-logical-pathname-translations
  :access-fn-arg-count 1
  :new-value-type list
  :doc
  "The setf method for LOGICAL-PATHNAME-TRANSLATIONS.
   The update operation is the function set-logical-pathname-translations.")

(translator-defsetf tcl:macro-function
  :type :store-function-new-value-last
  :update-fn trun:set-macro-function
  :access-fn-arg-count 1
  :doc
  "The setf method for MACRO-FUNCTION.
   The update operation is the function set-macro-function.")

(translator-defsetf readtable-case
  :type :store-function-new-value-last
  :update-fn trun:set-readtable-case
  :new-value-type keyword
  :access-fn-arg-count 1
  :doc
  "The setf method for READTABLE-CASE.
   The update operation is the function set-readtable-case.")

(translator-defsetf row-major-aref
  :type :store-function-new-value-last
  :update-fn trun:set-row-major-aref
  :access-fn-arg-count 2
  :doc
  "The setf method for ROW-MAJOR-AREF.
   The update operation is the function set-row-major-aref.")

(translator-defsetf schar
  :type :store-function-new-value-last
  :update-fn trun:set-schar
  :new-value-type character
  :access-fn-arg-count 2
  :doc
  "The setf method for SCHAR.
   The update operation is the function set-schar.")

(translator-defsetf subseq
  :type :store-function-new-value-last
  :update-fn trun:set-subseq
  :new-value-type sequence
  :access-fn-arg-count 3
  :doc
  "The setf method for SUBSEQ.
   The update operation is the function set-subseq.")

(translator-defsetf symbol-value
  :type :store-function-new-value-last
  :update-fn set
  :doc
  "The setf method for SYMBOL-VALUE.
   The update operation is the function set.")

;;; define the setf method for each generalized variable in CL that is an
;;; accessor-call l-value
;;;
;;; accessor calls are not side-effecting as long as the argument-expressions
;;; are not side-effecting
;;;
;;; structure access functions are also l-values whose setf methods are defined
;;; this way

(translator-defsetf caaaar
  :type :l-value
  :update-fn trun:%set-caaaar
  :doc
  "The setf method for CAAAAR.
   This is a l-value.")

(translator-defsetf caaadr
  :type :l-value
  :update-fn trun:%set-caaadr
  :doc
  "The setf method for CAAADR.
   This is a l-value.")

(translator-defsetf caaar
  :type :l-value
  :update-fn trun:%set-caaar
  :doc
  "The setf method for CAAAR.
   This is a l-value.")

(translator-defsetf caadar
  :type :l-value
  :update-fn trun:%set-caadar
  :doc
  "The setf method for CAADAR.
   This is a l-value.")

(translator-defsetf caaddr
  :type :l-value
  :update-fn trun:%set-caaddr
  :doc
  "The setf method for CAADDR.
   This is a l-value.")

(translator-defsetf caadr
  :type :l-value
  :update-fn trun:%set-caadr
  :doc
  "The setf method for CAADR.
   This is a l-value.")

(translator-defsetf caar
  :type :l-value
  :update-fn trun:%set-caar
  :doc
  "The setf method for CAAR.
   This is a l-value.")

(translator-defsetf cadaar
  :type :l-value
  :update-fn trun:%set-cadaar
  :doc
  "The setf method for CADAAR.
   This is a l-value.")

(translator-defsetf cadadr
  :type :l-value
  :update-fn trun:%set-cadadr
  :doc
  "The setf method for CADADR.
   This is a l-value.")

(translator-defsetf cadar
  :type :l-value
  :update-fn trun:%set-cadar
  :doc
  "The setf method for CADAR.
   This is a l-value.")

(translator-defsetf caddar
  :type :l-value
  :update-fn trun:%set-caddar
  :doc
  "The setf method for CADDAR.
   This is a l-value.")

(translator-defsetf cadddr
  :type :l-value
  :update-fn trun:%set-cadddr
  :doc
  "The setf method for CADDDR.
   This is a l-value.")

(translator-defsetf caddr
  :type :l-value
  :update-fn trun:%set-caddr
  :doc
  "The setf method for CADDR.
   This is a l-value.")

(translator-defsetf cadr
  :type :l-value
  :update-fn trun:%set-cadr
  :doc
  "The setf method for CADR.
   This is a l-value.")

(translator-defsetf car
  :type :l-value
  :update-fn trun:%set-car
  :doc
  "The setf method for CAR.
   This is a l-value.")

(translator-defsetf cdaaar
  :type :l-value
  :update-fn trun:%set-cdaaar
  :doc
  "The setf method for CDAAAR.
   This is a l-value.")

(translator-defsetf cdaadr
  :type :l-value
  :update-fn trun:%set-cdaadr
  :doc
  "The setf method for CDAADR.
   This is a l-value.")

(translator-defsetf cdaar
  :type :l-value
  :update-fn trun:%set-cdaar
  :doc
  "The setf method for CDAAR.
   This is a l-value.")

(translator-defsetf cdadar
  :type :l-value
  :update-fn trun:%set-cdadar
  :doc
  "The setf method for CDADAR.
   This is a l-value.")

(translator-defsetf cdaddr
  :type :l-value
  :update-fn trun:%set-cdaddr
  :doc
  "The setf method for CDADDR.
   This is a l-value.")

(translator-defsetf cdadr
  :type :l-value
  :update-fn trun:%set-cdadr
  :doc
  "The setf method for CDADR.
   This is a l-value.")

(translator-defsetf cdar
  :type :l-value
  :update-fn trun:%set-cdar
  :doc
  "The setf method for CDAR.
   This is a l-value.")

(translator-defsetf cddaar
  :type :l-value
  :update-fn trun:%set-cddaar
  :doc
  "The setf method for CDDAAR.
   This is a l-value.")

(translator-defsetf cddadr
  :type :l-value
  :update-fn trun:%set-cddadr
  :doc
  "The setf method for CDDADR.
   This is a l-value.")

(translator-defsetf cddar
  :type :l-value
  :update-fn trun:%set-cddar
  :doc
  "The setf method for CDDAR.
   This is a l-value.")

(translator-defsetf cdddar
  :type :l-value
  :update-fn trun:%set-cdddar
  :doc
  "The setf method for CDDDAR.
   This is a l-value.")

(translator-defsetf cddddr
  :type :l-value
  :update-fn trun:%set-cddddr
  :doc
  "The setf method for CDDDDR.
   This is a l-value.")

(translator-defsetf cdddr
  :type :l-value
  :update-fn trun:%set-cdddr
  :doc
  "The setf method for CDDDR.
   This is a l-value.")

(translator-defsetf cddr
  :type :l-value
  :update-fn trun:%set-cddr
  :doc
  "The setf method for CDDR.
   This is a l-value.")

(translator-defsetf cdr
  :type :l-value
  :update-fn trun:%set-cdr
  :doc
  "The setf method for CDR.
   This is a l-value.")

(translator-defsetf eighth
  :type :l-value
  :update-fn trun:%set-eighth
  :doc
  "The setf method for EIGHTH.
   This is a l-value.")

(translator-defsetf fifth
  :type :l-value
  :update-fn trun:%set-fifth
  :doc
  "The setf method for FIFTH.
   This is a l-value.")

(translator-defsetf first
  :type :l-value
  :update-fn trun:%set-first
  :doc
  "The setf method for FIRST.
   This is a l-value.")

(translator-defsetf fourth
  :type :l-value
  :update-fn trun:%set-fourth
  :doc
  "The setf method for FOURTH.
   This is a l-value.")

(translator-defsetf ninth
  :type :l-value
  :update-fn trun:%set-ninth
  :doc
  "The setf method for NINTH.
   This is a l-value.")

(translator-defsetf nth
  :type :l-value
  :update-fn trun:%set-nth
  :access-fn-arg-count 2
  :doc
  "The setf method for NTH.
   This is a l-value.")

(translator-defsetf rest
  :type :l-value
  :update-fn trun:%set-rest
  :doc
  "The setf method for REST.
   This is a l-value.")

(translator-defsetf second
  :type :l-value
  :update-fn trun:%set-second
  :doc
  "The setf method for SECOND.
   This is a l-value.")

(translator-defsetf seventh
  :type :l-value
  :update-fn trun:%set-seventh
  :doc
  "The setf method for SEVENTH.
   This is a l-value.")

(translator-defsetf sixth
  :type :l-value
  :update-fn trun:%set-sixth
  :doc
  "The setf method for SIXTH.
   This is a l-value.")

(translator-defsetf svref
  :type :l-value
  :update-fn trun:%set-svref
  :access-fn-arg-count 2
  :doc
  "The setf method for SVREF.
   This is a l-value.")

(define-translator-setf-method symbol-function (accessing-form env)
  "The setf method for SYMBOL-FUNCTION.
   This is a l-value."
  (if (eq (first accessing-form) 'apply)
      ;; make setf method for apply of symbol-function
      (runtime-fn-redefinition-apply-setf-method
        :place accessing-form
	:env env
	:access-fn symbol-function
	:update-fn trun:%set-symbol-function
	:fn-name-predicate symbolp
	:place-type :store-function-new-value-last
	:new-value-type function)
      ;; make setf method for symbol-function
      (runtime-fn-redefinition-setf-method
        :place accessing-form
	:env env
	:access-fn symbol-function
	:update-fn trun:%set-symbol-function
	:place-type :store-function-new-value-last
	:new-value-type function)))

(translator-defsetf symbol-plist
  :type :store-function-new-value-last
  :update-fn trun:%set-symbol-plist
  :access-fn-arg-count 1
  :doc
  "The setf method for SYMBOL-PLIST.
   This is a l-value.")

(translator-defsetf tenth
  :type :l-value
  :update-fn trun:%set-tenth
  :doc
  "The setf method for TENTH.
   This is a l-value.")

(translator-defsetf third
  :type :l-value
  :update-fn trun:%set-third
  :doc
  "The setf method for THIRD.
   This is a l-value.")

;;; define the setf method for THE
;;;
;;; can handle a place with multiple store variables
;;;
;;; since the is not a function, it can't be used with apply and an error will
;;; be signalled

(define-translator-setf-method the (accessing-form env)
  "The setf method for THE."
  (if (eq (first accessing-form) 'apply)
      (unknown-apply-of-place-error 'the)
      (destructuring-bind (type form &aux new-store-vars) (rest accessing-form)
	(multiple-value-bind
	  (temps value-forms store-vars storing-form accessing-form
	   temps-types store-vars-types)
	    (translator-get-setf-method-multiple-value form env)
	  (setf new-store-vars (copy-setf-method-temp-vars store-vars))
	  ;; make and return setf method for the
	  (values
            ;; temps
	    temps
	    ;; value forms
	    value-forms
	    ;; store variables
	    new-store-vars
	    ;; storing form
	    `(the ,type
	       (symbol-macrolet
		 ,(mapcar #'list
			  store-vars
			  (make-THE-forms new-store-vars type))
		 ,storing-form))
	    ;; accessing form
	    `(the ,type ,accessing-form)
	    temps-types
	    store-vars-types
	    (if (and (consp type)
		     (eq (car type) 'values))
		(let ((key-seen-p nil))
		  (mapcan #'(lambda (type)
			      (if (or key-seen-p
				      (member type lambda-list-keywords))
				  (progn
				    (setq key-seen-p t)
				    nil)
				  (list type)))
			  (cdr type)))
		(list type)))))))

(defun make-THE-forms
  (vars type-spec &aux the-forms list-of-types (context :required)
	               rest-type-list keyword-key-p symbol-key-p
		       key-value-types)
  (if (and (consp type-spec) (eq (first type-spec) 'values))
      (setf list-of-types (rest type-spec))
      (setf list-of-types (list type-spec)))
  (dolist (type list-of-types)
    (case type
      ((&optional &rest &key) (setf context type))
      (otherwise
        (case context
	  (:required (if vars
			 (push `(the ,type ,(pop vars)) the-forms)
		         (return)))
	  (&optional (if vars
			 (push `(the (or null ,type) ,(pop vars)) the-forms)
		         (return)))
	  (&rest (push type rest-type-list))
	  (&key (typecase (first type)
		  (keyword (setf keyword-key-p t))
		  (symbol (setf symbol-key-p t))
		  (t (error
		       "A keyword was encountered that isn't a symbol : ~S"
		       (first type))))
		(push (second type) key-value-types))))))
  (nreconc
    the-forms
    (&rest-and-&key-types->the-forms
      vars rest-type-list keyword-key-p symbol-key-p key-value-types)))

(defun &rest-and-&key-types->the-forms
  (vars rest-type-list keyword-key-p symbol-key-p key-value-types)
  (cond ((null vars) nil)
	(key-value-types
	  (let ((key-arg-types
		  (make-key-arg-types
		    keyword-key-p symbol-key-p key-value-types rest-type-list))
		(the-forms nil))
	    (dolist (key-arg-type key-arg-types (nreverse the-forms))
	      (if vars
		  (push `(the ,key-arg-type ,(pop vars)) the-forms)
		  (return (nreverse the-forms))))))
	(rest-type-list
	  (mapcar #'(lambda (var)
		      `(the (or null ,@rest-type-list) ,var))
		  vars))
	(t (mapcar #'(lambda (var)
		       `(the null ,var))
		   vars))))

(defun make-key-arg-types
  (keyword-key-p symbol-key-p key-value-types rest-type-list)
  (if key-value-types
      (let ((new-key-type
	      (cond ((and keyword-key-p symbol-key-p)
		     `(or null (and (or keyword symbol) ,@rest-type-list)))
		    (keyword-key-p
		     `(or null (and keyword ,@rest-type-list)))
		    (symbol-key-p
		     `(or null (and symbol ,@rest-type-list)))))
	    (new-key-value-type
	      `(or null (and ,@rest-type-list (or ,@key-value-types))))
	    (key-arg-types nil))
	(dotimes (counter (length (the cons key-value-types))
			  (nreverse key-arg-types))
	  (push new-key-type key-arg-types)
	  (push new-key-value-type key-arg-types)))
      nil))

;;; define the setf method for APPLY
;;;
;;; can handle a place with multiple store variables
;;;
;;; apply of apply, that is
;;; (apply #'apply ... #'apply #'<non-apply-place-name> <arg1> ... <argn>)
;;; is a place

(define-translator-setf-method apply (accessing-form env &aux temp1 temp2)
  "The setf method for APPLY."
  (multiple-value-bind (apply-arg place-name)
      (handle-multiple-apply-place (rest accessing-form) env)
    (let ((new-apply-form `(apply (function ,place-name) ,@apply-arg))
	  (expander (when (setf temp1
				(get-setf-method-expander place-name env))
		      (unless (eq (setf temp2 (translator-function-information
					        place-name env))
				  :function)
			(apply-functional-arg-warning place-name temp2))
		      temp1)))
      (if expander
	  (funcall expander new-apply-form env)
	  (if (symbolp place-name)
	      (make-setf-function-setf-method-for-apply new-apply-form env)
	      (error "The form ~S is not a known place and~@
                      a setf-function setf method can't be created."
		     new-apply-form))))))

;;; (apply #'apply ... #'apply #'<non-apply-place-name> <arg1> ... <argn>) is
;;; transformed into
;;; (apply #'<non-apply-place-name>
;;;        (apply #'list* ... (apply #'list* <arg1> ... <argn>)))
;;; where the number of apply-of-#'list* forms is equal to the number of
;;; #'apply forms in the original form
;;;
;;; the functional argument(s) to apply must be a FUNCTION form or a macro that
;;; expands into a FUNCTION form

(defun handle-multiple-apply-place (apply-args &optional env)
  ;; two values are returned :
  ;; 1. a list of the apply args that will appear after the first apply arg in
  ;;    the transformed apply form
  ;; 2. the name of the place specified with apply
  (let ((apply-arg (translator-macroexpand (first apply-args) env)))
    (unless (and (consp apply-arg) (eq (first apply-arg) 'function))
      (error "The argument ~S in the APPLY place must be of the form~@
              (FUNCTION name) or a macro that expands into this."
	     apply-arg))
    (let ((fn-name (second apply-arg)))
      (if (eq fn-name 'apply)
	  (multiple-value-bind (arg place-name)
	      (handle-multiple-apply-place (rest apply-args) env)
	    (values
	      `((apply (function list*) ,@arg))
	      place-name))
	  (values
	    (rest apply-args)
	    fn-name)))))

(defun apply-functional-arg-warning (name name-type)
  (warn "The first argument to the place APPLY, (FUNCTION ~S),~@
         refers to ~A."
	name
	(case name-type
	  (:macro "a macro")
	  (:special-form "a special form")
	  ((nil) "an undefined function"))))

;;; define the setf method for each place in CL that has an argument that is in
;;; turn a place (getf, char-bit, ldb and mask-field)

;;; define the setf method for GETF
;;;
;;; use of this place with apply is not recognized as a place and will signal
;;; an error

(define-translator-setf-method getf (accessing-form env)
  "The setf method for GETF."
  (if (eq (first accessing-form) 'apply)
      (unknown-apply-of-place-error 'getf)
      (destructuring-bind (place name &optional default) (rest accessing-form)
	(make-getf-setf-method place name default env))))

;;; define the setf method for CHAR-BIT
;;;
;;; X3J13 eliminated CHAR-BIT and SET-CHAR-BIT
;;;
;;; use of this place with apply is not recognized as a place and will signal
;;; an error

(define-translator-setf-method char-bit (accessing-form env)
  "The setf method for CHAR-BIT."
  (if (eq (first accessing-form) 'apply)
      (unknown-apply-of-place-error 'char-bit)
      (destructuring-bind (place name) (rest accessing-form)
        (make-char-bit-setf-method place name env))))

(defun make-getf-setf-method (place name default env)
  (make-getf/char-bit-setf-method 'getf 'trun:set-getf env place name default))

(defun make-char-bit-setf-method (place name env)
  (make-getf/char-bit-setf-method 'char-bit 'set-char-bit env place name))

(defun make-getf/char-bit-setf-method
  (access-fn update-fn env place &rest args)
  (multiple-value-bind
	(temps value-forms store-vars storing-form accessing-form
	 temps-types store-vars-types store-values-types)
      (translator-get-setf-method-multiple-value place env)
    (let* ((new-temps (make-setf-method-temp-vars
		        (length (the cons args))
			(sformat "~A-ARG" access-fn)))
	   (name-temp (first new-temps))
	   (default-temp (second new-temps))
	   (store-var (make-setf-method-temp-var
		        (sformat "~A-NEW-VALUE" access-fn))))
      ;; make and return setf method for getf/char-bit
      (values
        ;; temps
        (append temps new-temps)
	;; value forms
	(append value-forms args)
	;; store variable
	(list store-var)
	;; storing form
	;; if getf then need to include a void reference in the storing form
        ;; to the default-value temp to avoid an unreferenced-binding warning
	;; during translation
	(make-update-form
	  store-vars store-vars-types store-values-types
	  `(,update-fn ,accessing-form ,name-temp ,store-var)
	  `(progn ,default-temp ,storing-form ,store-var)
	  env)
	;; accessing form
	`(,access-fn ,accessing-form ,@new-temps)
	temps-types
	nil))))

;;; define the setf method for LDB
;;;
;;; use of this place with apply is not recognized as a place and will signal
;;; an error

(define-translator-setf-method ldb (accessing-form env)
  "The setf method for LDB."
  (if (eq (first accessing-form) 'apply)
      (unknown-apply-of-place-error 'ldb)
      (destructuring-bind (bytespec place) (rest accessing-form)
        (make-ldb-setf-method bytespec place env))))

;;; define the setf method for MASK-FIELD
;;;
;;; use of this place with apply is not recognized as a place and will signal
;;; an error

(define-translator-setf-method mask-field (accessing-form env)
  "The setf method for MASK-FIELD."
  (if (eq (first accessing-form) 'apply)
      (unknown-apply-of-place-error 'mask-field)
      (destructuring-bind (bytespec place) (rest accessing-form)
        (make-mask-field-setf-method bytespec place env))))

(defun make-ldb-setf-method (bytespec place env)
  (make-ldb/mask-field-setf-method 'ldb 'dpb bytespec place env))

(defun make-mask-field-setf-method (bytespec place env)
  (make-ldb/mask-field-setf-method
    'mask-field 'deposit-field bytespec place env))

(defun make-ldb/mask-field-setf-method (access-fn update-fn bytespec place env)
  (multiple-value-bind
    (temps value-forms store-vars storing-form accessing-form
	   store-vars-types store-values-types)
      (translator-get-setf-method-multiple-value place env)
    (let ((bytespec-temp
	    (make-setf-method-temp-var (sformat "~A-ARG" access-fn)))
	  (store-var (make-setf-method-temp-var
		       (sformat "~A-NEW-VALUE" access-fn))))
      ;; make and return setf method for ldb/mask-field
      (values
        ;; temps
        (cons bytespec-temp temps)
	;; value forms
        (cons bytespec value-forms)
	;; store variable
	(list store-var)
	;; storing form
	(make-update-form
	  store-vars store-vars-types store-values-types
	  `(,update-fn ,store-var ,bytespec-temp ,accessing-form)
	  `(progn ,storing-form ,store-var)
	  env)
	;; accessing form
	`(the integer (,access-fn ,bytespec-temp ,accessing-form))))))

;;; make a setf method for a place (or apply of a place) whose storing form is
;;; a call to a setf function, i.e., a place named f whose update operation is
;;; a call to a function named (setf f)
;;;
;;; this setf method can be created regardless of whether either f or (setf f)
;;; is defined as a function locally, globally, or at all

(defun make-setf-function-setf-method-for-apply (access-form env &aux temp)
  ;; make setf method for apply of a place whose storing form is a call to a
  ;; setf function
  ;; if the place (the functional argument to APPLY) is defined and is not a
  ;; function, then a warning is generated
  (let ((name (second (second access-form)))
	(apply-args (cddr access-form)))
    (unless (or (eq (setf temp (translator-function-information name env)) nil)
		(eq temp :function))
      (apply-functional-arg-warning name temp))
    (let ((temps (make-setf-method-temp-vars
		   (length (the cons apply-args))
		   (sformat "APPLY-OF-~A-ARG" name)))
	  (store-var (make-setf-method-temp-var
		       (sformat "APPLY-OF-~A-NEW-VALUE" name))))
      (multiple-value-bind (actual-temps actual-apply-args temps&apply-args)
          (remove-bindings-if-constantp temps apply-args :env env)
	(values
	  ;; temps
	  actual-temps
	  ;; value forms
	  actual-apply-args
	  ;; store variable
	  (list store-var)
	  ;; storing form
	  `(apply (function (setf ,name)) ,store-var ,@temps&apply-args)
	  ;; accessing form
	  `(apply (function ,name) ,@temps&apply-args))))))

(defun make-setf-function-setf-method (access-form env)
  ;; make setf method for a place whose storing form is a call to a setf
  ;; function
  (let* ((name (first access-form))
	 (value-forms (rest access-form))
	 (temps (make-setf-method-temp-vars
		  (length (the list value-forms))
		  (sformat "~A-ARG" name)))
	 (store-var (make-setf-method-temp-var
		      (sformat "~A-NEW-VALUE" name))))
    (multiple-value-bind (actual-temps actual-value-forms temps&value-forms)
        (remove-bindings-if-constantp temps value-forms :env env)
      (values
        ;; temps
        actual-temps
	;; value forms
	actual-value-forms
	;; store variable
	(list store-var)
	;; storing form
	`(funcall (function (setf ,name)) ,store-var ,@temps&value-forms)
	;; accessing form
	`(,name ,@temps&value-forms)))))

;;; define the setf method for VALUES
;;;
;;; extension to CLtL, 2nd edition and made a proposal to X3J13
;;;
;;; this is a place whose setf method can have zero, one, or multiple store
;;; variables
;;;
;;; use of this place with apply is not recognized as a place and will signal
;;; an error

;;; points of note :
;;;
;;; all the subforms of the all the places to values are evaluated first, from
;;; left to right, and then the new-value form is evaluated
;;;
;;; the new-value form supplies one value, at most, to each subplace of values,
;;; however, places with more than one store variable can be specified with
;;; the extra store variables of a place bound to nil and a subplace with no
;;; store variables can be specified with a store variable generated for it by
;;; the values setf method
;;;
;;; the value(s), if any, returned by the storing form of values are the
;;; values of all the "used" store variables, i.e, the value of the first
;;; store variable of each subplace's setf method

(define-translator-setf-method values (accessing-form env)
  "The setf method for VALUES.
   This is an extension to CLtL, 2nd ed."
  (if (eq (first accessing-form) 'apply)
      (unknown-apply-of-place-error 'values)
      (let ((places (rest accessing-form))
	    (temps nil)
	    (value-forms nil)
	    (used-store-vars nil)
	    (excess-store-vars nil)
	    (all-store-vars nil)
	    (num-of-store-vars-to-make 0)
	    (storing-forms nil)
	    (accessing-forms nil))
	(dolist (place places
		       (progn
			 (setf temps (nreverse temps)
			       value-forms (nreverse value-forms)
			       storing-forms (nreverse storing-forms)
			       accessing-forms (nreverse accessing-forms))
			 (let ((gen-store-vars
				 (nreverse
				   (make-setf-method-temp-vars
				     num-of-store-vars-to-make
				     "VALUES-NEW-VALUE"))))
			   (dolist (store-vars-list all-store-vars)
			     (if store-vars-list
				 (progn
				   (push (first store-vars-list)
					 used-store-vars)
				   (setf excess-store-vars
					 (nconc (rest store-vars-list)
						excess-store-vars)))
			         (push (pop gen-store-vars)
				       used-store-vars))))))
	  (multiple-value-bind (place-temps place-value-forms
				place-store-vars place-storing-form
				place-accessing-form)
	      (translator-get-setf-method-multiple-value place env)
	    (mapc #'(lambda (place-temp place-value-form)
		      (push place-temp temps)
		      (push place-value-form value-forms))
		  place-temps place-value-forms)
	    (push place-store-vars all-store-vars)
	    (unless place-store-vars (incf num-of-store-vars-to-make))
	    (push place-storing-form storing-forms)
	    (push place-accessing-form accessing-forms)))
	;; make and return setf method for values
	(values
	  ;; temps
	  temps
	  ;; value forms
	  value-forms
	  ;; store variables
	  used-store-vars
	  ;; storing form
	  `(let ,excess-store-vars
	     ,@storing-forms
	     (values ,@used-store-vars))
	  ;; accessing form
	  `(values ,@accessing-forms)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Implementation specific generalized variables
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Define the setf method for each implementation-specific generalized
;;; variable whose update operation is a store function

(define-translator-setf-method trun:setf-function (accessing-form env)
  "The setf method for SETF-FUNCTION.
   The update operation is the function set-setf-function."
  (if (eq (first accessing-form) 'apply)
      ;; make setf method for apply of setf-function
      (runtime-fn-redefinition-apply-setf-method
        :place accessing-form
	:env env
	:access-fn trun:setf-function
	:update-fn trun:set-setf-function
	:fn-name-predicate setf-function-name-p
	:place-type :store-function-new-value-last
	:new-value-type function)
      ;; make setf method for fdefinition
      (runtime-fn-redefinition-setf-method
        :place accessing-form
	:env env
	:access-fn trun:setf-function
	:update-fn trun:set-setf-function
	:place-type :store-function-new-value-last
	:new-value-type function)))

(translator-defsetf tx:foreign-pointer-address
  :type :store-function-new-value-last
  :update-fn tx:set-foreign-pointer-address
  :new-value-type (unsigned-byte 32)
  :access-fn-arg-count 1
  :doc
  "The setf method for tx:foreign-pointer-address.
   The update operation is the function tx:set-foreign-pointer-address.")

(translator-defsetf tx:foreign-pointer-type
  :type :store-function-new-value-last
  :update-fn tx:set-foreign-pointer-type
  :new-value-type t
  :access-fn-arg-count 1
  :doc
  "The setf method for tx:foreign-pointer-type.
   The update operation is the function tx:set-foreign-pointer-type.")

(translator-defsetf tx:foreign-string-value
  :type :store-function-new-value-last
  :update-fn tx:set-foreign-string-value
  :new-value-type t
  :access-fn-arg-count 1
  :doc
  "The setf method for tx:foreign-string-value.
   The update operation is the function tx:set-foreign-string-value")

(translator-defsetf tx:foreign-value
  :type :store-function-new-value-last
  :update-fn tx:set-foreign-value
  :new-value-type t
  :access-fn-arg-count 1
  :doc
  "The setf method for tx:foreign-value.
   The update operation is the function tx:set-foreign-value")

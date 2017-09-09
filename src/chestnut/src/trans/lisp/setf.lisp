;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; SETF -- handle SETF, PSETF, SHIFTF, and ROTATEF
;;;         file also contains TRANSLATOR-GET-SETF-METHOD and
;;;         TRANSLATOR-GET-SETF-METHOD-MULTIPLE-VALUE
;;;
;;; Author : John Gilson
;;;
;;; Copyright (c) 1990, Chestnut Software, Inc.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/setf.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:11 $")

;;; SETF
;;;
;;; handles places with setf methods that have multiple store variables

(define-translator-macro setf (&environment env &rest places&new-values)
  (cond ((null places&new-values) nil)
	((oddp (length (the cons places&new-values)))
	 (error "Odd-length argument list to SETF : ~S" places&new-values))
	(t
	  (setf-aux places&new-values env))))

(defun setf-aux (places&new-values env)
  (labels ((collect-forms (places&new-values env)
	     (when places&new-values
	       (cons (make-form (pop places&new-values)
				(pop places&new-values)
				env)
		     (collect-forms places&new-values env))))
	   (make-form (place value env)
	     (if (symbolp place)
		 ;; Always defer symbol-macro processing to setq.
		 `(setq ,place ,value)
		 (let* ((place-name (and (consp place) (car place)))
			(update-fn (and place-name
					(symbolp place-name)
					(not (local-functional-def-p place-name env))
					(simple-setf-update-function place-name))))
		   (if update-fn
		       `(,update-fn ,@(cdr place) ,value)
		       (multiple-value-bind (temps values stores setter getter
						   temps-types
						   stores-types store-values-types)
			   (translator-get-setf-method-multiple-value place env)
			 (declare (ignore getter))
			 (let ((declarations
				(make-type-declarations temps temps-types)))
			   `(let* ,(mapcar #'list temps values)
			      ,@(when declarations `((declare ,declarations)))
			      ,(make-update-form stores stores-types
						 store-values-types
						 value setter env)))))))))
    `(progn ,@(collect-forms places&new-values env))))

;;; PSETF
;;;
;;; handles places with setf methods that have multiple store variables

(define-translator-macro psetf (&environment env &rest places&new-values)
  (cond ((null places&new-values) nil)
	((oddp (length (the cons places&new-values)))
	 (error "Odd-length argument list to PSETF : ~S" places&new-values))
	((transform-psetf-to-psetq-p places&new-values env)
	 `(psetq ,@places&new-values))
	(t
	  (psetf-aux places&new-values env))))

(defun transform-psetf-to-psetq-p (places&new-values env)
  (labels ((symbol-place-p (place env)
	     (when (symbolp place)
	       (multiple-value-bind (expanded macrop)
		   (translator-macroexpand-1 place env)
		 (or (not macrop)
		     (and (symbolp expanded)
			  (symbol-place-p expanded env)))))))
    (do ((tail places&new-values (cddr tail)))
	((endp tail) t)
      (or (symbol-place-p (car tail) env)
	  (return nil)))))

(defun psetf-aux (places&new-values env
				    &optional body
				    &aux (place (first places&new-values))
				         (new-value
					   (second places&new-values)))
  (if places&new-values
      (multiple-value-bind
	    (temps value-forms store-vars storing-form accessing-form
	     temps-types store-vars-types store-values-types)
	  (translator-get-setf-method-multiple-value place env)
	(declare (ignore accessing-form))
	(let ((declarations (make-type-declarations temps temps-types)))
	  `(let* ,(mapcar #'list temps value-forms)
	     ,@(when declarations `((declare ,declarations)))
	     ,(make-update-form
	       store-vars store-vars-types store-values-types
	       new-value
	       (psetf-aux (cddr places&new-values)
			  env
			  (cons storing-form body))
	       env))))
      `(progn ,@(nreverse body) nil)))

;;; SHIFTF
;;;
;;; shiftf does the following :
;;; 1. for each place from left to right, all subforms of that place are
;;;    evaluated from left to right and then the value of the place is
;;;    accessed
;;; 2. the new-value form is evaluated
;;; 3. the assignments are done
;;; 4. the old value(s) of the first place is(are) returned
;;;
;;; places with setf methods that have multiple store variables are handled
;;;
;;; the number of values returned by shiftf, i.e. the number of values
;;; returned by the first place, is equal to the number of store variables
;;; specified in that place's setf method

(define-translator-macro shiftf (&environment env &rest args)
  (when (or (null args) (null (rest args)))
    (error "Length of SHIFTF argument list must be at least two : ~S"
	   args))
  (shiftf-aux args env))

(defun shiftf-aux (args env &optional (first-place-p t)
			store-vars-of-preceding-place
			store-vars-types-of-preceding-place
			store-values-types-of-preceding-place
			first-place-old-values
			storing-forms
			&aux (arg (first args)))
  (if (rest args)
      (multiple-value-bind (temps value-forms store-vars storing-form
				  accessing-form temps-types
				  store-vars-types store-values-types)
	  (translator-get-setf-method-multiple-value arg env)
	(when first-place-p
	  (setf first-place-old-values
		(setf store-vars-of-preceding-place
		      (make-temp-vars
		       (length (the cons store-vars))
		       (multiple-value-bind (name apply-used-p)
			   (place-name accessing-form)
			 (if apply-used-p
			     (sformat "APPLY-OF-~A-OLD-VALUE" name)
			     (sformat "~A-OLD-VALUE" name)))))))
	(let ((declarations (make-type-declarations temps temps-types)))
	  `(let* ,(mapcar #'list temps value-forms)
	     ,@(when declarations `((declare ,declarations)))
	     ,(make-update-form store-vars-of-preceding-place
				store-vars-types-of-preceding-place
				store-values-types-of-preceding-place
				accessing-form
				(shiftf-aux (rest args)
					    env
					    nil
					    store-vars store-vars-types
					    store-values-types
					    first-place-old-values
					    (cons storing-form storing-forms))
				env))))
      (make-update-form
       store-vars-of-preceding-place store-vars-types-of-preceding-place
       store-values-types-of-preceding-place
       arg
       `(progn
	  ,@(nreverse storing-forms)
	  (values ,@first-place-old-values))
       env)))

;;; ROTATEF
;;;
;;; rotatef does the following :
;;; 1. for each place from left to right, all subforms of that place are
;;;    evaluated from left to right and then the value of the place is
;;;    accessed
;;; 2. the assignments are done
;;; 3. nil is returned
;;;
;;; handles places with setf methods that have multiple store variables

(define-translator-macro rotatef (&environment env &rest places)
  (if places
      (if (rest places)
	  (rotatef-aux places env)
	  `(progn ,(first places) nil))
      nil))

(defun rotatef-aux (places env &optional (first-place-p t)
			   store-vars-of-preceding-place
			   store-vars-types-of-preceding-place
			   store-values-types-of-preceding-place
			   storing-forms
			   &aux (place (first places)))
  (multiple-value-bind (temps value-forms store-vars storing-form
			      accessing-form temps-types
			      store-vars-types store-values-types)
      (translator-get-setf-method-multiple-value place env)
    (cond (first-place-p
	   (multiple-value-bind (rest-of-expansion store-vars-of-last-place
				 store-vars-types-of-last-place
				 store-values-types-of-last-place)
	       (rotatef-aux
		(rest places) env nil
		store-vars store-vars-types store-values-types
		(cons storing-form storing-forms))
	     (let ((declarations (make-type-declarations temps temps-types)))
	       `(let* ,(mapcar #'list temps value-forms)
		  ,@(when declarations `((declare ,declarations)))
		  ,(make-update-form store-vars-of-last-place
				     store-vars-types-of-last-place
				     store-values-types-of-last-place
				     accessing-form rest-of-expansion env)))))
	  ((null (rest places))
	   (values
	    `(let* ,(mapcar #'list temps value-forms)
	       ,(make-update-form store-vars-of-preceding-place
				  store-vars-types-of-preceding-place
				  store-values-types-of-preceding-place
				  accessing-form
				  `(progn ,@(nreverse storing-forms)
					  ,storing-form
					  nil)
				  env))
	    store-vars store-vars-types store-values-types))
	  (t
	   (multiple-value-bind (rest-of-expansion store-vars-of-last-place
				 store-vars-types-of-last-place
				 store-values-types-of-last-place)
	       (rotatef-aux
		(rest places) env nil store-vars
		(cons storing-form storing-forms))
	     (values
	      `(let* ,(mapcar #'list temps value-forms)
		 ,(make-update-form store-vars-of-preceding-place
				    store-vars-types-of-preceding-place
				    store-values-types-of-preceding-place
				    accessing-form
				    rest-of-expansion
				    env))
	      store-vars-of-last-place
	      store-vars-types-of-last-place
	      store-values-types-of-last-place))))))

;;; TRANSLATOR-GET-SETF-METHOD
;;;
;;; returns a translator-created setf method for the specified place
;;;
;;; ensures that the setf method specifies exactly one store variable
;;;
;;; optional environment arg is specified because a setf method for a
;;; functional name is applicable only when the global binding of that name is
;;; visible (as specified by X3J13)

(defun translator-get-setf-method (place &optional env)
  (multiple-value-bind
    (temps value-forms store-vars storing-form accessing-form)
      (translator-get-setf-method-aux place env)
    (if (or (null store-vars) (rest store-vars))
	(error "The setf method for ~S has ~S store variables.~@
                One store variable was expected."
	       (place-name accessing-form) (length (the list store-vars)))
        (values temps value-forms store-vars storing-form accessing-form))))

;;; TRANSLATOR-GET-SETF-METHOD-MULTIPLE-VALUE
;;;
;;; returns a translator-created setf method for the specified place
;;;
;;; allows setf methods with zero or multiple store variables to be returned
;;;
;;; optional environment arg specified

(defun translator-get-setf-method-multiple-value (place &optional env)
  (translator-get-setf-method-aux place env))

(defun translator-get-setf-method-aux (place env)
  (cond ((symbolp place)
	 (multiple-value-bind (expanded-place expandedp)
	     (translator-symbol-macroexpand-1 place env)
	   (if expandedp
	       (translator-get-setf-method-aux expanded-place env)
	       (make-variable-setf-method place env))))
	((consp place)
	 (let* ((name (first place))
		(expander (get-setf-method-expander name env)))
	   (if expander
	       (funcall expander place env)
	       (multiple-value-bind (expanded-place expandedp)
		   (translator-macroexpand-1 place env)
		 (if expandedp
		     (translator-get-setf-method-aux expanded-place env)
		     (if (symbolp (first place))
			 (make-setf-function-setf-method place env)
		         (error "The form ~S is not a known place and~@
                                 a setf-function setf method can't be created."
				place)))))))
	(t (error "A generalized variable can't be of type ~S."
		  (type-of place)))))

(defun local-functional-def-p (name &optional env)
  (multiple-value-bind (type localp)
      (translator-function-information name env)
    (and localp type)))

(defun get-setf-method-expander (place-name &optional env)
  (and (not (local-functional-def-p place-name env))
       (defined-as-generalized-variable place-name env)))

;;; get a place's name

(defun place-name (place)
  ;; this function can be called with a place whose general form is one of the
  ;; following :
  ;; 1. a symbol
  ;; 2. (<place-name> <arg1> ... <argn>)
  ;; 3. (APPLY (function <place-name>) <arg1> ... <argn>)
  ;; 4. (THE <type> <place>)
  ;; two values are returned :
  ;;  1. the place's name
  ;;  2. t if APPLY of place was specified, otherwise nil
  (if (symbolp place)
      (values place nil)
      (let ((name (first place)))
	(cond ((eq name 'the) (place-name (third place)))
	      ((eq name 'apply) (values (second (second place)) t))
	      (t (values (first place) nil))))))

;;; all place macros should use this function to generate the code that will
;;; bind the store variable(s) and update the value(s) of the place

(defun make-update-form (store-vars store-vars-types store-values-types
				    new-value-form storing-form env)
  (cond ((null store-vars)
	 `(progn
	    ,new-value-form
	    ,storing-form))
	((rest store-vars)
	 (multiple-value-bind
	       (actual-store-vars actual-new-value-form store-var-replacements)
	     (remove-bindings-if-constantp
	      store-vars
	      new-value-form
	      :env env
	      :multiple-value-bind-p t)
	   (let ((declares (mapcar #'(lambda (var var-type)
				       `(type ,var-type ,var))
				   actual-store-vars store-vars-types)))
	     `(multiple-value-bind ,actual-store-vars
		  ,actual-new-value-form
		,@(when declares `((declare ,@declares)))
		(symbol-macrolet
		 ,(make-non-circular-symbol-macrolet-bindings
		   store-vars store-var-replacements)
		 ,storing-form)))))
	(t
	 (multiple-value-bind
	       (actual-store-vars actual-new-value-form store-var-replacements)
	     (remove-bindings-if-constantp
	      store-vars
	      (list new-value-form)
	      :env env)
	   (let ((declares (mapcar #'(lambda (var var-type)
				       `(type ,var-type ,var))
				   actual-store-vars store-vars-types)))
	     `(let ,(mapcar #'(lambda (var form type)
				`(,var ,(if (eq type 't)
					    form
					    `(the ,type ,form))))
			    actual-store-vars actual-new-value-form
			    (or store-values-types '(t)))
		,@(when declares `((declare ,@declares)))
		(symbol-macrolet
		 ,(make-non-circular-symbol-macrolet-bindings
		   store-vars store-var-replacements)
		 ,storing-form)))))))

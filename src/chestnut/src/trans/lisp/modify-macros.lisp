;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; MODIFY-MACROS -- handle DEFINE-MODIFY-MACRO and the read-modify-write
;;;                  generalized-variable macros DECF, INCF, POP, PUSH,
;;;                  PUSHNEW, and REMF
;;;
;;; Author : John Gilson
;;;
;;; Copyright (c) 1990, Chestnut Software, Inc.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/modify-macros.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:09 $")

;;; DEFINE-MODIFY-MACRO
;;;
;;; handles a place whose setf method has multiple store variables

;;; make expansion for define-modify-macro and define-translator-modify-macro

(eval-when (eval compile load)
(defmacro make-define-modify-macro-expansion
  (name &key pre-place-params post-place-lambda-list function doc)
  ;; pre-place-params can only contain required parameters
  ;; post-place-lambda-list may contain required, &optional, and &rest
  ;; parameters but not &key parameters
  `(multiple-value-bind
     (post-place-required post-place-optional post-place-rest)
       (get-function-params ,post-place-lambda-list :key-args-not-allowed-p t)
     `(define-translator-macro ,,name
	(&environment env ,@,pre-place-params accessing-form
		          ,@,post-place-lambda-list)
	,@(if (string= ,doc "") nil (list ,doc))
	(let ((pre-place-args (list ,@,pre-place-params))
	      (post-place-args (list* ,@post-place-required
				      ,@post-place-optional
				      ,(first post-place-rest))))
	  (multiple-value-bind (macro-call-bindings update-form
				accesssing-form-temp macro-call-declarations)
	      (make-modify-macro-expansion
	        :name ',,name
		:pre-place-args pre-place-args
		:place-arg accessing-form
		:post-place-args post-place-args
		:function ',,function
		:env env)
	      (declare (ignore accesssing-form-temp))
	    `(let* ,macro-call-bindings
	       ,@(when macro-call-declarations
		   `((declare ,@macro-call-declarations)))
	       ,update-form))))))
)

(define-translator-macro define-modify-macro
  (name lambda-list function &optional (doc ""))
  `(progn
     (eval-when (compile)
       (print-progress-message "Modify macro" ',name)
       ,(make-define-modify-macro-expansion
	  name :post-place-lambda-list lambda-list :function function
	  :doc doc))
     (eval-when (load eval)
       ',name)))

(defun make-type-declarations (temps temps-types)
  (mapcan #'(lambda (var type)
	      (unless (or (eq type 't) (eq type 'nil))
		`((type ,type ,var))))
	  temps
	  temps-types))

;;; make-modify-macro-expansion takes the following keyword arguments :
;;;
;;; NAME : name of the modify macro
;;;
;;; PRE-PLACE-ARGS : a list of macro-call arguments that precede the place
;;;                  argument
;;;
;;; PLACE-ARG : place from the macro-call form
;;;
;;; POST-PLACE-ARGS : a list of macro-call arguments that follow the place
;;;                   argument
;;;
;;; FUNCTION : the function used to get new value(s) for the place
;;;
;;; TEMP-ACCESSING-FORM-P : if non-nil, then make a temp that will be bound to
;;;                         the old value of the place
;;;
;;; ENV : an environment
;;;
;;; this function returns three values :
;;; 1. a list of bindings, created from the macro-call form, that can be
;;;    plugged into a let*
;;;    the binding order is PRE-PLACE-ARGS followed by subforms of
;;;    PLACE-ARG, then POST-PLACE-ARGS, and finally the binding for the old
;;;    value of the place if TEMP-ACCESSING-FORM-P is non-nil
;;; 2. an update form that binds the store variable(s) and does the update to
;;;    the place
;;; 3. if TEMP-ACCESSING-FORM-P is non-nil, then the temp that was created to
;;;    be bound to the old value of the place is returned

(defun make-modify-macro-expansion
  (&key name pre-place-args place-arg post-place-args function
	temp-accessing-form-p env)
  (multiple-value-bind
	(temps value-forms store-vars storing-form accessing-form
         temps-types store-vars-types store-values-types)
      (translator-get-setf-method-multiple-value place-arg env)
    (let* ((len-pre-place-args (length (the list pre-place-args)))
	   (len-post-place-args (length (the list post-place-args)))
	   (macro-temps
	    (make-temp-vars (+ len-pre-place-args len-post-place-args)
			    (sformat "~A-ARG" name)))
	   (pre-place-temps
	    (subseq (the list macro-temps) 0 len-pre-place-args))
	   (accessing-form-bindings (mapcar #'list temps value-forms))
	   (accessing-form-temp
	    (if temp-accessing-form-p
		(multiple-value-bind (name apply-used-p)
		    (place-name accessing-form)
		  (if apply-used-p
		      (make-symbol (sformat "APPLY-OF-~A-OLD-VALUE" name))
		      (make-symbol (sformat "~A-OLD-VALUE" name))))))
	   (post-place-temps (nthcdr len-pre-place-args macro-temps)))
      (multiple-value-bind
	    (actual-pre-place-temps actual-pre-place-args pre-place-temps&args)
	  (remove-bindings-if-constantp
	   pre-place-temps pre-place-args :env env)
	(multiple-value-bind
	      (actual-post-place-temps actual-post-place-args
	       post-place-temps&args)
	    (remove-bindings-if-constantp
	     post-place-temps post-place-args :env env)
	  (let ((pre-place-bindings
		 (mapcar #'list
			 actual-pre-place-temps actual-pre-place-args))
		(post-place-bindings
		 (mapcar #'list
			 actual-post-place-temps actual-post-place-args))
		(new-value-fn-call
		 `(,function ,@pre-place-temps&args
			     ,(if temp-accessing-form-p
				  accessing-form-temp
				  accessing-form)
			     ,@post-place-temps&args))
		(declarations (make-type-declarations temps temps-types)))
	    (values
	      (nconc pre-place-bindings
		     accessing-form-bindings
		     post-place-bindings
		     (if temp-accessing-form-p
			 `((,accessing-form-temp ,accessing-form))))
	      (make-update-form store-vars store-vars-types store-values-types
				new-value-fn-call storing-form env)
	      accessing-form-temp
	      declarations)))))))

;;; DEFINE-TRANSLATOR-MODIFY-MACRO

(defmacro define-translator-modify-macro
  (name &key pre-place-params post-place-lambda-list function (doc ""))
  (make-define-modify-macro-expansion
    name
    :pre-place-params pre-place-params
    :post-place-lambda-list post-place-lambda-list
    :function function
    :doc doc))

;;; DECF

(define-translator-modify-macro decf
  :post-place-lambda-list (&optional (delta 1))
  :function -
  :doc
  "The read-modify-write macro DECF.
   The new-value function is -.")

;;; INCF

(define-translator-modify-macro incf
  :post-place-lambda-list (&optional (delta 1))
  :function +
  :doc
  "The read-modify-write macro INCF.
   The new-value function is +.")

;;; POP

(define-translator-macro pop (&environment env place)
  "The read-modify-write macro POP.
   The new-value function is rest."
  (multiple-value-bind (pop-call-bindings update-form accessing-form-temp)
      (make-modify-macro-expansion
        :name 'pop
	:place-arg place
	:function 'rest
	;; temp-accessing-form-p is t because a temp needs to be generated and
	;; bound to the old value of the accessing form to avoid multiple
	;; evaluations
	:temp-accessing-form-p t
	:env env)
    `(let* ,pop-call-bindings
       (prog1 (first ,accessing-form-temp)
	      ,update-form))))

;;; PUSH

(define-translator-modify-macro push
  :pre-place-params (item)
  :function cons
  :doc
  "The read-modify-write macro PUSH.
   The new-value function is cons.")

;;; PUSHNEW

(define-translator-modify-macro pushnew
  :pre-place-params (item)
  :post-place-lambda-list (&rest keywords)
  :function adjoin
  :doc
  "The read-modify-write macro PUSHNEW.
   The new-value function is adjoin.")

;;; REMF
;;;
;;; the new-value function do-remf returns :
;;;
;;; if the property was found, the new property list with the property
;;; indicator and the corresponding value destructively removed
;;;
;;; if the property was not found, t

(define-translator-macro remf (&environment env place indicator)
  "The read-modify-write macro REMF.
   The new-value function is do-remf."
  (let ((indicator-var (make-symbol "REMF-ARG")))
    (multiple-value-bind
	  (actual-indicator-var actual-indicator-value temp-or-indicator)
        (remove-bindings-if-constantp
	 (list indicator-var)
	 (list indicator)
	 :env env)
      (multiple-value-bind
	    (temps value-forms store-vars storing-form accessing-form
	     temps-types store-vars-types store-values-types)
	  (translator-get-setf-method-multiple-value place env)
	(let ((declarations (make-type-declarations temps temps-types)))
	  `(let* ,(nconc (mapcar #'list temps value-forms)
			 (if actual-indicator-var
			     `(,(nconc actual-indicator-var
				       actual-indicator-value))))
	     ,@(when declarations `((declare ,declarations)))
	     ,(if store-vars
		  (make-update-form
		   store-vars store-vars-types store-values-types
		   `(trun:do-remf ,accessing-form ,@temp-or-indicator)
		   `(unless (eq ,(first store-vars) t)
		      ,storing-form
		      t)
		   env)
		  `(unless (eq `(trun:do-remf
				    ,accessing-form ,@temp-or-indicator)
			       t)
		     ,storing-form
		     t))))))))

;;; -*- Mode: Lisp; Package: TUTIL; Syntax: Common-Lisp -*-
;;;
;;; lambda.lsp -- various lambda-list parsing routines
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  11 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;

(in-package "TUTIL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/lambda.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/11/14 22:02:54 $")


;;; Note that the entire destructuring implementation is replicated in
;;; allegro-4-0-1-defs.lisp, since the allegro destructuring-bind (which
;;; the translator uses) is broken. We can't use the stuff in here because
;;; of package ordering problems. So any bug fixes that occur in this
;;; file should be propagated also to allegro-4-0-1-defs.lisp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Low-level parsing
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Here is the general-purpose parsing function.  It loops through
;;; each of the parameter specifiers in the lambda-list, calling
;;; the appropriate function (for side effect) for each one.  The
;;; functions should be defined as follows:
;;;    whole                (name)
;;;    required             (name)
;;;    optional             (name default default-p svar svar-p)
;;;    rest                 (name)
;;;    keyp                 ()
;;;    key                  (name keyword default default-p svar svar-p)
;;;    allow-other-keys-p   ()
;;;    aux                  (name default default-p)
;;; Note that this function will also handle DEFMACRO-like lambda lists
;;; with destructuring, provided that &ENVIRONMENT is removed first
;;; and destructure-p is true.  Destructure-p also inhibits some syntax
;;; checking.
;;;
;;; The idea is that we look for each kind of parameter specifier in turn,
;;; passing the tail of the lambda list to the handler for the next piece
;;; of possible syntax.  After doing the &aux, see if there's anything left.
;;;

(defmacro parse-lambda-list (lambda-list &key whole required optional rest
					 keyp key allow-other-keys-p aux
					 destructure-p)
  (unless (or (eq destructure-p 't) (eq destructure-p 'nil))
    (error "~S needs a constant ~S argument"
	   'parse-lambda-list ':destructure-p))
  `(let ((.tail. ,lambda-list) .arg.)
     ;; &WHOLE is permitted only if destructure-p is true.
     ;; Destructuring syntax for the parameter is not permitted.
     ,@(when destructure-p
	 `((when (eq (car .tail.) '&whole)
	     (when (or (atom (cdr .tail.))
		       (lambda-keyword-p (setq .arg. (cadr .tail.))))
	       (lambda-list-parse-error
		,lambda-list "Missing &WHOLE lambda variable."))
	     (check-parameter-syntax nil .arg. lambda-list)
	     ,@(when whole `((funcall* ,whole .arg.)))
	     (setq .tail. (cddr .tail.)))))
     ;; Pop off the required arguments.
     ;; Stop when we hit the next lambda keyword.
     ;; Destructuring syntax for the parameter is permitted.
     (loop (when (or (atom .tail.)
		     (lambda-keyword-p (setq .arg. (car .tail.))))
	       (return .tail.))
	   (check-parameter-syntax ,destructure-p .arg. ,lambda-list)
	   ,@(when required `((funcall* ,required .arg.)))
	   (pop .tail.))
     ;; Pop off optional arguments.  Stop when we hit the next lambda keyword.
     ;; Destructuring syntax for the parameter is permitted if the argument
     ;; is a list, but destructuring of the supplied-p parameter is not
     ;; permitted.
     (when (and (consp .tail.) (eq (car .tail.) '&optional))
       (pop .tail.)
       (loop (when (or (atom .tail.)
		       (lambda-keyword-p (setq .arg. (car .tail.))))
	       (return nil))
	     (if (not (consp .arg.))
		 (check-parameter-syntax nil .arg. ,lambda-list nil)
		 (progn
		   (check-parameter-syntax
		    ,destructure-p (car .arg.) ,lambda-list)
		   (check-optional-key-syntax '&optional .arg. ,lambda-list)))
	     ,@(when optional 
		 `((let* ((.name. (if (consp .arg.) (pop .arg.) .arg.))
			  (.default-p. (consp .arg.))
			  (.default. (when .default-p. (pop .arg.)))
			  (.svar-p. (consp .arg.))
			  (.svar. (when .svar-p. (car .arg.))))
		     (funcall* ,optional .name. .default. .default-p.
			       .svar. .svar-p.))))
	     (pop .tail.)))
     ;; Look for &REST, &BODY, or dotted lambda list.  
     ;; The latter two forms are permitted only if destructure-p is true.
     (cond ((and (consp .tail.)
		 (or (eq (car .tail.) '&rest)
		     ,@(when destructure-p
			 `((eq (car .tail.) '&body)))))
	    (if (or (atom (cdr .tail.))
		    (lambda-keyword-p (setq .arg. (cadr .tail.))))
		(lambda-list-parse-error
		 ,lambda-list "Missing &REST lambda variable."))
	    (check-parameter-syntax ,destructure-p .arg. ,lambda-list)
	    ,@(when rest `((funcall* ,rest .arg.)))
	    (setq .tail. (cddr .tail.)))
	   ,@(when destructure-p
	       `(((and .tail. (atom .tail.))
		  (check-parameter-syntax nil .tail. ,lambda-list)
		  ,@(when rest `((funcall* ,rest .tail.)))))))
     ;; Process &KEY arguments.  Call the keyp function if &KEY appears.
     ;; Call the key function for each argument.  Call the allow-other-keys-p
     ;; function if &ALLOW-OTHER-KEYS appears.
     ;; Destructuring syntax for the parameter is permitted if it is specified
     ;; using ((key var) ...) syntax.  Destructuring of the supplied-p 
     ;; parameter is not permitted.
     (when (and (consp .tail.) (eq (car .tail.) '&key))
       (pop .tail.)
       ,@(when keyp `((funcall* ,keyp)))
       (loop (when (or (atom .tail.)
		       (lambda-keyword-p (setq .arg. (car .tail.))))
	       (return nil))
	     (if (not (consp .arg.))
		 (check-parameter-syntax nil .arg. ,lambda-list)
		 (progn
		   (if (consp (car .arg.))
		       (check-parameter-syntax
			,destructure-p (second (car .arg.)) ,lambda-list)
		       (check-parameter-syntax nil (car .arg.) ,lambda-list))
		   (check-optional-key-syntax '&key .arg. ,lambda-list)))
	     ,@(when key
		 `((let* ((.name-part. (if (consp .arg.) (pop .arg.) .arg.))
			  (.name. (if (consp .name-part.)
				      (second .name-part.)
				      .name-part.))
			  (.keyword. (if (consp .name-part.)
					 (first .name-part.)
					 (keywordify .name.)))
			  (.default-p. (consp .arg.))
			  (.default. (when .default-p. (pop .arg.)))
			  (.svar-p. (consp .arg.))
			  (.svar. (when .svar-p. (car .arg.))))
		     (funcall* ,key .name. .keyword. .default. .default-p.
			       .svar. .svar-p.))))
	     (pop .tail.)))
     (when (and (consp .tail.) (eq (car .tail.) '&allow-other-keys))
       ,@(when allow-other-keys-p `((funcall* ,allow-other-keys-p)))
       (pop .tail.))
     ;; Do the &aux parameters.  Destructuring syntax is permitted for
     ;; the list form.
     (when (and (consp .tail.) (eq (car .tail.) '&aux))
       (pop .tail.)
       (loop (when (or (atom .tail.)
		       (lambda-keyword-p (setq .arg. (car .tail.))))
	      (return nil))
	     (if (consp .arg.)
		 (progn
		   (check-parameter-syntax
		    ,destructure-p (car .arg.) ,lambda-list)
		   (if (cddr .arg.)
		       (lambda-list-parse-error
			,lambda-list
			(format nil "Invalid &AUX syntax ~s." .arg.))))
		 (check-parameter-syntax nil .arg. ,lambda-list))
	     ,@(when aux
		 `((let* ((.name. (if (consp .arg.) (pop .arg.) .arg.))
			  (.default-p. (consp .arg.))
			  (.default. (when .default-p. (pop .arg.))))
		     (funcall* ,aux .name. .default. .default-p.))))
	     (pop .tail.)))
     .tail.))

(defmacro funcall* (function &rest args) ; an aid for compilers
  (if (and (consp function) (eq (car function) 'function))
      `(,(cadr function) ,@args)
      `(funcall ,function ,@args)))

;;; Is the symbol a lambda-list-keyword?  Signal an error if we detect 
;;; problems with nonportable syntax.

(eval-when (eval compile load)
(#-SBCL defconstant #+SBCL define-constant translator-lambda-list-keywords
  '(&optional &rest &key &allow-other-keys &aux
    &environment &whole &body))
)

(eval-when (eval compile load)
(#-SBCL defconstant #+SBCL define-constant host-extension-lambda-list-keywords
  '#.(set-difference lambda-list-keywords translator-lambda-list-keywords))
)

(defun lambda-keyword-p (symbol)
  (cond ((member symbol translator-lambda-list-keywords :test #'eq)
	 t)
	((member symbol host-extension-lambda-list-keywords :test #'eq)
	 (error "~s is a lambda-list-keyword in the host Lisp, but is not ~
                  supported by the translator." symbol)
	 nil)
	(t
	 nil)))


;;; Check to make sure that the lambda parameter is a symbol or a cons,
;;; if it makes sense to have a list here.

(defmacro check-parameter-syntax (cons-allowed-p variable lambda-list &optional
				  (consp :unknown))
  (if cons-allowed-p
      (once-only (variable)
	`(unless ,(if (null consp)
		      `(symbolp ,variable)
		      `(or (symbolp ,variable) (consp ,variable)))
	   (lambda-list-parse-error
	    ,lambda-list
	    (format nil
		    "The lambda parameter ~s is not a symbol or a list."
		    ,variable))))
      `(unless (symbolp ,variable)
	 (lambda-list-parse-error
	  ,lambda-list
	  (format nil
		  "The lambda parameter ~s is not a symbol." ,variable)))))


;;; Check syntax of optional/key parameter lists: make sure that the
;;; supplied-p var (if there is one) is a symbol and that the list isn't
;;; too long.

(defmacro check-optional-key-syntax (which arg lambda-list)
  `(progn
     (when (cddr ,arg)
       (check-parameter-syntax nil (caddr ,arg) ,lambda-list))
     (when (cdddr ,arg)
	(lambda-list-parse-error
	 ,lambda-list
	 (format nil "Invalid ~s argument syntax ~s." ,which ,arg)))))






;;; Helper functions

;;; Map the symbol into the keyword package.

(defun keywordify (symbol)
  (intern (symbol-name symbol) (find-package :keyword)))

;;; Helper function for match-argvalues-to-parameters.
(defun match-args-to-parameters-aux (args lambda-list constant-value-fn)
  (let ((result  nil)
	(alist   nil))
    (parse-lambda-list 
     lambda-list
     :required #'(lambda (name)
		   (push name result)
		   (pop args))
     :optional #'(lambda (name default defaultp svar svar-p)
		   (declare (ignore default defaultp svar svar-p))
		   (when args
		     (push name result)
		     (pop args)))
     :key #'(lambda (name keyword default defaultp svar svar-p)
	      (declare (ignore default defaultp svar svar-p))
	      (push (cons keyword name) alist)))
    (if alist
	(do ((args args (cddr args)))
	    ((null args) (values (nreverse result) nil))
	  (multiple-value-bind (value therep)
	      (funcall constant-value-fn (car args))
	    (if therep
		;; If the actual keyword doesn't match a lambda
		;; parameter, just pretend allow-other-keys is 
		;; true and ignore it.  Careful checking for bad 
		;; keywords happens elsewhere anyway.
		(let ((name  (cdr (assoc value alist))))
		  (push nil result)
		  (push name result))
		;; Give up immediately if we find a non-constant 
		;; keyword in the actual arguments.  
		(return
		  (values
		   (nreconc result (make-list (length args)))
		   t)))))
	(values
	 (nreconc result (make-list (length args)))
	 nil))))


;;; Here are some utilities for messing with the :lambda-list and :declare
;;; keywords to the :function database usage.
;;;
;;; Make a list of all the lambda parameters appearing in the lambda-list.

(defun collect-lambda-parameters (lambda-list)
  (let ((result nil))
    (parse-lambda-list 
     lambda-list
     :required #'(lambda (name)
		   (push name result)) 
     :optional #'(lambda (name default defaultp svar svar-p)
		   (declare (ignore default defaultp))
		   (push name result)
		   (if svar-p (push svar result)))
     :rest #'(lambda (name)
	       (push name result))
     :key #'(lambda (name keyword default defaultp svar svar-p)
	      (declare (ignore keyword default defaultp))
	      (push name result)
	      (if svar-p (push svar result)))
     :aux #'(lambda (name default defaultp)
	      (declare (ignore default defaultp))
	      (push name result)))
    (nreverse result)))




;;; General function for signalling lambda list parse errors.  Maybe at
;;; some point we will want to have a distinguished condition type for
;;; these guys.

(defun lambda-list-parse-error (lambda-list message)
  (error "Invalid syntax in lambda-list ~s: ~%~a" lambda-list message))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Destructuring utilities
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Look for and remove &environment from the lambda-list.  Returns
;;;    two variables, the &environment parameter (or NIL) and the
;;;    rest of the lambda list.

(defun extract-environment (lambda-list)
  (let ((head  nil))
    (loop
      (cond ((atom lambda-list)
	     (return (values nil (nconc (nreverse head) lambda-list))))
	    ((eq (car lambda-list) '&environment)
	     (return (values (cadr lambda-list)
			     (nconc (nreverse head) (cddr lambda-list)))))
	    (t
	     (push (pop lambda-list) head))))))


;;; Destructure the lambda-list.  Returns two values: a set of bindings 
;;; suitable for plugging into LET*, and the name of the &whole parameter
;;; (which might be a temporary variable).
;;; The lambda-list can contain &whole but must not contain &environment.
;;; Note that &whole is defined to be treated differently at the outermost 
;;; level of destructuring, which is why we strip it off here instead of
;;; letting destructure-aux do it.

(defun destructure (lambda-list &optional (default-init nil))
  (let ((whole-var  nil)
	(tail-var   (make-symbol "TAIL")))
    (if (eq (car lambda-list) '&whole)
	(progn
	  (setq whole-var (cadr lambda-list))
	  (setq lambda-list (cddr lambda-list)))
        (setq whole-var (make-symbol "WHOLE")))
    (values
      (nreverse
	(destructure-aux lambda-list tail-var
			 (list `(,tail-var (cdr ,whole-var)))
			 default-init))
      whole-var)))

(eval-when (compile load eval)
(defun destructure-keyword-value1 (tail key init svar)
  (let ((block (gensym)))
    `(block ,block
       (do ((,tail ,tail (cdr ,tail)))
	   ((endp ,tail))
	 (when (eq ',key (pop ,tail))
	   ,@(when svar `((setf ,svar t)))
	   (return-from ,block (car ,tail))))
       ,@(when svar `((setf ,svar nil)))
       ;; Execute initform outside the NIL block established by DO.
       ,init)))
)

(defmacro destructure-keyword-value (tail key init svar)
  (destructure-keyword-value1 tail key init svar))

#||
(define-translator-macro destructure-keyword-value (tail key init svar)
  (destructure-keyword-value1 tail key init svar))
||#
		    
;; *** There is nothing here to do exact key checking of keyword arguments.

(defvar *destructure-key-svar* (make-symbol "key suppliedp"))

(defun destructure-aux (lambda-list tail-var bindings default-init
				    &aux (key-svar nil))
  (parse-lambda-list 
   lambda-list
   :whole    #'(lambda (arg)
		 (push `(,arg ,tail-var) bindings)) 
   :required #'(lambda (arg)
		 (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
		   (push `(,name (pop ,tail-var)) bindings)
		   (when destructure-p
		     (setq bindings
			   (destructure-aux arg name bindings default-init)))))
   :optional #'(lambda (arg init initp svar svar-p)
		 (unless initp (setq init default-init))
		 (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
		   (if (not svar-p)
		       (push `(,name (if ,tail-var (pop ,tail-var) ,init))
			     bindings)
		       (progn
			 (push `(,name (if ,tail-var (car ,tail-var) ,init))
			       bindings)
			 (push `(,svar (prog1 ,tail-var (pop ,tail-var)))
			       bindings)))
		   (when destructure-p
		     (setq bindings
			   (destructure-aux arg name bindings default-init)))))
   :rest     #'(lambda (arg)
		 (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
		   (push `(,name ,tail-var) bindings)
		   (when destructure-p
		     (setq bindings
			   (destructure-aux arg name bindings default-init)))))
   :key      #'(lambda (arg keyword init initp svar svar-p)
		 (unless initp (setq init default-init))
		 (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
		   (when (and svar-p (null key-svar))
		     ;; If this is the first time we've encountered a suppliedp
		     ;; variable for a keyword parameter, initialize key-svar 
		     ;; (so we know we've done this part) and add a binding of
		     ;; the common suppliedp variable.
		     (setf key-svar *destructure-key-svar*)
		     (push `(,key-svar nil) bindings))
		   (push `(,name
			   (destructure-keyword-value
			    ,tail-var
			    ,keyword
			    ,init
			    ;; When we're going to follow this binding with
			    ;; a binding of an svar, update the common
			    ;; suppliedp variable so that the following svar
			    ;; binding can use it.
			    ,(and svar-p key-svar)))
			 bindings)
		   (when svar-p (push `(,svar ,key-svar) bindings))
		   (when destructure-p
		     (setq bindings
			   (destructure-aux arg name bindings default-init)))))
   :aux      #'(lambda (arg init initp)
		 (declare (ignore initp))
		 (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
		   (push `(,name ,init) bindings)
		   (when destructure-p
		     (setq bindings
			   (destructure-aux arg name bindings nil)))))
   :destructure-p  t)
  bindings)


;;; A helper function; check the syntax of an argument that might possibly
;;; need to be destructured.  If it's a cons, create a gensym.  Return two
;;; values, the name and a destructure-p value.

(defun check-destructuring-parameter (arg lambda-list)
    (cond ((symbolp arg)
	   (values arg nil))
	  ((consp arg)
	   (values (make-symbol "TAIL") t))
	  (t
	   (lambda-list-parse-error
	       lambda-list
	       (format nil "Cannot destructure ~s." arg)))))


;;; Defining forms for macro, compiler-macro, and type expansion
;;; functions all support destructuring.  Use a common helper function 
;;; to build the function form.

(eval-when (compile load eval)
(defvar *macro-whole*  (make-symbol "WHOLE"))
(defvar *macro-env*    (make-symbol "ENV"))
(defvar *macro-tail*   (make-symbol "TAIL"))
)

(defun translator-parse-macro (name lambda-list body &optional env)
  (declare (ignore env))
  (translator-parse-macro-aux name lambda-list body
			      `(cdr ,*macro-whole*)
			      nil))

(defun translator-parse-macro-for-expander (name lambda-list body
						 &optional env)
  (declare (ignore env))
  (let ((*macro-whole* (make-symbol "CALL-FORM"))
	(*macro-env*   (make-symbol "ENV"))
	(*macro-tail*  (make-symbol "REST-OF-CALL-FORM")))
    (translator-parse-macro-aux name lambda-list body
				`(rest ,*macro-whole*)
				nil)))

(defun translator-parse-compiler-macro (name lambda-list body &optional env)
  (declare (ignore env))
  (translator-parse-macro-aux name lambda-list body
			      `(if (eq (car ,*macro-whole*) 'funcall)
				   (cddr ,*macro-whole*)
				   (cdr ,*macro-whole*))
			      nil))

(defun translator-parse-deftype (name lambda-list body &optional env)
  (declare (ignore env))
  (translator-parse-macro-aux name lambda-list body
			      `(cdr ,*macro-whole*)
			      ''*))


;;; Set up the destructuring of the lambda list.  The tail-init specifies
;;; a form that the destructuring applies to, and the default-init
;;; specifies a form that is used as the default for unsupplied defaults
;;; for &optional and &key parameters.

(defun translator-parse-macro-aux (name lambda-list body tail-init
					default-init)
  (multiple-value-bind (real-body decls doc) (parse-body body t)
    (if (null lambda-list)
	`(lambda (,*macro-whole* ,*macro-env*)
	   ,@(when doc (list doc))
	   (declare (ignore ,*macro-whole* ,*macro-env*)
		    ,@decls)
	   (block ,(body-block-name name) ,@real-body))
	(multiple-value-bind (env-var rest-of-lambda-list)
	    (extract-environment lambda-list)
	  (let ((whole-var
		 (when (eq (car rest-of-lambda-list) '&whole)
		   (prog1 (cadr rest-of-lambda-list)
		     (setf rest-of-lambda-list (cddr rest-of-lambda-list)))))
		(bindings
		 (if (null rest-of-lambda-list)
		     ()
		     (nreverse
		      (destructure-aux rest-of-lambda-list
				       *macro-tail*
				       `((,*macro-tail* ,tail-init))
				       default-init)))))
	    `(lambda (,*macro-whole* ,*macro-env*)
	       ,@(when doc (list doc))
	       (declare (ignore 
                         ,@(unless (or whole-var bindings)
                             `(,*macro-whole*))
                         ,@(unless env-var 
                             `(,*macro-env*))))
	       ;; Ensure that bindings for whole-var and env-var pick up any
	       ;; related declarations.
	       (let* (,@(when whole-var `((,whole-var ,*macro-whole*)))
		      ,@(when env-var `((,env-var ,*macro-env*)))
		      ,@bindings)
		 (declare ,@decls)
		 (block ,(body-block-name name) ,@real-body))))))))


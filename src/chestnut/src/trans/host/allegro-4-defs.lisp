;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; allegro-4-defs.lisp -- host compatibility functions for Allegro 4
;;;
;;; author :  Andy Latto (based on Lucid version by Sandra Loosemore,
;;;    from original by Kim Barrett)
;;;
;;; date   :  4 Jan 1992
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/allegro-4-defs.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006-02-28 21:58:58 $")

#-ALLEGRO
#.(error "Attempting to use incorrect host database.
This file is for Allegro Common Lisp version 4")

;;; This file attempts to work for both Allegro 4-0-1 and Allegro 4-1.
;;; Probably we should have more uses of #+ and #-.

;;; No second argument in Allegro's version.

(defun host:upgraded-array-element-type (type &optional env)
  (when env
    (warn "Ignoring environment argument ~A to upgraded-array-element-type"
	  env))
  (common-lisp:upgraded-array-element-type type))

;(define-condition simple-program-error (simple-condition program-error) ())
;    
;(defun simple-program-error (format-control &rest arguments)
;  (error 'simple-program-error
;	   :format-control format-control
;	   :format-arguments arguments))

;(defun simple-program-error (format-control &rest arguments)
;  (apply #'error format-control arguments))

;;; Define ANSI version of LAST, which now takes an optional second argument.
(defun HOST:LAST (list &optional (n 1))
  (if (eql n 1)
      (last list)
      (do ((head list (cdr head))
	   (tail (do ((tail list (cdr tail)))
		     ((or (atom tail) (minusp (decf n))) tail))
		 (cdr tail)))
	  ((atom tail) head))))

;;; For implementations which support DEFINE-COMPILER-MACRO, but which do
;;; not support the optional second argument to LAST, provide a compiler
;;; macro which transforms case where second argument is constant 1 into
;;; call to the single argument function.

;(define-compiler-macro host:last (&whole whole list &optional (n 1))
;  (if (and (constantp n) (eql (eval n) 1))
;      `(last ,list)
;      whole))


;;; Define COMPLEMENT and CONSTANTLY

(defun HOST:COMPLEMENT (function)
  #'(lambda (&rest arguments)
      (not (apply function arguments))))

(defun HOST:CONSTANTLY (value)
  (flet ((constantly-false (&rest ignore)
	   (declare (ignore ignore))
	   'NIL)
	 (constantly-true (&rest ignore)
	   (declare (ignore ignore))
	   'T))
    (cond ((null value) #'constantly-false)
	  ((eql value 'T) #'constantly-true)
	  (t
	   ;; Hopefully, any compiler smart enough to optimize away this
	   ;; binding will also be smart enough to recognize that the bound
	   ;; value is closed over and avoid closing over the outer binding
	   ;; by actually not optimizing away this binding.
	   (let ((value value))
	     #'(lambda (&rest ignore)
		 (declare (ignore ignore))
		 value))))))

;;; MAP-INTO
;;;
;;; [Not very efficient, but it will probably suffice for now.]

(defun HOST:MAP-INTO (destination function &rest sequences)
  (etypecase destination
    (list
     (let ((target destination))
       (flet ((apply-function (&rest arguments)
		(if (endp target)
		    (return-from host:map-into destination)
		    (progn
		      (setf (car target) (apply function arguments))
		      (setf target (cdr target))))))
	 (apply #'map nil #'apply-function sequences)
	 destination)))
    (vector
     (let ((index 0)
	   (end (array-dimension destination 0)))
       (labels ((apply-function (&rest arguments)
		  (when (<= end index) (finish-mapping))
		  (setf (aref destination index) (apply function arguments))
		  (incf index))
		(finish-mapping ()
		  (when (array-has-fill-pointer-p destination)
		    (setf (fill-pointer destination) index))
		  (return-from host:map-into destination)))
	   (apply #'map nil #'apply-function sequences)
	   (finish-mapping))))))

;;; NTH-VALUE

(defmacro HOST:NTH-VALUE (index value-form)
  (flet ((make-default-expansion (index value-form)
	   `(nth ,index (multiple-value-list ,value-form))))
    (if (constantp index)
	(let ((index-value (eval index)))
	  (if (typep index-value '(integer 0))
	      (let ((vars ())
		    (result (gensym)))
		(dotimes (i index-value)
		  (push (gensym) vars))
		`(multiple-value-bind (,@vars ,result)
		     ,value-form
		   (declare (ignore ,@vars))
		   ,result))
	      (progn
		(warn "Index for ~S is not a non-negative integer: ~S."
		      'host:nth-value index-value)
		(make-default-expansion index value-form))))
	(make-default-expansion index value-form))))
			      
;;; PARSE-ERROR

(define-condition HOST:PARSE-ERROR (error) ())

;;; STYLE-WARNING

(define-condition HOST:STYLE-WARNING (warning) ())

;;; Iterators
;;;
;;; These aren't very efficient, but should do for now.

(defmacro HOST:WITH-HASH-TABLE-ITERATOR
          ((mname table) &body body &environment env)
  (multiple-value-bind (body decls)
      (parse-body body env nil)
    (let ((keys (gensym))
	  (values (gensym)))
      `(multiple-value-bind (,keys ,values)
	   ;; It would be more efficient to get these from a free pool
	   (let ((,keys (make-array 10 :fill-pointer 0 :adjustable t))
		 (,values (make-array 10 :fill-pointer 0 :adjustable t)))
	     (maphash #'(lambda (key value)
			  (vector-push key ,keys)
			  (vector-push value ,values))
		      ,table)
	     (values ,keys ,values))
	 ,@decls
	 (macrolet ((,mname ()
		       `(unless (zerop (length ,keys))
			  (values t
				  (vector-pop ,keys)
				  (vector-pop ,values)))))
	   ,@body)))))

;(defmacro HOST:WITH-PACKAGE-ITERATOR ...)

;;; Allegro destructuring-bind is broken when &key occurs in the lambda list.
;;; This code is copied from lambda.lisp, where it is in the tutil package.
;;; We replicate it here, since this needs to be compiled and loaded before
;;; the tutil package even exists.


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
;;;    optional             (name &optional default svar)
;;;    rest                 (name)
;;;    keyp                 ()
;;;    key                  (name keyword &optional default svar)
;;;    allow-other-keys-p   ()
;;;    aux                  (name &optional default)
;;; Note that this function will also handle DEFMACRO-like lambda lists
;;; with destructuring, provided that &ENVIRONMENT is removed first
;;; and destructure-p is true.  Destructure-p also inhibits some syntax
;;; checking.
;;;
;;; The idea is that we look for each kind of parameter specifier in turn,
;;; passing the tail of the lambda list to the handler for the next piece
;;; of possible syntax.  After doing the &aux, see if there's anything left.
;;;

(defun parse-lambda-list (lambda-list &key whole required optional rest
				      keyp key allow-other-keys-p aux
				      destructure-p)
    (let ((tail   lambda-list))
	(setq tail
	      (parse-lambda-whole lambda-list tail whole destructure-p))
	(setq tail
	      (parse-lambda-required lambda-list tail required destructure-p))
	(setq tail
	      (parse-lambda-optional lambda-list tail optional destructure-p))
	(setq tail
	      (parse-lambda-rest lambda-list tail rest destructure-p))
	(setq tail
	      (parse-lambda-key lambda-list tail keyp key allow-other-keys-p
				destructure-p))
	(setq tail
	      (parse-lambda-aux lambda-list tail aux destructure-p))
	(cond ((null tail)
	       nil)
	      ((atom tail)
	       (lambda-list-parse-error
		   lambda-list
		   "Invalid dotted lambda-list syntax."))
	      (t
	       (lambda-list-parse-error
		   lambda-list
		   (format nil "Misplaced lambda-list keyword ~s."
			   (car tail)))))
	))



;;; &WHOLE is permitted only if destructure-p is true.
;;; Destructuring syntax for the parameter is not permitted.

(defun parse-lambda-whole (lambda-list tail whole destructure-p)
    (when (and destructure-p (eq (car lambda-list) '&whole))
	(if (or (atom (cdr tail)) (lambda-keyword-p (cadr tail)))
	    (lambda-list-parse-error
	        lambda-list
		"Missing &WHOLE lambda variable."))
	(check-parameter-syntax nil (cadr tail) lambda-list)
	(if whole
	    (funcall whole (cadr tail)))
	(setq tail (cddr tail)))
    tail)


;;; Pop off the required arguments.  Stop when we hit the next lambda
;;; keyword.
;;; Destructuring syntax for the parameter is permitted.

(defun parse-lambda-required (lambda-list tail required destructure-p)
    (let ((arg  nil))
	(loop
	    (cond ((or (atom tail)
		       (lambda-keyword-p (setq arg (car tail))))
		   (return tail))
		  (t
		   (check-parameter-syntax destructure-p arg lambda-list)
		   (if required
		       (funcall required arg))))
	    (pop tail))))


;;; Pop off optional arguments.  Stop when we hit the next lambda keyword.
;;; Destructuring syntax for the parameter is permitted if the argument
;;; is a list, but destructuring of the supplied-p parameter is not
;;; permitted.

(defun parse-lambda-optional (lambda-list tail optional destructure-p)
    (when (and (consp tail) (eq (car tail) '&optional))
	(pop tail)
	(let ((arg   nil))
	    (loop
		(cond ((or (atom tail)
			   (lambda-keyword-p (setq arg (car tail))))
		       (return nil))
		      ((not (consp arg))
		       (check-parameter-syntax nil arg lambda-list)
		       (if optional
			   (funcall optional arg)))
		      (t
		       (check-parameter-syntax
			   destructure-p (car arg) lambda-list)
		       (check-optional-key-syntax '&optional arg lambda-list)
		       (if optional
			   (apply optional arg))))
		(pop tail))))
    tail)


;;; Look for &REST, &BODY, or dotted lambda list.  The latter two forms are
;;; permitted only if destructure-p is true.

(defun parse-lambda-rest (lambda-list tail rest destructure-p)
    (cond ((and (consp tail)
		(or (eq (car tail) '&rest)
		    (and destructure-p (eq (car tail) '&body))))
	   (if (or (atom (cdr tail)) (lambda-keyword-p (cadr tail)))
	       (lambda-list-parse-error
		   lambda-list
		   "Missing &REST lambda variable."))
	   (check-parameter-syntax destructure-p (cadr tail) lambda-list)
	   (if rest
	       (funcall rest (cadr tail)))
	   (cddr tail))
	  ((and tail (atom tail) destructure-p)
	   (check-parameter-syntax nil tail lambda-list)
	   (if rest
	       (funcall rest tail))
	   nil)
	  (t tail)))


;;; Process &KEY arguments.  Call the keyp function if &KEY appears.
;;; Call the key function for each argument.  Call the allow-other-keys-p
;;; function if &ALLOW-OTHER-KEYS appears.
;;; Destructuring syntax for the parameter is permitted if it is specified
;;; using ((key var) ...) syntax.  Destructuring of the supplied-p parameter
;;; is not permitted.

(defun parse-lambda-key (lambda-list tail keyp key allow-other-keys-p
				     destructure-p)
    (when (and (consp tail) (eq (car tail) '&key))
	(pop tail)
	(if keyp
	    (funcall keyp))
	(let ((arg  nil))
	    (loop
		(cond ((or (atom tail)
			   (lambda-keyword-p (setq arg (car tail))))
		       (return nil))
		      ((not (consp arg))
		       (check-parameter-syntax nil arg lambda-list)
		       (if key
			   (funcall key arg (keywordify arg))))
		      ((consp (car arg))
		       (check-parameter-syntax
			   destructure-p (second (car arg)) lambda-list)
		       (check-optional-key-syntax '&key arg lambda-list)
		       (if key
			   (apply key (second (car arg)) (first (car arg))
				  (cdr arg))))
		      (t
		       (check-parameter-syntax nil (car arg) lambda-list)
		       (check-optional-key-syntax '&key arg lambda-list)
		       (if key
			   (apply key (car arg) (keywordify (car arg))
				  (cdr arg)))))
		(pop tail))
	    (when (and (consp tail) (eq (car tail) '&allow-other-keys))
		(if allow-other-keys-p
		    (funcall allow-other-keys-p))
		(pop tail))))
    tail)


;;; Do the &aux parameters.  Destructuring syntax is permitted for
;;; the list form.

(defun parse-lambda-aux (lambda-list tail aux destructure-p)
    (when (and (consp tail) (eq (car tail) '&aux))
	(pop tail)
	(let ((arg  nil))
	    (loop
		(cond ((or (atom tail)
			   (lambda-keyword-p (setq arg (car tail))))
		       (return nil))
		      ((not (consp arg))
		       (check-parameter-syntax nil arg lambda-list)
		       (if aux
			   (funcall aux arg)))
		      (t
		       (check-parameter-syntax
			   destructure-p (car arg) lambda-list)
		       (if (cddr arg)
			   (lambda-list-parse-error
			       lambda-list
			       (format nil "Invalid &AUX syntax ~s." arg)))
		       (if aux
			   (apply aux arg))))
		(pop tail))))
    tail)



;;; Helper functions

;;; Map the symbol into the keyword package.

(defun keywordify (symbol)
  (intern (symbol-name symbol) (find-package :keyword)))


;;; Is the symbol a lambda-list-keyword?  Signal an error if we detect 
;;; problems with nonportable syntax.

(eval-when (eval compile load)
    (defconstant translator-lambda-list-keywords
	'(&optional &rest &key &allow-other-keys &aux
	  &environment &whole &body))
    (defconstant host-extension-lambda-list-keywords
	(set-difference lambda-list-keywords translator-lambda-list-keywords)))

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

(defun check-parameter-syntax (cons-allowed-p variable lambda-list)
    (if cons-allowed-p
	(if (not (or (symbolp variable) (consp variable)))
	    (lambda-list-parse-error
	        lambda-list
		(format nil
			"The lambda parameter ~s is not a symbol or a list."
			variable)))
	(if (not (symbolp variable))
	    (lambda-list-parse-error
	        lambda-list
		(format nil
			"The lambda parameter ~s is not a symbol." variable)))
	))


;;; Check syntax of optional/key parameter lists: make sure that the
;;; supplied-p var (if there is one) is a symbol and that the list isn't
;;; too long.

(defun check-optional-key-syntax (which arg lambda-list)
    (if (cddr arg)
	(check-parameter-syntax nil (caddr arg) lambda-list))
    (if (cdddr arg)
	(lambda-list-parse-error
	    lambda-list
	    (format nil "Invalid ~s argument syntax ~s." which arg))))


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

(defmacro destructure-keyword-value (tail key init svar)
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
		    
;; *** There is nothing here to do exact key checking of keyword arguments.

(defvar *destructure-key-svar* (make-symbol "key suppliedp"))

(defun destructure-aux (lambda-list tail-var bindings default-init
				    &aux (key-svar nil))
  (flet ((whole-fn (arg)
	     (push `(,arg ,tail-var) bindings))
	 (required-fn (arg)
	     (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
		 (push `(,name (pop ,tail-var)) bindings)
		 (if destructure-p
		     (setq bindings
			   (destructure-aux arg name bindings default-init)))))
	 (optional-fn (arg &optional (init default-init)
			             (svar nil svar-p))
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
	       (if destructure-p
		   (setq bindings
			 (destructure-aux arg name bindings default-init)))))
	 (rest-fn (arg)
	     (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
		 (push `(,name ,tail-var) bindings)
		 (if destructure-p
		     (setq bindings
			   (destructure-aux arg name bindings default-init)))))
	 (key-fn (arg keyword &optional (init default-init)
		                        (svar nil svar-p))
	     (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
	       (when (and svar-p (null key-svar))
		 ;; If this is the first time we've encountered a suppliedp
		 ;; variable for a keyword parameter, initialize key-svar (so
		 ;; we know we've done this part) and add a binding of the
		 ;; common suppliedp variable.
		 (setf key-svar *destructure-key-svar*)
		 (push `(,key-svar nil) bindings))
	       (push `(,name (destructure-keyword-value
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
	       (if destructure-p
		   (setq bindings
			 (destructure-aux arg name bindings default-init)))))
	 (aux-fn (arg &optional init)
	     (multiple-value-bind (name destructure-p)
		     (check-destructuring-parameter arg lambda-list)
		 (push `(,name ,init) bindings)
		 (if destructure-p
		     (setq bindings
			   (destructure-aux arg name bindings nil))))))
	(parse-lambda-list lambda-list
	    :whole          #'whole-fn
	    :required       #'required-fn
	    :optional       #'optional-fn
	    :rest           #'rest-fn
	    :key            #'key-fn
	    :aux            #'aux-fn
	    :destructure-p  t))
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


(defmacro HOST:DESTRUCTURING-BIND
  (lambda-list expression &body body)
  (if lambda-list
      (let ((whole  (make-symbol "WHOLE")))
	`(let* ,(nreverse (destructure-aux lambda-list
					   whole
					   (list `(,whole ,expression)) nil))
	   ,@body))
      ;; let so that result is not at top level
      `(let ()
	 ,@body)))

;;; PARSE-MACRO

(eval-when (compile load eval)

  (defvar *macro-whole*  (make-symbol "WHOLE"))
  (defvar *macro-env*    (make-symbol "ENV"))

  )

(defun HOSTX:PARSE-MACRO (name lambda-list body &optional environment)
  (multiple-value-bind (body decls doc)
      (excl::parse-body body environment)
    (flet ((extract-environment (lambda-list)
	     (do ((tail lambda-list (cdr tail)))
		 ((endp tail) (values nil lambda-list))
	       (when (eq (car tail) '&environment)
		 (return (values (cadr tail)
				 (nconc (ldiff lambda-list tail)
					(cddr tail)))))))
	   (extract-whole (lambda-list)
	     (if (eq (car lambda-list) '&whole)
		 (values (cadr lambda-list) (cddr lambda-list))
		 (values nil lambda-list)))
	   (block-name (name)
	     (if (and (consp name)
		      (eq (car name) 'setf))
		 (cadr name)
		 name)))
      (multiple-value-bind (whole lambda-list)
	  (extract-whole lambda-list)
	(multiple-value-bind (env lambda-list)
	    (extract-environment lambda-list)
	  (let ((destructure *macro-whole*))
	    (when env
	      (push env lambda-list)
	      (setf destructure `(cons ,*macro-env* ,destructure)))
	    (when whole
	      (push whole lambda-list)
	      (setf destructure `(cons ,*macro-whole* ,destructure)))
	    `(lambda (,*macro-whole* ,*macro-env*)
	       ,@(when doc (list doc))
	       ,@(when (null env) `((declare (ignore ,*macro-env*))))
	       (destructuring-bind ,lambda-list
				   ,destructure
		 ,@decls
		 (block ,(block-name name) ,@body)))))))))

;;; WITH-COMPILATION-UNIT
;;; Allegro seems to lack any way to acheive the functionality
;;; of with-compilaton-unit, so we'll just ignore it.

(defmacro HOST:WITH-COMPILATION-UNIT (options &body body)
  (declare (ignore options))
  `(progn ,@body))

;;; These variables are standard in ANSI common lisp but not supported
;;; yet by Lucid.  TRANSLATE-FILE uses them.

(defvar host:*compile-file-pathname* nil)
(defvar host:*compile-file-truename* nil)

;;; renamed SETF stuff

#+ALLEGRO-V4.0
(defmacro host:define-setf-expander (&rest stuff)
  `(lisp:define-setf-method ,@stuff))

#+ALLEGRO-V4.0
(defun host:get-setf-expansion (form &optional env)
  (lisp:get-setf-method-multiple-value form env))

;;; renamed special-form-p

#+ALLEGRO-V4.0
(defun host:special-operator-p (thing)
  (CLTL1:special-form-p thing))


;;; things with environment arguments added

(defun host:constantp (thing &optional env)
    (declare (ignore env))
    (lisp:constantp thing))

(defun host:typep (thing type &optional env)
    (declare (ignore env))
    (lisp:typep thing type))

(defun host:subtypep (type1 type2 &optional env)
    (declare (ignore env))
    (lisp:subtypep type1 type2))

;;; do-symbols and friends should take a package name, where allegro
;;; only accepts a package

(defun package-designator-to-package (p)
  (if (or (symbolp p) (stringp p))
      (find-package p)
      p))

(defmacro HOST:DO-EXTERNAL-SYMBOLS
  ((var &optional
	(package nil package-supplied-p)
	(result nil result-supplied-p))
   &body body)
  `(lisp:do-external-symbols (,var ,@(if package-supplied-p
					 `((package-designator-to-package
					   ,package))
					 nil)
				   ,@(if result-supplied-p
					 (list result)
					 nil))
			     ,@body))

(defmacro HOST:DO-SYMBOLS
  ((var &optional
	(package nil package-supplied-p)
	(result nil result-supplied-p))
   &body body)
  `(lisp:do-symbols (,var ,@(if package-supplied-p
					 `((package-designator-to-package
					   ,package))
					 nil)
				   ,@(if result-supplied-p
					 (list result)
					 nil))
			     ,@body))

(defun hostx:delq (item list)
  (loop (unless list
	  (return-from hostx:delq list))
	(unless (eq item (car list))
	  (return nil))
	(setq list (cdr list)))
  (let* ((tail list)
	 (next (cdr tail)))
    (loop (unless next
	    (return-from hostx:delq list))
	  (if (eq item (car next))
	      (setf next (cdr next)
		    (cdr tail) next)
	      (setf tail next
		    next (cdr tail))))))

(defmacro hostx:with-dynamic-area (&body forms)
  `(progn ,@forms))

;Can't do this in allegro:  static allocation is for arrays only,
;and it means what Lucid calls read-write allocation: neither collected
;nor scanned by gc.
(defmacro hostx:with-static-area (&body forms)
  `(progn ,@forms))


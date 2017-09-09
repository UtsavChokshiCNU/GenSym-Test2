;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION -*-
;;;
;;; lucid-5-defs.lisp -- host compatibility functions 
;;; for Lucid 5.0
;;;
;;; author :  Sandra Loosemore (from original by Kim Barrett)
;;; date   :  30 Jan 1991
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.
;;;

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/lucid-5-defs.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007-11-15 20:05:33 $")

#-LCL5.0
#.(error "Attempting to use incorrect host database.
This file is for Lucid Common Lisp version 5.0.")

;(define-condition simple-program-error (simple-condition program-error) ())
;    
;(defun simple-program-error (format-control &rest arguments)
;  (error 'simple-program-error
;	   :format-control format-control
;	   :format-arguments arguments))

;;; This is the only portable way I can see to do this, and the nonportable
;;; ways take more effort than seems worth it at this point, if we want
;;; user-defined types to work properly.

(defun HOST:UPGRADED-ARRAY-ELEMENT-TYPE (type &optional env)
  (when env
    (warn "Ignoring environment argument ~A to upgraded-array-element-type"
	  env))
  (let ((array (make-array 1 :element-type type)))
    (array-element-type array)))
  
(defun simple-program-error (format-control &rest arguments)
  (apply #'error format-control arguments))


;;; Define ANSI FDEFINITION and its SETF, and modify FBOUNDP and FMAKUNBOUND
;;; to permit SETF function names as arguments.  This requires that there
;;; exists an implementation specific function which takes a SETF function
;;; name and returns a corresponding symbol.
#+clos
(progn

  ;; Specify the function to call to coerce a SETF function name into a symbol.
  (defvar *function-name-to-function*
    'clos::normalize-spec-name-runtime)

  (flet ((coerce-name-to-symbol (name)
	   (cond ((symbolp name) name)
		 ((and (consp name)
		       (eq (car name) 'setf)
		       (consp (cdr name))
		       (null (cddr name))
		       (symbolp (cadr name)))
		  (funcall *function-name-to-function* name))
		 (t
		  (simple-program-error "~S is not a valid function name."
					name)))))
    
    (defun HOST:FBOUNDP (name)
      (fboundp (coerce-name-to-symbol name)))

    (defun HOST:FDEFINITION (name)
      (let ((coerced-name (coerce-name-to-symbol name)))
	(if (fboundp coerced-name)
	    (symbol-function coerced-name)
	    (error 'undefined-function :name name))))

    (defun set-fdefinition (name value)
      (setf (symbol-function (coerce-name-to-symbol name)) value))

    (defsetf host:fdefinition set-fdefinition)

    (defun HOST:FMAKUNBOUND (name)
      (fmakunbound (coerce-name-to-symbol name))
      name)                    ; return original name

    )
  )

;;; Define ANSI version of LAST, which now takes an optional second argument.
(defun HOST:LAST (list &optional (n 1))
  (if (eql n 1)
      (last list)
      (do ((head list (cdr head))
	   (tail (do ((tail list (cdr tail)))
		     ((or (atom tail) (minusp (decf n))) tail))
		 (cdr tail)))
	  ((atom tail) head))))

(eval-when (compile load eval)
; Note that Lucid's compiler macro semantics does not use have the
; feature that returning the &whole argument means stop expanding.
(setf (macro-function 'host:define-compiler-macro)
      (macro-function 'lcl:def-compiler-macro))
)

;;; For implementations which support DEFINE-COMPILER-MACRO, but which do
;;; not support the optional second argument to LAST, provide a compiler
;;; macro which transforms case where second argument is constant 1 into
;;; call to the single argument function.

;(host:define-compiler-macro host:last (&whole whole list &optional (n 1))
;  (if (and (constantp n) (eql (eval n) 1))
;      `(last ,list)
;      whole))

;;; Fix some bugs in Lucid 4.0.
;;; The compiler database has incorrect argument information for FIND-CLASS,
;;; so generates warning when compiling a call that includes the environment
;;; argument.  SETF function for FIND-CLASS doesn't accept the environment
;;; argument and may signal an error for two many arguments if called with
;;; one.

#+clos
(progn
(defun HOST:FIND-CLASS (name &optional (errorp t) environment)
  (declare (ignore environment))
  (clos:find-class name errorp))

(defun set-find-class (value name &optional errorp env)
  (declare (ignore errorp env))
  (setf (clos:find-class name) value))

(define-setf-method host:find-class (name &optional errorp env)
  (let ((vars (cons (gensym)
		    (cond (env (list (gensym) (gensym)))
			  (errorp (list (gensym)))
			  (t nil))))
	(vals (cons name
		    (cond (env (list errorp env))
			  (errorp (list errorp))
			  (t nil))))
	(store (gensym)))
    (values vars
	    vals
	    (list store)
	    `(set-find-class ,store ,@vars)
	    `(host:find-class ,@vars))))
)

;;; Define ANSI semantics GENSYM

(defvar HOST:*GENSYM-COUNTER* 0)

(defun HOST:GENSYM (&optional (prefix "G") &aux index)
  (etypecase prefix
    (string
     (when (not (typep (setf index host:*gensym-counter*) '(integer 0)))
       (lcl:restart-case
	   (error 'lcl:simple-type-error
		  :datum index
		  :expected-type '(integer 0)
		  :format-string
		    "The value of ~S is not a non-negative integer: ~S."
		  :format-arguments (list 'host:*gensym-counter* index))
	 (lcl:continue ()
	   :report (lambda (s)
		     (format s "Reset ~S to 0." 'host:*gensym-counter*))
	   (setf host:*gensym-counter* (setf index 0)))
	 (nil ()
	   :report (lambda (s)
		     (format s "Retry call to ~S." 'host:gensym))
	   (return-from host:gensym (host:gensym prefix)))))
     (incf host:*gensym-counter*))
    ((integer 0) (shiftf index prefix "G")))
  (make-symbol (format nil "~A~D" prefix index)))

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

;;; DECLAIM

(defmacro HOST:DECLAIM (&rest specs)
  `(eval-when (compile load eval)
     ,@(mapcar #'(lambda (spec) `(proclaim ',spec))
	       specs)))

;;; FORMATTER

(defmacro HOST:FORMATTER (string)
  (check-type string string)
  `(make-formatter ,string))

(defun make-formatter (string)
  (flet ((formatter-function (stream &rest arguments)
	   (apply #'format stream string arguments)))
    #'formatter-function))

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

(lcl:define-condition HOST:PARSE-ERROR (error) ())

;;; PRINT-UNREADABLE-OBJECT and friends.

(defvar HOST:*PRINT-READABLY* nil)

(lcl:define-condition HOST:PRINT-NOT-READABLE (error)
    (object)
  (:report
   (lambda (c s)
     ;; Careful to prevent recursive error when printing object for reporting.
     (let ((host:*print-readably* nil))
       (format s "Cannot print object readably: ~S."
	       (host:print-not-readable-object c))))))

;;; Because Lucid DEFINE-CONDITION doesn't support specifying reader name yet.
(defun HOST:PRINT-NOT-READABLE-OBJECT (c)
  (print-not-readable-object c))
	
(eval-when (compile load eval)

  (defvar *print-unreadable-object*      (make-symbol "Object"))
  (defvar *print-unreadable-stream*      (make-symbol "Stream"))
  (defvar *print-unreadable-type*        (make-symbol "Type"))
  (defvar *print-unreadable-identity*    (make-symbol "Identity"))

  )

;;; *** What is the return value of this supposed to be?
;;; *** For now, we are returning the object.
(defmacro HOST:PRINT-UNREADABLE-OBJECT
          ((object stream &rest keys &key type identity) &body body)
  (declare (ignore type identity))
  (let ((bodyp
	 ;; Note that this might be misleading if body were to consist only of
	 ;; declarations.  However, as there is no portable use for such a
	 ;; body, we'll ignore that possibility.
	 (and body t)))
    ;; This lambda form ensures that we get left to right evaluation order for
    ;; the keyword arguments, and that the keyword arguments are all evaluated
    ;; before any of the body forms are executed.  We could try to optimize
    ;; away constant keywords, but this code would then become much more
    ;; complex, and the benefit for doing so is pretty minimal.  Besides, thats
    ;; really a compiler's job.
    `((lambda (,*print-unreadable-object*
	       ,*print-unreadable-stream*
	       &key ((:type ,*print-unreadable-type*) nil)
	            ((:identity ,*print-unreadable-identity*) nil))
	(begin-print-unreadable-object ,*print-unreadable-object*
				       ,*print-unreadable-stream*
				       ,*print-unreadable-type*
				       ,*print-unreadable-identity*
				       ,bodyp)
	;; Permit declarations at front of body
	(locally ,@body)
	(finish-print-unreadable-object ,*print-unreadable-object*
					,*print-unreadable-stream*
					,*print-unreadable-identity*
					,bodyp))
      ,object ,stream ,@keys)))

(defun begin-print-unreadable-object (object stream type identity bodyp)
  ;; Signal an error if *print-readably* is true.
  (when host:*print-readably*
    (lcl:restart-case
        (error 'host:print-not-readable :object object)
      ;; Give the user the option of printing the object unreadably anyway.
      (lcl:continue ()
	:report (lambda (s)
		  ;; Careful to prevent recursive error when printing object
		  ;; and stream for reporting.
		  (let ((host:*print-readably* nil))
		    (format s "Print an unreadable representation of ~S on ~S."
			    object stream))))))
  ;; Start printing unreadable representation of object.
  (write-string "#<" stream)
  (when type
    ;; If type is indicated, print the type of the object.
    (prin1 (type-of object) stream)
    ;; If anything is going to follow type, print a space now.
    (when (or identity bodyp)
      (write-char #\Space stream))))

(defun finish-print-unreadable-object (object stream identity bodyp)
  (when identity
    (when bodyp (write-char #\Space stream))
    (write-string "#x" stream)
    (let ((*print-base* 16))
      (prin1 (sys:%pointer object) stream)))
  (write-char #\> stream)
  object)

;;; REAL type

(deftype HOST:REAL (&optional low high)
  (make-real-type-specifier low high))
  
(defun make-real-type-specifier (low high)
  (labels ((rationalize-range (value &optional (permit-cons t))
	     (typecase value
	       ((member *) value)
	       (cons
		(if permit-cons
		    (let ((value (rationalize-range (car value) nil)))
		      (if (eq value '*) '* (list value)))
		    (invalid-range (list value))))
	       (rational value)
	       (float (rational value))
	       (t (invalid-range value))))
	   (float-upper (value)
	     (typecase value
	       ((member *) value)
	       (rational
		(cond ((< most-positive-long-float value) '*)
		      ((< value most-negative-long-float) nil)
		      (t (coerce value 'long-float))))
	       (cons
		(let ((value (car value)))
		  (cond ((<= most-positive-long-float value) '*)
			((<= value most-negative-long-float) nil)
			(t (list (coerce value 'long-float))))))
	       (t (invalid-range value))))
	   (float-lower (value)
	     (typecase value
	       ((member *) value)
	       (rational
		(cond ((< value most-negative-long-float) '*)
		      ((< most-positive-long-float value) nil)
		      (t (coerce value 'long-float))))
	       (cons
		(let ((value (car value)))
		  (cond ((<= value most-negative-long-float) '*)
			((<= most-positive-long-float value) nil)
			(t (coerce value 'long-float)))))
	       (t (invalid-range value))))
	   (empty-range-p (low high)
	     (typecase low
	       ((member *) nil)
	       (rational
		(typecase high
		  ((member *) nil)
		  (rational (< high low))
		  (cons (<= (car high) low))
		  (t (invalid-range high))))
	       (cons
		(typecase high
		  ((member *) nil)
		  (rational (<= high (car low)))
		  (cons (<= (car high) (car low)))
		  (t (invalid-range high))))
	       (t (invalid-range low))))
	   (invalid-range (value)
	     (error "Invalid REAL range value: ~S." value))
	   (make-typespec (type low high)
	     (cond ((not (eq high '*)) `(,type ,low ,high))
		   ((eq low '*) type)
		   (t `(,type ,low))))
	   )
    (setf low (rationalize-range low))
    (setf high (rationalize-range high))
    (if (empty-range-p low high) 'nil
	(let ((float-low (float-lower low))
	      (float-high (float-upper high)))
	  (if (or (null float-low) (null float-high))
	      (make-typespec 'rational low high)
	      `(or ,(make-typespec 'rational low high)
		   ,(make-typespec 'float float-low float-high)))))))
	       
(defun HOST:REALP (object)
  (or (rationalp object)
      (floatp object)))
  
;;; SIMPLE-CONDITION-FORMAT-CONTROL

(defun HOST:SIMPLE-CONDITION-FORMAT-CONTROL (c)
  (lcl:simple-condition-format-string c))

;;; STYLE-WARNING

(lcl:define-condition HOST:STYLE-WARNING (lcl:warning) ())

;;; Iterators
;;;
;;; These aren't very efficient, but should do for now.

(defmacro HOST:WITH-HASH-TABLE-ITERATOR
          ((mname table) &body body &environment env)
  (multiple-value-bind (body decls)
      (lcl:parse-body body env nil)
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

;;; PARSE-MACRO

(eval-when (compile load eval)

  (defvar *macro-whole*  (make-symbol "WHOLE"))
  (defvar *macro-env*    (make-symbol "ENV"))

  )

(defun HOSTX:PARSE-MACRO (name lambda-list body &optional environment)
  (multiple-value-bind (body decls doc)
      (lcl:parse-body body environment)
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

(defmacro HOST:WITH-COMPILATION-UNIT (options &body body)
  (let ((override (gensym)))
    `((lambda (&key ((:override ,override) nil))
	(with-compiler-options (:undef-warnings ,override) ,@body))
      ,@options)))

;;; WITH-STANDARD-IO-SYNTAX

(defmacro HOST:WITH-STANDARD-IO-SYNTAX (&body body)
  (let ((vars (gensym))
	(vals (gensym)))
    `(multiple-value-bind (,vars ,vals)
         (standard-io-syntax-bindings)
       (progv ,vars ,vals (locally ,@body)))))

(defvar *standard-io-syntax-bindings* (make-hash-table))

(defmacro define-standard-io-syntax-binding (name &body body)
  `(setf (gethash ',name *standard-io-syntax-bindings*) #'(lambda () ,@body)))

(defun standard-io-syntax-bindings ()
  (let ((vars nil)
	(vals nil))
    (maphash #'(lambda (key value)
		 (push key vars)
		 (push (funcall value) vals))
	     *standard-io-syntax-bindings*)
    (values vars vals)))

(define-standard-io-syntax-binding HOST:*PACKAGE* (find-package "USER"))

(define-standard-io-syntax-binding HOST:*PRINT-ARRAY* t)
(define-standard-io-syntax-binding HOST:*PRINT-BASE* 10)
(define-standard-io-syntax-binding HOST:*PRINT-CASE* :upcase)
(define-standard-io-syntax-binding HOST:*PRINT-CIRCLE* nil)
(define-standard-io-syntax-binding HOST:*PRINT-ESCAPE* t)
(define-standard-io-syntax-binding HOST:*PRINT-GENSYM* t)
(define-standard-io-syntax-binding HOST:*PRINT-LENGTH* nil)
(define-standard-io-syntax-binding HOST:*PRINT-LEVEL* nil)
(define-standard-io-syntax-binding HOST:*PRINT-LINES* nil)
(define-standard-io-syntax-binding HOST:*PRINT-MISER-WIDTH* nil)
(define-standard-io-syntax-binding HOST:*PRINT-PPRINT-DISPATCH* nil)
(define-standard-io-syntax-binding HOST:*PRINT-PRETTY* nil)
(define-standard-io-syntax-binding HOST:*PRINT-RADIX* nil)
(define-standard-io-syntax-binding HOST:*PRINT-READABLY* t)
(define-standard-io-syntax-binding HOST:*PRINT-RIGHT-MARGIN* nil)

(define-standard-io-syntax-binding HOST:*READ-BASE* 10)
(define-standard-io-syntax-binding HOST:*READ-DEFAULT-FLOAT-FORMAT*
  'single-float)
(define-standard-io-syntax-binding HOST:*READ-SUPPRESS* nil)
(define-standard-io-syntax-binding HOST:*READ-EVAL* t)

(defvar *standard-io-syntax-readtable* (copy-readtable nil))
(define-standard-io-syntax-binding HOST:*READTABLE*
  *standard-io-syntax-readtable*)

;;; These variables are standard in ANSI common lisp but not supported
;;; yet by Lucid.  TRANSLATE-FILE uses them.

(defvar host:*compile-verbose* t)
(defvar host:*compile-print* nil)
(defvar host:*compile-file-pathname* nil)
(defvar host:*compile-file-truename* nil)


;;; renamed SETF stuff

(defmacro host:define-setf-expander (&rest stuff)
    `(lisp:define-setf-method ,@stuff))

(defun host:get-setf-expansion (form &optional env)
    (lisp:get-setf-method-multiple-value form env))


;;; renamed special-form-p

(defun host:special-operator-p (thing)
    (lisp:special-form-p thing))


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


(defvar *load-truename* nil)

(defun host:compiler-macro-function (name &optional env)
  (declare (ignore name env))
  (error "Not implemented."))

(defsetf host:compiler-macro-function (name &optional env) (value)
  (declare (ignore name env value))
  `(error "Not implemented."))

(defun hostx:declaration-information (name &optional env)
  (declare (ignore name env))
  (error "Not implemented."))

(defun hostx:enclose (lambda-expression &optional env)
  (declare (ignore lambda-expression env))
  (error "Not implemented."))

(defun hostx:function-information (name &optional env)
  (declare (ignore name env))
  (error "Not implemented."))

(defun host:upgraded-complex-part-type (type &optional env)
  (declare (ignore type env))
  (error "Not implemented."))

(defun hostx:variable-information (name &optional env)
  (declare (ignore name env))
  (error "Not implemented."))


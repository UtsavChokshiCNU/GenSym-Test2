;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; misc.lisp -- miscellaneous macros and stuff
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  05 Jul 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/misc.lisp,v $"
 "$Revision: 1.10 $"
 "$Date: 2007/07/10 16:57:57 $")

;;; The symbol iterators depend on using helper functions in the runtime
;;; library to construct state objects that encapsulate the state of the
;;; iteration, and to step the iteration along.
;;; *** It's not 100% clear from CLtL what the scope of the NIL block is.
;;; *** I've made it like DO in that it includes the entire form.

(define-translator-macro do-symbols ((var &optional (package '*package) result)
				     &body body)
    (multiple-value-bind (real-body decls) (parse-body body nil)
	(let ((statevar    (make-symbol "STATE")))
	    `(do ((,statevar  (trun:initialize-do-symbols-iterator ,package))
		  (,var       nil))
		 (nil)
		 (declare ,@decls)
		 (multiple-value-setq (,var ,statevar)
			 (trun:advance-do-symbols-iterator ,statevar))
		 (if (null ,statevar)
		     (return ,result))
		 ,@real-body)
	    )))


(define-translator-macro do-external-symbols ((var &optional
						   (package '*package*) result)
					      &body body)
    (multiple-value-bind (real-body decls) (parse-body body nil)
	(let ((statevar    (make-symbol "STATE")))
	    `(do ((,statevar  (trun:initialize-do-external-symbols-iterator
			          ,package))
		  (,var       nil))
		 (nil)
		 (declare ,@decls)
		 (multiple-value-setq (,var ,statevar)
			 (trun:advance-do-symbols-iterator ,statevar))
		 (if (null ,statevar)
		     (return ,result))
		 ,@real-body)
	    )))


(define-translator-macro do-all-symbols ((var &optional result) &body body)
    (multiple-value-bind (real-body decls) (parse-body body nil)
	(let ((statevar    (make-symbol "STATE")))
	    `(do ((,statevar  (trun:initialize-do-all-symbols-iterator))
		  (,var       nil))
		 (nil)
		 (declare ,@decls)
		 (multiple-value-setq (,var ,statevar)
			 (trun:advance-do-symbols-iterator ,statevar))
		 (if (null ,statevar)
		     (return ,result))
		 ,@real-body)
	    )))

(define-translator-macro with-package-iterator
        ((mname package-list &rest symbol-types) &body body)
    (if (or (null symbol-types)
	    (not (every #'(lambda (x)
			      (member x '(:internal :external :inherited)))
			symbol-types)))
	(error "Bad symbol-types argument ~s to WITH-PACKAGE-ITERATOR."
	       symbol-types))
    (let ((statevar     (make-symbol "STATE"))
	  (internal-p   (if (member :internal symbol-types) t nil))
	  (external-p   (if (member :external symbol-types) t nil))
	  (inherited-p  (if (member :inherited symbol-types) t nil)))
	`(let ((,statevar  (trun:initialize-with-package-iterator ,package-list
			       ,internal-p ,external-p ,inherited-p)))
	     (macrolet ((,mname ()
			    `(trun:advance-with-package-iterator ,',statevar)))
	         ,@body))))



;;; print-unreadable-object
;;; *** What should the return value for this be?
;;; *** For now we return the object.

(define-translator-macro print-unreadable-object
        ((object stream &rest keys &key type identity) &body body)
  (declare (ignore type identity))
  (let ((bodyp         (and (parse-body body nil) t))
	(object-var    (make-symbol "OBJECT"))
	(stream-var    (make-symbol "STREAM"))
	(type-var      (make-symbol "TYPE"))
	(identity-var  (make-symbol "IDENTITY")))
    ;; This lambda form ensures that we get left to right evaluation order for
    ;; the keyword arguments, and that the keyword arguments are all evaluated
    ;; before any of the body forms are executed.  We could try to optimize
    ;; away constant keywords, but this code would then become much more
    ;; complex, and the benefit for doing so is pretty minimal.  Besides, thats
    ;; really a compiler's job.
    `((lambda (,object-var
	       ,stream-var
	       &key ((:type ,type-var) nil)
	            ((:identity ,identity-var) nil))
	(trun:begin-print-unreadable-object
	    ,object-var ,stream-var ,type-var ,identity-var ,bodyp)
	;; Permit declarations at front of body
	(locally ,@body)
	(trun:finish-print-unreadable-object
	    ,object-var ,stream-var ,identity-var ,bodyp))
      ,object ,stream ,@keys)))

;;; *** The following two functions need to be in the runtime system.  Either
;;; *** the following code could translated and used, or these can be rewritten
;;; *** in C.  If this code is translated and used, then the primitive
;;; *** 'address-of' needs to be added to the runtime system.

;(defun begin-print-unreadable-object (object stream type identity bodyp)
;  ;; Signal an error if *print-readably* is true.
;  (when *print-readably*
;    ;; *** Until condition system is implemented
;    (let ((*print-readably* nil))
;      (error "Cannot print object readably: ~S." object))
;    ;; *** Use this once condition system exists.
;    ;(restart-case
;    ;    (error 'print-not-readable :object object)
;    ;  ;; Give the user the option of printing the object unreadably anyway.
;    ;  (continue ()
;    ;	:report (lambda (s)
;    ;		  ;; Careful to prevent recursive error when printing object
;    ;		  ;; and stream for reporting.
;    ;		  (let ((*print-readably* nil))
;    ;		    (format s "Print an unreadable representation of ~S on ~S."
;    ;			    object stream)))))
;    )
;  ;; Start printing unreadable representation of object.
;  (write-string "#<" stream)
;  (when type
;    ;; If type is indicated, print the type of the object.
;    (prin1 (type-of object) stream)
;    ;; If anything is going to follow type, print a space now.
;    (when (or identity bodyp)
;      (write-char #\Space stream))))
;
;(defun finish-print-unreadable-object (object stream identity bodyp)
;  (when identity
;    (when bodyp (write-char #\Space stream))
;    (write-string "#x" stream)
;    (let ((*print-base* 16))
;      (prin1 (address-of object) stream)))
;  (write-char #\> stream)
;  object)


;;; psetq
;;; transform into PSETF if any of the variables are really symbol-macros.

(define-translator-macro psetq (&rest var-value-pairs &environment env)
  (if (psetq-variables-are-really-variables-p var-value-pairs env)
      (multiple-value-bind (bindings setqs)
	  (psetq-aux var-value-pairs env nil)
	(if bindings
	    `(let ,bindings ,@setqs nil)
	    `(progn ,@setqs nil)))
      `(psetf ,@var-value-pairs)))

(defun psetq-variables-are-really-variables-p (var-value-pairs env)
  (cond ((null var-value-pairs)
	 t)
	((null (cdr var-value-pairs))
	 (error "Odd-length argument list to PSETQ: ~s" var-value-pairs))
	(t
	 (let* ((var  (car var-value-pairs))
		(exp  (translator-macroexpand-1 var env)))
	   (cond ((eq var exp)
		  (psetq-variables-are-really-variables-p
		   (cddr var-value-pairs) env))
		 ((symbolp exp)
		  (psetq-variables-are-really-variables-p
		   (cons exp (cdr var-value-pairs)) env))
		 (t
		  nil))))))
    

;;; Try to avoid generating unnecessary temporaries whenever possible.
;;; The idea is to not generate a temporary if we know that the value-form
;;; is a constant or variable that is not affected by the previous
;;; assignments.  Besides making sure that the assignments don't change
;;; the values of the value-forms, we also have to watch out for
;;; order-of-evaluation issues here to make sure that the side-effects
;;; of the value-forms all happen in the correct order.

(defun psetq-aux (var-value-pairs env variables)
  (cond ((null var-value-pairs)
	 (values nil nil))
	(t
	 (let* ((var   (car var-value-pairs))
		(value (cadr var-value-pairs))
		(exp   (apply-macros value env)))
	   (multiple-value-bind (bindings setqs)
	       (psetq-aux (cddr var-value-pairs) env
			  (cons var variables))
	     (if (or (null variables)
		     (translator-constantp exp env)
		     (and (atom exp)
			  (not (member exp variables))))
		 (push `(setq ,var ,value) setqs)
		 (let ((temp (make-symbol (sformat "~a-TEMP" var))))
		   (push `(,temp ,value) bindings)
		   (push `(setq ,var ,temp) setqs)))
	     (values (nreverse bindings) setqs))))))


;;; return

(define-translator-macro return (&optional value)
  `(return-from nil ,value))


;;; step
;;; *** bogus, we have no interactive debugger.

(define-translator-macro step (form)
    form)


;;; time

(define-translator-macro time (form)
    (let ((run-time  (make-symbol "RUN-TIME"))
	  (real-time (make-symbol "REAL-TIME")))
	`(multiple-value-bind (,run-time ,real-time) (trun:begin-time)
	     (declare (integer ,run-time ,real-time))
	     (multiple-value-prog1 ,form
		 (trun:finish-time ,run-time ,real-time)))
	))



;;; trace
;;; untrace
;;; *** more bogosity.

(define-translator-macro trace (&rest args)
    (declare (ignore args))
    (error "TRACE is not supported."))

(define-translator-macro untrace (&rest args)
    (declare (ignore args))
    (error "UNTRACE is not supported."))


;;; with-compilation-unit
;;; well, this is correct but not very interesting.

(define-translator-macro with-compilation-unit (options &body body)
    (declare (ignore options))
    `(progn ,@body))


;;; with-hash-table-iterator
;;; makes use of two helper functions, init-hash-table-iterator-state
;;; and hash-table-iterator.
;;; Note that the "obvious" iteration mechanism for hash tables fails
;;; because the GC might be invoked and the hash table rehashed while
;;; the iteration is in progress!  I think that in general, we need
;;; to cons up an uninitialized a-list with hash-table-count entries,
;;; then use the obvious technique to iterate over the hash table and
;;; fill in the entries in the a-list (being very careful to do nothing
;;; which allocates heap storage in the process), and then just cdr
;;; down this list.  We *can* allocate the a-list on the Lisp stack,
;;; though, since it has dynamic extent.  This all applies to MAPHASH 
;;; as well as WITH-HASH-TABLE-ITERATOR.

;;; The odd use of two ending functions is necessitated by the different
;;; possible runtime implementations, some of which need a termination function
;;; that only gets run on a normal exit from the iterator while others need
;;; something run on all forms of termination.  The protocol used here was the
;;; result of long discussions between Barrett, Nizhegorodov, and O'Toole about
;;; how to structure this macro to make it insensitive to the particular
;;; implementation being used by the RTL. -- kab, 8/5/91

(define-translator-macro with-hash-table-iterator
      ((mname hash-table) &body body)
  (let ((state (make-symbol "STATE")))
    `(let ((,state nil))
       (declare (dynamic-extent ,state))
       (unwind-protect
	   (progn
	     ;; Careful to evaluate hash-table form outside macro binding.
	     (setf ,state (trun:begin-hash-table-iterator ,hash-table))
	     (multiple-value-prog1
		 (macrolet ((,mname () `(trun:hash-table-iterator ,',state)))
		   ,@body)
	       (trun:end-hash-table-iterator ,state)))
	 (trun:cleanup-hash-table-iterator ,state)))))

;;; *** It isn't clear whether these WITH-xxx guys that bind variables to
;;; *** streams permit assignment to the variable within the body.  If so,
;;; *** we need to introduce another "hidden" variable so that we have
;;; *** a guaranteed handle to the stream to close it on the way out.  Also
;;; *** all of the declarations would apply only to the "hidden" variable.
;;; *** It's also not clear whether the language in CLtL about the streams
;;; *** having dynamic extent means dynamic extent in the ANSI CL sense.

;;; with-input-from-string
;;; *** When the runtime library is more complete, it might turn out that
;;; *** closing a string stream doesn't do anything useful.  In that case
;;; *** we could omit the unwind-protect and close and simplify this a bit.

(define-translator-macro with-input-from-string
        ((var string &key index start end) &body body)
    (multiple-value-bind (real-body decls) (parse-body body nil)
	(if index
	    (setq real-body
		  `((multiple-value-prog1
		            (progn ,@real-body)
		        (setf ,index (trun:string-stream-index ,var))))))
	`(let ((,var  (make-string-input-stream ,string
		          ,@(if start `(:start ,start))
		          ,@(if end   `(:end ,end)))))
	     (declare (type string-stream ,var)
		      (dynamic-extent ,var) ,@decls)
	     (unwind-protect (progn ,@real-body)
	         (close ,var)))
	))

;;; with-open-file
;;; CLtL does not require that the stream opened by WITH-OPEN-FILE has
;;; dynamic extent.
;;; It does say that the variable might be bound to something other than
;;; a stream if :if-does-not-exist NIL is specified.
;;; These two things mean that WITH-OPEN-FILE cannot be implemented in
;;; terms of WITH-OPEN-STREAM.

(define-translator-macro with-open-file ((var &rest open-options) &body body)
    (multiple-value-bind (real-body decls) (parse-body body nil)
	`(let ((,var  (open ,@open-options)))
	     (declare ,@decls)
	     (unwind-protect (progn ,@real-body)
		 (if (streamp ,var) (close ,var))))
	))


;;; with-open-stream
;;; CLtL requires that the stream argument evaluate to a stream and says
;;; it has dynamic extent.

(define-translator-macro with-open-stream ((var stream) &body body)
    (multiple-value-bind (real-body decls) (parse-body body nil)
	`(let ((,var  ,stream))
	     (declare (type stream ,var) (dynamic-extent ,var) ,@decls)
	     (unwind-protect (progn ,@real-body)
		 (close ,var)))
	))

;;; with-output-to-string
;;; not sure whether the tests for the string being NIL are supposed
;;; to happen at runtime instead....

(define-translator-macro with-output-to-string
  ((var &optional string &key (element-type nil type-p)) &body body)
  (declare (ignore element-type))
  (multiple-value-bind (real-body decls) (parse-body body nil)
    (if string
	`(let ((,var  (trun:extend-string-output-stream ,string)))
	   (declare (type string-stream ,var)
		    (dynamic-extent ,var)
		    ,@decls)
	   (unwind-protect (progn ,@real-body)
	     (close ,var)))
	(progn
	  (when type-p
	    (warn ":ELEMENT-TYPE argument to with-output-to-string~
                    not supported: ignored"))
	  `(let ((,var  (make-string-output-stream)))
	     ;; Put this back in when we support it
	     ;; :element-type
	     ;;    ,(if type-p element-type 'character)
	     (declare (type string-stream ,var)
		      (dynamic-extent ,var)
		      ,@decls)
	     (unwind-protect
		 (progn ,@real-body (get-output-stream-string ,var))
	       (close ,var))))
	)))



;;; with-standard-io-syntax
;;; See table 22-7 in CLtL-II
;;; ***Maybe this should be be treated as a special form and mapped onto a
;;; ***C macro.

(define-translator-macro with-standard-io-syntax (&body body)
    `(let ((*package*                   (find-package "COMMON-LISP-USER"))
	   (*print-array*               t)
	   (*print-base*                10)
	   (*print-case*                :upcase)
	   (*print-circle*              nil)
	   (*print-escape*              t)
	   (*print-gensym*              t)
	   (*print-length*              nil)
	   (*print-level*               nil)
	   (*print-pretty*              nil)
	   (*print-radix*               nil)
	   (*print-readably*            t)
	   (*read-base*                 10)
	   (*read-default-float-format* 'single-float)
	   (*read-eval*                 t)
	   (*read-suppress*             nil)
	   (*readtable*                 (copy-readtable nil))  ;???
	   (*print-lines*               nil)
	   (*print-miser-width*         nil)
	   (*print-pprint-dispatch*     nil)
	   (*print-right-margin*        nil))
	 ,@body))

;;; (tx:c-lines &rest <strings-of-c-code>)
(defmacro tx:c-lines (&rest c-lines)
  (declare (ignore c-lines))
  nil)

(deftranslate tx:c-lines (&rest c-lines)
  (unless (eq *context* *ignore-context*)
    (warn
      "TX:C-LINES used in a value-returning context.~@
       NIL will be returned."))
  (multiple-value-bind (statements expression return-type temps)
      (translate-form 'nil *environment* *value-context*)
    (declare (ignore statements))
    (handle-context
      (if c-lines
	  (list (apply-make-target-form 'c-lines c-lines))
	  nil)
      expression
      return-type
      temps)))

(defmacro tx:toplevel-c-lines (&rest c-lines)
  (declare (ignore c-lines))
  nil)

(define-toplevel-form tx:toplevel-c-lines (&rest c-lines)
  (unless *toplevel-p*
    (error "~S forms may only appear at top level" 'tx:toplevel-c-lines))
  (unless *compile-time-only*
    (mapc #'emit-c-line (list* nil c-lines)))
  nil)

;;; Incorporated from patch-1; probably this should ultimately
;;; be a new entry in the symbols file
(eval-when (compile load eval)
(export (intern "GLOBAL-C-LINES" "TX") "TX")
)

(defmacro tx:global-c-lines (&rest c-lines)
  (declare (ignore c-lines))
  nil)

(define-toplevel-form tx:global-c-lines (&rest c-lines)
  (unless *toplevel-p*
    (error "~S forms may only appear at top level" 'tx:global-c-lines))
  (unless *compile-time-only*
    (setq *global-c-lines* (nconc *global-c-lines*
				  (list* nil (copy-list c-lines)))))
  nil)

#| ; change this to implement "inlined c macros"
(defmacro tx:c-expression ((c-expression-and-options &rest args)
			   &rest argforms)
  (declare (ignore c-expression-and-options args argforms))
  nil)

(deftranslate tx:c-expression ((c-expression-and-options &rest argument-specs)
			       &rest argforms)
  (let* ((c-expression (if (consp c-expression-and-options)
			   (car c-expression-and-options)
			   c-expression-and-options))
	 (foreign-return-type
	  (if (consp c-expression-and-options)
	      (getf (cdr c-expression-and-options) :return-type)
	      :object))
	 (return-type (foreign-type->lisp-type foreign-return-type))
	 (macro (when (consp c-expression-and-options)
		  (getf (cdr c-expression-and-options) :macro)))
	 (foreign-argument-types
	  (mapcar #'(lambda (arg-spec)
		      (cond ((consp arg-spec)
			     `(,(second arg-spec)
				,(or (third arg-spec)
				     macro)))
			    ((eq arg-spec '&rest)
			     arg-spec)
			    (t
			     (error "arg-spec ~S is not supported" arg-spec))))
		  argument-specs))
	 (argument-types (mapcar #'(lambda (foreign-arg)
				     (if (consp foreign-arg)
					 (lisp-type (cadr foreign-arg))
					 foreign-arg))
				 argument-specs))
	 (aft (mapcar #'(lambda (clause)
			 )))
  (multiple-value-bind (statements arg-values arg-types temps)
      (translate-arguments argforms arg-types nil aft abadp)
    (declare (ignore arg-types))
    (note-local-temps
     (foreign-function-descriptor-uses-locals descriptor))
    (translate-foreign-function-call
     name descriptor statements arg-values temps return-type))
  (unless (eq *context* *ignore-context*)
    (warn
      "TX:C-LINES used in a value-returning context.~@
       NIL will be returned."))
  (multiple-value-bind (statements expression return-type temps)
      (translate-form 'nil *environment* *value-context*)
    (declare (ignore statements))
    (handle-context
      (if c-lines
	  (list (apply-make-target-form 'c-lines c-lines))
	  nil)
      expression
      return-type
      temps)))))

|#

;;; (tx:cpp-conditional &rest <clauses>)
;;;   clauses ::= (<key> <form>*)
;;;   key ::= <string> | (:defined <string>) | (:undefined <string>) | t
;;;
;;;   This expands into
;;;
;;;   #if <key1>
;;;       <key1-forms>
;;;   #else
;;;   #if <key2>
;;;       <key2-forms>
;;;   #else
;;;   ...
;;;   #endif
;;;   #endif
;;;
;;;   Basically, the clauses are treated like a COND (with an implicit (t nil)
;;;   clause) but each clause's forms are treated like a PROGN. The forms are
;;;   always translated as non-toplevel forms.

(deftranslate tx:cpp-conditional (&rest clauses)
  (with-temporary-variables
    (let (conditional
	  forms
	  statements
	  expression
	  return-type
	  (conditionals             nil)
	  (statements-from-clauses  nil)
	  (expression-from-clauses  nil)
	  (return-type-from-clauses nil))
      (let* ((value-returning-p (value-context-p *context*))
	     temp
	     (context (if value-returning-p
			  (make-target-form
			   'local-variable
			   (setf temp (allocate-temporary
				       (context-foreign-type *context*))))
			  *context*)))
	(unless (or (eq context *ignore-context*) (eq (caar (last clauses)) t))
	  (setf clauses (append clauses `((t)))))
	(dolist (clause clauses)
	  (setf conditional  (first clause)
		conditionals (nconc conditionals (list conditional))
		forms        (rest clause))
	  (or (stringp conditional)
	      (eq conditional t)
	      (and (consp conditional)
		   (or (eq (first conditional) :defined)
		       (eq (first conditional) :undefined))
		   (stringp (second conditional)))
	      (error "~S is not a valid key for a TX:CPP-CONDITIONAL clause."
		     conditional))
	  (multiple-value-setq (statements expression return-type)
	    (translate-progn-body forms *environment* context nil
				  *result-type*))
	  (push (nreverse statements) statements-from-clauses)
	  (if (and expression-from-clauses (lvalue-context-p context))
	      (merge-error-check
	       expression-from-clauses expression 'tx:cpp-conditional)
	      (setf expression-from-clauses expression))
	  (if return-type-from-clauses
	      (setf return-type-from-clauses
		    (or-value-types return-type-from-clauses
				    return-type
				    *environment*))
	      (setf return-type-from-clauses return-type)))
	(values
	 (if value-returning-p
	     (list (make-target-form
		    'with-lexical-bindings
		    (list temp)
		    (make-target-form
		     'preprocessor-conditional
		     conditionals
		     (nreverse statements-from-clauses))))
	     (unless (every #'null statements-from-clauses)
	       (list (make-target-form
		      'preprocessor-conditional
		      conditionals
		      (nreverse statements-from-clauses)))))
	 expression-from-clauses
	 return-type-from-clauses)))))


(defmacro tx:printf (control-string &rest printf-args)
  (unless (constantp control-string)
    (error "The control-string is not a constant"))
  (let* ((foreign-types (printf-control-foreign-type-list control-string)))
    (unless (= (length foreign-types) (length printf-args))
      (error "The control-string needs ~D args, but ~D were supplied"
	     (length foreign-types) (length printf-args)))
    `(progn
       (trun:%printf ,control-string
		     ,@(mapcar #'(lambda (ft arg)
				   `(the ,(lisp-type ft) ,arg))
			       foreign-types printf-args))
       nil)))

(defun printf-control-foreign-type-list (control-string)
  (let ((ft-list nil)
	(len (length control-string))
	(pos 0))
    (flet ((get-char (&optional error-p)
	     (when (>= pos len)
	       (if error-p
		   (error "Bad control string ~S" control-string)
		   (return-from printf-control-foreign-type-list
		     (nreverse ft-list))))
	     (prog1 (schar control-string pos)
	       (incf pos))))
      (loop (when (char= #\% (get-char))
	      (loop (let ((char (get-char t)))
		      (declare (type character char))
		      (when (case char
			      ((#\+ #\- #\0 #\space #\#
				    #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9 #\.)
			       nil)
			      ((#\l #\L #\h)
			       (error "size modifiers are not supported"))
			      (#\% t)
			      ((#\d #\i)
			       (push (translator-foreign-type :long) ft-list))
			      ((#\c)
			       (push (translator-foreign-type :char) ft-list))
			      ((#\u #\o #\x #\X)
			       (push (translator-foreign-type :unsigned-32bit)
				     ft-list))
			      ((#\f #\e #\E #\g #\G)
			       (push (translator-foreign-type :double-float)
				     ft-list))
			      ((#\s)
			       (push (translator-foreign-type :string) ft-list))
			      (t
			       (error "Unknown printf specifier ~s" char)))
			(return nil)))))))))

(defun trun:%printf (control-string &rest arguments)
  (let ((len (length control-string))
	(pos 0))
    (flet ((get-char (&optional error-p)
	     (when (>= pos len)
	       (if error-p
		   (error "Bad control string ~S" control-string)
		   (return-from trun:%printf nil)))
	     (prog1 (schar control-string pos)
	       (incf pos))))
      (loop (let ((char (get-char)))
	      (if (char/= #\% char)
		  (write-char char)
		  (loop (setq char (get-char t))
			(when (case char
				((#\+ #\- #\0 #\space #\#
				      #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9 #\.)
				 nil)
				((#\l #\L #\h)
				 (error "size modifiers are not supported"))
				(#\% (write-char #\%) t)
				((#\d #\i)
				 (princ (pop arguments)) t)
				((#\c)
				 (princ (pop arguments)) t)
				((#\u #\o #\x #\X)
				 (princ (pop arguments)) t)
				((#\f #\e #\E #\g #\G)
				 (princ (pop arguments)) t)
				((#\s)
				 (princ (pop arguments)) t)
				(t
				 (error "Unknown printf specifier ~s" char)))
			  (return nil)))))))))

(translator-simple-defsetf tx:typed-foreign-aref tx:set-typed-foreign-aref)

(define-translator-property foreign-type-function #'identity)

(defmacro define-foreign-type-function (name lambda-list &body body)
  (let ((fname (intern (format nil "GET-FOREIGN-TYPE-FUNCTION-~S" name))))
    `(progn
       (defun ,fname ,lambda-list ,@body)
       (setf (foreign-type-function ',name) #',fname))))

(deftranslate tx:typed-foreign-aref (&whole form
				     foreign-type foreign-pointer
				     &rest indices)
  (unless (constantp foreign-type)
    (return-from tx:typed-foreign-aref
      (translate-function-call form)))
  (setq foreign-type (translator-foreign-type (eval foreign-type)))
  (let ((ndims (length indices))
	(pointer-type (translator-foreign-type-name foreign-type)))
    (unless (and (consp pointer-type)
		 (eq (car pointer-type) ':pointer)
		 (consp (cdr pointer-type))
		 (consp (cadr pointer-type))
		 (eq (caadr pointer-type) ':array))
      (error "typed-foreign-aref: ~S is not of the form ~S"
	     pointer-type '(:pointer (:array etype dimensions))))
    (let* ((array-type (cadr pointer-type))
	   (etype (cadr array-type))
	   (dimensions (if (eq ':column-major (cadddr array-type))
			   (reverse (caddr array-type))
			   (caddr array-type)))
	   (index-type (translator-foreign-type :fixnum))
	   (dims-tail (cdr dimensions))
	   (cast-type (if (null dims-tail)
			  `(:pointer ,etype)
			  `(:pointer (:array ,etype ,dims-tail)))))
      (setq etype (translator-foreign-type etype))
      (when (eq *context* ':result-type-only)
	(return-from tx:typed-foreign-aref
	  (values nil nil (lisp-type etype))))
      (multiple-value-bind (statements value-list type-list temps)
	  (translate-arguments
	   (list* foreign-pointer indices)
	   (list* t (make-list ndims :initial-element 'fixnum))
	   nil 
	   (list* (translator-foreign-type cast-type)
		  (make-list ndims :initial-element index-type))
	   (list* nil (make-list ndims :initial-element nil)))
	(declare (ignore type-list))
	(handle-context
	 statements
	 (if (null dimensions)
	     (make-target-form 'operator-call
			       'trun:%indirection
			       form)
	     (reduce #'(lambda (form index)
			 (make-target-form 'operator-call
					   'trun:%typed-foreign-aref
					   form index))
		     (cdr value-list)
		     :initial-value (car value-list)))
	 (lisp-type etype)
	 temps
	 etype)))))

(deftranslate tx:set-typed-foreign-aref (&whole form
					 foreign-type foreign-pointer
					 &rest indices+new-value)
  (unless (constantp foreign-type)
    (return-from tx:set-typed-foreign-aref
      (translate-function-call form)))
  (setq foreign-type (translator-foreign-type (eval foreign-type)))
  (let* ((indices (butlast indices+new-value))
	 (ndims (length indices))
	 (pointer-type (translator-foreign-type-name foreign-type)))
    (unless (and (consp pointer-type)
		 (eq (car pointer-type) ':pointer)
		 (consp (cdr pointer-type))
		 (consp (cadr pointer-type))
		 (eq (caadr pointer-type) ':array))
      (error "set-typed-foreign-aref: ~S is not of the form ~S"
	     pointer-type '(:pointer (:array etype dimensions))))
    (let* ((array-type (cadr pointer-type))
	   (etype (cadr array-type))
	   (dimensions (if (eq ':column-major (cadddr array-type))
			   (reverse (caddr array-type))
			   (caddr array-type)))
	   (index-type (translator-foreign-type :fixnum))
	   (cast-type (if (null dimensions)
			  `(:pointer ,etype)
			  `(:pointer (:array ,etype ,(cdr dimensions))))))
      (setq etype (translator-foreign-type etype))
      (when (eq *context* ':result-type-only)
	(return-from tx:set-typed-foreign-aref
	  (values nil nil (lisp-type etype))))
      (multiple-value-bind (statements value-list type-list temps)
	  (translate-arguments
	   (list* foreign-pointer indices+new-value)
	   (list* t (nconc (make-list ndims :initial-element 'fixnum)
			   (list (lisp-type etype))))
	   nil 
	   (list* (translator-foreign-type cast-type)
		  (nconc (make-list ndims :initial-element index-type)
			 (list etype)))
	   (list* nil (nconc (make-list ndims :initial-element nil)
			     (list t))))
	(declare (ignore type-list))
	(let ((value (car (last value-list))))
	  (handle-context
	   (cons (make-target-form
		  'setq
		  (if (null dimensions)
		      (make-target-form 'operator-call
					'trun:%indirection
					form)
		      (reduce #'(lambda (form index)
				  (make-target-form 'operator-call
						    'trun:%typed-foreign-aref
						    form index))
			      (cdr value-list)
			      :initial-value (car value-list)))
		  value)
		 statements)
	   value
	   (lisp-type etype)
	   temps
	   etype))))))

(define-foreign-type-function tx:typed-foreign-aref (form return-type)
  (declare (ignore return-type))
  (when (constantp (cadr form))
    (let* ((pt (translator-foreign-type-name 
		(eval (cadr form)))))
      (when (and (consp pt)
		 (eq (car pt) ':pointer)
		 (consp (cdr pt))
		 (consp (cadr pt))
		 (eq (caadr pt) ':array))
	(cadadr pt)))))

(define-foreign-type-function tx:foreign-function (form return-type)
  (declare (ignore return-type))
  (let ((name (cadr form)))
    (multiple-value-bind (usage bound-p decls)
	(translator-function-information name *environment*)
      (when (or (eq usage ':function) (null usage))
	(let* ((fd (unless bound-p (defined-as-function name)))		     
	       (ll-info	(if bound-p
			    (function-record-lambda-list-info 
			     (cdr (assoc 'function-record decls)))
			    (get-descriptor-lambda-list-info fd))))
	  (translator-foreign-type 
	   `(:pointer ,(function-foreign-type fd ll-info))))))))

(defun function-foreign-type (fd &optional ll-info)
  (unless ll-info (setq ll-info (get-descriptor-lambda-list-info fd)))
  (let* ((foreign-p (and fd (function-descriptor-foreign-protocol fd)))
	 (variadic-p 
	  (and (not foreign-p)
	       (if fd
		   (function-descriptor-variadic fd)
		   (or (lambda-list-info-restp ll-info)
		       (not (zerop 
			     (- (lambda-list-info-positional ll-info)
				(lambda-list-info-required ll-info))))))))
	 (npos (if variadic-p
		   0
		   (lambda-list-info-positional ll-info)))
	 (arg-types 
	  (if foreign-p
	      (foreign-function-arguments-foreign-types fd)
	      (make-list npos :initial-element ':object)))
	 (result-type 
	  (if foreign-p
	      (foreign-function-descriptor-foreign-return-type fd)
	      ':values)))
    (if foreign-p
	(let ((rest (memq '&rest arg-types)))
	  (when rest 
	    (setq arg-types (nconc (ldiff arg-types rest) '(&rest)))))
	(when variadic-p
	  (setq arg-types (nconc arg-types '(&rest)))))
    `(,(if variadic-p ':variadic-function :function)
      ,arg-types
      ,result-type)))

(define-foreign-type-function the (form return-type)
  (simple-form-foreign-type (caddr form) return-type))

(define-translator-macro tx:foreign-variable-address (string)
  `(tx:foreign-variable-pointer ,string :unsigned-32bit))

(defun declare-foreign-variable-name (c-name)
  (when *remove-leading-underscore-from-foreign-string-p*
    (setq c-name (string c-name))
    (when (zerop (length c-name))
      (error "c-name is ~S" c-name))
    (when (char= (char c-name 0) #\_)
      (when (eq *remove-leading-underscore-from-foreign-string-p* ':warn)
	(setq *remove-leading-underscore-from-foreign-string-p* t)
	(warn "Removing one leading underscore from foreign variable names~@
               (for compatibility with C).~@
               Set ~S to T~@
               to avoid the warning, or to NIL to inhibit the removal."
	      '*remove-leading-underscore-from-foreign-string-p*))
      (setq c-name (subseq c-name 1))))
  (tutil::record-c-name c-name t)
  #||
  (let ((decl (format nil "int ~A;" c-name)))
    (unless (member form *global-c-lines*
		    :test #'equal)
      (setq *global-c-lines* (nconc *global-c-lines*
				    (list* nil decl)))))
  ||#
  c-name)


(deftranslate tx:foreign-variable-pointer (string &optional foreign-type)
  (unless foreign-type
    (setq foreign-type ''(:pointer :signed-32bit)))
  (unless (and foreign-type (constantp foreign-type))
    (return-from tx:foreign-variable-pointer
      (re-translate-form
       `(tx:make-foreign-pointer-internal 
	 (tx:foreign-variable-address ,string)
	 (tx:foreign-type ,foreign-type)))))
  (setq foreign-type (eval foreign-type))
  (if (eq *context* ':result-type-only)
      (values nil nil (lisp-type foreign-type))
      (handle-context nil 
		      (make-target-form 
		       'c-constant ':c-expression
		       (sformat "(~A)~A~A" 
				(c-type foreign-type)
				(if (and (consp foreign-type)
					 (eq (car foreign-type) ':pointer)
					 (consp (cadr foreign-type))
					 (eq (caadr foreign-type) ':function))
				    "" ; this is for old C compilers 
				    "&")
				(declare-foreign-variable-name string)))
		      (lisp-type foreign-type)
		      nil
		      (translator-foreign-type foreign-type))))

(deftranslate translator-foreign-size-of (foreign-type)
  (unless (constantp foreign-type)
    (error "~S requires a constant argument" 'translator-foreign-size-of))
  (setq foreign-type (eval foreign-type))
  (if (eq *context* ':result-type-only)
      (values nil nil `(unsigned-byte 32))
      (handle-context nil 
		      (make-target-form 
		       'c-constant ':c-expression
		       (format nil "(unsigned long)sizeof(~A)"
			       (c-type foreign-type)))
		      `(unsigned-byte 32)
		      nil
		      (translator-foreign-type :unsigned-32bit))))

(deftranslate tx:foreign-call (function &rest arguments)
  (translate-foreign-call nil function arguments))

(deftranslate tx:variadic-foreign-call (function &rest arguments)
  (translate-foreign-call t function arguments))

(defun translate-foreign-call (variadic-p function arguments)
  (let* ((function-ft 
	  (translator-foreign-type-name 
	   (or (simple-form-foreign-type function)
	       (error "~S~% is too complicated to determine its foreign-type~
                       (try making it a variable)" function))))
	 (fft function-ft)
	 arg-types result-type values-p)
    (unless (and (consp fft)
		 (eq (car fft) ':pointer)
		 (consp (setq fft (cadr fft)))
		 (or (eq (car fft) ':function)
		     (eq (car fft) ':variadic-function))
		 (setq result-type (caddr fft)))
      (error "~S: the foreign type of the first argument, ~S,~
              is not ~S" 'tx:foreign-call function-ft
	      '(:pointer (:function "argument-types" "result-type"))))
    (when (setq values-p (eq result-type ':values))
      (setq result-type ':object))
    (when (eq *context* ':result-type-only)
      (return-from translate-foreign-call
	(values nil nil (lisp-type result-type))))
    (setq arg-types (cadr fft))
    (when (eq (car fft) ':variadic-function)
      (setq variadic-p t))
    (when variadic-p
      (let ((last-arg-type :object))
	(setq arg-types (append arg-types
				(make-list (- (length arguments)
					      (length arg-types))
					   :initial-element last-arg-type)))))
    (unless (eql (length arg-types) (length arguments))
      (error "The number of argument types (~D), does not equal~
              the number of argument-forms (~D)."
	     (length arg-types) (length arguments)))
    (let* ((foreign-type-list (mapcar #'get-translator-foreign-type
				     (cons function-ft arg-types)))
	   (lisp-type-list (mapcar #'translator-foreign-type-lisp-type
				   foreign-type-list))
	   (badp-list (make-list (length foreign-type-list))))
    (multiple-value-bind (all-statements value-list result-type-list
					 all-temps)
	(translate-arguments 
	 (cons function arguments) lisp-type-list nil 
	 foreign-type-list badp-list)
      (declare (ignore result-type-list))
      (handle-context 
       all-statements
       (if variadic-p
	   (if values-p
	       (apply-make-target-form 'variadic-values-c-call value-list)
	       (apply-make-target-form 'variadic-c-call value-list))
	   (if values-p
	       (apply-make-target-form 'values-c-call value-list)
	       (apply-make-target-form 'c-call value-list)))
       (lisp-type result-type)
       all-temps
       (translator-foreign-type result-type))))))

;this should work on any function defined with 
;tx:def-foreign-callable or tx:def-foreign-function, and also
;any lisp function that neither uses varargs protocol nor
;has closed variables.  (does not work on generic functions)
(deftranslate tx:foreign-function (arg)
  (cond ((valid-function-name-p arg)
	 (translate-function-reference arg ':foreign))
	(t
	 (error "Bad syntax in TX:FOREIGN-FUNCTION special form: ~s" arg))))

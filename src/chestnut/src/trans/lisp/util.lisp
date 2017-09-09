;;; -*- Mode: Lisp; Package: TUTIL; Syntax: Common-Lisp -*-
;;;
;;; util.lsp -- various utility functions
;;;
;;; Author :  Kim Barrett
;;; Date   :  16 November 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.

(in-package "TUTIL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/util.lisp,v $"
 "$Revision: 1.7 $"
 "$Date: 2007/11/14 22:02:54 $")

;;; From PCL.
(defmacro once-only (vars &body body)
  (let ((gensym-var (gensym))
        (run-time-vars (gensym))
        (run-time-vals (gensym))
        (expand-time-val-forms ()))
    (dolist (var vars)
      (push `(if (or (symbolp ,var)
                     (numberp ,var)
                     (and (listp ,var)
			  (member (car ,var) '(quote function))))
                 ,var
                 (let ((,gensym-var (gensym)))
                   (push ,gensym-var ,run-time-vars)
                   (push ,var ,run-time-vals)
                   ,gensym-var))
            expand-time-val-forms))    
    `(let* (,run-time-vars
            ,run-time-vals
            (wrapped-body
	      (let ,(mapcar #'list vars (reverse expand-time-val-forms))
		,@body)))
       `(let ,(mapcar #'list (reverse ,run-time-vars)
			     (reverse ,run-time-vals))
	  ,wrapped-body))))

(defun simple-variable-p (var env)
  (multiple-value-bind (usage bound-p decls)
      (translator-variable-information var env)
    (declare (ignore bound-p decls))
    (not (eq usage :symbol-macro))))

;;; Patch 38 used the slightly different formulation:
;; (defun once-only-simple-form-p (form env)
;;   (or (constantp form)
;;       (and (symbolp form)
;;	   (simple-variable-p form env))
;;      (and (consp form)
;;	   (eq (car form) 'the)
;;	   (once-only-simple-form-p (caddr form) env))))

;; We are not using this one yet, since it constitutes a change that actually
;; changes the translation result, and we want to separate substansive changes
;; from folding patch code in. This change was not actually effective in patch
;; 38, since it redefines the macro after its uses are complete.

(defun once-only-simple-form-p (form env)
  (or (numberp form)
      (characterp form)
      (and (listp form)
	   (member (car form) '(quote)))
      (and (symbolp form)
	   (simple-variable-p form env))))

(defmacro once-only* (vars env &body body)
  (let ((gensym-var (gensym))
        (run-time-vars (gensym))
        (run-time-vals (gensym))
	(wrapped-body (gensym))
        (expand-time-val-forms ()))
    (dolist (var vars)
      (push `(if (once-only-simple-form-p ,var ,env)
                 ,var
                 (let ((,gensym-var (make-symbol "TEMP")))
                   (push ,gensym-var ,run-time-vars)
                   (push ,var ,run-time-vals)
                   ,gensym-var))
            expand-time-val-forms))    
    `(let* (,run-time-vars
            ,run-time-vals
            (,wrapped-body
	      (let ,(mapcar #'list vars (reverse expand-time-val-forms))
		,@body)))
       (if ,run-time-vars
	   `(let ,(mapcar #'list (reverse ,run-time-vars)
			  (reverse ,run-time-vals))
	      (declare (tx:unwritten-variable ,@,run-time-vars))
	      ,,wrapped-body)
	   ,wrapped-body))))

;used for foreign-type
(defmacro define-hashed-structure (name &rest fields)
  (let* ((dconstr (when (consp name)
		    (assoc :constructor (cdr name))))
	 (name (if (consp name) (car name) name))
	 (var (intern (format nil "*~A-~A*" name 'table)))
	 (pred (intern (format nil "~A-~A" name 'p)))
	 (%name (intern (format nil "~A-~A" name '%name)))
	 (print (intern (format nil "~A-~A" 'print name)))
	 (constr (intern (format nil "~A-~A" 'make name)))
	 (get-name (intern (format nil "~A-~A" 'get name))))
    `(progn
       (defvar ,var (make-hash-table :test #'eq))
       (defstruct (,name
		    (:print-function ,print)
		    ,@(when dconstr
			`(,dconstr)))
	 %name
	 ,@fields)
       (defun ,print (object stream depth)
	 (declare (ignore depth))
	 (format stream ,(format nil "#<~A ~~S>" (string-downcase name))
		 (,%name object)))
       (defun ,get-name (object &optional (make-p t))
	 (if (,pred object)
	     object
	     (or (gethash object ,var)
		 (setf (gethash object ,var)
		       (and make-p (,constr :%name object))))))
       (defmacro ,name (object)
	 (if (and (constantp object)
		  (symbolp (eval object)))
	     (let ((item-name (eval object)))
	       (intern (format nil "*~A-~A*" item-name ',name)
		       ,(package-name *package*)))
	     (once-only (object)
	       `(if (,',pred ,object)
		    ,object
		    (,',get-name ,object)))))
       (defmacro ,(intern (format nil "~A-~A" 'define name)) 
	   (item-name &rest args)
	 (let ((var-name (intern (format nil "*~A-~A*" item-name ',name))))
	   `(progn
	      (defparameter ,var-name
		(apply #',',constr ':%name ',item-name ',args))
	      (setf (gethash ',item-name ,',var) ,var-name))))
       (defmacro ,(intern (format nil "~A-~A" name 'name)) (object)
	 `(if (,',pred ,object)
	      (,',%name ,object)
	      ,object))
       ,@(mapcar #'(lambda (field)
		     (let ((field (if (atom field) field (car field))))
		       `(defmacro ,field (object)
			  `(,',(intern (format nil "~A-~A" name field))
			     (,',name ,object)))))
		 fields)
       ',name)))

(defmacro define-flags (conc-name internal-name &rest slots)
  (let ((slot-names (mapcar #'(lambda (slot)
				(if (consp slot) (car slot) slot))
			    slots)))
    `(progn
       ,@(mapcar
	  #'(lambda (slot-name)
	      (let ((accessor (intern (format nil "~A~A"
					      conc-name slot-name)))
		    (mask (ash 1 (position slot-name slot-names))))
		`(progn
		   #||(defmacro ,accessor (object)
			`(not (zerop (logand ,',mask
					     (,',internal-name ,object)))))||#
		   (defun ,accessor (object)
		     (not (zerop (logand ,mask
					 (the fixnum
					      (,internal-name object))))))
		   (defsetf ,accessor (object) (new-value)
		     `(progn
			(setf (,',internal-name ,object)
			      (let ((%%old (,',internal-name ,object)))
				(declare (fixnum %%old))
				(cond ((eq ,new-value 't)
				       (logior ,',mask %%old))
				      ((eq ,new-value 'nil)
				       (logandc1 ,',mask %%old))
				      (t
				       (error "~S can only hold T or NIL"
					      ',',accessor)))))
			,new-value)))))
	  slot-names)
       (eval-when (compile load eval)
	 (defparameter ,(intern (format nil "*~A~A*" 
					conc-name 'flags))
	   ',(mapcar #'(lambda (slot-name)
			 (intern (string slot-name) :keyword))
		     slot-names))
	 (defparameter ,(intern (format nil "*~A~A*"
					conc-name 'flags-slot-names))
	   ',slots))
       (defun ,(intern (format nil "~A~A" 'make- internal-name))
	   (&key ,@(mapcar #'(lambda (slot)
			       (if (and (consp slot)
					(cddr slot))
				   (list (car slot) (cadr slot))
				   slot))
			   slots))
	 (logior ,@(mapcar #'(lambda (slot-name)
			       `(if ,slot-name
				    ,(ash 1 (position slot-name slot-names))
				    0))
			   slot-names))))))

(defmacro char-ascii-code (char)
  #+(or sbcl lucid excl mcl clozure lispworks) `(char-code ,char)
  #+genera `(scl:ascii-code ,char)
  #-(or sbcl lucid excl mcl clozure genera lispworks)
  (error "You need to implement ~S" 'char-ascii-code))

(defmacro ascii-code-char (char)
  #+(or sbcl lucid excl mcl clozure lispworks) `(code-char ,char)
  #+genera `(scl:ascii-to-char ,char)
  #-(or sbcl lucid excl mcl clozure genera lispworks)
  (error "You need to implement ~S" 'ascii-code-char))


;;; DEFINE-FORWARD-VARIABLE-REFERENCE

;;; The actual definition (including documentation) of most Translator global
;;; variables is in the file which is primarily concerned with the variable.
;;; This macro provides a way of referencing the variable in files
;;; loaded earlier in the build process.

(defmacro define-forward-variable-reference (var)
  `(declaim (special ,var)))


(defvar *translator-parameters* nil)

(defun add-translator-parameter (name default)
  (let ((a (assoc name *translator-parameters*)))
    (if a
	(setf (second a) default)
	(setq *translator-parameters*
	      (nconc *translator-parameters*
		     (list (list name default))))))
  name)

(defmacro define-translator-parameter (name default &optional documentation)
  (declare (ignore documentation))
  `(progn
     (add-translator-parameter ',name ,default)
     (defvar ,name ,default)))

(eval-when (compile load eval)
(defun parse-body (body &optional (doc-allowed-p nil))
  (let ((doc    nil)
	(decls  nil)
	(message nil))
    (loop
     (cond ((null body)
	    (return (values nil decls doc message)))
	   ((and doc-allowed-p (stringp (car body)))
	    (if (cdr body)
		(setq doc (pop body))
		(return (values body decls doc message))))
	   ((and (consp (car body)) (eq (car (car body)) 'declare))
	    (dolist (d (cdr (pop body)))
	      (when (and (consp d)
			 (eq (car d) 'translator-message))
		(setq message (cdr d)))
	      (push d decls)))
	   (t
	    (return (values body decls doc message)))))))
)


;;; Define an extensible mechanism for extracting the principal symbol out of
;;; a generalized function name.  This is used in computing block names, C
;;; names, and similar places.  It is made extensible to make it easy to deal
;;; with some additional list-based `function names' that might be wanted (such
;;; as method names).  The only extraction mechanism defined here is for SETF
;;; function names.
;;;
;;; PRINCIPAL-NAME-OF-FUNCTION-NAME (external)
;;; DEFINE-PRINCIPAL-NAME (external)
;;; INVALID-FUNCTION-NAME-ERROR (external)


(defun invalid-function-name-error (name)
  ;(error 'simple-program-error
  ;	 :format-string "~S is not a valid function name."
  ;	 :format-arguments (list name))
  (error "~S is not a valid function name." name)
  )

(defvar *principal-function-name-extractors* (make-hash-table :test 'equal))

(defmacro principal-function-name-extractor (key)
  `(gethash ,key *principal-function-name-extractors*))

(defun principal-name-of-function-name (function-name &aux temp)
  (cond ((symbolp function-name) function-name)
	((and (symbolp (setf temp (car function-name)))
	      (setf temp (principal-function-name-extractor temp)))
	 (funcall temp function-name))
	((valid-function-name-p function-name)
	 (error "Translator bug -- Can't determine principal name for ~S."
		function-name))
	(t
	 (invalid-function-name-error function-name))))

(defmacro define-principal-function-name (key lambda-list &body body)
  (check-type key symbol)
  (multiple-value-bind (body decls) (parse-body body)
    (let ((name (intern (format nil "~A-~A" key 'principal-function-name))))
      `(progn
	 (defun ,name ,lambda-list 
	   (declare ,@decls)
	   ,@body)
	 (setf (principal-function-name-extractor ',key)
	       #',name)))))

(define-principal-function-name SETF (function-name)
  (second function-name))

;;; This function takes a function name and returns the appropriate block name
;;; for use in the block that is to be wrapped around the body of the named
;;; function.  If the name is not a valid function name, an error of type
;;; PROGRAM-ERROR is signaled.

(defun body-block-name (function-name)
  (principal-name-of-function-name function-name))


;;; LAMBDA-EXPRESSION-P
;;;
;;; This predicate returns true if the form appears to be a lambda expression.

(defun lambda-expression-p (form)
  (and (consp form)
       (eq (car form) 'lambda)
       (consp (cdr form))
       (listp (cadr form))))

;;; VALID-FUNCTION-NAME-P
;;;
;;; This predicate returns true if the form is a syntactically valid function
;;; name.

(defun setf-function-name-p (form)
  (and (consp form)
       (eq (pop form) 'setf)
       (consp form)
       (symbolp (pop form))
       (null form)))

(defun valid-function-name-p (form)
  (or (symbolp form)
      (setf-function-name-p form)))


;;; REQUIRED-KEYWORD
;;;
;;; Some keyword parameters must be supplied.  Use a call to this function as
;;; the initform for such a parameter.

(defun required-keyword (keyword)
  (error "The keyword argument ~S must be supplied." keyword))


;;; This function is used to print progress messages as various 
;;; kinds of definitions in the input file are translated.  The first
;;; argument should be a string indicating what kind of definition it is,
;;; like "Function".

(defun print-progress-message (type &rest names)
  (when *compile-print*
    (format *standard-output* "~&;;; ~A~{ ~S~}~%" type names)))


;;; Add variable bindings for the lambda parameters and the declarations
;;; to the environment.

(defun add-lambda-bindings-to-env (lambda-list declarations env)
    (translator-augment-environment env
        :variable (collect-lambda-parameters lambda-list)
	:declare declarations))


;;; Match unevaluated argument forms to the lambda parameters.
;;; Returns two values:  a list of the same length as the argument-forms
;;; list, with either the name of the matching lambda-parameter or NIL;
;;; and a boolean indicating whether there were unmatched keyword arguments
;;; in the lambda-list.

(defun match-argforms-to-parameters (args lambda-list env)
    (match-args-to-parameters-aux
        args
	lambda-list
	#'(lambda (form)
	    (translator-constant-value form env))))

;;; Similar, but works on target language.

(defun match-argvalues-to-parameters (args lambda-list)
  (match-args-to-parameters-aux
   args
   lambda-list
   #'match-argvalues-to-parameters-internal))

#|| ; in target.lisp
(defun match-argvalues-to-parameters-internal (construct)
  (if (or (eq (target-form-type construct) 'initial-symbol)
	  (eq (target-form-type construct) 'constant))
      (values (cadr construct) t)
      (values nil nil)))
||#

;;; RECORD-DOCUMENTATION-P
;;;
;;; Returns the documentation string, if it should be made available at
;;; runtime.

(define-forward-variable-reference *record-documentation-for-runtime*)

(defun record-documentation-p (documentation)
  (and *record-documentation-for-runtime* documentation))

;;; Miscellaneous functions for operating on lists
(defun unionq (set1 set2)
  (dolist (e2 set2 set1)
    (unless (dolist (e1 set1 nil)
	      (when (eq e1 e2)
		(return t)))
      (push e2 set1))))

(define-modify-macro unionf (other-set &rest keywords) union)
(define-modify-macro unionqf (other-set &rest keywords) unionq)

(defun union-append (old new)
  ;; UNION, but take OLD first, and preserve order in both OLD and NEW
  (let ((new-items '()))
    (dolist (item new
		  (if new-items
		      (append old (nreverse new-items))
		      old))
      (unless (member item old)
	(push item new-items)))))

(define-modify-macro union-appendf (other-set) union-append)

(defun unionq-append (old new)
  ;; UNIONQ, but take OLD first, and preserve order in both OLD and NEW
  (let ((new-items '()))
    (dolist (item new
		  (if new-items
		      (append old (nreverse new-items))
		      old))
      (unless (dolist (old-item old nil)
		(when (eq item old-item)
		  (return t)))
	(push item new-items)))))

(define-modify-macro unionq-appendf (other-set) unionq-append)

(defun unionq-append1 (old new)
  ;; UNIONQ, but take OLD first, and preserve order in both OLD and NEW
  ;; May destructively modify OLD.
  (let ((new-items '()))
    (dolist (item new
		  (if new-items
		      (nconc old (nreverse new-items))
		      old))
      (unless (dolist (old-item old nil)
		(when (eq item old-item)
		  (return t)))
	(push item new-items)))))

(define-modify-macro unionq-append1f (other-set) unionq-append1)

(define-modify-macro appendf (other-set) append)

;May modify the first argument.
(defun append1 (list1 list2)
  (nconc list1 (copy-list list2)))

(define-modify-macro append1f (other-set) append1)

(define-modify-macro maxf (other-number) max)

;;; Secret special operators
;;;
;;; Some internal functions are actually implemented as special forms.  In
;;; order to make them appear to be functions for environment processing, a
;;; function descriptor needs to be recorded for them in the environment.

(defmacro define-internal-function (name lambda-list)
  `(setf (defined-as-function ',name)
	 (make-function-descriptor
	  :lambda-list ',lambda-list
	  :foreign-protocol :secret-special-form)))

(defvar *translator-message-string* nil)

(defmacro with-translator-message (message &body forms)
  `(let* ((.message. ,message)
	  (.message. (if (or (null .message.)
			     (stringp .message.))
			 .message.
			 (if (atom .message.)
			     (format nil "~S" .message.)
			     (format nil "~{~S~^ ~}" .message.))))
	  (*translator-message-string*
	   (if (and *translator-message-string* .message.)
	       (format nil "~A <-~%    ~A"
		       .message. *translator-message-string*)
	       (or *translator-message-string* .message.))))
     ,@forms))

(defun warn (string &rest args)
  (if *translator-message-string*
      (apply #'host:warn "While translating ~A:~%~@?"
	     *translator-message-string* string args)
      (apply #'host:warn string args)))

(define-compiler-macro warn (string &rest args)
  `(if *translator-message-string*
       (host:warn "While translating ~A:~%~@?"
		  *translator-message-string* ,string ,@args)
       (host:warn ,string ,@args)))

(defun error (string &rest args)
  (if *translator-message-string*
      (apply #'host:error "While translating ~A:~%~@?"
	     *translator-message-string* string args)
      (apply #'host:error string args)))

(define-compiler-macro error (string &rest args)
  `(if *translator-message-string*
       (host:error "While translating ~A:~%~@?"
		   *translator-message-string* ,string ,@args)
       (host:error ,string ,@args)))

(defun cerror (cstring string &rest args)
  (if *translator-message-string*
      (apply #'host:cerror cstring "While translating ~A:~%~@?"
	     *translator-message-string* string args)
      (apply #'host:cerror cstring string args)))

(define-compiler-macro cerror (cstring string &rest args)
  `(if *translator-message-string*
       (host:cerror ,cstring "While translating ~A:~%~@?"
		    *translator-message-string* ,string ,@args)
       (host:cerror ,cstring ,string ,@args)))

(defun make-some/every-form (function list lists every-p)
  (let* ((lists (cons list lists))
	 (value-var (unless every-p (make-symbol "VALUE")))
	 (list-vars (let ((i -1))
		      (mapcar #'(lambda (list)
				  (declare (ignore list))
				  (make-symbol (format nil "LIST~D"
						       (incf i))))
			      lists)))
	 (call-form `(,@(if (and (consp function)
				 (eq (car function) 'function))
			    `(,(cadr function))
			    `(funcall ,function))
		       ,@(mapcar #'(lambda (list-var)
				     `(car ,list-var))
				 list-vars))))
    `(do* (,@(mapcar #'(lambda (list-var list)
			 `(,list-var ,list (cdr ,list-var)))
		     list-vars lists))
	  ((not (and ,@list-vars))
	   ,(not (null every-p)))
       ,(if every-p
	    `(unless ,call-form (return nil))
	    `(let ((,value-var ,call-form))
	       (when ,value-var (return ,value-var)))))))

(defmacro some (function list &rest lists)
  (make-some/every-form function list lists nil))

(defmacro every (function list &rest lists)
  (make-some/every-form function list lists t))

;only ~a, ~d, and ~% are supported
;all the arguments are strings or symbols whose names will be used.
(defmacro sformat (control &rest args)
  (unless (stringp control)
    (error "Error in sformat: control must be a string"))
  (let ((cargs nil)
	(start 0)
	(len (length control)))
    (loop (when (>= start len)
	    (return nil))
	  (let ((end (position #\~ control :start start)))
	    (unless (eql start end)
	      (push (subseq control start (or end len)) cargs))
	    (unless end (return nil))
	    (when (= (1+ end) len)
	      (error "Error in sformat: invalid control string"))
	    (case (char control (1+ end))
	      ((#\a #\A)
	       (push `(sformat-string ,(pop args)) cargs))
	      ((#\d #\D)
	       (push `(sformat-integer ,(pop args)) cargs))
	      (#\%
	       (push `(sformat-newline) cargs))
	      (t
	       (error "Error in sformat: invalid control string")))
	    (setq start (+ end 2))))
  `(sformat-internal ,@(nreverse cargs))))

(defun sformat-internal (&rest args)
  (let ((size 0))
    (dolist (arg args)
      (incf size (length arg)))
    (let ((string (make-string size))
	  (pos -1))
      (declare (string string) (fixnum pos))
      (dolist (arg args)
	(dotimes (i (length arg))
	  (setf (schar string (incf pos)) (char arg i))))
      string)))

(defun sformat-other (object)
  (format nil "~A" object))

(defmacro sformat-string (object)
  `(let ((object ,object))
     (typecase object
       (string object)
       (symbol (symbol-name object))
       (t (sformat-other object)))))

(defvar *sformat-integer-buffer*
  (make-array 20 :element-type '#.(array-element-type "")
	      :fill-pointer 0))

(defun sformat-integer (number)
  (if (not (integerp number))
      (sformat-other number)
      (let ((pos 0)
	    (minusp nil)
	    (number number))
	(declare (fixnum pos)(integer number))
	(macrolet ((push-char (char)
		     `(progn
			(setf (aref *sformat-integer-buffer* pos) ,char)
			(incf pos))))
	(when (minusp number)
	  (setq minusp t)
	  (setq number (- number)))
	(if (zerop number)
	    (push-char #\0)
	    (loop (multiple-value-bind (quotient divisor)
		      (floor number 10)
		    (declare (integer quotient)
			     (type (integer 0 9) divisor))
		    (push-char (digit-char divisor))
		    (when (zerop quotient)
		      (return nil))
		    (setq number quotient))))
	(when minusp (push-char #\-))
	(dotimes (i (ash pos -1))
	  (declare (fixnum i))
	  (rotatef (aref *sformat-integer-buffer* i)
		   (aref *sformat-integer-buffer* (- pos i 1))))
	(setf (fill-pointer *sformat-integer-buffer*) pos)
	*sformat-integer-buffer*))))

(defvar *sformat-newline* (make-string 1 :initial-element #\newline))

(defmacro sformat-newline ()
  '*sformat-newline*)

(define-translator-parameter timpl::*do-read-once-optimization* t)

#+ignore ; binghe, 2009/4/12, move to record.lisp
(defun reset-read-once-setqs (env)
  (when timpl::*do-read-once-optimization*
    (dolist (contour (translator-environment-lexical-part env))
      (when (and (variable-information-contour-p contour)
		 (eq ':lexical (variable-information-contour-usage contour)))
	(let* ((decls (variable-information-contour-declarations contour))
	       (record (cdr (assoc 'timpl::variable-record decls))))
	  (when (eq (timpl::variable-record-setq-statement record) ':none)
	    (return-from reset-read-once-setqs nil))
	  (setf (timpl::variable-record-setq-statement record) ':none))))))

(defun map-over-enclosing-functions (function use-env binding-env)
  (let ((binding-contour-list 
	 (translator-environment-lexical-part binding-env)))
    (when (function-or-multiple-execution-contour-list-p binding-contour-list)
      (let ((contour-list (translator-environment-lexical-part use-env)))
	(loop (when (or (null contour-list)
			(eq contour-list binding-contour-list))
		(return nil))
	      (let ((contour (pop contour-list)))
		(when (function-name-contour-p contour)
		  (funcall function 
			   (function-name-contour-name contour)
			   (function-name-contour-info contour)))))))))


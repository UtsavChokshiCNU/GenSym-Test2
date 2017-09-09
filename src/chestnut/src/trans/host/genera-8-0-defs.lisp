;;; -*- Mode: Lisp; Syntax: Common-Lisp; Package: HOST -*-
;;;
;;; genera-8-0-defs.lisp
;;;
;;; author :  Richard Harris 
;;; date   :  17 Nov 92
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;; 

(in-package "HOST")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/genera-8-0-defs.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006-02-28 21:58:58 $")

(defmacro macro-function (name &optional env)
  (declare (ignore env))
  `(lisp:macro-function ,name))

(defvar *compile-file-pathname* nil)
(defvar *compile-file-truename* nil)

;;; renamed SETF stuff

(defmacro define-setf-expander (&rest stuff)
  `(lisp:define-setf-method ,@stuff))

(defun get-setf-expansion (form &optional env)
  (lisp:get-setf-method-multiple-value form env))

;;; fix base-char and extended-char problems
(deftype base-char () 'future-common-lisp::base-character)
(deftype extended-char () 'future-common-lisp::extended-character)

;;; things with environment arguments added

(defun typep (thing type &optional env)
  (declare (ignore env))
  (lisp:typep thing type))

(defun subtypep (type1 type2 &optional env)
  (declare (ignore env))
  (lisp:subtypep type1 type2))

;;; SIMPLE-CONDITION-FORMAT-CONTROL

(defun SIMPLE-CONDITION-FORMAT-CONTROL (c)
  (conditions:simple-condition-format-string c))


;;; renamed special-form-p

(defun special-operator-p (thing)
  (lisp:special-form-p thing))

;;; DECLAIM

(defmacro declaim (&rest specs)
  `(eval-when (compile load eval)
     ,@(mapcar #'(lambda (spec) `(proclaim ',spec))
	       specs)))

;;; WITH-COMPILATION-UNIT

(defmacro with-compilation-unit (options &body body)
  (declare (ignore options))
  `(progn ,@body))

;;; NTH-VALUE

(defmacro NTH-VALUE (index value-form)
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
		      'nth-value index-value)
		(make-default-expansion index value-form))))
	(make-default-expansion index value-form))))

;;; HANDLER-BIND

(defvar *handler-clusters* nil)

(defmacro handler-bind (bindings &body forms)
  (unless (every #'(lambda (x) (and (listp x) (= (length x) 2))) bindings)
    (error "Ill-formed handler bindings."))
  (let ((handlers (mapcar #'(lambda (x) `(cons ',(car x) ,(cadr x)))
			  bindings)))
    `(let ((*handler-clusters* (cons (list ,@handlers)
				     *handler-clusters*)))
       ,@forms)))

;;; HANDLER-CASE

(defmacro handler-case (form &rest cases)
  (let ((no-error-clause (assoc ':no-error cases)))
    (if no-error-clause
	(let ((normal-return (make-symbol "normal-return"))
	      (error-return  (make-symbol "error-return")))
	  `(block ,error-return
	     (multiple-value-call #'(lambda ,@(cdr no-error-clause))
	       (block ,normal-return
		 (return-from ,error-return
		   (handler-case (return-from ,normal-return ,form)
		     ,@(remove no-error-clause cases)))))))
	(let ((tag (gensym))
	      (var (gensym))
	      (annotated-cases (mapcar #'(lambda (case) (cons (gensym) case))
				       cases)))
	  (flet ((handler-binding (annotated-case)
		   (list (cadr annotated-case)
			 `#'(lambda (temp)
			      ,@(if (caddr annotated-case)
				    `((setq ,var temp)))
			      (go ,(car annotated-case)))))
		 (handler-body (annotated-case)
		   (list (car annotated-case)
			 (let ((body (cdddr annotated-case)))
			   `(return-from ,tag
			      ,(cond ((caddr annotated-case)
				      `(let ((,(caaddr annotated-case)
					      ,var))
					 ,@body))
				     ((not (cdr body))
				      (car body))
				     (t
				      `(progn ,@body))))))))
	  `(block ,tag
	     (let ((,var nil))
	       ,var				;ignorable
	       (tagbody
		 (handler-bind ,(mapcar #'handler-binding annotated-cases)
			       (return-from ,tag ,form))
		 ,@(mapcan #'handler-body annotated-cases)))))))))

;;; IGNORE-ERRORS

(defmacro ignore-errors (&rest forms)
  `(handler-case (progn ,@forms)
     (error (condition) (values nil condition))))


(defvar *unique-id-counter* 0)
(defvar *unique-id-table* (make-hash-table :test 'eq))

(defun unique-id (object)
  (or (gethash object *unique-id-table*)
      (setf (gethash object *unique-id-table*)
	    (incf *unique-id-counter*))))

;;; RESTART-BIND

(defvar *restart-clusters* '())

(defun compute-restarts ()
  (mapcan #'copy-list *restart-clusters*))

(defun restart-print (restart stream depth)
  (declare (ignore depth))
  (if *print-escape*
      (format stream "#<~s.~d>" (type-of restart) (unique-id restart))
      (restart-report restart stream)))

(defstruct (restart (:print-function restart-print))
  name
  function
  report-function
  interactive-function)

(defun restart-report (restart stream)
  (funcall (or (restart-report-function restart)
               (let ((name (restart-name restart)))
		 #'(lambda (stream)
		     (if name (format stream "~s" name)
			      (format stream "~s" restart)))))
           stream))

(defmacro restart-bind (bindings &body forms)
  `(let ((*restart-clusters*
	  (cons (list ,@(mapcar #'(lambda (binding)
				    `(make-restart
				      :name     ',(car binding)
				      :function ,(cadr binding)
				      ,@(cddr binding)))
				bindings))
		*restart-clusters*)))
     ,@forms))


;;; RESTART-CASE

(eval-when (eval compile load)

(defun parse-keyword-pairs (list keys)
  (do ((l list (cddr l))
       (k '() (list* (cadr l) (car l) k)))
      ((or (null l) (not (member (car l) keys)))
       (values (nreverse k) l))))

(defmacro with-keyword-pairs ((names expression &optional keywords-var)
			      &body forms)
  (let ((temp (member '&rest names)))
    (unless (= (length temp) 2)
      (error "&rest keyword is ~:[missing~;misplaced~]." temp))
    (let ((key-vars (ldiff names temp))
          (key-var (or keywords-var (gensym)))
          (rest-var (cadr temp)))
      (let ((keywords (mapcar #'(lambda (x)
				  (intern (string x) (find-package "keyword")))
			      key-vars)))
        `(multiple-value-bind (,key-var ,rest-var)
             (parse-keyword-pairs ,expression ',keywords)
           (let ,(mapcar #'(lambda (var keyword)
			     `(,var (getf ,key-var ,keyword)))
			 key-vars keywords)
             ,@forms))))))

)

(defmacro restart-case (expression &body clauses)
  (flet ((transform-keywords (&key report interactive)
	   (let ((result '()))
	     (when report
	       (setq result (list* (if (stringp report)
				       `#'(lambda (stream)
					    (write-string ,report stream))
				       `#',report)
				   :report-function
				   result)))
	     (when interactive
	       (setq result (list* `#',interactive
				   :interactive-function
				   result)))
	     (nreverse result))))
    (let ((block-tag (gensym))
	  (temp-var  (gensym))
	  (data
	   (mapcar #'(lambda (clause)
		       (with-keyword-pairs ((report interactive &rest forms)
					    (cddr clause))
			 (list (car clause) ;name=0
			       (gensym)	;tag=1
			       (transform-keywords :report report ;keywords=2
						   :interactive interactive)
			       (cadr clause) ;bvl=3
			       forms)))	;body=4
		   clauses)))
      `(block ,block-tag
	 (let ((,temp-var nil))
	   (tagbody
	      (restart-bind
	         ,(mapcar #'(lambda (datum)
			      (let ((name (nth 0 datum))
				    (tag  (nth 1 datum))
				    (keys (nth 2 datum)))
				`(,name #'(lambda (&rest temp)
					    #+lispm
					    (setq temp (copy-list temp))
					    (setq ,temp-var temp)
					    (go ,tag))
					,@keys)))
			  data)
	       (return-from ,block-tag ,expression))
	      ,@(mapcan #'(lambda (datum)
			    (let ((tag  (nth 1 datum))
				  (bvl  (nth 3 datum))
				  (body (nth 4 datum)))
			      (list tag
				    `(return-from ,block-tag
				       (apply #'(lambda ,bvl ,@body)
					      ,temp-var)))))
			data)))))))

(defmacro with-simple-restart ((restart-name format-string
					     &rest format-arguments)
			       &body forms)
  `(restart-case (progn ,@forms)
      (,restart-name ()
	 :report (lambda (stream)
		   (format stream ,format-string ,@format-arguments))
	 (values nil t))))

(defmacro hostx:with-dynamic-area (&body forms)
  `(progn ,@forms))

;I am sure Genera has this. 
;Here, static means not collectable by GC, but scanned by GC.
(defmacro hostx:with-static-area (&body forms)
  `(progn ,@forms))

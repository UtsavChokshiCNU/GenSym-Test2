;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; emacros.lisp -- error system macros
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  06 Jul 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;
;;; We don't support a full condition system yet, so these are the
;;; stupid CLtL-I versions of the error macros.
;;; Probably all of these macros ought to be rewritten when the condition
;;; system is present.  Also it would probably be a good idea to hide a lot
;;; of the details behind helper functions or C macros in the run-time.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/emacros.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2007/05/25 13:59:56 $")

;;; Check-type and assert are pretty similar.


;;; This helper function isn't implemented in the runtime yet, so
;;; we'll use a translator-macro for now.

(define-translator-macro trun:prompt-for-value (place-info)
  `(progn
     (format t "~%Enter a new value for ~A" ',place-info)
     (read)))

(define-translator-parameter *use-condition-system-p* nil)

(define-translator-macro check-type (place type &optional type-string
					   &environment env)
  (let ((place-form (translator-macroexpand place env))
	(place-type 't))
    (when (and (consp place-form) (eq (car place-form) 'the))
      (setq place-type (cadr place-form))
      (setq place-form (caddr place-form)))
    (multiple-value-bind (value valuep)
	(translator-constant-value place-form env)
	(cond (valuep
	       (when (translator-typep value type)
		(return-from check-type 'nil))
	       (error
		"The first argument to ~S is a constant not of type ~S"
		'check-type type))
	      ((translator-subtypep place-type type)
	       (return-from check-type 'nil)))))
  (if *use-condition-system-p*
      (clcs-check-type place type type-string)
      (simple-check-type place type type-string)))

(defun clcs-check-type (place type type-string)
  (let ((tag1 (make-symbol "BLOCK-TAG"))
	(tag2 (make-symbol "TAGBODY-TAG")))
    `(block ,tag1
       (tagbody ,tag2
	 (if (typep ,place ',type) (return-from ,tag1 nil))
	 (restart-case ,(if type-string
			    `(error "The value of ~s is ~s, ~
				     which is not ~a."
				    ',place ,place ,type-string)
			    `(error "The value of ~s is ~s, ~
				     which is not of type ~s."
				    ',place ,place ',type))
	   (store-value (value)
	       :report (lambda (stream)
			 (format stream "supply a new value of ~s."
				 ',place))
	       :interactive read-evaluated-form
	     (setf ,place value)
	     (go ,tag2)))))))

(defun simple-check-type (place type string)
  (let ((error-string
	 (if string
	     (format nil "The value of ~s, ~~s, is not ~a." place string)
	     (format nil "The value of ~s, ~~s, is not of type ~s."
		     place type)))
	(continue-string
	 (format nil "You will be asked to supply a new value for ~s."
		 place))
	(begin-tag
	 (make-symbol "TEST")))
    `(tagbody
	,begin-tag
	(unless (tcl:typep ,place ',type)
	  (tcl:cerror ,continue-string ,error-string ,place)
	  (setf ,place (trun:prompt-for-value ',place))
	  (go ,begin-tag)))))

(define-translator-macro assert 
    (test-form &optional places datum &rest arguments)
  (if *use-condition-system-p*
      (clcs-assert test-form places datum arguments)
      (simple-assert test-form places datum arguments)))

(defun clcs-assert (test-form places datum arguments)
  (let ((tag (make-symbol "TAGBODY-TAG")))
    `(tagbody ,tag
       (unless ,test-form
	 (restart-case ,(if datum
			    `(error ,datum ,@arguments)
			    `(simple-assertion-failure ',test-form))
	   (continue ()
	       :report (lambda (stream) (assert-report ',places stream))
	     ,@(mapcar #'(lambda (place)
			   `(setf ,place (assert-prompt ',place ,place)))
		       places)
             (go ,tag)))))))

(defun simple-assert (test-form places string args)
  (let ((continue-string
	 (cond ((null places)
		"The test will be tried again.")
	       ((null (cdr places))
		(format nil
			"You will be asked to supply a new value for ~s."
			(car places)))
	       (t
		(format nil
			"You will be asked to supply new values for ~s."
			places))))
	(error-string
	 (or string "ASSERT failed."))
	(begin-tag
	 (make-symbol "TEST")))
    `(tagbody
	,begin-tag
	(unless ,test-form
	  (tcl:cerror ,continue-string ,error-string ,@args)
	  ,@(mapcar
	     #'(lambda (p) `(setf ,p (trun:prompt-for-value ',p)))
	     places)
	  (go ,begin-tag)))))

(defun accumulate-cases (macro-name cases list-is-atom-p)
  (do ((l '())
       (c cases (cdr c)))
      ((null c) (nreverse l))
    (let ((keys (caar c)))
      (cond ((atom keys)
	     (cond ((null keys))
		   ((member keys '(otherwise t))
		    (error "Otherwise is not allowed in ~s expressions."
			   macro-name))
		   (t (push keys l))))
	    (list-is-atom-p
	     (push keys l))
	    (t
	     (dolist (key keys) (push key l)))))))

;;; Likewise, ETYPECASE, CTYPECASE, ECASE, and CCASE.

(define-translator-macro etypecase (keyform &rest cases)
  (if *use-condition-system-p*
      (clcs-etypecase keyform cases)
      (simple-etypecase keyform cases)))

(defun clcs-etypecase (keyform cases)
  (let ((types (accumulate-cases 'etypecase cases t))
	(var (make-symbol "KEY")))
    `(let ((,var ,keyform))
       (typecase ,var
	 ,@cases
	 (otherwise
	   (error 'case-failure :name 'etypecase
		  		:datum ,var
				:expected-type '(or ,@types)
				:possibilities ',types))))))

(defun simple-etypecase (keyform clauses)
  `(typecase ,keyform
     ,@clauses
     (t
      (tcl:error
       ,(format nil "The type of ~s (~~s), is not one of ~s."
		keyform
		(gather-keys clauses))
       ,keyform))))

(define-translator-macro ctypecase (keyplace &rest cases)
  (if *use-condition-system-p*
      (clcs-ctypecase keyplace cases)
      (simple-ctypecase keyplace cases)))

(defun clcs-ctypecase (keyplace cases)
  (let ((types (accumulate-cases 'ctypecase cases t))
	(tag1 (make-symbol "BLOCK-TAG"))
	(tag2 (make-symbol "TAGBODY-TAG")))
    `(block ,tag1
       (tagbody ,tag2
	 (return-from ,tag1
	   (typecase ,keyplace
	     ,@cases
	     (otherwise
	       (restart-case (error 'case-failure
				    :name 'ctypecase
				    :datum ,keyplace
				    :expected-type '(or ,@types)
				    :possibilities ',types)
		 (store-value (value)
		     :report (lambda (stream)
			       (format stream "Supply a new value of ~s."
				       ',keyplace))
		     :interactive read-evaluated-form
		   (setf ,keyplace value)
		   (go ,tag2))))))))))

(defun simple-ctypecase (keyplace clauses)
  (let ((label  (make-symbol "TEST"))
	(block  (make-symbol "END"))
	(cmsg   (format nil "You will be asked to supply a new value for ~s."
			keyplace))
	(emsg   (format nil "The type of ~s (~~s), is not one of ~s."
			keyplace (gather-keys clauses))))
    `(block ,block
       (tagbody
	  ,label
	  (return-from ,block
	    (typecase ,keyplace
	      ,@clauses
	      (t
	       (tcl:cerror ,cmsg ,emsg ,keyplace)
	       (setf ,keyplace (trun:prompt-for-value ',keyplace))
	       (go ,label))))))))

(define-translator-macro ecase (keyform &rest cases)
  (if *use-condition-system-p*
      (clcs-ecase keyform cases)
      (simple-ecase keyform cases)))

(defun clcs-ecase (keyform cases)
  (let ((keys (accumulate-cases 'ecase cases nil))
	(var (make-symbol "KEY")))
    `(let ((,var ,keyform))
       (case ,var
	 ,@cases
	 (otherwise
	   (error 'case-failure :name 'ecase
		  		:datum ,var
				:expected-type '(member ,@keys)
				:possibilities ',keys))))))

(defun simple-ecase (keyform clauses)
  `(case ,keyform
     ,@clauses
     (t
      (tcl:error
       ,(format nil "The value of ~s (~~s), is not one of ~s."
		keyform
		(gather-keys clauses))
       ,keyform))))

(define-translator-macro ccase (keyplace &rest cases)
  (if *use-condition-system-p*
      (clcs-ccase keyplace cases)
      (simple-ccase keyplace cases)))

(defun clcs-ccase (keyplace cases)
  (let ((keys (accumulate-cases 'ccase cases nil))
	(tag1 (make-symbol "BLOCK-TAG"))
	(tag2 (make-symbol "TAGBODY-TAG")))
    `(block ,tag1
       (tagbody ,tag2
	 (return-from ,tag1
	   (case ,keyplace
	     ,@cases
	     (otherwise
	       (restart-case (error 'case-failure
				    :name 'ccase
				    :datum ,keyplace
				    :expected-type '(member ,@keys)
				    :possibilities ',keys)
		 (store-value (value)
		     :report (lambda (stream)
			       (format stream "Supply a new value of ~s."
				       ',keyplace))
		     :interactive read-evaluated-form
		   (setf ,keyplace value)
		   (go ,tag2))))))))))

(defun simple-ccase (keyplace clauses)
  (let ((label  (make-symbol "TEST"))
	(block  (make-symbol "END"))
	(cmsg   (format nil "You will be asked to supply a new value for ~s."
			keyplace))
	(emsg   (format nil "The value of ~s (~~s), is not one of ~s."
			keyplace (gather-keys clauses))))
    `(block ,block
       (tagbody
	  ,label
	  (return-from ,block
	    (case ,keyplace
	      ,@clauses
	      (t
	       (tcl:cerror ,cmsg ,emsg ,keyplace)
	       (setf ,keyplace (trun:prompt-for-value ',keyplace))
	       (go ,label))))))))

;;; A helper function for the above:  gather all the keys that appear
;;; in a CASE or TYPECASE.

(defun gather-keys (clauses)
  (cond ((null clauses)
	 nil)
	((atom (car (car clauses)))
	 (cons (car (car clauses)) (gather-keys (cdr clauses))))
	(t
	 (append (car (car clauses)) (gather-keys (cdr clauses))))))


;;; When the full condition system is implemented, the following macro
;;; will go here too:
;;;
;;; with-condition-restarts


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
          (key-var (or keywords-var (make-symbol "KEY")))
          (rest-var (cadr temp)))
      (let ((keywords (mapcar #'(lambda (x) (intern (string x)
						    (find-package "KEYWORD")))
			      key-vars)))
        `(multiple-value-bind (,key-var ,rest-var)
             (parse-keyword-pairs ,expression ',keywords)
           (let ,(mapcar #'(lambda (var keyword) `(,var (getf ,key-var ,keyword)))
                                 key-vars keywords)
             ,@forms))))))

);nehw-lave

;;; restarts


(define-translator-macro restart-bind (bindings &body forms)
  (unless *use-condition-system-p*
    (error "Use of ~S. Please set ~S to T, and retranslate"
	   'restart-bind '*use-condition-system-p*))
  `(let ((*restart-clusters*
	  (cons (list ,@(mapcar #'(lambda (binding)
				    `(make-restart
				      :name     ',(car binding)
				      :function ,(cadr binding)
				      ,@(cddr binding)))
				bindings))
		*restart-clusters*)))
     ,@forms))

(define-translator-macro restart-case (expression &body clauses)
  (unless *use-condition-system-p*
    (error "Use of ~S. Please set ~S to T, and retranslate"
	   'restart-case '*use-condition-system-p*))
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
    (let ((block-tag (make-symbol "BLOCK-TAG"))
	  (temp-var  (make-symbol "ARGS"))
	  (data
	    (mapcar #'(lambda (clause)
			(with-keyword-pairs ((report interactive &rest forms)
					     (cddr clause))
			  (list (car clause)			   ;name=0
				(make-symbol "TAGBODY-TAG")        ;tag=1
				(transform-keywords :report report ;keywords=2
						    :interactive interactive)
				(cadr clause)			   ;bvl=3
				forms)))			   ;body=4
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
					  #+lispm (setq temp (copy-list temp))
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

(define-translator-macro with-simple-restart ((restart-name format-string
					     &rest format-arguments)
			       &body forms)
  
  (unless *use-condition-system-p*
    (error "Use of ~S.  Please set ~S to T, and retranslate"
	   'with-simple-restart '*use-condition-system-p*))
  `(restart-case (progn ,@forms)
     (,restart-name ()
        :report (lambda (stream)
		  (format stream ,format-string ,@format-arguments))
      (values nil t))))

(define-translator-macro handler-bind (bindings &body forms)
  (unless *use-condition-system-p*
    (error "Use of ~S. Please set ~S to T, and retranslate"
	   'handler-bind '*use-condition-system-p*))
  (unless (every #'(lambda (x) (and (listp x) (= (length x) 2))) bindings)
    (error "ill-formed handler bindings."))
  `(let ((*handler-clusters*
	  (cons (list ,@(mapcar #'(lambda (x) `(cons ',(car x) ,(cadr x)))
				bindings))
		*handler-clusters*)))
     ,@forms))

(define-translator-macro handler-case (form &rest cases)
  (unless *use-condition-system-p*
    (error "Use of ~S. Please set ~S to T, and retranslate"
	   'handler-case '*use-condition-system-p*))
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
	(let ((tag (make-symbol "BLOCK-TAG"))
	      (var (make-symbol "CONDITION-VAR"))
	      (annotated-cases (mapcar #'(lambda (case)
					   (cons (make-symbol "TAGBODY-TAG")
						 case))
				       cases)))
	  `(block ,tag
	     (let ((,var nil))
	       ,var				;ignorable
	       (tagbody
		 (handler-bind
		  ,(mapcar #'(lambda (annotated-case)
			       (list (cadr annotated-case)
				     `#'(lambda (temp)
					  ,@(if (caddr annotated-case)
						`((setq ,var temp)))
					  (go ,(car annotated-case)))))
			   annotated-cases)
			       (return-from ,tag ,form))
		 ,@(mapcan #'(lambda (annotated-case)
			       (list
				(car annotated-case)
				(let ((body (cdddr annotated-case)))
				  `(return-from ,tag
				     ,(cond ((caddr annotated-case)
					     `(let ((,(caaddr annotated-case)
						     ,var))
						,@body))
					    ((not (cdr body))
					     (car body))
					    (t
					     `(progn ,@body)))))))
			   annotated-cases))))))))

(define-translator-macro ignore-errors (&rest forms)
  (unless *use-condition-system-p*
    (error "Use of ~S. Please set ~S to T, and retranslate"
	   'ignore-errors '*use-condition-system-p*))
  `(handler-case (progn ,@forms)
     (error (condition) (values nil condition))))


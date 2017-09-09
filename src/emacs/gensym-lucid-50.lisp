;;; -*- Syntax: Common-lisp; Base: 10; Mode: Lisp; Package: ILISP; -*-

;;;; Mr AB's patches to the lisp side of the Ilisp interface.

(in-package "ILISP")

(export '(ilisp-eval ilisp-pretty-arglist ilisp-describe-variable
	  ilisp-describe-function ilisp-callers ilisp-source-files
	  ilisp-function-describers))


;; We replace the Lucid init file: lucid.lisp is not loaded.


;;; Wrap lcl:with-deferred-warnings around the evaluation.
;;; This prevents "undefined" warnings about recursive functions.

(defun ilisp-eval (form package filename &optional redefinition-action)
  "Evaluate FORM in PACKAGE recording FILENAME as the source file."
  (princ " ")
  (let* ((*package* (ilisp-find-package package))
	 (lcl:*source-pathname*
	   (if (probe-file filename)
	       (truename filename)
	       (merge-pathnames filename)))
	 (lcl:*redefinition-action* redefinition-action))
    (lcl:with-deferred-warnings
	(eval (read-from-string form)))))


;; Modify to pass :WARN to ilisp-eval, so that we get redefinition warnings.

(defun ilisp-compile (form package filename)
  "Compile FORM in PACKAGE recording FILENAME as the source file."
  (princ " ")
  (labels ((compiler (form env)
	     (if (and (consp form)
		      (eq (first form) 'function)
		      (consp (second form)))
		 ;; If we have just compiled a named-lambda, and the name
		 ;; didn't make it in to the procedure object, then stuff the
		 ;; appropriate symbol in to the procedure object.
		 (let* ((proc (evalhook `(compile nil ,form) nil nil env))
			(old-name (and proc (sys:procedure-ref proc 1)))
			(lambda (second form))
			(name (and (eq (first lambda) 'lucid::named-lambda)
				   (second lambda))))
		   (when (or (null old-name)
			     (and (consp old-name) (eq :internal (car old-name))))
		     (setf (sys:procedure-ref proc 1) name))
		   proc)
		 (evalhook form #'compiler nil env))))
    (let ((*evalhook* #'compiler))
      (ilisp-eval form package filename :warn))))



;; G2 pushes interesting things onto this list.
(defparameter function-descriptions '((macro-function " (Macro)")
				      (special-form-p " (Special Form)")
				      generic-function-description
				      (function-advised-p " (Advised)")))

(defun generic-function-description (symbol)
  (let ((proc (lucid:get-unadvised-procedure (symbol-function symbol))))
    (when (system:generic-function-p proc)
      (format nil " (Generic ~d)"
	      (length (funcall (intern "GENERIC-FUNCTION-METHODS" "CLOS") proc))))))

(defun function-advised-p (symbol)
  (not (eq (lucid:get-unadvised-procedure (symbol-function symbol))
	   (symbol-function symbol))))
  
(defun ilisp-function-description (symbol)
  (loop for describer in function-descriptions
	for string = (if (consp describer)
			 (and (funcall (car describer) symbol)
			      (cadr describer))
			 (funcall describer symbol))
	when string
	  do (return string)))




;; Redefined.
(defun ilisp-function-short-description (symbol)
  (ilisp-function-description symbol))


;; Redefined.
(defun get-function-arglist (symbol)
  (let* ((proc (lucid:get-unadvised-procedure (symbol-function symbol)))
	 (a (lcl:ignore-errors (lcl:arglist proc)))
	 (arglist (ldiff a (member '&aux a))))
    arglist))




(defvar ilisp-function-describers () "A list of other functions on (symbol) which print stuff.")

;;; Bound to c-sh-D or m-sh-D.

(defun ilisp-describe-function (symbol package)
  "Print the arglist and the documentation string for the function named by SYMBOL."
  (ilisp-errors
   (let ((fn (ilisp-find-symbol symbol package)))
     (cond ((null fn)
	    (format t "Symbol ~s not present in ~s." symbol package))
	   ((not (fboundp fn))
	    (format t "~s: undefined~%" fn))
	   (t
	    (let ((*print-pretty* t)
		  (*print-length* nil))
	      (print-function-arglist fn))
	    (let ((doc (documentation fn 'function))
		  (src (lcl:get-source-file fn nil t)))
	      (when doc
		(format t "~&~a~%" doc))
	      (when src
		(loop for (type . pathname) in src doing
		  (format t " Defined in ~(~a.~a~)~%" (pathname-name pathname) (pathname-type pathname))))
	      (dolist (describer ilisp-function-describers)
		(funcall describer fn)))))))
  (values))






;;; Quick describe-variable (c-sh-V)

(defun ilisp-describe-variable (sexp package)
  "Describe SEXP in PACKAGE."
  (ilisp-errors
   (let ((*package* (ilisp-find-package package)))
     (let ((var (read-from-string sexp)))
       (cond ((symbolp var)
	      (format t "Variable ~s" var)
	      #+Lucid (when (system:proclaimed-special-p var)
			(format t " (special)"))
	      (let ((*print-length* 1))
		(if (boundp var)
		  (format t ": ~s" (symbol-value var))
		  (format t ": unbound")))
	      #+ignore (let ((paths (lcl:Get-source-file var nil t)))
			(when paths
			  (format t "in ~a" (cdar paths)))))
	     (t
	      (describe (eval var)))))))
   (values))


;;; Redefine to use AB's who-calls function.
;; Needs an option to limit the max number of callers to return.

;; However, since there is no who-calls function belonging to AB, we will just
;; use Lucid's for now -cshapiro, 11/1/00

(defun ilisp-callers (symbol package)
  "Print the callers of PACKAGE::SYMBOL.  Only compiled functions
currently.  Return T if successful."
  (ilisp-errors
   (when (find-package "AB")
     (let* ((function-name (ilisp-find-symbol symbol package))
	    (*print-level* nil)
	    (*print-length* nil))
       (when (and function-name (fboundp function-name))
	 (dolist (caller (lcl:find-callers function-name)) 
	   (print caller))
	 t)))))



(defun ilisp-source-files (symbol package type)
  "Print each file for PACKAGE:SYMBOL's TYPE definition on a line and
return T if successful."
  (ilisp-errors
   (let* ((symbol (ilisp-find-symbol symbol package))
	  (all (equal type "any"))
	  (type (unless all (ilisp-find-symbol type package)))
	  (paths (when symbol
		   (lucid::get-source-file symbol type all))))
     (if paths
	 (progn
	   (if all
	       (dolist (file (remove-duplicates paths
						:key #'cdr :test #'equal))
		 (print (namestring (cdr file))))
	       (print (namestring paths)))
	   t)
	 nil))))



(defun argument-names (arglist)
  (labels ((tree-atoms (tree)
	     (cond ((null tree) nil)
		   ((member tree lambda-list-keywords) nil)
		   ((atom tree) (list tree))
		   (t
		    (argument-names tree)))))
    (nconc
      (loop while arglist
	    as argument = (pop arglist)
	    until (member argument lambda-list-keywords)
	    nconc (tree-atoms argument))
      (loop while arglist
	    as argument = (pop arglist)
	    nconc (list (if (atom argument) argument (car argument)))))))
    



(defun ilisp-align-arguments (form)
  "Matchup the dummy and actual arguments in the current form"
  (let* ((form (if (stringp form) (read-from-string form) form))
	 (name (pop form))
	 (arglist (lcl:arglist name))
	 (width (loop for arg in arglist
		      for name = (if (consp arg) (car arg) arg)
		      unless (member arg lambda-list-keywords)
			maximize (length (string name))))
	 (*print-length* 3)
	 (*print-level* 2))
    (format t "~&Arguments in call to ~a~s:~%"
	    (if (macro-function name) "the macro " "") name)

    (cond #+someday
	  ((macro-function name)
	   (let* ((argument-names (argument-names arglist))
		  (boffo (loop for name in argument-names
			       collect `'',name
			       collect (list 'list ''quote name)))
		  (dummy `(defmacro ilisp-dummy ,arglist
			    (list 'list ,@boffo))))
	     (eval dummy)
	     (loop for (name value) on (eval `(ilisp-dummy ,@form)) by #'cddr doing
	       (format t "~(~v@a: ~s~)~%" width name value))))
	  (t
	   (loop with once
		 with optional = nil
		 for arg in arglist
		 doing

	     (when (and (null form) (null once))
	       (format t (if optional "Defaulted:~%" "Missing:~%"))
	       (setq once t))

	     (cond ((eq arg '&optional)
		    (setq optional t))
		   ((member arg lambda-list-keywords))
		   (t
		    (let* ((name (if (consp arg) (car arg) arg))
			   (default (cond ((consp arg) (cadr arg))
					  (optional nil)
					  (t '|missing|)))
			   (value (if form (pop form) default)))
		      (if (eq value '|missing|)
			  (format t "~(~v@a~)~%" width name)
			  (format t "~(~v@a: ~s~)~%" width name value))))))
	   (when form
	     (format t "Leftover arguments: ~s~%" form))))
    (values)))

;; Make this work for &rest and &key, as well as macro destructuring.




(defun ilisp-macroexpand-better (form)
  "Macroexpand the form once. Does a bit of code-walking to find interior macro calls."
  (if (atom form)
      form
      (let ((fun (car form)))
	(case fun
	  ;; 0 unevaluated args.
	  ((progn prog1 if block multiple-value-prog1 progv throw catch tagbody unwind-protect)
	   `(,fun ,@(mapcar #'ilisp-macroexpand-better (cdr form))))
	  
	  ;; 1 unevaluated arg.
	  ((eval-when flet labels macrolet return-from the)
	   `(,(first form) ,(second form)
	      ,@(mapcar #'ilisp-macroexpand-better (cddr form))))

	  ;; 2 unevaluated args.
	  ((defun defmacro)		    ; Expand the body, and leave the defun alone.
	   `(,(first form) ,(second form) ,(third form)
	      ,@(mapcar #'ilisp-macroexpand-better (cdddr form))))

	  ;; Special
	  ((let let*)
	   `(,fun
	       ,(loop for binding in (cadr form)
		      collect (if (atom binding)
				  binding
				  (list (car binding) (ilisp-macroexpand-better (cadr binding)))))
	       ,@(mapcar #'ilisp-macroexpand-better (cddr form))))

	  ;; Special
	  ((setq psetq)
	   `(,fun ,@(loop for (name value) on (cdr form) by 'cddr
			  collect name
			  collect (ilisp-macroexpand-better value))))
	  
	  ;; Special
	  ((declare)
	   form)
	  (t
	   (cond ((and (symbolp fun)
		       (not (or (special-form-p fun)
				(macro-function fun))))
		  `(,fun ,@(mapcar #'ilisp-macroexpand-better (cdr form))))
		 (t
		  (macroexpand-1 form))))))))



(defun ilisp-macroexpand-n (expression package &optional (count 1))
  "Macroexpand EXPRESSION to N times."
  (ilisp-errors
   (let* ((*print-length* nil)
	  (*print-level* nil)
	  (*package* (ilisp-find-package package))
	  (form (read-from-string expression))
	  (last-form nil))
     (loop repeat count
	   until (equal form last-form)
	   do (setq last-form form
		    form (ilisp-macroexpand-better form)))
     (let ((*print-case* :downcase))
       (pprint form)))))

			

(defun ilisp-macroexpand-all (form)
  (let ((last-form nil))
    (loop repeat 100
	  until (equal form last-form)
	  do (setq last-form form
		   form (ilisp-macroexpand-better form)))
    form))



;; Redefine this to call the better function.  -fmw, 10/13/93
(defun ilisp-macroexpand (expression package)
  "Macroexpand EXPRESSION until it stops changing."
  (ilisp-macroexpand-n expression package 100))



;;; Compile a function with :development removed from the features list.

(defun ilisp-compile-in-ab-build-context (form package filename)
  (let ((*features* (remove :development *features*)))
    (declare (special *features*))
    (ilisp-compile form package filename)))


(defun ilisp-current-debugger-function ()
  (declare (special sys:*frame-environment* sys:*frame-index*))
  (when (and (boundp 'sys:*frame-environment*)
	     (boundp 'sys:*frame-index*))
    (sys:stack-frame-name sys:*frame-index* sys:*frame-environment*)))

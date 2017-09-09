;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; transform-lambda.lisp -- transform lambda form to let/let*
;;;
;;; Author :  Kim Barrett
;;; Date   :  5 Nov 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/transform-lambda.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:13 $")

;;; TRANSFORM-LAMBDA-TO-LET                                    [Function]
;;;
;;; Purpose:
;;;
;;;  This function attempts to transform a ((LAMBDA lambda-list . body) . args)
;;;  form into an equivalent LET or LET* form.
;;;
;;; Syntax:
;;;
;;;  transform-lambda-to-let form environment
;;;			     &optional allow-other-keys subform-expander
;;;
;;; Arguments:
;;;
;;;  form -- A list whose CAR is a lambda expression and CDR is a list of
;;;  arguments for the lambda expression.
;;;
;;;  environment -- A translator environment object in which the form is to be
;;;  processed. 
;;;
;;;  allow-other-keys -- A boolean flag.  If true and the lambda-list of the
;;;  lambda expression contains &key, then the lambda-list is treated as if it
;;;  also contained &allow-other-keys.
;;;
;;;  subform-expander -- A function of two arguments -- a form and an
;;;  environment -- or the name of such a function.  This function may be
;;;  applied to subforms of the original form in order to simplify them.
;;;
;;; Values:
;;;
;;;  form -- A form.  This will be either a new form which is semantically
;;;  equivalent to the original form but expressed in terms of LET and LET*
;;;  rather than a lambda expression, or it will be the original (EQL) form
;;;  argument, indicating that it was unable to perform the transformation.
;;;
;;; Remarks:
;;;
;;;  Current failure cases:
;;;
;;;  1. Too few or two many arguments supplied.
;;;  2. Odd number of arguments for keyword processing.
;;;  3. Some keywords not resolvable to compile-time constant value.
;;;  4. Some keywords not matched and neither &allow-other-keys specified in
;;;     lambda-list nor :allow-other-keys true (determinable at compile-time)
;;;     specified in keyword arguments.
;;;
;;;  Cases 1 and 2, and compile-time resolvable cases of 4 are errors.  No
;;;  errors or warnings are signaled for these cases however, it being assumed
;;;  that the mechanism for processing function calls will presumably take care
;;;  of that.
;;;
;;;  There is a subset of case (3) that could still be transformed.  If
;;;  arguments to the left of the unresolved keyword supply values for all of
;;;  the keyword parameters, the transformation could still be performed if
;;;  exact key checking were disabled, or if code were inserted to ensure that
;;;  the runtime value of the unresolved keyword matches one of the keyword
;;;  parameters.  This has not been implemented.
;;;
;;;  There is a subset of case (4) that could still be transformed.  If
;;;  :allow-other-keys is present but its value cannot be determined at compile
;;;  time, code could be added to examine the value at runtime and signal an
;;;  error if it is Nil.  This check can be elided when the code is unsafe.
;;;  This has not been implemented.


(defun transform-lambda-to-let1 (form allow-other-keys)
  (let ((lambda-expression (car form))
	(args (cdr form)))
    (let ((lambda-list (cadr lambda-expression))
	  (body (cddr lambda-expression))
	  (let-bindings ())
	  (let-ignore ())
	  (let*-bindings ())
	  (let*-ignore ())
	  (rest nil)
	  (keyp nil)
	  (keys ())
	  (aux ()))
      (macrolet ((bind (var val)
		   `(push (list ,var ,val) let-bindings))
		 (bind* (var val)
		   `(push (list ,var ,val) let*-bindings))
		 (fail-to-transform ()
		   `(return-from transform-lambda-to-let1 nil)))
	;; Step 1: Parse the lambda-list, collecting bindings for positional
	;; parameters and information needed for processing &rest, &key, and
	;; &aux arguments.
	;; Process the lambda-list.
	(parse-lambda-list 
	 lambda-list
	 :required #'(lambda (var)
		       (if (endp args)
			   ;; If not enough arguments, punt transformation.
			   (fail-to-transform)
			   ;; Otherwise, LET-bind var to next arg.
			   (bind var (pop args))))
	 :optional #'(lambda (var init initp svar svar-p)
		       (declare (ignore initp))
		       (if (endp args)
			   ;; If no more arguments, LET*-bind var to its initform,
			   ;; and LET*-bind svar to nil if present.
			   (progn
			     (bind* var init)
			     (when svar-p (bind* svar nil)))
			   ;; Otherwise, LET-bind var to next arg and LET-bind svar
			   ;; to t if present.
			   (progn
			     (bind var (pop args))
			     (when svar-p (bind svar t)))))
	 :rest #'(lambda (var)
		   (setf rest var))
	 :keyp #'(lambda ()
		   (setf keyp t))
	 :key #'(lambda (var key init initp svar svar-p)
		  (declare (ignore initp))
		  (push (list* key var init (when svar-p (list svar))) keys))
	 :allow-other-keys-p #'(lambda ()
				 (setf allow-other-keys t))
	 :aux #'(lambda (var init initp)
		  (declare (ignore initp))
		  (push (list var init) aux))))
      (setf keys (nreverse keys))
      (setf aux (nreverse aux))
      (values lambda-expression args body 
	      let-bindings let-ignore let*-bindings let*-ignore
	      rest keyp keys aux allow-other-keys))))

(defun transform-lambda-to-let
    (form env &optional allow-other-keys (subform-expander #'apply-macros))
  (multiple-value-bind (lambda-expression args body 
			let-bindings let-ignore let*-bindings let*-ignore
			rest keyp keys aux allow-other-keys)
      (transform-lambda-to-let1 form allow-other-keys)
    (unless lambda-expression
      (return-from transform-lambda-to-let form))
    (macrolet ((bind (var val)
		 `(push (list ,var ,val) let-bindings))
	       (bind* (var val)
		 `(push (list ,var ,val) let*-bindings))
	       (fail-to-transform ()
		 `(return-from transform-lambda-to-let form))
	       (expand-subform (form env)
		 `(funcall subform-expander ,form ,env)))
      (flet (;; This function is used to bind &rest-like variables.  The
	     ;; decision of whether to LET-bind or LET*-bind is to try to
	     ;; produce prettier code.  If there are any let* bindings then the
	     ;; &rest var must be bound in the let*.  If there are no let
	     ;; bindings then we do a let* binding, since there won't be any
	     ;; other let bindings and there might be later let* bindings, so
	     ;; avoid generating the let for just the &rest var.
	     (bind-rest (var val &optional ignorep)
	       (cond ((and let-bindings (null let*-bindings))
		      (bind var val)
		      (when ignorep (push var let-ignore)))
		     (t
		      (bind* var val)
		      (when ignorep (push var let*-ignore))))))
	;; If too many arguments, punt the transformation.
	(when (and args (not (or rest keyp))) (fail-to-transform))
	;; Step 2: When &key present, do some grovelling over the remaining
	;; arguments to ensure that the transformation can be performed.
	(when keyp
	  ;; If odd length keylist, punt the transformation.
	  (when (oddp (length args)) (fail-to-transform))
	  ;; Process the remaining arguments, ensuring that the keys are all
	  ;; compile-time constants.  If any keys are not constants, punt the
	  ;; transformation.
	  (do ((args (setf args (copy-list args)) (cddr args))
	       (alwky-seen allow-other-keys))
	      ((endp args))
	    ;; Expand the keyform, in case it macroexpands into a constant.
	    (let ((key (expand-subform (car args) env)))
	      (multiple-value-bind (value therep)
		  (translator-constant-value key env)
		(when (or (not therep) (not (symbolp value)))
		  ;; If key is not a compile-time constant with a known value,
		  ;; cannot resolve it to determine which keyword parameter
		  ;; should be bound in let forms, so punt the transformation.
		  ;; Also punt if constant key is not a symbol, since that's an
		  ;; error.
		  (fail-to-transform))
		;; Store expanded key into args list, so it doesn't need to be
		;; reexpanded later.
		(setf (car args) key)
		(when (eq value :allow-other-keys)
		  (when (not alwky-seen)
		    (setf alwky-seen t)
		    (setf value (expand-subform (cadr args) env))
		    ;; If the value of the :allow-other-keys key is a non-nil
		    ;; constant, set the allow-other-keys flag to true,
		    ;; indicating to later processing that exact key checking is
		    ;; not needed.
		    (multiple-value-setq (value therep)
		      (translator-constant-value value env))
		    (when therep
		      (setf allow-other-keys (and value t)))))))))
	;; Step 3: Generate the bindings for &rest and &key parameters.
	(cond ((endp args)		; no arguments left
	       ;; Bind &rest var to nil when present.
	       (when rest (bind-rest rest nil))
	       ;; LET*-bind all the keyword variables to their initforms, and
	       ;; bind any suppliedp vars to nil.
	       (dolist (parm keys)
		 ;; Can't depend on destructuring-bind being available.
		 (let* ((key (pop parm))
			(var (pop parm))
			(init (pop parm)))
		   (declare (ignore key))
		   (bind* var init)
		   (when (consp parm) (bind* (pop parm) nil)))
		 ))
	      ((or (not keyp) (and (endp keys) allow-other-keys))
	       ;; Either no &key present, or &key with no keywords specified
	       ;; and allow-other-keys true.  In either case, no keyword
	       ;; processing actually needs to be done.
	       (if rest
		   ;; Bind &rest var to list of the remaining arguments.
		   (bind-rest rest `(list ,@args))
		   ;; No &rest var, and the remaining arguments are not going to
		   ;; be referenced by anything.  Still need to arrange for the
		   ;; argument forms to be evaluated, in case of side-effects.
		   ;; This is done by binding a dummy variable to the result of
		   ;; evaluating the remaining arguments in a progn returing nil.
		   (bind-rest (make-symbol "IGNORE") `(progn ,@args nil) t)))
	      ((endp keys)
	       ;; There is an &key, but no keyword parameters were specified,
	       ;; and there are arguments, and allow-other-keys is not known
	       ;; to be true.  Punt the transformation.  Note that this is just
	       ;; a special case of the next clause, and simply avoids some
	       ;; compile-time consing.
	       (fail-to-transform))
	      (t
	       ;; Process &key parameters.
	       ;; Key-map is an alist with entries of the form
	       ;; (key { :temp or :constant } initform), where :temp indicates
	       ;; that the initform is a variable which will be bound to the
	       ;; initform, while :constant indicates that the initform is a
	       ;; constant.
	       (let ((key-map ()))
		 (flet ((update-key-map (key value value-is-constant)
			  (push (list key
				      (if value-is-constant :constant :temp)
				      value)
				key-map))
			(make-key-temp (key)
			  ;; This function is used to create a temp that will be
			  ;; bound to the value for the specified keyword
			  ;; parameter.  Because the common case is to have the
			  ;; keyword variable have the same name as the keyword,
			  ;; it is preferable to have the name of this temp be
			  ;; something different so that it doesn't force the
			  ;; `real' variable to be given a different name due to
			  ;; name conflicts, so a prefix is tacked onto the name
			  ;; of the keyword when constructing the temp name.
			  (make-symbol (format nil "TEMP-~(~A~)" key)))
			)
		   ;; LET-bind temps to the values in the keylist.
		   ;; Record first occurance of keys with the temp bound to the
		   ;; associated value, so we can later LET*-bind the key vars.
		   ;; This record is also used to determine the presence of
		   ;; unrecognized keywords.  While we are at it, if there is a
		   ;; &rest var, build up a list to be used to create it's
		   ;; initform.
		   (do ((rest-list ())	; &rest var initform list (reversed)
			(temp-ref nil))	; flag -- temp referenced
		       ((endp args)
			;; Bind &rest var (when present) to a list of the
			;; collected keys and value forms.  If the initform for
			;; the &rest var doesn't reference any temps, the binding
			;; can be moved up to the let form, rather than binding
			;; it in the let* form (note that there are no let*
			;; bindings yet).  However, if there are no let-bindings
			;; then don't bother shifting it up.
			(when rest
			  (if (or temp-ref (null let-bindings))
			      (bind* rest `(list ,@(nreverse rest-list)))
			      (bind rest `(list ,@(nreverse rest-list))))))
		     (let* ((key (pop args))
			    (value (pop args))
			    (expanded (expand-subform value env)))
		       ;; When there is a &rest var, collect key form for it.
		       (when rest (push key rest-list))
		       ;; These errors due to failure to resolve the key to a
		       ;; constant symbol should never actually be triggered,
		       ;; since the code for determining whether the
		       ;; transformation can be performed at all should have
		       ;; detected these situations and given up.  Note that if
		       ;; the transformation were still permitted under some
		       ;; conditions in spite of unresolvable keywords, this
		       ;; error checking code would need to be changed.
		       (multiple-value-bind (key-value therep constantp)
			   (translator-constant-value key env)
			 (cond ((not constantp)
				(error "Translator bug -- Form should have been ~
                                      verified to be a constant: ~S."
				       key))
			       ((or (not therep) (not (symbolp key-value)))
				(error "Translator bug -- Form should have been ~
                                      verified to be a constant symbol: ~S."
				       key))
			       (t (setf key key-value))))
		       (if (translator-constantp expanded env)
			   (progn
			     ;; When there is a &rest var, collect the constant
			     ;; value for it.
			     (when rest (push expanded rest-list))
			     ;; If the key is already in the map, then previous
			     ;; entry takes precedence and this value can be
			     ;; ignored (since it is a constant).  Otherwise, add
			     ;; the key and constant form to the key map.
			     (unless (assoc key key-map)
			       (update-key-map key expanded t)))
			   (let ((var (make-key-temp key)))
			     (bind var value)
			     ;; When there is a &rest var, collect the temp which
			     ;; is bound to the argument value for it.
			     (when rest
			       (push var rest-list)
			       ;; Note that rest-list contains references to
			       ;; temps in let-bindings, so &rest var must be
			       ;; bound in the let*.
			       (setf temp-ref t))
			     (if (assoc key key-map)
				 ;; If the key is already in the map, then a
				 ;; previous entry for the key was encountered to
				 ;; the left of this one,  which takes
				 ;; precedence.  If we aren't going to be
				 ;; consing up a rest list, then the temp is
				 ;; going to be unreferenced, so add an ignore
				 ;; declaration for it.
				 (unless rest (push var let-ignore))
				 ;; Add the key and associated temp to key map.
				 (update-key-map key var nil)))))))
		 ;; Do exact key checking, adding ignore declarations for any
		 ;; key temps which are permitted but unmatched.
		 (dolist (entry key-map)
		   (unless (assoc (first entry) keys)
		     (if (or allow-other-keys
			     (eq (first entry) :allow-other-keys))
			 (when (eq (second entry) :temp)
			   (push (third entry) let-ignore))
			 (fail-to-transform))))
		 ;; Generate bindings for the keyword vars.
		 (dolist (parm keys)
		   ;; Can't depend on destructuring-bind being available.
		   (let* ((key (pop parm))
			  (var (pop parm))
			  (init (pop parm))
			  (svar-p (consp parm))
			  (svar (when svar-p (pop parm))))
		     (let ((entry (assoc key key-map)))
		       (cond ((null entry)
			      ;; No entry in the key-map, so unsupplied.  Bind
			      ;; key var to initform.  Bind suppliedp var to
			      ;; nil when present.
			      (bind* var init)
			      (when svar-p (bind* svar nil)))
			     ((and (eq (second entry) :constant)
				   (null let*-bindings)
				   let-bindings)
			      ;; If the initarg is a constant and there aren't
			      ;; any let* bindings, we can move the binding of
			      ;; var into the let form.  We only do this when
			      ;; there are already let bindings present.
			      (bind var (third entry))
			      (when svar-p (bind svar t)))
			     (t
			      (bind* var (third entry))
			      (when svar-p (bind* svar t))))))))))
	;; Finish up the binding generation.  Put the binding lists in the proper
	;; order (they are currently reversed).  Add &aux bindings to the end of
	;; the let* bindings.
	(setf let-bindings (nreverse let-bindings))
	(setf let*-bindings (nreconc let*-bindings aux))
	;; Step 4: Generate the expansion.
	(multiple-value-bind (body declspecs doc)
	    (parse-body body t)
	  (declare (ignore doc))
	  (flet ((make-decl (info decl-name)
		   (when info
		     `((declare (,decl-name ,@info)))))
		 (make-declarations (declspecs)
		   (mapcar #'(lambda (declspec) `(declare ,declspec))
			   declspecs)))
	    (cond ((null let*-bindings)
		   `(let ,let-bindings
		      ,@(make-declarations declspecs)
		      ,@(make-decl let-ignore 'ignore)
		      ,@body))
		  ((null let-bindings)
		   `(let* ,let*-bindings
		      ,@(make-declarations declspecs)
		      ,@(make-decl let*-ignore 'ignore)
		      ,@body))
		  (t
		   ;; When there are both let bindings and let* bindings, need
		   ;; to move any declarations related to the variables in the
		   ;; let bindings list up to the let, leaving all the rest of
		   ;; the declarations at the head of the body for the let*.
		   (let ((let-vars (mapcar #'car let-bindings))
			 (let-decls ())
			 (let*-decls ()))
		     (multiple-value-bind (v-decls f-decls set-r-decls r-decls)
			 (translator-parse-declarations
			  declspecs env
			  :variable (nconc (mapcar #'car let*-bindings)
					   let-vars))
		       ;; Seperate declarations related to vars in the
		       ;; let-bindings list from other variable declarations.
		       (dolist (decl v-decls)
			 (if (member (car decl) let-vars)
			     (push decl let-decls)
			     (push decl let*-decls)))
		       ;; Restore order of parsed information
		       (setf let-decls (nreverse let-decls))
		       (setf let*-decls (nreverse let*-decls))
		       `(let ,let-bindings
			  ,@(make-decl let-decls 'tx:variable-information)
			  ,@(make-decl let-ignore 'ignore)
			  (let* ,let*-bindings
			    ,@(make-decl let*-decls 'tx:variable-information)
			    ,@(make-decl f-decls 'tx:function-information)
			    ,@(make-decl set-r-decls
					 'tx:set-declaration-information)
			    ,@(make-decl r-decls 'tx:declaration-information)
			    ,@(make-decl let*-ignore 'ignore)
			    ,@body))))))))))))

#| test code

(defparameter *test-forms*
  '(;; Examples of &optional and &rest parameters
    (
     ((lambda (a b) (+ a (* b 3))) 4 5)
     (let ((a 4)
	   (b 5))
       (+ a (* b 3)))
     19)
    (
     ((lambda (a &optional (b 2)) (+ a (* b 3))) 4 5)
     (let ((a 4)
	   (b 5))
       (+ a (* b 3)))
     19)
    (
     ((lambda (a &optional (b 2)) (+ a (* b 3))) 4)
     (let ((a 4))
       (let* ((b 2))
	 (+ a (* b 3))))
     10)
    (
     ((lambda (&optional (a 2 b) (c 3 d) &rest x) (list a b c d x)))
     (let* ((a 2)
	    (b nil)
	    (c 3)
	    (d nil)
	    (x nil))
       (list a b c d x))
     (2 nil 3 nil nil))
    (
     ((lambda (&optional (a 2 b) (c 3 d) &rest x) (list a b c d x)) 6)
     (let ((a 6)
	   (b t))
       (let* ((c 3)
	      (d nil)
	      (x nil))
	 (list a b c d x)))
     (6 t 3 nil nil)
     )
    (
     ((lambda (&optional (a 2 b) (c 3 d) &rest x) (list a b c d x)) 6 3)
     (let ((a 6)
	   (b t)
	   (c 3)
	   (d t)
	   (x nil))
       (list a b c d x))
     (6 t 3 t nil)
     )
    (
     ((lambda (&optional (a 2 b) (c 3 d) &rest x) (list a b c d x)) 6 3 8)
     (let ((a 6)
	   (b t)
	   (c 3)
	   (d t)
	   (x (list 8)))
       (list a b c d x))
     (6 t 3 t (8))
     )
    (
     ((lambda (&optional (a 2 b) (c 3 d) &rest x) (list a b c d x))
      6 3 8 9 10 11)
     (let ((a 6)
	   (b t)
	   (c 3)
	   (d t)
	   (x (list 8 9 10 11)))
       (list a b c d x))
     (6 t 3 t (8 9 10 11))
     )
    ;; Examples of &key parameters
    (
     ((lambda (a b &key c d) (list a b c d)) 1 2)
     (let ((a 1)
	   (b 2))
       (let* ((c nil)
	      (d nil))
	 (list a b c d)))
     (1 2 nil nil)
     )
    (
     ((lambda (a b &key c d) (list a b c d)) 1 2 :c 6)
     (let ((a 1)
	   (b 2)
	   (c 6))
       (let* ((d nil))
	 (list a b c d)))
     (1 2 6 nil)
     )
    (
     ((lambda (a b &key c d) (list a b c d)) 1 2 :c *print-escape*)
     (let ((a 1)
	   (b 2)
	   (#15=#:|TEMP-c| *print-escape*))
       (let* ((c #15#)
	      (d nil))
	 (list a b c d)))
     (1 2 t nil)
     )
    (
     ((lambda (a b &key c d) (list a b c d)) 1 2 :d 8)
     (let ((a 1)
	   (b 2))
       (let* ((c nil)
	      (d 8))
	 (list a b c d)))
     (1 2 nil 8)
     )
    (
     ((lambda (a b &key c d) (list a b c d)) 1 2 :d *print-escape*)
     (let ((a 1)
	   (b 2)
	   (#1=#:|TEMP-d| *print-escape*))
       (let* ((c nil)
	      (d #1#))
	 (list a b c d)))
     (1 2 nil t)
     )
    (
     ((lambda (a b &key c d) (list a b c d)) 1 2 :c 6 :d 8)
     (let ((a 1)
	   (b 2)
	   (c 6)
	   (d 8))
       (list a b c d))
     (1 2 6 8)
     )
    (
     ((lambda (a b &key c d) (list a b c d))
      1 2 :c *print-level* :d *print-escape*)
     (let ((a 1)
	   (b 2)
	   (#2=#:|TEMP-c| *print-level*)
	   (#3=#:|TEMP-d| *print-escape*))
       (let* ((c #2#)
	      (d #3#))
	 (list a b c d)))
     (1 2 nil t)
     )
    (
     ((lambda (a b &key c d) (list a b c d)) 1 2 :d 8 :c 6)
     (let ((a 1)
	   (b 2)
	   (c 6)
	   (d 8))
       (list a b c d))
     (1 2 6 8)
     )
    (
     ((lambda (a b &key c d) (list a b c d))
      1 2 :d *print-level* :c *print-escape*)
     (let ((a 1)
	   (b 2)
	   (#4=#:|TEMP-d| *print-level*)
	   (#5=#:|TEMP-c| *print-escape*))
       (let* ((c #5#)
	      (d #4#))
	 (list a b c d)))
     (1 2 t nil)
     )
    (
     ((lambda (a b &key c d) (list a b c d)) :a 1 :d 8 :c 6)
     (let ((a :a)
	   (b 1)
	   (c 6)
	   (d 8))
       (list a b c d))
     (:a 1 6 8)
     )
    (
     ((lambda (a b &key c d) (list a b c d))
      :a 1 :d *print-level* :c *print-escape*)
     (let ((a :a)
	   (b 1)
	   (#6=#:|TEMP-d| *print-level*)
	   (#7=#:|TEMP-c| *print-escape*))
       (let* ((c #7#)
	      (d #6#))
	 (list a b c d)))
     (:a 1 t nil)
     )
    (
     ((lambda (a b &key c d) (list a b c d)) :a :b :d 8 :c 6)
     (let ((a :a)
	   (b :b)
	   (c 6)
	   (d 8))
       (list a b c d))
     (:a :b 6 8)
     )
    (
     ((lambda (a b &key c d) (list a b c d))
      :a :b :d *print-level* :c *print-escape*)
     (let ((a :a)
	   (b :b)
	   (#8=#:|TEMP-d| *print-level*)
	   (#9=#:|TEMP-c| *print-escape*))
       (let* ((c #9#)
	      (d #8#))
	 (list a b c d)))
     (:a :b t nil)
     )
    ;; Examples of mixtures
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      1)
     (let ((a 1))
       (let* ((b 3)
	      (x nil)
	      (c nil)
	      (d a))
	 (list a b c d x)))
     (1 3 nil 1 ())
     )
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      1 2)
     (let ((a 1)
	   (b 2)
	   (x nil))
       (let* ((c nil)
	      (d a))
	 (list a b c d x)))
     (1 2 nil 1 ())
     )
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      :c 7)
     (let ((a :c)
	   (b 7)
	   (x nil))
       (let* ((c nil)
	      (d a))
	 (list a b c d x)))
     (:c 7 nil :c ())
     )
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      1 6 :c 7)
     (let ((a 1)
	   (b 6)
	   (x (list :c 7))
	   (c 7))
       (let* ((d a))
	 (list a b c d x)))
     (1 6 7 1 (:c 7))
     )
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      1 6 :c *print-level*)
     (let ((a 1)
	   (b 6)
	   (#10=#:|TEMP-c| *print-level*))
       (let* ((x (list :c #10#))
	      (c #10#)
	      (d a))
	 (list a b c d x)))
     (1 6 nil 1 (:c nil))
     )
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      1 6 :d 8)
     (let ((a 1)
	   (b 6)
	   (x (list :d 8)))
       (let* ((c nil)
	      (d 8))
	 (list a b c d x)))
     (1 6 nil 8 (:d 8))
     )
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      1 6 :d *print-level*)
     (let ((a 1)
	   (b 6)
	   (#11=#:|TEMP-d| *print-level*))
       (let* ((x (list :d #11#))
	      (c nil)
	      (d #11#))
	 (list a b c d x)))
     (1 6 nil nil (:d nil))
     )
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      1 6 :d 8 :c 9 :d 10)
     (let ((a 1)
	   (b 6)
	   (x (list :d 8 :c 9 :d 10))
	   (c 9)
	   (d 8))
       (list a b c d x))
     (1 6 9 8 (:d 8 :c 9 :d 10))
     )
    (
     ((lambda (a &optional (b 3) &rest x &key c (d a))
	(list a b c d x))
      1 6 :d *print-level* :c *print-length* :d *print-escape*)
     (let ((a 1)
	   (b 6)
	   (#12=#:|TEMP-d| *print-level*)
	   (#13=#:|TEMP-c| *print-length*)
	   (#14=#:|TEMP-d| *print-escape*))
       (let* ((x (list :d #12# :c #13# :d #14#))
	      (c #13#)
	      (d #12#))
	 (list a b c d x)))
     (1 6 nil nil (:d nil :c nil :d t))
     )
    ;; Additional tests.
    (
     ((lambda (a &optional (b 3) &key c (d a))
	(list a b c d))
      1 6 :d 8 :c 9 :d 10)
     (let ((a 1)
	   (b 6)
	   (c 9)
	   (d 8))
       (list a b c d))
     (1 6 9 8)
     )
    (
     ((lambda (a &optional (b 3) &key c (d a))
	(list a b c d))
      1 6 :d *print-level* :c *print-length* :d *print-escape*)
     (let ((a 1)
	   (b 6)
	   (#16=#:|TEMP-d| *print-level*)
	   (#17=#:|TEMP-c| *print-length*)
	   (#18=#:|TEMP-d| *print-escape*))
       (declare (ignore #18#))
       (let* ((c #17#)
	      (d #16#))
	 (list a b c d)))
     (1 6 nil nil)
     )
    (
     ((lambda (a &optional (b 3) &key &allow-other-keys)
	(list a b))
      1 6 :d 8 :c 9 :d 10)
     (let ((a 1)
	   (b 6))
       (list a b))
     (1 6)
     )
    (
     ((lambda (a &optional (b 3) &key &allow-other-keys)
	(list a b))
      1 6 :d 8 :c 9 :d *print-level*)
     (let ((a 1)
	   (b 6)
	   (#20=#:ignore (progn *print-level* nil)))
       (declare (ignore #20#))
       (list a b))
     (1 6)
     )
    (
     ((lambda (a &optional (b 3) &key)
	(list a b))
      1 6 :d 8 :c 9 :d 10 :allow-other-keys t)
     (let ((a 1)
	   (b 6))
       (list a b))
     (1 6)
     )
    (
     ((lambda (a &optional (b 3) &key)
	(list a b))
      1 6 :d 8 :c 9 :d 10 :allow-other-keys t :allow-other-keys nil)
     (let ((a 1)
	   (b 6))
       (list a b))
     (1 6)
     )
    (
     ((lambda (a &optional (b 3) &key)
	(list a b))
      1 6 :d 8 :c 9 :d 10 :allow-other-keys t :allow-other-keys *print-level*)
     (let ((a 1)
	   (b 6)
	   (#23=#:ignore (progn *print-level* nil)))
       (declare (ignore #23#))
       (list a b))
     (1 6)
     )
    ))

(defun check-test-expansions ()
  (let ((index 0)
	(*print-level* nil)
	(*print-length* nil)
	(*print-escape* t))
    (mapc #'(lambda (entry)
	      (let ((form (second entry)))
		(unless (equal (third entry)
			       (ignore-errors (eval form)))
		  (print index)
		  (pprint form))
		(incf index)))
	  *test-forms*)
    nil))

(defun display-expansions ()
  (let ((index 0)
	(*print-level* nil)
	(*print-length* nil)
	(*print-escape* t))
    (mapc #'(lambda (entry)
	      (let ((lambda (first entry))
		    (form (second entry))
		    (value (third entry)))
		(print index)
		(incf index)
		(pprint lambda)
		(terpri)
		(let ((expansion
		        ;(walk:walk-form lambda)
		        (transform-lambda-to-let lambda
						 *default-global-environment*))
		      (*print-circle* t))
		  (pprint expansion)
		  (terpri)
		  (pprint form)
		  (unless (equal value (ignore-errors (eval expansion)))
		    (print 'values-differ))
		  (read-char))))
	  *test-forms*)
    nil))

|#

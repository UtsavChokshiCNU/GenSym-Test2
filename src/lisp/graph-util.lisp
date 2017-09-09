;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAPH-UTIL

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Joseph E. Devlin 



(declare-forward-references
  (print-constant function grammar0))





;;;; Standard Grammar Categories

;;; Standard Grammar Categories is an attempt to reduce code inertia
;;; and dependent definition regarding the grammars, compilers, and
;;; writers of G2 categories.

;;; While just about anything is allowable as the parsed representation
;;; of the text for a G2/slot attribute, standardizing on certain levels
;;; of representative power for parse results will allow a reduction in
;;; "junk" coding needed for introducing new grammar categories.  In this
;;; module two general kinds of grammar categories are identified and
;;; are given single macros that make all necessary definitions for their
;;; use.  One, which is relatively self-explanantory is the enumeration
;;; category, in which a slot-value is one of an enumations of symbols.
;;; The other is called the frame-like category, and has the parsed
;;; representation of (key-symbol . plist).  This key symbol is meant
;;; to stand for what the slot value is in general and the plist holds
;;; additional parameters for that key.  It is not intended that the
;;; the plists of frame-like slot-values be very long; it exists to serve
;;; as a means for context-sensitive parameterization as an alternative
;;; to defining a large number of distinct atomic-valued slots.

;;; An example, taken from the graphs module, is of the slot plot-point-marker
;;; category.  It can either be one of several pre-defined shapes, such as
;;; circle, triangle, etc., or it can be a G2 icon layer description.
;;; The key-symbol for this category is then either 'custom or 'standard.
;;; When the key is 'standard the plist has one property called shape
;;; which is filled by a symbol.  When the key is custom the plist has
;;; one propery called icon-description filled by a G2 icon-description
;;; s-expression.

;;; The example given is not a difficult slot value to write a grammar, compiler,
;;; and writer for, but there are many slots at this same level of
;;; complexity in G2 that have completely disparate grammars and parse-result
;;; representations.  So the author believes that by factoring out the commonality
;;; of such slots, he will be doing "good".


;;; `def-enumeration-grammar-category' defines a grammar category
;;; and all possible phrases that represent it.  The compiled
;;; value of such a category is always one of a short list of
;;; symbols.  A slot-value-writer is created, as well.

(def-global-property-name enumeration-grammar-category-members)


(defmacro def-enumeration-grammar-category (name &body specs)
  (loop with grammar-rules = '()
	with cases = '()
	with enumeration-members = '()
	with internal-tags = '()
	for spec in specs
	as internal-tag = (if (atom spec) spec (cadr spec))
	do
          (let* ((phrase (if (atom spec) spec (car spec)))
		 (grammar-rule-rhs
		   (cond ((atom phrase)
			  `',phrase)
			 ((and (consp phrase)
			       (null (cdr phrase)))
			  `',(car phrase))
			 (t
			  (mapcar #'(lambda (x) `',x) phrase))))
		 (string-to-tprinc
		   (if (atom spec)
		       (string-downcase (format nil "~a" spec))
		       (string-downcase (format nil "~{~a~^ ~}" (car spec)))))
		 (symbol internal-tag))
	    (push internal-tag internal-tags)
	    (push (if (atom phrase)
		      phrase
		      (apply 'build-ab-symbol phrase))
		  enumeration-members)
	    (push `(,name ,grammar-rule-rhs ,symbol) grammar-rules)
	    (push `(,symbol (twrite ,string-to-tprinc)) cases))
	finally
	  (setf enumeration-members (nreverse enumeration-members))
	  (setf internal-tags (nreverse internal-tags))
	  (return
	    `(progn
	       (setf (enumeration-grammar-category-members ',name)
		     ',enumeration-members)
	       (add-grammar-rules
		 ',grammar-rules)
	       (define-category-evaluator-interface (,name :access read-write)
		   (member ,@enumeration-members)
		 ((set-form (evaluation-value))
		  (let ((symbol (evaluation-symbol-symbol evaluation-value)))
		    (case symbol
		      ,@(loop for internal-tag in internal-tags
			      for enumeration-member in enumeration-members
			      collect
			  `(,enumeration-member ',internal-tag)))))
		 ((get-form (slot-value))
		  (case slot-value
		    ,@(loop for internal-tag in internal-tags
			    for enumeration-member in enumeration-members
			    collect
			`(,internal-tag ',enumeration-member)))))
	       (def-slot-value-writer ,name (value)
		 (case value
		   ,@cases))))))
	    

(defun-for-macro make-formatter-for-category (category-name link)
  (case category-name
    (interval
     `(print-constant (car (:link ,link)) 'seconds))
    (otherwise
     `(twrite (:link ,link)))))

(defun-for-macro substitute-for-link-in-args (link property-name arg-forms)
  (labels ((z (x)
	     (cond ((atom x) x)
		   ((and (consp x)
			 (consp (cdr x))
			 (null (cddr x))
			 (eq (car x) :link)
			 (eql (cadr x) link))
		    `(getf plist ',property-name))
		   (t
		    (cons (z (car x)) (z (cdr x)))))))
    (z arg-forms)))
  

(defun-for-macro expand-frame-like-category-production
    (category-name phrase-list transform-template
		   number-seen-for-key-so-far)
  (let* ((processed-phrase-list '())
	 (key-symbol (car transform-template))
	 (sub-key (code-char (+ #.(char-code #\A)
				-1
				number-seen-for-key-so-far)))
	 (processed-transform (list sub-key key-symbol))
	 (link-table '())
	 (formatting-forms '()))
    ;; make real phrase-list for g2 grammar rule and
    ;; mark position of all non-terminals
    ;; and build up a tformat control-string and arguments
    ;; in the process
    (loop for elt in phrase-list
	   as pos from 1 by 1
	  do
            (unless (= pos 1)
	      (push `(twrite " ") formatting-forms))
	    (cond  ((atom elt)
		    (push `',elt processed-phrase-list)
		    (push `(twrite ',(string-downcasew (symbol-name-text-string elt)))
			  formatting-forms))
		   (t
		    (push (car elt) processed-phrase-list)
		    (push (list (cadr elt) pos (car elt))
			  link-table)
		    (push (make-formatter-for-category (car elt) (cadr elt))
			  formatting-forms))))
    ;; build a transform with symbol links converted to
    ;; yucky, positional references
    (loop for (key link-or-quoted-value)
	      on (cdr transform-template)
	      by 'cddr
	  do
      (push key processed-transform)
      (cond ((and (consp link-or-quoted-value)
		  (eq (car link-or-quoted-value) 'quote))
	     (push (cadr link-or-quoted-value)
		   processed-transform))
	    (t
	     (setf formatting-forms
		   (substitute-for-link-in-args link-or-quoted-value
						key
						formatting-forms))
	     (push (cadr (assoc link-or-quoted-value link-table))
		   processed-transform))))
    (values `(,category-name ,(let ((phrase (reverse processed-phrase-list)))
				(cond ((= 1 (length phrase)) (car phrase))
				      (t phrase)))
			     ,(reverse processed-transform))
	    `((and (eq key-symbol ',key-symbol)
		   (eq sub-key ,(-f (char-code sub-key) (char-code #\A))))
	      ,@(reverse formatting-forms))
	    (reverse processed-transform))))

(defun-for-macro generate-checking-code-for-frame-like-category
    (check-forms)
  (loop for check-form in check-forms
	collect
	(case (car check-form)
	  ((interval-check range-check)
	   (let ((value-getting-form
		   (case (car check-form)
		     (range-check
		      `(getf (cddr parse-result) ',(cadadr check-form)))
		     (interval-check
		      `(car (getf (cddr parse-result) ',(cadadr check-form)))))))
	     `(let ((prop-value? (and (eq (car parse-result)
					  ',(caadr check-form))
				      ,value-getting-form)))
		(cond
		  (prop-value?
		   (cond ((check-frame-like-value-range prop-value?
							,(third check-form)
							,(fourth check-form))
			  t)
			 (t
			  (setq reason-for-bad-phrase
				,(fifth check-form))
			  nil)))
		  (t
		   t)))))
	   (old-funcalled-check
	    `(let ((prop-value? (and (eq (car parse-result) ',(caadr check-form))
				     (getf (cddr parse-result) ',(cadadr check-form)))))
	       (cond
		 (prop-value?
		  (cond ((funcall ',(caddr check-form) prop-value?)
			 t)
			(t
			 (setq reason-for-bad-phrase ,(fourth check-form))
			 nil)))
		 (t
		  t))))
	   (funcalled-check
	    (loop with bindings = '()
		  with property-spec = (cadr check-form)
		  with key = (car property-spec)
		  for property in (cdr property-spec)
		  do
	      (push `(,(gensym) (and (eq (car parse-result) ',key)
				     (getf (cddr parse-result) ',property)))
		    bindings)
		  finally
		    (setq bindings (nreverse bindings))
		    (return
		      `(let ,bindings
			 (cond ((and ,@(mapcar 'car bindings))
				(cond ((funcall ',(third check-form)
						,@(mapcar 'car bindings))
				       t)
				      (t
				       (setq reason-for-bad-phrase ,(fourth check-form))
				       nil)))
			       (t
				t))))))
	   )))
			

(defmacro normalize-frame-like-numerical-value (x)
  (avoiding-variable-capture (x)
    `(cond
       ((fixnump ,x) (coerce-fixnum-to-gensym-float ,x))
       ((managed-float-p ,x) (managed-float-value ,x))
       (t
	 ,x))))

(defun check-frame-like-value-range (value low? high?)
  (with-temporary-gensym-float-creation check-frame-like-value-range
    (let ((high? (normalize-frame-like-numerical-value high?))
	  (low? (normalize-frame-like-numerical-value low?))
	  (value (normalize-frame-like-numerical-value value)))
      (and (if low? (<=e low? value) t)
	   (if high? (>=e high? value) t)))))

;;; `def-frame-like-grammar-category' defines a frame-like grammar
;;; category, described in the long comment above.

(def-global-property-name frame-like-category-cases)

(defmacro def-frame-like-grammar-category (name productions &body check-forms)
  (loop with grammar-rules = '()
	with transform-cases = '()
	with slot-value-writer-cases = '()
	with number-seen-for-each-key = '()
	for (rhs transform-template) on productions by 'cddr
	Do
          (let ((number-for-category
		  (incf (getf number-seen-for-each-key (car transform-template) 0))))
	    (when (> number-for-category 26)
	      (error "Too many cases for key ~s in category ~s"
		     (car transform-template) name))
	    (multiple-value-bind
		(grammar-rule slot-value-writer-case transform-case)
		(expand-frame-like-category-production
		  name
		  (copy-list rhs)
		  (copy-list transform-template) number-for-category)
	      (push grammar-rule grammar-rules)
	      (push transform-case transform-cases)
	      (push slot-value-writer-case slot-value-writer-cases)))
	finally
	  (return
	    `(progn
	       (add-grammar-rules
		 ',grammar-rules)
	       (setf (frame-like-category-cases ',name)
		     (optimize-constant
		       ',(loop for (key sub-key . rest) in transform-cases
			       collect
			       (list* key
				      (- (char-code sub-key) (char-code #\A))
				      rest))))
	       (def-slot-value-compiler ,name (parse-result)
		 (unless (fixnump (cadr parse-result))
		   (setf (cadr parse-result)
			 (-f (char-code (cadr parse-result))
			     (char-code #\A))))
		 (let ((reason-for-bad-phrase nil))
		   reason-for-bad-phrase
		   (cond
		     ((and ,@(generate-checking-code-for-frame-like-category
			       check-forms))
		      parse-result)
		     (t
		      (values bad-phrase
			      (tformat-text-string "~a"
						   reason-for-bad-phrase))))))
	       (def-slot-value-writer ,name (slot-value)
		 (let ((key-symbol (car slot-value))
		       (sub-key (cadr slot-value))
		       (plist (cddr slot-value)))
		   plist
		   (cond
		     ,@slot-value-writer-cases)))
	       ',name))))

(defparameter recent-defaults-made '())

(defun make-frame-like-category-parse-result (category-name key-symbol plist)
  (let* ((parse-result (make-frame-like-category-default
			 category-name key-symbol plist 'phrase))
	 (case-number (cadr parse-result)))
    ;; The following mysterious bit undoes
    ;; what would be the effect of the slot-value compiler
    (setf (cadr parse-result) (code-char (+f case-number #.(char-code #\A))))
    parse-result))

(defun make-frame-like-category-default (category-name key-symbol plist
						       &optional (pool 'slot-value))
  (macrolet ((copy-for-pool (x)
	       `(cond ((eq pool 'slot-value)
		       (copy-for-slot-value ,x))
		      (t
		       (copy-for-phrase ,x))))
	     (pool-push (thing place)
	       `(cond ((eq pool 'slot-value)
		       (slot-value-push ,thing ,place))
		      (t
		       (phrase-push ,thing ,place)))))
    (loop with cases = (frame-like-category-cases category-name)
	  with best-case? = nil
	  with best-case-key-matches =  0 
	  with best-case-value-matches = 0
	  with maximum-matches = (floorf (length plist) 2)
	  for case in cases
	  as case-plist = (cddr case)
	  do
      (when (eq (car case) key-symbol)
	(cond ((= 0 maximum-matches)
	       (return (copy-for-pool case)))
	      (t
	       ;; count matches
	       (loop with current-case-key-matches = 0
		     with current-case-value-matches = 0
		     for (key value) on plist by 'cddr
		     as matching-key? = (memq key case-plist)
		     as value-in-case? = (and matching-key?
					      (getf case-plist key))
		     do
		 (when matching-key?
		   (incff current-case-key-matches)
		   (when (equal value-in-case? value)
		     (incf current-case-value-matches)))
		     finally
		       (when (or (not best-case?)
				 (>f current-case-key-matches
				     best-case-key-matches)
				 (and (=f current-case-key-matches
					  best-case-key-matches)
				      (>f current-case-value-matches
					  best-case-value-matches)))
			 (setf best-case? case)
			 (setf best-case-key-matches current-case-key-matches)
			 (setf best-case-value-matches current-case-value-matches))))))
	  finally
	    ;; leaks ! in getf !
	    (return 
	      (and best-case?
		   (loop with result = (copy-for-pool best-case?)
			 for (key value) on plist by 'cddr
			 do
		     (cond ((memq key (cddr result))
			    (let ((tail (cdr (memq key (cddr result)))))
			      (setf (car tail)
				    (copy-for-pool value))))
			   (t
			    (pool-push (copy-for-pool value)
				       (cddr result))
			    (pool-push key (cddr result))))
			 finally
			   (return result)))))))
	    

			   
(defmacro frame-like-value-key (slot-value)
  `(car ,slot-value))

(defmacro frame-like-value-property (slot-value property)
  `(getf (cddr ,slot-value) ,property))




;;;; EZ-FLOAT

;;;; Module EZ-FLOAT

;;; The following macros exist to present an interface for creating and using
;;; functions that have gensym-floats among their return values.  This is not to say
;;; that this cannot be done through the primitives already in G2, but rather to present
;;; an interface that does not compromise on any of the following points:
;;;
;;; 1) Do not introduce gobs of global variables (and therefore punt on re-entrancy
;;;    and modularity).
;;; 2a) Use gensym-floats as the common currency for intermediate or derived values.
;;;     Results can be stored managed-floats or arrays thereof.
;;; 2b) Do not litter the application code with allocate, reclaim, extract-value,
;;;    and the like, to the point that the code is unreadable.
;;; 3) Cons conservatively; when you must cons, have the reclamation be triggered
;;;    as automatically and invisibly as is possible.
;;;
;;; There is a macro for defining functions that return floats, 'def-ez-float-function'.
;;; It differs from a typical Common Lisp function in having a return value prototype
;;; in between the the lambda-list and the body.  The return values prototype defines
;;; a set of local variables with types.  Currently the only recognized types are
;;; 'float and 't.  The returned values of the function are ALWAYS the the local
;;; variables of the prototype, returned in order.  The special form (return-from )
;;; should not be used in float-functions, but instead the macro (ez-float-return).
;;; It takes no arguments because the return-value-prototype already determines the
;;; results of the function.  A float function's body is wrapped in a 
;;; temporary-gensym-float-creation context automatically.
;;;
;;; Float functions are used in two ways, both of which need to be used in a
;;; temporary-gensym-float-creation-context or in the body of another float-function.
;;;
;;; The first way is to bind the results from a float-function.  The macro,
;;; ez-float-let*, is type-specific cousin to multiple-value-bind that allows any
;;; number of lists of variables to be bound to the values of form. The syntax of 
;;; ez-float-let* is:
;;;
;;;   (ez-float-let* (<binding-spec>*)
;;;     <body>)
;;;
;;; where <binding> is
;;;
;;;   ( { <var-spec> | <symbol> } form)
;;;
;;; and <var-spec> is
;;;
;;;   ( (<symbol> t|float) | <symbol>)
;;;
;;; The default type in these binding specs is float, not t.  The values bound are
;;; gensym-floats, suitable for use by the "e" family of arithmetic operators.
;;;
;;; The other manner of using float functions is through a direct call.  The only
;;; restriction here is that just one value is returned.  Again the returned value,
;;; if a float is a gensym-float.

(defvar-for-macro current-float-function-internal-block-name)
(defvar-for-macro current-float-function-variable-map)

(def-system-variable calling-float-function-cleverly-p GRAPH-UTIL 'nil)
(def-system-variable outstanding-float-function-floats GRAPH-UTIL 'nil)

(defun init-ez-float ()
  (allocate-managed-float 3.1415926))

(defmacro def-ez-float-function (name arg-list return-var-specs &body body)
  ;; make return spec floats local refs
  ;; make return spec non-floats local refs
  (loop with variables = '()
	with initforms = '()
	with variable-map = '()
	with sys-var-defs = '()
	with return-vars = '()
	with allocated-vars = '()
	with already-returned-variable = (gensym)
        for (var type init) in return-var-specs
	do
    (cond ((eq type 'float)
	   (let ((system-var (intern (format nil "~a-SYSTEM-VARIABLE-FOR-~a"
					  var name))))
	     (push (list var system-var) variable-map)
	     (push ;; `(defvar ,system-var (allocate-managed-float 3.1415926))
	       `(def-system-variable ,system-var GRAPH-UTIL
	         (:funcall init-ez-float))
		   sys-var-defs)
	     (push var variables)
	     (push `(setf ,var ,(or init 3.1415926)) initforms)
	     (push system-var return-vars)
	     (push var allocated-vars)))
	  (t
	   (push var variables)
	   (push `(setf ,var ,init) initforms)
           (push var return-vars)
	   (push var allocated-vars)))
	finally
	  (let ((block-name (gensym)))
	    (setf current-float-function-internal-block-name block-name)
	    (setf current-float-function-variable-map variable-map)
	    (return `(progn
		       ,@sys-var-defs
		       (defun ,name ,arg-list
			 (let (,@variables
				 (,already-returned-variable nil))
			   (block ,block-name			   
			     (with-temporary-gensym-float-creation ,name
			       ,@initforms
			       ,@body
			       (unless ,already-returned-variable
				 ,(make-float-function-result-frobs))))
			   (cond (#+development
				  (and (boundp 'calling-float-function-cleverly-p)
				       calling-float-function-cleverly-p)
				  #-development
				  calling-float-function-cleverly-p
				  ; (print "being clever")
				  (values ,@(nreverse allocated-vars)))
				 (t
				  ; (print "being stupid")
				  (values ,@(nreverse return-vars)))))))))))

(defun-for-macro make-float-function-result-frobs ()
  (loop with mutate-forms = nil
	with allocate-forms = nil
	for (local-var system-var) in current-float-function-variable-map
	do
    (push `(mutate-managed-float-value ,system-var ,local-var)
	  mutate-forms)
    (push `(setf ,local-var
		 (allocate-managed-float ,local-var))
	  allocate-forms)
    (push `(slot-value-push ,local-var outstanding-float-function-floats) ; ugh!
	  allocate-forms)
	finally
	  (return
	    `(cond (#+development
		    (and (boundp 'calling-float-function-cleverly-p)
			 calling-float-function-cleverly-p)
		    #-development
		    calling-float-function-cleverly-p
		    ,@(nreverse allocate-forms))
		   (t
		    ,@mutate-forms)))))

(defmacro ez-float-return ()
  `(progn
     ,(make-float-function-result-frobs)
     (return-from ,current-float-function-internal-block-name)))

(defun cleanup-float-function-floats ()
  (loop for managed-float in outstanding-float-function-floats
	do
    (reclaim-managed-float managed-float)
	finally
	  (reclaim-slot-value-list outstanding-float-function-floats)
	  (setf outstanding-float-function-floats nil)))



(defun-for-macro expand-ffl (first-binding-spec binding-spec-tail body)
  (let ((inner-body (cond
		      ((null binding-spec-tail)
		       `((cleanup-float-function-floats)
			 ,@body))
		      (t
		       (list (expand-ffl (car binding-spec-tail)
					 (cdr binding-spec-tail)
					 body))))))
  (cond
    ((atom first-binding-spec)
     (error "Bad Float Function Let ~s near ~s" first-binding-spec body))
    ((atom (car first-binding-spec))
     (let ((var-name (car first-binding-spec)))
       (cond ((symbolp var-name)
	      `(let ((,var-name (managed-float-value ,(cadr first-binding-spec))))
		 ,@inner-body))
	     (t
	      (error "Bad Float Function Let ~s near ~s" first-binding-spec body)))))
    (t
     (let* ((var-spec (car first-binding-spec)) ;; we know its a cons
	    (first-var-spec (car var-spec))
	    (var-spec-tail (cdr var-spec)))
       ; (format t "Var spec = ~s ~%~%" var-spec)
       (cond
	 ((null var-spec-tail)
	  (cond ((consp first-var-spec)
		 (cond ((eq (cadr first-var-spec) 'float)
			`(let ((,(car first-var-spec) (managed-float-value
							,(cadr first-binding-spec))))
			   ,@inner-body))
		       (t
			`(let ((,(car first-var-spec) ,(cadr first-binding-spec)))
			   ,@inner-body))))
		((symbolp first-var-spec)
		 `(let ((,first-var-spec (managed-float-value
					   ,(cadr first-binding-spec))))
		    ,@inner-body))
		(t
		 (error "Bad Float Function Let ~s near ~s" first-binding-spec body))))
	 (t
	  (loop with variables = '()
		with frob-forms = '()
		for var-and-type in var-spec
		 as var-name = (if (consp var-and-type) (car var-and-type) var-and-type)
		 as var-type = (if (consp var-and-type) (cadr var-and-type) 'float)
		do
	    (push var-name variables)
	    (when (eq var-type 'float)
	      (push `(setf ,var-name (managed-float-value ,var-name))
		    frob-forms))
		finally
		  (return
		    `(multiple-value-bind
			 ,(reverse variables)
			 ,(cadr first-binding-spec)
		       ,@frob-forms
		       ,@inner-body))))))))))

;; must be called in temporary-float context
(defmacro ez-float-let* (binding-specs &body body)
  `(let ((calling-float-function-cleverly-p t))
     ,(expand-ffl (car binding-specs) (cdr binding-specs) body)))

;; Like funcall, but single-valued
(defmacro ez-float-call (function &body args)
  `(let* ((calling-float-function-cleverly-p t)
	  (res (,function ,@args)))
     (cleanup-float-function-floats)
     res))





;;;; Time and value arithmetic macros

;;; This implementation of graphs attempts to hide what it can of the details of
;;; doing arithmetic and storing numbers.  Histories contain values and times and there
;;; are suites of operations for each of these "types".

(defun make-2d-display-time ()
  (allocate-managed-float 0.0))

(defmacro time-slot? (frame slot-name)
  `(let ((slot-value (,slot-name ,frame)))
     (if slot-value (managed-float-value slot-value) nil)))

(defmacro time-slot (frame slot-name)
  `(let ((slot-value (,slot-name ,frame)))
     (if slot-value (managed-float-value slot-value) 0.0)))

(defmacro fast-time-slot (frame slot-name)
  `(managed-float-value (,slot-name ,frame)))

(defmacro mutate-time-slot (frame slot-name gensym-float)
  (avoiding-variable-capture (frame)
    `(let ((slot-value (,slot-name ,frame)))
       (cond (slot-value
	      (mutate-managed-float-value slot-value ,gensym-float))
	     (t
	      (setf (,slot-name ,frame) (allocate-managed-float ,gensym-float)))))))

(defmacro fast-mutate-time-slot (frame slot-name gensym-float)
  `(mutate-managed-float-value (,slot-name ,frame) ,gensym-float))

(defmacro reclaim-time-slot (frame slot-name)
  (avoiding-variable-capture (frame)
    `(let ((managed-float? (,slot-name ,frame)))
       (when managed-float?
	 (reclaim-managed-float managed-float?)
	 (setf (,slot-name ,frame) nil)))))

(defmacro most-negative-time ()
  most-negative-gensym-float)

(defmacro most-positive-time ()
  most-positive-gensym-float)

(defmacro most-negative-value ()
  (/e most-negative-gensym-float 10000.0))

(defmacro most-positive-value ()
  (/e most-positive-gensym-float 10000.0))

(defmacro uninitialized-negative-value-flag ()
  (/e most-negative-gensym-float 1000.0))

(defmacro uninitialized-positive-value-flag ()
  (/e most-positive-gensym-float 1000.0))

(defun make-2d-display-value ()
  (allocate-managed-float 0.0))

(defmacro define-synonym-macros (&body pairs)
  (loop with macros = `()
	for (my-name real-name all-args-float-p) in pairs
	do
    (cond
      (#+development all-args-float-p
       #-development nil
       (push
	 `(defmacro ,my-name (&body args)
	    (loop with arg-forms = '()
		  for arg in args
		  do
	      (push (list (gensym) arg) arg-forms)
		  finally
		    (setq arg-forms (nreverse arg-forms ))
		    (return
		      `(let ,arg-forms
			 (,',real-name
			       ,@(loop for arg-forms in arg-forms
				       collect
				       `(if (gensym-float-p ,(car arg-forms))
					    ,(car arg-forms)
					  (progn
					    (warn "non-float ~s seen near ~s"
						  ,(car arg-forms) ',',my-name)
					    ,(car arg-forms)))))))))
	 macros))
      (t
       (push `(defmacro ,my-name (&body args)
		`(,',real-name ,@args))
	     macros)))
	finally
	  (return
	    `(progn ,@macros))))

(defmacro frounde-as-fixnum (x)
  `(floore-first (frounde ,x)))

(define-synonym-macros
    (-time -e t)
    (+time +e t)
  (*time *e t)
  (/time /e t)
  (abs-time abse t)
  (floor-time ffloore-first t)     ; returns fixnum
  (ceiling-time fceilinge-first t) ; returns fixnum
  (round-time frounde t)
  (fixnum-to-time coerce-fixnum-to-gensym-float)
  (time-to-fixnum frounde-as-fixnum t)
  (<time <e t)
  (>time >e t)
  (<=time <=e t)
  (=time =e t)
  (/=time /=e t)
  (>=time >=e t)
  (maxtime maxe t)
  (mintime mine t)
  
  ;; value stuff
  (value-slot time-slot)
  (fast-value-slot fast-time-slot)
  (mutate-value-slot mutate-time-slot)
  (fast-mutate-value-slot fast-mutate-time-slot)
  (reclaim-value-slot reclaim-time-slot)
  (-value -e t)
  (+value +e t)
  (*value *e t)
  (/value /e t)
  (abs-value abse t)
  (floor-value ffloore-first t)
  (ceiling-value fceilinge-first t)
  (round-value frounde t)
  (fixnum-to-value coerce-fixnum-to-gensym-float)
;  (value-to-fixnum frounde-as-fixnum t)
  (<value <e t)
  (>value >e t)
  (<=value <=e t)
  (=value =e t)
  (/=value /=e t)
  (>=value >=e t)
  (expt-value expte t)
  (log-value loge t)
  (maxvalue maxe t)
  (minvalue mine t)
  )

;;; not used in this file. Do not need eval-when for allegro portability
;;; NOTE: This number is converted to float and back, so reducing by
;;; one from the real limit to ensure that we never convert above
;;; most-positive-fixnum.

(defun fixnum-to-time-function (x)
  (fixnum-to-time x))

(defparameter max-timespan
  (fixnum-to-time-function (- most-positive-fixnum 1)))

(defun-simple exceptional-float-flavor? (thing)
  (and (gensym-float-p thing)
       (if (eq g2-machine-type 'vms)
	   nil ;stub for now (jh, 5/26/92)
	   (multiple-value-bind (byte0 byte1 byte2 byte3)
	       (partition-float thing)
	     ;; following form tests for all 1s in the 11-bit IEEE exponent field
	     (cond
	       ((=f (logandf byte0 mask-for-ieee-exponent) mask-for-ieee-exponent)
		(cond
		  ((and (=f byte0 mask-for-ieee-exponent) 
					; remaining fractional bits
			(=f byte1 0)     ;0000000000000000
			(=f byte2 0)     ;0000000000000000
			(=f byte3 0))    ;0000000000000000
		   'positive-infinity)
		  ((and (=f byte0 65520) ;1    11111111111 0000
					; remaining fractional bits
			(=f byte1 0)     ;0000000000000000
			(=f byte2 0)     ;0000000000000000
			(=f byte3 0))     ;0000000000000000
		   'negative-infinity)
		  ((or (pluspf byte1)                 
		       (pluspf byte2)
		       (pluspf byte3)
		       ;; IEEE fraction includes 4 bits in byte0
		       (pluspf (logandf byte0 15)))
		   'nan)
		  (t
		   nil)))
	       (t
		nil))))))

(defmacro value-to-fixnum (x)
  (avoiding-variable-capture (x)
    `(cond
       ((>e ,x most-positive-fixnum-as-float)
	most-positive-fixnum)
       ((<e ,x most-negative-fixnum-as-float)
	most-negative-fixnum)
       (t
	(floore-first (frounde ,x))))))


;;;; GENERIC HISTORYS

;;; Generic Histories are an indirection layer in between the new graphs
;;; and local histories, old/variable histories, and future data-served histories.
;;; This layer also provides extrema caching for fast graph access to plot data bounds
;;; on arbitrary intervals.

(def-structure extremum-cache
  (extremum-polarity           nil)   ; maximum or minimum
  (extremum-history            nil)    ; backpointer
  (extremum-zone-vector        nil
			       :reclaimer reclaim-if-managed-array)
  (extremum-zone-count         nil)
  (extremum-zone-index         nil
			       :reclaimer reclaim-if-managed-array)
  (extremum-zone-index-size    nil)
  (extremum-zones-in-use       nil)
  (extremum-whole-interval-cache nil)
  (extremum-zone-width         nil)
  (extremum-initial-data-lost  nil)
  (extremum-least-recent-index nil)
  (extremum-most-recent-index  nil)
  (extremum-cache-valid-p      nil)
  (extremum-last-known-history-size? nil))

(def-class (generic-history dependent-frame define-predicate)
  (generic-history-maximum-cache nil vector-slot system)
  (generic-history-minimum-cache nil vector-slot system)
  (generic-history-type nil vector-slot system save)
  (generic-history-data nil vector-slot system)
  (generic-history-designation? nil vector-slot system save) 
  (generic-history-data-serial-number nil vector-slot system) 
  (generic-history-specification nil vector-slot system save))

(def-slot-value-reclaimer generic-history-data-serial-number (serial-number generic-history)
  (reclaim-frame-serial-number serial-number)
  (setf (generic-history-data-serial-number generic-history) nil))

(defvar trace-validate-p nil)

(def-class-method copy-frame (generic-history)
  (let ((old generic-history)
	(current-block-of-dependent-frame
	  (if (and (boundp 'current-block-of-dependent-frame)
		   current-block-of-dependent-frame)
	      current-block-of-dependent-frame
	      superior-frame-being-cloned?))
	(new (clone-frame generic-history)))
    ;; minimum-cache, maximum-cache -- structures are not copied now
    (setf (generic-history-minimum-cache new)
	  (copy-extremum-cache (generic-history-minimum-cache old) new))
    (setf (generic-history-maximum-cache new)
	  (copy-extremum-cache (generic-history-maximum-cache old) new))
    ;; data
    (setf (generic-history-data new)
	  (copy-generic-history-data (generic-history-data old)
				     (generic-history-type old)))
    (setf (generic-history-specification new)
	  (copy-for-slot-value (generic-history-specification old)))
    new))

(def-class-method cleanup (generic-history)
  (funcall-superior-method generic-history)
  (reclaim-generic-history generic-history nil))

(defun copy-generic-history-data (data type)
  (case type
    (constant
     (copy-managed-float data))
    (cascaded
     (copy-cascaded-ring-buffer data))
    (variable
     nil)))

(defun validate-generic-history (history)
  (case (generic-history-type history)
    ((cascaded constant)
     nil) ; no gross changes to state of histor
    (variable
     (let ((res (validate-variable-history history)))
       (when trace-validate-p
	 (format t "gross changes to ~s~%" history))
       res))))


(defun generic-history-valid-p (history)
  (case (generic-history-type history)
    ((cascaded constant)
     t)
    (variable
     (generic-history-data history))))

(defun reset-generic-history (history)
  (case (generic-history-type history)
    (constant
     (reset-constant-history history))
    (cascaded
     (reset-cascaded-history history))
    (variable
     (reset-variable-history history))))

(defun reclaim-generic-history (history &optional delete-p)
  (case (generic-history-type history)
    (constant
     (reclaim-constant-history history))
    (cascaded
     (reclaim-cascaded-history history delete-p))
    (variable
     (reclaim-variable-history history delete-p))))

(defun new-constant-history (fix-or-float)
  (let ((history (make-frame 'generic-history)))
    (setf (generic-history-data history)
	  (with-temporary-gensym-float-creation new-constant-history
	    (cond ((fixnump fix-or-float)
		   (allocate-managed-float
		     (coerce-fixnum-to-gensym-float fix-or-float)))
		  ((and (consp fix-or-float)
			(eq (car fix-or-float) '-))
		   (allocate-managed-float
		     (coerce-fixnum-to-gensym-float (* -1 (cadr fix-or-float)))))
		  (t
		   (copy-managed-float fix-or-float)))))
    (setf (generic-history-type history) 'constant)
    (initialize-generic-history history 100) ; random hack !
    history))

(defun compute-update-interval-spec (update-interval-in-seconds)
  (let ((update-interval-float
	  (normalize-to-gensym-float (or update-interval-in-seconds
					 1))))
    (setf update-interval-float
	  (mintime 1.0 update-interval-float))
    (time-to-fixnum (*time update-interval-float 1000.0))))

(defun new-cascaded-history (expiration-interval?
			      &optional granularity-interval-in-seconds)
  (let ((history (make-frame 'generic-history))
	(granularity (compute-update-interval-spec granularity-interval-in-seconds)))
    (setf (generic-history-data history)
	  (make-or-reformat-cascaded-ring-buffer
	    nil nil expiration-interval? granularity))
    (setf (generic-history-type history) 'cascaded)
    (with-temporary-gensym-float-creation new-cascaded-history
	(setf (generic-history-specification history)
	      (slot-value-list
		nil nil
		expiration-interval?
		granularity
		)))
    (initialize-generic-history history 500) ; ugh, random hack !
    history))

(defun update-cascaded-history-expiration (history expiration granularity-interval?)
  (let ((cascaded-ring-buffer? (generic-history-data history))
	(granularity (compute-update-interval-spec granularity-interval?)))
    (setf (caddr (generic-history-specification history)) expiration)
    (setf (cadddr (generic-history-specification history))
	  granularity)
    (when cascaded-ring-buffer?
      (make-or-reformat-cascaded-ring-buffer
	cascaded-ring-buffer? nil expiration granularity))))

(defun new-variable-history (frame cell-index use-simulator-p)
  (let ((history (make-frame 'generic-history)))
    (setf (generic-history-data history) nil)
    (setf (generic-history-designation? history)
	  (slot-value-list frame cell-index use-simulator-p))
    (setf (generic-history-type history) 'variable)
    (initialize-generic-history history 500) ; ugh, random hack !
    history))

(defmacro variable-history-uses-simulator-p (history)
  (avoiding-variable-capture (history)
    `(let ((designation? (generic-history-designation? ,history)))
       (and designation?
	    (caddr designation?)))))

(defun update-history-for-cell-array-change (history frame cell-index use-simulator-p)
  (when (eq (generic-history-type history) 'variable)
    (cond ((generic-history-designation? history)
	   (let ((designation (generic-history-designation? history)))
	     (setf (car designation) frame)
	     (setf (cadr designation) cell-index)
	     (unless (eq (caddr designation) use-simulator-p)
	       ;; the following will trigger good things in
	       ;; later code
	       (setf (generic-history-data history) nil))
	     (setf (caddr designation) use-simulator-p)))
	  (t
	   (setf (generic-history-designation? history)
		 (slot-value-list frame cell-index use-simulator-p))))))

(defun add-to-cascaded-history (history value)
  (with-temporary-gensym-float-creation add-to-cascaded-history
    (store-history-value
      (generic-history-data history)
      (generic-history-specification history)
      (cond ((managed-float-p value)
	     (managed-float-value value))
	    (t
	     value))
      (managed-float-value (clock-get current-g2-time))
      nil ; should probably get use-simulator p from designation
      )))


;; 1. if the cached value is good (fsn) and matches the
;;    generic-history-data then history is still good.
;;    so leave things as is
;; 2. if new cached value good but different
;;    invalidate the caches
;; 3  if cached value is nil or re-cycled
;;    set g-h-d to nil
;; function returns whether any gross-changes have occurred
;; so caller can or-up a decision to redraw everything.

;; functions need valid-plot-histories, update-active-tc.
;; need to slow down updates of generic history in
;; clone as trend chart.  I think it's cool that
;; the computation-style applies completely
;; to the evaluation of the designation or the
;; numerical value!!

(defun update-generic-history-for-change-to-cascaded-ring-buffer (history)
  (when (eq (generic-history-type history) 'variable)
    ;; this will invalidate the trend chart
    (when trace-validate-p
      (format t "invalidating gh=~s for ~s from ~S~%"
	      history
	      (generic-history-data history)
	      (and (generic-history-data history)
		   #+development
		   (backtrace)
		   #-development
		   nil)))
    (invalidate-extrema-caches history)
    ;; GENSYMCID-1065: Trend-chart causes abort and/or unexpected behavior
    (remove-generic-history-as-client-to-history-of-variable history)
    (setf (generic-history-data history) nil)))

(defun add-generic-history-as-client-to-history-of-variable
    (history)
  (let ((cascaded-ring-buffer?
	  (get-cascaded-ring-buffer-for-history history)))
    (when cascaded-ring-buffer?
      (add-cascaded-ring-buffer-client
	history cascaded-ring-buffer?))))

(defun remove-generic-history-as-client-to-history-of-variable
    (history)
  (let ((cascaded-ring-buffer?
	  (get-cascaded-ring-buffer-for-history history)))
    (cond
      (cascaded-ring-buffer?
       (remove-cascaded-ring-buffer-client
	 history cascaded-ring-buffer?))
      (trace-validate-p
       (format t "failed remove gh=~s client from ~s~%"
	       history
	       #+development
	       (backtrace)
	       #-development
	       nil
	       )))))

(defun validate-variable-history (history)
  (remove-generic-history-as-client-to-history-of-variable history)
  (let* ((frame (car (generic-history-designation? history)))
	 (cell-array? (cell-array frame))
	 (cell-array-index? (cadr (generic-history-designation?
				   history)))
	 (variable-in-history? (generic-history-data history))
	 (cached-variable?
	  (and cell-array-index?
	       cell-array?
	       (get-expression-cell-cache cell-array?
					  cell-array-index?)))
	 (var-change-p nil))
    (cond
      ((or (null cached-variable?)
      ;Start of SoftServe changes
             (typep cached-variable? 'fixnum)
      ;end of SoftServe changes
	   (not (frame-in-use-p cached-variable?))
	   (and variable-in-history?
		(eq variable-in-history? cached-variable?)
		(frame-has-been-reprocessed-p
		  cached-variable?
		  (generic-history-data-serial-number history))))
       (when trace-validate-p
	 (format t "validate case 1 cachvar=~s var-in-h=~s~%"
		 cached-variable? variable-in-history?))
       ;; variable not currently available case
       (cond (variable-in-history?
	      (setf (generic-history-data history) nil)
	      (invalidate-extrema-caches history)
	      (setq var-change-p t))
	     (t
	      nil)))
      ;; Normal case -- history exists and is unchanged
      ((eq variable-in-history? cached-variable?)
       (when trace-validate-p
	 (format t "validate case 2~%"))
       nil)
      ;; cached-variable is valid but is not equal to previous-value
      (t
       (when trace-validate-p
	 (format t "validate case 3~%")
	 (format t "setting new variable for gh old ~S new ~s~%"
		 variable-in-history? cached-variable?))
       (setf (generic-history-data history) cached-variable?)
       (frame-serial-number-setf (generic-history-data-serial-number history)
				 (frame-serial-number cached-variable?))
       (invalidate-extrema-caches history)
       (setq var-change-p t)))
    (add-generic-history-as-client-to-history-of-variable history)
    var-change-p))

(defun reset-constant-history (history)
  (reset-generic-history-internal history))

(defun reset-cascaded-history (history)
  (reset-generic-history-internal history)
  (clear-history-buffer (generic-history-data history)))

(defun reset-variable-history (history)
  (validate-variable-history history) ; to make link to variable
                                      ; as good aas it can be
  (when trace-validate-p
    (format t "in reset~%"))
  (remove-generic-history-as-client-to-history-of-variable history)
  (reset-generic-history-internal history)
  (setf (generic-history-data history) nil))

(defun reclaim-constant-history (history &optional delete-p)
  (reclaim-generic-history-internal history)
  (when (generic-history-data history)
    (reclaim-managed-float (generic-history-data history)))
  (setf (generic-history-data history) nil)
  (when delete-p
    (delete-frame history)))

(defun reclaim-cascaded-history (history &optional delete-p)
  (reclaim-generic-history-internal history)
  (when (generic-history-data history)
    (reclaim-history-buffer (generic-history-data history)))
  (setf (generic-history-data history) nil)
  (when delete-p
    (delete-frame history)))

(defun reclaim-variable-history (history &optional delete-p)
  (when trace-validate-p
    (format t "in reclaim~%"))
  (remove-generic-history-as-client-to-history-of-variable history)
  (reclaim-generic-history-internal history)
  (setf (generic-history-data history) nil)
  (when delete-p
    (delete-frame history)))

(defun initialize-generic-history (history length)
  (setf (generic-history-maximum-cache history)
	(allocate-extremum-cache history 'maximum (floorf length 32)))
  (setf (generic-history-minimum-cache history)
	(allocate-extremum-cache history 'minimum (floorf length 32))))

(defun reset-generic-history-internal (history)
  (reset-extremum-cache
    (generic-history-maximum-cache history) history)
  (reset-extremum-cache
    (generic-history-minimum-cache history) history))

(defun reclaim-generic-history-internal (history)
  (when (generic-history-minimum-cache history)
    (delete-extremum-cache
      (generic-history-minimum-cache history) history))
  (setf (generic-history-minimum-cache history) nil)
  (when (generic-history-maximum-cache history)
    (delete-extremum-cache
      (generic-history-maximum-cache history) history))
  (setf (generic-history-maximum-cache history) nil))


(defun update-generic-history-for-clock-discontinuity (history time-delta)
  (when (eq (generic-history-type history) 'cascaded)
    (add-delta-to-history-buffer-base-time
      (generic-history-data history)
      time-delta)))


;;;; Generic History Operators

;;; Run-time fine-grained access to histories and their indices, values, extrema
;;; is managed through this group of functions and macros.  This group uses macros
;;; a bit more heavily than I would like (as opposed to methods), but this is the code
;;; that gets called in the innermost loops of calculating a graph's plot.

    
;;; There are two tiers of caching for extrema.  The first is a very shallow lru
;;; to prevent unnecessary compuations for graphs that are in sync.  The second
;;; cache is maintained by keeping extrema for regular sub-intervals of the history

;;; right now the lru cache is just one element deep and is represented by a
;;; slot-value-list triple (start end index-of-value).  The sub-interval, or zone,
;;; cache is a vector of (index-of-value or -1) nil

;; extremum: polarity history zone-width zone-vector valid-p
;                whole-interval-cache zone-count zones-in-use zone-index
;                least-recent-index most-recent-index zone-index-size
;                initial-data-lost 
; graph-history: value-type maximum-cache minimum-cache
; local-history: value-buffer timestamp-buffer start end count length lost-data-count
; variable-history: structure

;;; generic-history-timestamp and generic-history-value both return gensym-floats
;;; and must be called in the a temporary-gensym-float context.  The mutating versions
;;; of the same can be called anywhere.  The rest of the operators in this suite return
;;; fixnum in all cases.

(defun get-variable-for-designation (designation)
  (when (or system-is-running system-has-paused)
    (let* ((*variables-that-did-not-have-values* nil)
	   (current-computation-flags current-computation-flags)
	   (variable? nil))
      (setf (role-serve-inactive-objects?) t)
      (setq variable? (evaluate-designation designation nil))
      (cond
	((and (framep variable?)
	      (frame-of-class-p variable? 'variable-or-parameter))
	 variable?)
	(t
	 (when (temporary-constant-p variable?)
	   (reclaim-temporary-constant variable?))
	 nil)))))


(defun get-cascaded-ring-buffer-for-designation (designation &optional
							     give-operator-message-p)
  (let* ((variable? (get-variable-for-designation designation))
	 (cascaded-ring-buffer?
	   (and variable?
		(variable-or-parameter-stored-histories? variable?))))
    (cond
      (cascaded-ring-buffer? cascaded-ring-buffer?)
      (variable?
       (when give-operator-message-p
	 (warning-message* 
	   1
	   "The plot expression \"~ND\" indicates variable or parameter without history."
	   designation)))
      (t
       (when give-operator-message-p
	 (warning-message* 
	   1
	   "The plot expression \"~ND\" did not evaluate to a variable or parameter."
	   designation))))))


(defun get-cascaded-ring-buffer-for-history (history &optional
						     give-operator-message-p)
  (case (generic-history-type history)
    (constant
     nil)
    (cascaded
     (generic-history-data history))
    (variable
     (let* ((unchecked-variable? (generic-history-data history))
	    (variable? (and unchecked-variable?
			    ;; fsn check
			    (frame-has-not-been-reprocessed-p
			     unchecked-variable?
			     (generic-history-data-serial-number history))
			    unchecked-variable?))
	    (cascaded-ring-buffer?
	     (and variable?
		  (if (variable-history-uses-simulator-p history)
		      (if (frame-of-class-p variable? 'variable) ; i.e. not a parameter
			  (let ((simulation-details? (simulation-details variable?)))
			    (and simulation-details?
				 (simulation-stored-histories? simulation-details?)))
			  nil)
		      (variable-or-parameter-stored-histories? variable?)))))
       (cond
	 (cascaded-ring-buffer? cascaded-ring-buffer?)
	 (variable?
	  (when give-operator-message-p
	    (warning-message* 
		1
		"The variable or parameter ~a does not have a history."
	      (name-or-names-for-frame variable?)))
	  nil)
	 (t
	  (when give-operator-message-p
	    (warning-message* 
		1
		"No variable or parameter available"))
	  nil))))))


(defmacro variable-history-ring-buffer (history)
  (avoiding-variable-capture (history)
    `(let* ((cascaded-ring-buffer?
	     (get-cascaded-ring-buffer-for-history ,history)))
;	    (error "Obsolete case")
;	    (setf (generic-history-data ,history) 
;		    (get-cascaded-ring-buffer-for-designation
;		      (generic-history-designation? history))))))
       (and cascaded-ring-buffer?
	    (car (cascaded-ring-buffers cascaded-ring-buffer?))))))

(defmacro variable-history-cascaded-ring-buffer (history)
  (avoiding-variable-capture (history)
    `(let* ((cascaded-ring-buffer?
	     (get-cascaded-ring-buffer-for-history ,history)))
;	       (generic-history-data ,history))))
;		  (error "obsolete-case")
;		  (setf (generic-history-data ,history) 
;			(get-cascaded-ring-buffer-for-designation
;			  (generic-history-designation? ,history))))))
       cascaded-ring-buffer?)))

(defun generic-history-supports-indexed-access-p (history)
  (case (generic-history-type history)
    (constant nil)
    ((cascaded variable) t)))

(defmacro generic-history-timestamp (history index)
  (avoiding-variable-capture (history index)
    `(case (generic-history-type ,history)
       (constant
	(error "index access not supported"))
       (cascaded
	(let ((cascaded-ring-buffer
		(generic-history-data ,history)))
	  (normalize-to-gensym-float
	    (get-history-g2-time
	      cascaded-ring-buffer ,index))))
       (variable
	(let ((cascaded-ring-buffer (variable-history-cascaded-ring-buffer ,history)))
	  (normalize-to-gensym-float
	    (get-history-g2-time
	      cascaded-ring-buffer ,index)))))))

;; trend charts have a particular view of what values are exceptional:
;; to allow for internal calculations to have room to maneuver, numbers
;; above most-positive-value (currently most-positive-gensym-float/10000)
;; are considered to be +infinity and truncated back to most-positive-value.
;; Similarly for most-negative-value.

(defmacro generic-history-nan-normalizer (value)
  (avoiding-variable-capture (value)
    `(case (exceptional-float-flavor? ,value)
       (positive-infinity (most-positive-value))
       (negative-infinity (most-negative-value))
       (nan 0.0)
       (otherwise
	(cond ((>=e ,value (most-positive-value))
	       (most-positive-value))
	      ((<=e ,value (most-negative-value))
	       (most-negative-value))
	      (t ,value))))))

(defmacro generic-history-value (history index)
  (avoiding-variable-capture (history index)
    `(generic-history-nan-normalizer
       (normalize-to-gensym-float
	 (case (generic-history-type ,history)
	   (constant
	    (generic-history-data ,history))
	   (cascaded
	    (let ((ring-buffer
		    (car (cascaded-ring-buffers
			   (generic-history-data ,history)))))
	      (if ring-buffer
		  (get-history-value ring-buffer ,index)
		(progn
		  #+development
		  (error "ring-buffer is null")
		  0))))
	   (variable
	    (let ((ring-buffer (variable-history-ring-buffer ,history)))
	      (if ring-buffer
		  (get-history-value ring-buffer ,index)
		(progn
		  #+development
		  (error "ring-buffer is null")
		  0))))
           (otherwise 0))))))
	 
(defmacro generic-history-start-index (history)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	(error "indexed access not supported"))
       (cascaded
	(let ((ring-buffer (car (cascaded-ring-buffers
				  (generic-history-data ,history)))))
	  (if ring-buffer
	      (oldest-active-element-index ring-buffer)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (variable
	(let ((ring-buffer (variable-history-ring-buffer ,history)))
	  (if ring-buffer
	      (oldest-active-element-index ring-buffer)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (otherwise 0))))

(defmacro generic-history-end-index (history)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	(error "indexed access not supported"))
       (cascaded
	(let ((ring-buffer (car (cascaded-ring-buffers
				  (generic-history-data ,history)))))
	  (if ring-buffer
	      (newest-active-element-index ring-buffer)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (variable
	(let ((ring-buffer (variable-history-ring-buffer ,history)))
	  (if ring-buffer
	      (newest-active-element-index ring-buffer)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (otherwise 0))))

(defmacro generic-history-interval-length (history start end)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	(error "indexed access not supported"))
       (cascaded
	(let ((ring-buffer (car (cascaded-ring-buffers
				  (generic-history-data ,history)))))
	  (if ring-buffer
	      (ring-buffer-index-difference ring-buffer ,end ,start)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (variable
	(let ((ring-buffer (variable-history-ring-buffer ,history)))
	  (if ring-buffer
	      (ring-buffer-index-difference ring-buffer ,end ,start)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (otherwise 0))))

(defmacro generic-history-size (history)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	1)
       (cascaded
	(let ((ring-buffer? (car (cascaded-ring-buffers
				   (generic-history-data ,history)))))
	  (if ring-buffer?
	      (ring-buffer-size ring-buffer?)
	    0)))
       (variable
	(let* ((cascaded-ring-buffer?
		 (variable-history-cascaded-ring-buffer ,history))
	       (ring-buffer?
		 (and cascaded-ring-buffer?
		      (variable-history-ring-buffer ,history))))
	  (if ring-buffer?
	      (ring-buffer-size ring-buffer?)
	    0)))
       (otherwise 0))))

(defmacro generic-history-count (history)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	1)
       (cascaded
	(let ((ring-buffer? (car (cascaded-ring-buffers
				  (generic-history-data ,history)))))
	  (cond ((or (null ring-buffer?)
		     (ring-buffer-empty? ring-buffer?))
		 0)
		(t
		 (ring-buffer-length ring-buffer?)))))
       (variable
	(let* ((cascaded-ring-buffer?
		(variable-history-cascaded-ring-buffer ,history))
	       (ring-buffer?
		 (and cascaded-ring-buffer?
		      (car (cascaded-ring-buffers cascaded-ring-buffer?)))))
	  (cond (ring-buffer?
		 (cond ((ring-buffer-empty? ring-buffer?)
			0)
		       (t
			(ring-buffer-length ring-buffer?))))
		(t
		 0))))
       (otherwise 0))))

(defmacro generic-history-lost-data-count (history)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	0)
       (cascaded
	(history-elements-discarded
	  (generic-history-data ,history)))
       (variable
	(let ((cascaded-ring-buffer?
		(variable-history-cascaded-ring-buffer ,history)))
	  (cond (cascaded-ring-buffer?
		 (history-elements-discarded cascaded-ring-buffer?))
		(t
		 0))))
       (otherwise 0))))

(defmacro generic-history-empty-p (history)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	(null (generic-history-data ,history)))
       (cascaded
	(let ((ring-buffer (car (cascaded-ring-buffers
				  (generic-history-data ,history)))))
	  (ring-buffer-empty? ring-buffer)))
       (variable
	(let ((ring-buffer (variable-history-ring-buffer ,history)))
	  (ring-buffer-empty? ring-buffer))))))

(defmacro generic-history-full-p (history)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	(generic-history-data ,history))
       (cascaded
	(let ((ring-buffer (car (cascaded-ring-buffers
				  (generic-history-data ,history)))))
	  (ring-buffer-full? ring-buffer)))
       (variable
	(let ((ring-buffer (variable-history-ring-buffer ,history)))
	 (ring-buffer-full? ring-buffer))))))

(defmacro generic-history-high-water-mark (history)
  (avoiding-variable-capture (history)
    `(generic-history-nan-normalizer
       (normalize-to-gensym-float
	 (case (generic-history-type ,history)
	   (constant
	    (generic-history-data ,history))
	   (cascaded
	    (let* ((cascaded-ring-buffer
		     (generic-history-data ,history))
		   (high-water-mark?
		     (highest-value-ever-in-history? cascaded-ring-buffer)))
	      (or high-water-mark? (uninitialized-positive-value-flag))))
	   (variable
	    (let* ((cascaded-ring-buffer
		     (variable-history-cascaded-ring-buffer ,history))
		   (high-water-mark?
		     (highest-value-ever-in-history? cascaded-ring-buffer)))
	      (or high-water-mark? (uninitialized-positive-value-flag)))))))))

(defmacro generic-history-high-water-marks-exist-p (history)
  (avoiding-variable-capture (history)
    `(case (generic-history-type ,history)
       (constant
	  (generic-history-data ,history))
       (cascaded
	(let* ((cascaded-ring-buffer
		(generic-history-data ,history)))
	  (highest-value-ever-in-history? cascaded-ring-buffer)))
       (variable
	(let* ((cascaded-ring-buffer (variable-history-cascaded-ring-buffer ,history)))
	  (highest-value-ever-in-history? cascaded-ring-buffer))))))

(defmacro generic-history-low-water-mark (history)
  (avoiding-variable-capture (history)
    `(generic-history-nan-normalizer
       (normalize-to-gensym-float
	 (case (generic-history-type ,history)
	   (constant (generic-history-data ,history))
	   (cascaded
	    (let* ((cascaded-ring-buffer
		     (generic-history-data ,history))
		   (low-water-mark?
		     (lowest-value-ever-in-history? cascaded-ring-buffer)))
	      (or low-water-mark? (uninitialized-negative-value-flag))))
	   (variable
	    (let* ((cascaded-ring-buffer
		     (variable-history-cascaded-ring-buffer ,history))
		   (low-water-mark?
		     (lowest-value-ever-in-history? cascaded-ring-buffer)))
	      (or low-water-mark? (uninitialized-negative-value-flag))))
           (otherwise 0))))))

(defmacro generic-history-index-position (history index)
  (avoiding-variable-capture (history index)
    `(case (generic-history-type ,history)
       (constant
        #+development
	(error "indexed access not supported")
        0)
       (cascaded
	(let ((ring-buffer (car (cascaded-ring-buffers
				   (generic-history-data ,history)))))
	  (ring-buffer-length-up-to-index ring-buffer ,index)))
       (variable
	(let ((ring-buffer (variable-history-ring-buffer ,history)))
	  (ring-buffer-length-up-to-index ring-buffer ,index)))
       (otherwise 0))))

(defmacro previous-generic-history-index (history index)
  (avoiding-variable-capture (history index)
    `(case (generic-history-type ,history)
       (constant
        #+development
	(error "indexed access not supported")
        0)
       (cascaded
	(let ((ring-buffer (car (cascaded-ring-buffers
				  (generic-history-data ,history)))))
	  (if ring-buffer
	      (decrement-active-element-index ,index ring-buffer)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (variable
	(let ((ring-buffer (variable-history-ring-buffer ,history)))
	  (if ring-buffer
	      (decrement-active-element-index ,index ring-buffer)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (otherwise 0))))

(defmacro next-generic-history-index (history index)
  (avoiding-variable-capture (history index)
    `(case (generic-history-type ,history)
       (constant
        #+development
	(error "indexed access not supported")
        0)
       (cascaded
	(let ((ring-buffer (car (cascaded-ring-buffers
				  (generic-history-data ,history)))))
	  (if ring-buffer
	      (increment-active-element-index ,index ring-buffer)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (variable
	(let ((ring-buffer (variable-history-ring-buffer ,history)))
	  (if ring-buffer
	      (increment-active-element-index ,index ring-buffer)
	    (progn
	      #+development
	      (error "ring-buffer is null")
	      0))))
       (otherwise 0))))

(defmacro get-history-time-as-float (cascaded-ring-buffer index)
  `(normalize-to-gensym-float
     (get-history-g2-time
       ,cascaded-ring-buffer ,index)))

(defun generic-history-index (history timestamp inclusion low-bound-p)
  (let ((history-type (generic-history-type history)))
    (case history-type
      (constant
       #+development
       (error "indexed access not supported")
       0)
      ((cascaded variable)
       (let* ((cascaded-ring-buffer
		(if (eq history-type 'cascaded)
		    (generic-history-data history)
		    (variable-history-cascaded-ring-buffer history)))
	      (ring-buffer
		(car (cascaded-ring-buffers cascaded-ring-buffer)))
	      (index
		(get-history-index-by-binary-search
		  cascaded-ring-buffer timestamp nil))
	      (time-for-index
		(get-history-time-as-float cascaded-ring-buffer index)))
	 (case inclusion
	   (inclusive
	    (cond
	      ((and low-bound-p (<time time-for-index timestamp))
	       ;; try next index
	       (let* ((next-index?
			(and (/=f (newest-active-element-index ring-buffer) index)
			     (increment-active-element-index index ring-buffer)))
		      (time-for-next-index
			(and next-index?
			     (get-history-time-as-float
			       cascaded-ring-buffer next-index?))))
		 (cond ((and next-index?
			     (>=time time-for-next-index timestamp))
			next-index?)
		       (t index))))
	      ((and (not low-bound-p) (>time time-for-index timestamp))
	       ;; try-previous
	       (let* ((prev-index?
			(and (/=f (oldest-active-element-index ring-buffer) index)
			     (decrement-active-element-index index ring-buffer)))
		      (time-for-prev-index
			(and prev-index?
			     (get-history-time-as-float
			       cascaded-ring-buffer prev-index?))))
		 (cond ((and prev-index? (<=time time-for-prev-index timestamp))
			prev-index?)
		       (t index))))
	      (t
	       index)))
	   (exclusive
	    (cond
	      ((and low-bound-p (<=time time-for-index timestamp))
	       ;; try next index
	       (let* ((next-index?
			(and (/=f (newest-active-element-index ring-buffer) index)
			     (increment-active-element-index index ring-buffer)))
		      (time-for-next-index
			(and next-index?
			     (get-history-time-as-float
			       cascaded-ring-buffer next-index?))))
		 (cond ((and next-index?
			     (>time time-for-next-index timestamp))
			next-index?)
		       (t index))))
	      ((and (not low-bound-p) (>=time time-for-index timestamp))
	       ;; try-previous
	       (let* ((prev-index?
			(and (/=f (oldest-active-element-index ring-buffer) index)
			     (decrement-active-element-index index ring-buffer)))
		      (time-for-prev-index
			(and prev-index?
			     (get-history-time-as-float
			       cascaded-ring-buffer prev-index?))))
		 (cond ((and prev-index? (<time time-for-prev-index timestamp))
			prev-index?)
		       (t index))))
	      (t
	       index)))
	   (loose
	    (cond
	      ((and low-bound-p (>time time-for-index timestamp))
	       ;; try-previous
	       (let* ((prev-index?
			(and (/=f (oldest-active-element-index ring-buffer) index)
			     (decrement-active-element-index index ring-buffer)))
		      (time-for-prev-index
			(and prev-index?
			     (get-history-time-as-float
			       cascaded-ring-buffer prev-index?))))
		 (cond ((and prev-index? (<=time time-for-prev-index timestamp))
			prev-index?)
		       (t index))))
	      ((and (not low-bound-p) (<time time-for-index timestamp))
	       ;; try next index
	       (let* ((next-index?
			(and (/=f (newest-active-element-index ring-buffer) index)
			     (increment-active-element-index index ring-buffer)))
		      (time-for-next-index
			(and next-index?
			     (get-history-time-as-float
			       cascaded-ring-buffer next-index?))))
		 (cond ((and next-index?
			     (>=time time-for-next-index timestamp))
			next-index?)
		       (t index))))
	      (t
	       index)))))))))


(defmacro generic-history-earliest-timestamp (history default-earliest-time)
  (avoiding-variable-capture (history default-earliest-time)
    `(case (generic-history-type ,history)
       (constant
	,default-earliest-time)
       ((variable cascaded)
	(generic-history-timestamp
	  ,history
	  (generic-history-start-index ,history))))))

(defmacro generic-history-value-at-time (history timestamp)
  (avoiding-variable-capture (history timestamp)
    `(case (generic-history-type ,history)
       (constant
	(normalize-to-gensym-float
	  (generic-history-data ,history)))
       ((variable cascaded)
	timestamp
	(error "NYI")))))


(defmacro generic-history-latest-timestamp (history default-latest-time)
  (avoiding-variable-capture (history default-latest-time)
    `(case (generic-history-type ,history)
       (constant
	,default-latest-time)
       ((variable cascaded)
	(generic-history-timestamp
	  ,history
	  (generic-history-end-index ,history))))))

(defmacro generic-history-index= (a b)
  `(=f ,a ,b))




;;;; History Extrema Caching

;;; This stuff makes my head spin.


(defun smallest-lesser-factor (n)
  (cond ((oddp n)
	 (loop with lim = (isqrt n)
	       for i from 3 to lim by 2
	       do
	   ;; (print i)
	   (when (=f 0 (modf n i))
	     (return i))
	       finally
		 (return nil)))
	(t
	 2)))

;; The outer loop of get-next-highest-prime is virtually guaranteed to need very
;; few iterations by the density of the prime numbers in the natural numbers at
;; n, which is 1/ln(n).  The inner loop executes in roughly (sqrt n).  So the
;; whole thing is O(n^(1/2)ln(n)).  This is small enough to be safely called in
;; one G2 scheduler quantum for n as large as 10000, which I don't think would
;; be approached.

(defun get-next-highest-prime (n)
  (unless (oddp n)
    (incff n))
  (loop for test from n by 2
	do
    (unless (smallest-lesser-factor test)
      (return test))))

;; extremum: polarity history zone-width zone-vector valid-p
;                whole-interval-cache zone-count zones-in-use zone-index
;                least-recent-index most-recent-index zone-index-size
;                initial-data-lost 
; graph-history: value-type maximum-cache minimum-cache
; local-history: value-buffer timestamp-buffer start end count length 
; variable-history: structure

(defmacro make-zone-cache-element () `(slot-value-list nil nil nil))
(defmacro zone-cache-element-value-index (zce) `(caddr ,zce))
(defmacro zone-cache-element-next (zce) `(car ,zce))
(defmacro zone-cache-element-previous (zce) `(cadr ,zce))


(defun allocate-extremum-cache (history polarity zone-count)
  (let ((extremum-cache (make-extremum-cache))
;	(zone-width (ceilingf (generic-history-size history) zone-count))
;	(old-data-lost (generic-history-lost-data-count history))
	(zone-index-size (get-next-highest-prime zone-count)))
    
    (setf (extremum-polarity extremum-cache) polarity)
    (setf (extremum-history extremum-cache) history)
    
    (setf (extremum-zone-index-size extremum-cache) zone-index-size)
    (setf (extremum-zone-index extremum-cache)
	  (allocate-managed-array zone-index-size))

    (setf (extremum-zone-count extremum-cache) zone-count)
    (setf (extremum-zone-vector extremum-cache)
	  (allocate-managed-array zone-count))

    (reset-extremum-cache extremum-cache history)))

(defmacro copy-slots-for-slot-value (slot-names new-obj-exp old-obj-exp)
  (loop with old-obj = (gensym)
	with new-obj = (gensym)
        for slot-name in slot-names
	collect
	`(setf (,slot-name ,new-obj)
	       (copy-for-slot-value (,slot-name ,old-obj)))
	into set-forms
	finally
	  (return `(let ((,old-obj ,old-obj-exp)
			 (,new-obj ,new-obj-exp))
		     ,@set-forms))))

(defun copy-extremum-cache (extremum-cache history)
  (let ((new-extremum-cache (make-extremum-cache)))
    (copy-slots-for-slot-value
      (extremum-polarity 
	extremum-zone-vector
	extremum-zone-count
	extremum-zone-index 
	extremum-zone-index-size
	extremum-zones-in-use
	extremum-whole-interval-cache
	extremum-zone-width 
	extremum-initial-data-lost
	extremum-least-recent-index
	extremum-most-recent-index
	extremum-cache-valid-p)
      new-extremum-cache extremum-cache)
    (setf (extremum-history new-extremum-cache)
	  history)
    new-extremum-cache))
    

(defun reset-extremum-cache (extremum-cache history)
  (let* ((zone-count (extremum-zone-count extremum-cache))
	 (history-size? (generic-history-size history))
	 (zone-width (if history-size?
			 (ceilingf history-size? zone-count)
			 2))
	 (old-data-lost (generic-history-lost-data-count history)))
    
    (setf (extremum-most-recent-index extremum-cache) nil)
    (setf (extremum-least-recent-index extremum-cache) nil)
    (setf (extremum-zones-in-use extremum-cache) 0)

    (loop with zone-vector = (extremum-zone-vector extremum-cache)
	  for i from 0 below (extremum-zone-count extremum-cache)
	  do
      (reclaim-slot-value-list (managed-svref zone-vector i))
      (setf (managed-svref zone-vector i) nil))
    (loop with zone-index = (extremum-zone-index extremum-cache)
	  for i from 0 below (extremum-zone-index-size extremum-cache)
	  do
      (reclaim-slot-value-tree (managed-svref zone-index i))
      (setf (managed-svref zone-index i) nil))
    
    (reclaim-slot-value-list (extremum-whole-interval-cache extremum-cache))
    (setf (extremum-whole-interval-cache extremum-cache) nil)

    (setf (extremum-zone-width extremum-cache) zone-width)
    (setf (extremum-initial-data-lost extremum-cache) old-data-lost)

    (setf (extremum-cache-valid-p extremum-cache) t)
    extremum-cache))
  

(defun delete-extremum-cache (extremum-cache history)
  (declare (ignore history)) ; eventually the history object may need to be signalled (?)
  (reclaim-slot-value-list (extremum-whole-interval-cache extremum-cache))
  (setf (extremum-whole-interval-cache extremum-cache) nil)
  (loop with zone-vector = (extremum-zone-vector extremum-cache)
        for i from 0 below (extremum-zone-count extremum-cache)
	do
    (reclaim-slot-value-list (managed-svref zone-vector i))
    (setf (managed-svref zone-vector i) nil))
  (loop with zone-index = (extremum-zone-index extremum-cache)
	for i from 0 below (extremum-zone-index-size extremum-cache)
	do
    (reclaim-slot-value-tree (managed-svref zone-index i))
    (setf (managed-svref zone-index i) nil))

  ;; cutting all pointers to outside world before reclamation
  (setf (extremum-history extremum-cache) nil)
  
  (reclaim-extremum-cache extremum-cache))

(defmacro position-in-history (history-exp index-exp)
  (let ((history (gensym))
	(index (gensym)))
    `(let* ((,history ,history-exp)
	    (,index ,index-exp)
	    (history-start (generic-history-start-index ,history))
	    (history-count (generic-history-count ,history))
	    (history-size (generic-history-size ,history)))
       (cond ((<f history-count history-size) ; implies history-start = 0 
	      ,index)			;       this might only be true for local-history
	     ((<f ,index history-start)
	      (+f ,index (-f history-size history-start)))
	     (t
	      (-f ,index history-start))))))


(defmacro map-relative-to-absolute-history-index (history index)
  (avoiding-variable-capture (history index)
    `(let ((position-in-history
	     (1-f (generic-history-index-position ,history ,index))))
       (+f position-in-history
	   (generic-history-lost-data-count ,history)))))       

(defmacro map-absolute-to-relative-history-index (history index)
  (avoiding-variable-capture (history index)
    `(let* ((position-in-history (-f ,index
				     (generic-history-lost-data-count ,history)))
	    (history-start (generic-history-start-index ,history))
	    (history-end (generic-history-end-index ,history))
	    (history-size (generic-history-size ,history)))
       (cond ((<= history-start history-end)
	      (+f position-in-history history-start))
	     (t
	      (modf (-f position-in-history
			(-f history-size history-start))
		    history-size))))))

;defun-simple
(defmacro old-map-relative-to-absolute-history-index (history-exp relative-index)
  (let ((history (gensym)))
    `(let ((,history ,history-exp))
       (+f (generic-history-lost-data-count ,history)
	   (position-in-history ,history ,relative-index)))))

(defmacro old-map-absolute-to-relative-history-index (history-exp absolute-index)
  (let ((history (gensym)))
    `(let* ((,history ,history-exp)
	    (relative-position (-f ,absolute-index
				   (generic-history-lost-data-count ,history))))
       (format t "rel-pos ~s~%" relative-position)
       (modf (+f relative-position (generic-history-start-index ,history))
	     (generic-history-size ,history)))))

(defun get-zone-start (history extremum-cache absolute-start)
  (declare (ignore history))
  (-f absolute-start
      (modf (-f absolute-start (extremum-initial-data-lost extremum-cache))
	    (extremum-zone-width extremum-cache))))

(defun add-zone-cache-element (extremum-cache start-index value-index)
  (let* ((zone-vector (extremum-zone-vector extremum-cache))
	 (vector-index
	   (cond ((=f (extremum-zones-in-use extremum-cache)
		      (extremum-zone-count extremum-cache))
		  (let* ((lru-element-index
			  (extremum-least-recent-index extremum-cache))
			 (2nd-to-lru-element-index
			   (zone-cache-element-previous
				(managed-svref zone-vector lru-element-index))))
		    ;; unlink 2nd-to-lru from lru
		    (setf (zone-cache-element-next
			    (managed-svref zone-vector 2nd-to-lru-element-index))
			  nil)
		    (setf (extremum-least-recent-index extremum-cache)
			  2nd-to-lru-element-index)
		    ;; remove it from the zone index
		    (remove-zone-cache-element-index extremum-cache start-index)
		    ;; HERE 
		    (remove-zone-cache-element-index
		      extremum-cache
		      (get-zone-start
			(extremum-history extremum-cache)
			extremum-cache
			(zone-cache-element-value-index
			  (managed-svref zone-vector lru-element-index))))
		    lru-element-index))
		 (t
		  (let ((zones-in-use (extremum-zones-in-use extremum-cache)))
		    (unless (managed-svref zone-vector zones-in-use)
		      (setf (managed-svref zone-vector zones-in-use)
			    (make-zone-cache-element)))
		    (incf (extremum-zones-in-use extremum-cache))
		    zones-in-use))))
	 (zone-cache-element (managed-svref zone-vector vector-index)))
    (setf (zone-cache-element-value-index zone-cache-element)
	  value-index)
    (add-zone-cache-element-index extremum-cache start-index vector-index)
    (make-zone-cache-element-most-recent
      extremum-cache zone-cache-element vector-index)))

(defun add-zone-cache-element-index (extremum-cache start-index vector-index)
  ;; this is simplified by the fact that we always know that there is no
  ;; entry for start index in the zone-index; i.e. we don't need to gethash
  ;; before puthash
  (slot-value-push
    (slot-value-cons start-index vector-index)
    (managed-svref (extremum-zone-index extremum-cache)
		   (modf start-index
			 (extremum-zone-index-size extremum-cache)))))

(defun remove-zone-cache-element-index (extremum-cache start-index)
  (let* ((chain-index (modf start-index
			    (extremum-zone-index-size extremum-cache)))
	 (zone-index (extremum-zone-index extremum-cache))
	 (chain (managed-svref zone-index chain-index)))
    (loop with previous-tail = nil
	  for  tail on chain
	   as bucket = (car tail)
	  do
      (cond ((=f (car-of-cons bucket) start-index)
	     (cond (previous-tail
		    (setf (cdr previous-tail)
			  (cdr tail)))
		   (t
		    (setf (managed-svref zone-index chain-index)
			  (cdr tail))))
	     (reclaim-slot-value-cons bucket)
	     (reclaim-slot-value-cons tail)
	     (return nil))
	    (t
	     (setf previous-tail tail))))))

(defun make-zone-cache-element-most-recent
    (extremum-cache zone-cache-element vector-index)
  (let ((former-most-recent-index (extremum-most-recent-index extremum-cache))
	(zone-vector (extremum-zone-vector extremum-cache)))
    (cond
      (former-most-recent-index
       (let ((former-most-recent-zone-cache-element
	       (managed-svref zone-vector former-most-recent-index)))
	 (setf (zone-cache-element-previous
		 former-most-recent-zone-cache-element)
	       vector-index)))
      (t
	(setf (extremum-least-recent-index extremum-cache) vector-index)))
       ;; establish least
    (setf (zone-cache-element-next zone-cache-element)
	  former-most-recent-index) ;; its ok if this is NIL
    (setf (zone-cache-element-previous zone-cache-element)
	  nil)
    (when (null vector-index)
      (error "Null vector index in make zce most recent ~%"))
    (setf (extremum-most-recent-index extremum-cache) vector-index)))
    
(defun lookup-zone-cache-element (extremum-cache start-index)
  (when (>f (extremum-zones-in-use extremum-cache) 0)
    (let* ((chain (managed-svref (extremum-zone-index extremum-cache)
				 (modf start-index (extremum-zone-index-size
						     extremum-cache))))
	   (vector-index
	     (and chain
		  (loop for bucket in chain
			do
;		    (format t "Bucket=~s~%" bucket)
		    (when (=f (car-of-cons bucket) start-index)
		      (return (cdr-of-cons bucket)))
			finally
			  (return nil))))
	   (zone-vector (extremum-zone-vector extremum-cache)))
      
;      (format t "vector-index=~s mri=~s~%"
;	      vector-index
;	      (extremum-most-recent-index extremum-cache))
      (when (and vector-index
		 (not (=f vector-index (extremum-most-recent-index extremum-cache))))
	(let* ((zone-cache-element (managed-svref zone-vector vector-index))
	       (previous-index (zone-cache-element-previous zone-cache-element))
	       (next-index (zone-cache-element-next zone-cache-element)))
	  (setf (zone-cache-element-next
		  (managed-svref zone-vector previous-index))
		next-index)
	  (cond (next-index
		 (setf (zone-cache-element-previous
			 (managed-svref zone-vector next-index))
		       previous-index))
		(t
		 (setf (extremum-least-recent-index extremum-cache)
		       previous-index)))
	  (make-zone-cache-element-most-recent
	    extremum-cache zone-cache-element vector-index)))
      (cond (vector-index
	     (zone-cache-element-value-index
	       (managed-svref zone-vector vector-index)))
	    (t
	     nil)))))

(defun update-whole-interval-extremum-cache (extremum-cache start end value-index)
  (let ((triple (extremum-whole-interval-cache extremum-cache)))
    (cond
      (triple
       (setf (car triple) start)
       (setf (cadr triple) end)
       (setf (caddr triple) value-index))
      (t
       (setf (extremum-whole-interval-cache extremum-cache)
	     (slot-value-list start end value-index))))))

(defmacro try-whole-interval-extremum-cache (extremum-cache start end)
  `(let ((triple (extremum-whole-interval-cache ,extremum-cache)))
     (cond ((and triple
	         (=f (pop triple) ,start)
		 (=f (pop triple) ,end))
	    (pop triple))
	   (t
	    nil))))

;; this macro does not care one whit about multiple evaluations of place
;; It probably should be a macrolet, because of its lack of generality

;; this macro needs that generic-history-x-value is always up-to-date.
;; This can be ensured once per scheduler quantum at start of draw method.

(defmacro update-history-extremum-absolute
    (history-value-accessor history-exp polarity
			    relative-index-place
			    new-value-relative-index-exp
			    less-than greater-than)
  (let ((history (gensym))
	(new-value-relative-index (gensym)))
    `(let ((,history ,history-exp)
	   (,new-value-relative-index ,new-value-relative-index-exp))
       (cond
	 (,relative-index-place
	  (let ((current-value (,history-value-accessor
				  ,history
				  (map-absolute-to-relative-history-index
				    ,history ,relative-index-place)))
		(new-value (,history-value-accessor
			      ,history
			      (map-absolute-to-relative-history-index
				,history ,new-value-relative-index))))
	    (case ,polarity
	      (minimum
	       (when (,less-than new-value current-value)
		 (setf ,relative-index-place ,new-value-relative-index)))
	      (maximum
	       (when (,greater-than new-value current-value)
		 (setf ,relative-index-place ,new-value-relative-index))))))
	 (t
	  (setf ,relative-index-place ,new-value-relative-index))))))

(defmacro update-history-value-extremum (history polarity place-of-index new-value-index)
  `(update-history-extremum-absolute
     generic-history-value
     ,history ,polarity ,place-of-index ,new-value-index
     <value >value))

;; compute-extremum-for-interval returns an absolute index
;; most extremum handling uses these indices because it will
;; reduce the creation and motion of a lot of floats, and require
;; very "casey" code to keep checking value types in all places

#+development
(defun print-values-for-interval (history start end)
  (with-temporary-gensym-float-creation waka-waka
    (format t "History values from ~s to ~s" start end)
    (loop for index = start
		    then (next-generic-history-index history index)
	   as count from 0 by 1
	  until (=f (previous-generic-history-index history index) end)
	  do
      (when (zerop (modf count 5))
	(format t "~%"))
      (format t "~vTVal(~3d)=~10f"
	      (*f 22 count) index (generic-history-value history index))
	  finally
	    (format t "~%"))))

(defun history-size-is-constant? (history extremum-cache)
  (let ((new-size? (generic-history-size history)))
    (cond ((eql (extremum-last-known-history-size? extremum-cache)
		new-size?)
	   t)
	  (t
	   (setf (extremum-last-known-history-size? extremum-cache)
		 new-size?)
	   nil))))

;;; Three ideas to speed extrema computation:
;;;
;;; - Have reset-extremum-cache reallocate larger arrays to keep zone-width
;;;   to a certain range, rather than have it go up linearly with history
;;;   size.  This is a basic memory for speed trade.  Base such reallocation
;;;   on a parameter called desired-number-average-number-of-comparisons-for-
;;;   extremum-computation?
;;;
;;; - maintain a notion of a last zone or open zone, such that running extrema
;;;   can be maintained for it
;;;
;;; - treat the first zone specially so that we use its extrema even if
;;;   it is only a right subset of a whole zone.  The restriction on its is
;;;   that its extrema should be less extreme than other zones, and thus
;;;   all of its zone-subsets would have extrema that are less extreme as well.
;;;   This optimization would force a re-ordering of the loop in the following
;;;   function so that all "whole" zones would be checked first.  In addition
;;;   to this notion we could maintain a special last zone extremum-computation
;;;   method that would know how to find the extrema of right zone subsets
;;;   faster than full recomputation in most cases.


(defun compute-extremum-for-interval (history start end polarity)
  (let ((extremum-cache (if (eq polarity 'minimum)
			    (generic-history-minimum-cache history)
			    (generic-history-maximum-cache history))))
    (unless (and (extremum-cache-valid-p extremum-cache)
		 (history-size-is-constant? history extremum-cache))
      (reset-extremum-cache extremum-cache history))
    (let* ((absolute-start (map-relative-to-absolute-history-index
			     history start))
	   (absolute-end (map-relative-to-absolute-history-index history end))
	   (extreme-value (try-whole-interval-extremum-cache
			   extremum-cache absolute-start absolute-end)))
      (declare (ignore extreme-value)) ; *** restore this soon
;      (format t "CEFI abs=(~s,~s)~%" absolute-start absolute-end)
      (cond
	(nil nil) ;extreme-value extreme-value) ; actually, an index of the value
	(t
	 (let* ((first-zone-start (get-zone-start history extremum-cache
						  absolute-start))
		(extremum-zone-width (extremum-zone-width extremum-cache))
		(interval-length (generic-history-interval-length
				   history start end))
		;; must handle short intervals better *** 
		(extreme-value-index
	          (compute-extremum-for-zone
		    history extremum-cache polarity absolute-start
		    (cond ((>f interval-length extremum-zone-width)
			   (+f first-zone-start extremum-zone-width))
			  (t
			   (+f absolute-start interval-length))))))
;	   (format t "interval=(~s,~s) abs=(~s,~s) first-zone-start=~s~%"
;		   start end absolute-start absolute-end first-zone-start)
	   (loop for zone-start from (+f first-zone-start extremum-zone-width)
				by extremum-zone-width
		  as first-time-p = t then nil
		  as zone-end = (+f zone-start extremum-zone-width)
		 do
	     (when (>f zone-end absolute-end)
	       ;; do last fragment except when first and last are the same
	       (unless (>f zone-start absolute-end) ;  first-time-p ; *** ???
		 (update-history-value-extremum
		   history polarity extreme-value-index
		   (compute-extremum-for-zone
		     history extremum-cache polarity zone-start
		     (1+f absolute-end)))) ; becuz cefz takes exclusive bounds
	       ;; update the whole-interval cache (which uses absolute indices)
	       (update-whole-interval-extremum-cache
		 extremum-cache absolute-start absolute-end extreme-value-index)
	       (return extreme-value-index))

	     (update-history-value-extremum
	       history polarity extreme-value-index
	       (compute-extremum-for-zone
		 history extremum-cache polarity zone-start zone-end)))))))))

#+development
(defvar ec-tries 0)
#+development
(defvar ec-hits 0)

(defun compute-extremum-for-zone (history extremum-cache polarity
					  zone-start zone-end)
;  (format t "CEFZ start=~s end=~S~%" zone-start zone-end)
  #+development
  (incf ec-tries)
  (let* ((zone-width (extremum-zone-width extremum-cache))
	 (cacheable-p (=f (-f zone-end zone-start) zone-width))
	 (cached-value-index
	   (and cacheable-p
		(lookup-zone-cache-element extremum-cache zone-start))))
    (when (and cached-value-index
	       (not (<=f zone-start cached-value-index zone-end)))
      #+development
      (format t "CVI=~S not in (~s,~s)~%"
	      cached-value-index zone-start zone-end)
      #+development
      (break))
    (cond
      ( cached-value-index
       #+development
       (incf ec-hits)
       cached-value-index)
      ((>=f zone-end zone-start)
       (loop with extremum = zone-start
	     for i from (1+f zone-start) below zone-end ; these are absolute indices with
					; exclusive end bounds, I think
	     do
	 (update-history-value-extremum
	   history polarity extremum i)
	     finally
	       (when cacheable-p
		 (unless (<=f zone-start extremum zone-end)
		   #+development
		   (format t "AZCE Snafu extremum=~s not in (~s,~s)~%"
			   extremum zone-start zone-end))
		 (add-zone-cache-element extremum-cache zone-start extremum))
	       (return extremum)))
      (t
       nil))))
	   

;; get-extrema-for-zone (or check-cache compute-extrema-for-zone and cache it)
;; compute-extrema-for-zone (do it the hard way when request does not cover whole
;; zone)


;;; Extrema caches should become invalid whenever history indices or history
;;; index bounds change.  This could happen when data is added to the middle of
;;; a hsitory or when previous history values are overwritten.
    
(defun invalidate-extrema-caches (history)
  (setf (extremum-cache-valid-p
	  (generic-history-minimum-cache history)) nil)
  (setf (extremum-cache-valid-p
	  (generic-history-maximum-cache history)) nil))

(defun invalidate-history-indices (history)
  (invalidate-extrema-caches history))

(defun generic-history-maximum-value-index (history start end)
  (map-absolute-to-relative-history-index
    history
    (compute-extremum-for-interval history start end 'maximum)))

(defun generic-history-minimum-value-index (history start end)
  (map-absolute-to-relative-history-index
    history
    (compute-extremum-for-interval history start end 'minimum)))




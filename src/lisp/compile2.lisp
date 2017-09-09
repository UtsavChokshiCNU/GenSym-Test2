;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module COMPILE2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann





;; To Do


;; Compile2-decoupled-and could just call compile2-comparison-operator-expression.
;; This would save some repetition.

;; Compile-forward-reference-path-for-symbol needs some review.  Besides being names
;; of kb objects or local names, symbols can also be reserved words such as 'true.
;; Review all cases of designations without reference paths.

;; In most of the compiler code, "form" would be a better term than "expression".
;; "Compiled-form-structure" would be a better term than 
;; "expression-for-compilation".

;; Get rid of for-all in third pass.  This is obsolete (check with Mike).


;;; COMPILE2 contains the first, second, and third passes of the
;;; compiler.  These are common to all statements (both rules
;;; and formulas).


;;;; First pass compilation

;;; The first pass of compilation converts generic expressions to
;;; specific ones and builds reference-structures.  Reference paths
;;; for the compilation without focus are built first and are then
;;; used to build reference paths for the compilation with focus.
;;; The reference paths then are used to determine what names 
;;; are provided within the expression and what names can be
;;; provided externally.

;;; Strings are copied in the first pass by
;;; compile1-forward-reference-for-designations-rec so that they are not
;;; eq to the string in the source.  This would cause data corruption
;;; problems when the source and compilations are recycled (there would be
;;; an attempt to recycle the same string twice).

;;; First pass compilation functions typically return
;;; expression-for-compilation structures.  The
;;; compiled-specific-expression of the expression-for-compilation can
;;; be a number, a symbol, an expression-for-compilation, or a list.  If
;;; it is a list, the car is an operator and the succeeding elements can
;;; be numbers, symbols, expression-for-compilation structures, or more
;;; lists of this form.

;; See notes (in design notebook, 8/19/87) on new first pass.

;;; Overview of first pass compilation 

;;; compile-1-expression-top
;;;   compile1-forward-reference-for-designations
;;;     compile1-designation
;;;       compile-forward-reference-path
;;;         compile-forward-reference-path
;;;     compile1-forward-reference-for-designations
;;;   compile1-designations-for-focus
;;;     combine-inverse-references-1
;;;     check-for-inverse-references
;;;       check-for-inverse-references-rec
;;;         better-reference-provided-by-inverse-reference?
;;;           better-reference-provided-by-inverse-reference-rec?
;;;             build-inverse-reference-path-for-sub-expression
;;;               build-inverse-reference-path-for-sub-expression-rec
;;;             add-new-inverse-references
;;;               build-inverse-reference-path
;;;               build-inverse-reference-path-rec
;;;   combine-references-for-expression
;;;     combine-reference-finding-paths
;;;       combine-reference-finding-paths-1
;;;         copy-reference-structure
;;;         combine-reference-finding-paths-rec
;;;           prune-and-combine-new-references-for-focus
;;;             prune-and-combine-new-references-for-focus-rec


(declare-forward-reference lookup-function-template function)
(declare-forward-reference lookup-action-template function)


;;; Compile1-expression-top is the top level function for the first pass of the
;;; compilation.  It will first compile the forward references for all 
;;; designations.  Then, if focus-name is not nil, the relaxation technique
;;; will be used to find all inverse references.  Finally, reference structures
;;; for all expressions will be generated.  Note that all forward and inverse
;;; references are found for designations before the references are combined
;;; for the expressions enclosing the designations.

;;; Compile1-expression-top takes the antecedent-expression and consequent-expression
;;; when compiling rules.  When compiling just an expression, consequent-expression?
;;; is nil and antecedent-expression is the expression.

;;; Compile1-expression-top first does a forward compile (without focus) to
;;; set up the forward reference trees which may then be mutated if there
;;; is a focus.  The forward compile is done by calling 
;;; compile1-forward-reference-for-designations.  This also checks if there
;;; may be multiple compilations (when compiling rules with focus), and if so, 
;;; sets up focus-local-names-for-focus-role-name. 
;;; If there are multiple compilations, then
;;; compile1-expression-top will set the focus name to the first of the
;;; focus local names in focus-local-names-for-focus-role-name and proceed with
;;; the compile for focus.  When done, it will return (among other things) a
;;; continuation which is an index to the next local name on 
;;; focus-local-names-for-focus-role-name.  Compile-rule will then call
;;; compile1-expression-top with this continuation.

;;; When compiling expressions (rather than rules), there may be more than
;;; one focus role name (the focus-names argument may be a list with more than
;;; one element).  With expressions, only one compilation is performed
;;; and there are never any inverse references.  Therefore, multiple compilations
;;; will not occur and focus-local-names are not computed for each 
;;; focus-role-name.  The focus names used will be the focus names passed in
;;; in the argument (the focus role names).  In cases where a focus-role-name
;;; specifies more than one runtime item, the compiler generates local names
;;; to replace the role name for all but the first occurrence;  the first
;;; occurrence will use the original role name.  Thus, the compile with focus
;;; using the focus role names will compile correctly.
;; (see also example of function definition f1 in agh>local-names-compile-test.kb.)

;;; When compiling a generic-formula or generic-simulation-formula, the
;;; left side of the formula is passed in as an expression (see also 
;;; documentation for compile-expression).  This left side is compiled along
;;; with the right side so that wrapper-references-for-left-side-of-formula?
;;; can be set.  This allows 
;;; compile2-top-level-expression-and-insert to wrap
;;; a "let" binding form around the compiled form so that the attribute on
;;; the left side of the formula can be referred to directly in the right
;;; side. (see also compile-expression, 
;;; insert-wrapper-references-for-left-side-of-formula).  

;;; When all compilation of a rule is finished, compile1-expression-top performs a number
;;; of focus checks (focus checks are not performed when compiling expressions).  
;;; First, it checks for fatal focus errors by calling
;;; fatal-focus-error?.  If there is a fatal focus error, fatal-focus-error-info?
;;; is set to information regarding the error and compile1-expression-top
;;; returns.  If there is no fatal focus error, a check for too narrow focus
;;; is performed.  If focus is not too narrow, compile1-expression-top returns
;;; without any errors.  If it is too narrow, the inverse reference path is
;;; checked to see if a wider focus is possible.  If a wider focus is not possible
;;; the flag focus-too-narrow? is set and compile1-expression-top returns.
;;; Compile-rule will return the general compilation if this flag is set.
;;; If a wider focus is possible, compile1-expression-top loops 
;;; back to the start and tries the entire first pass compilation again with
;;; the wider focus name.  This loop continues until either the focus is not
;;; too narrow, or wider focus is not possible.  

;;; Note that focus widening only occurs when compiling rules, never when compiling
;;; expressions.  This is because expressions never have inverse references.

;;; Note that the fatal focus error check need only be performed the first time
;;; through the loop.

;;; Note that the original inverse reference path is
;;; retained as pattern-checking-inverse-references
;;; because the focus object is bound to the original focus name on
;;; the alist and the wider focus object must be found by inverse reference.
;;; For this reason also, the original focus-local-name is returned.

;;; Issues of fatal focus errors and too narrow focus are discussed in detail
;;; in agh>generic-compiler-report.text.  See also agh>bad-focus-compile-test.kb
;;; and agh>too-narrow-focus-runtime-test.kb for examples.

;;; Function definitions are a bit different from other kinds of things that 
;;; get compiled.  First, they are the only things that can be compiled with
;;; more than one focus name.  Note however that unlike rules, the focus names
;;; are not really focus names but rather externally provided names that can
;;; be referred to.  Thus, if a function is being compiled, focus names is
;;; copied into list-of-known-names.
;;; This is to make sure that if one of the
;;; focus names is used again in the function to designate a new item, that 
;;; ambiguous references are caught.

;;; Designations from explicit iteration forms are forward compiled by
;;; compile1-forward-explicit-iteration-designations.  They are handled
;;; exactly like designations from the body for purposes of compiling with
;;; focus (see compile1-designations-for-focus).  The reference paths for
;;; these designations are combined using
;;; combine-reference-paths-for-explicit-iteration-designations and
;;; combine-explicit-iteration-and-antecedent-reference-trees which are similar
;;; to the other combine functions.

(defun compile1-expression-top 
       (antecedent-expression consequent-expression? 
	left-side-of-formula? focus-names continuation?)
  (loop with wider-focus-names-to-try? = nil
	with chaining-category? = nil
	with focus-local-name? = nil
	as first-time? = t then nil
	do

    (setq list-of-known-names nil
	  names-used-for-more-than-one-item nil
	  focus-local-names-for-focus-role-name nil
	  local-name-errors nil
	  top-level-reference-tree nil)
    ;; Have to reset these special variables for each try.
    ;; Consider just rebinding them instead.  
    ;; Note that pattern-checking-inverse-references is not reset since
    ;; the value from the first try must be used.

    (let* ((need-to-compile-with-focus?
	     (not (and compiling-expression-p
		       (not left-side-of-formula?))))
	   (list-of-known-names
	     (if (not need-to-compile-with-focus?)
		 (copy-list-using-phrase-conses focus-names))))
      ;; Need to compile with focus only if compiling a generic rule
      ;; or formula; not if compiling a function definition or 
      ;; specific simulation formula.

      (when compiling-rule-p
	(compile1-forward-explicit-iteration-designations))
      
      (let ((forward-reference-compiled-left-side-of-formula?
	      (if left-side-of-formula?
		  (compile1-forward-reference-for-designations
		    left-side-of-formula?)))
	    (forward-reference-compiled-antecedent-expression
	      (let ((compiling-antecedent-p compiling-rule-p))
		(compile1-forward-reference-for-designations antecedent-expression)))
	    (forward-reference-compiled-consequent-expression
	      (if consequent-expression?
		  (compile-consequent 
		    consequent-expression?
		    'compile1-forward-reference-for-designations)))
	    (combined-inverse-and-antecedent-reference-tree nil)
	    (combined-left-side-and-right-side-tree nil)
	    (combined-explicit-iteration-and-antecedent-reference-tree nil)
	    (inverse-references-for-designations nil))

	(when (and (null (cdr focus-names))
		   (car focus-names)
		   first-time?)
	  (cond
	    (compiling-rule-p
	     ;; When compiling a rule, there is only one focus name.
	     ;; If that focus name is not nil, then not doing general compilation.
	     (cond 
	       (continuation?
		;; If continuation, get next local name for focus.
		(let* ((focus-local-name-entry
			 (nth continuation?
			      focus-local-names-for-focus-role-name))
		       (next-focus-local-name-entry-continuation-index?
			 (+f continuation? 1))
		       (next-focus-local-name-entry
			 (nth next-focus-local-name-entry-continuation-index?
			      focus-local-names-for-focus-role-name)))
		  (setq focus-names
			(phrase-list 
			  (car focus-local-name-entry))
			chaining-category?
			(cdr focus-local-name-entry))
		  (setq continuation?
			(if next-focus-local-name-entry
			    next-focus-local-name-entry-continuation-index?))))
	       (t
		(setq focus-names
		      (phrase-list 
			(caar focus-local-names-for-focus-role-name))
		      chaining-category?
		      (cdar focus-local-names-for-focus-role-name))
		(setq continuation?
		      (if (second focus-local-names-for-focus-role-name)
			  1))))
	     (setq focus-local-name? (car focus-names)))
	    (left-side-of-formula?
	     ;; if compiling a generic formula or a generic simulation formula
	     (setq focus-names
		   (phrase-list 
		     (caar focus-local-names-for-focus-role-name)))
	     ;; Note that only the first entry in 
	     ;; focus-local-names-for-focus-role-name is used since it
	     ;; corresponds to the instance on the left side of the formula.
	     ;; This is the only one that should be focus compiled;  there are
	     ;; no multiple compilations with formulas.
	     )))

	;; relaxation technique
	(if (and need-to-compile-with-focus?
		 (car focus-names))
	    (setq inverse-references-for-designations
		  (compile1-designations-for-focus
		    forward-reference-compiled-left-side-of-formula?
		    forward-reference-compiled-antecedent-expression
		    forward-reference-compiled-consequent-expression
		    (or wider-focus-names-to-try?
			focus-names))))

	;; generate reference structures and set names-provided slots for all expressions
	(combine-references-for-expression
	  forward-reference-compiled-antecedent-expression)

	(unless (expression-for-compilation-p 
		  forward-reference-compiled-antecedent-expression)
	  (if designations-from-explicit-iteration-forms
	      (setq combined-explicit-iteration-and-antecedent-reference-tree
		    (combine-reference-paths-for-explicit-iteration-designations)))
	  (if inverse-references-for-designations
	      ;; This test should always be true for formulas
	      (setq combined-left-side-and-right-side-tree
		    (combine-inverse-reference-paths-with-local-reference-paths
		      inverse-references-for-designations
		      combined-left-side-and-right-side-tree)))
	  (setq combined-inverse-and-antecedent-reference-tree
		combined-explicit-iteration-and-antecedent-reference-tree))
	
	(when (expression-for-compilation-p 
		forward-reference-compiled-antecedent-expression)
	  
	  ;; Combine explicit iteration and antecedent references.
	  ;; Copies are made so original reference trees are left in tact.
	  (if designations-from-explicit-iteration-forms
		(setq combined-explicit-iteration-and-antecedent-reference-tree
		      (combine-explicit-iteration-and-antecedent-reference-trees
			(combine-reference-paths-for-explicit-iteration-designations)
			(local-reference-finding-paths
			  forward-reference-compiled-antecedent-expression)))
		(setq combined-explicit-iteration-and-antecedent-reference-tree
		      (local-reference-finding-paths
			forward-reference-compiled-antecedent-expression)))
	  
	  (when forward-reference-compiled-left-side-of-formula?
	    (setq combined-left-side-and-right-side-tree
		  (combine-left-side-tree-with-right-side-tree
		    (local-reference-finding-paths
		      forward-reference-compiled-left-side-of-formula?)
		    (local-reference-finding-paths
		      forward-reference-compiled-antecedent-expression)))
	    (if (inverse-references forward-reference-compiled-antecedent-expression)
		;; This test should always be true for formulas
		(setq combined-left-side-and-right-side-tree
		      (combine-inverse-reference-paths-with-local-reference-paths
			(inverse-references 
			  forward-reference-compiled-antecedent-expression)
			combined-left-side-and-right-side-tree)))
	    (setq wrapper-references-for-left-side-of-formula?
		  (car (local-reference-finding-paths
			 forward-reference-compiled-left-side-of-formula?))))
	  
	  (if inverse-references-for-designations
	      (setq combined-inverse-and-antecedent-reference-tree
		    (combine-inverse-reference-paths-with-local-reference-paths
		      inverse-references-for-designations
		      combined-explicit-iteration-and-antecedent-reference-tree))
	      (setq combined-inverse-and-antecedent-reference-tree
		    combined-explicit-iteration-and-antecedent-reference-tree)))
	;; The inverse-references are combined with the local-reference-finding-paths
	;; since all inverse-references are wrapped around the antecedent. 
	;; This will happen for actions when the
	;; reference paths for the antecedent are combined with those for the action
	;; (by combine-references-for-antecedent-and-consequent, see below).
	;; Note that a copy is made of the inverse-references before combining so that
	;; this structure is left intact.  The result is put in 
	;; combined-inverse-and-antecedent-reference-tree so that the
	;; local-reference-finding-paths slot of
	;; forward-reference-compiled-antecedent-expression is also left intact.
	
	(if consequent-expression?
	    (combine-references-for-actions
	      forward-reference-compiled-consequent-expression))
	
	(if compiling-rule-p
	    (setq top-level-reference-tree
		  (combine-references-for-antecedent-and-consequent
		    combined-inverse-and-antecedent-reference-tree
		    forward-reference-compiled-antecedent-expression
		    forward-reference-compiled-consequent-expression))
	    ;; if compiling an expression
	    (setq top-level-reference-tree
		  (or combined-left-side-and-right-side-tree
		      (if (expression-for-compilation-p
			    forward-reference-compiled-antecedent-expression)
			  combined-explicit-iteration-and-antecedent-reference-tree))))

	;; Combine-references-for-antecedent-and-consequent returns the
	;; reference tree for the entire rule.
	
	(when (and first-time? compiling-rule-p)
	  (setq pattern-checking-inverse-references
		(car inverse-references-for-designations)))
	;; All inverse references are wrapped around the antecedent in the
	;; third pass.
	
	;; Perform focus error checks here. 
	
	(let ((return?
		(or (not compiling-rule-p)	; not compiling rule
		    (not (car focus-names))	; not compiling with focus
		    (when first-time?
		      (fatal-focus-error?
			forward-reference-compiled-antecedent-expression
			forward-reference-compiled-consequent-expression))	; fatal focus error
		    (cond
		      ((too-narrow-focus?
			 forward-reference-compiled-antecedent-expression
			 forward-reference-compiled-consequent-expression
			 inverse-references-for-designations)   ; focus too narrow
		       (let* ((root-inverse-reference-structure
				(car (inverse-references
				       forward-reference-compiled-antecedent-expression)))
			      (wider-focus-reference-structure?
				(car (reference-structures-needing-provided-local-name
				       root-inverse-reference-structure))))
			 (cond
			   ((and wider-focus-reference-structure?	; wider focus possible
				 (not (inverse-reference-structure-is-global-end? 
					wider-focus-reference-structure?)))
			    ;; Make sure that reference structure is not a global
			    ;; end reference structure.
			    (setq wider-focus-names-to-try?
				  (phrase-list 
				    (domain-name-needed
				      wider-focus-reference-structure?)))
			    nil)
			   (t
			    (setq focus-too-narrow? t)))))	; wider focus not possible
		      (t			; focus not too narrow
		       t)))))
	  
	  (if return?
	      (return
		(values forward-reference-compiled-antecedent-expression
			forward-reference-compiled-consequent-expression
			chaining-category?
			focus-local-name?
			continuation?))))))))



(defun fatal-focus-error?
       (forward-reference-compiled-antecedent-expression
	forward-reference-compiled-consequent-expression)
  forward-reference-compiled-antecedent-expression
  forward-reference-compiled-consequent-expression
  fatal-focus-error-info?)

;; The actual check is done by check-for-illegal-focus called by
;; better-reference-provided-by-inverse-reference-rec? when the designations
;; are compiled for focus.  If there is a problem, the special variable
;; fatal-focus-error-info? will be set appropriately.


;;; Too-narrow-focus? is only called when compiling rules with focus.

(defun too-narrow-focus?
    (forward-reference-compiled-antecedent-expression
      forward-reference-compiled-consequent-expression
      inverse-references-for-designations)
  (declare (ignore forward-reference-compiled-consequent-expression))
  (or 
    (rule-focus-inside-rule-body?)
    (or (rule-focus-inside-every-quantifier?
	  (car inverse-references-for-designations))
	(rule-focus-inside-illegal-expression?
	  forward-reference-compiled-antecedent-expression))))

;; Note that it is not necessary to check the consequent for focus
;; inside "not" expressions since any focus in an expression in an
;; action is a fatal error and is caught by fatal-focus-error? 
;; resulting in a complete rejection of the rule.


;;; Rule-focus-inside-rule-body? checks if the focus is inside the body
;;; of the rule rather than the "context".  Since iteration is done
;;; only in the context and not the body, focusing on bindings in the
;;; context (of the general compilation) produces all "instances" of
;;; the rule.  Focusing on something in the body within the context 
;;; does not produce any new rule instances and is therefore 
;;; undesireable.  Furthermore, since only the body for the general
;;; compilation is kept for the rule, and since focusing within
;;; this body would produce a different body, focusing within the body
;;; is not allowed.  Therefore, the focus is widened until it is on
;;; one of the context bindings of the general compilation.

;;; Focus inside the rule body is easily detected ... 

(defun rule-focus-inside-rule-body? ()
  (let* ((focus-reference (car top-level-reference-tree))
	 (next-inverse-reference?
	   ;; If focus-reference is not an reference-structure, then it doesn't
	   ;; make sense to try to get the reference-structures-needing-
	   ;; provided-local-name.  In fact, if it is nil, then that would be a
	   ;; segmentation violation and a G2 abort.  So, I'm adding an extra
	   ;; check here.  - jv, 2/2/99
	   (and (reference-structure-p focus-reference)
		(car (reference-structures-needing-provided-local-name focus-reference)))))
    ;; The focus reference is always the first reference structure of the top level
    ;; tree due to the way reference trees are combined (see compile1-expression-top).
    ;; The next inverse reference is the one actually analyzed since needing trees
    ;; hang off this rather than the focus reference.
    (when (and next-inverse-reference?
	       (eq (forward-reference-quantifier-for-inverse-references
		     next-inverse-reference?)
		   'the)
	       (not (focus-reference-provides-binding-for-iteration?
		      next-inverse-reference?)))
      ;; If focus is in body, must widen focus.
      (setq number-of-no-binds (+f number-of-no-binds 1))
      ;; Number of no-binds is also the number of times focus was widened 
      ;; for this reason.
      t)))

;; Once rule-focus-inside-rule-body? returns nil, it will always return
;; nil thereafter for this focus compilation, even if the focus is widened
;; for other reasons.  Rule-focus-inside-rule-body? is checked
;; first in too-narrow-focus? so that incrementing number-of-no-binds
;; will not be skipped (due to focus widening due to some other reason).


(defun focus-reference-provides-binding-for-iteration? (reference-structure)
  (loop for needing-reference-structure
	    in (reference-structures-needing-provided-local-name 
		 reference-structure)
	thereis (and (not (eq (quantifier needing-reference-structure) 
			      'every-inverse))
		     (reference-tree-has-iteration? 
		       needing-reference-structure))))


;;; Rule-focus-inside-every-quantifier? will return t if there is a focus 
;;; "within" an "every" quantifier (within the scope of names provided by
;;; the "every" quantifier).

(defun rule-focus-inside-every-quantifier? (root-inverse-reference-structure)
  (loop as reference-structure 
	   = root-inverse-reference-structure
	   then next-reference-structure
	until (null reference-structure)
	as next-reference-structure
	   = (car (reference-structures-needing-provided-local-name
		    reference-structure))
	thereis
	  (if next-reference-structure
	      (eq (forward-reference-quantifier-for-inverse-references
		    next-reference-structure)
		  'every))))


;;; Rule-focus-inside-illegal-expression? returns t if there is a focus inside a
;;; an expression where there shouldn't be.

(defun rule-focus-inside-illegal-expression? (expression)
  (let ((compiled-specific-expression-to-investigate?
	  (when (expression-for-compilation-p expression)
	    (compiled-specific-expression expression))))
    (when (and compiled-specific-expression-to-investigate?
	       (consp compiled-specific-expression-to-investigate?))
      (cond
	((operator-to-check-for-illegal-focus-p 
	   (car compiled-specific-expression-to-investigate?))
	 (loop for designation in (designations-for-expression expression)
	       as root-reference-structure?
		  = (car (local-reference-finding-paths designation))
	       as providing-reference-structure?
		  = (if root-reference-structure?
			(reference-structure-providing-needed-domain-name
			  root-reference-structure?))
	       thereis (and providing-reference-structure?
			    (not (eq (domain-name-needed 
				       providing-reference-structure?)
				     needed-domain)))))
	(t (loop for sub-expression 
		     in (cdr compiled-specific-expression-to-investigate?)
		 thereis (rule-focus-inside-illegal-expression?
			   sub-expression)))))))

;; This checks if the reference path of the designation has been "broken"
;; into an inverse and forward part by 
;; better-reference-provided-by-inverse-reference?.  If it has, the
;; reference-structure-providing-needed-domain-name slot of the root reference
;; structure for the designation will still point to the old providing reference
;; structure.  If this old providing reference structure is not a "needed" stub,
;; then focus is inside the expression.

;; Note that since "any" is not allowed inside expressions of quantifiers and
;; aggregators, these expressions are always part of the body of the rule.
;; Consequently, focus within such an expression will be caught by
;; rule-focus-inside-rule-body? before rule-focus-inside-illegal-expression?
;; is even called.  Thus, for quantifiers and aggregators, 
;; rule-focus-inside-illegal-expression? is actually only needed to check for
;; focus in the scope of the quantifier or aggregator.  Consider implementing
;; an any-inverse-no-bind (similar to the-inverse-no-bind) for this case!


(defun operator-to-check-for-illegal-focus-p (operator)
  (or (eq operator 'not)
      (quantifier-or-aggregator-p operator)))

;; Operator-to-check-for-illegal-focus-p is currently identical to 
;; Operator-to-check-for-illegal-reference-p.


;;; Compile1-forward-explicit-iteration-designations converts the list of 
;;; uncompiled designations in source-designations-from-explicit-iteration-forms to a
;;; list of expression-for-compilation structures by calling compile1-designation
;;; for each one.  Thus, designations from explicit iteration forms are 
;;; forward compiled exactly the same way as designations for the body and
;;; forward reference paths are known after this function is called.

(defun compile1-forward-explicit-iteration-designations ()
  (loop with forward-compiled-designations = nil
	for uncompiled-designation 
	    in source-designations-from-explicit-iteration-forms
	as compiled-designation = (compile1-designation uncompiled-designation)
	do
    (setq forward-compiled-designations
	  (nconc forward-compiled-designations (phrase-list compiled-designation)))
	finally
	  (setq designations-from-explicit-iteration-forms 
		forward-compiled-designations)))
    

;;; Compile1-forward-reference-for-designations is a recursive function which
;;; searches out designations and compiles forward reference structures for
;;; each one.  The designations-for-expression slot of each 
;;; expression-for-compilation will be updated as well.  Also, expressions 
;;; for compilation are generated for each expression.  
;;; The compiled specific expression is formed by consing the operator
;;; with the results of invoking compile1-forward-reference-for-designations
;;; for each sub-expression.  This function can
;;; return a number, a symbol, or an expression-for-compilation.
;;; Note that if expression is just a symbol, it is always considered a designation
;;; and compiled using compile1-designation.  This includes the degenerate case
;;; of the top level expression (of the antecedent of a rule or the right side
;;; of a generic formula) being just a symbol.  It is necessary in these cases
;;; to make an expression-for-compilation for the symbol rather than just
;;; returning the symbol so that inverse references can be wrapped around the
;;; antecedent. 

;;; Note that compile1-forward-reference-for-designations syntactically 
;;; filters non-designation symbols.  These are not compiled as designations
;;; but rather are simply passed through all three passes.  These, of course,
;;; include operator symbols.

(defun compile1-forward-reference-for-designations (expression)
  (cond
    ((phrase-number-p expression) expression)
    ((symbolp expression)
     (compile1-designation expression))
    ;; mhd & jh, 2/1/93.  The copy-for-phrase call is necessary to prevent a
    ;; text-string leak when the expression is copied.  This bug has been
    ;; present since 1.11B, but was not important until compilation could happen
    ;; under program control, as with the "change the text of" action.
    ((text-string-p expression)
     (copy-for-phrase expression))
    ((phrase-sequence-p expression)
     expression)
    ((phrase-structure-p expression)
     expression)
    ;; test operators - quantifier or other
    ((consp expression)     
     (let ((operator (car expression))
	   (operator-1 (cdr expression)))
       (cond
	 ((eq operator 'quote)
	  expression)
	 ((phrase-number-p operator)  ; if constant of form (number . units)  
	  expression)
	 ((designation-operator-or-giver-of-value-p operator)
	  (compile1-designation expression))
	 ((quantifier-or-aggregator-p operator)
	  (compile1-quantifier-or-aggregator expression))
	 ((memq operator 
		'(create create-by-cloning create-connection create-explanation))
	  (compile1-create-action expression))
	 ((eq operator 'call-assignment-action)
	  (compile1-call-assignment-action expression))
         ((eq operator-1 'SEQUENCE)
	  expression)
         ((eq operator-1 'STRUCTURE)
	  expression)
	 (t
	  (compile1-expression-according-to-template expression)))))))

;; Note that function templates are not currently used for quantifiers and
;; aggregators.  These are special cased.  Consider using templates.



(defun compile1-expression-according-to-template (expression)
  (let* ((expression-for-compilation 
	   (make-compilation-reclaimable-expression-for-compilation))
	 (operator (car expression))
	 (template? (or (lookup-function-template operator)
			(lookup-action-template operator))))
    (setf (compiled-specific-expression expression-for-compilation)
	  (phrase-cons
	    ;; OK this is a terrible thing to do and I admit it
	    ;; but if the "operator" is nil. it will get removed
	    ;; by later stages of compilation
	    ;; So I wire in some of the tests in
	    ;; compile1-sub-expressions-according-to-template
	    ;; to insert the nil-indicator instead
	    (if operator
		operator
		(unless (and template?
			     (memq template? '(other sub-expression
					       show-or-hide-argument-list
					       color-changes)))
		  nil-indicator))
	    (compile1-sub-expressions-according-to-template
	      expression template? expression-for-compilation)))
    expression-for-compilation))


(defun compile1-sub-expressions-according-to-template
       (expression template? expression-for-compilation)
  (loop with rest-of-template = (cdr template?)
	with template-symbol 
	  = (if template? (car rest-of-template) 'expression)
	with compiled-sub-expression
	with rest-of-sub-expressions = (cdr expression)
	as sub-expression = (car rest-of-sub-expressions)
	until (null rest-of-sub-expressions)
	do
    (setq compiled-sub-expression 
	  (case template-symbol
	    (other
	     (if (null sub-expression)
		 nil-indicator
		 sub-expression))
	    ((expression-list designation-list)
	     (compile1-forward-reference-for-designations 
	       (phrase-cons expression-list-indicator sub-expression)))
	    (color-changes
	     (prog1
	       (compile1-color-changes rest-of-sub-expressions)
	       (setq rest-of-sub-expressions nil)))
	    (create-connection-spec
	     (compile1-create-connection-spec sub-expression))
	    (show-or-hide-argument-list
	     (compile1-show-or-hide-argument sub-expression))
	    (t
	     ;; designation, expression, message-designation, message-text,
	     ;; inform-option, create actions (create, create-by-cloning,
	     ;; create-connection, create-explanation).
	     (if (null sub-expression)
		 nil-indicator
		 (compile1-forward-reference-for-designations
		   sub-expression)))))
	   
    (nconc-designations-from-sub-expression
      compiled-sub-expression expression-for-compilation)

    (when template?
      (if (symbolp (cdr rest-of-template))  ; if dotted list template
	  (setq template-symbol (cdr rest-of-template))
	  (setq rest-of-template (cdr rest-of-template)
		template-symbol (car rest-of-template))))
    (setq rest-of-sub-expressions (cdr rest-of-sub-expressions))

	collect compiled-sub-expression using phrase-cons))

;; Note that for the template categories expression-list and color-changes
;; the form is converted to expression syntax and compiled in the first
;; and second passes like any other expression.  It is converted back to
;; the correct form specified by the template in the third pass.  This
;; greatly simplifies the first and second passes and reduces the amount
;; of special case code for non-default templates.

;; If template? is nil, template-symbol is always 'expression and every 
;; sub-expression is compiled by compile1-forward-reference-for-designations.

;; Note that it is assumed that any forms in the expression conform to
;; the template.  Thus, rest-of-template should never be nil in the 
;; above loop.




(defun compile1-color-changes (color-changes)
  (loop for (region-expression . color-expression) in color-changes
	collect (phrase-list 
		  color-change-indicator region-expression color-expression)
	  into modified-color-changes
			       using phrase-cons
	finally
	  (return
	    (compile1-forward-reference-for-designations 
	      (phrase-cons color-changes-indicator modified-color-changes)))))



(defun compile1-show-or-hide-argument (expression)
  (let ((operator (car expression)))
    (if (eq operator 'in)
	(compile1-forward-reference-for-designations 
	  expression)
	expression)))


;;; The function `substitute-nil-indicator' is used to splice a nil-indicator
;;; into list structure wherever a nil is found.

(defun-void substitute-nil-indicator (clause)
  (when (and clause (listp clause))
    (loop for tail on clause
	  do
      (when (null (car tail))
	(setf (car tail) nil-indicator)))))

;;; The function `compile1-create-connection-spec' copies and returns the
;;; connection-spec argument, substituting NIL-INDICATOR's for NIL's.  This is
;;; needed so that the NIL's are not removed during compilation.  Note that the
;;; NIL's will be added back, during the 3rd compilation pass (compile3).

;;; This function must be called from within a PHRASE-CONS area!
;; Is there some reason this doesn't simply walk the tree substituting
;; nil-indicators where apropriate?  If it's for efficiency, it's a pretty poor
;; choice since if the grammar is changed or added for create-connection, this must
;; be kept up to date.  STRONGLY consider rewriting to just do the NIL
;; substitution. As it is I just had to rewrite it to fix bug HQ-3310993 which
;; was letting the NILs through in LOCATED-AT clauses, which in the presence of a
;; local-var, was causing an incorrect compilation to happen. -dkuznick, 5/4/00

;;; The possible connection specifiers (the maximum number 
;;; of NILs possible are indicated) are:
;;; 
;;; (CONNECTED-BETWEEN (obj1 (LOCATED-AT nil nil 'obj1-port))
;;;                    (obj2 (LOCATED-AT nil nil 'obj2-port))
;;;                    (nil nil vlist))
;;;
;;; (CONNECTED-TO (obj (LOCATED-AT nil nil 'obj-port))
;;;               (nil nil vlist))
;;;
;;; All of the NILs in the above are supposed to be replaced 
;;; by NIL-INDICATORs. - jpg 10/23/01

(defun-simple compile1-create-connection-spec (connection-spec)
  (let ((new-connection-spec (copy-tree-using-phrase-conses connection-spec)))
    (when (and new-connection-spec
	       (memq (first new-connection-spec)
		     '(connected-to connected-between)))
      (gensym-dstruct-bind ((creation-specifier (nil end-position-specifier)
					       . rest-of-clauses)
			   new-connection-spec)
	(substitute-nil-indicator end-position-specifier)
	(if (eq creation-specifier 'connected-to)
	    ;; an optional vertices spec comes next
	    (substitute-nil-indicator (first rest-of-clauses))
	    ;; (first ...) was accidentally omitted from the above line.
	    ;; Put in on 10/23/01. - jpg
	    
	    ;; another end-position-specifier comes next optionally
	    ;; followed by vertices
	    (gensym-dstruct-bind (((nil end-position-specifier) . vertices?)
				 rest-of-clauses)
	      (substitute-nil-indicator end-position-specifier)
	      (substitute-nil-indicator (first vertices?))))))
  new-connection-spec))

(defun nconc-designations-from-sub-expression
       (compiled-sub-expression expression-for-compilation)
  (if (expression-for-compilation-p compiled-sub-expression)
      (setf (designations-for-expression expression-for-compilation)
	    (nconc (designations-for-expression expression-for-compilation)
		   (copy-list-using-phrase-conses
		     (designations-for-expression compiled-sub-expression))))))


(defun compile1-quantifier-or-aggregator (expression)
  (let* ((expression-for-compilation 
	   (make-compilation-reclaimable-expression-for-compilation))
	 (operator (first expression))
	 (aggregator-scope (second expression))
	 (aggregator-expression (third expression))
	 (modified-aggregator-scope
	   (phrase-cons 'quantifier aggregator-scope))
	 (local-name (get-name-provided-by-role
		       (second modified-aggregator-scope)))
	 (compiled-aggregator-scope
	   (compile1-designation modified-aggregator-scope))
	 (compiled-aggregator-expression
	   (compile1-forward-reference-for-designations aggregator-expression)))
    (nconc-designations-from-sub-expression
      compiled-aggregator-scope expression-for-compilation)
    (nconc-designations-from-sub-expression
      compiled-aggregator-expression expression-for-compilation)
    (setf (compiled-specific-expression expression-for-compilation)
	  (phrase-list 
	    operator compiled-aggregator-scope compiled-aggregator-expression))
    (when (and (eq operator 'there-exists-literal) local-name)
      (add-to-local-names-not-associated-with-roles local-name))
    expression-for-compilation))

;; The aggregator phrase is modified to make it look like a designation so that it
;; can be compiled using compile1-designation.  Note that the designation operator
;; is 'quantifier.  'Any can not be used because
;; reference-structure-provides-binding-for-iteration?, which is called by
;; compile2-name and which analyzes the reference tree would think that there is
;; iteration going on here.  This would cause wrong bindings to go into the
;; context.  'The can not be used because unknown-references?  would think that
;; there is an unknown reference in certain cases.  Therefore, the dummy symbol
;; 'quantifier is used.  Note also that
;; forward-reference-quantifier-for-inverse-references of a reference structure
;; could be set to 'quantifier.  However,
;; generate-inverse-context-from-inverse-reference-path will compile this as
;; any-inverse to indicate that the forward reference does not have to be unique.

;; The there-exists-literal aggregator is treated specially in that it is the only
;; quantifier or aggregator whose local name can be used outside of the
;; expression.



(defun compile1-create-action (expression)
  (prog1
    (compile1-expression-according-to-template expression)
    (let ((local-name-for-create-action? 
	    (if (memq (car expression) '(create-connection create-by-cloning))
		(fourth expression)
		(third expression))))
      (when local-name-for-create-action?
	(add-to-local-names-not-associated-with-roles
	  local-name-for-create-action?)))))


(defun add-to-local-names-not-associated-with-roles (local-name)
  (setq local-names-not-associated-with-roles
	(phrase-cons local-name local-names-not-associated-with-roles)))


(defun compile1-call-assignment-action (expression)
  (prog1
    (compile1-expression-according-to-template expression)
    (loop for local-name in (second expression)
	  do
      (add-to-local-names-not-associated-with-roles
	  local-name))))


;;; Compile1-designation will always return an 
;;; expression-for-compilation structure.  The compiled-specific-expression
;;; of the expression-for-compilation will be a name and the local
;;; reference path will be a reference structure for this name.
;;; The local reference path is found by compile-forward-reference-path.
;;; A "designation" typically refers to the contents of an 
;;; attribute slot, usually a constant or a variable.  When datum-evaluated
;;; this produces a value.
;;; Note that expression may be just a symbol.  In this case, the 
;;; compiled-specific-expression of the expression-for-compilation is the
;;; symbol.

(defun compile1-designation (expression)
  (let* ((expression-for-compilation
	   (make-compilation-reclaimable-expression-for-compilation))
	 (local-reference-path
	   (if (symbolp expression)
	       (compile-forward-reference-path-for-symbol expression)
	       (compile-forward-reference-path expression nil))))
    (phrase-push local-reference-path
		 (local-reference-finding-paths expression-for-compilation))
    (setf (compiled-specific-expression expression-for-compilation)
	  (if (symbolp expression)
	      expression
	      (find-target-name-of-reference-path
		local-reference-path)))
    (setf (designations-for-expression expression-for-compilation)
	  (phrase-list expression-for-compilation))
    (combine-designation-with-embedded-expression-if-appropriate
      expression-for-compilation local-reference-path)))

(defun combine-designation-with-embedded-expression-if-appropriate
       (expression-for-compilation local-reference-path)
  (loop as next-rs?
	   = local-reference-path 
	   then (car (reference-structures-needing-provided-local-name
		       next-rs?))
	until (null next-rs?)
	as embedded-expression? = (embedded-expression? next-rs?)
	do
    (when embedded-expression?
      (nconc-designations-from-sub-expression
	embedded-expression? expression-for-compilation)))
  expression-for-compilation)

;; Note that when a designation has an embedded expression, it can have more than
;; one designation in its designations-for-expression slot (due to the call to
;; nconc-designations-from-sub-expression).  Normally (without embedded
;; expressions) the designations-for-expression slot of a designation contains
;; only the designation itself.

;; Local-reference-path is a path, not a tree.



;;; The local name found by find-target-name-of-reference-path may be a 
;;; compiler generated local name.  It is for this reason that 
;;; find-target-name-provided-by-designation, which looks only at user
;;; specified names in the source expression, can't be used here instead.

(defun find-target-name-of-reference-path (reference-structure)
  (if (not (reference-structures-needing-provided-local-name
	     reference-structure))
      (local-name-provided reference-structure)
      (find-target-name-of-reference-path
	(car (reference-structures-needing-provided-local-name
	       reference-structure)))))


;;; Expression-for-compilation-designation-p tests whether an expression-for-compilation
;;; is a designation.  

(defun expression-for-compilation-designation-p (expression-for-compilation)
  (symbolp (compiled-specific-expression expression-for-compilation)))


;;; `Compile-forward-reference-path' takes a designation expression and a needing
;;; reference-structure (which may be nil) as arguments, and returns a
;;; reference-structure which is the anchor reference structure
;;; corresponding to the domain name needed externally.   (not the target
;;; reference structure) for the designation expression. 
;;; (See specs in grammar1 and compile1 on form of designations)
 
;;; The action of compile-forward-reference-path is best seen by example.
;;; Suppose the expression is:
;;;      (the a (any b (any c)))
;;; The reference path for this expression produced by 
;;; compile-forward-reference-path will be
;;;      (global any c)---(c any b)---(b the a)
;;; Reference structures are represented here in the form
;;; (needed-name quantifier provided-name).  The leftmost reference
;;; structure is the anchor and the provided-name of the 
;;; rightmost reference structure is the target provided name.

;;; The provided name specified in the source will be either the role name
;;; or a local name specified explicitly in the source expression.
;;; If this name is already being used to specify an item at runtime
;;; (if the name is on the list of known names) and the 
;;; providing-reference-structure is not a root reference structure
;;; that gets its reference from a previous designation, then this name
;;; refers to a new item.  If the local name is explicitly specified,
;;; then an error is flagged.  Otherwise, a compilation-local-name
;;; is generated and used as local-name-provided instead of the 
;;; role-name in order to differentiate the different items.  The
;;; compilation-local-name is also added to names-used-for-more-than-one-item
;;; (see also documentation for this special variable).

;;; Note that compilation local names don't occur too often in final compilations.
;;; They only occur if a role name is used to specify more than one runtime item
;;; and explicit local names are not used and no subsequent expression refers to
;;; one of these items using the role name (this last condition results in an
;;; ambiguous reference error and therefore no compilation).
;;; See also reference-structure-provides-local-binding?.

;;; If the provided name specified in the source is on the list of known
;;; names and the providing reference structure is a root reference structure
;;; that gets its reference from a previous designation, then the name
;;; refers to a previously specified item.  If this name has an entry in
;;; names-used-for-more-than-one-item, an ambiguous reference
;;; error is flagged since it is unclear which of these is being referred to.  
;;; Consider the possibility of using heuristics (such as the last name
;;; in the entry of names-used-for-more-than-one-item).

;; See also notes with bug report #209 (Greg's bug in find-path).

;;; The role is always the second of the designation expression.
;;; The local name is added to focus-local-names-for-focus-role-name IF 
;;;    1: focus-name-for-rule-or-formula-compilation is non-nil, and
;;;    2: if role-name (found by atomic-naming-element-of-role)
;;;         is focus-name-for-rule-or-formula-compilation,    and
;;;    3: if a new runtime item is being specified,
;;; (see also documentation for this special variable).
 
 ;;; Note that the local name may be role-name,
;;; an explicitly specified local name, or a compiler generated local name.
;;; A name is added to focus-local-names-for-focus-role-name in the form
;;; (name . chaining-category).  Chaining-category can be 'forward, 'backward,
;;; or both.  If the name is being added while compiling the antecedent, then
;;; the chaining category is 'forward.  If it is being added while compiling the
;;; consequent, the chaining category is 'backward.  If the name is referring to
;;; a previously specified item and if the consequent is being specified, then
;;; if the name's chaining-category in focus-local-names-for-focus-role-name is
;;; forward, then it should be changed to 'both.  This test is so simple because
;;; restrictions on focus will filter out illegal focus names.

;;; Role-names-and-local-names-for-runtime-items is maintained by 
;;; compile-forward-reference-path.  It is used to replace needing references
;;; which refer to an instance bound to a local name but which use the original
;;; role name.  For example, in
;;;   "if the foo foo1 of any bar and the x of the foo ... "
;;; the reference to the foo in the second sub-expression of the "and"
;;; is replaced by foo1.  Note that this is only an issue in this rare and
;;; actually silly case.

;;; Compile-forward-reference-path also handles embedded expessions in
;;; designations.  For 3.0, the only case where this can happen is in array or
;;; list element access where the embedded expression is the index.  The embedded
;;; expression appears as (fourth expression).

;;; Compile-forward-reference-path is only called from compile1-designation, and
;;; recursively

(defun compile-forward-reference-path
       (expression
	needing-reference-structure)
  (let* ((providing-reference-structure
	   (make-compilation-reclaimable-reference-structure))
	 (role (second expression))
	 (simple-role-of-role
	   (simple-role-of-role role))
	 (role-name
	   (atomic-naming-element-of-role role))
	 (explicitly-specified-local-name?
	   (get-explicitly-specified-local-name-of-role-if-any role))
	 (source-specified-local-name-provided
	   (or explicitly-specified-local-name?
	       role-name))
	 compiler-specified-local-name-provided)
    (when (and (symbolp simple-role-of-role)
	       (unauthorized-system-slot-p simple-role-of-role))
      (setq attribute-name-errors
	    (nconc attribute-name-errors (phrase-list simple-role-of-role))))
    (if explicitly-specified-local-name?
	(add-local-name-and-role-name-to-alist
	  explicitly-specified-local-name? role-name))
    (cond 
      ((or (memq source-specified-local-name-provided list-of-known-names)
	   (and (designation-requires-previous-reference-p expression)
		(assq source-specified-local-name-provided
		      role-names-and-local-names-for-runtime-items)))
       ;; Name specifies either new item or refers to old one
       (cond
	 ((not (designation-requires-previous-reference-p expression))
	  ;; if name specifies new item
	  (cond
	    (explicitly-specified-local-name?
	     (setq local-name-errors
		   (nconc local-name-errors 
			  (phrase-list
			    (phrase-cons
			      'explicitly-specified-local-name-refers-to-more-than-one-item
			      explicitly-specified-local-name?)))))
	    (t
	     (setq compiler-specified-local-name-provided
		   (interned-compilation-local-name-symbol))
	     (add-local-name-and-role-name-to-alist
	       compiler-specified-local-name-provided role-name)
	     (add-role-name-and-local-name-to-alist-of-runtime-instances
	       role-name role-name)
	     (if (and focus-name-for-rule-or-formula-compilation
		      (eq focus-name-for-rule-or-formula-compilation
			  role-name))
		 (setq focus-local-names-for-focus-role-name
		       (nconc focus-local-names-for-focus-role-name
			      (phrase-list 
				(phrase-cons
				  compiler-specified-local-name-provided
				  (if compiling-antecedent-p
				      'forward
				      'backward))))))
	     (let ((entry-in-names-used-for-more-than-one-item?
		     (assq source-specified-local-name-provided
			   names-used-for-more-than-one-item)))
	       (if entry-in-names-used-for-more-than-one-item?
		   (nconc entry-in-names-used-for-more-than-one-item?
			  (phrase-list compiler-specified-local-name-provided))
		   (setq names-used-for-more-than-one-item
			 (nconc names-used-for-more-than-one-item
				(phrase-list
				  (phrase-list source-specified-local-name-provided
					       compiler-specified-local-name-provided)))))))))
	 (t  
	  ;; If root-reference-structure is needing, source-specified-local-name refers
	  ;; to previously specified item.  Note also that 
	  ;; source-specified-local-name-provided is role-name in this case.

	  (check-for-ambiguous-reference source-specified-local-name-provided)
	  (check-if-role-name-is-same-as-previous-local-name
	    source-specified-local-name-provided)
	  (let ((previously-declared-local-name-for-this-item?
		  (role-name-refers-to-item-declared-using-local-name?
		    source-specified-local-name-provided)))
	    (cond 
	      (previously-declared-local-name-for-this-item?
	       (setq source-specified-local-name-provided
		     previously-declared-local-name-for-this-item?)
	       (setq expression source-specified-local-name-provided))))

	  (let ((entry-in-focus-local-names-for-focus-role-name?
		  (assq source-specified-local-name-provided
			focus-local-names-for-focus-role-name)))
	    (if (and entry-in-focus-local-names-for-focus-role-name?
		     (not compiling-antecedent-p)
		     (eq (cdr entry-in-focus-local-names-for-focus-role-name?)
			 'forward))
		(setf (cdr entry-in-focus-local-names-for-focus-role-name?) 'both)))

;		(setq compiler-specified-local-name-provided
;		      (loop for rest-of-names
;				on entry-in-names-used-for-more-than-one-item?
;			    until (null (cdr rest-of-names))
;			    finally (return (car rest-of-names))))
;		(setq compiler-specified-local-name-provided
;		      source-specified-local-name-provided)))
;; see above note on heuristics to dis-ambiguate references.
	  
	  (setq compiler-specified-local-name-provided
		source-specified-local-name-provided)
	  )))
      (t   ; name definitely specifies new item
       (setq compiler-specified-local-name-provided
	     source-specified-local-name-provided)
       (add-role-name-and-local-name-to-alist-of-runtime-instances
	 role-name compiler-specified-local-name-provided)
       (when (and focus-name-for-rule-or-formula-compilation
		  (eq focus-name-for-rule-or-formula-compilation
		      role-name))
	 (setq focus-local-names-for-focus-role-name
	       (nconc focus-local-names-for-focus-role-name
		      (phrase-list 
			(phrase-cons
			  source-specified-local-name-provided
			  (if compiling-antecedent-p
			      'forward
			      'backward))))))))

    (when (not (memq compiler-specified-local-name-provided list-of-known-names))
      (setq list-of-known-names
	    (nconc list-of-known-names
		   (phrase-list compiler-specified-local-name-provided))))
    ;; This is the only logical place to add to list-of-known-names.  In order for
    ;; this to work correctly, designations must be compiled in order of 
    ;; appearance, which they are (see compile1-designation,
    ;; compile1-forward-reference-for-designations, compile1-expression-top). 
    (cond
      ((symbolp expression)
       ;; if role name has been replaced by local name
       (let ((extra-reference-structure
	       (compile-forward-reference-path-for-symbol expression)))
	 (when needing-reference-structure
	   (phrase-push needing-reference-structure
			(reference-structures-needing-provided-local-name
			  extra-reference-structure))
	   (setf (reference-structure-providing-needed-domain-name
		   needing-reference-structure)
		 extra-reference-structure)
	   (setf (domain-name-needed needing-reference-structure)
		 (local-name-provided extra-reference-structure)))
	 extra-reference-structure))
      (t
       (setf (quantifier providing-reference-structure)
	     (first expression))  
       (setf (role-and-local-name providing-reference-structure)
	     (second expression))
       (setf (local-name-provided providing-reference-structure)
	     compiler-specified-local-name-provided)
       
       (when needing-reference-structure
	 (phrase-push needing-reference-structure
		      (reference-structures-needing-provided-local-name
			providing-reference-structure))
	 (setf (reference-structure-providing-needed-domain-name
		 needing-reference-structure)
	       providing-reference-structure)
	 (setf (domain-name-needed needing-reference-structure)
	       (local-name-provided providing-reference-structure)))
       
       (cond
	 ((null (cddr expression))
	  (if (designation-requires-previous-reference-p expression)
	      (setf (domain-name-needed providing-reference-structure)
		    needed-domain)
	      (setf (domain-name-needed providing-reference-structure)
		    global-domain))
	  providing-reference-structure)
	 ((and (null (cddddr expression))
	       (symbolp (third expression)))
	  (let ((local-name-or-name-of-object
		  (third expression)))
	    (setf (domain-name-needed providing-reference-structure)
		  local-name-or-name-of-object)
	    (let ((extra-reference-structure
		    (if (symbol-used-as-local-name-p local-name-or-name-of-object)
			(make-needing-reference-structure-for-symbol 
			  local-name-or-name-of-object)
			;; If local name, set up extra reference structure just to
			;; make it look like a needing reference.

			(make-global-reference-structure-for-symbol
			  local-name-or-name-of-object))))
	      (phrase-push providing-reference-structure
			   (reference-structures-needing-provided-local-name
			     extra-reference-structure))
	      (setf (reference-structure-providing-needed-domain-name
		      providing-reference-structure)
		    extra-reference-structure)
	      (compile1-embedded-expression-if-appropriate
		extra-reference-structure (fourth expression)
		providing-reference-structure))))
	 (t 
	  (compile1-embedded-expression-if-appropriate
	    (compile-forward-reference-path (third expression)
					    providing-reference-structure)
	    (fourth expression)
	    providing-reference-structure)))))))



(defun compile1-embedded-expression-if-appropriate 
       (reference-structure-to-return embedded-expression? 
	reference-structure-to-hold-embedded-expression)
  (when embedded-expression?    
    (setf (embedded-expression? 
	    reference-structure-to-hold-embedded-expression)
	  (compile1-forward-reference-for-designations embedded-expression?))
    (setf (embedded-expression-original-parse? 
	    reference-structure-to-hold-embedded-expression)
	  (copy-tree-using-phrase-conses embedded-expression?)))
  reference-structure-to-return)



;;; Compile-forward-reference-path-for-symbol takes as argument a symbol which
;;; is either the name of a kb object or a local name previously declared.  If
;;; it is the name of a kb object, a global root reference structure is made.
;;; If it is a local name, an extra reference structure is made just to make the
;;; local name look like a needing reference (the same thing is done in
;;; compile-forward-reference-path).  In either case, the reference structure is
;;; returned as the reference path.

(defun compile-forward-reference-path-for-symbol (symbol)
  (if (symbol-used-as-local-name-p symbol)
      (make-needing-reference-structure-for-symbol symbol)
      (make-global-reference-structure-for-symbol symbol)))

(defun make-needing-reference-structure-for-symbol (symbol)
  (make-extra-reference-structure symbol needed-domain))

(defun make-global-reference-structure-for-symbol (symbol)
  (make-extra-reference-structure symbol global-domain))

(defun make-extra-reference-structure (symbol domain)
  (let ((extra-reference-structure
	  (make-compilation-reclaimable-reference-structure)))
    (setf (quantifier extra-reference-structure)
	  'the
	  (role-and-local-name extra-reference-structure)
	  symbol
	  (local-name-provided extra-reference-structure)
	  symbol
	  (domain-name-needed extra-reference-structure)
	  domain)
    extra-reference-structure))


(defun symbol-used-as-local-name-p (symbol)
  (or (assq symbol alist-of-local-names-and-role-names)
      (memq symbol local-names-not-associated-with-roles)))


(defun add-local-name-and-role-name-to-alist (local-name role-name)
  (setq alist-of-local-names-and-role-names
	(nconc alist-of-local-names-and-role-names
	       (phrase-list (phrase-cons local-name role-name)))))

(defun add-role-name-and-local-name-to-alist-of-runtime-instances
       (role-name local-name)
  (setq role-names-and-local-names-for-runtime-items
	(nconc role-names-and-local-names-for-runtime-items
	       (phrase-list (phrase-cons role-name local-name)))))


;;; Check-if-role-name-is-same-as-previous-local-name is called by 
;;; compile-forward-reference-path in cases where the root reference
;;; is to a previously declared local name.  For example,
;;;   "if the x x1 of any y and the z of the x1 ... "
;;; is caught here.  The correct way to say this is
;;;   "if the x x1 of any y and the z of x1 ..."
;;; The compiler would produce the correct compilation if this check
;;; were omitted (it would automatically replace the reference to 
;;; "the x1" with x1) but it is better to flag the error to notify the 
;;; user that something is unclear.

(defun check-if-role-name-is-same-as-previous-local-name (role-name)
  (if (assq role-name alist-of-local-names-and-role-names)
      (setq local-name-errors
	    (nconc local-name-errors
		   (phrase-list
		     (phrase-cons
		       'root-reference-role-name-same-as-previously-specified-local-name
		       role-name))))))


(defun check-for-ambiguous-reference (role-name)
  (loop with runtime-item-entries = nil
	for entry in role-names-and-local-names-for-runtime-items
	do
    (if (eq role-name (car entry))
	(setq runtime-item-entries
	      (nconc runtime-item-entries
		     (phrase-list entry))))
	finally
	  (if (cdr runtime-item-entries)  ; if more than one
	      (loop with first-instance-not-declared-using-local-name = nil
		    for entry in runtime-item-entries
		    do
		(if (eq (car entry) (cdr entry))
		    (cond
		      (first-instance-not-declared-using-local-name
		       (setq local-name-errors
			     (nconc local-name-errors
				    (phrase-list
				      (phrase-cons
					'ambiguous-reference
					role-name))))
		       (return (values)))
		      (t 
		       (setq first-instance-not-declared-using-local-name
			     entry))))
		    finally
		      (if (null first-instance-not-declared-using-local-name)
			  (setq local-name-errors
				(nconc local-name-errors
				       (phrase-list
					 (phrase-cons
					   'ambiguous-reference
					   role-name)))))))))

(defun role-name-refers-to-item-declared-using-local-name? (role-name)
  (loop with runtime-item-entries = nil
	for entry in role-names-and-local-names-for-runtime-items
	do
    (if (eq role-name (car entry))
	(setq runtime-item-entries
	      (nconc runtime-item-entries
		     (phrase-list entry))))
	finally
	  (if (and (null (cdr runtime-item-entries))  ; if only one
		   (not (eq (car (car runtime-item-entries))
			    (cdr (car runtime-item-entries)))))  ; role and local names not same
	      (return (values (cdr (car runtime-item-entries)))))))


;;; Compile1-designations-for-focus takes an expression-for-compilation
;;; and a focus-name.  The reference paths for the designations
;;; have already been found (without any focus-name).  They will
;;; now be modified using the new reference provided by the focus
;;; name.  This is best illustrated by example.

;;; Suppose the original expression is
;;;      (+ (the a (the b (the c (the d (the e)))))
;;; 	    (the f (the d)))
;;; The reference paths for the designations are
;;;      (needed the e)-(e the d)-(d the c)-(c the b)-(b the a)
;;; and
;;;      (needed the d)-(d the f)
;;; If the focus name is c, the initial inverse reference is
;;;      (focus the c)
;;; Compile-designation-for-focus will loop through the designations,
;;; calling check-for-inverse-references (see below).  This will 
;;; modify the reference paths for the sub-expressions to be
;;;      (focus the c)-(c the b)-(b the a)
;;; and
;;;      (focus the c)-(c inverse-the d)-(d the f)
;;; Also, the inverse references will now be
;;;      (focus the c)-(c inverse-the d)-(d inverse-the e)

(defvar forward-compiled-antecedent)

(defvar forward-compiled-consequent?)


(defun compile1-designations-for-focus
       (forward-reference-compiled-left-side-of-formula?
	forward-reference-compiled-antecedent-expression
	forward-reference-compiled-consequent-expression?
	focus-names)
  (let* ((designations
	   (if forward-reference-compiled-left-side-of-formula?  ; only if compiling expression
	       (get-copy-of-designations-for-expression
		 forward-reference-compiled-left-side-of-formula?
		 forward-reference-compiled-antecedent-expression)
	       (if forward-reference-compiled-consequent-expression?
		   (get-copy-of-designations-for-rule
		     forward-reference-compiled-antecedent-expression
		     forward-reference-compiled-consequent-expression?)
		   (if (expression-for-compilation-p
			 forward-reference-compiled-antecedent-expression)
		       (designations-for-expression   ; don't have to copy since not nconcing 
			 forward-reference-compiled-antecedent-expression)))))
	 (forward-compiled-antecedent
	   forward-reference-compiled-antecedent-expression)
	 (forward-compiled-consequent?
	   forward-reference-compiled-consequent-expression?)
	 (inverse-references-for-designations nil))

    (loop for focus-name in focus-names
	  as focus-reference-structure
	     = (make-compilation-reclaimable-reference-structure)
	  do
      (setf (domain-name-needed focus-reference-structure)
	    focus-name)
      (setf (local-name-provided focus-reference-structure)
	    focus-range)
      (setf (role-and-local-name focus-reference-structure)
	    focus-range)
      (setf (quantifier focus-reference-structure)
	    'every-inverse)
      (phrase-push focus-reference-structure
		   inverse-references-for-designations))

    ;; relaxation technique to find all new inverse references

    (loop do
      (let ((designation-found-to-have-inverse-reference?
	      (loop for designation in designations
		    do
		(if (check-for-inverse-references
		      designation
		      inverse-references-for-designations)
		    (return designation)))))
	(if designation-found-to-have-inverse-reference?
	    (setq designations
		  (delq designation-found-to-have-inverse-reference?
			designations 1))
	    (return (values)))))

    ;; At this point, inverse references have been found
    ;; for all designations that have them and all reference
    ;; paths for the designations have been rebuilt.

    (if (expression-for-compilation-p forward-reference-compiled-antecedent-expression)
	(setf (inverse-references forward-reference-compiled-antecedent-expression)
	      inverse-references-for-designations))
    (if forward-reference-compiled-consequent-expression?
	(set-inverse-references-for-actions
	  forward-reference-compiled-consequent-expression?
	  inverse-references-for-designations))

    ;; There should be no need to make separate copies of the inverse references.

    ;; Note that the inverse-references slot of only the top level
    ;; expression-for-compilation is set.  The inverse-references
    ;; slot of lower level expressions is not used.  This is nice
    ;; because it obviates the need to combine inverse references
    ;; as is done with the local reference paths.

    inverse-references-for-designations))


(defun get-copy-of-designations-for-rule
       (forward-reference-compiled-antecedent-expression
	forward-reference-compiled-consequent-expression)
  (nconc
    (copy-list-using-phrase-conses
      designations-from-explicit-iteration-forms)
    (if (expression-for-compilation-p
	  forward-reference-compiled-antecedent-expression)
	(copy-list-using-phrase-conses
	  (designations-for-expression 
	    forward-reference-compiled-antecedent-expression)))
    (get-copy-of-designations-for-actions
      forward-reference-compiled-consequent-expression)))

(defun get-copy-of-designations-for-expression
       (forward-reference-compiled-left-side-of-formula?
	forward-reference-compiled-antecedent-expression)
  (nconc
    (copy-list-using-phrase-conses
      (designations-for-expression
	forward-reference-compiled-left-side-of-formula?))
    (if (expression-for-compilation-p
	  forward-reference-compiled-antecedent-expression)
	(copy-list-using-phrase-conses
	  (designations-for-expression 
	    forward-reference-compiled-antecedent-expression)))))

(defun get-copy-of-designations-for-actions (action-or-actions)
  (loop for expression 
	    in (cdr action-or-actions)
	nconc
	  (copy-list-using-phrase-conses
	    (designations-for-expression expression))))

(defun set-inverse-references-for-actions
       (action-or-actions inverse-references-for-designations)
  (loop for expression 
	    in (cdr action-or-actions)
	do
    (setf (inverse-references expression)
	  inverse-references-for-designations)))


;;; Check-for-inverse-references returns the designation if an
;;; inverse reference is found, else nil.
;;; Note that check-for-inverse-references makes use of the
;;; reference structures in local-reference-finding-paths of the
;;; designation.  These are the reference paths for the 
;;; compilation without focus (without any inverse references).
;;; The function better-reference-provided-by-inverse-reference?
;;; checks if the focus and resulting inverse references provide
;;; a more precise reference.  This is best illustrated by example.

;;; Suppose the designation is 
;;;      (the a (the b (the c (the d (the e)))))
;;; The reference path will then be
;;;      (needed the e)-(e the d)-(d the c)-(c the b)-(b the a)
;;; If the focus name is "c", better-reference-provided-by-inverse-reference?
;;; (called by check-for-inverse-references-rec) will succeed and will
;;; call build-inverse-reference-path-for-sub-expression to build the
;;; new reference path for the designation:
;;;      (focus the c)-(c the b)-(b the a)
;;; Note that the reference path is built all the way back to the anchor
;;; focus reference structure.
;;; Besides building the new reference path for the designation,
;;; new inverse references have to be built.  This is done by
;;; add-new-inverse-references which calls build-inverse-reference-path
;;; resulting in
;;;      (focus the c)-(c inverse-the d)-(d inverse-the e)
;;; 
;;; Thus, the original reference path for the designation is split in two, the part after
;;; the focal name becoming the new reference path for the designation, and the part
;;; before the focal name being added to the inverse references which can then be 
;;; used to provide references to other designations.

(defun check-for-inverse-references 
       (designation inverse-references-for-designations)
  (let ((reference-structure 
	  (car (local-reference-finding-paths designation))))
    (if (and reference-structure
	     (check-for-inverse-references-rec
	       designation
	       reference-structure
	       inverse-references-for-designations))
      designation)))


(defun check-for-inverse-references-rec
       (designation reference-structure inverse-references-for-designations)
  (if (not (eq (local-name-provided reference-structure)
	       focus-range))
      ;; if inverse reference hasn't already been found
      (if (better-reference-provided-by-inverse-reference?
	    designation reference-structure inverse-references-for-designations)
	  t
	  (loop for needing-reference-structure
		    in (reference-structures-needing-provided-local-name
			 reference-structure)
		doing (if (check-for-inverse-references-rec
			    designation
			    needing-reference-structure 
			    inverse-references-for-designations)
			  (return t))))))


(defun better-reference-provided-by-inverse-reference?
       (designation reference-structure inverse-references-for-designations)
  (loop for inverse-reference
	    in inverse-references-for-designations
	thereis
	  (better-reference-provided-by-inverse-reference-rec?
	    designation reference-structure 
	    inverse-reference)))
;; Inverse references are always a single path except in the case of 
;; function definitions.


(defun end-reference-structure-p (reference-structure)
  (null (reference-structures-needing-provided-local-name
	  reference-structure)))  ; no needing reference structures


;;; Better-reference-provided-by-inverse-reference-rec? shortens the 
;;; reference path of the designation if a better reference is provided 
;;; by the inverse reference.  For example, if the reference path for
;;; the designation is
;;; global:tank -----> tank:valve -----> valve:position
;;; (where the notation is of the form <domain>:<role>)
;;; and the inverse reference structure is
;;; valve:focus
;;; then the new reference path becomes 
;;; valve:position
;;; and the inverse reference from valve to tank is generated and
;;; added to the inverse reference path.  A special case is when
;;; focus is on the local name of an end reference structure.
;;; In the above example, this happens when the inverse reference structure is
;;; position:focus.
;;; Build-inverse-reference-path-for-designation recognizes this special
;;; case and the new reference path becomes
;;; needed:position.

;;; Note that focus is ignored for global kb names.

(defun better-reference-provided-by-inverse-reference-rec?
       (designation reference-structure inverse-reference)
  (cond 
    ((and (not (reference-structure-for-global-symbol-p reference-structure))
	  (or 
	    (and (eq (domain-name-needed inverse-reference)
		     (domain-name-needed reference-structure))
		 (let ((providing-reference-structure?
			 (reference-structure-providing-needed-domain-name
			   reference-structure)))
		   (and providing-reference-structure?
			(not (reference-structure-for-global-symbol-p 
			       providing-reference-structure?)))))
	    (if (and (end-reference-structure-p reference-structure)
		     (eq (domain-name-needed inverse-reference)
			 (local-name-provided reference-structure)))
		(setf (focus-on-local-name-of-end-reference-structure?
			reference-structure) t))))
     (check-for-illegal-focus 
       designation reference-structure)
     (add-new-inverse-references
       reference-structure inverse-reference)
     (setf (local-reference-finding-paths
	     designation)
	   (phrase-list 
	     (build-inverse-reference-path-for-designation
	       reference-structure inverse-reference)))
     ;; Designations only have one single reference path.
     ;; There is no tree here.
     t)
    (t
     (loop for needing-inverse-reference 
	       in (reference-structures-needing-provided-local-name
		    inverse-reference)
	   doing (if (better-reference-provided-by-inverse-reference-rec?
		       designation
		       reference-structure needing-inverse-reference)
		     (return t))))))


;;; Check-for-illegal-focus first checks if reference-structure is 
;;; specifying a new runtime item.  If it does, then it is necessary to
;;; check if focus on the new runtime item is legal.  It is easy to
;;; check if reference-structure specifies a new runtime item.
;;; If it is an end reference structure, then if it is a root 
;;; (has no providing reference structure) and if it refers to a name
;;; in a previous designation (domain-name-needed is needed-domain), then 
;;; reference-structure does not specify a new runtime item.  If 
;;; reference-structure is not an end reference structure, then if
;;; its providing reference structure is a root and refers to a name
;;; in a previous designation, then reference-structure does not
;;; specify a new runtime item.  See also compile-forward-reference-path
;;; for a discussion on local names and specifying new runtime items.

(defun check-for-illegal-focus 
       (designation reference-structure)
  (when
    (cond
      ((focus-on-local-name-of-end-reference-structure? reference-structure)
       (not (and (not (reference-structure-providing-needed-domain-name
			reference-structure))
		 (eq (domain-name-needed reference-structure) needed-domain))))
      (t
       (let ((providing-reference-structure?
	       (reference-structure-providing-needed-domain-name
		 reference-structure)))
	 (if providing-reference-structure?	; should always be the case
	     (not (and (not (reference-structure-providing-needed-domain-name
			      providing-reference-structure?))
		       (eq (domain-name-needed providing-reference-structure?) needed-domain)))))))
    (check-for-illegal-focus-in-rule-consequent designation)))


(defun check-for-illegal-focus-in-rule-consequent (designation)
  (when forward-compiled-consequent?
    (loop for consequent-action 
	      in (cdr forward-compiled-consequent?)
	  thereis (illegal-focus-in-action?
		    consequent-action designation))))


(defun illegal-focus-in-action? (action focus-designation)
  (when (expression-for-compilation-p action)
    (let ((compiled-specific-expression
	    (compiled-specific-expression action)))
      (if 
	(case (car compiled-specific-expression)
	  ((conclude conclude-not conclude-has-no-current-value
		     conclude-has-no-value change-icon-color)  
	   ;; Focus in the designation of the conclude is allowed.
	   ;; However, if the conclude has an expression, focus in the
	   ;; expression is not allowed.
	   (let ((conclude-expression?
		   (third compiled-specific-expression)))
	     (when (and conclude-expression?
			(expression-for-compilation-p conclude-expression?))
	       (memq focus-designation
		     (designations-for-expression conclude-expression?)))))
	  (t
	   ;; If the action is invoke, break, focus, activate,
	   ;; deactivate, inform, set, move, set-position, rotate, or set-heading,
	   ;; no focus at all is allowed in the action.
	   
	   (memq focus-designation
		 (designations-for-expression action))))
	(setq fatal-focus-error-info?
	      (car compiled-specific-expression))))))


(defun build-inverse-reference-path-for-designation
    (forward-reference-structure inverse-reference-structure)
  (when (eq (domain-name-needed inverse-reference-structure)
	    (local-name-provided forward-reference-structure))
    (setf (domain-name-needed forward-reference-structure) needed-domain))
  forward-reference-structure)

;; Usually, domain-name-needed of the forward and inverse reference
;; structures will be the same.  However, when the forward-reference-structure
;; is an end reference structure, it is possible for the domain-name-needed
;; of the inverse reference to correspond to the local name provided of the
;; forward reference (see also better-reference-provided-by-inverse-reference-rec).
;; In this special case (which is fairly common) the forward reference structure
;; is turned into a "stub" by setting the domain-name-needed to needed-domain.


(defun add-new-inverse-references
       (reference-structure 
	providing-inverse-reference-structure)
  (if (not (eq (domain-name-needed reference-structure) needed-domain))
      (let ((new-inverse-reference-structure
	      (build-inverse-reference-path
		reference-structure 
		providing-inverse-reference-structure)))
	(if new-inverse-reference-structure
	    (progn
	      (phrase-push new-inverse-reference-structure
			   (reference-structures-needing-provided-local-name
			     providing-inverse-reference-structure))
	      (setf (reference-structure-providing-needed-domain-name
		      new-inverse-reference-structure)
		    providing-inverse-reference-structure))))))
;; Will add things to providing-inverse-reference-structure, typically the
;; root reference structure (focus reference structure) in 
;; inverse-references-for-designations.


(defun build-inverse-reference-path
       (reference-structure inverse-reference-structure)
  (let ((new-inverse-reference-structure
	  (make-compilation-reclaimable-reference-structure))
	(old-providing-reference-structure
	  (if (and (null (reference-structures-needing-provided-local-name
			   reference-structure))
		   (eq (domain-name-needed inverse-reference-structure)
		       (local-name-provided reference-structure)))
	      reference-structure
	      (reference-structure-providing-needed-domain-name
		reference-structure))))
    (if (not (eq (domain-name-needed 
		   old-providing-reference-structure)
		 needed-domain))
	(progn
	  (setf (quantifier new-inverse-reference-structure)
		'every-inverse
		(forward-reference-quantifier-for-inverse-references
		  new-inverse-reference-structure)
		(quantifier old-providing-reference-structure))
	  (setf (domain-name-needed new-inverse-reference-structure)
		(domain-name-needed old-providing-reference-structure)
		(local-name-provided new-inverse-reference-structure)
		(local-name-provided old-providing-reference-structure)
		(role-and-local-name new-inverse-reference-structure)
		(role-and-local-name old-providing-reference-structure)
		(embedded-expression-original-parse? 
		  new-inverse-reference-structure)
		(embedded-expression-original-parse?
		  old-providing-reference-structure))
	  (build-inverse-reference-path-rec
	    new-inverse-reference-structure
	    (reference-structure-providing-needed-domain-name
	      old-providing-reference-structure))
	  new-inverse-reference-structure))))


;; build-inverse-reference-path-rec will always return nil.

(defun build-inverse-reference-path-rec
       (previous-reference-structure
	reference-structure)
  (if (and reference-structure
	   (not (eq (domain-name-needed reference-structure) needed-domain)))
      (let ((new-inverse-reference-structure
	      (make-compilation-reclaimable-reference-structure)))
	(setf (quantifier new-inverse-reference-structure)
	      'every-inverse
	      (forward-reference-quantifier-for-inverse-references
		new-inverse-reference-structure)
	      (quantifier reference-structure))
	(setf (domain-name-needed new-inverse-reference-structure)
	      (domain-name-needed reference-structure)
	      (local-name-provided new-inverse-reference-structure)
	      (local-name-provided reference-structure)
	      (role-and-local-name new-inverse-reference-structure)
	      (role-and-local-name reference-structure)
	      (embedded-expression-original-parse? 
		new-inverse-reference-structure)
	      (embedded-expression-original-parse?
		reference-structure))

	(phrase-push new-inverse-reference-structure
		     (reference-structures-needing-provided-local-name
		       previous-reference-structure))
	(setf (reference-structure-providing-needed-domain-name
		new-inverse-reference-structure)
	      previous-reference-structure)

	(build-inverse-reference-path-rec
	  new-inverse-reference-structure
	  (reference-structure-providing-needed-domain-name
	    reference-structure)))))


;;; Combine-references-for-expression returns the combined
;;; references for the expression.  This does nothing if the argument expression
;;; is not an expression-for-compilation.  Therefore, 
;;; compile1-forward-reference-for-designations must generate an 
;;; expression-for-compilation for any expression that has an 
;;; expression-for-compilation as a sub-expression.

;; The combination of reference paths is best illustrated by example.
;; Suppose the expression is
;;      (+ (the a (the b (the c)))
;;         (the d (the b)))
;; The reference paths for the sub-expressions are
;;      (needed the c)---(c the b)---(b the a)
;; and
;;      (needed the b)---(b the d)
;; The reference path for the expression will be
;;      (needed the c)---(c the b)---(b the a)
;;                                   (b the d)

(defun combine-references-for-expression (expression)
  (when (expression-for-compilation-p expression) 
    (let ((operator
	    (if (or (expression-for-compilation-designation-p expression) 
				(not (listp (compiled-specific-expression expression))))
		'+   ; + is a "safe" operator to use here
		(car (compiled-specific-expression expression)))))
      (unless (operator-does-not-require-references-p operator)
	(let* ((designation-p
		 (expression-for-compilation-designation-p expression))
	       (reference-paths-for-expression
		 (if designation-p	;ends recursion
		     (combine-references-for-designation expression)
		     (let ((reference-paths
			     (loop for sub-expression
				       in (cdr (compiled-specific-expression expression))
				   nconc
				   (combine-and-copy-references-for-expression				     
				     sub-expression))))
		       (combine-reference-finding-paths reference-paths)))))
	  (unless designation-p
	    (setf (local-reference-finding-paths expression)
		  reference-paths-for-expression))
	  reference-paths-for-expression)))))


(defun combine-references-for-designation 
       (designation-expression-for-compilation)
  (let* ((copied-local-reference-path
	   (copy-list-using-phrase-conses
	     (local-reference-finding-paths 
	       designation-expression-for-compilation)))
	 (paths-for-embedded-expressions?
	   (loop as next-rs?
		    = (car copied-local-reference-path)
		    then (car (reference-structures-needing-provided-local-name
				next-rs?))
		 until (null next-rs?)
		 as embedded-expression? = (embedded-expression? next-rs?)
		 nconc (when embedded-expression?
			 (combine-and-copy-references-for-expression embedded-expression?)))))
    (cond 
      ((null paths-for-embedded-expressions?)
       copied-local-reference-path)
      (t
       (combine-reference-finding-paths
	 (nconc copied-local-reference-path paths-for-embedded-expressions?))))))



(defun combine-and-copy-references-for-expression (expression)
  (copy-list-using-phrase-conses 
    (combine-references-for-expression expression)))



(defun combine-reference-paths-for-explicit-iteration-designations ()
  (let ((reference-paths
	  (loop for designation in designations-from-explicit-iteration-forms
		nconc (copy-list-using-phrase-conses
			(local-reference-finding-paths designation)))))
    (combine-reference-finding-paths reference-paths)))

(defun combine-references-for-actions (action-or-actions)
  (loop for expression 
	    in (cdr action-or-actions)
	do
    (combine-references-for-expression expression)))



;;; Combine-references-for-antecedent-and-consequent returns the reference
;;; tree for the entire rule.  It also marks the designations to indicate
;;; shortest reference paths.

(defun combine-references-for-antecedent-and-consequent
       (combined-inverse-and-antecedent-reference-tree
	antecedent consequent)
  (declare (ignore antecedent))
  (let* ((reference-paths-for-consequent
	   (loop for expression 
		     in (cdr consequent)
		 nconc 
		   (copy-list-using-phrase-conses
		     (local-reference-finding-paths expression))))
	 (reference-paths
	   (nconc 
	     (copy-list-using-phrase-conses
	       combined-inverse-and-antecedent-reference-tree)  ; actually a forest
	     reference-paths-for-consequent)))
    (combine-reference-finding-paths reference-paths)))

(defun combine-inverse-reference-paths-with-local-reference-paths
       (inverse-references local-references)
  (loop with combined-reference-paths
	  = (phrase-list
	      (copy-reference-structure
		(car inverse-references)))  ; (cdr inverse-references) should be nil
	for reference-structure
	    in local-references
	do
    (setq combined-reference-paths
	  (combine-reference-finding-paths-1
	    combined-reference-paths
	    reference-structure))
	finally
	  (return combined-reference-paths)))


(defun combine-explicit-iteration-and-antecedent-reference-trees
       (explicit-iteration-references local-references)
  (combine-reference-finding-paths
    (nconc explicit-iteration-references 
	   (copy-list-using-phrase-conses
	     local-references))))


(defun combine-left-side-tree-with-right-side-tree
       (left-side-local-references right-side-local-references)
  (loop with combined-reference-paths
	  = (phrase-list
	      (copy-reference-structure
		(car left-side-local-references)))
	;; (cdr left-side-local-references) should be nil
	for reference-structure
	    in right-side-local-references
	do
    (setq combined-reference-paths
	  (combine-reference-finding-paths-1
	    combined-reference-paths
	    reference-structure))
	finally
	  (return combined-reference-paths)))


;;; Combine-reference-finding-paths calls combine-reference-finding-paths-1
;;; iteratively for each (root) reference structure in reference-paths.
;;; Note that reference-paths is always a list.

(defun combine-reference-finding-paths (reference-paths)
  (loop with combined-reference-paths = nil
	for reference-structure in reference-paths
	do
    (setq combined-reference-paths
	  (combine-reference-finding-paths-1
	    combined-reference-paths
	    reference-structure))
	finally (return combined-reference-paths)))


;;; Combine-reference-finding-paths-1 takes as arguments
;;; reference-structure-list-1, which is always a list of reference
;;; structures, and reference-structure-2, which is a reference
;;; structure.  A copy is made of reference-structure-2.  This is done
;;; because when reference-paths for sub-expressions are combined into
;;; the reference path for the enclosing expression, pointers to related
;;; reference structures are added and the original reference structures
;;; for the sub-expressions are effectively destroyed.  This would cause
;;; problems in the second pass; therefore, a copy is made.

(defun combine-reference-finding-paths-1
    (reference-structure-list-1 reference-structure-2)
  (cond
    ((not reference-structure-2)
     reference-structure-list-1)
    ((not reference-structure-list-1)
     (phrase-list (copy-reference-structure
		    reference-structure-2)))
    (t
     (let ((copy-of-reference-structure-2
	     (copy-reference-structure
	       reference-structure-2)))
       (loop for reference-structure 
		 in reference-structure-list-1
	     doing (if (and (not (combining-needing-roots-p
				   reference-structure copy-of-reference-structure-2))
			    (combine-reference-finding-paths-rec
			      reference-structure
			      copy-of-reference-structure-2))
		       (return reference-structure-list-1))
	     finally (return (nconc reference-structure-list-1
				    (phrase-list copy-of-reference-structure-2))))))))

(defun-simple implicit-iterator-in-reference-structure (test-reference-structure)
  (let ((result? nil))
    (setq result? (implicit-iterator-p (quantifier test-reference-structure)))
    (loop until result?
	  for use in (reference-structures-needing-provided-local-name test-reference-structure)
	  do
      (setq result? (implicit-iterator-p (quantifier use))))
    result?))

;; Note that needing roots are not combined.  This would cause problems
;; for illegal-reference-outside-expression which would in certain cases
;; flag an error when there is none.  Besides, it is awkward to have
;; one needing root reference provide to another;  it makes the top
;; level reference tree look assymmetrical.

(defun combining-needing-roots-p
    (reference-structure-to-try reference-structure-2)
  (or
    (and (eq (domain-name-needed reference-structure-to-try) needed-domain)
	 (eq (domain-name-needed reference-structure-2) needed-domain)
	 (eq (local-name-provided reference-structure-to-try)
	     (local-name-provided reference-structure-2)))
    (and
      (or (eq (quantifier reference-structure-to-try) 'quantifier))
      (implicit-iterator-in-reference-structure reference-structure-2)
      (progn
;	(break "new test causes t (a)")
	t))
    (and
      (or (eq (quantifier reference-structure-2) 'quantifier))
      (implicit-iterator-in-reference-structure reference-structure-to-try)
      (progn
;	(break "new test causes t (a)")
	t))))


;;; Combine-reference-finding-paths-rec will return nil if the structures
;;; can't be combined.  

;; Note that the check if the quantifier is 'every has been commented out.
;; Thus, combination is no longer prevented.  The check for illegal 
;; references is now made after the first pass is finished by
;; illegal-reference-from-an-every-quantifier?. - agh 2/3/88
;; An every quantifier in a designation is now allowed to supply references to other 
;; designations within the immediately enclosing logical expression of its 
;; designation.  It used to be restricted to supplying references only to the
;; designation in which it appears.

(defun combine-reference-finding-paths-rec
       (reference-structure-to-try reference-structure-2)
  (if (or 
;	(eq (quantifier reference-structure-to-try)  
;	    'every)
	(eq (domain-name-needed reference-structure-2)
	    global-domain))
      nil
      (cond
	((or (and (eq (domain-name-needed reference-structure-2)
		      needed-domain)
		  (eq (local-name-provided reference-structure-2)
		      (local-name-provided reference-structure-to-try)))
	     (eq (domain-name-needed reference-structure-2)
		 (local-name-provided reference-structure-to-try)))
	 (phrase-push reference-structure-2
		      (reference-structures-needing-provided-local-name
			reference-structure-to-try))
	 (setf (reference-structure-providing-needed-domain-name
		 reference-structure-2)
	       reference-structure-to-try)
	 reference-structure-to-try)
	(t
	 (loop for reference-structure
		   in (reference-structures-needing-provided-local-name
			reference-structure-to-try)
	       doing (if (combine-reference-finding-paths-rec
			   reference-structure
			   reference-structure-2)
			 (return reference-structure-to-try)))))))


;;;; Copying Reference Structures


;;; Copy-reference-structure copies the reference structure and then calls
;;; itself recursively to make copies of the reference structures in the
;;; reference-structures-needing-provided-local-name, if any.  
;;; Thus, copy-reference-structure may copy a whole tree of reference structures
;;; rather than just one reference structure.
;;; This, of course, assumes no circularities in the reference paths, a phenomenon
;;; which could never happen in the current implementation.

;;; As mentioned in the documentation for combine-reference-finding-paths-1,
;;; reference structures have to be copied because when reference trees for
;;; sub-expressions are combined into the reference tree for the enclosing
;;; expression, pointers to related reference structures are added which would
;;; result in effectively destroying the reference structures for the sub-expressions
;;; if copies were not made.  Thus, separate reference trees containing separate
;;; copies of the same original reference structures are maintained for each
;;; level in the recursion of the first pass compile.  Pointers are kept so
;;; that it is possible, for example, to find the reference structure in the
;;; top-level-reference-tree of a rule or expression which is a copy of some
;;; reference structure in a designation.  This is important in compile2-name
;;; where it is necessary to decide if a name in a designation needs a "let"
;;; binding by analyzing its copy in the top-level-reference-tree.

;;; Thus, a rather complicated "3-dimensional" network of reference structures
;;; results.  The reference structure tree resulting from the
;;; reference-structure-providing-needed-domain-name and the
;;; reference-structures-needing-provided-local-name relations of reference 
;;; structures can be thought of as 2-dimensional.  The third dimension is
;;; each level of copied reference trees corresponding to each level of recursion
;;; (or each level of sub-expressions) in the first pass.  The levels of reference
;;; trees can be traversed using the
;;; copy-of-this-reference-structure-for-superior-expression and
;;; copy-of-this-reference-structure-for-sub-expression slots.
;;; Note that there will only be one copy of a reference structure per level.
;;; This is obvious from the way reference paths and trees are combined
;;; (see combine functions above).

;; The expression-for-compilation structures, which contain the reference trees 
;; (in their local-reference-finding-paths slots), could be thought of as a 
;; fourth dimension in this structure.

;; It would probably be good to give an example showing each two-dimensional
;; reference tree for each level and showing the links between copies of reference
;; structures at each level.

;;; It is always assumed in copy-reference-structure that the copied reference structure
;;; is to be used in the reference tree for the superior expression to 
;;; the expression whose reference tree contains the original reference structure.
;;; Thus, the copy-of-this-reference-structure... pointers can be set here.

(defun copy-reference-structure 
       (reference-structure &optional providing-reference-structure)
  (let ((copied-reference-structure
	  (make-compilation-reclaimable-reference-structure)))
    (setf (domain-name-needed
	    copied-reference-structure)
	  (domain-name-needed
	    reference-structure)
	  (local-name-provided
	    copied-reference-structure)
	  (local-name-provided
	    reference-structure)
	  (role-and-local-name
	    copied-reference-structure)
	  (role-and-local-name
	    reference-structure)
	  (quantifier
	    copied-reference-structure)
	  (quantifier
	    reference-structure)
	  (embedded-expression-original-parse? 
	    copied-reference-structure)
	  (embedded-expression-original-parse?
	    reference-structure)
	  (forward-reference-quantifier-for-inverse-references
	    copied-reference-structure)
	  (forward-reference-quantifier-for-inverse-references
	    reference-structure)
	  (copy-of-this-reference-structure-for-superior-expression
	    reference-structure)
	  copied-reference-structure
	  (copy-of-this-reference-structure-for-sub-expression
	    copied-reference-structure)
	  reference-structure
	  (reference-structures-needing-provided-local-name
	    copied-reference-structure)
	  (loop for needing-reference-structure
		    in (reference-structures-needing-provided-local-name
			 reference-structure)
		collect (copy-reference-structure
			  needing-reference-structure
			  copied-reference-structure)
		  using phrase-cons))
    (if providing-reference-structure
	(setf (reference-structure-providing-needed-domain-name
		copied-reference-structure)
	      providing-reference-structure))
    copied-reference-structure))


;; Currently, it is actually only necessary to have the top level reference tree
;; and the reference paths for the designations.  Thus, reference trees for 
;; sub-expressions between designations and the top level expression are actually
;; not necessary.  Maintain these copies for now though; they are useful for
;; debugging.

;; Note that this copying is only done when combining reference trees.  Therefore,
;; it is done after designations (including inverse stuff) are fully processed and
;; there is no possibility of copying reference trees which will change.



(defun get-copy-of-reference-structure-in-highest-level-reference-tree
       (reference-structure)
  (change-reference-structures-at-all-higher-levels 
    reference-structure nil nil))


(defun change-reference-structures-at-all-higher-levels
    (reference-structure change-function? change-arg?)
  (loop with higher-level-reference-structure
	= (copy-of-this-reference-structure-for-superior-expression
	    reference-structure)
	do 
    (when change-function?
      (funcall change-function? reference-structure change-arg?))
    (cond ((null higher-level-reference-structure)
	   (return reference-structure))
	  (t	   
	   (setq reference-structure
		 higher-level-reference-structure)
	   (setq higher-level-reference-structure
		 (copy-of-this-reference-structure-for-superior-expression
		   reference-structure))))))

;; The highest-level-reference-tree will typically be the top-level-refence-tree
;; for the expression or rule.


;(defun get-copy-of-reference-structure-in-lowest-level-reference-tree
;       (reference-structure)
;  (loop with lower-level-reference-structure
;	  = (copy-of-this-reference-structure-for-sub-expression
;	      reference-structure)
;	do (if (null lower-level-reference-structure)
;	       (return reference-structure)
;	       (setq reference-structure
;		     lower-level-reference-structure
;		     lower-level-reference-structure
;		     (copy-of-this-reference-structure-for-sub-expression
;		       reference-structure)))))

;; This is not currently used.
;; The lowest-level-reference-tree will typically be the reference path
;; for some designation.




;; Print-reference-tree and print-reference-structure are for debug only.

#+development
(defun print-reference-tree (reference-tree)
  (terpri)
  (loop for reference-structure in reference-tree
	do
    (print-reference-tree-rec reference-structure 0)))

#+development
(defun print-reference-tree-rec (reference-structure indentation)
  (print-indentation-for-reference-tree indentation)
  (format t "~s ~s ~s~%" 
	  (domain-name-needed reference-structure)
	  (quantifier reference-structure)
	  (local-name-provided reference-structure))
  (loop for needing-reference-structure
	    in (reference-structures-needing-provided-local-name
		 reference-structure)
	do (print-reference-tree-rec needing-reference-structure (+ indentation 1))))

#+development
(defun print-reference-path (reference-structure)
  (terpri)
  (when reference-structure
    (print-reference-tree-rec reference-structure 0)))

#+development
(defun print-indentation-for-reference-tree (indentation)
  (loop repeat indentation
	do (format t "  ")))




;;;; Second pass compilation

;;; The second pass builds the iteration structures and binding
;;; structures for the expressions in an optimal way.  The reference
;;; structures built in the first pass are utilized to accomplish this.
;;; The "for" structure is currently used for both iteration and
;;; binding.  If there is no iteration or binding needed, then "the"
;;; (which is more runtime efficient) is used.

;;; The second pass compilation functions are operator-type specific.

;;; Iteration forms are made by compile2-name which is used to second-pass
;;; compile designations.  This returns 3 values:  iteration-forms,
;;; insertion-location, and
;;; expression-to-be-inserted.  Expression-to-be-inserted is to be
;;; inserted at some point into the iteration-forms at the insertion-locations.

;;; The function compile2-comparison-operator-expression is used to second pass
;;; compile arithmetic and comparison expressions as well as function calls.
;;; Compile2-name will be called for each designation in the expression.
;;; Compile2-comparison-operator-expression takes the 3 values returned by
;;; compile2-name for each designation and builds iteration-forms for the entire
;;; expression.  Order of iteration forms is maintained; (subsequent iterations
;;; forms are nested inside previous ones).

;;; All non-top-level second pass compile functions return the 3 values to the
;;; top-level second pass compilation forms, even if iteration forms have been
;;; combined and these values are nil.  See also
;;; agh>generic-compiler-report.text, agh>universal-quantifier-compile-test.kb.

;;; The second pass simply passes symbols through.


;; First pass basically removes all quantification and role operators.




;; Functions in second pass
;; These aren't all the functions; only the higher level ones 
;; associated with the operators.

;; top level functions
;; 
;; compile2-expression-top
;;   compile2-expression-1-top
;;     compile2-logical-operator-expression-top
;;       compile2-and-expression-top
;;         compile2-and-expression-rec
;;           compile2-expression
;;       compile2-or-expression-top
;;         compile2-or-expression-rec
;;           compile2-or-sub-expression
;;             compile2-expression
;;       compile2-not-expression-top 
;;     compile2-comparison-operator-expression-top
;; 
;; 
;; non top level functions
;; 
;; compile2-expression
;;   compile2-expression-1
;;     compile2-logical-operator-expression
;;       compile2-and-expression
;;         compile2-and-expression-rec
;;           compile2-expression
;;       compile2-or-expression
;;         compile2-or-expression-rec
;;           compile2-or-sub-expression
;;             compile2-expression
;;       compile2-not-expression-top
;;     compile2-comparison-operator-expression-top

;; compile2-arithmetic-operator-expression shouldn't be called at all.


;;; In-non-top-level-context? is dynamically bound to t by functions such as
;;; compile2-quantifier-or-aggregator to indicate to compile2-name that 
;;; binding forms are not top level but are to be wrapped tightly around 
;;; the expression.  Therefore, compile2-name will not put for-structures
;;; on context-iteration-forms or non-context-top-level-binding-forms
;;; but will instead return them for insertion.

(def-system-variable in-non-top-level-context? compile2 nil)



;;; The top level functions return an expression-for-compilation.
;;; The non top level functions typically
;;; return three values: iteration-forms, expression-for-insertion, and
;;; insertion-location.  

(defun compile2-expression-top (expression)
  (cond
    ((phrase-number-p expression)
     expression)
    ((symbolp expression)
     expression)
    ((text-string-p expression)
     expression)
    ((and (consp expression)
	  (or (eq (car expression) 'quote)
	      (phrase-number-p (car expression))))  ; if constant of form (number . units)  
     expression)
    ((expression-for-compilation-p expression)
     (compile2-expression-1-top expression))))

;; Collapse cond cases into one "or" form!



(defun compile2-expression (expression)
  (cond
    ((phrase-number-p expression)
     (values nil expression nil))
    ((symbolp expression)
     (values nil expression nil))
    ((text-string-p expression)
     (values nil expression nil))
    ((phrase-structure-p expression)
     (values nil expression nil))
    ((phrase-sequence-p expression)
     (values nil expression nil))
    ((consp expression)
     (cond 
       ((or (eq (car expression) 'quote)
	    (phrase-number-p (car expression)))  ; if constant of form (number . units)  
	(values nil expression nil))
       ((eq (car-of-cons expression) 'the)
	(values
	  nil
	  (phrase-list*
	    'the (second expression)
	    (loop for domain in (cddr expression)
		  collect (multiple-value-bind (ignored expression-for-insertion)
			      (compile2-expression domain)
			    (declare (ignore ignored))
			    expression-for-insertion)
		    using phrase-cons))
	  nil))
	    
       (t
	(loop for sub-expression in expression
	      collect 
		(multiple-value-bind
		  (iteration-forms expression-for-insertion insertion-location)
		    (compile2-expression sub-expression)
		  iteration-forms insertion-location
		  expression-for-insertion)
		into return-expression
				 using phrase-cons
	      finally (return (values nil return-expression nil))))))
    ((expression-for-compilation-p expression)
     (compile2-expression-1 expression))))



;;; Compile2-expression-1-top assumes that the argument is an
;;; expression-for-compilation.


;;; In the `and' case ig  takes an expression-for-compilation as its
;;; argument and calls compile-2-and-expression-rec which returns the three
;;; values iteration-forms, expression-for-insertion, and insertion-location.
;;; The expression-for-insertion is inserted into the iteration-forms at the
;;; insertion-location.  Iteration-forms becomes the new 
;;; compiled-specific-expression.

;;; For example, if the expression is
;;;      (and (> (the a (any b (any c))) 5)
;;; 	      (< (the d (the b)) 4))
;;; then the iteration forms will be
;;;      (for (every b c) nil nil
;;; 	      (when (> (the a b) 5)
;;; 	        ))
;;; and the expression-for-insertion will be
;;;      (< (the d b) 4)

;;; (printed representations of structures are used in this example)
;;; Note that the original "and" has disappeared.  It is replaced 
;;; by the "for" iteration forms and "when" forms for efficiency.
;;; Note also that the insertion location is associated with the last
;;; sub-expression in the and.  All sub-expressions but the last
;;; are processed in iteration forms, with "when" forms used to
;;; test whether each sub-expression is true (see also 
;;; compile2-and-expression-rec.

(defun compile2-expression-1-top (expression-for-compilation)
  (if (consp (compiled-specific-expression
	       expression-for-compilation))
      (let ((operator
	      (first (compiled-specific-expression
		       expression-for-compilation))))	
	(cond
	  ((quantifier-or-aggregator-p operator)
	   (compile2-top-level-expression-and-insert
	     expression-for-compilation 'compile2-quantifier-or-aggregator))
	  ((logical-operator-p operator)
	   ;; Test for the different kinds of logicals
	   (cond
	     ((eq operator 'and)
	      (compile2-top-level-expression-and-insert
		expression-for-compilation 'compile2-and-expression))
	     ((eq operator 'or)
	      (compile2-top-level-expression-and-insert
		expression-for-compilation 'compile2-or-expression))
	     ((eq operator 'not)
	      (compile2-top-level-expression-and-insert
		expression-for-compilation 'compile2-not-expression))
	     (t nil)))
	  ((if-operator-p operator)
	   (compile2-top-level-expression-and-insert
	     expression-for-compilation 'compile2-if-expression))
	  (t  ; comparison, arithmetic, or any other function name
	   (compile2-top-level-expression-and-insert
	     expression-for-compilation 'compile2-comparison-operator-expression))))
      (progn
	(compile2-top-level-expression-and-insert
	  expression-for-compilation 'compile2-name))))


(defun compile2-action (expression-for-compilation)
  (let ((operator
	  (first (compiled-specific-expression
		   expression-for-compilation)))
	(inside-action-iteration-p t))
    (cond
      ((eq operator 'inform)
       (compile2-inform expression-for-compilation))
      (t
       (compile2-action-according-to-template
	 expression-for-compilation
	 (lookup-action-template operator))))))


(defun compile2-top-level-expression-and-insert
       (expression-for-compilation compilation-function)
  (multiple-value-bind
    (iteration-forms expression-for-insertion insertion-location)
      (funcall-symbol compilation-function
		      expression-for-compilation)
    (let* ((compiled-specific-expression
	     (insert-expressions-into-combined-iteration-forms
	       iteration-forms expression-for-insertion insertion-location)))
      (setf (compiled-specific-expression
	      expression-for-compilation)
	    compiled-specific-expression)))
  expression-for-compilation)



(defun insert-expressions-into-combined-iteration-forms
       (iteration-forms expression-for-insertion insertion-location)
  (if insertion-location
      (progn
	(insert-expression-into-for-structure-body
	  expression-for-insertion
	  insertion-location)
	iteration-forms)
      expression-for-insertion))


(defun compile2-if-expression
       (expression-for-compilation)
  (compile2-comparison-operator-expression expression-for-compilation))



;;; A non-providing expression does not supply references to 
;;; any other expression.  Therefore, rather than returning the
;;; iteration-forms, expression-for-insertion, insertion-location
;;; triple which would allow for providing references, only one
;;; value, the compiled form, is returned.

(defun compile-non-providing-expression (expression)
  (let ((inside-action-iteration-p nil))
    (multiple-value-bind
      (iteration-forms expression-for-insertion insertion-location)
	(compile2-expression expression)
      (insert-expressions-into-combined-iteration-forms
	iteration-forms expression-for-insertion insertion-location))))



;;; Compile2-providing-expression-collecting-iteration-forms, rather than
;;; returning the usual triple of nested iteration forms, 
;;; expression to be inserted, and insertion location, returns a triple of
;;; listed iteration forms, expression to be inserted, and listed insertion
;;; locations.  The nesting is accomplished by nest-listed-iteration-forms.

(defun compile2-providing-expression-collecting-iteration-forms
       (expression iteration-forms insertion-locations)
  (multiple-value-bind
    (iteration-form expression-for-insertion insertion-location)
      (compile2-expression expression)
    (setq iteration-forms
	  (phrase-cons iteration-form iteration-forms)
	  insertion-locations
	  (phrase-cons insertion-location insertion-locations))
    (values iteration-forms expression-for-insertion insertion-locations)))

;; Review if this mechanism can be used throughout the second pass!


(defun nest-listed-iteration-forms 
       (iteration-forms insertion-locations expression-to-insert)
  (loop with form-to-insert = expression-to-insert
	for iteration-form in iteration-forms
	for insertion-location in insertion-locations
	do (setq form-to-insert
		 (insert-expressions-into-combined-iteration-forms
		   iteration-form form-to-insert insertion-location))
	finally (return form-to-insert)))




(defun compile2-action-according-to-template
       (expression-for-compilation template?)
  (let* ((compiled-specific-expression
	   (compiled-specific-expression
	     expression-for-compilation))
	 (iteration-forms nil)
	 (insertion-locations nil)
	 (compiled-action-forms
	   (loop with rest-of-template = (cdr template?)
		 with template-symbol 
		   = (if template? (car rest-of-template) 'designation)
		 with compiled-sub-form
		 for sub-form in (cdr compiled-specific-expression)
		 do
	     (case template-symbol
	       (other (setq compiled-sub-form sub-form))
	       (show-or-hide-argument-list
		(if (eq
		      (cond
			((consp sub-form) (car sub-form))
			((expression-for-compilation-p sub-form)
			 (car (compiled-specific-expression sub-form))))
		      'in)
		    (multiple-value-setq
		      (iteration-forms compiled-sub-form insertion-locations)
		      (compile2-providing-expression-collecting-iteration-forms
			sub-form iteration-forms insertion-locations))
		    (setq compiled-sub-form sub-form)))
	       (t				       ; designation or action
		(multiple-value-setq
		  (iteration-forms compiled-sub-form insertion-locations)
		  (compile2-providing-expression-collecting-iteration-forms
		    sub-form iteration-forms insertion-locations))))
	     (if template?
		 (if (symbolp (cdr rest-of-template))  ; if dotted list template
		     (setq template-symbol (cdr rest-of-template))
		     (setq rest-of-template (cdr rest-of-template)
			   template-symbol (car rest-of-template)))
		 (setq template-symbol 'expression))
		 collect compiled-sub-form using phrase-cons))
	 (action-to-be-inserted
	   (phrase-cons 
	     (first compiled-specific-expression) compiled-action-forms)))
    (setf (compiled-specific-expression expression-for-compilation)
	  (nest-listed-iteration-forms 
	    iteration-forms insertion-locations action-to-be-inserted)))
    
  expression-for-compilation)

;; The action can have more than one designation.  Any iteration in the 
;; designations is wrapped around the entire action.




(defun compile2-inform
       (expression-for-compilation)
  (let* ((compiled-specific-expression
	   (compiled-specific-expression
	     expression-for-compilation))
	 (designation-for-inform
	   (second compiled-specific-expression))

	 ;; Only one designation for now.  Talk to Mike
	 ;; about current limitations and how to improve.

	 (expressions-for-inform
	   (cddr compiled-specific-expression)))
    (multiple-value-bind
      (iteration-forms-for-inform-designation 
       expression-for-insertion-for-inform-designation
       insertion-location-for-inform-designation)
	(compile2-expression designation-for-inform)
      (multiple-value-bind
	(iteration-forms-for-inform-message
	 expression-for-insertion-for-inform-message
	 insertion-locations-for-inform-message)
	  (compile2-inform-message-expression
	    (car expressions-for-inform))
	(let* ((expression-for-insertion-for-inform-expressions
		 (loop for sub-expression in (cdr expressions-for-inform)
		       collect
			 (compile-non-providing-expression sub-expression)
					  using phrase-cons))
	       (new-compiled-specific-expression
		 (insert-expressions-into-combined-iteration-forms
		   iteration-forms-for-inform-designation
		   (nest-listed-iteration-forms 
		     iteration-forms-for-inform-message
		     insertion-locations-for-inform-message
		     (phrase-cons
		       'inform
		       (phrase-cons
			 expression-for-insertion-for-inform-designation
			 (phrase-cons
			   expression-for-insertion-for-inform-message
			   expression-for-insertion-for-inform-expressions))))
		   insertion-location-for-inform-designation)))
	  (setf (compiled-specific-expression
		  expression-for-compilation)
		new-compiled-specific-expression)
	  expression-for-compilation)))))


(defun compile2-inform-message-expression (message-expression)
  (if (text-string-p message-expression)
      (values nil message-expression nil)
      (loop with current-expression-for-insertion 
	      = (phrase-list 'and)
	    with iteration-forms and insertion-locations
	    for string-or-expression 
		in (cdr (compiled-specific-expression
			  message-expression))
	    do
	(if (text-string-p string-or-expression)
	    (setq current-expression-for-insertion
		  (nconc current-expression-for-insertion
			 (phrase-list string-or-expression)))
	    (let (expression-for-insertion)
	      (multiple-value-setq
		(iteration-forms expression-for-insertion insertion-locations)
		(compile2-providing-expression-collecting-iteration-forms
		  string-or-expression iteration-forms insertion-locations))
	      (setq current-expression-for-insertion
		    (nconc current-expression-for-insertion
			   (phrase-list expression-for-insertion)))))
	    finally
	      (return (values iteration-forms 
			      current-expression-for-insertion
			      insertion-locations)))))



(defun compile2-expression-1 (expression-for-compilation)
  (if (consp (compiled-specific-expression
	       expression-for-compilation))
      (let ((operator 
	      (first (compiled-specific-expression
		       expression-for-compilation))))
	(cond
	  ((eq operator 'quote)
	   expression-for-compilation)
	  ((quantifier-or-aggregator-p operator)
	   (compile2-quantifier-or-aggregator expression-for-compilation))
	  ((logical-operator-p operator)  
	   (compile2-logical-operator-expression
	     expression-for-compilation))
	  ((if-operator-p operator)
	   (compile2-if-expression expression-for-compilation))
	  (t  ; comparison, arithmetic, or action operators, or any other function name
	   (compile2-comparison-operator-expression
	     expression-for-compilation))))
      (compile2-name
	expression-for-compilation)))



(defun compile2-quantifier-or-aggregator (expression-for-compilation)
  (let* ((in-non-top-level-context? t)
	 (old-compiled-specific-expression
	   (compiled-specific-expression expression-for-compilation))
	 (compiled-aggregator-expression
	   (compile-non-providing-expression
	     (third old-compiled-specific-expression)))
	 (scope (second old-compiled-specific-expression))
	 (reference-structure-for-aggregator-scope
	   (get-relevent-reference-structure-for-aggregator-scope scope))
	 (new-compiled-specific-expression
	   (phrase-list 
	     (first old-compiled-specific-expression)
	     scope
	     compiled-aggregator-expression)))
    (when 
      (memq (compiled-specific-expression scope)
		local-names-not-associated-with-roles)
      (add-for-structure-to-non-context-binding-forms
	(make-for-structure-given-reference-structure
	  reference-structure-for-aggregator-scope)))
    (when (eq (car old-compiled-specific-expression) 'there-exists-literal)
      (phrase-push 
	reference-structure-for-aggregator-scope
	reference-structures-originating-from-within-existence-predicate))
    (values nil
	    new-compiled-specific-expression
	    nil)))

;; Only the aggregator expression (not the aggregator scope) is compiled in the
;; second pass.

;; The second pass compile of quantifiers and aggregators is similar to that
;; for if expressions in that compile-non-providing-expression is used
;; (bindings from within the expression are not wrapped around the expression
;; for use by other expressions).


#+unused
(defun compile2-comparison-operator-expression-top (expression-for-compilation)
  (compile2-top-level-expression-and-insert
    expression-for-compilation 'compile2-comparison-operator-expression))


;;; Compile2-comparison-operator-expression loops through the
;;; sub-expressions, deciding what names have to be provided by each
;;; sub-expression and invoking compile2-expression for the
;;; sub-expression with these names.  It combines the iteration forms
;;; returned for each sub-expression and returns these as the new
;;; iteration forms, the compiled-specific-expression as the
;;; expression-for-insertion, and the insertion-location in the
;;; iteration forms.

(defun compile2-comparison-operator-expression (expression-for-compilation)
  (let* ((sub-expressions 
	   (cdr (compiled-specific-expression
		  expression-for-compilation)))
	 (operator 
	   (car (compiled-specific-expression
		  expression-for-compilation)))
	 (iteration-forms nil)
	 (insertion-location nil)
	 (new-compiled-specific-expression
	   (phrase-list operator)))
    (loop for sub-expression in sub-expressions
	  do
     (multiple-value-setq
       (iteration-forms new-compiled-specific-expression insertion-location)
       (incorporate-iteration-forms-of-expression-and-sub-expression
	 iteration-forms new-compiled-specific-expression insertion-location
	 sub-expression
	 'combine-sub-expression-with-expression)))
    (values iteration-forms
	    new-compiled-specific-expression
	    insertion-location)))


#+unused
(defun compile2-arithmetic-operator-expression (expression-for-compilation)
  (compile2-comparison-operator-expression expression-for-compilation))




;;; Compile2-name takes as argument expression-for-compilation and returns
;;; iteration-forms, expression-for-insertion, and insertion-location.  It
;;; builds iteration-forms so that all names which must be bound (for iteration
;;; or for providing a reference) are.  The "for" iteration form will be built
;;; as long as there is iteration, or for binding to supply references.  If
;;; there is no need to do either of these, then the more efficient "the" form
;;; is constructed by calling build-optimized-reference-phrase.

(defvar iteration-forms-for-embedded-expressions?)
(defvar insertion-location-for-embedded-expressions?)

(defun compile2-name (expression-for-compilation)
  (if (not (local-reference-finding-paths expression-for-compilation))	       ; if name of entity in kb
      (values nil 
	      (compiled-specific-expression
		expression-for-compilation)
	      nil)
      (loop with anchor-reference-structure
	      = (car (local-reference-finding-paths expression-for-compilation))
	    with iteration-forms = nil
	    with insertion-location = nil
	    with iteration-forms-for-embedded-expressions? = nil
	    with insertion-location-for-embedded-expressions? = nil
	    with previous-for-structure = nil
	    with for-structure = nil
	    with for-structure-binding-expression = nil
	    with for-structure-target-name = nil
	    with local-iteration-forms = nil
	    with local-insertion-location = nil
	    as reference-structure 
	       = anchor-reference-structure
	       then (if (reference-structures-needing-provided-local-name
			  reference-structure)
			(car (reference-structures-needing-provided-local-name
			       reference-structure)))
	    until (null reference-structure)
	    as reference-depends-on-existence?
	       = (reference-depends-on-existence? reference-structure)
	    as in-line-optimizing-ok?
	       = (or reference-depends-on-existence? in-non-top-level-context?
		     allow-in-line-designations?)
	    as provides-binding-for-iteration?
	       = (reference-structure-provides-binding-for-iteration? 
		   reference-structure)
	    as provides-local-binding?
	       = (when (not provides-binding-for-iteration?)
		   (reference-structure-provides-local-binding? 
		     reference-structure in-line-optimizing-ok?))
	    as local-name-not-associated-with-role?
	       = (memq (role-and-local-name reference-structure)
		       local-names-not-associated-with-roles)
	    do
	(cond
	  ((and (not provides-binding-for-iteration?)
		(not provides-local-binding?)
		(not local-name-not-associated-with-role?))
	   ;; Build optimized path and return.
	   ;; Generate optimal compilations using "the" form and
	   ;; modify compiled-specific-expression.
	   
	   (multiple-value-bind
	     (new-compiled-specific-expression target-name)
	       (build-optimized-reference-phrase reference-structure)
	     (when (and (not in-line-optimizing-ok?)
			(consp new-compiled-specific-expression))
	       (let ((for-structure
		       (make-for-structure-for-optimized-path
			 new-compiled-specific-expression target-name)))
		 (if previous-for-structure
		     (setf (body previous-for-structure)
			   for-structure)
		     (setq iteration-forms
			   for-structure))
		 (setq insertion-location for-structure))
	       (setf new-compiled-specific-expression target-name))
	     (setf (compiled-specific-expression expression-for-compilation)
		   new-compiled-specific-expression)
	     (return
	       (return-values-from-compile2-name
		 new-compiled-specific-expression
		 iteration-forms insertion-location
		 iteration-forms-for-embedded-expressions?
		 insertion-location-for-embedded-expressions?))))
	  (t
	   (when (not (or (eq (domain-name-needed reference-structure) needed-domain)
			  (reference-structure-for-global-symbol-p reference-structure)))
	     ;; If domain-name-needed is needed-domain, then the name is already bound in an
	     ;; outer for structure (it had better be).  Thus, it would be redundant
	     ;; to make another one.
	     (setq for-structure
		   (make-for-structure-given-reference-structure
		     reference-structure))
	     (cond 
	       (reference-depends-on-existence? 
		(add-for-structure-to-local-binding-forms for-structure))
	       (local-name-not-associated-with-role?
		;; Create action or there-exists local name
		(add-for-structure-to-non-context-binding-forms 
		  for-structure))
	       ((or (compiling-action-p)
		    in-non-top-level-context?)
		(if previous-for-structure
		    (setf (body previous-for-structure)
			  for-structure)
		    (setq iteration-forms
			  for-structure))
		(setq previous-for-structure for-structure
		      insertion-location for-structure))
	       (provides-binding-for-iteration?
		;; This should only occur when compiling rules.
		(cond
		  ((not (boundp 'context-iteration-forms))
		   (compiler-error "\"any\" may only be used in a rule."))
		  (t
		   (setq context-iteration-forms
			 (nconc context-iteration-forms
				(phrase-list for-structure)))))
		;; Note, don't have to change quantifier here.  The fact that
		;; this is in the context indicates to the third pass the final
		;; form to use.
		)
	       (t				       ; provides-local-binding?
		(cond
		  ((not (reference-structure-itself-provides-local-binding?
			  reference-structure))
		   (multiple-value-setq
		     (for-structure-binding-expression for-structure-target-name)
		     (add-to-for-structure-binding-expression 
		       reference-structure for-structure-binding-expression)))
		  (t
		   (when for-structure-binding-expression
		     (multiple-value-setq
		       (for-structure-binding-expression for-structure-target-name)
		       (add-to-for-structure-binding-expression 
			 reference-structure for-structure-binding-expression))
		     (setq for-structure
			   (make-for-structure-for-optimized-path
			     for-structure-binding-expression 
			     for-structure-target-name)))
		   (cond
		     (compiling-expression-p
		      (if previous-for-structure
			  (setf (body previous-for-structure)
				for-structure)
			  (setq iteration-forms
				for-structure))
		      (setq previous-for-structure for-structure
			    insertion-location for-structure))
		     (t
		      (add-for-structure-to-non-context-binding-forms 
			for-structure))))))))))
	    finally
	      (return
		(return-values-from-compile2-name
		  (compiled-specific-expression expression-for-compilation)
		  iteration-forms insertion-location
		  iteration-forms-for-embedded-expressions?
		  insertion-location-for-embedded-expressions?)))))

;; The reference path at this point is a path, not a tree
;; (greatly simplifies things).



(defun reference-depends-on-existence? (reference-structure)
  (unless (and nil
	       (eq (local-name-provided reference-structure) 'SYMBOLIC-VARIABLE)
	       (eq (domain-name-needed  reference-structure) 'c2))
    (loop for existence-origin-reference-structure
	      in reference-structures-originating-from-within-existence-predicate
	  as existence-origin-reference-structure-in-top-level-tree
	  = (get-copy-of-reference-structure-in-highest-level-reference-tree
	      existence-origin-reference-structure)
	  do
      (loop as reference-structure-to-check
	    = (get-copy-of-reference-structure-in-highest-level-reference-tree
		reference-structure)
	       then (reference-structure-providing-needed-domain-name
		      reference-structure-to-check)
	    until (null reference-structure-to-check)
	    do
	(if (eq reference-structure-to-check 
		existence-origin-reference-structure-in-top-level-tree)
	    (return-from reference-depends-on-existence? t)))))
  nil)



(defun compile2-embedded-expression (embedded-expression?)
  (when embedded-expression?
    (multiple-value-bind
      (iteration-forms compiled-specific-embedded-expression? insertion-location)
      (compile2-expression embedded-expression?)
      (multiple-value-setq
	(iteration-forms-for-embedded-expressions? 
	 insertion-location-for-embedded-expressions?)
	(combine-iteration-forms-with-those-of-sub-expression
	  iteration-forms-for-embedded-expressions?
	  insertion-location-for-embedded-expressions?
	  iteration-forms insertion-location))
      compiled-specific-embedded-expression?)))

(defun return-values-from-compile2-name
       (expression iteration-forms insertion-location
	iteration-forms-for-embedded-expressions?
	insertion-location-for-embedded-expressions?)
  (setq expression
	(insert-expressions-into-combined-iteration-forms
	  local-iteration-forms expression local-insertion-location))
  (multiple-value-setq
    (iteration-forms insertion-location)
    (combine-iteration-forms-with-those-of-sub-expression
      iteration-forms insertion-location
      iteration-forms-for-embedded-expressions?
      insertion-location-for-embedded-expressions?))
  (values
    iteration-forms expression insertion-location))



(defun combine-iteration-forms-with-those-of-sub-expression
       (iteration-forms insertion-location
	iteration-forms-for-sub-expression insertion-location-for-sub-expression)
  (if iteration-forms
      (when iteration-forms-for-sub-expression
	  (insert-expression-into-for-structure-body
	    iteration-forms-for-sub-expression
	    insertion-location))
      (setq iteration-forms
	    iteration-forms-for-sub-expression))
  (when iteration-forms-for-sub-expression
      (setq insertion-location
	    insertion-location-for-sub-expression))
  (values iteration-forms insertion-location))





(defun incorporate-iteration-forms-of-expression-and-sub-expression
       (iteration-forms expression insertion-location sub-expression
	function-for-combining-specific-expression-and-sub-expression)
  (if (expression-for-compilation-p sub-expression)
      (multiple-value-bind
	(iteration-forms-for-sub-expression
	 expression-for-insertion 
	 insertion-location-for-sub-expression)
	  (compile2-expression sub-expression)
	(setf expression
	      (funcall 
		function-for-combining-specific-expression-and-sub-expression
		expression expression-for-insertion))
	(multiple-value-setq
	  (iteration-forms insertion-location)
	  (combine-iteration-forms-with-those-of-sub-expression
	    iteration-forms insertion-location
	    iteration-forms-for-sub-expression 
	    insertion-location-for-sub-expression)))
      (setf expression
	    (funcall 
	      function-for-combining-specific-expression-and-sub-expression
	      expression sub-expression)))
  (values iteration-forms expression insertion-location))

(defun combine-sub-expression-with-expression
       (specific-expression specific-sub-expression)
  (nconc specific-expression (phrase-list specific-sub-expression)))



(defun add-for-structure-to-local-binding-forms (for-structure)
  (multiple-value-setq
    (local-iteration-forms local-insertion-location)
    (combine-iteration-forms-with-those-of-sub-expression
      local-iteration-forms local-insertion-location
      for-structure for-structure)))



(defun add-for-structure-to-non-context-binding-forms (for-structure)
  (setq non-context-top-level-binding-forms
	(nconc non-context-top-level-binding-forms
	       (phrase-list for-structure))))

;; This simplification is possible since all "let" forms for
;; the antecedent are currently wrapped around both the 
;; antecedent and the actions.  Note that
;; non-context-top-level-binding-forms is only bound for
;; rules.



(defun compiling-action-p ()
  (and compiling-rule-p (not compiling-antecedent-p)))

;; Instead of using compiling-action-p, consider having the action compilers bind
;; in-non-top-level-context?.


;;; Compile2-designations-from-explicit-iteration-forms is similar to compile2-name
;;; in that it processes reference structures in designations, generating 
;;; corresponding for structures and deciding whether the for structures
;;; should go in context-iteration-forms.  Unlike compile2-name however,
;;; it deals with the designations in designations-from-explicit-iteration-forms
;;; rather than from designations implied within the rule.  It is invoked
;;; directly from compile-rule and returns no values but adds for structures
;;; to context-iteration-forms or to non-context-top-level-binding-forms as appropriate.
;;; Note that references in the explicit for forms will always be bound either
;;; in the context or the top level "let" form.

(defun compile2-designations-from-explicit-iteration-forms ()
  (loop for designation in designations-from-explicit-iteration-forms
	do
    (when (local-reference-finding-paths designation)
      (let ((anchor-reference-structure
	      (car (local-reference-finding-paths designation))))
	(loop with for-structure = nil
	      as reference-structure 
		 = anchor-reference-structure
		 then (if (reference-structures-needing-provided-local-name
			    reference-structure)
			  (car (reference-structures-needing-provided-local-name
				 reference-structure)))
	      until (null reference-structure)
	      do
	  (when (and (not (eq (domain-name-needed reference-structure) needed-domain))
		     (not (reference-structure-for-global-symbol-p reference-structure)))
	    ;; If domain-name-needed is needed-domain, then the name is already bound in an
	    ;; outer for structure (it had better be).  Thus, it would be redundant
	    ;; to make another one.
	       
	    (setq for-structure
		  (make-for-structure-given-reference-structure
		    reference-structure))
	    (cond
	      ((reference-structure-provides-binding-for-iteration? reference-structure)
	       (setq context-iteration-forms
		     (nconc context-iteration-forms
			    (phrase-list for-structure))))
	      (t
	       (add-for-structure-to-non-context-binding-forms for-structure)))))))))


(defun reference-structure-provides-binding-for-iteration? (reference-structure)
  (reference-tree-has-iteration?
    (get-copy-of-reference-structure-in-highest-level-reference-tree
      reference-structure)))

(defun reference-tree-has-iteration? (reference-structure)
  (or (memq (quantifier reference-structure)
	    '(any every every-inverse))
      (loop for needing-reference-structure
		in (reference-structures-needing-provided-local-name
		     reference-structure)
	    thereis (reference-tree-has-iteration? needing-reference-structure))))

(defun reference-structure-provides-local-binding? 
       (reference-structure in-line-optimizing-ok?)
  (or (reference-structure-provides-external-references? reference-structure)

      (not (simple-role-p (role-and-local-name reference-structure)))
      ;; if the role has an explicitly declared local name

      (let ((further-reference-structures-for-binding?
	      (if (reference-structures-needing-provided-local-name
		    reference-structure)
		  (reference-structure-provides-local-binding?
		    (car (reference-structures-needing-provided-local-name
			   reference-structure))       ; designation is always a path
		    in-line-optimizing-ok?))))
	(when (and (not further-reference-structures-for-binding?)
		   in-line-optimizing-ok?)
	  (let ((source-specified-name
		  (get-name-provided-by-role
		    (role-and-local-name reference-structure))))
	    (if (not (eq (local-name-provided reference-structure)
			 source-specified-name))
		;; If compiler has changed or automatically generated local name
		;; and it isn't needed, use original name from source.
		(replace-compiler-generated-local-name-with-name-from-source
		  reference-structure source-specified-name))))
	further-reference-structures-for-binding?)))

;; Note that replace-compiler-generated-local-name-with-name-from-source is used
;; here because reference-structure-provides-local-binding?  can be called more
;; than once for the same reference structure.  Not changing the name at all
;; levels would cause reference-structure-provides-external-references?  to fail.
 


(defun reference-structure-itself-provides-local-binding? (reference-structure)
  (or (not (simple-role-p (role-and-local-name reference-structure)))
      ;; if the role has an explicitly declared local name

      (let ((needing-reference-structures-in-top
	      (reference-structures-needing-provided-local-name
		(get-copy-of-reference-structure-in-highest-level-reference-tree
		  reference-structure))))
	(or 
	  (cdr needing-reference-structures-in-top)
	  (not (eq (length needing-reference-structures-in-top)
		   (length (reference-structures-needing-provided-local-name
			     reference-structure))))))))



(defun replace-compiler-generated-local-name-with-name-from-source
       (reference-structure source-specified-name)
  (change-reference-structures-at-all-higher-levels
    reference-structure 'replace-compiler-generated-local-name-1 
    source-specified-name))

(defun replace-compiler-generated-local-name-1 
       (reference-structure source-specified-name)
  (setf (local-name-provided reference-structure) source-specified-name))




;;; Get-new-role-given-role-and-local-name is useful if the user does not specify
;;; a local name but the compiler generates one or if the compiler generates one
;;; which overides the user specified local name.  In either case, the user specified
;;; role must be modified to reflect the modifications made by the compiler to
;;; the local name.

(defun get-new-role-given-role-and-local-name (role local-name)
  (if (eq local-name 
	  (get-name-provided-by-role role))
      role
      (if (simple-role-p role)
	  (phrase-cons role local-name)
	  (phrase-cons (car role) local-name))))



(defun make-for-structure-given-reference-structure
       (reference-structure)
  (if (not (eq (role-and-local-name reference-structure) focus-range))
      (let* ((for-structure
	       (make-compilation-reclaimable-for-structure))
	     (quantifier
	       (quantifier reference-structure))
	     ;; quantifier can be: 'the, 'any, or 'every.
	     (reference-structure-role-and-local-name
	       (role-and-local-name reference-structure))
	     (for-structure-role-and-local-name
	       (get-new-role-given-role-and-local-name
		 reference-structure-role-and-local-name
		 (local-name-provided reference-structure)))
	     (domain-name-needed
	       (domain-name-needed reference-structure)))
	(if inside-action-iteration-p
	    (setf (for-structure-in-action-p for-structure) t))
	(setf (scope for-structure) 
	      (generate-designation-with-embedded-expression
		quantifier
		for-structure-role-and-local-name
		domain-name-needed
		reference-structure))
	for-structure)))



(defun make-for-structure-for-optimized-path (optimized-path target-name)
  (let* ((for-structure
	   (make-compilation-reclaimable-for-structure)))
    (if inside-action-iteration-p
	(setf (for-structure-in-action-p for-structure) t))
    (setf (scope for-structure) optimized-path
	  (for-structure-binding-name? for-structure) target-name)
    for-structure))



(defun generate-designation-with-embedded-expression 
       (quantifier role domain reference-structure)
  (let ((compiled-embedded-expression?
	  (compile2-embedded-expression 
	    (embedded-expression? reference-structure))))
    (phrase-cons
      quantifier
      (phrase-cons 
	role
	(phrase-cons
	  domain
	  (when compiled-embedded-expression?
	    (phrase-list compiled-embedded-expression?)))))))



;;; Build-optimized-reference-phrase proceeds recursively down a 
;;; reference path building reference-phrases of the form
;;; (the a (the b (the c d)))

(defun build-optimized-reference-phrase 
       (reference-structure &optional dont-check-needing-reference-structures?)
  (let ((domain-name-needed
	  (domain-name-needed reference-structure)))
    (if (null (reference-structures-needing-provided-local-name
		reference-structure))
	(if (not (eq (local-name-provided reference-structure) focus-range))
	    (cond 
	      ((or (reference-structure-for-global-symbol-p reference-structure) 
		   (eq domain-name-needed needed-domain))
	       (values (local-name-provided reference-structure)
		       (local-name-provided reference-structure)))
	      ((rs-for-two-element-designation-with-non-atomic-role-p
		 reference-structure)
	       (values (phrase-list
			 'the (role-and-local-name reference-structure))
		       (local-name-provided reference-structure)))
	      (t
	       (values
		 (generate-designation-with-embedded-expression
		   'the
		   (role-and-local-name reference-structure)
		   domain-name-needed
		   reference-structure)
		 (local-name-provided reference-structure))))
	    ;; See compile-forward-reference-path, 
	    ;; compile-forward-reference-path-for-symbol.

	    (values domain-name-needed domain-name-needed)
	    ;; special case: foo (with focus on foo)
	    )
	(build-optimized-reference-phrase-rec 
	  reference-structure nil dont-check-needing-reference-structures?))))

(defun build-optimized-reference-phrase-rec 
       (reference-structure phrase-so-far 
	dont-check-needing-reference-structures?)
  (let* ((new-role
	   (role-and-local-name reference-structure))
	 ;; New-role should never have a local name (it should be simple) at this point
	 ;; since a "the" expression cannot bind local variables.

	 (domain-name-needed (domain-name-needed reference-structure))
	 (new-phrase
	   (cond 
	     ((null (reference-structure-providing-needed-domain-name
		      reference-structure))
	      (cond
		((eq domain-name-needed needed-domain)
		 new-role)
		((and (not (eq domain-name-needed global-domain))
		      (not (eq (local-name-provided reference-structure)
			       focus-range)))
		 (phrase-list 'the new-role domain-name-needed))
		((rs-for-two-element-designation-with-non-atomic-role-p
		   reference-structure)
		 (phrase-list 'the new-role)
		 ;; Case of two element designation with non-atomic role.
		 )))
	     (t
	      (generate-designation-with-embedded-expression
		'the new-role (or phrase-so-far domain-name-needed)
		reference-structure)))))
    (if (and (not dont-check-needing-reference-structures?)
	     (reference-structures-needing-provided-local-name
	       reference-structure))
	(build-optimized-reference-phrase-rec
	  (car (reference-structures-needing-provided-local-name
		 reference-structure))
	  new-phrase
	  dont-check-needing-reference-structures?)
	(values new-phrase (local-name-provided reference-structure)))))

(defun add-to-for-structure-binding-expression 
       (reference-structure for-structure-binding-expression)
  (if (null for-structure-binding-expression)
      (build-optimized-reference-phrase
	reference-structure t)
      (build-optimized-reference-phrase-rec
	reference-structure for-structure-binding-expression t)))



(defun compile2-logical-operator-expression (expression-for-compilation)
  (let ((operator 
	  (first (compiled-specific-expression
		   expression-for-compilation))))
    (cond
      ((eq operator 'and)
       (compile2-and-expression 
	 expression-for-compilation))
      ((eq operator 'or)
       (compile2-or-expression 
	 expression-for-compilation))
      ((eq operator 'not)
       (compile2-not-expression 
	 expression-for-compilation))
      (t nil))))  ; error





;;; Compile2-and-expression takes as argument expression-for-compilation.

(defun compile2-and-expression (expression-for-compilation)
  (compile2-decoupled-and expression-for-compilation))


;;; Reference-structures-same-p checks if one reference structure is a copy
;;; of the other.

#+unused
(defun reference-structures-same-p
       (reference-structure-1 reference-structure-2)
  (and (eq (local-name-provided reference-structure-1)
	   (local-name-provided reference-structure-2))
       (eq (domain-name-needed reference-structure-1)
	   (domain-name-needed reference-structure-2))
       (eq (quantifier reference-structure-1)
	   (quantifier reference-structure-2))))

(defun compile2-decoupled-and (expression-for-compilation)
  (compile2-comparison-operator-expression expression-for-compilation))


(defun compile2-or-expression
       (expression-for-compilation)
  (compile2-comparison-operator-expression expression-for-compilation))



;;; not expressions


(defun compile2-not-expression
       (expression-for-compilation)
  (compile2-comparison-operator-expression expression-for-compilation))


(defun insert-expression-into-for-structure-body
       (expression-to-be-inserted
	for-structure)
  (setf (body for-structure)
	expression-to-be-inserted))




;;;; Third Pass Compilation

;;; The third pass uses the previously built structures to generate
;;; the actual compiled output form.


;;; Compile3-rule returns two values, context and body.  Body will always
;;; be t if compiling-with-focus? is t (body is only returned for general
;;; compilation.

(defun compile3-rule 
       (compiled-antecedent-2 compiled-consequent-2 
	compiling-with-focus? rule-keyword)
  (let* ((inverse-context
	   (generate-inverse-context-from-inverse-reference-path))
	 (forward-context
	   (loop for for-structure in context-iteration-forms
		 as compiled-iterator 
		    = (compile-forward-context-iterator for-structure)
		 nconc (if compiled-iterator (phrase-list compiled-iterator))))
	 (rule-context (nconc inverse-context forward-context))
	 compiled-antecedent-3
	 compiled-consequent-3
	 (rule-body t))
    (when (not compiling-with-focus?)
      (setq compiled-antecedent-3
	    (compile3-expression compiled-antecedent-2))
      (setq compiled-consequent-3
	    (compile-consequent compiled-consequent-2 'compile3-expression))
      (setq rule-body
	    (phrase-list 
	      rule-keyword compiled-antecedent-3 compiled-consequent-3))
      (if non-context-top-level-binding-forms
	  (setq rule-body
		(wrap-non-context-top-level-binding-forms rule-body nil)))
      
      ;added by SoftServe
      (unless (null assignment-section-forms)
      (setq rule-body (add-or-use-rule-let-section rule-body)))
      ;end of SoftServe changes
      
      )
    (values rule-context rule-body)))

;;; 'reference-structure-is-not-this-rule-nor-this-workspace' takes a
;;; reference-structure as input and check if reference structure contains
;;; two role.
;;;    (ROLE-SERVER THIS-RULE RULE)
;;;    (ROLE-SERVER THIS-WORKSPACE KB-WORKSPACE)
;;; if next reference structure contains either one, then return T, otherwise
;;; return nil

(defun inverse-reference-structure-contains-this-rule-nor-this-workspace
	  (reference-structure)
  (let ((role (get-new-role-given-role-and-local-name
		(role-and-local-name reference-structure)
		(local-name-provided reference-structure))))
	(and (consp role)
	     (consp (cdr role))
	     (consp (cddr role))
	     (eq (car role) 'ROLE-SERVER)
	     (or (and (eq (cadr role) 'THIS-WORKSPACE)
		      (eq (caddr role) 'KB-WORKSPACE))
	     (and (eq (cadr role) 'THIS-RULE)
		      (eq (caddr role) 'RULE))))))
	
	
	
;;; `Generate-inverse-context-from-inverse-reference-path' generates inverse
;;; context iteration forms based on the inverse reference path.
;;; Because these forms are the first in the context, the check whether the 
;;; focus object matches the pattern specified by the rule will be done before 
;;; anything else.  It is, thus, maximally efficient;  the evaluation will be 
;;; aborted immediately if the focus object doesn't match the pattern.
;;; Note that the inverse references are always a path, never a tree.

;;; Inverse context iteration forms can be one of the following:
;;;	(ANY-INVERSE range-binding role short-designation domain-binding)
;;;	(THE-INVERSE range-binding role short-designation domain-binding)
;;;     (THE-INVERSE-NO-BIND range-binding role short-designation domain-binding).

;;; The short designation is in one of the following forms:
;;; 1.  symbol - the symbol is the name of an entity in the kb
;;; 2.  (quantifier class)
;;; The domain binding can be the same as symbol or class in the above
;;; cases but may also be an explicitly declared or compiler generated local
;;; name.  The short designation is used by the inverse role servers and
;;; the result is bound to domain-binding.
;;; For example,
;;;   "if the foo foo1 of any bar and the baz of foo1 ..."
;;; compiled with focus on baz results in the following context iteration form
;;; to bind foo1:
;;;   (the-inverse baz baz (the foo) foo1)
;;; Note also that compile-forward-reference-path inserts an extra
;;; reference structure when the root domain name is a local name referring
;;; to a previous occurrence of the name.  This extra reference structure
;;; is a "needing" root reference structure and thus distinguishes the case
;;; of a local name from the name of an entity in the kb.  Thus
;;;   "the foo of bar1"
;;; ,where bar1 is a local name, is compiled differently from 
;;;   "the foo of bar1"
;;; ,where bar1 is the name of an entity in the kb.  Therefore, in case 1 above,
;;; the symbol which is the short designation is always the name of an entity
;;; in the kb, never a local name.  

(defun generate-inverse-context-from-inverse-reference-path ()
  (loop with short-designation = nil
	with domain-binding = nil
	as reference-structure 
	   = (if pattern-checking-inverse-references
		 (car (reference-structures-needing-provided-local-name
			pattern-checking-inverse-references)))  ; skip focus reference structure
	then next-reference-structure  
	until (or (null reference-structure)
		  (inverse-reference-structure-is-global-end? 
		    reference-structure))
	as next-reference-structure
	   = (car (reference-structures-needing-provided-local-name
		    reference-structure))
	as forward-quantifier  
	   = (forward-reference-quantifier-for-inverse-references
	       reference-structure)
	as role 
	   = (get-new-role-given-role-and-local-name
	       (role-and-local-name reference-structure)
	       (local-name-provided reference-structure))
	as range-binding
	   = (get-name-provided-by-role role)
	as number-left-to-not-bind
	   = number-of-no-binds
	   then (-f number-left-to-not-bind 1)
	do

    (if (not (and (inverse-reference-structure-is-global-end?
		    next-reference-structure)
		  (inverse-reference-structure-for-global-symbol-p 
		    next-reference-structure)
		  ;; The following line was an attempt to get chaining to work
		  ;; with "this workspace."  It had broken all chaining into
		  ;; names.  We will return.  -jra & rdf 3/10/95
;		  (not (rs-for-two-element-designation-with-non-atomic-role-p
;			 next-reference-structure))
		  ;; GENSYMCID-1303: Syntax problem 1
		  (not (inverse-reference-structure-contains-this-rule-nor-this-workspace
			 next-reference-structure))))
	(let ((quantifier-for-short-designation
		(forward-reference-quantifier-for-inverse-references
		  next-reference-structure))
	      (class-or-role-for-short-designation
		(if (rs-for-two-element-designation-with-non-atomic-role-p
		      next-reference-structure)
		    (simple-role-of-role
		      (role-and-local-name next-reference-structure))
		    (atomic-naming-element-of-role
		      (role-and-local-name next-reference-structure))))
	      (local-name-provided-by-next-reference-structure
		(local-name-provided next-reference-structure)))
	  ;; Local-name-provided-by-next-reference-structure may be a class
	  ;; (in which case it is the same as class-for-short-designation),
	  ;; an explicitly declared local name, or a compiler generated local name.
	  ;; If it is a local name, then it is included in the short designation
	  ;; in the previously described format.
	  (setq short-designation
		(phrase-list quantifier-for-short-designation
			     class-or-role-for-short-designation)
		domain-binding
		local-name-provided-by-next-reference-structure))

	;; If next-reference-structure is nil, reference structure is end reference 
	;; structure.  At this point, domain-name-needed can not be global-domain due
	;; to the inverse-reference-structure-is-global-end? check at the beginning
	;; of the loop.  Thus, domain-name-needed is a symbol designating a kb
	;; entity.
	(setq short-designation
	      (domain-name-needed reference-structure)
	      domain-binding
	      short-designation))
	nconc (phrase-list
		(phrase-list
		  (if (eq forward-quantifier 'the) 
		      (if (>f number-left-to-not-bind 0)
			  'the-inverse-no-bind 'the-inverse)
		      'any-inverse)
		  range-binding (simple-role-of-role role)
		  short-designation domain-binding))))

;added by SoftServe

;Declaration: add-or-use-rule-let-section (rule-body)

;Type: Lisp function

;Purpose: wrap rule with the rule-let section 

;Arguments: legacy rule body

;Return behavior: returns rule-body, wrapped in the rule-let section

;Users: compile3-rule

;Side effect: None

;Memory impact: None

(defun add-or-use-rule-let-section (rule-body)
  (if (eq (car rule-body) 'rule-let)
       (let ((new-args (phrase-list
           (loop for using-expression in assignment-section-forms
            nconc
                 (phrase-list 
                  (if (listp (third using-expression))
                      (fourth using-expression)
                      (third using-expression))
                  (phrase-list 'call-procedure (second using-expression) 
					(if (listp (third using-expression))
						(third using-expression)
					        '()
					)))))))
        (phrase-list 'rule-let (nconc new-args (second rule-body)) (third rule-body))) 
       (phrase-list 'rule-let
          (loop for using-expression in assignment-section-forms
            nconc
                (phrase-list
                 (phrase-list 
                  (if (listp (third using-expression))
                      (fourth using-expression)
                      (third using-expression))
                  (phrase-list 'call-procedure (second using-expression) 
					(if (listp (third using-expression))
						(third using-expression)
					        '()
					)))))
        rule-body)))

;end of change  

(defun wrap-non-context-top-level-binding-forms 
       (rule-or-expression-body use-let?)
  (phrase-list 
    (if use-let? 'let 'rule-let)
    (loop for for-structure in non-context-top-level-binding-forms
	  as scope = (scope for-structure)
	  nconc
	  (when (valid-scope-p scope)
	    (phrase-list
	      (let* ((role (second scope))
		     (domain-list (cddr scope))
		     (domain (car domain-list))
		     (name-to-be-bound (get-name-provided-by-role role)))
		;; Domain will never be global-domain except in cases
		;; of roles such as this-workspace where the quantifier
		;; is 'the and there is no domain.
		(phrase-list 
		  name-to-be-bound
		  (if (memq name-to-be-bound
			    local-names-not-associated-with-roles)
		      nil
		      (if (eq domain global-domain)
			  (phrase-list 'the (simple-role-of-role role))
			  (phrase-cons
			    'the
			    (phrase-cons
			      (simple-role-of-role role)
			      (loop for arg-domain in domain-list
				    collect
				    (copy-designation-dropping-local-names
				      arg-domain)
				    using phrase-cons))))))))))
    rule-or-expression-body))

(defun copy-designation-dropping-local-names (designation)
  (cond ((and (listp designation)
	      (>=f (length designation) 2))		; for safety
	 (phrase-list*
	   (first designation)
	   (simple-role-of-role (second designation))
	   (loop for domain in (cddr designation)
		 collect (copy-designation-dropping-local-names
			   domain)
		   using phrase-cons)))
	(t designation)))




(defun valid-scope-p (scope)
  (not (or (not scope)
	   (eq (third scope) needed-domain)
	   (eq (second scope) focus-range))))


(defun compile-forward-context-iterator (for-structure)
  (let ((scope (scope for-structure)))
    (when (valid-scope-p scope)
      (let* ((quantifier (first scope))
	     (role (second scope))
	     (domain (third scope))
	     (domain? (if (not (eq domain global-domain)) domain)))
	(case quantifier
	  (the (generate-forward-context-iterator 'the role domain?))
	  ((any every)
	   (generate-forward-context-iterator 'any role domain?)))))))

(defun generate-forward-context-iterator (operator role domain?)
  (nconc
    (phrase-list
      operator
      (simple-role-of-role role) 
      (get-name-provided-by-role role))
    (if domain? (phrase-list domain?))))


(defun compile3-expression-top (expression)
  (when (and compiling-expression-p
	     wrapper-references-for-left-side-of-formula?)
    (insert-wrapper-references-for-left-side-of-formula expression))
  (when non-context-top-level-binding-forms
    (setq expression
	  (wrap-non-context-top-level-binding-forms expression t)))
  (compile3-expression expression))

;; Insert-wrapper-references-for-left-side-of-formula should not nest
;; "for" structures.  Consider fixing this by using a mechanism similar
;; to the one for the inverse reference path (see
;; generate-inverse-context-from-inverse-reference-path).  This
;; completely by-passes "for" structures and generates the forms from
;; the reference structures directly.  This could be simplified!


;;Gensym-097 BugFix
(defun compile3-quantifier-or-aggregator-if-ok (expression)
  (let* ((aggregator-scope (second expression))
         (reference-structure (local-reference-finding-paths aggregator-scope)))
    (cond
      ((atom reference-structure)
         (return-from compile3-quantifier-or-aggregator-if-ok expression))
      (T
         (setq reference-structure (car reference-structure))
         (if (reference-structure-p reference-structure)
             (compile3-quantifier-or-aggregator expression)
             (return-from compile3-quantifier-or-aggregator-if-ok expression))))))

(defun compile3-expression (expression)
  (cond
    ((expression-for-compilation-p
       expression)
     (compile3-expression 
       (compiled-specific-expression
	 expression)))
    ((or (phrase-structure-p expression)
	 (phrase-sequence-p expression))
     expression)
    ((consp expression)
     (cond
       ((and (cdr expression)
	     (symbolp (cdr expression)))
	;; If non-simple role
	expression)
       (t
	(let ((operator (car expression)))
	  (cond
	    ((or (eq operator 'quote)
		 (phrase-number-p operator))
	     expression)
	    ;;Gensym-097 BugFix
	    ((quantifier-or-aggregator-p operator)
             (compile3-quantifier-or-aggregator-if-ok expression))
	    ((eq operator expression-list-indicator)
	     (if (cdr expression)
		 (compile3-sub-expressions-of-listed-expression (cdr expression))
		 nil-indicator))
	    ((eq operator color-change-indicator)
	     (phrase-cons (compile3-expression (second expression))
			  (compile3-expression (third expression))))
	    ((memq operator '(let the))
	     (nconc
	       (phrase-list (first expression) (second expression))
	       (when (third expression)
		 (phrase-list
		   (compile3-expression (third expression))))
	       (when (fourth expression)   ; embedded expression
		 (phrase-list
		   (compile3-expression (fourth expression))))))
	    (t
	     (compile3-sub-expressions-of-listed-expression expression)))))))
    ((symbolp expression) expression)
    ((or (text-string-p expression)
	 (phrase-number-p expression))
     expression)
    ((for-structure-p expression)
     (compile3-for-structure expression))))

;; Nil-indicator is used to prevent compile3-expression from omitting nils that
;; should be emitted according to the template (see also
;; compile1-sub-expressions-according-to-template).



(defun compile3-sub-expressions-of-listed-expression (expression)
  (loop for sub-expression in expression 
	nconc (let ((compiled-expression
		      (compile3-expression sub-expression)))
		(when compiled-expression
		  (cond
		    ((eq compiled-expression nil-indicator)
		     (phrase-list nil))
		    ((and (consp compiled-expression)
			  (eq (car compiled-expression)
			      color-changes-indicator))
		     (cdr compiled-expression))
		    (t
		     (phrase-list compiled-expression)))))))



(defun compile3-quantifier-or-aggregator (expression)
  (let* ((reference-structure-for-aggregator-scope
	   (get-relevent-reference-structure-for-aggregator-scope
	     (second expression)))
	 (new-role 
	   (get-new-role-given-role-and-local-name
	     (role-and-local-name reference-structure-for-aggregator-scope)
	     (local-name-provided reference-structure-for-aggregator-scope)))
	 (domain (domain-name-needed reference-structure-for-aggregator-scope))
	 (domain? (if (not (eq domain global-domain)) domain))
	 (new-aggregator-scope
	   (nconc
	     (phrase-list
	       (simple-role-of-role new-role) 
	       (get-name-provided-by-role new-role))
	     (if domain? 
		 (phrase-list
		   domain?)))))
    (phrase-list 
      (first expression) new-aggregator-scope 
      (compile3-expression (third expression)))))

(defun get-relevent-reference-structure-for-aggregator-scope (aggregator-scope)
  (let ((reference-structure
	  (car (local-reference-finding-paths aggregator-scope))))
    (or (car (reference-structures-needing-provided-local-name reference-structure))
	reference-structure)))

;; Ignore "needed" root reference structure.



(defun compile3-for-structure (for-structure)
  (let ((scope (scope for-structure)))
    (cond
      ((not (valid-scope-p scope))
       (compile3-expression
	 (body for-structure)))			; skip
      (t
       (let ((new-scope
	       (if (eq (third scope) global-domain)
		   (phrase-list (second scope))
		   (cdr scope)))
	     (quantifier (first scope)))
	 (case quantifier
	   ((nil)				; need parens here to distinguish from empty set
	    ;; Special case of let being used to bind local name
	    ;; when local name is used for class name in left side
	    ;; of a formula.  
	    ;; See also insert-wrapper-references-for-left-side-of-formula.
	    (phrase-cons
	      'let
	      (multiple-value-bind
		(binding-list next-expression-to-compile)
		  (generate-let-binding-list-from-nested-for-structures
		    for-structure nil)
		(phrase-cons
		  binding-list
		  (phrase-list (compile3-expression next-expression-to-compile))))))
	   (t
	    (compile3-for-structure-according-to-quantifier
	      for-structure quantifier scope new-scope))))))))

(defun compile3-for-structure-according-to-quantifier
       (for-structure quantifier scope new-scope)
  (case quantifier
    (the
     (if (eq (third scope) global-domain)
	 (setf (cddr scope) nil))
     (phrase-cons
       (if (for-structure-in-action-p for-structure)
	   'let-action
	   'let)
       (multiple-value-bind
	 (binding-list next-expression-to-compile)
	   (generate-let-binding-list-from-nested-for-structures
	     for-structure nil)
	 (phrase-cons
	   binding-list
	   (phrase-list (compile3-expression next-expression-to-compile))))))
    (every
     (phrase-list 
       (if (for-structure-in-action-p for-structure) 'every 'for-all)
       (let ((role (first new-scope))
	     (domain? (second new-scope)))
	 (phrase-cons (simple-role-of-role role)
		      (phrase-cons (get-name-provided-by-role role)
				   (if domain? (phrase-list domain?)))))
       (compile3-expression
	 (body for-structure))))
    
    (any
     #+development ;-rdf, 12/16/94
     (when (consp (car new-scope))
       (break "This will cause a compiler-bug"))
     (phrase-cons 
       (if (for-structure-in-action-p for-structure)
	   'every
	   'there-exists)
       (phrase-cons 
	 new-scope
	 (phrase-list 
	   (compile3-expression
	     (body for-structure))
	   ))))))

(defun generate-let-binding-list-from-nested-for-structures 
       (for-structure binding-list-so-far)
  (let* ((scope (scope for-structure))
	 (quantifier (first scope))
	 (role-and-local-name? (second scope))
	 (name-provided (or (for-structure-binding-name? for-structure)
			    (get-name-provided-by-role role-and-local-name?)))
	 (body (body for-structure)))
    (cond
      ((not (or (null quantifier)
		(eq quantifier 'the)))
       (values binding-list-so-far for-structure)
       ;; Return if for structure for non-let binding.
       )
      (t
       (cond
	 ((null quantifier)
	  (setq binding-list-so-far
		(phrase-list (phrase-list (second scope) 
					  (compile3-expression (third scope))))))
	 (t
	  (if (not (simple-role-p role-and-local-name?))
	      (setf (second scope)
		    (car role-and-local-name?)))      ; get rid of local name
	  (setq binding-list-so-far
		(nconc binding-list-so-far
		       (phrase-list (phrase-list name-provided 
						 (compile3-expression scope)))))))
       (if (for-structure-p body)
	   (generate-let-binding-list-from-nested-for-structures
	     body binding-list-so-far)
	   (values binding-list-so-far body))))))




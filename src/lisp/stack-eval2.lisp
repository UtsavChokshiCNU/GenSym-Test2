;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB") 

;;;; Module STACK-EVAL2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Chris Morel




;; In QUERIES

(declare-forward-reference do-query-evaluation-for-rule-restriction function)
(declare-forward-reference do-query-evaluation-for-with-status function)
(declare-forward-reference do-query-evaluation-for-containing function)

;;; In interop.lisp
;[tam.srogatch][2010-11-22]: Allow callling g2nke_count_history_datapoints_matching_op
;  and g2nke_count_history_datapoints_matching_op
;  from a KB function (not only from a procedure)
(declare-forward-reference  kb-g2nke-count-history-matching-op  function)
(declare-forward-reference  kb-g2nke-count-history-matching-op-and-eventflag  function)





;;;; Existence Expression (Quantifier) Evaluators




;;; Note that existential quantification over an empty set of conditions
;;; is false, universal quantification over the same is true, summation is
;;; 0, product is 1, average, minimum and maximum are undefined.

;;; The calculation for the expiration time of the following expression needs to
;;; be reviewed.  It had a bug where the expiration returned would be 0 for
;;; cases where the role iterated over an empty set.  For the moment it will
;;; return NEVER in that case.  Further though, we need to examine whether the
;;; expiration should be minimized or maximized through sets of expression
;;; values which do not exceed the truth-threshold (I think min is right), we
;;; need to review the decision to directly use whatever expiration we get back
;;; from the first expression to exceed the truth-threshold (this is probably
;;; right), and we need to determine whether it should return NEVER or
;;; gensym-time in the empty role case (I think it should be NEVER for static
;;; roles, and gensym-time for dynamic roles, but then we would have to review
;;; ALL of our role expirations and use of them -- it uses NEVER now).  -jra
;;; 10/17/89

;;; After reviewing the comment above, I believe that we have the following
;;; situation.  Nearly all of our roles can be considered "dynamic" now, so the
;;; idea of a static role is obsolete.  All of our roles currently use NEVER as
;;; the expiration, and changes to these roles are propagated on an event
;;; triggered basis.  I think this conforms to our earlier decisions that we do
;;; not "backward chain" to establish relations, and that this is the correct
;;; handling of expirations of roles.  So, the empty set case in there exists
;;; should return NEVER as its expiration.  The case where the logical
;;; expression is evaluated but never returns true should minimize the
;;; expirations of all evaluation attempts (like the case where AND returns
;;; false), since the false value is based on a combination of all the
;;; evaluations.  The case where the logical expression does return TRUE should
;;; use the expiration of the TRUE evaluation alone (discarding any previously
;;; accumulated expirations), since the truth of there exists is entirely
;;; dependent on the one case which did return true.  (Part of the justification
;;; of this last statement is based in my mind on the order independence of role
;;; service, though this is not true of list or array iteration.  Hmmm.)  So, I
;;; still believe that the decisions made in the discussion of the paragraph
;;; above are correct.  -jra 5/24/91


;;; The `THERE-EXISTS-LITERAL stack-evaluator' evaluates a logical expression
;;; that returns truth if at least one item meets the specified criteria.
;;; Otherwise, falsity is returned.  The item that satisfies the the condition
;;; of the there-exists expression can be referred to outside of the expression.

;;; The arguments to this expression are a scope of the form (role var-spot
;;; domain) and a logical-expression.

;;; This evaluator is implemented as a stack-node-instruction which emits its
;;; own instructions specifically.

;;; If the expression contains a possible indexed-attribute optimization, a new
;;; role, which can do the indexed-attribute-optimization, is added in place of
;;; the current role.  Also, the attribute expression from the logical
;;; expression is substituted in place of the original domain list, which is
;;; empty in this case.

;; Note that as of version 4.0, this expression allows attributes specified by a
;; class-qualified-name, as well as by an attribute name, to be indexed.  - cpm,
;; 2/22/94

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.  This expression is not available in actions.  Expirations of all
;;; aggregators are described in the comments above by jra.

(def-special-form-converter there-exists-literal (expression)
  (gensym-dstruct-bind ((nil scope logical-expression)
		       expression)
    (let* ((compiling-procedures?
	     (frame-of-class-p *current-computation-frame* 'procedure))
	   (role (car scope))
	   (domain-list (if compiling-procedures?
			    (cdr scope)
			    (cddr scope)))
	   (simple-role (simple-role-of-role role))
	   (type? (if (symbolp simple-role)
		      (make-class-type-specification simple-role)
		      (type-specification-of-role simple-role)))
	   (local-name?
	     (if compiling-procedures?
		 (get-explicitly-specified-local-name-of-role-if-any role)
		 (second scope)))
	   (naming-element? (atomic-naming-element-of-role role))
	   (binding (or local-name? (phrase-list 'the naming-element?)))
	   (instruction-node
	     (make-stack-node-instruction 'there-exists-literal nil)))
      
      (cond
	((not (or local-name? naming-element?))
	 (compiler-bug
	   "there exists parse converter"
	   "The iteration reference in ~NE cannot be compiled, since there is ~
            no local name or class name in the designation which can be used ~
            for later reference."
	   expression)
	 nil)
	((null type?)
	 (compiler-bug
	   "there exists parse converter"
	   "The iteration reference in ~NE could not be compiled because no ~
            type can be deduced from the reference."
	   expression)
	 (setq type? 'item-or-datum)
	 (phrase-push
	   (phrase-cons
	     binding (generate-new-stack-frame-var-spot 'item-or-datum))
	   expression-bound-local-names))
	(t
	 (let* ((var-spot? (resolve-stack-name-reference binding))
		(var-spot-type nil)
		(possible-indexed-attribute-expression?
		  (expression-may-use-indexed-attribute-p expression))
		(possible-indexed-attribute?
		  (when possible-indexed-attribute-expression?
		    (second (second possible-indexed-attribute-expression?))))
		(indexed-attribute-new-domain?
		  (when possible-indexed-attribute?
		    ;; The new domain for the indexed-attribute role.
		    (third possible-indexed-attribute-expression?))))
	   (cond ((valid-var-spot-p var-spot?)
		  (setq var-spot-type
			(var-spot-type
			  var-spot? lexically-visible-code-bodies)))
		 (t
		  ;; var-spot? is the binding, which is <name> or (the <class>).
		  (setq var-spot? nil)))
	   (cond ((and (null var-spot?)
		       compiling-procedures?
		       local-name?)
		  (setq var-spot-type type?)
		  (setq var-spot?
			(generate-new-variable-spot type? local-name?)))
		 ((null var-spot?)
		  (setq var-spot-type type?)
		  (setq var-spot?
			(generate-new-stack-frame-var-spot var-spot-type))
		  (setq expression-bound-local-names
			(phrase-cons (phrase-cons
				       binding
				       var-spot?)
				     expression-bound-local-names)))
		 (t
		  (when (or (null var-spot-type)
			    (not (type-specifications-could-intersect-p
				   type? var-spot-type)))
		    (compiler-error
		      "Type mismatch between the local name ~A and the type ~
                       ~NT referenced by the THERE EXISTS form iteration."
		      binding type?))))
	   (setf (stack-node-argument-nodes instruction-node)
		 (stack-cons
		   (convert-expression-to-stack-node-tree logical-expression)
		   (if possible-indexed-attribute?
		       ;; domain-list is empty for indexed-attribute.
		       (if indexed-attribute-new-domain?
			   (stack-list
			     (convert-expression-to-stack-node-tree
			       indexed-attribute-new-domain?))
			   nil)
		       (loop for domain in domain-list
			     collect
			     (convert-expression-to-stack-node-tree domain)
					using stack-cons))))
	   (let ((actual-role
		   (if possible-indexed-attribute?
		       ;; Add the optimized indexed-attribute role.
		       (phrase-list
			 'indexed-attribute possible-indexed-attribute?
			 simple-role)
		       simple-role)))
	     (setf (stack-node-instruction-extra-info instruction-node)
		   (phrase-list actual-role var-spot? var-spot-type))))))
      instruction-node)))



;; The function `prepare-preferred-instruction-chooser-if-indexed-attribute'
;; should be called at the beginning of preferred instruction choosers that may
;; be an indexed-attribute.  An indexed-attribute flag should have been added to
;; the extra-info in a special-form converter.  This function is called even by
;; the choosers of some instruction that cannot be indexed, since they contain
;; the indexed flag and this needs to be removed.
;;
;; NOTE: This function is now OBSOLETE.  The new indexed-attribute role is added
;; in the special form converter as necessary.  The free references of the old
;; and new role are recorded in the instruction choosers.  Previously, both of
;; these things were done in the chooser.  Having choosers produce this type of
;; side-effect caused problems when the choosers are called more than once.  -
;; cpm, 2/22/94



;;; The preferred instruction chooser for `there-exists-literal' can use the
;;; chooser for all aggregators, passing truth-value as the iterated expression
;;; type.  First the role is modified if the indexed-attribute optimization is
;;; possible

;; Are the phrase-conses of the old role reclaimed?? cpm, 6/26/91

;; No, and they don't have to be, because all phrase-conses are automatically
;; reclaimed at the end of a compile, even if they are "garbage" from the
;; perspective of the compilation result.  -jra 7/16/91

(declare-instruction-for-optimizer
  'there-exists-literal
  ;; can do anything
  '(evaluate-first-arg-last
    aggregator))

(def-preferred-instruction-chooser there-exists-literal
  (declare (ignore extra-info))
  (aggregator-instruction-chooser
    stack-node-instruction required-type 'truth-value 'truth-value nil 3))




;;; The preferred instruction chooser for aggregators chooses instructions and
;;; types on its argument nodes, and then sets its own return value, depending
;;; on whether any of its arguments can return unknown.  It generates a variable
;;; spot for the role continuation and may generate an iteration local variable
;;; and two new variable spots to hold global expiration and accumulated
;;; expiration when its result may be unknown.  This chooser expects the
;;; argument nodes to be the iterated expression, and the remainder of the list
;;; contains domain stack node trees.  The generate-iteration-local-var?
;;; argument indicates whether a local variable is needed to old the accumulated
;;; value.  This is useful for maximum, minimum, and aggregated-average.

;;; The type of this local var is given by generate-iteration-local-var?,
;;; unless this is t, which means
;;; "use the type of the first of the argument nodes". This allows maximum
;;; and minimum to accumulate the max or min in a variable of the appropriate
;;; type, while letting aggregated-average (which uses the extra variable to
;;; count the entries for a later division) to always use integers.
;;; -alatto, 6/15/99

;;; This chooser function records free references for the original role if it
;;; has been replaced by the indexed-attribute role.

;;; Note that in cases where an empty iteration implies a return value of
;;; no-item, then the return type of the aggregator will always include no-item.

(defun aggregator-instruction-chooser
    (stack-node-instruction required-type result-type iteration-type
			    generate-iteration-local-var? length-of-persistent-info)
  #+development
  (unless (or (=f length-of-persistent-info 2)
	      (=f length-of-persistent-info 3))
    (break "unknown value for length-of-persistent-info ~a"
	   length-of-persistent-info))
  (let* ((extra-info (stack-node-instruction-extra-info stack-node-instruction))
	 (extra-info-length (length extra-info))
	 (role (first extra-info))
	 (unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (domain-node-list (cdr argument-nodes))
	 (unknown-argument? nil)
	 (required-domain-type-list (when (not (symbolp role))
				      (required-domain-types-of-role
					(role-name-of-role role)))))
    ;; Record free references of the role.
    (cond ((and (symbolp role) (null domain-node-list))
	   (record-free-reference 'class role))
	  (t
	   (when (and (consp role) (eq (first role) 'indexed-attribute))
	     (let ((original-role (third role)))
	       ;; Record free references of the original role since it has been
	       ;; replaced.
	       (cond ((symbolp original-role)
		      ;; The domain-list of the orignal role should be empty in
		      ;; this case and is therefore not tested since a new
		      ;; domain has been substituted.
		      (record-free-reference 'class original-role))
		     (t
		      (record-free-references-of-role original-role)))))
	   (record-free-references-of-role role)))
    ;; Start with the domain arguments.
    (when (/=f (length required-domain-type-list) (length domain-node-list))
      (write-compiler-error
	(twrite-string "The role ")
	(print-role role)
	(tformat " requires ~a arguments, but instead received ~a"
		 (length required-domain-type-list)
		 (length domain-node-list)))
      (setq required-domain-type-list
	    (loop repeat (length domain-node-list)
		  collect 'item-or-datum
		    using phrase-cons)))

    (loop for domain-node-cons on domain-node-list
	  for required-domain-type in required-domain-type-list
	  for actual-type =
	  (maybe-add-no-item-implies-unknown
	    (maybe-add-unknown
	      (maybe-add-no-item required-domain-type no-item-allowed?)
	      unknown-allowed?)
	    no-item-implies-unknown-allowed?)
	  do
      (setf (car domain-node-cons)
	    (choose-stack-node-instructions-and-types
	      (car domain-node-cons)
	      actual-type))
      (when (type-specification-subtype-p
	      '(unknown-datum)
	      (stack-node-value-type (car domain-node-cons)))
	(setq unknown-argument? t)))

    ;; Iteration expression argument.  Note that in the expression below we
    ;; believe that when the iteration type is datum or a subtype of datum, then
    ;; the return type of the expression can never include no-item.  This is
    ;; true because of the way that the datum coercion operations change no-item
    ;; to unknown.  -jra & cpm 11/8/91
    (setf (car argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (car argument-nodes)
	    (maybe-add-no-item-implies-unknown
	      (maybe-add-no-item 
		(maybe-add-unknown iteration-type unknown-allowed?)
		no-item-allowed?)
	      no-item-implies-unknown-allowed?)))
    (when (type-specification-subtype-p
	    '(unknown-datum)
	    (stack-node-value-type (car argument-nodes)))
      (setq unknown-argument? t))

    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-unknown result-type unknown-argument?))

    ;; If any of the arguments can be unknown, then the result type can contain
    ;; unknown, and we need to generate the extra variables to hold the global
    ;; and accumulated expirations.
    (cond
      (unknown-argument?
       ;; Variables to hold the iteration, global expiration, and expression
       ;; expirations.
       (cond
	 ((=f extra-info-length (+f length-of-persistent-info 4))
	  ;; we don't have to do anything (4 items are added here)
	  )
	 (t
	  (cond 
	    ;; we have not run yet so no list alteration is necessary
	    ((=f length-of-persistent-info extra-info-length)
	     )
	    ((=f length-of-persistent-info 2)
	     (setf extra-info (phrase-list (first extra-info) (second extra-info))))
	    ((=f length-of-persistent-info 3)
	     (setf extra-info
		   (phrase-list (first extra-info) (second extra-info)
				(third extra-info))))
	    (t
	     #+development
	     (break "unknown value for length-of-persistent-info ~a"
		    length-of-persistent-info)))
	  
	  
	  (setf (stack-node-instruction-extra-info stack-node-instruction)
		(nconc
		  extra-info
		  (phrase-list
		    (generate-new-stack-frame-var-spot
		      (make-type-specification-for-iteration-state))
		    (when generate-iteration-local-var?
		      (generate-new-stack-frame-var-spot
			;; iteration type
			(if (eq generate-iteration-local-var? t)
			    (stack-node-value-type (car argument-nodes))
			    generate-iteration-local-var?)))
		    (generate-new-stack-frame-var-spot 'datum)
		    (generate-new-stack-frame-var-spot 'datum)))))))
      (t
       (cond
	 ((=f extra-info-length (+f length-of-persistent-info 2))
	  ;; we don't have to do anything (2 items are added here)
	  )
	 (t
	  (cond 
	    ;; we have not run yet so no list alteration is necessary
	    ((=f length-of-persistent-info extra-info-length)
	     )
	    ((=f length-of-persistent-info 2)
	     (setf extra-info (phrase-list (first extra-info) (second extra-info))))
	    ((=f length-of-persistent-info 3)
	     (setf extra-info
		   (phrase-list (first extra-info) (second extra-info)
				(third extra-info))))
	    (t
	     #+development
	     (break "unknown value for length-of-persistent-info ~a"
		    length-of-persistent-info)))

	  (setf (stack-node-instruction-extra-info stack-node-instruction)
		(nconc
		  extra-info
		  (phrase-list
		    (generate-new-stack-frame-var-spot
		      (make-type-specification-for-iteration-state))
		    (when generate-iteration-local-var?
		      (generate-new-stack-frame-var-spot
			;; iteration type
			(if (eq generate-iteration-local-var? t)
			    (stack-node-value-type (car argument-nodes))
			    generate-iteration-local-var?))))))))))))




;;; The stack node instruction emitter for THERE-EXISTS-LITERAL emits code
;;; differently depending upon whether or not any of its argument nodes can
;;; return unknown.  If the arguments cannot, then this instruction need not
;;; collect expirations from its arguments, or check at all whether or not they
;;; are known.

;;; The stack node arguments list contains the iterated expression, and the
;;; remainder of the argument list may contain domain stack node trees.  The
;;; stack node extra-info contains a role, var-spot, var-spot-type, and
;;; continuation variable and optionally may contain expiration and
;;; cached-global expiration variables.  Note that the role is normally a
;;; simple-role, unless the role has been modified to serve possible
;;; indexed-attributes.

;;; The instruction will serve values from the role, store each value into the
;;; binding local variable, evaluate the logical-expression after each binding
;;; is made, and accumulate on the stack the minimum truth-value of the
;;; logical-expression.  The expiration local variable will contain the minimum
;;; expiration of the evaluations.

;;; There are several possible outcomes for this instruction.

;;; 1. If no domain is found when one is required, either the return value is
;;; unknown if it is allowed or an error is signaled.
;;; 2. When there are no values to serve, i.e., there-exists of an empty set,
;;; the statement returns false and restores the global expiration (since
;;; minimizing the global expiration with NEVER is the global).
;;; 3. If the logical-expression has evaluated to true, the logical
;;; expression's truth-value is left on the stack and its expiration is
;;; minimized with the global expiration.
;;; 4. If the logical expression never evaluates to true, the maximum certainty
;;; is left on the stack and the minimum expiration of all evaluations of the
;;; logical expression is minimized with the global expiration.

(def-expiration-special-form there-exists-literal)

(def-stack-node-instruction-emitter there-exists-literal
  (gensym-dstruct-bind ((role value-spot value-spot-type continuation-spot
			     nil expiration-var? cached-global-expiration-var?)
		       extra-info)
    (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	   (logical-expression (first argument-nodes))
	   (domain-list? (cdr argument-nodes))
	   (role-type? (if (symbolp role)
			   (make-class-type-specification role)
			   (type-specification-of-role role)))
	   (unknown-allowed? (not (null cached-global-expiration-var?)))
	   ;; A default logical expression is a empty `such that' (true), in this
	   ;; case we don't need to return full search results as only the first
	   ;; result was used. -- Chun Tian (binghe), 2012/09/16
	   (default-logical-expression?
	    (and (eq (stack-node-operation logical-expression) 'push-constant)
		 (evaluation-boolean-is-true-p
		  (stack-node-instruction-extra-info logical-expression))))
	   (domain-ok-tag (generate-new-goto-tag))
	   (value-served-tag (generate-new-goto-tag))
	   (known-value-tag (generate-new-goto-tag))
	   (true-value-tag (generate-new-goto-tag))
	   (end-of-instruction-tag (generate-new-goto-tag)))

      (when unknown-allowed?
	;; Cache the global expiration, and reset it to never.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration)
	;; Initialize the accumulated expiration variable with the reset
	;; expiration.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?))
      
      ;; Push false as initial accumulated certainty.
      (call-stack-instruction-emitter push-constant
	byte-code-stream
	(make-evaluation-truth-value falsity))
      
      ;; Serve the first value of role and the continuation.  If a value is not
      ;; served, the open role iteration branches to the end of instruction tag.
      (cond (domain-list?
	     (loop for domain in domain-list?
		   for possible-unknown-domain? =
		       (type-specification-subtype-p
			 '(unknown-datum)
			 (stack-node-value-type stack-node-instruction))
		   for count from 1
		   do
	       (emit-stack-node-tree byte-code-stream domain)
		   finally
		     (when possible-unknown-domain?
		       (call-stack-instruction-emitter branch-long-if-known
			 byte-code-stream domain-ok-tag)
		       ;; Pop all values except for the initial accumulated
		       ;; certainty.
		       (call-stack-instruction-emitter pop-values byte-code-stream count)
		       (call-stack-instruction-emitter branch-long
			 byte-code-stream end-of-instruction-tag)
		       (register-tag-in-byte-code-stream
			 byte-code-stream domain-ok-tag))
		     (call-stack-instruction-emitter open-role-iteration
		       byte-code-stream role end-of-instruction-tag
		       ;; the `count' argument to `open-role-iteration' is actually
		       ;; ignored, can only be 1. now we reuse it by setting to zero (0)
		       ;; when doing a partial search. -- Chun Tian (binghe), 2012/09/16
		       (if default-logical-expression? 0 count))))
	    (t 
	     (call-stack-instruction-emitter open-role-iteration-no-domain
	       byte-code-stream role end-of-instruction-tag)))
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream continuation-spot)

      ;; First or next value for the role has been served.
      (register-tag-in-byte-code-stream
	byte-code-stream value-served-tag)
      
      (unless (and role-type?
                   (type-specification-subtype-p role-type? value-spot-type))
        (call-stack-instruction-emitter type-check byte-code-stream value-spot-type))
      
      ;; Evaluate the iteration expression with the role value in the var-spot.
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream value-spot)
      (emit-stack-node-tree byte-code-stream logical-expression)
      
      ;; Branch if the value is known.  Otherwise, replace it with falsity.
      (when unknown-allowed?
	(call-stack-instruction-emitter branch-long-if-known byte-code-stream known-value-tag)
	(emit-instruction-byte-code byte-code-stream 'pop)
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-truth-value falsity))
	(register-tag-in-byte-code-stream
	  byte-code-stream known-value-tag))

      ;; Save the maximum result of the logical expression.
      (emit-instruction-byte-code byte-code-stream 'fuzzy-or)

      (emit-instruction-byte-code
	byte-code-stream 'push-copy-of-top-of-stack)

      ;; Branches if the logical-expression is true.  Does not minimize the
      ;; current expiration with the accumulated expiration variable.
      (call-stack-instruction-emitter branch-long-if-true byte-code-stream true-value-tag)

      ;; Minimize the current expiration with the accumulated expiration variable
      ;; and reset the current expiration.
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration))
      
      ;; Serve the next value of role.
      (call-stack-instruction-emitter serve-next-iteration-value
	byte-code-stream continuation-spot end-of-instruction-tag)
      (call-stack-instruction-emitter branch-long byte-code-stream value-served-tag)
      
      (register-tag-in-byte-code-stream
	byte-code-stream end-of-instruction-tag)
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration))
      (register-tag-in-byte-code-stream
	byte-code-stream true-value-tag)
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration))
      (call-stack-instruction-emitter close-iteration byte-code-stream continuation-spot))))




;;; The `FOR-EVERY-LITERAL stack-evaluator' evaluates a logical expression and
;;; returns truth if all items of a class meet the specified criteria.  If there
;;; are no items in the class, truth is also returned.  If there are items of
;;; the class that do not meet the criteria, falsity is returned.

;;; The item that satisfies the the condition of the for-every expression can
;;; not be referred to outside of the expression.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.  This expression is not available in actions.

;;; This evaluator is implemented as a stack-node-instruction which emits its
;;; own instructions specifically.

(declare-instruction-for-optimizer
  `for-every-literal
  '(evaluate-first-arg-last
    no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    aggregator))

(def-special-form-converter for-every-literal (expression)
  (aggregator-special-form-converter expression))



;;; The function `aggregator-special-form-converter' is used to convert all the
;;; aggregator special forms, except for there-exists-literal which can
;;; reference an existing var-spot.  A local name is bound onto
;;; expression-bound-local-names with a newly generated var-spot.  This is done
;;; since the value in the var-spot can not be referenced outsided of this
;;; expression, unlike "there-exists".

;;; If the expression (currently only "there-exists" or "count") contains a
;;; possible indexed-attribute optimization, the role is replaced by the role
;;; which can do this optimization.  Also, the attribute expression from the
;;; logical expression is substituted in place of the original domain list,
;;; which is empty in this case.

;; Note that as of version 4.0, this expression allows attributes specified by a
;; class-qualified-name, as well as by an attribute name, to be indexed.  - cpm,
;; 2/22/94

(defun aggregator-special-form-converter (expression)
  (gensym-dstruct-bind ((stack-node-operation
			 scope iteration-expression)
		       expression)
    (let* ((compiling-procedures?
	     (frame-of-class-p *current-computation-frame* 'procedure))
	   (role (car scope))
	   (domain-list (if compiling-procedures?
			    (cdr scope)
			    (cddr scope)))
	   (simple-role (simple-role-of-role role))
	   (type? (if (symbolp simple-role)
		      (make-class-type-specification simple-role)
		      (type-specification-of-role simple-role)))
	   (local-name?
	     (if compiling-procedures?
		 (get-explicitly-specified-local-name-of-role-if-any role)
		 (second scope)))
	   (naming-element? (atomic-naming-element-of-role role))
	   (binding (or local-name? (phrase-list 'the naming-element?)))
	   (instruction-node
	     (make-stack-node-instruction stack-node-operation nil)))

      (cond
	((not (or local-name? naming-element?))
	 (compiler-bug
	   "aggregator parse converter"
	   "The iteration reference in ~NE cannot be compiled, since there is ~
            no local name or class name in the designation which can be used ~
            as a binding reference."
	   expression)
	 nil)
	((null type?)
	 (compiler-bug
	   "aggregator parse converter"
	   "The iteration reference in ~NE could not be compiled because no ~
            type can be deduced from the reference."
	   expression)
	 (phrase-push
	   (phrase-cons
	     binding (generate-new-stack-frame-var-spot 'item-or-datum))
	   expression-bound-local-names))
	(t
	 (let* ((var-spot (generate-new-stack-frame-var-spot type?))
		(possible-indexed-attribute-expression?
		  (expression-may-use-indexed-attribute-p expression))
		(possible-indexed-attribute?
		  (when possible-indexed-attribute-expression?
		    (second (second possible-indexed-attribute-expression?))))
		(indexed-attribute-new-domain?
		  (when possible-indexed-attribute?
		    ;; The new domain for the indexed-attribute role.
		    (third possible-indexed-attribute-expression?))))
	   (setq expression-bound-local-names
		 (phrase-cons (phrase-cons binding var-spot)
			      expression-bound-local-names))
	   (setf (stack-node-argument-nodes instruction-node)
		 (stack-cons
		   (convert-expression-to-stack-node-tree iteration-expression)
		   (if possible-indexed-attribute?
		       ;; domain-list is empty for indexed-attribute.
		       (if indexed-attribute-new-domain?
			   (stack-list
			     (convert-expression-to-stack-node-tree
			       indexed-attribute-new-domain?))
			   nil)
		       (loop for domain in domain-list
			     collect (convert-expression-to-stack-node-tree domain)
					using stack-cons))))
	   (let ((actual-role
		   (if possible-indexed-attribute?
		       ;; Add the optimized indexed-attribute role.
		       (phrase-list
			 'indexed-attribute possible-indexed-attribute?
			 simple-role)
		       simple-role)))
	     (setf (stack-node-instruction-extra-info instruction-node)
		   (phrase-list actual-role var-spot))))))
	instruction-node)))



;;; The preferred instruction chooser for `for-every-literal' can directly use
;;; the chooser for all aggregators, passing truth-value as the iterated
;;; expression type.

(def-preferred-instruction-chooser for-every-literal
  (declare (ignore extra-info))
  (aggregator-instruction-chooser
    stack-node-instruction required-type 'truth-value 'truth-value nil 2))




;;; The stack node instruction emitter for FOR-EVERY-LITERAL emits code
;;; differently depending upon whether or not any of its argument nodes can
;;; return unknown.  If the arguments cannot, then this instruction need not
;;; collect expirations from its arguments, or check at all whether or not they
;;; are known.

;;; The stack node arguments list contains the iterated expression, and the
;;; remainder of the argument list may contain domain stack node trees.  The stack
;;; node extra-info contains a simple role, var-spot, and continuation variable
;;; and optionally may contain expiration and cached-global expiration variables.

;;; The instruction will serve values from the role, store each value into the
;;; binding local variable, evaluate the logical-expression after each binding
;;; is made, and accumulate on the stack the maximum truth-value of the
;;; logical-expression.  The expiration local variable will contain the minimum
;;; expiration of the evaluations.

;;; There are several possible outcomes for this instruction.

;;; 1. If no domain is found when one is required, either the return value is
;;; unknown if it is allowed or an error is signaled.
;;; 2. When there are no values to serve, i.e., for-every of an empty set,
;;; the statement returns TRUE and restores the global expiration (since
;;; minimizing the global expiration with NEVER is the global).
;;; 3. If the logical-expression has evaluated to FALSE, the logical
;;; expression's truth-value is left on the stack and its expiration is
;;; minimized with the global expiration.
;;; 4. If the logical expression never evaluates to FALSE, the minimum
;;; certainty is left on the stack and the minimum expiration of all evaluations
;;; of the logical expression is minimized with the global expiration.

;;; This emitter is similar to the emitter for there-exists-literal, but differs
;;; the above outcomes.  Also, this instruction does not need to test the served
;;; role value with the var-spot type.

(def-expiration-special-form for-every-literal)

(def-stack-node-instruction-emitter for-every-literal
  (gensym-dstruct-bind ((simple-role value-spot continuation-spot nil
				    expiration-var?
				    cached-global-expiration-var?)
		       extra-info)
    (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	   (logical-expression (first argument-nodes))
	   (domain-list? (cdr argument-nodes))
	   (unknown-allowed? (not (null cached-global-expiration-var?)))
	   (domain-ok-tag (generate-new-goto-tag))
	   (value-served-tag (generate-new-goto-tag))
	   (known-value-tag (generate-new-goto-tag))
	   (false-value-tag (generate-new-goto-tag))
	   (end-of-instruction-tag (generate-new-goto-tag)))

      (when unknown-allowed?
	;; Cache the global expiration, and reset it to never.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration)
	;; Initialize the accumulated expiration variable with the reset
	;; expiration.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?))

      ;; Push truth as initial accumulated certainty.
      (call-stack-instruction-emitter push-constant
	byte-code-stream
	(make-evaluation-truth-value truth))

      ;; Serve the first value of role and the continuation.  If a value is not
      ;; served, the open role iteration branches to the end of instruction tag.
      (cond (domain-list?
	     (loop for domain in domain-list?
		   for possible-unknown-domain? =
		       (type-specification-subtype-p
			 '(unknown-datum)
			 (stack-node-value-type stack-node-instruction))
		   for count from 1
		   do
	       (emit-stack-node-tree byte-code-stream domain)
		   finally
		     (when possible-unknown-domain?
		       (call-stack-instruction-emitter branch-long-if-known
			 byte-code-stream domain-ok-tag)
		       ;; Pop all values except for the initial accumulated
		       ;; certainty.
		       (call-stack-instruction-emitter pop-values byte-code-stream count)
		       (call-stack-instruction-emitter branch-long
			 byte-code-stream end-of-instruction-tag)
		       (register-tag-in-byte-code-stream
			 byte-code-stream domain-ok-tag))
		     (call-stack-instruction-emitter open-role-iteration
		       byte-code-stream simple-role end-of-instruction-tag
		       count)))
	    (t 
	     (call-stack-instruction-emitter open-role-iteration-no-domain
	       byte-code-stream simple-role end-of-instruction-tag)))
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream continuation-spot)
      
      ;; First or next value for the role has been served.
      (register-tag-in-byte-code-stream
	byte-code-stream value-served-tag)
      
      ;; Evaluate the iteration expression with the role value in the var-spot.
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream value-spot)
      (emit-stack-node-tree byte-code-stream logical-expression)
      
      ;; Branch if the value is known.  Otherwise, replace it with truth.
      (when unknown-allowed?
	(call-stack-instruction-emitter branch-long-if-known byte-code-stream known-value-tag)
	(emit-instruction-byte-code byte-code-stream 'pop)
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-truth-value truth))
	(register-tag-in-byte-code-stream
	  byte-code-stream known-value-tag))

      ;; Save the minimum result of the logical expression.
      (emit-instruction-byte-code byte-code-stream 'fuzzy-and)

      (emit-instruction-byte-code
	byte-code-stream 'push-copy-of-top-of-stack)

      ;; Branches if the logical-expression is false.  Does not minimize the
      ;; current expiration with the accumulated expiration variable.
      (call-stack-instruction-emitter branch-long-if-false
	byte-code-stream false-value-tag)
      
      ;; Minimize the current expiration with the accumulated expiration variable
      ;; and reset the current expiration.
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration))
      
      ;; Serve the next value of role.
      (call-stack-instruction-emitter serve-next-iteration-value
	byte-code-stream continuation-spot end-of-instruction-tag)
      (call-stack-instruction-emitter branch-long byte-code-stream value-served-tag)
      
      (register-tag-in-byte-code-stream
	byte-code-stream end-of-instruction-tag)
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration))
      (register-tag-in-byte-code-stream
	byte-code-stream false-value-tag)
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration))
      (call-stack-instruction-emitter close-iteration byte-code-stream continuation-spot))))




;;; The `EXISTS stack-evaluator' returns truth if the designation refers to a
;;; servable (e.g., active) item or temporary constant.  Otherwise, it returns
;;; falsity.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.

;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;; Exists also needs a form writer, bug in 2.0, 2.1  -jra 11/14/90

(def-special-form-converter exists (expression)
  (let ((instruction-node (make-stack-node-instruction 'exists nil)))
    (setf (stack-node-argument-nodes instruction-node)
	  (stack-list
	    (convert-expression-to-stack-node-tree (second expression))))
    instruction-node))


(declare-optimizer-stack-instruction exists)


;;; The preferred instruction chooser for EXISTS chooses instructions and types
;;; on its arguments, and then sets its own return value.

(def-preferred-instruction-chooser exists
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(no-item-implies-unknown-allowed?
	  (type-specification-subtype-p '(no-item-implies-unknown) required-type)))
    (setf (first argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (first argument-nodes)
	    (maybe-add-no-item-implies-unknown
	      (maybe-add-unknown
		'(or item-or-datum (no-item))
		unknown-allowed?)
	      no-item-implies-unknown-allowed?)))
    
    (setf (stack-node-value-type stack-node-instruction)
	  (if (type-specification-subtype-p
		'(unknown-datum)
		(stack-node-value-type (first argument-nodes)))
	      '(or boolean (unknown-datum))
	      'boolean))))


(def-expiration-special-form exists)

(def-stack-node-instruction-emitter exists
  (declare (ignore extra-info))
  (emit-stack-node-tree
    byte-code-stream
    (first (stack-node-argument-nodes stack-node-instruction)))
  (call-stack-instruction-emitter funcall-instruction byte-code-stream 'exists))



;;; Instruction 37, the `EXISTS funcalled stack-instruction' is used to
;;; implement the evaluator for EXISTS.  The instruction accepts one argument,
;;; an item, datum, or no-item.  The instruction returns true if the argument
;;; is an item or datum.  Otherwise falsity is returned.

(def-funcalled-instruction exists (37 all 1 1 nil pprint-exists-instruction)
  (let* ((item-or-datum-arg? (stack-arg 0))
	 (result
	   (cond
	     ((null item-or-datum-arg?)
	      (make-evaluation-truth-value falsity))
	     ;; Now that procedures can refer to inactive items and will be passing
	     ;; said inactive items to procedures that cannot it is reasonable
	     ;; to have exists return false in the case that the item does exist
	     ;; but the procedure involved just cannot refer to it.
	     ((and (framep item-or-datum-arg?)
		   (not (serve-item-p item-or-datum-arg?)))
	      (make-evaluation-truth-value falsity))
	     (t
	      (make-evaluation-truth-value truth)))))
    (reclaim-if-evaluation-value item-or-datum-arg?)
    (setf (svref local-stack top-of-stack) result)
    nil))






;;;; Evaluators for Expressions Over Sets (Aggregators)





;;; The following aggregators stack evaluators are arithmetic expressions that
;;; compute the sum, product, average, maximum, minimum, and total count over a
;;; set of items.  These evaluators are special forms that emit their own
;;; instructions.




;;; The function `emit-aggregator-instruction' is used to emit code for the some
;;; of the aggregators that compute arithmetic expressions over sets.  The
;;; emitted code is similar for all the aggregators.  If there are no domains,
;;; unknown is returned if allowed or an error is signaled.  If the role value
;;; set is empty, then the default value for the operator is returned.  The
;;; default for sum is 0, product is 1, and count is 0.

;;; This function emits code for sum, product, and count.  It does not emit for
;;; there-exists-literal, for-every-literal, maximum, minimum, or
;;; aggregated-average.

(defun emit-aggregator-instruction (stack-node-instruction
				    byte-code-stream extra-info)
  (gensym-dstruct-bind ((simple-role value-spot continuation-spot nil
				    expiration-var?
				    cached-global-expiration-var?)
		       extra-info)
    (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	   (unknown-allowed? (not (null cached-global-expiration-var?)))
	   (operator (stack-node-operation stack-node-instruction))
	   (count-aggregator? (eq operator 'count))
	   (accumulator-operator? (case operator
				    ((sum count) '+)
				    (product '*)
				    ;; Error case signaled below.
				    (t nil)))
	   (iteration-expression (first argument-nodes))
	   (accumulator-operator-type?
	     (when accumulator-operator?
	       (if (eq operator 'count)
		   (stack-node-value-type stack-node-instruction)
		   (stack-node-value-type iteration-expression))))
	   (accumulator-operator-type-without-unknown?
	     (if accumulator-operator-type?
		 (if (union-type-specification-p accumulator-operator-type?)
		     (type-specification-minus-type
		       accumulator-operator-type? '(unknown-datum))
		     accumulator-operator-type?)
		 (compiler-bug "aggregator emitter"
			       "Missing accumular operator type.")))
	   (empty-role-value?
	     (case operator
	       ((sum count)
		(if (eq accumulator-operator-type-without-unknown? 'float)
		    0.0
		    0))
	       (product
		(if (eq accumulator-operator-type-without-unknown? 'float)
		    1.0
		    1))
	       (t nil)))
	   (domain-list? (cdr argument-nodes))
	   (domain-ok-tag (generate-new-goto-tag))
	   (value-served-tag (generate-new-goto-tag))
	   (count-tag? (when count-aggregator?
			 (generate-new-goto-tag)))
	   (known-value-tag? (when unknown-allowed?
			       (generate-new-goto-tag)))
	   (unknown-value-tag? (when unknown-allowed?
				 (generate-new-goto-tag)))
	   (end-of-instruction-tag (generate-new-goto-tag)))

      (when unknown-allowed?
	;; Cache the global expiration, and reset it to never.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration)
	;; Initialize the accumulated expiration variable with the reset
	;; expiration.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?))

      ;; Push initial accumulated value.
      (call-stack-instruction-emitter push-constant
	byte-code-stream
	(if empty-role-value?
	    (make-evaluation-quantity empty-role-value?)
	    (make-evaluation-symbol nil)))

      ;; Serve the first value of role and the continuation.  If a value is not
      ;; served, the open role iteration branches to the end of instruction tag.
      (cond (domain-list?
	     (loop for domain in domain-list?
		   for possible-unknown-domain? =
		       (type-specification-subtype-p
			 '(unknown-datum)
			 (stack-node-value-type stack-node-instruction))
		   for count from 1
		   do
	       (emit-stack-node-tree byte-code-stream domain)
		   finally
		     (when possible-unknown-domain?
		       (call-stack-instruction-emitter branch-long-if-known
			 byte-code-stream domain-ok-tag)
		       ;; Pop all values except for the initial accumulated
		       ;; value.
		       (call-stack-instruction-emitter pop-values byte-code-stream count)
		       (call-stack-instruction-emitter branch-long
			 byte-code-stream end-of-instruction-tag)
		       (register-tag-in-byte-code-stream
			 byte-code-stream domain-ok-tag))
		     (call-stack-instruction-emitter open-role-iteration
		       byte-code-stream simple-role end-of-instruction-tag
		       count)))
	    (t 
	     (call-stack-instruction-emitter open-role-iteration-no-domain
	       byte-code-stream simple-role end-of-instruction-tag)))
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream continuation-spot)

      ;; First or next value for the role has been served.
      (register-tag-in-byte-code-stream
	byte-code-stream value-served-tag)

      ;; Evaluate the iteration expression with the role value in the var-spot.
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream value-spot)
      (emit-stack-node-tree byte-code-stream iteration-expression)

      ;; If the value is not known pop it and skip the accumulation operator.
      (when unknown-allowed?
	(call-stack-instruction-emitter branch-long-if-known byte-code-stream known-value-tag?)
	(emit-instruction-byte-code byte-code-stream 'pop)
	(call-stack-instruction-emitter branch-long byte-code-stream unknown-value-tag?)
	(register-tag-in-byte-code-stream
	  byte-code-stream known-value-tag?))

      ;; Accumulate the result of the iteration expression.
      (cond ((null count-aggregator?)
	     (emit-operator-of-type
	       byte-code-stream accumulator-operator?
	       accumulator-operator-type-without-unknown?))
	    (t (call-stack-instruction-emitter branch-long-if-not-true
		 byte-code-stream count-tag?)
	       ;; Count only when the expression is true.
	       (call-stack-instruction-emitter push-constant
		 byte-code-stream (make-evaluation-integer 1))
	       (emit-operator-of-type
		 byte-code-stream accumulator-operator?
	       accumulator-operator-type-without-unknown?)
	       (register-tag-in-byte-code-stream
		 byte-code-stream count-tag?)))

      (when unknown-allowed?
	(register-tag-in-byte-code-stream
	  byte-code-stream unknown-value-tag?)
	;; Minimize the current expiration with the accumulated expiration
	;; variable and reset the current expiration.
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration))

      ;; Serve the next value of role.
      (call-stack-instruction-emitter serve-next-iteration-value
	byte-code-stream continuation-spot end-of-instruction-tag)
      (call-stack-instruction-emitter branch-long byte-code-stream value-served-tag)

      (register-tag-in-byte-code-stream
	byte-code-stream end-of-instruction-tag)
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration))
      (call-stack-instruction-emitter close-iteration byte-code-stream continuation-spot))))



;;; The function `emit-max-or-min-aggregator-instruction' is used to emit code
;;; for the max or min aggregators.  It expects the argument of the instruction
;;; to contain the iteration expression and a domain list.  The extra info
;;; instruction slot contains the role, role value local variable spot,
;;; continuation local variable spot, and optionally expiration and cached
;;; global expiration variable spots.  If the expiration variable spots are not
;;; provided the instruction can not return unknown.

;;; The emitted code is similar to that of the other aggregators.  If there are
;;; no domains when required or if the role value set is empty, there is no
;;; default numeric return value.  Either no-item is returned, if this is
;;; allowed, otherwise an error is signaled.

(declare-instruction-for-optimizer
  'sum
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    evaluate-first-arg-last
    aggregator))

(declare-instruction-for-optimizer
  'product
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    evaluate-first-arg-last
    aggregator))

(declare-instruction-for-optimizer
  `count
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    evaluate-first-arg-last
    aggregator))

(defun emit-max-or-min-aggregator-instruction
       (stack-node-instruction byte-code-stream extra-info)
  (gensym-dstruct-bind ((simple-role value-spot continuation-spot
				    iteration-var expiration-var?
				    cached-global-expiration-var?)
		       extra-info)
    (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	   (unknown-allowed? (not (null cached-global-expiration-var?)))
	   (no-item-allowed?
	     (type-specification-subtype-p
	       '(no-item)
	       (stack-node-required-value-type stack-node-instruction)))
	   (operator (stack-node-operation stack-node-instruction))
	   (accumulator-operator? (case operator
				    (maximum 'max)
				    (minimum 'min)
				    (t nil)))
	   (iteration-expression (first argument-nodes))
	   (accumulator-operator-type?
	     (when accumulator-operator?
	       (stack-node-value-type iteration-expression)))
	   (accumulator-operator-type-without-unknown?
	     (if accumulator-operator-type?
		 (type-specification-minus-type
		   (type-specification-minus-type 
		     accumulator-operator-type?
		     '(no-item))
		   '(unknown-datum))
		 (compiler-bug "max or min aggregator emitter"
			       "Missing accumular operator type.")))
	   (domain-list? (cdr argument-nodes))
	   (domain-ok-tag (generate-new-goto-tag))
	   ;; No value tag: missing domain or no values served.
	   (no-value-tag (generate-new-goto-tag))
	   (value-served-tag (generate-new-goto-tag))
	   (no-previous-value-tag (generate-new-goto-tag))
	   (accumulate-tag (generate-new-goto-tag))
	   (known-value-tag? (when unknown-allowed?
			       (generate-new-goto-tag)))
	   (unknown-value-tag? (when unknown-allowed?
				 (generate-new-goto-tag)))
	   (push-accumulator-tag (generate-new-goto-tag))
	   (end-of-instruction-tag (generate-new-goto-tag)))

      (when unknown-allowed?
	;; Cache the global expiration, and reset it to never.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration)
	;; Initialize the accumulated expiration variable with the reset
	;; expiration.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?))

      ;; Initialize the local var (may be a stack-frame var or var spot
      ;; depending on the compiler) because the var may not be nil.  This would
      ;; happen when this is a var-spot and when the expression is called more
      ;; than once, for example, within a FOR loop.
      (call-stack-instruction-emitter push-nones byte-code-stream 1)
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream iteration-var)

      ;; Serve the first value of role and the continuation.  If a value is not
      ;; served, the open role iteration branches to the no-value tag.
      ;;
      ;; Note that the domains can return no-item only in the cases where the
      ;; required type of the aggregator as a whole allows a no-item return
      ;; type.  If it was not allowed, the required type of the compilation of
      ;; the domains would not have included no-item, and then the domain type
      ;; could not include no-item.  -jra 11/8/91

      (cond (domain-list?
	     (loop with some-unknown-domain? = nil
		   for domain in domain-list?
		   for domain-type =
		       (stack-node-value-type stack-node-instruction)
		   for possible-unknown-domain? =
		       (type-specification-subtype-p
			 '(unknown-datum) domain-type)
		   for possible-no-item-domain? =
		       (type-specification-subtype-p
			 '(no-item) domain-type)
		   for count from 1
		   do
	       (setq some-unknown-domain?
		     (or some-unknown-domain? possible-unknown-domain?))
	       (emit-stack-node-tree byte-code-stream domain)

	       ;; Test for NO-ITEM domain when necessary.  Unknown and item
	       ;; (i.e., not no-item) domains are left on the stack.  Unknown
	       ;; domain is tested at the end of the loop.
	       (when possible-no-item-domain?
		 (let ((domain-known-tag (generate-new-goto-tag))
		       (leave-domain-on-stack-tag (generate-new-goto-tag)))
		   (when possible-unknown-domain?
		     (call-stack-instruction-emitter branch-long-if-known
		       byte-code-stream domain-known-tag)
		     (call-stack-instruction-emitter branch-long
		       byte-code-stream leave-domain-on-stack-tag))
		   
		   ;; Domain was known.  Test for no-item.
		   (register-tag-in-byte-code-stream
		     byte-code-stream domain-known-tag)
		   (emit-instruction-byte-code
		     byte-code-stream 'push-copy-of-top-of-stack)
		   (emit-instruction-byte-code
		     byte-code-stream 'none-test)
		   (call-stack-instruction-emitter branch-long-if-not-true
		     byte-code-stream leave-domain-on-stack-tag)
		   
		   ;; Domain was no-item.  Pop all the domains off the
		   ;; stack and branch to the no-value-tag.
		   (call-stack-instruction-emitter pop-values byte-code-stream count)
		   (call-stack-instruction-emitter branch-long byte-code-stream no-value-tag)
		   
		   ;; Leave domain on stack - either not known or not no-item.
		   (register-tag-in-byte-code-stream
		     byte-code-stream leave-domain-on-stack-tag)))

		   finally
		     (when some-unknown-domain?
		       ;; Unknown domain test.
		       (call-stack-instruction-emitter branch-long-if-known
			 byte-code-stream domain-ok-tag)

		       ;; Unknown domain.  Pop all domain values.  Push a dummy
		       ;; return value.  The stack-expiration is nil.
		       (call-stack-instruction-emitter pop-values byte-code-stream count)
		       (call-stack-instruction-emitter push-nones byte-code-stream 1)
		       (call-stack-instruction-emitter branch-long
			 byte-code-stream end-of-instruction-tag)

		       ;; Domain OK.
		       (register-tag-in-byte-code-stream
			 byte-code-stream domain-ok-tag))

		     (call-stack-instruction-emitter open-role-iteration
		       byte-code-stream simple-role no-value-tag
		       count)))
	    (t 
	     (call-stack-instruction-emitter open-role-iteration-no-domain
	       byte-code-stream simple-role no-value-tag)))
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream continuation-spot)

      (call-stack-instruction-emitter branch-long byte-code-stream value-served-tag)

      ;; Missing domain or no role values served.
      (register-tag-in-byte-code-stream byte-code-stream no-value-tag)

      ;; When no-item is an allowed value of this operation, both the case of a
      ;; domain returning no-item, and the case of no values being served by the
      ;; iteration will end up here.  In both of these cases, we should minimize
      ;; the cached global expiration with the current expiration and push none,
      ;; thereby returning no-item from this operation.  When no-item is not
      ;; allowed, the only case which can end up here is the case of no values
      ;; being served by the iteration, and we should issue an appropriate error
      ;; message.
      (cond (no-item-allowed?
	     ;; return value of no-item.
	     (call-stack-instruction-emitter push-nones byte-code-stream 1)
	     (call-stack-instruction-emitter branch-long
	       byte-code-stream end-of-instruction-tag))
	    (t
	     (call-stack-instruction-emitter push-constant
	       byte-code-stream (make-evaluation-symbol 'error))
	     (call-stack-instruction-emitter push-constant
	       byte-code-stream
	       (if (eq operator 'maximum)
		   (make-evaluation-text
		     "The maximum over an empty set of values has no value.  This was not an expected result."
		     )
		   (make-evaluation-text
		     "The minimum over an empty set of values has no value.  This was not an expected result."
		     )))
	     (emit-instruction-byte-code byte-code-stream 'signal-error)))

      ;; First or next value for the role has been served.
      (register-tag-in-byte-code-stream
	byte-code-stream value-served-tag)

      ;; Evaluate the iteration expression with the role value in the var-spot.
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream value-spot)
      (emit-stack-node-tree byte-code-stream iteration-expression)

      ;; If the value is not known pop it and skip the accumulation operator.
      (when unknown-allowed?		
	(call-stack-instruction-emitter branch-long-if-known byte-code-stream known-value-tag?)
	(emit-instruction-byte-code byte-code-stream 'pop)
	(call-stack-instruction-emitter branch-long byte-code-stream unknown-value-tag?)
	(register-tag-in-byte-code-stream
	  byte-code-stream known-value-tag?))

      ;; Accumulate the result of the iteration expression.
      ;;
      ;; First, test for no previous value.
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream iteration-var)
      (emit-instruction-byte-code byte-code-stream 'push-copy-of-top-of-stack)
      (emit-instruction-byte-code byte-code-stream 'none-test)
      (call-stack-instruction-emitter branch-long-if-true
	byte-code-stream no-previous-value-tag)

      ;; Take the max or min.
      (emit-operator-of-type
	byte-code-stream accumulator-operator?
	accumulator-operator-type-without-unknown?)
      (call-stack-instruction-emitter branch-long byte-code-stream accumulate-tag)

      ;; No previous value.  Pop the NIL accumulated value and leave the new
      ;; value on the stack.
      (register-tag-in-byte-code-stream
	byte-code-stream no-previous-value-tag)
      (emit-instruction-byte-code byte-code-stream 'pop)

      ;; Pop the accumulated or current value into the iteration variable.
      (register-tag-in-byte-code-stream
	byte-code-stream accumulate-tag)
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream iteration-var)

      (when unknown-allowed?
	;; Minimize the current expiration with the accumulated expiration
	;; variable and reset the current expiration.
	(register-tag-in-byte-code-stream
	  byte-code-stream unknown-value-tag?)
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration))

      ;; Serve the next value of role.
      (call-stack-instruction-emitter serve-next-iteration-value
	byte-code-stream continuation-spot push-accumulator-tag)
      (call-stack-instruction-emitter branch-long byte-code-stream value-served-tag)

      ;; Push the accumulated min or max.
      (register-tag-in-byte-code-stream
	byte-code-stream push-accumulator-tag)
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream iteration-var)

      ;; End of instruction.  Either the accumulated min/max value, no-item, or
      ;; unknown value is on the stack.  Minimize the cached expirations.
      (register-tag-in-byte-code-stream
	byte-code-stream end-of-instruction-tag)
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration))
      (call-stack-instruction-emitter close-iteration byte-code-stream continuation-spot))))



;;; The function `emit-aggregated-average-instruction' is used to emit code for
;;; the aggregated-average evaluator.  It expects the argument nodes to contain
;;; the iteration expression and a domain list.  The extra info instruction slot
;;; should contain the role, role value variable spot, the continuation variable
;;; spot, the accumulator variable spot, and optionally, expiration variable and
;;; cached global expiration variable spots.

;;; Before computing the average, the count of the values is maintained in the
;;; count variable spot and the sum is computed on the stack.

;; Note that in version 3.0 and 4.0 betas, the final sum was coerced to a float,
;; if necessary, before computing the average.  This is no longer the case.  If
;; each integer value could be represented as a fixnum, but the sum was too
;; large, this would result in an arithmetic overflow.  Now, each value is
;; coerced to a float, when necessary, before being added to the accumulator.
;; Note that the fix is within this emitter.  - cpm, 2/7/95

;;; The emitted code is similar to that of the other aggregators.  If there are
;;; no domains when required or if the role value set is empty, there is no
;;; default numeric return value.  Either no-item is returned, if this is
;;; allowed, otherwise an error is signaled.

(declare-instruction-for-optimizer
  `aggregated-average
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    evaluate-first-arg-last
    aggregator))

(defun emit-aggregated-average-instruction
       (stack-node-instruction byte-code-stream extra-info)
  (gensym-dstruct-bind ((simple-role value-spot continuation-spot
				    count-var expiration-var?
				    cached-global-expiration-var?)
		       extra-info)
    (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	   (unknown-allowed? (not (null cached-global-expiration-var?)))
	   (no-item-allowed?
	     (type-specification-subtype-p
	       '(no-item)
	       (stack-node-required-value-type stack-node-instruction)))
	   (iteration-expression (first argument-nodes))
	   (iteration-type (stack-node-value-type iteration-expression))
	   (iteration-type-without-unknown
	     (if (union-type-specification-p iteration-type)
		 (type-specification-minus-type
		   iteration-type '(unknown-datum))
		 iteration-type))
	   (iteration-float-type? (eq iteration-type-without-unknown 'float))
	   (initial-value 0.0)
	   (initial-count-value 0)
	   (count-value 1)
	   (domain-list? (cdr argument-nodes))
	   (domain-ok-tag (generate-new-goto-tag))
	   ;; No value tag: missing domain or no values served.
	   (no-value-tag (generate-new-goto-tag))
	   (value-served-tag (generate-new-goto-tag))
	   (known-value-tag? (when unknown-allowed?
			       (generate-new-goto-tag)))
	   (unknown-value-tag? (when unknown-allowed?
				 (generate-new-goto-tag)))
	   (compute-average-if-known-tag (generate-new-goto-tag))
	   (end-of-instruction-tag (generate-new-goto-tag)))

      (when unknown-allowed?
	;; Cache the global expiration, and reset it to never.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration)
	;; Initialize the accumulated expiration variable with the reset
	;; expiration.
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?))

      ;; Initialize the count variable.
      (call-stack-instruction-emitter push-constant
	byte-code-stream (make-evaluation-quantity initial-count-value))
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream count-var)

      ;; Initialize the sum on the stack.
      (call-stack-instruction-emitter push-constant
	byte-code-stream (make-evaluation-quantity initial-value))

      ;; Serve the first value of role and the continuation.  If a value is not
      ;; served, the open role iteration branches to the no-value tag.
      ;;
      ;; Note that the domains can return no-item only in the cases where the
      ;; required type of the aggregator as a whole allows a no-item return
      ;; type.  If it was not allowed, the required type of the compilation of
      ;; the domains would not have included no-item, and then the domain type
      ;; could not include no-item.  -jra 11/8/91
      (cond (domain-list?
	     (loop with some-unknown-domain? = nil
		   for domain in domain-list?
		   for domain-type =
		       (stack-node-value-type stack-node-instruction)
		   for possible-unknown-domain? =
		       (type-specification-subtype-p
			 '(unknown-datum) domain-type)
		   for possible-no-item-domain? =
		       (type-specification-subtype-p
			 '(no-item) domain-type)
		   for count from 1
		   do
	       (setq some-unknown-domain?
		     (or some-unknown-domain? possible-unknown-domain?))
	       (emit-stack-node-tree byte-code-stream domain)
	       ;; Test for NO-ITEM domain when necessary.  Unknown and item
	       ;; (i.e., not no-item) domains are left on the stack.  Unknown
	       ;; domain is tested at the end of the loop.
	       (when possible-no-item-domain?
		 (let ((domain-known-tag (generate-new-goto-tag))
		       (leave-domain-on-stack-tag (generate-new-goto-tag)))
		   (when possible-unknown-domain?
		     (call-stack-instruction-emitter branch-long-if-known
		       byte-code-stream domain-known-tag)
		     (call-stack-instruction-emitter branch-long
		       byte-code-stream leave-domain-on-stack-tag))

		   ;; Domain was known.  Test for no-item.
		   (register-tag-in-byte-code-stream
		     byte-code-stream domain-known-tag)
		   (emit-instruction-byte-code
		     byte-code-stream 'push-copy-of-top-of-stack)
		   (emit-instruction-byte-code
		     byte-code-stream 'none-test)
		   (call-stack-instruction-emitter branch-long-if-not-true
		     byte-code-stream leave-domain-on-stack-tag)

		   ;; Domain was no-item.  Pop all the domains off the
		   ;; stack and branch to the no-value-tag.
		   (call-stack-instruction-emitter pop-values byte-code-stream count)
		   (call-stack-instruction-emitter branch-long byte-code-stream no-value-tag)

		   ;; Leave domain on stack - either not known or not no-item.
		   (register-tag-in-byte-code-stream
		     byte-code-stream leave-domain-on-stack-tag)))
		   finally
		     (when some-unknown-domain?
		       ;; Unknown domain test.
		       (call-stack-instruction-emitter branch-long-if-known
			 byte-code-stream domain-ok-tag)

		       ;; Unknown domain.  Pop all domain values.
		       (call-stack-instruction-emitter pop-values byte-code-stream count)
		       (call-stack-instruction-emitter branch-long
			 byte-code-stream end-of-instruction-tag)

		       ;; Domain OK.
		       (register-tag-in-byte-code-stream
			 byte-code-stream domain-ok-tag))
		     (call-stack-instruction-emitter open-role-iteration
		       byte-code-stream simple-role no-value-tag
		       count)))
	    (t 
	     (call-stack-instruction-emitter open-role-iteration-no-domain
	       byte-code-stream simple-role no-value-tag)))
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream continuation-spot)

      (call-stack-instruction-emitter branch-long byte-code-stream value-served-tag)

      ;; Missing domain or no role values served.
      (register-tag-in-byte-code-stream
	byte-code-stream no-value-tag)

      ;; When no-item is an allowed value of this operation, both the case of a
      ;; domain returning no-item, and the case of no values being served by the
      ;; iteration will end up here.  In both of these cases, we should minimize
      ;; the cached global expiration with the current expiration, pop the
      ;; accumulator off the stack, and push none, thereby returning no-item
      ;; from this operation.  When no-item is not allowed, the only case which
      ;; can end up here is the case of no values being served by the iteration,
      ;; and we should issue an appropriate error message.

      ;; For the moment, we'll let the type check of the value catch the
      ;; no-item.  We'll emit a better message later, but hopefully before
      ;; release.  -jra 11/8/91.  The error is now being signaled here.  cpm,
      ;; 11/12/91.
      (cond (no-item-allowed?
	     (call-stack-instruction-emitter pop-values byte-code-stream 1)
	     (call-stack-instruction-emitter push-nones byte-code-stream 1)
	     (call-stack-instruction-emitter branch-long
	       byte-code-stream end-of-instruction-tag))
	    (t
	     ;; Signal an error instead of returning no-item.
;	     (call-stack-instruction-emitter pop-values byte-code-stream 1)
;	     (call-stack-instruction-emitter push-nones byte-code-stream 1)
;	     (call-stack-instruction-emitter branch-long
;	       byte-code-stream end-of-instruction-tag)

	     (call-stack-instruction-emitter push-constant
	       byte-code-stream (make-evaluation-symbol 'error))
	     (call-stack-instruction-emitter push-constant
	       byte-code-stream
	       (make-evaluation-text
		 "The average over an empty set of values has no value.  This was not an expected result."
		 ))
	     (emit-instruction-byte-code byte-code-stream 'signal-error)))

      ;; First or next value for the role has been served.
      (register-tag-in-byte-code-stream
	byte-code-stream value-served-tag)

      ;; Evaluate the iteration expression with the role value in the var-spot.
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream value-spot)
      (emit-stack-node-tree byte-code-stream iteration-expression)

      ;; If the value is not known pop it and skip the accumulation operator.
      ;; Unknown is only tested when it's allowed.
      (when unknown-allowed?
	(call-stack-instruction-emitter branch-long-if-known byte-code-stream known-value-tag?)
	(emit-instruction-byte-code byte-code-stream 'pop)
	(call-stack-instruction-emitter branch-long byte-code-stream unknown-value-tag?)
	(register-tag-in-byte-code-stream
	  byte-code-stream known-value-tag?))

      ;; Accumulate the result of the iteration expression on the stack.
      (unless iteration-float-type?
	(emit-instruction-byte-code byte-code-stream 'type-check-float))
      (emit-operator-of-type byte-code-stream '+ 'float)
      ;; Increment the counter.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream count-var)
      (call-stack-instruction-emitter push-constant
	byte-code-stream (make-evaluation-quantity count-value))
      (emit-operator-of-type byte-code-stream '+ 'integer)
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream count-var)

      (when unknown-allowed?
	(register-tag-in-byte-code-stream
	  byte-code-stream unknown-value-tag?)
	;; Minimize the current expiration with the accumulated expiration
	;; variable and reset the current expiration.
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'reset-expiration))

      ;; Serve the next value of role.
      (call-stack-instruction-emitter serve-next-iteration-value
	byte-code-stream continuation-spot compute-average-if-known-tag)
      (call-stack-instruction-emitter branch-long byte-code-stream value-served-tag)

      ;; Compute the average if possible.
      (register-tag-in-byte-code-stream
	byte-code-stream compute-average-if-known-tag)
      (when unknown-allowed?
	;; Test if any of the values were none.
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'none-test)
	 ;; Branch and leave the value on the stack.
	(call-stack-instruction-emitter branch-long-if-true
	   byte-code-stream end-of-instruction-tag))
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream count-var)
      (emit-instruction-byte-code byte-code-stream 'type-check-float)
      (emit-operator-of-type byte-code-stream '/ 'float)

      ;; End of instruction.  Minimize cached expirations when necessary.
      (register-tag-in-byte-code-stream
	byte-code-stream end-of-instruction-tag)
      (when unknown-allowed?
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration)
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream cached-global-expiration-var?)
	(emit-instruction-byte-code byte-code-stream 'minimize-expiration))
      (call-stack-instruction-emitter close-iteration byte-code-stream continuation-spot))))




;;; The `SUM stack-evaluator' is implemented as a stack-node-instruction which
;;; emits its own instructions specifically.

(def-special-form-converter sum (expression)
  (aggregator-special-form-converter expression))

(def-preferred-instruction-chooser sum
  (declare (ignore extra-info))
  (aggregator-instruction-chooser
    stack-node-instruction required-type 'number 'number nil 2))

(def-expiration-special-form sum)

(def-stack-node-instruction-emitter sum
  (emit-aggregator-instruction
    stack-node-instruction byte-code-stream extra-info))



;;; The `PRODUCT stack-evaluator' is implemented as a stack-node-instruction
;;; which emits its own instructions specifically.

(def-special-form-converter product (expression)
  (aggregator-special-form-converter expression))

(def-preferred-instruction-chooser product
  (declare (ignore extra-info))
  (aggregator-instruction-chooser
    stack-node-instruction required-type 'number 'number nil 2))

(def-expiration-special-form product)

(def-stack-node-instruction-emitter product
  (emit-aggregator-instruction
    stack-node-instruction byte-code-stream extra-info))



;;; The `COUNT stack-evaluator' is implemented as a stack-node-instruction
;;; which emits its own instructions specifically.

(def-special-form-converter count (expression)
  (aggregator-special-form-converter expression))

(def-preferred-instruction-chooser count
  (declare (ignore extra-info))
  (aggregator-instruction-chooser
    stack-node-instruction required-type 'integer 'truth-value nil 2))

(def-expiration-special-form count)

(def-stack-node-instruction-emitter count
  (emit-aggregator-instruction
    stack-node-instruction byte-code-stream extra-info))



;;; The `AGGREGATED-AVERAGE stack-evaluator' is implemented as a
;;; stack-node-instruction which emits its own instructions specifically.

(def-special-form-converter aggregated-average (expression)
  (aggregator-special-form-converter expression))

(def-preferred-instruction-chooser aggregated-average
  (declare (ignore extra-info))
  (aggregator-instruction-chooser
    stack-node-instruction required-type '(or float (no-item)) 'number 'integer 2))

(def-expiration-special-form aggregated-average)

(def-stack-node-instruction-emitter aggregated-average
  (emit-aggregated-average-instruction
    stack-node-instruction byte-code-stream extra-info))



;;; The `MAXIMUM stack-evaluator' is implemented as a stack-node-instruction
;;; which emits its own instructions specifically.

(declare-instruction-for-optimizer
  'maximum
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    evaluate-first-arg-last
    aggregator))

(def-special-form-converter maximum (expression)
  (aggregator-special-form-converter expression))

(def-preferred-instruction-chooser maximum
  (declare (ignore extra-info))
  (aggregator-instruction-chooser
    stack-node-instruction required-type '(or number (no-item)) 'number t 2))

(def-expiration-special-form maximum)

(def-stack-node-instruction-emitter maximum
  (emit-max-or-min-aggregator-instruction
    stack-node-instruction byte-code-stream extra-info))



;;; The `MINIMUM stack-evaluator' is implemented as a stack-node-instruction
;;; which emits its own instructions specifically.

(def-special-form-converter minimum (expression)
  (aggregator-special-form-converter expression))

(declare-instruction-for-optimizer
  'minimum
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    evaluate-first-arg-last
    aggregator))

(def-preferred-instruction-chooser minimum
  (declare (ignore extra-info))
  (aggregator-instruction-chooser
    stack-node-instruction required-type '(or number (no-item)) 'number t 2))

(def-expiration-special-form minimum)

(def-stack-node-instruction-emitter minimum
  (emit-max-or-min-aggregator-instruction 
    stack-node-instruction byte-code-stream extra-info))






;;;; Time Expression Evaluators




;;; The Current Time Expressions, described on page 250 of the G2 User Manual,
;;; call the evaluators used also by the time functions.  See the time-function
;;; section of this file.



;;; The `CURRENT-TIME stack-evaluator' returns the number of scheduler seconds
;;; since the current G2 was started.  This evaluator takes no arguments.  This
;;; evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; SIMULATOR: uses (get-current-time-in-simulation-environment),
;;; INFERENCE & PROCEDURE: uses gensym-time to compute the current time.

;;; CURRENT-TIME ()

(def-in-line-evaluator current-time
    (56 all nil integer nil pprint-current-time-evaluator)
  (if (or (eq current-environment 'simulator)
	  (eq current-environment 'simulated-value))
      ;; This evaluator currently returns
      ;; (get-current-time-in-simulation-environment), even if calculating
      ;; values for the next step.
      (extract-macro-number-from-compound-fixnum-simulation-time
       (get-current-time-in-simulation-environment))
	(-f gensym-time gensym-time-at-start)))



;;; The `current-subsecond-time stack evaluator' returns a floating point number
;;; which is the number of scheduler seconds since G2 was started.  This value
;;; is the same as the result of current-time, except that this one is accurate
;;; to subsecond intervals, where the other is the floor of this value.

(def-funcalled-evaluator current-subsecond-time ()
    (95 all nil float funcall-eval-type-0-arg)
  (if (or (eq current-environment 'simulator)
	  (eq current-environment 'simulated-value))
      (copy-managed-float-into-evaluation-float
	(extract-number-from-compound-fixnum-simulation-time
	  (get-current-time-in-simulation-environment)))
      (make-evaluation-float
	(-e (managed-float-value current-g2-time)
	    (managed-float-value g2-time-at-start)))))



;;; The `current-system-time stack evaluator' returns a floating point number
;;; which is the number of scheduler seconds since G2 was started plus the Unix
;;; time when G2 was started.

(def-funcalled-evaluator current-system-time ()
    (141 all nil float funcall-eval-type-0-arg)
  (make-evaluation-float
    (managed-float-value (clock-get current-g2-time))))



;;; The `Current-real-time stack evaluator' returns the number of real seconds
;;; that the KB has been running, even if G2 is running in simulated time or as
;;; fast as possible.  This evaluator takes no arguments.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;;; CURRENT-REAL-TIME ()

(def-in-line-evaluator current-real-time
    (57 all nil integer nil
			   pprint-current-real-time-evaluator)
  (setq register-1 (get-real-gensym-time))
  (-f register-1 gensym-time-at-start))



;;; The `current-subsecond-real-time evaluator' returns a floating point number
;;; representing the current real time in current time format, accurate to the
;;; best that we can get from the hardware.

(def-funcalled-evaluator current-subsecond-real-time ()
    (96 all nil float funcall-eval-type-0-arg)
  (make-evaluation-float
    (-e (gensym-get-unix-time) (managed-float-value (clock-get g2-time-at-start)))))



;;; The `current-system-real-time evaluator' returns a floating point number
;;; representing the current real time in Unix time format, accurate to the
;;; best that we can get from the hardware.

(def-funcalled-evaluator current-system-real-time ()
    (142 all nil float funcall-eval-type-0-arg)
  (make-evaluation-float
    (gensym-get-unix-time)))



;;; The `COLLECTION-TIME-OF stack-evaluator' returns the time as per "the
;;; current time" which gives the collection time of the most recent value of
;;; the designated variable or parameter.  In the variable case, if this
;;; variable has never had a value, then this returns unknown.  It is an error
;;; to ask for the collection time of an expression that does not designate a
;;; variable or parameter.  This evaluator is available in the inference engine
;;; and procedures.

;;; When there is no collection time,
;;; INFERENCE: Sets stack-expiration to nil (unknown).
;;; PROCEDURE: Signals an error.

;; This operator is a source node since it can return unknown.

(def-expiration-source-operator collection-time-of)

(declare-optimizer-stack-instruction collection-time-of)

(def-default-special-form-converter collection-time-of)

(def-preferred-instruction-chooser collection-time-of
  (declare (ignore extra-info))
  (let ((argument-list (stack-node-argument-nodes stack-node-instruction))
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type)))
    (setf (car argument-list)
	  (choose-stack-node-instructions-and-types
	    (car-of-cons argument-list) '(class variable-or-parameter)))
    (setf (stack-node-instruction-extra-info stack-node-instruction)
	  (not (null unknown-allowed?)))
    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-unknown 'number unknown-allowed?))))

(def-stack-node-instruction-emitter collection-time-of
  (emit-stack-node-tree
    byte-code-stream
    (car-of-cons (stack-node-argument-nodes stack-node-instruction)))
  (call-stack-instruction-emitter push-constant
    byte-code-stream
    (if extra-info
	(make-evaluation-truth-value truth)
	(make-evaluation-truth-value falsity)))
  (call-stack-instruction-emitter funcall-instruction byte-code-stream 'collection-time-of))

(def-stack-error no-value-eval-error (item top-of-stack)
  "~NF does not have a value." item)

(def-funcalled-instruction collection-time-of (69 all 2 1 nil pprint-collection-time-of-instruction)
  (let* ((variable-or-parameter (stack-arg 0))
	 (simulation-environment?
	   (or (eq current-environment 'simulator)
	       (eq current-environment 'simulated-value)))
	 (collection-time 
	   (if simulation-environment?
	       (managed-float-value
		 (get-simulation-environment-gensym-time-for-variable-as-float
		   variable-or-parameter))
	       (extract-number-or-value
		 (time-of-most-recent-value variable-or-parameter))))
	 (unknown-allowed-arg (stack-arg 1))
	 (unknown-allowed?
	   (as-true-as (evaluation-truth-value-value unknown-allowed-arg)
		       truth)))
    (cond ((or (symbolp collection-time)
	       (and (fixnump collection-time)
		    (=f collection-time *some-time-ago*)))
	   (cond (unknown-allowed?
		  (setq stack-expiration nil)
		  (setq collection-time 0))
		 (t
		  (no-value-eval-error variable-or-parameter top-of-stack))))
	  ((fixnump collection-time)
	   (setq collection-time
		 (make-evaluation-integer
		   (-f collection-time
		       (if simulation-environment?
			   (clock-get gensym-time-at-start)
			   (floore-first
			     (managed-float-value (clock-get g2-time-at-start))))))))
	  ((gensym-float-p collection-time)
	   (let ((result-float
		   (-e collection-time
		       (if simulation-environment?
			   (coerce-fixnum-to-gensym-float (clock-get gensym-time-at-start))
			   (managed-float-value (clock-get g2-time-at-start))))))
	     (declare (type gensym-float result-float))
	     (setq collection-time
		   (if (=e result-float (ffloore-first result-float))
		       (floore-first result-float)
		       (make-evaluation-float result-float))))))
    (reclaim-evaluation-truth-value unknown-allowed-arg)
    (setf (stack-arg 0) collection-time)
    nil))



;;; The `COLLECTION-TIME-OF-PREVIOUS-DATAPOINT stack-evaluator' returns the
;;; collection time of a variable or parameter at a given number of datapoints
;;; ago.  If a value is not present at that time, a level 3 warning is given and
;;; either unknown is returned, no value is returned, or an error is signaled.
;;; This depends on whether the instruction allows unknown-datum and/or no-item.

;;; The evaluator accepts a variable or parameter designation argument and an
;;; integer expression argument that indicates the datapoint.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;;; This evaluator is implemented as a funcalled-instruction which emits its own
;;; instructions specifically.  This instruction is an expiration source node.
;;; It can return unknown-datum, no-item, or signal an error depending on the
;;; allowed type.

;; Get-collection-time-of-previous-datapoint needs to be rewritten so that it
;; does not print its own error messages.  The evaluators need to handle error
;; cases differently depending on the environment!! - cpm, 11/21/91

;;; COLLECTION-TIME-OF-PREVIOUS-DATAPOINT 
;;;    (variable-or-parameter, number-of-datapoints-ago)

(declare-optimizer-stack-instruction collection-time-of-previous-datapoint)

(def-expiration-source-operator collection-time-of-previous-datapoint)

(def-default-special-form-converter collection-time-of-previous-datapoint)

(def-history-preferred-instruction-chooser
  collection-time-of-previous-datapoint)

(def-history-stack-node-instruction-emitter
  collection-time-of-previous-datapoint)



;;; Instruction 67, the `COLLECTION-TIME-OF-PREVIOUS-DATAPOINT funcalled
;;; stack-instruction' is the instruction used to implement the evaluator for
;;; Collection-Time-Of-Previous-Datapoint.  It accepts a variable-or-parameter
;;; and a number-of-datapoints argument.  The return value and error handling
;;; depends on the value of the unknown-datum and no-item flags.

(def-funcalled-instruction collection-time-of-previous-datapoint (67 all 4 1 nil
								     pprint-collection-time-of-previous-datapoint-instruction)
  (let* ((variable-or-parameter (stack-arg 0))
	 (number-of-datapoints-ago (evaluation-quantity-value (stack-arg 1)))
	 (unknown-allowed (evaluation-truth-value-value (stack-arg 2)))
	 (no-item-allowed (evaluation-truth-value-value (stack-arg 3)))
	 collection-time?
	 return-value?)
  (when (<f number-of-datapoints-ago 0)
    (stack-error
      top-of-stack
      "Cannot reference the collection time of ~NF as of ~d datapoints ago.  A ~
      history datapoint must be referenced by a non-negative integer."
    variable-or-parameter number-of-datapoints-ago))
  (setq collection-time?
	(get-collection-time-of-previous-datapoint
	  variable-or-parameter (or (eq current-environment 'simulator)
				    (eq current-environment 'simulated-value))
	  number-of-datapoints-ago))
  (cond (collection-time?
	 (let ((collection-time-float? collection-time?))
	   (declare (type gensym-float collection-time-float?))
	   (setq return-value?
		 (if (=e collection-time-float?
			 (ffloore-first collection-time-float?))
		     (make-evaluation-integer
		       (floore-first collection-time-float?))
		     (make-evaluation-float collection-time-float?)))))
	((=f unknown-allowed truth)
	 (setq stack-expiration nil)
	 (setq return-value? nil))
	((=f no-item-allowed truth)
	 (setq return-value? nil))
	(t
	 (stack-error
	   top-of-stack
	   "Cannot get a collection time for ~NF as of ~a datapoints ago.  ~
           There was no value at that datapoint."
	   variable-or-parameter number-of-datapoints-ago)))
    (reclaim-evaluation-quantity (stack-arg 1))
    (reclaim-evaluation-truth-value (stack-arg 2))
    (reclaim-evaluation-truth-value (stack-arg 3))
    (decff top-of-stack 3)
    (setf (svref local-stack top-of-stack) return-value?)
    nil))



;;; The `EXPIRATION-TIME-OF stack-evaluator' returns a time as per "the current
;;; time" which gives the expiration time of the most recent value of the
;;; designated variable or datum.  In the variable case, if this variable has
;;; never had a value, or if the expiration of its value is NEVER, then this
;;; returns unknown.  This evaluator is available in the inference engine and
;;; procedures.

;; The above differs from the G2 Reference Manual.  Datum (temp.constants) are
;; not mentioned!!  28aug, cpm.  Should we handle temporary constant
;; expirations!!

;; See comment in Eval from jra, 9/8/88!!

;; This operator is a source node since it can return unknown.

(declare-instruction-for-optimizer
  'expiration-time-of
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles))

(def-expiration-source-operator expiration-time-of)

(def-default-special-form-converter expiration-time-of)

(def-preferred-instruction-chooser expiration-time-of
  (declare (ignore extra-info))
  (let ((argument-list (stack-node-argument-nodes stack-node-instruction))
	(no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type)))
    (setf (car argument-list)
	  (choose-stack-node-instructions-and-types
	    (car-of-cons argument-list) '(class variable)))
    (setf (stack-node-instruction-extra-info stack-node-instruction)
	  (not (null unknown-allowed?)))
    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-no-item-implies-unknown
	    (maybe-add-unknown 'number unknown-allowed?)
	    no-item-implies-unknown-allowed?))))

(def-stack-node-instruction-emitter expiration-time-of
  (emit-stack-node-tree
    byte-code-stream
    (car-of-cons (stack-node-argument-nodes stack-node-instruction)))
  (call-stack-instruction-emitter push-constant
    byte-code-stream
    (if extra-info
	(make-evaluation-truth-value truth)
	(make-evaluation-truth-value falsity)))
  (call-stack-instruction-emitter funcall-instruction byte-code-stream 'expiration-time-of))

(def-funcalled-instruction expiration-time-of (70 all 2 1 nil pprint-expiration-time-of-instruction)
  (let* ((variable (stack-arg 0))
	 (expiration (expiration-time-of-current-value variable))
	 (unknown-allowed-arg (stack-arg 1))
	 (unknown-allowed?
	   (as-true-as (evaluation-truth-value-value unknown-allowed-arg)
		       truth)))
    (if (or (symbolp expiration)
	    (=f expiration *some-time-ago*))
	(cond (unknown-allowed?
	       (setq stack-expiration nil)
	       (setq expiration 0))
	      (t
	       (no-value-eval-error variable top-of-stack)))
	;; Note that expirations are stored in a gensym-time format.
	(setq expiration (-f expiration (clock-get gensym-time-at-start))))
    (reclaim-evaluation-truth-value unknown-allowed-arg)
    (setf (stack-arg 0) (make-evaluation-integer expiration))
    nil))



;;; Formatting Time Value Expressions (pg. 251 G2 User Manual) seems to part of
;;; the format-form evaluator code!!






;;;; List Expression Evaluators




;;; There are separate g2-list evaluators for expression and designation list
;;; elements.  This is necesssary so that we can distinguish at compile time
;;; between an element which is a variable and the value of the variable.

;;; Note that as of 4.0, there is also a g2-list expression that takes both
;;; expression and designation elements.  We can instead use the stability
;;; feature and the type of the g2-list to compile in optimizations.  Otherwise,
;;; we can check the g2-list element type at runtime to determine when to
;;; reference the variable or value of a variable.
;;;
;; - cpm, 11/12/93

;;; G2-list evaluators are responsible for testing that the list and elements
;;; are of the correct element-type.  The evaluators pass the g2-list structure
;;; to the g2-list functions.

;;; Note that expressions that reference list elements are implemented through
;;; role service.  These include:
;;;   FIRST <type or item> IN <list>
;;;   SECOND <type or item> IN <list>
;;;   NEXT TO LAST <type or item> IN <list>
;;;   LAST <type or item> IN <list>
;;;   FOR ANY <type or item class> [local name] IN <list>
;;;   NEXT-LIST-ELEMENT (<list>, <list-element-designation>)




;;; The `G2-LIST-OR-SEQUENCE-MEMBER-P stack evaluator' is used to test whether
;;; an item-or-value is found in a g2-list or sequence.  It accepts two
;;; arguments, a g2-list or sequence and an item-or-value  It returns
;;; truth or falsity depending on whether the item-or-value is found within the
;;; list.  This evaluator is available in the inference engine and procedures.

;;; The operator is declared as an expiration-source-operator because the
;;; expression can return unknown.  This occurs in the case where the given item
;;; or value is a variable, and the g2-list is a value-list.  In this case, an
;;; attempt is made to fetch the value of the variable, which may return
;;; unknown.

(def-expiration-source-operator g2-list-or-sequence-member-p)

(def-default-special-form-converter g2-list-or-sequence-member-p)

(declare-optimizer-stack-instruction g2-list-or-sequence-member-p)

(def-preferred-instruction-chooser g2-list-or-sequence-member-p
  (declare (ignore extra-info))
  (let* ((unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (g2-list-node (first argument-nodes))
	 (element-node (second argument-nodes))
	 (g2-list-spec nil)
	 (g2-list-class? nil)
	 (g2-list-element-type? nil))
    (setf (first argument-nodes)
	  (choose-stack-node-instructions-and-types
	    g2-list-node '(or (class g2-list) (sequence))))
    (setq g2-list-spec (stack-node-value-type g2-list-node))
    (setq g2-list-class?
	  (and (class-type-specification-p g2-list-spec)
	       (type-specification-class g2-list-spec)))
    ;; Only use the element-type of system-defined g2-lists classes.
    (setq g2-list-element-type?
	  (g2-list-or-array-class-element-type g2-list-class? t))
    ;; Compile the element based on the g2-list type, when possible.
    (setf (second argument-nodes)
	  (choose-stack-node-instructions-and-types
	    element-node
	    (maybe-add-unknown
	      (or g2-list-element-type? 'item-or-datum) unknown-allowed?)))
    (setf (stack-node-value-type stack-node-instruction)
	  (cond
	    ((and unknown-allowed?
		   (type-specification-subtype-p
		     '(class variable) (stack-node-value-type element-node)))
	      (maybe-add-no-item-implies-unknown
		'(or boolean (unknown-datum)) no-item-implies-unknown-allowed?))
	    ((and unknown-allowed?
		  (type-specification-subtype-p
		    '(unknown-datum) (stack-node-value-type element-node)))
	     '(or boolean (unknown-datum)))
	    (t 'boolean)))))



(def-stack-node-instruction-emitter g2-list-or-sequence-member-p
  (declare (ignore extra-info))
  (let* ((value-type (stack-node-value-type stack-node-instruction))
	 (unknown-is-allowed?
	   (type-specification-subtype-p '(unknown-datum) value-type))
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    (emit-stack-node-tree byte-code-stream (first argument-nodes))     ;g2-list
    (emit-stack-node-tree byte-code-stream (second argument-nodes))    ;element
    (if unknown-is-allowed?		;push unknown-allowed flag
      (call-stack-instruction-emitter push-constant
	byte-code-stream (make-evaluation-truth-value truth))
      (call-stack-instruction-emitter push-constant
	byte-code-stream (make-evaluation-truth-value falsity)))
    (call-stack-instruction-emitter funcall-instruction
      byte-code-stream 'g2-list-or-sequence-member-p)))



;;; Instruction 75, the `G2-List-or-Sequence-Member-p funcalled instruction' is
;;; used to implement the evaluator of the same name.  The instruction accepts
;;; three arguments, a g2-list, an item-or-value, and a boolean value that
;;; indicates wwhether unknown is allowed.  The instruction returns true if the
;;; element is found in the g2-list.  Otherwise falsity is returned.

(def-stack-error member-in-g2-list-element-error (element g2-list top-of-stack)
  "Cannot test that ~NA is a member of the g2-list ~NF.  This item or value ~
   conflicts with the element-type, ~a, of the g2-list."
  element g2-list (list-type g2-list))

;;; The expression is implemented as a funcalled-instruction, instead of a
;;; funcalled-evalutor, because the operator needs to have its own emitter.

;;; Note that this instruction type checks and coerces the element argument when
;;; necessary.  Also, note that an error is signaled if there is a conflict
;;; between the element and the g2-list element-type.

(def-funcalled-instruction g2-list-or-sequence-member-p
    (75 all 3 1 nil pprint-g2-list-or-sequence-member-p-instruction)
  (let* ((g2-list-or-sequence (stack-arg 0))
	 (potential-element (stack-arg 1)) ; item-or-evaluation-value
	 (unknown-allowed-flag (stack-arg 2)) ; boolean-value
	 (coerced-element? nil)
	 (result? nil))
    (cond
      ((evaluation-sequence-p g2-list-or-sequence)
       (setq result?
	     (if (loop for elt being each evaluation-sequence-element
		       of g2-list-or-sequence
		       thereis (item-or-value-equalp elt potential-element))
		 (make-evaluation-truth-value truth)
		 (make-evaluation-truth-value falsity))))
      (t
       (multiple-value-bind (register-1 register-2)
	   (coerce-matching-element-type-or-unknown
	     g2-list-or-sequence potential-element top-of-stack
	     (evaluation-boolean-is-true-p unknown-allowed-flag))
	 (when register-2
	   (raw-stack-error-named-error top-of-stack register-2))
	 (setq coerced-element? register-1))
       (cond ((null coerced-element?)	; Unknown value.
	      (setq result? nil))
	     ((g2-list-member-p coerced-element? g2-list-or-sequence)
	      (setq result? (make-evaluation-truth-value truth)))
	     (t 
	      (setq result? (make-evaluation-truth-value falsity))))))
    (reclaim-if-evaluation-value g2-list-or-sequence)
    (reclaim-if-evaluation-value potential-element)
    (reclaim-if-evaluation-value coerced-element?)
    (reclaim-evaluation-boolean unknown-allowed-flag)
    (setf (stack-arg 0) result?)	; truth, falsity, or unknown (NIL).
    nil))




;;; The `G2-LIST-OR-SEQUENCE-LENGTH stack-evaluator' computes the number of
;;; elements in a g2-list.  If the list is empty, 0 is returned.  This evaluator
;;; is available in the inference engine and procedures.

;;; G2-LIST-OR-SEQUENCE-LENGTH (g2-list)

(def-in-line-evaluator g2-list-or-sequence-length 
		       (58 (inference procedure)
			   ((or (class g2-list) (sequence))) integer
			   nil pprint-g2-list-or-sequence-length-evaluator)
  (setq register-1 (stack-arg 0))
  (cond ((evaluation-sequence-p register-1)
	 (setq register-2 (evaluation-sequence-length register-1))
	 (reclaim-evaluation-sequence register-1))
	(t
	 (setq register-2 (g2-list-length (stack-arg 0)))))
  (make-evaluation-integer register-2))




;;; The `NEXT-LIST-ELEMENT stack evaluator' is an expression that returns the
;;; next g2-list element after the specified element.  For example, the
;;; expression "next-list-element (tank-list, tank-1)", returns the element in
;;; tank-list after tank-1, if any.

;;; It is an error if the list does not contain the indicated element or
;;; contains no elements.  If there is no element after the specified element,
;;; which is in the list, no value is returned.  It is an error for this
;;; expression to operate on lists that allow duplicate elements.  If a
;;; duplicate element was being referenced in this expression, it is not
;;; possible to determine which element the user inteded to reference.  Also,
;;; with duplicates, the same series of "next elements" could possibly be served
;;; repeatedly.

;;; This expression is more efficient for item lists.  Since an item contains
;;; pointers to every g2-list that it belongs to (in fact it points to its
;;; actual position in the list), the speed of the operation depends on the
;;; number of times an item is in any g2-lists.  Therefore, if the item is
;;; contained in one list, the operation is executed in a constant time.

;;; This expression is less efficient for datum lists.  In this case, the list
;;; is searched from the start of the list for the next element, which is an
;;; O(n) operation, where n is the length of the list.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.

;;; This evaluator is available in the inference engine and procedures.

;;; NEXT-LIST-ELEMENT (<list>, <list-element-designation>)

(declare-instruction-for-optimizer
  'next-list-element
  '(no-wait-states
    cannot-write-local-variables    
    cannot-read-local-variables
    cannot-write-roles))

(def-special-form-converter next-list-element (expression)
  (let ((arguments
	  (stack-list
	    (convert-expression-to-stack-node-tree (second expression))
	    (convert-expression-to-stack-node-tree (third expression))))
	(next-list-element-node
	  (make-stack-node-instruction 'next-list-element nil)))
    (setf (stack-node-argument-nodes next-list-element-node)
	  arguments)
    next-list-element-node))



;;; The preferred instruction chooser for NEXT-LIST-ELEMENT chooses instructions
;;; and types on its arguments, and then sets its own return value.

(def-preferred-instruction-chooser next-list-element
  (declare (ignore extra-info))
  (let ((unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type))
	(no-item-implies-unknown-allowed?
	  (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	(argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(type-spec '(or item-or-datum (no-item))))
    ;; next-list-element role server argument.
    (setf (first argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (first argument-nodes)
	    '(class g2-list)))
    (setf (second argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (second argument-nodes)
	    'item-or-datum))
    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-no-item-implies-unknown
	    (maybe-add-unknown
	      type-spec unknown-allowed?)
	    no-item-implies-unknown-allowed?))))



;;; Next-List-Element is an expiration source node.  It can return unknown based
;;; on the result of the coerce-matching-element instruction.

(def-expiration-source-operator next-list-element)


;;; The stack node instruction emitter for Next-List-Element emits a call to an
;;; instruction that coerces the element to the correct type for the list.

(def-stack-node-instruction-emitter next-list-element
  (declare (ignore extra-info))
  (let* ((value-type (stack-node-value-type stack-node-instruction))
	 (unknown-is-allowed?
	   (type-specification-subtype-p '(unknown-datum) value-type))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) value-type))
	 (argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    (emit-stack-node-tree byte-code-stream (first argument-nodes))     ;g2-list
    (emit-stack-node-tree byte-code-stream (second argument-nodes))    ;element
    (if unknown-is-allowed?
	(emit-instruction-byte-code
	  byte-code-stream 'coerce-matching-element-type-or-unknown)
	(emit-instruction-byte-code
	  byte-code-stream 'coerce-matching-element-type))
    (call-stack-instruction-emitter evaluate-role
      byte-code-stream '(next-list-element item-or-datum) 2 no-item-allowed?
      nil nil nil)))






;;;; Item Hierarchy Expression Evaluators




;;; The evaluation of the expression "{the, any} <class name> that is an
;;; attribute of <item>" is handled by the ATTRIBUTE-OF-CLASS role server.



;;; The `ATTRIBUTE-NAME stack-evaluator' function returns a symbol which is the
;;; name of the attribute which contains the given item.  The evaluator accepts
;;; one argument, an item designation.  This evaluator is only available in the
;;; inference engine and procedures.

;;; A FUNCTIONALITY CHANGE!!  If an item was not a named attribute of another
;;; object, 
;;; EVAL - would return unknown (proc-eval would signal an error);
;;; NEW-EVAl - now signals an error for both procedures and the inference
;;; engine. 

;;; ATTRIBUTE-NAME (item)

;; Should this return "unknown" during inference??  This is how the G2 User
;; Manual describes it.

(def-stack-error attribute-item-eval-error (item top-of-stack)
  "The item ~NF is not an attribute of another item." item)

(def-in-line-evaluator attribute-name
		       (59 (inference procedure) ((class item)) symbol t
			   pprint-attribute-name-evaluator)
  (setq register-2 (stack-arg 0))
  (setq register-1 (get-parent-attribute-name-as-symbol register-2))
  (if register-1
      (setq register-1 (make-evaluation-symbol register-1))
      (attribute-item-eval-error register-2 top-of-stack)))




;;; The evaluation of the expression "the <class name> superior to <item>" is
;;; handled by the SUPERIOR-ITEM role server.






;;;; Arithmetic Function Evaluators




;; Maybe we should restrict some additional evaluators, such as floor, ceiling,
;; round, and truncate, to have only <evaluator>-e, float versions??  For these
;; evaluators, the (first) return value from an integer argument is the same as
;; the result of a float version of the integer argument.  If this change is
;; made, the argument should be converted to a gensym-float before calling the
;; evaluator.



;;; The `ABS stack-evaluator' returns the absolute value of its argument.  The
;;; argument must be a number and is not coerced to a gensym-float.  This
;;; evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; ABS (number)

(def-stack-error abs-fixnum-overflow-error (fixnum-register-1 top-of-stack)
  "Cannot compute the ABS of ~NV.  The result is too large to ~
     represent as an integer and cannot be coerced to a float since the ~
     required result type is integer."
  fixnum-register-1)

(def-in-line-evaluator (abs abs-quantity 3)
		       (60 all (number) number t pprint-functional-evaluator)
  (setq register-2 (stack-arg 0))
  (cond ((fixnump register-2)
	 (cond ((=f register-2 most-negative-fixnum)
		(abs-fixnum-overflow-error register-2 top-of-stack))
	       (t
		(setq register-1
		      (make-evaluation-integer (absf register-2)))))
	 (reclaim-evaluation-integer register-2))
	((evaluation-long-p register-2)
	 (let ((temp (make-evaluation-long 0)))
	   (cond ((>=l (evaluation-long-value register-2)
		       (evaluation-long-value temp))
		  (reclaim-evaluation-long temp)
		  (setq register-1 register-2))
		 (t
		  ;; TODO: possible overflow-error in (signed-byte 64)
		  (mutate-evaluation-long-value
		    register-2
		    (-l (evaluation-long-value temp)
			  (evaluation-long-value register-2)))
		  (reclaim-evaluation-long temp)
		  (setq register-1 register-2)))))
	(t
	 (mutate-evaluation-float-value
	   register-2
	   (abse (evaluation-float-value register-2)))
	 (setq register-1 register-2))))

;; Modify the following when evaluation-integers are implemented!!  cpm, 3/3/91

(def-in-line-evaluator (abs abs-integer 1)
		       (61 all (integer) integer nil pprint-functional-evaluator)
  (setq fixnum-register-1 (stack-arg 0))
  (cond ((=f fixnum-register-1 most-negative-fixnum)
	 ;; Most negative fixnum argument would have returned a bignum
	 ;; result.  Signal an error because we can't coerce the
	 ;; argument to a float.
	 (abs-fixnum-overflow-error fixnum-register-1 top-of-stack))
	(t
	 (make-evaluation-integer (absf fixnum-register-1)))))

(def-in-line-evaluator (abs abs-float 2)
		       (62 all (float) float t pprint-functional-evaluator)
  (setq register-1 (stack-arg 0))
  (mutate-evaluation-float-value
    register-1 
    (abse (evaluation-float-value register-1))))



;;; The `ARCTAN unary stack evaluator' computes the arc (inverse) tangent of a
;;; number.  It accepts one argument which is a number that should be converted
;;; to a gensym-float before the evaluator is called.  It returns the angle
;;; whose tangent is given by the argument.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.

;; A FUNCTIONALITY CHANGE!!
;; SIMULATOR - The unary version of arctan was not available.

;;; ARCTAN (y)

(def-in-line-evaluator (arctan arctan-1 2)
    (63 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (mutate-evaluation-float-value
    register-1
    (atane (evaluation-float-value register-1))))




;;; The `ARCTAN-2 binary stack evaluator' computes the arc (inverse) tangent of
;;; a quotient.  It accepts two quantity arguments which are quantities that
;;; should be converted to gensym-floats before the evaluator is called.  The
;;; signs of the two arguments are used to determine the quadrant of the result.
;;; The result will be an angle in the same quadrant as the point (denom,
;;; number), where arg1 is the number, and arg2 is denom.  The range of the
;;; result is minus pi (exclusive) to plus pi (inclusive).  It is an error for
;;; both arguments to be zero.  This evaluator is available in the inference
;;; engine, procedures, and the simulator.

;;; The evaluator for arctan-2 requires two float arguments.  The evaluator for
;;; arctan requires one float argument.

;;; ARCTAN (y, x)

;; The EVAL binary version of arctan did not test for bad args.  It catches the
;; division by zero error if the args are bad.  Should we test on each call or
;; catch the arithmetic error??

(def-in-line-evaluator (arctan arctan-2 2)
    (64 all (float float) float t pprint-functional-evaluator)
;      (and (<e (-e (stack-arg 0) 0.0) *smallest-divisor*)
;	   (<e (-e (stack-arg 1) 0.0) *smallest-divisor*))
  ;; 0.0 probably does not need to be coerced to gensym-float!!  In BASICS,
  ;; it is said that it is read correctly if gensym-float is other than
  ;; single-float.

  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-float-value
    register-1
    (atane (evaluation-float-value register-1)
	   (evaluation-float-value register-2)))
  (reclaim-evaluation-float register-2))



;;; The `AVERAGE stack-evaluator' does as expected and takes the average value
;;; of its numeric arguments.  This n-ary operator is converted to calls to '+'
;;; and '/'.

;;; This evaluator is only available in the inference engine and procedures.

(def-special-form-converter average (expression)
  (let ((number-of-arguments (length (cdr expression))))
    (cond ((<f number-of-arguments 2)
	   (compiler-error
	     "The ~s function requires ~d or more quantity arguments and ~
              received ~d."
	     (car expression) 2 number-of-arguments)
	   (make-dummy-stack-node))
	  (t (convert-expression-to-stack-node-tree
	       (phrase-list '/ 
			    (phrase-cons '+ (cdr expression))
			    (length (cdr expression))))))))



;;; The `CEILING stack-evaluator' returns the argument truncated toward positive
;;; infinity.  The argument must be a quantity and is coerced to a gensym-float.
;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; CEILING (number)


(def-stack-error ceiling-float-error (evaluation-float top-of-stack)
  "Cannot compute the CEILING of ~NV.  The result is outside the ~
   range of integers."
  evaluation-float)

(def-substitution-macro ceiling-evaluation-float (evaluation-float top-of-stack)
  (setq float-register-1 (evaluation-float-value evaluation-float))
  (cond ((or (>e-most-positive-fixnum float-register-1)
	     (<e-most-negative-fixnum float-register-1))
	 (ceiling-float-error evaluation-float top-of-stack))
	(t
	 (let ((result (ceilinge-first float-register-1)))
	   (reclaim-evaluation-float evaluation-float)
	   result))))

(def-in-line-evaluator (ceiling ceiling-quantity 3)
    (65 all (number) number t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-2 (stack-arg 0))
  (cond ((evaluation-integer-p register-2)
	 (setq register-1 register-2))
        ((evaluation-long-p register-2)
         (setq register-1 register-2))
	(t
	 ;; If the result is not within fixnum bounds, the result is
	 ;; undefined or an error is signaled.
	 (setq register-1
	       (ceiling-evaluation-float register-2 top-of-stack)))))

(def-in-line-evaluator (ceiling ceiling-float 2)
    (66 all (float) integer t pprint-functional-evaluator)
  ;; If the result is not within fixnum bounds, the result is undefined
  ;; or an error is signaled.
  (setq cached-top-of-stack top-of-stack)
  (setq register-1
	(ceiling-evaluation-float (stack-arg 0) top-of-stack)))



;;; The `COS stack-evaluator' returns the cosine of its radian argument.  The
;;; argument must be coerced to a gensym-float, if necessary, before this
;;; evaluator is called.  There are no integer and quantity versions of this
;;; evaluator.  This evaluator is available in the inference engine, procedures,
;;; and the simulator.

;;; COS (radians)


(def-in-line-evaluator (cos cos-float 2)
    (67 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (mutate-evaluation-float-value
    register-1
    (cose (evaluation-float-value register-1))))




;;; The `EXP stack-evaluator' returns "e" raised to the power of the argument.
;;; The argument must be a quantity and is coerced to a gensym-float, if
;;; necessary, before this evaluator is called.  There are no integer and
;;; quantity versions of this evaluator.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.

;;; EXP (number)


(def-in-line-evaluator (exp exp-float 2)
    (68 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (mutate-evaluation-float-value
    register-1
    (expe (evaluation-float-value register-1))))




;;; The `EXPT stack evaluator' and `^ stack evaluator' return the value of the
;;; first argument raised to the power of the second argument.

;;; These evaluators call g2-exponent instead of calling the Common Lisp expt
;;; function directly.  G2-exponent catches and prevents certain errors.  Since
;;; G2 does not have complex or ratio numeric datum, an error is signalled when
;;; a result would be a complex number and ratio results are prevented by
;;; coercing the base to a float when necessary.  Several other errors involving
;;; a base of 0 or 0.0 are signalled or prevented.

;;; The two arguments to the evaluators are either float or integer quantities.
;;; The return value is of type integer if both arguments are integer.  If
;;; either argument is a float or when an argument must be coerced to a float
;;; (as described above to prevent errors or ratio values), the result is a
;;; float.  These evaluator are available in the inference engine, procedures,
;;; and the simulator.

;; The integer and float versions of EXPT were doing exactly the same thing as
;; the quantity version, since they dispatch to a function to compute the
;; exponent.  Keep the float version only since it maintains float data typing
;; through its operation, though we could consider an optimization of the
;; integer version later.  -jra 11/21/90

;; The integer version has been removed.  Also, the integer version could not
;; guarantee that the result is always an integer.  For example, when the power is
;; an integer less than 0, the base is coerced to a float to prevent a ratio
;; result.  4dec90, cpm.

;;; EXPT (base, exponent)


(def-float-contagion-stack-operator expt)

(def-in-line-evaluator (expt expt-quantity 3)
    (69 all (number number) number nil pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (expt-evaluation-quantities (stack-arg 0) (stack-arg 1) top-of-stack))

(def-in-line-evaluator (expt expt-float 2)
    (70 all (float float) float nil pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (g2-exponent-evaluation-float (stack-arg 0) (stack-arg 1) top-of-stack))



;;; The `FLOOR stack-evaluator' returns the argument truncated toward negative
;;; infinity.  The argument must be a quantity and is coerced to a gensym-float.
;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; FLOOR (number)

(def-stack-error floor-evaluation-error (evaluation-float top-of-stack)
  "Cannot compute the FLOOR of ~NV.  The result is too large to ~
   represent as an integer."
  evaluation-float)

(def-substitution-macro floor-evaluation-float (evaluation-float top-of-stack)
  (setq float-register-1 (evaluation-float-value evaluation-float))
  (cond ((or (>e-most-positive-fixnum float-register-1)
	     (<e-most-negative-fixnum float-register-1))
	 (floor-evaluation-error evaluation-float top-of-stack))
	(t
	 (let ((result (floore-first float-register-1)))
	   (reclaim-evaluation-float evaluation-float)
	   result))))

(def-in-line-evaluator (floor floor-quantity 3)
    (71 all (number) number t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-2 (stack-arg 0))
  (cond ((evaluation-integer-p register-2)
	 (setq register-1 register-2))
        ((evaluation-long-p register-2)
         (setq register-1 register-2))
	(t
	 (setq register-1
	       (floor-evaluation-float register-2 top-of-stack)))))

(def-in-line-evaluator (floor floor-float 2)
    (72 all (float) integer t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (floor-evaluation-float (stack-arg 0) top-of-stack)))



;;; The `LN stack-evaluator' returns the logarithm of the argument in base "e",
;;; the base of the natural logarithms.  The argument must be a non-negative
;;; quantity and is coerced to a gensym-float.  There is no integer version of
;;; this evaluator.  This evaluator is available in the inference engine,
;;; procedures, and the simulator.

;;; LN (base)

(def-stack-error negative-arg-eval-error (negative-arg evaluator-name top-of-stack)
  ;; Arg is < 0 error.
  "The ~a operator received the negative argument ~a."
  evaluator-name
  (if (evaluation-quantity-p negative-arg)
      (evaluation-quantity-value negative-arg)
      negative-arg))

(def-in-line-evaluator (ln ln-float 2)
    (73 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (if (<e (evaluation-float-value register-1) 0.0)
      ;; The following reclaims its float arg.
      (negative-arg-eval-error register-1 'ln top-of-stack)
      (mutate-evaluation-float-value
	register-1
	(loge (evaluation-float-value register-1)))))


;;; The `LOG stack-evaluator' returns the logarithm of the argument in the base
;;; 10.  The argument must be a non-negative quantity and is coerced to a
;;; gensym-float.  There is no integer versions of this evaluator.  This
;;; evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; LOG (base)

(declare-side-effect-free-function log-10)

(defun log-10 (n) (log n 10))

(def-in-line-evaluator (log log-float 2)
    (74 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (if (<e (evaluation-float-value register-1) 0.0)
      ;; The following reclaims its float arg.
      (negative-arg-eval-error register-1 'log top-of-stack)
      (mutate-evaluation-float-value
	register-1
	(log-10 (evaluation-float-value register-1)))))


;;; The `MAX stack-evaluator' accepts two quantity arguments and returns the
;;; maximum of the two values.  The new form of this evaluator differs from the
;;; earlier one by not accepting any number of arguments.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;;; EVAL: accepted any number of arguments.
;;; NEW-EVAL: accepts only two arguments.

;;; The special form converter is only really needed to test for the correct
;;; number of arguments.  Otherwise, during the compile, no evaulator is found
;;; and the user was getting a compiler-bug, instead of a compiler-error.

;;; MAX (number, number)

(def-special-form-converter max (expression)	
  (special-form-converter-with-minimum-argument-count
    expression 2))

;;; Minimize type-checking by knowing that the arguments are either
;;; integers or floats.
(def-in-line-evaluator (max max-quantity 3)
		       (75 all (number number) number t pprint-functional-evaluator)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1
	(make-evaluation-quantity
	  (cond
	    ((or (evaluation-float-p register-2)
		 (evaluation-float-p register-3))
	     (maxe2 (evaluation-quantity-value-as-float register-2)
		    (evaluation-quantity-value-as-float register-3)))
	    ((and (evaluation-integer-p register-2)
		  (evaluation-integer-p register-3))
	     (maxf register-2 register-3))
	    (t
	     (when (evaluation-integer-p register-2)
	       (setq register-2 (make-evaluation-long register-2)))
	     (when (evaluation-integer-p register-3)
	       (setq register-3 (make-evaluation-long register-3)))
	     (if (>=l (evaluation-long-value register-2)
		      (evaluation-long-value register-3))
		 register-2 register-3)))))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

;; Rewrite the following when evaluation-integers are implemented!!  cpm, 3/4/91.

(def-in-line-evaluator (max max-integer 1)
		       (76 all (integer integer) integer nil
			   pprint-functional-evaluator)
  (maxf (stack-arg 0) (stack-arg 1)))

(def-in-line-evaluator (max max-float 2)
		       (77 all (float float) float t
			   pprint-functional-evaluator)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-float-value
    register-1
    (maxe2 (evaluation-float-value register-1)
           (evaluation-float-value register-2)))
  (reclaim-evaluation-float register-2))

;;; TODO: (def-in-line-evaluator (max max-long 3) ..)

;;; The `MIN stack-evaluator' accepts two number arguments and returns the
;;; minimum of the two values.  The new form of this evaluator differs from the
;;; earlier one by not not accept any number of arguments.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;;; EVAL: accepted any number of arguments.
;;; NEW-EVAL: accepts only two arguments.

;;; The special form converter is only really needed to test for the correct
;;; number of arguments.  Otherwise, during the compile, no evaulator is found
;;; and the user was getting a compiler-bug, instead of a compiler-error.

;;; MIN (number, number)

(def-special-form-converter min (expression)
  (special-form-converter-with-minimum-argument-count
    expression 2))

(def-in-line-evaluator (min min-quantity 3)
		       (78 all (number number) number t
			   pprint-functional-evaluator)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (setq register-1
	(make-evaluation-quantity
	  (cond
	    ((or (evaluation-float-p register-2)
		 (evaluation-float-p register-3))
	     (mine2 (evaluation-quantity-value-as-float register-2)
		    (evaluation-quantity-value-as-float register-3)))
	    ((and (evaluation-integer-p register-2)
		  (evaluation-integer-p register-3))
	     (minf register-2 register-3))
	    (t
	     (when (evaluation-integer-p register-2)
	       (setq register-2 (make-evaluation-long register-2)))
	     (when (evaluation-integer-p register-3)
	       (setq register-3 (make-evaluation-long register-3)))
	     (if (<=l (evaluation-long-value register-2)
		      (evaluation-long-value register-3))
		 register-2 register-3)))))
  (reclaim-evaluation-quantity register-2)
  (reclaim-evaluation-quantity register-3))

;; Rewrite the following when evaluation-integers are implemented!!  cpm, 3/4/91.

(def-in-line-evaluator (min min-integer 1)
		       (79 all (integer integer) integer nil
			   pprint-functional-evaluator)
  (minf (stack-arg 0) (stack-arg 1)))

(def-in-line-evaluator (min min-float 2)
		       (80 all (float float) float t
			   pprint-functional-evaluator)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-float-value
    register-1
    (mine2 (evaluation-float-value register-1)
	   (evaluation-float-value register-2)))
  (reclaim-evaluation-float register-2))

;;; TODO: (def-in-line-evaluator (max max-long 3) ..)

;;; The function `special-form-converter-with-minimum-argument-count' is used as
;;; a special form converter when a minimum number of arguments are required.
;;; Note that this function creates a stack-node and not a
;;; stack-instruction-node.  See the comments in def-special-form-converter to
;;; understand the difference between these two nodes as related to special-form
;;; conversion.  This function was written to convert the min and max functions
;;; and give an error when less than 2 arguments.

(defun special-form-converter-with-minimum-argument-count
       (expression minimum-argument-count)
  (let ((instruction-node nil)
	(stack-evaluator-descriptions? nil)
	(operator (first expression))
	(arguments (cdr expression)))
    (cond ((>=f (length arguments) minimum-argument-count)
	   (setq stack-evaluator-descriptions?
		 (stack-evaluators operator))
	   (setq instruction-node
		 (make-stack-node operator stack-evaluator-descriptions?))
	   (setf (stack-node-argument-nodes instruction-node)
		 (make-stack-argument-nodes
		   operator arguments stack-evaluator-descriptions?)))
	  (t
	   (setq instruction-node (make-dummy-stack-node))
	   (compiler-error
	     "The ~s function requires ~d or more quantity arguments and ~
              received ~d."
	     operator minimum-argument-count (length arguments))))
    instruction-node))



;;; The `QUOTIENT stack-evaluator' returns the result of dividing the first
;;; argument by the second argument and truncating.  The sign of the result
;;; depends on the arguments.  For example, quotient (-5, 2.1) = quotient (5,
;;; -2.1) = -2.  This evaluator is available in the inference engine and
;;; procedures.

;;; QUOTIENT (dividend, divisor)



(def-float-contagion-stack-operator quotient)

(def-stack-error truncate-evaluation-error (operation e-float-1 top-of-stack)
  "The result of the ~a expression, ~NV, is out of the range ~
   of integers."
  operation
  e-float-1)

(def-substitution-macro truncate-evaluation-float (e-float-1 operation top-of-stack)
  (let ((float-register-1 (evaluation-float-value e-float-1)))
    (cond ((or (>e-most-positive-fixnum float-register-1)
	       (<e-most-negative-fixnum float-register-1))
	   (truncate-evaluation-error operation e-float-1 top-of-stack))
	  (t
	   (let ((result (if (pluspe float-register-1)
			     (floore-first (evaluation-float-value e-float-1))
			     (-f (floore-first
				   (-e float-register-1))))))
	     (reclaim-evaluation-float e-float-1)
	   result)))))

(defun truncate-evaluation-quantities (number-1 number-2 top-of-stack)
  (let ((e-float-1 (if (evaluation-float-p number-1)
                       number-1
                       (prog1
                           (make-evaluation-float (evaluation-quantity-value-as-float number-1))
                           (reclaim-evaluation-quantity number-1))))
        (e-float-2 (if (evaluation-float-p number-2)
                       number-2
                       (prog1
                           (make-evaluation-float (evaluation-quantity-value-as-float number-2))
                           (reclaim-evaluation-quantity number-2)))))
    (mutate-evaluation-float-value
      e-float-1
      (/e (evaluation-float-value e-float-1)
	  (evaluation-float-value e-float-2)))
    (let ((result (truncate-evaluation-float e-float-1 'quotient top-of-stack)))
      (reclaim-evaluation-float e-float-2)
      result)))

(def-in-line-evaluator (quotient quotient-quantity 3)
    (81 (inference procedure) (number number) number t
	pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (cond ((and (evaluation-integer-p register-2)
	      (evaluation-integer-p register-3))
	 (setq register-1
	       (truncatef-first register-2 register-3)))
        ((or (evaluation-float-p register-2)
	     (evaluation-float-p register-3))
	 (setq register-1
	       (truncate-evaluation-quantities
		 register-2 register-3 top-of-stack)))
        (t
         (when (evaluation-integer-p register-2)
	   (setq register-2 (make-evaluation-long register-2)))
         (when (evaluation-integer-p register-3)
	   (setq register-3 (make-evaluation-long register-3)))
         (div-long register-2 register-3)
         (reclaim-evaluation-long register-3)
         (setq register-1 register-2))))

(defun truncate-evaluation-float-function (e-float-1 operation top-of-stack)
  (truncate-evaluation-float e-float-1 operation top-of-stack))

(def-in-line-evaluator (quotient quotient-integer 1)
    (82 (inference procedure) (integer integer) integer nil
	pprint-functional-evaluator)
  (make-evaluation-integer
    (truncatef-first (evaluation-integer-value (stack-arg 0))
		     (evaluation-integer-value (stack-arg 1)))))

(def-in-line-evaluator (quotient quotient-float 2)
    (83 (inference procedure) (float float) integer nil
	pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (mutate-evaluation-float-value
    register-1
    (/e (evaluation-float-value register-1)
	(evaluation-float-value register-2)))
  (let ((result (truncate-evaluation-float register-1 'quotient top-of-stack)))
    (reclaim-evaluation-float register-2)
    result))




;;; The `RANDOM unary stack evaluator' returns a random number greater than or
;;; equal to zero and less than the argument.  If the argument is an integer,
;;; the return value is an integer.  If the argument is a float, the return
;;; value is a float.  The argument must be a positive quantity.  This evaluator
;;; is available in the inference engine, procedures, and the simulator.

;;; Documentation from the original evaluator in EVAL by ML:

;;; If there is one argument, then if an integer, n, return an integer in [0,n).
;;; If real, return a real in [0, n).  The argument must be positive.

;;; If there are two arguments and both are integers, return an integer in
;;; [n,m].  If at least one is real, return a real in the interval [n,m).  The
;;; arguments may be negative or zero, put the first must be strictly less than
;;; the second.

;;; RANDOM (number)


(defparameter +recip-most-positive-fixnum+ (/ 1.0 most-positive-fixnum))
(defvar *random-real-0-result* nil)

(defun random-real-0 ()
  (unless *random-real-0-result*
    (setq *random-real-0-result* (allocate-managed-float 0.0)))
  (mutate-managed-float-value
   *random-real-0-result*
   (*e (coerce (g2-random most-positive-fixnum) (gensym-float-type))
                                        ; Chestnut translator doesn't understand
                                        ; gensym-float as a derived from 
                                        ; double-float, thus, using 
                                        ; (gensym-float-type)
       +recip-most-positive-fixnum+))
  *random-real-0-result*)

(defmacro random-real (r)
  `(*e ,r (managed-float-value (random-real-0))))


(def-stack-error non-positive-arg-eval-error (non-positive-arg evaluator-name top-of-stack)
  ;; Arg is <= 0 error.
  "The ~a operator received the non-positive argument ~a."
  evaluator-name
  (if (evaluation-quantity-p non-positive-arg)
      (evaluation-quantity-value non-positive-arg)
      non-positive-arg))

(def-in-line-evaluator (random random-quantity 3)
    (84 all (number) number t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-2 (stack-arg 0))
  (if (evaluation-integer-p register-2)
      (if (<=f register-2 0)
      ;; The following reclaims its number arg.
	  (non-positive-arg-eval-error register-2 'random top-of-stack)
	  (setq register-1 (make-evaluation-integer
			     (g2-random register-2))))
      (let ((float-value (evaluation-quantity-value-as-float register-2)))
        (if (<=e float-value 0.0)
	  ;; The following reclaims its number arg.
	  (non-positive-arg-eval-error register-2 'random top-of-stack)
            (setq register-1 (make-evaluation-float (random-real float-value))))))
  (reclaim-evaluation-quantity register-2))


(def-in-line-evaluator (random random-integer 1)
    (85 all (integer) integer nil pprint-functional-evaluator)
  (setq fixnum-register-1 (stack-arg 0))
  (if (<=f fixnum-register-1 0)
      (non-positive-arg-eval-error fixnum-register-1 'random top-of-stack)
      ;; integer arg.
      (g2-random fixnum-register-1)))

(def-in-line-evaluator (random random-float 2)
    (86 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq float-register-1 (evaluation-float-value register-1))
  (cond ((<=e float-register-1 0.0)
	 (non-positive-arg-eval-error register-1 'random top-of-stack))
	(t
	 (setq float-register-1 (random-real float-register-1))
	 (setf (evaluation-float-value register-1)
	       float-register-1))))


;;; The `RANDOM binary stack evaluator' returns a random number greater than or
;;; equal to the first argument and less than the second argument.  The
;;; arguments must each be a quantity.  The arguments can be negative or zero,
;;; but the second argument must be greater than the first argument.  If the
;;; argument is an integer, the function returns an integer.  If either argument
;;; is a float, the function returns a float. 

;;; The evaluator for random-2 requires 2 quantity arguments.  The evaluator for
;;; random requires only 1.


;;; RANDOM (number, number)

(def-float-contagion-stack-operator random)

;;; The following is no longer called:
;;; (def-stack-error arg-to-random-operator-is-most-positive-fixnum (top-of-stack)
;;;   "Integer arguments to the RANDOM operator must be less than or equal ~
;;;    to ~a (1 less than the most positive integer)."
;;;   (-f most-positive-fixnum 1))

(def-stack-error arg1-not-less-than-arg2-eval-error
    (stack-arg-1 stack-arg-2 argument-p evaluator-name top-of-stack)
  ;; Stack-arg-1 is >= Stack-arg-2 error.
  (if argument-p
      "The ~a operator requires the argument ~a to be less than~a the argument ~a."
      "The ~a operator requires the start-index, ~a, to be ~
       less than or equal to~a the end-index, ~a.")
  evaluator-name
  (if (evaluation-value-p stack-arg-1)
      (evaluation-value-value stack-arg-1)
      stack-arg-1)
  (if (memq evaluator-name '(get-from-text replace-in-text omit-from-text))
      " one more than"
      "")
  (if (evaluation-value-p stack-arg-2)
      (evaluation-value-value stack-arg-2)
      stack-arg-2))

;;; Given RANDOM(A,B), for A,B integers, B-A+1 must be <= most-positive-fixnum 
;;; in order to use a fixnum approach.  This is because we compute
;;; r=RANDOM(B-A+1) in order to get 0 <= r <= B-A, for a final answer of r+A
;;; where A <= r+A <= B .

;;; If B-A+1 > most-positive-fixnum then we use the following float approach:
;;; r = round(RANDOM(float(A),float(B))) .  This works for any fixnums A,B
;;; with A < B .

;;; - jpg 4/23/02

(def-in-line-evaluator (random random-quantity-2 3)
    (87 all (number number) number t
	pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-2 (stack-arg 0))
  (setq register-3 (stack-arg 1))
  (cond ((and (fixnump register-2) (fixnump register-3))
	 (when (>=f register-2 register-3)
	   ;; The following reclaims its quantity args.
	   (arg1-not-less-than-arg2-eval-error
	     register-2 register-3 t 'random top-of-stack))
	 (let ((arg-0-floated (coerce-fixnum-to-gensym-float register-2))
	       (arg-1-floated (coerce-fixnum-to-gensym-float register-3)))
	   (cond ((>e (-e arg-1-floated (+e arg-0-floated -1.0))
		      most-positive-fixnum-as-float)
		  (setq register-1
			(rounde-first 
			  (+e arg-0-floated 
			      (random-real (-e arg-1-floated arg-0-floated))))))
		 (t
		  (setq fixnum-register-1
			(g2-random (-f register-3 (+f register-2 -1))))
		  (setq register-1
			(make-evaluation-integer
			  (+f register-2 fixnum-register-1)))))
	   (reclaim-evaluation-integer register-2)
	   (reclaim-evaluation-integer register-3)))
	;; Could add a case for two floats, a small efficiency improvement.
	;; For now, just do the mixed type case.
	;; By coercing to floats where necessary, we are both simple and
	;; efficient -alatto, 8/20/98
	(t
	 (setf float-register-1 (evaluation-quantity-value-as-float register-2))
	 (setf float-register-2 (evaluation-quantity-value-as-float register-3))
	 (when (>=e float-register-1 float-register-2)
	   ;; The following reclaims its quantity args.
	   (arg1-not-less-than-arg2-eval-error
	     float-register-1 float-register-2 t 'random top-of-stack))
	 (setq float-register-2 (random-real
				  (-e float-register-2 float-register-1)))
	 (setq register-1 
	       (make-evaluation-float (+e float-register-2 float-register-1)))
	 (reclaim-evaluation-quantity register-2)
	 (reclaim-evaluation-quantity register-3))))

;; Rewrite when evaluation-integers are implemented!!  cpm, 3/4/91.

(def-in-line-evaluator (random random-integer-2 1)
		       (88 all (integer integer) integer nil
			   pprint-functional-evaluator)
  (when (>=f (stack-arg 0) (stack-arg 1))
    (arg1-not-less-than-arg2-eval-error
      (stack-arg 0) (stack-arg 1) t 'random top-of-stack))
  (let ((arg-0-floated (coerce-fixnum-to-gensym-float (stack-arg 0)))
	(arg-1-floated (coerce-fixnum-to-gensym-float (stack-arg 1))))
    (if (>e (-e arg-1-floated (+e arg-0-floated -1.0))
	    most-positive-fixnum-as-float)
	(rounde-first 
	  (+e arg-0-floated (random-real (-e arg-1-floated arg-0-floated))))
	(+f (stack-arg 0)
	    (g2-random (-f (stack-arg 1) (+f (stack-arg 0) -1)))))))

(def-in-line-evaluator (random random-float-2 2)
    (89 all (float float) float t
	pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (setq register-2 (stack-arg 1))
  (setq register-3 (evaluation-float-value register-1))
  (setq register-4 (evaluation-float-value register-2))
  (cond ((>=e register-3 register-4)
	 ;; This error handler reclaims its quantity args.
	 (arg1-not-less-than-arg2-eval-error
	   register-1 register-2 t 'random top-of-stack))
	(t
	 (setq float-register-1 (random-real (-e register-4 register-3)))
	 (mutate-evaluation-float-value
	   register-1
	   (+e register-3 float-register-1))))
  (reclaim-evaluation-float register-2))



;;; The `REMAINDER stack-evaluator' returns the remainder that results from
;;; dividing the first argument by the second argument.  The sign of the result
;;; has the same sign as the dividend.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.

;;; REMAINDER (dividend, divisor)

(def-float-contagion-stack-operator remainder)

(def-in-line-evaluator (remainder remainder-quantity 3)
    (90 all (number number) number t
	pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (compute-remainder-quantity (stack-arg 0) (stack-arg 1))))

(defun compute-remainder-quantity (numerator denominator)
  (cond ((and (fixnump numerator) (fixnump denominator))
         (rem-fixnums numerator denominator))
        ((or (evaluation-float-p numerator) (evaluation-float-p denominator))
	 (let ((numerator-ef
                (if (evaluation-float-p numerator)
                    numerator
		  (prog1
		      (make-evaluation-float (evaluation-quantity-value-as-float numerator))
		    (reclaim-evaluation-quantity numerator))))
	       (denominator-ef
                (if (evaluation-float-p denominator)
                    denominator
		  (prog1
		      (make-evaluation-float (evaluation-quantity-value-as-float denominator))
		    (reclaim-evaluation-quantity denominator)))))
           (compute-remainder-float numerator-ef denominator-ef)))
        (t ; one or both are evaluation-long values
         (when (fixnump numerator)
	   (setq numerator (make-evaluation-long numerator)))
         (when (fixnump denominator)
	   (setq denominator (make-evaluation-long denominator)))
	 (let ((n (evaluation-long-value numerator))
	       (d (evaluation-long-value denominator)))
	   (declare (type #.(gensym-long-type) n d))
	   (prog1
	       (make-evaluation-long (-l n (*l (/l n d) d)))
	     (reclaim-evaluation-long numerator)
	     (reclaim-evaluation-long denominator))))))

;; Rewrite the following when evaluation-integers are implemented!!  cpm, 3/4/91.


(def-in-line-evaluator (remainder remainder-integer 1)
		       (91 all (integer integer) integer t
			   pprint-functional-evaluator)
  (setq register-1 (rem-fixnums (stack-arg 0) (stack-arg 1))))

(def-in-line-evaluator (remainder remainder-float 2)
    (92 all (float float) float t
	pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (compute-remainder-float (stack-arg 0) (stack-arg 1))))

(defun compute-remainder-float (numerator-ef denominator-ef)
  ;; Compute the division.
  (let ((remainder-result
	  (make-evaluation-float
	    (/e (evaluation-float-value numerator-ef)
		(evaluation-float-value denominator-ef)))))
    ;; Compute the truncated division result.
    (mutate-evaluation-float-value
      remainder-result
      (if (minuspe (evaluation-float-value remainder-result))
	  (-e (ffloore-first (-e (evaluation-float-value remainder-result))))
	  (ffloore-first (evaluation-float-value remainder-result))))
    ;; Multiply the truncation result by the denominator and subtract that from
    ;; the numerator to compute the final result.
    (mutate-evaluation-float-value
      remainder-result
      (-e (evaluation-float-value numerator-ef)
	  (*e (evaluation-float-value denominator-ef)
	      (evaluation-float-value remainder-result))))
    ;; Reclaim the arguments and return the value.
    (reclaim-evaluation-float numerator-ef)
    (reclaim-evaluation-float denominator-ef)
    remainder-result))




;;; The `ROUND stack-evaluator' returns the argument rounded using g2-round.
;;; Positive numbers >= n.5 are rounded up to n+1.  Positive numbers < n.5 are
;;; rounded down to n.  Negative numbers > -n.5 are rounded to -n.  Negative
;;; numbers <= -n.5 are rounded to -(n+1).  G2-round behaves differently from
;;; the Common Lisp round which rounds n.5 or -n.5 to the nearest even integer.
;;; The argument must be a quantity and is coerced to a gensym-float.  This
;;; evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; ROUND (number)

(def-substitution-macro g2-round-evaluation-float (evaluation-float top-of-stack)
  (mutate-evaluation-float-value
    evaluation-float
    (if (pluspe (evaluation-float-value evaluation-float))
	(+e (evaluation-float-value evaluation-float) 0.5)
	(-e (evaluation-float-value evaluation-float) 0.5)))
  (truncate-evaluation-float evaluation-float 'round top-of-stack))

(def-in-line-evaluator (round round-quantity 3)
    (93 all (number) number t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-2 (stack-arg 0))
  (cond ((evaluation-integer-p register-2)
	 (setq register-1 register-2))
        ((evaluation-long-p register-2)
         (setq register-1 register-2))
	(t
	 (setq register-1
	       (g2-round-evaluation-float register-2 top-of-stack)))))

(def-in-line-evaluator (round round-float 2)
    (94 all (float) integer t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (g2-round-evaluation-float (stack-arg 0) top-of-stack)))




;;; The `SIN-E stack-evaluator' returns the sine of its radian argument.  The
;;; argument must be coerced to a gensym-float, if necessary, before this
;;; evaluator is called.  There are no integer and quantity versions of this
;;; evaluator.  This evaluator is available in the inference engine, procedures,
;;; and the simulator.

;;; SIN (radians)

(def-in-line-evaluator (sin sin-float 2)
    (95 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (mutate-evaluation-float-value
    register-1
    (sine (evaluation-float-value register-1))))


;;; The `SQRT stack-evaluator' returns the square root of its argument.  The
;;; argument must be coerced to a gensym-float, if necessary, before this
;;; evaluator is called.  There are no integer and quantity versions of this
;;; evaluator.  The argument must be a non-negative quantity.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

;;; SQRT (number)

(def-in-line-evaluator (sqrt sqrt-float 2)
    (96 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (if (<e (evaluation-float-value register-1) 0.0)
      ;; The following reclaims its quantity arg.
      (negative-arg-eval-error register-1 'sqrt top-of-stack)
      (mutate-evaluation-float-value
	register-1
	(sqrte (evaluation-float-value register-1)))))




;;; The `TAN-E stack-evaluator' returns the tangent of its radian argument.  The
;;; argument must be coerced to a gensym-float, if necessary, before this
;;; evaluator is called.  There are no integer and quantity versions of this
;;; evaluator.  This evaluator is available in the inference engine, procedures,
;;; and the simulator.

;;; FUNCTIONALITY CHANGE!!
;;; Previously, this evaluator was only available in the simulator.

;;; TAN (radians)

(def-in-line-evaluator (tan tan-float 2)
    (98 all (float) float t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-1 (stack-arg 0))
  (mutate-evaluation-float-value
    register-1
    (tane (evaluation-float-value register-1))))




;;; The `TRUNCATE stack-evaluator' returns the argument truncated toward zero.
;;; The argument must be a quantity and is coerced to a gensym-float.  This
;;; evaluator is available in the inference engine, procedures, and the
;;; simulator.

;;; TRUNCATE (number)

(def-in-line-evaluator (truncate truncate-float 2)
    (97 all (float) integer t pprint-functional-evaluator)
  (setq cached-top-of-stack top-of-stack)
  (setq register-2 (stack-arg 0))
  ;; The following reclaims register-2.
  (setq register-1 (make-evaluation-integer
		     (truncate-evaluation-float
		       register-2 'truncate top-of-stack))))



;;; The `TRUTH-VALUE stack-evaluator' converts a value to type truth-value.  It
;;; accepts one argument of type quantity or truth-value.  This evaluator is
;;; available in the inference engine and procedures.

;;; TRUTH-VALUE (number-or-truth-value)

;;; The datum version of truth-value is in-line so that the evaluator can
;;; distinguish between truth-value and numeric evaluation-values.


(def-in-line-evaluator (truth-value truth-value-datum 5)
		       (15 (inference procedure) ((or number truth-value))
			   truth-value nil pprint-functional-evaluator)
  (setq register-2 (stack-arg 0))
  (cond ((evaluation-truth-value-p register-2)
	 register-2)
	(t
	 (truth-value-evaluation-number register-2 top-of-stack))))


(def-funcalled-evaluator (truth-value truth-value-of-truth-value 4)
			 (truth-value)
			 (34 (inference procedure)
			     (truth-value) truth-value
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  truth-value)


(def-stack-error invalid-argument-to-truth-value (number top-of-stack)
  "Unknown kind of number, ~NV, given to truth-value."
  number)

(def-substitution-macro truth-value-gensym-float (gensym-float)
  (cond ((>=e gensym-float 1.0)
	 truth)
	((<=e gensym-float -1.0)
	 falsity)
	(t
	 (g2-round-e (*e gensym-float (coerce-fixnum-to-gensym-float truth))))))

(def-substitution-macro truth-value-lisp-number (quantity-value)
  (cond ((fixnump quantity-value)
	 (cond ((>=f quantity-value 1)
		truth)
	       ((=f quantity-value 0)
		0)
	       (t
		falsity)))
	((gensym-float-p quantity-value)
	 (truth-value-gensym-float quantity-value))))

(def-funcalled-evaluator (truth-value truth-value-quantity 3)
			 (quantity)
			 (35 (inference procedure)
			     (number) truth-value
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let* ((quantity-value (evaluation-quantity-value quantity))
	 (result (truth-value-lisp-number quantity-value)))
    (unless result
      (invalid-argument-to-truth-value quantity cached-top-of-stack))
    (setq result (make-evaluation-truth-value result))
    (reclaim-evaluation-quantity quantity)
    result))


(def-funcalled-evaluator (truth-value truth-value-integer 1)
			 (integer-arg)
			 (36 (inference procedure) (integer) truth-value
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let ((integer-value (evaluation-integer-value integer-arg))
	(result nil))
    (setq result
	  (cond ((>=f (the fixnum integer-value) 1)
		 (make-evaluation-truth-value truth))
		((<=f (the fixnum integer-value) -1)
		 (make-evaluation-truth-value falsity))
		(t 
		 (make-evaluation-truth-value 0))))
    (reclaim-evaluation-integer integer-arg)
    result))


(def-funcalled-evaluator (truth-value truth-value-float 2)
			 (float)
			 (37 (inference procedure) (float) truth-value
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let* ((float-value (evaluation-float-value float))
	 (result (truth-value-gensym-float float-value)))
    (setq result (make-evaluation-truth-value result))
    (reclaim-evaluation-float float)
    result))


;;; The functions `truth-value-evaluation-number' and
;;; `truth-value-evaluation-float' are used by the truth
;;; stack-evaluators to convert numbers to truth-value.  Note that the
;;; evaluation-number argument is reclaimed.

(defun truth-value-evaluation-number (evaluation-number top-of-stack)
  (cond ((evaluation-float-p evaluation-number)
	 (truth-value-evaluation-float evaluation-number top-of-stack))
	((>=f evaluation-number 1)
	 (reclaim-evaluation-integer evaluation-number)
	 evaluation-true-value)
	((<=f evaluation-number -1)
	 (reclaim-evaluation-integer evaluation-number)
	 evaluation-false-value)
	(t
	 (reclaim-evaluation-integer evaluation-number)
	 (make-evaluation-truth-value 0))))

(defun truth-value-evaluation-float (evaluation-float top-of-stack)
  (cond ((>=e (evaluation-float-value evaluation-float) 1.0)
	 (reclaim-evaluation-float evaluation-float)
	 evaluation-true-value)
	((<=e (evaluation-float-value evaluation-float) -1.0)
	 (reclaim-evaluation-float evaluation-float)
	 evaluation-false-value)
	(t
	 (mutate-evaluation-float-value
	   evaluation-float
	   (*e (evaluation-float-value evaluation-float)
	       (coerce-fixnum-to-gensym-float truth)))
	 ;; The following reclaims its float argument.
	 (make-evaluation-truth-value
	   (g2-round-evaluation-float evaluation-float top-of-stack)))))





;;;; Text Function Evaluators

;;; The text function evaluators all take at least one g2-text as argument.
;;; Most deal with indices of g2-text.  At the user level, a "text" is
;;; 1-based for the purposes of indexing (although the user cannot really
;;; refer to a character at all, since G2 lacks a character data type.)
;;; In the internal representation, a "g2-text" is zero-based.  Therefore,
;;; we always have to subtract 1 from the start index.
;;;
;;; Also, the definition of a character is not always entirely clear.
;;; The header for the "length-of-text" function contained this comment:
;;; > Complex, for example international characters, are counted
;;; > as one character.
;;; This is alluding to the discrepency between "simple characters" and
;;; "gensym characters".  This distinction should be gone as of 5.0,
;;; where we have switched from a greatly augmented ASCII base to a
;;; Unicode base.  I believe that we have also addressed the following
;;; comment, which I'm leaving here for now until I'm sure:
;;;
;; There's something wrong about the maximum length limit testing above: we test
;; the length in terms of simple characters, of which there may be four times as
;; many as of gensym character, and then we report to the user the maximum
;; number of characters allowed, if he goes over the limit.  Users can only
;; determine the length in terms of gensym characters, so there is no way they
;; could write code that avoids this error!  Deal with this!  Minor problems:
;; (1) the use of unabstracted length operations on the "g2 text" arguments; and
;; (2) the wording of the message, even aside from the issue of the units
;; ambiguity.  (MHD 3/24/93)
;;;
;;; - jv 5/24/96



;;; The `IS-CONTAINED-IN-TEXT stack-evaluator' tests if one text is found within
;;; another.  It accepts two g2-text arguments and returns a truth-value.  If
;;; the first string is found within the second, truth is returned.  Otherwise,
;;; falsity is returned.  This evaluator is available in the inference engine
;;; and procedures.

(def-funcalled-evaluator is-contained-in-text (locate-text original-text)
			 (38 (inference procedure)
			     (text text) boolean
			     funcall-eval-type-2-arg
			     nil pprint-functional-evaluator)
  (let* ((locate-text-value (evaluation-text-value locate-text))
	 (original-text-value (evaluation-text-value original-text))
	 (result 
	   (if (find-g2-text-section-position locate-text-value
					      original-text-value)
	       (make-evaluation-truth-value truth)
	       (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-text locate-text)
    (reclaim-evaluation-text original-text)
    result))



;;; The `LENGTH-OF-TEXT stack-evaluator' measures the length of text.  It
;;; accepts one argument of type g2-text and returns the number of g2-characters
;;; in the g2-text.  This evaluator is available in the inference engine and
;;; procedures.

(def-funcalled-evaluator length-of-text (original-text)
			 (39 (inference procedure)
			     (text) integer
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let ((result (make-evaluation-integer (g2-text-length original-text))))
    (reclaim-evaluation-text original-text)
    result))



;;; The `POSITION-OF-TEXT stack-evaluator' locates, if possible, one text within
;;; another.  It accepts two g2-text arguments and returns the starting position
;;; of the first occurrence of the first string within the second.  If this
;;; position is found, this one-based g2-text-index is returned.  Otherwise, 0
;;; is returned.  This evaluator is available in the inference engine and
;;; procedures.

(def-funcalled-evaluator position-of-text (locate-text original-text)
			 (40 (inference procedure)
			     (text text) integer
			     funcall-eval-type-2-arg
			     nil pprint-functional-evaluator)
  (let* ((locate-text-value (evaluation-text-value locate-text))
	 (original-text-value (evaluation-text-value original-text))
	 (result (find-g2-text-section-position locate-text-value
						original-text-value)))
    (reclaim-evaluation-text locate-text)
    (reclaim-evaluation-text original-text)
    (if result
	(make-evaluation-integer (1+f result))
	(make-evaluation-integer 0))))



;;; The `TEXT-BEGINS-WITH-QUANTITY stack-evaluator' accepts one text argument
;;; and returns truth if the text begins with a quantity, ignoring any leading
;;; whitespace.  Otherwise, falsity is returned.  This evaluator can be used to
;;; test that the quantity evaluator would return a quantity and not produce an
;;; error when given this text.  This evaluator is available in the inference
;;; engine and procedures.

(def-funcalled-evaluator text-begins-with-quantity (original-text)
			 (41 (inference procedure)
			     (text) boolean
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let* ((number?
	   (read-number-from-text-string
	     (evaluation-text-value original-text)))
	 (result 
	   (cond
	     ((not (or (null number?)
		       (eq number? 'underflow) ; should be sep. error?! (MHD)
		       (eq number? 'overflow)))
	      ;; the following would be more efficient, but allow overflow/underflow!
	      ;; (syntactically-numeric-substring-p (evaluation-text-value original-text))
	      (make-evaluation-truth-value truth))
	     (t
	      (make-evaluation-truth-value falsity)))))
    (reclaim-evaluation-text original-text)
    result))



;;; The `UPPER-CASE-TEXT stack-evaluator' converts text to upper-case.  It
;;; accepts one g2-text argument and returns a copy of that g2-text converted
;;; to upper-case.  This evaluator is available in the inference engine and
;;; procedures.

(def-funcalled-evaluator upper-case-text (original-text)
			 (42 (inference procedure)
			     (text) text
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let* ((original-text-value (evaluation-text-value original-text))
	 (result
	   (make-evaluation-text-reclaiming-argument
	     (copy-g2-text-with-case-conversion original-text-value :all))))
    (reclaim-evaluation-text original-text)
    result))



;;; The `LOWER-CASE-TEXT stack-evaluator' converts text to lower-case.  It
;;; accepts one g2-text argument and returns a copy of that g2-text converted to
;;; lower-case.  This evaluator is available in the inference engine and
;;; procedures.

(def-funcalled-evaluator lower-case-text (original-text)
			 (43 (inference procedure)
			     (text) text
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let* ((original-text-value (evaluation-text-value original-text))
	 (result
	   (make-evaluation-text-reclaiming-argument
	     (copy-g2-text-with-case-conversion original-text-value :none))))
    (reclaim-evaluation-text original-text)
    result))



;;; The `CAPITALIZE-WORDS stack-evaluator' capitalizes text.  It accepts a
;;; g2-text argument and returns a copy of that g2-text with the first
;;; g2-character of each word, if it is an alphabetic character, converted to an
;;; upper-case character.  This evaluator is only available in the inference
;;; engine and procedures.

(def-funcalled-evaluator capitalize-words (original-text)
			 (44 (inference procedure)
			     (text) text
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let* ((original-text-value (evaluation-text-value original-text))
	 (result
	   (make-evaluation-text-reclaiming-argument
	     (copy-g2-text-with-case-conversion
	       original-text-value :first-of-each-word))))
    (reclaim-evaluation-text original-text)
    result))


(def-stack-error unknown-text-eval-error (evaluator-name top-of-stack)
  "The ~a evaluator failed to produce an answer despite the fact~
   that it's arguments were within bounds.  Please report this~
   internal error to Gensym software support with the source code
   of the item named in the error message."
  evaluator-name)


;;; `report-text-indices-error'

(defun report-text-indices-error (original-text start-index end-index evaluator-name)
  (let* ((original-text-value (evaluation-text-value original-text))
	 (original-text-length (g2-text-length original-text))
	 (start-index-value (evaluation-integer-value start-index))
	 (end-index-value (if (null end-index)
			      original-text-length
			      (evaluation-integer-value end-index))))
    (cond
      ((<f start-index-value 1)
       (non-positive-arg-eval-error
	 start-index-value evaluator-name cached-top-of-stack))
      ((<f end-index-value 1)
       (non-positive-arg-eval-error
	 end-index-value evaluator-name cached-top-of-stack))
      ((>f start-index-value original-text-length)
       (index-of-g2-text-too-large-eval-error
	 start-index-value original-text-value
	 evaluator-name cached-top-of-stack))
      ((>f end-index-value original-text-length)
       (index-of-g2-text-too-large-eval-error
	 end-index-value original-text-value
	 evaluator-name cached-top-of-stack))
      ((>f start-index-value end-index-value)
       ;; end-index-value = start-index-value - 1  itself is not
       ;; an error and won't get here.  (RESULT is not NULL.)
       ;; E.g. for GET-FROM-TEXT it means that the empty text
       ;; is to be returned. - jpg 6/6/02
       (arg1-not-less-than-arg2-eval-error
	 start-index-value end-index-value nil evaluator-name
	 cached-top-of-stack))
      (t
       (unknown-text-eval-error evaluator-name cached-top-of-stack)))

    ; (reclaim-evaluation-text original-text)
    (reclaim-evaluation-integer start-index)
    (when end-index (reclaim-evaluation-integer end-index))))




;;; `checking-text-function' - This macro is used by the evaluators
;;; insert-in-text, omit-from-text, get-from-text, and replace-in-text.
;;; Each of these functions contains a call to a very similarly-named
;;; internal function, wrapped inside a call to checking-text-function.
;;; The internal functions take and return 1-based, inclusive indices,
;;; so there is no conversion which needs to go on here.  If there
;;; is a problem, presumably with the indices, the internal functions
;;; return nil.  At that point, checking-text-function will try to figure
;;; out what the exact problem was, and print a stack-error message
;;; describing it.  It could be made more efficient by having the internal
;;; functions be more descriptive about the problems they've found, but
;;; it's not worthwhile to optimize the error cases.

(defmacro checking-text-function (evaluator-name &body body)
  `(let* ((original-text-value (evaluation-text-value original-text))
	  (original-text-length (g2-text-length original-text))
	  (start-index-value (evaluation-integer-value start-index))
	  (end-index-value (if (null end-index)
			       original-text-length
			       (evaluation-integer-value end-index)))
	  (text-to-insert-value (and text-to-insert
				     (evaluation-text-value text-to-insert)))
	  (result
	    (make-evaluation-text-reclaiming-argument
	      ,@body)))
     ;; If nil is returned instead of a g2-text result, then either the
     ;; start or end index were out of bounds.  Report this error to the user.

     ;; The error functions reclaim their text args.
     (when (null result)
       (cond
	 ((and text-to-insert-value
	       (>f (+f original-text-length
		       (g2-text-length text-to-insert-value))
		   maximum-length-for-user-text-strings))
	  (merged-string-would-be-too-long-eval-error
	    original-text-value text-to-insert-value
	    ,evaluator-name cached-top-of-stack))
	 ((<f start-index-value 1)
	  (non-positive-arg-eval-error
	    start-index-value ,evaluator-name cached-top-of-stack))
	 ((<f end-index-value 1)
	  (non-positive-arg-eval-error
	    end-index-value ,evaluator-name cached-top-of-stack))
	 ((>f start-index-value original-text-length)
	  (index-of-g2-text-too-large-eval-error
	    start-index-value original-text-value
	    ,evaluator-name cached-top-of-stack))
	 ((>f end-index-value original-text-length)
	  (index-of-g2-text-too-large-eval-error
	    end-index-value original-text-value
	    ,evaluator-name cached-top-of-stack))
	 ((>f start-index-value end-index-value)
	  ;; end-index-value = start-index-value - 1  itself is not
	  ;; an error and won't get here.  (RESULT is not NULL.)
	  ;; E.g. for GET-FROM-TEXT it means that the empty text
	  ;; is to be returned. - jpg 6/6/02
	  (arg1-not-less-than-arg2-eval-error
	    start-index-value end-index-value nil ,evaluator-name
	    cached-top-of-stack))
	 (t
	  (unknown-text-eval-error ,evaluator-name cached-top-of-stack))))

     (reclaim-evaluation-text original-text)
     (reclaim-evaluation-integer start-index)
     (when end-index (reclaim-evaluation-integer end-index))
     (when text-to-insert (reclaim-evaluation-text text-to-insert))
     result))



;;; The `INSERT-IN-TEXT stack-evaluator' inserts one text within another text.
;;; It accepts three arguments: a source g2-text, a destination g2-text, and a
;;; one-based integer index into the destination text.  This evaluator returns a
;;; copy of the source g2-text inserted into a copy of the destination text at
;;; the index (i.e., before the g2-character that is at that position).  This
;;; operation is non-destructive.  This evaluator is only available in the
;;; inference engine and procedures.

(def-funcalled-evaluator insert-in-text 
    (text-to-insert original-text start-index)
    (45 (inference procedure)
	(text text integer) text
	funcall-eval-type-3-arg
	nil pprint-functional-evaluator)
  (let ((end-index nil))
    (checking-text-function
      'insert-in-text
      (insert-in-g2-text 
	text-to-insert-value original-text-value
	start-index-value))))


;;; The `OMIT-FROM-TEXT stack-evaluator' removes a piece of text from a g2-text.
;;; It accepts three arguments: a g2-text and two one-based g2-text indices.
;;; The g2-text section is removed starting at the beginning index up to and
;;; including, the end index.  This operation is non-destructive.  This
;;; evaluator is only available in the inference engine and procedures.

(def-funcalled-evaluator omit-from-text (original-text start-index end-index)
    (46 (inference procedure)
	(text integer integer) text
	funcall-eval-type-3-arg
	nil pprint-functional-evaluator)
  (let ((text-to-insert nil))
    (checking-text-function
      'omit-from-text
      (omit-from-g2-text 
	original-text-value start-index-value
	end-index-value))))



;;; The `GET-FROM-TEXT stack-evaluator' returns a section of a g2-text.  It
;;; accepts three arguments: a g2-text and two one-based g2-text positions.
;;; These positions indicate the beginning and end of the g2-text section that
;;; is returned (copied) from the g2-text.  The end index is included in the
;;; g2-text section.  This operation is non-destructive.  This evaluator is
;;; available in the inference engine and procedures.

(def-funcalled-evaluator get-from-text (original-text start-index end-index)
    (47 (inference procedure)
	(text integer integer) text
	funcall-eval-type-3-arg
	nil pprint-functional-evaluator)
  (let ((text-to-insert nil))
    (checking-text-function
      'get-from-text
      (get-from-g2-text
	original-text-value
	start-index-value
	end-index-value))))



;;; The `REPLACE-IN-TEXT stack-evaluator' simulates "overwriting" a
;;; portion of one text string with another text string.  The indices
;;; given refer to the portion of the original text to replace.  Then the
;;; new text is inserted between the two characters which surrounded the
;;; old text.  Of course, the text removed and the text inserted do not
;;; need to be of the same length.  This function is syntactic sugar for:
;;;     replace-in-text(a, b, x, y) ==
;;;        insert-in-text(a, omit-from-text(b, x, y), x)
;;; However, with the expanded tokenization facilities in 5.0, users
;;; will want to replace text much more often, and using the two function
;;; call is less efficient and makes the G2 user's code ugly.

(def-funcalled-evaluator replace-in-text
    (text-to-insert original-text start-index end-index)
    (66 (inference procedure)
	(text text integer integer) text
	funcall-eval-type-4-arg
	nil pprint-functional-evaluator)
  (checking-text-function
    'replace-in-text
    (replace-in-g2-text
      text-to-insert-value
      original-text-value
      start-index-value
      end-index-value)))



;;;; Regular Expression Functions


(def-stack-error bad-regular-expression-error
    (pattern evaluator-name top-of-stack preprocessor-errors?)
  (make-error-string-for-bad-regular-expression
    ;; reclaims preprocessor-errors?
    pattern evaluator-name preprocessor-errors?))
	

;;; `checking-regexp-function' - similar to checking text functions, but it
;;; does it's error checking first, and then calls the internal functions,
;;; which assume correct input.  Also, obviously, it has some different things
;;; to check, like whether the search pattern was a valid regular expression.

(defmacro checking-regexp-function ((source-text-name search-position-name lexing-table-or-errors)
				    evaluator-name &body body)
  `(let* ((,source-text-name (evaluation-text-value source-text))
	  (,search-position-name (evaluation-integer-value search-position))
	  (,lexing-table-or-errors nil)
	  (search-pattern-value (evaluation-text-value search-pattern))
	  (source-text-length (g2-text-length ,source-text-name))
	  (result nil))
     (cond
       ((>f ,search-position-name source-text-length)
	(index-of-g2-text-too-large-eval-error
	  ,search-position-name
	  ,source-text-name
	  ',evaluator-name
	  cached-top-of-stack))
       ((<f ,search-position-name 1)
	(index-of-g2-text-too-large-eval-error
	  ,search-position-name
	  ,source-text-name
	  ',evaluator-name
	  cached-top-of-stack))
       (t
	(setq ,lexing-table-or-errors
	      (get-lexing-table-for-regexp search-pattern-value))
	(cond
	  ((lexing-table-p ,lexing-table-or-errors)
	   (setq result ,@body))
	  (t
	   (bad-regular-expression-error
	     ;; reclaims lexing-table-or-errors
	     search-pattern-value ',evaluator-name
	     cached-top-of-stack ,lexing-table-or-errors)))))
     (reclaim-evaluation-text source-text)
     (reclaim-evaluation-text search-pattern-value)
     (reclaim-evaluation-integer search-position)
     result))


;;; `checking-end-position' 

(defmacro checking-end-position (evaluator-name text-to-insert
						search-position
						end-position
						source-text
						&body body)
  (avoiding-variable-capture (evaluator-name
			       text-to-insert
			       search-position
			       end-position
			       source-text
			       &aux search-position-value
			       end-position-value
			       source-text-value
			       source-text-length)
    `(let ((,search-position-value (evaluation-integer-value ,search-position))
	   (,end-position-value (evaluation-integer-value ,end-position))
	   (,source-text-value (evaluation-text-value ,source-text))
	   (,source-text-length (g2-text-length ,source-text)))
       (cond
	 ((>f ,end-position-value ,source-text-length)
	  (index-of-g2-text-too-large-eval-error
	    ,end-position-value
	    ,source-text-value
	    ',evaluator-name
	    cached-top-of-stack))
	 ((<f ,end-position-value 1)
	  (index-of-g2-text-too-large-eval-error
	    ,end-position-value
	    source-text-value
	    ',evaluator-name
	    cached-top-of-stack))
	 ((>f ,search-position-value ,end-position-value)
	  (arg1-not-less-than-arg2-eval-error
	    ,search-position-value
	    ,end-position-value
	    nil
	    ',evaluator-name
	    cached-top-of-stack))
	 (t
	  (setq result
		,@body)))
       (reclaim-evaluation-text ,text-to-insert)
       result)))


;;; The `FIND-NEXT-PATTERN stack-evaluator' takes three arguments: a regular
;;; expression text, source text to search, and a start index.  There is also
;;; a version which takes a structure used to define switches (modifiers) to
;;; the function.  If the argument given for the regular expression is
;;; actually not a valid regular expression, a run-time error is signaled. 
;;; When the pattern is a constant, the error could conceivably be detected
;;; at compile time, but that is not implemented.  Also, it is a run-time
;;; error to give a start index which is out of bounds.  Barring those cases,
;;; the function returns a structure to the user.  If the match is not found,
;;; the structure contains start-index and end-index 0.  If the match is found,
;;; the start-index and end-index are set to the indices of the longest
;;; possible match starting at the earliest possible position.

(def-funcalled-evaluator (find-next-pattern find-next-pattern-3 3)
    (search-pattern source-text search-position)
    (27 (inference procedure)
	(text text integer) (structure)
	funcall-eval-type-3-arg
	nil pprint-functional-evaluator)
  (checking-regexp-function
    (source-text-value search-position-value lexing-table)
    find-next-pattern
    (indices-for-match
      lexing-table source-text-value search-position-value)))




;;; `find-next-substring-matching-pattern' - this function operates in
;;; exactly the same manner as "find-next-pattern"; only their return
;;; values differ.  Whereas find-next-pattern returns a structure with
;;; information about the match, this function actually returns the string
;;; (returning "" for failure.)  It is essentially syntactic sugar:
;;;
;;;    substring = find-next-substring-matching-pattern(pattern, source, start, other);
;;;
;;; is equivalent to:
;;; 
;;;    structure1   = find-next-pattern(pattern, source, start, other);
;;;    start-pos = the start-index of structure1;
;;;    end-pos   = the end-index of structure1;
;;;    if end-pos = 0 then
;;;       substring = ""
;;;    else
;;;       substring = get-from-text(source, start-pos, end-pos)
;;;    end
;;;
;;; Actually, the syntactic sugar is much simpler now that we
;;; have the "lexeme" funcalled evaluator.

(def-funcalled-evaluator (find-next-substring-matching-pattern
			   find-next-substring-matching-pattern-3 3)
    (search-pattern source-text search-position)
    (28 (inference procedure)
	(text text integer) text
	funcall-eval-type-3-arg
	nil pprint-functional-evaluator)
  (checking-regexp-function
    (source-text-value search-position-value lexing-table)
    find-next-substring-matching-pattern
    (make-evaluation-text-reclaiming-argument
      (substring-for-match
	lexing-table source-text-value search-position-value))))




;;; `find-and-replace-pattern' - Finds all nonoverlapping matches
;;; of the given regular expression in the given source text starting
;;; at the given start position, and makes a copy of the whole text,
;;; replacing all the matches it found with the given text.  Note
;;; that the text to insert is *not* treated as a regular expression.
;;; It is simply inserted textually.  This function has no indication
;;; of failure.  Any number of matches succeeds, including zero.  In
;;; the case of zero matches, it returns a copy of the text unchanged.

(def-funcalled-evaluator (find-and-replace-pattern
			   find-and-replace-pattern-5 5)
    (search-pattern text-to-insert source-text search-position end-position)
    (29 (inference procedure)
	(text text text integer integer) text
	funcall-eval-type-5-arg
	nil pprint-functional-evaluator)
    (let ((end-position-value (evaluation-integer-value end-position))
	  (text-to-insert-value (evaluation-text-value text-to-insert)))
      (checking-regexp-function
	(source-text-value search-position-value lexing-table)
	find-and-replace-pattern
	(checking-end-position
	  find-and-replace-pattern
	  text-to-insert
	  search-position
	  end-position
	  source-text
	  (make-evaluation-text-reclaiming-argument
	    (text-with-replacements
	      lexing-table text-to-insert-value
	      source-text-value search-position-value end-position-value))))))



;;; `find-next-pattern-4' - takes an extra argument, a structure, other-args.

(def-funcalled-evaluator (find-next-pattern find-next-pattern-4 4)
    (search-pattern source-text search-position other-args)
    (33 (inference procedure)
	(text text integer (structure)) (structure)
	funcall-eval-type-4-arg
	nil pprint-functional-evaluator)
  (let*
      ((other-args-value (evaluation-structure-value other-args))
       (result
	(handling-other-args
	  other-args-value
	  (checking-regexp-function
	    (source-text-value search-position-value lexing-table)
	    find-next-pattern
	    (indices-for-match
	      lexing-table source-text-value search-position-value)))))
    (reclaim-evaluation-structure other-args)
    result))


;;; `find-next-substring-matching-pattern-4' - takes an extra argument,
;;; a structure, other-args.

(def-funcalled-evaluator (find-next-substring-matching-pattern
			   find-next-substring-matching-pattern-4 4)
    (search-pattern source-text search-position other-args)
    (79 (inference procedure)
	(text text integer (structure)) text
	funcall-eval-type-4-arg
	nil pprint-functional-evaluator)
  (let*
      ((other-args-value (evaluation-structure-value other-args))
       (result
	(handling-other-args
	  other-args-value
	  (checking-regexp-function
	    (source-text-value search-position-value lexing-table)
	    find-next-substring-matching-pattern
	    (make-evaluation-text-reclaiming-argument
	      (substring-for-match
		lexing-table source-text-value search-position-value))))))
    (reclaim-evaluation-structure other-args)
    result))



;;; `find-and-replace-pattern-6' - takes an extra argument, a structure,
;;; other-args.

(def-funcalled-evaluator (find-and-replace-pattern
			   find-and-replace-pattern-6 6)
    (search-pattern text-to-insert source-text search-position end-position other-args)
    (98 (inference procedure)
	(text text text integer integer (structure)) text
	funcall-eval-type-6-arg
	nil pprint-functional-evaluator)
  (let ((end-position-value (evaluation-integer-value end-position))
	(text-to-insert-value (evaluation-text-value text-to-insert))
	(other-args-value (evaluation-structure-value other-args)))
    (let*
      ((result
	(handling-other-args
	  other-args-value
	  (checking-regexp-function
	    (source-text-value search-position-value lexing-table)
	    find-and-replace-pattern
	    (checking-end-position
	      find-and-replace-pattern
	      text-to-insert
	      search-position
	      end-position
	      source-text
	      (make-evaluation-text-reclaiming-argument
		(text-with-replacements lexing-table
					text-to-insert-value source-text-value
					search-position-value end-position-value)))))))
      (reclaim-evaluation-structure other-args)
      result)))





;;;; Tokenizer evaluators


(def-stack-error bad-tokenizer-specification-error
    (tokenizer evaluator-name top-of-stack)
  "Tokenizer ~NF was passed to ~a, but it is not OK:~%~s~%"
  tokenizer
  evaluator-name)


;;; `get-next-token' is the interface to the tokenizer class in G2.  It
;;; is very similar in function to "find-next-pattern", but by specifying
;;; a tokenizer object rather than a simple string, the user can perform
;;; much more complicated text manipulation much easier.  It takes as
;;; arguments a tokenizer, a text to search, and a search-position at which
;;; to begin the search, and returns a structure containing the following
;;; information about the match: its start position, its end position, and
;;; its token-type.

(def-funcalled-evaluator (get-next-token
			   get-next-token-3 3)
    (tokenizer source-text search-position)
    (25 (inference procedure)
	((class tokenizer) text integer) (structure)
	funcall-eval-type-3-arg
	nil pprint-functional-evaluator)
  (let* ((search-position-value
	   (1-f (evaluation-integer-value search-position)))
	 (source-text-value (evaluation-text-value source-text))
	 (source-text-length (g2-text-length source-text-value))
	 (result nil))
    (cond
      ((frame-status-and-notes tokenizer)
       (bad-tokenizer-specification-error
	 tokenizer 'get-next-token cached-top-of-stack))
      ((>f search-position-value source-text-length)
       (index-of-g2-text-too-large-eval-error
	 (1+f search-position-value)
	 source-text-value
	 'get-next-token
	 cached-top-of-stack))
      ((<f search-position-value 0)
       (index-of-g2-text-too-large-eval-error
	 (1+f search-position-value)
	 source-text-value
	 'get-next-token
	 cached-top-of-stack))
      (t
       (let* ((result-struct (search-for-match-using-tokenizer
			       tokenizer
			       source-text-value
			       search-position-value)))
	 (setq result (make-evaluation-structure-from-parse-object-reclaiming-it
			result-struct)))))
    (reclaim-evaluation-text source-text)
    (reclaim-evaluation-integer search-position)
    result))



(def-funcalled-evaluator (get-next-token
			   get-next-token-4 4)
    (tokenizer source-text search-position include-string-p-arg)
    (32 (inference procedure)
	((class tokenizer) text integer truth-value) (structure)
	funcall-eval-type-4-arg
	nil pprint-functional-evaluator)
  (let* ((search-position-value
	   (1-f (evaluation-integer-value search-position)))
	 (source-text-value (evaluation-text-value source-text))
	 (source-text-length (g2-text-length source-text-value))
	 (include-string-p (evaluation-truth-value-value
			     include-string-p-arg))
	 (result nil))
    (cond
      ((frame-status-and-notes tokenizer)
       (bad-tokenizer-specification-error
	 tokenizer 'get-next-token cached-top-of-stack))
      ((>f search-position-value source-text-length)
       (index-of-g2-text-too-large-eval-error
	 (1+f search-position-value)
	 source-text-value
	 'get-next-token
	 cached-top-of-stack))
      ((<f search-position-value 0)
       (index-of-g2-text-too-large-eval-error
	 (1+f search-position-value)
	 source-text-value
	 'get-next-token
	 cached-top-of-stack))
      (t
       (let* ((result-struct
		(search-for-match-using-tokenizer
		  tokenizer
		  source-text-value
		  search-position-value)))
	 (setq result
	       (if include-string-p
		   (make-evaluation-structure-with-text-from-parse-object-reclaiming-it
		     result-struct source-text)
		   (make-evaluation-structure-from-parse-object-reclaiming-it
		     result-struct))))))
    (reclaim-evaluation-text source-text)
    (reclaim-evaluation-integer search-position)
    result))


;;; The `LEXEME stack-evaluator' takes a token structure of the type returned
;;; by get-next-token, and a source string, and extracts the portion of the
;;; string.  It is syntactic sugar for get-from-text.

(def-funcalled-evaluator lexeme (source-text token)
    (99 (inference procedure)
	(text (structure)) text
	funcall-eval-type-2-arg
	nil pprint-functional-evaluator)
  (let ((match-start (structure-slot
		       (car token) 'start-index no-tokenizer-match-start-index))
	(match-end (structure-slot
		     (car token) 'end-index no-tokenizer-match-end-index)))
    (if (=f match-end no-tokenizer-match-end-index)
	(make-evaluation-text #w"")
	(make-evaluation-text-reclaiming-argument
	  (get-from-g2-text
	    source-text
	    match-start
	    match-end)))))

#+development
(defun show-g2-token-structure (g2-token-structure)
  (let ((struct-array (car g2-token-structure)))
    (format t "Token-type: ~s~%"
	    (structure-slot struct-array 'token-type nil))
    (format t "Lexeme: ~s~%"
	    (structure-slot struct-array 'lexeme nil))
    (format t "Start-index: ~s~%"
	    (structure-slot struct-array 'start-index nil))
    (format t "End-index: ~s~%"
	    (structure-slot struct-array 'end-index nil))))
					       






;;;; Type Conversion Function Evaluators




;;; The quantity function, symbol function (new to release 3.0), and the
;;; truth-value function (described elsewhere in this module) are offered as a
;;; beginning of a type conversion facility.  There could eventually also be a
;;; TEXT converter, though the existing square brackets in a pair of quotes
;;; prints value for users already.



;;; The `QUANTITY stack-evaluator' converts a value to type quantity.  It
;;; accepts one argument of type truth-value, text, or quantity.  If the
;;; argument is of type text, a quantity is returned if the text begins with a
;;; quantity, ignoring any leading whitespace.  Otherwise, an error is
;;; signalled.  If the argument is of type truth-value or quantity, a quantity
;;; is returned.  This evaluator is available in the inference engine and
;;; procedures.

;;; Note that there is a problem if we do not know the type of the argument.  If
;;; it actually is a truth-value, then we would simply return the value, leaving
;;; in the range of -1000 to 1000 instead of converting it to a float.  So, to
;;; always get a consistent behavior for quantity, it must always know the type
;;; of its argument.  This will be a problem, since we do not know the type of
;;; the value returned from calls to user defined functions.  -jra 11/24/90

;; Check the above comment with jra!!  The following in-line evaluator is able
;; to distinguish truth-values.  Why should truth-value values have their
;; internal fixnum returned??  cpm, 6/24/91

;;; The datum version of the quantity evaluator is in-line so that the evaluator
;;; can distinguish between truth-value and numeric evaluation-values.

(def-in-line-evaluator (quantity quantity-datum 5)
		       (51 (inference procedure) ((or number truth-value text))
			   number t pprint-functional-evaluator)
  (setq register-2 (stack-arg 0))
  (setq register-1 (coerce-evaluation-value-to-quantity register-2))
  (when (text-string-p register-1)
    (raw-stack-error-named-error top-of-stack register-1))
  (reclaim-evaluation-value register-2))


(def-stack-error empty-string-eval-error (evaluator-name top-of-stack)
  "The ~a function received a text argument \"\"."
  evaluator-name)

(def-stack-error type-conversion-eval-error (value type evaluator-name top-of-stack)
  (if (evaluation-value-p value)
      "The ~a function could not convert the argument ~NV to type ~a."
      "The ~a function could not convert the argument ~A to type ~a.")
  evaluator-name value type)


;;; The function `coerce-evaluation-value-to-quantity' is called from the
;;; quantity datum in-line evaluator.  It is a separate function to save space
;;; in the in-line instructions.  This function may call stack-error and not
;;; return.

(defun coerce-evaluation-value-to-quantity
       (number-truth-value-or-text)
  (cond ((evaluation-truth-value-p number-truth-value-or-text)
	 (make-evaluation-float
	   (/e (coerce-fixnum-to-gensym-float
		 (evaluation-truth-value-value number-truth-value-or-text))
	       #.(coerce-to-gensym-float truth))))
	((evaluation-quantity-p number-truth-value-or-text)
	 ;; Makes a new quantity, since the caller may reclaim the argument.
	 (make-evaluation-quantity (evaluation-quantity-value
				     number-truth-value-or-text)))
	((evaluation-text-p number-truth-value-or-text)
	 (let ((text-length (g2-text-length number-truth-value-or-text))
	       end-index
	       start-index)
	   (cond ((=f text-length 0)
		  (empty-string-eval-error-message 'quantity))
		 (t
		  (setq end-index text-length)
		  (setq start-index (skip-whitespace-in-string
				      number-truth-value-or-text 0 end-index))
		  (cond ((>=f start-index end-index)
			 ;; all whitespace in string.
			 (type-conversion-eval-error-message
			   number-truth-value-or-text 'quantity
			   'quantity))
			(t
			 (with-temporary-gensym-float-creation quantity
			   (multiple-value-bind (number? kind)
			       (read-number-from-text-string
				 number-truth-value-or-text
				 start-index end-index)
			     (cond
			       ((or (null number?)
				    (eq number? 'underflow) ; should be sep. error?! (MHD)
				    (eq number? 'overflow))
				(type-conversion-eval-error-message
				  number-truth-value-or-text 'quantity
				  'quantity))
			       ((eq kind 'float)
				(make-evaluation-float number?))
			       (t
				(make-evaluation-integer number?)))))))))))))


(def-funcalled-evaluator (quantity quantity-truth-value 4) (truth-value)
			 (48 (inference procedure)
			     (truth-value) float
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let* ((truth-value-value (evaluation-truth-value-value truth-value))
	 (result
	   (make-evaluation-float
	     (/e (coerce-fixnum-to-gensym-float truth-value-value)
		 #.(coerce-to-gensym-float truth)))))
    (reclaim-evaluation-truth-value truth-value)
    result))


;; There is no need for a float or integer version of quantity.

(def-funcalled-evaluator (quantity quantity-quantity 3) (quantity)
			 (49 (inference procedure)
			     (number) number
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  quantity)


(def-funcalled-evaluator (quantity quantity-text) (text)
			 (50 (inference procedure)
			     (text) number
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let* ((text-value (evaluation-text-value text))
	 (text-length (g2-text-length text-value))
	 end-index
	 start-index
	 (result nil))
    (cond
      ((=f text-length 0)
       (empty-string-eval-error 'quantity cached-top-of-stack))
      (t
       (setq end-index text-length)
       (setq start-index (skip-whitespace-in-string text-value 0 end-index))
       (cond
	 ((>=f start-index end-index)
	  ;; all whitespace in string.
	  (type-conversion-eval-error
	    text-value 'quantity 'quantity cached-top-of-stack))
	 (t
	  (with-temporary-gensym-float-creation quantity
	    (multiple-value-bind (number? kind)
		(read-number-from-text-string
		  text-value start-index end-index)
	      (cond
		((or (null number?)
		     (eq number? 'underflow)
		     (eq number? 'overflow))
		 (type-conversion-eval-error
		   text-value 'quantity 'quantity cached-top-of-stack))
		((eq kind 'float)
		 (setq result (make-evaluation-float number?)))
		((eq kind 'long)
		 (setq result (make-evaluation-long number?)))
		(t
		 (setq result (make-evaluation-integer number?)))))
	    (when (and (eq 0 result) (< (- end-index start-index) 10))
	      (setq result
		    (make-evaluation-integer
		      (read-hex-number-from-text-string
			text-value start-index end-index)))))))))
    (reclaim-evaluation-text text)
    result))



;;; The `SYMBOL stack-evaluator' converts a value to type symbol.  It accepts
;;; one argument of type text or datum.  If the argument is of type text or
;;; symbol, a symbol is returned.  When converting a text to a symbol, the text
;;; is "read" as though by the same process that the G2 editor does when the
;;; user enters a symbol.  This involves, among other things, the upper casing
;;; of letters.  

;;; Lisp developers can think of this as an analog of READ-FROM-STRING; it is,
;;; by comparison, NOT an analog of Lisp's INTERN.

;;; This evaluator is available in the inference engine and procedures.

;;; As an optimization for simple cases, this uses the subfunction (actually a
;;; submacro in production) `try-to-read-g2-symbol-oversimplified-but-fast',
;;; which can recognize a subset of strings that are valid symbols (quickly) if
;;;
;;;    (1) total string length <= 200;
;;;    (2) 0 or more leading tab or space characters;
;;;    (3) initial character is A-Z | a-z | ' | _  ;
;;;    (4) 0 or more following characters that are: A-Z | a-z | 0-9 | - | _ | . | '  ; and
;;;    (5) 0 or more trailing tab or space characters
;;;
;;; If it recognizes such a symbol, it returns it.  Otherwise, it returns nil.
;;; Returning nil cannot, however, be taken to mean that a g2 symbol cannot be
;;; read from the string, so the (slow) reader still has to be applied in that
;;; case.  Note that the user symbol NIL, literally, would be returned as :NIL,
;;; i.e., the symbol with print name NIL in the keyword package, thus
;;; distinguishing it from the Lisp value nil.

(defun symbol-conversion-error
    (evaluation-text-string top-of-stack problem-string? &optional function-name?)
  (let* ((length (text-string-length evaluation-text-string))
	 (max-length 200)
	 (truncate-p (>f length max-length))
	 (small-text
	   (if truncate-p
	       (text-string-substring evaluation-text-string 0 max-length)
	       evaluation-text-string))
	 (the-text
	   (tformat-text-string
	     (if truncate-p
		 "beginning with \"~a...\""
		 "\"~a\"")
	     small-text)))
    (write-stack-error
	top-of-stack
      (tformat
	"The ~(~a~) function could not convert the text ~a to a symbol."
	(or function-name? 'symbol)
	the-text)
      (when problem-string?
	(tformat "  ~a" problem-string?))
      (when truncate-p
	(reclaim-text-string small-text))
      (reclaim-text-string the-text))))

(defun-substitution-macro try-to-read-g2-symbol-oversimplified-but-fast (string)
  (let* ((start 0)
	 (end (lengthw string))
	 (index 0)
	 (char #u0000))
    (declare (type fixnum start end index)
	     (type wide-character char))
    (if (and (<=f end 200)
	     (loop until (>=f index end)
		   do (setq char (charw string index))
		   when (cond
			  ((or (char<=w #.%\a char #.%\z)
			       (char<=w #.%\A char #.%\Z)
			       (char=w char #.%\_)
			       (char=w char #.%\'))
			   t))
		     do (setq start index)
			(return t)
		   when (not (or (char=w char #.%space) (char=w char #.%tab)))
		     do (return nil)
		   do (incff index))
	     (loop until (>=f index end)
		   do (setq char (charw string index))
		      (cond
			((cond
			   ((or (char<=w #.%\a char #.%\z)
				(char<=w #.%\A char #.%\Z)
				(char<=w #.%\0 char #.%\9)
				(char=w char #.%\')  (char=w char #.%\_)
				(char=w char #.%\-) (char=w char #.%\.))
			    t))
			 (incff index))
			((or (and (simple-character-code-p ; ascii range
				    (wide-character-code char))	; includes space
				  (not (char=w char #.%\@))
				  (not (char=w char #.%\:)))
			     (char=w char #.%tab)
			     (newline-p char))
			 ;; What is known to definitely delimit this symbol?
			 ;; Ascii punctuation chars, minus these:
			 ;;    :@'_-.  (last four checked already)
			 ;; Tab, space, or any newline character.
			 ;; Note: this test run at most once per call.
			 (loop-finish))
			(t (return nil)))
		   finally
		     (setq end index)
		     (return t)))
	(prog1 (or (intern-and-upcase-simple-symbol-portion-of-wide-string
		     string start end nil)
		   :nil)		; good ole' special :nil rule
	  (reclaim-wide-string string)))))

;; too complex to embed into stack evaluator
(defmacro create-symbol-from-text-string-macro (evaluation-text-string top-of-stack)
  `(or
     (try-to-read-g2-symbol-oversimplified-but-fast ,evaluation-text-string)
     (multiple-value-bind (attribute-name? end-point class-qualifier?)
	 (read-attribute-name-from-text-string ,evaluation-text-string)
       (declare (ignore end-point))
       (cond
	 (class-qualifier?
	  ;; If class-qualifier? is non-nil, we know that attribute-name?
	  ;; is non-nil.  We don't need to check that.
	  (let* ((class-qualified-symbol-text-string
		   (make-unique-slot-name-symbol-text-string
		     class-qualifier? attribute-name?))
		 (problem-string?
		   (non-valid-symbol-text-string-p
		     class-qualified-symbol-text-string)))
	    (cond
	      (problem-string?
	       (reclaim-text-string class-qualified-symbol-text-string)
	       (symbol-conversion-error
		 ,evaluation-text-string ,top-of-stack problem-string?))
	      (t	       
	       (reclaim-evaluation-text ,evaluation-text-string)
	       (make-evaluation-symbol
		 (intern-unique-slot-name-text-string
		   class-qualified-symbol-text-string))))))
	 (attribute-name?
	  (let* ((problem-string?
		   (non-valid-symbol-text-string-p
		     (symbol-name-text-string attribute-name?))))
	    (cond
	      (problem-string?
	       (symbol-conversion-error
		 ,evaluation-text-string ,top-of-stack problem-string?))
	      (t
	       (reclaim-evaluation-text ,evaluation-text-string)
	       (make-evaluation-symbol attribute-name?)))))
	 (t
	  (symbol-conversion-error ,evaluation-text-string ,top-of-stack nil))))))

(defun create-symbol-from-text-string (evaluation-text-string top-of-stack)
  (create-symbol-from-text-string-macro evaluation-text-string top-of-stack))

(def-funcalled-evaluator (symbol symbol-datum 5) (symbol-or-text)
			 (30 (inference procedure)
			     ((or symbol text)) symbol 
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (cond
    ((evaluation-symbol-p symbol-or-text)
     symbol-or-text)
    (t
     ;; else, evaluation-text -- call the function defined
     ;; by the following form.
     (eval-symbol-text-funcalled symbol-or-text))))


(def-funcalled-evaluator (symbol symbol-text 1) (text)
			 (31 (inference procedure)
			     (text) symbol
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (create-symbol-from-text-string
    (evaluation-text-value text)
    cached-top-of-stack))



;;; The `TEXT-TO-SYMBOL stack-evaluator' returns the symbol that is the result
;;; of interning the supplied text.  There is barely any restriction on text,
;;; i.e.,:
;;;
;;;   (a) must be no longer than the maximum length of
;;;        symbols (65,533 characters); and
;;;   (b) must not contain illegal Unicode characters #+uFFFE or #+uFFFF
;;;
;;; In 5.x, this did not catch problem strings of any kind.  In 6.0 this catches
;;; problem strings using non-valid-symbol-text-string-p.  However, note that
;;; this allows the empty string; it's not a problem to intern "" (Lisp symbol
;;; ||), and we'll eventually have a way to represent them as tokens, i.e., with
;;; brakets of some kind, so we can print them and tokenize them.
;;;
;;; Note: in releases prior to 8.0r1, this failed to perform the following
;;; necessary processing as follows:
;;;
;;;   (1) turn nil into :nil (nil in the keyword package); or
;;;   (2) mark syntactically numeric symbols

(def-funcalled-evaluator text-to-symbol (text)
    (114 (inference procedure)
	 (text) symbol
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (let ((problem-string? (non-valid-symbol-text-string-p text)))
    (cond
      ((and problem-string?
	    ;; exception for empty string:  -mhd, 7/3/00
	    (not (eq problem-string? message-illegal-symbol-text-string-empty)))
       (symbol-conversion-error
	 text cached-top-of-stack problem-string?
	 'text-to-symbol))
      (t
       (computing-syntactically-numeric-p
	 (let* ((wide-string (evaluation-text-value text))
		(length (wide-string-length wide-string))
		(symbol
		  (or (interning-text-character-sequence
			(loop for i from 0 below length
			      as char = (charw wide-string i)
			      do (next-character-for-intern char)
				 (advance-syntactically-numeric-p char))
			(result-of-intern))
		      ;; special nil rule for G2 symbols: nil => :nil
		      :nil)))
	   (when (result-of-syntactically-numeric-p)
	     (setf (type-of-syntactic-anomaly symbol) 'numeric))
	   (reclaim-wide-string wide-string)
	   symbol))))))





;;;; Time Function Evaluators

(def-stack-error invalid-argument-eval-error
       (value argument-name evaluator-name top-of-stack)
  (if (evaluation-value-p value)
      "The ~a function received an invalid ~a argument ~NV."
      "The ~a function received an invalid ~a argument ~A.")
  evaluator-name argument-name value)

;;; The `YEAR stack-evaluator' takes a time argument (i.e., an integer count of
;;; seconds from the start of the current run of G2) and returns the year based
;;; on that time, for example 1990.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.

(def-funcalled-evaluator year (time) (51 all
					 (number) integer
					 funcall-eval-type-1-arg
					 nil pprint-functional-evaluator)
  (cond ((evaluation-integer-p time)
	 (multiple-value-bind (second minute hour date month year)
	     (decode-gensym-time
	       (+f (evaluation-integer-value time)
		   (clock-get gensym-time-at-start)))
	   (declare (ignore second minute hour date month))
	   (reclaim-evaluation-integer time)
	   (make-evaluation-integer year)))
	;; GENSYMCID-1326 added, see NOTES in funcalled-evaluator TIME
	((evaluation-float-p time)
	 (with-temporary-gensym-float-creation year-evaluator
	   (multiple-value-bind (second minute hour date month year)
	       (gensym-decode-unix-time
		 (+e (evaluation-float-value time)
		     (managed-float-value (clock-get g2-time-at-start))))
	     (declare (ignore second minute hour date month))
	     (reclaim-evaluation-float time)
	     (make-evaluation-integer year))))
	(t
	 (invalid-argument-eval-error time 'time 'year cached-top-of-stack))))


;;; The `MONTH stack-evaluator' takes a time argument (i.e., an integer count of
;;; seconds from the start of the current run of G2) and returns the month based
;;; on that time as a quantity from 1 to 12.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.

(def-funcalled-evaluator month (time) (52 all
					  (number) integer
					  funcall-eval-type-1-arg
					  nil pprint-functional-evaluator)
  (cond ((evaluation-integer-p time)
	 (multiple-value-bind (second minute hour date month year)
	     (decode-gensym-time
	       (+f (evaluation-integer-value time)
		   (clock-get gensym-time-at-start)))
	   (declare (ignore second minute hour date year))
	   (reclaim-evaluation-integer time)
	   (make-evaluation-integer month)))
	;; GENSYMCID-1326 added, see NOTES in funcalled-evaluator TIME
	((evaluation-float-p time)
	 (with-temporary-gensym-float-creation month-evaluator
	   (multiple-value-bind (second minute hour date month year)
	       (gensym-decode-unix-time
		 (+e (evaluation-float-value time)
		     (managed-float-value (clock-get g2-time-at-start))))
	     (declare (ignore second minute hour date year))
	     (reclaim-evaluation-float time)
	     (make-evaluation-integer month))))
	(t
	 (invalid-argument-eval-error time 'time 'month cached-top-of-stack))))


;;; The `DAY-OF-THE-MONTH stack-evaluator' takes a time argument (i.e., an
;;; integer count of seconds from the start of the current run of G2) and
;;; returns the day of the month based on that time as a quantity from 1 to 31.
;;; This evaluator is available in the inference engine, procedures, and the
;;; simulator.

(def-funcalled-evaluator day-of-the-month (time) 
			 (53 all (number) integer
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (cond ((evaluation-integer-p time)
	 (multiple-value-bind (second minute hour date month year)
	     (decode-gensym-time
	       (+f (evaluation-integer-value time)
		   (clock-get gensym-time-at-start)))
	   (declare (ignore second minute hour month year))
	   (reclaim-evaluation-integer time)
	   (make-evaluation-integer date)))
	;; GENSYMCID-1326 added, see NOTES in funcalled-evaluator TIME
	((evaluation-float-p time)
	 (with-temporary-gensym-float-creation day-of-the-month-evaluator
	   (multiple-value-bind (second minute hour date month year)
	       (gensym-decode-unix-time
		 (+e (evaluation-float-value time)
		     (managed-float-value (clock-get g2-time-at-start))))
	     (declare (ignore second minute hour month year))
	     (reclaim-evaluation-float time)
	     (make-evaluation-integer date))))
	(t
	 (invalid-argument-eval-error time 'time
				      'day-of-the-month cached-top-of-stack))))


;;; The `DAY-OF-THE-WEEK stack-evaluator' takes a time argument (i.e., an
;;; integer count of seconds from the start of the current run of G2) and
;;; returns the day of the week based on that time as one of the symbols Monday,
;;; Tuesday etc.  This evaluator is available in the inference engine,
;;; procedures, and the simulator.

(defvar day-of-the-week-names
  '(monday tuesday wednesday thursday friday saturday sunday))

(def-funcalled-evaluator day-of-the-week (time) 
			 (54 all (number) symbol
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (cond ((evaluation-integer-p time)
	 (multiple-value-bind
	     (second minute hour date month year day-of-the-week)
	     (decode-gensym-time
	       (+f (evaluation-integer-value time) (clock-get gensym-time-at-start)))
	   (declare (ignore second minute hour date month year))
	   (reclaim-evaluation-integer time)
	   (make-evaluation-symbol
	     (nth day-of-the-week day-of-the-week-names))))
	;; GENSYMCID-1326 added, see NOTES in funcalled-evaluator TIME
	((evaluation-float-p time)
	 (with-temporary-gensym-float-creation day-of-the-week-evaluator
	   (multiple-value-bind
	       (second minute hour date month year day-of-the-week)
	       (gensym-decode-unix-time
		 (+e (evaluation-float-value time)
		     (managed-float-value (clock-get g2-time-at-start))))
	     (declare (ignore second minute hour date month year))
	     (reclaim-evaluation-float time)
	     (make-evaluation-symbol
	      (nth day-of-the-week day-of-the-week-names)))))
	(t
	 (invalid-argument-eval-error time 'time
				      'day-of-the-week cached-top-of-stack))))


;;; The `HOUR stack-evaluator' takes a time argument (i.e., an integer count of
;;; seconds from the start of the current run of G2) and returns the hour of the
;;; time as a quantity from 0 to 23.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.

(def-funcalled-evaluator hour (time) (55 all (number) integer
					 funcall-eval-type-1-arg
					 nil pprint-functional-evaluator)
  (cond ((evaluation-integer-p time)
	 (multiple-value-bind (second minute hour)
	     (decode-gensym-time
	       (+f (evaluation-integer-value time) (clock-get gensym-time-at-start)))
	   (declare (ignore second minute))
	   (reclaim-evaluation-integer time)
	   (make-evaluation-integer hour)))
	;; GENSYMCID-1326 added, see NOTES in funcalled-evaluator TIME
	((evaluation-float-p time)
	 (with-temporary-gensym-float-creation hour-evaluator
	   (multiple-value-bind (second minute hour)
	       (gensym-decode-unix-time
		 (+e (evaluation-float-value time)
		     (managed-float-value (clock-get g2-time-at-start))))
	     (declare (ignore second minute))
	     (reclaim-evaluation-float time)
	     (make-evaluation-integer hour))))
	(t
	 (invalid-argument-eval-error time 'time 'hour cached-top-of-stack))))


;;; The `MINUTE stack-evaluator' takes a time argument (i.e., an integer count
;;; of seconds from the start of the current run of G2) and returns the minute
;;; of the hour of the time as a quantity from 0 to 59.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

(def-funcalled-evaluator minute (time) (56 all (number) integer
					   funcall-eval-type-1-arg
					   nil pprint-functional-evaluator)
  (cond ((evaluation-integer-p time)
	 (multiple-value-bind (second minute)
	     (decode-gensym-time
	       (+f (evaluation-integer-value time) (clock-get gensym-time-at-start)))
	   (declare (ignore second))
	   (reclaim-evaluation-integer time)
	   (make-evaluation-integer minute)))
	;; GENSYMCID-1326 added, see NOTES in funcalled-evaluator TIME
	((evaluation-float-p time)
	 (with-temporary-gensym-float-creation minute-evaluator
	   (multiple-value-bind (second minute)
	       (gensym-decode-unix-time
		 (+e (evaluation-float-value time)
		     (managed-float-value (clock-get g2-time-at-start))))
	     (declare (ignore second))
	     (reclaim-evaluation-float time)
	     (make-evaluation-integer minute))))
	(t
	 (invalid-argument-eval-error time 'time 'minute cached-top-of-stack))))


;;; The `SECOND stack-evaluator' takes a time argument (i.e., an integer count
;;; of seconds from the start of the current run of G2) and returns the second
;;; of the minute of the time as a quantity from 0 to 59.  This evaluator is
;;; available in the inference engine, procedures, and the simulator.

(def-funcalled-evaluator second (time) (57 all (number) integer
					   funcall-eval-type-1-arg
					   nil pprint-functional-evaluator)
  (cond ((evaluation-integer-p time)
	 (let ((second
		(decode-gensym-time
		  (+f (evaluation-integer-value time) (clock-get gensym-time-at-start)))))
	   (reclaim-evaluation-integer time)
	   (make-evaluation-integer second)))
	;; GENSYMCID-1326 added, see NOTES in funcalled-evaluator TIME
	((evaluation-float-p time)
	 (with-temporary-gensym-float-creation second-evaluator
	   (let ((second
		  (gensym-decode-unix-time
		    (+e (evaluation-float-value time)
			(managed-float-value (clock-get g2-time-at-start))))))
	     (reclaim-evaluation-float time)
	     (make-evaluation-integer second))))
	(t
	 (invalid-argument-eval-error time 'time 'second cached-top-of-stack))))


;;; The `TIME stack-evaluator' accepts six arguments, a year, month, day, hour,
;;; minute, and second.  It returns a time stamp encoding, a number identical to
;;; what "the current time" would have returned at that given time.  This
;;; evaluator is available in the inference engine and procedures.

(def-funcalled-evaluator time (year month date hour minute second)
    (58 (inference procedure)
	(integer integer integer integer integer integer)
	number
	funcall-eval-type-6-arg
	nil pprint-functional-evaluator)
  (let ((year-value (evaluation-integer-value year))
	(month-value (evaluation-integer-value month))
	(date-value (evaluation-integer-value date))
	(hour-value (evaluation-integer-value hour))
	(minute-value (evaluation-integer-value minute))
	(second-value (evaluation-integer-value second)))
    (unless (>=f year-value 1900)
      ;; testing for year argument as 90 instead of 1990.
      (invalid-argument-eval-error year-value 'year 'time cached-top-of-stack))
    (unless (<=f 1 month-value 12)
      (invalid-argument-eval-error month-value 'month 'time cached-top-of-stack))
    ;; jh, 4/14/93.  Added more precision in the error checking for dates.
    (unless (fixnum-case month-value 
	      ((2) (if (leap-year-p year-value)
		       (<=f 1 date-value 29)
		       (<=f 1 date-value 28)))
	      ((4 6 9 11) (<=f 1 date-value 30))
	      (otherwise (<=f 1 date-value 31)))
      (invalid-argument-eval-error
	date-value 'day-of-the-month 'time cached-top-of-stack))
    (unless (<=f 0 hour-value 24)
      (invalid-argument-eval-error hour-value 'hour 'time cached-top-of-stack))
    (unless (<=f 0 minute-value 59)
      (invalid-argument-eval-error minute-value 'minute 'time cached-top-of-stack))
    (unless (<=f 0 second-value 59)
      (invalid-argument-eval-error second-value 'second 'time cached-top-of-stack))

    (with-temporary-gensym-float-creation time-evaluator
      (let ((float-encoded-time
	      (-e (gensym-encode-unix-time
		    second-value minute-value hour-value date-value month-value
		    year-value)
		  (managed-float-value (clock-get g2-time-at-start)))))
	(declare (type gensym-float float-encoded-time))
	(cond ((<=e most-negative-fixnum-as-float
		    float-encoded-time
		    most-positive-fixnum-as-float)
	       (reclaim-evaluation-integer year)
	       (reclaim-evaluation-integer month)
	       (reclaim-evaluation-integer date)
	       (reclaim-evaluation-integer hour)
	       (reclaim-evaluation-integer minute)
	       (reclaim-evaluation-integer second)
	       (make-evaluation-integer (floore-first float-encoded-time)))
	      (t
	       ;; GENSYMCID-1326: The result of the TIME expression is greater than the
	       ;;                 maximum quantity value.
	       ;; NOTES:
	       ;; Now we return evaluation-floats on values exceed fixnum range, to use
	       ;; the float, other funcalled-evaluators like YEAR, MONTH, ... have to be
	       ;; upgraded to accept evaluation floats. -- Chun Tian (binghe), 1/25/2015
	       (make-evaluation-float float-encoded-time)))))))






;;;; Relation Expression Evaluators




;;; The `IS-RELATED stack evaluator' and `IS-NOT-RELATED stack evaluator' test
;;; if two items are related and return truth or falsity.  These evaluators are
;;; available in the inference engine, procedures, and the simulator.

;; Comment From Simulate3!!  Note that because dynamic relations can only be
;; established via rules (typically "initially" rules), and because data servers
;; are initialized before any rules are fired, dynamic relations cannot be used
;; to compute initial values for state variables.  Review!  A better way to
;; synchronize initialization of the simulator with the rest of the system is
;; needed.  Parameters are a work-around.  A separate "start" action for the
;; simulator may be the best solution.

;; After talking with Andy, he agrees that this could be dealt with by making
;; the simulator initialize itself after the initialize data server call.  At
;; the moment, users can work around this by using simulator models.  -jra
;; 2/18/92
				  
(def-funcalled-evaluator is-related (given-relation-name item1 item2)
			 (59 all (symbol (class item) (class item)) boolean
			     funcall-eval-type-3-arg
			     nil pprint-is-related-evaluator)
  (let ((result
	  (if (is-related-macro
		(evaluation-symbol-symbol given-relation-name) item1 item2)
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-symbol given-relation-name)
    result))


(def-funcalled-evaluator is-not-related (given-relation-name item1 item2)
			 (60 all (symbol (class item) (class item)) boolean
			     funcall-eval-type-3-arg
			     nil pprint-is-not-related-evaluator)
  (let ((result
	  (if (is-related-macro
		(evaluation-symbol-symbol given-relation-name) item1 item2)
	      (make-evaluation-truth-value falsity)
	      (make-evaluation-truth-value truth))))
    (reclaim-evaluation-symbol given-relation-name)
    result))






;;;; Evaluators Not In The G2 User Manual




;;; The following sections contain evaluators that are not documented in the
;;; expressions chapter of the G2 User Manual!!  This could be a case of missing
;;; or misplaced documentation or more usually, that the evaluators are internal
;;; to G2 and therefore not available to the user.






;;;; Misc. Evaluators




;;; The `VAR-SPOT stack-evaluator' is defined to allow the inference engine to
;;; use values which are stored in procedure environments.  This situation
;;; arises in COLLECT DATA and WAIT statements.  It takes a var-spot as its only
;;; argument, and returns the value stored the that spot of the environment in
;;; the special variable code-body-environment.

;;; Within procedures, a variable spot location is inserted into parsed
;;; s-expressions and handed off to the stack compiler to compile.  This special
;;; form converter finds these var-spots, and makes a stack-node-instruction out
;;; of them.

(def-special-form-converter var-spot (expression)
  (make-stack-node-instruction
    'push-from-surrounding-local-var
    expression))



;;; The `FALSE stack-evaluator' is identical to "not" operationally, but may be
;;; passed through a quantifier by the compiler.  This evaluator is available in
;;; the inference engine and procedures.

(def-funcalled-evaluator false (truth-value)
			 (61 (inference procedure) (truth-value) truth-value
			     funcall-eval-type-1-arg
			     nil pprint-false-evaluator)
  (let ((result-value
	  (fuzzy-not (evaluation-truth-value-value truth-value))))
    (reclaim-evaluation-truth-value truth-value)
    (make-evaluation-truth-value result-value)))

;; It would be more efficient if the above false evaluator could call some sort
;; of mutate-evaluation-truth-value function.  - cpm, 5/14/93



;;; The `IDENTITY stack-evaluator' is implemented with a special form converter
;;; that transforms into a stack node tree of its expression argument.  This
;;; evaluator is used to keep the order of expressions grouped by parentheses.

(def-special-form-converter identity (expression)
  (convert-expression-to-stack-node-tree (second expression)))




;;; The `ATTRIBUTE-VALUE stack evaluator' is an expression that returns the item
;;; or constant value contained in the specified attribute.  The name of the
;;; attribute is determined from a symbolic-expression.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.

;;; This evaluator is available in the inference engine and procedures.

;;; ATTRIBUTE-VALUE (<object>, <attribute-name)


(declare-instruction-for-optimizer
  'attribute-value
  '(no-wait-states
    cannot-read-local-variables
    cannot-write-local-variables
    cannot-read-roles
    cannot-write-roles))

(def-special-form-converter attribute-value (expression)
  (let ((arguments
	  (stack-list
	    (convert-expression-to-stack-node-tree (second expression))
	    (convert-expression-to-stack-node-tree (third expression))))
	(attribute-value-node
	  (make-stack-node-instruction 'attribute-value nil)))
    (setf (stack-node-argument-nodes attribute-value-node)
	  arguments)
    attribute-value-node))



;;; The preferred instruction chooser for ATTRIBUTE-VALUE chooses instructions
;;; and types on its arguments, and then sets its own return value.

(def-preferred-instruction-chooser attribute-value
  (declare (ignore required-type extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    ;; next-list-element role server argument.
    (setf (first argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (first argument-nodes)
	    '(class object)))
    (setf (second argument-nodes)
	  (choose-stack-node-instructions-and-types
	    (second argument-nodes)
	    'symbol))
    (setf (stack-node-value-type stack-node-instruction)
	  '(or item-or-datum (no-item)))))



;;; The stack node instruction emitter for Attribute-Value emits a call to the
;;; role-server.

(def-stack-node-instruction-emitter attribute-value
  (declare (ignore extra-info))
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction)))
    (emit-stack-node-tree byte-code-stream (first argument-nodes))     ;object
    (emit-stack-node-tree byte-code-stream (second argument-nodes))    ;attribute
    (call-stack-instruction-emitter evaluate-role
      byte-code-stream '(attribute-value item-or-datum) 2
      (type-specification-subtype-p
	'(no-item)
	(stack-node-value-type stack-node-instruction))
      nil nil nil)))


;added by SoftServe

;Declaration: special form converter for the call-procedure instruction

;Type: Lisp function (after macroexpansion)

;Purpose: converts S-expression to stack node tree

;Arguments: S-expression to convert

;Return behavior: returns stack node tree

;Side effects: None

;Memory impact: generates new stack-node tree

(def-special-form-converter call-procedure (expression)
  (gensym-dstruct-bind
    ((nil procedure-definition-designation . argument-expressions)
     expression)
    (loop with node = (make-stack-node-instruction
			'call-procedure
			(phrase-list
			  nil
			  (if (symbolp procedure-definition-designation)
			      procedure-definition-designation
			      nil)))
	  for argument in (if (car argument-expressions)
			       (car argument-expressions)
			       '()
			   )
	  collect (convert-expression-to-stack-node-tree argument)
	    into arg-nodes using stack-cons
	  finally
	    (setf (stack-node-argument-nodes node)
		  (stack-cons
			(convert-designation-to-stack-node-tree
			  procedure-definition-designation)
			
		    arg-nodes))
	    (return node))))

;end of changes

;;; The `CALL-FUNCTION stack evaluator' is a function used to call a user,
;;; foreign, or tabular function.  The function is determined at run-time from a
;;; designation of a function definition.  Therefore, since system-functions do
;;; not have G2 function definitions, this function can not call system
;;; functions directly.  To do this, a user would need to create a function
;;; definition that calls a system function.

;;; This evaluator will be implemented as a stack-node-instruction which emits
;;; its own instructions specifically.

;;; This evaluator is available in the inference engine and procedures.

;;; CALL-FUNCTION (<function-definition> {,<function-argument>})

(def-special-form-converter call-function (expression)
  (gensym-dstruct-bind
    ((nil function-definition-designation . argument-expressions)
     expression)
   
   
    (if nil 
        
    (loop with node = (make-stack-node-instruction
                       'call (compile-stack-expression-into-nodes 
                               ;(get-instance-with-name-if-any 'item
                                function-definition-designation;) 
                       ;'(class procedure) 
                       'item-or-datum)                           
                       (loop for arg in argument-expressions
			   ;for type-cons? = stable-proc-arg-types?
				;	  then (cdr type-cons?)
			   collect
			     (compile-stack-expression
			       arg ;(or (car type-cons?)
			                'item-or-datum);)
				   using stack-cons)
                       )
          for argument in argument-expressions
	  collect (convert-expression-to-stack-node-tree argument)
	    into arg-nodes using stack-cons
	  finally
	    (setf (stack-node-argument-nodes node)
		  (stack-cons
			(convert-designation-to-stack-node-tree
			  function-definition-designation)
		    arg-nodes))
	    (return node))
          

        
    (loop with node = (make-stack-node-instruction
			'call-function
			(phrase-list
			  nil
			  (if (symbolp function-definition-designation)
			      function-definition-designation
			      nil)))
	  for argument in argument-expressions
	  collect (convert-expression-to-stack-node-tree argument)
	    into arg-nodes using stack-cons
	  finally
	    (setf (stack-node-argument-nodes node)
		  (stack-cons
		    (if (designation-p function-definition-designation)
			(convert-designation-to-stack-node-tree
			  function-definition-designation)
			(progn
			  (compiler-error
			    "The first argument to call-function ~
			     must be an item of class ~
                             function-definition, tabular-function, ~
                             or foreign-function-declaration, ~
                             but the expression `~NE' could not ~
                             refer to such an item."
			    function-definition-designation)
			  (make-dummy-stack-node)))
		    arg-nodes))
	    (return node))
        
        )
        
        ))


;;; Note that CALL-FUNCTION instruction already has a preferred-instruction
;;; chooser and an instruction emitter.






;;;; Event Predicate Evaluators




;;; The `RECEIVES-A-VALUE stack evaluator' and `FAILS-TO-RECEIVE-A-VALUE stack
;;; evaluator' are event logical predicates which are used as targets of
;;; chaining whenever these events occur.  Receives a value always returns true.
;;; Fails-to-receive-a-value returns truth if the variable is still failed and
;;; returns falsity if not failed or if the designation is a temporary constant.
;;; These evaluators are only available in the inference engine.

;; The type of the argument to this evaluator should be item-or-datum, not just
;; class item.  The reason is that constant valued attributes of objects can
;; receive values which cause propagations to here.  The type check to ensure
;; that the argument to this expression is item caused a rule to signal an error
;; when it should have just accepted the symbolic datum which it received.
;; I have changed the argument type for this evaluator, but I'm sure this means
;; I need to change the dispatch type so that the argument can be reclaimed.
;; -jra 8/4/91

(def-funcalled-evaluator receives-a-value (item-or-datum)
			 (62 (inference)
			     ((or item-or-datum (no-item))) boolean
			     funcall-eval-type-1-arg)
  (reclaim-if-evaluation-value item-or-datum)
  (make-evaluation-truth-value truth))


;; Should fails-to-receive-a-value be restricted to variables??  The eval
;; version was not.  Can the argument be a temporary constant/datum??

(def-funcalled-evaluator fails-to-receive-a-value (item)
		   (63 (inference) ((class item)) boolean
		       funcall-eval-type-1-arg)
  (cond 
;      ((temporary-constant-p (stack-arg 0))
;       (reclaim-temporary-constant (stack-arg 0))
;       (values falsity 'never 'truth-value))
    (t
     (if (failed-p item)
	 (make-evaluation-truth-value truth)
	 (make-evaluation-truth-value falsity)))))



;;; The `IS MOVED stack evaluator', `IS MOVED BY THE USER stack evaluator', `IS
;;; MOVED BY THE INFERENCE ENGINE stack evaluator', and `IS MOVED BY G2 stack
;;; evaluator' are event logical predicates that are used as a place holders
;;; from which forward chaining links are generated.  They are chained to
;;; whenever an icon is moved.  These event predicates should always return
;;; true.  These evaluators are only available in the inference engine.

(def-funcalled-evaluator is-moved (item)
			 (64 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))

(def-funcalled-evaluator is-moved-by-the-user (item)
			 (65 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))

(def-funcalled-evaluator is-moved-by-g2 (item)
			 (67 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))



;;; The `BECOMES-RELATED stack evaluator' and `CEASES-TO-BE-RELATED stack
;;; evaluator' are event propositions to initiate activity based on relations
;;; between items.  A whenevever rule that has the first expression is invoked
;;; whenever the relation is established between the two items.  A whenever
;;; rules that has the second expression is invoked whenever the relation ceases
;;; to exist between the two items.  These evaluators are only available in the
;;; inference engine.

(def-funcalled-evaluator becomes-related (given-relation-name item1 item2)
			 (68 (inference)
			     (symbol (class item) (class item)) boolean
			     funcall-eval-type-3-arg)
  (let ((result 
	  (if (is-related-macro
		(evaluation-symbol-symbol given-relation-name) item1 item2)
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-symbol given-relation-name)
    result))


(def-funcalled-evaluator ceases-to-be-related (given-relation-name item1 item2)
			 (69 (inference)
			     (symbol (class item) (class item)) boolean
			     funcall-eval-type-3-arg)
  (let ((result 
	  (if (is-related-macro
		(evaluation-symbol-symbol given-relation-name) item1 item2)
	      (make-evaluation-truth-value falsity)
	      (make-evaluation-truth-value truth))))
    (reclaim-evaluation-symbol given-relation-name)
    result))



;;; The `IS ACTIVATED stack evaluator', and `IS DEACTIVATED stack evaluator' are
;;; event logical predicates that are used as place holders from which forward
;;; chaining links are generated.  They are chained to whenever an item is
;;; activated/deactivated.  These event predicates should always return true.
;;; These evaluators are only available in the inference engine.

(def-funcalled-evaluator is-activated (item)
			 (10 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))

(def-funcalled-evaluator is-deactivated (item)
			 (11 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))



;;; The `IS ENABLED stack evaluator', and `IS DISABLED stack evaluator' are
;;; event logical predicates that are used as place holders from which forward
;;; chaining links are generated.  They are chained to whenever an item is
;;; enabled/disabled.  These event predicates should always return true.
;;; These evaluators are only available in the inference engine.

(def-funcalled-evaluator is-enabled (item)
			 (12 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))

(def-funcalled-evaluator is-disabled (item)
			 (13 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))



;;; The `LOSES ITS VALUE stack evaluator', is an event logical predicate that is
;;; used as a place holder from which forward chaining links are generated.
;;; They are chained to whenever a variable loses its value.  This event
;;; predicate should always return true.  This evaluator is only available in
;;; the inference engine.

(def-funcalled-evaluator loses-its-value (variable)
			 (14 (inference) ((class variable)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore variable))
  (make-evaluation-truth-value truth))

;; Review with Jim and Rich whether this should be restricted to being a
;; variable, or whether other items such as parameters should be included!!



;;; The `IS CREATED stack evaluator', and `IS CREATED INDIRECT stack evaluator' are
;;; event logical predicates that are used as place holders from which forward
;;; chaining links are generated.  They are chained to whenever an item is
;;; created.  These event predicates should always return true.
;;; These evaluators are only available in the inference engine.

(def-funcalled-evaluator is-created (item)
			 (15 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))

;; Funcalled Evaluator 16 was is-created-indirect, which was deemed
;; unimplementable.  -jra&agh 12/30/96
;; Re-using this evaluator index for generic event rules.
;; - jed 7/23/98

(def-funcalled-evaluator generic-event (item event-name event-object)
			 (16 (inference)
			     ((class item) symbol (class item))
			     boolean
			     funcall-eval-type-3-arg)
  (declare (ignore item event-name event-object))
  (make-evaluation-truth-value truth))



;;; The `GENERIC BECOMES RELATED stack evaluator', and `GENERIC CEASES TO BE
;;; RELATED stack evaluator' are event logical predicates that are used as place
;;; holders from which forward chaining links are generated.  They are chained
;;; to whenever two items become related / cease to be related.  These
;;; evaluators are only available in the inference engine.

(def-funcalled-evaluator generic-becomes-related (item1 item2)
			 (17 (inference) ((class item) (class item)) boolean
			     funcall-eval-type-2-arg)
  (if (generic-is-related-macro item1 item2)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(def-funcalled-evaluator generic-ceases-to-be-related (item1 item2)
    (18 (inference) ((class item) (class item)) boolean
	funcall-eval-type-2-arg)
  (if (generic-is-related-macro item1 item2)
      (make-evaluation-truth-value falsity)
      (make-evaluation-truth-value truth)))



;;; The `GENERIC DIRECTLY CONNECTED TO stack evaluator', the `GENERIC DIRECTLY
;;; DISCONNECTED FROM stack evaluator', the `DIRECTLY CONNECTED TO' stack
;;; evaluator, and the `DIRECTLY DISCONNECTED FROM' stack evaluator are event
;;; logical predicates that are used as place holders from which forward
;;; chaining links are generated.  They are chained to whenever a connection is
;;; made to the designated item.  Note that the filter-symbol arg is ignored by
;;; the evaluators.  This is because the filter symbol is available at invoke
;;; time and is checked there, before the rule is even invoked.  Thus, only
;;; rules that pass the filter will be invoked and it is not necessary to check
;;; the filter symbol again in the evaluators.

;;; These evaluators are only available in the inference engine.

(def-funcalled-evaluator generic-directly-connected-to (connection filter-symbol item)
			 (19 (inference) ((class connection) symbol (class item)) boolean
			     funcall-eval-type-3-arg)
  (declare (ignore filter-symbol))
  
  (if (generic-directly-connected-p connection item)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(def-funcalled-evaluator generic-directly-disconnected-from (filter-symbol item)
			 (20 (inference) (symbol (class item)) boolean
			     funcall-eval-type-2-arg)
  (declare (ignore filter-symbol))
  (declare (ignore item))
  
  (make-evaluation-truth-value truth))

(def-funcalled-evaluator directly-connected-to (connection filter-symbol item)
			 (21 (inference) ((class connection) symbol (class item)) boolean
			     funcall-eval-type-3-arg)
  (declare (ignore filter-symbol))
  
  (if (generic-directly-connected-p connection item)  ; generic-directly-connected-p check works here since connection class
      (make-evaluation-truth-value truth)             ; is checked at invoke time.
      (make-evaluation-truth-value falsity)))

(def-funcalled-evaluator directly-disconnected-from (connection-class filter-symbol item)
			 (22 (inference) (symbol symbol (class item)) boolean
			     funcall-eval-type-3-arg)
  (declare (ignore connection-class))
  (declare (ignore filter-symbol))
  (declare (ignore item))
  ;; The evaluator is a no-op since the actual connection no longer exists at this point
  ;; and since all necessary checking is done at invoke time.
  
  (make-evaluation-truth-value truth))





;;; The `INDIRECTLY CONNECTED TO stack evaluator', and the `INDIRECTLY
;;; DISCONNECTED FROM stack evaluator' are event logical predicates that are
;;; used as place holders from which forward chaining links are generated.  They
;;; are chained to whenever a connection is made/broken between the designated
;;; items.  These evaluators are only available in the inference engine.

;; The args of these will have to change.  Need to add code to check to make
;; sure predicate is actually true (don't always return true)!!

(def-funcalled-evaluator indirectly-connected-to (item1 item2)
			 (23 (inference) ((class item) (class item)) boolean
			     funcall-eval-type-2-arg)
  (declare (ignore item1))
  (declare (ignore item2))
  
  (make-evaluation-truth-value truth))

(def-funcalled-evaluator indirectly-disconnected-from (item1 item2)
			 (24 (inference) ((class item) (class item)) boolean
			     funcall-eval-type-2-arg)
  (declare (ignore item1))
  (declare (ignore item2))
  
  (make-evaluation-truth-value truth))





;;; The `NUPEC-SYNCHRONIZATION-OCCURS stack-evaluator' is an event proposition
;;; to initiate activity for NUPEC synchronization.  Note that this evaluator is
;;; only available in the inference engine of the NUPEC release.

(def-funcalled-evaluator nupec-synchronization-occurs nil
  (70 (inference) nil boolean funcall-eval-type-0-arg)
  (make-evaluation-truth-value truth))






;;;; Item Predicate Evaluators




;;; The `IS-OF-CLASS stack evaluator' and `IS-NOT-OF-CLASS stack evaluator' test
;;; if an item is an instance of a given class or a subclass of that class.  It
;;; also can accept datum types and test arguments against that type.  The
;;; evaluator returns truth or falsity.  This evaluator is available in the
;;; inference engine, procedures, and the simulator.

;; A FUNCTIONALITY CHANGE!!
;; 1. If either item is a temporary-constant:
;;    PROC-EVAL, EVAL - returned FALSE.
;;    SIMULATOR - returned nil (which is false to the simulator).
;;    NEW-EVAL - also accepts datum values and tests them against the given type
;;    or class
;; 2. This evaluator was not documented in the user manual.

;;; The special form converter is entirely so that we can register a free
;;; reference to the quoted class.

(def-special-form-converter is-of-class (expression)
  (let* ((operator (car expression))
	 (stack-evaluator-descriptions? (stack-evaluators operator))
	 (node (make-stack-node operator stack-evaluator-descriptions?))
	 (class-expr (third expression)))
    (when (and (consp class-expr)
               (eq (car class-expr) 'quote)
               (symbolp (second class-expr))
               (not (type-specification-for-user-or-datum-type
                      (second class-expr))))
      (record-free-reference 'class (second class-expr)))
    (setf (stack-node-argument-nodes node)
	  (make-stack-argument-nodes
	    operator (cdr expression)
	    stack-evaluator-descriptions?))
    node))

(def-stack-error invalid-type-or-class (item-or-datum-to-test type-or-class top-of-stack)
  "In the expression ~NA IS A ~s, ~s is not a class name or type."
  item-or-datum-to-test type-or-class type-or-class)

(def-funcalled-evaluator is-of-class (item-or-datum-to-test type-or-class)
    (71 all (item-or-datum symbol) boolean
	funcall-eval-type-2-arg
	nil pprint-is-of-class-evaluator)
  (if type-or-class
      (let ((type-specification-of-user-type?
	      (type-specification-for-user-or-datum-type
		(evaluation-symbol-symbol type-or-class)))
	    (result falsity))
	(if type-specification-of-user-type?
	    ;; Note that the following test takes an evaluation-value, not a raw
	    ;; value.
	    (when (type-specification-type-p
		    item-or-datum-to-test type-specification-of-user-type?)
	      (setq result truth))
	    (let* ((class-description?
		     (classp (evaluation-symbol-symbol type-or-class)))
		   (item-class-p?
		     (and class-description?
			  (class-is-subclass-of-item? class-description?))))
	      (cond ((not item-class-p?)
		     (invalid-type-or-class item-or-datum-to-test type-or-class
					    cached-top-of-stack))
		    ((and (framep item-or-datum-to-test)
			  (frame-of-class-description-p
			    item-or-datum-to-test
			    class-description?))
		     (setq result truth)))
	      ;; else the item or value is not correct.
	      ))
	(reclaim-if-evaluation-value item-or-datum-to-test)
	(reclaim-evaluation-symbol type-or-class)
	(make-evaluation-truth-value result))
  (make-evaluation-truth-value falsity)))

;;; The `IS-ACTIVE stack evaluator' and `IS-NOT-ACTIVE stack evaluator' test if
;;; an item is active.  The evaluators returns truth or falsity.  These
;;; evaluators are only only available in the inference engine and procedures.

(def-funcalled-evaluator is-active (kb-workspace)
			 (72 (inference procedure)
			     ((class item)) boolean
			     funcall-eval-type-1-arg
			     nil pprint-is-active-evaluator)
  (if (active-p kb-workspace)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))



;;; The `HAS-A-NAME stack-evaluator' returns truth if the item has a name and
;;; falsity if it does not.  The evaluator accepts one designation argument.
;;; This evaluator is available in the inference engine and procedures.

;; FUNCTIONALITY CHANGE: This evaluator was not documented in the user manual.

(def-funcalled-evaluator has-a-name (item)
			 (73 (inference procedure)
			     ((class item)) boolean
			     funcall-eval-type-1-arg
			     nil pprint-has-a-name-evaluator)
  (if (name-or-names-for-frame item)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))






;;;; Connection Info Evaluators




;;; The following evaluators retrieve internal (non-attribute) information about
;;; connections.  This information can also be accessed manually by doing a
;;; describe on the connection.

(def-funcalled-evaluator connection-portname (block connection)
			 (74 all ((class item) (class connection)) symbol
			     funcall-eval-type-2-arg
			     nil pprint-functional-evaluator)
  (check-args-for-connection-evaluator
    block connection "CONNECTION-PORTNAME" cached-top-of-stack)
  (let ((portname? (get-port-name-given-block-and-connection
		     block (connection-for-this-connection-frame connection))))
    (make-evaluation-symbol
      (if portname?
	  portname?
	  'none))))

; Check with Chris whether 'none is the correct symbol to use here!

(setf (argument-range 'connection-portname) 2)


(def-funcalled-evaluator connection-side (block connection)
			 (75 all ((class item) (class connection)) symbol
			     funcall-eval-type-2-arg
			     nil pprint-functional-evaluator)
  (check-args-for-connection-evaluator
    block connection "CONNECTION-SIDE" cached-top-of-stack)
  (make-evaluation-symbol
    (get-side-given-end-position
      (get-position-at-this-end-of-connection 
	(connection-for-this-connection-frame connection) block))))

(setf (argument-range 'connection-side) 2)


(def-funcalled-evaluator connection-position (block connection)
			 (76 all ((class item) (class connection)) integer
			     funcall-eval-type-2-arg
			     nil pprint-functional-evaluator)
  (check-args-for-connection-evaluator
    block connection "CONNECTION-POSITION" cached-top-of-stack)
  (make-evaluation-quantity
    (get-position-on-side-given-end-position
      (get-position-at-this-end-of-connection 
	(connection-for-this-connection-frame connection) block))))

(setf (argument-range 'connection-position) 2)


(def-funcalled-evaluator connection-direction (block connection)
			 (77 all ((class item) (class connection)) symbol
			     funcall-eval-type-2-arg
			     nil pprint-functional-evaluator)
  (check-args-for-connection-evaluator
    block connection "CONNECTION-DIRECTION" cached-top-of-stack)
  (make-evaluation-symbol
    (or (get-direction-of-connection 
	  (connection-for-this-connection-frame connection) block)
	'none)))

(setf (argument-range 'connection-direction) 2)


(def-funcalled-evaluator connection-style (connection)
			 (78 all ((class connection)) symbol
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (make-evaluation-symbol
    (get-style-of-connection
      (connection-for-this-connection-frame connection))))

(setf (argument-range 'connection-style) 1)



(defun check-args-for-connection-evaluator 
       (item connection evaluator-name-string top-of-stack)
  (cond 
    ((not (frame-of-class-p item 'block))
     (stack-error
       top-of-stack
       "The first argument to ~a was an item which was not a block ~
        so it has no connections.  The argument was ~NF."
       evaluator-name-string item))
    ((not (connection-connected-to-block-p 
	    (connection-for-this-connection-frame connection) item))
     (stack-error
       top-of-stack
       "The connection argument to ~a was a connection which is not ~
        connected to the block. The connection was ~NF."
       evaluator-name-string connection))))

;; Currently (3.0) every subclass of item is also a block so the first check
;; isn't really necessary.



;;; The following evaluators are predicates for determining whether blocks are
;;; connected in certain ways.  Items-are-connected takes two blocks as args and
;;; returns true if the blocks are connected (as determined by
;;; search-for-directly-connected-entities, the standard function for searching
;;; connections).  Items-are-connected-with-direction is like
;;; items-are-connected but takes an additional arg, a symbol, which can be
;;; either 'input or 'output.  It returns true if the blocks are connected
;;; according to the direction, with the first block being the source and the
;;; second being the target, (again, as determined by the standard function
;;; search-for-directly-connected-entities).  Items-are-connected-at-ports is
;;; like items-are-connected but takes two additional args (symbols) which
;;; indicate required ports for the source and target blocks.  If a port is
;;; 'any, then the filter is not applied for the corresponding block (any port
;;; will satisfy the predicate).  As with the other predicates,
;;; search-for-directly-connected-entities is used to test for true or false.

;;; IMPORTANT: please notice that the system function `items-are-connected' is not
;;; symmetrical when swaping the two arguments, if one of them are connections, or
;;; connection-posts (CPs), or junctions. This is desirable and useful sometimes.
;;;
;;; 1. The relationship between `connected to' and `items-are-connected' is:
;;;
;;;   for each item B connected to A => items-are-connected (A, B) is always true.
;;;
;;; 2. We have following behaviour table on different type of arguments:
;;;
;;; class of block1 | class of block2 | items-are-connected (block1, block2)
;;; ----------------+-----------------+--------------------------------------------------
;;;           block |           block | TRUE iff no other blocks between them
;;;      connection |           block | TRUE iff no other blocks between them
;;; connection post |           block | TRUE iff no other blocks between them
;;;        junction |           block | TRUE iff no other blocks between them
;;;      connection |      connection | TRUE if there's only one junction/CP between them
;;;           block |      connection | TRUE on directly attached connections to block1
;;;        junction |      connection | TRUE on directly attached connections to block1
;;; connection post |      connection | TRUE on directly attached connections to block1
;;;      connection | connection post | TRUE on directly attached CPs to block1
;;; connection post | connection post | TRUE iff no other block/CPs between them
;;;           block | connection post | TRUE iff no other block/CPs between them
;;;        junction | connection post | TRUE iff no other block/CPs between them
;;;           block |        junction | TRUE iff no other block/junctions between them
;;; connection post |        junction | TRUE iff no other block/junctions between them
;;;      connection |        junction | TRUE iff no other block/junctions between them
;;;        junction |        junction | TRUE iff no other block/junctions between them
;;; -------------------------------------------------------------------------------------
;;;
;;; NOTE: CPs are special: connection test could go across CPs with the same name, and
;;;       multiple CPs sharing the same name is considered as the same, even for those who
;;;       have multiple names: CP [XX, YY] = CP [YY, ZZ].

(def-funcalled-evaluator items-are-connected (block1 block2)
			 (134 all ((class item) (class item)) boolean
			     funcall-eval-type-2-arg
			     nil pprint-functional-evaluator)
  (cond 
    ((not (frame-of-class-p block1 'block))
     (stack-error
       cached-top-of-stack
       "The first argument to items-are-connected was an item which was not a block ~
        so it has no connections.  The argument was ~NF."
       block1))
    ((not (frame-of-class-p block2 'block))
     (stack-error
       cached-top-of-stack
       "The second argument to items-are-connected was an item which was not a block ~
        so it has no connections.  The argument was ~NF."
       block2)))

  (let* ((class-of-block2
	   (class-name-of-class-description
	     (class-description-slot block2)))
	 (connected-items?
	   (search-for-directly-connected-entities
	     block1 class-of-block2 nil nil nil nil nil nil))
	 (result
	   (loop for connected-item in connected-items? do
	     (when (eq connected-item block2)
	       (return (make-evaluation-truth-value truth)))
		 finally
		   (return (make-evaluation-truth-value falsity)))))
    (reclaim-eval-tree connected-items?)
    result))

(setf (argument-range 'items-are-connected) 2)

(def-funcalled-evaluator items-are-connected-with-direction (block1 block2 direction)
			 (135 all ((class item) (class item) symbol) boolean
			     funcall-eval-type-3-arg
			     nil pprint-functional-evaluator)
  (cond 
    ((not (frame-of-class-p block1 'block))
     (stack-error
       cached-top-of-stack
       "The first argument to items-are-connected-with-direction was an item which was not a block ~
        so it has no connections.  The argument was ~NF."
       block1))
    ((not (frame-of-class-p block2 'block))
     (stack-error
       cached-top-of-stack
       "The second argument to items-are-connected-with-direction was an item which was not a block ~
        so it has no connections.  The argument was ~NF."
       block2))
    ((not (or (eq direction 'input)
	      (eq direction 'output)))
     (stack-error
       cached-top-of-stack
       "The third argument to items-are-connected-with-direction was ~NF.  It has to be either input or output."
       direction)))

  (let* ((class-of-block2
	   (class-name-of-class-description
	     (class-description-slot block2)))
	 (connected-items?
	   (search-for-directly-connected-entities
	     block1 class-of-block2 nil direction direction nil nil nil))
	 (result
	   (loop for connected-item in connected-items? do
	     (when (eq connected-item block2)
	       (return (make-evaluation-truth-value truth)))
		 finally
		   (return (make-evaluation-truth-value falsity)))))
    (reclaim-eval-tree connected-items?)
    result))

(setf (argument-range 'items-are-connected-with-direction) 3)



(def-funcalled-evaluator items-are-connected-at-ports (block1 block2 source-port target-port)
			 (136 all ((class item) (class item) symbol symbol) boolean
			     funcall-eval-type-4-arg
			     nil pprint-functional-evaluator)
  (cond 
    ((not (frame-of-class-p block1 'block))
     (stack-error
       cached-top-of-stack
       "The first argument to items-are-connected-at-ports was an item which was not a block ~
        so it has no connections.  The argument was ~NF."
       block1))
    ((not (frame-of-class-p block2 'block))
     (stack-error
       cached-top-of-stack
       "The second argument to items-are-connected-at-ports was an item which was not a block ~
        so it has no connections.  The argument was ~NF."
       block2)))

  (let* ((class-of-block2
	   (class-name-of-class-description
	     (class-description-slot block2)))
	 (connected-items?
	   (cond
	     ((and (eq source-port 'any)
		   (eq target-port 'any))
	      ;; Degenerate case, it would be better to just use items-are-connected instead 
	      (search-for-directly-connected-entities
		block1 class-of-block2 nil nil nil nil nil nil))
	     ((eq target-port 'any)
	      ;; Source-port is specified, target-port is not.
	      (search-for-directly-connected-entities
		block1 class-of-block2 source-port nil nil nil nil nil))
	     ((eq source-port 'any)
	      ;; Target-port is specified, source-port is not.
	      (search-for-directly-connected-entities
		block1 class-of-block2 nil nil nil 'port-names nil nil))
	     (t
	      ;; Both source-port and target-port are specified.
	      (search-for-directly-connected-entities
		block1 class-of-block2 source-port nil nil 'port-names nil nil)))))

    (cond
      ((eq target-port 'any)  ; if target-port is not specified
       (loop for connected-item in connected-items?
	     when (eq connected-item block2)
	     do
		 (reclaim-eval-tree connected-items?)
		 (return (make-evaluation-truth-value truth))
	     finally
	       (reclaim-eval-tree connected-items?)
	       (return (make-evaluation-truth-value falsity))))
      (t  ; if target-port is specified, need to check portnames in connected-items?
       (loop for connected-item-entry in connected-items?
	     when (and (eq (first connected-item-entry) block2)
		       (memq target-port (second connected-item-entry))) do
		 (reclaim-eval-tree connected-items?)
		 (return (make-evaluation-truth-value truth))
	     finally
	       (reclaim-eval-tree connected-items?)
	       (return (make-evaluation-truth-value falsity)))))))

(setf (argument-range 'items-are-connected-at-ports) 4)





;;;; Query Evaluators




(declare-forward-reference do-query-evaluation-for-rule-restriction function) ; QUERIES
(declare-forward-reference do-query-evaluation-for-with-status      function) ; QUERIES
(declare-forward-reference do-query-evaluation-for-containing       function) ; QUERIES

;;; These evaluators are used only in inpect commands, codes in range [80..88]
;;; 
;;; Here is a summary of what is defined in this section:
;;;  Code      - Name -                  -  Args -         	- Result -
;;;  #80   which-has-the-focal-object <rule> <symbol>    	<truth-value>
;;;  #81   which-has-the-focal-class  <rule> <symbol>    	<truth-value>
;;;  #82   in-the-catagory            <rule> <symbol>    	<truth-value>
;;;  #83   with-status                <item> <symbol>    	<truth-value>
;;;  #84   with-notes                 <item>             	<truth-value>
;;;  #85   containing                 <item> <symbol-or-string> <truth-value>
;;;  #86   containing-word            <item> <symbol-or-string> <truth-value>
;;;  #87   g2-inspect-internal-name-for-debugging-p
;;;                                   <item> <symbol-or-string> <truth-value>
;;;  #88   assigned-to-module         <item> <symbol>     	<truth-value>
;;;  #97  containing-symbol          <item> <symbol-or-string> <truth-value>
;;;        [note: mysteriously omitted from 3.0; now added in 4.0. (MHD 8/1/94)
;;;         note: #97 was the next available code at this time.]
;;;
;;; These are all funcalled-evaluators.

;; 8/26/91 - ben
;; It is unclear how I decided to on to say "(inference procedures)" in
;; the code below. 

;; The 2.0 Inspect evaluator, found-on-workspace, is not in 3.0.  cpm, 8/27/91


(def-funcalled-evaluator which-has-the-focal-object (rule symbol)
			 (80 (inference procedures)
			     ((class rule) symbol) boolean
			     funcall-eval-type-2-arg)
  (let ((result
	  (if (do-query-evaluation-for-rule-restriction
		rule (evaluation-symbol-symbol symbol) 'focal-objects)
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-symbol symbol)
    result))

(def-funcalled-evaluator which-has-the-focal-class (rule symbol)
			 (81 (inference procedures)
			     ((class rule) symbol) boolean
			     funcall-eval-type-2-arg)
  (let ((result
	  (if (do-query-evaluation-for-rule-restriction
		rule (evaluation-symbol-symbol symbol) 'focal-classes)
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-symbol symbol)
    result))

(def-funcalled-evaluator in-the-category (rule symbol)
			 (82 (inference)
			     ((class rule) symbol) boolean
			     funcall-eval-type-2-arg)
  (let ((result
	  (if (do-query-evaluation-for-rule-restriction
		rule (evaluation-symbol-symbol symbol) 'rule-categories)
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-symbol symbol)
    result))

(def-funcalled-evaluator with-status (item status)
			 (83 (inference procedures)
			     ((class item) symbol) boolean
			     funcall-eval-type-2-arg)
  (let ((result
	  (if (do-query-evaluation-for-with-status
		item (evaluation-symbol-symbol status))
	      (make-evaluation-truth-value truth)
	      (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-symbol status)
    result))

(def-funcalled-evaluator with-notes (item)
			 (84 (inference procedures)
			     ((class item)) boolean
			     funcall-eval-type-1-arg)
  (if (frame-status-and-notes item)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))



;;; The `CONTAINING stack-evaluator' is used to check whether or not the texts
;;; of user visible slot values contain the passed string or symbol.  The
;;; `CONTAINING-WORD stack evaluator' does the same, except that it observes
;;; word boundaries during the search.  The `CONTAINING-SYMBOL stack evaluator'
;;; does the same, except that it observes symbol boundaries.

(def-funcalled-evaluator containing (item what-to-look-for)
			 (85 (inference procedures)
			     ((class item) (or symbol text)) boolean
			     funcall-eval-type-2-arg)
  (let* ((text-p? (evaluation-text-p what-to-look-for))
	 (result
	   (if (do-query-evaluation-for-containing
		 item
		 (if text-p?
		     (evaluation-text-value what-to-look-for)
		     (evaluation-symbol-symbol what-to-look-for))
		 nil)
	       (make-evaluation-truth-value truth)
	       (make-evaluation-truth-value falsity))))
    (if text-p?
	(reclaim-evaluation-text what-to-look-for)
	(reclaim-evaluation-symbol what-to-look-for))
    result))

(def-funcalled-evaluator containing-word (item what-to-look-for)
			 (86 (inference procedures)
			     ((class item) (or symbol text)) boolean
			     funcall-eval-type-2-arg)
  (let* ((text-p? (evaluation-text-p what-to-look-for))
	 (result
	   (if (do-query-evaluation-for-containing
		 item
		 (if text-p?
		     (evaluation-text-value what-to-look-for)
		     (evaluation-symbol-symbol what-to-look-for))
		 t)
	       (make-evaluation-truth-value truth)
	       (make-evaluation-truth-value falsity))))
    (if text-p?
	(reclaim-evaluation-text what-to-look-for)
	(reclaim-evaluation-symbol what-to-look-for))
    result))

(def-funcalled-evaluator containing-symbol (item what-to-look-for)
			 (97 (inference procedures)
			      ((class item) (or symbol text)) boolean
			      funcall-eval-type-2-arg)
  (let* ((text-p? (evaluation-text-p what-to-look-for))
	 (result
	   (if (do-query-evaluation-for-containing
		 item
		 (if text-p?
		     (evaluation-text-value what-to-look-for)
		     (evaluation-symbol-symbol what-to-look-for))
		 'symbol)
	       (make-evaluation-truth-value truth)
	       (make-evaluation-truth-value falsity))))
    (if text-p?
	(reclaim-evaluation-text what-to-look-for)
	(reclaim-evaluation-symbol what-to-look-for))
    result))

(def-funcalled-evaluator g2-inspect-internal-name-for-debugging-p (item symbol-or-string)
    (87 (inference procedures)
	((class item) (or symbol text)) boolean
	funcall-eval-type-2-arg)
  (let
    ((result
      (if (and (block-p item)
	       (debugging-name-for-block-p 
		 item
		 (if (symbolp symbol-or-string)
		     (symbol-name-text-string (evaluation-symbol-symbol symbol-or-string))
		     (evaluation-text-value symbol-or-string))))
	  (make-evaluation-truth-value truth)
	  (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-value symbol-or-string)
    result))




;;; The funcalled evaluator `assigned-to-module' returns a boolean result based
;;; on whether the supplied arg item is assigned to the supplied module or, if
;;; search-hierarchy-p is true, assigned to the supplied module's "hierarchy",
;;; i.e., either to module to one of module's required modules.
;;;
;;; Module should be the name of a module, but nothing special happens if it's
;;; some random symbol: it just returns false.
;;;
;;; Item may be any instance of the class ITEM.

(def-funcalled-evaluator assigned-to-module (item module search-hierarchy-p)
    (88 (inference procedures) ((class item) symbol boolean)
	boolean funcall-eval-type-3-arg)
  (let ((result
	 (if (if (evaluation-truth-value-true-p search-hierarchy-p)
		 (within-module-hierarchy-p item module)
		 (within-module-p item module))
	     (make-evaluation-truth-value truth)
	     (make-evaluation-truth-value falsity))))
    (reclaim-evaluation-truth-value search-hierarchy-p)
    (reclaim-evaluation-symbol module)
    result))



;;; The funcalled evaluator `with-changes-logged' returns a boolean result based
;;; on whether the supplied arg item has changes logged with restrictions matching
;;; those specified.
;;;
;;; Item may be any instance of the class ITEM.
;;;
;;; Restrictions should be a (evaluation) sequence of zero or more of these
;;; sequences:
;;;
;;;     (before <timestamp>)
;;;     (after <timestamp>)
;;;     (by <user-name>)

(def-funcalled-evaluator with-changes-logged-2
    (item before after author)
    (149
      (inference procedures)
      ((class item)
       (or integer truth-value)
       (or integer truth-value)
       (or symbol truth-value))
      boolean funcall-eval-type-4-arg)
  (make-evaluation-boolean-value
    (item-has-changes-logged-p item before after author)))







;;;; Obsolete Evaluators




;;; The `CURRENT-VALUE evaluator' is an obsolete version of value-of which
;;; is used to force an evaluation for datum of an expression, with variables
;;; attempting to obtain new values if they do not have a current value.  The
;;; evaluator accepts one designation argument.  This evaluator is only
;;; available in the inference engine.

;; Need a special form!!

;; Consider removing this obsolete evaluator!!



;;; The `ICON-COLOR-OF evaluator' is becoming obsolete.  Icon color becomes a
;;; role in 2.0.  The color of an icon, such as the icon for an object or class
;;; definition, is returned.  This evaluator is available in the inference
;;; engine and procedures.

;; Is it obsolete yet??  cpm, 5/21/91

;(def-new-evaluator icon-color-of (all ((class item)) symbol)
;  ;; test for temporary-constants??
;  (icon-color (stack-arg 0)))



;;; The `HAS-CURRENT-VALUE evaluator' is an obsolete version of the HAS-A-VALUE
;;; evaluator.  It checks if an expression or variable has a value and attempts
;;; to compute the value for a variable that does not currently have a value.
;;; (There is also a has-a-current-value evaluator which will check if a
;;; variable or expression has a value without updating any variable values.)
;;; The has-current-value evaluator always gives a level 3 warning which informs
;;; the user that this evaluator is obsolete and should be recompiled.  It
;;; accepts an expression argument and returns truth or falsity.  The value
;;; truth is returned if there is a current value or a new value was computed as
;;; a result of this evaluation.  Otherwise, falsity is returned.  This
;;; evaluator is only available in the inference engine.

;; If the obsolete has-current-value evaluator is not removed, we need to
;; implement it as a special form!!



;; (THE role domain) as an expression for datum-evaluation will evaluate-designation
;; the domain, and, if successful, should find the unique role value. This should
;; be datum-evaluated.
;;
;; The THE evaluator is now obsolete.



;; The def-evaluator for LET was moved to the file RULES.
;;
;;; (let ( {(binding expression)} ) expression)
;;
;; The LET evaluator is obsolete and should be removed from RULES when the
;; switch is made to stack execution.  This evaluator will be replaced by
;; bindings made during compilation.



;; The `IF evaluator' is an old form of if-expression that is only in the
;; simulator.  Does this need to be a new evaluator??  AGH says, Nope.
;; Simulation formulas have not saved their parses in files, and so parses for
;; simulation formulas are always produced from the current parser, which uses
;; if-expression, not if.  -jra & cpm 5/1/91






;;;; Miscellaneous Instructions Supporting Evaluators




;;; The following instruction is used to convert a value of the type NO-ITEM
;;; (i.e.  NIL) into an unknown, and leave all other kinds of items or
;;; evaluation values alone.

(def-funcalled-instruction coerce-no-item-to-unknown (68 all 1 1 nil)
  (when (null (stack-arg 0))
    (setq stack-expiration nil))
  nil)

;;;






;;;; NEW-EVAL Error Messages




;;; The following new-evaluator error functions print a warning to the user and
;;; does a throw to the error handling code.  These functions are generalized for
;;; for different evaluators to use.

;;; Note that only evaluation-values are reclaimed.  Non-evaluation values, such
;;; as text, are not reclaimed.  Funcalled evaluators, for example, are passed
;;; non-evaluation values (i.e., the values of evaluation-values) and must not
;;; reclaim them within the evaluator or within a call to an error function.






;;;; NEW-EVAL Argument Arithmetic Errors



;; The following replaces evaluator-index-float-error.

#+unused
(defun non-integer-arg-eval-error
       (non-integer-stack-arg evaluator-name top-of-stack)
  ;; The argument was not an integer.
  (write-stack-error
    top-of-stack
    (tformat "The ~a operator received the non-integer argument "
	     evaluator-name)
    (if (evaluation-value-p non-integer-stack-arg)
	(write-evaluation-value non-integer-stack-arg)
	(twrite non-integer-stack-arg))
    (twrite-string ".")))


;;; The eval-error function `start-index-greater-than-end-index-eval-error' is useful when
;;; validating the start and end indices in text operations.

;; This replaces the evaluator-indices-range-mismatch error function.


;;; The eval-error function `index-of-g2-text-too-large-eval-error' warns that
;;; the index for the given g2-text was out of bounds.  The index is either less
;;; than the starting index (i.e., 0), greater than the maximum index (i.e., the
;;; length), or referencing an empty g2-text (i.e., "").  This function reclaims
;;; any stack arguments.

;; This replaces the evaluator-out-of-g2-text-bounds error function.

(defun index-of-g2-text-too-large-eval-error
       (index g2-text evaluator-name top-of-stack)
  ;; g2-text[i], where i is out of bounds.
  (if (string-equalw g2-text #w"")
      (write-stack-error
	top-of-stack
	(twrite-string "The index ")
	(if (evaluation-value-p index)
	    (write-evaluation-value index)
	    (twrite index))
	(tformat " given to the operator ~a is out of bounds of ~
                  the empty text."
		 evaluator-name))
      (write-stack-error
	top-of-stack
	(twrite-string "The index ")
	(if (evaluation-value-p index)
	    (write-evaluation-value index)
	    (twrite index))
	(tformat " given to the operator ~a is out of bounds of the ~
                   text \"~a\", which has length ~d."
		 evaluator-name
		 (if (evaluation-value-p g2-text)
		     (evaluation-text-value g2-text)
		     g2-text)
		 (g2-text-length g2-text)))))


(defun merged-string-would-be-too-long-eval-error
    (source-text-value destination-text-value evaluator-name top-of-stack)
  (let ((small-source-text
	  (text-string-substring source-text-value 0 20))
	(small-destination-text
	  (text-string-substring destination-text-value 0 20)))
    (write-stack-error
	top-of-stack
      (tformat
	"The ~a operator cannot return a text containing ~
         more than ~a characters.  The text arguments began with ~
         \"~a...\" and \"~a...\"."
	evaluator-name
	maximum-length-for-user-text-strings
	small-source-text small-destination-text)
      (reclaim-text-string small-source-text)
      (reclaim-text-string small-destination-text))))








;;;; NEW-EVAL Computation and Result Errors
;;; `NO-ITEM-OF-CLASS-EVAL-ERROR' is used for example when locating an instance
;;; of a class near another item.




;;; `ATTRIBUTE-ITEM-EVAL-ERROR' is used when one item is expected to be an
;;; attribute of another item.




;;; `MOVING-ITEM-OF-CLASS-EVAL-ERROR' is used for example when locating an
;;; instance of a class near another item.

#+unused
(defun moving-item-of-class-eval-error (class top-of-stack)
  (stack-error
    top-of-stack "Could not locate a non-moving item of type ~a." class))




;;;; BIT-WISE EVALUATORS

;;; are split into in line evaluators and funcalled evaluators. This was done to
;;; conserve inline space


(def-in-line-evaluator bitwise-and
    (52 all (integer integer) integer nil pprint-functional-evaluator)
  (setq fixnum-register-1 (stack-arg 0))
  (setq fixnum-register-2 (stack-arg 1))
  
  (make-evaluation-integer (logandf fixnum-register-1 fixnum-register-2) ))

(setf (argument-range 'bitwise-and) 2)

(def-in-line-evaluator bitwise-or
    (53 all (integer integer) integer nil pprint-functional-evaluator)
  (setq fixnum-register-1 (stack-arg 0))
  (setq fixnum-register-2 (stack-arg 1))
  
  (make-evaluation-integer (logiorf fixnum-register-1 fixnum-register-2)))

(setf (argument-range 'bitwise-or) 2)

(def-funcalled-evaluator bitwise-not (value1)
    (89 all
	(integer) integer
	funcall-eval-type-1-arg)
  (let ((quantity-value1 (evaluation-integer-value value1)))
    (declare (type fixnum quantity-value1))
    (reclaim-evaluation-integer value1)
    (make-evaluation-integer (lognotf quantity-value1))))

(setf (argument-range 'bitwise-not) 1)

(def-funcalled-evaluator bitwise-xor (value1 value2)
    (90 all
	(integer integer) integer
	funcall-eval-type-2-arg)
  (let ((quantity-value1 (evaluation-integer-value value1))
	(quantity-value2 (evaluation-integer-value value2)))
    (declare (type fixnum quantity-value1 quantity-value2))
    (reclaim-evaluation-integer value1)
    (reclaim-evaluation-integer value2)
    (make-evaluation-integer (logxorf quantity-value1 quantity-value2))))

(setf (argument-range 'bitwise-xor) 2)

(def-funcalled-evaluator bitwise-right-shift (value shift-count)
    (91 all
	(integer integer) integer
	funcall-eval-type-2-arg)
  (let ((quantity-value (evaluation-integer-value value))
	(quantity-shift-count (-f (evaluation-integer-value shift-count))))
    (declare (type fixnum quantity-value quantity-shift-count))
    (reclaim-evaluation-integer value)
    (reclaim-evaluation-integer shift-count)
    (make-evaluation-integer
      #-chestnut-trans
      (ashf quantity-value quantity-shift-count)
      #+chestnut-trans
      (if (<=f 0 quantity-shift-count)
	  (ashf quantity-value (the (integer 0 *) quantity-shift-count))
	  (ashf quantity-value (the (integer * 0) quantity-shift-count))))))

(setf (argument-range 'bitwise-right-shift) 2)

(def-funcalled-evaluator bitwise-left-shift (value shift-count)
    (92 all
	(integer integer) integer
	funcall-eval-type-2-arg)
  (let ((quantity-value (evaluation-integer-value value))
	(quantity-shift-count (evaluation-integer-value shift-count)))
    (declare (type fixnum quantity-value quantity-shift-count))
    (reclaim-evaluation-integer value)
    (reclaim-evaluation-integer shift-count)
    (make-evaluation-integer
      #-chestnut-trans
      (ashf quantity-value quantity-shift-count)
      #+chestnut-trans
      (if (<=f 0 quantity-shift-count)
	  (ashf quantity-value (the (integer 0 *) quantity-shift-count))
	  (ashf quantity-value (the (integer * 0) quantity-shift-count))))))

(setf (argument-range 'bitwise-left-shift) 2)

(def-funcalled-evaluator bitwise-test (value location)
    (93 all
	(integer integer) boolean
	funcall-eval-type-2-arg)
  (let ((quantity-value (evaluation-integer-value value))
	(quantity-location (evaluation-integer-value location)))
    (declare (type fixnum quantity-value quantity-location))
    (when (or (minuspf quantity-location)
	      (>f quantity-location 29))
      (stack-error
	cached-top-of-stack
	"Desired test index ~a is outside the range 0-29"
	quantity-location))
    (reclaim-evaluation-integer value)
    (reclaim-evaluation-integer location)
    (if (=f quantity-location 29)
	(if (minuspf quantity-value) 
	    evaluation-true-value 
	    evaluation-false-value)
	(if #-chestnut-trans
	    (logbitpf (the (integer 0 28) quantity-location)
		      quantity-value)
	    #+chestnut-trans
	    (logtest (the fixnum (ash 1 (the (integer 0 28)
					     quantity-location)))
		     quantity-value)
	    evaluation-true-value
	    evaluation-false-value))))

(setf (argument-range 'bitwise-test) 2)


(def-funcalled-evaluator bitwise-set (value location)
    (94 all
	(integer integer) integer
	funcall-eval-type-2-arg)
  (let* ((quantity-value (evaluation-integer-value value))
	 (quantity-location (evaluation-integer-value location))
	 (set-value 1))
    (declare (type fixnum set-value quantity-value quantity-location))
    ;; although in some models 29 would be OK Common lisp really requires that
    ;; the result not go negative
    (when (or (minuspf quantity-location)
	      (>f quantity-location 28))
      (stack-error
	cached-top-of-stack
	"Desired set index ~a is outside the range 0-28"
	quantity-location))
    (setq set-value
	  (ashf set-value (the (integer 0 28) quantity-location)))
    (reclaim-evaluation-integer value)
    (reclaim-evaluation-integer location)
    (make-evaluation-integer (logiorf quantity-value set-value))))

(setf (argument-range 'bitwise-set) 2)


;;; The `great-circle-distance stack-evaluator' returns the
;;; great-circle-distance of its first four arguments given in
;;; degrees, multiplied by the spherical radius which is its fifth
;;; argument.  This is the great-circle-distance between the first
;;; point at (latitude-1, longitude-1) and the second point at 
;;; (latitude-2, longitude-2) .  The five arguments must be coerced
;;; to gensym-floats, if necessary, before this evaluator is called.
;;; There are no integer and quantity versions of this evaluator.
;;; This evaluator is available in the inference engine and procedures.

;;; Some notes:

;;; The great-circle-distance (gcd) is the distance between two
;;; points on a sphere when traveling on the surface of the sphere.
;;; The first point is at (latitude-1, longitude-1) and the second
;;; point is at (latitude-2, longitude-2).

;;; From:  http://williams.best.vwh.net/avform.htm#Dist 

;;; gcd = 2*radius*asin(sqrt(sin((lat1-lat2)/2)^2 +
;;;                     cos(lat1)*cos(lat2)*sin((long1-long2)/2)^2))

;;; Latitudes go from 0 to 90 degrees N (positive) and from 
;;; 0 to 90 degrees S (negative).

;;; Longitudes go from 0 to 180 degrees E (positive) and from 
;;; 0 to 180 degrees W (negative).  0 degrees is in Greenwich,
;;; England (prime meridian).  180 degrees is at the International
;;; Date Line.  (The convention E negative and W positive is also
;;; fine as long as one is consistent.)

;;; To convert from degrees to radians you multiply by pi/180.0 .
;;; pi = 3.141592653589793 (approx.).

;;; 180 degrees = pi radians;
;;; 90 degrees = pi/2 radians = 1.5707963267948966 (approx.)

;;; The units of the supplied radius determines the units of the
;;; result.  For the Earth, equatorial radius = 6378.137 kilometers,
;;; polar radius = 6356.752 km, and FAI radius = 6371.0 km.
;;; Kim Wilkins uses an earth radius = 6371009.0 (meters).
;;; radius = 1 implies that the result is in radians.

;;; Example calculation:

;;; The distance in radians between LAX at (33.95, -118.4) degrees 
;;; and JFK at (40.633333, -73.783333) degrees = 0.623585 radians.

;;; great-circle-distance(33.95, -118.4, 40.633333, -73.783333, 1)
;;;  = 0.623585 .

;;; Using the FAI radius of 6371.0 km:
;;; great-circle-distance(33.95, -118.4, 40.633333, -73.783333, 6371.0)
;;;  = 3972.858 (km).

;;;  - jpg 3/3/05

;;; GREAT-CIRCLE-DISTANCE (lat1, long1, lat2, long2, radius)

(def-funcalled-evaluator great-circle-distance
    (lat1 long1 lat2 long2 radius)
    (120 (inference procedure)
	 (float float float float float)
	 float
	 funcall-eval-type-5-arg
	 nil pprint-functional-evaluator)

  (let ((lat1-value (evaluation-float-value lat1))
	(long1-value (evaluation-float-value long1))
	(lat2-value (evaluation-float-value lat2))
	(long2-value (evaluation-float-value long2))
	(radius-value (evaluation-float-value radius)))

    (with-temporary-gensym-float-creation great-circle-distance 

      ;; The extra 0.1 is used to avoid roundoff error problems. - jpg 3/3/05

      (unless (<e -90.1 lat1-value 90.1)
	(invalid-argument-eval-error 
	  lat1-value 'latitude 'great-circle-distance cached-top-of-stack))
      (unless (<e -90.1 lat2-value 90.1)
	(invalid-argument-eval-error 
	  lat2-value 'latitude 'great-circle-distance cached-top-of-stack))
      (unless (<e -180.1 long1-value 180.1)
	(invalid-argument-eval-error 
	  long1-value 'longitude 'great-circle-distance cached-top-of-stack))
      (unless (<e -180.1 long2-value 180.1)
	(invalid-argument-eval-error 
	  long2-value 'longitude 'great-circle-distance cached-top-of-stack))
      (when (minuspe radius-value)
	(invalid-argument-eval-error 
	  radius-value 'radius 'great-circle-distance cached-top-of-stack))

      (setq lat1-value (*e #.(/ pi 180) lat1-value))
      (setq long1-value (*e #.(/ pi 180) long1-value))
      (setq lat2-value (*e #.(/ pi 180) lat2-value))
      (setq long2-value (*e #.(/ pi 180) long2-value))

      (reclaim-evaluation-float lat1)
      (reclaim-evaluation-float long1)
      (reclaim-evaluation-float lat2)
      (reclaim-evaluation-float long2)
      (reclaim-evaluation-float radius)

      (make-evaluation-float
	(*e 2.0 radius-value
	    (asine
	      (sqrte
		(+e (let ((sin-value
			    (sine (/e (-e lat1-value lat2-value) 2.0))))
		      (*e sin-value sin-value))
		    (*e (cose lat1-value)
			(cose lat2-value)
			(let ((sin-value
				(sine (/e (-e long1-value long2-value) 2.0))))
			  (*e sin-value sin-value)))))))))))


;;; The `rgb-symbol stack-evaluator' takes as arguments the
;;; red, green, and blue values, integers between 0 and 255
;;; inclusive and returns a symbol of the form RGBrrggbb,
;;; a valid color name, where rr, gg, bb, are the 8-bit hex
;;; values for red, green, and blue.

;;; Examples:
;;; blue:  rgb-symbol(0,0,255) = RGB0000FF
;;; brown:  rgb-symbol(165,42,42) = RGBA52A2A

;;; RGB-SYMBOL (three integers)

(def-funcalled-evaluator rgb-symbol 
    (red-value green-value blue-value)
    (122 (inference procedure)
	 (integer integer integer)
	 symbol
	 funcall-eval-type-3-arg
	 nil pprint-functional-evaluator)

  (let ((red-value-value (evaluation-integer-value red-value))
	(green-value-value (evaluation-integer-value green-value))
	(blue-value-value (evaluation-integer-value blue-value))
	hex-char-list
	hex-char-1 hex-char-2)

    (unless (<=f 0 red-value-value 255)
      (invalid-argument-eval-error
	red-value-value 'color-value 'rgb-symbol cached-top-of-stack))
    (unless (<=f 0 green-value-value 255)
      (invalid-argument-eval-error
	green-value-value 'color-value 'rgb-symbol cached-top-of-stack))
    (unless (<=f 0 blue-value-value 255)
      (invalid-argument-eval-error
	blue-value-value 'color-value 'rgb-symbol cached-top-of-stack))

    (multiple-value-setq (hex-char-1 hex-char-2)
	(hex-color-values blue-value-value))

      (setq hex-char-list
	    (gensym-cons hex-char-1
			 (gensym-cons hex-char-2
				      hex-char-list)))

    (multiple-value-setq (hex-char-1 hex-char-2)
	(hex-color-values green-value-value))

      (setq hex-char-list
	    (gensym-cons hex-char-1
			 (gensym-cons hex-char-2
				      hex-char-list)))

    (multiple-value-setq (hex-char-1 hex-char-2)
	(hex-color-values red-value-value))

      (setq hex-char-list
	    (gensym-cons hex-char-1
			 (gensym-cons hex-char-2
				      hex-char-list)))   
    (let
      ((result
	(intern-text-string
	  (apply #'tformat-text-string "RGB~c~c~c~c~c~c"
		 hex-char-list))))
      (reclaim-gensym-list hex-char-list)
      result)))

(defun hex-color-values (color-value)
  (multiple-value-bind (hex-digit-1 hex-digit-2)
      (floorf color-value 16)
    (values (digit-char hex-digit-1 16) (digit-char hex-digit-2 16))))



;;;; Place References for Class Qualified Attribute Names




;;; The funcalled instruction `class-qualified-name-frame-or-place-reference' is
;;; used to evaluate the first arguments to change or conclude.  If the denoted
;;; attribute contains a frame, it is returned.  If the denoted argument holds
;;; anything but a frame, then a place reference is returned.

(defun-void pprint-cqn-frame-or-place-reference-instruction
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "fetch the ")
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-string "::")
  (write-stack-argument 3 3 stack top-of-stack)
  (twrite-string " of ")
  (write-stack-argument 1 3 stack top-of-stack))

(def-funcalled-instruction class-qualified-name-frame-or-place-reference (76 all 3 1 nil pprint-cqn-frame-or-place-reference-instruction)
  (let* ((parent-frame (stack-arg 0))
	 (class-qualifier (stack-arg 1))
	 (pretty-slot-name (stack-arg 2))
	 (frame-or-place-reference
	   (fetch-attribute-frame-or-place-reference
	     parent-frame pretty-slot-name class-qualifier top-of-stack)))
    (reclaim-evaluation-symbol class-qualifier)
    (reclaim-evaluation-symbol pretty-slot-name)
    (setf (stack-arg 0) frame-or-place-reference)
    nil))






;;;; Sequence and Structure Evaluation Values




;;; The following section implements operations for creating and manipulating
;;; evaluation-list and evaluation-structure types.  These values are subtypes of
;;; value, but with internal structure.

(def-special-form-converter sequence (expression)
  (let ((arguments
	  (loop for arg in (cdr-of-cons expression)
		collect (convert-expression-to-stack-node-tree arg)
		  using stack-cons))
	(stack-node-instruction (make-stack-node-instruction 'sequence nil)))
    (setf (stack-node-argument-nodes stack-node-instruction) arguments)
    stack-node-instruction))

(declare-optimizer-stack-instruction sequence)

(def-preferred-instruction-chooser sequence
  (declare (ignore extra-info))
  (let* ((unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (arg-required-type (maybe-add-unknown 'item-or-datum unknown-allowed?))
	 (unknown-args? nil))
    (loop for arg-cons on (stack-node-argument-nodes stack-node-instruction)
	  for arg = (choose-stack-node-instructions-and-types
		      (car-of-cons arg-cons) arg-required-type)
	  do
      (setf (car arg-cons) arg)
      (when (and unknown-allowed?
		 (not unknown-args?)
		 (type-specification-subtype-p
		   '(unknown-datum) (stack-node-value-type arg)))
	(setq unknown-args? t)))
    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-unknown '(sequence) unknown-args?))
    stack-node-instruction))

(def-stack-node-instruction-emitter sequence
  (declare (ignore extra-info))
  (loop with args = (stack-node-argument-nodes stack-node-instruction)
	for arg in args
	do
    (emit-stack-node-tree byte-code-stream arg)
	finally 
	  (call-stack-instruction-emitter funcall-instruction
	    byte-code-stream 'make-evaluation-sequence (length args) 1)))

(defun-void pprint-make-evaluation-sequence-instruction
    (description pc byte-code-body constant-vector stack top-of-stack arg-count result-count)
  (declare (ignore description pc byte-code-body constant-vector result-count))
  (twrite-string "sequence(")
  (loop for index from 1 to arg-count
	do
    (unless (=f index 1)
      (twrite-string ", "))
    (write-stack-argument index arg-count stack top-of-stack))
  (twrite-character #.%\)))

(def-funcalled-instruction make-evaluation-sequence (78 all (+ (0) 1) 1 nil
							pprint-make-evaluation-sequence-instruction)
  (let* ((element-count-arg (svref local-stack top-of-stack))
	 (elt-count (evaluation-integer-value element-count-arg))
	 (base-stack-index (-f top-of-stack elt-count))
	 (new-sequence (allocate-new-evaluation-sequence-from-simple-vector
			 local-stack base-stack-index elt-count)))
    (declare (type fixnum elt-count base-stack-index))
    (reclaim-evaluation-integer element-count-arg)
    (setf (svref local-stack base-stack-index) new-sequence)
    nil))




;;; The function `evaluated-structure' takes an arbitrary number of alternating
;;; symbol and item-or-datum arguments (up to 250K pairs), and returns a newly
;;; created evaluation structure containing the given attributes which hold their
;;; corresponding values.  It is an error if there are not an even number of
;;; arguments, or if the first of each pair is not a symbol.

(def-special-form-converter evaluated-structure (expression)
  (let ((arguments
	  (loop for arg in (cdr-of-cons expression)
		collect (convert-expression-to-stack-node-tree arg)
		  using stack-cons))
	(stack-node-instruction
	  (make-stack-node-instruction 'evaluated-structure nil)))
    (setf (stack-node-argument-nodes stack-node-instruction) arguments)
    stack-node-instruction))

(declare-optimizer-stack-instruction evaluated-structure)

(def-preferred-instruction-chooser evaluated-structure
  (declare (ignore extra-info))
  (let* ((unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (name-arg-required-type
	   (maybe-add-unknown 'symbol unknown-allowed?))
	 (value-arg-required-type
	   (maybe-add-unknown 'item-or-datum unknown-allowed?))
	 (unknown-args? nil)
	 (args (stack-node-argument-nodes stack-node-instruction)))
    (unless (=f (logandf (length args) 1) 0)
      (compiler-error
	"Evaluated-structure requires an even number of arguments, it received ~a."
	(length args))
      (setq args nil))
    (loop for arg-cons on args by #'cddr
	  for name-arg = (choose-stack-node-instructions-and-types
			   (car arg-cons) name-arg-required-type)
	  for value-arg = (choose-stack-node-instructions-and-types
			    (second arg-cons)
			    value-arg-required-type)
	  do
      (setf (car arg-cons) name-arg)
      (setf (second arg-cons) value-arg)
      (when (and unknown-allowed?
		 (not unknown-args?)
		 (or (type-specification-subtype-p
		       '(unknown-datum) (stack-node-value-type name-arg))
		     (type-specification-subtype-p
		       '(unknown-datum) (stack-node-value-type value-arg))))
	(setq unknown-args? t)))
    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-unknown '(structure) unknown-args?))
    stack-node-instruction))

(def-stack-node-instruction-emitter evaluated-structure
  (declare (ignore extra-info))
  (loop with args = (stack-node-argument-nodes stack-node-instruction)
	for arg in args
	do
    (emit-stack-node-tree byte-code-stream arg)
	finally 
	  (call-stack-instruction-emitter funcall-instruction
	    byte-code-stream 'make-evaluated-structure (length args) 1)))

(defun-void pprint-make-evaluated-structure-instruction
    (description pc byte-code-body constant-vector stack top-of-stack arg-count result-count)
  (declare (ignore description pc byte-code-body constant-vector result-count))
  (twrite-string "evaluated-structure(")
  (loop for index from 1 to arg-count
	do
    (unless (=f index 1)
      (twrite-string ", "))
    (write-stack-argument index arg-count stack top-of-stack))
  (twrite-character #.%\)))

(def-funcalled-instruction make-evaluated-structure (79 all (+ (0) 1) 1 nil
							pprint-make-evaluated-structure-instruction)
  (let* ((key-count-times-two-arg (svref local-stack top-of-stack))
	 (key-count-times-two
	   (evaluation-integer-value key-count-times-two-arg))
	 (base-stack-index (-f top-of-stack key-count-times-two))
	 (new-sequence (allocate-evaluation-structure-from-vector
			 local-stack base-stack-index key-count-times-two)))
    (declare (type fixnum key-count-times-two base-stack-index))
    (reclaim-evaluation-integer element-count-arg)
    (setf (svref local-stack base-stack-index) new-sequence)
    nil))





;;;; 5.0 Text Evaluator Functions


;; Instruction numbers 100-119 Reserved for this set of functions.  Not all have
;; been assigned to date. (MHD/JRA 8/14/96)

;;; The `character-codes-to-text stack-evaluator' converts a
;;; character-codes-sequence, an evaluation sequence, to a text whose characters
;;; correspond one to one with the sequence of characters codes in the argument.
;;; This evaluator is available in the inference engine and procedures.
;;;
;;; If any element of sequence is not a valid character code, i.e., an integer
;;; between 0 and 65535, inclusive, this signals a stack error.

(def-funcalled-evaluator character-codes-to-text (character-codes-sequence)
    (100 (inference procedure)
	 ((sequence)) text
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  ;; Do error checking up front:
  (loop with index fixnum = 0
	for value being
	  each evaluation-sequence-element of character-codes-sequence
	unless (and (fixnump value) (<=f 0 value 65535))
	  do (stack-error
	       cached-top-of-stack
	       "~NA, element ~d of sequence ~NA, is not an integer ~
                       between 0 and 65535, and therefore not a valid ~
                       character code."
	       value index character-codes-sequence)
	do (incff index)
	finally
	  (when (>f index maximum-length-for-user-text-strings)
	    (stack-error
	      cached-top-of-stack
	      "The character-codes-to-text function cannot return a text containing ~
                     more than ~d characters; the argument sequence had ~d elements"
	      maximum-length-for-user-text-strings
	      index))
	;; Now, go at it with reckless abandon.
	  (let ((text-string (obtain-text-string index)))
	    (loop for value being
		    each evaluation-sequence-element of character-codes-sequence
		  as i from 0
		  do (setf (charw text-string i) (code-wide-character value)))
	    (return
	      (prog1
		  (make-evaluation-text text-string)
		(reclaim-evaluation-sequence character-codes-sequence)
		(reclaim-text-string text-string))))))


(def-funcalled-evaluator text-to-character-codes (text)
    (101 (inference procedure)
	 (text) (sequence)
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (let* ((length (text-string-length text))
	 (sequence (allocate-empty-evaluation-sequence length)))
    (loop with managed-array = (car sequence)
	  for i from (evaluation-sequence-first-element-index)
	  as j from 0			; i index in sequence; j index in text
	  repeat length
	  do (setf (managed-svref managed-array i)
		   (wide-character-code (charw text j))))
    (reclaim-evaluation-text text)
    sequence))





(defun-simple require-evaluation-value-as-valid-character-code
    (evaluation-value)
  (unless (and (evaluation-integer-p evaluation-value)
	       (<=f 0
		    (evaluation-integer-value evaluation-value)
		    65535))
    (stack-error
      cached-top-of-stack
      "~NA is not an integer ~
          between 0 and 65535, and therefore not a valid ~
          character code."
      evaluation-value)))

(def-funcalled-evaluator is-uppercase (character-code)
    (102 (inference procedure)
	 (integer) truth-value
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (let ((character-code (evaluation-integer-value character-code)))
    (if (unicode-uppercase-p character-code)      
	(make-evaluation-truth-value truth)
	(make-evaluation-truth-value falsity))))

(def-funcalled-evaluator is-titlecase (character-code)
    (103 (inference procedure)
	 (integer) truth-value
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (let ((character-code (evaluation-integer-value character-code)))
    (if (unicode-titlecase-p character-code)   
	(make-evaluation-truth-value truth)
	(make-evaluation-truth-value falsity))))

(def-funcalled-evaluator is-lowercase (character-code)
    (104 (inference procedure)
	 (integer) truth-value
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (let ((character-code (evaluation-integer-value character-code)))
    (if (unicode-lowercase-p character-code)   
	(make-evaluation-truth-value truth)
	(make-evaluation-truth-value falsity))))

(def-funcalled-evaluator to-uppercase (character-code)
    (105 (inference procedure)
	 (integer) integer
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (let ((character-code (evaluation-integer-value character-code)))
    (make-evaluation-integer (unicode-upcase character-code))))

(def-funcalled-evaluator to-titlecase (character-code)
    (106 (inference procedure)
	 (integer) integer
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (let ((character-code (evaluation-integer-value character-code)))
    (make-evaluation-integer (unicode-titlecase character-code))))

(def-funcalled-evaluator to-lowercase (character-code)
    (107 (inference procedure)
	 (integer) integer
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (let ((character-code (evaluation-integer-value character-code)))
    (make-evaluation-integer (unicode-downcase character-code))))

(def-funcalled-evaluator is-digit (character-code)
    (108 (inference procedure)
	 (integer) truth-value
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (let ((character-code (evaluation-integer-value character-code)))
    (if (unicode-digit-p character-code)
	(make-evaluation-truth-value truth)
	(make-evaluation-truth-value falsity))))

(def-funcalled-evaluator is-readable-digit (character-code)
    (109 (inference procedure)
	 (integer) truth-value
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (let ((character-code (evaluation-integer-value character-code)))
    (if (g2-readable-unicode-digit-p character-code)
	(make-evaluation-truth-value truth)
	(make-evaluation-truth-value falsity))))


(defun require-evaluation-value-as-valid-radix (evaluation-value)
  (unless (and (evaluation-integer-p evaluation-value)
	       (<=f 2 (evaluation-integer-value evaluation-value) 36))
    (stack-error
      cached-top-of-stack
      "~NA is not an integer ~
          between 2 and 36, and therefore not a valid radix."
      evaluation-value)))

(def-funcalled-evaluator is-readable-digit-in-radix (character-code radix)
    (110 (inference procedure)
	 (integer integer) truth-value
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (require-evaluation-value-as-valid-character-code character-code)
  (require-evaluation-value-as-valid-radix radix)
  (let ((character-code (evaluation-integer-value character-code))
	(radix (evaluation-integer-value radix)))
    (if (g2-readable-unicode-digit-in-radix character-code radix)
	(make-evaluation-truth-value truth)
	(make-evaluation-truth-value falsity))))


;;; `Readable-text-for-value' handles turning an evaluation value into that
;;; value's `readable representation text', i.e., such that reading back in such
;;; text through G2's parser/tokenizer would result in the same (=) value.  This
;;; returns the corresponding text if it can.  It only do so if the type of
;;; value has a readable representation (i.e., could be typed in) in the first
;;; place.  If value is one of the following types, it has a readable
;;; representation:
;;;
;;;    text  quantity   symbol  truth-value
;;;
;;; If there is no readable representation, this signals a stack error.

;;; ... We assume that write-evaluation-value writes values parsably.
;;; Furthermore, we assume that any symbol value that is syntactically anomolous
;;; has the appropriate property set.  (When a symbol makes it through
;;; tokenizer/parser with quoting, but without quoting would have looked less
;;; like a symbol than something else, e.g., a number or a punctuation mark,
;;; then the symbol's property type-of-syntactic-anomaly is set to true.  This
;;; information is even restored upon reading from a KB.)

(def-funcalled-evaluator readable-text-for-value (value)
    (111 (inference procedure)
	 (datum) text			; datum = value in user's terminology
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (let (result)
    (cond
     ((or (evaluation-quantity-p value)
	  (evaluation-text-p value)
	  (evaluation-symbol-p value)
	  (evaluation-truth-value-p value))
      (setq result (twith-output-to-text-string
		     (write-evaluation-value value)))
      (reclaim-if-evaluation-value value)
      result)
     (t
      (stack-error
	cached-top-of-stack
	"The value ~NV has no readable representation."
	value)))))



;;; `Readable-text' turns `printable representation text', i.e., text in its
;;; printed, or "pretty", form, into "readable representation" for the same
;;; text.  For example, if printable-representation-text is the text
;;;
;;;    Use quotes around email addresses: "mhd@gensym.com"
;;;
;;; this returns the text
;;;
;;;    "Use quotes around email addresses: @"mhd@@gensym.com@"
;;;
;;;
;;; `Readable-symbol-text' is similar.  It also returns a text, but the text
;;; returned is readable that would read in as the symbol whose text is the
;;; argument printed-representation-text.  For example, if
;;; printable-representation-text is the text
;;;
;;;    SYMBOL WiTH SPACES++
;;;
;;; might return the text
;;;
;;;    symbol@ w@ith@ spaces@+@+
;;;
;;; which, if read in by G2's parser/tokenizer, would be read in as a single
;;; symbol consisting of the letters in the printable text.  
;;;
;;; Note: the following would also be a valid result:
;;;
;;;   SYMBOL@ W@iTH@ SPACES@+@+
;;;
;;; since it would result in the same symbol when read in.
;;;
;;; Notice that the spaces and +'s are quoted, and so is the lowercase 'i' in
;;; "with".  This ensures that the spaces and +'s are accepted, and the 'i' is
;;; not uppercased, by tokenization.  Note also that this only guarantees that
;;; it will be readable as the symbol with the same printed representation,
;;; i.e., the same print name in Lisp parlance.

(def-funcalled-evaluator readable-text
    (printed-representation-text)
    (112 (inference procedure)
	 (text) text
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (let ((write-strings-parsably? t)
	result)
    (setq result (twith-output-to-text-string
		   (twrite-string printed-representation-text)))
    (reclaim-evaluation-text printed-representation-text)
    result))


(def-funcalled-evaluator readable-symbol-text
    (printed-representation-text)
    (113 (inference procedure)
	 (text) text
	 funcall-eval-type-1-arg
	 nil pprint-functional-evaluator)
  (let ((problem-string?
	  (non-valid-symbol-text-string-p printed-representation-text)))
    (cond
      (problem-string?
       (let* ((length (text-string-length printed-representation-text))
	      (max-length 200)
	      (truncate-p (>f length max-length))
	      (small-text
		(if truncate-p
		    (text-string-substring
		      printed-representation-text 0 max-length)
		    printed-representation-text)))	    
	 (write-stack-error
	     cached-top-of-stack
	   (tformat
	     (if truncate-p
		 "The text beginning with \"~a...\" is not valid as the text of a symbol.  ~a"
		 "The text \"~a\" is not valid as the text of a symbol.  ~a")
	     small-text
	     problem-string?)
	   (when truncate-p
	     (reclaim-text-string small-text)))))
      (t
       (let ((symbol
	       (intern-text-string
		 (copy-text-string printed-representation-text)))
	     (write-symbols-parsably? t)
	     result)
	 (cond
	   ((punctuation-mark-p symbol)
	    (setq symbol
		  (intern-text-string
		    (copy-text-string printed-representation-text)
		    keyword-package-1))
	    ;; Apparently not needed -- keep in synch with tokenizer! (MHD 10/11/96)
;       (setf (type-of-syntactic-anomaly symbol)
;	     'punctuation-mark)
	    )
	   ((syntactically-numeric-p (symbol-name-text-string symbol))
	    (setf (type-of-syntactic-anomaly symbol) 'numeric)))
	 (setq result (twith-output-to-text-string
			(twrite-symbol symbol)))
	 (reclaim-evaluation-text printed-representation-text)
	 result)))))

;; This handles syntactic anomolies like symbols that look like numbers and
;; symbols that look like punctuation.  This does not handle detecting illegal
;; symbol text yet, but that's coming!  It does not handle symbols that look
;; like class-qualified name symbols (foo::bar).  If anyone could give a
;; sensible proposal, I'd like to hear it! (MHD 10/11/96)


(def-funcalled-evaluator compare-text (text-1 text-2)
    (115 (inference procedure)
	 (text text) integer
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (prog1 (if (string<w (evaluation-text-value text-1)
		       (evaluation-text-value text-2))
	     (make-evaluation-integer -1)
	     (if (string=w (evaluation-text-value text-1)
			   (evaluation-text-value text-2))
		 (make-evaluation-integer 0)
		 (make-evaluation-integer 1)))
    (reclaim-evaluation-text text-1)
    (reclaim-evaluation-text text-2)))
    

(defun-simple map-to-internal-text-conversion-style
    (text-conversion-style-frame)
  (internal-structure-for-text-conversion-style text-conversion-style-frame))

(def-funcalled-evaluator import-text (text text-conversion-style)
    (116 (inference procedure)
	 (text (class text-conversion-style)) text
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (prog1 (import-text-string-per-text-conversion-style
	   (evaluation-text-value text)
	   (or (map-to-internal-text-conversion-style
		 text-conversion-style)
	       default-text-conversion-style))
    (reclaim-evaluation-text text)))


(def-funcalled-evaluator export-text (text text-conversion-style)
    (117 (inference procedure)
	 (text (class text-conversion-style)) text
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (prog1 (export-text-string-per-text-conversion-style
	   (evaluation-text-value text)
	   (or (map-to-internal-text-conversion-style
		 text-conversion-style)
	       default-text-conversion-style))
    (reclaim-evaluation-text text)))



(def-funcalled-evaluator transform-text-for-unicode-comparison (text consider-case-p)
    (118 (inference procedure)
	 (text truth-value) text
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (if (evaluation-truth-value-true-p consider-case-p)
      (evaluation-text-value text)	; noop case
      (nstring-downcasew (evaluation-text-value text)))) ; change in place



(def-funcalled-evaluator transform-text-for-g2-4.0-comparison (text consider-case-p)
    (119 (inference procedure)
	 (text truth-value) text
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (prog1 (export-text-string
	   (if (evaluation-truth-value-true-p consider-case-p)
	       (evaluation-text-value text)
	       (nstring-downcasew (evaluation-text-value text)))
	   'utf-g-wide-string)
    (reclaim-evaluation-text text)))




;;;; Sequence Functions




;;; The `remove funcalled evaluator' takes a sequence and a zero-based index
;;; into that sequence, and it removes the item at the given index.

(def-funcalled-evaluator remove (sequence index-to-remove)
    (123 (inference procedure)
	 ((sequence) integer) (sequence)
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (let ((new-sequence
	  (evaluation-sequence-remove-element-at-index
	    sequence index-to-remove)))
    (if new-sequence
	new-sequence
	(stack-error
	  cached-top-of-stack
	  "The index ~A was not within the range of indices for ~NE."
	  index-to-remove sequence))))




;;; The `insert-at-beginning funcalled evaluator' takes a sequence and a new
;;; item-or-value element.  A new sequence is returned which contains the given
;;; new element as its first value, and the elements of the argument sequence as
;;; the remaining elements.

(def-funcalled-evaluator insert-at-beginning (sequence item-or-value-to-add)
    (124 (inference procedure)
	 ((sequence) item-or-datum) (sequence)
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (evaluation-sequence-insert-at-beginning sequence item-or-value-to-add))




;;; The `insert-at-end funcalled evaluator' takes a sequence and a new
;;; item-or-value element.  A new sequence is returned which contains the
;;; elements of the argument sequence and then the given element as its last
;;; value.

(def-funcalled-evaluator insert-at-end (sequence item-or-value-to-add)
    (125 (inference procedure)
	 ((sequence) item-or-datum) (sequence)
	 funcall-eval-type-2-arg
	 nil pprint-functional-evaluator)
  (evaluation-sequence-insert-at-end sequence item-or-value-to-add))




;;; The function `evaluation-sequence-insert-before-or-after' implements the
;;; insert-before and insert-after funcalled evaluators.

(defun-simple evaluation-sequence-insert-before-or-after
    (sequence new-element existing-element before?)
  (let* ((new-length (1+f (evaluation-sequence-length sequence)))
	 (new-sequence (allocate-empty-evaluation-sequence new-length)))
    (loop with insertion-done = nil
	  for index from 0
	  for element being each evaluation-sequence-element of sequence
	  do
      (when (and (not insertion-done)
		 before?
		 (item-or-value-eql element existing-element))
	(setf (evaluation-sequence-ref new-sequence index) new-element)
	(incff index)
	(setq insertion-done t))
      (setf (evaluation-sequence-ref new-sequence index)
	    (copy-if-evaluation-value element))
      (when (and (not insertion-done)
		 (not before?)
		 (item-or-value-eql element existing-element))
	(incff index)
	(setf (evaluation-sequence-ref new-sequence index) new-element)
	(setq insertion-done t))
	  finally
	    (unless insertion-done
	      (reclaim-evaluation-sequence new-sequence)
	      (stack-error
		cached-top-of-stack
		"Unable to find ~NA in ~NA, cannot insert ~NA as new element."
		existing-element sequence new-element)))
    (reclaim-evaluation-sequence sequence)
    (reclaim-if-evaluation-value existing-element)
    new-sequence))
		




;;; The `insert-before funcalled evaluator' takes a sequence, a new element to
;;; insert, and an item-or-value within the given sequence.  This function will
;;; return a new sequence with the same elements as the argument sequence, but
;;; with the new element inserted before the first occurrence of the given
;;; element.

(def-funcalled-evaluator insert-before (sequence new-element existing-element)
    (126 (inference procedure)
	 ((sequence) item-or-datum item-or-datum) (sequence)
	 funcall-eval-type-3-arg
	 nil pprint-functional-evaluator)
  (evaluation-sequence-insert-before-or-after
    sequence new-element existing-element t))




;;; The `insert-after funcalled evaluator' takes a sequence, a new element to
;;; insert, and an item-or-value within the given sequence.  This function will
;;; return a new sequence with the same elements as the argument sequence, but
;;; with the new element inserted after the first occurrence of the given
;;; element.

(def-funcalled-evaluator insert-after (sequence new-element existing-element)
    (127 (inference procedure)
	 ((sequence) item-or-datum item-or-datum) (sequence)
	 funcall-eval-type-3-arg
	 nil pprint-functional-evaluator)
  (evaluation-sequence-insert-before-or-after
    sequence new-element existing-element nil))




;;; The function `evaluation-sequence-insert-before-or-after-element' implements
;;; the insert-before-element, insert-after-element, and change-element
;;; funcalled evaluators.  The index given is the new index location of the new
;;; value, and the insert? flag indicates if the given item should be inserted
;;; at that location or if it should overwrite the value at that location.

(defun-simple evaluation-sequence-insert-or-replace-at-index
    (sequence new-element element-index insert?)
  (cond
    ((and (not insert?)
	  (mutable-evaluation-sequence-p sequence)
	  (<=f 0 element-index (evaluation-sequence-length sequence)))
     (reclaim-if-evaluation-value
       (evaluation-sequence-aref sequence element-index))
     (setf (evaluation-sequence-ref sequence element-index) new-element)
     sequence)
    (t
     (let* ((new-length (+f (evaluation-sequence-length sequence)
			    (if insert? 1 0)))
	    (new-sequence (allocate-empty-evaluation-sequence new-length)))
       (cond
	 ((and (=f element-index (-f new-length 1))
	       ;; The following test protects against
	       ;; change-element(sequence(),-1,new_element)
	       ;; which is an error which is treated below.
	       ;; This fixes Bug HQ-4947392. - jpg 1/13/05
	       (/=f element-index -1))
	  (copy-evaluation-sequence-elements
	    sequence 0 (-f new-length 1) new-sequence 0)
	  (setf (evaluation-sequence-ref new-sequence (-f new-length 1))
		new-element))
	 (t
	  (loop with insertion-done? = nil
		for index from 0
		for value being each evaluation-sequence-element of sequence
		do
	    (cond
	      ((and (not insertion-done?)
		    (=f index element-index))
	       (setf (evaluation-sequence-ref new-sequence index) new-element)
	       (setq insertion-done? t)
	       (when insert?
		 (incff index)
		 (setf (evaluation-sequence-ref new-sequence index)
		       (copy-if-evaluation-value value))))
	      (t
	       (setf (evaluation-sequence-ref new-sequence index)
		     (copy-if-evaluation-value value))))
		finally
		  (unless insertion-done?
		    (reclaim-evaluation-sequence new-sequence)
		    (stack-error
		      cached-top-of-stack
		      "Index ~NA in ~NA is out of range, cannot insert ~NA ~
                        as new element."
		      element-index sequence new-element)))))
       (reclaim-evaluation-sequence sequence)
       new-sequence))))




;;; The `insert-before-element funcalled evaluator' takes a sequence, an index
;;; into the sequence, and a new element to insert into the sequence.  This
;;; function will return a new sequence with the same elements as the argument
;;; sequence, but with the new element inserted before the element currently at
;;; the given index.

(def-funcalled-evaluator insert-before-element (sequence index new-element)
    (128 (inference procedure)
	 ((sequence) integer item-or-datum) (sequence)
	 funcall-eval-type-3-arg
	 nil pprint-functional-evaluator)
  (evaluation-sequence-insert-or-replace-at-index
    sequence new-element index t))




;;; The `insert-after-element funcalled evaluator' takes a sequence, an index
;;; into the sequence, and a new element to insert into the sequence.  This
;;; function will return a new sequence with the same elements as the argument
;;; sequence, but with the new element inserted after the element currently at
;;; the given index.

(def-funcalled-evaluator insert-after-element (sequence index new-element)
    (129 (inference procedure)
	 ((sequence) integer item-or-datum) (sequence)
	 funcall-eval-type-3-arg
	 nil pprint-functional-evaluator)
  (evaluation-sequence-insert-or-replace-at-index
    sequence new-element (+f index 1) t))




;;; The `change-element funcalled evaluator' takes a sequence, an index into the
;;; sequence, and a new element to add to the sequence.  This function will
;;; return a new sequence with the same elements as the argument sequence, but
;;; with the new element replacing the element previously at the given index.

(def-funcalled-evaluator change-element (sequence index new-element)
    (130 (inference procedure)
	 ((sequence) integer item-or-datum) (sequence)
	 funcall-eval-type-3-arg
	 nil pprint-functional-evaluator)
  (evaluation-sequence-insert-or-replace-at-index
    sequence new-element index nil))




;;; The special form converter and funcalled instruction `concatenate' is used
;;; to produce a sequence which contains all of the elements of the combined
;;; argument sequences.

(def-special-form-converter concatenate (expression)
  (let ((arguments
	  (loop for arg in (cdr-of-cons expression)
		collect (convert-expression-to-stack-node-tree arg)
		  using stack-cons))
	(stack-node-instruction
	  (make-stack-node-instruction 'concatenate nil)))
    (setf (stack-node-argument-nodes stack-node-instruction) arguments)
    stack-node-instruction))

(declare-optimizer-stack-instruction concatenate)

(def-preferred-instruction-chooser concatenate
  (declare (ignore extra-info))
  (let* ((unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (arg-required-type
	   (maybe-add-unknown '(sequence) unknown-allowed?))
	 (unknown-args? nil)
	 (args (stack-node-argument-nodes stack-node-instruction)))
    (loop for arg-cons on args
	  for arg = (choose-stack-node-instructions-and-types
		      (car-of-cons arg-cons) arg-required-type)
	  do
      (setf (car arg-cons) arg)
      (when (and unknown-allowed?
		 (not unknown-args?)
		 (type-specification-subtype-p
		   '(unknown-datum) (stack-node-value-type arg)))
	(setq unknown-args? t)))
    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-unknown '(sequence) unknown-args?))
    stack-node-instruction))

(def-stack-node-instruction-emitter concatenate
  (declare (ignore extra-info))
  (loop with args = (stack-node-argument-nodes stack-node-instruction)
	for arg in args
	do
    (emit-stack-node-tree byte-code-stream arg)
	finally 
	  (call-stack-instruction-emitter funcall-instruction
	    byte-code-stream 'concatenate (length args) 1)))

(defun-void pprint-concatenate-instruction
    (description pc byte-code-body constant-vector stack top-of-stack arg-count result-count)
  (declare (ignore description pc byte-code-body constant-vector result-count))
  (twrite-string "concatenate(")
  (loop for index from 1 to arg-count
	do
    (unless (=f index 1)
      (twrite-string ", "))
    (write-stack-argument index arg-count stack top-of-stack))
  (twrite-character #.%\)))

(def-funcalled-instruction concatenate (84 all (+ (0) 1) 1 nil
					   pprint-concatenate-instruction)
  (let* ((arg-count-arg (svref local-stack top-of-stack))
	 (arg-count (evaluation-integer-value arg-count-arg))
	 (base-stack-index (-f top-of-stack arg-count))
	 (sequence-pairs
	   (loop for index from base-stack-index below top-of-stack
		 for seq = (svref local-stack index)
		 collect (eval-cons seq (evaluation-sequence-length seq))
		   using eval-cons))
	 (new-length (loop for pair in sequence-pairs
			   sum (cdr-of-cons pair) fixnum))
	 (new-sequence (allocate-empty-evaluation-sequence new-length)))
    (reclaim-evaluation-integer arg-count-arg)
    (loop for insertion-point fixnum = 0 then (+f insertion-point length)
	  for pair in sequence-pairs
	  for seq = (car-of-cons pair)
	  for length = (cdr-of-cons pair)
	  do
      (reclaim-eval-cons pair)
      (copy-evaluation-sequence-elements
	seq 0 length new-sequence insertion-point)
      (reclaim-evaluation-sequence seq))
    (reclaim-eval-list sequence-pairs)
    (setf (svref local-stack base-stack-index) new-sequence)
    nil))




;;; The `portion funcalled evaluator' takes a sequence, an index into the
;;; sequence, and a number of elements of the sequence to copy.  It returns a
;;; new sequence containing a portion of the elements of the argument sequence.
;;; The first integer argument is the index at which to start copying, and the
;;; second integer argument is the number of elements to return in the new
;;; sequence.

(def-funcalled-evaluator portion (sequence start-index number-to-copy)
    (131 (inference procedure)
	 ((sequence) integer integer) (sequence)
	 funcall-eval-type-3-arg
	 nil pprint-functional-evaluator)
  (let* ((index (evaluation-integer-value start-index))
	 (count (evaluation-integer-value number-to-copy))
	 (source-length (evaluation-sequence-length sequence)))
    (declare (type fixnum index count source-length))
    (when (<f index 0)
      (stack-error
	cached-top-of-stack
	"In PORTION, the starting index argument, ~a, was less than zero."
	index))
    (when (<f count 0)
      (stack-error
	cached-top-of-stack
	"In PORTION, the number of elements to copy argument, ~a, was less than zero."
	count))
    (when (>f (+f index count) source-length)
      (stack-error
	cached-top-of-stack
	"In PORTION, the starting index, ~a, plus the number of elements to ~@
         copy, ~a, was greater than the length of the source sequence, ~a."
	index count source-length))
    (let ((new-sequence (allocate-empty-evaluation-sequence count)))
      (copy-evaluation-sequence-elements
	sequence index count new-sequence 0)
      (reclaim-evaluation-integer start-index)
      (reclaim-evaluation-integer number-to-copy)
      (reclaim-evaluation-sequence sequence)
      new-sequence)))




;;; The `change-attribute' operation is implemented as a special form converter
;;; into the evaluated form of this operation, change-evaluated-attribute.  The
;;; difference between them is that the symbol naming the argument to be changed
;;; is implicitly quoted in this operation, and is an evaluated expression in
;;; the other.

(def-special-form-converter change-attribute (expression)
  (let* ((evaluator-descriptions (stack-evaluators 'change-evaluated-attribute))
	 (node (make-stack-node 'change-evaluated-attribute
				evaluator-descriptions))
	 (attribute-name (third expression)))
    (unless (and attribute-name
		 (symbolp attribute-name))
      (compiler-error
	"The second argument to change-attribute should be the attribute name ~
         to be changed, not an expression that evaluates to that name.  ~
         \"~NE\" was provided instead of a name."
	attribute-name)
      (setq attribute-name 'stand-in))
    (setf (stack-node-argument-nodes node)
	  (make-stack-argument-nodes
	    'change-evaluated-attribute
	    (phrase-list (second expression)
			 (phrase-list 'quote attribute-name)
			 (fourth expression))
	    evaluator-descriptions))
    node))




;;; The `change-evaluated-attribute funcalled evaluator' takes a structure, a
;;; symbol naming an attribute, and an item-or-value.  It creates and returns a
;;; new structure containing all of the same attributes and values in the
;;; argument structure, but with the given attribute-name containing the given
;;; item-or-value. If the attribute did not exist within the argument structure,
;;; the new attribute is added to the end. If the attribute already existed
;;; within the argument structure, then its value is changed keeping its same
;;; position within the attribute order in this structure.

(def-funcalled-evaluator change-evaluated-attribute (struct attribute new-value)
    (132 (inference procedure) ((structure) symbol item-or-datum) (structure)
	 funcall-eval-type-3-arg nil pprint-functional-evaluator)
  (let ((result-struct (obtain-mutable-evaluation-structure-copy struct))
	(name (evaluation-symbol-symbol attribute)))
    (reclaim-evaluation-symbol attribute)
    (setf (evaluation-structure-slot-macro result-struct name) new-value)
    result-struct))




;;; The `remove-attribute' operation is implemented as a special form converter
;;; into the evaluated form of this operation, remove-evaluated-attribute.  The
;;; difference between them is that the symbol naming the argument to be changed
;;; is implicitly quoted in this operation, and is an evaluated expression in
;;; the other.

(def-special-form-converter remove-attribute (expression)
  (let* ((evaluator-descriptions (stack-evaluators 'remove-evaluated-attribute))
	 (node (make-stack-node 'remove-evaluated-attribute
				evaluator-descriptions))
	 (attribute-name (third expression)))
    (unless (and attribute-name
		 (symbolp attribute-name))
      (compiler-error
	"The second argument to remove-attribute should be the attribute name ~
         to be removed, not an expression that evaluates to that name.  ~
         \"~NE\" was provided instead of a name."
	attribute-name)
      (setq attribute-name 'stand-in))
    (setf (stack-node-argument-nodes node)
	  (make-stack-argument-nodes
	    'remove-evaluated-attribute
	    (phrase-list (second expression)
			 (phrase-list 'quote attribute-name))
	    evaluator-descriptions))
    node))




;;; The `remove-evaluated-attribute funcalled evaluator' takes a structure and a
;;; symbol possibly naming an attribute in that structure.  It reclaims the
;;; arguments and creates a new structure containing all of the same attributes
;;; and values as the argument structure, but with the named attribute removed.
;;; If the named attribute was not in the argument structure, then an exact copy
;;; of the argument structure is returned.

(def-funcalled-evaluator remove-evaluated-attribute (struct attribute)
    (133 (inference procedure) ((structure) symbol) (structure)
	 funcall-eval-type-2-arg nil pprint-functional-evaluator)
  (let* ((name (evaluation-symbol-symbol attribute))
	 (result-struct? (remove-evaluation-structure-attribute struct name)))
    (reclaim-evaluation-symbol attribute)
    (cond (result-struct?
	   (reclaim-evaluation-structure struct)
	   result-struct?)
	  (t
	   struct))))




;; This is a function that the documentation generator expects to
;; be able to call. See if this function is necessary, since the
;; current implementation does not implement restrictions for
;; visibility of attributes given a class.

#+development
(defun-simple attribute-descriptions-of-class (class-name user-mode)
  (let ((visible-attributes (g2-get-attributes-visible-in-mode class-name user-mode))
	(class-description (class-description class-name)))
    (loop with name-and-description-alist
	    = (get-list-of-all-user-visible-attributes class-description)
	  for (name . slot) in name-and-description-alist
	  when (evaluation-value-in-sequence-p name visible-attributes)
	    collect (generate-description-of-attribute class-name
		      name slot class-description nil user-mode nil)
	      into struct-list
	      using eval-cons
	  finally
	    (reclaim-eval-alist name-and-description-alist)
	    (reclaim-evaluation-value visible-attributes)
	    (return (allocate-evaluation-sequence struct-list)))))



;;; The `find-java-class funcalled evaluator' only does anything in code that is
;;; export to java via export-definition's.  This always signals an error in the
;;; G2 evaluator.

(def-funcalled-evaluator find-java-class (java-class-name-as-text)
    (137 (procedure) (text) item-or-datum
	 funcall-eval-type-1-arg nil pprint-functional-evaluator)
  (stack-error
	cached-top-of-stack
	"FIND-JAVA-CLASS works only in exported methods and procedures")
  (reclaim-evaluation-text java-class-name-as-text))



(def-funcalled-evaluator network-interface-for (item)
    (138 all ((class item)) (class network-interface)
	 funcall-eval-type-1-arg nil pprint-functional-evaluator)
  (let ((interface? (g2-lookup-network-interface-for-home (g2-item-home item))))
    (unless interface?
      (stack-error
	cached-top-of-stack
	"Could not find a network interface for ~NF"
	item))
    interface?))


(def-funcalled-evaluator in-the-tracked-item-set (item)
                         (139 (inference)
			      ((class item)) boolean
			      funcall-eval-type-1-arg nil pprint-functional-evaluator)
  (if (tracking-item-in-set-p item)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))


(defun-simple item-has-unsaved-changes-p (item)
  (and (not (transient-p item))
       (permanent-block-p item)
       (or (superior-frame item)
	   (frame-of-class-p item 'kb-workspace)
	   (and (frame-of-class-p item 'system-frame)
		(not (frame-of-class-p item 'server-parameters))))
       (or (not (item-was-created-by-load-p item))
	   (attributes-permamently-changed item))))

(defun-simple item-has-unsaved-changes-visible-in-tables-p (item)
  (and (not (transient-p item))
       (permanent-block-p item)
       (or (superior-frame item)
	   (frame-of-class-p item 'kb-workspace)
	   (and (frame-of-class-p item 'system-frame)
		(not (frame-of-class-p item 'server-parameters))))
       (or (not (item-was-created-by-load-p item))
	   (item-has-unsaved-changes-visible-in-tables-p-1 item))))

(defun-simple attribute-may-be-visible-in-tables-p (item attribute)
  (or (consp attribute)
      (let ((slot-description?
	      (get-slot-description-of-frame attribute item)))
	(and slot-description?
	     (not (do-not-put-slot-in-attribute-tables-p
		      slot-description? nil item))
	     (category-symbol-given-slot-type
	       (feature-assq 'type
			     (slot-features slot-description?)))))))

(defun-simple item-has-unsaved-changes-visible-in-tables-p-1 (item)
  (let ((attributes (attributes-permamently-changed item)))
    (or (not (listp attributes))
	(loop for attribute in attributes
	      thereis (attribute-may-be-visible-in-tables-p item attribute)))))

(defun-simple item-has-unsaved-changes-not-visible-in-tables-p (item)
  (and (not (transient-p item))
       (permanent-block-p item)
       (or (superior-frame item)
	   (frame-of-class-p item 'kb-workspace)
	   (and (frame-of-class-p item 'system-frame)
		(not (frame-of-class-p item 'server-parameters))))
       (or (not (item-was-created-by-load-p item))
	   (item-has-unsaved-changes-not-visible-in-tables-p-1 item))))

(defun-simple item-has-unsaved-changes-not-visible-in-tables-p-1 (item)
  (let ((attributes (attributes-permamently-changed item)))
    (or (not (listp attributes))
	(loop for attribute in attributes
	      thereis (not (attribute-may-be-visible-in-tables-p item attribute))))))

(def-funcalled-evaluator with-unsaved-changes (item)
			 (140 (inference procedures)
			     ((class item)) boolean
			     funcall-eval-type-1-arg)
  (if (item-has-unsaved-changes-p item)
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))

(defvar mark-for-modules-with-unsaved-changes 0)

(def-kb-specific-property-name module-has-unsaved-changes)

(defun-simple modules-with-unsaved-changes ()
  (incff mark-for-modules-with-unsaved-changes)
  ;; Should iterate over the module/workspace heirarchy instead, for performance.
  (loop for item being each class-instance of 'item
	when (and (item-has-unsaved-changes-p item)
		  ;; GENSYMCID-694: G2 Server abort while attempting to save KB after
		  ;;                deleting item on WS and double clicking WS name.
		  ;; Prevent to get the module of a frame being delete.
		  (not (equal (frame-serial-number item) (frame-serial-number-recycled))))
	  do (setf (module-has-unsaved-changes (get-module-block-is-in item))
		   mark-for-modules-with-unsaved-changes))
  (loop for suite in modules-and-system-tables-a-list
	as module-information-instance = (first suite)
	as module-name = (top-level-kb-module? module-information-instance)
	as unsaved-changes-p = (eql (module-has-unsaved-changes module-name)
				    mark-for-modules-with-unsaved-changes)
	when unsaved-changes-p
	  collect module-name using gensym-cons))

(defun-void twrite-changed-modules-note ()
  (let ((module-list (modules-with-unsaved-changes)))
    (when module-list
      (tformat "~%")
      (if (memq nil module-list)
	  (tformat "(Note that there are unsaved changes.)")
	  (tformat "(Note that the module~a ~L,& ~a unsaved changes.)"
		   (if (cdr module-list) "s" "")
		   module-list
		   (if (cdr module-list) "have" "has")))
      (reclaim-gensym-list module-list))))

(def-stack-error divide-by-zero-error (item top-of-stack)
  "~NF is divided by zero." item)

(def-funcalled-evaluator div-long (dividend divisor)
    (143 all (number number) long funcall-eval-type-2-arg)
  (cond ((fixnump dividend)
	 (setq dividend (make-evaluation-long dividend)))
	((evaluation-float-p dividend)
	 (setq dividend
	       (make-evaluation-long (round (evaluation-float-value dividend))))))
  (cond ((fixnump divisor)
	 (setq divisor (make-evaluation-long divisor)))
	((evaluation-float-p divisor)
	 (setq divisor
	       (make-evaluation-long (round (evaluation-float-value divisor))))))
  (prog1
      (if (zerop (evaluation-long-value divisor))
	  (divide-by-zero-error (evaluation-long-value divisor)
				cached-top-of-stack)
	(div-long dividend divisor))
    (reclaim-evaluation-long divisor)))

(setf (argument-range 'div-long) 2)

;;;[tam.srogatch][2010-11-22]: Allow callling g2nke_count_history_datapoints_matching_op
;;;  from a KB function (not only from a procedure)
(def-funcalled-evaluator kbf-g2nke-count-history-matching-op
  ( arg-subj
    arg-N  arg-nStart  arg-fellow-val 
    arg-requiredGoodSize  arg-compareOperator
  )
  (
    144 all
	( (class quantitative-parameter) 
	  integer integer number
	  integer integer
	) 
	float
	funcall-eval-type-6-arg
  )
  (kb-g2nke-count-history-matching-op
    arg-subj
	arg-N arg-nStart arg-fellow-val 
    arg-requiredGoodSize arg-compareOperator
  )
)

(setf (argument-range 'kbf-g2nke-count-history-matching-op) 6)

(defvar cached-subj nil)
(defvar cached-N nil)
(defvar cached-nStart nil)
(defvar cached-fellow-val nil)
(defvar cached-eventFlag nil)
(defvar cached-event-bit nil)
(defvar cached-requiredGoodSize nil)
(defvar cached-compareOperator nil)
(defvar cached-result nil)

(def-funcalled-evaluator kbf-g2nke-count-history-matching-op-and-eventflag
  ( arg-subj
    arg-N  arg-nStart  arg-fellow-val
    arg-eventFlag  arg-event-bit
    arg-requiredGoodSize  arg-compareOperator
  )
  (
    145 all
	( (class quantitative-parameter) 
	  integer  integer  number
	  (class quantitative-parameter)  integer
	  integer integer
	) 
	float
	funcall-eval-type-8-arg
  )
  (cond
    ((and (eq cached-subj arg-subj)
	  (eq cached-N arg-N)
	  (eq cached-nStart arg-nStart)
	  (eq cached-fellow-val arg-fellow-val)
	  (eq cached-eventFlag arg-eventFlag)
	  (eq cached-event-bit arg-event-bit)
	  (eq cached-requiredGoodSize arg-requiredGoodSize)
	  (eq cached-compareOperator arg-compareOperator))
     (copy-evaluation-float cached-result))
    (t
     (setq cached-subj arg-subj)
     (setq cached-N arg-N)
     (setq cached-nStart arg-nStart)
     (setq cached-fellow-val arg-fellow-val)
     (setq cached-eventFlag arg-eventFlag)
     (setq cached-event-bit arg-event-bit)
     (setq cached-requiredGoodSize arg-requiredGoodSize)
     (setq cached-compareOperator arg-compareOperator)
     (setq cached-result
  (kb-g2nke-count-history-matching-op-and-eventflag
    arg-subj
	arg-N  arg-nStart  arg-fellow-val
	arg-eventFlag  arg-event-bit
    		arg-requiredGoodSize arg-compareOperator))
     (copy-evaluation-float cached-result)))
  )

(setf (argument-range 'kbf-g2nke-count-history-matching-op-and-eventflag) 8)

(def-funcalled-evaluator vector-add (array1 array2 array3)
    (146 all
	((class quantity-array) (class quantity-array) (class quantity-array)) (class quantity-array)
	funcall-eval-type-3-arg)
  (g2-vector-add array1 array2 array3 0)
  array3)

(setf (argument-range 'vector-add) 3)

(def-funcalled-evaluator vector-multiply (array1 array2)
    (147 all
	((class quantity-array) (class quantity-array)) float
	funcall-eval-type-2-arg)
  (g2-array-multiply array1 array2))

(setf (argument-range 'vector-multiply) 2)

(def-funcalled-evaluator vector-scalar-multiply (array1 x array2)
    (148 all
	((class quantity-array) float (class quantity-array)) (class quantity-array)
	funcall-eval-type-3-arg)
  (g2-scalar-multiply array1 array2 x)
  array2)

(setf (argument-range 'vector-scalar-multiply) 3)

;;; The `IS RESIZED BY THE USER stack evaluator'
;;; is event logical predicate that is used as a place holders
;;; from which forward chaining links are generated.  They are chained to
;;; whenever an icon is resized by G2.  This event predicate should always return
;;; true.  This evaluator are only available in the inference engine.
(def-funcalled-evaluator is-resized-by-the-user (item)
			 (150 (inference) ((class item)) boolean
			     funcall-eval-type-1-arg)
  (declare (ignore item))
  (make-evaluation-truth-value truth))

;;; The `NUMBER-OF-ARGUMENTS-FOR-PROCEDURE stack-evaluator' accepts one argument 
;;; of type procedure and returns the number of its arguments.
;;; This evaluator is available in the inference engine and procedures.

(def-funcalled-evaluator number-of-arguments-for-procedure (proc)
			 (151 (inference procedure)
			     ((class procedure)) integer
			     funcall-eval-type-1-arg
			     nil pprint-functional-evaluator)
  (let ((result (make-evaluation-integer (argument-count proc))))
    result))

;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; progn.lsp -- progn and other random special forms and macros
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  30 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/progn.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2007/07/10 16:57:57 $")

;;; The various PROGx guys.

(define-toplevel-form progn (&body forms)
  (if *toplevel-p*
      (translate-toplevel-body forms *environment* *compile-time-too*)
      (translate-progn-body forms *environment* *context* nil *result-type*)))

(deftranslate prog1 (first &body forms)
  (cond ((eq *context* ':result-type-only)
	 (re-translate-form `(values ,first)))
	((eq *context* *ignore-context*)
	 (translate-progn-body (cons first forms)
			       *environment* *ignore-context* nil))
	;;((endp forms)
	;; (re-translate-form `(values ,first)))
	((value-saving-context-p *context*)
	 (multiple-value-bind (statements value type temps)
	     (re-translate-form `(values ,first))
	   (values (nconc (with-stack-level
			    (translate-progn-body forms
						  *environment*
						  *ignore-context*
						  nil))
			  statements)
		   value type temps)))
	(t
	 (let ((temp (make-symbol "TEMP"))
	       (type (and-types
		       (translator-foreign-type-lisp-type
			 (context-foreign-type *context*))
		       (single-value-type *result-type*))))
	   (re-translate-form
	     `(let ((,temp ,first))
		(declare (type ,type ,temp))
		,@forms ,temp))))))

;;; Push the work off onto the prog1 handler.

(deftranslate prog2 (first second &body forms)
  (re-translate-form `(progn ,first (prog1 ,second ,@forms))))

;;; PROG and PROG* are the obvious macros.

(define-translator-macro prog (variable-list &body body)
  (prog-helper variable-list body 'let))

(define-translator-macro prog* (variable-list &body body)
  (prog-helper variable-list body 'let*))

(defun prog-helper (variable-list body binding-form)
  (multiple-value-bind (real-body decls) (parse-body body)
    `(block nil
       (,binding-form ,variable-list
         (declare ,@decls)
	 (tagbody ,@real-body)))))


;;; LOCALLY (see binding.lsp for more details on declaration handling)

(define-toplevel-form locally (&body body)
  (translate-locally body))

(defun translate-locally (body)
  (multiple-value-bind (real-body decls doc message)
      (parse-body body)
    (declare (ignore doc))
    (with-translator-message message
      (let ((env (translator-augment-environment *environment*
						 :declare decls)))
	(if *toplevel-p*
	    (translate-toplevel-body real-body env *compile-time-too*)
	    (translate-progn-body real-body env *context*
				  nil *result-type*))))))


;;; THE

(deftranslate the (declared-type form)
  (translate-form form *environment* *context*
		  (and-value-types (make-unspecific-number-of-values-type
				    declared-type)
				   *result-type*
				   *environment*)))


;;; COMPILER-LET
;;; *** This is commented out because I can't figure out what package it
;;; *** should be in; it's not in ANSI standard common lisp.
;;; *** The eval should be an evaluation in the translator environment.
;
;(define-toplevel-form compiler-let (bindings &body body)
;  (warn "COMPILER-LET is obsolete.")
;  (multiple-value-bind (names init-forms) (canonicalize-let-bindings bindings)
;    (progv names (mapcar #'eval init-forms)
;      (if *toplevel-p*
;	  (translate-toplevel-body body *environment* *compile-time-too*)
;	  (translate-progn-body body *environment* *context* nil)))))


;;; EVAL-WHEN
;;; The behavior of top-level EVAL-WHENs in the translator differs
;;; from that specified by the ANSI standard.
;;;
;;; The problem is that the translator's macro expansions might include
;;; references to things that cannot be executed in the host Lisp in
;;; compile-time-too situations.  So we just execute the body
;;; immediately using the host Lisp's expansion for any global macro
;;; references, and then re-process the body to pick up the translator's
;;; macro definitions at load time.
;;;
;;; This has two main brokennesses:
;;; (1) There is a potential for subforms of the EVAL-WHEN to be evaluated
;;;     multiple times.
;;; (2) Users might have to wrap some kinds of definitional forms
;;;     (like DEFSETF) in an explicit EVAL-WHEN to make the definitions
;;;     available to both the host Lisp and to the translator.
;;; Caveat emptor?

(define-toplevel-form eval-when (situations &body body)
  (if *toplevel-p*
      (let ((lt  (or (member :load-toplevel situations)
		     (member 'load situations)))
	    (ct  (or (member :compile-toplevel situations)
		     (member 'compile situations)))
	    (ex  (or (member :execute situations)
		     (member 'eval situations))))
	(cond ((and lt (or ct (and ex *compile-time-too*)))
	       (translate-toplevel-body body *environment* t))
	      (lt
	       (translate-toplevel-body body *environment* nil))
	      ((or ct (and ex *compile-time-too*))
	       (eval-in-env `(progn ,@body) *environment*)
	       nil)
	      (t nil)))
      (re-translate-form
	(if (or (member 'eval situations) (member :execute situations))
	    `(progn ,@body)
	    nil))))



;;; DECLARE
;;; Note that declarations are looked for explicitly in all the places
;;; that they are syntactically valid.  Everyplace else, signal a warning.

(define-translator-macro declare (&whole decl)
  (warn "Ignoring misplaced declaration: ~s" decl)
  nil)


;;; LOAD-TIME-VALUE
;;; This one is tricky.  The idea is that we allocate a memory location
;;; (like a C variable) and include the code to initialize it in the
;;; init code for the file.  Here we basically just defer all processing
;;; of the form until the closure/constant analysis phase, and at that
;;; point it is treated just like a constant reference.

(deftranslate load-time-value (form &optional read-only-p)
  (handle-context
   nil
   (make-target-form 'load-time-value form read-only-p nil)
   t nil
   (translator-foreign-type :object)))


;;; QUOTE
;;; Easy, huh?

(deftranslate quote (value)
  (translate-constant value))

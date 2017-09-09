;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; block.lsp -- support for BLOCK, RETURN-FROM
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  26 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/block.lisp,v $"
 "$Revision: 1.5 $"
 "$Date: 2007/07/13 18:16:52 $")

;;; "Simple" cases of BLOCK are handled directly by turning RETURN-FROMs
;;;    into a C GOTO, RETURN, or BREAK statement.  However, if a 
;;;    RETURN-FROM passes control through a function definition or
;;;    catch/unwind-protect body, those transfers of control have to
;;;    be treated like THROWs to a CATCH established by the BLOCK.
;;;    This is the "hard case".
;;; The approach we take is to first walk the BLOCK body assuming 
;;;    all the RETURN-FROMs are simple.  If we find any hard RETURN-FROMs
;;;    at that point, it'll do a throw back.  At that point we do a
;;;    source-to-source to set up the catch and re-walk the block body.

(deftranslate block (name &body body)
  (multiple-value-bind (statements value type temps returns)
      (do-block-simple-case name body nil *context*)
    (declare (ignore returns))
    (values statements value type temps)))


;;; Define an additional entry point for the case of an implicit NIL BLOCK
;;; surrounding an iteration construct.

(defun translate-iteration-block (body)
  (do-block-simple-case nil body t *context*))


;;; Walk the block body in the environment.  Then look at the flags
;;; on the record to see if we have to do anything else.
;;; Note that this function returns four values, not three....

(defun do-block-simple-case (name body break-p context)
  (when (eq *context* ':result-type-only)
    (return-from do-block-simple-case
      (values nil nil '(values &rest t)))) ; not right, but safe
  (multiple-value-bind (env record)
      (bind-block-name name *environment* context)
    (if break-p (setf (block-record-break-p record) t))
    (multiple-value-bind (statements value type temps)
	(catch record (translate-progn-body body env context nil))
      (cond ((eq statements :failure)
	     (do-block-hard-case name body))
	    ((eq statements :needs-temp)
	     ;; There are multiple exits from the block.  Allocate
	     ;; a temporary so that all exits can put the value in the
	     ;; same place, and re-walk the body.
	     (with-temporary-for-value (context returns)
	       (do-block-simple-case name body break-p context)))
	    ((eq statements :needs-values)
	     ;; There is a return that passes through a special binding
	     ;; and the context is :return.  Since :returns through
	     ;; special bindings are not allowed, do a trick like
	     ;; we do in the ordinary special binding code (in
	     ;; binding.lisp) to avoid propagating the :return context.
	     ;; *** Alternatively we might extend the various return
	     ;; *** target language constructs to pop special 
	     ;; *** bindings before returning.
	     (multiple-value-bind (statements value type temps returns)
		 (do-block-simple-case name body break-p :values)
	       (declare (ignore value temps))
	       (values (cons (make-target-form 'return-stored-values)
			     statements)
		       nil type nil returns)))
	    (t
	     ;; It's a simple block.
	     (let ((returns (block-record-returns record)))
	       (when (and returns
			  (not (eq context :return))
			  (not (block-record-break-p record)))
		 (push (make-target-form 'labeled-statement
					 (block-record-label record)
					 (make-target-form 'null-statement))
		       statements))
	       (values statements
		       value
		       (if returns
			   (or-value-types returns type env)
			   type)
		       temps
		       returns)))))))


;;; Until we get this right.
(define-translator-parameter *enable-nonlocal-lexical-jumps-p* t)

(defun do-block-hard-case (name body)
  ;; We found at least one "hard" return-from.
  ;; Wrap the body with a CATCH and re-walk it.
  (let ((temp (make-symbol "TAG-TEMP")))
    (record-variable-containing-compiler-introduced-catch-tag temp)
    (re-translate-form
     `(let ((,temp (trun:%unique-tag ',name)))
	,@(when *enable-nonlocal-lexical-jumps-p*
	    `((declare (tx:closed-variable ,temp))))
	(declare (tx:unwritten-variable ,temp))
	(declare (dynamic-extent ,temp))
	(catch ,temp
	  (hard-block ,name ,temp ,@body))))))

;;; The "hard case" of block is re-translated as a HARD-BLOCK inside of
;;; a CATCH.  "Hard" return-froms inside a hard block translate into
;;; THROWs to that catch.

(deftranslate hard-block (name catch-tag &body body)
  (multiple-value-bind (env record)
      (bind-block-name name *environment* *context*)
    (setf (block-record-hard-p record) catch-tag)
    (multiple-value-bind (statements value type temps)
	(translate-progn-body body env *context* nil)
	  
      ;; This seems unnecessary; return-from inside a hard block 
      ;; always translates
      ;; as a throw, never as a goto, so this label never gets used.	  
      ;;(push (make-target-form 'labeled-statement
      ;;			(block-record-label record)
      ;;			(make-target-form 'null-statement))
      ;;      statements)
	  
      (values statements
	      value
	      (or-value-types (block-record-returns record) type)
	      temps))))



;;; Translate a return-from.

(deftranslate return-from (name &optional value)
  (if (eq *context* ':result-type-only)
      (values nil nil nil nil)
      (translate-return-from-aux (block-binding name *environment*)
				 name value)))

(defun translate-return-from-aux (record name value)
  (cond ((not (hard-tagbody-block-p record *environment*))
	 (do-simple-return-from record value))
	((block-record-hard-p record)
	 (do-hard-return-from record value))
	((block-record-break-p record)
	 (translate-return-from-aux
	  (block-binding name *environment* t)
	  name
	  value))
	(t
	 (throw record :failure))))


;;; If we found a return-from a block that is in a value-returning (as
;;; opposed to side-effecting) context, report failure.
;;; If we found a return-from that passes through special bindings in
;;; a :return context, report failure.

(defun do-simple-return-from (record value)
  (let ((context  (block-record-context record))
	(bindings (tagbody-block-special-bindings record *environment*))
	(catches  (tagbody-block-catch-frames record *environment*)))
    (when (value-context-p context)
      (throw record :needs-temp))
    (when (and (or (plusp bindings) catches) (eq context :return))
      (throw record :needs-values))
    (multiple-value-bind (statements result type temps)
	(translate-form value *environment* context)
      (declare (ignore result))
      (cond ((eq context :return)
	     nil)
	    ((block-record-break-p record)
	     (push (make-target-form 'break-statement bindings catches)
		   statements))
	    (t
	     (push (make-target-form 'goto (block-record-label record)
				     bindings catches)
		   statements)))
      (merge-block-return-types type record)
      (handle-nonreturning-context statements temps))))


;;; Since THROW is nonreturning, it discards the type returned by VALUE,
;;; which we really want to propagate to the block record.  Sigh.

(defun do-hard-return-from (record value)
  (let ((tag  (block-record-hard-p record)))
    (merge-block-return-types t record)
    (re-translate-form `(throw ,tag ,value))))

(defun merge-block-return-types (type record)
  (let ((old-returns  (block-record-returns record)))
    (setf (block-record-returns record)
	  (if old-returns
	      (or-value-types old-returns type *environment*)
	      type))))

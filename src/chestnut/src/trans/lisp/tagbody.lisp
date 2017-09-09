;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; tagbody.lsp -- handling for TAGBODY and GO
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  26 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;; The handling for TAGBODY resembles that for BLOCK but the transformation
;;; for the hard case is a little more complicated.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/tagbody.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/07/13 18:16:53 $")

;;; Walking for TAGBODY follows the same simple-case / hard case division
;;; as for BLOCK.

(deftranslate tagbody (&body tags-and-forms)
  (multiple-value-bind (prolog-forms names named-forms)
      (parse-tagbody tags-and-forms)
    (if (null names)
	(re-translate-form `(progn ,@prolog-forms nil))
	(if (eq *context* ':result-type-only)
	    (values nil nil '(values &rest t))
	    (multiple-value-bind (env record)
		(bind-tagbody-names names *environment*)
	      (multiple-value-bind (statements value type temps)
		  (catch record
		    (do-tagbody-simple-case env prolog-forms
					    named-forms
					    (tagbody-record-labels record)))
		(if (eq statements :failure)
		    (do-tagbody-hard-case prolog-forms
		      named-forms names)
		    (values statements value type temps))))))))

(defun do-tagbody-simple-case (env prolog-forms named-forms labels)
  (let ((statements
	 (translate-progn-body prolog-forms env *ignore-context* nil)))
    (dolist (f named-forms)
      (push (make-target-form
	     'labeled-statement
	     (pop labels)
	     (apply-make-target-form
	      'compound-statement
	      (nreverse (translate-progn-body f env *ignore-context* nil))))
	    statements))
    (handle-context statements (translate-constant-aux 'nil) 'null nil
		    (translator-foreign-type :object))))


;;; The hard TAGBODY case uses two new special forms, WHILE and HARD-TAGBODY,
;;; as helpers.  See below for their definitions.

(defun do-tagbody-hard-case (prolog-forms named-forms names)
  (let* ((tag    (make-symbol "TAGBODY"))
	 (next   (make-symbol "NEXT-CASE")))
    (record-variable-containing-compiler-introduced-catch-tag tag)
    (re-translate-form
     `(let* ((,tag  (trun:%unique-tag 'tagbody))
	     (,next  0))
	(declare (dynamic-extent ,tag))
	,@(when *enable-nonlocal-lexical-jumps-p*
	    `((declare (tx:closed-variable ,tag))))
	(while ,next
	  (setq ,next
		(catch ,tag
		  (hard-tagbody ,tag ,next ,prolog-forms
				,named-forms ,names))))))))


;;; Parse a TAGBODY, returning a list of "prolog forms" at the
;;; head of the body, a list of names, and a list of lists of forms
;;; coming after the names.

(defun parse-tagbody (tags-and-forms)
  (let ((prolog-forms  nil))
    (loop
      (cond ((null tags-and-forms)
	     (return (values (nreverse prolog-forms) nil nil)))
	    ((or (symbolp (car tags-and-forms))
		 (integerp (car tags-and-forms)))
	     (multiple-value-bind (stuff names named-forms)
		 (parse-tagbody (cdr tags-and-forms))
	       (return
		 (values
		   (nreverse prolog-forms)
		   (cons (car tags-and-forms) names)
		   (cons stuff named-forms)))))
	    ((consp (car tags-and-forms))
	     (push (pop tags-and-forms) prolog-forms))
	    (t
	     (warn "Ignoring invalid form in TAGBODY: ~s."
		   (pop tags-and-forms)))))))


;;; Do the GO.

(deftranslate go (name)
  (if (eq *context* ':result-type-only)
      (values nil nil nil nil)
      (translate-go-aux (tagbody-binding name *environment*) name)))

(defun translate-go-aux (record name)
  (cond ((not (hard-tagbody-block-p record *environment*))
	 (do-simple-go name record))
	((tagbody-record-hard-p record)
	 (do-hard-go name record))
	(t
	 (throw record :failure))))

(defun do-simple-go (name record)
  (let ((label     (map-name-to-label name (tagbody-record-names record)
				      (tagbody-record-labels record)))
	(bindings  (tagbody-block-special-bindings record *environment*)))
    (handle-nonreturning-context
     (list (make-target-form 'goto label bindings))
     nil)))

(defun do-hard-go (name record)
  (let ((tag     (tagbody-record-hard-p record))
	(offset  (1+ (position name (tagbody-record-names record)))))
    (re-translate-form `(throw ,tag ,offset))))

(defun map-name-to-label (name names labels)
  (cond ((eql name (car names))
	 (car labels))
	((null names)
	 (error "Internal error in MAP-NAME-TO-LABEL."))
	(t
	 (map-name-to-label name (cdr names) (cdr labels)))))


;;; WHILE iterates over the body until the test-form returns NIL, and then
;;; returns a value of NIL.
;;; It doesn't establish an implicit BLOCK, so there's no support for
;;; break'ing out of the while.

(deftranslate while (test-form &rest body)
  (multiple-value-bind (test-statements test-value test-type test-temps)
      (translate-form test-form *environment* *predicate-context*)
    (declare (ignore test-type))
    (handle-context
     (cons (apply-make-target-form
	    'while-statement
	    (coerce-to-pseudo-boolean test-value)
	    (nreverse (translate-progn-body body *environment*
					    *ignore-context* nil)))
	   test-statements)
     (translate-constant-aux 'nil)
     'null
     test-temps
     (translator-foreign-type :object))))


;;; HARD-TAGBODY expands into a C switch statement with the value of "next"
;;; as its test-expression.  Like TAGBODY, it returns NIL.

;;; ANSI C allows implementations to limit the number of SWITCH cases to
;;; this weird number.  For now we just warn if there is an overflow.

(defconstant max-switch-cases 257)

(deftranslate hard-tagbody (tag next prolog-forms named-forms names)
  (if (> (length names) max-switch-cases)
      (warn "There may be too many case labels in a switch statement."))
  (multiple-value-bind (test-statements test-value test-type test-temps)
      (translate-form next *environment* (translator-foreign-type :int))
    (declare (ignore test-type))
    (multiple-value-bind (env record)
	(bind-tagbody-names names *environment*)
      (let ((body-statements  nil)
	    (count            0)
	    (labels           (tagbody-record-labels record)))
	(setf (tagbody-record-hard-p record) tag)
	(push (make-target-form
	       'labeled-statement 0
	       (apply-make-target-form
		'compound-statement
		(nreverse (translate-progn-body prolog-forms env
						*ignore-context* nil))))
	      body-statements)
	(dolist (f named-forms)
	  (push (make-target-form
		 'labeled-statement
		 (pop labels)
		 (make-target-form
		  'labeled-statement
		  (incf count)
		  (apply-make-target-form
		   'compound-statement
		   (nreverse (translate-progn-body f env
						   *ignore-context* nil)))))
		body-statements))
	(handle-context
	 (cons (make-target-form
		'switch
		test-value
		(apply-make-target-form
		 'compound-statement
		 (nreverse body-statements)))
	       test-statements)
	 (translate-constant-aux 'nil)
	 'null
	 test-temps
	 (translator-foreign-type :object))))))


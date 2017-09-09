;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; pattern.lsp -- pattern matching transformation drivers
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  14 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/pattern.lisp,v $"
			 "$Revision: 1.2 $"
			 "$Date: 2007/05/22 20:18:36 $")

;;; Define the patterns.  These are tested in the same order in which
;;;    they are defined, so you should put the most specific transformations
;;;    at the head of the list.
;;; Each pattern is a list of the form (logical-vars source target).
;;; DEFTRANSFORM expands into a compiler-macro definition.
;;; *** Maybe DEFTRANSFORM ought to be exported and documented?

(defmacro deftransform (name &rest patterns)
    `(define-translator-compiler-macro ,name (&whole form)
	 (apply-transformations form ',patterns)))


;;; Here is the function that actually applies the patterns defined via
;;;    DEFTRANSFORM.  It compares the "source" from the pattern to the
;;;    argument form, binding the "logical-vars" to corresponding pieces
;;;    of the argument form.  If everything matches, it plugs the
;;;    bindings into the "target" and returns the new form.  Otherwise
;;;    it returns the original form.
;;; As extra features, there are two additional hacks:
;;;    - match-key syntax for matching keyword arguments
;;;    - any leftover logical variables get bound to gensyms.

(defun apply-transformations (form pattern-list)
    (let ((bindings     nil))
	(dolist (pattern pattern-list form)
	    (when (setq bindings
			(match-pattern (first pattern) (second pattern)
				       form '((t . t))))
		(dolist (var (first pattern))
		    (if (not (assoc var bindings))
			(push (cons var (gensym)) bindings)))
		(return (replace-pattern (third pattern) bindings))))))

(defparameter apply-transformations
  '((($a)
     (apply #'list $a)
     (values $a))
    (($a)
     (apply 'list $a)
     (values $a))
    (($a $b)
     (apply $a $b)
     (trun:%apply-1 $a $b))
    (($a $b $c)
     (apply $a $b $c)
     (trun:%apply-2 $a $b $c))
    (($a $b $c $d)
     (apply $a $b $c $d)
     (trun:%apply-3 $a $b $c $d))
    (($a $b $c $d $e)
     (apply $a $b $c $d $e)
     (trun:%apply-4 $a $b $c $d $e))
    (($a $b $c $d $e $f)
     (apply $a $b $c $d $e $f)
     (trun:%apply-5 $a $b $c $d $e $f))
    ))

;;; Do the pattern-matching part.  If the "source" names a logical
;;;    variable, it had either better be a new binding or match a
;;;    previously made binding.  Return the list of bindings or NIL
;;;    if the pattern doesn't match.

(defun match-pattern (logical-vars source form bindings)
  (cond ((consp source)
	 (cond ((eq (car source) 'match-keys)
		(match-keys logical-vars (cdr source) form bindings))
	       ((and (consp form)
		     (setq bindings
			   (match-pattern logical-vars (car source)
					  (car form) bindings)))
		(match-pattern logical-vars (cdr source)
			       (cdr form) bindings))
	       (t nil)))
	((member source logical-vars)
	 (let ((binding  (assoc source bindings)))
	   (cond ((null binding)
		  (push (cons source form) bindings))
		 ((eql form (cdr binding))
		  bindings)
		 (t
		  nil))))
	((eql source form)
	 bindings)
	(t nil)))


;;; As a special case, a subform in a source pattern can look like
;;;    (match-keys (key pattern default) (key pattern default) ...).  This 
;;;    will match a list that contains any or all of the provided keywords
;;;    and none that aren't in the list.  This can't be done handily without
;;;    this kind of special handling, because when multiple keywords
;;;    are supplied there are just too many permutations to provide
;;;    an explicit pattern for each one.  Anyway, what happens is that
;;;    if the key appears in form-keylist, the pattern for that key is
;;;    matched against the corresponding actual argument form.  Otherwise
;;;    it is matched against the specified default.
;;; Note that this is primarily intended for matching against constant
;;;    keyword values that don't appear at all in the replacement pattern.
;;;    There are obviously problems with order-of-evaluation.

(defun match-keys (logical-vars pattern-keylist form-keylist bindings)
  (dolist (entry pattern-keylist (if form-keylist nil bindings))
    (multiple-value-bind (argument remaining)
	(look-for-key (first entry) form-keylist (third entry))
      (unless (setq bindings
		    (match-pattern logical-vars (second entry)
				   argument bindings))
	(return nil))
      (setq form-keylist remaining))))

(defun look-for-key (key form-keylist default)
  (let ((others nil))
    (loop
      (cond ((null form-keylist)
	     (values default (nreverse others)))
	    ((null (cdr form-keylist))  ; ill-formed keylist
	     (values default (nreverse others)))
	    ((eq key (car form-keylist))
	     (values (cadr form-keylist)
		     (nconc (nreverse others) (cddr form-keylist))))
	    (t
	     (push (pop form-keylist) others)
	     (push (pop form-keylist) others))))))


;;; Do the logical variable substitution on the result.

(defun replace-pattern (target bindings)
  (let ((temp  nil))
    (cond ((consp target)
	   (cons (replace-pattern (car target) bindings)
		 (replace-pattern (cdr target) bindings)))
	  ((setq temp (assoc target bindings))
	   (cdr temp))
	  (t target))))


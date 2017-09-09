;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Canonic initarg lists
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/canonic-initargs.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:01 $")

;;; Canonic initarg lists are used in the parsing of the CLOS user interface
;;; macros (DEFCLASS, DEFGENERIC, &etc).  They are based on an abstraction
;;; called a forms-plist.  A forms-plist is not a plist.  Rather, if X is a
;;; forms-plist, then (MAPCAR #'EVAL X) is a plist (up to issues of getting the
;;; lexical environment for the evaluation correct).  Another way of saying
;;; this is that if X is a forms-plist then evaluation of `(LIST . ,X) is a
;;; plist.
;;;
;;; The key entries in a canonic initarg list must all be QUOTE forms, with the
;;; value being a symbol.  The value entries are determined by the particular
;;; context and key.  The matching of properties uses EQ on the symbols.
;;;
;;; The following functions are provided by this package:
;;;  CGETF -- This corresponds to GETF.  It may be used as a place for SETF. 
;;;  CREMF -- This corresponds to REMF.

(defun cgetf-match-p (key-form property)
  (if (or (not (consp key-form))
	  (not (eq (car key-form) 'quote)))
      (error "Ill-formed key in canonic initarg list: ~S." key-form)
      (eql (cadr key-form) property)))

(defun invalid-canonic-initargs-error (canonic)
  (error "Ill-formed canonic initarg list: ~S." canonic))

;;; CGETF -- Canonic GETF
;;;
;;; canonic -- a forms-plist
;;; property -- a symbol
;;; default -- a Lisp object
;;;
;;; Returns the form associated with the property in the forms-plist, or the
;;; default value if no matching key form is present.  A second value is
;;; returned which is true if a match was found and false otherwise.
;;;
;;; This function roughly corresponds to GETF, but for forms-plists.

(defun cgetf (canonic property &optional default)
  (do ((plist canonic (cddr plist)))
      ((endp plist) (values default nil))
    (cond ((atom (cdr plist))
	   (invalid-canonic-initargs-error canonic))
	  ((cgetf-match-p (car plist) property)
	   (return (values (cadr plist) t))))))

;;; SETF of CGETF
;;; REPLACE-CGETF
;;;
;;; canonic -- a forms-plist
;;; property -- a symbol
;;; value -- a Lisp object
;;;
;;; Returns a new forms-plist in which the value for the property is the
;;; specified form.  New key/value pairs are added to the end of the
;;; forms-plist (as if by NCONC), ensuring that pairs appear in the order in
;;; which they were added.

(defun replace-cgetf (canonic property value)
  (do* ((head nil (cdr plist))
	(plist canonic (cdr head)))
       ((endp plist)
	;; If no match, add property and value to the end.
	(let ((tail (list `(quote ,property) value)))
	  (if (null head) tail
	      (progn
		(setf (cdr head) tail)
		canonic))))
    (cond ((atom (cdr plist))
	   (invalid-canonic-initargs-error canonic))
	  ((cgetf-match-p (car plist) property)
	   (setf (cadr plist) value)
	   (return canonic)))))

;;; Allegro doesn't support &environment keyword to define-setf-method.

(define-setf-method cgetf
    #-allegro (place key &optional default &environment env)
    #+allegro (place key &optional default)
  (multiple-value-bind (vars vals stores setter getter)
      (get-setf-method-multiple-value place #-allegro env)
    (let ((key-var (gensym))
	  (def-var (gensym))
	  (store (gensym)))
      (values (append vars (list key-var def-var))
	      (append vals (list key default))
	      (list store)
	      `(multiple-value-bind ,stores ,getter
		 ,def-var
		 (setf ,(car stores)
		       (replace-cgetf ,(car stores) ,key-var ,store))
		 ,setter
		 ,store)
	      `(cgetf ,getter ,key-var ,def-var)))))

;;; CREMF -- Canonic REMF
;;;
;;; place -- a forms-plist
;;; property -- a symbol
;;;
;;; This removes from the forms-plist stored in place the matching property.
;;; The property is removed by destructively splicing the forms-plist.  It
;;; returns true if a matching property was found, and false otherwise.
;;;
;;; This function roughly corresponds to REMF, but for forms-plists.

(defun cremf-internal (canonic property)
  (do* ((head nil (cdr plist))
	(plist canonic (cdr head)))
       ((endp plist) (values canonic nil))
    (cond ((atom (cdr plist))
	   (invalid-canonic-initargs-error canonic))
	  ((cgetf-match-p (car plist) property)
	   (if (null head)
	       (return (values (cddr canonic) t))
	       (progn
		 (setf (cdr head) (cddr plist))
		 (return (values canonic t))))))))

(defmacro cremf (place key &environment env)
  (multiple-value-bind (vars vals stores setter getter)
      (get-setf-method-multiple-value place env)
    (let ((temp (gensym)))
      `(let* (,.(mapcar #'list vars vals)
	      ;; For consistency with *&^* X3J13 RMW decision
	      (,temp ,key))
	 (multiple-value-bind ,stores ,getter
	   (multiple-value-setq (,(car stores) ,temp)
	     (cremf-internal ,(car stores) ,temp))
	   ,setter
	   ,temp)))))

;;; Filtering canonic initarg lists.
;;;
;;; Initarg lists are filtered to remove defaults and values which are not
;;; needed at runtime (generally as determined by certain compile-time options
;;; specified by the user).

(defvar *canonic-initarg-filters* (make-hash-table :test 'eq))

(defun get-filter-table (filter-name)
  (or (gethash filter-name *canonic-initarg-filters*)
      (error "Undefined initarg filter table: ~S." filter-name)))

(defun filter-initargs (filter-name initargs env)
  (setf initargs (copy-list initargs))
  (maphash #'(lambda (key filter)
	       (declare (ignore key))
	       (setf initargs (funcall filter initargs env)))
	   (get-filter-table filter-name))
  initargs)

(defmacro define-canonic-filter-table (name)
  `(setf (gethash ',name *canonic-initarg-filters*)
         (make-hash-table :test 'eq)))

(defmacro define-canonic-filter ((key table) lambda-list &body body)
  (multiple-value-bind (body declspecs) (parse-body body)
    `(setf (gethash ',key (get-filter-table ',table))
           #'(lambda ,lambda-list
	       (declare ,@declspecs)
	       (block ,key ,@body)))))

;;; Helper function for frequently performed operation when filtering initargs.
(defun resolve-constant-initarg (initarg initargs env)
  (multiple-value-bind (value therep)
      (cgetf initargs initarg)
    (if (not therep)
	(values nil nil nil)
	(multiple-value-bind (value therep constantp)
	    (translator-constant-value value env)
	  (declare (ignore constantp))
	  (values value therep t)))))

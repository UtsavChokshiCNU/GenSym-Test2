;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Random utility functions.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/clos-util.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:01 $")

(defun find-keyword (keylist keyword &optional (required nil))
  ;; Because ANSI says consequences are undefined if GETF used on list with
  ;; multiple entries for same key, can't use the following code reliably.
  ;; (let* ((default *find-keyword-default*)
  ;;        (value (getf keylist keyword default)))
  ;;   (cond ((not (eq default value)) value)
  ;;         ((not required) nil)
  ;;         (t (error "The keyword ~S is not present in ~S."
  ;;                   keyword keylist))))
  (flet ((odd-length-error (keylist)
	   (error "Keyword list has odd length: ~S." keylist)))
    (do ((keys keylist (cdr keys)))
	((endp keys)
	 (when required
	   (error "The keyword ~S is not present in ~S."
		  keyword keylist)))
      (cond ((eq (pop keys) keyword)
	     (return (if (endp keys)
			 (odd-length-error keylist)
			 (pop keys))))
	    ((endp keys) (odd-length-error keylist))))))

;;; Remove all occurances of the specified keys from the keylist.
;;; This function is not destructive.  The result may share cells with the
;;; keylist argument.
(defun strip-keylist (keylist &rest keys)
  (labels ((strip (tail keys)
	     (do ((head tail))
		 ((endp tail) head)
	       (let ((key (car tail)))
		 (if (member key keys :test #'eq)
		     (return (nconc (ldiff head tail)
				    (strip (cddr tail) keys)))
		     (setf tail (cddr tail)))))))
    (strip keylist keys)))

;;; Destructive version of strip-keylist.
(defun nstrip-keylist (keylist &rest keys)
  (labels ((strip (tail keys)
	     (do ((head tail)
		  (prev nil))
		 ((endp tail) head)
	       (let ((key (car tail)))
		 (if (not (member key keys :test #'eq))
		     (shiftf prev tail (cddr tail))
		     (progn
		       (setf tail (cddr tail))
		       (if (null prev)
			   (setf head tail)
			   (setf (cddr prev) tail))))))))
    (strip keylist keys)))

(defun make-name* (format-string format-arguments)
  (make-symbol (format nil "~?" format-string format-arguments)))

(defun make-name (format-string &rest format-arguments)
  (make-name* format-string format-arguments))

(defun make-variable (format-string &rest format-arguments)
  (make-name* format-string format-arguments))

;;; Parse a lambda-list into canonicalized components, returing the components
;;; as seperate values.  This function returns 7 values, which are:
;;;
;;;  * REQUIRED	A list of the required variables.
;;;
;;;  * OPTIONAL	A list of the optional parameters.  The format for entries in
;;;		this list is (variable initform [ suppliedp-var ]).
;;;
;;;  * REST	The &rest variable (if present) or Nil.
;;;
;;;  * KEYP	A boolean value which is true iff &key was present in the
;;;		lambda-list.
;;;
;;;  * KEYS	A list of the keyword parameters.  The format for entries in
;;;		this list is ((key variable) initform [ suppliedp-var ]).
;;;
;;;  * ALLOW-OTHER-KEYS
;;;		A boolean value which is true iff &allow-other-keys was present
;;;		in the lambda-list.
;;;
;;;  * AUX	A list of the auxiliary parameters.  The format for entries in
;;;		this list is (variable initform).

(defun parse-lambda-list-into-components (lambda-list)
  (let ((required ())
	(optional ())
	(rest nil)
	(keyp nil)
	(keys ())
	(allow-other-keys nil)
	(aux ()))
    (parse-lambda-list lambda-list
      :required #'(lambda (var)
		    (push var required))
      :optional #'(lambda (var init initp svar svar-p)
		    (declare (ignore initp))
		    (push (list* var init (when svar-p (list svar))) optional))
      :rest #'(lambda (var)
		(setf rest var))
      :keyp #'(lambda ()
		(setf keyp t))
      :key #'(lambda (var key init initp svar svar-p)
	       (declare (ignore initp))
	       (push `((,key ,var) ,init ,@(when svar-p (list svar))) keys))
      :allow-other-keys-p #'(lambda ()
			      (setf allow-other-keys t))
      :aux #'(lambda (var init initp)
	       (declare (ignore initp))
	       (push (list var init) aux)))
    (values (nreverse required)
	    (nreverse optional)
	    rest
	    keyp
	    (nreverse keys)
	    allow-other-keys
	    (nreverse aux))))


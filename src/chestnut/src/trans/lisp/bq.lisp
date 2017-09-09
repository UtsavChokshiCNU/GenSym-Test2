;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; bq -- backquote implementation from CLtL 2nd edition Appendix C
;;;       (pp. 960-967)
;;;
;;; Modified by : John Gilson
;;;
;;; Copyright (c) 1990, Chestnut Software, Inc.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/bq.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:00 $")

(defvar *comma* 'trun:comma)
(defvar *comma-atsign* 'trun:comma-atsign)
(defvar *comma-dot* 'trun:comma-dot)
(defvar *bq-list* (make-symbol "BQ-LIST"))
(defvar *bq-append* (make-symbol "BQ-APPEND"))
(defvar *bq-list** (make-symbol "BQ-LIST*"))
(defvar *bq-nconc* (make-symbol "BQ-NCONC"))
(defvar *bq-clobberable* (make-symbol "BQ-CLOBBERABLE"))
(defvar *bq-quote* (make-symbol "BQ-QUOTE"))
(defvar *bq-quote-nil* (list *bq-quote* nil))

#|
(setf (macro-function *comma*)
      #'(lambda (macro-call env)
	  (declare (ignore macro-call env))
	  (error "A comma appears outside of the scope of a backquote")))

(setf (macro-function *comma-atsign*)
      #'(lambda (macro-call env)
	  (declare (ignore macro-call env))
	  (error "A ,@ appears outside of the scope of a backquote")))

(setf (macro-function *comma-dot*)
      #'(lambda (macro-call env)
	  (declare (ignore macro-call env))
	  (error "A ,. appears outside of the scope of a backquote")))
|#

(defun bq-completely-process (x)
  (bq-remove-tokens (bq-simplify (bq-process x))))

(defun bq-process (x)
  (cond ((atom x)
	 (list *bq-quote* x))
	((eq (car x) 'trun::backquote) ; handle nested backquotes
	 (bq-process (bq-completely-process (cadr x))))
	((eq (car x) *comma-atsign*)
	 (error ",@~S after `" (cadr x)))
	((eq (car x) *comma-dot*)
	 (error ",.~S after `" (cadr x)))
	(t (do ((q '() (cons (bracket (car p)) q))
		(p x (cdr p)))
	       ((atom p)
		(cons *bq-append*
		      (nreconc q (list (list *bq-quote* p)))))
	     (when (eq (car p) *comma*)
	       (unless (null (cddr p)) (error "Malformed ,~S" p))
	       (return (cons *bq-append*
			     (nreconc q (list (cadr p))))))
	     (when (eq (car p) *comma-atsign*)
	       (error "Dotted ,@~S" p))
	     (when (eq (car p) *comma-dot*)
	       (error "Dotted ,.~S" p))))))

(defun bracket (x)
  (cond ((atom x)
	 (list *bq-list* (bq-process x)))
	((eq (car x) *comma*)
	 (list *bq-list* (cadr x)))
	((eq (car x) *comma-atsign*)
	 (cadr x))
	((eq (car x) *comma-dot*)
	 (list *bq-clobberable* (cadr x)))
	(t (list *bq-list* (bq-process x)))))

(defun maptree (fn x)
  (if (atom x)
      (funcall fn x)
    (let ((a (funcall fn (car x)))
	  (d (maptree fn (cdr x))))
      (if (and (eql a (car x)) (eql d (cdr x)))
	  x
	(cons a d)))))

(defun bq-splicing-frob (x)
  (and (consp x)
       (or (eq (car x) *comma-atsign*)
	   (eq (car x) *comma-dot*))))

(defun bq-frob (x)
  (and (consp x)
       (or (eq (car x) *comma*)
	   (eq (car x) *comma-atsign*)
	   (eq (car x) *comma-dot*))))

(defun bq-simplify (x)
  (if (atom x)
      x
    (let ((x (if (eq (car x) *bq-quote*)
		 x
	       (maptree #'bq-simplify x))))
      (if (not (eq (car x) *bq-append*))
	  x
	(bq-simplify-args x)))))

(defun bq-simplify-args (x)
  (do ((result
	 nil
	 (cond ((atom (car args))
		(bq-attach-append *bq-append* (car args) result))
	       ((and (eq (caar args) *bq-list*)
		     (notany #'bq-splicing-frob (cdar args)))
		(bq-attach-conses (cdar args) result))
	       ((and (eq (caar args) *bq-list**)
		     (notany #'bq-splicing-frob (cdar args)))
		(bq-attach-conses
		  (reverse (cdr (reverse (cdar args))))
		  (bq-attach-append *bq-append*
				    (car (last (car args)))
				    result)))
	       ((and (eq (caar args) *bq-quote*)
		     (consp (cadar args))
		     (not (bq-frob (cadar args)))
		     (null (cddar args)))
		(bq-attach-conses (list (list *bq-quote*
					      (caadar args)))
				  result))
	       ((eq (caar args) *bq-clobberable*)
		(bq-attach-append *bq-nconc* (cadar args) result))
	       (t (bq-attach-append *bq-append*
				    (car args)
				    result))))
       (args (reverse (cdr x)) (cdr args)))
      ((null args) result)))

(defun null-or-quoted (x)
  (and (or (null x) (and (consp x) (eq (car x) *bq-quote*)))))

(defun bq-attach-append (op item result)
  (cond ((or (null result) (equal result *bq-quote-nil*))
	 (if (bq-splicing-frob item) (list op item) item))
	((and (null-or-quoted item) (null-or-quoted result))
	 (list *bq-quote* (append (cadr item) (cadr result))))
	((and (consp result) (eq (car result) op))
	 (list* (car result) item (cdr result)))
	(t (list op item result))))

(defun bq-attach-conses (items result)
  (cond ((and (every #'null-or-quoted items)
	      (null-or-quoted result))
	 (list *bq-quote*
	       (append (mapcar #'cadr items) (cadr result))))
	((or (null result) (equal result *bq-quote-nil*))
	 (cons *bq-list* items))
	((and (consp result)
	      (or (eq (car result) *bq-list*)
		  (eq (car result) *bq-list**)))
	 (cons (car result) (append items (cdr result))))
	(t (cons *bq-list** (append items (list result))))))

(defun bq-remove-tokens (x)
  (cond ((eq x *bq-list*) 'list)
	((eq x *bq-append*) 'append)
	((eq x *bq-nconc*) 'nconc)
	((eq x *bq-list**) 'list*)
	((eq x *bq-quote*) 'quote)
	((atom x) x)
	((eq (car x) *bq-clobberable*)
	 (bq-remove-tokens (cadr x)))
	((and (eq (car x) *bq-list**)
	      (consp (cddr x))
	      (null (cdddr x)))
	 (cons 'cons (maptree #'bq-remove-tokens (cdr x))))
	(t (maptree #'bq-remove-tokens x))))


(defmacro trun::backquote (x)
  (bq-completely-process x))

(define-translator-macro trun::backquote (x)
  (bq-completely-process x))

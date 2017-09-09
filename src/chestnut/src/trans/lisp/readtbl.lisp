;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; readtbl -- set up translator readtable
;;;
;;; Author : John Gilson
;;;
;;; Copyright (c) 1990, Chestnut Software, Inc.

(in-package "TIMPL")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/readtbl.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:10 $")

#|

Backquote and comma

(set-macro-character #\`
  #'(lambda (stream char)
      (declare (ignore char))
      (list 'backquote (read stream t nil t)))
  nil
  *translator-readtable*)

(set-macro-character #\,
  #'(lambda (stream char)
      (declare (ignore char))
      (case (peek-char nil stream t nil t)
	(#\@ (read-char stream t nil t)
	     (list *comma-atsign* (read stream t nil t)))
	(#\. (read-char stream t nil t)
	     (list *comma-dot* (read stream t nil t)))
	(otherwise (list *comma* (read stream t nil t)))))
  nil
  *translator-readtable*)

|#

;;; Backquote and comma

(let ((backquote-depth 0)
      (comma-depth 0))
  (set-macro-character #\`
    #'(lambda (stream char)
	(declare (ignore char))
	(let ((old-backquote-depth backquote-depth))
	  (incf backquote-depth)
	  (unwind-protect
	    (prog1
	      (list 'trun:backquote (read stream t nil t))
	      (decf backquote-depth))
	    (unless (eq backquote-depth old-backquote-depth)
	      (setf backquote-depth 0
		    comma-depth 0)))))
    nil
    *translator-readtable*)
  (set-macro-character #\,
    #'(lambda (stream char)
	(declare (ignore char))
	(let ((old-comma-depth comma-depth))
	  (incf comma-depth)
	  (unwind-protect
	    (prog2
	      (when (> comma-depth backquote-depth)
		(error "A comma is not within the scope of a backquote"))
	      (case (peek-char nil stream t nil t)
		(#\@ (read-char stream t nil t)
		     (list 'trun:comma-atsign (read stream t nil t)))
		(#\. (read-char stream t nil t)
		     (list 'trun:comma-dot (read stream t nil t)))
		(otherwise (list 'trun:comma (read stream t nil t))))
	      (decf comma-depth))
	    (unless (eq comma-depth old-comma-depth)
	      (setf backquote-depth 0
		    comma-depth 0)))))
    nil
    *translator-readtable*))

;;; sharp-comma

#-translating
(set-dispatch-macro-character #\# #\,
  #'(lambda (stream subchar arg)
      (declare (ignore stream subchar arg))
      (error "The translator does not support #,"))
  *translator-readtable*)

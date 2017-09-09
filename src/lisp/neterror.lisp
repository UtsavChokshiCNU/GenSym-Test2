;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; ***************************************************************************
;;;; Module NETERROR
;;;;    New error-message system used in ICP 5.0.
;;;;      Note that this system is general enough that it might be used
;;;;     throughout G2.  Does not signal or use any method of nonlocal return;
;;;;     this must be done by the client.
;;;; ***************************************************************************

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author: Nicholas C. Caruso

;
;;;; Structure declarations

(def-structure (error-code
		 (:constructor
		   make-error-code
		   (error-severity
		     error-format-string)))
  error-format-string
  error-severity)

;
;;;; Local constants and parameters

;;; error severities

;;; success, informational, warning, fatal

(eval-when (:compile-toplevel :load-toplevel :execute)

  (defparameter error-severity-success 0)
  (defparameter error-severity-informational 1)
  (defparameter error-severity-warning 2)
  (defparameter error-severity-fatal 3))


;
;;;; macros

(defmacro def-error-message-table ((facility-name &key (code-offset 0))
				       &rest error-declarations)
  (let* ((error-table-symbol (intern (concatenate 'string (symbol-name facility-name) "-ERROR-TABLE")))
	 (error-message-string-lookup-macro
	   (intern (concatenate 'string (symbol-name facility-name) "-ERROR-FORMAT-STRING")))
	 (error-message-severity-lookup-macro
	   (intern (concatenate 'string (symbol-name facility-name) "-ERROR-SEVERITY"))))
    
    `(progn
      (defparameter ,error-table-symbol
	(make-array ,(length error-declarations)))
      
      (defmacro  ,error-message-string-lookup-macro (error-code)
	(let ((table ,error-table-symbol))
	  `(error-format-string (svref ,table ,error-code))))

      (defmacro  ,error-message-severity-lookup-macro (error-code)
	(let ((table ,error-table-symbol))
	  `(error-severity (svref ,table ,error-code))))
      
      ;; define & associate error-code symbols & numbers: 
      ,@(loop for i from code-offset to (length error-declarations)
	      as declaration in error-declarations
	      append `((defparameter
			   ,(intern
			      (concatenate 'string (symbol-name facility-name) "-"
					   (symbol-name (first declaration))))
			 ,i)
		       (setf (svref ,error-table-symbol ,i)
			(make-error-code ,(second declaration) ,(third declaration))))))))


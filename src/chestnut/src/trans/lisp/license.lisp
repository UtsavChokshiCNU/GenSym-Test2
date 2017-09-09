;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; license.lisp -- Defining the license message
;;;
;;; Author :  Bill Brodie
;;; Date   :  26 Sep 1991
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/license.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2007/11/14 22:02:54 $")

;;; When compiled without (member :internal-use *features*), this
;;; file creates a run-time definition of a function called
;;; DISPLAY-LICENSE-MESSAGE; the actual contents of the function
;;; are determined by your responses to prompts generated at
;;; compile time.  Before completing the compile, the file verifies
;;; your choices by displaying the license message.  At run time,
;;; the license message is displayed at the end of the Translator
;;; initialization sequence.

;;; A similar behavior is exhibited if you load this file as source.

;;; The point of doing things this way, rather than simply
;;; placing global variables in the file and having a common
;;; function to print them, is to make it a little harder
;;; for users to "patch" portions of the license message;
;;; this way they have to find and redefine the entire function.

(eval-when (compile eval #+internal-use load)

(defvar *license-directory* "/home/rh/releases/licenses/")
(defvar *clos-license-directory* "/u/projects/lisp-to-c/trans/clos-licenses/")

(defvar *translator-customer* nil)

(defvar *internal-use-license-binary*)

(defun get-customer-name ()
  (declare (special *translator-customer*))
  (or *translator-customer*
      (progn
	(format t "~&Enter the customer name ~
                     (this will be the name of a file in ~%~S),~@
                     or type <return> for the internal-use license: "
		*license-directory*)
	(let ((name (read-line)))
	  (if (equal name "")
	      nil
	      name)))))

(defun get-license-info ()
  (loop (with-simple-restart (retry "Retry getting the customer ~
                                     license information.")
	  (multiple-value-bind (name license-type serial-number
				     machine-serial-number)
	      (catch 'license-info
		(load (make-pathname :defaults *license-directory*
				     :name "licenses"
				     :type "lisp")))
	    ;; license-type codes:
	    ;;    1 - Single user
	    ;;    2 - Project team
	    ;;    3 - Departmental
	    ;;    4 - Developer's Edition
	    (when (and (eql license-type 4) (null machine-serial-number))
	      (error "The Developer's Edition license requires ~
                      a machine serial number"))
	    (return-from get-license-info
	      (values name license-type serial-number
		      machine-serial-number))))))

;; Call this to make a new license binary file.
(defun compile-license (&optional (customer (get-customer-name)))
  (declare (special *translator-customer*))
  (setq *internal-use-license-binary*
	(make-pathname :defaults himpl::*translator-binary-directory*
		       :name "license"
		       :type himpl::*translator-binary-type*))
  (if (null customer)
      *internal-use-license-binary*
      (let ((*translator-customer* customer)
	    (*features* (remove ':internal-use *features*))
	    (source (make-pathname :defaults
				   himpl::*translator-source-directory*
				   :name "license"
				   :type "lisp"))
	    (binary (make-pathname :defaults
				   #-translator-supports-clos
				   *license-directory*
				   #+translator-supports-clos
				   *clos-license-directory*
				   :name (string-downcase customer)
				   :type himpl::*translator-binary-type*)))
	(unless (and (probe-file binary)
		     (<= (file-write-date source) (file-write-date binary)))
	  (compile-file source :output-file binary))
	binary)))
)

(in-package #-(or SBCL MCL clozure Genera) "USER"
	    #+(or SBCL MCL clozure Genera) "CL-USER")

#+(and lucid internal-use)
(progn

(defmacro with-customer-license-file ((customer customer-p) &body forms)
  `(let* ((new-license (if ,customer-p
			   (timpl::compile-license ,customer)
			   (timpl::compile-license)))
	  (old-license timpl::*internal-use-license-binary*)
	  (save-license (make-pathname :defaults old-license
				       :name "license-save"))
	  (rename-p (not (equalp new-license old-license))))
     (when rename-p
       (when (or (probe-file save-license)
		 (not (and (probe-file old-license)
			   (probe-file new-license))))
	 (error "something is wrong"))
       (rename-file old-license save-license)
       (rename-file new-license old-license))
     (unwind-protect
	  (progn ,@forms)
       (when rename-p
	 (rename-file old-license new-license)
	 (rename-file save-license old-license)))))
     
(defun make-load-file (&key (clos-p (member :translator-supports-clos
					    *features*))
			    (initial-file-p nil)
			    (include-patches-p t)
			    (customer nil customer-p)
			    (print nil))
  (with-customer-license-file (customer customer-p)
    (let* ((*default-pathname-defaults* himpl::*translator-directory*)
	   (output (merge-pathnames
		    (make-pathname :name (if clos-p "clos-trans" "trans")
				   :type *translator-binary-type*)))
	   (initial-files (nconc (when initial-file-p
				   (list (if clos-p
					     "make-clos-trans"
					     "make-trans")))
				 '(#-MCL "host-implementation-package"
				   #+MCL "host-implementation-pkg"
				   "host-implementation"
				   "module"
				   "translator")))
	   (trans-files (nconc (let ((*record-files-to-load-p* t)
				     (*all-files-to-load* nil))
				 (apply #'load-translator-files initial-files)
				 (nreverse *all-files-to-load*))
			       (progn
				 (himpl::reset-load-times :translator)
				 (himpl::module-load-files :translator))))
	   (cwd (lcl:pwd)))
      (when include-patches-p
	(let ((last (last trans-files))
	      (pl (merge-pathnames "patch-list.lisp"))
	      (*record-files-to-load-p* t)
	      (*all-files-to-load* nil)
	      (himpl::*loaded-patches* nil))
	  (himpl::load-patches)
	  (with-open-file (out pl
			       :direction :output
			       :if-exists :supersede)
	    (format out "(in-package :himpl)~%")
	    (format out "(setq *loaded-patches* '~S)~%"
		    himpl::*loaded-patches*))
	  (setq trans-files (nconc (ldiff trans-files last)
				   (nreverse *all-files-to-load*)
				   (cons (compile-file pl)
					 last)))))
      (when (probe-file output)
	(delete-file output))
      (when print (pprint trans-files))
      (lcl:cd himpl::*translator-directory*)
      (lcl:run-program "cat"
		       :arguments (mapcar #'enough-namestring trans-files)
		       :output output)
      (lcl:cd cwd)
      output)))

)

(in-package "TIMPL")

(eval-when (compile eval)

(defun license-definition ()
  (multiple-value-bind (customer-name license-type serial-number
				      machine-serial-number)
      #+internal-use (values nil nil nil nil)
      #-internal-use (get-license-info)
      (unless customer-name
	(return-from license-definition
	  `(defun display-license-message ()
	     (format t
		     "~%Lisp-to-C Translator (TM)~
                  ~%    Version ~A
                  ~%    Copyright (c) 1986 - 2017 Gensym Corporation.~
                  ~%    Copyright (C) 1991, 1992, 1993 Chestnut Software, Inc.~
                  ~%    Proprietary material of Chestnut Software Inc.~
                  ~%    Internal use only.~%"
		     (himpl:translator-version t)))))
      `(defun display-license-message ()
	 ;;#-(and :gclisp (not :common-lisp)) (format t "~|")
	 #+(and :gclisp (not :common-lisp)) (send *terminal-io* :clear-screen)

       (format t "
            Lisp-to-C Translator (TM)

    Copyright (c) 1986 - 2017 Gensym Corporation.
    Copyright (C) 1991, 1992, 1993 Chestnut Software, Inc.

    Version ~A

    Proprietary material of Chestnut Software Inc.~%"
	       (himpl:translator-version))
       (format t
	       ,(ecase license-type
		  (1
		   "
  USE OF THIS SOFTWARE IS GOVERNED BY CHESTNUT'S 
  INDIVIDUAL USER LICENSE.  USE IS RESTRICTED TO A
  PARTICULAR COMPUTER AND TERMINAL.")
		  (2
		   "
  USE OF THIS SOFTWARE IS GOVERNED BY CHESTNUT'S 
  PROJECT TEAM LICENSE.  USE IS RESTRICTED TO A
  PARTICULAR SMALL ORGANIZATIONAL GROUP, AND THE NUMBER
  OF COMPUTERS AND TERMINALS WITH WHICH THIS SOFTWARE
  MAY BE USED IS LIMITED BY THE LICENSE.")
		  (3
		   "
  USE OF THIS SOFTWARE IS GOVERNED BY CHESTNUT'S 
  DEPARTMENTAL LICENSE.  USE IS RESTRICTED TO A
  PARTICULAR DEPARTMENT, AND THE NUMBER OF COMPUTERS
  AND TERMINALS WITH WHICH THIS SOFTWARE
  MAY BE USED IS LIMITED BY THE LICENSE.")
		  (4
		   "
  USE OF THIS SOFTWARE IS GOVERNED BY CHESTNUT'S 
  DEVELOPER'S EDITION USER LICENSE.  USE IS RESTRICTED TO A
  PARTICULAR COMPUTER AND TERMINAL.")))
       (format t "

  Please refer to Chestnut's license for details.

  Protected by federal statutory copyright and state
  trade secret law.  Unauthorized use prohibited.
  Created 1993.  All Rights Reserved.  Patent Pending.")
       #+(or nasa nsa irs)
       (format t "

  RESTRICTED RIGHTS LEGEND

  Use, duplication or disclosure is subject to restrictions stated in
  Contract # ~A.

  Chestnut Software, Inc.

  SPECIAL COPYRIGHT NOTICE

  Unpublished - rights reserved under the Copyright Laws of The
  United States."
	       #+nasa "NAS10-11774"
	       #+nsa  "MDA 904-90-C-A185"
	       #+irs  "Tir-92-0113")
       (format t "

  Serial number:  ~A
  User name:  ~A~%"
	       ,serial-number
	       ,customer-name)
       ,@(when (equal license-type 4)
	   (if (equal machine-serial-number "")
	       `((format t "~%  Use of the software is prohibited until a ~
                    host machine~%  serial number ~
                    has been registered with Chestnut ~%  Software, Inc.  ~
                    Please contact Chestnut Software at~%  (617) 542-9222 or ~
                    tech-support@chestnut.com.~%"))
	       `((format t "  Source Machine Serial Number:  ~A~%"
			 ,machine-serial-number))))
	 
       (values))))

(defparameter *license-definition* (license-definition))

(defmacro set-up-license ()
  *license-definition*)

)  ; End EVAL-WHEN

(eval-when (compile eval load)
  (set-up-license))

#-internal-use
(eval-when (compile eval)
  (display-license-message))



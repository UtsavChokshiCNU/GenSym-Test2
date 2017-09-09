;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CTEST-PATCHES

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; John Valente



;;; The following provides stubs for all of those variables and functions which
;;; are only applicable to the AB system but which are referenced in modules
;;; included in the CTEST system.  In the past declare-forward-reference handled
;;; these cases but with Chestnut declare-forward-reference expands to nil and
;;; these functions are left undefined.



;;;; Stubbing Tools

;; jh, 3/16/94.  Changed defun-stub and defvar-stub to declare-stub-defun and
;; declare-stub-defvar respectively, so that etags, which matches "^(def...",
;; does not put these stubs in the tags table.  This should make meta-dot less
;; travail for seekers of the actual functions and variables.

(defvar-for-macro property-naming-module-of-stubbed-out-function
  (intern
    (format nil "FUNCTION-IN-MODULE-STUBBED-OUT-BY-~a-SYSTEM"
	    current-system-being-loaded)))

(defvar-for-macro property-naming-stubbed-out-functions-of-module
  (intern
    (format nil "FUNCTIONS-STUBBED-OUT-BY-~a-SYSTEM"
	    current-system-being-loaded)))

(defvar-for-macro modules-with-ctest-stubs nil)

(defmacro declare-stub-defun ((module-name name) arglist
                      &optional (constant-return-value nil))
  (let ((ignorable-args? nil))
    (do* ((args arglist (cdr args))
	  (arg (car args) (car args)))
	 ((null args)
	  (setq ignorable-args? (nreverse ignorable-args?)))
      (unless (member arg lambda-list-keywords)
	(push arg ignorable-args?)))
    `(progn
       ,@(if (eval-feature :development)
	     `((setf (get ',name
			  ',property-naming-module-of-stubbed-out-function)
		     ',module-name)
	       (pushnew
		 ',name
		 (get ',module-name
		      ',property-naming-stubbed-out-functions-of-module))
	       (pushnew ',module-name modules-with-ctest-stubs))
	     nil)
       (defun ,name ,arglist
	 ,@(if ignorable-args?
	       `((declare (ignore ,@ignorable-args?)))
	       nil)
	 (cerror "Go on" "function ~s is stubbed out" ',name)
	 ,constant-return-value))))

;; Added optional return value arg.  --ncc 3/16 or earlier/94.

(defvar-for-macro property-naming-module-of-stubbed-out-variable
  (intern
    (format nil "VARIABLE-IN-MODULE-STUBBED-OUT-BY-~a-SYSTEM"
	    current-system-being-loaded)))

(defvar-for-macro property-naming-stubbed-out-variables-of-module
  (intern
    (format nil "VARIABLES-STUBBED-OUT-BY-~a-SYSTEM"
	    current-system-being-loaded)))

(defmacro declare-stub-defvar (module-name name)
  `(progn
     ,@(if (eval-feature :development)
	   `((setf (get ',name
			',property-naming-module-of-stubbed-out-variable)
		   ',module-name)
	     (pushnew ',name
		      (get ',module-name
			   ',property-naming-stubbed-out-variables-of-module))
	     (pushnew ',module-name modules-with-ctest-stubs))
	   nil)
     (defvar ,name nil)))


(declare-stub-defvar ISO2022 all-supported-2022-escape-sequences)

(declare-stub-defun (KSMAP2 map-unicode-to-gensym-KS-C-5601) (unicode))
(declare-stub-defun (JISMAP map-unicode-to-gensym-JIS-X-0208) (unicode))
(declare-stub-defun (KSMAP2 map-gensym-KS-C-5601-to-unicode) (gensym-KS-C-5601))
(declare-stub-defun (JISMAP map-JIS-X-0208-to-unicode) (jis-x-0208))
(declare-stub-defun (JISMAP map-unicode-to-JIS-X-0208) (unicode))
(declare-stub-defun (KSMAP2 map-KS-C-5601-to-unicode) (gensym-KS-C-5601))
(declare-stub-defun (KSMAP2 map-unicode-to-KS-C-5601) (unicode))
(declare-stub-defun (GBMAP map-GB-2312-to-unicode) (GB-2312))
(declare-stub-defun (GBMAPR map-unicode-to-GB-2312) (unicode))
(declare-stub-defun (PLATFORMS get-values-from-x11-parse-geometry) (parsestring))
(declare-stub-defun (PLATFORMS c-x11-initialize) (a b c d e f g h i j))
(declare-stub-defun (PLATFORMS get-default-x11-display) ())
(declare-stub-defun (PLATFORMS get-window-name-from-command-line-if-any) ())
(declare-stub-defun (PLATFORMS get-icon-name-from-command-line-if-any) ())
(declare-stub-defun (PLATFORMS x11-preinitialize-if-necessary) ())
(declare-stub-defun (PLATFORMS local-gensym-x11-display) ())
(declare-stub-defun (PLATFORMS x11-display-specified-p) ())
(declare-stub-defun (PLATFORMS no-local-window-p) ())
(declare-stub-defun (PLATFORMS print-display-error) ())
(declare-stub-defun (PLATFORMS get-node-id-for-uuid-1) ())
(declare-stub-defun (PLATFORMS make-or-revise-window-per-native-window)
  (gensym-window? native-window))

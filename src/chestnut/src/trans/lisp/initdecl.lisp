;;; -*- Mode: Lisp; Package: TUTIL; Syntax: Common-Lisp -*-
;;;
;;; initdecl.lisp -- initialize declaration handlers
;;;
;;; author :  Sandra Loosemore
;;; date   :  19 Dec 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TUTIL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/initdecl.lisp,v $"
 "$Revision: 1.8 $"
 "$Date: 2007/07/12 18:29:34 $")

;;; Initialize proclamations for DECLARATION.  These are the things
;;; that are handled specially in DECLARE and PROCLAIM.  All other
;;; declarations should be defined with DEFINE-TRANSLATOR-DECLARATION,
;;; which addes the declaration name to the list automagically.

(setf (random-proclamation 'declaration) '(special declaration))

(declaim (declaration trans:translator-message
		      
		      function-name
		      global-function
		      
		      tx:include-at-runtime
		      tx:omit-at-runtime
		      
		      nonrelocatable

		      tx:nonconsing
		      tx:nonrelocating
		      tx:non-state-changing
		      tx:non-state-using
		      
		      ;; mostly internal to the translator
		      tx:foreign-type
		      
		      ;; internal to the translator
		      tx:closed-variable
		      tx:unread-variable
		      tx:unwritten-variable
		      
		      tx:variable-information
		      tx:function-information
		      tx:set-declaration-information
		      tx:declaration-information
		      tx:type-from-element-type
		      tx:read-once-variable
		      tx:binding-environment

		      #+translator-supports-thread
		      tx:global-variable ; binghe, 2009/5/26

		      tx:closed-function 
		      tx:function-needs-environment
		      tx:function-needs-object
		      tx:returns-one-value
		      tx:dllexport-function
		      tx:dllimport-function))

;;; Define handlers for all of the standard declaration specifiers.
;;; *** All of these functions should probably do more syntax checking.

(define-translator-declaration type (decl-spec env)
  (let ((type     (cadr decl-spec))
	(names    (cddr decl-spec)))
    (values
     (mapcar #'(lambda (name)
		 (multiple-value-bind (usage bound-p decls)
		     (translator-variable-information name env)
		   (declare (ignore usage bound-p))
		   (let ((old-type  (assoc 'type decls)))
		     `(,name type ,(if old-type
				       (and-types (cdr old-type) type env)
				       type)))))
	     names)
     nil nil nil)))

;;; binghe, 2009/3/28: make sure following definition load only once
(eval-when (compile load eval)
  (unless (himpl::feature tx:foreign-type)

(define-translator-declaration tx:foreign-type (decl-spec env)
  (declare (ignore env))
  (let ((type     (cadr decl-spec))
	(names    (cddr decl-spec)))
    (values
     (mapcar #'(lambda (name)
		 `(,name tx:foreign-type ,type))
	     names)
     nil nil nil)))

(pushnew 'tx:foreign-type *features*))) ; eval-when

(define-translator-declaration ftype (decl-spec env)
  (let ((ftype    (cadr decl-spec))
	(names    (cddr decl-spec)))
    (values
     nil
     (mapcar
      #'(lambda (name)
	  (multiple-value-bind (usage bound-p decls)
	      (translator-function-information name env)
	    (declare (ignore usage bound-p))
	    (let ((old-ftype  (assoc 'ftype decls)))
	      `(,name ftype ,(if old-ftype
				 (and-ftypes (cdr old-ftype) ftype env)
				 ftype)))))
      names)
     nil
     nil)))

(define-translator-declaration inline (decl-spec env)
  (declare (ignore env))
  (let ((names    (cdr decl-spec)))
    (values
     nil
     (mapcar #'(lambda (name) `(,name inline inline)) names)
     nil
     nil)))

(define-translator-declaration notinline (decl-spec env)
  (declare (ignore env))
  (let ((names    (cdr decl-spec)))
    (values
     nil
     (mapcar #'(lambda (name) `(,name inline notinline)) names)
     nil
     nil)))

(define-translator-declaration trans:translator-message (decl-spec env)
  (declare (ignore decl-spec env))
  (values
   nil
   nil
   nil
   nil))

;;; Syntax is (function-name real-name pretty-name)
(define-translator-declaration function-name (decl-spec env)
  (declare (ignore env))
  (values ()
	  `((,(second decl-spec) function-name ,(third decl-spec)))
	  ()
	  nil))

;;; Syntax is (global-function . names).
;;; Bound declarations indicate that the named functions should be translated
;;; as global functions.
(define-translator-declaration global-function (decl-spec env)
  (declare (ignore env))
  (values ()
	  (mapcar #'(lambda (name) `(,name global-function t)) (cdr decl-spec))
	  ()
	  nil))

;;; Syntax is (global-variable . names).
;;; Bound declarations indicate that the named variable is never bound specially
;;; and then should be translated into plain C variables.  -- binghe, 2009/5/26
#+translator-supports-thread
(define-translator-declaration tx:global-variable (decl-spec env)
  (declare (ignore env))
  (values (mapcar #'(lambda (name) `(,name tx:global-variable t)) (cdr decl-spec))
	  ()
	  ()
	  nil))

(define-translator-declaration tx:closed-variable (decl-spec env)
  (declare (ignore env))
  (values
   (mapcar #'(lambda (name)
	       `(,name tx:closed-variable t))
	   (cdr decl-spec))
   nil nil nil))

(define-translator-declaration tx:unread-variable (decl-spec env)
  (declare (ignore env))
  (values
   (mapcar #'(lambda (name)
	       `(,name tx:unread-variable t))
	   (cdr decl-spec))
   nil nil nil))

(define-translator-declaration tx:unwritten-variable (decl-spec env)
  (declare (ignore env))
  (values
   (mapcar #'(lambda (name)
	       `(,name tx:unwritten-variable t))
	   (cdr decl-spec))
   nil nil nil))

;;; The syntax of IGNORE and IGNORABLE has been extended like DYNAMIC-EXTENT
;;; so you can say things about function bindings as well as variable
;;; bindings.

(defun collect-variable-and-function-declarations (names declaration property)
  (let ((vars   nil)
	(funs   nil))
    (dolist (name names)
      (cond ((symbolp name)
	     (push `(,name ,property t) vars))
	    ((and (consp name) (eq (car name) 'function))
	     (push `(,(cadr name) ,property t) funs))
	    (t
	     (warn "Bad syntax in ~s declaration: ~s" declaration name))))
    (values (nreverse vars) (nreverse funs) nil nil)))

(define-translator-declaration ignore (decl-spec env)
  (declare (ignore env))
  (collect-variable-and-function-declarations
   (cdr decl-spec) 'ignore 'ignore))


(define-translator-declaration ignorable (decl-spec env)
  (declare (ignore env))
  (collect-variable-and-function-declarations
   (cdr decl-spec) 'ignorable 'ignorable))

(define-translator-declaration nonrelocatable (decl-spec env)
  (declare (ignore env))
  (values (mapcar #'(lambda (name) (list name 'nonrelocatable t))
		  (cdr decl-spec))
	  nil
	  nil
	  nil))

(define-translator-declaration optimize (decl-spec env)
  (values
   nil
   nil
   nil
   `((optimize
      ,@(mapcan
	 #'(lambda (quality)
	     (if (consp quality)
		 (check-optimize-quality
		  (car quality) (cadr quality) env)
		 (check-optimize-quality
		  quality 3 env)))
	 (cdr decl-spec))
      ,@(translator-declaration-information 'optimize env)))))

(defun check-optimize-quality (name value env)
  (unless (defined-as-optimize-quality name env)
    (warn "~s is not a known optimize quality." name)
    (return-from check-optimize-quality nil))
  (unless (member value '(0 1 2 3))
    (warn "~s is not a valid value for the optimize quality ~s."
	  value name)
    (return-from check-optimize-quality nil))
  `((,name ,value)))

(setf (defined-as-optimize-quality 'speed) 1)
(setf (defined-as-optimize-quality 'safety) 1)
(setf (defined-as-optimize-quality 'space) 1)
(setf (defined-as-optimize-quality 'compilation-speed) 0)
(setf (defined-as-optimize-quality 'debug) 1)

(setf (random-proclamation 'optimize)
      (let ((defaults   nil))
	(translator-map-environment-names
	 #'(lambda (name value) (push `(,name ,value) defaults))
	 *default-global-environment*
	 'defined-as-optimize-quality)
	defaults))

(define-translator-declaration dynamic-extent (decl-spec env)
  (declare (ignore env))
  (collect-variable-and-function-declarations
   (cdr decl-spec) 'dynamic-extent 'dynamic-extent))

(define-translator-declaration tx:variable-information (decl-spec env)
  (declare (ignore env))
  (values (cdr decl-spec) nil nil nil))

(define-translator-declaration tx:function-information (decl-spec env)
  (declare (ignore env))
  (values nil (cdr decl-spec) nil nil))

(define-translator-declaration tx:set-declaration-information (decl-spec env)
  (declare (ignore env))
  (values nil nil (cdr decl-spec) nil))

(define-translator-declaration tx:declaration-information (decl-spec env)
  (declare (ignore env))
  (values nil nil nil (cdr decl-spec)))

;;; (TX:INCLUDE-AT-RUNTIME (<usage> <names>*)*)
;;; usage is one of :macro, :setf, :type, :symbol

(define-translator-declaration tx:include-at-runtime (decl-spec env)
  (handle-runtime-expander-decl-spec decl-spec env))

;;; (TX:OMIT-AT-RUNTIME (<usage> <names>*)*)
;;; usage is one of :macro, :setf, :type, :symbol

(define-translator-declaration tx:omit-at-runtime (decl-spec env)
  (handle-runtime-expander-decl-spec decl-spec env))

(defun handle-runtime-expander-decl-spec
    (decl-spec env &aux (decl-name (first decl-spec)))
  (declare (ignore env))
  (let ((normal-p    (ecase decl-name
		       (tx:include-at-runtime t)
		       (tx:omit-at-runtime nil)))
	(decls       (rest decl-spec))
	(macro-decl-values nil)
	(set-decl-values   nil))
    (mapc #'(lambda (decl)
	      (let ((usage (first decl))
		    (names (rest decl)))
		(multiple-value-bind (normal inverse)
		    (ecase usage
		      (:macro  (values 'tx:include-at-runtime
				       'tx:omit-at-runtime))
		      (:setf   (values 'tx::include-setf-at-runtime
				       'tx::omit-setf-at-runtime))
		      (:type   (values 'tx::include-type-at-runtime
				       'tx::omit-type-at-runtime))
		      (:symbol (values 'tx::include-symbol-at-runtime
				       'tx::omit-symbol-at-runtime)))
		  (multiple-value-bind (decl-name inverse-decl-name)
		      (if normal-p
			  (values normal inverse)
			  (values inverse normal))
		    (mapc #'(lambda (name)
			      (let ((decl `(,name ,decl-name t))
				    (inv-decl `(,name ,inverse-decl-name nil)))
				(cond ((eq usage :macro)
				       (push decl macro-decl-values)
				       (push inv-decl macro-decl-values))
				      (t
				       (push decl set-decl-values)
				       (push inv-decl set-decl-values)))))
			  names)))))
	  decls)
    (values nil macro-decl-values set-decl-values nil)))

;;; Declarations which can apply to either scopes or function names:
;;; NONCONSING, NONRELOCATING, NON-STATE-CHANGING, NON-STATE-USING

(define-translator-declaration tx:nonconsing (decl-spec env)
  (function-state-declaration decl-spec env))

(define-translator-declaration tx:nonrelocating (decl-spec env)
  (function-state-declaration decl-spec env))

(define-translator-declaration tx:non-state-changing (decl-spec env)
  (function-state-declaration decl-spec env))

(define-translator-declaration tx:non-state-using (decl-spec env)
  (function-state-declaration decl-spec env))

(define-translator-declaration tx:type-from-element-type (decl-spec env)
  (declare (ignore env))
  (let ((array-name (cadr decl-spec))
	(names      (cddr decl-spec)))
    (values
     (mapcar #'(lambda (name)
		 `(,name tx:type-from-element-type ,array-name))
	     names)
     nil nil nil)))

(define-translator-declaration tx:binding-environment (decl-spec env)
  (declare (ignore decl-spec env))
  (values nil nil nil nil))

(define-translator-declaration tx:returns-one-value (decl-spec env)
  (declare (ignore env))
  (let ((names    (cdr decl-spec)))
    (values
     nil
     (mapcar #'(lambda (name) `(,name values-count 1)) names)
     nil
     nil)))

(define-translator-declaration tx:dllexport-function (decl-spec env)
  (declare (ignore env))
  (values
    nil
    (mapcar #'(lambda (name) `(,name dllexport t)) (cdr decl-spec))
    nil
    nil))

(define-translator-declaration tx:dllimport-function (decl-spec env)
  (declare (ignore env))
  (values
    nil
    (mapcar #'(lambda (name) `(,name dllimport t)) (cdr decl-spec))
    nil
    nil))

(defmacro define-simple-variable-translator-declaration (decl-name)
  `(define-translator-declaration ,decl-name (decl-spec env)
     (declare (ignore env))
     (values
      (mapcar #'(lambda (name)
		  `(,name ,',decl-name t))
	      (cdr decl-spec))
      nil nil nil)))

(define-simple-variable-translator-declaration tx:read-once-variable)

(defmacro define-simple-function-translator-declaration (decl-name)
  `(define-translator-declaration ,decl-name (decl-spec env)
     (declare (ignore env))
     (values
      nil
      (mapcar #'(lambda (name)
		  `(,name ,',decl-name t))
	      (cdr decl-spec))
      nil nil)))

(define-simple-function-translator-declaration tx:closed-function)
(define-simple-function-translator-declaration tx:function-needs-environment)
(define-simple-function-translator-declaration tx:function-needs-object)

;;; Helper function to process the above declarations, whose syntax
;;; are identical.

(defun function-state-declaration (decl-spec env)
  (declare (ignore env))
  (let ((decl-name   (car decl-spec))
	(names       (cdr decl-spec)))
    (cond ((or (equal names '(nil))
	       (equal names '(t)))
	   (values
	    nil
	    nil
	    nil
	    `((,decl-name . ,(car names)))))
	  ((or (member nil names)
	       (member t names))
	   (error "The following declaration syntax is illegal:~%~S~
	    ~%The symbols NIL and T may not appear as function names."
		  decl-spec))
	  (t
	   (values nil
		   (mapcar #'(lambda (name) `(,name ,decl-name t)) names)
		   nil
		   nil)))))

;;; These are from patch-2. The existing calls to define-type-symbol
;;; are in type.lisp, but these have to come after the 
;;; proclamation of foreign-type as a type in this file, so we moved them
;;; here. -alatto, 3/1/06
(define-type-symbol tx:foreign-pointer tx:foreign-pointer-type-p (atom))
(define-type-symbol tx:foreign-type tx:foreign-type-p (atom))
(define-type-symbol tx:primitive-foreign-type tx:primitive-foreign-type-p
  (tx:foreign-type))
(define-type-symbol tx:array-foreign-type tx:array-foreign-type-p
  (tx:foreign-type))
(define-type-symbol tx:structure-foreign-type tx:structure-foreign-type-p
  (tx:foreign-type))
(define-type-symbol tx:pointer-foreign-type tx:pointer-foreign-type-p
  (tx:foreign-type))


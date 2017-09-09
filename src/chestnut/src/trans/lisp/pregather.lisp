;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; pregather.lisp -- gather information on a per-toplevel form
;;; basis, for generating additional initcode, use by optimizer
;;;
;;; Author :  Andy Latto
;;; Date   :  4 Nov 1991
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.
;;;
;;;

;;; This file defines an information-gathering pass that is invoked
;;; after the initial conversion of the source code into target language.
;;; It gathers information that must be gathered on a per-form, rather
;;; than a per-function, basis, and any information which is necessary
;;; to determine what other target language must be stuck into the
;;; init function before this code is stuck in (for example, code to
;;; initialize constants used in this code).

;;; It does things like
;;;
;;;
;;; o Identifying nested function forms so that their definitions can
;;;   be spit out separately (stored in the "nested-functions" slot of
;;;   the function record).
;;;
;;; o Determining the closure state at the time that each closed variable
;;;   is bound.
;;;
;;; o Identifying the references to specials, so that the linking
;;;   code and declaration for the corresponding C global can be put in
;;;   near the first reference to the special.
;;;
;;; o Identifying references to constants and LOAD-TIME-VALUE forms and
;;;   collecting initialization code for these guys.
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/pregather.lisp,v $"
 "$Revision: 1.5 $"
 "$Date: 2007/06/12 14:57:36 $")

;;; The information gathering process is essentially a walk of the 
;;; target language tree.  So each statement and expression
;;; in the target language needs to have a walker function defined.

;;; The pregatherer returns a pregather-info struct, or nil, which
;;; is then merged with the pregather-info structs obtained by gathering
;;; all its substatments.

;;; This is no longer used, to improve efficiency. We leave it here
;;; as documentation; pregather-info treats a pregather function of :null
;;; as though it were this function.


(defun null-pregatherer (construct closure)
  (declare (ignore construct))
  (values nil closure))

(defmacro def-pregatherer (name lambda-list &body body)
  (let ((fname (intern (format nil "~A-~A" name 'pregatherer))))
    `(progn
       (defun ,fname ,lambda-list ,@body)
       (setf (pregatherer ',name) #',fname))))

(defun def-null-pregatherer (name)
  (setf (pregatherer name) :null))

(defun define-null-pregatherers (namelist)
  (dolist (name namelist)
    (def-null-pregatherer name)))

;;; pregather-info is passed the following two arguments:
;;; the construct to be walked
;;; the current lexical closure state.
;;; The returned value is a pregather-info struct.

;;; All of the above functions may return nil in place of a pregather-info
;;; struct, which has the same semantics as a pregather-info struct, all of
;;; whose fields are 0 or nil, as appropriate, and must accept a nil
;;; argument instead of a pregather-info struct.

;;; The pregather-info struct contains the following
;;; fields:
;;;    a list of closed local variables bound inside the construct.
;;; (this is only needed at top level; we generate this inside nested
;;; functions, but throw it away)
;;;    a list of nested function definitions appearing inside the construct,
;;;        not including those inside nested functions
;;;        (these are "local" functions)
;;;    a list of nested function definitions appearing inside the construct,
;;;        including those inside nested functions
;;;        (these are "global" functions)
;;;    a list of nested variable definitions appearing inside the construct
;;;    a list of labels of constants that are referenced lexically within
;;;      the construct, not including those referenced inside nested functions
;;;      (these are "local" constants).
;;;    a list of labels of constants that are referenced inside function
;;;      definitions lexically within the construct (these are "global"
;;;      constants).

;;; The external interface, pregather-info-list, returns a pregather struct.
;;;
;;; The individual pregatherers return two values; a pregather info struct
;;; (or nil), to be merged with those obtained from its substatements,
;;; and a closure state, to be passed as argument
;;; to the recursive gather on its substatements.

(defstruct (pregather-info)
  (closed-locals		nil)
  (local-functions		nil)
  (global-functions		nil)
  (variables                    nil)
  (local-constants		nil)
  (global-constants		nil))

;;; This is the external entry point.
(defun pregather-info-list (statements closure &optional 
				       pregather-info nil-result-allowed-p)
  (dolist (statement statements (or pregather-info
				    (unless nil-result-allowed-p
				      (make-pregather-info))))
    (when statement
      (let ((pregather-fn (or (target-form-pregatherer statement)
			      (error "No pregatherer for ~s." statement))))
	(multiple-value-bind (statement-pregather-info closure)
	    (if (eq pregather-fn :null)
		(values nil closure)
		(funcall pregather-fn statement closure))
	  (let ((substatements (substatements statement)))
	    (when substatements
	      (setq statement-pregather-info
		    (pregather-info-list substatements closure
					 statement-pregather-info t))))
	  (when statement-pregather-info
	    (setq pregather-info
		  (if (not pregather-info)
		      statement-pregather-info
		      (merge-pregathers pregather-info 
					statement-pregather-info)))))))))


;;; MERGE-PREGATHERED-INFO
;;; Merge the information in two pregather-info structs into one.
;;; destructively modifies and returns the first argument.
;;; Called only by pregather-info-list.
(defun merge-pregathers (pregather1 pregather2)
  (appendf (pregather-info-closed-locals pregather1)
	   (pregather-info-closed-locals pregather2))
  (appendf (pregather-info-local-functions pregather1)
	   (pregather-info-local-functions pregather2))
  (appendf (pregather-info-global-functions pregather1)
	   (pregather-info-global-functions pregather2))
  (unionq-appendf (pregather-info-variables pregather1)
		  (pregather-info-variables pregather2))
  (appendf (pregather-info-local-constants pregather1)
	   (pregather-info-local-constants pregather2))
  (appendf (pregather-info-global-constants pregather1)
	   (pregather-info-global-constants pregather2))
  pregather1)


;;; definitions for unionf, maxf, union-append, and union-appendf
;;; are in util.lisp

;;; Null pregatherers (All the pregather phase does with these statements is
;;; merge the results of pregathering their substatements, if any).

(define-null-pregatherers
    '(null-statement
      return-value
      return-values
      store-value
      store-values
      return-stored-values
      values-assign
      save-values
      save-more-values
      labeled-statement
      goto
      switch
      compound-statement
      if-statement
      forever-statement
      for-statement
      while-statement
      do-while-statement
      break-statement
      c-lines
      c-call
      preprocessor-conditional
      restore-values
      values
      nth-value
      first-multiple-value
      setq
      call
      variadic-call
      symbolic-constant
      conditional-operator
      not-operator
      comma-operator
      and-expression
      or-expression
      c-constant
      box-value
      unbox-value
      unbound-special-p
      initial-symbol
      initial-package
      function-object
      constant-label
      with-catch
      with-unwind-protect
      with-progv
      with-local-allocation
      with-area
      with-protected-variables
      cast
      function-name
      variadic-values-c-call
      values-c-call
      variadic-c-call))
      

;;; Statements
      
(def-pregatherer local-variable (construct closure)
  (declare (ignore construct))
  (values nil closure))

(def-pregatherer with-lexical-bindings (construct closure)
  (let ((records (cadr construct)))
    (dolist (r records)
      (when (variable-record-closed-p r)
	(setf (variable-record-closure-state r) closure)
	(push r closure)))
    (values (make-pregather-info
	     :closed-locals (remove-if-not #'variable-record-closed-p records))
	    closure)))

;;; updates the pregather-info with information gleaned from the symbol,
;;; which names a special.
(defun gather-special (symbol)
  (make-pregather-info :variables (gather-special-aux symbol)))

(defun gather-special-aux (symbol)
  (unless (defined-as-variable symbol *initial-global-environment*)
    (list symbol)))

(def-pregatherer with-special-binding (construct closure)
  (values (gather-special (caddr construct)) closure))

(def-pregatherer set-symbol-value-location (construct closure)
  (values (make-pregather-info
	   :local-constants (translate-hidden-constant (cadr construct)))
	  closure))

;;; Expressions

(def-pregatherer call-generic (construct closure)
  (values (gather-global-function (cadr construct)) closure))

(def-pregatherer variadic-call-generic (construct closure)
  (values (gather-global-function (cadr construct)) closure))

(def-pregatherer macro-call (construct closure)
  (values (gather-hidden-constants (second construct)) closure))

(def-pregatherer operator-call (construct closure)
  (values (gather-hidden-constants (second construct)) closure))

(def-pregatherer foreign-call (construct closure)
  (values (gather-hidden-constants (second construct)) closure))

(def-pregatherer accessor-call (construct closure)
  (values (gather-hidden-constants (second construct)) closure))

(defun gather-hidden-constants (name)
  (let ((hidden-constants '())
	(descr (defined-as-function name)))
    (dolist (object (when (function-descriptor-foreign-protocol descr)
		      (foreign-function-descriptor-uses-constants descr)))
      (when (environment-entry-p object)
	(setq object (environment-entry-name object)))
      (setq hidden-constants
	    (nconc hidden-constants (translate-hidden-constant object))))
    (make-pregather-info :local-constants hidden-constants)))

;;; For global functions references, hack it so that it includes an implicit
;;; reference to the corresponding symbol.

(def-pregatherer global-function (construct closure)
  (values (gather-global-function (cadr construct)) closure))

(def-pregatherer global-foreign-function (construct closure)
  (values (gather-global-function (cadr construct)) closure))

(defun gather-global-function (name)
  (when (environment-entry-p name)
    (setq name (environment-entry-name name)))
  (make-pregather-info :local-constants (translate-hidden-constant
					 (if (consp name) (cadr name) name))))

(defun translate-hidden-constant (name)
  ;; Returns hidden code-initialized constants
  (let ((construct (translate-constant-aux name)))
    (when (eq 'constant (target-form-type construct))
      (list construct))))


;;; For a function definition, reset the catch/special depth to 0 while
;;; walking the body.
;;; Attach locals, constants, etc. used within the function to the function
;;; record so that we can emit appropriate definitions.  Don't propagate
;;; this stuff upward.

(def-pregatherer function-definition (construct closure)
  (let* ((record (cadr construct))
	 (pregather-info
	  (pregather-info-list (function-record-statements record) closure)))
    (setf (function-record-nested-functions record)
	  (pregather-info-local-functions pregather-info))
    (setf (function-record-closure-state record) closure)
    (setf (function-record-constants record)
	  (pregather-info-local-constants pregather-info))    
    (setf (pregather-info-closed-locals pregather-info) nil)
    (setf (pregather-info-local-functions pregather-info) (list record))
    (setf (pregather-info-global-functions pregather-info)
	  (append (pregather-info-global-functions pregather-info)
		  (list record)))
    (setf (pregather-info-global-constants pregather-info)
	  (append (pregather-info-global-constants pregather-info)
		  (pregather-info-local-constants pregather-info)))
    (setf (pregather-info-local-constants pregather-info) nil)
    (values pregather-info closure)))

(def-pregatherer variable-definition (construct closure)
  (declare (ignore closure))
  (gather-special (cadr construct)))

;;; Constants and load-time-value are treated very much alike.  The idea
;;; is that we treat a constant reference like a load-time-value form.

(def-pregatherer constant (construct closure)
  (declare (ignore closure))
  (make-pregather-info :local-constants (list construct)))

(def-pregatherer load-time-value (construct closure)
  (declare (ignore closure))
  (make-pregather-info :local-constants (list construct)))

;;; Function-object forms appear only in the code which links symbols to
;;;   the corresponding function objects; they behave like constants.


;;; Constant-labels appear only as l-values in initcode, and don't need
;;; to be collected since we're guaranteed that there will be at least one
;;; other constant or load-time-value construct referencing the object.

;;; L-values


(def-pregatherer special-variable (construct closure)
  (declare (ignore closure))
  (gather-special (cadr construct)))


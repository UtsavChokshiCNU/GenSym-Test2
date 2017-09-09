;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; gather.lisp -- gather information for emitter
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  26 Jun 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;
;;; This file defines an information-gathering pass that is invoked
;;; after the initial conversion of the source code into target language,
;;; and all target-language to target-language transformations have
;;; been completed. It is called on a function and all its nested functions
;;; (nested functions first) just before the function is emitted.
;;;
;;; It does things like
;;;
;;; o Identifying local variables which are bound throughout the body
;;;   of each C function so that they can all be declared at the head
;;;   of the function (stored in the "local-variables" slot of the
;;;   function record).
;;;
;;; o Identifying which closed variables are inherited by which nested 
;;;   functions (stored in the "external-variables" slot of the function
;;;   record).
;;;
;;; o Filling in slots in target forms like with-catch that indicate
;;;   the lexical depth of nesting of such forms.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/gather.lisp,v $"
 "$Revision: 1.4 $"
 "$Date: 2007/06/12 14:57:36 $")

;;; The information gathering process is essentially a walk of the 
;;; target language tree.  So each statement and expression
;;; in the target language needs to have a walker function defined.

;;; The gatherer first recursively calls itself on all subforms, merges
;;; the resulting gather-info structs, and then calls the gatherer on
;;; the form itself with the merged gather-info struct as argument.
;;; It returns a gather-info struct (generally (always so far) a
;;; destructively modified version of its argument.

;;; NB. If a need arises for a gatherer to take some action before, rather
;;; than after, its subforms are gathered, this can be handled by
;;; reintroducing the concept of pre-order and post-order gatherers.
;;; If this is necessary, steal some code from the old version of
;;; the gatherer (version 1.44, 1.45, or 1.46)

;;; This is no longer used, to improve efficiency. We leave it here
;;; as documentation; gather-info treats a gather function of :null
;;; as though it were this function.

(defun null-gatherer (construct)
  (declare (ignore construct))
  nil)

(defmacro defgatherer (name lambda-list &body body)
  (let ((fname (intern (format nil "~A-~A" name 'gatherer))))
    `(progn
       (defun ,fname ,lambda-list ,@body)
       (setf (gatherer ',name) #',fname))))

(defun def-null-gatherer (name)
  (setf (gatherer name) :null))

(defun define-null-gatherers (namelist)
  (dolist (name namelist)
    (def-null-gatherer name)))

;;; gather-info is passed a construct to be gathered
;;; as argument.
;;; The returned value is a gather-info struct.
;;; The individual gather functions are
;;; passed a construct and a gather-info struct (obtained by merging
;;; all gather-info structs obtained from gathering its subforms),
;;; and return a gather-info struct, typically (always, so far) a
;;; destructively modified version of the gather-info argument.

;;; All of the above functions may return nil in place of a gather-info struct,
;;; which has the same semantics as a gather-info struct, all of whose
;;; fields are 0 or nil, as appropriate, and must accept a nil argument instead
;;; of a gather-info struct.

;;; The gather-info struct contains the following
;;; fields:
;;;    a list of local variables bound inside the construct.
;;;    a list of closed variables referenced inside the construct 
;;;       (including references inside a nested function)
;;;    the maximum depth of catch frames
;;;    the maximum depth of special binding frames
;;;    the maximum depth of consing-area frames
;;;    the maximum depth of consing-area-frontier frames
;;;

(defstruct (gather-info)
  (locals			nil)
  (externals			nil)
  (catches			0)
  (specials			0)
  (areas			0)
  (frontiers			0))

(defun gather-info-list (statements &optional nil-result-allowed-p)
  (let ((gather-info nil))
    (dolist (statement statements (or gather-info
				      (unless nil-result-allowed-p
					(make-gather-info))))
      (when statement
	(let* ((gather-fn (or (target-form-gatherer statement)
			      (error "No gatherer for ~s." statement)))
	       (statement-gather-info
		(if (eq gather-fn :null)
		    (gather-info-list (substatements statement) t)
		    (funcall gather-fn statement
			     (gather-info-list (substatements statement))))))
	  (when statement-gather-info
	    (if (null gather-info)
		(setq gather-info statement-gather-info)
		(progn
		  (unionq-appendf
		   (gather-info-locals gather-info)
		   (gather-info-locals statement-gather-info))
		  (maxf (gather-info-catches gather-info)
			(gather-info-catches statement-gather-info))
		  (maxf (gather-info-specials gather-info)
			(gather-info-specials statement-gather-info))
		  (maxf (gather-info-areas gather-info)
			(gather-info-areas statement-gather-info))
		  (maxf (gather-info-frontiers gather-info)
			(gather-info-frontiers statement-gather-info))
		  (unionq-appendf
		   (gather-info-externals gather-info)
		   (gather-info-externals statement-gather-info))))))))))


;;; Definitions for unionf, maxf, union-append, and union-appendf
;;; are in util.lisp

;;; Do the common case where a whole bunch of statements need to be
;;; traversed, each inheriting the same set of remaining arguments.
;;; Merge the return values in the obvious ways.


;;; Null gatherers (All the gather phase does with these statements is
;;; merge the results of gathering their substatements, if any).

(define-null-gatherers
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
      preprocessor-conditional
      restore-values
      values
      nth-value
      first-multiple-value
      setq
      call
      variadic-call
      c-call
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
      set-symbol-value-location
      call-generic
      variadic-call-generic
      macro-call
      operator-call
      foreign-call
      accessor-call
      global-function
      global-foreign-function
      variable-definition
      constant
      load-time-value
      special-variable
      with-protected-variables
      cast
      function-name
      variadic-values-c-call
      values-c-call
      variadic-c-call))

(defvar *gather-function*)

;;; Statements

(defgatherer with-lexical-bindings (construct gather-info)
  (dolist (variable (cadr construct))
    (pushnew variable (gather-info-locals gather-info))
    (let ((link (car (variable-record-closure-state variable))))
      (when link
	(if (eq *gather-function* (variable-record-in-function link))
	    (pushnew link (gather-info-locals gather-info))
	    (pushnew link (gather-info-externals gather-info))))))
  gather-info)

(defgatherer with-special-binding (construct gather-info)
  (setf (cadr construct) (gather-info-specials gather-info))
  (incf (gather-info-specials gather-info))
  gather-info)

;;; Helper function for constructs based on catch.
(defun gather-catcher (construct gather-info)
  (setf (cadr construct) (gather-info-catches gather-info))
  (incf (gather-info-catches gather-info))
  gather-info)

(defgatherer with-catch (construct gather-info)
  (gather-catcher construct gather-info))

(defgatherer with-unwind-protect (construct gather-info)
  (gather-catcher construct gather-info))

(defgatherer with-progv (construct gather-info)
  (gather-catcher construct gather-info))

(defgatherer with-local-allocation (construct gather-info)
  (setf	(third construct) (gather-info-areas gather-info)
	(fourth construct) (gather-info-frontiers gather-info))
  (incf (gather-info-areas gather-info))
  (incf (gather-info-frontiers gather-info))
  (unless *new-areas-and-frontiers*
    (setf (second construct) (gather-info-catches gather-info))
    (incf (gather-info-catches gather-info)))
  gather-info)

(defgatherer with-area (construct gather-info)
  (unless *new-areas-and-frontiers*
    (setf (second construct) (gather-info-catches gather-info))
    (incf (gather-info-catches gather-info)))
  (setf (third construct) (gather-info-areas gather-info))
  (incf (gather-info-areas gather-info))
  gather-info)


;;; Expressions

;;; For global functions references, hack it so that it includes an implicit
;;; reference to the corresponding symbol.

;;; For a function definition, reset the catch/special depth to 0 while
;;; walking the body.
;;; Attach locals, constants, etc. used within the function to the function
;;; record so that we can emit appropriate definitions.  Don't propagate
;;; this stuff upward.

(defgatherer function-definition (construct gather-info)
  (let* ((record (cadr construct)))
    (dolist (var (function-record-external-variables record))
      (if (eq *gather-function* (variable-record-in-function var))
	  (pushnew var (gather-info-locals gather-info))
	  (pushnew var (gather-info-externals gather-info))))
    (dolist (var (function-record-closure-state record))
      (if (eq *gather-function* (variable-record-in-function var))
	  (pushnew var (gather-info-locals gather-info))
	  (pushnew var (gather-info-externals gather-info)))))
  gather-info)

;;; This is the new external interface. The new gatherer is called primarily
;;; for effect. It returns the externals so that the init function can
;;; issue an error message if it finds any.

(defun gather-function-definition (record)
  (let* ((*gather-function* record)
	 (gather-info (gather-info-list (function-record-statements record))))
    ;; While the internal entry point collects up *all* closed variables
    ;; as being external, here we remove closed variables that are
    ;; bound locally from the list and return only those closed variables
    ;; that are not bound in any of the statements.
    ;; The handler for WITH-LEXICAL-BINDINGS might seem like a more obvious
    ;; place to do this, but the problem is that references to the variable
    ;; can appear outside the WITH-LEXICAL-BINDINGS.
    (when (and (gather-info-externals gather-info)
	       (gather-info-locals gather-info))
      (setf (gather-info-externals gather-info)
	    (let ((locals (gather-info-locals gather-info))
		  (new-ext nil))
	      (dolist (ext (gather-info-externals gather-info) new-ext)
		(when (dolist (loc locals t)
			(when (eq ext loc) (return nil)))
		  (push ext new-ext))))))
    (let ((argument-variables (function-record-argument-variables record)))
      (setf (function-record-local-variables record)
	    (remove-if #'(lambda (x) (member x argument-variables))
		       (remove-duplicates
			(append (gather-info-locals gather-info)
				(function-record-local-variables record)))))
      (setf (function-record-external-variables record)
	    (remove-if #'(lambda (x) (member x argument-variables))
		       (gather-info-externals gather-info))))
    (setf (function-record-catchframe-count record)
	  (gather-info-catches gather-info))
    (setf (function-record-specialframe-count record)
	  (gather-info-specials gather-info))
    (setf (function-record-areaframe-count record)
	  (gather-info-areas gather-info))
    (setf (function-record-frontierframe-count record)
	  (gather-info-frontiers gather-info))
    (gather-info-externals gather-info)))



;;; Constant-labels appear only as l-values in initcode, and don't need
;;; to be collected since we're guaranteed that there will be at least one
;;; other constant or load-time-value construct referencing the object.

;;; L-values

(defgatherer local-variable (construct gather-info)
  (let ((record (cadr construct)))
    (if (eq *gather-function* (variable-record-in-function record))
	(pushnew record (gather-info-locals gather-info))
	(pushnew record (gather-info-externals gather-info)))
    gather-info))


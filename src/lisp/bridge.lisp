;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module BRIDGE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde




;;;; Introduction

;;; The forms in this module provide tools that allow us to implement a GSI 4.0
;;; bridge in Lisp.

;;; GSI 4.0 was designed to be used from C.  In fact it wasn't ever intended
;;; that people would write Bridge's Lisp.  The interfaces it exports are
;;; C interfaces.  If we want to write in Lisp we have to meet it on its
;;; own terms.  Thus we have to write routines with C interfaces, and we
;;; have to accept C data structures.  BUT... we can know that some of
;;; these C data structures are actually Lisp data in disguise.

;;; Beware that this module is loaded into GSI, not G2.  GSI is a very
;;; very lean system.  Many facilities you are presuming are available
;;; aren't.   Format, files, etc.




;;;; SINs


;;; We must slam the following variable so that when we define the
;;; C routines that fufill the GSI substrate's desire for C routines
;;; it can call we don't get warnings about how the same C fuction
;;; name was used twice.  Once when the substrate declared it as
;;; something it was planning on calling, and a second time when
;;; we declared it as something that can be called.

(eval-when (:compile-toplevel :load-toplevel :execute)
(when (find-package "TIMPL")
  (setf (symbol-value
	  (find-symbol "*ALLOW-MULTIPLE-FOREIGN-FUNCTIONS-PER-C-NAME*"
	       (find-package "TIMPL")))
	t)))

;; Of course it would be better if this were done dynamically rather
;; than globally, but one fears creating closures.







;;;; Macros for Coercing Data Between Lisp and C

;;; Items are implemented as lisp structures, aka simple-vectors.
;;; The C user manipulates these only via a handle.  The actual
;;; Lisp data is used for this handle.

(defmacro coerce-item-from-c-to-lisp (c-representation-of-an-item)
  `,c-representation-of-an-item)

(defmacro coerce-item-from-lisp-to-c (lisp-representation-of-an-item)
  `,lisp-representation-of-an-item)


;;; Vectors of items implemented as Lisp simple vectors.  The C
;;; user is passed a pointer to the actual array of values.  So
;;; when we come and go we have to find or loose the Lisp header.

;; This code is a copy of gsi-get-array-from-c-contents as defined in GSI v4.
;; In GSI v5, gsi-get-array-from-c-contents is only supposed to be called from
;; within an API function, so just duplicate code here.

(defmacro coerce-items-from-c-to-lisp (c-vector-of-items)
  ;; Dig the Lisp arrays header out.
  (avoiding-variable-capture (c-vector-of-items)
    `(let ((magic-number (inline-gsi-get-magic-header ,c-vector-of-items)))
      (if (=f magic-number ,gsi-magic-number)
	  (inline-get-array-from-c ,c-vector-of-items gsi-magic-offset)
	  (gsi-error 'gsi-web gsi-bad-magic-number)))))


(defmacro coerce-items-from-lisp-to-c (lisp-vector-of-items)
  ;; Step around the Lisp Array header.
  `(gsi-extract-c-array ,lisp-vector-of-items))

;;; `Gref' expands into the code to get elements for arrays
;;; of gsi items, doing the magic necessary to step around
;;; the lisp header and magic number in C.

(defmacro gref (array offset)
  `(gsi-managed-svref ,array (+f gsi-magic-offset ,offset)))



;;; GSI Symbols look like C strings to C users.  These C strings
;;; are embedded in Lisp strings.

(defmacro coerce-symbol-from-c-to-lisp (c-string-of-symbol)
  #+development `,c-string-of-symbol
  ;; Dig the Lisp string out, and intern it.
  #-development `(intern (inline-restore-lisp-gensym-string ,c-string-of-symbol)
			 ab-package-1))

(defmacro coerce-symbol-from-lisp-to-c (symbol)
  #+development `,symbol
  ;; Get the string name of the symbol, and dig the C string out.
  #-development `(inline-extract-c-string (symbol-name ,symbol)))



;;; TEXT look like C strings to the C user, but they are embbed
;;; in Lisp strings.

(defmacro coerce-text-from-c-to-lisp (c-string-inside-lisp-string)
  #+development `,c-string-inside-lisp-string
  ;; Dig the Lisp string out of the C string.
  #-development `(inline-restore-lisp-gensym-string ,c-string-inside-lisp-string))

(defmacro coerce-text-from-lisp-to-c (lisp-string)
  #+development `,lisp-string
  ;; Strip off the Lisp string header.
  #-development `(inline-extract-c-string ,lisp-string))



;;; Integers are coerced by the foreign function interfaces of the Lisp systems,
;;; and we need do no additional coercions.

(defmacro coerce-integer-from-lisp-to-c (lisp-fixnum)  `,lisp-fixnum)

(defmacro coerce-integer-from-c-to-lisp (c-fixnum) `,c-fixnum)


;;; `Coerce-null-return-value' is used below when the return value of a
;;; function is void or :null.

(defmacro coerce-null-return-value (x) `,x)







;;;; Macros for Lisp Interface to GSI Substrate




;;; `Do-call-to-shared-routine' is used to call routines documented
;;; in the GSI manual for the use of the C programmer.  We know
;;; something the regular Bridge author doesn't, that these routines
;;; are actually a facade created by the foreign function calling
;;; interface and the GSI authors.  The real routines that implement
;;; these are named in a stylized was, for example the C routine
;;; `gsi_int_of' is `GSI-INT-OF' and that `SHARED-GSI-INT-OF' is
;;; the real implementation.

;;; But don't get too excited!  Some of the Lisp<->C type conversions
;;; are done in the body of the shared-* routine, so we still need
;;; do do some coercion to be able to call these routines.  See
;;; def-gsi-lisp-api below for help in doing that.

(defmacro do-call-to-shared-routine ((head-of-form &rest etc))
  (let ((shared-head-of-form
	  (intern (format nil "SHARED-~S" head-of-form))))
    (unless (fboundp shared-head-of-form)
      (warn "~S is not part of the GSI API" head-of-form))
    `(,shared-head-of-form ,@etc)))


(defmacro do-call-to-shared-wide-string-routine ((head-of-form &rest etc))
  (let ((shared-head-of-form
	  (intern (format nil "SHARED-~S" head-of-form))))
    (unless (fboundp shared-head-of-form)
      (warn "~S is not part of the GSI API" head-of-form))
    #+no-wide-strings
    `(,shared-head-of-form ,@etc)
    #-no-wide-strings
    `(,shared-head-of-form nil ,@etc)))


;;; Each `def-gsi-lisp-api' creates a lisp routine that our bridge can
;;; use to call the GSI C API.  It actually calls routines just under
;;; the surface of the C API, for example rather than call gsi-sym-of
;;; it calls shared-gsi-sym-of.

;;; Your first thought is probably that the shared-* routines uses Lisp
;;; representations on their interfaces, but no.  The shared-* routines
;;; implement the coercions between C instances and Lisp instances
;;; where the storage of the C instance is substructure of the storage
;;; for the Lisp instance.

;;; We call the C data embedded in the Lisp data.  The shared routines
;;; expect embedded C data, so we here do the coercion to and for
;;; embedded data.  This uses the coercion routines from the previous
;;; section.

(defmacro bifurcated-def-gsi-lisp-api ((lisp-name gsi-name return wide-api-p) &body args)
  (macrolet
      ((noop (x) `x))
    (labels
	;; Lookup macro that does coercions the interface.
	((coerce-to-c (type)
	   (case type
	     (item 'coerce-item-from-lisp-to-c)
	     (items 'coerce-items-from-lisp-to-c)
	     (symbol 'coerce-symbol-from-lisp-to-c)
	     (text 'coerce-text-from-lisp-to-c)
	     (integer 'coerce-integer-from-lisp-to-c)
	     (otherwise (warn "Unknown type on interface ~S" type))))
	 (coerce-to-lisp (type)
	   (case type
	     (item 'coerce-item-from-c-to-lisp)
	     (items 'coerce-items-from-c-to-lisp)
	     (symbol 'coerce-symbol-from-c-to-lisp)
	     (text 'coerce-text-from-c-to-lisp)
	     (integer 'coerce-integer-from-c-to-lisp)
	     (null 'coerce-null-return-value)
	     (otherwise (warn "Unknown type on interface ~S" type))))
	 (coerce-to-lisp-for-return (type)
	   (case type
;	     (text 'coerce-null-return-value)
	     (otherwise (coerce-to-lisp type)))))
      (let ((return-type (second return)))
	`(defun ,lisp-name ,(mapcar #'first args)
	   (,(coerce-to-lisp-for-return return-type)
	     (,(if wide-api-p
		   'do-call-to-shared-wide-string-routine
		   'do-call-to-shared-routine)
		 (,gsi-name
		    ,@(loop
			for (arg-name arg-type) in args
			collect `(,(coerce-to-c arg-type) ,arg-name))))))))))


(defmacro def-gsi-lisp-api ((lisp-name gsi-name return) &body args)
  `(bifurcated-def-gsi-lisp-api (,lisp-name ,gsi-name ,return nil) ,@args))

(defmacro def-gsi-wide-string-lisp-api ((lisp-name gsi-name return) &body args)
  `(bifurcated-def-gsi-lisp-api (,lisp-name ,gsi-name ,return t) ,@args))



;;; `Defun-gsi-callback' defines a routine that will be called by the GSI C
;;; substrate.  GSI expects these functions to be named by C names, so we define
;;; foreign callables, which gets the C names right.  It might be nice to be
;;; able to shortcut some of the macrology to do a lisp call but that seemed to
;;; require a lot more hackery.

;;; It is possible that this doesn't work in development; it can't yet be tested
;;; as gsi-in-lisp doesn't work at all.  yduJ, Mar. 2004

(defmacro defun-gsi-callback ((name return-type) arg-specs &body body)
  (let ((c-name (substitute #\_ #\- (string-downcase name)))
	(lcl-c-args
	  (loop for arg in arg-specs 
		collect
		(list (first arg)
		      (cond ((eq (second arg) :fixnum-long)
			     :signed-32bit)
			    ((eq (second arg) :object)
			     :lisp)
			    (t (second arg))))))
	(lcl-return-type
	  (if (eq return-type :fixnum-long)
	      :signed-32bit
	      return-type)))
    (progn
      (if (and (eval-feature :chestnut-3)
	       (eval-feature :chestnut-trans))
	  (with-package-specific-symbols (tx |::| def-foreign-callable)
	    `(def-foreign-callable (,name
				      (:name ,c-name)
				      (:return-type ,return-type))
		 ,arg-specs
	       ,@body))
	  (progn
	    #+lucid
	    `(lcl:def-foreign-callable (,name
					  (:name ,c-name)
					  (:return-type ,lcl-return-type))
		 ,lcl-c-args
	       ,@body)
	    #-lucid
	    nil)))))



;;;; Lisp Interface to GSI Substrate


;;; Currently only a the little of the GSI C API is imported, i.e.
;;; that little which my bridge needs.

(def-gsi-lisp-api (lgsi-int-of gsi-int-of (:returns integer))
    (item item))

(def-gsi-wide-string-lisp-api (lgsi-str-of gsi-str-of (:returns text))
    (item item))

(def-gsi-wide-string-lisp-api (lgsi-sym-of gsi-sym-of (:returns symbol))
    (item item))

(def-gsi-wide-string-lisp-api (lgsi-set-sym gsi-set-sym (:returns null))
    (item item) (value symbol))

;(def-gsi-lisp-api (lgsi-set-log gsi-set-log (:returns null))
;    (item item) (value logical))

(def-gsi-lisp-api (lgsi-set-int gsi-set-int (:returns null))
    (item item) (value integer))

(def-gsi-wide-string-lisp-api (lgsi-set-str gsi-set-str (:returns null))
    (item item) (value text))

(def-gsi-wide-string-lisp-api (lgsi-attr-by-name gsi-attr-by-name (:returns item))
    (item-with-attributes item)
  (attribute-name symbol))

(def-gsi-lisp-api (lgsi-reclaim-items gsi-reclaim-items (:returns null))
    (item-to-reclaim items))



#+development
(def-gsi-lisp-api (lgsi-rpc-declare-local gsi-rpc-declare-local (:returns null))
    (symbol-use-here symbol)
  (name-for-g2 text))

#+development
(def-gsi-lisp-api (lgsi-install-error-handler gsi-install-error-handler
					      (:returns null))
    (function-name symbol))




;;;; Macros for Lisp Routines GSI C Substrate Callbacks







;;;; Utilities for Defining Exported and Imported RPC


;;; An RPC can be implemented as a thread.  In that case the
;;; current thread throughout its execution is an `rpc-thread'.

(def-structure (rpc-thread
		 (:include thread)
		 (:constructor
		   make-rpc-thread
		   ()))
  call-handle-of-rpc-thread
  icp-socket-of-rpc-thread)

;;; `Ignored-return-values-for-signals' is used by the scheme that allows
;;; an RPC to signal errors.

(def-global-property-name ignored-return-values-for-signals)
(def-global-property-name return-function-of-rpc)




;;; When an RPC is not a thread then `current-rpc-call-handle' is
;;; bound to the call handle

(defvar current-rpc-call-handle)

#+development
(defun rpc-in-progress? ()
  (boundp 'current-rpc-call-handle))

(defmacro def-rpc-exported-to-g2
    ((name &rest alist-of-options) arguments &body body)

  (let* ((return-values (cdr (assq :returns alist-of-options)))
	 (make-thread-form (or (cadr (assq :thread-maker alist-of-options))
				'(make-rpc-thread)))
	 (remote-procedure-is-a-thread (eq (caar body) 'with-thread))
	 (return-function (intern (format nil "RETURN-FROM-~S" name)))
	 (return-function-1 (intern (format nil "~S-1" return-function)))
	 (thread-function-name  (intern (format nil "P-~S" name)))
	 (return-names (mapcar #'car return-values))
	 (return-count (+ 2 (length return-values)))
	 (ignored-return-values-for-signals
	   (loop for (nil argument-type) in return-values
		 collect
		 (case argument-type
		   (text "")
		   (integer 0)
		   (symbol 't)
		   (otherwise
		    (warn "Return type of ~S lacks something for signals."
			  argument-type)))))
	 (argument-binding-forms
	  `(,@(when arguments
		`((argument-vector (coerce-items-from-c-to-lisp c-argument-vector))))
	    ,@(loop
		for (argument-name argument-type) in arguments
		as i from 0
		collect
		(case argument-type
		  (item
		   `(,argument-name
		       (coerce-item-from-c-to-lisp
			 (gref argument-vector ,i))))
		  ((text integer symbol)
		   `(,argument-name
		       (get-value-of-any-simple-type
			 (gref argument-vector ,i))))
		  (otherwise
		   (warn "unknown argument rpc type ~S" argument-type)
		   `(,argument-name
		       (get-value-of-any-simple-type
			 (gref argument-vector ,i)))))))))

    ;; We can use GSI's function for defining C callable routines.
    `(progn
       (setf (ignored-return-values-for-signals ',name)
	     ',ignored-return-values-for-signals)
       (setf (return-function-of-rpc ',name)
	     ',return-function-1)
       (defun ,return-function-1 (signal-name signal-description ,@return-names)
	 (let ((call-handle
		,@(if remote-procedure-is-a-thread 
		      `((call-handle-of-rpc-thread current-thread))
		      `(current-rpc-call-handle)))
	       (result-items;; the (values ...) vector
		(coerce-items-from-c-to-lisp
		  (gsi-make-items ,return-count))))
	   ;; stuff the results into the vector
	   ,@(loop for (return-value-name return-value-type)
		       in (list* '(signal-name symbol)
				 '(signal-description text)
				 return-values)
		   as i from 0
		   collect
		   `(set-simple-value-in-item
		      (gref result-items ,i)
		      ,return-value-name))
	   ;; fire off our reply.
	   (unless (eq -1 call-handle) ;; we were started, not called.
	     (do-call-to-shared-routine
		 (gsi-rpc-return-values
		   (coerce-items-from-lisp-to-c result-items)
		   ,return-count
		   call-handle
		   (gsi-current-context-number))))
	   ;; reclaim the return values array.
	   (do-call-to-shared-routine
	       (gsi-reclaim-items
		 (coerce-items-from-lisp-to-c 
		   result-items)))
	   ,@(unless remote-procedure-is-a-thread
	       ;; Clear the shared pool that resides in the root-thread.
	       `((clear-thread-pool root-thread)))))

       (defmacro ,return-function (,@return-names)
	 (list ',return-function-1 ''ok "" ,@return-names))
       
       (def-gsi-api-function (,name (:return-type :null))
	   ((c-argument-vector :object)
	    (count :fixnum-long)
	    (call-handle :object))
	 ;; the way def-gsi-api-function expands in GSI 5.x and forward, we
	 ;; can't declare allowing-unwind at this point.  I'm not sure if it
	 ;; really matters... if the function actually needs to be declared
	 ;; to allow unwind.  For now, we'll try simply removing it from GSI5,
	 ;; when we are doing a translate, and try to put it back in, if we
	 ;; need to, when we can.  -jv, 8/20/03
	 #+(and (or development gsi4) lucid)
	 ,@(unless remote-procedure-is-a-thread
             ;; But modern platforms doesn't support this. --binghe, 2011/10/10
	     `((declare allowing-unwind)))
	 (fake-declare-ignore count) ;; ought to check and call gsi-error
	 ,(unless arguments
	    '(fake-declare-ignore c-argument-vector))

	 ,@(cond
	     (remote-procedure-is-a-thread
	      `((let ((new-thread-instance ,make-thread-form))
		  (setf (name-of-thread new-thread-instance)
			',name)
		  (setf (contour-wrapper-of-thread new-thread-instance)
			#'contour-wrapper-for-rpc-threads)
		  (setf (call-handle-of-rpc-thread new-thread-instance)
			call-handle)
		  (setf (icp-socket-of-rpc-thread new-thread-instance)
			current-icp-socket)
		  (do-start-thread (new-thread-instance)
		    (,thread-function-name
		       call-handle
		       c-argument-vector)))))
	     (t
	      ;; Pick out and bind the arguments.
	      `((let ((current-rpc-call-handle call-handle))
		  (let* ,argument-binding-forms
		      (multiple-value-bind (signal-name signal-description)
			  (catch 'rpc-signal
			    (progn ,@body)
			    nil)
			(when signal-name
			  (,return-function-1
			    signal-name
			    signal-description
			    ,@ignored-return-values-for-signals)))))))))

       ,@(when remote-procedure-is-a-thread
	   (let* ((body-form (first body))
		  (body-of-thread (cddr body-form))
		  (thread-alist (second body-form))
		  (thread-locals (rest (assq :locals thread-alist)))
		  (cleaned-thread-alist
		   (loop
		     for e in thread-alist
		     unless (eq :locals (car e)) collect e)))
	     `((defun-for-thread ,thread-function-name
		   (call-handle c-argument-vector)
		 (with-thread
		     ((:locals
			,@argument-binding-forms
			,@thread-locals)
		      (:special-contour
			(current-icp-socket
			 (icp-socket-of-rpc-thread current-thread)))
		      ,@cleaned-thread-alist)
		   ,@body-of-thread)))))
       
       )))


;;; `Contour-wrapper-for-rpc-threads' establishs the dynamic extent
;;; required for an rpc thread to run.  It binds the current context and
;;; it creates the catch which will handle any signals generated by the
;;; rpc's implementation.  Those signals are raised by signal-from-rpc,
;;; below, and are then returned to G2 via additional arguments added to
;;; the default return values.

(defun-allowing-unwind contour-wrapper-for-rpc-threads ()
  (let* ((current-icp-socket
	  (icp-socket-of-rpc-thread current-thread)))
    (multiple-value-bind (signal-name signal-description)
	(catch 'rpc-signal
	  (funcall (microtask-of-thread current-thread))
	  nil)
      (when signal-name
	(let ((rpc-name (name-of-thread current-thread)))
	  (apply (return-function-of-rpc rpc-name)
		 signal-name
		 signal-description
		 (ignored-return-values-for-signals rpc-name)))
	(thread-kill current-thread)))))

;; Note the analagous code inlined when the RPC does not create
;; a process.

(defun signal-from-rpc (signal-name signal-value)
  (throw 'rpc-signal (values signal-name signal-value)))



;;; One `def-rpc-imported-from-g2' is given at top level for
;;; each G2 procedure we will invoke from our Bridge.  In addition
;;; two little fragments of C code must be written and a fragment
;;; of lisp code.

(defmacro def-rpc-imported-from-g2 ((local-name g2-name) arguments)
  (flet ((mksym (&rest args)
	   (intern (apply #'concatenate 'string (mapcar #'string args)))))
    `(progn
       ;; We will need something to hold the GSI substrate's
       ;; knowledge of this routine over in G2.
       ,@(cond
	   ;; In Lisp we put this in a one element array stored in a defvar.
	   ((eval-feature :development)
	    `((defvar ,(mksym "INFO-FOR-" g2-name) (make-array 1))))
	   ;; In C we write a C routine in our main, and store it in
	   ;; a C global over there.
	   ((and (eval-feature :chestnut-3)
		 (eval-feature :chestnut-trans))
	    (with-package-specific-symbols (tx |::| def-foreign-function)
	      `((def-foreign-function
		    (,(mksym "RPC-START-FOR-" g2-name)
		      (:name ,(concatenate'string
				"rpc_start_for_"
				(substitute #\_ #\- (string-downcase g2-name))))
		      (:return-type :null))
		    (arg-items :object)))))
	   ;; In pass one of the translate we define a stub to avoid
	   ;; a warning
	   (t
	    `((defun ,(mksym "RPC-START-FOR-" g2-name) (arg-items)
		(declare (ignore arg-items))))))
       (defun ,local-name ,(mapcar #'first arguments)
	 (let ((arguments
		(coerce-items-from-c-to-lisp
		  (gsi-make-items ,(length arguments)))))
	   ,@(loop for (arg-name arg-type) in arguments
		   for i from 0
		   collect
		   `(set-simple-value-in-item (gref arguments ,i) ,arg-name))
	   ,@(cond
	       ((eval-feature :development)
		`((do-call-to-shared-routine
		      (gsi-rpc-start
			(svref ,(mksym "INFO-FOR-" g2-name) 0)
			(coerce-items-from-lisp-to-c arguments)
			(gsi-current-context-number))
		    ;; (gsi-reclaim-items arguments) ;; Leak?
		    )))
	       (t
		`((,(mksym "RPC-START-FOR-" g2-name)
		    (coerce-items-from-lisp-to-c arguments))))))))))


(def-global-property-name alist-for-rpc-into-g2)

(defun lookup-gsi-rpc-info (context name)
  (cdr (assq context (alist-for-rpc-into-g2 name))))

(defun install-gsi-rpc-info (context name gsi-rpc-info)
  (let ((old-entry?
	  (assq context (alist-for-rpc-into-g2 name))))
    (cond
      (old-entry?
       ;; Note A.
       (setf (cdr old-entry?) gsi-rpc-info))
      (t
	(gensym-push
	  (gensym-cons context gsi-rpc-info)
	  (alist-for-rpc-into-g2 name))))))

;; Note A: This might appear to leak the gsi-remote-procedure, but
;; the good news is that it is reclaimed when the context is cleaned
;; up.

; #+development
(defvar temp-array-for-declare-remote (make-array 1))

; #-development
(defvar temp-for-declare-remote nil)

#+development
(defun lgsi-rpc-declare-remote-1 (a b c)
  (declare (ignore a b c)))

(defun lgsi-rpc-declare-remote
    (list-function-symbol number-of-args number-of-values)
  (let ((handle
	  (feature-case
	    (development
	      (do-call-to-shared-routine ;; so this is all screwed up.
		  (gsi-rpc-declare-remote-plain
		    nil ; wide-string-p
		    temp-array-for-declare-remote
		    (symbol-name list-function-symbol)
		    'gsi-generic-rpc-return-handler
		    number-of-args
		    number-of-values
		    (gsi-current-context-number)))
	      (svref temp-array-for-declare-remote 0))
	    (t
	      (lgsi-rpc-declare-remote-1

		(symbol-name
		  list-function-symbol)
		number-of-args
		number-of-values)
	      temp-for-declare-remote))))
    (install-gsi-rpc-info (gsi-current-context-number)
			  list-function-symbol
			  handle)
    handle))



;;; `Apply-rpc-imported-g2' does an gsi-rpc-start on the
;;; routine named, with the arguments given.

(defun apply-rpc-imported-g2 (routine-name argument-list)
  (let ((rpc-info
	  (lookup-gsi-rpc-info
	    (gsi-current-context-number)
	    routine-name)))
    (cond
      ((not rpc-info)
       (bridge-log "No RPC info for ~S" routine-name)
       nil)
      (t
       (let ((argument-items
	       (coerce-items-from-c-to-lisp
		 (gsi-make-items (length argument-list)))))
	 (loop for argument-value in argument-list
	       as i from 0
	       do
	   (set-simple-value-in-item (gref argument-items i) argument-value))
	 (do-call-to-shared-routine
	     (gsi-rpc-start
	       rpc-info
	       (coerce-items-from-lisp-to-c argument-items)
	       (gsi-current-context-number)))
	 (lgsi-reclaim-items argument-items))
       t)
      )))


;;;; Convenience Functions on top of the GSI API

(defun-simple get-value-of-any-simple-type (item)
  (case (do-call-to-shared-routine (gsi-type-of item))
    (#.gsi-integer-type-tag
     (lgsi-int-of item))
    (#.gsi-string-type-tag
     (lgsi-str-of item))
    (#.gsi-symbol-type-tag
     (lgsi-sym-of item))
    (#.gsi-logical-type-tag
     (let ((value (do-call-to-shared-routine (gsi-log-of item))))
       (cond
	 ((=f 1000 value)
	  t)
	 ((=f -1000 value)
	  nil)
	 (t
	  (cerror "Go" "Logicals must be true or false")))))
    #+development
    (otherwise
     (cerror "Go" "Unknown type in item presumed to be simple."))
    ;; (#.gsi-logical-type-tag (do-call-to-shared-routine (gsi-log-of item)))
    ;; (#.gsi-64bit-float-type-tag (do-call-to-shared-routine (gsi-flt-of item)))
    ))

;; Note A -- shared-gsi-str-of does the right thing so we
;; don't need to coerce C->lisp here.

(defun-simple set-simple-value-in-item (item value)
  (do-call-to-shared-routine (gsi-clear-item item))
  (cond
    ((fixnump value)
     (do-call-to-shared-routine
	 (gsi-set-int item value)))
    ((stringp value)
     (do-call-to-shared-wide-string-routine
	 (gsi-set-str item
		      (coerce-text-from-lisp-to-c value))))
    ((eq value t)
     (do-call-to-shared-routine
	 (gsi-set-log item 1000)))
    ((eq value nil)
     (do-call-to-shared-routine
	 (gsi-set-log item -1000)))
    ((symbolp value)
     (do-call-to-shared-wide-string-routine
	 (gsi-set-sym item
		      (coerce-symbol-from-lisp-to-c value))))
    ;; ((floatp value)  (do-call-to-shared-routine (gsi-set-flt item value)))
    ;;  #.gsi-logical-type-tag ???
    ))




;;; `lgsi-get-attribute-value' will obtain the scalar value of
;;; and attribute of an item, given a symbol naming it.

(defun lgsi-get-attribute-value (item attribute-name)
  (get-value-of-any-simple-type
    (lgsi-attr-by-name item attribute-name)))


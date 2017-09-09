;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module G2-RPC1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and John Hodgkinson

;; jh, 3/16/94.  Changed name of this module from PROC-REMOTE to G2-RPC1

;;; This module contains the machinery for remote-procedure execution that is
;;; specific to G2 and involves passing values as arguments and results.
;;; (Module G2-RPC2 contains the G2-specific machinery for passing items as
;;; arguments and results, and modules GSI-RPC1 and GSI-RPC2 contain RPC
;;; machinery for the GSI product.)



;;;; Forward References

(declare-forward-references
  (g2ds-interface-socket-function                       function G2DS)
  (g2-to-g2-data-interface-p-function                   function G2DS)
  (make-g2ds-interface-1                                function G2DS)
  (g2ds-server-connection-icp-socket-function           function G2DS)
  (send-icp-rpc-start-deferring-objects                 function G2-RPC2)
  (send-icp-rpc-return-values-deferring-objects         function G2-RPC2)
  (transform-rpc-argument-or-result-list                function G2-RPC3)
  (call-remote-procedure-after-checks                   function G2-RPC3)
  (get-rpc-priority-from-computation-context            function G2-RPC3)
  (gsi-interface-p-function                             function G2-GSI)
  (var-rpc-info-from-index                              function G2-RPC3)
  (in-suspend-resume-p                                    variable ACTIVATE)
  )

(declare-forward-reference analyze-compiled-items-for-consistency function)
(declare-forward-reference icp-socket-of-interface-object function)
(declare-forward-reference item-references-enabled-p function)
(declare-forward-reference get-item-from-local-handle function)
(declare-forward-reference g2-reclaim-sending-resumable-object function)




;;;; Remote Procedure Declarations




;;; Before a G2 can execute a remote procedure, this procedure must be declared
;;; using a remote procedure declaration.  Remote procedure declarations are
;;; very similar to foreign function declarations, and should be available close
;;; to them on the New Definitions menu.  They are implemented as statements,
;;; and have one extra user visible slot besides the box-translation-and-text,
;;; that being the name-in-remote-system.  They also have the internal slots
;;; remote-procedure-argument-description and remote-procedure-return-value-
;;; types.

;;; The syntax for a declaration is as follows.

;;;   DECLARE REMOTE <procedure-name>
;;;                  ([<type> {, <type>}) = ([<type> {, <type>}])

;;; The first list of types is the argument list, the second list of types is
;;; the return value list.  The following types are available.

;;; INTEGER, FLOAT, TEXT, SYMBOL, TRUTH-VALUE

;;; Note that remote G2s can receive any of these types, but that some remote
;;; systems may not be able to receive the types SYMBOL, TEXT, or TRUTH-VALUE.
;;; (I'm not sure about the way these types are handled in remote systems, this
;;; should be tightened up.  -jra 3/2/90)  Quantities are not handled at all
;;; since remote foreign systems may not have a unified representation for
;;; integers and floats.

;;; The class `remote-procedure-declaration' is a subclass of statement, and is
;;; a user sepecfiable object for declare procedures which will be invoked on
;;; remote systems.

(def-class (remote-procedure-declaration
	     statement (foundation-class remote-procedure-declaration)
	     define-predicate)
  ;; setting to incomplete now handled in the initialize method (for statement)
;  (frame-status-and-notes
;    (:funcall slot-value-cons-function incomplete nil))
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame	      ; gets filled in with procedure name
    nil system (type nil) save)
  (box-translation-and-text
    nil vector-slot system (type remote-procedure-declaration text) select-changes)
  (name-in-remote-system
    nil vector-slot system (type remote-procedure-name))
  (remote-procedure-name-structure nil vector-slot system do-not-save)
  (user-supplied-remote-name? nil vector-slot system save)
  (scheduled-remote-procedure-starts nil vector-slot system do-not-save)
  (remote-procedure-argument-description nil
    (type remote-procedure-argument-descriptions)
    vector-slot system save do-not-put-in-attribute-tables)
  (remote-procedure-returned-values-description nil
    (type remote-procedure-argument-descriptions)
    vector-slot system save do-not-put-in-attribute-tables))

(defun-simple convert-remote-procedure-description-to-structure
    (remote-procedure-description)
  (let ((is-value-p (symbolp remote-procedure-description)))
    (cond
      (is-value-p
       (allocate-evaluation-structure
	 (managed-backquote eval-cons
	   (is-class-instance
	      \,(copy-evaluation-truth-value evaluation-false-value)
	    type-name
	      \,(case remote-procedure-description
		  (item-or-datum 'item-or-value)
		  (datum 'value)
		  (number 'quantity)
		  (t remote-procedure-description))))))
      (t (let* ((general-description?
		  (and (consp remote-procedure-description)
		       (cdr remote-procedure-description)))
		(general-type (getf general-description? :type))
		(class-name
		  (and (consp general-type)
		       (eq (first general-type) 'class)
		       (second general-type)))
		(kind (getf general-description? :kind))
		(included-system-attrs
		  (getf general-description? :include-system-attributes))
		(include-all-system-attrs
		  (getf general-description? :include-all-system-attributes))
		(include-all-system-attrs-except
		  (getf general-description? :include-all-system-attributes-except))
		(included-user-attrs
		  (getf general-description? :include-attributes))
		(excluded-user-attrs
		  (getf general-description? :exclude-attributes)))
	   (if general-description?
	       (allocate-evaluation-structure
		 (managed-backquote eval-cons
		   (is-class-instance
		      \,(copy-evaluation-truth-value evaluation-true-value)
		    type-name
		      \,class-name
		    kind
		      \,kind
		    include-all-system-attributes
		      \,(if include-all-system-attrs
			    (copy-evaluation-truth-value
			      evaluation-true-value)
			    (copy-evaluation-truth-value
			      evaluation-false-value))
		    include-all-system-attributes-except
		      \,(with-list-to-evaluation-sequence-mapping
			    (include-all-system-attrs-except attr) attr)
		    included-system-attributes
		      \,(with-list-to-evaluation-sequence-mapping
			    (included-system-attrs attr) attr)
		    included-user-attributes
		      \,(with-list-to-evaluation-sequence-mapping
			    (included-user-attrs attr) attr)
		    excluded-user-attributes
		      \,(with-list-to-evaluation-sequence-mapping
			    (excluded-user-attrs attr) attr))))
		nil))))))

(define-category-evaluator-interface (remote-procedure-argument-descriptions
				       :access read)
    (sequence (structure remote-procedure-argument-description
		((is-class-instance truth-value)
		 (type-name symbol)
		 (kind (or (no-item)
			   (member handle
				   by-copy-with-handle
				   reference)))
		 (include-all-system-attributes truth-value)
		 (included-system-attributes
		   (sequence symbol 0))
		 (include-all-system-attributes-except
		   (sequence symbol 0))
		 (included-user-attributes
		   (sequence symbol 0))
		 (excluded-user-attributes
		   (sequence symbol 0)))
		(and type-name
		     #+ignore ; the "(eq kind 'handle)" makes this invalid
		     (or is-class-instance ; but it would only be used for the setter.
			 (not (or (eq kind 'handle)
				  included-system-attributes
				  include-all-system-attributes-except
				  included-user-attributes
				  excluded-user-attributes)))
		     (not (and included-user-attributes
			       excluded-user-attributes))))
	      0)
  ((get-form (slot-value?))
   (let ((arg-descriptions
	   (and slot-value?
		(loop for counter
		      from 1 below (managed-array-length slot-value?) by 2
		      for description = (managed-svref slot-value? counter)
		      collect
		      (convert-remote-procedure-description-to-structure
			description)
			using eval-cons))))
     (allocate-evaluation-sequence arg-descriptions))))

(define-category-evaluator-interface (remote-procedure-name
				       :access read-write)
    (or (no-item) text)
  ((set-form (evaluation-value))
   (if evaluation-value
       (copy-for-phrase evaluation-value)
       'none))
  ((get-form (slot-value?))
   (if slot-value?
       (copy-evaluation-text (symbol-name-text-string slot-value?))
       nil)))

(defun-simple remote-procedure-argument-description-function
	      (remote-procedure-declaration)
  (remote-procedure-argument-description remote-procedure-declaration))

(defun-simple set-remote-procedure-argument-description-function
              (remote-procedure-declaration new-value)
  (setf (remote-procedure-argument-description remote-procedure-declaration)
	new-value))

(defun-simple remote-procedure-returned-values-description-function
              (remote-procedure-declaration)
  (remote-procedure-returned-values-description remote-procedure-declaration))

(defun-simple set-remote-procedure-returned-values-description-function
              (remote-procedure-declaration new-value)
  (setf (remote-procedure-returned-values-description remote-procedure-declaration)
	new-value))

(defmacro remote-procedure-return-value-types (remote-procedure-declaration)
  `(third (car (box-translation-and-text ,remote-procedure-declaration))))

(defun remote-procedure-return-value-types-function (remote-procedure-declaration)
  (remote-procedure-return-value-types remote-procedure-declaration))


(add-grammar-rules
  `((remote-procedure-declaration
      ('declare 'remote
       procedure-name remote-procedure-type-list '= remote-procedure-type-list)
      (3 4 6))
    (remote-procedure-name whole-string)
    (remote-procedure-name 'none)
    (remote-procedure-type 'item-or-value item-or-datum)
    (remote-procedure-type 'value datum)
    (remote-procedure-type 'quantity number)
    (remote-procedure-type 'integer)
    (remote-procedure-type 'long)
    (remote-procedure-type 'float)
    (remote-procedure-type 'text)
    (remote-procedure-type 'symbol)
    (remote-procedure-type 'truth-value)
    (remote-procedure-type 'structure (:type (structure)))
    (remote-procedure-type 'sequence (:type (sequence)))
    (remote-procedure-type-list ( '\( '\) ) nil nil-function)
    (remote-procedure-type-list ( '\( remote-procedure-type-list-1 '\)) 2 cdr)
    ))

(add-grammar-rules
  `((remote-procedure-type-list-1
      ('all 'remaining remote-procedure-type)
      (\, 3) encode-remaining-into-remote-procedure-type-1)
    (remote-procedure-type-list-1
      (remote-procedure-type-list-1-tail '\, 'all 'remaining remote-procedure-type)
      (\, 1 5) encode-remaining-into-remote-procedure-type-2)
    
    (remote-procedure-type-list-1 remote-procedure-type-list-1-tail)
    (remote-procedure-type-list-1-tail remote-procedure-type (\, 1))
    (remote-procedure-type-list-1-tail (remote-procedure-type-list-1-tail '\, remote-procedure-type)
				       (\, 1 3) simplify-associative-operation)))

(defun-simple encode-remaining-into-remote-procedure-type (form)
  (if (atom form)
      (phrase-list ':type form ':all-remaining t)
      (nconc form (phrase-list ':all-remaining t))))

(defun encode-remaining-into-remote-procedure-type-1 (form)
  (phrase-list '\, (encode-remaining-into-remote-procedure-type (second form))))

(defun encode-remaining-into-remote-procedure-type-2 (form)
  (simplify-associative-operation
    (phrase-list '\, (second form)
		 (encode-remaining-into-remote-procedure-type (third form)))))


(defun-simple fix-remote-procedure-declaration-descriptions (descriptions)
  (loop for index from 0 below (var-count descriptions)
	for var-whole-type-description =
	(var-whole-type-description-from-index descriptions index)
	for type = (var-type-from-index descriptions index)
	do
    ;; (:type (class xxx :kind handle)) => (:type (class xxx) :kind handle)
    (when (and (consp type)
	       (eq (car type) 'class))
      (let ((badly-formated-properties? (cddr type)))
	(when badly-formated-properties?
	  (setf (cddr type) nil)
	  (if (eq (car var-whole-type-description) ':general-description)
	      (setf (cdr (last var-whole-type-description))
		    badly-formated-properties?)
	      (setf (var-whole-type-description-from-index descriptions index)
		    (slot-value-cons
		      ':general-description
		      (slot-value-cons
			':type
			(slot-value-cons
			  type badly-formated-properties?)))))))))
  (loop for index from 0 below (var-count descriptions)
	for description = (var-general-description-from-index descriptions index)
	do
    (loop for tail on (cdr description) by 'cddr
	  do
      (when (and (cdr tail)
		 (eq (cadr tail) ':as-handle-p))
	(setf (cdr tail)
	      (if (caddr tail)
		  (slot-value-cons ':kind (slot-value-cons 'handle (cdddr tail)))
		  (cdddr tail))))))
  descriptions)

(def-post-loading-function reformat-remote-procedure-declaration-descriptions
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (use-kind-for-remote-procedure-declaration-argument-passing-style-p)
      (loop for remote-procedure-declaration
		being class-instance of 'remote-procedure-declaration
	    do
	(convert-description-list-location-to-managed-array
	  (remote-procedure-argument-description remote-procedure-declaration))
	(setf (remote-procedure-argument-description remote-procedure-declaration)
	      (fix-remote-procedure-declaration-descriptions
		(remote-procedure-argument-description remote-procedure-declaration)))
	(setf (remote-procedure-returned-values-description remote-procedure-declaration)
	      (or (remote-procedure-returned-values-description remote-procedure-declaration)
		  (copy-for-slot-value
		    (remote-procedure-return-value-types remote-procedure-declaration))))
	(convert-description-list-location-to-managed-array
	  (remote-procedure-returned-values-description remote-procedure-declaration))
	(setf (remote-procedure-returned-values-description remote-procedure-declaration)
	      (fix-remote-procedure-declaration-descriptions
		(remote-procedure-returned-values-description remote-procedure-declaration)))
	(let* ((declarations
		 (first (box-translation-and-text remote-procedure-declaration)))
	       (arg-declarations (second declarations))
	       (result-declarations (third declarations)))
	  (loop for arg-declaration in arg-declarations
		do
	    (when (and (consp arg-declaration)
		       (eq (car arg-declaration) 'class))
	      (let ((excess-info? (cddr arg-declaration)))
		(when excess-info?
		  (setf (cddr arg-declaration) nil)
		  (reclaim-slot-value-cons excess-info?)))))
	  (loop for result-declaration in result-declarations
		do
	    (when (and (consp result-declaration)
		       (eq (car result-declaration) 'class))
	      (let ((excess-info? (cddr result-declaration)))
		(when excess-info?
		  (setf (cddr result-declaration) nil)
		  (reclaim-slot-value-cons excess-info?))))))))))

(def-slot-value-compiler remote-procedure-declaration (parse-result declaration)
  (let ((name (first parse-result))
	(arg-descriptions (second parse-result))
	(result-descriptions (third parse-result)))
    (cond ((null (user-supplied-remote-name? declaration))
	   (change-slot-value
	     declaration 'name-in-remote-system
	     name))
	  ((eq (name-in-remote-system declaration) name)
	   (setf (user-supplied-remote-name? declaration) nil)))
    (change-slot-value
      declaration
      'remote-procedure-argument-description
      (convert-description-list-to-managed-array arg-descriptions))
    (change-slot-value
      declaration
      'remote-procedure-returned-values-description
      (convert-description-list-to-managed-array result-descriptions t))
    (phrase-list
      (first parse-result)
      (loop for type in arg-descriptions
	    collect
	    (if (symbolp type)
		type
		(copy-list-using-phrase-conses (getf type :type)))
	      using phrase-cons)
      (loop for type in result-descriptions
	    collect
	    (if (symbolp type)
		type
		(copy-list-using-phrase-conses (getf type :type)))
	      using phrase-cons))))

(def-class-method put-box-translation-and-text-slot-value
		  (remote-procedure-declaration new-value initializing?)
  ;; Note that the update to box-translation-and-text must be done before the
  ;; consistency-analysis and name change, done below.  The analysis may rely on
  ;; the RPC return argument types, which are held in the box-translation-and-
  ;; text.
  (setf (box-translation-and-text remote-procedure-declaration)
	new-value)
  (when (not initializing?)
    (let* ((new-name (car (car new-value)))
	   (same-name?
	     (eq new-name
		 (name-or-names-for-frame remote-procedure-declaration))))
      ;; Make the frame-status of the RPC declaration OKAY before changing the
      ;; name.  This is necessary because items referring to this RPC are
      ;; analyzed when the name is changed and need to check if the RPC is okay.
      (update-frame-status remote-procedure-declaration nil nil)
      (change-slot-value
	remote-procedure-declaration 'name-or-names-for-frame new-name)
      (when same-name?
	;; Analyze when the name has not changed.  (In that case, change-slot-
	;; value does not analyze.)  This is necessary because the declaration
	;; may have changed and callers to this RPC need to be analyzed.
	(analyze-compiled-items-for-consistency new-name))))
  (values new-value nil))

(def-slot-value-compiler remote-procedure-name (parse-result declaration)
  (cond
    ((eq parse-result 'none)
     (let* ((box-translation-and-text
	      (box-translation-and-text declaration))
	    (translation?
	      (unless (eq box-translation-and-text no-value)
		(car box-translation-and-text)))
	    (name (car translation?)))
       
       (setf (user-supplied-remote-name? declaration) nil)
       (if name
	   (intern-text-string (tformat-text-string "~(~A~)" name))
	   nil)))
    
    (t
     (setf (user-supplied-remote-name? declaration) t)
     (intern-text-string (copy-text-string parse-result)))))

(def-slot-value-writer remote-procedure-name (value)
  (tprin (if value (symbol-name-text-string value) "none") value))

(def-slot-putter name-in-remote-system (remote-procedure-declaration new-name)
  (let ((old-name (remote-procedure-name-structure remote-procedure-declaration)))
    (when old-name
      (reclaim-remote-procedure-name old-name))
    (setf (remote-procedure-name-structure remote-procedure-declaration)
	  (make-remote-procedure-name new-name))
    (setf (name-in-remote-system remote-procedure-declaration) new-name)))

(def-slot-value-reclaimer remote-procedure-name-structure
			  (name-structure?)
  (when name-structure?
    (reclaim-remote-procedure-name name-structure?)))




;;;; The structure `scheduled-remote-procedure-start' is used to represent a
;;;; scheduled remote procedure which is to be started as some point in the
;;;; future.  It contains a frame serial number with which to verify that the
;;;; ICP interface has not been recycled, a pointer to the
;;;; remote-procedure-declaration which this is an invocation of, an eval cons
;;;; list of temporary constants which are the arguments to the remote
;;;; procedure, and a pointer to the scheduled task which will begin this
;;;; execution.  Note that the remote-procedure-declaration holds a constant
;;;; queue which contains all scheduled remote procedures to be started.

(def-structure (scheduled-remote-procedure-start
		 (:constructor make-scheduled-remote-procedure-start
		  (remote-procedure-start-reference-serial-number
		    remote-procedure-start-declaration
		    remote-procedure-start-icp-interface
		    remote-procedure-start-argument-list)))
  (remote-procedure-start-reference-serial-number nil :reclaimer reclaim-frame-serial-number)
  remote-procedure-start-declaration
  remote-procedure-start-icp-interface
  (remote-procedure-start-argument-list
    nil :reclaimer reclaim-rpc-argument-list-1)
  (remote-procedure-start-task nil :reclaimer cancel-task)
  remote-procedure-start-queue-entry)




;;; The slot scheduled-remote-procedure-starts holds a constant queue of
;;; scheduled-remote-procedure-start structure instances.  When activated an
;;; empty constant queue is placed here.  On deactivation, all scheduled starts
;;; should be dequeued and reclaimed, and the constant queue reclaimed.

(def-class-method activate (remote-procedure-declaration)
  (unless in-suspend-resume-p
    (setf (scheduled-remote-procedure-starts remote-procedure-declaration)
	  (make-empty-constant-queue)))
  (funcall-superior-method remote-procedure-declaration))

(def-class-method deactivate (remote-procedure-declaration)
  (unless in-suspend-resume-p
    (loop with queue = (scheduled-remote-procedure-starts
			 remote-procedure-declaration)
	  for scheduled-start = (constant-queue-dequeue queue)
	  while scheduled-start do
      (reclaim-scheduled-remote-procedure-start scheduled-start)
	  finally
	    (reclaim-constant-queue queue))
    (setf (scheduled-remote-procedure-starts remote-procedure-declaration) nil))
  (funcall-superior-method remote-procedure-declaration))






;;;; Remote Procedure Start




;;; The function `start-remote-procedure' is called from rules and procedures to
;;; start a remote procedure.  It takes a remote-procedure-declaration, an ICP
;;; interface object (i.e. either a G2-to-G2 or a GSI configuration object), an
;;; eval-cons-list of temporary constants which are the arguments, a priority or
;;; NIL, and a number of seconds to wait for starting or NIL.

;;; This function will type check the argument list and cause the messages
;;; to be sent across the ICP socket in the ICP interface object which will
;;; start the remote procedure.  If there is a wait interval given, then a task
;;; will be scheduled at the given priority to start the procedure.  If there is
;;; no wait interval given, then the priority is ignored.

(defun-simple start-remote-procedure
	      (remote-procedure-declaration
		icp-interface argument-list wait-interval? priority?
		new-top-of-stack)
  (let ((argument-error-message?
	  (remote-procedure-arg-type-error-p
	    (remote-procedure-argument-description
	      remote-procedure-declaration)
	    argument-list)))
    (when argument-error-message?
      (reclaim-rpc-argument-list argument-list nil)
      (when (and *current-computation-frame*
		 (procedure-p *current-computation-frame*))
	(write-stack-error new-top-of-stack
	  (tformat
	    "Argument error while starting remote procedure ~NF: ~a."
	    remote-procedure-declaration
	    argument-error-message?)
	  (reclaim-text-string argument-error-message?)))
      (write-warning-message* 1
	(tformat
	  "Argument error while starting remote procedure ~NF: ~a."
	  remote-procedure-declaration
	  argument-error-message?)
	(reclaim-text-string argument-error-message?))
      (return-from start-remote-procedure nil))
    (let ((execution-priority
	    (or priority?
		(get-rpc-priority-from-computation-context))))
      (if (null wait-interval?)
	  (if (or (g2-list-p icp-interface) (g2-array-p icp-interface))
	      (execute-parallel-remote-procedure-start
		remote-procedure-declaration
		icp-interface
		argument-list
		execution-priority)
	      (execute-remote-procedure-start
		remote-procedure-declaration
		icp-interface
		argument-list
		execution-priority
		nil))
	  (let ((scheduled-start
		  (make-scheduled-remote-procedure-start
		    (copy-frame-serial-number (current-frame-serial-number))
		    remote-procedure-declaration
		    icp-interface
		    argument-list)))
	    (with-future-scheduling
		((remote-procedure-start-task scheduled-start)
		 execution-priority
		 (g2-evaluation-value-to-future-interval wait-interval?))
	      (execute-scheduled-remote-procedure-start
	       scheduled-start execution-priority))
	    (reclaim-evaluation-quantity wait-interval?)
	    (setf (remote-procedure-start-queue-entry scheduled-start)
		  (constant-queue-enqueue
		    (scheduled-remote-procedure-starts
		      remote-procedure-declaration)
		    scheduled-start))))
      nil)))

(defun-simple all-elements-ok-for-parallel-rpc-start (icp-interface)
  (if (g2-list-p icp-interface)
      (do-g2-list-elements (element icp-interface t)
	(unless (and (framep element)
		     (or (not (serve-item-p element))
			 (g2-to-g2-data-interface-p-function element)
			 (gsi-interface-p-function element)))
	  (return nil)))
      (do-g2-array-elements (element icp-interface t)
	(unless (and (framep element)
		     (or (not (serve-item-p element))
			 (g2-to-g2-data-interface-p-function element)
			 (gsi-interface-p-function element)))
	  (return nil)))))

(defun execute-scheduled-remote-procedure-start
    (scheduled-start execution-priority)
  (let ((reference-serial-number
	  (remote-procedure-start-reference-serial-number
	    scheduled-start))
	(remote-procedure-declaration
	  (remote-procedure-start-declaration scheduled-start))
	(icp-interface (remote-procedure-start-icp-interface scheduled-start))
	(argument-list (remote-procedure-start-argument-list scheduled-start)))
    (delete-queue-element (remote-procedure-start-queue-entry scheduled-start))
    ;; Perhaps the following should be allowed, even while G2 is not running.
    ;; FIND ME, JRA -jra 11/4/96
    (when (and (frame-has-not-been-reprocessed-p
		 remote-procedure-declaration reference-serial-number)
	       (active-p remote-procedure-declaration)
	       (frame-has-not-been-reprocessed-p
		 icp-interface reference-serial-number)
	       (active-p icp-interface))
      (if (or (g2-list-p icp-interface) (g2-array-p icp-interface))
	  (when (all-elements-ok-for-parallel-rpc-start icp-interface)
	    (execute-parallel-remote-procedure-start
	      remote-procedure-declaration
	      icp-interface
	      argument-list
	      execution-priority))
	  (execute-remote-procedure-start
	    remote-procedure-declaration
	    icp-interface
	    argument-list
	    execution-priority
	    nil))
      ;; Following form prevents double reclamation of the contents of
      ;; remote-procedure-start-argument-list and its substructure.
      (setf (remote-procedure-start-argument-list scheduled-start) nil))
    (reclaim-scheduled-remote-procedure-start scheduled-start)))

(defun-simple non-resumable-icp-socket-p (icp-socket?)
  (and icp-socket?
       (icp-connection-open-p icp-socket?)
       (not (icp-connection-being-shutdown? icp-socket?)) ;?
       (with-bifurcated-version-for-output
	   (supports-non-resumability-icp-version icp-socket?)
	 nil
	 (icp-socket-does-not-allow-resumability icp-socket?))))

(defun-simple add-interface-to-alist (interface alist key)
  (let ((a (loop for a in alist
		 when (equal key (car a))
		   return a)))
    (cond (a
	   (when key (reclaim-gensym-cons key))
	   (gensym-push interface (cdr a))
	   alist)
	  (t
	   (gensym-cons (gensym-list key interface) alist)))))
    
(defun-allowing-unwind execute-parallel-remote-procedure-start
    (remote-procedure-declaration
      icp-interface
      argument-list
      execution-priority)
  (let ((socket-alist nil)
	(uses-by-handle-p
	  (loop with descriptions = (remote-procedure-argument-description-function
				      remote-procedure-declaration)
		for description-index from 0 below (var-count descriptions)
		for argument-type-or-class = (var-type-from-index descriptions description-index)
		for info = (var-rpc-info-from-index descriptions description-index)
		thereis (eq 'handle (remote-procedure-item-info-kind info)))))
    (if (g2-list-p icp-interface)
	(do-g2-list-elements (element icp-interface nil)
	  (when (and (framep element) (serve-item-p element))
	    (let ((icp-socket? (icp-socket-of-interface-object element)))
	      (setq socket-alist (add-interface-to-alist
				   element
				   socket-alist
				   (when (non-resumable-icp-socket-p icp-socket?)
				     (gensym-cons
				       (icp-protocol-version-for-output icp-socket?)
				       (item-references-enabled-p icp-socket?))))))))
	(do-g2-array-elements (element icp-interface nil)
	  (when (and (framep element) (serve-item-p element))
	    (let ((icp-socket? (icp-socket-of-interface-object element)))
	      (setq socket-alist (add-interface-to-alist
				   element
				   socket-alist
				   (when (non-resumable-icp-socket-p icp-socket?)
				     (gensym-cons
				       (icp-protocol-version-for-output icp-socket?)
				       (item-references-enabled-p icp-socket?)))))))))
    (loop for a in socket-alist
	  for (key . interface-list) = a
	  do
      (if (or uses-by-handle-p (null key) (null (cdr interface-list)))
	  (loop for interface in interface-list do
	    (execute-remote-procedure-start
	      remote-procedure-declaration interface argument-list execution-priority t))
	  (execute-fast-parallel-remote-procedure-start
	    remote-procedure-declaration argument-list execution-priority
	    (car key) (cdr key) interface-list))
      (when key (reclaim-gensym-cons key))
      (reclaim-gensym-list a))
    (reclaim-gensym-list socket-alist))
  (reclaim-rpc-argument-list argument-list nil))

(defun-void execute-fast-parallel-remote-procedure-start
    (remote-procedure-declaration argument-list execution-priority
     icp-version uses-item-references interface-list)
  (let* ((temporary-icp-socket (make-icp-socket nil 'temporary-output nil nil nil nil
						t nil current-system-name nil))
	 (temporary-output-port (icp-output-port temporary-icp-socket)))
    (setf (icp-socket-does-not-allow-resumability temporary-icp-socket) t)
    (setf (icp-protocol-version-for-output temporary-icp-socket) icp-version)
    (setf (icp-protocol-version-for-input temporary-icp-socket) icp-version)
    (setf (icp-socket-uses-item-references temporary-icp-socket) uses-item-references)
    (let ((inhibit-corresponding-icp-object-making t))
      (writing-icp-message-group (temporary-output-port)
	(execute-remote-procedure-start
	  remote-procedure-declaration current-icp-socket argument-list
	  execution-priority t)))
    (let ((icp-buffers
	    (let ((head (icp-buffer-queue-head temporary-output-port))
		  (tail (icp-buffer-queue-tail temporary-output-port)))
	      (unless (eq head tail)
		(prog1 (icp-buffer-next head)
		  (setf (icp-buffer-queue-tail temporary-output-port) head)
		  (setf (icp-buffer-next head) nil))))))
      (with-icp-buffer-coelescing-scope
	(loop for interface in interface-list
	      for icp-socket = (icp-socket-of-interface-object interface)
	      do
	  (writing-icp-message-group ((icp-output-port icp-socket))
	    (send-icp-define-temporary-index-space
	      (standard-icp-object-index-space temporary-output-port)))
	  (let ((current-icp-port (icp-output-port icp-socket))
		(icp-buffers-for-message-group
		  (copy-icp-buffer-chain icp-buffers)))
	    (transmit-completed-icp-message-group))
	  (writing-icp-message-group ((icp-output-port icp-socket))
	    (send-icp-release-temporary-index-space))))
      (reclaim-icp-buffer-list icp-buffers))
    (setf (icp-connection-state temporary-icp-socket) icp-connection-closed)
    (reclaim-icp-socket temporary-icp-socket)))

(defun-allowing-unwind execute-remote-procedure-start
       (remote-procedure-declaration
	 icp-interface
	 argument-list
	 execution-priority
	 do-not-reclaim-or-modify-argument-list)
  (when do-not-reclaim-or-modify-argument-list
    (setq argument-list (copy-list-using-eval-conses argument-list)))
  (let* ((interface-is-socket-p (icp-socket-p icp-interface))
	 (icp-socket? (if interface-is-socket-p
			  icp-interface
			  (icp-socket-of-interface-object icp-interface)))
	 (*current-computation-frame* remote-procedure-declaration)
	 (transform-error-message? nil))
    (cond
      ((or (null icp-socket?)
	   (=f (icp-connection-state icp-socket?) icp-connection-closed))
       (write-warning-message* 1
	 (tformat
	   "The ICP interface ~NF was unable to accept network messages to ~
              start ~NF, because it was not connected."
	   icp-interface
	   remote-procedure-declaration))
       (reclaim-rpc-argument-list argument-list do-not-reclaim-or-modify-argument-list))
      ((or (not (icp-connection-open-p icp-socket?))
	   (icp-connection-being-shutdown? icp-socket?))
       (let ((desc (icp-socket-description icp-socket?)))
	 (write-warning-message* 1
	   (tformat
	     "The ICP interface ~NF was unable to accept network messages to ~
              start ~NF.  The socket is ~A."
	     icp-interface
	     remote-procedure-declaration
	     desc))
	 (reclaim-text-string desc)
	 (reclaim-rpc-argument-list argument-list do-not-reclaim-or-modify-argument-list)))
      ((setq transform-error-message?
	     (transform-rpc-argument-or-result-list
	       remote-procedure-declaration
	       argument-list
	       (remote-procedure-argument-description-function
		 remote-procedure-declaration)
	       icp-socket?
	       (unless interface-is-socket-p icp-interface)
	       execution-priority
	       t))
       (write-warning-message* 1
	 (tformat
	   "The remote procedure ~NF could not be started ~
                 because of a problem with its arguments: ~A"
	   remote-procedure-declaration
	   transform-error-message?))
       (reclaim-rpc-argument-list argument-list do-not-reclaim-or-modify-argument-list))
      (t 
       (send-rpc-start
	 (icp-output-port icp-socket?)
	 execution-priority
	 (remote-procedure-name-structure remote-procedure-declaration)
	 argument-list
	 do-not-reclaim-or-modify-argument-list))))
  nil)

(defun-simple remote-procedure-arg-type-error-p-1 (type kind argument)
  (cond
    ((eq type 'item-or-datum)
     nil)
    ((framep argument)
     (if (not (class-type-specification-p type))
	 (tformat-text-string
	   "The argument ~NF was an item, ~
                      not a value of the required type ~A"
	   argument
	   type)
	 (let ((declared-class (second type))
	       (argument-class (class argument)))
	   (unless (subclassp argument-class declared-class)
	     (tformat-text-string
	       "The object argument ~NF was of class ~A, ~
                    not of the required class ~A."
	       argument
	       argument-class
	       declared-class)))))
    ((evaluation-value-p argument)
     (let* ((argument-type (evaluation-value-type argument))
	    (constant-value (evaluation-value-value argument))
	    (fixnum-type-p (eq argument-type 'integer)))
       (cond
	 ((class-type-specification-p type)
	  (unless (and (eq 'handle kind)
		       fixnum-type-p)
	    (twith-output-to-text-string
	      (twrite-string "The handle argument ")
	      (print-constant constant-value argument-type)
	      (tformat " for ~A was not of type integer."
		       type))))
	 (t (unless (if (symbolp type)
			(or (eq type 'datum)
			    (eq type argument-type)
			    (and (eq type 'number)
				 (or (eq argument-type 'float)
				     (eq argument-type 'integer))))
			(type-specification-type-p argument type))
	      (twith-output-to-text-string
		(twrite-string "The value argument ")
		(print-constant constant-value argument-type)
		(tformat " was not of the required type ~a." type)))))))
    (t
     (tformat-text-string
       "The argument ~A was not of the required type ~A"
       argument
       type))))

(defun-simple remote-procedure-arg-type-error-p
    (argument-type-descriptions argument-list)
  (let ((count (var-count argument-type-descriptions)))
    (if (=f 0 count)
 	(unless (null argument-list)
 	  (tformat-text-string
 	    "~D arguments were required, but ~D arguments were supplied"
 	    count (length argument-list)))
	(loop	for restp = nil then rest-arg-p
		for index = 0 then (if restp index (1+f index))
		for type = (var-type-from-index argument-type-descriptions index)
		for description = (var-general-description-from-index
				    argument-type-descriptions index)
		for kind = (getf description :kind)
		for rest-arg-p = (or restp (getf description :all-remaining))
		for argument-list-tail = argument-list then (cdr argument-list-tail)
		for argument = (car argument-list-tail)
		for error-text = (remote-procedure-arg-type-error-p-1 type kind argument)
		when error-text do (return error-text)
		until (or (null argument-list-tail)
			  (and (not rest-arg-p) (=f index (1-f count))))
		finally
		  (return
		    (unless (or rest-arg-p (=f (length argument-list) count))
		      (tformat-text-string
			"~D arguments were required, but ~D arguments were supplied"
			count (length argument-list))))))))



(defun make-vector-of-some-evaluation-values-for-remote-procedure (list)
  (let* ((vector-size (length list))
	 (arg-vector (when (> vector-size 0)
		       (allocate-managed-simple-vector vector-size))))
    (loop for evaluation-value-or-frame in list
	  for index from 0
	  do
      (setf (svref arg-vector index)
	    (if (evaluation-unsigned-vector-16-p evaluation-value-or-frame)
		(evaluation-unsigned-vector-16-value evaluation-value-or-frame)
		evaluation-value-or-frame)))
    (values arg-vector vector-size)))
	 




;;; The function `remote-procedure-call-authorized-p' is used to verify that a
;;; particular ICP socket is cleared by the security system to receive service
;;; from a particular procedure in the local system.  It receives an ICP-socket
;;; and the symbol which names the procedure the remote system would like to
;;; execute.  This function refuses service by returning NIL.

;;; At the moment this facility has not been designed, so all remote calls are
;;; immediately authorized.  -jra 3/13/90

;; The authorized-p predicate used to depend on nothing, but now it will depend on
;; the procedure being run, and eventually will also depend on the icp socket, the
;; g2 user, and the machine.  jh, 1/30/91.
;;
;; Next mod: item-remotely-visible (item-remotely-risible, hee hee hee) replaced by
;; item-remotely-callable-p.  Still only depends on the procedure name. ncc 20 Jan 1994 

(defun remote-procedure-call-authorized-p (procedure)
  (item-remotely-callable-p procedure))




;;; The function `receive-remote-procedure-error' is used to handle the
;;; RPC-error message.  It should post an error message on the logbook with the
;;; error and the name of the system which sent it.

;;; Note that at this point there is no good way to get an interface object
;;; associated with an ICP object.  So, for now the error message which just be
;;; posted without any identifying information.  -jra 3/13/90

(defun receive-remote-procedure-error
       (icp-socket error-name error-level error-description error-arglist)
  (declare (ignore error-name error-arglist))
  (let ((interface? (enclosing-interface-frame? icp-socket)))
    (if (and (framep-function interface?)
	     (frame-has-not-been-reprocessed-p
	       interface?
	       (enclosing-interface-frame-serial-number icp-socket)))
	(warning-message
	    error-level
	    "Error in remote procedure across interface ~NF: ~a"
	  interface? error-description)
	(warning-message
	    error-level
	    "Error in remote procedure: ~a"
	  error-description))))





(defun-simple get-copy-of-rpd-spec (rpd-vector key)
  (loop for index from 0 below (var-count rpd-vector)
	for description = (var-general-description-from-index rpd-vector index)
	collect (getf description key)
	  using icp-cons))

(defun-simple make-outgoing-remote-procedure-identifier-from-declaration (declaration)
  (let* ((return-descriptions
	   (remote-procedure-returned-values-description declaration))
	 (return-included-spec
	   (get-copy-of-rpd-spec return-descriptions :include-attributes))
	 (return-excluded-spec
	   (get-copy-of-rpd-spec return-descriptions :exclude-attributes))
	 (return-included-system-attribute-spec
	   (get-copy-of-rpd-spec return-descriptions :include-system-attributes))
	 (return-include-all-system-attribute-spec
	   (get-copy-of-rpd-spec return-descriptions :include-all-system-attributes))
	 (return-include-all-system-attribute-except-spec
	   (get-copy-of-rpd-spec return-descriptions :include-all-system-attributes-except))
	 (return-kind-spec
	   (get-copy-of-rpd-spec return-descriptions :kind))
	 (return-varargs-p
	   (and (<f 0 (var-count return-descriptions))
		(getf (var-general-description-from-index
			return-descriptions
			(1-f (var-count return-descriptions)))
		      :all-remaining))))
    (prog1 (make-outgoing-remote-procedure-identifier-with-info
	     return-included-spec
	     return-excluded-spec
	     return-included-system-attribute-spec
	     return-include-all-system-attribute-spec
	     return-include-all-system-attribute-except-spec
	     return-kind-spec
	     return-varargs-p)
      (reclaim-icp-list return-included-spec)
      (reclaim-icp-list return-excluded-spec)
      (reclaim-icp-list return-included-system-attribute-spec)
      (reclaim-icp-list return-include-all-system-attribute-spec)
      (reclaim-icp-list return-include-all-system-attribute-except-spec)
      (reclaim-icp-list return-kind-spec))))
      

;;; The function `call-remote-procedure' takes a remote-procedure-declaration,
;;; an ICP interface object, an argument list, and a calling code body
;;; invocation as arguments.  It will cause messages to be sent to the remote
;;; system to invoke a remote procedure, and set up a
;;; remote-procedure-invocation instance as a called-code-body of the given
;;; caller.  When values are returned from the remote system, then they will be
;;; returned to the given caller.

(defun-allowing-unwind call-remote-procedure
    (remote-procedure-declaration icp-interface argument-list calling-code-body)
  (let (argument-error-message? icp-socket? transform-error-message?)
    (cond ((setq argument-error-message?
		 (remote-procedure-arg-type-error-p
		   (remote-procedure-argument-description
		     remote-procedure-declaration)
		   argument-list))
	   (reclaim-rpc-argument-list argument-list nil)
	   (twith-output-to-error-text
	     (tformat "Argument error while calling remote procedure ~NF: ~a"
		      remote-procedure-declaration
		      argument-error-message?)
	     (reclaim-text-string argument-error-message?)))
	  ((or (null (setq icp-socket?
			   (icp-socket-of-interface-object icp-interface)))
	       (not (icp-connection-open-p icp-socket?))
	       (icp-connection-being-shutdown? icp-socket?))
	   (reclaim-rpc-argument-list argument-list nil)
	   (tformat-stack-error-text-string
	     "~NF is not able to receive remote procedure calls to ~NF.  ~
              Either the ICP connection has broken, or the remote system is ~
              not running."
	     icp-interface
	     remote-procedure-declaration))
	  ((setq transform-error-message?
		 (transform-rpc-argument-or-result-list
		   remote-procedure-declaration
		   argument-list
		   (remote-procedure-argument-description-function
		     remote-procedure-declaration)
		   icp-socket?
		   icp-interface
		   (code-body-invocation-priority calling-code-body)
		   t))
	   (tformat-stack-error-text-string
	     "Cannot execute remote procedure call to ~NF across ~NF, ~
              because of a problem in its arguments: ~A"
	     remote-procedure-declaration
	     icp-interface
	     transform-error-message?))
	  (t
	   (call-remote-procedure-after-checks
	     calling-code-body
	     argument-list
	     icp-socket?
	     remote-procedure-declaration
	     icp-interface)
	   nil))))







;;;; System Defined RPC's

(defvar system-defined-rpcs nil)
(def-global-property-name system-defined-rpc)

;; defun-for-system-procedure+
;; call-per-actual-number-of-arguments

(def-structure (system-rpc-instance
		 (:constructor make-system-rpc-instance
			       (system-rpc-instance-system-rpc 
				 system-rpc-instance-icp-socket
				 system-rpc-instance-identifier?)))
  (system-rpc-instance-system-rpc nil)
  (system-rpc-instance-icp-socket nil)
  (system-rpc-instance-identifier? nil))


;;; `defun-system-rpc' is like defun (actually defun-void because arg lists are
;;; simple and system-rpc's call a function to return values to remote caller)
;;; with the following additions.  All system rpc's take a system-rpc-instance
;;; as their fisrt arg.  All arguments and remote return values are specified in
;;; a prototype using type-specifications (see TYPES and SETS).

;; PLEASE DO: in events-g2 there is a function rpc-interface-class-ok?
;; that is designed to be used to restrict rpc calls to instances of a specific
;; rpc class (usually ui-client-interface for licensing reasons). This
;; test should be "burned" into defun-system-rpc in a manner equivalent
;; that used in define-system-rpc-access (actually, when doing this change,
;; define-system-rpc-access could be changed to piggy-back on the new
;; version of defun-system-rpc).

(defmacro defun-system-rpc ((name return-spec &key allow-unwind)
			    argument-spec &body body)
  (let ((first-arg-spec (car argument-spec))
	(function-name (build-ab-symbol name 'system-rpc-internal)))
    (unless (eq (cadr first-arg-spec) 'system-rpc-instance)
      (error "first argument for system rpc must be for system-rpc-instance"))
    `(progn
       (setf (system-defined-rpc ',name)
	     (make-system-rpc
	       ',function-name
	       (convert-description-list-to-managed-array
		 ',(loop for (arg-name arg-type) in (cdr argument-spec)
			 collect (list arg-name :type arg-type))
		 nil
		 t)
	       ',return-spec))
       (pushnew ',name system-defined-rpcs)
       (,(if allow-unwind 'defun-allowing-unwind 'defun-void) ,function-name
	   (,(car first-arg-spec)
	     ,@(loop for (arg-name arg-type) in (cdr argument-spec)
		     collect arg-name))
	 ,@body))))

(defvar current-system-rpc-icp-socket? nil)

(defmacro define-system-rpc-access ((name return-spec
					  &optional interface-class-name)
				    argument-spec
				    &body body)
  (let* ((rpc-instance-var (gensym))
	 (rpc-return-count (length return-spec))
	 (extra-return-var (gensym))
	 (rpc-return-value-names
	   (loop for i from 0 below rpc-return-count collect (gensym))))
    `(defun-system-rpc (,name ,return-spec :allow-unwind t)
	 ((,rpc-instance-var system-rpc-instance)
	  ,@argument-spec)
       (with-catch-handlers
	   (((:stack-error) (passed-top-of-stack error error-text
						 supress-debugging-info?)
	     passed-top-of-stack
	     supress-debugging-info?
	     (let ((error-text-string
		     (prog1 (error-text-string error-text)
		       (reclaim-error-text-but-not-string error-text))))
	       (system-rpc-error
		 ,rpc-instance-var error error-text-string))))
	 (let ((current-computation-flags current-computation-flags)
	       (current-system-rpc-icp-socket?
		 (system-rpc-instance-icp-socket ,rpc-instance-var))
	       ,@rpc-return-value-names
	       (,extra-return-var nil)
	       (return-list '()))
	   (setf (role-serve-inactive-objects?)
		 (icp-socket-runs-while-inactive
		   current-system-rpc-icp-socket?))
	   ;; check if the call is allowed for this interface
	   ,@(if interface-class-name
		 `((let ((interface?
			   (and current-system-rpc-icp-socket? ; paranoid
				(enclosing-interface-frame?
				  current-system-rpc-icp-socket?))))
		     (if (or (null interface?)
			     (not (frame-of-class-p
				    (enclosing-interface-frame?
				      current-system-rpc-icp-socket?)
				    ',interface-class-name)))
			 (stack-error cached-top-of-stack
				      "Call to ~A not available to interface ~NF"
				      ',name
				      (enclosing-interface-frame?
					current-system-rpc-icp-socket?))))))
	   (multiple-value-setq
	       (,@rpc-return-value-names ,extra-return-var)
	     (progn ,@body))
	   (setq return-list
		 (eval-list ,@rpc-return-value-names))
	   #+development
	   (when ,extra-return-var
	     (cerror "Continue, ignoring extra return values!"
		     "Too many return values from in a system procedure."))
	   (return-from-system-defined-rpc
	     ,rpc-instance-var return-list))))))

(defmacro rpc-arg-to-lisp-value (arg)
  arg)

(defun call-system-defined-rpc (icp-socket
				system-rpc
				rpc-arg-list
				remote-procedure-identifier?)
  ;; arg count error check here
  (unless (=f (length rpc-arg-list)
	      (var-count (system-rpc-argument-types system-rpc)))
    (remote-procedure-error
      icp-socket 'wrong-number-of-arguments
      (tformat-text-string
	"Error while beginning RPC call to ~ND: wanted ~NV args, got ~NV"
	(system-rpc-lisp-function system-rpc)
	(length rpc-arg-list)
	(var-count (system-rpc-argument-types system-rpc)))
      remote-procedure-identifier?))
  (loop with argument-list = '()
	with argument-types = (system-rpc-argument-types system-rpc)
        for rpc-arg in rpc-arg-list
	as lisp-arg = (rpc-arg-to-lisp-value rpc-arg)
	as index from 0
	as arg-type = (var-type-from-index argument-types index)
	
	do
    (eval-push lisp-arg argument-list)
    (unless (type-specification-type-p lisp-arg arg-type)
      (loop for thing in argument-list
	    do (reclaim-managed-number-or-value thing))
      (reclaim-eval-list argument-list)
      (reclaim-icp-list rpc-arg-list)
      (remote-procedure-error
	icp-socket
	'argument-type-mismatch
	(tformat-text-string
	  "Error while beginning RPC call to ~ND: arg ~NV should be of type ~NT"
	  (system-rpc-lisp-function system-rpc)
	  index arg-type) ; here print arg type and index
	remote-procedure-identifier?)
      (return))
	finally
	  (reclaim-icp-list rpc-arg-list)
	  (let ((apply-args (nreverse argument-list)))
	    (multiple-value-prog1
		(apply (system-rpc-lisp-function system-rpc)
		       (make-system-rpc-instance
			 system-rpc icp-socket remote-procedure-identifier?)
		       ;; some extra arg indicating return values and socket
		       apply-args)
	      (reclaim-eval-list apply-args)))))

(defmacro system-rpc-frame-handle (frame)
  `(frame-serial-number ,frame))

;;; `return-from-system-defined-rpc' sends the results of a system-defined
;;; rpc to it's caller.  It does not consume the lisp-value-list argument.
;;; It does reclaim the system-rpc-instance, because calls should only
;;; be returned from once.  It reclaims the system-rpc-instance.

(defun-allowing-unwind return-from-system-defined-rpc
    (system-rpc-instance rpc-value-list)
  (let ((identifier? (system-rpc-instance-identifier? system-rpc-instance)))
    (unless identifier?
      #+development
      (error "return-from-system-defined-rpc called, but rpc was invoked with start")
      #-development
      ()
      (return-from return-from-system-defined-rpc nil))
    (loop with system-rpc = (system-rpc-instance-system-rpc
			      system-rpc-instance)
	  with return-types = (system-rpc-return-types system-rpc)
	  for evaluation-value in rpc-value-list
	  for return-value-type in return-types
	  initially
	    #+development
	    (unless (=f (length return-types) (length rpc-value-list))
	      (error "wrong number of return args for system-defined rpc"))
	    #-development
	    ()
	  do
      #+development
      (unless (type-specification-type-p evaluation-value return-value-type)
	(error "bad return value for system-defined rpc"))
      #-development
      nil
	  finally
	    (let* ((socket (system-rpc-instance-icp-socket system-rpc-instance))
		   (output-port (icp-output-port socket))
		   (tag (remote-procedure-identifier-tag identifier?))
		   (info-list (remote-procedure-item-passing-info-item-info-list
				(remote-procedure-item-passing-info identifier?)))
		   (varargs-p (remote-procedure-item-passing-info-varargs-p
				(remote-procedure-item-passing-info identifier?))))
	      (reclaim-system-rpc-instance system-rpc-instance)
	      (transform-system-rpc-arguments socket rpc-value-list info-list nil varargs-p)
	      (with-bifurcated-version (resumable-icp-version (parent-icp-socket output-port))
		(progn
		  (send-icp-rpc-return-values-deferring-objects
		    output-port
		    tag
		    rpc-value-list)
		  (reclaim-after-rpc-return-values rpc-value-list))
		(send-or-enqueue-icp-write-task
		  output-port
		  6 ; execution-priority
		  #'send-icp-resumable-rpc-return-values
		  (icp-list tag rpc-value-list)
		  #'reclaim-after-rpc-return-values
		  (icp-list rpc-value-list)))))))

;;; `system-rpc-error' is the error signaller that should be called
;;; in a system-defined rpc or any of its sub-functions or spawned
;;; tasks.  The error-description arg is a text string which is consumed.

(defun system-rpc-error (system-rpc-instance error-name error-description)
  (remote-procedure-error
    (system-rpc-instance-icp-socket system-rpc-instance)
    error-name error-description
    (system-rpc-instance-identifier? system-rpc-instance)))

(defun-system-rpc (g2-api-test-1 (float))
    ((rpc-instance system-rpc-instance)
     (arg1 float))
  (with-temporary-gensym-float-creation g2-api-test1
    (let* ((res (*e 3.0 (managed-float-value arg1)))
	   (result-list (gensym-list (allocate-managed-float res))))
      (return-from-system-defined-rpc rpc-instance result-list)
      (reclaim-managed-float (car result-list))
      (reclaim-gensym-list result-list))))

;;; The function `evaluate-procedure-or-method-declaration' must be called in a
;;; context where *current-computation-frame* is bound.

(defun-simple evaluate-procedure-or-method-designation (name)
  (or (let ((current-computation-flags current-computation-flags)
	    (debugging-reset t))
	(setf (role-serve-inactive-objects?) t)
	(evaluate-designation name nil))
      (let* ((symbol-name (gensym-symbol-name name))
	     (position-of-qualifier? (gensym-search "::" symbol-name)))
	(and position-of-qualifier?
	     (let ((qualifying-class
		     (intern-gensym-string
		       (copy-partial-gensym-string
			 symbol-name
			 position-of-qualifier?)))
		   (method-declaration-name
		     (intern-gensym-string 
		       (copy-gensym-string-portion
			 symbol-name
			 (+f position-of-qualifier? 2)
			 (gensym-string-length symbol-name)))))
	       (car (get-specific-methods-for-class-or-superior-class
		      method-declaration-name
		      qualifying-class)))))))

(defvar prefer-kb-procedures-to-system-defined-p nil)

(defun-for-system-procedure g2-prefer-kb-procedures-to-system-defined
    (evaluation-truth-value)
  (setf prefer-kb-procedures-to-system-defined-p
	(evaluation-truth-value-is-true-p evaluation-truth-value))
  (reclaim-evaluation-truth-value evaluation-truth-value))

(define-system-rpc-access (g2-prefer-kb-procedures-to-system-defined ())
    ((prefer truth-value))
  (g2-prefer-kb-procedures-to-system-defined prefer))

(defun-simple check-that-remote-procedure-can-be-started-or-called
    (icp-socket name argument-list remote-procedure-identifier?)
  (let ((procedure nil)
	(method-or-error-string? nil)
	(*current-computation-frame* inference-engine-parameters)
	(system-rpc?
	  (unless (with-bifurcated-version-for-output (resumable-icp-version icp-socket)
		    t ; until we fix transform-system-rpc-arguments
		    (and prefer-kb-procedures-to-system-defined-p
		       (get-instance-with-name-if-any 'procedure name)))
	    (system-defined-rpc name)))
	(argument-error? nil)
	(how-invoked (if remote-procedure-identifier? "call" "start")))
    (multiple-value-bind (format-string arg1 arg2)
	(cond (system-rpc?
	       (setq procedure system-rpc?)
	       (cond (rpc-argument-list-error
		      (values "Cannot ~A ~A, since: ~A"
			      rpc-argument-list-error))
		     ((setq argument-error?
			    (get-procedure-argument-list-error-if-any
			      (setq procedure (or method-or-error-string? procedure))
			      argument-list icp-socket))
		      (values "Argument error ~Aing ~A:  ~A"
			      argument-error?))
		     (t
		       nil)))
	      ((null (setq procedure
			   (evaluate-procedure-or-method-designation name)))
	       (values "Cannot ~A ~A, since no procedure by that name exists."))
	      ((or (temporary-constant-p procedure) (evaluation-value-p procedure))
	       (values "Cannot ~A ~A, since it named the constant ~NC instead of a procedure."
		       procedure))
	      ((not (procedure-p procedure))
	       (values "Cannot ~A ~A, since it names ~A~A, instead of a procedure."
		       (supply-a-or-an (class procedure))
		       (class procedure)))
	      ((not (remote-procedure-call-authorized-p procedure))
	       (values "Cannot ~A ~A, since this interface is not authorized to start remote procedure calls."))
	      ((not (runnable-p procedure))
	       (values "Cannot ~A ~A, since it is not active or has a status other than OK."))
	      ((and (frame-of-class-p procedure 'method-declaration)
		    (text-string-p
		      (setq method-or-error-string?
			    (get-specific-method-for-arg-list-given-name
			      name argument-list icp-socket))))
	       (values "Cannot ~A ~A.  ~A"
		       method-or-error-string?))
	      (rpc-argument-list-error
	       (values "Cannot ~A ~A, since: ~A"
		       rpc-argument-list-error))
	      ((setq argument-error?
		     (get-procedure-argument-list-error-if-any
		       (setq procedure (or method-or-error-string? procedure))
		       argument-list icp-socket))
	       (values "Argument error ~Aing ~A:  ~A"
		       argument-error?)))
      (cond (format-string
	     (remote-procedure-error
	       icp-socket
	       'error
	       (tformat-text-string format-string how-invoked name arg1 arg2)
	       remote-procedure-identifier?)
	     (when (temporary-constant-p procedure) (reclaim-temporary-constant procedure))
	     (when (evaluation-value-p procedure) (reclaim-evaluation-value procedure))
	     (when argument-error? (reclaim-text-string argument-error?))
	     nil)
	    (t procedure)))))


;;; The simple function `plausible-remote-method-call-p' takes two arguments:
;;; remote-procedure-name-symbol and rpc-argument-list.  This function returns
;;; true if remote-procedure-name-symbol names a generic method and
;;; rpc-argument-list could be passed as arguments to that method

(defun-simple plausible-remote-method-call-p
    (remote-procedure-name-symbol rpc-argument-list)
  (and (get-instance-with-name-if-any
	 'method-declaration
	 remote-procedure-name-symbol)
       (receiving-resumable-object-p (car rpc-argument-list))))

;;; The simple function `receive-start-or-call-remote-procedure' is called on the target
;;; side of a remote procedure call.  It should initiate a call within the local
;;; G2.  If there is a problem with this call, then a RPC-error-to-caller
;;; message should be sent back, identifying the call with the identifier-tag
;;; from the remote-procedure-identifier already sent.

(defun-simple receive-start-or-call-remote-procedure
    (icp-socket procedure-name argument-list remote-procedure-identifier?)
  (let* ((initial-rpc-frame-serial-number (icp-pop argument-list))
	 (rpc-argument-list-error (icp-pop argument-list))
	 (procedure?
	   (check-that-remote-procedure-can-be-started-or-called
	     icp-socket
	     procedure-name
	     argument-list
	     remote-procedure-identifier?)))
    (cond ((null procedure?)
	   (reclaim-if-text-string rpc-argument-list-error)
	   (reclaim-unprocessed-rpc-argument-list argument-list initial-rpc-frame-serial-number))
	  ((system-rpc-p procedure?)
	   (call-system-defined-rpc
	     icp-socket procedure? argument-list remote-procedure-identifier?))
	  (inside-breakpoint-p
	   (with-current-scheduling (nil highest-system-priority)
	     (receive-start-or-call-remote-procedure-1
	       procedure? argument-list icp-socket remote-procedure-identifier?)))
	  (t
	   (receive-start-or-call-remote-procedure-1
	     procedure? argument-list icp-socket remote-procedure-identifier?)))
    (reclaim-frame-serial-number initial-rpc-frame-serial-number)))



(defun-allowing-unwind receive-start-or-call-remote-procedure-1
    (procedure argument-list icp-socket remote-procedure-identifier?)
  (multiple-value-bind (arg-vector arg-vector-size)
      (make-vector-of-some-evaluation-values-for-remote-procedure argument-list)
    (reclaim-icp-list argument-list)
    (let* ((*current-computation-frame* procedure)
	   (remote-procedure-call
	     (when t ; remote-procedure-identifier?
	       (make-incoming-remote-procedure-call remote-procedure-identifier? icp-socket)))
	   (new-invocation-or-error-text
	     (if remote-procedure-call
		 (generate-procedure-and-code-body-invocation-in-place
		   procedure remote-procedure-call
		   arg-vector (-f arg-vector-size 1) arg-vector-size
		   nil nil :error-string nil nil nil)
		 (start-procedure-invocation-in-place
		   procedure nil nil
		   arg-vector (-f arg-vector-size 1) arg-vector-size
		   nil nil :error-string nil nil)))
	   (new-invocation
	     (if (error-text-p new-invocation-or-error-text)
		 (progn
		   (remote-procedure-error
		     icp-socket
		     'rpc-error
		     (tformat-text-string
		       "Error while beginning RPC start of ~NF: ~NW"
		       procedure
		       new-invocation-or-error-text)
		     remote-procedure-identifier?)
		   (reclaim-error-text new-invocation-or-error-text)
		   nil)
		 new-invocation-or-error-text)))
      (when arg-vector
	(reclaim-managed-simple-vector arg-vector))
      (when new-invocation
	(when remote-procedure-call
	  (if remote-procedure-identifier?
	      (setf (remote-procedure-identifier-callee remote-procedure-identifier?)
		    remote-procedure-call)
	      (register-remote-procedure-call-for-start remote-procedure-call icp-socket))
	  (wake-up-code-body-invocation new-invocation))
	(write-major-trace-for-rpc-call-or-start
	  new-invocation remote-procedure-identifier?)))))

(defun find-remote-procedure-call-for-code-body-invocation (code-body-invocation)
  #| ; Maybe this is equivalent?
  (calling-code-body-invocation
    (local-base-of-procedure-invocation-stack
      (procedure-invocation-of-code-body code-body-invocation)))
  |#
  (loop	for caller? = (code-body-caller code-body-invocation)
		    then (code-body-caller caller?)
	while caller?
	when (remote-procedure-call-p caller?)
	  return caller?))

(defun get-icp-interface-for-remote-procedure-call (remote-procedure-call stack-eval-p)
  (let ((interface? (remote-procedure-call-icp-interface remote-procedure-call)))
    (if (and interface?
	     (frame-has-not-been-reprocessed-p
	       interface?
	       (code-body-invocation-frame-serial-number
		 remote-procedure-call)))
	interface?
	(let ((interface (find-network-interface-for-icp-socket
			   (remote-procedure-call-icp-socket remote-procedure-call)
			   stack-eval-p)))
	  (setf (remote-procedure-call-icp-interface remote-procedure-call)
		interface)
	  (frame-serial-number-setf (code-body-invocation-frame-serial-number remote-procedure-call)
				    (frame-serial-number interface))
	  interface))))

(declare-system-procedure-function g2-current-remote-interface-lisp-side nil)

(defun-funcallable g2-current-remote-interface-lisp-side ()
  (get-icp-interface-for-remote-procedure-call
    (or (find-remote-procedure-call-for-code-body-invocation
	  current-computation-instance)
	(stack-error cached-top-of-stack
		     "The current procedure was not invoked via RPC"))
    t))


(defun write-major-trace-for-rpc-call-or-start (new-invocation call-p)
  (write-major-trace-message
    (twrite-string (if call-p "Calling procedure " "Starting procedure "))
    (write-procedure-invocation-instance-from-slot
      (procedure-invocation-of-code-body new-invocation) nil)
    (twrite-string " for remote system.")))

;;; The function `error-starting-remote-procedure' is called by the
;;; receive-remote-procedure-start function to send back an error message.
;;; This function should send back and RPC-error message containing the given
;;; error description.

;;; Note that errors are quite simple in G2 now, but the error message protocol
;;; has been written such that it will support named error types and arguments
;;; to an error type, as well as the error level and error description.  -jra
;;; 3/13/90

;;; The function `error-calling-remote-procedure' is used in a target G2 to send
;;; back an error message to the source about an error which occurred which
;;; attempting to launch the call to a remote procedure.  The
;;; remote-procedure-identifier has not had its called-procedure-invocation slot
;;; set yet, so the identifier need not be changed.

(defun-simple remote-procedure-error
    (icp-socket name error-string remote-procedure-identifier?)
  (remote-procedure-error-1 icp-socket
			    name 1 error-string
			    remote-procedure-identifier? name))

(defun-allowing-unwind remote-procedure-error-1
    (icp-socket error-name error-level error-message remote-procedure-identifier? error)
  (unless icp-socket
    (propagate-error-to-remote-caller-reclaim error-message nil)
    (return-from remote-procedure-error-1 nil))
  (let ((remote-procedure-index?
	  (when remote-procedure-identifier?
	    (remote-procedure-identifier-tag remote-procedure-identifier?)))
	(output-port (icp-output-port icp-socket)))
    (with-bifurcated-version (resumable-icp-version icp-socket)
      (progn
	(writing-icp-message-group (output-port)
	  (if remote-procedure-identifier?
	      (send-icp-rpc-error-to-caller
		remote-procedure-index? nil
		error-name error-level error-message nil)
	      (send-icp-rpc-error
		error-name error-level error-message nil)))
	(propagate-error-to-remote-caller-reclaim error-message nil))
      (progn
	(when (and error (symbolp error))
	  (setq error-name error)
	  (setq error nil))
	(let ((error-arguments
		(if error
		    (icp-list (icp-list 'copy error
					(make-remote-procedure-item-info nil nil nil t nil nil)
					nil))
		    (icp-list (icp-cons 'value error-name)
			      (icp-cons 'value (copy-text-string error-message))))))
	  (send-or-enqueue-icp-write-task
	    output-port
	    6 ; execution-priority
	    (if remote-procedure-identifier?
		#'send-icp-resumable-rpc-error-to-caller
		#'send-icp-resumable-rpc-error)
	    (let ((args (icp-list error-name error-level error-message error-arguments)))
	      (if remote-procedure-identifier?
		  (nconc (icp-list remote-procedure-index? nil) args)
		  args))
	    #'propagate-error-to-remote-caller-reclaim
	    (icp-list error-message error-arguments)))))))

(defun-void propagate-error-to-remote-caller-reclaim (error-message error-arguments)
  (reclaim-text-string error-message)
  (when error-arguments
    (let ((error (when (and error-arguments (null (cdr error-arguments)))
		   (second (first error-arguments)))))
      (if (and (framep error)
	       (transient-p error))
	  (delete-frame error)))
    (reclaim-transformed-rpc-argument-list error-arguments nil)))



(defun-void register-remote-procedure-call-for-start (remote-procedure-call icp-socket)
  (let ((map (remote-procedure-call-start-map icp-socket)))
    (unless map
      (setq map (make-index-space 'remote-procedure-call-start-map
				  'remove-remote-procedure-calls-from-start-map))
      (setf (remote-procedure-call-start-map icp-socket) map)
      (enlarge-index-space map 20))
    (let ((index (assign-index-in-index-space map)))
      (store-object-in-index-space map index remote-procedure-call)
      (setf (remote-procedure-call-start-index remote-procedure-call) index))))

(defun-void deregister-remote-procedure-call-for-start (remote-procedure-call)
  (let ((icp-socket (remote-procedure-call-icp-socket remote-procedure-call)))
    (when icp-socket
      (let ((map (remote-procedure-call-start-map icp-socket))
	    (index (remote-procedure-call-start-index remote-procedure-call)))
	(store-object-in-index-space map index nil)
	(deassign-index-in-index-space index map)
	(setf (remote-procedure-call-icp-socket remote-procedure-call) nil)
	(setf (remote-procedure-call-start-index remote-procedure-call) -1)))))

; reclaim-remote-procedure-call-start-map is defined in int1.lisp
 
(defun-void remove-remote-procedure-calls-from-start-map (object index-space-name shutdownp)
  (declare (ignore index-space-name shutdownp))
  (when (remote-procedure-call-p object)
    (let ((remote-procedure-call object))
      (setf (remote-procedure-call-icp-socket remote-procedure-call) nil)
      (setf (remote-procedure-call-start-index remote-procedure-call) -1))))

;;; The function `return-values-to-remote-caller' is called by the RETURN-VALUES
;;; procedure instruction when values are being returned through a
;;; remote-procedure-call.

;; Obsolete in 3.0: return-values-to-remote-caller.



(defun-allowing-unwind return-stack-values-to-remote-caller
    (remote-procedure-call 
      stack top-of-stack values-on-stack
      returning-code-body-invocation)
  (cond
    ((null (remote-procedure-identifier-of-call remote-procedure-call))
     (let ((returning-procedure-invocation
	     (procedure-invocation-of-code-body returning-code-body-invocation)))
       (loop with returning-procedure = (procedure-of-invocation returning-procedure-invocation)
	     with return-descriptions = (returned-values-description returning-procedure)
	     for index from (+f (-f top-of-stack values-on-stack) 1)
	     for value-or-object = (svref stack index)
	     for description-index from 0 below (var-count return-descriptions)
	     do (reclaim-if-evaluation-value value-or-object))
       (setf (code-body-caller returning-code-body-invocation) nil)
       (setf (called-code-bodies remote-procedure-call)
	     (delete-proc-element
	       returning-code-body-invocation
	       (called-code-bodies remote-procedure-call)))
       (deregister-remote-procedure-call-for-start remote-procedure-call)
       (reclaim-incoming-remote-procedure-call remote-procedure-call)))
    (t
     (let* ((remote-procedure-identifier
	      (remote-procedure-identifier-of-call remote-procedure-call))
	    (returning-procedure-invocation
	      (procedure-invocation-of-code-body returning-code-body-invocation))
	    (icp-socket
	      (remote-procedure-call-icp-socket remote-procedure-call))
	    (returning-procedure
	      (procedure-of-invocation returning-procedure-invocation))
	    (return-descriptions
	      (returned-values-description returning-procedure))
	    (exit-message?
	      (exit-trace-messages-will-be-written-p returning-procedure))
	    (argument-strings-for-trace nil)
	    (return-results-list nil)
	    (cached-top-of-stack top-of-stack))
       (loop for index from (+f (-f top-of-stack values-on-stack) 1)
	     for value-or-object = (svref stack index)
	     for description-index from 0 below (var-count return-descriptions)
	     for return-type =
	     (var-type-from-index return-descriptions description-index)
	     for return-description
		 = (var-general-description-from-index return-descriptions description-index)
	     do
	 (let ((invalidity-message?
		 (invalid-stack-value-or-object-for-return-to-remote-caller?
		   value-or-object return-type return-description)))
	   (cond
	     (invalidity-message?
	      (reclaim-rpc-argument-list results nil)
	      (when exit-message?
		(loop for string in argument-strings-for-trace do
		  (reclaim-text-string string))
		(reclaim-proc-list argument-strings-for-trace))
	      (write-stack-error cached-top-of-stack
		(tformat "~A" invalidity-message?)
		(reclaim-text-string invalidity-message?)))
	     (t (when exit-message?
		  (proc-push (twith-output-to-text-string
			       (if (evaluation-value-p value-or-object)
				   (write-evaluation-value value-or-object)
				   (tformat "~NF" value-or-object)))
			     argument-strings-for-trace))
		(setf (svref stack index) nil))))
	     collect value-or-object
	       into results using eval-cons
	     finally
	       (let ((transform-error-message?
		       (transform-rpc-argument-or-result-list
			 (remote-procedure-declaration-of-call
			   remote-procedure-call)
			 results
			 return-descriptions
			 icp-socket
			 (get-icp-interface-for-remote-procedure-call
			   remote-procedure-call
			   t)
			 (get-rpc-priority-from-computation-context)
			 nil
			 (remote-procedure-item-passing-info-item-info-list
			   (remote-procedure-item-passing-info remote-procedure-identifier))
			 (remote-procedure-item-passing-info-varargs-p
			   (remote-procedure-item-passing-info remote-procedure-identifier)))))
		 (cond
		   (transform-error-message?
		    (reclaim-rpc-argument-list results nil)
		    (when exit-message?
		      (loop for string in argument-strings-for-trace do
			(reclaim-text-string string))
		      (reclaim-proc-list argument-strings-for-trace))
		    (write-stack-error cached-top-of-stack
		      (tformat "~A" transform-error-message?)
		      (reclaim-text-string transform-error-message?)))
		   (t (exit-tracing-and-breakpoint-context
			returning-procedure
			(and exit-message?
			     (remote-return-exit-message
			       returning-procedure-invocation
			       (nreverse argument-strings-for-trace))))
		      (setq return-results-list results)))))
       (reclaim-rpc-and-invocation-after-rpc-return-values
	 remote-procedure-call returning-code-body-invocation)
       (send-rpc-return-values
	 (icp-output-port (remote-procedure-call-icp-socket remote-procedure-call))
	 (code-body-invocation-priority returning-code-body-invocation)
	 (remote-procedure-identifier-tag remote-procedure-identifier)
	 return-results-list))))
  nil)

(defun reclaim-rpc-and-invocation-after-rpc-return-values
    (remote-procedure-call returning-code-body-invocation)
  (let ((remote-procedure-identifier
	  (remote-procedure-identifier-of-call remote-procedure-call)))
    (setf (remote-procedure-identifier-callee remote-procedure-identifier) nil))
  (setf (code-body-caller returning-code-body-invocation) nil)
  (setf (called-code-bodies remote-procedure-call)
	(delete-proc-element
	  returning-code-body-invocation
	  (called-code-bodies remote-procedure-call)))
  (reclaim-incoming-remote-procedure-call remote-procedure-call))

(defun reclaim-after-rpc-return-values (return-results-list)
  (reclaim-transformed-rpc-argument-list return-results-list nil))

;;; The function `invalid-stack-value-or-object-for-return-to-remote-caller?'
;;; returns nil if its first argument is valid to be sent across ICP for remote
;;; procedure return, relative to its second argument, a type description.  If
;;; the first argument is invalid, this function returns a text string
;;; describing the problem, which it is the caller's responsibility to reclaim.

(defun invalid-stack-value-or-object-for-return-to-remote-caller?
    (value-or-object return-type return-description)
  (cond
    ((eq return-type 'item-or-datum)
     nil)
    ((not (class-type-specification-p return-type))
     (when (framep value-or-object)
       (tformat-text-string
	 "Attempting to return an object of class ~A ~
             to a remote procedure caller.  The caller ~
             expects a value of type ~A instead."
	 (class value-or-object)
	 return-type)))
    ((framep value-or-object)
     (let ((return-class (second return-type))
	   (class-of-frame (class value-or-object)))
       (unless (subclassp class-of-frame return-class)
	 (tformat-text-string
	   "Attempting to return an object of class ~A ~
                    to a remote procedure caller.  This object ~
                    is not of the declared class ~A."
	   class-of-frame
	   return-class))))
    (t
     (let ((as-handle-p (eq 'handle (getf return-description :kind))))
       (unless (and as-handle-p (evaluation-integer-p value-or-object))
	 (twith-output-to-text-string
	   (twrite-string "Attempting to return ")
	   (write-evaluation-value value-or-object)
	   (tformat
	     " to a remote procedure caller.  The caller ~
                      expects an object of class ~A instead."
	     return-type)))))))


(defun-simple remote-return-exit-message
	      (procedure-invocation return-value-strings)
  (twith-output-to-text-string
    (twrite-string "Returning values (")
    (loop for string in return-value-strings
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (twrite-string string)
      (reclaim-text-string string))
    (reclaim-proc-list return-value-strings)
    (twrite-string ") from ")
    (write-procedure-invocation-instance-from-slot procedure-invocation nil)
    (twrite-string " to a remote caller.")))




;;; The function `receive-remote-procedure-values' is called by the message
;;; handler for the message which returns values from a remote system back to
;;; the caller of a remote procedure call.  Note that this function may be
;;; called after an abort for this call has been issued, in which case this
;;; function should ignore the values and return.  If the values are being
;;; returned to a valid ongoing remote procedure call, these values should be
;;; stored back into the calling environment, and this procedure should be
;;; rescheduled for execution.

(defun-allowing-unwind receive-remote-procedure-values 
    (remote-procedure-identifier returned-values)
  (let* ((initial-rpc-frame-serial-number (icp-pop returned-values))
	 (rpc-argument-list-error (icp-pop returned-values))
	 (remote-procedure-call
	   (when remote-procedure-identifier
	     (remote-procedure-identifier-caller remote-procedure-identifier)))
	 (caller
	   (or (when remote-procedure-call
		 (code-body-caller remote-procedure-call))
	       (return-from receive-remote-procedure-values nil)))
	 ;; In some cases we can know that this is NIL, optimize those in the
	 ;; future.  -jra & jh 5/23/95
	 (receiving-passed-items? t)
	 (remote-procedure-declaration
	   (remote-procedure-declaration-of-call remote-procedure-call))
	 (return-descriptions
	   (remote-procedure-returned-values-description
	     remote-procedure-declaration))
	 (formal-return-restp-index nil)
	 (caller-procedure-invocation
	   (procedure-invocation-of-code-body caller))
	 (*current-computation-frame*
	   (procedure-of-invocation caller-procedure-invocation))
	 (calling-environment
	   (invocation-local-var-vector caller))
	 (position (invocation-return-value-position caller))
	 (values-count (length returned-values))
	 (count (invocation-return-value-count caller)))
    (declare (type fixnum values-count count))
    (setf (called-code-bodies caller)
	  (delete-proc-element remote-procedure-call
			       (called-code-bodies caller)))
    (reclaim-outgoing-remote-procedure-identifier-and-index remote-procedure-identifier)
    (reclaim-outgoing-remote-procedure-call remote-procedure-call)
    (let ((i (1-f (var-count return-descriptions))))
      (when (and (<=f 0 i)
		 (getf (var-general-description-from-index return-descriptions i)
		       :all-remaining))
	(setq formal-return-restp-index i)))
    (let ((error-message?
	    (cond (rpc-argument-list-error
		   (tformat-text-string
		     "Cannot return results from the remote procedure ~NF, since ~A"
		     remote-procedure-declaration
		     rpc-argument-list-error))
		  ((if formal-return-restp-index
		       (<f values-count (1-f (var-count return-descriptions)))
		       (/=f values-count (var-count return-descriptions)))
		   (tformat-text-string
		     "~A values were returned, but the remote procedure declaration ~
                      ~NF declares that ~a values would be returned."
		     values-count
		     remote-procedure-declaration
		     (var-count return-descriptions)))
		  ((>f count values-count)
		   (tformat-text-string
		     "Procedure ~NF is requesting more values than ~NF can return."
		     (procedure-of-invocation
		       (procedure-invocation-of-code-body caller))
		     remote-procedure-declaration))
		  (t
		   ;; Note that when we are about to modify the caller environment in
		   ;; a way that leaves new items in it, then we must validate its
		   ;; environment, perform the modifications, then update the frame
		   ;; serial number of the caller.
		   (when receiving-passed-items?
		     (validate-computation-instance-environment
		       caller nil t))
		   (receive-remote-procedure-values-1
		     position
		     count
		     returned-values
		     return-descriptions
		     remote-procedure-declaration
		     calling-environment)))))
      ;; Use count to determine how many returned-values need to be not
      ;; reclaimed because they were handled.  HQ-4099514 - "Ignoring return
      ;; value of RPC leaks" -dkuznick, 10/23/01
      (reclaim-unprocessed-rpc-argument-list returned-values
					     initial-rpc-frame-serial-number
					     (unless error-message? count))
      (cond
	(error-message?
	 (reclaim-if-text-string rpc-argument-list-error)
	 (signal-code-body-invocation-error
	   caller 'rpc-error 1 error-message?
	   nil nil nil nil nil))
	(t
	 (when receiving-passed-items?
	   (update-code-body-invocation-frame-serial-number-ignoring-callers
	     caller))
	 (wake-up-code-body-invocation caller)))
      (reclaim-frame-serial-number initial-rpc-frame-serial-number))))

;; jh, 4/25/94.  Modified
;; new-receive-remote-procedure-values-inside-catch-handlers to convert handles
;; to the objects they handle.  See the comments above the system procedure
;; register-on-network-lisp-side for further details, including why we store the
;; handle in the icp-output-port.

(defun receive-remote-procedure-values-1
    (position
      count
      returned-values
      return-descriptions
      remote-procedure-declaration
      calling-environment)
  (loop for index from position below (+f position count)
	for value-or-object in returned-values
	for rest-return-p = nil then (or rest-return-p restp)
	for description-index = 0 then (if rest-return-p
					   description-index
					   (1+f description-index))
	for return-type = (var-type-from-index return-descriptions description-index)
	for return-description  = (var-general-description-from-index
				    return-descriptions description-index)
	for restp = (or rest-return-p (getf return-description :all-remaining))
	for kind = (getf return-description :kind)
	do
    (when (evaluation-unsigned-vector-16-p value-or-object)
      (setq value-or-object
	    (evaluation-unsigned-vector-16-value value-or-object)))		
    (unless (type-specification-type-p value-or-object return-type)
      (let* ((as-handle-p (eq 'handle kind))
	     (handled-object?
	       (and as-handle-p
		    (evaluation-integer-p value-or-object)
		    (get-item-from-local-handle
		      (evaluation-integer-value value-or-object)
		      current-icp-socket))))
	(cond
	  ((and handled-object?
		(type-specification-type-p handled-object? return-type))
	   (setq value-or-object handled-object?))
	  (t
	   (loop for index from position below (+f position count)
		 do (setf (svref calling-environment index) nil))
	   (return-from receive-remote-procedure-values-1
	     (twith-output-to-text-string
	       (tformat "The returned value at position ~D, "
			(-f index position))
	       (if (evaluation-value-p value-or-object)
		   (write-evaluation-value value-or-object)
		   (tformat "~NF" value-or-object))
	       (tformat " was not of the type ~NT, as required by the ~
                          declaration for ~NF."
			return-type
			remote-procedure-declaration)))))))
    (setf (svref calling-environment index) value-or-object))
  nil)






;;; The function `receive-remote-procedure-error-for-caller' is called from the
;;; message handler which propagates error messages back from a remote procedure
;;; call into the calling G2 environment.  This function should pass the error
;;; into the code-body-invocation which is waiting for the given remote
;;; procedure call to complete.  It should not, however, reclaim the
;;; remote-procedure-call, remote-procedure-identifier, or issue an abort
;;; command.  The handlers for the base of the stack which will eventually
;;; handle the error should give the command to abort the stack, and the abort
;;; should cause all structures to be reclaimed.  Note that this message could
;;; be received after this remote-procedure-call has been aborted (but before
;;; the abort has been acknowledged).  In this case, this function should do
;;; nothing.

(defun receive-remote-procedure-error-for-caller
       (remote-procedure-identifier? signalling-invocation?
	error error-level error-description)
  (declare (ignore signalling-invocation?))
  (with-backtrace-for-internal-error 'receive-remote-procedure-error-for-caller
    (let* ((resumable-objects?
	     (when remote-procedure-identifier?
	       (remote-procedure-identifier-resumable-objects
		 remote-procedure-identifier?)))
	   (remote-procedure-call?
	     (when remote-procedure-identifier?
	       (remote-procedure-identifier-caller remote-procedure-identifier?)))
	   (caller?
	     (when remote-procedure-call?
	       (code-body-caller remote-procedure-call?))))
      (when resumable-objects?
	(loop for resumable-object in resumable-objects?
	      do
	  (g2-reclaim-sending-resumable-object resumable-object))
	;; jh, 9/28/94.  The icp-list in resumable-objects? has already been
	;; reclaimed by successive delete-icp-element calls in
	;; g2-reclaim-sending-resumable-object.  Don't re-reclaim here!
	(setf (remote-procedure-identifier-resumable-objects
		remote-procedure-identifier?)
	      nil))
      (if caller?
	  (propagate-error-to-code-body-invocation
	    caller? error error-level
	    (copy-text-string error-description))
	  (receive-remote-procedure-error
	    current-icp-socket error error-level error-description nil)))))






;;; The function `remote-procedure-call-being-aborted' is called when a
;;; procedure invocation invoked through a remote procedure call is aborted.
;;; This remote-procedure-call should send back an error message to its caller,
;;; and then reclaim itself and disconnect itself from the procedure invocation.
;;; This is an uncontinuable error, so all the remote caller can do is abort the
;;; call.

;;; The reason, if given, should be a string, which is reclaimed by this
;;; function.

(defun remote-procedure-call-being-aborted (remote-procedure-call reason-string? error)
  (let* ((remote-procedure-identifier?
	   (remote-procedure-identifier-of-call remote-procedure-call))
	 (called-code-body (car (called-code-bodies remote-procedure-call)))
	 (called-procedure-invocation
	   (when called-code-body
	     (procedure-invocation-of-code-body called-code-body)))
	 (local-host-name? (get-local-host-name)))
    (remote-procedure-error-1
      (remote-procedure-call-icp-socket remote-procedure-call)
      'rpc-error
      1
      (twith-output-to-text-string
	(twrite-string (if remote-procedure-identifier?
			   "Remote procedure call to "
			   "Remote procedure start to "))
	(if called-procedure-invocation
	    (write-procedure-invocation-instance-from-slot
	      called-procedure-invocation nil)
	    (twrite-string "<already deleted procedure invocation>"))
	(twrite-string " is being aborted on the remote system")
	(when local-host-name?
	  (tformat " ~a" local-host-name?))
	(if reason-string?
	    (tformat " for the following reason:~%~a" reason-string?)
	    (twrite-string ".")))
      (remote-procedure-identifier-of-call remote-procedure-call)
      error)
    (reclaim-error-text reason-string?)
    (when called-procedure-invocation
      (setf (code-body-caller called-code-body) nil)
      (setf (called-code-bodies remote-procedure-call)
	    (delete-proc-element called-code-body
				 (called-code-bodies remote-procedure-call))))
    (setf (remote-procedure-identifier-of-call remote-procedure-call) nil)
    (if remote-procedure-identifier?
	(setf (remote-procedure-identifier-callee remote-procedure-identifier?) nil)
	(deregister-remote-procedure-call-for-start remote-procedure-call))
    (reclaim-incoming-remote-procedure-call remote-procedure-call)))




;;; The function `abort-rpc-call-and-reclaim-identifier' is called when an ICP
;;; connection has been lost, and there is an existing remote-procedure-
;;; identifier on the server side of a connection.  In this situation, any
;;; ongoing procedure stack for this identifier should be aborted, and the
;;; remote-procedure-identifier should be reclaimed.  Note that the
;;; remote-procedure-call and the procedure-invocation for that call may be
;;; missing, if it has already returned or been aborted.  In that case, clean up
;;; only what is left.

(defun abort-incoming-rpc-call (remote-procedure-call)
  (let ((base-code-body-invocation
	  (car (called-code-bodies remote-procedure-call))))
    (when base-code-body-invocation
      (setf (code-body-caller base-code-body-invocation) nil)
      (setf (called-code-bodies remote-procedure-call)
	    (delete-proc-element
	      base-code-body-invocation
	      (called-code-bodies remote-procedure-call)))
      (let ((base-procedure-invocation
	      (procedure-invocation-of-code-body base-code-body-invocation)))
	(when base-procedure-invocation
	  (abort-procedure-invocation base-procedure-invocation)))))
  (reclaim-incoming-remote-procedure-call remote-procedure-call)
  nil)

;called upon connection-loss
(defun abort-rpc-call-and-reclaim-identifier (remote-procedure-identifier)
  (let ((remote-procedure-call
	  (remote-procedure-identifier-callee remote-procedure-identifier)))
    (when remote-procedure-call
      (abort-incoming-rpc-call remote-procedure-call))
    (reclaim-incoming-remote-procedure-identifier remote-procedure-identifier)
    nil))



;;; The function `signal-error-to-rpc-caller-and-reclaim-identifier' is called
;;; when an ICP connection has been lost, and there is an existing
;;; remote-procedure-identifier on the client side of a connection.  In this
;;; situation, the remote-procedure-identifier should detach itself and any
;;; remote-procedure-call from any ongoing caller of this RPC, and then signal
;;; an error into the calling code-body-invocation.  If any of these data
;;; structures are not hooked up to the identifier for some reason, clean up
;;; only what is available.

(defun signal-error-to-rpc-caller-and-reclaim-identifier
       (remote-procedure-identifier)
  (let* ((remote-procedure-call
	   (remote-procedure-identifier-caller remote-procedure-identifier))
	 (caller
	   (when remote-procedure-call
	     (code-body-caller remote-procedure-call))))
    (when remote-procedure-call
      (when caller
	(setf (called-code-bodies caller)
	      (delete-proc-element remote-procedure-call
				   (called-code-bodies caller)))
	(signal-code-body-invocation-error
	  caller 'rpc-error 1
	  (twith-output-to-error-text
	    (twrite-string "The ICP connection")
	    (let ((interface? (remote-procedure-call-icp-interface
				remote-procedure-call)))
	      (when (and interface?
			 (frame-has-not-been-reprocessed-p
			   interface?
			   (code-body-invocation-frame-serial-number
			     remote-procedure-call)))
		(tformat " for the interface ~NF" interface?)))
	    (tformat
	      " has broken.  It was used for the remote call to ~NF."
	      (remote-procedure-declaration-of-call
		remote-procedure-call)))
	  nil nil nil nil nil))
      (reclaim-outgoing-remote-procedure-call remote-procedure-call))
    (reclaim-outgoing-remote-procedure-identifier-and-index remote-procedure-identifier)
    nil))




;;; The function `abort-remote-procedure-call' is used by a source of a remote
;;; procedure call to abort an ongoing procedure call in a remote system.  This
;;; function takes the remote-procedure-call structure.  Note that for now we
;;; only have asynchronous aborts.  When the CALL ABORT language is added to the
;;; grammar, then we will have to add functionality here to possibly send
;;; synchronous abort messages.

(defun-allowing-unwind abort-outgoing-remote-procedure-call (remote-procedure-call)
  (with-backtrace-for-internal-error 'abort-outgoing-remote-procedure-call
    (let* ((remote-procedure-identifier?
	     (remote-procedure-identifier-of-call remote-procedure-call))
	   (icp-socket?
	     (remote-procedure-call-icp-socket remote-procedure-call))
	   (code-body-caller? (code-body-caller remote-procedure-call)))
      (when code-body-caller?
	(setf (called-code-bodies code-body-caller?)
	      (delete-proc-element remote-procedure-call
				   (called-code-bodies code-body-caller?)))
	(setf (code-body-caller remote-procedure-call) nil))
      (when remote-procedure-identifier?
	(setf (remote-procedure-identifier-caller remote-procedure-identifier?) nil))
      (reclaim-outgoing-remote-procedure-call remote-procedure-call)
      (when remote-procedure-identifier?
	(let ((resumable-objects?
		(remote-procedure-identifier-resumable-objects
		  remote-procedure-identifier?)))
	  (when resumable-objects?
	    (loop for resumable-object in resumable-objects?
		  do (g2-reclaim-sending-resumable-object resumable-object))
	    ;; jh, 9/28/94.  The icp-list in resumable-objects? has already been
	    ;; reclaimed by successive delete-icp-element calls in
	    ;; g2-reclaim-sending-resumable-object.  Don't re-reclaim here!
	    (setf (remote-procedure-identifier-resumable-objects
		    remote-procedure-identifier?)
		  nil)))
        (when (and icp-socket?
		   (eq (icp-connection-state icp-socket?) icp-connection-running))
	  (writing-icp-message-group ((icp-output-port icp-socket?))
	    (send-icp-rpc-asynchronous-abort remote-procedure-identifier?))
	  (when (eq (icp-connection-state icp-socket?) icp-connection-running)
	    (setf (remote-procedure-identifier-awaiting-acknowledge-abort
		    remote-procedure-identifier?)
		  t))))
      nil)))




;;; The function `receive-remote-procedure-asynchronous-abort' handles requests
;;; from a remote system to abort an ongoing remote procedure call.  This
;;; function receives the ICP socket across which the request came, and the
;;; remote-procedure-identifier structure which represents the call.  This
;;; function should remove any connections between the remote-procedure-
;;; identifier and the remote-procedure-call and abort the base procedure
;;; invocation of the ongoing call.  If the remote-procedure-identifier or
;;; remote-procedure-call object are already disconnected from their
;;; procedure-invocation stack, then the procedure may have already returned,
;;; and no further work should be done on this end.  Note that the ICP message
;;; handler function for this message sends back an acknowledgement of the abort
;;; immediately after calling this function.

(defun receive-remote-procedure-asynchronous-abort
       (icp-socket remote-procedure-identifier)
  (declare (ignore icp-socket))
  (with-backtrace-for-internal-error
      'receive-remote-procedure-asynchronous-abort
    (let ((resumable-objects?
	    (remote-procedure-identifier-resumable-objects
	      remote-procedure-identifier)))
      (when resumable-objects?
	(reclaim-receiving-resumable-object (first resumable-objects?))
	;; jh, 9/28/94.  The icp-list in resumable-objects? has been reclaimed by
	;; successive delete-icp-element calls in the
	;; reclaim-single-receiving-resumable-object calls for each receiving
	;; resumable object.  Don't use reclaim-icp-list here!
	(setf (remote-procedure-identifier-resumable-objects
		remote-procedure-identifier)
	      nil)))
    (let ((remote-procedure-call
	    (remote-procedure-identifier-callee remote-procedure-identifier)))
      (when remote-procedure-call
	(setf (remote-procedure-identifier-callee remote-procedure-identifier) nil)
	(abort-incoming-rpc-call remote-procedure-call)))))
 
;; End file with [CR]

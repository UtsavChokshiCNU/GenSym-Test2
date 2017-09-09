;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module RPC-COMMON3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.

;;; Richard Harris

(declare-forward-references (:suppress-module-checks-for gsi)
  (activate-gsi-interface                          function G2-GSI)
  (set-icp-object-index-for-registered-item        function G2-RPC2)
  (icp-object-map-for-registered-item-function     function G2-RPC2)
  (establish-new-object-index-for-registered-item  function G2-RPC2)
  (establish-new-object-index-for-class-description function G2-RPC2)
  (get-icp-object-index-for-registered-item        function G2-RPC2)
  (name-for-local-home                             function G2-RPC3)
  (get-effective-data-type                         function GRAMMAR4A)
  (conclude-into-attribute-component               function STACK-ACTS)
  (include-slots-visible-only-to-roles-p           variable ATTR-EXPORT)
  (changing-validity-interval-invalidates-current-value-p
    variable INSTALL)
  (make-frame-for-class                            function STACK-ACTS)
  (get-class-info                                  function EVENTS-G2)
  #+java-export-facilities
  (instantiable-secret-java-class-p                function JAVA2)
  (make-transient-item-without-initialization      function FRAMES2A)
  (user-visible-slot-p                             function ATTR-EXPORT))

(declare-forward-references (:suppress-module-checks-for ab)
  (gsi-get-item-of-attribute-named      function GSI)
  (gsi-make-attributes-for-user-or-gsi  function GSI)
  (set-gsi-attribute-name               function GSI)
  (gsi-simple-content-copy-internal     function GSI)
  (gsi-make-appropriate-array           function GSI)
  (gsi-push-onto-appropriate-list       function GSI)
  (make-gsi-history-from-specification  function GSI)
  (add-vectors-to-gsi-history           function GSI)
  (gsi-make-array-for-user-or-gsi       function GSI)
  (make-gsi-attribute-for-user-or-gsi   function GSI)
  (gsi-attribute-qualified-name         function GSI)
  (gsi-local-home                       variable GSI-COMMON))

(declare-forward-references (:suppress-module-checks-for gsi)
  (send-icp-rpc-start-deferring-objects function G2-RPC2)
  (send-icp-rpc-call-deferring-objects function G2-RPC2)
  (send-icp-rpc-return-values-deferring-objects function G2-RPC2)
  (reclaim-after-rpc-return-values function G2-RPC1))

(declare-forward-reference get-list-of-all-user-visible-attributes function)
(declare-forward-reference make-transient-item function)
(declare-forward-reference set-transient-and-propagate function)
(declare-forward-reference receive-start-or-call-remote-procedure function)
(declare-forward-reference receive-remote-procedure-values function)
(declare-forward-reference receive-remote-procedure-error function)
(declare-forward-reference receive-remote-procedure-error-for-caller function)



(def-global-property-name class-rpc-item-info-to-slot-names-interned-list)

(defmacro interned-list--class (interned-list)
  `(car (interned-list--list ,interned-list)))

(defmacro interned-list--attribute-list (interned-list)
  `(cdr (interned-list--list ,interned-list)))

(defmacro interned-list--attribute-description-list (interned-list)
  `(getfq (interned-list--plist ,interned-list) 'attribute-description-list 'none))

(defun-simple set-interned-list--attribute-description-list (interned-list value)
  (let* ((plist (interned-list--plist interned-list))
	 (tail (memq 'attribute-description-list plist)))
    (if tail
	(setf (cadr tail) value)
	(setf (interned-list--plist interned-list)
	      (icp-cons 'attribute-description-list (icp-cons value plist))))
    value))

(defsetf interned-list--attribute-description-list
    set-interned-list--attribute-description-list)  

(define-interned-list-mapper decache-all-attribute-description-lists (tree)
  (when (interned-list-p tree)
    (let ((list (interned-list--attribute-description-list tree)))
      (when (consp list)
	(setf (interned-list--attribute-description-list tree) 'none)
	(reclaim-icp-list list)))))

(defun-void decache-attribute-description-lists-of-interned-lists (class)
  (let ((alist (class-rpc-item-info-to-slot-names-interned-list class)))
    (setf (class-rpc-item-info-to-slot-names-interned-list class) nil)
    (loop for a in alist do (reclaim-icp-cons a))
    (reclaim-icp-list alist))
  (let ((table (interned-list-table class)))
    (when table
      (decache-all-attribute-description-lists table))))

(set 'decache-attribute-description-lists-of-interned-lists-function
     #'decache-attribute-description-lists-of-interned-lists)

(defun-simple check-class-for-item-passing-1 (class)
  (runtime-current-system-case
    (ab
     (cond ((not (classp class))
	    #w"~A~S does not name a class")
	   ((or #+java-export-facilities
		(instantiable-secret-java-class-p class)
		(subclassp class 'error)
		(subclassp class 'name-box))
	    nil)
	   ((get-class-feature-if-any class 'not-user-instantiable)
	    #w"~AThe class ~S is not instantiatable")
	   ((not (subclassp class 'item)) ; This test should not be necessary
	    #w"~AThe class ~S is not a subclass of item")
	   ((subclassp class 'connection)
	    #w"~APassing connections is not supported")))
    (t class nil)))

(defun-simple check-class-for-item-passing (class)
  (let ((error-string (check-class-for-item-passing-1 class)))
    (when error-string
      (icp-resumable-error error-string #w"Error during item-passing: " class))))

(defun-simple get-attribute-description-list-for-interned-list (interned-list)
  (runtime-current-system-case
    (ab
     (let ((attribute-description-list
	     (interned-list--attribute-description-list interned-list)))
       (if (not (eq attribute-description-list 'none))
	   attribute-description-list
	   (let ((class (interned-list--class interned-list))
		 (attribute-list (interned-list--attribute-list interned-list)))
	     (when (check-class-for-item-passing-1 class)
	       (return-from get-attribute-description-list-for-interned-list nil))
	     (setq attribute-description-list
		   (loop with class-description = (class-description class)
			 for attribute in attribute-list
			 for attribute-name = (if (consp attribute) (caddr attribute) attribute)
			 for class-qualifier? = (if (consp attribute) (cadr attribute) nil)
			 for attribute-description
			     = (get-attribute-description-from-class-description
				 class-description
				 attribute-name
				 class-qualifier?)
			 collect attribute-description
			   using icp-cons))
	     (setf (interned-list--attribute-description-list interned-list)
		   attribute-description-list)))))
    (gsi
      interned-list
      nil)))

(defun-simple include-user-attribute-for-item-passing-p
    (slot-description class-description included-attributes? excluded-attributes?)
  (runtime-current-system-case
    (gsi
      slot-description class-description included-attributes? excluded-attributes?
      t)
    (t
      (when (user-vector-slot-index? slot-description)
	(let ((slot-name-with-qualifier-if-necessary
		(make-slot-name-denotation
		  (pretty-slot-name slot-description)
		  (when (slot-name-needs-qualification-p slot-description class-description)
		    (defining-class slot-description))
		  icp-cons)))
	  (when (cond
		  (included-attributes?
		   (member slot-name-with-qualifier-if-necessary
			   included-attributes?
			   :test #'equal))
		  (excluded-attributes?
		   (not (member slot-name-with-qualifier-if-necessary
				excluded-attributes?
				:test #'equal)))
		  (t t))
	    slot-name-with-qualifier-if-necessary))))))

(defparameter attributes-to-exclude-from-item-passing
  '(class ; always sent
    history ; use history-using-unix-time, instead
    value-structure ; use xxx-using-unix-time
    attribute-display-items ; contains table-items, which are not items
    following-item-in-workspace-layering ; setter isn't general purpose
    position-in-workspace ; causes too much trouble when sending the workspace
    name-box-item
    attribute-display-items
    ))

(defun-simple get-slot-names-for-item-passing-from-class-description-1
    (class-description included-attributes? excluded-attributes?
		       included-system-attributes excluded-system-attributes)
  (runtime-current-system-case
    (gsi
      class-description included-attributes? excluded-attributes?
      included-system-attributes excluded-system-attributes
      nil)
    (t
      (if (not (listp included-system-attributes))
	  (let* ((attribute-pairs
		   (let ((include-slots-visible-only-to-roles-p nil))
		     (get-list-of-all-user-visible-attributes class-description)))
		 (order-restriction
		   (class-description-class-case class-description
		     ((value-array item-array g2-array)
		      (icp-list 'foundation-class 'element-type 'g2-array-sequence))
		     ((value-list item-list g2-list)
		      (icp-list 'foundation-class 'element-type 'g2-list-sequence))
		     ((hash-table)
		      (icp-list 'foundation-class 'g2-hash-table-sequence))
		     ((variable-or-parameter)
		      (icp-list 'foundation-class
				'effective-data-type
				'history-keeping-spec
				'value-structure-using-unix-time
				'history-using-unix-time))
		     (t
		      (icp-list 'foundation-class))))
		 (attr-names
		   (loop with all-user-attributes-p
			   = (not (or included-attributes? excluded-attributes?))
			 for (attr-name . attr-desc) in attribute-pairs
			 for slot-desc-p = (slot-description-p attr-desc)
			 for user-attr-p = (and slot-desc-p
						(user-vector-slot-index? attr-desc))
			 when (if user-attr-p
				  (or all-user-attributes-p
				      (include-user-attribute-for-item-passing-p
					attr-desc class-description
					included-attributes? excluded-attributes?))
				  (and (not (memq attr-name order-restriction))
				       (not (memq attr-name attributes-to-exclude-from-item-passing))
				       (not (memq attr-name excluded-system-attributes))))
			   collect attr-name using icp-cons)))
	    (loop for cons in attribute-pairs do (reclaim-eval-cons cons))
	    (reclaim-eval-list attribute-pairs)
	    (if order-restriction
		(nconc order-restriction attr-names)
		attr-names))
	  (let* ((system-attrs-1
		   (nconc (when (memq 'name included-system-attributes)
			    (icp-list 'names))
			  (class-description-class-case class-description
			    ((value-array item-array g2-array)
			     (icp-list 'element-type
				       'g2-array-sequence
				       ;; 'array-length ; alias for 'g2-array-length
				       ;; 'g2-array-initial-values
				       ;; 'array-is-permanent
				       ))
			    ((value-list item-list g2-list)
			     (icp-list 'element-type
				       'g2-list-sequence))
			    ((hash-table)
			     (icp-list 'g2-hash-table-sequence))
			    ((variable-or-parameter)
			     (nconc (when (memq 'current-value included-system-attributes)
				      (icp-list 'value-structure-using-unix-time))
				    (nconc (icp-list 'effective-data-type)
					   (when (memq 'history included-system-attributes)
					     (icp-list 'history-keeping-spec
						       'history-using-unix-time)))))
			    ((object)
			     nil)
			    (t nil))))
		 (system-attrs-2
		   (loop for slot-name in included-system-attributes
			 for attr = (unless (or (memq slot-name '(name history current-value))
						(memq slot-name system-attrs-1))
				      (get-attribute-description-from-class-description
					class-description slot-name nil))
			 when (cond ((null attr) nil)
				    ((slot-description-p attr)
				     (and (not (user-defined-slot-description-p attr))
					  (user-visible-slot-p attr)))
				    (t
				     (virtual-attribute-defined-for-class?
				       attr
				       (class-name-of-class-description class-description))))
			   collect slot-name using icp-cons)))
	    (nconc system-attrs-1
		   system-attrs-2
		   (loop with slot-descriptions = (slot-descriptions class-description)
			 for slot-description in slot-descriptions
			 for slot-name? = (include-user-attribute-for-item-passing-p
					    slot-description class-description
					    included-attributes? excluded-attributes?)
			 when slot-name?
			   collect slot-name? using icp-cons)))))))

(defun-simple get-interned-slot-names-for-item-passing-from-class-description
    (class-description rpc-item-info icp-protocol-version)
  (runtime-current-system-case
    (gsi
      class-description rpc-item-info
      nil)
    (t
      (let* ((class-name (class-name-of-class-description class-description))
	     (alist (class-rpc-item-info-to-slot-names-interned-list class-name)))
	(or (loop for prev = nil then current
		  for current = alist then next
		  for next = (cdr current)
		  while current
		  when (eq rpc-item-info (caar current))
		    do (when prev
			 (setf (class-rpc-item-info-to-slot-names-interned-list class-name) current)
			 (setf (cdr current) alist)
			 (setf (cdr prev) next))
		       (return (cdar current)))
	    (let* ((included-attributes? (remote-procedure-item-info-included-attributes rpc-item-info))
		   (excluded-attributes? (remote-procedure-item-info-excluded-attributes rpc-item-info))
		   (included-system-attributes
		     (if (remote-procedure-item-info-include-all-system-attributes rpc-item-info)
			 t
			 (remote-procedure-item-info-included-system-attributes rpc-item-info)))
		   (excluded-system-attributes
		     (remote-procedure-item-info-include-all-system-attributes-except rpc-item-info))
		   (slot-names
		     (get-slot-names-for-item-passing-from-class-description-1
		       class-description
		       included-attributes? excluded-attributes?
		       included-system-attributes excluded-system-attributes))
		   (list (icp-cons class-name slot-names))
		   (interned-slot-names (intern-list list)))
	      (reclaim-icp-tree list)
	      (setf (class-rpc-item-info-to-slot-names-interned-list class-name)
		    (icp-cons (icp-cons rpc-item-info interned-slot-names) alist))
	      interned-slot-names))))))		  

(defun-simple gsi-get-slot-names-for-item-passing (item)
  (runtime-current-system-case
    (gsi
      (nconc 
	(when (gsi-instance-name item)
	  (icp-list 'names))
	(case (gsi-instance-value-type item)
	  ((#.gsi-integer-type-tag #.gsi-string-type-tag #.gsi-64bit-float-type-tag
            #.gsi-logical-type-tag #.gsi-symbol-type-tag
	    #.gsi-unsigned-short-vector-type-tag)
	   (when (gsi-instance-value item)
	     (icp-list 'value-structure-using-unix-time)))
	  ((#.gsi-64bit-float-array-type-tag #.gsi-string-array-type-tag
	    #.gsi-integer-array-type-tag #.gsi-logical-array-type-tag
	    #.gsi-symbol-array-type-tag
	    #.gsi-item-array-type-tag #.gsi-value-array-type-tag
	    #.gsi-item-or-value-array-type-tag #.gsi-quantity-array-type-tag)
	   (icp-list 'element-type
		     (cond ((gsi-item-append-flag-value item)
			    'g2-array-sequence-append)
			   ((and (memq (gsi-instance-value-type item)
				       '(#.gsi-item-array-type-tag
					 #.gsi-item-or-value-array-type-tag))
				 (gsi-update-items-in-lists-and-arrays-flag-value item))
			    (with-bifurcated-version (g2-supports-update-with-delete-icp-version)
			      'g2-array-sequence-immediate
			      (if (gsi-item-delete-flag-value item)
				  'g2-array-sequence-immediate-with-delete
				  'g2-array-sequence-immediate)))
			   (t
			    (with-bifurcated-version (g2-supports-update-with-delete-icp-version)
			      'g2-array-sequence
			      (if (gsi-item-delete-flag-value item)
				  'g2-array-sequence-with-delete
				  'g2-array-sequence))))))
	  ((#.gsi-64bit-float-list-type-tag #.gsi-string-list-type-tag
	    #.gsi-integer-list-type-tag #.gsi-logical-list-type-tag
	    #.gsi-symbol-list-type-tag
	    #.gsi-item-list-type-tag #.gsi-value-list-type-tag
	    #.gsi-item-or-value-list-type-tag #.gsi-quantity-list-type-tag)
	   (icp-list 'element-type
		     (cond ((gsi-item-append-flag-value item)
			    'g2-list-sequence-append)
			   ((and (memq (gsi-instance-value-type item)
				       '(#.gsi-item-list-type-tag
					 #.gsi-item-or-value-list-type-tag))
				 (gsi-update-items-in-lists-and-arrays-flag-value item))
			    (with-bifurcated-version (g2-supports-update-with-delete-icp-version)
			      'g2-list-sequence-immediate
			      (if (gsi-item-delete-flag-value item)
				  'g2-list-sequence-immediate-with-delete
				  'g2-list-sequence-immediate)))
			   (t
			    (with-bifurcated-version (g2-supports-update-with-delete-icp-version)
			      'g2-list-sequence
			      (if (gsi-item-delete-flag-value item)
				  'g2-list-sequence-with-delete
				  'g2-list-sequence)))))))
	(when (gsi-instance-history item)
	  (icp-list 'history-keeping-spec
		    'history-using-unix-time))
	(let* ((gsi-item item)
	       (attribute-count (gsi-attribute-count gsi-item))
	       (attribute-count-with-offset (+f attribute-count gsi-magic-offset))
	       (attributes (gsi-attributes gsi-item)))
	  (when (<f 0 attribute-count)
	    (loop for i from gsi-magic-offset below attribute-count-with-offset
		  for attribute = (gsi-managed-svref attributes i)
		  for attribute-spec = (gsi-attribute-spec attribute)
		  for base-name = (resumable-attribute-base-name attribute-spec)
		  for class-qualifier?
		      = (resumable-attribute-class-qualifier? attribute-spec)
		  unless (gsi-attribute-is-transient-p attribute)
		    collect (if class-qualifier?
				(icp-list 'class-qualified-name
					  class-qualifier? base-name)
				base-name)
		      using icp-cons)))))
    (t item)))

(defun-simple gsi-get-interned-slot-names-for-item-passing (class item)
  (runtime-current-system-case
    (gsi
      (let* ((slot-names (gsi-get-slot-names-for-item-passing item))
	     (list (icp-cons class slot-names))
	     (interned-slot-names (intern-list list)))
	(reclaim-icp-tree list)
	interned-slot-names))
    (t class item)))

;This list must match the entries in the case statement in the GSI part of
;the icp-value-reader for item-new-copy.
(defun-simple gsi-special-attribute-p (attribute)
  (memq attribute '(class
		    names
		    value
		    element-type
		    g2-array-sequence
		    g2-list-sequence
		    effective-data-type
		    history-keeping-spec
		    history-using-unix-time
		    value-structure-using-unix-time)))

(defun-simple element-type-for-gsi-type (gsi-type)
  (case gsi-type
    (#.gsi-64bit-float-array-type-tag 'float)
    (#.gsi-64bit-float-list-type-tag  'float)
    (#.gsi-string-array-type-tag      'text)
    (#.gsi-string-list-type-tag       'text)
    (#.gsi-integer-array-type-tag     'integer)
    (#.gsi-integer-list-type-tag      'integer)
    (#.gsi-logical-array-type-tag     'truth-value)
    (#.gsi-logical-list-type-tag      'truth-value)
    (#.gsi-symbol-array-type-tag      'symbol)
    (#.gsi-symbol-list-type-tag       'symbol)
    (#.gsi-item-or-value-array-type-tag 'item-or-value)
    (#.gsi-item-or-value-list-type-tag  'item-or-value)
    (#.gsi-quantity-array-type-tag    'quantity)
    (#.gsi-quantity-list-type-tag     'quantity)
    (#.gsi-item-array-type-tag        'item)
    (#.gsi-item-list-type-tag         'item)
    (#.gsi-value-array-type-tag       'value)
    (#.gsi-value-list-type-tag        'value)))

(defvar item-copy-root-item nil)
(defvar item-copy-handle-for-root-item nil)

(defvar item-copy-rpc-item-info nil)
(defmacro with-attributes-for-item-copy (attributes-lists &body body)
  `(gensym-dstruct-bind ((item-copy-rpc-item-info
			 item-copy-handle-for-root-item)
			,attributes-lists)
     ,@body))

(defun-simple ensure-item-copy-index-space ()
  (if (symbolp item-copy-index-space)
      (setq item-copy-index-space (make-index-space 'item-copy-index-space nil))
      item-copy-index-space))

(defun-simple lookup-index-in-index-space (x index-space)
  (loop with vector-of-vectors = (vector-of-index-subspace-vectors index-space)
	for i fixnum from 0 below (length (the simple-vector vector-of-vectors))
	for vector = (svref vector-of-vectors i)
	while vector
	do (loop for j fixnum from 0 below (length (the simple-vector vector))
		 for value = (svref vector j)
		 while value
		 when (eq x value)
		   do (return-from lookup-index-in-index-space
			(+f (ashf i #.(integer-length
					(1- (index-space-vector-length))))
			    j)))))

(defvar current-attribute-description-index nil)

(defmacro with-icp-item (item-var &body body)
  (let ((frame-serial-number (make-symbol "FRAME-SERIAL-NUMBER")))
    `(runtime-current-system-case
       (ab
	(with-icp-assertion ((not (evaluation-value-p ,item-var))
			     "~S is a value, not an item" ,item-var)
	  (with-icp-assertion
	      ((or (framep ,item-var) (class-description-p ,item-var))
	       "The item has been deleted" ,item-var)
	    (let ((,frame-serial-number (frame-serial-number ,item-var)))
	      (with-icp-assertion
		  ((frame-serial-number-equal ,frame-serial-number (frame-serial-number ,item-var))
		   "The item has been deleted" ,item-var)
		,@body)))))
       (gsi
	 ,@body))))

;Save the frame-serial-numbers of the items in the item-copy-index-space
;  Then, check them using the with-resumable-icp-assertion macro.

(defvar current-slot-value-of-user-slot nil)

;The callers of this should first call check-class-for-item-passing.
(defun-simple make-transient-frame-for-item-passing (class)
  (runtime-current-system-case
    (ab
     (if (or (subclassp class 'g2-list)
	     (subclassp class 'g2-array)
	     (subclassp class 'variable-or-parameter))
	 (make-transient-item class)
	 (make-transient-item-without-initialization class)))
    (t class)))

(defun-simple activate-item-if-necessary (item)
  (runtime-current-system-case
    (ab
     (cond (rpc-argument-list-error
	    (delete-frame item)
	    nil)
	   (t
	    (unless (active-p item)
	      (funcall-method 'activate-if-possible-and-propagate item))
	    (cond ((or (active-p item)
		       (icp-socket-runs-while-inactive current-icp-socket)
		       (and (frame-of-class-p item 'name-box)
			    (not allow-activation-of-name-boxes-p)))
		   item)
		  (t
		   (setq rpc-argument-list-error
			 (twith-output-to-text-string
			   (tformat "Failed to activate ~NF.  It's notes are: " item)
			   (write-frame-status-and-notes-from-slot
			     (frame-status-and-notes item)
			     item)))
		   (delete-frame item)
		   nil)))))
    (t item)))

(defun-simple array-or-list-element-type-suitable-p (received-element-type required-element-type)
  (setq received-element-type (case received-element-type
				(truth 'truth-value)
				(|float| 'float)
				(t received-element-type)))
  (cond	((or (eq required-element-type received-element-type)
	     (eq required-element-type 'item-or-value))
	 't)
	((eq required-element-type 'value)
	 (cond ((memq received-element-type '(float integer quantity text truth-value symbol))
		't)
	       ((eq received-element-type 'item-or-value)
		'maybe)))
	((eq required-element-type 'quantity)
	 (cond ((memq received-element-type '(float integer))
		't)
	       ((memq received-element-type '(item-or-value value))
		'maybe)))
	((memq required-element-type '(float integer))
	 (cond ((memq received-element-type '(item-or-value value quantity))
		'maybe)))
	((memq required-element-type '(text truth-value symbol))
	 (cond ((memq received-element-type '(item-or-value value))
		'maybe)))
	(t
	 (runtime-current-system-case
	   (ab
	     (cond ((and (classp required-element-type) (classp received-element-type))
		    (cond ((subclassp received-element-type required-element-type)
			   't)
			  (t ; should be: classes-have-a-common-subclass-p
			   'maybe)))))))))

(def-icp-value-writer item-new-copy
  (let* ((class
	   (runtime-current-system-case
	     (gsi (class-for-gsi-item item-new-copy))
	     (ab  (class item-new-copy))))
	 (interned-list
	   (runtime-current-system-case
	     (gsi
	       (gsi-get-interned-slot-names-for-item-passing class item-new-copy))
	     (ab
	      (get-interned-slot-names-for-item-passing-from-class-description
		(class-description-slot item-new-copy)
		item-copy-rpc-item-info
		(icp-protocol-version-for-output current-icp-socket))))))
    (let ((new-index (assign-index-in-index-space (ensure-item-copy-index-space))))
      (store-object-in-index-space item-copy-index-space new-index item-new-copy))
    (write-icp-interned-list-as-value-type interned-list)
    (runtime-current-system-case
      (ab
       (or (check-class-for-item-passing class)
	   (loop for attribute-description
		     in (get-attribute-description-list-for-interned-list interned-list)
		 for value = (get-attribute-description-evaluation-value
			       item-new-copy attribute-description)
		 do (if (binary-wide-string-p value)
			(let ((remote-value-is-binary-p t))
			  (write-icp-remote-value value))
			(write-icp-remote-value value))
		    (reclaim-if-evaluation-value value))))
      (gsi
	(let ((name (gsi-instance-name item-new-copy)))
	  (when name (write-icp-symbol-as-value-type name)))
	(when (gsi-instance-value item-new-copy)
	  (case (gsi-instance-value-type item-new-copy)
	    ((#.gsi-integer-type-tag #.gsi-string-type-tag #.gsi-64bit-float-type-tag
				     #.gsi-logical-type-tag #.gsi-symbol-type-tag
				     #.gsi-unsigned-short-vector-type-tag)
	     (write-gsi-value-structure item-new-copy))))
	(let ((element-type (element-type-for-gsi-type
			      (gsi-instance-value-type item-new-copy))))
	  (when element-type
	    (write-icp-remote-value element-type)
	    (write-sequence-from-gsi-item item-new-copy element-type)))
	(let ((history (gsi-instance-history item-new-copy)))
	  (when history
	    (write-gsi-history-specification history)
	    (write-gsi-history history item-new-copy)))
	(let* ((gsi-item item-new-copy)
	       (attribute-count (gsi-attribute-count gsi-item))
	       (attribute-count-with-offset (+f attribute-count gsi-magic-offset))
	       (attributes (gsi-attributes gsi-item)))
	  (when (<f 0 attribute-count)
	    (loop for i from gsi-magic-offset below attribute-count-with-offset
		  for attribute = (gsi-managed-svref attributes i)
		  for attribute-value = (gsi-attribute-instance attribute)
		  unless (gsi-attribute-is-transient-p attribute)
		    do (write-icp-remote-value attribute-value))))))))

(defun-simple get-default-class-for-missing-class (desired-class foundation-class)
  (when (and desired-class foundation-class)
    (let* ((new-class (cond ((eq foundation-class 'error) ; generalize this!
			     'default-error)))
	   (error-string (if new-class
			     (check-class-for-item-passing-1 new-class)
			     #w"~ANo default class")))
      (unless error-string
	new-class))))

(defun-simple handle-missing-class-in-rpc (error-string desired-class contents-as-structure index)
  (runtime-current-system-case
    (ab
     (let ((default-class
	       (get-default-class-for-missing-class
		 desired-class
		 (evaluation-structure-slot contents-as-structure 'foundation-class))))
       (when default-class
	 (let ((item (make-transient-frame-for-item-passing default-class)))
	   (store-object-in-index-space item-copy-index-space index item)
	   (loop with class-description = (class-description default-class)
		 for (attribute . value) being evaluation-structure-pair of contents-as-structure
		 for attribute-name = (if (consp attribute) (caddr attribute) attribute)
		 for class-qualifier? = (if (consp attribute) (cadr attribute) nil)
		 for attribute-description
		     = (get-attribute-description-from-class-description
			 class-description
			 attribute-name
			 class-qualifier?)
		 for virtual-attribute-p = (virtual-attribute-p attribute-description)
		 for user-slot-p = (and attribute-description
					(not virtual-attribute-p)
					(user-vector-slot-index? attribute-description))
		 for writable-p
		     = (cond (user-slot-p)
			     ((null attribute-description) nil)
			     (virtual-attribute-p
			      (virtual-attribute-setter? attribute-description))
			     (t
			      (let* ((slot-description-type?
				       (feature-assq 'type (slot-features attribute-description)))
				     (category-symbol
				       (second slot-description-type?)))
				(evaluation-value-to-category-function category-symbol))))
		 do
	     (when writable-p
	       (change-attribute-description-evaluation-value
		 item attribute-description value)))
	   (return-from handle-missing-class-in-rpc item)))
       (reclaim-evaluation-value contents-as-structure)))
    (t
      contents-as-structure index))
  (icp-error error-string #w"Error during item-passing: " desired-class))

(defvar append-into-arrays-and-lists nil)
(defvar delete-old-elements-from-arrays-and-lists nil)

(defun-void change-attribute-description-evaluation-value-for-icp
    (item-new-copy attribute-description value)
  (runtime-current-system-case
    (ab
      (let ((changing-validity-interval-invalidates-current-value-p nil))
	(when (evaluation-unsigned-vector-16-p value)
	  (setq value (evaluation-unsigned-vector-16-value value)))
	(let* ((slot-description?
		 (cond ((symbolp attribute-description)
			(get-slot-description-of-class-description
			  attribute-description (class-description-slot item-new-copy) nil))
		       ((slot-description-p attribute-description)
			attribute-description)))
	       (user-defined-slot-p
		 (and slot-description?
		      (user-defined-slot-description-p slot-description?)))
	       (existing-value-of-user-slot
		 (when user-defined-slot-p
		   (get-slot-description-value item-new-copy slot-description?))))
	  (cond ((and (framep existing-value-of-user-slot)
		      (framep value)
		      (type-specification-type-p
			value
			(slot-type-specification slot-description?)))
		 (unless (eq existing-value-of-user-slot value)
		   (change-slot-description-value
		     item-new-copy slot-description? value)))
		(t
		 (let ((problem-description?
			 (if (symbolp attribute-description)
			     (conclude-into-attribute-component
			       item-new-copy attribute-description nil value nil nil)
			     (change-attribute-description-evaluation-value
			       item-new-copy attribute-description value))))
		   (when problem-description?
		     (icp-warning problem-description? item-new-copy value)
		     (reclaim-if-evaluation-value value)
		     (reclaim-text-string problem-description?))))))))
    (t item-new-copy attribute-description value
       nil)))

(defvar allow-no-value-p t)

(defun-void delete-frame-for-rpc (frame)
  (current-system-case
    (ab (delete-frame frame))
    (t frame
       nil)))

(defun-simple-resumable-icp-function read-immediate-g2-array-sequence (g2-array delete-p)
  (runtime-current-system-case
    (ab
      (let* ((element-type (g2-array-element-type g2-array))
	     (typetag (case (read-icp-byte)
			(#.gsi-typed-sequence-type-tag (read-icp-byte))
			(#.gsi-sequence-type-tag       #.gsi-value-type-tag)))
	     (remote-value-known-typetag
	       (cond ((=f typetag #.gsi-value-type-tag) nil)
		     (t typetag)))
	     (length (read-icp-fixnum))
	     (array-length (g2-array-length g2-array)))
	(unless (=f length array-length)
	  (when (and delete-p (<f length array-length))
	    (loop for index from length below array-length
		  for current-element = (g2-array-aref-item-or-evaluation-value g2-array index)
		  when (framep current-element)
		    do (delete-frame-for-rpc current-element)))
	  (change-slot-value g2-array 'g2-array-length length))
	(loop with allow-no-value-p = (or (not (null (class-description element-type)))
					  (eq element-type 'item-or-datum))
	      for index from 0 below length
	      for current-element = (g2-array-aref-item-or-evaluation-value g2-array index)
	      for current-slot-value-of-user-slot
		  = (when (framep current-element) current-element)
	      for item-or-datum? = (read-icp-remote-value)
	      do
	  (when (evaluation-unsigned-vector-16-p item-or-datum?)
	    (setq item-or-datum? (evaluation-unsigned-vector-16-value item-or-datum?)))
	  (unless (and current-slot-value-of-user-slot
		       (eq current-slot-value-of-user-slot item-or-datum?))
	    (mutate-g2-array g2-array index item-or-datum? t t)
	    (when (and current-slot-value-of-user-slot delete-p)
	      (delete-frame-for-rpc current-slot-value-of-user-slot)))
	  (reclaim-if-evaluation-value current-element)))
      t)
    (t g2-array delete-p
       nil)))

(defun-simple-resumable-icp-function read-immediate-g2-list-sequence (g2-list delete-p)
  (runtime-current-system-case
    (ab
      (let* ((element-type (list-type g2-list))
	     (typetag (case (read-icp-byte)
			(#.gsi-typed-sequence-type-tag (read-icp-byte))
			(#.gsi-sequence-type-tag       #.gsi-value-type-tag)))
	     (remote-value-known-typetag
	       (cond ((=f typetag #.gsi-value-type-tag) nil)
		     (t typetag)))
	     (length (read-icp-fixnum))
	     (list-length (g2-list-length g2-list))
	     (min-length (minf length list-length)))
	(loop with allow-no-value-p = (or (not (null (class-description element-type)))
					  (eq element-type 'item-or-datum))
	      with g2-list-structure = (list-structure g2-list)
	      for i from 0 below min-length
	      for element-structure = #-Lockfree-List
				      (g2-list-structure-head g2-list-structure)
				      #+Lockfree-List
				      (g2-list-structure-next
				        (g2-list-structure-head g2-list-structure)
					g2-list-structure)
		  then (g2-list-structure-next element-structure g2-list-structure)
	      for current-element = (list-element-value element-structure)
	      for current-slot-value-of-user-slot
		  = (when (framep current-element) current-element)
	      for item-or-datum? = (read-icp-remote-value)
	      do
	  (when (evaluation-unsigned-vector-16-p item-or-datum?)
	    (setq item-or-datum? (evaluation-unsigned-vector-16-value item-or-datum?)))
	  (unless (and current-slot-value-of-user-slot
		       (eq current-slot-value-of-user-slot item-or-datum?))
	    (replace-g2-list-element
	      element-structure item-or-datum? allow-no-value-p element-type delete-p))
	      finally
		(cond ((<f length list-length)
		       (loop for i from length below list-length
			     for element-structure = (g2-list-last g2-list nil t)
			     for element-value = (list-element-value element-structure)
			     do
			 (remove-g2-list-element-structure element-structure g2-list t t t)
			 (when (and delete-p (framep element-value))
			   (delete-frame element-value))))
		      ((<f list-length length)
		       (loop for i from list-length below length
			     for item-or-datum? = (read-icp-remote-value)
			     do
			 (when (evaluation-unsigned-vector-16-p item-or-datum?)
			   (setq item-or-datum? (evaluation-unsigned-vector-16-value item-or-datum?)))
			 (maybe-insert-g2-list-element-at-end
			   item-or-datum? g2-list allow-no-value-p element-type))))))
      t)
    (t g2-list delete-p
       nil)))

(defun-void replace-g2-list-element (element-structure item-or-datum? allow-no-value-p element-type delete-p)
  (runtime-current-system-case
    (ab
      (let ((current-element (list-element-value element-structure)))
	(when (or (and allow-no-value-p (null item-or-datum?))
		  (type-specification-type-p item-or-datum? element-type)
		  (of-class-p item-or-datum? element-type))
	  (note-change-to-runtime-data-for-block (list-frame element-structure))
	  (when (framep current-element)
	    (delete-from-list-elements-for-item
	      current-element element-structure)
	    (when (and delete-p (not (eq current-element item-or-datum?)))
	      (delete-frame current-element)))
	  (setf (list-element-value element-structure) item-or-datum?)
	  (reclaim-if-evaluation-value current-element)
	  (when (framep item-or-datum?)
	    (add-to-list-elements-for-item
	      item-or-datum? element-structure)))))
    (t element-structure item-or-datum? allow-no-value-p element-type delete-p
       nil)))

(defun-void maybe-insert-g2-list-element-at-end (item-or-datum? g2-list allow-no-value-p element-type)
  (runtime-current-system-case
    (ab
      (when (or (and allow-no-value-p (null item-or-datum?))
		(type-specification-type-p item-or-datum? element-type)
		(of-class-p item-or-datum? element-type))
	(g2-list-insert-at-end item-or-datum? g2-list t)))
    (t
      item-or-datum? g2-list allow-no-value-p element-type
      nil)))

(defvar identifying-attribute-count-for-item-new-copy nil)
(defvar corresponding-icp-object-index-for-item-new-copy nil)
(defvar item-being-read-for-new-reference nil)

(def-icp-value-reader item-new-copy
  (let* ((current-computation-flags current-computation-flags)
	 (new-index
	   (progn
	     ;; This modifies the compution-flags bound just above.
	     (current-system-case
	       (ab (setf (role-serve-inactive-objects?) t)))
	     (assign-index-in-index-space (ensure-item-copy-index-space))))
	 (interned-list (read-icp-interned-list-as-value-type))
	 (interned-class (interned-list--class interned-list))
	 (attribute-name-list (interned-list--attribute-list interned-list))
	 (class
	   (runtime-current-system-case
	     (gsi interned-class)
	     (ab
	      (let ((error-string (check-class-for-item-passing-1 interned-class)))
		(cond ((null error-string)
		       interned-class)
		      ((eq 'foundation-class (first attribute-name-list))
		       (setq attribute-name-list (cdr attribute-name-list))
		       (let ((new-class (get-default-class-for-missing-class
					  interned-class (read-icp-remote-value))))
			 (if new-class
			     (let ((new-interned-list (icp-cons new-class attribute-name-list)))
			       (setq interned-list (intern-list new-interned-list))
			       (reclaim-icp-cons new-interned-list)
			       new-class)
			     (return-from read-icp-item-new-copy
			       (handle-missing-class-in-rpc
				 error-string
				 interned-class
				 (read-evaluation-structure-from-list
				   (eval-list 'foundation-class new-class)
				   attribute-name-list)
				 new-index)))))
		      (t
		       (return-from read-icp-item-new-copy
			 (handle-missing-class-in-rpc
			   error-string
			   interned-class
			   (read-evaluation-structure-from-list nil attribute-name-list)
			   new-index))))))))
	 (attribute-description-list
	   (runtime-current-system-case
	     (ab
	      (get-attribute-description-list-for-interned-list interned-list))))
	 (all-attributes-count
	   (runtime-current-system-case
	     (gsi attribute-description-list
		  (length attribute-name-list))))
	 (gsi-special-attributes-count
	   (runtime-current-system-case
	     (gsi (loop for attribute in attribute-name-list
			count (gsi-special-attribute-p attribute)))))
	 (attribute-count
	   (runtime-current-system-case
	     (gsi (-f all-attributes-count gsi-special-attributes-count))))
	 (use-bound-value-for-item-new-copy-p 
	   (runtime-current-system-case
	     (ab
	      (and (framep current-slot-value-of-user-slot)
		   (eq class (class current-slot-value-of-user-slot))))
	     (t
	      nil)))
	 (item-new-copy
	   (runtime-current-system-case
	     (gsi
	       (let* ((owner (if identifying-attribute-count-for-item-new-copy
				 'context
				 (default-owner-for-gsi-objects)))
		      (instance
			(make-gsi-instance
			  gsi-null-type-tag nil
			  (gsi-make-attributes-for-user-or-gsi attribute-count owner)
			  class nil owner)))
		 (when corresponding-icp-object-index-for-item-new-copy
		   (store-corresponding-item
		     corresponding-icp-object-index-for-item-new-copy
		     instance)
		   (setq corresponding-icp-object-index-for-item-new-copy nil))		 
		 (when (and owner (not item-being-read-for-new-reference))
		   (setq item-being-read-for-new-reference instance))
		 instance))
	     (ab
	       (unless rpc-argument-list-error
		 (if use-bound-value-for-item-new-copy-p
		     (activate-item-if-necessary current-slot-value-of-user-slot)
		     (make-transient-frame-for-item-passing class)))))))
    (current-system-case
      (ab all-attributes-count gsi-special-attributes-count attribute-count)
      (gsi attribute-description-list use-bound-value-for-item-new-copy-p))
    (store-object-in-index-space item-copy-index-space new-index item-new-copy)
    (runtime-current-system-case
      (ab
       (with-icp-item item-new-copy
	 (loop for attribute-description in attribute-description-list
	       for attribute-name in attribute-name-list
	       for virtual-attribute-p = (virtual-attribute-p attribute-description)
	       for user-slot-p = (and (not virtual-attribute-p)
				      attribute-description
				      (user-vector-slot-index? attribute-description))
	       for writable-p
		   = (cond (rpc-argument-list-error nil)
			   (user-slot-p)
			   ((null attribute-description) nil)
			   (virtual-attribute-p
			    (virtual-attribute-setter? attribute-description))
			   (t
			    (let* ((slot-description-type?
				     (feature-assq 'type (slot-features attribute-description)))
				   (category-symbol
				     (second slot-description-type?)))
			      (evaluation-value-to-category-function category-symbol))))
	       for current-slot-value-of-user-slot
		   = (when (and user-slot-p writable-p)
		       (let ((value (get-attribute-description-evaluation-value
				      item-new-copy attribute-description)))
			 (if (framep value)
			     value
			     (progn
			       (reclaim-if-evaluation-value value)
			       nil))))
	       for immediate-sequence-p
		   = (when (and use-bound-value-for-item-new-copy-p
				(not rpc-argument-list-error))
		       (case attribute-name
			 (g2-array-sequence-immediate
			  (read-immediate-g2-array-sequence item-new-copy nil))
			 (g2-array-sequence-immediate-with-delete
			  (read-immediate-g2-array-sequence item-new-copy t))
			 (g2-list-sequence-immediate
			  (read-immediate-g2-list-sequence item-new-copy nil))
			 (g2-list-sequence-immediate-with-delete
			  (read-immediate-g2-list-sequence item-new-copy t))))
	       for value = (unless immediate-sequence-p
			     (read-icp-remote-value))
	       do
	   (cond ((or immediate-sequence-p
		      (and current-slot-value-of-user-slot ; a frame
			   (eq current-slot-value-of-user-slot value))))  ; no action required
		 (rpc-argument-list-error
		  (reclaim-if-evaluation-value value))
		 ((or (eq attribute-name 'g2-array-sequence-append)
		      (eq attribute-name 'g2-list-sequence-append))
		  (let ((append-into-arrays-and-lists t))
		    (change-attribute-description-evaluation-value-for-icp
		      item-new-copy
		      (case attribute-name
			(g2-array-sequence-append 'g2-array-sequence)
			(g2-list-sequence-append  'g2-list-sequence))
		      value)))
		 ((or (eq attribute-name 'g2-array-sequence-delete)
		      (eq attribute-name 'g2-list-sequence-delete))
		  (let ((delete-old-elements-from-arrays-and-lists t))
		    (change-attribute-description-evaluation-value-for-icp
		      item-new-copy
		      (case attribute-name
			(g2-array-sequence-delete 'g2-array-sequence)
			(g2-list-sequence-delete  'g2-list-sequence))
		      value)))
		 ((and (eq attribute-name 'element-type)
		       (slot-description-p attribute-description)
		       (eq (cadr (feature-assq 'type (slot-features attribute-description)))
			   'element-type))
		  (let ((element-type (get-attribute-description-evaluation-value
					item-new-copy attribute-description)))
		    (unless (array-or-list-element-type-suitable-p value element-type)
		      (icp-warning "Item-passing array or list element type mismatch: need ~S, received ~S"
				   element-type value))))
		 ((not (and writable-p attribute-description))
		  (if (framep value)
		      (unless virtual-attribute-p ; because there are problems with the v.a. represented-item
			(delete-frame value))
		      (reclaim-if-evaluation-value value)))
		 (t
		  (change-attribute-description-evaluation-value-for-icp
		    item-new-copy attribute-description value))))
	 (activate-item-if-necessary item-new-copy)))
      (gsi
	(loop with item-with-identifying-attributes-p
		= (eq item-being-read-for-new-reference item-new-copy)
	      with names = nil
	      with gsi-item = item-new-copy
	      with attributes = (when gsi-item
				  (gsi-attributes gsi-item))
	      with element-type = nil
	      with i = gsi-magic-offset
	      for attribute-name in attribute-name-list
	      for identifying-attribute-p
		  = (and item-with-identifying-attributes-p
			 (<f 0 identifying-attribute-count-for-item-new-copy))
	      do
	  (case attribute-name
	    (names
	     (cond ((memq (peek-icp-byte) '(#.gsi-sequence-type-tag #.gsi-typed-sequence-type-tag))
		    (setq names (read-icp-remote-value)))
		   (t
		    (setf (gsi-instance-name item-new-copy)
			  (let ((gsi-remote-value-creates-instance-p nil))
			    (read-icp-remote-value)))
		    (when identifying-attribute-p
		      (setf (gsi-item-name-is-identifying-flag-value item-new-copy) t)))))
	    (value
	     (let ((make-gsi-instance-existing-instance gsi-item))
	       (read-icp-remote-value)))
	    (value-structure-using-unix-time
	     (read-gsi-value-structure item-new-copy))
	    (element-type
	     (setq element-type (read-icp-symbol-as-value-type)))
	    (g2-array-sequence
	     (read-sequence-into-gsi-item item-new-copy element-type 'array))
	    (g2-list-sequence
	     (read-sequence-into-gsi-item item-new-copy element-type 'list))
	    (effective-data-type
	     (read-gsi-effective-data-type-into-item item-new-copy))
	    (history-keeping-spec
	     (setf (gsi-instance-history item-new-copy)
		   (read-gsi-history-specification)))
	    (history-using-unix-time
	     (read-gsi-history (gsi-instance-history item-new-copy) item-new-copy))
	    (class
	     (let ((gsi-remote-value-creates-instance-p nil))
	       (read-icp-remote-value)))
	    (t
	     (let* ((value (read-icp-remote-value))
		    (attribute (gsi-managed-svref attributes i)))
	       (cond ((consp attribute-name)
		      (let ((base-name
			      (if (consp attribute-name) (third attribute-name) attribute-name))
			    (class-qualified-name?
			      (if (consp attribute-name) (second attribute-name) nil))
			    (attribute-spec (gsi-attribute-spec attribute)))			    
			(setf (resumable-attribute-base-name attribute-spec) base-name)
			(setf (resumable-attribute-class-qualifier? attribute-spec) class-qualified-name?)))
		     (t
		      (set-gsi-attribute-name attribute attribute-name)))
	       (setf (gsi-attribute-instance attribute) value)
	       (when identifying-attribute-p
		 (setf (gsi-attribute-is-identifying-p attribute) t))
	       (incff i))))
	  (when identifying-attribute-p
	    (decff identifying-attribute-count-for-item-new-copy))
	      finally
		(when (and names item-new-copy)
		  (let ((new-attributes (gsi-make-array-for-user-or-gsi
					  (1+f attribute-count)
					  (default-owner-for-gsi-objects)))
			(name-attribute (make-gsi-attribute-for-user-or-gsi
					  (default-owner-for-gsi-objects))))
		    (setf (gsi-managed-svref new-attributes gsi-magic-offset) name-attribute)
		    (setf (gsi-attribute-instance name-attribute) names)
		    (loop for i from gsi-magic-offset
				below (+f attribute-count gsi-magic-offset)
			  do (setf (gsi-managed-svref new-attributes (1+f i))
				   (gsi-managed-svref attributes i)))
		    (setf (gsi-attributes item-new-copy) new-attributes)
		    (setf (gsi-attribute-count item-new-copy)
			  (1+f attribute-count)))))
	item-new-copy))))

;(structure ((data-point-value datum) ; if not present, there is no current value
;	     (data-point-collection-time number)
;	     (data-point-expiration-time number)))
(defun-simple-resumable-icp-function read-gsi-value-structure (gsi-item)
  (runtime-current-system-case
    (gsi
      (cond ((eq #.gsi-null-type-tag (peek-icp-byte))
	     (read-icp-byte)
	     nil)
	    (t
	     (unless (eq (read-icp-byte) #.gsi-structure-type-tag)
	       (return-from read-gsi-value-structure
		 (icp-error "Expected a value-structure")))
	     (loop with list = (interned-list--list
				 (read-icp-interned-list-as-value-type))
		   for name in list
		   for make-gsi-instance-existing-instance
		       = (case name (data-point-value gsi-item))
		   for gsi-remote-value-creates-instance-p
		       = (not (null make-gsi-instance-existing-instance))
		   for value = (read-icp-remote-value)
		   do
	       (case name
		 (data-point-value)
		 (data-point-collection-time
		  (setf (gsi-instance-timestamp gsi-item) value))
		 (data-point-expiration-time
		  (when (managed-float-p value)
		    (reclaim-managed-float value))))))))
    (t gsi-item nil)))

(defvar data-point-value-interned-list
  (intern-list '(data-point-value)))

(defvar data-point-value-and-collection-time-interned-list
  (intern-list '(data-point-value data-point-collection-time)))

(defun-simple-resumable-icp-function write-gsi-value-structure (gsi-item)
  (runtime-current-system-case
    (gsi
      (cond ((null (gsi-instance-value gsi-item))
	     (write-icp-byte #.gsi-null-type-tag))
	    (t
	     (let ((collection-time (gsi-instance-timestamp gsi-item)))
	     (write-icp-byte #.gsi-structure-type-tag)
	     (write-icp-interned-list-as-value-type
	       (if collection-time
		   data-point-value-and-collection-time-interned-list
		   data-point-value-interned-list))
	     (let ((write-value-of-gsi-item-p t))
	       (write-icp-remote-value gsi-item))
	     (when collection-time
	       (write-icp-remote-value collection-time))))))
    (t
      gsi-item
      nil)))

(defun-simple-resumable-icp-function read-sequence-into-gsi-item (gsi-item element-type array-or-list)
  (runtime-current-system-case
    (gsi
      (if (eq #.gsi-null-type-tag (peek-icp-byte))
	  (progn
	    (read-icp-byte)
	    nil)
	  (let ((value-type
		  (case array-or-list
		    (array
		     (case element-type
		       (item-or-value #.gsi-item-or-value-array-type-tag)
		       (value         #.gsi-value-array-type-tag)
		       (quantity      #.gsi-quantity-array-type-tag)
		       (text          #.gsi-string-array-type-tag)
		       (truth-value   #.gsi-logical-array-type-tag)
		       (symbol        #.gsi-symbol-array-type-tag)
		       (float         #.gsi-64bit-float-array-type-tag)
		       (integer       #.gsi-integer-array-type-tag)
		       (t             #.gsi-item-array-type-tag)))
		    (list
		     (case element-type
		       (item-or-value #.gsi-item-or-value-list-type-tag)
		       (value         #.gsi-value-list-type-tag)
		       (quantity      #.gsi-quantity-list-type-tag)
		       (text          #.gsi-string-list-type-tag)
		       (truth-value   #.gsi-logical-list-type-tag)
		       (symbol        #.gsi-symbol-list-type-tag)
		       (float         #.gsi-64bit-float-list-type-tag)
		       (integer       #.gsi-integer-list-type-tag)
		       (t             #.gsi-item-list-type-tag))))))
	    (setf (gsi-instance-value-type gsi-item) value-type)
	    (read-icp-evaluation-sequence-body
	      gsi gsi-item value-type
	  (when (memq element-type '(integer truth-value float symbol text))
	    element-type)))))
    (t
      gsi-item element-type array-or-list
      nil)))

(defun-simple-resumable-icp-function write-sequence-from-gsi-item (gsi-item element-type)
  (runtime-current-system-case
    (gsi
      (let ((length (gsi-element-count gsi-item))
	    (array (gsi-instance-value gsi-item)))
	(write-icp-evaluation-sequence-body
	  gsi
	  length
	  value
	  (when array
	    (loop for i fixnum from 0 below length
		  for value = (case element-type
				(text        (gsi-typed-array-ref string array i))
				(truth-value (gsi-typed-array-ref logical array i))
				(symbol      (gsi-typed-array-ref symbol array i))
				(float       (gsi-typed-array-ref 64bit-float array i))
				(integer     (gsi-typed-array-ref integer array i))
				(t           (gsi-typed-array-ref gsi-item array i)))
		  do
	      .use-next-value.
	       (when (eq element-type 'float)
		 (reclaim-managed-float value))))
	  (when (memq element-type '(text truth-value float symbol integer))
	    element-type))))
    (t
      gsi-item element-type
      nil)))

(defun-simple-resumable-icp-function read-gsi-history-specification ()
  (runtime-current-system-case
    (gsi
      (cond ((eq #.gsi-null-type-tag (peek-icp-byte))
	     (read-icp-byte)
	     nil)
	    (t
	     (unless (eq (read-icp-byte) #.gsi-structure-type-tag)
	       (return-from read-gsi-history-specification
		 (icp-error "Expected a history specification")))
	     (let ((maximum-number-of-data-points nil)
		   (maximum-age-of-data-points nil)
		   (minimum-interval-between-data-points nil)
		   (list (interned-list--list (read-icp-interned-list-as-value-type))))
	       (loop with gsi-remote-value-creates-instance-p = nil
		     for name in list
		     for value = (read-icp-remote-value)
		     do
		 (case name
		   (maximum-number-of-data-points (setq maximum-number-of-data-points value))
		   (maximum-age-of-data-points (setq maximum-age-of-data-points value))
		   (minimum-interval-between-data-points (setq minimum-interval-between-data-points value))))
	       (make-gsi-history-from-specification
		 maximum-number-of-data-points
		 maximum-age-of-data-points
		 minimum-interval-between-data-points)))))
    (t nil)))

(defvar attributes-of-history-specification-structure-as-interned-list
  (intern-list
    '(maximum-number-of-data-points maximum-age-of-data-points minimum-interval-between-data-points)))

(defun-simple-resumable-icp-function write-gsi-history-specification (history)
  (runtime-current-system-case
    (gsi
      (cond ((null history)
	     (write-icp-byte #.gsi-null-type-tag))
	    (t
	     (let* ((history-spec (gsi-history-internals history))
		    (max-count? (second history-spec)) ; nil or fixnum
		    (max-age? (third history-spec)) ; nil or fixnum
		    (granularity? (fourth history-spec)) ; nil or fixnum
		    (list (nconc (when max-count? (gsi-list 'maximum-number-of-data-points))
				 (when max-age? (gsi-list 'maximum-age-of-data-points))
				 (when granularity? (gsi-list 'minimum-interval-between-data-points)))))
	       (cond (list
		      (write-icp-byte #.gsi-structure-type-tag)
		      (write-icp-interned-list-as-value-type (intern-list list))
		      (reclaim-gsi-list list)
		      (when max-count? (write-icp-remote-value max-count?))
		      (when max-age? (write-icp-remote-value max-age?))
		      (when granularity? (write-icp-remote-value granularity?)))
		     (t
		      (write-icp-byte #.gsi-null-type-tag))))))
      history)
    (t history)))

(defun-simple-resumable-icp-function read-gsi-effective-data-type-into-item (gsi-item)
  (runtime-current-system-case
    (gsi
      (let* ((type (let ((gsi-remote-value-creates-instance-p nil))
		     (read-icp-remote-value)))
	     (tag (case type
		    (text        #.gsi-string-type-tag)
		    (symbol      #.gsi-symbol-type-tag)
		    (float       #.gsi-64bit-float-type-tag)
		    (integer     #.gsi-integer-type-tag)
		    (truth-value #.gsi-logical-type-tag)
		    (quantity    #.gsi-quantity-type-tag)
		    (t           #.gsi-value-type-tag))))
	(setf (gsi-instance-class-type gsi-item) tag)))
    (t
      gsi-item
      nil)))

(defvar attributes-of-history-element-structure-as-interned-list
  (intern-list '(history-value history-collection-time)))

(defun-simple-resumable-icp-function read-gsi-history (history item)
  (runtime-current-system-case
    (gsi
      (cond
	((eq #.gsi-null-type-tag (peek-icp-byte))
	 (read-icp-byte)
	 history)
	(t
	 (unless (eq (read-icp-byte) #.gsi-sequence-type-tag)
	   (return-from read-gsi-history
	     (icp-error "expected a history sequence")))
	 (let ((length (read-icp-fixnum)))
	   (unless (<=f 1 length)
	     (return-from read-gsi-history
	       (icp-error "expected at least one element in the history")))
	   (add-vectors-to-gsi-history length history item)
	   (loop with gsi-remote-value-creates-instance-p = nil
		 with type = (gsi-instance-class-type item)
		 with values = (gsi-history-values history)
		 with timestamps = (gsi-history-timestamps history)
		 for i from 0 below length
		 do
	     (unless (and (eq (read-icp-byte) #.gsi-structure-type-tag)
			  (eq (read-icp-interned-list-as-value-type)
			      attributes-of-history-element-structure-as-interned-list))
	       (return-from read-gsi-history
		 (icp-error "expected a history element structure")))
	     (let* ((history-value
		      (if (or (=f #.gsi-value-type-tag type)
			      (=f #.gsi-quantity-type-tag type))
			  (let ((gsi-remote-value-creates-instance-p t))
			    (read-icp-remote-value))
			  (read-icp-remote-value)))
		    (history-collection-time
		      (read-icp-remote-value)))
	       (case type
		 (#.gsi-integer-type-tag
		  (setf (gsi-typed-array-ref integer values i) history-value))
		 (#.gsi-logical-type-tag
		  (setf (gsi-typed-array-ref logical values i) history-value))
		 (#.gsi-64bit-float-type-tag
		  (setf (gsi-typed-array-ref 64bit-float values i) history-value)
		  (reclaim-managed-float history-value))
		 (#.gsi-string-type-tag
		  (setf (gsi-typed-array-ref string values i) history-value))
		 (#.gsi-symbol-type-tag
		  (setf (gsi-typed-array-ref symbol values i) history-value))
		 ((#.gsi-value-type-tag #.gsi-quantity-type-tag)
		  (setf (gsi-typed-array-ref gsi-item values i) history-value)))
	       (setf (gsi-typed-array-ref 64bit-float timestamps i) history-collection-time)
	       (reclaim-managed-float history-collection-time)))))))
    (t item history)))

(defun-simple-resumable-icp-function write-gsi-history (history item)
  (runtime-current-system-case
    (gsi
      (cond
	((or (null history)
	     (=f #.gsi-null-type-tag (gsi-instance-value-type item)))
	 (write-icp-byte #.gsi-null-type-tag))
	(t
	 (write-icp-byte #.gsi-sequence-type-tag)
	 (write-icp-fixnum (gsi-history-length history))
	 (loop with type = (gsi-instance-class-type item)
	       with values = (gsi-history-values history)
	       with timestamps = (gsi-history-timestamps history)
	       for i fixnum from 0 below (gsi-history-length history)
	       for history-value = (case type
				     (#.gsi-integer-type-tag
				      (gsi-typed-array-ref integer values i))
				     (#.gsi-logical-type-tag
				      (gensym-cons
					(gsi-typed-array-ref logical values i)
					'truth-value))
				     (#.gsi-string-type-tag
				      (gsi-typed-array-ref string values i))
				     (#.gsi-symbol-type-tag
				      (gsi-typed-array-ref symbol values i))
				     (#.gsi-64bit-float-type-tag
				      (gsi-typed-array-ref 64bit-float values i))
				     ((#.gsi-value-type-tag #.gsi-quantity-type-tag)
				      (gsi-typed-array-ref gsi-item values i)))
	       for history-collection-time = (gsi-typed-array-ref 64bit-float timestamps i)
	       do
	   (write-icp-byte #.gsi-structure-type-tag)
	   (write-icp-interned-list-as-value-type
	     attributes-of-history-element-structure-as-interned-list)
	   (write-icp-remote-value history-value)
	   (case type
	     (#.gsi-64bit-float-type-tag (reclaim-managed-float history-value))
	     (#.gsi-logical-type-tag (reclaim-gensym-cons history-value)))
	   (write-icp-remote-value history-collection-time)
	   (reclaim-managed-float history-collection-time)))))
    (t
      history item)))

(defvar pending-write-reference-list nil)
(defvar using-pending-write-reference-list nil)

(defmacro write-icp-item-reference-1 (item)
  `(if (null using-pending-write-reference-list)
       (let ((pending-write-reference-list nil)
	     (using-pending-write-reference-list t))
	 (prog1 (write-icp-item-reference ,item)
	   (reclaim-icp-list pending-write-reference-list)))
       (write-icp-item-reference ,item)))

(defun write-icp-item-reference-1-function (item)
  (write-icp-item-reference-1 item))

(def-icp-value-writer item-copy
  (let ((existing-index (when item-copy-index-space
			  (lookup-index-in-index-space item-copy item-copy-index-space))))
    (cond (existing-index
	   (write-icp-byte rpc-existing-item-copy)
	   (write-icp-fixnum existing-index))
	  (t
	   (cond ((current-system-case
		    (ab (and (eq item-copy-handle-for-root-item 't)
			     (not (get-icp-object-index-for-registered-item ; skip the difficult case
				    item-copy (icp-input-port current-icp-socket)))))
		    (gsi nil))
		  (write-icp-byte rpc-new-item-copy-with-reference)
		  (write-icp-item-reference-1 item-copy))
		 ((and item-copy-handle-for-root-item
		       (eq item-copy item-copy-root-item))
		  (write-icp-byte rpc-new-item-copy-with-handle)
		  (write-icp-fixnum item-copy-handle-for-root-item))
		 (t
		  (write-icp-byte rpc-new-item-copy)))
	   (write-icp-item-new-copy item-copy)))))

(def-icp-value-reader item-copy
  (let ((tag (read-icp-byte)))
    (cond ((=f rpc-existing-item-copy tag)
	   (get-object-from-index-space item-copy-index-space (read-icp-fixnum)))
	  ((=f rpc-new-item-copy-with-handle tag)
	   (let* ((handle (read-icp-fixnum))
		  (item-copy (read-icp-item-new-copy)))
	     (when item-copy
	       ;; Don't call store-corresponding-icp-object since this object is a copy,
	       ;; there will always be a registered object at this index, by this time.
	       ;; item-with-handle-index-space
	       (register-item-with-handle-on-port handle item-copy current-icp-port)
	       (current-system-case
		 (ab  (set-icp-object-index-for-registered-item item-copy handle current-icp-port))
		 (gsi (set-icp-object-index-for-gsi-instance item-copy handle current-icp-port))))
	     item-copy))
	  ((=f rpc-new-item-copy-with-reference tag)
	   (let* ((reference (read-icp-item-reference))
		  (handle (when reference
			    (current-system-case
			      (ab (get-icp-object-index-for-registered-item
				    reference current-icp-port))
			      (gsi (get-icp-object-index-for-gsi-instance
				     reference current-icp-port)))))
		  (item-copy (read-icp-item-new-copy)))
	     ;; Don't call store-corresponding-icp-object since this object is a copy,
	     ;; there will always be a registered object at this index, by this time.
	     ;; item-with-handle-index-space
	     (when (and handle item-copy)
	       (register-item-with-handle-on-port handle item-copy current-icp-port)
	       (current-system-case
		 (ab  (set-icp-object-index-for-registered-item item-copy handle current-icp-port))
		 (gsi (set-icp-object-index-for-gsi-instance item-copy handle current-icp-port))))
	     item-copy))
	  ((=f rpc-new-item-copy tag)
	   (read-icp-item-new-copy))
	  (t
	   #+development
	   (error "read-icp-item-copy: tag was ~S" tag)
	   (icp-out-of-synch 7)))))

(def-icp-value-writer item
  (with-icp-item item
    (case (runtime-current-system-case
	    (ab
	      (if (class-description-p item)
		  'reference
		  write-remote-value-items-kind))
	    (gsi
	      (cond ((not (gsi-instance-p item))
		     'copy)
		    ((eq #.gsi-item-handle-type-tag (gsi-instance-value-type item))
		     'handle)
		    ((gsi-item-reference-flag-value item)
		     'reference)
		    (t
		     'copy))))
      (handle
       (write-icp-item-handle item))
      (reference
       (write-icp-item-reference-1 item))
      (copy
       (write-icp-item-copy item)))))

(def-icp-value-reader item
  (fixnum-case (peek-icp-byte)
    ((#.rpc-handle-for-sending-side-object-type-tag
      #.rpc-handle-for-receiving-side-object-handle-type-tag
      #.rpc-handle-for-temporary-object-handle-type-tag
      #.rpc-handle-for-new-sending-side-object-type-tag)
     (read-icp-item-reference))
    ((#.rpc-existing-item-copy
      #.rpc-new-item-copy
      #.rpc-new-item-copy-with-handle
      #.rpc-new-item-copy-with-reference)
     (read-icp-item-copy))
    (t nil)))

(def-icp-value-writer item-handle
  (write-icp-byte rpc-object-handle-type-tag)
  (write-icp-fixnum 
    (runtime-current-system-case
      (ab  (get-icp-object-index-for-registered-item item-handle current-icp-port))
      (gsi (gsi-instance-value item-handle)))))	       

(def-icp-value-reader item-handle
  nil)

(def-icp-value-writer value-or-reference-argument-list
  (write-icp-unsigned-integer (length value-or-reference-argument-list))
  (loop for value-or-item in value-or-reference-argument-list
	do (let ((write-remote-value-items-kind 'reference))
	     (write-icp-remote-value value-or-item))))

(def-icp-value-reader value-or-reference-argument-list
  (loop repeat (read-icp-unsigned-integer)
	collect (with-item-index-space ()
		  (read-icp-remote-value))
	  using icp-cons))

(def-icp-value-writer resumable-rpc-argument-list ;actually an array for GSI
  (runtime-current-system-case
    (ab
     (write-icp-unsigned-integer (length resumable-rpc-argument-list))
     (loop for value-or-object in resumable-rpc-argument-list
	   for kind = (car value-or-object)
	   do (with-item-index-space ()
		(case kind
		  (handle
		   (let ((write-remote-value-items-kind 'handle))
		     (write-icp-remote-value (cdr value-or-object))))
		  (value 
		   (let ((write-remote-value-items-kind 'copy)) ; ??
		     (write-icp-remote-value (cdr value-or-object))))
		  (reference
		   (let ((write-remote-value-items-kind 'reference))
		     (write-icp-remote-value (cdr value-or-object))))
		  (copy
		   (let ((write-remote-value-items-kind 'copy)
			 (item-copy-root-item (cadr value-or-object)))
		     (with-attributes-for-item-copy (cddr value-or-object)
		       (write-icp-remote-value item-copy-root-item))))
		  (t
		   #+development
		   (cerror "Resume, sending unknown RPC type ~
                           (This behavior is what the user would get)"
			   "WRITE-ICP-RPC-VALUE-OR-OBJECT: unexpected kind ~a"
			   kind)
		   (write-icp-byte rpc-unknown-type-tag))))))
    (gsi
      (let* ((actual-size
	       (or rpc-argument-count-override?
		   (if resumable-rpc-argument-list
		       (-f (gsi-managed-array-length resumable-rpc-argument-list) gsi-magic-offset)
		       0))))
	(write-icp-unsigned-integer actual-size)
	(loop for i from gsi-magic-offset
		    to actual-size
	      as value-or-object = (gsi-managed-svref resumable-rpc-argument-list i)
	      do (let ((write-remote-value-items-kind 'copy))
		   (with-item-index-space ()
		     (write-icp-remote-value value-or-object))))))))

(defun-simple make-gsi-rpc-argument-list (length)
  (let ((arg-array (gsi-allocate-managed-array (+f length gsi-magic-offset))))	       
    (gsi-push-onto-appropriate-list (make-gsi-array-wrapper 'managed-array arg-array))
    (setf (gsi-managed-svref arg-array 0) gsi-magic-number)
    arg-array))

(defvar rpc-argument-list-error nil)

(def-icp-value-reader resumable-rpc-argument-list ;actually an array for GSI
  (let ((length (read-icp-unsigned-integer))
	(rpc-argument-list-error nil))
    (runtime-current-system-case
      (ab
       (let* ((initial-frame-serial-number
		(copy-frame-serial-number (current-frame-serial-number)))
	      (argument-list
		(loop repeat length
		      collect (with-item-index-space ()
				(read-icp-remote-value))
			using icp-cons)))
	 (icp-cons initial-frame-serial-number
		   (icp-cons rpc-argument-list-error
			     argument-list))))
      (gsi
	(let ((arg-array (make-gsi-rpc-argument-list length)))
	  (loop for item-count from gsi-magic-offset below (+f length gsi-magic-offset)
		for argument = (with-item-index-space ()
				 (read-icp-remote-value))
		do
	    (setf (gsi-managed-svref arg-array item-count) argument))
	  arg-array)))))

(defun-simple intern-list-of-item-reference-attributes
    (identifying-attributes-plist creation-attributes-plist)
  (let ((class (or (getfq identifying-attributes-plist 'class)
		   (getfq creation-attributes-plist 'class))))
    (interning-list
      (intern-next-element class)
      (loop for (key val) on identifying-attributes-plist by 'cddr
	    unless (eq key 'class)
	      do (intern-next-element key))
      (loop for (key val) on creation-attributes-plist by 'cddr
	    unless (eq key 'class)
	      do (intern-next-element key)))))

; pending-write-reference-list
; using-pending-write-reference-list
(defvar corresponding-icp-object-index-for-item-reference nil)

(def-icp-value-writer item-reference
  (with-disabled-write-icp-suspension
    (multiple-value-bind (reference-type corresponding-icp-object-index pending-index
			  identifying-attributes-plist creation-attributes-plist)
	(network-item-reference-information item-reference)
      pending-index ; needed to send recursice references to G2 (but not GSI)
      (unless (if (eq reference-type 'new)
		  (with-bifurcated-version-for-output (supports-new-references-icp-version)
		    nil t)
		  (with-bifurcated-version-for-output (item-reference-icp-version)
		    nil t))
	(write-icp-byte gsi-null-type-tag)
	(return-from write-icp-item-reference nil))
      (write-icp-byte
	(case reference-type
	  (temporary rpc-handle-for-temporary-object-handle-type-tag)
	  (remote rpc-handle-for-receiving-side-object-handle-type-tag)
	  (local rpc-handle-for-sending-side-object-type-tag)
	  (new rpc-handle-for-new-sending-side-object-type-tag)))
      (write-icp-fixnum corresponding-icp-object-index)
      (when (eq 'new reference-type)
	(let ((identifying-attribute-count
		(halff (length identifying-attributes-plist)))
	      (class-is-identifying-p
		(loop for (key val) on identifying-attributes-plist by 'cddr
		      when (eq key 'class) return t
		      finally (return nil))))
	  (write-icp-fixnum
	    (if class-is-identifying-p
		(-f identifying-attribute-count)
		identifying-attribute-count)))
	(write-icp-interned-list-as-value-type
	  (intern-list-of-item-reference-attributes
	    identifying-attributes-plist
	    creation-attributes-plist))
	(let ((corresponding-icp-object-index-for-item-reference nil))
	  (loop for (key val) on identifying-attributes-plist by 'cddr
		unless (eq key 'class)
		  do (write-icp-remote-value val))
	  (loop for (key val) on creation-attributes-plist by 'cddr
		unless (eq key 'class)
		  do (write-icp-remote-value val)))
	(reclaim-icp-list identifying-attributes-plist)
	(reclaim-icp-list creation-attributes-plist)))))

(defun-simple-resumable-icp-function read-reference-attributes (attr-list limit class?)
  (runtime-current-system-case
    (ab
      (allocate-evaluation-structure
	(let ((list (loop for attr in attr-list
			  for i from 0 below limit
			  for value = (read-icp-remote-value)
			  collect attr using eval-cons
			  collect (if (evaluation-unsigned-vector-16-p value)
				      (evaluation-unsigned-vector-16-value value)
				      value)
			    using eval-cons)))
	  (if class?
	      (eval-cons 'class (eval-cons class? list))
	      list))))
    (t attr-list limit class?
       nil)))

(def-icp-value-reader item-reference
  (let* ((type-tag (read-icp-byte))
	 (corresponding-icp-object-index (read-icp-fixnum))
	 (item (fixnum-case type-tag
		 (#.rpc-handle-for-temporary-object-handle-type-tag
		  (get-object-from-index-space
		    current-temporary-icp-object-index-space
		    corresponding-icp-object-index))
		 (#.rpc-handle-for-sending-side-object-type-tag
		  (get-from-icp-port current-icp-port
				     corresponding-icp-object-index
				     'item-index-space))
		 (#.rpc-handle-for-receiving-side-object-handle-type-tag
		  (get-from-icp-port (icp-output-port (parent-icp-socket current-icp-port))
				     corresponding-icp-object-index
				     'item-index-space))
		 (#.rpc-handle-for-new-sending-side-object-type-tag
		  'reading-new-item-reference)
		 (t
		  (icp-error "Internal error: Bad type-tag for reading an item reference")))))
    (unless (eq item 'reading-new-item-reference)
      (unless item
	(setq rpc-argument-list-error
	      (tformat-text-string "an item sent by reference has been deleted")))
      (return-from read-icp-item-reference item))
    (let* ((identifying-attributes-count-with-class (read-icp-fixnum))
	   (class-is-identifying-p (>f 0 identifying-attributes-count-with-class))
	   (identifying-attributes-count (if class-is-identifying-p
					     (-f identifying-attributes-count-with-class)
					     identifying-attributes-count-with-class))
	   (item (runtime-current-system-case
		   (gsi
		     (let* ((identifying-attribute-count-for-item-new-copy
			      identifying-attributes-count)
			    (corresponding-icp-object-index-for-item-new-copy
			      corresponding-icp-object-index)
			    (item-being-read-for-new-reference nil)
			    (item (read-icp-item-new-copy)))
		       (when class-is-identifying-p
			 (setf (gsi-item-class-is-identifying-flag-value item) t))
		       item))
		   (ab (let* ((class+attributes-list
				(interned-list--list (read-icp-interned-list-as-value-type)))
			      (non-class-ident-attr-count
				(if class-is-identifying-p
				    (1-f identifying-attributes-count)
				    identifying-attributes-count)))
			 (lookup-or-create-item-from-reference-attributes
			   (read-reference-attributes
			     (cdr class+attributes-list)
			     non-class-ident-attr-count
			     (when class-is-identifying-p (car class+attributes-list)))
			   (read-reference-attributes
			     (nthcdr non-class-ident-attr-count (cdr class+attributes-list))
			     most-positive-fixnum
			     (unless class-is-identifying-p (car class+attributes-list)))
			   t t))))))
      (cond
	((and item
	      (not (text-string-p item))
	      (runtime-current-system-case
		(ab (framep item))
		(t t)))
	 (store-corresponding-item corresponding-icp-object-index item)
	 (runtime-current-system-case
	   (ab  (set-icp-object-index-for-registered-item
		  item corresponding-icp-object-index (icp-input-port current-icp-socket)))
	   (gsi (set-icp-object-index-for-gsi-instance
		  item corresponding-icp-object-index (icp-input-port current-icp-socket))))
	 (runtime-current-system-case
	   (gsi (gsi-call-receive-registration-callback item)))
	 item)
	(t
	 (setq rpc-argument-list-error
	       (if (text-string-p item)
		   item
		   (tformat-text-string
		     "an item sent by reference could not be found or constructed")))
	 nil)))))


(defun-simple gsi-call-receive-registration-callback (item)
  (call-gsi-callback gsi-receive-registration item))

(defun-simple-resumable-icp-function write-icp-item-reference-2 (item)
  (with-item-index-space ()
    (write-icp-item-reference item)))

(defun-simple-resumable-icp-function read-icp-item-reference-2 ()
  (with-item-index-space ()
    (let ((rpc-argument-list-error nil))
      (read-icp-item-reference))))

(def-icp-message-type create-item-reference ((item-reference-2 item))
  (declare (ignore item)) ; does nothing.  (it's all handled by the value type item-reference)
  nil)

; pending-write-reference-list
(defun network-item-reference-information (item)
  (let* ((pending-index (when using-pending-write-reference-list
			  (loop for i from 0
				for pending-item in pending-write-reference-list
				when (eq item pending-item)
				  return i)))
	 (class-description-p
	   (runtime-current-system-case
	     (ab (class-description-p item))
	     (gsi nil))))
    class-description-p
    (let ((object-map (runtime-current-system-case
			(ab (if class-description-p
				(icp-object-map-for-class-description item)
				(icp-object-map-for-registered-item-function item)))
			(gsi (icp-object-map-for-gsi-instance item)))))
      (macrolet ((lookup-existing-index (type port)
		   `(let ((corresponding-icp-object-index
			    (getfq object-map (,port current-icp-socket))))
		      (when corresponding-icp-object-index
			(return-from network-item-reference-information
			  (values ',type corresponding-icp-object-index pending-index))))))
	(when inhibit-corresponding-icp-object-making
	  (lookup-existing-index temporary icp-output-port))
	(unless corresponding-icp-object-index-for-item-reference
	  (lookup-existing-index local icp-output-port)
	  (lookup-existing-index remote icp-input-port))))
    (let ((corresponding-icp-object-index
	    (or corresponding-icp-object-index-for-item-reference
		(runtime-current-system-case
		  (ab  (if class-description-p
			   (establish-new-object-index-for-class-description
			     item (icp-output-port current-icp-socket) nil)
			   (establish-new-object-index-for-registered-item
			     item (icp-output-port current-icp-socket) nil)))
		  (gsi (establish-new-object-index-for-gsi-instance
			 item (icp-output-port current-icp-socket) nil))))))
      (cond (inhibit-corresponding-icp-object-making
	     (values 'temporary corresponding-icp-object-index nil))
	    (t
	     (when using-pending-write-reference-list
	       (setq pending-write-reference-list
		     (nconc pending-write-reference-list (icp-list item))))
	     (multiple-value-bind (identifying-attributes-plist creation-attributes-plist)
		 (if class-description-p
		     (get-class-description-reference-attributes item)
		     (get-item-reference-attributes item))
	       (values 'new corresponding-icp-object-index nil
		       identifying-attributes-plist creation-attributes-plist)))))))

(defmacro change-icp-plist (plist property value)
  `(setf ,plist (put-on-icp-plist ,property ,value ,plist)))

(defvar current-network-interface nil)
(defvar reference-class-info-p nil)

(defun get-class-description-reference-attributes (class-description)
  (current-system-case
    (ab
      (values
	(icp-list 'class (class-name-of-class-description class-description))
	(let ((reference-class-info-p t))
	  (get-class-info
	    (class-name-of-class-description class-description)
	    nil
	    nil))))
    (gsi class-description
	 nil)))

(defun get-item-reference-attributes (item)
  (runtime-current-system-case
    (ab
     (multiple-value-bind (interface-identifying-attributes interface-creation-attributes
							    item-reference-options)
	 (get-item-reference-attributes-from-current-interface)
       (let* ((local-home (name-for-local-home))
	      (identifying-attributes-plist
		(select-attributes-from-item
		  item interface-identifying-attributes
		  nil))
	      (identifying-attributes-home
		(getfq identifying-attributes-plist 'home 0))
	      (identifying-attributes-home-1
		(if (eql 0 identifying-attributes-home)
		    local-home
		    identifying-attributes-home))
	      (localp (equalw local-home identifying-attributes-home-1))
	      (home-for-network
		(if (second (assq 'convert-home-to-local item-reference-options))
		    local-home
		    identifying-attributes-home-1))
	      (identifying-attributes-class (getfq identifying-attributes-plist 'class 0))
	      (identifying-attributes-names (getfq identifying-attributes-plist 'names 0))
	      (identifying-attributes-e-d-t (getfq identifying-attributes-plist 'effective-data-type 0))
	      (identifying-attributes-d-u-i (getfq identifying-attributes-plist 'default-update-interval 0))
	      (creation-attributes-plist
		(select-attributes-from-item
		  item interface-creation-attributes
		  (nconc (when (eql 0 identifying-attributes-class)
			   (eval-list 'class (class item)))
			 (when (eql 0 identifying-attributes-names)
			   (eval-list 'names
				      ;; RH: This used to call (get-names item)
				      ;; which was the macro-generated getter
				      ;; for the now-defunct virtual attribute, NAMES.
				      ;; The following line of code returns the
				      ;; same value.
				      (get-attribute-description-evaluation-value
					item
					(get-slot-description-of-frame
					  'name-or-names-for-frame item nil))))
			 (when (and (of-class-p (or current-network-interface
						    (when current-icp-socket
						      (find-network-interface-for-icp-socket
							current-icp-socket nil)))
						'gsi-interface)
				    (of-class-p item 'gsi-data-service))
			   (nconc (when (eql 0 identifying-attributes-e-d-t)
				    (eval-list 'effective-data-type
					       (get-effective-data-type item)))
				  (when (eql 0 identifying-attributes-d-u-i)
				    (eval-list 'default-update-interval
					       (background-collection-interval? item))))))))
	      (add-home-to-name (second (assq 'add-home-to-name item-reference-options)))
	      (names-for-network
		(convert-names-for-network
		  (if (not (eql 0 identifying-attributes-names))
		      identifying-attributes-names
		      (getfq creation-attributes-plist 'names))
		  add-home-to-name localp identifying-attributes-home-1)))
	 (change-icp-plist identifying-attributes-plist 'home home-for-network)
	 (if (not (eql 0 identifying-attributes-names))
	     (change-icp-plist identifying-attributes-plist 'names names-for-network)
	     (change-icp-plist creation-attributes-plist 'names names-for-network))
	 (values identifying-attributes-plist creation-attributes-plist))))
    (gsi
      (loop with attribute-count = (gsi-attribute-count item)
	    with attribute-count-with-offset = (+f attribute-count gsi-magic-offset)
	    with attributes = (gsi-attributes item)
	    for i from gsi-magic-offset below attribute-count-with-offset
	    for attribute = (gsi-managed-svref attributes i)
	    for attribute-value = (gsi-attribute-instance attribute)
	    for transientp = (gsi-attribute-is-transient-p attribute)
	    for identifyingp = (gsi-attribute-is-identifying-p attribute)
	    for attribute-name = (gsi-attribute-qualified-name attribute)
	    when (and (not transientp) identifyingp)
	      nconc (icp-list attribute-name attribute-value)
	      into identifying-attributes-plist
	    when (and (not transientp) (not identifyingp))
	      nconc (icp-list attribute-name attribute-value)
	      into creation-attributes-plist
	    finally
	      (unless (getfq identifying-attributes-plist 'home)
		(setq identifying-attributes-plist
		      (nconc (icp-list 'home gsi-local-home)
			     identifying-attributes-plist)))
	      (macrolet ((add-if-not-present (name value)
			   `(unless (or (getfq identifying-attributes-plist ',name)
					(getfq creation-attributes-plist ',name))
			      (let ((value-1 ,value))
				(when value-1
				  (if ,(case name
					 (class `(gsi-item-class-is-identifying-flag-value item))
					 (names `(gsi-item-name-is-identifying-flag-value item)))
				      (setq identifying-attributes-plist
					    (nconc (icp-list ',name value-1)
						   identifying-attributes-plist))
				      (setq creation-attributes-plist
					    (nconc (icp-list ',name value-1)
						   creation-attributes-plist))))))))
		(add-if-not-present class (class-for-gsi-item item))
		(add-if-not-present names (gsi-instance-name item)))
	      ;; make any desired adjustments to name
	      (return (values identifying-attributes-plist creation-attributes-plist))))))

(defun select-attributes-from-item (item identifying-attributes network-attribute-plist)
  (runtime-current-system-case
    (ab
      (macrolet ((maybe-add-attribute (attribute network-attribute item)
		   `(let ((attribute ,attribute)
			  (network-attribute ,network-attribute)
			  (item ,item)
			  (class-if-specific? nil))
		      (case attribute
			#+ignore
			(frame-serial-number
			 (change-icp-plist network-attribute-plist network-attribute
					   (frame-serial-number item)))
			(class-description
			 (change-icp-plist network-attribute-plist network-attribute
					   (class-description (class item))))
			(t
			 (with-slot-evaluation-value-from-user-attribute-if-present
			     (value item attribute class-if-specific?
				    (when all-symbol-p
				      (change-icp-plist network-attribute-plist
							network-attribute nil)))
			   (change-icp-plist network-attribute-plist
					     network-attribute value)))))))
	(loop with all-symbol-p = t
	      for attr-spec in identifying-attributes
	      do
	  (if (symbolp attr-spec)
	      (maybe-add-attribute attr-spec attr-spec item)
	      (gensym-dstruct-bind ((spec-class . class-attr-specs) attr-spec)
		(setq all-symbol-p nil)
		(when (of-class-p item spec-class)
		  (loop for class-attr-spec in class-attr-specs
			do
		    (if (eq (car class-attr-spec) '*)
			(return-from select-attributes-from-item
			  (with-slot-evaluation-value-from-user-attribute-if-present
			      (value item identifying-attributes nil nil)
			    (prog1 (loop for (attribute . attribute-value)
					     being each evaluation-structure-pair of value
					 do
				     (change-icp-plist network-attribute-plist
						       attribute attribute-value))
			      (reclaim-if-evaluation-value value))))
			(maybe-add-attribute
			  (car class-attr-spec)
			  (or (cdr class-attr-spec) (car class-attr-spec))
			  item))))))
	      finally (return network-attribute-plist))))
    (t
      item identifying-attributes network-attribute-plist
      nil)))

(defun-simple identifying-or-creation-attributes-of-item-for-interface (item interface identifying-p)
  (runtime-current-system-case
    (ab
      (let ((current-network-interface interface))
	(multiple-value-bind (identifying-attributes-plist creation-attributes-plist)
	    (get-item-reference-attributes item)
	  (reclaim-eval-list (if identifying-p
				 creation-attributes-plist
				 identifying-attributes-plist))
	  (allocate-evaluation-structure (if identifying-p
					     identifying-attributes-plist
					     creation-attributes-plist)))))
    (t
      item interface identifying-p
      nil)))

(defun lookup-or-create-item-from-reference-attributes
    (identifying-attributes creation-attributes reclaim-p allow-create-p)
  (runtime-current-system-case
    (ab
      (multiple-value-bind (interface-identifying-attributes interface-creation-attributes item-reference-options)
	  (get-item-reference-attributes-from-current-interface)
	(let ((item-or-symbol
		(when (second (or (assq 'reference-lookup item-reference-options) '(reference-lookup t)))
		  (multiple-value-bind (identifying-class identifying-names identifying-attribute-translations)
		      (process-register-item-reference-attributes
			identifying-attributes nil
			interface-identifying-attributes interface-creation-attributes item-reference-options)
		    (prog1 (lookup-item-from-identifying-attributes-and-translations
			     identifying-attributes
			     identifying-class identifying-names identifying-attribute-translations
			     nil)
		      (reclaim-icp-list identifying-attribute-translations))))))
	  (prog1 (case item-or-symbol
		   ((more-than-one-match)
		    (tformat-text-string "an item sent by reference matched more than one item"))
		   ((nil)
		    (when (and allow-create-p
			       (second (or (assq 'reference-creation item-reference-options) '(reference-creation t))))
		      (multiple-value-bind (creation-class creation-names
					    identifying-attribute-translations creation-attribute-translations)
			  (process-register-item-reference-attributes
			    identifying-attributes creation-attributes
			    interface-identifying-attributes interface-creation-attributes item-reference-options)	
			(prog1 (create-item-from-attributes-and-translations
				 identifying-attributes creation-attributes
				 creation-class creation-names
				 identifying-attribute-translations creation-attribute-translations)
			  (reclaim-icp-list identifying-attribute-translations)
			  (reclaim-icp-list creation-attribute-translations)))))
		   (t item-or-symbol))
	    (when reclaim-p
	      (reclaim-evaluation-value identifying-attributes)
	      (reclaim-evaluation-value creation-attributes))))))
    (gsi
      identifying-attributes creation-attributes reclaim-p allow-create-p
      nil)))

(defun process-register-item-reference-attributes
    (identifying-attributes creation-attributes
     interface-identifying-attributes interface-creation-attributes item-reference-options)
  (runtime-current-system-case
    (ab
      (let* ((local-home (name-for-local-home))
	     (item-home (or (evaluation-structure-slot identifying-attributes 'home)
			    local-home))
	     (localp (equalw local-home item-home))
	     (class-for-network
	       (or (and creation-attributes
			(evaluation-structure-slot creation-attributes 'class))
		   (evaluation-structure-slot identifying-attributes 'class))))
	(when (eq class-for-network 'class-description)
	  (return-from process-register-item-reference-attributes
	    (values class-for-network (evaluation-structure-slot identifying-attributes 'names)
		    nil nil))) ; no translations
	(let* ((add-home-to-name (second (assq 'add-home-to-name item-reference-options)))
	       (names-for-network
		 (or (and creation-attributes
			  (evaluation-structure-slot creation-attributes 'names))
		     (evaluation-structure-slot identifying-attributes 'names)))
	       (names
		 (if (or (eq add-home-to-name t)
			 (and (eq add-home-to-name 'unless-local) (not localp)))
		     (when names-for-network
		       (if (symbolp names-for-network)
			   (add-home-to-name item-home names-for-network)
			   (changing-elements-of-evaluation-sequence (name names-for-network)
                             (add-home-to-name item-home name))))
		     names-for-network))
	       (non-local-item-class-info (assq 'non-local-item-class item-reference-options))
	       (non-local-item-class-default (second non-local-item-class-info))
	       (non-local-item-class-prefix (third non-local-item-class-info))
	       (class (if localp
			  class-for-network
			  (or (when non-local-item-class-prefix
				(let ((prefixed-class
					(intern-text-string
					  (tformat-text-string "~A~A"
							       non-local-item-class-prefix
							       class-for-network))))
				  (when (classp prefixed-class)
				    prefixed-class)))
			      non-local-item-class-default
			      class-for-network))))
	  (values class names
		  (get-attribute-translations class interface-identifying-attributes)
		  (when creation-attributes
		    (get-attribute-translations class interface-creation-attributes))))))
    (t
      identifying-attributes creation-attributes
      interface-identifying-attributes interface-creation-attributes item-reference-options
      nil)))

(defun get-attribute-translations (class interface-attributes)
  (runtime-current-system-case
    (ab
      (loop for attr-spec in interface-attributes
	    unless (symbolp attr-spec)
	      nconc 
	      (gensym-dstruct-bind ((spec-class . class-attr-specs) attr-spec)
		(when (subclassp class spec-class)
		  (loop for (attribute . network-attribute) in class-attr-specs
			when (and network-attribute
				  (not (eq attribute network-attribute)))
			  collect (icp-cons network-attribute attribute)
			    using icp-cons)))))
    (t
      class interface-attributes
      nil)))

(defun lookup-item-from-frame-or-frames
    (frame-or-frames identifying-attributes class names attribute-translations list-p)
  (current-system-case
    (ab
      (if (listp frame-or-frames)
	  (if list-p
	      (loop for item in frame-or-frames
		    when (item-matches-identifying-attributes-p
			   item identifying-attributes class names attribute-translations)
		      collect item using eval-cons)
	      (loop with first-match = nil
		    for item in frame-or-frames
		    when (item-matches-identifying-attributes-p
			   item identifying-attributes class names attribute-translations)
		      do (if first-match
			     (return 'more-than-one-match)
			     (setq first-match item))
		    finally (return first-match)))
	  (when (and frame-or-frames
		     (item-matches-identifying-attributes-p
		       frame-or-frames
		       identifying-attributes class names attribute-translations))
	    (if list-p
		(eval-list frame-or-frames)
		frame-or-frames))))
    (t frame-or-frames identifying-attributes class names attribute-translations list-p
       nil)))

(defun lookup-item-from-identifying-attributes-and-translations
    (identifying-attributes class names attribute-translations list-p)
  (runtime-current-system-case
    (ab
      (when (eq class 'class-description)
	(return-from lookup-item-from-identifying-attributes-and-translations
	  (let ((class-description (class-description (if (consp names)
							  (car names)
							  names))))
	    (if (and class-description list-p)
		(eval-list class-description)
		class-description))))
      (multiple-value-bind (role-name value-or-table)
	  (choose-role-for-identifying-attributes identifying-attributes class names
						  attribute-translations)
	(case role-name
	  (uuid
	   (lookup-item-from-frame-or-frames
	     value-or-table
	     identifying-attributes class names attribute-translations
	     list-p))
	  (named-by
	   (lookup-item-from-frame-or-frames
	     value-or-table
	     identifying-attributes class names attribute-translations
	     list-p))
	  (indexed-attribute
	   (when value-or-table
	     (if list-p
		 (loop for (item . defining-classes) being each
		       binary-tree-entry-cons of value-or-table
		       when (item-matches-identifying-attributes-p
			      item identifying-attributes class names attribute-translations)
			 collect item using eval-cons)
		 (loop with first-match = nil
		       for (item . defining-classes) being each
		       binary-tree-entry-cons of value-or-table
		       when (item-matches-identifying-attributes-p
			      item identifying-attributes class names attribute-translations)
			 do (if first-match
				(return 'more-than-one-match)
				(setq first-match item))
		       finally (return first-match)))))
	  (class
	   ;; collect-instances-of-class-for-role-service does strange things,
	   ;; if the class is a subclass of connection
	   (if list-p
	       (loop for item being each class-instance of class
		     when (item-matches-identifying-attributes-p
			    item identifying-attributes class names attribute-translations)
		       collect item using eval-cons)
	       (loop with first-match = nil
		     for item being each class-instance of class
		     when (item-matches-identifying-attributes-p
			    item identifying-attributes class names attribute-translations)
		       do (if first-match
			      (return 'more-than-one-match)
			      (setq first-match item))
		     finally (return first-match)))))))
    (t
      identifying-attributes class names attribute-translations list-p
      nil)))

(defun-simple attribute-is-in-identifying-attributes-p
    (attr-name identifying-attributes attribute-translations)
  (current-system-case
    (ab
      (loop for (name . value) being each evaluation-structure-pair of identifying-attributes
	    for translated-name = (or (cdr (assq name attribute-translations)) name)
	    for attribute = translated-name
	    when (eq attribute attr-name)
	      return value))
    (t
      attr-name identifying-attributes attribute-translations
      nil)))

;if one of the translated identifying-attributes is names, or is an indexed-attribute, use it.
;otherwise, just check every item of class class.
(defun choose-role-for-identifying-attributes (identifying-attributes class names
					       attribute-translations)
  (runtime-current-system-case
    (ab
      (let (uuid indexed-attribute-table indexed-attribute-value indexed-attribute)
	(cond ((setq uuid (attribute-is-in-identifying-attributes-p
			    'uuid identifying-attributes attribute-translations))
	       (values 'uuid (get-item-or-item-list-for-uuid uuid)))
	      ((and (attribute-is-in-identifying-attributes-p
		      'names identifying-attributes attribute-translations)
		    (or (symbolp names)
			(=f 1 (evaluation-sequence-length names))))
	       (values 'named-by
		       (frame-or-frames-with-this-name
			 (if (symbolp names)
			     names
			     (loop for value being each evaluation-sequence-element of names
				   do (return value))))))
	      ((setq indexed-attribute-table
		     (loop for (name . value) being each evaluation-structure-pair of identifying-attributes
			   for translated-name = (or (cdr (assq name attribute-translations)) name)
			   for attribute = translated-name
			   for indexed-attribute-table?
			       = (and (valid-indexed-attribute-value-p
					(setq indexed-attribute-value (evaluation-value-value value)))
				      (indexed-attribute-hash-table
					(setq indexed-attribute attribute)))
			   when indexed-attribute-table?
			     return indexed-attribute-table?))
	       (values 'indexed-attribute
		       (get-indexed-attribute-parent-objects
			 indexed-attribute-value
			 indexed-attribute-table)
		       indexed-attribute))
	      (class
	       (values 'class class))
	      (t
	       (values 'class 'item)))))
    (t
      identifying-attributes class names attribute-translations
      nil)))

(defun-simple item-or-value-equal (x y)
  (current-system-case
    (ab
      (cond ((eq x y)
	     t)
	    ((or (null x) (framep x)
		 (null y) (framep y))
	     nil)
	    (t
	     (evaluation-value-eql x y))))
    (gsi
      x y
      nil)))  

(defun item-matches-identifying-attributes-p (item identifying-attributes class names
						   attribute-translations)
  (runtime-current-system-case
    (ab
     (and (or (null class) (of-class-p item class))
	  (loop for (name . value) being each evaluation-structure-pair of identifying-attributes
		for translated-name = (assq-lookup name attribute-translations name)
		for attribute = translated-name
		for attribute-class? = nil
		do
	    (when (eq attribute 'names)
	      (setq value names))
	    (if nil ;(eq attribute 'frame-serial-number)
		(unless (eql value (frame-serial-number item))
		  (return nil))
		(with-slot-evaluation-value-from-user-attribute-if-present
		    (item-value item attribute attribute-class?
				(if (eq name 'home)
				    (unless (item-or-value-equal value (name-for-local-home))
				      (return nil))
				    (return nil)))
		  (unless (item-or-value-equal value item-value)
		    (return nil))))
		finally
		  (return t))))
    (t
      item identifying-attributes class names attribute-translations
      nil)))

(defun create-item-from-attributes-and-translations
    (identifying-attributes creation-attributes
     class names
     identifying-attribute-translations creation-attribute-translations)
  (runtime-current-system-case
    (ab
      (let ((error-string
	      (if (null class)
		  #w"~Athe reference could not be created, because no class was specified"
		  (check-class-for-item-passing-1 class))))
	(cond (error-string
	       (tformat-text-string
		 error-string
		 "Error while sending an item by reference: "
		 class))
	      (t
	       (let ((item (make-transient-frame-for-item-passing class)))
		 (icp-push (icp-cons 'class nil) identifying-attribute-translations)
		 (icp-push (icp-cons 'class nil) creation-attribute-translations)
		 (let ((value-translations (icp-list (icp-cons 'names names))))
		   (copy-evaluation-structure-into-item
		     item identifying-attributes
		     identifying-attribute-translations
		     value-translations)
		   (copy-evaluation-structure-into-item
		     item creation-attributes
		     creation-attribute-translations
		     value-translations))
		 (activate-item-if-necessary item))))))
    (t
      identifying-attributes creation-attributes class names
      identifying-attribute-translations creation-attribute-translations)))


(def-system-variable remote-gsi-interface-list    rpc-common3 nil)

(defun g2-initialize-gsi-interface (interface-name class-name keep-connection-on-g2-reset
				    listener-network-type listener-host-name listener-port-name
				    remote-process-initialization-string already-initialized-p)
  (runtime-current-system-case
    (ab
      (let ((class-name (or class-name 'gsi-interface)))
	(let ((error (cond ((not (classp-function class-name))
			    #w"The interface class does not name a class")
			   ((not (subclassp-function class-name 'gsi-interface))
			    #w"The class is not a subclass of gsi-interface"))))
	  (when error
	    (writing-icp-message-group ((icp-output-port current-icp-socket))
	      (send-icp-return-initialize-gsi-interface-status error))
	    (flush-and-shutdown-icp-socket current-icp-socket)
	    (return-from g2-initialize-gsi-interface nil)))
	;; check whether an existing gsi-interface could be used instead?
	(let ((interface-frame (make-frame class-name)))
	  (icp-push interface-frame remote-gsi-interface-list)
	  (unless keep-connection-on-g2-reset
	    (set-transient-and-propagate interface-frame nil))
	  (when keep-connection-on-g2-reset
	    ;; need to do more checking, starting at
	    ;; traverse-referenced-g2-windows-and-procedure-invocations-for-saving
	    ;(set-permanent-block interface-frame)
	    ;; I don't think this is quite right
	    (set-do-not-save-in-kb interface-frame)
	    (set-runs-while-inactive interface-frame))
	  
	  (when interface-name
	    (change-slot-value interface-frame 'name-or-names-for-frame interface-name))

	  (when keep-connection-on-g2-reset
	    (let* ((listener-string
		     (case listener-network-type
		       (tcp-ip (twith-output-to-text-string
				 (tformat "tcp-ip host \"~A\" port-number ~A"
					  listener-host-name listener-port-name)))
		       (t (copy-constant-wide-string #w"none"))))
		   (listener-text (convert-text-string-to-text listener-string))
		   (actual-value		     
		     (if (eq listener-network-type 'tcp-ip)
			 (slot-value-list
			   listener-network-type
			   (copy-text-string listener-host-name)
			   (copy-text-string listener-port-name))))
		   (box-translation-and-text
		     (slot-value-cons actual-value listener-text)))
	    (set-slot-value
	      interface-frame 'gsi-connection-configuration
	      box-translation-and-text)))

	  (set-slot-value
	    interface-frame
	    'remote-process-initialization-string
	    (copy-text-string remote-process-initialization-string))
	  
	  (set-slot-value interface-frame 'gsi-interface-icp-socket current-icp-socket)
	  (when current-icp-socket
	    ;;if this GSI interface is being created on the fly, inquire of the
	    ;;remote side about resumability -- later code will be examining
	    ;;this value and changing the value in the ICP socket, which makes
	    ;;sense if the GSI interface was created by the user, but not if it
	    ;;was created by a GSI unsolicited connection. -- yduJ 3/28/01
	    (set-slot-value interface-frame
			    'disable-interleaving-of-large-messages
			    (get-remote-icp-version-info-value
			      current-icp-socket 'disable-resumability nil)))
	  
	  (setf (enclosing-interface-frame? current-icp-socket) interface-frame)
	  (frame-serial-number-setf (enclosing-interface-frame-serial-number current-icp-socket)
		(frame-serial-number interface-frame))
	  (when (runs-while-inactive-p interface-frame)
	    (activate-gsi-interface interface-frame already-initialized-p))
	  (funcall-method 'activate-if-possible-and-propagate interface-frame)
	  interface-frame)))
    (t
      interface-name class-name keep-connection-on-g2-reset
      listener-network-type listener-host-name listener-port-name
      remote-process-initialization-string already-initialized-p
      nil)))

(defun find-network-interface-for-icp-socket (icp-socket stack-eval-p)
  (runtime-current-system-case
    (ab
      (let* ((interface? (and icp-socket (enclosing-interface-frame? icp-socket)))
	     (error-string 	 ; should check interface status, too
	       (cond ((null interface?)
		      "No network interface exists for the current icp-socket")
		     ((not (frame-has-not-been-reprocessed-p
			     interface?
			     (enclosing-interface-frame-serial-number icp-socket)))
		      "The network interface has already been reclaimed"))))
	(if error-string
	    (cond ((eq stack-eval-p 'no-error)
		   error-string)
		  (stack-eval-p
		   (stack-error cached-top-of-stack error-string))
		  (t
		   (icp-error error-string)))
	    interface?)))
    (t
      icp-socket stack-eval-p
      nil)))

(defun get-item-reference-attributes-from-current-interface ()
  (runtime-current-system-case
    (ab
      (let ((interface (or current-network-interface
			   (when current-icp-socket
			     (find-network-interface-for-icp-socket current-icp-socket nil)))))
	(when interface
	  (values (get-slot-value interface 'identifying-attributes)
		  (get-slot-value interface 'creation-attributes)
		  (get-slot-value interface 'item-reference-options)))))))

(defun get-default-slot-value-from-class (class slot-name)
  (runtime-current-system-case
    (ab
     (slot-init-form (slot-description-from-class class slot-name)))
    (t
      class slot-name
      nil)))

(defun convert-names-for-network (names add-home-to-name localp item-home)
  (runtime-current-system-case
    (ab
     (if (or (eq add-home-to-name t)
	     (and (eq add-home-to-name 'unless-local) (not localp)))
	 (when names
	   (if (symbolp names)
	       (remove-home-from-name item-home names)
	       (changing-elements-of-evaluation-sequence (name names)
		 (remove-home-from-name item-home name))))
	 names))
    (t
      add-home-to-name localp item-home
      names)))

(defun put-on-icp-plist (property value plist)
  (loop for tail on plist
	when (eq (car tail) property)
	  do (setf (cadr tail) value)
	     (return plist)
	finally
	  (return (icp-cons property (icp-cons value plist)))))

(defun assq-lookup (name alist default)
  (let ((a (assq-macro name alist)))
    (if a (cdr a) default)))

(defun copy-evaluation-structure-into-item (item structure
						 attribute-translations value-translations)
  (runtime-current-system-case
    (ab
     (loop for (name . value) being each evaluation-structure-pair of structure
	   for translated-name = (assq-lookup name attribute-translations name)
	   for attribute = translated-name
	   ;; this is a bold assumption - class-qualified names received
	   ;; from users must be broken into name and class pieces
	   for attribute-class? = nil
	   for attribute-value = (assq-lookup name value-translations value)
	   do
       (when attribute
	 ;; we may want to do something with these errors
	 (let ((error-string?
		 (conclude-into-attribute-component 
		   item attribute attribute-class?
		   (copy-if-evaluation-value attribute-value)
		   nil nil)))
	   (reclaim-if-text-string error-string?)))))
    (t
      item structure attribute-translations value-translations
      nil)))

(defvar home-name-separator #w"--")

(defun remove-home-from-name (home name)
  (if (not (and name (symbolp name)
		home (or (symbolp home) (text-string-p home))))
      name
      (let* ((name-string (symbol-name-text-string name))
	     (name-string-length (wide-string-length name-string))
	     (home-string (if (symbolp home)
			      (symbol-name-text-string home)
			      home))
	     (home-string-length (wide-string-length home-string))
	     (home-name-separator-length (wide-string-length home-name-separator))
	     (prefix-length (+f home-string-length home-name-separator-length)))
	(if (or (=f 0 home-string-length)
		(=f 0 name-string-length)
		(<f name-string-length prefix-length)
		(loop for i fixnum from 0 below home-string-length
		      unless (char=w (charw name-string i) (charw home-string i))
			return t
		      finally (return nil))
		(loop for i fixnum below home-name-separator-length
		      unless (char=w (charw home-name-separator i)
				     (charw name-string (+f i home-string-length)))
			return t
		      finally (return nil)))
	    name
	    (intern-text-string
	      (copy-text-string-portion name prefix-length name-string-length))))))

(defun add-home-to-name (home name)
  (if (not (and name (symbolp name)
		home (or (symbolp home) (text-string-p home))))
      name
      (let ((name-string (symbol-name-text-string name))
	    (home-string (if (symbolp home)
			     (symbol-name-text-string home)
			     home)))
	(intern-text-string
	  (tformat-text-string "~A~A~A"
			       home-string home-name-separator name-string)))))



(defun interned-list--remote-procedure-item-passing-lists (interned-list)
  (let ((list (interned-list--list interned-list)))
    (if (and list (fixnump (car list)) (null (cdr list)))
	(let ((list-of-nils (loop for i from 0 below (car list)
				  collect nil using icp-cons)))
	  (values list-of-nils list-of-nils list-of-nils list-of-nils list-of-nils list-of-nils nil))
	(if (=f 7 (length list))
	    (values (pop list) (pop list) (pop list) (pop list) (pop list) (pop list) (pop list))
	    (let ((included-attributes-spec (pop list)))
	      (values included-attributes-spec (pop list) (pop list) (pop list)
		      (loop for i from 0 below (length included-attributes-spec)
			    collect nil using icp-cons)
		      (pop list) (pop list)))))))

(defmacro interned-list--remote-procedure-item-passing-info (interned-list)
  `(getfq (interned-list--plist ,interned-list) 'remote-procedure-item-passing-info))

(defun-simple set-interned-list--remote-procedure-item-passing-info (interned-list value)
  (let* ((plist (interned-list--plist interned-list))
	 (tail (memq 'remote-procedure-item-passing-info plist)))
    (if tail
	(setf (cadr tail) value)
	(setf (interned-list--plist interned-list)
	      (icp-cons 'remote-procedure-item-passing-info (icp-cons value plist))))
    value))

(defsetf interned-list--remote-procedure-item-passing-info
    set-interned-list--remote-procedure-item-passing-info)

(defun-simple get-remote-procedure-item-passing-info-for-interned-list (interned-list)
  (or (interned-list--remote-procedure-item-passing-info interned-list)
      (setf (interned-list--remote-procedure-item-passing-info interned-list)
	    (let ((list (interned-list--list interned-list)))
	      (if (and list
		       (or (and (null (cdr list)) (fixnump (car list)))
			   (consp (car list))))
		  (multiple-value-bind (included-attributes-spec
					 excluded-attributes-spec
					 included-system-attributes-spec
					 include-all-system-attributes-spec
					 include-all-system-attributes-except-spec
					 kind-spec
					 varargs-p)
		      (interned-list--remote-procedure-item-passing-lists interned-list)
		    (make-remote-procedure-item-passing-info-from-specs
		      t ; interned
		      included-attributes-spec
		      excluded-attributes-spec
		      included-system-attributes-spec
		      include-all-system-attributes-spec
		      include-all-system-attributes-except-spec
		      kind-spec
		      varargs-p))
		  (make-interned-remote-procedure-item-passing-info-1
		    (if (and (cdr (interned-list--list interned-list))
			     (=f 6 (length (interned-list--list
					     (cadr (interned-list--list interned-list))))))
			interned-list
			(let* ((list (interned-list--list interned-list))
			       (varargs-p (car list))
			       (list-of-interned-item-infos (cdr list))
			       (new-list-of-interned-item-infos
				 (loop for info in list-of-interned-item-infos
				       for (incl-attr excl-attr
						      incl-sys-attr incl-all-sys-attr
						      kind)
					   = (interned-list--list info)
				       collect (make-remote-procedure-item-info
						 incl-attr excl-attr
						 incl-sys-attr incl-all-sys-attr nil
						 kind)
					 using icp-cons))
			       (new-list (icp-cons varargs-p new-list-of-interned-item-infos)))
			  (prog1 (intern-list new-list)
			    (reclaim-icp-list new-list))))))))))

(defun-simple list-of-nil-p (list)
  (loop for e in list
	when e return nil
	finally (return t)))

(def-icp-message-type define-resumable-remote-procedure-identifier
                      (corresponding-icp-object-index
                       (unsigned-integer remote-procedure-identifier-tag)
		       (interned-list remote-procedure-item-passing-info))
  (store-corresponding-icp-object
    corresponding-icp-object-index
    (make-incoming-remote-procedure-identifier
      remote-procedure-identifier-tag
      (get-remote-procedure-item-passing-info-for-interned-list
	remote-procedure-item-passing-info))))

(def-icp-object-type resumable-remote-procedure-identifier
                     (standard-icp-object-index-space
		       (icp-object-map-for-remote-procedure-identifier
			 resumable-remote-procedure-identifier)
		       reclaim-incoming-remote-procedure-identifier
		       reclaim-remote-procedure-identifier-for-connection-loss)
  (send-icp-define-resumable-remote-procedure-identifier
    corresponding-icp-object-index 
    (remote-procedure-identifier-tag resumable-remote-procedure-identifier)
    (with-bifurcated-version-for-output (new-remote-procedure-identifer-protocol-icp-version)
      (with-remote-procedure-info
	  (resumable-remote-procedure-identifier
	    included-attributes-spec excluded-attributes-spec included-system-attributes-spec
	    include-all-system-attributes-spec include-all-system-attributes-except-spec
	    kind-spec varargs-p)
	(let ((list (if (and (list-of-nil-p included-attributes-spec)
			     (list-of-nil-p excluded-attributes-spec)
			     (list-of-nil-p included-system-attributes-spec)
			     (list-of-nil-p include-all-system-attributes-spec)
			     (list-of-nil-p kind-spec)
			     (not varargs-p))
			(icp-list (length included-attributes-spec))
			(icp-list (copy-list-using-icp-conses included-attributes-spec)
				  (copy-list-using-icp-conses excluded-attributes-spec)
				  (copy-list-using-icp-conses included-system-attributes-spec)
				  (copy-list-using-icp-conses include-all-system-attributes-spec)
				  (copy-list-using-icp-conses kind-spec)
				  (not (null varargs-p))))))
	  (prog1 (intern-list list)
	    (reclaim-icp-list list))))
      (let ((interned-list
	      (remote-procedure-item-passing-info-interned-varargsp+item-info-list
		(remote-procedure-item-passing-info resumable-remote-procedure-identifier))))
	(with-bifurcated-version-for-output
	    (remote-procedure-include-all-system-attributes-except-icp-version)
	  (let* ((list (interned-list--list interned-list))
		 (varargs-p (car list))
		 (list-of-interned-item-infos (cdr list))
		 (old-list-of-interned-item-infos
		   (loop for info in list-of-interned-item-infos
			 for (incl-attr excl-attr
			      incl-sys-attr incl-all-sys-attr incl-all-sys-attr-except
			      kind)
			     = (interned-list--list info)
			 collect (make-remote-procedure-item-info-old
				   incl-attr excl-attr
				   incl-sys-attr incl-all-sys-attr
				   kind)
			 using icp-cons))
		 (old-list (icp-cons varargs-p old-list-of-interned-item-infos)))
	    (prog1 (intern-list old-list)
	      (reclaim-icp-list old-list)))
	  interned-list)))))




(def-icp-message-type resumable-rpc-start (remote-procedure-name
					    (resumable-rpc-argument-list rpc-argument-list))
  (runtime-current-system-case
    (ab
      (receive-start-or-call-remote-procedure
	current-icp-socket
	(remote-procedure-name-symbol remote-procedure-name)
	rpc-argument-list
	nil))
    (gsi
     (gsi-start-or-call-local-function-or-handle-return-values
       'start
       remote-procedure-name nil rpc-argument-list)
     (unless current-resumable-icp-read-task
       (when (eq 'gsi (default-owner-for-gsi-objects))
	 (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi))))))

(def-icp-message-type resumable-rpc-call
                      (remote-procedure-name resumable-remote-procedure-identifier
		       (resumable-rpc-argument-list rpc-argument-list))
  (runtime-current-system-case
    (ab
      (receive-start-or-call-remote-procedure
	current-icp-socket
	(remote-procedure-name-symbol remote-procedure-name)
	rpc-argument-list
	resumable-remote-procedure-identifier))
    (gsi
     (gsi-start-or-call-local-function-or-handle-return-values
       'call
       remote-procedure-name resumable-remote-procedure-identifier
       rpc-argument-list)
     (unless current-resumable-icp-read-task
       (when (eq 'gsi (default-owner-for-gsi-objects))
	 (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi))))))

(def-icp-message-type resumable-rpc-return-values
		      ((unsigned-integer calling-procedure-index)
		       (resumable-rpc-argument-list return-values-list))
  (let ((remote-procedure-identifier
	  (or (lookup-remote-procedure-identifier-from-index calling-procedure-index)
	      (runtime-current-system-case
		(gsi
		  (gsi-connection-error 'rpc-return-values
					gsi-unknown-calling-procedure-index))))))
    (when (and remote-procedure-identifier
	       (eq 'outstanding
		   (remote-procedure-identifier-state remote-procedure-identifier)))
      (setf (remote-procedure-identifier-state remote-procedure-identifier)
	    'returned))
    (runtime-current-system-case
      (ab
	(receive-remote-procedure-values
	  remote-procedure-identifier
	  return-values-list))
      (gsi
       (gsi-start-or-call-local-function-or-handle-return-values
	 'return
	 (gsi-remote-procedure-name-structure
	   (remote-procedure-identifier-caller remote-procedure-identifier))
	 remote-procedure-identifier
	 return-values-list)
       (unless current-resumable-icp-read-task
	 (when (eq 'gsi (default-owner-for-gsi-objects))
	   (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi)))))))

(def-icp-message-type resumable-rpc-error
                      ((symbol error-name)
                       (unsigned-integer error-level)
                       (text-string error-description)
                       (resumable-rpc-argument-list error-argument-list))
  (runtime-current-system-case
    (ab (reclaim-frame-serial-number (icp-pop error-argument-list))
	(reclaim-if-text-string (icp-pop error-argument-list))
	(receive-remote-procedure-error
          current-icp-socket
          error-name
          error-level
          error-description
          error-argument-list)
	(reclaim-transformed-rpc-argument-list error-argument-list nil))
    ((gsi telewindows)
     (declare-ignorable-icp-arguments error-name error-argument-list)
     (gsi-warning 'rpc_error_handler_1
		  gsi-rpc-error-from-g2
		  error-level
		  error-description)
     (unless current-resumable-icp-read-task
       (when (eq 'gsi (default-owner-for-gsi-objects))
	 (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi))))))

(defun-simple check-gsi-error-object (error-object)
  (runtime-current-system-case
    (gsi
      (if (/=f gsi-null-type-tag (gsi-instance-value-type error-object))
	  "The error-object did not have a null type tag"
	  (let* ((error-class (gsi-instance-class error-object)))
	    (cond ((null error-class) nil)
		  ((let ((descr (gsi-get-item-of-attribute-named error-object 'error-description)))
		     (cond ((null descr)
			    "The error-object did not have a error-description attribute")
			   ((/=f gsi-string-type-tag (gsi-instance-value-type descr))
			    "The error-description attribute of the error-object was not a string"))))
		  ((member error-class '(error default-error g2-error g2-rpc-error))
		   nil)
		  (t
		   nil
		   #|
		   (let ((descr (gsi-get-item-of-attribute-named error-object 'foundation-class)))
		     (cond ((null descr)
			    "The third result, error-object, did not have a foundation-class attribute")
			   ((/=f gsi-symbol-type-tag (gsi-instance-value-type descr))
			    "The foundation-class attribute of the error-object was not a symbol")
			   ((not (eq 'error (gsi-instance-value descr)))
			    "The foundation-class attribute of the error-object was not the symbol ERROR")
			   (t
		            nil)))|#
		   )))))
    (t
      error-object
      nil)))

(defun-simple check-gsi-error-argument-list (argument-array)
  (runtime-current-system-case
    (gsi
      (cond ((=f 2 (1-f (gsi-managed-array-length argument-array)))
	     (cond ((/=f gsi-symbol-type-tag
			 (gsi-instance-value-type (gsi-managed-svref argument-array 1)))
		    "The first result, error-name, is not a symbol")
		   ((/=f gsi-string-type-tag
			 (gsi-instance-value-type (gsi-managed-svref argument-array 2)))
		    "The second result, error-message, is not a string")
		   (t nil)))
	    ((=f 1 (1-f (gsi-managed-array-length argument-array)))
	     (check-gsi-error-object (gsi-managed-svref argument-array 1)))
	    (t
	     "The number of results is not equal to 1 or 2")))
    (t
      argument-array
      nil)))

(defun-simple make-gsi-error-argument-list (error-name error-description error-object)
  (runtime-current-system-case
    (gsi
      (if error-object
	  (let ((new-error-argument-list (make-gsi-rpc-argument-list 1)))
	    (setf (gsi-managed-svref new-error-argument-list 1)
		  error-object)
	    new-error-argument-list)
	  (let ((new-error-argument-list (make-gsi-rpc-argument-list 2)))
	    (setf (gsi-managed-svref new-error-argument-list 1)
		  (make-gsi-instance gsi-symbol-type-tag error-name))
	    (setf (gsi-managed-svref new-error-argument-list 2)
		  (make-gsi-instance gsi-string-type-tag
				     (convert-value-to-gsi-value
				       (copy-text-string error-description))))
	    new-error-argument-list)))
    (t error-name error-description error-object
       nil)))

(def-icp-message-type resumable-rpc-error-to-caller
                      ((unsigned-integer remote-caller-index)
                       (unsigned-integer-or-nil signaller?)
                       (symbol error-name)
                       (unsigned-integer error-level)
                       (text-string error-description)
                       (resumable-rpc-argument-list error-argument-list))
  (let ((remote-procedure-identifier
	  (when (<f 0 remote-caller-index)
	    (lookup-remote-procedure-identifier-from-index remote-caller-index))))
    (when (and remote-procedure-identifier
	       (eq 'outstanding
		   (remote-procedure-identifier-state remote-procedure-identifier)))
      (setf (remote-procedure-identifier-state remote-procedure-identifier)
	    'sync-abort))
    (runtime-current-system-case
      (ab (reclaim-frame-serial-number (icp-pop error-argument-list))
	  (reclaim-if-text-string (icp-pop error-argument-list))
	  (receive-remote-procedure-error-for-caller
	    remote-procedure-identifier
	    signaller?
	    (if (and error-argument-list
		     (first error-argument-list)
		     (null (cdr error-argument-list)))
		(first error-argument-list)
		error-name)
	    error-level
	    error-description)
	  (reclaim-transformed-rpc-argument-list error-argument-list nil))
      ((gsi telewindows)
       (declare-ignorable-icp-arguments signaller? error-level)
       (unless (check-gsi-error-argument-list error-argument-list)
	 (setq error-argument-list (make-gsi-error-argument-list
				     error-name error-description nil)))
       (gsi-start-or-call-local-function-or-handle-return-values
	 'error-return
	 (gsi-remote-procedure-name-structure
	   (remote-procedure-identifier-caller remote-procedure-identifier))
	 remote-procedure-identifier
	 error-argument-list)
       (unless current-resumable-icp-read-task
	 (when (eq 'gsi (default-owner-for-gsi-objects))
	   (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi)))))))


(defun-simple send-rpc-start (output-port execution-priority remote-procedure-name-structure
			      argument-list do-not-reclaim-arguments)
  (runtime-current-system-case
    (ab
     (with-bifurcated-version (resumable-icp-version (parent-icp-socket output-port))
       (progn
	 (send-icp-rpc-start-deferring-objects
	   output-port
	   remote-procedure-name-structure
	   argument-list)
	 (reclaim-transformed-rpc-argument-list argument-list do-not-reclaim-arguments))
       (send-or-enqueue-icp-write-task
	 output-port
	 execution-priority
	 #'send-icp-resumable-rpc-start
	 (icp-list remote-procedure-name-structure argument-list)
	 #'reclaim-transformed-rpc-argument-list
	 (icp-list argument-list do-not-reclaim-arguments))))
    (t
      output-port execution-priority remote-procedure-name-structure
      argument-list do-not-reclaim-arguments
      nil)))

(defun-simple send-rpc-call (output-port execution-priority remote-procedure-name-structure
			     remote-procedure-identifier argument-list)
  (setf (remote-procedure-identifier-name-symbol remote-procedure-identifier)
	(remote-procedure-name-symbol remote-procedure-name-structure))
  (runtime-current-system-case
    (ab
     (with-bifurcated-version (resumable-icp-version (parent-icp-socket output-port))
       (progn
	 (send-icp-rpc-call-deferring-objects
	   output-port
	   remote-procedure-name-structure
	   remote-procedure-identifier
	   argument-list)
	 (reclaim-transformed-rpc-argument-list argument-list nil))
       (send-or-enqueue-icp-write-task
	 output-port
	 execution-priority
	 #'send-icp-resumable-rpc-call
	 (icp-list remote-procedure-name-structure
		   remote-procedure-identifier
		   argument-list)
	 #'reclaim-transformed-rpc-argument-list
	 (icp-list argument-list nil))))
    (t
      output-port execution-priority remote-procedure-name-structure
      remote-procedure-identifier argument-list
      nil)))

(defun-simple send-rpc-return-values
              (output-port execution-priority remote-procedure-identifier-tag
	       return-results-list)
  (runtime-current-system-case
    (ab
     (with-bifurcated-version (resumable-icp-version (parent-icp-socket output-port))
       (progn
	 (send-icp-rpc-return-values-deferring-objects
	   output-port
	   remote-procedure-identifier-tag
	   return-results-list)
	 (reclaim-after-rpc-return-values return-results-list))
       (send-or-enqueue-icp-write-task
	 output-port
	 execution-priority
	 #'send-icp-resumable-rpc-return-values
	 (icp-list remote-procedure-identifier-tag
		   return-results-list)
	 #'reclaim-after-rpc-return-values
	 (icp-list return-results-list))))
    (t
      output-port execution-priority remote-procedure-identifier-tag
      return-results-list
      nil)))


;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module GSI-RPC2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Peter Fandel, Nick Caruso, and John Hodgkinson.

;;; This module contains the machinery for remote-procedure execution that is
;;; specific to GSI and involves passing items as arguments and results.
;;; (Module GSI-RPC1 contains the GSI-specific machinery for passing values as
;;; arguments and results.)

;; jh, 3/16/94.  Created this module.




;;;; Forward References

;; Local:

(declare-forward-reference gsi-preflight-item function)




;;;; Variables and Parameters

(defparameter gsi-maximum-number-of-ICP-bytes-to-buffer 4000) ;this number is arbitrary and
							      ;should be tuned based on experience.
(defparameter gsi-collection-range-limit 1000) ;this number is arbitrary and
					       ;should be tuned based on experience.

;; this holds the root item being sent by gsi-send-item.  It's bound in
;; flush-outgoing-item-list (below)
(defvar gsi-current-resumable-item nil)

(defvar list-of-gsi-circular-references nil)
(defvar gsi-current-recursive-depth nil)
(defvar gsi-depth-of-last-transmission nil)

(defmacro sxhash-for-gsi (thing)
  (if (eval-feature :chestnut-trans)
      `(sxhash-symbol ,thing)
      `(sxhash ,thing)))		; note: use sxhashw not necessary if only for symbols

(def-hash-table gsi-circularity-table
    :hash-function-or-macro sxhash-for-gsi)


;; number-of-bytes-in-icp-buffers			SUBSTITUTION MACRO
;;
;; Computes the number of ICP bytes outstanding in ICP buffers.  This formula was
;; obtained from end-icp-message-group, where it's used in the i-am-alive support
;; code to compute the actual number of ICP bytes in the message group. -ncc,
;; 10/25/94
(def-substitution-macro number-of-bytes-in-icp-buffers ()
  (+f number-of-icp-bytes-in-message-group
      (-f number-of-icp-bytes-for-message-series
	  number-of-icp-bytes-to-fill-buffer)
      3))


;;maybe-suspend-and-continue-building-object		FUNCTION
;;
;; Purpose: prevents G2 from blocking when very large or complicated objects
;;         are sent by GSI, by breaking up ICP message groups whenever a
;;         certain threshold number of ICP bytes have accumulated in ICP
;;         buffers.  No bandwidth calculations (ala G2) are done; although
;;         there is in principle no reason why such a scheme could not be
;;         implemented using this function.    This routine has no use
;;         inside G2.
;;
;; Contract:
;;  Pre: must be called from within the context established by
;;       flush-outgoing-item-list, from within GSI.  This function
;;       depends on being called from within the "protocol extent" of a
;;       send-icp-continue-building-resumable-item message, that is, after the
;;       message has been sent and before the write-icp-finish-building-object
;;       protocol message has been sent.  The special "gsi-current-resumable-item"
;;       must be bound to the root item currently being transmitted.

;;  Post: if the number of ICP bytes currently stored in ICP buffers for the
;;        current-icp-socket exceeds a certain threshold
;;        (gsi-maximum-number-of-ICP-bytes-to-buffer) then the current ICP
;;        message group is terminated and a new one is begun.  The operation of
;;        beginning a new message group sets the values of the variables
;;        bound by the writing-icp-message-group form mentioned in
;;        the preconditions above.
;; Notes
;;      
(defun-void maybe-suspend-and-continue-building-object ()
  (when (>=f (number-of-bytes-in-icp-buffers)
	     gsi-maximum-number-of-ICP-bytes-to-buffer)
    ;; send the suspend protocol and end the current message group:

    (write-icp-suspend-building-object 0) ; say zero bandwidth for now.
					; the GSI body for
					; update-object-passing-network-resources
					; ignores this value for now. -ncc, 10/25/94
    (next-icp-message-group)
    (when (/=f (icp-connection-state current-icp-socket) icp-connection-closed)
      (send-icp-continue-building-resumable-object gsi-current-resumable-item))))



(defun-void gsi-prepare-for-recursive-descent ()
  (setf gsi-current-recursive-depth 0)
  (setf gsi-depth-of-last-transmission 0)
  (clear-gsi-circularity-table reusable-circularity-table))

(defun-simple item-in-resumable-circularity-table-p (key)
  (get-gsi-circularity-table key reusable-circularity-table))

(defun-simple put-item-in-resumable-circularity-table (key)
  (setf (get-gsi-circularity-table key reusable-circularity-table) t))




;;;; Functions specific to receiving items sent from G2 to GSI

;; For now, G2 arrays and G2 lists end up as arrays in GSI.  Eventually, we
;; will provide user API functions for list handling.

(defun gsi-make-appropriate-array (gsi-type-tag element-count &optional (gsi-instance? nil))
  (declare (type fixnum gsi-type-tag element-count))
  (let* ((new-array-wrapper (make-gsi-array-wrapper nil nil))
	 (new-array
	   (case gsi-type-tag
	     ((#.gsi-item-or-value-array-type-tag #.gsi-item-or-value-list-type-tag
               #.gsi-quantity-array-type-tag #.gsi-quantity-list-type-tag
	       #.gsi-item-array-type-tag #.gsi-item-list-type-tag
	       #.gsi-value-array-type-tag #.gsi-value-list-type-tag)
	      (setf (gsi-array-type new-array-wrapper)
		    'managed-array)
	      (let ((array (gsi-allocate-managed-array
			     (+f element-count gsi-magic-offset))))
		(setf (gsi-managed-svref array 0) gsi-magic-number)
		array))
	     ((#.gsi-integer-array-type-tag
		 #.gsi-integer-list-type-tag
		 #.gsi-logical-array-type-tag
		 #.gsi-logical-list-type-tag)
	      (setf (gsi-array-type new-array-wrapper)
		    'simple-integer-vector)
	      (gsi-allocate-integer-vector element-count))
	     ((#.gsi-64bit-float-array-type-tag
		 #.gsi-64bit-float-list-type-tag)
	      (setf (gsi-array-type new-array-wrapper)
		    'simple-float-array)
	      (allocate-managed-simple-float-array element-count))
	     ((#.gsi-string-array-type-tag
		 #.gsi-string-list-type-tag)
	      (setf (gsi-array-type new-array-wrapper)
		    'managed-string-array)
	      (gsi-allocate-managed-array element-count))
	     ((#.gsi-symbol-array-type-tag
		 #.gsi-symbol-list-type-tag)
	      (setf (gsi-array-type new-array-wrapper)
		    'managed-array)
	      (gsi-allocate-managed-array element-count)))))
    (setf (gsi-array new-array-wrapper) new-array)
    (gsi-push-onto-appropriate-list new-array-wrapper gsi-instance?)
    new-array))


;; 'gsi-add-to-or-traverse-item-instance' is used to build up the meat of an item.
;; It is called exclusively from 'gsi-build-item-instance'.

(defun-simple gsi-add-to-or-traverse-item-instance (current-subobject
						     attribute-type
						     attribute-qualifier?
						     attribute-name-or-index
						     class-name
						     gsi-type-tag
						     element-count
						     symbolic-attribute-count)
  (declare (ignore attribute-qualifier?))
  (case attribute-type
    (attribute
     (let* ((attribute (make-gsi-attribute attribute-name-or-index attribute-qualifier?))
	    (attribute-item (make-gsi-instance gsi-type-tag nil nil class-name)))
       (setf (gsi-attribute-instance attribute) attribute-item)
       ;; Insert this attribute into the attribute array of the
       ;; item being built, and update the item's attribute count.
       (setf (gsi-managed-svref
	       (gsi-attributes current-subobject)
	       (+f (gsi-attribute-count current-subobject) gsi-magic-offset))
	     attribute)
       (incff (gsi-attribute-count current-subobject))
       ;; If this attribute itself has any attributes, and/or if
       ;; it has an array or list of values, make room for them
       (when (>f symbolic-attribute-count 0)
	 (setf (gsi-attributes attribute-item)
	       (gsi-make-appropriate-array gsi-item-array-type-tag symbolic-attribute-count)))
       (when (>f element-count 0) ; for either a list or an array
	 (setf (gsi-instance-value attribute-item)
	       (gsi-make-appropriate-array gsi-type-tag element-count attribute-item)))
       (setf (gsi-superior-item attribute-item) current-subobject)
       (setf (current-resumable-subobject-being-built?
	       current-receiving-resumable-object)
	     attribute-item)
       attribute-item))
    ((vector-element list-element)
     (let* ((item (make-gsi-instance gsi-type-tag nil nil class-name))
	    (index (gsi-element-count current-subobject)))
       ;; Insert this sub-item or value into the value array of the
       ;; item being built, and update the item's element count.
       (setf (gsi-managed-svref (gsi-instance-value current-subobject)
				(+f index gsi-magic-offset))
	     item)
       (incff (gsi-element-count current-subobject))
       ;; If this sub-item itself has any attributes and/or an array
       ;; or list of values, make room for them
       (when (>f symbolic-attribute-count 0)
	 (setf (gsi-attributes item)
	       (gsi-make-appropriate-array gsi-item-array-type-tag symbolic-attribute-count)))
       (when (>f element-count 0) ; for either a list or an array
	 (setf (gsi-instance-value item)
	       (gsi-make-appropriate-array gsi-type-tag element-count item))) 
       (setf (gsi-superior-item item) current-subobject)
       (setf (current-resumable-subobject-being-built?
	       current-receiving-resumable-object)
	     item)
       item))))

;; The top level item or root is created by 'gsi-build-item-instance'.
;; When not building top-level items, it passes its arguments on to
;; gsi-add-to-or-traverse-item-instance.

(defun-simple gsi-build-item-instance (attribute-type
					attribute-qualifier?
					attribute-name-or-index
					class-name
					gsi-type-tag
					list-or-vector-length
					symbolic-attribute-count)
  (let ((current-subobject?
	  (current-resumable-subobject-being-built?
	    current-receiving-resumable-object)))
    (if current-subobject?
	
       (gsi-add-to-or-traverse-item-instance current-subobject?
					     attribute-type
					     attribute-qualifier?
					     attribute-name-or-index
					     class-name
					     gsi-type-tag
					     list-or-vector-length
					     symbolic-attribute-count)
       
       (let ((toplevel-object (make-gsi-instance gsi-type-tag
						 nil
						 nil
						 class-name)))
	 (when (>f symbolic-attribute-count 0)
	   (setf (gsi-attributes toplevel-object)
		 (gsi-make-appropriate-array gsi-item-array-type-tag
					     symbolic-attribute-count)))
	 (when (>f list-or-vector-length 0)
	   (setf (gsi-instance-value toplevel-object)
		 (gsi-make-appropriate-array gsi-type-tag list-or-vector-length
					     toplevel-object)))
	 (setf (resumable-object-being-built?
		 current-receiving-resumable-object)
	       toplevel-object)
	 (setf (current-resumable-subobject-being-built?
		 current-receiving-resumable-object)
	       toplevel-object)
	 toplevel-object))))


(defun-simple gsi-type-from-g2-element-type (g2-element-type)
  (case g2-element-type
      (integer     gsi-integer-type-tag)
      (long        gsi-long-type-tag)
      (|float|     gsi-64bit-float-type-tag)
      (text        gsi-string-type-tag)
      (truth       gsi-logical-type-tag)
      (symbol      gsi-symbol-type-tag)
      (otherwise   gsi-null-type-tag)))

(defun-simple g2-element-type-from-gsi-type (gsi-type)
  (case gsi-type
      (#.gsi-integer-type-tag       'integer)
      (#.gsi-long-type-tag          'long)
      (#.gsi-64bit-float-type-tag   '|float|)
      (#.gsi-string-type-tag        'text)
      (#.gsi-unsigned-short-vector-type-tag  'text)
      (#.gsi-logical-type-tag       'truth)
      (#.gsi-symbol-type-tag        'symbol)
      (#.gsi-value-type-tag         nil)
      (#.gsi-quantity-type-tag      nil)
      (otherwise
       (gsi-connection-error 'g2-element-type-from-gsi-type gsi-unknown-type-tag))))

(defun-simple gsi-array-type-from-g2-element-type (g2-element-type)
  (case g2-element-type
      (integer     gsi-integer-array-type-tag)
      (|float|     gsi-64bit-float-array-type-tag)
      (text        gsi-string-array-type-tag)
      (truth       gsi-logical-array-type-tag)
      (symbol      gsi-symbol-array-type-tag)
      (otherwise   gsi-value-array-type-tag)))

(defun-simple gsi-list-type-from-g2-element-type (g2-element-type)
  (case g2-element-type
      (integer     gsi-integer-list-type-tag)
      (|float|     gsi-64bit-float-list-type-tag)
      (text        gsi-string-list-type-tag)
      (truth       gsi-logical-list-type-tag)
      (symbol      gsi-symbol-list-type-tag)
      (otherwise   gsi-value-list-type-tag)))

(defun-simple g2-element-type-from-gsi-collection-type (gsi-collection-type)
  (case gsi-collection-type
      ((#.gsi-integer-list-type-tag #.gsi-integer-array-type-tag)
       'integer)
      ((#.gsi-64bit-float-list-type-tag #.gsi-64bit-float-array-type-tag)
       '|float|)
      ((#.gsi-string-list-type-tag #.gsi-string-array-type-tag)
       'text)
      ((#.gsi-logical-list-type-tag #.gsi-logical-array-type-tag)
       'truth)
      ((#.gsi-symbol-list-type-tag #.gsi-symbol-array-type-tag)
       'symbol)
      (otherwise nil)))

(defun-simple gsi-type-from-leaf-type (leaf-type)
  (case leaf-type
    (#.attribute-value-integer-tag             gsi-integer-type-tag)
    (#.attribute-value-long-tag                gsi-long-type-tag)
    (#.attribute-value-float-tag               gsi-64bit-float-type-tag)  
    (#.attribute-value-symbol-tag              gsi-symbol-type-tag) 
    (#.possibly-interned-symbol-interned-tag   gsi-symbol-type-tag) 
    (#.possibly-interned-symbol-uninterned-tag gsi-symbol-type-tag) 
    (#.attribute-value-text-tag                gsi-string-type-tag)
    (#.attribute-value-truth-value-tag         gsi-logical-type-tag)
    (t                                         gsi-null-type-tag)))

(defun-simple simple-value-type-p (type)
  (case type
    ((#.gsi-integer-type-tag
      #.gsi-long-type-tag
	#.gsi-64bit-float-type-tag
	#.gsi-logical-type-tag
	#.gsi-symbol-type-tag
	#.gsi-string-type-tag
	#.gsi-unsigned-short-vector-type-tag)
     t)
    (t
     nil)))
		     
(defun-simple simple-or-null-value-type-p (type)
  (case type
    ((#.gsi-integer-type-tag
      #.gsi-long-type-tag
	#.gsi-64bit-float-type-tag
	#.gsi-logical-type-tag
	#.gsi-symbol-type-tag
	#.gsi-string-type-tag
	#.gsi-unsigned-short-vector-type-tag
	#.gsi-null-type-tag)
     t)
    (t
     nil)))
		     
(defun-simple gsi-add-leaf-to-item-instance
    (current-subobject
      attribute-type
      attribute-qualifier?
      attribute-name-or-index
      leaf-value
      leaf-type)
  (declare (ignore attribute-qualifier?))
  (let ((gsi-type-tag (gsi-type-from-leaf-type leaf-type)))
    
    (case attribute-type
      
      (attribute
       (cond ((eq attribute-name-or-index 'name)
	      (setf (gsi-instance-name current-subobject) leaf-value))
	     ((eq attribute-name-or-index 'current-value)
	      (setf (gsi-instance-value current-subobject) leaf-value)
	      (setf (gsi-instance-value-type current-subobject) gsi-type-tag))
	     (t
	      (let* ((leaf (make-gsi-attribute attribute-name-or-index attribute-qualifier?)))
		(setf (gsi-managed-svref (gsi-attributes current-subobject)
					 (+f
					   (gsi-attribute-count current-subobject)
					   gsi-magic-offset))
		      leaf)
		(incff (gsi-attribute-count current-subobject))
		(cond ((eq leaf-type circular-reference-tag)
		       (setf (gsi-attribute-instance leaf) leaf-value))
		      (t
		       (let ((leaf-instance (make-gsi-instance gsi-type-tag leaf-value)))
			 (setf (gsi-attribute-instance leaf) leaf-instance)
			 (let ((element-count (gsi-element-count leaf-instance)))
			   (when element-count
			     (setf (gsi-element-count leaf-instance) 0))))))))))
      ((vector-element list-element)
       ;; For non-circular cases the values are read in within the loops
       ;; inside the protocol readers. paf!12may94
       (when (eq leaf-type circular-reference-tag)
	 (let ((current-subobject?
		 (current-resumable-subobject-being-built?
		   current-receiving-resumable-object)))
	   (when current-subobject?
	     (let ((index (gsi-element-count current-subobject?)))
	       (setf (gsi-managed-svref
		       (gsi-instance-value current-subobject?)
		       (+f index gsi-magic-offset))
		     leaf-value)
	       (incff (gsi-element-count current-subobject?))
	       (setf (gsi-superior-item leaf-value) current-subobject?)
	       (setf (current-resumable-subobject-being-built?
		       current-receiving-resumable-object)
		     leaf-value)))))))))

(defun-void gsi-receive-add-history-range (timestamps-use-float-array-p
					    values-use-float-array-p
					    number-of-elements)
  (let* ((receiving-item (current-resumable-subobject-being-built?
			   current-receiving-resumable-object))
	 (history-structure (gsi-instance-history receiving-item))
	 (timestamps (gsi-history-timestamps history-structure))
	 (values (gsi-history-values history-structure))
	 (base-time (first (gsi-history-dynamic-info history-structure)))
	 (current-index (gsi-history-counter history-structure)))
    (if (or timestamps-use-float-array-p values-use-float-array-p)
	(cond
	  ((and timestamps-use-float-array-p values-use-float-array-p)
	   (loop for i from current-index repeat number-of-elements
		 do (setf (float-vector-aref timestamps i)
			  (+e (managed-float-value base-time)
			      (the double-float (read-icp-double-float-1))))
		    (setf (gsi-managed-svref values (+f i gsi-magic-offset))
			  (make-gsi-instance gsi-64bit-float-type-tag
					     (read-icp-managed-double-float)))))
	  (timestamps-use-float-array-p
	   (loop for i from current-index repeat number-of-elements
		 do (setf (float-vector-aref timestamps i)
			  (+e (managed-float-value base-time)
			      (the double-float (read-icp-double-float-1))))
		    (multiple-value-bind (history-value value-type)
			(read-icp-attribute-value)
		      (setf (gsi-managed-svref values (+f i gsi-magic-offset))
			    (make-gsi-instance (gsi-type-from-leaf-type value-type)
					       history-value)))))
	  (values-use-float-array-p
	   (loop for i from current-index repeat number-of-elements
		 do (setf (float-vector-aref timestamps i)
			  (if (eq (read-icp-byte) attribute-value-integer-tag)
			      (+e (managed-float-value base-time)
				  (coerce-fixnum-to-gensym-float (read-icp-fixnum)))
			      (+e (managed-float-value base-time)
				  (the double-float (read-icp-double-float-1)))))
		    (setf (gsi-managed-svref values (+f i gsi-magic-offset))
			  (make-gsi-instance gsi-64bit-float-type-tag
					     (read-icp-managed-double-float))))))
	(loop for i from current-index repeat number-of-elements
	      do (setf (float-vector-aref timestamps i)
		       (if (eq (read-icp-byte) attribute-value-integer-tag)
			   (+e (managed-float-value base-time)
			       (coerce-fixnum-to-gensym-float (read-icp-fixnum)))
			   (+e (managed-float-value base-time)
			       (the double-float (read-icp-double-float-1)))))
		 (multiple-value-bind (history-value value-type)
		     (read-icp-attribute-value)
		   (setf (gsi-managed-svref values (+f i gsi-magic-offset))
			 (make-gsi-instance (gsi-type-from-leaf-type value-type)
					    history-value)))))
    (setf (gsi-history-counter history-structure) (+f current-index number-of-elements))))

(defun-void gsi-receive-add-homogeneous-history-range
    (timestamps-use-floats? element-type number-of-elements)
  (let* ((receiving-item (current-resumable-subobject-being-built?
			   current-receiving-resumable-object))
	 (history-structure (gsi-instance-history receiving-item))
	 (timestamps (gsi-history-timestamps history-structure))
	 (values (gsi-history-values history-structure))
	 (base-time (first (gsi-history-dynamic-info history-structure)))
	 (current-index (gsi-history-counter history-structure)))
    (if timestamps-use-floats?
	(case element-type
	  ((integer truth)
	   (loop for i from current-index repeat number-of-elements
		 do
	     (setf (float-vector-aref timestamps i)
		   (+e (managed-float-value base-time)
		       (the double-float (read-icp-double-float-1))))
	     (setf (integer-vector-aref values i)
		   (typed-read-icp-value-to-c-element integer))))
	  (|float|
	   (loop for i from current-index repeat number-of-elements
		 do
	     (setf (float-vector-aref timestamps i)
		   (+e (managed-float-value base-time)
		       (the double-float (read-icp-double-float-1))))
	     (setf (float-vector-aref values i)
		   (typed-read-icp-value-to-c-element 64bit-float))))
	  (text
	   (loop for i from current-index repeat number-of-elements
		 do
	     (setf (float-vector-aref timestamps i)
		   (+e (managed-float-value base-time)
		       (the double-float (read-icp-double-float-1))))
	     (setf (gsi-managed-svref values i)
		   (typed-read-icp-value-to-c-element string))))
	  (symbol
	   (loop for i from current-index repeat number-of-elements
		 do
	     (setf (float-vector-aref timestamps i)
		   (+e (managed-float-value base-time)
		       (the double-float (read-icp-double-float-1))))
	     (setf (gsi-managed-svref values i)
		   (typed-read-icp-value-to-c-element symbol))))
	  (otherwise
	   (gsi-connection-error 'gsi-receive-add-homogeneous-history-range
				 gsi-invalid-history-type)))
	(case element-type
	  ((integer truth)
	   (loop for i from current-index repeat number-of-elements
		 do
	     (setf (float-vector-aref timestamps i)
		   (if (eq (read-icp-byte) attribute-value-integer-tag)
		       (+e (managed-float-value base-time)
			   (coerce-fixnum-to-gensym-float (read-icp-fixnum)))
		       (+e (managed-float-value base-time)
			   (the double-float (read-icp-double-float-1)))))
	     (setf (integer-vector-aref values i)
		   (typed-read-icp-value-to-c-element integer))))
	  (|float|
	   (loop for i from current-index repeat number-of-elements
		 do
	     (setf (float-vector-aref timestamps i)
		   (if (eq (read-icp-byte) attribute-value-integer-tag)
		       (+e (managed-float-value base-time)
			   (coerce-fixnum-to-gensym-float (read-icp-fixnum)))
		       (+e (managed-float-value base-time)
			   (the double-float (read-icp-double-float-1)))))
	     (setf (float-vector-aref values i)
		   (typed-read-icp-value-to-c-element 64bit-float))))
	  (text
	   (loop for i from current-index repeat number-of-elements
		 do
	     (setf (float-vector-aref timestamps i)
		   (if (eq (read-icp-byte) attribute-value-integer-tag)
		       (+e (managed-float-value base-time)
			   (coerce-fixnum-to-gensym-float (read-icp-fixnum)))
		       (+e (managed-float-value base-time)
			   (the double-float (read-icp-double-float-1)))))
	     (setf (gsi-managed-svref values i)
		   (typed-read-icp-value-to-c-element string))))
	  (symbol
	   (loop for i from current-index repeat number-of-elements
		 do
	     (setf (float-vector-aref timestamps i)
		   (if (eq (read-icp-byte) attribute-value-integer-tag)
		       (+e (managed-float-value base-time)
			   (coerce-fixnum-to-gensym-float (read-icp-fixnum)))
		       (+e (managed-float-value base-time)
			   (the double-float (read-icp-double-float-1)))))
	     (setf (gsi-managed-svref values i)
		   (typed-read-icp-value-to-c-element symbol))))
	  (otherwise
	   (gsi-connection-error 'gsi-receive-add-homogeneous-history-range
				 gsi-invalid-history-type))))
    (setf (gsi-history-counter history-structure) (+f current-index number-of-elements))))

(defun-void gsi-add-resumable-circularity (corresponding-index)
  (store-corresponding-icp-object corresponding-index
				  (current-resumable-subobject-being-built?
				    current-receiving-resumable-object))
  (gsi-push corresponding-index
	    (corresponding-indices-of-subobjects
	      current-receiving-resumable-object)))

(defun-void gsi-delayed-invocation (pending-invocation)
  (let ((invocation-type (continuation-waiting-for-rpc-arglist
			   pending-invocation))
	(rpc-argument-list (rpc-arglist-being-built pending-invocation))
	(remote-procedure-name (rpc-name-waiting-for-rpc-arglist
				 pending-invocation))
	(remote-procedure-identifier (rpc-identifier-waiting-for-rpc-arglist
				       pending-invocation)))
    (gsi-start-or-call-local-function-or-handle-return-values
      invocation-type
      remote-procedure-name remote-procedure-identifier rpc-argument-list)
    (when (eq 'gsi (default-owner-for-gsi-objects))
      (gsi-reclaim-contents-and-clear-list
	(receiving-rpc-arglist-reclaim-list pending-invocation)
	'gsi))
    (setf (rpc-arglist-being-built pending-invocation) nil)
    (reclaim-receiving-rpc-arglist-structure pending-invocation)))

(defun-simple gsi-check-if-all-items-are-built (pending-invocation)
  (let ((previous?
	  (previous-resumable-object-in-rpc-arglist?
	    current-receiving-resumable-object))
	(next?
	  (next-resumable-object-in-rpc-arglist?
	    current-receiving-resumable-object)))
    (cond
      ((and previous? next?)
       (setf (next-resumable-object-in-rpc-arglist? previous?) next?)
       (setf (previous-resumable-object-in-rpc-arglist? next?) previous?))
      (previous?
       (setf (next-resumable-object-in-rpc-arglist? previous?) next?))
      (next?
       (setf (previous-resumable-object-in-rpc-arglist? next?) nil))
      (t
       (current-system-case
	   (gsi
	     (loop with arguments = (rpc-arglist-being-built pending-invocation)
		   for i from gsi-magic-offset below (length arguments)
		   for argument-or-resumable = (gsi-managed-svref arguments i)
		   do
	       (when (receiving-resumable-object-p argument-or-resumable)
		 (let ((item (resumable-object-being-built? argument-or-resumable)))
		   (reclaim-single-receiving-resumable-object argument-or-resumable)
		   (setf (gsi-managed-svref arguments i) item))))))
       (gsi-delayed-invocation pending-invocation)))))
	       
(defun copy-portion-of-string-into-string
       (source-string source-start source-end
	destination-string destination-start)
  (if (wide-string-p destination-string)
      (copy-portion-of-string-into-text-string
	source-string source-start source-end
	destination-string destination-start)
      (if (not (wide-string-p source-string))
	  (copy-portion-of-string-into-gensym-string
	    source-string source-start source-end
	    destination-string destination-start)
	  (loop as i from source-start below source-end
		as j from destination-start
		do (setf (charw destination-string j) (char source-string i))))))


(defun-simple simple-text-string-copy-from-attribute-name (base-name class-qualifier?)
  (simple-text-string-copy-from-attribute-name-1
    base-name class-qualifier?
    (using-wide-gsi-api-p)))

(defun-simple simple-text-string-copy-from-attribute-name-1 (base-name class-qualifier? wide-string-p)
  (let* ((base-string (if wide-string-p
			  (symbol-name-text-string base-name)
			  (symbol-name base-name)))
	 (base-length (lengthw base-string)))
    (if class-qualifier?
	(let* ((qualifier-string (if wide-string-p
				     (symbol-name-text-string class-qualifier?)
				     (symbol-name class-qualifier?)))
	       (qualifier-length (lengthw qualifier-string))
	       (actual-length (+f base-length qualifier-length 2))
	       (simple-text-string (if wide-string-p
				       (obtain-simple-text-string actual-length)
				       (obtain-simple-gensym-string actual-length))))
	  (copy-portion-of-string-into-string
	    qualifier-string         ;source
	    0                        ;source from-index
	    qualifier-length         ;source to-index (exclusive)
	    simple-text-string       ;destination
	    0)                       ;destination from-index
	  (copy-portion-of-string-into-string
	    (if wide-string-p
		#w"::"
		"::")		
	    0
	    2
	    simple-text-string
	    qualifier-length)
	  (copy-portion-of-string-into-string
	    base-string
	    0
	    base-length
	    simple-text-string
	    (+f qualifier-length 2))
	  simple-text-string)
	(let ((simple-text-string (if wide-string-p
				      (obtain-simple-text-string base-length)
				      (obtain-simple-gensym-string base-length))))
	  (copy-portion-of-string-into-string
	    base-string
	    0
	    base-length
	    simple-text-string
	    0)
	  simple-text-string))))






;;;; Functions specific to sending items from GSI to G2

(defmacro gsi-write-icp-homogeneous-values (collection-type element-type attribute-spec? item)
  `(let ((element-count (gsi-element-count ,item))
	 (element-type-symbol (g2-element-type-from-gsi-collection-type ,element-type)))
    ,(if (eq collection-type 'array)
	 `(write-icp-add-attribute-value-vector ,attribute-spec?
	                                        (gsi-instance-class ,item)
	                                        nil
                                                (gsi-attribute-count ,item)
						element-type-symbol
						element-count)
	 `(write-icp-add-attribute-value-list ,attribute-spec?
	                                      (gsi-instance-class ,item)
					      nil
					      (gsi-attribute-count ,item)
					      element-type-symbol
					      element-count))
    (loop with remainder-count = element-count
	  as range-count = (minf remainder-count gsi-collection-range-limit)
	  while (pluspf range-count)
	  do
      ,(if (eq collection-type 'array)
	   `(write-icp-byte 14) ;add-homogeneous-value-vector-range
	   `(write-icp-byte 15)) ;add-homogeneous-value-list-range
       (write-icp-fixnum range-count)
       (write-icp-resumable-sequence-element-type element-type-symbol)
       ,@(when (eq collection-type 'array)
	  `((write-icp-fixnum (-f remainder-count 1))))
       (loop with elements = (gsi-instance-value item)
	     ,@(if (eq collection-type 'array)
		   `(for i from (-f remainder-count 1) downto
		     (maxf 0 (-f remainder-count gsi-collection-range-limit)))
		   `(for i from (-f element-count remainder-count) below
		     (+f range-count (-f element-count remainder-count))))
	     do
	 (case element-type-symbol
	    ((integer truth)
	       (write-icp-fixnum (the fixnum (integer-vector-aref elements i))))
	    (|float|
	       (write-icp-double-float-1 (float-vector-aref elements i)))
	    (symbol
	       (write-icp-possibly-interned-symbol
		 (gsi-coerce-symbol-array-element-to-symbol
		   (gsi-managed-svref elements i))
		 nil))
	    (text
	     (converting-gsi-value-to-value
	         (converted-value
		   (gsi-coerce-string-array-element-to-string
		     (gsi-managed-svref elements i)))
	       (write-icp-text-string converted-value)))))
       (setf remainder-count (-f remainder-count range-count))
       (when (pluspf remainder-count)
	 (maybe-suspend-and-continue-building-object)))))

(defmacro gsi-write-icp-heterogeneous-values (collection-type attribute-spec? item)
  `(let ((element-count (gsi-element-count ,item)))
    ,(if (eq collection-type 'array)
	 `(write-icp-add-attribute-value-vector ,attribute-spec?
	                                        (gsi-instance-class ,item)
					        nil
					        (gsi-attribute-count ,item)
					        nil
					        element-count)
	  `(write-icp-add-attribute-value-list ,attribute-spec?
					       (gsi-instance-class ,item)
					       nil
					       (gsi-attribute-count ,item)
					       nil
					       element-count))
    (loop with remainder-count = element-count
	  as range-count = (minf remainder-count gsi-collection-range-limit)
	  while (pluspf range-count)
	  do
      ,(if (eq collection-type 'array)
	   `(write-icp-byte 8)  ;add-value-vector-range
	   `(write-icp-byte 9)) ;add-value-list-range
      (write-icp-fixnum range-count)
      ,@(when (eq collection-type 'array)
	`((write-icp-fixnum (-f remainder-count 1))))
      (loop with elements = (gsi-instance-value ,item)
	    ,@(if (eq collection-type 'array)
		  `(for i from (-f remainder-count 1) downto
		    (maxf 0 (-f remainder-count gsi-collection-range-limit)))
		  `(for i from (-f element-count remainder-count) below
		    (+f range-count (-f element-count remainder-count))))
	    do
	(write-icp-attribute-value (gsi-managed-svref elements (+f i gsi-magic-offset)) nil))
      (setf remainder-count (-f remainder-count range-count))
      (when (pluspf remainder-count)
	(maybe-suspend-and-continue-building-object)))))

(defun-void gsi-send-history-item (attribute-spec? class attribute-count item)
  (let* ((history (gsi-instance-history item))
	 (history-type (gsi-instance-value-type item))
	 (history-length (gsi-history-length history))
	 (timestamps (gsi-history-timestamps history))
	 (values (gsi-history-values history))
	 (g2-element-type (g2-element-type-from-gsi-type history-type)))
    (write-icp-add-attribute-history-object
      attribute-spec?
      class
      nil
      attribute-count
      g2-element-type
      history-length
      (gsi-history-internals history)
      (gsi-history-dynamic-info history) ;basetime always 0.
      t
      (if (eq history-type gsi-64bit-float-type-tag)
	  t nil))
    (cond ((or (eq history-type gsi-value-type-tag)
	       (eq history-type gsi-quantity-type-tag))
	   (loop with remainder-count = history-length
		 as range-count = (minf remainder-count gsi-collection-range-limit)
		 while (pluspf range-count)
		 do
	     (write-icp-byte 18)      ;add-history-range
	     (write-icp-boolean t)    ;timestamps-use-float-array-p
	     (write-icp-boolean nil)  ;values-use-float-array-p
	     (write-icp-fixnum range-count)
	     (loop for timestamp-index from (-f history-length remainder-count) repeat range-count
		   as timestamp double-float = (float-vector-aref timestamps timestamp-index)
		   as value = (gsi-managed-svref
				values
				(+f timestamp-index gsi-magic-offset))
		   do
	       (write-icp-double-float-1 timestamp)
	       (write-icp-attribute-value value nil))
	     (setf remainder-count (-f remainder-count range-count))
	     (when (pluspf remainder-count)
	       (maybe-suspend-and-continue-building-object)
	       (when (=f (icp-connection-state current-icp-socket) icp-connection-closed)
 		 (return nil)))))	  
	  (t
	   (loop with remainder-count = history-length
		 as range-count = (minf remainder-count gsi-collection-range-limit)
		 while (pluspf range-count)
		 do	   
	     (write-icp-byte 19)      ;add-homogeneous-history-range
	     (write-icp-boolean t)    ;timestamps-use-float-array-p
	     (write-icp-resumable-sequence-element-type g2-element-type)
	     (write-icp-fixnum range-count)
	     (case history-type
	       ((#.gsi-integer-type-tag #.gsi-logical-type-tag)
		(loop for i from (-f history-length remainder-count) repeat range-count
		      for timestamp double-float = (float-vector-aref timestamps i)
		      for logical = (the fixnum (integer-vector-aref values i))
		      do
		  (write-icp-double-float-1 timestamp)
		  (write-icp-fixnum logical)))
	       (#.gsi-64bit-float-type-tag
		(loop for i from (-f history-length remainder-count) repeat range-count
		      for timestamp double-float = (float-vector-aref timestamps i)
		      for float double-float = (float-vector-aref values i)
		      do
		  (write-icp-double-float-1 timestamp)
		  (write-icp-double-float-1 float)))
	       (#.gsi-string-type-tag
		(loop for i from (-f history-length remainder-count) repeat range-count
		      for timestamp double-float = (float-vector-aref timestamps i)
		      for string = (gsi-coerce-string-array-element-to-string
				     (gsi-managed-svref values i))
		      do
		  (write-icp-double-float-1 timestamp)
		  (converting-gsi-value-to-value (string)
		    (write-icp-text-string string))))
	       (#.gsi-symbol-type-tag
		(loop for i from (-f history-length remainder-count) repeat range-count
		      for timestamp double-float = (float-vector-aref timestamps i)
		      for symbol = (gsi-coerce-symbol-array-element-to-symbol
				     (gsi-managed-svref values i))
		      do
		  (write-icp-double-float-1 timestamp)
		  (write-icp-possibly-interned-symbol symbol nil)))
	       (t
		(gsi-connection-error 'send_history_item gsi-invalid-history-type)))
	     (setf remainder-count (-f remainder-count range-count))
	     (when (pluspf remainder-count)
	       (maybe-suspend-and-continue-building-object)))))))

(defmacro recursively-apply-to-gsi-item (recursive-function item)
  `(let* ((class? (gsi-instance-class ,item))
	  (type (gsi-instance-value-type ,item))
	  (name? (gsi-instance-name ,item))
	  (value? (gsi-instance-value ,item))
	  (count (gsi-element-count ,item)))
     (unless value? (setq type #.gsi-null-type-tag))
     (when class?
       (incff gsi-current-recursive-depth)
       (when name?
	 (setf (gsi-instance-value reusable-name-instance) name?)
	 (,recursive-function reusable-name-instance
			      item-name-attribute-spec))
       (let ((count (gsi-attribute-count ,item)))
	 (unless (=f count 0)
	   (loop with attributes = (gsi-attributes ,item)
		 for i from gsi-magic-offset below (+f count gsi-magic-offset)
		 as attribute = (gsi-managed-svref attributes i)
		 unless (gsi-attribute-is-transient-p attribute)
		   do (,recursive-function (gsi-attribute-instance attribute)
					   (gsi-attribute-spec attribute)))))
       (when (or (=f type gsi-item-array-type-tag)
		 (=f type gsi-item-or-value-array-type-tag))
	 (unless (=f count 0)
	   (loop for i from gsi-magic-offset below (+f count gsi-magic-offset)
		 as my-item = (gsi-managed-svref value? i)
		 do (setf (resumable-vector-or-list-index array-element-attribute-spec)
			  (-f i gsi-magic-offset))
		    (,recursive-function my-item array-element-attribute-spec))))
       (when (or (=f type gsi-item-list-type-tag)
		 (=f type gsi-item-or-value-list-type-tag))
	 (unless (=f count 0)
	   (loop for i from gsi-magic-offset below (+f count gsi-magic-offset)
		 as my-item = (gsi-managed-svref value? i)
		 do (setf (resumable-vector-or-list-index list-element-attribute-spec)
			  (-f i gsi-magic-offset))
		    (,recursive-function my-item list-element-attribute-spec))))
       (when (and (simple-value-type-p type)
		  value?)
	 (setf (gsi-instance-value-type reusable-value-instance) type)
	 (setf (gsi-instance-value reusable-value-instance) value?)
	 (,recursive-function reusable-value-instance
			      simple-item-value-attribute-spec))
       (when (>f gsi-current-recursive-depth gsi-depth-of-last-transmission)
	 (setf gsi-depth-of-last-transmission gsi-current-recursive-depth))
       (decff gsi-current-recursive-depth))))
  
;; GSI is single threaded.  Once an item is given by the user code for
;; transmission to G2, it cannot be modified in any way until after the
;; transmission is complete and control is passed back to user code.
;; So the recursive descent of `gsi-preflight-item' is guaranteed to
;; encounter sub-items in exactly the same order as the recursive descent
;; `gsi-send-item'.  Every time `gsi-preflight-item' encounters an item
;; which it has already encountered (not necessarily evidence of circularity
;; but nonetheless treated in the same manner), it pushes that item onto a
;; list.  This list is used by `gsi-send-item'.  Note that in this first use
;; of the hash table by `gsi-preflight-item', it is only used to determine
;; if items occur more than once, and no other information is stored within.

(defun-void gsi-preflight-item (item attribute-spec?)
  (cond ((and attribute-spec?
	      (or (eq (resumable-attribute-base-name attribute-spec?) 'name)
		  (eq (resumable-attribute-base-name attribute-spec?) 'current-value)))
	 )
	((item-in-resumable-circularity-table-p item)
	 (gsi-push item list-of-gsi-circular-references))
	(t
	 (put-item-in-resumable-circularity-table item)
	 (recursively-apply-to-gsi-item gsi-preflight-item item))))

(defun-void gsi-send-item (item attribute-spec?)
  (when (=f (icp-connection-state current-icp-socket) icp-connection-closed)
    (return-from gsi-send-item nil))
  (let ((object-index? (item-in-resumable-circularity-table-p item))
	(value-type (gsi-instance-value-type item)))
    (unless (gsi-instance-value item)
      (setq value-type #.gsi-null-type-tag))
    (cond (object-index?
	   (write-icp-add-circular-attribute attribute-spec? object-index?))
	  (t
	   (when (<f gsi-current-recursive-depth gsi-depth-of-last-transmission)
	     (write-icp-ascend-to-parent (-f gsi-depth-of-last-transmission
					     gsi-current-recursive-depth))
	     (setf gsi-depth-of-last-transmission gsi-current-recursive-depth))
	   (if (not (gsi-instance-class item))
	       ;; Simple values
	       (write-icp-add-attribute-value attribute-spec? item nil)
	       ;; Items
	       (case value-type
		 ;; unaries (items with simple values or none at all)
		 ((#.gsi-integer-type-tag #.gsi-logical-type-tag
					  #.gsi-symbol-type-tag #.gsi-string-type-tag
					  #.gsi-64bit-float-type-tag #.gsi-null-type-tag
					  #.gsi-item-type-tag)
		  (let ((history? (gsi-instance-history item)))
		    (if history?
			(gsi-send-history-item attribute-spec?
					       (gsi-instance-class item)
					       (gsi-attribute-count item)
					       item)
			(write-icp-add-attribute-object attribute-spec?
							(gsi-instance-class item)
							nil
							(gsi-attribute-count item)))))
		 ;; arrays
		 ((#.gsi-integer-array-type-tag
		     #.gsi-64bit-float-array-type-tag
		     #.gsi-logical-array-type-tag
		     #.gsi-string-array-type-tag
		     #.gsi-symbol-array-type-tag)
		  (gsi-write-icp-homogeneous-values array value-type attribute-spec? item))
		 ((#.gsi-value-array-type-tag #.gsi-quantity-array-type-tag)
		  (gsi-write-icp-heterogeneous-values array attribute-spec? item))
		 ((#.gsi-item-array-type-tag #.gsi-item-or-value-array-type-tag)
		  (write-icp-add-attribute-object-vector
		    attribute-spec? (gsi-instance-class item) nil
		    (gsi-attribute-count item) (gsi-element-count item)))
		 ;; lists
		 ((#.gsi-integer-list-type-tag
		     #.gsi-64bit-float-list-type-tag
		     #.gsi-logical-list-type-tag
		     #.gsi-string-list-type-tag
		     #.gsi-symbol-list-type-tag)
		  (gsi-write-icp-homogeneous-values list value-type attribute-spec? item))
		 ((#.gsi-value-list-type-tag #.gsi-quantity-list-type-tag)
		  (gsi-write-icp-heterogeneous-values list attribute-spec? item))
		 ((#.gsi-item-list-type-tag #.gsi-item-or-value-list-type-tag)
		  (write-icp-add-attribute-object-list
		    attribute-spec? (gsi-instance-class item) nil
		    (gsi-attribute-count item) (gsi-element-count item)))))
	   
	   (when (eq item (first list-of-gsi-circular-references))
	     (gsi-connection-error 'gsi_send_item gsi-circularity-not-supported)))))
  
  ;; whenever more than a threshold of ICP bytes are buffered, suspend
  ;; building the object, flush the buffers and then continue. -ncc, 10/25/94
  (when (/=f (icp-connection-state current-icp-socket) icp-connection-closed)
    (maybe-suspend-and-continue-building-object)
    (recursively-apply-to-gsi-item gsi-send-item item)
    (when (/=f (icp-connection-state current-icp-socket) icp-connection-closed)
      (recursively-apply-to-gsi-item gsi-send-item item))))

(defun-void flush-outgoing-item-list (icp-socket)
  (when (/=f (icp-connection-state icp-socket) icp-connection-closed)
    (let ((extension-data (gsi-extension-data? icp-socket)))
      (loop as item = (gsi-pop (gsi-outgoing-item-list? extension-data))
	    while item
	    while (/=f (icp-connection-state icp-socket) icp-connection-closed)
	    as gsi-current-resumable-item = item ; a special
	    do (unless (gsi-instance-p item)
		 (gsi-connection-error 'write_item_argument gsi-incompatible-structure))
	       (gsi-prepare-for-recursive-descent)
	       (gsi-preflight-item item nil)
	       (writing-icp-message-group ((icp-output-port icp-socket))
		 (send-icp-continue-building-resumable-object item)
		 (gsi-prepare-for-recursive-descent)
		 (gsi-send-item item nil)
		 (when (/=f (icp-connection-state icp-socket) icp-connection-closed)
		   (write-icp-finish-building-object 0)))
	       (unless (=f (icp-connection-state icp-socket) icp-connection-closed)
		 (reclaim-gensym-list (icp-object-map-for-gsi-instance item))
		 (setf (icp-object-map-for-gsi-instance item) nil))))))


(defun-void establish-new-object-indices-as-required (arguments)
  (loop with actual-size = (or rpc-argument-count-override?
			       (if arguments
				   (-f (gsi-managed-array-length arguments) gsi-magic-offset)
				   0))
	for i from gsi-magic-offset
	      to actual-size
	as value-or-object = (gsi-managed-svref arguments i)
	do
    (when (gsi-instance-class value-or-object) ; Presence of a class name indicates an item.
      (setf (gsi-instance-squirrelled-index value-or-object)
	    (establish-new-object-index-for-gsi-instance
	      value-or-object
	      (icp-output-port current-icp-socket))))))



;; End file with [CR]

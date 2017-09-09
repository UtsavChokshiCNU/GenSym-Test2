;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module Resources (System-Common Code)

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Joseph Devlin

(def-structure (compiled-resource
		 (:constructor
		   make-compiled-resource
		   (compiled-resource-native-p
		    compiled-resource-type
		    compiled-resource-id
		    compiled-resource-language))
		 #+development
		 (:print-function print-compiled-resource))
  (compiled-resource-native-p nil)
  (compiled-resource-type nil)
  (compiled-resource-id nil)
  (compiled-resource-language nil)
  (compiled-resource-load-option nil)
  (compiled-resource-memory-options
    nil :reclaimer reclaim-compiled-resource-slot)
  (compiled-resource-properties
    nil :reclaimer reclaim-compiled-resource-slot))

(defun reclaim-compiled-resource-slot (slot-value)
  (reclaim-slot-value slot-value))

(defun compiled-resource-p-function (thing)
  (compiled-resource-p thing))

(defun reclaim-compiled-resource-function (compiled-resource)
  (reclaim-compiled-resource compiled-resource))

#+obsolete
(defun reclaim-compiled-resource-slot (slot-value)
  (cond
    ((or (symbolp slot-value)	
	 (fixnump slot-value))
     nil)
    ((managed-float-p slot-value)
     (reclaim-managed-float slot-value))
    ((consp slot-value)
     (reclaim-compiled-resource-slot (car-of-cons slot-value))
     (reclaim-compiled-resource-slot (cdr-of-cons slot-value))
     (reclaim-gensym-cons-macro slot-value))
    ((text-string-p slot-value)
     (reclaim-text-string slot-value))
    (t
     (error "unexpected value in compiled resource slot"))))

#+development
(defun print-compiled-resource (compiled-resource stream depth)
  (declare (ignore depth))			; unused
  (printing-random-object (compiled-resource stream)
    (format stream "~a ~a resource id=~s lang=~s"
	    (if (compiled-resource-native-p compiled-resource)
		'Native
		'Non-native)
	    (compiled-resource-type compiled-resource)
	    (compiled-resource-id compiled-resource)
	    (compiled-resource-language compiled-resource))))

(defun encode-resource-as-list (compiled-resource)
  (gensym-list
    (compiled-resource-native-p compiled-resource)
    (compiled-resource-type compiled-resource)
    (compiled-resource-id compiled-resource)
    (compiled-resource-language compiled-resource)
    (compiled-resource-load-option compiled-resource)
    (compiled-resource-memory-options compiled-resource)
    (compiled-resource-properties compiled-resource)))

;;; `decode-resource-from-list' consumes its argument

(defun decode-resource-from-list (list)
  (let ((compiled-resource
	  (make-compiled-resource
	    (gensym-pop list)
	    (gensym-pop list)
	    (gensym-pop list)
	    (gensym-pop list))))
    (setf
      (compiled-resource-load-option compiled-resource)
      (gensym-pop list)
      (compiled-resource-memory-options compiled-resource)
      (gensym-pop list)
      (compiled-resource-properties compiled-resource)
      (gensym-pop list))
    compiled-resource))


;;;; Some macros for accessing parts of a parsed resource.
;;;; jtidwell 5/17/96

(defun safe-and-stupid-getf (plist indicator)
  (if (oddp (length plist))
      nil
      (getf plist indicator)))

(defmacro parsed-resource-native-p (x)
  `(nth 0 ,x))

(defmacro parsed-resource-type (x)
  `(nth 1 ,x))

(defmacro parsed-resource-id (x)
  `(nth 2 ,x))

(defmacro parsed-resource-properties (x)
  `(nth 3 ,x))

(defmacro parsed-resource-property (x key)
  `(safe-and-stupid-getf (nth 3 ,x) ,key))

(defmacro parsed-resource-attribute (x attribute)
  `(safe-and-stupid-getf (safe-and-stupid-getf (nth 3 ,x) 'attributes) ,attribute))

(defmacro parsed-resource-contents (x)   ;; only for containers
  `(safe-and-stupid-getf (nth 3 ,x) 'contents))

#|
For controls:
    (type class id (text x y width height style ex-style attrs))
      With maybe control-style and control-extended-style, as well...
      consider this later.

For containers:
    (type class id (x y style caption ... attrs contents))
      The option statements vary with every kind of top-level resource.
|#





;;;; Resources as Components/Parts




(defun compiled-resource-to-component (compiled-resource)
  (let ((new-structure
	  (allocate-evaluation-structure-inline
	    'is-native
	    (make-evaluation-boolean-value
	      (compiled-resource-native-p compiled-resource))
	    'top-level-type
	    (compiled-resource-type compiled-resource) ; a symbol
	    'id
	    (make-evaluation-value-based-on-type
	      (compiled-resource-id compiled-resource))
	    'language
	    (compiled-resource-language compiled-resource)
	    'load-option
	    (compiled-resource-load-option compiled-resource)))  ; only one?
	(memory-options? (compiled-resource-memory-options compiled-resource)))
    (when memory-options?
      (setf (evaluation-structure-slot new-structure 'memory-options)
	    (with-list-to-evaluation-sequence-mapping (memory-options? option)
	      option)))
    (loop for (name value . nil)
	  on (compiled-resource-properties compiled-resource)
	  by 'cddr
	  do
      (add-resource-property-to-structure
	new-structure (compiled-resource-type compiled-resource)
	name value))
    new-structure))
 	    
(defun add-resource-property-to-structure (structure type name value)
;  (format t "before adding name=~s it looked like:~%~s~%"
;	  name
;	  (twith-output-to-text-string
;	    (write-evaluation-value struct)))
  (declare (ignore type))
  (if (eq name 'text)
      (setf (evaluation-structure-slot structure 'control-text)
	    (make-evaluation-value-based-on-type value))
      (cond
	((or (symbolp value) ; will catch truth-values too!
	     (fixnump value)
	     (text-string-p value))
	 (setf (evaluation-structure-slot structure name)
	       (make-evaluation-value-based-on-type value))
;     (describe (evaluation-structure-value structure))
	 )
	(t
	 (case name    ;; complex properties which could occur in lots of types
	   (style
	    (setf (evaluation-structure-slot structure name)
		  (allocate-evaluation-sequence
		    (copy-list-using-eval-conses value))))
	   (options
	    (setf (evaluation-structure-slot structure name)
		  (allocate-evaluation-sequence
		    (copy-list-using-eval-conses value))))
;;	   (attributes
;;	    (setf
;;	      (evaluation-structure-slot structure name)
;;	      (allocate-evaluation-structure
;;		(let ((attr-copy (copy-list-using-eval-conses value)))
;;		  (loop for (attr-name attr-value . nil) on attr-copy by 'cddr
;;			do
;;		    (if (listp attr-value)
;;			(allocate-evaluation-sequence attr-value))
;;		    attr-copy)))))
   
	   (attributes
	    (setf
	      (evaluation-structure-slot structure name)
	      (let ((attr-structure (allocate-evaluation-structure-inline)))
		(loop for (attr-name attr-value . nil) on value by 'cddr
			do
		  (setf (evaluation-structure-slot attr-structure attr-name)
			(cond ((eq attr-value 'true)
			       evaluation-true-value)
			      ((eq attr-value 'false)
			       evaluation-false-value)
			      ((listp attr-value)
			       (allocate-evaluation-sequence
				 (copy-list-using-eval-conses attr-value)))
			      (t
			       (copy-if-evaluation-value attr-value)))))
		attr-structure)))
		   
	   (contents
	    ;; these will be controls in dialogs, or menu-items in menus,
	    ;; or the entries in an accelerator table.  you get the idea.
	    (setf
	      (evaluation-structure-slot structure name)
	      (with-list-to-evaluation-sequence-mapping (value control)
		(gensym-dstruct-bind ((native-p control-type id properties)
				     control)
		  (let ((control-structure
			  (allocate-evaluation-structure-inline
			    'is-native (if (eq native-p 'win32) t nil)
			    'type control-type
			    'id id)))
		    (loop for (prop-name prop-value . nil) on properties by 'cddr
			  do
		      (add-resource-property-to-structure
			control-structure control-type prop-name prop-value))
		    control-structure)))))))
    )))


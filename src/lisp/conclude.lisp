;;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")


;;;; Module CONCLUDE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Joe Devlin et al


;; Real TO-DO
;; 1 definitions fanout must include re-validating subscriptions
;; 2 change-slot-value should pattern-match & change with this system
;; 3 component-particulars->denotation should
;;   intern things as slot-descriptions or v-a's
;; 4 denotation tail match must say whether conclude tail is
;;   INSIDE the subscribe tail in any way.
;; 5 deleting a representation must delete a subscriptions
;;   in a classes subscription data
;; 6 feed the expiration and collection info in through this mechanism


(defparameter debug-conclude-p nil)



;;;; Pseudo-List (a CPU-data-cache-friendly data structure)


#+unused
(def-structure (pseudo-list
		 (:constructor make-pseudo-list-internal))
  (pseudo-list-vector nil)
  (pseudo-list-start nil)
  (pseudo-list-end nil)
  (pseudo-list-free nil)
  (pseudo-list-entry-size nil))

#+unused
(defun-simple make-pseudo-list (user-entry-size list-size)
  (unless (>f user-entry-size 0)
    (error "pseudo-list-entries must at least 1 in size"))
  (let* ((pseudo-list (make-pseudo-list-internal))
	 (entry-size (1+f user-entry-size))
	 (vector-size (*f entry-size list-size))
	 (vector (allocate-managed-simple-vector vector-size)))
    (setf (pseudo-list-vector pseudo-list) vector)
    (setf (pseudo-list-start pseudo-list) -1)
    (setf (pseudo-list-end pseudo-list) -1)
    (setf (pseudo-list-free pseudo-list) 0)
    (setf (pseudo-list-entry-size pseudo-list) entry-size)
    (loop for i from 0 below vector-size by entry-size
	  do
      (setf (svref vector i) (1+f i)))
    (setf (svref vector (-f vector-size entry-size)) -1)))
	  

#+unused
(defun-simple get-pseudo-list-entry ()
  )




;;;; Attribute Value and Description Caching



(defun-simple double-reallocate-managed-simple-vector (vector)
  (loop with length = (length-of-simple-vector vector)
	with new-vector = (allocate-managed-simple-vector (*f 2 length))
	for i from 0 below length
	do
    (setf (svref new-vector i) (svref vector i))
	finally
	  (reclaim-managed-simple-vector vector)
	  (return new-vector)))

(def-structure (item-access-cache
		 (:constructor
		   make-item-access-cache-internal ()))
  (item-access-cache-slot-description-count 0)
  (item-access-cache-slot-description-vector nil)
  (item-access-cache-attribute-value-count 0)
  (item-access-cache-attribute-value-vector nil))



(defun-simple make-item-access-cache ()
  (let ((item-access-cache (make-item-access-cache-internal))
	(slot-description-vector
	  (allocate-managed-simple-vector
	    (*f slot-description-cache-entry-size 16)))
	(attribute-value-vector
	  (allocate-managed-simple-vector
	    (*f attribute-value-cache-entry-size 16))))
    (setf (item-access-cache-slot-description-vector 
	    item-access-cache)
	  slot-description-vector)
    (setf (item-access-cache-attribute-value-vector
	    item-access-cache)
	  attribute-value-vector)
    item-access-cache))

(defun-simple lookup-cached-slot-description-of-class-description
    (cache attribute-name class-description class-qualifier?)
  (loop with slot-description-vector
	  = (item-access-cache-slot-description-vector cache)
        for i from 0 below (*f slot-description-cache-entry-size
			       (item-access-cache-slot-description-count
				 cache))
	      by slot-description-cache-entry-size
	when (and (eq attribute-name (svref slot-description-vector i))
		  (eq class-description (svref slot-description-vector (+f i 1)))
		  (eq class-qualifier? (svref slot-description-vector (+f i 2))))
	  return (svref slot-description-vector (+f i 3))))

(defun-simple cache-slot-description-of-class-description
    (cache attribute-name class-description class-qualifier?)
  (let ((cache-vector
	  (item-access-cache-slot-description-vector cache))
	(cache-count (item-access-cache-slot-description-count cache)))
    (when (=f (*f slot-description-cache-entry-size cache-count) 
	      (length-of-simple-vector cache-vector))
      (setf cache-vector
	    (double-reallocate-managed-simple-vector cache-vector))
      (setf (item-access-cache-slot-description-vector cache)
	    cache-vector))
    (let ((slot-description?
	    (get-slot-description-of-class-description
	      attribute-name class-description class-qualifier?))
	  (start (*f slot-description-cache-entry-size cache-count)))
      (setf (svref cache-vector start) attribute-name
	    (svref cache-vector (+f start 1)) class-description
	    (svref cache-vector (+f start 2)) class-qualifier?
	    (svref cache-vector (+f start 3)) slot-description?)
      (incff (item-access-cache-slot-description-count cache))
      slot-description?)))

(defmacro get-cached-slot-description-of-class-description
    (cache attribute-name class-description class-qualifier?)
  (avoiding-variable-capture (attribute-name class-description class-qualifier?)
    `(or (lookup-cached-slot-description-of-class-description
	   ,cache ,attribute-name ,class-description ,class-qualifier?)
	 (cache-slot-description-of-class-description
	   ,cache ,attribute-name ,class-description ,class-qualifier?))))

#+development
(defun test-slot-description-caching-speed (cache n cache-p)
  (let ((class-description (class-description 'trend-chart)))
    (if cache-p
	(loop for i from 0 below n
	      do
	  (get-cached-slot-description-of-class-description
	    cache 'trend-chart-plots class-description nil))
	(loop for i from 0 below n
	      do
	  (get-slot-description-of-class-description
	    'trend-chart-plots class-description nil)))))

(defun-simple lookup-cached-attribute-description-evaluation-value
    (cache item attribute-description)
  (loop with slot-description-vector
	  = (item-access-cache-attribute-value-vector cache)
        for i from 0 below (*f attribute-value-cache-entry-size
			       (item-access-cache-attribute-value-count cache))
	      by attribute-value-cache-entry-size
	when (and (eq item (svref slot-description-vector i))
		  (eq attribute-description (svref slot-description-vector (1+f i))))
	  return (svref slot-description-vector (+f i 2))))

(defun-simple cache-attribute-description-evaluation-value
    (cache item attribute-description)
  (let ((cache-vector
	  (item-access-cache-attribute-value-vector cache))
	(cache-count (item-access-cache-attribute-value-count cache)))
    (when (=f (*f attribute-value-cache-entry-size cache-count) 
	      (length-of-simple-vector cache-vector))
      (setf cache-vector
	    (double-reallocate-managed-simple-vector cache-vector))
      (setf (item-access-cache-attribute-value-vector cache)
	    cache-vector))
    (let ((value (get-attribute-description-evaluation-value
		   item attribute-description))
	  (start (*f attribute-value-cache-entry-size cache-count)))
      (setf (svref cache-vector start) item
	    (svref cache-vector (+f start 1)) attribute-description
	    (svref cache-vector (+f start 2)) value)
      (incff (item-access-cache-attribute-value-count cache))
      value)))

(defmacro get-cached-attribute-description-evaluation-value
    (cache item attribute-description)
  (avoiding-variable-capture (cache item attribute-description)
    `(or (lookup-cached-attribute-description-evaluation-value
	   ,cache ,item ,attribute-description)
	 (cache-attribute-description-evaluation-value
	   ,cache ,item ,attribute-description))))


(defun delete-item-access-cache (cache)
  (loop with attribute-value-vector
	  = (item-access-cache-attribute-value-vector cache)
	for i from 0 below (item-access-cache-attribute-value-count cache)
	do
    (reclaim-if-evaluation-value
      (svref attribute-value-vector
	     (+f (*f attribute-value-cache-entry-size i) 2)))
	finally
	  (reclaim-managed-simple-vector attribute-value-vector)
	  (reclaim-managed-simple-vector
	    (item-access-cache-slot-description-vector cache))
	  (reclaim-item-access-cache cache)))


;;;; Denotations



(defmacro fill-simple-vector ((vector-exp start-position-exp) &body forms)
  `(let ((vector ,vector-exp)
	 (start-position ,start-position-exp))
     ,@(loop for form in forms
	     as i from 0 by 1
	     collect
	     `(setf (svref vector (+f start-position ,i)) ,form))))

(eval-when (:compile-toplevel :load-toplevel :execute)
;; Commented out in denotation-next-index-macro 
#+unused
(defparameter all-denotation-types
  '(attribute aliased-attribute element virtual-attribute
    variable-value))



(def-global-property-name denotation-type-code)
(def-global-property-name denotation-type-size)
(def-global-property-name denotation-type-validator)
(def-global-property-name denotation-type-defined-check)
(def-global-property-name denotation-type-wildcard-arg-index?)
)

(defvar denotation-size-vector
  (with-permanent-allocation (make-array maximum-denotation-types)))

(defun-for-macro get-denotation-wildcard-arg-index? (annotated-args)
  (loop with wildcard-arg-index? = nil
	for arg in annotated-args
	as i from 0 by 1
	when (and (consp arg)
		  (eq (cadr arg) :wildcard))
	  do
	    (cond
	      (wildcard-arg-index?
	       (error "you only gets one wildcard, pal"))
	      (t
	       (setf wildcard-arg-index? i)))
	return i))

(defvar current-conclude-innermost-attribute-description nil)

(defmacro def-denotation-type ((name &key code more-specific-types)
			       annotated-args &body pseudo-functions)
  (declare (ignore more-specific-types))
  (let* ((arglist (loop for arg in annotated-args
			collect (if (consp arg) (car arg) arg)))
	 (wildcard-arg-index?
	   (get-denotation-wildcard-arg-index? annotated-args))
	 (validator (assq 'validator pseudo-functions))
	 (validator-arglist (cadr validator))
	 (name-for-validator (build-ab-symbol name 'denotation-validator))
	 (defined-check (assq 'defined-check pseudo-functions))
	 (defined-check-arglist (cadr defined-check))
	 (name-for-defined-check (build-ab-symbol name 'denotation-defined-check)))
    (unless (= (length validator-arglist) 5)
      (error "validator must take five arguments"))
    (unless (= (length defined-check-arglist) 3)
      (error "defined-check must take three arguments"))
    `(progn
       (eval-when (:compile-toplevel :load-toplevel :execute)
	 (setf (denotation-type-code ',name) ,code)
	 (setf (denotation-type-size ',name)
	       ,(+ denotation-element-overhead-slot-count
		   (length arglist))))
       (setf (svref denotation-size-vector ,code)
	      ,(+ denotation-element-overhead-slot-count
		   (length arglist)))
       ,@(when wildcard-arg-index?
	   `((setf (denotation-type-wildcard-arg-index? ',name)
		   (+f denotation-element-overhead-slot-count
		       ,wildcard-arg-index?))))
       (setf (denotation-type-validator ',name)
	     ',name-for-validator)
       (defun-simple ,name-for-validator ,validator-arglist
	 ,@(multiple-value-bind (declarations body doc)
	       (parse-body-declarations (cddr validator))
	     (declare (ignore doc))
	    `(,@declarations
		(let (,@(loop for arg in arglist
			      as i from 2 by 1
			      collect
			      `(,arg (svref ,(caddr validator-arglist)
					    (+f ,i ,(cadddr validator-arglist))))))
		  ,@body))))
       (setf (denotation-type-defined-check ',name)
	     ',name-for-defined-check)
       (defun ,name-for-defined-check ,defined-check-arglist
	 ,@(multiple-value-bind (declarations body doc)
	       (parse-body-declarations (cddr defined-check))
	     (declare (ignore doc))
	    `(,@declarations
		(let (,@(loop for arg in arglist
			      as i from 2 by 1
			      collect
			      `(,arg (svref ,(cadr defined-check-arglist)
					    (+f ,i ,(caddr defined-check-arglist))))))
		  ,@body))))
       )))

(defmacro denotation-code-case (selector &body clauses)
  `(fixnum-case ,selector
    ,@(loop for (type-name . actions) in clauses
	    collect
	    `(,(denotation-type-code type-name)
	       ,@actions))))


(defvar the-denotation-conversion-buffer nil)


(defun-simple denotation-sequence->denotation (sequence)
  (unless the-denotation-conversion-buffer
    (setf the-denotation-conversion-buffer
	  (allocate-managed-simple-vector
	    (*f 6 maximum-denotation-sequence-elements))))
  (loop with length = 0
	for structure being each evaluation-sequence-element of sequence
	as i from 0 by 1
	as type? = (and (evaluation-structure-p structure)
			(evaluation-structure-slot structure 'type))
	do
    (cond
      (type? 
       (let ((new-length-or-error
	       (fill-denotation-from-denotation-element structure length)))
	 (cond ((fixnump new-length-or-error)
		(setf length new-length-or-error))
	       (t
		(return-from denotation-sequence->denotation
		  new-length-or-error)))))
      ((evaluation-structure-p structure)
       (return-from denotation-sequence->denotation
	 (access-error
	   'no-type-in-denotation-sequence-element-structure
	   'element-structure (tformat-text-string "~NV" structure))))
      (t
       (return-from denotation-sequence->denotation
	 (access-error
	   'non-structure-indenotation-sequence-element
	   'sequence (tformat-text-string "~NV" sequence)
	   'index i))))
	finally
	  (return
	    (let ((result (allocate-managed-simple-vector length)))
	      (loop for i from 0 below length
		    do
		(setf (svref result i) (svref the-denotation-conversion-buffer i)))
	      result))))

(defun-simple fill-denotation-from-denotation-element (structure length)
  (let ((type (evaluation-structure-slot structure 'type)))
    (case type
      ((sequence-element element)
       (let ((index (evaluation-structure-slot structure 'index)))
	 (cond
	   (index
	    (fill-simple-vector
	      (the-denotation-conversion-buffer length)
	      (denotation-type-code 'element)
	      'element
	      index)
	    (+f length (denotation-type-size 'element)))
	   (t
	    (access-error
	      'no-index-for-element-denotation-element
	      'denotation-element
	      (tformat-text-string "~NA" structure))))))
      ((structure-attribute attribute)
       (let ((name (evaluation-structure-slot structure 'name))
	     (class-qualifier?
	       (and (eq type 'attribute)
		    (evaluation-structure-slot structure 'class-qualifier))))
	 (cond (name
		(fill-simple-vector
		  (the-denotation-conversion-buffer length)
		  (denotation-type-code 'attribute)
		  'attribute 
		  name
		  class-qualifier?)
		(+f length (denotation-type-size 'attribute)))
	       (t
		(access-error
		  'no-name-for-attribute-denotation-element
		  'denotation-element
		  (tformat-text-string "~NA" structure))))))
       #+development
       (structure-attributes
	(cerror "go on" "NYI")
	length)
       #+development
       (sequence-elements
	(cerror "go on" "NYI")
	length)
       (variable-value
	(fill-simple-vector
	  (the-denotation-conversion-buffer length)
	  (denotation-type-code 'variable-value)
	  'variable-value)
	(+f length (denotation-type-size 'variable-value)))
       (item-color-pattern-change
	(fill-simple-vector (the-denotation-conversion-buffer length)
			    (denotation-type-code 'item-color-pattern-change)
			    'item-color-pattern-change)
	(+f length (denotation-type-size 'item-color-pattern-change)))
       (custom-event
	(fill-simple-vector (the-denotation-conversion-buffer length)
			    (denotation-type-code 'custom-event)
			    'custom-event
			    (evaluation-structure-slot structure
						       'custom-event-name))
	(+f length (denotation-type-size 'custom-event)))
       (add-item-to-workspace
	(fill-simple-vector (the-denotation-conversion-buffer length)
			    (denotation-type-code 'add-item-to-workspace)
			    'add-item-to-workspace)
	(+f length (denotation-type-size 'add-item-to-workspace)))
       (remove-item-from-workspace
	(fill-simple-vector (the-denotation-conversion-buffer length)
			    (denotation-type-code 'remove-item-from-workspace)
			    'remove-item-from-workspace)
	(+f length (denotation-type-size 'remove-item-from-workspace)))
       (item-event
	(fill-simple-vector (the-denotation-conversion-buffer length)
			    (denotation-type-code 'item-event)
			    'item-event
			    (evaluation-structure-slot structure
						       'item-event-name))
	(+f length (denotation-type-size 'item-event)))
       (otherwise
	(access-error
	  'unknown-denotation-element-type
	  'type type)))))

(defun sub-denotation (denotation start &optional end?)
  (let* ((end (or end? (length-of-simple-vector denotation)))
	 (sub-denotation
	   (allocate-managed-simple-vector (-f end start))))
    (loop for i from start below end
	  as sub-i from 0
	  do
      (setf (svref sub-denotation sub-i) (svref denotation i)))
    sub-denotation))

(defmacro reclaim-denotation (d)
  `(reclaim-managed-simple-vector ,d))

(defun copy-denotation (d)
  (let* ((len (length-of-simple-vector d))
	 (new-d (allocate-managed-simple-vector len)))
    (loop for i from 0 below len
	  do (setf (svref new-d i) (svref d i)))
    new-d))

(defun-void reclaim-denotation-function (d)
  (reclaim-denotation d))

;;; `denotation-next-index' ...

(defmacro denotation-next-index-macro (denotation index)
  (avoiding-variable-capture (index)
    `(+f ,index
	 (svref denotation-size-vector (svref ,denotation ,index)))))

;           (declare (type fixnum increment))
;	   (fixnum-case (svref ,denotation ,index)
;	     ,@(loop for denotation-type in all-denotation-types
;		     collect
;		     `(,(denotation-type-code denotation-type)
;			(setf increment ,(denotation-type-size denotation-type)))))
;	   increment))))

(defun-simple denotation-next-index (denotation index)
  (denotation-next-index-macro denotation index))

;;; `denotation-previous-index' is not particularly fast.  Yet

#+unused
(defun-simple denotation-previous-index (denotation index)
  (loop with vector-length = (length-of-simple-vector denotation)
	with prev-index = nil
	for i = 0 then (denotation-next-index-macro denotation i)
	while (<f i vector-length)
	do
    (when (=f i index)
      (return prev-index))
    (setf prev-index index)
	finally
	  (error "denotation index out of range")))
	     

(defmacro denotation-type-name (denotation index)
  `(svref ,denotation (1+f ,index)))

;;; `denotation-length'

#+unused
(defun-simple denotation-length (denotation)
  (loop with vector-length = (length-of-simple-vector denotation)
	with length = 0
	for i = 0 then (denotation-next-index-macro denotation i)
	while (<f i vector-length)
	do
    (incff length)
	finally
	  (return length)))
	

;;; `denotation-end-index'

(defun-simple denotation-end-index (denotation)
  (loop with vector-length = (length-of-simple-vector denotation)
	with result = 0
	for i = 0 then (denotation-next-index-macro denotation i)
	while (<f i vector-length)
	do
    (setf result i)
	finally
	  (return result)))

#+development
(defun-void pprint-denotation (denotation)
  (loop with end-index = (denotation-end-index denotation)
	for index = 0 then next-index
	as next-index = (denotation-next-index denotation 0)
		      then (denotation-next-index denotation index)
	do
    (format t "{~a: " (svref denotation (1+f index)))
    (loop for i from (+f index 2) below next-index
	  do
      (format t "~s " (svref denotation i)))
    (format t "}" )
    (when (=f index end-index)
      (terpri)
      (return))))



;;;; Heuristic Search for Type-Specification Info

(defun-simple item-type-specification? (type-specification)
  (cond
    ((symbolic-type-specification-subtype-p type-specification 'item-or-datum)
     '(class item))
    ((class-type-specification-p type-specification)
     type-specification)
    (t
     nil)))

(defun-simple get-class-type-specification-if-unique
    (type-specification)
  (or (item-type-specification? type-specification)
      (and (union-type-specification-p type-specification)
	   ;; this is a hack, and I should be shot
	   (loop with result = nil
		 for disjunct in (cdr type-specification)
		 as item-type-spec? = (item-type-specification? disjunct)
		 when item-type-spec?
		   do
		     (cond (result
			    (return nil)) ; not unique
			   (t
			    (setf result disjunct)))
		 finally
		   (return result)))))

(defun-simple get-structure-type-specification-if-unique (type-specification)
  (if (structure-type-specification-p type-specification)
      type-specification
      (and (union-type-specification-p type-specification)
	   ;; this is a hack, and I should be shot
	   (loop with result = nil
		 for disjunct in (cdr type-specification)
		 when (structure-type-specification-p disjunct)
		   do
		     (cond (result
			    (return nil))
			   (t
			    (setf result disjunct)))
		 finally
		   (return result)))))

(defun-simple get-sequence-type-specification-if-unique (type-specification)
  (if (sequence-type-specification-p type-specification)
      type-specification
      (and (union-type-specification-p type-specification)
	   ;; this is a hack, and I should be shot
	   (loop with result = nil
		 for disjunct in (cdr type-specification)
		 when (sequence-type-specification-p disjunct)
		   do
		     (cond (result
			    (return nil))
			   (t
			    (setf result disjunct)))
		 finally
		   (return result)))))

(def-denotation-type (attribute :code 1)
    ((attribute-name :wildcard) class-qualifier?)
  (validator (cache root denotation index write-p)
    (cond
      ((framep root)
       (let* ((item root)
	      (class-description (class-description-slot item))
	      (slot-description?
		(let ((sd (get-cached-slot-description-of-class-description
			    cache attribute-name class-description class-qualifier?)))
		  (when debug-conclude-p
		    (format t "cd=~s aname=~s cq=~s sd=~s~%"
			    class-description attribute-name
			    class-qualifier? sd))
		  sd))
	      (unaliased-name?
		(if (or (null slot-description?)
			(system-defined-slot-description-p slot-description?))
		    (get-slot-name-for-alias-if-any attribute-name item)))
	      (user-defined-slot-p
		(and slot-description?
		     (user-defined-slot-description-p slot-description?)))
	      (virtual-attribute? nil))
	 (cond
	   (user-defined-slot-p
	    (let* ((slot-value?
		     (get-user-slot-description-value root slot-description?)))
	      (setf current-conclude-innermost-attribute-description
		    slot-description?)
	      (cond
		((or (not (framep slot-value?))
		     (serve-item-p slot-value?))
		 slot-value?)
		(t
		 (make-inactive-item-in-attribute-error-message
		   slot-description? class-description item slot-value?)))))
	   (t
	    (when unaliased-name?
	      (setq slot-description?
		    (get-cached-slot-description-of-class-description
		      cache unaliased-name? class-description nil)))
	    (let* ((evaluator-info?
		    (and slot-description?
			 (get-slot-description-evaluator-info
			   slot-description?)))
		   (valid-p
		     (and
		       evaluator-info?
		       (if write-p
			   (evaluator-slot-info-category-setter evaluator-info?)
			   (evaluator-slot-info-category-getter evaluator-info?)))))
	      (cond
		(valid-p
		 (setf current-conclude-innermost-attribute-description
		       slot-description?)
		 (get-cached-attribute-description-evaluation-value
		   cache item slot-description?))
		((and (setq virtual-attribute?
			    (or (and evaluator-info?
				     (evaluator-slot-info-virtual-attribute
				       evaluator-info?))
				(virtual-attribute attribute-name)))
		      (type-specification-type-p
			item
			(virtual-attribute-arg-type virtual-attribute?)))
		 (setf current-conclude-innermost-attribute-description
		       virtual-attribute?)
		 (get-cached-attribute-description-evaluation-value
		   cache item virtual-attribute?))
		(t
		 (and write-p
		      (access-error
			'undefined-attribute
			'attribute-name
			(tformat-text-string
			  "~NQ" attribute-name class-qualifier?))))
		))))))
      ((evaluation-structure-p root)
       (let ((next-root? (evaluation-structure-slot root attribute-name)))
	 (cond
	   (next-root?
	    next-root?)
	   (t
	    (access-error
	      'attribute-does-not-exist-in-structure
	      'structure (tformat-text-string "~NV" root)
	      'attribute-name attribute-name)))))
      (t
       (make-attribute-access-on-non-frame-error
	 root attribute-name class-qualifier?))))
  (defined-check (root denotation index)
    (let ((item-type-specification-or-error
	    (get-class-type-specification-if-unique root))
	  (structure-type-specification-or-error
	    (get-structure-type-specification-if-unique root)))
      (cond
	((access-error-p item-type-specification-or-error)
	 item-type-specification-or-error)
	((access-error-p structure-type-specification-or-error)
	 structure-type-specification-or-error)
	((and item-type-specification-or-error
	      structure-type-specification-or-error)
	 (access-error
	   'ambiguous-attribute-definition
	   'attribute-name (tformat-text-string
			     "~NQ" attribute-name class-qualifier?)))
	(item-type-specification-or-error
	 (let* ((class-description
		  (class-description
		    (type-specification-class
		      item-type-specification-or-error)))
		(attribute-description?
		  (get-attribute-description-from-class-description
		    class-description attribute-name class-qualifier?)))
	   (cond ((null attribute-description?)
		  (cond ((eq attribute-name '*)
			 (values '(or item-or-datum (no-item))
				 nil))
			(t
			 (access-error
			   'undefined-attribute
			   'attribute-name (tformat-text-string
					     "~NQ" attribute-name class-qualifier?)))))
		 ((virtual-attribute-p attribute-description?)
		  ;; eventually mark virtual attributes
		  ;; as invertible or not
		  (values (virtual-attribute-value-type attribute-description?)
			 nil))
		 ((user-defined-slot-description-p attribute-description?)
		  (values
		    (slot-type-specification attribute-description?)
		    t))
		 (t
		  (let* ((evaluator-info?
			  (and attribute-description?
			       (get-slot-description-evaluator-info
				 attribute-description?)))
			 (type-specification?
			   (and evaluator-info?
				(evaluator-slot-info-category evaluator-info?))))
		    (cond
		      (type-specification?
		       (values type-specification? nil))
		      (t
		       (access-error
			 'unexported-attribute
			 'attribute-name
			 (tformat-text-string
			   "~NQ" attribute-name class-qualifier?)))))))))
	(structure-type-specification-or-error
	 (let ((type-specification structure-type-specification-or-error))
	   (cond
	     ((eq attribute-name '*)
	      (values '(or item-or-datum (no-item))
		      nil))
	     ((structure-type-specification-has-details? type-specification)
	      (let ((slot-list
		      (structure-type-specification-slot-list type-specification)))
		(loop for (name slot-type-spec) in slot-list
		      when (eq name attribute-name)
			return
			(values slot-type-spec
				(not
				  (type-specifications-could-intersect-in-kb-p
				    slot-type-spec '(class item))))
		      finally
			(return
			  (values '(or item-or-datum (no-item))
				  nil))))) ; could be an item
	     (t
	       (values '(or item-or-datum (no-item))
		       nil)))))
	(t
	 (access-error
	   'attribute-of-non-item
	   'attribute-name (tformat-text-string
			     "~NQ" attribute-name class-qualifier?))))))
  (getter ( )
	  )
  (setter ( )
	 ))

(def-denotation-type (aliased-attribute :code 2)
    (aliased-name attribute-name class-qualifier?)
  (validator (cache root denotation index write-p)
    (declare (ignore cache root write-p))
    aliased-name attribute-name class-qualifier?
    nil)
  (defined-check (root denotation index)
    (declare (ignore root))
    aliased-name attribute-name class-qualifier?
    nil)
  (getter ()
    )
  (setter ()
    ))

(def-denotation-type (element :code 3)
    ((element-index :wildcard))
  (validator (cache root denotation index write-p)
    (declare (ignore cache write-p))
    (cond
      ((not (fixnump element-index))
       (access-error
	 'non-integer-index
	 'value (tformat-text-string "~NV" element-index)))
      ((framep root)
       (cond
	 ((g2-array-p root)
	  (cond ((g2-array-index-ok-p root element-index)
		 (let ((item-or-value (g2-array-aref root element-index)))
		   (cond ((null item-or-value)
			  (access-error
			    'element-does-not-exist
			    'array (tformat-text-string "~NF" root)
			    'index element-index))
		         ((or (framep item-or-value)
			      (aggregate-evaluation-value-p item-or-value))
			  (copy-if-evaluation-value item-or-value))
			 (t
			  nil))))
		(t
		 (access-error
		   'index-out-of-range
		   'index element-index))))
	 ((g2-list-p root)
	  (cond
	    ((g2-list-empty-p root)
	     (access-error
	       'list-is-empty
	       'list (tformat-text-string "~NF" root)))
	    (t
	     (let ((element?
		     (nth-g2-list-item-or-evaluation-value
		       element-index root nil)))
	       (cond ((or (framep element?)
			  (aggregate-evaluation-value-p element?))
		      (copy-if-evaluation-value element?))
		     (t
		      (access-error
			'element-of-item-not-array-or-list
			'item (tformat-text-string "~NF" root))))))))))
      ((evaluation-sequence-p root)
       (let ((length (evaluation-sequence-length root)))
	 (cond ((<f -1 element-index length)
		;; Can do fast access because sequence length validates the seq.
		(let ((element (evaluation-sequence-ref root element-index)))
		  (cond ((evaluation-item-reference-p element)
			 (evaluation-item-reference-referenced-item element))
			((or (framep element)
			     (aggregate-evaluation-value-p element))
			 (copy-if-evaluation-value element))
			(t
			 nil))))
	       (t
		(access-error
		  'index-out-of-range
		  'sequence (tformat-text-string "~NA" root))))))
      (t
       (access-error
	 'element-of-non-array-list-or-sequence
	 'item-or-value (tformat "~NA" root)))))
  (defined-check (root denotation index)
    (let ((item-type-specification-or-error
	    (get-class-type-specification-if-unique root))
	  (sequence-type-specification-or-error
	    (get-sequence-type-specification-if-unique root)))
      (cond
	((and (null item-type-specification-or-error)
	      (null sequence-type-specification-or-error))
	 (access-error
	   'denotation-of-non-list-array-or-sequence
	   'item-or-value (tformat-text-string "~NA" root)))
	(item-type-specification-or-error
	 (let ((class-description
		 (class-description
		   (type-specification-class
		     item-type-specification-or-error))))
	   (cond
	     ;; It seems to me that lists are invertible roles
	     ;; in practice, but arrays aren't.  Not that the
	     ;; the rule compiler knows shit from shinola on
	     ;; this point.
	     ((class-description-of-class-p class-description 'g2-array)
	      (values nil nil))
	     ((class-description-of-class-p class-description 'g2-list)
	      (let ((list-element-type (class-description-list-type root)))
		(cond
		  ((type-specifications-could-intersect-in-kb-p
		     list-element-type '(class item))
		   (values list-element-type t))
		  (t
		   (values nil nil)))))
	     (t
	      (access-error
		'denotation-of-non-list-array-or-sequence
		'item-or-value (tformat-text-string "~NA" root))))))
	(sequence-type-specification-or-error
	 (let ((element-type?
		 (sequence-type-specification-element-type
		   sequence-type-specification-or-error)))
	   (when (fixnump element-index)
	     ;; could be pre-check bounds here if defined in type
	     nil)
	   (cond (element-type?
		  (values element-type? t))
		 (t
		  (values nil nil))))))))
  (getter ()
	  )
  (setter ()
	  ))

;;; `class-description-list-type' is a hack.

(defun-simple class-description-list-type (class-description)
  (let ((slot-description
	  (get-slot-description-of-class-description
	    'list-type class-description)))
    (slot-init-form slot-description)))
    

(def-denotation-type (virtual-attribute :code 4)
    ((virtual-attribute-name :wildcard))
  (validator (cache root denotation index write-p)
    (declare (ignore write-p))
    (let ((virtual-attribute? (virtual-attribute virtual-attribute-name)))
      (cond ((null virtual-attribute?)
	     (make-no-such-virtual-attribute-error-message
	       root virtual-attribute-name))
	    ((type-specification-type-p
	       root
	       (virtual-attribute-arg-type virtual-attribute?))
	     (setf current-conclude-innermost-attribute-description
		   virtual-attribute?)
	     (get-cached-attribute-description-evaluation-value
	       cache root virtual-attribute?))
	    (t
	     (make-no-such-virtual-attribute-error-message
	       root virtual-attribute-name)))))
  (defined-check (root denotation index)
    (let ((virtual-attribute? (virtual-attribute virtual-attribute-name)))
      (cond ((null virtual-attribute?)
	     (make-no-such-virtual-attribute-error-message
	       root virtual-attribute-name))
	    (t
	     (values
	       (virtual-attribute-arg-type virtual-attribute?)
	       nil))))) ; may someday v-a's will have inverses
  (getter ()
	  )
  (setter ()
	  ))

(def-denotation-type (variable-value :code 5)
    ()
  (validator (cache root denotation index write-p)
    (declare (ignore cache denotation index write-p))
    (cond ((frame-of-class-p root 'variable-or-parameter)
	   (let ((*current-computation-frame* root)
		 (current-computation-flags current-computation-flags))
	     (setf (force-new-request-for-value) nil)
	     (setf (dont-compute-new-variable-values) t)
	     (get-current-evaluation-value root nil)))
	  (t
	   (make-conclude-into-non-v-or-p-error-message root))))
  (defined-check (root denotation index)
    (declare (ignore denotation index))
    (let ((item-type-specification-or-error?
	    (get-class-type-specification-if-unique root)))
      (cond
	((access-error-p item-type-specification-or-error?)
	 (values item-type-specification-or-error? nil))
	(t
	 (let ((class-description
		 (class-description
		   (type-specification-class item-type-specification-or-error?))))
	   (cond
	     ((class-description-of-class-p class-description 'variable-or-parameter)
	      (values nil t))
	     (t
	      (values
		(access-error
		  'variable-value-of-non-variable-or-parameter
		  'class (class-name-of-class-description class-description))
		nil))))))))
  (getter ()
    )
  (setter ()
    ))

;; May want to pass in region? For now ignore.
(def-denotation-type (item-color-pattern-change :code 6)
    ()
  (validator (cache root denotation index write-p)
    (declare (ignore cache denotation index write-p))
    (and (framep root)
	 (entity-p root)
	 (icon-color-pattern root)))
  (defined-check (root denotation index)
    (declare (ignore root denotation index))
    (values nil t)))

;; Note the silly no-ops references to event-name are to get around a bug in
;; def-denotation-type in that there is no way to declare anything about the
;; args to the type itself, but the args are needed to size the denotation
;; vector correctly
(def-denotation-type (custom-event :code 7)
    (event-name)
  (validator (cache root denotation index write-p)
    (declare (ignore cache write-p))
    event-name
    (and (framep root)
	 (entity-p root)))		;See comment in dialog #1 of bug HQ-4707336
  (defined-check (root denotation index)
      (declare (ignore root))
    event-name
    (values nil t)))

(def-denotation-type (add-item-to-workspace :code 8)
    ()
  (validator (cache root denotation index write-p)
    (declare (ignore cache denotation index write-p))
    (workspace-p root))			;may need hack as above
  (defined-check (root denotation index)
      (declare (ignore root denotation index))
    (values nil t)))

(def-denotation-type (remove-item-from-workspace :code 9)
    ()
  (validator (cache root denotation index write-p)
    (declare (ignore cache denotation index write-p))
    (workspace-p root))			;may need hack as above
  (defined-check (root denotation index)
      (declare (ignore root denotation index))
    (values nil t)))

(def-denotation-type (item-event :code 10)
    (event-name)
  (validator (cache root denotation index write-p)
    (declare (ignorable cache write-p))
    event-name
    (and (eq event-name 'delete)
         (framep root)
         (frame-of-class-p root 'item)))
  (defined-check (root denotation index)
      (declare (ignore root))
    event-name
    (values nil t)))

;; short list
;; 4 validators for element and aliased attribute
;;     well-defined checks for element and variable value
;;   think about pattern matching & well-definedness checks
;;   think about inverse navigation for pattern matching
;;    Guess: can only match on invertible links
;;             or things within the final item
;;           pattern matching should probably be rooted on the final item
;;   patterns come from subscribe
;;   patterns that come from def-deep-conclude
;;   DON'T BREAK CHAINING
;; 6 mutators
;; 7 mem management


#+development
(defun-simple disambiguate-component-particulars
    (item component-particulars new-value)
  (unless (attribute-component-particulars-p component-particulars)
    (return-from disambiguate-component-particulars component-particulars))
  (with-attribute-component-particulars
      ((attribute-name class-qualifier? enclosed-component)
       component-particulars)
    (let* ((class-description (class-description-slot item))
	   (slot-description?
	     (get-slot-description-of-class-description
	       attribute-name class-description class-qualifier?))
	   (user-defined-slot-p
	     (and slot-description?
		  (user-defined-slot-description-p slot-description?))))
      (cond
	(user-defined-slot-p
	 (let* ((slot-value? (get-user-slot-description-value
			       item slot-description?))
		(slot-value-class-description? (framep slot-value?)))
	   (cond
	     (slot-value-class-description?
	      (cond
		((not (eq enclosed-component '*current-computation-frame*))
		 component-particulars)
		(t
		 (let ((place-or-error-text
			 (if (and new-value (evaluation-symbol-p new-value))
			     (get-implied-attribute-place-or-error-description
			       slot-value? (evaluation-symbol-symbol new-value))
			     slot-value?)))
		   (cond
		     ((text-string-p place-or-error-text)
		      ;; actually return the (normalized) error
		      (access-error 'bad-implied-attribute-access
				    'reason place-or-error-text))
		     ((neq slot-value? place-or-error-text) ; its an implied attribute
		      (synthesize-implied-attribute-component
			component-particulars slot-value? place-or-error-text))
		     ((frame-of-class-p
			place-or-error-text 'variable-or-parameter)
		      (cond
			((null new-value)
			 (cond
			   ((frame-of-class-p place-or-error-text 'variable)
			    (make-variable-value-component-particulars
			      component-particulars))
			   (t
			    (make-conclude-no-value-into-non-variable-error-message
			      place-or-error-text))))
			(t
			 (make-variable-value-component-particulars
			   component-particulars))))
		     (t
		      component-particulars))))))
	     (t                ; user-defined - but no frame in slot
	      component-particulars))))
	(t                     ; not user-defined
	 component-particulars)))))

#+development
(defun-simple synthesize-implied-attribute-component
    (component-particulars item variable-in-item)
  (multiple-value-bind (parent-item attribute-name class-qualifier?)
      (get-kb-parent-information variable-in-item)
    (unless (eq parent-item item)
      (error "tell Joe he's all wet"))
    (format t "in synth iac p=~s aname=~s cq=~s~%"
	    parent-item attribute-name class-qualifier?)
    (make-variable-value-component-particulars
      (make-attribute-component-particulars
	attribute-name class-qualifier? component-particulars))))

#+development
(defun-simple convert-component-particulars (component-particulars)
  (convert-component-particulars-1 component-particulars 0))

#+development
(defun-simple convert-component-particulars-1 (component-particulars length-needed)
  (let* ((denotation-type-name (car component-particulars))
	 (length-for-current-particular
	   (denotation-type-size denotation-type-name))
	 (sub-particulars component-particulars)
	 denotation)
    ;; the following is an efficient, inline implementation of nth
    (loop for i below (-f length-for-current-particular 1)
	  do
      (setf sub-particulars (cdr-of-cons sub-particulars)))
    (setf sub-particulars (car-of-cons sub-particulars))
    (cond
      ((eq sub-particulars '*current-computation-frame*)
       (setq denotation
	     (allocate-managed-simple-vector
	       (+f length-needed length-for-current-particular))))
      (t
       (setf denotation
	     (convert-component-particulars-1
	       sub-particulars (+f length-needed length-for-current-particular)))))
    (let ((start-position
	    (-f (length-of-simple-vector denotation)
		(+f length-needed length-for-current-particular))))
      (case (car component-particulars)
	(attribute
	 (fill-simple-vector
	   (denotation start-position)
	   attribute-particular-code
	   'attribute
	   (attribute-component-particulars-attribute-name component-particulars)
	   (attribute-component-particulars-defining-class component-particulars)))
	(aliased-attribute
	 (fill-simple-vector
	   (denotation start-position)
	   aliased-attribute-particular-code
	   'aliased-attribute 
	   (aliased-attribute-alias component-particulars)
	   (aliased-attribute-actual-attribute component-particulars)
	   (aliased-attribute-defining-class component-particulars)))
	(element
	 (fill-simple-vector
	   (denotation start-position)
	   element-particular-code
	   'element
	   (element-component-particulars-index component-particulars)))
	(virtual-attribute
	 (fill-simple-vector
	   (denotation start-position)
	   virtual-attribute-particular-code
	   'virtual-attribute
	   (virtual-attribute-component-particulars-name component-particulars)))
	(variable-value
	 (fill-simple-vector
	   (denotation start-position)
	   variable-value-particular-code
	   'variable-value)))
      denotation)))


;;; `denotation-attribute-description' assumes the denotation is intended to
;;; be rooted to an item and returns the attribute-description of the first
;;; denotation element.

#+maybe
(defun-simple denotation-attribute-description (denotation)
  )

(defvar comp-trace-level 0)

#+development
(defun pprint-component (component depth)
  (labels ((contains-sublists-p (l)
	     (and (consp l)
		  (loop for x in l thereis (consp x))))
	   (z (x depth)
	     (cond ((contains-sublists-p x)
		    (format t "~vT(~s~%" depth (car x))
		    (loop for sub in (cdr x)
			  do
		      (z sub (+f depth 2))))
		   ((and (consp x)
			 (>f (length x) 2))
		    (format t "~vT(~s~%" depth (car x))
		    (format t "~vT  ~{~s ~})~%" depth (cdr x)))
		   (t
		    (format t "~vT~s~%" depth x)))))
    (z component depth)))


(defconstant subscription-callback-arg-types '(symbol (class item)
					       (sequence)
					       item-or-datum
					       item-or-datum
					       integer))


(defun represent-item-internal (icp-socket? frame denotation callback
					    user-data-value)
  ;; Normally, when we register a callback from within a g2 where we want the
  ;; callback fired, we have a NIL icp-socket? and a procedure as the callback.
  ;; When we want a callback run in a remote G2 or bridge, icp-socket? is bound
  ;; to a socket, and callback is a symbol, naming a procedure in the remote
  ;; G2/bridge.  As a convenience, we now accept a symbol for a callback in the
  ;; first case (as per PP's request, 2/2004), and in that case look for a
  ;; procedure with that name and use that. -dkuznick, 2/19/04
  
  (when (and icp-socket?
	     ;; You'd think you could say procedure-p here, but frame
	     ;; predicates have to be passed a frame!  It's unecessary to do
	     ;; the procedure-p check in addition to framep because the cap is
	     ;; supposed to enforce the symbol or procedure constraint, but we
	     ;; are going for minimal C diffs because of the late date.
	     ;; -dkuznick, 5/12/05
	     (framep callback)
	     (procedure-p callback))
    ;; This means a subscription request came in via a remote socket, but is
    ;; asking for a local callback, so forget about the socket. -dkuznick,
    ;; 5/10/05 
    (setf icp-socket? nil))
  
  (when (and (not icp-socket?)		;being called locally
	     (symbolp callback))
    (let ((procedure? (get-instance-with-name-if-any 'procedure callback)))
      (if (null procedure?)
	  (return-from represent-item-internal
	    (access-error 'no-callback-found
			  'callback callback))
	  ;; Note that callback is re-bound here to now be a procedure rather
	  ;; than a symbol
	  (setq callback procedure?))))
  ;; Check to make sure the callback signature is ok.  We'll also check again
  ;; at invocation time.
  (when (and (not icp-socket?))		;can only check local callbacks
    (check-procedure-arglist-and-maybe-notify
      callback subscription-callback-arg-types warning-message* 3))
  (multiple-value-bind (definition-error-or-inner-item-index
			   class-description?)
      (check-denotation-well-defined frame denotation)
    (cond
      ((access-error-p definition-error-or-inner-item-index)
       definition-error-or-inner-item-index)
      (t
       (let ((representation
	       (make-representation
		 (or icp-socket? local-pseudo-socket)
		 frame 'item-representation)))
	 (setf (representation-address representation)
	       (slot-value-list
		 'socket (or icp-socket? local-pseudo-socket)
		 'session-id (if icp-socket?
				 (icp-socket-session-id icp-socket?)
				 12345678)))
	 (setf (callback-representation-callback-procedure representation)
	       (demand-representation-callback-remote-procedure-name callback))
	 (when (framep callback)
	   (frame-serial-number-setf (callback-representation-callback-serial-number representation)
				     (frame-serial-number callback)))
	 (setf (item-representation-denotation representation)
	       denotation)
	 (setf (item-representation-user-data-value representation)
	       (get-reference-to-item-if-item user-data-value))
	 (install-subscription
	   class-description?
	   representation
	   denotation
	   definition-error-or-inner-item-index)
	 representation)))))

(defun-simple install-subscription (class-description
			      representation denotation inner-item-index)
  (let* ((subscription (make-class-subscription
			 denotation inner-item-index representation))
	 (class-name (class-name-of-class-description class-description))
	 (subscriptions
	   (or (class-subscriptions class-name)
	       (setf (class-subscriptions class-name)
		     (make-class-subscriptions)))))
    (cond
      ((denotation-element-specific-p denotation inner-item-index)
       (gensym-push subscription
		    (class-subscriptions-specific-denotation-table
		      subscriptions)))
      (t
       (gensym-push subscription
		    (class-subscriptions-wildcard-denotation-list
		      subscriptions))))
    (setf (item-representation-subscriptions representation)
	  subscriptions)))

(defun remove-subscription (class-subscriptions representation)
  (or (loop for subscription
		in (class-subscriptions-specific-denotation-table
		     class-subscriptions)
	    when (eq (class-subscription-representation subscription)
		     representation)
	      do
		(reclaim-class-subscription subscription)
		(setf (class-subscriptions-specific-denotation-table
			class-subscriptions)
		      (delete-gensym-element
			subscription
			(class-subscriptions-specific-denotation-table
			  class-subscriptions)))
		(return t))
      (loop for subscription
		in (class-subscriptions-wildcard-denotation-list
		     class-subscriptions)
	    when (eq (class-subscription-representation subscription)
		     representation)
	      do
		(setf (class-subscriptions-wildcard-denotation-list
			class-subscriptions)
		      (delete-gensym-element
			subscription
			(class-subscriptions-wildcard-denotation-list
			  class-subscriptions)))
		(return)))
  (setf (item-representation-subscriptions representation) nil))

(defun denotation->denotation-sequence (denotation &optional for-exposing-in-kb)
  (loop with end-index = (denotation-end-index denotation)
	with sequence-elements = '()
	for index = 0 then next-index
	as next-index = (denotation-next-index denotation 0)
		      then (denotation-next-index denotation index)
	as denotation-code = (svref denotation index)
	do
    (eval-push
      (denotation-code-case denotation-code
	(attribute
	  (let ((structure
		  (allocate-evaluation-structure-inline
		    'type 'attribute
		    ;; The following is an ugly hack because KB users of this
		    ;; facility use the symbol ALL to mean *. -dkuznick,
		    ;; 5/27/04 
		    'name (let ((val (svref denotation (+f index 2))))
			    (if (and (eq val '*)
				     for-exposing-in-kb)
				'all
				val))))
		(class-qualifier?
		  (svref denotation (+f index 3))))
	    (when class-qualifier?
	      (setf (evaluation-structure-slot
		      structure 'class-qualifier)
		    class-qualifier?))
	    structure))
	(element
	  (allocate-evaluation-structure-inline
	    'type 'element
	    'index (svref denotation (+f index 2))))
	(virtual-attribute
	  (allocate-evaluation-structure-inline
	    'type 'virtual-attribute
	    'name (svref denotation (+f index 2))))
	(variable-value
	  (allocate-evaluation-structure-inline
	    'type 'variable-value))
	(item-color-pattern-change
	  (allocate-evaluation-structure-inline
	    'type 'item-color-pattern-change))
	(custom-event
	  (allocate-evaluation-structure-inline
	    'type 'custom-event
	    'custom-event-name (svref denotation (+f index 2))))
	(add-item-to-workspace
	  (allocate-evaluation-structure-inline
	    'type 'add-item-to-workspace))
	(remove-item-from-workspace
	  (allocate-evaluation-structure-inline
	    'type 'remove-item-from-workspace))
	(item-event
	  (allocate-evaluation-structure-inline
	    'type 'item-event
	    'item-event-name (svref denotation (+f index 2)))))
      sequence-elements)
    (when (=f index end-index)
      (return
	(allocate-evaluation-sequence
	  (nreverse sequence-elements))))))

(defun-simple denotation-element-specific-p (denotation index)
  (let* ((type (svref denotation (+f index 1)))
	 (wildcard-arg-index?
	   (denotation-type-wildcard-arg-index? type)))
    (cond
      (wildcard-arg-index?
       (let ((denotation-wildcard?
	       (svref denotation wildcard-arg-index?)))
	 (cond ((eq denotation-wildcard? '*)
		nil)
	       (t
		t))))
      (t
       nil))))


(defun-simple denotation-element-equal-p
    (denotation-1 index-1 denotation-2 index-2)
  (if (denotation-element-specific-p denotation-2 index-2)
      (let* ((type (svref denotation-1 (1+f index-1)))
	     (size (denotation-type-size type)))
	(loop for i from denotation-element-overhead-slot-count
		    below size
	      always
	      (progn
;		(format t "a=~s b=~s~%"
;			(svref denotation-1 (+f index-1 i))
;			(svref denotation-2 (+f index-2 i)))
		(eq (svref denotation-1 (+f index-1 i))
		    (svref denotation-2 (+f index-2 i))))))
      t))

 

(defvar current-conclude-frame-list nil)
(defvar current-conclude-innermost-frame nil)
(defvar current-conclude-innermost-item-index nil)

#+soon
(defmacro def-deep-attribute-access ()
  )

#+soon
(def-deep-attribute-access ((class trend-chart)
			    (aliased-attribute plots trend-chart-plots nil)
			    (element *)
			    (attribute *))
    )

#+soon
(def-deep-attribute-access ((class entity)
			    (virtual-attribute icon-variables)
			    (attribute *))
    )

;; chaining must be checked from ALL items passed in the validation phase
;; deep concluders (and concluding mechanisms in general from the
;;  innermost item)

;; General Mutators
;; user-def
;;   get it (from cache) see if its the only copy
;;    obtain-mutable-copy??
;;   set part in copy and done
;; sys-def va
;;   always new copy
;;   get, clobber, set
;; variable-value
;;   put-evaluation-value & friends

(defvar current-subscribe-innermost-class nil)
(defvar current-subscribe-innermost-item-index nil)


(defun check-denotation-well-defined
    (frame-or-class-description denotation)
  (let* ((current-subscribe-innermost-class nil)
	 (current-subscribe-innermost-item-index nil)
	 (class-description
	   (if (framep frame-or-class-description)
	       (class-description-slot frame-or-class-description)
	       frame-or-class-description))
	 (root (gensym-list
		 'class
		 (class-name-of-class-description class-description)))
	 (error-string?
	   (check-denotation-well-defined-1 root denotation)))
    ;; We need the prog1 here, because root might be sitting in
    ;; current-subscribe-innermost-class after the call to
    ;; check-denotation-well-defined-1 -dkuznick, 5/24/04
    (multiple-value-prog1
	(cond
	  ((access-error-p error-string?)
	   error-string?)
	  ((not current-subscribe-innermost-item-index)
	   (access-error
	     'no-items-implied-by-denotation))
	  (t
	   (values current-subscribe-innermost-item-index
		   (class-description
		     (type-specification-class
		       current-subscribe-innermost-class)))))
      (reclaim-gensym-list root))))

(defun-simple check-denotation-well-defined-1
    (root denotation)
  (loop with end-index = (denotation-end-index denotation)
	with next-root-or-error-string = nil
	with invertible-p = nil
	for index = 0 then (denotation-next-index-macro denotation index)
	as denotation-type-name = (denotation-type-name denotation index)
	do
    (when debug-conclude-p
      (format t "root = ~s index=~s well-defined-checker=~s~%"
	      root
	      index
	      (denotation-type-defined-check
		denotation-type-name)))
    (multiple-value-setq (next-root-or-error-string invertible-p)
      (funcall (denotation-type-defined-check
		 denotation-type-name)
	       root denotation index))
    (when (class-type-specification-p root)
      (setf current-subscribe-innermost-class root)
      (setf current-subscribe-innermost-item-index index))
    ;; here do iteration and return index of
    (cond ((access-error-p next-root-or-error-string)
	   (return next-root-or-error-string))
	  ((=f index end-index)
	   (return root))
	  (t
	   (setf root next-root-or-error-string)))))

  

;;; `conclude-attribute-evaluation-value'
;;;
;;; The new-value arg is an evaluation-value.

(defmacro system-procedure-call-is-local-p ()
  `(null current-system-rpc-icp-socket?))

#+unused
(defun-simple simple-all-attribute-denotation-p (denotation)
  (let* ((type (denotation-type-name denotation 0))
	 (len (denotation-length denotation))
	 (wildcard-arg-index?
	   (denotation-type-wildcard-arg-index? type)))
    (and wildcard-arg-index?
	 (eq type 'attribute)
	 (eq (svref denotation wildcard-arg-index?)
	     '*)
	 (=f len 1))))

(defun-simple denotation-ends-in-wildcard-p (denotation)
  (loop with end-index = (denotation-end-index denotation)
	for index = 0 then (denotation-next-index-macro denotation index)
	as denotation-type = (denotation-type-name denotation index)
	as wildcard-arg-index?
	   = (denotation-type-wildcard-arg-index? denotation-type)
	do
    ;; (format t "i ~s ei ~s wci ~s ~%" index end-index wildcard-arg-index?)
    (cond ((=f index end-index)
	   (return (and wildcard-arg-index?
			(eq (svref denotation
				   (+f index wildcard-arg-index?))
			    '*))))
	  ((and wildcard-arg-index?
		(eq (svref denotation wildcard-arg-index?)
		    '*))
	   (return nil)))))
     
(defun-for-system-procedure g2-get-unique-named-item
    (item-class-ev item-name-ev)
  (let* ((item-class (evaluation-symbol-symbol item-class-ev))
	 (item-name (evaluation-symbol-symbol item-name-ev))
	 (item? (get-instance-with-name-if-any item-class item-name)))
    (cond (item?
	   item?)
	  (t
	   evaluation-false-value))))

(define-system-rpc-access (g2-get-unique-named-item (item-or-datum))
    ((item-class symbol)
     (item-name symbol))
  (g2-get-unique-named-item item-class item-name))

(defun-for-system-procedure g2-get-item-with-uuid (uuid)
  (let ((item? (the-item-having-uuid 'item uuid)))
    (reclaim-if-evaluation-value uuid)
    (cond (item?
	   item?)
	  (t
	   evaluation-false-value)))) 

(define-system-rpc-access (g2-get-item-with-uuid (item-or-datum))
    ((uuid text))
  (g2-get-item-with-uuid uuid))

;;; `g2-make-uuid' is used to expose UUID generation to G2 users.  It's first
;;; appearing in G2 6.1r0

(defun-for-system-procedure g2-make-uuid ()
  (declare (keeps-g2-local-variables-valid t))
  (twith-output-to-text-string
    (let ((uuid-internal (make-uuid)))
      (prog1 (twrite-uuid-printed-representation uuid-internal)
	(reclaim-wide-string uuid-internal)))))

(defun-for-system-procedure g2-get-from-item
    (item denotation-sequence)
  (let ((denotation-or-error
	  (denotation-sequence->denotation denotation-sequence)))
    (reclaim-evaluation-value denotation-sequence)
    (cond
      ((access-error-p denotation-or-error)
       (stack-error cached-top-of-stack
		    "~A"
		    (make-default-text-string-for-access-error
		      denotation-or-error)))
      (t
       (let ((evaluation-value-or-error
	       (get-denoted-evaluation-value item denotation-or-error)))
	 (cond ((access-error-p evaluation-value-or-error)
		(reclaim-denotation denotation-or-error)
		(stack-error cached-top-of-stack
			     "~a"
			     (make-default-text-string-for-access-error
			       evaluation-value-or-error)))
	       ((null evaluation-value-or-error)
		(let ((definition-error-or-inner-item-index
			  (check-denotation-well-defined item denotation-or-error)))
		  (cond ((access-error-p definition-error-or-inner-item-index)
			 (reclaim-denotation denotation-or-error)
			 (stack-error cached-top-of-stack
				      "~a"
				      (make-default-text-string-for-access-error
					definition-error-or-inner-item-index)))
			((system-procedure-call-is-local-p)
			 (let ((sequence (denotation->denotation-sequence
					   denotation-or-error)))
			   (reclaim-denotation denotation-or-error)
			   (stack-error cached-top-of-stack
					"Denotation ~NV in ~NF has no value"
					sequence
					item)))
			(t
			 (reclaim-denotation denotation-or-error)
			 evaluation-value-or-error))))
	       (t
		(reclaim-denotation denotation-or-error)
		evaluation-value-or-error)))))))

(defun-for-system-procedure g2-get-from-item-multiple
    (item denotation-sequences)
  (prog1
      (allocate-evaluation-sequence
	(loop for denotation-sequence
		  being each evaluation-sequence-element of denotation-sequences
	      collect (g2-get-from-item item
					(copy-evaluation-value denotation-sequence))
		using eval-cons))
    (reclaim-evaluation-value denotation-sequences)))
	      
(define-system-rpc-access (g2-get-from-item ((or (no-item) item-or-datum)))
    ((item (class item))
     (denotation-evaluation-value datum))
  (g2-get-from-item item denotation-evaluation-value))

(define-system-rpc-access (g2-get-from-item-multiple ((sequence)))
    ((item (class item))
     (denotation-sequences (sequence)))
  (unless (type-specification-type-p denotation-sequences '(sequence (sequence)))
    (stack-error cached-top-of-stack
		 "denotation-sequences argument ~NV must be a sequence of sequences"
		 denotation-sequences))
  (g2-get-from-item-multiple item denotation-sequences))

(defun-for-system-procedure g2-conclude-in-item
    (item denotation-sequence new-value)
  (let ((denotation-or-error
	  (denotation-sequence->denotation denotation-sequence)))
    (reclaim-evaluation-value denotation-sequence)
    (cond
      ((access-error-p denotation-or-error)
       (reclaim-if-evaluation-value new-value)
       (stack-error cached-top-of-stack
		    "~a"
		    (make-default-text-string-for-access-error
		      denotation-or-error)))
      (t
       (let ((error?
	       (conclude-attribute-evaluation-value
		 item denotation-or-error new-value t)))
	 (reclaim-denotation denotation-or-error)
	 (when (access-error-p error?)
	   (stack-error cached-top-of-stack
			"~a"
			(make-default-text-string-for-access-error
			  error?)))
	 evaluation-true-value)))))
 
(define-system-rpc-access (g2-conclude-in-item (truth-value))
    ((item (class item))
     (denotation-sequence (sequence))
     (new-value (or (no-item) datum)))
  (g2-conclude-in-item item denotation-sequence new-value))


;;; The function `g2-subscribe-to-item' causes callback to be called whenever
;;; the given aspect of the given item is changed. The returned value is a
;;; subscription object, which is a structure containing a SUBSCRIPTION-HANDLE
;;; slot and an INITIAL-VALUE slot.

;;; It is used internally by Javalink and T2 as an RPC. It is available,
;;; undocumented, to KB developers via this system procedure. See HQ-4340386
;;; "Productize G2 event model used by Javalink and TW2".

;;; Subscriptions are stored in the global `representation-handle' hash table,
;;; as well as indexed by the item class, I think. Subscription handles are
;;; fixnums which count upwards without reuse or checks for overflow.

;;; The denotation-sequence is a sequence of denotations describing a "path" to
;;; the aspect of the item which shall be monitored (I believe). Each denotation
;;; is a structure with a TYPE slot. Each type may have different other slots.

;;; For the simple case of monitoring a top-level item attribute, the
;;; denotation-sequence looks like:

;;;  sequence(structure(TYPE: the symbol ATTRIBUTE,
;;;                     NAME: the symbol <name-of-attribute-to-monitor>))

;;; Except that this syntax doesn't parse in the editor because of the reserved
;;; word "NAME"; you have to construct the denotation using
;;; evaluated-structure().

;;; The possible denotation types are: ATTRIBUTE, ALIASED-ATTRIBUTE, ELEMENT,
;;; VIRTUAL-ATTRIBUTE, VARIABLE-VALUE. I'm not sure all are fully implemented

;;; The callback should be either a symbol or a procedure object. If it is a
;;; symbol, then it will be assumed to name a local procedure if we are not
;;; being run within the call-tree of a remote-procedure-call, otherwise, it
;;; will be assumed to name a remote-procedure-call.  Otherwise, it is a KB
;;; procedure.

;;; It gets the following arguments, at least in the case of simple attribute
;;; denotation sequences:

;;;  callback(event: symbol,           { MODIFY, DELETE, SHOW, HIDE, ...}
;;;           item: class item {when local, otherwise a network-registration
;;;                              handle for the item - if using a callback into
;;;                              GSI, you want to use gsi_handle_of to get the
;;;                              value, not gsi_int_of} 
;;;           denotation-sequence: sequence,
;;;           new-value: item-or-value,
;;;           user-data: item-or-value,
;;;           subscription-handle: integer)

;;; The callback is called whenever the attribute of item is set, even if set to
;;; it's current value.

;;; The allow-batched-update-p argument is ignored.

;;; An example KB can be found in /home/fmw/pub/subscribe.kb

;;; This unprecedented bit of documentation for functions in this section
;;; brought to you by -fmw, 7/18/03.

(defun-for-system-procedure g2-subscribe-to-item
    (item denotation-sequence callback user-data allow-batched-update-ev)
  (let ((allow-batched-update-p
	  (prog1 (evaluation-truth-value-is-true-p allow-batched-update-ev)
	    (reclaim-evaluation-truth-value allow-batched-update-ev)))
	(denotation-or-error
	  (denotation-sequence->denotation denotation-sequence)))
    (declare (ignore allow-batched-update-p))
    (reclaim-evaluation-value denotation-sequence)
    (cond
      ((access-error-p denotation-or-error)
       (reclaim-if-evaluation-value user-data)
       (stack-error cached-top-of-stack
		    "~a"
		    (make-default-text-string-for-access-error
		      denotation-or-error)))
      (t
       (let ((representation-or-error
	       (represent-item-internal
		 (or current-system-rpc-icp-socket? ;javalink/tw2
		     ;; We are being registered via an RPC somewhere up the call
		     ;; tree 
		     (let ((rpc? (find-remote-procedure-call-for-code-body-invocation
				   current-computation-instance)))
		       (and rpc? (remote-procedure-call-icp-socket rpc?))))
		 item denotation-or-error callback user-data)))
	 (cond
	   ((access-error-p representation-or-error)
	    (reclaim-denotation denotation-or-error)
	    (stack-error cached-top-of-stack
			 "~a"
			 (make-default-text-string-for-access-error
			   representation-or-error)))
	   (t
	    (let ((initial-subscription-value-or-error
		    (get-denoted-evaluation-value
		      item denotation-or-error)))
	      (cond
		((access-error-p initial-subscription-value-or-error)
		 #+development
		 (cerror "go on" "subsciption had error in getting initial value")
		 (stack-error cached-top-of-stack
			      "~a"
			      (make-default-text-string-for-access-error
				initial-subscription-value-or-error)))
		(t
		 (let ((subscription-handle
			 (store-callback-representation representation-or-error)))
		   (allocate-evaluation-structure-inline
		     'subscription-handle subscription-handle
		     'initial-value initial-subscription-value-or-error))))))))))))

(defun-for-system-procedure g2-subscribe-to-item-multiple
    (item denotation-sequences callback user-data allow-batched-update)
  (prog1
      (allocate-evaluation-sequence
	(loop for denotation-sequence
		  being each evaluation-sequence-element of denotation-sequences
	      collect (g2-subscribe-to-item
			item
			(copy-evaluation-value denotation-sequence)
			callback
			(copy-if-evaluation-value user-data)
			(copy-evaluation-value allow-batched-update))
		using eval-cons))
    (reclaim-evaluation-value denotation-sequences)
    (reclaim-if-evaluation-value user-data)
    (reclaim-evaluation-value allow-batched-update)))

;;; One could write a g2-subscribe-to-multiple-items-multiple, but this is not that
;;; function. The t2-performance functions are completely untested.
#+t2-performance
(defun-for-system-procedure g2-subscribe-to-multiple-items
    (item-denotation-sequences callback user-data allow-batched-update)
  (prog1
      (allocate-evaluation-sequence
	(loop for item-denotation-sequence
		  being each evaluation-sequence-element of item-denotation-sequences
	      as item = (evaluation-structure-slot item-denotation-sequence 'item)
	      as denotation-sequence = (evaluation-structure-slot
					 item-denotation-sequence
					 'denotation-sequence)
	      collect (g2-subscribe-to-item
			item
			(copy-evaluation-value denotation-sequence)
			callback
			(copy-if-evaluation-value user-data)
			(copy-evaluation-value allow-batched-update))
		using eval-cons))
    (reclaim-evaluation-value item-denotation-sequences)
    (reclaim-if-evaluation-value user-data)
    (reclaim-evaluation-value allow-batched-update)))

(define-system-rpc-access (g2-subscribe-to-item ((structure)))
    ((item (class item))
     (denotation-sequence (sequence))
     (callback symbol)
     (user-data datum)
     (allow-batched-update truth-value))
  (g2-subscribe-to-item
    item denotation-sequence callback user-data allow-batched-update))

(define-system-rpc-access (g2-subscribe-to-item-multiple ((sequence)))
    ((item (class item))
     (denotation-sequences (sequence))
     (callback symbol)
     (user-data datum)
     (allow-batched-update truth-value))
  (unless (type-specification-type-p denotation-sequences '(sequence (sequence)))
    (stack-error cached-top-of-stack
		 "denotation-sequences argument ~NV must be a sequence of sequences"
		 denotation-sequences))
  (g2-subscribe-to-item-multiple
    item denotation-sequences callback user-data allow-batched-update))

#+t2-performance
(define-system-rpc-access (g2-subscribe-to-multiple-items ((sequence)))
    ((item-denotation-sequences (sequence))
     (callback symbol)
     (user-data datum)
     (allow-batched-update truth-value))
  (unless (type-specification-type-p item-denotation-sequences '(sequence (structure)))
    (stack-error cached-top-of-stack
		 "denotation-sequences argument ~NV must be a sequence of structures"
		 item-denotation-sequences))
  (g2-subscribe-to-multiple-items
    item-denotation-sequences callback user-data allow-batched-update))

;;; `get-representation-from-subscription-handle' gets the representation
;;; associated with the handle, or NIL.

(defun get-representation-from-subscription-handle (handle)
  (and (not (minuspf handle))		;to allow 0
       (representation-handle-gethash
	 (evaluation-integer-value handle))))

(defun-for-system-procedure g2-unsubscribe-to-item (subscription-index)
  (let ((representation? (get-representation-from-subscription-handle
			   subscription-index)))
    (when representation?
      (delete-representation representation?))
    nil))

(defun-for-system-procedure g2-unsubscribe-to-item-multiple
    (sequence-of-indices)
  (loop for index being each evaluation-sequence-element of sequence-of-indices
	do
    (g2-unsubscribe-to-item index))
  (reclaim-evaluation-sequence sequence-of-indices)
  nil)

(define-system-rpc-access (g2-unsubscribe-to-item ())
    ((subscription-handle integer))
  (g2-unsubscribe-to-item subscription-handle))

(define-system-rpc-access (g2-unsubscribe-to-item-multiple ())
    ((subscription-handle-sequence (sequence))) 
  (unless (type-specification-type-p subscription-handle-sequence '(sequence integer))
    (stack-error cached-top-of-stack
		 "handle-sequence argument ~NV must be a sequence of integers"
		 subscription-handle-sequence))
  (g2-unsubscribe-to-item-multiple subscription-handle-sequence))


;;; `g2-subscribe-to-item-attributes' is a variation of g2-subscribe-to-item and
;;; g2-subscribe-to-item-multiple to make it easier to expose this functionality
;;; to G2 users.  Its attribute-spec is in a friendlier format, and simply
;;; massages them to call g2-subscribe-to-item or g2-subscribe-to-item-multiple,
;;; and then simplifies the return value to just the subscription-handle(s).

;;; The signature is
;;; g2-subscribe-to-item-attributes (item attr-spec callback user-data)
;;;   ITEM - the item to subscribe to.
;;;   ATTR-SPEC - either a symbol naming an attribute in ITEM, the symbol ALL
;;;               which is interpreted as subscribing to all an item's attributes
;;;               (system and user-defined), or a sequence of symbols which name
;;;               attributes.  As a special case, the symbol * is not allowed.
;;;  CALLBACK - a procedure to run when the subscribed to attribute(s) get
;;;             modified.  Signature of the callback documented above
;;;             g2-subscribe-to-item.
;;;  USER-DATA - an item-or-value that gets passed to the CALLBACK.
;;;
;;; The return value is either an integer which is a subscription-handle
;;; intended to be passed to g2-unsubscribe-to-item to remove the subscription,
;;; or in the case where ATTR-SPEC is a sequence, is a sequence of such handles,
;;; in correpsonding order. 

;;; See projects/core-0032-publish-subscribe.html for more documentation.

(defun-for-system-procedure g2-subscribe-to-item-attributes
    (item attr-spec callback user-data)
  (let ((return-val
	  (subscribe-to-item-attributes-body item attr-spec callback user-data)))
    (evaluation-typecase return-val
      ;; This is the simple case of
      ;; structure(subscription-handle: <handle>, initial-value: <value>)
      (evaluation-structure
	(prog1
	    (copy-evaluation-integer	;to comply with the
					;evaluation-structure-slot-macro spec
	      (evaluation-structure-slot-macro evaluation-structure
					       'subscription-handle))
	  (reclaim-evaluation-structure return-val)))
      ;; This is the case when we get a sequence of structures
      (evaluation-sequence
	(let ((seq-to-return (allocate-empty-evaluation-sequence
			       (evaluation-sequence-length return-val))))
	  (loop for struct being
		each evaluation-sequence-element of evaluation-sequence
		for i from 0
		do
	    (setf (evaluation-sequence-aref seq-to-return i)
		  (copy-evaluation-integer
		    (evaluation-structure-slot-macro struct
						     'subscription-handle))))
	  (prog1
	      seq-to-return
	    (reclaim-evaluation-sequence return-val))))
      ;; Should never happen.  If so, it's our coding error.
      (otherwise
	#-development -1
	#+development (error "Got unexpected value back from ~
                              subscribe-to-item-attributes-body.")))))

;; In G2 8.0a0 and 8.0a1, there existed a system-procedure called
;; g2-subscribe-to-item-attributes-returning-current-values.  It was the other
;; user of subscribe-to-item-attributes-body, and simply returned its value.
;; This was removed for 8.0b0, but we'll keep the body-function here for
;; abstraction purposes (Lowell's rule says nothing about un-abstracting :-)

(defun subscribe-to-item-attributes-body (item attr-spec callback user-data)
  (evaluation-typecase attr-spec
    (evaluation-symbol
     (when (eq evaluation-symbol '*)
       (reclaim-if-evaluation-value user-data)
       ;; Disallow "*" so users don't accidentally get a surprise, which would
       ;; be to subscribe to all attributes.
       (stack-error cached-top-of-stack
		    "The attribute-specification * is not allowed."))
     (g2-subscribe-to-item item
			   (allocate-evaluation-sequence
			     (eval-list
			       (allocate-evaluation-structure-inline
				 'type 'attribute
				 ;; Here's where we reinterpret ALL as *
				 'name (if (eq evaluation-symbol 'all)
					   '*
					   evaluation-symbol))))
			   callback
			   user-data
			   evaluation-false-value))
    ;; In the case of a sequence, we interpet that as a sequence of
    ;; attribute-names and call g2-subscribe-to-item-multiple.  In this case we
    ;; return a sequence of structures.  The structures are described in the
    ;; typecase clause about evaluation-symbol.  This means that you are
    ;; actually registering multiple subscriptions (and hence getting back
    ;; multiple handles) in this case.

    ;; Also note from here on out, if we want to throw a stack-error, we have to
    ;; use write-stack-error, so we can properly reclaim the attr-spec.
    (evaluation-sequence
     (unless (type-specification-type-p evaluation-sequence '(sequence symbol))
       (reclaim-if-evaluation-value user-data)
       (write-stack-error cached-top-of-stack
	 (tformat
	   "The attribute-specification ~NV must be a sequence of symbols."
	   attr-spec)
	 (reclaim-evaluation-sequence attr-spec)))
     (let* ((problem-p nil)
	    (new-sequence-contents
	      (loop for attr-name
			being each evaluation-sequence-element of attr-spec
		    ;; Check for elements being symbols and not "*"
		    if (or (not (symbolp attr-name))
			   (eq attr-name '*))
		       do (setq problem-p t) and (loop-finish)
		      else
			collect (allocate-evaluation-sequence
				  (eval-list
				    (allocate-evaluation-structure-inline
				      'type 'attribute
				      'name attr-name)))
			  using eval-cons)))
       (when problem-p
	 (loop for seq in new-sequence-contents
	       do (reclaim-evaluation-sequence seq))
	 (reclaim-eval-list new-sequence-contents)
	 (reclaim-if-evaluation-value user-data)
	 (write-stack-error cached-top-of-stack
	   (tformat
	     "The attribute-specification ~NV must not contain the symbol *."
	     attr-spec)
	   (reclaim-evaluation-sequence attr-spec)))
       
       (g2-subscribe-to-item-multiple
	 item
	 (allocate-evaluation-sequence new-sequence-contents)
	 callback
	 user-data
	 evaluation-false-value)))
    (otherwise
     (reclaim-if-evaluation-value user-data)
     (write-stack-error cached-top-of-stack
       (tformat
	 "The attribute-specification ~NV must be a symbol or a seqeuence ~
          of symbols."
	 attr-spec)
       (reclaim-evaluation-value attr-spec)))))


;;; `g2-subscribe-to-item-color-pattern-change' is used to subscribe to color
;;; changes to an item.  Currently, you get notified of changes to any and all
;;; regions.  In the future, we may add a way to subscribe only to certain
;;; regions.  See `g2-subscribe-to-item-attributes' for details on the arguments
;;; and return value (which is always an integer).  The callback has the same
;;; signature as for attribute subscriptions: the  event symbol will be
;;; ITEM-COLOR-PATTERN-CHANGE, the denotation-sequence will be: 
;;;
;;; sequence(structure(type: the symbol ITEM-COLOR-PATTERN-CHANGE))
;;;
;;; and the new-value will be a structure which is a subset of the
;;; item-color-pattern virtual attribute according to which region(s) changed.

(defun-for-system-procedure g2-subscribe-to-item-color-pattern-change
    (item callback user-data)
  (let ((return-val (g2-subscribe-to-item
		      item
		      (allocate-evaluation-sequence
			(eval-list
			  (allocate-evaluation-structure-inline
			    'type 'item-color-pattern-change)))
		      callback
		      user-data
		      evaluation-false-value)))
    (prog1
	(copy-evaluation-integer
	  (evaluation-structure-slot-macro return-val 'subscription-handle))
      (reclaim-evaluation-structure return-val))))


;;; `g2-subscribe-to-custom-event' is used to subscribe to "custom" events
;;; (events which are specified at the KB level).  A future enhancement will be
;;; to provide the actual event to be sent later, and incorporate that in the
;;; denotation so only the "right" callbacks are run.

(defun-for-system-procedure g2-subscribe-to-custom-event
    (item custom-event-name callback user-data)
  (let ((return-val (g2-subscribe-to-item
		      item
		      (allocate-evaluation-sequence
			(eval-list
			  (allocate-evaluation-structure-inline
			    'type 'custom-event
			    'custom-event-name (copy-evaluation-symbol
						 custom-event-name))))
		      callback
		      user-data
		      evaluation-false-value)))
    (prog1
	(copy-evaluation-integer
	  (evaluation-structure-slot-macro return-val 'subscription-handle))
      (reclaim-evaluation-structure return-val))))


;;; `g2-send-notification-to-item' is used to send a "custom" event to
;;; callbacks.  The argumnets are the item to send the event to, a symbol
;;; naming an event, and an item-or-value that will be
;;; passed to the callbacks in the new-val argument.
;;

(defun-for-system-procedure g2-send-notification-to-item (item event info)
  (prog1
      (update-subscriptions-for-custom-event item event info)
    (reclaim-evaluation-symbol event)
    (reclaim-if-evaluation-value info)))

;;; g2-subscribe-to-item-event is used to subscribe to "item" level events.
;;; and currently, the only supported "item" level event is 'delete. In
;;; future, this can be extended to support move "item" level event like 
;;; moved...

(defun-for-system-procedure g2-subscribe-to-item-event
    (item item-event-name callback user-data)
  (let ((return-val (g2-subscribe-to-item
		      item
		      (allocate-evaluation-sequence
			(eval-list
			  (allocate-evaluation-structure-inline
			    'type 'item-event
			    'item-event-name (copy-evaluation-symbol
						 item-event-name))))
		      callback
		      user-data
		      evaluation-false-value)))
    (prog1
	(copy-evaluation-integer
	  (evaluation-structure-slot-macro return-val 'subscription-handle))
      (reclaim-evaluation-structure return-val))))

(defun-void send-notification-to-item-internal (item event)
  (update-subscriptions-for-item-event item event))

(defun-for-system-procedure g2-subscribe-to-add-item-to-workspace
    (workspace callback user-data)
  (subscribe-to-add-or-remove-item-from-workspace
    workspace callback user-data 'add-item-to-workspace))

(defun-for-system-procedure g2-subscribe-to-remove-item-from-workspace
    (workspace callback user-data)
  (subscribe-to-add-or-remove-item-from-workspace
    workspace callback user-data 'remove-item-from-workspace))

(defun subscribe-to-add-or-remove-item-from-workspace
    (workspace callback user-data denotation-name)
  (let ((return-val (g2-subscribe-to-item
		      workspace
		      (allocate-evaluation-sequence
			(eval-list
			  (allocate-evaluation-structure-inline
			    'type denotation-name)))
		      callback
		      user-data
		      evaluation-false-value)))
    (prog1
	(copy-evaluation-integer
	  (evaluation-structure-slot-macro return-val 'subscription-handle))
      (reclaim-evaluation-structure return-val))))

;;; `g2-subscribe-to-variable-or-parameter-value' is used to subscribe to
;;; changes to the value of a variable or parameter.  It takes a
;;; variable-or-parameter, a callback and user-data and returns an integer
;;; subscription handle.  The callback has the same signature as for attribute
;;; subscriptions: the event symbol will be MODIFY, the denotation-sequence
;;; will be:
;;;
;;; sequence(structure(type: the symbol VARIABLE-VALUE))
;;;
;;; and the new-value will be the new value.  Note that unlike attribute
;;; modifications, which get callbacks triggered regardless of the old value,
;;; these callbacks will only get triggered if the new value is different from
;;; the old value, or in the case of a variable, if the old value is an expired
;;; value.

(defun-for-system-procedure g2-subscribe-to-variable-or-parameter-value
    (variable-or-parameter callback user-data)
  (let ((return-val (g2-subscribe-to-item
		      variable-or-parameter
		      (allocate-evaluation-sequence
			(eval-list
			  (allocate-evaluation-structure-inline
			    'type 'variable-value)))
		      callback
		      user-data
		      evaluation-false-value)))
    (prog1
	(copy-evaluation-integer
	  (evaluation-structure-slot-macro return-val 'subscription-handle))
      (reclaim-evaluation-structure return-val))))

;;; `g2-get-subscription-handle-info' takes a subscription-handle (an integer)
;;; and returns a structure containing information about the corresponding
;;; subscription as follows:
;;;
;;;  structure(subscribed-item: <item>,
;;;            subscribed-callback: <procedure-or-symbol>,
;;;            subscribed-denotation: <sequence>,
;;;            subscription-user-data: <item-or-value>)
;;;
;;; A stack-error is thrown if an invalid handle is passed.

(defun-for-system-procedure g2-get-subscription-handle-info (handle)
  (declare (keeps-g2-local-variables-valid t))
  (let ((representation? (get-representation-from-subscription-handle handle)))
    (if (null representation?)
	(stack-error cached-top-of-stack
		     "~NV is not a valid subscription handle."
		     handle)
	(let ((subscribed-callback
		;; The copy is silly since this is always a procedure or
		;; a symbol, but if we ever box symbols or something like
		;; that, this is correct
		(copy-if-evaluation-value
		  (callback-representation-callback-procedure
		    representation?))))
	  (allocate-evaluation-structure-inline
	    'subscribed-item (represented-frame representation?)
	    'subscribed-callback subscribed-callback
	    'subscription-denotation (denotation->denotation-sequence
				       (item-representation-denotation
					 representation?)
				       t)
	    'subscription-user-data (copy-if-evaluation-value
				      (item-representation-user-data-value
					representation?)))))))

;;; `g2-get-subscription-handles-for-item' takes an item and returns a sequence
;;; of subscription-handles for that item.  An empty sequence is returned in
;;; the case of none being found.

(defun-for-system-procedure g2-get-subscription-handles-for-item (item)
  (declare (keeps-g2-local-variables-valid t))
  (allocate-evaluation-sequence
    (loop for representation in (frame-representations item)
	  when (item-representation-p representation)
	    collect (callback-representation-callback-subscription-handle
		      representation)
	      using eval-cons)))

;;; This one is scary...
#+too-scary
(defun-for-system-procedure g2-clear-all-subscriptions ()
  (loop with representations = (loop for v being each hash-value
				     of the-representation-handle-hashtable
				     collect v using gensym-cons)
	for representation in representations
	do (delete-representation representation) ;look closely!!!
	finally
	  (reclaim-gensym-list representations)
	;; yikes!!
	  (setf current-callback-representation-subscription-handle 0)))
	

#+development
(defun show-component-disambiguation (item component-particulars new-value)
  (let ((disambiguated-component-or-error-string
	  (disambiguate-component-particulars
	    item component-particulars new-value)))
    (format t "Disambiguate Input: (on ~s)~%" item)
    (pprint component-particulars)
    (terpri)
    (format t "Disambiguate Output:~%")
    (pprint disambiguated-component-or-error-string)
    (terpri)
    (cond ((text-string-p disambiguated-component-or-error-string)
	   )
	  (t
	   (conclude-attribute-evaluation-value
	     item
	     (convert-component-particulars disambiguated-component-or-error-string)
	     new-value
	     nil)))
    disambiguated-component-or-error-string))
  

(defun-simple get-denoted-evaluation-value (item denotation)
  (cond
    ((denotation-ends-in-wildcard-p denotation)
     (let ((end-index (denotation-end-index denotation)))
       (cond
	 ((=f end-index 0)
	  (allocate-evaluation-structure
	    (loop with all-user-visible-attributes =
		  (get-list-of-all-user-visible-attributes
		    (class-description-slot item))
		  with result-list = '()
		  for name-description in all-user-visible-attributes
		  as name = (car-of-cons name-description)
		  do
	      (unless (exclude-from-wildcard-denotation-p name)
		(eval-push name result-list)
		(eval-push (get-attribute-description-evaluation-value
			     item (cdr-of-cons name-description))
			   result-list))
		  finally
		    (reclaim-eval-alist all-user-visible-attributes)
		    (return (nreverse result-list))
		  )))
	 (t
	  (let ((sub-denotation (sub-denotation denotation 0 end-index)))
	    (prog1
		(get-denoted-evaluation-value item sub-denotation)
	      (reclaim-denotation sub-denotation)))))))
    (t
     (loop with root = item
	   with cache = (make-item-access-cache) ; here, then test through sys-proc
	   ;; then make sys-procs/rpcs for subscribe and unsubscribe
	   ;; and a sys-rpc for conclude
	   with end-index = (denotation-end-index denotation)
	   for index = 0 then (denotation-next-index-macro denotation index)
	   as next-root-or-error-string
	      = (progn
		  (when debug-conclude-p
		    (format t "root = ~s index=~s validator=~s~%"
			    root
			    index
			    (denotation-type-validator
			      (denotation-type-name denotation index))))
		  (funcall (denotation-type-validator
			     (denotation-type-name denotation index))
			   cache root denotation index nil))
	   do
       (cond ((access-error-p next-root-or-error-string)
	      (delete-item-access-cache cache)
	      (return next-root-or-error-string))
	     ((=f index end-index)
	      ;; (remove-value-from-access-cache next-root-or-error-string)
	      (let ((result
		      (copy-if-evaluation-value next-root-or-error-string)))
		(delete-item-access-cache cache)
		(return
		  (if (evaluation-truth-value-p result)
		      result
		      (coerce-user-slot-value-to-evaluation-value result)))))
	     (t
	      (setf root next-root-or-error-string)))))))

(defun-simple conclude-attribute-evaluation-value
    (item denotation new-value mutate-p)
  (let* ((current-conclude-innermost-frame nil)
	 (current-conclude-frame-list '())
	 (current-conclude-innermost-item-index nil)
	 (cache (make-item-access-cache))
	 place-or-error-text?)
    #+development
    (when debug-conclude-p
      (format t "Denotation: ~%")
      (pprint-denotation denotation))
    (setf place-or-error-text? (validate-denotation cache item denotation))
    (when debug-conclude-p
      (format t "~%Place or Error: ~s ~% f-list=~s~% inner-frame=~s~%"
	      place-or-error-text?
	      current-conclude-frame-list
	      current-conclude-innermost-frame))
    (cond
      ((not (access-error-p place-or-error-text?))
       (let* ((class-subscriptions
		(class-subscriptions-macro
		  (class current-conclude-innermost-frame)))
	      (matching-subscriptions
		(if class-subscriptions
		    (match-subscriptions
		      class-subscriptions
		      denotation current-conclude-innermost-item-index)))
	      (matching-representations '()))
	 
	 (when debug-conclude-p
	   (format t "matching-subscriptions=~s~%"
		   matching-subscriptions))
	 (loop for subscription in matching-subscriptions
	       do
	   (let* ((representation
		    (class-subscription-representation subscription))
		  (represented-frame (represented-frame representation))
		  (match-p
		    (representation-represents-item-p
		      cache represented-frame
		      (class-subscription-denotation subscription)
		      (class-subscription-inner-item-index subscription)
		      current-conclude-innermost-frame)))
	     (when debug-conclude-p
	       (format t "~s passes-filter=~s~%" represented-frame match-p))
	     (when match-p
	       (gensym-push (gensym-cons representation represented-frame)
			    matching-representations))))
	 (and mutate-p
	      (prog1
		  (let ((access-error?
			  (mutate-denoted-item-part
			    current-conclude-innermost-frame denotation
			    current-conclude-innermost-item-index new-value)))
		    (cond ((access-error-p access-error?)
			   access-error?)
			  (t
			   (loop for representation-and-frame in matching-representations
				 as representation = (car-of-cons representation-and-frame)
				 as frame = (cdr-of-cons representation-and-frame)
				 do
			     (when nil
			       (update-representation-with-denotation
				 representation frame denotation))
			     (reclaim-gensym-cons-macro representation-and-frame))
			   (reclaim-gensym-list matching-representations)
			   nil)))
		(reclaim-gensym-list current-conclude-frame-list)
		(delete-item-access-cache cache)))))
      (t
       (reclaim-gensym-list current-conclude-frame-list)
       (delete-item-access-cache cache)
       place-or-error-text?))))

(defun-simple gather-affected-representations
    (cache matching-subscriptions mutated-frame)
  (let ((matches '()))
    (loop for subscription in matching-subscriptions
	  do
      (let ((match-p
	      (representation-represents-item-p
		cache
		(represented-frame
		  (class-subscription-representation subscription))
		(class-subscription-denotation subscription)
		(class-subscription-inner-item-index subscription)
		mutated-frame)))
	(when match-p
	  (gensym-pushnew (class-subscription-representation subscription)
			  matches))))
    matches))

(defun-simple validate-denotation (cache root denotation)
  (loop with end-index = (denotation-end-index denotation)
	for index = 0 then (denotation-next-index-macro denotation index)
	as next-root-or-error-string
	   = (progn
	       (when debug-conclude-p
		 (format t "root = ~s index=~s validator=~s~%"
			 root
			 index
			 (denotation-type-validator
			   (denotation-type-name denotation index))))
	       (funcall (denotation-type-validator
			  (denotation-type-name denotation index))
			cache root denotation index t))
	do
    (when (framep root)
      (setf current-conclude-innermost-item-index index)
      (gensym-push root current-conclude-frame-list)
      (setf current-conclude-innermost-frame root))
    (cond ((access-error-p next-root-or-error-string)
	   (return next-root-or-error-string))
	  ((=f index end-index)
	   (return root))
	  (t
	   (setf root next-root-or-error-string)))))

(defun-simple representation-represents-item-p (cache root denotation
						      end-index end-item)
  (loop for index = 0 then (denotation-next-index-macro denotation index)
	do
    (when debug-conclude-p
      (format t "resfilter root = ~s index=~s end=~s validator=~s~%"
	      root
	      index
	      end-index
	      (denotation-type-validator
		(denotation-type-name denotation index))))
    (cond
      ((=f index end-index)
       (return (eq root end-item)))
      (t
       (let ((next-root-or-error
	       (funcall (denotation-type-validator
			  (denotation-type-name denotation index))
			cache root denotation index nil)))
	 (cond ((access-error-p next-root-or-error)
		(return nil))
	       (t
		(setf root next-root-or-error))))))))

(defun-simple gather-matching-subscriptions (class denotation index)
  (let ((subscriptions? (class-subscriptions class)))
    (cond
      (subscriptions?
       (let ((result (match-subscriptions subscriptions? denotation index)))
;	 (when result
;	   (format t "found subs match on ~s with ~s at ~s => ~s"
;		   class denotation index result))
	 result))
      (t
       nil))))

(defun-simple match-subscriptions (subscriptions denotation index)
  (let ((result '()))
    (when (denotation-element-specific-p denotation index)
      (loop for subscription
		in (class-subscriptions-specific-denotation-table
		     subscriptions)
	    when (denotation-tails-match-p
		   (class-subscription-denotation subscription)
		   (class-subscription-inner-item-index subscription)
		   denotation
		   index)
	      do (gensym-push subscription result)))
    (loop for subscription
	      in (class-subscriptions-wildcard-denotation-list subscriptions)
	  when (denotation-tails-match-p
		 (class-subscription-denotation subscription)
		 (class-subscription-inner-item-index subscription)
		 denotation
		 index)
	    do (gensym-push subscription result))
    result))

(defmacro virtual-attribute-denotation-name (d i)
  `(svref ,d (+f ,i 2)))

(defmacro attribute-denotation-name (d i)
  `(svref ,d (+f ,i 2)))

(defun-simple denotation-tails-match-p
    (subscription-denotation subscription-start-index
     conclude-denotation conclude-start-index)
  (loop with subscription-end-index
	  = (length-of-simple-vector subscription-denotation)
	with conclude-end-index
	  = (length-of-simple-vector conclude-denotation)
	for subscription-index
	    = subscription-start-index
	    then (denotation-next-index-macro
		   subscription-denotation subscription-index)
	for conclude-index
	    = conclude-start-index
	    then (denotation-next-index-macro
		   conclude-denotation conclude-index)
	as subscription-denotation-code
	   = (and (<f subscription-index subscription-end-index)
		  (svref subscription-denotation subscription-index))
	as conclude-denotation-code
	   = (and (<f conclude-index conclude-end-index)
		  (svref conclude-denotation conclude-index))
	do
    (when debug-conclude-p
      (format t "dtm-p loop si ~s sei ~s sdc ~s ci ~S cei~s cdc ~s~%"
	      subscription-index subscription-end-index subscription-denotation-code
	      conclude-index conclude-end-index conclude-denotation-code))
    (cond ((and (=f subscription-index subscription-end-index)
		(=f conclude-index conclude-end-index))
	   (return t))
	  ((=f subscription-index subscription-end-index)
	   (return nil))
	  ((=f conclude-index conclude-end-index)
	   (return t))
	  ((=f subscription-denotation-code conclude-denotation-code)
	   (cond
	     ((denotation-element-equal-p
		conclude-denotation conclude-index
		subscription-denotation subscription-index)
	      (unless (denotation-element-specific-p
			subscription-denotation subscription-index)
		(when debug-conclude-p
		  (format t "wildcard tail match~%"))
		(return t)))
	     (t
	      (return nil))))
	  (t
	   (let ((subscription-denotation-type
		   (svref subscription-denotation
			  (1+f subscription-index)))
		 match-p)
	     (denotation-code-case conclude-denotation-code
	       (attribute
		 (when debug-conclude-p
		   (format t "conc attr with sub ~S~%" subscription-denotation-type))
		 (case subscription-denotation-type
		   (virtual-attribute
		    (setq
		      match-p
		      (and (eq (attribute-denotation-name
				 conclude-denotation conclude-index)
			       (virtual-attribute-denotation-name
				 subscription-denotation subscription-index)))))))
	       (virtual-attribute
		 (when debug-conclude-p
		   (format t "conc virt with sub ~S~%" subscription-denotation-type))
		 (case subscription-denotation-type
		   (attribute
		    (setq
		      match-p
		      (let ((subscription-attribute-name
			      (attribute-denotation-name
				subscription-denotation subscription-index)))
			(or (and(eq subscription-attribute-name '*)
				(not (exclude-from-wildcard-denotation-p
				       (attribute-denotation-name
					 conclude-denotation
					 conclude-index))))
			    (eq (virtual-attribute-denotation-name
				  conclude-denotation conclude-index)
				subscription-attribute-name))))))))
	     (unless match-p
	       (return nil)))))
	finally
	  (error "internal error in denotation-tails-match-p")))

(defun-simple exclude-from-wildcard-denotation-p (attr-name)
  (let ((virtual-attribute (virtual-attribute attr-name)))
    (and virtual-attribute
	 (let ((features (virtual-attribute-features virtual-attribute)))
	   (loop for (feature value) on features by #'cddr
		 thereis (and (eq 'exclude-from-wildcard-denotation feature)
			      value))))))


;;;; Implied Attribute Handling




;;; The function `implied-attribute-of-class?' takes a target-class and a
;;; symbolic-value and returns the name of the unique attribute of the target
;;; class for which the symbolic value is a possible value.  If there is no such
;;; unique attribute, nil is returned.  If more than one attribute is found,
;;; then a third value is returned which is a text-string describing the
;;; trouble.

(defun implied-attribute-of-class? (target-class symbolic-value)
  (loop with target-description = (class-description target-class)
	with slot-description
	with target-class-inheritance-path
	  = (class-inheritance-path target-description)
	with desired-unique-attribute? =  nil
	with desired-unique-class? =  nil
	for (class . attribute) in (attribute-value-macro symbolic-value)
	doing
    (when (memq-macro class target-class-inheritance-path)
      (cond
	(desired-unique-attribute?
	 (return
	   (values
	     nil nil
	     (tformat-text-string
	       "More than one attribute of class ~a has ~a as a possible ~
                 value.  The implied attributes feature cannot be used when ~
                 this is the case. Attributes found so far are ~NS and ~NS."
	       target-class symbolic-value
	       (get-slot-description-of-class-description
		 desired-unique-attribute? target-description
		 desired-unique-class?)
	       target-description
	       (get-slot-description-of-class-description
		 attribute target-description class)
	       target-description))))
	(t
	 (setq desired-unique-attribute? attribute)
	 (setq slot-description
	       (get-slot-description-of-class-description
		 desired-unique-attribute? target-description
		 class))
	 (when (slot-name-needs-qualification-p
		 slot-description target-description)
	   (setq desired-unique-class? class)))))
	finally (return (values desired-unique-attribute?
				desired-unique-class?
				nil))))

(def-substitution-macro implied-attribute-of-class-throwing-errors
    (target-class symbolic-value top-of-stack)
  (multiple-value-bind (attribute? class? error?)
      (implied-attribute-of-class? target-class symbolic-value)
    (if error?
	(write-stack-error top-of-stack
	  (twrite-string error?)
	  (reclaim-text-string error?))
	(values attribute? class?))))



;;; The function `get-implied-attribute-place' is a function that attempts to
;;; locate an implied attribute that is a place (i.e., a variable or parameter).
;;; This is based on code in place-evaluate.  If no implied place attribute is
;;; found, the original item is returned, even though it has not been verified to
;;; be a valid place.

;;; added support for attribute-class? (multiple-inheritance) -rdf, 2/17/94

(defun-simple get-implied-attribute-place (item symbolic-value top-of-stack)
  (let* ((class (class item))
	 (attribute-class? nil)
	 (attribute? nil)
	 (implied-place? nil))
    (multiple-value-setq (attribute? attribute-class?)
      (implied-attribute-of-class-throwing-errors
	class symbolic-value top-of-stack))
    (cond (attribute?
	   (setq implied-place? (get-slot-value item attribute? attribute-class?))
	   (if (and (of-class-p implied-place? 'variable-or-parameter)
		    (active-p implied-place?))
	       implied-place?
	       item))
	  (t item))))

(defun-simple get-implied-attribute-place-or-error-description
    (item symbolic-value)
  (let* ((class (class item)))
    (multiple-value-bind (attribute? attribute-class? error?)
	(implied-attribute-of-class? class symbolic-value)
      (cond (error? error?)
	    (attribute?
	     (let ((implied-place?
		     (get-slot-value item attribute? attribute-class?)))
	       (if (and (of-class-p implied-place? 'variable-or-parameter)
			(active-p implied-place?))
		   implied-place?
		   item)))
	    (t item)))))



;;;; Mutators

(defun-simple mutate-denoted-item-part
    (item denotation index new-value)
  (let ((reason-not-editable? (reason-permanent-items-module-is-not-editable item)))
    (when reason-not-editable?
      (return-from mutate-denoted-item-part
	(access-error
	  'item-not-editable-conclude-error
	  'item (tformat-text-string "~NA" item)
	  'message (tformat-text-string "Cannot edit ~NF, because ~A.  See the saving-parameters."
					item reason-not-editable?)))))
  (let ((denotation-code (svref denotation index)))
    (denotation-code-case denotation-code
      (attribute
	#+development
	(unless current-conclude-innermost-attribute-description
	  (error "joe screwed up"))
	(cond
	  ((slot-description-p
	     current-conclude-innermost-attribute-description)
	   (let ((slot-description
		    current-conclude-innermost-attribute-description))
	     (cond
	       ((user-defined-slot-description-p slot-description)
		;; are all structs and sequences in slots ref-count == 1
		;; how do we fan these changes out other slots
		(mutate-user-attribute
		  item slot-description denotation index new-value))
	       (t
		(mutate-system-attribute
		  item slot-description denotation index new-value)))))
	  (t
	   (let* ((virtual-attribute
		    current-conclude-innermost-attribute-description))
	     (mutate-virtual-attribute
	       item virtual-attribute denotation index new-value)))))
      (aliased-attribute
	#+development
	(error "NYI"))
      (element
	(error "NYI"))
      (virtual-attribute
	(let* ((virtual-attribute
		 current-conclude-innermost-attribute-description))
	  (mutate-virtual-attribute
	    item virtual-attribute denotation index new-value)))
      (variable-value
	(mutate-variable-value
	  item denotation index new-value)))))

(defmacro typecheck-and-cast-conclude-value (type-spec-exp value-exp)
  (let ((type-specification (gensym))
	(value (gensym)))
    `(let ((,type-specification ,type-spec-exp)
	   (,value ,value-exp))
       (cond ((and (eq ,type-specification 'float)
		   (fixnump ,value))
	      (prog1
		  (make-evaluation-float
		    (coerce-fixnum-to-gensym-float
		      (evaluation-integer-value ,value)))
		(reclaim-evaluation-integer ,value)))
	     ((type-specification-type-p ,value ,type-specification)
	      ,value) ; fix truth-values here
	     (t
	      (access-error 'type-mismatch))))))
	      
(defun-simple mutate-virtual-attribute
    (item virtual-attribute denotation index new-value)
  (let ((end-index (denotation-end-index denotation))
	(type-specification
	  (virtual-attribute-value-type virtual-attribute)))
    (cond
      ((=f end-index index)
       (let ((value-to-conclude?
	       (typecheck-and-cast-conclude-value type-specification new-value)))
	 (cond
	   ((access-error-p value-to-conclude?)
	    ;(reclaim-access-error value-to-conclude?)
	    (access-error
	      'type-mismatch
	      'attribute (virtual-attribute-name virtual-attribute)
	      'value (tformat-text-string "~NA" new-value)))
	   (t ;value-to-conclude?
	    (set-virtual-attribute
	      item (virtual-attribute-name virtual-attribute)
	      virtual-attribute value-to-conclude?)))))
      (t
       (let ((evaluation-value
	       (get-virtual-attribute item virtual-attribute)))
	 (cond
	   ((aggregate-evaluation-value-p evaluation-value)
	    (let ((replaced-partial-evaluation-value-or-error		
		    (substitute-denoted-evaluation-value-part
		      evaluation-value denotation
		      (denotation-next-index-macro
			denotation index) ; we already used the v-a
		      end-index new-value t)))
	      (cond
		((access-error-p replaced-partial-evaluation-value-or-error)
		 replaced-partial-evaluation-value-or-error)
		(t
		 (reclaim-if-evaluation-value
		   replaced-partial-evaluation-value-or-error)
		 ;; the following type-check must be done on the whole,
		 ;; modified value, i.e. the var evaluation-value
		 (cond ((type-specification-type-p
			  evaluation-value type-specification)
			(set-virtual-attribute
			  item (virtual-attribute-name virtual-attribute)
			  virtual-attribute evaluation-value))
		       (t
			(access-error
			  'type-mismatch
			  'attribute (virtual-attribute-name virtual-attribute)
			  'value (tformat-text-string "~NA" evaluation-value))))))))
	   (t
	    (prog1
		(access-error
		  'expecting-structure-or-sequence-inside-attribute
		  'value (tformat-text-string "~NA" evaluation-value))
	      (reclaim-if-evaluation-value
		evaluation-value)))))))))

(defun-simple set-system-attribute-evaluation-value
    (item slot-description new-value)
  (let* ((evaluator-info
	   (get-slot-description-evaluator-info slot-description))
	 (parse-result-maker
	   (evaluator-slot-info-category-setter evaluator-info)))
    (with-attribute-export-conclude-context
	item
      (multiple-value-bind (parse-result-or-bad-phrase error-string?)
	  (funcall-simple-multi-valued-compiled-function
	    parse-result-maker
	    new-value item slot-description nil)
	(cond
	  ((eq parse-result-or-bad-phrase bad-phrase)
	   error-string?)
	  (t
	   ;; returns new-error-string or nil
	   (simple-commit-parse-result
	     item
	     (pretty-slot-name slot-description)
	     (if (slot-name-needs-qualification-p
		   slot-description (class-description-slot item))
		 (defining-class slot-description)
		 nil)
	     slot-description nil nil
	     (evaluator-slot-info-category evaluator-info)
	     (evaluator-slot-info-text-slot-p evaluator-info)
	     parse-result-or-bad-phrase nil
	     new-value)))))))
  
(defun mutate-system-attribute (item slot-description denotation index new-value)
  (let ((end-index (denotation-end-index denotation)))
    (cond
      ((=f end-index index)
       (let ((error-string?
	       (set-system-attribute-evaluation-value
		 item slot-description new-value)))
	 (cond
	   (error-string?
	    (access-error
	      'system-attribute-conclude-error
	      'item (tformat-text-string "~NA" item)
	      'name (pretty-slot-name slot-description)
	      'value (tformat-text-string "~NA" new-value)
	      'message error-string?))
	   (t
	    nil))))
      (t
       (let ((evaluation-value
	       (get-attribute-description-evaluation-value
		 item slot-description)))
	 (cond
	   ((aggregate-evaluation-value-p evaluation-value)
	    (let ((replaced-partial-evaluation-value-or-error		
		    (substitute-denoted-evaluation-value-part
		      evaluation-value denotation
		      (denotation-next-index-macro
			denotation index) ; we already used the slot-desc
		      end-index new-value t)))
	      (cond
		((access-error-p replaced-partial-evaluation-value-or-error)
		 replaced-partial-evaluation-value-or-error)
		(t
		 (reclaim-if-evaluation-value
		   replaced-partial-evaluation-value-or-error)
		 ;; the following type-check must be done on the whole,
		 ;; modified value, i.e. the var evaluation-value
		 (let ((error-string?
			 (set-system-attribute-evaluation-value
			   item slot-description evaluation-value)))
		   (cond
		     (error-string?
		      (access-error
			'system-attribute-conclude-error
			'item (tformat-text-string "~NA" item)
			'name (pretty-slot-name slot-description)
			'value (tformat-text-string "~NA" new-value)))
		     (t
		      nil)))))))
	   (t
	    (prog1
		(access-error
		  'expecting-structure-or-sequence-inside-attribute
		  'value (tformat-text-string "~NA" evaluation-value))
	      (reclaim-if-evaluation-value
		evaluation-value)))))))))
  
(defun-simple mutate-user-attribute
    (item slot-description denotation index new-value)
  (let ((end-index (denotation-end-index denotation)))
    (cond
      ((=f end-index index)
       (let ((value-to-conclude?
	       (typecheck-and-cast-conclude-value
		 (slot-type-specification slot-description)
		 new-value)))
	 (cond
	   ((access-error-p value-to-conclude?)
	    ;(reclaim-access-error value-to-conclude?)
	    (access-error
	      'type-mismatch
	      'item (tformat-text-string "~NA" item)
	      'name (pretty-slot-name slot-description)
	      'value (tformat-text-string "~NA" new-value)))
	   (t ;value-to-conclude?
	    (cond ((evaluation-truth-value-p value-to-conclude?)
		   (change-slot-description-value
		     item slot-description
		     (slot-value-list
		       (evaluation-truth-value-value value-to-conclude?)
		       'truth-value))
		   (reclaim-evaluation-truth-value value-to-conclude?))
		  (t
		   (change-slot-description-value
		     item slot-description value-to-conclude?)))))))
      (t
       (let ((type-specification
	       (slot-type-specification slot-description)))
	 (cond
	   ((symbolp type-specification)
	    (cond
	      ((symbolic-type-specification-subtype-p
		 type-specification 'datum)
	       (access-error 'type-mismatch
		  'item (tformat-text-string "~NA" item)
		  'name (pretty-slot-name slot-description)
		  'value (tformat-text-string "~NA" new-value)))
	      (t
	       (error "unknown type-specification for user attribute conclude ~s"
		      type-specification))))
	   (t
	    #+development
	    (unless (consp type-specification)
	      (error "malformed type-specification for conclude ~s" type-specification))
	    (let ((type-details (cdr-of-cons type-specification)))
	      (case (car-of-cons type-specification)
		(or
		 (unless (and (eq (car-of-cons type-details) 'item-or-datum)
			      (equal (cadr type-details) '(no-item)))
		   (error "unknown type-specification for user attribute conclude ~s"
			  type-specification))
		 ;; conclude deeply
		 )
		((structure sequence)
		 ;; conclude deep
		 )
		(otherwise
		 (error "unknown type-specification for user attribute conclude ~s"
			type-specification)))
	      (let ((evaluation-value
		      (get-slot-description-value item slot-description)))
	        (multiple-value-bind
		    (replaced-partial-evaluation-value-or-error new-whole-value)
		    (substitute-denoted-evaluation-value-part
		      evaluation-value denotation
		      (denotation-next-index-macro
			denotation index) ; we already used the slot-desc
		      end-index new-value nil)
;		  (format t "eval-val= ~s replaced-part=~s new-whole-~s~%"
;			  evaluation-value
;			  replaced-partial-evaluation-value-or-error new-whole-value)
;		  (break)
		  (cond
		    ((access-error-p replaced-partial-evaluation-value-or-error)
		     replaced-partial-evaluation-value-or-error)
		    (t
		     (reclaim-if-evaluation-value
		       replaced-partial-evaluation-value-or-error)
		     (change-slot-description-value
		       item slot-description
		       ;; copy it to bump up ref count to 2 before putter
		       ;; which will reclaim (i.e. bust it down to 1)
		       (copy-evaluation-value new-whole-value))
		     ))))))))))))

(defmacro element-denotation-index (d i)
  `(svref ,d (+f ,i 2)))


(defun substitute-denoted-evaluation-value-part
    (evaluation-value denotation index end-index part
		      unique-p)
  #+development
  (when (>f index end-index)
    (error "hey bonehead"))
  (loop with root = evaluation-value
	with first-root = nil
	with previous-root-is-structure-p = nil
	with previous-root = nil
	with previous-key = nil
	with next-root = nil
	for next-index = (denotation-next-index-macro denotation index)
	as code = (svref denotation index)
	do
    (denotation-code-case code
      (attribute
	(unless (evaluation-structure-p root)
	  (return
	    (access-error
	      'expecting-structure-inside-attribute
	      'value (tformat-text-string "~NA" root))))
	(unless unique-p
	  (let ((mutable-p (mutable-evaluation-structure-p root)))
	    (unless mutable-p
	      (setf root
		    (make-unique-evaluation-structure-copy root)))
	    (cond (first-root
		   (unless mutable-p
		     (cond (previous-root-is-structure-p
			    (setf (evaluation-structure-slot previous-root previous-key)
				  root))
			   (t
			    (setf (evaluation-sequence-ref previous-root previous-key)
				  root)))))
		  (t
		   (setf first-root root)))))
	(let ((attribute-name
		(attribute-denotation-name denotation index)))
	  (setf next-root
		(evaluation-structure-slot root attribute-name))
	  (cond ((=f index end-index)
		 (setf (evaluation-structure-slot root attribute-name)
		       part)
		 (return (values next-root first-root)))
		(t
		 (setf index next-index)
		 (unless unique-p
		   (setf previous-root root)
		   (setf previous-key attribute-name)
		   (setf previous-root-is-structure-p t))
		 (setf root next-root)))))
      (element
	(unless (evaluation-sequence-p root)
	  (return
	    (access-error
	      'expecting-sequence-inside-attribute
	      'value (tformat-text-string "~NA" root))))
	(unless unique-p
	  (let ((mutable-p (mutable-evaluation-sequence-p evaluation-value)))
	    (unless mutable-p
	      (setf root (allocate-new-evaluation-sequence-copy root)))
	    (cond (first-root
		   (unless mutable-p
		     (cond (previous-root-is-structure-p
			    (setf (evaluation-structure-slot previous-root previous-key)
				  root))
			   (t
			    (setf (evaluation-sequence-ref previous-root previous-key)
				  root)))))
		  (t
		   (setf first-root root)))))
	(let ((elt-index (element-denotation-index denotation index)))
	  (setf next-root
		(evaluation-sequence-aref root elt-index))
	  (cond ((=f index end-index)
		 (setf (evaluation-sequence-ref root elt-index)
		       part)
		 (return (values next-root first-root)))
		(t
		 (setf index next-index)
		 (unless unique-p
		   (setf previous-root root)
		   (setf previous-key elt-index)
		   (setf previous-root-is-structure-p nil))
		 (setf root next-root))))))))  

(defun mutate-variable-value (item denotation index new-value)
  (declare (ignore denotation index))
  (cond
    ((and (null new-value)
	  (frame-of-class-p item 'parameter))
     (access-error
       'conclude-no-value-into-parameter
       'parameter (tformat "~NF" item)))
    ((null new-value)
     (put-has-no-value item))
    (t
     #+development
     (format t "ignoring expirations and collections on ~s~%" item)
     (let ((problem-description?
	     (put-current-evaluation-value
	       item new-value
	       (or nil ; user-provided-expiration?
		   stack-expiration)
	       nil ; user-provided-collection?
	       (not (null nil))))) ; user-provided-expiration?)))))
       (cond
	 (problem-description?
	  (access-error
	    'conclude-into-variable-error
	    'explanation problem-description?))
	 (t
	  nil))))))

#+unused
(defun mutate-array-or-list-element (item denotation index new-value)
  (declare (ignore item denotation index new-value))
  nil)





;;;; Convenience Functions for making denotations



(defvar scratch-attribute-denotation nil)

(defun-simple make-attribute-denotation (slot-name class-qualifier? permanent-p)
  (let* ((length #.(denotation-type-size 'attribute))
	 (denotation
	   (if permanent-p
	       (allocate-managed-simple-vector length)
	       (or scratch-attribute-denotation
		   (setf scratch-attribute-denotation
			 (allocate-managed-simple-vector length))))))
    (fill-simple-vector
      (denotation 0)
      #.(denotation-type-code 'attribute)
      'attribute
      slot-name
      class-qualifier?)
    denotation))

(defvar scratch-virtual-attribute-denotation nil)

(defun-simple make-virtual-attribute-denotation (virtual-attribute
						  permanent-p)
  (let* ((length #.(denotation-type-size 'virtual-attribute))
	 (denotation
	   (if permanent-p
	       (allocate-managed-simple-vector length)
	       (or scratch-virtual-attribute-denotation
		   (setf scratch-virtual-attribute-denotation
			 (allocate-managed-simple-vector length))))))
    (fill-simple-vector
      (denotation 0)
      #.(denotation-type-code 'virtual-attribute)
      'virtual-attribute
      (virtual-attribute-name virtual-attribute))
    denotation))

(defvar scratch-variable-value-denotation nil)

(defun-simple make-variable-value-denotation (permanent-p)
  (let* ((length #.(denotation-type-size 'variable-value))
	 (denotation
	   (if permanent-p
	       (allocate-managed-simple-vector length)
	       (or scratch-variable-value-denotation
		   (setf scratch-variable-value-denotation
			 (allocate-managed-simple-vector length))))))
    (fill-simple-vector
      (denotation 0)
      #.(denotation-type-code 'variable-value)
      'variable-value)
    denotation))

(defvar scratch-item-color-pattern-change-denotation nil)

(defun-simple make-item-color-pattern-change-denotation ()
  (let* ((length #.(denotation-type-size 'item-color-pattern-change))
	 (denotation (or scratch-item-color-pattern-change-denotation
			 (setf scratch-item-color-pattern-change-denotation
			       (allocate-managed-simple-vector length)))))
    (fill-simple-vector
      (denotation 0)
      #.(denotation-type-code 'item-color-pattern-change)
      'item-color-pattern-change)
    denotation))

(defvar scratch-custom-event-denotation nil)

(defun-simple make-custom-event-denotation (event-name)
  (let* ((length #.(denotation-type-size 'custom-event))
	 (denotation (or scratch-custom-event-denotation
			 (setf scratch-custom-event-denotation
			       (allocate-managed-simple-vector length)))))
    (fill-simple-vector
      (denotation 0)
      #.(denotation-type-code 'custom-event)
      'custom-event
      event-name)
    denotation))

(defvar scratch-item-event-denotation nil)

(defun-simple make-item-event-denotation (event-name)
  (let* ((length #.(denotation-type-size 'item-event))
	 (denotation (or scratch-item-event-denotation
			 (setf scratch-item-event-denotation
			       (allocate-managed-simple-vector length)))))
    (fill-simple-vector
      (denotation 0)
      #.(denotation-type-code 'item-event)
      'item-event
      event-name)
    denotation))

(defvar scratch-add-item-to-workspace nil)

(defun-simple make-add-item-to-workspace-denotation ()
  (let* ((length #.(denotation-type-size 'add-item-to-workspace))
	 (denotation (or scratch-add-item-to-workspace
			 (setf scratch-add-item-to-workspace
			       (allocate-managed-simple-vector length)))))
    (fill-simple-vector
      (denotation 0)
      #.(denotation-type-code 'add-item-to-workspace)
      'add-item-to-workspace)
    denotation))

(defvar scratch-remove-item-from-workspace nil)

(defun-simple make-remove-item-from-workspace-denotation ()
  (let* ((length #.(denotation-type-size 'remove-item-from-workspace))
	 (denotation (or scratch-remove-item-from-workspace
			 (setf scratch-remove-item-from-workspace
			       (allocate-managed-simple-vector length)))))
    (fill-simple-vector
      (denotation 0)
      #.(denotation-type-code 'remove-item-from-workspace)
      'remove-item-from-workspace)
    denotation))

;;;; Dev tools


#+development
(defvar all-class-descriptions nil)

#+development
(defun gather-class-descriptions (class-name)
  (pushnew (class-description class-name) all-class-descriptions)
  (loop for subclass-name in (inferior-classes class-name)
	do
    (gather-class-descriptions subclass-name)))

#+development
(defun report-uses-of-category (category-name)
  (loop for class-description in all-class-descriptions
	do
    (report-uses-of-category-for-slot-names
      category-name class-description
      (slots-local-to-class class-description))
    (report-uses-of-category-for-slot-names
      category-name class-description
      (inherited-slots-this-class-overrides class-description))))

#+development
(defun report-uses-of-category-for-slot-names (category-name class-description unique-names)
  (loop for slot-name in unique-names
	as slot-description
	   = (get-slot-description-of-class-description
	       slot-name class-description)
	as type? = (feature-assq
		     'type (slot-features slot-description))
	as category? = (and type?
			    (category-symbol-given-slot-type type?))
	as editable-p = (not (feature-assq 'not-user-editable
					   (slot-features slot-description)))
	when (eq category? category-name)
	  do
	    (format t "~s::~s ~50T alias=~s ~70Tedit?=~s~%"
		    (class-name-of-class-description class-description)
		    (pretty-slot-name slot-description)
		    (get-alias-for-slot-name-if-any
		      (pretty-slot-name slot-description)
		      (class-name-of-class-description class-description))
		    editable-p)))


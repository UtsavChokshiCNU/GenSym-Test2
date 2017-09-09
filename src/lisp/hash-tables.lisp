; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module HASH-TABLES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andy Latto

;;; User level hash tables.

(def-hash-table user-hash-table-internal
    :hash-function-or-macro user-hash-function
    :key-comparitor user-hash-comparitor
    :key-reclaimer reclaim-user-hash-table-key
    :entry-reclaimer reclaim-user-hash-table-entry)

;;; We use "stand-ins" for items in user hash tables. These are
;;; basically the uuid's, but we wrap and mark them, so that we
;;; can distinguish them from the case where the user is actually
;;; explicitly putting an item-reference in the hash-table.

(defconstant stand-in-marker (gensym-cons 'user-hash-table-stand-in nil))

(defun wrapped-item-p (thing)
  (and (consp thing) (eq (car thing) stand-in-marker)))

;;; Use this for any key or value going into a user-hash-table.
(defun wrap-or-copy-for-user-hash-table (thing)
  (cond
    ((framep thing)
     (slot-value-cons stand-in-marker
		      (get-reference-to-item thing)))
    ((evaluation-value-p thing)
     (copy-evaluation-value thing))
    (t thing)))

;;; Use this for any returned value coming out of a user-hash-table.
;;; A returned value of nil here means that it was a reference to
;;; an item that has since been deleted, and nil should be returned.
(defun unwrap-or-copy-for-user-hash-table (thing)
  (cond
    ((wrapped-item-p thing)
     (evaluation-item-reference-referenced-item (cdr thing)))
    ((evaluation-value-p thing)
     (copy-evaluation-value thing))
    (t thing)))


;;; Item references are reference counted, and never copied, so
;;; we can use the address as the hash code, since we never relocate
;;; objects. This doesn't work in development, though, where the
;;; GC can relocate the object. So we assign a hash value to
;;; each object the first time it is called for, and use a Lucid hash
;;; table to keep track of these hash values. The hash values in this
;;; table are reference counted, so that things don't stay in
;;; this hash table forever.
;;; So this reference count has to be decremented every time we
;;; compute the hash value of an object. This is handled by
;;; reclaim-user-hash-table-key, as long as each key has the hash
;;; function called only once.
;;; See the comments at eq item hash tables
;;; in utilities3, which shares this hash table, for more details.
(defun user-hash-function (thing)
  (cond
    ((wide-string-p thing)
     (hash-wide-string thing))
    ((evaluation-integer-p thing)
     (absf (evaluation-integer-value thing)))
    ((evaluation-float-p thing)
     (with-temporary-gensym-float-creation user-hash-function
       ;; GENSYMCID-1555: Negative float hash-table key crashes G2
       ;; Use ABSF to fix negative values; use FLOORE-FIRST instead of FLOOR
       ;; for better performance. -- Chun Tian (binghe), Jan 5 2016.
       (absf (floore-first (evaluation-float-value thing)))))
    ((evaluation-item-reference-p thing)
     #-development
     (sxhash-symbol thing)
     #+development
     (eqhash thing))
    ;; Could add more clauses for other evaluation-values here,
    ;; to make them more efficient. But items and strings are by
    ;; far the most common case.
    ((wrapped-item-p thing)
     #-development
     (sxhash-symbol (cdr thing))
     #+development
     (eqhash (cdr thing)))
    ((evaluation-value-p thing) 0)
    (t 0)))

(defun user-hash-comparitor (thing1 thing2)
  (cond ((and (wide-string-p thing1) (wide-string-p thing2))
	 (string=w thing1 thing2))
	((and (evaluation-value-p thing1) (evaluation-value-p thing2))
	 (evaluation-value-= thing1 thing2))
	((and (wrapped-item-p thing1) (wrapped-item-p thing2))
	 ;; since we use the actual uuid from the slot, we can
	 ;; use eq here.
	 (eq (cdr thing1) (cdr thing2)))
	(t nil)))

(defun reclaim-user-hash-table-key (key)
  (cond
    ((wrapped-item-p key)
     #+development
     (decf-eqhash-reference-count (cdr key))
     (reclaim-evaluation-value (cdr key))
     (reclaim-slot-value-cons key))
    (t
     #+development
     (when (evaluation-item-reference-p key)
       (decf-eqhash-reference-count key))
     (reclaim-if-evaluation-value key))))

(defun reclaim-user-hash-table-entry (key)
  (cond
    ((wrapped-item-p key)
     (reclaim-evaluation-value (cdr key))
     (reclaim-slot-value-cons key))
    (t (reclaim-if-evaluation-value key))))

;;; Returns two values. The first returned value is the value
;;; associated with the given key in the hash table, nor nil if
;;; none. The second value is t in the case where the given key
;;; was associated with an item-reference to an item which has been
;;; deleted; When this condition is detected, user-hash-table-gethash
;;; removes this key-value pair from the table, so that it doesn't
;;; leak an item reference, and the user of user-hash-table-gethash
;;; needs to know about this so it can update current-number-of-entries.

(defun user-hash-table-gethash (table key)
  (let* ((internal-key
	   (wrap-or-copy-for-user-hash-table key))
	 (result-reference
	  (get-user-hash-table-internal
	    internal-key
	    table)))
    (multiple-value-prog1
	(if result-reference
	    (or (unwrap-or-copy-for-user-hash-table result-reference)
		(progn
		  (delete-user-hash-table-internal internal-key table)
		  (values nil t)))
	    (values nil nil))
      (reclaim-user-hash-table-key internal-key))))

;;; Need to look at this; do we need to decf the reference
;;; count? No; hash table internals handle this by reclaiming the
;;; key as appropriate.

;;; returns t if this is a new key, nil if object was already in table.
(defun user-hash-table-sethash (table key value)
  (let* ((wrapped-key
	   (wrap-or-copy-for-user-hash-table key))
	 (wrapped-value
	   (wrap-or-copy-for-user-hash-table value))
	 (old-value
	   (user-hash-table-gethash table key)))
  (setf (get-user-hash-table-internal wrapped-key table)
	wrapped-value)
  (not old-value)))

(def-class (hash-table object (foundation-class hash-table) define-predicate
		       (class-export-comment
			 "hash tables provide a way to associate keys with values with fast lookup"))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-outline . foreground)
		   (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (text-region . foreground))
       (variables)
       (background-layer)
       g2-icon-background (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
					     ((0 0) (50 0) (47 3))
					     ((3 3) (3 47) (0 50))
					     ((0 0) (47 3) (3 3))
					     ((3 3) (0 50) (0 0)))
       (lines (5 45) (44 45) (44 5))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50)) ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50)) ((50 50) (3 47) (47 47)))
       g2-icon-outline (outline (0 0) (0 50) (50 50) (50 0))
       g2-icon-outline (lines (44 5) (5 5) (5 45))
       ;; Put text that looks like this in the icon:  (H-T, for Hash-Table)
       ;;   H
       ;;    -
       ;;     T
       text-region (text #w"H" ( 8 21) large)
       text-region (text #w"-" (22 32) large)
       text-region (text #w"T" (30 43) large))
      nil nil nil nil nil
      ((g2-icon-outline 27 26 43 42)
       (g2-icon-background 0 0 50 50)
       (g2-icon-light-shading 0 0 50 50)
       (g2-icon-dark-shading 0 0 50 50)
       (g2-icon-outline 0 0 50 50)
       (text-region 8 6 20 26))))
  (internal-hash-table (:funcall make-user-hash-table-internal) vector-slot system
		       not-user-editable do-not-save)
  ;(case-sensitive t vector-slot system save (type yes-or-no))
  (current-number-of-entries 0 vector-slot system)
  ;(initial-values nil vector-slot system save (type sequence))
  )

(def-class-method deactivate (hash-table)
  (clear-user-hash-table-internal (internal-hash-table hash-table))
  (setf (current-number-of-entries hash-table) 0))

(def-class-method activate (hash-table)
  (initialize-hash-table-from-initial-values-attribute hash-table))

;;; Put this version in once initial-values work.
#|
(defun initialize-hash-table-from-initial-values-attribute (hash-table)
  (let ((table (internal-hash-table hash-table))
	(initial-values-sequence (initial-values hash-table)))
    (if initial-values-sequence
      (let*
	  ((length (evaluation-sequence-length initial-values-sequence))
	   (rounded-length (if (evenp length) length (1-f length))))
	(loop for key-index from 0 below length by 2
	      do
	  (user-hash-table-sethash
	    table
	    (evaluation-sequence-aref initial-values-sequence key-index)
	    (evaluation-sequence-aref initial-values-sequence (1+f key-index))))
	(setf (current-number-of-entries hash-table) (/ rounded-length 2)))
      (setf (current-number-of-entries hash-table) 0))))
|#

(defun initialize-hash-table-from-initial-values-attribute (hash-table)
  (declare (ignorable hash-table))
  ;; GENSYMCID-1186: Warmboot hash-table content is lost and G2 aborts during warmboot
  ;; This function could be called after the ICP read, in which intial contents
  ;; were set up by using the setter of `g2-hash-table-sequence'. Reset the
  ;; `current-number-of-entries' is simply wrong. -- Chun Tian (binghe), 1/21/14
  #+ignore
  (setf (current-number-of-entries hash-table) 0))

(def-slot-value-reclaimer internal-hash-table (value frame)
  (reclaim-user-hash-table-internal value)
  (setf (internal-hash-table frame) nil))

(defun-for-system-procedure g2-hash-table-set-value
    (table key value)
  (when
      (user-hash-table-sethash (internal-hash-table table)
			       key
			       value)
    (incff (current-number-of-entries table)))
  (reclaim-if-evaluation-value key)
  (reclaim-if-evaluation-value value))

(defun-for-system-procedure g2-hash-table-get-value (table key)
  (multiple-value-bind (result deleted-item-found)
      (user-hash-table-gethash (internal-hash-table table) key)
    (when deleted-item-found
      (decff (current-number-of-entries table)))
    (reclaim-if-evaluation-value key)
    (if result
	(values result
		(make-evaluation-boolean-value t))
	(values (make-evaluation-boolean-value nil)
		(make-evaluation-boolean-value nil)))))

(defun-for-system-procedure g2-hash-table-clear-value (table key)
  (let* ((wrapped-key (wrap-or-copy-for-user-hash-table key))
	 (key-exists (get-user-hash-table-internal
		       wrapped-key
		       (internal-hash-table table))))
    (delete-user-hash-table-internal wrapped-key (internal-hash-table table))
    (when key-exists
      (decff (current-number-of-entries table)))
    ;; We hash on the wrapped key twice, once for the get and once
    ;; for the delete. So we need to decrement the reference count
    ;; for the hash value twice, and reclaim-wrapped-thing only does it
    ;; once. So we have to do it manually.
    #+development
    (cond
      ((wrapped-item-p wrapped-key)
       (decf-eqhash-reference-count (cdr wrapped-key)))
      ((evaluation-item-reference-p key)
       (decf-eqhash-reference-count key)))
    (reclaim-user-hash-table-key wrapped-key)
    (reclaim-if-evaluation-value key)))

(defun-for-system-procedure g2-hash-table-clear (table)
  (clear-user-hash-table-internal (internal-hash-table table))
  (setf (current-number-of-entries table) 0))

(defun-for-system-procedure g2-hash-table-reset (table)
  (clear-user-hash-table-internal (internal-hash-table table))
  (initialize-hash-table-from-initial-values-attribute table))

(defmacro reclaim-flattened-table (flattened-table)
  `(loop for key-or-val in ,flattened-table
        do (reclaim-if-evaluation-value key-or-val)
        finally (reclaim-eval-list ,flattened-table)))

(def-virtual-attribute g2-hash-table-number-of-entries
    ((class hash-table)
     integer
     (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial ((class) (declare (ignore class)) 0)
  :getter ((hash-table)
	   (let* ((flattened-table
		    (flatten-user-hash-table
		      (internal-hash-table hash-table)))
		  (result (halff (length flattened-table))))
	     (reclaim-flattened-table flattened-table)
	     result)))

;; returns a sequence of 2-element-structures.
(def-virtual-attribute g2-hash-table-sequence
    ((class hash-table)
     ;; inactive hash tables, and eventually permanent tables that have
     ;; not been initialized 
     ;; return no-item (aka nil)
     (or (no-item) (sequence))
     ;; I don't quite understand what this does, but I'm being consistent
     ;; with g2-array-sequence and g2-list-sequence -alatto, 6/3/04
     (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :setter ((hash-table new-value)
	   (let* ((table (internal-hash-table hash-table)))
	     (loop for element being each evaluation-sequence-element of new-value
		   as key = (evaluation-structure-slot element 'entry-key)
		   as value = (evaluation-structure-slot element 'entry-value)
		   do
	       (when (user-hash-table-sethash table key value)
		 ;; GENSYMCID-1186: Warmboot hash-table content is lost and G2 aborts
		 ;; during warmboot
		 ;; `current-number-of-entries' must be updated, it's used when saving
		 ;; runtime data into snapshot KB. -- Chun Tian (binghe), Jan 21, 2014
		 (incff (current-number-of-entries hash-table))))
	     nil))
  :getter  ((hash-table)
	    (if (active-p hash-table)
		(flatten-user-hash-table-into-sequence-of-structures
		  (internal-hash-table hash-table))
	      nil)))

(defun deleted-hash-table-entry-p (key-or-value)
  (and (wrapped-item-p key-or-value)
       (null (evaluation-item-reference-referenced-item (cdr key-or-value)))))

(defun flatten-user-hash-table (table)
  (let* ((keys-and-values (flatten-user-hash-table-internal table))
	 (pruned-list
	   (loop for key-cons on keys-and-values by 'cddr
		 unless (or (deleted-hash-table-entry-p (car key-cons))
			    (deleted-hash-table-entry-p (cadr key-cons)))
		   collect (unwrap-or-copy-for-user-hash-table (car key-cons))
		     using eval-cons
		   and
		   collect (unwrap-or-copy-for-user-hash-table (cadr key-cons))
		     using eval-cons)))
    (reclaim-eval-list keys-and-values)
    pruned-list))

(defun-simple flatten-user-hash-table-into-sequence-of-structures (table)
  (let* ((flattened-table
	  (flatten-user-hash-table table))
	 (result-list
	  (loop for key-value on flattened-table by 'cddr
		collect (allocate-evaluation-structure-inline
			  'entry-key
			  (unwrap-or-copy-for-user-hash-table (first key-value))
			  'entry-value
			  (unwrap-or-copy-for-user-hash-table (second key-value)))
		using eval-cons)))
    (reclaim-flattened-table flattened-table)
    (allocate-evaluation-sequence result-list)))

(defun-for-system-procedure g2-hash-table-to-sequence (table)
  (let ((keys-and-values (flatten-user-hash-table
			   (internal-hash-table table))))
    (allocate-evaluation-sequence keys-and-values)))

;;;
;;; Added by SoftServe
;;;
	
;;;copied from the virtual attribute definition
;;;returns key-value pairs for the given hash table	
(defun get-key/value-list (hash-table)
 (let* ((flattened-table
	(flatten-user-hash-table
	   (internal-hash-table hash-table)))
	   (result-list
	 (loop for key-cons on flattened-table by 'cddr
		   collect
		 (gensym-list 
		  (unwrap-or-copy-for-user-hash-table
		   (car key-cons))
		 (unwrap-or-copy-for-user-hash-table
		   (cadr key-cons)))
		   using gensym-cons)))
  (reclaim-flattened-table flattened-table)
	result-list))	

;;;writes the hash table runtime data into the current KB	
(defun write-hash-table-data-for-kb (table)
  (let ((data-seq (get-key/value-list table)))
    (write-left-bracket-if-necessary)
    (write-char-for-kb #\O)
    (write-fixnum-for-kb (current-number-of-entries table))
    (loop for (key val) in data-seq
	  do (write-element-for-kb key)
	     (write-element-for-kb val))))

;;;reads the hash table runtime data from the current KB		
(defun read-hash-table-data (table)
  (declare (ignore table))
  (loop with len = (read-element-for-kb nil)
	for i from 1 to len
	collect (gensym-list (read-element-for-kb nil)
			     (read-element-for-kb nil))
	using gensym-cons))

;;; installs runtime data into the given hash table  
(defun unsquirrel-hash-table-data (table data)
 (loop for key/value-pair in data do
  (g2-hash-table-set-value table (first key/value-pair)
                           (second key/value-pair))
  (reclaim-gensym-list key/value-pair))
  (reclaim-gensym-list data))
;end of SoftServe changes
						   

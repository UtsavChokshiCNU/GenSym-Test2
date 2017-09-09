;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module RINGS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann




;; To Do

;; Consider making some of the macros defined by define-ring-buffer be functions
;; instead.

;; (low priority)
;; Currently, get-or-make-smallest...  will always allocate a managed float array
;; if the type declared for the vector in define-ring-buffer is
;; possible-float-array (as is the case with the history-value-vector in history
;; ring buffers.  Thus, a managed float array will always be allocated initially,
;; even if it is a history for a non-numeric variable.  The managed float array
;; will then be replaced with a managed array when the first data point is stored.
;; This is not all that inefficient because the managed float array is empty when
;; switch-from-managed-float-array-to-managed-array is called.  However, consider
;; removing this minor inefficiency by passing a runtime argument to
;; get-or-make-smallest... specifying the desired type.

;; (low priority)
;; The enlarge-x-ring-buffer macro defined by define-ring-buffer should check to
;; make sure that the maximum possible size is not being exceeded.  Currently,
;; this is being done by the expand functions which call the enlarge macro.  It
;; would be better, however, to put the check in the macro itself.



;;;; Ring Buffers

;;; Ring buffers are used to keep histories and also as plot data buffers for
;;; graphs.  There may eventually be additional uses for these so a general ring
;;; buffer facility is provided here.

;;; Macros defined by define-ring-buffer are used in the following modules:
;;;   rings
;;;   histories
;;;   graphs1
;;;   graphs2
;;;   gfi
;;;   g2ds



;;;; Ring Buffer Vectors

;;; Ring buffer vectors are used in ring buffers to hold data.  A ring buffer
;;; can have any number of parallel vectors of this type.  The vectors are
;;; managed arrays.  Thus, memory utilization is at least 75% (see documentation
;;; for managed arrays.  Enlarging ring buffers is done via  
;;; adjust-managed-array which enlarges a managed array without creating
;;; any temporary floats.  Thus, there should not be any problem with 
;;; overflowing temporary areas when ring buffers are enlarged.

(defparameter smallest-ring-buffer-vector-size 
	      (minf 16 maximum-managed-array-size))

	;modified by SoftServe
(defparameter largest-ring-buffer-vector-size (* maximum-managed-array-size 16))
	;end of SoftServe changes

(defmacro get-or-make-smallest-ring-buffer-vector (type)
  (if (eq type 'possible-float-array)
      `(allocate-managed-float-array smallest-ring-buffer-vector-size)
      `(allocate-managed-array smallest-ring-buffer-vector-size)))

(defmacro get-or-make-ring-buffer-vector (type size)
  (if (eq type 'possible-float-array)
      `(allocate-managed-float-array ,size)
      `(allocate-managed-array ,size)))

(defun reclaim-ring-buffer-vector (ring-buffer-vector)
  (cond 
    ((managed-array-p ring-buffer-vector)
     (loop for vector-index from 0 below (managed-array-length ring-buffer-vector)
	   do (reclaim-managed-number-or-value
		(managed-svref ring-buffer-vector vector-index)))
     (reclaim-managed-array ring-buffer-vector))
    (t
     (reclaim-managed-float-array ring-buffer-vector))))

(defun compute-next-larger-size-for-ring-buffer-vectors (current-size)
  (minf largest-ring-buffer-vector-size
	(if (<f current-size 1000)
	    (*f current-size 2)
	    (+f current-size 1024))))

;; Rather than always doubling the size, it is better to cap the increase at
;; something like 1000 so that enlarging ring buffers does not have to become
;; suspendable.  The increase is made to be 1024 for maximal memory utilization.



;;;; Ring Buffer Parameters

;;; Ring buffer parameters are common to all ring buffers.

(def-structure (ring-buffer-state
		 (:constructor
		   make-ring-buffer-state))
  (newest-active-element-index 0)
  (oldest-active-element-index 0)
  (ring-buffer-empty? t)
  (ring-buffer-size 0)
  (ring-buffer-serial-number 0))

;; Ring-buffer-state is common to all ring buffers;  they all inherit this
;; structure.  There is some question about using the Common Lisp 
;; inheritance mechanism.  Consider implementing the slots specific to
;; each ring buffer type as sub-structures of a common structure for 
;; ring buffers.



(defmacro set-newest-active-element-index (ring-buffer value)
  `(setf (newest-active-element-index ,ring-buffer) ,value))

(defmacro set-oldest-active-element-index (ring-buffer value)
  `(setf (oldest-active-element-index ,ring-buffer) ,value))

(defmacro set-ring-buffer-empty? (ring-buffer value)
  `(setf (ring-buffer-empty? ,ring-buffer) ,value))

(defmacro set-ring-buffer-size (ring-buffer value)
  `(setf (ring-buffer-size ,ring-buffer) ,value))


;;;; Ring Buffer Definition

;;; Define-ring-buffer defines a def-structure for the ring buffer as well as
;;; various macros for creating, enlarging, accessing data in, and storing 
;;; data in the ring buffer.  Macros for moving pointers for the ring buffer
;;; are common to all ring buffers and thus are not defined specifically here.
;;; Note that all ring buffers use managed arrays for their vectors.

;;; Types can be specified for vectors of a ring buffer.  The parallel-vectors
;;; argument contains elements that are of the form
;;;   vector-name or (vector-name . type).
;;; Vector-name is used to generate the slot name for the vector in the ring
;;; buffer structure.  Type, if specified, can be 'fixnum-vector, or
;;; 'possible-float-array.  The types affect the way accessors are expanded (see
;;; get-ring-buffer-value and set-ring-buffer-value).  If type is not specified,
;;; managed arrays will be used and these accessors will expand to
;;; extract-number-or-value and store-managed-number-or-value.  If type is
;;; 'fixnum-vector, managed arrays will be used and the accessors will expand to
;;; managed-svref and setf.  If type is 'possible-float-array, managed float
;;; arrays will be used as long as possible (until a non-float is stored into the
;;; vector), at which time the managed float array is converted to a managed 
;;; array.  It is assumed here that the probability of receiving a non-float
;;; decreases with each float stored in the history.  Thus, it will be unlikely
;;; that a conversion of a large history buffer will have to be made.

;;; Note that history buffers are not reclaimed on deactivation.  They are
;;; reclaimed when the variable or parameter containing the history is deleted,
;;; or when the history specifications are edited to specify a maximum number of
;;; datapoints.  Therefore, once a managed float array is switched to a managed
;;; array, it stays a managed array, even after reset.  The assumption here (as
;;; mentioned above) is that [even] if a history gets only floating point values
;;; during one run, it is unlikely to get them in subsequent runs.

;;; Memory Efficiency Issues

;;; The type declared for a ring buffer vector can make a big difference in memory
;;; efficiency.  The memory requirements for number boxes for LUCID are as follows
;;; (assuming double floats):
;;;   LUCID
;;;     overhead - 2 words (8 bytes)
;;;     data     - 2 words (8 bytes)
;;;   IBUKI
;;;     overhead - 14 words (56 bytes)
;;;     data     - 2 words (8 bytes)

;;; Thus, if managed float arrays are not used, the memory required for a floating
;;; point value in a ring buffer vector (taking into account the 1 word array
;;; element in the array itself) is as follows:
;;;   LUCID  - 5 words (20 bytes)
;;;   IBUKI  - 17 words (68 bytes)
;;; For history buffers stored this way, the memory requirements for a floating 
;;; point data point (taking into account the 1 word array element for the
;;; time stamp vector) is as follows:
;;;   LUCID  - 6 words (24 bytes)
;;;   IBUKI  - 18 words (72 bytes)

;;; If managed float arrays are used, there is no number box and only 2 words (8
;;; bytes) are used (in the float array element itself), for both LUCID and IBUKI.
;;; Thus, the memory requirement for a floating point history data point is only
;;; 3 words (12 bytes), taking into account the 1 word array element for the
;;; time stamp vector.  Thus, only 1/2 as much memory is used for LUCID, and
;;; 1/6 as much for IBUKI.

;;; Further improvement could be attained if single floats were used.



(defmacro get-ring-buffer-value (vector index type)
  (case type
    (fixnum-vector
     `(managed-svref ,vector ,index))
    (possible-float-array
     (avoiding-variable-capture (vector)
       `(if (managed-array-p ,vector)
	    (extract-number-or-value
	      (managed-svref ,vector ,index))
	    ;; else, if managed float array
	    (managed-float-aref ,vector ,index))))
    (t   ; if type is nil
     `(extract-number-or-value
	(managed-svref ,vector ,index)))))

(defmacro get-ring-buffer-evaluation-value-non-float-array (vector index logicalp)
  `(let ((value (managed-svref ,vector ,index)))
     (if ,logicalp
	 (make-evaluation-truth-value value)
	 (copy-evaluation-value value))))

(defmacro get-ring-buffer-evaluation-value (vector index type logicalp)
  (case type
    (fixnum-vector
     `(get-ring-buffer-evaluation-value-non-float-array ,vector ,index ,logicalp))
    (possible-float-array
     (avoiding-variable-capture (vector)
       `(if (managed-array-p ,vector)
	    (get-ring-buffer-evaluation-value-non-float-array ,vector ,index ,logicalp)
	    ;; else, if managed float array
	    (make-evaluation-float (managed-float-aref ,vector ,index)))))
    (t   ; if type is nil
     `(get-ring-buffer-evaluation-value-non-float-array ,vector ,index ,logicalp))))

(defmacro mutate-managed-float-from-numeric-ring-buffer-value 
    (managed-float-box vector index)
  (avoiding-variable-capture (vector)    
    `(if (managed-array-p ,vector)
	 (let ((managed-number-or-value
		 (managed-svref ,vector ,index)))
	   (mutate-managed-float-value
	     ,managed-float-box
	     (if (managed-float-p managed-number-or-value)
		 (managed-float-value managed-number-or-value)
		 (coerce-fixnum-to-gensym-float managed-number-or-value))))
	 ;; else, if managed float array
	 (mutate-managed-float-value
	   ,managed-float-box
	   (managed-float-aref ,vector ,index)))))

;; Type is always possible-float-array here.



(defmacro switch-from-managed-float-array-to-managed-array 
	  (ring-buffer vector-slot-name vector)
  (avoiding-variable-capture (ring-buffer vector &aux new-managed-array)
    `(let* ((,new-managed-array
	      (allocate-managed-array (managed-float-array-length ,vector))))
       (when (not (ring-buffer-empty? ,ring-buffer))
	 (loop with element-index
		 = (oldest-active-element-index ,ring-buffer)
	       do (setf (managed-svref ,new-managed-array element-index)
			(allocate-managed-float
			  (managed-float-aref ,vector element-index)))
	       until (=f element-index
			 (newest-active-element-index ,ring-buffer))
	       do (setq element-index
			(increment-active-element-index
			  element-index ,ring-buffer))))
       (reclaim-managed-float-array ,vector)
       (setf (,vector-slot-name ,ring-buffer) ,new-managed-array))))

;; Vector-slot-name is assumed to always be a symbol.



(defmacro set-ring-buffer-value 
	  (vector index value type ring-buffer vector-slot-name)
  (case type
    (fixnum-vector
     `(setf (managed-svref ,vector ,index) ,value))
    (possible-float-array
     (avoiding-variable-capture (vector value ring-buffer)
       `(cond
	  ((managed-array-p ,vector)
	   (store-managed-number-or-value
	     (managed-svref ,vector ,index) ,value))
	  ((evaluation-float-p ,value)
	   (setf (managed-float-aref ,vector ,index) 
		 (evaluation-float-value ,value)))
	  ((gensym-float-p ,value)
	   (setf (managed-float-aref ,vector ,index) 
		 ,value))
	  (t
	   (switch-from-managed-float-array-to-managed-array
	     ,ring-buffer ,vector-slot-name ,vector)
	   (store-managed-number-or-value
	     (managed-svref
	       (,vector-slot-name ,ring-buffer)
	       ,index)
	     ,value)))))
    (t   ; if type is nil
     `(store-managed-number-or-value
	(managed-svref ,vector ,index) ,value))))

(defmacro set-ring-buffer-value-from-evaluation-value
	  (vector index value type ring-buffer vector-slot-name)
  `(set-ring-buffer-value ,vector ,index ,value ,type ,ring-buffer ,vector-slot-name))

(def-substitution-macro mutate-ring-buffer-element
			(vector index value)
  (let ((current-element (managed-svref vector index)))
    (if (managed-float-p current-element)
	(mutate-managed-float-value
	  current-element
	  (if (managed-float-p value)
	      (managed-float-value value)
	      (coerce-fixnum-to-gensym-float value)))
	(setf (managed-svref vector index)
	      (if (managed-float-p value)
		  (allocate-managed-float (managed-float-value value))
		  value)))))

(defmacro mutate-ring-buffer-value 
	  (vector index value type ring-buffer vector-slot-name)
  (case type
    (fixnum-vector
     `(setf (managed-svref ,vector ,index) ,value))
    (possible-float-array
     (avoiding-variable-capture (vector index value ring-buffer)
       `(if (managed-array-p ,vector)
	    (mutate-ring-buffer-element
	      ,vector ,index ,value)
	    ;; else, if managed float array
	    (cond
	      ((not (managed-float-p ,value))
	       (switch-from-managed-float-array-to-managed-array
		 ,ring-buffer ,vector-slot-name ,vector)
	       (mutate-ring-buffer-element
		 (,vector-slot-name ,ring-buffer)
		 ,index ,value))
	      (t
	       (mutate-managed-float-array
		 ,vector ,index
		 (managed-float-value ,value)))))))
    (t   ; if type is nil
     `(mutate-ring-buffer-element ,vector ,index ,value))))

(defun copy-ring-buffer-shell-slots (ring-buffer new-shell)
  (setf (newest-active-element-index new-shell)
	(newest-active-element-index ring-buffer))
  (setf (oldest-active-element-index new-shell)
	(oldest-active-element-index ring-buffer))
  (setf (ring-buffer-empty? new-shell)
	(ring-buffer-empty? ring-buffer))
  (setf (ring-buffer-size new-shell)
	(ring-buffer-size ring-buffer)))

(defun copy-ring-buffer-vector (vector)
  (cond ((managed-float-array-p vector)
	 (copy-managed-float-array vector))
	(t
	 ;; It's a managed-array
	 (loop with length = (managed-array-length vector)
	       with new-vector = (allocate-managed-array length)
	       for index from 0 below length
	       for value-to-copy = (managed-svref vector index)
	       do (setf (managed-svref new-vector index)
			(cond ((managed-float-p value-to-copy)
			       (copy-managed-float value-to-copy))
			      (t
			       ;; It's one of (NIL, Fixnum, Truth-Value, Symbol)
			       value-to-copy))) 
	       finally (return new-vector)))))


(defmacro define-ring-buffer 
	  (root-name parallel-vectors &body additional-ring-buffer-slots)
  (let* ((ring-buffer-type
	   (intern (format nil "~a-RING-BUFFER" root-name)))	; Have to use caps
	 (constructor-name
	   (intern (format nil "MAKE-~a-RING-BUFFER" root-name)))
	 (copier-name
	   (intern (format nil "COPY-~a-RING-BUFFER" root-name)))
	 (parallel-vector-name-roots
	   (loop for name-or-name-and-type in parallel-vectors
		 collect (if (symbolp name-or-name-and-type)
			     name-or-name-and-type
			     (car name-or-name-and-type))))
	 (parallel-vector-types
	   (loop for name-or-name-and-type in parallel-vectors
		 collect (if (symbolp name-or-name-and-type)
			     nil
			     (cdr name-or-name-and-type))))
	 (names-for-parallel-vectors
	   (loop for name in parallel-vector-name-roots
		 as vector-name 
		    = (intern (format nil "~a-VECTOR" name))
		 collect vector-name))
	 (get-or-make-smallest-x-ring-buffer-macro
	   (intern (format nil "GET-OR-MAKE-SMALLEST-~a-RING-BUFFER" root-name)))
	 (get-or-make-x-ring-buffer-macro
	   (intern (format nil "GET-OR-MAKE-~a-RING-BUFFER" root-name)))
	 (enlarge-x-ring-buffer-macro
	   (intern (format nil "ENLARGE-~a-RING-BUFFER" root-name)))
	 (shrink-x-ring-buffer-macro
	   (intern (format nil "SHRINK-~a-RING-BUFFER" root-name)))
	 (set-x-ring-buffer-element-macro
	   (intern (format nil "SET-~a-RING-BUFFER-ELEMENT" root-name)))
	 (set-x-ring-buffer-element-evaluation-value-macro
	   (intern (format nil "SET-~a-RING-BUFFER-ELEMENT-EVALUATION-VALUE" root-name)))
	 (mutate-x-ring-buffer-element-macro
	   (intern (format nil "MUTATE-~a-RING-BUFFER-ELEMENT" root-name)))
	 (get-x-ring-buffer-element-macro
	   (intern (format nil "GET-~a-RING-BUFFER-ELEMENT" root-name)))
	 (get-x-ring-buffer-element-evaluation-value-macro
	   (intern (format nil "GET-~a-RING-BUFFER-ELEMENT-EVALUATION-VALUE" root-name)))
	 (store-new-element-in-x-ring-buffer-macro
	   (intern (format nil "STORE-NEW-ELEMENT-IN-~a-RING-BUFFER" root-name)))
	 (store-new-element-evaluation-value-in-x-ring-buffer-macro
	   (intern (format nil "STORE-NEW-ELEMENT-EVALUATION-VALUE-IN-~a-RING-BUFFER" root-name)))
	 (ring-store-element-in-x-ring-buffer-macro
	   (intern (format nil "RING-STORE-ELEMENT-IN-~a-RING-BUFFER" root-name)))
	 (ring-mutate-element-in-x-ring-buffer-macro
	   (intern (format nil "RING-MUTATE-ELEMENT-IN-~a-RING-BUFFER" root-name)))
	 (mutate-number-in-x-ring-buffer-macro
	   (intern (format nil "MUTATE-NUMBER-IN-~a-RING-BUFFER" root-name))))

    `(progn
       (def-structure
	 (,ring-buffer-type
	  (:include ring-buffer-state)
	  (:constructor
	    ,constructor-name))

	 ,@(loop for vector-name in names-for-parallel-vectors
		 collect `(,vector-name 
			   nil :reclaimer reclaim-ring-buffer-vector))
	 ,@additional-ring-buffer-slots)

       ;; Newest-active-element-index is an index to the history-vector to
       ;; the newest active element.  Oldest-active-element-index is an index
       ;; to the history-vector to the oldest active element.  If 
       ;; newest-active-element-index = oldest-active-element-index, the
       ;; buffer may or may not be empty.  The flag ring-buffer-empty?
       ;; indicates if it is.

       ,@(loop for name in parallel-vector-name-roots
	       for vector-name in names-for-parallel-vectors
	       for vector-type in parallel-vector-types
	       as accessor-name
		  = (intern (format nil "GET-~a" name))
	       as accessor-name-evaluation-value
		  = (intern (format nil "GET-~a-EVALUATION-VALUE" name))
	       collect
	       `(defmacro ,accessor-name (ring-buffer index)
		  `(get-ring-buffer-value
		     (,',vector-name ,ring-buffer)
		     ,index
		     ,',vector-type))
	       collect
	       `(defmacro ,accessor-name-evaluation-value (ring-buffer index logicalp)
		  `(get-ring-buffer-evaluation-value
		     (,',vector-name ,ring-buffer)
		     ,index
		     ,',vector-type
		     ,logicalp)))

       ,@(loop for name in parallel-vector-name-roots
	       for vector-name in names-for-parallel-vectors
	       for vector-type in parallel-vector-types
	       as mutator-name
		  = (intern (format nil "MUTATE-MANAGED-FLOAT-FROM-~a" name))
	       nconc
	       (when (eq vector-type 'possible-float-array)
		 `((defmacro ,mutator-name (managed-float-box ring-buffer index)
		     (avoiding-variable-capture (ring-buffer)
		       `(progn
		          (setf (ring-buffer-serial-number ,ring-buffer) (+f (ring-buffer-serial-number ,ring-buffer) 1))
		          (mutate-managed-float-from-numeric-ring-buffer-value
			    ,managed-float-box
			    (,',vector-name ,ring-buffer)
			    ,index)))))))

       ,@(loop for name in parallel-vector-name-roots
	       for vector-name in names-for-parallel-vectors
	       for vector-type in parallel-vector-types
	       as set-name
		  = (intern (format nil "SET-~a" name))
	       collect
	       `(defmacro ,set-name (ring-buffer index value)
		  (avoiding-variable-capture (ring-buffer)
		    `(progn
		       (setf (ring-buffer-serial-number ,ring-buffer) (+f (ring-buffer-serial-number ,ring-buffer) 1))
		       (set-ring-buffer-value
		         (,',vector-name ,ring-buffer)
		         ,index
		         ,value
		         ,',vector-type
		         ,ring-buffer
		         ,',vector-name)))))

       (defmacro ,set-x-ring-buffer-element-macro 
		 (ring-buffer-shell index
		  &rest parallel-vector-temps) 
	 (avoiding-variable-capture 
	     (ring-buffer-shell index &rest parallel-vector-temps)
	   `(progn
	      (setf (ring-buffer-serial-number ,ring-buffer-shell) (+f (ring-buffer-serial-number ,ring-buffer-shell) 1))
	      ,@(loop for value-of-name in parallel-vector-temps 
		      for vector-name in ',names-for-parallel-vectors
		      for vector-type in ',parallel-vector-types
		      collect 
		      `(set-ring-buffer-value
			 (,vector-name ,ring-buffer-shell)
			 ,index
			 ,value-of-name
			 ,vector-type
			 ,ring-buffer-shell
			 ,vector-name)))
	   ))

       ;; Set-x-ring-buffer-element takes as args a ring buffer, an index, and n args
       ;; corresponding to each of the parallel vectors.  The elements in the vectors
       ;; svref'ed by index will be set to the n args.  

       ;; jh, 1/16/91.  Added smarter
       ;; gensyming to avoid unnecessary lexical bindings.

       (defmacro ,set-x-ring-buffer-element-evaluation-value-macro
		 (ring-buffer-shell index
		  &rest parallel-vector-temps) 
	 (avoiding-variable-capture 
	     (ring-buffer-shell index &rest parallel-vector-temps)
	   `(progn
	      (setf (ring-buffer-serial-number ,ring-buffer-shell) (+f (ring-buffer-serial-number ,ring-buffer-shell) 1))
	      ,@(loop for value-of-name in parallel-vector-temps 
		      for vector-name in ',names-for-parallel-vectors
		      for vector-type in ',parallel-vector-types
		      collect 
		      `(set-ring-buffer-value-from-evaluation-value
			 (,vector-name ,ring-buffer-shell)
			 ,index
			 ,value-of-name
			 ,vector-type
			 ,ring-buffer-shell
			 ,vector-name)))
	   ))


       (defmacro ,mutate-x-ring-buffer-element-macro 
		 (ring-buffer-shell index
		  &rest parallel-vector-temps) 
	 (avoiding-variable-capture 
	     (ring-buffer-shell index &rest parallel-vector-temps)
	   `(progn
	      (setf (ring-buffer-serial-number ,ring-buffer-shell) (+f (ring-buffer-serial-number ,ring-buffer-shell) 1))
	      ,@(loop for value-of-name in parallel-vector-temps 
		      for vector-name in ',names-for-parallel-vectors
		      for vector-type in ',parallel-vector-types
		      collect 
		      `(mutate-ring-buffer-value
			 (,vector-name ,ring-buffer-shell)
			 ,index
			 ,value-of-name
			 ,vector-type
			 ,ring-buffer-shell
			 ,vector-name)))
	   ))

       (defmacro ,get-x-ring-buffer-element-macro 
		 (ring-buffer-shell index)
	 (avoiding-variable-capture (ring-buffer-shell index)
	   `(values
	      ,@(loop for vector-name in ',names-for-parallel-vectors
		      for vector-type in ',parallel-vector-types
		      collect 
		      `(get-ring-buffer-value
			 (,vector-name ,ring-buffer-shell)
			 ,index
			 ,vector-type)))
	   ))

       (defmacro ,get-x-ring-buffer-element-evaluation-value-macro 
		 (ring-buffer-shell index logicalp)
	 (avoiding-variable-capture (ring-buffer-shell index)
	   `(values
	      ,@(loop for vector-name in ',names-for-parallel-vectors
		      for vector-type in ',parallel-vector-types
		      collect 
		      `(get-ring-buffer-evaluation-value
			 (,vector-name ,ring-buffer-shell)
			 ,index
			 ,vector-type
			 ,logicalp)))
	   ))
       ;; Get-x-ring-buffer-element takes as args a ring buffer and an index.
       ;; The values of the n elements svref'ed by index will be returned.

       (defmacro ,ring-store-element-in-x-ring-buffer-macro 
		 (ring-buffer-shell
		  &rest parallel-vector-values)
	 (avoiding-variable-capture
	     (ring-buffer-shell
	      &rest parallel-vector-values)
	   `(cond
	       ((ring-buffer-empty? ,ring-buffer-shell)
		(,',set-x-ring-buffer-element-macro
		   ,ring-buffer-shell
		   (newest-active-element-index ,ring-buffer-shell)
		   ,@parallel-vector-values)
		(set-ring-buffer-empty? ,ring-buffer-shell nil)
		nil)
	       ((ring-buffer-full? ,ring-buffer-shell)
		(increment-newest-element-index ,ring-buffer-shell)
		(,',set-x-ring-buffer-element-macro
		     ,ring-buffer-shell
		     (newest-active-element-index ,ring-buffer-shell)
		     ,@parallel-vector-values)
		(increment-oldest-element-index ,ring-buffer-shell)
		t)
	       (t
		(increment-newest-element-index ,ring-buffer-shell)
		(,',set-x-ring-buffer-element-macro
		     ,ring-buffer-shell
		     (newest-active-element-index ,ring-buffer-shell)
		     ,@parallel-vector-values)
		nil))
	   ))
       ;; Returns boolean to indicate whether it had to overwrite.
       ;; It is an error to call this macro on a ring buffer of
       ;; size 0.
       
       (defmacro ,ring-mutate-element-in-x-ring-buffer-macro 
		 (ring-buffer-shell
		  &rest parallel-vector-values)
	 (avoiding-variable-capture
	     (ring-buffer-shell
	      &rest parallel-vector-values)
	   `(cond
	       ((ring-buffer-empty? ,ring-buffer-shell)
		(,',mutate-x-ring-buffer-element-macro
		   ,ring-buffer-shell
		   (newest-active-element-index ,ring-buffer-shell)
		   ,@parallel-vector-values)
		(set-ring-buffer-empty? ,ring-buffer-shell nil)
		nil)
	       ((ring-buffer-full? ,ring-buffer-shell)
		(increment-newest-element-index ,ring-buffer-shell)
		(,',mutate-x-ring-buffer-element-macro
		     ,ring-buffer-shell
		     (newest-active-element-index ,ring-buffer-shell)
		     ,@parallel-vector-values)
		(increment-oldest-element-index ,ring-buffer-shell)
		t)
	       (t
		(increment-newest-element-index ,ring-buffer-shell)
		(,',mutate-x-ring-buffer-element-macro
		     ,ring-buffer-shell
		     (newest-active-element-index ,ring-buffer-shell)
		     ,@parallel-vector-values)
		nil))
	   ))
       ;; Returns boolean to indicate whether it had to overwrite.
       ;; It is an error to call this macro on a ring buffer of
       ;; size 0.
      

       (defmacro ,store-new-element-in-x-ring-buffer-macro 
		 (ring-buffer-shell expansion-function-to-use
		  &rest parallel-vector-values)
	 (avoiding-variable-capture
	     (ring-buffer-shell expansion-function-to-use
	      &rest parallel-vector-values)
	   `(cond
	       ((ring-buffer-empty? ,ring-buffer-shell)
		(,',set-x-ring-buffer-element-macro
		   ,ring-buffer-shell
		   (newest-active-element-index ,ring-buffer-shell)
		   ,@parallel-vector-values)
		(set-ring-buffer-empty? ,ring-buffer-shell nil))
	       (t (when (ring-buffer-full? ,ring-buffer-shell)
		    (funcall
		      ,expansion-function-to-use
		      ,ring-buffer-shell))
		  (increment-newest-element-index ,ring-buffer-shell)
		  (,',set-x-ring-buffer-element-macro
		     ,ring-buffer-shell
		     (newest-active-element-index ,ring-buffer-shell)
		     ,@parallel-vector-values)))
	   ))
       ;; Store-new-element-in-x-ring-buffer takes as args a ring buffer, an
       ;; expansion-function-to-use, and n args
       ;; corresponding to each of the parallel vectors.  The values for the
       ;; n args will be stored in the element
       ;; after the one pointed to by newest-active-element-index.
       ;; This will handle empty buffers and will automatically expand buffers
       ;; if necessary.

       (defmacro ,store-new-element-evaluation-value-in-x-ring-buffer-macro 
		 (ring-buffer-shell expansion-function-to-use
		  &rest parallel-vector-values)
	 (avoiding-variable-capture
	     (ring-buffer-shell expansion-function-to-use
	      &rest parallel-vector-values)
	   `(cond
	       ((ring-buffer-empty? ,ring-buffer-shell)
		(,',set-x-ring-buffer-element-evaluation-value-macro
		   ,ring-buffer-shell
		   (newest-active-element-index ,ring-buffer-shell)
		   ,@parallel-vector-values)
		(set-ring-buffer-empty? ,ring-buffer-shell nil))
	       (t (when (ring-buffer-full? ,ring-buffer-shell)
		    (funcall
		      ,expansion-function-to-use
		      ,ring-buffer-shell))
		  (increment-newest-element-index ,ring-buffer-shell)
		  (,',set-x-ring-buffer-element-evaluation-value-macro
		     ,ring-buffer-shell
		     (newest-active-element-index ,ring-buffer-shell)
		     ,@parallel-vector-values)))
	   ))

       (defmacro ,mutate-number-in-x-ring-buffer-macro 
		 (ring-buffer-shell expansion-function-to-use
		  &rest parallel-vector-values)
	 (avoiding-variable-capture
	     (ring-buffer-shell expansion-function-to-use
	      &rest parallel-vector-values)
	   `(cond
	       ((ring-buffer-empty? ,ring-buffer-shell)
		(,',mutate-x-ring-buffer-element-macro
		   ,ring-buffer-shell
		   (newest-active-element-index ,ring-buffer-shell)
		   ,@parallel-vector-values)
		(set-ring-buffer-empty? ,ring-buffer-shell nil))
	       (t (if (ring-buffer-full? ,ring-buffer-shell)
		      (funcall
			,expansion-function-to-use
			,ring-buffer-shell))
		  (increment-newest-element-index ,ring-buffer-shell)
		  (,',mutate-x-ring-buffer-element-macro
		     ,ring-buffer-shell
		     (newest-active-element-index ,ring-buffer-shell)
		     ,@parallel-vector-values)))
	   ))

       (defmacro ,get-or-make-smallest-x-ring-buffer-macro ()
	 `(let* ((ring-buffer-shell (,',constructor-name)))
	    ,@(loop for vector-name in ',names-for-parallel-vectors
		    for vector-type in ',parallel-vector-types
		    collect 
		    `(setf (,vector-name ring-buffer-shell)
			   (get-or-make-smallest-ring-buffer-vector
			     ,vector-type)))
	    (set-ring-buffer-size 
	      ring-buffer-shell
	      smallest-ring-buffer-vector-size)
	    ring-buffer-shell))

       (defmacro ,get-or-make-x-ring-buffer-macro (ring-buffer-size)
	 `(let* ((ring-buffer-shell
		   (,',constructor-name))
		 (size-to-allocate
		   (minf ,ring-buffer-size
			 largest-ring-buffer-vector-size)))
	    ,@(loop for vector-name in ',names-for-parallel-vectors
		    for vector-type in ',parallel-vector-types
		    collect 
		      `(setf (,vector-name ring-buffer-shell)
			     (get-or-make-ring-buffer-vector
			       ,vector-type 
			       size-to-allocate)))
	    (set-ring-buffer-size 
	      ring-buffer-shell
	      size-to-allocate)
	    ring-buffer-shell))
       

       ;; The copier function doesn't know what's in the additional-slots of
       ;; a ring-buffer.  So if they are used, a copier function should be passed in
       ;; or the slots will be "copied" through setf.
       (defun ,copier-name (ring-buffer &optional copier-function-for-additional-slots)
	 ,@(cond (additional-ring-buffer-slots
		  nil)
		 (t
		  `((declare (ignore copier-function-for-additional-slots)))))
	 (let ((new-shell (,constructor-name)))
	   (copy-ring-buffer-shell-slots ring-buffer new-shell)
	    ,@(loop for vector-name in names-for-parallel-vectors
		    collect 
    		      `(setf (,vector-name new-shell)
			     (copy-ring-buffer-vector (,vector-name ring-buffer))))
	    ,@(loop for slot-descriptor in additional-ring-buffer-slots
		    as slot-name = (if (consp slot-descriptor)
				       (car slot-descriptor)
				       slot-descriptor)
		    collect
		    `(setf (,slot-name new-shell)
			   (cond (copier-function-for-additional-slots
				  (funcall copier-function-for-additional-slots
					   (,slot-name ring-buffer)))
				 (t
				  (,slot-name ring-buffer)))))
	    new-shell))
       
       (defmacro ,enlarge-x-ring-buffer-macro 
		 (ring-buffer-shell current-size &optional new-size?)
	 (avoiding-variable-capture (ring-buffer-shell current-size new-size?)
	   `(let ((oldest-active-element-index
		    (oldest-active-element-index ,ring-buffer-shell))
		  (ring-buffer-length
		    (ring-buffer-length ,ring-buffer-shell))
		  (next-larger-size
		    (or ,new-size?
			(compute-next-larger-size-for-ring-buffer-vectors
			  ,current-size))))
	      ,@(loop for vector-name in ',names-for-parallel-vectors
		      collect
		      `(cond ((managed-array-p
				(,vector-name ,ring-buffer-shell))
			      ;; Compile time check using parallel-vector-types
			      ;; is not performed here (as it is in other cases).
			      ;; Compile time check in addition to runtime check
			      ;; would not greatly improve speed for this 
			      ;; operation.
			      (rotate-managed-array 
				(,vector-name ,ring-buffer-shell)
				oldest-active-element-index)
			      (setf (,vector-name ,ring-buffer-shell)
				    (adjust-managed-array
				      (,vector-name ,ring-buffer-shell)
				      next-larger-size)))
			     (t (rotate-managed-float-array 
				  (,vector-name ,ring-buffer-shell)
				  oldest-active-element-index)
				(setf (,vector-name ,ring-buffer-shell)
				      (adjust-managed-float-array
					(,vector-name ,ring-buffer-shell)
					next-larger-size)))))
	      (set-oldest-active-element-index ,ring-buffer-shell 0)
	      (set-newest-active-element-index ,ring-buffer-shell
					       (-f ring-buffer-length 1))
	      (set-ring-buffer-size 
		,ring-buffer-shell
		next-larger-size))
	   ))
       ;; The enlarge macro should not have to become a suspendable function
       ;; as long as the amount by which the ring buffer is enlarged is kept
       ;; below some limit.  It would be difficult to make this
       ;; suspendable since it would be difficult to access or set elements
       ;; of the ring buffer if it is in the middle of being enlarged.

       (defmacro ,shrink-x-ring-buffer-macro 
		 (ring-buffer-shell current-size new-size)
	 (avoiding-variable-capture (ring-buffer-shell current-size new-size)
	   `(let ((oldest-active-element-index
		    (oldest-active-element-index ,ring-buffer-shell))
		  (ring-buffer-length
		    (ring-buffer-length ,ring-buffer-shell)))
	      ,@(loop for vector-name in ',names-for-parallel-vectors
		      collect
		      `(cond ((managed-array-p
				(,vector-name ,ring-buffer-shell))
			      ;; Compile time check using parallel-vector-types
			      ;; is not performed here (as it is in other cases).
			      ;; Compile time check in addition to runtime check
			      ;; would not greatly improve speed for this 
			      ;; operation.
			      (rotate-managed-array 
				(,vector-name ,ring-buffer-shell)
				oldest-active-element-index)
			      (when (<f ,new-size ring-buffer-length)
				(rotate-managed-array 
				  (,vector-name ,ring-buffer-shell)
				  (-f ring-buffer-length ,new-size)))
			      (setf (,vector-name ,ring-buffer-shell)
				    (adjust-managed-array
				      (,vector-name ,ring-buffer-shell)
				      ,new-size)))
			     (t 
			      (rotate-managed-float-array 
				(,vector-name ,ring-buffer-shell)
				oldest-active-element-index)
			      (when (<f ,new-size ring-buffer-length)
				(rotate-managed-float-array 
				  (,vector-name ,ring-buffer-shell)
				  (-f ring-buffer-length ,new-size)))
			      (setf (,vector-name ,ring-buffer-shell)
				    (adjust-managed-float-array
				      (,vector-name ,ring-buffer-shell)
				      ,new-size)))))
	      (set-oldest-active-element-index ,ring-buffer-shell 0)
	      (set-newest-active-element-index ,ring-buffer-shell
					       (-f (minf ring-buffer-length ,new-size) 1))
	      (set-ring-buffer-size 
		,ring-buffer-shell
		,new-size))
	   ))
       )))

;; Added avoiding-variable-capture scopes to some of the macros generated by
;; define-ring-buffer, so that gensyms will be bound only if needed and the
;; resulting macroexpansions are more perspicuous.  Below the define-ring-buffer
;; definition is a commented-out version which breaks in some versions of Coral
;; because it contains the ,,@ backquoting idiom.  There is no need to maintain
;; this code in parallel anymore, since the new define-ring-buffer contains no
;; backquote idioms more complicated than the old, working define-ring-buffer.  We
;; should of course keep the old one around for a while, though.  jh, 1/24/91.
;; jh, 6/4/91. Flushed the Coral code.

;; If you are relying on strict left-to-right evaluation of the macros generated
;; by define-ring-buffer, see the caveat under the documentation for
;; avoiding-variable-capture in UTILITIES2.  I may have to change the
;; avoiding-variable-capture scopes to use &aux variables in this case.  
;; jh, 1/24/91.

;; Initializations are currently allowed for the additional ring buffer slots 
;; but not for the vectors.  Initialization of vectors is cumbersome
;; (may take some time when vector is retrieved from pool) and 
;; shouldn't be necessary in a ring buffer.

;; Anything that changes the buffer size (by enlarging or shrinking)
;; must adjust the ring-buffer-size slot of the ring buffer accordingly.




;;;; Ring Buffer Pointer Movement

(def-substitution-macro increment-oldest-element-index (ring-buffer)
  (set-oldest-active-element-index
    ring-buffer 
    (increment-active-element-index 
      (oldest-active-element-index ring-buffer) ring-buffer)))

(def-substitution-macro increment-newest-element-index (ring-buffer)
  (set-newest-active-element-index
    ring-buffer 
    (increment-active-element-index 
      (newest-active-element-index ring-buffer) ring-buffer)))

(def-substitution-macro decrement-oldest-element-index (ring-buffer)
  (set-oldest-active-element-index
    ring-buffer 
    (decrement-active-element-index 
      (oldest-active-element-index ring-buffer) ring-buffer)))

(def-substitution-macro decrement-newest-element-index (ring-buffer)
  (set-newest-active-element-index
    ring-buffer 
    (decrement-active-element-index 
      (newest-active-element-index ring-buffer) ring-buffer)))

(def-substitution-macro increment-active-element-index (index ring-buffer)
  (if (=f index
	  (-f (ring-buffer-size ring-buffer) 1))
      0
      (+f 1 index)))

;;; The substitution macro `advance-active-element-index' takes three arguments:
;;; an index into a ring buffer, the ring buffer itself, and delta, the amount
;;; to advance the ring buffer index.  Delta must not be greater in absolute
;;; magnitude than the size of the ring buffer.

(def-substitution-macro advance-active-element-index (index ring-buffer delta)
  (let ((size (ring-buffer-size ring-buffer))
	(raw-index (+f index delta)))
    (if (>=f raw-index size)
	(-f raw-index size)
	raw-index)))

;;; The substitution macro `ring-buffer-index<' returns non-nil if the first
;;; index precedes the second for the given ring buffer, and nil otherwise.

(def-substitution-macro ring-buffer-index< (ring-buffer index1 index2)
  (let ((oldest-index (oldest-active-element-index ring-buffer)))
    (cond
      ((or (and (>=f index1 oldest-index) (>=f index2 oldest-index))
	   (and (<f index1 oldest-index) (<f index2 oldest-index)))
       (<f index1 index2))
      ((>=f index1 oldest-index) t)
      (t nil))))
      
	    

(def-substitution-macro decrement-active-element-index (index ring-buffer)
  (if (=f index 0)
      (-f (ring-buffer-size ring-buffer) 1)
      (-f index 1)))

(def-substitution-macro ring-buffer-length (ring-buffer)
  (ring-buffer-length-up-to-index
    ring-buffer (newest-active-element-index ring-buffer)))

;; Ring-buffer-length, defined by the number of elements between the
;; oldest and newest active element indices, should not be confused 
;; with ring-buffer-size, which is the total number of elements 
;; available in the ring buffer.


(def-substitution-macro ring-buffer-length-up-to-index (ring-buffer index)
  (let ((oldest-active-element-index-for-ring-buffer
	  (oldest-active-element-index ring-buffer)))
    (if (>=f index oldest-active-element-index-for-ring-buffer)
	(+f 1 (-f index oldest-active-element-index-for-ring-buffer))
	(+f 1 (-f (+f index (ring-buffer-size ring-buffer))
		  oldest-active-element-index-for-ring-buffer)))))

(def-substitution-macro ring-buffer-full? (ring-buffer)
  (=f (ring-buffer-length ring-buffer)
      (ring-buffer-size ring-buffer)))

(def-substitution-macro ring-buffer-index-difference (ring-buffer index-1 index-2)
  (if (>=f index-1 index-2)
      (+f 1 (-f index-1 index-2))
      (+f 1 (-f (+f index-1 (ring-buffer-size ring-buffer)) index-2))))




;;;; Ring Buffers for Thrashing Cost in Decacheable Structures

;;; This code is here rather than in UTILITIES2 because it uses
;;; define-ring-buffer (see above), which is not defined in UTILITIES2.
;;; UTILITIES2 contains most of the code for the decacheable structure mechanism
;;; (see define-decacheable-structure).



;;; Thrashing-ratio-ring-buffer-length indicates the number of values to be
;;; kept.  It is assumed that the ring buffer is large enough to accomodate all
;;; the values without having to be enlarged.

(defparameter thrashing-ratio-ring-buffer-length 10)



;;; A thrashing-ratio-ring-buffer contains the last N thrashing ratios where N =
;;; thrashing-ratio-ring-buffer-length.  It is much simpler than other ring
;;; buffers like history-ring-buffer or plot-data-ring-buffer since it has only
;;; one vector, is never enlarged, and doesn't change size at all once it
;;; reaches thrashing-ratio-ring-buffer-size.

(define-ring-buffer thrashing-ratio (thrashing-ratio-value))

;; An alternative would be to keep the thrashing cost and measurement interval
;; in separate vectors.  At this point, however, there is no advantage in 
;; doing this.

;; Use immediate float arrays for thrashing-ratio ring buffers!


(defparameter fixnum-time-normalization-factor
	      (coerce-to-gensym-float (fixnum-time-interval 1000)))

;; Dividing a fixnum time by this normalization factor normalizes it to seconds.




;;; Compute-newest-thrashing-ratio computes the newest thrashing ratio based on
;;; accumulated thrashing cost and time-since-last-update.  It also computes the
;;; filtered thrashing ratio by calling compute-filtered-thrashing-ratio with
;;; the thrashing ratio ring buffer.  It sets the appropriate slots in
;;; limit-info (a memory-limit-info structure) to the new values as well as
;;; returning them.  It also stores the newest thrashing ratio in the thrashing
;;; ratio ring buffer.  If no ring buffer exists, one is created and put into
;;; the thrashing-cost-ring-buffer slot of limit-info.

;;; Note that the thrashing ratios are actually kept as integers in the 
;;; ring buffer and in the memory-limit-info structure.  Thus, they are
;;; not actually fractions and it is assumed that they are of sufficient
;;; magnitude that rounding them does not greatly reduce their accuracy
;;; (see also global-desired-thrashing-setpoint).

(defun compute-newest-thrashing-ratio (limit-info time-since-last-update)
  (let* ((thrashing-cost-float
	   (coerce-to-gensym-float
	     (accumulated-thrashing-cost limit-info)))
	 (normalized-time-since-last-update
	   (when time-since-last-update
	     (/e (coerce-to-gensym-float time-since-last-update)
		 fixnum-time-normalization-factor)))
	 (newest-thrashing-ratio
	   (round
	     (if normalized-time-since-last-update
		 (/ thrashing-cost-float normalized-time-since-last-update)
		 thrashing-cost-float)))
	 filtered-thrashing-ratio)

    ;; reset thrashing cost accumulator
    (setf (accumulated-thrashing-cost limit-info) 0)   

    (when (null (thrashing-ratio-ring-buffer limit-info))
      (setf (thrashing-ratio-ring-buffer limit-info)
	    (get-or-make-smallest-thrashing-ratio-ring-buffer)))
    (let ((thrashing-ratio-ring-buffer
	    (thrashing-ratio-ring-buffer limit-info)))
      (store-new-element-in-thrashing-ratio-ring-buffer
	thrashing-ratio-ring-buffer
	nil					       ; should never expand
	newest-thrashing-ratio)
      (if (>f (ring-buffer-length thrashing-ratio-ring-buffer)
	      thrashing-ratio-ring-buffer-length)
	  (increment-oldest-element-index thrashing-ratio-ring-buffer))
      (setq filtered-thrashing-ratio
	    (round
	      (compute-filtered-thrashing-ratio thrashing-ratio-ring-buffer)))
      (setf (newest-thrashing-ratio limit-info) newest-thrashing-ratio)
      (setf (filtered-thrashing-ratio limit-info) filtered-thrashing-ratio)
      (values newest-thrashing-ratio filtered-thrashing-ratio))))



(defparameter base-for-exponential-weighting 0.5)


(defun compute-weighting-factors-for-thrashing-filter ()
  (compute-exponential-weighting-factors base-for-exponential-weighting)
  ;; Other weighting factors, such as a simple average, are possible.
  ;; See also books on optimal digital filtering.
  )

;; A simple average could be used to implement the integral factor of a PID
;; control scheme.  The proportional factor would be the newest-thrashing-ratio,
;; and the differential factor could be computed by the difference between the
;; ratios in the ring buffer.


(defun compute-exponential-weighting-factors (exponent-base)
  (loop for exponent from 1 to thrashing-ratio-ring-buffer-length
	collect (expt exponent-base exponent)))

(defvar weighting-factors-for-thrashing-ratio-ring-buffers
	(compute-weighting-factors-for-thrashing-filter))



(defun compute-filtered-thrashing-ratio (thrashing-ratio-ring-buffer)
  (if (not (ring-buffer-empty? thrashing-ratio-ring-buffer))
      (loop with index = (newest-active-element-index
			   thrashing-ratio-ring-buffer)
	    with count = 1
	    for weighting-factor 
		in weighting-factors-for-thrashing-ratio-ring-buffers
	    sum (* weighting-factor
		   (get-thrashing-ratio-ring-buffer-element
		     thrashing-ratio-ring-buffer index))
	    do (if (>=f count 
			(ring-buffer-length
			  thrashing-ratio-ring-buffer))
		   (setq count 1
			 index (newest-active-element-index
				 thrashing-ratio-ring-buffer))
		   (setq count (+f count 1)
			 index (decrement-active-element-index
				 index thrashing-ratio-ring-buffer))))
      0))

;; Note that if the ring buffer contains fewer elements than 
;; weighting-factors-for-thrashing-ratio-ring-buffers, the above loop will
;; wrap around the ring buffer, reusing existing elements.














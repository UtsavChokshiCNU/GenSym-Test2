;;; KB System Procedure: kb-g2nke-count-history-matching-op
;;; Below the 3 layers from KB through Lisp to C follow in reverse order

;;; This layer finally allows implementing the KB function in C
(def-gensym-c-function c-g2nke-count-history-matching-op
                       (:object "g2nke_count_history_datapoints_matching_op")
  ((:object arg-variable)
   (:object value-history-cascaded-ring-buffer)
   (:object value-history-ring-buffer-or-cascade)
   (:object value-requested-by-simulator?)
   (:object referencing-simulation-history?)
   (:object arg-N) 
   (:object arg-nStart)
   (:object arg-fellow-val)
   (:object arg-requiredGoodSize)
   (:object arg-compareOperator)))

;;; This layer is gaining "history-function" features
(define-history-function lisp-g2nke-count-history-matching-op
  ( arg-N 
    arg-nStart arg-fellow-val 
    arg-requiredGoodSize arg-compareOperator
  )
  nil t
  (c-g2nke-count-history-matching-op
      variable 
      value-history-cascaded-ring-buffer
      value-history-ring-buffer-or-cascade
      value-requested-by-simulator?
      referencing-simulation-history?
      ; arg-subj duplicates "variable"
      arg-N  arg-nStart  arg-fellow-val 
      arg-requiredGoodSize  arg-compareOperator
  )
)

;;; This layer is adding the system call for KB language            
(defun-for-system-procedure kb-g2nke-count-history-matching-op
  (arg-subj arg-N arg-nStart arg-fellow-val 
   arg-requiredGoodSize arg-compareOperator)
  
  (make-evaluation-float
	(if
		(g2-enterprise-p)
		(lisp-g2nke-count-history-matching-op
		  arg-subj ; variable
		  NIL      ; value-requested-by-simulator?
		  arg-N  arg-nStart  arg-fellow-val 
		  arg-requiredGoodSize  arg-compareOperator
		)
		0.0
	)
  )
  ;TODO: reclaim? use defun-for-system-procedure+ ?
)


;;; KB System Procedure: kb-g2nke-count-history-matching-op-and-eventflag
;;; Below the 3 layers from KB through Lisp to C follow in reverse order

;;; This layer finally allows implementing the KB function in C
(def-gensym-c-function c-g2nke-count-history-matching-op-and-eventflag
                       (:object "g2nke_count_history_datapoints_matching_op_and_eventflag")
  ((:object arg-variable)
   (:object arg-N)
   (:object arg-nStart)
   (:object arg-fellow-val)
   (:object arg-eventFlag)
   (:object arg-event-bit)
   (:object arg-requiredGoodSize)
   (:object arg-compareOperator)))

;;; This layer is adding the system call for KB language            
(defun-for-system-procedure kb-g2nke-count-history-matching-op-and-eventflag
  (arg-subj  arg-N  arg-nStart  arg-fellow-val
   arg-eventFlag  arg-event-bit
   arg-requiredGoodSize  arg-compareOperator)
  ; (make-evaluation-value 
  (make-evaluation-float
    (if
	  (g2-enterprise-p)
	  (c-g2nke-count-history-matching-op-and-eventflag
	    arg-subj  arg-N  arg-nStart  arg-fellow-val
	    arg-eventFlag  arg-event-bit
	    arg-requiredGoodSize  arg-compareOperator
	  )
	  0.0
	)
  )
  ;TODO: reclaim? use defun-for-system-procedure+ ?
)


;;; Some helper functions for C code implementing the KB function

;;; Makes macro get-total-length-of-ring-buffer-or-cascade 
;;;   accessible from C code
(defun c2-get-total-length-of-ring-buffer-or-cascade (ring-buffer-or-cascade)
  (get-total-length-of-ring-buffer-or-cascade ring-buffer-or-cascade))


;;; c2-get-history-spec returns a list containing the objects necessary for working
;;;   with histories
;;; A history-spec is a list containing
;;; (value-history-cascaded-ring-buffer value-history-ring-buffer-or-cascade 
;;;   value-requested-by-simulator? referencing-simulation-history?)
(define-history-function c2-get-history-spec () nil t
  ;; causes warn_gensym_area_violation("Memory inconsistency (type 1) detected.")
  ;; (list
  (values
      value-history-cascaded-ring-buffer
      value-history-ring-buffer-or-cascade
      value-requested-by-simulator?
   referencing-simulation-history?
   (ring-buffer-serial-number value-history-ring-buffer-or-cascade)))

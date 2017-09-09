;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;; Function copy-for-slot-value was moved from frames2.lisp without any touch,
;;; because it use many macros defined also in frames2.lisp and those macros
;;; are not easily to be made visible on compile-time for this function.
;;; -- Glority, 2010/3/21

;;; `Copy-for-slot-value' copies a slot value, or converts a compilation result
;;; into a slot value, by:
;;;
;;;    (1) copying a gensym float or a managed float as a managed float;
;;;
;;;    (2) copying a cons as a slot value cons, with recursive copying of
;;;        the car and cdr, unless it is the unique value no-value, or
;;;         (2a) a cons whose car is a list of elements to be copied
;;;              and made the value of a sequence; the cdr is the unique
;;;              value phrase-sequence-marker; or
;;;         (2b) a cons car is a plist of field-name/value pairs to
;;;              be copied and made the value of a structure; the cdr
;;;              is the unique value phrase-structure-marker;
;;;
;;;    (3) copying a gensym string or a text string as a text string;
;;;
;;;    (4) copying a managed array as a managed array, with recursive copying
;;;        of its elements;
;;;
;;;    (5) copying a managed float array, copying the float values stored
;;;        therein;
;;;
;;;    (6) copying a byte-code-body using copy-byte-code-body;
;;;
;;;    (7) copying a dependent frame using its copy-frame method. IT IS AN
;;;        ERROR TO COPY A SLOT VALUE CONTAINING A DEPENDENT-FRAME WITHOUT
;;;        HAVING A COPY-FRAME METHOD FOR DEPENDENT FRAMES OF THAT CLASS.
;;;        There is no reasonable way to write a generic method for all
;;;        dependent frames, it would be an error to reference the frame
;;;        in the value being copied, and it would be inappropriate to
;;;        replace it with the value NIL; and
;;;
;;;    (8) leaving anything else as is.
;;;
;;; Note that unique-structure-marker and unique-sequence-marker should
;;; only be present in phrases (parse results) that are passed to this
;;; function; never in actual slot values.  Similarly, gensym floats
;;; and gensym strings should only be present in slot init forms or
;;; other constant, shared data structures passed to this function, never
;;; in actual slot values, at least not as unique slot values, unshared,
;;; and therefore subject to mutation and reclamation.

;;; Note copy-for-slot-value is being declared as aside-effect free function.
;;; This is valid under a special case of the definition of side-effect free as
;;; long as the memory metering functions are not themselves declared
;;; side-effect free.  See the documentation for declare-side-effect-free-
;;; function for a further description of this special case.  -jra 3/26/91

(declare-side-effect-free-function copy-for-slot-value)

(defun copy-for-slot-value (value-for-slot)
  (cond
    ((or (null value-for-slot)
         (fixnump value-for-slot)
         (symbolp value-for-slot)
         (no-value-p value-for-slot))
     value-for-slot)                                ; optimization
    #+subblocks-v2
    ((constant-queue-p value-for-slot)
     #+development
     (error "copy a constant-queue?!")
     nil)
    ((managed-float-p value-for-slot)
     (copy-managed-float value-for-slot))
    ((managed-long-p value-for-slot)
     (copy-managed-long value-for-slot))
    ((or (gensym-string-p value-for-slot)
         (text-string-p value-for-slot))
     (copy-text-string value-for-slot))
    ((managed-float-array-p value-for-slot)
     (copy-managed-float-array value-for-slot))
    ((managed-array-p value-for-slot)
     (loop with length = (managed-array-length value-for-slot)
           with new-array = (allocate-managed-array length)
           for index from 0 below length
           for value-to-copy = (managed-svref value-for-slot index)
           do (setf (managed-svref new-array index)
                    (if value-to-copy
                        (copy-for-slot-value value-to-copy)
                        nil))
           finally (return new-array)))
    ((byte-code-body-p value-for-slot)
     (copy-byte-code-body value-for-slot))
    ((gensym-float-p value-for-slot)                ; new. (MHD 3/15/91)
     (make-slot-value-float-macro value-for-slot))
    ((gensym-long-p value-for-slot)
     (make-slot-value-long-macro value-for-slot))
    ((of-class-p value-for-slot 'dependent-frame)
     (funcall-method-macro 'copy-frame value-for-slot))
    #+relation-instances-v2
    ((and (consp value-for-slot)
	  (eq (car value-for-slot) 'relation-instance-tree))
     #+development
     (error "copy-for-slot-value for relation-instance-tree?!")
     nil)
    #+connections-v2
    ((and (consp value-for-slot)
	  (eq (car value-for-slot) 'connection-item-table))
     #+development
     (error "copy-for-slot-value for connection-item-table?!")
     nil)
    ;; NOTE: in current Chestnut configuration, there's no header for conses,
    ;; so the type test for conses must be the last test after all others. --binghe
    ((consp value-for-slot)
     (let ((cdr-of-cons (cdr value-for-slot)))
       (cond
         ((null cdr-of-cons)
          (let ((car-of-cons (car value-for-slot)))
            (slot-value-cons
              (if (or (null car-of-cons) (symbolp car-of-cons)
                      (fixnump car-of-cons))
                  car-of-cons
                  (copy-for-slot-value car-of-cons))
              nil)))

         ;; The next two are used only when copying a parse result
         ;; for inclusion in a slot value:
         ((eq cdr-of-cons phrase-sequence-marker)
          ;; In this case (phrase-sequence-p value-for-slot) must be true.
          (loop for element in (car-of-cons value-for-slot)
                collect (copy-for-slot-value element)
                into contents
                using eval-cons
                finally (return (allocate-evaluation-sequence contents))))
         ((eq cdr-of-cons phrase-structure-marker)
          ;; In this case (phrase-structure-p value-for-slot) must be true.
          (loop for element in (car-of-cons value-for-slot)
                collect (copy-for-slot-value element)
                into property-list
                using eval-cons
                finally (return (allocate-evaluation-structure property-list))))
         ((eq cdr-of-cons phrase-item-denotation-marker)
          (find-frame-for-denotation (car-of-cons value-for-slot)))
         ((eq cdr-of-cons phrase-item-marker)
          (car-of-cons value-for-slot))

         ((defined-evaluation-value-type-p cdr-of-cons)
          (funcall-simple-compiled-function
            (defined-evaluation-type-copier cdr-of-cons)
            value-for-slot))
         (t
          (loop with new-list
                  = (make-slot-value-list
                      (loop for next-cdr = cdr-of-cons then (cdr next-cdr)
                            count t
                            while (consp next-cdr)))
                for cons-to-copy
                    = value-for-slot then (cdr cons-to-copy)
                as new-cons
                   = new-list then (cdr new-cons)
                as car-to-copy
                   = (car cons-to-copy)
                do (setf (car new-cons)
                         (if (or (null car-to-copy)
                                 (symbolp car-to-copy)
                                 (fixnump car-to-copy)
                                 (no-value-p value-for-slot))
                             car-to-copy        ; optimization
                             (copy-for-slot-value car-to-copy)))
                when (null (cdr new-cons))
                  do (when (cdr cons-to-copy)
                       (setf (cdr new-cons)
                             (copy-for-slot-value (cdr cons-to-copy))))
                     (return new-list))))))
    (t
     #+development
     (unless (legal-non-copied-slot-value-p value-for-slot)
       (cerror "Continue" "Unknown thing for copy-for-slot-value ~S" value-for-slot))
     value-for-slot)))

;; This is not simply called copy-slot-value because its arg may be a compilation
;; result in addition to a slot value.  (Some people have wondered why.)
;; (MHD 2/22/91)

;; This will fail if it encounters a simple vector of length zero.

;; Note that in the implementation above, the order in this documentation is not
;; maintained.  The important points of the ordering to remember are that
;; managed-floats must be considered before conses, and that managed-arrays,
;; managed-float-arrays, and dependent-frames are all implemented as
;; simple-vectors (though this second fact need not currently be relied upon in
;; the code above).  -jra 2/19/91

;; Note that the loop for slot value cons lists above could be optimized quite a
;; bit.  It is mostly using car and cdr instead of car-of-cons and cdr-of-cons;
;; within the actual copying loop the cdr of the new-cons and the cons-to-copy
;; are taken at least twice instead of making a leading-cons variable; and in
;; the optimizations for calling copy-slot-value it is unnecessary to call both
;; null and symbolp.  -jra 9/10/91

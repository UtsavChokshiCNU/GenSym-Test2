;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module UTILITIES1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David, Lowell Hawkinson, Michael Levin, Stephen DeVoy,
;;; Jim Allard, and Ong, Peng Tsin



(declare-forward-references                ; in UNICODE
  (twrite-general-string function)
  (twrite-line-separator function)
  (twrite-wide-character function)
  (text-string-p function)
  (lengthw function)
  (charw-function function)
  (twrite-symbol function)
  (wide-character-member function)
  (twrite-fixnum function)
  (write-floating-point-number function)
  (write-floating-point-number-simple-c-format function)
  (twrite-positive-bignum function)
  (twrite-positive-fixnum-in-radix function)
  (copy-text-string function)
  (twrite-long-function function))

;; In EVAL

(declare-forward-reference print-designation function)
(declare-forward-reference print-constant function)
(declare-forward-reference write-type-specification function)
(declare-forward-reference write-expression function)
(declare-forward-reference get-or-make-up-designation-for-block function)

;; In SETS

(declare-forward-reference write-evaluation-value function)
(declare-forward-reference write-block-or-evaluation-value function)

;; See module CHARACTERS for the subsection "Gensym Strings" -- I move that there
;; when major forward referencing problems surfaced today.  (MHD 1/26/90)


;; In DEBUG
(declare-forward-reference write-error-text function)


;; In UTILITIES3

(declare-forward-reference managed-float-p-function function)
(declare-forward-reference managed-float-value-function function)

;; In LAUNCH

(declare-forward-reference current-system-name variable)


;; In STREAMS

(declare-forward-reference write-gensym-pathname function)


;; In FRAMES2a

(declare-forward-reference block-p-function function)
(declare-forward-reference framep-function function)


;; In FRAMES4 (& Stubbed in TW-PATCHES & GSI-PATCHES)

(declare-forward-reference write-name-denotation-components function)
(declare-forward-reference write-name-denotation-for-slot function)
(declare-forward-reference write-name-denotation function)

;; In GSI

(declare-forward-reference signal-gsi-maximum-gensym-string-length-error
                           function)

(declare-forward-reference signal-gsi-extend-current-gensym-string-error
                           function)

(declare-forward-reference signal-gsi-undefined-structure-method-error
                           function)

;; In PLACES

(declare-forward-reference denote-component-of-block function)


(declare-forward-reference twrite-designation-for-item function)

;; In G2-METERS
(declare-forward-reference report-simple-string-allocation function)
(declare-forward-reference report-simple-string-reclamation function)

;; In CHECK-KBS
#+development
(declare-forward-reference gensym-structure-or-frame-p function)

#+development
(declare-forward-reference
 *current-kb-specific-property-list-property-name* variable)

#+development
(declare-forward-reference ci function)

#+development
(declare-forward-reference lookup-global-or-kb-specific-property-value function)

#+development
(declare-forward-reference lookup-kb-specific-property-value function)

#+development
(declare-forward-reference workstation-this-is-on-function function)







;;;; Definition Database

;; This is actually first used below by the first use of
;; defvar-for-named-dynamic-extent in the section "Writing Gensym Strings".
;; Consider just moving this section to the module PRIMITIVES, which is
;; the module in which defvar-for-named-dynamic-extent is defined.
;; (MHD 5/30/91)


;;; Filename-of-module-being-loaded? is a special variable defined in the BOOTSTRAP module.
;;; When the system is being loaded, the variable is bound to the filename for the source
;;; file of the module currently being loaded.  This information can then be used by the
;;; function register-definition (below), in order to record the source file location of
;;; various definitions.  When not loading the system, the normal value for this variable
;;; is nil.

#-chestnut-3
(proclaim '(special filename-of-module-being-loaded?))
#+chestnut-3
(declaim (special filename-of-module-being-loaded?))



;;; `register-definition' registers definition in the lisp system's database for use by,
;;; e.g., editors (meta-.).  This feature is only for developers and is usually
;;; only implemented for their systems (i.e. lisp machines).

#+development
(defun register-definition (name type)
  name type                                                    ; not necessarily used
  #+:allegro (cl-user::record-source-file name :type type)
  #+:ccl (ccl:record-source-file name type)
  #+:lispworks-dspec
  (lispworks:record-definition (list name type)
			       (lispworks::current-pathname)
			       :check-redefinition-p nil)
  #+:mcl (ccl:record-source-file name type)
  #+Lucid
  (lcl:record-source-file name type))




;;;; Creating Gensym Strings




;;; Typically when dealing with strings, you will only need to know about a few
;;; routines.  They are obtain-gensym-string, copy-gensym-string, and
;;; reclaim-gensym-string.  There are two kinds of strings given out, those with
;;; and those without fill-pointers.  In general it is best if your code is
;;; prepared to deal with whichever of these have been given out.  Simple
;;; strings will be used when the length of the string is less than a certain
;;; limit, and above that it will give out fill-pointered strings with lengths
;;; rounded up to certain allocation sizes.  In general, this mechanism will
;;; hand out simple or fill-pointered strings of any length, but making strings
;;; longer than 64K is considered anti-social and harmful to memory management
;;; goals.

;;; Note that fill-pointered strings are called adjustable strings in this code,
;;; though Common Lisp adjustable arrays are not used.  In fact, adjustable
;;; arrays cannot be used, since adjusting an array may cons.

;;; There are three reclamation schemes for strings.  Small simple strings will
;;; be stored in lists within an array, one list per different length.  The
;;; upper limit for a small string is maximum-suggested-length-for-simple-text-
;;; strings.  All other simple strings are handled in such a way that simple
;;; strings of similar size will be kept in separate lists from simple strings
;;; of differing sizes.  This will be arranged such that the smallest string in
;;; a pool will be at smallest 50% of the size of the largest string in the
;;; pool.  This will somewhat limit the search for a simple string of the
;;; appropriate size.  When a fill-pointered string is allocated, it's actual
;;; size should be rounded up to some reasonable size over the required size.
;;; The allocation scheme used will round up so that at least 50% of the
;;; allocated size is used.

;;; There will be a maximum string size of 1Meg.  If you have code using 1 Meg
;;; strings, there is something obviously wrong, and it's not with the string
;;; allocators.  This value is stored in maximum-gensym-string-size.




;;; The parameter `string-allocation-schemes' contains an allocation scheme
;;; alist for use in determining appropriate rounding sizes of fill-pointered
;;; strings, and for pool selection for simple strings.  This allocation scheme
;;; always gets at least 50% usage out of the rounded up size.  See the
;;; documentation around managed-array-allocation-schemes for a further
;;; description of allocation schemes.  The parameter
;;; `maximum-gensym-string-length' contains a fixnum which is the longest
;;; allowable adjustable string length.

(def-memory-allocation-schemes string-allocation-schemes
    (128 32 16))

;;; The parameter `maximum-gensym-string-length' must be four times
;;; `maximum-text-string-length' in order to allow for the possibility of
;;; maximally large Unicode characters (four bytes each).
; changed to `defvar' to make LW api-tests happy
(defvar maximum-gensym-string-length (* 4 1048576))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter maximum-gensym-string-length-exceeded-message ;SS_ERROR: was defconstant
  "Attempting to allocate ~a element string, ~
   which is beyond the established maximum of ~a.")
)

(defmacro body-of-maximum-gensym-string-length-error (length)
  `(current-system-case
     ((ab telewindows)
      (error ,maximum-gensym-string-length-exceeded-message
                 ,length
                 maximum-gensym-string-length))
     (gsi (signal-gsi-maximum-gensym-string-length-error
            ,length
            maximum-gensym-string-length))))

(defun-simple maximum-gensym-string-length-error (length)
  (body-of-maximum-gensym-string-length-error length))




;;; The system variable `short-simple-gensym-strings' contains a simple vector of
;;; lists of simple gensym strings.  The system variable `long-simple-text-
;;; strings' contains a simple vector of lists of longer simple gensym strings.
;;; The system variable `adjustable-gensym-strings' contains a simple-vector of
;;; lists of adjustable gensym strings.  These variables make up the pools for all
;;; string allocation.  The system variables `short-simple-gensym-string-counts',
;;; `long-simple-gensym-string-counts', and `adjustable-gensym-string-counts' are
;;; simple vectors holding counts of the number of simple gensym strings allocated
;;; into the different pools of strings.

(defun-simple new-short-simple-gensym-string-vector (initial-element)
  (make-array
    (+F maximum-suggested-length-for-simple-gensym-strings 1)
    :initial-element initial-element))

(defun-simple new-partial-buffer-gensym-string-vector (initial-element)
  (make-array
    (+f (partial-buffer-pool-index-given-length
          maximum-gensym-string-length string-allocation-schemes)
        1)
    :initial-element initial-element))

(def-system-variable short-simple-gensym-strings utilities1
  (:funcall new-short-simple-gensym-string-vector nil) nil t)

(def-system-variable long-simple-gensym-strings utilities1
  (:funcall new-partial-buffer-gensym-string-vector nil) nil t)

(def-system-variable adjustable-gensym-strings utilities1
  (:funcall new-partial-buffer-gensym-string-vector nil) nil t)

(def-system-variable short-simple-gensym-string-counts utilities1
  (:funcall new-short-simple-gensym-string-vector 0) nil t)

(def-system-variable long-simple-gensym-string-counts utilities1
  (:funcall new-partial-buffer-gensym-string-vector 0) nil t)

(def-system-variable adjustable-gensym-string-counts utilities1
  (:funcall new-partial-buffer-gensym-string-vector 0) nil t)






;;; The cons pool for `string-pool' is used to allocate all conses used to hold
;;; lists of reclaimed strings.

(defconser string-pool)




;;; The following variables and functions are used to determine memory usage for
;;; the pool reports for simple-gensym-strings, which is defined just below the
;;; variables.

(def-system-variable simple-gensym-string-counter utilities1 0 nil t)

(def-system-variable simple-gensym-string-byte-use-counter utilities1 0 nil t)

(defun-simple sum-reclaimed-strings (vector)
  (loop with sum1 fixnum = 0
        for index from 0 below (length-of-simple-vector vector)
        do
    (incff sum1 (length (svref vector index)))
        finally (return sum1)))

(defun-simple outstanding-simple-gensym-strings ()
  (-f simple-gensym-string-counter
      (+f (sum-reclaimed-strings short-simple-gensym-strings)
          (sum-reclaimed-strings long-simple-gensym-strings))))

(defun-simple compute-memory-used-by-simple-gensym-strings ()
  simple-gensym-string-byte-use-counter)

(def-system-object-pool simple-gensym-strings simple-string
  simple-gensym-string-counter nil outstanding-simple-gensym-strings
  compute-memory-used-by-simple-gensym-strings)

;;; The function `obtain-simple-gensym-string' is used to allocate simple text
;;; strings of a given length.  The string returned will be pulled from the
;;; pools of reclaimed strings if possible, else a new one will be allocated.

(defun-simple obtain-simple-gensym-string (length)
  (let ((string
          (cond ((<=f length maximum-suggested-length-for-simple-gensym-strings)
                 (let ((pool? (svref short-simple-gensym-strings length)))
                   (if pool?
                       (prog1 (car-of-cons pool?)
                         (setf (svref short-simple-gensym-strings length)
                               (cdr-of-cons pool?))
                         (reclaim-string-pool-cons-macro pool?))
                       (allocate-new-simple-gensym-string length
                                                          #+translator nil))))
                ((>f length maximum-gensym-string-length)
                 (maximum-gensym-string-length-error length))
                (t
                 (let* ((pool-index (partial-buffer-pool-index-given-length
                                      length string-allocation-schemes)))
                   (declare (type fixnum pool-index))
                   (loop for trailing-cons? = nil then pool-cons
                         for pool-cons on (svref long-simple-gensym-strings pool-index)
                         do
                     (when (=f length (glength (car-of-cons pool-cons) t))
                       (if trailing-cons?
                           (setf (cdr trailing-cons?)
                                 (cdr-of-cons pool-cons))
                           (setf (svref long-simple-gensym-strings pool-index)
                                 (cdr-of-cons pool-cons)))
                       (return (prog1 (car-of-cons pool-cons)
                                 (reclaim-string-pool-cons-macro pool-cons))))
                         finally
                           (return #+translator
                                   (if (or (=f string-pool-number-to-malloc -1)
                                           (<f pool-index string-pool-number-to-malloc))
                                       (allocate-new-simple-gensym-string length nil)
                                       (progn
                                         (setf largest-non-malloced-string-pool-index
                                               (maxf largest-non-malloced-string-pool-index pool-index))
                                         (allocate-new-simple-gensym-string length t)))
                                   #-translator
                                   (allocate-new-simple-gensym-string length))))))))
    (note-allocate-cons string 'simple-gensym-string)
    string))





;;; The function `obtain-simple-gensym-string-of-quantized-length' is similar to
;;; obtain-simple-gensym-string except that the length is interpreted as the
;;; minimum, as opposed to the exact, length for the resulting string.  If the
;;; length is between 0 and maximum-suggested-length-for-simple-gensym-strings,
;;; this just returns the result of calling obtain-simple-text-string.
;;;
;;; For higher values of length this allocates a string at least one longer than
;;; length, rounded up to the next quantized length according to the allocation
;;; scheme alist string-allocation-schemes. In this case, the string is "null
;;; terminated" at the length position. I.e., the NUL character (code-char 0) is
;;; placed at the length position of the resulting string, thus ensuring that
;;; the string will be null-terminated after string contents before the length
;;; position gets filled in.  The null termination is useful for passing strings
;;; to C.  (Simple strings that are of exact length do not need null termination
;;; to be passed to C, presumably because they are internally null terminated
;;; one past their physical end in memory.)
;;;
;;; The idea here is to encourage optimal reuse of strings of various (minimum)
;;; lengths as they are allocated and reclaimed.  This is strongly recommended
;;; to be used by code that that can get by without having the active length of
;;; the string stored in string Lisp object itself.  (Simple gensym strings,
;;; unlike adjustable gensym strings or wide strings, are not adjustable: they
;;; have no fill pointer.)

(defun obtain-simple-gensym-string-of-quantized-length (length)
  (cond
    ((<=f length maximum-suggested-length-for-simple-gensym-strings)
     (obtain-simple-gensym-string length))
    (t
     (multiple-value-bind (rounded-up-length pool-index)
         (buffer-size-and-pool-for-partial-buffer
           (1+f length) string-allocation-schemes)
       (declare (ignore pool-index))
       (let ((string (obtain-simple-gensym-string rounded-up-length)))
         (setf (schar string length) #.(code-char 0))
         string)))))

;; Consider having long simple Gensym strings be stored directly in the same
;; vector as the short strings for lengths that align exactly with the quantized
;; lengths ("rounded-up-length"). This would improve efficiency of allocation
;; for these sizes, since they currently have to be searched for in a list of
;; long strings. (MHD 11/9/04)

;; Issue HQ-4881565 "Memory growth in G2 with Pivetal's Cortex Application"
;; gives some historical background on why we needed this.  (MHD 11/9/04)





;;; The variable `log-simple-string-data' is used to control a new
;;; facility used to gather some information on who is calling
;;; obtain-simple-gensym-string (as opposed to obtain-gensym-string,
;;; which gets an adjustable string for those that are longer than 64) for long
;;; lengths, since those essentially never get reused (since the lengths must
;;; match exactly). Heavy users of long simple-gensym-strings should probably be
;;; rewritten to use adjustable strings or byte-vector-16s or something, which
;;; have fill pointers, and can therefore round up the requested length and
;;; reuse reclaimed strings. This metering should help us find the
;;; heavy users. -alatto, 11/17/04

;; Can't turn this on yet, since strings get allocated before enough
;; of the system is loaded to print out backtraces. So we start with
;; this off, and turn it on in g2-final.

(defvar log-simple-string-data nil)

;;; The variable `log-simple-string-reclaims' determines whether the
;;; string metering facility, when turned on, logs only allocates (if
;;; the value is nil) or both allocates and reclaims (if non-nil).
;;; This is only checked if log-simple-string-data is non-nil.

(defvar log-simple-string-reclaims t)

;; The following defvars control the extent of the output of the metering
;; facility, to ensure that it doesn't spend so much time producing output
;; that it slows things down. They can be modified using the system
;; procedure g2-set-simple-string-metering-parameters.

(defvar min-string-length-to-report 2100)

;; This is really 1/frequency; if the value is n, this means "file a report on
;; every nth allocation and deallocation"

(defvar string-report-frequency 10)
(defvar string-allocations-until-next-report 0)
(defvar string-reclaims-until-next-report 0)
(defvar string-chars-to-print 200)

(defvar largest-non-malloced-string-pool-index -1)

;;; The variable `string-pool-number-to-malloc' determines which byte-vector-16s
;;; are heap allocated and which ones are malloced. Byte-vectors
;;; in this pool and larger ones are malloced. Set value to -1 to cause
;;; all byte-vector-16's to be heap allocated (current setting)
;;; Currently set not to malloc anything. To malloc strings of length
;;; greater than (for example) 100, change this to
;;; (defvar byte-vector-16-pool-number-to-malloc
;;;    (partial-buffer-pool-index-given-length
;;;       100 string-allocation-schemes))
;;; Note that this length will be rounded up to the next pool boundary.
;;; "Short strings" (those with length <=
;;; maximum-suggested-length-for-simple-gensym-strings, currently 64)
;;; are never malloced. This setting only applies to "long strings".

(defvar string-pool-number-to-malloc -1)

;;; Once a string of a given length has been allocated, it's too late to
;;; switch whether vectors of that length are malloced, since we have no way
;;; to distinguish a malloc'ed one from an unmalloced one. So this
;;; Returns nil if it's too late to change the allocation as requested, and the minimum length
;;; of string that will now be malloc'ed if it succeeds.
;;; All strings of length greater than the specified length, rounded up to
;;; a pool boundary, will be subsequently malloced.
;;; As a special case, a length argument of -1 will turn off all
;;; malloc'ing of strings.
(defun set-malloced-string-threshhold (length)
  (if (=f length -1)
      (setf string-pool-number-to-malloc -1)
      (multiple-value-bind (rounded-up-length pool-index)
          (buffer-size-and-pool-for-partial-buffer
            length
            string-allocation-schemes)
        (when (>f pool-index largest-non-malloced-string-pool-index)
          (setq string-pool-number-to-malloc pool-index))
        rounded-up-length)))

#+translator
(defun free-malloced-strings ()
  (when (>=f string-pool-number-to-malloc 0)
    (loop for pool-index from string-pool-number-to-malloc below (length long-simple-gensym-strings)
          do
      (let ((array-list (svref long-simple-gensym-strings pool-index)))
        (loop for array in array-list do
          (atomic-decff simple-gensym-string-counter)
          (atomic-decff simple-gensym-string-byte-use-counter
                 (bytes-per-simple-string (length array)))
          (free-malloced-array-internal array))
        (reclaim-string-pool-list array-list))
      (setf (svref long-simple-gensym-strings pool-index) nil)
      (setf (svref long-simple-gensym-string-counts pool-index) 0))))


;;; The function `allocate-new-simple-gensym-string' will cons a new simple text
;;; string of the requested length, incrementing the appropriate memory meters.

(defun-simple allocate-new-simple-gensym-string (length #+translator malloc-p)
  (when (>f length maximum-gensym-string-length)
    (maximum-gensym-string-length-error length))
  (atomic-incff simple-gensym-string-counter)
  (atomic-incff simple-gensym-string-byte-use-counter
         (bytes-per-simple-string length))
  (if (<=f length maximum-suggested-length-for-simple-gensym-strings)
      (incff (svref short-simple-gensym-string-counts length))
      (progn
        (incff (svref long-simple-gensym-string-counts
                      (partial-buffer-pool-index-given-length
                        length string-allocation-schemes)))
        (current-system-case
          (ab
            (when log-simple-string-data
              (when (>=f length min-string-length-to-report)
                (if (zerop string-allocations-until-next-report)
                    (progn
                      (report-simple-string-allocation length)
                      (setf string-allocations-until-next-report
                            (1-f string-report-frequency)))
                    (atomic-decff string-allocations-until-next-report))))))))
  #+translator
  (if malloc-p
      (malloc-string length)
      (with-permanent-string-creation
        (make-string length)))
  #-translator
  (with-permanent-string-creation
    (make-string length)))


;;; The function `reclaim-simple-gensym-string' reclaims simple-gensym-string and
;;; makes it available for use by by obtain-simple-gensym-string.

;;; In the development environment (at least) the first element of the string
;;; gets the letter "?" placed in them.  This is to help in recognizing
;;; reclaimed strings if they show up.

;;; In addition, one may bind `current-custom-reclamation-stamp?' to a string,
;;; the letters of which will be put into reclaimed simple gensym strings between
;;; the &'s, as much as fit.  This may be useful for tracking down sources of
;;; invalid string recycling.  The variable may be bound (or setqed) whether in
;;; development or in distribution.

(defvar current-custom-reclamation-stamp? nil)        ; nil or a string for stamping

(defun-void reclaim-simple-gensym-string (simple-gensym-string)
  (block reclaim-simple-gensym-string-1        ; to work around bogus
                                        ;   defun-void restriction! (MHD)
    (note-reclaim-cons simple-gensym-string 'simple-gensym-string)
    (let* ((gensym-string-length (glength simple-gensym-string t))
           (short-string? (<=f gensym-string-length
                               maximum-suggested-length-for-simple-gensym-strings))
           (string-pool-vector
             (if short-string? short-simple-gensym-strings long-simple-gensym-strings))
           (index (if short-string?
                      gensym-string-length
                      (partial-buffer-pool-index-given-length
                        gensym-string-length string-allocation-schemes))))
      (declare (type fixnum gensym-string-length index))
      (current-system-case
        (ab
          (when (and log-simple-string-data log-simple-string-reclaims)
            (when (>=f gensym-string-length min-string-length-to-report)
              (if (zerop string-reclaims-until-next-report)
                  (progn
                    (report-simple-string-reclamation simple-gensym-string
                                                      gensym-string-length)
                    (setf string-reclaims-until-next-report
                          (1-f string-report-frequency)))
                  (atomic-decff string-reclaims-until-next-report))))))
      ;; #+development maybe?
      (when (>f gensym-string-length 0)
        (setf (schar simple-gensym-string 0) #\&)
        (setf (schar simple-gensym-string (-f gensym-string-length 1)) #\&)
        (when current-custom-reclamation-stamp?
          (loop for i from 0 below (length current-custom-reclamation-stamp?)
                as j from 1 below (-f gensym-string-length 1)
                do
            (setf (schar simple-gensym-string j)
                  (char current-custom-reclamation-stamp? i)))))
      #+development
      (when (memq simple-gensym-string (svref string-pool-vector index))
        (cerror
          "Continue. (This is fine to do once the problem's been looked at.)"
          "Attempt to recycle an already recycled string! Please show this ~
            to a developer!  String: ~s"
          simple-gensym-string)
        (return-from reclaim-simple-gensym-string-1 nil))
      #+translator
      (if
        (and
          free-malloced-arrays
          (<=f string-pool-number-to-malloc index)
          (not (=f string-pool-number-to-malloc -1))
          (not short-string?))
        (progn
          (atomic-decff simple-gensym-string-counter)
          (atomic-decff simple-gensym-string-byte-use-counter
                 (bytes-per-simple-string (length simple-gensym-string)))
          (decff (svref long-simple-gensym-string-counts index))
          (free-malloced-array-internal simple-gensym-string))
        (setf (svref string-pool-vector index)
              (string-pool-cons-macro simple-gensym-string
                                      (svref string-pool-vector index))))
      #-translator
      (setf (svref string-pool-vector index)
            (string-pool-cons-macro simple-gensym-string
                                    (svref string-pool-vector index))))))

;;; The following variables and functions are used to determine memory usage for
;;; the pool reports for adjustable-gensym-strings, which is defined just below
;;; the variables.

(def-system-variable adjustable-gensym-string-counter utilities1 0 nil t)

(def-system-variable adjustable-gensym-string-byte-use-counter utilities1 0 nil t)

(defun-simple outstanding-adjustable-gensym-strings ()
  (-f adjustable-gensym-string-counter
      (sum-reclaimed-strings adjustable-gensym-strings)))

(defun-simple compute-memory-used-by-adjustable-gensym-strings ()
  adjustable-gensym-string-byte-use-counter)

(def-system-object-pool adjustable-gensym-strings string
  adjustable-gensym-string-counter nil outstanding-adjustable-gensym-strings
  compute-memory-used-by-adjustable-gensym-strings)




;;; The function `obtain-adjustable-gensym-string' returns an adjustable text
;;; string.  The new string's fill-pointer is initialized to zero.  The initial
;;; size will be some reasonable length for many formatting needs.

(declare-side-effect-free-function obtain-adjustable-gensym-string)

(defun-simple obtain-adjustable-gensym-string ()
  (obtain-long-enough-adjustable-gensym-string 1024))




;;; The function `obtain-long-enough-adjustable-gensym-string' allocates an
;;; adjustable gensym string of a length greater than or equal to size with
;;; undefined initial contents.  The new string's fill-pointer is initialized to
;;; length, and the contents of the string are undetermined.

(defun-simple obtain-long-enough-adjustable-gensym-string (length)
  (when (>f length maximum-gensym-string-length)
    (maximum-gensym-string-length-error length))
  (let* ((pool-index (partial-buffer-pool-index-given-length
                       length string-allocation-schemes))
         (pool? (svref adjustable-gensym-strings pool-index))
         (string (if pool?
                     (prog1 (car-of-cons pool?)
                       (setf (svref adjustable-gensym-strings pool-index)
                             (cdr-of-cons pool?))
                       (reclaim-string-pool-cons-macro pool?))
                     (allocate-new-adjustable-gensym-string
                       (buffer-size-for-partial-buffer
                         length string-allocation-schemes)))))
    (declare (type fixnum pool-index))
    (setf (fill-pointer string) length)
    #+chestnut-trans
    (setf (char string length) (code-char 0))
    (note-allocate-cons string 'adjustable-gensym-string)
    string))

(defun-simple allocate-new-adjustable-gensym-string (length)
  (atomic-incff adjustable-gensym-string-counter)
  (atomic-incff adjustable-gensym-string-byte-use-counter
         (bytes-per-adjustable-string length))
  (atomic-incff (svref adjustable-gensym-string-counts
                (partial-buffer-pool-index-given-length
                 length string-allocation-schemes)))
  (with-permanent-string-creation
    (make-array
      length
      :element-type (gensym-string-char-type)
      :fill-pointer length
      :adjustable t))) ; needed by with-output-to-gensym-string

;; CLtL says (p 23) that string-char has been removed as a Common Lisp type.  CLtL
;; is not clear (p 460) on what should take its place.  The issue is fairly moot,
;; since our Lisp (currently Chestnut) supports string-char, but character is a
;; good candidate when our Lisp ceases to support string-char.  jh, 10/4/91.

;; This function used to pass an ":adjustable t" argument to make-array.  Note
;; that this was always bogus, since we never adjust arrays (see CLtL on
;; adjust-array), we only ever modify the fill-pointer of arrays.  -jra 7/26/93




;;; The function `reclaim-adjustable-gensym-string' reclaims an adjustable text
;;; string and makes it available for use by by obtain-long-enough-adjustable-
;;; gensym-string.

;;; In the development environment (at least) the first element of the
;;; string gets the letter "?" placed in them.  This is to help in recognizing
;;; reclaimed strings if they show up.

(defun-simple reclaim-adjustable-gensym-string (adjustable-gensym-string)
  (note-reclaim-cons adjustable-gensym-string 'adjustable-gensym-string)
  (let* ((length (array-dimension (the string adjustable-gensym-string) 0))
         (pool-index (partial-buffer-pool-index-given-length
                       length string-allocation-schemes)))
    (declare (type fixnum pool-index))
    #+development
    (when (memq adjustable-gensym-string (svref adjustable-gensym-strings pool-index))
      (cerror
        "Continue. (This is fine to do once the problem's been looked at.)"
        "Attempt to recycle an already recycled string! Please show this ~
            to a developer!  String: ~s"
        adjustable-gensym-string)
      (return-from reclaim-adjustable-gensym-string nil))
    ;; #+development maybe?
    (when (>f length 0)
      (setf (char adjustable-gensym-string 0) #\?))
    (setf (svref adjustable-gensym-strings pool-index)
          (string-pool-cons-macro
            adjustable-gensym-string
            (svref adjustable-gensym-strings pool-index)))))




;;; The substitution macro `obtain-gensym-string' allocates a simple or adjustable
;;; gensym string of a length equal to size with undefined initial contents.

(def-substitution-macro obtain-gensym-string (length)
  (current-system-case
    (gsi (obtain-simple-gensym-string length))
    (t (if (>f length maximum-suggested-length-for-simple-gensym-strings)
           (obtain-long-enough-adjustable-gensym-string length)
           (obtain-simple-gensym-string length)))))




;;; The substitution macro `reclaim-gensym-string' takes a gensym-string as its
;;; argument and reclaims it back into the available pools.

(def-substitution-macro reclaim-gensym-string-1 (gensym-string)
  (if (simple-string-p gensym-string)
      (reclaim-simple-gensym-string gensym-string)
      (reclaim-adjustable-gensym-string gensym-string)))

(defun-void reclaim-gensym-string (gensym-string)
  (reclaim-gensym-string-1 gensym-string))






;;; The substitution macro `reclaim-if-gensym-string' takes a single argument.  If
;;; that argument is a string, it will be reclaimed back in to the gensym string
;;; pools.  Otherwise, it does nothing.

(def-substitution-macro reclaim-if-gensym-string (thing)
  (when (gensym-string-p thing)
    (reclaim-gensym-string thing)))

(defun reclaim-if-gensym-string-function (thing)
  (reclaim-if-gensym-string thing))



;;; The substitution macro `copy-if-gensym-string' takes one argument, and returns
;;; a copy if the thing is a string, else it returns the thing.

(def-substitution-macro copy-if-gensym-string (thing)
  (if (gensym-string-p thing)
      (copy-gensym-string thing)
      thing))



;;; The function `reclaim-gensym-strings-in-list' reclaims all gensym-string which
;;; are elements of its argument which is assumed to be a list. Only
;;; gensym-strings which are on the top level are reclaimed.

(defun-void reclaim-gensym-strings-in-list (list)
  (loop for gensym-string in list do
    (reclaim-if-gensym-string gensym-string)))





;;; `gensym-string-substring' returns a simple gensym string containing the
;;; substring of string given by the start and end arguments.  String may be
;;; any type of (Common Lisp) string, in particular, any type of gensym string.

(defun gensym-string-substring (string start? end?)
  (loop with string-is-simple? = (simple-gensym-string-p string)
        with end = (or end? (glength string string-is-simple?))
        with start = (or start? 0)
        with new-string = (obtain-simple-gensym-string (-f end start))
        for i from (or start? 0) below end
        as j from 0
        do (setf (schar new-string j) (gchar string i string-is-simple?))
        finally (return new-string)))

;; Consider having separate loops for the simple and non-simple cases, as is done in
;; copy-gensym-string, to gain a bit of speed.


;; Other types of operations to consider adding here:
;;
;;    tests for equality (=, >, >=, <, <=, /=)
;;
;;    case conversion


;;; The function `reclaim-gensym-tree-with-text-strings' is a utility used to
;;; reclaim a tree of gensym conses as gensym conses, also reclaiming the text
;;; strings therein as text strings.  Note that special evaluation-value,
;;; slot-value, and phrase conses are NOT specially handled (with care) here.

;;; The function `copy-gensym-tree-with-text-strings' is similar but copies
;;; rather than reclaims conses and text strings.

(defun-void reclaim-gensym-tree-with-text-strings (tree)
  (loop for tail = tree then next-tail
        while (consp tail)
        for car = (car tail)
        for next-tail = (cdr tail)
        do (reclaim-gensym-tree-with-text-strings car)
           (reclaim-gensym-cons tail)
        finally

          (cond ((text-string-p tail)
                 (reclaim-text-string tail))
                ((gensym-string-p tail)
                 (reclaim-gensym-string tail)))))

;; Now used for return values in workstation contexts (MICE).  This abstraction
;; is probably needed elsewhere, and should be elaborated!  Consider `gensym
;; value' (ala slot value and evaluation value). Also, it had a bug prior to
;; this day: it did not properly reclaim text strings stored in the cdr of
;; any cons.  (MHD 2/29/00)

;; jh, 11/7/94.  Cloned reclaim-gensym-tree-with-text-strings from the
;; macroexpansion of the defconser for gensym-conses in UTILITIES0.  Since this
;; is the only place where we have to reclaim text-strings at the leaves of a
;; pooled cons tree (so far), there is no need to abstract this and incorporate
;; it into defconser itself.

(defun copy-gensym-tree-with-text-strings (tree)
  (cond
    ((consp tree)
     (gensym-cons
       (copy-gensym-tree-with-text-strings (car tree))
       (copy-gensym-tree-with-text-strings (cdr tree))))
    ((or (text-string-p tree) (gensym-string-p tree))
     (copy-text-string tree))
    (t tree)))





;;;; Dealing with Null-terminated Strings




;;; A `null-terminated string' is a (lisp) string that logically ends with the
;;; `null character', i.e., the Ascii character named NUL, whose code is 0.  The
;;; operations below are generally written conservately in that they do not
;;; absolutely require null-terminated strings -- their behavior in the face of
;;; non-null- terminated strings is documented below.

;;; Return-gensym-string-from-null-terminated-string is only to be called from
;;; SEQUENCES1; see copy-null-terminated-string-as-gensym-string, which does the
;;; much the same thing ... If string is not null-terminated, this simply returns
;;; a copy of string.

(defmacro return-gensym-string-from-null-terminated-string-1
          (string do-not-reclaim-string-p)
  `(prog1 (gensym-string-substring
            ,string 0
            (loop with maximum-index = (-f (length ,string) 1)
                  for i from 0                        ; end of NUL terminated string
                  do
              (when (=f (char-int (schar ,string i)) 0)
                (return i))
              (when (>=f i maximum-index)
                (return (+f i 1)))))
          ,@(if (not do-not-reclaim-string-p)
               `((reclaim-gensym-string ,string)))))

(defmacro return-gensym-string-from-null-terminated-string
          (string &optional (do-not-reclaim-string-p nil))
  (if (symbolp string)
      `(return-gensym-string-from-null-terminated-string-1 ,string ,do-not-reclaim-string-p)
      (let* ((string-var '#:string))
        `(return-gensym-string-from-null-terminated-string-1
           ,string-var
           ,do-not-reclaim-string-p))))





;;; Copy-null-terminated-string-as-gensym-string ... If string is not
;;; null-terminated, this simply returns a copy of string.

(defun copy-null-terminated-string-as-gensym-string (string)
  (let* ((length-if-null-terminated? (length-of-null-terminated-string string)))
    (if length-if-null-terminated?
        (gensym-string-substring string 0 length-if-null-terminated?)
        (copy-gensym-string string))))





;;; `Length-of-null-terminated-string' ... returns nil if no null character
;;; (i.e., the Ascii character NUL, code 0) is found in string.  Otherwise,
;;; notice that for a result i, (char string i) is the character NUL.

(defun length-of-null-terminated-string (string)
  (loop with string-is-simple? = (simple-gensym-string-p string)
        with string-length = (glength string string-is-simple?)
        for i from 0 below string-length
        when (char= (gchar string i string-is-simple?)
                    #.(code-char 0))
          return i))






;;; `Copy-null-terminated-string' copies all characters in the source string
;;; from the 0th character up to and including the null character into the
;;; target string.  The target string has to be at least the length of the
;;; source string.  The source string must be null-terminated.

(def-substitution-macro copy-null-terminated-string (source-string target-string)
  (loop for index from 0 below (length source-string)
        as source-char = (char source-string index)
        do (setf (char target-string index) source-char)
        until
          (char= source-char #.(code-char 0))
        finally
          (return index)))

;; This is at present only used by nsleep-with-key-error-trap, an I386 security
;; function in SEQUENCES1.  It probably does not need to be a macro, but there
;; might be a security reason for it being one.  (MHD 12/27/91)





;;;; Dealing with Requirements for Simple Strings



;;; The function `require-simple-gensym-string' checks if its arg is a simple text
;;; string.  If it is, the arg is simple returned.  If not, this returns the
;;; result of copying the arg as a simple gensym string, and the arg is reclaimed.

(defun-simple require-simple-gensym-string (gensym-string)
  (if (simple-gensym-string-p gensym-string)
      gensym-string
      (prog1 (copy-gensym-string gensym-string) ; makes a simple-gensym-string copy
        (reclaim-gensym-string gensym-string))))





;;;; Writing Gensym Strings




;;; `Twith-output-to-gensym-string' returns a new gensym string, the contents of which
;;; are produced by a sequences of invocations of twrite, tformat, et al. within
;;; body.  Each of these invocations ultimately reduces to the writing of simple
;;; characters by means of twrite-char.
;;;
;;; This macro has the important restriction that it cannot handle
;;; non-ISO-8859-1 (Latin1) characters.  This means it must be used with caution
;;; around arbitrary calls to twrite functions, in particular those that can
;;; write user-spelled symbols in almost any script.  The alternative is to use
;;; twith-output-to-text-string, and then translate the resulting text string to
;;; an appropriately encoded gensym or wide string.
;;;
;;; This macro has been denigrated except for use in various semi-primitive
;;; level facilities fairly close to an IO boundary.

(def-named-dynamic-extent outputting-to-gensym-string
  (module utilities1)
  (unwind? nil))

(defvar-of-named-dynamic-extent current-gensym-string                  outputting-to-gensym-string) ; a simple gensym string

(defvar-of-named-dynamic-extent fill-pointer-for-current-gensym-string outputting-to-gensym-string)

(defvar-of-named-dynamic-extent total-length-of-current-gensym-string  outputting-to-gensym-string)


;;; `Current-twriting-output-type' is a special bound by both
;;; twith-output-to-gensym-string and twith-output-to-wide-string.
;;;
;;; If it is bound to WIDE-STRING, it should get a wide character as its
;;; argument, and it writes it to the current wide string to eventually be
;;; copied as the value of twith-output-to-wide-string.
;;;
;;; Otherwise, current-twriting-output-type should be GENSYM-STRING.  In this case
;;; it takes a simple character and writes it to the simple string that will
;;; eventually be copied either as a simple or adjustable string, to be the
;;; value of either twith-output-to-gensym-string.

(defvar current-twriting-output-type)

(defun-substitution-macro get-current-twriting-output-type ()
  current-twriting-output-type)

(defun-substitution-macro careful-get-current-twriting-output-type ()
  (if (boundp 'current-twriting-output-type)
      current-twriting-output-type
      nil))



#+development
(defvar standard-output-trap (make-synonym-stream '*terminal-io*))
; We grew tired of this complaining all the time when debugging
; now that we doen't make this mistake so often.  (ben/mhd 5/21/91)
;        ;a (Lisp Machine) stream to be used as value
;        #'(lambda (op &rest args)       ; of *standard-output* that signals an error
;            (declare (ignore op args))        ; when written to. #+Development only.
;            (cerror "Ignore this problem" "Attempt to write to standard output ~
;                     within ~
;                     with-current-gensym-string!  This is usually a bug and/or ~
;                     involves trying to ~
;                     execute debugging print statements.")))


(defmacro with-designated-current-gensym-string (gensym-string &body body)
  `(let* ((current-gensym-string ,gensym-string)
          (fill-pointer-for-current-gensym-string 0)
          (total-length-of-current-gensym-string 2048)
          (current-twriting-output-type 'gensym-string)) ; see twrite-char
     (progn . ,body)))

(defmacro with-current-gensym-string (&body body)
  `(with-designated-current-gensym-string
       (obtain-simple-gensym-string 2048)
     ,@body))

(defmacro twith-output-to-gensym-string (&body body)
  `(with-current-gensym-string
     (progn . ,body)
     (copy-out-current-gensym-string)))

(def-concept start-output-to-gensym-string)
(def-concept finish-output-to-gensym-string)

(defmacro twith-possible-output-to-gensym-string (&body body)
  `(macrolet ((start-output-to-gensym-string ()
                `(setq current-gensym-string (obtain-simple-gensym-string 2048)))
              (finish-output-to-gensym-string ()
                `(copy-out-current-gensym-string)))
     (with-designated-current-gensym-string nil
       (progn . ,body))))

(defmacro twith-output-to-designated-gensym-string (gensym-string &body body)
  `(with-designated-current-gensym-string ,gensym-string
     ,@body))



;;; `Twith-output-to-then-use-of-gensym-string' is like twith-output-to-gensym-string
;;; except that (1) the special variable, current-gensym-string, is bound during
;;; the execution of body and is available to the caller; (2) the special
;;; variable, fill-pointer-for-current-gensym-string, is bound during the
;;; execution of body and is available to the caller; (3) it returns the results
;;; of evaluating the last form in body; and (4) the output string is
;;; automatically reclaimed upon exiting the body.  This can return at most
;;; 6 values.

;;; To copy the filled portion of current-gensym-string, use the function copy-
;;; current-gensym-string.

(defmacro twith-output-to-then-use-of-gensym-string (&body body)
  (let* ((arg1 (gensym))
         (arg2 (gensym))
         (arg3 (gensym))
         (arg4 (gensym))
         (arg5 (gensym))
         (arg6 (gensym)))
    `(with-current-gensym-string
       ;; Unwind-protect was supposed to fix the consing problem in Lucid's
       ;; multiple-value-prog1, but it doesn't!  So we just use
       ;; multiple-value-bind and values, keeping in mind the number of values
       ;; to be returned is limited.  Fix someday!
       (multiple-value-bind (,arg1 ,arg2 ,arg3 ,arg4 ,arg5 ,arg6)
        (progn . ,body)
        (reclaim-simple-gensym-string current-gensym-string)
        (values ,arg1 ,arg2 ,arg3 ,arg4 ,arg5 ,arg6)))))

;; This is used, at present, in get-next-token-if-available in module EDIT and in
;; read-element-for-kb in module FILES.



;;; `Copy-current-gensym-string' makes a gensym-string copy of current-gensym-string
;;; and returns the copy.  If truncate-if-overly-long? is specified, the copy
;;; will be truncated if necessary so that it can be a simple gensym string
;;; whose length does not exceed maximum-suggested-length-for-simple-gensym-strings.

;;; `Copy-out-current-gensym-string' makes a gensym-string copy of current-gensym-string
;;; and returns the copy after reclaiming the original.

;;; If the string to be copied is "short enough", the copy will be a simple text
;;; string of exactly the right size.  Otherwise, it will be an adjustable text
;;; string of sufficient size.  (Adjustable gensym strings exist only in certain
;;; quantized sizes to prevent "fragmentation" of gensym string pools.)

(defun-simple copy-current-gensym-string (truncate-if-overly-long?)
  (let* ((length fill-pointer-for-current-gensym-string)
         (simple?
           (current-system-case
             (gsi truncate-if-overly-long? t)
             (t (or (<=f length maximum-suggested-length-for-simple-gensym-strings)
                    (if truncate-if-overly-long?
                        (loop with i = 0
                              do (setq length i)
                                 (skip-past-gensym-character
                                   current-gensym-string i t)
                              until
                              (>f i maximum-suggested-length-for-simple-gensym-strings)
                              finally
                                (return t)))))))
         (new-gensym-string
           (if simple?
               (obtain-simple-gensym-string length)
               (let ((adjustable-gensym-string
                       (obtain-long-enough-adjustable-gensym-string length)))
                 (setf (fill-pointer adjustable-gensym-string) length)
                 adjustable-gensym-string))))
    (if simple?
        (loop for i from 0 below length
              do (setf (schar new-gensym-string i) (schar current-gensym-string i)))
        (loop for i from 0 below length
              do (setf (char new-gensym-string i) (schar current-gensym-string i))))
    new-gensym-string))

(defun-simple copy-out-current-gensym-string ()
  (prog1 (copy-current-gensym-string nil)
    ;; changed from reclaim-simple-gensym-string to keep leaks from being reported
    ;; some question as to whether or not they were actually there -rdf, 11/17/94
    (reclaim-gensym-string current-gensym-string)))



;;; `With-output-to-gensym-string' executes body with *standard-output* bound to an
;;; output stream for a freshly allocated, ready-to-be-written-in adjustable
;;; gensym string, and then returns that or an equivalent gensym string.  The body
;;; typically contains such forms as (format t ...) and (write ...).

;;; Note that the body of with-output-to-gensym-string is within a
;;; with-dynamic-creation form.

(defmacro with-output-to-gensym-string ((stream) &body body)
  (let ((adjustable-gensym-string '#:adjustable-gensym-string))
    `(let ((,adjustable-gensym-string (obtain-adjustable-gensym-string)))
       (setf (fill-pointer ,adjustable-gensym-string) 0)
       (with-dynamic-creation
         (with-output-to-string (,stream ,adjustable-gensym-string)
           . ,body))
       ;; If the resulting string is "short enough", i.e. of a size likely to be
       ;;    used again and hence worth ultimately recycling, make it be a simple
       ;;    gensym string; otherwise return an adjustable gensym string.
       (if (not (>f (fill-pointer ,adjustable-gensym-string)
                    maximum-suggested-length-for-simple-gensym-strings))
           (prog1 (copy-gensym-string ,adjustable-gensym-string)
                  (reclaim-adjustable-gensym-string ,adjustable-gensym-string))
           ,adjustable-gensym-string))))

;; Eliminate in favor of twith-output-to-gensym-string, which avoids cons leakage!








;;;; Copying and Case-Converting Gensym Strings




;;; `Copy-gensym-string' makes a simple-gensym-string copy of string.  String may be
;;; any type of (Common Lisp) string or any type of gensym string.

(declare-side-effect-free-function copy-gensym-string)

(defun-simple copy-gensym-string (string)
  (let* ((string-is-simple? (simple-gensym-string-p string))
         (string-length (glength string string-is-simple?))
         (new-gensym-string (obtain-simple-gensym-string string-length)))
    (if string-is-simple?
        (loop for i from 0 below string-length
              do (setf (schar new-gensym-string i) (schar string i)))
        (loop for i from 0 below string-length
              do (setf (schar new-gensym-string i) (char string i))))
    new-gensym-string))



;;; `Copy-partial-gensym-string' makes a simple-gensym-string copy of the leading part of
;;; string where part-length indicates the size of the leading part.  String may be
;;; any type of (Common Lisp) string or any type of gensym string.

(declare-side-effect-free-function copy-partial-gensym-string)

(defun-simple copy-partial-gensym-string (string part-length)
  (let* ((string-is-simple? (simple-gensym-string-p string))
         (new-gensym-string (obtain-simple-gensym-string part-length)))
    (if string-is-simple?
        (loop for i from 0 below part-length
              do (setf (schar new-gensym-string i) (schar string i)))
        (loop for i from 0 below part-length
              do (setf (schar new-gensym-string i) (char string i))))
    new-gensym-string))



;;; `Copy-gensym-string-portion' makes a simple-gensym-string copy of the part of
;;; string from start below end.  String may be any type of (Common Lisp) string or
;;; any type of gensym string.

(declare-side-effect-free-function copy-gensym-string-portion)

(defun-simple copy-gensym-string-portion (string start end)
  (let* ((string-is-simple? (simple-gensym-string-p string))
         (part-length (-f end start))
         (new-gensym-string (obtain-simple-gensym-string part-length)))
    (if string-is-simple?
        (loop for i from start below end
              for j from 0
              do (setf (schar new-gensym-string j) (schar string i)))
        (loop for i from start below end
              for j from 0
              do (setf (schar new-gensym-string j) (char string i))))
    new-gensym-string))



;;; `Copy-gensym-string-into-simple-or-adjustable-gensym-string' makes a
;;; simple-gensym-string or adjustable-gensym-string copy of string.  The string
;;; argument is either simple or adjustable.

(declare-side-effect-free-function
  copy-gensym-string-into-simple-or-adjustable-gensym-string)

(defun-simple copy-gensym-string-into-simple-or-adjustable-gensym-string (string)
  (let* ((string-is-simple? (simple-gensym-string-p string))
         (string-length (glength string string-is-simple?))
         ;; Obtains adjustable or simple gensym strings.
         (new-gensym-string (obtain-gensym-string string-length))
         (new-string-is-simple? (simple-gensym-string-p new-gensym-string)))
    (cond
      (string-is-simple?
       (cond
         (new-string-is-simple?
          (loop for i from 0 below string-length
                do (setf (schar new-gensym-string i) (schar string i))))
         (t
          (loop for i from 0 below string-length
                do (setf (char new-gensym-string i) (schar string i))))))
      (new-string-is-simple?
       (loop for i from 0 below string-length
             do (setf (schar new-gensym-string i) (char string i))))
      (t
       (loop for i from 0 below string-length
             do (setf (char new-gensym-string i) (char string i)))))
    new-gensym-string))

;; Note that a better name for the above function would be copy-gensym-string, but
;; that name is already used.  At some point, we should rename the above
;; function.  Then, the current copy-gensym-string should be renamed to something
;; like copy-simple-gensym-string, which is what it does.  This is too big a task
;; to do right now.  There are many callers to copy-gensym-string.  - cpm, 1/10/94
;;
;; -- OK, just to be clear: the reason why copy-gensym-string cannot just be used
;; is simply that it warrants that its result will be a simple gensym string, and
;; therefore, it would be a daunting task to locate all the callers that rely
;; upon that, and therefore access the result using schar.



;;; `Copy-portion-of-string-into-simple-gensym-string' copies the portion of
;;; source-string specified by source-start and source-end into the portion of
;;; destination-string starting at destination-start.  Destination-string must
;;; be simple and must be long enough to hold all the characters to be copied.

(defun copy-portion-of-string-into-simple-gensym-string
       (source-string source-start source-end
        destination-string destination-start)
  (let ((source-string-is-simple? (simple-gensym-string-p source-string)))
    (if source-string-is-simple?
        (loop as i from source-start below source-end
              as j from destination-start
              do (setf (schar destination-string j) (schar source-string i)))
        (loop as i from source-start below source-end
              as j from destination-start
              do (setf (schar destination-string j) (char source-string i))))))

;; This function is useful for G2 text insertion and deletion operations.



;;; `Copy-portion-of-string-into-gensym-string' copies the portion of
;;; source-string specified by source-start and source-end into the portion of
;;; destination-string starting at destination-start.  Destination-string does
;;; not need be simple and must be long enough to hold all the characters to be
;;; copied.

(defun copy-portion-of-string-into-gensym-string
       (source-string source-start source-end
        destination-string destination-start)
  (let ((source-string-is-simple? (simple-gensym-string-p source-string)))
    (if source-string-is-simple?
        (loop as i from source-start below source-end
              as j from destination-start
              do (setf (char destination-string j) (schar source-string i)))
        (loop as i from source-start below source-end
              as j from destination-start
              do (setf (char destination-string j) (char source-string i))))))



(defvar write-symbols-parsably? nil)




;;;; Tools for Deriving Substrings


;;; NOTE: all of the functions in this section at present do not work in terms
;;; of Gensym gensym strings, but rather in terms of ISO 646/ASCII/Common Lisp
;;; strings ("ASCII Strings").  In principle, Gensym gensym-string versions of all
;;; of these functions can and should be written.
;;;
;;; Since Common Lisp strings are in use, it's reasonable to use non-Gensym
;;; characters, such as Tab.  Also, Gensym escape sequences will not be
;;; recognized, and generally not preserved.
;;;
;;; To implement these operations, these functions sometimes use primitives that
;;; are for gensym-strings, based on low-level assumptions and knowledge of their
;;; internals, but this is just an implementational detail.
;;;
;;; However gensym strings allocation and reclamation is handled through the same
;;; primitives as for Gensym gensym strings (i.e., obtain-gensym-string and
;;; reclaim-gensym-string, et al.)  Where these strings must create new strings
;;; (or reclaim strings), it may be assumed that they are being allocated out of
;;; gensym string pools, and are to be reclaimed (or allocated) using the
;;; appropriate gensym-string operations previously mentioned.
;;;
;;; NOTE: The functions in this section differ from those in the following
;;; section, "Handy String Functions", in that the later set is intended for
;;; offline use, i.e., at macro definition time, and not at runtime.  They
;;; also allocate using dynamic, non-pooled memory.  There may be some there
;;; that will want to belong here, and they can just be moved over, possibly
;;; with appropriate name changes, on an as-needed basis.





;;; `Position-in-gensym-string' and `find-in-gensym-string' provide highly
;;; efficient implementations of a simplified subset of the position and
;;; find Common Lisp sequence functions.
;;;
;;; They are open to the addition more and more of the original options provided
;;; by their Common Lisp counterparts, but for now they differ in that (1) they
;;; take a string instead of a general sequence; (2) they take a character
;;; instead of a sequence element of a general type; (3) the test function is
;;; always char= (note that this implies that it is case-sensitive); (4) none of
;;; the other args from these functions Common Lisp counterparts are supported;
;;; (5) the call corresponds to a call to the Common Lisp counterpart function
;;; in which all other (keyword or optional) arguments from CL, such as start,
;;; end, predicate, from-end, etc., are unspecified.
;;;
;;; `Position-of-gensym-character-in-list' and `find-gensym-character-in-list'

(defun-simple position-in-gensym-string (character gensym-string)
  (declare (eliminate-for-gsi))
  (if (simple-gensym-string-p gensym-string)
      (loop with len = (length gensym-string)
            for i from 0 below len
            for ch = (schar gensym-string i)
            when (char= ch character)
              return i)
      (loop with len = (length gensym-string)
            for i from 0 below len
            for ch = (char gensym-string i)
            when (char= ch character)
              return i)))

(defun-simple find-in-gensym-string (character string)
  (declare (eliminate-for-gsi))
  (loop with string-is-simple? = (simple-gensym-string-p string)
        for i from 0 below (glength string string-is-simple?)
        as char = (gchar string i string-is-simple?)
        when (char= char character)
          return char))

(defun-simple find-gensym-character-in-list (character list)
  (declare (eliminate-for-gsi))
  (loop as i from 0
        for char in list
        when (char= char character)
          return char))


(defun-simple find-gensym-character-in-sequence (character bag)
  (declare (eliminate-for-gsi))
  (cond
    ((gensym-string-p bag)
     (find-in-gensym-string character bag))
    ((listp bag)
     (find-gensym-character-in-list character bag))
    (t (find character bag ':test #'char=))))




;;; `Position-of-ascii-character-not-in-bag' ...

(defun-allowing-keywords position-of-ascii-character-not-in-bag
    (string bag &key start end)
  (declare (eliminate-for-gsi))
  (loop with string-is-simple? = (simple-gensym-string-p string)
        for i from (or start 0)
              below (or end (glength string string-is-simple?))
        when (not (find-gensym-character-in-sequence
                    (gchar string i string-is-simple?)
                    bag))
          do (return i)))


;;; `Position-of-ascii-character-in-bag' ...

(defun-allowing-keywords position-of-ascii-character-in-bag
    (string bag &key start end)
  (declare (eliminate-for-gsi))
  (loop with string-is-simple? = (simple-gensym-string-p string)
        for i from (or start 0)
              below (or end (glength string string-is-simple?))
        when (find-gensym-character-in-sequence
               (gchar string i string-is-simple?)
               bag)
          do (return i)))


(defun-allowing-keywords position-of-ascii-character-not-in-bag-from-end
    (string bag &key start end)
  (declare (eliminate-for-gsi))
  (loop with string-is-simple? = (simple-gensym-string-p string)
        for i from (-f (or end (glength string string-is-simple?)) 1)
              downto (or start 0)
        when (not (find-gensym-character-in-sequence
                    (gchar string i string-is-simple?)
                    bag))
          do (return i)))

;; Compare this with CL's POSITION called with just the right args:
;;
;; -> (position-of-ascii-character-not-in-bag-from-end "  foobar      " " " :start 6  :end 10)
;; 7
;; -> (position-of-ascii-character-not-in-bag-from-end "  foobar      " " " :start 8  :end 10)
;; NIL
;; -> (position-of-ascii-character-not-in-bag-from-end "  foobar      " " ")
;; 7
;;
;; -> (position  #\space "  foobar      "  :from-end t :test-not #'char= :start 6  :end 10)
;; 7
;; -> (position  #\space "  foobar      "  :from-end t :test-not #'char= :start 8  :end 10)
;; NIL
;; -> (position  #\space "  foobar      "  :from-end t :test-not #'char=)
;; 7



;;; `Parse-ascii-text-line-into-list-of-ascii-strings' returns a list made up of
;;; gensym conses and of the gensym strings that make up "fields" of
;;; ascii-text-line, or the subsequence thereof bounded by start and end, if
;;; specified.  Start defaults to 0, and end defaults to the length of
;;; ascii-text-line.
;;;
;;; Empty-strings-nil, if true, provides the convenience of producing nils where
;;; it would otherwise have to come up with empty (zero-length) strings. (not
;;; implemented as of 4/19/95)
;;;
;;; It is assumed that ascii-text-line contains no newline characters, but that is not
;;; tested for.
;;;
;;; Delimiter-bag should be a sequence of one more characters that serve as
;;; delimiters.  Note that the start and end positions of the line are always
;;; implicitly used as delimiters except that contains either no characters or
;;; only trim-bag characters, then the empty list (nil) is returned by this
;;; function.  In other words, at least where trim-bag contains all "blank"
;;; (whitespace) characters, a blank line corresponds to nil.
;;;
;;; Trim-bag should be a sequence of zero or more characters that should be
;;; stripped off of the left and right side of the resulting strings.
;;;
;;; Examples:
;;;
;;;   (parse-ascii-text-line-into-list-of-ascii-strings " foo :bar" ":" "")
;;;     -> (" foo " "bar")
;;;   (parse-ascii-text-line-into-list-of-ascii-strings " foo :bar" ":" " ")
;;;     -> ("foo" "bar")
;;;
;;; The non-Common-Lisp keyword :grouping-bag, if supplied, is a two-element
;;; sequence giving the beginning and ending delimiters that override the
;;; segmenting specified by delimiter-bag.  For example,
;;;   (parse-ascii-text-line-into-list-of-ascii-strings
;;;     " `hi ho' off to work" " " " " :grouping-bag "`'")
;;;     -> ("hi ho" "off" "to" "work")

(defun-simple parse-ascii-text-line-given-grouping-bag
    (ascii-text-line delimiter-bag trim-bag start end grouping-bag)
  (declare (eliminate-for-gsi))
  (loop with start fixnum = (or start 0)
        with end fixnum = (or end (length ascii-text-line))
        with grouping-start-char = (char grouping-bag 0)
        with grouping-end-char = (char grouping-bag 1)
        for substart = start then (if peek-p j (1+f j))
        while (<f substart end)
        for i0? =  (position-of-ascii-character-not-in-bag
                    ascii-text-line trim-bag :start substart :end end)
        while i0?
        for in-group-p
            = (eql (char ascii-text-line i0?) grouping-start-char)
        for i = (if in-group-p (1+f i0?) i0?)
        for peek-p = nil
        as j = (if in-group-p
                   (loop for i2 from i below end
                         for this-char = (char ascii-text-line i2)
                         thereis
                         (and (eql this-char grouping-end-char) i2)
                         finally (return end))
                   (loop for i2 from i below end
                         for this-char = (char ascii-text-line i2)
                         for group-start-p
                             = (eql this-char grouping-start-char)
                         when group-start-p do (setq peek-p t)
                         thereis
                         (and (or group-start-p
                                  (find-gensym-character-in-sequence
                                    this-char delimiter-bag))
                              i2)))
        as k = (if in-group-p
                   nil
                   (position-of-ascii-character-not-in-bag-from-end
                     ascii-text-line trim-bag :start i :end j))
        collect (gensym-string-substring ascii-text-line i (if k (1+f k) j))
          using gensym-cons
        while j))

(defun-allowing-keywords parse-ascii-text-line-into-list-of-ascii-strings
    (ascii-text-line delimiter-bag trim-bag &key start end grouping-bag)
  (declare (eliminate-for-gsi))
  (if grouping-bag
      (parse-ascii-text-line-given-grouping-bag
        ascii-text-line
        delimiter-bag
        trim-bag
        start
        end
        grouping-bag)
      (loop with start fixnum = (or start 0)
            with end fixnum = (or end (length ascii-text-line))
            for substart = start then (+f j 1)
            while (<=f substart end)
            for i = (or (position-of-ascii-character-not-in-bag
                          ascii-text-line trim-bag :start substart :end end)
                        end)
            as j = (position-of-ascii-character-in-bag
                     ascii-text-line delimiter-bag :start i :end end)
            as k = (position-of-ascii-character-not-in-bag-from-end
                     ascii-text-line trim-bag :start i :end j)
            collect (gensym-string-substring ascii-text-line i (if k (+f k 1) j))
              using gensym-cons
            while j)))



;;; `Test-parse-ascii-text-line-into-list-of-ascii-strings' applies the function
;;; parse-ascii-text-line-into-list-of-ascii-strings to each set of args in the
;;; special variable
;;; `parse-ascii-text-line-into-list-of-ascii-strings-test-cases', and checks if
;;; it results in the corresponding results.  Failure is indicated by a non-nil
;;; value, which would be a list of the form
;;;
;;;    ( { (args actual-result expected-result) } )
;;;
;;; This is defined for development only.

#+development
(defparameter parse-ascii-text-line-into-list-of-ascii-strings-test-cases
  '(
    ;; vanilla functionality
    (("foo:bar" ":" " ") ("foo" "bar"))
    (("foo :bar" ":" " ") ("foo" "bar"))
    (("foo : bar" ":" " ") ("foo" "bar"))
    (("foo : bar " ":" " ") ("foo" "bar"))
    (("foo : bar bz " ":" " ") ("foo" "bar bz"))
    (("foo : bar bz: " ":" " ") ("foo" "bar bz" ""))

    ;; :grouping-bag
    (("`hi'" " " " " :grouping-bag "`'") ("hi"))
    (("`hi'`ho'" " " " " :grouping-bag "`'") ("hi" "ho"))
    (("`hi'`ho'`ha'" " " " " :grouping-bag "`'") ("hi" "ho" "ha"))
    (("`hi ho'`ha'" " " " " :grouping-bag "`'") ("hi ho" "ha"))
    (("`hi'`ho ha'" " " " " :grouping-bag "`'") ("hi" "ho ha"))
    (("`hi' `ho'`ha'" " " " " :grouping-bag "`'") ("hi" "ho" "ha"))
    (("`hi ho' `ha'" " " " " :grouping-bag "`'") ("hi ho" "ha"))
    (("`hi ho'  `ha'" " " " " :grouping-bag "`'") ("hi ho" "ha"))
    (("`hi ho'   `ha'" " " " " :grouping-bag "`'") ("hi ho" "ha"))
    (("`hi' `ho ha'" " " " " :grouping-bag "`'") ("hi" "ho ha"))
    (("hi`ho ha'" " " " " :grouping-bag "`'") ("hi" "ho ha"))
    (("hi `ho ha'" " " " " :grouping-bag "`'") ("hi" "ho ha"))
    (("`ho ha'hi" " " " " :grouping-bag "`'") ("ho ha" "hi"))
    (("`ho ha' hi" " " " " :grouping-bag "`'") ("ho ha" "hi"))
    (("`hi hi'ho`ha ha'" " " " " :grouping-bag "`'") ("hi hi" "ho" "ha ha"))
    (("`hi hi' ho`ha ha'" " " " " :grouping-bag "`'") ("hi hi" "ho" "ha ha"))
    (("`hi hi'ho `ha ha'" " " " " :grouping-bag "`'") ("hi hi" "ho" "ha ha"))

    ;; identical grouping delimiters
    (("\"hi\"" " " " " :grouping-bag "\"\"") ("hi"))
    (("\"hi\"\"ho\"" " " " " :grouping-bag "\"\"") ("hi" "ho"))
    (("\"hi\"\"ho\"\"ha\"" " " " " :grouping-bag "\"\"") ("hi" "ho" "ha"))
    (("\"hi ho\"\"ha\"" " " " " :grouping-bag "\"\"") ("hi ho" "ha"))
    (("\"hi\"\"ho ha\"" " " " " :grouping-bag "\"\"") ("hi" "ho ha"))
    (("\"hi\" \"ho\"\"ha\"" " " " " :grouping-bag "\"\"") ("hi" "ho" "ha"))
    (("\"hi ho\" \"ha\"" " " " " :grouping-bag "\"\"") ("hi ho" "ha"))
    (("\"hi ho\"  \"ha\"" " " " " :grouping-bag "\"\"") ("hi ho" "ha"))
    (("\"hi ho\"   \"ha\"" " " " " :grouping-bag "\"\"") ("hi ho" "ha"))
    (("\"hi\" \"ho ha\"" " " " " :grouping-bag "\"\"") ("hi" "ho ha"))
    (("hi\"ho ha\"" " " " " :grouping-bag "\"\"") ("hi" "ho ha"))
    (("hi \"ho ha\"" " " " " :grouping-bag "\"\"") ("hi" "ho ha"))
    (("\"ho ha\"hi" " " " " :grouping-bag "\"\"") ("ho ha" "hi"))
    (("\"ho ha\" hi" " " " " :grouping-bag "\"\"") ("ho ha" "hi"))
    (("\"hi hi\"ho\"ha ha\"" " " " " :grouping-bag "\"\"") ("hi hi" "ho" "ha ha"))
    (("\"hi hi\" ho\"ha ha\"" " " " " :grouping-bag "\"\"") ("hi hi" "ho" "ha ha"))
    (("\"hi hi\"ho \"ha ha\"" " " " " :grouping-bag "\"\"") ("hi hi" "ho" "ha ha"))

    ;; trim-bag interaction with grouping-bag
    (("  `hi'`ho'" " " " " :grouping-bag "`'") ("hi" "ho"))
    (("`hi'`ho'  " " " " " :grouping-bag "`'") ("hi" "ho"))

    ;; trim-bag within grouping
    (("`  hi ho  '" " " " " :grouping-bag "`'") ("  hi ho  "))
    ))

#+development
(defun test-parse-ascii-text-line-into-list-of-ascii-strings ()
  (loop with function = 'parse-ascii-text-line-into-list-of-ascii-strings
        for (args expected-result)
            in parse-ascii-text-line-into-list-of-ascii-strings-test-cases
        as actual-result = (eval `(,function . ,args))
        when (not (equal actual-result expected-result))
          collect (list args actual-result expected-result)
            into failures
        finally
          (if failures
              (return failures))))

#+development
(assert (null (test-parse-ascii-text-line-into-list-of-ascii-strings)))





;;; `Parse-colon-delimited-ascii-text-line-into-list-of-ascii-strings' ...
;;;
;;; `Parse-space-delimited-ascii-text-line-into-list-of-ascii-strings'

(defun parse-colon-delimited-ascii-text-line-into-list-of-ascii-strings
    (ascii-text-line)
  (declare (eliminate-for-gsi))
  (parse-ascii-text-line-into-list-of-ascii-strings
    ascii-text-line '(#\:) '(#\space #\tab)))

(defun parse-space-delimited-ascii-text-line-into-list-of-ascii-strings
    (ascii-text-line)
  (declare (eliminate-for-gsi))
  (parse-ascii-text-line-into-list-of-ascii-strings
    ascii-text-line '(#\space #\tab) '(#\space #\tab)))






;;;; Basic Twriting Functions and Macros




;;; `Twrite-char' writes simple-or-wide-character.
;;;
;;; All twriting functions bottleneck through twrite-char, and it is also called
;;; directly in many cases.  Tformat, twrite, tprin, and twrite-general-string are some
;;; of the functions that go through twrite-char.
;;;
;;; The only place users should generally have to care about whether the result
;;; is to be a gensym string or a wide string is in the call to either of the
;;; twith-output-... macros.
;;;
;;; Note that the contract is now being changed around the Twriting functions.
;;; Their documentation may still reflect the old policy: that they are only
;;; to be used in a twith-output-to-gensym-string context.

(defmacro twrite-char (simple-or-wide-character)
  (avoiding-variable-capture (simple-or-wide-character)
    `(if (eq (get-current-twriting-output-type) 'wide-string)
         (twrite-wide-character
           (coerce-to-wide-character ,simple-or-wide-character))
         (twrite-simple-character-to-current-gensym-string
           (or (code-char
                 (wide-character-code
                   (coerce-to-wide-character
                     ,simple-or-wide-character)))
               #+development
               (cerror "Continue (ignoring the problem, as in production)"
                       "~a cannot be transformed into a simple character!"
                       ,simple-or-wide-character))))))

;;; `Twrite-simple-character-to-current-gensym-string' always writes a simple
;;; character to the current gensym string.  It must be called in a
;;; twith-output-to-gensym-string context.

(defmacro twrite-simple-character-to-current-gensym-string (simple-character)
  `(progn
     (if (not (<f fill-pointer-for-current-gensym-string
                  total-length-of-current-gensym-string))
         (extend-current-gensym-string))
     (setf (schar current-gensym-string fill-pointer-for-current-gensym-string)
           ,simple-character)
     (incff fill-pointer-for-current-gensym-string)))


;;; `Twrite-character' is a function equivalent to the macro twrite-char.

(defun twrite-character (simple-character)
  (twrite-char simple-character))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter extend-current-gensym-string-error-message ;SS_ERROR: was defconstant
  "Trying to write a string longer than 1MB!")
)

(defmacro signal-extend-current-gensym-string-error ()
  `(current-system-case
     ((ab telewindows)
      #+development
      (cerror
        "Continue"
        #.extend-current-gensym-string-error-message))
     (gsi
       (signal-gsi-extend-current-gensym-string-error))))

(defun extend-current-gensym-string (&optional minimum-new-total-length?)
  (when (>f (or minimum-new-total-length? (1+f total-length-of-current-gensym-string))
            maximum-length-for-user-gensym-strings)
    (signal-extend-current-gensym-string-error))        ; presumably an infinite loop
  (let* ((minimum-new-total-length (or minimum-new-total-length? 0))
         (new-total-length
           (minf
             maximum-gensym-string-length
             (maxf (floorf-positive
                     (*f total-length-of-current-gensym-string 3)
                     2)  ; 1.5; 1.25?
                   minimum-new-total-length)))
         (new-gensym-string
           (obtain-simple-gensym-string new-total-length)))
    (loop for i from 0 below fill-pointer-for-current-gensym-string
          do (setf (schar new-gensym-string i) (schar current-gensym-string i)))
    (reclaim-simple-gensym-string current-gensym-string)
    (setf current-gensym-string new-gensym-string)
    (setf total-length-of-current-gensym-string new-total-length)))

;; Rename twrite-char "twrite-char-macro"!




;;; The function `twrite-n-spaces' takes an integer and twrites that many space
;;; characters.

(defun twrite-n-spaces (spaces-count)
  (loop repeat spaces-count do
    (twrite-char #.%space)))



;;; The function `twrite-spaces-if-necessary' takes a minimum width argument and
;;; writes spaces, when necessary, to bring the actual width up to the minimum.

(defun twrite-spaces-if-necessary (minimum-width actual-width)
  (when (>f minimum-width actual-width)
    (twrite-n-spaces (-f minimum-width actual-width))))





;;; `twrite-float' writes a number in the system standard format for writing
;;; floating point numbers.  It is an error for float not to be a floating point
;;; number.  This expands into a call to
;;; write-floating-point-number-simple-c-format with default values of
;;; precision and output format from Miscellaneous parameters system table,
;;; without minimum width and with suppressing trailing zeroes set to true.

(defmacro twrite-float (float)
  `(write-floating-point-number-simple-c-format ,float))



;;; `Twrite' writes x, where x may be a symbol, string, integer, floating-point number,
;;; including managed float, slot-value float, and phrase float.  NOTE: previously,
;;; this could handle a character, but that is no longer a legal option.  It cannot
;;; handle wide characters either.

;; [It's too confusing to handle character, especially since we can't handle
;; wide-character, since it cannot currently be distinguished from fixnum!  The
;; use of twrite with characters was seldom used anyway. (MHD 6/6/96)]

;;; If x is any other data object, x will be written as an S-expression, to provide
;;; system-level debugging information.

;;; This converts a symbol to lower case if write-symbols-in-lower-case? is true.

;;; Note: twrite has an implicit parameter, calling-tformat-for-give-warning?, a
;;; defvar bound to nil at top-level, which is used to implement a
;;; special-purpose contract with give-warning, warning-message, and
;;; warning-message*, which bind it to true, for the case where X is a block; in
;;; that case, it prints X's name, as given by get-or-make-up-name-for-block.
;;; However, this is not a supported interface for other callers, and should not
;;; be relied upon.  In fact, eventually this feature will be removed.  See
;;; documentation near warning-message* for further information.  (MHD 11/26/91)

(defvar calling-tformat-for-give-warning? nil)

(defvar write-symbols-in-lower-case? nil)

(defun-simple twrite (x)
  (cond
    ((symbolp x)
     (twrite-symbol x (not write-symbols-in-lower-case?)))
    ((fixnump x)
     (twrite-fixnum x))
    ((or (text-string-p x)
         (gensym-string-p x))                ; for now, union of the two string types
     (twrite-general-string x))
    #-chestnut-trans
    ((managed-float-p-function x)
     (twrite-float (managed-float-value-function x)))
    #+chestnut-trans
    ((managed-float-p x)
     (twrite-float (managed-float-value x)))
    ((floatp x)
     (twrite-float x))
    ((characterp x)
     (twrite-char x))
    ((long-p x)
     #+chestnut-trans
     (with-temporary-bignum-creation
       (twrite-long-macro x))
     #-chestnut-trans
     (twrite-long-function x))
    ((integerp x)
     (current-system-case
       ((ab telewindows)
        (with-temporary-bignum-creation
          (cond
            ((< x 0)
             (twrite-char #\-)
             (twrite-positive-bignum (- x)))
            (t (twrite-positive-bignum x)))))
       (gsi nil)))
    (calling-tformat-for-give-warning?
     (current-system-case
       (ab
	(when (and
	        #-chestnut-trans (framep-function x)
		#+chestnut-trans (framep x)
		#-chestnut-trans (block-p-function x)
		#+chestnut-trans (block-p x))
	  (twrite (get-or-make-up-designation-for-block x))))
       (t
	(write-random-s-expression x))))
    (t
     (write-random-s-expression x)
     ;; alt.
     ;; #+development
     ;; (cerror "Ignore it"
     ;;   "~s cannot be used as an arg to tformat!"
     ;;   x)
     )))

;; It would be an overstatement to say that it's an error for x to be another
;; data type in non-development.  I know we certainly want to keep write-random-
;; s-expression around in non-development -- it could be used by internal-error,
;; for example.  Refine! (MHD 11/25/91)

;; Do case conversion differently!



;;; `Twrite-parsably' is like twrite except that symbols and strings are written in
;;; such a way (with quoting characters and delimiters) that they can later be parsed
;;; as tokens.

(defvar write-strings-parsably? nil)

(defun-simple twrite-parsably (x)
  (let ((write-symbols-parsably? t)
        (write-strings-parsably? t))
    (twrite x)))

;; Consider writing characters and maybe numbers in a special parsable way.




;; Section containing twrite-symbol and friends moved from here from UNICODE to
;; avoid forward reference problems. (MHD 2/20/96)


;; Section containing twrite-general-string and friends moved from here from UNICODE to
;; avoid forward reference problems. (MHD 2/20/96)



;;; `Twrite-line-break' writes a line separator, which represents a (forced)
;;; line break.

(defun twrite-line-break ()
  (twrite-line-separator))

;; Considering getting rid of one or the other of twrite-line-break and
;; twrite-line-separator!  This previously wrote out @L. (MHD 2/16/96)



(defmacro tprinc (x)
  `(twrite ,x))

;; Eliminate this after converting calls to call twrite!



(defun tprin (x enclose-strings-in-quotes?)
  (declare (eliminate-for-gsi))
  (if (and enclose-strings-in-quotes?
           (or (text-string-p x)        ; for now, handle union of the two string types (MHD 2/14/96)
               (gensym-string-p x)))
      (twrite-parsably x)
      (twrite x)))

;; Second arg name, write-strings-parsably?, was previously
;; enclose-strings-in-quotes?, and call to twrite-parsably was previously to
;; twrite-general-string-with-quotation-marks.  This is more general, and works with
;; strings whose contents include double quote marks and @'s.  E.g.,
;;
;;   strings with these contents => string displayed this way
;;    foo                        => "foo"
;;    bar@baz                    => "bar@@baz"
;;    bar"not"bar                => "bar@"not@"bar"
;;
;; so the resulting strings are called parsable, because they could be parsed by
;; the G2 language tokenizer.
;;
;; In English, quote marks within quotations are handled rather differently.  E.g.,
;; a string whose contents include double quotes, such as
;;
;;   the "right" thing
;;
;; would be written in quotes as
;;
;;   "the 'right' thing"
;;
;; (or as ``the `right' thing'). It is true, the display strings above could not
;; be parsed by normal English readers, for whom the quoting convention is
;; different, but that's a different matter; all know callers of this function,
;; are either neutral, or prefer the G2 tokenizer's definition of parsable.
;;
;; (MHD 5/5/95)

;; Eliminate this after converting calls to call either twrite or
;; twrite-general-string-with-quotation-marks!  On second thought, maybe just get rid of
;; twrite-general-string-with-quotation-marks, and use either tprin or twrite-parsably
;; in its place.  Also, maybe get rid of tprin and convert its callers?



(defmacro princ-lowercase (symbol)
  `(twrite-symbol ,symbol))

;; Eliminate this after converting calls to call twrite-symbol!





;;; Begins-with-vowel? is true if symbol-or-string begins with a, e, i, o, or u.

(defun begins-with-vowel? (symbol-or-string)
  (declare (eliminate-for-gsi))
  (when (consp symbol-or-string)
    (setq symbol-or-string (car symbol-or-string)))
  (memq (char (if (symbolp symbol-or-string)
                  (symbol-name symbol-or-string)
                  symbol-or-string)
              0)
        '( #\a #\e #\i #\o #\u #\A #\E #\I #\O #\U)))



;;; Supply-a-or-an ... returns either the string "a " or "an ".  Notice that a
;;; space character is there after the a or an.

(defun supply-a-or-an (symbol-or-string)
  (declare (eliminate-for-gsi))
  (when (consp symbol-or-string)
    (setq symbol-or-string (car symbol-or-string)))
  (if (begins-with-vowel? symbol-or-string)
      "an "
      "a "))






;; NEEDS WORK!  (MHD 5/2/91)

;(defparameter report-non-string-constant-format-control-strings? nil)

;(defun check-format-function-args
;       (position-of-format-control-string-arg
;        arglist-with-format-control-string-and-args
;        function-name)
;  (let ((format-control-string
;          (nth position-of-format-control-string-arg
;               arglist-with-format-control-string-and-args)))
;    (if (and report-non-string-constant-format-control-strings?
;             (not (stringp format-control-string)))
;        (warn "Format control string arg to ~a is not a constant string: ~s"
;              function-name format-control-string))))


;(defmacro def-format-function
;          (position-of-format-control-string-arg name args &body body)
;  (let ((name-of-real-function (format-symbol "REAL-FORMAT-FUNCTION-~a" name)))
;    `(progn
;       (defmacro ,name ,args
;         (check-format-function-args
;           ',position-of-format-control-string-arg ',args ',name)
;         (def-format-function-1 ,name-of-real-function ,args))
;       (defun ,name-of-real-function ,args
;         . ,body))))

;(defmacro def-format-function-1 (name-of-real-function args)
;  `(,name-of-real-function . ,args))

;(def-format-function-1 a (b c))

;(def-format-function 1 my-foo (stream format-control-string arg1 arg2)
;  (format stream format-control-string arg1 arg2))
(progn) ; marks end of section of commented-out code above.







;;;; Tformat



;;; `Tformat' is like format in that it takes a control string and arguments
;;; and prints the requested items.  It does not take a destination argument,
;;; and instead will write to a gensym string established by
;;; twith-output-to-gensym-string.

;;; Tformat supports the following format directives with their Common Lisp
;;; meanings: ~A ~S ~C ~D ~B ~O ~X ~F ~( ~) ~% ~newline ~~.  The optional prefix
;;; parameters and : or @ modifiers that some of these directives take in Common
;;; Lisp are not supported.  Also, ~(str~) converts to lower case only roman
;;; alphabetic characters in symbols that are included per ~A, ~S, ~D, or ~F
;;; directives.

;;; Note that tformat takes a maximum of 9 arguments, but that number could
;;; be increased without much trouble.

;;; In addition, tformat takes two sets of new G2-software-specific directives.
;;; One set is called the `~N directives' or "New Directives": ~NF, ~ND, ~NE,
;;; etc. All of these correspond directly to a G2 function which their arg(s)
;;; are called upon. These are summarized in the following table.
;;;
;;;
;;;        name (mnemonic)            directive        arg(s)                  G2 function (description)
;;;        -------------------------------------------------------------------
;;;     (1-ARG DIRECTIVES)
;;;            Frame                    ~NF                frame                  get-or-make-up-designation-for-block
;;;                                                         (if a block)
;;;            Designation            ~ND                designation          print-designation
;;;     Name                ~NN         name-denotation   write-name-denotation
;;;            Expression            ~NE             expression          write-expression
;;;            Type of Data            ~NT                data-type          write-type-specification
;;;            Value of Evaluation ~NV         evaluation-value  write-evaluation-value
;;;     Gensym-pathname     ~NP         gensym-pathname   write-gensym-pathname
;;;     Error-text          ~NW         error-text-object write-error-text
;;;            All                    ~NA                frame                  write-block-or-evaluation-value
;;;                                            or evaluation-
;;;                                            value
;;;
;;;     (2-ARG DIRECTIVES)
;;;            Constant            ~NC                constant-value,          print-constant
;;;                                             constant-type
;;;     Slot                ~NS         slot-description, write-name-denotation-for-slot
;;;                                     class-description
;;;     Qualified Name      ~NQ         name,             write-name-denotation-components
;;;       Components                      class-qualifier?
;;;
;;;     Record Block        ~NR         block,            (records block like ~NF, but
;;;                                       text-to-print     with custom text.)
;;;
;;;     Denote Component    ~NB  component-particulars,   donote-component-of-block
;;;       Particulars              block
;;;
;;; ~NN prints, as though the directive had been ~A, the result of calling
;;; write-name-denotation on its arg.  The other directives all write to
;;; the current output buffer.

;;; Note that, with the exception of the ~N directives, the args to tformat
;;; should be symbols, strings, characters, integers, and floats.  With the
;;; aforementioned exceptions, the arguments should not be conses, arrays, rationals,
;;; complex numbers, etc.

;;; The second set of gensym-specific directives are the L (or List) directives.
;;; These, too, correspond to function calls, specifically to calls to the
;;; function write-symbol-list.  All of these directives start with the letter
;;; L, and are followed by two more letters.  They all take just one argument,
;;; either a list, a symbol, or a string.
;;;
;;; The following table lists the possible variations of the L directive, and
;;; how they translate into the separator? and conjunction? arguments to
;;; write-symbol-list.
;;;
;;;                        Args to write-symbol-list (when arg is a list)
;;;        New Tformat        ----------------------------------------------
;;;        Directive        Separator?        Conjunction?
;;;             ~L,&                ","                "and"
;;;             ~L;&                ";"                "and"
;;;             ~L &                " "                "and"
;;;             ~L-&                nil                "and"
;;;             ~L,|                ","                "or"
;;;             ~L;|                ";"                "or"
;;;             ~L |                " "                "or"
;;;             ~L-|                nil                "or"
;;;             ~L,-                ","                nil
;;;             ~L;-                ";"                nil
;;;             ~L -                ";"                nil
;;;             ~L--                nil                nil
;;;
;;; if the arg to any of the above directives is not a list, then it should
;;; be a symbol (other than NIL) or a string.  Given a symbol or string S,
;;; and any of the above directives, tformat supplies S as the empty-list-
;;; symbol-or-string? arg to write-symbol-list.  This is intended to be used
;;; in forms like (tformat "~L,|" (or my-list "nothing")).


;;; The defvar `note-blocks-in-tformat', if bound to a simple-compiled-function
;;; of one argument, block, will be called on each block processed by the ~NF
;;; tformat directive.

(defvar note-blocks-in-tformat nil)

(def-substitution-macro note-block-in-tformat (thing)
  (when (and (framep-function thing)
             (block-p-function thing)
             note-blocks-in-tformat)
    (funcall-simple-compiled-function note-blocks-in-tformat thing)))

(defvar tformat-fresh-line-is-newline-p t) ; some places bind this to nil
(defvar in-text-for-item-or-value-p nil)

(defun tformat
       (control-string
        &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)        ; add more as needed!
  #+development
  (unless (or (gensym-string-p control-string)
              (text-string-p control-string)) ; for now, handle both (MHD 2/7/97)
    (error "First argument to TFORMAT, ~s, is not a string." control-string))
  (macrolet ((backup-arg ()
               `(decff arg-index))
             (pop-arg ()
               `(case (incff arg-index)
                  (1 arg1) (2 arg2) (3 arg3) (4 arg4) (5 arg5)
                  (6 arg6) (7 arg7) (8 arg8) (9 arg9)
                  (t #+development
                     (cerror "Use nil instead of real arg"
                             "Too many directives to tformat!")
                  nil)))
             (pop-char ()
               `(progn
                  (setq character
                        (if gensym-string-p
                            (coerce-to-wide-character
                              (gchar control-string i gensym-string-is-simple?))
                            (charw-function control-string i)))
                  (incff i)
                  character))
             (pop-format-directive ()
               `(progn
                  (setq directive-colon-p nil directive-atsign-p nil)
                  (loop do (wide-character-case (pop-char)
                             (#.%\: (setq directive-colon-p t))
                             (#.%\@ (setq directive-atsign-p t))
                             (t (return character))))))
             (skip-to-next-clause () ; does not properly handle nested ~[ ~]
               `(loop until (=f i string-length)
                      do (wide-character-case (pop-char)
                           (#.%\~
                              (when (=f i string-length) ; error?
                                (return nil))
                              (wide-character-case (pop-format-directive)
                                (#.%\; (return t))
                                (#.%\] (return nil)))))
                      finally (return nil)))
             (skip-to-end-of-conditional () ; does not properly handle nested ~[ ~]
               `(loop until (=f i string-length)
                      do (wide-character-case (pop-char)
                           (#.%\~
                              (when (=f i string-length) ; error?
                                (return t))
                              (wide-character-case (pop-format-directive)
                                (#.%\] (return t)))))
                      finally (return nil))))
    (loop with arg-index = 0        ; nils implicitly added
          with write-symbols-in-lower-case? = nil
          with directive-colon-p
          with directive-atsign-p
          with i = 0
          with gensym-string-p = (gensym-string-p control-string)
          with gensym-string-is-simple? = (simple-gensym-string-p control-string)
          with string-length = (if gensym-string-p
                                   (glength control-string gensym-string-is-simple?)
                                   (lengthw control-string))
          with character
          until (=f i string-length)
          do (wide-character-case (pop-char)
               (#.%newline (twrite-char #.%line-separator)) ; new; keep this?!
               (#.%\~
                  (when (=f i string-length) ; error?
                    (loop-finish))
                  (wide-character-case (pop-format-directive)
                    ((#.%\A #.%\a #.%\S #.%\s #.%\C #.%\c #.%\D #.%\d
                            #.%\B #.%\b #.%\O #.%\o
                          #.%\X #.%\x #.%\F #.%\f #.%\N #.%\n #.%\L #.%\l)
                     (let ((arg (pop-arg)))
                       (wide-character-case character
                         ((#.%\A #.%\a) (twrite arg))
                         ((#.%\S #.%\s) (twrite-parsably arg))
                         ((#.%\C #.%\c) (twrite-char arg))
                         ((#.%\D #.%\d) (twrite arg))        ; bind base?
                         ((#.%\B #.%\b #.%\O #.%\o #.%\X #.%\x)        ; print binary, octal, or hex
                          #+development
                          (unless (fixnump arg)
                            (cerror "Continue"
                                    "tformat's O & X ~
                                   directives only support fixnums."))
                          (twrite-positive-fixnum-in-radix
                            arg
                            (wide-character-case character
                              ((#.%\B #.%\b) 2)
                              ((#.%\O #.%\o) 8)
                              (t 16))))
                         ((#.%\F #.%\f) (twrite arg))        ; eliminate?
                         ((#.%\N #.%\n)
                          (wide-character-case (pop-char)
                            ;; 1-arg directives:
                            ((#.%\F #.%\f) (cond (in-text-for-item-or-value-p
                                                  (twrite-designation-for-item arg))
                                                 ((and (framep-function arg) (block-p-function arg))
                                                  (twrite (get-or-make-up-designation-for-block arg))
                                                  (note-block-in-tformat arg))
                                                 (t
                                                  (twrite arg))))
                            ((#.%\A #.%\a) (write-block-or-evaluation-value arg))
                            ((#.%\N #.%\n) (write-name-denotation arg))
                            ((#.%\D #.%\d) (print-designation arg))
                            ((#.%\E #.%\e) (write-expression arg))
                            ((#.%\T #.%\t) (write-type-specification arg))
                            ((#.%\V #.%\v) (write-evaluation-value arg))
                            ((#.%\P #.%\p) (write-gensym-pathname arg))
                            ((#.%\W #.%\w) (write-error-text arg)) ; -fmw, 3/6/94
                            ;; 2-arg directives:
                            ((#.%\C #.%\c) (print-constant arg (pop-arg)))
                            ((#.%\S #.%\s) (write-name-denotation-for-slot arg (pop-arg)))
                            ((#.%\Q #.%\q) (write-name-denotation-components arg (pop-arg)))
                            ((#.%\R #.%\r) (progn (note-block-in-tformat arg)
                                              (twrite (pop-arg))))
                            ((#.%\B #.%\b) (current-system-case
                                             ((ab)
                                              (denote-component-of-block
                                                t arg (pop-arg)))))))
                         ((#.%\L #.%\l)
                          (write-symbol-list
                            (if (listp arg) arg nil)
                            (wide-character-case (pop-char)
                              (#.%\; ";")
                              (#.%\, ",")
                              (#.%space " ")
                              (t nil))
                            (wide-character-case (pop-char)
                              (#.%\| "or")
                              (#.%\& "and")
                              (#.%\- nil))
                            (if (not (listp arg))
                                arg))))))
                    (#.%\( (setq write-symbols-in-lower-case? t))
                    (#.%\) (setq write-symbols-in-lower-case? nil))
                    (#.%\%
                     (twrite-line-separator))
                    (#.%\&
                     ;; & is just a newline for now, but could ultimately be
                     ;; smarter; note that the spec for & allows for this kind of
                     ;; punting (MHD 10/11/94)
                       (if tformat-fresh-line-is-newline-p
                           (twrite-line-separator)
                           (twrite-char #.%space)))
                    (#.%newline
                       (loop until (=f i string-length)
                             do (pop-char)
                             until (not (wide-character-member
                                          character
                                          '(#.%space #.%tab #.%newline
                                            ;; not needed or not allowed in some
                                            ;; Lisps:
                                            #.%linefeed #.%return)))
                             finally
                               (decff i)))
                    ;; used by icp-trace.  see EMIT-ICP-WRITE-TRACE
                    (#.%\[
                       (let ((arg (pop-arg)))
                         (cond (directive-atsign-p ; 1 clause; if arg is nil, skip arg and clause
                                (cond (arg
                                       (backup-arg))
                                      (t
                                       (skip-to-end-of-conditional))))
                               (directive-colon-p ; 2 clauses; do first if arg is nil, do second otherwise
                                (when arg
                                  (skip-to-next-clause)))
                               (t ; n clauses; 0 means first, 1 second ...; ~:; introduces a default clause
                                (loop for i fixnum from 0 below arg ; default case is not implemented
                                      do
                                  (unless (skip-to-next-clause)
                                    (return nil)))))))
                    (#.%\; (skip-to-end-of-conditional))
                    (#.%\] )
                    (#.%\~ (twrite-char #.%\~))
                    (t
                      #+development
                      (cerror "Ignore directive"
                              "~~~C directive to tformat not yet handled!"
                              (code-char (wide-character-code character))))))
             (t
               (twrite-char character))))))


;; New -- added the ~x (hex) directive today.  It was easy because we already
;; had one for ~o (octal).  (MHD 11/13/92)

;; For a while this advertised
;;
;;   ~ND gets enclosing single quotes (`') around it.
;;
;; It never was true. Consider that in the future, but don't do it now.
;; (MHD 2/6/92)

;; The ~N and ~I directives were added today.  They need some review, and then
;; should be helpful in significantly reducing the size of code that produces
;; error and warning messages in G2.  (MHD 11/6/90)

;; Count or stack ~( and ~) directives later, or eliminate them!

;; Macro-expand where possible?!

;; Consider adding a suite of Tformat directives to handle the majority of list
;; types:
;;
;;                        Args to write-symbol-list
;;        New Tformat        --------------------------
;;        Directive        Separator        Conjunction?
;;             ~L,A                ","                "and"
;;             ~L;A                ";"                "and"
;;             ~L,O                ","                "or"
;;             ~L;O                ";"                "or"
;;             ~L,-                ","                nil
;;             ~L;-                ";"                nil
;;             ~L-A                "and"                nil
;;             ~L-O                "or"                nil
;;             ~L--                nil                nil
;;             ~L--                nil                nil
;;
;;      empty-list-symbol-or-string?: if the arg to any of the
;;      above directives is a symbol (other than NIL) or string
;;      S then this prints what you would see with
;;         (write-symbol-list nil anything anything S)
;;      I.e., this write S instead of a list.  This is intended
;;      to allow forms like
;;         (tformat "~L,|" (or my-list "nothing"))
;;
;; (MHD 12/91)
;; -- DONE. (MHD 9/17/93)
;;
;; Note: the alternative of "how CLtL's format accomplishes this" is not
;; so appealing.  Compare how the print a list of comma-delimited symbols,
;; L, ANDed together:
;;
;;   tformat: (tformat "~L,&" (or L "and"))
;;   format:  (apply 'format t
;;                   "~#[none~;~S~;~S and ~S~:;~@{~#[~; and~] ~S~^,~}~]"
;;                   L)
;;
;; If I could figure the format code out I could maybe get rid of the APPLY.  I
;; got the code from CLtL. Anyway, the point is that the L directive is a lot
;; more fun to use for common List printing.  (MHD 9/27/93)




;;; `Tformat-gensym-string' ...  The args should be symbols, strings, characters, integers,
;;; and floats.  They should not be conses, arrays, rationals, complex numbers, etc.

(defun tformat-gensym-string
    (control-string
      &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)        ; add more as needed!
  (twith-output-to-gensym-string
    (tformat control-string arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)))






;;;; Miscellaneous Twrite Functions



;;; `Write-random-s-expression' and `write-s-expression' ...

(defun write-random-s-expression (s-expression)
  ; (twrite-general-string "[S-Expression: ")   -- this was OK, but too much hassle
  (write-s-expression s-expression)
  ; (twrite-general-string "]")
  )

(defun write-s-expression (s-expression)
  (if (atom s-expression)
      (cond
        ((or (gensym-string-p s-expression)
             (text-string-p s-expression)
             (symbolp s-expression)
             (floatp s-expression)
             (integerp s-expression)
             (characterp s-expression))
         (twrite-parsably s-expression))
        (t
         (let ((string  ; for arrays (etc?)
                 #-development
                 (with-output-to-gensym-string (*standard-output*)
                   (pm-prin1 s-expression))
                 #+development
                 (with-output-to-gensym-string (stream)            ; May leak.
                   (princ s-expression stream)))
               (write-strings-parsably? nil))
           (twrite-general-string string)
           (reclaim-gensym-string string))))
      (loop initially
              (let ((write-strings-parsably? nil))
                (twrite-general-string "("))
            do (write-s-expression (pop s-expression))
            until
            (atom s-expression)
            do (twrite-character #.%space)
            finally
              (cond
                ((not (eq s-expression nil))
                 (let ((write-strings-parsably? nil))
                   (twrite-general-string " . "))
                 (write-s-expression s-expression)))
            (let ((write-strings-parsably? nil))
              (twrite-general-string ")")))))

;; These should begin "twrite-"!









;;; `write-symbol-list' ...  If conjunction?  is nil, it writes a `simple comma
;;; series', i.e.  lists of the form "A", "A, B", "A, B, C", etc.  If non-nil,
;;; Conjunction?  may be a string or symbol to be used as a conjunction (i.e.
;;; symbols AND, OR, UND, ODER, etc., or similar strings).  In the case of the
;;; conjunction being a symbol, it is written in all lowercase letters.  The comma
;;; series in this case follows the rules of English: with AND as second argument,
;;; for example, it writes lists of the form "A", "A and B", "A, B, and C", etc.

;;; All symbols in symbol-list are written using twrite, and so the special variable
;;; write-symbols-in-lower-case?  and write-symbols-parsably?  may be bound
;;; appropriately.  Since if conjunction?  is a symbol, it is always written in all
;;; lowercase letters, the only way to write it in some other case to supply it as a
;;; string with letters in uppercase or lowercase as appropriate.

;;; If symbol-list is nil, then if empty-list-symbol-or-string?  is nil, it prints
;;; "none"; otherwise, it prints empty-list-symbol-or-string?, which may be a string
;;; or a symbol.  Note that you can print nothing for an empty list by passing in the
;;; empty string ("").

;;; If suffix-alist? is specified, it should be of the form
;;;
;;;   {(symbol-to-suffix . suffix-string)}
;;;
;;; Then, for each symbol in symbol-list?, if it matches a symbol-to-suffix in
;;; suffix-alist?, the corresponding suffix-string is appended to symbol when
;;; it is written.  None of the strings of conses in suffix-alist? will be
;;; recycled.  (The only known use for this facility, at present, is to append
;;; the Trademark or Registered symbols to various G2 product names, as
;;; appropriate, when writing part of the title block.)

;;; Write-symbol-list is now used in various grammar slot writers.

(defun write-symbol-list (symbol-list
                          &optional
                            (separator? nil) (conjunction? nil)
                            (empty-list-symbol-or-string? nil)
                            (suffix-alist? nil))
  (if (null symbol-list)
      (twrite (or empty-list-symbol-or-string? "none"))
      (progn
        (unless separator?
          (setf separator? ","))
        (loop for listed-symbol on symbol-list
              do (twrite (car listed-symbol))
                 (let ((entry-for-symbol-to-suffix?
                         (assq (car listed-symbol) suffix-alist?)))
                   (if entry-for-symbol-to-suffix?
                       (twrite-general-string (cdr entry-for-symbol-to-suffix?))))
                 (if (cdr listed-symbol)
                     (cond ((cddr listed-symbol)
                            (tformat "~a " separator?))
                           ((=f (length symbol-list) 2)
                            (if conjunction?
                                (if (symbolp conjunction?)
                                    (tformat " ~(~a~) " conjunction?)
                                    (progn
                                      (twrite-general-string " ")
                                      (twrite-general-string conjunction?)
                                      (twrite-general-string " ")))
                                (tformat "~a " separator?)))
                           (conjunction?
                            (tformat "~a " separator?)
                            (if (symbolp conjunction?)
                                (tformat "~(~a~)" conjunction?)
                                (twrite-general-string conjunction?))
                            (twrite-general-string " "))
                           (t (tformat "~a " separator?))))))))

;; Make this a more general utility (not only for symbols); perhaps change name
;; first.  Consider taking a function to print elements (or perhaps only non-
;; symbol elements).




;;; The function `twrite-list' is a more general version of write-symbol-list.

(defun-allowing-keywords twrite-list (list &key
                                           (element-writer #'twrite)
                                           (empty nil)
                                           (conjoiner " or ")
                                           (separator ", "))
  (declare (eliminate-for-gsi))
  #+development (unless (simple-compiled-function-p element-writer)
                  (warn "~s is not a simple-compiled-function -- may fail in build."
                        element-writer))
  (cond ((and (null list) empty)
         (twrite-general-string empty))
        (t
         (loop for sublist on list doing
           (funcall-simple-compiled-function element-writer (car sublist))
           (cond ((null (cdr sublist)))
                 ((and (null (cddr sublist)) conjoiner)
                  (twrite-general-string conjoiner))
                 (separator
                  (twrite-general-string separator)))))))



;;; Many other text-related utilities are found in the module UTILITIES4.  That
;;; module contains utilities that are not needed, and therefore unavailable, in
;;; Telewindows.




;;; `Provide-legal-gensym-string' takes two keyword arguments,
;;; form-to-determine-string-length and loop-clauses-to-read-next-character.  It
;;; returns a new gensym-string which is guaranteed to be legal for subsequent use
;;; inside G2.  In the new gensym string returned by provide-legal-gensym-string,
;;; all illegal characters have been elided.  Eventually we may abstract this
;;; behavior and provide some alternatives.  See the function
;;; convert-ascii-filename-to-gensym-string-as-much-as-possible for one such
;;; as-yet unabstracted alternative.

;;; The form-to-determine-string-length keyword argument to
;;; provide-legal-gensym-string is a Lisp form which, when evaluated, gives the
;;; maximum length of the new string.

;;; The loop-clauses-to-get-next-character keyword argument to
;;; provide-legal-gensym-string is a list to be spliced at macroexpansion time
;;; into a loop which checks successive characters for legality.  The clauses in
;;; loop-clauses-to-get-next-character must set two variables, character and
;;; character-code.  These are, respectively, the next character to check for
;;; legality and the code of that character.  The variables string-length,
;;; last-character-p, character-index, and skip-this-character-p are lexically
;;; available to the code in loop-clauses-to-read-next-character.

;;; The limit-string-length-p keyword argument to provide-legal-gensym-string is
;;; unevaluated.  When this argument is t, the length of any string returned by
;;; provide-legal-gensym-string is limited to
;;; maximum-length-for-user-gensym-strings, a constant defined in CHARACTERS,
;;; currently (5/29/92, jh) 64k.  Beyond this limit, the
;;; loop-clauses-to-get-next-character forms are executed, but the resulting
;;; character is "thrown away" -- it is not checked for legality and is not
;;; placed in the gensym string to be returned.  Care is taken, however, to treat
;;; maximum-length-for-user-gensym-strings as end-of-file for multi-character
;;; legality checks, like the check for a dangling escape character.  If the
;;; limit is exceeded, a second value of t is returned from
;;; provide-legal-gensym-string.

;;; There are two rationales for using a series of loop clauses as an argument:
;;; first, inlining gains speed, and second, local state sometimes needs to be
;;; stored while stepping through the input gensym string.

;;; An example of the use of provide-legal-gensym-string may be found immediately
;;; below, in the function
;;; copy-string-filtering-out-non-gensym-characters.  This macro is a
;;; first attempt at abstracting the notion of a `gensym-string filter' and will
;;; no doubt undergo many changes (after 3/23/92) before reaching its final
;;; form.

(defmacro provide-legal-gensym-string
          (&key form-to-determine-string-length
                loop-clauses-to-get-next-character
                limit-string-length-p
                (gensym-string-obtainer 'obtain-gensym-string))
  (avoiding-variable-capture
      ;; Following are variables that are not lexically available to clients of
      ;; this macro.  Avoiding-variable-capture will "gensym" them into unique
      ;; but readable names in the macroexpansion.
      (&aux gensym-string string-is-simple-p
            last-char-index bad-state-p escape-character?
            first-character-code-following-\\?
            second-character-code-following-\\?
            third-character-code-following-\\?
            kanji-character-code?
            string-length-exceeded-p
            )
    `(let* ((string-length ,form-to-determine-string-length)
            ;; Splice in different let-spec for gensym-string, depending on
            ;; whether or not we are limiting gensym-string length.
            ,(if limit-string-length-p
                 `(,gensym-string
                   (,gensym-string-obtainer
                     (minf string-length
                           maximum-length-for-user-gensym-strings)))
                 `(,gensym-string (,gensym-string-obtainer string-length)))
            (,string-length-exceeded-p nil)
            (character-code 0)
            (character #\a))
       (declare (type fixnum string-length character-code)
                (type character character))
       (loop with ,string-is-simple-p = (simple-gensym-string-p ,gensym-string)
             with ,bad-state-p = nil
             with ,escape-character? = nil
             with ,first-character-code-following-\\? = nil
             with ,second-character-code-following-\\? = nil
             with ,third-character-code-following-\\? = nil
             with ,kanji-character-code? = nil

             ;; Splice in a different "with" clause for last-char-index, depending
             ;; on whether or not we are limiting gensym string length.
             ,@(if limit-string-length-p
                   `(with ,last-char-index fixnum =
                     (minf (1-f string-length)
                      (1-f maximum-length-for-user-gensym-strings)))
                   `(with ,last-char-index fixnum = (1-f string-length)))
             for character-index fixnum
                 = 0
                 then (if skip-this-character-p
                          character-index
                          (1+f character-index))
             while (<f character-index string-length)
             as last-character-p = (=f character-index ,last-char-index)
             as skip-this-character-p = nil

             ,@loop-clauses-to-get-next-character

             ;; Splice in the following "when" clause if there is a limit on
             ;; string length.
             ,@(if limit-string-length-p
                   `(when (=f character-index maximum-length-for-user-gensym-strings)
                     do (setq ,string-length-exceeded-p t)))

             ;; Splice in a different "unless" clause depending on whether or
             ;; not there is a limit on string length.
             ,@(if limit-string-length-p
                   `(unless (or skip-this-character-p ,string-length-exceeded-p))
                   `(unless skip-this-character-p))
             do
         (if ,string-is-simple-p
             (setf (schar ,gensym-string character-index) character)
             (setf (char ,gensym-string character-index) character))

         ;; This cond deals with seeing if we can get bad-state-p
         ;; to be true; it does nothing if it already is true
         (cond
           (,bad-state-p)
           ((not (simple-character-code-p character-code))
            (setq ,bad-state-p 'non-simple-character-code))
           (,escape-character?
            (case ,escape-character?
              (#\@
               (if (currently-legal-character-following-\@ character)
                   (setq ,escape-character? nil)
                   (setq ,bad-state-p 'bad-character-following-\@)))
              (#\~
               (if (map-to-roman-font-special-character-code-if-any character)
                   (setq ,escape-character? nil)
                   (setq ,bad-state-p 'bad-character-following-\~)))
              (#\\
               (cond
                 ((null ,first-character-code-following-\\?)
                  (setq ,first-character-code-following-\\? character-code))
                 ((null ,second-character-code-following-\\?)
                  (setq ,second-character-code-following-\\? character-code)
                  (if (not (<f ,first-character-code-following-\\? 40))
                      (setq ,kanji-character-code?
                            (+f (*f 95 ,first-character-code-following-\\?)
                                ,second-character-code-following-\\?
                                #.(+ (ash 33 13) (- (+ (ash 32 13) (* 95 40) 32)))))))
                 (t
                  (setq ,third-character-code-following-\\? character-code)
                  (setq ,kanji-character-code?
                        (+f (ashf ,first-character-code-following-\\? 13)
                            (*f 95 ,second-character-code-following-\\?)
                            ,third-character-code-following-\\?
                            #.(- (+ (ash 32 13) (* 95 40) 32))))))
               ;; Bad 2 char example: \8p
               ;; Bad 3 char example: \#[S
               (when (and ,first-character-code-following-\\?
                          ,second-character-code-following-\\?
                          (or ,third-character-code-following-\\?
                              (not (<f ,first-character-code-following-\\? 40))))
                 (cond
                   ((or (null ,kanji-character-code?)
                        ;; this was only checked during the 3.0 Rev. 0 release -- is
                        ;; now considered to have been a mistake -- overzealousness.
                        ;; (MHD/JH 11/18/92)
                        ; (not (legal-kanji-character-code-p ,kanji-character-code?))
                        )
                    (setq ,bad-state-p 'illegal-characters-following-\\))
                   (t
                    (setq ,escape-character? nil)
                    (setq ,first-character-code-following-\\? nil)
                    (setq ,second-character-code-following-\\? nil)
                    (setq ,third-character-code-following-\\? nil)
                    (setq ,kanji-character-code? nil)))))))
           ((or (char= character #\@)
                (char= character #\~)
                (char= character #\\))
            (setq ,escape-character? character)))

             ;; One more thing that can get us into a bad state is is leaving
             ;; escape-character? non-nil.  Note that we want to check this
             ;; whether or not we execute the "do" of the "unless" clause
             ;; spliced in above.
             do
         (if (and last-character-p
                  (not ,bad-state-p)
                  ,escape-character?)
             (setq ,bad-state-p 'incomplete-escape-sequence))

             finally
               (when ,bad-state-p
                 (setq ,gensym-string
                       (prog1
                         (copy-illegal-gensym-string-without-bad-characters ,gensym-string)
                         (reclaim-gensym-string ,gensym-string)))))
       (values ,gensym-string ,string-length-exceeded-p))))

#+development
(defvar string-for-provide-legal-gensym-string-minimal "~\\hello~\\there")

#+development
(defun provide-legal-gensym-string-minimal-form ()
  (provide-legal-gensym-string
    :form-to-determine-string-length
    (length string-for-provide-legal-gensym-string-minimal)
    :loop-clauses-to-get-next-character
    (do (setq character
              (schar string-for-provide-legal-gensym-string-minimal
                     character-index))
        (setq character-code (char-code character)))
     :gensym-string-obtainer obtain-simple-gensym-string
     :limit-string-length-p t))


;; jh, 3/23/92.  Created provide-legal-gensym-string-p to abstract similarities
;; between copy-string-filtering-out-non-gensym-characters and the ICP
;; reader for gensym-strings (see INT3).

;; mhd 4/8/92.  Note that skip-this-character-p  is currently only used in
;; read-character-sequence-as-gensym-string, and we should consider eliding it in
;; other uses, because of the fixed cost incurred even when it is not used.

;; jh, 5/28/92.  Protected provide-legal-gensym-string against variable capture of
;; those loop variables we don't want its users to know about.



;;; `Twrite-gensym-characters-from-ascii-string' interprets the characters in as
;;; ascii characters, and converts them if possible to gensym characters.
;;;
;;; If a character is outside the both the ASCII and Gensym repertoire of
;;; characters, it is normally dropped.
;;;
;;; Those that cannot be converted, notably Tab, are discarded.  Newlines are
;;; converted to the gensym character @L.
;;;
;;; However, a bone is thrown to the ASCII tab character, however, even though
;;; it is strictly outside of the Gensym character set.  If the optional arg
;;; spaces-for-tabs? is specified, it can be one of the following:
;;;
;;;    nil - (the default) - just strip tabs, i.e., treat them as a random
;;;    character outside the repertoire
;;;
;;;    fixnum integer - this many space characters are substituted (min: 0)
;;;
;;;    anything else - ("true") - one space character is inserted
;;;

#+gsi-web ; no callers outside of WebLink
(defun twrite-gensym-characters-from-ascii-string
    (ascii-string &optional spaces-for-tabs? (start 0) end?)
  (loop with string-is-simple? = (simple-gensym-string-p ascii-string)
        with length-of-string fixnum = (glength ascii-string string-is-simple?)
        with i fixnum = start
        with end = (if end? (minf end? length-of-string) length-of-string)
        with char
        until (=f i end)
        do (setq char
                 (read-simple-character-from-gensym-string
                   ascii-string i string-is-simple?))
           (character-case char
             ((#\\ #\~ #\@)
              (twrite-char #\~)
              (twrite-char char))
             (#\Newline
              (twrite-char #\@)
              (twrite-char #\L))
             (#.char-tab
              (loop repeat
                      (if spaces-for-tabs?
                          (if (fixnump spaces-for-tabs?)
                              spaces-for-tabs?
                              1)
                          0)
                    do (twrite-char #\space)))
             (t (when (simple-character-p char)
                  (twrite-char char))))))



;;; `Copy-string-filtering-out-non-gensym-characters' is used (among other
;;; places) in file contents into G2 text format.  It is distinct from
;;; convert-ascii-filename-to-gensym-string-as-much-as-possible and
;;; copy-ascii-string-as-gensym-string (q.v.).
;;;
;;; The former is designed to make file contents behave as intuitively as
;;; possible when transformed into G2 gensym-strings, the latter is for file
;;; namestrings.

;;; `Copy-string-filtering-out-non-gensym-characters' ...

(defun copy-string-filtering-out-non-gensym-characters (ascii-string)
  (declare (eliminate-for-gsi))
  (provide-legal-gensym-string
    :form-to-determine-string-length
    (length ascii-string)
    :loop-clauses-to-get-next-character
    (do (setq character (char ascii-string character-index))
        (setq character-code (char-code character)))))

;; The old name of this,
;; convert-ascii-string-to-gensym-string-as-much-as-possible, seemed wrong for
;; this purpose and right for another, useful purpose.  But I decided it would
;; be too confusing to keep the same name, and just change its meaning, so I
;; gave this function AND the new function new names.
;;
;; I know at one point the old name seemed to describe just what it does, but
;; on closer inspection, it fails.
;;
;; This doesn't translate from ASCII to Gensym, it just filters out non-gensym
;; characters.  The other function actually does character set translation.  The
;; old name was therefore misleading.
;;
;; Accordingly, I'm renaming other test functions in this area.  (MHD 10/12/94)

#+development
(defvar standard-gensym-character-filtering-test-strings
        ;; (<test-string> [<result if different>])
        '(("")                                        ; ok - empty string
          ("a b c")                                ; ok string
          ("a
b" "ab")                                        ; illegal return char
          ("a        b" "ab")                        ; illegal tab char
          ("foo@Lbar")                                ; legal @L
          ("foo@xbar" "foobar")                        ; illegal @ escape
          ("~@~\\~~")                                ; legal ~ escapes
          ("~" "")                                ; illegal ~ escape
          ("@" "")                                ; illegal @ escape
          ("\\" "")                                ; illegal \ escape
          ("\\n" "")                                ; illegal \ escape
          ("\\111")                                ; illegal \ escape
          ("\\nn" "\\nn")                        ; "\\nn" - legal \ escape
          ("\\8p" "\\8p")                        ; not a legal JIS code, but a
                                                ;   legal Gensym "Kanji" (Asian) code
                                                ;   - 2 char (we've relaxed to accept
                                                ;   well-formed Asian codes that
                                                ;   are non-JIS codes, since we'll
                                                ;   be adding character sets.
                                                ;   (MHD 11/3/94)
          ("\\8q")                                ; good Asian and JIS code - 2 char
          ("\\#[" "")                                ; bad Asian code - must be 3 char
          ("\\#[z" "\\#[z")                        ; good Asian code - (it's 3
                                                ;   char, though not JIS)
          ("\\#[T")                                ; good Kanji and Asian code
                                                ;   - 3 char

          ;; How about 8-bit characters?  (they're all bad characters)
          (#.(format nil "~c" (code-char 180)) "") ; bad - must be ascii (this
                                                   ; contains an 8 bit char)
          ))

#+development
(defun test-gensym-character-filtering ()
  (loop for (input output-if-different?)
            in standard-gensym-character-filtering-test-strings
        do
    (let ((expected-output (or output-if-different? input))
          (obtained-output
            (copy-string-filtering-out-non-gensym-characters
              input)))
      (unless (string= expected-output obtained-output)
        (cerror "Continue"
                "COPY-STRING-FILTERING-OUT-NON-GENSYM-CHARACTERS: ~
                 input ~s expected output ~s, got ~s."
                input
                expected-output
                obtained-output)))
    finally (return t)))


;; Some functions are handing NIL to
;; copy-string-filtering-out-non-gensym-characters.  Wrapped stringp test
;; around the body of this function until we can track down all the offending
;; callers.  (jh, 4/5/90)

;; jh, 1/30/92.  Added simple-character-p test to
;; copy-string-filtering-out-non-gensym-characters.  Now we replace any
;; non-simple character with an underscore.  There is a possibility that a raw
;; character received from GSI (or, for that matter, a strange character in a
;; filename) can crash G2 otherwise.  The underscore was chosen because it takes
;; up space (it wouldn't do simply to skip the offending character) and because it
;; is a legal constituent character in all the file systems we know about.  This
;; is by no means a solution to the general problem of importing text into G2.
;; One suggestion to make things more general would be to set an errno-like flag
;; when the string is read, and notify the appropriate facility (pathnames, GSI,
;; or something else) after the read is complete, to save time.

;; jh, 3/23/92.  Rewrote copy-string-filtering-out-non-gensym-characters
;; to use the provide-legal-gensym-string abstraction.








;;; Copy-illegal-gensym-string-without-bad-characters ...

(defun copy-illegal-gensym-string-without-bad-characters (string)
  (declare (eliminate-for-gsi))
  (twith-output-to-gensym-string
    (loop with string-is-simple? = (simple-gensym-string-p string)
          with end = (glength string string-is-simple?)
          with i = 0
          with character
          when (>=f i end)
            do (loop-finish)
          do (case (setq character
                         (read-string-character-from-gensym-string
                           string i string-is-simple?))
               (#\@
                (let ((character-following-\@?
                        (if (<f i end)
                            (read-string-character-from-gensym-string
                              string i string-is-simple?))))
                  (cond
                    ((and character-following-\@?
                          (simple-character-p character-following-\@?)
                          (currently-legal-character-following-\@
                            character-following-\@?))
                     (twrite-char character)
                     (twrite-char character-following-\@?)))))
               (#\~
                (let ((character-following-\~?
                        (if (<f i end)
                            (read-string-character-from-gensym-string
                              string i string-is-simple?))))
                  (cond
                    ((and character-following-\~?
                          (simple-character-p character-following-\~?)
                          (map-to-roman-font-special-character-code-if-any
                            character-following-\~?))
                     (twrite-char character)
                     (twrite-char character-following-\~?)))))
               (#\\
                (let* ((first-character-following-\\?
                         (if (<f i end)
                             (read-string-character-from-gensym-string
                               string i string-is-simple?)))
                       (second-character-following-\\?
                         (if (<f i end)
                             (read-string-character-from-gensym-string
                               string i string-is-simple?))))
                  (if (and first-character-following-\\?
                           (simple-character-p first-character-following-\\?)
                           second-character-following-\\?
                           (simple-character-p second-character-following-\\?))
                      (cond
                        ((long-kanji-character-p first-character-following-\\?)
                         (let ((third-character-following-\\?
                                 (if (<f i end)
                                     (read-string-character-from-gensym-string
                                       string i string-is-simple?))))
                           (if (and third-character-following-\\?
                                    (simple-character-p third-character-following-\\?))
                               (when t
                                 ;; this was only checked during the 3.0 Rev. 0 release -- is
                                 ;; now considered to have been a mistake -- overzealousness.
                                 ;; (MHD/JH 11/18/92)
;                                 (legal-kanji-character-code-p
;                                   (+f (ashf (char-code first-character-following-\\?) 13)
;                                       (*f 95 (char-code second-character-following-\\?))
;                                       (char-code third-character-following-\\?)
;                                       #.(- (+ (ash 32 13) (* 95 40) 32))))
                                 (twrite-char character)
                                 (twrite-char first-character-following-\\?)
                                 (twrite-char second-character-following-\\?)
                                 (twrite-char third-character-following-\\?)))))
                        (t
                         (when t
                           ;; this was only checked during the 3.0 Rev. 0 release -- is
                           ;; now considered to have been a mistake -- overzealousness.
                           ;; (MHD/JH 11/18/92)
;                           (legal-kanji-character-code-p
;                             (+f (*f 95 (char-code first-character-following-\\?))
;                                 (char-code second-character-following-\\?)
;                                 #.(+ (ash 33 13) (- (+ (ash 32 13) (* 95 40) 32)))))
                           (twrite-char character)
                           (twrite-char first-character-following-\\?)
                           (twrite-char second-character-following-\\?)))))))
               (t
                (if (simple-character-p character)
                    (twrite-char character)))))
    #+development
    (test-assertion
      (legal-gensym-string-p
        current-gensym-string 0 fill-pointer-for-current-gensym-string))))





;;;; Small 2D Arrays


;;; A small-2d-array is a two dimensional square array which can have, at most,
;;; the number of elements equal to the number of elements of a managed simple
;;; vector (or the value of maximum-managed-simple-vector-size).  The functions
;;; and macros for manipulating small-2d-arrays are:  allocate-small-2d-array,
;;; reclaim-small-2d-array, and small-2d-aref (which can be setf'ed).
;;; It should be noted that a 256 element array is always allocated because
;;; small-2d-arrays are intended to be used in places where speed is essential
;;; and fixing the size of the array allows fast access.
;;; Note that allocate-small-2d-array will set all the array's elements to nil.

(defun allocate-small-2d-array (size-of-each-dimension)
  #-development
  (declare (ignore size-of-each-dimension) (eliminate-for-gsi))
  #+development
  (if (>f (*f 2 size-of-each-dimension) maximum-managed-simple-vector-size)
      (error "Attempted to allocate a small-2d-array of size ~a by ~a ~ which ~
              would have more than ~a (maximum-managed-simple-vector-size) ~
              elements."
             size-of-each-dimension
             size-of-each-dimension
             maximum-managed-simple-vector-size))
  (let* ((array
           (allocate-managed-simple-vector maximum-managed-simple-vector-size)))
    (loop for index from 0 to #.(- maximum-managed-simple-vector-size 1)
          do (setf (svref array index) nil))
    array))


(defmacro reclaim-small-2d-array (small-2d-array)
  `(reclaim-managed-simple-vector ,small-2d-array))


;;; The macro `convert-2d-array-indexes-to-index' converts an 2d (x,y) index to
;;; a physical, 1d index for accessing a small-2d-array type of structure.

(defmacro convert-2d-array-indexes-to-index (x-index y-index)
  (let* ((dimension-size (truncate (sqrt maximum-managed-simple-vector-size)))
         (use-ashf-p (or (= dimension-size 2)
                         (= dimension-size 4)
                         (= dimension-size 8)
                         (= dimension-size 16))))
    `(+f ,x-index
         (,(if use-ashf-p
               'ashf
               '*f)
           ,y-index
           ,(if use-ashf-p
                (truncate (log dimension-size 2))
                dimension-size)))))

;; Used below and in allocate-bigger-stored-raster (WINDOWS1).  (MHD 8/18/98)


;;; `Small-2d-aref' ... Ex. (small-2d-aref array-1 x y)

(defmacro small-2d-aref (small-2d-array x-index y-index)
  `(svref ,small-2d-array
          (convert-2d-array-indexes-to-index ,x-index ,y-index)))




;;;; Handy String Functions


(defun-for-macro substring (string from &optional to)
  (subseq (string string) from to))

(defun-for-macro string-search-set (char-set string &key from-end (start 0) end)
  (position-if #'(lambda (ch) (find ch char-set :test #'char-equal))
               (string string) :from-end from-end :start start :end end))


;;; The function `parse-string-into-words' splits a string into a list of
;;; words. The delimiter chars are normally discarded.

(defun-for-macro parse-string-into-words
    (string &key (delimiters '(#\- #\space #\tab #\.))
            preserve-delimiters
            (start 0)
            (end (length string)))
  (loop for i = start then (1+ j)
        while (< i end)
        for j = (or (string-search-set delimiters string :start i) end)
        if (/= i j)
          collect (substring string i j)
          and if (and preserve-delimiters (< j end))
                collect (substring string j (1+ j))))


(defun-for-macro string-search (key string &key from-end (start1 0) end1 (start2 0) end2)
  (search (string key) (string string) :from-end from-end :start1 start1 :end1 end1
          :start2 start2 :end2 end2 :test #'char-equal))


(defun-for-macro string-append (&rest strings)
  (apply #'concatenate 'string (mapcar #'string strings)))


;;; The function `string-difference' removes s2 from s1.

(defun-for-macro string-difference (s1 s2 &key from-end)
  (let ((spot (string-search s2 s1 :from-end from-end)))
    (if spot
        (string-append (substring s1 0 spot) (substring s1 (+ spot (length s2))))
        s1)))




;;;; Stuff for Defstruct





;;; The package `G2-DEFSTRUCT-STRUCTURE-NAME' is created to provide a different
;;; naming environment for structure names than we have for class names.  All
;;; structure names will be interned in this package.  This package "uses" no
;;; other packages, not even the lisp package.  The global
;;; `the-g2-defstruct-package' is bound to the package to provide efficent
;;; access.

;;; Developers can map over this package to find all structures, but beware that
;;; many implementations tend to push a few additional symbols into every
;;; package, NIL for example.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar the-g2-defstruct-package (find-package "G2-DEFSTRUCT-STRUCTURE-NAME")))

(intern "TYPE-DESCRIPTION-G2-STRUCT" the-g2-defstruct-package)






;;; The macro `intern-unique-def-structure-symbol-name' takes a def-structure
;;; symbol name and returns a symbol which is used to uniquely mark structure
;;; instances as members of this structure class.  Currently the guarantee is
;;; maintained by placing these returned symbols into a package other than AB.
;;; The concern is that user defined class names should never collide with these
;;; structure names.  This could also be guaranteed by inserting characters into
;;; this symbol name which cannot be entered by users as portions of their class
;;; names.

(defmacro intern-unique-def-structure-symbol-name (symbol)
  (if (and (consp symbol)
           (eq (car symbol) 'quote))
      `',(intern
           (format nil "~A-G2-STRUCT" (symbol-name (eval symbol)))
           the-g2-defstruct-package)
      `(intern
         (format nil "~A-G2-STRUCT" (symbol-name ,symbol))
         the-g2-defstruct-package)))


;;; `G2-type-name-of-named-simple-vector' returns the zeroth element
;;; of a simple-vector, this happens to be where the g2 type name
;;; of both frames and g2 structures are stored.

;;; Note that element zero in simple vectors is used for other things
;;; in G2.  Examples include the simple-vector pools use element zero
;;; to chain vectors togther.  Managed arrays use element zero for
;;; the managed-array-identity-marker.

(defmacro g2-type-name-of-named-simple-vector (simple-vector)
  `(svref ,simple-vector 0))




;;; The function `allocated-named-gensym-structure-p' is a predicate which
;;; determines if the given thing is an instance of a Gensym structure as
;;; defined by defstruct-g2.  It can only recognize allocated Gensym structures,
;;; since their type slots are used as to chain together unallocated structures.

(defun allocated-named-gensym-structure-p (thing)
  (and (simple-vector-p thing)
       (>= (length thing) 1)
       (symbolp (g2-type-name-of-named-simple-vector thing))
       (eq (symbol-package (g2-type-name-of-named-simple-vector thing))
           the-g2-defstruct-package)))



;;; Option-equal and remove-entry-given-car are used in the def-structure macro to
;;; remove options from a list.

(defun-for-macro option-equal (option option-entry)
  (if (consp option-entry)
      (eq option (car option-entry))
      (eq option option-entry)))

(defun-for-macro remove-entry-given-car (option option-list)
  (remove option option-list :test 'option-equal))


;;; `Type-description-of-unique-type-name-of-gensym-structure' returns the
;;; type description structure given the unique type name of the structure.

(def-global-property-name type-description-of-unique-type-name-of-gensym-structure)







;;;; Type Descriptions

;;; `Type descriptions' are g2 structures that encapsulate knowledge about the
;;; various types found in G2.  For example structures.  Currently these are
;;; only generated for g2-structures.

;;; For those type descriptions that are named by a symbol <type-name> we can reach the
;;; type description either via a property on <type-name> or via the global
;;; value of the symbol THE-TYPE-DESCRIPTION-OF-<type-name>.

;;; `Build-type-description-var-of-type-name' maybe used at compile time to
;;; find the symbol who's symbol value holds the type description for a given
;;; type-name.


(defun-for-macro build-type-description-var-of-type-name (type-name)
  (build-ab-symbol "the-type-description-of" type-name))

;;; `Type-description-of-type' maps from type-name to type description, it a
;;; global property.  (Which is wrong since I want these to be KB specific, but
;;; that doesn't show up until utilities4.lisp.

; (def-global-or-kb-specific-property-name type-description-of-type)
(def-global-property-name type-description-of-type)



;;; `Type-description-of' returns the type description of an instance.  At
;;; present, this instance must already be known to be a gensym-structure.

(defun-substitution-macro type-description-of-1 (thing)
  (let ((possible-type-name?))
    (when (and (simple-vector-p thing)
               (<= 1 (length thing))
               (setf possible-type-name?
                     (g2-type-name-of-named-simple-vector thing))
               (symbolp possible-type-name?))
      (type-description-of-unique-type-name-of-gensym-structure
        possible-type-name?))))

(defun type-description-of (thing)
  (or
    (type-description-of-1 thing)
    #+development
    (error "No type-description inferable for ~S" thing)))

(defun-substitution-macro type-description-of-structure (structure-instance)
  (type-description-of-unique-type-name-of-gensym-structure
    (g2-type-name-of-named-simple-vector structure-instance)))







;;; `Def-early-structure' is analagous to def-structure.  It is used only
;;; to define structures in used in bootstrapping def-structure, and the
;;; rest of the type system.  The slot descriptions must include an
;;; initial value, and not slot options.  Accessors macros are generated,
;;; and a function "build-<structure-name>" of no arguments that conses
;;; a fresh instance of the structure.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro def-early-structure (structure-type-name &body slot-names)
  `(progn
     ,@(loop for (slot-name) in slot-names
             as i from 0
             collect `(defmacro ,slot-name (,structure-type-name)
                        (list 'svref ,structure-type-name ,i)))
     (def-substitution-macro ,(build-ab-symbol "build" structure-type-name) ()
       (let ((#1=#:result (make-array ,(length slot-names))))
         ,@(loop for (nil initial-value) in slot-names
                 as i from 0
                 collect `(setf (svref #1# ,i) ,initial-value))
         #1#))
     ))
)

;;; The `type-descriptor' structure
(eval-when (:compile-toplevel :load-toplevel :execute)
(def-early-structure type-description
    (type-name-of-type-description 'g2-defstruct-structure-name::type-description-g2-struct)

  (name-of-type-description nil)

  ;; Subtype Lattice.
  ;; These are all lists of type names (Note <type-name>)
  (inheritance-path-of-type-description nil)
  (direct-superiors-of-type-description nil)
  (direct-inferiors-of-type-description nil)

  ;; Slots.
  (slot-descriptions-of-type-description nil)
  (direct-slots-of-type-description nil) ;; a list of slot names
  (performance-hack-for-slot-of-type-description-tbd nil)  ;; Unused.

  ;; Methods.
  (direct-methods-of-type-description nil) ;; a list of pairs (<method> <function>)
  (method-table-of-type-description (make-array 10))

  ;; Other.
  (alist-of-type-description nil)
  (flags-of-type-description 0)
  (instance-length-of-type-description 0)
  (user-vector-length-of-type-description 0)
  (subclass-of-item-for-type-description nil)

  ;; Subtypep implementation
  (serial-number-of-type-description 0)
  (subtype-p-bit-vector-of-type-description nil))
)

;;; The slots in type descriptions are carefully arranged to get them to line up
;;; with those in class descriptions.  But the names are not the same.

;;; The type lattice is recorded in the two slots
;;; `direct-superiors-of-type-description' and
;;; `direct-inferiors-of-type-description', while the linearization of the type
;;; superiors is recorded in `inheritance-path-of-type-description.'

;;; Note that if you recompile a file, after latter files have been loaded, the
;;; resulting binary will include forward references to inferiors types.

;;; The `direct-methods-of-type-description' slot of a type-description is a
;;; list of pairs, an alist keyed by the method name, the second element is the
;;; function that implements the method.  For example, ((EXECUTE-EVENT
;;; EXECUTE-EVENT-FOR-DRAGGING-STATE))


;; Note <type-name>: The type-name will, eventually, be have a type-description
;; on it.  Forward references to types can happen.  It happens when a file is
;; recompiled in a fully loaded system.  In that situations all inferior types
;; are known.  When that file is then loaded into an image from scratch, these
;; will be foward references.



;;; `Type?' returns true if the symbol given has a type description.

(defmacro type? (type)
  `(type-description-of-type ,type))


;;; `Subtype-p-using-type-descriptions' is just like subtype-p in common lisp,
;;; except that it takes type-descriptions, not type specifications.

(defun-simple subtype-p-using-type-descriptions
    (refined-type-description superior-type-description)
  (loop for superior-type in (inheritance-path-of-type-description refined-type-description)
        when (eql (type-description-of-type superior-type) superior-type-description)
          return t))








;;; `Build-type-descriptor-of-t' is the macro used to compute
;;; the intial value of `the-type-descriptor-of-t', the root
;;; type descriptor lattice.

(defmacro build-type-description-of-t ()
  (let ((name (build-type-description-var-of-type-name t))
        (compile-time-type-description (build-type-description)))
    (setf (name-of-type-description compile-time-type-description) t)
    `(progn
       (defvar ,name (optimize-constant ',compile-time-type-description))
       (setf (type-description-of-type t) ,name))))

(build-type-description-of-t)



;;; The `simple-slot-description' structure is used to store in the declartive
;;; knowledge about a slot.

(def-early-structure basic-slot-description
    (type-description-of-slot-description nil)
    (slot-name-of-slot-description nil)
    (defining-type-of-slot-description nil)
    (init-form-of-slot-description nil)
    (slot-index-of-slot-description nil)
    (user-slot-index-of-slot-description nil)
    (alist-of-slot-description nil))













;;;; The Structure Method Dispatch Table


;;; `Maximum-number-of-structure-methods' is a constant, changeing it must
;;; force a full recompile.
;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter maximum-number-of-structure-methods 40) ; 10 => 20 (MHD 11/8/95); 20 => 40 (MHD 8/1/96); 40 => 80 -dougo, 8/22/05; 80 => 40 -dkuznick, 5/23/06
)

(defvar table-to-map-structure-id-to-method-name
  (make-array-with-nils maximum-number-of-structure-methods))

(defmacro map-structure-id-to-method-name? (id)
  `(svref table-to-map-structure-id-to-method-name ,id))

(defmacro map-structure-method-name-to-id? (method-name)
  (avoiding-variable-capture (method-name)
    `(loop
      for id from 0 below maximum-number-of-structure-methods
      when (eql (map-structure-id-to-method-name? id) ,method-name)
      do (return id))))

(defmacro def-generic-structure-method-id (method-name id)
  (unless (and (symbolp method-name)
               (fixnump id)
               (< 0 id maximum-number-of-structure-methods))
    (warn "Def-generic-structure-method-id for ~S malformed." method-name))
  `(progn
     #+development
    (unless (or (null (map-structure-id-to-method-name? ,id))
                (eql (map-structure-id-to-method-name? ,id) ',method-name))
      (warn "Oh NO!! attempting to redefine id for ~
                                 def-generic-structure-method-id for method ~S."
            ',method-name)
      ;; I don't get the following code -- there's no "system" when you're
      ;; running this code, i.e., compile or load time.  It bombed out, saying
      ;; as much... (MHD 8/11/96)
;      (current-system-case
;        ((ab telewindows) (warn "Oh NO!! attempting to redefine id for ~
;                                 def-generic-structure-method-id for method ~S."
;                                ',method-name))
;        (gsi (format t "Oh NO!! attempting to redefine id for ~
;                    def-generic-structure-method-id for method ~S."
;                     ',method-name)))
      )
    (setf (map-structure-id-to-method-name? ,id) ',method-name)))
;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter undefined-structure-method-message
  "Call to structure method where none was defined.")
)

(defmacro signal-undefined-structure-method ()
  `(error #.undefined-structure-method-message)
  ;; Ditto! (MHD -- see above -- 8/11/96)
;  `(current-system-case
;     ((ab telewindows) (error #.undefined-structure-method-message))
;     (gsi (signal-gsi-undefined-structure-method-error)))
  )

(defun undefined-structure-method-function
    (structure-type &optional a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11)
  (declare (ignore structure-type a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11))
  (signal-undefined-structure-method))

(defmacro superior-dispatch-table (dispatch-table)
  `(svref ,dispatch-table 0))

(defun make-structure-method-table (superior-dispatch-table?)
  (let ((dispatch-table
         (if superior-dispatch-table?
             (make-array maximum-number-of-structure-methods
                         :initial-contents superior-dispatch-table?)
             (make-array maximum-number-of-structure-methods
                         :initial-element 'undefined-structure-method-function))))
    (setf (superior-dispatch-table dispatch-table) superior-dispatch-table?)
    dispatch-table))












;;;; Enumeration of ALL methods on structures.

;; The number zero is taken.

(def-generic-structure-method-id clean-up-workstation-context 1)
(def-generic-structure-method-id track-mouse-into-spot 2)
(def-generic-structure-method-id reclaim-structure 3)
(def-generic-structure-method-id valid-workstation-context-p 4)
(def-generic-structure-method-id setup-workstation-context 5)
(def-generic-structure-method-id suspend-workstation-context 6)
(def-generic-structure-method-id resume-workstation-context 7)
(def-generic-structure-method-id read-character-code 8) ; gensym-string-stream
(def-generic-structure-method-id clean-up-structure 9)  ; Generic version of method #3
(def-generic-structure-method-id initialize-text-sequence-string 10)
(def-generic-structure-method-id read-character-from-text-sequence 11)
(def-generic-structure-method-id transcode-character 12)
(def-generic-structure-method-id twrite-unicode-from-transcoder 13)
(def-generic-structure-method-id transcode-as-text-string 14)
(def-generic-structure-method-id export-character 15)
(def-generic-structure-method-id export-as-string 16)
(def-generic-structure-method-id twrite-for-export-from-transcoder 17)
(def-generic-structure-method-id map-code-to-unicode 18)
(def-generic-structure-method-id map-unicode-to-code-if-any 19)
(def-generic-structure-method-id handle-read-event      20)
(def-generic-structure-method-id handle-write-event     21)
(def-generic-structure-method-id handle-network-connect 22)
(def-generic-structure-method-id handle-network-accept  23)
(def-generic-structure-method-id handle-network-close   24)
(def-generic-structure-method-id handle-g2-reset        25)
(def-generic-structure-method-id get-cached-explanation-evaled-variables-if-any 26)
(def-generic-structure-method-id make-cached-explanation-node 27)
(def-generic-structure-method-id return-cached-explanation-if-valid 28)
(def-generic-structure-method-id export-cached-explanation-node 29)












;;;; Developer Debugging Tools



;;; This section provides some tools for inserting debugging code into
;;; the sources.  Debugging code should evaporate outside of development.
;;; This can be done directly by guarding the code with #+development,
;;; or indirectly by using some of the macros defined below that will
;;; expand to nil outside of development.

;;; `*debug*' may be bound to a non-nil file to create a dynamic extent
;;; where debug tracing is enabled.

#+development
(defvar *debug* nil)



;;; `DFormat' is analagous to format, except the stream argument is
;;; elided.  It will output to T when *debug* is non-nil.  Any uses
;;; of it must be guarded by #+development

#+development
(defmacro dformat (&body body)
  `(when *debug*
     (with-dynamic-creation
       (terpri)
       (format t ,@body)
       (force-output))))







;;; `With-zwei-output' is analagous to with-open-file.  Output to the stream it
;;; binds will append that output to a ZWEI buffer.  Uses of this must be
;;; guarded by #+development.  And optional third argument, if non-nil, will
;;; cause any output to be broadcast to *standard-output* as well.

#+development
(defmacro with-zwei-output ((stream buffer-name &optional broadcast-to-standard-output-as-well-p)
                            &body body)
  #+lucid (declare (ignore broadcast-to-standard-output-as-well-p buffer-name))
  #+lucid
  `(let ((,stream *standard-output*)) ,@body)
  #-lucid
  `(with-open-stream (,stream
                        ,(if (not broadcast-to-standard-output-as-well-p)
                             `(open-editor-stream-or-bitsink ,buffer-name)
                             `(make-broadcast-stream
                                *standard-output*
                                (open-editor-stream-or-bitsink ,buffer-name))))
     ,@body))


;;; `With-debug-output', `db-format', `db-dump', and `db-dump*' expand to NIL outside of development.
;;; They are all used to emit tracing output to the ZWEI buffer "ab-debug-output."
;;; - With-debug-output wraps a body where in *standard-output* is redirected to
;;;   that buffer.
;;; - Db-format is analagous to format, except the stream is eluded, and output is
;;;   sent to that buffer.
;;; - Db-dump takes a list of expressions, they and the result of evaluating them are
;;;   sent to that buffer.
;;; - Db-dump* behaves as db-dump, but only if *debug* is non-nil.

(defmacro with-debug-output (&body body)
  #-development (declare (ignore body))
  #-development nil
  #+development `(with-zwei-output (*standard-output* "ab-debug-output")
                   ,@body))

(defun db-format (&rest args)
  #-development (declare (ignore args))
  #-development nil
  #+development (with-dynamic-creation
                  (with-debug-output
                    (apply (lisp-format) t args)
                    (force-output))))

(defmacro db-dump (&rest stuff)
  #-development (declare (ignore stuff))
  #-development nil
  #+development `(db-format "~2&(~@{~S ~S~^~&  ~})"
                            ,@(loop for i in stuff
                                    nconc `(',i ,i))))

(defmacro db-dump* (&rest stuff)
  #-development (declare (ignore stuff))
  #-development nil
  #+development `(when *debug*
                   (db-dump ,@stuff)))




;;;; Outliner for Development



;;; `Outline-tree-of-nodes' is a workhorse routine that will display an outline on
;;; standard output of a spanning tree over a graph of nodes.  It is available
;;; only in development for looking at data structures.  It takes a mess of
;;; parameters.

;;; The scale of the outline maybe controled by binding *print-length* and
;;; *print-depth*, as in lisp.

;;; Two nodes are assumed to be identical if they are EQL.  A list of all nodes
;;; seen is accumulated during the walk.  The children of a node are not outlined
;;; if the node has already been seen, such nodes are marked by "^" in the printout.

;;; Child-Generator, the first parameter, is a function which when applied to a
;;; node in the tree will generate the set of children.  Node, the second
;;; parameter, is the node currently being outlined.  Depth, the third, is the
;;; integer count of how deep we are.  Already-seen, the fourth parameter, is a
;;; cons, the cdr of which contains a list of the nodes already seen.  Visible-p
;;; is a function on nodes that returns a boolean indication that this node is
;;; or isn't visible.

;;; See outline-subblocks for a simple example use.

#+development
(defun outline-tree-of-nodes (child-generator node depth already-seen visible-p &optional (printer #'princ))
  (multiple-value-bind (ignore id)
      (push-outline-node node)
    (declare (ignore ignore))
    (if (=f 0 depth)
        (format t "~&<~2D> " id)
        (format t "~&~VT<~2D> " depth id))
    (funcall printer node))
  (cond
    ((memq node already-seen)
     (format t " ^"))
    ((push node (cdr already-seen))
     (if (<= *print-level* depth)
         (format t " ...")
         (loop for child in (funcall child-generator node)
               as visible = (or (funcall visible-p child)
                                (eql child node))
               as i = 1 then (if visible (1+ i) i)
               when visible do
                   (outline-tree-of-nodes child-generator child (1+ depth) already-seen
                                          visible-p printer)
                   (when (eql i *print-length*)
                     (format t "~&~VT ..." depth)
                     (return nil)))))))




;;; `Outline-node-ring-buffer' is used to remember and the last hundred
;;; nodes outlined.  These can then be fetched with get-outline-node or
;;; more mnemonicly with the function `gon'.  These access functions will
;;; take either a numeric <id> or a type name and they return the latest
;;; matching entry.

;;; Like the outliner this is a development only facility.

#+development
(defvar outline-node-ring-buffer (make-array 100))
#+development
(defvar outline-node-ring-buffer-last-entry 0)
#+development
(defvar outline-node-ring-buffer-oldest-entry? nil)

#+development
(defun push-outline-node (new-entry)
  (macrolet ((bump (pointer)
               `(setf ,pointer (modf (1+f ,pointer) length))))
    (let ((length (length outline-node-ring-buffer)))
      (bump outline-node-ring-buffer-last-entry)
      (cond
        ((null outline-node-ring-buffer-oldest-entry?)
         (setf outline-node-ring-buffer-oldest-entry?
               outline-node-ring-buffer-last-entry))
        ((= outline-node-ring-buffer-oldest-entry?
            outline-node-ring-buffer-last-entry)
         (bump outline-node-ring-buffer-oldest-entry?)))
      (values
       (setf (svref outline-node-ring-buffer
                    outline-node-ring-buffer-last-entry)
             new-entry)
       outline-node-ring-buffer-last-entry))))



;;; `Get-outline-node' searches for something matching designation given.  Given
;;; a number it returns the element in the outline history of that ID.  Given a
;;; symbol it looks first for something of that type in the outline history.
;;; Then it looks for something of that name.  It then looks for something in
;;; the * for something of that type.  It then looks tries current-instance to
;;; for something of that type.

#+development
(defun get-outline-node (number-or-type)
  (block :got-it
    (macrolet ((got-it (x) `(return-from :got-it ,x))
               (ab-type (x)
                 `(let ((raw-type (if (gensym-structure-or-frame-p ,x)
                                      (g2-type-name-of-named-simple-vector ,x)
                                      (type-of ,x))))
                    (if (and (symbolp raw-type)
                             (get raw-type 'ab-name-of-unique-structure-type))
                        (get raw-type 'ab-name-of-unique-structure-type)
                        raw-type))))
      (when (symbolp number-or-type)

        ;;! Note: When adding clauses be sure they are
        ;;! functional outside of the G2 process.

        ;; Look in the outline History
        (when outline-node-ring-buffer-oldest-entry?
          (loop with length = (length outline-node-ring-buffer)
             for i = outline-node-ring-buffer-last-entry then (modf (1-f i) length)
             as node = (svref outline-node-ring-buffer i)
             as ab-type = (ab-type node)
             when (eql number-or-type ab-type)
             do (got-it node)
             until (=f i outline-node-ring-buffer-oldest-entry?)))

        ;; Look for things with this name
        (cond
          ;; in the current KB
          ((and (boundp '*current-kb-specific-property-list-property-name*)
                *current-kb-specific-property-list-property-name*)
           (when (lookup-kb-specific-property-value
                  number-or-type
                  'frame-or-frames-with-this-name)
             (got-it (lookup-kb-specific-property-value
                      number-or-type
                      'frame-or-frames-with-this-name))))
          ;; unique in one and only one KB.
          (T
           (loop with result?
              finally (when result? (got-it result?))
              for (nil value) on (symbol-plist number-or-type) by #'cddr
              as frame-or-frames-with-this-name?
              = (if (listp value) (getf value 'frame-or-frames-with-this-name))
              when (and frame-or-frames-with-this-name?
                        result?)
              do (got-it :in-multiple-kb)
              do (setf result? frame-or-frames-with-this-name?))))

        ;; Look for in the output history.
        (loop for i from output-recording-next-id
           downto output-recording-minimum-id
           as x = (output-recording-get-object i)
           when (eql (ab-type x) number-or-type)
           do (got-it x))

        ;; Look for in the * history.
        (loop for i in (list * ** ***)
           when (eql (ab-type i) number-or-type)
           do (got-it i))
        ;; Look via Current Instance.
        (when (and (lookup-global-or-kb-specific-property-value
                    number-or-type 'class-description)
                   (ci number-or-type))
          (got-it (ci number-or-type)))

        ;; Look in the current dynamic extents.
        (let ((result?
               (search-dynamic-extent-for-thing-of-type number-or-type)))
          (when result? (got-it result?)))

        ;; Try the magic-argument-fetcher on the latest mouse pointer
        (when (get number-or-type 'magic-argument-fetcher)
          (when (and (boundp 'system-window)
                     (fboundp 'magic-argument-of-latest-event))
            (let* ((current-workstation ;; improve chance fetcher will work.
                    (if (boundp 'current-workstation)
                        (symbol-value 'current-workstation)
                        (workstation-this-is-on-function
                         (symbol-value 'system-window))))
                   (result?
                    (funcall 'magic-argument-of-latest-event
                             number-or-type)))
              (declare (special current-workstation))
              (when result?
                (got-it result?))))))
      (when (fixnump number-or-type)
        (got-it
         (if (<= (length outline-node-ring-buffer) number-or-type)
             (or (output-recording-get-object number-or-type)
                 :unknown)
             (svref outline-node-ring-buffer number-or-type))))
      :unknown
      )))

#+development
(defun gon (number-or-type) (get-outline-node number-or-type))

#+development
(defun @ (number-or-type) (gon number-or-type))





;;;; Enumerated Types


;;; [This crud is used only by the icon editor].


;;; The macro `def-enumerated-type' generates macros and functions.  One
;;; function, the enumerated type index function, maps a symbol to a number.
;;; For example:
;;;
;;;   (def-enumerated-type icon-editor-engine
;;;     (change-size resize)
;;;     shrink-wrap
;;;     :skip
;;;     set-main-color-name)
;;;
;;; will generate a function (<name>-FUNCTION) called icon-editor-engine which
;;; will take a symbol and will return a number (the index).
;;; (icon-editor-engine-function 'resize) will return 0.  A :skip is a place
;;; holder, and will ensure that the index whose position the :skip is
;;; occupying is not used.
;;;
;;; A macro corresponding to the enumerated type index function is also
;;; generated.  The macro's name is the type name.  In our example, it is
;;; icon-editor-engine.
;;;
;;; A macro <name>-P is also generated to see check if an object is of the
;;; right type and range.  In our example, icon-editor-P.
;;;
;;; Def-enumerated-type also generates a CASE statement (icon-editor-engine-CASE in
;;; the example), which takes the enumerated symbols in the same syntax as the Common
;;; Lisp CASE statement.  The enumerated case statement is macroexpanded into
;;; a Common Lisp statement with fixnums (i.e. the indexes) as the keys.
;;;
;;; The purpose of this facility is to provide a means of implementing very fast
;;; CASE-like operations, using indexes instead eql comparisons of symbols.
;;;
;;; In macro compiles, the constant <name>-largest-index is bound to the largest
;;; index which is used (0 being the smallest).

(defun-for-macro make-enumerated-type-case
                 (keyform enumerated-type-index-function case-clauses)
  (let ((case-body
          (loop with enumerated-type-case-body = nil
                for (key-or-keys . consequents) in case-clauses
                do
            (push
              `(,(cond
                   ((or (eq key-or-keys t) (eq key-or-keys 'otherwise))
                    key-or-keys)
                   ((listp key-or-keys)
                    (mapcar enumerated-type-index-function key-or-keys))
                   (t
                    (funcall-symbol enumerated-type-index-function key-or-keys)))
                 ,@consequents)
              enumerated-type-case-body)
                finally
                  (return (nreverse enumerated-type-case-body)))))
    `(case (the fixnum ,keyform)
       ,@case-body)))

;; Note on optimization:  We could optimize the case statement above to
;; do a computed goto (instead of doing eql tests on fixnums) if the compiler
;; doesn't do it.  -pto 13sep89

(defmacro def-enumerated-type (type-name &body ordered-list-of-symbols)
  (let* ((cond-body nil)
         (index 0)
         (index-p-name (intern (format nil "~a-P" type-name)))
         (index-function-name (intern (format nil "~a-FUNCTION" type-name)))
         (index-macro-name (intern (format nil "~a" type-name)))
         (case-statement-name
           (intern (format nil "~a-CASE" type-name)))
         (largest-index-name
           (intern (format nil "~a-LARGEST-INDEX" type-name))))
    (declare (type fixnum index))
    (loop for symbol-or-list-of-symbol in ordered-list-of-symbols
          do
      (if (not (eq symbol-or-list-of-symbol :skip))
          (push
            `((,(if (listp symbol-or-list-of-symbol)
                    'memq
                    'eq)
               symbol ',symbol-or-list-of-symbol)
              ,index)
            cond-body))
      (incff index))
    (let* ((largest-index (-f index 1))
           (cond-form
             `(cond ,@cond-body
                    ,@(if (eval-feature :development)
                          `((t (error
                                 ,(format
                                    nil
                                    "The symbol ~~a is not an enumerated type of ~a."
                                    type-name)
                                 symbol)))))))
      (declare (type fixnum largest-index))
      `(eval-when (:compile-toplevel :load-toplevel :execute)
         (defconstant-for-macro ,largest-index-name ,largest-index)
         (def-substitution-macro ,index-p-name (object)
           (and (typep object 'fixnum)
                (<=f 0 object ,largest-index)))
         (defun-for-macro ,index-function-name (symbol)
;           (if (or (boundp 'system-is-running)
;                   (boundp 'system-has-paused))
;               (cerror
;                 "Continue, and will fix later."
;                 ,(format nil "~a is a compile time function, and shoud not be ~
;                                called when the system is running."
;                          type-name)))
           ,cond-form)
         (defmacro ,index-macro-name (symbol-to-be-evaled)
           (let* ((symbol (eval symbol-to-be-evaled)))
             ;; ,cond-form
             (,index-function-name symbol)
            ))
         (defmacro ,case-statement-name (keyform &body clauses)
           (make-enumerated-type-case keyform ',index-function-name clauses))))))




;;;; Lambda-list Destructuring




(defvar-for-macro empty-binding-marker (make-symbol "EMPTY-BINDING-MARKER"))



;;; The macro `destructuring-lambda-list' is like gensym-dstruct-bind except
;;; that it allows lambda-list-keywords in the destructuring pattern, its
;;; calling syntax matches that of lisp:gensym-dstruct-bind, and it is less
;;; efficient.  There is no error checking for expressions which do not match
;;; the lambda-list.  It does handle named keyword arguments but does NOT
;;; understand supplied-p arguments.  Arguments named NIL or IGNORE in the
;;; lambda-list will not be bound.

(defmacro destructuring-lambda-list (lambda-list expression &body body)
  (let* ((var (if (symbolp expression) expression (gensym)))
         (bindings-and-forms (destructure-lambda-list-1 lambda-list var))
         (bindings (loop for element in bindings-and-forms
                         unless (eq (first element) empty-binding-marker)
                           collect element))
         (forms (loop for element in bindings-and-forms
                      when (eq (first element) empty-binding-marker)
                        collect (second element))))
    (multiple-value-bind (declarations body)
        (parse-body-declarations body)
      `(let* (,@(if (not (eq var expression)) `((,var ,expression)))
                ,@bindings)
         ,@declarations
         ,@forms
         ,@body))))


;;; The defun-for-macro `destructure-lambda-list-1' returns a list of bindings,
;;; one for each dummy argument in the lambda-list.  Any bindings of the form
;;; (#:empty-binding-marker form) are not really bindings, but are rather forms to be
;;; evaluated in the body of the resulting LET.  Handles &optional, &rest and
;;; &key.  This doesn't completely syntax-check the lambda-list.  Also, we rely
;;; completely on the compiler to optimize!!

(defun-for-macro destructure-lambda-list-1 (lambda-list form)
  (let (bindings)
    (flet ((emit-binding (var value)
             (unless (member var '(ignore nil))
               (push `(,var ,value) bindings)))
           (emit-form (form)
             (push `(,empty-binding-marker ,form) bindings)))
      (cond ((null lambda-list)
             nil)
            ((symbolp lambda-list)
             (emit-binding lambda-list form))
            ((not (consp lambda-list))
             (error "Weird lambda-list in destructure-lambda-list-1: ~s" lambda-list))
            ((member (car lambda-list) '(&optional &rest &key))
             (let ((f form)                        ; cdr down each of these.
                   (p lambda-list))

               (when (eq (car p) '&optional)
                 (setq p (cdr p))
                 (do ((elem (car p) (car p)))
                     ((or (null p)
                          (member elem '(&key &rest))))
                   (cond ((listp elem)                ; &optional (x y)
                          (emit-binding (car elem) `(if ,f (car ,f) ,(cadr elem))))
                         (t
                          (emit-binding elem `(car ,f))))
                   (setq f `(cdr ,f)
                         p (cdr p))))

               (when (eq (car p) '&rest)
                 (emit-binding (cadr p) f)
                  (setq p (cddr p)))

               (when (eq (car p) '&key)
                 (setq p (cdr p))
                 (loop with warn-p = (not (memq '&allow-other-keys p))
                       for element in p
                       as variable = (cond ((atom element) element)
                                           ((atom (car element)) (car element))
                                           (t (second (car element))))
                       as default = (cond ((atom element) nil)
                                          (t (second element)))
                       as keyword = (cond ((or (atom element) (atom (car element)))
                                           (intern (string variable)
                                                   (find-package "KEYWORD")))
                                          (t (first (car element))))
                       collect keyword into allowed-keywords
                       unless (memq element lambda-list-keywords)
                         do (emit-binding variable `(getf ,f ,keyword ,@(if default `(,default))))
                       finally
                         (when warn-p
                           (emit-form `(check-keyword-list-syntax ,f ',allowed-keywords)))))
               (nreverse bindings)))
            (t
             (append (destructure-lambda-list-1 (car lambda-list) `(car ,form))
                     (destructure-lambda-list-1 (cdr lambda-list) `(cdr ,form))))))))



(defun check-keyword-list-syntax (list allowed-keywords)
  (declare (eliminate-for-gsi))
  (loop for (keyword nil) on list by 'cddr
        unless (memq keyword allowed-keywords)
          do
            #+development
            (warn "The keyword ~s is not understood here. Allowed keywords are ~{~s~^, ~}."
                   keyword allowed-keywords)))

;; This function is currently called only at macroexpand-time, but it could conceivably be
;; needed at run-time.






;;;; Debugging functions


;;; The macro `with-simple-restart' binds a development-only restart option
;;; around the body.

(defmacro with-simple-restart ((restart-name format-string &rest format-args) &body forms)
  #+(and Lucid development)
  (let ((restart-name (case restart-name
                        (abort 'lcl:abort)
                        (t restart-name))))
    `(lcl:with-simple-restart (,restart-name ,format-string ,@format-args) ,@forms))
  #-(and Lucid development) (declare (ignore restart-name format-string format-args))
  #-(and Lucid development) `(progn ,@forms))




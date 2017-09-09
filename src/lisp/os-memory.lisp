;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module OS-MEMORY

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Hodgkinson

;; 2 February 1992



;;; This module contains the machinery with which G2 manages memory allocation
;;; from the operating system and the from the native Lisp environment.  It also
;;; contains miscellaneous memory-related utilities, such as one to grow stack
;;; size on platforms that need it.  It was thought that this machinery is
;;; complex enough to rate its own module.  As well, it is time os-specific
;;; modules got more revealing names.


;;;; Forward References

(declare-forward-references
  (ab-permanent-area                               variable PRIMITIVES)
  (bytes-allocated-for-image-tiles                 function) ;In IMAGES or GSI-PATCHES.
  (maximum-bytes-for-image-tiles                   function)
  (current-system-name                             variable) ;LAUNCH
  (get-command-line-keyword-argument-as-memory-size function)
  (read-memory-size-for-gensym-environment-variable function)
  )

(declare-forward-references (:suppress-module-checks-for ab telewindows ctest gensym-site)
  (gsi-option-is-set-p                     function gsi)
  (gsi-suppress-output                     variable gsi-common)
  )

;;;; Memory Limits

;;; From the user's point of view, G2 divides system memory into `memory
;;; regions'.  There are currently (jh, 2/2/92) two regions on every platform.
;;; This number is due to the exigencies of Chestnut, our current Lisp
;;; implementation.  Region 2 contains symbols and region 1 contains everything
;;; else.  (Note that interned symbols are not garbage-collectable, but
;;; everything else -- including uninterned symbols -- is.)

;;; G2 3.0 or later only garbage collects when the user explicitly chooses
;;; "Optimize Memory" from the Main Menu Miscellany.  When G2 runs out of memory,
;;; instead of garbage-collecting, it obtains more memory from the Lisp
;;; implementation.  Lisp accomplishes this by a call to the UNIX system function
;;; malloc() or its analogue on VMS.  G2 requests memory in 4-megabyte chunks at
;;; launch time.  After launch, G2 will obtain more memory in 64-kilobyte chunks.
;;; These numbers are subject to change as we determine our users' requirements
;;; more precisely.

;;; The call to malloc() supplants the garbage collection performed in earlier
;;; versions of G2, but is still as insidious, since malloc() can in the worst
;;; case take an unbounded amount of time getting a chunk of continguous memory of
;;; the desired size.  G2 will warn the user of a malloc() call by emitting an
;;; "Obtaining more memory" message, specifying the region which had to be grown
;;; and the new amount of memory occupied.  To side-step the call to malloc(), the
;;; user should adjust the initial memory limit of G2 the next time it is
;;; launched.

;;; Users specify memory limits as command-line arguments (the command-line
;;; switches -rgn1lmt and -rgn2lmt) or operating-system environmental variables
;;; ("G2RGN1LMT" and G2RGN2LMT").  Specifications are always measured in 8-bit
;;; bytes.  Note that the use of C-translation technology permits the same
;;; command-line and variable switches to work on either VMS or UNIX platforms.

;; Sizes for region 3 are independant of the OS (except Windows?)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter default-bytes-for-renderings 2500000)
(defparameter minimum-bytes-for-renderings  400000))



(defmacro region-info-index (info)
  `(svref ,info 0))
(defmacro region-info-name (info)
  `(svref ,info 1))
(defmacro region-info-command-line-keyword-argument (info)
  `(svref ,info 2))
(defmacro region-info-environment-variable (info)
  `(svref ,info 3))
(defmacro region-info-default (info)
  `(svref ,info 4))
(defmacro region-info-minimum (info)
  `(svref ,info 5))
(defmacro region-info-requested (info)
  `(svref ,info 6))
(defmacro region-info-desired (info)
  `(svref ,info 7))
(defmacro region-info-measured-usage (info)
  `(svref ,info 8))
(defmacro region-info-measured-size (info)
  `(svref ,info 9))

(defun make-region-info (index name command-line-keyword-argument environment-variable)
  (let ((array (make-array 10)))
     (setf (region-info-index array) index)
     (setf (region-info-name array) name)
     (setf (region-info-command-line-keyword-argument array) command-line-keyword-argument)
     (setf (region-info-environment-variable array) environment-variable)
     (setf (region-info-default array) 0)
     (setf (region-info-minimum array) 0)
     (setf (region-info-requested array) nil)
     (setf (region-info-desired array) 0)
     (setf (region-info-measured-usage array) 0)
     (setf (region-info-measured-size array) 0)
     array))

(defvar region-1-info (make-region-info 1 :dynamic    "rgn1lmt" "G2RGN1LMT"))
(defvar region-2-info (make-region-info 2 :static     "rgn2lmt" "G2RGN2LMT"))
(defvar region-3-info (make-region-info 3 'image-tile "rgn3lmt" "G2RGN3LMT"))
(defvar all-region-info (make-array 3))


;;; `number-of-memory-regions' -- really, nil is not a valid value.  I guess we
;;; set it to nil because we WANT to see an error if the later functions do not
;;; give it a numerical value.  -jv, 11/27/07
(defvar number-of-memory-regions nil)

(defmacro get-info-for-region (region-index)
  `(svref all-region-info (1-f ,region-index)))

(defun initialize-all-region-info (system)
  ;; Use different environment variable names for TW/GSI to prevent unintentional
  ;; large memory allocations when G2 spawns TW and GSI processes.
  (case system
    (telewindows
     (setf (region-info-environment-variable region-1-info) "TWRGN1LMT")
     (setf (region-info-environment-variable region-2-info) "TWRGN2LMT")
     (setf (region-info-environment-variable region-3-info) "TWRGN3LMT"))
    (gsi
     (setf (region-info-environment-variable region-1-info) "GSIRGN1LMT")
     (setf (region-info-environment-variable region-2-info) "GSIRGN2LMT")))
  #-(or chestnut chestnut-3)
  (progn
    system
    (setf (region-info-default region-1-info) 900000)
    (setf (region-info-minimum region-1-info) 600000)
    (setf (region-info-default region-2-info) 0)
    (setf (region-info-minimum region-2-info) 0))
  #+(or chestnut chestnut-3)
  (case system
    (ab
     (setf (region-info-default region-1-info) (if (eq 'alphaosf g2-machine-type) 20000000 10000000))
     (setf (region-info-minimum region-1-info) (if (eq 'alphaosf g2-machine-type)  9500000  4750000))
     (setf (region-info-default region-2-info) (if (eq 'alphaosf g2-machine-type)  5000000  3500000))
     (setf (region-info-minimum region-2-info) (if (eq 'alphaosf g2-machine-type)  5000000  3500000)))
    (telewindows
     (setf (region-info-default region-1-info) (if (eq 'alphaosf g2-machine-type)  2800000  1400000))
     (setf (region-info-minimum region-1-info) (if (eq 'alphaosf g2-machine-type)  1600000   800000))
     (setf (region-info-default region-2-info) (if (eq 'alphaosf g2-machine-type)   800000   800000))
     (setf (region-info-minimum region-2-info) (if (eq 'alphaosf g2-machine-type)   800000   800000)))
    (gsi
     (setf (region-info-default region-1-info) (if (eq 'alphaosf g2-machine-type)  3500000   800000))
     (setf (region-info-minimum region-1-info) (if (eq 'alphaosf g2-machine-type)  2900000   800000))
     (setf (region-info-default region-2-info) (if (eq 'alphaosf g2-machine-type)   300000   500000))
     (setf (region-info-minimum region-2-info) (if (eq 'alphaosf g2-machine-type)   300000   500000))))
  (case system
    ((ab telewindows)
     (setf (region-info-default region-3-info) #.default-bytes-for-renderings)
     (setf (region-info-minimum region-3-info) #.minimum-bytes-for-renderings)))
  (setf (get-info-for-region 1) region-1-info)
  (setf (get-info-for-region 2) region-2-info)
  (case system
    ((ab telewindows)
     (setf (get-info-for-region 3) region-3-info)
     (setq number-of-memory-regions 3))
    (t
     (setq number-of-memory-regions 2)))
  all-region-info)

(defconstant size-of-chunks-for-allocate-to-target 4000000)

(defmacro allocate-memory-to-target (area-keyword target)
  #+chestnut
  `(trun::allocate-memory-to-target ,area-keyword ,target)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      `(tx:allocate-memory-to-target ,area-keyword ,target)
      nil)

  #-(or chestnut chestnut-3)
  (declare (ignore area-keyword target))
  #-(or chestnut chestnut-3)
  (error "ALLOCATE-MEMORY-TO-TARGET is only implemented in Chestnut")
  )

(defun initialize-memory-for-region (system index)
  (let ((info (get-info-for-region index)))
    (when info
      (setf (region-info-requested info)
	    (or (get-command-line-keyword-argument-as-memory-size
		  (region-info-command-line-keyword-argument info))
		(read-memory-size-for-gensym-environment-variable
		  (region-info-environment-variable info))))
      (setf (region-info-desired info)
	    (or (region-info-requested info)
		(region-info-default info)))
      (let* ((desired-allocation (region-info-desired info))
	     (minimum-size (region-info-minimum info))
	     ;; This is a little less than (1- (ash 1 32)), to avoid problems
	     ;; (seg faults) with malloc.  -- update: for AlphaOSF (i.e., 64-bit
	     ;; platforms), allow close to a terabyte (2^40), a reasonable
	     ;; practical limit for now.  (MHD 8/17/06)
	     (maximum-size 1.0995e12)
	     (too-small-p (< desired-allocation minimum-size))
	     (too-large-p (> desired-allocation maximum-size)))
	(setf (region-info-desired info)
	      (cond ((or too-small-p too-large-p)
		     (reject-proposed-region-size system index desired-allocation
						  minimum-size maximum-size)
		     (if too-small-p
			 minimum-size
			 maximum-size))
		    (t
		     desired-allocation)))
	#+(or chestnut chestnut-3)
	(let ((region-name (region-info-name info))
	      out-of-memory-p)
	  (when (or (eq region-name ':static) (eq region-name ':dynamic))
	    ;; jh, 12/4/91.  Chestnut is calling malloc on region-1 in one big
	    ;; chunk.  Most operating systems are not able to provide this much
	    ;; contiguous memory, and we certainly don't need it to be contiguous.
	    ;; So, rather than take a fix from Chestnut at this late date, we
	    ;; allocate to target in 5 meg increments.  We don't use smarter loop
	    ;; clauses because they wrap (the fixnum ...) around things.
	    (loop with target gensym-float = (float size-of-chunks-for-allocate-to-target 0.0)
		  while (< target (float (region-info-desired info) 0.0))
		  do (or (allocate-memory-to-target region-name target)
			 (progn (setq out-of-memory-p t)
			        (return)))
		     (incf target size-of-chunks-for-allocate-to-target)
		  finally (or (allocate-memory-to-target region-name (region-info-desired info))
			      (setq out-of-memory-p t))))
	  (when out-of-memory-p
	    (exit-lisp-process)))
	nil))))

(defun-for-top-level set-up-lisp-memory-management (system)
  (initialize-all-region-info system)
  (loop for index from 1 to number-of-memory-regions
	do (initialize-memory-for-region system index)))

(defun report-memory-usage (system)
  (when (current-system-case
	  (gsi (and (not (gsi-option-is-set-p gsi-suppress-output))
		    (loop for index from 1 to 2
			  thereis (region-info-requested
				    (get-info-for-region index)))))
	  (t t))
    (loop for index from 1 to number-of-memory-regions
	  for info = (get-info-for-region index)
	  do (setf (region-info-measured-usage info)
		   (g2-region-memory-usage-as-float index))
	     (setf (region-info-measured-size info)
		   (g2-region-memory-size-as-float index)))
    (announce-region-sizes system)
    #+(or chestnut chestnut-3)
    (check-for-region-deficits system)))



;;;; Announcing Region Sizes


(defconstant minimum-memory-tab-setting  15)
(defconstant default-memory-tab-setting  30)
(defconstant desired-memory-tab-setting  45)
(defconstant measured-memory-tab-setting 60)  



(defun format-into-string-grouping-thousands (thing)
  (cond
    ((stringp thing)
     thing)
    ((not (numberp thing))
     "")
    ((= thing 0) "0")
    (t
     (let* ((number-of-digits
	      (loop for quotient gensym-float = (float thing 0.0) then (ffloor quotient 10)
		    until (= quotient 0)
		    count t))
	    (number-of-commas (floorf-positive (1-f number-of-digits) 3))
	    (length-of-string (+f number-of-digits number-of-commas))
	    (output-string (make-string length-of-string)))
       (loop with index = (1-f length-of-string)
	     with comma-counter = 1
	     for digits double-float = (float thing 0.0) then (ffloor digits 10)
	     while (>= digits 1.0)
	     do
	 (setf (schar output-string index) (digit-char (floor (mod digits 10))))
	 (decff index)
	     while (>=f index 0)
	     do
	 (when (>f (incff comma-counter) 3)
	   (setf (schar output-string index) #\,)
	   (decff index)
	   (setq comma-counter 1)))
       output-string))))

(defun right-justify-in-column (thing column-size)
  (let* ((formatted-string
	   (format-into-string-grouping-thousands
	     thing))
	 (length-of-formatted-string
	   (length formatted-string)))
    (if (> length-of-formatted-string column-size)
	formatted-string
	(concatenate 'string
		     (make-string (- column-size length-of-formatted-string)
				  :initial-element #\Space)
		     formatted-string))))

(defun announce-region-sizes (system-name)
  (format *terminal-io* "~&~a Memory Region Sizes (bytes):~%"
	  (case system-name
	    (ab "G2")
	    (telewindows "Telewindows")
	    (otherwise system-name)))
  (format *terminal-io* 
	  "~&  region#        minimum        default        desired    measured size  measured usage~%")
  (format *terminal-io* 
	    "  -------      ----------     ----------     ----------     ----------     ----------  ~%")
  (loop with desired-total = 0
	with unsupplied-desired-component-p = nil
	with lowest-total = 0
        with default-total = 0
        with measured-size-total = 0
        with measured-usage-total = 0
        for region-index from 1 to number-of-memory-regions
	for info = (get-info-for-region region-index)
	for lowest-size = (region-info-minimum info)
	for default-size = (region-info-default info)
	for desired-size = (region-info-desired info)
	for measured-size = (region-info-measured-size info)
	for measured-usage = (region-info-measured-usage info)
	do
	(format *terminal-io* 
		"     ~a    ~a~a~a~a~a~%"
		region-index ;one digit only
		(right-justify-in-column lowest-size 15)
		(right-justify-in-column default-size 15)
		(right-justify-in-column (or desired-size "unsupplied") 15)
		(right-justify-in-column (or measured-size "unknown") 15)
		(right-justify-in-column (or measured-usage "unknown") 15))
	(incf lowest-total lowest-size)
	(incf default-total default-size)
	(if desired-size
	    (incf desired-total desired-size)
	    (setq unsupplied-desired-component-p t))
	(if measured-usage
	    (incf measured-usage-total measured-usage))
	(if measured-size
	    (incf measured-size-total measured-size))
	finally
	  (format *terminal-io* 
		  "  -------      ----------     ----------     ----------     ----------     ----------  ~%")
	(format *terminal-io* 
		"  Totals: ~a~a~a~a~a~%"
		(right-justify-in-column lowest-total 15)
		(right-justify-in-column default-total 15)
		(right-justify-in-column 
		  (if unsupplied-desired-component-p
		      ""
		      desired-total)
		  15)
		(right-justify-in-column measured-size-total 15)
		(right-justify-in-column measured-usage-total 15))))


;; the following two functions print in the parent window of G2, not in the
;; logbook, for maximum debugging power.  If, despite our checks, the user crashes
;; G2 with an inappropriate memory limit on the command line, it's safest to leave
;; a record of it in the parent window.  The consing done by format only happens
;; once.  (jh, 7/31/90)

;; Output string reformatted for VMS compilation under chestnut.  (was, 1/28/91)

(defun reject-proposed-region-size 
    (system-name region-index proposed-region-size lowest-allowed-value highest-allowed-value)
  (let ((system-name-for-user
	  (case system-name
	    (ab "G2")
	    (telewindows "Telewindows")
	    (GSI "GSI")
	    (otherwise system-name))))
    
    (format *terminal-io*
	    "~&*************************************************************************~%")
    (format *terminal-io*
	    "*   Attempt to set memory region #~a to ~a bytes.~%"
	    region-index
	    (format-into-string-grouping-thousands proposed-region-size))

    (cond ((< proposed-region-size lowest-allowed-value)
	   (format *terminal-io* 
		   "*   This value is too low for proper ~a operation.~%" 	  
		   system-name-for-user)
	   (format *terminal-io*
		   "*   ~a will use the lowest recommended value (~a bytes).~%" 
		   system-name-for-user
		   (format-into-string-grouping-thousands lowest-allowed-value)))
	  (t
	   (format *terminal-io*
		   "*   This value is too high for proper ~a operation.~%" 	  
		   system-name-for-user)
	   (format *terminal-io*
		   "*   ~a will use the highest possible value (~a bytes).~%" 
		   system-name-for-user
		   (format-into-string-grouping-thousands highest-allowed-value))))
    
    (format *terminal-io* "*************************************************************************~%")
    ))




;;; The function `region-is-preallocated-p' accounts for the fact that the
;;; window system memory regions (just region 3 for now), are not preallocated,
;;; hence check-for-region-deficits should not warn about them.

(defun region-is-preallocated-p (region-index)
  (or (= region-index 1)
      (= region-index 2)))

(defun check-for-region-deficits (system-name)
  (loop for region-index from 1 to number-of-memory-regions
	for info = (get-info-for-region region-index)
	for default-region-size = (region-info-default info)
	for proposed-region-size = (region-info-desired info)
	for measured-region-size = (region-info-measured-size info)
	with at-least-one-deficit-found-p = nil
	with system-name-for-user =
	     (case system-name
	       (ab "G2")
	       (telewindows "Telewindows")
	       (GSI "GSI")
	       (otherwise system-name))

	when (and (region-is-preallocated-p region-index)
		  (if proposed-region-size
		      (< measured-region-size proposed-region-size)
		      (< measured-region-size default-region-size)))
	  do
	  (unless at-least-one-deficit-found-p
	    (format *terminal-io* 
		    "~&****************************************************************~%")
	    (format *terminal-io*
		    "*                            Warning:~%")
	    (format *terminal-io*
		    "* Operating system could not allocate all memory requested for~%")
	    (format *terminal-io*
		    "* ~a.  Performance may be degraded.  Please check the~%"
		    system-name-for-user)
	    (format *terminal-io*
		    "* ~a Installation Manual for possible remedies.~%"
		    system-name-for-user)
	    (format *terminal-io*
		    "*---------------------------------------------------------------~%")
	    (setq at-least-one-deficit-found-p t))
	  (format *terminal-io*
		  "~&*   Region #~a: requested ~a, measured ~a.~%"
		  region-index
		  (or proposed-region-size default-region-size)
		  measured-region-size)

	  finally
	  (when at-least-one-deficit-found-p
	    (format *terminal-io* 
	      "~&****************************************************************~%"))))








;;;; Abstractions for Chestnut Memory-related Functions

;; jh, 1/27/93. 

(defmacro area-memory-limit (area-keyword)
  #+chestnut
  `(trun::area-memory-limit ,area-keyword)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      (if (constantp area-keyword)
	  (let ((known-area-keyword (eval area-keyword)))
	    (case known-area-keyword
	      (:total `(+f (tx:area-memory-limit :static)
			   (tx:area-memory-limit :dynamic)))
	      (otherwise `(tx:area-memory-limit ,known-area-keyword))))
	  `(case ,area-keyword
	     (:total (+f (tx:area-memory-limit :static)
			 (tx:area-memory-limit :dynamic)))
	     (otherwise (tx:area-memory-limit ,area-keyword))))
      0)

  #-(or chestnut chestnut-3)
  (declare (ignore area-keyword))
  #-(or chestnut chestnut-3)
  (error "AREA-MEMORY-LIMIT is only implemented in Chestnut")
  )

(defmacro area-memory-limit-as-float (area-keyword)
  #+chestnut
  `(trun::area-memory-limit ,area-keyword)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      (if (constantp area-keyword)
	  (let ((known-area-keyword (eval area-keyword)))
	    (case known-area-keyword
	      (:total `(+f (tx:area-memory-limit-as-float :static)
			   (tx:area-memory-limit-as-float :dynamic)))
	      (otherwise `(tx:area-memory-limit-as-float ,known-area-keyword))))
	  `(case ,area-keyword
	     (:total (+f (tx:area-memory-limit-as-float :static)
			 (tx:area-memory-limit-as-float :dynamic)))
	     (otherwise (tx:area-memory-limit-as-float ,area-keyword))))
      0)

  #-(or chestnut chestnut-3)
  (declare (ignore area-keyword))
  #-(or chestnut chestnut-3)
  (error "AREA-MEMORY-LIMIT is only implemented in Chestnut")
  )

(defmacro total-memory-used ()
  #+chestnut
  `(trun::total-memory-used)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      `(+f (tx:area-memory-used :static)
	   (tx:area-memory-used :dynamic))
      0)

  #-(or chestnut chestnut-3)
  (error "TOTAL-MEMORY-USED is only implemented for Chestnut")
  )

(defmacro area-memory-used (area-keyword)
  #+chestnut
  `(trun::area-memory-used ,area-keyword)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      (if (constantp area-keyword)
	  (let ((known-area-keyword (eval area-keyword)))
	    (case known-area-keyword
	      (:total `(+f (tx:area-memory-used :static)
			   (tx:area-memory-used :dynamic)))
	      (otherwise `(tx:area-memory-used ,known-area-keyword))))
	  `(case ,area-keyword
	     (:total (+f (tx:area-memory-used :static)
			 (tx:area-memory-used :dynamic)))
	     (otherwise (tx:area-memory-used ,area-keyword))))
      0)

  #-(or chestnut chestnut-3)
  (declare (ignore area-keyword))
  #-(or chestnut chestnut-3)
  (error "AREA-MEMORY-USED is only implemented in Chestnut")
  )

(defmacro area-memory-used-as-float (area-keyword)
  #+chestnut
  `(trun::area-memory-used ,area-keyword)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      (if (constantp area-keyword)
	  (let ((known-area-keyword (eval area-keyword)))
	    (case known-area-keyword
	      (:total `(+e (tx:area-memory-used-as-float :static)
			   (tx:area-memory-used-as-float :dynamic)))
	      (otherwise `(tx:area-memory-used-as-float ,known-area-keyword))))
	  `(case ,area-keyword
	     (:total (+e (tx:area-memory-used-as-float :static)
			 (tx:area-memory-used-as-float :dynamic)))
	     (otherwise (tx:area-memory-used-as-float ,area-keyword))))
      0)

  #-(or chestnut chestnut-3)
  (declare (ignore area-keyword))
  #-(or chestnut chestnut-3)
  (error "AREA-MEMORY-USED is only implemented in Chestnut")
  )

(defmacro force-gc ()
  #+chestnut
  `(trun::force-gc)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      `(trun:force-gc)
      nil)

  #-(or chestnut chestnut-3)
  (error "FORCE-GC is only implemented in Chestnut")
  )

(defmacro gc-inhibit-off ()
  #+chestnut
  `(setq trun::*gc-inhibit* nil)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      `(setq trun:*gc-inhibit* nil)
      nil)

  #-(or chestnut chestnut-3)
  (error "GC-INHIBIT-OFF is only implemented in Chestnut")
  )

(defmacro gc-inhibit-on ()
  #+chestnut
  `(setq trun::*gc-inhibit* t)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      `(setq trun:*gc-inhibit* t)
      nil)

  #-(or chestnut chestnut-3)
  (error "GC-INHIBIT-ON is only implemented in Chestnut")
  )

;; jh, 1/27/93.  As of this date allow-gc is no longer used, since we no longer
;; allow garbage collection to occur in distribution ever.

(defmacro allow-gc (margin)
  #+chestnut
  `(trun::allow-gc ,margin)

  #+chestnut-3
  (if (eval-feature :chestnut-trans)
      `(when (<f (+f (-f (tx:area-memory-limit :static)
			 (tx:area-memory-used :static))
		     (-f (tx:area-memory-limit :dynamic)
			 (tx:area-memory-used :dynamic)))
		 ,margin)
	 (trun:force-gc))
      nil)

  #-(or chestnut chestnut-3)
  (declare (ignore margin))
  #-(or chestnut chestnut-3)
  (error "ALLOW-GC is only implemented in Chestnut")
  )





;; jh, 12/10/91.  Made set-up-lisp-memory-management-in-chestnut a top-level
;; function.  Since it forces a gc, we need to protect its local variables.


(declare-forward-reference gsi-error function)
(declare-forward-reference gsi-connection-error function)
(declare-forward-reference gsi-fatal-error function)

(defvar unrecoverable-error-p nil)
 
(defvar out-of-memory-handler nil)
 
#+chestnut-3
(defun-into-place (out-of-memory-handler out-of-memory-handler) ()
  (setq unrecoverable-error-p t)
  (error "No More Memory"))

#+(and chestnut-3 chestnut-trans)
(progn
  
(tx:def-foreign-function (set-area-overflow-function
			   (:name "set_area_overflow_function"))
    (arg :object))
  
(tx:toplevel-c-lines
  "#define set_area_overflow_function(fun) (Area_overflow_function=fun)")
  
(set-area-overflow-function out-of-memory-handler)
  
)
  

;;; The macro `adjust-memory-areas-if-appropriate' changes the default memory
;;; area sizes so that implementations that allocate memory at launch time can
;;; do so efficiently and without "obtaining more memory" messages.  Currently,
;;; the only implementation where we need to do this is Chestnut 3.1.

;;; When a Chestnut 3.1 image is launched, its main() function is called.
;;; Inside main(), the translator calls the function userinit() followed by the
;;; top-level Lisp function, launch-ab (for G2) or launch-tw in our case.  The
;;; userinit() function simulates load-time by calling an init function for each
;;; module that was translated, in the order of translation.  The init function
;;; for a given module contains all the top-level forms in that module, plus
;;; interns for all the symbols introduced there.  So placing a top-level defvar
;;; initialization in LOAD, which is always the first module loaded, will ensure
;;; that that top-level form will be executed before anything else in userinit()
;;; and before launch-g2-image is called.  In this way, we set the default
;;; static size before any symbols are allocated and the default dynamic size
;;; before anything else is allocated.  See LOAD for further details.

;; The function adjust-area-target-sizes is a Gensym addition to the Chestnut
;; runtime library, in rtl/c/rtlcore/heap.c.  We suppress translator complaints
;; by declaring it to be a foreign function, and we suppress type coercion in
;; calls to this foreign function by declaring its arguments and return value to
;; be of type :object.

(defmacro adjust-memory-areas-if-appropriate ()
  #+chestnut-3
  `(progn
     (tx:def-foreign-function
	 (adjust-area-target-sizes
	   (:name "adjust_area_target_sizes")
	   (:return-type :object))
	 (static-target-size-in-K :object)
         (dynamic-target-size-in-K :object)
	 (system-name :string))
     (#-chestnut-3-2-7 defvar
      #-chestnut-3-2-7 dummy-var ; to-adjust-chestnut-area-target-sizes-at-load-time
      #+chestnut-3-2-7 progn
       (adjust-area-target-sizes
	 ,(case current-system-being-loaded
	    (ab          3300)
	    (telewindows  800)
	    (gsi          500)
	    (otherwise   1560))
	 ,(case current-system-being-loaded
	    (ab          4750)
	    (telewindows 1400)
	    (gsi          700)
	    (otherwise   1650))
	 ,(case current-system-being-loaded
	    (ab          "AB")
	    (telewindows "TELEWINDOWS")
	    (gsi         "GSI")
	    (otherwise   "OTHER")))))

  #-chestnut-3
  nil
  )


;;;; Memory Usage Metering

;;; The function `g2-memory-usage' returns a fixnum which represents the amount
;;; of data space memory in bytes that G2 currently occupies.  As consing occurs
;;; this number will increase, but if we have done our jobs correctly, this will
;;; level off to some maximum while running.  On systems where we are placing
;;; objects into several areas of memory (i.e. the Lisp machines), this number
;;; will be the sum of the sizes of all areas into which we are consing objects.
;;; On systems where we do not yet have a means of obtaining this measure, this
;;; function will return 0.

;;; In Lucid, this function returns the number of bytes being used within the
;;; current newspace hemisphere of the dynamic area.  This number encompasses
;;; all dynamic memory in the Lisp environment.  Typically this may have a base
;;; value of around 750 thousand.

;;; The function lucid::gc-size returns three values: the number of bytes of
;;; storage already used in the current dynamic semi-space, the number of bytes
;;; still available in the current dynamic semi-space, and the number of bytes
;;; available in the combined dynamic semi-spaces.  Note that this function is
;;; likely to change somewhat in release 3 of Lucid, since they are adding the
;;; new generational garbage collection system.  -jra 8/31/88

;; Notice this and the following functions HAVEN'T changed so are now likely
;; wrong in Lucid development.  I believe the amount of memory in the ephemeral
;; spaces is not being taken into account. -dkuznick, 8/27/99

;; Modified g2-memory-usage in the Lucid case to use a more accurate count of 
;; outstanding memory than before.  The variable measured-memory-region1-size is
;; set by the def-memory-limit-setup form in the BASICS module.  (jh, 7/18/90)

;; Changed the variable measured-memory-region1-size to
;; measured-ab-memory-region1-size due to the change in BASICS which made these
;; memory variables specific to a system (eg telewindows, ab).  (jh, 8/29/90)

(defun g2-memory-usage ()
  (loop with total fixnum = 0
	for region from 1 to number-of-memory-regions
	do (incff total (g2-region-memory-usage region))
        finally (return total)))

(defun g2-memory-usage-as-float ()
  (loop with total #.(gensym-float-type) = 0.0
	for region from 1 to number-of-memory-regions
	do (setq total (+e total (g2-region-memory-usage-as-float region)))
        finally (return total)))




;;; The function `g2-memory-size' returns the amount of memory in bytes that has
;;; already been allocated (i.e. malloc'ed) into the G2 process.  Not all of
;;; this memory has neccessarily been used yet by G2.

(defun g2-memory-size ()
  (loop with total fixnum = 0
	for region from 1 to number-of-memory-regions
	do (incff total (g2-region-memory-size region))
        finally (return total)))

(defun g2-memory-size-as-float ()
  (loop with total #.(gensym-float-type) = 0.0
	for region from 1 to number-of-memory-regions
	do (setq total (+e total (g2-region-memory-size-as-float region)))
        finally (return total)))



;;; The function `g2-memory-available' returns a fixnum which represents the
;;; amount of memory in bytes that the has already been allocated
;;; (i.e. malloc'ed) into the G2 process, but not yet used by G2.  This value is
;;; defined as the difference between g2-memory-size and g2-memory-usage.

(defun g2-memory-available ()
  (-f (g2-memory-size) (g2-memory-usage)))

(defun g2-memory-available-as-float ()
  (-e (g2-memory-size-as-float) (g2-memory-usage-as-float)))



;;; Allegro makes you jump through hoops to get the memory info.  The values in
;;; this section were gotten from the docs for sys::gsgc-map.

;;; First some utilities.

#+(and allegro (not chestnut) (not chestnut-3))
(defun-simple num-oldspaces-allegro (mem-info-vector)
  (floorf-positive (-f (length mem-info-vector) 20) 10))

#+(and allegro (not chestnut) (not chestnut-3))
(defun oldspace-mem-info-for-slot (mem-info-vector oldspace-index slot)
  (aref mem-info-vector (+f 20 (*f oldspace-index 10) slot)))

#+(and allegro (not chestnut) (not chestnut-3))
(defun-simple total-oldspace-size-allegro (mem-info-vector)
  (loop for index fixnum from 0 below (num-oldspaces-allegro mem-info-vector)
	sum (oldspace-mem-info-for-slot
	      mem-info-vector index 1))) ;1 = slot for size of old area

#+(and allegro (not chestnut) (not chestnut-3))
(defun-simple total-newspace-size-allegro (mem-info-vector)
  (twicef (aref mem-info-vector 1)))		;1 = slot for GsNewSemiSize and 2 areas


#+(and allegro (not chestnut) (not chestnut-3))
(defun-simple total-oldspace-used-allegro (mem-info-vector)
  (-f (total-oldspace-size-allegro mem-info-vector)
      (loop for index fixnum from 0 below (num-oldspaces-allegro
					    mem-info-vector)
	    sum (oldspace-mem-info-for-slot
		  mem-info-vector index 8)))) ;8 = slot for number of free bytes

#+(and allegro (not chestnut) (not chestnut-3))
(defun-simple total-newspace-used-allegro (mem-info-vector)
  ;; halff because only one of the newspaces is active
  (-f (halff (total-newspace-size-allegro mem-info-vector))
      (aref mem-info-vector 8)))		;8 = slot for GsNewFree


;;; Here are the two main entry points

#+(and allegro (not chestnut) (not chestnut-3))
(defun-simple total-mem-size-allegro ()
  (let ((mem-info-vector (sys::gsgc-map 1)))
    (+f (total-oldspace-size-allegro mem-info-vector)
	(total-newspace-size-allegro mem-info-vector))))

#+(and allegro (not chestnut) (not chestnut-3))
(defun-simple total-mem-used-allegro ()
  (let ((mem-info-vector (sys::gsgc-map 1)))
    (+f (total-oldspace-used-allegro mem-info-vector)
	(total-newspace-used-allegro mem-info-vector))))




;;; The function `g2-region-memory-usage' returns a fixnum which represents the
;;; amount of dynamic memory in bytes that G2 currently occupies in a given
;;; region.  It is used in the G2 memory-measurement meters.

;;; As of 7/05/91 Chestnut has just two areas, static and dynamic, and no longer
;;; differentiates between node and array regions.  I changed these calls 
;;; to follow this. AC 07/06/91.

(defun g2-region-memory-usage (region-number)
  #+(and lucid (not chestnut) (not chestnut-3))
  (case region-number
    (1 (values (lucid::gc-size)))
    (2 0)
    (3 (bytes-allocated-for-image-tiles))		    ; Image renderings.
    (otherwise 0))

  #+(and allegro (not chestnut) (not chestnut-3))
  (case region-number
    (1 (total-mem-used-allegro))
    (2 0)
    (3 (bytes-allocated-for-image-tiles))
    (otherwise 0))

  #+(and lispworks (not chestnut) (not chestnut-3))
  (case region-number
    (1 (getf (sys:room-values) :total-allocated))
    (2 0)
    (3 (bytes-allocated-for-image-tiles))		    ; Image renderings.
    (otherwise 0))

  #+(and sbcl (not chestnut) (not chestnut-3))
  (case region-number
    (1 0) ; TODO
    (2 0)
    (3 (bytes-allocated-for-image-tiles))		    ; Image renderings.
    (otherwise 0))

  #+(or chestnut chestnut-3) ;Chestnut3.1
  (case region-number
    (1 (area-memory-used :dynamic))
    (2 (area-memory-used :static))
    (3 (bytes-allocated-for-image-tiles))		    ; Image renderings.
    (otherwise 0)))


(defun g2-region-memory-usage-as-float (region-number)
  #+(and lucid (not chestnut) (not chestnut-3))
  (case region-number
    (1 (float (lucid::gc-size) 0.0))
    (2 0.0)
    (3 (float (bytes-allocated-for-image-tiles) 0.0))		    ; Image renderings.
    (otherwise 0.0))

  #+(and allegro (not chestnut) (not chestnut-3))
  (case region-number
    (1 (float (total-mem-used-allegro) 0.0))
    (2 0.0)
    (3 (float (bytes-allocated-for-image-tiles) 0.0))
    (otherwise 0.0))

  #+(and lispworks (not chestnut) (not chestnut-3))
  (case region-number
    (1 (float (getf (sys:room-values) :total-allocated) 0.0d0))
    (2 0.0d0)
    (3 (float (bytes-allocated-for-image-tiles) 0.0d0))		    ; Image renderings.
    (otherwise 0.0d0))

  #+(and sbcl (not chestnut) (not chestnut-3))
  (case region-number
    (1 0.0d0) ; TODO
    (2 0.0d0)
    (3 (float (bytes-allocated-for-image-tiles) 0.0d0))		    ; Image renderings.
    (otherwise 0))

  #+(or chestnut chestnut-3) ;Chestnut3.1
  (case region-number
    (1 (area-memory-used-as-float :dynamic))
    (2 (area-memory-used-as-float :static))
    (3 (float (bytes-allocated-for-image-tiles) 0.0))		    ; Image renderings.
    (otherwise 0.0)))




;;; The function `g2-region-memory-size' returns a fixnum which represents the
;;; about of memory in bytes that G2 has already fetched (i.e. malloc'ed) from
;;; the operating system for a region.

(defun g2-region-memory-size (region-number)
  #+(and lucid (not chestnut) (not chestnut-3))
  (case region-number
    (1
     (multiple-value-bind (used available)
	 (lucid::gc-size)
       (+f used available)))
    (2 0)
    (3 (maximum-bytes-for-image-tiles))
    (otherwise 0))

  #+(and allegro (not chestnut) (not chestnut-3))
  (case region-number
    (1 (total-mem-size-allegro))
    (2 0)
    (3 (maximum-bytes-for-image-tiles))
    (otherwise 0))

  #+(and lispworks (not chestnut) (not chestnut-3))
  (case region-number
    (1 (getf (sys:room-values) :total-size))
    (2 0)
    (3 (maximum-bytes-for-image-tiles))		    ; Image renderings.
    (otherwise 0))

  #+(and sbcl (not chestnut) (not chestnut-3))
  (case region-number
    (1 (sb-ext:dynamic-space-size))
    (2 0)
    (3 (maximum-bytes-for-image-tiles))		    ; Image renderings.
    (otherwise 0))

  #+(or chestnut chestnut-3) ;Chestnut3.1
  (case region-number
    (1 (area-memory-limit :dynamic))
    (2 (area-memory-limit :static))
    (3 (maximum-bytes-for-image-tiles))
    (otherwise 0)))

(defun g2-region-memory-size-as-float (region-number)
  #+(and lucid (not chestnut) (not chestnut-3))
  (case region-number
    (1
     (multiple-value-bind (used available)
	 (lucid::gc-size)
       (float (+ used available) 0.0)))
    (2 0.0)
    (3 (float (maximum-bytes-for-image-tiles) 0.0))
    (otherwise 0.0))

  #+(and allegro (not chestnut) (not chestnut-3))
  (case region-number
    (1 (float (total-mem-size-allegro) 0.0))
    (2 0.0)
    (3 (float (maximum-bytes-for-image-tiles) 0.0))
    (otherwise 0.0))

  #+(and lispworks (not chestnut) (not chestnut-3))
  (case region-number
    (1 (float (getf (sys:room-values) :total-size) 0.0d0))
    (2 0.0d0)
    (3 (float (maximum-bytes-for-image-tiles) 0.0d0))		    ; Image renderings.
    (otherwise 0.0d0))

  #+(and sbcl (not chestnut) (not chestnut-3))
  (case region-number
    (1 (float (sb-ext:dynamic-space-size) 0.0d0))
    (2 0.0d0)
    (3 (float (maximum-bytes-for-image-tiles) 0.0d0))		    ; Image renderings.
    (otherwise 0.0d0))

  #+(or chestnut chestnut-3) ;Chestnut3.1
  (case region-number
    (1 (area-memory-limit-as-float :dynamic))
    (2 (area-memory-limit-as-float :static))
    (3 (float (maximum-bytes-for-image-tiles) 0.0))
    (otherwise 0.0)))



;;; The function `g2-region-memory-available' returns a fixnum which represents
;;; the amount of memory in bytes that G2 has not yet used of the memory that
;;; was already fetched (i.e. malloc'ed)from the operating system.  So, this
;;; amount of memory may still be used by G2 before any additional malloc'ing
;;; will need to occur.

(defun g2-region-memory-available (region-number)
  (-f (g2-region-memory-size region-number)
      (g2-region-memory-usage region-number)))

(defun g2-region-memory-available-as-float (region-number)
  (-e (g2-region-memory-size-as-float region-number)
      (g2-region-memory-usage-as-float region-number)))






;;;; Development-only stuff



;;; The function `g2-memory-usage-per-named-region' returns a fixnum which
;;; represents the amount of dynamic memory that G2 currently occupies in a given
;;; region.  It is currently used only in development.

;; Never called.

#+development
(defun g2-memory-usage-per-named-region (region)
  #-(or chestnut chestnut-3) ;Chestnut3.1
  (declare (ignore region))
  #-(or chestnut chestnut-3) ;Chestnut3.1
  0

  #+(or chestnut chestnut-3) ;Chestnut3.1
  (case region
    (:static
     (area-memory-used :static))
    (:dynamic
     (area-memory-used :dynamic))
    (:total 
     (area-memory-used :total))
    (t (format t "~&Memory-usage-per-region: ~a - Illegal option." region)))
  )


;;; The function `g2-memory-limit-per-named-region' returns a fixnum which
;;; represents the amount of dynamic memory that G2 may potentially allocate in a
;;; given region.  It is currently used only in development.

;; Never called.

#+development
(defun g2-memory-limit-per-named-region (region)
  #-(or chestnut chestnut-3) ;Chestnut3.1
  (declare (ignore region))
  #-(or chestnut chestnut-3) ;Chestnut3.1
  0

  #+(or chestnut chestnut-3) ;Chestnut3.1
  (case region
    (:static
     (area-memory-limit :static))
    (:dynamic
     (area-memory-limit :dynamic))
    (:total 
     (area-memory-limit :total))
    (t (format t "~&Memory-limit-per-region: ~a - Illegal option." region)))
    )




;;;; Lisp Object Memory Usage Estimates

;;; The following functions return the numbers of 8-bit bytes in various Lisp
;;; data structures.  These have been tuned per platform.  Any which have not
;;; been verified by direct experimentation should at least have comments next
;;; to them explaining this.

;; jh, 7/9/92.  Updated bytes-per-cons, bytes-per-double-float,
;; bytes-per-simple-vector bytes-per-unsigned-byte-8-simple-array,
;; bytes-per-unsigned-byte-16-simple-array, bytes-per-simple-string, and
;; bytes-per-adjustable-string to reflect what we now know about the sizes of
;; Chestnut objects.  We got a rude surprise a few weeks before the final 3.0
;; release, when we learned that every object in Chestnut Lisp is 4 bytes larger
;; than we had been promised.  These 4 bytes are a "relocation word", necessary
;; for the relocating mark-and-sweep garbage collector that we use.

;; The numbers for Allegro were given by tech support for ACL 5.0.1.  Also see
;; doc/cl/implementation.html 2.0 Data types -dkuznick, 8/31/99

;;; The macro `bytes-per-cons' returns the number of bytes needed to allocate
;;; one cons.

(defparameter bytes-per-rtl-ptr (if *is-g2-enterprise?* 8 4))
(defconstant bytes-per-rtl-double 8)
(defconstant bytes-per-rtl-int64 8) ; 64bit

(defmacro bytes-per-cons ()
  (cond ((eval-feature :chestnut-3)
	 `(* 2 bytes-per-rtl-ptr))
	((eval-feature '(or :lucid :allegro))
	 `(* 2 bytes-per-rtl-ptr))
	(t
	 `(* 2 bytes-per-rtl-ptr)))) ;12 was funny

;; The numbers above are certainly true of the Lisp machines, Lucid, and
;; Chestnut 2.0.  I believe they are correct for Ibuki.  -jra 11/25/90




;;; The macro `bytes-per-double-float' returns the number of bytes needed to
;;; create a boxed double-float.

(defmacro bytes-per-double-float ()
  ;; None of these have been verified.  -jra 11/25/90
  (cond ((eval-feature :chestnut-3) ;Chestnut3.1 - soon to be 8
	 bytes-per-rtl-double)
	((eval-feature '(or :lucid :allegro))
	 `(* 2 bytes-per-rtl-double))
	(t
	 bytes-per-rtl-double)))




;;; The function `bytes-per-simple-vector' takes a fixnum length of a
;;; simple-vector and returns the number of bytes that a vector of that size
;;; would require.  The functions `bytes-per-unsigned-byte-8-simple-array',
;;; `bytes-per- unsigned-byte-16-simple-array', `bytes-per-double-float-
;;; simple-array', and `bytes-per-simple-string' perform the same operation for
;;; 8-bit-byte, 16-bit-byte, and double-float immediate simple arrays.

(defmacro bytes-per-simple-vector-1 (length)
  (cond ((eval-feature :chestnut-3) ;Chestnut3.1
	 `(+f (bytes-per-cons) (*f bytes-per-rtl-ptr ,length)))
        ((eval-feature :lucid)
	 ;; Lucid allocates on 8 byte boundaries only, and needs 1 word of
	 ;; header for each simple-vector.  Need to verify by experiment.  -jra
	 ;; 11/25/90
	 `(*f (bytes-per-cons) (ceilingf-positive (+f ,length 1) 2)))
        ((eval-feature :allegro)
	 `(+f bytes-per-rtl-ptr (*f bytes-per-rtl-ptr ,length)))
	(t
	 ;; For unknown platforms, assume the best of them.
	 `(*f bytes-per-rtl-ptr (+f ,length 1)))))

(defun bytes-per-simple-vector (length)
  (bytes-per-simple-vector-1 length))

(defmacro bytes-per-unsigned-byte-8-simple-array-1 (vector-length)
  ;; Has been verified for Lucid and Lispm.  -jra 11/25/90
  (cond ((eval-feature :chestnut-3) ;Chestnut3.1
	 `(+f (bytes-per-cons)
	      (*f (ceilingf-positive ,vector-length bytes-per-rtl-ptr) bytes-per-rtl-ptr)))
        ((eval-feature :lucid)
	 `(*f (bytes-per-cons)
	      (ceilingf-positive (+f ,vector-length bytes-per-rtl-ptr) (bytes-per-cons))))
	((eval-feature :allegro)
	 `(+f bytes-per-rtl-ptr ,vector-length))
	(t
	 `(+f (bytes-per-cons)
	      (*f (ceilingf-positive ,vector-length bytes-per-rtl-ptr) bytes-per-rtl-ptr)))))




(defun bytes-per-unsigned-byte-8-simple-array (vector-length)
  (bytes-per-unsigned-byte-8-simple-array-1 vector-length))

(defmacro bytes-per-unsigned-byte-16-simple-array-1 (vector-length)
  ;; None of these have been verified.  -jra 11/25/90
  (cond ((eval-feature :chestnut-3) ;Chestnut3.1
	 `(+f (bytes-per-cons) (*f (ceilingf-positive ,vector-length 2) bytes-per-rtl-ptr)))
	((eval-feature :lucid)
	 `(*f (bytes-per-cons) (ceilingf-positive (+f ,vector-length 2) bytes-per-rtl-ptr)))
	((eval-feature :allegro)
	 `(+f bytes-per-rtl-ptr (*f 2 ,vector-length)))
	(t
	 `(+f (bytes-per-cons) (*f (ceilingf-positive ,vector-length 2) 2)))))

(defun bytes-per-unsigned-byte-16-simple-array (vector-length)
  (bytes-per-unsigned-byte-16-simple-array-1 vector-length))

(defmacro bytes-per-double-float-simple-array-1 (vector-length)
  ;; None of these have been verified.  -jra 11/25/90
  (cond ((eval-feature :lucid)
	 `(+f (bytes-per-cons)
	      (*f bytes-per-rtl-double ,vector-length)))
	((eval-feature :allegro)
	 `(+f (bytes-per-cons) (*f 16 ,vector-length))) ;4 header + 4 fill for alignment
	(t
	 `(+f (bytes-per-cons)
	      (*f bytes-per-rtl-double ,vector-length)))))

(defun bytes-per-double-float-simple-array (vector-length)
  (bytes-per-double-float-simple-array-1 vector-length))

(defmacro bytes-per-long-simple-array-1 (vector-length)
  `(+f (bytes-per-cons)
       (*f bytes-per-rtl-int64 ,vector-length)))

(defun-simple bytes-per-long-simple-array (vector-length)
  (bytes-per-long-simple-array-1 vector-length))

(defmacro bytes-per-simple-string-1 (vector-length)
  (cond ((eval-feature :chestnut-3) ;Chestnut3.1
	 `(+f (bytes-per-cons)
	      (*f (floorf-positive ,vector-length bytes-per-rtl-ptr) bytes-per-rtl-ptr)))
	((eval-feature :lucid)
	 `(*f (bytes-per-cons)
	      (ceilingf-positive (+f ,vector-length bytes-per-rtl-ptr) (bytes-per-cons))))
	((eval-feature :allegro)
	 `(+f 5 ,vector-length))	;4 byte header plus 1 for the 0
	(t
	 `(+f (bytes-per-cons)
	      (*f (ceilingf-positive ,vector-length bytes-per-rtl-ptr) bytes-per-rtl-ptr)))))

(defun bytes-per-simple-string (vector-length)
  (bytes-per-simple-string-1 vector-length))




;;; The macro `bytes-per-adjustable-string' takes a length and returns the
;;; number of bytes that would be used by an adjustable string of that length.

(defmacro bytes-per-adjustable-string (vector-length)
  (cond ((eval-feature :chestnut)
	 `(+f 36 (*f (floorf-positive ,vector-length bytes-per-rtl-ptr) bytes-per-rtl-ptr)))
	((eval-feature :chestnut-3) ;Chestnut3.1
	 `(+f 36 (*f (floorf-positive ,vector-length bytes-per-rtl-ptr) bytes-per-rtl-ptr)))
	((eval-feature :allegro)
	 `(+f 28 ,vector-length))
	(t
	 `(bytes-per-simple-string ,vector-length))))




;;; The function `bytes-per-typed-simple-array' takes an element-type and a
;;; length, and returns the number of bytes needed to allocate an array of that
;;; type and length.

(defun-simple bytes-per-typed-simple-array (element-type length)
  (cond ((eq element-type t)
	 (bytes-per-simple-vector length))
	;; G2 uses all double-floats now.  -jra 11/25/90
	((or (eq element-type 'single-float)
	     (eq element-type 'double-float))
	 (bytes-per-double-float-simple-array length))
	((or (eq element-type (gensym-string-char-type))
	     (eq element-type 'character))
	 (bytes-per-simple-string length))
	((equal element-type '(unsigned-byte 8))
	 (bytes-per-unsigned-byte-8-simple-array length))
	((equal element-type '(unsigned-byte 16))
	 (bytes-per-unsigned-byte-16-simple-array length))
	(t
	 (bytes-per-simple-vector length))))




;;; The function `bytes-in-lisp-objects' takes a Lisp object and
;;; returns the number of bytes in the given object and any objects stored
;;; within it.  At the moment this function can only handle conses, strings,
;;; and simple vectors, but it should be extended later.

#+development
(defun bytes-in-lisp-objects (object)
  (typecase object
    (cons
     (loop with total = 0
	   for cdr-object = object then (cdr cdr-object)
	   while (consp cdr-object)
	   for car-object = (car cdr-object)
	   do
       (setq total (+f total
		       (bytes-per-cons)
		       (if (symbolp car-object)
			   0
			   (bytes-in-lisp-objects car-object))))
	   finally
	     (incff total (bytes-in-lisp-objects cdr-object))
	     (return total)))
    (simple-vector
     (loop with length = (length object)
	   with total = (bytes-per-simple-vector length)
	   for index from 0 below length
	   do
       (incff total (bytes-in-lisp-objects (svref object index)))
	   finally
	     (return total)))
    (string
     (bytes-per-simple-string (array-total-size object)))
    (t 0)))

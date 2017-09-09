;; -*- mode: lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-

(in-package "AB")

;;;; Module SEQUENCES2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin


;;;; Forward References



(declare-forward-reference compile-symbol-list function)
(declare-forward-reference loading-kb-p variable)
(declare-forward-reference post-prominent-notification function)    	; BOOKS

(declare-forward-reference g2-equiv function)				; FILTERS
(declare-forward-reference get-telewindows-license-level function)
(declare-forward-reference get-g2-license-level function)
(declare-forward-reference print-frame function)
(declare-forward-reference validate-as-possible-user-mode function)

(declare-forward-reference parent function)
(declare-forward-reference identify-all-savable-kb-workspaces function)
(declare-forward-reference close-telewindows-connection function) ; TELESTUBS


(declare-forward-reference ;KB-MERGE
  name-text-string-for-kb-being-read variable)

(declare-forward-reference empty-kb-p function) ;KB-SAVE2

(declare-forward-reference
  system-version-from-kb-being-read variable)

(declare-forward-reference ;COMP-UTILS
  current-computation-component-particulars
  variable)

(declare-forward-reference timing-parameters variable) ; WORKSTATION
(declare-forward-reference g2-window-user-is-valid-function function)
(declare-forward-reference g2-window-mode-is-valid-function function)
(declare-forward-reference workstation-for-g2-window?-function function)

(declare-forward-reference schedule-tw-modernization-tasks-if-necessary
			   function)

(declare-forward-reference authorizing-ok-pathname variable)
(declare-forward-reference
  twrite-standard-secure-g2-notification-header function)

;; in VIEW-G2
(declare-forward-reference ui-client-session-license-level?-function function)
(declare-forward-reference ui-client-session-nonce-function function)
(declare-forward-reference set-ui-client-session-license-level function)
(declare-forward-reference inform-ui-client-interfaces-of-top-level-workspace-assignment-change function)
(declare-forward-reference ui-client-session-valid-p function)
(declare-forward-reference make-ui-client-session-internal function)
(declare-forward-reference already-is-a-named-ui-session-from-this-client function)
(declare-forward-reference g2-release-ui-client-session function)

;; in CHECK-KBS
(declare-forward-reference ok-file-generation-for-version-5.1-or-greater-p variable)

;; in RUN
(declare-forward-reference encode-and-check-password-change-information function)

(declare-forward-reference set-ui-client-session-status function)
(declare-forward-reference ui-client-session-status-function function)

(declare-forward-reference get-module-block-is-in function)
(declare-forward-reference locked-to-kb? variable)

;; in COMMANDS1
(declare-forward-reference completely-shut-down-g2 function)

;; in KFEP2
(declare-forward-reference initialize-for-asian-languages function)



;;; These belong in sequences1, however I don't want to touch that file
;;; during the release of g2 5.1r1. Move them there and promulgate them
;;; when the code loosens up for v6 development.  ddm 10/9/98

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant unauthorized-lic-level  -2)
(defconstant floating-lic-level      -1)
(defconstant embedded-lic-level       0)
(defconstant runtime-lic-level        1)
(defconstant restricted-use-lic-level 2)
(defconstant development-lic-level    3)
) ; eval-when




;;; This fragment of def-optional-module could not be performed until
;;; add-grammar-rule is defined. So it is done here based on data in
;;; optional-modules-map.

(setq optional-modules-map (nreverse optional-modules-map)) 

(loop for (module-name nil nil invisible-module-p) in optional-modules-map
      doing
  (when (not invisible-module-p)
    (add-grammar-rules `((product ',module-name)))))

(defun-strange-names-for-optional-modules)  ;; Touch Me from time to time, please!







;;;; Constructing the codes for TW2s


;;; These 'pulse-rate' routines are the equivalent of G2's finger
;;; adapted for tw2 -- details are in numbers.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar pulse-rate-multiplier 1))

(defmacro choose-tw2-numeric-seed-macro ()
  `(case pulse-rate-multiplier
     (1 87975)))

(defun choose-pulse-rate-multiplier ()
  (case pulse-rate-multiplier
    (1 #.(stringw "q4b14f8gs"))
    (t (error 
	 "unknown version: ~d" pulse-rate-multiplier))))

(def-system-variable pulse-rate-options sequences2
  (:funcall choose-pulse-rate-multiplier))


;;; These are all the obfuscating macros

(defmacro compute-tw2-codes-for-current-version
    (machine-id start-day? start-month? start-year?
     expiration-day? expiration-month? expiration-year? license-level)
  `(compact-rpc-scratch-space-if-necessary
     ,machine-id ,start-day? ,start-month? ,start-year?
     ,expiration-day? ,expiration-month? ,expiration-year? ,license-level))

(defmacro compute-tw2-codes-1
          (machine-id start-date? expiration-date? license-level)
  `(compact-rpc-scratch-space
     ,machine-id ,start-date? ,expiration-date? ,license-level))

(defmacro create-tw2-authorization-codes
    (machine-id start-date end-date authorization-level)
  `(scan-rpc-scratch-space
     ,machine-id ,start-date ,end-date ,authorization-level))


(defmacro initialize-random-state-array-for-tw2
          (machine-id start-date? expiration-date? authorization-level)
  `(map-scratch-space-blocks
     ,machine-id ,start-date? ,expiration-date? ,authorization-level))


(defmacro vet-temporary-license-intervals
         (start-day? start-month? start-year? 
          expiration-day? expiration-month? expiration-year?)
  `(convert-valid-date-expressions-to-universal-dates
     ,start-day? ,start-month? ,start-year? 
     ,expiration-day? ,expiration-month? ,expiration-year?))


(defmacro compute-tw2-code-checksum (machine-id code1 code2 code3 code4
	                             start-date? expiration-date?
           	                     license-level)
  `(revert-rpc-bounds-now
     ,machine-id ,code1 ,code2 ,code3 ,code4
     ,start-date? ,expiration-date? ,license-level))


(defmacro validate-self-authorizing-tw2
    (machine-id ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
     start-date-sequence? end-date-sequence? desired-authorization-level)
  `(defragment-rpc-mapping-table
     ,machine-id ,ok-code1 ,ok-code2 ,ok-code3 ,ok-code4 ,ok-code5
     ,start-date-sequence? ,end-date-sequence? ,desired-authorization-level))





;;; These are the real routines. 

;;; This is compute-tw2-codes-for-current-version
(defun compact-rpc-scratch-space-if-necessary
    (machine-id start-day? start-month? start-year?
     expiration-day? expiration-month? expiration-year? license-level)
  (cond 
    ((or start-day? start-month? start-year? 
	 expiration-day? expiration-month? expiration-year?)
     (multiple-value-bind (start-date end-date)
	 (vet-temporary-license-intervals
	   start-day? start-month? start-year? 
	   expiration-day? expiration-month? expiration-year?)
       (compute-tw2-codes-1 
	 machine-id start-date end-date license-level)))
    (t
     (compute-tw2-codes-1
       machine-id nil nil license-level))))


;;; This is compute-tw2-codes-1
(defun compact-rpc-scratch-space
       (machine-id start-date? expiration-date? license-level)
  (multiple-value-bind
      (code1 code2 code3 code4)
      (create-tw2-authorization-codes
	machine-id start-date? expiration-date? license-level)
    (values
      code1 code2 code3 code4
      (compute-tw2-code-checksum
	machine-id code1 code2 code3 code4
	start-date? expiration-date? license-level))))


;;; This is create-tw2-authorization-codes
(defun scan-rpc-scratch-space
       (machine-id start-date end-date authorization-level)
  (initialize-random-state-array-for-tw2
    machine-id start-date end-date authorization-level)
  (setq *random-state-array-current-pointer* 54)
  (setq *random-state-array-24-pointer* 30)
  (loop for i from 1 to 500
	do (generate-large-random))
  (values (aref *random-state-array* 0) (aref *random-state-array* 1)
	  (aref *random-state-array* 2) (aref *random-state-array* 3)))


;;; This is initialize-random-state-array-for-tw2
(defun map-scratch-space-blocks
    (machine-id start-date? expiration-date? authorization-level)
  
  (macrolet ((launder-tw2-license-level (level)
	       ;; The documentation of what the permitted license levels are for
	       ;; a telewindowss (which we are cloning for tw2) is out of
	       ;; sync. with the reality of what the code accepts.This acts as
	       ;; an impedence matcher to bring them into sync. It returns a
	       ;; fresh list that is reclaimed in the section that calls this.
	       `(gensym-list
		  (case ,level
		    (deployment 'restricted-use-option)
		    (t (error "Unknown license level for a tw2: ~a" ,level))))))
    
    (unless *random-state-array*
      (setq *random-state-array*
	    (with-permanent-array-creation
	      (make-array 55 :element-type 'fixnum))))
    
    (loop for state-array-index from 0 to 54 do 
         (setf (aref *random-state-array* state-array-index)
	    (choose-tw2-numeric-seed-macro)))

    (loop with state-array-index = 0
	  for i from 0 below (text-string-length machine-id)
	  as weight? = (digit-char-pw (charw machine-id i) 36)
	  do
      (when weight?
         (setf (aref *random-state-array* state-array-index) weight?)
	(incff state-array-index))
	  until (=f state-array-index 55))
    
    (setf (aref *random-state-array* 54) 1)
    ;; why do we need at least one odd number?

    (when start-date?
      (setf (aref *random-state-array* 3) 
	    (logxorf (aref *random-state-array* 3) start-date?)
	    (aref *random-state-array* 4) 
	    (logxorf (aref *random-state-array* 4) start-date?)
	    (aref *random-state-array* 5) 
	    (logxorf (aref *random-state-array* 5) start-date?)
	    (aref *random-state-array* 6) 
	    (logxorf (aref *random-state-array* 6) start-date?)))

    (when expiration-date?
      (setf (aref *random-state-array* 7)
	    (logxorf (aref *random-state-array* 7) expiration-date?)
	    (aref *random-state-array* 8)
	    (logxorf (aref *random-state-array* 8) expiration-date?)
	    (aref *random-state-array* 9)
	    (logxorf (aref *random-state-array* 9) expiration-date?)
	    (aref *random-state-array* 10)
	    (logxorf (aref *random-state-array* 10) expiration-date?)))


    (when authorization-level
      (unless (eq authorization-level 'development)
	;; development is defined as the absense of a retriction to
	;; restricted, runtime, or embedded.
	(let* ((list (launder-tw2-license-level authorization-level))
	       (products-bitmask (compute-product-code list)))
	  
	  (when (or (tw-runtime-option-authorized-code-p products-bitmask)
		    (tw-restricted-use-option-authorized-code-p products-bitmask)
		    (tw-embedded-option-authorized-code-p products-bitmask))
	    (setf (aref *random-state-array* 11)
		  (logxorf (aref *random-state-array* 11)
			   products-bitmask)))
	  
	  (reclaim-gensym-list list))))))



;;; This is vet-temporary-license-intervals. It's conceivably interesting
;;; in its own right (if you've got two spread dates), hence the relatively
;;; clear name.

(defun-allowing-unwind convert-valid-date-expressions-to-universal-dates
    (start-day? start-month? start-year? 
     expiration-day? expiration-month? expiration-year?)
  (protected-let
      ((start-date? nil)
       (expiration-date? nil)
       (start-date-list?
	 (gensym-list start-day? start-month? start-year?)
	 (reclaim-gensym-list start-date-list?))
       (end-date-list?
	 (gensym-list expiration-day? expiration-month? expiration-year?)
	 (reclaim-gensym-list end-date-list?)))
    
    (when (valid-universal-date-elements-p
	    start-day? start-month? start-year?)
      (setq start-date? 
	    (convert-input-to-universal-date start-date-list?)))
    
    (when (valid-universal-date-elements-p
	    expiration-day? expiration-month? expiration-year?)
      (setq expiration-date? 
	    (convert-input-to-universal-date end-date-list?)))
    
    (if (or (null start-date?)
	    (null expiration-date?))
	(values nil nil 'bad-date-format)
	(values start-date? expiration-date?))))




;;; This is compute-tw2-code-checksum
(defun revert-rpc-bounds-now
       (machine-id code1 code2 code3 code4
        start-date? expiration-date? license-level)
  (let* ((keystring
	   (tformat-text-string "~a~a" machine-id pulse-rate-options))
	 (modularized-key
	   (prog1
	       (modularized-normalize-key-online
		 keystring new-modulus)
	     (reclaim-text-string keystring))))

    (when (<f code1 100) (setq code1 (+f 173 (*f 477 code1)))) ; random
    (when (<f code2 100) (setq code2 (+f 931 (*f  73 code2))))
    (when (<f code3 100) (setq code3 (+f 575 (*f 637 code3))))
    (when (<f code4 100) (setq code4 (+f 347 (+f 782 code4))))

    (mod
      (let* ((t1 (or start-date? 0))
	     (t2 (or expiration-date? 0))
	     (license-multiplier
	       (cond ((eq license-level 'runtime) code1)
		     ((eq license-level 'restricted) code2)
		     ((eq license-level 'embedded) code3)
		     (t 0))) ; development
	     (t3 (inner-multiply license-multiplier code1))
	     (t4 (inner-multiply license-multiplier code4)))
	
	(logxorf
	  (inner-multiply modularized-key code1)
	  (inner-multiply code2 code3)
	  (inner-multiply code4 code4)
	  (inner-multiply t1 t2)
	  (inner-multiply t3 t4)))

      new-modulus)))



;;; This is an auto-test routine. I also use its body as a place to take
;;; note of the values that are generated for similar licenses. It can
;;; be improved to be a real regression test with only a little work. 

(defun check-code-space-2 ()
  (macrolet
      ((check-set-of-tw2-codes (list-of-pairs)
	 `(loop with code1  with code2  with code3  with code4  with code5
		for ( (id s-day s-month s-year e-day e-month e-year level)
		      (c1 c2 c3 c4 c5) )
		    in ,list-of-pairs
		do
	    (multiple-value-setq (code1 code2 code3 code4 code5)
	      (compute-tw2-codes-for-current-version
		id s-day s-month s-year e-day e-month e-year level))
	    
	    (unless (and (=f code1 c1) (=f code2 c2) (=f code3 c3) (=f code4 c4))
	      (error "failed the inner check"))
	    (unless (=f code5 c5)
	      (error "falled the outer check"))

		finally (return 'all-is-well))))
    
  (check-set-of-tw2-codes
    '(((#w"89723529" nil nil nil nil nil nil deployment)
       (2133228 6794277 6819064 6805666 764797))
      ((#w"89723529" nil nil nil nil nil nil development)
       (2832108 6794277 6819064 6815394 365801))

      ((#w"00609758605d" nil nil nil nil nil nil deployment)
       (7631149 1167989 1194458 1180380 554244))
      ((#w"00609758605d" nil nil nil nil nil nil development)
       (6932269 1167989 1194458 1170652 657026))
      ((#w"00609758605d" 1 oct 1998 24'nov 1998 development)
       (5947951 176383 5729073 5134757 653127))

      ((#w"1111" nil nil nil nil nil nil development)
       (6748523 6748523 6780083 3433045 128953))
      ((#w"1110" nil nil nil nil nil nil development)
       (6748523 6748523 6779930 3433044 837304))
      ((#w"0111" nil nil nil nil nil nil development)
       (6748522 6748523 6780083 3431329 608298))
      ((#w"0000" nil nil nil nil nil nil development)
       (6748369 6748369 6779929 3431328 113545))
      ((#w"0001" nil nil nil nil nil nil development)
       (6748369 6748369 6780082 3431329 312781))
      
      ((#w"000086074AF7" nil nil nil nil nil nil development)
       (6921994 1165169 1185082 1168833 200502))
      ((#w"000086078f43" nil nil nil nil nil nil development)
       (6916610 1165444 1185098 1168262 805320))
      ))))




;;; `Validate-self-authorizing-tw2', aka defragment-rpc-mapping-table, is
;;; called when a tw2 client is trying to get its OK entry validated.
;;; Check-self-authorizing-tw2-1 is the proximal caller. The process
;;; started with a call to the rpc g2-validate-named-tw2.

(defun defragment-rpc-mapping-table
       (machine-id ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
        start-date-sequence? end-date-sequence? desired-authorization-level)
  (let ((start-date? nil)
	(end-date? nil)
	(error-symbol? nil)
	(bad-date-format? nil))
    
    (when start-date-sequence?
      (unless end-date-sequence?
	(setq error-symbol? 'no-end-date-supplied-with-start-date))
      
      (unless error-symbol?
	(unless (and (evaluation-sequence-p start-date-sequence?)
		     (evaluation-sequence-p end-date-sequence?))
	  (setq error-symbol? ; this would be a bug in the caller
		'wrong-data-structure-for-temporary-interval-information)))

      (unless error-symbol?
	(let ((start-day   (evaluation-sequence-aref start-date-sequence? 0))
	      (start-month (evaluation-sequence-aref start-date-sequence? 1))
	      (start-year  (evaluation-sequence-aref start-date-sequence? 2))
	      (expiration-day   (evaluation-sequence-aref end-date-sequence? 0))
	      (expiration-month (evaluation-sequence-aref end-date-sequence? 1))
	      (expiration-year  (evaluation-sequence-aref end-date-sequence? 2)))
	  
	  (unless (and start-day start-month start-year 
		       expiration-day expiration-month expiration-year)
	    (setq error-symbol? 'missing-date-information))

	  (unless error-symbol?
	    (multiple-value-setq (start-date? end-date? bad-date-format?)
	      (vet-temporary-license-intervals
		start-day start-month start-year 
		expiration-day expiration-month expiration-year))
	    (when bad-date-format?
	      ;; Should never happen because the ok parser should catch it,
	      ;; but paranoia makes for stronger code.
	      (setq error-symbol? bad-date-format?)))

	  ;; Check for our being inside the interval
	  (unless error-symbol?
	    (let ((today (get-universal-date)))
	      (cond
		((<f end-date? start-date?)
		 (setq error-symbol? 'temp-codes-end-before-they-start))
		((<f end-date? today)
		 (setq error-symbol? 'temp-codes-interval-has-ended))
		((<f today start-date?)
		 (setq error-symbol? 'temp-codes-interval-not-started))))))))

    (if error-symbol?
	(values nil error-symbol?)
	
	(let* ((checksum
		 (compute-tw2-code-checksum
		   machine-id ok-code1 ok-code2 ok-code3 ok-code4
		   start-date? end-date? desired-authorization-level)))
	  
	  (if (=f checksum ok-code5)
	      t
	      (values nil 'bad-codes))))))








;;;; Abstracting the Messages used while Parsing Text-based OK files


;;; `define-ok-message' ...
;;; is designed on the pattern of def-scrambled-constant-string in that
;;; it defines a function whose execution produces the desired string.
;;; It's the callers' responsibility to get the string out to where it
;;; can be announced to the user.
;;;
;;; This form produces a function, e.g.
;;;
;;;   (define-ok-message authorization-not-valid-until
;;;      "The OK for this machine will not be valid until <date>" start-date)
;;;
;;; becomes:
;;;
;;;   (defun authorization-not-valid-until-ok-messagee (start-date)
;;;     (twith-output-to-text-string
;;;       (twrite-string "The OK for this machine will not be valid until ")
;;;       (print-universal-date-as-decoded-date start-date)))

;;; The version in place now (4/30/97) does not allow the messages to
;;; take arguments. That is a planned near-term extension once the
;;; kinks are worked out of the design. At present the body of the functions
;;; is just the string that it replaces, returned unmodified.

;;; To facilitate coordinating message function definitions (grouped at
;;; the end of this file) with the sites where they are called. Each
;;; message is informally given a number that appears as a comment
;;; with the message and at the place where it is called.


(defmacro define-ok-message (name narrow-control-string  &rest arglist)
  (let ((ok-message-name
	  (intern (format nil "~a-OK-MESSAGE" (symbol-name name))))
	 (transformed-form
	   (setup-ok-message narrow-control-string arglist)))
    `(defun ,ok-message-name ,arglist
	,transformed-form )))


;;; `setup-ok-message' is a hook for mounting more complex options
;;; in the future. Now it takes just one string (the English version)
;;; checks for whether there are any argument insertion points within
;;; it, and then either has the string spread to include them or
;;; just sets it up to be printed. As of 4/30, having an insertion point
;;; is a compile-time error since that aspect of the functionality
;;; isn't complete.

(defun-for-macro setup-ok-message (narrow-control-string arglist)
  arglist  ; to keep the compiler quiet while the segment that uses it is turned off
  (if (position #\< narrow-control-string)
;      `(twith-output-to-text-string
;	 ,@(spread-ok-message-string narrow-control-string arglist))
      (error "Arguments to ok-messages are not yet permitted")
      
;      `(twith-output-to-text-string
;	 (tformat ,narrow-control-string))
      narrow-control-string ))




(defun-for-macro spread-ok-message-string (narrow-control-string arglist)
  (loop with argument-index = -1
	with segment
	with remainder-of-string
	with print-forms
	with first-time-through? = t
	do
    (multiple-value-setq (segment remainder-of-string)
      (next-segment-of-ok-control-string (if first-time-through?
					     narrow-control-string
					     remainder-of-string)))
    (setq first-time-through? nil)
    (cond ((string-equal segment "")
	   (return (nreverse print-forms)))
	  ((stringp segment)
	   (push `(twrite ,segment) print-forms))
	  ((symbolp segment)
	   (push (print-form-for-ok-argument-type
			  segment (nth (incff argument-index) arglist))
			print-forms)))))


;; This version is much easier to understand, but doesn't work
;; because a values return isn't accepted by the destructuring bind
;; in the For. Why?  What's the simplest variation in this style
;; that works?
#+ignore
(defun-for-macro spread-ok-message-string (narrow-control-string arglist)
  (loop with argument-index = -1
	for (segment rest)
	    = (next-segment-of-ok-control-string narrow-control-string)
	    then (next-segment-of-ok-control-string rest)
	when (null segment)
	  return ()
	when (stringp segment)
	  collect `(twrite ,segment)
	when (symbolp segment)
	  collect (print-form-for-ok-argument-type
		    segment (nth (incff argument-index) arglist))))



(defun-for-macro next-segment-of-ok-control-string (control-string)
  (when control-string
    (let* ((index-of-open-angle-bracket
	     (position #\< control-string))
	   (index-of-close-angle-bracket
	     (if index-of-open-angle-bracket
		 (position #\> control-string))))
      (when (and index-of-open-angle-bracket
		 (not index-of-close-angle-bracket))
	(error "ill-formed ok-control-string:~%   open angle bracket ~
                without a matching close."))
      (if index-of-open-angle-bracket
	  (if (=f index-of-open-angle-bracket 0)
	      (values
		(intern (string-upcase
			  (substring control-string
				   (1+f index-of-open-angle-bracket)
				   index-of-close-angle-bracket)))
		(substring control-string (1+f index-of-close-angle-bracket)))
	      (values
		(substring control-string 0 index-of-open-angle-bracket)
		(substring control-string index-of-open-angle-bracket)))
	  (values
	    control-string nil)))))



;;; Routines for handling the arguments that are permitted in OK messages

(defun-for-macro print-form-for-ok-argument-type (type-name argument-symbol)
  (case type-name
    (date
     `(print-universal-date-as-decoded-date ,argument-symbol))
    (otherwise
     #+development
     (error "~a unknown argument type in ok message-string" type-name)
     "<arg>")))


(defun print-universal-date-as-decoded-date (universal-date-fixnum)
  (multiple-value-bind (day month year)
      (decode-universal-date universal-date-fixnum)
    (print-decoded-date day month year)))
;; lifted from new-reformat-line-from-left and expected to be used
;; in the context of the error messages in that section of the code


#+unused
(defmacro with-spaces-on-either-side (printing-form)
  `(progn (twrite-string " ")
	  ,printing-form
	  (twrite-string " ")))








;;;; OK entities



(def-class (ok entity)
  (machine-id nil system (type id-or-whole-string?))
  (authorized-products nil system (type products?))
  (expiration-date? nil system (type authorization-interval?))

  (code-1 nil system (type integer?))
  (code-2 nil system (type integer?))
  (code-3 nil system (type integer?))
  (code-4 nil system (type integer?))
  (code-5 nil system (type integer?))

  (ok-slot-coordinator 0 system save)
  (make-g2-secure? nil (type yes-or-no))

  (authorized-kb-packages nil system (type authorized-packages))

  ;; Number-of-processes-authorized picked up a new alias
  ;; with the 4.0 release: maximum-number-of-independent-g2-allowed
  ;; It has also picked up a new
  (number-of-processes-authorized nil system (type number-of-processes))

  (maximum-number-of-concurrent-floating-telewindows-allowed
    0 system (type non-negative-integer))
  (maximum-number-of-concurrent-floating-tw2-allowed
    0 system (type non-negative-integer))
  )

(def-slot-value-compiler non-negative-integer-or-none (parse-result)
  (cond
    ((eq parse-result 'none) 0)
    ((<f parse-result 0)
     (values
       bad-phrase
       (copy-constant-wide-string #w"This value must be a non-negative integer.")))
    (t parse-result)))

;; Non-negative-integer-or-none: not needed for now, since I'm making the type
;; for maximum-number-of-concurrent-floating-telewindows-allowed just be
;; non-negative-integer.  One drawback: if the value is 0, and none is showing,
;; the editor doesn't rub out the text when you click on NONE.  That's a
;; disappointment for users generally. (MHD 5/4/95)

(def-slot-value-writer non-negative-integer-or-none
    (non-negative-integer-or-none)
  (if (=f non-negative-integer-or-none 0)
      (twrite-string "none")
      (twrite-fixnum non-negative-integer-or-none)))

(add-grammar-rules
  '(
    (non-negative-integer-or-none non-negative-integer)
    (non-negative-integer-or-none 'none)
    ))
  



(define-slot-alias authorized-optional-modules authorized-products ok)


(def-absent-slot-putter expiration-date (frame value)
  (declare (ignore frame value)))


;; Ok-slot-coordinator has as its purpose to guarantee upon loading
;; that authorization will occur if it is correct to do so, regardless
;; of the order of setting slots upon either loading or editing.
;; It is saved, invisible to the user, and always has an integer value.
;; Its default value is 0, and it will never be 0 at any time after editing
;; code-5. Thus once the ok has been made
;; usable, it will always have its slot putter called upon loading.

;; The problem is that authorization on loading must be attempted when the ok
;; object has the id for this machine, when all 5 codes have been loaded,
;; AND when the three other user editable slots have been loaded, if
;; they are going to be loaded. The logic for the bits of ok-slot-coordinator
;; is as follows:
;;         bit 0 is 1 iff: The ok has been edited as stated above, thus
;;             it could potentially authorize some machine.
;;         bit 1 is 1 iff: authorized-products is not nil
;;         bit 2 is 1 iff: expiration-date?? is not nil
;;         bit 3 is 1 iff: authorized-kb-packages is not nil
;;	   bit 4 is 1 iff: make-g2-secure? is not nil
;;	   bit 5 is 1 iff: number-of-processes-authorized is not nil
;;	   bit 6 is 1 iff: number-of-processes-authorized is non-defaulted
;;         bit 7 is 1 iff: number-of-concurrent-floating-tw2 is non-defaulted

;; NOTE: I suspect strongly that this whole facility could be abandoned in favor
;; of an initialize-after-reading method (a facility newer than this one) and,
;; other than that, perhaps a few extra well-chosen nil checks.  It's not
;; something I can quite convince myself should be acted on at once, but I'll
;; think about it, and perhaps discuss with ML or JH.  I discussed it with Ben,
;; and he was not sure it was not needed at runtime.  (MHD 1/31/95)

;; It does appear that this facility remains in use for the construction of
;; the site ok file. Search down from update-gensym-site-ok-file and you'll
;; see it. It's not clear whether the usage there has any consequence, but
;; I figure this is a sleeping dog that I can let lie. (ddm 6/30/98)

(eval-when (:compile-toplevel :load-toplevel :execute)
;; NOTE: change all DEFCONSTANTs into DEFVARs to support SBCL 1.0.29, or:
;;   "Can't declare constant variable locally special: OK-AUTHORIZED-PACKAGES"
;; when compiling check-kbs.lisp, function (authorize-package):
;;   "(declare (special ok-authorized-packages))". --binghe, 2009/7/19
(defvar ok-modified 1)
(defvar ok-authorized-products 2)
(defvar ok-expiration-date? 4)
(defvar ok-authorized-packages 8)
(defvar ok-make-g2-secure? 16)
(defvar ok-number-of-processes-authorized 32)
(defvar ok-maximum-number-of-concurrent-floating-telewindows-allowed 64)
(defvar ok-maximum-number-of-concurrent-floating-tw2-allowed 128)

)



;; reformat-line-from-left is called by slot-putters for all 9 user editable slots
;; and also for the slot-putter of ok-slot-coordinator. It will attempt
;; to authorize if all of the following:
;;   1. machine-id present.
;;   2. if bit 1, then authorized-products is not nil.
;;   3. if bit 2, then expiration-date? is not nil.
;;   4. if bit 3, then authorized-kb-packages is not nil.
;;   5. if bit 4, then make-g2-secure? is not nil.
;;   6. if bit 5, then number-of-processes-authorized is not nil.
;;   7. ok-slot-coordinator is not 0.
;;   8. all 5 codes are present.

;; Under these constraints, authorization during a kb-load will not
;; be attempted before all pertinent data is present.  It cannot be
;; done before ok-slot-coordinator has been loaded, and that prevents
;; it from happening before other slots are loaded.

;; Because slot-putters are called during load for any non-default
;; value and are never called for a default null value,
;; authorization will be attempted exactly once for each
;; properly filled in ok, and it will not happen before pertinent
;; data is present regardless of the order of slot-putting.
;; Proof by cases: (1) If ok-slot-coordinator is the last to be loaded, 
;; all pertinent data is present. It cannot be called before this time,
;; and it will be called at this time because the value is neither null
;; nor defaulted. (2) If ok-slot-coordinator is loaded after every
;; slot except some that are nil and are permitted to be nil for a
;; a completed ok (these are the last ones), authorization will
;; be attempted at that time, and not attempted later for the
;; null values. (3) If ok-slot-coordinator is loaded before some
;; non-null pertinent data, authorization will not be attempted then.
;; But the last, and only the last such slot to be loaded will
;; cause an attempt to authorize because the bits of
;; ok-slot-coordinator specifies whether the loading is complete.

;; The main difference when editing is that an authorization attempt
;; will always be made upon any edit if all 5 codes and machine-id
;; are present.  This is because ok-slot-coordinator cannot be out
;; of synch with the present condition of the other slots.  Therefore
;; the user should be told to fill in all other slots before setting
;; the machine-id.  




;; This should not be a subclass of object!  Object was to be reserved
;; for classes of user defined knowledge base frames which may be reasoned
;; about.


(add-grammar-rules '((id-or-whole-string? whole-string?)
		     (id-or-whole-string? ('id 'for 'this 'machine))))





(def-slot-value-writer id-or-whole-string? (id-or-whole-string?)
  (if id-or-whole-string?
      (tprin id-or-whole-string? t)
      (twrite-string "none")))



;;; The slot value compiler for id-or-whole-string?  expects parse-result to be
;;; a string, the symbol NONE, or the list (ID FOR THIS MACHINE).  In the list
;;; case, this tries to generate the machine id and return that, as a string, as
;;; the value.  In the string case, this just returns parse-result.  If
;;; parse-result is NONE, this returns nil.  Before returning, this function
;;; calls analyze-authorized-packages with (authorized-kb-packages ok) as the
;;; package-authorizations arg, the value it is about to return as the
;;; machine-id arg, and ok as the ok arg.

(def-slot-value-compiler id-or-whole-string? (parse-result ok)
  (let ((transformed-value
	  (cond ((text-string-p parse-result) parse-result)
		((eq parse-result 'none) nil)
		(t			; The user selected "id for this machine".
		 (get-local-machine-id-as-text-string)))))
    (analyze-authorized-packages (authorized-kb-packages ok) transformed-value ok)
    transformed-value))





(def-slot-putter machine-id (frame value)
  (setf (machine-id frame) value)
  (reformat-line-from-left frame)
  value)

(def-slot-putter code-1 (frame value)
  (setf (code-1 frame) value)
  (reformat-line-from-left frame)
  value)

(def-slot-putter code-2 (frame value)
  (setf (code-2 frame) value)
  (reformat-line-from-left frame)
  value)

(def-slot-putter code-3 (frame value)
  (setf (code-3 frame) value)
  (reformat-line-from-left frame)
  value)

(def-slot-putter code-4 (frame value)
  (setf (code-4 frame) value)
  (reformat-line-from-left frame)
  value)

(def-slot-putter code-5 (frame value)
  (setf (code-5 frame) value)
  (unless loading-kb-p
    (setbits (ok-slot-coordinator frame) #.ok-modified))
  (reformat-line-from-left frame)
  value)

;(defmacro products-hash-key () 8388607)

(def-slot-putter authorized-products (frame value)
  (setf (authorized-products frame) value)
  (unless loading-kb-p
    (if value
	(setbits (ok-slot-coordinator frame) #.ok-authorized-products)
	(clearbits (ok-slot-coordinator frame) #.ok-authorized-products)))
  (reformat-line-from-left frame)
  value)

;; Note that this info is not stored elsewhere than on the long list.

(def-slot-putter expiration-date? (frame value)
  (setf (expiration-date? frame) value)
  (unless loading-kb-p
    (if value
	(setbits (ok-slot-coordinator frame) #.ok-expiration-date?)
	(clearbits (ok-slot-coordinator frame) #.ok-expiration-date?)))  
  (reformat-line-from-left frame)
  value)



(def-slot-putter make-g2-secure? (frame value)
  (setf (make-g2-secure? frame) value)
  (unless loading-kb-p
    (if value
	(setbits (ok-slot-coordinator frame) #.ok-make-g2-secure?)
	(clearbits (ok-slot-coordinator frame) #.ok-make-g2-secure?)))
  (reformat-line-from-left frame)
  value)




(def-slot-putter ok-slot-coordinator (frame value)
  (setf (ok-slot-coordinator frame) value)
  (reformat-line-from-left frame)
  value)




(add-grammar-rules
  '((products? products)
    (products? 'none)

    (products product)
    (products (product '\, products) (2 1 3) simplify-associative-operation)

    (number-or-unlimited 'unlimited)
    (number-or-unlimited positive-integer)

    ))




(def-slot-value-compiler products? (translation)
  (compile-symbol-list translation))


(def-slot-value-writer products? (value)
  (write-symbol-list value))


(def-slot-value-writer number-or-unlimited (value)
  (twrite value))




(defparameter 1-2-version (make-system-version 1 2))
(defparameter 4-0-version (make-system-version 4 0))






;;;; Authorization Intervals

;;; Customers can be granted a temporary license to use G2 that becomes
;;; valid on a given date and expires on some specific later date. The
;;; core of this facility is encapsulated here in the encode and decode
;;; authorization-interval functions. These are used by authorization
;;; code proper to determine whether the current data falls within the
;;; specified range.
;;;
;;; When the pair of date expressions is encountered in a ok file, they
;;; are rendered into integers by convert-input-to-universal-date and
;;; then encoded into a single integer by by encode-authorization-interval.
;;; The algorithm for doing this was (according to Ben) developed by
;;; Michael Levin. Here is his description verbatim:

;;; Expiration-date modified on 16 April, 1990 to allow for intervals of validation.
;;; Source language:
;;;    (1) none
;;;    (2) a date (e.g. 16 APR 1990)
;;;    (3) from <date> to <date>   This is new!

;;; Internal forms:
;;;    (1) NIL
;;;    (2) a universal date (u.d.)
;;;    (3) 2^23 + (start-date - Jan 1, 1990)
;;;             + (end-date - start-date)*(2^12)
;;;    An alternative description of (3) is that:
;;;        (i)   it is a fixnum on all implementations,
;;;        (ii)  bit 23 (based on leftmost bit is 0) = 1 which cannot be the case for many
;;;              milenia for coding (2).
;;;        (iii) field (0-11) is the universal date of the start time, offset by the u.d.
;;;                It is valid through the year 2001.
;;;        (iv)  field (12-22) is the valid interval. It is valid for over 5 years.

;;; Note that this algorithm by its nature had to expire in 2001, eleven years
;;; after it was installed. The limitation is due to the restriction on the
;;; size of the bit-field used to contain the two dates to just 23 bits.
;;;
;;; The impact of this limitation is to make it impossible to authorize
;;; temporary licenses that start after the eleven years have expired.
;;; To be precise, if a start date is specified that is on or later than
;;; March 20th, 2001, the start field will overflow into the interval
;;; field. The result is that the dates, as percieved by the ok parser,
;;; will wrap. We know this because a customer making y2k tests used a
;;; starting date of 3/31/2003 and was given the message that their machine's
;;; authorization had not been valid since 13 jan 1994!
;;;
;;; To expedite making this y2k compilant a.s.a.p., I am taking the easy
;;; of changing the reference time constant from 1/1/1990 to 1/1/1998,
;;; which postpones the problem until 2009. A better fix would be to
;;; use more of the containing integer than just 23 bits (but Michael
;;; may be using those bits for other purposes, or the limitation to
;;; just 2^23'd worth of code space may have some other motivation. This has
;;; yet to be determined), or to restructure the encoding into two integers,
;;; but that would require jiggling the stored model of the authorization
;;; numbers, and I don't want to touch that just yet since it might
;;; explode on me. (ddm 6/1/98)  

(defconstant jan-1-1990 32872) ; (encode-universal-date 1 1 1990)
(defconstant jan-1-1998 35794) ; (encode-universal-date 1 1 1998)
(defconstant jan-1-1999 36159) ; (encode-universal-date 1 1 1999)
(defconstant jan-1-2006 38716) ; (encode-universal-date 1 1 2006)
(defconstant jan-1-2009 39812) ; (encode-universal-date 1 1 2009)
(defconstant jan-1-2015 42003) ; (encode-universal-date 1 1 2015)

;; History:
;; r3) jan-1-2015 for G2 2015 (no need to change before 2020)
;; r2) jan-1-2006 for G2 8.3 and 2011
;; r1) jan-1-1998 for G2 from 5.0r4 to 8.2r4 (jpg 12/6/06)
;; r0) jan-1-1990 for G2 before 5.0r4
(defvar reference-date-for-interval-encoding jan-1-2015)

(def-substitution-macro encode-authorization-interval (start-date end-date)
  (+f #.(expt 2 23)
      (-f start-date reference-date-for-interval-encoding) ; was jan-1-2006 (binghe, 2015/11/25)
      (ashf (-f end-date start-date) 12)))

(def-substitution-macro authorization-is-interval-p (authorization-interval?)
  (and authorization-interval?
       (>=f authorization-interval? #.(expt 2 23))))

(def-substitution-macro decode-authorization-interval (authorization-interval)
  (let* ((start-date
	  (+f reference-date-for-interval-encoding
	      (logandf authorization-interval #.(1- (expt 2 12)))))
	 (end-date
	   (+f start-date (logandf (ashf authorization-interval -12)
				   #.(1- (expt 2 11))))))
    (values start-date end-date)))


(def-grammar-category authorization-interval? ()
  (date)
  ('none nil nil-function)
  (('from date 'to date) (2 . 4)))




;;; There used to be a slot-compiler for `authorization-interval?', but
;;; I need to reuse its guts for bounds checking in the License Server.
;;; So I reorganized them to have a simpler return signature and moved them
;;; to license. There is no consequence to this since ok's are not done as
;;; items after G2V5. ddm 6/24/98

;; This writer is not irrelevant because it's used in generating the
;; site ok file.

(def-slot-value-writer authorization-interval? (value)
  (cond ((null value)
	 (twrite "none"))
	((authorization-is-interval-p value)
	 (multiple-value-bind (start-date end-date)
	     (decode-authorization-interval value)
	   (twrite "from ")
	   (multiple-value-bind (day month year)
	       (decode-universal-date start-date)
	     (print-decoded-date day month year))
	   (twrite " to ")
	   (multiple-value-bind (day month year)
	       (decode-universal-date end-date)
	     (print-decoded-date day month year))))
	(t
	 (multiple-value-bind (day month year)
	     (decode-universal-date value)
	   (print-decoded-date day month year)))))



;;; If the dates involved are beyond the end-time of the interval machinery
;;; (i.e. 2009 now) this round trip will fail because the bit fields of
;;; the two quantities will overlap when the encoding is done. The signature
;;; is, e.g., (test-authorization-interval-round-trip '(31 3 2003) '(31 3 2005))

#+development 
(defun test-authorization-interval-round-trip (from-triple to-triple)
  (let* ((from (apply #'encode-universal-date
		      from-triple))
	 (to (apply #'encode-universal-date
		    to-triple))
	 (encoding
	   (encode-authorization-interval from to)))

    (multiple-value-bind (decoded-from decoded-to)
	(decode-authorization-interval encoding)
      (unless (=f decoded-from from)
	(format t "From didn't make the round trip"))
      (unless (=f decoded-to to)
	(format t "To didn't make the round trip")))
    encoding ))








;; jh, 7/2/91.  Moved per-process and KB-timestamping mechanisms to SEQUENCES1,
;; where Telewindows can use them also.


;;;; Floating Telewindows Licenses

;;; The algorithm govering the distribution of floating telewindows
;;; license is somewhat subtle, in that we don't manage the number
;;; available. Instead, each time that there is a request for one,
;;; we let it go through if there are still any available.
;;;
;;; The determination of whether any licenses are still available is
;;; done by `count-available-floating-telewindows' based on an iteration
;;; through the workstations-in-service looking for those that are
;;; licensed as floating, in conjunction with a check of the set of
;;; ui-client-interface objects that exist.
;;;
;;; There are separate pools for TW and TW2 licenses. The general outline
;;; of how they are handed is identical, but the details vary enough
;;; that they are implemented by separate functions with comparable
;;; names. 

;;; For the ui-client-interfaces, each interface attempt is gated by there
;;; being at least one available (tw2) floating license at the time that it
;;; connects.  The license isn't consumed until the first ui-client-session
;;; associated with that interface is successfully logged in. so a race
;;; condition exists when we have just one license left such that two
;;; interfaces might connect but one of them be frozen out of getting an
;;; sessions created because the other got its session made first and took
;;; the last license.


;;; `Floating-telewindows-limit' defaults to 0, meaning not to allow any
;;; floating telewindows connections. It will get a non-zero value for
;;; a particular G2 depending on what is specified in its OK file.


;;; This must be a number in the range [0..8000].

(defvar floating-telewindows-limit 0)

(defvar floating-tw2-limit 0)  ; ranges from 0 to 2^16 - 1



;;; `Count-floating-telewindows-in-service' counts the number of floating
;;; telewindows currently in use.

(defun count-floating-telewindows-in-service ()
  (let* ((floating-license-level
	   (telewindows-license-level-from-product 'floating))
	 (telewindows-count
	  (loop for workstation in workstations-in-service
		count (=f (telewindows-license-level-of-gensym-window
			    (window-for-workstation workstation))
			  floating-license-level))))

    telewindows-count ))



;;; `Count-floating-tw2-in-service' does what its name implies.
;;; Ui-client-interfaces do not consume a license, ui-client-sessions are
;;; counted only if they are valid, i.e. successfully logged in.

(defun count-floating-tw2-in-service ()
  (let ((ui-session-count
	  (loop for session being each class-instance of 'ui-client-session
		count (and
			;; The initial value is unathorized -- any session that exists
			;; but hasn't been vetted doesn't count
			(not (=f (ui-client-session-license-level?-function session)
				 #.unauthorized-lic-level))
			
			;; Some ui-client-sessions will be self-authorized
			;; via an ok file ('named'), so we check and only count
			;; sessions that are licensed as floaters.
			(=f (ui-client-session-license-level?-function session)
			    #.floating-lic-level)

			;; has it been vetted for the case of a secure g2
			(ui-client-session-valid-p session)

			))))
    ui-session-count ))


;; The original counter -- before breaking apart the two kinds of floaters
;; or abandoning the notion of an empty-ui-interface.
#+obsolete
(defun count-floating-telewindows-in-service ()
  (let* ((floating-license-level
	   (telewindows-license-level-from-product 'floating))
	 (telewindows-count
	  (loop for workstation in workstations-in-service
		count (=f (telewindows-license-level-of-gensym-window
			    (window-for-workstation workstation))
			  floating-license-level)))
	 
	(ui-session-count
	  (loop for session being each class-instance of 'ui-client-session
		count (and
			;; the initial value is nil -- any session that exists
			;; but hasn't been vetted doesn't count
			(ui-client-session-license-level?-function session)
			
			;; eventually some ui-client-sessions will be standalone,
			;; so we check and only count sessions that are
			;; licensed as floaters.
			(=f (ui-client-session-license-level?-function session)
			    floating-license-level)

			;; has it been vetted for the case of a secure g2
			(ui-client-session-valid-p session))))

	 (empty-ui-interface-count
	   (loop for interface being each class-instance of 'ui-client-interface
		 as ui-client-sessions = (ui-client-interface-sessions-function
					   interface)
		 unless ui-client-sessions
		   count interface)))

    (+f telewindows-count ui-session-count empty-ui-interface-count)))




;; This was used by a counting routine that effectively reserved space
;; for ui-client-interfaces that hadn't yet established a ui-client-session.
;; Which is a dubious thing to do given that it's a way to attack a G2
;; by clogging all its floaters. 
#+obsolete
(defun some-empty-ui-interfaces-have-been-authorized ()
  (not (loop for interface being each class-instance of 'ui-client-interface
	     as ui-client-sessions = (ui-client-interface-sessions-function interface)
	     thereis (null ui-client-sessions))))
  


;;; `Some-floating-{telewindows tw2}-available-p' is the common core of the
;;; check for whether to grant a floating license. In the standard case,
;;; this is just a matter of counting the number of {workstations /
;;; ui-client-sessions} that are authorized by floating licenses and
;;; comparing that with the limit given in the OK.

;;; But when the G2 has been launched with the `-nowindow' option, we now
;;; (v6) provide an additional floating authorization as compensation. This
;;; situation is noticed inside run-ab, which calls `set-flag-permitting-
;;; free-floating-authorization' to do what it says. While this flag is up
;;; (non-nil), the first connection to request a floating authorization,
;;; either a t2 or a tw, is given one without affecting its pool of
;;; licenses.

;;; What this comes to in practice is that we first see whether there are
;;; any available licenses the usual way. If that fails, and the -nowindow
;;; flag (`free floater-allowed?') is up, we will authorize the connection
;;; (session) via a floater if we haven't already used the 'free' floating
;;; license the 'other' type of connection hasn't already used it. We know
;;; whether they have by checking if they have one more than their
;;; allotment of floating license connected.

(defvar free-floater-allowed? nil)  ;; the flag 

(defun set-flag-permitting-free-floating-authorization ()
  (unless (eq (get-g2-license-level) #.embedded-lic-level)
    (setq free-floater-allowed? t)))





;;; The macro `count-free-telewindows-floaters-available' returns the number of
;;; "free floaters" available for use by Telewindows. That is, 1 if there's a
;;; "free floater" available (for either Telewindows or TW2), and it's not
;;; already already in use as a TW2; otherwise, it returns 0.
;;;
;;; The macro `count-free-tw2-floaters-available' does the same but for TW2.

(defun-substitution-macro count-free-telewindows-floaters-available ()  
  (if (and free-floater-allowed?
	   (<=f (count-floating-tw2-in-service)
		(1+f floating-tw2-limit)))
      1
      0))


(defun-substitution-macro count-free-tw2-floaters-available ()  
  (if (and free-floater-allowed?
	   (<=f (count-floating-telewindows-in-service)
		(1+f floating-telewindows-limit)))
      1
      0))


;;; The macro `compute-floating-telewindows-limit' computes the limit on the
;;; number of Telewindows that may be permitted to be in service.  This limit is
;;; computed as the sum of
;;;
;;;  floating-telewindows-limit -- the floating TW limit from the OK file (a
;;;                                non-negative integer)
;;;
;;; and
;;;
;;;   1, if and only if a free floater is allowed (G2 is running windowless, and
;;;   is not using an embedded license) and the free floater has not already
;;;   been used as a TW2 (floating) client; otherwise, 0.
;;;
;;; Notice that mostly, the count is static (determined once and for all at G2
;;; authorization time).  The only dynamic part is the possible additional "free
;;; floater", based on whether it's in use already as a TW2 client.
;;;
;;; The macro `compute-floating-tw2-limit' computes the corresponding limit on
;;; the number of TW2 clients.

(defun-substitution-macro compute-floating-telewindows-limit ()
  (+f floating-telewindows-limit
      (count-free-telewindows-floaters-available)))

(defun-substitution-macro compute-floating-tw2-limit ()
  (+f floating-tw2-limit
      (count-free-tw2-floaters-available)))

;; TW2 support will ultimately be discontinued, fortunately, so this all can
;; become much simpler. (MHD 9/23/06)



;;; `Count-available-floating-telewindows' gives the current number of floating
;;; telewindows available, a non-negative fixnum.  This DOES take into account
;;; the "free floater" made available when a non-embedded G2 is run windowless.
;;;
;;; `Count-available-floating-tw2s' is the TW2 analog.

(defun count-available-floating-telewindows ()
  (maxf 0 (-f (compute-floating-telewindows-limit)
	      (count-floating-telewindows-in-service))))



(defun count-available-floating-tw2s ()
  (maxf 0 (-f (compute-floating-tw2-limit)
	      (count-floating-tw2-in-service))))

;; Note that this information is avaiable via g2-floating-licenses-
;; remaining. How about other possible places to put this information?  In
;; the network-info table, the kb-configuration system table, the title
;; block, or a combination of some or all of these, or somewhere else?
;; (MHD 5/27/95)











(defun some-floating-telewindows-available-p ()
  (>f (count-available-floating-telewindows) 0))

(defun some-floating-tw2-available-p ()
  (>f (count-available-floating-tw2s) 0))





;;; `Obtain-floating-telewindows-for-workstation-if-possible' is used by TW.

(defun obtain-floating-telewindows-for-workstation-if-possible (gensym-window)
  (cond
    ((some-floating-telewindows-available-p)
     (setf (telewindows-license-level-of-gensym-window gensym-window)
	   (telewindows-license-level-from-product 'floating))
     t)
    (t nil)))

;; Consider having a way to "reserve" a floating telewindows license.  This
;; could be useful for more sophisticated programs that need to offer a menu of
;; "destinations" (G2's that they can get floating Telewindows licenses for),
;; without actually connecting.  (MHD 2/1/95)

;; Should simulation of a lower limit be allowed?! (Ben?) (MHD 1/31/95)



(defun get-floater-license-if-available-for-window (gensym-window)
  (obtain-floating-telewindows-for-workstation-if-possible gensym-window))



;;; This is used by `initialize-gsi-interface' to control whether at T2 is
;;; permitted to connect and instantiate a ui-client-interface. Note the
;;; possibility of race conditions described above.

;;; In the beta version of TW2 (Sequoia) there was a provision here to allow
;;; a G2 with no floating TW to make one connection.

;; Turned off with 5.1r1 and the advent of ok-based, dedicated tw2s.
#+obsolete
(defun license-for-ui-client-interface-available-p ()
  (some-floating-tw2-available-p))



;;; `Can-use-floater-if-level-is-too-low' is a replacement for an unfinished
;;; facility (with the alternative name: decide-when-to-use-floater) that
;;; would have looked at some aspect of the gensym-window and made an
;;; interesting decision as to whether a floater was an appropriate alternative
;;; if the license level of the Telewindows was incompatible with that of
;;; the G2 it was connecting to. The old version always returned T. So will
;;; this version if that is the policy we decide to apply. Given that simplicity
;;; this function could have been replaced with a global variable, but the
;;; cost is minimal and this serves as a stub if we ever do decide to make
;;; conditional decisions about this.

(defmacro can-use-floater-if-level-is-too-low ()
  t)




;;; `Negotiate-telewindows-licensing' obtains the maximum allowable license
;;; level for gensym-window, a Telewindows window just coming up, and returns
;;; that license-level.  That license level is intended to be shipped
;;; immediately back to the client Telewindows, which is presumably waiting
;;; unable to do anything until it arrives.

(defun negotiate-telewindows-licensing (gensym-window)
  (let* ((telewindows-license-level-of-gensym-window
	   (get-telewindows-license-level gensym-window))
	 (g2-license-level
	   (get-g2-license-level))
	 (license-level
	   (cond
	     ((>=f telewindows-license-level-of-gensym-window g2-license-level)
	      telewindows-license-level-of-gensym-window)
	     ((not (can-use-floater-if-level-is-too-low))
	      #.unauthorized-lic-level)
	     ((get-floater-license-if-available-for-window gensym-window)
	      #.floating-lic-level)
	     (t #.unauthorized-lic-level))))
    (setf (telewindows-license-level-of-gensym-window gensym-window) license-level)
    (schedule-tw-modernization-tasks-if-necessary)
    license-level))

;; Note that workstation has still not been set in the gensym window by the
;; time this is needed.  If it were, I'd have put the slot
;; telewindows-license-level-of-gensym-window in the workstation instead of
;; the window.  (MHD 2/1/95)



;;; This is the analog of negotiate-telewindows-licensing as used by
;;; Telewindows2. It is simpler because the heavy-lifting is done by the
;;; caller

(defun session-licensing-level-compatible-with-g2-level (session-symbolic-level)
  (>= (telewindows-license-level-from-product session-symbolic-level)
      (get-g2-license-level)))


;; !!!!!!!!!!! dead code ???
(defun disallow-ui-client-session (ui-client-session)
  (set-ui-client-session-license-level
    ui-client-session
    (telewindows-license-level-from-product 'unauthorized))
  'no-available-floating-licenses)




(defun get-telewindows-license-level (gensym-window)
  (or (get-gensym-window-parameter gensym-window 'telewindows-license-level)
      #.development-lic-level))				; for backward compatibility








;;;; Checking Telewindows authorizations


;;; `Kick-out-unauthorized-telewindows' is to be called periodically to monitor
;;; compliance with licensing limits on the number of floating Telewindows
;;; connections.  It does so without much compassion or selectivity.
;;;
;;; `Kick-out-unauthorized-runtime-telewindows' is similarly crude but deals in
;;; runtime versions of Telewindows (which are discount-priced and not allowed
;;; to run with development versions of G2).
;;;
;;; `kick-out-unauthorized-telewindows-1' is similarly crude but deals in totally
;;; unauthorized versions of Telewindows.
;;;
;;; `Kick-out-unauthorized-telewindows' just dispatches to all of the above
;;; functions.

(defmacro kick-out-unauthorized-floating-telewindows ()
  `(start-adaptive-font-fallback))



;;; Kill-list-of-unauthorized-tw-workstations basically closes the supplied list
;;; of workstations and reclaims the list.
;;;
;;; More precisely, for each element W of workstations, a gensym-cons list of
;;; workstations, if W is in workstations-in-service, this invokes
;;; close-telewindows-connection on W.  Finally, the conses of workstations are
;;; returned to the gensym-cons pool.
;;;
;;; This function does not specify whether or not any workstations in the
;;; argument list will actually have been reclaimed or removed from
;;; workstations-in-service upon exit; it must not be assumed either way. Note,
;;; however, that in practice, in current versions of G2, the schedule generally
;;; must run, possibly over several cycles, before the workstation actually does
;;; get shut down and the workstation gets removed from workstations-in-service.

(def-substitution-macro kill-list-of-unauthorized-tw-workstations (workstations)
  (loop for workstation in workstations
	;; maybe unnec.; in general, TW workstations will remain in
	;; the list, but didn't used to in the past, so don't assume
	;; (MHD 3/31/06)
	when (memq workstation workstations-in-service)
	  do (close-telewindows-connection
	       (window-for-workstation workstation)))
  (reclaim-gensym-list workstations))

(defun start-adaptive-font-fallback () ;devious name
  (let ((count (-f (count-floating-telewindows-in-service)
		   (compute-floating-telewindows-limit))))
    (when (>f count 0)
      (notify-user (number-of-floating-telewindows-limit-exceeded-ok-message)) ;#41
      (loop for workstation in workstations-in-service
	    when (=f (telewindows-license-level-of-gensym-window
		       (window-for-workstation workstation))
		     (telewindows-license-level-from-product 'floating))
	      collect workstation into workstations using gensym-cons
	      and (decff count)
	    while (>f count 0)
	    finally
	      (kill-list-of-unauthorized-tw-workstations workstations)))))


;;; `Kick-out-unauthorized-runtime-telewindows' ... should be renamed
;;; kick-out-unauthorized-deployment-telewindows!
;;;
;;; `Find-unauthorized-telewindow' returns the first window it comes across that
;;; has an authorization level higher than floating, but less that the current
;;; g2 license level, i.e., a deployment Telewindow if this is a development G2.

(defmacro kick-out-unauthorized-runtime-telewindows ()
  `(invoke-interlace-abstraction-if-offered))

(defun invoke-interlace-abstraction-if-offered () ;devious name
  (loop for workstation in workstations-in-service
	when (<f (telewindows-license-level-from-product 'floating)
		 (telewindows-license-level-of-gensym-window
		   (window-for-workstation workstation))
		 (get-g2-license-level))
	  collect workstation into workstations using gensym-cons
	finally
	  (when workstations
	    (loop for workstation in workstations
		  do (notify-user
		       (not-permitted-to-connect-to-development-g2-ok-message) ;#42
		       (get-telewindows-product-name-from-level
			 (telewindows-license-level-of-gensym-window
			   (window-for-workstation workstation)))))
	    (kill-list-of-unauthorized-tw-workstations workstations))))


(defmacro kick-out-unauthorized-telewindows-1 ()
  `(optimize-telewindows-z-layer-model))

(defun optimize-telewindows-z-layer-model () ;devious name
  (loop for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	as telewindows-window-p
	   = (icp-output-port-for-window? gensym-window)
	when (and telewindows-window-p
		  (<=f (telewindows-license-level-of-gensym-window gensym-window)
		       (telewindows-license-level-from-product 'unauthorized)))
	  collect workstation into workstations using gensym-cons
	finally
	  (kill-list-of-unauthorized-tw-workstations workstations)))


(defmacro kick-out-unauthorized-telewindows ()
  `(progn (kick-out-unauthorized-telewindows-1)
	  (kick-out-unauthorized-floating-telewindows)
	  (kick-out-unauthorized-runtime-telewindows)))

;; Work on making this more secretive.  Make there be public and private checks
;; that are different, and harder to detect in the private case! (MHD 6/11/95)


;;; `Consider-telewindows-license-checking' is to be called somewhat frequently,
;;; on the order of a few times a second, but only rarely does it do anything.
;;; It costs about zero to call when it does nothing.  When it does something,
;;; it's just to call kick-out-unauthorized-telewindows, which is still quite
;;; cheap unless it finds things to kick out.

(def-system-variable ctlc-cons-count sequences2 0)

(defmacro consider-telewindows-license-checking ()
  `(progn
     (incff ctlc-cons-count)
     (when (=f ctlc-cons-count 1000)
       (setq ctlc-cons-count 0)
       (kick-out-unauthorized-telewindows))))


	 
  


;;;; Nonces for Telewindows2

;;; Telewindows2 is a java program. Java is trivial to decompile, therefore we
;;; need to take special precautions when dealing with user-names and passwords
;;; when setting up secure G2 sessions when the client is a T2. The user +
;;; password combination that goes across the wire is encrypted (digested) of
;;; course, but (1) decompilation of the source could reveal the material that
;;; goes into our digest, and (2) if just user and password information are
;;; involved, then a UU with a packet sniffer (and patience) could intercept the
;;; digest and use it to impersonate a legitimate user.
;;;
;;; The approach taken has been to issue each session a unique string (the nonce)
;;; and fold it into the construction of the digest that is sent across the wire.
;;; The nonce incorporates time of day and other random information to ensure
;;; that each one given out is unique. (See `make-uuid'.) The process of initiating
;;; a secure session begins by passing a new nonce to the T2 that the session
;;; originates in. That string is then folded into an MD5 digest along with the
;;; usual user + password digest that is used in a TW connection, ensuring that
;;; what passes over the wire is useless for anything other than establishing
;;; one specific session.


;;; The nonce also acts as an index to identify an attempt to initiate a
;;; session that we can use to keep track of the status of the attempt
;;; as it goes through various tries (e.g. the user miss-types their
;;; password or a UU tries to guess a user+password combination). This
;;; is done by creating a `t2-nonce-data' structure along with each new
;;; nonce and storing them in a table keyed to the nonce string.
;;; The 'data-store' field is a bland name for the authorizing-data of
;;; a ok-based log-in. It's value is a simple list with no items on it.

(def-structure (t2-nonce-data)
  (t2-nonce-string nil)
  (t2-nonce-state 'not-allocated)
  (t2-nonce-session-frame nil)
  (t2-nonce-login-attempts-count 0)
  (t2-nonce-data-store nil))

;; this is a clone of uuid-hash
(def-binary-tree t2-nonce-hash
    :constructor make-t2-nonce-hash-tree
    :key-comparitor string=w
    :hash-function sxhashw
    :key-reclaimer reclaim-text-string
    :entry-reclaimer reclaim-structure)

(defvar t2-nonce-table (make-t2-nonce-hash-tree))


;;; The nonce structures are removed from the table and reclaimed iff the
;;; corresponding ui-client-session is logged out.

(defun reclaim-nonce (t2-nonce-data)
  (when t2-nonce-data ; paranoia to avoid an abort
    (let ((nonce (t2-nonce-string t2-nonce-data)))
      ;; This removes it from the table and reclaims the key (the nonce) and the
      ;; entry (the t2-nonce-data) at the same time given that the reclaimers to
      ;; use have been specified with the definition of the binary tree.
      (delete-t2-nonce-hash nonce t2-nonce-table))))


(defun-simple allocate-new-nonce ()
  (let* ((uuid (allocate-new-nonce-internal))
	 ;; The conversion to hex is required to get around a bug such that
	 ;; whereas G2 can send a wide string with high unicodes in to
	 ;; Java, we can't get one back without an error. Probably a
	 ;; gsi problem rather than JavaLink. 5/3/98 rpenny,vkp
	 ;; uuid consumed in following call
	 (string (convert-uuid-string-to-hex-string uuid (lengthw uuid)))
	 (nonce (make-t2-nonce-data)))
    (setf (t2-nonce-string nonce) string)
    (setf (t2-nonce-state nonce) 'login-not-yet-attempted)
    (setf (get-t2-nonce-hash string t2-nonce-table) nonce)
    nonce ))



;;; This is called by log-in-ui-client to change the status of the
;;; nonce data.

(defun note-that-session-has-been-successfully-logged-in (ui-client-session)
  (set-ui-client-session-status ui-client-session 'logged-in)
  (let ((struct (data-for-valid-nonce
		  (get-slot-value ui-client-session 'ui-client-session-nonce))))
    #+development
    (unless struct
      (cerror "continue" "Shouldn't have gotten here!~%We're updating a structure ~
               as part of having successfully logged in~%but the stucture isn't ~
               available in the table."))
    (when struct
      (setf (t2-nonce-state struct) 'logged-in))))

;; This same information ('logged-in) is also kept in the ui-client-session,
;; making it nominally redundant, so if this design is ever revisited this could
;; be reconsidered


;;; Runtime check called by ui-client-session-valid-p

(defun-simple session-has-successfully-logged-in-p (ui-client-session)
  (let ((struct (data-for-valid-nonce
		  (get-slot-value ui-client-session 'ui-client-session-nonce))))
    (when struct
      ;; if the session was logged out, then its nonce structure was
      ;; removed from the table so it's quite plausible to get a nil here.
      (eq (t2-nonce-state struct) 'logged-in))))



;;; Called from log-out-ui-client, which itself is only (5/8/98) called
;;; from g2-release-ui-client-session. We mark the session item to ensure
;;; that it will fail any check by session-has-successfully-logged-in-p,
;;; and we take this occasion to reclaim the nonce so we don't accumulate
;;; an arbitrary number of them.

(defun-simple note-that-session-has-logged-out (ui-client-session)
  (multiple-value-bind (struct error-symbol?)
      (data-for-valid-nonce
	(get-slot-value ui-client-session 'ui-client-session-nonce))

    (unless (and error-symbol?
		 (eq error-symbol? 'no-entry-for-this-nonce)
		 (eq (ui-client-session-status-function ui-client-session)
		     'no-available-floating-licenses))
      ;; This case occurs when there's been an attempt to make a new
      ;; session but we don't have enough licenses to permit it.
      ;; In this situation we didn't bother to create a t2-nonce-structure
      ;; so we certainly shouldn't try to reclaim any.
       
      #+development
      (unless struct
	(cerror "continue" "Shouldn't have gotten here!~
                 ~%This ui-client-session has already been logged out, ~
                 ~%yet we're logging it out again!"))
      (when struct
	(reclaim-nonce struct))))
  (set-ui-client-session-status ui-client-session 'logged-out))



;;; Evaluate a nonce-data for whether it reflects a valid situation as
;;; a user goes through one or more attempts to provide the proper
;;; information (name, password, mode) for logging in to a secure g2.
;;; Only one case (too many attempts) is noticed now, so this is largely
;;; a placeholder.

(defun-simple nonce-is-not-in-a-valid-state (nonce-data)
  (let ((state (t2-nonce-state nonce-data)))
    (or (when (eq state 'too-many-login-attempts)
	  'too-many-login-attempts)
	)))


;;; This is the proper way to get a nonce data structure given a nonce (string).
;;; It returns an error symbol as a second value, and knowledge of some of
;;; these errors is burned into some callers. 

(defun data-for-valid-nonce (string)
  (cond
    ((stringpw string)
     (let ((nonce-data (get-t2-nonce-hash string t2-nonce-table)))
       (cond
	 (nonce-data
	  (values nonce-data (nonce-is-not-in-a-valid-state nonce-data)))
	 (t (values nil 'no-entry-for-this-nonce)))))
    (t (values nil 'nonce-is-not-a-string))))


;;; Given a nonce string, return the ui-client-session that it goes with
;;; or pass back nil and an error symbol if the nonce is bad/undefined.
;;; Revised 11/16/98 to additionally pass back the nonce-data as an
;;; additional third argument. Note that there can be a session object
;;; even if the nonce is not valid because part of its 'validity' is
;;; that, e.g., the associated session has not been logged out.

(defun ui-client-session-for-nonce (uuid)
  (multiple-value-bind (nonce-data? error-symbol?)
      (data-for-valid-nonce uuid)
    (if nonce-data?
	(values (t2-nonce-session-frame nonce-data?)
		error-symbol?
		nonce-data?)
	(values nil error-symbol?))))


;;; This is the g2-side equivalent of what is done on the T2-side to construct
;;; the string that goes over the wire.  See `validate-user-and-password' for
;;; how this is used in context.

(defun hash-nonce-with-password-hash (nonce password-hash)
  (let ((string (obtain-simple-gensym-string 16)))
    (init-MD5-context)
    (update-MD5-context password-hash)
    (update-MD5-context #w":nonce:")
    (update-MD5-context nonce)
    (finalize-MD5-context string)
    (prog1
	(convert-MD5-result-string-to-hex-string string 16)
      (reclaim-simple-gensym-string string))))








;;;; Authorizing Non-floating ('named') Telewindows 2

;;; Checking the validity of an ok-based, self-authorizing tw2 entails
;;; (1) checking that the nonce is live, (2) creating a ui-client-session
;;; now so that we have something to hold the license level that we'll
;;; establish, (3) checking the codes, (4) considering whether we can
;;; legally fall back to a floater if the license-level is too low.
;;; Returns t if the authorization is good. Returns nil and an error
;;; symbol otherwise. This is called from the rpc g2-validate-named-tw2.


(defun ui-client-session-is-not-unauthorized-p (session)
  (not (=f (ui-client-session-license-level?-function session)
	   #.unauthorized-lic-level)))

(defun ui-client-session-is-self-authorized-p (session)
  (let ((level (ui-client-session-license-level?-function session)))
    (and (not (=f level #.unauthorized-lic-level))
	 (not (=f level #.floating-lic-level)))))



;;; Macros to obfuscate the code. Corresponding functions are just below.

(defmacro check-self-authorizing-tw2
       (gsi-interface nonce
	machine-id ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	start-date? expiration-date?
	desired-authorization-level )
  `(compact-cons-pools-now-if-necessary
     ,gsi-interface ,nonce
     ,machine-id ,ok-code1 ,ok-code2 ,ok-code3 ,ok-code4 ,ok-code5
     ,start-date? ,expiration-date?
     ,desired-authorization-level))

(defmacro check-self-authorizing-tw2-1
          (nonce-data machine-id
           ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	   start-date? expiration-date? desired-license-level)
  `(compact-cons-pools-now
     ,nonce-data ,machine-id
     ,ok-code1 ,ok-code2 ,ok-code3 ,ok-code4 ,ok-code5
     ,start-date? ,expiration-date? ,desired-license-level))

(defmacro record-authorizing-codes-on-nonce-data
	  (nonce-data machine-id
	   ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	   start-date? expiration-date?
	   desired-license-level level-to-authorize)
  `(remove-gaps-from-cons-pool
     ,nonce-data ,machine-id
     ,ok-code1 ,ok-code2 ,ok-code3 ,ok-code4 ,ok-code5
     ,start-date? ,expiration-date?
     ,desired-license-level ,level-to-authorize))


(defmacro authorizing-tw2-codes-have-not-changed
	  (session machine-id ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
           start-date? expiration-date?
	   desired-authorization-level)
  `(reposition-cons-pool-fragments
     ,session ,machine-id ,ok-code1 ,ok-code2 ,ok-code3 ,ok-code4 ,ok-code5
     ,start-date? ,expiration-date? ,desired-authorization-level))


(defmacro authorizing-ok-data-for-session (session)
  `(check-pulse-rate-limit ,session))





;;; `Check-self-authorizing-tw2', aka compact-cons-pools-now-if-necessary,
;;; is responsible for all of the validating that has nothing to do with
;;; the codes per se, which is done by Check-self-authorizing-tw2-1.  It
;;; returns t if all the checks are satisfied or nil and an error symbol if
;;; they are not.

(defun compact-cons-pools-now-if-necessary
       (gsi-interface nonce
	machine-id ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	start-date? expiration-date?
	desired-authorization-level )

  (when (already-is-a-named-ui-session-from-this-client
	  gsi-interface machine-id)
    (return-from compact-cons-pools-now-if-necessary
      (values nil 'only-one-named-connection-per-client)))
  
	
  (multiple-value-bind (session? error-symbol? nonce-data)
      ;; Possible errors are:
      ;;  'nonce-is-not-a-string  -- unlikely but logically possible
      ;;     and has to be checked for.
      ;;  'no-entry-for-this-nonce -- i.e. it's stale. The client is
      ;;     improperly reusing a nonce whose nonce-data struct has
      ;;     been reclaimed. 
      ;;  'too-many-login-attempts
      ;;     Their codes were ok, but this is a secure G2 and they
      ;;     could not provide a valid user-name and password
      ;;     within the limit of the number of tries. 
      ;;
      (ui-client-session-for-nonce nonce)

    (when error-symbol?
      (when session?
	;; This also reclaims the nonce. Next time around
	;; it will be stale.
	(g2-release-ui-client-session session?))
      (return-from compact-cons-pools-now-if-necessary
	(values nil error-symbol?)))

      
    (if (and session?
	     (authorizing-tw2-codes-have-not-changed
	       session? machine-id ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
               start-date? expiration-date?
	       desired-authorization-level))
	;; For some reason the client is logging in again on the same,
	;; still-valid nonce. The session associated with that nonce will
	;; record whether the codes were valid for connecting to this G2.
	;; If it's passing in the same codes as before and it was valid
	;; before then it's valid now.
	(if (ui-client-session-is-not-unauthorized-p session?)
	    t
	    (progn
	      (g2-release-ui-client-session session?)
	      (values nil 'already-failed-self-authorization)))
	      
	(check-self-authorizing-tw2-1
	  nonce-data machine-id
	  ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	  start-date? expiration-date? desired-authorization-level))))




;;; `Check-self-authorizing-tw2-1', aka compact-cons-pools-now, is the
;;; continuation of check-self-authorizing-tw2, which is the entry point
;;; for the shallow check on the codes that is done when one of these tw2s
;;; tries to log in. All of the codes and authorization driven checking is
;;; done here. Iff we get through all of it successfully we create a
;;; ui-client-session object and associate it with the nonce. It will be
;;; passed back to the client once they successfully get through the next
;;; step of the protocol, g2-make-ui-client-session.

(defun compact-cons-pools-now
       (nonce-data machine-id
	ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	start-date? expiration-date? desired-license-level)
  
  (let* ((level-to-authorize #.unauthorized-lic-level) ; pessimistic
	 (error-symbol? nil)
	 (ok? nil)
	 (internal-desired-level
	   (cond ((eq desired-license-level 'development)
		  'development)
		 ((eq desired-license-level 'deployment)
		  'restricted-use-option)
		 (t (setq error-symbol? 'undefined-license-level-requested)
		    nil)))
	 (numerical-desired-level
	   (and (not error-symbol?)
		(telewindows-license-level-from-product
		  internal-desired-level))))

    (unless error-symbol?
      (multiple-value-setq (ok? error-symbol?)
	(validate-self-authorizing-tw2
	  machine-id ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	  start-date? expiration-date?
	  internal-desired-level ))
      
      (when ok?  ; codes are good
	(cond
	  ((session-licensing-level-compatible-with-g2-level
	     internal-desired-level)
	   (setq level-to-authorize numerical-desired-level))
	    
	  ((can-use-floater-if-level-is-too-low)
	   (if (some-floating-tw2-available-p)
	       (setq level-to-authorize #.floating-lic-level)
	       (setq error-symbol? 'incompatible-license-level-no-floaters
		     ok? nil)))

	  (t (setq error-symbol? 'incompatible-license-level)))

	(unless error-symbol?
	  (let ((session (make-ui-client-session-internal)))
	    (setf (t2-nonce-session-frame nonce-data) session)
	    (set-ui-client-session-license-level session level-to-authorize)
	    (record-authorizing-codes-on-nonce-data
	      nonce-data machine-id
	      ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	      start-date? expiration-date?
	      internal-desired-level level-to-authorize)))))

    (values ok? error-symbol?)))



;;; `record-authorizing-codes-on-nonce-data', aka remove-gaps-from-cons-pool,
;;; does what it says. We need these for later periodic checks and to track
;;; how many sessions of what sort have logged in from tw2. 

(defun remove-gaps-from-cons-pool
       (nonce-data machine-id
	ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
	start-date? expiration-date?
	desired-license-level level-to-authorize)
  (setf (t2-nonce-data-store nonce-data)
	(gensym-list level-to-authorize desired-license-level
		     start-date? expiration-date?
		     ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
		     machine-id)))


;;; This is really `authorizing-ok-data-for-session', which is the
;;; corresponding accessor to record-authorizing-codes-on-nonce-data's
;;; storing routine.

(defun check-pulse-rate-limit (session)
  (let ((nonce-data (data-for-valid-nonce
		      (ui-client-session-nonce-function session))))
    (when nonce-data
      (t2-nonce-data-store nonce-data))))

;; consider using def-list-structure if it becomes important to
;; have independent access to a lot of these values.


;;; `Machine-id-of-ui-client-session' returns a string. Either the
;;; stored machine-id of this session if it was authorized via an
;;; ok file, or the empty string if it was not. It is written in
;;; a very paranoid style in case the session is unauthorized or
;;; otherwise does not have an associated nonce-data.

(defmacro machine-id-of-ui-client-session (session)
  `(let ((list (authorizing-ok-data-for-session ,session)))
     (if (null list)
	 ""
	 (nth 10 list))))





;;; This really is `authorizing-tw2-codes-have-not-changed'. The situation
;;; it is checking for in check-self-authorizing-tw2 is abnormal and would
;;; never occur in the standard built-in way of logging in a tw2, but since
;;; we have no control over what the users of that Java code do, it is
;;; necessary as a precaution. 

(defun-allowing-unwind reposition-cons-pool-fragments
       (session machine-id ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
        start-date? expiration-date? desired-license-level)
  (protected-let
      ((current-list
	 (gensym-list desired-license-level start-date? expiration-date?
		      ok-code1 ok-code2 ok-code3 ok-code4 ok-code5
		      machine-id)
	 (reclaim-gensym-list current-list))
       (reference-list
	 (authorizing-ok-data-for-session session)))
    
    (when reference-list
      (equal current-list (cdr reference-list)))))










;;;; Secure G2.

(defvar relations-tag-list nil)

(defmacro make-g2-secure ()
  '(setq relations-tag-list t))

(defmacro g2-secure-p ()
  'relations-tag-list)

(def-virtual-attribute g2-is-secure 
    ((class server-parameters) truth-value nil)
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((server-parameters)
	    (make-evaluation-boolean-value (g2-secure-p))))


(add-grammar-rules
  '((number-of-processes positive-integer)
    (number-of-processes ('no 'limit) nil nil-function)))

(def-slot-value-compiler number-of-processes (parse-result)
  (cond ((not (numberp parse-result)) nil)
	((<f parse-result 1)
	 (values bad-phrase
		 (copy-constant-wide-string #w"Use a positive number")))
	((>f parse-result 200)
	 (values bad-phrase
		 (copy-constant-wide-string #w"Not more than 200 processes")))
	(t parse-result)))


(def-slot-value-writer number-of-processes (value)
  (if (numberp value) (twrite value) (twrite "no limit")))


(def-slot-putter number-of-processes-authorized (ok value)
  (setf (number-of-processes-authorized ok) value)
  (unless loading-kb-p
    (if value
	(setbits (ok-slot-coordinator ok) #.ok-number-of-processes-authorized)
	(clearbits (ok-slot-coordinator ok) #.ok-number-of-processes-authorized)))
  (reformat-line-from-left ok)
  value)


(def-slot-putter maximum-number-of-concurrent-floating-telewindows-allowed (ok value)
  (setq value (maxf 0 (minf 8000 value))) ; crude normalizing!
  (setf (maximum-number-of-concurrent-floating-telewindows-allowed ok) value)
  (unless loading-kb-p
    (if (not (eq value			; if not the default, ...
		 (get-slot-init-form
		   'ok
		   'maximum-number-of-concurrent-floating-telewindows-allowed)))		 
	(setbits (ok-slot-coordinator ok)
		 #.ok-maximum-number-of-concurrent-floating-telewindows-allowed)
	(clearbits (ok-slot-coordinator ok)
		   #.ok-maximum-number-of-concurrent-floating-telewindows-allowed)))
  (reformat-line-from-left ok)
  value)


;;; If we ever go back to frame-based ok objects again, add a case here
;;; for floating-telewindows-two's.






(def-grammar-category authorized-packages ()
  (authorized-package (1))
  ((authorized-package '\; authorized-packages) (1 . 3))
  ('none 1 nil-function))

(def-grammar-category authorized-package ()
  ((package package-code package-code package-code) (1 2 3 4))
  ((package 'from date 'to date '\, package-code package-code package-code)
   (1 7 8 9 3 5)))

(def-grammar-category package ()
  (unreserved-symbol))

(def-grammar-category package ()
  (unreserved-symbol))

#+obsolete
(add-grammar-rules
  '((authorized-packages authorized-package (1))
    (authorized-packages (authorized-package '\; authorized-packages)
			  (1 . 3))
    (authorized-packages 'none 1 nil-function)

    (authorized-package (package package-code package-code package-code) (1 2 3 4))

    (authorized-package
      (package 'from date 'to date '\, package-code package-code package-code)
      (1 7 8 9 3 5))

    (package unreserved-symbol)

    (package-code integer)
    ))

				

(def-slot-value-writer authorized-packages (value)
  (if value
      (loop for (authorization . rest) on value
	    for dates? = (cddddr authorization) do
	(tformat "~(~a~) " (first authorization))
	
	(when dates?
	  (twrite "from ")
	  (multiple-value-bind (day month year)
	      (decode-universal-date (first dates?))
	    (print-decoded-date day month year))
	  (twrite " to ")
	  (multiple-value-bind (day month year)
	      (decode-universal-date (second dates?))
	    (print-decoded-date day month year))
	  (twrite ","))
	
	(tformat " ~d ~d ~d" (second authorization)
		 (third authorization) (fourth authorization))
	
	(when rest (tformat ";~%")))
      
      (twrite "none")))





;; If this is ever revived, update the reference date.

;(def-slot-value-compiler authorization-interval? (parse-result)
;  (cond ((symbolp parse-result) nil)
;	((numberp parse-result) parse-result)
;	((not (<=f jan-1-1990 (car parse-result) (+f jan-1-1990 #.(* 11 366))))
;	 (values bad-phrase
;		 (copy-constant-wide-string #w"The start date for an interval must be between 1990 and 2000.")))
;	((>f (-f (cdr parse-result) (car parse-result))
;	     #.(* 5 366))
;	 (values bad-phrase
;		 (copy-constant-wide-string #w"The authorization interval may not exceed 5 years.")))
;	(t (encode-authorization-interval (car parse-result)



(def-slot-value-compiler authorized-packages (parse-result ok)
  (if (eq parse-result 'none)
      nil      
      (loop for pkg in parse-result
	    for start-date? = (fifth pkg)
	    for end-date? = (sixth pkg) doing
	(if (and start-date?
		 (or (>=f start-date? end-date?)
		     (=f start-date? 0)))
	    (return
	      (values bad-phrase
		      (copy-constant-wide-string #w"The start date must be before the end date."))))
	    finally
	      (analyze-authorized-packages parse-result (machine-id ok) ok)
	      (return parse-result))))



(defun analyze-authorized-packages (package-authorizations machine-id ok)
  (delete-frame-note-if-any 'bad-package-authorization ok)
  (when machine-id
    (loop with q3 and q4 and q5 and q6 and c3
	  for authorization in package-authorizations
	  for package-name = (first authorization)
	  for code-1 = (second authorization)
	  for code-2 = (third authorization)
	  for code-3 = (fourth authorization)
	  for start-date = (or (fifth authorization) 0)
	  for end-date = (or (sixth authorization) 0)
	  do
      (multiple-value-setq (q3 q4)
	(eval-sequence-2 (symbol-name-text-string package-name)))
      (multiple-value-setq (q5 q6)
	(button-down-handler machine-id))
      (setq c3 (reverse-list-search q3 q4 q5 q6 code-1 code-2 start-date end-date))
      (unless (=f c3 code-3)
	(add-to-frame-note-particulars-list-if-necessary
	  package-name 'bad-package-authorization ok)))))

(defun new-analyze-authorized-packages (package-authorizations machine-id)
  (loop
    finally (return t)
    with q3 and q4 and q5 and q6 and c3
    for authorization in package-authorizations
    for package-name = (first authorization)
    for code-1 = (second authorization)
    for code-2 = (third authorization)
    for code-3 = (fourth authorization)
    for start-date = (or (fifth authorization) 0)
    for end-date = (or (sixth authorization) 0)
    do
    (multiple-value-setq (q3 q4)
      (eval-sequence-2 (symbol-name-text-string package-name)))
    (multiple-value-setq (q5 q6)
      (button-down-handler machine-id))
    (setq c3
	  (reverse-list-search q3 q4 q5 q6 code-1 code-2 start-date end-date))
    (unless (=f c3 code-3)
      (error-broke-rule-reading-ok-file
	(incorrect-authorization-for-package-ok-message)) ;#43
      (return nil))))



(def-frame-note-writer bad-package-authorization (packages)
  (twrite "the following packages have invalid authorization codes: ")
  (loop for (kb-package . rest) on packages doing
    (tformat "~(~a~)" kb-package)
    (when rest (twrite ", "))))



(def-slot-putter authorized-kb-packages (ok value)
  (setf (authorized-kb-packages ok) value)
  (unless loading-kb-p
    (if value
	(setbits (ok-slot-coordinator ok) #.ok-authorized-packages)
	(clearbits (ok-slot-coordinator ok) #.ok-authorized-packages)))
  (reformat-line-from-left ok)
  value)




;;; Contents of format-structure-description
;;; 0	code 5
;;; 1	chaining-refresh-list 9
;;; 2	(-f code-4 code-5)  lacks a useful purpose
;;; 3	array derrived from machine-id and fingerprint
;;; 4	tab array, 8 x 8 bits
;;; 5	machine-id
;;; 6   code-1
;;; 6   code-2
;;; 7   code-3
;;; 9   code-4
;;; 10  authorized-products-code
;;; 11  expiration-date?
;;; 12  package authorizations
;;; 13  number-of-processes-authorized
;;; 14  maximum-number-of-concurrent-floating-telewindows-allowed
;;; 15  maximum-number-of-concurrent-floating-telewindows-twos-allowed



;;; Consider-Asian-Language-Initializations? is is initially true in a G2
;;; process and can also be set true below right after G2 is authorized.
;;; Service-workstations (in WORKSTATIONS) looks at this once every time it is
;;; called, and if it's true, calls initialize-for-asian-languages, if that
;;; function is defined, and then sets it false.

(def-system-variable consider-asian-language-initializations? sequences2 t)

(defmacro maybe-initialize-asian-languages ()
  `(progn
     (setq consider-asian-language-initializations? t)
     (with-immediate-scheduling ()
       (initialize-for-asian-languages))))


;;; `Authorized-products-of-this-machine' is a global list of symbols
;;; copied from the OK object that authorized this machine.  It is 
;;; set when we authorize, and it is used in the simulated authorization
;;; mechinisms.

;; jh, 7/15/94.  Changed authorized-products-of-this-machine from a system
;; variable to a defvar.  This change has the effect of retaining optional
;; product authorization the second and subsequent times a development G2 is
;; launched, and has no distribution effect.

;; Alas, this change introduces a problem if more than one G2 has been launched
;; from the same development image and simulated authorization is being
;; examined.  The most recently launched G2 will modify the value for
;; authorized-products-of-this-machine, and that will confuse the G2 whose
;; behavior under simulated authorization is being examined.  There is no way
;; around this through the system variable mechanism, however.  Given that
;; loading the OK file sets authorized-products-of-this-machine, and given that
;; we want to skip loading the OK file in development launches after the first,
;; we have to chose between launching two processes with independent versions of
;; authorized-products-of-this-machine and having the value of
;; authorized-products-of-this-machine persist across launches.  Fortunately,
;; all this is moot in distribution, since G2 always runs in an independent
;; process space there.

(defvar text-representation-of-our-ok-object '#w"")
(defvar authorized-products-of-this-machine nil)
   

(def-scrambled-constant-string using-g2-ok-file-message 
    "Using G2 OK file:")

(def-scrambled-constant-string ok-to-run-g2-message
  "It is now OK to run G2!")

(def-scrambled-constant-string should-save-ok-file-message
  "You should now save out the OK knowledge base ~
   as \"g2.ok\" in the default G2 directory.")

(def-scrambled-constant-string should-create-users-and-then-save-ok-file-message-format-control-string
    "~a~a~a")
(def-scrambled-constant-string should-create-users-and-then-save-ok-file-message-1
  "WARNING: this machine's OK object makes G2 secure, but this KB has no authorized users with names, passwords, and user modes.")
(def-scrambled-constant-string should-create-users-and-then-save-ok-file-message-2
    " A G2 run with this OK file would not be usable by anyone.")
(def-scrambled-constant-string should-create-users-and-then-save-ok-file-message-3
    " Please create authorized users as needed, using the Site Maintenance Password supplied by Gensym, and then save out the OK knowledge base as \"g2.ok\" in the default G2 directory.")


(def-scrambled-constant-string can-create-additional-users-and-then-save-ok-file-message-format-control-string
    "~a~a")
(def-scrambled-constant-string can-create-additional-users-and-then-save-ok-file-message-1
    "Note: this machine's OK object makes G2 secure.")
(def-scrambled-constant-string can-create-additional-users-and-then-save-ok-file-message-2    
    " Please create additional authorized users as needed, using the Site Maintenance Password supplied by Gensym, and then save out the OK knowledge base as \"g2.ok\" in the default G2 directory.")

;; The above could be simpler, but there is a length limit on args to
;; def-scrambled-constant-string.  Would someone who knows why please explain
;; the reason for the limit?! I asked JH, and he doesn't know/remember, and nor
;; do I. (MHD 5/3/95)


(def-scrambled-constant-string 
  g2-not-authorized-because-fails-process-count-message
  "The maximum number of permitted G2 processes ~
   are already running on this machine.  ~
   This new G2 process is not authorized.")

(def-scrambled-constant-string 
  g2-not-authorized-because-cannot-register-process-license-message
  "Problem registering process license on network. ~
   G2 is not authorized.")



;;; The following forms implement a shutdown of G2 if it
;;; notices a chain of N failed attempts to authorize.  This
;;; feature was installed in service of getting US Goverment
;;; approval for export to China.  It makes it more difficult
;;; to use a generate and test approach to stealing licenses.

;; - ben Dec 29 95

(defmacro increment-authoriation-attempt-counter ()
  `(progn
     #+development
     (print :authorization-failed-flawed-codes)
     (incff (second keytab-interface-linkage))))

(defmacro authoriation-attempt-counter ()
  `(third keytab-interface-inset))

(defmacro clear-authoriation-attempt-counter ()
  `(setf (fourth keytab-backbone) 0))

(defmacro authorization-attempt-limit ()
  #+development 3
  #-development 18)

(defmacro schedule-authoriation-counter-shutdown ()
  `(progn
     #+development
     (print :shutdown)
     (with-immediate-scheduling ()
       (completely-shut-down-g2))))

(defparameter keytab-backbone '(3 2 1 0 -1 -2))

(defparameter keytab-interface-linkage (cddr keytab-backbone))

(defparameter keytab-interface-inset (cdr keytab-backbone))













;;; See plant-seed. Reverses the state which should only happen if G2 has
;;; had an atttempt to cheat authorization.

;; jh, 6/2/92.  Moved default-format-structure here to avoid a compiler
;; complaint.

(defvar default-format-structure (list nil nil nil nil nil))

(defmacro unplant-seed ()
  '(setf (third default-format-structure)
	 nil))

(defun reformat-line-from-left (ok)
  (declare (special loading-kb-p system-version-from-kb-being-read))

  ;; To maintain compatibility with 1.11 ok.ok files, it is
  ;; necessary to make the ok-slot-coordinator conform to the spec for
  ;; authorized-products and expiration-date? being nil, which must be the case
  ;; since they do not exist in 1.11 kbs.
  (when
    (and loading-kb-p
	 (system-version-greater-p
	   1-2-version
	   system-version-from-kb-being-read))
    (setf (ok-slot-coordinator ok) #.ok-modified))

  (let*  ((coordinator (ok-slot-coordinator ok))
	  (modulus new-modulus)
	  (machine-id (machine-id ok))
	  (code-1 (code-1 ok))
	  (code-2 (code-2 ok))
	  (code-3 (code-3 ok))
	  (code-4 (code-4 ok))
	  (code-5 (code-5 ok))
	  (authorized-products (authorized-products ok))
	  (expiration-date? (expiration-date? ok))
	  (authorized-kb-packages (authorized-kb-packages ok))
	  (number-of-processes-authorized (number-of-processes-authorized ok))
	  (maximum-number-of-concurrent-floating-telewindows-allowed
	    (maximum-number-of-concurrent-floating-telewindows-allowed ok))
	  (make-g2-secure? (make-g2-secure? ok)))

    (when (and
	    ;; It is completely filled in
	    machine-id
	    (not (shunned-machine-id-string-p machine-id)) ; note would be helpful! (frame
					                   ;   note needed, in addition)
	    code-1
	    code-2
	    code-3
	    code-4
	    code-5
	    (>f coordinator 0)
	    (g2-equiv (/=f 0 (logandf coordinator #.ok-authorized-products))
		      authorized-products)
	    (g2-equiv (/=f 0 (logandf coordinator #.ok-expiration-date?))
		      expiration-date?)
	    (g2-equiv (/=f 0 (logandf coordinator #.ok-authorized-packages))
		      authorized-kb-packages)
	    (g2-equiv (/=f 0 (logandf coordinator #.ok-make-g2-secure?))
		      make-g2-secure?)
	    (g2-equiv (/=f 0 (logandf coordinator #.ok-number-of-processes-authorized))
		      number-of-processes-authorized)

	    (g2-equiv			; this is extra wierd because the defautl
	      (/=f 0			;   is 0, not nil
		   (logandf
		     coordinator
		     #.ok-maximum-number-of-concurrent-floating-telewindows-allowed))
	      (if (=f maximum-number-of-concurrent-floating-telewindows-allowed
		      (get-slot-init-form
			'ok
			'maximum-number-of-concurrent-floating-telewindows-allowed))
		  nil
		  maximum-number-of-concurrent-floating-telewindows-allowed))
	    
	    ;; and the ok pertains to this machine
	    (or (and expiration-date? (machine-id-of-site-p (machine-id ok)))
	        (let ((machine-id? (get-local-machine-id-as-text-string)))
		  (prog1 
		      (normalized-string-equal machine-id? (machine-id ok))
		    (reclaim-text-string machine-id?)))))
      (when (<=f (authorization-attempt-limit) (authoriation-attempt-counter))
	(schedule-authoriation-counter-shutdown))
      (let* ((keystring
	       (twith-output-to-text-string
		 (tformat "~a" (machine-id ok))
		 (if (> chaining-refresh-version 3) ; null finger ("") used for 3.0 
		     (tformat "~a" chaining-refresh-list)
		     )))
	     (modularized-key	       
	       (modulo-string-hash keystring modulus))
	     (authorized-products-code
	       (compute-product-code authorized-products))
	     (checksum
	       (let ((code-1x
		       (if (>=f code-1 100)
			   code-1
			   (+f 394 (*f 185 code-1))))
		     (code-2x
		       (if (>=f code-2 100)
			   code-2
			   (+f 260 (*f 165 code-2))))
		     (code-3x
		       (if (>=f code-3 100)
			   code-3
			   (+f 111 (*f 64 code-3))))
		     (code-4x
		       (if (>=f code-4 100)
			   code-4
			   (+f 973 (*f 469 code-4)))))
		 (mod
		   (logxorf
		     (inner-multiply modularized-key code-3x)
		     (inner-multiply code-1x authorized-products-code)
		     (inner-multiply code-2x code-4x)
		     (inner-multiply
		       (or expiration-date? 0)
		       (or expiration-date? 0))
		     (if number-of-processes-authorized
			 (inner-multiply
			   code-3x
			   number-of-processes-authorized)
			 0)
		     (if number-of-processes-authorized
			 (inner-multiply
			   code-4x
			   (ashf number-of-processes-authorized 8))
			 0)
		     (inner-multiply
		       code-1x
		       maximum-number-of-concurrent-floating-telewindows-allowed)
		     (inner-multiply
		       code-2x
		       (ashf maximum-number-of-concurrent-floating-telewindows-allowed
			     8)))		   
		   modulus))))
	(cond
	  ;; 1st: is this ok except for an invalid expiration date?
	  ((and (=f checksum code-5)		; means its ok otherwise
		expiration-date?		; has a specified exp. date
						; the rest checks it; if bad,
						;   it notifies the user
						;   and returns true; otherwise,
						;   it return nil.
		(let ((date (get-universal-date)))
		  (multiple-value-bind (start-date? end-date)
		      (if (authorization-is-interval-p expiration-date?)
			  (decode-authorization-interval expiration-date?)
			  (values nil expiration-date?))
		    (if (or (if start-date? (<f date start-date?))
			    (>f date end-date))
			(let ((notification-text-string
				(twith-output-to-text-string
				  (twrite-string "The authorization for this machine ")
				  (twrite-string
				    (if (>f date end-date)
					"has not been valid since "
					"will not be valid until "))
				  (multiple-value-bind (day month year)
				      (decode-universal-date
					(if (>f date end-date)
					    end-date
					    start-date?))
				    (print-decoded-date day month year))
				  (twrite-string "."))))
			  (notify-user "~a" notification-text-string)
			  (reclaim-text-string notification-text-string)
			  t))))))		; T stops COND, which returns no interesting 
						;    value, from falling through

	  ;; jh, 11/14/91.  Added G2 per-process authorization here and removed it
	  ;; from run-ab.  This had caused G2 to exit with a failed process count
	  ;; whenever the OK file was not found.  Now it gives the users a chance
	  ;; to authorize manually.  While I was at it, I made messages like "OK
	  ;; to run G2" into scrambled strings, to confound a UU looking for
	  ;; constant strings in the C image.

	  ;; 2nd: is this OK except for running on a machine with too many G2
	  ;; processes already?
	  ((and (=f checksum code-5)
		(not (unlimited-number-of-g2-processes-permitted-p 
		       number-of-processes-authorized))
		(progn 
		  (unless (per-process-license-registered-and-listener-activated-p)
		    (setf (per-process-license-registered-and-listener-activated-p) 
			  (and (register-licensed-product 
				 (g2-image-product)
				 (g2-image-option authorized-products))
			       (license-listen))))
		     #-development
		     (cond
		       ((not (per-process-license-registered-and-listener-activated-p))
			(notify-user
			  (g2-not-authorized-because-cannot-register-process-license-message))
			t)
		       ((new-licensed-g2-process-permitted-p 
			  number-of-processes-authorized
			  authorized-products)
			nil)
		       (t (notify-user
			    (g2-not-authorized-because-fails-process-count-message))
			  t))
		  #+development
		  nil)))    ;as above, the t exits the cond and the nil falls through
					

	  ((=f checksum code-5)
	   ;; should screen out the majority of innocent typos
	   (set-list-contents
	     format-structure-description
	     code-5
	     chaining-refresh-list
	     (-f code-4 code-5)
	     (make-array-from-strings (machine-id ok) chaining-refresh-list)
	     (make-array 8)	    
	     (copy-text-string machine-id)
	     code-1
	     code-2
	     code-3
	     code-4
	     ;; codes for authorized products, expiration date, and number of processes
	     (let ((cons (nth 10 format-structure-description)))
	       (setf (car cons) authorized-products-code)
	       cons)	       
	     expiration-date?
	     ;; Only package authorizations that are valid should be installed.
	     (loop with frame-note? =
		     (get-particulars-of-frame-note-if-any 'bad-package-authorization ok)
		   for pkg in authorized-kb-packages
		   when (not (memq  (first pkg) frame-note?))
		     collect (copy-list pkg))
	     number-of-processes-authorized
	     maximum-number-of-concurrent-floating-telewindows-allowed
	     )

	   (unless (g2-authorized-p) 
	     (when (and expiration-date?
			(machine-id-of-site-p (machine-id ok)))
	       (c-nsleep (machine-id ok))))

	   (setf text-representation-of-our-ok-object
		 (twith-output-to-text-string (print-frame ok)))
	   
	   (setf authorized-products-of-this-machine 
		 (loop for visible-product in authorized-products
		       collect visible-product))

	   (setf floating-telewindows-limit
		 maximum-number-of-concurrent-floating-telewindows-allowed)
	   (schedule-tw-modernization-tasks-if-necessary)

	   (clear-authoriation-attempt-counter)
	   
	   (notify-user (ok-to-run-g2-message))

	   (when (nupec-really-authorized-p)
	     (authorize-nupec))

	   (maybe-initialize-asian-languages)

	   ;; When authorization occurs for the first time, G2 is made secure if the
	   ;; OK item is set to do so.
	   (if (and (not (g2-authorized-p))
		    make-g2-secure?)
	       (make-g2-secure))
	      
	   (unless loading-kb-p
	     (cond
	       (make-g2-secure?
		(issue-mgs-notifications))
	       (t
		(notify-user (should-save-ok-file-message)))))

	   (unplant-seed)

	   (setq unevaluated-expression t))

	  
	  ((g2-authorized-p)
	   (increment-authoriation-attempt-counter)
	   (notify-user 
	     "Your machine has already been authorized but there is ~
              now an OK for this machine which is incorrect. ~
              You are still authorized."))
	  
	  (t
	   (increment-authoriation-attempt-counter)
	   ;; Extend-grace-period-on-ok-files-if-appropriate is being
	   ;; removed from the sources.  (ghw 3/5/96)
;	   (or (extend-grace-period-on-ok-files-if-appropriate ok)
	       (notify-user
		 "The authorization is not correct.  ~
                  Please check it and try again.")))

	(reclaim-text-string keystring)))))










;;; `Choose-keytab' 

(defun choose-keytab ()
  (case chaining-refresh-version
    (3       
     (copy-optimized-constant 
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 122 174
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5
	 48 95 230 251 212 74 32
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165)))
    (4
     (copy-optimized-constant
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 122 174
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165)))
    (5
     (copy-optimized-constant
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 174 122
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165)))
    (6  ;; presently identical to version 5 (ddm 6/30/99)
     (copy-optimized-constant
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 174 122
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165)))
    (8  ;; jpg 4/28/04
     (copy-optimized-constant
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 174 122
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32 171 149 5 
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165)))
    ;; GENSYMCID-1519: G2 2015 licensing
    ;; Version 9 was never used actually, now we reuse it for Version 12 (G2 2015).
    ((9 12) ;; Chun Tian (binghe), 10/2/2010
     (copy-optimized-constant
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 174 122
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 172 162 ; 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32 171 149 5 
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165)))
   (11  ;; tam.boirsyakovita@gdev.biz 06/19/2011
       (copy-optimized-constant
         #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 174 122
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32 171 149 5 
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 115 134 158 41 123 236 169 99 186 80 125 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165)))
    (t
     (error "unknown version: ~d" chaining-refresh-version))))


(def-system-variable keytab1 sequences2 (:funcall choose-keytab))

;; Consider making a read-time dependency at some point, say for the next (Beta)
;; revision or for the final release.  That will reduce the prominence of this
;; data as well its size.  (MHD 12/19/94)


(defmacro keytab ()
  ;; `',keytab1
  'keytab1)

;; This should be hidden.  It is hidden as long as names are scrambled due
;; to the fact that we never ship debuggable images to customers. Beware!
;; (MHD 5/19/93)
;; 
;; ;; -- UPDATE: This has been turned into a macro that accesses the array directly
;; ;; inline, rather than indirectly accessing it through the variable.






(defmacro transpose-c6 ()
  (let ((r-var-list '(r0 r1 r2 r3 r4 r5 r6 r7))
	(s-var-list '(s0 s1 s2 s3 s4 s5 s6 s7)))
    
    `(let*
       ,(nconc
	  (loop for r-var in r-var-list
		   for i from 0
		   collecting `(,r-var (svref c6 ,i)))
	  (loop for s-var in s-var-list
		   collecting `(,s-var 0)))

       ,@(loop for i from 0 to 7
	       for r-var in r-var-list
	       nconcing
		 (loop for j from 0 to 7
		       for s-var in s-var-list
		       nconcing
			 `((if (/=f 0 (logandf ,r-var ,(ash 1 j)))
			       (setq ,s-var (logiorf ,s-var ,(ash 1 i)))))))

       ,@(loop for k from 0 to 7
	       for s-var in s-var-list
	       collecting
		 `(setf (svref c6 ,k) ,s-var)))))


(defmacro replace-c6 ()
  '(loop for i from 0 to 7 do
     (setf (svref c6 i)
	   (svref (keytab) (svref c6 i)))))



(defmacro encode-c6 ()
  '(loop for i from 1 to 5 do
     (replace-c6)
     (transpose-c6)))










;;; extract-byte has as value the nth byte from the left
;;; counting the leftmost byte as byte 0.

(defmacro extract-byte (fixnum byte-position)
  (if (typep byte-position 'fixnum)
      `(logandf (ashf ,fixnum ,(*f -8 byte-position)) 255)
      `(logandf (ashf ,fixnum (*f -8 ,byte-position)) 255)))



(defun limited-true-list-p (x n)
  (loop for y = x then (cdr y)
	for i from 0	
	doing
    (cond ((>f i n) (return nil))
	  ((null y) (return t))
	  ((atom y) (return nil)))))

;; Propagates to BOOKS.



(defmacro special-or (&body body)
  (let ((var (gensym)))
    `(prog (,var)
	   ,@(loop for form in body collect `(if (setq ,var ,form) (return ,var)))
	   nil)))

(defmacro special-and (&body body)
  (if body
      `(prog ()
	     ,@(loop for (form . rest) on body
		     collect
		       (if rest
			   `(if (null ,form) (return nil))
			   `(return ,form))))
      t))



	    
(defmacro check-ok (&optional why-not?)
  (cond
    (t
     #+unrestricted
     '(progn 
	why-not?
	t)
     #-unrestricted
     `(let
	((list (symbol-value (intern-text-string
			       (twith-output-to-text-string
				 (tformat "~a-~a-~a" 'format
					  (car format-redefinition-list)
					  (second format-redefinition-list)))))))
	,why-not?				; not used
	(loop for cons = list then (cdr cons)
	      for i from 1 to 14
	      do (if (atom cons)
		     (progn
;		    ,@(if why-not? `((format t "No OK: (atom cons)")))
		       (return nil)))
	      finally
		(return
		  (let*
		    (pkg-name d1 d2 d3 dd1 dd2 dd3 q1 q2 q3 q4 q5 q6
		     start-time end-time
		     (c1 (seventh list))
		     (c2 (eighth list))
		     (c3 (ninth list))
		     (c4 (tenth list))
		     (array (fourth list))
		     (c6 (fifth list))
		     (machine-id (sixth list))
		     (product-code
		       (let ((cons (nth 10 list)))
			 (if (consp cons) (car cons))))
		     (expiration-date? (nth 11 list))
		     (packages (nth 12 list))
		     (processes (nth 13 list))
		     (floaters (nth 14 list))
		     (t2-floaters (nth 15 list)))
		    
		    (cond
		      ((special-or (not (simple-vector-p array))
			   (not (simple-vector-p c6))
			   (not (typep c1 'fixnum))
			   (not (typep c2 'fixnum))
			   (not (typep c3 'fixnum))
			   (not (typep c4 'fixnum))
			   (not (>=f (length array) 8))
			   (not (=f (length c6) 8))
			   (not (loop for i from 0 below (length array)
				      for j = (svref array i)
				      always (and (typep j 'fixnum) (<=f 0 j 255))))
			   (not (typep product-code 'fixnum))
			   (and expiration-date?
				(not (typep expiration-date? 'fixnum)))
			   (not (text-string-p machine-id))
			   (not (and
				  (limited-true-list-p packages 200)
				  (loop for pkg in packages
					always
					  (or
					    (not (assq pkg-name control-sequence-record))
					    (special-and (limited-true-list-p pkg 4)
						 (setq pkg-name (first pkg))					      
						 (setq d1 (second pkg))
						 (setq d2 (third pkg))
						 (setq d3 (fourth pkg))
						 (setq start-time
						       (or (fifth pkg) 0))
						 (setq start-time
						       (or (sixth pkg) 0))	  
						 (symbolp pkg-name)
						 (typep d1 'fixnum)
						 (typep d2 'fixnum)
						 (typep d3 'fixnum)
						 (setq pkg-name
						       (symbol-name-text-string pkg-name))
						 (multiple-value-setq (q1 q2)
						   (color-match-p pkg-name))
						 (multiple-value-setq (q3 q4)
						   (eval-sequence-2 pkg-name))
						 (multiple-value-setq (q5 q6)
						   (button-down-handler machine-id))
						 (multiple-value-setq (dd1 dd2)
						   (procedure-recursive q1 q2 q5 q6
									start-time end-time))
						 (setq dd3
						       (reverse-list-search q3 q4 q5 q6
									    dd1 dd2
									    start-time end-time))
						 (=f d1 dd1)
						 (=f d2 dd2)
						 (=f d3 dd3)					    
						 )))))
			   (not (or (null processes) (typep processes 'fixnum)))
			   (not (and (typep floaters 'fixnum)
				     (>=f floaters 0)
				     (<=f floaters 8000)))
			   (not (and (typep t2-floaters 'fixnum)
				     (>=f t2-floaters 0)
				     (<=f t2-floaters #.(-f (expt 2 16) 1)))))

		       nil)
		      (t
		       (loop with size = (length array)
			     with bunch-count = (-f (ceilingf size 8) 1)
			     for i from 1 to bunch-count
			     initially (loop for i from 0 to 7 do
					 (setf (svref c6 i) (svref array i)))
			     do
			 (encode-c6)
			 (loop for k from 0 to 7
			       for offset
				   = (*f 8
					 i)
			       for j = (+f k offset) do
			   (setf (svref c6 k)
				 (logxorf (svref c6 k)
					  (if (<f j size)
					      (svref array j)
					      j))))
			     finally
			       ;; For new scheme add product-code and expiration-date?
			       (setf (svref c6 7)
				     (logxorf (svref c6 7) (extract-byte product-code 0)))
			       (setf (svref c6 6)
				     (logxorf (svref c6 6) (extract-byte product-code 1)))
				 
			       (when expiration-date?
				 (setf (svref c6 5)
				       (logxorf (svref c6 5) (extract-byte expiration-date? 0)))
				 (setf (svref c6 4)
				       (logxorf (svref c6 4) (extract-byte expiration-date? 1))))

			       (when processes
				 (setf (svref c6 3)
				       (logxorf (svref c6 3) processes)))
			     
			       (unless (=f floaters 0) 
				 (setf (svref c6 2)
				       (logxorf (svref c6 2)
						(extract-byte floaters 0)))
				 (setf (svref c6 0)
				       (logxorf (svref c6 0)
						(extract-byte floaters 1))))

			       (unless (=f t2-floaters 0)
				 (setf (svref c6 1)
				       (logxor (svref c6 1)
					       (extract-byte t2-floaters 0)))
				 (setf (svref c6 0)
				       (logxor (svref c6 0)
					       (extract-byte t2-floaters 1))))
		       
			       (encode-c6)
			       (return
				 (or
				   (and
				     (=f c1 (+f (svref c6 0)
						(*f 256 (svref c6 1))))
				     (=f c2 (+f (svref c6 2)
						(*f 256 (svref c6 3))))
				     (=f c3 (+f (svref c6 4)
						(*f 256 (svref c6 5))))
				     (=f c4 (+f (svref c6 6)
						(*f 256 (svref c6 7)))))
;				,@(if why-not? `((format t "No OK: bad codes")))
				   ))))))))))))







(defvar redef-class-instance (cons (make-array 4) (cons nil (cdr default-format-structure))))

(setf (aref (car redef-class-instance) 1) redef-class-instance)

(defvar saved-initial-status (car redef-class-instance))


#+development
(defvar destruct-ack nil)

;; Revert this when the new authorization is stabilized.



; (def-kb-specific-variable trouble-workspace? sequences2 nil)
; (def-kb-specific-variable frame-serial-number-for-trouble-workspace? sequences2)

(defvar system-slot-accessor
	(list 34 "This G2 is not authorized. Please shut it down and call Gensym for proper authorization."))



(defvar color-code-differences (list nil (second system-slot-accessor)))


;(defun replace-format-using-equivalent-font (class)
;  (declare (ignore class))
;  (when (and trouble-workspace?
;	     (frame-has-not-been-reprocessed-p trouble-workspace?
;					       frame-serial-number-for-trouble-workspace?))
;    (delete-frame trouble-workspace?))
;  (setq trouble-workspace?
;	(post-prominent-notification
;	  (copy-text-string (second color-code-differences))
;	  900 700))
;  (setq frame-serial-number-for-trouble-workspace? (current-frame-serial-number)))


(defmacro deauthorize ()
  '(progn
    (setq unevaluated-expression within-side-limits)
    (loop for cons on format-structure-description
	  for i from 0
	  do
      (if (=f i 10)
	  (setf (car (car cons)) 0)
	  (setf (car cons) nil)
	  ))))


(def-kb-specific-variable alternate-chaining-queue sequences2 nil)

(def-kb-specific-variable revert-to-fuzzy-cache-p sequences2 nil)

(defun-simple call-post-prominent-notification (a b c d)
  (post-prominent-notification a b c d))

(defun-simple redraw-solid-rectangles-without-overlap (class)
  (declare (ignore class))
  (when (destroyer-armed-p)
    (redraw-solid-rectangles-without-overlap-1
      (slot-descriptions (class-description 'variable)))
    (setq available-gensym-conses (make-permanent-list 5))
    (setf (cdr (last available-gensym-conses)) available-gensym-conses)))

(defun replace-format-using-equivalent-font (class)
  (declare (ignore class))
  (unless system-is-running
    (deauthorize))
  (when (or system-is-running system-has-paused)
    (arm-destroyer)
    (with-future-scheduling (alternate-chaining-queue 1 (g2-future-interval 2))
      (call-post-prominent-notification
	(copy-text-string (second color-code-differences)) 900 700 t))
    (with-future-scheduling (revert-to-fuzzy-cache-p 1 (g2-future-interval 4))
      (redraw-solid-rectangles-without-overlap nil))))








(defun redraw-solid-rectangles-without-overlap-1 (x)
  (if (atom (car x))
      (setf (car x) nil)
      (redraw-solid-rectangles-without-overlap-1 (car x)))
  (if (atom (cdr x))
      (setf (cdr x) nil)
      (redraw-solid-rectangles-without-overlap-1 (cdr x))))
  


(defmacro plant-seed ()
  '(setf (third default-format-structure)
	 t))






;;; array-made-from-strings-p is true if array is equal to an array
;;; which is the value of (make-array-from-strings string1 string2)
;;; It allocates no storage, and does not use bignums.

(def-substitution-macro array-made-from-strings-p (string1 string2 array)
  (loop with length1 = (lengthw string1)
	with length2 = (lengthw string2)	
	with nlength1 = (number-of-alphanumerics-in-string string1)
	with nlength2 = (number-of-alphanumerics-in-string string2)
	with w1 = nil
	with w2 = nil
	with i1 = 0
	with i2 = 0
	for i from 0 below nlength1
	initially
	  (when (/=f (length array) (+f nlength1 nlength2)) (return nil))
	do
    (loop until (>=f i1 length1) do
      (when (setq w1 (digit-char-pw (charw string1 i1) 36))
	(incff i1)
	(return (values)))
      (incff i1)
	  finally
	    (setq w1 nil))
    (when (/=f (aref array i)
	       (if (=f i 0)
		   w1
		   (modf (+f (*f 3769 (aref array (-f i 1)))
			     (*f 6237 w1))
			 256)))
      (return nil))
    
	finally
	  (return
	    (loop for i from nlength1 below nlength2 do
	      (loop until (>=f i2 length2) do      
		(when (setq w2 (digit-char-pw (charw string2 i2) 36))
		  (incff i2)
		  (return (values)))
		(incff i2)
		    finally
		      (setq w2 nil))
	      (when (/=f (aref array i)
			 (modf (+f (*f 3769 (aref array (-f i 1)))
				   (*f 6237 w2))
			       256))
		(return nil))
		  finally
		    (return t)))))




;;; The function `match-machine-id-for-this-machine-online' matches the machine
;;; ID represented by finger and array with the one or more actual machine ID's
;;; of this machine.

;;; After the first time this is called, it caches the machine ID of the machine
;;; in the special variable cached-matching-machine-id?.  [This is equivalent to
;;; what was done previously, though it seems highly questionable from a
;;; security point of view. Review later! (MHD 7/3/00)]

(defvar cached-matching-machine-id? nil)

(defun-allowing-unwind match-machine-id-for-this-machine-online (finger array)
  (if cached-matching-machine-id?
      (array-made-from-strings-p cached-matching-machine-id? finger array)
      (protected-let ((ids (get-local-machine-ids-as-gensym-list)
			   (reclaim-gensym-tree-with-text-strings ids)))
	(loop for id in ids
	      when (array-made-from-strings-p id finger array)
		do (setq cached-matching-machine-id? (copy-text-string id))
		   (return t)))))




;; Propagated to CYCLES and MENUS.

(defmacro have-a-nice-day ()
  (cond
    (t
     ;; Use temporary context for bignum.
     #+unrestricted
     '(progn)
     #-unrestricted
     (let ((list (gensym))
	   (cons (gensym))
	   (array (gensym))
	   (finger (gensym))
	   (i (gensym))
	   (j (gensym))
	   ;; never used:   (MHD 3/21/91)
;	   (expiration? (gensym))
	   )	
       `(let
	  ((,list
	    (symbol-value
	      (intern-text-string
		(twith-output-to-text-string
		  (tformat
		    "~a-~a-~a" 'format
		    (car format-redefinition-list)
		    (second format-redefinition-list)))))))
	  (if (null 
		(and
		  (loop repeat 15
			for ,cons = ,list then (cdr ,cons)
			never (atom ,cons))
		  (let*
		    ((,array (fourth ,list))
		     (,finger (second ,list))
		     ;; never used:   (MHD 3/21/91)
;		     (,expiration? (nth 11 ,list))
		     )
		    (prog1
		      (cond
			((or ;(null ,key-as-bignum?)
			     (not (simple-vector-p ,array))
			     (not (>=f (length ,array) 8))
			     (not (loop for ,i from 0 below (length ,array)
					for ,j = (svref ,array ,i)
					always (and (typep ,j 'fixnum) (<=f 0 ,j 255))))
			     (not
			       ;; Verify that the machine-id of this machine is the
			       ;; same as the one that encoded the array.
			       (match-machine-id-for-this-machine-online ,finger ,array))

			     ;; Expiration checking

			     ;; Authorized-products

			     ;; Per-process licensing
			     )
			 nil)
			(t t))
		      ;; Why are these local variables whose scope is about
		      ;; to be exited set to NIL? ML 2/7/91   (
		      ;; -- To make the disassembled, or interrupted, code
		      ;; harder to read.
		      ;; (MHD 3/21/91)
		      (setq ,finger nil)
		      (setq ,array nil)
		      (setq ,list nil)))))
	      (plant-seed)))))))








;;; Grammar-rules-to-add-for-nupec-after-authorization is the variable that is
;;; built up at load time with the grammar rules to be added to the current
;;; grammar if and G2 is authorized for NUPEC.

(defvar grammar-rules-to-add-for-nupec-after-authorization nil)



;;; Add-grammar-rules-for-nupec-after-authorization ...  adds all new rules in
;;; grammar-rules to grammar-rules-to-add-for-nupec-after-authorization.
;;; Grammar rules on that list at the time of nupec authorization will be added
;;; to the current grammar, in order; i.e., they will be added at runtime instead
;;; of at load time.

;;; Note that a new grammar rule that matches an old one in its first and second
;;; elements causes the old one to be replaced with the new one in its current
;;; position; new rules that do not so match are simply put at the end.

(defun add-grammar-rules-for-nupec-after-authorization (grammar-rules)
  (loop for new-rule in grammar-rules
	do (loop as l on grammar-rules-to-add-for-nupec-after-authorization
		 as old-rule = (car l)
		 when (and (eq (first new-rule) (first old-rule))
			   (equal (second new-rule) (second old-rule)))
		   return (setf (car l) new-rule)
		 finally
		   (setq grammar-rules-to-add-for-nupec-after-authorization
			 (nconc grammar-rules-to-add-for-nupec-after-authorization
				(list new-rule))))))

;; This is used only below, and in MENUS, for nupec menu choices.  (MHD 5/27/92)



(add-grammar-rules-for-nupec-after-authorization
  '(;; From GFI-STUBS
    (gfi-file-format ('NUPEC 'snapshot) nupec-snapshot)
    (gfi-file-format ('NUPEC 'snapshot 'with 'restart 'time)
		     nupec-snapshot-with-restart-time)
    ;; From CYCLES
    (timing-scheduler-mode ('nupec 'catch 'up 'mode) nupec-catch-up)
    
    ;; From GRAPHS2
    (plot-marker-phrase ('using class 'NUPEC 'plot 'marker) (3 . 2))
    
    ;; From GRAMMAR1
    
    ;; In the target G2 when a NUPEC synchronization has finished, the event
    ;; proposition "whenever nupec synchronization occurs..." should be
    ;; executed.
    (event-literal ('nupec 'synchronization 'occurs)
		   (nupec-synchronization-occurs))
    
    (action ('nupec 'synchronize synchronize-reference-list
	     'across unique-designation)
	    (nupec-synchronize 5 3)
	    fix-nupec-synchronize)
    
    (nupec-extra-action-list
      (action 'and action-list-3) (and 1 3) simplify-associative-operation)
    (nupec-extra-action-list action)
    (nupec-extra-action-list 'none nil)
    
    ;; Moved to GRAMMAR4 and de-nupecified. -dkuznick, 7/15/98

    ;; "a-or-an" in the following two rules used to be 'a, but that was too
    ;; cute; when users selected "a" they would get a subset of the grammar
    ;; they would have gotten if they had selected "an", since the other rules
    ;; contribute additional grammar (for ACTION, following CREATE) that can
    ;; begin with "an". (MHD 1/11/91)
;    (action ('create a-or-an 'NUPEC 'explanation 'for unique-designation)
;	    (create-nupec-explanation 6))
;    (action 
;      ('create a-or-an 'NUPEC 'explanation local-name 'for unique-designation)
;      (create-nupec-explanation 7 5))
    
    
;    ;; Moved to GRAMMAR5. -dkuznick, 7/15/98
    
;    (variable-frame-flags 
;      (variable-forward-chain-spec '\, variable-backward-chain-spec
;				   '\, cache-explanation-spec)
;      (1 3 5))
;    (parameter-frame-flags 
;      (variable-forward-chain-spec '\, cache-explanation-spec)
;      (1 passive-flag 3))
    
    ;; These next two will not be folded back into the general code, as we now
    ;; use override-for-object-definition, which is defined in terms of
    ;; <mumble>-frame-flags which is defined correctly for the cache explanation
    ;; stuff -dkuznick, 7/15/98

;    (override ('options 'for 'variable '\: variable-forward-chain-spec
;	       '\, variable-backward-chain-spec '\, cache-explanation-spec)
;	      (frame-flags (5 7 9) variable))
    
;    (override ('options 'for 'parameter '\:
;	       variable-forward-chain-spec '\, cache-explanation-spec)
;	      (frame-flags (5 7) parameter))
    
    
;    ;; Moved back to RULES, lost duplicate second case -dkuznick, 7/15/98
;    (rule-frame-flags (invocable-via-backward-chaining '\,
;		       invocable-via-forward-chaining '\,
;		       may-cause-data-seeking '\,
;		       may-cause-forward-chaining '\,
;		       cache-explanation-spec)
;     (1 3 5 7 9))
;    (rule-frame-flags (invocable-via-backward-chaining '\,
;		       invocable-via-forward-chaining '\,
;		       may-cause-data-seeking '\,
;		       may-cause-forward-chaining '\,
;		       cache-explanation-spec)
;     ;; (1 3 5 7 9 11 13)
;     (1 3 5 7 9)) ;lose the 11 13 -dkuznick, 6/12/98
    ))





;;; The function `authorize-nupec' is called to authorized a G2 for NUPEC.  The
;;; features are present in each image but only become available after this
;;; function is called.  This authorization adds grammar rules, makes
;;; nupec-explanation class an item, and adds "NUPEC" to the title block.  Since
;;; rules can not be removed, once a G2 is authorized for NUPEC it can not be
;;; unauthorized.  This function does not test if NUPEC is already authorized
;;; since the nupec-authorized-p is set before this function is called.

;;; Other aspects of NUPEC G2 become "turned on" separate from this function when
;;; nupec-authorized-p is true.  For example, some menus test for this
;;; authorization condition when displaying choices.  Also, the creation of
;;; directory of names upon reset (during the authorization) is affected by some
;;; nupec-related slot-features.  Some attributes may be added to the directory
;;; depending on the slot features (do-not-put-in-attribute-tables nupec) and
;;; (do-not-put-in-attribute-tables not-nupec).  The first feature causes the the
;;; attribute not to be displayed in the table for NUPEC.  The second feature
;;; causes the attribute to not be displayed in the table for non-NUPEC.

(defun authorize-nupec ()
  
  ;; Add rules that make NUPEC features available to the user.
  (add-grammar-rules grammar-rules-to-add-for-nupec-after-authorization)
  
  
						       ; Need to add "NUPEC" to
						       ; the G2 title-block!!
						       ; cpm, 3/21/91.
  (when (not (search "NUPEC" (machine-model)))
    (setq machine-model-var
	  (format nil "~a NUPEC" (machine-model))))
  
;  (unless (class-is-subclass-of-item? (class-description 'nupec-explanation))
;    (make-nupec-system-class-be-an-item 'nupec-explanation))

  )





;;;; Extended Grace Period for OK Files



;;; `Extend-grace-period-on-ok-files-if-appropriate' is to be called after a
;;; failure to authorize to extend a grace period for 3.0 OK files, for a
;;; limited time, and returns true if it results in g2 being authorized.
;;; Otherwise, nil.
;;;
;;; If users do get authorized via this extension of a grace period, and this is
;;; taking place during the OK initializations phase of starting up a G@, then a
;;; message is shown them after the clearing of the KB, warning them that they
;;; must upgrade their OK files.
;;;
;;; This will no longer be done after 1/25/95 in images generated from these
;;; sources.  This is to be removed from the sources completely no later than
;;; 1/25/95.  (MHD 12/21/94)

;; Commented out 5/3/96 -- See note above.  (also wanted to get rid of a
;; call to get-universal-time during translation).
;(defun extend-grace-period-on-ok-files-if-appropriate (ok)
;  (when (and loading-kb-p
;	     (= chaining-refresh-version 4)
;	     (system-version-greater-p
;	       4-0-version
;	       system-version-from-kb-being-read)
;	     (< (get-universal-time)
;		(encode-universal-time 0 0 0 25 1 95)))
;    (setq chaining-refresh-version 3)
;    (setq keytab1 (choose-keytab))
;    (setq chaining-refresh-list (choose-chaining-refresh-list))
;    (reformat-line-from-left ok)
;    (when (g2-authorized-p)
;      (make-message-regarding-ok-file
;	(tformat-text-string
;	  "Your machine has been authorized from the OK file ~s ~
;             using G2 3.0 codes.  These will only be acceptable in this ~
;             G2 4.0 Beta version during a brief period in ~
;             time (until Jan. 25, 1994). Please obtain new ~
;             authorization codes."
;	  name-text-string-for-kb-being-read))
;      t)))





;;; In light of Christophe's rapid discovery attempt to break
;;; the authorization system: He started with (who-calls 'syscall).
;;; This brought him immeidtaely to the function ok-if-possible (since renamed). 
;;; A more obscure way is to use a funcall, and make sure that none of the arguments
;;; of the funcall can be statically linked to the call itself. This is done by
;;; putting the arguments into lists, then creating other lists that tail into
;;; this list. There is non-locality of code, and even disassembling is not likely
;;; to reveal how the suspisious argument or keyword is associated with the location
;;; of the call. 

;;; The good hacker can still cause trouble if he can cause the system to hang when
;;; the get-local-machine-id is done. In G2, this still will not lead to where
;;; the real encoding is done, but it would allow the user to return a machine id
;;; from some other authorization. This is hard to prevent. 

;;; ML, 23 September, 1989





;;;; Warning system for license about to expire. 


;;; warn-of-license-expiration (macro - obvious-name) is called every 200
;;; gensym seconds from take-actions-at-start-of-clock-tick. It is not part
;;; of the ultra secure system. It posts warnings that the license is about
;;; to expire, only for licenses with expirations. The warnings come up
;;; once a week for one week prior to expiration, hourly on the day of
;;; expiration. They come up only while running G2. If the system has
;;; not been run for a while, a message will come up promptly if it is overdue.

(defvar daily-countdown 7)
(defvar hourly-countdown 24)
(defvar hour-of-last-message -1)

(defvar operative-task-list (list 3 7 12))
(defvar smoothed-subsecond-adjustment (cons 4 (cons 5 (cddr operative-task-list))))


(defmacro warn-of-license-expiration ()
  '(loop with expiration? = (fourth end-of-recovery-list)
	 with license-expiration? = 	       
	   (cond
	     ((null expiration?) nil)
	     ((authorization-is-interval-p expiration?)
	      (nth-value 1 (decode-authorization-interval expiration?)))
	     (t expiration?))
	with this-hour = 
	  (multiple-value-bind (second minute hour)
	      (get-decoded-real-time)
	    (declare (ignore second minute))
	    hour)
	with today = (get-universal-date)
	with days-left = (if (and license-expiration? (typep license-expiration? 'fixnum))
			     (-f license-expiration? (get-universal-date))
			     100000)	
	with expired = nil
	with will-expire = nil
	with post-dated = nil
	with not-authorized = nil
	with post-message? = nil
	with authorized-package-list = (third local-recovery-list)
	for (existing-package . nil) in control-sequence-record
	for (package-name nil nil nil start-date? end-date?) =
	    (assq existing-package authorized-package-list)
	doing
    (cond
      ((null package-name)
       (setq not-authorized (gensym-cons existing-package not-authorized)))

      ((null start-date?))
       
      ((<f end-date? today)
       (setq expired (gensym-cons existing-package expired)))

      ((<f today start-date?)
       (setq post-dated (gensym-cons existing-package post-dated)))

      ((and end-date? (<f end-date? (+f today 7)))
       (setq will-expire (gensym-cons existing-package will-expire))
       (setq days-left (minf days-left (-f end-date? today)))))

    finally
      (cond
	;; If already expired, post hourly messages.
	((and (or
		not-authorized
		expired
		post-dated
		(and (<=f daily-countdown 0)
		     (<=f hourly-countdown 0)))
	      (/=f this-hour hour-of-last-message))
	 (setq hour-of-last-message this-hour)
	 (setq post-message? t))

	;; last day, post hourly messages
	((and (<=f daily-countdown 0)
	      (>f hourly-countdown 0))	 
	 (let ((hours-left
		 (-f 23 this-hour)))
	   (when (>f hourly-countdown hours-left)
	     (setq hourly-countdown hours-left)
	     (setq post-message? t))))
	     
	;; last week, post daily messages
	((>f daily-countdown days-left)
	 (setq daily-countdown days-left)
	 (setq post-message? t)))

      (when post-message?
	(post-prominent-notification
	  (twith-output-to-text-string

	    (when license-expiration?
	      (when (<f license-expiration? today)
		(tformat (license-on-this-machine-has-expired-ok-message))) ;#??

	      (when (=f license-expiration? today)
		(tformat (licence-on-this-machine-expires-today-ok-message))) ;#??

	      (when (<f today license-expiration? (+f today 7))
;		(twrite (licence-on-this-machine-expires-this-week-ok-message
;			  license-expiration?))
		;; Using the original until (at least some) arguments are included:
		(twrite "The license to use G2 on this machine expires on ")
		(multiple-value-bind (day month year)
		    (decode-universal-date license-expiration?)
		  (print-decoded-date day month year))
		(tformat ".~%G2 will not run after this date.~%~%")))
	    
	    (when not-authorized
;	      (tformat (packages-not-authorized-ok-message not-authorized))
	      (tformat
		"The following application packages are not authorized:~%")
	      (print-list-without-message not-authorized))
	    
	    (when expired
;	      (tformat (packages-with-expired-authorizations-ok-message expired))
	      (tformat    
		"The following application packages have expired authorizations:~%")
	      (print-list-without-message expired))
    
	    (when post-dated
;	      (tformat (packages-with-further-authorizations-ok-message post-dated))
	      (tformat
		"The following application packages have authorizations with future start dates:~%")
	      (print-list-without-message post-dated))

	    (when will-expire
;	      (tformat (packages-with-authorizations-expiring-in-a-week will-expire))
	      (print-list-without-message will-expire)
	      (tformat
		"The following application packages have authorizations that will expire within a week:~%"))
	      )))

    (reclaim-gensym-list not-authorized)
    (reclaim-gensym-list expired)
    (reclaim-gensym-list post-dated)
    (reclaim-gensym-list will-expire)
    ))






(defun print-message-with-list (list text)
  (twrite text)
  (print-list-without-message list))

(defun print-list-without-message (list)
  (loop with authorizations = (third local-recovery-list)
	for package-name in list
	for authorization? = (assq package-name authorizations)
	for start-date? = (fifth authorization?)
	for end-date? = (sixth authorization?) doing
    (tformat "~(~a~)      " package-name)
    (when start-date?
      (twrite "Start date: ")
      (multiple-value-bind (d m y)
	  (decode-universal-date start-date?)
	(print-decoded-date d m y))
      (tformat "      End date: ")
      (multiple-value-bind (d m y)
	  (decode-universal-date end-date?)
	(print-decoded-date d m y)))
    (tformat "~%~%")))





;;; warn-upon-start-or-resume posts a prominent notification if start, restart
;;; or resume has been selected, but it is not ok to run g2. These menu choices
;;; are offered if the machine has been authorized at any time. If
;;; warn-upon-start-or-resume is called, it is the case that g2-authorized-p
;;; but not ok-to-run-g2?. The reason must be that either the license to run
;;; g2 has expired, some package has not been authorized, or some package
;;; authorization has expired. The message deals with these three cases. It must
;;; not be called if ok-to-run-g2?, or if the machine has never been authorized,
;;; becasue it could post an empty message.

(defun warn-upon-start-or-resume ()
  (post-prominent-notification
     (twith-output-to-text-string
       (loop with expiration? = (fourth end-of-recovery-list)
	     with today = (get-universal-date)
	     with license-expiration? = 	       
	       (cond
		 ((null expiration?) nil)
		 ((authorization-is-interval-p expiration?)
		  (nth-value 1 (decode-authorization-interval expiration?)))
		 (t expiration?))
	     with days-left? =
	       (if (and license-expiration? (typep license-expiration? 'fixnum))
		 (-f license-expiration? today) nil)
	     with authorized-package-list = (third local-recovery-list)
	     for (existing-package . nil) in control-sequence-record
	     for (package-name nil nil nil start-date? end-date?) =
		 (assq existing-package authorized-package-list)
	     
		 initially
		 (if (and days-left? (<f days-left? 0))
		     (tformat "The license to use G2 on this machine has expired.~%"))
	     
	     doing
	 (when (null package-name)
	   (tformat "G2 is not licensed to run with the package ~(~a~).~%"
		    existing-package))
	 
	 (when (and package-name
		    end-date?
		    (<f end-date? today))
	   (tformat "The license to use the package ~(~a~) has expired.~%" existing-package))

	 (when (and package-name
		    start-date?
		    (>f start-date? today))
	   (tformat "The license to use the package ~(~a~) has not yet begun.~%" existing-package))


	     finally
	 (twrite "G2 cannot be started or resumed.")

	 ))))



;; Commented out by ML.  There are no callers and it uses bignums.
;(defun normalize-key (text-string)
;  (loop with expt = 0
;	with value = 0
;	for i from 0 to (- (lengthw text-string) 1)
;	for weight = (digit-char-pw (charw text-string i) 36) doing
;    (when weight
;      (setq value (+ value (* weight (expt 36 expt))))
;      (incf expt))
;    finally (return value)))

;; bless-them moved down in this file to prevent forward reference
;; to `permitted-user-modes'.  -pto 26jun90

















;;;; Users

;;; A `authorized-user' is an entity used to specify who is authorized to use G2.
;;; It usually appears only in ok files, and is not an item. 


;;; Properties of authorized-user needing to be implemented.

;;; 1. Can create an authorized-user and an ok from a workspace menu only
;;;    when in administrator mode, AND on a secure G2.

;;; 2. May not examine the table of an authorized-user except when in administrator mode.

;;; 3. Can the type-in of the password not print characters to the screen?
;;;    Note that the slot writer is blank.
;;;    How can we get the correct type-in confirmed?


(def-class (authorized-user entity)
  (user-password 0 vector-slot system (type user-password))
  (permitted-user-modes nil vector-slot system (type permitted-mode-list)) 
  ;; No claim is made for the artistic merit of the following:
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      20 42
      ((circle (10 0) (16 6) (10 12))
       (lines (10 12) (10 30))
       (lines (0 18) (20 18))
       (lines (0 42) (10 30) (20 42))))))



(def-grammar-category user-password ()
  (symbol))

(def-grammar-category permitted-mode-list ()
  (unreserved-symbol)
  ((unreserved-symbol '\, permitted-mode-list) (2 1 3)
   simplify-associative-operation))






;;; `User-password' is stored as a symbol, the value nil is stored for the
;;; default value.  See also password.

;;; When a the enter-user-settings-editor enters the editor on a slot of this
;;; type, it gets edited using the "blob font", a font in which all characters
;;; are indistinguishable black blobs.

;;; The `slot value writer for user-password' writes no text at all if the value
;;; is nil.  If the value is non-nil, it writes an asterisk (*) character for
;;; each character in the translation.  Note that in versions of G2 prior to 5.0
;;; Rev. 3 (as of Feb. 11, 1998), no text at all was written for any value of
;;; the slot.  Note that this assumes translation may only be either a symbol or
;;; a string.  (However, in practice, it may really only be a symbol.)

(def-slot-value-compiler user-password (translation)
  (if (eq translation 'none) nil translation))

(def-slot-value-writer user-password (translation)
  (unless (null translation)
    (loop repeat (lengthw (stringw translation))
	  do (twrite-char #.%\*))))



(def-slot-value-compiler permitted-mode-list (translation)
  (compile-symbol-list translation))


(def-slot-value-writer permitted-mode-list (value)
  (write-symbol-list value))






;;;; User Passwords

;;; `password-string' is a 32 character string representing a 128 bit number in
;;; hex.  That number is the MD5 hash of the user's name and password. For
;;; example (and hence as definition) for the user named ed, with the password
;;; "alphabet" we would form the text "user:ed:password:alphabet". Passwords
;;; and user names are coerced to lower case prior to doing this, so typeing
;;; AlphaBet is ok too.  The MD5 hash of that string is:
;;; "ceb6d1ab8509c56b72b52b968839e371" and that is what we store for the
;;; password-string.

;;; `md5-password' is used as a keyword in the window-parameter-plist, in
;;; 5.0 telewindow's sessions and G2 5.0 system-windows.  The key
;;; `password' is used by older Telewindows, and holds the fixnum encoded
;;; password.

(def-concept password-string)
(def-concept password)
(def-concept md5-password)



;;; `Set-user-password' is the Lisp-side of a programmatic way of doing what
;;; can also be done from the system-menu of a running G2. It seques into that
;;; code just at the point when the entries have been read out of the
;;; dialog box and are about to be checked for validity.
;;;
;;; Given that this is programmatic, for security reasons we include a built-in
;;; delay mechanism that prohibits calls to it from going through more frequently
;;; than a specified amount of time. Trying to do that results in an error
;;; symbol being passed back to signal that the call did not go through and
;;; no changes were made.

(defvar time-of-last-call-to-set-user-password
  (allocate-managed-float 0.0))

;; Note that this delay doesn't know who is trying to make the change.
;; As a result it's conceivable that someone could be blocked from
;; making their call just because someone else had made theirs within
;; the time window. It's unlikely, but it's logically possible.
;;   To forestall this possibility, the cap for the system-procedure 
;; (see system-procedures.kb) g2-set-user-password checks for the
;; specific error value that is returned if the calls are being made
;; too fast, and sits in a repeat loop with a delay until some other 
;; value is returned. This amounts to a backoff protocol that will
;; allow any number of simultaneously enqueued thread to eventually
;; be processed correctly, and keeps the users from having to know
;; that we have implemented this delaying protocol since they never
;; see its error symbol. 


(defparameter required-delay-between-calls-to-set-password
  (allocate-managed-float 1.0 ))  ; one second

(defun set-user-password (user clear-old-password clear-new-password)
  (with-temporary-gensym-float-creation set-user-password
    (let ((now (gensym-get-unix-time)))
      (cond
	((>e now
	     (+e (managed-float-value
		   time-of-last-call-to-set-user-password)
		 (managed-float-value
		   required-delay-between-calls-to-set-password)))
	 (mutate-managed-float-value
	   time-of-last-call-to-set-user-password
	   now)
	 (encode-and-check-password-change-information
	   user clear-old-password clear-new-password))
	(t
	 (values nil 'attempting-to-set-user-password-too-fast))))))







;;; The system procedure `g2-validate-user-and-password' and its middle
;;; man `valid-user-and-password-p' were cloned from the password setting
;;; routines above since they have to operate on the same principles:
;;; a delay loop to make them worthless to the unscrupulous user and
;;; a set of symbolic return values. To do the actual work we use the
;;; same function that checks password validity at login, and all the
;;; middle man does beyond the delay loop is convert from the clear
;;; to the encrypted form of the password.

(defun valid-user-and-password-p (user-name clear-password)
  (with-temporary-gensym-float-creation valid-user-and-password-p
    (let ((now (gensym-get-unix-time)))
      (cond
	((>e now
	     (+e (managed-float-value
		   time-of-last-call-to-set-user-password)
		 (managed-float-value
		   required-delay-between-calls-to-set-password)))
	 (mutate-managed-float-value
	   time-of-last-call-to-set-user-password
	   now)
	 (let ((encoded-password
		 (encode-password-via-md5 user-name clear-password nil)))
	   (validate-user-and-password user-name encoded-password)))
	(t
	 'attempting-to-set-user-password-too-fast)))))







;;;; Managing what users are authorized

;;; `Authorized-users-list' is an alist keyed by the symbolic name of the G2
;;; user.  This is filled when the g2 ok file is read in.  The structure entries is
;;; defined by the def-list-structure below


;;; There is only one entry per name. The list of
;;; modes in the entry should be kept in the same order as the list of modes in
;;; the authorized-user, because the first one is the default one. The list is
;;; outside of any KB. This entire system is not reference by a G2 which is not
;;; secure.
;;;
;;; `Updated-users-list' is a mimic of authorized-users-list that acts as a
;;; temporary store when OK files are read into an already running G2. It is
;;; read by `update-user-data' to manage the consolidation of any changes
;;; in user data.

(defvar authorized-users-list nil)

(defvar updated-users-list nil)

;; Note that in a multi-process LISP G2, authorized-users-list may be
;; mutated from one G2 and used by another G2. Consider the integrety of this.
;; ?? Is this datum still valid - ddm 10/16/99


(defun authorized-user-p (user-name)
  (assq user-name authorized-users-list))

(def-list-structure (user-OK-entry
		      (:constructor make-user-OK-entry)
		      (:consing-function gensym-cons))
    
    (user-entry-user-name ;; alist key
     user-entry-encoded-password
     user-entry-password-validity
     . user-entry-user-modes))
      



(defun users-authorized-password (user-name)
  (let ((authorization-entry?
	  (assq user-name authorized-users-list)))
    (when authorization-entry?
      (user-entry-encoded-password authorization-entry?))))



;;; `Enter-authorized-user' is used in two different contexts, differentiated
;;; by whether its original-p argument is T or Nil. We will either be entering
;;; data on the authorized users for the first time as part of the process
;;; of parsing the OK file that authorizes G2 to run (in which case the call
;;; is from read-user-ok-file-entry), or we will be updating the data on
;;; the authorized users (adding new users, removing those who have left,
;;; changing what modes they are authorized for) as part of a call to
;;; G2-update-user-data-from-ok-file that occurs while the G2 is running.

;; Both the list of user-modes and the password string are fresh copies made
;; just for the purpose of this call so we manage their reclaimation here.

(defun enter-authorized-user
       (name encoded-password user-modes password-validity original-p)
  (let ((entry? (if original-p
		    (assq name authorized-users-list)
		    (assq name updated-users-list))))
    
    (when (and password-validity
	       (=f password-validity 0)) ;; it's valid forever
      (setq password-validity nil))

    (cond
      (entry?
       ;; The data in later entries takes precedence over earlier ones
       (let ((password-string (user-entry-encoded-password entry?))
	     (earlier-user-modes (user-entry-user-modes entry?))
	     (password-validity (user-entry-password-validity entry?)))
	 (setf (user-entry-encoded-password entry?) encoded-password)
	 (setf (user-entry-user-modes entry?) user-modes)
	 (setf (user-entry-password-validity entry?) password-validity)
	 (reclaim-wide-string password-string)
	 (reclaim-gensym-list earlier-user-modes)))
      
      (t ;; Otherwise create a new entry.
       (let ((new-user-entry
	       (make-user-OK-entry
		 name encoded-password password-validity user-modes)))
	 (if original-p
	     (gensym-push new-user-entry authorized-users-list)
	     (gensym-push new-user-entry updated-users-list)))))))


(defun remove-authorized-user (user-name)
  (let ((entry? (assq user-name authorized-users-list)))
    (when entry?
      (setq authorized-users-list
	    (delete-gensym-element entry? authorized-users-list))
      (reclaim-gensym-list entry?)
      (propagate-changes-in-authorization-to-logged-in-users nil nil))))


;;; `Update-OK-user-data' is called by read-ok-file-just-for-updating-user-data.
;;; Its primary function is to replace the authorized-users-list with the
;;; update-users-list and reclaim it. It also must review the status of
;;; the users who are presently logged in given the changes that may have
;;; occurred. This includes users and user-modes that are no longer valid
;;; and also, just in case, any (momentarily) invalid logged-in users who
;;; are now valid (e.g. when the administrator need to correct a mistaken
;;; change to a user's validity).

(defun update-OK-user-data ()
  (let ((users-added nil)
	(users-with-additional-modes nil))
    (loop with old-entry
	  for entry in updated-users-list
	  do
      (cond
	;; new user?
	((not (setq old-entry (assq (user-entry-user-name entry)
				    authorized-users-list)))
	 (gensym-push (user-entry-user-name entry) users-added))
	(t
	 ;; has a known user gained any modes?
	 (loop with old-modes = (user-entry-user-modes old-entry)
	       for mode in (user-entry-user-modes entry)
	       when (not (memq mode old-modes))
		 do (gensym-push (user-entry-user-name entry)
				 users-with-additional-modes)))))	 

    ;; switch over
    (let ((old-user-data authorized-users-list))
      (setq authorized-users-list updated-users-list)
      (setq updated-users-list nil)
      (loop for entry in old-user-data
	    as password-string = (user-entry-encoded-password entry)
	    as mode-list = (user-entry-user-modes entry)
	    do
	(reclaim-wide-string password-string)
	(reclaim-gensym-list mode-list))
      (reclaim-gensym-list old-user-data))

    ;; promulgate the changes
    (propagate-changes-in-authorization-to-logged-in-users
      users-added users-with-additional-modes)
    (reclaim-gensym-list users-added)
    (reclaim-gensym-list users-with-additional-modes)))







;;;; Checking User, Password and Mode in Secure G2s

;;; This code had been in CONTROLS as part of log-in-workstation. It has been
;;; pulled out so that it can also be used as part of authorizing T2 users.
;;; ddm 3/19/98


;;; `Validate-user-mode-for-use' returns nil if the user can be in
;;; this mode when the G2 is secure and a symbol naming the problem
;;; if s/he can't be. The symbols are the standard ones for login
;;; problems and internationalized in Controls.

(defun-simple validate-user-mode-for-user (user-name user-mode)
  (let ((valid-modes-for-user (user-entry-user-modes
				(assq user-name authorized-users-list)))
	(reason-we-failed?
	  (validate-as-possible-user-mode user-mode)))

    (unless reason-we-failed?
      (when (g2-secure-p)
	;; You have to be preaproved for this mode
	(unless (memq user-mode valid-modes-for-user)
	  (setq reason-we-failed? 'unauthorized-mode))
	(unless reason-we-failed?
	  ;; and it must be available in this kb unless the kb is empty.
	  ;; Since the directory is kb specific it is a simple test to
	  ;; make since any reference to a user-mode in a constraint
	  ;; statement will have caused the mode to be added to the
	  ;; directory
	  (unless (or (empty-kb-p)
		      (memq user-mode '(administrator))
		      (in-directory-of-names-p
			user-mode 'non-built-in-g2-user-mode))
	    (setq reason-we-failed? 'unknown-user-mode-in-current-kb)))))
      
      reason-we-failed?))

;;;
;;;
;;;
(def-gensym-c-function g2-check-authentification-ldap-in-c
                       (:fixnum-int "g2_check_authentification_ldap")
  ((:string user-name)
   (:string user-mode)))

(defun authentificate-user-ldap (user-name? user-mode?)
   (let ((reason-we-failed? nil))
     ;; All this is irrelevant unless the G2 is secure. If it
     ;; isn't we will always return nil, which the caller should
     ;; understand indicates that the values are valid.
     (when (g2-secure-p)
       ;; check that they've provided some values
       (cond
        ((null user-name?)
         (setq reason-we-failed? 'user-name-required))
        ((null user-mode?)
         (setq reason-we-failed? 'user-mode-required)))
       
       ;; lets try to start ldap authentication
       (unless reason-we-failed?
         (let ((ldap-result (g2-check-authentification-ldap-in-c user-name? user-mode?)))
           (cond ((= ldap-result 1) (setq reason-we-failed? 'unknown-user-or-bad-password))
                 ((= ldap-result 2) (setq reason-we-failed? 'unauthorized-mode))))))
     reason-we-failed? ))
 
(def-gensym-c-function g2-check-user-ldap-in-c
   (:fixnum-int "g2_check_user_ldap")
   ((:string default-user-name)
    (:string user-name)
    (:string encoded-password)))
 
(defun check-user-ldap (default-user-name? user-name? user-password?)
(let ((reason-we-failed? nil))
    ;; All this is irrelevant unless the G2 is secure. If it
    ;; isn't we will always return nil, which the caller should
    ;; understand indicates that the values are valid.
    (when (g2-secure-p)
      ;; check that they've provided some values
      (cond
	((null user-name?)
	 (setq reason-we-failed? 'user-name-required))
	((null user-password?)
	 (setq reason-we-failed? 'password-required)))
      
      ;; lets try to start ldap authentication
      (unless reason-we-failed?
        (let ((ldap-result (g2-check-user-ldap-in-c default-user-name? user-name? user-password?)))
          (if (= ldap-result 1) (setq reason-we-failed? 'unknown-user-or-bad-password)))))
    reason-we-failed? ))
 

(defun validate-user-and-password (user-name? encoded-password?
				   &optional nonce-from-t2? )
  (let ((reason-we-failed? nil))

    ;; All this is irrelevant unless the G2 is secure. If it
    ;; isn't we will always return nil, which the caller should
    ;; understand indicates that the values are valid.
    (when (g2-secure-p)
      ;; check that they've provided some values
      (cond
	((null user-name?)
	 (setq reason-we-failed? 'user-name-required))
	((null encoded-password?)
	 (setq reason-we-failed? 'password-required)))

      ;; The notion of a backdoor, e.g. valid-back-door-p had been
      ;; used here in situations where the password did not match.
      ;; It is no longer paid attention to in v5 because the situation
      ;; it controlled (access to the authorization KB by a g2-fluent
      ;; administrator) is no longer relevant given text-based oks.
      ;; I'm preserving it in case we ever want to revive this. ddm.
      #+obsolete
      (when (and encoded-user-password?
		 (valid-back-door-p encoded-password?))
	(setq in-thru-backdoor? t))

      ;; check the user name
      (unless reason-we-failed?
	(unless (authorized-user-p user-name?)
	  (setq reason-we-failed?
		'unknown-user-or-bad-password)))

      ;; Even though we can distinguish the case of not providing a known user
      ;; name from that of having a valid name but the wrong password we do not
      ;; distinguish them in what we tell the user because even that little bit
      ;; ('got the name right') would help an unscrupulous user. This is part of
      ;; standard security policy.

      ;; check the password
      (unless reason-we-failed?
	(let* ((hash-of-the-correct-password
		 (users-authorized-password user-name?))
	       (hash-with-nonce?
		 (when nonce-from-t2?
		   (hash-nonce-with-password-hash
		     nonce-from-t2? hash-of-the-correct-password))))
	  
	  (when (not (text-string=
		       encoded-password?
		       (or hash-with-nonce?
			   hash-of-the-correct-password)))

	    (setq reason-we-failed?
		  'unknown-user-or-bad-password))
	  
	  (when hash-with-nonce?
	    (reclaim-text-string hash-with-nonce?))))

      ;; check whether the password has expired
      (unless reason-we-failed?
	(setq reason-we-failed?
	      (password-still-valid? user-name?))))
    
    reason-we-failed? ))


	      

;;; Retrieving the authorized modes of a user. This is deployed for users
;;; in g2-authorized-modes-for-user.

(defun authorized-modes-for-user (user-name)
  (let ((user-entry? (assq user-name authorized-users-list)))
    (when user-entry?
      (user-entry-user-modes user-entry?))))







;;;; Password Decay

;;; < documentation > validate-user-and-password

(defun validity-of-users-password (user-name)
  (let ((user-entry? (assq user-name authorized-users-list)))
    (when user-entry?
      (user-entry-password-validity user-entry?))))

;; Called by change-users-password-decay-date
(defun set-validity-of-user-password (user-name value)
  (when (=f value 0)
    (setq value nil))
  (let ((user-entry? (assq user-name authorized-users-list)))
    (when user-entry?
      (setf (user-entry-password-validity user-entry?) value))))


;;; `Password-still-valid?' returns nil if the password is valid and an
;;; error-symbol if it is not. Note that not having a value for the password
;;; validity field (because it wasn't given in the OK file or hasn't been
;;; set since the G2 was loaded) implicitly means that the password is
;;; valid forever.

(defun password-still-valid? (user-name)
  (let ((expiration-date? (validity-of-users-password user-name))
	(today (get-universal-date)))
    (when expiration-date?
      (if (<f expiration-date? today)
	'password-has-expired
	nil))))











;;;; Managing users when the OK file is updated

;;; When the site manager updates the OK file to drop some person/s from the
;;; list of valid users, they will want to know if that person is presently
;;; logged in, so that they can take appropriate action (warn them, log them off
;;; immediately, etc.)  This facility gives them the information they need
;;; without presuming how they're going to use it -- we put the information into
;;; two slots in the g2-window. This is initiated by a call to
;;; `update-OK-user-data'.  This also covers the case where one update has
;;; removed a user/mode but a second update recinds that change.


(defun propagate-changes-in-authorization-to-logged-in-users
       (users-added users-with-additional-modes)
  (loop
    with users-modes
    for workstation in workstations-in-service
    as g2-window = (g2-window-for-this-workstation? workstation)
    as user = (g2-user-name-for-this-workstation? workstation)
    as mode = (g2-user-mode-for-this-workstation? workstation)
    when (eq (workstation-login-state workstation) 'logged-in)
      ;; ignore logged-out workstations or users in the process of logging in
      do
	#+development (assert (framep g2-window))
	(setq users-modes (user-entry-user-modes
			    (assq user authorized-users-list)))
	(cond
	  ;; user is not longer valid given the update to the OK file
	  ((not (assq user authorized-users-list))
	   (set-user-validity-of-g2-window g2-window nil)
	   (set-user-mode-validity-of-g2-window g2-window nil))

	  ;; This case (and the last) cover the situation where the
	  ;; administrator has (mistakenly) removed a user or their mode
	  ;; and is now reinstating them while they are still logged in.
	  ((memq user users-added)
	   (when (=f (g2-window-user-is-valid-function g2-window) falsity)
	     (set-user-validity-of-g2-window g2-window t))
	   (cond
	     ((memq mode users-modes)
	      (when (=f (g2-window-mode-is-valid-function g2-window) falsity)
		(set-user-mode-validity-of-g2-window g2-window t)))
	     (t  ;; user is valid (revalidated), but his mode isn't
	      (when (=f (g2-window-mode-is-valid-function g2-window) truth)
		(set-user-mode-validity-of-g2-window g2-window nil)))))

	  ;; user is ok, but his mode isn't
	  ((not (memq mode users-modes))
	   (set-user-mode-validity-of-g2-window g2-window nil))

	  ((memq user users-with-additional-modes)
	   (when (and (memq mode users-modes)
		      (=f (g2-window-mode-is-valid-function g2-window) falsity))
	     (set-user-mode-validity-of-g2-window g2-window t))))))



(defun set-user-validity-of-g2-window (g2-window t-or-nil)
  (change-slot-value g2-window 'g2-window-user-is-valid
		     (if t-or-nil truth falsity)))

(defun set-user-mode-validity-of-g2-window (g2-window t-or-nil)
  (change-slot-value g2-window 'g2-window-mode-is-valid
		     (if t-or-nil truth falsity)))









;;;; User Slot putters

;;; The code in this section is only relevant for object-based OK processing
;;; and is being kept around in the v5->v6 sources for the moment so that
;;; I can think about variations on these notions for any potential project
;;; involving sharpening the error messages from the login-dialog since it
;;; has the same slots.   ddm 1/9/98


(def-slot-putter permitted-user-modes (authorized-user value)
  (setf (permitted-user-modes authorized-user) value)
  (maintain-authorized-user authorized-user)
  value)


(def-slot-putter user-password (authorized-user value)
  (setf (user-password authorized-user) value)
  (maintain-authorized-user authorized-user)
  value)



;;; `Maintain-authorized-user' is called by slot-putting including name-or-names-for-frame
;;; of authorized-users. It acts only if the frame has at least one name, a password,
;;; and at least one mode. It does the following: 
;;;     For each name in name or names, it makes or finds an entry.
;;;        The password is made consistent with its current value.
;;;            The modes is made identical to the mode list.
;;; Removing a name from the authorized user list by editing is handled
;;; separately as described below.

;; This is only called from KB-based OK processing,
;; i.e. the two slot-putters below and by add-as-frame-with-name.
;; At some point this sort of stuff should probably be reaped.  ddm 1/9/98

(defun maintain-authorized-user (authorized-user)
  (let ((names (name-or-names-for-frame authorized-user))
	(encoded-password (user-password authorized-user))
	(modes (permitted-user-modes authorized-user)))
    names encoded-password modes
;    (when (and names modes (/=f encoded-password 0))
;      (if (symbolp names)
;	  (maintain-authorized-user-1 names encoded-password modes)
;	  (loop for name in names do
;	    (maintain-authorized-user-1 name encoded-password modes))))
    ;; Maintain-authorized-users-1 has been flushed in favor of
    ;; enter-authorized-user. Keeping this function around now
    ;; just to avoid having to do the cleanup of all of this old,
    ;; object-centered code right now since some of it may be adapted
    ;; to new uses as the login procedure is abstracted and re-examined
    ;; in light of the need to control access to G2 from Nevada.
    ;; ddm 2/10/98
    ))



;; This is relevant to KB-based OK processing. It is called during
;; authorization by reformat-line-from-left.

(defun issue-mgs-notifications ()
  (cond
    ((null (loop for user being each class-instance of 'authorized-user
		 thereis (and (permitted-user-modes user)
			      (name-or-names-for-frame user)
			      (user-password user))))
     ;; If there are no authorized users, say so as a warning:
     (notify-user
       (should-create-users-and-then-save-ok-file-message-format-control-string)
       (should-create-users-and-then-save-ok-file-message-1)
       (should-create-users-and-then-save-ok-file-message-2)
       (should-create-users-and-then-save-ok-file-message-3)))
    (t
     ;; if there are some users, say they can add users now, and then
     ;; save.
     (notify-user
       (can-create-additional-users-and-then-save-ok-file-message-format-control-string)
       (can-create-additional-users-and-then-save-ok-file-message-1)
       (can-create-additional-users-and-then-save-ok-file-message-2)))))





;;;; Back Door Entry to Secure G2.



;;; Find-back-door (not part of G2 code) maps any string (presumed to be
;;; a local machine id) into another string in a non-predicatble way.
;;; Its value is always of the for "KDFdddddddd" where the ds are digits
;;; and the length is 11.  The value is called a backdoor password.

;; The definition of find-back-door from NUMBERS is provided for reference,
;; embedded in the comment that follows (with two ;'s).  The working copy
;; is in ma:>ml>numbers.lisp.

;; From NUMBERS:
;; 
;;  (defun find-back-door (key-as-string)
;;    (loop with first-key = (gensym-string-hash
;;                             (concatenate 'string key-as-string mm4 key-as-string)
;;                             mm1)
;;          with second-key = (logior
;;                              (ash first-key -12)
;;                              (ash (logand first-key 4095) 12))
;;          with reduced-key = (inner-multiply
;;                               (logxor second-key mm3) second-key)
;;          with xx = (logxor reduced-key mm2)
;;          with result = "KDF"
;;          for i from 1 to 8
;;          doing
;;      (setq result (concatenate 'string result (format nil "~d" (logand xx 7))))
;;      (setq xx (ash xx -3))
;;          finally
;;            (return result)))



;;; (valid-back-door-p encoded-password) gets the local machine id on line,
;;; and is true if encoded-password corresponds to the site manager password
;;; for this machine id.  Encoded-password must be a fixnum.
						       
(defparameter mm1 16776379)
(defparameter mm2 12184771)
(defparameter mm3 3720484)
(defparameter mm4 "g0934sd")


;; Should be a macro!

(defun valid-back-door-p (encoded-password)
  (let ((string-to-encode
	  (twith-output-to-text-string
	    (loop with first-key
		    = (let* ((key-as-string
			       (get-local-machine-id-as-text-string-online))
			     (string-to-hash
			       (twith-output-to-text-string
				 (twrite-string key-as-string)
				 (twrite-string mm4)
				 (twrite-string key-as-string))))
			(prog1
			  (text-string-hash-with-modulus string-to-hash mm1)
			  (reclaim-text-string key-as-string)
			  (reclaim-text-string string-to-hash)))
		  with second-key
		    = (logiorf
			(ashf first-key -12)
			(ashf (logandf first-key 4095) 12))
		  with reduced-key
		    = (inner-multiply
			(logxorf second-key mm3)
			second-key)
		  with xx = (logxorf reduced-key mm2)
		  initially (twrite-string "KDF")
		  for i from 1 to 8
		  do (twrite-fixnum (logandf xx 7))
		     (setq xx (ashf xx -3))))))
  (prog1
    (=f encoded-password
	(encode-user-password-string string-to-encode))
    (reclaim-text-string string-to-encode))))





;; To do:

;; 1. Control the production and editing of authorized-users. DONE! MHD

;; 2. Add secure-system to the ok. Loading it should make
;;    a system secure. DONE!
;;    It should be visible only when system is secure. (DONE!. MHD.)

;; 3. For a non-secure system, all permissions succeed. DONE!

;; 4. Have the site-manager method of entering a secure system. DONE!

;; 5. MHD: Interface for login and mode change. DONE!

;; 6. Is there a way to protect against importing an OK with a secure
;;    system???

;; 7. Rename OK to be G2 (the file) for Beta 2 and forward. DONE! MHD.













;;;; Package Authorization

;;; ... Overview Documentation




;;; Encoding Schema

;;; Let:

;;; 	Q1,Q2 = X(package-name)			      	(1)
;;;	Q3,Q4 = Y(package-name)			  	(2)
;;;  	Q5,Q6 = Z(machine-id)				(3)
			
;;;	C1,C2 = R(Q1,Q2,Q5,Q6,start-date,end-date) 	(4)
;;;	C3    = S(Q3,Q4,Q5,Q6)				(5)

;;; The Ci are the authorizing codes for a module. They are determined
;;; by the package-name and the machine id.

;;; The Qi and the Ci are fixnums on all platforms. package-name and
;;; machine-id are arbitrary strings. Functions X,Y and Z are insensitive
;;; to case of letters, and to the presence of non-alphanumeric characters.

;;; The five functions are "obscure" in the sense that no reasonable collection
;;; of examples is useful for computing the function for new arguments.

;;; The Gensym proprietary authorizing module computes the Ci given the
;;; package-name and the machine-id using the five equations above.

;;; The package-specific authorizing module, which may be given to the
;;; author of the module who is not Gensym, computes the Ci from the last
;;; three equations only. It requires a small accompanying file containing
;;; Q1-4 for a particular package, which it reads initially.  

;;; The five functions are readilly non-invertible, and "obscure" in the
;;; sense that having many instances of a function is not useful for computing
;;; its value for new arguments.

;;; The authorization is not compromized in general unless the would be
;;; breaker can compute X. It is not compromized for a specific package
;;; as long as Q1-Q4 for that package are not disclosed.

;;; The package-specific authorizing module computes the Qi givn Q1-Q4,
;;; and the machine id. The VAR who may be given this module is given
;;; Q1-4 for a particular package. He cannot use the module to authorize
;;; any other package unless the owner of that package gives him Q1-4 for
;;; that package. Only Gensym knows how to compute X.

;;; It is possible to write obscure C code such that it would be
;;; difficult even for a hacker to learn exactly what it does even given a
;;; C emulator.

;;; The first level of authorization checking usues only C3. It is invoked
;;; every time a workspace is loaded, or an authorization occurs to see
;;; if the authorization status has changed. It is not the most sensitive part
;;; of the code. It uses equations 2,3,5 to compute C3 from the machine-id and
;;; the module name to see if a module is authorized. It is important that it
;;; does not use the computation for X (equation 1).

;;; The second level of authorization checking uses codes C1 and C2. It is invoked
;;; only by check-ok to catch unauthorized users who have entered a correct C3.
;;; It uses equations 1,3 and 4, thus requiring the secret function X.









;;; Encoding Functions


;;; The heart of the obscure function computation is array churning.
;;; It is performed on an array of 8 8-bit bytes. It uses a random
;;; permutation of the numbers 0-255 as a key. The function mixin-class-attributes
;;; takes as arguments an array of 8 bytes, a key which is an array of
;;; length 256 containing a permutation of 0 - 255, and an index of how
;;; many churns to perform. The entire work is performed in local variables,
;;; and returned to the byte array when complete to optimize use of registers.
;;; The algorithm can be read from the code.





;;; The following macros are used only to generate open code in mixin-class-attributes.
;;; They reference local variables of mixin-class-attributes.


;;; Move the 8 bytes from mixin-class-attributes into local variables. 

(defmacro churn-set-locals ()
  `(progn
     ,@(loop for i from 0 to 7
	    for local in '(x0 x1 x2 x3 x4 x5 x6 x7)
	    collect
	      `(setq ,local (svref mixin-class-attributes ,i)))))


;;; Move the 8 bytes from the local variables into mixin-class-attributes when done.

(defmacro churn-set-array ()
  `(progn
     ,@(loop for i from 0 to 7
	    for local in '(x0 x1 x2 x3 x4 x5 x6 x7)
	    collect
	      `(setf (svref mixin-class-attributes ,i) ,local))))


;;; Replace each byte by substitution into the key.

(defmacro churn-subst-macro ()
  `(progn
     ,@(loop for local in '(x0 x1 x2 x3 x4 x5 x6 x7)
	     collect
	       `(setq ,local (svref churn-key ,local)))))


;;; Rotate the low order 4 bits of each local variable into the
;;; low order 4 bits of the preceeding variable in cyclic order.

(defmacro churn-rotate-down-macro ()
  `(progn
     (setq g2temp1 x0)
     ,@(loop for (x y . nil) on '(x0 x1 x2 x3 x4 x5 x6 x7)
	     collect
	       (if y
		   `(setq ,x (logiorf (logandf ,y 15) (logandf ,x 240)))
		   `(setq ,x (logiorf (logandf g2temp1 15) (logandf ,x 240)))))))


;;; Swaps the 4 low order bits of pairs of variables. The swaped pairs
;;; are V(i) and V(i+4), for i = 0 to 3.

(defmacro churn-swap-fours-macro ()
  `(progn
     ,@(loop for x in '(x0 x1 x2 x3)
	    for y in '(x4 x5 x6 x7)
	    nconc
	      `((setq g2temp1 (logandf ,x 15))
		(setq g2temp2 (logandf ,y 15))
		(setq ,x (logiorf (logandf ,x 240) g2temp2))
		(setq ,y (logiorf (logandf ,y 240) g2temp1))))))



(defun mixin-class-attributes (mixin-class-attributes churn-key n)
  (let (g2temp1 g2temp2 x0 x1 x2 x3 x4 x5 x6 x7)
    (churn-set-locals)

    (loop for i from 1 to n doing
      (churn-subst-macro)
      (churn-rotate-down-macro)
      (churn-subst-macro)
      (churn-swap-fours-macro)
      )

    (churn-set-array)
    ))



;;; font-feature-list is used to compute chuf-x, and roman-character-map is used to compute
;;; all others.

(defvar font-feature-list	
  (copy-optimized-constant
    #(165 192 60 104 72 215 66 34 226 207 53 27 55 15 167 68 92 112 154
      120 173 88 214 143 107 103 101 176 234 49 13 70 240 206 37 54
      158 134 115 125 80 186 99 169 236 123 41 141 73 118 124 19 227
      135 113 85 117 65 87 4 1 178 81 188 238 195 245 247 127 71 16
      203 11 38 138 131 191 144 31 205 225 59 244 221 114 133 184 91
      56 69 51 61 9 116 89 145 224 179 142 229 2 146 241 228 20 249
      8 77 150 148 45 130 18 102 110 201 32 74 212 251 230 95 48 5
      149 171 250 220 33 98 63 163 209 182 47 42 23 242 126 177 216
      189 52 26 152 75 86 58 172 162 187 223 0 3 43 22 30 29 28 106
      183 218 67 44 159 174 122 7 39 151 24 211 200 10 252 83 14 82
      129 185 97 50 121 213 139 153 204 119 105 64 246 132 208 25
      232 161 111 198 231 248 202 17 157 79 62 168 197 180 239 36
      136 235 243 219 254 175 156 166 160 40 93 6 84 109 108 181 196
      222 90 199 253 194 190 128 147 21 170 193 96 137 237 155 94 217
      140 57 46 35 210 255 100 76 233 164 78 12)))



(defvar roman-character-map	
  (copy-optimized-constant
    #(222 90 199 253 194 190 128 147 21 170 193 96 137 237 155 94 217
      192 60 104 72 215 66 34 226 207 53 27 55 15 167 68 92 112 154
      120 173 88 214 143 107 103 101 176 234 49 13 70 240 206 37 54
      135 113 85 117 65 87 4 1 178 81 188 238 195 245 247 127 71 16
      203 11 38 138 131 191 144 31 205 225 59 244 221 114 133 184 91
      56 69 51 61 9 116 89 145 224 179 142 229 2 146 241 228 20 249
      8 77 150 148 45 130 18 102 110 201 32 74 212 251 230 95 48 5
      149 171 250 220 33 98 63 163 209 182 47 42 23 242 126 177 216
      189 52 26 152 75 86 58 172 162 187 223 0 3 43 22 30 29 28 106
      183 218 67 44 159 174 122 7 39 151 24 211 200 10 252 83 14 82
      158 134 115 125 80 186 99 169 236 123 41 141 73 118 124 19 227
      129 185 97 50 121 213 139 153 204 119 105 64 246 132 208 25
      232 161 111 198 231 248 202 17 157 79 62 168 197 180 239 36
      136 235 243 219 254 175 156 166 160 40 93 6 84 109 108 181 196
      140 57 46 35 210 255 100 76 233 164 78 12 165)))





(defvar feature-blt (make-array 8))




(defmacro load-randoms-into-churn-array ()
  `(progn
     ,@(loop for i from 0
	     for random in '(r0 r1 r2 r3 r4 r5 r6 r7) collect
	     `(setf (svref array ,i) ,random))))



(defun implant-string-into-array (string array r0 r1 r2 r3 r4 r5 r6 r7)
  (load-randoms-into-churn-array)

  (loop with j = 0
	for i from 0 to (-f (lengthw string) 1)
	for weight = (digit-char-pw (charw string i) 36) doing
    (when weight
      (setf (svref array (modf j 8))
	    (logxorf (svref array (modf j 8)) weight))
      (incf j))))




(defun color-match-p (package-name)
  (let ((array feature-blt))

    (implant-string-into-array package-name array
			       171 23 221 225 204 37 208 167)

    (mixin-class-attributes array font-feature-list 5)

    (values
      (logxorf (svref array 1)
	      (ashf (svref array 2) 5)
	      (ashf (svref array 3) 11))
      (logxorf (svref array 4)
	      (ashf (svref array 5) 5)
	      (ashf (svref array 6) 11)))))


(defun eval-sequence-2 (package-name)
  (let ((array feature-blt))

    (implant-string-into-array package-name array 
			       155 87 96 155 224 43 4 175)

    (mixin-class-attributes array roman-character-map 5)

    (values
      (logxorf (svref array 1)
	      (ashf (svref array 2) 5)
	      (ashf (svref array 3) 11))
      (logxorf (svref array 4)
	      (ashf (svref array 5) 5)
	      (ashf (svref array 6) 11)))))


(defun button-down-handler (machine-id)
  (let ((array feature-blt))

    (implant-string-into-array machine-id array 
			       9 184 41 90 71 250 97 167)

    (mixin-class-attributes array roman-character-map 5)

    (values
      (logxorf (svref array 1)
	      (ashf (svref array 2) 5)
	      (ashf (svref array 3) 11))
      (logxorf (svref array 4)
	      (ashf (svref array 5) 5)
	      (ashf (svref array 6) 11)))))


(defun procedure-recursive (q1 q2 q3 q4 start-date end-date)
  (let ((array feature-blt))    
    (setf (svref array 0)
	  (logxorf 83
		  (logandf q1 77)
		  (logandf start-date 77)))
    (setf (svref array 1)
	  (logxorf 211
		  (logandf (ashf q1 -8) 77)
		  (ashf q1 -13)
		  (logandf (ashf start-date -8) 77)))    
    (setf (svref array 2)
	  (logxorf 219
		  (logandf q2 77)
		  (logandf (ashf start-date -13) 77)))
    (setf (svref array 3)
	  (logxorf 63
		  (logandf (ashf q2 -8) 77)
		  (ashf q1 -13)
		  (logandf end-date 77)))    
    (setf (svref array 4)
	  (logxorf 143
		  (logandf q3 77)
		  (logandf (ashf end-date -8) 77)))
    (setf (svref array 5)
	  (logxorf 30
		  (logandf (ashf q1 -8) 77)
		  (ashf q3 -13)
		  (logandf (ashf end-date -13) 77)))    
    (setf (svref array 6)
	  (logxorf 241
		  (logandf q4 77)))
    (setf (svref array 7)
	  (logxorf 253
		  (logandf (ash q4 -8) 77)
		  (ashf q1 -13)))    
    (mixin-class-attributes array roman-character-map 5)    
    (values
      (logxorf (svref array 1)
	      (ashf (svref array 2) 5)
	      (ashf (svref array 3) 11))
      (logxorf (svref array 4)
	      (ashf (svref array 5) 5)
	      (ashf (svref array 6) 11)))))




(defun reverse-list-search (q1 q2 q3 q4 c1 c2 start-date end-date)
  (let ((array feature-blt))    
    (setf (svref array 0)
	  (logxorf 89
		  (logandf q1 77)
		  (logandf c1 77)
		  (logandf start-date 77)))
    (setf (svref array 1)
	  (logxorf 195
		  (logandf (ashf q1 -8) 77)
		  (ashf q1 -13)
		  (logandf (ashf c1 -8) 77)
		  (logandf (ashf start-date -8) 77)))
    (setf (svref array 2)
	  (logxorf 4
		  (logandf q2 77)
		  (logandf (ashf c1 -13) 77)
		  (logandf (ashf start-date -13) 77)))
    (setf (svref array 3)
	  (logxorf 193
		  (logandf (ashf q2 -8) 77)
		  (ashf q1 -13)
		  (logandf c2 77)
		  (logandf end-date 77)))    
    (setf (svref array 4)
	  (logxorf 18
		  (logandf q3 77)
		  (logandf (ashf c2 -8) 77)
		  (logandf (ashf end-date -8) 77)))
    (setf (svref array 5)
	  (logxorf 158
		  (logandf (ashf q1 -8) 77)
		  (ashf q3 -13)
		  (logandf (ashf c2 -13) 77)
		  (logandf (ashf end-date -13) 77)))    
    (setf (svref array 6)
	  (logxorf 119
		  (logandf q4 77)))
    (setf (svref array 7)
	  (logxorf 105
		  (logandf (ash q4 -8) 77)
		  (ashf q1 -13)))    
    (mixin-class-attributes array roman-character-map 5)    

    (logxor (svref array 3)
	    (ashf (svref array 4) 5)
	    (ashf (svref array 5) 11))))




;;; Grammar and slot putter for proprietary-package of kb-workspace.


(add-grammar-rules
  '((proprietary-package 'none 1 nil-function)
    (proprietary-package ('not 'proprietary) (nil))
    (proprietary-package ('potentially package) (2))
    ))

;;; GENSYMCID-1823 add write-proprietary-package-while-saving-xml-kb 
;;; to control slot-value-writer for proprietary-package. prevent to
;;; save "private" to XML format KB

(defvar write-proprietary-package-while-saving-xml-kb nil)

(def-slot-value-writer proprietary-package (value)
  (cond
    ((null value) (twrite "none"))
    ((symbolp value)
     (if write-proprietary-package-while-saving-xml-kb 
       (tformat "potentially ~(~a~)" value)
       (tformat "~(~a~)" value)))
    ((null (car value)) (twrite "not proprietary"))
    (t (tformat "potentially ~(~a~)" (car value)))))









;;; The slot should not be editable unless in application preparation mode,
;;; and the value is not a non-null symbol. Needs special editor enforcement.
;;; Thus once proprietary, always proprietary.

;; make proprietary now, a main menu misc. menu choice, iterates over
;; the kb-workspace hierarchy, except for non-savable ones.
;; (1) A package name gets inherited as long as NONE is encountered. (2)
;; POTENTIALLY gets changed to the package name, (2) (nil) gets changed to NIL.

;; Remember to put a describe feature in for workspaces.

;; A list of packages with the number of prop. workspaces must be maintained.



;; There is a parameter that gets saved which must tally with the summation
;; of proprietary workspaces and non-proprietary ones.






(def-substitution-macro add-proprietary-kb-workspace (package-name)
  (unless (eq package-name 'private)
    (let ((workspace-count? (assq package-name control-sequence-record)))
      (if workspace-count?
	  (incff (cdr workspace-count?))
	  (setq control-sequence-record
		(gensym-cons (gensym-cons package-name 1) control-sequence-record))))))

(def-substitution-macro remove-proprietary-kb-workspace (package-name)
  (unless (eq package-name 'private)
    (loop for trailing-cons = nil then leading-cons
	  for leading-cons on control-sequence-record
	  for workspace-count = (car leading-cons)
	  until (eq (caar leading-cons) package-name)
	  finally
	    (cond
	      #+development
	      ((null workspace-count) (cerror "continue" "control-sequence-record"))
	      ((=f 0 (decff (cdr workspace-count)))
	       (if trailing-cons
		   (setf (cdr trailing-cons) (cdr leading-cons))
		   (setq control-sequence-record (cdr leading-cons)))
	       (reclaim-gensym-cons leading-cons)
	       (reclaim-gensym-cons workspace-count))))))


(def-slot-putter proprietary-package (kb-workspace new-value)
  (let ((old-value (proprietary-package kb-workspace)))
    (cond
      ((and old-value (symbolp old-value))
       old-value)
      
      (t (setf (proprietary-package kb-workspace) new-value)
	 
	 (when (and new-value (symbolp new-value))
	   (add-proprietary-kb-workspace new-value))
	 
	 new-value))))



(def-class-method cleanup (kb-workspace)
  (let* ((deleting-subworkspace-p	; See Note 1 (MHD 3/28/00)
	   (or (parent-of-subworkspace? kb-workspace)
	       (eq kb-workspace subworkspace-currently-being-deleted?)))
	 (module-if-relevant?
	   (if deleting-subworkspace-p nil (module-this-is-part-of? kb-workspace))))
    (when module-if-relevant?
      ;; send notification before reclaiming icp-object-map
      (inform-ui-client-interfaces-of-top-level-workspace-assignment-change
	kb-workspace nil module-if-relevant?))
    (funcall-superior-method kb-workspace)
    (let ((value (proprietary-package kb-workspace)))
      (when (and value (symbolp value))
	(remove-proprietary-kb-workspace value)
	(setf (proprietary-package kb-workspace) nil)))
    (cond				; See Note 2 (MHD 4/28/91)
      (module-if-relevant?
       (change-slot-value kb-workspace 'module-this-is-part-of? nil))
      ((not deleting-subworkspace-p)
       (update-module-related-frame-notes-for-all-workspaces)))))

;; Note 1: On detecting if this is a subworkspace being deleted: if you call
;; delete-frame on a subworkspace itself, e.g., via delete on its menu, the
;; parent-of-subworkspace?  slot is non-nil here.  If you call delete-frame on a
;; subworkspace indirectly, e.g., by deleting the parent item, the
;; parent-of-subworkspace? slot is nil here, but to
;; subworkspace-currently-being-deleted?, since the reclaimer for subworkspaces
;; has created this binding before calling delete-frame on this workspace. Note
;; that in previous releases, this code did not propertly detect
;; deleting-subworkspace-p in indirect case (going through the reclaimer for
;; subworkspaces).  (MHD 4/28/00)

;; Note 2: Cleanup for modules:
;; -- only needed if this is a top-level kb-workspace
;; -- this assumes its being called after the frame-being-delete
;;    flag has been set on kb-workspace, but before kb-workspace's
;;    slots have been reclaimed or modified generally
;; -- the following calls the slot putter to set the module slot to
;;    nil if that slot has a non-nil value, which will result in the
;;    update-module-related-... function being called; otherwise,
;;    this has to call that function directly iff there is a
;;    top-level module  (MHD 12/10/91)




;;; Make-proprietary-Now

;;; make-proprietary-now examines every kb-workspace in a top down
;;; manner. Before this is done, there may be four types of values for
;;; proprietary-workspace?:
;;;    	nil				NONE
;;;    	package-name			package-name
;;;    	(package-name)			POTENTIALLY package-name
;;;    	(NIL)				NOT PROPRIETARY
;;; After this pass, only the first two are possible. The following
;;; transformations are performed:
;;; (1) NONE 			   If there is a superior workspace and it has 
;;;  				   a package-name, then that package-name
;;;  				   is inherited.
;;; (2) package-name		   May never be changed.
;;; (3) POTENTIALLY package-name   package-name
;;; (4) NOT PROPRIETARY		   NOT PROPRIETARY

;; In version 3.0 the fourth rewrite was to nil, that was stupid. - ben 1/24/94

(defun make-proprietary-now ()
  (cond
    (system-is-running
     (notify-user
       "You cannot make workspaces proprietary while the system is running.  ~
        No workspaces were made proprietary."))
    (t
     (notify-user "Making workspaces proprietary now!")
     
     (identify-all-savable-kb-workspaces)
     
     (loop for kb-workspace being each class-instance of 'kb-workspace
	   doing
       (when (null (parent-of-subworkspace? kb-workspace))
	 (make-proprietary-now-1 kb-workspace nil)))

     (notify-user "Finished making workspaces proprietary."))))




(defun make-proprietary-now-1 (kb-workspace inherited-package?)
  (loop with marking-for-children?
	  = (let ((proprietary-package (proprietary-package kb-workspace)))
	      (cond
		;; aka NIL aka NONE
		((null proprietary-package)
		 (when inherited-package?
		   (change-slot-value kb-workspace
				      'proprietary-package inherited-package?))
		 (update-representations-of-slot-value kb-workspace
						       'proprietary-package)
		 inherited-package?)
		
		;; aka <package> aka <package> 
		((symbolp proprietary-package)
		 proprietary-package)
		
		;; aka (<package>) aka POTENTIALLY <package>
		((car proprietary-package)
		 
		 (change-slot-value kb-workspace
				    'proprietary-package
				    (car proprietary-package))
		 (update-representations-of-slot-value kb-workspace
						       'proprietary-package)
		 (proprietary-package kb-workspace))
		
		;; aka (NIL) aka NOT PROPRIETARY
		(t nil)))
	for subblock being each subblock of kb-workspace
	for subworkspace?
	    = (if (and (frame-of-class-p subblock 'entity)
		       (not (transient-or-unsavable-p subblock)))
		  (car (subworkspaces subblock)))
	when subworkspace? do
	    (make-proprietary-now-1 subworkspace? marking-for-children?)))









;;; (proprietary-p block) is true if block is proprietary.
;;; A block is proprietary if (1) it is a workspace
;;; whose proprietary-package slot is a symbol other than NIL, or
;;; (2) it is other than a workspace, and the workspace, if any,
;;; which is its closest ancestor is such. The value, if proprietary,
;;; is the package name.

;; Moved to DEBUG

;(defmacro proprietary-p (block)
;  `(in-order-p ,block))


(def-kb-specific-variable simulate-proprietary? sequences2 nil)


(defun in-order-p (block)
  (if simulate-proprietary?
      
      (loop for ancestor? = block then (parent ancestor?)
	    doing
	(cond
	  ((null ancestor?) (return nil))
	  ((frame-of-class-p ancestor? 'workspace)
	   (let ((proprietary-package (proprietary-package ancestor?)))
	     (cond
	       ((null proprietary-package)) 
	       ((symbolp proprietary-package) (return proprietary-package))
	       (t (return (car proprietary-package))))))))
      
      
      (loop for ancestor? = block then (parent ancestor?)
	    doing
	(cond
	  ((null ancestor?) (return nil))
	  ((frame-of-class-p ancestor? 'workspace)
	   (let ((proprietary-package (proprietary-package ancestor?)))
	     (cond
	       ((null proprietary-package)
		(unless (transient-p ancestor?)
		  (return nil)))
	       ((symbolp proprietary-package)
		(return proprietary-package))
	       ((and (consp proprietary-package)
		     (null (car proprietary-package)))
		(return nil))
	       ((transient-p ancestor?))
	       (t (return nil)))))))))





;;; Prevention of KB tampering to avoid authorization.

;; 1. Frame-flag recent-procedure-p

;; 2. Before saving, every procedure gets marked, and every ws gets
;;    check-summed as indicated below.

;; 3. Slot on kb-workspaces display-stack-priority saved. Its value
;;    is an integer or NIL. It should neverbe NIL if any procedure
;;    is recent.

;; 4. Display-stack-priority is a function of the the number of items
;;    on the workspace, and their positions. It looks very random.

;; 5. Post-loading function examines workspaces and computes this.
;;    If it is NIL and a recent procedure, or if it fails to compute correctly,
;;    then consider plant-seed!! First cerror to author for a week.








;;; normalize-kb-workspace (not a very informative name) is used to compute a
;;; checksum for a kb-workspace. This checksum is a pseudo-random function
;;; of the proprietary name if any, the number of objects, free-texts, and
;;; borderless-free-texts, and the number and exact positions of each procedure
;;; and statement which are subblocks of the kb-workspace. The checksum is
;;; placed in display-stack-priority of the kb-workspace, and is also
;;; returned as the value of the function. In addition to this,
;;; the frame flag recent-procedure is set for every procedure which is
;;; a subblock of the kb-workspace.

;;; A kb-workspace was normalized if the value of display-stack-priority before
;;; executing normalize-kb-workspace is the same as the value of
;;; normalize-kb-workspace. (After execution of normalize-kb-workspace, it certainly
;;; is normalized.)

;;; It is a requirement of the package security system that when a kb is saved
;;; in a normalized condition, then it will be read back in a normalized condition.
;;; The conditions required for this to be the case are, (1) display-stack-priority
;;; and recent-procedure are saved in a kb, (2) The coordinates of subblocks
;;; of a workspace are fixnums, (3) procedures and statements do not have their upper
;;; left corner moved during saving and during loading up to just before the
;;; post-loading functions are called, (4) free-texts, borderless-free-texts and
;;; objects are not deleted by save and restore. (Note that definitions may be
;;; deleted by merge.)

;;; Kb-worksapce are not kept in a normalized state during G2 operation.
;;; The entire KB will be normalized (1) immediately before a save, and (2)
;;; immediately before a load or a merge. Therefore, immeditaely after a load or 
;;; merge and before calling post-loading functions, every kb-workspace should be
;;; normalized except those that were saved before this software was implemented.
;;; In the latter case (1) display-stack-priority will be NIL, (2) no procedure should
;;; have recent-procedure-p be true, and (3) kb-security-implemented-p, a kb-flag,
;;; will have been false during the load.

;;; Immediately after a load or merge, the entire kb will be checked. If a kb-workspace
;;; is found to be unnormalized and (1) kb-security-implemented-p was true during the
;;; load or merge, or (2) some procedure on the workspace has recent-kb-p, or
;;; (3) display-stack-priority is other than NIL, this will be taken as evidence
;;; of tampering, and G2 will self-destruct (plant-seed).

;;; The method of computing display-stack-priority was changed on 11/25/91 in
;;; order to avoid certain fraigilities of the old system. A new slot with a
;;; (bogus) name display-index-point was introduced. It is given a somewhat
;;; randomized value the first time normalization occurs, and therefater keeps
;;; its value even when saved. This, together with the value of
;;; proprietary-package is sued to generate display-stack-priority. The
;;; subblocks are no longer involved in the computation in any repeatable way,
;;; which avoids interaction with various types of saving that might introduce
;;; bugs. Normalize-kb-workspace has a second argument which is t except while
;;; reading older kbs than those with kb-flags = 218
;;; (new-tampering-algorithm-p).

(defun normalize-kb-workspace (kb-workspace new-algorithm?)
  (let ((noting-changes-to-kb-p nil)
	display-index-point)

    ;; display-index-point is given a fixnum value which is never modified. It
    ;; is saved in KBs. The value is pseudo-random. This number is used as an
    ;; input to display-stack-priority, and its only requirement is to make that
    ;; computation unrepeatable.
    (when new-algorithm?
      (when (null (display-index-point kb-workspace))
	(setf (display-index-point kb-workspace)
	      (*f (modf (frame-hash kb-workspace) 3847)
		  (modf (+f (#-subblocks-v2 length
			     #+subblocks-v2 constant-queue-length
			     (subblocks kb-workspace))
			    (frame-serial-number-hash (current-frame-serial-number))
			    4079)
			4091))))
      (setq display-index-point (display-index-point kb-workspace)))
    
    (implant-string-into-array
      (let ((package? (proprietary-package kb-workspace)))
	(if (symbolp package?)
	    (symbol-name-text-string (proprietary-package kb-workspace))
	    '#w"abc"))
      feature-blt
      53 41 213 32 122 90 91 232)
    
    (cond
      (new-algorithm?
       (loop for subblock being each subblock of kb-workspace doing
	 (when (frame-of-class-p subblock 'procedure)
	   (set-recent-procedure subblock)))
       (setf (svref feature-blt 7)
	     (logxorf (svref feature-blt 7)
		      (logandf display-index-point 255)))
       (setf (svref feature-blt 6)
	     (logxorf (svref feature-blt 6)
		      (logandf (ashf display-index-point -8) 255)))
       (setf (svref feature-blt 6)
	     (logxorf (svref feature-blt 6)
		      (logandf (ashf display-index-point -8) 255))))
      (t
       (loop with i = 0
	     for subblock being each subblock of kb-workspace doing
	 
	 (when (and (not (transient-or-unsavable-p subblock))
		    (or (frame-of-class-p subblock 'statement)
			(frame-of-class-p subblock 'procedure)))
	   (when (frame-of-class-p subblock 'procedure)
	     (set-recent-procedure subblock))
	   
	   (setf (svref feature-blt i)
		 (logxorf (svref feature-blt i)
			  (logandf
			    (logxorf (left-edge-of-block subblock)
				     (top-edge-of-block subblock))
			    255)))      
	   
	   (setq i (modf (+f i 1) 8))))  
       
       (setf (svref feature-blt 1)
	     (logxorf (svref feature-blt 1)
		      (logandf
			(loop for subblock being each subblock of kb-workspace
			      counting
				(and (not (transient-or-unsavable-p subblock))
				     (or (frame-of-class-p subblock 'free-text)
					 (frame-of-class-p subblock 'borderless-free-text)
					 (frame-of-class-p subblock 'object))))
			255)))))
    
    (mixin-class-attributes feature-blt roman-character-map 5)
    
    (setf (display-stack-priority kb-workspace)
	  (+f (svref feature-blt 0)
	      (ashf (svref feature-blt 1) 8)
	      (ashf (svref feature-blt 2) 13)))))



(def-substitution-macro normalize-kb (new-algorithm?)
  (loop for ws being each class-instance of 'kb-workspace doing
    (normalize-kb-workspace ws new-algorithm?)))


(defmacro make-trouble (n)
  #+development
  `(cerror "continue" "Call ML. Authorization problem ~d." ,n)
  #-development
  (declare (ignore n))
  #-development
  ;; RETROFIT
  ;; The bombout mechanism for tampering now really works, and is
  ;; quite destructive. Note that this change is made along with a
  ;; change in read-kb that normalizes a kb-workspace created while
  ;; reading or merging.
  '(replace-format-using-equivalent-font 'variable)
  )

(def-substitution-macro check-for-tampered-kb
			(after-pkg-authorization? new-algorithm?)
  (loop for ws being each class-instance of 'kb-workspace
	for checksum? = (display-stack-priority ws) doing
    (cond
      (checksum?
       (if (/=f checksum? (normalize-kb-workspace ws new-algorithm?))
	   (make-trouble 1)))

      (after-pkg-authorization?
       (make-trouble 2))

      (t (loop for subblock being each subblock of ws doing
	   (if (and (frame-of-class-p subblock 'procedure)
		    (recent-procedure-p subblock))
	       (make-trouble 3)))))))

; abort-on-bad-kb






;; substitutions of names

;; 	churn-x		color-match-p
;; 	churn-y	 	eval-sequence-2
;;	churn-z		button-down-handler
;;	churn-r		procedure-recursive
;;	churn-s		reverse-list-search
;; 	churn-array	mixin-class-attributes

;; 	churn-key-1	font-feature-list
;; 	churn-key-2	roman-character-map

;; 	churn-box	feature-blt

;; Some of these are referenced in check-ok, a macro called in
;; CYCLES and BOOKS. All other changes are local.


;; proprietary-p is changed to a macro because its name is too obvious.
;; It is called too many times to justify expanding it in line.
;; Therefore, the macro is a call to a function called in-order-p.
;; Thus documentary correctness ius achieved.

;; proprietary-p is referenced in FACILITIES, MOVES, FILTERS and QUERIES.






;;; Modulo-string-hash computes a non-negative fixnum less than the modulus from
;;; the text-string.

(defun modulo-string-hash (text-string modulus)
  (loop with length = (lengthw text-string)
	with w = nil
	with i = 0
	with result = 0
	do (loop until (>=f i length)
		 do (when (setq w (digit-char-pw (charw text-string i) 36))
		      (incff i)
		      (return (values)))
		    (incff i)
		 finally
		   (setq w nil))
	when (null w)
	  do (return result)
	do (setq result
		 (modf (logxorf result
				(*f w 354673))
		       modulus))))


;;;; Text Based OK files.


;;; The next few sections implement an enhancment introduced in
;;; G2 version 5.0, i.e. text based ok files.  Prior to that date
;;; OK files were G2 knowledge bases.  These knowledge bases included
;;; frames of type OK, and PERSON.  These two frames continue to
;;; exist in development G2, but in production G2 they are obsolete.






;;;; Versions

;;; Things change. Over time we may add or delete fields from the
;;; the authorization data or change their types. At major version
;;; boundaries we switch to a new basis for the authorization codes.
;;; At each such point, older versions of G2 will not have the
;;; machinery to handle the new information.
;;;
;;; To accomodate this, every OK file includes a "version" attribute.  (If
;;; it does not, then implicitly we can infer that it is intended for one
;;; of the first three revisions of G2 version 5.0.) The G2 itself includes
;;; a variable, supported-ok-file-format-version, that indicates what
;;; version OK file it can handle. Versions are fixnums that increase over
;;; time.  (The same design is used for versions of the icp protocol. See
;;; platforms.)
;;;
;;; When a machine entry is read (see read-g2-ok-file-entity) the version
;;; is checked by ok-file-is-incompatible-with-image. If it returns nil
;;; the OK is valid to be processed by that G2. Non-nil indicates that
;;; there is something necessary attribute or property of the OK file that
;;; the image will be unable to understand and the reading of the OK file
;;; is aborted and the G2 is denied authorization. 

(defvar supported-ok-file-format-version 3)

;;; Version 1 is the original. It was back-fit into OK files generated
;;; by the siteok facility beginning with 5.1.

;;; Version 2 adds a new field: maximum-number-of-concurrent-floating-
;;; telewindows2-allowed. Codes generated for this version are incompatible
;;; with those of earlier versions.

;;; Version 3 added a new field to the user-entries: password-validity.
;;; This field is optional and has no effect on the codes or the
;;; well-formedness of the ok file.


(defun-simple ok-file-is-incompatible-with-image (version-number)
  (when (>f version-number supported-ok-file-format-version)
    (unless (=f version-number 3) ;; optional attribute
      :incompatible-ok-file)))









;;;; Writing out G2 Ok Files.

;;; Writing G2 OK files is a development only feature.
;;; it is used as part of the site OK file generateion
;;; tools used inhouse at Gensym.


(defmacro my-g2-stream-tformat (g2-stream format-string &rest format-args)
  (avoiding-variable-capture (g2-stream &aux result-string)
    `(let ((,result-string (tformat-text-string ,format-string ,@format-args)))
       (write-text-string-to-stream ,result-string ,g2-stream)
       (reclaim-text-string ,result-string))))


;;; `Write-current-ok-file' takes a KB file containing
;;; OK objects and Person Objects, and writes on a text
;;; file containing thost objects in the format used for
;;; text based ok files.

;; The only calling sites for this are from the +developement code for
;; generating the gensym site files, so it can inherit that contraint
;; and we can be more liberal with writing comments to standard output
;; to track its progress.
#+development
(defun write-current-ok-file (&optional (namestring "/home/bhyde/junk/test.ok"))
  (declare allowing-unwind)
  (g2-stream-with-open-stream (s namestring :direction :output)
    (when t (format t "~%Writing OK file ~a~%" namestring))
    (unless s
      (error "Problem opening ~a:~%   ~a" s (g2-stream-error-string)))	
    (macrolet ((emit (&rest args) `(my-G2-stream-tformat s ,@args)))
      ;; File header, and open bracket.
      (emit "begin g2-ok-file~%")

      ;; File header comments.
;      (emit "-- This was generated from a G2 Knowledge Base~%")

      (emit "~%~%file-format-version: ")
      (if ok-file-generation-for-version-5.1-or-greater-p
	  (emit "2;")
	  (emit "1;"))

      (block machines
	(unless (loop
		  for machine being each class-instance of 'ok
		  when (machine-id machine) do (return t))
	  (emit "-- There were no OK Objects in the KB.~%")
	  (return-from machines nil))
	(emit "~%~%-- Machine Authorizations~%")
	(loop
	  for machine being each class-instance of 'ok
	  as machine-id? = (machine-id machine)
	  as part-description-of-machine
	     = (gensym-list
		 'machine
		 'name (name-or-names-for-frame machine)
		 'machine-id (machine-id machine)
		 'authorized-products (authorized-products machine)
		 'expiration-date? (expiration-date? machine)
		 'authorization (gensym-list
				  (code-1 machine)
				  (code-2 machine)
				  (code-3 machine)
				  (code-4 machine)
				  (code-5 machine))
		 'make-g2-secure? (make-g2-secure? machine)
		 'authorized-kb-packages (authorized-kb-packages machine)
		 'number-of-processes-authorized
		 (number-of-processes-authorized machine)
		 'maximum-number-of-concurrent-floating-telewindows-allowed
		 (maximum-number-of-concurrent-floating-telewindows-allowed
		   machine)
		 )
	  when ok-file-generation-for-version-5.1-or-greater-p
	    do (setq part-description-of-machine
		     (nconc part-description-of-machine
			    (gensym-list
			      'maximum-number-of-concurrent-floating-tw2-allowed
			      (maximum-number-of-concurrent-floating-tw2-allowed
				machine))))
	  when t do (format t " .") ; This is a slow process, this helps gauge it.
	  when machine-id? do (write-part-description-to-stream
				s part-description-of-machine)))

      (block users
	(unless (loop
		  for user being each class-instance of 'authorized-user
		  when (name-or-names-for-frame user) do (return t))
;	  (emit "~%~%-- There were no named users in the KB.~%")
	  (return-from users nil))
	(emit "~%~%-- Named users.~%")
	(loop
	   for user being each class-instance of 'authorized-user
	   as name? = (name-or-names-for-frame user)
	   as part-description-of-user
	      = (gensym-list
		  'authorized-user
		  'name-or-names (name-or-names-for-frame user)
		  'user-password (user-password user)
		  'permitted-user-modes (permitted-user-modes user))
	   when name? do
	       (write-part-description-to-stream s part-description-of-user)))

      (emit "end g2-ok-file~%"))))

;; Removed seemingly silly comments
;;   -- There were no named users in the KB
;;   -- This was generated from a G2 Knowledge Base
;;   -- End of file marker
;; (MHD 4/26/01)



(defun write-part-description-to-stream (s part-description)
  (macrolet ((emit (&rest args) `(my-G2-stream-tformat s ,@args)))
    (loop with type = (first part-description)
	  initially (emit "~(begin ~S~%~)" type)
	  finally   (emit "~(end ~S~%~)" type)
	  for (key value) on (rest part-description) by #'cddr
	  do
      (emit "~(  ~NN:" key)
      (write-part-description-value-to-stream
	s value (if (memq key '(expiration-date? authorized-kb-packages))
		    '(list) nil))
      (emit ";~&"))))

;; Mine comments out object-configuration?

(defun write-part-description-value-to-stream (s v advice)
  (macrolet ((emit (&rest args) `(my-G2-stream-tformat s ,@args)))
    (cond
      ((eq nil v)
       (emit (if (memq 'list advice) " none" " false")))
      ((stringp v)  (emit " ~S" v))
      ((wide-string-p v) (emit " ~S" v))
      ((fixnump v)  (emit " ~D" v))
      ((symbolp v)  (emit " ~NN" v))
      ((listp v)
       (emit " (")
       (loop
	 with long? = (<f 5 (length v))
	 for e in v
	     do
	 (when long? (emit "~%                "))
	 (write-part-description-value-to-stream s e nil))
       (emit " )")))))






;;;; Dynamic Extent of Reading OK files


;;; `Reading-ok-file' is a dynamic extent which implements the
;;; stream abstraction for reading an textual OK file.  It works
;;; by reading large chunks of the file off disk, and then streaming
;;; characters from those chunks via read-char-from-ok-file.

;;; The character reading arranges to maintain a model of the
;;; current line number in line-number-of-ok-file-reader.

;;; `Pad-for-ok-file-reader' is a small string used for reading
;;; strings, symbols, when tokenizing.

;;; `Error-of-ok-file-reader?' is discussed in the error handling
;;; section below.

(def-dynamic-extent (reading-ok-file
		      (module sequences2))
  (g2-stream-of-ok-file-reader (proclaim-special-globally nil))
  (buffer-of-ok-file-reader (proclaim-special-globally nil))
  (buffer-index-of-ok-file-reader (proclaim-special-globally nil))
  (characters-in-buffer-of-ok-file-reader? (proclaim-special-globally nil))
  (buffer-length-of-ok-file-reader (proclaim-special-globally nil))
  (unread-char-of-ok-file-reader? (proclaim-special-globally nil))
  (line-number-of-ok-file-reader (proclaim-special-globally nil))
  (pad-for-ok-file-reader (proclaim-special-globally nil)
			  (process-binding (make-string 100)))
  (error-of-ok-file-reader? (proclaim-special-globally nil))
  (file-format-version-of-g2-ok-file? (proclaim-special-globally nil))
  (authorized-user-records-of-g2-ok-file (proclaim-special-globally nil))
  (useful-machine-authorization-info (proclaim-special-globally nil))
  (slot-pad-of-ok-file-reader (proclaim-special-globally nil))
  (success-of-ok-file-reader?  (proclaim-special-globally nil))
  (saw-more-than-one-machine-authorization? (proclaim-special-globally nil))
  ;(current-machine-of-g2-ok-file? (proclaim-special-globally nil))
  ) 

;; Took current-machine-of-g2-ok-file? outside of the reading-ok-file dynamic
;; extent so that its binding site could be moved all the way up to authorize-ab
;; in order to use it in a standard error message contextualizer that's there.

;; (defvar current-machine-of-g2-ok-file? nil)

;; -- UPDATE: now it's been replaced by current-machine-ids-of-g2-ok-file?, a
;; gensym list of machine IDs (for multiple dongles and/or ethernet adaptors).
;; (MHD 7/5/00)

(defvar current-machine-ids-of-g2-ok-file? nil)


(defmacro within-named-dynamic-extent* ((name &rest special-variables)
					&body body)
  `(within-named-dynamic-extent ,name
     (let ()
       (declare (special ,@special-variables))
       ,@body)))

(def-system-variable read-ok-file-buffer-1 sequences2
  (:funcall make-string 2048))

;;; `With-reading-ok-file' establishes the `reading-ok-file' dynamic
;;; extent.  It returns NIL indicating success or a text-string
;;; indicating what went wrong.

(defmacro with-reading-ok-file ((namestring) &body body)
  `(with-named-dynamic-extent* reading-ok-file
       ;; Notice that the let below does most of the actual bindings.
       ((error-of-ok-file-reader? nil)
	(line-number-of-ok-file-reader -1))
     (g2-stream-with-open-stream (stream ,namestring :direction :input)
       (cond
	 ((not stream)
	  (error-broke-rule-reading-ok-file
	    (could-not-open-stream-ok-message))) ;#1
	 ((null (gensym-pathname-name namestring))  ;; note A
	  (error-broke-rule-reading-ok-file
	    (no-filename-provided-ok-message))) ;#2
	 (t 
	  (let* ((g2-stream-of-ok-file-reader stream)
		 (buffer-of-ok-file-reader read-ok-file-buffer-1)
		 (buffer-length-of-ok-file-reader (length buffer-of-ok-file-reader))
		 (unread-char-of-ok-file-reader? nil)
		 (characters-in-buffer-of-ok-file-reader?
		   (g2-stream-read-into-buffer buffer-of-ok-file-reader
					       buffer-length-of-ok-file-reader
					       g2-stream-of-ok-file-reader))
		 (buffer-index-of-ok-file-reader 0)
		 (line-number-of-ok-file-reader 1)
		 (file-format-version-of-g2-ok-file? nil)
		 (authorized-user-records-of-g2-ok-file nil) ;; reclaimer?
		 (useful-machine-authorization-info nil) ;; reclaimer?
		 (success-of-ok-file-reader? nil) ;; Pessimistic
		 (saw-more-than-one-machine-authorization? nil)
		 (slot-pad-of-ok-file-reader
		   (allocate-managed-simple-vector 20)))
	    (prog1 (progn ,@body)
	      (reclaim-managed-simple-vector slot-pad-of-ok-file-reader)
	      ))))
       error-of-ok-file-reader?)))

;; Need handing for non existant OK file!

;; Note A: This check may be redundant given that the same situation is
;; checked for in `provide-pathname-for-launch-time-load-asking-os',
;; however the action that check does (merging the insufficient
;; original with the default) only goes through if the default is
;; actually supplied. The calling sequence into that function seems
;; to always supply it, but since I don't understand all of the situations
;; that could get to the function and can't rule out the possibility
;; that it won't be supplied, it seems best to leave this additional
;; check in for the case where we fall through.  11/27/96 ddm








;;;; Error Handling when reading G2 OK Files

;;; The reading process has both a recursive element, and a coroutined pipe
;;; lined element.  The first error encounted is treated as fatal. The text for
;;; the error is recorded in the global `error-of-ok-file-reader?', which is
;;; returned as the value of the with-reading-ok-file wrapper, and thus as the
;;; value of `read-ok-file'. That means that its handler is actually the
;;; trouble return case of `authorize-ab'. If there is no error, then
;;; error-of-ok-file-reader? will remain nil.

;;; As the process unwinds two notable things happen.  First some routines,
;;; particularly those that read characters, tokens, and statements, return
;;; unique values to signal that an error is in progress.

;;; Secondly other errors may occur.  These are reported to the the
;;; routines in this section, which effectively ignore them.  That
;;; assures that the original, most trival, error is reported to the
;;; users.

;;; For example a bad character is seen in the file.  This is reported
;;; here, and the mechinism unwinds.  Parsing failures are then reported
;;; here, and finally the error that the file didn't seem to contain
;;; a machine authorization is reported here.  Only the illegal character
;;; error is reported to the user.

;;; The arguement passed here is a constant narrow text.  This is copied
;;; into a wide string and stored.  This text appears in a message of
;;; this form:
;;;    OK file error near line 12
;;;    Rule broken: <your message here>
;;; Notice this allows both positive and negitive phrases:
;;;    OK file error near line 12
;;;    Rule broken: Illegal character encountered.
;;; or
;;;    OK file error near line 12
;;;    Rule broken: Only 7 bit characters are allowed.
;;;
;;; The statement of the line where the error occurs is blocked for certain errors
;;; by means of an optional flag in the call to error-broke-rule-reading-ok-file.
;;; These are cases where the error is not specific to a particular line (e.g. no
;;; machine entry in the file) or is only noticed after the entire entry has been
;;; read, at which point the line counter is pointing to the line just after the
;;; entry (e.g. a problem with the authorization codes). Including the line number
;;; would be misleading in those cases.

;;; (Adjustments, 7/2/98 -ddm) Two ways of reporting problems are now available.
;;; If the mistake is fatal, then the `error-broke-rule-reading-ok-file' form
;;; should be used with the effects described above. If the problem may not be
;;; fatal, for example if an older version of G2 is reading an OK file that has
;;; attributes that only make sense for newer G2s, then the problem should be
;;; reported online using `warning-while-reading-ok-file' and the parsing
;;; allowed to continue. Whether or not the problem is fatal will be determined
;;; later in the process.

(defun error-broke-rule-reading-ok-file (constant-text-of-rule-broken
					  &optional do-not-report-the-line-number? )
  (within-named-dynamic-extent* (reading-ok-file
				 error-of-ok-file-reader?)
    (unless error-of-ok-file-reader?
      (setf error-of-ok-file-reader?
	    (twith-output-to-text-string
	      (tformat "~%OK file error ~a"
		       (formulate-ok-error-message
			 constant-text-of-rule-broken
			 do-not-report-the-line-number?)))))))

(defun warning-while-reading-ok-file (constant-text-of-rule-broken
				      &optional do-not-report-the-line-number? )
  (let ((message
	  (twith-output-to-text-string
	    (tformat "OK file warning. Possible problem~a"
		     (formulate-ok-error-message
		       constant-text-of-rule-broken
		       do-not-report-the-line-number?)))))
    (let ((*write-console-p* t))
		(notify-user-at-console "~%~a~%" message))
    (reclaim-text-string message)))


(defun formulate-ok-error-message (constant-text-of-rule-broken
				    &optional do-not-report-the-line-number? )
  (twith-output-to-text-string
    (unless do-not-report-the-line-number?
      (when (<f 0 line-number-of-ok-file-reader)
	(tformat " on or near line ~D" line-number-of-ok-file-reader)))
    (tformat "~%Rule broken: ~A" constant-text-of-rule-broken)))


;;;; Character Handling in G2 OK Files

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant eof-character-for-g2-ok-file -1)
(defconstant illegal-character-for-g2-ok-file 0)
(defconstant whitespace-character-for-g2-ok-file 1)
(defconstant open-string-character-for-g2-ok-file 2)
(defconstant open-paren-character-for-g2-ok-file 3)
(defconstant close-paren-character-for-g2-ok-file 4)
(defconstant colon-character-for-g2-ok-file 5)
(defconstant semicolon-character-for-g2-ok-file 6)
(defconstant dash-character-for-g2-ok-file 7)
(defconstant digit-character-for-g2-ok-file 8)
(defconstant alphabetic-character-for-g2-ok-file 9)
(defconstant cr-character-for-g2-ok-file 10)
(defconstant lf-character-for-g2-ok-file 11)
(defconstant underscore-character-for-g2-ok-file 12)
(defconstant question-mark-character-for-g2-ok-file 13)
(defconstant period-character-for-g2-ok-file 14)
)


;;; The constant `symbol-token-match-should-be-case-sensitive-p' says whether
;;; string comparison should be case sensitive.  This is defined to be nil,
;;; i.e. characters in ok files can be either upper or lower case as usual in G2.

(defconstant symbol-token-match-should-be-case-sensitive-p nil)


(defmacro create-character-table-for-g2-ok-file ()
  (coerce
    (loop
      for i from 0 below 256
      as c = (code-char i)
      collect
      (cond
	((memq c '(#\space #\tab))
	 whitespace-character-for-g2-ok-file)
	((eq c #\")
	 open-string-character-for-g2-ok-file)
	((eq c #\return)
	 cr-character-for-g2-ok-file)
	((eq c #\linefeed)
	 lf-character-for-g2-ok-file)
	((eq c #\()
	 open-paren-character-for-g2-ok-file)
	((eq c #\))
	 close-paren-character-for-g2-ok-file)
	((eq c #\:)
	 colon-character-for-g2-ok-file)
	((eq c #\;)
	 semicolon-character-for-g2-ok-file)
	((eq c #\-)
	 dash-character-for-g2-ok-file)
	((eq c #\_)
	 underscore-character-for-g2-ok-file)
	((eq c #\?)
	 question-mark-character-for-g2-ok-file)
	((eq c #\.)
	 period-character-for-g2-ok-file)
	((digit-char-p c)
	 digit-character-for-g2-ok-file)
	((alpha-char-p c)
	 alphabetic-character-for-g2-ok-file)
	(t
	 illegal-character-for-g2-ok-file)))
    'simple-vector))


(defparameter character-table-for-g2-ok-file
  (create-character-table-for-g2-ok-file))




;;; `Read-char-from-ok-file' returns a character or :eof from
;;; the reading-ok-file dynamic extent advancing various pointers etc.

(defun read-char-from-ok-file ()
  (within-named-dynamic-extent* (reading-ok-file
				  unread-char-of-ok-file-reader?
				  buffer-of-ok-file-reader
				  buffer-length-of-ok-file-reader
				  g2-stream-of-ok-file-reader
				  characters-in-buffer-of-ok-file-reader?)
    (cond
      ;; We have a character which was push'd back.
      (unread-char-of-ok-file-reader?
       (prog1
	   unread-char-of-ok-file-reader?
	 (setf unread-char-of-ok-file-reader? nil)))
      ((eq 0 characters-in-buffer-of-ok-file-reader?)
       :eof)
      ;; The usual case.
      ((<f buffer-index-of-ok-file-reader
	   characters-in-buffer-of-ok-file-reader?)
       (prog1 (schar buffer-of-ok-file-reader buffer-index-of-ok-file-reader)
	 (incff buffer-index-of-ok-file-reader)))
      ;; Get another buffer full.
      (t
       (setf characters-in-buffer-of-ok-file-reader?
	     (g2-stream-read-into-buffer buffer-of-ok-file-reader
					 buffer-length-of-ok-file-reader
					 g2-stream-of-ok-file-reader))
       (cond
	 ((eq 0 characters-in-buffer-of-ok-file-reader?)
	  :eof)
	 (t
	  (setf buffer-index-of-ok-file-reader 1)
	  (schar buffer-of-ok-file-reader 0)))))))




;;; `Unread-char-from-ok-file' pushes the character given back
;;; into the stream implmented by the dynamic extent reading-ok-file.

(defun unread-char-from-ok-file (c)
  (within-named-dynamic-extent* (reading-ok-file
				  unread-char-of-ok-file-reader?)
    (setf unread-char-of-ok-file-reader? c)))



;;; `ok-file-sanity-check' will check that the file has
;;; the given string as it's first few characters.  This
;;; is used just after the file is opened and it's first
;;; buffer full has been read.  It provides a sanity check
;;; that the file we opened is in fact an ok file.

(defun ok-file-sanity-check (prefix-string)
  (within-named-dynamic-extent* (reading-ok-file
				  buffer-of-ok-file-reader
				  buffer-length-of-ok-file-reader
				  characters-in-buffer-of-ok-file-reader?)
    (let ((temporary-wide-string-copy
	    (text-string-substring	; the "wide" version is not polymorphic
	      buffer-of-ok-file-reader
	      0 (lengthw prefix-string))))
      (prog1 (if symbol-token-match-should-be-case-sensitive-p
		 (string=w prefix-string temporary-wide-string-copy)
		 (string-equalw prefix-string temporary-wide-string-copy))
	(reclaim-wide-string temporary-wide-string-copy)))))




;;;; G2 OK file Tokens

(def-structure (ok-file-token
		 #+development
		 (:print-function print-ok-file-token)
		 (:constructor
		   make-ok-file-token-1
		     (kind-of-ok-file-token
		       text-of-ok-file-token)))
  (kind-of-ok-file-token nil
			 ;:type (member :symbol :list :integer)
			 )
  (line-number-of-ok-file-token line-number-of-ok-file-reader
				;:type fixnum
				)
  (text-of-ok-file-token nil
			 :reclaimer reclaim-text-string
			 ;:type text-string
			 )
  (value-of-ok-file-token nil
			  ; :type (or null ok-file-token)
			  :reclaimer reclaim-ok-file-value))

#+development
(defun print-ok-file-token (token stream depth)
  (declare (ignore depth))
  (printing-random-object (token stream)
    (format stream "OK ~a: ~a"
	    (kind-of-ok-file-token token)
	    (text-of-ok-file-token token))))

(defvar contour-of-ok-file-tokens)

(defconser ok-file-token)

(defun make-ok-file-token (kind text)
  (let ((result (make-ok-file-token-1 kind text)))
    (ok-file-token-push result contour-of-ok-file-tokens)
    result))

(defmacro with-contour-of-ok-file-tokens (() &body body)
  `(let ((contour-of-ok-file-tokens nil))
     (prog1 (progn ,@body)
       (reclaim-contour-of-ok-file-tokens))))

;;; `Reclaim-contour-of-ok-file-tokens' clears all tokens that
;;; currently reside in the open contour of tokens.  It must be
;;; called before exiting the contour.  It maybe called within
;;; the contour if you have no further use for the tokens prior
;;; tokens.  That's a good thing to do.

(defun-void reclaim-contour-of-ok-file-tokens ()
  (loop for ok-file-token in contour-of-ok-file-tokens
	do (reclaim-ok-file-token ok-file-token))
  (reclaim-ok-file-token-list contour-of-ok-file-tokens)
  (setf contour-of-ok-file-tokens nil))

(defun make-constant-token (constant)
  (make-ok-file-token constant (copy-constant-wide-string #w"")))

(defun make-list-token (list)
  (let ((result (make-constant-token :list)))
    (setf (value-of-ok-file-token result) list)
    result))

(defun make-illegal-token (constant-text-of-rule-broken)
  (within-named-dynamic-extent* (reading-ok-file
				  error-of-ok-file-reader?)
    (error-broke-rule-reading-ok-file constant-text-of-rule-broken)
    (make-constant-token :illegal)))

(defun token-kind-is (kind token)
  (eq kind (kind-of-ok-file-token token)))



(defun symbol-token-match (string token)
  (and
    (eq :symbol (kind-of-ok-file-token token))
    (if symbol-token-match-should-be-case-sensitive-p
	(string=w string (text-of-ok-file-token token))
	(string-equalw string (text-of-ok-file-token token)))))

;; This is performance hotspot.

#+obsolete  ;; this version is case sensitive
(defun symbol-token-match (string token)
  (and
    (eq :symbol (kind-of-ok-file-token token))
    (let ((length (length string))
	  (token-stringw (text-of-ok-file-token token)))
      (and (=f length (wide-string-length token-stringw))
	   (loop for i from 0 below length
		 always
		 (=f (char-codew (charw token-stringw i))
		     (char-code (char string i))))))))


(defun reclaim-ok-file-value (value)
  (cond
    ((symbolp value))
    ((consp value)
     (reclaim-ok-file-value (car value))
     (reclaim-ok-file-value (cdr value))
     (reclaim-ok-file-token-cons value))
    ((ok-file-token-p value)
     ;; These are reclaimed by reclaim-contour-of-ok-file-tokens
     )
    (t
     (reclaim-slot-value value))))


(defun coerce-token-to-lisp (token-or-value)
  (cond
    ((consp token-or-value)
     (loop for i in token-or-value
	   collect (coerce-token-to-lisp i)
	     using ok-file-token-cons))
    ((ok-file-token-p token-or-value)
     (case (kind-of-ok-file-token token-or-value)
       (:symbol
	(setf (value-of-ok-file-token token-or-value)
	      (intern-wide-string
		(copy-wide-string
		  (nstring-upcasew
		    (text-of-ok-file-token token-or-value))))))
       (:list
	(coerce-token-to-lisp (value-of-ok-file-token token-or-value)))
       (otherwise
	(value-of-ok-file-token token-or-value))))))







;;;; Token Reading



(defun read-token-from-ok-file ()
  (block accumulate-token
    (macrolet ((return-token (token) `(return-from accumulate-token ,token))
	       (return-constant-token (constant)
		 `(return-token (make-constant-token ,constant))))
      (within-named-dynamic-extent* (reading-ok-file
				      characters-in-buffer-of-ok-file-reader?
				      line-number-of-ok-file-reader)
	(unless characters-in-buffer-of-ok-file-reader?
	  (return-from read-token-from-ok-file :eof))

	(loop
	  for char = (read-char-from-ok-file)
	  when (eq char :eof) do (return-constant-token :eof)
	  doing
	  (fixnum-case (the fixnum
			    (svref character-table-for-g2-ok-file
				   (ascii-char-code char)))
	    ;; Handle line terminators.
	    (#.cr-character-for-g2-ok-file
	       (unless (eq #\linefeed (read-char-from-ok-file))
		 (unread-char-from-ok-file char))
	       (incff line-number-of-ok-file-reader))
	    (#.lf-character-for-g2-ok-file
	       (incff line-number-of-ok-file-reader))

	    ;; Handle comments.
	    (#.dash-character-for-g2-ok-file
	       (unless (eq #\- (read-char-from-ok-file))
		 (return-from read-token-from-ok-file
		   (make-illegal-token
		     (hyphen-not-followed-by-another-hyphen-ok-message)))) ;#3
	       (loop
		 for char = (read-char-from-ok-file)
		 when (eq :eof char) do (return-constant-token :eof)
		 when (eq #\linefeed char)
		   do (incff line-number-of-ok-file-reader)
		      (return nil)
		 when (eq #\return char)
		   do (unless (eq #\linefeed (read-char-from-ok-file))
			(unread-char-from-ok-file char))
		      (incff line-number-of-ok-file-reader)))

	    ;; Skip over whitespace.
	    (#.whitespace-character-for-g2-ok-file
	       ;; skip
	       )

	    ;; Assorted more typical cases.
	    (#.open-string-character-for-g2-ok-file
	       (return-token (read-string-from-ok-file)))
	    (#.open-paren-character-for-g2-ok-file
	       (return-token (read-list-from-ok-file)))
	    (#.close-paren-character-for-g2-ok-file
	       (return-constant-token :close-paren))
	    (#.colon-character-for-g2-ok-file
	       (return-constant-token :colon))
	    (#.semicolon-character-for-g2-ok-file
	       (return-constant-token :semicolon))
	    (#.digit-character-for-g2-ok-file
	       (return-token (read-integer-from-ok-file char)))
	    (#.alphabetic-character-for-g2-ok-file
	       (return-token (read-symbol-from-ok-file char)))
	    (#.underscore-character-for-g2-ok-file
	       (return-token (read-symbol-from-ok-file char)))
	    (#.period-character-for-g2-ok-file
	       (return-token (read-symbol-from-ok-file char)))
	    (#.question-mark-character-for-g2-ok-file 
	       (return-token (read-symbol-from-ok-file char)))

	    ;; Finally
	    (otherwise
	      (return-constant-token
		(make-illegal-token
		  (character-cannot-start-token-ok-message)))) ;#4

	    ))))))


(defun text-string-of-pad-for-ok-file-reader (length)
  (within-named-dynamic-extent* (reading-ok-file
				  pad-for-ok-file-reader)
    (let ((result (obtain-text-string length)))
      (loop for i from 0 below length
	    do (setf (charw result i)
		     (code-wide-character ; fixed to explicitly type 
		       (ascii-char-code	  ;   convert. (MHD 6/7/96)
			 (schar pad-for-ok-file-reader i)))))
      result)))

;; This exists since there isn't a substrate routine that does
;; anything similar without type dynamic dispatching.
;;
;; -- This would produce the same result, and has no dispatching
;; in the inner loop, just a little at the beginning:  (MHD 6/7/96)
;;
;;  (copy-text-string-portion pad-for-ok-file-reader 0 length)
  


(defun read-string-from-ok-file ()
  (within-named-dynamic-extent* (reading-ok-file
				  pad-for-ok-file-reader)
    (loop for i from 0 below 60
	  finally (return (make-illegal-token
			    (string-too-long-ok-message))) ;#5
	  as c = (read-char-from-ok-file)
	  do
      (when (eq c #\")
	(return (make-ok-file-token
		  :string (text-string-of-pad-for-ok-file-reader i))))
      (when (memq c '(#\@ #\~ #\\ #\linefeed #\return))
	(return
	  (make-illegal-token (illegal-character-in-string-ok-message)))) ;#6
      (setf (schar pad-for-ok-file-reader i) c))))

;;; `read-symbol-from-ok-file' does just that.  It also coerces
;;; the symbol none into the list nil.

(defun read-symbol-from-ok-file (first-char)
  (within-named-dynamic-extent* (reading-ok-file
				  pad-for-ok-file-reader)
    (setf (schar pad-for-ok-file-reader 0) first-char)
    (let ((result
	    (loop
	      for i from 1 below 60
	      finally (return (make-illegal-token
				(symbol-too-long-ok-message))) ;#7
	      as c = (read-char-from-ok-file)
	      as op = (if (eq c :eof)
			  eof-character-for-g2-ok-file
			  (svref character-table-for-g2-ok-file (ascii-char-code c)))
	      do
	      (fixnum-case op
		((#.alphabetic-character-for-g2-ok-file
		    #.digit-character-for-g2-ok-file
		    #.dash-character-for-g2-ok-file
		    #.question-mark-character-for-g2-ok-file
		    #.underscore-character-for-g2-ok-file
		    #.period-character-for-g2-ok-file)
		 (setf (schar pad-for-ok-file-reader i) c))
		(#.whitespace-character-for-g2-ok-file
		   (return
		     (make-ok-file-token
		       :symbol (text-string-of-pad-for-ok-file-reader i))))
		(t
		  (unread-char-from-ok-file c)
		  (return
		    (make-ok-file-token
		      :symbol (text-string-of-pad-for-ok-file-reader i))))))))
      (cond
	((symbol-token-match #w"none" result)
	 (setf (kind-of-ok-file-token result) :list)
	 (setf (value-of-ok-file-token result) nil))
	((symbol-token-match #w"true" result)
	 (setf (value-of-ok-file-token result) t)))
      result)))

(defun read-integer-from-ok-file (first-char)
  (within-named-dynamic-extent* (reading-ok-file
				  pad-for-ok-file-reader)
    (setf (schar pad-for-ok-file-reader 0) first-char)
    (loop for i from 1 below 40
	  finally (return (make-illegal-token
			    (integer-too-long-ok-message))) ;#8
	  as c = (read-char-from-ok-file)
	  as op = (if (eq c :eof)
		      eof-character-for-g2-ok-file
		      (svref character-table-for-g2-ok-file (ascii-char-code c)))
	  do
      (fixnum-case op
	((#.digit-character-for-g2-ok-file)
	 (setf (schar pad-for-ok-file-reader i) c))
	((#.alphabetic-character-for-g2-ok-file
	    #.underscore-character-for-g2-ok-file
	    #.question-mark-character-for-g2-ok-file 
	    #.period-character-for-g2-ok-file)
	   (return (make-illegal-token
		     (integer-contains-non-digit-character-ok-message)))) ;#9
	(#.whitespace-character-for-g2-ok-file
	   (return (make-integer-ok-file-token-from-text
		     (text-string-of-pad-for-ok-file-reader i))))
	(t
	  (unread-char-from-ok-file c)
	  (return (make-integer-ok-file-token-from-text
		    (text-string-of-pad-for-ok-file-reader i))))))))

(defun make-integer-ok-file-token-from-text (stringw)
  (make-integer-ok-file-token
    stringw
    (loop
      with result = 0 finally (return result)
      for i from 0 below (wide-string-length stringw)
      for digit = (digit-char-pw (charw stringw i))
      doing (setf result (+f (*f 10 result) digit)))))

(defun make-integer-ok-file-token (stringw value)
  (let ((token (make-ok-file-token :integer stringw)))
    (setf (value-of-ok-file-token token)
	  value)
    token))


(defun read-list-from-ok-file ()
  (within-named-dynamic-extent* (reading-ok-file)
    (loop for element = (read-token-from-ok-file)
	  for i from 0
	  when (<=f 60 i) do
	      (return
		(make-illegal-token
		  (too-many-elements-in-list-ok-message))) ;#10
	  until (token-kind-is :close-paren element)
	  collect element into list using ok-file-token-cons
	  finally
	    (return (make-list-token list)))))

;; This will be using read-useful-element, not read-token.



;;; `Read-tokens-of-ok-file' provides a way to test things at
;;; at this layer in the cake.

#+development
(defun read-tokens-of-ok-file (&optional (namestring "/tmp/ok/g2v5.ok"))
  (declare allowing-unwind)
  (with-reading-ok-file (namestring)
    (loop for token = (read-token-from-ok-file)
	  do
      (cond
	((token-kind-is :illegal token)
	 (format t "~&Error on line# ~D" (line-number-of-ok-file-token token))
	 (format t "~&Rule broken: ~A" error-of-ok-file-reader?))
	((token-kind-is :eof token)
	 (format t "~&--- End of file ---")
	 (return))
	(t
	 (format t "~&~3D ~11S ~S"
		 (line-number-of-ok-file-token token)
		 (kind-of-ok-file-token token)
		 (text-of-ok-file-token token))
	 (when (value-of-ok-file-token token)
	   (format t "~&        ~S" (value-of-ok-file-token token)))
	   )))))





;;;; Slot Pad

;;; Yet another class/structure system, I'm sorry.  I wanted something that
;;; worked very early in the operation of G2, before a KB exists, and since I
;;; was reading things in I need a slot-name to slot-index mapping that
;;; structures do not currently support.

;;; We read the entities out of the file into simple vectors.  Since the file
;;; isn't very recursive we can get away with a single simple vector that we
;;; fill out, process, and then reuse.  We stow this simple vector in
;;; slot-pad-of-ok-file-reader.  We call it a pad after a concept in Forth,
;;; where they have a string pad that is used as a staging area when reading in
;;; a string.

;;; For the two kinds of entities we find in the ok file we have slot
;;; descriptions.  Since there are only two it is silly to build up too much of
;;; a support mechinism.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter slot-pad-descriptions-of-machine-authorization
    '((#w"name" name symbol)
      (#w"machine-id" machine-id string)
      (#w"authorized-products" authorized-products
       (list-of (member
		  #w"runtime" #w"restricted-use" #w"embedded"
		  #w"development" #w"offline" #w"gsi" #w"gfi" #w"icp"
		  #w"japanese" #w"korean" #w"chinese" #w"gspan" #w"nupec" #w"g1"
		  #w"online"
		  #w"jl" #w"jp" #w"al"
		  #w"ent"
		  )))
      (#w"expiration-date?" expiration-date?
       (or
	null
	(list-structure
	  (member #w"from")
	  integer
	  (member
	    #w"jan" #w"feb" #w"mar" #w"apr" #w"may" #w"jun"
	    #w"jul" #w"aug" #w"sep" #w"oct" #w"nov" #w"dec")
	  integer
	  (member #w"to")
	  integer
	  (member
	    #w"jan" #w"feb" #w"mar" #w"apr" #w"may" #w"jun"
	    #w"jul" #w"aug" #w"sep" #w"oct" #w"nov" #w"dec")
	  integer)))
      (#w"authorization" authorization (list-of integer))
      (#w"make-g2-secure?" make-g2-secure? boolean)
      (#w"authorized-kb-packages"
       authorized-kb-packages
       (list-of
	(or
	  (list-structure
	    symbol integer integer integer)
	  (list-structure
	    symbol
	    (member #w"from") integer (member
				    #w"jan" #w"feb" #w"mar" #w"apr" #w"may" #w"jun"
				    #w"jul" #w"aug" #w"sep" #w"oct" #w"nov" #w"dec") integer
	    (member #w"to") integer (member
				    #w"jan" #w"feb" #w"mar" #w"apr" #w"may" #w"jun"
				    #w"jul" #w"aug" #w"sep" #w"oct" #w"nov" #w"dec") integer
	    integer integer integer))))

      (#w"number-of-processes-authorized"
       number-of-processes-authorized
       integer)
      (#w"maximum-number-of-concurrent-floating-telewindows-allowed"
       maximum-number-of-concurrent-floating-telewindows-allowed
       integer)
      (#w"maximum-number-of-concurrent-floating-tw2-allowed"
       maximum-number-of-concurrent-floating-tw2-allowed
       integer)
      (#w"customer" customer symbol)
      (#w"serial-number" serial-number string)
      (#w"installation-code" installation-code string)
    )))


(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter slot-pad-descriptions-of-user
    '((#w"name" name symbol)
      (#w"password" password string)
      (#w"password-validity" password-validity integer)
      (#w"permitted-user-modes" permitted-user-modes (list-of symbol)))))



;;; `Unbound-value-for-ok-reader' provides a way to catch missing
;;; slots, or duplicate slots.

(defvar unbound-value-for-ok-reader '#:unbound-value-for-ok-reader)

(defun clear-slot-pad ()
  (within-named-dynamic-extent* (reading-ok-file
				  slot-pad-of-ok-file-reader)
    (loop for i from 0 below 20
	  do
      (setf (svref slot-pad-of-ok-file-reader i) unbound-value-for-ok-reader))))

(defmacro slot-of-slot-pad (name slot-descriptions)
  (let ((slot-index
	  (position (eval name) (eval slot-descriptions) :key #'second)))
    (unless slot-index
      (warn "Unknown ok-slot ~S" (eval name)))
    `(svref slot-pad-of-ok-file-reader ,slot-index)))







;;;; Parsing statements from OK Files

;;; OK files are so stylized we can have something a little
;;; larger than a token consisting of statements of two or three
;;; "tokens" each.  These are then used to drive the parser.



;;; `read-statement-from-ok-file' reads bits of the file.
;;; it presumes the file consists of only three kinds of
;;; forms:
;;;    <attribute-name> : <attribute-value> ;
;;;    begin <entity-name>
;;;    end <entity-name>
;;; We return three values, the first is a key word.
;;; the return value patterns are as follows:
;;;   :eof nil nil
;;;   :illegal token nil
;;;   :begin-entity <name:token> nil
;;;   :end-entity <name:token> nil
;;;   :attribute <key:token> <value:token>

(defun read-statement-from-ok-file ()
  (let ((first-token (read-token-from-ok-file))
	(second-token (read-token-from-ok-file))
	third-token
	fourth-token)
    (cond
      ((token-kind-is :eof first-token)
       (values :eof nil nil))
      ;; Begin and end entity.
      ((and (symbol-token-match #w"begin" first-token)
	    (token-kind-is :symbol second-token))
       (values :begin-entity second-token nil))
      ((and (symbol-token-match #w"end" first-token)
	    (token-kind-is :symbol second-token))
       (values :end-entity second-token nil))

      ;; Attribute value pairs. This clause does a coarse data check,
      ;; the next one complains about any problems that uncovers.
      ((and
	 (token-kind-is :symbol first-token)
	 (token-kind-is :colon second-token)
	 (setf third-token (read-token-from-ok-file))
	 (or (token-kind-is :list third-token)
	     (token-kind-is :integer third-token)
	     (token-kind-is :string third-token)
	     (token-kind-is :symbol third-token))
	 (token-kind-is :semicolon
			(setf fourth-token (read-token-from-ok-file))))
       (values :attribute first-token third-token))

      ;; These are errors in form that should cause the parsing
      ;; to stop. The only case that could be considered a candidate
      ;; for a warning is the illegal value, however the goal of
      ;; the warnings is to shield users from having to go through
      ;; multiple passes to catch misspellings and such. If the
      ;; spelling is so bad that the type of the token is changed
      ;; then there's probably a lot wrong. 
      (t
       (error-broke-rule-reading-ok-file
	 (cond
	   ((token-kind-is :eof second-token)
	    (eof-in-middle-of-statement-ok-message)) ;#11
	   (fourth-token
	    (fourth-element-of-statement-not-a-semicolon-ok-message)) ;#12
	   (third-token
	    ;(illegal-attribute-value-ok-message) ;#13
	    (illegal-attribute-value-ok-message-1 first-token third-token))
	   (t (unknown-problem-parsing-statement-ok-message)))) ;#14
       (values :illegal first-token nil)))))

;; !! This error pattern doesn't notice that you've omitted the colon!

#+development
(defun read-forms-from-ok-file (&optional (namestring "/home/bhyde/junk/test.ok"))
  (declare allowing-unwind)
  (with-reading-ok-file (namestring)
    (loop doing
      (multiple-value-bind (statement v1 v2)
	  (read-statement-from-ok-file)
	(case statement
	  (:begin-entity
	   (format t "~&begin ~S" v1))
	  (:end-entity
	   (format t "~&end ~S" v1))
	  (:attribute
	   (format t "~&   ~S ~S" v1 v2))
	  (:illegal
	   (format t "~&illegal ~a" error-of-ok-file-reader?))
	  (:eof
	   (format t "~& --- EOF ---")
	 (return nil)))))))







;;;; OK File Parsing


#+development
(defun-allowing-unwind test-ok-parsing (path name)
  (protected-let
      ((current-machine-ids-of-g2-ok-file?
	 (get-local-machine-ids-as-gensym-list)
	 (reclaim-gensym-tree-with-text-strings current-machine-ids-of-g2-ok-file?))
       (pathname (gensym-make-pathname
		   :name name :directory path :type #w"ok")))
    (format t "Reading from ~a" pathname)
    (read-ok-file pathname)))



;;; `Read-ok-file' is the top level of a recursive reader for the G2 ok file.
;;; Returns nil or a string.  The string indicates failure, and is a wide
;;; string indicating what broke.  See the section
;;; "Error Handling when reading G2 OK Files" for more info.

(defun read-ok-file (&optional (namestring "/home/bhyde/junk/test.ok"))
  (declare allowing-unwind)
  (with-reading-ok-file (namestring)
    (block :reading
      (macrolet ((done () '(progn
			    (clear-slot-pad)
			    (return-from :reading nil)))
		 (break-out (constant-text-of-rule-broken
			      &optional no-line-numbers-flag)
		   `(progn
		      (error-broke-rule-reading-ok-file
			,constant-text-of-rule-broken ,no-line-numbers-flag)
		      (done))))
	;; Sanity check on first N characters of OK file.
	(unless (ok-file-sanity-check #w"begin g2-ok-file")
	  (break-out
	    (sanity-check-on-initial-characters-of-file-ok-message))) ;#15

	;; Read prefix of the first and only entity.
	(with-contour-of-ok-file-tokens () ;; Note A
	  (multiple-value-bind (s v1 v2) (read-statement-from-ok-file)
	    (declare (ignore v2))
	    (when (eq :error s) (done))  ;; impossible value for s
	    (unless (and (eq :begin-entity s)
			 (symbol-token-match #w"g2-ok-file" v1))
	      (break-out
		(header-for-file-entry-missing-ok-message))) ;#16
	    (read-g2-ok-file-entity)))
	
	(unless success-of-ok-file-reader?
	  (if saw-more-than-one-machine-authorization?
	      (break-out
		(no-authorization-found-for-this-machine-multiple-entries-ok-message) ;#17
		t)
	      (break-out
		(no-authorization-found-for-this-machine-one-entry-ok-message)
		t))))))) ;#17a

;; Note A: The break out can skip the reclaim this does, but
;; since G2 then shuts down that's tollerable.



;;; `Read-g2-ok-file-entity' is invoked after reading the begin statement of the
;;; g2-ok-file-entity.  Side effects on the authorization status of G2 usually
;;; occur.  No return value.

(defun-void read-g2-ok-file-entity ()
  (let ((saw-at-least-one-machine-authorization? nil))
    (within-named-dynamic-extent* (reading-ok-file
				   file-format-version-of-g2-ok-file?
				   saw-more-than-one-machine-authorization?)
      (with-contour-of-ok-file-tokens ()
	(loop
	  with have-seen-subentities? = nil
	  doing
	  (reclaim-contour-of-ok-file-tokens)
	  (macrolet ((break-out (constant-text-of-rule-broken
				  &optional no-line-numbers-flag)
		       `(progn
			  (error-broke-rule-reading-ok-file
			    ,constant-text-of-rule-broken ,no-line-numbers-flag)
			  (return nil))))
	    (multiple-value-bind (s v1 v2) (read-statement-from-ok-file)
	      (case s
		(:eof
		 (return nil))

		(:begin-entity
		 (cond
		   ((symbol-token-match #w"machine" v1)
		    (if saw-at-least-one-machine-authorization?
			(setf saw-more-than-one-machine-authorization? t)
			(setf saw-at-least-one-machine-authorization? t))
		    (read-machine-ok-file-entry))
		   ((symbol-token-match #w"user" v1)
		    (read-user-ok-file-entry))
		   (t
		    (break-out (undefined-entry-type-ok-message))))) ;#18

		(:attribute
		 (cond
		   (have-seen-subentities?
		    (break-out (file-attribute-not-initial-ok-message))) ;#19
		   
		   ((not (symbol-token-match #w"file-format-version" v1))
		    (break-out (undefined-file-attribute-ok-message))) ;#20
		   
		   (file-format-version-of-g2-ok-file?
		    (break-out (file-format-attribute-duplicated-ok-message))) ;#21
		   
		   ((not (token-kind-is :integer v2))
		    (break-out (file-format-value-not-an-integer-ok-message))) ;#22
		   
		   ((ok-file-is-incompatible-with-image (value-of-ok-file-token v2))
		    (break-out (file-version-higher-than-image-version-ok-message-1 ;#22a
				 supported-ok-file-format-version
				 (value-of-ok-file-token v2))))
		   
		   (t
		    (setf file-format-version-of-g2-ok-file?
			  (value-of-ok-file-token v2)))))

		(:end-entity
		 (unless (symbol-token-match #w"g2-ok-file" v1)
		   (break-out (wrong-label-on-file-level-end-statement-ok-message)))) ;#23

		(t
		 (break-out (unknown-problem-parsing-file-ok-message))))))))) ;#24
    
    (unless saw-at-least-one-machine-authorization?
      (error-broke-rule-reading-ok-file
	(no-machine-authorization-in-file-ok-message) t)))) ;#25







;;; `read-user-ok-file-entry' is invoked to read the body of a user's
;;; authorziation entry in the ok file after the "begin user" has been read.  It
;;; has no return value but may note an error, and return.  It usually has side
;;; effects on the set of user records being accumulated in the reading-ok-file
;;; dynamic extent.

(defun read-user-ok-file-entry ()
  (within-named-dynamic-extent* (reading-ok-file)
    (with-contour-of-ok-file-tokens ()
      (macrolet ((debugging (level &rest args)
		   ;; Low numbers are more likely to print
		   (when nil
		     `(when (<= ,level 10)
			(format t "~&~S " 'read-user-ok-file-entry)
			(format t ,@args)
			nil)))
		 (break-out (constant-text-of-rule-broken)
		   `(progn
		      (debugging 2 "broke-out")
		      (error-broke-rule-reading-ok-file
			,constant-text-of-rule-broken)
		      (return-from read-user-ok-file-entry nil)))
		 (slot (name)
		   `(slot-of-slot-pad ,name slot-pad-descriptions-of-user))
		 (slot-text (name)
		   `(text-of-ok-file-token (slot ,name)))
		 (slot-value (name)
		   `(progn
		      (debugging 4 "slot-value ~S" ,name)
		      (value-of-ok-file-token (slot ,name))))
		 (ok-unboundp (name)
		   `(eq (slot ,name) unbound-value-for-ok-reader)))

	;; Clean slot slate.
	(debugging 2 "clear-slot-pad")
	(clear-slot-pad)

	;; Read slots.
	(loop
	  doing
	  (multiple-value-bind (s v1 v2) (read-statement-from-ok-file)
	    (debugging 2 "stm: ~S ~S ~S" s v1 v2)
	    (case s
	      (:end-entity
	       (unless (symbol-token-match #w"user" v1)
		 (break-out (wrong-label-on-end-statement-ok-message))) ;#26
	       (return nil))
	      (:attribute
	       ;; Problems with attributes of user entries are reasons to
	       ;; stop since all of them are required. Alternatively, could
	       ;; beef up the final processing of user entries and catch
	       ;; the problem then so as to allow every instance of an
	       ;; attribute problem to be noticed and warned about rather
	       ;; than just stopping with the first.  ddm 7/14/98
	       (unless (process-attribute-of-entity
			 slot-pad-descriptions-of-user
			 v1
			 v2)
		 (break-out "")))  ; error recorded by process-attribute-of-entity
	      (t
	       (break-out (unknown-problem-parsing-entry-ok-message)))))) ;#27

	;; Semantic checking and commit.
	(let ((permitted-user-modes
		(coerce-token-to-lisp
		  (slot 'permitted-user-modes))))
	  ;; Type checking is almost sufficent.
	  (unless permitted-user-modes
	    (break-out (no-user-modes-specified-ok-message))) ;#28
	  (when (memq 'proprietary permitted-user-modes)
	    (break-out (proprietary-mode-specified-ok-message))) ;#29

	  ;; Proceed to commit the edit.
	  (enter-authorized-user
	    (coerce-token-to-lisp (slot 'name))
	    (copy-text-string (slot-text 'password))
	    (copy-list-using-gensym-conses permitted-user-modes)
	    (coerce-token-to-lisp (slot 'password-validity))
	    t ) ; this is the original call, not an update
	  
	  (reclaim-gensym-list permitted-user-modes))))))



;;; `Read-machine-ok-file-entry' is invoked to read the body of a user's
;;; authorziation entry in the ok file after the "begin user" has been
;;; read.  It has no return value but may note an error, and return.  It
;;; has side effects: if it encounters an authorization that appears valid
;;; for this machine it will record the info it found into the dynamic
;;; extent.

(defun read-machine-ok-file-entry ()
  (within-named-dynamic-extent* (reading-ok-file
				  file-format-version-of-g2-ok-file?)
    (with-contour-of-ok-file-tokens ()
      (macrolet ((debugging (level &rest args)
		   ;; Low numbers are more likely to print
		   (when nil
		     `(when (<= ,level 5)
			(format t "~&~S " 'read-machine-ok-file-entry)
			(format t ,@args)
			nil)))
		 (break-out (constant-text-of-rule-broken)
		   `(progn
		      (debugging 2 "broke-out")
		      (error-broke-rule-reading-ok-file
			,constant-text-of-rule-broken)
		      (return-from read-machine-ok-file-entry nil)))
		 (slot (name)
		   `(slot-of-slot-pad
		      ,name
		      slot-pad-descriptions-of-machine-authorization))
		 (slot-text (name)
		   `(text-of-ok-file-token (slot ,name)))
		 (slot-value (name)
		   `(progn
		      (debugging 4 "slot-value ~S" ,name)
		      (value-of-ok-file-token (slot ,name))))
		 (ok-unboundp (name)
		   `(eq (slot ,name) unbound-value-for-ok-reader))
		 (slot-is-present (name)
		   `(not (ok-unboundp ,name))))

	;; Wipe off the slate.
	(clear-slot-pad)
	(debugging 2 "clear")

	;; Read in the entity's slots.
	(debugging 2 "read-slots")
	(loop
	  doing
	  (multiple-value-bind (s v1 v2) (read-statement-from-ok-file)
	    (debugging 2 "stm: ~S ~S ~S" s v1 v2)
	    (case s
	      (:end-entity
	       (unless (symbol-token-match #w"machine" v1)
		 (break-out (wrong-label-on-end-statement-ok-message))) ;# 
	       (return nil))
	      (:attribute
	       ;; Problems here have for the most part been converted to warnings.
	       ;; Remove this old code once this is stable. ddm 7/2/98
;	       (unless (process-attribute-of-entity
;			 slot-pad-descriptions-of-machine-authorization
;			 v1
;			 v2)
;		 (break-out "")) ; error recorded in process-attribute-of-entity
	       (process-attribute-of-entity
			 slot-pad-descriptions-of-machine-authorization
			 v1
			 v2))
	      (t
	       (break-out (unknown-problem-parsing-entry-ok-message)))))) ;# 

	;; Scan slots, checking for required values, and binding
	;; defaults for those that aren't required.
	(debugging 2 "bind defaults, check required")
	
	(when (eq (slot 'machine-id) unbound-value-for-ok-reader)
	  (break-out (machine-id-missing-ok-message))) ;#30
	(when (ok-unboundp 'authorization)
	  (break-out (authorization-missing-ok-message))) ;#31

	(when (ok-unboundp 'name)
	  (setf (slot 'name) (make-list-token nil)))
	(when (ok-unboundp 'authorized-products)
	  (setf (slot 'authorized-products) (make-list-token nil)))
	(when (ok-unboundp 'expiration-date?)
	  (setf (slot 'expiration-date?) (make-list-token nil)))
	(when (ok-unboundp 'make-g2-secure?)
	  (setf (slot 'make-g2-secure?) (make-list-token nil)))
	(when (ok-unboundp 'authorized-kb-packages)
	  (setf (slot 'authorized-kb-packages) (make-list-token nil)))
	(when (ok-unboundp 'number-of-processes-authorized)
	  (setf (slot 'number-of-processes-authorized)
		(make-integer-ok-file-token
		  (copy-wide-string #w"1")
		  1)))
	(when (ok-unboundp 'maximum-number-of-concurrent-floating-telewindows-allowed)
	  (setf (slot 'maximum-number-of-concurrent-floating-telewindows-allowed)
		(make-integer-ok-file-token
		  (copy-wide-string #w"0")
		  0)))
	(when (ok-unboundp 'maximum-number-of-concurrent-floating-tw2-allowed)
	  (setf (slot 'maximum-number-of-concurrent-floating-tw2-allowed)
		(make-integer-ok-file-token
		  (copy-wide-string #w"0")
		  0)))

	;; Semantic checking, required of all machine authorizations.
	(debugging 2 "semantic checking")
	(when (shunned-machine-id-string-p (slot-text 'machine-id))
	  (break-out (shunned-machine-id-ok-message))) ;#32

	;; Semantic checking, required of this machine's authorization.
	(when (or (loop for id in current-machine-ids-of-g2-ok-file?
			thereis (normalized-string-equal (slot-text 'machine-id) id))
		  (machine-id-of-site-p (slot-text 'machine-id)))
	  (debugging 1 "authorization encountered for this machine.")

	  
	  ;; The following are taken from the old OK object's
	  ;; slot compiler/putter/grammer, etc.
	  ;; TBD: Check package authorization. etc. etc.

	  (debugging 1 "attempt to authorize.")
	  (let ((codes (slot-value 'authorization))
		(authorized-products
		  (coerce-token-to-lisp (slot-value 'authorized-products)))
		(authorized-kb-packages-parse
		  (coerce-token-to-lisp (slot-value 'authorized-kb-packages)))
		(expiration-date-parse
		  (coerce-token-to-lisp (slot-value 'expiration-date?)))
		expiration-date? authorized-kb-packages)

	    (when (slot-is-present 'customer)
	      (setq name-of-customer-in-ok-file
		    (process-slot-text-for-customer (slot-text 'customer))))
	    (when (slot-is-present 'serial-number)
	      (setq serial-number-in-ok-file
		    (copy-text-string (slot-text 'serial-number))))
	    (when (slot-is-present 'installation-code)
	      (setq installation-code-in-ok-file
		    (copy-text-string (slot-text 'installation-code))))

	    (unless (=f 5 (length codes))
	      (break-out (wrong-number-of-authorization-codes-ok-message))) ;#44

	    (when expiration-date-parse
	      (when *expiration-date-for-display-in-title*
		(reclaim-gensym-tree *expiration-date-for-display-in-title*))
	      (setq *expiration-date-for-display-in-title*
		    (copy-tree-using-gensym-conses expiration-date-parse))
	      (let* ((from-date? (convert-input-to-universal-date
				   (cdr expiration-date-parse)))
		     (to-date? (convert-input-to-universal-date
				 (cddddr (cdr expiration-date-parse)))))
		(unless (and from-date? to-date? (<f from-date? to-date?))
		  (break-out
		    (from-date-earlier-than-to-date-ok-message))) ;#33
		(setf expiration-date?
		      (encode-authorization-interval from-date? to-date?))))

	    (setf authorized-kb-packages
		  (loop
		    for element in authorized-kb-packages-parse
		    collecting    
		    (cond
		      ((<f 4 (length element))
		       (let* ((from-date?
				(convert-input-to-universal-date (cddr element)))
			      (to-date?
				(convert-input-to-universal-date
				  (cddddr (cddr element)))))
			 (unless (and from-date? to-date? (<f from-date?
							      to-date?))
			   (break-out (from-date-earlier-than-to-date-ok-message))) ;#33
			 (ok-file-token-cons
			   (first element)
			   (nconc
			     (copy-list-using-ok-file-token-conses (nthcdr 9 element))
			     (ok-file-token-list from-date? to-date?)))))
		      (t
		       (copy-list-using-ok-file-token-conses element)))
		      using ok-file-token-cons))

	    (unless (new-analyze-authorized-packages
		      authorized-kb-packages
		      (slot-text 'machine-id))
	      (break-out "")) ; error recorded in new-analyze-authorized-packages

	  ;; GENSYMCID-1465: How can'I change g2.ok file without restart G2
	  (with-dynamic-creation ; indent is wrong here.
	    (new-reformat-line-from-left
	      (slot-text 'machine-id)
	      (value-of-ok-file-token (first codes))
	      (value-of-ok-file-token (second codes))
	      (value-of-ok-file-token (third codes))
	      (value-of-ok-file-token (fourth codes))
	      (value-of-ok-file-token (fifth codes))
	      authorized-products
	      authorized-kb-packages
	      expiration-date?
	      (slot-value 'number-of-processes-authorized)
	      (slot-value
		'maximum-number-of-concurrent-floating-telewindows-allowed)
	      (slot-value
		'maximum-number-of-concurrent-floating-tw2-allowed)
	      (slot-value 'make-g2-secure?))
	    (reclaim-ok-file-token-tree authorized-products)
	    (reclaim-ok-file-token-tree authorized-kb-packages-parse)
	    (reclaim-ok-file-token-tree authorized-kb-packages)
	    (reclaim-ok-file-token-tree expiration-date-parse))))))))



;;; The function `process-slot-text-for-customer' processes the slot text with the
;;; customer information from the OK file, and returns either a freshly consed
;;; text string presentable to the user as the customer name or nil.
;;;
;;; This is a bit of a hack to make the customer symbol more human-friendly in
;;; appearance.  We want to not print anything in the "no customer" case
;;; (uniquely identified with slot text = "x_").  In this case we return nil.
;;; We also want to print -'s and _'s as spaces.  (User-typed spaces are
;;; converted to -, and punctuation characters are converted to _'s.)  In the
;;; unusual case of ending up with only spaces, this returns nil.  In any other
;;; case, this returns a new text string.

(defun process-slot-text-for-customer (slot-text)
  (if (string=w slot-text #w"x_")
      nil		; no customer case		      
      (let* ((temp-string
	       (twith-output-to-text-string
		 (loop as just-wrote-space-p
			  = nil
			  then (char=w char #.%space)
		       for i from 0 below (lengthw slot-text)
		       as char = (charw slot-text i)
		       do (setq char 
				(if (member char '(#.%\- #.%_))
				    #.%space
				    char))
		       unless (and just-wrote-space-p ; collapse multiple spaces
				   (char=w char #.%space))
			 do (twrite-character char))))
	     (trimmed-temp-string
	       (text-string-trim '(#.%space) temp-string)))
	(reclaim-text-string temp-string)	    
	(if (string=w trimmed-temp-string #w"")
	    (progn
	      (reclaim-text-string trimmed-temp-string)
	      nil)
	    trimmed-temp-string))))

;; Added for G2 6.0 Beta Rev. 1, and for G2 5.1 Rev. 8.  The
;; customer information was added and exposed to user with the
;; first bundle release, as of G2 5.1 Rev. 6. (MHD 2/6/01)



(defun process-attribute-of-entity (slot-descriptions
				     attribute-name
				     attribute-value)
  (within-named-dynamic-extent* (reading-ok-file
				  slot-pad-of-ok-file-reader)
    (loop
      finally
	(warning-while-reading-ok-file
	  ;(unrecognized-attribute-ok-message) ;#34
	  (unrecognized-attribute-ok-message-1 attribute-name))
	(return nil)
      for (slot-spelling slot-symbol slot-type) in slot-descriptions
      as i from 0
      when (symbol-token-match slot-spelling attribute-name)
	do
	  (unless (check-ok-token-against-type attribute-value slot-type)
	    (warning-while-reading-ok-file
	      ;(syntax-error-in-attribute-value-ok-message) ;#35
	      (syntax-error-in-attribute-value-ok-message-1
		attribute-name attribute-value slot-type))
	    (return nil))
	  (unless (eq unbound-value-for-ok-reader
		      (svref slot-pad-of-ok-file-reader i))
	    (warning-while-reading-ok-file
	      ;(attribute-appears-more-than-once-ok-message) ;#36
	      (attribute-appears-more-than-once-ok-message-1 attribute-name))		
	    (return nil))
	  (setf (svref slot-pad-of-ok-file-reader i) attribute-value)
	  (return t))))

(defun check-ok-token-against-type (token type)
  (cond
    ((symbolp type)
     (case type
       (integer
	(token-kind-is :integer token))
       (symbol
	(token-kind-is :symbol token))
       (string
	(token-kind-is :string token))
       (null
	(and (eq nil (value-of-ok-file-token token))
	     (token-kind-is :list token)))
       (boolean
	(and (token-kind-is :symbol token)
	     (or (symbol-token-match #w"false" token)
		 (symbol-token-match #w"true" token))))
       #+development
       (otherwise
	(error "Opps3"))))
    ((listp type)
     (case (first type)
;       (satisfies
;	(funcall (second type) token))
       (or
	(loop for cantidate-type in (rest type)
	      when (check-ok-token-against-type token cantidate-type)
		do (return t)
	      finally (return nil)))
       (member ;; Not exactly what you'd expect, see example use.
	(loop for element in (rest type)
	      when (symbol-token-match element token)
		do (return t)
	      finally (return nil)))
       (list-of
	(and
	  (token-kind-is :list token)
	  (loop
	    with element-type = (second type)
	    for element in (value-of-ok-file-token token)
	    always (check-ok-token-against-type
		     element element-type))))
       (list-structure
	(let ((value (value-of-ok-file-token token))
	      (element-types (rest type)))
	  (and
	    (token-kind-is :list token)
	    (=f (length value) (length element-types))
	    (loop
	      for element in (value-of-ok-file-token token)
	      for element-type in element-types
	      unless (check-ok-token-against-type element element-type)
		do (return nil)
	      finally (return t)))))
       #+development
       (t
	(error "Opps"))))
    #+development
    (t
     (error "Opps2"))))







;;;; OK File Probing

;;; The functions in this section deal with probing the one G2.ok file, if any,
;;; that was used to authorize G2.  


;;; The variable `authorizing-OK-pathname' is either nil (while G2 is loading)
;;; or the gensym pathname that was used to load the g2.ok file from which the
;;; current G2 has been authorized.  We save the identity of the OK file since
;;; we allow users to change their passwords via a classic G2 dialog while G2 is
;;; running and we want the changes to be recorded in the same OK file that this
;;; G2 was authorized from. It is set in authorize-ab and never reset.

(defvar authorizing-OK-pathname nil)

(defun-simple set-authorizing-OK-pathname (pathname)
  (when (gensym-pathname-version pathname)
    (setf (gensym-pathname-version pathname) :newest))
  (setq authorizing-OK-pathname pathname))



(defun g2-ok-file-probe-for-write ()
  (let ((pathname? authorizing-OK-pathname))
    (if pathname? (gensym-probe-file-for-write pathname?))))

(defun-allowing-unwind g2-ok-file-writeable-p ()
  (protected-let
      ((pathname?
	 (if authorizing-OK-pathname
	     (gensym-probe-file-for-write authorizing-OK-pathname))
	 (reclaim-gensym-pathname pathname?)))
    (if pathname? t nil)))

(defun g2-ok-file-probe ()
  (let ((pathname? authorizing-OK-pathname))
    (if pathname? (gensym-probe-file pathname?))))

(defun-allowing-unwind g2-ok-file-readable-p ()
  (protected-let
      ((pathname?
	 (if authorizing-OK-pathname
	     (gensym-probe-file authorizing-OK-pathname))
	 (reclaim-gensym-pathname pathname?)))
    (if pathname? t nil)))
  






;;;; Checking for the G2passwd Executable

;;; ... see def-command-line-argument (g2passwdexe ...) in utilities3

(def-system-variable g2passwdexe sequences2
  (:funcall initialize-g2passwdexe))

(defun initialize-g2passwdexe ()
  (getf command-line-arguments 'g2passwdexe))

(defun-allowing-unwind g2passwd-probe-file ()
  (when g2passwdexe
    (with-protected-pathname-conversion ((g2passwdexe g2passwd-pathname))
      (if (eq (gensym-pathname-file-system g2passwd-pathname) 'UNIX)
	  (gensym-probe-file-for-truth-value g2passwd-pathname)
	  (protected-let ((g2passwd-EXE-pathname
			    ;;the "G2" portion of "G2.EXE" is overridden by merge pathnames
			    (gensym-merge-pathnames g2passwd-pathname #w"G2.EXE")
			    (reclaim-gensym-pathname g2passwd-EXE-pathname)))
	    (gensym-probe-file-for-truth-value g2passwd-EXE-pathname))))))
	
      

(def-system-variable g2passwdexe-is-executable-p sequences2
  'unknown)


(defconstant g2passwdexe-areyouthere-arg
  "-areyouthere"); in g2passwd: #define G2PW_AREYOUTHERE_ARG
(defconstant g2passwdexe-areyouthere-good-result
  111)	         ; in g2passwd: #define G2PW_GOOD_RESULT  (arbitrary 8-bit int)

;; see also corresponding code in g2passwd.c


(defun-allowing-unwind initialize-g2passwdexe-is-executable-p ()
  (protected-let*
      ((command-line
	 (tformat-text-string "~a ~a" g2passwdexe g2passwdexe-areyouthere-arg)
	 (reclaim-text-string command-line))
       (result (c-substatus_run_command_line command-line)))
    (=f result g2passwdexe-areyouthere-good-result)))


;;; `Check-password-setup-and-notify-user-if-necessary' packages all the
;;; operations that we need to do for this as part of launching g2.
;;; It is called from Authorize-ab, which gates it with a call to
;;; g2-secure-p.

(defun-allowing-unwind check-password-setup-and-notify-user-if-necessary ()
  ;; Do the setup. Include a sanity check that we haven't already
  ;; done this, though if we only ever go through authorize-ab once
  ;; that's unnecessary
  (when (eq g2passwdexe-is-executable-p 'unknown)
    (setq g2passwdexe-is-executable-p
	  (initialize-g2passwdexe-is-executable-p)))

  ;; Check for a problem
  (when (not g2passwdexe-is-executable-p)
    (protected-let ((message
		      (twith-output-to-text-string
			(twrite-standard-secure-g2-notification-header)
			(tformat
			  "Warning: Cannot execute ~s from G2; password changing will be disabled for the entire G2 session!"
			  g2passwdexe))
		      (reclaim-text-string message)))

      (let ((*write-console-p* t))
		(notify-user-at-console "~%~a~%" message)))))

;; Note: the message is supposed to work for both the case where this is not
;; there and for the case where it's there, but it's an old version.  Maybe can
;; improve the wording.  Note: when we use an old version of g2passwd, we expect
;; it to print out something like:
;;
;;  ERROR: Unable to open "-areyouthere" as a G2 OK file.
;;
;; before we print out this message.  Ugly, but the users will just have to
;; update their g2passwd executable to get rid of this uglyness.  (MHD 2/26/98)







;;;; OK Parsing to update user information

;;; This is called from g2-update-user-data-from-ok-file, the system
;;; procedure that administrators can use to change the users or
;;; their modes in a secure G2 without having to drop the system
;;; and reload the OK file, i.e. this reads the file with the system
;;; up and just reacts to the user entries. If no problems are
;;; encountered it returns Nil to indicate success. Otherwise it
;;; returns a fresh copy of the error string for that problem.
;;; (See define-ok-message and the section on 'Error Handling
;;; when reading G2 OK Files'.)
;;;
;;; This is largely a straight copy of the equivalent functions
;;; in the regular, authorizing ok parser. It didn't seem worth it to
;;; abstract out the core of something this ideosyncratic that was
;;; only going to have two instantiations and has only one maintainer.
;;;  - ddm 1/9/98


(defun read-ok-file-just-for-updating-user-data (namestring)
  (declare allowing-unwind)
  (let ((error-in-ok-file? nil))
    (with-reading-ok-file (namestring)
      (block :reading
	(macrolet ((done () '(progn
			      (clear-slot-pad)
			      (return-from :reading nil)))
		   (break-out (constant-text-of-rule-broken
				&optional no-line-numbers-flag)
		     `(progn
			(error-broke-rule-reading-ok-file
			  ,constant-text-of-rule-broken ,no-line-numbers-flag)
			(done))))
	  
	  ;; Standard sanity check
	  (unless (ok-file-sanity-check #w"begin g2-ok-file")
	    (break-out
	      (sanity-check-on-initial-characters-of-file-ok-message))) ;#15

	  ;; get the prefix of the wrapper around the whole file out of the way
	  (with-contour-of-ok-file-tokens ()
	    (multiple-value-bind (s v1 v2) (read-statement-from-ok-file)
	      (declare (ignore v2))

	      (unless (and (eq :begin-entity s)
			   (symbol-token-match #w"g2-ok-file" v1))
		(break-out
		  (header-for-file-entry-missing-ok-message))) ;#16

	      ;; do all the work
	      (read-g2-ok-file-entity-just-for-users)))

	  
	  ;; lift the error flag out of the reading-ok-file wrapper
	  (setq error-in-ok-file? error-of-ok-file-reader?)

	  (unless error-in-ok-file?
	    ;; Assimilate the results of the changes to individual user entries
	    (update-OK-user-data)))))
    
    error-in-ok-file? ))



(defun read-g2-ok-file-entity-just-for-users ()
  (with-contour-of-ok-file-tokens ()
    (macrolet ((done () '(progn
			    (clear-slot-pad)
			    (return-from
			      read-g2-ok-file-entity-just-for-users nil)))
		 (break-out (constant-text-of-rule-broken
			      &optional no-line-numbers-flag)
		   `(progn
		      (error-broke-rule-reading-ok-file
			,constant-text-of-rule-broken ,no-line-numbers-flag)
		      (done))))
      (loop doing
	(reclaim-contour-of-ok-file-tokens)
	(multiple-value-bind (s v1 v2) (read-statement-from-ok-file)
	  (declare (ignore v2))
	  (case s
	    (:eof (return nil))
	    (:begin-entity
	     (cond ((symbol-token-match #w"machine" v1)
		    (skip-ok-statements-until-end-of-entry #w"machine"))
		   ((symbol-token-match #w"user" v1)
		    (read-user-ok-file-entry-for-updates))
		   (t (break-out (undefined-entry-type-ok-message))))) ;#18
	    (:end-entity
	     (unless (symbol-token-match #w"g2-ok-file" v1)
	       (break-out (wrong-label-on-file-level-end-statement-ok-message)))) ;#23
	    (:attribute ) ;; no-op since there are no file-level attributes yet
	    (t  ;; i.e. :illegal, but this compensates for neglectfullness
	     (break-out (unknown-problem-parsing-file-ok-message))))))))) ;#24



(defun skip-ok-statements-until-end-of-entry (string-for-entry-type)
  (with-contour-of-ok-file-tokens ()
    (macrolet ((done () '(progn
			    (clear-slot-pad)
			    (return-from
			      skip-ok-statements-until-end-of-entry nil)))
	       (break-out (constant-text-of-rule-broken
			    &optional no-line-numbers-flag)
		 `(progn
		    (error-broke-rule-reading-ok-file
		      ,constant-text-of-rule-broken ,no-line-numbers-flag)
		    (done)))
	       (slot (name)
		 `(slot-of-slot-pad
		    ,name
		    slot-pad-descriptions-of-user))
	       (slot-text (name)
		 `(text-of-ok-file-token (slot ,name))))
      (loop doing
	(reclaim-contour-of-ok-file-tokens)
	(multiple-value-bind (s v1 v2) (read-statement-from-ok-file)
	  ;(format t "~&s = ~a  v1 = ~a  v2 = ~a~%" s v1 v2)
	  (declare (ignore v2))
	  (case s
	    (:eof (break-out (reached-eof-while-inside-an-entry-ok-message))) ;#45
	    (:begin-entity
	     (break-out (entry-started-while-still-inside-entry-ok-message))) ;#46
	    (:end-entity
	     (if (symbol-token-match string-for-entry-type v1)
		 (return nil)
		 (break-out (wrong-label-on-file-level-end-statement-ok-message)))) ;#23
	    (:attribute )  ;; ignore the content of the entry
	    (:illegal (break-out (syntax-error-in-attribute-value-ok-message))) ;#35
	    (t ;; compensate for unchecked changes in read-statement's return options
	     (break-out (unknown-problem-parsing-file-ok-message)))))))))



(defun read-user-ok-file-entry-for-updates ()
  (with-contour-of-ok-file-tokens ()
    (macrolet ((done () '(progn
			    (clear-slot-pad)
			    (return-from
			      read-user-ok-file-entry-for-updates nil)))
	       (break-out (constant-text-of-rule-broken
			    &optional no-line-numbers-flag)
		 `(progn
		    (error-broke-rule-reading-ok-file
		      ,constant-text-of-rule-broken ,no-line-numbers-flag)
		    (done)))
	       (slot (name)
		 `(slot-of-slot-pad
		    ,name
		    slot-pad-descriptions-of-user))
	       (slot-text (name)
		 `(text-of-ok-file-token (slot ,name))))
      (clear-slot-pad)
      (loop doing
	(multiple-value-bind (s v1 v2) (read-statement-from-ok-file)
	  ;(format t "~2%s = ~a  v1 = ~a  v2 = ~a" s v1 v2)
	  (case s
	    (:end-entity
	     (unless (symbol-token-match #w"user" v1)
	       (break-out (wrong-label-on-end-statement-ok-message))) ;#26
	     (return nil))
	    (:attribute
	     (unless (process-attribute-of-entity
		       slot-pad-descriptions-of-user v1 v2)
	       (break-out "")))  ; error recorded by process-attribute-of-entity
	    (t
	     (break-out (unknown-problem-parsing-entry-ok-message)))))) ;#2

      (let ((permitted-user-modes
	      (coerce-token-to-lisp
		(slot 'permitted-user-modes))))
	;; Type checking is almost sufficent.
	(unless permitted-user-modes
	  (break-out (no-user-modes-specified-ok-message))) ;#28
	(when (memq 'proprietary permitted-user-modes)
	  (break-out (proprietary-mode-specified-ok-message))) ;#29

	;; Proceed to commit the edit.
	(enter-authorized-user
	  (coerce-token-to-lisp (slot 'name))
	  (copy-text-string (slot-text 'password))
	  (copy-list-using-gensym-conses permitted-user-modes)
	  (coerce-token-to-lisp (slot 'password-validity))
	  nil )  ; This is an update, not an original
	
	(reclaim-gensym-list permitted-user-modes)))))










;;;; Authorizing Locked KBs

;;; The codes for a G2 that has been locked to a given KB must be different
;;; from those for a regular G2 on that same machine.  We achieve that by
;;; seripticiously adding one more item (one more bit ultimately) to the
;;; authorized products field of the OK information. This will spread through
;;; all of the elements of the codes and make them utterly different.
;;; N.b. the authorized-product `g1' has traditionally been reserved for
;;; identifying 'reduced' G2s such as we have here and has no other
;;; function at this time (10/99 ddm).

;;; `locked-to-kb?' is the variable that holds the cookie that goes into
;;; a locked kb and is non-nil iff the G2 is to be locked to a KB.

(defmacro should-the-codes-be-locked-down? ()
  `(when locked-to-kb?
     (push 'g1 authorized-products)))








;;;; Line Reformating


;;; This code implements that front door authorization of a G2.
;;; It is called by the code that reads in a machine's authorization
;;; when it encounters a one with this machine's ID.


;;; `New-reformat-line-from-left' is called from the OK file reader once
;;; for the first machine encountered that has the correct machine ID, or
;;; is a SITE id.

;;; It side effects the dynamic extent, either with error information or
;;; with a success flag.

(defun new-reformat-line-from-left (machine-id
				     code-1
				     code-2
				     code-3
				     code-4
				     code-5
				     authorized-products
				     authorized-kb-packages
				     expiration-date?
				     number-of-processes-authorized
				     maximum-number-of-concurrent-floating-telewindows-allowed
				     maximum-number-of-concurrent-floating-tw2-allowed
				     make-g2-secure?)
  (within-named-dynamic-extent* (reading-ok-file
				  success-of-ok-file-reader?)
    (macrolet ((debugging (level &rest args)
		 ;; Low numbers are more likely to print
		 (when t
		   `(when (<= ,level 10)
		      (format t "~&~S " 'new-reformat-line-from-left)
		      (format t ,@args)
		      nil))))
      (let*  ((modulus new-modulus))

	;; These error routines directly set the global that records the text
	;; of the error (see `error-broke-rule-reading-ok-file'). As a result
	;; these error reports will not include the line number where the error
	;; occurred, which is a good thing since that information would be
	;; misleading in this case.
	(macrolet ((note-error (error-text-string)
		     `(setf error-of-ok-file-reader?
			    ,error-text-string))
		   (note-error-2 (error-text-string)
		     `(note-error
			(twith-output-to-text-string
			  (tformat ,error-text-string)))))
	  (when (and
		  ;; It is completely filled in
		  machine-id
		  (not (shunned-machine-id-string-p machine-id)) ; note would be helpful! (frame
;   note needed, in addition)
		  code-1
		  code-2
		  code-3
		  code-4
		  code-5
		  ;; and the ok pertains to this machine
		  (or ;(and expiration-date? (machine-id-of-site-p machine-id))
		      (machine-id-of-site-p machine-id) ;; ddm 3/21/00
		      (let ((machine-ids
			      (get-local-machine-ids-as-gensym-list)))
			(prog1 (loop for id in machine-ids
				     thereis (normalized-string-equal id machine-id))
			  (reclaim-gensym-tree-with-text-strings machine-ids)))))
	    
	    (should-the-codes-be-locked-down?)
	    
	    (when (<=f (authorization-attempt-limit) (authoriation-attempt-counter))
	      (schedule-authoriation-counter-shutdown))
	    (let* ((keystring
		     (twith-output-to-text-string
		       (tformat "~a" machine-id)
		       (if (> chaining-refresh-version 3) ; null finger ("") used for 3.0 
			   (tformat "~a" chaining-refresh-list)
			   )))
		   (modularized-key	       
		     (modulo-string-hash keystring modulus))
		   (authorized-products-code
		     (compute-product-code authorized-products))
		   (checksum
		     (let ((code-1x
			     (if (>=f code-1 100)
				 code-1
				 (+f 394 (*f 185 code-1))))
			   (code-2x
			     (if (>=f code-2 100)
				 code-2
				 (+f 260 (*f 165 code-2))))
			   (code-3x
			     (if (>=f code-3 100)
				 code-3
				 (+f 111 (*f 64 code-3))))
			   (code-4x
			     (if (>=f code-4 100)
				 code-4
				 (+f 973 (*f 469 code-4)))))
		       (mod
			 (logxorf
			   (inner-multiply modularized-key code-3x)
			   (inner-multiply code-1x authorized-products-code)
			   (inner-multiply code-2x code-4x)
			   (inner-multiply
			     (or expiration-date? 0)
			     (or expiration-date? 0))
			   (if number-of-processes-authorized
			       (inner-multiply
				 code-3x
				 number-of-processes-authorized)
			       0)
			   (if number-of-processes-authorized
			       (inner-multiply
				 code-4x
				 (ashf number-of-processes-authorized 8))
			       0)
			   (inner-multiply
			     code-1x
			     maximum-number-of-concurrent-floating-telewindows-allowed)
			   (inner-multiply
			     code-2x
			     (ashf maximum-number-of-concurrent-floating-telewindows-allowed
				   8))
			   (inner-multiply
			     code-3x
			     maximum-number-of-concurrent-floating-tw2-allowed)
			   (inner-multiply
			     code-4x
			     (ash maximum-number-of-concurrent-floating-tw2-allowed
				  12))) 
			 modulus))))

	      (cond
		;; 1st: is this ok except for an invalid expiration date?
		((and (=f checksum code-5)		; means its ok otherwise
		      expiration-date?		; has a specified exp. date
					; the rest checks it; if bad,
					;   it notifies the user
					;   and returns true; otherwise,
					;   it return nil.
		      (let ((date (get-universal-date)))
			(multiple-value-bind (start-date? end-date)
			    (if (authorization-is-interval-p expiration-date?)
				(decode-authorization-interval expiration-date?)
				(values nil expiration-date?))
;			  (cond
;			    (start-date?
;			     (when (<f date start-date?)
;			       (note-error (authorization-not-valid-until-ok-message start-date)))) ;#37
;			    ((> date end-date)
;			     (note-error (authorization-expired-ok-message end-date))) ;#38
;			    (t nil))
			  ;; This should replace the following If statement once
			  ;; the capability to take arguments is incorporated.
			  
			  (if (or (if start-date? (<f date start-date?))
				  (>f date end-date))
			      (let ((notification-text-string
				      (twith-output-to-text-string
					(twrite-string "The authorization for this machine ")
					(twrite-string
					  (if (>f date end-date)
					      "has not been valid since "
					      "will not be valid until "))
					(multiple-value-bind (day month year)
					    (decode-universal-date
					      (if (>f date end-date)
						  end-date
						  start-date?))
					  (print-decoded-date day month year))
					(twrite-string "."))))
				(note-error notification-text-string)
				t)))))
		 ;; T stops COND.
		 )

		;; 2nd: is this OK except for running on a machine with too many G2
		;; processes already?  (Note A)
		((and (=f checksum code-5)
		      (not (unlimited-number-of-g2-processes-permitted-p 
			     number-of-processes-authorized))
		      (progn 
			(unless (per-process-license-registered-and-listener-activated-p)
			  (setf (per-process-license-registered-and-listener-activated-p) 
				(and (register-licensed-product 
				       (g2-image-product)
				       (g2-image-option authorized-products))
				     (license-listen))))
			   #-development
			   (cond
			     ((not (per-process-license-registered-and-listener-activated-p))
			      (note-error-2
				(g2-not-authorized-because-cannot-register-process-license-message))
			      t)
			     ((new-licensed-g2-process-permitted-p 
				number-of-processes-authorized
				authorized-products)
			      nil)
			     (t (note-error-2
				  (g2-not-authorized-because-fails-process-count-message))
				t))
			#+development
			nil)))		;as above, the t exits the cond and the nil falls through

		;; 3rd: is this ok for enterprise version?
		((and (g2-enterprise-p) (not (memq 'ent authorized-products))
		      (let ((notification-text-string
			      (twith-output-to-text-string
				(twrite-string "The authorization for the Enterprise version has not been valid."))))
			(note-error notification-text-string)
			t)))
		((and (not (g2-enterprise-p)) (memq 'ent authorized-products)
		      (let ((notification-text-string
			      (twith-output-to-text-string
				(twrite-string "The authorization for the Standard version has not been valid."))))
			(note-error notification-text-string)
			t)))

		((=f checksum code-5)
		 ;; should screen out the majority of innocent typos
		 (set-list-contents
		   format-structure-description
		   code-5                          ; 0th
		   chaining-refresh-list           ; 1st
		   (-f code-4 code-5)              ; 2nd
		   (make-array-from-strings machine-id chaining-refresh-list) ; 3rd
		   (make-array 8)                  ; 4th
		   (copy-text-string machine-id)   ; 5th
		   code-1                          ; 6th
		   code-2                          ; 7th
		   code-3                          ; 8th
		   code-4                          ; 9th
		   
		   ;; codes for authorized products, expiration date, and number of processes
		   (let ((cons (nth 10 format-structure-description)))
		     (setf (car cons) authorized-products-code)
		     cons)	                   ; 10th
		   
		   expiration-date?                ; 11th
		   
		   ;; Only package authorizations that are valid should be installed.
		   (copy-tree authorized-kb-packages)   ; 12th

		   number-of-processes-authorized                              ; 13th
		   maximum-number-of-concurrent-floating-telewindows-allowed   ; 14th
		   maximum-number-of-concurrent-floating-tw2-allowed           ; 15th
		   )

		 (unless (g2-authorized-p) 
		   (when (and ;;expiration-date? ddm 3/21/00
			      (machine-id-of-site-p machine-id))
		     (c-nsleep machine-id)))

		 ;; Save the machine ID used (one of the possible many):
		 (set-local-machine-id-in-use machine-id) ; (MHD 7/4/00)

		 (setf text-representation-of-our-ok-object
		       (generate-simulation-of-printing-ok-frame))
		 
		 (setf authorized-products-of-this-machine 
		       (loop for visible-product in authorized-products
			     collect visible-product))

		 (setf floating-telewindows-limit
		       maximum-number-of-concurrent-floating-telewindows-allowed)
		 (schedule-tw-modernization-tasks-if-necessary)

		 (setq floating-tw2-limit
		       maximum-number-of-concurrent-floating-tw2-allowed)

		 (clear-authoriation-attempt-counter)
		 (setf success-of-ok-file-reader? t)
		 (when (nupec-really-authorized-p)
		   (authorize-nupec))

		 (maybe-initialize-asian-languages)

		 ;; When authorization occurs for the first time, G2 is made secure if the
		 ;; OK item is set to do so.
		 (when make-g2-secure?
		   #+development
		   (when (and (g2-authorized-p)
			      (not (g2-secure-p)))
		     (notify-user-at-console
		       "Ignoring unimplementable request to make secure an already authorized G2."))
		   (unless (g2-authorized-p)
		     (make-g2-secure)))
		 (unplant-seed)

		 (setq unevaluated-expression t))

		
		((g2-authorized-p)
		 (increment-authoriation-attempt-counter)
		 (note-error-2
		   (authorization-incorrect-when-already-authorized-ok-message))) ;#39
		
		(t
		 (increment-authoriation-attempt-counter)
		 ;; Extend-grace-period-on-ok-files-if-appropriate is being
		 ;; removed from the sources.  (ghw 3/5/96)
		 (note-error-2
		   (authorization-incorrect-ok-message)))) ;#40

	      (reclaim-text-string keystring))))))))

;; Note A: jh, 11/14/91.  Added G2 per-process authorization here and removed it
;; from run-ab.  This had caused G2 to exit with a failed process count
;; whenever the OK file was not found.  Now it gives the users a chance
;; to authorize manually.  While I was at it, I made messages like "OK
;; to run G2" into scrambled strings, to confound a UU looking for
;; constant strings in the C image.







;;;; Entry Point for OK file Reading.

;;; OK files are read for one of two purposes. (1) At startup to see
;;; whether the machine G2 is being launched on is properly authorized,
;;; and (2) when the G2 is secure, to update the information on its
;;; authorized users while the G2 is running. The startup case is
;;; done here as the main part of `authorize-ab'.  The update is done
;;; via `reinstall-authorized-users'.


;;; `Authorize-ab'  returns a boolean to it's caller, run-ab,
;;; who then exit's g2 if that's ok.  Note this is called before
;;; the class system is even functional.

(defun-allowing-unwind authorize-ab ()
  (protected-let*
      ((pathname (get-appropriate-ok-pathname)
       ) ;SS_G2L - when loading with SBCL, no info is available about g2.ok location
       (current-machine-ids-of-g2-ok-file?
	 (get-local-machine-ids-as-gensym-list)
	 (reclaim-gensym-tree-with-text-strings current-machine-ids-of-g2-ok-file?))       
       (trouble?
	 (if (g2-authorized-p)
	     nil
	     (cond
	       (pathname
		(read-ok-file pathname))
	       (t
		#w"No OK file was found."))))
       (message?
	 (when trouble?
	   (make-authorization-file-status-string
	     pathname
	     current-machine-ids-of-g2-ok-file?))))
    
    (cond
      (trouble?
       (let ((*write-console-p* t))
		(notify-user-at-console "~%~%---~%~A~%~A~%" trouble? message?))
       (reclaim-text-string message?)
       nil)
      ((g2-authorized-p)
       (set-authorizing-OK-pathname pathname)
       (when (eq verbosity-level 'verbose)
	 (let ((ok-file-namestring (gensym-namestring pathname)))
	   (let ((*write-console-p* t))
		(notify-user-at-console 
			"~%[~A ~s]~%"
			(using-g2-ok-file-message)
			ok-file-namestring))
	   (reclaim-text-string ok-file-namestring)))

       (let ((*write-console-p* t))
		(notify-user-at-console "~%~A~%" (ok-to-run-g2-message)))
       (when (g2-secure-p)
	 (check-password-setup-and-notify-user-if-necessary))
       t)
      (t
       #+development
       (error "Failed to authorize, but no error was generated.")
       nil))))


;;; The code below was added in 1.17 to "(f)ix some narrow/wide string leaks.".
;;; Then it was marked obsolete in 1.33 without any comment (that rev. was
;;; about passwords.) I'm retaining a record of it here because it
;;; involves a subtlety about character set usage that might well come
;;; back and haunt us.  The correspondences for where these go in
;;; Authorize-ab are supposed to be obvious.  (ddm 6/13/97)
;;; Notify-user-at-console now handles all of this sort of hair.
;
;        (let* ((wide-string (export-text-string
; 			       trouble?
; 			       'notify-user-if-possible-via-console)
; 			     'notify-user-if-possible-via-console))
; 	      (narrow-string (wide-string-to-string wide-string)))
; 	 (format *terminal-io* "~%~A~%" narrow-string)
; 	 (reclaim-wide-string trouble?)
; 	 (reclaim-wide-string wide-string)
; 	 (reclaim-gensym-string narrow-string))
;
;        (let* ((wide-string (export-text-string
; 			     (ok-to-run-g2-message)
; 			     'notify-user-if-possible-via-console))
; 	      (narrow-string (wide-string-to-string wide-string)))
; 	 (format *terminal-io* "~%~A~%" narrow-string)
; 	 (reclaim-wide-string wide-string)
; 	 (reclaim-gensym-string narrow-string))







;;;; Epilog to Text OK File Reading.


;; Issues
;; review to be sure terms are acceptable in G2's impl. generally.
;; authorized-optional-modules !!! not authorized-products
;; Writing ok files is amazingly slow - effects site auth generator.
;; OK file lookup doesn't report missing, i.e. if env. or cmd line
;;   switch offers OK file that doesn't exist we should squak!

;; Dike out the old code.
;; Do not authorized a secure G2 if he has failed to define any users.
;; revise choose-keytab, and finger
;; Custom error message for kb vs text and visa versa.
;; Get a version # into the file format.
;; system procedure to read an OK file while running, et. al.


;;; `Generate-simulation-of-printing-ok-frame' is used to simulate
;;; functionality in G2 V3.  There a call was made to print the OK
;;; object just after G2 was authorized.  That printed text allowed
;;; the KB author to learn everything we knew about the authorization.

;;; This routine generates similar text.  It is not identical.  I do
;;; not generate the first few lines.  The table header, notes, and
;;; item configuration are not emitted.  The slot that was called
;;; "names" is here called "name".  Rather than print the five codes
;;; one to a line each, here we show a single attribute with the
;;; list of five codes.

(defun generate-simulation-of-printing-ok-frame ()
  (within-named-dynamic-extent* (reading-ok-file)
    (twith-output-to-text-string
      (write-pad-slot #w"name")
      (write-pad-slot #w"machine-id")
      (write-pad-slot #w"authorized-products") ; 
      (write-pad-slot #w"expiration-date?")
      (write-pad-slot #w"authorization")
      (write-pad-slot #w"authorized-kb-packages")
      (write-pad-slot #w"number-of-processes-authorized")
      (write-pad-slot
	#w"maximum-number-of-concurrent-floating-telewindows-allowed")
      (write-pad-slot
	#w"maximum-number-of-concurrent-floating-tw2-allowed"))))

(defun write-pad-slot (slot-name)
  (within-named-dynamic-extent* (reading-ok-file
				  slot-pad-of-ok-file-reader)
    (let* ((index-of-slot
	     (position slot-name slot-pad-descriptions-of-machine-authorization
		       :key #'first
		       :test
		       (if symbol-token-match-should-be-case-sensitive-p
			   #'string=w
			   #'string-equalw)))
	   (type-description
	     (nth index-of-slot
		  slot-pad-descriptions-of-machine-authorization)))
      (tformat "  ~A:" slot-name)
      (twrite-ok-token
	(svref slot-pad-of-ok-file-reader index-of-slot)
	(atom type-description))
      (tformat ";~%"))))

(defun twrite-ok-token (token simple?)
  (let ((value (value-of-ok-file-token token)))
    (case (kind-of-ok-file-token token)
      (:integer (tformat " ~D" value))
      (:string (tformat " ~S" (text-of-ok-file-token token)))
      (:symbol
       (cond
	 ((null value)
	  (tformat " none"))
	 (t
	  (tformat " ~S" value))))
      (:list
       (cond
	 ((null value)
	  (tformat " none"))
	 (t
	  (tformat " (")
	  
	  (loop
	    with long? = (<f 5 (length value))
	    for element in value
	    when long? do (tformat "~%          ")
	    do (twrite-ok-token element simple?))
	  (tformat " )")))))))




#+nil
(progn ;; Setup for testing.
  (breakon 'service-workstations)
  (replace-command-line "g2 -nowindow")
  (launch-ab))





;;;; The Texts for the OK Parsing Messages

;;; This set of messages was initially created by clipping the texts from
;;; the place in the code where they appeared and making that literal text
;;; the 2d argument of these calls to define-ok-message. The fact that in
;;; some cases the string is a control string with formatting characters
;;; and in other cases a final string is ignored for the timebeing. 

;;; This was a simple, first-pass treatment of the problem that avoided
;;; the ultimate task of either modifying the choice of macro to use or
;;; (better) rationalizing the pattern of the user of the string to uniformly
;;; take one or the other sort of string.



;;; messages posted from `with-reading-ok-file'

;; #1
(define-ok-message could-not-open-stream
    "OK file must exist and be readable.")

;; #2
(define-ok-message no-filename-provided
    "OK-file-path must specify a valid file name")



;;; messages posted from `read-token-from-ok-file'

;; #3
(define-ok-message hyphen-not-followed-by-another-hyphen
     "A minus sign can only introduce a comment.")

;; #4
(define-ok-message character-cannot-start-token
   "Only certain characters may start a new token.")


;;; messages posted from `read-string-from-ok-file

;; #5
(define-ok-message string-too-long
    "Strings must be less than 60 characters.")

;; #6
(define-ok-message illegal-character-in-string
    "Strings may not contain atsign, tilde, backslash or line terminators.")



;;; messages posted from `read-symbol-from-ok-file

;; #7
(define-ok-message symbol-too-long
    "Symbols must be less than 60 characters.")



;;; messages posted from `read-integer-from-ok-file '

;; #8
(define-ok-message integer-too-long
    "Integers must be less than 40 digits.")

;; #9
(define-ok-message integer-contains-non-digit-character
    "Integers contain only digits.")



;;; messages posted from `read-list-from-ok-file'

;; #10
(define-ok-message too-many-elements-in-list
    "Lists must contain less than 60 elements")



;;; messages posted from `read-statement-from-ok-file

;; #11
(define-ok-message eof-in-middle-of-statement
    "Premature end of file.")

;; #12
(define-ok-message fourth-element-of-statement-not-a-semicolon
    "Attribute value pairs must end with a semicolon")

;; #13
(define-ok-message illegal-attribute-value
    "Attribute values must be integers, lists, or symbols.")
;;; This is the equivalent to #13 as straight (not i18n ready) code that will
;;; let me feed it an argument as part of 5.0rev4 so we can get clear error
;;; messages without needed to already implement the general facility.
(defun illegal-attribute-value-ok-message-1 (attribute-token bad-token)
  (twith-output-to-text-string
    (tformat "Bad type for the value of the attribute ~a: ~a~
           ~%Attribute values must be integers, lists, or symbols."
	     (text-of-ok-file-token attribute-token)
	     (kind-of-ok-file-token bad-token))))


;; #14
(define-ok-message unknown-problem-parsing-statement
    "Cannot parse statement.")



;;; messages posted from `read-ok-file

;; #15
(define-ok-message sanity-check-on-initial-characters-of-file
    "The first N characters of file must be \"begin g2-ok-file\"." )

;; #16
(define-ok-message header-for-file-entry-missing
    "The file must contain one g2-ok-file entity")

;; #17
(define-ok-message no-authorization-found-for-this-machine-multiple-entries
    "None of the entries in this authorization file has a machine id that matched this machine"
;    "There was no entry in the authorization file with a machine id that ~
;     matched this machine"
;    "OK file must contain a machine authorization for this machine."
    )

;; #17a
(define-ok-message no-authorization-found-for-this-machine-one-entry
    "The machine id in the authorization file does not match the id for this machine.")


;;; messages posted from `read-g2-ok-file-entity

;; #18
(define-ok-message undefined-entry-type
    "Unexpected element found inside of g2-ok-file-entity.")

;; #19
(define-ok-message file-attribute-not-initial
    "Entity attributes must appear before subentities.")

;; #20
(define-ok-message undefined-file-attribute
    "Only file-format-version attributes may appear in g2-ok-files.")

;; #21
(define-ok-message file-format-attribute-duplicated
    "Attributes may only appear once.")

;; #22
(define-ok-message file-format-value-not-an-integer
    "Attribute must be an integer.")

;; #22a
(defun file-version-higher-than-image-version-ok-message-1 (image-version ok-version)
  ;; This will leak since it's going through a formalism that assumes it's dealing
  ;; with a constant string but we're building the string afresh each time. On the
  ;; other hand we don't care since the G2 this runs in is getting shut down momentarily
  ;; since this is a concommitant of not being authorized.
  (twith-output-to-text-string
    (tformat "This G2 can only read OK files in version ~a format.~
            ~%The OK file being loaded is in version ~a format and is incompatible~
            ~%because it contains attributes or codes that your G2 will not understand."
	     image-version ok-version )))

;; #23
(define-ok-message wrong-label-on-file-level-end-statement
    "The type given on begin and end must match.")

;; #24
(define-ok-message unknown-problem-parsing-file
    "File must be parsable.")

;; #25
(define-ok-message no-machine-authorization-in-file
    "OK file must contain at least one machine authorization.")



;;; messages posted from `read-user-ok-file-entry

;; #26
(define-ok-message wrong-label-on-end-statement
    "The type given on begin and end must match.")

;; #27
(define-ok-message unknown-problem-parsing-entry
    "File syntax must be correct.")

;; #28
(define-ok-message no-user-modes-specified
    "Users must have some permitted user-modes.")

;; #29
(define-ok-message proprietary-mode-specified
    "Proprietary is not a user-mode.")



;;;messages posted from `read-machine-ok-file-entry

;; #30
(define-ok-message machine-id-missing
    "A machine-id attribute is required.")

;; #31
(define-ok-message authorization-missing
    "A authorization attribute is required.")

;; #32
(define-ok-message shunned-machine-id
    "The machine ID must meet certain rules.")

;; #33
(define-ok-message from-date-earlier-than-to-date
    "The date range must be reasonable.")



;;; messages posted from `process-attribute-of-entity

;; #34
(define-ok-message unrecognized-attribute
    "Illegal attribute name."
;    "Only legal attributes may appear in entities."   -original
    )
(defun unrecognized-attribute-ok-message-1 (name)
  (twith-output-to-text-string
    (tformat "Unknown attribute: \"~a\"" (text-of-ok-file-token name))))

;; #35
(define-ok-message syntax-error-in-attribute-value
    "Attribute value is not right.")
(defun syntax-error-in-attribute-value-ok-message-1 (name value correct-type)
  (twith-output-to-text-string
    (tformat "The value ~a is the wrong type for the attribute ~a.~
            ~%It should be of type ~a"
	     (value-of-ok-file-token value)
	     (text-of-ok-file-token name)
	     correct-type)))

;; #36
(define-ok-message attribute-appears-more-than-once
    "Duplicate attributes are illegal.")
(defun attribute-appears-more-than-once-ok-message-1 (name)
  (twith-output-to-text-string
    (tformat "This instance of attribute ~a is a duplicate" (text-of-ok-file-token name))))


;; These take arguments. See above
;;; #37
;(define-ok-message authorization-not-valid-until
;    "The OK for this machine will not be valid until <date>" start-date)
;
;;; #38
;(define-ok-message authorization-expired
;    "The OK for this machine has not been valid since <date>" end-date)

;; #39
(define-ok-message authorization-incorrect-when-already-authorized
    "You were already authorized.~%You are still authorized.~%Meanwhile the authorization found in the OK file was wrong.")

;; #40
(define-ok-message authorization-incorrect
    "The authorization is not correct. Please check it and try again.")



;;; message posted from `kick-out-unauthorized-floating-telewindows'

;; #41
(define-ok-message number-of-floating-telewindows-limit-exceeded
    "Limit on number of Floating Telewindows licenses ~
     exceeded.  Closing unauthorized connection(s) immediately.")



;;; message posted from `kick-out-unauthorized-runtime-telewindows'

;; #42
(define-ok-message not-permitted-to-connect-to-development-g2
    "A connection to ~a Telewindows is being closed immediately ~
    because it is not permitted to connect to a Development version of G2.")



;;; message posted from `new-analyze-authorized-packages'

;; #43
(define-ok-message incorrect-authorization-for-package
    "Bad package authorization.")
;; Cries out for an argument. E.g.
;    "The authorization for the <name> package is incorrect."
;  package-name)


;;; message posted from Read-machine-ok-file-entry

;;#44
(define-ok-message wrong-number-of-authorization-codes
    "Wrong number of codes in authorization field. There should be five.")



;;; messages posted from skip-ok-statements-until-end-of-entry

;;#45
(define-ok-message reached-eof-while-inside-an-entry
    "Premature end of file: some entry was not terminated")

;;#46
(define-ok-message entry-started-while-still-inside-entry
    "Unexpected start of an entry: previous entry was not terminated")






;;; There's a bunch in `warn-of-license-expiration'

(define-ok-message license-on-this-machine-has-expired
    "The license to run G2 on this machine has expired.~%")

(define-ok-message licence-on-this-machine-expires-today
    "The license to use G2 on this machine expires today.~% G2 will not run after today.~%~%")


;; This whole set takes arguments. The source code contains the call
;; as a commented-out line that we can swap back in once the argument
;; capability is working
;(define-ok-message licence-on-this-machine-expires-this-week
;    "The license to use G2 on this machine expires on <date>. ~
;     .~%G2 will not run after this date.~%~%"
;  date)
;
;(define-ok-message packages-not-authorized
;    "The following application packages are not authorized:~%~
;     <list-of-names>"  ; check that.  Code uses Print-list-without-message
;  not-authorized)
;
;(define-ok-message packages-with-expired-authorizations
;    "The following application packages have expired authorizations:~%_
;     <list-of-names>"
;  expired)
;
;(define-ok-message packages-with-further-authorizations
;    "The following application packages have authorizations with future start dates:~%"
;  post-dated)
;
;(define-ok-message packages-with-authorizations-expiring-in-a-week
;    "The following application packages have authorizations that will expire within a week:~%"
;  will-expire)





;; Tests to do:
;; some texts in league with `print-list-without-message'
;; some (copies?) in `warn-upon-start-or-resume'
;; the scrambled strings 

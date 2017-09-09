;; -*- mode: lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SEQUENCES1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin


;;;; Forward References



(declare-forward-reference loading-kb-p variable)

(declare-forward-reference		; Telewindows only
  abort-telewindows-for-protocol-out-of-synch-case-6 function)
(declare-forward-reference		; Telewindows only
  abort-telewindows-top-level function)


;;; This deliberately misnamed file contains authorization code common
;;; to both G2 and Telewindows.


;;; The variable `verbosity-level' is used by both G2 and Telewindows 
;;; to control the amount of status information to print.  It can be
;;; one of the following values:
;;;
;;;    NORMAL
;;;    SILENT
;;;    VERBOSE
;;;
;;; In G2, NORMAL and SILENT are the same; and VERBOSE now means just
;;; to print information about which ok file was used for authorization.

(def-system-variable verbosity-level sequences1 
  (:funcall initialize-verbosity-level))

(defun initialize-verbosity-level ()
  (cond
    ((getf command-line-arguments 'verbose)
     'verbose)
    ((getf command-line-arguments 'silent)
     'silent)
    (t 'normal)))


;;;; Per-process Licensing

;; jh, 2/7/91.  
;; redesigned, jh & blm, 8/13/91.

;;; The idea behind per-process licensing is to count the number of G2 processes
;;; running on a given machine and only permit a new G2 to launch if that number
;;; is within licensed limits for that CPU.

;;; The per-process licensing code attempts to make things difficult for an
;;; `unscrupulous user' (abbreviated `UU') attempting to run G2 processes outside
;;; of licensed limit, yet tries to keep things transparent to the `naive victim'
;;; (henceforward `NV').  NV should experience no sudden shutdowns or misbehavior
;;; as a result of these licensing precautions.  UU should not be able to break
;;; the per-process check without clearly demonstrating intent to steal, by doing
;;; things like changing the binary image or altering process parameters with
;;; system-manager privileges.

;;; The interface with per-process licensing internals consists of six macros.
;;; The interface uses no functions, in order to make it slightly more difficult
;;; for UU to detect the parts of the code that deal with this authorization.
;;; In the macros that take arguments, the arguments system and option are
;;; scrambled constant strings.  The possible system and option arguments are:
;;;
;;; system: "G2"
;;;   option: "DEVELOPMENT"
;;;           "RUNTIME"
;;;           "RESTRICTED USE"
;;;           "EMBEDDED"
;;;
;;; system: "TW"
;;;   option: "TW" [no subordinate options as of 8/12/91]

;;; A brief description of the macros follow.

;;; register-licensed-product(system option)
;;; To be called once, when G2 or TW is launched, and before license-listen() is
;;; called.

;;; license-listen()
;;; To be called once, when G2 or TW is launched.

;;; maximum-licensed-processes (system option)
;;; Returns the largest number of processes allowed to run on this machine at a
;;; single time.

;;; new-licensed-process-permitted-p (system option)
;;; Returns non-nil if it can be determined that a new process is allowed to run
;;; on this machine, nil otherwise.  New-licensed-process-permitted-p should be
;;; called only after license-listen is called.

;;; accept-process-license-queries()
;;; To be called repeatedly, whenever G2 or TW processes its network requests (in
;;; process-icp-sockets, as of 8/12/91).

;;; close-license-listener()
;;; To be called once, when G2 or TW exits.  If G2 or TW exits without calling
;;; this function, the process (in UNIX) or the machine itself (in VMS) could get
;;; clogged with unusable listeners.  (As of 8/13/91, this is called in
;;; shut-down-ab-process, which is used by both TW and G2.)

;;; do-per-process-checks(system-symbol)
;;; System-symbol is unevaluated, and is one of g2 or tw.  This is the top-level
;;; call.  It counts the number of processes on the machine with the same option
;;; and exits G2 if the licensed number would be exceeded.

;;; The macro def-scrambled-constant-string defines a macro that expands to code
;;; for reconstructing a string.  This is an alternative to keeping possibly
;;; revealing string constants inside the Lisp world for UU to notice.
;;; Def-scrambled-constant-string is related to hide-constant-string in INT1 but
;;; uses a different encoding scheme and generates different top-level forms.
;;; Having more than one scrambler of text constants is probably not a bad idea,
;;; since it makes the code slightly less intelligible to UU, who probably
;;; expects a single encoding scheme.

(defconser sequence SEQUENCES1)

(defmacro def-scrambled-constant-string (string-name string)
  (when (and (constantp string)
	     (> (if (stringp (eval string))
		    (length (eval string))
		    (text-string-length (eval string)))
		243))
    (warn "The constant string named ~a is too long."
	  string-name))
  (let ((string-name-maker
	 (intern (format nil "~a-MAKER" string-name))))
   `(progn
    (eval-when (:compile-toplevel)
    (defmacro ,string-name-maker ()
     ,(avoiding-variable-capture (string)
	`(let* ((text-string (if (text-string-p ,string) ,string (copy-text-string ,string)))
		(string-length (text-string-length text-string))
		(new-string
		  (tformat-text-string "~a1357acehstvxz" text-string))
		(sorted-string
		  (quicksort-text-string-alphabetically new-string))
		(string-chars
		  (remove-duplicates-in-text-string sorted-string))
		(constant-string-specs
		  (loop for index from 0 below (text-string-length string-chars)
			for this-char = (charw string-chars index)
			collect
			(loop for original-index 
			      from 0 below string-length
			      when (char=w this-char 
					   (charw text-string original-index))
				collect
				original-index
				  into index-characters
			      finally
				(return (concatenate
					  'vector
					  index-characters)))
			  into vector-elements
			finally
			  (return (concatenate 'vector vector-elements)))))
	   `(unscramble-constant-string
	      ,string-length
	      ,string-chars
	      (optimize-constant ,constant-string-specs)))))
    ) ; eval-when
    (defconstant ,string-name (,string-name-maker))
    (defmacro ,string-name () `,',string-name)
    )))

;; jh, 10/5/91.  Changed def-scrambled-constant-string to use managed conses
;; instead of a large constant tree.  The constant tree was breaking the compiles
;; of the Chestnut C translation on the HPs.  Michael suggests we consider the
;; simpler alternative of cons-hiding the constant string, but I am still wary of
;; leaving the bare string anywhere in the G2 image.  Furthermore, the scrambling
;; is not a performance problem since it only occurs after we know that
;; authorization has been violated.

;; The size of the expansion of a reference to the scrambled string is a
;; problem.  Anne now informs me that it takes 10 hours to compile some of the
;; functions containing scrambed strings.  This is likely due to the HP
;; optimizer attempting to analyze the inlined setf cars produced by
;; sequence-list.  jra, ac. 10/10/91.

;; jh, 1/3/92.  Changed def-scrambled-constant-string not to encode the string
;; indices as characters.  Some C compilers can't handle strange characters in
;; constant strings very well.

(defmacro unscramble-constant-string
	  (string-length string-chars string-specs) ; string-specs a vector of vectors
  `(transform-type-specification-2
     ,string-length
     ,string-chars
     ,string-specs))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun transform-type-specification-2 (string-length string-chars string-specs)
  (let ((new-string (obtain-text-string string-length)))
    ;; goes from gensym-string to text-string here! (MHD 2/5/96)
    (loop for index from 0 below (length string-specs)
	  for string-spec = (svref string-specs index)
	  for this-char = (charw string-chars index)
	  do (loop for spec-index from 0 below (length string-spec)
		   for new-index = (svref string-spec spec-index)
		   do (setf (charw new-string new-index) this-char)))
    new-string))
) ; eval-when

(defmacro def-secret-string-for-system (name &rest system-string-pairs)
  (let ((constant-name-list
	  (loop for (system nil) in system-string-pairs
		collect (intern (format nil "~a-~a-CONSTANT" system name))))
	(scrambled-name-list
	  (loop for (system nil) in system-string-pairs
		collect (intern (format nil "~a-~a" system name)))))
    `(progn
       ,@(loop for constant-name in constant-name-list
	       for scrambled-name in scrambled-name-list
	       for (nil string) in system-string-pairs
	       append
	       `((defvar-for-macro ,constant-name 
		   ,string)
		 (def-scrambled-constant-string ,scrambled-name 
		   ,constant-name)))
       (defmacro ,name (system)
	 (case system
	   ,@(loop for scrambled-name in scrambled-name-list
		   for (system nil) in system-string-pairs
		   collect `(,system '(,scrambled-name)))
	   (otherwise (error "Unknown system name ~a in ~a"
			     system
			     ',name)))))))
		   


(def-scrambled-constant-string g2-product "G2")

;;; jh, 10/21/94.  Dorothy tells me that the price list calls the following four
;;; things `licensing options', that they are all mutually exclusive, and that a
;;; `development licensing option' (a.k.a. `development G2') is a fully
;;; functioning G2 and is the default.  She further tells me that the terms
;;; `online G2' and `offline G2' are an entirely separate axis in the
;;; two-dimensional licensing matrix, and have to do with excluding or including
;;; facilities like GSI, ICP, and GFI.  Per-process limit do not take online or
;;; offline into account.  [This is a three-semi comment because it contains the
;;; only known definition of licensing options, yet it is dated because
;;; licensing information changes frequently.]

(def-scrambled-constant-string g2-runtime-option        "RUNTIME")
(def-scrambled-constant-string g2-restricted-use-option "RESTRICTED USE")
(def-scrambled-constant-string g2-embedded-option       "EMBEDDED")
(def-scrambled-constant-string g2-development-option    "DEVELOPMENT")


(def-scrambled-constant-string tw-product "TW")

(def-scrambled-constant-string tw-runtime-option        "RUNTIME")
(def-scrambled-constant-string tw-restricted-use-option "RESTRICTED USE")
(def-scrambled-constant-string tw-embedded-option       "EMBEDDED")
(def-scrambled-constant-string tw-development-option    "TW")

;; In 4.0 Beta Phase 2, we are going from having one Telewindows License that
;; could connect to any kind of G2 to having the same number as in G2 --
;; runtime, restricted-use, embedded, and development, which can only connect
;; to that level of G2 or lower.
;;
;; Prior to 4.0 Beta Phase 2, we just had this one
;; 
;;   (def-scrambled-constant-string tw-option "TW")
;;
;; This effectively corresponds to our modern day development option, and so
;; this is replaced by tw-development-option, but the exact string that gets
;; hashed is not going to be "DEVELOPMENT", but rather "TW", as it was before.
;; The more logical stamp to use not being used because that would allow
;; previousl versions of TW running on the same machine to not be taken into
;; account for purposes of counting licenses.  That would allow you to run a
;; machine authorized for 10 Telewindows to run 10 4.0 Beta Phase 2 Telewindows,
;; and 10 4.0 Beta Phase 1 Telewindows.  We don't want that.  I.e., this stamp
;; doesn't fit the pattern for historical reasons; making it fit would be a
;; security loophole. (MHD 1/27/95)


(DEFMACRO g2-image-product ()
  `(g2-product))

(defmacro tw-image-product ()
  `(tw-product))

(defmacro memq-case (elements &body clauses)
  (avoiding-variable-capture (elements)
    `(cond
       ,@(loop for (unevaluated-element . actions) in clauses
	       collect
	       (if (memq unevaluated-element '(t otherwise))
		   `(t ,@actions)
		   `((memq ',unevaluated-element ,elements) ,@actions))))))

;; jh, 10/21/94. Changed g2-image-option to work before G2 actually becomes
;; authorized for a given licensing option.  Previously, it was always
;; defaulting to the development option.

(defmacro g2-image-option (authorized-products)
  `(memq-case ,authorized-products
     (runtime        (g2-runtime-option))
     (restricted-use (g2-restricted-use-option))
     (embedded       (g2-embedded-option))
     (otherwise      (g2-development-option))))

(defmacro tw-image-option (authorized-products)
  ;; Old:  (prior to 4.0 Beta Phase 2)
  ;;   `(tw-option) ;No subordinate options for TW as of 8/13/91.
  ;; -- no longer true
  ;; 
  ;; New:
  `(memq-case ,authorized-products
     (runtime        (tw-runtime-option))
     (restricted-use (tw-restricted-use-option))
     (embedded       (tw-embedded-option))
     (otherwise      (tw-development-option))))
  



;;; Top-level macros (to be used in run-ab in RUN)

;; jh, 1/15/92.  Changed the foreign functions called by the per-process licensing
;; code to devious names.  Even stripped images on the VMS contain function names,
;; so we don't want to give inquisitive UUs a chance to look at them.  This change
;; affects all platforms, just in case we encounter another one like VMS.

(def-gensym-c-function 
  update-frames-needing-icp-callback
  (:fixnum-int "g2ext_update_callback_frames") ;cc_register_licensed_product
  ((:string system)
   (:string option)))

;; jh, 11/11/91.  Added flag which is set the first time we register per-process
;; licensing information.  This is part of the fix which moves the per-process
;; licensing check from the wrong place (run-ab) to the right place
;; (reformat-line-from-left).

(declare-special-global unlimited-backtracking-in-internal-truth-maintenance-p)
(def-system-variable unlimited-backtracking-in-internal-truth-maintenance-p
		     SEQUENCES1
		     nil)
(defmacro per-process-license-registered-and-listener-activated-p ()
  `unlimited-backtracking-in-internal-truth-maintenance-p)



;; The macro register-licensed-product drops the text strings bound to system and
;; option.  Since this happens only once in the life of a process, it is
;; acceptable.

(defmacro register-licensed-product (system option)
  (avoiding-variable-capture (system option)
    `(if (=f (update-frames-needing-icp-callback ,system ,option) 1)
	 t
	 nil)))

;; This used to have a lispm vs. non-lispm behavior.  That's been removed now,
;; making this appear to be platform independent.  (MHD 11/21/94)




(def-gensym-c-function 
  reduce-implicit-process-sleep-tolerance
  (:fixnum-int "g2ext_reduce_sleep_tolerance") ;cc_license_listen
  ())

(defmacro license-listen ()
  `(/=f (reduce-implicit-process-sleep-tolerance) -1))
       

;; This used to have a lispm vs. non-lispm behavior.  That's been removed now,
;; making this appear to be platform independent.  (MHD 11/21/94)



(defmacro unlimited-number-of-g2-processes-permitted-p (number-of-processes)
  `(null ,number-of-processes))

(defmacro maximum-licensed-g2-processes ()
  `(or (nth 13 format-structure-description) 2))


							

(defmacro maximum-licensed-tw-processes ()
  `(or (nth 9 (second icon-list-notes)) 2))

(defmacro unlimited-number-of-tw-processes-permitted-p ()
  `(null (nth 9 (second icon-list-notes))))

(defmacro tw-authorized-products ()
  `(nth 10 (second icon-list-notes)))



(def-gensym-c-function
  frequently_typed_characters
  (:fixnum-int "g2ext_frequently_typed_chars") ;cc_count_licensed_processes
  ((:string system)
   (:string option)))



;; The macro count-licensed-processes drops the text strings bound to system and
;; option.  Since this happens only once in the life of a process, it is
;; acceptable.

(defmacro count-licensed-processes (system option)
  (avoiding-variable-capture (system option)
    `(frequently_typed_characters ,system ,option)))

;; This used to have a lispm vs. non-lispm behavior.  That's been removed now,
;; making this appear to be platform independent.  (MHD 11/21/94)



;; The macros new-g2-process-permitted-p and new-tw-process-permitted-p leak the
;; text strings obtained by calling xx-image-product and xx-image-option.  Since
;; this happens only once in the life of a process, it is acceptable.

;; jh, 10/6/91.  Changed new-licensed-g2-process-permitted-p and
;; new-licensed-tw-process-permitted-p to accept "no limit" in the OK object.
;; While I was at it, made the pre-authorization default in the secret places be
;; 0, not nil, since nil equates to unlimited processes.  I can imagine a clever
;; dbx hacker skipping authorization and then circumventing the occasional
;; authorization checks.  It makes things a bit harder if the per-process check
;; has to be skipped too.

(defmacro new-licensed-g2-process-permitted-p
    (number-of-processes authorized-products)
  `(or (unlimited-number-of-g2-processes-permitted-p ,number-of-processes)
       (< (count-licensed-processes
	    (g2-image-product)
	    (g2-image-option ,authorized-products))
	  ,number-of-processes)))

(defmacro new-licensed-tw-process-permitted-p (authorized-products)
  `(or (unlimited-number-of-tw-processes-permitted-p)
       (< (count-licensed-processes
	    (tw-image-product)
	    (tw-image-option ,authorized-products))
	  (maximum-licensed-tw-processes))))



(def-gensym-c-function rule-invocation-updates-needed-p
  (:fixnum-int "g2ext_invokation_updates_needed") ;cc_license_event_pending_p
  ())

(defmacro license_event_pending_p ()
  `(=f (rule-invocation-updates-needed-p) 1))


(def-gensym-c-function cache-deferred-rule-invocation-indices
  (:fixnum-int "g2ext_cache_deferred_rules") ;cc_accept_license_option_query
  ())

(defmacro accept-process-license-queries ()
  `(cache-deferred-rule-invocation-indices))

;; This used to have a lispm vs. non-lispm behavior.  That's been removed now,
;; making this appear to be platform independent.  (MHD 11/21/94)


(defun cache-deferred-rule-invocation-indices-function ()
  (accept-process-license-queries))

;; This used to have a lispm vs. non-lispm behavior.  That's been removed now,
;; making this appear to be platform independent.  (MHD 11/21/94)



(def-gensym-c-function shift-rule-ordering-heuristics
  (:fixnum-int "g2ext_shift_rule_ordering") ;cc_license_close_listener
  ())

;; The macro license-close-listener is defined too late to do any good, so we had
;; to transplant the devious name to PLATFORMS, where it is used.  Keep this here
;; for when we straighten things out.  jh, 8/13/91.

(defmacro license-close-listener ()
  `(shift-rule-ordering-heuristics))

;; This used to have a lispm vs. non-lispm behavior.  That's been removed now,
;; making this appear to be platform independent.  (MHD 11/21/94)





;; Scrambled strings for licensing failure messages

(def-secret-string-for-system process-count-exceeded-goodbye-message
  (g2 "~&Launching this G2 would exceed the licensed number of processes.~%~
         Sorry, must exit.~%")
  (tw "~&Launching this Telewindows would exceed the licensed number of ~
         processes.~%Sorry, must exit.~%"))



(def-scrambled-constant-string 
  tw-cannot-register-process-license-goodbye-message
  "Problem registering process license on network. ~
   Sorry, TW cannot continue.")

;; jh, 1/6/92.  Moved do-telewindows-per-process-checks to TELEWINDOWS because we
;; had to functionize it for the HP compiler, and G2 is unaware of some of the
;; functions it references.



;;;; Thwarting system time set-back

;; jh, 6/28/91.

;;; This machinery makes it harder for G2 users with expiration dates to set back
;;; the system time and get G2 for free.

;;; The idea is to place a timestamp in each KB saved from a G2 with an expiration
;;; date.  Before loading the KB, G2 will compare the current time with this
;;; timestamp, and refuse to load the KB if the KB timestamp is later than the
;;; system time.  Here are the requirements:

;;; (1) We need a place for the timestamp in the KB file.  This is currently split
;;; into several fixnum fields, encrypted, and hidden in the debugging-parameters
;;; system table.

;;; (2) We need a way to encrypt the timestamp.  It should also contain some
;;; redundancy, so that a random guess by UU doesn't by chance set the timestamp
;;; far into the past.  This means the timestamp should have several fields which
;;; are combined in an obscure way.  Most combinations will immediately cause G2 to
;;; refuse to load the KB.  This resembles the design of the OK object.

;;; (3) The timestamp has to be KB-dependent, to prevent UU from inserting an
;;; earlier timestamp into a later KB.  As of 6/28/91, this requirement has not
;;; been met.

;;; (4) We need to place a "primeval timestamp" inside each version of G2.  This is
;;; a time before this G2 version could possibly have existed.  G2 will fail to
;;; launch if the system time precedes the primeval date.  The primeval date will
;;; be appropriately encrypted.  We use the KB-independent part of the KB-timestamp
;;; encryption machinery.

;;; (5) We have to make sure G2 contains safeguards against resetting the system
;;; clock while it is running.  Otherwise UU could defeat the timestamp by
;;; resetting the system clock to the moment just after the last KB save and
;;; thereby run G2 much longer than the license permits.  This is accomplished by
;;; storing the system time every so often and refusing to store a time which is
;;; earlier than the last stored value.  When the KB is saved, that timestamp will
;;; ensure that the user is charged for all the time that the G2 process was
;;; active.

;; jh, 5/8/97.  Customers with permanent licenses occasionally can't save or
;; load KBs due to licensing mechanisms designed to prevent temporary license
;; holders from cheating.  Naturally, permanent license holders object to these
;; mechanisms.  On the other hand, we would like to know if customers are
;; engaging in unusual clock-shifting behavior, regardless of whether their
;; licence is temporary or permanent.  So we store such information in the KB's
;; initial plist under devious names (cf. write-initial-plist in KB-SAVE1).


;; Timestamp encryption and decryption

;; An uncoded date, whether a KB timestamp or a primal timestamp, is represented
;; using five 21-bit fields.  (The remaining bits in the implementation's fixnum
;; are ignored.) In each field, only the most significant 7 bits are meaningful.
;; If the trailing 14 bits, when decrypted, do not contain two exact duplicates of
;; the leading 7, tampering has occurred and G2 should refuse to load the KB.  To
;; prevent the user from narrowing down the search by discovering which field
;; contains the most significant digits, the timestamp bits are distributed to
;; each field.  The timestamp is in Lisp time, measured in seconds since midnight
;; 1/1/1900.  This is currently a 32-bit number.

(defconser timestamp SEQUENCES1)

(defun initialize-class-instance-delta-masks () ;devious name
  (make-array 5 
    :element-type t
    :initial-contents
    (loop for index from 0 to 32 by 7
	  for mask = #.(- (ash 1 7) 1) then (ash mask 7)
	  collect mask)))

(declare-special-global class-instance-delta-masks)
(def-system-variable class-instance-delta-masks SEQUENCES1 ;devious name
  (:funcall initialize-class-instance-delta-masks))

(defmacro with-circular-list ((list-to-make-circular) &body body)
  (avoiding-variable-capture (list-to-make-circular &aux circularity-point)
    `(let ((,circularity-point (1- (length ,list-to-make-circular))))
       (setf (cdr (nthcdr ,circularity-point ,list-to-make-circular))
	     ,list-to-make-circular)
       (unwind-protect
	   (progn ,@body)
	 (setf (cdr (nthcdr ,circularity-point ,list-to-make-circular))
		    nil)))))

(def-substitution-macro time-to-timestamp (time)
  (protected-let 
      ((raw-field-list
	 (loop repeat 5
	       ;; bignum arithmetic necessary to pass validation tests
	       ;; Can't use `floore-first' here! (result is too large)
	       with fix-time = (floor (+e time seconds-from-1900-to-1970))
	       for index from 4 by -1
	       for shift-amount from -28 by 7
	       collect
	       (ash (logand (svref class-instance-delta-masks index) 
			    fix-time) 
		    shift-amount)
		 using timestamp-cons)
	 (reclaim-timestamp-list raw-field-list))
       (timestamp (timestamp-list 0 0 0 0 0)))
    (with-circular-list (timestamp)
      (loop for raw-field in raw-field-list
	    do
	(loop repeat 7
	      do
	  (let ((timestamp-field (car timestamp)))
	    (setf (car timestamp)
		  (if (oddp raw-field) 
		      (logiorf (ash timestamp-field 1) 1) 
		      (ashf timestamp-field 1)))
	    (setq timestamp (cdr timestamp))
	    (setq raw-field (ashf raw-field -1))))
	    finally 
	      (return timestamp)))))



(define-modify-macro logrotate-in-place (amount offset window) logrotate)

(defmacro logrotate (n amount offset window) ;straightforward name
  `(assemble-uncached-compound-method-flags 
     ,n ,amount ,offset ,window))

;; TODO: need to optimize, removing all generic arithmetics.
(defun assemble-uncached-compound-method-flags ;devious name
       (n amount offset window)
  (setq amount (mod amount window))
  (if (and (numberp amount) (= amount 0))
      n 
      (let ((intact
	      (logand (lognot (ash (1- (ash 1 window)) 
				   offset))
		      n)))
	(let ((span (- window amount)))
	  (logior
	    (ash (logand (ash (1- (ash 1 span)) 
			      offset)
			 n)
		 amount)
	    (ash (logand (ash (1- (ash 1 amount)) 
			      (+ offset span))
			 n)
		 (- span))
	    intact)))))

(def-system-variable embedded-fuzzy-conditionals-list SEQUENCES1 ;devious name
  (:funcall initialize-embedded-fuzzy-conditionals-list))

(defun initialize-embedded-fuzzy-conditionals-list ()
  (list 13 -2  4  2 -1 7  8))
;; elt:  0  1  2  3  4 5  6



(def-substitution-macro encode-timestamp-field (timestamp-field)
  (let ((encrypted-timestamp-field
	  (logior (ash timestamp-field 0)
		  (ash timestamp-field 7)
		  (ash timestamp-field 14)
		  #+no (ash timestamp-field 21)))
	(rotator-list
	  (timestamp-list
	    (nth 2 embedded-fuzzy-conditionals-list)
	    (nth 5 embedded-fuzzy-conditionals-list)
	    (nth 6 embedded-fuzzy-conditionals-list)
	    (nth 1 embedded-fuzzy-conditionals-list)
	    (nth 0 embedded-fuzzy-conditionals-list)
	    (nth 4 embedded-fuzzy-conditionals-list)
	    (nth 3 embedded-fuzzy-conditionals-list))))
    (loop for rotator in rotator-list
	  for offset from 0 by 3
	  do (logrotate-in-place encrypted-timestamp-field rotator offset 3))
    (reclaim-timestamp-list rotator-list)
    encrypted-timestamp-field))


;; Note that encode timestamp does not create a new timestamp list, but
;; decode-timestamp does.

(def-substitution-macro encode-timestamp (timestamp)
  (loop for timestamp-field in timestamp
	for timestamp-cons on timestamp
	do (setf (car timestamp-cons)
		 (encode-timestamp-field timestamp-field))
	finally (return timestamp)))



(def-substitution-macro decode-timestamp-field (encoded-timestamp-field)
  (protected-let 
      ((rotator-specs
	 (timestamp-list
	   (timestamp-cons (nth 3 embedded-fuzzy-conditionals-list) 0)
	   (timestamp-cons (nth 4 embedded-fuzzy-conditionals-list) 3)
	   (timestamp-cons (nth 1 embedded-fuzzy-conditionals-list) 6)
	   (timestamp-cons (nth 4 embedded-fuzzy-conditionals-list) 9)
	   (timestamp-cons (nth 2 embedded-fuzzy-conditionals-list) 12)
	   (timestamp-cons (nth 5 embedded-fuzzy-conditionals-list) 12)
	   (timestamp-cons (nth 1 embedded-fuzzy-conditionals-list) 15)
	   (timestamp-cons (nth 4 embedded-fuzzy-conditionals-list) 18)
	   (timestamp-cons (nth 6 embedded-fuzzy-conditionals-list) 18))
	 (loop for rotator-spec in rotator-specs
	       do (reclaim-timestamp-cons rotator-spec)
	       finally (reclaim-timestamp-list rotator-specs))))
    (loop for (rotator . offset) in rotator-specs
	  do 
	  (logrotate-in-place encoded-timestamp-field rotator offset 3))
    (protected-let*
        ((filled-timestamp-field-components
	   (loop repeat 3
		 for index from 2 by -1
		 for shift-amount from -14 by 7
		 collect
		 (ash (logand (svref class-instance-delta-masks index)
			      encoded-timestamp-field)
		      shift-amount)
		 using timestamp-cons)
	   (reclaim-timestamp-list filled-timestamp-field-components))
	 (key (first filled-timestamp-field-components)))
      (if (loop for component in (rest filled-timestamp-field-components)
		always (=f key component))
	  key
	  nil))))

;;; Note that decode-timestamp creates a new timestamp list, whereas
;;; encode-timestamp does not.

;; jh, 7/15/94.  Modified decode-timestamp to prevent variable capture.  It was
;; capturing "timestamp", which should have been "timestamp?" anyway.

(defmacro decode-timestamp (encoded-timestamp)
  (avoiding-variable-capture
      (encoded-timestamp
	&aux timestamp? encoded-timestamp-field timestamp-field?)
    `(let ((,timestamp? nil))
       (loop for ,encoded-timestamp-field in ,encoded-timestamp
	     for ,timestamp-field?
	     = (decode-timestamp-field ,encoded-timestamp-field)
	     do
	 (timestamp-push ,timestamp-field? ,timestamp?))
       (loop for ,timestamp-field? in ,timestamp?
	     do
	 (unless ,timestamp-field?
	   (when ,timestamp?
	     (reclaim-timestamp-list ,timestamp?))
	   (return nil))
	     finally
	       (return (nreverse ,timestamp?))))))



(def-substitution-macro timestamp-to-time (timestamp)
  (macrolet ((leftmost-bit () #.(ash 1 6)))
    (with-circular-list (timestamp)
      (let ((raw-field-list
	      (loop repeat 5
		    for raw-field = 0
		    do
		    (loop repeat 7
			  for timestamp-field = (car timestamp)
			  do
			  (setq raw-field
				(if (logtest (leftmost-bit) timestamp-field)
				    (logior (ash raw-field -1) (leftmost-bit))
				    (ash raw-field -1)))
			  (setf (car timestamp) (ash timestamp-field 1))
			  (setq timestamp (cdr timestamp)))
		    collect raw-field using timestamp-cons)))
	(loop for raw-field in raw-field-list
	      for shift-amount from 28 by -7
	      with time = 0
	      do 
	      (setq time 
		    (logior (ash raw-field shift-amount) time))
	      finally 
	      (reclaim-timestamp-list raw-field-list)
	      (return time))))))

;; Note that insert-kb-timestamp happens elsewhere from save-kb, to make it more
;; difficult for UU to locate a decryption/encryption pattern in the code.

;; We need to supress timestamp insertion during KB reading.

(defmacro do-kb-timestamp-checks-p () 'separate-imminent-actions-p)
(def-system-variable separate-imminent-actions-p SEQUENCES1 t) ;devious name

;; System-clock-set-back-p is the flag which tells us if UU has set the system
;; clock back by more than an hour when this KB has been running, or by an hour or
;; less more than once in the past year this KB has been running.  We want NV to
;; be able set daylight savings time backwards, but we don't want UU to set the
;; system clock back in 59-minute increments.  jh, 7/23/91.

(declare-special-global engage-context-pipelining-p)
(defmacro system-clock-set-back-p () 'engage-context-pipelining-p) ;devious name
(def-system-variable engage-context-pipelining-p SEQUENCES1 nil)

;; The following constants are chosen to make the test for daylight savings time
;; shift easier.  They use 12, which gives the first power of two greater than the
;; number of seconds in an hour.  If the kb-guardian-1 fields (which have been
;; left-shifted by 12) differ by more than 1, we know that the system clock has
;; been set back more than an hour.  If the system clock has been set back an hour
;; or less, but this has happened more than once in the last year, we know that
;; the system clock was set back more frequently than is appropriate.  In either
;; case, we know that some skulduggery has taken place, since the maximum
;; legitimate amount to set back the system clock is a single hour once a year.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant-for-macro kb-guardian-shift-amount -12)
  (defconstant-for-macro kb-guardian-shift-result 4096)
  (defconstant-for-macro kb-guardian-inverse-shift-amount 12)
  (defconstant-for-macro kb-guardian-overage #.(ash 1 12))
  (defconstant-for-macro kb-guardian-mask #.(1- (ash 1 12)))
  (defconstant-for-macro minimum-daylight-savings-setback-interval
      #.(1- (ash (* 365 24 60 60) -12)))
  (defconstant-for-macro maximum-allowed-accumulated-clock-setback-time 
      #.(* 24 60 60))  
  (defconstant-for-macro number-of-seconds-in-an-hour #.(* 60 60))
  (defconstant-for-macro number-of-seconds-in-twenty-five-hours
      #.(* 25 60 60))
  (defconstant-for-macro constant-for-low-order-bit-preservation 1e8)
)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant-for-macro shifted-seconds-from-1900-to-1970
      (/ seconds-from-1900-to-1970 kb-guardian-shift-result)))

;; cpm & jh, 7/30/91.  Note the use of #. with the above constants in
;; insert-kb-timestamp.  Without the #. read-time macro, these constants are
;; undefined in the no-macros pass, since that is what defconstant-for-macro is
;; supposed to do.  In turn, we have to use defconstant-for-macro because for
;; security reasons we don't want the names of the constants present at run time.
;; (Although Chestnut probably doesn't preserve constant names in the translated
;; image, other Lisps, even other Lisp translators, may do so.) The gist of all
;; this is that constants-for-macro appearing inside macros must be prefixed with
;; #. for the no-macros pass to compile properly.  Intuitively, we expect
;; defconstant-for-macro to do this work automatically, but it would have to cause
;; every macroexpander to look for places to inline the constant value, not a
;; feasible task.

(declare-special-global current-inner-procedure-loop-cache-index)
(def-system-variable current-inner-procedure-loop-cache-index ;devious name
		     SEQUENCES1
		     0)
(defmacro accumulated-clock-setback-time ()
  `current-inner-procedure-loop-cache-index)

(declare-special-global drawing-task-tuning-info)
(def-system-variable drawing-task-tuning-info ;devious name
    SEQUENCES1
  nil)

(defmacro setback-time-preventing-kb-save? ()
  `drawing-task-tuning-info)

(defmacro property-for-setback-time-preventing-kb-save? ()
  `'performance-tuning-bits)

(defmacro reset-guardians (time new-guardian-1 new-guardian-2)
  `(protected-let 
       ((timestamp
	  (encode-timestamp
	    (time-to-timestamp ,time))
	  (reclaim-timestamp-list timestamp)))
     (setf (kb-timestamp-field-1) (nth 0 timestamp))
     (setf (kb-timestamp-field-2) (nth 1 timestamp))
     (setf (kb-timestamp-field-3) (nth 2 timestamp))
     (setf (kb-timestamp-field-4) (nth 3 timestamp))
     (setf (kb-timestamp-field-5) (nth 4 timestamp))
     (setf (kb-timestamp-guardian-1) ,new-guardian-1)
     (setf (kb-timestamp-guardian-2) ,new-guardian-2)))

(declare-special-global counter-for-sleep-management-adjustment)
(def-system-variable counter-for-sleep-management-adjustment ;devious name
    CYCLES 0)
(defmacro time-since-last-kb-timestamp-insertion ()
  `counter-for-sleep-management-adjustment)

(defvar legacy-subsecond-heartbeat-adjustment-interval 10000) ;devious name
(defmacro interval-for-kb-timestamp-insertion ()
  `legacy-subsecond-heartbeat-adjustment-interval)

(defun-for-macro expander-for-insert-kb-timestamp ()
  `(when (do-kb-timestamp-checks-p)
     (with-temporary-creation expander-for-insert-kb-timestamp
       (let* ((time (gensym-get-unix-time))
	      (new-guardian-1
		(floore-first
		  (+e #.shifted-seconds-from-1900-to-1970
		      (/e (gensym-get-unix-time)
			  (coerce-fixnum-to-gensym-float
			    #.kb-guardian-shift-result)))))
	      ;; bignum arithmetic necessary to pass validation tests
	      ;; Can't use `floore-first' here! (result is too large)
	      (new-guardian-2
		(logand (floor (+e time seconds-from-1900-to-1970))
			#.kb-guardian-mask))
	      (old-guardian-1? (kb-timestamp-guardian-1))
	      (old-guardian-2? (kb-timestamp-guardian-2)))
	 (cond 
	   (;; Clock has been set back.
	    (and old-guardian-1? 
		 old-guardian-2?
		 (or (<f new-guardian-1 old-guardian-1?) 
		     (and (=f new-guardian-1 old-guardian-1?)
			  (< new-guardian-2 old-guardian-2?)))) ; can't use <F here
	    (let* ((clock-setback-time
		     (+ (ashf (-f old-guardian-1? new-guardian-1)
			      #.kb-guardian-inverse-shift-amount)
			(- old-guardian-2? new-guardian-2))) ; can't use -F here
		   (setback-remaining
		     (-f most-positive-fixnum
			 (accumulated-clock-setback-time)))
		   (total-setback-time
		     (if (>f clock-setback-time setback-remaining)
			 most-positive-fixnum
			 (+f clock-setback-time
			     (accumulated-clock-setback-time)))))
	      (cond 
		
		(;; This clock setback exceeds the maximum total allowed in the
		 ;; life of this process.
		 (>f total-setback-time
		     #.maximum-allowed-accumulated-clock-setback-time)
		 (setf (system-clock-set-back-p) t)
		 (setf (accumulated-clock-setback-time) total-setback-time)
		 (reset-guardians time new-guardian-1 new-guardian-2))
		
		(t ;; The clock setback is legitimate.
		   ;; Note that the simplest and most innocent case is a yearly
		   ;; setback of an hour for daylight savings time, and in that
		   ;; simplest case, the following two forms leave
		   ;; (accumulated-clock-setback-time) unchanged.
		 
		   ;; Accumulate the setback amount.  
		   (setf (accumulated-clock-setback-time) total-setback-time)

		   ;; Reset the guardians so we don't continue to accumulate
		   ;; setback time.
		   (reset-guardians time new-guardian-1 new-guardian-2)

		   ;; If more than a year has passed since the last setback,
		   ;; give an hour's credit and store the new setback time.
		   (let ((last-setback?
			   (last-daylight-savings-clock-setback)))
		     (when (or (null last-setback?)
			       (>=f (-f new-guardian-1 last-setback?)
				    #.minimum-daylight-savings-setback-interval))
		       (when (and last-setback?
				  (>=f (accumulated-clock-setback-time)
				       #.number-of-seconds-in-an-hour))
			 (decff (accumulated-clock-setback-time) 
				#.number-of-seconds-in-an-hour))
		       (setf (last-daylight-savings-clock-setback)
			     new-guardian-1)))))))
	   
	   (t ;; Clock has not been set back.  Insert an updated timestamp.
	      (reset-guardians time new-guardian-1 new-guardian-2)))))))

(defmacro insert-kb-timestamp ()
  (expander-for-insert-kb-timestamp))

;; jh, 5/15/92.  Modified insert-kb-timestamp to be more forgiving of users that
;; are setting the clock back for small experiments.  Previously, G2 would
;; regard more than a single clock setback per year as evidence of malicious
;; intent, and refuse to save the user's KB.  Now, G2 accumulates the setback
;; times throughout the life of the G2 process and only refuses to save a KB if
;; they total more than maximum-allowed-accumulated-clock-setback-time, which is
;; currently 24 hours.  Every year, G2 credits the user with an hour for
;; legimimate daylight savings time setback purposes (on VMS platforms).

;; Chris has pointed out that users can still iterate over the following to
;; bypass this mechanism:
;;   load KB
;;   set clock back 23 hours
;;   save KB.
;; He suggests we save out the total accumulated time inside the KB to prevent
;; this.


#+development
(defmacro test-insert-kb-timestamp-macro
	  (test-temporary-universal-time
	   test-kb-timestamp-guardian-1 
	   test-kb-timestamp-guardian-2
	   test-accumulated-clock-setback-time
	   test-last-daylight-savings-clock-setback)
  `(let ((test-kb-timestamp-field-1 nil)
	 (test-kb-timestamp-field-2 nil)
	 (test-kb-timestamp-field-3 nil)
	 (test-kb-timestamp-field-4 nil)
	 (test-kb-timestamp-field-5 nil)
	 (test-system-clock-set-back-p nil)
	 (test-temporary-universal-time ,test-temporary-universal-time)
	 (old-test-kb-timestamp-guardian-1 ,test-kb-timestamp-guardian-1)
	 (old-test-kb-timestamp-guardian-2 ,test-kb-timestamp-guardian-2)
	 (test-kb-timestamp-guardian-1  ,test-kb-timestamp-guardian-1)
	 (test-kb-timestamp-guardian-2 ,test-kb-timestamp-guardian-2)
	 (test-accumulated-clock-setback-time 
	   ,test-accumulated-clock-setback-time)
	 (test-last-daylight-savings-clock-setback
	   ,test-last-daylight-savings-clock-setback))
     (macrolet
         ((kb-timestamp-field-1 () `test-kb-timestamp-field-1)
	  (kb-timestamp-field-2 () `test-kb-timestamp-field-2)
	  (kb-timestamp-field-3 () `test-kb-timestamp-field-3)
	  (kb-timestamp-field-4 () `test-kb-timestamp-field-4)
	  (kb-timestamp-field-5 () `test-kb-timestamp-field-5)
	  (kb-timestamp-guardian-1 () `test-kb-timestamp-guardian-1)
	  (kb-timestamp-guardian-2 () `test-kb-timestamp-guardian-2)
	  (do-kb-timestamp-checks-p () t)
	  ;; ??? I killed get-temporary-universal-time,
	  ;; get-universal-time-as-double-float is a reasonable substitute
	  ;; but in this test I'm not sure
	  (gensym-get-unix-time () `test-temporary-universal-time)
	  (accumulated-clock-setback-time () 
	    `test-accumulated-clock-setback-time)
	  (last-daylight-savings-clock-setback () 
	    `test-last-daylight-savings-clock-setback)
	  (system-clock-set-back-p () `test-system-clock-set-back-p))
       ,(expander-for-insert-kb-timestamp)
       (when (and (eql test-kb-timestamp-guardian-1 
			old-test-kb-timestamp-guardian-1)
		  (eql test-kb-timestamp-guardian-2 
		       old-test-kb-timestamp-guardian-2))
	 (setq test-kb-timestamp-guardian-1 nil)
	 (setq test-kb-timestamp-guardian-2 nil))
       (values test-kb-timestamp-field-1
	       test-kb-timestamp-field-2
	       test-kb-timestamp-field-3
	       test-kb-timestamp-field-4
	       test-kb-timestamp-field-5
	       test-kb-timestamp-guardian-1 
	       test-kb-timestamp-guardian-2
	       test-accumulated-clock-setback-time
	       test-last-daylight-savings-clock-setback
	       test-system-clock-set-back-p))))


#+development
(defun-allowing-unwind test-insert-kb-timestamp
       (test-temporary-universal-time
	test-kb-timestamp-guardian-1 
	test-kb-timestamp-guardian-2
	test-accumulated-clock-setback-time
	test-last-daylight-savings-clock-setback)
  (test-insert-kb-timestamp-macro
    test-temporary-universal-time
    test-kb-timestamp-guardian-1 
    test-kb-timestamp-guardian-2
    test-accumulated-clock-setback-time
    test-last-daylight-savings-clock-setback))


#+development
(defparameter test-suite-for-insert-kb-timestamp
  '(
    
    ("first no-setback call of insert-kb-timestamp"
     (test-insert-kb-timestamp (- 2914866129.0 seconds-from-1900-to-1970) nil nil 0 nil)
     (1082913 773525 1357419 1822645 1391226	;kb-timestamp-field-1 thru 5
      711637 977				;kb-timestamp-guardian-1 and 2
      0						;accumulated-clock-setback-time
      nil					;last-daylight-savings-clock-setback
      nil					;system-clock-set-back-p
      ))
    
    ("subsequent no-setback call of insert-kb-timestamp"
     (test-insert-kb-timestamp (- 2914868888.0 seconds-from-1900-to-1970) 711637 977 0 nil)
     (1214117 777687 1323626 1691441 1420857	;kb-timestamp-field-1 thru 5
      711637 3736				;kb-timestamp-guardian-1 and 2
      0						;accumulated-clock-setback-time
      nil					;last-daylight-savings-clock-setback
      nil					;system-clock-set-back-p
      ))

    ("clock setback by 1 -~%~
      non daylight savings - zero accumulated setbacks"
     (test-insert-kb-timestamp (- 2914866129.0 1 seconds-from-1900-to-1970) 
      711637 977
      0
      nil)
     (1082913 773525 1357419 1691441 1391226    ;kb-timestamp-field-1 thru 5
      711637 976                                ;kb-timestamp-guardian-1 and 2
      1                                         ;accumulated-clock-setback-time
      711637                                    ;last-daylight-savings-clock-setback
      nil                                       ;system-clock-set-back-p
      ))

    ("clock setback within allowed total -~%~
      non daylight savings - zero accumulated setbacks"
     (test-insert-kb-timestamp (- 2914866129.0
				  (- #.maximum-allowed-accumulated-clock-setback-time
				     12345)
				  seconds-from-1900-to-1970)
			       711637 977
			       0
			       nil)

     (1082913 710087 1450668 1691441 469148     ;kb-timestamp-field-1 thru 5
      711619 650                                ;kb-timestamp-guardian-1 and 2
      74055                                     ;accumulated-clock-setback-time
      711619                                    ;last-daylight-savings-clock-setback
      nil                                       ;system-clock-set-back-p
      ))

    ("clock setback exactly at allowed total -~%~
      non daylight savings - zero accumulated setbacks"
     (test-insert-kb-timestamp (- 2914866129.0
				  #.maximum-allowed-accumulated-clock-setback-time
				  seconds-from-1900-to-1970)
			       711637 977
			       0
			       nil)
     (1082913 540928 1323626 1822645 342106     ;kb-timestamp-field-1 thru 5
      711616 593                                ;kb-timestamp-guardian-1 and 2
      86400                                     ;accumulated-clock-setback-time
      711616                                    ;last-daylight-savings-clock-setback
      nil                                       ;system-clock-set-back-p
      ))

    ("clock setback exceeds allowed total by 1 -~%~
      non daylight savings - zero accumulated setbacks"
     (test-insert-kb-timestamp (- 2914866129.0
				  #.maximum-allowed-accumulated-clock-setback-time
				  1
				  seconds-from-1900-to-1970)
			       711637 977
			       0
			       nil)
     (nil nil nil nil nil	;kb-timestamp-field-1 thru 5
      nil nil 			;kb-timestamp-guardian-1 and 2
      86401			;accumulated-clock-setback-time
      nil			;last-daylight-savings-clock-setback
      t				;system-clock-set-back-p
      ))

    ("clock setback exceeds allowed total -~%~
      non daylight savings - zero accumulated setbacks"
     (test-insert-kb-timestamp (- 2914866129.0
				  #.maximum-allowed-accumulated-clock-setback-time
				  87654
				  seconds-from-1900-to-1970)
			       711637 977
			       0
			       nil)
     (nil nil nil nil nil	;kb-timestamp-field-1 thru 5
      nil nil			;kb-timestamp-guardian-1 and 2
      174054			;accumulated-clock-setback-time
      nil			;last-daylight-savings-clock-setback
      t				;system-clock-set-back-p
      ))

    ("clock setback exceeds allowed total by 1 -~%~
      non daylight savings - nonzero accumulated setbacks"
     (test-insert-kb-timestamp (- 2914866129.0 12345 seconds-from-1900-to-1970)
			       711637 977
			       (- #.maximum-allowed-accumulated-clock-setback-time
				  12344)
			       nil)
     (nil nil nil nil nil	;kb-timestamp-field-1 thru 5
      nil nil			;kb-timestamp-guardian-1 and 2
      86401			;accumulated-clock-setback-time
      nil			;last-daylight-savings-clock-setback
      t				;system-clock-set-back-p
      ))

    ("clock setback exceeds allowed total -~%~
      non daylight savings - nonzero accumulated setbacks"
     (test-insert-kb-timestamp (- 2914866129 22222 seconds-from-1900-to-1970) 
			       711637 977
			       (- #.maximum-allowed-accumulated-clock-setback-time
				  12345)
			       nil)
     (nil nil nil nil nil	;kb-timestamp-field-1 thru 5
      nil nil			;kb-timestamp-guardian-1 and 2
      96277			;accumulated-clock-setback-time
      nil			;last-daylight-savings-clock-setback
      t				;system-clock-set-back-p
      ))

    ("clock setback exceeds allowed total -~%~
      non daylight savings - accumulated setbacks cause wraparound"
     (test-insert-kb-timestamp (- 2914866129 22222 seconds-from-1900-to-1970) 
			       711637 977
			       (- most-positive-fixnum 1)
			       nil)
     (nil nil nil nil nil	;kb-timestamp-field-1 thru 5
      nil nil			;kb-timestamp-guardian-1 and 2
      536870911			;accumulated-clock-setback-time
      nil			;last-daylight-savings-clock-setback
      t				;system-clock-set-back-p
      ))

    ("clock setback within allowed total -~%~
      no previous daylight savings - nonzero accumulated setbacks < 1 hour"
     (test-insert-kb-timestamp (- 2914866129 1111 seconds-from-1900-to-1970)
			       711637 977
			       1111
			       nil)
     (1214117 612690 1357419 1695603 1556223    ;kb-timestamp-field-1 thru 5
      711636 3962                               ;kb-timestamp-guardian-1 and 2
      2222                                      ;accumulated-clock-setback-time
      711636                                    ;last-daylight-savings-clock-setback
      nil                                       ;system-clock-set-back-p
      ))

    ("clock setback within allowed total -~%~
      no previous daylight savings - nonzero accumulated setbacks > 1 hour"
     (test-insert-kb-timestamp (- 2914866129 1111 seconds-from-1900-to-1970)
			       711637 977
			       4444
			       nil)
     (1214117 612690 1357419 1695603 1556223    ;kb-timestamp-field-1 thru 5
      711636 3962                               ;kb-timestamp-guardian-1 and 2
      5555                                      ;accumulated-clock-setback-time
      711636                                    ;last-daylight-savings-clock-setback
      nil                                       ;system-clock-set-back-p
      ))

    ("get timestamp of almost 1 year later for daylight savings tests"
     (test-insert-kb-timestamp (- (+ 2914866129
				     (* 364 24 60 60))
				  seconds-from-1900-to-1970)
			       nil nil 
			       0 
			       nil)
     (1082913 1822645 1218279 1788852 375899 	;kb-timestamp-field-1 thru 5
      719315 1489 				;kb-timestamp-guardian-1 and 2
      0 					;accumulated-clock-setback-time
      nil 					;last-daylight-savings-clock-setback
      nil 					;last-daylight-savings-clock-setback
      ))

    ("no credit for almost daylight savings setback"
     (test-insert-kb-timestamp (- (+ 2914866129
				     ( - (* 364 24 60 60) 7777))
				  seconds-from-1900-to-1970)
			       719315 1489
			       0 
			       nil)
     (1082913 1788852 1087075 1695603 375899    ;kb-timestamp-field-1 thru 5
      719313 1904                               ;kb-timestamp-guardian-1 and 2
      7777                                      ;accumulated-clock-setback-time
      719313                                    ;last-daylight-savings-clock-setback
      nil                                       ;system-clock-set-back-p
      ))

    ("get timestamp of 1 year later for daylight savings tests"
     (test-insert-kb-timestamp (- (+ 2914866129
				  (* 365 24 60 60))
				  seconds-from-1900-to-1970)
			       nil nil 
			       0 
			       nil)
     (1150513 1590048 1154675 1822645 375899	;kb-timestamp-field-1 thru 5
      719336 1873				;kb-timestamp-guardian-1 and 2
      0						;accumulated-clock-setback-time
      nil					;last-daylight-savings-clock-setback
      nil					;system-clock-set-back-p
      ))

    ("subsequent clock setback for daylight savings -~%~
      zero accumulated setbacks"
     (test-insert-kb-timestamp (- (+ 2914866129
				     ( - (* 365 24 60 60) 3600))
				  seconds-from-1900-to-1970)
			       719336 1873
			       0 
			       711637)
     (1214117 1721252 1281717 1788852 1391226  ;kb-timestamp-field-1 thru 5
      719335 2369                              ;kb-timestamp-guardian-1 and 2
      0                                        ;accumulated-clock-setback-time
      719335                                   ;last-daylight-savings-clock-setback
      nil                                      ;system-clock-set-back-p
      ))

    ("subsequent clock setback for daylight savings -~%~
      accumulated setbacks < 1 hr"
     (test-insert-kb-timestamp (- (+ 2914866129
				     ( - (* 365 24 60 60) 3600))
				  seconds-from-1900-to-1970)
			       719336 1873
			       3599
			       711637)
     (1214117 1721252 1281717 1788852 1391226  ;kb-timestamp-field-1 thru 5
      719335 2369                              ;kb-timestamp-guardian-1 and 2
      3599                                     ;accumulated-clock-setback-time
      719335                                   ;last-daylight-savings-clock-setback
      nil                                      ;system-clock-set-back-p
      ))

    ("subsequent clock setback for daylight savings -~%~
      accumulated setbacks >= 1 hr"
     (test-insert-kb-timestamp (- (+ 2914866129
				     ( - (* 365 24 60 60) 3600))
				  seconds-from-1900-to-1970)
			       719336 1873
			       3600
			       711637)
     (1214117 1721252 1281717 1788852 1391226  ;kb-timestamp-field-1 thru 5
      719335 2369                              ;kb-timestamp-guardian-1 and 2
      3600                                     ;accumulated-clock-setback-time
      719335                                   ;last-daylight-savings-clock-setback
      nil                                      ;system-clock-set-back-p
      ))
    ))

#+development
(defun validate-insert-kb-timestamp (&optional terse-p) 
  (loop for (doc form expected-result) in test-suite-for-insert-kb-timestamp
	with all-tests-passed-p = t
	do
    (unless terse-p
      (format t "~&~? ... " doc nil))
    (let ((result (multiple-value-list (eval form))))
      (cond ((equal result expected-result)
	     (unless terse-p
	       (format t "passed.~%")))
	    (t (setq all-tests-passed-p nil)
	       (format t "*** failed ***~%"))))
    (unless terse-p (terpri))
    finally
    (if all-tests-passed-p
	(format t "~&all tests passed.~%")
	(format t "~&*** WARNING: some tests failed. ***~%"))))



(def-scrambled-constant-string refuse-load-at-discrepancy-with-system-clock-message
  "~s cannot be loaded because it was created ~
   after the time given by the operating system clock.")

(def-scrambled-constant-string refuse-save-after-system-clock-tampering-message
  "This KB cannot be saved because the operating system clock was set back ~
   and daylight savings time was not in effect.")

(declare-special-global limit-bignum-inner-loop-cache-p)
(def-system-variable limit-bignum-inner-loop-cache-p SEQUENCES1 t) ;devious name
(defmacro do-kb-timestamp-load-check-p ()
  `limit-bignum-inner-loop-cache-p)

;; jh, 11/4/91.  Added license-has-expiration-date-p as partial fix of the refusal
;; of the mechanism to load into a UNIX G2, a KB timestamped and saved from a VMS
;; G2.  This will appear in KB-LOAD2.

(defmacro license-has-expiration-date-p (system)
  (case system
    (g2 `(and (nth 11 format-structure-description) t))
    (tw `(and (eighth (second icon-list-notes)) t))))

(declare-special-global evaluator-tradeoff-info)
(def-system-variable evaluator-tradeoff-info SEQUENCES1 nil) ;devious name

(defmacro system-clock-setback-before-kb-load? ()
  `evaluator-tradeoff-info)

(defmacro set-system-clock-setback-before-kb-load (new-value)
  `(let ((old-value? evaluator-tradeoff-info))
     (when old-value?
       (reclaim-timestamp-list old-value?))
     (setq evaluator-tradeoff-info ,new-value)))

(defmacro property-for-system-clock-setback-before-kb-load? ()
  `'graphics-tuning-bits)

(def-substitution-macro system-time-is-earlier-than-kb-timestamp ()
  (protected-let
      ((earlier-p nil)
       (encrypted-timestamp
	 (timestamp-list 
	   (kb-timestamp-field-1)
	   (kb-timestamp-field-2)
	   (kb-timestamp-field-3)
	   (kb-timestamp-field-4)
	   (kb-timestamp-field-5))
	 (reclaim-timestamp-list encrypted-timestamp)))
    ;; if KB is not timestamped, give it the benefit of the doubt
    (unless (loop for field in encrypted-timestamp never field)
      (with-temporary-bignum-creation
	(protected-let* 
	    ((decrypted-timestamp?
	       (decode-timestamp encrypted-timestamp)
	       (reclaim-timestamp-list decrypted-timestamp?))
	     (decrypted-time?
	       (and decrypted-timestamp?
		    (timestamp-to-time decrypted-timestamp?))))
	  (cond
	    ((null decrypted-time?) ;i.e., file was tampered with
	     (setq earlier-p t)
	     (set-system-clock-setback-before-kb-load
	       (timestamp-list 0)))
	    ;; Give an hour margin to loaders of the KB, since we forestall
	    ;; hour setbacks on the saving end, and since it would take a lot
	    ;; of effort to accumulate this margin by alternately loading and
	    ;; saving a KB of any appreciable size.  jh per jra, 8/14/91.
	    ;; jh per licensing committee, 5/8/97.  Changed the margin to a
	    ;; day to permit exchanging KBs between VMS and non-VMS systems
	    ;; across multiple timezones.

	    ;; GENSYMCID-1112: G2 aborts when loading a regular KB and when
	    ;;                 authorized by a specific g2.ok file
	    ;; In Feb 2012 release, we ever introduced a serious bug in timestamp
	    ;; encoding algorithm, which caused zero or very large timestamps
	    ;; (of ~10x big), latter ones were so far only observed in 64-bit
	    ;; Debug or Debug - Enterprise builds.  The zero timestamp is not
	    ;; a problem to customers, just make our security check not working
	    ;; any more, but the too large timestamps will get KB failed to be
	    ;; loaded by G2 when running on timed licenses. We need to get rid
	    ;; of these KBs by treating very large timestamp (5x+) as normal.
	    ;;
	    ;; -- Chun Tian (binghe), 2013/09/12
	    (t (let ((universal-time (get-universal-time-as-double-float)))
		 (setq earlier-p ;i.e., clock setback
		       (and (< universal-time
			       (- decrypted-time?
				  #.number-of-seconds-in-twenty-five-hours))
			    ;; Apply validations for valid `decrypted-time?'
			    (< decrypted-time? (*e 5.0d0 universal-time))))
		 (when earlier-p
		   (set-system-clock-setback-before-kb-load
		     (encode-timestamp
		       (time-to-timestamp universal-time))))))))))
    earlier-p))



;;; Primeval Timestamp

;; This is an encrypted timestamp from a time before any KB could possibly have
;; been created by the current version of G2.  When G2 is launched, it compares
;; this value with the system time.  This will tell us if UU is setting the system
;; clock far back to provide more KB development time than his expiration date
;; allows.

(def-system-variable minimal-fragmentation-seeds SEQUENCES1 ;devious name
  (:funcall initialize-minimal-fragmentation-seeds))

#+development
(defun-allowing-unwind calendar-to-kb-timestamp (s min h d mon y)
  (encode-timestamp
    (time-to-timestamp
      (- (encode-universal-time s min h d mon y) seconds-from-1900-to-1970))))

#+development
(defun-allowing-unwind kb-timestamp-to-calendar (timestamp)
  (decode-universal-time
    (timestamp-to-time
      (decode-timestamp timestamp))))

(defun-simple initialize-minimal-fragmentation-seeds ()
  ;(list 33793 773525 1180324 1691441 4162) ;Midnight, June 28, 1991
  ;(list 1623841 672132 371737 642321 342106) ;Midnight, July 1, 1994
  ;(list 672132 1623841 308299 811272 1053282) ;Midnight, November 1, 1994
  ;(list 1623841 1691441 67600 642321 1425019) ;Midnight, July 1, 1995
  (list 1691441 1755045 1150513 574721 4162) ;Midnight, May 1, 1997
  ;; i.e., (calendar-to-kb-timestamp 0 0 0 1 5 1997)
  )

(def-secret-string-for-system system-time-too-early-goodbye-message
  (g2 "The operating system clock gives a time that is substantially before ~
       the current time.~%Sorry, G2 cannot run under this condition.~%~
       Please reset your system clock to the current time and launch G2 ~
       again.~%")
  (tw "The operating system clock gives a time that is substantially before ~
       the current time.~%Sorry, Telewindows cannot run under this ~
       condition.~%Please reset your system clock to the current time ~
       and launch Telewindows again.~%"))

(def-system-variable master-hierarchy-reconciliation-switches ;devious name
    SEQUENCES1
  (:funcall initialize-master-hierarchy-reconciliation-switches))

(defun-simple initialize-master-hierarchy-reconciliation-switches ()
  (list nil nil nil))

(def-system-variable consistency-tree-focus-shifts ;devious name
    SEQUENCES1
  (:funcall initialize-consistency-tree-focus-shifts))

(defun-simple initialize-consistency-tree-focus-shifts ()
  (let ((original-list (make-list 5)))
    (setf (cdr (last original-list))
	  (cdr master-hierarchy-reconciliation-switches))
    original-list))

(defmacro set-system-time-too-early-for-launch (new-value)
  `(let ((old-value? (third master-hierarchy-reconciliation-switches)))
     (when old-value?
       (reclaim-timestamp-list old-value?))
     (setf (third master-hierarchy-reconciliation-switches) ,new-value)))

(defmacro system-time-too-early-for-launch? ()
  `(seventh consistency-tree-focus-shifts))

(defmacro property-for-system-time-too-early-for-launch? ()
  `'class-hierarchy-flags)

(defmacro check-system-time-against-primeval-time ()
  `(with-temporary-bignum-creation
     (protected-let* 
	 ((system-time (get-universal-time-as-double-float))
	  (decrypted-primeval-timestamp?
	    (decode-timestamp minimal-fragmentation-seeds)
	    (reclaim-timestamp-list decrypted-primeval-timestamp?))
	  (decrypted-primeval-time?
	    (and decrypted-primeval-timestamp?
		 (timestamp-to-time decrypted-primeval-timestamp?))))
       (when (or (null decrypted-primeval-time?) ;tampering has occurred
		 (< system-time (float decrypted-primeval-time?)))
	 (set-system-time-too-early-for-launch
	   (encode-timestamp (time-to-timestamp system-time)))))))

(defmacro exit-if-system-time-too-early (system)
  `(when (and (system-time-too-early-for-launch?)
	      (license-has-expiration-date-p ,system))
     (notify-user-at-console (system-time-too-early-goodbye-message ,system))
     #+development
     (cerror (format nil "Shut down ~S" ',system)
	     "System time must be after 5/1/97")
     (shut-down-ab-process)))





;;;; Authorizing Embedded G2

;; Embedded G2 is the public name for windowless G2.

(def-scrambled-constant-string embedded-g2-with-windows-goodbye-message
  "~%This G2 is not authorized to run with a local window.~%~
   Please launch with the -nowindow option on the command line and use ~
   Telewindows.")

(defmacro check-windows-authorization ()
  `(when (and (zerop x11-preinitialized-p)
	      (g2-limited-to-this-license-level-or-more embedded)
	      #+pre-g2-v5-licensing
	      (embedded-option-authorized-p))
     ;; Fixed to call NOTIFY-USER-AT-CONSOLE instead of
     ;; (FORMAT *TERMINAL-IO* ...) since
     ;; EMBEDDED-G2-WITH-WINDOWS-GOODBYE-MESSAGE returns 
     ;; a wide string. - jpg 12/26/01
     (notify-user-at-console 
       (embedded-g2-with-windows-goodbye-message))
     (shut-down-ab-process)))



;; The "finger":

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar chaining-refresh-version
    major-version-number-of-current-gensym-product-line))

(defun choose-chaining-refresh-list ()
  (case chaining-refresh-version
    (3 #.(stringw "f3r56twe4"))
    (4 #.(stringw "gsa88z0q3"))
    ((5 6) #.(stringw "htb99a1r4"))
    (8 #.(stringw "if8pbys64"))
    ((9 12) #.(stringw "80jz0hrt9")) ; Chun Tian (binghe), 10/2/2010
    (11 #.(stringw "by21bel86")) ;; tam.boirsyakovita@gdev.biz 06/19/2011
    (t (error "unknown version: ~d" chaining-refresh-version))))

;; finger for 3.0:
(def-system-variable chaining-refresh-list sequences1
    (:funcall choose-chaining-refresh-list))

(defmacro choose-tw-numeric-seed-macro ()
  `(case chaining-refresh-version
     (3 97578)
     (4 109225)
     ((5 6) 74890)
     (8 98312)
     ((9 12) 57909) ; Chun Tian (binghe), 10/2/2010
     (11 19863) ;; tam.boirsyakovita@gdev.biz 06/19/2011
     #+development
     (t (error "Unknown TW verserion."))))



;;;; Obtaining Machine IDs



;; Years-old, featured-out, obsolete, vms authorization code in this section has
;; now been removed, and similar code fragments in other sections similarly
;; flushed.  (MHD 1/28/95)



;;; The function `nsleep' returns the machine id or key for the platform.
;;;
;;; We're keeping this out of the nsleep.c file for now, but it logically
;;; belongs there, at least the low-level contract specifications.
;;; 
;;;
;;; /* This file contains all the platform-dependent implementations of the
;;;      nsleep function.
;;;   
;;;      The job of the nsleep function is to write the machine ID into the
;;;      argument string and write a NUL character at the end of the end of that
;;;      string.  The ID can be no longer than 31 characters.  The total length
;;;      of the string can be assumed to be at least 32, leaving one byte open
;;;      for the NUL byte.  The caller is responsible for ensuring a string of
;;;      sufficient length.  In addition, the caller must set the first byte to
;;;      the NUL character.  It may be impossible for this function to return
;;;      properly, and this ensures that a NUL-terminated empty string will
;;;      result if this function cannot cause the necessary side effects.
;;;
;;;      If successful, nsleep should return a non-negative integer (typically
;;;      0, which is defined by the macro SUCCESS).  If unsuccessful, it should
;;;      return a negative integer (typically -1, which is defined as the macro
;;;      FAILURE).  In addition, it should if at all possible, write the letters
;;;      ERROR, if possible followed by some informative text, e.g.,
;;;   
;;;         ERROR: no serial number
;;;   
;;;      The return value type of the nsleep is always long.
;;;   
;;;      Note that there must never be a "back door" intentially entered here.
;;;   
;;;      -------------
;;;   
;;;      Issues with what had been here:
;;;   
;;;      - "gensym" as dummy ID -- no back doors allowed!
;;;      - non-uniform side effects in error case -- write "ERROR:" + info in
;;;        all failure cases!
;;;      - ideally there should be "on-line" and "off-line" versions of these functions
;;;        to discourage tampering
;;;      - non-uniform return value to indicate failure/success (fixed)
;;;        (defined SUCCESS/FAILURE over the whole file, and made use of them)
;;;      
;;;     */


(def-gensym-c-function c-nsleep (:fixnum-int "g2ext_nsleep")
  ((:string timestring)))

(def-gensym-c-function c-nsleep-next (:fixnum-int "g2ext_nsleep_next")
  ((:string timestring)))


;;; Get-local-machine-id ...  This macro can return nil if the machine id is not
;;; available, unlike the online version.  If nsleep returns a successful
;;; result, this hands back the result.  Later users of this must still check
;;; for a shunned ID.  If there's failure, this makes sure the resulting string
;;; appears to be shunned.  If not, it writes the minimum needed to make it so.

(defconstant size-of-local-machine-id 256)

(defmacro get-local-machine-id ()				; this one, but not the online
  `(progn							;   one, may return nil if
     #-unrestricted
     (let* ((temp (obtain-simple-gensym-string size-of-local-machine-id))
	    success?
	    text-string-result)
       (setf (schar temp 0) #.(code-char 0)) ; initialize first char to NUL
       (setq success? (>=f (c-nsleep temp) 0))
       (setq text-string-result
	     ;; convert Gensym (Lisp) string -> Text (wide) string:
	     (prog1 (copy-text-string temp)
	       (reclaim-simple-gensym-string temp)))
	     
       (cond
	 (success? text-string-result)
	 (t
	  (cond
	    ((shunned-machine-id-string-p text-string-result)
	     ;; presumably contains "error" + info
	     text-string-result)
	    (t
	     (setf (charw text-string-result 0) #.%\E)
	     (setf (charw text-string-result 1) #.%\R)
	     (setf (charw text-string-result 2) #.%\R)
	     (setf (charw text-string-result 3) #.%\O)
	     (setf (charw text-string-result 4) #.%\R)
	     (setf (charw text-string-result 5) #.%Null))))) ; NUL
       (return-text-string-from-null-terminated-string text-string-result))
     
     #+unrestricted
     #w""))

(defun-simple get-local-machine-id-function ()
  (get-local-machine-id))


(defmacro write-local-machine-id-to-text-string (id)
  `(twith-output-to-text-string (twrite ,id)))

;; This used to have a lispm vs. non-lispm behavior.  That's been removed now,
;; making this appear to be platform independent.  (MHD 11/21/94)






;;; Get-local-machine-id-online ....  For optimum security, this should look
;;; different when disassembled from get-local-machine-id, and it should also
;;; be harder to figure out what it's doing.  This is because we do not try
;;; very hard to hide the entry point to get-local-machine-id, but we do try
;;; to do so for get-local-machine-id-online, so making it easy to see what
;;; the former looks like disassembled makes it easier to find, and thus
;;; maliciously patch, the latter.

(defmacro get-local-machine-id-online ()
  `(get-local-machine-id))

;; In practice, this is implemented by simply calling get-local-machine-id.
;; Prior to today, this only implemented "optimum security" for TI and
;; Symbolics, which we do not even ship on anymore, so I removed such code.
;; This is now simpler to read, but it really should be made different and
;; more secure for relevant platforms!!! (MHD 3/19/91)





;;; `Get-local-machine-id-as-text-string' is almost like get-local-machine-id
;;; except that it returns the one machine ID that was used to authorized this
;;; product, which may be different if there are multiple machine IDs (new for
;;; G2/TW 6.0, release pending 7/5/00).  This returns nil if the product has not
;;; yet been authorized.

;;; `Set-local-machine-id-in-use' is now (new for G2/TW 6.0, release pending
;;; 7/5/00) to be called with the machine ID that is used to authorize the
;;; current product (G2 or Telewindows).  This is necessary now that there can
;;; be a list of machine IDs per machine.  After this is called, the
;;; get-local-machine-id-as-text-string is ready to work properly.

;; NOTE: These are the only two that are called by higher layers:

(defvar first-string-in-pool-group nil)

(defun set-first-string-in-pool-group (text-string)
  (setq first-string-in-pool-group (copy-text-string text-string)))

(defun pointer-to-first-string-in-pool-group ()
  ; may return nil (if unavailable)
  (copy-text-string first-string-in-pool-group))

(defmacro set-local-machine-id-in-use (text-string)
  `(set-first-string-in-pool-group ,text-string))

(defmacro get-local-machine-id-as-text-string ()
  `(pointer-to-first-string-in-pool-group))

(defvar name-of-customer-in-OK-file nil)
(defvar serial-number-in-ok-file nil)
(defvar installation-code-in-ok-file nil)

(defparameter original-site-license-title-block-phrase
  #w"This software is exclusively licensed for use by")
(defparameter site-license-title-block-phrase
  #w" software is exclusively licensed for use by")
(defparameter serial-number-title-block-phrase
  #w"Serial Number:")

(defun-allowing-unwind print-first-string-in-pool-group ()
  (protected-let* ((id-string
		     (get-local-machine-id-as-text-string)
		     (reclaim-if-text-string id-string)))
    (if (text-string-equal+
	  id-string #w"site:"
	  :end1 (minf 5 (text-string-length id-string)))
	(let ((site-license-label
		(text-string-substring
		  id-string
		  (if (and (>=f (text-string-length id-string) 6)
			   (char=w (charw id-string 5) #.%space))
		      6
		      5)
		  nil)))
	  (cond
	    ((null (or name-of-customer-in-OK-file
		       serial-number-in-ok-file
		       installation-code-in-ok-file))
	     ;; Original style of site licensing, e.g. for BMC
	     (tformat ";~% ~a ~a"
		      original-site-license-title-block-phrase
		      site-license-label))
	    
	    ((and name-of-customer-in-OK-file
		  serial-number-in-ok-file)
	     (tformat ";~% This ~a ~a ~a~% ~a ~a"
		      site-license-label
		      site-license-title-block-phrase
		      name-of-customer-in-OK-file
		      serial-number-title-block-phrase
		      serial-number-in-ok-file))
	    
	    (name-of-customer-in-OK-file
	     (tformat ";~% This ~a ~a ~a"
		      site-license-label
		      site-license-title-block-phrase
		      name-of-customer-in-OK-file))

	    (serial-number-in-ok-file
	     (tformat ";~% This ~a ~a UNKNOWN~% ~a ~a"
		      site-license-label
		      site-license-title-block-phrase
		      serial-number-title-block-phrase
		      serial-number-in-ok-file))

	    (installation-code-in-ok-file
	     (tformat ";~% This ~a ~a UNKNOWN"
		      site-license-label
		      site-license-title-block-phrase))))
	  
	(tformat ";~% Machine ID: ~s" id-string))))

(defvar cached-machine-id? nil)

(defmacro get-local-machine-id-as-text-string-online ()
  `(copy-text-string
     (or cached-machine-id?
	 (setq cached-machine-id?
	       (get-local-machine-id-online)))))







(defun get-next-local-machine-id-as-text-string ()
  (let* ((temp (obtain-simple-gensym-string size-of-local-machine-id))
	 temp-text-string)
    (setf (schar temp 0) #.(code-char 0)) ; initialize first char to NUL
    (prog1 (when (>=f (c-nsleep-next temp) 0)	; success
	     (setq temp-text-string (copy-text-string temp))
	     (return-text-string-from-null-terminated-string temp-text-string))
      (reclaim-simple-gensym-string temp))))


;;; Get-local-machine-ids-as-gensym-list returns a list of machine IDs,
;;; consisting of freshly allocated text strings and gensym conses.  This
;;; eliminates IDs not considered acceptable -- including shunned IDs and
;;; duplicates.

(defun get-local-machine-ids-as-gensym-list ()
  (loop with result = nil
	for machine-id?
	    = (get-local-machine-id)
	    then (get-next-local-machine-id-as-text-string)
	while machine-id?
	if (and (not (shunned-machine-id-string-p machine-id?))
		(loop for prev in result ; see Note
		      never (normalized-string-equal prev machine-id?)))
	  do (setq result (nconc result (gensym-cons machine-id? nil)))
	else do (reclaim-text-string machine-id?)
	finally
	  (return result)))

;; Note: I saw a duplicate problem on Windows NT; nsleep thought there were two
;; adaptor cards on my PC (MHD266), but they both had the same MAC address, and
;; there was just one card to my knowledge. (MHD 7/7/00)









;;; `Modularized-normalize-key-online' is a replacement for
;;; normalize-key-online, which used bignums. The latter was called only once by
;;; check-small workspace, and its value (a bignum) was immediately taken modulo
;;; a fixnum. This function performs the whole computation in modular arithmetic
;;; using only integers. The reason for doing this is because it is desired not
;;; to perturb the code generation at this time. Otherwise, one could replace
;;; this computation with modul-string-hash which does the same thing but with a
;;; different number generated. Note that this computation affects only the
;;; fifth code.  ML 2/7/96

;;; In order for *f not to overflow, (*f modulus 36) must be a fixnum.  Copy
;;; this note to new-modulus.

(defmacro modularized-normalize-key-online (string modulus)
  (let ((string-value (gensym))
	(modulus-value (gensym)))
    `(loop with ,string-value = ,string
	   with ,modulus-value = ,modulus
	   with expt = 1
	   with value = 0
	   for i from 0 to (-f (lengthw ,string-value) 1)
	   for weight? = (digit-char-pw (charw ,string-value I) 36)
	   do (when weight?
		(setq value
		      (modf-positive
			(+f value 
			    (modf-positive
			      (*f weight? expt)
			      ,modulus-value))
			,modulus-value))
		(setq expt
		      (modf-positive (*f expt 36) ,modulus-value)))
	   finally (return value))))





;;; Inner-multiply is a combiner of numbers which always produces a positive
;;; fixnum as its value.  It behave like multiply for quite small numbers, and
;;; by folding, uses up to 24 bits of each argument to produce a value.  The
;;; value will be no longer than 24 bits.  In the G2 version, x and y must be
;;; fixnums.
;;;
;;; Note that inner-multiply shares the property with multiply (i.e., standard
;;; multiplication) that if x or y is zero, its result is always 0.

(defparameter mask12 #o7777)

(defun inner-multiply (x y)
  (*f (logxorf (logandf x mask12) (logandf (ashf x -12) mask12))
      (logxorf (logandf y mask12) (logandf (ashf y -12) mask12))))



(defparameter new-modulus 943223)


;;;	 telewindows-machine-ids-equal-p is true if the two strings given as
;;;	arguments would be identical if all non-alphanumerics were removed
;;;	and all letters made lower case. Performance is not important.

(def-substitution-macro telewindows-machine-ids-equal-p (id1 id2)
  (loop  with i = 0
	 with j = 0
	 with length1 = (text-string-length id1)
	 with length2 = (text-string-length id2)
	 with weight1
	 with weight2
	 do
    
    ;; Advancing i, get the weight with radix 36 of the first alphanumeric 
    ;; or nil if none
    (loop until  (=f  i length1)
	  do 
      (setq weight1 (digit-char-pw (charw id1 i) 36))
      (incf i)
      (if weight1 (return))
	  finally (setq weight1 nil))
    
    (loop until (=f j length2)
	  do 
      (setq weight2 (digit-char-pw (charw id2 j) 36))
      (incf j)
      (if weight2 (return))
	  finally (setq weight2 nil))

    (cond ((null weight1) (return (null weight2)))
	  ((null weight2) (return nil))
	  ((/=f weight1 weight2) (return nil)))
))


(defvar shunned-machine-ids-list
  '#.(loop for x in '("00FFFFFF4D00" "unknown" "none" "ERROR"
		      "Gensym"		; was returned on certain platforms,
					;   maybe only in-house (e.g., stratus)
		      "3562951413")	; sometimes returned on old HP machines
	   collect (stringw x)))




;;; Date: Thu, 6 Apr 95 16:32:56 EDT
;;; From: mes (Mark E. Staknis)
;;; To: mhd
;;; Subject: Re:  shun 3562951413?
;;; 
;;; If you wish.  The abomination to which you refer preceded me and was
;;; actually needed in house until I got to the bottom of it.  It would be
;;; better to remove it from the code, which I'll do right now.  But you
;;; can watch out for it for earlier incarnations.
;;;   Speaking of shunning, you should shun all strings that begin with AA00.
;;; These typically indicate a DECnet station address, which is settable by
;;; users.  We are likely to see them if users use Pathworks under NT for
;;; TCP/IP connectivity.  We can easily send them a dongle instead.  Please
;;; acknowledge that you've read this and are taking care of it.
;;; 
;;;    Thanks,
;;;    Mark
;;;
;;; [In conversation, Mark and I clarified that what was needed was high
;;; suspicion for aa00-... ID's, but outright shunning would be overkill, since
;;; it would risk making G2's unusable for potentially reasonable ID's on
;;; platforms that cannot be "programmed" to have a certain ID. Hence, there
;;; arose the notion of a "suspicous" as opposed to a "shunned" ID. (MHD)]
;;;
;;; `Suspicious-machine-id-string-p' is true if machine ID is a superset of
;;; shunned: it's true if the string is either shunned or merely suspicious.  If
;;; a string is merely suspicious, G2/TW will not reject it at runtime; however,
;;; no person at Gensym is authorized to give out codes for it, and all
;;; authorization is hard-programmed not to accept it.  An policy decision by
;;; management followed by programming would be required to derive codes for it,
;;; but then it could be used out in the field.  Shunned ID's on the other hand
;;; couldn't be authorized to run in the field at all; a new version of G2/TW
;;; would be needed that didn't shun them for them to make them run.

#+development
(defun suspicious-machine-id-string-p (machine-id-string)
  (or (normalized-string-equal machine-id-string "aa00" t)
      (shunned-machine-id-string-p machine-id-string)))

;; This is not used at runtime.  Instituted today. (MHD 4/7/95)
    

(defun shunned-machine-id-string-p (machine-id-string)
  (or (<f (normalized-string-length machine-id-string) 3)	; Ben's test (Mac Licensing version)
      (member machine-id-string
	      shunned-machine-ids-list
	      :test 'normalized-string-equal)
      (search "error" shunned-machine-ids-list)))





;;; `Normalized-string-equal' is true if its arguments are strings which would
;;; be equal if all letters were the same case and all non alphanumeric
;;; characters were removed. It is nil for any other pair of strings.
;;;
;;; If different-lengths-ok? is true, then only as many letters are compared as
;;; there are in both strings, and different-length strings are considered equal
;;; if the elements they have in common are the same.

(defun normalized-string-equal (text-string-1 text-string-2 &optional different-lengths-ok?)
  (loop with length1 = (lengthw text-string-1)
	with length2 = (lengthw text-string-2)
	with w1 = nil
	with w2 = nil
	with i1 = 0
	with i2 = 0
	do (loop until (>=f i1 length1)
		 do (when (setq w1 (digit-char-pw (charw text-string-1 i1) 36))
		      (incff i1)
		      (return (values)))
		    (incff i1)
		 finally
		   (setq w1 nil))
	   (loop until (>=f i2 length2)
		 do (when (setq w2 (digit-char-pw (charw text-string-2 i2) 36))
		      (incff i2)
		      (return (values)))
		    (incff i2)
		 finally
		   (setq w2 nil))
	   (if (not (eql w1 w2))
	       (return (if different-lengths-ok?
			   (or (null w1) (null w2))
			   nil)))
	   (if (and (>=f i1 length1) (>=f i2 length2)) (return t))))


;;; `Normalized-string-length' returns the number of alphanumeric characters in
;;; string, a text string.

(defun normalized-string-length (string)
  (loop as i from 0 below (lengthw string)
	count (digit-char-pw (charw string i) 36)))





;;;; Authorized Products



;;; In 3.0, there were only two (explicitly) `authorized products', which became
;;; known simply as `asian language options': JAPANESE and KOREAN.
;;; 
;;; As of 4.0, throughout the authorization code, a variable named authorized
;;; products should be taken to mean a list of symbols, each of which is either
;;; JAPANESE, KOREAN, RUNTIME, DEVELOPMENT, EMBEDDED, or RESTRICTED-USE.  Note,
;;; however, that japanese and korean are obsolete as of 4.0 Beta Phase 2.
;;; Codes are normally never given out for them.  Note that the remaining 4
;;; types are all mutually exclusive.  Note that the lack of any optional
;;; modules implies DEVELOPMENT.  Since 3.0 and early only had one type of
;;; license, they can all be regarded retroactively as having been DEVELOPMENT
;;; type licenses.
;;;
;;; NOTE: the lowest level processing of these options doesn't (yet, at least)
;;; know about DEVELOPMENT because it's not an explicitly defined module.  It is
;;; therefore stripped out of this list at some point, if present.

;; Obsolete:  (MHD 1/28/95)
;; 
;; ;;; The variable first-asian-language-option-in-ok-object? is either NIL or
;; ;;; an asian language option.  It gets its value based on the order in which
;; ;;; the asian language options are entered in the OK object for this machine.
;; ;;;
;; ;;; If it is non-nil, it will be the asian language to be preferred when there
;; ;;; is no way to avoid a choice.  At present, this obtains only in the following
;; ;;; circumstance:
;; ;;;
;; ;;; If both Japanese and Korean are authorized, then the DEFAULT default
;; ;;; language must be one or the other; it cannot be both.  So, if it is Korean,
;; ;;; for example, then KOREAN will be the default current language in a fresh
;; ;;; KB, or in a KB that has never had its (current-language language-parameters)
;; ;;; slot explicitly set.
;; 
;; ;;; This variable is set only by reformat-line-from-left, in SEQUENCES2.
;; 
;; ;;; NOTE: Where it is not desired or practical to use this option in the code,
;; ;;; the ordering to be preferred is the order of development: i.e., Japanese
;; ;;; first.   For example, the code that generates the listing of authorized
;; ;;; products and codes to enter should show Japanese ahead of Korean in the
;; ;;; order of entry.  Only by changing this order -- because of a tip or because
;; ;;; of experimentation -- will the user ever discover the significance of the
;; ;;; order.  An other example: the order in which the grammar rules mentioning
;; ;;; the option/language are entered in the code -- Japanese first here.
;; 
;; (defvar first-asian-language-option-in-ok-object? nil)
;; 
;; ;; Not used in Telewindows at present, but conceivably it will be at some point
;; ;; in the future; to extend this for that use, there should be a separate variable
;; ;; for Telewindows, and that should be set somewhere in the Telewindows
;; ;; authorization line reading code below.  (MHD 11/13/92)
;; 
;; ;; Notice that this must be a defvar because the OK happens once per machine,
;; ;; not once per process.  (Telewindows does it once per process, but that's more
;; ;; or less a bug.)  (MHD 11/13/92)
;; 
;; ;; At present, this is NOT to be documented behavior; we want some flexibility
;; ;; to change it, and it might cause some embarrassment to even mention it.
;; ;; It may help out, however, in situations where the default-default asian
;; ;; language sticks out as an issue for some customer.  (MHD 11/13/92)
;; 
;; ;; Added as part of Korean G2 project.  (MHD 11/13/92)
;; ;; 
;; ;; 
;; ;; 



;;;; Obtaining OK File Pathnames





;;; The function `get-appropriate-ok-pathname' finds either the version-specific
;;; pathname or default pathname, choosing the first of the following that
;;; yields the pathname of an existing file:
;;;
;;;    (1) -v5ok command line arg;
;;;    (2) -ok command line arg;
;;;    (3) G2V5_OK environment variable;
;;;    (4) G2_OK environment variable;
;;;    (5) a file named g2v5.ok in the G2 home directory;
;;;    (6) a file named g2.ok in the G2 home directory
;;;
;;; This can also be used for telewindows, by specifying non-nil for the
;;; telewindows-case? argument.  In that case, read "tw" for "g2" in the
;;; the above description. 
;;;
;;; This returns either nil (if no pathname is found) or a new gensym pathname.
;;; The resulting new pathname, if any, if is owned by the caller.

(defun get-appropriate-ok-pathname (&optional telewindows-case?)
  (multiple-value-bind (v-pathname? v-desired-namestring? v-source?) ; version specific
      (case major-version-number-of-current-gensym-product-line
	(12
	 (if telewindows-case? 
	     (get-or-use-twv12-ok-pathname t)
	     (get-or-use-g2v12-ok-pathname t)))
	(11
	 (if telewindows-case? 
	     (get-or-use-twv11-ok-pathname t)
	     (get-or-use-g2v11-ok-pathname t)))
	(9
	 (if telewindows-case? 
	     (get-or-use-twv9-ok-pathname t)
	     (get-or-use-g2v9-ok-pathname t)))
	(8 
	 (if telewindows-case? 
	     (get-or-use-twv8-ok-pathname t)
	     (if (or (>f minor-version-number-of-current-gensym-product-line 30)
		     (and (=f minor-version-number-of-current-gensym-product-line 30)
			  (>=f release-quality-of-current-gensym-product-line 
			       beta-release-quality)))
		 (get-or-use-g2v83-ok-pathname t)
		 (get-or-use-g2v8-ok-pathname t))))
	(7 
	 (if telewindows-case? 
	     (get-or-use-twv7-ok-pathname t)
	     (get-or-use-g2v7-ok-pathname t)))
	(6
	 (if telewindows-case?
	     (get-or-use-twv6-ok-pathname t)
	     (get-or-use-g2v6-ok-pathname t)))
	(5
	 (if telewindows-case?
	     (get-or-use-twv5-ok-pathname t)
	     (if (>=f minor-version-number-of-current-gensym-product-line 10) ; i.e. 5.1
		 (get-or-use-g2v51-ok-pathname t)
		 (get-or-use-g2v5-ok-pathname t))))
	;; add mutually exclusive cases for current version to
	;; override default.
	)

    ;; If the environment variable G2V51_OK doesn't have a value
    ;; we still want them to get v5 codes.
    (when (and (null v-pathname?)
	       (not telewindows-case?)
	       (=f 5 major-version-number-of-current-gensym-product-line)
	       (>=f minor-version-number-of-current-gensym-product-line 10))
      (multiple-value-setq (v-pathname? v-desired-namestring? v-source?)
	(get-or-use-g2v5-ok-pathname t)))

    (multiple-value-bind (pathname? desired-namestring? source?) ; default
	(if telewindows-case?
	    (get-or-use-tw-ok-pathname t)
	    (get-or-use-g2-ok-pathname t))  ; i.e. /home/ab/g2.ok
      (prog1
	  (or (if (and pathname? v-pathname?)
		  ;; in case of a tie, go by priority
		  (cond
		    ((eq v-source? :command-line)
		     v-pathname?)
		    ((eq source? :command-line)
		     pathname?)
		    ((eq v-source? :environment-variable)
		     v-pathname?)
		    ((eq source? :environment-variable)
		     pathname?)
		    ((eq v-source? :directory)
		     v-pathname?)
		    ((eq source? :directory)
		     pathname?)))
	      (or v-pathname? pathname?))
	(when v-desired-namestring?
	  (reclaim-text-string v-desired-namestring?))
	(when desired-namestring?
	  (reclaim-text-string desired-namestring?))))))

;; mhd, 10/11/94:  (Compilation of old notes follows.)
;; 
;; called "g2.ok" in 2.0; called "ok.ok" in previous versions.  (MHD 2/15/90)
;; jh, 9/11/91.  We now allow the user to specify the ok file on the 
;; command line.
;; jh, 1/24/92.  Changed get-or-use-default-ok-pathname to
;; get-or-use-g2-ok-pathname.  This function also checks the command
;; line and environment variables for an OK file to load in a
;; security-conscious way.  For details, see the documentation of
;; def-suite-for-loading-file-at-launch-time in the PATHNAMES
;; module.
;; ajs, 5/2/97. Added :directory case to establish the appropriate
;; priority between command-line, environment variable, and home
;; directory sources of ok files. This implements (5) and (6)
;; described above. See supporting changes in
;; provide-pathname-for-launch-time-asking-os.



(def-suite-for-loading-file-at-launch-time ok tw
  :base-name-of-file-to-load   "tw"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "ok"
  :environment-variable-name   "TW_OK"
  :base-name-of-disabling-file "TNOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-tw-ok-pathname

(def-suite-for-loading-file-at-launch-time ok twv5
  :base-name-of-file-to-load   "twv5"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v5ok"
  :environment-variable-name   "TWV5_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-twv5-ok-pathname

(def-suite-for-loading-file-at-launch-time ok twv6
  :base-name-of-file-to-load   "twv6"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v6ok"
  :environment-variable-name   "TWV6_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-twv6-ok-pathname

(def-suite-for-loading-file-at-launch-time ok twv7
  :base-name-of-file-to-load   "twv7"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v7ok"
  :environment-variable-name   "TWV7_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-twv7-ok-pathname

(def-suite-for-loading-file-at-launch-time ok twv8
  :base-name-of-file-to-load   "twv8"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v8ok"
  :environment-variable-name   "TWV8_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-twv8-ok-pathname

(def-suite-for-loading-file-at-launch-time ok twv9
  :base-name-of-file-to-load   "twv9"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v9ok"
  :environment-variable-name   "TWV9_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-twv9-ok-pathname

(def-suite-for-loading-file-at-launch-time ok twv11
  :base-name-of-file-to-load   "twv11"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v11ok"
  :environment-variable-name   "TWV11_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-twv11-ok-pathname

(def-suite-for-loading-file-at-launch-time ok twv12
  :base-name-of-file-to-load   "twv12"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v12ok"
  :environment-variable-name   "TWV12_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-twv12-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2
  :base-name-of-file-to-load   "g2"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "ok"
  :environment-variable-name   "G2_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v5
  :base-name-of-file-to-load   "g2v5"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v5ok"
  :environment-variable-name   "G2V5_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v5-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v51
  :base-name-of-file-to-load   "g2v51"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v51ok"
  :environment-variable-name   "G2V51_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v51-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v6
  :base-name-of-file-to-load   "g2v6"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v6ok"
  :environment-variable-name   "G2V6_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v6-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v7 
  :base-name-of-file-to-load   "g2v7"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v7ok"
  :environment-variable-name   "G2V7_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v7-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v8 
  :base-name-of-file-to-load   "g2v8"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v8ok"
  :environment-variable-name   "G2V8_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v8-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v83 
  :base-name-of-file-to-load   "g2v83"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v83ok"
  :environment-variable-name   "G2V83_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v83-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v9 
  :base-name-of-file-to-load   "g2v9"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v9ok"
  :environment-variable-name   "G2V9_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v9-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v11
  :base-name-of-file-to-load   "g2v11"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v11ok"
  :environment-variable-name   "G2V11_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v11-ok-pathname

(def-suite-for-loading-file-at-launch-time ok g2v12
  :base-name-of-file-to-load   "g2v12"
  :type-of-file-to-load        "ok"
  :command-line-keyword        "v12ok"
  :environment-variable-name   "G2V12_OK"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "OK")

;; defines: get-or-use-g2v12-ok-pathname

;;;; Authorization Problem Reporting



;;; The function `make-authorization-file-status-string' makes a text string
;;; reporting the the pathname and machine IDs used for authorization.
;;; Pathname?  should be nil if none was found, or otherwise the pathname used
;;; to read the OK file.  Machine-ids should be a list of zero or more machine
;;; IDs looked for in the file.
;;;
;;; If there are no machine IDs, they're reported as "(none found).  If there
;;; is no pathname, it's reported as "(none found)".  The entire result string
;;; has an open and close paren at the end.
;;;
;;; For example, the result might look like this:
;;;
;;;    (Authorization file: /home/mhd/g2.ok; Machine ID: 23-A4-34-D5-F9-BD)
;;;
;;; This is now used for both Telewindows and G2 authorization.

(defun-allowing-unwind make-authorization-file-status-string
    (pathname? machine-ids)
  (protected-let ((namestring
		    (if pathname? (gensym-enough-namestring pathname?))
		    (reclaim-text-string namestring)))    
    (twith-output-to-text-string
      (tformat
	"(Authorization file: ~a; Machine ID"
	(if pathname? namestring "(none found)"))
      (cond
	((null machine-ids)
	 (tformat ": (none found))"))
	((null (cdr machine-ids))
	 (tformat ": ~a)" (first machine-ids)))
	(t 
	 (tformat "s:")
	 (loop for ids on machine-ids
	       do (tformat "~a" (first ids))
		  (when (cdr ids)
		    (tformat ", ")))
	 (tformat ")"))))))





;;;; OK File Reading for Telewindows



;; Another misleading name.
;; Match content with the same computation in ls.

(defun sort-scheduled-priorities (authorized-products)
  (loop with result = 0
	for product in authorized-products do
    (setq result
	  (logiorf result
		   (second (assq product optional-modules-map))))
	finally
	  ;; This code causes the product 'offline to turn off gsi,
	  ;; gfi and icp unless these products are explicitly
	  ;; mentioned. This is to allow the use of combinations
	  ;; such as "offline, runtime."
	  (when (memq 'offline authorized-products)
	    (loop for product-1 in '(gsi gfi icp)
		  unless (memq product-1 authorized-products)
		    do
		      (clearbits result
				 (second (assq product-1
					       optional-modules-map)))))
	  (return result)))

;; Moved here from SEQUENCES2 for Telewindows support.


(defmacro compute-product-code (authorized-products)
  `(sort-scheduled-priorities ,authorized-products))

;; Moved here from SEQUENCES2 for Telewindows support.

;;; `Number-of-alphanumerics-in-string' ... takes a text string.

(def-substitution-macro number-of-alphanumerics-in-string (text-string)
  (loop with length fixnum =  (lengthw text-string)
	for i from 0 below length
	count (digit-char-pw (charw text-string i) 36)))

;; Moved here from SEQUENCES2 for Telewindows support. (MHD 11/4/92)


;;; make-array-from-strings forms an array whose length is the sum
;;; the number of alphanumeric characters in both strings and
;;; whose contents are fixnums in the range 0-255 derrived from
;;; the strings in a deterministic manner. A modest attempt is made
;;; to make the array contents unreadable from the source text.
				
(defun make-array-from-strings (text-string-1 text-string-2)
  (loop with length1 = (lengthw text-string-1)
	with length2 = (lengthw text-string-2)	
	with nlength1 = (number-of-alphanumerics-in-string text-string-1)
	with nlength2 = (number-of-alphanumerics-in-string text-string-2)
	with array = (make-array (+f nlength1 nlength2))
	with w1 = nil
	with w2 = nil
	with i1 = 0
	with i2 = 0
	for i from 0 below (maxf nlength1 nlength2)
	do (loop until (>=f i1 length1)
		 do (when (setq w1 (digit-char-pw (charw text-string-1 i1) 36))
		      (incff i1)
		      (return (values)))
		    (incff i1)
		 finally
		   (setq w1 nil))
	   (loop until (>=f i2 length2)
		 do (when (setq w2 (digit-char-pw (charw text-string-2 i2) 36))
		      (incff i2)
		      (return (values)))
		    (incff i2)
		 finally
		   (setq w2 nil))
	   (when (<f i nlength1)
	     (setf (aref array i) w1))
	   (when (<f i nlength2)
	     (setf (aref array (+f i nlength1)) w2))
	finally
	  (loop for i from 0 to (+f nlength1 nlength2 -2)
		do (setf (aref array (+f i 1))
			 (modf (+f (*f 3769 (aref array i))
				   (*f 6237 (aref array (+f i 1))))
			       256)))
	  (return array)))

;; Moved here from SEQUENCES2 for Telewindows support. (MHD 11/4/92)



;;; `Gobble-machine-id' ... 

(def-substitution-macro gobble-machine-id (string start-index)
  (loop with string-length = (text-string-length string)
	as i from start-index below string-length
	while (wide-character-member (charw string i) '(#.%space #.%tab))
	finally
	  (if (not (=f i string-length))
	      (return
		(values
		  (twith-output-to-text-string
		    (loop as character = (charw string i)
			  until (wide-character-member character '(#.%space #.%tab))
			  do (twrite-char character)
			     (incff i)
			  until (=f i string-length)))
		  i)))))



;;; `Find-machine-id-in-telewindows-ok-file' (arguments: machine-id file-name).  Returns
;;; the seven elements which make up a entry in the telewindows-ok-file: hostname, machine-id,
;;; code-1, code-2, code-3, code-4, and code-5 or nil if there is an error in the file. The
;;; function searches for the correct entry based on the machine-id and then verifies that
;;; the entry contains each of the seven elements and that they are of the proper type.

;; Changed (system-pathname 'telewindows) default pathname to the new system
;; variable process-specific-system-pathname, defined in PATHNAMES.  jh, 1/16/91.

;; jh, 7/2/91.  Modified find-machine-id-in-telewindows-ok-file to handle a
;; number-of-processes option.  Added scrambled constant strings to make UU's task
;; a bit harder.

(def-scrambled-constant-string no-valid-telewindows-ok-entry-message
  "~%~%No valid entry found in file ~s for machine-id ~s.~%")

(def-scrambled-constant-string cannot-open-telewindows-ok-file-message
  "~%~%Can't open ~s!~%")

;; jh, 12/4/91.  Cloned get-default-telewindows-ok-pathname from
;; get-or-use-default-ok-pathname in KB-SAVE2.  The difference between the two is
;; that get-default-telewindows-ok-pathname always returns some kind of
;; gensym-pathname, and never returns nil.



(defun get-tw-ok-info-from-stream (input-stream? machine-ids-to-match)
  (loop for line? = (g2-stream-read-line input-stream?)
	while line?
	as result = (get-tw-ok-info-from-string line? machine-ids-to-match)
	when result
	  return (if (listp result) result)))



;;; `Telewindows-product-modules-to-select' is the set of product module
;;; keywords to select from the TW OK file entry for a given machine.  Note that
;;; this excludes at least one legal choice, DEVELOPMENT, since that choice is
;;; implied by the absence of other legal choices, i.e., RUNTIME, et al.
;;;
;;; This is just used for filtering a list of legal, defined "modules" in the
;;; def-optional-module sense.

(defparameter telewindows-product-modules-to-select
  '((japanese japanese)
    (korean korean)
    (chinese chinese)			; (MHD 4/9/99)
    
    (floating floating)			; not really a module! -- handled specially
    
    (runtime runtime-option)		; these are new for 4.0
    (restricted-use restricted-use-option)
    (embedded embedded-option)
    ;; development  ; development may be present, but can't be in list
    ))


;;; `Get-tw-modules-from-remaining-fields' ...

(defun get-tw-modules-from-remaining-fields (remaining-fields)
  (let ((modules nil))
    (loop while
	  (loop for x in remaining-fields
		as module?
		  = (loop for (user-name internal-name)
			      in telewindows-product-modules-to-select
			  when (normalized-string-equal x (symbol-name-text-string user-name))
			    return internal-name)
		when module?
		  return
		  (progn
		    (setq remaining-fields
			  (delete-gensym-element x remaining-fields))
		    (reclaim-text-string x)
		    (gensym-push module? modules)
		    t)))
    (values remaining-fields modules)))




(defun get-tw-dates-from-remaining-fields (remaining-fields)
  (let ((start-date? nil)
	(expiration-date? nil))
    (loop while
	  (loop as (x day-string? month-string? year-string?) on remaining-fields
		as from-or-to?
		= (if (normalized-string-equal #w"from" x)
		      'from
		      (if (normalized-string-equal #w"to" x)
			  'to))
		when (and from-or-to? day-string? month-string? year-string?)
		  do (let* ((day
			      (read-positive-fixnum-from-string
				day-string? 0 (text-string-length day-string?)))
			    (month
			      (read-symbol-from-string
				month-string? 0 (text-string-length month-string?)))
			    (year
			      (read-positive-fixnum-from-string
				year-string? 0 (text-string-length year-string?)))
			    (date-list (gensym-list day month year))
			    (universal-date?
			      (if (and day month year
				       (valid-universal-date-elements-p
					 day month year))
				  (convert-input-to-universal-date date-list))))
		       (if universal-date?
			   (if (eq from-or-to? 'from)
			       (setq start-date? universal-date?)
			       (setq expiration-date? universal-date?)))
		       (setq remaining-fields
			     (delete-gensym-element
			       x
			       (delete-gensym-element
				 day-string?
				 (delete-gensym-element
				   month-string?
				   (delete-gensym-element
				     year-string?
				     remaining-fields)))))
		       (reclaim-gensym-list date-list)
		       (reclaim-text-string x)
		       (reclaim-text-string day-string?)
		       (reclaim-text-string month-string?)
		       (reclaim-text-string year-string?)
		       (return t))))
    (values remaining-fields start-date? expiration-date?)))


(defun get-tw-process-limit-from-remaining-fields (remaining-fields)
  (loop for x in remaining-fields
	as integer? = (read-positive-fixnum-from-string x 0 (text-string-length x))
	when integer?
	  do (setq remaining-fields (delete-gensym-element x remaining-fields))
	     (reclaim-text-string x)
	     (return (values remaining-fields integer?))))



;; jh, 4/13/95.  For details on the feature associated with
;; machine-id-of-site-p, see Ben Hyde, licensing czar.

(defmacro machine-id-of-site-p (machine-id-string)
  (avoiding-variable-capture (machine-id-string)
    `(and (>f (lengthw ,machine-id-string) 5)
	  ;; If buffer begins with "Site:", insensitive to case, no trailing
	  ;; space necessary, computed opaquely ...
	  (char=w (charw ,machine-id-string 4) #.%\: )
	  (wide-character-member
	    (charw ,machine-id-string 2)
	    '(#.%\t #.%\T))
	  (wide-character-member
	    (charw ,machine-id-string 1)
	    '(#.%\I #.%\i))
	  (or (char=w (charw ,machine-id-string 3) #.%\e)
	      (char=w (charw ,machine-id-string 3) #.%\E))
	  (or (char=w (charw ,machine-id-string 0) #.%\S)
	      (char=w (charw ,machine-id-string 0) #.%\s)))))

(defun get-tw-ok-info-from-string (string machine-ids-to-match)
  (let ((fields
	  (parse-text-line-into-list-of-text-strings
	    string '(#.%space #.%tab) '(#.%space #.%tab)
	    :grouping-bag #w"\"\"")))
    (when (or (machine-id-of-site-p (second fields))
	      (loop for machine-id in machine-ids-to-match
		    thereis (normalized-string-equal (second fields) machine-id)))
      (cond
	((=f (length fields) 3)
	 (when (normalized-string-equal (third fields) #w"floating")
	   (gensym-list
	     (copy-text-string (first fields))
	     (copy-text-string (second fields))
	     nil nil nil nil nil
	     nil nil
	     (gensym-list 'floating))))
	((>= (length fields) 6)
	 ;; (formatting irregularity!)
      (loop with host-name = (copy-text-string (first fields))
	    with machine-id = (copy-text-string (second fields))
	    for code-string in (nthcdr 2 fields) ; past Host & Machine ID
	    as length = (text-string-length code-string)
	    as code? = (read-positive-fixnum-from-string code-string 0 length)
	    repeat 5			; read at most 5 codes (MHD 3/31/95)
	    when (null code?)
	      do (loop-finish)
	    count t into code-count
	    collect code? into codes using gensym-cons 
	    finally
	      (return
		(cond
		  ((<f code-count 5)
		   'does-not-contain-5-codes)
		  ((shunned-machine-id-string-p machine-id)
		   'shunned-machine-id-string)
		  (t
		   (let* ((remaining-fields (nthcdr #.(+ 2 5) fields))
			  (modules nil)
			  start-date? expiration-date? number-of-processes?)
		     (progn
		       (setf (cdr (nthcdr #.(- (+ 2 5) 1) fields)) nil)
		       (loop for x in fields do (reclaim-text-string x))
		       (reclaim-gensym-list fields))
		     (multiple-value-setq (remaining-fields modules)
		       (get-tw-modules-from-remaining-fields remaining-fields))
		     (multiple-value-setq (remaining-fields start-date? expiration-date?)
		       (get-tw-dates-from-remaining-fields remaining-fields))
		     (multiple-value-setq (remaining-fields number-of-processes?)
		       (get-tw-process-limit-from-remaining-fields remaining-fields))
		     (nconc (gensym-list host-name machine-id)
			    codes
			    (gensym-list
			      start-date? expiration-date?
			      modules
			      number-of-processes?))))))))))))

;; Example:
;;
;;    (get-tw-ok-info-from-string
;;      "acton.com  08-00-2b-05-1a-17      1018995 2475 310707 8379312 523348 japanese from 13 jan 1995"
;;	"08-00-2b-05-1a-17")
;;    => ("acton.com" "08-00-2b-05-1a-17" 1018995 2475 310707 8379312 523348 (JAPANESE) 34710 NIL NIL)


;; This isn't written particularly "obscurely".  I don't think it has to be.
;; This is just the upfront checking done to prevent innocent user from using
;; software that's unauthorized.  There must also be secret checking done
;; elsewhere, i.e., in particular, for the use of a bogus/shunned machine ID.

(defun-allowing-unwind find-machine-id-in-telewindows-ok-file ()
  (let* ((tw-ok-pathname? (get-appropriate-ok-pathname t))
	 (namestring-for-tw-ok-file?
	   (if tw-ok-pathname? (gensym-namestring tw-ok-pathname?))))
    (cond
      ((null namestring-for-tw-ok-file?)
       (when (eq verbosity-level 'verbose)
	 (notify-user-if-possible
	   "[Telewindows: unable to locate a Telewindows OK file ...]"))
       ;; Use cannot-open-telewindows-ok-file-message ?!
       nil)
      ((g2-stream-probe-file-for-read namestring-for-tw-ok-file?)
       (protected-let* ((machine-ids
			  (get-local-machine-ids-as-gensym-list)
			  (reclaim-gensym-tree-with-text-strings machine-ids)))
	 (when (eq verbosity-level 'verbose)
	   (notify-user-if-possible
	     "~%[Telewindows: using Telewindows OK file: ~s]"
	     namestring-for-tw-ok-file?))
	 (g2-stream-with-open-stream
	     (input-stream? namestring-for-tw-ok-file?)
	   (when input-stream?
	     (let* ((ok-information?
		      (get-tw-ok-info-from-stream input-stream? machine-ids)))
	       (cond
		 ((and ok-information? (listp ok-information?))
		  (gensym-dstruct-bind
		      ((nil machine-id		; ignore host-name 
			    code-1 code-2 code-3 code-4 code-5
			    start-date? expiration-date?
			    optional-modules
			    number-of-processes?)
		       ok-information?)
		    (values machine-id
			    code-1 code-2 code-3 code-4 code-5 
			    start-date? expiration-date?
			    optional-modules
			    number-of-processes?)))
		 (t
		  (when (eq verbosity-level 'verbose)
		    (protected-let ((status-string
				      (make-authorization-file-status-string
					(gensym-truename input-stream?)
					machine-ids)
				      (reclaim-text-string status-string)))
		      (notify-user-if-possible
			"[Telewindows: ~a]" status-string)
		      (notify-user-if-possible
			"[Telewindows: no local authorization found for this machine]")
		      nil
		      ))))))))))))

;; This is a rewrite from 3.0.  It is clearer, should not cons freely, does not
;; use the Lisp reader, and is not written secretively.  It takes the product
;; options, process limit, and start and expiration dates, in any order.  Some
;; diagnostics were lost in the process.  Improve the diagnostics for the final
;; release! (MHD 1/28/95)





;; Number-of-raster-oddspaces is actually the default telewindows process count.
(defmacro default-number-of-licensed-telewindows-processes ()
  'number-of-raster-oddspaces)
(defvar number-of-raster-oddspaces 2) ;devious name



;;; Check-if-valid-date given misleading name decrease-raster-dimension, checks
;;; whether the elements for day, month, and year are valid and prints an error if
;;; they are not.
;;;
;;; `Valid-universal-date-elements-p-macro' and
;;; `valid-universal-date-elements-p' are similar, but they have no misleading
;;; name, and they just return true or false and does not print an error message
;;; in case of a problem.

(defparameter tw-months-of-the-year	; for compatibility - clean up later?
  `(jan feb mar apr may jun jul aug sep oct nov dec))

;; Duplicate of the list months-of-the-year, but that's in a G2-only module that
;; needs it earlier than when this module gets loaded for G2.  Fix later! (MHD
;; 5/3/95)

(def-substitution-macro valid-universal-date-elements-p-macro (day month year)
  (and (fixnump day)
       (>=f day 1)
       (<=f day 31)
       (memq month tw-months-of-the-year)
       (fixnump year)))

(defun valid-universal-date-elements-p (day month year)
  (valid-universal-date-elements-p-macro day month year))

(defun decrease-raster-dimension (day month year)
  (cond
    ((valid-universal-date-elements-p-macro day month year)
     t)
    (t
     (format t 
	     "~%~%~s ~s ~s in the tw.ok file is not a valid date.~%"
	     day month year)
     nil)))

;; The use of format for some of these error messages is a weakness in the initial
;; part of the authorization.  Someone could break on format and use this to get a
;; backtrace of some of the functions involved in the initial (non secret) part of
;; the authorization.  This can be fixed by saving the warning messages and
;; sending them from a higher level function so that there is no backtrace to
;; authorization functions!

(defconstant map-month-to-number-code
	     '((Jan 1 31)
	       (Feb 2 28)
	       (Mar 3 31)
	       (Apr 4 30)
	       (May 5 31)
	       (Jun 6 30)
	       (Jul 7 31)
	       (Aug 8 31)
	       (Sep 9 30)
	       (Oct 10 31)
	       (Nov 11 30)
	       (Dec 12 31)))




;;; `Convert-input-to-universal-date' returns a universal date encoding if
;;; list, which is of the form
;;;
;;;    (day month days-in-month year-abbrev year)
;;;
;;; designates a valid year, within a legal range.  Otherwise, it returns nil.
;;; Month can be either a symbol, or an integer in the range from 1 to 12.

(defun convert-input-to-universal-date (list)
  (let* ((day (first list))
	 (month-input (second list))
	 (month-code (if (symbolp month-input)
			 (assq month-input map-month-to-number-code)
			 (if (<=f 1 month-input 12)
			     (elt map-month-to-number-code (1-f month-input))
			     (return-from convert-input-to-universal-date nil))))
	 (month (second month-code))
	 (days-in-month (third month-code))
	 (year-abbrev (third list))
	 (year (if (<=f year-abbrev 99)
		   (guess-year-from-two-digit-year year-abbrev)
		   year-abbrev)))
    (when (and (<f 1899 year 2399)		; was: (<f 1601 year 2399); see
	       (<=f 1 month 12)		;   note below. (MHD 4/13/94)
	       (>f day 0)
	       (or (<=f day days-in-month)
		   (and (leap-year-p year)
			(=f month 2)
			(=f day 29))))
      (encode-universal-date day month year))))




;;; The function `guess-year-from-two-digit-year' takes a two digit year and
;;; returns a four digit year made by guessing which century this is supposed to
;;; be talking about.  The guess is made by taking the interpretation that is
;;; closest to the current year.  So, as of 1996, 92 will return 1992, 99 will
;;; return 1999, and 11 will return 2011.

(defun-simple guess-year-from-two-digit-year (year-abbrev)
  (let* ((current-year
	   (with-temporary-gensym-float-creation guess-year
	     (nth-value 5 (gensym-decode-unix-time (gensym-get-unix-time)))))
	 (this-century-guess
	   (+f (*f (floorf-positive current-year 100)
		   100)
	       year-abbrev)))
    (if (>=f this-century-guess current-year)
	(if (<f (-f this-century-guess current-year)
		(-f current-year (-f this-century-guess 100)))
	    this-century-guess
	    (-f this-century-guess 100))
	(if (<f (-f current-year this-century-guess)
		(-f (+f this-century-guess 100) current-year))
	    this-century-guess
	    (+f this-century-guess 100)))))






;;;; Higher-level TW OK Support




;;; `Telewindows-authorization-numbers' (given the misleading name
;;; `icon-list-notes') points to the machine id and authorization numbers.  The
;;; secret place secret-telewindows-authorization-numbers (given misleading name
;;; graph-allocation-factor) also points to the numbers.

(defvar icon-list-notes
  (list nil (list nil nil nil nil nil nil nil nil nil 0)))

;; jh, 10/6/91.  Changed the default number of processes in icon-list-notes to be
;; 0.  Having the default be nil (which equates to unlimited processes after
;; authorization) was considered too dangerous.





;;; Secret-telewindows-authorization-numbers (given misleading name
;;; graph-allocation-factor) is the secret pointer to the telewindows
;;; authorization numbers.

(defvar graph-allocation-factor	(cons nil (cdr icon-list-notes)))





;;;; Telewindows Authorization Macros 

(defmacro authorize-telewindows ()
  `(setf (second telewindows-screen-utilization) t))


(defmacro telewindows-authorized-p ()
  `(second telewindows-screen-utilization))


(defmacro secret-deauthorize-telewindows ()
  `(setf (second reclaimed-telewindows-boxes) nil))

;; plants seed of destruction


(defmacro secret-telewindows-authorized-p ()
  `(second reclaimed-telewindows-boxes))


(defmacro set-telewindows-authorization-info
	  (machine-id number1 number2 number3 number4 number5
	   start-date? expiration-date? authorized-products-code
	   number-of-processes?)
  `(setf (second icon-list-notes)
	 (list ,machine-id ,number1 ,number2 ,number3 ,number4 ,number5
	       ,start-date? ,expiration-date?
	       ,authorized-products-code	; ninth element -- authorized products code
	       ,number-of-processes?)))


(defmacro secret-get-telewindows-authorization-info ()
  `(second graph-allocation-factor))

(defmacro required-length-of-authorization-list ()
  `10) ;jh, 7/2/91.  Was 9 before we included a number-of-processes slot.       








;;; The deliberately misnamed variable clogged-count controls when the secret
;;; telewindows authorization functions are run.

(def-system-variable clogged-count telestubs 0)

(defmacro do-secret-destroy-if-necessary ()
  `(when (>f clogged-count 13455)
     (setf clogged-count 0)
     (enhance-graphics-colors)))



;;; Telewindows-authorization-flag (given misleading name
;;; telewindows-screen-utilization) points to the authorization flag.  The secret
;;; place secret-telewindows-authorization-flag (given misleading name
;;; reclaim-telewindows-numbers) also points to the flag.

(defvar telewindows-screen-utilization (list nil nil))



(def-system-variable time-of-last-expiration-check telewindows
  (:funcall get-fixnum-time-function))

(def-system-variable tw-expiration-check-interval telewindows
  (:funcall fixnum-time-interval 100000)) ; every 100 seconds

(def-substitution-macro warn-of-tw-expiration-if-necessary (fixnum-time-now)
  (cond
    ((>f (fixnum-time-difference fixnum-time-now time-of-last-expiration-check)
	 tw-expiration-check-interval)
     (warn-of-tw-expiration-if-necessary-1)
     ;; last change here was significant. (MHD 7/19/93)
     (setq time-of-last-expiration-check fixnum-time-now))))

(defun warn-of-tw-expiration-if-necessary-1 ()
  (let ((expiration? (eighth (second icon-list-notes))))
    (when (and expiration? (fixnump expiration?))
      (let ((days-left (-f expiration? (get-tw-universal-date))))
	(when (<f days-left 0)
	  (format t "~%~%The authorization for this machine has expired.~%
                        Telewindows will not run.~%")
	  (force-output)
	  (abort-telewindows-top-level 'tw-expiration))))))






;;; Secret-telewindows-authorization-flag (given misleading name
;;; reclaimed-telewindows-boxes) is the secret pointer to the telewindows
;;; authorization flag.

(defvar reclaimed-telewindows-boxes 
	(cons nil (cdr telewindows-screen-utilization)))



;;; Telewindows-machine-id-checker (given the misleading name
;;; cache-icon-in-system-table) is the secret function which verifies that the
;;; machine id used to authorize and the actual machine id are the same.  If they
;;; aren't it plants the seed of destruction.  

(defun cache-icon-in-system-table ()
  (let ((authorization-info-list
	  (secret-get-telewindows-authorization-info)))
    (when (and authorization-info-list
	       (consp authorization-info-list)
	       (=f (length authorization-info-list) 
		   (required-length-of-authorization-list)))
      (let ((stored-machine-id (first authorization-info-list)))
	(when
	  (not (and
		 (text-string-p stored-machine-id)
		 (telewindows-machine-ids-equal-p
		   stored-machine-id
		   (get-local-machine-id-as-text-string))
		 ))
	  (secret-deauthorize-telewindows))))))





;;; Telewindows-authorization-number-verifier (given the misleading name
;;; telewindows-screen-list-too-big) is the secret function which uses the secret
;;; authorization number generator to verify that the authorization numbers are
;;; correct.  If they aren't it plants the seed of destruction.

(defun telewindows-screen-list-too-big ()
  (let ((authorization-info-list
	  (secret-get-telewindows-authorization-info)))
    (when (and authorization-info-list
	       (consp authorization-info-list)
	       (=f (length authorization-info-list) 
		   (required-length-of-authorization-list)))
      (let ((machine-id (first authorization-info-list))
	    (number1 (second authorization-info-list))
	    (number2 (third authorization-info-list))
	    (number3 (fourth authorization-info-list))
	    (number4 (fifth authorization-info-list))
	    (number5 (sixth authorization-info-list))
	    (start-date? (seventh authorization-info-list))
	    (expiration-date? (eighth authorization-info-list))
	    (authorized-products-bitmask (ninth authorization-info-list))
	    (number-of-processes? (tenth authorization-info-list)))
	(when
	  (not (and
		 (text-string-p machine-id)
		 (fixnump number1) (fixnump number2)
		 (fixnump number3) (fixnump number4) (fixnump number5)
		 (or (null start-date?) (fixnump start-date?))
		 (or (null expiration-date?) (fixnump expiration-date?))
                                        ; *random-state-array*  
                                        ; *random-state-array* initialized 
                                        ; by enlarge-telewindows-memory
                                        ; (=f (length *random-state-array*) 55)
		 (multiple-value-bind
                        (computed-number1 computed-number2 computed-number3 
                                          computed-number4)
		     (enlarge-telewindows-memory 
		       machine-id start-date? expiration-date?
		       authorized-products-bitmask number-of-processes?)
		   (and
		     (=f number1 computed-number1)
		     (=f number2 computed-number2)
		     (=f number3 computed-number3)
		     (=f number4 computed-number4)))))
	  (secret-deauthorize-telewindows))))))






;;; Destroy-telewindows (given the misleading name enhance-graphics-colors) is the
;;; secret function which destroys telewindows.

(defun enhance-graphics-colors ()
  (when (not (secret-telewindows-authorized-p))
    #+development
    (cerror """Authorization failure.  Call Andy.")
    #-development
    (abort-telewindows-for-protocol-out-of-synch-case-6)))







;;;; Telewindows Authorization



;;; The authorization scheme is documented here fully; no attempt is made to
;;; keep things secret in the source code itself.  However, many of the
;;; functions defined are given misleading names and are distributed in various
;;; places in the code in order to thwart attempts to break authorization by
;;; disassembling and decompiling binary files.  Note that this is not an issue
;;; for macros since these are absent in the distribution version.

;;; The following is a table of misleading names and meaningful names (names
;;; that these functions would have if no attempt were made to mislead).  The
;;; meaningful names do not exist in the source;  they simply help avoid 
;;; confusion.  The meaningful names are also noted in comments for each
;;; function definition using a misleading name.

;;; Misleading Name                          Meaningful Name

;;; enlarge-telewindows-memory               compute-telewindows-authorization-numbers
;;; shrink-telewindows-memory                initialize-state-array-for-telewindows-authorization
;;; telewindows-screen-utilization           telewindows-authorization-flag
;;; reclaimed-telewindows-boxes              secret-telewindows-authorization-flag
;;; icon-list-notes                          telewindows-authorization-numbers
;;; graph-allocation-factor                  secret-telewindows-authorization-numbers
;;; check-small-workspace                    make-last-telewindows-authorization-number 
;;; make-small-workspace                     check-telewindows-authorization-numbers  
;;; change-login-box-size                    authorize-telewindows-if-ok
;;; warp-login-box-1                         get-telewindows-ok-entry
;;; telewindows-screen-list-too-big          telewindows-authorization-number-verifier
;;; cache-icon-in-system-table               telewindows-machine-id-checker
;;; enhance-graphics-colors                  destroy-telewindows

;;; The functions telewindows-authorization-number-verifier,
;;; telewindows-machine-id-checker, and destroy-telewindows (a.k.a.
;;; telewindows-screen-list-too-big, cache-icon-in-system-table, and
;;; enhance-graphics-colors) are the secret authorization functions.  They are
;;; called periodically from telewindows-connection-clogged?  or
;;; run-telewindows-top-level-2.



;;; Telewindows authorization information is kept in the tw.ok file, a text file.
;;; Each line of this file contains authorization information for a machine.  Such
;;; a line has the following format:

;;; line:   machine-name machine-id code1 code2 code3 code4 code5 [options]
;;; options:  dates | 'japanese | dates 'japanese
;;; dates:  'from day month year 'to day month year

;;; Month must be a member of {jan feb mar apr may jun jul aug sep oct nov dec}.



;;; Make-last-telewindows-authorization-number (given misleading name
;;; check-small-workspace) takes the four principal telewindows authorization
;;; numbers plus optional features data and generates the fifth number.

(defun check-small-workspace
    (machine-id number1 number2 number3 number4
		start-date? expiration-date? authorized-products 
		number-of-processes?)
  (let* ((keystring
	   (tformat-text-string "~a~a" machine-id chaining-refresh-list))
	 (modularized-key
	   (prog1
	       (modularized-normalize-key-online keystring new-modulus)
	       ;; The above replacement is computationally equivalent, but
	       ;; does not use bignums.
;	       (mod (normalize-key-online keystring) new-modulus)
	     (reclaim-text-string keystring)))
	 (japanese? (memq 'japanese authorized-products)) ; obsolete as of 4.0
	 (korean? (memq 'korean authorized-products)))
    (if (<f number1 100) (setq number1 (+f 253 (*f 792 number1))))
    (if (<f number2 100) (setq number2 (+f 468 (*f 905 number2))))
    (if (<f number3 100) (setq number3 (+f 167 (*f 312 number3))))
    (if (<f number4 100) (setq number4 (+f 833 (*f 398 number4))))
    (mod
      (let* ((t1 (or start-date? 0))
	     (t2 (or expiration-date? 0))
	     (t3 (+ (if japanese? 5781 0) (if korean? 2556 0)))
	     (t4 (+ (if japanese? number4 0) (if korean? number3 0)))
	     (t5 (or number-of-processes? 1001))
	     (t6 (or number-of-processes? 1001))
	     ;; license type: the type DEVELOPMENT is the default, and correspond to
	     ;; the following being all nil; the following are mutually exclusive:
	     (license-type-multiplier
	       (cond
		 ((memq 'runtime-option authorized-products)
		  number1)
		 ((memq 'restricted-use-option authorized-products)
		  number2)
		 ((memq 'embedded-option authorized-products)
		  number3)
		 (t			; development is the default, too
		  0)))
	     (t7 (inner-multiply license-type-multiplier number1))
	     (t8 (inner-multiply license-type-multiplier number2)))	
	(logxorf
	  (inner-multiply modularized-key number1)
	  (inner-multiply number2 number3)
	  (inner-multiply number4 number4)
	  (inner-multiply t1 t2)
	  (inner-multiply t3 t4)
	  (inner-multiply t5 t6)
	  (inner-multiply t7 t8)))
      new-modulus)))




;;; Check-telewindows-authorization-numbers (given misleading name
;;; make-small-workspace) takes the five telewindows authorization numbers plus
;;; the optional features data and checks to make sure that the fifth is the
;;; correct function of the first four.  It returns non-nil if this is the case.
;;; Also, if successful, it sets up the information saying what is and isn't
;;; authorized.

(defun make-small-workspace 
       (machine-id code-1 code-2 code-3 code-4 code-5
	start-date? expiration-date? authorized-products 
	number-of-processes?)
  (let* ((computed-code-5 
	   (check-small-workspace 
	     machine-id code-1 code-2 code-3 code-4
	     start-date? expiration-date? authorized-products 
	     number-of-processes?)))
    (=f code-5 computed-code-5)))



;; Next two: format args, not format control strings:
(def-scrambled-constant-string too-late-telewindows-authorization-message
  "The authorization for this machine has not been valid since ")

(def-scrambled-constant-string too-early-telewindows-authorization-message
  "The authorization for this machine will not be valid until ")

(defun initialize-network-scheduler-interweave-matrix (authorized-products)
  (progn
    (unless (per-process-license-registered-and-listener-activated-p)
      (setf (per-process-license-registered-and-listener-activated-p) 
	    (and (register-licensed-product 
		   (tw-image-product)
		   (tw-image-option authorized-products))
		 (license-listen))))
      #-development
      (cond 
	((not (per-process-license-registered-and-listener-activated-p))
	 (notify-user-if-possible
	   (tw-cannot-register-process-license-goodbye-message))
	 (abort-telewindows-top-level 'cannot-register-process))
	((new-licensed-tw-process-permitted-p authorized-products))
	(t (notify-user-if-possible
	     (process-count-exceeded-goodbye-message tw))
	   (abort-telewindows-top-level 'process-count-exceeded)))))

(defmacro do-telewindows-per-process-checks (authorized-products)
  `(initialize-network-scheduler-interweave-matrix ,authorized-products))

;; jh, 1/6/92.  Functionized do-telewindows-per-process-checks because the inlined
;; version was breaking the HP compiler in the Telewindows function
;; change-login-box-size.  Moved from SEQUENCES1 because G2 does not include some
;; of the referenced function.


;;; `Telewindows-authorized-products' is initially nil.  The Telewindows
;;; authorization process causes it to be set to a (gensym-list) copy of the
;;; list of authorized product symbol(s).
;;;
;;; `Telewindows-license-level' is initially -1.  -1 means that this is not an
;;; authorized Telewindows, but may be used as a floating Telewindows.  The
;;; level gets incremented to a nonnegative value if and only if a successful
;;; authorization takes place.  A value lower than -1, -2, is used for the case
;;; of a Telewindows that is denied access even as a floating Telewindow.  The
;;; possible levels, then, are:
;;;
;;;  -2 (unauthorized)
;;;  -1 (floating)
;;;   0 (embedded)
;;;   1 (runtime)
;;;   2 (restricted-use)
;;;   3 (development)
;;;
;;; A value of 3 (development) is the default for a Telewindows that does not
;;; specify any other license option.  With this option, a Telewindows should
;;; never consume a `Floating Telewindows License'.  With a value of -1,
;;; Telewindows must always consume a Floating Telewindows License in order to
;;; operate.  The in-between values can go either way: a Floating Telewindows
;;; License is consumed iff connecting to a G2 with a higher license level.

(def-system-variable telewindows-authorized-products sequences1 nil)
(def-system-variable telewindows-license-level sequences1 -1)


(defun telewindows-license-level (authorized-products)
  (or
    (loop for product in authorized-products
	  thereis (case product
		    (embedded-option 0)
		    (runtime-option 1)
		    (restricted-use-option 2)))
    3))



;;; `Record-telewindows-authorized-products' is called once and only once for a
;;; Telewindows process that has been authorized for at least a level 0
;;; (embedded) license.  If this is never called, then the Telewindows may still
;;; be used, but it will only be used if a floating license can be granted.
;;;
;;; Note that unlike G2, Telewindows authorizations are not Lisp system process
;;; wide, but rather only Telewindows process wide.
;;;
;;; Note that there is at present no way to require that a floating license only
;;; be used, not to prefere a floating license to a standalone license, nor to
;;; prohibit a floating license to be consumed if it is available and there is
;;; not sufficient standalone capability.  Choosing among these variations may
;;; be supported at a later date.

(defun record-telewindows-authorized-products (authorized-products)
  (setq telewindows-authorized-products
	(copy-list-using-gensym-conses authorized-products))
  (setq telewindows-license-level
	(telewindows-license-level authorized-products)))


;;; `Telewindows-license-level-from-product' maps from a "product" to a level.
;;; Its inverse is `get-telewindows-product-from-level', which maps from a
;;; product to a level.  The function `get-telewindows-product-name-from-level'
;;; is similar, but maps from a level to a `product name', which may be slightly
;;; different than the product, e.g., RUNTIME (product name) vs. RUNTIME-OPTION
;;; (product).
;;;
;;; `Get-telewindows-authorization-state' maps from a level to one of the 3
;;; possible working states of Telewindows: FLOATING (unauthorized but using an
;;; available floating Telewindows license), RUNTIME (authorized for connection
;;; to a runtime or embedded G2), DEVELOPMENT (authorized for connection to
;;; a development or restricted use G2).

(defun telewindows-license-level-from-product (product)
  (case product
    (unauthorized -2)
    (floating -1)
    (embedded-option 0)
    (runtime-option 1)
    (restricted-use-option 2)
    (development 3)
    #+development
    (t (cerror "continue" "~a is an unknown Telewindows product!" product))))

(defun get-telewindows-product-from-level (level)
  (case level
    (-2 'unauthorized)
    (-1 'floating)
    (0 'embedded-option)
    (1 'runtime-option)
    (2 'restricted-use-option)
    (3 'development)
    #+development
    (t (cerror "continue" "~a is an unknown level" level))))

(defun get-telewindows-product-name-from-level (level)
  (case level
    (-2 'unauthorized)
    (-1 'floating)
    (0 'embedded)
    (1 'runtime)
    (2 'restricted-use)
    (3 'development)
    #+development
    (t (cerror "continue" "~a is an unknown level" level))))

(defun get-telewindows-authorization-state (level)
  (case level
    (-2 nil)
    (-1 'floating)
    ((0 1) 'runtime)
    ((2 3) 'development)
    #+development
    (t (cerror "continue" "~a is an unknown level" level))))

(defun telewindows-licensed-for-product-p (product)
  (>=f telewindows-license-level
       (telewindows-license-level-from-product product)))



;;; `Authorize-telewindows-if-ok' (given misleading-name
;;; `change-login-box-size') gets the machine id, obtains the entry for the
;;; machine id in the tw.ok file, and checks the numbers to see if they are ok.
;;; If so, telewindows is authorized.  If not, an error is printed and the
;;; process is aborted.
;;;
;;; This function is implemented as a series of when and unless forms, which may
;;; contain non-local exits, i.e., calls to abort the Telewindow process.  If we
;;; make it through all of them, TW is authorized.

(defun change-login-box-size ()
  (multiple-value-bind
      (machine-id ok-number1 ok-number2 ok-number3 ok-number4 ok-number5
		  start-date? expiration-date? authorized-products 
		  number-of-processes?)
      (warp-login-box-1)
    (when (memq 'floating authorized-products)
      (when (eq verbosity-level 'verbose)
	(notify-user-if-possible
	  "~%[Telewindows: will attempt to connect using a Floating Telewindows authorization ...]~%"))
      (return-from change-login-box-size nil))
    (unless ok-number1
      (return-from change-login-box-size nil))
    (unless (make-small-workspace
	      machine-id ok-number1 ok-number2 ok-number3 ok-number4 ok-number5
	      start-date? expiration-date? authorized-products 
	      number-of-processes?)
      (when (eq verbosity-level 'verbose)
	(notify-user-if-possible
	  "[Telewindows: entry for machine ID ~s incorrect.]"
	  machine-id)
	(notify-user-if-possible
	  "[Telewindows: will attempt to connect using a Floating Telewindows authorization ...]"))
      (force-output)
      (return-from change-login-box-size nil))
    (when start-date?  ; and expiration-date?
      (let* ((date (get-tw-universal-date))
	     (too-early? (<f date start-date?))
	     (too-late? (>f date expiration-date?)))
	(when (or too-early? too-late?)
	  (when (eq verbosity-level 'verbose)
	    (let ((date-string
		    (twith-output-to-text-string
		      (multiple-value-bind
			  (day month year)
			  (decode-universal-date
			    (if too-late? expiration-date? start-date?))
			(tformat-tw-decoded-date day month year)))))
	      (notify-user-if-possible
		"~%[Telewindows: ~a~a; will attempt to connect using a Floating Telewindows authorization ...]~%"
		;; The no space in ~a~a is intentional since the (too-...-message)'s
		;; already end in a space. - jpg 2/27/03
		(if too-late?
		    (too-late-telewindows-authorization-message)
		    (too-early-telewindows-authorization-message))
		date-string)
	      (reclaim-text-string date-string)))
	  (return-from change-login-box-size nil))))
    (authorize-telewindows)
    (when ;(and (machine-id-of-site-p machine-id) expiration-date?)
	(machine-id-of-site-p machine-id) ;; ddm 3/21/00
      (c-nsleep machine-id))
    (set-local-machine-id-in-use machine-id) ; (MHD 7/4/00)
    (set-telewindows-authorization-info
      machine-id ok-number1 ok-number2
      ok-number3 ok-number4 ok-number5
      start-date? expiration-date?
      (compute-product-code authorized-products)
      number-of-processes?)
    (record-telewindows-authorized-products authorized-products)
    (do-telewindows-per-process-checks authorized-products)))



;;; `Get-telewindows-ok-entry' (given misleading name `warp-login-box-1') takes
;;; as argument a machine id and returns the authorization numbers from the
;;; entry in the tw.ok file corresponding to the machine id, or nil if the entry
;;; does not exist.

(defun-allowing-unwind warp-login-box-1 ()
  (find-machine-id-in-telewindows-ok-file))



;;; `Compute-telewindows-authorization-numbers' (given misleading name
;;; enlarge-telewindows-memory) takes a machine id as argument and computes the
;;; four authorization numbers from it using the *random-state-array* mechanism.
;;; Machine-id is a string.  Generate-large-random is called iteratively to
;;; modify this array in a manner similar to that used by g2-random for
;;; generating random numbers.  However, because random-state-array, and the
;;; pointers *random-state-array-current-pointer* and
;;; *random-state-array-24-pointer* are initialized to the same value each time,
;;; the results are completely deterministic; the same four numbers will always
;;; be computed for any given machine id.

(defun enlarge-telewindows-memory 
       (machine-id start-date? expiration-date?
	authorized-products-bitmask number-of-processes?)
  (shrink-telewindows-memory 
    machine-id start-date? expiration-date?
    authorized-products-bitmask number-of-processes?)
  (setq *random-state-array-current-pointer* 54)
  (setq *random-state-array-24-pointer* 30)
  (loop for i from 1 to 500
	do (generate-large-random))
  (values (aref *random-state-array* 0) (aref *random-state-array* 1)
	  (aref *random-state-array* 2) (aref *random-state-array* 3)))



;;; Initialize-state-array-for-telewindows-authorization (given misleading name
;;; shrink-telewindows-memory) takes a machine id (a string) as argument and
;;; initializes *random-state-array*.  It does this by converting each alphanumeric
;;; digit in the machine id to a number between 0 and 35, and then looping through
;;; these numbers until the array is full.

(defun shrink-telewindows-memory 
    (machine-id start-date? expiration-date?
		authorized-products-bitmask number-of-processes?)
  (unless *random-state-array*
    (setq *random-state-array*
	  (with-permanent-array-creation
	    (make-array 55 :element-type 'fixnum))))
  (loop for state-array-index from 0 to 54 do 
       (setf (aref *random-state-array* state-array-index)
	  (choose-tw-numeric-seed-macro)))
  (loop with state-array-index = 0
	for i from 0 below (text-string-length machine-id)
	as weight? = (digit-char-pw (charw machine-id i) 36)
	do
    (when weight?
       (setf (aref *random-state-array* state-array-index) weight?)
      (incff state-array-index))
	until (=f state-array-index 55))
  (setf (aref *random-state-array* 54) 1)
  ;; to ensure at least one odd number

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
  (when (tw-japanese-authorized-code-p authorized-products-bitmask)
    (setf (aref *random-state-array* 11)
	  (logxorf (aref *random-state-array* 11) 89342)
	  (aref *random-state-array* 12)
	  (logxorf (aref *random-state-array* 12) 14783)
	  (aref *random-state-array* 13)
	  (logxorf (aref *random-state-array* 13) 28335)
	  (aref *random-state-array* 14)
	  (logxorf (aref *random-state-array* 14) 67482)))
  (when (tw-korean-authorized-code-p authorized-products-bitmask)
    ;; The numbers are completely random; but they must be kept in
    ;; synch with what's in NUMBERS.
    (setf (aref *random-state-array* 11)
	  (logxorf (aref *random-state-array* 11) 29138)
	  (aref *random-state-array* 12)
	  (logxorf (aref *random-state-array* 12) 40417)
	  (aref *random-state-array* 13)
	  (logxorf (aref *random-state-array* 13) 57969)
	  (aref *random-state-array* 14)
	  (logxorf (aref *random-state-array* 14) 15408)))
  (when number-of-processes?
    (setf (aref *random-state-array* 15)
	  (logxorf (aref *random-state-array* 15) (*f number-of-processes? 47))
	  (aref *random-state-array* 16)
	  (logxorf (aref *random-state-array* 16) 11963)
	  (aref *random-state-array* 17)
	  (logxorf (aref *random-state-array* 17) 67802)
	  (aref *random-state-array* 18)
	  (logxorf (aref *random-state-array* 17) 19575))) ; yes, ....
  ;; ... yes, 18 would have made sense, but the 17 wants to remain forever now
  ;; that it's been there, unless we "rev" this.  Not likely.

  ;; Added in 4.0 beta phase 2:  (MHD 1/28/95)
  (when (or (tw-runtime-option-authorized-code-p authorized-products-bitmask)
	    (tw-restricted-use-option-authorized-code-p authorized-products-bitmask)
	    (tw-embedded-option-authorized-code-p authorized-products-bitmask))
    ;; development is the default, and is implied by the other ones not present;
    ;; the others are mutually exclusive; the Japanese and Korean options are
    ;; obsolete, but were historically included in other slots; see above
    (setf (aref *random-state-array* 19)
	  (logxorf (aref *random-state-array* 19) authorized-products-bitmask))))

;; Note that there is no need to explicitly check for non-alphanumeric characters
;; since the call to digit-char-p returns nil for them.  Also, digit-char-p
;; returns the same weight for upper and lower case alphabetic characters so there
;; is no need to explicitly convert to upper case.

;; The initialization to 12345 (rather than 0) helps make authorization numbers
;; large.  Iterating more than 500 times would also do this.



(defun get-tw-universal-date ()
  (with-temporary-bignum-creation
    (multiple-value-bind (second minute hour day month year)
	(get-decoded-real-time)
      (declare (ignore second minute hour))
      (encode-universal-date day month year))))



(defun tformat-tw-decoded-date (day month year)
  (tformat "~d ~a ~d" 
	   day
	  (case month
	    (1 "Jan")
	    (2 "Feb")
	    (3 "Mar")
	    (4 "Apr")
	    (5 "May")
	    (6 "Jun")
	    (7 "Jul")
	    (8 "Aug")
	    (9 "Sep")
	    (10 "Oct")
	    (11 "Nov")
	    (12 "Dec"))
	  year))



(defmacro perform-secret-checking ()
  `(progn
     (cond
       ((=f clogged-count 5000)
	(telewindows-screen-list-too-big))
       ((=f clogged-count 10000)
	(cache-icon-in-system-table)))
     (if (>f clogged-count 0)
	 (incff clogged-count))))




;; `Inhibit-secret-checking-if-appropriate' sets clogged count to -1 for a
;; floating telewindows license, which makes it stop its slow but inevitable
;; climb towards 5000, at which point it will not like to find Telewindows
;; unauthorized.  This makes floating telewindows work. This must be called just
;; once, and before perform-secret-checking is called too many times; preferably
;; in a different place.  We ensure this by calling this every time
;; service-current-telewindows-workstation is called.

(defmacro inhibit-secret-checking-if-appropriate ()
  `(if (and (>=f clogged-count 0)
	    (eql (telewindows-connection-license-level? current-workstation) -1))
       (setf clogged-count -1)))






;;;; String Hashing and Gensym-symbol-hash




;;; The following functions implement hashing schemes peculiar to the
;;; authorization schemes of SEQUENCES1.  Because of the particular set of
;;; characters it pays attention to, transforms, and ignores, it shouldn't be
;;; used as a general hashing scheme outside of SEQUENCES1.

;;; Gensym-symbol-hash, given a symbol, returns a non-negative integer which is
;;; less than modulus. Modulus must be positive and less than half of
;;; most-positive-fixnum. The result is deterministic and machine independent,
;;; even if the machine uses EBCDIC, provided that digit-char-p is correctly
;;; implemented.

;;; Gensym-symbol-hash-with-modulus is the same but takes a modulus argument.

;;; The computation uses all alphanumeric characters as base 36 numbers and
;;; ignores others.  These characters are assembled in groups of 4 into a
;;; fixnum.  If the number of alphanumeric characters is not a multiple of 4,
;;; the last group is shifted so that the low rather than the high order bits
;;; are zeros. The fixnums resulting from this process are all added modulo the
;;; mdulus to give a value.

;;; Note that non-alphanumerics and case are ignored, e.g. "abC3" and "AB-c3*"
;;; as print names hash equivalently.

;;; Text-string-hash does exactly the same thing, but for text strings.

(defconstant default-text-string-hash-modulus
  (1-f (halff most-positive-fixnum)))

(defun-simple gensym-symbol-hash (symbol)
  (gensym-symbol-hash-with-modulus symbol default-text-string-hash-modulus))

(defun-simple gensym-symbol-hash-with-modulus (symbol modulus)
  (text-string-hash-with-modulus (symbol-name-text-string symbol) modulus))

(defun-simple text-string-hash (text-string)
  (text-string-hash-with-modulus
    text-string
    default-text-string-hash-modulus))

(defun-simple text-string-hash-with-modulus (text-string modulus)
  (loop with length = (lengthw text-string)
	with accumulator = 0
	with packer = 0
	with packing-index = 0
	for name-index from 0
	until (=f name-index length)
	for char = (charw text-string name-index)
	when (alphanumericpw char)
	  do (setq packer (+f (ashf packer 6) (digit-char-pw char 36)))
	     (incff packing-index)
	     (when (=f 0 (logandf packing-index 3))
	       (setq accumulator
		     (modf-positive
		       (+f (modf-positive accumulator modulus) packer)
		       modulus))
	       (setq packer 0))	    
	finally
	  (when (>f packer 0)
	    (setq packer (ashf packer (*f 6 (-f 4 (logandf packing-index 3)))))
	    (setq accumulator
		  (modf-positive
		    (+f (modf-positive packer modulus) accumulator)
		    modulus)))	    
	  (return accumulator)))

;; Previously named gensym-string-hash.  (MHD 5/12/96)

;; Time of TI Explorer II:
;;    (gensym-symbol-hash 'abc 8388607) takes 176 u-sec.
;;    (gensym-symbol-hash 'abcdefghijklmnopqrstuvwxyz01234567890 8388607)
;;                             takes 1820 u-sec.





;; Gensym-symbol-hash section (String Hashing Facility) moved to UNICODE. (MHD 5/13/96)






;;;; Encoding User Passwords


;;; Encoding of passwords is done by both by Telewindows and G2, and must
;;; produce exactly the same results on both sides, i.e., use this common
;;; (identical) encoding source code.


;;; Encode user-password has as value a machine independent fixnum
;;; (small enough to be a fixnum on TI). It is a medium sophisitication
;;; randomizer. It produces about 24 bits of stuff, and should be fairly
;;; random. That is, there should be less than a chance in a million of
;;; an incorrect password encoding to the correct number. The value is
;;; positive.

;; The efficiency could easily be improved by using the internals of
;; gensym-symbol-hash. There is probably no good reason to do this.

;;; Encode-user-password-string does the exact same thing, but for strings.

(defmacro encode-user-password-string (string)
  (let ((string-value '#:string-value))
    `(let* ((,string-value ,string)
	    (x1 (text-string-hash-with-modulus ,string-value 4051))
	    (x2 (text-string-hash-with-modulus ,string-value 4003))
	    (x3 (text-string-hash-with-modulus ,string-value 3943))
	    (x4 (text-string-hash-with-modulus ,string-value 3889))
	    (y1 (logiorf
		  (ashf x1 -6)
		  (ashf (logandf x4 63) 6)))
	    (y4 (logiorf
		  (ashf x4 -6)
		  (ashf (logandf x1 63) 6))))
       (+f 1 (logxorf (*f y1 y4) (*f x2 x3))))))

;;; The function `encode-user-password-string-function' is just a functional
;;; variant of encode-user-password-string.  It had to be created just so it
;;; could be forward referenced from a command line argument processing function
;;; defined in an earlier module.

(defun-simple encode-user-password-string-function (string)
  (encode-user-password-string string))

;; Note that putting a symbol naming this code is not a security issue for G2,
;; and would if anything be a red herring for those malicious intent.  (MHD
;; 4/11/97)


(defmacro encode-user-password (symbol)
  `(encode-user-password-string (symbol-name-text-string ,symbol)))

;; It is not great to be turning passwords into symbols; probably we could be by
;; without doing that.  Probably, either way, we could get by without encode-user-
;; password (the one for symbols). (MHD 3/2/90)





;;; `Encode-password-via-md5' is used to compute the hashed password
;;; value given the username and clear text password.  Note that the
;;; first two parameters is a symbol when this is called from the change mode
;;; (aka login, or g2-login) dialog and a string when called from the
;;; command line handling.

(defun-simple encode-password-via-md5 (user-name? password? default-result?)
  (macrolet ((with-simple-gensym-string ((var length) &body body)
	       `(let ((,var (obtain-simple-gensym-string ,length)))
		  (prog1
		      (progn
			,@body)
		    (reclaim-simple-gensym-string ,var))))
	     (update-md5-context-with-string-or-symbol (x)
	       `(let ((str (string-downcasew (if (symbolp ,x) (symbol-name-text-string ,x) ,x))))
		  (update-md5-context str)
		  (reclaim-text-string str))))
    (cond ((and user-name? password?)
	   (init-md5-context)
	   (update-md5-context #w"user:")
	   (update-md5-context-with-string-or-symbol user-name?)
	   (update-md5-context #w":password:")
	   (update-md5-context-with-string-or-symbol password?)
	   (with-simple-gensym-string (string 16)
	     (finalize-md5-context string)
	     (convert-md5-result-string-to-hex-string string 16)))
	  (t
	   default-result?))))

;; user:ed:password:alphabet -MD5-> ceb6d1ab8509c56b72b52b968839e371

(defun-simple convert-MD5-result-string-to-hex-string (simple-gensym-string length)
  (nstring-downcasew   ; had been string-downcase until 2/9/98,
	               ; but that leaks
    (twith-output-to-text-string
      (loop with result-string = simple-gensym-string
	    for i from 0 below length
	    as value = (char-code (schar result-string i))
	    do
	(if (<f value 16)
	    (tformat "0~x" value)
	    (tformat "~x" value))))))

;;; consumes its arg

(defun-simple convert-uuid-string-to-hex-string (wide-string length)
  (let ((new-string
	  (nstring-downcasew
	    (twith-output-to-text-string
	      (loop with result-string = wide-string
		    for i from 0 below length
		    as value = (charw-bv16 result-string i)
		    do
		(tformat "~x" value))))))
    (reclaim-wide-string wide-string)
    new-string))

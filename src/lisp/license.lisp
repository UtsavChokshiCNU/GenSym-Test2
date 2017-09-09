;;;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module LICENSE: A very simple server to hand out G2 licenses

;;; Copyright (c) 2010 Versata Software, Inc.
;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author: Ben Hyde
;;; Subsequently: David McDonald and Mark David
;;; Subsequently: Chun Tian (binghe)

;;;; Introduction

;;; This module implements a licensing server for Gensym.  The section MAIN
;;; below includes the function eval-licensing-request and implements the read
;;; eval print loop of the server.  The networking protion of this mechinism in
;;; in the module LUCID-SERVER (now LISP-SERVER).



;;;; Forward References

(declare-forward-reference cl-user::make-ok function)
(declare-forward-reference cl-user::find-back-door function)
(declare-forward-reference cl-user::compute-tw-codes function)
(declare-forward-reference cl-user::compute-tw2-codes function)
; (declare-forward-reference cl-user::make-particular-package-ok function)
(declare-forward-reference make-particular-package-ok function)
(declare-forward-reference cl-user::convert-input-to-universal-date-offline function)
(declare-forward-reference cl-user::compute-bridge-authorizations function)
(declare-forward-reference cl-user::bridge-universal-date function)
; (declare-forward-reference cl-user::adjust-version-if-necessary function)
(declare-forward-reference cl-user::legal-machine-id-p function)
(declare-forward-reference cl-user::optional-modules-map variable)
(declare-forward-reference cl-user::encode-universal-date function)
(declare-forward-reference cl-user::reference-date-for-interval-encoding variable)
(declare-forward-reference cl-user::jan-1-1990 variable)
(declare-forward-reference cl-user::jan-1-1998 variable)
(declare-forward-reference cl-user::jan-1-2006 variable)
(declare-forward-reference cl-user::jan-1-2009 variable)
(declare-forward-reference cl-user::jan-1-2015 variable)

;;;; Property List Utlities

;;; This section contains tools for checking that a property list is well
;;; formed.  These are needed since we record the description of a product as
;;; human editted property list and if these are not well formed then the tragic
;;; events will happen when the server attempts to use the description.


(defun-for-macro has-property-p (plist key)
  (loop for (actual-key value) on plist by #'cddr
        do (when (eq actual-key key) value (return t))
        finally (return nil)))

(defmacro plist-type-description (plist-type)
  `(get ,plist-type :plist-type-description))




;;; Def-plist provides a way to declare a type spec for a plist.
;;;    Def-plist <plist-type-name>  &body (<slot-key> <slot-description>)

;;; The slot description matches this grammar:
;;;   (<require-spec> <type-spec>)
;;;   <require-spec> : required
;;;                    optional
;;;                    (required-for  <slot-name> <value>)
;;;                    (required-with <slot-name>)
;;;   <type-spec> : <common-lisp-type-spec>

;;; A required slot must always appear, an optional slot may appear.  Duplicate
;;; slots are (?) considered an error.  A required for slot is required when 
;;; another slot's value takes on a particular value.  A required-with slot
;;; is required when another slot appears.

;;; The slot, if it appears, must match the common lisp type spec given.

(defmacro def-plist (type-name &body slot-descriptions-plist)
  (block semantic-checking
    (setf slot-descriptions-plist (copy-tree slot-descriptions-plist))
    (unless (evenp (length slot-descriptions-plist))
      (warn "Slot descriptions for ~S malformed" type-name)
      (return-from semantic-checking nil))
    (loop with require-spec
          ;; with type-spec
          for (slot-name slot-description) 
          on slot-descriptions-plist by #'cddr
          do
          (unless (eq 2 (length slot-description))
            (warn "Malformed plist slot description for ~S in ~S" slot-name type-name)
            (return-from semantic-checking nil))
          (setq require-spec (first slot-description))
          ;; (setq type-spec (second slot-description))
          (unless (typecase require-spec
                    (atom
                     (when (memq require-spec '(required optional))
                       (setf (first slot-description) (list require-spec))
                       t))
                    (t
                     (let ((require-operation (car require-spec)))
                       (case require-operation
                         (required-for
                          (and 
                           (= 3 (length require-spec))
                           (has-property-p slot-descriptions-plist (second require-spec))))
                         (required-with
                          (and
                           (= 2 (length require-spec))
                           (has-property-p slot-descriptions-plist (second require-spec)))) 
                         (t
                          nil)))))
            (warn "Malformed plist slot description for ~S in ~S" slot-name type-name)
            (return-from semantic-checking nil))))
  `(progn
     (setf (plist-type-description ',type-name)
           ',slot-descriptions-plist)
     ',type-name))


(defun check-plist-instance (plist-type instance)
  (block checking
    (macrolet ((fail (reason-keyword slot-name) 
                     `(return-from checking
                                   (values nil ,reason-keyword instance ,slot-name))))
      (let ((slot-descriptions-plist (plist-type-description plist-type)))
        ;; 1. Scan instance checking type of each slot.
        (loop for (key value) on instance by #'cddr
              as (require-spec type-spec) = (getf slot-descriptions-plist key)
              unless require-spec
              do (fail :unexpected-slot-in-instance key)
              unless (typep value type-spec)
              do (fail :slot-value-of-wrong-type key))
        ;; 2. Scan plist description checking requirements.
        (loop for (slot-name (require-spec nil)) on slot-descriptions-plist by #'cddr
              as required-kind = (if (symbolp require-spec)
                                   require-spec
                                   (car require-spec))
              do (case required-kind
                   (optional nil)
                   (required 
                    (unless (has-property-p instance slot-name)
                      (fail :required-slot-is-missing slot-name)))
                   (required-with
                    (when (and (has-property-p instance (second require-spec))
                               (not (has-property-p instance slot-name)))
                      (fail :required-with-slot-is-missing slot-name)))
                   (required-for
                    (when (and (has-property-p instance (second require-spec))
                               (eql (third require-spec)
                                    (getf instance (second require-spec)))
                               (not (has-property-p instance slot-name)))
                      (fail :required-for-slot-is-missing slot-name))) 
                   ))))
    t))



;;;;  Useful Type Specifications

(deftype boolean () '(member nil T))

(defun length-of-four-p (x)
  (= 4 (length x)))

(defun every-integer-p (x) 
  (every #'integerp x))

(deftype package-authorization-codes
         ()
  '(and list
    (satisfies every-integer-p)
    (satisfies length-of-four-p)))

(deftype non-nil-symbol ()
  `(and (not null) symbol))

(deftype type-specification () 'cons)

(defun list-of-strings-p (x)
  (and (consp x)
       (every #'string x)))

(deftype list-of-strings () '(satisfies list-of-strings-p))

(defun fixnum-or-nil-p (x)
  (or (null x) (fixnump x)))

(deftype fixnum-or-nil () '(satisfies fixnum-or-nil-p))
			     



(defun get-day-number-of-date-list (date-info)
  (let* ((day (first date-info))
	 (month (second date-info))
	 (year (third date-info)))
    (+ (* 365 (if (< year 100)
                (- year 70)
                (- year 1970)))
       day
       (second (assoc month
                      '((1 0) (2 31) (3 60)
                        (4 91) (5 121) (6 152)
                        (7 182) (8 213) (9 244)
                        (10 274) (11 305) (12 335)))))))

(defun convert-date-list? (date-list?)
  (when date-list?
    (setf (second date-list?)
	  (nth (second date-list?)
	       '(foo
		 cl-user::jan cl-user::feb cl-user::mar
		 cl-user::apr cl-user::may cl-user::jun
		 cl-user::jul cl-user::aug cl-user::sep
		 cl-user::oct cl-user::nov cl-user::dec))))
  date-list?)


;;; `Check-dates-for-validity' subsumes and refines a set of
;;; checks make in earlier versions. In particular it tests
;;; for valid intervals and prohibits two digit dates.
;;; The arguments come in as triples of numbers, e.g. (6 24 1998)
;;; The argument bridge-p should be true if this is a bridge authorization.
;;; In this case, this knows not to check for the limitations in some
;;; versions of G2 on temporary authorizations starting past a certain
;;; year, which limitations are not present for bridge temporary dates.

;;; G2-authorization-method-p is used for a limitation on start and end times
;;; that is specific to G2's authorization method. This argument is documented
;;; for function check-authorization-interval-for-validity, see below.

(defun check-dates-for-validity (start end g2-authorization-method-p)
  (unless (= 3 (length start))
    (error "Dates must be a list of three elements: (<day> <month> <year>) not ~S." start))
  (when end
    (unless (= 3 (length end))
      (error "Dates must be a list of three elements: (<day> <month> <year>) not ~S." end)))
  (unless (every #'(lambda (x) (fixnump x)) start)
    (error "Dates must be given as fixnums, e.g. (6 24 1998), not ~s" start))
  (when end
    (unless (every #'(lambda (x) (fixnump x)) end)
      (error "Dates must be given as fixnums, e.g. (6 24 1998), not ~s" end)))
  (unless (and (<= 1 (first start) 31)
	       (<= 1 (second start) 12))
    (error "Bad values for either the day or the month of the start time. The order is <day> <month>"))
  (when end
    (unless (and (<= 1 (first end) 31)
	       (<= 1 (second end) 12))
    (error "Bad values for either the day or the month of the end time. The order is <day> <month>")))
  (when (<=f (third start) 99)
    (error "Years must be stated as four digit quantities."))
  (when (and end
	     (<=f (third end) 99))
    (error "Years must be stated as four digit quantities."))
  (unless (<= 1970 (third start) 2060) ;; Note a
    (error "The year ~s cannot be represented" (third start)))
  (when end
    (unless (<= 1970 (third end) 2060)
      (error "The year ~s cannot be represented" (third end))))
  (when end
    (check-authorization-interval-for-validity
      (cl-user::encode-universal-date
	(first start) (second start) (third start))
      (cl-user::encode-universal-date
	(first end) (second end) (third end))
      g2-authorization-method-p)))

;; Note a: Inspection suggests that because this value is
;; encoded into 2 bytes in the make-ok code 2079 is an upper limit.
;; The code in bridge and package auth, appears to safe for much
;; longer, packages seem to do 3 bytes of stuff.



;;; Check-authorization-interval-for-validity checks for problems with start and
;;; end.  One is that start comes after end, and another is the interval is not
;;; greater than 5 years, which is a policy restriction.
;;;
;;; If g2-authorization-method-p is true, this is assumed to be for G2, and in
;;; this case there is an implementation limitation for the start and end that
;;; is G2 version specific.  The old G2's cannot have start dates that are after
;;; Jan. 10, 2001, while newer G2's (G2 5.1 or later) can.  Note: this is made
;;; to work for post-1-10-2001 end dates by having
;;; cl-user::reference-date-for-interval-encoding bound higher up by a caller
;;; (function license-1) that knows the G2 version this is for and its
;;; corresponding reference date.  For non-G2 products (bridge, kb, tw, tw2),
;;; there is no meaningful restriction on start and end dates for at least
;;; several decades beyond the release of G2 5.1 in the late 1990's.

(defun check-authorization-interval-for-validity (start end g2-authorization-method-p)
  (cond ((<f end start)
	 (error "The authorization end date must be later than the start date."))
	((and g2-authorization-method-p
	      (not (<=f cl-user::reference-date-for-interval-encoding
			start
			(+f cl-user::reference-date-for-interval-encoding
			    #.(* 11 366)))))
	 (error "The start date for an interval is outside its legal range."))
	((>f (-f end start)
	     #.(* 5 366))
	 (error "The authorization interval may not exceed 5 years."))))




(defun valid-optional-modules-p (product-optional-modules)
  (and (listp product-optional-modules)
       (loop for optional-module in product-optional-modules
	     as info? = (find optional-module
			      cl-user::optional-modules-map
			      :key 'first
			      :test 'string=)
	     as public = (if info? (not (fourth info?)))
	     always (or public
			(eq 'kfep optional-module)))))

;; KFep isn't public anymore, but for old versions we must
;; treat it as if it were when handing out licenses.







;;;; The Plist Type product-info

(def-plist product-info
  :product-text-name (required string)
  :product-version (required string)
  
  :product-symbolic-name (required symbol)
;  :short-name (required string)
;  :menu-name (required string)    ;; Eliminated 2/1/95
  :description (required string)
;  :shipping (required boolean)    ;; Eliminated 2/1/95
  
  :authorization-method (required (member telewindows telewindows2 g2 g2-package bridge))

  :additional-information (optional list-of-strings)
  :package-authorization-codes ((required-for :authorization-method g2-package)
                                package-authorization-codes)
  :package-name-for-ok-object ((required-for :authorization-method g2-package)
                               non-nil-symbol)
  :g2-version-switch ((required-for :authorization-method g2) 
                      (member nil t 3 4 5 6 7 8 83 9 11 12)) ;; Note: 7 never actually used for G2
  :bridge-revision-switch ((required-for :authorization-method bridge)
                           (member revision-1 revision-2))
  :telewindows-version-number-as-float ((required-for :authorization-method telewindows) 
                                        float)
  :tw2-version-number ((required-for :authorization-method telewindows2)
		       fixnum)
  :default-process-count ((required-with :process-count-spec)
                          fixnum)
  :default-tw-process-count (optional
			      fixnum)
  :default-t2-process-count (optional
			      fixnum-or-nil)
  :process-count-spec (optional
                       type-specification))






;;;; Database of Product Descriptions


;;; `*product-records*' is a list of plists, each list is a well formed
;;; instance of the type outlined in the last section.  This is read in
;;; by the reader in the next section.

(defvar *product-records* nil)

(defun product-info (product-name)
  (loop for product-record in *product-records*
        when (eql product-name (getf product-record :product-symbolic-name))
        do (return product-record)))



;;;; Reader for Product Descriptions


;;; As necessary, for example on startup, we read in a fresh value for
;;; *product-records*.   This section includes the reader that does this.
;;; The reader checks that each instance is well formed.

;;; For delivered application, it will search the two config files in current
;;; directory; and for running in LispWorks, absolute pathname was used, based
;;; on SRCBOX pathname.  -- Chun Tian (binghe)

(defparameter the-product-info-file
  (if (hcl:delivered-image-p)
      #p"products.lisp"
    (merge-pathnames #p"lic/server/products.lisp" source-directory-name)))

(defparameter the-licensing-users-file
  (if (hcl:delivered-image-p)
      #p"licensing-users.lisp"
    (merge-pathnames #p"lic/server/licensing-users.lisp" source-directory-name)))

(pushnew :nbv *features*)  ;; UGH!

;;; `Read-in-product-descriptions' is called at startup to create
;;; the product records.

(defun read-in-product-descriptions ()
  (let ((*package* (find-package "AB"))
        (*features* (list* 'nbv *features*)))
    (cond
      ((probe-file the-product-info-file)
       (with-open-file (f the-product-info-file)
	 (setf *product-records*
	       (loop
		 for input-record = (read f nil :eof)
		 until (eql :eof input-record)
		 as package-info
		 = (validate-and-rewrite-product-description input-record)
		 when package-info
		   collect package-info))))
      (t
       (warn "Unable to find product info file.")))))

;;; Since mortals will probably edit that file we check the enties
;;; with reasonable care.

(defun validate-and-rewrite-product-description (input-record)
  (let ((error-message? nil)
        product-info)
    (block validating-package-description
      (macrolet ((fail-validation
                  (string)
                  `(progn (setf error-message? ,string)
                          (return-from validating-package-description nil)))
                 (check
                  (predicate string)
                  `(unless ,predicate (fail-validation ,string))))
        (check 
         (consp input-record) 
         "Only def-product-authorization forms may appear in the product-info file, but an atom was found.")

	(when (eq (car input-record) 'in-package)
	  (return-from validating-package-description nil))
	
        (check 
         (eql (car input-record) 'def-product-authorization)
         "Only def-product-authorization forms may appear in the product-info file, but and atom was found.")
        (check (and (consp (second input-record))
                    (= 2 (length (second input-record))))
               "the first argument to def-product-authorization must be a list of two elements")
        (setf product-info
              (let ((name (first (second input-record)))
                    (version (second (second input-record))))
                (list* :product-text-name name
                       :product-version version
                       :product-symbolic-name
		       (make-product-symbolic-name name version)
                       (cddr input-record))))
        (multiple-value-bind (flag why-failed? instance? slot-name?)
                             (check-plist-instance 'product-info product-info)
          (declare (ignore instance?))
          (check flag
                 (format 
                   nil
                   "Body of def-product-authorization for ~S is malformed. (~S is ~S)"
                   (first (second input-record))
                   slot-name?
                   why-failed?)))))
      (when error-message?
        (error error-message?))
      product-info))

;;; `Make-product-symbolic-name' is critical since it creates the name
;;; used by client requests to name products.

(defun make-product-symbolic-name (name version)
  (let ((string (concatenate'string
		  (string-upcase name)
		  "-"
		  (string-upcase version))))
    (loop for i from 0 below (length string)
	  unless (alphanumericp (char string i))
	    do (setf (char string i) #\-))
    (intern string)))



;;; `Def-product-authorization' to allow the products file to be part of the
;;; initial system we define this macro which will process each entry as if we
;;; we read it.

(defmacro def-product-authorization (&whole whole
					    (product version) &body plist)
  (declare (ignore product version plist))
  (let ((form (validate-and-rewrite-product-description whole)))
    `(update-product-database ',form)))

(defun update-product-database (valid-product-record)
  (let ((symbolic-name (getf valid-product-record :product-symbolic-name)))
    (setf *product-records*
	  (delete symbolic-name *product-records*
		  :key #'(lambda (record)
			   (getf record :product-symbolic-name))))
    (push valid-product-record
	  *product-records*)))



;;;; Adding Unusual Bridge Products


(defun validate-bridge-version (version-string bridge-revision-switch)
  ;;    V[0-9].[0-9]
  ;; or V[0-9].[0-9][AB]
  ;; or V[0-9]   (if the bridge-revsion-switch is revision-2)
  (let ((length (if (stringp version-string) (length version-string))))
    (and
     length
     (<= 2 length)
     (char-equal #\V (char version-string 0))
     (digit-char-p   (char version-string 1))
     (or
      (and
       (eq 'revision-2 bridge-revision-switch)
       (= 2 length))
      (and
       (<= 4 length 5)
       (char-equal #\. (char version-string 2))
       (digit-char-p   (char version-string 3))
       (or (= 4 length)
           (char-equal #\A (char version-string 4))
           (char-equal #\B (char version-string 4))))))))

(defun bridge-identifier-char-p (c)
  (or (alphanumericp c)
      (memq c '(#\_ #\-))))

(defun validate-bridge-product (product-string)
  ;; product-name: [A-Z][~-0-9_A-Z]*
  (and (stringp product-string)
       (< 1 (length product-string))
       (alpha-char-p (char product-string 0))
       (loop for index from 0 below (length product-string)
	     always (bridge-identifier-char-p (char product-string index)))))

(defun move-symbols-into-user-package (symbols)
  (loop for symbol in symbols
	collect (move-symbol-into-user-package symbol)))

(defun move-symbol-into-user-package (symbol)
  (intern (symbol-name symbol) user-package-in-this-lisp))



;;;; Simple Interface to Authorization Code

;;; This section provides a switching yard between the product
;;; descriptions and the various mechanisms that implement the
;;; authorization for assorted products.  The primary routine
;;; is compute-authroziation-codes.  This takes a product info,
;;; and the info about the license to grant.  It then  dispatches
;;; to a glue routine that calls the actual authorization computing
;;; code.  The glue routines do the ugly conversion between data
;;; formats etc. etc.  That arose over time as the designs for these
;;; suffered optomistic enhancement.



;;; `Compute-authorization-codes' provides a swiss army knife for creating
;;; product authorizations.   Given the product name along with a slew of
;;; other information it looks up that product's description in the product
;;; data base we just built.  It then computes authorization codes etc for
;;; that product.

(defun compute-authorization-codes (product-info 
				     machine-id
				     start-date-list? 
				     end-date-list?
				     product-process-limit?
				     telewindows-connection-limit
				     t2-connection-limit
				     product-optional-modules)
  (declare (special licensing-client-name))
  (let ((license (multiple-value-list
		     (funcall
		       (case (getf product-info :authorization-method)
			 (g2           'compute-g2-type-authorization)
			 (telewindows  'compute-tw-type-authorization)
			 (telewindows2 'compute-tw2-type-authorization)
			 (bridge       'compute-bridge-type-authorization)
			 (g2-package   'compute-g2-package-type-authorization))
		       :product-info     product-info
		       :machine-id       machine-id
		       :start-date?      start-date-list?
		       :end-date?        end-date-list?
		       :product-process-limit?    product-process-limit?
		       :optional-modules (move-symbols-into-user-package
					   product-optional-modules)
		       :telewindow-connection-limit telewindows-connection-limit
		       :t2-connection-limit t2-connection-limit
		       ))))
    (values-list license)))


;;; `Compute-telewindows-type-authorization' maps from standard authorization arguments
;;; to the argument pattern of the routine provided in numbers for authorization of
;;; telewindows.  This routine is paranoid only about the optional-modules.

(defun compute-tw-type-authorization (&optional
				       &key
				       product-info
				       machine-id
				       (start-date? nil)
				       (end-date? nil)
				       (product-process-limit? nil)
				       (optional-modules nil)
				       telewindow-connection-limit
				       t2-connection-limit)
  (declare (ignore telewindow-connection-limit t2-connection-limit))
  (let ((all-optional-modules
	  (let ((telewindows-version-number-as-float
		  (getf product-info :TELEWINDOWS-VERSION-NUMBER-AS-FLOAT)))
	    (cond
	      ((and (<= 3.0 telewindows-version-number-as-float)
		    (< telewindows-version-number-as-float 4.0))
	       '(japanese korean))
	      ((<= 4.0 telewindows-version-number-as-float)
	       '(; runtime ;; Note A
		 restricted-use
		 japanese korean chinese
		 ))
	      (t nil)))))
    (unless (every #'(lambda (x)
		       (member x all-optional-modules :test #'string-equal))
		   optional-modules)
      (error
	"Inapproprate optional modules, ~S, specified for compute-tw-type-authorization."
	optional-modules)))
  ;; Convert from the names users know to the names that happened to get
  ;; used in the internals of the code generation.
  (loop for (external-name internal-name)
	in '((runtime cl-user::runtime-option)
	     (restricted-use cl-user::restricted-use-option)
	     (embedded cl-user::embedded-option))
	do
    (when (member external-name optional-modules :test #'string=)
      (setf optional-modules
	    (substitute internal-name external-name
			optional-modules
			:test #'string=))))
  (cl-user::compute-tw-codes
    machine-id
    (first start-date?) (second start-date?) (third start-date?)
    (first end-date?)  (second end-date?) (third end-date?)
    optional-modules
    product-process-limit?
    (getf product-info :telewindows-version-number-as-float)
    ))

;; Note A -- Only restricted-use is actually used.
;;           this license is commonly known as a "runtime telewindows license."
;;           or sometimes as the deployment telewindows license.
;;           I.e. this license level is "high" enough to connect to a runtime,
;;           embedded or restricted use license.
;;  Meanwhile around Rev 33 we had a period when japanese and korean where
;;  not supported (i.e. they were free) but then they came back again.



;;; `Compute-tw2-type-authorization' is a near clone of its tw equivalent.
;;; The differences are that tw2 does not presently have any 'optional
;;; modules' other than the symbol that says what its license-level is.

(defun compute-tw2-type-authorization
    (&optional
      &key product-info machine-id
      (start-date? nil) (end-date? nil)
      product-process-limit?
      (optional-modules nil)
      telewindow-connection-limit t2-connection-limit)
  
  (declare (ignore telewindow-connection-limit t2-connection-limit
		   product-process-limit? ))
  
  (when (>f (length optional-modules) 1)
    (error "More than one item specified in the optional modules"))

  (let* ((version-number (getf product-info :tw2-version-number))
	 (all-optional-modules
	   '( restricted-use  ; only one so far. development is implicit
	     )))

    (unless (every #'(lambda (x)
		       (member x all-optional-modules
			       :test #'string-equal))
		   optional-modules)
      (error
	"Inapproprate optional modules, ~S, specified for ~
         compute-tw2-type-authorization."
	optional-modules))
    
    ;; Convert from the names users know to the names that happened to get
    ;; used in the internals of the code generation and switch their
    ;; packages while we're at it.
    (loop for (external-name internal-name)
	      in '((restricted-use cl-user::restricted-use-option))
	  do
      (when (member external-name optional-modules :test #'string=)
	(setf optional-modules
	      (substitute internal-name external-name
			  optional-modules
			  :test #'string=))))
    
    (cl-user::compute-tw2-codes
      machine-id
      (first start-date?) (second start-date?) (third start-date?)
      (first end-date?)  (second end-date?) (third end-date?)
      (first optional-modules)
      version-number )))




;;; `Compute-g2-type-authorization' maps from the standard suthorization arguements
;;; to the argument pattern of the authorization routine implemented in numbers.  It is
;;; not paranoid.

(defun compute-g2-type-authorization (&optional
				       &key
				       product-info
				       machine-id
				       (start-date? nil) ; nil is redundant!
				       (end-date? nil)
				       (product-process-limit? nil)
				       (optional-modules nil)
				       telewindow-connection-limit
				       t2-connection-limit)
  (values-list
    (nconc
      (multiple-value-list 
	  (cl-user::make-ok machine-id
			 (getf product-info :g2-version-switch)
			 optional-modules
			 end-date?
			 start-date?
			 product-process-limit?
			 (or telewindow-connection-limit 0)
			 (or t2-connection-limit 0)))
      (list
	(cl-user::find-back-door machine-id)))))


;;; `Compute-g2-package-type-authorization' maps from the standard authorization
;;; arguments to the arguments expected by the routine implemented in numbers.
;;; It is not paranoid.

(defun compute-g2-package-type-authorization (&optional
					       &key
					       product-info
					       machine-id
					       (start-date? nil)
					       (end-date? nil)
					       (product-process-limit? nil)
					       (optional-modules nil)
					       (telewindow-connection-limit 1)
					       t2-connection-limit)
  (declare (ignore telewindow-connection-limit t2-connection-limit
		   optional-modules
		   product-process-limit?))
  (let ((codes (getf product-info :package-authorization-codes)))
    (values-list
      (nconc
	;; The Codes
	(multiple-value-list
	  (make-particular-package-ok ;; cl-user::make-particular-package-ok
	    machine-id
	    (first codes) (second codes) (third codes) (fourth codes)
	    (if start-date?
		(cl-user::convert-input-to-universal-date-offline start-date?) 
		nil)
	    (if end-date?
		(cl-user::convert-input-to-universal-date-offline end-date?) 
		nil)))
	;; The package ID.
	(list (getf product-info :package-name-for-ok-object))))))




;;; `Compute-bridge-type-authorization' maps from the standard authorization argument
;;; pattern to the pattern provided by the authorization routine in numbers.  It is
;;; paranoid only in so far as it checks that the optional-modules passed are NIL.

(defun compute-bridge-type-authorization (&optional
                                          &key
                                          product-info
                                          machine-id
                                          (start-date? nil)
                                          (end-date? nil)
                                          (product-process-limit? nil)
                                          (optional-modules nil)
					  (telewindow-connection-limit 1)
					  t2-connection-limit)
  (declare (ignore product-process-limit?
		   telewindow-connection-limit t2-connection-limit))
  (when optional-modules
    (error "The optional modules ~S were passed to compute-bridge-type-authorization."))
  (let ((bridge-revision-switch
	  (move-symbol-into-user-package
	    (getf product-info :bridge-revision-switch)))
	(product-text-name
	 (string-upcase (getf product-info :product-text-name)))
	(product-version
	  (string-upcase (getf product-info :product-version))))
    (values-list
      (nconc
	(multiple-value-list
	    (cl-user::compute-bridge-authorizations
	      (string-upcase machine-id)
	      product-text-name
	      product-version
	      (if start-date?
		  (cl-user::bridge-universal-date
		    (first start-date?)
		    (month-number (second start-date?))
		    (third start-date?))
		  0)
	      (if end-date?
		  (cl-user::bridge-universal-date
		    (first end-date?)
		    (month-number (second end-date?))
		    (third end-date?))
		  0)
	      bridge-revision-switch)
	  )
	(list
	  (intern (string-upcase (getf product-info :product-text-name)))
	  (intern (string-upcase (getf product-info :product-version))))))))

(defun month-number (month)
  (position month '(:foo 
                    jan feb mar apr
                    may jun jul aug
                    sep oct nov dec)
	    :test 'string-equal))













;;;; Challenge Response


;;; We use a challenge response protocol to assure that clients are
;;; trusted.  Before we give them access to the server we challenge
;;; them with a question that they can awnser only if they know their
;;; password.  Their response is computed by combining the challenge
;;; with their password.  The actual response does not contain enough
;;; information to allow it's inverting back to the password.

;;; We store user passwords in the server.  These are encrypted
;;; since file that enumerates users is not very secure (this is
;;; like /etc/passwd). 


;;; `Compute-challenge-response-1' is used to convert a fragment of text
;;; and a number into a scrabled string containing most, but not all the
;;; information in the original.  This is used to encrypt passwords for
;;; storage in the user file (our mimic of a /etc/passwd), and to compute
;;; the response generated by a client to our challenge.

(defun compute-challenge-response-1 (text number)
  (let ((s1
	  (format nil "~A~A~A" number (string-upcase (string text)) number)))
    (loop with seed = 74
	  with sixty-four-nice-chars
	  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789#@"
	  for i from 0 below (length s1)
	  as c = (char-code (char s1 i))
	  do
      (setf seed (logxor seed c))
      (setf (char s1 i) (char sixty-four-nice-chars (logand 63 seed))))
    s1))

;;; `encrypt-licensing-password' we store user password's in a damaged scramble of
;;; their original form.  This is used only when editing the user list.

(defun encrypt-licensing-password (password)
  (compute-challenge-response-1 password 0))


;;; `Compute-challenge-response' is used by clients to compute the response
;;; to the challenge we give them.  They take the clear text password,
;;; encrypt it (as we do) and then compute a response.

(defun compute-challenge-response (password number)
  (compute-challenge-response-1
    (compute-challenge-response-1 password 0)
    number))

;;; `Correct-response-p' is used to check a response recieved from the user.

(defun correct-response-p (encrypted-password number possible-response)
  (string=
    possible-response
    (compute-challenge-response-1 encrypted-password number)))












;;;; User Name Database.


;;; One of the next few modules loaded contains a setf that
;;; binds a value for *user-records*.  This consists of a list
;;; of plists.  Each plist describes one user and has these
;;; entries:
;;;     :name <symbol>
;;;     :encrypted-password <string>
;;;     :permissions <list-of-permissions>
;;; Each entry enables a user of that name to log in using
;;; that password, and afterward he will have those permissions.

(def-plist user-info
  :name (required symbol)
  :encrypted-password (required string)
  :permissions (required licensing-permission-list))

(deftype licensing-permission-list () '(and
					list
					(satisfies licensing-permission-list-p)))

(defparameter all-user-permissions
    '(root                ;; Provides all commands
      basic               ;; Quit, help.
      login               ;; Permission to login to the server.
      any-license         ;; 
      temporary-license   ;; temporary-license
      list-products       ;; list-products
      ))

(defun licensing-permission-list-p (list)
  (every #'(lambda (x)
	     (member x
		     all-user-permissions)) list))

(defun find-troubled-user (user-list)
  (loop for user in user-list
	unless (check-plist-instance 'user-info user)
	  do (return user)))

(defvar *user-records* nil)

(defun find-licensing-user (name)
  (find name *user-records* :key #'(lambda (x) (getf x :name))))

(defun licensing-user-encrypted-password (name)
  (getf (find-licensing-user name) :encrypted-password))

(defun licensing-user-permissions (name)
  (getf (find-licensing-user name) :permissions))



;;; `Reload-user-records' is called by one of the server commands to
;;; trigger it's relearning what it knows about users.

(defun reload-user-records ()
  (let ((file-pathname (probe-file the-licensing-users-file)))
    (unless file-pathname
      (warn "Unable to find file of users."))
    (when file-pathname
      (with-open-file (f file-pathname)
	(let ((*package* *package*))
	  (let ((in-package (read f)))
	    (unless (and (consp in-package)
			 (stringp (second in-package))
			 (find-package (second in-package)))
	      (error "Malformed in-package clause."))
	    (setf *package* (find-package (second in-package))))
	  (let* ((pending-user-records (second (third (read f))))
		 (troubled-user? (find-troubled-user pending-user-records)))
	    (when troubled-user?
	      (error "Malformed User Info: ~S" troubled-user?))
	    (setf *user-records* pending-user-records)))))))




;;;; Dictionary of Server Commands


;;; Each command is defined using `define-licensing-command' which creates a
;;; function, and records function name, documentation, enabling permissions and
;;; lambda list for the command on properties of the command name.  A set of all
;;; command names are pooled the list of `all-licensing-commands' for use by the
;;; help command.

(defvar all-licensing-commands nil)

(defmacro licensing-command-function (command-name)
  `(get ,command-name 'licensing-command-function))

(defmacro licensing-command-documentation (command-name)
  `(get ,command-name 'licensing-command-documentation))

(defmacro licensing-command-lambda-list (command-name)
  `(get ,command-name 'licensing-command-lambda-list))

(defmacro licensing-command-enabling-permissions (command-name)
  `(get ,command-name 'licensing-command-enabling-permissions))

(defmacro def-licensing-command ((name &rest required-permissions)
				 args &body body-and-doc)
  (let ((command-function (intern (format nil "~S-COMMAND-FUNCTION" name)))
	(doc
	  (loop for i in body-and-doc while (stringp i) collect i))
	(body
	  (remove-if #'stringp body-and-doc)))
  `(progn
     (pushnew ',name all-licensing-commands)
     (setf (licensing-command-enabling-permissions ',name)
	   ',(append
	       '(root)
	       (remove 'root required-permissions)))
     (setf (licensing-command-lambda-list ',name) ',args)
     (setf (licensing-command-function ',name) ',command-function)
     (setf (licensing-command-documentation ',name) ',doc)
     (defun ,command-function ,args ,@body))))

(defun command-allowed-p (command)
  (declare (special licensing-client-permissions))
  (loop for permission
	    in (licensing-command-enabling-permissions command)
	thereis (member permission licensing-client-permissions)))









;;;; Listener of the Licensing Server


;;; `:license-server' is what this file implements.  It will launch
;;; a client that capable of emiting licenses for Gensym products.
;;; Of course use user must log in etc. etc.

(define-server-kind :license-server ()
  :type 1
  :name "LS"
  :listener-port 7535
  :client-function licensing-server-client)

;; The :Name appears in client output upon connection so a mnemonic
;; name is less likely to tempt an intruder.  The name takes space
;; in the log file output so a mnemonic name is more concise.


;;; `Start-licensing-server' is called when the process launches
;;; to get things going.

(defun start-licensing-server ()
  (read-in-product-descriptions)
  (reload-user-records)
  (start-server :license-server))







;;;; Server Process Created by the Listener and Server Command 



;;; We establish assorted bindings in the client to quide how things
;;; are going.
;;; `shutdown-licensing-client' is set to non nil when every any
;;;    command wants to shut the connection.  This is sometime set
;;;    long before the actual shutdown takes place.
;;; `*client-output*' provides a stream for commands to write
;;;    their output back to the client.  Meanwhile *standard-output*
;;;    is the background stream of the server.
;;; `licensing-client-name' is just that.  It defaults to GUEST in
;;;    the fresh client server process.
;;; `licensing-client-permissions' is a list of symbols.  Each command
;;;    has a similar list, and can be seen and executed only if the
;;;    entire the user has all the permissions enumerated for the command.
;;; `challenged-user' bound by login, and cleared by response.  This
;;;    implements the half state between those two commands.
;;; `challenge-number' this was the "question" we gave to the user.
;;; `pending-query-form?' The command do-it binds this, and then if
;;;    bound a successful response will execute the command.

(defvar shutdown-licensing-client) ;; a flag that when set to nonnil triggers an exit.
(defvar *client-output*)           ;; the stream we reply to him on.
(defvar licensing-client-name 'internal)
(defvar licensing-client-permissions)
(defvar challenged-user)
(defvar challenge-number)
(defvar pending-query-form?)


;;; `licensing-server-client-readtable' is the readtable used
;;; inside the server seal the read time eval security hole.

(defvar licensing-server-client-readtable
  (let ((readtable (ab-lisp::copy-readtable nil)))
    (ab-lisp::set-syntax-from-char #\# #\A readtable)
    readtable))



;;; `Licensing-server-client' is the client server, and implements
;;; the read eval print loop of the client process.  See Lucid-Server
;;; (now Lisp-Server) for the table this mechinism is installed into resides in.

(defparameter *licensing-server-timeout* 13)

(defun make-timeout-licensing-server ()
  #+lucid
  (lcl:make-process
    :name (concatenate 'string "Timer for "
			      (lcl:process-name lcl:*current-process*))
    :function 'timeout-licensing-server-client
    :args (list lcl:*current-process* *licensing-server-timeout*))
  #+lispworks
  (mp:process-run-function (format nil "Timer for ~A"
                                   (mp:process-name (mp:get-current-process)))
                           nil
                           'timeout-licensing-server-client
                           (mp:get-current-process) *licensing-server-timeout*)
  #-(or lucid lispworks)
  (portable-threads:spawn-thread
    (format nil "Timer for ~A"
            (portable-threads:thread-name (portable-threads:current-thread)))
    'timeout-licensing-server-client
    (portable-threads:current-thread)
    *licensing-server-timeout*))

(defun-allowing-unwind licensing-server-client (socket)
  (make-timeout-licensing-server)
  (let ((reason-for-exit? "for unknown reason."))
    (setf
      reason-for-exit? 
      (block :server
	(#+lucid lcl:handler-case #-lucid ab-lisp::handler-case
	  (with-open-stream (stream #+lucid
                                    (lcl:make-lisp-stream :input-handle socket
                                                          :output-handle socket
                                                          :auto-force t)
                                    #+lispworks
                                    (cl:make-instance 'comm:socket-stream
                                                      :socket socket
                                                      :direction :io
                                                      :element-type 'cl:base-char)
                                    #-(or lucid lispworks)
                                    (error "Unknown platform"))
	    (loop
	      with *readtable* = licensing-server-client-readtable
	      with shutdown-licensing-client = nil
	      with *package* = (find-package "AB")
	      with licensing-client-name = 'guest
	      with licensing-client-permissions = (licensing-user-permissions
						    licensing-client-name)
	      with challenged-user = nil
	      with challenge-number = nil
	      with pending-query-form? = nil
	      initially
		(trace-licensing-server 'connection-open
                                        #+lucid (hostname)
                                        #-lucid (cl:machine-instance))
	      ;; This line is used by the client to notice we are connected.
		(format stream "Howdy... ~a on ~a Connected ~S~%"
			(ab-lisp::lisp-implementation-type)
                        (ab-lisp::software-type)
                        #+lucid
			(lcl:process-name lcl:*current-process*)
                        #+lispworks
                        (mp:process-name (mp:get-current-process))
                        #-(or lucid lispworks)
			(portable-threads:thread-name
			  (portable-threads:current-thread)))
	      ;; This line is then passed on into the output stream.
		(format stream "Gd mawning to yah~%")
                #-lucid (force-output stream)

	      until shutdown-licensing-client

	      finally
		(format stream "Have a nice day.~%")
                #-lucid (force-output stream)
		(return-from :server "finished tranaction.")

	      do

	      (format stream "~%<<<--GensymLicensing-->>>~%")
	      (force-output stream)
	      (let ((form (read stream nil 'close)))
		(when (eq form 'close) (return-from :server))
		(trace-licensing-server 'request form)
		(let ((values (#+lucid lcl:handler-case
                               #-lucid ab-lisp::handler-case
				(multiple-value-list
				    (eval-licensing-request form stream))
				(error (e) (list 'error
						 #-ansi-cl
						 (lisp:princ-to-string e)
						 #+ansi-cl
						 (cl:princ-to-string e))))))
		  (when values
		    (trace-licensing-server 'reply values))
		  (loop
		    for value in values do (format stream "~s~%" value))
		  (force-output stream)))))
	  (error (c)
	    (return-from :server (format nil "ERROR: ~A" c))))))
    (if reason-for-exit?
	(trace-licensing-server :exiting (format nil "exiting server ~A"
						 reason-for-exit?))
	(trace-licensing-server :exiting "exiting server, ok"))))

#+lucid
(defun timeout-licensing-server-client (guarded-process timeout)
  (lcl:process-wait-with-timeout "Hunting" timeout #'(lambda ()))
  (unless (or (member 'root (getf (lcl:process-plist guarded-process)
				  'licensing-client-permissions))
	      (eq :killed (lcl:process-state guarded-process)))
    (trace-licensing-server 'timeout (lcl:process-name guarded-process))
    (lcl:kill-process guarded-process)))

#+lispworks
(defun timeout-licensing-server-client (guarded-process timeout)
  (mp:process-wait-with-timeout "Hunting" timeout #'(lambda ()))
  (unless (or (member 'root (getf (mp:process-plist guarded-process)
				  'licensing-client-permissions))
	      (string= (mp:process-whostate guarded-process) "Dead"))
    (trace-licensing-server 'timeout (mp:process-name guarded-process))
    (mp:process-kill guarded-process)))

#-(or lucid lispworks)
(defun timeout-licensing-server-client (guarded-process timeout)
  (sleep 5)
  (error "not fully implemented."))

;;; `Eval-licensing-request' implements the very stupid evaluator for clients of
;;; the licensing server.

(defun eval-licensing-request (request stream)
  (unless (consp request)
    (error "Unknown request?"))
  (let* ((command-name (car request))
	 (command-function? (licensing-command-function command-name)))
    (unless (and command-function?
		 (command-allowed-p command-name))
      (error "Unknown request?"))
    (unless (= (length (cdr request))
	       (length (licensing-command-lambda-list command-name)))
      (error "Incorrect number of arguments to request, expected:~{ ~A~}"
	     (licensing-command-lambda-list command-name)))
    (let ((*client-output* stream))
      (apply command-function? (rest request)))))


(defparameter trace-licensing-server t)

(defun trace-licensing-server (label value)
  (when trace-licensing-server
    (multiple-value-bind (SECOND MINUTE HOUR DATE MONTH YEAR)
	(decode-universal-time (get-universal-time))
      (format *terminal-io*
	      "~&~4D-~2,'0D-~2,'0D ~2,'0D:~2,'0D:~2,'0D  ~A ~(~A: ~S~)~%"
	      year month date hour minute second
	      #+lucid
	      (lcl:process-name lcl:*current-process*)
	      #+lispworks
	      (mp:process-name mp:*current-process*)
	       #-(or lucid lispworks)
	      (portable-threads:thread-name
		(portable-threads:current-thread))
	      label value))))







;;;; Individual Server Commands



(def-licensing-command (noop basic) ()
  "A No Operation"
  (values))



(def-licensing-command (bye basic) ()
  "Close the connection"
  (setf shutdown-licensing-client t)
  (values))



(def-licensing-command (quit basic) ()
  "Close the connection"
  (setf shutdown-licensing-client t)
  (values))



(def-licensing-command (help basic) ()
  "Enumerate the available commands."
  (loop for command in all-licensing-commands
	when (command-allowed-p command)
	do
    (format *client-output* "~(~S -- ~)" command)
    (loop for arg in (licensing-command-lambda-list command)
	  do (format *client-output* "~( ~A~)" arg))
    (when (licensing-command-lambda-list command)
      (format *client-output* "~%"))
    (loop for s in (licensing-command-documentation command)
	  do (format *client-output* "~15T~A~%" s)))
  (values))







(def-licensing-command (license any-license)
				(product-id
				 machine-id
				 start-date-list? 
				 end-date-list?
				 product-process-limit?
				 number-of-tw-connections?
				 number-of-t2-connections?
				 product-optional-modules)
  "License computes a license for a product and takes seven args"
  "    machine-id -- a string, case and spaces are unimportant"
  "    start-date-list? -- see below"
  "    end-date-list?   -- see below"
  "    product-process-limit?    -- is a positive integer or nil"
  "    number-of-tw-connections? -- is a positive integer or nil"
  "    number-of-t2-connections? -- is a positive integer or nil"
  "    product-optional-modules  -- is a list of these:"
  "        gsi gspan icp gfi kfep chinese japanese korean nupec g1 jl jp al"
  "        offline online runtime restricted-use embedded"
  " The date list arguments may be nil.  They are only useful"
  " for Telewindows or G2.  They are three integers:"
  "   (<day> <month> <year>) or nil."
  " The number-of-tw-connections? is used only for G2, and should default"
  " to be defaulted to zero."
  " The number-of-t2-connections? is also only for G2 and when issuing"
  " temporary licenses for versions of G2 version 5.1 and later should"
  " default to 0. It is meaningless for versions earlier than 5.1"
  " and must be given the value nil to indicate that the temporary"
  " license is for such a system"
  " The process limit should default to 2 for G2.  Nil implies"
  " unlimited processes."
  (license-1
    product-id
    machine-id
    start-date-list? 
    end-date-list?
    product-process-limit?
    number-of-tw-connections?
    number-of-t2-connections?
    product-optional-modules))



(def-licensing-command (temporary-license temporary-license)
    (product-id
      machine-id
      start-date?
      end-date
      product-process-limit
      number-of-tw-connections?
      number-of-t2-connections?
      product-optional-modules)
  (unless end-date
    (error "A temporary license must specify an end date"))
  (license-1
    product-id
    machine-id
    start-date?
    end-date
    product-process-limit
    number-of-tw-connections?
    number-of-t2-connections?
    product-optional-modules))

(defun license-1 (product-id
		   machine-id
		   start-date
		   end-date
		   product-process-limit
		   number-of-tw-connections?
		   number-of-t2-connections?
		   product-optional-modules)
  
  (let* ((product-info (find product-id *product-records*
			     :key #'(lambda (record)
				      (getf record :product-symbolic-name))))
	 (cl-user::reference-date-for-interval-encoding
	   (if number-of-t2-connections? ; If non-nil use 1998 or 2005 values.
	       (let ((g2-version-switch
		       (getf product-info :G2-VERSION-SWITCH)))
		 (cond ((and (numberp g2-version-switch)
			     (>= g2-version-switch 12))		   ; G2 2015+
			cl-user::jan-1-2015)
		       ((and (numberp g2-version-switch)
			     (or (= g2-version-switch 83)	   ; G2 8.3
				 (and (>= g2-version-switch 9)	   ; never used
				      (<= g2-version-switch 11)))) ; G2 2011
			cl-user::jan-1-2006)
		       (t ; (old versions after 5.0r4)
			;; GENSYMCID-564: temporary codes generated for G2 82.r3 don't work.
			;; Pre 8.2r4 reference-date added back according to G2 8.2r4 source code.
			;; -- Chun Tian (binghe) / Glority, 2011/11/21
			cl-user::jan-1-1998)))
	       cl-user::jan-1-1990))) ; otherwise we're pre 5.0r4
    
    (flet ((check (arg error check?)
	     (unless check?
	       (error error arg))))
      
      (check product-id "Unknown Product ~S" product-info)
      (check machine-id "Machine Id must be String, not ~S" (stringp machine-id))
      (unless (memq 'root licensing-client-permissions)
	(check machine-id "Cannot issue licenses for that machine-id"
	       (cl-user::legal-machine-id-p machine-id)))
      
      (when start-date
	(unless end-date
	  (error "A temporary license that specifies a start date must also give an end date"))	
	(check-dates-for-validity
	  start-date end-date
	  ;; bridges have a different date representation: (MHD 3/23/01)
	  (eq (getf product-info :authorization-method) 'g2)))
      
      (check number-of-tw-connections?
	     "Number-of-tw-connections? must be nil or 0..8000"
	     (or (null number-of-tw-connections?)
		 (<= 0 number-of-tw-connections? 8000)))
      (when number-of-tw-connections?
	(check number-of-tw-connections?
	       "Number-of-tw-connections? valid only for G2"
	       (eq (getf product-info :AUTHORIZATION-METHOD) 'g2))
	(check number-of-tw-connections?
	       "Number-of-tw-connections found only in g2 v4 and latter."
	       (let ((g2-version-switch
		       (getf product-info :G2-VERSION-SWITCH)))
		 (and (numberp g2-version-switch)
		      (<= 4 g2-version-switch)))))

      (when number-of-t2-connections?
	(unless (eq (getf product-info :AUTHORIZATION-METHOD) 'g2)
	  (error "Number-of-t2-connections? valid only for G2"))
	(unless (let ((g2-version-switch
			(getf product-info :G2-VERSION-SWITCH)))
		  (and (numberp g2-version-switch)
		       (>= g2-version-switch 5)))
	  ;; That's not sufficient really because it's not valid for any version
	  ;; of G2 earlier than 5.0r4, but that's handled by the convention of
	  ;; making this argument nil in such cases and only giving it a numeric
	  ;; value for 5.0r4 and later. The responsibility is on the caller
	  ;; since we don't divide up product authorization any more finely
	  ;; than major version. Sigh.
	  (error "Number-of-t2-connections? is not valid for any version of G2 earlier than 5.0r4"))
	(unless (typep number-of-t2-connections? 'fixnum)
	  (error "The number-of-t2-connections argument must be an integer."))
	(unless (>=f (-f #.(expt 2 16) 1) number-of-t2-connections? 0)
	  (error "Too many Telewindows2 connections requested")))

      (check product-process-limit
	     "Process limit must be NIL or inside range 0..200, not ~S"
	     (or (null product-process-limit)
		 (< 0 product-process-limit 200)))
      
      ;; Rules about optional modules in any and all products.
      (check product-optional-modules "Optional modules ~S is malformed."
	     (valid-optional-modules-p product-optional-modules))
      (when product-optional-modules
	(case (getf product-info :AUTHORIZATION-METHOD)
	  ;; Rules about optional modules in G2.
	  (g2
	   (let ((g2-version-switch
		   (getf product-info :G2-VERSION-SWITCH)))
	     (declare (ignore g2-version-switch))
	     #+obsolete ;; Note A
	     (when (and (numberp g2-version-switch)
			(<= 4 g2-version-switch))
	       (check product-optional-modules
		      "Korean is obsolete as of g2 version 4.0."
		      (not (member 'korean product-optional-modules
			      :test #'string-equal)))
	       (check product-optional-modules
		      "Japanese is obsolete as of g2 version 4.0."
		      (not (member 'japanese product-optional-modules
				   :test #'string-equal)))))))))
    (setf shutdown-licensing-client t)
    (compute-authorization-codes
      product-info
      machine-id
      (convert-date-list? start-date)
      (convert-date-list? end-date)
      product-process-limit
      number-of-tw-connections?
      number-of-t2-connections?
      product-optional-modules)))

;; Note A: There was a period around Rev53 of the 4.0 beta when we
;; decided to give japanese and korean away.  Then we changed our
;; minds.



(def-licensing-command (list-products list-products) (kind match)
  "List the known products."
  "Kind should be one of these four values:"
  "    g2    telewindows"
  "    kb    bridge"
  "Match should be a string that limits the search, for example:"
  "  (list-products bridge \"ABP\")"
  " will show just bridge products matching that string."

  (let ((real-kind (case kind
		     (g2 'g2)
		     (telewindows 'telewindows)
		     (kb 'g2-package)
		     (bridge 'bridge))))
    (unless real-kind
      (error "Unknown kind of product not one of: g2, telewindows, kb, or bridge.~%"))

    (loop for product-info in *product-records*
	  when (and (eq real-kind
			(getf product-info :authorization-method))
		    (search match
			    (getf product-info :description)
			    :test #'char-equal))
	    do
	      (format *client-output* "~15S ~S~%"
		      (getf product-info :product-symbolic-name)
		      (getf product-info :description)))
    (values)))



(def-licensing-command (login login) (name)
  "Attempt login for user name."
  "  for example (login little-joe)."
  "  will challenge the user first."
  (setf challenged-user name)
  (setf challenge-number (+ 30 (random 99959)))
  (unless (find-licensing-user challenged-user)
    (trace-licensing-server 'login "Unknown user"))
  (format *client-output* "Challenge: ~S~%" challenge-number)
  (values))

(def-licensing-command (response login) (response)
  "Respond to challenge."
  (cond
    ((and (find-licensing-user challenged-user)
	  (fixnump challenge-number)
	  (correct-response-p
	    (licensing-user-encrypted-password challenged-user)
	    challenge-number
	    response))
     (setf licensing-client-name challenged-user)
     (setf licensing-client-permissions
	   (licensing-user-permissions licensing-client-name))
     (setf (getf #+lucid
                 (lcl:process-plist lcl:*current-process*)
                 #+lispworks
                 (mp:process-plist mp:*current-process*)
                 #-(or lucid lispworks)
                 (error "Unknown platform")
		 'licensing-client-permissions)
	   licensing-client-permissions)
     (setf challenged-user nil)
     (setf challenge-number nil)
     (cond
       (pending-query-form?
	(setf shutdown-licensing-client t)
	;; bracket the output in this case.
	(format *client-output* "To Clorox a horse.~%")
	(eval-licensing-request
	  (shiftf pending-query-form? nil)
	  *client-output*)
	;; This return value is critical.
	)
       ((member 'root licensing-client-permissions)
	(format *client-output* "Welcome~%")
	(values))
       (t
	(format *client-output* "Sorry One Queries.~%")
	(values))))
    (t
     (trace-licensing-server 'response "Failed")
     (setf shutdown-licensing-client t)
     (values))))



(def-licensing-command (do-for-me login) (name command)
  "Do a single query for this user."
  "  will challenge the user first."
  (setf pending-query-form? command)
  (funcall (licensing-command-function 'login) name)
  (values))



(def-licensing-command (reload) (what)
  "Reload either the products, or the users"
  (case what
    (users    (reload-user-records))
    (products (read-in-product-descriptions))
    (t        (error "Either users or products?")))
  (values :ok))

(def-licensing-command (shutdown-server) ()
  "Commit suicide, the server will quit running."
  #+lucid (lcl:quit)
  #+lispworks (lw:quit)
  #-(or lucid lispworks) (error "Unknown platform")
  (values :ok))

(def-licensing-command (show-users) ()
   (loop for record in *user-records*
	 do (print record *client-output*))
   (values :ok))

(def-licensing-command (introduce-bridge temporary-license any-license)
    (bridge-name
      bridge-version
      authorization-style)
  "Adds a bridge to the set of products."
  "This new product will be known to the licensing server"
  "only for a short period."
  "  bridge-name -- the string mnemonic name of the bridge."
  "  bridge-version -- the string version id of the bridge."
  "  authorization-style -- either revision-1 or revision-2."

  (flet ((check (arg error check?)
	   (unless check?
	     (error error arg))))

    (check bridge-name "bridge-name must be a string" bridge-name)
    (check bridge-name "Malformed bridge name."
	   (validate-bridge-product bridge-name))
    (check bridge-name "bridge-name must be of a reasonable length"
	   (< 2 (length bridge-name)))

    (check authorization-style
	   "authorization-style must be either revision-1 or revision-2."
	   (member authorization-style '(revision-1 revision-2)))
    (check bridge-version "bridge-version must be a string"
	   (stringp bridge-version))
    (check bridge-version "malformed bridge version"
	   (validate-bridge-version bridge-version
				    authorization-style))

    (let* ((bridge-symbolic-name
	     (make-product-symbolic-name bridge-name bridge-version))
	   (new-bridge-description
	     (list
	       :product-text-name (string-upcase bridge-name)
	       :product-version (string-upcase bridge-version)
	       :product-symbolic-name bridge-symbolic-name
	       :authorization-method 'bridge
	       :description
	       "A temporary introduced bridge with no description."
	       :bridge-revision-switch authorization-style)))
      ;; Let check-plist approve it.
      (multiple-value-bind (ok? reason instance slot-name)
	  (check-plist-instance 'product-info new-bridge-description)
	  (declare (ignore instance))
	(unless ok?
	  (error "Malformed bridge's description (~S ~S)."
		 reason slot-name)))

      ;; OK let's boogy.
      (setf *product-records*
	    (list*
	      new-bridge-description
	      (loop for product-record in *product-records*
		    unless (eql bridge-symbolic-name
				(getf product-record :PRODUCT-SYMBOLIC-NAME))
		      collect product-record)))
      bridge-symbolic-name)))


(defconstant clear-code
  "():\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")

(defconstant black-code
  "MNOPQRSTUVWXYZABCDEFGHIJKL0123456789abcdefghijklmnopqrstuvwxyz():\"")

(defun move-string-into-black (clear-string)
  (do-substitution clear-code black-code clear-string))

(defun move-string-into-clear (black-string)
  (do-substitution black-code clear-code black-string))

(defun do-substitution (from to string)
  (loop with result = (make-string (length string)) finally (return result)
	for i from 0 below (length string)
	as from-char = (char string i)
	as encode-pos? = (position from-char from)
	as to-char = (if encode-pos?
			 (char to encode-pos?)
			 from-char)
	do (setf (char result i) to-char)))

;;;;  Testing Harness

(defparameter test-cases  ; <<<=========== add tw2 argument throughout, and regenerate(?) the targets
  '(;; Telewindow-v3
    ((telewindows-v3 "foobar" nil nil nil nil ())
    . (6248909 6282952 581501 277047 201352))
    ((telewindows-v3 "foobar" nil nil nil nil (japanese))
     . (5646075 3288143 5608116 540243 164720))
    ((telewindows-v3 "foobar" nil nil nil nil (korean))
    . (3912339 7542845 4140738 3908913 680366))
    ((telewindows-v3 "foobar" nil nil nil nil (japanese korean))
     . (602549 4978010 7837839 7694361 873050))

    ;; Telewindows-v4
    ((telewindows-v4 "foobar" nil nil nil nil (japanese))
     . error)
    ((telewindows-v4 "foobar" nil nil nil nil ())
     . (7189080 7223123 4852714 7757296 530667))
       
    ((telewindows-v4 "foobar" nil nil nil nil (runtime))
     . (7189080 7258963 4852714 7757296 473473))

    ((telewindows-v4 "foobar" nil nil 3 nil ())  ;; Process limit
     . (5310691 7169354 1525006 2165679 802164))
    ((telewindows-v4 "foobar" (1 1 90) (20 1 90) 3 nil ()) ;; Temp
     . (1885011 3743674 6012822 7342198 554448))

    ;; G2-V3
    ((g2-v3 "foobar" nil nil nil nil nil)
     . (63077 32946 33350 26680 429416 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) nil nil nil)   ;; + Temporary
     . (2236 39136 63079 47541 109257 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil nil)    ;; + Process limit
     . (38669 53920 30042 58488 637042 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 4 nil)    ;; + TW Conn
     . error)

    ;; Try G2-v3 with assorted optional modules
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (gsi))
     . (64314 11703 13982 17374 298576 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (runtime))
     . (13332 9180 18084 36529 695155 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (restricted-use))
     . (63136 62637 63579 56150 372236 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (embedded))
     . (54250 36738 2166 35322 56099 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (online))
     . (35862 45099 60651 8994 343896 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (runtime offline))
     . (6990 56905 18432 57684 10695 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (gspan))
     . (61381 12332 62757 9785 434026 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (gfi))
     . (31857 18664 13106 61778 684981 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (japanese))
     . (41805 49655 47680 7362 831214 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (korean))
     . (8535 47929 43342 27024 908468 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (nupec))
     . (19955 22522 48801 49201 251352 "KDF21027651"))
    ((g2-v3 "foobar" (1 1 90) (20 1 90) 10 nil (kfep))
     . (53994 12325 10838 54220 415342 "KDF21027651"))


    ;; Try G2-V4
    ((g2-v4 "foobar" nil nil nil nil nil)
     . (43073 15886 18774 502 885270 "KDF21027651"))
    ((g2-v4 "foobar" (1 1 90) (20 1 90) nil nil nil)   ;; + Temporary
     . (61446 6266 45221 12817 200487 "KDF21027651"))
    ((g2-v4 "foobar" (1 1 90) (20 1 90) 10 nil nil)    ;; + Process limit
     . (64362 60504 64169 47301 626407 "KDF21027651"))
    ((g2-v4 "foobar" (1 1 90) (20 1 90) 10 4 nil)      ;; + TW Conn
     . (18837 7700 28869 62761 544533 "KDF21027651"))

    ;; Try G2-v4 with a few optional modules
    ((g2-v4 "foobar" (1 1 90) (20 1 90) 10 nil (gsi))
     . (48004 63132 34030 28818 126755 "KDF21027651"))
    ((g2-v4 "foobar" (1 1 90) (20 1 90) 10 nil (runtime))
     . (26680 47089 40094 5679 317875 "KDF21027651"))
    ((g2-v4 "foobar" (1 1 90) (20 1 90) 10 nil (restricted-use))
     . (42703 20275 63286 47553 494147 "KDF21027651"))
    ((g2-v4 "foobar" (1 1 90) (20 1 90) 10 nil (japanese))
     . error)
    ((g2-v4 "foobar" (1 1 90) (20 1 90) 10 nil (korean))
     . error)


    ;;; Bridge
    ((GSI-RTAP-V1 "FooBar" nil nil nil nil nil)
     . (5564952 5560015 859302 1190219 423089699 GSI-RTAP V1))

    ;; KB 
    ((BIOTECH-DESIGN-SIMULATOR-ANY "FooBar" nil nil nil nil nil)
     . (211111 202734 469502 LSC-BDS))
    
    ))

#+lucid
(defun do-self-test ()
  (let ((licensing-client-name 'testing)
	(*client-output* *standard-output*))
    (loop for ((product 
		 machine-id
		 start-date-list?
		 end-date-list?
		 product-process-limit?
		 number-of-tw-connections?
		 number-of-t2-connections?
		 product-optional-modules) . expected-result) in test-cases
	  as test-number from 1
	  as error-string? = nil
	  as result = (lcl:handler-case
			    (multiple-value-list
				(license-1
				  product
				  machine-id
				  (copy-list start-date-list?)
				  (copy-list end-date-list?)
				  product-process-limit?
				  number-of-tw-connections?
				  number-of-t2-connections?
				  product-optional-modules))
			    (error (c)
				   (setf error-string? (format nil "~A" c))
				   'error))
	  do
      (format t "~&Test ~3D ~20S: " test-number product)
      (if (equal result expected-result)
	  (format t "ok")
	  (progn
	    (format t "FAILED: ~S ~S ~S ~S ~S ~S"
		    machine-id
		    start-date-list?
		    end-date-list?
		    product-process-limit?
		    number-of-tw-connections?
		    product-optional-modules)
	    (format t "~&                 got: ~S" result)
	    (when error-string? (format t "~&           eg: ~A" error-string?))
	    )))))





;;;; gsi.ok file

;;; This section includes a rough draft for a facility to generate
;;; the site's gsi.ok file.  This file is then put in /home/ab/gsi.ok.
;;; That's useful!  But to get this section to work you need to ahve
;;; loaded G2 up thru utilities1, and then compiled these routines.
;;; The second of the three routines require are duplicated in the
;;; site-ok-files sections of the encrypted sources.

;;; Instructions -

;;; 0. See util/generate-site-gsi-ok-file


#+generate-gsi-ok
(eval-when (:compile-toplevel)
  (print "Compiling generate-gsi-ok facilities"))

#+generate-gsi-ok
(eval-when (:load-toplevel)
  (print "Loading generate-gsi-ok facilities"))

;;; `Generate-gsi-ok' takes a copy of of the hostinfo yellowpage
;;; from a file /tmp/hostinfo and creates a /tmp/gsi.ok.  This
;;; file is huge, if the optional argument is given as T.  
;;; Huge means it has all the files in the hostinfo file in it.
;;; not huge uses some guesses to include the machines that are
;;; important -- it's all so bogus.

#+generate-gsi-ok
(defun generate-gsi-ok (&optional (huge? t))
  #-obsolete
  (declare (ignore huge?))
  (flet (#+obsolete
	 (include-this-machine-in-gsi-ok? (info)
	   (when huge? (return-from include-this-machine-in-gsi-ok? t))
	   (loop with this-machine = (car info)
		 for machine in '("montreal"
				  "moscow"
				  "baltimore"
				  "nippon"
				  "ox"
				  "rwanda"
				  "somalia"
				  "th"
				  "uganda"
				  "holden" 
				  "be"  
				  "andorra"
				  "bhutan"
				  "bombay"
				  "dulles"
				  "eris"
				  "finland"
				  "gambia"
				  "ganesha"
				  "he" "hy"
				  "homer"
				  "iraq"
				  "ireland"
				  "israel"
				  "jordan"
				  "li"
				  "lr"
				  "lesotho"
				  "malawi"
				  "mendota"
				  "niue"
				  "pele"
				  "plasma"
				  "thailand"
				  "thor"
				  "tm"
				  "vivace"
				  "wa"
				  "wy"
				  "wyoming"
				  "zaire"
				  "zeus")
		 when (string-equal machine this-machine)
		   do (return-from include-this-machine-in-gsi-ok? t))
	   (loop for i in info
		 do
	     (loop for k in '("vms" "vax" "build" "syseng" "engineering"
			      "sdev" "gensym" "s5")
		   when (search k i :test #'char-equal)
		     do (return-from include-this-machine-in-gsi-ok? t)))))

    (with-open-file (s "/tmp/gsi.ok" :direction :output)
      (loop
	for info
	    in (read-host-info-file-into-list "/tmp/hostinfo") ;; see below
	as (machine-name machine-id) = info
	when (and machine-id
		  machine-name
		  ; (include-this-machine-in-gsi-ok? info)
		  (not (string=w '#.(stringw "") machine-id))
		  (not (string=w '#.(stringw "") machine-name)))
	  do
	    (print machine-name)
	    (flet ((f (product-text-name
			product-version
			bridge-revision-switch)
		     (setf machine-id (nstring-upcase machine-id))
		     (setf product-text-name (string-upcase product-text-name))
		     (setf product-version (string-upcase product-version))
		     (multiple-value-bind (c1 c2 c3 c4 c5)
			 (cl-user::compute-bridge-authorizations
			   machine-id
			   product-text-name
			   product-version
			   0
			   0
			   (find-symbol (symbol-name bridge-revision-switch)
					(find-package "CL-USER"))
			   )
		       (format s "~A ~A   ~A ~A   ~A ~A ~A ~A ~A~&"
			       machine-name machine-id
			       product-text-name
			       product-version
			       c1 c2 c3 c4 c5))))
	      (f "TESTBRIDGE" "V0" 'revision-2)
	      (loop for product in *product-records*
		    when (eq 'bridge (getf product :AUTHORIZATION-METHOD))
		      do (f (getf product :PRODUCT-TEXT-NAME)
			    (getf product :PRODUCT-VERSION)
			    (getf product :BRIDGE-REVISION-SWITCH))))))
    "/tmp/gsi.ok"))



#+generate-gsi-ok
(defun parse-hostinfo-line-into-fields (line-string)
  (let ((line-string-1 (string-trim '(#\space #\tab) line-string)))
    (loop with result-so-far = nil
	  with i = 0
	  do (loop with non-space-seen? = nil
		   for j from i below (length line-string-1)
		   as char = (char line-string-1 j)
		   until (or (char= char #\#)
			     (char= char #\:))
		   when (and (not non-space-seen?)
			     (not (member char '(#\space #\tab))))
		     do (setq non-space-seen? t)
		   finally
		     (setq result-so-far
			   (nconc result-so-far
				  (if (or non-space-seen? (char= char #\:))
				      (list (subseq line-string-1 i j)))))
		     (setq i j))
	  until (or (>= i (length line-string-1))
		    (char= (char line-string-1 i) #\#))
	  do (incff i)
	  finally
	    (return result-so-far))))

#+generate-gsi-ok
(defun read-host-info-file-into-list (pathname)
  (with-open-file (input-stream pathname)
    (sort-list
      (loop for line? = (read-line input-stream nil nil)
	    while line?
	    as fields = (parse-colon-delimited-ascii-text-line-into-list-of-ascii-strings line?)
	    ;; obsolete! (parse-hostinfo-line-into-fields line?)
	    when fields
	      collect fields)
      #'string-lessp
      #'car)))






;;;; To Do List

;; Why does this disk save so large?  (applisp is tempting.)








;; Files End

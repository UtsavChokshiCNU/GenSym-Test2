;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module BASICS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Hodgkinson, Jim Allard, and Ong, Peng Tsin






;;;; Basic Facilities for G2



;;;; Forward References

(declare-forward-references (:suppress-module-checks-for gsi)
  #+development
  (check-memory                      function))




;;; The macro `gensym-assert' is a new and improved version of the Common
;;; Lisp macro.  It tells you why the assert fails if it does.  This macro
;;; expands to nil if :development is not in *features*.

(defmacro gensym-assert (test-form)
  (when (eval-feature :development)
    `(if (not ,test-form)
	 (cerror "Continue, ignoring failure in assertion by gensym-assert."
		 ,(format nil
			  "Gensym-assert failed on: ~a." test-form)))))





;;; Test-assertion ... 

(defmacro test-assertion (test-form &optional (fatal? nil))
  `(if (not ,test-form)
       (let ((test-form ',test-form))
	 (if ,fatal?
	     (error "Failed assertion (FATAL): ~S" test-form)
	     (cerror "Continue" "Failed assertion: ~S" test-form)))))

;; Used quite a bit in FONTS.  By MHD.  Moved here from FONTS.  (MHD 11/27/90)









;;;; Arithmetic




;;; The macro `g2-round' rounds a numbers up or down depending on the argument
;;; value and differs from the Common Lisp round function in several ways.
;;; First, Common Lisp rounds its argument of n.5 or -n.5 to the nearest even
;;; integer.  This macro rounds n.5 and -n.5 to n+1 and -(n+1) respectively.
;;; Second, this macro does not accept an optional divisor argument.  Third, the
;;; macro only returns one value which is a type-declared fixnum.

(def-substitution-macro g2-round (number)
  (the fixnum (truncate (if (> number 0)
			    (+ number 0.5)
			    (- number 0.5)))))


;; G2-round-function is needed in the module Eval since it is funcalled.  It
;; should be removed when we swicth to using Stack-Eval!!  cpm, 6dec90.

#+obsolete
(defun g2-round-function (number)
  (declare (eliminate-for-gsi))
  (g2-round number))


;;; The macro `g2-round-e' is the floating point version of g2-round.

(def-substitution-macro g2-round-e (float)
  (the fixnum (truncate (if (>e float 0.0)
			    (+e float 0.5)
			    (-e float 0.5)))))


;;; The macro `g2-round-with-divisor' rounds a numbers up or down depending on
;;; the argument value in a way that differs from the Common Lisp round
;;; function.  See the macro g2-round.  This macro accepts a dividend and
;;; divisor argument and returns two values, the rounded value and the
;;; remainder.

(def-substitution-macro g2-round-with-divisor (dividend divisor)
  (let ((rounded-quotient (g2-round (/ dividend divisor))))
    (values rounded-quotient
	    (- dividend (* rounded-quotient divisor)))))




;;; The following functions implement fixnum versions of operations which are
;;; not optimized properly in Chestnut.  Direct references to these functions
;;; are made only from the fixnum operation macros defined in GLBASICS.  These
;;; definitions needed to follow the macro definitions in GLBASICS, and so were
;;; placed here.  -jra 11/9/91

#+(or chestnut chestnut-3) ;Chestnut3.1
(declare-side-effect-free-function chestnut-floorf-function)

#+(or chestnut chestnut-3) ;Chestnut3.1
(defun chestnut-floorf-function (fixnum divisor-fixnum)
  (declare (type fixnum fixnum divisor-fixnum))
  (let ((floor-result 0)
	(remainder-result 0))
    (declare (type fixnum floor-result remainder-result))
    (if (>f divisor-fixnum 0)
	(cond ((>=f fixnum 0)
	       (setq floor-result 
		     (floorf-positive fixnum divisor-fixnum))
	       (setq remainder-result
		     (modf-positive fixnum divisor-fixnum)))
	      (t
	       (let ((positive-fixnum (-f fixnum)))
		 (declare (type fixnum positive-fixnum))
		 (setq floor-result
		       (-f (ceilingf-positive positive-fixnum divisor-fixnum)))
		 (setq remainder-result
		       (modf-positive positive-fixnum divisor-fixnum))
		 (unless (=f remainder-result 0)
		   (setq remainder-result
			 (-f divisor-fixnum remainder-result))))))
	(let ((positive-divisor (-f divisor-fixnum)))
	  (declare (type fixnum positive-divisor))
	  (cond ((>=f fixnum 0)
		 (setq floor-result
		       (-f (ceilingf-positive fixnum positive-divisor)))
		 (setq remainder-result
		       (modf-positive fixnum positive-divisor))
		 (unless (=f remainder-result 0)
		   ;; Note that divisor-fixnum is negative, so the statement
		   ;; below works.
		   (setq remainder-result
			 (+f divisor-fixnum remainder-result))))
		(t
		 (let ((positive-fixnum (-f fixnum)))
		   (declare (type fixnum positive-fixnum))
		   (setq floor-result
			 (floorf-positive positive-fixnum positive-divisor))
		   (setq remainder-result
			 (-f (modf-positive
			       positive-fixnum positive-divisor))))))))
    (values floor-result remainder-result)))

#+(or chestnut chestnut-3) ;Chestnut3.1
(declare-side-effect-free-function chestnut-modf-function)

#+(or chestnut chestnut-3) ;Chestnut3.1
(defun-simple chestnut-modf-function (fixnum divisor-fixnum)
  (declare (type fixnum fixnum divisor-fixnum))
  (let ((remainder-result 0))
    (declare (type fixnum remainder-result))
    (if (>f divisor-fixnum 0)
	(cond ((>=f fixnum 0)
	       (setq remainder-result
		     (modf-positive fixnum divisor-fixnum)))
	      (t
	       (let ((positive-fixnum (-f fixnum)))
		 (declare (type fixnum positive-fixnum))
		 (setq remainder-result
		       (modf-positive positive-fixnum divisor-fixnum))
		 (unless (=f remainder-result 0)
		   (setq remainder-result
			 (-f divisor-fixnum remainder-result))))))
	(let ((positive-divisor (-f divisor-fixnum)))
	  (declare (type fixnum positive-divisor))
	  (cond ((>=f fixnum 0)
		 (setq remainder-result
		       (modf-positive fixnum positive-divisor))
		 (unless (=f remainder-result 0)
		   ;; Note that divisor-fixnum is negative, so the statement
		   ;; below works.
		   (setq remainder-result
			 (+f divisor-fixnum remainder-result))))
		(t
		 (let ((positive-fixnum (-f fixnum)))
		   (declare (type fixnum positive-fixnum))
		   (setq remainder-result
			 (-f (modf-positive
			       positive-fixnum positive-divisor))))))))
    remainder-result))

;(defun test-floor ()
;  (loop for divisor from -5 to 5 do
;    (unless (= divisor 0)
;      (loop for fixnum from -30 to 30 do
;	(multiple-value-bind (q1 r1)
;			     (floor fixnum divisor)
;	  (multiple-value-bind (q2 r2)
;			       (chestnut-floorf-function fixnum divisor)
;	    (unless (and (= q1 q2) (= r1 r2))
;	      (error "Bad result"))))))))

;(defun test-modf ()
;  (loop for divisor from -5 to 5 do
;    (unless (= divisor 0)
;      (loop for fixnum from -30 to 30 do
;	(unless (= (mod fixnum divisor)
;		   (chestnut-modf-function fixnum divisor))
;	  (error "Bad result for (chestnut-modf-function ~a ~a) => ~a."
;		 fixnum divisor
;		 (chestnut-modf-function fixnum divisor)))))))






;;;; Unwind Protect For Development




;;; `Unwind-protect' is used in G2, but rarely.  Frames that catch unwind are
;;; more expensive to compile.  The C implementation depending as it does on
;;; setjmp/longjmp is very expensive.  Particularly on processors with large
;;; register sets, or good pipelines.  Most C compilers decline to optimize
;;; routines (possibly not even using registers) routines that use
;;; setjmp/longjmp.

;;; Meanwhile the absence of unwind-protect can create problems when
;;; debugging code.  Unwinding the the stack when debugging will often
;;; need to clean up data structures to keep the process usable.  The
;;; macro `unwind-protect-for-development' provides a way to get and eat
;;; this cake.

;;; See also the facilities in that implement warnings on thoughtless usage of
;;; unwind-protect, e.g. `defun-allowing-unwind'.

;;; Non-local exits are used widely.  Those that cross lexical contours are no
;;; problem.  Those that cross dynamic countours, such as catch and throw need
;;; careful design to assure that they do not cross over any code that didn't
;;; expect to be unwound thru.  Since most code in the products is written with
;;; that assumption this can be difficult.

#+forward-reference
(def-concept unwind-protect)



;;; `Warn-of-development-unwinding' is called when ever the process stack
;;; is unwound pass an unwind protect that in production code is eliminated.
;;; such event should never happen, except as part of debugging.

#+development
(defun warn-of-development-unwinding (tag)
  (warn
    "~&Unwind-protect-for-development ~S cleaning up for nonlocal transfer."
    tag))



;;; `Unwind-protect-for-development' has exactly the semantics of unwind protect
;;; when used in development code, with one exception.  The exception is that it
;;; will generate a warning if the unwind-protect code is ever executed.  In
;;; nondevelopment it expands to a prog1.

;;; In production code the system would NEVER unwind through this code.  See
;;; section intro for additional info.

(defmacro unwind-protect-for-development (tag protected-form &body cleanup)
  (assert (symbolp tag))

  #+development
  (let ((normal-exit-flag (gensym)))
    `(let ((,normal-exit-flag nil))
	(ab-lisp::unwind-protect  ;; Note 1
	    (multiple-value-prog1
		,protected-form
	      (setf ,normal-exit-flag t))
	  (unless ,normal-exit-flag
	    (warn-of-development-unwinding ',tag))
	  ,@cleanup)))
  #-development
  `(multiple-value-prog1
    ,protected-form
    ,@cleanup))

;; Note 1: we must reach around the macrolet version of unwind-proctect 
;; and into ab-lisp to get an unwind-protect that won't generate warnings
;; in development.



;;; `Unwind-protect-for-development-using-latest-function' is useful as a direct
;;; replacement for unwind protect in macros.  It will infer a tag by using the
;;; current binding of most-recent-defun-name.

(defmacro unwind-protect-for-development-using-most-recent-defun-name (protected-form &body cleanup)
  `(unwind-protect-for-development ,most-recent-defun-name
      ,protected-form
    ,@cleanup))






;;;; Catch Tag Establishment




;;; The following macro provides a clean interface for specifying catch tags.
;;; The interface allows the specification of tags around bodies of code, the
;;; binding of thrown values into variables, and the execution of code within
;;; such bindings when a particular tag is caught.  This facility provides no
;;; special memory management or other hacks, but is simply a nicer environment
;;; within which to specify catch tags.
;;;
;;; The macro `with-catch-handlers' takes the following form:
;;;
;;;   (with-catch-handlers (catch-handler ...)
;;;     &body protected-forms)
;;;
;;; Each specified catch handler takes the following form:
;;;
;;;   (catch-tag-or-list-of-tags throw-binding-list &body catch-forms)
;;;
;;; Catch handlers will be established for the tag or tags.  If a throw is
;;; executed the protected forms, the thrown values will be bound to the
;;; variable sin the throw-binding-list, and the catch-forms will be executed,
;;; returning all values from the last form in the catch-forms.  If all
;;; protected-forms execute without a throw, all values returned by the last
;;; protected form will be returned by the with-catch-handlers form.
;;;
;;; Also note that the scope of an established catch handler encompasses the
;;; catch-forms of succeeding catch handlers.  That is, the first catch handler
;;; has scope over the rest of the catch handlers as well as the
;;; protected-forms.
;;;
;;; All of our current implementations have been tested to show that CATCH and
;;; THROW forms do not cons.  -jra 3/31/89

(defmacro with-catch-handlers (catch-handlers &body forms)
  (let ((body (if (cdr forms)
		  `(progn ,@forms)
		  (car forms)))
	(block-name (gensym))
	tags catch-bind-list? catch-forms)
    (loop for catch-handler in (reverse catch-handlers)
	  do
      (setq tags (if (consp (car catch-handler))
		     (car catch-handler)
		     (list (car catch-handler))))
      (setq catch-bind-list? (second catch-handler))
      (setq catch-forms (or (cddr catch-handler) (list nil)))
      (setq body `(return-from ,block-name ,body))
      (loop for tag in tags
	    do
	(setq body `(catch ,tag ,body)))
      (cond ((null catch-bind-list?)
	     (setq body `(progn ,body ,@catch-forms)))
	    ((null (cdr catch-bind-list?))
	     (setq body `(let ((,(car catch-bind-list?) ,body))
			   ,@catch-forms)))
	    (t
	     (setq body
		   `(multiple-value-bind ,catch-bind-list?
			,body
		      ,@catch-forms)))))
    `(block ,block-name ,body)))










;;;; Basic Set Operations




;;; The function `compress-set' takes a list of objects and returns the
;;; shortest list which corresponds to the set of characters represented by the
;;; original list.  For example, #.(compress-set #\a #\a #\b) returns (#\a
;;; #\b), #.(compress-set #\a #\b) returns (#\a #\b) - not the lack of a quote
;;; before the returned form.  This function conses, but it is only intended to
;;; be used at compile time when references to sets of typeable Gensym
;;; characters are needed.

;;; Unused (same as remove-duplicates, anyways). (fmw 3-Aug-93)
;(defun-for-macro compress-set (&rest char-set)
;  (let* ((new-set nil))
;    (dolist (item-or-list char-set (nreverse new-set))
;      (if (listp item-or-list)
;          ;; List present
;          (dolist (item item-or-list)
;            (if (not (member item new-set))
;                (push item new-set)))
;          ;; Item present
;          (if (not (member item-or-list new-set))
;              (push item-or-list new-set))))))










;;;; Sleep


;;; The macro `gensym-sleep' will expand to a call to ab-lisp:sleep
;;; in distribution software, and to ab::development-sleep in
;;; development software.

#+development
(defparameter check-memory-on-development-sleep nil)

#+development
(defun development-sleep (intervals-in-seconds)
  (when check-memory-on-development-sleep
    (check-memory-for-development 'development-sleep-enter))
  (prog1
    (sleep intervals-in-seconds)
    (when check-memory-on-development-sleep
      (check-memory-for-development 'development-sleep-exit))))




;;; `Gensym-sleep' is the macro that all the modules should refer
;;; to instead of the Common Lisp sleep function.

(defmacro gensym-sleep (intervals-in-seconds)
  (if (eval-feature :development)
      `(development-sleep ,intervals-in-seconds)
      `(sleep ,intervals-in-seconds)))






;;;; KFEP Switches



;; KFEP1 and KFEP2 are optional modules, but kfep-capability? is referred to in 
;; non-optional modules.  Thus, we put the kfep-capability? definition here, for 
;; lack of a better place.  -pto 17apr90

;;; Kfep-capability? must be true for kfep functionality to be enabled.

(defvar kfep-capability? nil)

;; Have this set according to authorization, platform limitations, and availability
;; of software and fonts!




;;; Hfep-capability? ... analagous to "kfep-capability?", but applies to Hangul
;;; (Korean) input capability.

(defvar hfep-capability? nil)





;;;; Inline Binary Search Code



;;; Generate-binary-search-code is a defun-for-macro that can be used to
;;; generate an inline binary search over a constant set of integer.
;;; Integer-upper-limits must be a list of fixnum integers, sorted by increasing
;;; order.  Corresponding-forms must be a list of forms, of the same length, to
;;; evaluate upon a match.  A match occurs when integer-variable is less than or
;;; equal to (<=f) an element of integer-upper-limits, and greater than (>f) any
;;; preceeding element in the ordered list integer-upper-limits.  Upon a match,
;;; the corresponding form is evaluated.  It may, for example, verify that the
;;; integer variable is greater than or equal to (>=f) a lower limit.

;;; Integer-out-of-bounds-form is the form to evaluate in the case where integer-
;;; variable is greater than the highest integer in integer-upper-limits.

;;; For example, the following code might be generated to ensure that a number
;;; fits within one of several ranges, in this case the ascii character codes for
;;; 0-9, A-Z, or a-z, or [48..57], [65..90], and [97..122], respectively:
;;;
;;;     (generate-binary-search-code
;;;       'code
;;;       '(57 90 122)
;;;       '((>=f code 48) (>=f code 65) (>=f code 97))
;;;       nil)
;;;
;;;   => (if (<=f code 90)
;;;          (if (<=f code 57)
;;;              (>=f code 48)
;;;              (>=f code 65))
;;;          (if (<=f code 122)
;;;              (>=f code 97)
;;;              nil))
;;;
;;; Thus, alphanumeric-code-p could be defined as a macro with
;;;
;;;    (defmacro alphanumeric-code-p (code)
;;;       (generate-binary-search-code
;;;         code
;;;         '(57 90 122)
;;;         '((>=f code 48) (>=f code 65) (>=f code 97))
;;;         nil))

(defun-for-macro generate-binary-search-code
  (integer-variable integer-upper-limits
   corresponding-forms integer-out-of-bounds-form)
  (loop with if-forms
	  = (append
	      (butlast integer-upper-limits)
	      (list (cons
		      (car (last integer-upper-limits))
		      `(if (<=f ,integer-variable ,(car (last integer-upper-limits)))
			   ,(car (last corresponding-forms))
			   ,integer-out-of-bounds-form))))
	with depth-of-if-forms
	  = (if integer-upper-limits
		(truncate (/ (log (length integer-upper-limits)) #.(log 2)))
		0)
	repeat (+ depth-of-if-forms 1)
	do (setq if-forms
		 (loop as (low-value-or-pair high-value-or-pair) on if-forms by #'cddr
		       as low-value
			  = (if (numberp low-value-or-pair)
				low-value-or-pair
				(car low-value-or-pair))
		       as low-form
			  = (if (numberp low-value-or-pair)
				(nth
				  (position
				    low-value-or-pair
				    integer-upper-limits)
				  corresponding-forms)
				(cdr low-value-or-pair))
		       as high-value
			  = (if (numberp high-value-or-pair)
				high-value-or-pair
				(car high-value-or-pair))
		       as high-form
			  = (if (numberp high-value-or-pair)
				(nth 
				  (position
				    high-value-or-pair
				    integer-upper-limits)
				  corresponding-forms)
				(cdr high-value-or-pair))
		       collect
			 `(,high-value
			   . ,(if high-form
				  `(if (<=f ,integer-variable ,low-value) ,low-form ,high-form)
				  low-form))))
	finally
	  (return (cdr (car if-forms)))))

;; This is a general utility, which naturally belongs in one of the UTILITIES modules.
;; However, it is needed in this module, which comes earlier!  (MHD 11/3/92)

;; This is based on the code and adapted from the code in WINDOWS1, originally by
;; Ong, Peng Tsin.  This should replace much of that original code eventually.  See
;; the macro find-smallest-regular-size-1 in WINDOWS1.  (MHD 11/3/92)  

;; Note that Peng's original had the flaw that it generated generic <= tests, not
;; fixnum <=f tests.  This probably cost a fair amount of overhead in the graphics
;; code, so we may see a slight performance gain from plugging this in.

;; This could probably be rewritten more easily and straightforwardly as a recursive
;; function, instead of an interative.  This version more closely resembles Peng's
;; original.




;;; `Ez-generate-binary-search-code' is an alternative, usually easier
;;; interface, to generate-binary-search-code.  It takes the upper limits and
;;; corresponding forms together, which is usually easier to deal with, and also
;;; does not require upper limits to be in proper lowest to highest order.

(defun-for-macro ez-generate-binary-search-code
    (integer-variable unsorted-upper-limits-and-forms integer-out-of-bounds-form)
  (let ((upper-limits-and-forms
	  (sort (copy-list unsorted-upper-limits-and-forms)
		#'(lambda (x y) (< (eval (car x)) (eval (car y)))))))
    (loop for (upper-limit form) in upper-limits-and-forms
	  collect upper-limit into upper-limits
	  collect form into forms
	  finally
	    (return
	      (generate-binary-search-code
		integer-variable
		upper-limits
		forms
		integer-out-of-bounds-form)))))




;; End file with CR

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module LETTERS: Utilities for Defining "Letters" and Other Higher-level
;;;; Specifics of Unicode Characters

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David






;;;; Unicode Miscellaneous Utilities



(defmacro mhd-evenpf (x)
  `(=f (logandf 1 ,x) 0))

(defmacro mhd-oddpf (x)
  `(=f (logandf 1 ,x) 1))

;; When evenpf/oddpf are implemented, replace callers with them, and eliminate
;; the above functions.





;;;; Unicode Block Definition Facilities



(define-structure unicode-block ()
  (:managed nil)
  (:conc-name t)
  name
  range
  case-mappings
  not-normally-case-converted-p)


(def-global-property-name unicode-block)

(defvar all-unicode-block-names nil)



;;; `Def-unicode-block' ...

;;; The first argument is the name.  It should be a symbol naming the unicode
;;; block, conventionally named as per the Unicode Standard.  For blocks that
;;; are not being dealt with, the recommended convention is such blocks that
;;; are adjacent together, and to call them "miscellaneous", "miscellaneous-1",
;;; "miscellaneous-2", etc.
;;;
;;; The second argument is the range.  This should be a list of the form
;;;
;;;    (low high)
;;;
;;; giving the inclusive range of this block.  Note that these need not refer to
;;; legal characters, just to a block reserved for a particular subset of
;;; codes. Low and high should, by convention, be a multiple of 16 and 1 less
;;; than a multiple of 16, respectively, e.g., (0 255), since Unicode blocks
;;; generally are so assigned.
;;;
;;; The third arument, case mappings, should be a list, possibly empty, of
;;; lettercase mapping specs for this code block.  Note that many blocks have no
;;; case mappings, e.g., Hebrew, Arabic, etc.
;;;
;;; Each lettercase mapping spec is of one of the following forms:
;;;
;;;    (:LOWER-RANGE (low high) :OFFSET-TO-UPPER offset)
;;;
;;;        Low and high give the inclusive bounds of all lowercase
;;;        letters to which offset can be added to get each corresponding
;;;        uppercase letter.
;;;
;;;
;;;    (:LOWER-ODD-RANGE (low high) :OFFSET-TO-UPPER offset)
;;;    (:LOWER-EVEN-RANGE (low high) :OFFSET-TO-UPPER offset)
;;;
;;;        Low and high give the inclusive bounds of alternating upper- and
;;;        lowercase letters, with either odd or even code values, to which
;;;        offset can be added to get each corresponding uppercase letter.
;;;        Note that offset here should either be 1 or -1.
;;;
;;;
;;;    (:LOWERCASE-CODE code-1 :UPPERCASE-CODE code-2)
;;;
;;;        Code-1 is the lowercase version of the uppercase letter code-2.
;;;        This is a simple, single mapping.
;;;
;;; Where possible, ranges should be specified, rather simple, single mappings,
;;; since they save average search time and code space in the generated mapping
;;; functions based on these specs.
;;;
;;; The fourth argument, not-normally-case-converted-p, should be true only for
;;; blocks for scripts that should normally be freely case converted.  This is
;;; used, for example, for Georgian, which now just uses the lowercase letters,
;;; though it has historical uppercase letters as well which are included in
;;; Unicode.

;; Document the ranging syntax and the case declaration syntax!!

(defmacro def-unicode-block
    (name range case-mappings &optional not-normally-case-converted-p)
  `(progn
     (pushnew ',name all-unicode-block-names)
     (let ((unicode-block (make-unicode-block)))
       (setf (unicode-block-name unicode-block) ',name)
       (setf (unicode-block-range unicode-block) ',range)
       (setf (unicode-block-case-mappings unicode-block)
	     ',case-mappings)
       (setf (unicode-block-not-normally-case-converted-p unicode-block)
	     ',not-normally-case-converted-p)
       (setf (unicode-block ',name) unicode-block))
     ',name))

  
;;; `Unicode-block-<' compares two unicode block structures, and returns
;;; true if the first one is for a range lower than the second one.

(defun unicode-block-< (unicode-block-1 unicode-block-2)
  (<f (first (unicode-block-range unicode-block-1))
      (first (unicode-block-range unicode-block-2))))




;;;; Unicode Case Handling Function Generation Facilities



;;; Map-unicode-case is a nonstandard macro used to generate efficient
;;; inline code for testing and/or converting lettercase, where appropriate,
;;; based on unicode block definitions.

;;; It is nonstandard in the sense that direction must be either the symbol
;;; UP or DOWN, and it is not evaluated at run time.  Code is evaluated once
;;; at runtime to yield the appropriate result.

;;; This is intended to be used for defining case conversion and predicate
;;; operations.  See uses below.

;;; Generate-unicode-case-map-code-within-block is a submacro that helps to
;;; generate code on a per-block basis.

(defmacro map-unicode-case (code direction)
  `(let ((code ,code))
     (declare (type fixnum code))
     (cond
       ,@(loop for block-name in all-unicode-block-names
	       collect (unicode-block block-name)
		 into unicode-blocks
	       finally
		 (setq unicode-blocks
		       (sort unicode-blocks #'unicode-block-<))
		 (return
		   (loop for unicode-block in unicode-blocks
			 collect
			   `((<=f ,(first (unicode-block-range unicode-block))
				  code
				  ,(second (unicode-block-range unicode-block)))
			     ,(generate-unicode-case-map-code-within-block
				unicode-block direction))))))))


(defun-for-macro generate-unicode-case-map-code-within-block (unicode-block direction)
  `(cond
     . ,(unless
	    (unicode-block-not-normally-case-converted-p
	      unicode-block)
	  (loop for mapping
		    in (unicode-block-case-mappings unicode-block)
		as keyword-1 = (first mapping)
		collect
		  (case keyword-1
		    (:lowercase-code
		     (let ((lower (second mapping)) (upper (fourth mapping)))
		       `((=f code ,(if (eq direction 'down) upper lower))
			 ,(if (eq direction 'down) lower upper))))
		    (t
		     (let* ((range (second mapping))
			    (low (first range))
			    (high (second range))
			    (offset (fourth mapping)))
		       (case keyword-1			     
			 (:lower-range
			  `((<=f ,(+ low (if (eq direction 'down) offset 0))
				 code
				 ,(+ high (if (eq direction 'down) offset 0)))
			    ,(if (eq direction 'down)
				 `(-f code ,offset)
				 `(+f code ,offset))))
			 (:lower-odd-range
			  (if (eq direction 'down)
			      `((and (<=f ,low code ,high) (mhd-evenpf code))
				(-f code ,offset))
			      `((and (<=f ,low code ,high) (mhd-oddpf code))
				(+f code ,offset))))
			 (:lower-even-range
			  (if (eq direction 'down)
			      `((and (<=f ,low code ,high) (mhd-oddpf code))
				(-f code ,offset))
			      `((and (<=f ,low code ,high) (mhd-evenpf code))
				(+f code ,offset))))))))))))











;;;; Unicode Block Definitions




(def-unicode-block basic-latin
    (#x0000 #x007f)
  ((:lower-range (#x0061 #X007A) :offset-to-upper #.(- #x20))))

(def-unicode-block latin-1-supplement
    (#x0080 #x00FF)
  ((:lower-range (#x00E0 #x00F6) :offset-to-upper #.(- #x20))
   (:lower-range (#x00F8 #x00FE) :offset-to-upper #.(- #x20))
   ;; lowercase y diaresis -- uppercase letter is in next block:
   (:lowercase-code #X00FF :uppercase-code #x0178)))

(def-unicode-block latin-extended-a
    (#x0100 #x017F)
  ((:lower-odd-range (#x0100 #x0137) :offset-to-upper -1)
   (:lower-even-range (#x0139 #x0148) :offset-to-upper -1)
   (:lower-odd-range (#x014A #x0177) :offset-to-upper -1)
   (:lower-even-range (#x0179 #x017E) :offset-to-upper -1)))

(def-unicode-block miscellaneous
    ;; Latin Extended-B, IPA Extensions, Spacing Modifier Letters, Combining
    ;; Diacritical Marks
    (#x0180 #x036F)
  ())					; generate mappings from table!


(def-unicode-block basic-greek
    (#x0370 #x03CF)
  ((:lower-range (#x03B1 #x03C1) :offset-to-upper #.(- #x20))
   (:lower-range (#x03C3 #x03C9) :offset-to-upper #.(- #x20))
   					; others? generate from table!
   ))


(def-unicode-block greek-symbols-and-coptic
    (#x03D0 #x03FF)
  ())					; generate mappings from table!

(def-unicode-block cyrillic		; (ISO 8859-5 equivalent)
    (#x0400 #x047F)
  ((:lower-range (#x0430 #x044F) :offset-to-upper #.(- #x20))
   (:lower-range (#x0451 #x045f) :offset-to-upper #.(- #x50))
   (:lower-odd-range (#x0460 #x047F) :offset-to-upper -1)))

(def-unicode-block cyrillic-extended
    (#x0480 #x04FF)
  ())					; generate mappings from table!

(def-unicode-block armenian
    (#x0500 #x058F)
  ((:lower-range (#x0561 #x0586) :offset-to-upper #.(- #x30))
					; others? generate from table!
   ))

(def-unicode-block miscellaneous-2
    ;; Hebrew, Arabic, Lao, etc. (a bunch of scripts with no case)
    (#x0590 #x0EFF)
  ())

(def-unicode-block georgian
    (#X10A0 #x10FF)
  ((:lower-range (#x10D0 #x10F6) :offset-to-upper #.(- #x30)))
  ;; Per documentation in the Unicode Standard, only obsolete/ancient Georgian
  ;; has case. The modern script is based on a subset of the ancient lowercase
  ;; script.  So, don't do case normally for Georgian:
  t)


(def-unicode-block hangul-jamo		; no case
    (#x1100 #x11FF)
  ())

(def-unicode-block latin-extended-additional
    (#x1E00 #x1EFF)
  (
   ;; Do via a table generated from Unicode mapping file!!
   ))

(def-unicode-block greek-extended
    (#x1F00 #x1FFF)
  (
   ;; Do via a table generated from Unicode mapping file!!
   ))

;; A few other blocks higher up probably remain with case mapping
;; requirements; do later!





  





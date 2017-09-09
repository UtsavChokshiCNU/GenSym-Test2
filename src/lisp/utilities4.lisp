;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module UTILITIES4

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David, Lowell Hawkinson, Michael Levin, Stephen DeVoy,
;;; Chris Morel, and Jim Allard





;;; This module is not in Telewindows.

;;; Note: some stuff in this module was originally in UTILITIES1.  It was
;;; moved here mostly in order to separate utilities not needed for
;;; Telewindows or any of the minor systems.
;;; -- the sections:
;;;     ;;;; G2 Text
;;;     ;;;; G2-text Comparison Functions.
;;;     ;;;; G2-text insertion and deletion functions.

;;; Note: some more stuff in this module was added here from UTILITIES3
;;; -- the section: ;;;; KB's and KB-Specific Properties and Variables
;;; (MHD 3/20/91)

;;; In frames2A
(declare-forward-reference frame-hash-function function)

;; In FRAMES3 - called by the macros slot-value-cons, reclaim-slot-value-cons.

(declare-forward-reference thing-is-item-p function)

;; In FRAMES4

(declare-forward-reference reclaim-slot-value function)
(declare-forward-reference copy-for-slot-value function)

;; To FRAMES5

(declare-forward-reference reclaim-items-deleted-since-load-or-save function)

;; To PARSE

(declare-forward-reference set-current-grammar function)
(declare-forward-reference global-grammar variable)


;; To DEBUG

(declare-forward-reference restore-debugging-parameters-to-default-values function)

;; To KB-SAVE3

(declare-forward-reference restore-backup-journaling-parameters-to-default-values function)

;; To PLATFORMS

(declare-forward-reference current-system-name variable)
(declare-forward-reference check-shape-of-window-without-lookahead function)


;; To DEFINITIONS

(declare-forward-reference initialize-kb-name-directories function)



;; To ENTITIES

(declare-forward-reference initialize-modules-and-system-tables-a-list function)



;; To WINDOWS1

(declare-forward-reference sync-graphics-on-native-window-1 function)


;; To LEXER

(declare-forward-reference
  make-evaluation-structure-from-parse-object-reclaiming-it
  function)

;; To PROC-COMP
(declare-forward-reference get-byte-code-body-if-any function)

;; To SETS
(declare-forward-reference current-profile-structure? variable)

;;;; G2 Text




;;; `G2 text' is an abstraction of text and text-strings that allows the
;;; manipulation of either type using the same operator.  This is consistent
;;; with the user's view of text which does not distinguish between one and many
;;; lines of text.

;;; A `g2-text-section' is a part of a g2-text that is of the same subtype as
;;; the g2-text (text or text-string).

;;; A `g2-text-index' is an index into a g2-text that locates a particular
;;; gensym-character.  This zero-based index refers to the number of
;;; gensym-characters that precede that position.



;; When handling g2-text only use the following operations.  If new operations
;; are needed, please add them to this section.  In code outside of this
;; section, do not assume a particular implementation for g2-text (i.e., use
;; these operations)!

;; CURRENTLY, ONLY TEXT-STRINGS (NOT TEXT) ARE HANDLED IN G2-TEXT OPERATIONS!!!

;; You should implement a data abstraction here, not just a union of two types!  (LH)


(defmacro obtain-g2-text (length)
  `(obtain-text-string ,length))


(defmacro reclaim-g2-text (g2-text)
  `(reclaim-text-string ,g2-text))


;;; `G2-text-length' computes the number of gensym-characters in the g2-text.

(defmacro g2-text-length (g2-text)
  `(text-string-length ,g2-text))



;;; `Copy-g2-text-with-case-conversion' makes a copy of g2-text with case
;;; conversion of all characters that have upper and lower case versions.
;;; Which-characters-to-upcase?  may be :first, :first-of-each-word, or :all;
;;; other characters are downcased as appropriate.  Note that the first
;;; character and each character after a space or hyphen are taken as first
;;; characters of words.

;; See copy-text-string-with-case-conversion for more up-to-date documentation.
;; An NIL which-characters-to-upcase? argument, now acts like ":first".  And,
;; an argument of ":none" makes all characters lower-case.  - cpm, 4/14/94

(defmacro copy-g2-text-with-case-conversion (g2-text which-characters-to-upcase?)
  `(copy-text-string-with-case-conversion ,g2-text ,which-characters-to-upcase?))




;;;; G2-text Comparison Functions.




;;; This is the lowest level of the G2-text comparison API.  These api routines
;;; are all currently implemented as macros.  They perform case-insensitive
;;; comparison for all characters in the string, generally according to Unicode
;;; guidelines, although there may be some divergence for very obscure scripts,
;;; for newly added scripts, or as Unicode guidelines change.

(defmacro g2-text-equal (g2-text-1 g2-text-2)
  `(string-equalw ,g2-text-1 ,g2-text-2))

(defmacro g2-text-not-equal (g2-text-1 g2-text-2)
  `(string-not-equalw ,g2-text-1 ,g2-text-2))

(defmacro g2-text-less-than (g2-text-1 g2-text-2)
  `(string-lesspw ,g2-text-1 ,g2-text-2))

(defmacro g2-text-not-less-than (g2-text-1 g2-text-2)
  `(string-not-lesspw ,g2-text-1 ,g2-text-2))

(defmacro g2-text-greater-than (g2-text-1 g2-text-2)
  `(string-greaterpw ,g2-text-1 ,g2-text-2))

(defmacro g2-text-not-greater-than (g2-text-1 g2-text-2)
  `(string-not-greaterpw ,g2-text-1 ,g2-text-2))

;; Optional flag g2-text-simple? was never used, is now entirely obsolete, and
;; has been flushed here and below.  (MHD 6/20/96)



;; Text-string-equal, text-string-lessp, et al, case insensitive text string
;; comparison operations, have gone away.  Their API is completely superceded by
;; string-equalw, string-lesspw, et al.  In addition, text-string-compare is
;; superceded by wide-string-compare with the appropriate args to specify case
;; insensitivity. Notes about text-string-equal, et al, follow:

;; Note that these functions are slightly different from the ones they replace,
;; which were used in 2.1 and 3.0, in that it properly handles case
;; insensitivity when it comes to special characters and Kanji characters.  For
;; example, JIS cyrillic backwards-R, upper and lower case, are considered equal
;; here; and, for example, upper and lower case A with the acute accent are
;; considered equal here.  The previous version did consider "A" and "a" the
;; same, but didn't follow through with the other alphabets or character sets.
;; (MHD 3/20/93)

;; A change is happening again in 5.0: the ordering of the non-ASCII repertoire
;; is completely different.  At least now the ordering corresponds to some
;; standard, namely Unicode, which is the same as the ASCII and ISO Latin 1
;; ordering.  Note the ordering of among Asian characters originally deriving
;; from one or the other standard, i.e., JISX0208 and KSC5601 (Japanese and
;; Korean), is completely different in 6.0, due to Unicode han Unification.
;; (MHD 6/19/96)





;;; `Find-g2-text-section-position' tests if g2-text-to-seek is found within
;;; g2-source-text.  If found, the starting position of the text to seek within
;;; the source text (i.e., a g2-text-index) is returned.  Otherwise, nil is
;;; returned.  Note that if g2-text-to-seek is #w"" (the empty string), this
;;; also returns nil.

;;; This used to be a function which optional arguments, but there were no
;;; callers who ever supplied them, so I'm removing them and making this a
;;; macro.  Anyone who wants optional arguments or needs a function can
;;; call text-string-search directly.  - jv 8/7/96

(defmacro find-g2-text-section-position (g2-text-to-seek g2-source-text)
  `(text-string-search ,g2-text-to-seek ,g2-source-text nil nil))






;;; `Text-string-search' ... Source-Start? and source-end?, if non-nil, index
;;; the positions of characters in source-text.

;;; Combining this function with the now obsolete g2-text-search.  Changed
;;; it to a simple function (by making its formerly optional arguments
;;; required), and changed some of the local variable names to be clearer.
;;; If either source-start?  or source-end?  are supplied non-nil, but are
;;; invalid, this returns nil.  "Find-g2-text-section-position", which used
;;; to call g2-text-search, now calls this function.  - jv 8/7/96

(defun-simple text-string-search (text-to-seek source-text
					       source-start? source-end?)
  (loop with length-1 = (g2-text-length text-to-seek)
	with source-length = (g2-text-length source-text)
	with source-limit = (if source-end?
				(maxf 0 (minf source-length source-end?))
				source-length)
	with source-anchor = (if source-start?
				 (minf source-limit (maxf 0 source-start?))
				 0)
	with character-1
	with source-character
	initially
	  (when (or
		  (=f source-limit source-anchor)
		  (null text-to-seek))
	    (return nil))
	until (>=f source-anchor source-limit)
	when (loop with index-1 = 0
		   with source-index = source-anchor
		   do (setq character-1
			    (read-character-from-text-string
			      text-to-seek index-1))
		      (setq source-character
			    (read-character-from-text-string
			      source-text source-index))
		   always
		     (char-equalw character-1 source-character)
		   until (>=f index-1 length-1)
		   when (>=f source-index source-limit)
		     do (return-from text-string-search nil))
	  return source-anchor
	do (incff source-anchor)))

;; Provide case-sensitive variant, and then give access to it for users of G2 in
;; the language!!  (MHD 2/5/96)




;;; `g2-text-character-search' - like text-string-search, but only seeks
;;; a single character.

(defun-simple g2-text-character-search (character-to-seek source-text)
  (and source-text
       character-to-seek
       (loop with source-length = (g2-text-length source-text)
	     with source-index = 0
	     until (=f source-index source-length)
	     as source-character = (read-character-from-text-string
				     source-text source-index)
	     when (char-equalw character-to-seek source-character)
	       return (1-f source-index))))






;;;; G2-text insertion and deletion functions


;;; `convert-user-g2-text-indices-to-internal-indices' is a replacement for the
;;; old function convert-g2-text-start-and-end-index-to-simple-character-
;;; positions.  The concept of "simple character position" is obsolete in 5.0.
;;; However, the old function did more than that.  It also changed nil to a
;;; valid index, and checked that any fixnum index was in fact within the
;;; range of the string.  However, this function differs from convert-g2-
;;; text-start-and-end-index-to-simple-character-positions in the following
;;; ways:  (a) it checks that start <= end.  It was a design decision
;;; to allow the order to be reversed previously, but there were no users
;;; of that feature.  (b) if either index is invalid, this function
;;; returns nil for *both* indices;  (c) this function checks that
;;; non-nil indices are in fact fixnums before comparing them.

(defun convert-user-g2-text-indices-to-internal-indices
    (g2-text g2-text-start-index? g2-text-end-index?)
  (let* ((g2-text-length (g2-text-length g2-text))
	 (g2-text-start-index (if (fixnump g2-text-start-index?)
				  (1-f g2-text-start-index?)
				  0))
	 (g2-text-end-index (if (fixnump g2-text-end-index?)
				g2-text-end-index?
				g2-text-length)))
    (declare (type fixnum
		   g2-text-length g2-text-start-index
		   g2-text-end-index))
    (if (<=f 0 g2-text-start-index g2-text-end-index g2-text-length)
  	(values g2-text-start-index g2-text-end-index)
  	(values nil nil))))





;;; `Get-from-g2-text' returns a new g2-text containing the section specified by
;;; the start and end index arguments.  The start and end g2-text indices are
;;; one-based and locate gensym-characters.  The gensym-character located at
;;; the end index, if any, is not included in the g2-text-section.  If either
;;; index is not valid, nil is returned.

(defun-simple get-from-g2-text (g2-text g2-text-start-index? g2-text-end-index?)
  (multiple-value-bind
      (g2-text-start-index g2-text-end-index)
      (convert-user-g2-text-indices-to-internal-indices
	g2-text g2-text-start-index? g2-text-end-index?)
    (if g2-text-start-index
	(copy-portion-of-wide-string g2-text
				     g2-text-start-index g2-text-end-index)
	;; else, if indices are not valid, return nil.
	nil)))



;;; The `omit-from-g2-text' function is used to delete a g2-text-section from
;;; a g2-text.  The section is specified with a start and end g2-text character
;;; position.  The end index is not included in the text-section.  These
;;; positions are 1-based g2-text indices, since G2 text is 1-based in the
;;; user's view.   This operation is non-destructive.  If either g2-text
;;; position is not valid, nil is returned.

(defun-simple omit-from-g2-text
    (g2-text g2-text-start-index g2-text-end-index)

  (multiple-value-bind (start-char-index? end-char-index?)
      (convert-user-g2-text-indices-to-internal-indices
	g2-text g2-text-start-index g2-text-end-index)

    (if (and start-char-index? end-char-index?)
	(let* ((length-of-g2-text
		 (g2-text-length g2-text))
	       (new-g2-text
		 (obtain-g2-text
		   (-f length-of-g2-text
		       (-f end-char-index? start-char-index?)))))

	  (if (>f g2-text-start-index 0)
	      (copy-portion-of-string-into-text-string
		g2-text 0 start-char-index? new-g2-text 0))

	  (if (<=f g2-text-start-index length-of-g2-text)
	      ;; The =f case had been omitted!  One example
	      ;; that needs it is: omit-from-text("abc",3,2)
	      ;; - jpg 6/24/02
	      (copy-portion-of-string-into-text-string
		g2-text end-char-index?
		length-of-g2-text
		new-g2-text start-char-index?))

	  ;; Return the new text string.
	  new-g2-text)

	;; Else, if either index is not valid, return nil.
	nil)))

;; Fix the above not to assume simple text strings! Note that we should
;; first of all provide versions of the copy-portion functions above that
;; don't require simple-text-string destinations!  (MHD/CPM 3/25/93)



;;; The `insert-in-g2-text' function is used to insert one g2-text-section
;;; within another at the specified g2-text position (i.e., before the gensym
;;; character that is currently in that position).  This position is a 1-based
;;; g2-text-index, since G2 text is 1-based in the user's view.  This operation
;;; is non-destructive.  If the g2-text position is not valid or the resulting
;;; string would be too long, nil is returned. Otherwise, the new g2-text is
;;; returned.

;;; Error checking: by inserting a very long string into an already very
;;; long string, one could create a string longer than the maximum length
;;; allowed by G2.  If the sum of the lengths of the two strings exceeds
;;; the maximum, signal an error.

(defun-simple insert-in-g2-text
    (insertion-g2-text original-g2-text original-g2-text-start-index)
  (multiple-value-bind (original-g2-text-index?
			 original-g2-text-length)
      (convert-user-g2-text-indices-to-internal-indices
	original-g2-text original-g2-text-start-index nil)
    ;; note that convert-user-g2-text-indices-to-internal-indices returns the
    ;; g2-text-length as the end-index when nil is supplied.

    (if original-g2-text-index?
	(let* ((insertion-g2-text-length
		 (g2-text-length insertion-g2-text))
	       (destination-g2-text-length
		 (+f insertion-g2-text-length original-g2-text-length)))
	  (cond
	    ((>f destination-g2-text-length
		 maximum-length-for-user-text-strings)
	     nil)
	    (t
	     (let ((destination-g2-text
		     (obtain-g2-text destination-g2-text-length)))

	       (unless (=f original-g2-text-index? 0)
		 (copy-portion-of-text-string-into-text-string-given-count
		   original-g2-text 0 destination-g2-text 0
		   original-g2-text-index?))

	       (copy-portion-of-text-string-into-text-string-given-count
		 insertion-g2-text 0 destination-g2-text original-g2-text-index?
		 insertion-g2-text-length)

	       (unless (=f original-g2-text-index? original-g2-text-length)
		 (copy-portion-of-string-into-text-string
		   original-g2-text original-g2-text-index? original-g2-text-length
		   destination-g2-text
		   (+f original-g2-text-index? insertion-g2-text-length)))

	       ;; return the new text.
	       destination-g2-text))))

	;; If index is out of bounds, return nil.
	nil)))



;;; The `replace-in-g2-text' function is used to insert one g2-text-section
;;; within another, "overwriting" the specified g2-text-section.  All positions
;;; are 1-based g2-text-indices, since G2 text is 1-based in the user's view.
;;; This operation is non-destructive.  If the g2-text position is not valid,
;;; character that is currently in that position).  This position is a 1-based
;;; nil is returned.  Otherwise, the new g2-text is returned.

(defun-simple replace-in-g2-text
    (insertion-g2-text original-g2-text
		       original-g2-text-start-index original-g2-text-end-index)
  (multiple-value-bind (g2-text-start-index? g2-text-end-index?)
      (convert-user-g2-text-indices-to-internal-indices
	original-g2-text original-g2-text-start-index original-g2-text-end-index)

    (if g2-text-start-index?
	(let* ((original-g2-text-length
		 (g2-text-length original-g2-text))
	       (insertion-g2-text-length
		 (g2-text-length insertion-g2-text))
	       (omission-g2-text-length
		 (-f g2-text-end-index? g2-text-start-index?))
	       (destination-g2-text
		 (obtain-g2-text
		   (-f original-g2-text-length
		       (-f omission-g2-text-length
			 insertion-g2-text-length)))))
	  (unless (=f g2-text-start-index? 0)
	    (copy-portion-of-text-string-into-text-string-given-count
	      original-g2-text 0 destination-g2-text 0 g2-text-start-index?))

	  (copy-portion-of-text-string-into-text-string-given-count
	    insertion-g2-text 0 destination-g2-text g2-text-start-index?
	    insertion-g2-text-length)

	  (unless (=f g2-text-end-index? original-g2-text-length)
	    (copy-portion-of-string-into-text-string
	      original-g2-text g2-text-end-index? original-g2-text-length
	      destination-g2-text
	      (+f g2-text-start-index? insertion-g2-text-length)))

	  ;; return the new text.
	  destination-g2-text)

	;; If index is out of bounds, return nil.
	nil)))



;;; `next-parse-object'
;;; Takes the result of a regular expression parse, text to search
;;; through, and an index to start at, and returns a parse-object
;;; indicating the first, longest match found.
;;;
;;; This function takes and returns 1-based indices.

(defun-simple next-parse-object (lexing-table original-g2-text start-index end-index)
  (declare (ignore end-index))
  (multiple-value-bind (g2-text-start-index g2-text-length)
      (convert-user-g2-text-indices-to-internal-indices
	original-g2-text start-index nil)
    (declare (ignore g2-text-length))
    (if g2-text-start-index
	(let ((match-parse-object
		(in-lexing-context
		  lexing-table
		  (get-next-token-from-text-string
		    original-g2-text g2-text-start-index))))
	  (incff (parse-object-start-index match-parse-object))
	  match-parse-object)
	nil)))


;;; `indices-for-match' - implements the find-next-pattern evaluator.

(defun-simple indices-for-match (lexing-table source-text search-position)
  (make-evaluation-structure-from-parse-object-reclaiming-it
    (next-parse-object
      lexing-table source-text search-position nil)))




;;; `substring-for-match' - implements the find-next-substring-matching-pattern
;;; evaluator.

(defun-simple substring-for-match (lexing-table original-g2-text start-index)
  (let* ((result-struct
	   (next-parse-object lexing-table
			      original-g2-text
			      start-index nil))
	 (match-start (parse-object-start-index result-struct))
	 (match-end   (parse-object-end-index result-struct))
	 (substring
	   (if (=f match-end no-tokenizer-match-end-index)
	       (obtain-g2-text 0)
	       (get-from-g2-text
		 original-g2-text
		 match-start
		 match-end))))
    (reclaim-parse-object result-struct)
    substring))


;;; `text-with-replacements' - implements the find-and-replace-pattern
;;; evaluator.

(defun-simple text-with-replacements
    (lexing-table text-to-insert original-g2-text search-position stop-searching)
  (multiple-value-bind (g2-text-start-index g2-text-end-index)
      (convert-user-g2-text-indices-to-internal-indices
	original-g2-text search-position stop-searching)
    (if g2-text-start-index
	(twith-output-to-text-string
	  (loop initially
		  (twrite-portion-of-wide-string-unparsably-to-current-wide-string
		    original-g2-text 0 g2-text-start-index)
		with replacement-length = (alphabet-text-string-length text-to-insert)
		as source-index = g2-text-start-index then end-of-match
		for next-token = (next-parse-object lexing-table original-g2-text
						    (1+f source-index) nil)
		as start-of-match = (1-f (parse-object-start-index next-token))
		as end-of-match = (parse-object-end-index next-token)
		until (or (=f end-of-match no-tokenizer-match-end-index)
			  (>=f start-of-match g2-text-end-index))
		do
	    (reclaim-parse-object next-token)
	    (twrite-portion-of-wide-string-unparsably-to-current-wide-string
	      original-g2-text source-index start-of-match)
	    (cond
	      ((<=f end-of-match g2-text-end-index)
	       (twrite-portion-of-wide-string-unparsably-to-current-wide-string
		 text-to-insert 0 replacement-length))
	      (t
	       (let* ((part-of-original-text (get-from-g2-text
					       original-g2-text
					       (1+f start-of-match)
					       g2-text-end-index))
		      (part-match (next-parse-object lexing-table
						     part-of-original-text 1 nil))
		      (part-end-index (parse-object-end-index part-match)))
		 (cond
		   ((=f part-end-index no-tokenizer-match-end-index)
		    (twrite-portion-of-wide-string-unparsably-to-current-wide-string
		      original-g2-text start-of-match end-of-match))
		   (t
		    (twrite-portion-of-wide-string-unparsably-to-current-wide-string
		      text-to-insert 0 replacement-length)
		    (twrite-portion-of-wide-string-unparsably-to-current-wide-string
		      original-g2-text (+f start-of-match part-end-index)
		      end-of-match)))
		 (reclaim-parse-object part-match)
		 (reclaim-text-string part-of-original-text))))
		finally
		  (twrite-portion-of-wide-string-unparsably-to-current-wide-string
		    original-g2-text source-index (alphabet-text-string-length
						    original-g2-text))
		  (reclaim-parse-object next-token)))
	nil)))







;;;; Text Hash Codes



;;; The function `compute-text-hash-code' computes a hash-code by iterating over
;;; the gensym-characters in the text, using the char-code of the lowercase
;;; conversion of the character.

(defun-simple compute-text-hash-code (text-string)
  (let ((character #u0000))
    (declare (type wide-character character))
    (loop with length fixnum = (wide-string-length text-string)
       with index fixnum = 0
       with downcase-character-code fixnum = 0
       with hash-sum fixnum = 0
       while (<f index length)
       do (setq character
                (read-character-from-text-string text-string index))
       (setq downcase-character-code
             (logandf (unicode-downcase (char-codew character)) #x7f))
       (if (g2-enterprise-p)
           (xor-hash-expr hash-sum downcase-character-code 7)
           (xor-hash-expr hash-sum downcase-character-code 1))
       finally
       (return hash-sum))))

;; See if a more efficient version of char-downcasew can be used, or must be
;; created, for efficiency reasons!  Now that we have Unicode, things are not
;; as simple.  (MHD 2/5/96)

;; NB: This returns different results for some strings than it did in 5.0, since
;; the character codes of many characters, especially the non-ASCII repertoire,
;; has changed completely.  (MHD 6/19/96)

;; This is similar, but different, from hash-wide-string, in UNICODE.  The main
;; functionality difference is that this is case insensitive, but
;; hash-wide-string is case sensitive.




;;;; KB's and KB-Specific Properties and Variables



;;; The conser `kb-property' is a consing pool for KB specific property lists.

;;; In addition, the function `reclaim-kb-property-list-function' is defined
;;; as a functional version of the macro reclaim-kb-property-list for use as
;;; a reclaimer function.

(defconser kb-property utilities4)

(defun reclaim-kb-property-list-function (kb-property-list)
  (reclaim-kb-property-list kb-property-list))

;; Reclaim-kb-property-list needs to be funcalled when reclaiming
;; user-menu-choices-for-this-class KB property values.  And it is also used to
;; reclaim kb-state-changes.



;;; All new properties of symbols should be accessed by means of access forms
;;; that are defined via def-global-property-name or
;;; def-global-or-kb-specific-property-name.  In other words, GET should not be
;;; used to access new properties of symbols.  (See also def-global-property and
;;; global-property-names, which are defined in the PRIMITIVES module.)

;; In addition to global and kb-specific properties, there ought to be
;; "ab-process-specific" properties!

;; Note: Def-global-property-name and global-property-names were moved to
;; PRIMITIVES because they need to be used in that module, not because of any
;; machine dependencies.



;;; The variable `*current-kb-specific-property-list-property-name*' ...  Note
;;; that even though *current-kb-specific-property-list-property-name* has a
;;; global value of KB-0, no property lists under that property name should ever
;;; be created.  In fact, there must not be an entry for KB-0 in
;;; *locations-of-kb-specific-property-lists*.

(def-system-variable *current-kb-specific-property-list-property-name*
    utilities4 'kb-0 nil t)



;;; The variable `*locations-of-kb-specific-property-lists*' is of the form
;;;
;;;    ({(kb-specific-property-list-property-name
;;;       . symbols-having-such-a-property)})
;;;
;;; For example, the variable may contain
;;;
;;;    ((KB-1 foo bar) (KB-2 baz uffda))
;;;
;;; This structure is made up of kb-property conses.

(defvar-of-special-global *locations-of-kb-specific-property-lists* nil)




;;; The function `clear-all-kb-properties' removes all kb-specific properties,
;;; which will hopefully soon be GCed.

#+development
(defun clear-all-kb-properties ()
  (loop for (property) in *locations-of-kb-specific-property-lists* doing
       (do-symbols (symbol "AB")
         (remprop symbol property))))




;;; The variable `kb-state-changes' is either nil, or a list of the form
;;;
;;;    (nil . {frame-with-kb-state-changes})
;;;
;;; This structure is made up of kb-property conses.  The value of the car of
;;; the first cons is arbitrary.  There just has to be a dummy cons at the head
;;; of the list to enable uniform handling of the previous cons pointer, i.e.,
;;; so that there's always a cons to serve as the value of
;;; kb-state-changes-previous-cons?, a slot of block (q.v.).

;;; Frames (i.e., blocks) should be recorded as having kb-state changes through
;;; note-as-frame-with-kb-state-changes, and recorded as not having kb-state
;;; changes through remove-as-frame-with-kb-state-changes.

;;; Kb-state-changes is to be maintained so that deleted frames are never in it.
;;; Note that undo-kb-state-changes, note-kb-state-change, and the reclaimer
;;; for the original-kb-state-plist slot, among others (probably), all observe,
;;; maintain, or depend upon this constraint.

(defun initialize-kb-state-changes ()
  (kb-property-list nil))

(def-kb-specific-variable kb-state-changes utilities4
  (:funcall initialize-kb-state-changes) nil
  reclaim-kb-property-list-function)

;; Changed for G2 5.1r5 and G2 6.0 to its current format.  Previously, it was a
;; list of frames, possibly nil, i.e., without the head cons. (MHD 3/27/00)



;;; The variable `*there-is-a-current-kb?*' is set non-nil by
;;; switch-to-new-empty-kb.  It is used by make-frame as well as by various
;;; class definition facilities.

(def-system-variable *there-is-a-current-kb?* utilities4 nil nil t)



;;; `Def-global-or-kb-specific-property-name' defines access and update operations
;;; for `global-or-kb-specific-property-name'.

;;; The accessor for this property will first check if there is kb-specific
;;; value for property, and if so will return it.  If there is no value, it will
;;; then return any global value.  The mutator for this property will first
;;; check the global variable *there-is-a-current-kb?*.  If there is, it will
;;; mutate the kb-specific value for this property.  If there is not, it will
;;; mutate the global value.  Note that it also keeps track of which symbols
;;; have kb-specific property lists via the
;;; *locations-of-kb-specific-property-lists* global variable.


(defvar-of-special-global kb-specific-property-names nil)

(def-global-property-name function-to-copy-global-value-for-this-property-name)

(def-global-property-name do-not-carry-global-property-value-into-kbs?)

(def-global-property-name function-to-reclaim-kb-specific-property-value?)




;;; A test was done in an environment having several g2 processes and several
;;; kbs in at least one window to determine usage of proeprties. The following
;;; properties had been used in both a global and a kb-specific way at least
;;; once:

;;; definition-state slot-assignment old-slot-assignment inferior-classes
;;; class-description superior-class class-definition

;;; A further investigation showed that the only property to have both global
;;; and kb-specific values for the same symbol is inferior-classes, and the only
;;; such symbol is OBJECT.

;;; Code for the investigation follows:



#+development
(defvar  properties-having-global-values nil)
#+development
(defvar  symbols-with-kb-specific-and-global-values nil)

#+development
(defun properties-used-globally ()
  (loop for symbol-list in *locations-of-kb-specific-property-lists* do
       (loop for symbol in (cdr symbol-list) do
            (loop for property in kb-specific-property-names do
                 (when (memq property (symbol-plist symbol))
                   (pushnew property properties-having-global-values)
                   )))))

#+development
(defun symbols-with-global-and-kb-specific-values-for-same-property ()
  (setq symbols-with-kb-specific-and-global-values nil)
  (loop for symbol-list in *locations-of-kb-specific-property-lists* do
       (loop for symbol in (cdr symbol-list) do
            (loop for property in kb-specific-property-names do
                 (and (memq property (symbol-plist symbol))
                      (loop for symbol-list in *locations-of-kb-specific-property-lists*
                         for property-list = (get symbol (car symbol-list)) do
                         (when (memq property property-list)
                           (push (list property symbol)
                                 symbols-with-kb-specific-and-global-values)))))))

  symbols-with-kb-specific-and-global-values)




;;; The macro get-property-value-cons takes a property list and a property, and
;;; either returns the cons in that list whose car holds the value for the given
;;; property, or else it returns nil.

(def-substitution-macro get-property-value-cons (property-list property)
  (loop for property-cons = property-list
			  then (cdr-of-cons (cdr-of-cons property-cons))
	while property-cons
	do
    (when (eq (car-of-cons property-cons) property)
      (setq property-cons (cdr-of-cons property-cons))
      (return property-cons))))

(defvar-of-special-global *no-specific-property-value*
  (make-symbol "NO-SPECIFIC-PROPERTY-VALUE"))

(defmacro def-global-or-kb-specific-property-name
	  (kb-specific-property-name
	   &optional function-to-copy-global-property-value?
	             do-not-carry-global-property-value-into-kbs?
		     function-to-reclaim-kb-specific-property-value?)
  (let ((set-kb-property-value-macro
	  (intern (format nil "SET-KB-SPECIFIC-~a" kb-specific-property-name)))
	(lookup-macro (intern (format nil "~a-MACRO" kb-specific-property-name)))
	(property-name-var
	  (intern (format nil "~a-GKBPROP" kb-specific-property-name))))
    `(progn
       (setq kb-specific-property-names
	     (cons ',kb-specific-property-name
		   kb-specific-property-names))
       ,@(if function-to-copy-global-property-value?
	     `((setf (function-to-copy-global-value-for-this-property-name
		       ',kb-specific-property-name)
		     ',function-to-copy-global-property-value?)))
       ,@(if do-not-carry-global-property-value-into-kbs?
	     `((setf (do-not-carry-global-property-value-into-kbs?
		       ',kb-specific-property-name)
		     t)))
       ,@(if function-to-reclaim-kb-specific-property-value?
	     `((setf (function-to-reclaim-kb-specific-property-value?
		       ',kb-specific-property-name)
		     ',function-to-reclaim-kb-specific-property-value?)))
       (eval-when (:compile-toplevel :load-toplevel :execute)
	 (defparameter ,property-name-var ',kb-specific-property-name))
       (defmacro ,kb-specific-property-name (symbol)
	 `(lookup-global-or-kb-specific-property-value
	    ,symbol ,',property-name-var))
       (defmacro ,lookup-macro (symbol)
	 `(lookup-global-or-kb-specific-property-value-macro
	    ,symbol ,',property-name-var))
       (defmacro ,set-kb-property-value-macro (symbol-form value-form)
	 `(mutate-global-or-kb-specific-property-value
	    ,symbol-form ,value-form ,',property-name-var))
       (defsetf ,kb-specific-property-name ,set-kb-property-value-macro)
       ',kb-specific-property-name)))

;;;
;;; Below are functions that make API to work with global and KB specific
;;; properties. For the time being they are made of property lists either
;;; as symbol plists for global properties or KB specific plists.
;;;

;;;
;;; Properties API using hash-tables
;;;

(def-skip-list-or-binary-tree symbol-properties-hash-table
    :constructor make-symbol-properties-hash-table
    :reclaimer reclaim-symbol-properties-hash-table
    :hash-function sxhash-symbol
    :use-binary-tree nil) ; must be always NIL here

(defvar-of-special-global symbol-properties-table
  (make-symbol-properties-hash-table))

(defmacro get-symbol-properties-from-hash-table-as-is (symbol)
  `(get-symbol-properties-hash-table ,symbol symbol-properties-table))

(defmacro get-symbol-properties-from-hash-table (symbol)
  (let ((symbol-properties (gensym)))
    `(let ((,symbol-properties
            (get-symbol-properties-hash-table ,symbol symbol-properties-table)))
       (unless ,symbol-properties
         (setf ,symbol-properties
               (setf (get-symbol-properties-hash-table ,symbol symbol-properties-table)
                     (make-symbol-properties-hash-table))))
       ,symbol-properties)))

(defmacro put-symbol-properties-into-hash-table (symbol properties)
  `(setf (get-symbol-properties-hash-table ,symbol symbol-properties-table) ,properties))

(defmacro get-property-value-from-hash-table (properties property-name &optional default)
  `(or (get-symbol-properties-hash-table ,property-name ,properties)
       ,default))

(defun is-property-value-in-hash-table? (properties property-name)
  (when properties
    (get-symbol-properties-hash-table property-name properties)))

(defmacro set-property-value-into-hash-table (properties property-name value)
  `(progn
     (setf (get-symbol-properties-hash-table ,property-name ,properties) ,value)
     ,properties))

(defun get-kb-specific-properties-from-hash-table (symbol)
  (let* ((symbol-properties (get-symbol-properties-from-hash-table symbol))
         (kb-specific-properties
          (get-property-value-from-hash-table
            symbol-properties
            *current-kb-specific-property-list-property-name*)))
    (unless kb-specific-properties
      (register-symbol-as-location-of-kb-specific-properties symbol)
      (setq kb-specific-properties
            (make-symbol-properties-hash-table))
      (set-property-value-into-hash-table
        symbol-properties
        *current-kb-specific-property-list-property-name*
        kb-specific-properties))
    kb-specific-properties))

;;;
;;; Properties API using property lists
;;;

(defmacro get-symbol-properties-from-plist-for-search (symbol)
  `(symbol-plist-for-lookup ,symbol))

(defun get-symbol-properties-from-plist (symbol)
  (declare (type symbol symbol))
  (symbol-plist symbol))

(defun put-symbol-properties-into-plist (symbol properties)
  (setf (symbol-plist symbol) properties))

(defun-simple get-property-value-from-plist-without-default (properties property-name)
  (getfq-macro properties property-name))

(defun-simple get-property-value-from-plist-with-default (properties property-name default)
  (getfq-macro properties property-name default))

(defmacro get-property-value-from-plist (properties property-name &optional default)
  `(cond
     (,default
       (get-property-value-from-plist-with-default ,properties ,property-name ,default))
     (t
       (get-property-value-from-plist-without-default ,properties ,property-name))))

(defun set-property-value-into-plist (properties property value)
  (let ((value-place (get-property-value-cons properties property)))
    (if value-place
        (progn
          (setf (car value-place) value)
          properties)
        (kb-property-cons property (kb-property-cons value properties)))))

(defun get-kb-specific-properties-from-plist (symbol)
  (let ((kb-specific-properties-place
         (get-property-value-cons
           (get-symbol-properties-from-plist symbol)
           *current-kb-specific-property-list-property-name*))
        (kb-specific-properties nil))
    (if kb-specific-properties-place
        (setf kb-specific-properties (car-of-cons kb-specific-properties-place))
        (register-symbol-as-location-of-kb-specific-properties symbol))
    kb-specific-properties))

(defun is-property-value-in-plist? (properties property-name)
  (not (null (get-property-value-cons properties property-name))))




;;;
;;; Generalized Properties API
;;;

#-chestnut-trans
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :properties-api-based-on-hash-tables *features*))

(defmacro get-symbol-properties (symbol)
  `(#+properties-api-based-on-hash-tables get-symbol-properties-from-hash-table
    #-properties-api-based-on-hash-tables get-symbol-properties-from-plist
    ,symbol))

(defun get-symbol-properties-function (symbol)
  (get-symbol-properties symbol))

(defmacro put-symbol-properties (symbol properties)
  `(#+properties-api-based-on-hash-tables put-symbol-properties-into-hash-table 
    #-properties-api-based-on-hash-tables put-symbol-properties-into-plist
    ,symbol ,properties))

(defmacro get-property-value (properties property-name &optional default)
  `(#+properties-api-based-on-hash-tables get-property-value-from-hash-table 
    #-properties-api-based-on-hash-tables get-property-value-from-plist
    ,properties ,property-name ,default))

(defun get-property-value-function (properties property-name &optional default)
  (get-property-value properties property-name default))

(defmacro set-property-value (properties property value)
  `(#+properties-api-based-on-hash-tables set-property-value-into-hash-table 
    #-properties-api-based-on-hash-tables set-property-value-into-plist  
    ,properties ,property ,value))

(defun set-property-value-function (properties property value)
  (set-property-value properties property value)
  value)

(defmacro get-kb-specific-properties-from (symbol)
  `(#+properties-api-based-on-hash-tables get-kb-specific-properties-from-hash-table
    #-properties-api-based-on-hash-tables get-kb-specific-properties-from-plist
    ,symbol))

(defmacro is-property-value-in? (properties property-name)
  `(#+properties-api-based-on-hash-tables is-property-value-in-hash-table?
    #-properties-api-based-on-hash-tables is-property-value-in-plist? 
    ,properties ,property-name))

(defun register-symbol-as-location-of-kb-specific-properties (symbol)
  (let ((location-of-list-of-kb-specific-symbols
         (assq-macro
           *current-kb-specific-property-list-property-name*
           *locations-of-kb-specific-property-lists*)))
    (if location-of-list-of-kb-specific-symbols
        (setf (cdr location-of-list-of-kb-specific-symbols)
              (kb-property-cons
                symbol
                (cdr location-of-list-of-kb-specific-symbols)))
      (error "*location-of-list-of-kb-specific-symbols* is not initialized"))))

;;; The function `lookup-global-or-kb-specific-property-value' is used to lookup
;;; specific properties on symbols.  It first attempts to find the KB specific
;;; value, and if it does not find that, it finds and returns any global value.

(declare-side-effect-free-function lookup-global-or-kb-specific-property-value)

(def-substitution-macro
    lookup-global-or-kb-specific-property-value-macro (symbol property-name)
  (let* ((global-properties (get-symbol-properties symbol))
         (kb-properties (get-property-value global-properties
                          *current-kb-specific-property-list-property-name*))
         (kb-specific-value
          (if kb-properties
              (get-property-value kb-properties property-name 
                                  *no-specific-property-value*)
            *no-specific-property-value*))
         (resulting-value
          (if (not (eq kb-specific-value *no-specific-property-value*))
              kb-specific-value
            (get-property-value global-properties property-name))))
    resulting-value))

(defun-simple lookup-global-or-kb-specific-property-value
    (symbol property-name)
  #+development
  (unless (and (symbolp symbol) (symbolp property-name))
    (error "Arguments to lookup-global-or-kb-specific-property-value must be symbols!"))
  (lookup-global-or-kb-specific-property-value-macro symbol property-name))

;; Note that in the implementation above, great pains are taken to not traverse
;; the property list twice in the case where there is no kb specific property
;; list.  -jra 11/1/91


;;; The following function is used to mutate the values of KB specific
;;; properties.  It is the expansion of a defsetf form, and so should be sure to
;;; return the value which is being placed into the property.

(defun-simple mutate-global-or-kb-specific-property-value
    (symbol value property)
  (as-atomic-operation
    (let* ((global-properties (get-symbol-properties symbol))
           (properties
            (if *there-is-a-current-kb?*
                (set-property-value
                  global-properties
                  *current-kb-specific-property-list-property-name*
                  (set-property-value
                    (get-kb-specific-properties-from symbol) property
                    value))
              (set-property-value global-properties
                                  property value))))
      (put-symbol-properties symbol properties)
      value)))

;;; The function `copy-kb-specific-property-from-global-if-necessary' is called
;;; with a symbol and a property-name symbol.  If there is currently no KB
;;; specific property value for this property, the global value (if any) will be
;;; copied into a KB specific property entry.  Note that to use this facility,
;;; you must give the def-global-or-kb-specific-property-name form a copier
;;; function.

(defun copy-kb-specific-property-from-global-if-necessary (symbol property)
  (unless (is-property-value-in?
            (get-property-value (get-symbol-properties symbol)
                                *current-kb-specific-property-list-property-name*)
            property)
    (mutate-global-or-kb-specific-property-value
       symbol
       (funcall-symbol
         (function-to-copy-global-value-for-this-property-name property)
         (get-property-value (get-symbol-properties symbol) property))
       property)))




;;; The function `reclaim-kb-specific-properties' reclaims all kb-specific
;;; properties for *current-kb-specific-property-list-property-name*, provided
;;; there is an entry for it in *locations-of-kb-specific-property-lists*.  Each
;;; symbol containing a kb-specific property list for this KB will have its
;;; spine reclaimed, and any properties on those lists with reclaimer functions
;;; will have the functions called on the property value before it is unbound.
;;; Unless keep-locations-entry? is non-nil, the entry for
;;; *current-kb-specific-property-list-property-name* in
;;; locations-of-kb-specific-property-lists will be deleted.

(defun reclaim-kb-specific-properties (keep-locations-entry?)
  (let* ((location-cons?
	  (loop for entry-cons on *locations-of-kb-specific-property-lists*
		do
	    (if (eq (caar entry-cons)
		    *current-kb-specific-property-list-property-name*)
		(return entry-cons)))))
    (cond
      (location-cons?
       (loop for symbol in (cdar location-cons?) ;; kb specific properties
	     for symbol-properties = (get-symbol-properties symbol)
	     for specific-property-list ; plist or hash-table
		 = (get-property-value symbol-properties
				       *current-kb-specific-property-list-property-name*)
	     do
	 (cond
	   #-properties-api-based-on-hash-tables
	   (specific-property-list
	    (loop for property-cons on specific-property-list by 'cddr
	       for property = (car property-cons)
	       for property-value-cons = (cdr property-cons)
	       for property-value = (car property-value-cons)
	       do
	       (let ((reclaimer?
		      (function-to-reclaim-kb-specific-property-value? property)))
		 (if reclaimer?
		     (funcall-symbol reclaimer? property-value))
		 (setf (car property-value-cons) nil)))	; make sure car is dereferenced
	    (reclaim-kb-property-list specific-property-list))
	   #+properties-api-based-on-hash-tables
	   ((and specific-property-list
		 (not (binary-tree-empty-p specific-property-list)))
	    (loop for (property . property-value) being each binary-tree-entry-cons
						of specific-property-list
		  as reclaimer? = (function-to-reclaim-kb-specific-property-value? property)
		  when reclaimer? do
	      (funcall-symbol reclaimer? property-value))
	    (reclaim-symbol-properties-hash-table specific-property-list)))

	 #-properties-api-based-on-hash-tables
	 ;; Now get rid of the conses in the symbol's global plist.
	 (as-atomic-operation
	    (let ((symbol-property-list (symbol-plist symbol)))
	      (cond ((eq (car symbol-property-list)
			 *current-kb-specific-property-list-property-name*)
		     (setf (symbol-plist symbol)
			   (cddr symbol-property-list))
		     (reclaim-kb-property-cons-macro (cdr symbol-property-list))
		     (reclaim-kb-property-cons-macro symbol-property-list))
		    (t
		     (loop with lag-property-cons = (cdr symbol-property-list)
			for property-cons on symbol-property-list by 'cddr
			do
			(cond ((eq (car property-cons)
				   *current-kb-specific-property-list-property-name*)
			       (setf (cdr lag-property-cons)
				     (cddr property-cons))
			       (reclaim-kb-property-cons-macro (cdr property-cons))
			       (reclaim-kb-property-cons-macro property-cons)
			       (return nil))
			      (t
			       (setq lag-property-cons (cdr property-cons)))))))))
	  #+properties-api-based-on-hash-tables
	  (delete-symbol-properties-hash-table
	    *current-kb-specific-property-list-property-name*
	    symbol-properties))

       ;; Now outside of above LOOP
       (reclaim-kb-property-list (cdar location-cons?))
       (setf (cdar location-cons?) nil)
       (cond
	 ((not keep-locations-entry?)
	  (reclaim-kb-property-cons (car location-cons?))
	  (as-atomic-operation
	    (setq *locations-of-kb-specific-property-lists*
		  (delete-kb-property-cons
		    location-cons?
		    *locations-of-kb-specific-property-lists*)))
	  ;; reclaim *current-kb-specific-property-list-property-name* ?
	  ))))))



;;; `Def-kb-specific-property-name' declares a symbol property which values
;;; local to individual a kbs, and never outside of a KB.  It takes the name of
;;; the property as its first argument, and an optional unquoted symbol naming a
;;; reclaiming function as its second argument.  This reclaimer is only called
;;; when a kb is being unloaded and reclaimed.  If you overwrite a property
;;; value, you are responsible for reclaiming it beforehand.

(defmacro def-kb-specific-property-name
	  (kb-specific-property-name
	   &optional function-to-reclaim-kb-specific-property-value?)
  (let ((set-kb-property-value-macro
	  (intern (format nil "SET-KB-SPECIFIC-~a" kb-specific-property-name)))
	(lookup-macro (intern (format nil "~a-MACRO" kb-specific-property-name)))
	(property-name-var
	  (intern (format nil "~a-KBPROP" kb-specific-property-name))))
    `(progn
       (setq kb-specific-property-names
	     (cons ',kb-specific-property-name
		   kb-specific-property-names))
       ;; This is always t for kb-specific only properties
       (setf (do-not-carry-global-property-value-into-kbs?
	       ',kb-specific-property-name)
	     t)

       ,@(if function-to-reclaim-kb-specific-property-value?
	     `((setf (function-to-reclaim-kb-specific-property-value?
		       ',kb-specific-property-name)
		     ',function-to-reclaim-kb-specific-property-value?)))
       (eval-when (:compile-toplevel :load-toplevel :execute)
	 (defparameter ,property-name-var ',kb-specific-property-name))
       ;; Look for the kb-specific property only
       (defmacro ,kb-specific-property-name (symbol)
	 `(lookup-kb-specific-property-value
	    ,symbol ,',property-name-var))
       (defmacro ,lookup-macro (symbol)
	 `(lookup-kb-specific-property-value-macro
	    ,symbol ,',property-name-var))
       (defmacro ,set-kb-property-value-macro (symbol-form value-form)
	 `(mutate-kb-specific-property-value
	    ,symbol-form ,value-form ,',property-name-var))
       (defsetf ,kb-specific-property-name ,set-kb-property-value-macro)
       ',kb-specific-property-name)))




;;; The function `lookup-kb-specific-property-value' takes a symbol and a
;;; property name symbol and returns any the KB specific property value for that
;;; symbol.  If there is none, it returns nil.

(declare-side-effect-free-function lookup-kb-specific-property-value)

(defmacro lookup-kb-specific-property-value-macro
    (symbol kb-specific-property-name &optional default)
  `(getfq-macro
    (getfq-macro
     (symbol-plist-for-lookup ,symbol)
     *current-kb-specific-property-list-property-name*)
    ,kb-specific-property-name
    ,default))

(defun-simple lookup-kb-specific-property-value (symbol kb-specific-property-name)
  #+development
  (unless (and (symbolp symbol) (symbolp kb-specific-property-name))
    (error "Arguments to lookup-kb-specific-property-value must be symbols.!"))
  (lookup-kb-specific-property-value-macro symbol kb-specific-property-name))

(defun-simple lookup-kb-specific-property-value-with-default (symbol kb-specific-property-name default)
  #+development
  (unless (and (symbolp symbol) (symbolp kb-specific-property-name))
    (error "Arguments to lookup-kb-specific-property-value must be symbols.!"))
  (lookup-kb-specific-property-value-macro symbol kb-specific-property-name default))




;;; This function differs from mutate-kb-global-or-specific-property-value only
;;; in that it is an error to set a global value of such a property.  After we
;;; are sure this is not happening, the intial test could be removed.

(declare-function-type mutate-kb-specific-property-value (t t t) (t))

(defun-simple mutate-kb-specific-property-value (symbol value property)
  #+development
  (unless *there-is-a-current-kb?*
    (cerror
     "Continue anyway"
     "The kb-specific property ~A of the symbol ~A may not be set outside of a kb."
     property symbol)
    (return-from mutate-kb-specific-property-value value))
  (as-atomic-operation
    (let ((kb-specific-property-list-cons
           (get-property-value-cons
            (symbol-plist symbol)
            *current-kb-specific-property-list-property-name*)))
      (if kb-specific-property-list-cons
	  (let ((property-value-cons
                 (get-property-value-cons
                  (car-of-cons kb-specific-property-list-cons)
                  property)))
	    (if property-value-cons
		(setf (car property-value-cons) value)
		(setf (car kb-specific-property-list-cons)
		      (kb-property-cons-macro
                       property
                       (kb-property-cons-macro
                        value
                        (car-of-cons kb-specific-property-list-cons))))))
	  (let ((location-of-list-of-kb-specific-symbols
                 (assq-macro *current-kb-specific-property-list-property-name*
                             *locations-of-kb-specific-property-lists*)))
	    (setf (cdr location-of-list-of-kb-specific-symbols)
		  (kb-property-cons
                   symbol
                   (cdr-of-cons location-of-list-of-kb-specific-symbols)))
	    (setf (symbol-plist symbol)
		  (kb-property-cons
                   *current-kb-specific-property-list-property-name*
                   (kb-property-cons
                    (kb-property-cons
                     property
                     (kb-property-cons value nil))
                    (symbol-plist symbol))))))))
  value)



;;; In-kb executes body in the context of the KB specified by specified by
;;; kb-specific-property-list-property-name, for which there must be an entry
;;; in *locations-of-kb-specific-property-lists*.

(defmacro in-kb ((kb-specific-property-list-property-name) &body body)
  (let ((old-kb-specific-property-list-property-name (gensym)))
    `(let ((,old-kb-specific-property-list-property-name
	    *current-kb-specific-property-list-property-name*))
       (switch-to-kb ,kb-specific-property-list-property-name)
       (unwind-protect
            (progn . ,body)
	 (switch-to-kb ,old-kb-specific-property-list-property-name)))))


;; ELIMINATE THE FOLLOWING ONCE THE VARIABLES HAVE BECOME KB-SPECIFIC!

(declare-forward-reference initialize-data-server-properties function)

;;; Switch-to-new-empty-kb makes a new empty kb.

(defvar last-assigned-global-kb-number 0)

(defun-simple switch-to-new-empty-kb ()
  (restore-debugging-parameters-to-default-values)
  (restore-backup-journaling-parameters-to-default-values)
  (reclaim-items-deleted-since-load-or-save)
  (atomic-exchange *there-is-a-current-kb?* t)
  (set-current-grammar global-grammar) ; remove later? (now compiles grammar)
  (switch-to-kb
   (as-atomic-operation
     (let ((kb-specific-property-list-property-name
            (intern-text-string
             (tformat-text-string
              "KB-~D" (atomic-incff last-assigned-global-kb-number)))))
       #+SymScale
       (kb-property-push-atomic (kb-property-list kb-specific-property-list-property-name)
				*locations-of-kb-specific-property-lists*)
       #-SymScale
       (setq *locations-of-kb-specific-property-lists*
             (kb-property-cons
               (kb-property-list kb-specific-property-list-property-name)
               *locations-of-kb-specific-property-lists*))
       kb-specific-property-list-property-name)))
  (initialize-data-server-properties)   ; remove later!
  (initialize-modules-and-system-tables-a-list)
  (initialize-kb-name-directories))





;;; Switch-to-kb switches the current process to the kb specified by
;;; kb-specific-property-list-property-name, for which there must be an entry
;;; in *locations-of-kb-specific-property-lists*, unless that is already the current kb.
;;; *current-kb-specific-property-list-property-name* is ignored if it neither is the
;;; same as kb-specific-property-list-property-name nor has an entry in
;;; *locations-of-kb-specific-property-lists*.

;;; Values of kb-specific variables are saved only if there is an entry in
;;; *locations-of-kb-specific-property-lists* for
;;; *current-kb-specific-property-list-property-name*.  (There is no such entry
;;; for KB-0.)

;;; This assumes that no new kb-specific variables can be defined after a kb has
;;; been loaded.

(def-kb-specific-property-name kb-specific-variable-plist
			       reclaim-gensym-list-function)

;; SymScale notes: SWITCH-KB will change lots of global variables which is
;;; considered as KB specific, use a lock here to make sure all threads can
;;; have a consist view of system memory.  -- Chun Tian (binghe), 2009/11/24

(defun-simple switch-to-kb (kb-specific-property-list-property-name)
  (unless (eq kb-specific-property-list-property-name
              *current-kb-specific-property-list-property-name*)
    (when (assq *current-kb-specific-property-list-property-name*
                *locations-of-kb-specific-property-lists*)
      (let ((kb-specific-variable-plist
             (kb-specific-variable-plist
              *current-kb-specific-property-list-property-name*)))
        (if kb-specific-variable-plist
            (loop for l on kb-specific-variable-plist by 'cddr do
                 (setf (cadr l)
                       (symbol-value (car l))))
            (loop for module-name in (system-modules current-system-name) do
              (loop for (system-variable-name nil nil kb-specific?) in
                        (system-variable-descriptions module-name)
                    when kb-specific?
                    do (setq kb-specific-variable-plist
                             (gensym-cons system-variable-name
                               (gensym-cons (symbol-value system-variable-name)
                                 kb-specific-variable-plist))))
                 finally
                 (setf (kb-specific-variable-plist
                        *current-kb-specific-property-list-property-name*)
                       kb-specific-variable-plist)))))
    (setq *current-kb-specific-property-list-property-name*
          kb-specific-property-list-property-name)
    (let ((kb-specific-variable-plist
           (kb-specific-variable-plist
            *current-kb-specific-property-list-property-name*)))
      (if kb-specific-variable-plist
          (progn
            #-development
            (loop for (kb-specific-variable value) on kb-specific-variable-plist by 'cddr do
              (set kb-specific-variable value))
            #+development
            (loop for module-name in (system-modules current-system-name) do
              (loop for (system-variable-name initialization nil kb-specific? nil) in
                        (system-variable-descriptions module-name)
                    when kb-specific?
                    do (let ((saved-value-if-any
                              (getfq kb-specific-variable-plist
                                     system-variable-name no-saved-initial-value)))
                         (if (eq saved-value-if-any no-saved-initial-value)
                             (set-system-variable-as-appropriate
                               system-variable-name initialization)
                             (set system-variable-name saved-value-if-any))))
                 finally
                 (setf (kb-specific-variable-plist
                        kb-specific-property-list-property-name) nil)
                 (reclaim-gensym-list kb-specific-variable-plist)))
          (let (kb-specific-variable-plist)
            (loop for module-name in (system-modules current-system-name) do
                 (loop for (system-variable-name initialization nil kb-specific?)
                       in (system-variable-descriptions module-name)
                    when kb-specific?
                    do (set-system-variable-as-appropriate system-variable-name initialization)
                    #-development
                    (setq kb-specific-variable-plist
                          (gensym-cons system-variable-name
                            (gensym-cons (symbol-value system-variable-name)
                              kb-specific-variable-plist)))))
            (setf (kb-specific-variable-plist
                   *current-kb-specific-property-list-property-name*)
                  kb-specific-variable-plist)))))) ; nreverse-plist?

;; Consider speeding this up a bit by defining
;; set-system-variable-as-appropriate as a macro.

;; Consider speeding this up a bit by keeping a
;; kb-specific-variable-descriptions property on module names that is separate
;; and distinct from the system-variable-descriptions property.



;;; Reclaim-values-of-kb-specific-variables ...

(defun reclaim-values-of-kb-specific-variables (system-name)
  (loop as module-name in (system-modules system-name)
	do
    (loop for (system-variable-name
		nil				; initialization
		nil				; re-evaluate-initialization-on-rebinding?
		kb-specific?
		value-reclaimer?)
	      in (system-variable-descriptions module-name)
	  when (and kb-specific?
		    value-reclaimer?)
	    do (funcall-symbol value-reclaimer? (symbol-value system-variable-name))
	       (setf (symbol-value system-variable-name) nil))))






;;;; Valid Procedure Environment Property




;;; The property `function-keeps-procedure-environment-valid?' is a flag on a
;;; Lisp function name that that specifies whether the function (a Lisp function
;;; called from a system-procedure) will keep the environment of the
;;; system-procedure and any other executing procedure valid.

;;; If the property is non-NIL, the Lisp function will never invalidate
;;; a local-variable environment.  NIL means that it might.

;;; To keep all local-variables valid means that the function will not cause any
;;; item in a procedure's local-variable environment to be inaccessible because
;;; of the item being deleted or deactivated.  The G2 actions that could cause
;;; this invalidation include:
;;; - deleting, deactivating, or transfering an item;
;;; - calling a G2 procedure;
;;; - allowing a "wait state" before returning.  (The wait state could allow
;;;   another procedure to run that may invalidate the environment.)

;;; By default, the value of this property is nil.  Until we know otherwise, the
;;; function is assumed to be capable of invalidating the environment.

;;; Use this property when writing new system-procedures in G2 to indicate
;;; whether the function called by a G2 system-procedure (i.e., funcalled by the
;;; system-call stack-instruction) can invalidate a procedure environment.

;;; See declare-system-procedure-function which is used to set this property.
;;; Also, see procedure-environment-always-valid-p for more information on
;;; keeping environments valid.

(def-global-property-name function-keeps-procedure-environment-valid?)

;; Note that this property is located in this module to be ahead of any function
;; directly called by a G2 system procedure.  - cpm, 5/27/95






;;;; System-Procedure Declaration




;;; The variable `system-call-function-list' is used in #+development to hold
;;; the names of the lisp-functions called by system-procedures (i.e., called by
;;; system-call instruction).

;;; This list is added to only when the system-procedure are compiled.

#+development
(defvar system-call-function-list nil)
;see also funcallable-symbol-argument-table and funcallable-symbol-result-table

#+development
(defvar compiled-system-call-function-list nil) ;for finding system procedures without caps

#+development
(defun show-non-compiled-system-procedures (&optional (show-compiled-p nil))
  (loop for sc in (sort (copy-list system-call-function-list) #'string<)
	for compiled? = (not (null (memq sc compiled-system-call-function-list)))
	for arguments = (gethash sc funcallable-symbol-argument-table 'not-declared)
	for results = (gethash sc funcallable-symbol-result-table 'not-declared)
	when (eq compiled? (not (null show-compiled-p)))
	  do (format t "~&~(~:S ~:S ~:S~)~%" sc arguments results)))

#+development
(defvar system-call-function-list-local-vars-always-valid nil)

#+development
(defvar system-call-function-list-local-vars-not-always-valid nil)




;;; The macro `declare-system-procedure-function' is used to specify the Lisp
;;; function called by a G2 system-procedure.  The first argument is the name of
;;; the Lisp function.  The second argument indicates whether it is possible for
;;; the Lisp function to invalidate the local-variable environment of the
;;; system-procedure or the caller to the system-procedure.  Note that if this
;;; second argument is T, the Lisp function must guarantee that it does not
;;; invalidate the environment!

;;; The invalidation can happen if the Lisp function causes an item deletion,
;;; deactivation, or transfer; calls a G2 procedure; or allows a "wait state".

;;; See the function-keeps-procedure-environment-valid? property for more
;;; information about invalidating environments.  See the the system-call
;;; stack-instruction regarding an optimization that is made for
;;; system-procedures that never invalidate the calling procedure environment
;;; (i.e., when the second to declare-system-procedure-function is T).

(defmacro declare-system-procedure-function
    (unquoted-lisp-function-name keeps-g2-local-variables-valid? &optional
				 (arguments 'not-supplied) (results 'not-supplied))
  (let ((local-var-flag? (gensym)))
    `(eval-when (:compile-toplevel :load-toplevel :execute)
       (let ((,local-var-flag? ,keeps-g2-local-variables-valid?))
	 (progn
	   (declare-funcallable-symbol ,unquoted-lisp-function-name ,arguments ,results)
	   (setf (function-keeps-procedure-environment-valid?
		   ',unquoted-lisp-function-name)
		 ,local-var-flag?)
	   #+development
	   (progn
	     (pushnew ',unquoted-lisp-function-name system-call-function-list)
	     (if ,local-var-flag?
		 (pushnew
		   ',unquoted-lisp-function-name
		   system-call-function-list-local-vars-always-valid)
		 (pushnew
		   ',unquoted-lisp-function-name
		   system-call-function-list-local-vars-not-always-valid)))
	   nil)))))

;; Note that every system-procedure must be declared using the macro
;; declare-system-procedure-function or the various versions of
;; defun-*for-system-procedure*, which either has argument or declarations which
;; indicates whether any procedure environment may be invalidated.  - cpm,
;; 5/27/95






;;;; System-Procedure Definition




;;; `Defun-for-system-procedure' is analagous to defun, but it is used
;;; to implement those functions that may have a corresponding G2 system
;;; procedure.  These are implemented in the G2 procedure language using the
;;; "system call" syntax, and the system-call instruction.  These can be
;;; compiled only in a development system, i.e. at Gensym.

;;; If the arglist is a list of (argument-name argument-type), and if the
;;; first line of the body is a return values declaration of the form
;;;   (declare (values type-1 ... type-n))
;;; then this macro expands like `defun-for-system-procedure+', and takes
;;; care of all of your boxing and unboxing needs.

;;; Note also that this macro can contain:
;;;   (declare ... (keeps-g2-local-variables-valid <T-or-NIL>))
;;;
;;; IMPORTANT: If this declaration is T, then a important runtime optimization
;;; can be made on this system-procedures.  See documentation below.

;;; There are strict rules about system procedures.  All their arguments
;;; and return values must be of legal evaluation types.  They must return
;;; as many or more values than their callers expect.

;;; This macro will assure they are declared funcallable (see
;;; declare-funcallable-symbol) and that they are allowed to unwind
;;; (see defun-allowing-unwind).

;; This should be used for all system procedure entry points.  So we
;; could enumerate them and reengineer them, but that isn't currently
;; the case.



;;; `Defun-for-system-procedure+' and
;;; `defun-allowing-unwind-for-system-procedure+' are extensions of
;;; defun-for-system-procedure.  Requires that you declare the type of all
;;; inputs and outputs.  In exchange it will unbox all the inputs, box all the
;;; results, it will reclaim all the inputs, and create bindings for named
;;; variables in the list of values, and return them at the end.
;;;
;;; Note that all types should be declared using their internal names (e.g.,
;;; integer, text, number, float, datum, etc.) as opposed to their user-visible
;;; names (e.g., integer, text, quantity, float, value).
;;;

;;; This macro also has a KEEPS-G2-LOCAL-VARIABLES-VALID argument which should
;;; be T or NIL.  This indicates whether the sys-proc Lisp function keeps the
;;; local-variable environment of the system-procedure and any other procedure
;;; valid.  If this argument is T, an important runtime optimization can be
;;; made.  See declare-system-procedure-function for more information.

;;; An example:
;;;
;;;  (defun-for-system-procedure+ my-system-procedure-sum
;;;           ((x integer) (y integer))
;;;           ((sum integer) (zero integer 0))
;;;    T                 ; keeps-g2-local-variables-valid? FLAG
;;;    (setq sum (+f x y)))
;;;
;;; expands into
;;;
;;;   (progn
;;;     (declare-system-procedure-function my-system-procedure-sum T)
;;;     (defun my-system-procedure-sum
;;;         (x-as-evaluation-value y-as-evaluation-value)
;;;       (let* ((x (evaluation-integer-value x-as-evaluation-value))
;;;              (y (evaluation-integer-value y-as-evaluation-value))
;;;              (sum nil) (zero 0))
;;;         (setq sum (+f x y))
;;;         (reclaim-evaluation-integer x-as-evaluation-value)
;;;         (reclaim-evaluation-integer y-as-evaluation-value)
;;;         (values (make-evaluation-integer sum)
;;;                 (make-evaluation-integer zero)))))

(defun-for-macro expand-defun-for-system-procedure+
    (defun-kind name args results keeps-g2-local-variables-valid? body)
  (let ((arglist args))
    ;; If this is true, then massage the body and arglist.
    (when (or (and args (every #'consp args)) results)
      (loop with type-reclaimer-assocation = '(integer reclaim-evaluation-integer
					       symbol reclaim-evaluation-symbol
					       text  reclaim-evaluation-text
					       truth-value  reclaim-evaluation-truth-value
					       float  reclaim-evaluation-float
					       ;; NOTE: number => quantity, &
					       ;; added value, here and below.
					       ;; (MHD 12/19/94) -- type names
					       ;; returned to their internal
					       ;; names (number, datum vs.
					       ;; quantity, value) per JRA's
					       ;; wish. (MHD 12/21/94)
					       number  reclaim-evaluation-quantity
					       datum  reclaim-evaluation-value
					       item  identity
					       sequence identity
					       ;; structure: create it yourself
					       ;; using allocate-evaluation-structure
					       structure identity)
	    with type-maker-assocation = '(integer  make-evaluation-integer
					   symbol make-evaluation-symbol
					   text make-evaluation-text
					   truth-value make-evaluation-truth-value
					   float make-evaluation-float
					   number make-evaluation-quantity
					   datum make-evaluation-value-based-on-type
					   item identity
					   sequence identity
					   structure identity)
	    with type-unboxer-assocation = '(integer evaluation-integer-value
					     symbol evaluation-symbol-symbol  ;; Humm.
					     text evaluation-text-value
					     truth-value evaluation-truth-value-value
					     float evaluation-float-value
					     number evaluation-quantity-value
					     datum evaluation-value-value
					     item identity
					     sequence identity
					     structure identity)
	    for (arg-name arg-type) in args
	    as boxed-arg-name = (intern (format nil "~S-AS-EVALUATION-VALUE" arg-name))
	    as type-unboxer = (getf type-unboxer-assocation arg-type)
	    as type-reclaimer = (getf type-reclaimer-assocation arg-type)
	    unless (and type-unboxer type-reclaimer)
	      do (error "Unknown argument-type: ~s" arg-type)
	    collect boxed-arg-name into lambda-list
	    collect `(,arg-name (,type-unboxer ,boxed-arg-name)) into unboxed-args
	    collect `(,type-reclaimer ,boxed-arg-name) into reclaim-parameters
	    finally
	      (loop for (result-name result-type result-default) in results
		    as type-maker = (getf type-maker-assocation result-type)
		    unless type-maker
		      do (error "Unknown result-type: ~s" result-type)
		    collect `(,result-name ,result-default) into results
		    collect `(,type-maker ,result-name) into box-results
		    finally
		      (setq arglist lambda-list
			    body `((let* (,@unboxed-args ,@results)
				     ,@body
				     ,@reclaim-parameters
				     (values ,@box-results)))))))
    `(progn
       (declare-system-procedure-function
	 ,name ,keeps-g2-local-variables-valid? ,args ,results)
       (,defun-kind ,name ,arglist
	 ,@body))))

;; Added truth-value, float, and number as known types.  Ben consulted.  (MHD
;; 8/29/94)

;; This ought to insert typechecks on the arguments, at least in development.



;;; The defun-for-macro `expand-defun-for-system-procedure' grovels around for a
;;; VALUES declaration.  If it finds one, then we translate it into the results
;;; list for `expand-defun-for-system-procedure+'.

;;; This macro also checks for any KEEPS-G2-LOCAL-VARIABLES-VALID declaration.
;;; This indicates whether the sys-proc Lisp function keeps the local-variable
;;; environment of the system-procedure and any other procedure valid.  If this
;;; argument is T, an important runtime optimization can be made.  See
;;; declare-system-procedure-function for more information.

(defun-for-macro expand-defun-for-system-procedure
    (defun-kind name arglist body)
  (assert (or (every #'consp arglist)
 	      (notany #'consp arglist))
 	  (arglist)
 	  "Not all arguments to ~a have their types declared.  You probably ~%~
                made a mistake as no unboxing or reclaiming will occur for any ~%~
                arguments.  You should either specify all the types or none of~%~
                them."
 	  name)
  (let* ((declaration? (car body))
	 (value-types-declaration?
	   (and (consp declaration?)
		(eq (first declaration?) 'declare)
		(cdr-of-cons declaration?)
		(assq 'values (cdr-of-cons declaration?))))
	 (value-types
	   (and value-types-declaration?
		(consp value-types-declaration?)
		(cdr-of-cons value-types-declaration?)))
	 (results (loop for value-type in value-types
			for i from 1
			for value-name = (build-ab-symbol 'value i)
			collect (list value-name value-type)))
	 ;; The following allows declarations of the form:
	 ;; (declare ... (keeps-g2-local-variables-valid t)).  - cpm, 5/29/95
	 (valid-environment-declaration?
	   (and (consp declaration?)
		(eq (first declaration?) 'declare)
		(cdr-of-cons declaration?)
		(assq
		  'keeps-g2-local-variables-valid (cdr-of-cons declaration?))))
	 (keeps-g2-local-vars-valid?
	   (when valid-environment-declaration?
	     (second valid-environment-declaration?)))
	 )
    (when (and (listp declaration?)
	       (eq (first declaration?) 'declare))
      (pop body))
    (when results
      (setq body `((multiple-value-setq ,(loop for (name) in results collect name)
		     (progn ,@body)))))
    (expand-defun-for-system-procedure+
      defun-kind name arglist results keeps-g2-local-vars-valid? body)))



;;; The macro `defun-for-system-procedure' defines a system procedure.

(defmacro defun-for-system-procedure (name arglist &rest body)
  (expand-defun-for-system-procedure 'defun name arglist body))

(defmacro defun-allowing-unwind-for-system-procedure (name arglist &rest body)
  (expand-defun-for-system-procedure 'defun-allowing-unwind name arglist body))


(defmacro defun-for-system-procedure+
    (name args results keeps-g2-local-variables-valid? &body body)
  (expand-defun-for-system-procedure+
    'defun name args results keeps-g2-local-variables-valid? body))

(defmacro defun-allowing-unwind-for-system-procedure+
    (name args results keeps-g2-local-variables-valid? &body body)
  (expand-defun-for-system-procedure+
    'defun-allowing-unwind
    name args results keeps-g2-local-variables-valid? body))






(defvar in-edit-warning-context-p nil)
(defvar items-warned-in-edit-warning-context nil)

(defmacro with-edit-warning-context (args &body forms)
  (declare (ignore args))
  `(let ((in-edit-warning-context-p t)
	 (items-warned-in-edit-warning-context nil))
     (prog1 (progn ,@forms)
       (reclaim-gensym-list items-warned-in-edit-warning-context))))




;;;; Frame Serial Numbers


;;; A `Frame-serial-number' is a fixnum placed into each frame as it is
;;; created.  Newer frames have larger values. No two frames (in the
;;; same KB) have the same serial number.

;;; When a frame is reclaimed the frame serial number is set to a unique
;;; value.  This can be used to detect a reclaimed frame.

;;; Notice that a recycled frame will have a bigger frame serial number than it
;;; did in it's previous encarnation.  By storing the
;;; `current-frame-serial-number' a data structure can detect if any of a number
;;; of frame's it includes have been reclaimed, or recycled.

;;; The primary interface here in is: frame-has-not-been-reprocessed-p,
;;; frame-has-been-reprocessed-p and current-frame-serial-number.

;;; Frame serial numbers have many customers, all micro scheduled tasks use
;;; frame serial numbers to guard their continuation state against reclaiming.
;;; KB same and load is something of a trickster with these.

;;; Frame serial numbers less than 2^29 are represented as fixnums.
;;; Frame serial numbers greater than 2^29 are represented as a pair
;;; (of type frame-serial-number) of two fixnums. This means that
;;; Frame serial numbers must be copied and reclaimed as appropriate with
;;; copy-frame-serial-number and reclaim-frame-serial-number, and
;;; compared only with frame-serial-number-equal, frame-serial-number-<=,
;;; and friends. -alatto, 4/22/99

(def-concept frame-serial-number)



;;; A `reference-serial-number' is a frame-serial-number stored in some data
;;; structure to allow the code to guard against accessing a frame that has been
;;; recycled.  It is not necessarily the frame serial number of any frame.

(def-concept reference-serial-number)




(def-system-variable *current-frame-serial-number*
    utilities4
  (:funcall frame-serial-number-0))

#+one-word-serial-numbers
(def-system-variable *frame-serial-number-overflow-count*
    frames3
  0)





;;; `Current-frame-serial-number' is the latest frame-serial-number to be
;;; issued.  Frame-serial-numbers are a unique seuqential numbering of frames as
;;; they are issued.  It is set to -1 for a reclaimed and not yet reissued
;;; frame.  Frame-serial-number is used for hashing, and for verifying that a
;;; frame has not been reclaimed (and possibly re-issued) since a reference to
;;; *current-frame-serial-number* has been noted.

;;; The problem of bignum generation after many frames have been issued needs to
;;; be addressed.

(defmacro current-frame-serial-number ()
  '*current-frame-serial-number*)

(defun current-frame-serial-number-function ()
  *current-frame-serial-number*)

(defun copy-of-current-frame-serial-number-function ()
  (copy-frame-serial-number (current-frame-serial-number)))

;;; These are stubs, which will get changed when we implement 2-word frame serial numbers.
;;; Most of these may turn into macros later.

#+one-word-serial-numbers
(progn

(defun increment-current-frame-serial-number ()
  (when (=f *current-frame-serial-number* most-positive-fixnum)
    (incff *frame-serial-number-overflow-count*))
  (incff *current-frame-serial-number*))

(defun copy-frame-serial-number (x) x)

(defun frame-serial-number-< (x y) (<f x y))
(defun frame-serial-number-> (x y) (>f x y))
(defun frame-serial-number-<= (x y) (<=f x y))
(defun frame-serial-number->= (x y) (>=f x y))
(defun frame-serial-number-equal (x y) (=f x y))
(defun frame-serial-number-<-function (x y) (<f x y))
(defun frame-serial-number->-function (x y) (>f x y))
(defun frame-serial-number-<=-function (x y) (<=f x y))
(defun frame-serial-number->=-function (x y) (>=f x y))
(defun frame-serial-number-equal-function (x y) (=f x y))
(defun reclaim-frame-serial-number (x) (declare (ignore x)) nil)
(defmacro frame-serial-number-setf (place fsn)
  (if (and (eq place '*current-frame-serial-number*)
	   (equal fsn '(frame-serial-number-0)))
      `(progn
	 (setf *frame-serial-number-overflow-count* 0)
	 (setf ,place ,fsn))
      `(setf ,place ,fsn)))
(defun frame-serial-number-0 () 0)
(defmacro frame-serial-number-recycled () -1)
(defun frame-serial-number-recycled-function () -1)
(defun frame-serial-number-hash (fsn) fsn)
(defun frame-serial-number-hash-function (fsn) fsn)

(defun g2-instance-creation-count-as-float ()
  (+e (coerce-to-gensym-float *current-frame-serial-number*)
      (*e (coerce-to-gensym-float *frame-serial-number-overflow-count*)
	  ;; 2.0 because the wrap around is from
	  ;; most-positive-fixnum to most-negative-fixnum
	  #.(*e 2.0 (+e 1.0 most-positive-fixnum-as-float)))))

;;; will return t erroneously sometimes, but it's only used in old bug-detection code, so that's OK.

(defmacro frame-serial-number-p (thing)
  `(fixnump ,thing))

) ; progn (#+one-word-serial-numbers)

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :use-a-structure-for-frame-serial-numbers *features*))

#-one-word-serial-numbers
(progn

(defconser frame-serial)

#-use-a-structure-for-frame-serial-numbers
(progn
;; NOTE: this is the actual version used in final product.
(defmacro compound-frame-serial-number-p (cfsn)
  `(consp ,cfsn))

(defmacro compound-frame-serial-number-most-significant-part (cfsn)
  `(car-of-cons ,cfsn))

(defmacro compound-frame-serial-number-least-significant-part (cfsn)
  `(cdr-of-cons ,cfsn))

(defmacro make-compound-frame-serial-number (msp lsp)
  `(frame-serial-cons ,msp ,lsp))

(defmacro reclaim-compound-frame-serial-number (cfsn)
  `(reclaim-frame-serial-cons ,cfsn))
)

#+use-a-structure-for-frame-serial-numbers
(def-structure (compound-frame-serial-number
		 (:constructor make-compound-frame-serial-number
			       (compound-frame-serial-number-most-significant-part
				compound-frame-serial-number-least-significant-part))
		 #+development
		 (:print-function print-compound-frame-serial-number))
  compound-frame-serial-number-most-significant-part
  compound-frame-serial-number-least-significant-part
  (compound-frame-serial-number-owned-by-frame-p nil))

#+development
(defun print-compound-frame-serial-number (cfsn stream depth)
  (declare (ignore depth))
  (printing-random-object (cfsn stream)
    (format stream "fsn ~D ~D"
	    (compound-frame-serial-number-most-significant-part cfsn)
	    (compound-frame-serial-number-least-significant-part cfsn))))

(defmacro with-frame-serial-number-debugging (options &body body)
  (declare (ignore options)) ; for indenting purposes only
  #+development
  `(progn ,@body)
  #-development
  (progn body nil))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter max-fixnum-frame-serial-number
    ;; change this to some small number to test frame serial numbers
    #+development most-positive-fixnum ; old: 12
    #-development most-positive-fixnum))

(defun-simple increment-current-frame-serial-number ()
  (let ((current *current-frame-serial-number*))
    (if (fixnump current)
	(setq *current-frame-serial-number*
	      (if (=f current max-fixnum-frame-serial-number)
		  (make-compound-frame-serial-number 1 0)
		  (1+f current)))
	(progn
	  (if (=f (compound-frame-serial-number-least-significant-part current)
		  max-fixnum-frame-serial-number)
	      (progn
		(incff (compound-frame-serial-number-most-significant-part current))
		(setf (compound-frame-serial-number-least-significant-part current) 0))
	      (incff (compound-frame-serial-number-least-significant-part current)))
	  current))))

(defun-simple copy-frame-serial-number (x)
  (if (or (fixnump x) (null x))
      x
      (let ((msp (compound-frame-serial-number-most-significant-part x))
	    (lsp (compound-frame-serial-number-least-significant-part x)))
	(with-frame-serial-number-debugging ()
	  (unless (and (fixnump msp) (fixnump lsp))
	    (error "Invalid frame serial number ~S" x)))
	(make-compound-frame-serial-number msp lsp))))

(defun-substitution-macro frame-serial-number-< (x y)
  (if (fixnump x)
      (if (fixnump y)
	  (<f x y)
	  t)
      (if (fixnump y)
	  nil
	  (let ((xa (compound-frame-serial-number-most-significant-part x))
		(ya (compound-frame-serial-number-most-significant-part y)))
	    (or (<f xa ya)
		(and (=f xa ya)
		     (<f (compound-frame-serial-number-least-significant-part x)
			 (compound-frame-serial-number-least-significant-part y))))))))

(def-substitution-macro frame-serial-number-> (x y)
  (frame-serial-number-< y x))

(defun-substitution-macro frame-serial-number-<= (x y)
  (if (fixnump x)
      (if (fixnump y)
	  (<=f x y)
	  t)
      (if (fixnump y)
	  nil
	  (let ((xa (compound-frame-serial-number-most-significant-part x))
		(ya (compound-frame-serial-number-most-significant-part y)))
	    (or (<f xa ya)
		(and (=f xa ya)
		     (<=f (compound-frame-serial-number-least-significant-part x)
			  (compound-frame-serial-number-least-significant-part y))))))))

(def-substitution-macro frame-serial-number->= (x y)
  (frame-serial-number-<= y x))

(defmacro frame-serial-number-equal (x y)
  (let ((x-expand (macroexpand x))
	(y-expand (macroexpand y)))
    (if (fixnump x-expand)
      (if (fixnump y-expand)
	(=f x-expand y-expand)
	(let ((y-var (gensym)))
	  `(let ((,y-var ,y))
	     (if (fixnump ,y-var)
	       (=f ,x ,y-var)
	       nil))))
      (if (fixnump y-expand)
	(let ((x-var (gensym)))
	  `(let ((,x-var ,x))
	     (if (fixnump ,x-var)
	       (=f ,x-var ,y)
	       nil)))
	(let ((x-var (gensym))
	      (y-var (gensym)))
	  `(let ((,x-var ,x)
		 (,y-var ,y))
	     (if (fixnump ,x-var)
	       (if (fixnump ,y-var)
		 (=f ,x-var ,y-var)
		 nil)
	       (if (fixnump ,y-var)
		 nil
		 (and (=f (compound-frame-serial-number-most-significant-part ,x-var)
			  (compound-frame-serial-number-most-significant-part ,y-var))
		      (=f (compound-frame-serial-number-least-significant-part ,x-var)
			  (compound-frame-serial-number-least-significant-part ,y-var)))))))))))
#+development
(defun frame-serial-number-equal-for-development (x y)
  (frame-serial-number-equal x y))

(defun-simple frame-serial-number-<=-function (x y) (frame-serial-number-<= x y))
(defun-simple frame-serial-number->=-function (x y) (frame-serial-number->= x y))
(defun-simple frame-serial-number-<-function (x y) (frame-serial-number-< x y))
(defun-simple frame-serial-number->-function (x y) (frame-serial-number-> x y))
(defun-simple frame-serial-number-equal-function (x y) (frame-serial-number-equal x y))

(defvar-of-special-global reclaimed-frame-serial-number-marker
  (make-symbol "reclaimed-frame-serial-number-marker"))

(def-substitution-macro frame-serial-number-reclaimed-p (x)
  (or (fixnump x) (null x) (eq x no-saved-initial-value)
      (not (and (fixnump (compound-frame-serial-number-most-significant-part x))
                (fixnump (compound-frame-serial-number-least-significant-part x))))))

(defun-void reclaim-frame-serial-number (x)
  (unless (or (fixnump x) (null x) (eq x no-saved-initial-value))
    (with-frame-serial-number-debugging ()
      (unless (and (fixnump (compound-frame-serial-number-most-significant-part x))
		   (fixnump (compound-frame-serial-number-least-significant-part x)))
	(error "Already reclaimed frame-serial-number"))
      #+use-a-structure-for-frame-serial-numbers
      (when (compound-frame-serial-number-owned-by-frame-p x)
	(cerror "Continue" "Reclaiming a frame serial number that is still in use"))
      (setf (compound-frame-serial-number-most-significant-part x)
	    reclaimed-frame-serial-number-marker)
      (setf (compound-frame-serial-number-least-significant-part x)
	    reclaimed-frame-serial-number-marker))
    ;; If there are problems with frame serial numbers being reclaimed
    ;; and reused prematurely, uncomment this line; The GC will reclaim
    ;; the FSN, but the leak detection tools won't be usable on
    ;; frame-serial-number-cons. -alatto, 6/28/06
    #-debugging-frame-serial-double-reclaims
    (reclaim-compound-frame-serial-number x)))

(defun-simple frame-serial-number-setf-helper-1 (old new)
  (if (or (null old)
	  (fixnump old)
	  (eq old no-saved-initial-value))
      (copy-frame-serial-number new)
      (if (or (null new)
	      (fixnump new))
	  (progn
	    (reclaim-frame-serial-number old)
	    new)
	  (let ((new-msp (compound-frame-serial-number-most-significant-part new))
		(new-lsp (compound-frame-serial-number-least-significant-part new))
		(old-msp (compound-frame-serial-number-most-significant-part old))
		(old-lsp (compound-frame-serial-number-least-significant-part old)))
	    (declare (ignorable old-msp old-lsp))
	    (with-frame-serial-number-debugging ()
	      (unless (and (fixnump new-msp) (fixnump new-lsp))
		(error "bad frame serial number ~S" new))
	      (unless (and (fixnump old-msp) (fixnump old-lsp))
		(error "bad old frame serial number ~S" old)))
	    (setf (compound-frame-serial-number-most-significant-part old) new-msp)
	    (setf (compound-frame-serial-number-least-significant-part old) new-lsp)
	    old))))

(defun-substitution-macro frame-serial-number-setf-helper (old new)
  (if (and (or (fixnump old) (null old))
	   (or (fixnump new) (null new)))
      new
      (frame-serial-number-setf-helper-1 old new)))

(define-modify-macro frame-serial-number-setf (fsn)
		     frame-serial-number-setf-helper)

(defun-simple frame-serial-number-0 ()
  #+use-a-structure-for-frame-serial-numbers
  (make-compound-frame-serial-number 0 0)
  #-use-a-structure-for-frame-serial-numbers
  0)

(defmacro frame-serial-number-recycled ()
  #+use-a-structure-for-frame-serial-numbers
  #.#(nil -1 -1 nil)
  #-use-a-structure-for-frame-serial-numbers
  -1)

(defun-simple frame-serial-number-recycled-function ()
  (frame-serial-number-recycled))

(defmacro frame-serial-number-hash (fsn)
  `(let ((fsn ,fsn))
     (if (fixnump fsn)
	 fsn
	 (logxorf (compound-frame-serial-number-most-significant-part fsn)
		  (compound-frame-serial-number-least-significant-part fsn)))))

(defun-simple frame-serial-number-hash-function (fsn)
  (frame-serial-number-hash fsn))

(defun g2-instance-creation-count-as-float ()
  (let ((fsn *current-frame-serial-number*))
    (if (fixnump fsn)
	(coerce-to-gensym-float fsn)
	(+e (coerce-to-gensym-float (compound-frame-serial-number-least-significant-part fsn))
	    (*e (coerce-to-gensym-float (compound-frame-serial-number-most-significant-part fsn))
		(+e 1.0 (coerce-to-gensym-float max-fixnum-frame-serial-number)))))))

;;; will return t erroneously sometimes, but it's only used in
;;; the development only function find-bugs-in-post-object-menu, so that's OK.

(defmacro frame-serial-number-p (thing)
  `(let ((thing ,thing))
     (or (fixnump thing)
	 (and (compound-frame-serial-number-p thing)
	      (fixnump (compound-frame-serial-number-most-significant-part thing))
	      (fixnump (compound-frame-serial-number-least-significant-part thing))))))

) ; progn (#-one-word-serial-numbers)

(defun reset-current-frame-serial-number ()
  (frame-serial-number-setf *current-frame-serial-number* (frame-serial-number-0)))

(setq *current-frame-serial-number* nil)
(reset-current-frame-serial-number)





;;; (kb-frames-have-not-been-deleted-p reference-frame-serial-number) is
;;; true if it can be guaranteed that no kb-frames have been deleted
;;; since reference-frame-serial-number was the value of
;;; (current-frame-serial-number). This is accomplished by placing the
;;; value of (current-frame-serial-number) in
;;; current-serial-number-at-last-delete each time a kb-frame has been
;;; deleted. If (current-frame-serial-number) at the time of this test
;;; is greater than that, then no deletes have occurred since the
;;; reference-frame-serial-number was recorded.

;;; If a situation occurs in which the last kb-frame delete happened
;;; after the last frame had been issued, and neither of these has
;;; happened for some time, we would want the test to succeed, but it
;;; would not because (current-frame-serial-number) and
;;; current-frame-serial-number-at-last-delete would remain equal
;;; indefinitely. To overcome this, (current-frame-serial-number) must
;;; be incremented occasionally. This is done in
;;; take-actions-at-start-of-clock-tick, every 10 clock ticks.

;;; Where the frame life cycle is quite active, this test will not
;;; accomplish very much.

;(def-system-variable current-frame-serial-number-at-last-delete frames3 0)

;(defmacro kb-frames-have-not-been-deleted-p (reference-frame-serial-number)
;  `(>f ,reference-frame-serial-number current-frame-serial-number-at-last-delete))

;; The kb-frames-have-not-been-deleted-p predicate is not being used anywhere in
;; the system, and so I am removing it for now.  I have also commented out the
;; incrementing of the current-frame-serial-number whic was happening in
;; take-actions-at-start-of-clock-tick.  If you want this predicate back in the
;; system, you must comment in the increment in the file CYCLES.  Before you do
;; so, please talk to me about it.  I'm not comfortable at all with a facility
;; which requires us to increment a counter in a way which might cause it to
;; overflow in a system with lots of transient objects.  -jra 8/12/88






;;;; Byte Code Body




;;; The structure byte-code-body is used to hold byte-code-vectors which
;;; represent the compilations of user defined code.  These structures have all
;;; the properties of slot-values, in that they can be saved and read from
;;; files, reclaimed with reclaim-slot-value, and copied with
;;; copy-for-slot-value.  The one significant difference is that within
;;; constant vectors, frames get copied and written to kbs as NIL.  These
;;; frames are caches that apply only to the original holder of a byte code
;;; body.

;;; There are five slots:

;;;   byte-code-body-length:  containing the count of bytes in the byte-vector
;;;   (Note the the actual size of the byte-vector will be rounded up somewhat
;;;   from this size, at least by a multiple of four.  See allocate-byte-vector
;;;   for details.);

;;;   byte-code-body-byte-vector:  containing the byte-vector for the code;

;;;   byte-code-body-constant-vector: a simple vector (from the
;;;   managed-simple-vector pool) containing slot values which are code
;;;   constants for this byte-code-body and frames which are cached item
;;;   references;  may also contain an annotation-lookup-structure in the last
;;;   position.

;;;   byte-code-body-environment-description:  a slot value which describes the
;;;   names of local variables used by the byte-code-body; and

;;;   byte-code-body-free-references: a simple vector (from the
;;;   managed-simple-vector pool) containing slot values which are
;;;   declarations of needed characteristics of other items within the
;;;   knowledge base.

(def-structure (byte-code-body
		 (:constructor
		   make-byte-code-body
		   (byte-code-body-length
		     byte-code-body-byte-vector
		     byte-code-body-constant-vector
		     byte-code-body-environment-description
		     byte-code-body-free-references)))
  byte-code-body-length
  (byte-code-body-byte-vector nil :reclaimer reclaim-byte-vector)
  (byte-code-body-constant-vector
    nil :reclaimer reclaim-if-simple-vector-of-slot-values)
  (byte-code-body-environment-description nil :reclaimer reclaim-slot-value)
  (byte-code-body-activity-description nil :reclaimer reclaim-slot-value)
  (byte-code-body-text-position-description nil :reclaimer reclaim-slot-value)
  (byte-code-body-free-references
    nil :reclaimer reclaim-if-simple-vector-of-slot-values)
  (byte-cody-body-compiled-function nil)
  (byte-code-body-native-code nil))

(defun reclaim-if-simple-vector-of-slot-values (simple-vector?)
  (when simple-vector?
    (reclaim-simple-vector-of-slot-values simple-vector?)))

(defun reclaim-simple-vector-of-slot-values (simple-vector)
  (loop for index from 0 below (length-of-simple-vector simple-vector)
	for value = (svref simple-vector index)
	do
    (unless (or (fixnump value) (symbolp value))	; Optimization
      (reclaim-slot-value value)))
  (reclaim-managed-simple-vector simple-vector)
  nil)

(defun-simple copy-if-byte-code-subvector (simple-vector?)
  (if simple-vector?
      (let* ((vector-length (length-of-simple-vector simple-vector?))
	     (new-vector (allocate-managed-simple-vector vector-length)))
	(loop for constant-index fixnum from 0 below vector-length
	      for value = (svref simple-vector? constant-index) do
	  (cond ((or (fixnump value) (symbolp value))
		 (setf (svref new-vector constant-index) value))
		((thing-is-item-p value)
		 (setf (svref new-vector constant-index) nil))
		(t
		 (setf (svref new-vector constant-index)
		       (copy-for-slot-value value)))))
	new-vector)
      nil))




;;; The function `copy-byte-code-body' takes a byte code body and returns a
;;; copy of that byte code body, containing copies of its components.  Note
;;; that any items stored within the vectors will be not copied, but will have
;;; NIL in their place.  Items in the constant vector are cached items will be
;;; reinstalled in the new copy when it is analyzed for consistency.

(defun-simple copy-byte-code-body (byte-code-body)
  (let* ((byte-vector-length (byte-code-body-length byte-code-body))
	 (old-byte-vector (byte-code-body-byte-vector byte-code-body))
	 (new-byte-vector (allocate-byte-vector byte-vector-length))
	 (new-constant-vector
	   (copy-if-byte-code-subvector
	     (byte-code-body-constant-vector byte-code-body)))
	 (new-environment-description
	   (copy-for-slot-value
	     (byte-code-body-environment-description byte-code-body)))
	 (new-free-reference-vector
	   (copy-if-byte-code-subvector
	     (byte-code-body-free-references byte-code-body))))
    (copy-byte-vector-portion
      old-byte-vector 0 new-byte-vector 0 byte-vector-length)
    (make-byte-code-body
      byte-vector-length
      new-byte-vector
      new-constant-vector
      new-environment-description
      new-free-reference-vector)))


;;; `special-annotation-lookup-structure-marker' is a magic-cookie which will be
;;; stored in the car of the lookup-structure that will live in the constant-vector
;;; of a byte-code-body to indentify it as such.

(defconstant special-annotation-lookup-structure-marker
  (intern "spEcIal annOtatiOn LookuP strUctUrE maRkeR" (find-package "KEYWORD")))

;;; `get-lookup-structure-if-any' is used to extract an annotation
;;; lookup-structure from an item.  It lives in the (n-1)th index of the
;;; constant-vector.  It returns two values: the lookup-structre (or NIL) and
;;; the constant-vector (for ease in cleanup during a text-stripping)

(defun get-lookup-structure-if-any (item)
  ;; fix call to get-byte-code-body-if-any if we start supporting cell-arays and generic-simulation-formulas
  (let* ((byte-code-body? (get-byte-code-body-if-any item nil))
	 (constant-vector? (and byte-code-body?
				(byte-code-body-constant-vector byte-code-body?)))
	 (lookup-structure? (and constant-vector?
				 (svref constant-vector?
					(1-f (length constant-vector?))))))
    (and (consp lookup-structure?)
	 (eq (car-of-cons lookup-structure?)
	     special-annotation-lookup-structure-marker)
	 (values (cdr-of-cons lookup-structure?)
		 constant-vector?))))

(defun-void clean-out-annotation-lookup-structure (item)
  (multiple-value-bind (lookup-structure? constant-vector)
      (get-lookup-structure-if-any item)
    (when lookup-structure?
      (reclaim-slot-value lookup-structure?)
      (setf (svref constant-vector (1-f (length constant-vector)))
	    0))))			;doesn't matter

;;; The following non-destructive, non-consing pure functions are useful because
;;; Common Lisp functions such as intersection do not have these features.


;;; `Duplicates-p' is nil if the list does have have any element eq some other
;;; element.  Otherwise the value is the tail of the list beginning with the
;;; first element which is eq some earlier symbol. This is an O(n^2) algorithm.

(defun duplicates-p (list)
  (loop for element in list
	for rest-of-list = (cdr list) then (cdr rest-of-list)
	thereis (memq element rest-of-list)))




;;; `Intersects-p' is nil if there is no pair of members, one from the first list
;;; and one from the second that are eq.  Otherwise, letting x be the the first
;;; member of the first list to be found in the second list, the value is the
;;; longest tail of the second list to begin with x.  This is an O(n^2)
;;; algorithm.

(defun intersects-p (list1 list2)
  (loop for symbol in list1
	thereis (memq symbol list2)))



;;;; Tree traversal


(defparameter tree-traversal-marker (make-symbol "TREE-TRAVERSAL-MARKER"))

(defconser tree-ordering)

;;; The macro `do-post-order' runs body with node bound to each element of the
;;; tree rooted at root in post-order.  If do-not-copy-list if T, then
;;; inferiors function MUST return a freshly consed gensym list of inferiors.
;;; The list will be recycled.  If the body needs to perform a non-local exit,
;;; then it must be done simply with (return), else we will leak gensym conses.
;;; The body may return one value.

(defmacro do-post-order ((node root inferiors &key (filter 'identity) do-not-copy-list)
			 &body body)
  (avoiding-variable-capture (&aux stack temp infs)
    `(let ((,stack (tree-ordering-list ,root))
	   (,node nil))
       (prog1
	   (loop while ,stack doing
	     (let ((,temp (tree-ordering-pop ,stack)))
	       (setq ,node nil)
	       (cond ((eq ,temp tree-traversal-marker)
		      (setq ,node (tree-ordering-pop ,stack)))
		     ((,filter ,temp)
		      (let ((,infs (,inferiors ,temp)))
			(cond ((null ,infs)
			       (setq ,node ,temp))
			      (t
			       (setq ,stack (nconc (if ,do-not-copy-list
						       ,infs
						       (copy-list-using-tree-ordering-conses ,infs))
						   (tree-ordering-list tree-traversal-marker)
						   (tree-ordering-list ,temp)
						   ,stack)))))))
	       (when ,node
		 ,@body)))
	 (when ,stack
	   (reclaim-tree-ordering-list ,stack))))))



;;; The macro `do-pre-order' is similar for a pre-order traversal.

(defmacro do-pre-order ((node root inferiors &key (filter 'identity) do-not-copy-list)
			&body body)
  (avoiding-variable-capture (&aux stack)
    `(let ((,stack (tree-ordering-list ,root))
	   (,node nil))
       (prog1
	   (loop while ,stack doing
	     (setq ,node (tree-ordering-pop ,stack))
	     (when (,filter ,node)
	       (progn ,@body)
	       (setq ,stack (nconc (if ,do-not-copy-list
				       (,inferiors ,node)
				       (copy-list-using-tree-ordering-conses
					 (,inferiors ,node)))
				   ,stack))))
	 (when ,stack
	   (reclaim-tree-ordering-list ,stack))))))


;;; Some early parts of profiling had to be move here to be available for telestubs

(declare-forward-reference registered-activities-array variable)



;;;; Profiling


;;; a sub-profiling-structure is the structure stored in the called-information
;;; hash table

(def-structure (sub-profiling-structure)
  last-start-time
  (total-sub-calls (allocate-managed-float 0.0)
		   :reclaimer reclaim-managed-float)
  (total-sub-time (allocate-managed-float 0.0)
		   :reclaimer reclaim-managed-float))

;;; The `basic-profiling-structure' holds the profiling information about a
;;; profiliable item. Recorded component timing information goes only
;;; one layer deep. Example: if procedure A calls procedure B which
;;; calls procedure C. The total times spent in A, B and C will be recorded
;;; here but the times for the seperate activities of B and C will not be
;;; recorded. Activities are defined in registered-activities-array
;;; in comp-utils.lisp.
;;; The prime reason for this is the difficulty of effectively tracking
;;; recursive procedures. If the demand is there we may have to solve this
;;; but currently there is no compelling reason to do so. It should be noted
;;; that doing this recursive tracking will increase the run time for
;;; running with profiling enabled, as the calling stack will have to be
;;; examined for each call.

(def-structure (basic-profiling-structure
		(:reclaimer reclaim-basic-profiling-structure-internal)
		(:constructor make-basic-profiling-structure1))
  ;; name of the structure being profiled
;  (profile-name nil)
  (basic-profiling-name nil :reclaimer reclaim-profiling-name)

  ;; the object being profiled
  (basic-profiling-item nil)

  (basic-profiling-serial-number nil :reclaimer reclaim-frame-serial-number)
  ;; total-time  and total calls will be managed floats
  (basic-total-time (allocate-managed-float 0.0)
		    :reclaimer reclaim-managed-float)
  (basic-total-calls  0 :type fixnum)
  ;; array of begin-activity counts
  (profiling-activity-count-array
    (allocate-managed-simple-vector (length registered-activities-array))
    :reclaimer reclaim-managed-simple-vector)
  ;; array of begin-activity times
  (profiling-activity-time-array
    (allocate-managed-float-array (length registered-activities-array))
    :reclaimer reclaim-managed-float-array)
  ;; hash table of called procedures
  #+sub-call-hash-used(called-information (make-sub-call-hash )
		      :reclaimer reclaim-sub-call-hash))


(defun-void reclaim-basic-profiling-structure (bps)
  (when (eq bps current-profile-structure?)
    (setq current-profile-structure? nil))
  (reclaim-basic-profiling-structure-internal bps))

;;; Name is either a symbol or a frame serial number.
(defun reclaim-profiling-name (name)
  (unless (symbolp name)
    (reclaim-frame-serial-number name)))


(def-substitution-macro hash-call-key (key)
  (typecase key
    (symbol
     (sxhash-symbol key))
    (t
     (frame-hash-function key))))

;;; `call-hash' is a hash table designed to record top level function/procedure
;;; calls

(def-hash-table call-hash
    :hash-function-or-macro hash-call-key
    :entry-reclaimer reclaim-basic-profiling-structure)

(defun make-call-hash-function ()
  (make-call-hash))

;;; `sub-call-hash' is a hash table designed to record sub function calls

(def-hash-table sub-call-hash
    :hash-function-or-macro hash-call-key
    :entry-reclaimer reclaim-sub-profiling-structure)


(declare-forward-reference profiling-enabled? variable)

;;; Moved from UTILITIES3 for hidding from GSI. --binghe, 2015/2/11

;;; the structure `global-profiling-structure' contains slots holding global
;;; information about profiling.  it holds slots for total time spent idle,
;;; spent in service-icp-sockets, etc.  it also holds a hash table relating
;;; items to their associated profiling-structure.

(def-structure global-profiling-structure
  (profiling-call-information (make-call-hash-function))
  (start-time-of-last-profile-change
    (allocate-managed-float 0.0)
    :reclaimer reclaim-managed-float)

  ;; how much time was spent idle
  (profiling-idle-time (allocate-managed-float 0.0)
                       :reclaimer reclaim-managed-float)

  ;; how much time spent in take-actions-at-start-of-clock-tick
  ;; this is an approximation, it is actually measures from the
  ;; beginning of the schedule loop to the end of the scheculer-mode
  ;; case switch
  (profiling-clock-tick-time (allocate-managed-float 0.0)
                             :reclaimer reclaim-managed-float)

  ;; time spent redrawing
  (profiling-redraw-time (allocate-managed-float 0.0)
                         :reclaimer reclaim-managed-float)
  ;; time spent service icp tasks
  (profiling-icp-time (allocate-managed-float 0.0)
                      :reclaimer reclaim-managed-float)

  ;; `profiling-gensym-time-of-last-start' set to the current value of
  ;; gensym-time when profiling is turned on
  (profiling-gensym-time-of-last-start
    (allocate-managed-float 0.0)
    :reclaimer reclaim-managed-float)

  ;;  `total-clock-ticks-profiled' should be incremented when profiling is
  ;;  turned off, or the profiling data is sampled to assure that the numbers
  ;;  presented to the user are consistent

  (total-clock-ticks-profiled
    (allocate-managed-float 0.0)
    :reclaimer reclaim-managed-float))


;;;; Misc Junk



;;; `Check-shape-of-window-without-lookahead-for-g2' is really part of the
;;; TELESTUBS module, but it needs to be here as the first customer of
;;; with-temporary-profiling-context, a g2-only facility.

(defun-simple check-shape-of-window-without-lookahead-for-g2
    (gensym-window native-window)
  (let ((work-was-done? nil))
    (with-temporary-profiling-context redraw
      ;; Window reshaping events are handled locally
      (setq work-was-done?
	    (check-shape-of-window-without-lookahead gensym-window native-window)))
    work-was-done?))

;; Called from poll-workstation, which is why it can't be called when
;; on window with drawing.



;;; `Sync-graphics-on-native-window-maybe-with-tracing' called from WINDOWS1
;;; when we know we're in a G2 (AB) system, so it can use the macro
;;; with-temporary-profiling-context, which is undefined for Telewindows.

(defun sync-graphics-on-native-window-maybe-with-tracing (native-window)
  (with-temporary-profiling-context redraw
    (sync-graphics-on-native-window-1 native-window)))



(def-gensym-c-function c-write-exact-float-from-c (:void "g2ext_g_fmt")
  ((:string return-string)
   (:double-float double)))



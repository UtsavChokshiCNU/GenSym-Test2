;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module UNICODE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David


(declare-forward-references
  (intern-gensym-string function)
  (current-system-name variable)
  (skip-spaces-in-string function)
  (read-symbol-from-string function)
  (read-number-from-string function)
  (signal-gsi-maximum-text-string-length-error function)
  (signal-gsi-maximum-gensym-string-length-error function)
  (base-36-digits-string variable)        ; actually defined in this file,
                                        ;   below its first use
  (float-to-text-default-precision-from-system-table function)
  (float-to-text-default-format-from-system-table function)
  
  #+development
  (export-text-string function)
  (gensym-string-to-wide-string function)
  (wide-string-to-gensym-string function)
  (twrite-ascii-from-wide-string function)
  (skip-whitespace-in-string function)
  (intern-wide-string function)
  (intern-wide-string-no-reclaim function)
  (c-write-exact-float-from-c function)
  (managed-float-p-function function)
  (managed-float-value-function function)
  (nanp function)
  (positive-infinity-p function)
  (negative-infinity-p function)
  (coerce-number-to-fixnum function))




;;;; Unicode Characters


;;; A `unicode character' or more simply a `unicode' is represented as a 16 bit
;;; unsigned integer. The numeric value and semantics of all unicodes are
;;; defined by Unicode, Inc.  Unicodes are standardly written (in the
;;; literature) as U+HHHH, where the H's are hex digits.  Legal unicode values
;;; are defined by the Unicode consortium, in league with the ISO 10646
;;; committee.  Note that certain 16-bit unsigned integers are expressly not
;;; (legal) unicodes.  Note in particular that U+FFFF and U+FFFE are not
;;; considered Unicode characters.

;;; The ISO/IEC 10646 character set standard defines a 32-bit character code
;;; space.  A character within this space is a 32-bit unsigned integer, and is
;;; called a `UCS-4 code' or simply `UCS-4', where the 4 indicates that it
;;; requires 4 octets (8-bit bytes) to represent such a code.  The space is
;;; divided into 256 "planes", a code of which is a 16-bit unsigned integer and
;;; is called `ucs-2 code' or `ucs-2', since it requires 2 octets to represent.
;;; The first of this set of planes is called the `Basic Multilingual Plane' (or
;;; `BMP').  The BMP has, by agreement between Unicode and the ISO, been made
;;; equivalent to Unicode (as of Unicode Version 1.1).
;;;

;;; The term "unicode" also refers collectively to a sequence of unicode
;;; characters, i.e., as a mass noun.  E.g., "this emits unicode".

;;; Unicode will serve in 5.0 and beyond as a replacement for the Gensym
;;; Character Set.  Note that the Gensym Character Set, as defined for G2
;;; version 4.0, may be regarded as a subset of Unicode under Han Unification
;;; rules, as well as a few other minor interpretations.  There is a defined
;;; mapping for all Gensym characters (though the "Han Interpretation Mode"
;;; makes it somewhat ambiguous) into Unicode.  This is defined in CHARACTERS.
;;; Note that not all Unicode characters can be mapped into Gensym characters.

(def-concept unicode)





;;;; Unicode Lettercase Operations

;; This facility builds on definitions established in the module LETTERS, q.v.


;;; The function `unicode-uppercase-if-lowercase' returns the uppercase
;;; equivalent of code if it is lowercase in Unicode.  If not, it returns nil.
;;; The function `unicode-lowercase-if-uppercase' works in the opposite
;;; direction.
;;;
;;; The function `unicode-lowercase-p' returns non-nil if code is a lowercase
;;; character in Unicode.  The function `unicode-uppercase-p' works in the
;;; opposite direction.
;;;
;;; The function `unicode-upcase' returns the uppercase equivalent of code if
;;; it's a lowercase letter in Unicode.  If not, it returns the original value
;;; of code.  The function `unicode-downcase' works in the opposite direction.

;;; Note that these are not exported as wide-character operations; they are
;;; operations on unicodes, i.e., integer character codes.  See char-downcasew,
;;; et al, for the wide-character operations.

(defun-simple unicode-uppercase-if-lowercase (code)
  (declare (type fixnum code))
  (map-unicode-case code up))

(defun-simple unicode-lowercase-if-uppercase (code)
  (declare (type fixnum code))
  (map-unicode-case code down))

(defun-substitution-macro unicode-lowercase-p (code)
  (unicode-uppercase-if-lowercase code))

(defun-substitution-macro unicode-uppercase-p (code)
  (unicode-lowercase-if-uppercase code))

(def-substitution-macro unicode-downcase (code)
  (if (<f code 127)                        ; inline/optimize for ASCII
      (if (<=f #.(char-code #\A) code #.(char-code #\Z))
          (+f code #.(-f (char-code #\a) (char-code #\A)))
          code)
      (or (unicode-lowercase-if-uppercase code)
          code)))

(def-substitution-macro unicode-upcase (code)
  (if (<f code 127)                        ; inline/optimize for ASCII
      (if (<=f #.(char-code #\a) code #.(char-code #\z))
          (+f code #.(-f (char-code #\A) (char-code #\a)))
          code)
      (or (unicode-uppercase-if-lowercase code)
          code)))


;; Titlecase needs to be better abstracted, but it's such a nit -- only 4 such
;; characters!: For now: do this by hand for the four characters.  Note that the
;; to-titlecase function should is missing cases like roman numeral one in the
;; 2000..2FFFF range.  To be corrected later, etc.!

;; 01C5;LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON;Lt;0;L;<compat> 0044 017E;;;;N;LATIN LETTER CAPITAL D SMALL Z HACEK;;01C4;01C6;
;; 01C8;LATIN CAPITAL LETTER L WITH SMALL LETTER J;Lt;0;L;<compat> 004C 006A;;;;N;LATIN LETTER CAPITAL L SMALL J;;01C7;01C9;
;; 01CB;LATIN CAPITAL LETTER N WITH SMALL LETTER J;Lt;0;L;<compat> 004E 006A;;;;N;LATIN LETTER CAPITAL N SMALL J;;01CA;01CC;
;; 01F2;LATIN CAPITAL LETTER D WITH SMALL LETTER Z;Lt;0;L;<compat> 0044 007A;;;;N;;;01F1;01F3;

(defun-substitution-macro unicode-titlecase-p (code)
  (or (=f code #x01C5)
      (=f code #x01C8)
      (=f code #x01CB)
      (=f code #x01F2)))

(defun-substitution-macro unicode-titlecase (code)
  (case code
    (#x01C5 #x01C4)
    (#x01C8 #x01C7)
    (#x01CB #x01CA)
    (#x01F2 #x01F1)
    (t (unicode-upcase code))))





;;;; Unicode Digitology



(defun-substitution-macro unicode-digit-p (unicode)
  (or (<=f #x0030 unicode #x0039)
      ;; ASCII/ISO-LATIN-1 digits ('0' through '9')
      (<=f #x0660 unicode #x0669)
      ;; Arabic-Indic digits
      (<=f #x06F0 unicode #x06F9)
      ;; Extended Arabic-Indic digits
      (<=f #x0966 unicode #x096F)
      ;; Devanagari digits
      (<=f #x09E6 unicode #x09EF)
      ;; Bengali digits
      (<=f #x0A66 unicode #x0A6F)
      ;; Gurmukhi digits
      (<=f #x0AE6 unicode #x0AEF)
      ;; Gujarati digits
      (<=f #x0B66 unicode #x0B6F)
      ;; Oriya digits
      (<=f #x0BE7 unicode #x0BEF)
      ;; Tamil digits
      (<=f #x0C66 unicode #x0C6F)
      ;; Telugu digits
      (<=f #x0CE6 unicode #x0CEF)
      ;; Kannada digits
      (<=f #x0D66 unicode #x0D6F)
      ;; Malayalam digits
      (<=f #x0E50 unicode #x0E59)
      ;; Thai digits
      (<=f #x0ED0 unicode #x0ED9)
      ;; Lao digits
      (<=f #xFF10 unicode #xFF19)
      ;; Fullwidth digits
      ))

(defun-substitution-macro g2-readable-unicode-digit-p (unicode)
  (<=f #x0030 unicode #x0039))


(defun-substitution-macro g2-readable-unicode-digit-in-radix (unicode radix)
  (digit-char-pw-function
    (code-wide-character unicode)
    radix))

;; Optimize later!













;;;; Wide Strings



;;; A `wide string' is a data abstraction for a sequence of wide characters.
;;; The following code implements the (unexported) subprimitives and the most
;;; basic of the (exported) primitives of a wide string.


;;; Wide String Subprimitives:  Implementation as Byte Vector 16 Arrays

;;; The following section implements the subprimitives to support wide strings
;;; as byte-vector-16 arrays.  These subprimitives, and knowledge of their inner
;;; workings, are not be used except by the primitives, below.

;;; The last two elements of the vector encode a fill pointer, and the remaining
;;; elements contain wide character codes.  The users never see the raw contents
;;; of the byte vector.  Instead, access is only through the primitives provided
;;; below, notably charw and its setf method.  The internally stored code is
;;; turned into a wide character before being returned by charw, and the reverse
;;; takes place when (charw s i) is setf'd to a wide character, for some wide
;;; string s and index i.

;;; The fill-pointer is a 29-bit fixnum.  The least significant 16 bits are
;;; stored in element 0 of the (16-bit) byte vector.  The remaining 13 bits are
;;; stored in the the rightmost 13 bits of element 1 of the byte vector.  A
;;; "signature" of three one bits (#b111) is stored in the leftmost three bits
;;; of element 1 of the byte vector.  The signature is used for checking the
;;; validity and, to some extent, the purpose of the byte vector.

(def-substitution-macro wide-string-length-bv16 (wide-string-bv16)
  (let ((length (byte-vector-16-length wide-string-bv16)))
    (declare (type fixnum length))
    (+f (byte-vector-16-aref wide-string-bv16 (-f length 2))
        ;; Mask off the signature upper 3 bits, then shift it up 16.
        (ashf (logandf (byte-vector-16-aref wide-string-bv16 (-f length 1))
                       #x1FFF)
              16))))

(def-substitution-macro set-wide-string-length-bv16
    (wide-string-bv16 new-length)
  (let ((bv16-length (byte-vector-16-length wide-string-bv16)))
    (declare (type fixnum bv16-length))
    (setf (byte-vector-16-aref wide-string-bv16 (-f bv16-length 2))
          (logandf new-length #xFFFF))
    (setf (byte-vector-16-aref wide-string-bv16 (-f bv16-length 1))
          (logiorf #xE000 (ashf new-length -16)))
    ;; Insert a null byte at the new length.
    (setf (byte-vector-16-aref wide-string-bv16 new-length) 0)
    new-length))

(defsetf wide-string-length-bv16 set-wide-string-length-bv16)

(def-substitution-macro mark-wide-string-as-binary (wide-string-bv16)
  (let ((length (wide-string-length-bv16 wide-string-bv16)))
    (declare (type fixnum length))
    ;; terminate with 1, not 0.
    (setf (byte-vector-16-aref wide-string-bv16 length) 1)
    wide-string-bv16))

(def-substitution-macro binary-wide-string-p (wide-string-bv16)
  (and (byte-vector-16-p wide-string-bv16)
       (=f 1 (byte-vector-16-aref wide-string-bv16
                                  (wide-string-length-bv16 wide-string-bv16)))))


(defmacro charw-bv16 (wide-string-bv16 index)
  `(byte-vector-16-aref ,wide-string-bv16 ,index))

;; Note that this macro is used by charw and by an optimization in
;; wide-character-code.  -jra 7/15/96




(defun-simple valid-wide-string-length-bv16 (wide-string-bv16)
  (let ((bv16-length (byte-vector-16-length wide-string-bv16)))
    (declare (type fixnum bv16-length))
    (and (>=f bv16-length extra-wide-string-bv16-elements)
         (>=f (-f bv16-length extra-wide-string-bv16-elements)
              (wide-string-length-bv16 wide-string-bv16))
         (=f (logandf (byte-vector-16-aref wide-string-bv16 (-f bv16-length 1))
                      #xE000)
             #xE000))))






;;;; Wide-string Basic Primitives




;;; The macro `fill-wide-string' fills a wide string with wide-character between
;;; start?  and end?, for which 0 and (wide-string-length wide-string) are
;;; substituted if nil.

(defmacro fill-wide-string (wide-string wide-character &optional start? end?)
  (if (and (null end?) (not (symbolp wide-string)))
      (let ((ws (gensym)))
        `(let ((,ws ,wide-string))
           (fill-wide-string ,ws ,wide-character ,(or start? 0)
                             (wide-string-length-bv16 ,ws))))
      `(fill-wide-string-1 ,wide-string ,wide-character ,(or start? 0)
                           ,(or end? `(wide-string-length-bv16 ,wide-string)))))

(defun-void fill-wide-string-1 (wide-string wide-character start end)
  (declare (type fixnum start end))
  (loop with code fixnum = (wide-character-code wide-character)
        for i from start below end
        do
    (setf (charw-bv16 wide-string i) code)))

;; This is coded for maximal speed, and therefore goes below the primitive
;; level.  It is desirable that this be even faster, ideally a call to C memset.
;; (MHD 6/7/96)

;; The above is correct, but for maximal speed, the optional arguments should
;; also be removed from this function and this should be recoded as a
;; defun-void.  -jra 6/11/96





;;; The macro `make-wide-string' creates a wide string.  The keyword argument
;;; initial-element may be used to initialize each element in the string.  This
;;; has the same signature as make-stringw.
;;;
;;; `Make-wide-string-function' is a function variant of the macro
;;; make-wide-string.  However, it takes no keyword arguments.

(defmacro make-wide-string (length &key initial-element fill-pointer)
  (avoiding-variable-capture (length initial-element &aux wide-string-bv16)
    `(let ((,wide-string-bv16 (allocate-byte-vector-16
                                (+f ,length ,extra-wide-string-bv16-elements))))
       ,@(when initial-element
           `((fill-wide-string ,wide-string-bv16 ,initial-element 0 ,length)))
       (setf (wide-string-length-bv16 ,wide-string-bv16)
             ,(if fill-pointer
                  `,fill-pointer
                  length))
       ,wide-string-bv16)))


(defun-simple make-wide-string-function (length)
  (make-wide-string length))






;;; `Wide-string-fill-pointer' is exported for use on a wide string for which
;;; `adjustable-wide-string-p', which is a valid operation on any wide string,
;;; is true.  Wide-string-fill-pointer is setf'able.  An `adjustable wide
;;; string' is one which has a fill pointer. Also, `text-string-total-length' is
;;; exported for use on any wide string: it returns the maximum or "physical"
;;; length of the string, which may differ from the "active" length, i.e., the
;;; position of the fill-pointer, in the case of an adjustable wide string.
;;; Note that no operation for expanding the maximum length is provided at
;;; present.  Note, also, that the terminology around "adjustable" is not
;;; consistent with Common Lisp's use of that term; it's historically been used
;;; with its current meaning in Gensym software, however.

(defmacro wide-string-fill-pointer (wide-string)
  `(wide-string-length ,wide-string))

(defmacro adjustable-wide-string-p (wide-string)
  `(progn
     ,wide-string
     t));; always true in the current implementation

(defmacro wide-string-total-length (wide-string)
  `(-f (byte-vector-16-length ,wide-string) ,extra-wide-string-bv16-elements))




;;; `Wide-string-length' returns the current active length of wide-string.  It
;;; is exported for use outside of this module.
;;;
;;; This is analogous to Common Lisp's string (array) fill pointer mechanism
;;; but differs in a few respects.
;;;
;;; First, it is not necessary to check if a wide string has a fill pointer: all
;;; wide strings, by definition, have fill pointers.
;;;
;;; Second, it is is illegal to access the elements beyond the fill
;;; pointer. Before setting an element beyond the fill pointer, the fill pointer
;;; should be moved forward to at least one element beyond the position being set.
;;;
;;; Third, moving the fill pointer closer to the beginning of the string (0) can
;;; destroy data.  After you set the fill pointer of a wide string, the contents
;;; beyond that fill pointer are undefined.  E.g.,
;;;
;;;  (let ((my-string (make-stringw 5))
;;;           (string1 (copy-wide-string my-string)))
;;;        (decff (wide-string-fill-pointer my-string))
;;;        (incff (wide-string-fill-pointer my-string))
;;;        (let ((string2 (copy-wide-string my-string)))
;;;           (string=w string1 string2)))
;;;
;;; Fourth, (for code savvy about C foreign function calling), wide strings can
;;; be passed to C functions expecting an array of unsigned 16-bit integers
;;; terminated by a NUL (0) at the position of the fill pointer, i.e., one past
;;; the active length of the string.
;;;
;;; Note that the active length of the string is given by the macro
;;; wide-string-total-length, q.v.

(defmacro wide-string-length (wide-string)
  `(wide-string-length-bv16 ,wide-string))




;;; `Probable-reclaimed-text-string-p' is a development-only macro that
;;; heuristically determines if things is a reclaimed text string.  It could be
;;; wrong, but more often than not it will be correct.  It is used in
;;; text-string-p to trap calls to text-string-p with a reclaimed text string,
;;; which are usually errors, since a reclaimed text string appears not to be a
;;; text string at all.
;;;
;;; To make this work better, we bash the fill pointer in reclaimed strings,
;;; making them easily recognizeable as bad.
;;;
;;; NOTE: In 4.0 and earlier, reclaimed text strings were indistinguishable from
;;; from text strings in use.  This appears to have masked certain bugs, which
;;; the current distinction has now revealed.

(def-substitution-macro probable-reclaimed-wide-string-p (thing)
  (not (valid-wide-string-length-bv16 thing)))



;;; `Wide-string-p' is true if thing is a wide string, at least as can be
;;; determined in most contexts.  This should do the right thing in common
;;; usage, but it may be necessary to know the implementation to use this
;;; effectively in certain situations.

;; This predicate is bogus. It should at least be ANDed with
;; valid-wide-string-length-bv16.

#-development
(def-substitution-macro wide-string-p (thing)
  (byte-vector-16-p thing))

#+development
(defun-simple wide-string-p (thing)
  (when (byte-vector-16-p thing)
    (when (probable-reclaimed-wide-string-p thing)
      (cerror "Continue, as though in production, returning true"
              "~a is being recognized as a wide string, ~
             but it appears to be a RECLAIMED wide string!"
              thing))
    t))




;;; `Reclaim-wide-string' should be used to reclaim a wide string.

(defun-void reclaim-wide-string (wide-string)
  #+development
  (when (not (wide-string-p wide-string))
    (cerror "Continue, not reclaiming the string (in production, this would corrupt the pool!)"
            "~a was given to reclaim-wide-string, but isn't a wide-string."
            wide-string)
    (return-from reclaim-wide-string nil))
  ;; Bash the fill pointer, for debuggability, by XOR'ing off the signature:
  #+development
  (let ((original-length (wide-string-length wide-string))
        (bv16-length (byte-vector-16-length wide-string)))
    (declare (type fixnum original-length bv16-length))
    (setf (byte-vector-16-aref wide-string (-f bv16-length 1))
          (logandf #x1FFF (byte-vector-16-aref wide-string (-f bv16-length 1))))
    ;; Make the first and last characters bear the stamp of reclamation (&):
    (let ((stamp #.(wide-character-code #.%\&)))
      (cond
        ((>f original-length 2)
         (setf (charw-bv16 wide-string 0) stamp)
         (when (<=f original-length bv16-length) ; Protect against invalid length.
           (setf (charw-bv16 wide-string (-f original-length 1))
                 stamp)))
        ((>f (byte-vector-16-length wide-string) 3)
         (setf (charw-bv16 wide-string 0) stamp)))))
  ;; Now reclaim as a byte-vector-16:
  (reclaim-byte-vector-16 wide-string))




(defun-substitution-macro memmove-portion-of-wide-string-into-wide-string
    (source-string source-start source-end
                   destination-string destination-start)
  (copy-byte-vector-16-portion-carefully
    source-string source-start
    destination-string destination-start
    (-f source-end source-start)))


(defun-substitution-macro memcpy-portion-of-wide-string-into-wide-string
    (source-string source-start source-end
                   destination-string destination-start)
  (copy-byte-vector-16-portion
    source-string source-start
    destination-string destination-start
    (-f source-end source-start)))



;;; `Copy-portion-of-wide-string-into-wide-string' copies a portion of
;;; source-string to destination-string.  This should be the most efficient
;;; method possible, e.g., something like a memcpy on a good day, and is used by
;;; many higher level routines, e.g., copy-text-string.  This handles overlaps
;;; on EQ source and destination strings safely, i.e., as though contents of the
;;; source regions were initially copied to a temporary buffer, although the
;;; implementation may be more efficient than that.  Note that this could not
;;; deal with memory-overlaid source and destination strings, but those are
;;; not permitted by Gensym coding conventions.

(defun-substitution-macro copy-portion-of-wide-string-into-wide-string
    (source-string source-start source-end
                   destination-string destination-start)
  (cond
    ((and (eq source-string destination-string)
          (cond
            ((=f source-start source-end) t)        ; optimization; noop
            ((or 
               (<f source-start destination-start source-end)  
               (<f destination-start
                 source-start
                 (+f destination-start (-f source-end source-start)))) ; true => overlap
             (memmove-portion-of-wide-string-into-wide-string
               source-string source-start source-end
               destination-string destination-start)
             t))))
    (t
     (memcpy-portion-of-wide-string-into-wide-string
       source-string source-start source-end
       destination-string destination-start))))


;;; The accessor function `charw' accesses an element of a wide string.  `Charw'
;;; is a macro and a setf'able accessor of wide strings.  The accessor `scharw'
;;; is an analog of CL's SCHAR, and is provided for compatibility and/or
;;; completeness.  At this time, use of scharw is denigrated: it should not be
;;; relied on for a speed boost, and it adds complexity to use it in new code.
;;; But it's still supported for compatibility.

(defmacro charw (wide-string index)
  `(code-wide-character (charw-bv16 ,wide-string ,index)))

(defmacro set-charw (wide-string index wide-character)
  (if (wide-character-code-is-noop-p)
      `(setf (charw-bv16 ,wide-string ,index) ,wide-character)
      (avoiding-variable-capture (wide-string index wide-character)
        `(progn
           (setf (charw-bv16 ,wide-string ,index)
                 (wide-character-code ,wide-character))
           ,wide-character))))                ; return value set, per convention

(defsetf charw set-charw)

(defun-simple charw-function (wide-string index)
  (charw wide-string index))

(defun-simple set-charw-function (wide-string index wide-character)
  (set-charw wide-string index wide-character))

(defmacro scharw (wide-string index)
  `(charw ,wide-string ,index))

;; Note that the above automatically gives us a setf method for schar.



;;; The macro `concatenate-wide-strings' creates a new wide string whose that is
;;; the concatenation of the contents of wide-string-1 and wide-string-2.

(defun-substitution-macro concatenate-wide-strings (wide-string-1 wide-string-2)
  (let* ((length-1 (wide-string-length wide-string-1))
         (length-2 (wide-string-length wide-string-2))
         (new-wide-string (make-wide-string (+f length-1 length-2))))
    (declare (type fixnum length-1 length-2))
    (memcpy-portion-of-wide-string-into-wide-string
      wide-string-1 0 length-1 new-wide-string 0)
    (memcpy-portion-of-wide-string-into-wide-string
      wide-string-2 0 length-2 new-wide-string length-1)
    new-wide-string))







;;;; Printing Wide String Structures



;;; The code in this section is not intended for use outside of its module.  In
;;; fact, it is only to be called downstream from PRIN1 in order to print wide
;;; strings to the the specified Lisp stream.

;; It also is the beginning of the printer for wide-strings as byte-vector-16's.
;; -jra 5/29/96
;;
;; -- OK

;;; `Print-wide-string' is the printer for wide strings.  Note that this is
;;; defined in non-development systems so it may be used for debugging, e.g., by
;;; the PM suite.  Note, too, that it makes no use of Lisp's FORMAT function,
;;; just so it can be used in (the obsolete) "lite" systems (such as GSI),
;;; which do not define Lisp's FORMAT function.

;;; The GL system is currently rigged so that all byte vectors are printed using
;;; print-wide-string.  This can mean that certain random data may be mistakenly
;;; passed of as a wide string.  Accordingly, the printer endeavors to mistrust
;;; its input, in order to avoid aborts or illegal memory accesses.

;;; This function obeys the Common Lisp special variable *print-escape*, q.v. in
;;; CLtL.

;;; The special variables `*print-wide-string-max-length*' and
;;; `*abbreviate-wide-strings-for-legibility*' are of Gensym's creation, and
;;; can be used to fine-tune the way the printer works.
;;;
;;; If *abbreviate-wide-strings-for-legibility* is nil, then
;;; *print-wide-string-max-length* is ignored, and strings are always printed in
;;; their entirety.  If *print-escape* is true, then they are written such that
;;; they can be read back in; otherwise, their entire contents are written out,
;;; and this cannot in generall be read back in as a string with the same
;;; contents.
;;;
;;; If *abbreviate-wide-strings-for-legibility* is true, then at most
;;; *print-wide-string-max-length* characters of a wide string will be printed,
;;; with some amount removed from the middle or end as necessary to keep to this
;;; limit.  If *print-escape* is true, and truncation needs to happen, this will
;;; print the string unreadably (using #<...>), so that it cannot be mistaken
;;; for a shorter string that happens to contain an ellipsis (...).
;;;
;;; Note that in no case will the printer print a string that is readable unless
;;; it will in fact produce an equal string when read back in.
;;;
;;; The initial values are *print-wide-strings-readably* = T and
;;; *print-wide-string-max-length* = 200.


(defvar *print-wide-string-max-length* 200) ; was 100; try a little bit higher (MHD)
(defvar *abbreviate-wide-strings-for-legibility* t) ; previously named *print-wide-strings-readably*

(defun print-wide-string (wide-string stream print-depth)
  (declare (ignore print-depth))
  (cond
    ((valid-wide-string-length-bv16 wide-string)
     (print-valid-wide-string wide-string stream))
    (t
     (print-random-byte-vector-16 wide-string stream))))

#+development
(def-development-describer describe-wide-string (x)
  (when (wide-string-p x)
    (let ((*abbreviate-wide-strings-for-legibility* nil)
          (*print-wide-string-max-length* 2000))
      (print-wide-string x *standard-output* 0)
      x)))

;;; Print-random-byte-vector-16 prints something fairly good at showing the
;;; contents of a byte-vector-16 that does not appear to be a valid wide string.
;;; E.g., a byte-vector-16 10 long with each element = 97 prints as
;;;
;;;   #<Byte-vector-16 (10) [97|97] "aaaaaaaa">
;;;
;;; This gives the physical length (10), the content of the first 2 bytes (97),
;;; and the contents of the following 8 bytes, printed as unicode characters.

(defun print-random-byte-vector-16 (byte-vector-16 stream)
  (printing-random-object (byte-vector-16 stream)
    (let ((bv16-length (byte-vector-16-length byte-vector-16)))

      (write-string "Byte-vector-16 " stream)

      (write-string "(")
      (princ (byte-vector-16-length byte-vector-16) stream)
      (write-string ")")

      (write-string "[" stream)
      (when (>f bv16-length 0)
        (princ (byte-vector-16-aref byte-vector-16 0) stream))
      (when (>f bv16-length 1)
        (write-string "|")
        (princ (byte-vector-16-aref byte-vector-16 1) stream))
      (write-string "]" stream)

      (write-string "\"" stream)
      (loop with physical-length-limit = (-f bv16-length 2)
            for i from 0 below (min 100 physical-length-limit)
            do (print-wide-character-readably-in-string
                 (charw byte-vector-16 i)
                 stream)
            finally (when (<f i physical-length-limit)
                      (write-string "..." stream)))
      (write-string "\""))))


(defun print-valid-wide-string (wide-string stream)
  (let ((length (wide-string-length wide-string)))
    (cond
      ((and *abbreviate-wide-strings-for-legibility*
            (<f *print-wide-string-max-length*
                length))
       (cond
         (*print-escape*
          (printing-random-object (wide-string stream)
            (print-valid-wide-string-1
              wide-string stream 0 *print-wide-string-max-length* t)))
         (t
          (print-valid-wide-string-1
            wide-string stream 0 *print-wide-string-max-length* t))))
      (t
       (print-valid-wide-string-1 wide-string stream 0 length nil)))))



(defun print-valid-wide-string-1 (wide-string stream start end print-ellipsis-p)
  (when *print-escape* (write-string "#w\"" stream))
  (loop for i from start below end
        do (print-wide-character-readably-in-string
             (charw wide-string i)
             stream))
  (when print-ellipsis-p (write-string "..." stream))
  (when *print-escape* (write-string "\"" stream)))

;; Consider elliding from the middle, ala MS-Windows Directories (see MS-Windows
;; UI Style guide for description).


#+development
(def-development-printer pprint-wide-string (thing stream)
  (when (wide-string-p thing)
    (print-valid-wide-string thing stream)
    thing))


#+development
(defun-void pprint-wide-string-fully (text-string output-stream)
  (let ((*abbreviate-wide-strings-for-legibility* nil)
        (ascii-string
          (export-text-string text-string 'ascii)))
    (with-faster-standard-output
      (terpri output-stream)
      (write-string ascii-string output-stream)
      (reclaim-gensym-string ascii-string))))


(defun print-wide-character-readably-in-string (wide-character stream)
  (let ((code (wide-character-code wide-character)))
    (cond
      ((<=f 0 code 255)
       (let ((character (ascii-code-char code)))
         (when (and *print-escape*
                    (or (char= character #\\) (char= character #\")))
           (write-char #\\ stream))
         (write-char character stream)))
      (t
       (write-char #\\ stream)
       (write-char #\u stream)
       (if (<=f code #xfff) (write-char #\0 stream))
       (if (<=f code #xff) (write-char #\0 stream))
       (if (<=f code #xf) (write-char #\0 stream))
       (write-in-hex-to-lisp-stream stream code)))))

;; NOTE: you cannot use CL's FORMAT to implement this function.  It would make
;; it not work (not compile) with GSI. So the individual calls to write-char, et
;; al, may seem verbose, but they're there for a purpose.  (MHD 5/23/96)


;;; `pretty-print-wide-character-in-string' -- most of the time, "readable"
;;; characters are as pretty as we can get.  Make any exceptions here.

(defun pretty-print-wide-character-in-string (wide-character stream)
  (cond
    ((=f wide-character #.%line-separator)
     (write-char #\newline stream))
    ;; more exceptions to come?
    (t
     (print-wide-character-readably-in-string wide-character stream))))


;;; `pretty-print-wide-string-to-stream' - prints the contents of a wide string,
;;; using "pretty" version of characters. Prints the entire contents (no
;;; abbreviation) without quotes or other markers (i.e., no "#w", nor even the
;;; double quotes).  It finishes by printing a newline at the end.

(defun pretty-print-wide-string-to-stream (wide-string stream)
  (loop for i from 0 below (wide-string-length wide-string)
        do (pretty-print-wide-character-in-string
             (charw wide-string i)
             stream))
  (write-char #\newline stream))


;;; `pretty-print-wide-string' - prints to *standard-output*.  This function can
;;; be called, and is quite useful, from the C debugger.  It is not (presently)
;;; called by any Lisp code.  -jv, 4/25/06

(defun pretty-print-wide-string (wide-string)
  (pretty-print-wide-string-to-stream wide-string  *standard-output*)
  (values))



;;; `Twrite-wide-character-readably' writes wide-character in a "readable"
;;; manner (but only readable by humans, not by, say, the G2 parser) to the
;;; current wide string, i.e., in a twith-output-to-wide-string context.  The
;;; character is written as its byte value if it is under 256, and other wise as
;;; \uHHHH, where HHHH is its Unicode hex value, zero-extended as needed to use
;;; four digits.

(defun twrite-wide-character-readably (wide-character)
  (let ((code (wide-character-code wide-character)))
    (cond
      ((<=f 0 code 255)
       (let ((character (ascii-code-char code)))
         (when (and *print-escape*
                    (or (char= character #\\) (char= character #\")))
           (twrite-char #\\))
         (twrite-char character)))
      (t
       (twrite-char #\\)
       (twrite-char #\u)
       (if (<=f code #xfff) (twrite-char #\0))
       (if (<=f code #xff) (twrite-char #\0))
       (if (<=f code #xf) (twrite-char #\0))
       (twrite-positive-fixnum-in-radix code 16)))))


;;; `Lisp-highest-printable-character-code' is usually bound to 255.  It may
;;; well be useful to bind this at times to 127 or 126.  This will keep
;;; print-wide-character from printing Latin-1 (non-ASCII ) characters directly,
;;; but instead use hex escapes.  Note that Gensym currently does not put
;;; non-ASCII characters in its source files.

(defvar lisp-highest-printable-character-code 255)

(defun print-wide-character (wide-character &optional stream)
  (when (null stream)
    (setq stream *standard-output*))        ; nec?
  (let ((code (wide-character-code wide-character)))
    (cond
      ((<=f 0 code lisp-highest-printable-character-code)
       (let ((character (ascii-code-char code)))
         (write-char #\# stream)
         (write-char #\. stream)
         (write-char #\% stream)
         (write-char #\\ stream)
         (write-char character stream)))
      (t
       (write-char #\# stream)
       (write-char #\u stream)
       (if (<=f code #xfff) (write-char #\0 stream))
       (if (<=f code #xff) (write-char #\0 stream))
       (if (<=f code #xf) (write-char #\0 stream))
       (write-in-hex-to-lisp-stream stream code)))))







;;; `Write-in-hex-to-lisp-stream' writes positive-fixnum in the specified radix.

(defun-void write-in-hex-to-lisp-stream
    (stream non-negative-fixnum)
  (let ((radix 16))
    (if (>=f non-negative-fixnum radix)
        (let ((quotient (floorf-positive non-negative-fixnum radix))
              (remainder (modf-positive non-negative-fixnum radix)))
          (write-in-hex-to-lisp-stream stream quotient)
          (write-char (digit-char remainder radix) stream))
        (write-char (digit-char non-negative-fixnum radix) stream))))





;;;; Error Checking Wide String Access




;;; The function `error-check-wide-string-access' is used to make sure
;;; wide-string is a wide string, and that index falls within its current active
;;; length.  This is to be used in development-only code. However, it may be
;;; used in production code being developed or debugged.

#+development
(defun error-check-wide-string-access (wide-string index)
  (assert (wide-string-p wide-string))
  (if (not (<f index (wide-string-length wide-string)))
      (error
        "attempt to read a character beyond the ~
         length (~D) of this wide string"
        (wide-string-length wide-string))))

;; This is certainly a development-only operation.  -jra 5/22/96
;;
;; -- I'd rather leave it in as documented, since while we're
;; developing/debugging production code, it may be necessary at times to enable
;; this.  The cost is essentially nil as long as nobody uses it.  We could add a
;; warning with some effort if it does get used outside development, but is it
;; worth it?  (MHD 5/23/96)

;; I want to ensure that we don't accidentally leave it in someplace where it
;; could kill performance.  The cost of leaving it in is ensuring that nobody
;; uses it.  -jra 5/28/96
;;
;; Fine. (MHD 6/7/96)






;;;; Analogues to CL Char/String Functions for Wide Characters and Strings




;;; The functions, macros, and variables in this section are analogs for Common
;;; Lisp's functions for strings and characters, and should generally serve to
;;; replace them in Gensym's code transitioning from the "text string" to the
;;; "wide string" datatype.
;;;
;;; The analog functions all have names formed by appending the suffix "w", for
;;; "Wide", to the original Common Lisp name.
;;;
;;; The Common Lisp documentation and specification serves as the basic
;;; documentation and specification for these analogues.  The documentation here
;;; will mostly specify any significant and/or non-obvious incompatibilities.

;;; In general, the analog of the "character" datatype specified as an argument
;;; or value in CL is our "wide character" datatype, meaning either a Common
;;; Lisp character or a wide character code, a 16-bit unsigned integer.
;;;
;;; At the time the wide character/wide string implementation of the text string
;;; data type goes into effect, the character set used for storing characters in
;;; text strings will be the Unicode International Character Set (equivalent to
;;; the Basic Multilingual Plane (BMP) of the ISO standard ISO 10646).

;;; Operations such as comparison operations (char<w, et al), case conversion
;;; operations, and case-insensitive operations, will be with respect encodings
;;; in Unicode (rather than, say, ASCII, or even "the Common Lisp
;;; implementation") as the reference standard by which to judge case
;;; equivalence, character code values, etc.

;;; The functions are
;;;
;;;   stringpw -- use of wide-stringp is encouraged for sytilistic reasons
;;;
;;;   charw -- setf'able
;;;
;;;   scharw -- setf'able -- but note that this is no better than charw in our
;;;     current implementation.  Here for completeness, but use is discouraged.
;;;
;;;   make-stringw -- its initial-element keyword arg can be any wide character.
;;;       -- Here for completeness, but use of the equivalent make-wide-string
;;;       is encouraged for stylistic reasons.
;;;
;;;   lengthw -- generic: may be applied to wide strings or any other sequence
;;;
;;;   stringw -- coerces many things to a string
;;;
;;;   char=w, char>w, char<w, char>=w, char<=w, char/=w
;;;
;;;   char-codew, code-charw -- here for completeness, but use of wide-character-code
;;;       and code-wide-character is encouraged for stylistic reasons; perhaps normalize-
;;;       wide-character is really what you want if you think you want these; note that
;;;       code-char(w) may return nil for codes that don't have corresponding CL characters.
;;;       I.e., unlike CL, (eq c (code-charw (char-codew c))), where c is an arbitrary
;;;       wide character, is not necessarily true.

;; The implementation of code-wide-character does not conform to the description
;; above.  The implemented function attempts to make a Common Lisp character
;; from a wide character code, or else it returns NIL.  This is wrong, in that
;; this operations should always return a wide character given a fixnum
;; character code.  Further, in GL I am dropping the use of NIL returning
;; behavior for code-char, and that should also be true for code-charw.  -jra
;; 5/22/96

;;;
;;;
;;;   char-equalw, char-lesspw, char-greaterpw, char-not-lesspw,
;;;     char-not-greaterpw, char-not-equalw, char-upcasew, char-downcasew
;;;   string=w, string<w, string>w, string<=w, string>=w, string-lesspw,
;;;     string-greaterpw, string-not-greaterpw, string-not-lesspw
;;;
;;;       -- note that these do case folding, where appropriate, for
;;;       non-standard Lisp characters, e.g., for accented Latin characters, as
;;;       well elements of non-Roman scripts such as Cyrillic, Greek, etc. [This
;;;       is partially completed functionality -- the goal should be to do all
;;;       of Unicode in a complete, and stable way, as of the first public
;;;       release of this software.  Unless unavoidable, these should return the
;;;       same results between releases to avoid compatibility problems.]
;;;
;;;   digit-char-pw
;;;
;;;   string-upcasew, nstring-upcasew, string-downcasew, nstring-downcase



;;; The macro `stringpw' is true if thing is a wide string.  Note, however, that
;;; WIDE-STRING is not defined as a Common Lisp type.  I.e., (typep x
;;; 'wide-string) is illegal.

(defmacro stringpw (thing)
  `(wide-string-p ,thing))

;; I'd like (typep thing 'wide-string) to work, but we don't get it for free
;; from def-structure, and deftype is known to be buggy, so it's probably way
;; too much trouble. (MHD 11/18/95)




;;; The funciton `make-stringw' allocates a wide string length elements long.
;;; Initial-element can be either nil or any wide-character.  If non-nil, all
;;; elements are initialized to this value.  If initial-element is nil, the
;;; initial value of the elements is undefined: they may be "garbage" (any old
;;; wide character, 0's, space characters, or whatever.

(defun-allowing-keywords make-stringw (length &key initial-element)
  (if initial-element
      (make-wide-string length :initial-element initial-element)
      (make-wide-string length)))



;;; The function `lengthw' gives the length of a Common Lisp sequence or a wide
;;; string, which is not properly recognized as a sequence by the CL LENGTH
;;; function, for which this is a substitute.

(defun-simple lengthw (real-sequence-or-wide-string)
  (if (wide-string-p real-sequence-or-wide-string)
      (wide-string-length real-sequence-or-wide-string)
      (length real-sequence-or-wide-string)))



;;; The macro `fill-pointerw' is the setf'able accessor of a wide string only.
;;; Unlike CL's fill-pointer and unlike our lengthw function, this cannot work
;;; with any array with a fill pointer.  This just expands into
;;; wide-string-length, q.v., for further important details.

(defmacro fill-pointerw (wide-string)
  `(wide-string-length ,wide-string))





;;; The function `eltw' gives ith element of a Common Lisp sequence or a wide
;;; string, which is not properly recognized as a sequence by the CL ELT
;;; function, for which this is a substitute.

(defun-simple eltw (real-sequence-or-wide-string i)
  (if (wide-string-p real-sequence-or-wide-string)
      (charw real-sequence-or-wide-string i)
      (elt real-sequence-or-wide-string i)))

;; I sure hope nobody ever uses this operation.  The theory of elt as a language
;; feature is plain wrong, since it forces type dispatches on a sequence down
;; into the depths of loops that iterate over contents.  The callers of elt and
;; eltw should type dispatch on the kinds of sequences they can be given and
;; then use type specific element accessors within each separate case.  -jra
;; 5/22/96




;;;; Character Comparison



;;; The following operations are analogues of Common operations with the same
;;; names except for the "w" suffix.  Refer to the CL documentation along with
;;; the notes above for exact documentation.
;;;
;;;   `char=w', `char>w', `char<w', `char>=w', `char<=w', `char/=w'
;;;
;;;   `char-equalw', `char-lesspw', `char-greaterpw', `char-not-lesspw',
;;;     `char-not-greaterpw', `char-not-equalw'
;;;
;;;   `char-codew', `code-charw'
;;;
;;;   `char-upcasew', `char-downcasew'

(defun-for-macro spread-wide-character-rest-arg (wide-characters)
  (loop for wc in wide-characters
        collect `(wide-character-code ,wc)))

(defmacro char=w (&rest wide-characters)
  `(=f . ,(spread-wide-character-rest-arg wide-characters)))

(defun-simple char=w-function (wide-character-1 wide-character-2)
  (char=w wide-character-1 wide-character-2))

(defmacro char>w (&rest wide-characters)
  `(>f . ,(spread-wide-character-rest-arg wide-characters)))

(defmacro char>=w (&rest wide-characters)
  `(>=f . ,(spread-wide-character-rest-arg wide-characters)))

(defmacro char<w (&rest wide-characters)
  `(<f . ,(spread-wide-character-rest-arg wide-characters)))

(defmacro char<=w (&rest wide-characters)
  `(<=f . ,(spread-wide-character-rest-arg wide-characters)))

(defmacro char/=w (&rest wide-characters)
  `(/=f . ,(spread-wide-character-rest-arg wide-characters)))

(defun-simple char/=w-function (wide-character-1 wide-character-2)
  (char/=w wide-character-1 wide-character-2))


(defun-for-macro spread-and-downcase-wide-character-rest-arg (wide-characters)
  (loop for wc in wide-characters
        collect `(unicode-downcase (wide-character-code ,wc))))

(defmacro char-equalw (&rest wide-characters)
  `(=f . ,(spread-and-downcase-wide-character-rest-arg wide-characters)))


;;; `Char-equalw-function' is a function, and is primarily intended for use as a
;;; test function arg to gensym-search.  Note that it only accepts two
;;; arguments.

(defun-simple char-equalw-function (wide-character-1 wide-character-2)
  (char-equalw wide-character-1 wide-character-2))


(defmacro char-greaterpw (&rest wide-characters)
  `(>f . ,(spread-and-downcase-wide-character-rest-arg wide-characters)))

(defmacro char-not-lesspw (&rest wide-characters)
  `(>=f . ,(spread-and-downcase-wide-character-rest-arg wide-characters)))

(defmacro char-lesspw (&rest wide-characters)
  `(<f . ,(spread-and-downcase-wide-character-rest-arg wide-characters)))


;;; `Char-lesspw-function' is a function, and is primarily intended for use as a
;;; sort predicate.  Note that it only accepts two arguments.

(defun-simple char-lesspw-function (wide-character-1 wide-character-2)
  (char-lesspw wide-character-1 wide-character-2))


(defmacro char-not-greaterpw (&rest wide-characters)
  `(<=f . ,(spread-and-downcase-wide-character-rest-arg wide-characters)))

(defmacro char-not-equalw (&rest wide-characters)
  `(/=f . ,(spread-and-downcase-wide-character-rest-arg wide-characters)))

(defmacro code-charw (wide-character-code)
  `(code-wide-character ,wide-character-code))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro char-codew (wide-character)
  `(wide-character-code ,wide-character))
)

(def-substitution-macro char-upcasew (wide-character)
  (code-wide-character
    (unicode-upcase
      (wide-character-code wide-character))))

(def-substitution-macro char-downcasew (wide-character)
  (code-wide-character
    (unicode-downcase
      (wide-character-code wide-character))))





;;; The following are not "enhanced" for Unicode -- they only work for the
;;; standard Common Lisp printing characters, i.e., ASCII.
;;;
;;;   `lower-case-pw', `upper-case-pw', `alpha-char-pw', `alphanumericpw',
;;;   `digit-char-pw'

(defun-simple lower-case-pw (wide-character)
  (declare (type wide-character wide-character))
  (char<=w #.%\a wide-character #.%\z))

;; In this and all of the following operations, remove the requirement to
;; transform the given wide character into a Common Lisp character.  First of
;; all the NIL returning clause of code-char is going away in GL and secondly
;; this is guaranteed to be slow.  Use a char<=w on the appropriate wide
;; character constants in a macro to implement these simple predicates and make
;; them into macros.  -jra 5/22/96
;;
;; -- UPDATE: done, not only for reasons Jim gives, but because Chestnut RTL
;; already doesn't implement the NIL returning spec of CL's code-char.  Same
;; implementation is already in place for upper-case-pw, below.  (MHD 5/7/97)


(defmacro upper-case-pw (wide-character)
  (let ((code (gensym)))
    `(let ((,code (char-codew ,wide-character)))
       (<=f ,(char-codew %\A) ,code ,(char-codew %\Z)))))

(defmacro alpha-char-pw (wide-character)
  (let ((code (gensym)))
    `(let ((,code (char-codew ,wide-character)))
       (or (<=f ,(char-codew %\a) ,code ,(char-codew %\z))
           (<=f ,(char-codew %\A) ,code ,(char-codew %\Z))))))

(defun-simple alpha-char-pw-function (wide-character)
  (alpha-char-pw wide-character))

(defmacro alphanumericpw (wide-character)
  (let ((code (gensym)))
    `(let ((,code (char-codew ,wide-character)))
       (or (<=f ,(char-codew %\a) ,code ,(char-codew %\z))
           (<=f ,(char-codew %\A) ,code ,(char-codew %\Z))
           (<=f ,(char-codew %\0) ,code ,(char-codew %\9))))))

(defun-simple alphanumericpw-function (wide-character)
  (alphanumericpw wide-character))

(defun-simple digit-char-pw-function (wide-char radix)
  (declare (type wide-character wide-char)
           (fixnum radix))
  (let ((char-code (char-codew wide-char)))
    (cond ((<=f (char-codew %0)
                char-code
                (if (<f radix 10)
                    (+f (char-codew %0) (-f radix 1))
                    (char-codew %9)))
           (-f char-code (char-codew %0)))
          ((<=f radix 10)
           nil)
          ((<=f (char-codew %\A)
                char-code
                (+f (char-codew %\A) (-f radix 10 1)))
           (-f char-code (- (char-codew %\A) 10)))
          ((<=f (char-codew %\a)
                char-code
                (+f (char-codew %\a) (-f radix 10 1)))
           (-f char-code (- (char-codew %\a) 10)))
          (t nil))))

(defmacro digit-char-pw (wide-char &optional (radix 10))
  (if (and (constantp radix)
           (<= (eval radix) 10))
      (let ((char-code (gensym)))
        `(let ((,char-code (char-codew ,wide-char)))
           (declare (type fixnum ,char-code))
           (if (and (<=f ,(char-codew %0) ,char-code)
                    (<=f ,char-code
                         ,(+f (char-codew %0) (-f (eval radix) 1))))
               (-f ,char-code ,(char-codew %0))
               nil)))
      `(digit-char-pw-function ,wide-char ,radix)))

(defun-simple decimal-digit-char-pw-function (wide-character)
  (digit-char-pw wide-character 10))

(defun-simple hexadecimal-digit-char-pw-function (wide-character)
  (digit-char-pw wide-character 16))


(defmacro digit-charw (weight &optional (radix 10))
  (let ((weight-value (gensym))
        (radix-value (gensym)))
    (if (constantp radix)
        (cond ((<= 2 (eval radix) 10)
               `(let ((,weight-value ,weight))
                  (declare (type fixnum ,weight-value))
                  (if (and (>=f ,weight-value 0)
                           (<f ,weight-value ,radix))
                      (code-charw (+f ,(char-codew %0) ,weight-value))
                      nil)))
              ((<= 2 (eval radix) 36)
               `(let ((,weight-value ,weight))
                  (declare (type fixnum ,weight-value))
                  (if (and (>=f ,weight-value 0)
                           (<f ,weight-value ,radix))
                      (code-charw (+f (if (<f ,weight-value 10)
                                          ,(char-codew %0)
                                          ,(- (char-codew %\A) 10))
                                      ,weight-value))
                      nil)))
              (t
               (error "Bad radix ~a to digit-charw" radix)))
        `(let ((,weight-value ,weight)
               (,radix-value ,radix))
           (declare (type fixnum ,weight-value ,radix-value))
           (if (and (<=f 2 ,radix-value 36)
                    (>=f ,weight-value 0)
                    (<f ,weight-value ,radix-value))
               (code-charw (+f (if (<f ,weight-value 10)
                                   ,(char-codew %0)
                                   ,(- (char-codew %\A) 10))
                               ,weight-value))
               #.%\?))))) ; old: NIL





;;;; STRINGW: Coercion to Wide Strings



;;; `Stringw' is an analog of the Common Lisp function string.  It accepts a
;;; Common Lisp string or character, a wide string or wide character, or a
;;; symbol.  At present it does not accept a (gensym) pathname, even though CL's
;;; STRING would.
;;;
;;; It does the following based on the datatype of thing:
;;;
;;;   a wide string: returns thing itself
;;;
;;;   Common Lisp Character/Wide Character: a new wide string with one element: thing
;;;
;;;   symbol: the wide-string print name of thing (note: a shared object, not a copy)
;;;
;;;   A Common Lisp/Gensym string: a wide-string copy of thing
;;;
;;;   otherwise: nothing else is legal, so it signals an error
;;;
;;; Since this does not cons up fresh text strings repeatedly when called with a
;;; text string or symbol, it is appropriate to use at run time for normalizing
;;; a symbol or text string argument to a string comparison routine, which
;;; requires a text string.  It should not be used with gensym strings or
;;; characters at run time because these uses do cause consing.  Use with gensym
;;; strings or characters is appropriate for use at load time or at read time,
;;; e.g., #.(stringw "foo") would be the normal replacement for "foo" as a code
;;; constant in the sources.

;;; `Stringw-macro' is just the macro version of stringw.

(eval-when (#-chestnut-trans :compile-toplevel :load-toplevel :execute)

(def-substitution-macro stringw-macro (thing)
  (cond
    ((stringpw thing)
     thing)
    ((wide-character-p thing)
     (make-stringw 1 :initial-element thing))
    ((symbolp thing)
     (symbol-namew thing))
    ((stringp thing)
     (copy-as-wide-string thing))
    ;; (gensym-pathname thing) ; do later!
    ;;(t
    ;; (error "~a cannot be coerced to a wide string!" thing))))
    (t
     (copy-as-wide-string "UNSPECIFIED"))))

(defun-simple stringw (thing)
  (stringw-macro thing))
)


;;; `Careful-stringw' is used for internal functions that want to add a runtime
;;; development check for suspicious-seeming calling modes, namely with thing a
;;; string or character, which would cons up a new wide string, creating
;;; garbage.  This is used, i.e., for string=w, string-lesspw, and friends.

(def-system-variable stringw-should-not-cons-p unicode t t) ; bound t in a process
(setq stringw-should-not-cons-p nil)        ; bound nil outside a process

;; Note: it's not clear how this can work out if you compile in a buffer, since
;; that interrupts a process for the compile, presumably giving you the wrong
;; setting.  If we can get from the environment that we're doing such a compile,
;; we should fix this to check for that case in development. (MHD 6/7/96)

(defun-substitution-macro careful-stringw (thing)
  #+development
  (when (and stringw-should-not-cons-p        ; alt. abstraction would be "at-run-time-p"
             (not (or (stringpw thing)        ;   -- here, nil test used to determine
                      (symbolp thing))));   if we're at run time
    (cerror "Continue, as though in production, creating the garbage"
            "You are about to use STRINGW coercion at run time with something ~
             other than a symbol or wide string (~s).  This creates garbage!"
            thing))
  (stringw-macro thing))





;;;; New Text String Comparison Functions



;;; This set of operations is analogous to the set in Common Lisp, minus the "w"
;;; suffix on each function name.  Note that the somewhat unusual non-nil
;;; results are specified there as well.
;;;
;;;
;;; The functions below all return either nil or an integer, the length of the
;;; longest common prefix of the two strings, i.e., the index of the first
;;; position where the corresponding characters of the two strings differ.
;;; Differences in case are ignored.
;;;
;;; The conditions are as follows under which nil rather than an index is
;;; returned:
;;;
;;; `String>w' and `string-greaterpw' return nil if wide-string-1 is less than
;;; or equal to wide-string-2.  Only string>w is case-sensitive.
;;;
;;; `String<w' and `string-lesspw' return nil if wide-string-1 is greater than
;;; or equal to wide-string-2.  Only string<w is case-sensitive.
;;;
;;; `String/=w' and `string-not-equalw' return nil if wide-string-1 is the same
;;; as wide-string-2.  Only string/=w is case-sensitive.
;;;
;;; `String<=w' and `String-not-greaterpw' return nil if wide-string-1 is
;;; greater than wide-string-2.  Only string<=w is case-sensitive.
;;;
;;; `String>=w' and `string-not-lesspw' return nil if wide-string-1 is less than
;;; wide-string-2.  Only string>=w is case-sensitive.

;;; NB: keyword args are not always supported completely.  Where needed, they
;;; may be added in the future.


;; OBSOLETE: (for conformance to the standard, compatibility with existing code,
;; and efficiency of programming, we now do perform the usual conversion by
;; calling string; note that as before it is generally an error to call this
;; such that it would need to cons up a new, unshared wide string at run time,
;; e.g., by passing in a gensym string or a character.  However, if you pass
;; in either a symbol or a wide string, this will not be a problem.  (MHD 5/10/96)
;;
;; ;; NB: For efficiency, unlike CL, we do not perform coercions on args to
;; ;; strings, e.g., a symbol is not coerced to a string.  To get around this
;; ;; where it is needed, simply apply STRINGW to the args that are either symbols
;; ;; or strings.

;; The advice above is bad, since it tricks people into creating leaks.  -jra 5/22/96
;; -- Experience has shown this is needed functionality.  The documentation
;; makes clear what cases leak, and a development check detects cases of leaks
;; for those who don't follow the spec.  I really don't want to change this also
;; because there turned out to be quite few callsites using the free coercion,
;; usually to advantage. (MHD 6/6/96)

;; The style of implementation of these functions is wrong.  Making one
;; comparison function taking an ignore-case pushes a branch into the inner loop
;; of the comparitor.  Computing all the different return types of the
;; comparitors adds code within the inner loop that could cause its compiled
;; body to no longer fit within instruction caches.  Write nearly equivalent
;; loops special to each function.  -jra 5/22/96
;;
;; -- OK, it now has separate loops for case-sensitive vs. not. (MHD 6/6/96)

(defun-simple string-greaterpw (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 nil nil)))
    (if (>f result 0) (-f (absf result) 1))))

;; What is this function doing?  Why waste time computing some particular fixnum
;; to be returned when this is a predicate that callers can only depend upon to
;; return NIL or non-nil.  Any old fixnum is non-nil.  -jra 5/22/96
;;
;; Common Lisp: (string-greaterp "aabcd" "aaabc") => 2  (MHD 5/23/96)

(defun-simple string>w (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 nil t)))
    (if (>f result 0) (-f (absf result) 1))))

(defun-simple string-lesspw (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 nil nil)))
    (if (<f result 0) (-f (absf result) 1))))

(defun-simple string<w (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 nil t)))
    (if (<f result 0) (-f (absf result) 1))))

(defun-simple string-not-equalw (wide-string-1 wide-string-2)
  (let ((result                                ; t arg means that result is
          (wide-string-compare wide-string-1 wide-string-2 t nil)))
    (unless (=f result 0) (-f result 1))))        ;   always 0 or positive

(defun-simple string/=w (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 t t)))
    (unless (=f result 0) (-f result 1))))

(defun-simple string-not-greaterpw (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 nil nil)))
    (cond
      ((<f result 0)
       (-f (absf result) 1))
      ((=f result 0)
       (wide-string-length (stringw wide-string-1))))))

(defun-simple string<=w (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 nil t)))
    (cond
      ((<f result 0)
       (-f (absf result) 1))
      ((=f result 0)
       (wide-string-length (stringw wide-string-1))))))

(defun-simple string-not-lesspw (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 nil nil)))
    (cond
      ((>f result 0)
       (-f result 1))
      ((=f result 0)
       (wide-string-length (stringw wide-string-1))))))

(defun-simple string>=w (wide-string-1 wide-string-2)
  (let ((result (wide-string-compare wide-string-1 wide-string-2 nil t)))
    (cond
      ((>f result 0)
       (-f result 1))
      ((=f result 0)
       (wide-string-length (stringw wide-string-1))))))


;;; `String=' and `string-equalw' return true if wide-string-1 and wide-string-2
;;; are the same.  Only string=w is case-sensitive.

(defun-simple string-equalw (wide-string-1 wide-string-2)
  (=f (wide-string-compare wide-string-1 wide-string-2 t nil)
      0))

;; Consider coercing args to strings, using stringw, as does CL's string-equal,
;; et al! (MHD 2/16/96)

(defun-simple string=w (wide-string-1 wide-string-2)
  (or (eq wide-string-1 wide-string-2)        ; optimization only
      (=f (wide-string-compare wide-string-1 wide-string-2 t t)
          0)))



;;; `Wide-string-compare' compares the two text strings in "dictionary order",
;;; considering case only if consider-case? is true.  It returns zero (0) if
;;; wide-string-1 = wide-string-2.  If the strings are not equal, and
;;; just-check-equality? is false, then it returns a number whose absolute value
;;; minus one is the index of the first character in wide-string-1 at which the
;;; difference occured.  If just-check-equality?  is true, this number is always
;;; positive; however, if the strings are different lengths, this number is
;;; simply one past the lesser of the two lengths.  Otherwise
;;; (just-check-equality? is false), this number is negative number iff
;;; wide-string-1 < wide-string-2.  This also performs the usual CL-inspired
;;; normalization of non-wide-string args; see above for discussion of important
;;; caveats and limitations.

(defun-simple wide-string-compare
       (wide-string-1 wide-string-2 just-check-equality? consider-case?)

  (setq wide-string-1 (careful-stringw wide-string-1)) ; change/canonicalize
  (setq wide-string-2 (careful-stringw wide-string-2)) ;    string args

  (let ((length-1 (wide-string-length wide-string-1))
        (length-2 (wide-string-length wide-string-2)))
    (declare (type fixnum length-1 length-2))
    (when (and just-check-equality? consider-case?)
      (return-from wide-string-compare
        (if (or (not (=f length-1 length-2))
                (not (=f (compare-byte-vector-16-portion
                           wide-string-1 0
                           wide-string-2 0
                           length-1
                           t) ; the sign of the result doesn't matter
                         0)))
            (1+f (minf length-1 length-2))
            0)))
    (macrolet ((inner-loop (consider-case?)
                 `(loop
                    with index fixnum = 0
                    with code-1 fixnum = 0
                    with code-2 fixnum = 0
                    do (cond
                         ((>=f index length-1)
                          (return (if (<f index length-2)
                                      (-f (+f index 1)) 0)))
                         ((>=f index length-2)
                          (return (+f index 1))))

                    ;; Pseudoloop: just "loops" two times, leaving code-1, code-2,
                    ;; and index appropriately set upon exit.
                       (setq code-1
                             (wide-character-code
                               (charw wide-string-1 index)))
                       (setq code-2
                             (wide-character-code
                               (charw wide-string-2 index)))
                       ,@(when (not consider-case?)
                           '((let ((downcase-code?
                                     ;; largeish expansion:
                                     (map-unicode-case code-1 down)))
                               (when downcase-code?
                                 (setq code-1 downcase-code?))
                               (setq downcase-code?
                                     ;; largeish expansion:
                                     (map-unicode-case code-2 down))
                               (when downcase-code?
                                 (setq code-2 downcase-code?)))))
                        (incff index)
                    unless (=f code-1 code-2)
                      return (if (or just-check-equality?
                                     (>f code-1 code-2))
                                 index
                                 (-f index)))))
      (if consider-case?
          (inner-loop t)
          (inner-loop nil)))))

;; This is definitely coded for speed more than elegance.

;; Consider adding start/end args when the need arises, here and elsewhere in
;; this section.


        

;;;; Other Basic and Miscellaneous Wide String Operations




;;; The simple function `copy-wide-string' takes a wide string and returns a
;;; newly allocated wide-string containing the same characters.  To make a
;;; wide-string when you have an unknown type of string, use
;;; copy-as-wide-string.

(defmacro copy-wide-string-given-length-macro
    (wide-string-to-copy length &optional (check-for-binary-p nil))
  `(let* ((new-wide-string (make-wide-string ,length))
          ,@(when check-for-binary-p `((binary-p (binary-wide-string-p ,wide-string-to-copy))))
          )
     (copy-byte-vector-16-portion
       ,wide-string-to-copy 0 new-wide-string 0 ,length)
     ,@(when check-for-binary-p `((when binary-p
                                    (mark-wide-string-as-binary new-wide-string))))
     new-wide-string))

(defun-simple copy-wide-string-given-length (wide-string-to-copy length)
  (copy-wide-string-given-length-macro wide-string-to-copy length nil))

(defun-simple copy-wide-string (wide-string-to-copy)
  #+development
  (test-assertion (wide-string-p wide-string-to-copy))
  (let* ((length (wide-string-length wide-string-to-copy)))
    (copy-wide-string-given-length-macro wide-string-to-copy length t)))

(defun-simple copy-constant-wide-string-given-length (wide-string-to-copy length)
  (copy-wide-string-given-length-macro wide-string-to-copy length nil))


(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro copy-constant-wide-string (constant-wide-string)
  (cond
    ((constantp constant-wide-string)
     (test-assertion (wide-string-p constant-wide-string))
     (let ((length (wide-string-length constant-wide-string)))
       `(copy-constant-wide-string-given-length
          ,constant-wide-string ,length)))
    (t
     `(progn
        #+development
        (cerror "Go on, doing a regular copy-wide-string"
                "copy-constant-wide-string must receive a constant as its argument.")
        (copy-wide-string constant-wide-string)))))
)




;;; `Copy-as-wide-string' takes either a wide string or a Common Lisp string and
;;; returns a wide string with equivalent contents.  `Copy-partial-wide-string'
;;; is the same, but makes a string only part-length elements long, with that
;;; many equivalent elements.

(eval-when (#-chestnut-trans :compile-toplevel :load-toplevel :execute)
(defun-simple copy-as-wide-string (wide-string-or-lisp-string)
  (if (stringp wide-string-or-lisp-string)
      (let* ((string-length
               (length wide-string-or-lisp-string))
             (result
               (make-wide-string string-length)))
        (copy-portion-of-string-into-text-string
          wide-string-or-lisp-string 0 string-length
          result 0)
        result)
      (copy-wide-string wide-string-or-lisp-string)))
  )

;; Why is this polymorphic?  The function of this name should take only wide
;; strings and you should make another function with a more compilicated name
;; that can take either kind.  -jra 5/22/96
;;
;; -- It's just as easy to leave this polymorphic.  The inner loop is the only
;; only place that matters, and it's nonpolymorphic.

;; I disagree.  The polymorphism fosters confusion, especially this this copy
;; operation does no transformation between character encodings.  Also,
;; performance outside the loop is an issue.  This operation should really end
;; up as an inlined expansion to copy-byte-vector-16-portion.  -jra 5/28/96
;;
;; There are 450+ call sites of copy-text-string and copy-wide-string. Deferred
;; issue. (MHD 6/7/96).

;; But copy-wide-string is NEW, so the "been this way forever so it can't be
;; changed" argument doesn't hold water.  Besides, I just did a search and found
;; a total of 11 callers.  If you want copy-text-string and a
;; copy-as-wide-string that converts from apples, oranges, and orangutans to
;; wide-strings, thats fine.  But the most convenient name should be reserved
;; for the type specific operation, and that is copy-wide-string.  I can't even
;; find a wide-string specific copy operation, besides wide-string substring,
;; and that forces me to pass over extra NILs.  No one is going to call that
;; directly.  I'm making the change.  -jra 6/11/96



(defun-simple copy-partial-wide-string (wide-string-or-lisp-string part-length)
  (let ((result (make-wide-string part-length)))
    (copy-portion-of-string-into-text-string
      wide-string-or-lisp-string 0 part-length
      result 0)
    result))

;; Note that no translation from Gensym complex characters to Unicode is going
;; to be done at this level.  The few places in the sources where this might be
;; an issue are going to be fixed by hand.



;;; `Copy-portion-of-wide-string' is a macro which returns a wide string
;;; containing the substring of wide-string given by the start and end
;;; arguments.  Start and end are required arguments so that it never
;;; has to call wide-string-length.

(defmacro copy-portion-of-wide-string (wide-string start end)
  (avoiding-variable-capture (wide-string start end)
    `(let* ((part-length (-f ,end ,start))
            ;; We need to know the length of the portion to
            ;;   (i) create the new string,
            ;;   (ii) do the copying.
            (result (make-wide-string part-length)))
       (declare (type fixnum part-length))
       ;; We could call copy-portion-of-wide-string-into-wide-string
       ;; at this point, which handles the special case of the source
       ;; and destination strings being the same string.  But since
       ;; we've just created a fresh string for the destination, we
       ;; can call copy-byte-vector-16-portion directly.
       (copy-byte-vector-16-portion
         ,wide-string ,start result 0 part-length)
       result)))


;;; `Wide-string-substring' is a function which returns a wide string
;;; containing the substring of wide-string given by the optional start
;;; and end arguments.

(defun-simple wide-string-substring (wide-string start? end?)
  (copy-portion-of-wide-string
    wide-string (or start? 0) (or end? (wide-string-length wide-string))))

;; Consider changing to allow the arg to be a gensym string. (MHD 12/13/95)



;;; `Read-character-from-wide-string' returns the wide character at the position
;;; in wide-string specified by index-variable.  Index-variable is advanced past
;;; the character.

(defmacro read-character-from-wide-string (wide-string index-variable)
  `(prog1
     (charw ,wide-string ,index-variable)
     (incff ,index-variable)))



;;; `Eqlw' is true if either (1) a and b are eql or (2) if both are wide
;;; characters, a and b are char=w.  The idea is that eqlw works as well
;;; for wide characters as eql does for characters.

(defmacro eqlw (a b)
  `(eql ,a ,b))

;; This should be a macro, there are no forward references.  When
;; wide-characters are always fixnums, then this macro can expand directly into
;; eql, and we can consider removing this abstraction on an abstraction on an
;; abstraction.  -jra 5/22/96
;;
;; It's now a macro that expands into eql, since wide characters can be tested
;; this way now, given the current implementation.  (MHD 6/7/96)



;;; `Equalw' is true if either (1) a and b are equal; (2) a and b are both wide
;;; characters and are char=w; or (3) a and b are both wide strings and are
;;; string=w.  The idea is that equalw works for wide strings or characters as
;;; well as equal does for strings or characters.

(defun-simple equalw (a b)
  (cond
    ((and (consp a) (consp b))
     (and (equalw (car a) (car b))
          (equalw (cdr a) (cdr b))))
    ((and (wide-string-p a) (wide-string-p b))
     (string=w a b))
    (t
     (equal a b))))

;; Note that now that wide characters are implemented as fixnums, no
;; special test is needed here; the test falls out naturally through equal.

;; A quick review of the call sites to this function shows that most of them
;; should be calling string=w directly since one argument was clearly a
;; wide-string.  -jra 5/23/96





;;; The function `wide-character-member' is like member called with two args,
;;; but compares item to the elements of list using EQLW instead of EQL.  It
;;; also differs in that it takes no more than two args.
;;;
;;; The function `wide-character-assoc' is to assoc as wide-character-member is
;;; to member.

(defun-simple wide-character-member (item list)
  (loop for items on list
        when (eqlw item (first items))
          return items))


(defun-simple wide-character-assoc (item a-list)
  (loop for sublist in a-list
        when (and sublist                ; skip (null sublist) entries
                  (eqlw item (car sublist)))
          return sublist))


(defun-simple wide-character-rassoc (item a-list)
  (loop for sublist in a-list
        when (and sublist                ; skip (null sublist) entries
                  (eqlw item (cdr sublist)))
          return sublist))


;;; `Position-in-wide-string' is similar to CL's POSITION, but is specialized
;;; for searching for a wide character in a wide string.

(defun-simple position-in-wide-string (wide-character wide-string)
  (declare (type wide-character wide-character))
  (loop for i from 0 below (wide-string-length wide-string)
        when (char=w (charw wide-string i) wide-character)
          return i))


;;; The function `remove-character-from-wide-string' removes all occurances of
;;; wide-character from wide-string, returning a new wide string (even if there
;;; were no changes.)

(defun remove-character-from-wide-string (wide-character wide-string)
  (declare (type wide-character wide-character))
  (let* ((count (loop for i from 0 below (wide-string-length wide-string)
                      count (char=w (charw wide-string i) wide-character)))
         (new-string (make-wide-string (-f (wide-string-length wide-string)
                                           count)))
         (j 0))
    (loop for i from 0 below (wide-string-length wide-string) doing
      (unless (char=w (charw wide-string i) wide-character)
        (setf (charw new-string j) (charw wide-string i))
        (incff j)))
    new-string))


;;; The function `search-wide-string' returns the position of pattern in
;;; wide-string. It optionally ignores text which is "hidden" by being quoted
;;; with double-quotes or an at-sign.

(defun search-wide-string (pattern wide-string start? end? &optional skip-quoted-portions?)
  (loop with patlen = (lengthw pattern)
        with end = (or end? (lengthw wide-string))
        with escape = nil
        with quoted = nil
        for i from (or start? 0) to (-f end patlen)
        as ch = (charw wide-string i)
        doing
    (cond (escape
           (setq escape nil))
          ((and skip-quoted-portions? (char=w ch #.%\@))
           (setq escape t))
          ((and skip-quoted-portions? (char=w ch #.%\"))
           (setq quoted (not quoted)))
          (quoted)
          ((=f 0 (compare-byte-vector-16-portion
                   pattern 0 wide-string i (minf patlen (-f end i)) t))
           (return i)))))


;;; `String-upcasew', `nstring-upcasew', `string-downcasew', `nstring-downcase'
;;; ...

(defun-simple string-upcasew (wide-string)
  (loop with new-string = (copy-wide-string wide-string)
        for i from 0 below (wide-string-length wide-string)
        do (setf (charw new-string i) (char-upcasew (charw wide-string i)))
        finally (return new-string)))

(defun-simple string-downcasew (wide-string)
  (loop with new-string = (copy-wide-string wide-string)
        for i from 0 below (wide-string-length wide-string)
        do (setf (charw new-string i) (char-downcasew (charw wide-string i)))
        finally (return new-string)))

(defun-simple nstring-upcasew (wide-string)
  (loop for i from 0 below (wide-string-length wide-string)
        do (setf (charw wide-string i) (char-upcasew (charw wide-string i))))
  wide-string)

(defun-simple nstring-downcasew (wide-string)
  (loop for i from 0 below (wide-string-length wide-string)
        do (setf (charw wide-string i) (char-downcasew (charw wide-string i))))
  wide-string)




;;;; G2 Symbols and Wide Strings



;;; `Simple-symbol-wide-character-p' and `simple-pathname-wide-character-p' are
;;; wide-character replacements for simple-symbol-character-p and
;;; simple-pathname-character-p, respectively.  See the original function for
;;; the documentation/spec.  These are used for token parsing in the editor.

(defun-simple simple-symbol-wide-character-p (wide-character)
  (let* ((code (wide-character-code wide-character)))
    (if (<=f code #x7f)
        (simple-symbol-character-p wide-character))))

;; Fixed not to rely on code-char returning nil for non-ascii values -- this
;; could be a problem with Chestnut's RTL. And ditto below. (MHD 5/7/97)


(defun-simple simple-pathname-wide-character-p (wide-character)
  (let* ((code (wide-character-code wide-character))
         (character? (if (<=f code #x7f) (code-char code))))
    (and character? (simple-pathname-character-p character?))))

;; Same comment here as the function above, this is an incorrect usage of
;; code-wide-character.  -jra 5/23/96



;;;; Writing Wide Strings




;;; `Twith-output-to-wide-string' returns a new wide string, the contents
;;; of which are produced by a sequences of invocations of twrite, tformat, et
;;; al. within body.  Each of these invocations ultimately reduces to the
;;; writing of simple characters by means of twrite-char.
;;;
;;; This binds current-twriting-output-type to WIDE-STRING.  See twrite-char and
;;; twith-output-to-text-string for further information on what this does.

;; This section needs a new operation as well, twith-output-to-wide-string-list
;; to handle arbitrarily long texts.  -jra 5/23/96

(def-named-dynamic-extent outputting-to-wide-string
  (module utilities1)
  (unwind? nil))

(defvar-of-named-dynamic-extent current-wide-string
    outputting-to-wide-string)

(defvar-of-named-dynamic-extent fill-pointer-for-current-wide-string
    outputting-to-wide-string)

(defvar-of-named-dynamic-extent total-length-of-current-wide-string
    outputting-to-wide-string)

(defvar-of-named-dynamic-extent current-wide-string-list
    outputting-to-wide-string)


(defmacro with-designated-current-wide-string (wide-string &body body)
  `(let* ((current-wide-string ,wide-string)
          (fill-pointer-for-current-wide-string 0)
          (total-length-of-current-wide-string
            (wide-string-length current-wide-string))
          (current-twriting-output-type 'wide-string))
     (progn . ,body)))

(defmacro with-current-wide-string (&body body)
  `(let ((current-wide-string-list 'do-not-use))
     (with-designated-current-wide-string
         (make-wide-string 2048)
       ,@body)))

(defmacro twith-output-to-wide-string (&body body)
  `(with-current-wide-string
     (progn . ,body)
     (copy-out-current-wide-string)))

(defmacro twith-output-to-designated-wide-string (wide-string &body body)
  `(let ((current-wide-string-list 'do-not-use))
     (with-designated-current-wide-string ,wide-string
       ,@body)))



;;; `Twith-output-to-then-use-of-wide-string' is like twith-output-to-wide-string
;;; except that (1) the special variable, current-wide-string, is bound during
;;; the execution of body and is available to the caller; (2) the special
;;; variable, fill-pointer-for-current-wide-string, is bound during the
;;; execution of body and is available to the caller; (3) it returns the results
;;; of evaluating the last form in body; and (4) the output string is
;;; automatically reclaimed upon exiting the body.  This can return at most
;;; 6 values.

;;; To copy the filled portion of current-wide-string, use the function
;;; copy-current-wide-string.

(defmacro twith-output-to-then-use-of-wide-string (&body body)
  (let* ((arg1 (gensym)) (arg2 (gensym)) (arg3 (gensym))
         (arg4 (gensym)) (arg5 (gensym)) (arg6 (gensym)))
    `(with-current-wide-string
         (multiple-value-bind (,arg1 ,arg2 ,arg3 ,arg4 ,arg5 ,arg6)
             (progn . ,body)
           (reclaim-wide-string current-wide-string)
           (values ,arg1 ,arg2 ,arg3 ,arg4 ,arg5 ,arg6)))))

;; Fix limit on the number of values someday!


;;; `Twith-output-to-wide-string-list' is like twith-output-to-wide-string
;;; except that it emits a gensym list of wide strings.  Each string but the
;;; last has a maximum length (given by the constant
;;; `wide-string-list-maximum-length', currently 1024).  The last string will
;;; range in length between 0 and the maximum as needed to fit the final data.
;;;
;;; This is intended for use in situations where the length of the intermediate
;;; and/or result string(s) must be limited.  This can be used, for example, to
;;; work around the limit given by the constant text-string-total-length, q.v.
;;;
;;; This macro is guaranteed not to expand the current wide string beyond the
;;; specified maximum length.  Note that character sequences are broken off at a
;;; completely arbitrary point.  For example, there is no guarantee that a base
;;; character (say A) will not be separated from its accent (say umlaut), since
;;; that would have to happen if, say, A is the 1024th character and umlaut is
;;; the 1025th.

(defconstant wide-string-list-maximum-length 1024)

;; Consider making this a parameter, which callers might bind in order to
;; control the length of emitted strings.



;;; The variable current-wide-string-list is internal to the inner workings of
;;; of twith-output-to-text-string, et al.  Its value is at all times either (a)
;;; a symbol or (b) a non-empty list made up of gensym conses, the symbol nil,
;;; and unshared wide strings.
;;;
;;; When twith-output-to-text-string is called normally,
;;; current-wide-string-list has its top-level global binding, namely to the
;;; symbol DO-NOT-USE.  In this case, emitting of strings to a list is not done,
;;; and wide-string-list-maximum-length is not referred to.
;;;
;;; When twith-output-to-text-string is being called by
;;; twith-output-to-wide-string-list, current-wide-string-list is initially
;;; bound to a gensym list whose single element is a wide string whose physical
;;; length is at least that given by the constant
;;; wide-string-list-maximum-length, and whose fill pointer is set at 0.
;;;
;;; In the course of emitting wide strings to the list, contents will be
;;; replaced by as many characters as needed, up to its maximum length, and its
;;; fill-pointer incremented accordingly.  If additional elements are needed,
;;; they will nconced onto the end (using as gensym-listed wide strings).

(defmacro twith-output-to-wide-string-list (&body body)
  `(let* ((new-wide-string
            (make-wide-string wide-string-list-maximum-length))
          (current-wide-string-list
            (gensym-list new-wide-string)))
     (with-designated-current-wide-string
         new-wide-string
       (progn ,@body)
       (setf (wide-string-length current-wide-string)
             fill-pointer-for-current-wide-string))
     current-wide-string-list))


;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter extend-current-text-string-error-message
  "Trying to write a string longer than 2MB!") ; previously 128K, then 1MB
)



(defmacro signal-extend-current-wide-string-error ()
  `(if (fboundp 'handle-extend-current-text-string-error)
       (funcall 'handle-extend-current-text-string-error)
       (error #.extend-current-text-string-error-message)))

(defun-void extend-current-wide-string (minimum-new-total-length)
  (when (>f minimum-new-total-length maximum-wide-string-length)
    (signal-extend-current-wide-string-error)) ; presumably an infinite loop
  (cond
    ((consp current-wide-string-list)
     (let* ((new-string-length (maxf minimum-new-total-length
                                     wide-string-list-maximum-length))
            (new-wide-string
              (make-wide-string new-string-length)))
       (setf (wide-string-length current-wide-string)
             fill-pointer-for-current-wide-string)
       (nconc current-wide-string-list (gensym-list new-wide-string))
       (setq fill-pointer-for-current-wide-string 0)
       (setf current-wide-string new-wide-string)
       (setq total-length-of-current-wide-string new-string-length)))
    (t
     (let* ((new-total-length
              (minf maximum-wide-string-length
                    (maxf (floorf-positive
                            (*f total-length-of-current-wide-string 3)
                            2)  ; 1.5; 1.25?
                          minimum-new-total-length)))
            (new-wide-string
              (make-wide-string new-total-length)))
       (copy-portion-of-wide-string-into-wide-string
         current-wide-string 0 fill-pointer-for-current-wide-string
         new-wide-string 0)
       (reclaim-wide-string current-wide-string)
       (setf current-wide-string new-wide-string)
       (setf total-length-of-current-wide-string new-total-length)))))




;;; The function `twriting-accumulated-length' returns a fixnum of the number of
;;; characters accumulated within the string being produced within the current
;;; twriting context.  This works for twith-output-to-text-string,
;;; twith-output-to-wide-string, or twith-output-to-wide-string-list contexts,
;;; but not the old gensym-string writing contexts.

(defun-simple twriting-accumulated-length ()
  (cond ((consp current-wide-string-list)
         (+f (loop for string-cons = current-wide-string-list
                                   then next-cons
                   for next-cons = (cdr-of-cons string-cons)
                   while next-cons
                   sum (wide-string-length (car-of-cons string-cons)) fixnum)
             fill-pointer-for-current-wide-string))
        (t
         fill-pointer-for-current-wide-string)))




;;; `Copy-current-wide-string' makes a wide-string copy of current-wide-string
;;; and returns the copy.  This may not be used when accumulating a list of
;;; strings for output, i.e., immediately within
;;; twith-output-to-text-string-list.

;;; `Copy-out-current-wide-string' makes a wide-string copy of
;;; current-wide-string and returns the copy after reclaiming the original.
;;; This may not be used when accumulating a list of strings for output, i.e.,
;;; immediately within twith-output-to-text-string-list.

(defun-simple copy-current-wide-string ()
  (let ((new-wide-string (make-stringw fill-pointer-for-current-wide-string)))
    (copy-portion-of-wide-string-into-wide-string
      current-wide-string 0 fill-pointer-for-current-wide-string
      new-wide-string 0)
    new-wide-string))

(defun-simple copy-out-current-wide-string ()
  (prog1 (copy-current-wide-string)
    (reclaim-wide-string current-wide-string)))


;;; `Maximum-suggested-length-for-wide-strings' determines the maximum length of
;;; wide strings.  This is a reasonably high number so that extension is
;;; usually/often unnecessary.

(defparameter maximum-suggested-length-for-wide-strings 2048)

;; Used in BOXES for formatting entire texts.


;; [The truncate-if-overly-long? arg from old text-string days is not
;; supported. Old doc: If truncate-if-overly-long? is specified, the copy will
;; be truncated if necessary so that it can be a simple wide string whose
;; length does not exceed maximum-suggested-length-for-simple-wide-strings.
;;
;; We also don't provide an equivalent to the (starts without a "T")
;; with-output-to-text-string macro, which is only used in one place, just
;; for writing strange objects that don't need writing.  I'm making that
;; be #+development anyway -- see UTILITIES1.
;;
;; (MHD 11/10/95)]




;;; `Tformat-wide-string' is just like tformat-gensym-string, but it returns a new
;;; wide string instead of a gensym string.  The args should be symbols, strings,
;;; characters, integers, and floats.  They should not be conses, arrays,
;;; rationals, complex numbers, etc.

(defun tformat-wide-string
       (control-string
        &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)        ; add more as needed!
  (twith-output-to-wide-string
    (tformat control-string arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)))






(defun copy-wide-string-with-case-conversion
    (wide-string which-characters-to-upcase?)
  (declare (eliminate-for-gsi))
  (loop with new-wide-string = (copy-as-wide-string wide-string) ; a little slow
        with length = (wide-string-length new-wide-string)
        with upcase-after-ordinary-character?
          = (eq which-characters-to-upcase? :all)
        with upcase-next-character? = (neq which-characters-to-upcase? :none)
        for i from 0 below length
        as wide-character = (charw new-wide-string i)
        do (setf (charw new-wide-string i)
                 (cond
                   ((word-separator-p wide-character)
                    (setq upcase-next-character?
                          (and which-characters-to-upcase?
                               (or (eq which-characters-to-upcase?
                                       :first-of-each-word)
                                   (eq which-characters-to-upcase? :all))))
                    wide-character)
                   (t (cond
                        (upcase-next-character?
                         (setq upcase-next-character?
                               upcase-after-ordinary-character?)
                         (char-upcasew wide-character))
                        (t (setq upcase-next-character?
                                 upcase-after-ordinary-character?)
                           (char-downcasew wide-character))))))
        finally (return new-wide-string)))

;; NOTE: German double-s not handled correctly: double-s should only be used for
;; lowercase.  It's not clear this can be handled by such a low-level routine,
;; since it would involve an expansion or contraction of the string, and it
;; would not be reversible.
;;
;; NOTE: In some languages, accents should not be included in uppercase letters.
;; It's not clear how to support that here, since it varies by language.  And
;; it's also not clear how to handle the expansion/contraction that would happen
;; if non-spacing-mark accents were used.
;;
;; NOTE: "Title case" should be used for first-of-each-word style -- this is
;; standardized in Unicode.  E.g., the digraph character DZ, which is a single
;; character used for some European languages, has three cases: DZ, Dz, and dz,
;; the middle one being "title case".

;; Note that the use of word-separator-p is a slightly incompatible upgrade from
;; the 4.0 version, where we tested
;;
;;   (or
;;     (char= wide-character #\-)
;;     (char= wide-character #\space))
;;
;; This may want to documented and users warned.  (MHD 11/14/95)

;; See copy-gensym-string-with-case-conversion for original "subtleties" (or even
;; bugs).  (MHD 11/14/95)


;; Most of the functions in this section are analogues of similarly named
;; functions in UTILITIES1.  I haven't brought over all the documentation, but
;; that should eventually be done! (MHD 11/18/95)



(defun copy-symbol-name-as-wide-string
    (symbol which-characters-not-to-downcase?
            &optional substitute-spaces-for-hyphens?
            character-to-add-at-end?
            acronym-list?)
  (declare (eliminate-for-gsi))
  (twith-output-to-wide-string
    (twrite-symbol-name
      symbol which-characters-not-to-downcase?
      substitute-spaces-for-hyphens?
      character-to-add-at-end?
      acronym-list?)))



;;; `Twrite-symbol-name' write symbols to the current output string.  The args
;;; are the same as those documented for copy-symbol-name., q.v.  [Note that
;;; this does not properly write out to the current _text_ string, only to the
;;; current _wide_ (unicode) string.]

(defun twrite-symbol-name (symbol which-characters-not-to-downcase?
                                  substitute-spaces-for-hyphens?
                                  character-to-add-at-end?
                                  acronym-list?)
  (declare (eliminate-for-gsi))
  (twrite-string-as-attribute-name
    (get-or-make-symbol-name-wide-string symbol)
    which-characters-not-to-downcase?
    substitute-spaces-for-hyphens?
    character-to-add-at-end?
    acronym-list?))


;;; `Twrite-string-as-attribute-name' is just a redistribution of the
;;; original code that provides this additional entry-point into its
;;; processing for the instances when you already have a string but
;;; want it manipulated with the same set of options as twrite-symbol-
;;; name provides. This comes up when internationalizing messages.
;;; (ddm 4/17/97)

(defun twrite-string-as-attribute-name (string
                                        which-characters-not-to-downcase?
                                        substitute-spaces-for-hyphens?
                                        character-to-add-at-end?
                                        acronym-list?)

  (loop with string-length = (wide-string-length string)
        with new-wide-string
          = (make-stringw
              (if character-to-add-at-end? (+f string-length 1) string-length))
        with indices-of-word-delimiters = nil
        with do-not-downcase-after-ordinary-character?
          = (eq which-characters-not-to-downcase? :all)
        with i = 0
        with do-not-downcase-next-character? = which-characters-not-to-downcase?
        with character
        until (>=f i string-length)
        do (setq character (charw string i))
           (setf (charw new-wide-string i)
                 (wide-character-case character
                    (#.%\-                ; Consider other Unicode hyphens!! (MHD 11/15/95)
                       (when acronym-list?
                         (gensym-push i indices-of-word-delimiters))
                       (setq do-not-downcase-next-character?
                             (if which-characters-not-to-downcase?
                                 (not (eq which-characters-not-to-downcase? :first))))
                       (if substitute-spaces-for-hyphens? #.%space character))
                    (t (cond
                         ((char=w character #.%space) ; use blank-p?!
                          (when acronym-list?
                            (gensym-push i indices-of-word-delimiters))
                          (setq do-not-downcase-next-character?
                                (if which-characters-not-to-downcase?
                                    (not (eq which-characters-not-to-downcase? :first))))
                          character)
                         (do-not-downcase-next-character?
                             (setq do-not-downcase-next-character?
                                   do-not-downcase-after-ordinary-character?)
                           character)
                         (t (setq do-not-downcase-next-character?
                                  do-not-downcase-after-ordinary-character?)
                            (char-downcasew character))))))
           (incff i)
        finally
          (if character-to-add-at-end?
              (setf (charw new-wide-string string-length)
                    character-to-add-at-end?))
          (when acronym-list?
            (gensym-push string-length indices-of-word-delimiters)
            (setq indices-of-word-delimiters
                  (nreverse indices-of-word-delimiters))
            (loop for delimiter-index in indices-of-word-delimiters
                  with start-index = 0
                  for word-length = (-f delimiter-index start-index)
                  do
              (loop for acronym in acronym-list?
                    do
                (when (and (=f (wide-string-length acronym) word-length)
                           (loop for word-i from start-index
                                 for acronym-i from 0 below word-length
                                 always
                                 (eqlw (char-upcasew
                                         (charw new-wide-string word-i))
                                       (char-upcasew
                                         (charw acronym acronym-i)))))
                  (loop for word-i from start-index below delimiter-index
                        do
                    (setf (charw new-wide-string word-i)
                          (char-upcasew (charw new-wide-string word-i))))))
              (setq start-index (1+f delimiter-index)))
            (reclaim-gensym-list indices-of-word-delimiters))
          (twrite-general-string new-wide-string)
          (reclaim-wide-string new-wide-string)))

;; TODO: Acronym lists in use have to be converted to lists with wide strings!



;;; The global property name `symbol-name-wide-string' caches the wide-string
;;; version of a symbol's print name on that symbol's property list.

(def-global-property-name symbol-name-wide-string)

(defun-simple get-or-make-symbol-name-wide-string (symbol)
  (or (symbol-name-wide-string symbol)
      (setf (symbol-name-wide-string symbol)
            (make-symbol-name-wide-string symbol))))

(defmacro get-or-make-symbol-name-wide-string-macro (symbol)
  (let ((symbol-var (gensym)))
    `(let ((,symbol-var ,symbol))
       (or (symbol-name-wide-string-macro ,symbol-var)
           (setf (symbol-name-wide-string ,symbol-var)
                 (make-symbol-name-wide-string ,symbol-var))))))

;; NOTE: Later, this must decode encoded (likely using UTF-8) name strings.  THIS
;; IS IMPORTANT!! (Not deferrable beyond when you want, say, Japanese symbols to
;; be possible.)  (MHD 11/15/95)



;;; `Symbol-namew' is like Common Lisp's symbol-name accessor except that it
;;; returns a wide string symbol name.  Note that it may have to cons it up,
;;; but it keeps it around forever after that.  It should never be reclaimed
;;; or mutated.

(defun-simple symbol-namew (symbol)
  (get-or-make-symbol-name-wide-string symbol))

;; name ok?!




;;; The constant `gensym-symbol-encoding-method' decides the implementation
;;; parameter for the encoding of symbols.  This can in principle have values
;;; such as GENSYM-STRING, UTF-8, or UTF-7.
;;;
;;; The GENSYM-STRING just uses the classic gensym-string, or UTF-G, encoding in
;;; strings, and is compatible with what we've done in all releases through the
;;; most recent before the switch to Unicode, 4.0
;;;
;;; The UTF-8 and UTF-7 are international draft standard publicly advocated for
;;; use in various contexts by the Unicode consortium.  (Documents available
;;; at the Unicode web site, http://www.unicode.com/.)
;;;
;;; For now, only GENSYM-STRING is supported.  The plan is to consider a move
;;; UTF-8 to UTF-7 or UTF-8 at some point in the future.  No matter which of the
;;; 3 plans, all ASCII characters except for @, \, ~, =, and + would exist
;;; unaltered in the symbol names of symbols.
;;;
;;; Note that under the GENSYM-STRING encoding method, we can handle even
;;; Unicode characters that could not be handled under the old Gensym
;;; (4.0/classic) encoding method.  See the specs for UTF-G for further
;;; information.




;;; `Make-symbol-name-wide-string' translate the symbol name of symbol
;;; into a Unicode-encoded wide string.  This makes a fresh wide string
;;; that it is caller's responsibility to reclaim.

(defun-simple make-symbol-name-wide-string (symbol)
  #-chestnut-trans
  (gensym-string-to-wide-string (symbol-name symbol))
  #+chestnut-trans
  (let ((gensym-string (gensym-symbol-name symbol)))
    (prog1 (gensym-string-to-wide-string gensym-string)
      (reclaim-gensym-string gensym-string))))


;; Do the encoding/decoding methods for of symbol names using UTF-8 & UTF-7!





;;;; Writing Wide Characters



;;; `Twrite-wide-character-in-available-buffer-space' is the lowest level
;;; subprimitive for writing a wide character.  This is only to be used by
;;; intra-module primitives.
;;;
;;; It is to be called when it is known that current-wide-string has space
;;; available for at least one wide character at the position indexed by
;;; fill-pointer-for-current-wide-string.
;;;
;;; It fills that position with wide-character, and then increments
;;; fill-pointer-for-current-wide-string.

(defmacro twrite-wide-character-in-available-buffer-space (wide-character)
  `(progn
     (setf (charw current-wide-string fill-pointer-for-current-wide-string)
           ,wide-character)
     (incff fill-pointer-for-current-wide-string)))




;;; `Twrite-wide-string-in-available-buffer-space' is the lowest level
;;; subprimitive for writing a sequence of wide characters from wide-string.
;;; This is only to be used by intra-module primitives.
;;;
;;; It is to be called when it is known that current-wide-string has space
;;; available for at least the number of characters between start and end at the
;;; position indexed by fill-pointer-for-current-wide-string.
;;;
;;; It fills that position with those wide characters, and then increments
;;; fill-pointer-for-current-wide-string by the difference between start and
;;; end.

(defmacro twrite-wide-string-in-available-buffer-space (wide-string start end)
  (avoiding-variable-capture (wide-string start end)
    `(progn
       (copy-portion-of-wide-string-into-wide-string
         ,wide-string ,start ,end
         current-wide-string fill-pointer-for-current-wide-string)
       (incff fill-pointer-for-current-wide-string
              (-f ,end ,start)))))


;;; `Assure-current-wide-string-available-buffer-space' is the lowest level
;;; subprimitive for checking the available buffer space in the current wide
;;; string and extending it if necessary to give it length at least
;;; minimum-new-total-length.
;;;
;;; This is a non-standard macro in that it may not always evaluate its argument
;;; only once: it may evaluate it twice.  This is done for efficiency, and
;;; callers should be written so that they don't depend on the usual evaluation
;;; protocol.

;;; NOTE: this is currently limited in that when current-wide-string-list is a
;;; cons (i.e., when doing output to a wide string list), it can only accept an
;;; argument one past the last legal index in the current wide string.  Since
;;; this is a subprimitive, primitives using this must for now test for and deal
;;; with this restriction.  This generally means that the optimized string
;;; writing primitives must for now emit their output character by character.

(defmacro assure-current-wide-string-available-buffer-space
    (minimum-new-total-length)
  `(when (not (<f ,minimum-new-total-length ; previously was <=, a fencepost error masked by slop! (MHD 6/14/96)
                  total-length-of-current-wide-string))
     (extend-current-wide-string ,minimum-new-total-length)))


;;; `Twrite-wide-character-macro' writes wide-character into the current wide
;;; string that will eventually be copied to be the value of
;;; twith-output-to-wide-string.  Note that, unlike twrite-char, this does not
;;; handle CL characters, and does not do output to a current gensym string.

;;; `Twrite-wide-character' is a function equivalent to the macro
;;; twrite-wide-character-macro.

(defmacro twrite-wide-character-macro (wide-character)
  `(progn
     (assure-current-wide-string-available-buffer-space
       fill-pointer-for-current-wide-string)
     (twrite-wide-character-in-available-buffer-space ,wide-character)))

(defun-void twrite-wide-character (wide-character)
;  (declare (eliminate-for-gsi))
  (twrite-wide-character-macro wide-character))


;;; `Twrite-char-macro' - see comments for twrite-char in UTILITIES1.
;;; Twrite-char-macro calls twrite-wide-character-macro in the
;;; wide-string-case.  (The name may be confusing because twrite-char
;;; is already a macro, but, again, the -macro here refers to what's
;;; done for wide-characters.)

(defmacro twrite-char-macro (simple-or-wide-character)
  (avoiding-variable-capture (simple-or-wide-character)
    `(if (eq (get-current-twriting-output-type) 'wide-string)
         (twrite-wide-character-macro
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


;;; `twrite-appropriate-char' depends on coercing being unnecessary;
;;; it is assumed that the caller already "knows" whether we are
;;; printing to a wide-string or a gensym-string, and is sending
;;; along the right kind of character to fit into that string.
;;; There are checks done in development, but even though they are
;;; cerrors, they cannot be ignored in distribution.

(defmacro twrite-appropriate-char (simple-or-wide-character)
  (avoiding-variable-capture (simple-or-wide-character)
    #+development
    `(cond
       ((eq (get-current-twriting-output-type) 'wide-string)
        (cond
          ((wide-character-p ,simple-or-wide-character)
           (twrite-wide-character-macro ,simple-or-wide-character))
          (t
           (cerror "Coerce it to a wide character"
                   "twrite-appropriate-char needs a WIDE CHARACTER but was given ~s"
                   ,simple-or-wide-character)
           (twrite-wide-character-macro
             (coerce-to-wide-character ,simple-or-wide-character)))))
       (t
        (cond
          ((characterp ,simple-or-wide-character)
           (twrite-simple-character-to-current-gensym-string
             ,simple-or-wide-character))
          ((wide-character-p ,simple-or-wide-character)
           (cerror "Coerce it to a character"
                   "twrite-appropriate-char needs an (ascii) CHARACTER but was ~
                    given wide character #~s"
                   ,simple-or-wide-character)
           (twrite-simple-character-to-current-gensym-string
             (code-char
               (wide-character-code ,simple-or-wide-character))))
          (t
           (cerror "Twrite 'X'"
                   "twrite-appropriate-char needs an (ascii) CHARACTER but was ~
                    given unknown object #~s"
                   ,simple-or-wide-character)
           (twrite-simple-character-to-current-gensym-string #\X)))))
    #-development
    `(if (eq (get-current-twriting-output-type) 'wide-string)
         (twrite-wide-character-macro
           ,simple-or-wide-character)
         (twrite-simple-character-to-current-gensym-string
           ,simple-or-wide-character))))


;;; `twrite-unicode-character' dispatches based on current-twriting-type,
;;; but assumes that its input is a wide character.

(defmacro twrite-unicode-character (wide-character)
  (avoiding-variable-capture (wide-character)
    #+development
    `(cond
       ((eq (get-current-twriting-output-type) 'wide-string)
        (cond
          ((wide-character-p ,wide-character)
           (twrite-wide-character-macro ,wide-character))
          (t
           (cerror "Coerce it to a wide character"
                   "twrite-unicode-char needs a WIDE CHARACTER but was given ~s"
                   ,wide-character)
           (twrite-wide-character-macro
             (coerce-to-wide-character ,wide-character)))))
       (t
        (cond
          ((wide-character-p ,wide-character)
           (twrite-simple-character-to-current-gensym-string
             (code-char
               (wide-character-code ,wide-character))))
          ((characterp ,wide-character)
           (cerror "Twrite the character"
                   "twrite-unicode-char expects a WIDE character, and coerces ~
                    it unconditionally.  In distribution, giving it ~s will abort G2."
                   ,wide-character)
           (twrite-simple-character-to-current-gensym-string
             ,wide-character))
          (t
           (cerror "Twrite 'X'"
                   "twrite-appropriate-char needs an (ascii) CHARACTER but was ~
                    given unknown object #~s"
                   ,wide-character)
           (twrite-simple-character-to-current-gensym-string #\X)))))
    #-development
    `(if (eq (get-current-twriting-output-type) 'wide-string)
         (twrite-wide-character-macro
           ,wide-character)
         (twrite-simple-character-to-current-gensym-string
           (code-char (wide-character-code ,wide-character))))))



;;; `inside-twriting' - makes things more efficient by (a) only checking
;;; current-twriting-output-type once; (b) avoiding global reads by using
;;; locals for the fill pointer and length-of-current-string.

(defmacro inside-twriting (&body body)
  `(case (careful-get-current-twriting-output-type)
     (wide-string
      (macrolet ((twrite-unicode-character-efficiently (character)
                   `(progn
                      (unless (<f local-fill-pointer
                                  local-length-of-current-string)
                        (extend-current-wide-string local-fill-pointer))
                      (setf (charw current-wide-string local-fill-pointer) ,character)
                      (incff local-fill-pointer))))
        (let* ((local-fill-pointer
                 fill-pointer-for-current-wide-string)
               (local-length-of-current-string
                 total-length-of-current-wide-string))
          ,@body
          (setq total-length-of-current-wide-string local-length-of-current-string)
          (setq fill-pointer-for-current-wide-string local-fill-pointer))))
     (gensym-string
      (macrolet ((twrite-unicode-character-efficiently (character)
                   `(progn
                      (unless (<f local-fill-pointer
                                  local-length-of-current-string)
                        (extend-current-gensym-string))
                      (setf (schar current-gensym-string local-fill-pointer)
                            (code-char (wide-character-code ,character)))
                      (incff local-fill-pointer))))
        (let* ((local-fill-pointer
                 fill-pointer-for-current-gensym-string)
               (local-length-of-current-string
                 total-length-of-current-gensym-string))
          ,@body
          (setq total-length-of-current-gensym-string local-length-of-current-string)
          (setq fill-pointer-for-current-gensym-string local-fill-pointer))))
     (t
      #+development
      (cerror "Return nil"
              "Cannot use inside-twriting unless inside of a twith-output-to-....")
      nil)))





;;;; Reader for Wide Strings




;;; A wide string is read in by the Lisp reader upon encountering series of
;;; letters enclosed by #w"...".  Apart from the #w prefix, the syntax for
;;; string tokens follows the Java language spec quite closely.
;;;
;;; The characters \ and " must be escaped if they are to become elements,
;;; literally, of the string.  An arbitrary character may be expressed as the
;;; backslash (\), followed by one or more occurances of the letter U (in
;;; either upper- or lower-case), followed by four hex digit representing the
;;; code of the desired character.  The format syntax is
;;;
;;;   \{u|U}+HHHH
;;;
;;; where {, |, }, +, and H are metasymbols with their usual meanings.  Note
;;; that the Java spec allows one or more U's. we support this for
;;; compatibility, though the reasons probably don't particularly apply at this
;;; time. See Java documentation for the spec and its rationales.

;;; We currently do not support "\b" or "\n" style shorthand for control
;;; characters.  These may get added in the future.

;;; `Read-wide-string' is the function that implements the reader.  It is only
;;; to be called (indirectly) by the Lisp READ function calling through its read
;;; table.  The code that sets up the read tables for this call is at the end of
;;; this file.

;; The ANSI spec allows both Hex (\xh[h[h[h[...]]]]) and Octal (\o[o[o]])
;; escapes, where h and o are hex and octal digits respectively.  Both escapes
;; terminate after the first non-digit past the first.  The hex escape can go
;; on indefinitely, producing an indefinitely large integer (although only a
;; 16-bit integer would be valid in wide strings).  The octal escape terminates
;; after the third octal digit, producing at most a 9-bit integer.  This is all
;; just rehashed from the spec.  The spec is clearly funky, especially around
;; termination of the escape sequence, but at least it's a standard.  We decided
;; not to use this.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun read-wide-string (stream subchar arg)
  (declare (ignore subchar arg))
  (twith-output-to-wide-string
    (macrolet ((extend-buffer (chw)
                 `(twrite-wide-character ,chw))
               (char-to-wide-character (ch)
                 `(code-wide-character (ascii-char-code ,ch)))
               (get-character ()
                 `(read-char stream t nil t)))
      (unless (char= (get-character) #\") (error "#w syntax error"))
      (loop with state = 'normal
            with unicode-digit-count = 0
            with unicode-value = 0
            for ch = (get-character)
            do
        (cond
          ((eq state 'normal)
           (cond ((char= ch #\\)
                  (setf state 'escape))
                 ((char= ch #\")
                  (RETURN))                ; only loop exit point
                 (t
                  (extend-buffer (char-to-wide-character ch)))))
          ((eq state 'escape)
           (cond ((or (char= ch #\U)
                      (char= ch #\u))
                  (setf state 'unicode-U)
                  (setf unicode-digit-count 0)
                  (setf unicode-value 0))
                 (t
                  (extend-buffer (char-to-wide-character ch))
                  (setf state 'normal))))
          ((or (eq state 'unicode) (eq state 'unicode-U))
           (unless (and (eq state 'unicode-U)
                        (cond
                          ((or (char= ch #\U) ; \ {U|u}+ HHHH
                               (char= ch #\u))
                           t)
                          (t
                           (setf state 'unicode)
                           nil)))
             (setf unicode-value
                   (logiorf (ashf unicode-value 4)
                            (or (digit-char-p ch 16) ; digit value
                                (error
                                  "bad embedded unicode char ~c in wide string"
                                  ch))))
             (incff unicode-digit-count)
             (when (=f unicode-digit-count 4)
               (extend-buffer (code-wide-character unicode-value))
                  (setf state 'normal)))))))))
)

;; Updated this to just use twith-output-to-wide-string, which is perfectly
;; efficient.  This way, I won't lose any further time dealing with a limit
;; (4096) on the length of the buffer.  Also, to handle multiple u's, as in
;; \uuu00FF, per the Java spec. (MHD 6/10/96)


;; #w"" wide strings may be read in only after this module.




;;;;
;; ;;;; Plan for Converting Gensym Software to Unicode
;;
;;
;; ;;; #+Wide-Strings Feature.
;; ;;;
;; ;;; This will be put in various spots to handle the incremental conversion.  But
;; ;;; run-time switching will be mostly used, since it's much easier to develop
;; ;;; and test with this approach.  And where practical or more convenient (e.g.,
;; ;;; throughout editor-specific code), code will just be changed one-way over to
;; ;;; wide strings.
;; ;;;
;; ;;; Text-string will remain an ICP value type for the indefinite future.
;; ;;;
;; ;;; Wide-string will eventually be a new ICP value type.  But not for now. See
;; ;;; text-line.
;; ;;;
;; ;;; Text-line Data Abstraction.
;; ;;;
;; ;;; A text-line is the gensym-string element in a text in 4.0.  In 5.0
;; ;;; this will ultimately be a wide string.  For now, it is a union type
;; ;;; of both wide-string and gensym-string.
;; ;;;
;; ;;; Text-line will change from being an ICP value type equivalence for
;; ;;; gensym-string to being equivalent to wide-string.  Up till now (i.e., in 4.0)
;; ;;; it was a value type equivalence.
;; ;;;
;; ;;; Text-line is used for text rendering over Telewindows.
;; ;;; Text-line will stop being an ICP value-type-equivalence for gensym-string,
;; ;;; and will now become its own ICP value type, one that can write either a
;; ;;; text string or wide string, but always reads a wide string.
;; ;;;
;; ;;;
;; ;;; Runtime Enabling Feature.
;; ;;;
;; ;;; In addition to the read-time feature, the macros if-wide-strings and
;; ;;; if-wide-strings-if will enclose code during the transition.
;; ;;;
;; ;;; `IF-WIDE-STRINGS' runs the then clause if #+wide-strings is on, and
;; ;;; `wide-strings-enabled-globally?' -- a run-time enabling variable -- is true;
;; ;;; otherwise, it runs the then clause.
;; ;;;
;; ;;; `IF-WIDE-STRINGS-IF' takes a condition and runs the then clause if
;; ;;; #+wide-strings is on, and wide-strings-enabled-globally?, and the condition
;; ;;; is true.
;; ;;;
;; ;;;
;; ;;; Twrite, Twrite-char, Tformat, etc.
;; ;;;
;; ;;; All of the twrite functions and macros, called to emit text to the
;; ;;; current output gensym-string, will be changed to emit to the current
;; ;;; output wide-string.  A global variable, current-twriting-output-type
;; ;;; will be bound to either GENSYM-STRING or WIDE-STRING.
;; ;;;
;; ;;;
;; ;;; Tformat-gensym-string will not be changed.  Tformat-wide-string will be
;; ;;; written and substituted. Tformat-gensym-string will still emit a text string.
;; ;;; Tformat-wide-string will emit a wide string.
;; ;;;
;; ;;;
;; ;;; Interned Symbol Representation Using UTF-8
;; ;;;
;; ;;; All symbols will be in the Unicode character set.  But for compatibility
;; ;;; with Common Lisp and with ASCII, they will be encoded using the UTF-8
;; ;;; encoding of Unicode.  This uses ASCII for all ASCII characters, and uses
;; ;;; 8-bit characters to represent all Unicode characters in from 1 to 9
;; ;;; characters per Unicode character.
;; ;;;
;; ;;; Intern-wide-string will be written in order to go from Unicode pure-16-bit
;; ;;; byte representation to UTF-8.
;; ;;;
;; ;;; Symbol-namew (or some such) will return a (shared/cached/constant) wide
;; ;;; string.
;; ;;;
;; ;;; Source Text.  Reduce-noting-source-position and friends could be
;; ;;; troublesome.  They did not store logical character indexes, so if any of
;; ;;; them were saved, which I think some were, they'll have to be changed when
;; ;;; the text strings are changed to wide strings.  Fortunately there's an
;; ;;; operation for doing this: convert-text-to-wide-text [removed -- no longer needed].
;; ;;;
;; ;;;
;; ;;; Other Issues/To Do
;; ;;;
;; ;;; Interface to KFEP (Kanji/Japanese FEP) through strings.
;; ;;;
;; ;;; Interface to HFEP (Hangul/Korean FEP) through strings.
;; ;;;
;; ;;; Strings in pathname system (parser for pathnames, etc.)
;; ;;;
;; ;;; Strings in authorization system (machine id, etc.)
;; ;;;
;; ;;; Interface to token reader through strings: read-symbol-from-gensym-strings,
;; ;;; et al.; what to do if token reading buffer gets too big (huge); punctuation
;; ;;; a-list cleanup for Unicode; extensions to alphabetic/numeric classifications
;; ;;; for Unicode in G2?
;; ;;;
;; ;;; The definition of G2 Symbols must be revised for Unicode.  For example, we
;; ;;; don't want to/can't allow ALL "Kanji" (i.e., JIS X 0208, KS C 5601, and ISO
;; ;;; 8859-5 (Cyrillic)) be used without quoting in symbols.  Similarly, we have a
;; ;;; slew of new characters, some of which should and some of which should not be
;; ;;; allowed in symbols without quoting.  Review the secion "G2 symbols" in
;; ;;; characters, and the section in this module dealing with "G2 Symbols and Wide
;; ;;; Strings".  This will probably take another 1/2 day to get in pretty good
;; ;;; shape.
;; ;;;
;; ;;; Def-tokenizer and users, in particular the number reader: to convert this to
;; ;;; either a union type (ala text-line) or straight over to wide strings
;; ;;; (Unicode) will probably take 2 days.  But it's deferrable for now: we just
;; ;;; translate wide strings to text strings prior to number token reading.
;; ;;;
;; ;;; Note that the "old" tokenizer for numbers has not being used apparently
;; ;;; since 1991.  At this point it should be flushed.  I'm not going to even
;; ;;; conditionally call it in new code that reads tokens using wide strings.
;; ;;; See [new-]get-next-numeric-token-from-text.
;; ;;;
;; ;;; Per the following, if we go with it, I'll have to fix the writer to properly
;; ;;; emit wide string readably.  Right now it's broken according to this note.
;; ;;;
;; ;;;   Date: Fri, 1 Dec 95 00:42:53 EST
;; ;;;   From: mhd (Mark H David)
;; ;;;   To: jh
;; ;;;   Subject: fine point on the C string syntax
;; ;;;   Cc: jed
;; ;;;
;; ;;;   This is mostly an output issue, but I'll throw it out there.  Also, do we really
;; ;;;   want to live with this whole C bogosity?!  Is this a pointless "standard" to
;; ;;;   follow?
;; ;;;
;; ;;;   Note 1: I don't think we intend to follow the C string rule that literal
;; ;;;   newlines are not allowed in the input stream in the middle of reading a string.
;; ;;;
;; ;;;
;; ;;;
;; ;;;   Note 2: An approach to the ambiguity problem discussed in the C spec around hex
;; ;;;   \x escapes.
;; ;;;
;; ;;;   If you are writing a string constant in your code, or you're an output function
;; ;;;   emitting a sequence of characters in a readable format, you need to keep track
;; ;;;   of whether the previous character was written using the \x escape.
;; ;;;
;; ;;;   If so, and if the current character is the ASCII code for 0..9 or a..z or
;; ;;;   A..Z, then it should not be output straight.
;; ;;;
;; ;;;   Instead, it should be output using a full 3-digit octal escape.  After this,
;; ;;;   characters can be output literally.
;; ;;;
;; ;;;   Example:
;; ;;;
;; ;;;   Say your string has these five 8- or 16-bit bytes:  #xABCD 'a' 'b' 'c' 'd'
;; ;;;
;; ;;;   You should write this as follows:
;; ;;;
;; ;;;     "\xABCD\141bcd"
;; ;;;
;; ;;;   The first escape, \xABCD, is a hex value, and is delimited on the right by the
;; ;;;   second escape, \141, which is self-delimiting after 3 octal digits.  (#o141 is
;; ;;;   'a'.)  If you wrote this as "\xABCDabcd", it would be interpreted as a string
;; ;;;   one long consisting of the 32-bit number #xabcdabcd, which would be an error
;; ;;;   anyway.
;; ;;;
;; ;;;
;; ;;;   Mark
;; ;;;
;; ;;;
;; ;;; TWRITE-GENERAL-STRING: this will changed for now to handle both wide strings and text
;; ;;; strings.  Thus, "string" here is a union type, ala text line.  Note that with
;; ;;; 1259 uses of twrite-general-string, this is the most practical plan.
;; ;;;
;; ;;; Various stats:
;; ;;;
;; ;;; occurances of "\#": 1991
;; ;;; occurances of char-code: 166
;; ;;; occurances of code-char: 88
;; ;;; occurances of "(Char": 1522
;; ;;; occurances of "(Tchar": 48
;; ;;; occurances of "twrite-general-string": 1259
;; ;;;
;; ;;;
;; ;;;
;; ;;; Joe and I lately agreed that we should probably go for making the gensym
;; ;;; encoding be a "UTF" (ala "UTF-G"; which see, below), but this is to be
;; ;;; done.
;; ;;;
;; ;;;
;; ;;; An apparent bug: (gensym-character-pair-to-code #\W #\~) doesn't work --
;; ;;; fails the assertion!  (Manifested with this and several other character
;; ;;; while loading FLOW.KB.)  Needs diagnosis -- I couldn't understand right
;; ;;; off the bat why this should occur. (12/95)
;; ;;;
;; ;;; THE CURRENT STATE: KBs load in and turn the texts of text boxes and tables
;; ;;; into "wide texts".  They seem live to pretty well with like that under
;; ;;; superficial testing.  Some code was sketched to write out the wide strings
;; ;;; to KBs, but this has not been finished, and will need work/testing.  (A
;; ;;; new element type with character prefix $ is used to write wide strings,
;; ;;; as opposed to text strings.)  All editing/formatting is done using wide
;; ;;; strings.  However, it will be hairy to get things to use wide strings
;; ;;; as the token type rather than strings.  This currently plagues the save-KB
;; ;;; dialogue, for example.  (MHD 12/24/95)
;;
;;
;;
;;
;; (defvar wide-strings-enabled-globally? t)
;;
;; (defmacro if-wide-strings-if
;;     (condition-to-be-evaluated-if-wide-strings
;;       condition-and-wide-strings-case
;;       &optional non-wide-strings-or-failed-condition-case)
;;   `(cond
;;      #+wide-strings
;;      ((and ,condition-to-be-evaluated-if-wide-strings
;;            wide-strings-enabled-globally?)
;;       ,condition-and-wide-strings-case)
;;      (t
;;       ,non-wide-strings-or-failed-condition-case)))
;;
;; (defmacro if-wide-strings
;;     (wide-strings-case &optional non-wide-strings-case)
;;   `(cond
;;      #+wide-strings
;;      (wide-strings-enabled-globally?
;;       ,wide-strings-case)
;;      (t
;;       ,non-wide-strings-case)))
;;
;;
;;
;;
;;
;;
;;
;; (defun twrite-if-wide-string-function (x)
;;   (when (if-wide-strings
;;           (wide-string-p x)
;;           nil)
;;     (twrite-wide-string x)
;;     t))


(defmacro xor-hash-expr (accumulator code shift)
  (let* ((backshift (- 28 shift))
         (mask (1- (ashf 1 backshift))))
    `(setq ,accumulator
           (logxorf (+f (ashf (logandf ,accumulator ,mask) ,shift)
                        (ashf ,accumulator ,(- backshift))) ,code))))

;;; The simple function `hash-wide-string' takes a wide-string and returns a 28
;;; bit positive fixnum.

(defun-simple hash-wide-string (wide-string)
  (loop with accumulator fixnum = 0
     for index from 0 below (wide-string-length wide-string)
     do
     (xor-hash-expr accumulator (char-codew (charw wide-string index)) 7)
     finally (return accumulator)))




;;; The simple function `sxhashw' is like sxhash, but it hashes wide strings
;;; using text-string-hash, and hashes anything else using sxhash.

(defun-simple sxhashw (thing)
  (cond
    ((wide-string-p thing)
     (hash-wide-string thing))
    (t
     #+chestnut-trans
     (current-system-case
       (gsi (sxhash-symbol thing))
       (t (sxhash thing)))
     #-chestnut-trans
     (sxhash thing))))







;;;; Other Things to Consider/Design Notes

;;; Have wide-character be a union type of 16-bit-integer and character.  Then
;;; characters of a string could be easily compared with wide characters.
;;;
;;; Advantages:
;;;
;;;   CASE works for match dispatching because

;;;   EQL works for comparison
;;;   #\ reader macros would be able to remain in the code unchanged
;;;     (1991 uses of the #\ reader macros are in /bt/.../*.lisp)
;;;
;;;
;;; Maybe drop the idea of a "unicode string" in favor simply a "wide character
;;; string".  It's a little problematic to give a string a specific type for a
;;; general element type, and unicode characters are not distinguishable as
;;; a type from the more general "wide character" type.
;;;
;;;
;;; Maybe really go with the idea of a structure all the time for wide character
;;; strings.  This way, you could freely swap in and out the internal buffer
;;; without losing the EQ identity of the external object.
;;;
;;; Going one step further, suppose you allowed the internal buffer to be a
;;; regular (8-bit Lisp character) string.  This would certainly pay back for
;;; the extra cost in structure overhead.
;;;
;;; Note that this is independent of whether we make wide character a union
;;; type: if you didn't, the charw accessor would just have to a be made to
;;; coerce a character to an integer if accessing from a (Lisp) string.
;;;
;;; Higher Level Needs:
;;;
;;;   newline-p (wide-character) => true of new paragraph, new line, CR, or LF
;;;
;;;   horizontal-space-p (wide-character) => true of space, tab, ...
;;;
;;;   blank-p  => true of newline-p or horizontal-space-p
;;;
;;;   graphic-word-separator-p => true of -, _, ...
;;;
;;;   word-separator-p => true of blank-p and hyphens and underscores





;;;; Revived Plan (of changing the implementation of text-string from string to
;;;; wide-string)

;; The plan of changing the implementation of text-string from string to
;; wide-string has been abandoned, and then revived.  Here's the commented-out
;; beginnings of that abandoned plan:
;;
;; The plan continues: a new datatype will be used in all of the places that used
;; text-string to mean "string of Lisp characters":
;;
;;   Need: Replacement for "text-string": e.g., gensym-string, lisp-string,
;;          ascii-string, octet-string, string, simple-string, character-string,
;;          char-string, ...
;;
;;  Need: Replacement for the "T" prefix, e.g., in tchar, twrite, tformat, etc.
;;
;;  Think carefully: do we want to get rid of tchar (for this use), and get rid
;;  of simple strings right now?  That's a double jump -- ok?
;;
;; Can both kinds of strings be in KBs?  Note that strings appear in a few more
;; places than slots: initial and final plist for example.
;;
;; One cool thing possible: use tchar instead of charw (but get rid of the 3rd arg).
;; Consider also: text-string-length, or tlength, throughout.  Consider just going
;; back to the "T" prefix throughout, but this time really nailing it down.  And
;; now a tchar gets any (Unicode) char, and tlength or text-string-length gets the
;; logical length, not the physical.
;;
;;


;;;; Wide-string Replacements for Basic Text-String Operations Previously in Utilities



(defun-simple obtain-simple-text-string (length)
  (make-stringw length))


(defun-void reclaim-simple-text-string (simple-text-string)
  (reclaim-wide-string simple-text-string))

;; NOTE: the function obtain-adjustable-text-string is being used for some
;; obscure purposes. IT WILL FOR NOW RETURN A LISP STRING!  I don't want to deal
;; with it now.  It seems like it can be dealt with later.



;;; `Maximum-text-string-length' ...

;; NOTE: this is not currently enforced by obtain-text-string, et al, but
;; it is used by GSI et al.

(defparameter maximum-text-string-length 1048576)

;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter maximum-text-string-length-exceeded-message
  "Attempting to allocate ~a element string, ~
   which is beyond the established maximum of ~a.")
)

(defmacro body-of-maximum-text-string-length-error (length)
  `(current-system-case
     ((ab telewindows)
      (error ,maximum-text-string-length-exceeded-message
                 ,length
                 maximum-text-string-length))
     (gsi (signal-gsi-maximum-text-string-length-error
            ,length
            maximum-text-string-length))))

(defun-simple maximum-text-string-length-error (length)
  (body-of-maximum-gensym-string-length-error length))

(defun obtain-text-string (length)
  (make-stringw length))

;; Consider making a macro -- but must deal with Lisp module loading issues.


(defun-void reclaim-text-string (text-string)
  (reclaim-wide-string text-string))

(def-substitution-macro reclaim-if-text-string (thing)
   (if (stringpw thing)
       (reclaim-wide-string thing)))

(defun reclaim-if-text-string-function (thing)
  (reclaim-if-text-string thing))

#+development
(defun outstanding-wide-strings ()
  (outstanding-byte-vector-16-vectors))


(def-substitution-macro copy-if-text-string (thing)
  (if (stringpw thing)                        ; or stringp!!? (MHD 11/15/95)
      (copy-text-string thing)
      thing))

;;
;; Consider adding this declaration for the next function, as was there in
;; the days of the old implementation:
;;
;; (declare-side-effect-free-function copy-text-string)

(defun-simple copy-text-string (string)
  ;; "String may be any type of (Common Lisp) string or any type of text
  ;; string." -- copy-as-wide-string handles this as well.
  (copy-as-wide-string string))

;; Consider adding this declaration for the next function, as was there in
;; the days of the old implementation:
;;
;; (declare-side-effect-free-function copy-partial-text-string)

(defun-simple copy-partial-text-string (string part-length)
  ;; "String may be any type of (Common Lisp) string or any type of text
  ;; string." -- copy-as-wide-string handles this as well.
  (copy-partial-wide-string string part-length))



;;; `Copy-portion-of-string-into-simple-text-string' ... really obsolete.
;;; Copy-portion-of-string-into-text-string is equivalent, and is now preferred.

(defun copy-portion-of-string-into-simple-text-string
       (source-string source-start source-end
        destination-string destination-start)
  (copy-portion-of-string-into-text-string
    source-string source-start source-end
    destination-string destination-start))



;;; `Copy-portion-of-string-into-text-string' ... source-string may be either a
;;; gensym-string or a text-string.

(defun-void copy-portion-of-string-into-text-string
    (source-string source-start source-end
                   destination-string destination-start)
  (cond
    ((gensym-string-p source-string)
     (copy-portion-of-gensym-string-into-wide-string
       source-string source-start source-end
       destination-string destination-start))
    (t
     (copy-portion-of-wide-string-into-wide-string
       source-string source-start source-end
       destination-string destination-start))))

;; Copy-portion-of-string-into-simple-text-string doesn't return anything
;; different than its nonsimple counterpart, since we don't really have an
;; implementation of simple wide strings with optimized access.



;;; `Copy-portion-of-text-string-into-text-string-given-count'
;;; source-string must be a text-string.

(defun-void copy-portion-of-text-string-into-text-string-given-count
    (source-string source-start destination-string destination-start
                   count-of-chars-to-copy)
  (cond
    ((eq source-string destination-string)
     (dwarn "Warning: source-string is eq to destination string.~%~
             copy-portion-of-text-string-into-text-string-given-count ~
             was not written to handle that efficiently.")
     (let ((new-source-string (copy-text-string source-string)))
       (copy-byte-vector-16-portion
         new-source-string source-start destination-string destination-start
         count-of-chars-to-copy)
       (reclaim-text-string new-source-string)))
    (t
     (copy-byte-vector-16-portion
       source-string source-start destination-string destination-start
       count-of-chars-to-copy))))





;;; `Copy-portion-of-gensym-string-into-wide-string' copies the specified
;;; characters from source-string, a gensym string, to destination-string,
;;; a wide string.  No useful value is returned.

(defun-void copy-portion-of-gensym-string-into-wide-string
    (source-string source-start source-end
                   destination-string destination-start)
  (macrolet ((do-inner-loop (accessor)
               `(loop as i from source-start below source-end
                      as j from destination-start
                      do (setf (charw destination-string j)
                               (code-wide-character
                                 (ascii-char-code
                                   (,accessor source-string i)))))))
    (cond
      ((simple-gensym-string-p source-string)
       (do-inner-loop schar))
      (t
       (do-inner-loop char)))))




;;; `Copy-text-string-with-case-conversion', like copy-text-string, allows both
;;; a text-string and a gensym-string string argument.  This returns a new text
;;; string with the specified case conversion.

(defun-simple copy-text-string-with-case-conversion
       (string which-characters-to-upcase?)
  (declare (eliminate-for-gsi))
  (copy-wide-string-with-case-conversion string which-characters-to-upcase?))

;;; `Capitalize-text-string-in-place' mutates its text-string argument such that
;;; the first character, if any, is upcased.  `Downcase-text-string-in-place'
;;; and `upcase-text-string-in-place' mutate their text-string argument such
;;; that all characters are downcased and upcased, respectively.

(defun-void capitalize-text-string-in-place (text-string)
  (when (>f (lengthw text-string) 0)
    (setf (charw text-string 0)
          (char-upcasew (charw text-string 0)))))

(defun-void downcase-text-string-in-place (text-string)
  (loop for i from 0 below (lengthw text-string)
        as character = (charw text-string i)
        do (setf (charw text-string i)
                 (char-downcasew character))))

(defun-void upcase-text-string-in-place (text-string)
  (loop for i from 0 below (lengthw text-string)
        as character = (charw text-string i)
        do (setf (charw text-string i)
                 (char-upcasew character))))



(defun copy-symbol-name
       (symbol which-characters-not-to-downcase?
        &optional substitute-spaces-for-hyphens?
                  character-to-add-at-end?
                  acronym-list?)
  (declare (eliminate-for-gsi))
  (copy-symbol-name-as-wide-string
    symbol which-characters-not-to-downcase?
    substitute-spaces-for-hyphens?
    character-to-add-at-end?
    acronym-list?))





(defmacro twith-output-to-text-string (&body body)
  `(twith-output-to-wide-string . ,body))

(defmacro twith-output-to-then-use-of-text-string (&body body)
  `(twith-output-to-then-use-of-wide-string . ,body))

(defmacro twith-output-to-designated-text-string (text-string &body body)
  `(twith-output-to-designated-wide-string ,text-string . ,body))


(defmacro twith-output-to-string-type (string-type &body body)
  (if (constantp string-type)
      (if (eq (eval string-type) 'gensym-string)
          `(twith-output-to-gensym-string ,@body)
          `(twith-output-to-text-string ,@body))
      `(if (eq ,string-type 'gensym-string)
           (twith-output-to-gensym-string ,@body)
           (twith-output-to-text-string ,@body))))






;; in UTILITIES1 still:
;(defvar write-symbols-parsably? nil)
;(defvar write-strings-parsably? nil)

(def-global-property-name length-when-written-parsably)



;;; `Tformat-text-string' ...  The args should be symbols, strings, text
;;; strings, characters, integers, and floats.  They should not be conses,
;;; arrays, rationals, complex numbers, etc.

(defun tformat-text-string
       (control-string
        &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)        ; add more as needed!
  (twith-output-to-text-string
    (tformat control-string arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)))


;;; `Text-string-substring' returns a text string containing the substring of
;;; string given by the start and end arguments.  String may be a Gensym string
;;; (i.e., a Common Lisp) as well as a text string.

(defun-simple text-string-substring (string start? end?)
  (let* ((start (or start? 0))
         (end (or end?
                  (if (gensym-string-p string)
                      (gensym-string-length string)
                      (text-string-length string)))))
    (copy-text-string-portion string start end)))



;;; `Copy-text-string-portion' makes a text-string copy of the part of
;;; string from start below end.  String may be any type of (Common Lisp) string or
;;; any type of gensym string.

(declare-side-effect-free-function copy-text-string-portion)

(defun-simple copy-text-string-portion (string start end)
  (let* ((part-length (-f end start))
         (new-text-string (obtain-text-string part-length)))
    (copy-portion-of-string-into-text-string string start end new-text-string 0)
    new-text-string))


;;; `Read-character-from-text-string' is a macro returns the wide character at
;;; index, and then increments index.  Index should be any generalized variable
;;; expression.

(defmacro read-character-from-text-string (text-string index)
  `(read-character-from-wide-string ,text-string ,index))





;;; `Twrite-ascii-from-gensym-string' ...

(defun-void twrite-ascii-from-text-string (text-string)
  (twrite-ascii-from-wide-string text-string))



;;; `Convert-text-string-to-ascii-as-much-as-possible' ...

(defun-simple convert-text-string-to-ascii-as-much-as-possible (text-string)
  (twith-output-to-text-string
    (twrite-ascii-from-text-string text-string)))



;;; `Convert-gensym-string-to-ascii-filename-as-much-as-possible' ...

(defun-simple convert-text-string-to-ascii-filename-as-much-as-possible
       (text-string)
  (twith-output-to-text-string
    (twrite-ascii-from-text-string text-string)))





;;; The function `copy-text-string-without-newlines' returns text-string with
;;; its newline characters either dropped or turned into spaces according to the
;;; second arg.
;;;
;;; Examples:  (Here, <NL> stands for any Unicode linebreak character.)
;;;
;;;    (copy-text-string-without-newlines "foo<NL>bar" t) => "foo bar"
;;;    (copy-text-string-without-newlines "foo<NL>bar" nil) => "foobar"
;;;    (copy-text-string-without-newlines "foo <NL>bar" t) => "foo  bar" (2 spaces)
;;;    (copy-text-string-without-newlines "foo<NL>bar" nil) => "foo bar" (1 space)
;;;    (copy-text-string-without-newlines "foo bar" t) => "foobar"
;;;    (copy-text-string-without-newlines "foo bar" nil) => "foobar"

(defun copy-text-string-without-newlines (text-string convert-to-spaces?)
  (declare (eliminate-for-gsi))
  (twith-output-to-text-string
    (loop with length = (text-string-length text-string)
          with i fixnum = 0
          with character
          while (<f i length)
          do (setq character
                   (read-character-from-text-string text-string i))
             (cond
               ((newline-p character)
                (when convert-to-spaces?
                  (twrite-char #.%space)))
               (t
                (twrite-char character))))))

;; See copy-gensym-string-without-newlines.


;;; The macro `setf-text' sets place to new-text-string, reclaiming the old one
;;; there, if any.

(defmacro setf-text (place new-text-string?)
  (avoiding-variable-capture (new-text-string? &aux old-text-string?)
    `(let ((,old-text-string? ,place))
       (setf ,place ,new-text-string?)
       (when ,old-text-string?
         (reclaim-text-string ,old-text-string?))
       ,new-text-string?)))


;;;; Dealing with Null-terminated Text Strings




;;; A `null-terminated text string' is a (wide) string that logically ends with
;;; the `null character', i.e., the Unicode/Ascii character named NUL, whose
;;; code is 0.  The operations below are generally written conservately in that
;;; they do not absolutely require null-terminated strings -- their behavior in
;;; the face of non-null- terminated strings is documented below.

;;; Return-text-string-from-null-terminated-string is only to be called from
;;; SEQUENCES1; see copy-null-terminated-string-as-text-string, which does the
;;; much the same thing ... If string is not null-terminated, this simply returns
;;; a copy of string.

(defmacro return-text-string-from-null-terminated-string-1
          (string do-not-reclaim-string-p)
  `(prog1 (text-string-substring
            ,string 0
            (loop with maximum-index = (-f (text-string-length ,string) 1)
                  for i from 0                        ; end of NUL terminated string
                  do
              (when (char=w (charw ,string i) #.%Null)
                (return i))
              (when (>=f i maximum-index)
                (return (+f i 1)))))
          ,@(if (not do-not-reclaim-string-p)
               `((reclaim-text-string ,string)))))

(defmacro return-text-string-from-null-terminated-string
          (string &optional (do-not-reclaim-string-p nil))
  (if (symbolp string)
      `(return-text-string-from-null-terminated-string-1 ,string ,do-not-reclaim-string-p)
      (let* ((string-var '#:string))
        `(return-text-string-from-null-terminated-string-1
           ,string-var
           ,do-not-reclaim-string-p))))





;;; Copy-null-terminated-string-as-text-string copies a null-terminated Gensym
;;; string as a non-null terminated text-string.  If string is not
;;; null-terminated, this simply returns a copy of string.

(defun copy-null-terminated-string-as-text-string (string)
  (let* ((length-if-null-terminated? (length-of-null-terminated-string string)))
    (if length-if-null-terminated?
        (text-string-substring string 0 length-if-null-terminated?)
        (copy-text-string string))))





;;; `Length-of-null-terminated-text-string' ... returns nil if no null character
;;; (i.e., the Ascii character NUL, code 0) is found in string.  Otherwise,
;;; notice that for a result i, (charw string i) is the character NUL.

(defun-simple length-of-null-terminated-text-string (string)
  (loop with string-length = (text-string-length string)
        for i from 0 below string-length
        when (char=w (charw string i) #.%Null)
          return i))

;; Patterned after length-of-null-terminated-string, q.v.

;; Consider having a version that copies a null terminated gensym string as a
;; wide string.






;;; `Copy-null-terminated-text-string' copies all characters in the source
;;; string from the 0th character up to and including the null character into
;;; the target-string?, if non-nil.
;;;
;;; If target-string? is null, this creates a new text string (not
;;; null-terminated) with just the contents of source-string prior to the Null.
;;;
;;; The target string has to be at least the length of the source string.
;;;
;;; The source string can be either a gensym string or a text string. It should
;;; normally be null-terminated, but if not, copying will stop when the end of
;;; the string is reached.
;;;
;;; This returns the resulting string as its only value.

(defun copy-null-terminated-text-string (source-string &optional target-string?)
  (let* ((length                        ; excludes the null
           (if (text-string-p source-string)
               (length-of-null-terminated-text-string source-string)
               (length-of-null-terminated-string source-string)))
         (target-string
          (or target-string?
              (obtain-text-string length))))
    (declare (type fixnum length))
    (copy-portion-of-string-into-text-string
      source-string 0 length
      target-string 0)
    (when target-string?    ; per spec., include Null in this case only
      (setf (charw target-string length) #.%Null))
    target-string))

;; CAUTION: copy-null-terminated-string is the original of this! (MHD 2/5/96)






;; (From the section in UTILITIES3:)

;;; Interning Text Strings and Generating Symbols



;;; `Intern-text-string' is like intern, except that it takes a text-string
;;; which is to be reclaimed unless it is incorporated into the resulting
;;; symbol.

(def-system-variable count-of-interned-text-strings UNICODE 0)
(def-system-variable memory-used-for-interned-text-strings UNICODE 0)

(defun intern-text-string (text-string &optional package?)
  (intern-wide-string text-string package?))

(defun intern-text-string-no-reclaim (text-string &optional package?)
  (intern-wide-string-no-reclaim text-string package?))




;;; The substitution-macro `intern-text-string-substring' returns the symbol in
;;; AB named by the given substring of string.

(def-substitution-macro intern-text-string-substring (text-string start? end?)
  (let ((substring (text-string-substring string start? end?)))
    (intern-text-string substring ab-package-1)))



;;; `Text-string-p' is true if thing is a text string.
;;;
;;; Note that thing should not be a reclaimed text string. Such objects should
;;; generally not be referenced at all, except by the primitive operations on
;;; text strings and subprimitives thereof.  In development, this signals a
;;; continuable error if thing appears to be a reclaimed text string.

(defun-simple text-string-p (thing)
  (wide-string-p thing))

(defmacro text-string-p-macro (thing)
  `(wide-string-p ,thing))




(defmacro text-string-fill-pointer (text-string)
  `(wide-string-fill-pointer ,text-string))

(defmacro adjustable-text-string-p (text-string)
  `(adjustable-wide-string-p ,text-string))

(defmacro text-string-total-length (text-string)
  `(wide-string-total-length ,text-string))


(defun-simple symbol-name-text-string (symbol-name)
  (get-or-make-symbol-name-wide-string symbol-name))

;; NEW:

(defun-simple text-string-length (text-string)
  #+development (test-assertion (text-string-p text-string))
  (wide-string-length text-string))

(defun-simple gensym-string-length (gensym-string)
  (glength gensym-string nil))


(defun-simple copy-symbol-name-parsably (symbol do-not-downcase?)
  (declare (eliminate-for-gsi))
  (let ((length-when-written-parsably?
          (length-when-written-parsably symbol)))
    (if (and length-when-written-parsably?        ; no characters need quoting
             (=f length-when-written-parsably?
                 (lengthw (symbol-name-text-string symbol))))
        (if do-not-downcase?
            (copy-text-string (symbol-name-text-string symbol))
            (copy-symbol-name symbol nil))
        (let ((text-string
                (twith-output-to-text-string
                  (let ((write-symbols-parsably? t))
                    (twrite-symbol symbol do-not-downcase?)))))
          (setf (length-when-written-parsably symbol)
                (text-string-length text-string))
          text-string))))


;;;
;;;
;;;
;;;   string-appendw, substringw
;;;
;;;   string-to-wide-string
;;;
;;;
;;; Wide character loop iteration path:
;;;
;;;    (loop for wide-character being each wide-character of wstring ...)
;;;
;;;    -- alt. to (loop for i from 0 below (wlength wstring)
;;;                     as wide-character = (charw wstring i)
;;;                     ...)
;;;
;;;
;;; Redefine:
;;;
;;;   obtain-simple-text-string  (to create a wide character string)
;;;   text-line-p  (in BOXES; to test Wstringp)
;;;   text-blank-p  (in BOXES; to test if characters blank-p)
;;;   read-gensym-character-from-text-string-with-lost-spaces
;;;     (in FONTS; simpler wstring access)
;;;   simple-text-string-p  (just to be a noop; always return nil)
;;;   skip-past-gensym-character  (just to incff index variable by 1)
;;;   compute-width-of-text-line  (in FONTS; just to use wlength on
;;;     the lost-spaces string)
;;;   tlength  (primitive; make equivalent to wlength & ignore simple-p arg)
;;;   tchar  (primitive; make equivalent to charw & ignore simple-p arg)
;;;   obtain-simple-text-string  (gets a wstring)
;;;   copy-portion-of-string-into-simple-text-string
;;;      (seminoop: wstring -> wstring)
;;;   interface-to-foreign-environment-access !!!!! must do wstring -> c string
;;;     data conversion properly -- means we must make all C sources
;;;     use wchar_t (wide char) type strings!!!!
;;;


;; This will count the output (as a string) of a call to "grep -c ...":
;(defun count-via-grep-output (output-string)
;  (with-input-from-string (in output-string)
;    (loop for line? = (read-line in nil nil)
;          while line?
;          sum (parse-integer line? :start (1+ (position #\: line?))))))








;;;; Unicode Classification Tools


;;; `Def-wide-character-class' ...

(defmacro def-wide-character-class (name &rest classes-or-wide-characters-or-ranges)
  `(progn
     (def-substitution-macro ,(build-ab-symbol name 'p 'macro) (wide-character)
       (or . ,(loop for x in classes-or-wide-characters-or-ranges
                    collect
                    (if (listp x)
                        `(char<=w ',(first x) wide-character ',(second x))
                        (if (symbolp x)
                            `(,(build-ab-symbol x 'p) wide-character)
                            `(char=w wide-character ',x))))))
     (defun-simple ,(build-ab-symbol name 'P) (wide-character)
       (declare (type wide-character wide-character))
       (,(build-ab-symbol name 'p 'macro) wide-character))))


;;; An `ordinary space' is ordinarily subject to widening or narrowing between
;;; words (as opposed to fixed-width space).  It also delimits where words are
;;; normally broken when formatting (as opposed to non-breaking spaces).  The
;;; spaces can also be hidden from view where they occur between lines.

(def-wide-character-class ordinary-space #.%space)


(def-wide-character-class newline
    #.%return
  #.%linefeed
  #.%newline        ; Per CL, may be same as above or different
  ;; how about VT (vertical tab)?
  #.%line-separator
  #.%paragraph-separator)

(def-wide-character-class horizontal-space
    #.%space
  #.%tab                                ; = HT (horizontal tab)
  ;; or char=w to one of the n other space chars in Unicode!
  )


;;; `Text-break-p' is true if wide-character is a `text break character', a
;;; spacing kind of character where a line break is permitted, in particular an
;;; ordinary space, a tab, or one of the following characters in Unicode-Data
;;; format.  Note that this category includes non-spacing characters (e.g.,
;;; zero-width space).
;;;
;;;   00AD;SOFT HYPHEN;Po;0;ON;;;;;N;;;;;
;;;
;;;   2002;EN SPACE;Zs;0;WS;<font variant> 0020;;;;N;;;;;
;;;   2003;EM SPACE;Zs;0;WS;<font variant> 0020;;;;N;;;;;
;;;   2004;THREE-PER-EM SPACE;Zs;0;WS;<font variant> 0020;;;;N;;;;;
;;;   2005;FOUR-PER-EM SPACE;Zs;0;WS;<font variant> 0020;;;;N;;;;;
;;;   2006;SIX-PER-EM SPACE;Zs;0;WS;<font variant> 0020;;;;N;;;;;
;;;   2007;FIGURE SPACE;Zs;0;ES;<font variant> 0020;;;;N;;;;;
;;;   2008;PUNCTUATION SPACE;Zs;0;WS;<font variant> 0020;;;;N;;;;;
;;;   2009;THIN SPACE;Zs;0;WS;<font variant> 0020;;;;N;;;;;
;;;   200A;HAIR SPACE;Zs;0;WS;<font variant> 0020;;;;N;;;;;
;;;   200B;ZERO WIDTH SPACE;Zs;0;WS;;;;;N;;;;;

(def-wide-character-class text-break
    #.%space
  #.%tab
  #u00AD        ; refer to Unicode Data above
  (#u2002 #u200B))

;; Just a first guess -- See original definition in BOXES w.r.t. the "classic" @
;; characters, and see its use.  Try to rationalize this as different from
;; horizontal-space-p and blank-p is possible, or clean up.


(def-wide-character-class blank
  newline
  horizontal-space)

(def-wide-character-class graphic-word-separator
    #.%\-
  #.%\_)

(def-wide-character-class word-separator
    blank
  graphic-word-separator
  ;; or one of the n other characters similar to hyphen in Unicode!
  )


;;; `Non-graphic-character-p' is what the renderer for a line of text uses to
;;; decide if the putting down of any ink or offsetting of the pen should happen
;;; because of this character.  This is at present true only for the vertical
;;; spacing characters (newline).

(def-wide-character-class non-graphic-character
    ;; these are characters that are not graphic characters
    newline
  ;; add directional markers, etc.! fill in from Unicode table!
  ;; include Tab?  but they're already documented as becoming
  )


(def-wide-character-class non-spacing-mark
    (#u02EA #u0373)                        ; Mostly Latin/Greek

    (#u05B0 #u05C2)                        ; Hebrew

    #u0e31                                ; Thai
    (#u0e34 #u0e3a)                        ; Thai
    (#u0e47 #u0e4e)                        ; Thai

  ;; Fix -- do the rest!
  )


(defun-simple alphabetic-p (wide-character)
  (declare (type wide-character wide-character))
  (or
    ;; If it's a letter with case, consider it alphabetic.  Note that this
    ;; accounts for Latin and Cyrillic.
    (not (char=w (char-downcasew wide-character)
                 (char-upcasew wide-character)))

    ;; Hebrew -- include letters and diacritics and some punctuation.
    ;; Interpretation for Hebrew is new in G2 8.0. (MHD 12/22/03)
    (char<=w #u0590 wide-character #u05AF) ; cantillation marks
    (char<=w #u05B0 wide-character #u05Bd) ; points
    (char<=w #u05C1 wide-character #u05C2) ; points
    (char=w #u05C4 wide-character)           ; point
    (char<=w #u05D0 wide-character #u05EA) ; letters
    (char<=w #u05F0 wide-character #u05F2) ; digraphs
    (char<=w #u05F3 wide-character #u05F4) ; punctuation (gershayim)

    ;; Thai -- include consonants, vowels, signs, tone marks, and digits.
    ;; Interpretation for Thai is new in G2 8.0. (MHD 12/22/03)
    (char<=w #u0E01 wide-character #u0E2E) ; consonants
    (char<=w #u0E30 wide-character #u0E3A) ; vowels
    (char<=w #u0E40 wide-character #u0E44) ; vowels
    (char<=w #u0E45 wide-character #u0E46) ; signs
    (char=w #u0E47 wide-character)           ; vowel
    (char<=w #u0E48 wide-character #u0E4B) ; tone marks
    (char<=w #u0E4c wide-character #u0E4f) ; signs
    (char<=w #u0E50 wide-character #u0E59) ; digits
    (char<=w #u0E5a wide-character #u0E5b) ; signs
    ))

;; Heuristic definition -- may not/doesn't always work in all cases! Fix later!



(def-wide-character-class numeric
  (#.%\0 #.%\9))

;; Handle other kinds of numbers per Unicode guidelines?


(def-wide-character-class alpha-numeric
    alphabetic
  numeric)

;; Extend beyond ASCII!!


(def-wide-character-class cjk-unified-ideograph
    (#u4E00 #u9FFF))

(def-wide-character-class hangul-syllable
    (#uAC00 #uD7A3))

(def-wide-character-class obsolete-hangul-syllable
    (#u3400 #u3D2F))

;; Note: this range is defined in Unicode 1.1, and is undefined (you "can't" do
;; that, but they did!) in 2.0.  We can support both for a release or
;; two.... (MHD 10/16/96)

(def-wide-character-class hangul-jamo
    (#u1100 #u11FF))

;; Note there are equivalences that "really _should_" be observed between
;; sequences of hangul jamo and hangul syllables.  We've not yet added support
;; for observing these equivalences, however!  (MHD 10/16/96)


(def-wide-character-class hangul-compatibility-jamo
    (#u3131 #u3184))                        ; note: includes the
                                        ;  special character "HANGUL FILLER"


;; Note that Hiragana and Katakana classes do not include punctuation marks in
;; these scripts, only the "letters".  These do include the extra precomposed
;; katakana, e.g., U+30FA, which are not in JIS X 0208

(def-wide-character-class hiragana
    (#u3041 #u3093))

(def-wide-character-class katakana
    (#u30A1 #u30FA))


(def-wide-character-class bopomofo
    (#u3105 #u312C))





(def-wide-character-class readable-symbolic
    numeric
    alphabetic
    #.%\- #.%\_ #.%\' #.%\.
    cjk-unified-ideograph
    hangul-syllable
    obsolete-hangul-syllable
    hangul-jamo
    hangul-compatibility-jamo
    hiragana
    katakana
    bopomofo)

;; See also (def-built-in-class g2symbol alphabet-g2symbol-chars) in ALPHABET!
;; (MHD 10/16/96)







;;; `G2-Exponent-marker-p' is true if character is an exponent marker in G2 syntax
;;; for floating-point numbers.

(def-wide-character-class g2-exponent-marker
    ;; replacement for exponent-marker-p, which has been in CHARACTERS!
    #.%\e #.%\E)                        ; #.%\s #.%\S #.%\f #.%\F
                                        ;   #.%\d #.%\D #.%\l #.%\L also?





;;; `Word-delimiting-character-p' ...

(defun-simple word-delimiting-character-p (wide-character)
  (declare (type wide-character wide-character))
  (and (not (alpha-numeric-p wide-character))
       (not (chinese-or-hangul-or-kana-p wide-character))))




;;;; Asian Languages, Characters, and Scripts


;;; `Wide-character-is-katakana-jis-code-p' ...

;;; `Wide-character-is-hiragana-jis-code-p' ...

(defmacro wide-character-is-katakana-jis-code-p (wide-character)
  `(char<=w #u30A1 ,wide-character #u30F6))

(defmacro wide-character-is-hiragana-jis-code-p (wide-character)
  `(char<=w #u3041 ,wide-character #u3093))

;; Both Unicode and (old) Gensym character sets for both Hiragana and Katakana
;; are based on JISX208.
;;
;; Note that punctuation marks are not included.
;;
;; Note, however, that Unicode 1.1 has one additional Hiragana character (U+3094
;; HIRAGANA LETTER VI), and four additional Katakana characters (U+30F7->U+30FA
;; KATAKANA LETTER VA, VI, VE, VO) which are not present in the Japanese
;; standard JISX0208, so I'm not including it for now.  This is consistent with
;; the naming of these functions with "-jis", although originally the "-jis" was
;; meant to distinguish JIS from KS (i.e., Korean).  The users of this function
;; use this for functions involving Romaji input and kana-to-kanji conversion,
;; so I'm afraid to change this definition lest these callers break.  (See also
;; "(def-wide-character-class katakana ...)", above.)
;;
;; I sent email to the Unicore list requesting clarification.  Here is further
;; information below from Ken Lunde.  (MHD 7/12/96)
;;
;;   To: mhd@mailhost
;;   Cc: unicore@Unicode.ORG
;;   Subject: Re: HIRAGANA LETTER VU: the 84th Hiragana
;;   Date: Fri, 12 Jul 1996 10:20:46 PDT
;;   From: "Ken Lunde" <lunde@mv.us.adobe.com>
;;
;;   Mark,
;;
;;           You wrote:
;;
;;   >> JIS X0208 - 1990 has 83 Hiragana, but Unicode has 84.
;;
;;           Correct. You must have skipped the other observation that JIS
;;   X 0208-1990 has 86 katakana, but Unicode has 90 (see U+30F7 through
;;   U+30FA).
;;
;;   >> The 84th is U+3094 (HIRAGANA LETTER VU).
;;   >>
;;   >> _The Unicode Standard_, Version 1.0, Volume 1 indicates that
;;   >> the Hiragana block is based on JISX0208.
;;   >>
;;   >> I have been unable to find an explanation as to the origin of
;;   >> this character.  Can someone provide any background information?
;;
;;           These additional kana characters are usually found in vendor
;;   extensions of JIS X 0208-1990. Here are some examples:
;;
;;   o Hiragana VU is in Fujitsu's FMR character set as follows:
;;
;;     - 0x2474 (JIS encoding)
;;     - 0x82F2 (Shift-JIS encoding)
;;
;;     (But, somehow hiragana small KA and small KE were forgotten in
;;     Unicode -- Fujitsu's FMR character set encodes them at 0x2475 and
;;     0x2476).
;;
;;   o Apple's KanjiTalk7 character set encodes hiragana VU and katakana
;;     VA, VI, VE, and VO as follows:
;;
;;     Hiragana VU: 0x8868 (Shift-JIS encoding)
;;     Katakana VA: 0x886A (Shift-JIS encoding)
;;     Katakana VI: 0x886B (Shift-JIS encoding)
;;     Katakana VE: 0x886C (Shift-JIS encoding)
;;     Katakana VO: 0x886D (Shift-JIS encoding)
;;
;;   o There is a note in JIS X 0212-1990 that proposes to add these four
;;     katakana as follows (to JIS X 0212-1990, not to JIS X 0208-1990):
;;
;;     Katakana VA: 0x2577
;;     Katakana VI: 0x2578
;;     Katakana VE: 0x2579
;;     Katakana VO: 0x257A
;;
;;     This immediately after the 86 katakana already in JIS X 0208-1990.
;;
;;   >> I'm interested in things like:
;;   >>
;;   >> to what degree is it necessary for Japanese text entry
;;
;;           Hiragana VU is used very rarely (if ever). Its existence is
;;   made necessary only because katakana VU exists.
;;
;;   >> how it interacts with Kana to Kanji converters
;;
;;           It does not interact with them.
;;
;;   >> Romaji spelling(s)
;;
;;           The four additional katakana would be used to transcribe
;;   foriegn words. I don't see a purpose for hiragana VU except for making
;;   the hiragana set (83 characters in JIS X 0208-1990) conform to the
;;   katakana set (86 characters in JIS X 0208-1990).
;;           Hope this helps...
;;
;;   -- Ken





;;; `Wide-character-is-katakana-p' and `wide-character-is-hiragana-p' include
;;; all of the Hiragana and Katakana from JISX0208, as well as the variant forms
;;; included in Unicode, but not the unassigned characters, punctuation-like
;;; characters, or diacritical-mark characters from these blocks in Unicode.

(defmacro wide-character-is-katakana-p (wide-character)
  `(char<=w #u30A1 ,wide-character #u30FA))

(defmacro wide-character-is-hiragana-p (wide-character)
  `(char<=w #u3041 ,wide-character #u3094))




;;; `Chinese-or-hangul-or-kana-p' is primarily intended to detect characters
;;; that are part of words, i.e., the CJK equivalent of alphabetic characters.
;;;
;;; This returns true iff wide-character is belongs to either (a) CJK Ideographs
;;; Area (U+4E00 - U+9FFF); (b) the new Hangul Syllables Area (U+AC00 - U+D7A3);
;;; (c) the old Hangul Syllables Area (U+3400->3D2F); (d) the Hiragana
;;; characters; or (e) the Katakana characters.
;;;
;;; Note that all elements of the CJK Ideographs Area are included, even though
;;; there are several columns at the end of this area that are not yet assigned
;;; at this time.
;;;
;;; Note that both Unicode 1.1 and 2.0 Hangul characters are included.
;;;
;;; Note that Hiragana and Katakana diacritical and punctuation-like characters,
;;; as well as unassigned characters, are excluded.

(defun-simple chinese-or-hangul-or-kana-p (wide-character)
  (declare (type wide-character wide-character))
  (or (char<=w #u4E00 wide-character #u9FFF) ; Note 1

      (char<=w #uAC00 wide-character #uD7A3) ; Note 2
      (char<=w #u3400 wide-character #u3D2F)

      (wide-character-is-hiragana-p wide-character)
      (wide-character-is-katakana-p wide-character)))

;; Replacement for chinese-or-hangul-or-kana-gensym-character-p, which was
;; overzealous in counting all of JIS and all of KSC and not counting any
;; Chinese characters, since they weren't allowed anyway at the time.  Only user
;; at present is word-like-sequence-in-text-p.  The name should really be
;; changed to indicate that it's searching for a wordlike character. (MHD 7/12/96)

;; Note 1: In 1.0, the range of CJK Ideographs was to be U+4000->U+8BFF, but it
;; was changed to this in 1.1

;; Note 2: In 1.1, the range for Hangul was different (U+3400->3D2F), and much
;; smaller.  That range had the nice property that it was 1:1 with KSC5601.
;; That range is being declared obsolete as of 2.0.  It will probably continue
;; to be supported in denigrated fashion for some years.  Microsoft has pushed
;; for this, so all of their systems should be 2.0 complient immediately.  At
;; this moment, we only handle the old range, and not the new.  We don't have
;; fonts for the new range, for example.  And we don't have a working HFEP that
;; could generate elements of the new range.  We should carefully review and
;; consider whether to import text into the old or new range before we release!
;; We should consider whether to get a new font and a new HFEP before the
;; release.  (MHD 7/12/96)





;;; Map-character-code-to-asian-language returns either nil or a symbol naming
;;; one of the currently supported Asian languages: currently JAPANESE or
;;; KOREAN.
;;;
;;; This is intended as the standard test for whether gensym-character-code is
;;; in an Asian language.

(defun-substitution-macro map-character-code-to-asian-language
    (gensym-character-code)
  (cond
    ((<f gensym-character-code 256)        ; easy quick test
     nil)
    ((legal-gensym-jis-character-code-p gensym-character-code)
     'japanese)
    ((legal-gensym-ksc-character-code-p gensym-character-code)
     'korean)))

(defun-substitution-macro map-language-to-asian-alpahabet-name (language)
  (case language (japanese 'kanji) (korean 'hangul)))


(defun-substitution-macro map-gensym-character-code-to-contiguous-code
    (gensym-character-code language)
  (case language
    (japanese (gensym-jis-code-to-contiguous gensym-character-code))
    (korean (gensym-ksc-code-to-contiguous gensym-character-code))))

(defun-substitution-macro map-gensym-asian-character-code-to-contiguous-code
    (gensym-character-code)
  (map-gensym-character-code-to-contiguous-code
    gensym-character-code
    (map-character-code-to-asian-language gensym-character-code)))









;;;; Gensym Character Stream-like Data Abstraction

;; MHD, 11/8/95


;;; This facility is used to provide a stream-like front end to the original
;;; Gensym character set and its implementation and encoding used in G2/TW 4.0
;;; and earlier versions.  The fact that characters were represented as
;;; sequences of simpler characters, and that there was not atomic
;;; (single-lisp-object) representation for those characters, made text
;;; operations very difficult.  This facility, along with the newly defined
;;; character-code representation for (old) gensym character set elements, and
;;; their mappings to and from the non-atomic ("pair") representation, make
;;; dealing with them much easier.
;;;
;;; NOTE: in this section, CLASSIC-GENSYM-STRING refers to the old representation
;;; of text strings, i.e., as Common Lisp strings, and the old Gensym character
;;; set, and its old multibyte encoding as "complex characters" in text strings.


;;; A `gensym-string stream' is a structure that you make to overlay a stream-like
;;; interface on top of our text strings.  In addition to providing the streams
;;; interface, it also provides characters as atomic codes rather than as pairs
;;; of values.
;;;
;;; Here are the operations defined thus far:
;;;
;;;   (make-gensym-string-stream <string>) ; creates the stream
;;;                                      ;   structure based on <string>
;;;
;;;   (reclaim-gensym-string-stream gensym-string-stream) ; deletes stream (not string)
;;;
;;;   (read-character-code gensym-string-stream) ; returns the next character code
;;;                                            ;   or nil if end-of-file
;;;
;;;   (unread-character-code gensym-string-stream character-code) ; puts it back
;;;
;;;   (peek-character-code gensym-string-stream character-code) ; looks 1 ahead

(def-structure (gensym-string-stream
                 (:constructor make-gensym-string-stream-internal ()))
  gensym-string-stream-data                ; text string
  gensym-string-stream-length                ; fixnum intenger
  gensym-string-stream-has-simple-gensym-string-p ; boolean
  (gensym-string-stream-index 0)                ; fixnum integer, physical gensym string index
  (gensym-string-stream-previous-index? nil) ; nil or the previous index
  (gensym-string-stream-unread-char-index? nil)) ; nil or previous index
                                               ;   for an unread char
(defun make-gensym-string-stream (gensym-string)
  (let* ((stream (make-gensym-string-stream-internal)))
    (setf (gensym-string-stream-data stream) gensym-string)
    (setf (gensym-string-stream-has-simple-gensym-string-p stream)
          (simple-gensym-string-p gensym-string))
    (setf (gensym-string-stream-length stream)
          (glength
            gensym-string
            (gensym-string-stream-has-simple-gensym-string-p stream)))
    (setf (gensym-string-stream-index stream) 0)
    stream))




; (def-generic-structure-method read-character-code (gensym-string-stream))
; (def-structure-method read-character-code (gensym-string-stream))
; (def-structure-method unread-character-code (gensym-string-stream character-code))
; (def-structure-method peek-character-code (gensym-string-stream))
;; The hassles with methods are a drag on developing -- switch to them when
;; the dust settles!

;; This should be remodularized to provide us with a basic stream abstract
;; classes, and various specialized classes for our various storage types and
;; various character sets and encoding methods!

(defun read-character-code (gensym-string-stream)
  (let* ((local-character-index
           (or (gensym-string-stream-unread-char-index? gensym-string-stream)
               (gensym-string-stream-index gensym-string-stream)))
         escape-character? character-or-character-code)
    (cond
      ((=f local-character-index
           (gensym-string-stream-length gensym-string-stream))
       nil)
      (t
       (setf (gensym-string-stream-previous-index? gensym-string-stream)
             local-character-index)
       (setf character-or-character-code
             (read-gensym-character-from-gensym-string
               (gensym-string-stream-data gensym-string-stream)
               local-character-index
               (gensym-string-stream-has-simple-gensym-string-p gensym-string-stream)
               escape-character?))
       (setf (gensym-string-stream-unread-char-index? gensym-string-stream) nil)
       (setf (gensym-string-stream-index gensym-string-stream)
             local-character-index)
       (gensym-character-pair-to-code
         character-or-character-code
         escape-character?)))))

(defun unread-character-code (gensym-string-stream character-code)
  (declare (ignore character-code))
  (setf (gensym-string-stream-unread-char-index? gensym-string-stream)
        (gensym-string-stream-previous-index? gensym-string-stream))
  nil)

(defun peek-character-code (gensym-string-stream)
  (let ((character-code? (read-character-code gensym-string-stream)))
    (when character-code?
      (unread-character-code gensym-string-stream character-code?))
    character-code?))


;; Consider creating a new data type, plaintext, which is an object whose
;; operations are
;;
;;   creation (with data, character set, encoding, read-only-p, ...)
;;   random access read (position)
;;   random access write (position) [unless read-only-p]



(defmacro with-input-from-gensym-string-stream
    ((stream-var gensym-string) &body body)
  `(protected-let ((,stream-var
                      (make-gensym-string-stream ,gensym-string)
                      (reclaim-gensym-string-stream ,stream-var)))
     . ,body))






;;;; String-> Wide-String-> String


;;; `String-to-wide-string' copies string, taken to be an ASCII/ISO Latin1
;;; encoded CL string, as a wide string, using the (compatibile) Unicode
;;; character set.

;;; `Wide-string-to-string' copies wide-string as a simple Lisp string.  Note
;;; that no character set translation take place, and, furthermore, any
;;; non-8-bit Unicode characters are truncated to 8 bits by stripping off any
;;; extra bits.  Wide-string-to-string is guaranteed to return a simple (Lisp)
;;; string.  C.f.  gensym-string-to-wide-string, which does do translation, and
;;; can return a general Lisp string ("gensym string").

(defun-simple string-to-wide-string (string)
  (let* ((length (length string))
         (wide-string (make-stringw (length string))))
    (declare (type fixnum length))
    (copy-portion-of-gensym-string-into-wide-string
      string 0 length wide-string 0)
    wide-string))


(defun-simple wide-string-to-string (wide-string)
  (let* ((length (lengthw wide-string))
         (string (obtain-simple-gensym-string (lengthw wide-string))))
    (declare (type fixnum length))
    (copy-portion-of-wide-string-octets-into-simple-gensym-string
      wide-string 0 length string 0)
    string))











;;;; Miscellaneous CL Operations in Adapted for Text Strings





;;; `Sort-text-string' is like the Common Lisp function sort for the text-string
;;; case, but is guaranteed not to cons.  It performs a stable sort on a text
;;; string.

;;; They currently uses the most trivial of sinking rock sorting algorithms and
;;; mutates its given sequence so that is are ordered least to greatest as
;;; indicated by the less-than-predicate function.

(defun-allowing-keywords sort-text-string
    (text-string less-than-predicate &key key)
  (declare (eliminate-for-gsi))
  (loop for end-point from (-f (text-string-length text-string) 1) downto 1
        do
    (loop for lesser-index from 0 below end-point
          for lesser-elt = (charw text-string lesser-index)
          for greater-index fixnum = (+f lesser-index 1)
          for greater-elt = (charw text-string greater-index)
          do
      (when (if key
                (funcall less-than-predicate
                         (funcall key greater-elt)
                         (funcall key lesser-elt))
                (funcall less-than-predicate greater-elt lesser-elt))
        (setf (charw text-string greater-index) lesser-elt)
        (setf (charw text-string lesser-index) greater-elt))))
  text-string)

;; Adapted from JRA's sort-array function.  Speed up later if necessary!


(defun-simple quicksort-text-string-alphabetically (text-string)
  (declare (eliminate-for-gsi))
  (quicksort-text-string-alphabetically-1
    text-string 0 (1-f (text-string-length text-string)))
  text-string)


(defun-simple quicksort-text-string-alphabetically-1 (s l r)
  (declare (eliminate-for-gsi) (fixnum l r))
  (let ((i l)
        (j r)
        (x (charw s (halff (+f l r)))))
    (declare (type fixnum i j))
    (loop do (loop while (char<w (charw s i) x) do (incff i))
             (loop while (char<w x (charw s j)) do (decff j))
             (when (<=f i j)
               (let ((w (charw s i)))
                 (setf (charw s i) (charw s j))
                 (setf (charw s j) w))
               (incff i)
               (decff j))
          until (>f i j))
    (when (<f l j)
      (quicksort-text-string-alphabetically-1 s l j)
      (quicksort-text-string-alphabetically-1 s i r))))

;; Adapted from Nicklaus Wirth's "Algorithms + Data Structures = Programs".


;;; `Remove-duplicates-in-text-string' is like Common Lisp's remove-duplicates
;;; function, but is adapted for use with text strings.  This always returns a
;;; fresh text string containing just one of each of the elements in its
;;; argument text-string.  The original order is preserved.

(defun remove-duplicates-in-text-string (text-string)
  (twith-output-to-then-use-of-wide-string
    (loop with length = (text-string-length text-string)
          for i from 0 below length
          as char = (charw text-string i)
          unless (loop for j from 0
                             below
                       fill-pointer-for-current-wide-string
                       thereis
                       (char=w char (charw current-wide-string j)))
            do (twrite-char char))
    (copy-current-wide-string)))





;;; The function `concatenate-text-strings' is roughly an analog of the very
;;; generic Common Lisp CONCATENATE function, specialized for the case of two
;;; text-string args with a text-string result. This simply creates a new text
;;; string whose contents are the concatenation of its two argument strings,
;;; text-string-1 and text-string-2, in that order.  Arguments are not reclaimed
;;; nor incorporated into the resulting text string.

(defun-simple concatenate-text-strings (text-string-1 text-string-2)
  (concatenate-wide-strings text-string-1 text-string-2))



;;;; Miscellaneous Gensym-String/Wide-string Coexistence Tools



;;; The variable `base-36-digits-string' is a wide string with the following
;;; contents:
;;;
;;;    0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
;;;
;;; It is used by digit-charw, and is available for use generally.

(defvar base-36-digits-string (stringw "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"))

;; It had to be moved here, away from digit-charw, because it needs to come after
;; stringw in the load order.



#+development
(defparameter digit-charw-testbed
  '((0 2 #.%\0) (1 2 #.%\1)
    (7 2 #.%\?) ; old: nil
    (7 8 #.%\7)
    (8 8 #.%\?) ; old: nil
    (15 16 #.%\f)))

#+development
(defun test-digit-charw ()
    (loop for (a b c) in digit-charw-testbed
          as char? = (digit-charw a b)
          do (assert (if (and c char?) (char-equalw c char?) (eq c char?)))))

#+development
(test-digit-charw)


;commented as not used by SoftServe
(defun reclaim-gensym-string-or-wide-string (gensym-string-or-wide-string)
  (if (gensym-string-p gensym-string-or-wide-string)
      (reclaim-gensym-string gensym-string-or-wide-string)
      (reclaim-wide-string gensym-string-or-wide-string)))

;SoftServe: be aware to uncomment
(defun gensym-string-or-wide-string-p (thing)
  (or (gensym-string-p thing) (wide-string-p thing)))

;commented as not used by SoftServe
(defun reclaim-if-gensym-string-or-wide-string (thing)
  (if (gensym-string-or-wide-string-p thing)
      (reclaim-gensym-string-or-wide-string thing)))


;;; `Twrite-line-separator' is the primitive (used by TFORMAT for the ~%
;;; directive, for example) for emitting a line separator to the current
;;; output string.

(defun twrite-line-separator ()
  (if (eq (get-current-twriting-output-type) 'wide-string)
      (twrite-char #.%line-separator)
      (twrite-char #\newline)
      ;; This is the one major change in behavior for Gensym strings: We used to
      ;; emit UTF-G in this case; in other cases, we really just went with
      ;; straight CL characters, and the UTF-G/Gensym encoding was left as a
      ;; higher level protocol.  In 5.0, we're changing this to an ASCII
      ;; newline.  Review callers/users of this feature, which should be few!
      ;; (MHD 6/4/96)
      ;;
      ;; (progn (twrite-char #\@) (twrite-char #\L))
      ))


;;; `Get-quality-and-revision-of-revision-string' is a subfunction of
;;; get-quality-and-revision-of-system-version, q.v., in BOOTSTRAP.  Its arg,
;;; revision-string, can be either a gensym string or a text string.

;; moved here from BOOTSTRAP:

(defun-allowing-unwind get-quality-and-revision-of-revision-string
    (revision-string)
  (declare (eliminate-for-gsi))
  (protected-let
      ((revision-string-text-string
         (copy-text-string revision-string)
         (reclaim-text-string revision-string-text-string))
       (quality 0)
       (revision 0)
       (index 0)
       (end-index
         (text-string-length
           revision-string-text-string))
       (next-thing? nil))
    (multiple-value-setq (next-thing? index)
      (progn
        (setq index
              (skip-spaces-in-string
                revision-string-text-string
                index end-index))
        (read-symbol-from-string
          revision-string-text-string
          index end-index)))
    (when next-thing?
      (setq quality
            (case next-thing?
              (alpha 1)
              (beta 2)
              (rev. 3)
              (t 0)))                        ; prototype, or "bad"
      (when (and next-thing?
                 (or (eq next-thing? 'rev.)
                     (progn
                       (multiple-value-setq (next-thing? index)
                         (progn (setq index
                                      (skip-spaces-in-string
                                        revision-string-text-string
                                        index end-index))
                                (read-symbol-from-string
                                  revision-string-text-string
                                  index end-index)))
                       (eq next-thing? 'rev.))))
        (multiple-value-setq (next-thing? index)
          (progn
            (setq index
                  (skip-spaces-in-string
                    revision-string-text-string
                    index end-index))
            (read-number-from-string
              revision-string-text-string
              index end-index)))
        (when (and next-thing? (numberp next-thing?))
          (setq revision next-thing?))))
    (values quality revision)))




;;; `Copy-foreign-string-arg-if-appropriate' takes a wide string or a Gensym
;;; string (either simple or non-simple) and checks to see if it is of the
;;; appropriate type for passing to a C foreign function as an arg declared to
;;; be of type string, i.e., required to be a simple Gensym string, i.e., a Lisp
;;; object of type simple-string.
;;;
;;; Given a simple Gensym string, this returns nil, indicating that the string
;;; can be passed straight through, that no copying was necessary, and that no
;;; corresponding reclaim need be done after the call to the C function.
;;;
;;; Given a non-simple string or a wide string, this generally copies the octets
;;; (least signficant 8 bits) of each element of the argument into a newly
;;; allocated simple string that can be passed to C.  In the case of a wide
;;; string, there is one exception to copying the least significant 8 bits: the
;;; Unicode line separator character (#.%line-separator) is translated into the
;;; ASCII linefeed character (#\newline).
;;;
;;; Note that the resulting string may be of greater physical length than the
;;; argument string.  If so, it's guaranteed to have a NUL (code-char = 0)
;;; character one past the end, so that C can tell where the end is if it's
;;; expecting the string to be null-terminated.  The endeavors to obtain a
;;; string of a quantized length (using
;;; obtain-simple-gensym-string-of-quantized-length), thereby facilitating
;;; optimal reuse of strings.
;;;
;;; Note that callers that require a string argument to a C foreign to act as a
;;; buffer, i.e., in order to have the contents changed by the C function, MUST
;;; pass a simple Gensym string.  Such callers may call this function directly
;;; to obtain such a string, and are encouraged for the benefit of getting
;;; quantized strings.
;;;
;;; This is for use in OS-FOREIGN, for macro def-gensym-c-function, q.v.

#+(or chestnut-3 (not (or sbcl lispworks clozure)))
(defun copy-foreign-string-arg-if-appropriate (gensym-string-or-wide-string)
  (cond
    ((wide-string-p gensym-string-or-wide-string)
     (let* ((length (wide-string-length gensym-string-or-wide-string))
            (string (obtain-simple-gensym-string-of-quantized-length length)))
       (copy-portion-of-wide-string-octets-into-simple-gensym-string
         gensym-string-or-wide-string 0 length string 0)
       string))
    ((not (simple-gensym-string-p gensym-string-or-wide-string))
     (let* ((length (glength gensym-string-or-wide-string nil))
            (string (obtain-simple-gensym-string-of-quantized-length length)))
       (copy-portion-of-string-into-simple-gensym-string
         gensym-string-or-wide-string 0 length string 0)
       string))
    (t nil)))

;;; The SBCL version of `copy-foreign-string-arg-if-appropriate' makes an alien
;;; string and copies the contents of the given string into it.  -jv, 12/7/07

#+(and sbcl (not chestnut-3))
(defun copy-foreign-string-arg-if-appropriate (gensym-string-or-wide-string)
    (cond
        ((wide-string-p gensym-string-or-wide-string)
            (let* ((length (wide-string-length gensym-string-or-wide-string))
                    (sbcl-string (sb-alien:make-alien char (+ 1 length))))
                (dotimes (i length)
                    (setf (sb-alien:deref sbcl-string i)
                        (wide-character-code
                            (charw gensym-string-or-wide-string i))))
                ;added by SoftServe - fixed bug with endless string
                (setf (sb-alien:deref sbcl-string length) 0)
                sbcl-string))

        ((simple-gensym-string-p gensym-string-or-wide-string)
            (let* ((length (length gensym-string-or-wide-string))
                    (sbcl-string (sb-alien:make-alien char (+ length 1))))
                (dotimes (i length)
                    (setf (sb-alien:deref (sb-alien:cast sbcl-string
                                (* (sb-alien:unsigned 8))) i)
                        (char-code (char gensym-string-or-wide-string i))))
                ;added by SoftServe - fixed bug with endless string
                (setf (sb-alien:deref sbcl-string length) 0)
                sbcl-string))

        (t
            #+development
            (warn "need to handle adjustable strings better")
            (let* ((length (glength gensym-string-or-wide-string nil))
                    (string (obtain-simple-gensym-string-of-quantized-length
                            length)))
                (copy-portion-of-string-into-simple-gensym-string
                    gensym-string-or-wide-string 0 length string 0)
                (copy-foreign-string-arg-if-appropriate string)))))

#+(and lispworks (not chestnut-3))
(defun copy-foreign-string-arg-if-appropriate (gensym-string-or-wide-string)
  (let* ((wide-string? (wide-string-p gensym-string-or-wide-string))
         (string-length 
          (if wide-string?
              (position 0 gensym-string-or-wide-string)
              (length gensym-string-or-wide-string)))
         (c-array (make-array (1+ string-length) 
                              :element-type '(unsigned-byte 8)
                              :allocation :static)))
    (map-into c-array #'(lambda (x) (logand #xff (if wide-string? x (char-code x))))
              gensym-string-or-wide-string)
    (setf (aref c-array string-length) 0)
    c-array))

#+(and clozure (not chestnut-3))
(defun copy-foreign-string-arg-if-appropriate (gensym-string-or-wide-string)
  (cond ((wide-string-p gensym-string-or-wide-string)
         (let ((length (wide-string-length gensym-string-or-wide-string)))
           (multiple-value-bind (la lap)
               (ccl:make-heap-ivector (+ 1 length) '(unsigned-byte 8))
             (loop for i from 0 below length
                   do (setf (aref la i)
                            (logand #xff (wide-character-code (charw gensym-string-or-wide-string i))))
                   finally (setf (aref la length) 0))
             lap)))
        (t ;; (simple-gensym-string-p gensym-string-or-wide-string)
           (ccl::make-cstring gensym-string-or-wide-string))))

#+(and sbcl (not chestnut-3))
(defun copy-out-alien-string-into-original-string (alien-string original-string)
  (let ((ccode 0))
  (if (wide-string-p original-string)
      (progn (dotimes (i (wide-string-length original-string))
              (setq ccode (sb-alien:deref alien-string i))  
              (setf (charw original-string i)
              (code-wide-character
               ;variable "ccode" and bounds checking added by SoftServe
               (if (and (>=f ccode 0) (<=f ccode 65535) ) ccode 0)
                    
                    )))
        )
      (progn (dotimes (i (length original-string))
             (setq ccode (sb-alien:deref alien-string i))  
        (setf (char original-string i)
              ;added by SoftServe
              (code-char (if (and (>=f ccode 0) (<=f ccode 255) ) ccode 0))))
        ))))

#+(and lispworks (not chestnut-3))
(defun copy-out-alien-string-into-original-string 
    (lisp-array-pointer gensym-string)
  (cond ((wide-string-p gensym-string)
         (loop for i from 0 below (length gensym-string)
            as code = (fli:foreign-typed-aref '(unsigned-byte 8) 
                                              lisp-array-pointer i)
            until (zerop code)
            do (setf (aref gensym-string i) code)))
        ((simple-gensym-string-p gensym-string)
         (loop for i from 0 below (length gensym-string)
            as code = (fli:foreign-typed-aref '(unsigned-byte 8) 
                                              lisp-array-pointer i)
            until (zerop code)
            do (setf (char gensym-string i) (code-char code))
            finally (when (and code (zerop code)) 
                      (setf (char gensym-string i) (code-char code))))))
  gensym-string)

#+(and clozure (not chestnut-3))
(defun copy-out-alien-string-into-original-string (lap gensym-string)
  (declare (type ccl:macptr lap))
  (cond ((wide-string-p gensym-string)
         (loop for i from 0 below (length gensym-string)
               as code = (ccl::%get-unsigned-byte lap i)
               until (zerop code)
               do (setf (charw gensym-string i) (code-wide-character code))
               finally (when (and code (zerop code))
                         (setf (charw gensym-string i) (code-wide-character 0)))))
        ((simple-gensym-string-p gensym-string)
         (loop for i from 0 below (length gensym-string)
               as code = (ccl::%get-unsigned-byte lap i)
               until (zerop code)
               do (setf (char gensym-string i) (code-char code))
               finally (when (and code (zerop code))
                          (setf (char gensym-string i) (code-char 0))))))
  gensym-string)

;;; `reclaim-sbcl-alien-string' does nothing, but is here as a placeholder
;;; in case it should do something.

#+(and sbcl (not translator))
(defun reclaim-sbcl-alien-string (sbcl-string)
  (declare (ignore sbcl-string))
  nil)

;;; Non-static arrays which appears in :wide-string place must be static-lized.
;;; Only useful when G2 running in LispWorks directly.
;;; -- Chun Tian (binghe), 2010/8/3

#+(and lispworks (not translator))
(defun copy-foreign-byte-vector-16 (lisp-array)
  ;(declare (optimize (safety 0) (speed 3) (cl:debug 0)))
  (unless (sys:staticp lisp-array)
    (let* ((length (length lisp-array))
           (static-array (make-array length :allocation :static
                                     :element-type '(unsigned-byte 16)
                                     :adjustable nil)))
      (loop for i from 0 below length do
            (setf (aref static-array i) (aref lisp-array i)))
      static-array)))

#+(and lispworks (not translator))
(defun copy-byte-vector-16-into-original (static-array lisp-array)
  ;(declare (optimize (safety 0) (speed 3) (cl:debug 0)))
  (loop for i from 0 below (length static-array) do
        (setf (aref lisp-array i) (aref static-array i)))
  nil)

;;; Clozure CL doesn't support static Lisp array which could be called directly
;;; by foreign code. So here we must make a wrapper for it (:byte-vector-16).
;;; Following two functions are called by macro "expand-c-function-with-strings".
;;; -- Chun Tian (binghe), for Glority, 2010/07/28

#+(and clozure (not translator))
(defun copy-foreign-byte-vector-16 (lisp-array)
  (declare (type vector lisp-array))
  (let ((lisp-array-length (length lisp-array)))
    (multiple-value-bind (la lap)
        (ccl:make-heap-ivector lisp-array-length '(unsigned-byte 16))
      (loop for i from 0 below lisp-array-length
            do (setf (aref la i) (aref lisp-array i)))
      (cons la lap))))

#+(and clozure (not translator))
(defun copy-byte-vector-16-into-original (la-and-lap lisp-array
                                          &aux (la (car la-and-lap)))
  (declare (type cons la-and-lap)
           (type vector lisp-array))
  (let ((lisp-array-length (length lisp-array)))
    (loop for i from 0 below lisp-array-length
          do (setf (aref lisp-array i) (aref la i)))
    (ccl:dispose-heap-ivector la)
    lisp-array))

;;; `Strings-to-text-strings-in-list' copies list, if necessary, converting
;;; gensym strings to text strings.  It does not do the copy if there are no
;;; strings in list.  If it does do the copy, it uses all new free conses to
;;; copy the spine of the list, and fresh wide strings; all other substructure
;;; is shared with the argument list.  This is only to be called at compile
;;; time; it's therefore a defun-for-macro.  Note that it does not expect any
;;; gensym strings to be in the Gensym character set (UTF-G), and does not do
;;; any translation.

(defun-for-macro strings-to-text-strings-in-list (list)
  (if (loop for x in list thereis (gensym-string-p x))
      (loop for x in list
            collect (if (gensym-string-p x)
                        (string-to-wide-string x)
                        x))
      list))


#+development
(defun copy-tree-changing-strings-to-text-strings (tree)
  (cond
    ((atom tree)
     (if (gensym-string-p tree)
         (string-to-wide-string tree)
         tree))
    (t
     (cons
       (copy-tree-changing-strings-to-text-strings (car tree))
       (copy-tree-changing-strings-to-text-strings (cdr tree))))))


;;; `Gensym-encoded-strings-to-text-strings-in-tree' assumes that all strings in
;;; tree are encoded in UTF-G (the old Gensym character set/encoding), and
;;; copies any such strings, with character set translation, as wide strings.
;;; All conses are copied from the general cons pool.  This is intended to be
;;; used at compile time only; hence it is a defun-for-macro.

(defun-for-macro gensym-encoded-strings-to-text-strings-in-tree (tree)
  (cond
    ((atom tree)
     (if (gensym-string-p tree)
         (gensym-string-to-wide-string tree)
         tree))
    (t
     (cons
       (gensym-encoded-strings-to-text-strings-in-tree (car tree))
       (gensym-encoded-strings-to-text-strings-in-tree (cdr tree))))))



;;; `Copy-portion-of-string-into-simple-gensym-string' copies the portion of
;;; source-string, a text string, specified by source-start and source-end into
;;; the portion of destination-string, a gensym string, starting at
;;; destination-start.  Destination-string must be simple and must be long
;;; enough to hold all the characters to be copied.  No unicode to gensym
;;; encoding is performed: only octets (the right most 8 bits) of characters are
;;; copied.  The rest of the bits are simply discarded.  This is good enough for
;;; ASCII/ISO Latin-1 text, which makes it well suited for facilities dealing
;;; with strings containing numeric characters such as digits, periods, etc.,
;;; for example.

(defun-void copy-portion-of-wide-string-octets-into-simple-gensym-string
    (source-string source-start source-end
                   destination-string destination-start)
  (declare (type fixnum source-start source-end destination-start))
  (loop for i from source-start below source-end
        as j from destination-start
        as char = (charw source-string i)
        do (setf (schar destination-string j)
                 (if (char=w #.%line-separator char)
                     #\newline
                     (ascii-code-char
                       (logandf
                         #xff
                         (wide-character-code char)))))))

;; Consider implementing this in C, for efficiency, since it could become a
;; bottleneck.

;; Patterned after copy-portion-of-string-into-simple-gensym-string.




;;;; Tools for Deriving Substrings

;; Wide string version; see similar section with ASCII-STRING for TEXT-STRING in
;; UTILITIES1.  (Also, ASCII-TEXT-LINE => TEXT-LINE and ASCII-CHARACTER =>
;; TEXT-CHARACTER.) (MHD 2/15/96)

;;; NOTE: all of the functions in this section at present do not work in terms
;;; of Gensym strings, but rather in terms of ISO 10646/Unicode-encoded wide
;;; strings ("Text Strings").
;;;
;;; NOTE: The functions in this section differ from those in the section of
;;; UTILITIES1, "Handy String Functions", in that the later set is intended for
;;; offline use, i.e., at macro definition time, and not at runtime.  They also
;;; allocate using dynamic, non-pooled memory.  There may be some there that
;;; will want to belong here, and they can just be moved over, possibly with
;;; appropriate name changes, on an as-needed basis.





;;; `Position-in-text-string' and `find-in-text-string' provide highly
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
;;; `Position-of-text-character-in-list' and `find-text-character-in-list'

(defun-simple position-in-text-string (character string)
  (declare (eliminate-for-gsi))
  (loop for i from 0 below (lengthw string)
        when (char=w (charw string i) character)
          return i))

(defun-simple position-in-text-string-tail (character string start)
  (declare (eliminate-for-gsi))
  (loop for i from start below (lengthw string)
        when (char=w (charw string i) character)
          return i))

(defun-simple find-in-text-string (character string)
  (declare (eliminate-for-gsi))
  (loop for i from 0 below (lengthw string)
        as char = (charw string i)
        when (char=w char character)
          return char))


(defun-simple position-of-text-character-in-list (character list)
  (declare (eliminate-for-gsi))
  (loop as i from 0
        for char in list
        when (char=w char character)
          return i))

(defun-simple find-text-character-in-list (character list)
  (declare (eliminate-for-gsi))
  (loop as i from 0
        for char in list
        when (char=w char character)
          return char))


(defun-simple find-text-character-in-sequence (character bag)
  (declare (eliminate-for-gsi))
  (cond
    ((text-string-p bag)
     (find-in-text-string character bag))
    ((listp bag)
     (find-text-character-in-list character bag))
    (t ;; (find character bag ':test #'char=w-function)
     (loop for i from 0 below (lengthw bag) ; arbitrary sequence
           as element = (elt bag i)
           when (char=w character element)
             return element))))

#+unused
(defun-simple position-of-text-character-in-sequence (character bag)
  (declare (eliminate-for-gsi))
  (cond
    ((text-string-p bag)
     (position-in-text-string character bag))
    ((listp bag)
     (position-of-text-character-in-list character bag))
    (t
     ;; (position character bag ':test #'char=w-function)
     (loop for i from 0 below (lengthw bag) ; arbitrary sequence
           as element = (elt bag i)
           when (char=w character element)
             return i))))




;;; `Position-of-text-character-not-in-bag' ...

(defun-allowing-keywords position-of-text-character-not-in-bag
    (string bag &key start end)
  (declare (eliminate-for-gsi))
  (loop for i from (or start 0)
              below (or end (lengthw string))
        when (not (find-text-character-in-sequence
                    (charw string i)
                    bag))
          do (return i)))


;;; `Position-of-text-character-in-bag' ...

(defun-allowing-keywords position-of-text-character-in-bag
    (string bag &key start end)
  (declare (eliminate-for-gsi))
  (loop for i from (or start 0)
              below (or end (lengthw string))
        when (find-text-character-in-sequence
               (charw string i)
               bag)
          do (return i)))


(defun-allowing-keywords position-of-text-character-not-in-bag-from-end
    (string bag &key start end)
  (declare (eliminate-for-gsi))
  (loop for i from (-f (or end (lengthw string)) 1)
              downto (or start 0)
        when (not (find-text-character-in-sequence
                    (charw string i)
                    bag))
          do (return i)))

;; Compare this with CL's POSITION called with just the right args:
;;
;; -> (position-of-text-character-not-in-bag-from-end #w"  foobar      " #w" " :start 6  :end 10)
;; 7
;; -> (position-of-text-character-not-in-bag-from-end #w"  foobar      " #w" " :start 8  :end 10)
;; NIL
;; -> (position-of-text-character-not-in-bag-from-end #w"  foobar      " #w" ")
;; 7
;;
;; -> (position  #\space "  foobar      "  :from-end t :test-not #'char= :start 6  :end 10)
;; 7
;; -> (position  #\space "  foobar      "  :from-end t :test-not #'char= :start 8  :end 10)
;; NIL
;; -> (position  #\space "  foobar      "  :from-end t :test-not #'char=)
;; 7









;;; `text-string-trim' returns a gensym string copy of string, with all characters
;;; in character-bag stipped off the beginning and end.  `text-string-left-trim'
;;; strips characters off only the beginning, and `text-string-right-trim' strips
;;; off only the end.
;;;
;;; The argument character-bag may be any sequence containing characters.
;;;
;;; These are intended analogs of the Common Lisp string functions string-trim,
;;; string-left-trim, and string-right-trim, respectively.  Note, however, that
;;; this may be relied on to ALWAYS return a new string, never the argument
;;; string, even if no characters need to be trimmed.
;;;
;;; Examples:
;;;
;;;   -> (text-string-trim " (*)" " ( *three (silly) words* ) ")
;;;   "three (silly) words"
;;;   -> (text-string-right-trim " (*)" " ( *three (silly) words* ) ")
;;;   " ( *three (silly) words"
;;;   -> (text-string-left-trim " (*)" " ( *three (silly) words* ) ")
;;;   "three (silly) words* ) "
;;;
;;;   -> (text-string-trim '(#\space #\=) "  = foo = bar =  ")
;;;   "foo = bar"

(defun text-string-trim (character-bag string)
  (declare (eliminate-for-gsi))
  (loop for start from 0 below (lengthw string)
        as character = (charw string start)
        while (find-text-character-in-sequence character character-bag)
        finally
          (return
            (loop for end from (lengthw string) above start
                  as character = (charw string (-f end 1))
                  while (find-text-character-in-sequence character character-bag)
                  finally
                    (return (text-string-substring string start end))))))


(defun text-string-left-trim (character-bag string)
  (declare (eliminate-for-gsi))
  (loop for start from 0 below (lengthw string)
        as character = (charw string start)
        while (find-text-character-in-sequence character character-bag)
        finally
          (return (text-string-substring string start nil))))



(defun text-string-right-trim (character-bag string)
  (declare (eliminate-for-gsi))
  (loop for end from (lengthw string) above 0
        as character = (charw string (-f end 1))
        while (find-text-character-in-sequence character character-bag)
        finally
          (return (text-string-substring string nil end))))

;; These are not coded for speed at present.  In particular, FIND is likely
;; to be slow.


;;; `Parse-text-line-into-list-of-text-strings' returns a list made up of
;;; gensym conses and of the gensym strings that make up "fields" of
;;; text-line, or the subsequence thereof bounded by start and end, if
;;; specified.  Start defaults to 0, and end defaults to the length of
;;; text-line.
;;;
;;; Empty-strings-nil, if true, provides the convenience of producing nils where
;;; it would otherwise have to come up with empty (zero-length) strings. (not
;;; implemented as of 4/19/95)
;;;
;;; It is assumed that text-line contains no newline characters, but that is not
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
;;;   (parse-text-line-into-list-of-text-strings " foo :bar" ":" "")
;;;     -> (" foo " "bar")
;;;   (parse-text-line-into-list-of-text-strings " foo :bar" ":" " ")
;;;     -> ("foo" "bar")
;;;
;;; The non-Common-Lisp keyword :grouping-bag, if supplied, is a two-element
;;; sequence giving the beginning and ending delimiters that override the
;;; segmenting specified by delimiter-bag.  For example,
;;;   (parse-text-line-into-list-of-text-strings
;;;     " `hi ho' off to work" " " " " :grouping-bag "`'")
;;;     -> ("hi ho" "off" "to" "work")

(defun-simple parse-text-line-given-grouping-bag
    (text-line delimiter-bag trim-bag start end grouping-bag)
  (declare (eliminate-for-gsi))
  (loop with start fixnum = (or start 0)
        with end fixnum = (or end (lengthw text-line))
        with grouping-start-char = (charw grouping-bag 0)
        with grouping-end-char = (charw grouping-bag 1)
        for substart = start then (if peek-p j (1+f j))
        while (<f substart end)
        for i0? =  (position-of-text-character-not-in-bag
                    text-line trim-bag :start substart :end end)
        while i0?
        for in-group-p
            = (eqlw (charw text-line i0?) grouping-start-char)
        for i = (if in-group-p (1+f i0?) i0?)
        for peek-p = nil
        as j = (if in-group-p
                   (loop for i2 from i below end
                         for this-char = (charw text-line i2)
                         thereis
                         (and (eqlw this-char grouping-end-char) i2)
                         finally (return end))
                   (loop for i2 from i below end
                         for this-char = (charw text-line i2)
                         for group-start-p
                             = (eqlw this-char grouping-start-char)
                         when group-start-p do (setq peek-p t)
                         thereis
                         (and (or group-start-p
                                  (find-text-character-in-sequence
                                    this-char delimiter-bag))
                              i2)))
        as k = (if in-group-p
                   nil
                   (position-of-text-character-not-in-bag-from-end
                     text-line trim-bag :start i :end j))
        collect (text-string-substring text-line i (if k (1+f k) j))
          using gensym-cons
        while j))

(defun-allowing-keywords parse-text-line-into-list-of-text-strings
    (text-line delimiter-bag trim-bag &key start end grouping-bag)
  (declare (eliminate-for-gsi))
  (if grouping-bag
      (parse-text-line-given-grouping-bag
        text-line
        delimiter-bag
        trim-bag
        start
        end
        grouping-bag)
      (loop with start fixnum = (or start 0)
            with end fixnum = (or end (lengthw text-line))
            for substart = start then (+f j 1)
            while (<=f substart end)
            for i = (or (position-of-text-character-not-in-bag
                          text-line trim-bag :start substart :end end)
                        end)
            as j = (position-of-text-character-in-bag
                     text-line delimiter-bag :start i :end end)
            as k = (position-of-text-character-not-in-bag-from-end
                     text-line trim-bag :start i :end j)
            collect (text-string-substring text-line i (if k (+f k 1) j))
              using gensym-cons
            while j)))

;; Adapted from the function that was
;; parse-ascii-text-line-into-list-of-text-strings in 4.0.  (MHD 2/22/96)




;;; `Test-parse-text-line-into-list-of-text-strings' applies the function
;;; parse-text-line-into-list-of-text-strings to each set of args in the
;;; special variable
;;; `parse-text-line-into-list-of-text-strings-test-cases', and checks if
;;; it results in the corresponding results.  Failure is indicated by a non-nil
;;; value, which would be a list of the form
;;;
;;;    ( { (args actual-result expected-result) } )
;;;
;;; This is defined for development only.

#+development
(defparameter parse-text-line-into-list-of-text-strings-test-cases
  (copy-tree-changing-strings-to-text-strings
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
    )))

#+development
(defun test-parse-text-line-into-list-of-text-strings ()
  (loop with function = 'parse-text-line-into-list-of-text-strings
        for (args expected-result)
            in parse-text-line-into-list-of-text-strings-test-cases
        as expression = `(,function . ,args)
        as actual-result = (eval expression)
        when (not (equalw actual-result expected-result))
          collect (list args actual-result expected-result)
            into failures
          and do (format t "~%=> (~a; ~s) ~s"
                         (if (equalw actual-result expected-result) "good" "bad")
                         expected-result
                         actual-result)
        finally
          (if failures
              (return failures))))

#+development
(assert (null (test-parse-text-line-into-list-of-text-strings)))





;;; `Parse-space-delimited-text-line-into-list-of-text-strings'

(defun-allowing-keywords parse-module-map-line-into-list-of-text-strings
    (text-line delimiter-bag trim-bag &key start end)
  ;; Adapted from parse-text-line-into-list-of-text-strings.
  ;; The differences are:
  ;; (1) This code doesn't accept a grouping-bag keyword.
  ;; (2) This code treats the delimiter-bag differently as
  ;;     it only accepts at most two items on a line, a
  ;;     module name and an associated pathname.
  ;; - jpg 2/23/01
  (declare (eliminate-for-gsi))
  (loop with start fixnum = (or start 0)
        with end fixnum = (or end (lengthw text-line))
        for substart = start then (+f j 1)
        while (<=f substart end)
        for i = (or (position-of-text-character-not-in-bag
                      text-line trim-bag :start substart :end end)
                    end)
        as j = (position-of-text-character-in-bag
                 text-line delimiter-bag :start i :end end)
        as k = (position-of-text-character-not-in-bag-from-end
                 text-line trim-bag :start i :end j)
        ;; Collect the remaining characters until the end of
        ;; the line... - jpg 2/23/01
        while (or j k)
        ;; ... but only if there are useful characters to
        ;; collect, e.g. for #w"foo   ", the spaces after
        ;; "foo" aren't meaningful. - jpg 2/27/01
        collect (prog1 (text-string-substring-from-module-map-line
                         text-line i (if k (+f k 1) j))
                  (setq delimiter-bag nil))
          using gensym-cons
        while j))

(defun-simple text-string-substring-from-module-map-line
    (string start? end?)
  (declare (eliminate-for-gsi))
  (let ((start (or start? 0))
        (end (or end? (lengthw string))))
    ;; Actually, neither start? nor end? can be null now, but ...
    (when (and (char=w (charw string start) #.%\")
               (char=w (charw string (1-f end)) #.%\"))
      ;; Strip off at most one pair of surrounding double
      ;; quotes, but only if they're paired. - jpg 2/23/01
      (setq start (1+f start) end (1-f end)))
    (copy-text-string-portion string start end)))

;;; Note that `parse-space-delimited-text-line-into-list-of-text-strings'
;;; is only used to parse lines in module map files.  These lines
;;; should each contain exactly two items: a module name and an
;;; associated pathname.

(defun parse-space-delimited-text-line-into-list-of-text-strings
    (text-line)
  (declare (eliminate-for-gsi))
  (parse-module-map-line-into-list-of-text-strings
    text-line '(#.%space #.%tab) '(#.%space #.%tab)))

;; Adapted from the function that was
;; parse-space-delimited-ascii-text-line-into-list-of-ascii-strings in 4.0.
;; (MHD 2/22/96)


;;; `Test-parse-space-delimited-text-line-into-list-of-text-strings'
;;; applies the function
;;; parse-space-delimited-text-line-into-list-of-text-strings to
;;; each set of args in the special variable
;;; `parse-space-delimited-text-line-into-list-of-text-strings-test-cases',
;;; and checks if it returns the corresponding results.  Failure is
;;; indicated by a non-nil value, which would be a list of the form
;;;
;;;    ( { (arg actual-result expected-result) } )
;;;
;;; Note that `parse-space-delimited-text-line-into-list-of-text-strings'
;;; is only used to parse lines in module map files.  These lines
;;; should each contain exactly two items: a module name and an
;;; associated pathname.
;;;
;;; This test is defined for development only.

#+development
(defparameter parse-space-delimited-text-line-into-list-of-text-strings-test-cases
  (copy-tree-changing-strings-to-text-strings
    '(
      ;; The following tests collecting the remaining characters until
      ;; the end of the line into one string, after the first string.
      ("foo bar baz" ("foo" "bar baz"))
      ;; In the second string, all contained characters until the
      ;; end of the line are retained, including the spaces ...
      ("foo bar  baz" ("foo" "bar  baz"))
      ;; ... but not surrounding spaces or tabs.
      (" foo bar  baz  " ("foo" "bar  baz"))
      ;; Tests stripping off one surrounding pair of double-quotes.
      ("foo \"bar baz\"" ("foo" "bar baz"))
      ;; All characters between the double-quotes are retained ...
      ("foo \" bar baz \"" ("foo" " bar baz "))
      ;; ... but not surrounding spaces or tabs.
      (" foo  \" bar  baz \"  " ("foo" " bar  baz "))
      ;; Only paired surrounding double-quotes are removed.
      ("foo \"bar" ("foo" "\"bar"))
      ;; Only one pair of surrounding double-quotes are removed.
      ("foo \"\"bar baz\"\"" ("foo" "\"bar baz\""))

      ;; Some degenerate cases:

      ;; Paired double-quotes.
      ("foo \"\"" ("foo" ""))
      ;; Paired double-quotes plus one.
      ("foo \"\"\"" ("foo" "\""))
      ;; Just one element.
      ("foo" ("foo"))
      ;; One element plus spaces.
      ("foo    " ("foo"))

      ;; The following are real live examples:

      ;; First, no double-quotes surrounding the second item.
      ("sys-mod                 /bt/ab/kbs/sys-mod.kb"
       ("sys-mod" "/bt/ab/kbs/sys-mod.kb"))
      ;; The same, but with double quotes.
      ("sys-mod              \"/bt/ab/kbs/sys-mod.kb\""
       ("sys-mod" "/bt/ab/kbs/sys-mod.kb"))
      ;; No space in a directory name.
      ("sys-mod        D:\\gensym\\gda-40r1\\sys-mod.kb"
       ("sys-mod" "D:\\gensym\\gda-40r1\\sys-mod.kb"))
      ;; Now a space in the directory name.
      ("uilroot   \"C:\\Program Files\\Gensym\\g2classic-51r7\\gda\\uilroot.kb\""
       ("uilroot" "C:\\Program Files\\Gensym\\g2classic-51r7\\gda\\uilroot.kb"))
      ;; Just the directory, with a space.
      ("my-classes   \"C:\\Program Files\\\""
       ("my-classes" "C:\\Program Files\\"))
    )))

#+development
(defun test-parse-space-delimited-text-line-into-list-of-text-strings ()
  (loop with function
          = 'parse-space-delimited-text-line-into-list-of-text-strings
        for (arg expected-result)
            in parse-space-delimited-text-line-into-list-of-text-strings-test-cases
        as expression = `(,function ,arg)
        as actual-result = (eval expression)
        when (not (equalw actual-result expected-result))
          collect (list arg actual-result expected-result)
            into failures
          and do (format t "~%~a: ~s => ~s ; ~s"
                         (if (equalw actual-result expected-result) "good" "bad")
                         arg
                         expected-result
                         actual-result)
        finally
          (if failures (return failures))))

#+development
(assert (null (test-parse-space-delimited-text-line-into-list-of-text-strings)))







;;; A `number' in G2 may be an `integer' or `floating-point number'.

;;; Integers and floating-point numbers are the same syntactically in G2 as they are
;;; in Common Lisp (see Table 22-2 in section 22.1.2 of the Common Lisp manual),
;;; except that (a) they may not have an initial + and (b) only e or E are allowed
;;; as exponent markers at present.

;; Finish the documentation!



;;; `Exponent-marker-p' is true if character is an exponent marker in G2 syntax
;;; for floating-point numbers.  Character should be a Unicode wide character.

(defun-substitution-macro exponent-marker-p (character)
  (or (char=w character #.%\e)   ; #.%\s #.%\S #.%\f #.%\F #.%\d #.%\D #.%\l #.%\L also?
      (char=w character #.%\E)))



;;; `Advance-number-parsing-state-if-possible' tries to advance the parsing of a number,
;;; if possible, from number-parsing-state? per next-character.  Number-parsing-state?
;;; should be nil for the initial state or an integer in the range [1,7] for a
;;; particular non-initial state.  Advance-number-parsing-state-if-possible may return
;;; either: nil to indicate that next-character is not possible in this state,
;;; an integer in the range [1,7] for the state after next-character, INTEGER to
;;; indicate that next-character delimits an integer on the right, or FLOAT to
;;; indicate that next-character delimits a floating-point number on the right.

;;; Next-character should be a Unicode wide character.

(defun-substitution-macro advance-number-parsing-state-if-possible
    (number-parsing-state? next-character ignore-exponent-marker?)
  (if (digit-char-pw next-character)
      (cond
        ((or (null number-parsing-state?)
             (<=f number-parsing-state? 2))
         2)
        ((<=f number-parsing-state? 4) 4)
        (t 7))
      (case number-parsing-state?
        ((nil) (cond
                 ((eqlw next-character #.%\-) 1)
                 ((eqlw next-character #.%\.) 3)))
        (1 (cond
             ((eqlw next-character #.%\.) 3)))
        (2 (cond
             ((eqlw next-character #.%\.) 4)
             ((and (not ignore-exponent-marker?) (exponent-marker-p next-character)) 5)
             ((or (eqlw next-character #.%\-)
                  (eqlw next-character #.%\')
                  (eqlw next-character #.%\_))
              nil)
                                                ; ((eqlw next-character #.%\+) nil)?
             ((not (alpha-char-pw next-character))
              'integer)))                        ; w/o "."
        (4 (cond
             ((and (not ignore-exponent-marker?) (exponent-marker-p next-character)) 5)
             ((eqlw next-character #.%\.) nil)
             ((or (eqlw next-character #.%\-)
                  (eqlw next-character #.%\')
                  (eqlw next-character #.%\_))
              nil)
                                                ; ((eqlw next-character #.%\+) nil)?
             ((not (alpha-char-pw next-character)) 'float)))
        (5 (cond
             ((or (eqlw next-character #.%\+)
                  (eqlw next-character #.%\-)) 6)))
        (7 (cond
             ((eqlw next-character #.%\.) nil)
             ((or (eqlw next-character #.%\-)
                  (eqlw next-character #.%\')
                  (eqlw next-character #.%\_))
              nil)
                                                ; ((eqlw next-character #.%\+) nil)?
             ((not (alpha-char-pw next-character))
              'float))))))


;; As of 6/27/89, this is used in syntactically-numeric-p below and in
;; get-next-token-if-available in module EDIT.



;;; `Syntactically-numeric-p' is true if text-string is syntactically a number.

(def-concept advance-syntactically-numeric-p)
(def-concept result-of-syntactically-numeric-p)

(defmacro computing-syntactically-numeric-p (&body body)
  (let ((number-parsing-state-var (make-symbol "NUMBER-PARSING-STATE"))
        (possibly-numeric-p-var (make-symbol "POSSIBLY-NUMERIC-P")))
    `(let ((,number-parsing-state-var nil)
           (,possibly-numeric-p-var t))
       (macrolet ((advance-syntactically-numeric-p (char)
                    `(when ,',possibly-numeric-p-var
                       (setq ,',possibly-numeric-p-var
                             (fixnump (setq ,',number-parsing-state-var
                                            (advance-number-parsing-state-if-possible
                                              ,',number-parsing-state-var
                                              ,char
                                              nil))))))
                  (result-of-syntactically-numeric-p ()
                    `(when ,',possibly-numeric-p-var
                       (advance-syntactically-numeric-p #.%space)
                       (case ,',number-parsing-state-var
                         (integer 'integer)
                         (float 'float)))))
         ,@body))))


(defun syntactically-numeric-p (text-string)
  (declare (eliminate-for-gsi))
  (computing-syntactically-numeric-p
    (loop for i from 0 below (text-string-length text-string)
          as char = (charw text-string i)
          while (advance-syntactically-numeric-p char)
          finally (return (result-of-syntactically-numeric-p)))))

;; Fixnump test above used to be integerp.  I changed it here and throughout
;; this module upon learning that fixnum is inlined, while integerp is a function
;; call (in Chestnut).  This is ok, althought ideally, both would be inlined,
;; I think. (MHD 6/4/92)



;;; `Syntactically-numeric-substring-p' returns true (non-nil) if string is
;;; syntactically a number between start? (defaults to 0) and end? (defaults to
;;; the length of the string).  Unless disallow-junk? is true, this will accept
;;; syntactically numeric input up to a junk character (ala G2's QUANTITY
;;; function).  Unless disallow-leading-whitespace? is true, this ignores any
;;; initial whitespace characters (as determined by skip-whitespace-in-string),
;;; whereas if disallow-leading-spaces? is true, common initial horizontal
;;; whitespace characters (at present, space and tab) result in a false (nil)
;;; result.  Unless disallow-unary-plus? is true, this allows a leading "unary"
;;; plus.  For example "+1" and "+.34" would be accepted, whereas if the flag
;;; were specified true, they would not be accepted.  The acceptance of the + at
;;; the beginning of a numeric token does not correspond to G2's current token
;;; syntax for numbers (as of 4.0, at least); however, G2's QUANTITY function
;;; has historically allowed unary +, and we currently choose to continue accept
;;; it there for compatibility purposes.  In order to be most compatible with
;;; all current and potential tokenizers, when a leading + is accepted, the
;;; second return value, being the exact start index, is the index one past the
;;; + character; this way, tokenizing from that position forward will always be
;;; successful, whereas it might fail, depending on the tokenizer, if the +
;;; were included.
;;;
;;; As an added convenience, when this returns true, there are three values
;;; returned:
;;;
;;;   (1) either INTEGER or FLOAT as appropriate
;;;   (2) the exact start index; and
;;;   (3) the exact end index
;;;
;;; Note that a syntactically numeric string or substring may not be able to be
;;; parsed as a number in the case of overflow or underflow.
;;;
;;; Note that this function does not allocate any temporary floats, and does
;;; not allocate memory of any kind.

(defun syntactically-numeric-substring-p
    (string
      &optional start? end?
      disallow-junk? disallow-leading-whitespace?
      disallow-unary-plus?)
  (declare eliminate-for-gsi)
  (multiple-value-bind (kind? start-index end-index)
      (syntactically-numeric-substring-p-1
        string nil start? end?
        disallow-junk? disallow-leading-whitespace? disallow-unary-plus?)
    (if kind?
	    (progn 
		 ;added by SoftServe
		 (let ((strlen (lengthw string)))
		  (when (and (>f strlen end-index) (char=w (charw string end-index) #.%\L))
		    (incff end-index)
		   )
		 )	
		(values kind? start-index end-index))
        (syntactically-numeric-substring-p-1
          string t start? end?
          disallow-junk? disallow-leading-whitespace? disallow-unary-plus?))))

(defun syntactically-numeric-substring-p-1
    (string ignore-exponent-marker? start? end?
            disallow-junk? disallow-leading-whitespace? disallow-unary-plus?)
  (declare eliminate-for-gsi)
  (loop with end = (or end? (lengthw string))
        with start = (or start? 0)
        with initial-index
          = (if disallow-leading-whitespace?
                start
                (skip-whitespace-in-string string start end))
        as previous-number-parsing-state?
           = nil then number-parsing-state?
        with number-parsing-state? = nil
        as i from initial-index
        as accept-leading-plus? = (not disallow-unary-plus?) then nil
        as next-character = (if (=f i end) #.%space (charw string i))
        if (and accept-leading-plus? (char=w next-character #.%\+))
          do (incff initial-index)        ; return exact starting point past +
             (setq number-parsing-state? 1) ; 1? our good friend advance-... knows this as
                                        ;   the state we're in after a unary minus
        else
          do (setq number-parsing-state?
                   (advance-number-parsing-state-if-possible
                     number-parsing-state? next-character ignore-exponent-marker?))
             (cond
               ((fixnump number-parsing-state?)
                (when (>=f i end)          ; never here in practice, but safer to test
                  (return nil)))
               (t
                (return
                  (cond
                    ((=f i end)
                     (if (memq number-parsing-state? '(integer float))
                         (values number-parsing-state? initial-index i)))
                    ((and (not disallow-junk?)
                          (and previous-number-parsing-state?
                               (<=f 1 previous-number-parsing-state? 7)))
                     (setq number-parsing-state?
                           (advance-number-parsing-state-if-possible
                             previous-number-parsing-state?
                             #.%space ignore-exponent-marker?))
                     (if (memq number-parsing-state? '(integer float))
                         (values number-parsing-state? initial-index i)))
                    (t
                     nil)))))))

;; Note: we implement the acceptance of leading + here, and not in the numeric
;; syntax recognizer advance-number-parsing-state-if-possible in order to avoid
;; complicating that function with options and/or changing interface or the
;; behavior of the main tokenizer (for the editor), which uses it.  Note that
;; the old numeric tokenizer used by the QUANTITY function handled unary +.  To
;; see that unary + is not handled by the editor's tokenizer: try these
;; expressions in a readout table: (1) + -30; (2) - +30; (3) -30; (4) +30.  In
;; 4.0 and 5.0, only (2) fails.  Note, too, that it is not strictly necessary
;; for the user of this function, i.e., implementing G2's QUANTITY function, to
;; use the returned initial index, since the current actual tokenizer for
;; quantity handles + in tokens. (MHD 10/28/96)

;; Note 2: Two character lookahead was implemented for the case of an
;; 'E' or 'e' being handled as junk vs. as an exponent marker.  For example
;; "1.0XY" requires one character of look ahead to get the right result
;; ("1.0"), while "1.0EY" requires two to get the same result.  In the first
;; case, X could immediately be recognized as junk, whereas the E in the second
;; case did not appear to be junk until the character following it was read.
;; (MHD 10/30/96)

;; It was also stated: with a little more work, this could be fixed to always
;; return the last known good state, but that work should await an actual
;; need for this function. (MHD 11/1/96)

;; Two character lookahead as implemented did not handle the cases of "12e"
;; or "1.2e".  E.g. this led to Bug HQ-5129181.  And two character lookahead
;; cannot handle the following cases:  "12e+", "1.2e+", "12e+a", "1.2e+a"

;; To get all these cases right a new approach was implemented which
;; eliminated two character lookahead and instead
;; syntactically-numeric-substring-p-1 is called twice but only on
;; troublesome cases which are quite rare.  The first time through
;; is normal.  But if a number is not found, even though it may indeed
;; be present, a second call is made, but this time 'E' or 'e' are
;; not recognized as exponent markers so that the number, if present,
;; is found (JPG 10/31/05)

;; UPDATE: we've found the bug in the original string number reader, and fixed
;; that.  Meanwhile, we found various interesting divergences between the
;; number reader and G2's reader; here are some:
;;
;;   input        string reader          G2's reader in the editor
;;
;;   +10          integer 10             illegal token (or, two tokens: + and 10)
;;
;;   10.          integer 10             float 10.0
;;
;;   10.e         integer 10             illegal token (or, two tokens: float 10.0 and e, if allowing junk)
;;
;;   +            integer 0              illegal token (or, the token +)
;;
;;   536870911    float 5.36870911E8     integer 536870911
;;   536870910    float 5.36870910E8     integer 536870910
;;   536870909    float 5.36870909E8     integer 536870909
;;
;; For 5.0, we should eliminate the differences that imply different
;; interpretations (all but the first of the above), but keep those
;; that imply greater liberality (the inclusion of unary + in a
;; quantity, for example, and allowing junk at the end, returning
;; the last known good state.  (MHD 11/1/96)














;;;; G2 Symbols



;;; A `G2 symbol' is a symbol whose symbol name must consist of a sequence of Gensym
;;; characters.  Any possible sequence of Gensym characters can be a G2 symbol name.
;;; All symbols that can be written as symbols by G2 must be G2 symbols.
;;; All G2 symbols should be in the ab package except for (1) those already in
;;; ("inherited from") the lisp package, (2) syntactically anomalous G2 symbols of
;;; type PUNCTUATION-MARK (see below), and (3) :nil, which is used in lieu of nil
;;; because nil is conventionally used in Lisp to mean "no", "none", "does not exist",
;;; etc.

;;; A G2 symbol should be written parsably in contexts where it may be parsed as a
;;; token, by quoting certain of its characters with a prefix @ (~@ internally).
;;; Except in punctuation marks (see below), where no quoting is needed, any
;;; character other than the following ones must be quoted in a parsable
;;; representation of a G2 symbol:
;;;
;;;    (a) a `simple symbol character' - any of the 40 simple characters A-Z, 0-9,
;;;        -, ., ', and _;
;;;
;;;    (b) a ~ complex character iff the simple character following the ~ is alphanumeric
;;;        (a-z, A-Z, or 0-9) and does not represent a lower-case character;
;;;
;;;    (c) Kanji (\ complex) characters.
;;;
;;; Also, certain `syntactically anomalous G2 symbols' must have at least one character
;;; quoted (conventionally including the first) when they are written parsably.  A
;;; syntactically anomalous G2 symbol is distinguished by means of a non-nil
;;; `type-of-syntactic-anomaly' global property value, as follows: NUMERIC, when the
;;; name would represent a number if no character were quoted, and PUNCTUATION-MARK,
;;; when the name would represent a punctuation mark if no character were quoted.
;;; Syntactically anomalous G2 symbols that are part of G2 must be given
;;; their type-of-syntactic-anomaly property value explicitly, whereas syntactically
;;; anomalous symbols that introduced by a user or kb will be given their property
;;; value upon token parsing or kb reading.  Syntactically anomalous G2 symbols of
;;; type PUNCTUATION-MARK are kept in the keyword package, to be distinct from
;;; punctuation marks.

;;; Parsable representations of G2 symbols should be written in the following cases:
;;;
;;;    (1) in token menu items ...

;;; ...

;;; Finally, certain text can never be in symbols: newlines, the character #xFFFF,
;;; and the character #xFFFE.

;; Also, consider banning illegal combinations, such as standalone floating
;; accents! (MHD 12/19/96)

;; See twrite-symbol in module UTILITIES1 and get-next-token-if-available in module EDIT.

;; Require certain Kanji characters to be quoted in parsable representations of G2
;; symbols!  (Otherwise get-next-token-if-available would map them to corresponding
;; standard ascii characters.)




;;; Valid-symbol-text-string-p is true iff printed-representation-text-string
;;; does NOT contains only valid symbol characters, or combinations valid to
;;; appear in a symbol.  When this returns true, if the result is a string,
;;; it may be assumed to be a complete English sentence of the form "It <verb> ...",
;;; explaining what the string ("it") has wrong with it.  The result string
;;; is owned by this function, not the caller, and should not be reclaimed.
;;;
;;; Note that this applies to the print name of the symbol, not the readable
;;; form.  Thus, spaces, punctuation marks, etc., are no problem.
;;;
;;; This is extremely liberal in what it will accept.  It will reject
;;;
;;;   (a) a totally empty text (no characters at all);
;;;   (b) text with any non-Unicode character, of
;;;       which there are exactly two: U+FFFF and U+FFFE;
;;;   (c) text longer than maximum-length-for-user-symbols
;;;
;;; Note that in 5.x, newline characters were disallowed here, but this was
;;; called from fewer places responsible for creating symbols.  In 6.0, newline
;;; characters are allowed in symbols.  There may be some cases where there
;;; are problems creating a symbol token with a newline, or printing one.
;;;
;;; Note that there is currently no way to represent a symbol whose text is
;;; empty ("" -- Lisp symbol ||).  This returns the value of the special
;;; variable message-illegal-symbol-text-string-empty if given an empty text
;;; string.  However, text-to-symbol (introduced in 5.x) allowed such symbols in
;;; 5.x, and will continue to allow them.  Now that that function calls this
;;; function to check its text, it will have to accept that case.  We plan to
;;; eventually add a way to represent such a token readably, e.g., with a
;;; bracketing syntax ala Lisp's vertical bars (||).

(defvar message-illegal-symbol-text-string-empty
  (stringw "It is empty."))
(defvar message-illegal-symbol-text-string-contains-a-newline
  (stringw "It contains a newline character."))
(defvar message-illegal-symbol-text-string-contains-FFFF
  (stringw "It contains the illegal character whose code is (hex) FFFF"))
(defvar message-illegal-symbol-text-string-contains-FFFE
  (stringw "It contains the illegal character whose code is (hex) FFFE"))
(defvar message-illegal-symbol-text-string-too-long
  (stringw
    #.(format nil
              "It is longer than the maximum length for symbols, ~d."
              maximum-length-for-user-symbols)))


(defun-simple non-valid-symbol-text-string-p  (printed-representation-text-string)
  (let ((character #u0000))
    (declare (type wide-character character))
    (loop with length = (lengthw printed-representation-text-string)
          initially
            (when (=f length 0)
              (return message-illegal-symbol-text-string-empty))
            (when (>f length maximum-length-for-user-symbols)
              (return message-illegal-symbol-text-string-too-long))
          for i from 0 below length
          do (setq character (charw printed-representation-text-string i))
          ;; See note!
          ;; when (newline-p character)
          ;;   return message-illegal-symbol-text-string-contains-a-newline
          when (char>=w character #uFFFE)
            return (if (char=w character #uFFFF)
                       message-illegal-symbol-text-string-contains-FFFF
                       message-illegal-symbol-text-string-contains-FFFE))))

;; Note: this previously disallowed "newline" characters.  However, we're
;; changing this to allow newline characters in 6.0 because (a) it's compatible
;; with some significant 5.0 functionality: the symbol reader in 5.0 and the
;; symbol interning function text-to-symbol accepted such characters; (b) it's
;; more user friendly, since users may well want to intern such text strings.
;; One of the reasons for not interning symbols might be inconsistencies or bugs
;; in their display.  However, that is a problem exists for other characters as
;; well, and it's better for that to be the only problem than to continue with
;; inconsistent processing of these characters.  For now, keeping FFFF and FFFE
;; as illegal characters, since those truely are not valid Unicode characters.
;; (MHD 7/3/00)



;;; `Simple-symbol-character-p' is true if wide-character corresponds to a
;;; simple symbol character.

(defun-simple simple-symbol-character-p (wide-character)
  ;; FOR NOW:  (MHD 2/20/96)
  (and (simple-symbol-character-p-4.0 wide-character)
       (not (char=w wide-character #.%tab)))        ; See Note! (MHD 3/18/97)
  ;; Possible start at a better one for Unicode:
;  (or (alphanumericpw wide-character)
;      (char=w wide-character #.%\-)
;      (char=w wide-character #.%\.)
;      (char=w wide-character #.%\')
;      (char=w wide-character #.%\_))
  )

;; Added restriction on Tab, which was not even a "Gensym character" prior to
;; 5.0. For the final release of 5.0, rewrite this to exclude as many
;; punctuation and space and other kinds of characters as it makes sense not to
;; treat as simple symbol characters!!! Base this Unicode information tables as
;; much as possible.  (MHD/JV 3/18/97)

;; If additional characters become simple symbol characters, revise the parsing
;; of numbers by get-next-token-if-available appropriately.  Note that it is
;; undesirable for #\? to be a simple symbol character.



;;; `Simple-symbol-character-p-4.0' is true if character would have been a
;;; simple symbol character in 4.0.  At present, there are practically no
;;; differences between simple-symbol-character-p-4.0 and
;;; simple-symbol-character-p, but the former should be used if strict
;;; compatibility is called for.

(defun simple-symbol-character-p-4.0 (wide-character)
  (multiple-value-bind
      (character-or-character-code? escape?)
      (gensym-character-code-to-pair
        (map-unicode-to-gensym-character-code
          (wide-character-code wide-character)))
    (when character-or-character-code? ; can this be null?
      (case escape?
        (#\@ nil)
        (#\~ (alphanumericp character-or-character-code?))
        (#\\ t)
        (t
         (or (alphanumericp character-or-character-code?)
             (char= character-or-character-code? #\-)
             (char= character-or-character-code? #\.)
             (char= character-or-character-code? #\')
             (char= character-or-character-code? #\_)))))))




(defun-simple simple-pathname-character-p (character)
;  (declare (eliminate-for-gsi))
  (or (simple-symbol-character-p character)
      (char=w character #.%\\)
      (char=w character #.%\/)
      (char=w character #.%\~)
      (char=w character #.%\:)
      (char=w character #.%\>)
      (char=w character #.%\<)
      (char=w character #.%\])
      (char=w character #.%\[)))

;; Not yet used.






;;;; Punctuation Marks



;;; A `punctuation mark' is one of the following.
;;;
;;;    < <= > >= / /= = + +- *
;;;    ^ ( ) [ ] { } , : ; ? ! | $ % &       (\^ \( \) ... in Common Lisp)
;;;    ::
;;;
;;; A punctuation mark is represented in G2 by a symbol with a non-nil
;;; punctuation-mark-p global property value.  A punctuation mark is not considered
;;; a G2 symbol; in fact, a G2 symbol with the same name as a punctuation mark is
;;; a distinct symbol and must have at least one of its characters quoted when
;;; written parsably.



;;; `Punctuation-alist' is of the form
;;;
;;;   ( { (first-or-next-character symbol-ending-with-this-character
;;;         . punctuation-alist-for-additional-characters) }
;;;     )
;;;
;;; Note that as of 4.0, "character" here means a Unicode Wide Character; see
;;; UNICODE.  It should therefore not be accessed by using ASSOC, but rather by
;;; using WIDE-CHARACTER-ASSOC.

(defparameter-excluding-gsi punctuation-alist
    '((#.%\< < (#.%\= <=))
      (#.%\> > (#.%\= >=))
      (#.%\/ / (#.%\= /=))
      (#.%\= =)
      (#.%\+ + (#.%\- +-))
      (#.%\* *)
      (#.%\^ ^)
      (#.%\( \()
      (#.%\) \))
      (#.%\[ \[)
      (#.%\] \])
;                (#.%\{ \{)                        ; these now delimit comments
;                (#.%\} \})
      (#.%\, \,)
      (#.%\: \: (#.%\: \:\:))
      (#.%\; \;)
      (#.%\? \?)
      (#.%\! \!)
      (#.%\| \|)
      (#.%\$ \$)
      (#.%\% \%)
      (#.%\& \&)

      ;; added for 4.0 now that these are unicode wide characters:
      (#.%\\ |~\\|)                        ; remember: symbol print names are in UTF-G!
      (#.%\~ |~~|)
      ))


;; Add more here from Unicode, particularly from ISO Latin 1, later!  Note that
;; it may be non-trivial, given that symbols may have already be read in an
;; interned with the old syntax, and code could even be relying on it.  Still,
;; you have to break a few eggs to make an omelette sometimes.... (MHD 2/17/96)

;; If any punctuation mark is ever eliminated from G2, the corresponding syntactically
;; anomalous G2 symbols in kbs should be converted appropriately.

;; Added the double colon (::) punctuation mark today for 4.0. (MHD 1/11/93)



(defun note-punctuation-marks-as-such (punctuation-alist-1)
  (declare (no-op-for-gsi))
  (loop for (nil symbol . punctuation-alist-2)        ; nil is a place holder for character
            in punctuation-alist-1
        do (setf (get symbol 'punctuation-mark-p) t)
           (note-punctuation-marks-as-such punctuation-alist-2)))

(note-punctuation-marks-as-such punctuation-alist)

;; ;; The global property name definition for punctuation-mark-p is in module
;; ;; UTILITIES1, because it is too soon to define it here.
;;
;; -- Older comment .Not true if "here" is UNICODE, but I haven't bothered to do
;; it yet. (MHD 2/20/96)




;;;; Character Syntax



;;; A `character syntax table' is an a-list ...
;;;
;;;    (unicode-wide-character
;;;      . (dont-space-before-p
;;;         dont-space-after-p
;;;         bracket-open-or-close?
;;;         matching-bracket-character-or-character-code?
;;;         normally-dont-space-before-p)
;;;      )
;;;
;;; Bracket-open-or-close? is either NIL, OPEN, or CLOSE.  Note that bracket
;;; pairs are always found within the

(defparameter-excluding-gsi standard-character-syntax-table
  '((#.%space nil nil nil   nil t   t)
    (#.%\/     t   t   nil   nil t   t)
    (#.%\)     t   nil close #.%\( t   nil)
    (#.%\(     nil t   open  #.%\) nil t)
    (#.%\]     t   nil close #.%\] t   nil)
    (#.%\[     nil t   open  #.%\] nil t)
    (#.%\}     t   nil close #.%\{ t   nil)
    (#.%\{     nil t   open  #.%\} nil t)
    (#.%\!     t)
    (#.%\,     t)
    (#.%\:     t)                                ; what about "::"; hmmm...!
    (#.%\;     t)
    (#.%\?     t)

    (#.%\\     t   t   nil   nil t   t)        ; backslash

    ;; comment format: <adobe name> / <official unicode data>
    ;; exclamdown / 00A1;INVERTED EXCLAMATION MARK;Po;0;ON;;;;;N;;;;;
    (#X00A1 t)
    ;; trademark / 2122;TRADE MARK SIGN;So;0;ON;<+sup> 0054 004D <-sup>;;;;N;TRADEMARK;;;;
    (#X2122 t)
    ;; registered / 00AE;REGISTERED SIGN;So;0;ON;<+circled> 0052 <-circled>;;;;N;REGISTERED TRADE MARK SIGN;;;;
    (#X00AE t)
    ;; questiondown / 00BF;INVERTED QUESTION MARK;Po;0;ON;;;;;N;;;;;
    (#X00BF t)))

;; The characters / and \ began not liking space after or before themselves
;; today, for 4.0. (MHD 4/16/94)


(defvar-excluding-gsi current-character-syntax-table
    standard-character-syntax-table)

(defun look-up-character-syntax-table-entry (unicode-wide-character)
  (declare (eliminate-for-gsi))
  (assoc unicode-wide-character current-character-syntax-table))


;;; Dont-space-before-character-p is true for
;;;
;;;    Space / \
;;;    ) ] }
;;;    ! , : ; ?
;;;    Exclamdown Trademark Registered

(defun dont-space-before-character-p (unicode-wide-character)
  (declare (eliminate-for-gsi))
  (second (look-up-character-syntax-table-entry unicode-wide-character)))

(defun dont-space-after-character-p (unicode-wide-character)
  (declare (eliminate-for-gsi))
  (third (look-up-character-syntax-table-entry unicode-wide-character)))




;;; Remove-space-before-character-p is true for
;;;
;;;    Space / \ ) ] }
;;;
;;;
;;; Remove-space-after-charactrer-p is true for
;;;
;;;   Space / \ ( [ {

(defun remove-space-before-character-p (unicode-wide-character)
  (declare (eliminate-for-gsi))
  (sixth (look-up-character-syntax-table-entry unicode-wide-character)))

(defun remove-space-after-character-p (unicode-wide-character)
  (declare (eliminate-for-gsi))
  (seventh (look-up-character-syntax-table-entry unicode-wide-character)))

;; Add Kanji characters, too?




;;; `Bracket-open-or-close?' is OPEN for
;;;
;;;    ( [ {
;;;
;;; and is CLOSE for
;;;
;;;    ) ] }

(defun bracket-open-or-close? (unicode-wide-character)
  (declare (eliminate-for-gsi))
  (fourth (look-up-character-syntax-table-entry unicode-wide-character)))





;;;; The G2 Ellipsis



(defparameter ellipsis-text-string (stringw "..."))
(defparameter ellipsis-text-string-length 3)

;; change later, to "##" maybe?

;; At present, "<??>" fails, as does any string containing a punctuation character.




;;;; Twriting G2 Symbols



;; This section moved here from UTILITIES1 to avoid forward reference
;; problems. (MHD 2/20/96)



;;; `Twrite-symbol' writes a G2 symbol.  It "downcases" as appropriate unless
;;; do-not-downcase? is true.  If special variable write-symbols-parsably?  is
;;; true, @'s are inserted as appropriate; this is the "prin1" case for when
;;; symbol is to be written in a context where it may later be parsed as a
;;; token.

;;; `Type-of-syntactic-anomaly' is a global property of syntactically anomalous
;;; G2 symbols; this is fully described in module UTILITIES1.

(def-global-property-name punctuation-mark-p)        ; see module CHARACTERS

(def-global-property-name type-of-syntactic-anomaly)

(def-substitution-macro class-qualified-symbol-p (symbol)
  (and (eq (symbol-package symbol) keyword-package-1)
       (loop with symbol-name-text-string = (symbol-name-text-string symbol)
             with symbol-name-length
               = (text-string-length symbol-name-text-string)
             for i from 0 below symbol-name-length
             for this-char = (charw symbol-name-text-string i)
             thereis (and (char=w this-char #.%\:)
                          (<f (1+f i) symbol-name-length)
                          (char=w (charw symbol-name-text-string (1+f i))
                                  #.%\:)))))

;; THIS IS BOGUS!  Pairs of colon's (:'s) can occur in a symbol without any
;; problem.  The reader (tokenizer) lets them in as long as they're quoted.
;; This also didn't deal with Gensym encoding of character, which can introduce
;; additional colons that have nothing to do with class qulifiers; however, that
;; issue goes away with Unicode wide strings (the new implementation of text
;; strings).  If there were to be the new rule banning ::'s from appearing in a
;; symbol, it would have to documented, and supported by the symbol writer, the
;; symbol reader (tokenizer), the reader for old KBs, functions that import
;; symbol names from wherever, particularly GSI, etc. The support for this in
;; twrite-symbol is broken -- it assumes that because :: appears in a symbol,
;; should be written entirely unparsably -- wrong.  The interning of the symbols
;; in the keyword package, would be partially better, but I see no corresponding
;; interning done in EDIT1's tokenizer. (UPDATE: Why? Because it's done by
;; explicit grammar, not by tokenization (!))  Finally, it is wrong, to begin
;; with, to do a search over a symbol every time you want this information; it
;; should be stored on the symbol's plist, or in a hash table tied to the
;; symbol! If we had our own symbols (as structures, say), they would have an
;; additional slot to hold this information.  Review with JED, GHW, and JRA! See
;; /home/mhd/dev/symbols.text!  (MHD 2/20/96)


(defun twrite-symbol (symbol &optional do-not-downcase?)
  (let ((which-characters-not-to-downcase? (if do-not-downcase? :all)))
    (cond
      ((eq (get-current-twriting-output-type) 'wide-string)
       (twrite-symbol-into-text-string
         symbol which-characters-not-to-downcase?))
      (t
       (let* ((temporary-text-string
                (twith-output-to-text-string
                  (twrite-symbol-into-text-string
                    symbol which-characters-not-to-downcase?)))
              (temporary-gensym-string
                (wide-string-to-gensym-string temporary-text-string)))
         (twrite-portion-of-gensym-string-unparsably
           temporary-gensym-string nil nil)
         (reclaim-text-string temporary-text-string)
         (reclaim-gensym-string temporary-gensym-string))))))

;; In 5.0, old body of twrite-symbol moved into twrite-symbol-into-text-string,
;; which were moved to UNICODE since 4.0.

;; See get-next-token-if-available in module EDIT.

;; Note that twrite-symbol assumes that the symbol-name is a valid G2 gensym string!



;;; `Write-name-for-frame' writes name as an all-caps symbol.

(defmacro write-name-for-frame (name)
  `(twrite-symbol ,name t))

;; Consider writing names, by default, with an initial capital only.



;;; `Write-symbol-with-a-or-an' writes symbol preceded by "a" or "an", according to
;;; whether symbol starts without or with a vowel.

(defun write-symbol-with-a-or-an (symbol &optional capitalize?)
  (declare (eliminate-for-gsi))
  (let ((symbol-name-text-string (symbol-name-text-string symbol)))
    (twrite-general-string
      (wide-character-case (char-upcasew (charw symbol-name-text-string 0))
        ;; fix for Kanji and European vowels!
        ((#.%\A #.%\E #.%\I #.%\O #.%\U)
         (if capitalize? "An " "an "))
        (t (if capitalize? "A " "a "))))
    (twrite-symbol symbol)))

;; The capitalization feature has not been used as of 6/24/89.




;;; `Twrite-quoting-character' ...

(defmacro twrite-quoting-character ()
  `(twrite-char #.%\@))



;;; `Twrite-symbol-into-text-string' ... which-characters-not-to-downcase? is the same
;;; basic spec as for copy-wide-string-with-case-conversion, et al.

(defun twrite-symbol-into-text-string (symbol &optional which-characters-not-to-downcase?)
  (let* ((string (symbol-name-text-string symbol))
         (string-length (text-string-length string))
         (class-qualified-symbol? (class-qualified-symbol-p symbol))
         (ellipsis-parsing-state 0)
         (quote-characters-as-appropriate?
           (when write-symbols-parsably?  ; optimize as in copy-symbol-name-parsably?
             (unless class-qualified-symbol?
               (not (punctuation-mark-p symbol))))))
    (cond
      ((or (not (eq which-characters-not-to-downcase? ':all))
           quote-characters-as-appropriate?)
       (loop with i = 0
             with character
             as previous-character? = nil then character
             until (>=f i string-length)
             do (setq character
                      (read-character-from-text-string string i))
                (setq ellipsis-parsing-state
                      (if (and (/=f ellipsis-parsing-state
                                    ellipsis-text-string-length)
                               (char=w character (charw ellipsis-text-string
                                                        ellipsis-parsing-state)))
                          (1+f ellipsis-parsing-state)
                          0))
                (when (and quote-characters-as-appropriate? ; see note (MHD 2/20/96)
                           (or (not (simple-symbol-character-p character))
                               (lower-case-pw character)
                               (=f ellipsis-parsing-state
                                   ellipsis-text-string-length)
                               (if (=f i 1)
                                   (type-of-syntactic-anomaly symbol))))
                  ;; If we've printed the quoting character due to an ellipsis-like
                  ;; text string, then reset the ellipsis-parsing state to 1.
                  (when (=f ellipsis-parsing-state ellipsis-text-string-length)
                    (setq ellipsis-parsing-state 1))
                  (twrite-quoting-character))
                (twrite-char
                  (if (case which-characters-not-to-downcase?
                        (:all t)
                        (:first (=f i 1))
                        (:first-of-each-word
                         (or (null previous-character?)
                             (word-separator-p previous-character?)))
                        (:none nil)
                        (t nil))
                      character
                      (char-downcasew character)))))
      (t
       (twrite-portion-of-wide-string-unparsably
         string 0 string-length)))))

;; See if this can be combined parts of copy-wide-string-with-case-conversion to
;; avoid duplication of the interpreting of which-characters-not-to-downcase?.
;; Converting old do-not-downcase? to new which-characters-not-to-downcase? in
;; old callers of twrite-symbol must be done with care, and is being deferred.
;; I converted just this call in order to support writing Keystrokes with
;; initial caps, without the need for a special-purpose function, which I
;; noticed needed repair and didn't want to "fix".

;; Replacement for twrite-symbol which came to call this and
;; twrite-symbol-into-gensym-string, below.

;; NOTE: Simple-symbol-character-p is too simple under Unicode, and even under
;; the old Gensym character set!  The handling of class qualifiers is broken, as
;; noted elsewhere.  A proposal for dealing with it is under discussion with
;; JED. (MHD 2/20/96)

;; Keep this in synch with all of the symbol token readers used throughout G2
;; and with the reader for symbols saved in KBs.





;;;; Twriting Strings



;;; `twrite-general-string' writes a string.  If special variable write-strings-parsably?
;;; is true, string is written parsably: double-quotes are written to delimit the
;;; string and @'s are inserted as appropriate (to quote characters special to the
;;; token reader, i.e., `"' and `@').

;;; For now, twrite-general-string handles both text strings and gensym strings.  Thus,
;;; "string" here is a union type.  Note that with 1259 uses of twrite-general-string in
;;; the Lisp sources, this is the most practical plan.

;;; For now, only the cases of twriting wide strings, parsably or not, in a
;;; current wide string output context are extremely optimized.  The other cases
;;; are quite efficient, but deservedly less effort has gone into optimizing
;;; them to the max.

;;; However, it is an error for string to contain other than 8-bit characters if
;;; called in a current gensym string context.  This, and its subfunctions, do
;;; not do any kind of encoding for 8-bit output strings.  Accordingly, if
;;; arbitrary text strings are to be used for output to gensym strings, they
;;; should be run through export-text-string.

(defun-void twrite-general-string (string)
  (cond
    #+development
    ((null string)
     (cerror "Go on, not twriting anything"
             "twrite-general-string must be given a string.  This will be an ~
              abort in distribution.")
     nil)
    (write-strings-parsably?
     (twrite-portion-of-string-parsably string nil nil))
    (t
     (twrite-portion-of-string-unparsably string nil nil))))


;;; `twrite-beginning-of-wide-string' - can be used under the following
;;; circumstances: (a) the string to be twritten is a wide-string;
;;; (b) the first character to be written is the zeroth;  (c) the
;;; last character to be written is known ahead of time.  Calling
;;; it "beginning" is sort of misleading -- by far the more common
;;; usage will be to print the entire string, which counts as
;;; printing the beginning of the string by the three qualifications
;;; above.

(defun-void twrite-beginning-of-wide-string (wide-string first-n-characters)
  (if write-strings-parsably?
      (if (eq (get-current-twriting-output-type) 'wide-string)
          (twrite-portion-of-wide-string-parsably-to-current-wide-string
            wide-string 0 first-n-characters)
          (twrite-portion-of-wide-string-parsably-to-current-gensym-string
            wide-string 0 first-n-characters))
      (if (eq (get-current-twriting-output-type) 'wide-string)
          (twrite-beginning-of-wide-string-unparsably-to-current-wide-string
            wide-string first-n-characters)  ;; just optimize this case
          (twrite-portion-of-wide-string-unparsably-to-current-gensym-string
            wide-string 0 first-n-characters))))



;;; `twrite-string' - optimizes twriting constant strings by calculating the
;;; length at compilation time.

(defmacro twrite-string (string)
  (if (wide-string-p string)
      (let ((len (lengthw string)))
        (if (=f len 1)
            `(twrite-wide-character-macro
               ,(charw string 0))
            `(twrite-beginning-of-wide-string
               ,string ,len)))
      (if (stringp string)
          (let ((wstring (stringw string)))
            `(twrite-beginning-of-wide-string
               ,wstring ,(lengthw wstring)))
          `(twrite-general-string ,string))))


;;; `Twrite-portion-of-string-parsably' writes a subsequence of string,
;;; parsably, beginning with start? (0 if nil) and ending before end? (length of
;;; string if nil).  It is an error for string to contain other than 8-bit
;;; characters if called in a current gensym string context.

(defun-void twrite-portion-of-string-parsably (string start? end?)
  (cond
    ((wide-string-p string)
     (twrite-portion-of-wide-string-parsably string start? end?))
    (t
     (twrite-portion-of-gensym-string-parsably string start? end?))))

(defun-void twrite-portion-of-wide-string-parsably (wide-string start? end?)
  (cond
    ((eq (get-current-twriting-output-type) 'wide-string)
     (twrite-portion-of-wide-string-parsably-to-current-wide-string
       wide-string start? end?))
    (t
     (twrite-portion-of-wide-string-parsably-to-current-gensym-string
       wide-string start? end?))))

(defun-void twrite-portion-of-wide-string-parsably-to-current-wide-string
    (wide-string start? end?)
  (let ((wide-character #u0000))
    (declare (type wide-character wide-character))
    (loop with start fixnum = (or start? 0)
          with end fixnum = (or end? (lengthw wide-string))
          with i fixnum = start
          initially
            (assure-current-wide-string-available-buffer-space
              (+f fill-pointer-for-current-wide-string
                  (-f end start)
                  2))        ; 2 for quotes ("")
            (twrite-wide-character-in-available-buffer-space #.%\")
          while (<f i end)
          do (loop for j from i below end
                   do (setq wide-character (charw wide-string j))
                   when (or (char=w wide-character #.%\@)
                            ;; This would technically be the right thing to do
                            ;; in terms of making strings "readable" by the
                            ;; G2 reader, however, it would not be readable
                            ;; according to English conventions, or according
                            ;; to the conventions of other computer systems,
                            ;; e.g., VMS command lines, etc.  We are commenting
                            ;; it out to avoid, for example, printing VMS
                            ;; pathnames on the logbook as "btdisk:@[bt...]".
                            ;; (MHD 1/17/96)
                            ;; GENSYMCID-858: Left square bracket in text attributes.
                            ;; Comment next line again. -- Glority, 2012/9/24
                            ;; (char=w wide-character #.%\[)
                            (char=w wide-character #.%\"))
                     do
                       (unless (=f i j)
                         (twrite-wide-string-in-available-buffer-space
                           wide-string i j))
                       (assure-current-wide-string-available-buffer-space
                         (+f fill-pointer-for-current-wide-string
                             (-f end j)
                             2)) ; ""'s
                       (twrite-wide-character-in-available-buffer-space
                         #.%\@)
                       (twrite-wide-character-in-available-buffer-space
                         wide-character)
                       (setq i (+f j 1))
                       (return)
                   finally
                     (twrite-wide-string-in-available-buffer-space
                       wide-string i end)
                     (setq i end))
          finally
            (twrite-wide-character-in-available-buffer-space #.%\"))))


(defun-void twrite-portion-of-wide-string-parsably-to-current-gensym-string
    (wide-string start? end?)
  (let ((wide-character #u0000))
    (declare (type wide-character wide-character))
    (loop with start fixnum = (or start? 0)
          with end fixnum = (or end? (lengthw wide-string))
          initially
            (twrite-char #.%\")
          for i from start below end
          do (setq wide-character (charw wide-string i))
             (when (or (char=w wide-character #.%\@)
                       (char=w wide-character #.%\[)
                       (char=w wide-character #.%\`)
                       (char=w wide-character #.%\"))
               (twrite-char #.%\@))
             (twrite-char wide-character)
          finally
            (twrite-char #.%\"))))

(defun-void twrite-portion-of-gensym-string-parsably
    (gensym-string start? end?)
  (let ((character #\a))
    (declare (type character character))
    (loop with simple? = (simple-gensym-string-p gensym-string)
          with start fixnum = (or start? 0)
          with end fixnum = (or end? (glength gensym-string simple?))
          initially
            (twrite-char #\")
          for i from start below end
          do (setq character (gchar gensym-string i simple?))
             (when (or (char= character #\@)
                       (char= character #\"))
               (twrite-char #\@))
             (twrite-char character)
          finally
            (twrite-char #\"))))




;;; `Twrite-portion-of-string-unparsably' is writes a subsequence of string,
;;; beginning with start and ending before end.  This never writes quotes and
;;; does not obey write-strings-parsably?.  It is an error for string to contain
;;; other than 8-bit characters if called in a current gensym string context.

(defun-void twrite-portion-of-string-unparsably (string start? end?)
  (cond
    ((wide-string-p string)
     (twrite-portion-of-wide-string-unparsably string start? end?))
    (t
     (twrite-portion-of-gensym-string-unparsably string start? end?))))

(defun-void twrite-portion-of-wide-string-unparsably (wide-string start? end?)
  (cond
    ((eq (get-current-twriting-output-type) 'wide-string)
     (twrite-portion-of-wide-string-unparsably-to-current-wide-string
       wide-string start? end?))
    (t
     (twrite-portion-of-wide-string-unparsably-to-current-gensym-string
       wide-string start? end?))))

(defun-void twrite-portion-of-wide-string-unparsably-to-current-wide-string
    (wide-string start? end?)
  (let ((start (or start? 0))
        (end (or end? (lengthw wide-string))))
    (assure-current-wide-string-available-buffer-space
      (+f fill-pointer-for-current-wide-string (-f end start)))
    (twrite-wide-string-in-available-buffer-space wide-string start end)))


(defun-void twrite-portion-of-wide-string-unparsably-to-current-gensym-string
    (wide-string start? end?)
  (let* ((start (or start? 0))
         (end (or end? (lengthw wide-string))))
    (declare (type fixnum start end))
    (loop for i from start below end
          for char = (charw wide-string i)
          do (twrite-char (if (char=w char #.%line-separator)
                              #\newline
                              char)))))

(defun-void twrite-portion-of-gensym-string-unparsably (gensym-string start? end?)
  (let* ((simple? (simple-gensym-string-p gensym-string))
         (start (or start? 0))
         (end (or end? (glength gensym-string simple?))))
    (declare (type fixnum start end))
    (loop for i from start below end
          do (twrite-char (gchar gensym-string i simple?)))))

;; For historians: the former function "twrite-portion-of-string" has become
;; various pieces of the above.

;; Old comment, applies to practically all of the above functions in this
;; section: this could be further optimized, defined maybe as a macro, and used
;; where appropriate (e.g., write-symbol and write-string) to copy a sequence of
;; characters more efficiently!


;;; `twrite-beginning-of-wide-string-unparsably-to-current-wide-string' - is an
;;; optimization of twrite-portion-of-wide-string-unparsably-to-current-wide-string
;;; for the (very common) case of start being zero, and end being specified.

(defun-void twrite-beginning-of-wide-string-unparsably-to-current-wide-string
    (wide-string first-n-characters)
  (assure-current-wide-string-available-buffer-space
    (+f fill-pointer-for-current-wide-string first-n-characters))
  (twrite-wide-string-in-available-buffer-space wide-string 0 first-n-characters))





;;;; Language Tagging


;;; Do we need language tagging?  Do we need it in G2?

;;; I think the answer to both questions is YES.

;;; If so, where do we put it?

;;; File output: use a special language-tagged Unicode.  Copy and/or license
;;; Gamma's format.  Otherwise, you won't get Japanese/Korean back as
;;; Japanese/Korean, but rather as indistinguished "Han".

;;; Symbols: put a language marker on all symbols?  Well, this wouldn't work
;;; because you then could not have multiple languages within a symbol.  This
;;; would preclude symbols like
;;;
;;;   [ENG]SATELLITE-IS-IN-[JAP]<tokyo, written in Japanese>
;;;
;;; where [ENG] and [JAP] are not part of the symbol but are language IDs,
;;; and <tokyo, written in Japanese> is the Japanese (Kanji) letters for the
;;; word Tokyo.  It's a hassle to impose limitations on where language
;;; tags can go because they often get in the way.
;;;
;;; On the other hand, having two symbols be distinguishable based just on
;;; language is a bad thing.  This would be something like having letter case or
;;; font or style (bold, italic, underline) distinguish a symbol.
;;;
;;; So, what to do....

;;; Cut buffer: if you mark Japanese text and insert it somewhere, it should be
;;; inserted as Japanese text, at least usually, I would think.

;;; Text: As you type in text in a given language, you have to maintain the info
;;; as to what language it's in.






;;;; Twriting Numbers

;; This section moved here from UTILITIES1 because it needs
;; twith-output-... macros, and it can't be in UTILITIES1 because GSI needs it.



;;; The variable `wide-twrite-fixnum-buffer' holds a wide string that is used as
;;; a buffer.  It is at least long enough to hold the printed representation of
;;; any fixnum.  Its length is given by the constant
;;; `length-of-wide-twrite-fixnum-buffer'

;;; GENSYM-47130: increase fixnum buffer size for 64-bit fixnums in the future.
;;; 2^64 = 18446744073709551616 which is 20 digits long, so 24 should be enough.
;;; Macro fixnum-twrite-length is updated also, see below.
;;; -- Chun Tian (binghe), 2010/1/23

(def-system-variable wide-twrite-fixnum-buffer unicode
  (:funcall make-wide-string-function 24) nil t)

(defconstant length-of-wide-twrite-fixnum-buffer 24)

;; The function is noly for the length of the 32bit positive fixnum
(defmacro fixnum-length-32bit (fixnum-to-write)
  (let ((v (gensym)))
    `(let ((,v ,fixnum-to-write))
       (declare (type fixnum ,v))
       (if (<f ,v 10000) ;the scope of fixnum is 0~9999
           (if (<f ,v 100) 
               (if (<f ,v 10) 1 2)    ;the scope of fixnum is 0~99
               (if (<f ,v 1000) 3 4)) ;the scope of fixnum is 100~9999
           (if (<f ,v 1000000)  ;the scope of fixnum is 10000 ~ 99999999
               (if (<f ,v 100000) 5 6) ;the scope of fixnum is 10000 ~ 999999
               (if (<f ,v 10000000)    ;the scope of fixnum is 1000000 ~ 99999999
                   7
                   (if (<f ,v 100000000) 8 9)))))))

;; The function is noly for the length of the number scope 0 ~ 999'999'999'999
(defmacro fixnum-twrite-length-2 (fixnum-to-write)
  (let ((v (gensym)))
    `(let ((,v ,fixnum-to-write))
       (declare (type fixnum ,v))
       ;;Judge the fixnum whether it is a longer than 999999
       (if (<=f ,v 999999)
           (fixnum-length-32bit ,v)
         ;;if the fixnum is a long number, calc the floor number with 1000000
         ;;Then calc the length of floor number by fixnum-length function
         ;;The real length of the fixnum is that the floor lenght plus 6
	 (let ((tmpf (floorf-positive ,v 1000000)))
           (+f 6 (fixnum-length-32bit tmpf)))))))

(defvar most-negative-fixnum-as-string
  (format nil "~D" most-negative-fixnum))

(defvar length-of-most-negative-fixnum-as-string
  (length most-negative-fixnum-as-string))
                                        
(defmacro fixnum-twrite-length (fixnum-to-write)
  (let ((v (gensym)))
    `(let ((,v ,fixnum-to-write))
       (declare (type fixnum ,v))
       (cond ((=f ,v most-negative-fixnum)
	      length-of-most-negative-fixnum-as-string)
	     ((and (<=f ,v 999999) (>=f ,v -999999))
	      (+f (if (<f ,v 0) 1 0)
		  (fixnum-length-32bit (absf ,v))))
	     ;; if the fixnum is a long number, calc the floor number with 1000000
	     ;; Then calc the length of floor number by fixnum-length function
	     ;; The real length of the fixnum is that the floor lenght plus 6
	     (t
	      (let ((tmpf (floorf-positive (absf ,v) 1000000)))
		(+f (if (<f ,v 0) 1 0)
		    6
		    (fixnum-twrite-length-2 tmpf))))))))

#+development
(defun test-fixnum-twrite-length (fixnum)
  (if (= (length (format nil "~d" fixnum))
         (fixnum-twrite-length fixnum))
      (fixnum-twrite-length fixnum)
      nil))

#+development
(progn (test-assertion (test-fixnum-twrite-length most-positive-fixnum))
       (test-assertion (test-fixnum-twrite-length most-negative-fixnum))
       (test-assertion (test-fixnum-twrite-length (+ most-negative-fixnum 1)))
       (test-assertion (test-fixnum-twrite-length -1000))
       (test-assertion (test-fixnum-twrite-length -999))
       (test-assertion (test-fixnum-twrite-length 1000))
       (test-assertion (test-fixnum-twrite-length 999))
       (test-assertion (test-fixnum-twrite-length -1))
       (test-assertion (test-fixnum-twrite-length 1))
       (test-assertion (test-fixnum-twrite-length 0))
       (test-assertion (test-fixnum-twrite-length 1986)))

(defun-substitution-macro write-positive-fixnum-in-radix-to-the-buffer (fixnum-to-write radix)
  (let ((buffer wide-twrite-fixnum-buffer)
        (last-index (-f length-of-wide-twrite-fixnum-buffer 1))
        (digit-count 0))
    (declare (type fixnum last-index digit-count))
    (macrolet ((push-digit (digit)
                 `(progn
                    (setf (charw buffer (-f last-index digit-count)) ,digit)
                    (incff digit-count))))
      (loop for number fixnum = fixnum-to-write then next
            for next fixnum = (floorf-positive number radix)
            for digit fixnum = (-f number (*f next radix))
            do (push-digit (digit-charw digit radix))
            until (=f 0 next)))
    digit-count))

;;; `Twrite-fixnum-into-wide-string' writes fixnum-to-write to wide-string, starting at
;;; index start-index, and return the number of characters written.

(defun-simple twrite-fixnum-into-wide-string (fixnum-to-write wide-string start-index)
  (declare (type fixnum fixnum-to-write start-index))
  (cond
    ;; special treatment because (- most-negative-fixnum) is not fixnum.
    ((=f fixnum-to-write most-negative-fixnum)
     (with-current-wide-string
       (let* ((write-strings-parsably? nil)
	      (result-length length-of-most-negative-fixnum-as-string))
	 (twrite-general-string most-negative-fixnum-as-string)
	 (memcpy-portion-of-wide-string-into-wide-string
	   current-wide-string 0 result-length
	   wide-string start-index)
	 result-length)))
    ;; other cases
    (t
     (let* ((positive-fixnum
	     (if (<f fixnum-to-write 0)
		 (-f fixnum-to-write)
	       fixnum-to-write))
	    (digit-count
	     (write-positive-fixnum-in-radix-to-the-buffer positive-fixnum 10))
	    (source-start
	     (-f length-of-wide-twrite-fixnum-buffer digit-count))
	    (result-length digit-count))
       (declare (type fixnum
		      positive-fixnum result-length digit-count source-start))
       (when (<f fixnum-to-write 0)
	 (setf (charw wide-string start-index) #.%\-)
	 (incff start-index)                ; changes arg
	 (incff result-length))
       (memcpy-portion-of-wide-string-into-wide-string
	 wide-twrite-fixnum-buffer source-start length-of-wide-twrite-fixnum-buffer
	 wide-string start-index)
       result-length))))

(defun-substitution-macro twrite-positive-fixnum-in-radix-macro (fixnum-to-write radix)
  (let ((digit-count (write-positive-fixnum-in-radix-to-the-buffer fixnum-to-write radix)))
    (declare (type fixnum digit-count))
    (cond
      ((eq (get-current-twriting-output-type) 'wide-string)
       (twrite-portion-of-wide-string-unparsably-to-current-wide-string
         wide-twrite-fixnum-buffer (-f length-of-wide-twrite-fixnum-buffer digit-count)
         length-of-wide-twrite-fixnum-buffer))
      (t
       (twrite-portion-of-string-unparsably
         wide-twrite-fixnum-buffer (-f length-of-wide-twrite-fixnum-buffer digit-count)
         length-of-wide-twrite-fixnum-buffer)))))

(def-substitution-macro twrite-positive-fixnum-macro (fixnum-to-write)
  (twrite-positive-fixnum-in-radix-macro fixnum-to-write 10))

(defmacro twrite-fixnum-macro (fixnum-to-write)
  (avoiding-variable-capture (fixnum-to-write &aux positive-fixnum)
    `(let ((,positive-fixnum
              (cond
                ((<f ,fixnum-to-write 0)
                 (cond ((eq (get-current-twriting-output-type) 'wide-string)
                        (twrite-wide-character #.%\-))
                       (t (twrite-simple-character-to-current-gensym-string #\-)))
                 (-f ,fixnum-to-write))
                (t ,fixnum-to-write))))
       (declare (type fixnum ,positive-fixnum))
       (twrite-positive-fixnum-macro ,positive-fixnum))))

;;; `Twrite-fixnum' writes fixnum-to-write.

(defun-void twrite-fixnum (fixnum-to-write)
  (declare (type fixnum fixnum-to-write))
  (if (=f fixnum-to-write most-negative-fixnum)
      (let ((write-strings-parsably? nil))
        (twrite-general-string most-negative-fixnum-as-string))
      (twrite-fixnum-macro fixnum-to-write)))

;;; `Twrite-positive-fixnum' writes fixnum-to-write, which must be a
;;; non-negative fixnum.

(defmacro decimal-digit-char (0-thru-9)
  `(convert-ascii-to-simple-character (+f #x30 ,0-thru-9)))

;; see notes for wide-twrite-fixnum-buffer
(defvar twrite-fixnum-buffer (make-string 24)) ; previous value: 12 / 32 

(defun-void twrite-positive-fixnum (fixnum-to-write)
  (declare (type fixnum fixnum-to-write))
  (twrite-positive-fixnum-macro fixnum-to-write))



;;; `Twrite-positive-fixnum-in-radix' writes fixnum-to-write, which must be
;;; a non-negative fixnum, in the specified radix.

(defun-void twrite-positive-fixnum-in-radix (fixnum-to-write radix)
  (declare (type fixnum fixnum-to-write radix))
  (twrite-positive-fixnum-in-radix-macro fixnum-to-write radix))

;; Positive is a misnomer; here, it really means non-negative.

;; This and the function below could now be used to implement format directives
;; x (print in hex), o (print in octal), or nr (print in radix n).  Consider doing
;; this.

;;; `Twrite-positive-bignum' writes positive-bignum.

(defun twrite-positive-bignum (positive-bignum)
  (declare (eliminate-for-gsi))
  (if (> positive-bignum 9)
      (multiple-value-bind (quotient remainder)
          (floor positive-bignum 10)
	(let ((rem (coerce-number-to-fixnum remainder)))
	  (declare (type fixnum rem))
	  (if (<= quotient most-positive-fixnum)
	      (twrite-positive-fixnum quotient)
	    (twrite-positive-bignum quotient))
	  (twrite-char (decimal-digit-char rem))))
    (let ((rem (coerce-number-to-fixnum positive-bignum)))
      (twrite-char (decimal-digit-char rem)))))

;;; `Twrite-positive-bignum-in-radix' writes positive-bignum in the specified radix.

(defun twrite-positive-bignum-in-radix (positive-bignum radix)
  (declare (type fixnum radix))
  (if (>= positive-bignum radix)
      (multiple-value-bind (quotient remainder)
          (floor positive-bignum radix)
	(let ((rem (coerce-number-to-fixnum remainder)))
	  (declare (type fixnum rem))
	  (if (<= quotient most-positive-fixnum)
	      (twrite-positive-fixnum-in-radix quotient radix)
	    (twrite-positive-bignum-in-radix quotient radix))
	  (twrite-char (digit-char rem radix))))
    (let ((rem (coerce-number-to-fixnum positive-bignum)))
      (twrite-char (digit-char rem radix)))))

(defun-void twrite-n-digit-number-with-0-pad (n number)
  (loop with digits
          = (nreverse (loop for i from 1 to n
                            for num = number then (floorf num 10)
                            collect (modf num 10) using gensym-cons))
        for digit in digits
        do (twrite-char
             (digit-charw digit))
        finally (reclaim-gensym-list digits)))

(def-substitution-macro twrite-positive-long-macro (long-to-write)
  (twrite-positive-bignum-in-radix long-to-write 10))

(defmacro twrite-long-macro (long-to-write)
  (avoiding-variable-capture (long-to-write &aux positive-long)
    `(cond ((=l ,long-to-write most-negative-int64)
	    (let ((write-strings-parsably? nil))
	      (twrite-general-string #.(format nil "~D" most-negative-int64))))
	   (t
	    (let ((,positive-long
		   (cond
		     ((<l ,long-to-write 0)
		      (cond ((eq (get-current-twriting-output-type) 'wide-string)
			     (twrite-wide-character #.%\-))
			    (t
			     (twrite-simple-character-to-current-gensym-string #\-)))
		      (-l ,long-to-write))
		     (t ,long-to-write))))
	      (declare (type ,(gensym-long-type) ,positive-long))
	      (twrite-positive-long-macro ,positive-long))))))

(defun-void twrite-long-function (long-to-write)
  (with-temporary-bignum-creation
    (twrite-long-macro long-to-write)))

(defun-void twrite-long (long-to-write)
  (with-temporary-bignum-creation
    (twrite-long-macro long-to-write)
    (twrite-general-string "L")))


;;; `Write-floating-point-number' writes the representation of a float.

;;; The argument may be any type of real (non-complex) number, but it is immediately
;;; coerced to a gensym-float, unless it is too big.

;;; The basic format is "dddd.ddd" or "-ddddd.ddd" where the length of the first
;;; string of digitss is integral-size, and the length of the second is fraction-size.

;;; When a number is too big to be represented in the fixed format discussed above
;;; (i.e. when its magnitude is greater than or equal to (10 ^ integal-size))
;;; an exponent notation is then used. The number of significant digits is then
;;; specified by the parameter precision.

;; The effect of trailing-zeros? is documented for the function write-integer-in-field.

;;; Representing small numbers presents a different problem. There are situations in which
;;; it would be correct to represent .000056 as "000.00" and situations where this is
;;; inappropriate. If  small-number-limit? is a number, and the magnitude of the
;;; number being written is less than that, then scientific notation is used
;;; to represent the small number, if doing so would display precision that would be
;;; lost in the fixed field format. The number of significant digits is again
;;; controlled by precision. The test-suite that follows provides some interesting
;;; examples of this.



;;; The parameters smallest-order-of-magnitude and float-with-smallest-order-of-
;;; magnitude are used to determine the lower boundary of the order-of-magnitude
;;; macro.  There are problems giving very small floats to LOG, in that it
;;; "blows up" in some C math libraries.

(defparameter
  smallest-order-of-magnitude
  #+(or chestnut chestnut-3) ;Chestnut3.1
  -307
  #-(or chestnut chestnut-3) ;Chestnut3.1
  (ceiling (log least-positive-normalized-gensym-float 10)))

;; Bill has assured me that he will have a C function soon which returns the
;; minimum exponent of a double.  That should be inserted here when it is ready.
;; -jra 4/23/91

(defparameter-excluding-gsi float-with-smallest-order-of-magnitude
  (expt #.(coerce-to-gensym-float 10.0) smallest-order-of-magnitude))



;;; `Order-of-magnitude' return the largest integer n such that
;;; (expt 10 n) < magnitude.

;; Note that this could be optimized more if only gensym-floats were allowed in
;; this function.  The current usage of this macro allows bignums to be given to
;; this, so generic arithmetic must be used.

(def-substitution-macro order-of-magnitude (magnitude)
  (if (<= magnitude float-with-smallest-order-of-magnitude)
      smallest-order-of-magnitude
      (floor (log magnitude 10.0))))




;; Note also that these functions will create an error condition if out of range.

;;; Floating-power-of-ten raises 10 to the power of its arg as a normalized
;;; floating point number. If the argument is out of bounds, an aref out of bounds
;;; will occur. WATCH OUT.

(defmacro floating-power-of-ten (exponent)
  `(expt 10.0 ,exponent))



;;; Order-of-largest-fixnum-power-of-ten is the largest integer
;;; which is the log base 10 of a fixnum.  This is machine dependent.

(defparameter-excluding-gsi order-of-largest-fixnum-power-of-ten
              (floor (log most-positive-fixnum 10)))



;;; Integer-decade-table is an array of positive integral powers of 10 up to
;;; and including the largest such fixnum. This is machine dependent.

(defparameter-excluding-gsi integer-decade-table
              (loop with table = (make-array (+ order-of-largest-fixnum-power-of-ten 1))
                    for i from 0 to order-of-largest-fixnum-power-of-ten
                    do (setf (svref table i) (expt 10 i))
                    finally (return table)))


;;; Fixnum-power-of-ten raises its arg to the power of 10. The arg
;;; must be a non-negative fixnum.  If the result would be too large
;;; to be a fixnum, an aref out of bounds will occur ionstead. WATCH OUT.

(defmacro fixnum-power-of-ten (small-integer)
  `(svref integer-decade-table ,small-integer))




;;; The function `fixnum-order-of-magnitude' takes a positive fixnum argument
;;; and returns the largest fixnum such that (expt 10 value) <= argument.
;;; It does this by an efficient binary search
;;; through an array of powers of 10 which includes all such numbers
;;; which are representable as normalized gensym-floats. This is machine
;;; dependent.

(defun-simple fixnum-order-of-magnitude (non-negative-fixnum)
  (declare (eliminate-for-gsi))
  (loop for index from (1-f (length-of-simple-vector integer-decade-table)) downto 0
        when (<=f (svref integer-decade-table index) non-negative-fixnum)
          return index
        finally
          (return 0)))




;;; The function `twrite-fixnum-in-fixed-field' takes a fixnum and the width of
;;; the field that it should be written within.  It assumes space characters to
;;; pad out the width to the left of the number.  There are optional arguments
;;; to change the padding to the right and to replace the pad char with
;;; something other than a space.  Even if the given field is too narrow, the
;;; number will be written in its entirety with no padding.

(defun twrite-fixnum-in-fixed-field
    (fixnum-to-write field-width &optional pad-right? (pad-char #.%space))
  (declare (type fixnum fixnum-to-write)
	   (eliminate-for-gsi))
  (let ((number-width
          (+f (fixnum-order-of-magnitude (absf fixnum-to-write))
              (if (minuspf fixnum-to-write) 2 1))))
    (when pad-right? (twrite-fixnum fixnum-to-write))
    (loop repeat (-f field-width number-width) do
      (twrite-char pad-char))
    (when (not pad-right?) (twrite-fixnum fixnum-to-write))
    nil))




;;; The constant `plus-infinity-single-float' and `minus-infinity-single-float'
;;; represent infinity in Lucid.  -pto 22nov88

#+lucid
(defconstant plus-infinity-single-float 1.0)

#+lucid
(defconstant minus-infinity-single-float -1.0)

;; The above constants need to be defined in Lucid 3.0, or some other kind of
;; floating point divide by zero error needs to be handled!!!  -jra 3/27/89


(defmacro infinite-lucid-number-p-1 (number)
  `(or (= ,number plus-infinity-single-float)
       (= ,number minus-infinity-single-float)))

(defmacro infinite-lucid-number-p (number)
  (if (symbolp number)
      `(infinite-lucid-number-p-1 ,number)
      (let* ((number-var (gensym)))
        `(let* ((,number-var ,number))
           (infinite-lucid-number-p-1 ,number-var)))))

(defun write-integer-in-field (integer field-width trailing-zeros?)
  (declare (eliminate-for-gsi))
  (loop with quotient
        with remainder = integer
        for index from (-f field-width 1) downto 0
        do (multiple-value-setq (quotient remainder)
             (floor remainder (fixnum-power-of-ten index)))
           (twrite-fixnum quotient)                ; twrite-positive-fixnum?
        until (and (null trailing-zeros?)
                   (=f remainder 0))))

#+development
(defparameter num-test-suite
  '(0.0 .09 .1 .11 1.0 1.5 1.2 4325435.34 .0000543
    .0004 .00004 .000004
    .303 .3003 .30003 .300003 .0303 .03003 .030003
    .03984 .003984 .003999 .00399999
    .0300003 .03000003 .003006 .00300006 .003000006
    .0030000057 .0030000006 34.053 -5342.0 -4524354.0e12
    -.0000004504 1.9 1.99 1.999 1.9999 10.999 10.9999))

#+development
(defun test-floating-numbers ()
  (twith-output-to-text-string
    (loop for num in num-test-suite doing
      (twrite-general-string (format nil "~S~16T" num))
      (twrite-float num)
      (tformat "~c" #.%newline))))        ; was (tformat "~%"), but a newline
                                        ; looks better than \u2028!







;;; `Twrite-positive-fixnum-in-field' ... is supposed to be an improved equivalent of
;;; write-integer-in-field for the fixnum case.  It has not yet been tested. (LH 2/88)

(defun twrite-positive-fixnum-in-field (positive-fixnum field-width trailing-zeros?)
  (declare (eliminate-for-gsi))
  (if (>f field-width 0)
      (let ((quotient (floorf-positive positive-fixnum 10))
            (remainder (modf-positive positive-fixnum 10)))
        (if (and (null trailing-zeros?) (not (=f remainder 0)))
            (setq trailing-zeros? t))                ; changes arg
        (twrite-positive-fixnum-in-field quotient (-f field-width 1) trailing-zeros?)
        (if (or trailing-zeros? (=f field-width 1))
            (twrite-char (digit-char remainder))))))        ; case faster than digit-char?


;;; `twrite-rgb-as-padded-hex'

(defun twrite-rgb-as-padded-hex (r-value g-value b-value)
  (macrolet ((write-hex-two-digits (value)
               `(let ((substitute-value
                        (cond
                          ((<f ,value 0) 0)
                          ((>f ,value 255) 255)
                          (t ,value))))
                  (if (<f substitute-value 16) (twrite-character #.%\0))
                  (tformat "~x" substitute-value))))
    (write-hex-two-digits r-value)
    (write-hex-two-digits g-value)
    (write-hex-two-digits b-value)))


(def-gensym-c-function c-write-float-from-c (:void "g2ext_write_float_from_c")
  ((:string return-string)
   (:string format-string)
   (:fixnum-int precision)
   (:double-float double)))


;; jh, 11/26/91.  Removed #+chestnut compiler switch from new-decade-table-size
;; and new-decade-table.  This is to help bring the Lispm code more in conformance
;; with the code that gets executed in distribution.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant new-decade-table-size 16))

(defmacro make-and-initialize-new-decade-table (size sign)
  `(let ((table (make-array ,size)))
     ,@(loop for i below size
             collect `(setf (svref table ,i)
                            ,(coerce (expt 10 (* i sign)) 'gensym-float)))
     table))

(defparameter new-decade-table
  (make-and-initialize-new-decade-table #.new-decade-table-size  1))

(defparameter new-fractional-decade-table
  (make-and-initialize-new-decade-table #.new-decade-table-size -1))

;; jh, 1/22/92.  Added new-fractional-decade-table, so we can switch to
;; exponential notation when a number is too small, not just when a number is too
;; big.

(defconstant size-of-string-for-returning-floats 100)

(defvar string-for-returning-floats
  (make-string size-of-string-for-returning-floats))



;; jh, 4/4/93.  Modified initialize-string-for-returning-floats to differentiate
;; between Lispm and non-Lispm implementations rather than between Chestnut and
;; non-Chestnut.  This bug showed up because we are now attempting to develop in
;; Lucid as well as the Lispms, and the Lucid we are using lacks the :chestnut
;; feature.


;; jh, 4/17/92.  Introduced the new macro schar-if-appropriate, which will
;; expand into schar in distribution and char on the Lispms.  This will improve
;; performance on distribution platforms.  Note that occasionally we do want to
;; use the slower char instead, even in distribution.  The reason for this is we
;; sometimes want to access characters of a string we obtained through
;; twith-output-to-gensym-string, and there is no guarantee that such strings are
;; simple.  An example of this is the heuristic marked "Try to drop digits from
;; the exponential representation" in twrite-number-string-in-fixed-field.  It
;; uses char because it is examining a string that was produced in earlier
;; heuristics through twith-output-to-gensym-string, and that macro never
;; guarantees to return a simple string.  But most places in distribution, we
;; are simply passing string-for-returning-floats around, and that string is
;; always simple in distribution images.

;; NOTE: (MHD 2/7/96) Lispm -- officially a feature being phased out -- is long
;; obsolete.  I therefore simplified the code, but not all of the comments,
;; by removing most of the #+lispm code, and removing explicit #-lispm's.

(defmacro schar-if-appropriate (possibly-simple-string index)
  `(schar ,possibly-simple-string ,index))




;; Float Writing in G2
;; -------------------

;; jh, 2/12/92.

;; This is a proposal, not a description.  G2 may not behave this way now, but
;; the assertion is that it should.  This proposal has two parts.  The first
;; describes how the G2 end-user can control the writing of floats; the second
;; describes the internal tools used by G2 for writing floats, whether within or
;; outside the control of the user.

;; User Interface for Writing Floats
;; ---------------------------------

;; The G2 end-user has a two options for controlling how floats get written:
;; `implicit mode', where the user makes no choice about how floats should
;; appear, and `ddd-mode', where the user explicitly specifies a format
;; directive (which looks like "ddd.dddd") to control how G2 writes floats.
;; Note that these modes are entered per item: a user may let G2 print, say,
;; readouts in implicit mode but execute inform statements in ddd-mode.  Also
;; note that, depending on the item writing the float, implicit mode may have
;; other behavior not under control of the user, such as suppression of trailing
;; righthand zeros or provision for fixed field size.

;; From the G2 user's point of view, float writing is controlled by two numbers,
;; `left-n' and `right-n'.  Roughly speaking, left-n is the number of digits the
;; user wants to the left of the decimal point, right-n is the number of digits
;; to the right.  In ddd-mode, left-n is the number of d's to the left of the
;; decimal point in the "ddd.dddd" directive, and right-n is the number of d's
;; to the right.  The user can also imagine that G2 uses left-n and right-n
;; settings when it writes floats in implicit mode, though these typically are
;; not visible as "ddd.dddd" directives.

;; The maximum value of the sum of left-n and right-n is in distribution images
;; should be 15.  A larger sum will have an undefined effect.  This limit is due
;; to the maximum precision available for IEEE floats, namely
;;   (floor (log (expt 2 53) 10)).
;; There are 52 bits in the underlying representation plus 1 for the "hidden
;; bit" which normalized numbers always have (an implicit leftmost "1").

;; If G2 is able to identify them, other IEEE numeric entities are
;; written as follows:
;;   positive infinity         "+Inf"
;;   negative infinity   "-Inf"
;;   not-a-number        "NaN"
;;   denormalized number "NaN"
;; Note that some platforms signal a floating-point exception instead of
;; producing these entities.  Eventually we probably want consistent (or even
;; switchable) behavior on all platforms, but that is outside the scope of this
;; proposal.

;; If the lefthand digits in the written representation of the number would
;; exceed left-n, or if the number is between 1.0 and -1.0 and the righthand
;; zeros would exceed right-n, G2 will write the number in exponential notation.
;; Exponential notation has the following format:

;;   [-] <single lefthand digit> <decimal point> <right-n digits> e [-] <exponent>

;; For example, if left-n were 3 and right-n were 4, G2 would write the number
;; 1234.5678 as "1.2345e3".  Note that exponential notation and floating-point
;; data types are somewhat orthogonal, but not completely so.  G2 will write an
;; integer in exponential format if writing it otherwise would exceed left-n
;; digits, although G2 in ddd-mode will never write a float without a decimal
;; point.

;; Implicit mode can supress righthand trailing zeros if they are not
;; significant.  For example, with a left-n of 3 and a right-n of 3, G2 will
;; write 123.45 as "123.45" in implicit mode, whereas in ddd-mode G2 would write
;; this number as "123.450".  (For justification, see the 2.0 Reference Manual p
;; 222, "Formatting Arithmetic Values".)

;; In either mode, if the number has more significant digits than can be
;; accommodated, the number will be truncated and the last-written digit will be
;; rounded.  For example, in both modes, a left-n or 3 and a right-n of 3 will
;; cause 123.4567 to be printed as "123.457", and 123.00001 would be printed as
;; "123.000" (since the zeros to the right of the decimal point are
;; significant).

;; Lisp Interface for Writing Floats
;; ---------------------------------

;; write-floating-point-number        [function]
;;   number                                        fixnum or float
;;   left-n                                        fixnum
;;   right-n                                        fixnum
;;   precision                                  fixnum (ignored)
;;   suppress-trailing-zeros-p                        boolean (default is t)
;;   force-any-number-into-exponential-p        boolean (default is nil)
;;   force-small-number-to-exponential-p        boolean (default is t)
;;   fixed-exponent-subfield?                   positive fixnum or nil (default is nil)
;;   fixed-field?                                 positive fixnum or nil (default is nil)
;;   over-or-underflow-char                        character (default is #.%\#)

;; If <number> is not a float, it will be coerced to one.  If it is not a
;; number, a Lisp error will be signalled in development.

;; Due to the IEEE representation used for floats, no additional precision is
;; gained if the sum of <left-n> and <right-n> exceeds 15.  Callers may want to
;; supply a <left-n> and a right-n> of 15 apiece to ensure maximum precision.
;; We should make this limit clear to G2 end-users in the documentation.

;; <precision> is currently ignored.  It exists for backwards-compatibility with
;; the old-floating-point writer.

;; If <suppress-trailing-zeros-p> is non-nil, G2 will not write trailing zeros
;; unless they are significant.  This is useful in implementing implicit mode,
;; as described in the previous section.

;; If <force-any-number-into-exponential-p> is non-nil, <number> will always be
;; written in exponential notation, regardless of its magnitude.  This switch
;; currently (jh, 4/28/92) exists only for the benefit of CHARTS.

;; If <force-small-number-into-exponential-p> is non-nil, <number> will be
;; written in exponential notation, if its magnitude is less than 1.  The
;; off-position of this switch currently (jh, 4/28/92) exists only for the
;; benefit of CHARTS.

;; If <fixed-exponent-subfield?> is non-nil, it represents the exact size the
;; exponent field must have.  If positive, the exponent is padded on the left
;; with zeros and lacks a plus sign; if negative, it is padded with zeros after
;; the initial minus sign.  The minus sign (for a negative exponent) or the
;; initial zero (for a positive exponent) is considered part of the subfield
;; width.  This argument currently (jh, 4/28/92) exists only for the benefit of
;; CHARTS.

;; If <fixed-field?> is non-nil, it represents an upper limit on the number of
;; characters which may appear in the output.  If writing the float would exceed
;; this limit, write-floating-point-number will make these compromises, in
;; order:

;;   (1) Remove trailing zeros if not gone already, even if
;;       <suppress-trailing-zeros-p> is nil.
;;   (2) Remove digits from the right of the decimal place
;;   (3) Convert to exponential notation if not already exponential, even
;;       if <force-small-number-to-exponential-p> is nil.
;;   (4) Remove significant mantissa digits from exponential notation.
;;   (5) Remove the decimal point from exponential notation.
;;   (6) Fill the field with <over-or-underflow-char>.  (The user should never
;;       see this.)

;; Rounding will occur as if in response to a diminished <right-n> argument.
;; <over-or-underflow-char> should be a wide character in the ISO Latin1 subset
;; of Unicode (i.e., only 8 bits).  It defaults to the wide character
;; representing sharp-sign (#) to distinguish it from the asterisk (*) used to
;; display expired values.  The purpose of <fixed-field?> and
;; <over-or-underflow-char> is to aid in implementing an implicit mode for
;; occasions where the space for writing floats is limited, such as in graph
;; labels and dial markings.



(defvar null-char (code-char 0))

(defun gensym-sprintf-float
       (string-to-write-into precision number-to-write)
  (c-write-float-from-c string-to-write-into "%.*f" precision number-to-write))

(defun gensym-sprintf-float-or-exponential
       (string-to-write-into precision number-to-write)
  (c-write-float-from-c string-to-write-into "%.*g" precision number-to-write))

(defun gensym-sprintf-exponential
       (string-to-write-into precision number-to-write)
  (c-write-float-from-c string-to-write-into "%.*e" precision number-to-write)
  (loop with i = 0
        for this-char = (schar-if-appropriate string-to-write-into i)
        until (eql this-char null-char)
        with index-delta = 0
        with exponent-marker-encountered-p = nil
        with at-least-one-nonzero-exponent-digit-written-p = nil
        do (case this-char
             (#\+ (incff index-delta))
             (#\e (setq exponent-marker-encountered-p t)
                  (setf (schar-if-appropriate
                          string-to-write-into
                          (-f i index-delta))
                        this-char))
             (#\0 (cond
                    ((and exponent-marker-encountered-p
                          (not at-least-one-nonzero-exponent-digit-written-p))
                     (incff index-delta))
                    (t (setf (schar-if-appropriate
                               string-to-write-into
                               (-f i index-delta))
                             this-char))))
             (otherwise
              (when (and exponent-marker-encountered-p
                         (not at-least-one-nonzero-exponent-digit-written-p)
                         (digit-char-p this-char))
                (setq at-least-one-nonzero-exponent-digit-written-p t))
              (setf (schar-if-appropriate
                      string-to-write-into
                      (-f i index-delta))
                    this-char)))
           (incff i)
        finally (cond
                  (at-least-one-nonzero-exponent-digit-written-p
                   (setf (schar-if-appropriate
                           string-to-write-into
                           (-f i index-delta))
                         null-char))
                  (t (let ((index-of-zero-exponent (-f i index-delta)))
                       (setf (schar-if-appropriate
                               string-to-write-into
                               index-of-zero-exponent)
                             #\0)
                       (setf (schar-if-appropriate
                               string-to-write-into
                               (1+f index-of-zero-exponent))
                             null-char))))))

(defun gensym-sprintf-minimal-exponential
       (string-to-write-into number-to-write)
  (progn
    (c-write-float-from-c
      string-to-write-into
      "%.*e"
      0
      number-to-write)
    (loop with i = 0
          for this-char = (schar string-to-write-into i)
          until (char= this-char null-char)
          with index-delta = 0
          with exponent-marker-encountered-p = nil
          with at-least-one-nonzero-exponent-digit-written-p = nil
          do (case this-char
               (#\. (incff index-delta))
               (#\+ (incff index-delta))
               (#\e (setq exponent-marker-encountered-p t)
                    (setf (schar string-to-write-into (-f i index-delta))
                          this-char))
               (#\0 (cond
                      ((and exponent-marker-encountered-p
                            (not at-least-one-nonzero-exponent-digit-written-p))
                       (incff index-delta))
                      (t (setf (schar string-to-write-into (-f i index-delta))
                               this-char))))
               (otherwise
                (when (and exponent-marker-encountered-p
                           (not at-least-one-nonzero-exponent-digit-written-p)
                           (digit-char-p this-char))
                  (setq at-least-one-nonzero-exponent-digit-written-p t))
                (setf (schar string-to-write-into (-f i index-delta))
                      this-char)))
             (incff i)
          finally
            (cond
              (at-least-one-nonzero-exponent-digit-written-p
               (setf (schar string-to-write-into (-f i index-delta))
                     null-char))
              (t (let ((index-of-zero-exponent (-f i index-delta)))
                   (setf (schar string-to-write-into index-of-zero-exponent)
                         #\0)
                   (setf (schar string-to-write-into
                               (1+f index-of-zero-exponent))
                         null-char)))))))




(defun twrite-number-string-as-is (number-string)
  (loop for i from 0 below size-of-string-for-returning-floats
        for this-char = (schar-if-appropriate number-string i)
        until (char= null-char this-char)
        do
    (twrite-char this-char)))                ; Note: writes a CL char, not a wide char

(defun twrite-number-string-suppressing-fraction-entirely
       (number-string)
  (loop for i from 0 below size-of-string-for-returning-floats
        for this-char = (schar-if-appropriate number-string i)
        until (or (char= this-char null-char)
                  (char= this-char #\.))
        do
    (twrite-char this-char)))                ; Note: writes a CL char, not a wide char



;;; The function `count-of-number-string-trailing-zeros' is used to determine
;;; the number of zeros that are at the end of the string representation of a
;;; (float or exponent) number.  Note that the right end of the number, in the
;;; string, is indicated by a null-char.

(defun count-of-number-string-trailing-zeros
       (number-string use-exponential-notation-p)
  (let* ((index-of-final-trailing-digit
           (if use-exponential-notation-p
               (loop for i from 0 below size-of-string-for-returning-floats
                     until (char= (schar-if-appropriate number-string i) #\e)
                     finally
                       (return (1-f i)))
               (loop for i from 0 below size-of-string-for-returning-floats
                     until
                       (char= (schar-if-appropriate number-string i) null-char)
                     finally
                       (return (1-f i)))))
         (index-of-final-nonzero-trailing-digit
           (loop for i from index-of-final-trailing-digit
                     downto 0
                 for this-char = (schar-if-appropriate number-string i)
                 while (char= this-char #\0)
                 finally
                   (if (char= this-char #\.)
                       (return (1+f i))
                       (return i)))))
    (-f index-of-final-trailing-digit index-of-final-nonzero-trailing-digit)))

;; Note that this function should be updated if the implementation of the
;; function twrite-number-string-suppressing-trailing-zeros changes!  - cpm,
;; 1/9/96


(defun twrite-number-string-suppressing-trailing-zeros
       (number-string
        use-exponential-notation-p)
  (let* ((index-of-exponent-marker? nil)
         (index-of-final-trailing-digit
           (if use-exponential-notation-p
               (loop for i from 0 below size-of-string-for-returning-floats
                     until (char= (schar-if-appropriate number-string i) #\e)
                     finally
                       (setq index-of-exponent-marker? i)
                       (return (1-f i)))
               (loop for i from 0 below size-of-string-for-returning-floats
                     until
                       (char= (schar-if-appropriate number-string i) null-char)
                     finally
                       (return (1-f i)))))
         (index-of-final-nonzero-trailing-digit
           (loop for i from index-of-final-trailing-digit
                     downto 0
                 for this-char = (schar-if-appropriate number-string i)
                 while (char= this-char #\0)
                 finally
                   (if (char= this-char #\.)
                       (return (1+f i))
                       (return i)))))
    (loop with i = 0
          for this-char = (schar-if-appropriate number-string i)
          until (or (>=f i size-of-string-for-returning-floats)
                    (char= this-char null-char))
          do
      (tprinc this-char)
      (if (=f i index-of-final-nonzero-trailing-digit)
          (if index-of-exponent-marker?
              (setq i index-of-exponent-marker?)
              (loop-finish))
          (incff i)))))




;; The macro `writing-number-string-into-fixed-field' takes a series of
;; protected-let* specs called heuristics.  The last binding form in
;; each heuristic should be a text-string (whose length will be tested
;; against fixed-field-width) or nil (meaning that the next heuristic
;; should be tried).  The heuristics are examined in order, and the
;; first resulting text-string which fits inside a field of size
;; fixed-field-width is passed to twrite-general-string.  The remaining
;; heuristics are not evaluated.  Each heuristic is responsible for
;; reclaiming the objects it creates, including the resulting
;; text-string.  If none of the heuristics is successful, a sequence of
;; over-or-underflow-char is written that is exactly fixed-field-width
;; long.  This macro mainly exists to make the heuristics used in
;; writing fixed-width floats more readable.

(defmacro writing-number-string-into-fixed-field
          ((fixed-field-width over-or-underflow-char)
           &body protected-let*-specs)
  (let ((fixed-field-width-identifier
          (make-symbol "FIELD-WIDTH"))
        (over-or-underflow-char-identifier
          (make-symbol "OVER-OR-UNDERFLOW-CHAR")))
    `(let ((,fixed-field-width-identifier ,fixed-field-width))
       (with-flattened-protected-let-forms
         ,(loop for protected-let*-spec in (reverse protected-let*-specs)
                with expansion = nil
                for innermost-clause-p = t then nil
                do
            (let* ((last-protected-let*-binding
                     (car (last protected-let*-spec)))
                   (identifier-for-number-string-to-try
                     (first last-protected-let*-binding)))
              (setq expansion
                    `(protected-let* ,protected-let*-spec
                       (if (and ,identifier-for-number-string-to-try
                                (<=f (or (length-of-null-terminated-text-string
                                           ,identifier-for-number-string-to-try)
                                         (text-string-length
                                           ,identifier-for-number-string-to-try))
                                     ,fixed-field-width-identifier))
                           (twrite-general-string ,identifier-for-number-string-to-try)
                           ,(if innermost-clause-p
                                `(let ((,over-or-underflow-char-identifier
                                        ,over-or-underflow-char))
                                   (loop repeat ,fixed-field-width-identifier
                                         do
                                     (twrite-char
                                       ,over-or-underflow-char-identifier)))
                                expansion)))))
                finally (return expansion))))))

;; jh, 5/11/92.  Added with-flattened-protected-let-forms wrapper so that we
;; only enter a single unwind-protect scope instead of several.  This improves
;; efficiency in the face of the Chestnut implementation of unwind-protect,
;; which uses setjmp, a slow construct.

(defun-allowing-unwind twrite-number-string-in-fixed-field
                       (number
                         number-string
                         fixed-field-width
                         fraction-size
                         use-exponential-notation-p
                         force-small-number-into-exponential-p
                         suppress-trailing-zeros-p
                         over-or-underflow-char
                         zero-fraction-size-p)

  ;; Both Lispms and sprintf() round incorrectly when given a fractional size of
  ;; 0.  This is only important where a fractional size of 0 is allowed at all,
  ;; namely here in twrite-number-string-in-fixed-field.  Note that round is
  ;; called inside the with-temporary-gensym-float-creation context established
  ;; by write-floating-point-number.
  (when zero-fraction-size-p
    (setq number (coerce-to-gensym-float (round number))))

  ;; Enter a scoped macro which makes the heuristics easier to read.
  (writing-number-string-into-fixed-field
    (fixed-field-width over-or-underflow-char)

    ;; See if the unprocessed number-string fits in the field.
    ((number-string-before-heuristics
       (twith-output-to-text-string
         (if suppress-trailing-zeros-p
             (twrite-number-string-suppressing-trailing-zeros
               number-string
               use-exponential-notation-p)
             (twrite-number-string-as-is number-string)))
       (reclaim-text-string number-string-before-heuristics)))

    ;; If we haven't already dropped trailing zeros, do so and see if
    ;; the number-string will fit now.
    ((suppressed-trailing-zeros-unasked?
       (and (not suppress-trailing-zeros-p)
            (twith-output-to-text-string
              (twrite-number-string-suppressing-trailing-zeros
                number-string
                use-exponential-notation-p)))
       (reclaim-text-string suppressed-trailing-zeros-unasked?)))

    ;; Try to drop trailing non-zero digits from a non-exponential
    ;; representation.
    ((truncated-non-exponential?
       (and (not use-exponential-notation-p)
            (let* ((length-of-number-string
                     (or (length-of-null-terminated-string number-string) ; number-string is narrow
                         (text-string-length number-string-before-heuristics)))
                   (index-of-decimal-point
                     (loop for i from 0 below length-of-number-string
                           until (char=w (charw number-string-before-heuristics i)
                                         #.%\.)
                           finally (return i)))
                   (maximum-characters-that-can-be-truncated
                     (-f length-of-number-string index-of-decimal-point))
                   (number-of-decimal-places-before-truncation
                     (1-f maximum-characters-that-can-be-truncated))
                   (number-of-characters-to-truncate
                     (-f length-of-number-string fixed-field-width))
                   (index-of-final-nonzero-trailing-digit?
                     ;; Suppress any trailing zeros that may have resulted from
                     ;; truncating to the fixed field width.
                     (when suppress-trailing-zeros-p
                       (loop for i from (-f (1-f length-of-number-string)
                                            number-of-characters-to-truncate)
                             downto index-of-decimal-point
                             for this-char =
                               (charw number-string-before-heuristics i)
                             while (char=w this-char #.%\0)
                             finally
                               (if (char=w this-char #.%\.)
                                   (return (1+f i))
                                   (return i))))))
              (if (and suppress-trailing-zeros-p
                       index-of-final-nonzero-trailing-digit?)
                  (setq number-of-characters-to-truncate
                        (maxf number-of-characters-to-truncate
                              (-f (1-f length-of-number-string)
                                  index-of-final-nonzero-trailing-digit?))))

              (and (plusp number-of-characters-to-truncate)
                   (<=f number-of-characters-to-truncate
                        maximum-characters-that-can-be-truncated)
                   (twith-output-to-text-string
                     (cond
                       ((>=f number-of-characters-to-truncate
                             (1-f maximum-characters-that-can-be-truncated))
                        (gensym-sprintf-float
                          number-string
                          1
                          number)
                        (twrite-number-string-suppressing-fraction-entirely
                          number-string))
                       (t (gensym-sprintf-float
                            number-string
                            (-f number-of-decimal-places-before-truncation
                                number-of-characters-to-truncate)
                            number)
                          (twrite-number-string-as-is number-string)))))))
       (reclaim-text-string truncated-non-exponential?)))

    ;; If the number is small and small numbers may not be written
    ;; exponentially, write floating 0 with the correct number of
    ;; righthand digits.  If the field width is too small to allow at
    ;; least a "0.0", then write a sequence of underflow characters.
    ((magnitude-less-than-one-p
       (and (< number 1.0) (> number -1.0)))
     (too-small-number?
       (and magnitude-less-than-one-p
            (not use-exponential-notation-p)
            (not force-small-number-into-exponential-p)
            (if (>=f fixed-field-width 3)
                (twith-output-to-text-string
                  (twrite-general-string "0.0") ; #w"0.0" is a fwd. ref.!
                  (loop repeat (-f fixed-field-width
                                   (+f fraction-size 3))
                        do (twrite-char #.%\0)))
                (twith-output-to-text-string
                  (loop repeat fixed-field-width
                        do (twrite-char over-or-underflow-char)))))
       (reclaim-text-string too-small-number?)))

    ;; If permitted, try to write the number in exponential notation.
    ;; If it is too large to fit, a subsequent clause will try to
    ;; truncate righthand digits of the exponent.
    ((exponential-notation-unasked?
       (and (not use-exponential-notation-p)
            (if magnitude-less-than-one-p
                force-small-number-into-exponential-p
                t)
            (twith-output-to-text-string
              (gensym-sprintf-exponential
                number-string
                fraction-size
                number)
              (twrite-number-string-as-is number-string)))
       (reclaim-text-string exponential-notation-unasked?)))

    ;; Try to drop digits from the exponential representation.
    ((exponential-number-string
       (or exponential-notation-unasked?
           suppressed-trailing-zeros-unasked?
           number-string-before-heuristics))
     (length-of-exponential-number-string
       (or (length-of-null-terminated-text-string exponential-number-string)
           (text-string-length exponential-number-string)))
     (index-of-decimal-point
       (loop for i from 0 below length-of-exponential-number-string
             until (char=w (charw exponential-number-string i)  #.%\.)
             finally (return i)))
     (index-of-exponent-marker
       (loop for i from (1+f index-of-decimal-point)
                   below length-of-exponential-number-string
             until (char=w (charw exponential-number-string i) #.%\e)
             finally (return i)))
     (number-of-decimal-places-before-truncation
       (1-f (-f index-of-exponent-marker index-of-decimal-point)))
     (maximum-characters-that-can-be-truncated
       (-f index-of-exponent-marker index-of-decimal-point))
     (number-of-characters-to-truncate
       (-f length-of-exponential-number-string fixed-field-width))
     (truncated-exponential?
       (and (plusp number-of-characters-to-truncate)
            (<=f number-of-characters-to-truncate
                 maximum-characters-that-can-be-truncated)
            (twith-output-to-text-string
              (if (>=f number-of-characters-to-truncate
                       (1-f maximum-characters-that-can-be-truncated))
                  (gensym-sprintf-minimal-exponential
                    number-string
                    number)
                  (gensym-sprintf-exponential
                    number-string
                    (-f number-of-decimal-places-before-truncation
                        number-of-characters-to-truncate)
                    number))
              (twrite-number-string-as-is number-string)))
       (reclaim-text-string truncated-exponential?)))

    ;; If all else fails, write a sequence of over/underflow characters.
    ;; (This is done automatically by the
    ;; writing-number-string-into-fixed-field macro.)

    ))

;; Modified the above to suppress trailing zeros, when specified by the
;; argument, that result from truncating a non-exponential number.  - cpm,
;; 4/14/95



(defun-allowing-unwind pad-exponent-to-fixed-width
                       (fixed-exponent-subfield-width
                         &optional (plus-sign-char #\0))
  (protected-let
      ((string-for-storing-exponent
         (obtain-adjustable-gensym-string)
         (reclaim-gensym-string string-for-storing-exponent)))
    (setf (fill-pointer string-for-storing-exponent) 0)
    (loop for index from 0
                    below (-f size-of-string-for-returning-floats
                              1) ;since we peek one char ahead
          for this-char = (schar-if-appropriate
                            string-for-returning-floats
                            index)
          until (char= this-char null-char)
          do (when (char= this-char #\e)
               (let* ((next-index (1+f index))
                      (minus-exponent-p
                        (char= (schar-if-appropriate
                                 string-for-returning-floats
                                 next-index)
                               #\-))
                      (exponent-digits-start
                        (+f index
                            (if minus-exponent-p 2 1)))
                      (number-of-exponent-digits 0))

                 ;; Store the sign-less exponent digits.
                 (loop for from-index from exponent-digits-start
                                      below size-of-string-for-returning-floats
                       for exponent-char
                           = (schar-if-appropriate
                               string-for-returning-floats
                               from-index)
                       for to-index from 0
                       until (char= exponent-char null-char)
                       do (setf (char
                                  string-for-storing-exponent
                                  to-index)
                                exponent-char)
                       finally (setq number-of-exponent-digits to-index)
                               (setf (char
                                       string-for-storing-exponent
                                       to-index)
                                     null-char))

                 ;; Determine the number of padding zeroes we need.
                 (let ((number-of-zeros-for-exponent-pad
                         (-f fixed-exponent-subfield-width
                             number-of-exponent-digits
                             1 ;the sign is part of the fixed field
                             ))
                       (new-exponent-digits-start
                         (if minus-exponent-p
                             exponent-digits-start
                             (1+f exponent-digits-start))))

                   ;; Give up if there are too many exponent digits.
                   (unless (minusp number-of-zeros-for-exponent-pad)

                     ;; Supply a plus sign character if necessary.
                     ;; jh, 4/14/92.  The "plus sign" is currently a #\0 instead
                     ;; of #\+.  The chart labeler is currently the only client
                     ;; for pad-exponent-to-fixed-width, and Bill notes that a
                     ;; series of labels, all with a plus sign in the exponent,
                     ;; violate Gensym float-writing style.  Mixed signs on
                     ;; exponents are not yet an issue with charts, although
                     ;; they may be when logarithmic charts are implemented.
                     (unless minus-exponent-p
                       (setf (schar-if-appropriate
                               string-for-returning-floats
                               next-index)
                             plus-sign-char))

                     ;; Add the padding zeros.
                     (loop for pad-index
                               from 0 below number-of-zeros-for-exponent-pad
                           for to-index
                               from new-exponent-digits-start
                           do (setf (schar-if-appropriate
                                      string-for-returning-floats
                                      to-index)
                                    #\0))
        
                     ;; Copy the exponent digits into the output string.
                     (loop for to-index
                               from (+f new-exponent-digits-start
                                        number-of-zeros-for-exponent-pad)
                               below size-of-string-for-returning-floats
                           for from-index from 0
                           for exponent-char
                               = (char
                                   string-for-storing-exponent
                                   from-index)
                           until (char= exponent-char null-char)
                           do (setf (schar-if-appropriate
                                      string-for-returning-floats
                                      to-index)
                                    exponent-char)
                           finally (setf (schar-if-appropriate
                                           string-for-returning-floats
                                           to-index)
                                         null-char)))))

               ;; Exit the loop after exponent marker no matter what.
               (loop-finish)))))


;; jh, 4/10/92.  The rationale for
;; maximum-significant-decimal-digits-in-gensym-float is that distribution
;; platforms support no more than 15 digits of precision, that is, (floor (log
;; (expt 2 53) 10)).  As well, we want at least one righthand digit under normal
;; circumstances (i.e., where fixed-field-width?  is nil).  We should
;; investigate whether this limit is the same for VMS G-floats.

(defvar maximum-significant-decimal-digits-in-gensym-float 15)

;;; Note that the idea behind accurate float printing is to print with enough
;;; precision that the same number will result upon being read back in;
;;; this requirement would usually result in many extra digits being printed
;;; by formatted printing. because it is necessary to specify the number of
;;; digits that are needed in the worst case, which is something like 17 or 18;
;;; the only "unnecessary" digits that the old code was able to omit were
;;; trailing zeros.

(defvar write-floats-accurately-p nil)

(defun write-floating-point-number
    (number &optional (integral-size 5) (fraction-size nil) (precision 6)
     (suppress-trailing-zeros-p t)
     (force-any-number-into-exponential-p nil)
     (force-small-number-into-exponential-p t)
     fixed-exponent-subfield-width?
     fixed-field-width?
     (over-or-underflow-char #.%\#)
     &aux supplied-fraction-size-p zero-fraction-size-p)
  (declare (ignore precision))

  (with-temporary-gensym-float-creation
      write-floating-point-number

    ;; Make sure we really have a float.
    (setq number (if (managed-float-p-function number)
                     (managed-float-value-function number)
                     (coerce-to-gensym-float number)))

    ;; Write anomalous IEEE entities in a standard way.
    (cond
      ((nanp number)
       (twrite-general-string "NaN")
       (return-from write-floating-point-number))
      ((positive-infinity-p number)
       (twrite-general-string "+Inf")
       (return-from write-floating-point-number))
      ((negative-infinity-p number)
       (twrite-general-string "-Inf")
       (return-from write-floating-point-number)))

    (setq supplied-fraction-size-p (not (null fraction-size)))
    (unless fraction-size
      (setq fraction-size 3))
    (setq zero-fraction-size-p
          (zerop fraction-size))
    (setq integral-size
          (minf maximum-significant-decimal-digits-in-gensym-float
                integral-size))
    (setq fraction-size
          (maxf (minf maximum-significant-decimal-digits-in-gensym-float
                      fraction-size)
                1))

    (let* ((use-exponential-notation-p
            (or force-any-number-into-exponential-p
                (cond
                  ((=e number 0.0d0) nil)
                  ((>=e number 0.0d0)
                   (or (>=e number (svref new-decade-table integral-size))
                       (if force-small-number-into-exponential-p
                           (<e number (svref new-fractional-decade-table
                                             fraction-size))
                           nil)))
                  (t (let ((absolute-value-of-number (-e number)))
                       (or (>=e absolute-value-of-number
                                (svref new-decade-table integral-size))
                           (if force-small-number-into-exponential-p
                               (<e absolute-value-of-number
                                   (svref new-fractional-decade-table
                                          fraction-size))
                               nil)))))))
           (use-exact-float-p
            (current-system-case
             (ab (and write-floats-accurately-p
                      (null supplied-fraction-size-p)
                      (null force-any-number-into-exponential-p)))
             (t nil))))
      ;; Use C sprintf to write number into string-for-returning-floats
      (cond (use-exact-float-p
             (current-system-case
              (ab (c-write-exact-float-from-c
                   string-for-returning-floats
                   number))))
            (use-exponential-notation-p
             (gensym-sprintf-exponential
              string-for-returning-floats
              fraction-size
              number))
            (t
             (gensym-sprintf-float
              string-for-returning-floats
              fraction-size
              number)))

      ;; Enforce a fixed exponent field if appropriate.
      (when (and use-exponential-notation-p
                 fixed-exponent-subfield-width?)
        (pad-exponent-to-fixed-width fixed-exponent-subfield-width?))

      ;; Dispatch on the various types of output format.
      (cond
        ((or use-exact-float-p
             (and (null suppress-trailing-zeros-p)
                  (null fixed-field-width?)))
         (twrite-number-string-as-is
          string-for-returning-floats))
        ((null fixed-field-width?)
         (twrite-number-string-suppressing-trailing-zeros
          string-for-returning-floats
          use-exponential-notation-p))
        (t (twrite-number-string-in-fixed-field
            number
            string-for-returning-floats
            fixed-field-width?
            fraction-size
            use-exponential-notation-p
            force-small-number-into-exponential-p
            suppress-trailing-zeros-p
            over-or-underflow-char
            zero-fraction-size-p))))))

;; jh, 1/24/92.  Changed the maximum precision in write-floating-point-number to
;; be 15 instead of 13 on Chestnut platforms.  This value is (floor (log (expt 2
;; 52) 10)), where 52 is the number of bits in an IEEE standard double float
;; that represent the fractional part of the float.

;; jh, 2/19/92.  Changed the novel arguments to write-floating-point-number
;; (supress-trailing-zeros-p and the like) to be required.  These will now be
;; defaulted in write-floating-point-number, so that callers can have the
;; advantage of specifying these novel arguments and we can still back out of
;; new-floating-point-writer if it starts to misbehave.



;;; The function `write-floating-point-number-c-format' is similar to
;;; write-floating-point-number, except that it allows more direct access to the
;;; printf control of "C".

;;; The printf-like features used are: precision; formats of float (f), exponent
;;; (e), and best (g); and minimum-width (optional).  Note that the float format
;;; argument is specified by the symbols float, exponent, or best.

;;; A difference from the C printf is the addition of the suppress trailing
;;; zeros argument.  Note that this is already done by "C" in the "g" (best)
;;; format.

;;; GENSYMCID-1108: Minor bug in class definition
(defvar default-float-to-text-format nil)

(defun write-floating-point-number-simple-c-format
    (number &optional
     (precision
      (current-system-case
        (ab (float-to-text-default-precision-from-system-table))
        (t 3)))
     (output-format
      (current-system-case
        (ab (or default-float-to-text-format
                (float-to-text-default-format-from-system-table)))
        (t 'default)))
     (minimum-width? nil)
     (suppress-trailing-zeros-p t))

  ;; GENSYMCID-939: Difference in format of freeform-table
  ;; Now we introduce a new float-to-text format called `default', it precisely
  ;; recovered the legacy format used in G2 8.x, which is quite smart.

  (when (eq output-format 'default)
    (write-floating-point-number number)
    (return-from write-floating-point-number-simple-c-format))

  (with-temporary-gensym-float-creation
    write-floating-point-number

    ;; Make sure we really have a float.
    (setq number (if (managed-float-p-function number)
                     (managed-float-value-function number)
                     (coerce-to-gensym-float number)))

    ;; Validate the width, if necessary.
    (when minimum-width?
      (setq minimum-width?
            (minf (maxf minimum-width? 1)
                  maximum-length-for-user-gensym-strings)))

    ;; Write anomalous IEEE entities in a standard way.
    (cond
      ((nanp number)
       (when minimum-width?
         (twrite-spaces-if-necessary minimum-width? 3))        ; 3 for NaN
       (twrite-general-string "NaN")
       (return-from write-floating-point-number-simple-c-format))
      ((positive-infinity-p number)
       (when minimum-width?
         (twrite-spaces-if-necessary minimum-width? 4))        ; 4 for +Inf
       (twrite-general-string "+Inf")
       (return-from write-floating-point-number-simple-c-format))
      ((negative-infinity-p number)
       (when minimum-width?
         (twrite-spaces-if-necessary minimum-width? 4))        ;; 4 for -Inf
       (twrite-general-string "-Inf")
       (return-from write-floating-point-number-simple-c-format)))

    ;; 0 >= Precision >= 16.  Note G2 has max of 15 to 16 digit precision.
    (setq precision (maxf (minf 16 precision) 0))

    ;; Use C sprintf to write number into string.
    ;; for force-zero option when integer length is greater than 29 bits, we append a .0 in printing
    (case output-format
      (float
       (gensym-sprintf-float
         string-for-returning-floats precision number))
      (exponent
       (gensym-sprintf-exponential
         string-for-returning-floats precision number))
      (best
       (gensym-sprintf-float-or-exponential
         string-for-returning-floats precision number))
      (force-zero
       (current-system-case
         (ab (c-write-exact-float-from-c
               string-for-returning-floats number))))
      (t
       #+development
       (cerror
         "continue"
         "Unknown float format.  Should be one of float, exponent,best or force-zero.")
       (when minimum-width?
         (twrite-spaces-if-necessary minimum-width? 4))        ; 4 for ####
       (twrite-general-string "####")
       (return-from write-floating-point-number-simple-c-format)))

    ;; Output the value
    ;; for force-zero option, suppress trailing zeroes in case floats were passed. if integers were passed
    ;; for printing for this option, do not eat up trailing zeroes.
    (cond
      ((and suppress-trailing-zeros-p
            (neq output-format 'best)
            (neq output-format 'force-zero)
            ;; If the output-format is float and the precision is 0
            ;; there are no digits to the right of the decimal point,
            ;; in fact there is no decimal point, so there are no
            ;; trailing zeros to suppress.  And we don't want it to
            ;; eat into the integer part of a non-zero float that
            ;; ends in one or more zeros.  E.g. we want
            ;; g2-float-to-text(42120.0, 1, 0, the symbol float, true)
            ;; to return "42120" and not "4212". - jpg 11/30/00
            (or (eq output-format 'exponent) (/=f precision 0)))
       ;; Note that the "g" (best) format already removes trailing zeros and is
       ;; not handled in this case.  (It would be difficult to handle here
       ;; because we don't know if the value is being converted to an exponent
       ;; and, therefore, if the use-exponential-notation-p of the following
       ;; function should be t or nil.)  - cpm, 1/3/96

       ;; Pad with spaces, when necessary, accounting for trailing zeros that
       ;; will be removed.
       (when minimum-width?
         (let ((length-of-string-for-returning-floats?
                 (length-of-null-terminated-string
                   string-for-returning-floats))
               (number-of-zeros-to-remove
                 (count-of-number-string-trailing-zeros
                   string-for-returning-floats (eq output-format 'exponent))))
           (when length-of-string-for-returning-floats?
             (twrite-spaces-if-necessary
               minimum-width?
               (-f length-of-string-for-returning-floats?
                   number-of-zeros-to-remove)))))
       (twrite-number-string-suppressing-trailing-zeros
         string-for-returning-floats (eq output-format 'exponent)))
      (t
       ;; Pad with spaces, when necessary.
       (when minimum-width?
         (let ((length-of-string-for-returning-floats?
                 (length-of-null-terminated-string
                   string-for-returning-floats)))
           (when length-of-string-for-returning-floats?        ; NULL char found
             (twrite-spaces-if-necessary
               minimum-width? length-of-string-for-returning-floats?))))
       (twrite-number-string-as-is string-for-returning-floats)))))

;; Note that this function is currently used for a new system-procedure in G2
;; 4.0r2 that formats a float (i.e., converts from float to text, as specified).
;;
;; We should consider merging this function and write-floating-point-number.
;;
;; We should consider writing a second function and system-procedure that uses
;; more of the formatting capabilities (left-justify, minimum width, etc.) of
;; printf.  - cpm, 1/2/96

;; Precision parameter turned to optional. From now on default values for 
;; precision and output-format parameters will be taken from Miscellaneous
;; parameters system table. (abto 09/19/08)



;; jh, 4/23/92.  Removing the #+development compiler switching from test-fpw,
;; test-suite-for-write-floating-point-number, and validate-fpw.  This is so we
;; can test the new floating-point writer in distribution images, where the code
;; diverges significantly from development.  Dropping this development code into
;; the distribution image is a special-case solution to the general problem of
;; including development code in distribution images, and considerations of
;; space prevent us from doing this wholesale.  The true solution is to get a
;; tool from Chestnut which can reliably emit #ifdef'd C code directly into the
;; translated file.  The currently existing Chestnut tools, trun:c-lines and
;; trun:ifdef, do not work at top level.

#+development
(defun test-fpw (float left-n right-n
                 &optional suppress-trailing-zeros-p
                           force-any-number-into-exponential-p
                           force-small-number-into-exponential-p
                           fixed-exponent-subfield-width?
                           fixed-field-width?)
  (twith-output-to-text-string
    (write-floating-point-number
      float
      left-n
      right-n
      nil
      suppress-trailing-zeros-p
      force-any-number-into-exponential-p
      force-small-number-into-exponential-p
      fixed-exponent-subfield-width?
      fixed-field-width?
      #.%\#)))

#+development
(defparameter test-suite-for-write-floating-point-number
  (optimize-constant
  '(
    ;; vanilla test of trailing zero suppression
    ;;       suppress-trailing-zeros-p
    ;;                  V
    ;;                  V
    ;;                  V
    ((test-fpw 1.0 3 3 nil) "1.000")
    ((test-fpw 1.0 3 3 t)   "1.0")
    ((test-fpw 1.0 4 3 nil) "1.000")
    ((test-fpw 1.0 4 3 t)   "1.0")

    ;; test elimination of leading zero sprintf() puts in exponent
    ;;           force-small-number-into-exponential-p
    ;;                           V
    ;;                           V
    ;;                           V
    ((test-fpw 1.0e20  3 3 t nil t) "1.0e20")
    ((test-fpw 1.0e-20 3 3 t nil t) "1.0e-20")
    ((test-fpw 1.0e20  4 3 t nil t) "1.0e20")
    ((test-fpw 1.0e-20 4 3 t nil t) "1.0e-20")

    ;; vanilla test of forcing all numbers to exponential
    ;;       force-any-number-into-exponential-p
    ;;                       V
    ;;                       V
    ;;                       V
    ((test-fpw 1.0 3 3  nil nil nil nil) "1.000")
    ((test-fpw 1.0 3 3  t   t   nil nil) "1.0e0")
    ((test-fpw 10.0 3 3 nil nil nil nil) "10.000")
    ((test-fpw 10.0 3 3 t   t   nil nil) "1.0e1")

    ;; large numbers normally go into exponential
    ;;             suppress-trailing-zeros-p
    ;;                       V
    ;;                       V
    ;;                       V
    ((test-fpw 1234.5    3 3 nil) "1.234e3")
    ((test-fpw 100000.0  3 3 nil) "1.000e5")
    ((test-fpw 1000000.0 3 3 t)   "1.0e6")
    ((test-fpw 1230000.0 3 3 t)   "1.23e6")
    ((test-fpw 12345.6   4 3 nil) "1.235e4")
    ((test-fpw 100000.0  4 3 nil) "1.000e5")
    ((test-fpw 1000000.0 4 3 t)   "1.0e6")
    ((test-fpw 1230000.0 4 3 t)   "1.23e6")

    ;; vanilla test of mandatory exponential format for small numbers
    ;;              force-small-number-into-exponential-p
    ;;                            V
    ;;                            V
    ;;                            V
    ((test-fpw .0001 3 3 nil nil nil) "0.000")
    ((test-fpw .0001 3 3 t   nil nil) "0.0")
    ((test-fpw .0001 3 3 t   nil t)   "1.0e-4")
    ((test-fpw .0001 3 3 nil nil t)   "1.000e-4")
    ((test-fpw .0001 4 3 nil nil nil) "0.000")
    ((test-fpw .0001 4 3 t   nil nil) "0.0")
    ((test-fpw .0001 4 3 t   nil t)   "1.0e-4")
    ((test-fpw .0001 4 3 nil nil t)   "1.000e-4")

    ;; vanilla test of fixed total field width
    ;;                                  fixed-field-width?
    ;;                                        V
    ;;                                        V
    ;;                                        V
    ((test-fpw 12345.6789 3 3 nil nil nil nil 6) "1.23e4")
    ((test-fpw 12345.6789 4 3 nil nil nil nil 6) "1.23e4")
    ((test-fpw 1.23d-8    3 3 nil nil t   nil 6) "1.2e-8")
    ((test-fpw 1.23d-8    4 3 nil nil t   nil 6) "1.2e-8")
    ((test-fpw 1.23d8     3 3 nil nil t   nil 5) "1.2e8")
    ((test-fpw 1.23d8     4 3 nil nil t   nil 5) "1.2e8")

    ;; tests correct rounding in fixed field - large numbers
    ;;                                  fixed-field-width?
    ;;                                        V
    ;;                                        V
    ;;                                        V
    ((test-fpw 98765.4321 3 3 nil nil nil nil 6) "9.88e4")
    ((test-fpw 98765.4321 3 3 nil nil nil nil 5) "9.9e4")
    ((test-fpw 98765.4321 3 3 nil nil nil nil 4) "1e5")
    ((test-fpw 98765.4321 3 3 nil nil nil nil 3) "1e5")
    ((test-fpw 98765.4321 3 3 nil nil nil nil 2) "##")
    ((test-fpw 98765.4321 4 3 nil nil nil nil 6) "9.88e4")
    ((test-fpw 98765.4321 4 3 nil nil nil nil 5) "9.9e4")
    ((test-fpw 98765.4321 4 3 nil nil nil nil 4) "1e5")
    ((test-fpw 98765.4321 4 3 nil nil nil nil 3) "1e5")
    ((test-fpw 98765.4321 4 3 nil nil nil nil 2) "##")

    ;; tests correct rounding in fixed field - small numbers
    ;;                                   fixed-field-width?
    ;;                                         V
    ;;                                         V
    ;;                                         V
    ((test-fpw 0.00098765  3 3 nil nil nil nil 6) "0.001")
    ((test-fpw 0.000098765 3 3 nil nil nil nil 6) "0.000")
    ((test-fpw 0.000098765 3 3 t   nil nil nil 6) "0.0")
    ((test-fpw 0.000098765 3 3 nil nil t   nil 6) "9.9e-5")
    ((test-fpw 0.000098765 3 3 nil nil t   nil 5) "1e-4")
    ((test-fpw 0.000098765 3 3 nil nil t   nil 4) "1e-4")
    ((test-fpw 0.000098765 3 3 nil nil t   nil 3) "###")
    ((test-fpw 0.00098765  4 3 nil nil nil nil 6) "0.001")
    ((test-fpw 0.000098765 4 3 nil nil nil nil 6) "0.000")
    ((test-fpw 0.000098765 4 3 t   nil nil nil 6) "0.0")
    ((test-fpw 0.000098765 4 3 nil nil t   nil 6) "9.9e-5")
    ((test-fpw 0.000098765 4 3 nil nil t   nil 5) "1e-4")
    ((test-fpw 0.000098765 4 3 nil nil t   nil 4) "1e-4")
    ((test-fpw 0.000098765 4 3 nil nil t   nil 3) "###")

    ;; tests elimination of leading zero in fixed-field
    ;;                             fixed-field-width?
    ;;                                   V
    ;;                                   V
    ;;                                   V
    ((test-fpw 1.0e20  3 3 nil nil t nil 4) "1e20")
    ((test-fpw 1.0e-20 3 3 nil nil t nil 5) "1e-20")
    ((test-fpw 1.0e20  4 3 nil nil t nil 4) "1e20")
    ((test-fpw 1.0e-20 4 3 nil nil t nil 5) "1e-20")

    ;; force-any-number-into-exponential-p with fixed-field
    ;;                         fixed-field-width?
    ;;                               V
    ;;                               V
    ;;                               V
    ((test-fpw 1.0 3 3 nil t nil nil 3) "1e0")
    ((test-fpw 1.0 4 3 nil t nil nil 3) "1e0")

    ;; writing zero in fixed-field mode
    ;;                           fixed-field-width?
    ;;                                 V
    ;;                                 V
    ;;                                 V
    ((test-fpw 0.0 3 3 nil nil nil nil 3) "0.0")
    ((test-fpw 0.0 3 3 nil t   nil nil 3) "0e1")
    ((test-fpw 0.0 4 3 nil nil nil nil 3) "0.0")
    ((test-fpw 0.0 4 3 nil t   nil nil 3) "0e1")

    ;; fenceposting in decade table
    ;;          integer-size
    ;;                  V
    ;;                  V
    ;;                  V
    ((test-fpw 9.99d14 14 1 nil nil t nil 18) "1.0e15")
    ((test-fpw 9.99d14 15 1 nil nil t nil 18) "999000000000000.0")
    ((test-fpw 9.99d14 16 1 nil nil t nil 18) "999000000000000.0")
    ((test-fpw 9.99d14 17 1 nil nil t nil 18) "999000000000000.0")

    ;; vanilla test of fixed exponent subfield width
    ;;               fixed-exponent-subfield-width?
    ;;                              V
    ;;                              V
    ;;                              V
    ((test-fpw 1.23d20  3 3 t nil t 5) "1.23e00020")
    ((test-fpw 1.23d-20 3 3 t nil t 5) "1.23e-0020")
    ((test-fpw 1.23d20  4 3 t nil t 5) "1.23e00020")
    ((test-fpw 1.23d-20 4 3 t nil t 5) "1.23e-0020")
    ((test-fpw 1.23d8   3 3 t nil t 2) "1.23e08")
    ((test-fpw 1.23d-8  3 3 t nil t 2) "1.23e-8")
    ((test-fpw 1.23d8   4 3 t nil t 2) "1.23e08")
    ((test-fpw 1.23d-8  4 3 t nil t 2) "1.23e-8")

    ;; interaction between fixed field and fixed exponent subfield
    ;;                              fixed-exponent-subfield-width?
    ;;                              V
    ;;                              V   fixed-field-width?
    ;;                              V   V
    ;;                              V   V
    ;;                              V   V
    ((test-fpw 1.23d8   3 3 t nil t 1   6) "1.23e8")
    ((test-fpw 1.23d-8  3 3 t nil t 1   6) "1.2e-8")
    ((test-fpw 1.23d8   4 3 t nil t 1   6) "1.23e8")
    ((test-fpw 1.23d-8  4 3 t nil t 1   6) "1.2e-8")


    ;; writing a float as an integer in a fixed field when it fits
    ;;                   fraction
    ;;                      V         fixed-field-width?
    ;;                      V               V
    ;;                      V               V
    ;;                      V               V
    ((test-fpw 1234.56789 6 0 t nil nil nil 6) "1234.6")
    ((test-fpw 12345.6789 6 0 t nil nil nil 6) "12346")  ;note rounding
    ((test-fpw 123456.789 6 0 t nil nil nil 6) "123457") ;note rounding
    ((test-fpw 1234567.89 6 0 t nil nil nil 6) "1.2e6")  ;0 maximizes with 1 when exponential

    ;; boundaries of significance for fixed field and 0 fraction size
    ;;                            fraction
    ;;                               V        fixed-field-width?
    ;;                               V               V
    ;;                               V               V
    ;;                               V               V
    ((test-fpw 10000000000123.0d0 14 0 t nil nil nil 14) "10000000000123")
    ((test-fpw 10000000001234.0d0 14 0 t nil nil nil 14) "10000000001234")
    ((test-fpw 10000000012345.0d0 14 0 t nil nil nil 14) "10000000012345")
    ((test-fpw 10000000123456.0d0 14 0 t nil nil nil 14) "10000000123456")
    ((test-fpw 10000001234567.0d0 14 0 t nil nil nil 14) "10000001234567")

    ;; truncating non-exponential notation
    ;;                                   fixed-field-width?
    ;;                                         V
    ;;                                         V
    ;;                                         V
    ((test-fpw  0.67891234 3 3 nil nil nil nil 3) "0.7")
    ((test-fpw  1.67891234 3 3 nil nil nil nil 3) "1.7")
    ((test-fpw  0.67891234 3 3 nil nil nil nil 4) "0.68")
    ((test-fpw  1.67891234 3 3 nil nil nil nil 4) "1.68")
    ((test-fpw  16.7891234 3 3 nil nil nil nil 4) "16.8")
    ((test-fpw -0.67891234 3 3 nil nil nil nil 4) "-0.7")
    ((test-fpw -1.67891234 3 3 nil nil nil nil 4) "-1.7")
    ((test-fpw -0.67891234 3 3 nil nil nil nil 5) "-0.68")
    ((test-fpw -1.67891234 3 3 nil nil nil nil 5) "-1.68")
    ((test-fpw -16.7891234 3 3 nil nil nil nil 5) "-16.8")
    )))


#+development
(declare-funcallable-symbol validate-fpw) ;so we can call this via a system procedure
#+development
(defun validate-fpw ()
  (loop for (form desired-result)
            in test-suite-for-write-floating-point-number
        with validated-p = t
        do
    (let ((result (apply #'test-fpw (cdr form))))
     (unless (equal result desired-result)
        (setq validated-p nil)
        (format t "~&~a should have been ~a, not ~a~%"
                form
                desired-result
                result))
     (when (text-string-p result)
       (reclaim-text-string result))) ;so we can use with-memory-checking
     finally (return validated-p)))



;;; `Supply-ordinal-suffix' returns one of the following ordinal suffix strings:
;;;
;;;   "st", "d", "th"
;;;
;;; Note that this follows the preference of the Chicago Manual of Style.  Per
;;; the CMS:
;;;
;;;    the preferred figure form of the ordinals _second_ and _third_ is with
;;;    _d_ alone not _nd_ and _rd_:
;;;
;;;       The 222d sand 123d days of the strike were marked by
;;;       renewed violence.
;;;
;;; Which one depends on the value of count, which must be a non-negative
;;; fixnum.  The value returned is a quoted program constant that must never be
;;; modified by its receiver.

(defun-simple supply-ordinal-suffix (count)
  (declare (eliminate-for-gsi))
  (case (mod count 100)
    ((11 12 13) '"th")
    (t (case (mod count 10)
         (1 '"st")
         (2 '"d")                        ; not nd
         (3 '"d")                        ; not rd
         (otherwise '"th")))))

;; Ultimately, the rd/nd vs. d rule may want to be decided by the user, i.e., in
;; parameterized.  Do along with the full-scale internationalization project.

;; Note that the CMS also prefers that the ordinals 1 through 99 be spelled out,
;; as opposed to using figures.  That's the next thing to do.  When we it, we
;; should take note of their footnote, which says that their standard conflicts
;; with the practice of many newspapers and scholarly publications, which only
;; spell out 1 through 9.  Also, decide what to do with zero and other non-whole
;; number, which they don't deal with.  Also, we're on edition 13; check for
;; any revisions.  (MHD 5/18/94)





;;; `Twrite-unicode-character-code' writes character-code, a 16-bit unsigned
;;; integer, as @uHHHH, where HHHH is the 4-digit hexadecimal representation
;;; of character-code.  [This is planned as a new number token syntax in the
;;; G2 tokenizer.]

#+unused
(defun twrite-unicode-character-code (character-code)
  (twrite-string "@u")
  (twrite-string
    (if (<=f character-code #xf)
        "000"
        (if (<=f character-code #xff)
            "00"
            (if (<=f character-code #xfff)
                "0"
                ""))))
  (twrite-positive-fixnum-in-radix character-code 16))

;; Move this elsewhere!  Decide when/how to use it!  The idea is that characters
;; outside of a core set should be written in the @uHHHH format, and core letters
;; literally.





;;;; Wide-string Reader Macro

;;; N.B. The function that implements the reader for wide-string constants is
;;;      NOT defined until this file, so don't use #w until after this module
;;;      is loaded.  The function that implements the reader for wide characters
;;;      is defined in CHARACTERS2, so wide character constants can be used once
;;;      that module is loaded.

(eval-when
    #+chestnut-trans (:compile-toplevel)
    #-chestnut-trans (:compile-toplevel :load-toplevel :execute)
  (set-dispatch-macro-character #\# #\w 'read-wide-string))





;;;; Setting Up the Lucid Lisp Readtable


;;; Lucid (one assumes for safety and sanity purposes) conses up a fresh
;;; readtable upon entry to the Debugger or Breakpoint read-eval-print
;;; loops.  This implies that our #w and #n macros would not be present.
;;; Since we don't tend to use copy-readtable very much, we can hack it
;;; that it will always make readtables that have our read macros.  Try
;;; to patch C (or ADA or Cobol) on the fly this easily.

#+(and lucid (not chestnut-trans))
(progn

(defvar *real-copy-readtable* nil)

(defun special-copy-readtable (&rest args)
  (let* ((rt (apply *real-copy-readtable* args))
         (*readtable* rt))
    (set-dispatch-macro-character #\# #\u 'read-wide-character)
    (set-dispatch-macro-character #\# #\w 'read-wide-string)
    rt))

(defun clobber-copy-readtable ()
  (unless *real-copy-readtable*
    (setf *real-copy-readtable* #'lisp:copy-readtable))
  (setf (symbol-function 'lisp:copy-readtable)
                  #'special-copy-readtable))

(clobber-copy-readtable)

)

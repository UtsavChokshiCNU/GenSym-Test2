;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CHARACTERS2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David and Ong, Peng Tsin





;;;; Gensym <-> Unicode Han Mapping


;;; `Han-interpretation-mode' is to be bound around calls to facilities that map
;;; from Unicode (featuring unified Han characters) to systems that contain
;;; Chinese, Japanese, or Korean National Versions of overlapping subsets of the
;;; unified Han.  This defaults to JAPANESE.  Currently defined legal values are
;;; JAPANESE and KOREAN.  CHINESE-TRADITIONAL and CHINESE (= CHINESE-SIMPLIFIED)
;;; may soon be added.

(defvar han-interpretation-mode 'japanese)

(defun unicode-han-character-p (unicode)
  ;; IMPLEMENT!
  unicode
  )

(defun-simple map-unicode-to-gensym-han-character-code (unicode)
  (cond
    ((eq han-interpretation-mode 'korean)
     (or (map-unicode-to-gensym-KS-C-5601 unicode)
	 (map-unicode-to-gensym-JIS-X-0208 unicode)))
    (t ; includes: (eq han-interpretation-mode 'japanese)
     (or (map-unicode-to-gensym-JIS-X-0208 unicode)
	 (map-unicode-to-gensym-KS-C-5601 unicode)))))

(defun-simple map-gensym-han-character-code-to-unicode (gensym-character-code)
  (cond
    ((eq han-interpretation-mode 'korean)
     (or (if (legal-gensym-ksc-character-code-p gensym-character-code)
	     (map-gensym-KS-C-5601-to-unicode gensym-character-code))
	 (if (legal-gensym-jis-character-code-p gensym-character-code)
	     (map-JIS-X-0208-to-unicode gensym-character-code))))
    (t ; includes: (eq han-interpretation-mode 'japanese)
     (or (if (legal-gensym-jis-character-code-p gensym-character-code)
	     (map-JIS-X-0208-to-unicode gensym-character-code))
	 (if (legal-gensym-ksc-character-code-p gensym-character-code)
	     (map-gensym-KS-C-5601-to-unicode gensym-character-code))))))









(defvar gensym-code-for-linebreak	; U+2028 = linebreak (@L)
  (map-unicode-1-1-character-to-gensym-character-code (unicode-line-separator)))

(defvar gensym-char-or-code-for-linebreak #\L)
(defvar gensym-esc-for-linebreak? #\@)

(defvar gensym-code-for-paragraph-break	; U+2029 = paragraph-break (@P)
  (map-unicode-1-1-character-to-gensym-character-code (unicode-paragraph-separator)))
(defvar gensym-char-or-code-for-paragraph-break #\P)
(defvar gensym-esc-for-paragraph-break? #\@)

;; NOTE: it turns out that the MILL kb in 4.0 (and presumably earlier) actually
;; does contain a @P sequence, in the string "@PAll rights reserved".  So it's
;; not true that this never got out of the building, as has previously at times
;; been claimed or believed. (MHD 2/21/96)

(defvar gensym-code-for-capital-ligature-oe ; U+0152 = OE (~W)
  (map-unicode-1-1-character-to-gensym-character-code (unicode-capital-ligature-oe)))
(defvar gensym-char-or-code-for-capital-ligature-oe #\W)
(defvar gensym-esc-for-capital-ligature-oe? #\~)

(defvar gensym-code-for-small-ligature-oe ; U+0153 = oe (~w)
  (map-unicode-1-1-character-to-gensym-character-code (unicode-small-ligature-oe)))
(defvar gensym-char-or-code-for-small-ligature-oe #\w)
(defvar gensym-esc-for-small-ligature-oe? #\~)

(defvar gensym-code-for-bullet ; U+2022 = bullet (~*)
  (map-unicode-1-1-character-to-gensym-character-code (unicode-bullet)))
(defvar gensym-char-or-code-for-bullet #\*)
(defvar gensym-esc-for-bullet? #\~)

(defvar gensym-code-for-small-letter-f-with-hook ; U+0192 = florin (~&)
  (map-unicode-1-1-character-to-gensym-character-code
    (unicode-latin-small-letter-f-with-hook)))
(defvar gensym-char-or-code-for-small-letter-f-with-hook #\&)
(defvar gensym-esc-for-small-letter-f-with-hook? #\~)

(defvar gensym-code-for-trade-mark-sign	; U+2122 = TM - trademark (~:)
  (map-unicode-1-1-character-to-gensym-character-code (unicode-trade-mark-sign)))
(defvar gensym-char-or-code-for-trade-mark-sign #\:)
(defvar gensym-esc-for-trade-mark-sign? #\~)

;; Note: U+xxxx is standard Unicode notation for a Unicode character assigned
;; hex code xxxx.


(defun-substitution-macro map-simple-character-following-\~-to-gensym-code-if-any (character)
  (or (map-simple-character-following-\~-to-iso-latin1-code-if-any character)
      (character-case character
	(#\W gensym-code-for-capital-ligature-oe)
	(#\w gensym-code-for-small-ligature-oe)
	(#\* gensym-code-for-bullet)
	(#\& gensym-code-for-small-letter-f-with-hook)
	(#\: gensym-code-for-trade-mark-sign))))

(defun-substitution-macro map-gensym-code-to-simple-character-following-\~-if-any (code)
  (or (if (<f code 256)
	  (map-iso-latin1-code-to-simple-character-following-\~-if-any code))
      (cond
	((=f code gensym-code-for-capital-ligature-oe) #\W)
	((=f code gensym-code-for-small-ligature-oe) #\w)
	((=f code gensym-code-for-bullet) #\*)
	((=f code gensym-code-for-small-letter-f-with-hook) #\&)
	((=f code gensym-code-for-trade-mark-sign) #\:))))

(defun-substitution-macro map-unicode-to-simple-character-following-\~-if-any
    (unicode)
  (or (if (<f unicode 256)
	  (map-iso-latin1-code-to-simple-character-following-\~-if-any unicode))
      (cond
	((=f unicode (unicode-capital-ligature-oe)) #\W)
	((=f unicode (unicode-small-ligature-oe)) #\w)
	((=f unicode (unicode-bullet)) #\*)
	((=f unicode (unicode-latin-small-letter-f-with-hook)) #\&)
	((=f unicode (unicode-trade-mark-sign)) #\:))))



(defun-substitution-macro map-unicode-cyrillic-to-code-following-\\-if-any
    (unicode)
  (if (unicode-cyrillic-character-p unicode)
      (unicode-cyrillic-to-gensym-cyrillic unicode)))
      


;;;; Mapping Between Gensym Character and Unicode Code Points



;;; `Map-gensym-character-code-to-unicode' and
;;; `Map-unicode-to-gensym-character-code' map from and to Gensym and to and
;;; from Unicode, respectively.  If a mapping does exist, then this returns
;;; nil.
;;;
;;; Mapping obeys in both directions a precedence.  The mapping precedence is at
;;; present:
;;;
;;;   (1) ASCII/Latin 1 and Special and Accented Characters in G2 4.0;
;;;   (2) Cyrillic Characters;
;;;   (3) Gensym JIS and KSC characters (i.e., JIS X 0208 and KS C 5601);
;;;   (4) All Unicode 1.1 Characters;
;;;   (5) As yet unknown Unicode (as of Unicode 1.1)


(defvar current-extended-utf-g-low-half-character? nil)	; implicit parameter to following:

(defun-substitution-macro map-gensym-character-code-to-unicode
    (gensym-character-code)
  (cond
    ((map-gensym-code-to-simple-character-following-\~-if-any gensym-character-code)
     (map-gensym-character-code-to-unicode-1-1-character gensym-character-code))

    ((legal-gensym-cyrillic-character-p gensym-character-code)
     (map-gensym-character-code-to-unicode-1-1-character gensym-character-code))
    
    ((map-gensym-han-character-code-to-unicode gensym-character-code))
    
    ((map-gensym-character-code-to-unicode-1-1-character gensym-character-code))
    
    (current-extended-utf-g-low-half-character?
     ;; returns two values; fix callers to deal with this where appropriate!
     (map-extended-utf-g-characters-to-unicode
       current-extended-utf-g-low-half-character?		; high-half
       gensym-character-code))		; low-half
    (t #xFFFF)))			; Non-Unicode character!

;; Review byte ordering for extended UTF-G!!





;;;; Support for Unicode <-> Gensym (UTF-G) Mapping


;;; Note: this is just support: the main exported functionality is in LETTERS
;;; and TRANSCODE, q.v.



;;; `Wide-character-is-simple-gensym-character-p' is true if wide-character is
;;; one of the simple gensym characters, i.e., any one of the 95 ASCII printing
;;; characters except for @, \, or ~.  This is used for historical reasons in
;;; the token parser.

;;; `Unicode-is-simple-gensym-character-p' is similar, but it's a macro, and
;;; takes a raw unicode code, rather than a wide character.

(defmacro unicode-is-simple-gensym-character-p (unicode)
  (let ((unicode-variable (make-symbol "CODE")))
    `(let ((,unicode-variable ,unicode))
       (and (<f ,unicode-variable 127)
	    (not (or ,@(loop for code in (escape-character-codes)
			     collect `(=f ,code ,unicode-variable))))))))

(defun-simple wide-character-is-simple-gensym-character-p (wide-character)
  (unicode-is-simple-gensym-character-p (wide-character-code wide-character)))




;;; `Map-unicode-to-gensym-character-code' usually returns one, but may return
;;; two, gensym character codes.  It returns two codes only in the case of
;;; Unicodes belonging to 256-character rows allocated after Unicode 1.1.
;;;
;;; This is biased towards mapping CJK characters to Gensym's Japanese and
;;; Korean code areas.  

;;; The macro `set-gensym-character-codes-from-unicode' is similar, but gives
;;; its result by setting the argument variables code and extended code to what
;;; would be the the first and second values, respectively, of the
;;; map-unicode-to-gensym-character-code.  It returns the value of code as its
;;; only value.

;;; The macro `set-gensym-character-pairs-from-unicode' usually sets one pair
;;; the second pair of variables to nil, and sets one or both of the first pair
;;; to non-nil values.  The first pair is the familiar escape-character?  and
;;; character-or-character-code pair used for emitting UTF-G encoded Gensym
;;; characters.  Note that escape-character? and character-or-character-code are
;;; wide characters in the case where they are not character codes.  The second
;;; pair is the the same, but is only non-nil in the rare case when an extended
;;; UTF-G code is needed.

;;; NOTE: these functions only handle "graphic" characters in UTF-G; in
;;; particular, they don't handle linebreak characters; the calling functions
;;; must deal with this appropriately by preprocessing the Unicode looking
;;; for linebreaks.

(defmacro set-gensym-character-codes-from-unicode
    (unicode code extended-code)
  (let ((unicode-var '#:unicode))	; avoiding-variable-capture def'd later!
    `(let ((,unicode-var ,unicode))
       ;; defaults extended code to nil, and then possibly reverse it in the
       ;; (rarely reached) final clause:
       (setf ,extended-code nil)
       (cond
	 ((unicode-is-simple-gensym-character-p ,unicode-var) ; Optimize ASCII case
	  (setf ,code ,unicode-var))
	 
	 ;; This ensures that Gensym's Accented and Special characters get mapped
	 ;; first, Gensym's Cyrillic, then Gensym's JIS and KSC, then, finally,
	 ;; all other things in Unicode.
	 
	 ((let ((gensym-character-code?
		  (map-unicode-1-1-character-to-gensym-character-code ,unicode-var)))
	    (when (and gensym-character-code?
		       (or (map-gensym-code-to-simple-character-following-\~-if-any
			     gensym-character-code?)
			   (legal-gensym-cyrillic-character-p gensym-character-code?)))
	      (setf ,code gensym-character-code?))))
	 
	 ;; Having this come first means that Unicode will be mapped to the Gensym
	 ;; JIS/CJK sections if possible, which is desirable for now.
	 ((setf ,code (map-unicode-to-gensym-han-character-code ,unicode-var)))
	 
	 ((setf ,code (map-unicode-1-1-character-to-gensym-character-code ,unicode-var)))
	 
	 (t
	  (setf ,extended-code (unicode-to-extended-utf-g-low-half ,unicode-var))
	  (setf ,code (unicode-to-extended-utf-g-high-half ,unicode-var)))))))



(defun-substitution-macro map-unicode-to-gensym-character-code (unicode)
  (let (code extended-code)
    (values 
      (set-gensym-character-codes-from-unicode unicode code extended-code)
      extended-code)))


;;; `Map-unicode-to-gensym-character-code-with-cjk-neutrality' maps unicode to a
;;; Gensym character code, or values 1 and 2 corresponding to a pair of codes,
;;; but differs from map-unicode-to-gensym-character-code in that it does not
;;; make use of the traditional Gensym Korean and Japanese encoding ranges.
;;; This means that CJK ideograph characters ("Han") are transcoded into the
;;; Gensym-UTF-G version of their their unified ("neutral") Unicode code points.
;;;
;;; This is used for printing, which needs a way to store away UTF-G encoded CJK
;;; characters separately, and earlier, than the decision as to which CJK
;;; language preference (= font choice) to make.

(defun map-unicode-to-gensym-character-code-with-cjk-neutrality (unicode)
  (cond
    ((unicode-is-simple-gensym-character-p unicode)
     unicode)
    ((map-unicode-1-1-character-to-gensym-character-code unicode))
    (t
     (values
       (unicode-to-extended-utf-g-low-half unicode)
       (unicode-to-extended-utf-g-high-half unicode)))))

;; New for the upcoming release currently pending, part of the Chinese project.
;; (MHD 4/9/99)



(defmacro set-gensym-character-pairs-from-unicode
    (unicode
      escape-character?-var character-or-character-code-var
      extended-escape-character?-var extended-character-or-character-code-var)
  (let ((unicode-var '#:unicode))	; avoiding-variable-capture def'd later!
    `(let ((,unicode-var ,unicode))
       (setf ,escape-character?-var nil)
       (setf ,extended-escape-character?-var nil)
       (setf ,extended-character-or-character-code-var nil)
       (cond
	 ((unicode-is-simple-gensym-character-p ,unicode-var)
	  (setf ,character-or-character-code-var
		(code-wide-character ,unicode-var)))
	 ((setf ,character-or-character-code-var		
		(map-unicode-to-simple-character-following-\~-if-any
		  ,unicode-var))
	  (setq ,character-or-character-code-var ; Lisp Char -> Wide char
		(character-to-wide-character ,character-or-character-code-var))
	  (setf ,escape-character?-var %\~)		; See note
	  ,character-or-character-code-var)
	 (t
	  (setf ,escape-character?-var %\\)
	  (cond
	    ((setf ,character-or-character-code-var
		   (map-unicode-cyrillic-to-code-following-\\-if-any
		     ,unicode-var)))
	    ((setf ,character-or-character-code-var
		   (map-unicode-to-gensym-han-character-code
		     ,unicode-var)))
	    ((setf ,character-or-character-code-var
		   (map-unicode-1-1-character-to-gensym-character-code
		     ,unicode-var)))
	    (t
	     (setf ,extended-escape-character?-var %\\)
	     (setf ,extended-character-or-character-code-var
		   (unicode-to-extended-utf-g-low-half ,unicode-var))
	     (setf ,character-or-character-code-var
		   (unicode-to-extended-utf-g-high-half ,unicode-var))
	     ,character-or-character-code-var)))))))

;; This pulls out all the stops for efficiency/compactness, including taking
;; advantage of the fact the (cond (p)) returns the value of p, and that (setf
;; (x y) ...)  returns the value of (x y).  Things you're taught not to do in
;; Lisp 101.  (MHD 6/4/97)

;; Note: The character reader macro, e.g., #.%\\, cannot be used here because
;; these constants are defined in this module, so they're not available at read
;; time.







;;;; Mapping Between Gensym Complex Characters to Gensym Character Codes







;;; `Escape-character-code-p' is true if simple-gensym-character-code is one of
;;; the escape characters in the Gensym character set encoding (now known as
;;; UTF-G).

(defmacro escape-character-code-p (simple-gensym-character-code)
  `(let ((simple-gensym-character-code ,simple-gensym-character-code))
     (or
       . ,(loop for esc in (escape-characters)
		collect `(=f simple-gensym-character-code
			     ',(ascii-char-code esc))))))



;;; `Gensym-character-code-to-pair' maps character-code, a code representing
;;; a particular member of the Gensym character set, to a pair of variables,
;;; character-or-character-code and escape-character?, representing the
;;; same character.
;;;
;;; Note that this assumes only legal values for character-code.  If a value for
;;; character-code supplied that does not correspond to a Gensym character, the
;;; results are undefined.
;;;
;;; `Gensym-character-pair-to-code' is similar, but works in the opposite
;;; direction.
;;;
;;; These are primitives, and therefore can be savvy to such things as the fact
;;; that code-char and char-code use ASCII to encode Common Lisp standard
;;; characters.

(defun-substitution-macro gensym-character-code-to-pair (character-code)
  (let (char)
    (cond
      ((=f character-code gensym-code-for-linebreak)
       (values
	 gensym-char-or-code-for-linebreak
	 gensym-esc-for-linebreak?))
      ((=f character-code gensym-code-for-paragraph-break)
       (values
	 gensym-char-or-code-for-paragraph-break
	 gensym-esc-for-paragraph-break?))
      ((and (simple-character-code-p character-code) ; simple gensym character case
	    (not (escape-character-code-p character-code)))
       (values (ascii-code-char character-code) nil))
      ((setq char
	     (map-gensym-code-to-simple-character-following-\~-if-any
	       character-code))
       (values char #\~))
      (t
       (values character-code #\\)))))



;;; `Gensym-character-pair-to-code' ... This returns #xFFFF for any
;;; illegal or unrecognized complex character.

(defun-substitution-macro gensym-character-pair-to-code
    (character-or-character-code escape-character?)
  (cond
    ((null escape-character?)
     ;; must be true: (simple-gensym-character-p character-or-character-code)
     (ascii-char-code character-or-character-code))
    ((if (char= escape-character? #\~)
	 (map-simple-character-following-\~-to-gensym-code-if-any
	   character-or-character-code)))
    ((gensym-character=
       character-or-character-code escape-character?
       gensym-char-or-code-for-linebreak gensym-esc-for-linebreak?)
     gensym-code-for-linebreak)
    ((gensym-character=
       character-or-character-code escape-character?
       gensym-char-or-code-for-paragraph-break gensym-esc-for-paragraph-break?)
     gensym-code-for-paragraph-break)
    ((if (not (eql escape-character? #\\)) #xFFFF))
    (t
     character-or-character-code)))





;;;; Wide Characters



;;; A `wide character' is implemented as the `wide character code' datatype.  A
;;; `wide character code' is any unsigned 16-bit integer.  Cf. "unicode
;;; character" (above).  Note in particular that #xFFFF and #xFFFE may be
;;; regarded as wide characters, but not as unicode characters.

;;; NB: For a brief period beginning with the initial commit, around 4/26/96,
;;; the wide character will allow the union of this type and the original Common
;;; Lisp character type.  However, that will ultimately be changed.  Users
;;; should in general write code that doesn't depend on any particular
;;; implementation.  Allowing the union type would be an OK thing to do if not
;;; for the performance penalty it would cause, since the need would arise to
;;; check the type at the lowest level access point when setting, leading to
;;; branch instructions too frequently breaking up basic blocks to get good
;;; optimization, especially with modern RISC hardware and compilers.
;;;
;;; Note that committing to the current implementation would allow us to commit
;;; to supporting EQL comparison for for wide characters, as well as type-of
;;; consistency among all wide characters.  We are deferring committing to that
;;; for now just to leave ourselves maximum flexibility.  I.e., eqlw should
;;; still be used to compare wide characters (though eql will work), and it
;;; should not be assumed that (eq (type-of wc1) (type-of wc2)) is true, where
;;; wc1 and and wc2 are wide characters.
;;;
;;; Code constants are available for all of the Standard Common Lisp characters;
;;; see below.

;; We don't do a deftype because deftype is known to be broken in most every
;; Lisp, in particular both the Lucid Common Lisp we use and in Chestnut.  If it
;; worked, we'd define wide-character to be the union of the types CHARACTER and
;; (MOD #.(expt 2 16)).

;; Deftype of "OR" types is broken, but a deftype of wide-character to fixnum
;; would work in all current implementations.  This is what we did for
;; gensym-float.  -jra 5/22/96

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro expand-wide-character-type-function ()
  ''fixnum)
)


(defmacro expand-wide-character-type ()
  (expand-wide-character-type-function))

(deftype wide-character () #.(expand-wide-character-type-function))



;;; `Wide-character-p' is true if thing is a wide character.

(defun-substitution-macro wide-character-p (thing)
  (typep thing 'wide-character))

;; "characterpw"?

;; Now this essentially tests for fixnums; verify that the above is as efficient
;; as the equivalent fixnum test!
;;
;; In development we may want to add
;; some large postive offset, like 100,000,000 or 2^28 or some such thing so
;; that we can do a range check on wide-character arguments to verify that they
;; have been through the code-charw abstraction.  -jra 5/22/96

(defun-simple wide-character-p-function (thing)
  (wide-character-p thing))



;;; `Normalize-wide-character-code' returns a wide character represented as its
;;; representation data type in a stable way (i.e., fixed at compile time --
;;; doesn't vary at runtime).
;;;
;;; For code to be fully abstracted, it must not rely on the implementation of
;;; of a wide character being stable, and subject to equality testing under EQL,
;;; from instanct to instance of a wide character for the exact same code.  In
;;; particular, it should not be assumed that
;;;
;;;    (or (not (char=w c1 c2)) (eql c1 c2))
;;;
;;; Instead, one may assume no more than that
;;; 
;;;    (or (not (char=w c1 c2))
;;;        (eql (normalize-wide-character c1) (normalize-wide-character c2)))
;;;
;;; For example, a way to use CASE and remain fully abstracted is as follows:
;;;
;;;     (case (normalize-wide-character wc)
;;;       (#.(normalize-wide-character #.%\a) ...)
;;;       (#.(normalize-wide-character #.%\b) ...)
;;;       ...)

(def-substitution-macro normalize-wide-character (wide-character)
  wide-character)


;; This function needs to go away when we adopt a uniform representation for
;; wide characters.  -jra 5/22/96
;;
;; -- I don't agree.  It's a no-op with the current implementation, but it's
;; needed to allow fully abstracted use of wide characters with no assumptions
;; about implementation.





;;;; Code Constants for Wide Characters




;;; Code constants whose print names are stylized after various individual
;;; characters' names are available for all of the Standard Common Lisp
;;; characters.  In addition, numerous well-known Unicode characters have named
;;; constants, notable line-separator and paragraph-separator.  Additional ones
;;; can and will be added as necessary and convenient.  The symbol names of the
;;; constants are defined below and in general have print names of the form
;;;
;;;     %<letter or word>
;;;
;;; where <letter or word> is either a single (ASCII) character corresponding to
;;; an ASCII code, which should generally be expressed as
;;;
;;;     \<character>
;;;
;;; i.e., so as to make the letter case (upper or lower) explicit,
;;;
;;; or a reserved character name.
;;;
;;; Currently the following reserved character names exist.
;;;
;;;     The ASCII/Common Lisp Set:
;;;
;;;     %space %sp
;;;     %newline %linefeed
;;;     %return
;;;     %tab
;;;     %page
;;;     %null
;;;     %escape %esc
;;;
;;;     The Unicode Set: (these names are in synch, modulo the "unicode-"
;;;     prefix, with the section "Macros for Some Well-known Wide Characters",
;;;     q.v., in CHARACTERS)
;;;
;;;     %line-separator
;;;     %paragraph-separator
;;;     %ordinary-space  (note: same as %space)
;;;     ;; Not included: %tab  (note: same as %tab, same constant defined above)
;;;     %fixed-width-space  (note: called "figure space" in Unicode)
;;;     %no-break-space
;;;     %zero-width-no-break-space
;;;     %soft-hyphen
;;;     %copyright-sign
;;;     %registered-sign
;;;     %trade-mark-sign
;;;     %capital-ligature-oe
;;;     %small-ligature-oe
;;;     %bullet
;;;     %latin-small-letter-f-with-hook  (note: adobe name: florin)
;;;     %hair-space
;;;     %thin-space
;;;     %en-space
;;;     %em-space
;;;     %zero-width-space
;;;     %zero-width-joiner
;;;
;;; The following characters have code single-character constants
;;;
;;;     ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ?
;;;   @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _
;;;   ` a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~
;;;
;;; So, for example, the constant whose value is the ASCII code for letter
;;; lowercase-g can be written readably in Lisp as
;;;
;;;    %\g
;;;
;;; Since we generally would like the code itself to appear (and integers
;;; are self-evaluating), the constant should be made to evaluate at read
;;; time, i.e., by using the sharpsign-dot (#.) form. Thus, we write
;;;
;;;    #.%\g
;;;
;;; In general, #.%\x is to wide characters as #\x is to (Common Lisp)
;;; characters.
;;;
;;; Note: the first single-character constant is space.  I.e., the symbol
;;; whose print name is "% " is bound to the ASCII code for space (32). It
;;; can be written readably as either
;;;
;;;    %\
;;;
;;; or
;;;
;;;    |% |

(defmacro define-character-code-name-constants ()
  `(progn
     ,@(loop for (name code)
		 in '((%space #.(ascii-char-code #\space))
		      (%sp #.(ascii-char-code #\space))
		      (%newline #.(ascii-char-code #\newline))
		      (%linefeed #.(ascii-char-code #\linefeed))
		      (%return #.(ascii-char-code #\return))
		      (%tab #.(ascii-char-code #\tab))
		      (%page #.(ascii-char-code #\page))
		      (%null #.(ascii-char-code #\null))
		      (%escape #.(ascii-char-code #\escape))
		      (%esc #.(ascii-char-code #\esc)))
	     collect `(defconstant ,name ,(code-wide-character code)))
     ,@(loop for (name code)
		 in '((%line-separator #.(unicode-line-separator))
		      (%paragraph-separator #.(unicode-paragraph-separator))
		      (%ordinary-space #.(unicode-ordinary-space))
		      ;; (%tab #.(unicode-tab))  ; already defined above
		      (%fixed-width-space #.(unicode-fixed-width-space))
		      (%no-break-space #.(unicode-no-break-space))
		      (%zero-width-no-break-space #.(unicode-zero-width-no-break-space))
		      (%soft-hyphen #.(unicode-soft-hyphen))
		      (%copyright-sign #.(unicode-copyright-sign))
		      (%registered-sign #.(unicode-registered-sign))
		      (%trade-mark-sign #.(unicode-trade-mark-sign))
		      (%capital-ligature-oe #.(unicode-capital-ligature-oe))
		      (%small-ligature-oe #.(unicode-small-ligature-oe))
		      (%bullet #.(unicode-bullet))
		      (%latin-small-letter-f-with-hook
		       #.(unicode-latin-small-letter-f-with-hook))
		      (%hair-space #.(unicode-hair-space))
		      (%thin-space #.(unicode-thin-space))
		      (%en-space #.(unicode-en-space))
		      (%em-space #.(unicode-em-space))
		      (%zero-width-space #.(unicode-zero-width-space))
		      (%zero-width-joiner #.(unicode-zero-width-joiner))
		      (%inverted-exclamation-point
		       #.(unicode-inverted-exclamation-point))
		      (%cent-sign #.(unicode-cent-sign))
		      (%pound-sign #.(unicode-pound-sign))
		      (%yen-sign #.(unicode-yen-sign))
		      (%right-pointing-double-angle-quotation-mark
		        #.(unicode-right-pointing-double-angle-quotation-mark))
		      (%left-pointing-double-angle-quotation-mark
		        #.(unicode-left-pointing-double-angle-quotation-mark))
		      (%inverted-question-mark
		       #.(unicode-inverted-question-mark))
		      (%euro-sign
		       #.(unicode-euro-sign)))
	     collect `(defconstant ,name ,(code-wide-character code)))))

(define-character-code-name-constants)

(defmacro define-character-code-letter-constants ()
  `(progn
     . ,(loop for code from 32 to 126	; range of ASCII graphics characters
	      collect `(defconstant
			   ,(intern (format nil "%~c" (ascii-code-char code)))
			 ,(code-wide-character code)))))

(define-character-code-letter-constants)





;;;; Reader for Wide Characters


;;; `Read-wide-character' is a reader macro subfunction, called while reading a
;;; #uHHHH Unicode wide character constant.  It is called after #U has been
;;; read.  It expects to read a 4-digit hex integer from stream.  It ignores
;;; subchar and arg.  If there's a problem with the input it may signal an
;;; error.  Otherwise, it returns a 16-bit unsigned integer.  Note that this is
;;; expected to be used primarily at read time.

#-chestnut-trans
(eval-when (:compile-toplevel :load-toplevel :execute)
(defun read-wide-character (stream subchar arg)
  (declare (ignore subchar arg))
  (loop repeat 4
	for character = (read-char stream t nil t)
	as weight = (or (digit-char-p character 16)
			(error "bad hex digit ~c (code: ~D) in #uHHHH"
			       character (char-code character)))
	as unicode fixnum first weight then (logiorf (ashf unicode 4) weight)
	finally (return (code-wide-character unicode))))
)



;;;; Wide-character Reader Macro

(defmacro set-dispatch-macro-character (&rest args)
  #-ansi-cl `(lisp:set-dispatch-macro-character ,@args)
  #+ansi-cl `(common-lisp:set-dispatch-macro-character ,@args))

(eval-when
    #+chestnut-trans (:compile-toplevel)
    #-chestnut-trans (:compile-toplevel :load-toplevel :execute)
  (set-dispatch-macro-character #\# #\u 'read-wide-character))

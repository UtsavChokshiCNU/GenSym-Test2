;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp; External-Format: LATIN-1; -*-
(in-package "AB")

;;;; Module CHARACTERS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David and Ong, Peng Tsin



(declare-forward-reference obtain-simple-gensym-string function)



;;; This file contains constant definitions for non-Common Lisp characters.
;;; All references to the constants defined in this file should be via a
;;; compiler reader ("#.") for efficiency.  These refrences should assume that
;;; these constants will only be available during compile time.




;; Questions from LH.
;;
;;   (1) Is there some way to reduce the terminology and complexity?
;;
;;   (4) Wouldn't real defvars save significant space in Common Lisps that do
;;   not share constants fully, especially since some of the constants here are
;;   large structures?
;;   ANS:  The large structures you see in this file are used for development
;;   only.
;;
;;   (5) Should all characters representable within G2 be representable as
;;   Gensym characters?  ANS:  I can only think of one reason not to do so:  If
;;   we have user loadable character sets, we might save some space by not
;;   representing everything with Gensym characters.  However, we will need
;;   some ways to distinguish between character sets.  Should Gensym characters
;;   be called `text characters'?  ANS:  I think `Gensym characters' is fine.




(eval-when (:compile-toplevel :load-toplevel :execute)

(pushnew :ascii *features*)

)

;; All uses of this feature should be confined to this module, for reasons of
;; abstraction.









;;;; Glossary for Characters



;;; `Lisp character' - a Lisp character.  It does not have to be a Common Lisp
;;; character, so long as it can be specified in Lisp with a "#\" prefix.
;;; Lisp characters are platform dependent.

;;; `standard character' - a standard character is one of the standard Common
;;; Lisp characters and it is one of the following (96 characters):
;;;
;;;   ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ?
;;;   @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _
;;;   ` a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~
;;;   space newline
;;;
;;; These characters are platform independent.

;;; `semi-standard character' - One of the following:  backspace, tab,
;;; linefeed, page (or formfeed), return, and rubout (or delete).  (Note that
;;; on some platforms, #\newline might be eql #\linefeed or #\return.)
;;; Semi-standard characters are platform independent.

;;; `control character' - one of the following (33 characters):  control-@,
;;; control-a, control-b, ... , control-y, control-z, control-[, control-\,
;;; control-], control-^, control-_, and escape.  (Note that control-[ is eql
;;; escape on the conventional machines.)  Control characters are platform
;;; dependent, but we will define a set of constants which are machine
;;; independent in G2.

;;; `standard typeable character' - the set of standard typeable characters
;;; consists of the control characters, the semi-standard characters, and the
;;; standard characters.  Some standard typeable characters might be eql on
;;; some platforms - for example, control-H and backspace on conventional
;;; machines.  The set of standard typeable characters should correspond to the
;;; set resulting from the intersection of all typeable keys on all workstation
;;; keyboards.  (Note that keys that generate more than one character should be
;;; handled at a higher level of abstraction.)  Standard typeable characters
;;; are platform dependent.

;;; `native typeable character' - a Lisp character which can be produced by the
;;; native keyboard on the native platform but is not a standard typeable
;;; character.

;;; `typeable character' - a standard typeable character or a native typeable
;;; character.

;;; `ascii code' - the numbers 0 through 127, inclusive.

;;; `ascii character' - a character which is mapped by the Common Lisp function
;;; char-int to an ascii code.  These characters are platform dependent.

;;; `string character' - a character which can be part of a simple string.
;;; This is a platform dependent definition.



;;; Gensym Characters

;;; `simple character' - a standard Common Lisp character (object) other than
;;; the newline character.  The `standard Common Lisp character set', as
;;; defined in the Common Lisp manual, consists of the 95 standard
;;; ASCII printing characters (94 non-blank plus space), plus a newline
;;; character.  Thus, there are 95 simple characters.

;;; `escape character' - any of the following characters: @ ~ \ (for now -- and
;;; eventually also these may also become escape characters: # $ % & ^ ` |).

;;; `ESCAPE' - (noun) the ascii character ESCAPE is the value of the constant
;;; char-escape.  It is #\escape on some platforms and (code-char 27) on others.
;;; This character is not an escape character.

;;; `complex character sequence' - a sequence of two or more simple characters,
;;; beginning with an escape character (not ESCAPE), that represents a printing
;;; character (a letter, digit, punctuation character, mathematical symbol,
;;; accent etc.), a space, or some format or control directive or delimiter
;;; thereof.

;;; `simple gensym character' - a simple character that is not an escape
;;; character.  It is a simple character that represents itself in a text string
;;; and is one of the following characters.
;;;
;;;    space ! " ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ?
;;;    A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ ] _
;;;    a b c d e f g h i j k l m n o p q r s t u v w x y z { }
;;;    # $ % & ^ ` |  (for now -- eventually these may become escape characters)

;;; `gensym character' - a character in the Gensym Character Set.
;;;
;;; A gensym character may be represented in one of two ways:
;;;
;;;   (1) as a pair of Lisp objects, character-or-character-code and
;;;   escape-character?, character-or-character-code is either a simple gensym
;;;   character or a 16 bit number, and where escape-character? is either NIL or
;;;   an escape character.
;;;
;;;   (2) as a `gensym character code', a single object that represents a Gensym
;;;   character, namely as a 16-bit integer.  Each gensym character is alotted a
;;;   unique gensym character code.
;;;
;;;   The 16-bit encoding space is divided into various rectangular encoding
;;;   blocks, as follows.  (Note: you read a rectangular encoding block by
;;;   as a 2-d array of codes bounded by the most significant byte of the first and
;;;   second hex codes in the Y dimension, and by the least significant byte of
;;;   the first and second hext codes in the X dimension.)
;;;
;;;
;;;     0x0000        (ASCII/ISO 646 Graphic and Control codes and ISO Latin 1)
;;;     .    .        (aka, Basic Latin/Latin-1 Supplement, from Unicode)
;;;     0x00ff
;;;
;;;     0x2000        (Cyrillic Encoding Block from Unicode)
;;;     .    .
;;;     0x20ff
;;;
;;;     0x2121        (Rectangular code range for Japanese Standard JIS X 0208-1990)
;;;     .    .
;;;     0x747e
;;;
;;;     0x217f        (Rectangular code range for Korean Standard KS C 5601)
;;;     .    .
;;;     0x7ddd
;;;
;;; Issues: - adding formatting characters from ascii (e.g., tab, return, page)
;;;         - adding formatting characters from Latin 1 (e.g., soft-hyphen)
;;;         - adding formatting characters unique to G2
;;;            a - making some maybe be 1:1 with ascii, e.g., @L, or with
;;;                Unicode, e.g., Unicode's special newline character
;;;            b - losing some?
;;;            c - making some fit in elsewhere (e.g., non-plain tab character?)
;;;         - making non-Latin1/non-ASCII characters fit in, e.g., TM (trademark)
;;;           (Consider taking in all of the Unicode character sets' dingbats,
;;;           which includes TM (trademark).)
;;;         - where to fit in Chinese/Traditional and Chinese/Simplified
;;;
;;;
;;; In addition, there are various ways of encoding a gensym character, e.g., as
;;; a simple gensym character or complex character sequence, or as a character
;;; in an array, e.g., in a "wide-byte" (16-bit) character string or array.
;;; Variations and other methods are imaginable.


;;; Gensym Fonts (Ab Fonts)

;;; `roman font' - an ab font that contains all the simple characters, with
;;; ascii character codes, plus other special printing characters.

;;; `kanji font' - an ab font that can contain thousands of Kanji characters.







;;;; Text Strings



;;; A `text string' is a Common Lisp string that may consist of any sequence of
;;; Gensym characters.  A text string is used primarily to represent lines of
;;; text.  A text string should never be shared, except transiently.

;;; At the present, there are no real restrictions in what characters can or
;;; cannot be stored in a text string.  Thus, JIS strings (in KFEP1) have been
;;; defined to make use of the text string facilities.  If the implementation of
;;; text string is changed in the future, the implementation of JIS strings must
;;; also be changed.

;;; A `simple text string' is a text string represented as a simple string. An
;;; `adjustable text string' is an adjustible string (with a fill pointer),
;;; typically written incrementally via twith-output-to-gensym-string.  For further
;;; information, see under "strings" in the Common Lisp manual.



;;; `Maximum-suggested-length-for-simple-gensym-strings' determines the maximum
;;; length of simple text strings kept in length-specific pools.  Text strings
;;; longer than this are less efficient to use represented as an adjustable text
;;; string.

(defparameter maximum-suggested-length-for-simple-gensym-strings 64)





;;; `gensym-string-p' is true if gensym-thing is a text string.  At present,
;;; gensym-thing is considered a text string as long as it is a Common Lisp
;;; string.
;;;
;;; While it is an error for a text string to be a string with an adjustable
;;; array (string), we don't test for this in this predicate, because such
;;; objects are not supposed to generally exist in our environments.  The
;;; argument name is therefore gensym-thing, as opposed to thing, to indicate
;;; that its domain is a subset of all possible Common Lisp "things".
;;;
;;; (At present, it is probably not harmful for them to exist; if it were, then
;;; it would need to be asserted that Common Lisp functions do not give rise to
;;; them causing our environment to be contaminated.)

(defmacro gensym-string-p (gensym-thing)
  `(stringp ,gensym-thing))

;; This was introduced lately, 1/3/95.  Up until now, stringp has generally been
;; used instead.  This should now be preferred, and stringp should be
;; transitioned away from.
;;
;; Make sure this is efficient in all implementations.  This should be inlined,
;; ideally, in all production implementations.  (MHD 1/3/95)





;;; `Adjustable-gensym-string-p' is true if gensym-string is an adjustable text string.

(defmacro adjustable-gensym-string-p (gensym-string)
  `(array-has-fill-pointer-p (the string ,gensym-string)))

;; Note that there is a confusion in the terminology here.  The predicate above
;; does not test for Common Lisp adjustable strings, it tests for Common Lisp
;; fill-pointered strings.  Gensym's code currently does not make any use of
;; Common Lisp adjustable array features, and it can not.  The Common Lisp
;; adjustable array features cons, whereas fill pointered strings do not.  -jra
;; 7/26/93



;;; `Simple-gensym-string-p' is true if gensym-string is a simple text string.

(defmacro simple-gensym-string-p (gensym-string)
  `(not (array-has-fill-pointer-p (the string ,gensym-string))))




;;; `Gchar' is the same as char of its first two arguments, but expands into
;;; schar if string-is-simple? is true.  (Schar is open-coded in many Common
;;; Lisp implementations.)

(defmacro Gchar (gensym-string index string-is-simple?)
  (if (constantp string-is-simple?)
      (if (eval string-is-simple?)
          `(schar ,gensym-string ,index)
          `(char ,gensym-string ,index))
      `(Gchar-1 ,gensym-string ,index ,string-is-simple?)))

(def-substitution-macro Gchar-1 (gensym-string index string-is-simple?)
  (if string-is-simple?
      (schar gensym-string index)
      (char gensym-string index)))

;; In Common Lisp implementations where char and schar are identical (as they are in
;; the TI Explorer as of 3/11/89), this should expand more simply.




;;; `Glength' is the same as length of its first argument, but expands with an
;;; appropriate argument declaration if string-is-simple? is true.

(defmacro Glength (gensym-string string-is-simple?)
  (if (constantp string-is-simple?)
      (if (eval string-is-simple?)
          `(length-of-simple-string ,gensym-string)
          `(length (the string ,gensym-string)))
      `(Glength-1 ,gensym-string ,string-is-simple?)))

(def-substitution-macro Glength-1 (gensym-string string-is-simple?)
  (if string-is-simple?
      (length-of-simple-string gensym-string)
      (length (the string gensym-string))))






;;;; Use of Gensym Characters



;;; All text strings in G2, whether they represent text lines or not, must
;;; consist entirely of "Gensym characters" (see below).  Thus, for example,
;;; slot value writers and format-gensym-string control-string arguments must
;;; conform to Gensym character conventions.

;;; Major alphabets in the Gensym character set include: Roman (the default),
;;; Kanji, Katakana, Hiragana, Cyrillic, Hebrew, Thai, Arabic, Greek, and Math
;;; (miscellaneous signs).

;; Consider requiring that the symbol names of all symbol tokens, category
;; names, and object names consist entirely of Gensym characters.

;; Consider having in text boxes or text strings a flag to indicate the
;; possible presence of escape characters, to gain a bit of speed.

;; Here are some Gensym character implementation issues:
;;
;;    (1) mapping to Gensym characters from user input, in each implementation;
;;
;;    (2) token parsing;
;;
;;    (3) text formatting;
;;
;;    (4) mapping a Gensym character to a font plus a character code (font
;;    character  index, taking "context" (?), e.g. italicization, into
;;    account;
;;
;;    (5) conversion of sequences of characters in old saved KBs;
;;
;;    (6) alphabetical ordering, especially for directories of names;
;;
;;    (7) printing Gensym characters on line printers.



;; Do not use these where you can avoid them (say by using predicates).



;;; `Convert-simple-character-to-ascii' converts character to the equivalent
;;; ascii code if it is a simple character.  Otherwise, it returns a fixnum not
;;; in the range of ascii codes for simple characters.

(defmacro convert-simple-character-to-ascii (character)
  ;; (convert-simple-character-to-ascii #\5)
  `(the fixnum (char-int ,character)))

;; In Common Lisp implementations where char-int does not produce an ascii
;; code, this would have to map the result of char-int into ascii.  In all
;; implementations on which G2 is running, char-int does what you want.

;; In Common Lisp implementations where char-int is slow, write a fast
;; equivalent.

;; Consider defining this as (logandf (char-int ,character) 127) to guarantee that
;; the result is an ascii code, no matter what, and thus that indexing into an
;; ab-font array cannot fail.






;;;`Convert-ascii-to-simple-character' converts an ascii code between 32 and 126
;;; (inclusive) to a simple character.

(defmacro convert-ascii-to-simple-character (ascii)
  `(code-char (the fixnum ,ascii)))



;;; `Simple-character-code-p' is true if event-code (a fixnum) is the code for a
;;; simple character.  (Ascii codes are a subset of event codes.)

(defmacro simple-character-code-p (event-code)
  `(<=f 32 ,event-code 126))                        ; 126 (not 127) is correct

;; This assumes that ascii codes are a subset of "event codes".  At present,
;; however, "event code" is not defined, nor is its relationship to ascii specified,
;; though it is widely used.  It would be good to be more thorough about definitions
;; of terms!  (LH)



;;; Convert-simple-character-code-to-character ...

(defmacro convert-simple-character-code-to-character (simple-character-code)
  `(code-char (the fixnum ,simple-character-code)))

;;; Note that ascii-char-code and ascii-code-char are defined in files.




;;; `Simple-character-p' is true if character (a character object) is one of the
;;; 95 simple characters.

(defmacro simple-character-p (character)
  `(simple-character-code-p (convert-simple-character-to-ascii ,character)))


;;; `Simple-gensym-character-p' is true if character (a character object) is a
;;; simple character, but not one of the escape characters.

(defmacro simple-gensym-character-p (character)
  `(let ((character ,character))
     (and (simple-character-p character)
          (not (member character (escape-characters))))))

;; The current ordering in this module prevents this macro from being used until
;; after escape-characters is defined, below.




;;; `Read-string-character-from-gensym-string' returns the character at the position in
;;; gensym-string specified by index-variable.  Index-variable is advanced past
;;; the character.  This works even if the character is not simple; thus it may
;;; be used to verify that gensym-string consists only of simple characters.

(defmacro read-string-character-from-gensym-string
          (gensym-string index-variable gensym-string-is-simple?)
  `(prog1
     (gchar ,gensym-string ,index-variable ,gensym-string-is-simple?)
     (incff ,index-variable)))



;;; `Read-simple-character-from-gensym-string' returns the simple character at the
;;; position in gensym-string specified by index-variable.  Index-variable is advanced
;;; past the simple character.

(defmacro read-simple-character-from-gensym-string
          (gensym-string index-variable gensym-string-is-simple?)
  `(prog1
     (gchar ,gensym-string ,index-variable ,gensym-string-is-simple?)
     (incff ,index-variable)))



;;; `Write-simple-character-into-gensym-string' writes simple-character into the
;;; position of gensym-string specified by index-variable.  Index-variable is advanced
;;; past the written character.

(defmacro write-simple-character-into-gensym-string
          (simple-character gensym-string index-variable gensym-string-is-simple?)
  (let ((character (gensym))
        (string (gensym)))
    `(let ((,character ,simple-character)
           (,string ,gensym-string))
       (if ,gensym-string-is-simple?
           (setf (schar ,string ,index-variable) ,character)
           (setf (char ,string ,index-variable) ,character))
       (incff ,index-variable))))

;; Consider eliminating the gensym-string-is-simple? argument, which would simplify this
;; at the cost of a bit of speed.



;;; `Escape-characters' returns a list of the currently implemented escape characters.
;;;
;;; `Escape-character-codes' returns a list of the (ASCII) codes for the
;;; currently implemented escape characters.

(defmacro escape-characters ()
  ''(#\@ #\~ #\\))

(defmacro escape-character-codes ()
  ''#.(loop for x in '(#\@ #\~ #\\)
            collect (char-code x)))

(defmacro escape-wide-characters ()
  ''(#.(character-to-wide-character #\@)
     #.(character-to-wide-character #\~)
     #.(character-to-wide-character #\\)))

;; If this weren't defined before the wide character constants, we'd use #.%\@,
;; #.%\~, and #.%\\. (MHD 7/9/96)

;; To add two more escape characters, say #\# and #\$, the following must be done:
;;    (1) all uses of # and $ in strings in G2 source files must be prefixed by ~;
;;    (2) the table below of ~ complex characters must be updated;
;;    (3) five-escape-characters-p must be defined appropriately in module FILES;
;;    (4) read-character-sequence-as-gensym-string in module FILES must be revised near
;;          where ~ is handled; and
;;    (5) all text handling code must be revised to handle the new escape characters.

;; As other escape characters are added, make sure that punctuation mark and symbol
;; parsing has been fixed.  See below.



;;; `Skip-past-gensym-character' advances index-variable past the gensym character in
;;; gensym-string that starts at the position specified by index-variable.

(defmacro skip-past-gensym-character
          (gensym-string index-variable gensym-string-is-simple?)
  (let ((string (gensym))
        (string-is-simple? (gensym)))
    `(let* ((,string ,gensym-string)
            (,string-is-simple? ,gensym-string-is-simple?))
       (case (read-simple-character-from-gensym-string
              ,string ,index-variable ,string-is-simple?)
         ((#\@ #\~)
          (incff ,index-variable))
         (#\\
          (skip-past-kanji-character
            ,string ,index-variable ,string-is-simple?))))))

;; Consider trying to avoid the unnecessary binding of string and string-is-simple?.

;; As other escape characters are added, handle them herein as appropriate.



;;; `Previous-character-might-be-complex-p' is true if the gensym character to the
;;; left of position i (a string index) in gensym-string might be, but is not with
;;; certainty, complex, where i specifies a position after a gensym character.

(def-substitution-macro previous-character-might-be-complex-p
                        (gensym-string i gensym-string-is-simple?)
  (and (>f i 1)
       (or (memberp (gchar gensym-string (-f i 2) gensym-string-is-simple?) '(#\@ #\~))
           (and (>f i 2)
                (or (eql (gchar gensym-string (-f i 3) gensym-string-is-simple?) #\\)
                    (and (>f i 3)
                         (eql (gchar gensym-string (-f i 4) gensym-string-is-simple?)
                              #\\)))))))

;; This is defined as a macro primarily because its only obvious use is in function
;; find-previous-character-if-any in module BOXES.

;; Consider changing "previous" to "preceding", and consider using "succeeding".

;; As other escape characters are added, handle them herein as appropriate.








;;;; Format Control Characters (@ Complex Characters)



;;; The @ complex characters are as follows:
;;;
;;;    @P followed by n (zero or more) ordinary spaces, at the beginning of a
;;;    line only, for a new paragraph that is to be indented by n spaces in
;;;    addition to any paragraph or turnover line indentation
;;;
;;;    @L followed by n (zero or more) ordinary spaces, at the beginning of a
;;;    line only, for a (forced) line break within a paragraph, where this line
;;;    is to be indented by n spaces and any subsequent lines are to be indented
;;;    by n spaces plus any turnover line indentation
;;;
;;;    @F ... @E   default font family piece of text
;;;    @G ... @E   alternate font family piece of text
;;;
;;;    @R ... @E   roman (light) face piece of text
;;;    @I ... @E   italics piece of text
;;;    @B ... @E   boldface piece of text
;;;    @J ... @E   bold italics piece of text
;;;    @C ... @E   small caps piece of text
;;;
;;;    @S ... @E   piece of text with no line breaks allowed
;;;
;;;    @U ... @E   superscript on preceding baseline character or piece of text
;;;    @D ... @E   subscript on preceding baseline character or piece of text
;;;    @A ... @E   piece of text above preceding baseline character or piece of
;;;                text
;;;    @O ... @E   piece of text below preceding baseline character or piece of
;;;                text
;;;
;;;    @T ... @N ... @N ... @E   vertical stack
;;;    @N          to separate vertically stacked elements (read "next")

;;;    @H to separate vertically stacked elements by means of a "horizontal
;;;    rule"
;;;
;;;    @S ... @E@A@E   bar over piece of text
;;;    @S ... @E@O@E   bar under piece of text
;;;    @S[ ... ]@E     for brackets of a size appropriate to piece of text
;;;
;;;    @V   very thin space
;;;    @W   thin space
;;;    @X   en space
;;;    @Y   em space
;;;    @K   tab
;;;
;;;    @R   permit line break here
;;;    @Q   do not permit line break here
;;;
;;; Note that things delimited by @E may be nested.  Also note that, for an @S,
;;; @U, @D, @A, @O, or @T, the matching @E must be on the same line.
;;;
;;; Note that any complex character consisting of @ followed by an alphabetic
;;; character is to parse as a punctuation mark, except that (1) @L, @V, @W,
;;; @X, @K, and (for now) @Y are to look like ordinary spaces to the parser
;;; and (2) @R and @Q are to be entirely invisible to the parser.
;;;
;;; Note that @K was only assigned as of 9/8/95 by MHD.  The earlier assignments
;;; were by LH, almost 9 years years earlier.  NB: its handling must be
;;; implemented, and its role as a spacing character must implemented throughout!
;;;
;;; Note that @M, @Z, @a - @z, are not presently assigned.
;;;
;;; Note that if an @P or @L were ever followed by "lost" ordinary spaces, they
;;; would cause extra indentation on turnover lines.

;; Note that most of the above @ complex characters (those that specify
;; fixed-width spaces, alphabet shifts, and format or control directives or
;; delimiters thereof) are not yet implemented.



;;; `Currently-legal-character-following-\@' is true if character-following-\@ is
;;; a simple character following an @ that is currently handled.

(defmacro currently-legal-character-following-\@ (character-following-\@)
  `(case ,character-following-\@
     ((#\P #\L) t)))

;; Update as additional @ complex characters are implementedd!





;;;; Postscript Character Encodings



;;; `Postscript-character-encodings' is a compile time only data structure.
;;; It maps each Adobe character name into its position in the Adobe standard
;;; encoding vector and the Adobe ISO Latin encoding vector.  The contents of
;;; this table is taken directly from appendix E.5 of the Postscript Language
;;; Reference Manual Second Edition.

;;; This is not an alist.  For example there are two entries for acute, and
;;; since composite characters like Iacute's postscript program depend upon the
;;; position of their parts in the encoding vector this can't be ignored
;;; casually.

(defvar-for-macro postscript-character-encodings
  ;; Columns: (1) Adobe Name; (2) Standard Encoding; (3) Adobe's + ISO
  ;; 8859-1/Latin-1's "Latin Encoding"*
  ;;
  ;;   * Note: We have here in column (3), presumably from Adobe, code assignments where
  ;;   Latin-1 has none, i.e., in the 8-bit control code range [#x80..#x9F],
  ;;   namely the following 11 characters: acute, breve, caron, circumflex,
  ;;   dotaccent, dotlessi, grave, hungarumlaut, ogonek, ring, tilde
  '(("A"               #o101 #o101)
    ("AE"              #o341 #o306)
    ("Aacute"            NIL #o301)
    ("Acircumflex"       NIL #o302)
    ("Adieresis"         NIL #o304)
    ("Agrave"            NIL #o300)
    ("Aring"             NIL #o305)
    ("Atilde"            NIL #o303)
    ("B"               #o102 #o102)
    ("C"               #o103 #o103)
    ("Ccedilla"          NIL #o307)
    ("D"               #o104 #o104)
    ("E"               #o105 #o105)
    ("Eacute"            NIL #o311)
    ("Ecircumflex"       NIL #o312)
    ("Edieresis"         NIL #o313)
    ("Egrave"            NIL #o310)
    ("Eth"               NIL #o320)
    ("F"               #o106 #o106)
    ("G"               #o107 #o107)
    ("H"               #o110 #o110)
    ("I"               #o111 #o111)
    ("Iacute"            NIL #o315)
    ("Icircumflex"       NIL #o316)
    ("Idieresis"         NIL #o317)
    ("Igrave"            NIL #o314)
    ("J"               #o112 #o112)
    ("K"               #o113 #o113)
    ("L"               #o114 #o114)
    ("Lslash"          #o350   NIL)
    ("M"               #o115 #o115)
    ("N"               #o116 #o116)
    ("Ntilde"            NIL #o321)
    ("O"               #o117 #o117)
    ("OE"              #o352   NIL)
    ("Oacute"            NIL #o323)
    ("Ocircumflex"       NIL #o324)
    ("Odieresis"         NIL #o326)
    ("Ograve"            NIL #o322)

    ("Oslash"          #o351 #o330)
    ("Otilde"            NIL #o325)
    ("P"               #o120 #o120)
    ("Q"               #o121 #o121)
    ("R"               #o122 #o122)
    ("S"               #o123 #o123)
    ("Scaron"            NIL   NIL)
    ("T"               #o124 #o124)
    ("Thorn"             NIL #o336)
    ("U"               #o125 #o125)
    ("Uacute"            NIL #o332)
    ("Ucircumflex"       NIL #o333)
    ("Udieresis"         NIL #o334)
    ("Ugrave"            NIL #o331)
    ("V"               #o126 #o126)
    ("W"               #o127 #o127)
    ("X"               #o130 #o130)
    ("Y"               #o131 #o131)
    ("Yacute"            NIL #o335)
    ("Ydieresis"         NIL   NIL)
    ("Z"               #o132 #o132)
    ("Zcaron"            NIL   NIL)
    ("a"               #o141 #o141)
    ("aacute"            NIL #o341)
    ("acircumflex"       NIL #o342)
    ("acute"           #o302 #o222)
    ("acute"           #o302 #o264)
    ("adieresis"         NIL #o344)
    ("ae"              #o361 #o346)
    ("agrave"            NIL #o340)
    ("ampersand"       #o046 #o046)
    ("aring"             NIL #o345)
    ("asciicircum"     #o136 #o136)
    ("asciitilde"      #o176 #o176)
    ("asterisk"        #o052 #o052)
    ("at"              #o100 #o100)
    ("atilde"            NIL #o343)
    ("b"               #o142 #o142)
    ("backslash"       #o134 #o134)

    ("bar"             #o174 #o174)
    ("braceleft"       #o173 #o173)
    ("braceright"      #o175 #o175)
    ("bracketleft"     #o133 #o133)
    ("bracketright"    #o135 #o135)
    ("breve"           #o306 #o226)
    ("brokenbar"         NIL #o246)
    ("bullet"          #o267   NIL)
    ("c"               #o143 #o143)
    ("caron"           #o317 #o237)
    ("ccedilla"          NIL #o347)
    ("cedilla"         #o313 #o270)
    ("cent"            #o242 #o242)
    ("circumflex"      #o303 #o223)
    ("colon"           #o072 #o072)
    ("comma"           #o054 #o054)
    ("copyright"         NIL #o251)
    ("currency"        #o250 #o244)
    ("d"               #o144 #o144)
    ("dagger"          #o262   NIL)
    ("daggerdbl"       #o263   NIL)
    ("degree"            NIL #o260)
    ("dieresis"        #o310 #o250)
    ("divide"            NIL #o367)
    ("dollar"          #o044 #o044)
    ("dotaccent"       #o307 #o227)
    ("dotlessi"        #o365 #o220)
    ("e"               #o145 #o145)
    ("eacute"            NIL #o351)
    ("ecircumflex"       NIL #o352)
    ("edieresis"         NIL #o353)
    ("egrave"            NIL #o350)
    ("eight"           #o070 #o070)
    ("ellipsis"        #o274   NIL)
    ("emdash"          #o320   NIL)
    ("endash"          #o261   NIL)
    ("equal"           #o075 #o075)
    ("eth"               NIL #o360)
    ("exclam"          #o041 #o041)

    ("exclamdown"      #o241 #o241)
    ("f"               #o146 #o146)
    ("fi"              #o256   NIL)
    ("five"            #o065 #o065)
    ("fl"              #o257   NIL)
    ("florin"          #o246   NIL)
    ("four"            #o064 #o064)
    ("fraction"        #o244   NIL)
    ("g"               #o147 #o147)
    ("germandbls"      #o373 #o337)
    ("grave"           #o301 #o221)
    ("greater"         #o076 #o076)
    ("guillemotleft"   #o253 #o253)
    ("guillemotright"  #o273 #o273)
    ("guilsinglleft"   #o254   NIL)
    ("guilsinglright"  #o255   NIL)
    ("h"               #o150 #o150)
    ("hungarumlaut"    #o315 #o235)
    ("hyphen"          #o055 #o255)
    ("i"               #o151 #o151)
    ("iacute"            NIL #o355)
    ("icircumflex"       NIL #o356)
    ("idieresis"         NIL #o357)
    ("igrave"            NIL #o354)
    ("j"               #o152 #o152)
    ("k"               #o153 #o153)
    ("l"               #o154 #o154)
    ("less"            #o074 #o074)
    ("logicalnot"        NIL #o254)
    ("lslash"          #o370   NIL)
    ("m"               #o155 #o155)
    ("macron"          #o305 #o257)
    ("minus"             NIL #o055)
    ("mu"                NIL #o265)
    ("multiply"          NIL #o327)
    ("n"               #o156 #o156)
    ("nine"            #o071 #o071)
    ("ntilde"            NIL #o361)
    ("numbersign"      #o043 #o043)

    ("o"               #o157 #o157)
    ("oacute"            NIL #o363)
    ("ocircumflex"       NIL #o364)
    ("odieresis"         NIL #o366)
    ("oe"              #o372   NIL)
    ("ogonek"          #o316 #o236)
    ("ograve"            NIL #o362)
    ("one"             #o061 #o061)
    ("onehalf"           NIL #o275)
    ("onequarter"        NIL #o274)
    ("onesuperior"       NIL #o271)
    ("ordfeminine"     #o343 #o252)
    ("ordmasculine"    #o353 #o272)
    ("oslash"          #o371 #o370)
    ("otilde"            NIL #o365)
    ("p"               #o160 #o160)
    ("paragraph"       #o266 #o266)
    ("parenleft"       #o050 #o050)
    ("parenright"      #o051 #o051)
    ("percent"         #o045 #o045)
    ("period"          #o056 #o056)
    ("periodcentered"  #o264 #o267)
    ("perthousand"     #o275   NIL)
    ("plus"            #o053 #o053)
    ("plusminus"         NIL #o261)
    ("q"               #o161 #o161)
    ("question"        #o077 #o077)
    ("questiondown"    #o277 #o277)
    ("quotedbl"        #o042 #o042)
    ("quotedblbase"    #o271   NIL)
    ("quotedblleft"    #o252   NIL)
    ("quoteddblright"  #o272   NIL)
    ("quoteleft"       #o140 #o140)
    ("quoteright"      #o047 #o047)
    ("quotesinglebase" #o270   NIL)
    ("quotesingle"     #o251   NIL)
    ("r"               #o162 #o162)
    ("registered"        NIL #o256)
    ("ring"            #o312 #o232)

    ("s"               #o163 #o163)
    ("scaron"            NIL   NIL)
    ("section"         #o247 #o247)
    ("semicolon"       #o073 #o073)
    ("seven"           #o067 #o067)
    ("six"             #o066 #o066)
    ("slash"           #o057 #o057)
    ("space"           #o040 #o040)
    ("sterling"        #o243 #o243)
    ("t"               #o164 #o164)
    ("thorn"             NIL #o376)
    ("three"           #o063 #o063)
    ("threequarters"     NIL #o276)
    ("threesuperior"     NIL #o263)
    ("tilde"           #o304 #o224)
    ("trademark"         NIL   NIL)
    ("two"             #o062 #o062)
    ("twosuperior"       NIL #o262)
    ("u"               #o165 #o165)
    ("uacute"            NIL #o372)
    ("ucircumflex"       NIL #o373)
    ("udieresis"         NIL #o374)
    ("ugrave"            NIL #o371)
    ("underscore"      #o137 #o137)
    ("v"               #o166 #o166)
    ("w"               #o167 #o167)
    ("x"               #o170 #o170)
    ("y"               #o171 #o171)
    ("yacute"            NIL #o375)
    ("ydieresis"         NIL #o377)
    ("yen"             #o245 #o245)
    ("z"               #o172 #o172)
    ("zcaron"            NIL   NIL)
    ("zero"            #o060 #o060)))



;(defun check-postscript-encoding ()
;  (flet ((chk (x) (or (null x)
;                      (<= 0 x #o377))))
;    (loop for (name std iso) in postscript-character-encodings
;          do
;      (assert (and (stringp name)
;                   (chk std)
;                   (chk iso)
;                   (if (<= #\040 std #\0176)
;                       (= std iso)
;                       t))))
;    (loop as prev-name = "unknown" then name
;          as prev = -1 then std
;          for (name std nil) in (sort (remove nil postscript-character-encodings :key #'second) #'< :key #'second)
;          do (assert
;               (or (string-equal name "acute")
;                   (not (= std prev))) () "~S and ~S have same standard coding" prev-name name))
;    (loop as prev-name = "unknown" then name
;          as prev = -1 then iso
;          for (name nil iso)
;              in (sort (remove nil postscript-character-encodings :key #'third) #'< :key #'third)
;          do (assert
;               (or (string-equal name "acute")
;                   (not (= iso prev))) () "~S and ~S have same iso coding" prev-name name))
;    "Looks ok."))





;;;; Special Characters (~ Complex Characters)



;;; The ~ complex characters are as follows:
;;;
;;;    ~ followed by an alphanumeric simple character (a-z, A-Z, or 0-9) represents
;;;     a non-English roman alphabetic character
;;;
;;;    ~ followed by a non-alphanumeric simple character represents some special
;;;    character in a roman font



;;; Largest-non-kanji-font-character-code ...

(eval-when (:compile-toplevel :load-toplevel :execute)                        ; used in reader macro below
(defmacro largest-non-kanji-font-character-code ()
  256)                                        ; 171 => 256 (MHD 8/15/96)
)



;;; `Special-character-alist' is of the form
;;;
;;;    {(character-following-\~-in-gensym-character
;;;      roman-font-special-character-code
;;;      character-following-\~-in-lower-case-equivalent?
;;;      equivalent-unaccented-character?
;;;      character-or-characters-following-\~-for-input
;;;      adobe-name
;;;      BCIS-code? ; OBSOLETE! (MHD 8/26/96)
;;;      ISO-Latin1-name-if-different?)}.
;;;
;;; Note that (1) the Adobe/ISO-Latin1 names are case-sensitive symbols.  E.g.,
;;; |Aacute| and |aacute| are distinct from each other, and from the symbol
;;; AACUTE.  (2) The Adobe names are _mostly_ a superset of the ISO-Latin1
;;; names, distinct only for characters that aren't in ISO-Latin1. However, a
;;; few names are spelled differently, mostly those including the word
;;; "dieresis", which means the same as "umlaut".  ISO-Latin1 spells these as
;;; "diaeresis", as does the CMS, by the way.  Where these differ, the
;;; ISO-Latin1 name, instead of nil, appears as the final field.  (3) The
;;; symbols used here are kept in agreement with corresponding symbols used for
;;; characters that have keydefs.  However, those are ISO-Latin1 names.  Thus,
;;; e.g.,
;;;
;;;     (key-code-for-key-symbol
;;;       (or ISO-Latin1-name-if-different?
;;;           adobe-name))
;;;
;;; will map to a character's ISO-Latin1 keycode if that character's in
;;; ISO-Latin1.  (4) At present, keycodes for ISO-Latin1 characters happen to be
;;; the same as their corresponding ISO-Latin1 character codes, but that should
;;; not be relied upon, and need not be, except by one or two macros in F-KEYS.
;;; (5) Only a subset of ISO-Latin1 characters exist in the repertoire of the
;;; Gensym Character Set.

;;; Roman font special character codes can be changed without knowledge base
;;; compatibility problems, though fonts must be regenerated.  Note also that
;;; the input sequence for special characters need not match their gensym character
;;; representation, and therefore may be changed if that is deemed desirable.

(eval-when (:compile-toplevel :load-toplevel :execute)
  ;; Note: previously defparameter-excluding-gsi, parameter in development and
  ;; at macro expansion time. In theory, we should have defparameter-for-macro
  ;; in #-development and defparameter in #+development.  However, in practice
  ;; defparameter-for-macro provides us with the definitional equivalent of
  ;; defparameter at development time, at least using our current mode of
  ;; development, so we simply rely on the one definitional form for now,
  ;; leaving this code a bit simpler, hence hopefully findable via meta-point in
  ;; Emacs. (MHD 9/27/96)
(defparameter-for-macro special-character-alist
  (optimize-constant
  '(

     ;; The following 3 entries are here only to provide mappings from the gensym
     ;; characters to the corresponding roman font special character codes, and,
     ;; in the case of the tilde (~), to provide a mapping to the Bitstream BCID.

     (#\@  64 nil nil nil |at| 64)
     (#\~ 126 nil nil nil |asciitilde| 4744)  ; Bitstream's SWA fonts do not
     (#\\  92 nil nil nil |backslash| 92)     ;   contain a character with BCID
                                                          ;   126 ("Tilde Spacing"); however,
                                                          ;   they do contain BCID 4744
                                                          ;   ("Math Half Approximation").
                                                          ;   (MHD 6/21/93)

     ;; 0 is reserved for a missing-character "blob"

     (#\a  16 nil #\a (#\: #\") |adieresis| 394 |adiaeresis|) ; Ge. Sw. Finn.
     (#\A   1 #\a #\A (#\: #\") |Adieresis| 393 |Adiaeresis|)

     (#\b  17 nil #\a #\' |aacute| 400)        ; Sp. Port. Hung. Czech.
     (#\B   2 #\b #\A #\' |Aacute| 399)

     (#\c  18 nil #\c #\, |ccedilla| 184)        ; Fr. Port. Turk.
     (#\C   3 #\c #\C #\, |Ccedilla| 183)

     (#\d  19 nil #\a #\^ |acircumflex| 396)        ; Fr. Port. Turk.
     (#\D   4 #\d #\A #\^ |Acircumflex| 395)

     (#\e  20 nil #\e #\' |eacute| 390)        ; Fr. Sp. Port. Hung. Czech.
     (#\E   5 #\e #\E #\' |Eacute| 389)

     (#\f 131 nil #\e #\^ |ecircumflex| 386)        ; Port.
     (#\F 132 #\f #\E #\^ |Ecircumflex| 385)

     (#\g  21 nil #\e #\` |egrave| 388)        ; Fr. It. Port.
     (#\G   6 #\g #\E #\` |Egrave| 387)

     (#\h 137 nil #\i #\` |igrave| 376)        ; It. Port.
     (#\H 138 #\h #\I #\` |Igrave| 375)

     (#\i  22 nil #\i #\' |iacute| 378)        ; Sp. Port. Hung. Czech.
     (#\I   7 #\i #\I #\' |Iacute| 377)

     (#\j  23 nil #\i #\^ |icircumflex|  374)        ; Fr.
     (#\J   8 #\j #\I #\^ |Icircumflex| 373)

;     (#\l 155 nil #\l #\/ |lslash| 230)        ; Pol. -- maybe add later
;     (#\L 156 #\l #\L #\/ |Lslash| 231)

     (#\m 135 nil #\a #\` |agrave| 398)        ; Fr. It. Port.
     (#\M 136 #\m #\A #\` |Agrave| 397)

     (#\n  24 nil #\n #\~ |ntilde| 322)        ; Sp.
     (#\N   9 #\n #\N #\~ |Ntilde| 323)

     (#\o  25 nil #\o (#\: #\") |odieresis| 332)  ; Ge. Sw. Finn. Hung. Turk.
     (#\O  10 #\o #\O (#\: #\") |Odieresis| 333)

     (#\p  26 nil #\o #\' |oacute| 326)        ; Sp. Port. Hung. Czech. Pol.
     (#\P  11 #\p #\O #\' |Oacute| 327)

     (#\q  27 nil #\o #\^ |ocircumflex| 330)        ; Fr. Port.
     (#\Q  12 #\q #\O #\^ |Ocircumflex| 331)

     (#\r  28 nil #\a (#\o #\0) |aring| 151)            ; Sw. Norw. Dan.
     (#\R  13 #\r #\A (#\o #\0) |Aring| 147)

     (#\s  31 nil nil #\s |germandbls| 155)        ; Ge.

;     (#\S 157 nil nil #\i |dotlessi| 156)        ; Turk. -- maybe add when all Turk.
                                                        ;       --   or when diacritics can
                                                        ;       --   be separately overstruck

     (#\t 140 nil #\o #\/ |oslash| 153)        ; Norw. Dan.
     (#\T 130 #\t #\O #\/ |Oslash| 149)

     (#\u  29 nil #\u (#\: #\") |udieresis| 342 |udiaeresis|)  ; Ge. Fr. Span. Port. Hung. Turk.
     (#\U  14 #\u #\U (#\: #\") |Udieresis| 343 |Udiaeresis|)

     (#\v  30 nil #\u #\' |uacute| 336)        ; Sp. Port. Hung. Czech.
     (#\V  15 #\v #\U #\' |Uacute| 337)

     (#\w 128 nil #\o #\e |oe| 154)                ; Fr.        ; note: not in ISO 8859 at all!
     (#\W 129 #\w #\O #\e |OE| 150)

     (#\x 143 nil #\a #\e |ae| 152)                ; Norw. Dan.
     (#\X 142 #\x #\A #\e |AE| 148)

     (#\y 139 nil #\o #\` |ograve| 328)        ; It. Port.
     (#\Y 144 #\y #\O #\` |Ograve| 329)

     (#\z 145 nil #\u #\` |ugrave| 338)        ; It. Port.
     (#\Z 146 #\z #\U #\` |Ugrave| 339)

     (#\0 147 nil #\e (#\: #\") |edieresis| 384 |ediaeresis|) ; Fr.
     (#\1 148 #\0 #\E (#\: #\") |Edieresis| 383 |Ediaeresis|)

     (#\2 149 nil #\i (#\: #\") |idieresis| 372 |idiaeresis|) ; Fr. Port.
     (#\3 150 #\2 #\I (#\: #\") |Idieresis| 371 |Idiaeresis|)

     (#\4 151 nil #\a #\~ |atilde| 392)        ; Port.
     (#\5 152 #\4 #\A #\~ |Atilde| 391)

     (#\6 153 nil #\o #\~ |otilde| 334)        ; Port.
     (#\7 154 #\6 #\O #\~ |Otilde| 335)

     (#\8 133 nil #\u #\^ |ucircumflex| 340)        ; Fr. Turk.
     (#\9 134 #\8 #\U #\^ |Ucircumflex| 341)

     (#\% 158 nil #\c #\/ |cent| 132)
     (#\| 141 nil nil #\c |copyright| 564)        ; non-Postscript adobe name
     (#\: 159 nil nil #\t |trademark| 566)        ; non-Postscript adobe name
                                        ; note: not in ISO 8859 at all!
     (#\; 160 nil nil #\r |registered| 565)        ; non-Postscript adobe name
     (#\? 161 nil nil #\? |questiondown| 161)
     (#\! 162 nil nil #\! |exclamdown| 162)
;     (#\{ 163 nil nil #\{ |guilsinglleft| 157)   ; CMS doesn't ever say to use
;     (#\} 164 nil nil #\} |guilsinglright| 158)  ;    these for any lang.
     (#\< 165 nil nil #\< |guillemotleft| 159)
     (#\> 166 nil nil #\> |guillemotright| 160)
     (#\# 168 nil nil #\l |sterling| 131)
     (#\$ 169 nil nil #\y |yen|)        ; WHERE's BCIS for YEN !! (MHD 2/10/94)
     (#\& 170 nil nil #\f |florin| 133)        ; Florin Currency Symbol (Dutch)
                                        ;  == Unicode's LATIN SMALL LETTER SCRIPT F (U+0192)
                                        ;  == ISO 10646's LATIN SMALL LETTER F WITH HOOK
                                        ; note: not in ISO 8859 at all!
     (#\* 171 nil nil #\* |bullet| 575)

;     (#\_ 167 nil nil #\_ |emdash| 418)      ; series of hyphens will work

     ;; Remember to update largest-non-kanji-font-character-code above and
     ;; recompile BOXES and FONTS!

     ;; Roman font special character codes used so far: 1-31, 128-154,
     ;; 158-162, 165-166, 168-171.
     ;;
     ;; Simple characters following ~ not used so far: k K " ' ( ) + , - _ .
     ;; / = [ ] ^ ` S L l { } (though k was used for a while for copyright,
     ;; _ might want to be used for emdash, S (~i for input) might want
     ;; to be used for "dotless i", L and l might want to be used for
     ;; Slashed L and l, and { and } might want to be used for left and
     ;; right single guillemets).

     ;; NOTE: { and } had been used briefly for guilsinglleft and guilsinglright
     ;; but were removed, thinking they could not exist in any KB.  However, I
     ;; just discovered them in the regression test kbs,
     ;; ma:>regression-kb>no-stress.kb and ma:>regression-kb>stress.kb!
     ;; (MHD 2/10/92)

     )))
)

;; This was derived from the "Postscript Language Reference Manual", Appendix A.
;; However, entries that have comments in the margin saying "non-Postscript
;; adobe name" have the names used in the font files Gensym received from Adobe
;; instead whenever they differ, since the names here are used for manufacturing
;; Gensym fonts from Adobe font files.

;; This has been updated to include all characters of most important European
;; languages (3/27/90).  With the exception of the trademark (TM), bullet, and
;; oe-ligature characters, the current set of characters is a proper subset of
;; the ISO-Latin1 character set.  Note that every member of the ISO-8859-1
;; ("ISO-Latin1") character set is available in our Adobe font files, as well as
;; many additional characters.  For example, hungarumlaut (the Hungarian umlaut
;; diacritic), which is missing here, and which is not in ISO Latin1 but is in
;; another ISO standard, is available.  And Lslash (Polish slashed L), which is
;; neither here nor in any ISO standard, is available.  See also
;; postscript-character-encodings, below.

;; Good references are "The Chicago Manual of Style" (CMS) and the "ISO-Latin1"
;; character set, as well as appendix E.5 of the Postscript Language Reference
;; Manual, Second Edition.

;; Consider changing the mappings to give a more standard sort order when
;; text trings are sorted using string< or string-lessp.

;; This has been changed to keep a (case-sensitive) symbol as the "adobe name",
;; and to keep it in non-development versions.  I have reviewed callers.  Only
;; the loop below, and callers in PRINTING and PS-HEADER needed modification to
;; handle the change from string to symbol. (MHD 2/10/94)

;; Also moved the defvar for postscript-character-encodings above this code in
;; this module, since it is now used here (to map adobe names to ISO Latin1
;; encodings).  (MHD 2/10/94)








;; The following is here only to provide the mapping to the Bitstream BCID for
;; backquote (`), which is called quoteleft in PostScript. The rest of the
;; characters that need mapping are all characters in special-characters-alist,
;; q.v.

;; Bitstream uses BCID 137 ("Punctuation, Single Open Quote") instead of BCID 96
;; ("Grave Spacing") for backquote (Adobe's name: quoteleft (`)).

;; OBSOLETE! (MHD 8/26/96)
; (setf (map-to-bcis-character-code-if-any 96) 137)


;; Moved from above to pick up special-character-alist at macro expansion
;; time. (MHD 10/21/96)


(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro list-special-character-code-map-initial-elements-1 ()
  (if (and (gsi-no-utf-g-eliminable-p)
           (not (eval-feature :development)))
      nil
    `,`(loop with result = (make-list 96 :initial-element nil)
             with code-offset = 32
             for (character-following-\~-in-gensym-character
                   roman-font-special-character-code
                   nil                        ; character-following-\~-in-lower-case-equivalent?
                   nil                        ; equivalent-unaccented-character?
                   nil                        ; character-or-characters-following-\~-for-input
                   nil                        ; adobe-name
                   nil                        ; bcis-character-code?        ; OBSOLETE! (MHD 8/26/96)
                   nil                        ; ISO-Latin1-name-if-different?
                   )
                 in special-character-alist
             do (setf (nth (-f (char-code character-following-\~-in-gensym-character)
                               code-offset)
                           result)
                      roman-font-special-character-code)
             finally
               (return result))))
)

(defmacro list-special-character-code-map-initial-elements ()
  `(optimize-constant
     ',(list-special-character-code-map-initial-elements-1)))


;;; `Map-to-roman-font-special-character-code-if-any' returns either a roman font
;;; character code for the complex character consisting of ~ followed by simple-
;;; character-following-\~ or else nil to indicate that the complex character has not
;;; yet been defined.  A map-to-roman-font-special-character-code-if-any form can be
;;; used as a place form for defining these complex characters.

(defmacro map-to-roman-font-special-character-code-if-any
          (simple-character-following-\~)
  `(svref roman-font-special-character-code-map
          (-f (convert-simple-character-to-ascii ,simple-character-following-\~) 32)))

(defvar roman-font-special-character-code-map
        (make-array 96 :initial-contents ; a simple vector
                    (list-special-character-code-map-initial-elements)))





;;; `Map-iso-latin1-code-to-simple-character-following-\~-if-any' maps an ISO
;;; Latin1 code, an 8-bit superset of ASCII, into a simple character that
;;; follows ~ to make a gensym special character, if any, or nil.
;;;
;;; Note that the code must be in the range [0..255].
;;;
;;; The elements missing from the mapping (i.e., that map here to nil) are those
;;; that are not in the repertoire of Gensym Special Characters.
;;;
;;; Some of the ISO Latin1 characters do belong to the Gensym Character Set,
;;; generally, but just aren't Gensym Special Characters (i.e., "~ Complex
;;; Characters"), e.g., ~, \, and @.
;;;
;;; Some of the ISO Latin1 characters just aren't in the Gensym Character Set at
;;; present,

(defmacro map-iso-latin1-code-to-simple-character-following-\~-if-any
          (iso-latin1-character-code)        ; a simple vector
  `(svref iso-latin1-special-character-code-map ,iso-latin1-character-code))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro list-iso-latin1-special-character-code-map-initial-elements-1 ()
  (if (and (gsi-no-utf-g-eliminable-p)
           (not (eval-feature :development)))
      nil
    `,`(loop with result = (make-list 256 :initial-element nil)
             for (character-following-\~-in-gensym-character
                   nil                        ; roman-font-special-character-code
                   nil                        ; character-following-\~-in-lower-case-equivalent?
                   nil                        ; equivalent-unaccented-character?
                   nil                        ; character-or-characters-following-\~-for-input
                   adobe-name
                   nil                        ; bcis-character-code? ; OBSOLETE! (MHD 8/26/96)
                   nil                        ; ISO-Latin1-name-if-different?
                   )
                 in special-character-alist
             as key-code?
                = (third
                    (assoc (symbol-name adobe-name)
                           postscript-character-encodings ; a defvar-for-macro
                           :test 'string=))
             when key-code?
               do (setf (elt result key-code?)
                        character-following-\~-in-gensym-character)
             finally
               (return result))))
)

(defmacro list-iso-latin1-special-character-code-map-initial-elements ()
  `(optimize-constant
     ',(list-iso-latin1-special-character-code-map-initial-elements-1)))

(defvar-excluding-gsi-no-utf-g iso-latin1-special-character-code-map
  (make-array
    256
    :initial-contents
    (list-iso-latin1-special-character-code-map-initial-elements)))


(defvar-excluding-gsi-no-utf-g reverse-iso-latin1-special-character-code-map
  (make-array-with-nils 256))

(defmacro map-simple-character-following-\~-to-iso-latin1-code-if-any
    (simple-character-following-\~)
  `(svref reverse-iso-latin1-special-character-code-map
          (char-code ,simple-character-following-\~)))

;; setup reverse map:

(defmacro set-up-reverse-iso-latin1-map ()
  (unless (and (gsi-no-utf-g-eliminable-p)
               (not (eval-feature :development)))
    `(loop for i from 0 below 256
           as char? = (map-iso-latin1-code-to-simple-character-following-\~-if-any i)
           as code? = (if char? (char-code char?))
           when code?
             do (setf (svref reverse-iso-latin1-special-character-code-map code?)
                      i))))

(set-up-reverse-iso-latin1-map)

;; Make these maps more efficient in terms of space later! (I.e., use a byte
;; vector.)  (MHD 2/10/94)





;;;; Kanji Characters (\ Complex Characters)



;;; A `kanji character' is represented in G2 as a 16-bit `kanji code', as in JNIX
;;; (Japanese UNIX) on the SUN.  There must not be an actual character with kanji code
;;; 0, since that code is reserved for a missing-character "blob".

;;; A kanji character is represented in a text string as a complex character starting
;;; with a \ and followed by either 2 or 3 simple characters derived from the kanji
;;; code as follows:
;;;
;;;    (1) unless (ash kanji-code -13) = 1, the character whose ascii code is
;;;        (+ (ash kanji-code -13) 32);
;;;    (2) the character whose ascii code is (+ (floor (logand kanji-code #x1FFF) 95) 40);
;;;    (3) the character whose ascii code is (+ (mod (logand kanji-code #x1FFF) 95) 32).
;;;
;;; Examples:
;;;    #x2138 = 8504 is represented as "\\+;"
;;;    #x434c = 17228 is represented as "\\\"0t"
;;;
;;; When there are both upper and lower case versions of a kanji character, it may be
;;; assumed that they take the same number of simple characters to represent in a text
;;; string.

;;; JIS (Japanese Industrial Standard) character codes occupy the rectangular
;;; code range #x2121..#x747e.  The JIS codes in the range #x2121..#x397e can be
;;; represented in 3 bytes in the Gensym character set.  The other JIS codes
;;; i.e., those in the range #x4021..#x747e, require 4 bytes.

;;; Important Note: an invalid sequence can result in a too-large integer (>
;;; #xFFFF) or a negative integer.  Examples:
;;;
;;;    #x10048 = 65608 is represented as "\\'~~" (NOT A VALID CODE!)
;;;    #x-298 = -664 is represented as "\\ !!"   (NOT A VALID CODE!)
;;;
;;; In some situations, e.g., when dealing with user data, which may contain
;;; incorrectly produced sequences or even sequences never intended to be
;;; interpreted as \ complex chars, the interpreting must check for a result in
;;; the valid range 0..#xFFFF.  [Note: at present, we have made an incomplete
;;; investigation of what code should safeguard against the condition just
;;; described, though one function, get-utf-g-transcoder-code, has been revised.
;;; (MHD 5/25/00)]


;;; `Long-kanji-character-p' is true if the kanji character that has simple-character-
;;; following-\\ following the \ escape character is long, i.e., has a total of 3
;;; simple characters following the \ escape character.

(defmacro long-kanji-character-p (simple-character-following-\\)
  `(<f (convert-simple-character-to-ascii ,simple-character-following-\\) 40))



;;; `Read-kanji-code-from-gensym-string' returns a kanji code produced from a kanji
;;; character in gensym-string that starts at the position just before that specified by
;;; index-variable.  Index-variable is advanced past the kanji character.

(defmacro read-kanji-code-from-gensym-string
          (gensym-string index-variable gensym-string-is-simple?)
  (let ((string (gensym))
        (string-is-simple? (gensym)))
    `(let* ((,string ,gensym-string)
            (,string-is-simple? ,gensym-string-is-simple?)
            (ascii-code
              (convert-simple-character-to-ascii
                (read-simple-character-from-gensym-string
                  ,string ,index-variable ,string-is-simple?))))
       (declare (type fixnum ascii-code))
       (if (<f ascii-code 40)
           (+f (ashf ascii-code 13)
               (*f 95
                   (convert-simple-character-to-ascii
                     (read-simple-character-from-gensym-string
                       ,string ,index-variable ,string-is-simple?)))
               (convert-simple-character-to-ascii
                 (read-simple-character-from-gensym-string
                   ,string ,index-variable ,string-is-simple?))
               #.(- (+ (ash 32 13) (* 95 40) 32)))
           (+f (*f 95 ascii-code)
               (convert-simple-character-to-ascii
                 (read-simple-character-from-gensym-string
                   ,string ,index-variable ,string-is-simple?))
               #.(+ (ash 33 13) (- (+ (ash 32 13) (* 95 40) 32))))))))

;; Consider having this take gensym-string-length as an argument so that it can verify
;; that there are enough simple characters to read.

;; Consider having this expand into a call to a function with two values, to reduce the
;; size of the expansion.



;;; `Skip-past-kanji-character' advances index-variable past the kanji character in
;;; gensym-string that starts at the position just before that specified by index-variable.

(defmacro skip-past-kanji-character
          (gensym-string index-variable gensym-string-is-simple?)
  `(incff ,index-variable
          (if (long-kanji-character-p
                (gchar ,gensym-string ,index-variable ,gensym-string-is-simple?))
              3
              2)))



;;; `Compute-gensym-string-length-of-kanji-character' returns the number of simple
;;; characters required to represent the kanji character specified by kanji-code in
;;; a text string.

(defmacro compute-gensym-string-length-of-kanji-character (kanji-code)
  `(if (=f (ashf ,kanji-code -13) 1) 3 4))



;;; `Write-kanji-character-into-gensym-string' writes the kanji character specified by
;;; kanji-code into gensym-string starting at the position specified by index-variable.
;;; Index-variable is advanced past the written kanji character.

(defmacro write-kanji-character-into-gensym-string
          (kanji-code gensym-string index-variable gensym-string-is-simple?)
  (let ((code (gensym))
        (string (gensym))
        (string-is-simple? (gensym)))
    `(let ((,code ,kanji-code)
           (,string ,gensym-string)
           (,string-is-simple? ,gensym-string-is-simple?))
       (multiple-value-bind (quotient remainder)
           (floorf (logandf ,code #.(- (ash 1 13) 1)) 95)
         (write-simple-character-into-gensym-string
           #\\ ,string ,index-variable ,string-is-simple?)
         (if (not (=f (ashf ,code -13) 1))
             (write-simple-character-into-gensym-string
               (convert-simple-character-code-to-character (+f (ashf ,code -13) 32))
               ,string ,index-variable ,string-is-simple?))
         (write-simple-character-into-gensym-string
           (convert-simple-character-code-to-character (+f quotient 40))
           ,string ,index-variable ,string-is-simple?)
         (write-simple-character-into-gensym-string
           (convert-simple-character-code-to-character (+f remainder 32))
           ,string ,index-variable ,string-is-simple?)))))

;; Consider having this verify that gensym-string is long enough.

;; Consider eliminating the gensym-string-is-simple? argument, which would simplify this
;; at the cost of a bit of speed.

;; Consider defining this as a function, returning the updated index, especially
;; since it needs a companion macro to provide the index increment in advance, and
;; also because it is seldom used.



;;; `Set-octet-characters-from-gensym-character-code' sets octet?-var-1 to nil
;;; (if there are two octets) or the first of three octets.  It then sets
;;; octet-2-var and octet-3-var to those octets.
;;;
;;; This returns as its only result the final value of octet-1?-var, which says
;;; to write octet-1 if true, and otherwise not to write octet-1.
;;;
;;; (Note: a "character code", especially following a \ in a Gensym (UTF-G)
;;; character, is sometimes called a "kanji code" in Gensym software for
;;; historical reasons.)

(defmacro set-octets-from-gensym-character-code
    (code octet-1?-var octet-2-var octet-3-var)
  (let ((code-var '#:code))                        ; avoiding-variable-capture def'd later!
    `(let ((,code-var ,code))
       (multiple-value-bind (quotient remainder)
           (floorf (logandf ,code-var #.(- (ash 1 13) 1)) 95)
         (setf ,octet-2-var (+f quotient 40))
         (setf ,octet-3-var (+f remainder 32))
         (setf ,octet-1?-var
               ;; return value:
               (if (not (=f (ashf ,code-var -13) 1))
                   (+f (ashf ,code-var -13) 32)))))))


;;; `Twrite-kanji-character' writes the kanji character specified by kanji-code
;;; using twrite-char (q.v.).

(defmacro twrite-kanji-character (kanji-code)
  (let ((kanji-code-var '#:kanji-code))        ; avoiding-variable-capture def'd later!
    `(let ((,kanji-code-var ,kanji-code)
           octet-1? (octet-2 0) (octet-3 0))
       (declare (type fixnum octet-2 octet-3))
       (twrite-char #.(character-to-wide-character #\\))
       (when (set-octets-from-gensym-character-code
               ,kanji-code-var octet-1? octet-2 octet-3)
         (twrite-char (code-wide-character octet-1?)))
       (twrite-char (code-wide-character octet-2))
       (twrite-char (code-wide-character octet-3)))))

;; This cannot be used until after twrite-char is defined.



;;; The function `kstring' takes kanji-codes, a kanji code, or a list thereof, and returns
;;; a string encoding of them; it is defined for development-use only.

#+development
(defun kstring (kanji-codes)
  (with-output-to-string (*standard-output*)
    (loop for kanji-code? in (if (listp kanji-codes) kanji-codes '(nil))
          as kanji-code = (or kanji-code? kanji-codes)
          do (multiple-value-bind (quotient remainder)
                 (floorf (logandf kanji-code #.(- (ash 1 13) 1)) 95)
               (write-char #\\)
               (if (not (=f (ashf kanji-code -13) 1))
                   (write-char
                     (convert-simple-character-code-to-character (+f (ashf kanji-code -13) 32))))
               (write-char (convert-simple-character-code-to-character (+f quotient 40)))
               (write-char (convert-simple-character-code-to-character (+f remainder 32)))))))

;; New. (MHD 11/12/92)

;; An example of using the above to take binary character codes from
;; Jimmy Um and preparing them for the editor to use them.  Resulting
;; text strings end up in EDIT.  (MHD 1/6/92)

#+development
(defun convert-bytes-list-to-kanji-codes (bytes-list)
  (declare (eliminate-for-gsi-no-utf-g))
  (loop for (high-byte low-byte)
            on bytes-list
            by #'cddr
        collect
          (ksc-to-gensym-ksc
            (+f (ashf high-byte 8) low-byte))))

;#+development
;(defvar korean-edit-buttons
;        `((cancel
;            ,(kstring (convert-bytes-list-to-kanji-codes
;                        '(#2r1000011 #2r1101011 #2r0111100 #2r1010010))))
;          (undo
;            ,(kstring (convert-bytes-list-to-kanji-codes
;                        '(#2r0111010 #2r0111001 #2r0110001 #2r0111000))))
;          (redo
;            ,(kstring (convert-bytes-list-to-kanji-codes
;                        '(#2r1000000 #2r1100111 #2r0111101 #2r1000011
;                          #2r0110101 #2r0110101))))
;          (end
;            ,(kstring (convert-bytes-list-to-kanji-codes
;                        '(#2r0110011 #2r0100001))))
;          (update
;            ,(kstring (convert-bytes-list-to-kanji-codes
;                        '(#2r0111100 #2r1110110 #2r1000001 #2r0100100))))
;          (paste
;            ,(kstring (convert-bytes-list-to-kanji-codes
;                        '(#2r0111010 #2r1011001 #2r1000000 #2r1001100
;                          #2r0110001 #2r1100010))))
;          (english
;            ,(kstring (convert-bytes-list-to-kanji-codes
;                        '(#2r0111111 #2r0110101 #2r0111110 #2r1101110))))
;          (hangul
;            ,(kstring (convert-bytes-list-to-kanji-codes
;                        '(#2r1000111 #2r1010001 #2r0110001 #2r1011011))))))




;;; `Copy-kanji-character' ...

(defmacro copy-kanji-character
          (gensym-string gensym-string-is-simple? new-simple-gensym-string index-variable)
  (let ((string (gensym))
        (string-is-simple? (gensym))
        (new-string (gensym)))
    `(let* ((,string ,gensym-string)
            (,string-is-simple? ,gensym-string-is-simple?)
            (,new-string ,new-simple-gensym-string))
       (setf (schar ,new-string ,index-variable) #\\)
       (incff ,index-variable)
       (let ((character (gchar ,string ,index-variable ,string-is-simple?)))
         (setf (schar ,new-string ,index-variable) character)
         (incff ,index-variable)
         (setf (schar ,new-string ,index-variable)
               (gchar ,string ,index-variable ,string-is-simple?))
         (incff ,index-variable)
         (cond
           ((long-kanji-character-p character)
            (setf (schar ,new-string ,index-variable)
                  (gchar ,string ,index-variable ,string-is-simple?))
            (incff ,index-variable)))))))

;; This is used by copy-symbol-name et al.





;;;; Character Code Classification



;;; `hiragana-jis-code-p' is true if kanji-code represents a hiragana character
;;; in the JIS character set.  Note that this does not return true for the
;;; hiragana character in the KSC (Korean) character set.

(defun-substitution-macro hiragana-jis-code-p (kanji-code)
  (<=f #x2421 kanji-code #x2473))



;;; `katakana-jis-code-p' is true if kanji-code represents a katakana character
;;; in the JIS character set.  Note that this does not return true for the
;;; katakana character in the KSC (Korean) character set.

(defun-substitution-macro katakana-jis-code-p (kanji-code)
  (<=f #x2521 kanji-code #x2576))



;;; `Alphabetic-jis-code-p' is true if kanji-code represents an alphabetic
;;; character in JIS.

(defun-substitution-macro alphabetic-jis-code-p (kanji-code)
  (<=f #x2341 kanji-code #x237a))


;;; `Numeric-jis-code-p' is true if kanji-code represents a numeric character in
;;; JIS.

(defun-substitution-macro numeric-jis-code-p (kanji-code)
  (<=f #x2330 kanji-code #x2339))        ; digits; others?


(defun-substitution-macro numeric-ksc-code-p (kanji-code)
  (let ((start (ksc-to-gensym-ksc #x2330)))
    (<=f start kanji-code (+f start 10 -1))))


;;; `Numeric-kanji-code-p' is true if kanji-code represents a digit.

(defun-substitution-macro numeric-kanji-code-p (kanji-code)
  (or (numeric-jis-code-p kanji-code)
      (numeric-ksc-code-p kanji-code)))



;;; `Alphanumeric-kanji-code-p' is true if kanji-code represents a digit or
;;; an alphabetic character.

(defun-substitution-macro alphanumeric-jis-code-p (kanji-code)
  (or (<=f #x2330 kanji-code #x237A)                ; digits; others?
      ))



;;; `Upper-case-roman-jis-code-p' is true if kanji-code represents an upper-case
;;; roman alphabetic character.

(defun-substitution-macro upper-case-roman-jis-code-p (kanji-code)
  (<=f #x2341 kanji-code #x235a))



;;; `Upper-case-roman-ksc-code-p' is true if kanji-code represents an upper-case
;;; roman alphabetic character.

(defun-substitution-macro upper-case-roman-ksc-code-p (kanji-code)
  (<=f (ksc-to-gensym-ksc #x2341) kanji-code (ksc-to-gensym-ksc #x235a)))




(defun-substitution-macro upper-case-greek-jis-code-p (kanji-code)
  (<=f #x2621 kanji-code #x2638))

(defun-substitution-macro upper-case-greek-ksc-code-p (kanji-code)
  (<=f (ksc-to-gensym-ksc #x2541) kanji-code (ksc-to-gensym-ksc #x2558)))


(defun-substitution-macro upper-case-cyrillic-jis-code-p (kanji-code)
  (<=f #x2721 kanji-code #x2741))

(defun-substitution-macro upper-case-cyrillic-ksc-code-p (kanji-code)
  (<=f (ksc-to-gensym-ksc #x2c21) kanji-code (ksc-to-gensym-ksc #x2c41)))


(defconstant gensym-cyrillic-character-block-start #x2000)
;; here due to fwd. ref. prob. -mhd

(defun-substitution-macro upper-case-cyrillic-code-p (kanji-code)
  (let ((unicode-index (-f kanji-code gensym-cyrillic-character-block-start)))
    (or (<=f #x10 unicode-index #x2f)
        (<=f #x1 unicode-index #xc)
        (<=f #xe unicode-index #xf)
        (and (<=f #x60 unicode-index #x7f) ; This part of the block (which
             ; contains alternating upper and lower case strange characters)
             ; isn't yet implemented for Gensym, and is not defined for ISO
             ; 8859-8, but they're in ISO 10646, and are reserved for gensym.
             (evenp unicode-index)))))






;;; `Lower-case-roman-jis-code-p' is true if kanji-code represents an lower-case
;;; roman alphabetic character.

(defun-substitution-macro lower-case-roman-jis-code-p (kanji-code)
  (<=f #x2361 kanji-code #x237a))


;;; `Lower-case-roman-ksc-code-p' is true if kanji-code represents an lower-case
;;; roman alphabetic character.

(defun-substitution-macro lower-case-roman-ksc-code-p (kanji-code)
  (<=f (ksc-to-gensym-ksc #x2361) kanji-code (ksc-to-gensym-ksc #x237a)))


(defun-substitution-macro lower-case-greek-jis-code-p (kanji-code)
  (<=f #x2641 kanji-code #x2658))

(defun-substitution-macro lower-case-greek-ksc-code-p (kanji-code)
  (<=f (ksc-to-gensym-ksc #x2561) kanji-code (ksc-to-gensym-ksc #x2578)))


(defun-substitution-macro lower-case-cyrillic-jis-code-p (kanji-code)
  (<=f #x2751 kanji-code #x2771))

(defun-substitution-macro lower-case-cyrillic-ksc-code-p (kanji-code)
  (<=f (ksc-to-gensym-ksc #x2c51) kanji-code (ksc-to-gensym-ksc #x2c71)))

(defun-substitution-macro lower-case-cyrillic-code-p (kanji-code)
  (let ((unicode-index (-f kanji-code gensym-cyrillic-character-block-start)))
    (or (<=f #x30 unicode-index #x4f)
        (<=f #x51 unicode-index #x5c)
        (<=f #x5e unicode-index #x5f)
        (and (<=f #x60 unicode-index #x7f) ; This part of the block (which
                                        ; contains alternating upper and lower
                                        ; case strange characters) isn't yet
                                        ; implemented for Gensym, and is not
                                        ; defined for ISO 8859-8, but they're in
                                        ; ISO 10646, and are reserved for
                                        ; gensym.
             (oddp unicode-index)))))



;;; `Upper-case-kanji-code-p' is true if kanji-code represents an upper-case character.

;;; `Lower-case-kanji-code-p' is similar.

(defun-substitution-macro upper-case-kanji-code-p (kanji-code)
  (or (upper-case-roman-jis-code-p kanji-code)
      (upper-case-greek-jis-code-p kanji-code)
      (upper-case-cyrillic-jis-code-p kanji-code)

      (upper-case-roman-ksc-code-p kanji-code)
      (upper-case-greek-ksc-code-p kanji-code)
      (upper-case-cyrillic-jis-code-p kanji-code)

      (upper-case-cyrillic-code-p kanji-code)))


(defun-substitution-macro lower-case-kanji-code-p (kanji-code)
  (or (lower-case-roman-jis-code-p kanji-code)
      (lower-case-greek-jis-code-p kanji-code)
      (lower-case-cyrillic-jis-code-p kanji-code)

      (lower-case-roman-ksc-code-p kanji-code)
      (lower-case-greek-ksc-code-p kanji-code)
      (lower-case-cyrillic-ksc-code-p kanji-code)

      (lower-case-cyrillic-code-p kanji-code)))



;;; `Upcase-kanji-code' either converts kanji-code to the corresponding upper-case
;;; code, if any, or else just returns kanji-code.  Here, "kanji-code" means any
;;; Asian language code we now handle.  This currently handles Korean (Gensym KSC)
;;; codes and Japanese (Gensym JIS) codes.

;;; `Downcase-kanji-code' is similar.

(defun-substitution-macro upcase-kanji-code (kanji-code)
  (cond
    ((or (lower-case-roman-jis-code-p kanji-code) ; JIS Roman
         (lower-case-greek-jis-code-p kanji-code) ; JIS Greek
         (lower-case-roman-ksc-code-p kanji-code) ; KSC Roman
         (lower-case-greek-ksc-code-p kanji-code)) ; KSC Greek
     (-f kanji-code #x20))
    ((or (lower-case-cyrillic-jis-code-p kanji-code) ; JIS Cyrillic
         (lower-case-cyrillic-ksc-code-p kanji-code)) ; KSC Cyrillic
     (-f kanji-code #x30))
    ((lower-case-cyrillic-code-p kanji-code) ; ISO Latin5 Cyrillic
     (let* ((unicode-index (-f kanji-code gensym-cyrillic-character-block-start))
            (unicode-offset
              (cond ((<=f unicode-index #x4f)
                     (-f unicode-index #.(* 2 16))) ; over 2 columns
                    ((<=f unicode-index #x5f)
                     (-f unicode-index #.(* 5 16))) ; over 5 columns
                    (t (-f unicode-index 1)))))
       (+f gensym-cyrillic-character-block-start unicode-offset)))
    (t kanji-code)))

;; Handle the new Russian character set!!


(defun-substitution-macro downcase-kanji-code (kanji-code)
  (cond
    ((or (upper-case-roman-jis-code-p kanji-code) ; JIS Roman
         (upper-case-greek-jis-code-p kanji-code) ; JIS Greek
         (upper-case-roman-ksc-code-p kanji-code) ; KSC Roman
         (upper-case-greek-ksc-code-p kanji-code)) ; KSC Greek
     (+f kanji-code #x20))
    ((or (upper-case-cyrillic-jis-code-p kanji-code) ; JIS Cyrillic
         (upper-case-cyrillic-ksc-code-p kanji-code)) ; KSC Cyrillic
     (+f kanji-code #x30))
    ((upper-case-cyrillic-code-p kanji-code) ; ISO Latin5 Cyrillic
     (let* ((unicode-index (-f kanji-code gensym-cyrillic-character-block-start))
            (unicode-offset
              (cond ((<=f unicode-index #x0f)
                     (+f unicode-index #.(* 5 16))) ; over 5 columns
                    ((<=f unicode-index #x2f)
                     (+f unicode-index #.(* 2 16))) ; over 2 columns
                    (t (+f unicode-index 1)))))
       (+f gensym-cyrillic-character-block-start unicode-offset)))
    (t kanji-code)))



;; Write and use: "convert-roman-kanji-code-to-ascii",
;; "convert-ascii-alphabetic-code-to-kanji-code", etc!





;;;; JIS/Contiguous Enumeration Mapping



;;; Thanks to our consultant Carl Hoffman the code upon which this is originally
;;; based, and for many of the facts and coding ideas in this section, as well
;;; as documentation assistance.  I have updated this for JIS X 0208, year 1990;
;;; it had originally been for year '78.  (I refer to the "old way" below as
;;; "'78".)

;;; This code translates between JIS numeric character codes, a contiguous
;;; enumeration of the JIS characters starting at 0, and Lisp machine character
;;; objects.  NIL is returned if an attempt is made to translate an invalid JIS
;;; code.

;;; It is easier to understand the following code if you look at a JIS character
;;; chart.  A 1990 JIS chart (or an '78 chart for the figures in parens, where
;;; different).
;;;
;;; There are 6879 (6802 in '78) characters in the JIS character set.
;;; There are 3489 (3418 in '78) characters in the JIS Level 1 character set,
;;;   of which 2965 are JIS Level 1 Kanji, and 524 (453 in '78) of which are
;;;   non-Kanji.
;;; There are 3390 (3384 in '78) characters in the JIS Level 2 character set,
;;;   all of which are JIS Leval 2 Kanji.
;;;
;;; There are 524 (453 in '78) non-kanji characters.
;;; There are 6355 (6349 in '78) kanji characters.
;;; There are 68 rows of kanji characters.
;;;
;;; The Level 1 characters are organized in the following contiguous groups:
;;;   94 14
;;;   8 (not in '78)
;;;   7 (not in '78)
;;;   15 (not in '78)
;;;   8 (not in '78)
;;;   1 (not in '78)
;;;   10 26 26 83 86 24 24 33 33
;;;   32 (not in '78)
;;;   ((31 x 94) + 51)
;;; The Level 2 characters are organized in the following contiguous groups:
;;;   ((36 x 94)
;;;    + 6) (not in '78)

;; Mostly this has not been updated for '90, is still based on '78; only the
;; constant at the end giving the sum of characters is updated. (MHD 1/11/95)

#+development
(defvar-excluding-gsi-no-utf-g jis-contiguous-character-group-lengths
  '(94 14 8 7 15 8 1 10 26 26 83 86 24 24 33 33 32
    #.(+ (* 31 94) 51) #.(+ (* 36 94) 6)))

#+development
(defvar-excluding-gsi-no-utf-g jis-starting-offsets-for-character-groups
  ;;  '(0 94 108 116 123 138 146 147 157 183 209 292
  ;;    378 402 426 459 492 524 3489)
  (loop for start = 0 then (+ start length)
        as length in jis-contiguous-character-group-lengths
        collect start))

;;; High bytes for pre-jis rows with gaps:

(defconstant jis-symbols-1-high-byte		#x21)
(defconstant jis-symbols-2-high-byte		#x22)
(defconstant jis-roman-high-byte		#x23)
(defconstant jis-hiragana-high-byte		#x24)
(defconstant jis-katakana-high-byte		#x25)
(defconstant jis-greek-high-byte		#x26)
(defconstant jis-cyrillic-high-byte		#x27)
(defconstant jis-ruled-line-elements-high-byte	#x28)

(defconstant jis-level-1-kanji-high-byte	#x30)
(defconstant jis-level-2-kanji-high-byte	#x50)

(defconstant jis-undefined-byte			#x75) ; was #x74 in '78

(defconstant jis-symbols-90-1-offset		25) ; symbols 2 -- row 2; high byte = #x22
(defconstant jis-symbols-90-2-offset		41) ; none of these were in '78
(defconstant jis-symbols-90-3-offset		59)
(defconstant jis-symbols-90-4-offset		81)
(defconstant jis-symbols-90-5-offset		93)

(defconstant jis-numbers-offset			15) ; row 3; high byte = #x23
(defconstant jis-upper-case-roman-offset	32)
(defconstant jis-lower-case-roman-offset	64)

(defconstant jis-lower-case-greek-offset	32) ; row 6; high byte = #x26

(defconstant jis-lower-case-cyrillic-offset	48) ; row 7; high byte = #x27

(defconstant jis-symbols-1-start		0)
(defconstant jis-symbols-2-start		94)
(defconstant jis-symbols-90-1-start		108) ; not in '78
(defconstant jis-symbols-90-2-start		116) ; ditto.
(defconstant jis-symbols-90-3-start		123) ; ditto.
(defconstant jis-symbols-90-4-start		138) ; ditto.
(defconstant jis-symbols-90-5-start		146) ; ditto.
(defconstant jis-numbers-start			147)

;; in '78:
;(defconstant *jis-numbers-start*              108)
;(defconstant *jis-upper-case-roman-start*     118)
;(defconstant *jis-lower-case-roman-start*     144)
;(defconstant *jis-hiragana-start*             170)
;(defconstant *jis-katakana-start*             253)
;(defconstant *jis-upper-case-greek-start*     339)
;(defconstant *jis-lower-case-greek-start*     363)
;(defconstant *jis-upper-case-cyrillic-start*  387)
;(defconstant *jis-lower-case-cyrillic-start*  420)
;(defconstant *jis-level-1-kanji-start*        453)
;(defconstant *jis-level-2-kanji-start*        3418)

(defconstant jis-upper-case-roman-start		157)
(defconstant jis-lower-case-roman-start		183)
(defconstant jis-hiragana-start			209)
(defconstant jis-katakana-start			292)
(defconstant jis-upper-case-greek-start		378)
(defconstant jis-lower-case-greek-start		402)
(defconstant jis-upper-case-cyrillic-start	426)
(defconstant jis-lower-case-cyrillic-start	459)
(defconstant jis-ruled-line-elements-start	492) ; not in '78
(defconstant jis-level-1-kanji-start		524)
(defconstant jis-level-2-kanji-start		3489)

(defconstant jis-undefined-start		6879) ; i.e., the number of chars
                                                      ; 6802 in '78

;;; Contiguous codes range from 0 to 6801 base 10.
(defconstant jis-last-contiguous-code (1- jis-undefined-start))


;; Rows 2, 8, and 84 differ between '90 and '78. (MHD)

#+development
(defun jis-bytes-to-contiguous (high-byte low-byte)
  (declare (eliminate-for-gsi-no-utf-g))
  (let* ((offset
           (macrolet ((get-start (start-index)
                        `(nth ,(- start-index 1)
                              jis-starting-offsets-for-character-groups)))
             (cond
               ((=f high-byte jis-symbols-1-high-byte)
                (cond ((<= #x21 low-byte #x7e)
                       (get-start 1)         ; jis-symbols-1-start
                       )))
               ((=f high-byte jis-symbols-2-high-byte) ; row 2
                (cond ((<= #x21 low-byte #x2e)
                       (get-start 2)         ; jis-symbols-2-start
                       )
                      ;; rest are not in '78:
                      ((<= 58 low-byte 65)
                       (- (get-start 3) (- 58 #x21)))

                      ((<= 74 low-byte 80)
                       (- (get-start 4) (- 74 #x21)))

                      ((<= 92 low-byte 106)
                       (- (get-start 5) (- 92 #x21)))

                      ((<= 114 low-byte 121)
                       (- (get-start 6) (- 114 #x21)))

                      ((<= 126 low-byte 126)
                       (- (get-start 7) (- 126 #x21)))))

               ((=f high-byte jis-roman-high-byte)
                (cond ((<= #x30 low-byte #x39)
                       (- (get-start 8)      ; (- jis-numbers-start jis-numbers-offset)
                          (- #x30 #x21)))
                      ((<= #x41 low-byte #x5a)
                       (- (get-start 9)      ; (- jis-upper-case-roman-start jis-upper-case-roman-offset)
                          (- #x41 #x21)))
                      ((<= #x61 low-byte #x7a)
                       (- (get-start 10)     ; (- jis-lower-case-roman-start jis-lower-case-roman-offset)
                          (- #x61 #x21)))))
               ((=f high-byte jis-hiragana-high-byte)
                (cond ((<= #x21 low-byte #x73)
                       (get-start 11)        ; jis-hiragana-start
                       )))
               ((=f high-byte jis-katakana-high-byte)
                (cond ((<= #x21 low-byte #x76)
                       (get-start 12)        ; jis-katakana-start
                       )))
               ((=f high-byte jis-greek-high-byte)
                (cond ((<= #x21 low-byte #x38)
                       (get-start 13)        ; jis-upper-case-greek-start
                       )
                      ((<= #x41 low-byte #x58)
                       (- (get-start 14)     ; (- jis-lower-case-greek-start jis-lower-case-greek-offset)
                          (- #x41 #x21)))))
               ((=f high-byte jis-cyrillic-high-byte)
                (cond ((<= #x21 low-byte #x41)
                       (get-start 15)        ; jis-upper-case-cyrillic-start
                       )
                      ((<= #x51 low-byte #x71)
                       (- (get-start 16)     ; (- jis-lower-case-cyrillic-start jis-lower-case-cyrillic-offset)
                          (- #x51 #x21)))))
               ((=f high-byte jis-ruled-line-elements-high-byte) ; row 8 -- not in '78 at all
                (cond ((<= #x21 low-byte #x40)
                       (get-start 17))))
               (t
                (cond ((<= jis-level-1-kanji-high-byte
                           high-byte
                           (1-f jis-level-2-kanji-high-byte))
                       (if (if (= high-byte (1-f jis-level-2-kanji-high-byte))
                               (<= #x21 low-byte #x53)
                               (<= #x21 low-byte #x7e))
                           (+ (get-start 18) ; jis-level-1-kanji-start
                              (* 94 (- high-byte jis-level-1-kanji-high-byte)))))
                      ((<= jis-level-2-kanji-high-byte
                           high-byte
                           (1-f jis-undefined-byte))
                       (if (if (= high-byte (1-f jis-undefined-byte))
                               (<= #x21 low-byte #x26) ; extra 6 bytes in new last row not in '78
                               (<= #x21 low-byte #x7e))
                           (+ (get-start 19) ; jis-level-2-kanji-start
                              (* 94 (- high-byte jis-level-2-kanji-high-byte)))))))))))
    (when offset
      (+ offset (- low-byte #x21)))))


#+development
(defun jis-to-contiguous (code)
  (declare (eliminate-for-gsi-no-utf-g))
  (when (<= 0 code #.(- (ash 1 16) 1))
    (jis-bytes-to-contiguous
      (ashf code -8)
      (logandf code #xff))))



#+development
(defun contiguous-to-jis-bytes (code)
  (declare (eliminate-for-gsi-no-utf-g))
  (multiple-value-bind (high-byte low-byte)
      (cond ((< code jis-symbols-1-start)
             nil)
            ((< code jis-symbols-2-start)
             (values jis-symbols-1-high-byte
                     code))
            ;; not in '78:
            ((< code jis-symbols-90-1-start)
             (values jis-symbols-2-high-byte
                     (- code jis-symbols-2-start)))
            ((< code jis-symbols-90-2-start)
             (values jis-symbols-2-high-byte
                     (+ (- code jis-symbols-90-1-start)
                        jis-symbols-90-1-offset)))
            ((< code jis-symbols-90-3-start)
             (values jis-symbols-2-high-byte
                     (+ (- code jis-symbols-90-2-start)
                        jis-symbols-90-2-offset)))
            ((< code jis-symbols-90-4-start)
             (values jis-symbols-2-high-byte
                     (+ (- code jis-symbols-90-3-start)
                        jis-symbols-90-3-offset)))
            ((< code jis-symbols-90-5-start)
             (values jis-symbols-2-high-byte
                     (+ (- code jis-symbols-90-4-start)
                        jis-symbols-90-4-offset)))

            ((< code jis-numbers-start)
             (values jis-symbols-2-high-byte
                     (+ (- code jis-symbols-90-5-start)
                        jis-symbols-90-5-offset)))

            ((< code jis-upper-case-roman-start)
             (values jis-roman-high-byte
                     (+ (- code jis-numbers-start) jis-numbers-offset)))
            ((< code jis-lower-case-roman-start)
             (values jis-roman-high-byte
                     (+ (- code jis-upper-case-roman-start) jis-upper-case-roman-offset)))
            ((< code jis-hiragana-start)
             (values jis-roman-high-byte
                     (+ (- code jis-lower-case-roman-start) jis-lower-case-roman-offset)))
            ((< code jis-katakana-start)
             (values jis-hiragana-high-byte
                     (- code jis-hiragana-start)))
            ((< code jis-upper-case-greek-start)
             (values jis-katakana-high-byte
                     (- code jis-katakana-start)))
            ((< code jis-lower-case-greek-start)
             (values jis-greek-high-byte
                     (- code jis-upper-case-greek-start)))
            ((< code jis-upper-case-cyrillic-start)
             (values jis-greek-high-byte
                     (+ (- code jis-lower-case-greek-start) jis-lower-case-greek-offset)))
            ((< code jis-lower-case-cyrillic-start)
             (values jis-cyrillic-high-byte
                     (- code jis-upper-case-cyrillic-start)))
            ;; not in '78:
            ((< code jis-ruled-line-elements-start)
             (values jis-cyrillic-high-byte
                     (+ (- code jis-lower-case-cyrillic-start) jis-lower-case-cyrillic-offset)))
            ((< code jis-level-1-kanji-start)
             (values jis-ruled-line-elements-high-byte
                     (- code jis-ruled-line-elements-start)))
            ((< code jis-level-2-kanji-start)
             (multiple-value-bind (high low)
                 (floor (- code jis-level-1-kanji-start) 94)
               (values (+ jis-level-1-kanji-high-byte high) low)))
            ((< code jis-undefined-start)
             (multiple-value-bind (high low)
                 (floor (- code jis-level-2-kanji-start) 94)
               (values (+ jis-level-2-kanji-high-byte high) low))))
    (when high-byte
      (values high-byte (+ low-byte #x21)))))


#+development
(defmacro jis-bytes-to-jis (form)
  `(multiple-value-bind (high-byte low-byte)
       ,form
     (when high-byte
       (+f (ashf high-byte 8) low-byte))))


#+development
(defun contiguous-to-jis (code)
  (declare (eliminate-for-gsi-no-utf-g))
  (jis-bytes-to-jis (contiguous-to-jis-bytes code)))


#||
;;; This tests that the conversions are inverses of each other.
(defun test-jis-to-contiguous ()
  (loop for code from 0 below jis-undefined-start
        unless (eql code (gensym-jis-code-to-contiguous
                           (contiguous-to-gensym-jis-code code)))
          do (break "~a" code))
  (loop for code from 0 below (ash 1 16)
        for x = (gensym-jis-code-to-contiguous code)
        unless (or (not x) (= code (contiguous-to-gensym-jis-code x)))
          do (print code)))
||#





;;;; Gensym-JIS Characters




;;; A `Gensym-JIS' code is a character code corresponding to a JIS X0208
;;; character code.  The codes are identical.  (C.f., "Gensym-KSC" codes
;;; below.)  Gensym-JIS codes are represented in Gensym text as Kanji (\)
;;; complex characters.


;;; To abstract away from the detail that JIS and Gensym-JIS codes are identical,
;;; we provide the mapping functions below, which are identities.



;;; `Jis-to-gensym-jis' returns the Gensym-JIS code corresponding to  jis-code.
;;; This is a macro.

(defmacro jis-to-gensym-jis (jis-code)
  `,jis-code)


;;; `Gensym-jis-to-jis' returns the JIS code corresponding to gensym-jis-code.
;;; This is a macro.

(defmacro gensym-jis-to-jis (gensym-jis-code)
  `,gensym-jis-code)








;;; Benchmark-legal-gensym-jis-character-code-p ...

#+development
(defun benchmark-legal-gensym-jis-character-code-p ()
  (time
    (loop for i from 0 to 65000                        ; about .5 secs
          count (legal-gensym-jis-character-code-p i))))





;;; Legal-gensym-jis-character-code-p returns a non-nil value iff code is a legal
;;; JIS code.  This includes all of the new characters added in the 1983 revision.
;;; At present, only our KANJI16 font has these; our KANJI24 font lacks these.
;;; This also includes all 6 new character in ward 84.  At present, neither
;;; of our fonts have these, but the Bitstream fonts we're probably buying
;;; will have these.  According to Carl Hoffman's 1985 handbook, of the 1983
;;; revision, there were only four codes added to ward 84.  Don't know why
;;; Bitstream has 6.  We'll be getting in the JIS standard soon from ANSI,
;;; so I can check then.
;;;
;;; UPDATE: We got the JIS X 0208 Standard, year 1990, English translation,
;;; and it's 6.
;;;
;;; UPDATE: The following is informative for reference but not used in practice.
;;; The version in use is below, with correct name
;;; (legal-gensym-jis-character-code-p).

#+development
(defun old-legal-gensym-jis-character-code-p (code)
  (let ((high-byte (ashf code -8))
        (low-byte (logandf code 255)))

    (cond

      ((not (<=f #x21 low-byte #x7e))
       ;; if not in legal JIS range
       nil)

      ;; Below, we always assume that the low-byte is >= #x21.

      ;; the next two cases test JIS Level 1 Kanji
      ((<=f #x30 high-byte #x4e)
       'kanji)
      ((=f high-byte #x4f)
       (if (<=f low-byte #x53)
           'kanji))


      ;; the next two cases test JIS Level 2 Kanji
      ((<=f #x50 high-byte #x72)
       'kanji)
      ((=f high-byte #x73)
       'kanji)                                        ; happens to fill a whole row

      ((=f high-byte #x74)                        ; the new ward: 84 (#x74) -- not in
       (if (<=f #x21 low-byte #x26)                ;   our old KANJI16; has 4 or
           'kanji))                                ;   6 characters in it depending
                                                ;   on whom you ask! (?)
                                                ;
                                                ;   -- The JIS Standard JIS-X-0208
                                                ;   (1990) does assign 6 characters.




      ;; The rest are symbols, digits, Roman,
      ;; hiragana, katakana, Greek, Cyrillic,
      ;; and line-drawing characters.
      ;; (<=f #x21 high-byte #x27)

      ((=f high-byte #x21)                        ; symbols
       'symbol)                                        ; whole row
      ((=f high-byte #x22)                        ; more symbols
       (or (<=f low-byte #x2e)                        ;   ends are filled in,  but


           ;; the rest are not in our KANJI24 -- they are newer
           (<=f #x3a low-byte #x41)                ; ends are filled in,  but
           (<=f #x4a low-byte #x50)                ;   there's a gap in the middle
           (<=f #x5c low-byte #x6a)                ;   -- note that
           (<=f #x72 low-byte #x79)                ;   this was only up to
           (=f low-byte #x7e)))                        ;   #x2e in "old" JIS, but
                                                ;   has had many symbols added
                                                ;   to it in 1987 at the end


      ((=f high-byte #x23)                        ; romans
       (or (<=f #x30 low-byte #x39)                ;   digits
           (<=f #x41 low-byte #x5a)                ;   capital letters
           (<=f #x61 low-byte #x7a)))                ;   lowercase letters

      ((=f high-byte #x24)                        ; hiragana
       (<=f low-byte #x73))

      ((=f high-byte #x25)                        ; katakana
       (<=f low-byte #x76))

      ((=f high-byte #x26)                        ; Greek
       (or (<=f low-byte #x38)
           (<=f #x41 low-byte #x58)))

      ((=f high-byte #x27)                        ; cyrillic
       (or (<=f low-byte #x41)
           (<=f #x51 low-byte #x71)))

      ((=f high-byte #x28)                        ; line-drawing characters
       (<=f low-byte #x40)))))

;; A better name for this would be legal-gensym-jis-code-p!

;; This could be adapted to be both the predicate and the function to map
;; from JIS to a contiguous (from 0 to N) code assignment.  Later.

;; Consider using fixnum-case here for speed of testing the high-byte.

;; Consider using generate-binary-search-code to optimize the cond a bit,
;; which, since there are 13 independent cond clauses (after the original
;; one testing for range of low byte), would cut the number of tests down
;; from (/ 13 2) = 6.5 on the average to about (log 13) = 2.65, assuming
;; random distribution of inputs accross the code ranges.  (MHD 11/12/92)





;;; ... Low-byte-offset is non-zero for Gensym's KSC (Korean) code set at present.

(defmacro generate-codeset-membership-predicate
    (name gap-map low-byte-offset
          high-byte-min high-byte-max
          low-byte-min low-byte-max)
  `(defun ,(build-ab-symbol 'legal 'gensym (eval name) 'character-code-p) (code)
     (let ((high-byte (ashf code -8))
           (low-byte (-f (logandf code 255) ,low-byte-offset)))
       (cond
         ((and (<=f ,(eval high-byte-min) high-byte ,(eval high-byte-max))
               (<=f ,(eval low-byte-min) low-byte ,(eval low-byte-max)))
          (not                                        ; NOT in a gap?
            ,(generate-binary-search-code
               'high-byte
               (loop for (high-byte-with-gaps)
                         in (eval gap-map)
                     collect high-byte-with-gaps)
               (loop for (high-byte-with-gaps . gaps)
                         in (eval gap-map)
                     collect
                     `(if (=f ,high-byte-with-gaps high-byte)
                          ,(if (cdr gaps)        ; could always use an or, but this
                               `(or                ;   simplifies reading the expansion a bit
                                  . ,(loop for (min . max) in gaps
                                           collect
                                           `(<=f ,min low-byte ,max)))
                               `(<=f ,(car (car gaps))
                                     low-byte
                                     ,(cdr (car gaps))))))
               nil)))))))

(defmacro generate-codeset-contiguator
    (name gap-map low-byte-offset
          high-byte-min high-byte-max
          low-byte-min low-byte-max)
  (let ((total 0))
    `(defun ,(build-ab-symbol 'gensym (eval name) 'code-to-contiguous) (code)
       (declare (eliminate-for-gsi-no-utf-g))
       (let ((high-byte (ashf code -8))
             (low-byte (-f (logandf code 255) ,low-byte-offset)))
         (cond
           ((and (<=f ,(eval high-byte-min) high-byte ,(eval high-byte-max))
                 (<=f ,(eval low-byte-min) low-byte ,(eval low-byte-max)))
            (let* ((offset?
                     ,(generate-binary-search-code
                        'high-byte
                        (loop for (high-byte-with-gaps)
                                  in (eval gap-map)
                              collect high-byte-with-gaps)
                        (loop as accumulated-offset
                              = 0 then (-f accumulated-offset
                                           (loop for gap in gaps
                                                 sum (+ 1 (- (cdr gap) (car gap)))))
                              for (high-byte-with-gaps . gaps)
                                  in (eval gap-map)
                              collect
                              `(if (=f ,high-byte-with-gaps high-byte)
                                   (cond
                                     ,@(loop as this-row-offset = 0
                                                                then (- this-row-offset this-gap-length)
                                             for ((min . max) . more?) on gaps
                                             as this-gap-length = (+ (- max min) 1)
                                             collect
                                             `((<f low-byte ,min)
                                               ,(+ accumulated-offset
                                                   this-row-offset))
                                             collect
                                             `((<=f low-byte ,max)
                                               nil)
                                             when (null more?)
                                               collect `(t ,(+ accumulated-offset
                                                               (- this-row-offset
                                                                  this-gap-length)))))
                                   ,accumulated-offset)
                              do (setq total accumulated-offset)
                              )
                        total)))
              (when offset?
                (+f offset?
                    (*f (-f high-byte ,(eval high-byte-min))
                        ,(+ (- (eval low-byte-max) (eval low-byte-min)) 1))
                    (-f low-byte #x21))))))))))




;;; `Jis-gap-map' is an alist mapping rows that are between jis-high-byte-min
;;; and jis-high-byte-max that have gaps between jis-low-byte-min and
;;; jis-low-byte-max.
;;;
;;; The a-list is of the form
;;;
;;;     ( { (high-byte { (min-missing-low-byte . max-missing-low-byte) } ) } )
;;;
;;; Min and max are inclusivie limits.  The a-list is maintained strictly in
;;; order of increasing high-byte values, and the sublists are maintained
;;; strictly in order of increasing low-byte values.  Note that only rows that
;;; have gaps are present.
;;;
;;; This is defined only for use in expanding macros, namely for building
;;; the function that tests for legal predicate and (soon, at least) for
;;; mapping from actual JIS codes to a contiguous code space.

(defparameter-for-macro jis-gap-map
  '((#x22                                ; symbols
     (#x2f . #x39)
     (#x42 . #x49)
     (#x51 . #x5b)
     (#x6b . #x71)
     (#x7a . #x7d))
    (#x23                                ; romans
     (#x21 . #x2f)
     (#x3a . #x40)
     (#x5b . #x60)
     (#x7b . #x7e))
    (#x24                                ; hiragana
     (#x74 . #x7e))
    (#x25                                ; katakana
     (#x77 . #x7e))
    (#x26                                ; greek
     (#x39 . #x40)
     (#x59 . #x7e))
    (#x27
     (#x42 . #x50)
     (#x72 . #x7e))
    (#x28                                ; line-drawing characters
     (#x41 . #x7e))

    ;; 7 entire rows missing before kanji starts:
    (#x29 (#x21 . #x7e)) (#x2a (#x21 . #x7e)) (#x2b (#x21 . #x7e))
    (#x2c (#x21 . #x7e)) (#x2d (#x21 . #x7e)) (#x2e (#x21 . #x7e))
    (#x2f (#x21 . #x7e))

    ;; space at end of last row of JIS-1
    (#x4f (#x54 . #x7e))

    ;; space at end of the last row of JIS-2
    (#x74 (#x27 . #x7e))
    ))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant jis-high-byte-min #x21)
(defconstant jis-high-byte-max #x74)

(defconstant jis-low-byte-min #x21)
(defconstant jis-low-byte-max #x7e)
)

;;; `JIS-low-byte-offset' is the offset to be added to the low byte of
;;; a Gensym-JIS code from its original value as a KSC code.

(defconstant JIS-low-byte-offset 0)

;;; `Gensym-jis-code-to-contiguous' maps character-code, a fixnum, to a contigous
;;; code that is the sum of the legal JIS codes that preceeded this code in the JIS
;;; code map.  If this is not a legal code, NIL is returned.
;;;
;;; `Contiguous-to-gensym-jis-code' maps in the reverse direction.

(generate-codeset-contiguator 'jis
                              jis-gap-map
                              JIS-low-byte-offset
                              jis-high-byte-min jis-high-byte-max
                              jis-low-byte-min jis-low-byte-max)

;; This is much faster than jis-to-contiguous, defined above.  There is at present
;; no difference between gensym-jis and jis (c.f., ksc).  We should not really keep
;; both indefinitely, but it doesn't harm anything for now.  (MHD 1/12/95)


#+development
(defun contiguous-to-gensym-jis-code (code)
  (declare (eliminate-for-gsi-no-utf-g))
  (jis-to-gensym-jis (contiguous-to-jis code)))


;;; `Legal-gensym-jis-character-code-p' is true if character-code, a fixnum, is
;;; a legal Gensym-JIS code.  To map between a Gensym-JIS code and a JIS code,
;;; use either jis-to-gensym-jis or gensym-jis-to-jis.

(defmacro generate-legal-gensym-jis-character-code-p ()
  `(defun legal-gensym-jis-character-code-p (gensym-jis-code)
     (declare (eliminate-for-gsi-no-utf-g))
     (let ((high-byte (ashf gensym-jis-code -8))
           (low-byte
             (-f (logandf gensym-jis-code 255)  ; converts from Gensym-JIS to JIS code
                 JIS-low-byte-offset)))
       (cond
         ((and (<=f jis-high-byte-min high-byte jis-high-byte-max)
               (<=f jis-low-byte-min low-byte jis-low-byte-max))
          (not                                  ; NOT in a gap?
            ,(generate-binary-search-code
               'high-byte
               (loop for (high-byte-with-gaps)
                         in jis-gap-map
                     collect high-byte-with-gaps)
               (loop for (high-byte-with-gaps . gaps)
                         in jis-gap-map
                     collect
                     `(if (=f ,high-byte-with-gaps high-byte)
                          ,(if (cdr gaps)     ; could always use an or, but this
                               `(or           ;   simplifies reading the expansion a bit
                                  . ,(loop for (min . max) in gaps
                                           collect
                                           `(<=f ,min low-byte ,max)))
                               `(<=f ,(car (car gaps))
                                     low-byte
                                     ,(cdr (car gaps))))))
               nil)))))))

(generate-legal-gensym-jis-character-code-p)



#+development
(progn



(defun compute-number-of-jis-codes-naively-from-old-legality-predicate ()
  (loop for i from 0 below (ash 1 16)
        when (old-legal-gensym-jis-character-code-p i)
          count t))

(defun diff-old-and-new-jis-predicates ()
  (loop for i from 0 below (ash 1 16)
        when (not (eq (if (old-legal-gensym-jis-character-code-p i) t)
                      (if (legal-gensym-jis-character-code-p i) t)))
          do (format t "~%~X" i)
            and collect i))

(defun compute-number-of-jis-codes-naively-from-legality-predicate ()
  (loop for i from 0 below (ash 1 16)
        when (legal-gensym-jis-character-code-p i)
          count t))

(defun compute-number-of-jis-codes-naively-from-contiguator ()
  (loop for i from 0 below (ash 1 16)
        when (jis-to-contiguous i)
          count t))


(defun compute-number-of-jis-codes-from-standard ()
  (+ 147                                ; special character
     10                                        ; numerals
     52                                        ; roman letters
     83                                        ; heragana
     86                                        ; katakana
     48                                        ; greek
     66                                        ; russian
     6355                                ; kanji
     32                                        ; ruled line elements
     ))                                        ; (info. from JIS X 0208, p. 3)


(defvar number-of-jis-codes
  6879)

(progn
  (assert (= (compute-number-of-jis-codes-from-standard)
             number-of-jis-codes))
  (assert (= (compute-number-of-jis-codes-naively-from-contiguator)
             number-of-jis-codes))
  (assert (= (compute-number-of-jis-codes-naively-from-old-legality-predicate)
             number-of-jis-codes))
  (assert (= (compute-number-of-jis-codes-naively-from-legality-predicate)
             number-of-jis-codes)))


)



;;; The macro `jis-unicode-p' is true if unicode corresponds to a JIS-X-0208
;;; character code.

(def-substitution-macro jis-unicode-p (unicode)
  (map-unicode-to-JIS-X-0208 unicode))





;;;; JIS - JIS Kuten Conversion


;;; In addition to the JIS representation for JIS codes, also known as "straight
;;; JIS Hex codes", there is an alternative representation that users see, in
;;; dictionaries, character set tables, type spec sheets, and the like, called
;;; `JIS Kuten'.  This is also known, e.g., in the English translation of the
;;; JIS character set standard document, as `row/column' designation.  Note that
;;; a "row" is also often referred to as a `ward' by the JIS.

;;; In this representation, a JIS code appears at the surface as a 4-digit
;;; decimal code, of the form
;;;
;;;       DD  DD
;;;         1   2
;;;
;;; To convert this to its corresponding JIS hex code, take each of the two
;;; pairs of digits as decimal numbers, add 32 to each, then convert each
;;; separately to hex, and lay them back down next to eachother, i.e.,
;;;
;;;       (format nil "~x~x" (+ DD  32) (+ DD  32))
;;;                               1          2
;;;
;;; For example, the JIS Kuten code 401 (or 0401) is expressed as a JIS Hex
;;; code as
;;;
;;;             (format nil "~x~x" (+ 4 32) (+ 1 32))
;;;
;;;             ==>  2421
;;;
;;; Other examples:
;;;
;;;   JIS Kuten 7102 => JIS Hex 6722
;;;   JIS Kuten 4068 => JIS Hex 4864
;;;   JIS Kuten 3546 => JIS Hex 434e
;;;   JIS Kuten 2604 => JIS Hex 3a24

;;; Here are two routines for converting Kuten to Hex and back:  Kuten-to-hex
;;; and Hex-to-Kuten.

#+development
(progn

(defun kuten-to-hex (kuten-code)
  (declare (eliminate-for-gsi-no-utf-g))
  (multiple-value-bind (floor remainder)
      (floorf kuten-code 100)
    (+ (ash (+f floor 32) 8)
       (+f remainder 32))))

;; Try with (format nil "~x" (kuten-to-hex 2604)) => "3A24".



(defun hex-to-kuten (hex-code)
  (declare (eliminate-for-gsi-no-utf-g))
  (+ (*f 100 (-f (ashf hex-code -8) 32))
     (- (logandf hex-code #xff) 32)))

;; Try with (hex-to-kuten #x3a24) => 2604.

) ; end #+development (progn  ....)





;;;; Shift JIS


;;; Shift-JIS is a variation on JIS that is widely used in the PC world, but is
;;; also gaining some strength in the workstation world, due to its use in the
;;; HP Unix environment, as well as the potential ascendency of MS Windows and
;;; Windows NT, which use Shift-JIS.

;;; What is Shift-JIS?  It's a way to encode JIS alongside straight ASCII codes.
;;; With regular JIS, an ASCII file has to be converted to JIS, thus costing
;;; double for each byte, as well as the conversion cost.  But in a Shift-JIS
;;; environment, a straight ASCII file looks the same as it would in an ASCII
;;; environment, thus saving half the bytes as well as the entire conversion
;;; cost.

;;; The first 128 character codes are shared by Shift-JIS and ASCII.  ...

;;; We use jis-to-shift-jis mapping in order to use Bitstream Speedo Kanji
;;; Fonts.  Other than that, we do not currently support Shift JIS, but it may
;;; be important in the future, as we intend to interrelate with a number of
;;; existing standards.

#+development
(defun shift-jis-to-jis (code)
  (declare (eliminate-for-gsi-no-utf-g))
  (let (upper lower)
    (if (> code #xa000) (setq code (- code (- #xe000 #xa000))))
    (setq code (- code #x8100))
    (setq upper (ash (ash code -8) 1))
    (setq lower (logand code #xff))
    (cond
      ((> lower #x9e)
       (incf upper)
       (setq lower (- lower #x9f))
       (setq lower (+ lower #x21)))
      (t
       (when (> lower #x7e)
         (decf lower))
       (setq lower (- lower #x40))
       (setq lower (+ lower #x21))))
    (+ #x2100 (ash upper 8) lower)
    ))

;; The above is an untested sample conversion routine: (MHD 11/9/92)



;;; `Jis-to-shift-jis' maps a straight JIS code to "shift JIS".  This is used
;;; currently for mapping to Japanese outline font indices.

(defun jis-to-shift-jis (code)
  (declare (eliminate-for-gsi-no-utf-g)
	   (type fixnum code))
  (let* ((j1 (ashf (logandf code #xff00) -8))
         (j2 (logandf code #x00ff))
         (sj1 (-f j1 #x21))
         (plus
           (if (>f j1 #x5e)
               #xc100
               #x8100))
         (flag? nil))
    (declare (type fixnum j1 j2 sj1 plus))
    (when (oddp (the fixnum sj1))
      (decff sj1)
      (setq flag? t))
    (let ((sj (+f (ashf (halff sj1) 8) plus)))
      (declare (type fixnum sj))
      (cond
        (flag?
         (incf sj (+f j2 #x7e)))
        ((<=f j2 #x5f)
         (incf sj (+f j2 #x1f)))
        ((>=f j2 #x60)
         (incf sj (+f j2 #x20))))
      sj)))

;; The above is adapted from some C code in Bitstream's 4-in-1 Kanji
;; package, specifically JIS2SJ pre_proc.c. (MHD 8/17/93)





;;;; Gensym-KSC Characters



;;; Gensym-JIS codes are represented in Gensym text as Kanji (\) complex
;;; characters.

;;; A `Gensym-KSC code' is a 16-bit code that represents a `KSC code', a
;;; standard Korean KS C 5601 character code.  The codes can be mapped into one
;;; another; the design for how that is done is described below.




;;; KS C 5601 codes, like JIS X0208 codes, are allocated in the rectangular code
;;; area starting from #x21 to #x7d (JIS only goes up to #x74) for the higher
;;; byte, and from #x21 to #x7e for the lower byte.  (#x2121..#x7d7e)
;;;
;;; This poses the problem that Hangul codes would overlap JIS codes if
;;; converted straightforwardly into our \ (Kanji) Gensym complex character
;;; encoding.
;;;
;;; First, consider that the \ complex characters are one byte more efficient
;;; for character codes in the range [2^13..2^14-1], or in the #x20 to #x3f
;;; high-byte range, due to the details of our coding scheme.
;;;
;;; Second, the limited area for the low byte of the JIS code is great for
;;; keeping each byte representable with 7-bit ascii characters, but it wastes a
;;; lot of number space that can be easily represented.  We are under no such
;;; limitation: we do want to keep to 7-bit ascii characters, but the \ complex
;;; character representation already guarantees that for an arbitrary character
;;; code (in the legal range).

;;; In other words, the low byte occupies ((#x7e - #x21) + 1) = 94 places out of
;;; total of 256 possible places in the byte.

;;; Thus, we could leave the high bytes as they are, and simply shift the low
;;; bytes over by 94 and still have plenty of room.  This is what is done below,
;;; thus mapping the KS code rectangle from #x2121..#x7d7e to #x217f..#x21dd.

;;; The KS codes in the range #x2121..#x397e can be represented in 3 bytes in
;;; the Gensym character set.  The other KS codes i.e., those in the range
;;; #x4021..#x7d7e, require 4 bytes.

;;; Gensym-KSC codes are used for storing characters in our fonts in memory (but
;;; not on disk), for representing characters in our strings, and for writing
;;; characters out to disk or across the network.  Legal-hangul-
;;; character-code-p is in terms of gensym-ksc codes, not ksc codes.

;;; KSC codes are used for inputting KSC hex codes in the editor (via
;;; control-\), and for storing characters in the Hangul font files, hangul16
;;; and hangul24.  Later, we may added some capabilities to translate between
;;; gensym-ksc and ksc codes.


;;; The variable `number-of-ksc-codes' gives the number of KSC codes there are.

(defvar number-of-ksc-codes
  8224)



;;; `KSC-low-byte-offset' is the offset to be added to the low byte of
;;; a Gensym-KSC code from its original value as a KSC code.

(defconstant KSC-low-byte-offset #.(+ (- #x7e #x21) 1))        ; = 94



;;; The function ksc-to-gensym-ksc takes a KSC code converts it into a Gensym-KSC
;;; code.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun ksc-to-gensym-ksc (ksc-code)
  (let ((high-byte (ashf ksc-code -8))
        (low-byte (logandf ksc-code 255)))
    (+f (ashf high-byte 8)
        (+f KSC-low-byte-offset low-byte))))
)





;;; Ks2-bytes-to-ksc5601 converts a 2-byte "KS2" code to a "KSC5601" code.
;;;
;;; (The "KS2" code is often/usually seen in tables of KSC5601 codes.  Specifically,
;;; it is in the tables supplied by Jimmy Um in is "KS2" document, which gives the
;;; whole KSC5601 table.  It is also used in the tables given in a xerox hardcopy by
;;; some Korean visitors.  It is also used in the DK public-domain Hangul automaton
;;; software, which we have incorporated into G2.
;;;
;;; The "KSC5601" codes are used by the font supplied with X11 R5, a public domain
;;; Korean font, which we have incorporated into G2.)

;;; `Convert-2-byte-to-gensym-ksc5601' is similar, but goes directly into the Gensym-
;;; internal variation of the KSC character code set.

(defun ks2-bytes-to-ksc5601 (ks2-high-byte ks2-low-byte)
  (declare (eliminate-for-gsi-no-utf-g))
  (+f (ashf (+f ks2-high-byte #.(- #x21 #xa1)) 8)
      (+f ks2-low-byte #.(- #x21 #xa1))))

(defun convert-2-byte-to-gensym-ksc5601 (ks2-high-byte-character ks2-low-byte-character)
  (declare (eliminate-for-gsi-no-utf-g))
  (ksc-to-gensym-ksc
   (ks2-bytes-to-ksc5601
    (char-code ks2-high-byte-character)
    (char-code ks2-low-byte-character))))

;; The terminology needs review.  I'm not sure of what I'm talking about because
;; there is no English documentation, and I'm short on communications with those
;; bearing the "oral tradition".  (MHD 1/4/93)



;;; The function gensym-ksc-to-ksc takes a Gensym-KSC code converts it into a KSC
;;; code.

(defun gensym-ksc-to-ksc (gensym-ksc-code)
  (declare (eliminate-for-gsi-no-utf-g))
  (let ((high-byte (ashf gensym-ksc-code -8))
        (low-byte (logandf gensym-ksc-code 255)))
    (+f (ashf high-byte 8)
        (-f low-byte KSC-low-byte-offset))))

;; With this scheme, about 43% of KSC codes can be represented in 2 characters
;; following the \.  For JIS, it's about 41%.  This is not all that meaningful
;; since it does not take into account frequency; for example, many of the
;; lower rows are symbols, alphabetic characters, and other non-Kanji characters,
;; which may not be frequently used; on the other hand, the Hiragana & Katakana
;; characters are here.  So, I just don't know.  (MHD 11/12/92)




;;; Ksc-gap-map is an a-list of the rows in the KSC code space that have
;;; gaps.

(defvar-for-macro
  ksc-gap-map
  '((34 (102 . 126))
    (37 (43 . 47) (58 . 64) (89 . 96) (121 . 126))
    (38 (101 . 126))
    (39 (112 . 126))
    (40 (37 . 37) (39 . 39) (48 . 48))
    (42 (116 . 126))
    (43 (119 . 126))
    (44 (66 . 80) (114 . 126))
    (45 (33 . 126))
    (46 (33 . 126))
    (47 (33 . 126))
    (73 (33 . 126))
    (#x7e (33 . 33))))                        ; dummy terminator! works around bug in
                                        ;   contiguator-generator macro!
                                        ;   (MHD 1/19/95)



(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant ksc-high-byte-min #x21)
(defconstant ksc-high-byte-max #x7d)

(defconstant ksc-low-byte-min #x21)
(defconstant ksc-low-byte-max #x7e)
)

(defconstant ksc-symbols-1-start 0)
(defconstant ksc-hangul-start 986)
(defconstant ksc-hanja-start 3336)
(defconstant ksc-undefined-start 8224)
(defconstant ksc-last-contiguous-code (1- ksc-undefined-start))


(defvar-excluding-gsi-no-utf-g ksc-contiguous-character-group-lengths
  '(94                                        ; row 1
    69                                        ; row 2
    94                                        ; row 3
    94                                        ; row 4
    10 10 24 24                                ; row 5 (greek)
    68                                        ; row 6
    79                                        ; row 7
    4 1 8 78                                ; row 8
    94                                        ; row 9
    83                                        ; row 10 (hiragana)
    86                                        ; row 11 (katakana)
    33 33                                ; row 12 (cyrillic)
    #.(* 25 94)                                ; rows 16-40 (hangul)
    #.(* 52 94)                                ; rows 42-93 (hanja*)
    ))

;; * "Hanja" is just the Korean pronunciation of Kanji, which just means
;; "chinese characters".  It is sometimes written "Hancha".


#+development
(defvar-excluding-gsi-no-utf-g ksc-starting-offsets-for-character-groups
  ;;  (0 94 163 257 351 361 371 395 419 487 566 570 571 579
  ;;   657 751 834 920 953 986 3336)
  (loop for start = 0 then (+ start length)
        as length in ksc-contiguous-character-group-lengths
        collect start))


#+development
(defun contiguous-to-ksc-bytes (code)
  (declare ; (values high-byte low-byte)
           (fixnum code)
           (eliminate-for-gsi-no-utf-g))
  (multiple-value-bind (high-byte low-byte)
      (cond ((< code 0) nil)
            ((< code 94) (values #x21 code))
            ((< code 163) (values #x22 (- code 94)))
            ((< code 257) (values #x23 (- code 163)))
            ((< code 351) (values #x24 (- code 257)))
            ((< code 361) (values #x25 (+ (- code 351) 0)))
            ((< code 371) (values #x25 (+ (- code 361) 15)))
            ((< code 395) (values #x25 (+ (- code 371) 32)))
            ((< code 419) (values #x25 (+ (- code 395) 64)))
            ((< code 487) (values #x26 (- code 419)))
            ((< code 566) (values #x27 (- code 487)))
            ((< code 570) (values #x28 (+ (- code 566) 0)))
            ((< code 571) (values #x28 (+ (- code 570) 5)))
            ((< code 579) (values #x28 (+ (- code 571) 7)))
            ((< code 657) (values #x28 (+ (- code 579) 16)))
            ((< code 751) (values #x29 (- code 657)))
            ((< code 834) (values #x2a (- code 751)))
            ((< code 920) (values #x2b (- code 834)))
            ((< code 953) (values #x2c (+ (- code 920) 0)))
            ((< code 986) (values #x2c (+ (- code 953) 48)))
            ((< code 3336)
             (multiple-value-bind (high low)
                 (floor (- code 986) 94)
               (values (+ #.(+ 32 16) high) low)))
            ((< code 8224)
             (multiple-value-bind (high low)
                 (floor (- code 3336) 94)
               (values (+ #.(+ 32 42) high) low))))
    (when high-byte
      (values high-byte (+ low-byte #x21)))))

;; Generic arithmetic ok from the speed viewpoint: this is only used offline.

;; We haven't defined symbolically all of the magic numbers above.  The offsets
;; used (0, 94, 163, ..., 8224) are derived from
;; ksc-contiguous-character-group-lengths and
;; ksc-starting-offsets-for-character-groups.  Between these lists and the KSC
;; code charts, this is pretty easy to follow.  (MHD 1/19/95)


(defmacro ksc-bytes-to-ksc (form)
  `(multiple-value-bind (high-byte low-byte)
       ,form
     (when high-byte
       (+f (ashf high-byte 8) low-byte))))


#+development
(defun contiguous-to-ksc (code)
  (declare (eliminate-for-gsi-no-utf-g))
  (ksc-bytes-to-ksc (contiguous-to-ksc-bytes code)))


#||
;;; This tests that the conversions are inverses of each other.
(defun test-ksc-to-contiguous ()
  (loop for code from 0 below ksc-undefined-start
        unless (eql code (gensym-ksc-code-to-contiguous
                           (contiguous-to-gensym-ksc-code code)))
          do (break "~a" code))
  (loop for code from 0 below (ash 1 16)
        for x = (gensym-ksc-code-to-contiguous code)
        unless (or (not x) (= code (contiguous-to-gensym-ksc-code x)))
          do (print code)))
||#






;;; `Gensym-ksc-code-to-contiguous' maps character-code, a fixnum, to a
;;; contigous code that is the sum of the legal KSC codes that preceeded this
;;; code in the KSC code map.  If this is not a legal code, NIL is returned.
;;;
;;; `Contiguous-to-gensym-ksc-code' maps in the reverse direction.

(generate-codeset-contiguator 'ksc
                              ksc-gap-map
                              KSC-low-byte-offset
                              ksc-high-byte-min ksc-high-byte-max
                              ksc-low-byte-min ksc-low-byte-max)



#+development
(defun contiguous-to-gensym-ksc-code (code)
  (declare (eliminate-for-gsi-no-utf-g))
  (ksc-to-gensym-ksc (contiguous-to-ksc code)))


(defmacro generate-legal-gensym-ksc-character-code-p ()
  `(defun legal-gensym-ksc-character-code-p (gensym-ksc-code)
     (declare (eliminate-for-gsi-no-utf-g))
     (let ((high-byte (ashf gensym-ksc-code -8))
           (low-byte
             (-f (logandf gensym-ksc-code 255)        ; converts from Gensym-KSC to KSC code
                 KSC-low-byte-offset)))
       (cond
         ((and (<=f ksc-high-byte-min high-byte ksc-high-byte-max)
               (<=f ksc-low-byte-min low-byte ksc-low-byte-max))
          (not                                        ; NOT in a gap?
            ,(generate-binary-search-code
               'high-byte
               (loop for (high-byte-with-gaps)
                         in ksc-gap-map
                     collect high-byte-with-gaps)
               (loop for (high-byte-with-gaps . gaps)
                         in ksc-gap-map
                     collect
                       `(if (=f ,high-byte-with-gaps high-byte)
                            ,(if (cdr gaps)        ; could always use an or, but this
                                 `(or                ;   simplifies reading the expansion a bit
                                    . ,(loop for (min . max) in gaps
                                             collect
                                               `(<=f ,min low-byte ,max)))
                                 `(<=f ,(car (car gaps))
                                       low-byte
                                       ,(cdr (car gaps))))))
               nil))
          ;; The following alternative is a few percentage points slower (maybe 4%?),
          ;; but is a bit more straightforward and takes a few less instructions,
          ;; (maybe 15% less).  (MHD 11/17/92)
;          (not                                        ; NOT in a gap?
;            (cond
;              ,@(loop for (high-byte-with-gaps . gaps)
;                          in ksc-gap-map
;                      collect
;                        `((=f ,high-byte-with-gaps high-byte)
;                          ,(if (cdr gaps)        ; could always use an or, but this
;                               `(or                ;   simplifies reading the expansion a bit
;                                  . ,(loop for (min . max) in gaps
;                                           collect
;                                             `(<=f ,min low-byte ,max)))
;                               `(<=f ,(car (car gaps))
;                                     low-byte
;                                     ,(cdr (car gaps))))))))
          )))))

;; The resulting function tests if the high and low bytes are in the
;; code space allocated for KSC codes.





;;; Legal-gensym-ksc-character-code-p is true if character-code, a fixnum, is a
;;; legal Gensym-KSC code.  To map between a Gensym-KSC code and a KSC code, use
;;; either ksc-to-gensym-ksc or gensym-ksc-to-ksc.

(generate-legal-gensym-ksc-character-code-p)


;;; Test-legal-gensym-ksc-character-code-p returns T if it works; otherwise,
;;; nil.

#+development
(defun test-legal-gensym-ksc-character-code-p ()
  (= (loop for i from 0 to 65000
           count (legal-gensym-ksc-character-code-p i))
     8224))


;;; Benchmark-legal-gensym-ksc-character-code-p ...

#+development
(defun benchmark-legal-gensym-ksc-character-code-p ()
  (time
    (loop for i from 0 to 65000
          count (legal-gensym-ksc-character-code-p i))))



;;; The macro `ks-unicode-p' is true if unicode corresponds to a KS-C-5601
;;; character code.

(def-substitution-macro ks-unicode-p (unicode)
  (map-unicode-to-ks-c-5601 unicode))





;;;; "Gensym GB-2312-1980" Characters



;;; NB: There is no special region of gensym character codes in the legacy
;;; Gensym character set, hence the "quotes".  There are some functions here for
;;; consistency with those used for Japanese and Korean national character sets.
;;; Mostly this section deals with defining a few facts about the Mainland
;;; Chinese character set known as `GB-2312-1980', also known in Gensym software
;;; typically as `gb-2312' or `gb2312', or just `gb' for short.

(def-concept gb-2312-1980)
(def-concept gb-2312)
(def-concept gb2312)
(def-concept gb)

(defconstant gb-high-byte-min #x21)
(defconstant gb-high-byte-max #x77)

(defconstant gb-low-byte-min #x21)
(defconstant gb-low-byte-max #x7e)



;;; The constant `number-of-contiguous-gb2312-codes' gives the number of
;;; contiguous code points allocated for the GB2312 character set.
;;;
;;; NOTE: Not Development:
;;;
;;; NOTE: Technically, this should be
;;;
;;; (defconstant number-of-contiguous-gb2312-codes 7445)
;;;
;;; However, we don't squeeze down quite that far (to save 733 characters), but
;;; assume a solidly packed 87 rows of 94 characters each, thus giving the
;;; definition that follows
;;;
;;; (defconstant number-of-contiguous-gb2312-codes 8178)
;;;
;;; with a value of 8178.  This simplifies the definition of
;;; `gensym-gb2312-code-to-contiguous', which maps from a GB2312 code to a
;;; contiguous code such that 0 = first character in the first row, 1 is the
;;; second character in the first row, ..., 94 is the first character in the
;;; second row, etc.
;;;
;;; The GB2312 character set has codes defined in the rectangular area from
;;; #x2121 to #x777E.
;;;
;;; Examples: (gensym-gb2312-code-to-contiguous #x2121) => 0
;;;           (gensym-gb2312-code-to-contiguous #x777e) => 8177

(defconstant number-of-contiguous-gb2312-codes 8178)

(defun-substitution-macro gensym-gb2312-code-to-contiguous (gensym-gb2312-code)
  (+f (*f (-f (ashf gensym-gb2312-code -8) #x21) 94)
      (-f (logandf #xFF gensym-gb2312-code) #x21)))




;;;; Cyrillic within the Gensym Character Set



;;; The `Cyrillic script' is encoded in the Gensym character set as \ complex
;;; characters.
;;;
;;; This script occupies the block of 256 places in the code space starting at
;;; #x2000 (ending at #x20ff).  This block is intended to match relative
;;; position of the Cyrillic script in the Unicode character set standard, where
;;; it is U+0400 -> U+04FF (i.e., the range #x400 to #x4ff, inclusive).
;;;
;;; Note that the Unicode standard for Cyrillic is a superset of, and is based
;;; on, the prominent ISO standard, ISO-8859-5, and that it encodes characters
;;; common to both standards in the same relative positions.  Thus, for any two
;;; characters in the ISO standard, C1 and C2, the value of C1 - C2 will always
;;; be the same in all three character sets (ISO-8859-5, Unicode, and Gensym).
;;;
;;; Note that many of the possible 256 character codes are unassigned in
;;; Unicode, but they are reserved for this character set regardless by the
;;; Unicode character set, and, accordingly, also by the Gensym character set.
;;;
;;; Note that in the immediate future, it is unlikely that all of the defined
;;; Unicode will be implemented.  In particular, the diacritics that must be
;;; composed with other base characters will not be supported because support
;;; for composed characters is generally lacking in G2 text facilities.  In
;;; addition, many of the characters in the Unicode standard are obscure and
;;; will likely not find much use, particularly those that are not in
;;; ISO-8859-5.  Note that all of the characters common to ISO-8859-5 will be
;;; supported from the outset.  Note that ISO-Latin5 is a synonym for
;;; ISO-8859-5.
;;;
;;; See the Unicode Standard, Version 1.0, Volume 1, pages 44-45, for definition
;;; and discussion of the Cyrillic script within Unicode.  See pages 204-205 for
;;; a chart of the Cyrillic block within Unicode.  See pages 206-209 for the
;;; names listing.
;;;
;;; Note that Gensym Cyrillic characters happen to always be encodable in three
;;; bytes due to where they are positioned in the code space and the details
;;; of the encoding of "Kanji" characters.
;;;
;;; Note that Cyrillic, Korean, and, in the future, other scripts, look to
;;; certain software like "Kanji" or "Japanese".  This is an historical artifact
;;; dating from the time when only Japanese (Kanji/JIS) scripts used the \
;;; complex characters.

(defmacro legal-gensym-cyrillic-character-p (character-code)
  `(<=f #x2000 ,character-code #x20ff))

(defmacro cyrillic-unicode-p (unicode)
  `(legal-gensym-cyrillic-character-p
     (unicode-cyrillic-to-gensym-cyrillic ,unicode)))

; (defconstant gensym-cyrillic-character-block-start #x2000)
;; moved above to fix fwd. ref. problem!

(defconstant unicode-cyrillic-character-block-start #x0400)

(defconstant iso-8859-5-offset-within-cyrillic-character-block 0)

(defvar unicode-offset-for-gensym-cyrillic
  (-f gensym-cyrillic-character-block-start
      unicode-cyrillic-character-block-start))

(defun-substitution-macro unicode-cyrillic-character-p (unicode)
  (legal-gensym-cyrillic-character-p
    (+f unicode
        unicode-offset-for-gensym-cyrillic)))

(defun-substitution-macro unicode-cyrillic-to-gensym-cyrillic (unicode)
  (+f unicode
      unicode-offset-for-gensym-cyrillic))

(defun-simple iso-8859-5-to-gensym-cyrillic (iso-8859-5-character-code)
  (+f gensym-cyrillic-character-block-start
      iso-8859-5-offset-within-cyrillic-character-block
      iso-8859-5-character-code))


;;; `Cyrillic-a-list' contains an alist of the form
;;;
;;;   { (entry-or-range code-or-range? name direct-index? key-name? key-cap?) }
;;;
;;; ...
;;;
;;; The first element is Unicode, which in the first 128 characters is a simple
;;; offset from ISO-8859-5 (ISO Latin5).  The second element is the Microsoft
;;; Windows (3.1) Cyrillic Character Set.  The name is the Unicode name, minus
;;; "CYRILLIC CAPITAL|SMALL LETTER", but using case of the names to distinguish
;;; upper from lower case.  The direct-index? is either nil of the Bitstream
;;; Character ID that corresponds to this character in our current slavic font.
;;; (This character ID mapping scheme may well need overhauling if we use a
;;; different font.  This is based on our current font, called "Slavic Swiss", a
;;; TrueType font for MS Windows.)  The key-name?, if non-nil, is the symbol
;;; defined in keydefs (based on X keysyms) associated with this character code.
;;; Key-cap? is the (typical/standard US Keyboard) character that is normally
;;; engraved on the keycap for this character on a standard Russian character.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter-excluding-gsi cyrillic-character-a-list
  (optimize-constant
  '((#x0400 nil)                        ; 160 = non-breaking space - don't use in Unicode/10646
    (#x0401 168 "IO" 135 |Cyrillic_IO| #\~)
    (#x0402 128 "DJE" 98 |Serbian_DJE|)        ; serbian
    (#x0403 129 "GJE" 99 |Macedonia_GJE|) ; macedonian
    (#x0404 170 "E" 137 |Ukrainian_IE|)        ; "ukrainian ie" per 10646
    (#x0405 189 "DZE" 156 |Macedonia_DSE|)
    (#x0406 178 "I" 145 |Ukrainian_I|)        ; "byelorussian-ukrainian i" per 10646
    (#x0407 175 "YI" 142 |Ukrainian_YI|) ; ukrainian
    (#x0408 163 "JE" 130 |Cyrillic_JE|)
    (#x0409 138 "LJE" 107 |Cyrillic_LJE|)
    (#x040a 140 "NJE" 109 |Cyrillic_NJE|)
    (#x040b 142 "TSHE" 111 |Serbian_TSHE|) ; serbian/serbocroatian
    (#x040c 141 "KJE" 110 |Macedonia_KJE|) ; macedonian
    (#x040d nil)                        ; 173 = soft hyphen - don't use in Unicode/10646
    (#x040e 161 "SHORT U" 128 |Byelorussian_SHORTU|) ; byelorussian
    (#x040f 143 "DZHE" 112 |Cyrillic_DZHE|)
    ((#x0410 #x044F)
     (192 255)
     ("A" "BE" "VE" "GE"
      "DE" "IE" "ZHE" "ZE"
      "II" "SHORT II" "KA" "EL"
      "EM" "EN" "O" "PE"
      "ER" "ES" "TE" "U"
      "EF" "KHA" "TSE" "CHE"
      "SHA" "SHCHA" "HARD SIGN" "YERI"
      "SOFT SIGN" "REVERSED E" "IU" "IA"

      "a" "be" "ve" "ge" "de" "ie" "zhe" "ze" "ii" "short ii"
      "ka" "el" "em" "en" "o" "pe" "er" "es" "te" "u" "ef" "kha"
      "tse" "che" "sha" "shcha" "hard sign" "yeri" "soft sign"
      "reversed sign" "reversed e" "iu" "ia") ; (several naming divergences from 10646!)
     (159 222)
     (|Cyrillic_A| |Cyrillic_BE| |Cyrillic_VE| |Cyrillic_GHE|
      |Cyrillic_DE| |Cyrillic_IE|  |Cyrillic_ZHE| |Cyrillic_ZE|
      |Cyrillic_I| |Cyrillic_SHORTI| |Cyrillic_KA| |Cyrillic_EL|
      |Cyrillic_EM| |Cyrillic_EN| |Cyrillic_O| |Cyrillic_PE|
      |Cyrillic_ER| |Cyrillic_ES| |Cyrillic_TE| |Cyrillic_U|
      |Cyrillic_EF| |Cyrillic_HA| |Cyrillic_TSE| |Cyrillic_CHE|
      |Cyrillic_SHA| |Cyrillic_SHCHA| |Cyrillic_HARDSIGN| |Cyrillic_YERU|
      |Cyrillic_SOFTSIGN| |Cyrillic_E| |Cyrillic_YU| |Cyrillic_YA|

      |Cyrillic_a| |Cyrillic_be| |Cyrillic_ve| |Cyrillic_ghe|
      |Cyrillic_de| |Cyrillic_ie|  |Cyrillic_zhe| |Cyrillic_ze|
      |Cyrillic_i| |Cyrillic_shorti| |Cyrillic_ka| |Cyrillic_el|
      |Cyrillic_em| |Cyrillic_en| |Cyrillic_o| |Cyrillic_pe|
      |Cyrillic_er| |Cyrillic_es| |Cyrillic_te| |Cyrillic_u|
      |Cyrillic_ef| |Cyrillic_ha| |Cyrillic_tse| |Cyrillic_che|
      |Cyrillic_sha| |Cyrillic_shcha| |Cyrillic_hardsign| |Cyrillic_yeru|
      |Cyrillic_softsign| |Cyrillic_e| |Cyrillic_yu| |Cyrillic_ya|)
     (#\F #\< #\D #\U
      #\L #\T #\: #\P
      #\B #\Q #\R #\K
      #\V #\Y #\J #\G
      #\H #\C #\N #\E
      #\A #\{ #\W #\X
      #\I #\O #\} #\S
      #\M #\" #\> #\Z

      #\f #\, #\d #\u
      #\l #\t #\; #\p
      #\b #\q #\r #\k
      #\v #\y #\j #\g
      #\h #\c #\n #\e
      #\a #\[ #\w #\x
      #\i #\o #\] #\s
      #\m #\' #\. #\z))
    (#x0450 nil)                        ; don't use in Unicode/10646
    (#x0451 184 "io" 151 |Cyrillic_io| #\`)
    (#x0452 144 "dje" 113 |Serbian_dje|) ; (above notes for upper case apply)
    (#x0453 131 "gje" 101 |Macedonia_gje|)
    (#x0454 186 "e" 153 |Ukrainian_ie|)
    (#x0455 190 "dze" 157 |Macedonia_dse|)
    (#x0456 179 "i" 146 |Ukrainian_i|)
    (#x0457 191 "yi" 158 |Ukrainian_yi|)
    (#x0458 188 "je" 155 |Cyrillic_je|)
    (#x0459 154 "lje" 122 |Cyrillic_lje|)
    (#x045a 156 "nje" 124 |Cyrillic_nje|)
    (#x045b 158 "tshe" 126 |Serbian_tshe|)
    (#x045c 157 "kje" 125 |Macedonia_kje|)
    (#x045d nil)                        ; ? = section sign - don't use in Unicode/10646
    (#x045e 162 "short u" 129 |Byelorussian_SHORTU|)
    (#x045f 144 "dzhe" 127 |Cyrillic_dzhe|)

    ;; the rest (60 to 7f) are Historic letters; Gensym does not handle them now.
    )))
)

;; This isn't used yet, but I anticipate it being used shortly to generate
;; an mapping array; so it is a defvar-for-macro, and will be around only
;; at macroexpansion time.

;; See if the space for this at runtime could be eliminated -- this information
;; is only needed to construct the macro that needs to just be run once at load
;; time (i.e., to set up the mapping arrays)!  Note that the character name
;; strings are not used yet and could be eliminated entirely.  (MHD 4/5/95)




;;; `Map-to-msw-cyrillic-code-if-any' returns either a MSW Cyrillic character
;;; code for cyrillic-unicode-index, or nil to indicate that character has not
;;; been defined.  A `Cyrillic unicode index' is a unicode character minus the
;;; offset of the Cyrillic coding block, i.e. a number in the range 0..255.  A
;;; map-to-msw-cyrillic-code-if-any form can be used as a setf'able place form
;;; for defining these complex characters.

(defmacro map-unicode-index-to-msw-cyrillic-code-if-any (unicode-index)
  `(svref msw-cyrillic-code-map ,unicode-index))

(defvar-excluding-gsi-no-utf-g msw-cyrillic-code-map
  (make-array-with-nils 128))        ; a simple vector

#+development
(defmacro map-msw-cyrillic-to-unicode-index-code-if-any (msw-code)
  `(svref msw-to-unicode-cyrillic-code-map ,msw-code))

#+development
(defvar msw-to-unicode-cyrillic-code-map
  (make-array-with-nils 256))        ; a simple vector


#+development
(defmacro set-one-msw-cyrillic-to-unicode-code-mapping (msw-code unicode)
  `(setf (map-msw-cyrillic-to-unicode-index-code-if-any ,msw-code)
         ,unicode))

(defmacro set-one-msw-cyrillic-code-mapping (unicode msw-code)
  `(setf (map-unicode-index-to-msw-cyrillic-code-if-any
           (-f ,unicode unicode-cyrillic-character-block-start))
         ,msw-code))

#+development
(defvar unicode-index-to-cyrillic-name-map
  (make-array-with-nils 128))

#+development
(defmacro map-unicode-index-to-cyrillic-name (unicode-index)
  `(svref unicode-index-to-cyrillic-name-map ,unicode-index))

#+development
(defmacro set-one-unicode-index-to-cyrillic-to-name-mapping (unicode-index name?)
  `(setf (map-unicode-index-to-cyrillic-name ,unicode-index) ,name?))


(defmacro map-unicode-index-to-slavic-font-direct-index (unicode-index)
  `(svref unicode-index-to-slavic-font-direct-index-map ,unicode-index))

(defvar-excluding-gsi-no-utf-g unicode-index-to-slavic-font-direct-index-map
  (make-array-with-nils 128))

(defmacro set-one-unicode-index-to-slavic-font-direct-index-mapping (unicode-index direct-index?)
  `(setf (map-unicode-index-to-slavic-font-direct-index ,unicode-index) ,direct-index?))

(def-global-property-name cyrillic-gensym-character-code-for-key-name)


(defvar-excluding-gsi-no-utf-g key-cap-to-gensym-cyrillic-character-code-map
  (make-array-with-nils 128))

(defmacro map-key-cap-to-gensym-cyrillic-character-code (simple-character-char-code)
  `(svref key-cap-to-gensym-cyrillic-character-code-map ,simple-character-char-code))

(defmacro set-one-cyrillic-keyboard-key-cap-mapping
    (char-code gensym-cyrillic-character-code)
  `(setf (map-key-cap-to-gensym-cyrillic-character-code ,char-code)
         ,gensym-cyrillic-character-code))

(defun-void utilize-cyrillic-character-a-list ()
  (declare (eliminate-for-gsi-no-utf-g))
  ;; just used at load time; could be a macro to save a bit of space
  (loop for (code msw-code? name? direct-index? key-name? key-cap?)
            in cyrillic-character-a-list
        do
    (cond
      ((consp code)
       (loop for code from (first code) to (second code)
             as msw-code? from (first msw-code?)
             as name? in name?
             as direct-index? from (first direct-index?)
             as key-name? in key-name?
             as key-cap? in key-cap?
             do (utilize-cyrillic-character-a-list-1
                  code msw-code? name? direct-index? key-name? key-cap?)))
      (t
       (utilize-cyrillic-character-a-list-1
         code msw-code? name? direct-index? key-name? key-cap?)))))

(defun-void utilize-cyrillic-character-a-list-1
    (code msw-code? name? direct-index? key-name? key-cap?)
  (declare (eliminate-for-gsi-no-utf-g) #-development (ignore name?))
  (set-one-msw-cyrillic-code-mapping code msw-code?)
  #+development
  (when msw-code? (set-one-msw-cyrillic-to-unicode-code-mapping msw-code? code))
  #+development
  (set-one-unicode-index-to-cyrillic-to-name-mapping
    (-f code unicode-cyrillic-character-block-start)
    name?)
  (set-one-unicode-index-to-slavic-font-direct-index-mapping
    (-f code unicode-cyrillic-character-block-start)
    direct-index?)
  (when key-name?
    (setf (cyrillic-gensym-character-code-for-key-name key-name?)
          (+f (-f code unicode-cyrillic-character-block-start)
              gensym-cyrillic-character-block-start)))
  (when key-cap?
    (set-one-cyrillic-keyboard-key-cap-mapping
      (char-code key-cap?)
      code)))                                ; as of 5/22/96 this is Unicode (#x04xx);
                                        ; previously (e.g., in 4.0) it was
                                        ;   a gensym character code (#x20xx)


(defmacro utilize-cyrillic-character-a-list-macro ()
  (if (gsi-no-utf-g-eliminable-p)
      nil
      '(utilize-cyrillic-character-a-list)))


(utilize-cyrillic-character-a-list-macro)





;;;; UTF-G
(def-concept utf-g)


;;; In 5.0, the Gensym character set, and its encoding in strings and files as a
;;; sequence of 7 bit characters, is expanded compatibly to include all of
;;; Unicode.  There are several notable regions:
;;;
;;;   The `JIS-X-0208 region' remains the same as in 4.0 -- these are direct
;;;   mapping of all of the JIS-X-0208 character set encodings.  These are
;;;   located in the rectangular region with #x2121 in the upper left, and
;;;   #x747e in the upper right
;;;
;;;   The `KS-C-5601 region' remains the same as in 4.0 -- these are the
;;;   KS-C-5601 character set encoding with the first (8-bit) byte incremented
;;;   by 94.  These are located in the rectangular region with #x7421 in the
;;;   upper left, and #xdd7e in the lower right.
;;;
;;;   The `general region' contains the 32 rows that have assignments in Unicode
;;;   1.1 apart from the 112 rows that make up the CJK region (described below).
;;;   Refer to Figure 3 - "Overview of the Basic Multilingual Plane" in the ISO
;;;   10646 document, reference number ISO/IEC 10646-1:1993(E).  Intuitively,
;;;   the broad categories of General Scripts, Symbols, and Compatibility are
;;;   encoded in these rows.  As of Unicode version 1.1, which is equivalent to
;;;   the ISO 10646 BMP (Basic Multilingual Plane), there are 32 rows assigned.
;;;   A table will be defined that maps the row number in of each such row to
;;;   the row number of the same row in the Gensym character set.  Once this row
;;;   mapping has been done, the column mapping will be an identity.  For
;;;   example, the row assigned to Cyrillic in Unicode (#x04) is assigned to row
;;;   #x20 in the Gensym character set.  Thus any unicode character #x04xx will
;;;   be the Gensym character #x20xx.  Note that this region includes ISO
;;;   8859-1, which includes ASCII.  That row is #x00 in both Unicode and Gensym
;;;   character sets.  Note that there are four (4) non-ISO 8859-1 characters in
;;;   the Gensym/G2 4.0 character sets: trademark, OE, oe, and bullet.  These
;;;   all map into various other rows of the general region.
;;;
;;;   The `CJK main region' contains the 108 rows of the Hangul (10), Hangul
;;;   Supplementary-A (7), Hangul Supplementary-B (9), and CJK (82) rows of
;;;   Unicode.  Note that there is strong overlap and ambiguity between this
;;;   region and the JIS-X-0208 and KS-C-5601 regions.  See han-unification-mode
;;;   (tbd!) for information how approaches to resolving the ambiguity.
;;;
;;;   The `CJK miscellaneous region' takes the remaining 6 CJK-related rows of
;;;   Unicode not handled by the CJK main or General regions.  (Rows FE and FF
;;;   are partially CJK-related, but they're handled by the general region.)
;;;
;;;   The `extension region' (= "extended UTF-G") contains two subregions, and
;;;   extends the Gensym character set to encode all 2^16 possible Unicode code
;;;   points.  In text validly encoded the Gensym character set, a first-half
;;;   character should appear right before a second-half character.  The two
;;;   character codes are interpreted by multiplying them together, thus giving
;;;   rise to 256 X 256 (= 65536) possible codes, which is adequate to encode
;;;   all of Unicode.  This region thus gives rise to yet another ambiguity, in
;;;   that all possible Unicode characters that can appear in the General or CJK
;;;   regions of the Gensym character set may also be encoded via pairs of
;;;   characters from this region.  This region is intended to handle the
;;;   Private Use Area of Unicode (rows in the range #xe0..#xf8), as well as any
;;;   newly assigned rows in future versions of Unicode.  Note, however, that it
;;;   is valid to encode any Unicode character using pairs of character from
;;;   this region.

;; Notes: (1) most of the code that implements this is in CHARACTERS; (2) the
;; CJK miscellaneous region is just conceptual: it overlaps arbitrarily with the
;; general region; (3) some of the row assignement details are off.  This
;; documentation should be fixed by making it follow the facts in CHARACTERS.




;;;; Gensym/Unicode Row Correspondences



;;; `Gensym-unicode-row-correspondences' is a table, of sorts, and gives the
;;; correspondences between rows in the Gensym Character Set and rows in Unicode
;;; 1.1.

;;; These are organized in order Unicode Row, lowest to highest.  Gensym
;;; Row(s)/Unicode Row(s)/Rectangular Area/; Description
;;;
;;; Rectangular area is a list, (upper-left lower-right), i.e., a pair of
;;; numbers giving the rectangular coding area, offset from column #x00 of the
;;; given row, in the Gensym coding space that Unicode row is to occupy.  It can
;;; be omitted, in which case it is assumed to occupy an entire row, that is, is
;;; assumed to be (#x0000 #x00FF).  For example, (#x0080 #x01FF) gives a
;;; rectangular area that occupies that right half of two rows.  [There is no
;;; use of partial rows at present; this might be an extension in future, but
;;; there are no plans at present.]

;;; Row #xF6 is currently reserved as the invalid row for Gensym character
;;; codes, thus the value of the constant `invalid-gensym-full-row'.  Row #x07
;;; (not allocated in Unicode 1.1) is reserved as the invalid row for Unicode
;;; charactere codes, thus the value of the constant `invalid unicode full
;;; row'. These are useful for creating a distinguished value in the row mapping
;;; vectors, although they're changeable at any time with no impact on users.

;;; Rows #xF7-#xF8 shall be reserved for `Extended UTF-G', wherein a sequence of a
;;; high-half code Ch, a code 0..255 from row F7, followed by a low-half code
;;; Cl, a code 0..255 from row F8, is interpreted as a single occurance of the
;;; 16-bit code ChCl.  Note: this is analagous to the "surrogate characters"
;;; approach adopted by Unicode to extend its character repertoire past 2^16
;;; to over 1,000,000.
;;;
;;; Note that the Unicode 1.1 rows assigned as "Private Use Area", as well
;;; as unassigned rows, have not corresponding assignment in this table.  They
;;; fit into the extended UTF-G.

(defparameter gensym-unicode-row-correspondences
  (optimize-constant
  '((#x00 #x00)                                ; Basic Latin; Latin-1 Supplement
    (#x01 #x01)                                ; Latin Extended-A; Latin Extended-B
    (#x02 #x02)                                ; Latin Extended-B; IPA Extensions;
                                        ;   Spacing Modifier Letters
    (#x03 #x03)                                ; Combining Diacritical Marks; Basic
                                        ;   Greek; Greek Sybols and Coptic
    (#x20 #x04)                                ; Cyrillic
    (#x04 #x05)                                ; Armenian; Hebrew (Basic and Extended)
    (#x05 #x06)                                ; Basic Arabic; Arabic Extended
    (#x06 #x09)                                ; Devanagari; Bengali
    (#x07 #x0A)                                ; Gurmukhi; Gujarati
    (#x08 #x0B)                                ; Oriya; Tamil
    (#x09 #x0C)                                ; Telugu; Kannada
    (#x0A #x0D)                                ; Malayalam
    (#x0B #x0E)                                ; Thai; Lao
    (#x0C #x10)                                ; Georgian
    (#x0D #x11)                                ; Hangul Jamo
    (#x0E #x1E)                                ; Latin Extended Additional
    (#x0F #x1F)                                ; Greek Extended
    (#x10 #x20)                                ; General Punctuation; Super-Subscripts;
                                        ;   Currency Symbols; Comb. Diacritical
                                        ;    Marks for Symbols
    (#x11 #x21)                                ; Letterlike Symbols; Number Forms;
                                        ;   Arrows
    (#x12 #x22)                                ; Mathematical Operators
    (#x13 #x23)                                ; Miscellaneous Technical
    (#x14 #x24)                                ; Control Pictures; O.C.R.; Enclosed
                                        ;   Alphanumerics
    (#x15 #x25)                                ; Box Drawing; Block Elements; Geometric Shapes
    (#x16 #x26)                                ; Miscellaneous Symbols
    (#x17 #x27)                                ; Dingbats
    (#x18 #x30)                                ; CJK Symbols and Punctuation; Hragana; Katakana
    (#x19 #x31)                                ; Bopomofo; Hangul Compatibility Jamo; CJK Miscellaneous
    (#x1A #x32)                                ; Enclosed CJK Letters and Months
    (#x1B #x33)                                ; CJK Compatiblity
    ((#x7F #xEA) (#x34 #x9F))                ; 108 Rows: Hangul (begins 10 rows); Hangul
                                        ;   Supplementary-A (begins 7 rows);
                                        ;   Hangul Supplementary-B (begins 9 rows);
                                        ;   CJK Unified Ideographs (begins 82 rows)

    ;; NOTE: Row F6 is the reserved invalid row for Gensym codes.  Row #x07 is
    ;; the invalid Unicode row.

    ;; NOTE: Rows F7-F8 Reserved for "Extended UTF-G"; F7 is for the first-half
    ;; characters, and F8 is for the second-half characters.

    ((#xF9 #xFA) (#xF9 #xFA))                ; 2 Rows: CJK Compatibility Ideographs
    (#xFB #xFB)                                ; Alphabetic Presentation Forms
    ((#xFC #xFD) (#xFC #xFD))                ; 2 Rows: Arabic Presentation Forms
    (#xFE #xFE)                                ; Comb. Half Marks; CJK Compat. Forms; Small Form
                                        ;   Variants; Arabic Presntation Forms-B
    (#xFF #xFF))))                        ; Halfwidth and Fullwidth Forms; Specials



(defconstant invalid-unicode-full-row #x07)

(defparameter gensym-to-unicode-full-row-map
  (loop with vector
          = (make-array
              256
              :element-type '(unsigned-byte 8)
              :initial-element invalid-unicode-full-row)
        for x in gensym-unicode-row-correspondences
        when (null (third x))
          do (let ((g (first x))
                   (u (second x)))
               (if (consp g)
                   (loop for g-row from (first g) to (second g)
                         as u-row from (first u)
                         do (setf (aref vector g-row) u-row))
                   (setf (aref vector g) u)))
        finally (return vector)))

(defconstant invalid-gensym-full-row #xF6)

(defparameter unicode-to-gensym-full-row-map
  (loop with vector = (make-array
                        256
                        :element-type '(unsigned-byte 8)
                        :initial-element invalid-gensym-full-row)
        for x in gensym-unicode-row-correspondences
        when (null (third x))
          do (let ((g (first x))
                   (u (second x)))
               (if (consp g)
                   (loop for g-row from (first g) to (second g)
                         as u-row from (first u)
                         do (setf (aref vector u-row) g-row))
                   (setf (aref vector u) g)))
        finally (return vector)))





;;; `Map-unicode-to-extended-utf-g-characters' maps an arbitrary Unicode to its
;;; corresponding pair of "extended UTF-G" characters.  Its values are (1)
;;; high-half and (2) low-half.  See the definition of "Extended UTF-G" (above)
;;; for details.  The macros `unicode-to-extended-utf-g-high-half' and
;;; `unicode-to-extended-utf-g-low-half' give the high and low half,
;;; respectively, of their argument unicode.
;;;
;;; Although this can effectively encode all of Unicode, this is intended for
;;; use to cover only those rows not allocated in Unicode 1.1.
;;;
;;; `Map-unicode-1-1-character-to-gensym-character-code' will map any character
;;; in a row that was allocated in Unicode 1.1.  Note that this will even
;;; allocate characters allocated after Unicode 1.1, as long as they are in rows
;;; that had been at least partially allocated as of Unicode 1.1.

(defmacro unicode-to-extended-utf-g-high-half (unicode)
  `(+f #xF700 (ashf ,unicode -8)))

(defmacro unicode-to-extended-utf-g-low-half (unicode)
  `(+f #xF800 (logandf #xFF ,unicode)))

(defun map-unicode-to-extended-utf-g-characters (unicode)
  (values
    (unicode-to-extended-utf-g-high-half unicode)
    (unicode-to-extended-utf-g-low-half unicode)))


(defun-simple map-extended-utf-g-characters-to-unicode (high-half low-half)
  (+f (ashf (logandf high-half #xFF) 8) (logandf low-half #xFF)))


(defun-substitution-macro map-unicode-1-1-character-to-gensym-character-code (unicode)
  (let* ((row (ashf unicode -8))
         (gensym-full-row
           ;; NOTE: Accessed as translator version of byte-vector-aref, which is
           ;; defined later:
           (the (unsigned-byte 8)
                (aref (the (simple-array (unsigned-byte 8) (*))
                           unicode-to-gensym-full-row-map)
                      (the fixnum row)))))
    (unless (=f gensym-full-row invalid-gensym-full-row)
      (+f (ashf gensym-full-row 8)
          (logandf #xFF unicode)))))




(defun-substitution-macro map-gensym-character-code-to-unicode-1-1-character
    (gensym-character-code)
  (let* ((row (ashf gensym-character-code -8))
         (unicode-full-row
           ;; NOTE: Accessed as translator version of byte-vector-aref, which is
           ;; defined later:
           (the (unsigned-byte 8)
                (aref (the (simple-array (unsigned-byte 8) (*))
                           gensym-to-unicode-full-row-map)
                      (the fixnum row)))))
    (unless (=f unicode-full-row invalid-unicode-full-row)
      (+f (ashf unicode-full-row 8)
          (logandf #xFF gensym-character-code)))))





;;;; Latin Extended A: The OE Ligature and Florin


;;; The block of 256 places in our code space starting at #x0100 is reserved for
;;; the Unicode blocks Latin Extended A, and Latin Extended B, which is row #x01
;;; in Unicode.  For brevity, this row shall be internally called the `Latin
;;; Extended-A block' of the Gensym character set.

;;; The OE ligature is not a member of ISO Latin 1 (= ISO8859-1), and in fact
;;; is not even a member of any ISO 8859 character set.  It is, however, included
;;; at least once in Unicode.
;;;
;;; It has been in the Gensym character set since the beginning, so room must be
;;; allocated for it now.  In Unicode it fits into the block Latin Extended A
;;;
;;; Here is the Unicode data for OE:
;;;
;;;    0152;LATIN CAPITAL LIGATURE OE;Lu;0;L;;;;;N;LATIN CAPITAL LETTER O E;;;0153;
;;;    0153;LATIN SMALL LIGATURE OE;Ll;0;L;;;;;N;LATIN SMALL LETTER O E;;0152;;0152
;;;
;;;
;;; The Florin character has a completely different name in Unicode (LATIN SMALL
;;; LETTER SCRIPT F), ISO 10646 (LATIN SMALL LETTER F WITH HOOK), and
;;; Gensym/Adobe (Florin).  It's not in ISO Latin 1, but it's been part of the
;;; Gensym character set from the beginning.  Here is the Unicode data for
;;; Florin:
;;;
;;;    0192;LATIN SMALL LETTER F WITH HOOK;Ll;0;L;;;;;N;LATIN SMALL LETTER SCRIPT F;;0191;;0191





;; Excerpts discussing OE from Version: 2.9887
;;
;;
;;                   ISO 8859-1  National Character Set FAQ
;;
;;                           Michael K. Gschwind
;;
;;                       <mike@vlsivie.tuwien.ac.at>
;;
;; [Note: I replaced the instances of 8-bit ISO Latin1 characters representing
;; AE and replaced them with that character's uppercase Unicode Name: (LATIN
;; CAPITAL LIGATURE AE) -- I don't think we're ready for 8-bit characters in our
;; source code yet. (MHD 2/23/96)]
;;
;;
;; Footnote: Some people have complained about missing characters,
;;           e.g. French users about a missing 'oe'.  Note that oe is
;;           not a character, but a typographical ligature (a combination of two
;;           characters for typographical purposes).  Ligatures are not
;;           part of the ISO 8859-X standard.  (Although 'oe' used to
;;           be in the draft 8859-1 standard before it was unmasked as
;;           `mere' ligature.)
;;
;;           Two stories exist for the removal of the oe:
;;           (1) argues that in the final session, the French admitted
;;               that oe was only a ligature.  This prompted the
;;               committee to remove it.
;;           (2) argues that the French member missed the session and the
;;               members from the other countries simply decided to
;;               remove it.  (If this is true, where were the Swiss and
;;               Belgians?)
;;
;;           Note that the oe ligature is different from the 'historical
;;           ligature' (LATIN CAPITAL LIGATURE AE) which is now considered
;;           a letter in Nordic countries and cannot be replaced by the
;;           the latters 'ae'.
;;
;; Footnote: ISO 10646 calls (LATIN CAPITAL LIGATURE AE) a `ligature', but
;;           this is a letter in (at least some) Scandinavian languages.
;;           Thus, it is not in the same, merely typographic `ligature' class as
;;           `oe' ({\oe} in {\LaTeX} convention) which was not included
;;           in the ISO8859-1 standard.





;;;; Letterlike Symbols: Trademark

;;; The block of 256 places in our code space starting at #x1100 is reserved for
;;; the Unicode blocks Letterlike Symbols, Number Forms, and Arrows, which is
;;; row #x21 in Unicode.  For brevity, this row shall be internally called the
;;; `Letterlike Symbols Block' of the Gensym character set. Traditionally, only
;;; one character has been used for Gensym's character set through 4.0, namely,
;;; the Unicode character described as follows (in the Unicode database):
;;;
;;;    2122;TRADE MARK SIGN;So;0;ON;<+sup> 0054 004D <-sup>;;;;N;TRADEMARK;;;;
;;;
;;; There is one additional special aspect of this one included character: it
;;; is encoded as a ~ complex character, i.e., using the ~ escape character,
;;; followed by the colon (:) character.

(defmacro gensym-letterlike-symbol-p (character-code)
  `(<=f #x1100 ,character-code #x11ff))

(defconstant gensym-letterlike-symbol-block-start #x1100)

(defconstant unicode-letterlike-symbol-block-start #x2100)

(defvar unicode-offset-for-gensym-letterlike-symbol
  (-f gensym-letterlike-symbol-block-start
      unicode-letterlike-symbol-block-start))

(defun-simple unicode-letterlike-symbol-p (unicode)
  (gensym-letterlike-symbol-p
    (+f unicode
        unicode-offset-for-gensym-letterlike-symbol)))

;; Representing Trademark is a notorious problem, as explicated by the following
;; prose, dealing with HTML and ISO8859 character coding issues, from
;;
;; http://ppewww.ph.gla.ac.uk/~flavell/iso8859/iso8859-pointers.html#TM
;;
;;    TM - They seek it here, they seek it there
;;
;;    More than all other special characters added together, people post
;;    questions on the usenet WWW groups asking how to represent the TM
;;    (trademark) glyph. The answer, up to and including HTML 2.0, is that you
;;    cannot. This glyph is not included in the ISO8859-1 character code, and
;;    there is no defined way to represent it. When the question is asked on
;;    usenet, it usually brings at least one response that states a value of n
;;    for which &#n; displays the TM glyph on that informant's browser: but
;;    readers who have taken on board my explanation so far will realise that
;;    this is of no use, since it will display something different, or nothing
;;    at all, on some other browsers. The value of n is different according to
;;    whether the informant uses a Mac-based or an MS Windows-based browser
;;    (X-based browsers do not display this glyph at all in their normal fonts).
;;
;;    There are a number of kludges that you might consider using at this time:
;;    the letters T and M, marked up in some way that you hope will be displayed
;;    distinctively by the browser; an inline image with an ALT="TM"; or
;;    whatever. Bearing in mind that a modest range of browsers already honour
;;    the SUP tags, you might even enclose "TM" in those, like this:
;;    <SUP>TM</SUP>, and here is what your current browser does with that: TM.
;;
;;    When HTML3 is fully defined and supported, you will be able to get this
;;    glyph by coding &trade; - indeed, a few browsers already honour that, even
;;    though there is no defined character code for it in ISO8859-1. I cannot
;;    recommend that you use this yet though, because users who are not
;;    HTML-aware will be confused when a browser that does not honour this
;;    entity displays &trade; to them. Here is what your present browser
;;    displays in response to this entity: &trade;.





;;;; General Punctuation Block: New Line, New Paragraph, Bullet, and Oe



;;; The block of 32 places in our code space starting at zero (#x0000) is
;;; reserved for ASCII equivalents.  At present, no character codes are assigned
;;; here.  Note that 10, which is the ASCII LF (linefeed) character, would
;;; naturally loosely map to our @L (line break) complex character.  This is
;;; regarded in some, but not all, operating systems as the Newline character.

;;; The block of 256 places in our code space starting at #x1000 is reserved for
;;; General Punctuation characters, and is intended to be a subset of the
;;; Unicode characters defined in the blocks starting in the area from #x2000 to
;;; #x20ff, called General Punctuation, Superscripts and Subscripts, Currency
;;; Symbols, and Diacritical Marks for Symbols.  For brevity, this row shall be
;;; internally called the `general punctuation block' of the Gensym character
;;; set.

;;; The subset we make use of are three characters: line separator (@L),
;;; paragraph separator (@P), and bullet (~*).

;;; Unicode defines these characters unambiguously as line and paragraph
;;; separators, respectively:
;;;
;;;    2028;LINE SEPARATOR;Zl;0;B;;;;;N;;;;;
;;;    2029;PARAGRAPH SEPARATOR;Zp;0;B;;;;;N;;;;;

;;; The gensym complex character @L then will be assigned the character
;;; code #x1028.

;;; The Unicode character BULLET, which has been encoded in the 4.0 Gensym
;;; character set as ~*, appears in Unicode at #x2022, with the following
;;; mapping data:
;;;
;;;    2022;BULLET;Po;0;ON;;;;;N;;;;;
;;;
;;; Thus, the complex character ~* will be assigned the character code #x1022.

(defmacro legal-gensym-general-punctuation-character-p (character-code)
  `(<=f #x1000 ,character-code #x10ff))

(defconstant gensym-general-punctuation-character-block-start #x1000)

(defconstant unicode-general-punctuation-character-block-start #x2000)

(defvar unicode-offset-for-gensym-general-punctuation
  (-f gensym-general-punctuation-character-block-start
      unicode-general-punctuation-character-block-start))

(defun-simple unicode-general-punctuation-character-p (unicode)
  (legal-gensym-general-punctuation-character-p
    (+f unicode
        unicode-offset-for-gensym-general-punctuation)))

;; Note that currently in G2 (4.0), foo@Lbar < fooxbar.  If we assigned
;; a code for @L that is higher than the ascii graphic characters, then
;; would change the sort order.  On the other hand, it would remain a stable
;; sort order.  Is this a big issue?  If so, you could still be compatible,
;; but at the expense of being able to do a straight numeric code comparison.
;;
;; Note also: some people might be sad that we're not mapping @L to one of the
;; ASCII code or code sequences used for this.  I think mapping to ASCII is too
;; problematic because of the ambiguity as to what you map to.  If this were a
;; situation where ASCII had a clear match, that would be different.  At least
;; Unicode has a perfect match for @L and @P, so why not use them.  Then the
;; problem of mapping from Unicode-to-ascii or -whatever, and back, can be
;; solved separately, a problem we're presumably left with in any case.

;; What about the @P letter -- it's defined as an "implemented @ character"
;; above, but I don't think it's been too much used.  There's no ASCII/Latin1
;; character corresponding. However, there are two separate New Line and New
;; Paragraph codes in Unicode.  If we make @P be New Paragraph, should we make
;; @L be New Line?  Only New Line, or both ASCII and Unicode's?

;; The RTF specification has this heuristic:
;;
;;   For simplicity of operation, the ASCII codes 9 and 10 will be accepted as
;;   \tab and \par, respectively. ASCII 13 will be ignored. The control
;;   code \<10> will be ignored. It may be used to include "soft"
;;   carriage returns for easier readibility but which will have no effect
;;   on the interpretation.

;; Note that we assigned row #x20 in the Gensym character set to Cyrillic before
;; we had any notion that it should be aligned with its native Unicode row.  Now
;; that it's out there (as of G2 4.0 Documentation and usable as of G2 Rev. 1),
;; we're stuck with a somewhat unnatural ordering of the Gensym rows vs. the
;; Unicode rows, but it's kind of arbitrary anyway.  (MHD 2/28/96)


;;;; The Gensym Character Set vs. Other Standards: A Discussion

;; (MHD 11/7/95)

;;; Character Sets vs. Coded Character Sets
;;;
;;; There is a Gensym Character Set, but no `Coded Gensym Character Set' exists
;;; at present.  In general, a `character set' has a `repertoire' of characters,
;;; and a `coded character set' maps a set of distinct codes (generally,
;;; unsigned 8- or 16-bit integers) to each character in its repertoire.
;;; Separate from the notion of a character set (coded or uncoded) is its
;;; encoding.
;;;
;;; Gensym does have a `standard encoding for Gensym characters', i.e., the one
;;; that features the somewhat notorious multibyte escape sequences starting
;;; with (the ASCII values for) ~, \, or @, no 8-bit characters, no characters
;;; in the control range (0-31 or 127), etc.  But the specification `encoding'
;;; for a character set can be, and generally is, handled as a separate matter
;;; from the specification of the character set itself.
;;;
;;; Unicode, for example, specifies a logical ordering of codes, the size in
;;; bits of each code, the mapping from characters to codes, etc., but there
;;; exist now several different standards for _encoding_ Unicode, e.g., UTF-7
;;; (universal transformation format - 7 bits), UTF-8 (universal transformation
;;; format - 8 bits), FSS-UTF (file system safe universal transformation
;;; format), etc.  Similarly, the JIS X 0208 character set (Japanese) has at
;;; least three prominent standard encodings, including EUC (8-bit), JIS (7-bit,
;;; ISO 2022 compliant), and Shift-JIS (7-bit multibyte, non-ISO 2022
;;; compliant).
;;;
;;; In principle, defining a mapping from the characters in the Gensym character
;;; set to codes is all that would be needed to give us a coded character set.
;;; While that alone would have some beneficial value, this is not enough for
;;; most needs.
;;;
;;; First of all, which codes do you choose?  The first suggestion that springs
;;; to mind is "pick a standard".  There are of course many to choose from.
;;; Let's examine some of them and see how if at all they mesh with our needs.
;;;
;;;
;;; ASCII - there are really two sides to ASCII, which is also now an
;;; international standard, ISO 646.  One is the Graphic characters of ASCII,
;;; which have codes in the inclusive range [32..126], and the other is the
;;; Control characters, which have codes in the inclusive range [0..31] plus
;;; 127.
;;;
;;; We mesh well with the Graphic characters of ASCII because there is a
;;; complete 1:1 correspondence between the repertoire of ASCII graphics
;;; characters and a subset of the Gensym characters.
;;;
;;; However, we do not mesh well with the Control characters of ASCII.  Certain
;;; of the control characters have no standard semantics.  The most notorious
;;; example is the control character or character sequence used with ASCII characters
;;; to encode "new line".  The official ASCII convention is Return followed by
;;; linefeed.  But the Macintosh OS uses just Return, while Unix uses just Linefeed,
;;; while PC's and Vaxes use ASCII's Return followed by Linefeed.  Whatever representation
;;; of Newline in ASCII, Gensym has one character dedicated to this purpose,
;;; @L. Gensym also has internally defined @P as the character meaning "new paragraph".
;;; Gensym has not yet used @P in files it exports, so this could possibly be backed
;;; out. ASCII does not define a "new paragraph" character, although other character
;;; sets do.  Unicode in particular defines both an unambiguous Newline character
;;; and an unambiguous New Paragraph character.  If we wanted to, we could do what
;;; Unicode has done and map @L and @P to ASCII in ways that they do.
;;;
;;; Glenn Adams, Unicode Technical Committee member and character set design maven
;;; extraordinaire has written
;;;
;;;    No little blood has been spilled among programmers over the
;;;    issue of what constitutes a _new line_. Many systems employ
;;;    the ASCII sequence CARRIAGE RETURN, LINE FEED; while other
;;;    systems, e.g., UN*X systems, employ only LINE FEED. Furthermore,
;;;    what consitutes a _new paragraph_ has beeen similarly vague.
;;;    Unicode addresses both of these problems by defining two
;;;    explicit punctuation characters that signify LINE SEPARATOR
;;;    and a PARAGRAPH SEPARATOR, respectively.
;;;
;;; (Our comment: that's great, but how does this help us to translate to
;;; Unicode from ASCII and back?!)
;;;
;;; A character that's frequently missed in the Gensym character set is a plain
;;; TAB character, i.e., one that would put the text following this character at
;;; the next column, where each column might appear every width of 5 spaces,
;;; say, or some user-controllable width.  Implementing the keyboard/mouse
;;; input, parsing, formatting, and text rendering side of this character's
;;; semantics would probably need to be done before allowing an equivalent
;;; character to be defined in the Gensym set, at least if it's to be done in a
;;; satisfactory way.  The formatting and text rendering in particular are not
;;; totally trivial.  Note that if Gensym's built-in support for text entry,
;;; rendering, and formatting is to be phased out, it may be acceptable to
;;; support a Tab equivalent character as a pass-through character, which would
;;; at least provide full round-trip translation.
;;;
;;; The PAGE character is also a semistandard character.  It is doubtful we
;;; would ever provide a meaningful interpretation of this character in our
;;; character set, but allowing it to pass through would probably be a
;;; beneficial thing.
;;;
;;; The VERTICAL TAB character is similarly not likely to ever be implemented,
;;; though it could want to be safely transmitted ala PAGE.
;;;
;;; The backspace character is no longer considered even a semistandard
;;; character, although it used to be standardly used for composing or "joining"
;;; two characters in ASCII, e.g., EQUAL SIGN + BACKSPACE + SLASH would give
;;; you the NOT EQUAL SIGN. Again, this is no longer "standard".
;;;
;;; Another exceptional character is the NULL character (ASCII 0xFFFF).
;;; This is actually not a legal character in a C character string except
;;; as the last character, i.e., the terminator in null-terminated string.
;;;
;;; In a sense, we're kind of in the same fix as Unicode.  Our application has
;;; one encoding system, and within our application, characters are always
;;; unambiguously represented, and (what we'd like) text in external coding
;;; systems gets translated in and out without loss of data.
;;;
;;; How does Unicode do this?
;;;
;;; Here's the guideline, again from Glenn Adams:
;;;
;;;    Even when a Unicode process can display only a subset of Unicode
;;;    characters, it should still attempt to display characters outside of
;;;    supported subset, that is, it should be able to indicate to the user that
;;;    something is encoded there, but simply cannot be displayed.
;;;
;;;    .... It should indicate that some character data is there and interpret
;;;    what it can, e.g., whitespace characters.
;;;
;;;    Some suggestions for how to display undisplayable characters are ...
;;;    [pictures of: a special-purpose glyph with the hex code in it; a pair of
;;;    horizontal, parallel lines, called GETA MARK, as a substitute, and glyph
;;;    that's a black, horizontal blob, much like our blobs, called MEDIUM
;;;    SHADE, as a substitute.




;;;;  Thoughts on the Transition to a Coded Character Set: A discussion

;; (MHD 11/7/95)

;;; Problems of Unicode.
;;;
;;; The main difficulty is that there is no language tagging in Unicode.  This
;;; is mainly a problem because some of the Han characters (CJK) seen by C, J,
;;; or K people were unified as a single logical character.  Unicode theory
;;; states that the display of C, J, or K characters appropriately is a higher
;;; level problem, and not their concern..  However, the character set we have
;;; now, does solve this concern, as do other plain text encodings, and it does
;;; need to be solved in the opinion of most experts and users.  Essentially,
;;; this means that Unicode's idea of plain text is not really completely usable
;;; commodity.
;;;
;;; The Unicode approach to representing all of Korean, Japanese, and eventually
;;; Chinese, in text is with additional "rich text"-like markup.  If you have
;;; "rich text", even if it's around Unicode, you don't really succeed in having
;;; Unicode (plain) text.  How do you get text from cut buffers this way,
;;; for example?
;;;
;;; Additional problems: (1) we have a need for far fewer characters than
;;; Unicode supplies; (2) we have a lot of text already in our old format; ....
;;;
;;; Advantages:
;;;
;;; - interning
;;; - somewhat standard
;;; - gives us a superset of the characters we need, thus allowing "all the
;;;   languages of the world" to be stored and entered, at least if you can
;;;   get it into G2 -- coupled with Gamma Unitype, this could easily allow
;;;   anyone to type in (single lines) of text on any Windows 3.1, '95, or
;;;   Windows NT platform.
;;; - can interface to many Windows facilites, particularly in Windows NT 3.5.1,
;;;   but also in a growing number of software products
;;;
;;; The above are not fatal reasons.  We could bite the bullet and say we either
;;; (a) support CJK only via Unicode-unified Han, or (b) we could do our own
;;; simple rich text format to support distinct CJK characters in terms of
;;; viewing (assuming we continue rendering our own text), but just have Unicode
;;; plain text when we export.  Note that just doing (a) does not rule out other
;;; software, i.e., 3rd party tools, from adding rich-text type markup,
;;; including language tagging, and displaying the culturally correct glyphs for
;;; the unified Han characters.
;;;
;;; Note that we could also, when we expose the new character-code type,
;;; decide that the codes you get out of G2 text is Unicode.  We could
;;; also decide that the codes are whatever you parameterize them to be --
;;; i.e., we translate on the fly from the string to "your code" when
;;; you access a character.





;;;; How to Get to Unicode

;;; You will need on an ongoing bases to utilize the resources available through
;;; the following URL (universal resource locator):
;;;
;;;   ftp://unicode.org/pub/MappingTables
;;;
;;; This contains tables needed for translation to and from various national
;;; character sets, in particular, JIS X 0208 (Japanese) and KS C 5601 (Korean).
;;;




;;;; Alphabetic and Numeric Gensym Characters



;;; `Alphabetic-gensym-character-p' is true if the gensym character represented
;;; by character-or-character-code and escape-character? is alphabetic.

(defun-simple alphabetic-gensym-character-p
    (character-or-character-code escape-character?)
  (declare (eliminate-for-gsi-no-utf-g))
  (if escape-character?
      (case escape-character?
        (#\~ (alphanumericp character-or-character-code))
        (#\\ (or (lower-case-kanji-code-p character-or-character-code)        ; more?
                 (upper-case-kanji-code-p character-or-character-code))))
      (alpha-char-p character-or-character-code)))

;; It would be more elegant to define this in terms of two new macros,
;; alphabetic-special-character-p and alphabetic-kanji-code-p.

;; Consider defining this as a macro.



;;; `Numeric-gensym-character-p' is true if the gensym character represented
;;; by character-or-character-code and escape-character? is numeric.

(defun-simple numeric-gensym-character-p
    (character-or-character-code escape-character?)
  (declare (eliminate-for-gsi-no-utf-g))
  (if escape-character?
      (case escape-character?
        (#\\ (numeric-kanji-code-p character-or-character-code)))
      (digit-char-p character-or-character-code)))

;; Consider defining this as a macro.



;;; `Alphanumeric-gensym-character-p' is true if the gensym character represented
;;; by character-or-character-code and escape-character? is alphabetic or numeric.

(defun-simple alphanumeric-gensym-character-p
    (character-or-character-code escape-character?)
  (declare (eliminate-for-gsi-no-utf-g))
  (or (alphabetic-gensym-character-p character-or-character-code escape-character?)
      (numeric-gensym-character-p character-or-character-code escape-character?)))





;;;; Misc Character Operations



;;; `Gensym-character=' ...

(def-substitution-macro gensym-character=
    (character-or-character-code-1
      escape-character-1?
      character-or-character-code-2
      escape-character-2?)
  (cond
    ((and (null escape-character-1?) (null escape-character-2?))
     (char= character-or-character-code-1 character-or-character-code-2))
    (t
     (and (eql character-or-character-code-1 character-or-character-code-2)
          (eql escape-character-1? escape-character-2?)))))


;;; Escape-character-weight is a macro used for assigning weights to
;;; each of the four possible escape-character? values, as follows
;;;
;;;    @         1
;;;    nil        2
;;;    ~        3
;;;    \        4
;;;
;;; This is the sort ordering to be used when comparing two gensym
;;; characters having differing escape characters.

(defmacro escape-character-weight (escape-character?)
  `(case ,escape-character?
     (#\@ 1)
     ((nil) 2)
     (#\~ 3)
     (t 4)))

;; Sort order when comparing different complex characters:
;;
;;   @ chars   <   ascii chars   <   ~ chars  <  \ chars
;;
;; This is not the only way to do things, but it's reasonable
;; for now.  And it's stable.  (MHD 3/22/93)

;; IMPORTANT NOTE: There currently is no property that even
;;    a+{<any accent>} < b+{<any accent>} < c+{<any accent>} < ...
;; This is not a pretty story to tell users!  It could be solved with a bit
;; more coding.  I'm not sure if ISO-Latin1 encodings have that property.
;; This certainly doesn't provide ISO-Latin1 encoding order.  (MHD 3/24/93)

;; Comparison needs improvement for different character sets.  For example,
;;
;;    "A"
;;      <  "A<umlaut>"
;;      <  "A-in-JIS-character-set"
;;      <  "A-in-KS-character-set"
;;
;; is questionable!

;; Consider:
;;
;;   (1) when comparing unaccented and accented characters, apply char-lessp
;;   between two different base characters;
;;
;;   (2) if two base characters are the same, differentiate in a random but
;;   stable way, e.g., by applying char-lessp on the character after the ~; and
;;
;;   (3) when comparing the character after the ~, and it is known that we're
;;   comparing a special-character punctuation character with an Ascii
;;   character, consider all special-character punctuation characters to be
;;   NOT LESS THAN any Ascii characters, both alphanumerics and other
;;   punctuation chars
;;
;; (MHD 3/22/93)

;; Consider a variant in which base characters and all accented characters
;; are considered equal.  This is the preferred University of Chicago Manual
;; of Style alphabetical ordering convention.  (MHD 3/22/93)

;; What about comparing "ss" with German double-s ("sharf s")?! There's also
;; the ligatures (ae and oe guys)! (MHD 3/22/93)

;; This Needs user-level documentation.  This may ultimately have to be one of
;; several lessp predicates that users can employ, since different locales and
;; different applications will not be able to get by with only one sorting
;; order, at least not for long!  (MHD 3/22/93)

;; Another thing to do, especially if there are higher-level search and collate
;; routines, is to have the options of treating different types of white-space
;; equally.  (MHD 3/22/93)



;;; `Twrite-gensym-character' writes the gensym character designated by the args
;;; character-or-character-code and escape-character? in a
;;; twith-output-to-gensym-string dynamic extent, i.e., using twrite-char.

(def-substitution-macro twrite-gensym-character
    (character-or-character-code escape-character?)
  (cond
    ((null escape-character?)
     (twrite-char character-or-character-code))
    ((char= escape-character? '#\\)
     (twrite-kanji-character character-or-character-code))
    (t
     (twrite-char escape-character?)
     (twrite-char character-or-character-code))))

;; This macro cannot be used until after twrite-char is defined.


;;; `Make-gensym-character-string' creates and returns a new text string just
;;; long enough to contain the gensym character designated by the args
;;; character-or-character-code and escape-character?, and containing just that
;;; gensym character.

(defun-simple make-gensym-character-string
    (character-or-character-code escape-character?)
  (declare (eliminate-for-gsi-no-utf-g))
  (let (gensym-string)
    (cond
      ((null escape-character?)
       (setq gensym-string (obtain-simple-gensym-string 1))
       (setf (schar gensym-string 0) character-or-character-code))
      ((char= escape-character? '#\\)
       (setq gensym-string
             (obtain-simple-gensym-string
               (compute-gensym-string-length-of-kanji-character
                 character-or-character-code)))
       (let ((index 0))
         (declare (type fixnum index))
         (write-kanji-character-into-gensym-string
           character-or-character-code gensym-string index t)))
      (t
       (setq gensym-string (obtain-simple-gensym-string 2))
       (setf (schar gensym-string 0) escape-character?)
       (setf (schar gensym-string 1) character-or-character-code)))
    gensym-string))





;;;; Macros for Some Well-known Wide Characters


;;; Naming convention:
;;;
;;;   UNICODE-<name from UnicodeDataCurrent.txt with Hyphens>
;;;
;;; Note: the name is taken from the Unicode data file.  Note that despite the
;;; name "Unicode", these are actually the ISO 10646 names.  Usually they're the
;;; similar or the same, but sometimes they're different.  They always should
;;; mean the same thing.



;; 2028;LINE SEPARATOR;Zl;0;B;;;;;N;;;;;
;; 2029;PARAGRAPH SEPARATOR;Zp;0;B;;;;;N;;;;;

(defmacro unicode-line-separator ()
  '#x2028)

(defun unicode-line-separator-function ()
  (unicode-line-separator))                ; temporary, to deal with fwd. ref. prob.

(defmacro unicode-paragraph-separator ()
  '#x2029)

(defmacro unicode-ordinary-space ()
  '#x0020)


;; LF has a HEX code "A" (DEC code "10")
(defmacro line-feed-code ()
  '#x000A)



;; CR has a HEX code "D" (DEC code "13")

(defmacro return-code ()

  '#x000D)



(defmacro unicode-tab ()

  '#x0009)

(defun unicode-tab-function ()
  (unicode-tab))                        ; temporary, to deal with fwd. ref. prob.

(defmacro unicode-fixed-width-space ()
  ;; Best approximation for this concept is figure space. Review!
  ;; 2007;FIGURE SPACE;Zs;0;ES;<font variant> 0020;;;;N;;;;;
  #x2007)


(defmacro unicode-no-break-space ()
  '#x00A0)

(defmacro unicode-zero-width-space ()
  '#X200B)

(defmacro unicode-zero-width-no-break-space ()
  '#XFEFF)

(defmacro unicode-soft-hyphen ()
  '#x00AD)


;; 00A9;COPYRIGHT SIGN;So;0;ON;<+circled> 0043 <-circled>;;;;N;;;;;

(defmacro unicode-copyright-sign ()
  '#X00A9)


;; 00AE;REGISTERED SIGN;So;0;ON;<+circled> 0052 <-circled>;;;;N;REGISTERED TRADE MARK SIGN;;;;

(defmacro unicode-registered-sign ()
  '#X00AE)


;; 2122;TRADE MARK SIGN;So;0;ON;<+sup> 0054 004D <-sup>;;;;N;TRADEMARK;;;;

(defmacro unicode-trade-mark-sign ()
  '#x2122)

;; Currently, the file /bt/mhd50/UnicodeDataCurrent.txt has the unicode
;; character data that appears in comments. (MHD 2/8/96)




;; 0152;LATIN CAPITAL LIGATURE OE;Lu;0;L;;;;;N;LATIN CAPITAL LETTER O E;;;0153;
;; 0153;LATIN SMALL LIGATURE OE;Ll;0;L;;;;;N;LATIN SMALL LETTER O E;;0152;;0152

(defmacro unicode-capital-ligature-oe ()
  '#x0152)

(defmacro unicode-small-ligature-oe ()
  '#x0153)



;; 2022;BULLET;Po;0;ON;;;;;N;;;;;

(defmacro unicode-bullet ()
  '#x2022)


;; 0192;LATIN SMALL LETTER F WITH HOOK;Ll;0;L;;;;;N;LATIN SMALL LETTER SCRIPT F;;0191;;0191

(defmacro unicode-latin-small-letter-f-with-hook () ; adobe name: florin
  '#x0192)


(defmacro unicode-inverted-exclamation-point () 161)
(defmacro unicode-cent-sign () 162)
(defmacro unicode-pound-sign () 163)
(defmacro unicode-yen-sign () 165)
(defmacro unicode-left-pointing-double-angle-quotation-mark () 171)
(defmacro unicode-right-pointing-double-angle-quotation-mark () 187)
(defmacro unicode-inverted-question-mark () 191)

(defmacro unicode-euro-sign () '#x20AC)
(defmacro unicode-won-sign () '#x20A9) ; Korea
(defmacro unicode-new-sheqel-sign () '#x20AA) ; Israel
(defmacro unicode-french-franc-sign () '#x20A3) ; France



;;; How Unicode Maps to the Old Gensym Formatting Characters:
;;;
;;; (These were never exposed to users, but code that dealt with them will
;;; need intelligent transformation.  See doc for @-chars for rules on how
;;; these interface to the token reader.)
;;;
;;; Gensym @-character sequences and their Unicode equivalents:
;;;
;;;    @V   very thin space - Unicode Hair Space
;;;    @W   thin space - Unicode Thin Space
;;;    @X   en space - Unicode En Space
;;;    @Y   em space - Unicode Em Space
;;;
;;;    @R   permit line break here - Unicode Zero Width Space
;;;    @Q   do not permit line break here - Unicode Zero Width Joiner
;;;
;;;
;;; Unicode Reference Data:
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
;;;   200C;ZERO WIDTH NON-JOINER;Cc;0;ON;;;;;N;;;;;
;;;   200D;ZERO WIDTH JOINER;Cc;0;ON;;;;;N;;;;;

(defmacro unicode-hair-space ()                ; @V
  '#x200A)

(defmacro unicode-thin-space ()                ; @W
  '#x2009)

(defmacro unicode-en-space ()                ; @X
  '#x2002)

(defmacro unicode-em-space ()                ; @Y
  '#x2001)

(defmacro unicode-zero-width-joiner ()        ; @Q
  '#x200D)





;;;; Generating CJK <-> Unicode Maps


;;; After this and the following two sections are defined,
;;; `generate-cjk-unicode-map-modules' is used in development to generate the
;;; mapping files.  It generates the Lisp modules JISMAP and KSMAP.


;; The following is a generalized version of a simple static sparse vector
;; lookup, adapted from the kanji-font-cache-vector facility in FONTS.

;;; A `cjk code mapping vector' is used to map CJK national character set
;;; standard codes to other standards, especially Unicode.

(eval-when (:compile-toplevel :load-toplevel :execute)                        ; used in reader macro below
  (defmacro cjk-code-mapping-vector-length ()
    307))                                        ; some good prime

(defun make-cjk-code-mapping-vector ()
  (make-array (cjk-code-mapping-vector-length)
              :element-type t :initial-element nil))


(defvar-for-macro cjk-code-map-subvector-type '(simple-array (unsigned-byte 16) (*)))

(defmacro the-cjk-code-map-subvector (x)
  `(the ,cjk-code-map-subvector-type ,x))


;;; `NEW-Get-cjk-code-mapping-if-any' maps to the code corresponding to
;;; cjk-code.  This returns nil for an invalid code.

;;; The idea of this mapping scheme is to save a simple vector of vectors of
;;; 16-bit integers.  There will be one exact sized vector per bucket, and each
;;; code/cjk-code pair, i, will be kept as the ith/(i + 1)th element of the
;;; array.  This replaces an older scheme for storing the mapping vectors, and
;;; should take up about half as much space as under the old scheme.  NOTE: the
;;; older scheme is still in use for the previously existing CJK maps (for
;;; Japanese and Korean) and has not yet been phased out due to lack of time to
;;; completely finish that job; however, it's a farely straightforward job.
;;; [For the release pending. (MHD 4/9/99)]

(defmacro NEW-get-cjk-code-mapping-if-any
    (cjk-code cjk-code-mapping-vector)
  `(let* ((cjk-code ,cjk-code)
          (cjk-code-mapping-vector ,cjk-code-mapping-vector)
          (vector                        ; may not be null
            (svref cjk-code-mapping-vector
                   (modf-positive
                     cjk-code
                     #.(cjk-code-mapping-vector-length)))))
     (declare (type ,cjk-code-map-subvector-type vector))
     (loop with length fixnum = (length (the-cjk-code-map-subvector vector))
           for i from 0 below length by 2
           as code fixnum = (aref (the-cjk-code-map-subvector vector) i)
           when (=f code cjk-code)
             return (aref (the-cjk-code-map-subvector vector) (1+f i))
           ;; entries are sorted from smallest to largest code, so
           ;; exit early if code is already larger than our target:
           while (<f code cjk-code))))


;;; The code that follows is used only in development at the time of creating a
;;; CJK mapping file, namely by new-generate-cjk-to-unicode-map.

(defvar-for-macro current-cjk-code-mapping-notation-vector)

(defmacro emitting-cjk-code-mapping-code ((name stream) &body body)
  `(let ((current-cjk-code-mapping-notation-vector
           (make-array (cjk-code-mapping-vector-length))))
     (progn . ,body)
     (emit-final-cjk-code-mapping-code
       ,name ,stream current-cjk-code-mapping-notation-vector)))

(defun-for-macro emit-final-cjk-code-mapping-code (name stream notation-vector)
  (format stream
          "~%(defvar unicode-to-~a-map" name)
  (format stream
          "~% (optimize-constant ~%  '#.(let ((a (make-array ~d)))" ; i.e., a simple vector
          (cjk-code-mapping-vector-length))
  (loop for i from 0 below (cjk-code-mapping-vector-length)
        as sorted-entry = (sort (copy-list (aref notation-vector i))
                                #'< :key #'car)
        as length = (* (length sorted-entry) 2)
        do (format stream "~%       (setf (svref a ~d) (make-array ~d
 :element-type '(unsigned-byte 16)
 :initial-contents ~%        '("
                   i length)
           (loop with break-every-n = 4
                 with start-column = 10
                 for (code-a . code-b) in sorted-entry
                 as tick from 0
                 as break? = (= (mod tick break-every-n) 0)
                 do (cond
                      (break?
                       (unless (= tick 0)
                         (terpri stream)
                         (loop repeat start-column
                               do (write-char #\space stream))))
                      (t
                       (loop repeat 2 do (write-char #\space stream))))
                    (format stream "#x~x #x~x" code-a code-b))
           (format stream ")))"))
  (format stream "~%       a))")
  (format stream "~%)"))



;;; `Note-cjk-code-mapping' creates an entry at the designated cjk-code point
;;; for the corresponding code, if any.  Null codes should not be supplied.
;;;
;;; This must be called in an environment established by the
;;; emitting-cjk-code-mapping-code macro.
;;;
;;; At present, this is intended for use on static data structures: no memory
;;; reclamation is performed, and memory is allocated dynamically.  It is only
;;; used in development at the time of creating a CJK mapping file.

(defun-for-macro note-cjk-code-mapping
    (cjk-code corresponding-code)
  (push (cons cjk-code corresponding-code)
        (svref current-cjk-code-mapping-notation-vector
               (mod cjk-code (cjk-code-mapping-vector-length)))))



;; To test/see: Both functions below should emit the same thing, but illustrate
;; different aspects of this stuff.  Note that it should be the case that
;;
;;   (equalp (sample-emit-final-cjk-code-mapping-code)
;;           (sample-2-emit-final-cjk-code-mapping-code))
;;
;; The emitted sample code looks like this (with zero-length-array entries
;; elided with ...):
;;
;; (defvar unicode-to-FOO-map
;;  (optimize-constant
;;   '#.(let ((a (make-array 307)))
;;        ...
;;        (setf (svref a 1) (make-array 4 :element-type '(unsigned-byte 16) :initial-contents
;;         '(#x1 #x100  #x134 #x101)))
;;        ...
;;        (setf (svref a 10) (make-array 6 :element-type '(unsigned-byte 16) :initial-contents
;;         '(#xA #x10A  #x13D #x10B  #x270 #x10C)))
;;        a))
;; )
;;
;; After evaluating the resulting code, a sample session could look like this:
;;
;; >(new-get-cjk-code-mapping-if-any #x134 unicode-to-foo-map))
;; => 257 ; = #x101
;; >(new-get-cjk-code-mapping-if-any #x133 unicode-to-foo-map))
;; => NIL
;; >(new-get-cjk-code-mapping-if-any #x13d unicode-to-foo-map)
;; => 267 ; #x10b
;; >(new-get-cjk-code-mapping-if-any #x3A3 unicode-to-foo-map)
;; => NIL
;;
;; (MHD 4/9/99)

#+development
(defun sample-emit-final-cjk-code-mapping-code ()
 (let ((v (make-array (cjk-code-mapping-vector-length))))
   (setf (aref v 1) '((#x1 . #x100) (#x134 . #x101)))
   (setf (aref v 10)
         '((#xa . #x10a) (#x13d . #x10b) (#x270 . #x10c)))
   (emit-final-cjk-code-mapping-code 'foo *standard-output* v)))

#+development
(defun sample-2-emit-final-cjk-code-mapping-code ()
  (emitting-cjk-code-mapping-code ('foo *standard-output*)
    (loop for (code-a code-b)
              on '(#x1 #x100 #x134 #x101
                   #xa #x10a #x13d #x10b #x270 #x10c)
              by 'cddr
          do (note-cjk-code-mapping code-a code-b))))

#+development
(defun generate-cjk-unicode-map-modules ()
  (generate-jis-x-0208-to-unicode
    "/bt/mhd/trail/0132-unicode-resources/jis0208map.text" "jismap.lisp")
  (generate-ks-c-5601-to-unicode
    "/bt/mhd/trail/0132-unicode-resources/ksc5601map.text" "ksmap.lisp")
  (generate-ks-c-5601-to-unicode-2-0
    "/bt/mhd/trail/0132-unicode-resources/ksc5601map.text" "ksmap2.lisp")

  (generate-gb-2312-to-unicode                ; see notes (MHD 4/9/99)
    "/bt/mhd/trail/0132-unicode-resources/GB2312.TXT"
    "gbmap.lisp"
    "gbmapr.lisp"))

;; If necessary, in "/bt/mhd/trail/..." above, substitute mhd for the name of
;; your favorite sandbox with a trail module checked out.  (MHD 4/9/99)

;; The last form, which generates the gb-2312 mapping table, was added for
;; release pending on this day.  At the same time, the other forms were
;; corrected to find the files with pathnames that currently work for now.  Also
;; on this day I tested to see whether running this now would result in the same
;; files as are currently in the repository, and THE TEST FAILED: Some hand
;; edits had been done.  BEWARE!  Also note that one of the files, ksmap.lisp,
;; is not used, which just means we have gone with Unicode 2.0 for our Korean
;; mapping needs.  (MHD 4/9/99)
;; -- Update: I've modified generate-cjk-to-unicode-map to generate practically
;; equivalent code for JIS/KS map files.  I'll soon regenerate and commit
;; those maps based on these changes. (MHD 1/10/03)


#+development
(defparameter get-faster-readtime-for-generate-cjk-to-unicode-map-p t)

;; This is the new way -- generates initial values list, easier for Lisp to
;; swallow, especially on Harlequin and Allegro. -mhd/css, 5/3/02



#+development
(defun generate-cjk-to-unicode-map
    (input-file-name output-file-name
                     cjk-charset-name ; jis-x-0208
                     cjk-charset-number-of-codes ; number-of-jis-codes
                     file-header-string        ; jis-x-0208-to-unicode-header
                     mapping-retrieval-function
                     sparse-code-to-contiguous-mapping-function-or-macro
                     row-start row-end column-start column-end        ; of rect. code space
                     charset-short-name-if-offset-in-gensym-charset?
                     &optional hand-edits)
  (with-open-file (instream input-file-name)
    (with-open-file (outstream output-file-name :direction :output)
      (format outstream "~a" file-header-string)

      ;; The following will emit a "byte-vector-16", i.e., an array of 16-bit
      ;; unsigned bytes, accessed via aref-byte-vector-16.  Note that the
      ;; def. of byte-vector-16-aref is in UTILITIES0, but that shouldn't be a
      ;; problem as long as the emitted map file is loaded after that module.
      ;; Also, if desired, the def. could easily be moved.
      ;;
      ;; (defvar jis-x-0208-to-unicode-map
      ;;  (optimize-constant
      ;;   '#.(let ((mapping-array (make-array 6879 :element-type '(unsigned-byte 16))))
      ;;        (setf (byte-vector-16-aref mapping-array #x0) #x3000)
      ;;        ...
      ;;        (setf (byte-vector-16-aref mapping-array #x1ADE) #x7199)
      ;;        mapping-array)))

      (format outstream
              "~%(defconstant ~a-to-unicode-map" cjk-charset-name)
      (cond
        (get-faster-readtime-for-generate-cjk-to-unicode-map-p
         (format outstream
                 "~
 (optimize-constant '#.(make-array ~d :element-type '(unsigned-byte 16) :initial-contents '("
                 cjk-charset-number-of-codes)
         (loop with array = (make-array cjk-charset-number-of-codes :element-type '(unsigned-byte 16))
               with mapper = sparse-code-to-contiguous-mapping-function-or-macro
               with cjk-charset-code?
               with unicode
               do (multiple-value-setq (cjk-charset-code? unicode)
                    (funcall mapping-retrieval-function instream))
               while cjk-charset-code?
               do (setf (aref array (eval `(,mapper ,cjk-charset-code?))) unicode)
               finally
                 ;; Now deal with special "hand edits" not in Unicode's table: (MHD 1/12/03)
                 (loop for (u j) in hand-edits
                       as index = (eval `(,mapper ,j))
                       as previous-mapping? = (aref array index)
                       when previous-mapping?
                         do (format
                              t
                              "~%Overriding Unicode<->~a mapping. Was: U+~4,'0x <=> 0x~4,'0x; NOW: U+~4,'0x <=> 0x~4,'0x"
                              cjk-charset-name previous-mapping? j u j)
                       do (setf (aref array index) u))
                 ;; Now emit the final list of initial values:
                 (loop with elements-per-line = 10
                       for i from 0 below cjk-charset-number-of-codes
                       as element-count from 0
                       when (= (mod element-count elements-per-line) 0)
                         do (format outstream "~%   ")
                       do (format outstream " #x~x" (aref array i))))
         (format outstream "))))~%~%"))
        (t
         (format outstream
                 "~
 (optimize-constant
  '#.(let ((mapping-array (make-array ~d :element-type '(unsigned-byte 16))))"
                 cjk-charset-number-of-codes)
         (loop while (multiple-value-bind (cjk-charset-code? unicode)
                         (funcall mapping-retrieval-function instream)
                       (when cjk-charset-code?
                         (format
                           outstream
                           "~%       (setf (aref mapping-array (~a #x~X)) #x~X)" ; opt. not nec.
                           sparse-code-to-contiguous-mapping-function-or-macro
                           cjk-charset-code?
                           unicode)
                         t)))
         (format outstream "~%       mapping-array)))")
         (format outstream "~%~%")))
      ;; The long, drawn-out array reference that follows is equivalent to the
      ;; translator-specific version of byte-vector-16-aref, but that's defined
      ;; too late for our use.  The places where this is only needed at load or
      ;; read time are skipped for readability.  (MHD 3/6/96)
      ;; The following was fixed today to generate the code which had been
      ;; hand-edited for some time.  The intent of the change is to do the nil
      ;; check to a allow for the case of a a null mapping. (MHD 1/9/03)
      (format outstream "(defun-substitution-macro map-gensym-~a-to-unicode (gensym-~a)~
                         ~%  (let ((contiguous-code? (~(~a~) gensym-~a)))~
                         ~%    (if contiguous-code?~
                         ~%      (the (unsigned-byte 16)~
                         ~%           (aref (the (simple-array (unsigned-byte 16) (*)) ~a-to-unicode-map)~
                         ~%                 (the fixnum contiguous-code?))))))~%~%"
              cjk-charset-name cjk-charset-name
              sparse-code-to-contiguous-mapping-function-or-macro
              cjk-charset-name cjk-charset-name)

      ;; See below for short name explanation. (MHD 1/9/03)
      (if charset-short-name-if-offset-in-gensym-charset?
          (let ((short-name charset-short-name-if-offset-in-gensym-charset?))
            (format outstream "(defun-substitution-macro map-~a-to-unicode (~(~a~))~
                              ~%  (map-gensym-~(~a~)-to-unicode (~(~a~)-to-gensym-~(~a~) ~(~a~))))~%~%"
                    cjk-charset-name cjk-charset-name cjk-charset-name
                    short-name short-name cjk-charset-name))
          (format outstream "(defun-substitution-macro map-~a-to-unicode (~(~a~))~
                              ~%  (map-gensym-~(~a~)-to-unicode ~(~a~)))~%~%"
                  cjk-charset-name cjk-charset-name cjk-charset-name cjk-charset-name))

      ;; Now make mapping for the other way:
      (format outstream "(defvar unicode-to-~a-map~%" cjk-charset-name)
      (format outstream "  (make-cjk-code-mapping-vector))~%~%")
      ;; The following was fixed today to generate the code which had been
      ;; hand-edited for some time.  The intent of the change is to type-declare
      ;; the array reference to the X-to-unicode-map array. (MHD 1/9/03)
      (format outstream "(loop for row from #x~x to #x~x~
                         ~%   do (loop for column from #x~x to #x~x~
                         ~%        as cjk-code = (+f (ashf row 8) column)~
                         ~%        as contiguous-code? = (~a cjk-code)
                         ~%        when contiguous-code?~
                         ~%          do (set-cjk-code-mapping~
                         ~%               (aref (the (simple-array (unsigned-byte 16) (*)) ~a-to-unicode-map)~
                         ~%                 (the fixnum contiguous-code?))~
                         ~%               unicode-to-~a-map~
                         ~%               cjk-code)))~%~%"
              row-start row-end column-start column-end
              sparse-code-to-contiguous-mapping-function-or-macro
              cjk-charset-name
              cjk-charset-name)

      ;; The first (and currently only) example of this arg in practice is
      ;; unicode-jis-x-0208-mapping-hand-edits, q.v., below. (MHD 5/12/03)
      (when hand-edits
        (format outstream "~2%;; Hand-edits/overrides/many-to-one mappings:~%")
        (loop for (unicode cjk-code replaced-unicode do-not-map-back-p) in hand-edits
              unless do-not-map-back-p
                do (format t "~%Providing Secondary Unicode->~a mapping. Now: U+~4,'0x => 0x~4,'0x"
                           cjk-charset-name replaced-unicode cjk-code)
                   (format outstream "(set-cjk-code-mapping #x~4,'0x unicode-to-~a-map #x~4,'0x)~%"
                           replaced-unicode cjk-charset-name cjk-code))
        (format outstream "~%"))

      ;; The second form that follows was added, and then the following two
      ;; forms were modified, to produce exactly the same code as had been in
      ;; place due to hand-editing for quite some time. (MHD 1/9/03)
      (format outstream "(defun-substitution-macro map-unicode-to-gensym-~a (unicode)~
                         ~%  (get-cjk-code-mapping-if-any  unicode  unicode-to-~a-map))~%~%"
              cjk-charset-name cjk-charset-name)
      ;; If the short name is supplied non-nil, we assume a mapping function or
      ;; macro of the form gensym-x-to-x (where x is the short name) exists to
      ;; map from the gensym character set to the national character. (They're
      ;; the same for JIS, and a trivial offset mapping for KSC.) This change
      ;; was put in to allow us to generate the same code that's been there due
      ;; to hand-editing for some time. (MHD 1/9/03)
      (if charset-short-name-if-offset-in-gensym-charset?
          (let ((short-name charset-short-name-if-offset-in-gensym-charset?))
            (format outstream "(defun-substitution-macro map-unicode-to-~a (unicode)~
                              ~%  (let ((gensym-~(~a~)-code?~
                              ~%           (get-cjk-code-mapping-if-any  unicode  unicode-to-~a-map)))~
                              ~%    (if gensym-~(~a~)-code?~
                              ~%        (gensym-~(~a~)-to-~(~a~) gensym-~(~a~)-code?))))~%~%"
                    cjk-charset-name short-name cjk-charset-name
                    short-name short-name short-name short-name))
          (format outstream "(defun-substitution-macro map-unicode-to-~a (unicode)~
                            ~%  (map-unicode-to-gensym-~a unicode)) ; no distinction~%~%"
              cjk-charset-name cjk-charset-name)))))


;; The following is intended as a replacement for the above, but no time to do
;; all the retrofitting now. For now, just use it to get the new modules GBMAP
;; and GBMAPR.  (MHD 4/9/99)

#+development
(defun new-generate-cjk-to-unicode-map
    (input-file-name output-file-name reverse-output-file-name
                     cjk-charset-name
                     cjk-charset-number-of-codes
                     file-header-string
                     reverse-file-header-string
                     mapping-retrieval-function
                     sparse-code-to-contiguous-mapping-function-or-macro
                     row-start row-end column-start column-end)
  (with-open-file (instream input-file-name)
    (with-open-file (outstream output-file-name :direction :output)
      (format outstream "~a" file-header-string)
      (format outstream
              "~%(defconstant ~a-to-unicode-map" cjk-charset-name)
      (cond
        (get-faster-readtime-for-generate-cjk-to-unicode-map-p
         (format outstream
                 "
 (optimize-constant '#.(make-array ~d :element-type '(unsigned-byte 16) :initial-contents '("
                 cjk-charset-number-of-codes)
         (loop with array = (make-array cjk-charset-number-of-codes :initial-element #xFFFF :element-type '(unsigned-byte 16))
               with cjk-charset-code?
               with unicode
               do (multiple-value-setq (cjk-charset-code? unicode)
                    (funcall mapping-retrieval-function instream))
               while cjk-charset-code?
               do (setf (aref array
                              (eval
                                `(,sparse-code-to-contiguous-mapping-function-or-macro
                                    ,cjk-charset-code?)))
                        unicode)
               finally
                 (loop with elements-per-line = 10
                       for i from 0 below cjk-charset-number-of-codes
                       as element-count from 0
                       when (= (mod element-count elements-per-line) 0)
                         do (format outstream "~%   ")
                       do (format outstream " #x~X" (aref array i))))
         (format outstream "))))~%~%"))
        (t
         (format outstream
                 "
 (optimize-constant
  '#.(let ((mapping-array (make-array ~d :initial-element #xFFFF :element-type '(unsigned-byte 16))))"
                 cjk-charset-number-of-codes)
         (loop while (multiple-value-bind (cjk-charset-code? unicode)
                         (funcall mapping-retrieval-function instream)
                       (when cjk-charset-code?
                         (format
                           outstream
                           "~%       (setf (aref mapping-array #x~X) #x~X) ; #x~x" ; opt. not nec.
                           (eval                ; gross, but OK for this seldom-used code
                             `(,sparse-code-to-contiguous-mapping-function-or-macro
                                 ,cjk-charset-code?))
                           unicode
                           cjk-charset-code?)
                         t)))
         (format outstream "~%       mapping-array)))")
         (format outstream "~%~%")))
      (format outstream "(defun-substitution-macro map-~a-to-unicode (~a)~
                         ~% (let ((index (~a ~a)) (code 0))~
                         ~%  (declare (type fixnum index code))~
                         ~%  (when (<=f 0 index ~d)~
                         ~%   (setq code
                         ~%      (the (unsigned-byte 16)~
                         ~%           (aref (the (simple-array (unsigned-byte 16) (*)) ~a-to-unicode-map)~
                         ~%                 (the fixnum index))))~
                         ~%   (if (=f code #xFFFF) nil code))))~%~%"
              cjk-charset-name cjk-charset-name
              sparse-code-to-contiguous-mapping-function-or-macro cjk-charset-name ; (fn arg)
              (- cjk-charset-number-of-codes 1)        ; last valid code
              cjk-charset-name))
    (with-open-file (outstream reverse-output-file-name :direction :output)
      (format outstream "~a" reverse-file-header-string)
      (emitting-cjk-code-mapping-code (cjk-charset-name outstream)
         (loop for row from row-start to row-end
               do (loop for column from column-start to column-end
                        as cjk-code = (+ (ash row 8) column)
                        as contiguous-code?
                           = (eval        ; gross! (but only used every few years)
                               `(,sparse-code-to-contiguous-mapping-function-or-macro
                                   ,cjk-code))
                        when contiguous-code?
                          do (note-cjk-code-mapping cjk-code contiguous-code?))))
      (terpri outstream) (terpri outstream)
      (format outstream "~%~%(defun-substitution-macro map-unicode-to-~a (unicode)~
                         ~%  (NEW-get-cjk-code-mapping-if-any  unicode  unicode-to-~a-map))~%~%"
              cjk-charset-name cjk-charset-name)

      )))

;; (Code moved from here to earlier in this module.) (MHD 4/9/99)

;;; `Get-cjk-code-mapping-if-any' maps to the code corresponding to cjk-code.

;;; This returns nil for an invalid code.

(defmacro get-cjk-code-mapping-if-any
          (cjk-code cjk-code-mapping-vector)
  `(let ((cjk-code ,cjk-code)
         (cjk-code-mapping-vector ,cjk-code-mapping-vector))
     (loop as l on (svref cjk-code-mapping-vector
                          (modf-positive
                            cjk-code
                            #.(cjk-code-mapping-vector-length)))
                by 'cddr
           when (=f (car l) cjk-code)
             return (cadr l))))


;;; `Set-cjk-code-mapping' creates an entry at the designated cjk-code point
;;; for the corresponding code, if any.  If the code is nil, this makes the
;;; cjk-code point invalid.
;;;
;;; At present, this is intended for use on static data structures: no memory
;;; reclamation is performed, and memory is allocated dynamically.

(defun-simple set-cjk-code-mapping
    (cjk-code cjk-code-mapping-vector corresponding-code?)
  (with-permanent-allocation                ; for now, never removed once allocated
    (setf (getf (svref cjk-code-mapping-vector
                       (modf-positive
                         cjk-code
                         #.(cjk-code-mapping-vector-length)))
                cjk-code)
          corresponding-code?)))



;;;; Unicode <-> JIS0208 Mapping



;;; `Generate-jis-x-0208-to-unicode' creates a file that defvar's
;;; generate-jis-x-0208-to-unicode as an array number-of-jis-codes elements in
;;; length such that JIS codes mapped to their contiguous indices will index
;;; their corresponding Unicode.  This is a #+development facility, used only
;;; at development time to generate a data/source file.

;;; The first few lines look like
;;;
;;;   (defvar jis-x-0208-to-unicode-map (make-array 6879))
;;;
;;;   (setf (byte-vector-16-aref jis-x-0208-to-unicode-map #x0) #x3000)
;;;   (setf (byte-vector-16-aref jis-x-0208-to-unicode-map #x1) #x3001)
;;;
;;; and so the file continues with (6879 - 2) additional setf forms.

#+development
(defvar jis-x-0208-to-unicode-header
  (format
    nil "~a~%~a~%~%~a~%~%~a~%~a~%~%~a~%~%"
    ";; -*- mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-"
    "(in-package \"AB\")"

    ";;;; Module JISMAP"

    ";;; Copyright (c) 1986 - 2017 Gensym Corporation."
    ";;; All Rights Reserved."

    ";; (Automatically Generated File from Code in CHARACTERS)"))



;;; The parameter `unicode-jis-x-0208-mapping-hand-edits' is supplied to
;;; generate-cjk-to-unicode-map as hand-edits.  This fixes the mapping problem
;;; described in suggestion HQ-4435582 "update the mapping tables for Japanese
;;; character sets".  Note that the discussion and mappings came from the
;;; following web page:
;;;
;;;    http://homepage2.nifty.com/hobbit/english/html/jcode.html
;;;
;;; The JIS codes from that page were in the JIS EUC form.  We need them to be
;;; in hex form. To convert from the JIS hex form, we simply subtract #x8080.
;;;
;;; Caveats:
;;;
;;;   (1) note that this began being used for G2/GSI/TW 7.0, introducing a minor
;;;   discontinuity in mapping from earlier versions.  We don't believe users
;;;   will be bothered by this, if it's noticed at all.
;;;
;;;   (2) it would probably be more correct to not do this for all JIS-X-0208
;;;   mappings, but to only do this as special handling of the various
;;;   encodings.  According emailed advice from someone on the web who commented
;;;   (see below), the Unicode mappings are actually probably OK for "pure"
;;;   JIS-X-0208.  However, since we don't strictly speaking handle the multiple
;;;   character sets in such a pure manner, this is a more practical approach, I
;;;   feel. (MHD 5/1/03)

(defparameter unicode-jis-x-0208-mapping-hand-edits
  ;; format:
  ;;   ( { (unicode JIS-X-0208-code replaced-unicode-mapping [do-not-map-back-p])
  ;;       ; JIS-hex: Unicode Name -- replacing: replacement name (unicode)
  ;;      } )
  ;;
  ;; do-not-map-back-p: is nil by default; if specified non-nil, this means not
  ;; to provide a secondary mapping from the replaced character code back to the
  ;; original JIS code.
  '((#xff3c #.(- #xa1c0 #x8080) #x005C t) ; 0x2140: Fullwidth Reverse Solidus -- replacing: Reverse Solidus (U+005C) [*]
    (#xff5e #.(- #xa1c1 #x8080) #x301C)        ; 0x2141: Fullwidth Tilde -- replacing: Wave Dash (U+301C)
    (#x2225 #.(- #xa1c2 #x8080) #x2016)        ; 0x2142: Parallel To -- replacing: Double Vertical Line (U+2016)
    (#xff0d #.(- #xa1dd #x8080) #x2212)        ; 0x215D: Fullwidth Hyphen-Minus -- replacing: Minus Sign (U+2212),
    (#xffe0 #.(- #xa1f1 #x8080) #x00A2)        ; 0x2171: Fullwidth Cent Sign -- replacing: Cent Sign (U+00A2)
    (#xffe1 #.(- #xa1f2 #x8080) #x00A3)        ; 0x2172: Fullwidth Pound Sign -- replacing: Pound Sign (U+00A3)
    (#xffe2 #.(- #xa2cc #x8080) #x00AC))) ; 0x224C: Fullwidth Not Sign -- replacing: Not Sign (U+00AC)

;; [*]: This mapping of #x005C was never actually used before in the unicode =>
;; JIS direction, since codes less than 128 were/are never actually in used by
;; our transcoding software in practice.  They're just sent straight through.
;; This means, namely, that U+005C would never have been actually mapped to
;; fullwidth reverse solidus by the transcoding layer, and still won't, because
;; of the low code and also that we're tagging this
;; do-not-map-back-p. Otherwise, it would interfere with the customary
;; equivalence between normal ascii \ and Japanese Yen; i.e., when converting to
;; JIS-EUC or Shift-JIS, the appropriate conversion is: U+005c -> 0x5c is more
;; appropriate.  Note, too, that the glyph/display for U+005c is Yen Sign in the
;; Japanese version of MS Windows (though never in G2). (MHD 5/12/03)



;;; Get-jis-x-0208-entry-from-line-if-any is a very simple parser for a line
;;; from the Unicode JIS mapping file.  It returns either nil (for a comment
;;; line or blank line), or else three values, shift-jis-code, jis-code, and
;;; unicode, indicating that these three codes are equivalent in their
;;; respective character sets/encodings according to Unicode han unification
;;; rules.
;;;
;;; We assume a line is either blank or looks either like
;;;
;;;    # ....
;;;
;;; or like
;;;
;;;    0xHHHH<tab>0xHHHH<tab>0xHHHH ....
;;;
;;; where H is a hexadecimal digit, <tab> is the ascii Tab character, and
;;; ellipsis indicates ellision of arbitrary characters.
;;;
;;; This is not a robust parser, but works for the 8 March 1994 version of the
;;; Unicode JIS X 0208 to Unicode mapping table file.
;;;
;;; Example:
;;;
;;;   (get-jis-x-0208-entry-from-line-if-any
;;;     "0x8140        0x2121        0x3000        # IDEOGRAPHIC SPACE ")
;;;
;;;   => 33088 8481 12288   ; i.e., #x8140 #x2121 #x3000

#+development
(defun get-jis-x-0208-entry-from-line-if-any (line)
  (if (and (>f (length line) 0)
           (not (char= (char line 0) #\#)))
      (values
        (parse-integer line :start 2 :end 6 :radix 16)
        (parse-integer line :start 9 :end 13 :radix 16)
        (parse-integer line :start 16 :end 20 :radix 16))))

;; This has been made to work with the file identified as follows:
;;            Name:             JIS X 0208 (1990) to Unicode
;;            Unicode version:  1.1
;;            Table version:    0.9
;;            Table format:     Format A
;;            Date:             8 March 1994
;;            Authors:          Glenn Adams <glenn@metis.com>
;;                         John H. Jenkins <John_Jenkins@taligent.com>


#+development
(defun jis-x-0208-mapping-retrieval-function (instream)
  (loop for line? = (read-line instream nil nil)
        while line?
        do (multiple-value-bind (shift-jis-code?  jis-code  unicode)
               (get-jis-x-0208-entry-from-line-if-any line?)
             (when shift-jis-code?
               (return (values jis-code unicode))))))


#+development
(defun generate-jis-x-0208-to-unicode
    (input-file-name output-file-name)
  (generate-cjk-to-unicode-map
    input-file-name output-file-name
    'jis-x-0208
    number-of-jis-codes
    jis-x-0208-to-unicode-header
    'jis-x-0208-mapping-retrieval-function
    'gensym-jis-code-to-contiguous
    jis-high-byte-min jis-high-byte-max
    jis-low-byte-min jis-low-byte-max
    nil
    unicode-jis-x-0208-mapping-hand-edits))



;;; The macro `map-JIS-X-0208-to-unicode' is defined in JISMAP, a module
;;; automatically generated by development code above.  It returns the Unicode
;;; corresponding to the the argument Gensym JIS-X-0208 code, if any; otherwise,
;;; nil.  Note that Gensym JIS-X-0208 is not necessarily the same as JIS-X-0208,
;;; but it is trivial to convert from one to the other: see gensym-jis-to-jis
;;; and jis-to-gensym-jis.

;;; The macro `map-unicode-to-JIS-X-0208' is also defined in JISMAP.  It returns
;;; the Gensym JIS-X-0208 code corresponding to unicode, if any; otherwise, nil.






;;;; Unicode <-> GB2312 Mapping


;;; The character set GB 2312-80 is defined by the Peoples Republic of China for
;;; Simplified Chinese.



;;; `Generate-gb-2312-to-unicode' creates two modules, one for the gb-code =>
;;; unicode direction, and the other for the reverse direction.  The first file
;;; defvar's an array number-of-contiguous-gb2312-codes elements in length such that GB2312
;;; codes mapped to their contiguous indices will index their corresponding
;;; Unicode.  This is a #+development facility, used only at development time to
;;; generate a data/source file.

#+development
(defvar gb-2312-to-unicode-header
  (format
    nil "~a~%~a~%~%~a~%~%~a~%~a~%~%~a~%~%"
    ";; -*- mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-"
    "(in-package \"AB\")"

    ";;;; Module GBMAP"

    ";;; Copyright (c) 1986 - 2017 Gensym Corporation."
    ";;; All Rights Reserved."

    ";; (Automatically Generated File from Code in CHARACTERS)"))

#+development
(defvar unicode-to-gb-2312-header
  (format
    nil "~a~%~a~%~%~a~%~%~a~%~a~%~%~a~%~%"
    ";; -*- mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-"
    "(in-package \"AB\")"

    ";;;; Module GBMAPR"

    ";;; Copyright (c) 1986 - 2017 Gensym Corporation."
    ";;; All Rights Reserved."

    ";; (Automatically Generated File from Code in CHARACTERS)"))




;;; Get-gb-2312-entry-from-line-if-any is a very simple parser for a line from
;;; the Unicode GB2312 mapping file.  It returns either nil (for a comment line
;;; or blank line), or else two values, gb2312-code and unicode, indicating that
;;; these two codes are equivalent in their respective character sets/encodings
;;; in accordance with Unicode han unification rules.
;;;
;;; We assume a line is either blank or looks either like
;;;
;;;    # ....
;;;
;;; or like
;;;
;;;    0xHHHH<tab>0xHHHH ....
;;;
;;; where H is a hexadecimal digit, <tab> is the ascii Tab character, and
;;; ellipsis indicates ellision of arbitrary characters.
;;;
;;; This is not a robust parser, but works for the 6 December 1993 version of
;;; the Unicode GB2312-80 to Unicode mapping table file.
;;;
;;; Example:
;;;
;;;   (get-gb-2312-entry-from-line-if-any
;;;     "0x2121        0x3000        # IDEOGRAPHIC SPACE")
;;;
;;;   => 8481 12288   ; i.e., #x2121 #x3000

#+development
(defun get-gb-2312-entry-from-line-if-any (line)
  (if (and (>f (length line) 0)
           (not (char= (char line 0) #\#)))
      (values
        (parse-integer line :start 2 :end 6 :radix 16)
        (parse-integer line :start 9 :end 13 :radix 16))))

;; This has been made to work with the file identified as follows:
;;        Name:             GB2312-80 to Unicode table (complete, hex format)
;;        Unicode version:  1.1
;;        Table version:    0.0d2
;;        Table format:     Format A
;;        Date:             6 December 1993
;;        Author:           Glenn Adams <glenn@metis.com>
;;                     John H. Jenkins <John_Jenkins@taligent.com>


#+development
(defun gb-2312-mapping-retrieval-function (instream)
  (loop for line? = (read-line instream nil nil)
        while line?
        do (multiple-value-bind (gb2312-code? unicode)
               (get-gb-2312-entry-from-line-if-any line?)
             (when gb2312-code?
               (return (values gb2312-code? unicode))))))


#+development
(defun generate-gb-2312-to-unicode
    (input-file-name output-file-name reverse-output-file-name)
  (NEW-generate-cjk-to-unicode-map
    input-file-name output-file-name reverse-output-file-name
    'gb-2312
    number-of-contiguous-gb2312-codes
    gb-2312-to-unicode-header unicode-to-gb-2312-header
    'gb-2312-mapping-retrieval-function
    'gensym-gb2312-code-to-contiguous
    gb-high-byte-min gb-high-byte-max
    gb-low-byte-min gb-low-byte-max))



;;; The macro `map-GB-2312-to-unicode' is defined in GBMAP, a module
;;; automatically generated by development code above.  It returns the Unicode
;;; corresponding to the the argument Gensym GB-2312 code, if any; otherwise,
;;; nil.

;;; The macro `map-unicode-to-GB-2312' is defined in GBMAPR.  It returns the
;;; Gensym GB-2312 code corresponding to unicode, if any; otherwise, nil.






;;;; Unicode <-> KSC5601 Mapping



;;; `Generate-ks-c-5601-to-unicode' creates a file that defvar's
;;; generate-ks-c-5601-to-unicode as an array number-of-KSC-codes elements in
;;; length such that KSC codes mapped to their contiguous indices will index
;;; their corresponding Unicode.  This is a #+development facility, used only
;;; at development time to generate a data/source file.

;;; The first few lines look like
;;;
;;;   (defvar ks-c-5601-to-unicode-map (make-array 6879))
;;;
;;;   (setf (byte-vector-16-aref ks-c-5601-to-unicode-map #x0) #x3000)
;;;   (setf (byte-vector-16-aref ks-c-5601-to-unicode-map #x1) #x3001)
;;;
;;; and so the file continues with (6879 - 2) additional setf forms.

#+development
(defvar ks-c-5601-to-unicode-header
  (format
    nil "~%~a~%~a~%~%~a~%~%~a~%~a~%~%~a~%~%"
    ";; -*- mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-"
    "(in-package \"AB\")"

    ";;;; Module KSMAP"

    ";;; Copyright (c) 1986 - 2017 Gensym Corporation."
    ";;; All Rights Reserved."

    ";; (Automatically Generated File from Code in CHARACTERS)"))

#+development
(defun ks-c-5601-mapping-retrieval-function (instream)
  (loop for line? = (read-line instream nil nil)
        while line?
        do (multiple-value-bind (ksc-code? unicode)
               (get-ks-c-5601-entry-from-line-if-any line?)
             (when ksc-code?
               (return (values (ksc-to-gensym-ksc ksc-code?) unicode))))))


#+development
(defun generate-ks-c-5601-to-unicode
    (input-file-name output-file-name)
  (generate-cjk-to-unicode-map
    input-file-name output-file-name
    'ks-c-5601
    number-of-KSC-codes
    ks-c-5601-to-unicode-header
    'ks-c-5601-mapping-retrieval-function
    'gensym-ksc-code-to-contiguous
    ksc-high-byte-min ksc-high-byte-max
    (+ ksc-low-byte-min KSC-low-byte-offset)
    (+ ksc-low-byte-max KSC-low-byte-offset)
    'ksc))

;; The above approach will result in the need to execute 6,879 setf forms at
;; startup time.  It would be better to just arrange to lay out the the data
;; structure in the binary image!
;;
;; For space efficiency, later make this into a data structure that packs
;; together the 16-integer elements, rather than a simple vector of general
;; elements!
;;
;; For both reasons, probably a byte array with custom access methods should be
;; implemented. (MHD 11/10/95)





;;; The macro `map-KS-C-5601-to-unicode' is defined in KSMAP, a module
;;; automatically generated by development code above.  It returns the Unicode
;;; corresponding to the the argument Gensym KS-C-5601 code, if any; otherwise,
;;; nil.  Note that Gensym KS-C-5601 is not necessarily the same as KS-C-5601,
;;; but it is trivial to convert from one to the other: see gensym-KSC-to-KSC
;;; and KSC-to-gensym-KSC.

;;; The macro `map-unicode-to-KS-C-5601' is also defined in KSMAP.  It returns
;;; the Gensym KS-C-5601 code corresponding to unicode, if any; otherwise, nil.






;;;; Unicode-2-0 <-> KSC5601 Mapping



;;; `Generate-ks-c-5601-to-Unicode-2-0' creates a file that defvar's
;;; generate-ks-c-5601-to-Unicode-2-0 as an array number-of-KSC-codes elements in
;;; length such that KSC codes mapped to their contiguous indices will index
;;; their corresponding Unicode-2-0.  This is a #+development facility, used only
;;; at development time to generate a data/source file.

;;; The first few lines look like
;;;
;;;   (defvar ks-c-5601-to-Unicode-2-0-map (make-array 6879))
;;;
;;;   (setf (byte-vector-16-aref ks-c-5601-to-Unicode-2-0-map #x0) #x3000)
;;;   (setf (byte-vector-16-aref ks-c-5601-to-Unicode-2-0-map #x1) #x3001)
;;;
;;; and so the file continues with (6879 - 2) additional setf forms.

#+development
(defvar ks-c-5601-to-Unicode-2-0-header
  (format
    nil "~%~a~%~a~%~%~a~%~%~a~%~a~%~%~a~%~%"
    ";; -*- mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-"
    "(in-package \"AB\")"

    ";;;; Module KSMAP2"

    ";;; Copyright (c) 1986 - 2017 Gensym Corporation."
    ";;; All Rights Reserved."

    ";; (Automatically Generated File from Code in CHARACTERS)"))

;;; Get-ks-c-5601-entry-from-line-if-any is a very simple parser for a line from
;;; the Unicode-2-0 KSC mapping file.  It returns either nil (for a comment line or
;;; blank line), or else three values, ksc-code and Unicode-2-0, indicating that
;;; these three codes are equivalent in their respective character
;;; sets/encodings according to Unicode-2-0 han unification rules.
;;;
;;; We assume a line is either blank or looks either like
;;;
;;;    # ....
;;;
;;; or like
;;;
;;;    0xHHHH<tab>0xHHHH<tab># <Unicode-2-0 name>
;;;
;;; where H is a hexadecimal digit, <tab> is the ascii Tab character, and
;;; ellipsis indicates ellision of arbitrary characters.  Note that <Unicode-2-0
;;; name> is abbreviated in certain cases; see comments at the top of the file
;;; for an explanation.
;;;
;;; This is not a robust parser, but works for the 8 March 1994 version of the
;;; Unicode-2-0 KS C 5601 to Unicode-2-0 mapping table file.
;;;
;;; Example:
;;;
;;;   (get-ks-c-5601-entry-from-line-if-any
;;;     "0x2121        0x3000        # IDEOGRAPHIC SPACE")
;;;
;;;   => 8481 12288   ; i.e., #x2121 #x3000

#+development
(defun get-ks-c-5601-entry-from-line-if-any (line)
  (if (and (>f (length line) 0)
           (not (char= (char line 0) #\#)))
      (values
        (parse-integer line :start 2 :end 6 :radix 16)
        (parse-integer line :start 9 :end 13 :radix 16))))

;; This has been made to work with the file identified as follows:
;;
;;        Name:             KSC5601 to Unicode table
;;        Unicode version:  1.1
;;        Table version:    0.0d2
;;        Table format:     Format A
;;        Date:             6 December 1993
;;        Authors:          Glenn Adams <glenn@metis.com>
;;                     John H. Jenkins <John_Jenkins@taligent.com>
;;
;; but the Unicode 1.1 codes for Hangul from this file have been replaced by
;; Unicode 2.0 codes for Hangul according to the file HANGUL.TXT, which has
;; this header:
;;
;;   Korean Hangul Encoding Conversion Table
;;
;;   ---------------------------------------------------------------------------
;;   Date   : Oct 04, 1995
;;   Author : K.D.Chang    <a-kchang@microsoft.com>
;;            In Sook Choi <ischoi@microsoft.com>
;;            Jung Ho Kim  <junghok@microsoft.com>
;;   ---------------------------------------------------------------------------


;; The following defvar's hangul-character-table.  It assume that the file
;; "hangul.lisp" (possibly with an associated compiled binary file) contains
;; the definition with all the data.  The file hangul.lisp was created "by
;; hand" (well, maybe using keyboard macros) from the file HANGUL.TXT).  Note
;; that as of May, 1997, the files referred to here are found in the repository
;; under trail/0132-unicode-resources/.  (MHD 5/10/97)

#+development
(defun initialize-hangul-character-table-if-necessary ()
  (unless (boundp 'hangul-character-table) ; see note above about pathname! (MHD 4/9/99)
    (load "/bt/mhd/trail/0132-unicode-resources/hangul.lisp"))
  (unless (boundp 'hangul-character-table)
    (cerror "proceed anyway" "Initialization of hangul-character-table failed!")))


#+development
(defun map-to-unicode-2-0-hangul (ksc-code unicode-1-1)
  (declare (ignore ksc-code)
           (special hangul-character-table))
  (initialize-hangul-character-table-if-necessary)
  (loop with unicode-1-1?
        with unicode-2-0?
        for entry in hangul-character-table
        do (setf unicode-1-1? (nth 5 entry))
           (setf unicode-2-0? (nth 6 entry))
        when (eql unicode-1-1? unicode-1-1)
          return unicode-2-0?))                ; never nil in practice


#+development
(defun unicode-2-ks-c-5601-mapping-retrieval-function (instream)
  (loop for line? = (read-line instream nil nil)
        while line?
        do (multiple-value-bind (ksc-code? unicode)
               (get-ks-c-5601-entry-from-line-if-any line?)
             (when ksc-code?
               (return (values (ksc-to-gensym-ksc ksc-code?)
                               (or (map-to-unicode-2-0-hangul
                                     ksc-code? unicode)
                                   unicode)))))))


#+development
(defun generate-ks-c-5601-to-unicode-2-0
    (input-file-name output-file-name)
  (generate-cjk-to-unicode-map
    input-file-name output-file-name
    'ks-c-5601
    number-of-KSC-codes
    ks-c-5601-to-Unicode-2-0-header
    'unicode-2-ks-c-5601-mapping-retrieval-function
    'gensym-ksc-code-to-contiguous
    #x21        ; #x217f..#x21dd
    #x7f
    (+ #x21 KSC-low-byte-offset)
    (+ #x7e KSC-low-byte-offset)
    'ksc))

;; The above approach will result in the need to execute 6,879 setf forms at
;; startup time.  It would be better to just arrange to lay out the the data
;; structure in the binary image!
;;
;; For space efficiency, later make this into a data structure that packs
;; together the 16-integer elements, rather than a simple vector of general
;; elements!
;;
;; For both reasons, probably a byte array with custom access methods should be
;; implemented. (MHD 11/10/95)





;;; The macro `map-KS-C-5601-to-unicode' is defined in KSMAP, a module
;;; automatically generated by development code above.  It returns the Unicode
;;; corresponding to the the argument Gensym KS-C-5601 code, if any; otherwise,
;;; nil.  Note that Gensym KS-C-5601 is not necessarily the same as KS-C-5601,
;;; but it is trivial to convert from one to the other: see gensym-KSC-to-KSC
;;; and KSC-to-gensym-KSC.

;;; The macro `map-unicode-to-KS-C-5601' is also defined in KSMAP.  It returns
;;; the Gensym KS-C-5601 code corresponding to unicode, if any; otherwise, nil.





;;;; Hebrew (esp. Hebrew Font) Information Used in FONTS


;;; The Hebrew fonts used for G2/Telewindows include the Hebrew letters, letter
;;; combinations, nikud diacritics, Hebrew punctuation, and Hebrew precomposed
;;; characters and letterlike forms.  In addition Gensym supports the Euro sign
;;; (EUR, or European currency symbol) through the Hebrew font, since it happens
;;; to be new enough and filled out enough to support it.  In addition, various
;;; other European characters are here supported, in particular characters needed
;;; for Turkish support.

;; Note: have to add "Hebrew" punctuation, e.g., all punctuation from ISO
;; 8859-8, various kinds of quote marks used for Hebrew, as well as the New
;; Sheckel (currency) symbol.  These should be able to fit in the ~30 spaces
;; left below the Euro sign.

;; Starts with nikud, but after trope:
(defconstant unicode-hebrew-character-block-start #x05b0)
(defconstant unicode-hebrew-character-block-end #x05F4)

;; Starts with one (1) character in Unicode's pipeline:
(defconstant unicode-hebrew-precomposed-character-block-start #xFB1D)
(defconstant unicode-hebrew-precomposed-character-block-end #xFB4F)

;; Additional characters for Turkish:
;;
;; These characters previously not accessible from built-in fonts; other Turkish
;; characters were already accessible.  (MHD 10/22/99)
;;
;; 011E;LATIN CAPITAL LETTER G WITH BREVE;Lu;0;L;0047 0306;;;;N;LATIN CAPITAL LETTER G BREVE;;;011F;
;; 011F;LATIN SMALL LETTER G WITH BREVE;Ll;0;L;0067 0306;;;;N;LATIN SMALL LETTER G BREVE;;011E;;011E
;; 0130;LATIN CAPITAL LETTER I WITH DOT ABOVE;Lu;0;L;0049 0307;;;;N;LATIN CAPITAL LETTER I DOT;;;0069;
;;   (NOTE: Turkish uppercase version of  'i', i.e., I+<dot>, so lowercase is 'i'.)
;; -- UPDATE: These are also necessary Turkish characters, but were left out of the initial commit in
;; error:  (MHD 1/12/00)
;;
;; 015C;LATIN CAPITAL LETTER S WITH CIRCUMFLEX;Lu;0;L;0053 0302;;;;N;LATIN CAPITAL LETTER S CIRCUMFLEX;;;015D;
;; 015D;LATIN SMALL LETTER S WITH CIRCUMFLEX;Ll;0;L;0073 0302;;;;N;LATIN SMALL LETTER S CIRCUMFLEX;;015C;;015C
;; 015E;LATIN CAPITAL LETTER S WITH CEDILLA;Lu;0;L;0053 0327;;;;N;LATIN CAPITAL LETTER S CEDILLA;;;015F;
;; 015F;LATIN SMALL LETTER S WITH CEDILLA;Ll;0;L;0073 0327;;;;N;LATIN SMALL LETTER S CEDILLA;;015E;;015E
;; 01E6;LATIN CAPITAL LETTER G WITH CARON;Lu;0;L;0047 030C;;;;N;LATIN CAPITAL LETTER G HACEK;;;01E7;
;; 01E7;LATIN SMALL LETTER G WITH CARON;Ll;0;L;0067 030C;;;;N;LATIN SMALL LETTER G HACEK;;01E6;;01E6
;;
;; NOTE: Of these, the glyphs 015C, 015D, 01E6, 01E7 are not currently supported
;; by our Hebrew font.  Meanwhile, they have been suggested as required for
;; Turkish through one issue, but that status is doubtful according to my
;; preliminary research.  (MHD 1/12/99)

(defmacro hebrew-unicode-p (unicode)
  `(let ((unicode ,unicode))
     ,(ez-generate-binary-search-code
        'unicode
        `((,unicode-hebrew-character-block-end
             (>=f unicode ,unicode-hebrew-character-block-start))
          (,(unicode-euro-sign)
            (=f unicode ,(unicode-euro-sign)))
          (,(unicode-new-sheqel-sign)
            (=f unicode ,(unicode-new-sheqel-sign)))
          (,(unicode-french-franc-sign)
            (=f unicode ,(unicode-french-franc-sign)))
          (,#x011f (>=f unicode #x011e)) ; G/g with Breve (Turkish)
          (,#x0130 (=f unicode #x0130))  ; Dotted Capital I (Turkish)
          (,#x015f (>=f unicode #x015c)) ; S/s with circumflex, cedilla (Turkish)
          (,#x01e7 (>=f unicode #x01e6)) ; G/g with caron (Turkish)

          (,unicode-hebrew-precomposed-character-block-end
             (>=f unicode ,unicode-hebrew-precomposed-character-block-start)))
        nil)))





;;;; Thai (esp. Thai Font) Information Used in FONTS


;;; The Thai fonts used for G2/Telewindows include the Thai characters only.
;;; The Unicode Standard v. 2.0, q.v., tells us that the Thai script is used to
;;; write the Thai language and other Southeast Asian languages, such as Kuy,
;;; Lavna, and Pali, and it is also frequently used to write Sanskrit.

;;; The prominent national character set standard for Thai is the Thai
;;; Industrial Standard 620-2529, aka TIS-620. The Thai layout in the Unicode
;;; Standard (i.e., the positions of characters in the Thai block of Unicode) on
;;; this Thai standard.

;;; Our Thai font, Monotype's Arial Thai for Gensym, has a small block of
;;; special Thai glyphs in the private use area (PUA) in the range F700 - F71D.
;;; Here's an explanation of how they function:
;;;
;;;   The glyph variants for 0e0d & 0e10 can be found at PUA locations f700 &
;;;   f70f. The vowel marks in the normal Thai range (0e00-0e5b) are placed at
;;;   the normal height for narrow characters, while the version of the marks in
;;;   the PUA range (f700-f7...) is better suited for wide characters; i.e. the
;;;   marks are shift left.
;;;
;;;   The tone marks in the normal Thai range (0e00-0e5b) are placed at the
;;;   normal height, i.e. above the vowels, while the version of the tone marks
;;;   in the PUA range is positioned lower for use whenever no vowel mark is
;;;   present. Similarly, the PUA holds variants of the tone marks that are
;;;   shifted left.
;;;
;;; The constants `unicode-thai-glyph-variants-start' and
;;; `unicode-thai-glyph-variants-end' refer to this small range of the Unicode
;;; PUA used for Thai font glyph variants.  For now (as of 12/17/03), we will
;;; only make use of the two glyph variats placed at F700 and F70F in
;;; combination with diacritics that appear below the baseline.  See code in
;;; FONTS referring to U+700 and U+F70F for details.


;; Per UnicodeData-2.0.12.txt, these are the non-spacing marks in the Thai
;; character block (as signified by having Mn in field 2).
;;
;; 0E31;THAI CHARACTER MAI HAN-AKAT
;; 0E34;THAI CHARACTER SARA I
;; 0E35;THAI CHARACTER SARA II
;; 0E36;THAI CHARACTER SARA UE
;; 0E37;THAI CHARACTER SARA UEE
;; 0E38;THAI CHARACTER SARA U
;; 0E39;THAI CHARACTER SARA UU
;; 0E3A;THAI CHARACTER PHINTHU
;; 0E47;THAI CHARACTER MAITAIKHU
;; 0E48;THAI CHARACTER MAI EK
;; 0E49;THAI CHARACTER MAI THO
;; 0E4A;THAI CHARACTER MAI TRI
;; 0E4B;THAI CHARACTER MAI CHATTAWA
;; 0E4C;THAI CHARACTER THANTHAKHAT
;; 0E4D;THAI CHARACTER NIKHAHIT
;; 0E4E;THAI CHARACTER YAMAKKAN

(defconstant unicode-thai-character-block-start #x0e00)
(defconstant unicode-thai-character-block-end #x0e7f)


(defconstant unicode-thai-glyph-variants-start #xF700)
(defconstant unicode-thai-glyph-variants-end #xF70F)

(defmacro thai-unicode-p (unicode)
  `(let ((unicode ,unicode))
     ,(ez-generate-binary-search-code
        'unicode
        `((,unicode-thai-character-block-end
             (>=f unicode ,unicode-thai-character-block-start))
          (,unicode-thai-glyph-variants-end
             (>=f unicode ,unicode-thai-glyph-variants-start)))
        nil)))





;;;; Text Strings



;;; A `text string' (or `Gensym string') is a Common Lisp string that may consist
;;; of any sequence of Gensym characters; see also a more complete definition in
;;; module UTILITIES1.  A text string is often written with delimiting double quotes
;;; (").

;;; A text string should be written parsably in contexts where it may be parsed as a
;;; token, by quoting double quotes (") and at signs (~@ internally) with a prefix @
;;; (~@ internally) AND by delimiting the text string.  There are four cases of
;;; delimitation, as follows.
;;;
;;;    A `whole string' is delimited by double quotes (") on both sides.
;;;
;;;    A `left string' is delimited by double quotes (") on the left and
;;;    a left bracket ([) on the right.
;;;
;;;    A `middle string' is delimited by a right bracket (]) on the left and
;;;    a left bracket ([) on the right.
;;;
;;;    A `right string' is delimited by a right bracket (]) on the left and
;;;    double quotes (") on the right.
;;;
;;; Left brackets ([) occurring in a string written parsably are NOT quoted with a
;;; prefix @, because it is assumed that slot writers for editable slots will not
;;; write left, middle, or right strings (or at least will not do so in any ordinary
;;; way).  This makes the parsably written form of certain strings representing file
;;; pathnames less confusing to the human reader.

;; See twrite-string in module UTILITIES1 and get-next-token-if-available in module EDIT.



;;; `Legal-gensym-string-p' is true if gensym-string (or the portion of gensym-string
;;; after the start position, if specified) consists exclusively of currently valid
;;; Gensym characters.  If an illegal Gensym character is encountered, nil is
;;; returned along with a second value that gives the position in gensym-string of
;;; the illegal character.

(defun legal-gensym-string-p (string &optional (start 0) (end? nil))
  (declare (eliminate-for-gsi))
  (loop with string-is-simple? = (simple-gensym-string-p string)
        with end fixnum = (or end? (glength string string-is-simple?))
        with i fixnum = start
        with j fixnum = 0
        with character
        as character-index fixnum = i
        when (>=f i end)
          return t
        unless
          (case (setq character
                      (read-string-character-from-gensym-string
                        string i string-is-simple?))
            (#\@
             (and (<f i end)
                  (currently-legal-character-following-\@
                    (read-string-character-from-gensym-string
                      string i string-is-simple?))))
            (#\~
             (and (<f i end)
                  (simple-character-p
                    (setq character
                          (read-string-character-from-gensym-string
                            string i string-is-simple?)))
                  (map-to-roman-font-special-character-code-if-any character)))
            (#\\
             (setq j i)
             (and (<f i end)
                  (simple-character-p
                    (setq character
                          (read-string-character-from-gensym-string
                            string i string-is-simple?)))
                  (<f i end)
                  (simple-character-p
                    (read-string-character-from-gensym-string
                      string i string-is-simple?))
                  (or (not (long-kanji-character-p character))
                      (and (<f i end)
                           (simple-character-p
                             (read-string-character-from-gensym-string
                               string i string-is-simple?))))
                  (<f (read-kanji-code-from-gensym-string string j string-is-simple?)
                      #.(ash 1 16))))         ; that it converts into a 16-bit kanji code
            (t (simple-character-p character)))
          return (values nil character-index)))

;; Consider verifying kanji codes more completely.





;;; `Read-gensym-character-from-gensym-string' reads and returns the next
;;; character or character code, after setting index-variable to the character
;;; index past the next character, and after setting escape-character?-variable
;;; to either nil or the escape character beginning a complex character if the
;;; next character is complex.
;;;
;;; C.f. find-next-gensym-character-in-gensym-string, which is essentially a
;;; values returning, non-side-affecting version of this function.
;;; Unfortunately, the names don't reveal this as well as they might for
;;; historical reasons.

(defmacro read-gensym-character-from-gensym-string
          (gensym-string index-variable gensym-string-is-simple?
           escape-character?-variable)
  `(let* ((gensym-string ,gensym-string)
          (gensym-string-is-simple? ,gensym-string-is-simple?))
     (let ((character
              (read-simple-character-from-gensym-string
                gensym-string ,index-variable gensym-string-is-simple?)))
       (character-case character
         ((#\@ #\~)
          (setf ,escape-character?-variable character)
          (read-simple-character-from-gensym-string
            gensym-string ,index-variable gensym-string-is-simple?))
         (#\\
            (setf ,escape-character?-variable character)
            (read-kanji-code-from-gensym-string
              gensym-string ,index-variable gensym-string-is-simple?))
         (t
           (setf ,escape-character?-variable nil)
           character)))))





;; The following two functions were moved here from BOXES.  I think they belong
;; more to this module than to BOXES.  Note that BOXES adds analogs that work on
;; texts, as opposed to strings.

;;; `find-next-gensym-character-in-gensym-string' returns the character at position
;;; character-index in string, as three values:
;;;    (1) a character or character code;
;;;    (2) either nil or the escape character beginning a complex character; and
;;;    (3) the character index past the next character.
;;; The first value is: for a simple Gensym character, that character; for a
;;; complex character beginning with @ or ~, the character after the @ or ~; or
;;; for any other complex character, the appropriate character code.

;;; There is assumed to be a next character in string; character-index must not
;;; be at the end of string.

#+development                                ; later, make obsolete or eliminate! (MHD 10/30/96)
(defun find-next-gensym-character-in-gensym-string (character-index string)
  (declare (eliminate-for-gsi-no-utf-g))
  (let* ((local-character-index character-index)
         (string-is-simple? (simple-gensym-string-p string))
         (escape-character? nil)
         (character-or-character-code
           (read-gensym-character-from-gensym-string
             string local-character-index
             string-is-simple? escape-character?)))
    (values character-or-character-code
            escape-character?
            local-character-index)))



;;; `find-previous-gensym-character-in-gensym-string' returns the character just before
;;; position character-index in string, as three values:
;;;    (1) a character or character code;
;;;    (2) either nil or the escape character beginning a complex character; and
;;;    (3) the character index for the previous character.
;;; The second value is: for a simple Gensym character, that character; for a
;;; complex character beginning with @ or ~, the character after the @ or ~; or
;;; for any other complex character, the appropriate character code.

;;; There is assumed to be a previous character in string; character-index must
;;; not be at the beginning of string.

#+development                                ; later, make obsolete or eliminate! (MHD 10/30/96)
(defun find-previous-gensym-character-in-gensym-string (character-index string)
  (declare (eliminate-for-gsi-no-utf-g))
  (let ((string-is-simple? (simple-gensym-string-p string))
        previous-character-index
        local-previous-character-index
        (escape-character? nil)
        character-or-character-code)
    (if (not (previous-character-might-be-complex-p
               string character-index string-is-simple?))
        (setq previous-character-index (-f character-index 1))
        (loop with i = 0
              do (setq previous-character-index i)
                 (skip-past-gensym-character string i string-is-simple?)
              until (>=f i character-index)))        ; =f should be enough
    (setq local-previous-character-index previous-character-index)
    (setq character-or-character-code
          (read-gensym-character-from-gensym-string
            string local-previous-character-index
            string-is-simple? escape-character?))
    (values character-or-character-code
            escape-character?
            previous-character-index)))

;; Consider defining this in terms of
;; find-next-gensym-character-in-gensym-string, at the cost of bit of speed.



#+development
(defun print-gensym-characters-in-string (string)
  (loop with i = 0
        while (< i (length string))
        do (multiple-value-bind (character-or-character-code escape-character? next-i)
               (find-next-gensym-character-in-gensym-string i string)
             (print (list character-or-character-code escape-character?))
             (setq i next-i))))



;; Moved the sections ";;;; G2 Symbols", ";;;; Numbers in G2", ";;;; Punctuation
;; Marks", and ";;;; Character Syntax" from here to UNICODE to avoid forward
;; reference problems. (MHD 2/17/96)





;;;; Character Input and Transmission



;;; Key Points Concerning Characters:
;;;
;;; All these definitions boil down to the ability to handle portable files,
;;; keyboard inputs, and ICP transmission.
;;;
;;; Files.  Complex characters are needed for such purposes as the creation of
;;; portable files.
;;;
;;; Keyboard.  Standard typeable characters are needed in handling keyboards.
;;; All typeable characters (native and Gensym) MUST map into Gensym
;;; characters.  This is the only way we can assure uniformity across
;;; platforms.  Typeable characters can be represented internally as symbols or
;;; complex characters.
;;;
;;; Transmission.  There is a choice to be made here:  characters can be
;;; transmitted as (1) ascii codes, (2) Gensym characters, or (3) symbols.
;;; Choosing (1) will mean that some native typeable characters will not be
;;; transmittable (for example, ABORT has to be transmitted as control-A
;;; because they are the same key on conventional machines).  This is probably
;;; not acceptable.  Choosing (2) would mean more network traffic.  We will
;;; face a problem with (3) as there are more characters added to the set of
;;; complex characters.




;;; `Standard Characters'.  These are referred to with the "#\" prefix.


;;; `Semi-Standard Characters.'  These are referred to as constants:
;;; char-backspace, char-tab, char-linefeed, char-page, char-return, and
;;; char-rubout.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant char-backspace #-ascii #\backspace #+ascii (code-char 8))        ;BS
  (defconstant char-tab #-ascii #\tab #+ascii (code-char 9))                ;HT
  (defconstant char-linefeed #-ascii #\linefeed #+ascii (code-char 10))        ;LF
  (defconstant char-page #-ascii #\page #+ascii (code-char 12))                ;FF
; (defconstant char-formfeed char-page)                                        ;FF
  (defconstant char-return #-ascii #\return #+ascii (code-char 13))        ;CR
  (defconstant char-rubout #-ascii #\rubout #+ascii (code-char 127))        ;DEL
; (defconstant char-delete char-rubout)                                        ;DEL
  )



;;; `Control Characters'.  These are referred to as constants: char-control-@,
;;; char-control-a, char-control-b, ..., char-control-y, char-control-z,
;;; char-control-[, char-control-backslash, char-control-],
;;; char-control-^, char-control-_, and char-escape.

(eval-when (:compile-toplevel :load-toplevel :execute)
  ;;(defconstant char-null #-ascii #\null #+ascii (code-char 0))
  (defconstant char-control-@ #-ascii #\control-@ #+ascii (code-char 0))
  (defconstant char-control-a #-ascii #\control-a #+ascii (code-char 1))
  (defconstant char-control-b #-ascii #\control-b #+ascii (code-char 2))
  (defconstant char-control-c #-ascii #\control-c #+ascii (code-char 3))
  (defconstant char-control-d #-ascii #\control-d #+ascii (code-char 4))
  (defconstant char-control-e #-ascii #\control-e #+ascii (code-char 5))
  (defconstant char-control-f #-ascii #\control-f #+ascii (code-char 6))
  (defconstant char-control-g #-ascii #\control-g #+ascii (code-char 7))
  (defconstant char-control-h #-ascii #\control-h #+ascii (code-char 8))
  (defconstant char-control-i #-ascii #\control-i #+ascii (code-char 9))
  (defconstant char-control-j #-ascii #\control-j #+ascii (code-char 10))
  (defconstant char-control-k #-ascii #\control-k #+ascii (code-char 11))
  (defconstant char-control-l #-ascii #\control-l #+ascii (code-char 12))
  (defconstant char-control-m #-ascii #\control-m #+ascii (code-char 13))
  (defconstant char-control-n #-ascii #\control-n #+ascii (code-char 14))
  (defconstant char-control-o #-ascii #\control-o #+ascii (code-char 15))
  (defconstant char-control-p #-ascii #\control-p #+ascii (code-char 16))
  (defconstant char-control-q #-ascii #\control-q #+ascii (code-char 17))
  (defconstant char-control-r #-ascii #\control-r #+ascii (code-char 18))
  (defconstant char-control-s #-ascii #\control-s #+ascii (code-char 19))
  (defconstant char-control-t #-ascii #\control-t #+ascii (code-char 20))
  (defconstant char-control-u #-ascii #\control-u #+ascii (code-char 21))
  (defconstant char-control-v #-ascii #\control-v #+ascii (code-char 22))
  (defconstant char-control-w #-ascii #\control-w #+ascii (code-char 23))
  (defconstant char-control-x #-ascii #\control-x #+ascii (code-char 24))
  (defconstant char-control-y #-ascii #\control-y #+ascii (code-char 25))
  (defconstant char-control-z #-ascii #\control-z #+ascii (code-char 26))
  (defconstant char-control-[ #-ascii #\control-[ #+ascii (code-char 27))
  (defconstant char-control-backslash
                                     #-ascii #\control-\\ #+ascii (code-char 28))
  (defconstant char-control-] #-ascii #\control-] #+ascii (code-char 29))
  (defconstant char-control-^ #-ascii #\control-^ #+ascii (code-char 30))
  (defconstant char-control-_ #-ascii #\control-_ #+ascii (code-char 31))
  (defconstant char-escape #-ascii #\escape #+ascii (code-char 27))

  ;;(defconstant char-fs (code-char 28))
  ;;(defconstant char-gs (code-char 29))
  ;;(defconstant char-rs (code-char 30))
  ;;(defconstant char-us (code-char 31))

  )


;;; Whitespace (Standard and Semi-standard) Characters.

(defvar whitespace-characters
        '(#\space #\newline
          #.char-tab #.char-page #.char-return #.char-linefeed))

(defvar whitespace-wide-characters
        '(#.(character-to-wide-character #\space)
          #.(character-to-wide-character #\newline)
          #.(character-to-wide-character #.char-tab)
          #.(character-to-wide-character #.char-page)
          #.(character-to-wide-character #.char-return)
          #.(character-to-wide-character #.char-linefeed)))


;; I deleted all of the useless variables and functions here. (fmw 4-Aug-93)

;; Note that both ascii-char and char-ascii are just used for scratch work
;; while doing development work.  They are not intended to be permanent
;; variables within G2.  -pto 07mar89

;; It seems to me that this and the above misses the appropriate abstraction!
;; The number of places that assume ascii encoding should be minimized! (LH)

;; Please try to avoid choosing such non-descriptive names as char-ascii, even
;; though it is analogous to char-int! (LH)

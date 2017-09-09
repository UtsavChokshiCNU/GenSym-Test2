;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module KEYBOARDS -- Definitions of functions for defining key codes

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Mark David, Peng Tsin Ong, Fred White



;;;; Glossary

;;; `key symbol' - a symbol which represents a Lisp character or Lisp character
;;; sequence that is produceable on a (native) keyboard by hitting one key,
;;; with or without the SHIFT key depressed.  Thus, the maximum number of key
;;; symbols for a particular keyboard is the number of keys on the keyboard
;;; times two (shifted and unshifted).  Usually, only the inner keys (such as
;;; the alphabetic keys) have shifted key symbols.  Keys such as "5" and "6" do
;;; not.  Many keys will be common to all keyboards (for example, A, B, 5, 6,
;;; ...), and others will not (F1, F2, ...).
;;;
;;; `key character' - a Lisp character which is uniquely representable by a key
;;; symbol.  The set of key characters is smaller than, or the same size as the
;;; set of key symbols because key symbols also represent keys which generate
;;; Lisp character sequences.
;;;
;;; `key index' - an 11-bit integer unique to a particular key.  (This can
;;; presently be increased using the spare bits in key modifier.)  There is
;;; thus a one-one mapping between key symbols and key indexes.
;;;
;;; `key index string' - a string of (presently) two simple characters (see
;;; CHARACTERS) which uniquely corresponds to a key index.  There is thus a
;;; one-one mapping of key indexes to key index strings.
;;;
;;; `key modifiers' - The following are key modifiers: CONTROL, META, SHIFT,
;;; CAPS-LOCK, DOUBLE, COMPOSE, ALTERNATE, UNICODE, and EXTEND-CHAR.
;;;
;;; `key spec' - A list of a keysym together with modifier bits and the special
;;; tokens KEY and MOUSE.  A key-spec is the result of parseing a keypress action
;;; in filters.lisp, and may also be used in source code as a convenient way to
;;; specify a complete key-code, with modifiers.  KEY-CODE converts key-specs into
;;; key codes.  Examples: (mouse left), (control shift a), #\a, (key left).
;;;
;;; `key code' - a fixnum whose 25 least significant bits represent key
;;; characters, with different key modifiers.  The least significant 16 bits of
;;; a key code are either used as Unicode or Key index bits.  If the Unicode bit
;;; (bit 24) is set, then they are Unicode character bits; otherwise, the least
;;; significant 11 bits are used as the key index bits (the unique bit
;;; combinations that represent the key symbols).  Bits 17 through 24 represent
;;; key modifier states (on or off).  Previously, G2 software used only 24-bit
;;; fixnums; now it uses 29-bit fixnums.  We have recently (5/17/99) begun using
;;; the 25th bit here.  In the future, we could use the remainining bits for
;;; increasing the maximum number of Unicode keys, the number of key indexes,
;;; and/or for new key modifiers.  The fixnum -1 is defined to be a key code
;;; which represents an "illegal key code".
;;;
;;;        Bit number:
;;;        MSB......25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 ... 00
;;;         |        |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | ...  |
;;;     <ignored>-+  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | ...  |
;;;        <Unicode>----+  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | ...  |
;;;        <CONTROL>-------+  |  |  |  |  |  |  |  |  |  |  |  |  |  | ...  |
;;;        <META>-------------+  |  |  |  |  |  |  |  |  |  |  |  |  | ...  |
;;;        <EXTEND-CHAR>---------+  |  |  |  |  |  |  |  |  |  |  |  | ...  |
;;;        <COMPOSE>----------------+  |  |  |  |  |  |  |  |  |  |  | ...  |
;;;        <ALTERNATE>-----------------+  |  |  |  |  |  |  |  |  |  | ...  |
;;;        <SHIFT>------------------------+  |  |  |  |  |  |  |  |  | ...  |
;;;        <CAPS-LOCK>-----------------------+  |  |  |  |  |  |  |  | ...  |
;;;        <DOUBLE>-----------------------------+  |  |  |  |  |  |  | ...  |
;;;        <Bit 15 Most Signif. Unicode Bit>-------+  |  |  |  |  |  | ...  |
;;;        <Bit 14 Unicode Bit>-----------------------+  |  |  |  |  | ...  |
;;;        <Bit 13 Unicode Bit>--------------------------+  |  |  |  | ...  |
;;;        <Bit 12 Unicode Bit>-----------------------------+  |  |  | ...  |
;;;        <Bit 11 Unicode Bit>--------------------------------+  |  | ...  |
;;;        <Bit 10 Unicode Bit or Most Signif. Key Index Bit>-----+  | ...  |
;;;        <Bit 9 of key index>--------------------------------------+ ...  |
;;;        <Least significant bit of key index>-----------------------------+












;;; When the `Unicode bit' is set, no other modifier bit should ordinarily be
;;; set.  Note that a `Unicode character key' cannot be a control, special, or
;;; function key.  The keys represented by key-index-bits, by contrast, can
;;; represent both ordinary characters as well as control keys (e.g., control-c,
;;; et al), special keys (Tab, Return, et al), and Function keys (F10, et al).

;;; Compatibility Note: Unicode character keys are new for the release currently
;;; pending.  Previously, the Unicode bit was the 25th bit (previously the first
;;; ignored bit), which never used, in G2 or Telewindows.  If a Telewindows
;;; process of this version sends a Unicode character key to a G2 of a previous
;;; version, the G2 may emit warnings complaining that it doesn't know what to
;;; do with such a key event.  It should not pose a serious problem for users.
;;; There are no plans at this time to deal with that issue further, but in
;;; principle Telewindows could be made to know the version of G2 it is talking
;;; to and refrain from ever sending Unicode character keys to it if it were too
;;; old.  (MHD 5/17/99)

(def-concept unicode-bit)
(def-concept unicode-character-key)









;;;; Macros for Testing and Manipulating Key Codes



(defmacro key-code-p (thing)
  `(fixnump ,thing))


(defmacro key-unicode (key-code)
  `(logandf unicode-character-bits ,key-code))


(defmacro key-modifier-bits (key-code)
  `(logandf key-modifier-bits ,key-code))


(defmacro illegal-key-code-p (key-code)
  `(=f illegal-key-code ,key-code))


(defmacro key-code-type-p (object)
  `(typep ,object 'fixnum))

;; Compatibility.
(defmacro event-code-type-p (object)
  `(key-code-type-p ,object))


(defmacro clear-bit (value bit)
  `(logandf ,value (lognotf ,bit)))



(defmacro unicode-bit-on-p (key-code)
  `(/=f (logandf ,key-code unicode-bit) 0))

(defmacro menu-bit-on-p (key-code)
  `(/=f (logandf ,key-code menu-bit) 0))



;;; The macro `key-index-for-unicode' takes a key-code and returns its
;;; corresponding key-index if appropriate.  If key-code represents a unicode
;;; character that's in ASCII [0..127], and therefore is likely to be found on a
;;; standard keyboard, the result is the key index corresponding to the
;;; character value.  Note that a Unicode key code has no bits besides its
;;; character value, e.g., no control key bits.  Otherwise, for any other kind
;;; of unicode key-code, this returns illegal-key-index as its result.  For key
;;; codes with a proper key index, this returns the key index bits of the key
;;; code only.

(defun-substitution-macro key-index (key-code)
  (if (unicode-bit-on-p key-code)
      (let ((unicode (key-unicode key-code)))
         (if (<= 0 unicode 127)
             ;; handle ascii for now; maybe others later! (MHD 10/1/99)
             unicode                        ; happen to be 1:1 with key indexes
            illegal-key-index))
      (logandf key-index-bits key-code)))


(defmacro control-bit-on-p (key-code)
  `(/=f (logandf ,key-code control-bit) 0))


(defmacro meta-bit-on-p (key-code)
  `(/=f (logandf ,key-code meta-bit) 0))


(defmacro shift-bit-on-p (key-code)
  `(/=f (logandf ,key-code shift-bit) 0))


(defmacro caps-lock-bit-on-p (key-code)
  `(/=f (logandf ,key-code caps-lock-bit) 0))


(defmacro double-bit-on-p (key-code)
  `(/=f (logandf ,key-code double-bit) 0))


(defmacro alternate-bit-on-p (key-code)
  `(/=f (logandf ,key-code alternate-bit) 0))


(defmacro compose-char-bit-on-p (key-code)
  `(/=f (logandf ,key-code compose-char-bit) 0))


(defmacro extend-char-bit-on-p (key-code)
  `(/=f (logandf ,key-code extend-char-bit) 0))


(defmacro symbol-bit-on-p (key-code)
  `(/=f (logandf ,key-code symbol-bit) 0))





;;;; Macros and Functions for Defining Keys





;;; The next four variables form the "database" of key <--> character mappings.

;;; The array `key-index-to-key-symbol-array' is used for help printouts and for
;;; unparsing events specifications.

(defvar key-index-to-key-symbol-array (make-array-with-nils maximum-number-of-key-indexes))


;;; The hashtable `key-symbol-to-key-index-hash-table' maps a key name, as a symbol,
;;; to its code, a fixnum.  Used by key-code and needed by event parsing.

;;; (defvar key-symbol-to-key-index-hash-table (make-hash-table :size 512))


;;; The array `key-index-to-lisp-character-array' maps a key index to its Common Lisp character
;;; object, if any.  Needed by the editor.

(defvar key-index-to-lisp-character-array (make-array-with-nils maximum-number-of-key-indexes))


;;; The hashtable `lisp-int-character-to-key-index-array' maps char-int of a CommonLisp
;;; character object to a gensym key-index, if any.

(defvar lisp-int-character-to-key-index-array (make-array-with-nils maximum-number-of-key-indexes))

;; The size should really be maximum-value-of-lisp-char-int.


;;; The list `lisp-int-character-to-key-index-alist' holds additional lisp-character --> key-index mappings.
;;; It should only be needed on lispms, but we'll keep it for now.

(defvar lisp-character-to-key-index-alist ())



;;; The defvar `bindable-keysyms' is a static list of all of the keysyms which are
;;; allowed to be rebound by the user in object configurations.

(defvar bindable-keysyms ())


;;; The defvar `pseudo-keysyms' is a static list of all of the keysyms which
;;; don't correspond to actual mouse or keyboard events.

(defvar pseudo-keysyms ())


;;; The property `key-code-for-key-symbol' ...

(def-global-property-name key-code-for-key-symbol)

;; I'm not sure if this should be a global-property or not.  It is built at load time
;; and could be read-only.



;;; The macro `def-keysym' defines a portable G2 key-code for a key-name.
;;; Include the lisp character which corresponds to this key, if it exists.

(defmacro def-keysym (key-name key-index &optional lisp-character bindable-p pseudo-p)
  (let* ((symbol (if (stringp key-name)
                     (intern (string-upcase key-name))
                     key-name))
         (pretty-symbol (if (stringp key-name)
                            (intern key-name)
                            key-name))
         (index (eval key-index))        ; We really do want to get a number at compile-time.
         (character-object (eval lisp-character))
         (character-index (and character-object (char-int character-object))))

    (unless (<= 0 index (- maximum-number-of-key-indexes 1))
      (cerror "Give up" "The key-index, ~d, is out of range." index))

    `(define-key-symbol-1 ',symbol ',index ',pretty-symbol ',character-object ',character-index
                          ',bindable-p ',pseudo-p)))




;;; The macro `def-bindable-keysym' is a shorthand for defining a keysym which is
;;; rebindinable by the user in item configurations.

(defmacro def-bindable-keysym (key-name key-index &optional lisp-character)
  `(def-keysym ,key-name ,key-index ,lisp-character t))


(defmacro def-pseudo-keysym (key-name key-index)
  `(def-keysym ,key-name ,key-index nil nil t))



(defun define-key-symbol-1 (key-symbol key-index pretty-key-symbol
                                       character-object character-index bindable-p pseudo-p)
  (setf (svref key-index-to-key-symbol-array key-index) pretty-key-symbol)
  (setf (key-code-for-key-symbol key-symbol) key-index)
  (when bindable-p
    ;; Maintain the order here.  It's the order they appear in the editor's token menu.
    (setq bindable-keysyms (nconc bindable-keysyms (list key-symbol))))
  (when pseudo-p
    (setq pseudo-keysyms (nconc pseudo-keysyms (list key-symbol))))
  (when character-object
    (setf (svref key-index-to-lisp-character-array key-index) character-object)
    ;; Update the table of lisp-character --> G2 key.  The table is stored in two parts,
    ;; an array and an alist, for effecient lookup of common characters.
    (if (<= 0 character-index (1- maximum-number-of-key-indexes))
        (setf (svref lisp-int-character-to-key-index-array character-index) key-index)
        (push (cons character-object key-index) lisp-character-to-key-index-alist))))


;;  Add key-name to a grammar category! (grammars do not yet exist, so, do this in filters.lisp).
;;  All keys go into the grammar except for control-foo, since they are handled
;;  by the modifier mechanism in the grammar.

;;  Maybe check for redefinitions.




;;; The function `clear-all-key-code-information' clears all the sundry
;;; character lookup tables.  For use only during development.

#+development
(defun clear-all-key-code-information ()
  (fill key-index-to-key-symbol-array nil)
  (fill key-index-to-lisp-character-array nil)
  (fill lisp-int-character-to-key-index-array nil)
  (setq lisp-character-to-key-index-alist nil)
  (setq bindable-keysyms nil))



;;; The function `convert-key-code-to-key-symbol' returns the G2 key symbol
;;; for a given key code.  Any modifier bits in the key-code are
;;; ignored.  It is used by the unparsing functions.

(defun convert-key-code-to-key-symbol (key-code)
  (let ((index (key-index key-code)))
    (when (<f -1 index maximum-number-of-key-indexes)
      (svref key-index-to-key-symbol-array index))))


;;; The function `key-code-from-character' converts a Lisp character object
;;; into its corresponding G2 key-code.  It is used by the input event loop
;;; on lispm's.

(defun key-code-from-character (character)
  (let ((index (char-int character)))
    (declare (type fixnum index))
    (or
      (if (<f -1 index maximum-number-of-key-indexes)
          (svref lisp-int-character-to-key-index-array index)
          (cdr (assq character lisp-character-to-key-index-alist)))
      illegal-key-code)))

;; Note that we assume that the Common Lisp function char-int will always
;; return a fixnum.

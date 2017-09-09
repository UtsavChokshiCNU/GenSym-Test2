;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")
     
;;;; Module F-KEYS -- Key codes and patterns

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Mark H. David, Peng Tsin Ong, Fred M. White


;;;; Key Codes


(def-concept key-code)


;;; The function `convert-key-symbol-to-key-code' returns the key code (a
;;; fixnum) for the key names by key-symbol.  There is a slight ambiguity in
;;; the keys named left,middle,right and the corresponding buttons.  Normally,
;;; we assume the keyboard key code; however, if is-mouse-button? is true, we
;;; assume the mouse button code.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun convert-key-symbol-to-key-code (key-symbol &optional is-mouse-button?)
  (when is-mouse-button?
    (case key-symbol
      (any
       (setq key-symbol 'mouse-down))
      (left
       (setq key-symbol 'mouse-left-down))
      (middle
       (setq key-symbol 'mouse-middle-down))
      (right
       (setq key-symbol 'mouse-right-down))))

  ;; The editor returns keyword symbols for key symbols which were
  ;; punctuation marks.
  (when (eq (symbol-package key-symbol) keyword-package-1)
    (setq key-symbol (intern (symbol-name key-symbol) ab-package-1)))
  
  (or
    (key-code-for-key-symbol key-symbol)
    illegal-key-code))
)



;;; The function `canonicalize-gensym-key-code' converts a key-code as either
;;; received from the underlying window system or as the result of the simple
;;; parse in key-code-function, below, into the canonicalized code.  The basic
;;; transformation is to remove redundant modifier bits.  Since this function
;;; is used both on the input side of G2 (get-local-event), and the processing
;;; side (all the calls to key-case in the source code), then we can be sure
;;; that both are using the same conventions, more or less (telewindows is
;;; less, for example). BUT, see also `canonicalize-key-code'.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun canonicalize-gensym-key-code (key-code)
  (cond
    ((unicode-space-p key-code)		; Windows G2/TW sends Unicode spaces instead of SPACE.
     (key-code-for-space))

    ((unicode-bit-on-p key-code)
     key-code)
    (t
     ;; If the character is an upper case letter, and the caps lock bit is set,
     ;; and there are any other modifier bits, then change the character to lower
     ;; case.  In other words, caps lock only affects the printing letters, not
     ;; modified ones.
     (when (and (upper-case-letter-key-code-p key-code)
		(caps-lock-bit-on-p key-code)
		(or (control-bit-on-p key-code)
		    (meta-bit-on-p key-code)
		    (alternate-bit-on-p key-code)))
       (setq key-code (invert-case-of-letter-key-code key-code)))
     
     ;; In any case, clear CapsLock
     (setq key-code (logandf key-code (lognotf caps-lock-bit)))
     
     ;; If the SHIFT bit is set, and the key is a lower case letter, then upcase
     ;; the key. The next clause will clear the SHIFT bit.
     (when (and (shift-bit-on-p key-code)
		(lower-case-letter-key-code-p key-code))
       (setq key-code (upcase-letter-key-code key-code)))
     
     
     ;; If the SHIFT bit is implicit in the key itself, that is, the key is a
     ;; printing ASCII character except SPACE, then clear it.
     (when (shift-bit-is-implicit-in-key-code-p (key-index key-code))
       (setq key-code (logandf key-code (lognotf shift-bit))))
     

     ;; As for SPACE, only the precise combination SHIFT+SPACE is not allowed.
     ;; Convert that to just SPACE.  Don't use key-code here since key-code calls
     ;; us!
     (let ((space (key-code-for-space)))
       (when (and (=f (key-modifier-bits key-code) shift-bit)
		  (=f (key-index key-code) space))
	 (setq key-code space)))
     
     
     ;; If the CONTROL bit is ON, and the key-code is one of the conventional
     ;; ASCII control characters (A-Z, etc), then clear the control bit and mask
     ;; the key-code down to 0-31.  Eg, control+a becomes SOH (code 1, control bit
     ;; off)
     (when (and (control-bit-on-p key-code)
		(conventional-ascii-control-character-key-code-p
		  (key-index key-code)))
       (setq key-code (logandf key-code
			       (lognotf control-bit)
			    (lognotf (logxorf key-index-bits #x1f)))))
  key-code)))
)

;; I really, REALLY hate this stuff.





;;; The function `key-code-function' parses the lists as returned by the grammar
;;; for key-codes in item configurations.  We call them key-specs.
;;; A `key-spec' is either a character, a symbol, or a list of modifiers
;;; and a key-spec.  The allowed modifers are:
;;;     CONTROL, SHIFT, META, etc. - the usual modifiers.
;;; The modifer tokens may appear anywhere in the list.

;;; If invert-symbol-letter-case? is t, then the symbols A-Z are considered
;;; lower case letters, and the symbols |a|-|z| are considered upper case
;;; letters.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun key-code-function (key-spec mouse? invert-symbol-letter-case?)
  (declare (ignore mouse?))				    ; No longer used.
  (cond ((symbolp key-spec)
	 (let ((key-code (convert-key-symbol-to-key-code key-spec)))
	   (cond ((illegal-key-code-p key-code)
		  (dwarn "Unknown modifier or key name ~s in key-code-function." key-spec)
		  key-code)
		 ((and invert-symbol-letter-case?
		       (letter-key-code-p key-code))
		  (invert-case-of-letter-key-code key-code))
		 (t
		  key-code))))

	((gensym-string-p key-spec)
	 (convert-key-symbol-to-key-code (intern key-spec)))

	((text-string-p key-spec)
	 (convert-key-symbol-to-key-code (intern-text-string key-spec)))
	  
	((characterp key-spec)
	 (key-code-from-character key-spec))
	  
	((fixnump key-spec)
	 key-spec)
	  
	((not (consp key-spec))
	 illegal-key-code)

	(t
	 (let ((key-code illegal-key-code)
	       (modifier-bits 0))
	   (loop for token in key-spec doing
	     (case token
	       (control
		(setq modifier-bits (logiorf modifier-bits control-bit)))
	       (shift
		(setq modifier-bits (logiorf modifier-bits shift-bit)))
	       ((alternate alt)
		(setq modifier-bits (logiorf modifier-bits alternate-bit)))
	       (meta
		(setq modifier-bits (logiorf modifier-bits meta-bit)))
	       (double
		(setq modifier-bits (logiorf modifier-bits double-bit)))
	       (t
		(setq key-code (key-code-function token nil invert-symbol-letter-case?)))))

	   (cond ((illegal-key-code-p key-code)
		  key-code)
		 (t
		  (canonicalize-gensym-key-code
		    (logiorf key-code modifier-bits))))))))
  )

;; At present, this does not handle Unicode characters.  That should be
;; eventually be done, but there's no great need at this point.  (MHD 5/17/99)

;; Removed the MOUSE and KEY modifiers, which were unused, and caused junk like
;; mouse+up (typo) and key+up (pure junk) to parse. -fmw, 1/28/95




;;; The function `key-code-from-list' parses lists as returned by the grammar
;;; for item-configuration.  

(defun key-code-from-list (key-spec)
  (cond ((symbolp key-spec)
	 (key-code-from-symbol key-spec))
	((text-string-p key-spec)
	 (key-code-from-symbol		; shouldn't need conversion to ASCII
	   (intern-text-string (string-upcasew key-spec))))
	((not (consp key-spec))
	 illegal-key-code)
	(t
	 (key-code-function key-spec nil t))))



;;; The macro `key-code' parses a key-spec into a key-code at compile-time,
;;; is possible.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro key-code (key-spec)
  (if (constantp key-spec)
      `',(key-code-function (eval key-spec) nil t)
      `(key-code-function ,key-spec nil t)))
)


;;; The function `key-code-from-symbol' converts a symbol naming a key in the
;;; user-model to a numeric key-code as used by event dispatching.  User-model
;;; symbols naming keys are "+" separated strings of modifier names and a
;;; keysym name.  Examples: return, control+alt+b, alt+mouse-down.

(defun key-code-from-symbol (symbol)
  (let* ((symbols (split-symbol symbol #\+))
	 (key-spec (if (singleton? symbols) (first symbols) symbols)))
    (prog1
	(key-code key-spec)
      (reclaim-gensym-list symbols))))


(defun symbol-from-key-code (key-code)
  (intern-text-string
    (nstring-upcasew
      (twith-output-to-text-string
	(twrite-key-code key-code)))))

(defun parseable-symbol-from-key-code (key-code)
  (let ((write-symbols-parsably? t))
    (intern-text-string
      (nstring-upcasew
	(twith-output-to-text-string
	  (twrite-key-code key-code))))))


(defmacro key-code-equal (key-code key-spec)
  `(=f ,key-code (key-code ,key-spec)))



;;; The defparameter `characters-requiring-quotation-in-key-symbols' was
;;; determined empirically.  It must represent some hardwired delimiter
;;; characters in the parser.

(defparameter characters-requiring-quotation-in-key-symbols
  #w"^<>*^()[],:;?!|$%&'`#{}+/=\"\\")

;; Try to eliminate and reabstract in same terms as symbol token reading and
;; writing! (MHD 2/20/96)


;;; The function `twrite-character-of-keysym' twrites the character, escaping
;;; escape characters with ~ and punctuation characters with @.

(defun twrite-character-of-keysym (char first-char? case)
  (let ((pretty-char
	  (case case
	    (:downcase (char-downcasew char))
	    (:upcase (char-upcasew char))
	    (:capitalize (if first-char? (char-upcasew char) (char-downcasew char)))
	    (t char))))
    (cond ((null write-symbols-parsably?)
	   nil)
	  ((and (eq write-symbols-parsably? 'for-filters)
		(or (find-in-text-string
		      char characters-requiring-quotation-in-key-symbols)
		    (and first-char?
			 (or (digit-char-pw char)
			     ;; Quote hyphen only if first char, also.
			     (char-equalw char #.%\-)))))
	   ;; If for filters, escape all punctuation chars, and digits if the
	   ;; first char.
	   (twrite-char #.%\@)))		; symbol quoting character
    (twrite-char pretty-char)))

;; We could use twrite-symbol, except we want additionally to escape ~
;; characters.  Actually, if we want to be able to rebind the trademark symbol,
;; maybe we should not escape ~?.  In any case, we need to quote punctuation
;; chars. Also must quote the digits 0-9.


;;; The variable `twrite-control-as-ctrl' is bound to t to write key codes
;;; following Windows conventions (not parseable in item configs!)

(defvar twrite-control-as-ctrl nil)


;;; MS Windows (and Motif?) prefer Ctrl+.  Must fix the grammar and maybe the
;;; special control chars, too, if this is changed.

(defun twrite-key-modifier-bits (key-code capitalize?)
  (when (double-bit-on-p key-code)
    (twrite-string "Double+"))
  (when (or (control-bit-on-p key-code)
	    (special-control-key-p key-code))
    (twrite-string (if twrite-control-as-ctrl
		       (if capitalize? "Ctrl+" "ctrl+")
		       (if capitalize? "Control+" "control+"))))
  (when (alternate-bit-on-p key-code)
    (twrite-string (if capitalize? "Alt+" "alt+")))
  (when (shift-bit-on-p key-code)
    (twrite-string (if capitalize? "Shift+" "shift+")))
  key-code)

; (when (meta-bit-on-p key-code) (twrite-string "Meta+")) ; Deprecated.


;;; The function `twrite-key-code' twrites a key-code in a form parseable in
;;; object configurations.  It thus is an inverse of `key-code-function'.  All
;;; characters but the first are written in lower case.

(defun twrite-key-code (key-code)
  (cond ((not (key-code-type-p key-code))
	 (twrite key-code))
	((illegal-key-code-p key-code)
	 (twrite-string "illegal-key"))
	((unicode-bit-on-p key-code)	; See Note (MHD 1/10/00)
	 (twrite-char (code-wide-character (key-unicode key-code))))
	(t
	 ;; Print upper case letters with the SHIFT modifier.  This is
	 ;; so that the resulting string is unique, and does not depend
	 ;; on its own case.
	 (when (upper-case-letter-key-code-p key-code)
	   (setq key-code (logiorf (invert-case-of-letter-key-code key-code) shift-bit)))

	 (let ((key-symbol? (convert-key-code-to-key-symbol key-code)))

	   (cond ((null key-symbol?)
		  (dwarn "Unknown key-code ~d" key-code)
		  (twrite-string "illegal-key"))
		 (t
		  (twrite-key-modifier-bits key-code t)
		  
		  ;; Special control character have symbol names which already
		  ;; include "control-".  Skip over that here.

		  ;; Turn the code into a string, then turn that into a symbol,
		  ;; then print it (parsably, if so desired) as a symbol.  Print
		  ;; the symbol with initial cap.
		  (cond ((special-control-key-p key-code)
			 (let* ((string (symbol-name-text-string key-symbol?))
				(char 
				  (charw string (-f (lengthw string) 1))))
			   (twrite-character-of-keysym char t :capitalize)))
			(t
			 (let ((string (symbol-name-text-string key-symbol?)))
			   (loop for i below (lengthw string)
				 as char = (charw string i)
				 doing
			     (twrite-character-of-keysym
			       char (=f i 0) :capitalize)))))))))))

;; Note: Earlier, I thought to have this call twrite-wide-character-readably.
;; That prints \uHHHH.  I'm not happy with that, since it's not readable, and
;; further more gets printed usually as #\uHHHH, which is also unreadable by
;; G2's string reader.  Even if it were readable, it would not take advantage
;; G2/Telewindows large glyph rendering repertoire.  I think it would
;; disapppoint users to see that G2 can print a Russian or Japanese character
;; perfectly well, but then subjects them to hex codes to represent them as
;; symbols in G2.  (We should consider having a Unicode/Hex escape feature for
;; G2 strings, and also review what twrite-wide-character-readably should do and
;; what it is good for ultimately.  Anyhow, it works out much better, it turns
;; out, to just put the code in here, since G2 will typically escape it if
;; necessary, and it will typically be a renderable glyph if it's being typed by
;; the user.  If not, the next step would be to have substitute glyphs for
;; unimplemented unicode ranges, e.g., which print e.g., [U+43A5] as a glyph if
;; U+43a5 is an unimplemented glyph.  (I.e., as opposed to printing a blob.)
;; (MHD 1/10/00)

;; Later, unkludge this somehow -- combine better with symbol writer/token
;; reader! (MHD 2/20/96)



;;; The function `key-name' returns the name of a given key-code, as printed on
;;; the help workspace.  The returned string is a freshly consed LISP string,
;;; hence, key-name should be called only at compile or load time.

#+development
(defun key-name (key-code)
  (cond ((or (not (fixnump key-code))
	     (illegal-key-code-p key-code))
	 "Illegal-Key")

	((menu-bit-on-p key-code)	; Hack -fmw, 1/15/02
	 (format nil "Menu~d-Item-~d" 
		 (key-code-menu-number key-code)
		 (key-code-item-number key-code)))
	
	((and (not (unicode-bit-on-p key-code))
	      (null (convert-key-code-to-key-symbol key-code)))
	 key-code)
	(t
	 (let ((string (twith-output-to-text-string
			 (twrite-key-code key-code))))
	   (prog1 (copy-seq string)
	     (reclaim-text-string string))))))


#+development
(defun describe-key (key-code-or-name)
  (let ((key-code (key-code key-code-or-name)))
    (cond
      ((unicode-bit-on-p key-code)	; print unicode as #uHHHH (H=hex digit)
       (format t "~&Character:         #u~4,'0,x" (key-unicode key-code)))
      (t
       (format t "~&Character:         `~a'" (key-name key-code))))
    (format t "~&Key Index:         ~a" (key-index key-code))
    (format t "~%Key Code:          ~a" key-code)
    (format t "~%Key Code (binary): ~24,'0b" key-code)
    (format t "~%Bits set:          ")
    (loop for bit in '(menu-bit
		       unicode-bit
		       control-bit
		       meta-bit
		       extend-char-bit
		       compose-char-bit
		       alternate-bit
		       shift-bit
		       caps-lock-bit
		       double-bit)
	  when (/= (logandf (symbol-value bit) key-code) 0)
	    do (format t " ~(~a~)" (string-difference bit "-BIT")))
    key-code))




;;;; Key Patterns



;;; A `key-pattern' is an abstract object which specifies a set of key codes.
;;; It has both an external and an internal representation.  New patterns can
;;; be defined by arbitrary predicates on (key-code).

(def-concept key-pattern)

;; Still want: "indirect" key patterns -- patterns which name another
;; key, stored in a variable.

(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name key-pattern-named)
(def-global-property-name key-pattern-abbreviation)
)

;; Maybe, a named key-code set?  Makes it easier to unparse.

;;; At present, key-code-patterns are represented internally as either:
;;;   A fixnum, which is an exact key-code
;;;   A symbol, which is a pattern defined by define-key-code-pattern.
;;;   A cons (value . mask), which ignores some bits in the key-code.
;;;   A cons (OR <kp1> ... <kpn>).

(def-substitution-macro key-code-matches-key-pattern-p (key-code key-pattern)
  (cond ((fixnump key-pattern)
	 (=f key-pattern key-code))

	((symbolp key-pattern)
	 #+development (unless (key-pattern-named key-pattern)
			 (error "Unknown key-pattern ~s" key-pattern))
	 (funcall-simple-compiled-function (key-pattern-named key-pattern)
					   key-code))

	((and (consp key-pattern)
	      (fixnump (car key-pattern)))
	 (=f (logandf key-code (cdr key-pattern))
	     (car key-pattern)))

	((and (consp key-pattern)
	      (eq (first key-pattern) 'or))
	 (loop for disjunct in (rest key-pattern)
	       thereis (key-code-matches-key-pattern-p-function key-code disjunct)))))


(defun key-code-matches-key-pattern-p-function (key-code key-pattern)
  (key-code-matches-key-pattern-p key-code key-pattern))


(defun-for-macro make-key-pattern-matching-form (key-code-variable key-pattern)
  (let ((key-pattern (parse-key-pattern key-pattern)))
    (cond ((fixnump key-pattern)
	   `(=f ,key-code-variable ,key-pattern))

	  ((symbolp key-pattern)
	   `(and (key-pattern-named ',key-pattern)
		 (funcall-simple-compiled-function (key-pattern-named ',key-pattern)
						   ,key-code-variable)))

	  ((and (consp key-pattern)
		(fixnump (car key-pattern)))
	   `(=f (logandf ,key-code-variable ,(cdr key-pattern))
		,(car key-pattern)))
	  
	  ((and (consp key-pattern)
		(eq (first key-pattern) 'or))
	   `(or
	      ,@(loop for disjunct in (rest key-pattern)
		      collect (make-key-pattern-matching-form key-code-variable disjunct)))))))


;;; The function `parse-key-string' parses a string naming a key into a list
;;; of modifiers and keys.  For example, CONTROL++ returns (control +).

(defun-for-macro parse-key-string (string)
  (loop with delimiters = (list #\+)
	with length = (length string)
	for i = 0 then (1+ j)
	as inc = 0 then 1		; Start search one beyond a delimiter.
	while (< i length)
	as j = (or (string-search-set delimiters string :start (+ i inc)) length)
	collect (substring string i j)))

;;; The defun-for-macro `parse-key-pattern' parses the external representation
;;; of a key pattern into the internal representation. It returns NIL if the
;;; pattern is unparseable.

;;; The external representation is either:
;;;   A lisp character
;;;   The name of a key.
;;;   The name of a key pattern (which parses as itself).
;;;   A "+" separated symbol or string of modifiers and a key name.
;;;   The string ANY+keyname, which matches any modifiers (and parses as a cons of code and mask).
;;;   A list of (OR <key-pattern> ... <key-pattern>)

;;;  The internal representation is basically the same, except that key names
;;; are transformed into their key codes (fixnums).

(defun-for-macro parse-key-pattern (external-key-pattern)
  (cond ((characterp external-key-pattern)
	 (let ((code (key-code external-key-pattern)))
	   (unless (illegal-key-code-p code)
	     code)))

	((fixnump external-key-pattern)
	 external-key-pattern)
	
	((and (symbolp external-key-pattern)
	      (key-pattern-named external-key-pattern))
	 external-key-pattern)

	#+development			; (MHD 2/15/96)
	((text-string-p external-key-pattern)
	 (cerror "Continue with nil" "~a, a text string, not handled yet!"
		 external-key-pattern))
	
	((or (symbolp external-key-pattern)
	     (gensym-string-p external-key-pattern))
	 (let* ((symbols (loop for word in (parse-key-string (string external-key-pattern))
			       collect (build-ab-symbol word)))
		(key-spec (if (singleton? symbols) (first symbols) symbols)))

	   ;; Here is where we handle the "ANY+xxx" syntax which means that any modifier bits
	   ;; are allowed. It is returned as a value and mask pair.

	   (cond ((and (consp key-spec)
		       (eq (car key-spec) 'any))
		  (cons (key-code (cdr key-spec))	    ; Ignore modifier bits.
			key-index-bits))

		 (t
		  (key-code key-spec)))))
	((and (consp external-key-pattern)
	      (eq (car external-key-pattern) 'or))
	 (cons 'or (loop for key-pattern in (rest external-key-pattern)
			 collect (parse-key-pattern key-pattern))))
	
	(t
	 (cerror "Return NIL" "~s is not parseable as a key-pattern" external-key-pattern)
	 nil)))



;;; The macro `define-key-pattern' defines a named key pattern
;;; as a predicate on key-code.  The predicate may perform
;;; any computation is wishes, but should be fast and
;;; free of side-effects.

(defmacro define-key-pattern (name (key-code) &body body)
  (let ((function-name (build-ab-symbol name "KEY-PATTERN")))
    `(progn
       (defun-simple ,function-name (,key-code) ,@body)
       (setf (key-pattern-named ',name) #',function-name))))


(define-key-pattern otherwise (key-code)
  (declare (ignore key-code))
  t)

(define-key-pattern <pseudo-keycode> (key-code)
  (pseudo-key-code-p key-code))

(define-key-pattern <printing-character> (key-code)
  (printable-character-key-code-p key-code))


(define-key-pattern <unicode-character> (key-code)
  (unicode-bit-on-p key-code))

;; New for the release pending. (MHD 5/17/99)


(define-key-pattern <alphabetic> (key-code)
  (letter-key-code-p key-code))

(define-key-pattern <any-keyboard-event> (key-code)
  (and (not (mouse-key-code-p key-code))
       (not (pseudo-key-code-p key-code))))


;; Matches any mouse up, down, or motion, with any modifiers.
(define-key-pattern <mouse-gesture> (key-code)
  (mouse-key-code-p key-code))


;; This are much nicer than the "any+" syntax.

(define-key-pattern <mouse-up> (key-code)
  (key-code-is-mouse-up-p key-code))

;; This matches mouse-down as well as mouse-{left,middle,right}-down.  The latter
;; events were never seen by G2 until today. -fmw, 3/4/02
(define-key-pattern <mouse-down> (key-code)
  (key-code-is-mouse-down-p key-code))

(define-key-pattern <mouse-left-down> (key-code)
  (key-code-is-mouse-left-down-p key-code))

(define-key-pattern <mouse-middle-down> (key-code)
  (key-code-is-mouse-middle-down-p key-code))

(define-key-pattern <mouse-right-down> (key-code)
  (key-code-is-mouse-right-down-p key-code))

(define-key-pattern <mouse-motion> (key-code)
  (key-code-is-mouse-motion-p key-code))

(define-key-pattern <mouse-hover> (key-code)
  (key-code-is-mouse-hover-p key-code))

(define-key-pattern <mouse-drag> (key-code)
  (key-code-is-mouse-drag-p key-code))

;; Matches mouse-select, and mouse-left/middle-right-select.
(define-key-pattern <mouse-select> (key-code)
  (key-code-is-mouse-select-p key-code))

(define-key-pattern <mouse-left-select> (key-code)
  (=f (key-index key-code) (key-code 'mouse-left-select)))

(define-key-pattern <mouse-middle-select> (key-code)
  (=f (key-index key-code) (key-code 'mouse-middle-select)))

(define-key-pattern <mouse-right-select> (key-code)
  (=f (key-index key-code) (key-code 'mouse-right-select)))

(define-key-pattern <mouse-left-drag> (key-code)
  (=f (key-index key-code) (key-code 'mouse-left-drag)))

(define-key-pattern <mouse-right-drag> (key-code)
  (=f (key-index key-code) (key-code 'mouse-right-drag)))

;; Hack for menu-choose events. -fmw, 1/15/02
(define-key-pattern <native-menu-choice> (key-code)
  (key-code-is-native-menu-choice-p key-code))



;;; The macro `define-key-pattern-abbreviation' defines a named key pattern as
;;; an abbreviation for another, presumably more complex, key pattern.

(defmacro define-key-pattern-abbreviation (name key-pattern)
  `(progn
     (setf (key-pattern-abbreviation ',name)
	   ',(parse-key-pattern key-pattern))
     (define-key-pattern ,name (key-code)
       ,(make-key-pattern-matching-form 'key-code key-pattern))))


(define-key-pattern-abbreviation <standard-newline-keys>
    (or linefeed line control+J))

(define-key-pattern-abbreviation <standard-help-keys>
    (or control+? help control+/))

;; Removed control+_ -fmw, 10/3/94

(define-key-pattern-abbreviation <standard-enter-keys>
    (or enter return))

(define-key-pattern-abbreviation <delete-backward-keys>
    (or backspace shift+backspace))			    ; Shift by popular demand.

(define-key-pattern-abbreviation <delete-forward-keys>
    (or delete shift+delete))			   

(define-key-pattern-abbreviation <standard-abort-keys>
    (or abort control+a))




(defmacro key-code-equivalent-p (key-code key-pattern)
  (cond ((constantp key-pattern)
	 (make-key-pattern-matching-form key-code (eval key-pattern)))
	(t
	 (cerror "Proceed" "Second argument to key-code-equivalent-p must be a constant.")
	 nil)))




;;; The macro `key-case' dispatches on a key-code.  Each arm of the case is a
;;; key-pattern or a list of key-patterns.  The first arm which contains a
;;; key-pattern matching the given key-code is run.

(defmacro key-case (key &body cases)
  (avoiding-variable-capture (key)
    `(cond
       ,@(loop for (spec . body) in cases
	       as key-patterns = (if (consp spec) spec (list spec))
	       as condition = (cond ((and (atom spec)
					  (memq spec '(t otherwise)))
				     't)
				    ((singleton? key-patterns)
				     (make-key-pattern-matching-form key (car key-patterns)))
				    (t
				     (cons 'or
					   (loop for key-pattern in key-patterns
						 collect (make-key-pattern-matching-form key key-pattern)))))
	       collect `(,condition ,@body)))))



;;; The function `twrite-key-pattern' is used by the HELP workspace to print
;;; the contents of key maps.

(defun twrite-key-pattern (key-pattern)
  (cond ((fixnump key-pattern)
	 (twrite-key-code key-pattern))

	((symbolp key-pattern)				    ; Maybe it abbrevs something else.
	 (let ((abbreviation? (key-pattern-abbreviation key-pattern)))
	   (if abbreviation?
	       (twrite-key-pattern abbreviation?)
	       (twrite-symbol key-pattern))))

	((and (consp key-pattern)
	      (fixnump (car key-pattern)))
	 (let ((value (car key-pattern))
	       (mask (cdr key-pattern)))
	   (cond ((=f mask key-index-bits)
		  (tformat "any+")
		  (twrite-key-pattern value))
		 (t
		  ;; Bogus
		  (tformat "[0~o,0~o]" value mask)))))

	((and (consp key-pattern)
	      (eq (first key-pattern) 'or))
	 (twrite-key-patterns (rest key-pattern)))

	#+development
	(t
	 (dwarn "Bogus key-pattern ~s" key-pattern))))



;;; The function `twrite-key-patterns' twrites a list of key-patterns, as a
;;; comma and or-separated list.

(defun twrite-key-patterns (key-patterns)
  (loop for sublist on key-patterns doing
    (twrite-key-pattern (car sublist))
    (cond ((null (cdr sublist)))
	  ((null (cddr sublist))
	   (twrite-string " or "))
	  (t
	   (twrite-string ", ")))))


(defun-simple twrite-symbol-simply (symbol)
  (twrite-symbol symbol))


;;; The function `twrite-key-patterns-and-classes' writes a list of
;;; (key-pattern . class-or-classes).  A class named T means any class, and is not
;;; printed.  Used by the HELP workspace.

(defun twrite-key-patterns-and-classes (key-patterns-and-classes)
  (let ((write-symbols-parsably? t))
    ;; We must write parseably, else this can generate invalid text strings!
    (loop for sublist on key-patterns-and-classes
	  as key-pattern = (car (car sublist))
	  as class-or-classes = (cdr (car sublist))
	  doing
      (twrite-key-pattern key-pattern)

      (when (and class-or-classes (neq class-or-classes t))
	(twrite-string " on ")
	(if (consp class-or-classes)
	    (twrite-list class-or-classes :element-writer #'twrite-symbol-simply)
	    (twrite-symbol class-or-classes)))
      
      (cond ((null (cdr sublist)))
	    ((null (cddr sublist))
	     (twrite-string " or "))
	    (t
	     (twrite-string ", "))))))


#+development
(defun unparse-key-pattern (key-pattern)
  (twith-output-to-text-string
    (twrite-key-pattern key-pattern)))


;;; The function `key-code-mouse-button-name' returns the name of the mouse
;;; button for key-code: left, middle, right, any, or nil if none.

(defun key-code-mouse-button-name (key-code)
  (key-case (key-index key-code)
    ((mouse-left-down mouse-left-up mouse-left-select mouse-left-drag) 'left)
    ((mouse-middle-down mouse-middle-up mouse-middle-select mouse-middle-drag) 'middle)
    ((mouse-right-down mouse-right-up mouse-right-select mouse-right-drag) 'right)
    ((mouse-down mouse-up mouse-select mouse-drag) 'any)
    (mouse-hover 'mouse-hover)))


  
;;; The simple function `convert-mouse-code-to-mouse-select' converts a mouse
;;; key-code to a mouse-select key-code, preserving buttons and modifiers.

(defun-simple convert-mouse-code-to-mouse-select (key-code)
  (logiorf (key-modifier-bits key-code)
	   (key-case (key-index key-code)
	     ((mouse-left-down mouse-left-up) (key-code 'mouse-left-select))
	     ((mouse-middle-down mouse-middle-up) (key-code 'mouse-middle-select))
	     ((mouse-right-down mouse-right-up) (key-code 'mouse-right-select))
	     (t
	       ;; It is important to return some form of mouse-select in all cases,
	       ;; although we should never see generic mouse key codes here.
	       (dwarn "Unexpected key-code ~d (~a) in convert-mouse-code-to-mouse-select"
		      key-code (key-name key-code))
	       (key-code 'mouse-select)))))

;;; The simple function `convert-mouse-code-to-mouse-drag' does the same for
;;; mouse-drag.

(defun-simple convert-mouse-code-to-mouse-drag (key-code)
  (logiorf (logandf (key-modifier-bits key-code) double-mask) ; No double on mouse-drag
	   (key-case (key-index key-code)
	     ((mouse-left-down mouse-left-up) (key-code 'mouse-left-drag))
	     ((mouse-middle-down mouse-middle-up) (key-code 'mouse-middle-drag))
	     ((mouse-right-down mouse-right-up) (key-code 'mouse-right-drag))
	     (t 
	       ;; It is important to return some form of mouse-drag in all cases.
	       ;; although we should never see generic mouse key codes here.
	       (dwarn "Unexpected key-code ~d (~a) in convert-mouse-code-to-mouse-drag"
		      key-code (key-name key-code))
	       (key-code 'mouse-drag)))))


;;; The function `mouse-motion-key-code' creates a mouse-motion key code with
;;; modifier bits.  Mouse motion (as well as mouse drag) never have a double
;;; bit. Nor do they have the unicode bit!

(defun mouse-motion-key-code (modifier-bits)
  (logiorf (logandf modifier-bits double-mask unicode-mask)
	   (key-code 'mouse-motion)))


;;; The function `twrite-shortcut-key' writes a shortcut in the standard way
;;; expected by Windows users.

(defun twrite-shortcut-key (key-code)
  (key-case key-code
    (delete (twrite-string "Del")) ; Special case. Others?
    (t (let ((twrite-control-as-ctrl t))
	 (twrite-key-code key-code)))))

;; -*- Mode:Common-Lisp; Package:AB; Base:10; Syntax:COMMON-LISP -*-
(in-package "AB")

;;;; Module KFEP3  --  Kanji Front End Processor

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; Ong, Peng Tsin


#+development
(declare-forward-reference check-memory function)

#+development
(declare-forward-reference save-kb function)

(declare-forward-reference make-new-top-level-kb-workspace function)


;;;; CONVERTERS (Kana-to-ASCII and ASCII-to-Kana)




;; A Note on Writing Our Own Roman-to-Kana and Kana-to-Roman Converters:
;;
;; The KaNa[] array in kkaro2ka.c can serve as a basis to provide to build our
;; own converters in Lisp.  Note that only the low bytes of the Kana codes are
;; provided in the Kana side of the data structure.  -pto 15mar90




;;; Strings that consist exclusively of simple roman, Kanji roman, hiragana, and
;;; katakana characters should always be convertible to `ascii roman'.



;;; The constant `jis-kana-to-ascii' contains a mapping of either Hiragana or
;;; Katakana to the ascii Romaji representation of the kana.  If the offset
;;; #x2420 is added to the index, the Hiragana conversion is obtained.  If
;;; #x2520 is added, the Katakana conversion is obtained.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter jis-kana-to-ascii
              #(""
                "xa"
                "a"
                "i"
                "i"
                "xu"
                "u"
                "e"
                "e"
                "xo"
                "o"
                "ka"
                "ga"
                "ki"
                "gi"
                "ku"
                "gu"
                "ke"
                "ge"
                "ko"
                "go"
                "sa"
                "za"
                "si"
                "zi"
                "su"
                "zu"
                "se"
                "ze"
                "so"
                "zo"
                "ta"
                "da"
                "ti"
                "di"
                "tu"
                "tu"
                "du"
                "te"
                "de"
                "to"
                "do"
                "na"
                "ni"
                "nu"
                "ne"
                "no"
                "ha"
                "ba"
                "pa"
                "hi"
                "bi"
                "pi"
                "hu"
                "bu"
                "pu"
                "he"
                "be"
                "pe"
                "ho"
                "bo"
                "po"
                "ma"
                "mi"
                "mu"
                "me"
                "mo"
                "ya"
                "ya"
                "yu"
                "yu"
                "yo"
                "yo"
                "ra"
                "ri"
                "ru"
                "re"
                "ro"
                "wa"
                "wa"
                "wi"
                "we"
                "wo"
                "n"
                "v"
                "ka"
                "ki"))
)


;;; The constant `jis-offsets-for-y-prefix-kana-characters' is a list
;;; of offsets of JIS Hiragana or Katakana codes which are used as
;;; prefixes to "ya", "yu", and "yo".

(def-kfep-constant jis-offsets-for-y-prefix-kana-characters
             '#.(loop for index from 0 below (length jis-kana-to-ascii)
                      as  ascii-string = (svref jis-kana-to-ascii index)
                      when (and (= (length ascii-string) 2)
                                (eql (char ascii-string 1) #\i))
                        collect index))


;; Ascii strings that start with "y".

(def-kfep-constant jis-offsets-for-y-kana-characters '(67 69 71))






;; Old code for Kana to ASCII translation:
;                         (cond
;                           ((or (hiragana-code-p kanji-code)
;                                (katakana-jis-code-p kanji-code))
;                            (let* ((offset (if (hiragana-code-p kanji-code)
;                                               #x2420        ; Hiragana
;                                               #x2520))        ; Katakana
;                                   (kanji-code-offset (-f kanji-code offset)))
      
;                              ;; The heuristic here might not be correct, check with
;                              ;; someone who knows Japanese well.

;                              ;; This part of the code should be replaced with a routine
;                              ;; written in C to make use of the Ascii-to-Kana table in
;                              ;; kkaro2ka.c.  -pto 09mar90

;                              ;; Print:
;                              (cond
;                                ;; First part of special combination, if any:
        
;                                ;; KI[yo]
;                                ((and (eq possible-special-combination-state? 'y-suffix)
;                                      (member kanji-code-offset
;                                              jis-offsets-for-y-kana-characters))
;                                 (twrite-char (char last-kana-string? 0))
;                                 (twrite-string (svref jis-kana-to-ascii kanji-code-offset))
;                                 (setq last-kana-code-offset? nil)
;                                 (setq possible-special-combination-state? nil))
;                                ;; DE[i]
;                                ((and (eq possible-special-combination-state? 'dhi)
;                                      (=f kanji-code-offset #x03))        ; #x03 = small "i"
;                                 (twrite-string "dhi")
;                                 (setq last-kana-code-offset? nil)
;                                 (setq possible-special-combination-state? nil))
;                                ;; tsu[TO]
;                                ((and (eq possible-special-combination-state? 'small-tsu)
;                                      (>f (length last-kana-string?) 0)
;                                      (not (member (char last-kana-string? 0)
;                                                   '(#\a #\i #\u #\e #\o))))        ; tsuTO -> TTO
;                                 (let* ((current-kana-string
;                                          (svref jis-kana-to-ascii kanji-code-offset)))
;                                   (if (=f (length current-kana-string) 2)
;                                       (progn
;                                         (twrite-char (char current-kana-string 0))
;                                         (twrite-string current-kana-string))
;                                       (progn
;                                         (twrite-string last-kana-string?)
;                                         (twrite-string current-kana-string)))
;                                   (setq last-kana-code-offset? nil)
;                                   (setq possible-special-combination-state? nil)))
;                                ;; V[i]
;                                ((and (eq possible-special-combination-state? 'vi)
;                                      (=f kanji-code-offset #x03))        ; #x03 = small "i"
;                                 (twrite-string "vi")
;                                 (setq last-kana-code-offset? nil)
;                                 (setq possible-special-combination-state? nil))
        
;                                ;; Second part of special combination, if any:
        
;                                ;; [KI]yo
;                                ((member kanji-code-offset        ; possible Y-SUFFIX
;                                         jis-offsets-for-y-prefix-kana-characters)
;                                 (when last-kana-code-offset?
;                                   (twrite-string last-kana-string?)
;                                   (setq last-kana-code-offset? nil))
;                                 (setq possible-special-combination-state? 'y-suffix)
;                                 (setq last-kana-code-offset? kanji-code-offset))
;                                ;; [DE]i
;                                ((=f kanji-code-offset #x27)        ; "DE"
;                                 (when last-kana-code-offset?
;                                   (twrite-string last-kana-string?)
;                                   (setq last-kana-code-offset? nil))
;                                 (setq possible-special-combination-state? 'dhi)
;                                 (setq last-kana-code-offset? kanji-code-offset))
;                                ;; [tsu]TO
;                                ((=f kanji-code-offset #x23)        ; "tsu"
;                                 (when last-kana-code-offset?
;                                   (twrite-string last-kana-string?)
;                                   (setq last-kana-code-offset? nil))
;                                 (setq possible-special-combination-state? 'small-tsu)
;                                 (setq last-kana-code-offset? kanji-code-offset))
;                                ;; [V]i
;                                ((=f kanji-code-offset #x03)        ; "i"
;                                 (when last-kana-code-offset?
;                                   (twrite-string last-kana-string?)
;                                   (setq last-kana-code-offset? nil))
;                                 (setq possible-special-combination-state? 'vi)
;                                 (setq last-kana-code-offset? kanji-code-offset))

;                                ;; Not a special combination, print:
;                                (t
;                                 (when last-kana-code-offset?
;                                   (twrite-string last-kana-string?)
;                                   (setq last-kana-code-offset? nil))
;                                 (twrite-string (svref jis-kana-to-ascii kanji-code-offset))
;                                 (setq possible-special-combination-state? nil)))
;                              ))
;                           ;; Same as in convert-jis-string-to-text-string below.
;                            (t
;                              (when last-kana-code-offset?
;                                (twrite-string last-kana-string?)
;                                (setq last-kana-code-offset? nil))
;                            (cond
;                              ((upper-case-roman-jis-code-p kanji-code)
;                               (twrite-character
;                                 (convert-ascii-to-simple-character
;                                   (+f #.(convert-simple-character-to-ascii #\A)
;                                       (-f kanji-code #x2341)))))
;                              ((lower-case-roman-jis-code-p kanji-code)
;                               (twrite-character
;                                 (convert-ascii-to-simple-character
;                                   (+f #.(convert-simple-character-to-ascii #\a)
;                                       (-f kanji-code #x2361)))))
;                              ((numeric-jis-code-p kanji-code)
;                               (twrite-character
;                                 (convert-ascii-to-simple-character
;                                   (+f #.(convert-simple-character-to-ascii #\0)
;                                       (-f kanji-code #x2330)))))
;                              (t (loop-finish)))))



;;; `Tflush-stripped-kana-buffer-if-necessary' writes the Romaji form of the kana
;;; in the stripped kana buffer.

(defun tflush-stripped-kana-buffer-if-necessary
       (stripped-kana-buffer number-of-bytes-in-stripped-kana-buffer)
  (let* ((stripped-kana-buffer-index 0))
    (loop while (<f stripped-kana-buffer-index
                    number-of-bytes-in-stripped-kana-buffer)
          do
      (multiple-value-bind (translation? stripped-kana-buffer-index-increment?)
          (map-longest-possible-substring-using-jis-map
            stripped-kana-buffer kana-to-ascii-map
            stripped-kana-buffer-index
            number-of-bytes-in-stripped-kana-buffer
            maximum-length-of-kana-string)
        (cond
          ((gensym-string-p translation?)
           (twrite-string translation?)
           (incff stripped-kana-buffer-index
                  stripped-kana-buffer-index-increment?))
          (t
           (incff stripped-kana-buffer-index)))))))




;;; `Convert-to-ascii-roman-if-possible' returns either a new text string that is
;;; the ascii roman equivalent of string, or nil if there is no such equivalent.
;;; There is such an equivalent only if string consists exclusively of simple
;;; roman, Kanji roman, hiragana, and katakana characters.  If case-normalization?
;;; is CHAR-UPCASE, the result will have upper-case characters only, or if
;;; case-normalization? is CHAR-DOWNCASE, it will have lower-case characters only.

(defun convert-to-ascii-roman-if-possible
       (text-string-to-convert case-normalization?)
  (let* ((success? nil)
         (stripped-kana-buffer
           (obtain-lisp-string (text-string-length text-string-to-convert)))
         (stripped-kana-buffer-index 0))
    (let* ((new-text-string
             (twith-output-to-text-string
               (loop with string-length
                       = (text-string-length text-string-to-convert)
                     with string-index = 0
                     with character
                     with jis-code?
                     when (>=f string-index string-length)
                       do (setq success? t)
                          (loop-finish)
                     do
                 (setq character
                       (read-character-from-text-string
                         text-string-to-convert string-index))
                 (setq jis-code?
                       (map-unicode-to-JIS-X-0208 (wide-character-code character)))


                 (cond
                   (jis-code?
                    (cond
                      ((or (hiragana-jis-code-p jis-code?)
                           (katakana-jis-code-p jis-code?))
                       (setf (char stripped-kana-buffer
                                   stripped-kana-buffer-index)
                             (code-char (logandf #xFF jis-code?)))
                       (incff stripped-kana-buffer-index))
                      ;; Same as in convert-jis-string-to-text-string below.
                      (t
                       (when (>f stripped-kana-buffer-index 0)
                         (tflush-stripped-kana-buffer-if-necessary
                           stripped-kana-buffer stripped-kana-buffer-index)
                         (setq stripped-kana-buffer-index 0))
                       (cond
                         ((upper-case-roman-jis-code-p jis-code?)
                          (twrite-character
                            (code-wide-character
                              (+f #.(wide-character-code #.%\A)
                                  (-f jis-code? #x2341)))))
                         ((lower-case-roman-jis-code-p jis-code?)
                          (twrite-character
                            (code-wide-character
                              (+f #.(wide-character-code #.%\a)
                                  (-f jis-code? #x2361)))))
                         ((numeric-jis-code-p jis-code?)
                          (twrite-character
                            (code-wide-character
                              (+f #.(wide-character-code #.%\0)
                                  (-f jis-code? #x2330)))))
                         (t ;; Punt
                          (loop-finish))))))
                   ((alpha-char-pw character)
                    (when (>f stripped-kana-buffer-index 0)
                      (tflush-stripped-kana-buffer-if-necessary
                        stripped-kana-buffer stripped-kana-buffer-index)
                      (setq stripped-kana-buffer-index 0))
                    (twrite-char
                      (if (lower-case-pw character)
                          (case case-normalization?
                            (char-upcase (char-upcasew character))
                            (t character))
                          (case case-normalization?
                            (char-downcase (char-downcasew character))
                            (t character)))))
                   ((wide-character-member
                      character
                      allowable-non-alpha-characters-in-kfep-conversions)
                    (when (>f stripped-kana-buffer-index 0)
                      (tflush-stripped-kana-buffer-if-necessary
                        stripped-kana-buffer stripped-kana-buffer-index)
                      (setq stripped-kana-buffer-index 0))
                    (twrite-character character))
                   (t
                    (loop-finish)))))))
      (reclaim-lisp-string stripped-kana-buffer)
      (cond
        (success? new-text-string)
        (t (reclaim-text-string new-text-string)
           nil)))))


;; Consider using the mapping in kana-to-ascii-map.  This would collapse
;; the representation of ascii-kana and kana-ascii down to one facility.  -pto
;; 23jul90


;; The logic will have to be revised if, as expected, the conversion of a hiragana or
;; katakana character to a series of roman characters is not context-free.





;;; `Convert-to-hiragana-in-jis-string-if-possible' returns either a new jis string
;;; containing the hiragana equivalent of string together with a second value that
;;; specifies the actual number of bytes of the jis string used for the hiragana
;;; equivalent, or else nil if there is no such hiragana equivalent.

;; Not to be called in EDIT.LISP.
(defun convert-to-hiragana-in-jis-string-if-possible (text-string)
  (let ((ascii-roman-text-string?
          (convert-to-ascii-roman-if-possible text-string nil)))
    (if ascii-roman-text-string?
        (let* ((ascii-roman-string-length
                (text-string-length ascii-roman-text-string?))
               last-character-is-m?
               (number-of-jis-characters-available
                 (twicef ascii-roman-string-length))
               (number-of-jis-bytes-available        ; in the worst case
                 (twicef number-of-jis-characters-available))
               (jis-string-for-hiragana
                 (obtain-jis-string
                   number-of-jis-characters-available))
               ascii-roman-lisp-string)

          ;; Prevent ascii "m" from being converted to hiragana "n"
          (setq last-character-is-m?
                (if (wide-character-member
                      (charw ascii-roman-text-string?
                             (-f ascii-roman-string-length 1))
                      '(#.%\M #.%\m))
                    (charw ascii-roman-text-string?
                           (-f ascii-roman-string-length 1))))
          (when last-character-is-m?
            (decff ascii-roman-string-length))

          (setq ascii-roman-lisp-string
                (copy-text-string-as-managed-lisp-string
                  ascii-roman-text-string?
                  0 ascii-roman-string-length))
          (reclaim-text-string ascii-roman-text-string?)

          (let* ((result
                   (roman_kana_g2                ; convert to Hiragana
                     ascii-roman-lisp-string ascii-roman-string-length
                     jis-string-for-hiragana number-of-jis-bytes-available 0))
                 (actual-number-of-jis-bytes
                   (if (=f result -1)                ; if error
                       0
                       (roman_kana_g2                ; get number of bytes in result
                         ascii-roman-lisp-string ascii-roman-string-length
                         jis-string-for-hiragana number-of-jis-bytes-available 1))))
            ;(print ascii-roman-lisp-string)
            ;(print jis-string-for-hiragana)
            (when last-character-is-m?
              (setf (jis-char jis-string-for-hiragana (halff actual-number-of-jis-bytes))
                    (convert-simple-alpha-character-to-jis-code
                      (ascii-code-char
                        (wide-character-code
                          last-character-is-m?))))        ; #x2341 = "A" in JIS
              (setq actual-number-of-jis-bytes
                    (+f actual-number-of-jis-bytes 2)))
            (reclaim-lisp-string ascii-roman-lisp-string)
            (cond
              ((>=f actual-number-of-jis-bytes 0)
               #+development
               (when *debug*
                 (format t "~%hira-in-jis-if-pos: ~s" jis-string-for-hiragana))
               (values jis-string-for-hiragana actual-number-of-jis-bytes))
              (t (reclaim-jis-string jis-string-for-hiragana)
                 nil))))
        (loop with string-length = (text-string-length text-string)
              with string-index = 0
              with jis-string-for-hiragana
                = (obtain-jis-string (halff string-length))        ; in the worst case
              with jis-string-index = 0
              with character
              with jis-code?
              when (>=f string-index string-length)
                return
                  (values jis-string-for-hiragana
                          (twicef jis-string-index))
              do (setq character
                       (read-character-from-text-string text-string string-index))
                 (setq jis-code?
                       (map-unicode-to-JIS-X-0208 character))
                 (cond
                   ((and jis-code?
                         (or (hiragana-jis-code-p jis-code?)
                             ))                        ; ALLOW CERTAIN PUNCTUATION!
                    (setf (jis-char jis-string-for-hiragana jis-string-index)
                          jis-code?)
                    (incff jis-string-index))
                   (t (loop-finish)))
              finally
                (reclaim-jis-string jis-string-for-hiragana)
                (return nil)))))



;;; `Convert-to-hiragana-if-possible' returns either a new text string representing
;;; the hiragana equivalent of string, or nil if there is no such equivalent.
;;; `Convert-to-katakana-if-possible' returns either a new text string representing
;;; the katakana equivalent of string or nil, if there is no such equivalent.
;;; At the present, these functions can only take Gensym strings of the following form:
;;;
;;;    [<jis-character>]<string-of-alphabetic-characters>
;;;
;;; For example, "\\+7abc" where "\\+7" is a Gensym character for a JIS Hiragana
;;; character.  Or "kyou", which is an alphabetic text string.

;; Used in EDIT.LISP
(defun convert-to-hiragana-if-possible (string)
  (multiple-value-bind (jis-string-for-hiragana? actual-number-of-jis-bytes?)
      (convert-to-hiragana-in-jis-string-if-possible string)
    (if jis-string-for-hiragana?
        (prog1
          (convert-jis-string-to-text-string
            jis-string-for-hiragana? (halff actual-number-of-jis-bytes?))
          (reclaim-jis-string jis-string-for-hiragana?)))))

;; Consider having this return nil when the result would be identical to string.




;;; `Convert-to-katakana-if-possible', an API function, takes a text string.
;;; This converts the contents to Katakana if possible.

;; Used in EDIT.LISP
(defun convert-to-katakana-if-possible (string)
  ;; For test purposes, this converts by changing to all caps if string ends in a vowel.
  (let ((ascii-roman-text-string?
          (convert-to-ascii-roman-if-possible string nil)))
    (if ascii-roman-text-string?
        (let* ((ascii-roman-string-length
                 (text-string-length ascii-roman-text-string?))
               (number-of-jis-characters-available        ; in the worst case
                 (twicef ascii-roman-string-length))
               (number-of-jis-bytes-available
                 (twicef number-of-jis-characters-available))
               (jis-string-for-katakana
                 (obtain-jis-string
                   number-of-jis-characters-available))
               last-character-is-m?
               ascii-roman-lisp-string)

          ;; Prevent ascii "m" from being converted to hiragana "n"
          (setq last-character-is-m?
                (if (wide-character-member
                      (charw ascii-roman-text-string?
                             (-f ascii-roman-string-length 1))
                      '(#.%\M #.%\m))
                    (charw ascii-roman-text-string?
                           (-f ascii-roman-string-length 1))))

          (when last-character-is-m?
            (decff ascii-roman-string-length))

          (setq ascii-roman-lisp-string
                (copy-text-string-as-managed-lisp-string
                  ascii-roman-text-string?
                  0 ascii-roman-string-length))

          (reclaim-text-string ascii-roman-text-string?)

          (let* ((result
                   (roman_kata_g2                ; convert to Katakana
                     ascii-roman-lisp-string ascii-roman-string-length
                     jis-string-for-katakana number-of-jis-bytes-available 0))
                 (actual-number-of-jis-bytes
                   (if (=f result -1)                ; if error
                       0
                       (roman_kata_g2                ; get number of bytes in result
                         ascii-roman-lisp-string ascii-roman-string-length
                         jis-string-for-katakana number-of-jis-bytes-available 1))))
            (when last-character-is-m?
              (setf (jis-char jis-string-for-katakana (halff actual-number-of-jis-bytes))
                    (convert-simple-alpha-character-to-jis-code
                      (ascii-code-char
                        (wide-character-code
                          last-character-is-m?))))        ; #x2341 = "A" in JIS
              (setq actual-number-of-jis-bytes
                    (+f actual-number-of-jis-bytes 2)))
            (prog1
                (if (>=f actual-number-of-jis-bytes 0)        ; also check if different?
                    (convert-jis-string-to-text-string
                      jis-string-for-katakana (halff actual-number-of-jis-bytes)))
              (reclaim-lisp-string ascii-roman-lisp-string)
              (reclaim-jis-string jis-string-for-katakana)))))))

;; Consider having this return nil when the result would be identical to string.




;;; `Convert-jis-string-to-text-string' converts jis-string, which contains
;;; actual-number-of-jis-characters characters, to an equivalent new text string.
;;; Roman characters in jis-string are converted to simple (non-Kanji) characters.

(defun convert-jis-string-to-text-string
    (jis-string actual-number-of-jis-characters)
  (twith-output-to-text-string
    (loop with string-is-simple? = nil
          for i from 0 below actual-number-of-jis-characters
          as kanji-code = (jis-gchar jis-string i string-is-simple?)
          do (cond
               ((upper-case-roman-jis-code-p kanji-code)
                (twrite-character
                  (code-wide-character
                    (+f #.(wide-character-code #.%\A)
                        (-f kanji-code #x2341)))))
               ((lower-case-roman-jis-code-p kanji-code)
                (twrite-character
                  (code-wide-character
                    (+f #.(wide-character-code #.%\a)
                        (-f kanji-code #x2361)))))
               ((numeric-jis-code-p kanji-code)
                (twrite-character
                  (code-wide-character
                    (+f #.(wide-character-code #.%\0)
                        (-f kanji-code #x2330)))))
               ((=f kanji-code #x216c)                ;  a '
                (twrite-character #.%\'))
               ((not (legal-gensym-jis-character-code-p ; condition should never be true
                       ;; Here, kanji code is a JIS code, not a Gensym JIS
                       ;; code, though they happen to be the same.
                       (jis-to-gensym-jis kanji-code)))
                ;; it shouldn't get here, but it would have worked without
                ;; squacking: if code was something strange, such as 3, it would
                ;; simply write that out as a "kanji" \ extended Gensym
                ;; cahracter, i.e., in the case of code = 3:
                ;;
                ;;    \ (#
                ;;
                ;; So, we'll handle this by just writing the character
                ;; for that code.  Assuming they're always ASCII graphic
                ;; characters or control codes, there should be no problem.
                ;;
                ;; Still, we'll warn in development.
                ;;
                ;; (MHD 5/21/96)
                #+development
                (warn "~a is not an ASCII code or legal JIS code!" kanji-code)
                (twrite-character
                  (coerce-to-wide-character kanji-code)))
               (t (twrite-character
                    (coerce-to-wide-character
                      (map-JIS-X-0208-to-unicode kanji-code))))))))






;;; Convert-kanji-codes-to-text-string ... is just for development.  It converts
;;; kanji-codes, a list of Kanji (JIS) character codes, into a text string
;;; representing those codes.

#+development
(defun convert-kanji-codes-to-text-string (kanji-codes)
  (twith-output-to-text-string
    (loop for kanji-code in kanji-codes
          do (twrite-character
               (coerce-to-wide-character
                 (map-JIS-X-0208-to-unicode kanji-code))))))













;;;; CONVERTER (Hiragana-to-Kanji)



;;;`Jis-string-is-an-acceptable-translation-p' returns nil for jis strings
;;; that are:
;;;   1. not a null string,
;;;   2. not the same as the original jis string up to length - characters-to-drop.
;;;   3. not already selected as an acceptable translation, and,

(def-substitution-macro jis-string-is-an-acceptable-translation-p
                        (translated-jis-string
                          original-jis-string
                          list-of-acceptable-translated-jis-strings-so-far
                          characters-to-drop)        ; in jis-chars terms (i.e. double)
  (let ((translated-jis-string-length
          (-f (length translated-jis-string)
              (twicef characters-to-drop))))
    (and (/=f translated-jis-string-length 0)
         (not (string= translated-jis-string original-jis-string
                       :end1 translated-jis-string-length))
         (loop for unacceptable-string
                   in list-of-acceptable-translated-jis-strings-so-far
               never (string= translated-jis-string unacceptable-string
                              :end1 translated-jis-string-length)))))


;;; `Number-of-characters-untranslated' returns the number of jis characters at
;;; the end of translated-jis-string that are the same as those in original-
;;; jis-string.

(defun number-of-characters-untranslated
       (translated-jis-string original-jis-string)
  (loop with largest-index-of-translated-jis-string
          = (-f (jis-string-length translated-jis-string) 1)
        with largest-index-of-original-jis-string
          = (-f (jis-string-length original-jis-string) 1)
        with original-jis-string-is-simple? = nil
        with translated-jis-string-is-simple? = nil
        for original-jis-string-index
            from largest-index-of-original-jis-string
            downto 0
        for translated-jis-string-index
            from largest-index-of-translated-jis-string
            downto 0
        when (/=f (jis-gchar
                    translated-jis-string translated-jis-string-index
                    translated-jis-string-is-simple?)
                  (jis-gchar
                    original-jis-string original-jis-string-index
                    original-jis-string-is-simple?))
          do (loop-finish)
        count t))




;;; `Maximum-number-of-hiragana-bytes-to-translate' is a magic number which
;;; limits the number of bytes (twice the number of jis codes) that gets passed
;;; to CTC's translator.  The reason for this limit is that CTC's translator
;;; has a bug which will cause a bomb-out if it is given a string that is
;;; too long.

(defparameter maximum-number-of-hiragana-bytes-to-translate 40)




;;; `Get-list-of-choices-of-kanji-translation' returns two values.  The first is
;;; a slot value list of jis strings which were translated by kka_P_batkanakan.
;;; The second value is the number of jis characters from the hiragana jis buffer
;;; used to produce the translation.
;;;
;;; If hiragana-jis-buffer has a fill pointer, there might be translation problems
;;; on several platforms.

(defun get-list-of-choices-of-kanji-translation
       (hiragana-jis-buffer number-of-hiragana-bytes)
  (if (>f number-of-hiragana-bytes
          maximum-number-of-hiragana-bytes-to-translate)
      (setq number-of-hiragana-bytes
            maximum-number-of-hiragana-bytes-to-translate))
  (let* ((number-of-hiragana-characters
           (halff number-of-hiragana-bytes))
         (length-of-kanji-buffer                ; does this need to be communicated to
           (maxf (halff number-of-hiragana-bytes)        ;  kka_P_batkanakan?! (MHD 1/3/91)
                 30))
         (kanji-buffer
           (obtain-jis-string length-of-kanji-buffer))
         (choices nil)
         (tail-of-choices nil)
         (hiragana-jis-string
           (convert-n-bytes-to-jis-string
             hiragana-jis-buffer number-of-hiragana-bytes))
         (number-of-characters-not-used
           number-of-hiragana-characters))
    (multiple-value-bind (number-of-jis-characters-used
                          number-of-output-bytes?
                          number-of-candidates-left?)
        (kka_P_batkanakan
          #.kkaprimitive-first-candidate
          hiragana-jis-buffer
          number-of-hiragana-bytes
          kanji-buffer)
      (loop while (>f number-of-jis-characters-used 0)
            as jis-string
               = (convert-n-bytes-to-jis-string
                   kanji-buffer number-of-output-bytes?)
            as characters-to-drop
            = (number-of-characters-untranslated
                jis-string hiragana-jis-string)
            do
        (if (<=f characters-to-drop number-of-characters-not-used)
            (progn
              (when (<f characters-to-drop number-of-characters-not-used)
                ;; no reclamation of strings -- is this a leak??!!!!
                ;; (PTO might have thought that reclaim-slot-value-list
                ;; reclaimed strings!!) (MHD 12/11/90) -- YES. Fixed
                ;; to call reclaim-slot-value instead of reclaim-slot-
                ;; value-list below. (MHD 1/3/91)
                (reclaim-slot-value choices)
                (setq choices nil)
                (setq number-of-characters-not-used characters-to-drop))
              (if (jis-string-is-an-acceptable-translation-p
                    jis-string hiragana-jis-string choices
                    characters-to-drop)
                  ;; Then
                  (enqueue-1
                           (if (=f characters-to-drop 0)
                               jis-string
                               (prog1
                                 (jis-string-substring        ; reclaim jis-string below
                                   jis-string
                                   0
                                   (-f (jis-string-length jis-string)
                                       characters-to-drop))
                                 (reclaim-jis-string jis-string)))
                           choices
                           tail-of-choices
                           slot-value-cons)
                  (reclaim-jis-string jis-string)))
            (reclaim-jis-string jis-string))
        (if (<=f number-of-candidates-left? 0)
            (return choices)
            (multiple-value-setq (number-of-jis-characters-used
                                  number-of-output-bytes?
                                  number-of-candidates-left?)
              (kka_P_batkanakan
                #.kkaprimitive-next-candidate
                hiragana-jis-buffer
                number-of-hiragana-bytes
                kanji-buffer)))
            finally
              (return choices)))
    (reclaim-jis-string hiragana-jis-string)
    (reclaim-jis-string kanji-buffer)
    (values choices (-f number-of-hiragana-characters
                        number-of-characters-not-used))))



;;; `Search-for-longest-prefix-with-kfep-word-choices' attempts to convert
;;; a text string which contains Hiragana gensym characters to a list of text
;;; strings (prefixes) which contain Kanji equivalent of the translateable part
;;; of the original text string.
;;;
;;;    If no conversion is possible, nil is returned.
;;;
;;;    If conversions are possible,
;;;
;;;      1. a slot value list of translated prefixes is returned as the first value,
;;;      2. the number of Gensym characters from text-string used to create these
;;;         prefixes as the second value.
;;;
;;; The prefixes are guaranteed to be translated from the maximum number of characters
;;; in the original text string; so the second value is the maximum possible.

;;; Any conversions returned must use at least minimum-number-of-gensym-
;;; characters-to-convert gensym characters from text-string.

;;; [The following has not yet been implemented. -mhd]
;;;
;;; When ok-to-get-first-choice-only? is non-nil this function may return
;;;
;;;    (<first-choice> T)
;;;
;;; as the first value.  This argument is intended to be used when there is only
;;; one Hiragana character to be translated in the original text string.  When
;;; there is only one Hiragana character, there are many possible translations,
;;; so we might want to show users only one choice first.

;; [Peng: As you approach my advanced age, you too may decide to omit, from
;; your documentation, everything that is obvious or can reasonably be deduced
;; from looking at the definition header (up through the arg list).]

;; New search-for-longest-prefix-with-kfep-word-choices.  -pto 22jun90

(defun search-for-longest-prefix-with-kfep-word-choices
       (text-string
        minimum-number-of-gensym-characters-to-convert
        &optional (ok-to-get-first-choice-only? nil))
  ok-to-get-first-choice-only?
  #+development
  (check-memory-for-development
    'entering-search-for-longest-prefix-with-kfep-word-choices)
  (let* ((jis-text-strings? nil)
         (number-of-characters-used? nil))
    (when (/=f (length text-string) 0)
      (multiple-value-bind (jis-string-to-translate? actual-number-of-jis-bytes?)
          (convert-to-jis-string-if-possible text-string)
        ;; We assume that if jis-string? is non-nil, there is a one-to-one
        ;; mapping between the Gensym characters in text-string and the
        ;; jis codes in jis-string?.
        (when jis-string-to-translate?
          (let ((jis-buffer jis-string-to-translate?)
                (reclaim? nil))
            (gensym-assert (=f (modf actual-number-of-jis-bytes? 2) 0))
            (when (array-has-fill-pointer-p jis-string-to-translate?)
              ;; Ensure that the buffer does not have a fill pointer.
              (setq reclaim? t)
              (setq jis-buffer
                    (copy-managed-lisp-string
                      jis-string-to-translate?
                      0 actual-number-of-jis-bytes?)))
            (loop with number-of-bytes-in-jis-string-to-translate
                    = actual-number-of-jis-bytes?
                  while (and (null jis-text-strings?)
                             (>=f (halff number-of-bytes-in-jis-string-to-translate)
                                  minimum-number-of-gensym-characters-to-convert))
                  do (multiple-value-bind
                       (slot-value-list-of-jis-strings number-of-gensym-characters-used)
                       (get-list-of-choices-of-kanji-translation
                         jis-buffer number-of-bytes-in-jis-string-to-translate)

                       (when slot-value-list-of-jis-strings
                         ;; Set jis-text-strings?.  Slot-value-list-of-jis-strings
                         ;; get recycled into the value for jis-text-strings? here.
                         (loop for l on slot-value-list-of-jis-strings
                               as jis-string = (car l)
                               do (setf (car l)
                                        (convert-jis-string-to-text-string
                                          jis-string
                                          (halff (length jis-string))))
                                  (reclaim-jis-string jis-string)
                               finally
                                 (setq jis-text-strings?
                                       slot-value-list-of-jis-strings)))

                       (setq number-of-characters-used?
                             number-of-gensym-characters-used))

                     ;;(decff number-of-bytes-in-jis-string-to-translate 2)
                     ;; Don't bother trying to translate fewer characters - assume
                     ;; that kka_p_batkanakan will translate the apropriate
                     ;; number of characters.  So we just need to return here:
                     (return)

                     )
            (if reclaim? (reclaim-lisp-string jis-buffer))))))
    (values jis-text-strings? number-of-characters-used?)))






;;;; LEARNING




;;; `Note-kfep-conversion-choice' tells the Kanji converter which of the possible
;;; conversion choices for string was chosen by the user.  List-of-choices must
;;; have been computed from string by means of compute-kfep-conversion-choices.
;;; Choice-index is an integer that indicates which element of list-of-choices was
;;; chosen; it is 0-based.

(defparameter kfep-learning-capability? nil)

(defun note-kfep-conversion-choice (string list-of-choices choice-index)
  (declare (ignore string list-of-choices))
  (when kfep-learning-capability?
;    (loop for choice in list-of-choices
;          as index from 0
;          do
;          (if (string-equal string list-of-choices)
;              (kka_P_updatekojin index)))
    (kka_P_updatekojin choice-index)
    ))









;;;; Start of Old KFEP4




;;;; KFEP Debugging Facilities



#+development
(progn


(defun p-kfep-m-table (index)                        ; probe kfep m table
  (let* ((entry (svref kfep-m-table index)))
    (format t "~&kfep-m-table[~a]={" index)
    (format t "~s" (kfep-master-midashi entry))
    (format t ", #x~2,'0x~2,'0x~2,'0x~2,'0x, #x~2,'0x~2,'0x}~%"
            (ascii-char-code (char (kfep-master-offset entry) 0))
            (ascii-char-code (char (kfep-master-offset entry) 1))
            (ascii-char-code (char (kfep-master-offset entry) 2))
            (ascii-char-code (char (kfep-master-offset entry) 3))
            (ascii-char-code (char (kfep-master-nbyte entry) 0))
            (ascii-char-code (char (kfep-master-nbyte entry) 0))))
  0)




(defun kfep-master-header (index)                ; probe master header
  (format t "~&kfep-master-header[~a]=#x~8,'0x, or ~a"
          index (svref kfep-master-header index)
          (svref kfep-master-header index)))

(defun kfep-kojin-header (index)                ; probe kojin header
  (format t "~&kfep-kojin-header[~a]=#x~8,'0x, or ~a"
          index (svref kfep-kojin-header index)
          (svref kfep-kojin-header index)))








;;;; Describing KFEP Contents


(defun print-char-in-hex (char)
  (format t "~2,'0x" (ascii-char-code char)))

(defun print-string-in-hex (string)
  (loop for index from 0 below (length string)
        do (print-char-in-hex (char string index))))


(defun describe-kfep-gobisetu (symbol)
  (let* ((array (symbol-value symbol)))
    (loop for index from 0 below (length array)
          as entry = (svref array index)
          do
      (when entry
        (format t "~&~a[~3,'0d] = ~%" symbol index)
        (format t "~&   kfep-gobitype-gobi   = ")
        (print-string-in-hex (kfep-gobitype-gobi entry))
        (terpri)
        (format t "~&   kfep-gobitype-katuyo = ~a~%"
                (kfep-gobitype-katuyo entry))
        (format t "~&   kfep-gobitype-bogi   = ~a~%"
                (kfep-gobitype-bogi entry)))))
  (terpri))



(defun describe-kfep-xx-index (symbol)
  (let* ((array (symbol-value symbol)))
    (loop for index from 0 below (length array)
          as entry = (svref array index)
          do
      (when entry
        (format t "~&~a[~3,'0d] = ~%" symbol index)
        (format t "~&   kfep-bunindex-length = ~a~%"
                (kfep-bunindex-length entry))
        (format t "~&   kfep-bunindex-start  = ~a~%"
                (kfep-bunindex-start entry))
        (format t "~&   kfep-bunindex-end  = ~a~%"
                (kfep-bunindex-end entry)))))
  (terpri))


(defun describe-kfep-xxxxx-index (symbol)
  (let* ((array (symbol-value symbol)))
    (loop for index from 0 below (length array)
          as entry? = (svref array index)
          when entry?
            do (format t "~&~a[~3,'0d] = ~%" symbol index)
               (format t "~&   kfep-jjdkkd-key = ~s or "
                       (kfep-jjdkkd-key entry?))
               (print-string-in-hex (kfep-jjdkkd-key entry?))
               (terpri)
               (format t "~&   kfep-jjdkkd-hinsi  = ~a~%"
                       (kfep-jjdkkd-hinsi entry?))
               (format t "~&   kfep-jjdkkd-katuyo  = ~a~%"
                       (kfep-jjdkkd-katuyo entry?))
               (format t "~&   kfep-jjdkkd-bunbun  = ~32b~%"
                       (kfep-jjdkkd-bunbun entry?))))
  (terpri))


(defun describe-kfep ()
  "Describes the contents of the variables of KFEP."

  (let* (#+lucid
         (sys::*gc-silence* t))

    (format t "~&kfep-master-header = ~a~%" kfep-master-header)
    (loop for index from 0 below (kfep-master-header-size)
          do (format t "~&kfep-master-header[~2,'0d] = ~a~%"
                     index
                     (svref kfep-master-header index)))
    (format t "~&kfep-master-header-in-characters = ~s, length=~a~%"
            kfep-master-header-in-characters
            (length kfep-master-header-in-characters))

    (format t "~&kfep-kojin-header = ~a~%" kfep-kojin-header)
    (loop for index from 0 below (kfep-kojin-header-size)
          do (format t "~&kfep-kojin-header[~2,'0d] = ~a~%"
                     index
                     (svref kfep-kojin-header index)))

    (format t "~&kfep-tablemax = ~a~%" kfep-tablemax)

    (format t "~&kfep-index-file-stream = ~a~%" kfep-index-file-stream)
    (format t "~&kfep-main-file-stream  = ~a~%" kfep-main-file-stream)
    (format t "~&kfep-kojin-file-stream = ~a~%" kfep-kojin-file-stream)

    (format t "~&kfep-m-table = ~a~%" kfep-m-table)
    (loop for index from 0 below (kfep-m-table-size)
          as entry = (svref kfep-m-table index)
          as midashi = (kfep-master-midashi entry)
          do
          (when (not (and (=f (ascii-char-code (char midashi 0)) 0)
                          (=f (ascii-char-code (char midashi 1)) 0)
                          (=f (ascii-char-code (char midashi 2)) 0)))
            (format t "~&kfep-m-table[~3,'0d] =~%" index)
            (format t "~&   kfep-master-midashi = ~s or " midashi)
            (print-string-in-hex (kfep-master-midashi entry))
            (format t "~&   kfep-master-offset  = ~s or #x" midashi)
            (print-string-in-hex (kfep-master-offset entry))
            (format t "~&   kfep-master-nbyte   = ~s or #x" midashi)
            (print-string-in-hex (kfep-master-nbyte entry))
            (terpri)))
    (terpri)

    (let* ((substring (subseq kfep-kojin-usedbits 0 20)))
      (format t "~&kfep-kojin-usedbits = \"~a ...\" or " substring)
      (print-string-in-hex substring))

    (let* ((substring (subseq kfep-kojin-bunpobits 0 20)))
      (format t "~&kfep-kojin-bunpobits = \"~a ...\" or " substring)
      (print-string-in-hex substring))
    (terpri)

    (loop for index from 0 below (minf 30 (halff (halff (kfep-k-hindex))))
          do (format t "~&kfep-kojin-index[~2,'0d] = ~a~%"
                     index (svref kfep-kojin-index index)))
    (terpri)

    (format t "~&kfep-kojin-hyolen = ~a~%" kfep-kojin-hyolen)

    (format t "~&kfep-batchyomi = ~s or " kfep-batchyomi)
    (print-string-in-hex kfep-batchyomi)
    (format t "~&kfep-batchyomilen = ~a~%" kfep-batchyomilen)
    (terpri)

    (loop for index from 0 below (kfep-bunsetumax)
          do
          (format t "~&kfep-battable[~2,'0d] = " index)
          (describe (svref kfep-battable index)))
    (terpri)

    (format t "~&kfep-kka-usetblnum = ~a~%" kfep-kka-usetblnum)

    (describe-kfep-gobisetu 'kfep-gobisetu1)
    (describe-kfep-gobisetu 'kfep-gobisetu2)

    (describe-kfep-xx-index 'kfep-ta-index)
    (describe-kfep-xx-index 'kfep-sa-index)
    (describe-kfep-xx-index 'kfep-jd-index)
    (describe-kfep-xx-index 'kfep-kk-index)

    (describe-kfep-xxxxx-index 'kfep-jyodou-array)
    (describe-kfep-xxxxx-index 'kfep-jyosi-array)
    (describe-kfep-xxxxx-index 'kfep-keiyo-array)
    (describe-kfep-xxxxx-index 'kfep-taigen-array)
    (describe-kfep-xxxxx-index 'kfep-taigen-array)
    (describe-kfep-xxxxx-index 'kfep-sahen-array)

    (format t "~&specified-kfep-index-filename? = ~s~%"
            specified-kfep-index-filename?)
    (format t "~&specified-kfep-main-filename? = ~s~%"
            specified-kfep-main-filename?)
    (format t "~&specified-kfep-kojin-filename? = ~s~%"
            specified-kfep-kojin-filename?)))



(defun break-up-kfep-batch-hyoki (kfep-batch-hyoki-string)
  (loop with length = (length kfep-batch-hyoki-string)
        for index from 0 below length
        as char = (char kfep-batch-hyoki-string index)
        as golen = (ascii-char-code char)
        do (print-char-in-hex char)
           (princ " ")
           (loop for j from 0 below golen
                 do
             (incff index)
             (print-char-in-hex (char kfep-batch-hyoki-string index)))
           (princ " ")
           (incff index)
           (print-char-in-hex (char kfep-batch-hyoki-string index))
           (terpri)))

(defun peek-at-choices ()
  (break-up-kfep-batch-hyoki (kfep-batch-hyoki (svref kfep-battable 0))))


) ; end of #+development (progn ...)    (KFEP Debugging Facilities)








;;;; Generating Korean Character Set (KSC) Byte Ranges

#+development
(progn



(progn) ; establish col. 0 formatting

;;; Generate-legal-ksc-byte-ranges generates a list of the form
;;;
;;;   (  { (high-byte-with-gaps . { low-byte-gap } ) } )
;;;
;;; where each high-byte-with-gaps is a legal ksc high byte (i.e., in the
;;; range [#x21..#x7d]), and each low-byte-gap is a cons of the form
;;;
;;;   (low-byte-gap-min . low-byte-gap-max)
;;;
;;; where low-byte-gap-min and low-byte-gap-max are the lowest and highest
;;; in a range of gaps in this high-byte row of character codes.

(defun generate-legal-ksc-byte-ranges ()
  (loop for high-byte
            from ksc-high-byte-min
            to ksc-high-byte-max
        as low-byte-gaps?
           = (loop with gap-range-start? = nil
                   with gap-range-end? = nil
                   with gaps = nil
                   for low-byte
                       from ksc-low-byte-min
                       to ksc-low-byte-max
                   as last-time? = (=f low-byte ksc-low-byte-max)
                   do (cond
                        ((not (legal-gensym-ksc-character-code-p
                                (ksc-to-gensym-ksc
                                  (+f (ashf high-byte 8)
                                      low-byte))))
                         (cond
                           (gap-range-end?
                            (incff gap-range-end?)
                            (if last-time?
                                (push (cons gap-range-start? gap-range-end?)
                                      gaps)))
                           (t
                            (setq gap-range-start? low-byte)
                            (setq gap-range-end? low-byte))))
                        (gap-range-start?
                         (push (cons gap-range-start? gap-range-end?)
                               gaps)
                         (setq gap-range-start? nil)
                         (setq gap-range-end? nil)))
                   finally
                     (return gaps))
        when low-byte-gaps?
          collect
            `(,high-byte . ,low-byte-gaps?)))

;; The above is used to generate the value of ksc-gap-map, which is defined
;; in CHARACTERS.  (MHD 11/17/92)

)



;;;; Printing an Asian Character Set Chart


#+development
(progn

(progn)

;;; `Make-jis-workspaces', `make-ks-workspaces', and `make-gb-workspaces' are
;;; used in development to create top-level workspaces with codes for jis, ks,
;;; and gb charsets respectively.  It does not clear KBs or save KBs.  See
;;; make-cjk-codes-kls for that.

(defun make-jis-workspaces ()
  (make-cjk-character-set-workspaces 'jis))


(defun make-ks-workspaces ()
  (make-cjk-character-set-workspaces 'ks))


(defun make-gb-workspaces ()
  (make-cjk-character-set-workspaces 'gb))



;;; `Make-cjk-codes-kls' is intended to be used in development to generate the
;;; KBs (actually, ".KL" files) jiscodes.kl, kscodes.kl, and gbcodes.kl.
;;; Earlier versions of jiscodes.kl and kscodes.kl were created by other means
;;; in G2 4.0.  This routine has been used to create these KBs for the release
;;; pending 5/12/99, which is 5.2.
;;;
;;; To use this, type C-M-Esc in a running G2 local window.  This gets you into
;;; a breakpoint in which there should be a current workstation (so it can
;;; create and save a pane layout).  Then evaluate the form
;;; (make-cjk-codes-kls).  At the end, the KB you had before the break has been
;;; cleared, and you are left with the last KB created (gbcodes.kl) as your
;;; current KB.

#+development
(defun make-cjk-codes-kls ()
  (when
      #-(or sbcl clozure)
      (system::y-or-n-p "Throw away the current KB, write 3 KLs to the current directory?")
      #+(or sbcl clozure)
      (progn
        (cerror "Go ahead"
                "About to throw away the current KB and write 3 KLs to the current directory!")
        t)
    (format t "~%OK...")
    (loop for charset in '(jis ks gb)
          do (format t "~%Clearing KB ...")
             (clear-kb)
             (format t " Done.")
             (format t "~%Creating Workspaces for charset ~A ..." charset)
             (funcall 'make-cjk-character-set-workspaces charset)
             (format t " Done.")
             (maybe-schedule-service-workstations t)
             (let ((gensym-pathname
                     (gensym-pathname (tformat-text-string "~(~A~)codes.kl" charset))))
               (format
                 t "~%Saving KB for charset ~A as ~s ..."
                 charset (gensym-namestring gensym-pathname))
               (save-kb gensym-pathname 'KB-SAVE nil)
               (format t " Done.")))
    (format t "~%-- All Done. --~%")))









(defconstant ideographic-space-unicode
  (map-jis-x-0208-to-unicode jis-space-character-code))
(defconstant ideographic-space-character
  (code-wide-character ideographic-space-unicode))


(defconstant ideographic-colon-unicode
  (map-jis-x-0208-to-unicode jis-colon-character-code))
(defconstant ideographic-colon-character
  (code-wide-character ideographic-colon-unicode))



(defun ascii-to-jis-hex-digit (ascii-hex-digit)
  (let ((weight
          (if (<=f (char-codew #.%\A)
                   (char-codew (char-upcasew ascii-hex-digit))
                   (char-codew #.%\F))
              (+f 10
                  (-f (char-codew (char-upcasew ascii-hex-digit))
                      (char-codew #.%\A)))
              (-f (char-codew ascii-hex-digit)
                  (char-codew #.%\0)))))
    (jis-hex-digit-char weight)))

(defun jis-hex-digit-char (weight)
  (if (<f weight 10)
      (+f jis-0-digit-character-code weight)
      (+f jis-letter-A-character-code (- weight 10))))

(defun ideographic-hex-digit-char (weight)
  (code-wide-character
    (map-jis-x-0208-to-unicode
      (jis-hex-digit-char weight))))

(defun twrite-byte-pair-as-ideographic-hex (byte-1 byte-2)
  (tformat "~c~c~c~c"
           (ideographic-hex-digit-char (ashf byte-1 -4))
           (ideographic-hex-digit-char (logandf byte-1 #xF))
           (ideographic-hex-digit-char (ashf byte-2 -4))
           (ideographic-hex-digit-char (logandf byte-2 #xF))))

(defun twrite-cjk-row-box-stub (row-number) ; NB: row-number here is 1-based
  (multiple-value-bind (d1 d2)
      (truncatef row-number 10)
    (loop repeat (if (>f d1 0) 1 2)
          do (twrite-character ideographic-space-character))
    (when (>f d1 0) (twrite-character (ideographic-hex-digit-char d1)))
    (twrite-character (ideographic-hex-digit-char d2))
    (twrite-char ideographic-colon-character)
    (twrite-char ideographic-space-character)))

(defun map-cjk-code-to-unicode-per-charset (cjk-code charset)
  (case charset
    (jis (map-jis-x-0208-to-unicode cjk-code))
    (ks (map-ks-c-5601-to-unicode cjk-code))
    (gb (map-gb-2312-to-unicode cjk-code))))

(defun make-cjk-row-box (charset row-number)
  (multiple-value-bind (high-min high-max low-min low-max)
      (get-cjk-charset-range-edges charset)
    (if (<=f high-min row-number high-max)
        (make-free-text-box
          (twith-output-to-text-string
            (twrite-cjk-row-box-stub (+f (-f row-number high-min) 1))
            (loop for i from 0 to #xf
                  as last-time? = (=f i #xf)
                  do (twrite-character (ideographic-hex-digit-char i))
                     (unless last-time?
                       (twrite-character ideographic-space-character)))
            (tformat "~%")
            ;; rows:
            (twrite-cjk-row-box-rows
              charset row-number
               low-min low-max))
         'character-inserter))))

(defun twrite-cjk-row-box-rows (charset row-number low-min low-max)
  (loop for box-row
        from (logandf #xf0 low-min) to (logandf #xf0 low-max) by #x10
        as last-time? = (= box-row #x70)
        do (twrite-byte-pair-as-ideographic-hex row-number box-row)
           (twrite-character ideographic-space-character)
           (loop for box-column from 0 to #xf
                 as cjk-code
                    = (+ (ash row-number 8)
                         (+ box-row box-column))
                 as unicode?
                    = (map-cjk-code-to-unicode-per-charset
                        cjk-code charset)
                 do (twrite-character
                      (or unicode? ideographic-space-character))
                    (twrite-character ideographic-space-character))
           (unless last-time? (tformat "~%"))))




(defun make-one-cjk-character-set-workspace
       (charset
         starting-row-number number-of-rows &optional name? scale? put-at-the-bottom?)
  (let ((workspace (make-new-top-level-kb-workspace 'kb-workspace)))
    (change-slot-value workspace 'workspace-margin 3)
    (when name?
      (change-slot-value workspace 'name-or-names-for-frame name?))
    (lay-down-column-of-cjk-row-boxes
      charset
      starting-row-number number-of-rows
      workspace
      (+w (left-edge-of-block workspace) (workspace-margin workspace))
      (if (has-subblocks-p workspace)                        ; i.e., a name box
          (+w (loop for subblock being each subblock of workspace
                    maximize (bottom-edge-of-block subblock))
              10)
          (+w (top-edge-of-block workspace) (workspace-margin workspace))))
    (loop for workstation in workstations-in-service
          as pane = (detail-pane        ; works most of the time in development, but
                                        ;   not full-blown enough for real use
                     (window-for-workstation workstation))
          do (put-workspace-on-pane
              workspace pane
              'center 'center scale?
              :at-the-bottom? put-at-the-bottom?))))


(defun lay-down-column-of-cjk-row-boxes
       (charset
         starting-row-number number-of-rows workspace left-edge top-edge)
  (loop for row-number from starting-row-number
        repeat number-of-rows
        as row-box? = (make-cjk-row-box charset row-number)
        when row-box?
          do (add-to-workspace row-box? workspace left-edge top-edge)
             (setq top-edge (+w (bottom-edge-of-block row-box?) 10))))



(defparameter default-number-of-cjk-boxes-per-workspace 4)


(defun get-cjk-charset-range-edges (charset)
  (case charset
    (jis (values jis-high-byte-min jis-high-byte-max jis-low-byte-min jis-low-byte-max))
    (ks (values ksc-high-byte-min ksc-high-byte-max ksc-low-byte-min ksc-low-byte-max))
    (gb (values gb-high-byte-min gb-high-byte-max gb-low-byte-min gb-low-byte-max))))

(defvar cjk-charset-to-prefix-a-list
  '((jis . #w"JIS-X-O208-")
    (ks . #w"KS-C-5601-")
    (gb . #w"GB-2312-")))

(defun get-cjk-charset-row-name (charset row-number)
  (intern-text-string
    (tformat-text-string
      "~a~x00"
      (cdr (assq charset cjk-charset-to-prefix-a-list))
      row-number)))                        ; assumed: 2-digit hex representation

(defun likely-cjk-character-set-image-plane-and-workspace-p (image-plane workspace)
  (declare (ignore image-plane))
  (and (atom (name-or-names-for-frame workspace))
       (loop for (charset . prefix) in cjk-charset-to-prefix-a-list
             thereis (text-string-equal+
                       (symbol-name-text-string
                         (name-or-names-for-frame workspace))
                       prefix :end1 (lengthw prefix)))))

(defun make-cjk-character-set-workspaces (charset)
  (let ((number-of-boxes-per-workspace default-number-of-cjk-boxes-per-workspace))
    (multiple-value-bind (high-min high-max)
        (get-cjk-charset-range-edges charset)
      (loop for row-number from high-min to high-max
                           by number-of-boxes-per-workspace
            do (make-one-cjk-character-set-workspace
                 charset
                 row-number number-of-boxes-per-workspace
                 (get-cjk-charset-row-name charset row-number)
                 (floor (* (normalized-scale) .5))
                 t))))
  (neatly-stack-image-planes-in-pane
    current-workstation-detail-pane
    'right 'top
    (-r (right-edge-of-pane-in-window
          (first (stack-of-image-planes current-workstation-detail-pane)))
        10)
    (+r (top-edge-of-pane-in-window
          (first (stack-of-image-planes current-workstation-detail-pane)))
        10)
    -35 18
    'kb-workspace
    #'likely-cjk-character-set-image-plane-and-workspace-p))

)  ; end #+development progn
